#!/usr/bin/env python3
"""
Mutation Scanner v2 — Mandelbulber2 mutation system audit tool.

Read-only diagnostics for CPU/GPU parity, parameter wiring, UI XML, and safety heuristics.

Usage:
  python3 mutation_scanner.py                  # summary report
  python3 mutation_scanner.py --verbose        # all issues
  python3 mutation_scanner.py --ci-smoke       # infra check (always use in CI for now)
  python3 mutation_scanner.py --ci             # fail on CRITICAL + HIGH findings
  python3 mutation_scanner.py --json out.json  # machine-readable report
  python3 mutation_scanner.py --markdown out.md
  python3 mutation_scanner.py --validate-ui    # parse mutation-related .ui files
"""

from __future__ import annotations

import argparse
import json
import re
import sys
import xml.etree.ElementTree as ET
from collections import defaultdict
from pathlib import Path
from typing import Dict, List, Optional, Set, Tuple

# ─── Paths ────────────────────────────────────────────────────────────────────

ROOT = Path(__file__).resolve().parent.parent.parent  # mandelbulber2/
MUTATIONS_DIR = ROOT / "mutations"
EXEMPTIONS_FILE = MUTATIONS_DIR / "config" / "scanner_exemptions.json"

CPU_FILE = ROOT / "src" / "compute_fractal.cpp"
GPU_FILES = [
    ROOT / "opencl" / "engines" / "compute_fractal.cl",
    ROOT / "opencl" / "engines" / "nebula.cl",
]
CPU_STRUCT = ROOT / "src" / "nine_fractals.hpp"
GPU_STRUCT = ROOT / "opencl" / "fractal_sequence_cl.h"
INIT_PARAMS = ROOT / "src" / "initparameters.cpp"
NINE_FRACT = ROOT / "src" / "nine_fractals.cpp"
MUTATION_TAB_CPP = ROOT / "qt" / "dock_mutation_tab.cpp"
MUTATION_TAB_UI = ROOT / "qt" / "dock_mutation_tab.ui"
DOCK_EFFECTS_UI = ROOT / "qt" / "dock_effects.ui"

UI_FILES = [MUTATION_TAB_UI, DOCK_EFFECTS_UI]

CRITICAL = "CRITICAL"
HIGH = "HIGH"
MEDIUM = "MEDIUM"
LOW = "LOW"

SECTION_MARKER = re.compile(r"v7\.\d+[a-z]?.*—")
SWITCH_RE = re.compile(r"\bswitch\s*\(")
CASE_RE = re.compile(r"case\s+(\d+)\s*:")


class Issue:
    __slots__ = ("severity", "category", "file", "line", "message")

    def __init__(self, severity: str, category: str, file: str, line: int, message: str):
        self.severity = severity
        self.category = category
        self.file = file
        self.line = line
        self.message = message

    def to_dict(self) -> dict:
        return {
            "severity": self.severity,
            "category": self.category,
            "file": self.file,
            "line": self.line,
            "message": self.message,
        }


class ScanResult:
    __slots__ = ("issues", "gpu_struct_bytes", "meta")

    def __init__(self):
        self.issues: List[Issue] = []
        self.gpu_struct_bytes: int = 0
        self.meta: Dict[str, object] = {}


def load_exemptions() -> dict:
    if not EXEMPTIONS_FILE.is_file():
        return {"param_read_exempt": [], "param_ui_exempt": [], "ui_widget_prefix_exempt": []}
    with open(EXEMPTIONS_FILE, encoding="utf-8") as f:
        return json.load(f)


def report(result: ScanResult, severity: str, category: str, filepath: Path, line: int, message: str) -> None:
    result.issues.append(
        Issue(
            severity=severity,
            category=category,
            file=filepath.name if isinstance(filepath, Path) else str(filepath),
            line=line,
            message=message,
        )
    )


def normalize_section(name: str) -> str:
    name = re.sub(r"\s*\[GPU[^\]]*\]\s*", " ", name)
    name = re.sub(r"\s+", " ", name).strip("/ \t")
    name = re.sub(r"\bv7\.14f\b", "v7.14", name)
    return name[:50]


def extract_switch_cases(lines: List[str]) -> Dict[str, Set[int]]:
    """Collect switch case numbers scoped to the switch after each v7 section marker."""
    sections: Dict[str, Set[int]] = {}
    i = 0
    while i < len(lines):
        stripped = lines[i].strip()
        if SECTION_MARKER.search(stripped):
            sec = normalize_section(stripped)
            switch_idx: Optional[int] = None
            for j in range(i + 1, min(i + 80, len(lines))):
                if SWITCH_RE.search(lines[j]):
                    switch_idx = j
                    break
            cases: Set[int] = set()
            if switch_idx is not None:
                depth = 0
                started = False
                for j in range(switch_idx, min(switch_idx + 1200, len(lines))):
                    line = lines[j]
                    if not started:
                        if "{" in line:
                            started = True
                            depth = line.count("{") - line.count("}")
                        continue
                    depth += line.count("{") - line.count("}")
                    m = CASE_RE.match(line.strip())
                    if m:
                        cases.add(int(m.group(1)))
                    if depth <= 0 and j > switch_idx:
                        break
            if cases:
                sections[sec] = cases
        i += 1
    return sections


def merge_gpu_sections(gpu_section_maps: List[Dict[str, Set[int]]]) -> Dict[str, Set[int]]:
    merged: Dict[str, Set[int]] = {}
    for section_map in gpu_section_maps:
        for name, cases in section_map.items():
            merged.setdefault(name, set()).update(cases)
    return merged


def find_gpu_section(cpu_name: str, gpu_sections: Dict[str, Set[int]]) -> Set[int]:
    for gpu_name, cases in gpu_sections.items():
        if gpu_name[:40] == cpu_name[:40]:
            return cases
    return set()


# ─── Scanner: UI XML ──────────────────────────────────────────────────────────

def scan_ui_xml(result: ScanResult, ui_files: List[Path]) -> None:
    for ui_path in ui_files:
        if not ui_path.is_file():
            report(result, HIGH, "UI_FILE_MISSING", ui_path, 0, f"UI file not found: {ui_path}")
            continue
        try:
            ET.parse(ui_path)
        except ET.ParseError as exc:
            report(result, CRITICAL, "UI_XML_PARSE", ui_path, exc.position[0] if exc.position else 0, str(exc))


# ─── Scanner: GPU conversion heuristics ───────────────────────────────────────

def scan_gpu_conversions(result: ScanResult, gpu_lines: List[str], filepath: Path) -> None:
    in_mutation = False
    for i, line in enumerate(gpu_lines, 1):
        stripped = line.strip()
        if SECTION_MARKER.search(stripped):
            in_mutation = True
            continue
        if not in_mutation or stripped.startswith("//"):
            continue

        if re.search(r"\bdouble\b", stripped):
            ctx = stripped[max(0, stripped.find("double") - 10) : stripped.find("double") + 30]
            report(result, CRITICAL, "GPU_DOUBLE", filepath, i, f"'double' in GPU code: ...{ctx}...")

        if re.search(r"\bM_PI\b(?!_F)", stripped):
            report(result, CRITICAL, "GPU_M_PI", filepath, i, "M_PI without _F suffix")

        if re.search(r"\bmut\.(?!torusType)", stripped) and "mut->" not in stripped:
            report(result, CRITICAL, "GPU_MUT_DOT", filepath, i, "'mut.' used instead of 'mut->'")

        if re.search(r"\bCVector[34]\b", stripped):
            report(result, CRITICAL, "GPU_CVECTOR", filepath, i,
                   "CVector3/CVector4 is C++ only — use float3/float4 or (float4)(...)")

        if re.search(r"\bin\.point\b", stripped):
            report(result, CRITICAL, "GPU_IN_POINT", filepath, i,
                   "in.point is C++ only — use length(point) in OpenCL Fractal()")

        if re.search(r"\bint\([^)]+\)", stripped):
            report(result, CRITICAL, "GPU_CPP_CAST", filepath, i,
                   "C++ cast int(...) — use (int)expr in OpenCL")

        if re.search(r"\bfloat\([a-z_]", stripped):
            report(result, CRITICAL, "GPU_CPP_CAST", filepath, i,
                   "C++ cast float(...) — use (float)expr in OpenCL")

        if not stripped.startswith("case "):
            continue

        for func in ("sin", "cos", "exp", "sqrt", "log", "tan"):
            for m in re.finditer(rf"(?<![a-zA-Z_]){func}\(", stripped):
                pre = stripped[max(0, m.start() - 7) : m.start()]
                if "native_" in pre:
                    continue
                pre1 = stripped[max(0, m.start() - 1) : m.start()]
                if pre1 in ("a", "h"):
                    continue
                report(result, HIGH, f"GPU_BARE_{func.upper()}", filepath, i,
                       f"Bare {func}() should be native_{func}() in OpenCL case")


# ─── Scanner: runtime safety heuristics ─────────────────────────────────────

def scan_runtime_safety(result: ScanResult, lines: List[str], filepath: Path) -> None:
    in_mutation = False
    for i, line in enumerate(lines, 1):
        stripped = line.strip()
        if SECTION_MARKER.search(stripped):
            in_mutation = True
            continue
        if not in_mutation or stripped.startswith("//") or not stripped.startswith("case "):
            continue

        for m in re.finditer(r"/\s*\(([^)]+)\)", stripped):
            denom = m.group(1)
            if not any(p in denom for p in ("fmax", "+1e-", "+0.0", "fabs")):
                if not re.match(r"^[\d.]+f?$", denom.strip()):
                    report(result, MEDIUM, "DIV_ZERO", filepath, i,
                           f"Division by ({denom[:40]}) without fmax() protection")

        for m in re.finditer(r"(?:native_)?log\(([^)]{1,80})\)", stripped):
            arg = m.group(1).strip()
            if re.match(r"^[\d.]+f?$", arg):
                continue
            if any(p in arg for p in ("+", "fmax", "fabs", "1.0", "1e-")):
                continue
            # log(n) where n = fmax(i+1, 1) on the same case line is safe
            if re.match(r"^[a-zA-Z_]\w*$", arg) and re.search(
                rf"{re.escape(arg)}\s*=\s*fmax\(", stripped
            ):
                continue
            report(result, HIGH, "LOG_DOMAIN", filepath, i,
                   f"log({arg[:50]}) — argument may be zero or negative")

        if "aux.DE *=" in stripped:
            after_eq = stripped.split("aux.DE *=", 1)[1]
            if "fmin" not in after_eq and "fmax" not in after_eq and "exp(" in after_eq:
                report(result, MEDIUM, "DE_UNBOUNDED", filepath, i,
                       "aux.DE *= exp(...) without clamp")


# ─── Scanner: CPU/GPU case parity ───────────────────────────────────────────

def scan_case_parity(result: ScanResult, cpu_lines: List[str], gpu_files: List[Path]) -> None:
    cpu_sections = extract_switch_cases(cpu_lines)
    gpu_maps = []
    for gpu_path in gpu_files:
        with open(gpu_path, encoding="utf-8") as f:
            gpu_maps.append(extract_switch_cases(f.readlines()))
    gpu_sections = merge_gpu_sections(gpu_maps)

    result.meta["cpu_mutation_sections"] = len(cpu_sections)
    result.meta["gpu_mutation_sections"] = len(gpu_sections)

    for sec_name, cpu_cases in sorted(cpu_sections.items()):
        gpu_cases = find_gpu_section(sec_name, gpu_sections)
        if not gpu_cases:
            report(result, CRITICAL, "SECTION_MISSING_GPU", GPU_FILES[0], 0,
                   f"Section '{sec_name}' ({len(cpu_cases)} CPU cases) not found in GPU kernels")
            continue

        cpu_only = sorted(cpu_cases - gpu_cases - {0})
        gpu_only = sorted(gpu_cases - cpu_cases - {0})
        if cpu_only:
            preview = cpu_only[:12]
            suffix = "..." if len(cpu_only) > 12 else ""
            report(result, CRITICAL, "CASE_MISSING_GPU", GPU_FILES[0], 0,
                   f"Section '{sec_name}': CPU cases missing on GPU: {preview}{suffix} ({len(cpu_only)} total)")
        if gpu_only:
            preview = gpu_only[:12]
            suffix = "..." if len(gpu_only) > 12 else ""
            report(result, HIGH, "CASE_MISSING_CPU", CPU_FILE, 0,
                   f"Section '{sec_name}': GPU cases missing on CPU: {preview}{suffix} ({len(gpu_only)} total)")


# ─── Scanner: struct size ─────────────────────────────────────────────────────

def scan_struct_parity(result: ScanResult) -> int:
    with open(GPU_STRUCT, encoding="utf-8") as f:
        gpu = f.read()
    gstart = gpu.find("cl_int enabled;")
    gend = gpu.find("} sClFormulaMutationParams;")
    gpu_body = gpu[gstart:gend] if gstart > 0 else ""
    n_floats = len(re.findall(r"\bcl_float\b", gpu_body))
    n_ints = len(re.findall(r"\bcl_int\b", gpu_body))
    n_mats = len(re.findall(r"matrix33", gpu_body))
    size_per_slot = n_floats * 4 + n_ints * 4 + n_mats * 36
    total_size = size_per_slot * 9
    if total_size > 85 * 1024:
        report(result, CRITICAL, "STRUCT_SIZE", GPU_STRUCT, 0,
               f"GPU struct too large: {total_size / 1024:.1f} KB > 85 KB limit")
    return total_size


# ─── Scanner: parameter registration ────────────────────────────────────────

def param_base_name(name: str) -> str:
    return re.sub(r"_\d+$", "", name)


def scan_param_registration(result: ScanResult, exemptions: dict) -> None:
    with open(INIT_PARAMS, encoding="utf-8") as f:
        init = f.read()
    with open(NINE_FRACT, encoding="utf-8") as f:
        nf = f.read()

    registered = set(re.findall(r'addParam\("(mutation_\w+)"', init))
    reads = set(re.findall(r'Get<\w+>\("(mutation_\w+)"', nf))
    reads |= set(re.findall(r'"(mutation_\w+)"', nf)) & registered

    read_exempt = set(exemptions.get("param_read_exempt", []))
    reg_only = registered - reads - read_exempt
    read_only = reads - registered

    for p in sorted(reg_only):
        report(result, HIGH, "PARAM_NO_READ", NINE_FRACT, 0,
               f"Parameter '{p}' registered but not referenced in nine_fractals.cpp")
    for p in sorted(read_only):
        report(result, HIGH, "PARAM_NO_REG", INIT_PARAMS, 0,
               f"Parameter '{p}' referenced but not registered in initparameters.cpp")

    result.meta["mutation_params_registered"] = len(registered)
    result.meta["mutation_params_read"] = len(reads & registered)


# ─── Scanner: UI ↔ parameter audit ───────────────────────────────────────────

def widget_base_to_param(widget_base: str) -> Optional[str]:
    """Best-effort map spinbox_mutation_foo → mutation_foo (slot suffix added at runtime)."""
    for prefix in ("spinbox_", "checkBox_", "comboBox_", "slider_"):
        if widget_base.startswith(prefix):
            widget_base = widget_base[len(prefix) :]
            break
    if not widget_base.startswith("mutation_"):
        return None
    return widget_base


def scan_ui_param_audit(result: ScanResult, exemptions: dict) -> None:
    with open(INIT_PARAMS, encoding="utf-8") as f:
        init = f.read()
    registered_bases = {param_base_name(p) for p in re.findall(r'addParam\("(mutation_\w+)"', init)}

    ui_param_bases: Set[str] = set()
    if MUTATION_TAB_UI.is_file():
        ui_text = MUTATION_TAB_UI.read_text(encoding="utf-8")
        for name in re.findall(r'name="([^"]+)"', ui_text):
            if "mutation" not in name:
                continue
            param = widget_base_to_param(name)
            if param and re.fullmatch(r"mutation_[a-z0-9_]+", param):
                ui_param_bases.add(param)

    if MUTATION_TAB_CPP.is_file():
        cpp = MUTATION_TAB_CPP.read_text(encoding="utf-8")
        for param in re.findall(r'"(mutation_[a-z0-9_]+_\d+)"', cpp):
            ui_param_bases.add(param_base_name(param))
        for param in re.findall(r'"(mutation_[a-z0-9_]+)"\s*\+', cpp):
            ui_param_bases.add(param.rstrip("_"))

    ui_exempt = set(exemptions.get("param_ui_exempt", []))
    prefix_exempt = tuple(exemptions.get("ui_widget_prefix_exempt", []))

    unmapped_widgets = sorted(
        p for p in ui_param_bases
        if p not in registered_bases and p not in ui_exempt
    )
    for p in unmapped_widgets[:40]:
        report(result, HIGH, "UI_WIDGET_NO_PARAM", MUTATION_TAB_UI, 0,
               f"UI references '{p}' but no matching mutation_* parameter base in initparameters.cpp")
    if len(unmapped_widgets) > 40:
        report(result, HIGH, "UI_WIDGET_NO_PARAM", MUTATION_TAB_UI, 0,
               f"... and {len(unmapped_widgets) - 40} more unmapped UI param bases")

    # Headless registered params without UI (informational HIGH, many expected)
    headless = sorted(
        p for p in registered_bases
        if p not in ui_param_bases and p not in ui_exempt and p not in exemptions.get("param_read_exempt", [])
    )
    result.meta["ui_param_bases"] = len(ui_param_bases)
    result.meta["registered_param_bases"] = len(registered_bases)
    result.meta["headless_param_bases"] = len(headless)


# ─── Scanner: iteration guards ────────────────────────────────────────────────

def scan_iteration_controls(result: ScanResult, cpu_lines: List[str]) -> None:
    section = None
    has_iter_guard = False
    for line in cpu_lines:
        stripped = line.strip()
        if SECTION_MARKER.search(stripped):
            if section and not has_iter_guard:
                report(result, MEDIUM, "NO_ITER_GUARD", CPU_FILE, 0,
                       f"Section '{section[:50]}' may lack iteration range guard")
            section = stripped.strip("/ \t")[:60]
            has_iter_guard = False
        if section and "IterStart" in stripped and "IterStop" in stripped:
            has_iter_guard = True


# ─── Run all scans ────────────────────────────────────────────────────────────

def run_scan(validate_ui: bool = True, section_filter: Optional[str] = None) -> ScanResult:
    result = ScanResult()
    exemptions = load_exemptions()

    if validate_ui:
        scan_ui_xml(result, UI_FILES)

    with open(CPU_FILE, encoding="utf-8") as f:
        cpu_lines = f.readlines()

    for gpu_path in GPU_FILES:
        with open(gpu_path, encoding="utf-8") as f:
            gpu_lines = f.readlines()
        scan_gpu_conversions(result, gpu_lines, gpu_path)
        scan_runtime_safety(result, gpu_lines, gpu_path)

    scan_runtime_safety(result, cpu_lines, CPU_FILE)
    scan_case_parity(result, cpu_lines, GPU_FILES)
    result.gpu_struct_bytes = scan_struct_parity(result)
    scan_param_registration(result, exemptions)
    scan_ui_param_audit(result, exemptions)
    scan_iteration_controls(result, cpu_lines)

    if section_filter:
        needle = section_filter.lower()
        result.issues = [
            issue for issue in result.issues
            if needle in issue.message.lower() or needle in issue.category.lower()
        ]

    return result


def group_issues(issues: List[Issue]) -> Tuple[Dict[str, List[Issue]], Dict[str, List[Issue]]]:
    by_severity: Dict[str, List[Issue]] = defaultdict(list)
    by_category: Dict[str, List[Issue]] = defaultdict(list)
    for issue in issues:
        by_severity[issue.severity].append(issue)
        by_category[issue.category].append(issue)
    return by_severity, by_category


def print_report(result: ScanResult, verbose: bool = False) -> None:
    by_severity, by_category = group_issues(result.issues)
    print("=" * 70)
    print("  Mutation Scanner v2 — Mandelbulber2 Code Quality Audit")
    print("=" * 70)
    print()
    print(f"  GPU struct size: {result.gpu_struct_bytes / 1024:.1f} KB / 85 KB")
    print(f"  Mutation params registered: {result.meta.get('mutation_params_registered', '?')}")
    print(f"  CPU mutation sections: {result.meta.get('cpu_mutation_sections', '?')}")
    print(f"  Total issues: {len(result.issues)}")
    print()
    for sev in (CRITICAL, HIGH, MEDIUM, LOW):
        count = len(by_severity[sev])
        if count:
            print(f"  {sev}: {count}")
    print()
    print("  By category:")
    for cat in sorted(by_category):
        print(f"    {cat}: {len(by_category[cat])}")

    if verbose:
        print()
        print("-" * 70)
        for sev in (CRITICAL, HIGH, MEDIUM, LOW):
            for issue in by_severity[sev]:
                print(f"  [{issue.severity}] {issue.file}:{issue.line} ({issue.category}) {issue.message}")

    print()
    crit = len(by_severity[CRITICAL])
    high = len(by_severity[HIGH])
    if crit == 0 and high == 0:
        print("  STATUS: no CRITICAL/HIGH issues")
    else:
        print(f"  STATUS: {crit} CRITICAL, {high} HIGH")
    print("=" * 70)


def write_json(result: ScanResult, path: Path) -> None:
    by_severity, by_category = group_issues(result.issues)
    payload = {
        "scanner_version": 2,
        "gpu_struct_bytes": result.gpu_struct_bytes,
        "meta": result.meta,
        "counts": {sev: len(by_severity[sev]) for sev in (CRITICAL, HIGH, MEDIUM, LOW)},
        "categories": {cat: len(items) for cat, items in sorted(by_category.items())},
        "issues": [issue.to_dict() for issue in result.issues],
    }
    path.write_text(json.dumps(payload, indent=2), encoding="utf-8")


def write_markdown(result: ScanResult, path: Path) -> None:
    by_severity, by_category = group_issues(result.issues)
    lines = [
        "# Mutation Scanner Report",
        "",
        f"- GPU struct: {result.gpu_struct_bytes / 1024:.1f} KB",
        f"- Issues: {len(result.issues)}",
        "",
        "## Counts by severity",
        "",
    ]
    for sev in (CRITICAL, HIGH, MEDIUM, LOW):
        lines.append(f"- **{sev}**: {len(by_severity[sev])}")
    lines.extend(["", "## Counts by category", ""])
    for cat in sorted(by_category):
        lines.append(f"- `{cat}`: {len(by_category[cat])}")
    lines.extend(["", "## CRITICAL + HIGH", ""])
    for sev in (CRITICAL, HIGH):
        for issue in by_severity[sev]:
            lines.append(f"- `{issue.category}` {issue.file}:{issue.line} — {issue.message}")
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def exit_code_for(result: ScanResult, ci: bool, ci_smoke: bool) -> int:
    if ci_smoke:
        return 0
    if not ci:
        by_severity, _ = group_issues(result.issues)
        return 1 if by_severity[CRITICAL] else 0
    by_severity, _ = group_issues(result.issues)
    if by_severity[CRITICAL] or by_severity[HIGH]:
        return 1
    return 0


def parse_args(argv: List[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Mandelbulber2 mutation system scanner")
    parser.add_argument("--verbose", "-v", action="store_true")
    parser.add_argument("--ci", action="store_true", help="Exit 1 on CRITICAL or HIGH issues")
    parser.add_argument("--ci-smoke", action="store_true", help="Run scans but always exit 0 (infra gate)")
    parser.add_argument("--json", metavar="PATH", help="Write JSON report")
    parser.add_argument("--markdown", metavar="PATH", help="Write Markdown report")
    parser.add_argument("--validate-ui", action="store_true", help="Only validate UI XML files")
    parser.add_argument("--section", metavar="NAME", help="Filter issues by section/category substring")
    return parser.parse_args(argv)


def main(argv: Optional[List[str]] = None) -> int:
    args = parse_args(argv or sys.argv[1:])

    if args.validate_ui:
        result = ScanResult()
        scan_ui_xml(result, UI_FILES)
        for issue in result.issues:
            print(f"[{issue.severity}] {issue.file}: {issue.message}")
        return 1 if any(i.severity == CRITICAL for i in result.issues) else 0

    result = run_scan(validate_ui=True, section_filter=args.section)
    print_report(result, verbose=args.verbose)

    if args.json:
        write_json(result, Path(args.json))
    if args.markdown:
        write_markdown(result, Path(args.markdown))

    return exit_code_for(result, ci=args.ci, ci_smoke=args.ci_smoke)


if __name__ == "__main__":
    sys.exit(main())

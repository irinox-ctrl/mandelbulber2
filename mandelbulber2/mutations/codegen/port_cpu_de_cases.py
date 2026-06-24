#!/usr/bin/env python3
"""
Port missing mutation DE switch cases from CPU (compute_fractal.cpp) to GPU (compute_fractal.cl).

Read-only by default. Use --apply to patch the OpenCL file, then run apply_mutation_prune_cl.py.

Example:
  python3 port_cpu_de_cases.py --list
  python3 port_cpu_de_cases.py --system jos_leys --dry-run
  python3 port_cpu_de_cases.py --all --apply
"""

from __future__ import annotations

import argparse
import re
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Tuple

ROOT = Path(__file__).resolve().parent.parent.parent
CPU_FILE = ROOT / "src" / "compute_fractal.cpp"
GPU_FILE = ROOT / "opencl" / "engines" / "compute_fractal.cl"


@dataclass
class DeSection:
    section_id: str
    marker: str
    cpu_switch: str
    gpu_switch: str


SECTIONS: List[DeSection] = [
    DeSection("jos_leys", "v7.7 — Jos Leys DE system", r"switch\s*\(\s*mut\.josLeysDeType\s*\)", r"switch\s*\(\s*mut->josLeysDeType\s*\)"),
    DeSection("pk", "v7.7 — Pseudokleinian DE system", r"switch\s*\(\s*mut\.pseudoKleinianDeType\s*\)", r"switch\s*\(\s*mut->pseudoKleinianDeType\s*\)"),
    DeSection("mb_math", "v7.8 — Mandelbox Math system", r"switch\s*\(\s*mut\.mbMathType\s*\)", r"switch\s*\(\s*mut->mbMathType\s*\)"),
    DeSection("warp_dist", "v7.9 — Warp Distortion system", r"switch\s*\(\s*mut\.warpDistType\s*\)", r"switch\s*\(\s*mut->warpDistType\s*\)"),
    DeSection("sym_kal", "v7.9 — Symmetry/Kaleidoscope system", r"switch\s*\(\s*mut\.symKalType\s*\)", r"switch\s*\(\s*mut->symKalType\s*\)"),
    DeSection("abox", "v7.9 — Abox DE system", r"switch\s*\(\s*mut\.aboxType\s*\)", r"switch\s*\(\s*mut->aboxType\s*\)"),
    DeSection("noise", "v7.10 — Noise & Procedural DE system", r"switch\s*\(\s*mut\.noiseType\s*\)", r"switch\s*\(\s*mut->noiseType\s*\)"),
    DeSection("orbit_trap", "v7.10 — Orbit Trap DE system", r"switch\s*\(\s*mut\.orbitTrapType\s*\)", r"switch\s*\(\s*mut->orbitTrapType\s*\)"),
    DeSection("torus", "v7.12 — MandelTorus DE system", r"switch\s*\(\s*mut\.torusType\s*\)", r"switch\s*\(\s*mut->torusType\s*\)"),
    DeSection("as", "v7.13 — Amazing Surf 1-4 DE system", r"switch\s*\(\s*mut\.asType\s*\)", r"switch\s*\(\s*mut->asType\s*\)"),
    DeSection("sm", "v7.13 — SphereTree/Menger DE system", r"switch\s*\(\s*mut\.smType\s*\)", r"switch\s*\(\s*mut->smType\s*\)"),
]


def find_marker_pos(text: str, marker: str) -> int:
    idx = text.find(marker)
    if idx >= 0:
        return idx
    gpu_marker = marker.replace(" — ", " [GPU] — ", 1)
    idx = text.find(gpu_marker)
    if idx >= 0:
        return idx
    short = marker.split(" — ", 1)[0]
    for line in text.splitlines():
        if short in line and "—" in line:
            return text.find(line)
    raise ValueError(f"Marker not found: {marker}")


def find_switch_body(text: str, switch_pattern: str, start: int) -> Tuple[int, int, str]:
    m = re.search(switch_pattern, text[start:])
    if not m:
        raise ValueError(f"Switch not found after marker: {switch_pattern}")
    switch_start = start + m.start()
    brace = text.find("{", switch_start)
    if brace < 0:
        raise ValueError("Switch opening brace not found")
    depth = 0
    for i in range(brace, len(text)):
        ch = text[i]
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                body = text[brace + 1 : i]
                return switch_start, i + 1, body
    raise ValueError("Switch closing brace not found")


def strip_prune_guards(body: str) -> str:
    lines = []
    for line in body.splitlines():
        s = line.strip()
        if s.startswith("#if") or s.startswith("#endif"):
            continue
        lines.append(line)
    return "\n".join(lines)


def extract_cases(switch_body: str) -> Dict[int, str]:
    body = strip_prune_guards(switch_body)
    cases: Dict[int, str] = {}
    pattern = re.compile(r"case\s+(\d+)\s*:\s*(.*?)\sbreak\s*;", re.DOTALL)
    for m in pattern.finditer(body):
        case_body = m.group(2).strip()
        if case_body.startswith("{"):
            case_body = case_body[1:].lstrip()
        cases[int(m.group(1))] = case_body
    return cases


def cpu_body_to_gpu(body: str) -> str:
    out = body
    out = out.replace("CVector4", "float4")
    out = re.sub(r"\bdouble\b", "float", out)
    out = re.sub(r"\(double\)", "(float)", out)
    out = re.sub(r"\bM_PI\b", "M_PI_F", out)
    for fn in ("sin", "cos", "exp", "sqrt", "log", "pow", "floor", "ceil", "tan", "asin", "acos", "atan"):
        out = re.sub(rf"(?<!native_)\b{fn}\(", rf"native_{fn}(", out)
    out = out.replace("native_native_", "native_")
    out = re.sub(r"\bpow\(", "native_powr(", out)  # fallback if pow missed
    out = re.sub(r"fmax\(\s*1e-10\s*,", "fmax(1e-10f,", out)
    out = re.sub(r"fmax\(\s*1e-21\s*,", "fmax(1e-21f,", out)
    out = re.sub(r"fmin\(\s*1e-10\s*,", "fmin(1e-10f,", out)
    out = re.sub(r"\b1e-21\b(?![fF])", "1e-21f", out)
    out = re.sub(r"\b1e-10\b(?![fF])", "1e-10f", out)
    out = re.sub(r"(?<![\w.])(\d+\.\d+)(?![fFeEdD\w])", r"\1f", out)
    out = re.sub(r"\bCVector4\b", "float4", out)
    out = re.sub(r"\bCVector3\b", "float3", out)
    out = re.sub(r"\.GetXYZ\(\)", ".xyz", out)
    out = re.sub(r"\bin\.point\.Length\(\)", "length(pointTransformed)", out)

    def _cpp_cast_to_ocl(m: re.Match) -> str:
        typ = m.group(1)
        inner = m.group(2)
        return f"({typ})({inner})"

    out = re.sub(r"\b(int|float)\(([^()]*(?:\([^()]*\)[^()]*)*)\)", _cpp_cast_to_ocl, out)
    return out


def detect_case_indent(switch_body: str) -> str:
    body = strip_prune_guards(switch_body)
    m = re.search(r"^(\s*)case\s+\d+\s*:", body, re.MULTILINE)
    return m.group(1) if m else "\t\t\t\t\t"


def build_gpu_cases(missing: Dict[int, str], indent: str) -> str:
    lines = []
    for num in sorted(missing):
        body = cpu_body_to_gpu(missing[num])
        lines.append(f"{indent}case {num}: {{ {body} break; }}")
    return "\n".join(lines) + ("\n" if lines else "")


def port_section(section: DeSection, cpu_text: str, gpu_text: str) -> Tuple[str, int, int]:
    cpu_start = find_marker_pos(cpu_text, section.marker)
    _, _, cpu_body = find_switch_body(cpu_text, section.cpu_switch, cpu_start)
    cpu_cases = extract_cases(cpu_body)

    gpu_marker_pos = find_marker_pos(gpu_text, section.marker)
    gpu_switch_start, gpu_switch_end, gpu_body = find_switch_body(gpu_text, section.gpu_switch, gpu_marker_pos)
    gpu_cases = extract_cases(gpu_body)

    missing_nums = sorted(set(cpu_cases) - set(gpu_cases))
    if not missing_nums:
        return gpu_text, 0, max(cpu_cases) if cpu_cases else 0

    missing = {n: cpu_cases[n] for n in missing_nums}
    indent = detect_case_indent(gpu_body)
    insert_block = build_gpu_cases(missing, indent)

    default_match = re.search(r"(\s*)default\s*:\s*break\s*;", gpu_body)
    if not default_match:
        raise ValueError(f"No default:break in GPU switch for {section.section_id}")

    brace_open = gpu_text.find("{", gpu_switch_start)
    body_start = brace_open + 1
    insert_at = body_start + default_match.start()

    new_gpu = gpu_text[:insert_at] + insert_block + gpu_text[insert_at:]
    return new_gpu, len(missing_nums), max(cpu_cases)


def port_section_safe(section: DeSection, cpu_text: str, gpu_text: str) -> Tuple[str, int, int]:
    try:
        return port_section(section, cpu_text, gpu_text)
    except ValueError as exc:
        print(f"  SKIP {section.section_id}: {exc}", file=sys.stderr)
        return gpu_text, 0, 0


def main() -> int:
    parser = argparse.ArgumentParser(description="Port CPU DE mutation cases to GPU OpenCL")
    parser.add_argument("--system", action="append", help="Section id (repeatable)")
    parser.add_argument("--all", action="store_true", help="Port all DE sections")
    parser.add_argument("--list", action="store_true", help="List section ids")
    parser.add_argument("--apply", action="store_true", help="Write GPU file")
    parser.add_argument("--dry-run", action="store_true", help="Print counts only")
    args = parser.parse_args()

    if args.list:
        for s in SECTIONS:
            print(s.section_id, "-", s.marker)
        return 0

    selected = SECTIONS
    if args.system:
        wanted = set(args.system)
        selected = [s for s in SECTIONS if s.section_id in wanted]
        unknown = wanted - {s.section_id for s in selected}
        if unknown:
            print(f"Unknown systems: {', '.join(sorted(unknown))}", file=sys.stderr)
            return 2

    if not args.all and not args.system:
        parser.error("Specify --all or --system <id>")

    cpu_text = CPU_FILE.read_text(encoding="utf-8")
    gpu_text = GPU_FILE.read_text(encoding="utf-8")
    total_added = 0

    for section in selected:
        gpu_text, added, cpu_max = port_section_safe(section, cpu_text, gpu_text)
        print(f"{section.section_id}: +{added} cases (CPU max={cpu_max})")
        total_added += added

    print(f"Total cases to add: {total_added}")
    if args.apply and total_added > 0:
        GPU_FILE.write_text(gpu_text, encoding="utf-8")
        print(f"Wrote {GPU_FILE}")
    elif total_added > 0 and not args.dry_run:
        print("Dry run — pass --apply to write changes")
    return 0


if __name__ == "__main__":
    sys.exit(main())

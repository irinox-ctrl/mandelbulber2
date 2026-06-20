#!/usr/bin/env python3
"""
Formula registry audit — C++ definition / OpenCL / UI / enum matrix.

Verifies registered formulas in all_fractal_list.cpp against on-disk assets
and enum consistency. Supports formula-freeze baseline checks.

Usage:
  python3 formula_audit.py
  python3 formula_audit.py --ci
  python3 formula_audit.py --markdown mutations/audit/FORMULA_AUDIT.md
  python3 formula_audit.py --json report.json
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from collections import Counter
from dataclasses import dataclass, field
from datetime import date
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent.parent
DEF_DIR = ROOT / "formula" / "definition"
OCL_SRC = ROOT / "formula" / "opencl"
OCL_SHARE = ROOT / "share" / "mandelbulber2" / "formula" / "opencl"
UI_DIR = ROOT / "share" / "mandelbulber2" / "formula" / "ui"
LIST_CPP = DEF_DIR / "all_fractal_list.cpp"
ENUM_HPP = DEF_DIR / "all_fractal_list_enums.hpp"
ALLOWLIST_FILE = ROOT / "mutations" / "config" / "formula_audit_allowlist.json"


@dataclass
class FormulaRow:
    internal_name: str
    class_name: str
    combo_name: str
    enum_id: str
    registered: bool = False
    has_cpp: bool = False
    has_opencl: bool = False
    has_ui: bool = False


@dataclass
class AuditResult:
    rows: list[FormulaRow] = field(default_factory=list)
    critical: list[str] = field(default_factory=list)
    warnings: list[str] = field(default_factory=list)
    info: list[str] = field(default_factory=list)


def load_allowlist() -> dict:
    if ALLOWLIST_FILE.is_file():
        return json.loads(ALLOWLIST_FILE.read_text(encoding="utf-8"))
    return {}


def parse_enum_names() -> set[str]:
    text = ENUM_HPP.read_text(encoding="utf-8")
    return set(re.findall(r"^\s*(\w+)\s*=", text, re.M)) - {"invalid"}


def parse_cpp_metadata() -> dict[str, dict]:
    """Map cFractalClass -> metadata from fractal_*.cpp files."""
    by_class: dict[str, dict] = {}
    for cpp in DEF_DIR.glob("fractal_*.cpp"):
        text = cpp.read_text(encoding="utf-8", errors="replace")
        m_class = re.search(r"(cFractal\w+)::cFractal\w+\(\)", text)
        m_name = re.search(r'internalName\s*=\s*"([^"]+)"', text)
        m_combo = re.search(r'nameInComboBox\s*=\s*"([^"]+)"', text)
        m_id = re.search(r"internalID\s*=\s*fractal::(\w+)", text)
        if not (m_class and m_name and m_id):
            continue
        internal = m_name.group(1)
        by_class[m_class.group(1)] = {
            "internal_name": internal,
            "combo_name": m_combo.group(1) if m_combo else "",
            "enum_id": m_id.group(1),
            "cpp_path": cpp,
            "cpp_name_ok": cpp.name == f"fractal_{internal}.cpp",
        }
    return by_class


def parse_registry_classes() -> list[str]:
    text = LIST_CPP.read_text(encoding="utf-8")
    return re.findall(r"fractalList->append\(new (cFractal\w+)\(\)\)", text)


def run_audit() -> AuditResult:
    allow = load_allowlist()
    missing_ocl_ok = set(allow.get("missing_opencl_ok", []))
    missing_ui_ok = set(allow.get("missing_ui_ok", []))
    orphan_ocl_ok = set(allow.get("orphan_opencl_ok", []))
    orphan_ui_ok = set(allow.get("orphan_ui_ok", []))
    unused_enum_ok = set(allow.get("unused_enum_ok", []))
    baseline_count = allow.get("baseline_registry_count")

    enum_names = parse_enum_names()
    by_class = parse_cpp_metadata()
    registry_classes = parse_registry_classes()

    ocl_src = {p.stem for p in OCL_SRC.glob("*.cl")}
    ocl_share = {p.stem for p in OCL_SHARE.glob("*.cl")}
    ui_files = {p.stem for p in UI_DIR.glob("*.ui")}

    result = AuditResult()
    registered_internals: set[str] = set()

    for cls in registry_classes:
        meta = by_class.get(cls)
        if not meta:
            result.critical.append(f"registry class missing cpp: {cls}")
            continue
        internal = meta["internal_name"]
        registered_internals.add(internal)
        row = FormulaRow(
            internal_name=internal,
            class_name=cls,
            combo_name=meta["combo_name"],
            enum_id=meta["enum_id"],
            registered=True,
            has_cpp=meta["cpp_path"].is_file(),
            has_opencl=internal in ocl_src,
            has_ui=internal in ui_files,
        )
        result.rows.append(row)

        if not meta["cpp_name_ok"]:
            result.critical.append(
                f"cpp filename mismatch: {meta['cpp_path'].name} vs fractal_{internal}.cpp"
            )
        if meta["enum_id"] not in enum_names:
            result.critical.append(f"internalID not in enum: {internal} -> fractal::{meta['enum_id']}")

        if not row.has_opencl and internal not in missing_ocl_ok:
            result.critical.append(f"registered missing OpenCL: {internal}")
        if not row.has_ui and internal not in missing_ui_ok:
            result.critical.append(f"registered missing UI: {internal}")

    # Duplicate checks across all cpp files
    internal_names = [m["internal_name"] for m in by_class.values()]
    enum_ids = [m["enum_id"] for m in by_class.values()]
    for name, count in Counter(internal_names).items():
        if count > 1:
            result.critical.append(f"duplicate internalName: {name} ({count}x)")
    for eid, count in Counter(enum_ids).items():
        if count > 1:
            result.critical.append(f"duplicate internalID: fractal::{eid} ({count}x)")

    # Orphan assets (on disk but not registered)
    all_internals = {m["internal_name"] for m in by_class.values()}
    for stem in sorted(ocl_src - registered_internals):
        if stem not in orphan_ocl_ok and stem in all_internals:
            result.warnings.append(f"cpp exists but not registered (opencl present): {stem}")
        elif stem not in orphan_ocl_ok:
            result.warnings.append(f"orphan OpenCL (not registered): {stem}")
    for stem in sorted(ui_files - registered_internals):
        if stem not in orphan_ui_ok:
            result.warnings.append(f"orphan UI (not registered): {stem}")

    # Share vs source OpenCL sync
    src_only = sorted(ocl_src - ocl_share)
    share_only = sorted(ocl_share - ocl_src)
    if src_only:
        result.critical.append(f"formula/opencl not in share: {src_only[:5]}" + (
            f" (+{len(src_only)-5} more)" if len(src_only) > 5 else ""
        ))
    if share_only:
        result.critical.append(f"share opencl not in formula/opencl: {share_only[:5]}" + (
            f" (+{len(share_only)-5} more)" if len(share_only) > 5 else ""
        ))

    # Enum values unused by any cpp (legacy / reserved)
    used_enums = {m["enum_id"] for m in by_class.values()}
    unused = sorted(enum_names - used_enums - {"none"})
    unexpected_unused = [e for e in unused if e not in unused_enum_ok]
    for e in unexpected_unused:
        result.warnings.append(f"enum unused by cpp (not in allowlist): fractal::{e}")
    for e in unused:
        if e in unused_enum_ok:
            result.info.append(f"enum reserved/unused (allowlisted): fractal::{e}")

    # Freeze baseline
    reg_count = len(registry_classes)
    if baseline_count is not None and reg_count != baseline_count:
        result.warnings.append(
            f"registry count drift: {reg_count} (baseline {baseline_count}) — update allowlist or freeze policy"
        )

    cpp_not_registered = sorted(all_internals - registered_internals - {"none"})
    for internal in cpp_not_registered:
        result.warnings.append(f"cpp defined but not in registry: {internal}")

    return result


def print_summary(result: AuditResult) -> None:
    registered = [r for r in result.rows if r.registered]
    with_ocl = sum(1 for r in registered if r.has_opencl)
    with_ui = sum(1 for r in registered if r.has_ui)

    print("Formula registry audit")
    print(f"  Registered:     {len(registered)}")
    print(f"  With OpenCL:    {with_ocl}/{len(registered)}")
    print(f"  With UI:        {with_ui}/{len(registered)}")
    print(f"  Critical:       {len(result.critical)}")
    print(f"  Warnings:       {len(result.warnings)}")
    if result.critical:
        for issue in result.critical[:15]:
            print(f"    CRIT  {issue}")
        if len(result.critical) > 15:
            print(f"    ... +{len(result.critical) - 15} more")
    if result.warnings:
        for issue in result.warnings[:10]:
            print(f"    WARN  {issue}")
        if len(result.warnings) > 10:
            print(f"    ... +{len(result.warnings) - 10} more")
    if not result.critical and not result.warnings:
        print("  Status: OK")


def write_markdown(result: AuditResult, path: Path) -> None:
    registered = [r for r in result.rows if r.registered]
    with_ocl = sum(1 for r in registered if r.has_opencl)
    with_ui = sum(1 for r in registered if r.has_ui)
    allow = load_allowlist()
    baseline = allow.get("baseline_registry_count", "?")

    lines = [
        "# Formula Registry Audit",
        "",
        f"*Generated: {date.today().isoformat()}*",
        "",
        "## Summary",
        "",
        "| Metric | Value |",
        "|--------|-------|",
        f"| Registered formulas | {len(registered)} |",
        f"| Baseline (freeze) | {baseline} |",
        f"| With C++ definition | {sum(1 for r in registered if r.has_cpp)}/{len(registered)} |",
        f"| With OpenCL | {with_ocl}/{len(registered)} |",
        f"| With UI | {with_ui}/{len(registered)} |",
        f"| Critical issues | {len(result.critical)} |",
        f"| Warnings | {len(result.warnings)} |",
        "",
        "## CI policy",
        "",
        "- **CRITICAL (fail `--ci`):** registered formula missing cpp/opencl/ui, enum drift, share sync",
        "- **WARN:** orphan assets, registry count drift, unallowlisted unused enums",
        "- **Allowlist:** `mutations/config/formula_audit_allowlist.json`",
        "",
        "## Known gaps (allowlisted)",
        "",
        f"- Missing OpenCL: `{', '.join(allow.get('missing_opencl_ok', []))}`",
        f"- Missing UI: `{', '.join(allow.get('missing_ui_ok', []))}`",
        "",
        "## Issues",
        "",
    ]
    if result.critical:
        lines.append("### Critical")
        lines.append("")
        for issue in result.critical:
            lines.append(f"- {issue}")
        lines.append("")
    if result.warnings:
        lines.append("### Warnings")
        lines.append("")
        for issue in result.warnings:
            lines.append(f"- {issue}")
        lines.append("")
    if not result.critical and not result.warnings:
        lines.append("*No critical or warning issues.*")
        lines.append("")

    lines.extend([
        "## Tooling",
        "",
        "```bash",
        "cd mandelbulber2",
        "python3 mutations/codegen/formula_audit.py --ci",
        "python3 mutations/codegen/formula_audit.py --markdown mutations/audit/FORMULA_AUDIT.md",
        "```",
        "",
    ])
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("\n".join(lines), encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--ci", action="store_true", help="Exit 1 on critical issues")
    parser.add_argument("--json", metavar="PATH")
    parser.add_argument("--markdown", metavar="PATH")
    args = parser.parse_args()

    result = run_audit()
    print_summary(result)

    if args.json:
        payload = {
            "registered_count": sum(1 for r in result.rows if r.registered),
            "critical": result.critical,
            "warnings": result.warnings,
            "info": result.info,
        }
        Path(args.json).write_text(json.dumps(payload, indent=2), encoding="utf-8")

    md_path = Path(args.markdown) if args.markdown else ROOT / "mutations" / "audit" / "FORMULA_AUDIT.md"
    if args.markdown or not md_path.is_file():
        write_markdown(result, md_path)

    if args.ci and result.critical:
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())

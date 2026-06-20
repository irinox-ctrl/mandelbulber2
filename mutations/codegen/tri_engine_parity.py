#!/usr/bin/env python3
"""
Tri-engine mutation parity report — CPU / compute_fractal.cl / nebula.cl.

Read-only assessment; does not modify source. Use before porting GPU cases.

Usage:
  python3 tri_engine_parity.py
  python3 tri_engine_parity.py --markdown mutations/audit/TRI_ENGINE_PARITY.md
  python3 tri_engine_parity.py --json report.json
  python3 tri_engine_parity.py --ci   # fail on unexpected compute_fractal gaps
"""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))

from mutation_scanner import (  # noqa: E402
    CPU_FILE,
    GPU_FILES,
    extract_switch_cases,
    find_gpu_section,
    normalize_section,
)

MAP_FILE = ROOT / "mutations" / "config" / "subsystem_engine_map.json"
COMPUTE_FRACTAL = GPU_FILES[0]
NEBULA = GPU_FILES[1]


def load_map() -> list[dict]:
    return json.loads(MAP_FILE.read_text(encoding="utf-8"))["subsystems"]


def match_section(prefix: str, sections: dict) -> tuple[str | None, set[int]]:
    for name, cases in sections.items():
        norm = normalize_section(name)
        if norm.startswith(prefix) or norm[:40] == prefix[:40]:
            return name, cases
    return None, set()


def status_row(cpu_cases: set[int], cf_cases: set[int], nb_cases: set[int], nebula_expect: str) -> str:
    cpu_n = len(cpu_cases - {0})
    cf_miss = sorted(cpu_cases - cf_cases - {0})
    if not cpu_cases:
        return "NO_CPU"
    if not cf_cases:
        return "MISSING_COMPUTE_FRACTAL"
    if cf_miss:
        return f"PARTIAL_CF ({len(cf_miss)} missing)"
    if nebula_expect == "partial":
        if not nb_cases:
            return "NEBULA_EXPECTED_GAP"
        nb_miss = sorted(cpu_cases - nb_cases - {0})
        if nb_miss:
            return f"NEBULA_PARTIAL ({len(nb_miss)} missing vs CPU)"
        return "OK_ALL_ENGINES"
    if nebula_expect == "absent":
        if nb_cases:
            return "NEBULA_UNEXPECTED"
        return "OK_FRACTAL_ONLY"
    return "UNKNOWN"


def build_report() -> dict:
    cpu_secs = extract_switch_cases(CPU_FILE.read_text(encoding="utf-8").splitlines())
    cf_secs = extract_switch_cases(COMPUTE_FRACTAL.read_text(encoding="utf-8").splitlines())
    nb_secs = extract_switch_cases(NEBULA.read_text(encoding="utf-8").splitlines())

    rows = []
    cf_actionable = []
    nebula_gaps = []

    for sub in load_map():
        sid = sub["id"]
        prefix = sub["section_prefix"]
        nebula_expect = sub.get("nebula", "absent")

        cpu_name, cpu_cases = match_section(prefix, cpu_secs)
        _, cf_cases = match_section(prefix, cf_secs)
        _, nb_cases = match_section(prefix, nb_secs)

        cf_miss = sorted(cpu_cases - cf_cases - {0}) if cpu_cases else []
        nb_miss = sorted(cpu_cases - nb_cases - {0}) if cpu_cases else []

        row = {
            "id": sid,
            "section": cpu_name or prefix,
            "enabled_param": sub["enabled_param"],
            "cpu_cases": len(cpu_cases - {0}),
            "compute_fractal_cases": len(cf_cases - {0}),
            "nebula_cases": len(nb_cases - {0}),
            "missing_compute_fractal": cf_miss[:20],
            "missing_compute_fractal_count": len(cf_miss),
            "missing_nebula_vs_cpu": nb_miss[:20],
            "missing_nebula_count": len(nb_miss),
            "nebula_expectation": nebula_expect,
            "status": status_row(cpu_cases, cf_cases, nb_cases, nebula_expect),
        }
        rows.append(row)

        if cf_miss and nebula_expect != "absent":
            cf_actionable.append(row)
        if nebula_expect == "absent" and nb_cases:
            nebula_gaps.append(row)
        elif nebula_expect == "partial" and nb_miss:
            nebula_gaps.append(row)

    return {
        "cpu_sections": len(cpu_secs),
        "compute_fractal_sections": len(cf_secs),
        "nebula_sections": len(nb_secs),
        "subsystems": rows,
        "actionable_compute_fractal_gaps": cf_actionable,
        "nebula_notes": nebula_gaps,
    }


def print_summary(report: dict) -> None:
    print("Tri-engine mutation parity")
    print(f"  CPU sections:            {report['cpu_sections']}")
    print(f"  compute_fractal sections: {report['compute_fractal_sections']}")
    print(f"  nebula sections:          {report['nebula_sections']}")
    print()
    print(f"  {'ID':<10} {'CPU':>5} {'CF':>5} {'NEB':>5}  Status")
    print("  " + "-" * 58)
    for row in report["subsystems"]:
        print(
            f"  {row['id']:<10} {row['cpu_cases']:>5} {row['compute_fractal_cases']:>5} "
            f"{row['nebula_cases']:>5}  {row['status']}"
        )

    actionable = report["actionable_compute_fractal_gaps"]
    if actionable:
        print()
        print(f"  Actionable compute_fractal gaps: {len(actionable)}")
        for row in actionable:
            miss = row["missing_compute_fractal"]
            preview = miss[:8]
            suffix = "..." if len(miss) > 8 else ""
            print(f"    {row['id']}: missing cases {preview}{suffix} ({row['missing_compute_fractal_count']} total)")


def write_markdown(report: dict, path: Path) -> None:
    lines = [
        "# Tri-Engine Mutation Parity",
        "",
        f"- CPU sections: `{report['cpu_sections']}`",
        f"- compute_fractal.cl sections: `{report['compute_fractal_sections']}`",
        f"- nebula.cl sections: `{report['nebula_sections']}`",
        "",
        "## Subsystem matrix",
        "",
        "| ID | CPU cases | CF | Nebula | Expectation | Status |",
        "|----|-----------|----|--------|-------------|--------|",
    ]
    for row in report["subsystems"]:
        lines.append(
            f"| `{row['id']}` | {row['cpu_cases']} | {row['compute_fractal_cases']} | "
            f"{row['nebula_cases']} | {row['nebula_expectation']} | {row['status']} |"
        )

    lines.extend(["", "## Actionable compute_fractal gaps", ""])
    actionable = report["actionable_compute_fractal_gaps"]
    if not actionable:
        lines.append("_None — compute_fractal matches CPU for all checked subsystems._")
    else:
        for row in actionable:
            miss = row["missing_compute_fractal"]
            lines.append(
                f"- **{row['id']}** (`{row['section']}`): missing {row['missing_compute_fractal_count']} cases "
                f"— e.g. `{miss[:12]}`"
            )

    lines.extend(["", "## Nebula notes", ""])
    lines.append(
        "Nebula intentionally omits DE-heavy subsystems (jos, pk, mb, wd, sk, ab, noise, orbit, torus, as, sm, blockify, tile). "
        "Only clip, inversion, clamp, jb, md are expected in nebula today."
    )
    unexpected = [r for r in report["subsystems"] if r["status"] == "NEBULA_UNEXPECTED"]
    if unexpected:
        lines.append("")
        lines.append("Unexpected nebula sections:")
        for row in unexpected:
            lines.append(f"- `{row['id']}`: {row['nebula_cases']} cases")

    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--markdown", metavar="PATH")
    parser.add_argument("--json", metavar="PATH")
    parser.add_argument("--ci", action="store_true", help="Fail if compute_fractal has unexpected case gaps")
    args = parser.parse_args()

    report = build_report()
    print_summary(report)

    if args.json:
        Path(args.json).write_text(json.dumps(report, indent=2), encoding="utf-8")
    if args.markdown:
        write_markdown(report, Path(args.markdown))

    if args.ci and report["actionable_compute_fractal_gaps"]:
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())

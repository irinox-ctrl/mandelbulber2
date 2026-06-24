#!/usr/bin/env python3
"""
Unified mutation stability audit runner.

Runs all CI gates in order and prints a summary.

Usage:
  python3 run_all_audits.py
  python3 run_all_audits.py --ci
  python3 run_all_audits.py --markdown mutations/audit/CI_AUDIT_REPORT.md
"""

from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path

CODEGEN = Path(__file__).resolve().parent
ROOT = CODEGEN.parent.parent

AUDITS = [
    # ── Phases 0–6 + 10–12 (existing) ──────────────────────────────────────────
    ("scanner smoke", [sys.executable, str(CODEGEN / "test_scanner_smoke.py")], {}),
    ("scanner --ci-smoke", [sys.executable, str(CODEGEN / "mutation_scanner.py"), "--ci-smoke"], {}),
    ("scanner --validate-ui", [sys.executable, str(CODEGEN / "mutation_scanner.py"), "--validate-ui"], {}),
    ("scanner --ci", [sys.executable, str(CODEGEN / "mutation_scanner.py"), "--ci"], {}),
    ("mutation_audit --ci", [sys.executable, str(CODEGEN / "mutation_audit.py"), "--ci"], {}),
    ("generate_mutation_ui_registry", [sys.executable, str(CODEGEN / "generate_mutation_ui_registry.py")], {}),
    ("ui_audit --ci", [sys.executable, str(CODEGEN / "ui_audit.py"), "--ci"], {}),
    ("combo_audit --ci", [sys.executable, str(CODEGEN / "combo_audit.py"), "--ci"], {}),
    ("julia_audit --ci", [sys.executable, str(CODEGEN / "julia_audit.py"), "--ci"], {}),
    ("tri_engine_parity --ci", [sys.executable, str(CODEGEN / "tri_engine_parity.py"), "--ci"], {}),
    ("formula_audit --ci", [sys.executable, str(CODEGEN / "formula_audit.py"), "--ci"], {}),
    # ── Phase 7: codegen pilot (.mut validation) ────────────────────────────────
    ("codegen validate --all", [sys.executable, str(CODEGEN / "generate_switch.py"),
                                "--all", "--validate-only"], {}),
    # ── Phase 8: param_codegen registry validation ───────────────────────────────
    ("param_codegen --ci", [sys.executable, str(CODEGEN / "param_codegen.py"), "--ci"], {}),
    # ── Phase 9: safety budget ───────────────────────────────────────────────────
    ("safety_budget --ci", [sys.executable, str(CODEGEN / "safety_budget.py"), "--ci"], {}),
]


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--ci", action="store_true", help="Exit 1 if any audit fails")
    parser.add_argument("--markdown", metavar="PATH")
    args = parser.parse_args()

    rows = []
    failed = 0
    print("Mutation stability audit suite")
    print("=" * 50)
    for name, cmd, _ in AUDITS:
        proc = subprocess.run(cmd, cwd=str(ROOT), capture_output=True, text=True)
        ok = proc.returncode == 0
        if not ok:
            failed += 1
        status = "PASS" if ok else "FAIL"
        print(f"  [{status}] {name}")
        if not ok and proc.stdout.strip():
            print(f"         {proc.stdout.strip().splitlines()[-1]}")
        rows.append((name, status, proc.returncode))

    print("=" * 50)
    print(f"  {len(rows) - failed}/{len(rows)} passed")
    if failed:
        print(f"  {failed} failed")

    if args.markdown:
        lines = [
            "# Mutation CI Audit Report",
            "",
            "| Audit | Status |",
            "|-------|--------|",
        ]
        for name, status, _ in rows:
            lines.append(f"| `{name}` | {status} |")
        lines.extend(["", f"**Summary:** {len(rows) - failed}/{len(rows)} passed", ""])
        Path(args.markdown).parent.mkdir(parents=True, exist_ok=True)
        Path(args.markdown).write_text("\n".join(lines), encoding="utf-8")

    if args.ci and failed:
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())

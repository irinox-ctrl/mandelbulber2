#!/usr/bin/env python3
"""Smoke tests for mutation_scanner.py — run: python3 test_scanner_smoke.py"""

import subprocess
import sys
from pathlib import Path

CODEGEN = Path(__file__).resolve().parent
SCANNER = CODEGEN / "mutation_scanner.py"
ROOT = CODEGEN.parent.parent


def test_import():
    proc = subprocess.run(
        [sys.executable, "-c", f"import runpy; runpy.run_path('{SCANNER}')"],
        cwd=str(ROOT),
        capture_output=True,
        text=True,
        check=False,
    )
    assert proc.returncode == 0, proc.stderr


def test_ci_smoke():
    proc = subprocess.run(
        [sys.executable, str(SCANNER), "--ci-smoke"],
        cwd=str(ROOT),
        capture_output=True,
        text=True,
        check=False,
    )
    assert proc.returncode == 0, proc.stdout + proc.stderr


def test_validate_ui():
    proc = subprocess.run(
        [sys.executable, str(SCANNER), "--validate-ui"],
        cwd=str(ROOT),
        capture_output=True,
        text=True,
        check=False,
    )
    assert proc.returncode == 0, proc.stdout + proc.stderr


def test_deterministic_counts():
    proc1 = subprocess.run(
        [sys.executable, "-c",
         "import runpy; m=runpy.run_path('mutations/codegen/mutation_scanner.py'); "
         "r=m['run_scan'](validate_ui=False); print(len(r.issues))"],
        cwd=str(ROOT), capture_output=True, text=True, check=True,
    )
    proc2 = subprocess.run(
        [sys.executable, "-c",
         "import runpy; m=runpy.run_path('mutations/codegen/mutation_scanner.py'); "
         "r=m['run_scan'](validate_ui=False); print(len(r.issues))"],
        cwd=str(ROOT), capture_output=True, text=True, check=True,
    )
    assert proc1.stdout.strip() == proc2.stdout.strip()


def test_stability_audits():
    for script, extra in [
        ("mutation_audit.py", ["--ci"]),
        ("ui_audit.py", ["--ci"]),
        ("combo_audit.py", ["--ci"]),
        ("julia_audit.py", ["--ci"]),
        ("tri_engine_parity.py", ["--ci"]),
        ("formula_audit.py", ["--ci"]),
        ("mutation_scanner.py", ["--ci"]),
    ]:
        proc = subprocess.run(
            [sys.executable, str(CODEGEN / script), *extra],
            cwd=str(ROOT),
            capture_output=True,
            text=True,
            check=False,
        )
        assert proc.returncode == 0, f"{script}: " + proc.stdout + proc.stderr


if __name__ == "__main__":
    test_import()
    test_ci_smoke()
    test_validate_ui()
    test_deterministic_counts()
    test_stability_audits()
    print("mutation_scanner smoke tests: OK")

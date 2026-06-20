#!/usr/bin/env python3
"""
Julia mutation subsystem audit — params, enums, validation hooks.

Read-only checks against initparameters, nine_fractals.cpp validation,
and UI gray-out registry.

Usage:
  python3 julia_audit.py
  python3 julia_audit.py --ci
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent.parent
INIT = ROOT / "src" / "initparameters.cpp"
NINE = ROOT / "src" / "nine_fractals.cpp"
REGISTRY = ROOT / "src" / "mutation_ui_registry_extended_data.cpp"
DOCK = ROOT / "qt" / "dock_mutation_tab.cpp"

JULIA_ENUMS = {
    "mutation_julia_injection": 11,
    "mutation_julia_start": 9,
    "mutation_julia_c_transform": 11,
    "mutation_julia_dynamic": 11,
    "mutation_julia_multi": 11,
}

JULIA_ITER_PARAMS = [
    ("mutation_julia_iter_start", "mutation_julia_iter_stop"),
    ("mutation_julia_ctransform_iter_start", "mutation_julia_ctransform_iter_stop"),
    ("mutation_julia_dynamic_iter_start", "mutation_julia_dynamic_iter_stop"),
    ("mutation_julia_multi_iter_start", "mutation_julia_multi_iter_stop"),
]

JULIA_MOBIUS_PARAMS = [
    "mutation_julia_c_mobius_a",
    "mutation_julia_c_mobius_b",
    "mutation_julia_c_mobius_d",
]


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--ci", action="store_true")
    parser.add_argument("--json", metavar="PATH")
    args = parser.parse_args()

    init = INIT.read_text(encoding="utf-8")
    nf = NINE.read_text(encoding="utf-8")
    dock = DOCK.read_text(encoding="utf-8")

    issues: list[str] = []

    # Registered params
    registered = set(re.findall(r'addParam\("(mutation_julia_\w+)"', init))
    reads = set(re.findall(r'Get<\w+>\("(mutation_julia_\w+)"', nf))

    for param in sorted(registered):
        if param not in reads:
            issues.append(f"registered but not read: {param}")

    # Enum max vs qBound in ValidateMutationParams block
    for param, enum_max in JULIA_ENUMS.items():
        if param not in registered:
            issues.append(f"missing registration: {param}")
            continue
        m = re.search(rf'addParam\("{param}"\s*,\s*i\s*,\s*\d+\s*,\s*\d+\s*,\s*(\d+)', init)
        if not m:
            issues.append(f"cannot parse max for {param}")
            continue
        reg_max = int(m.group(1))
        if reg_max != enum_max:
            issues.append(f"{param}: init max={reg_max}, expected enum max={enum_max}")
        if f"qBound(0, (int)p.{param.replace('mutation_julia_', 'julia')}" not in nf.replace(
            "mutation_julia_", "julia"
        ):
            # softer check: qBound present for julia enums
            pass
        bound_name = {
            "mutation_julia_injection": "juliaInjection",
            "mutation_julia_start": "juliaStart",
            "mutation_julia_c_transform": "juliaCTransform",
            "mutation_julia_dynamic": "juliaDynamic",
            "mutation_julia_multi": "juliaMulti",
        }[param]
        if f"qBound(0, (int)p.{bound_name}," not in nf:
            issues.append(f"missing qBound for {bound_name} in ValidateMutationParams")

    # Iter range swap validation
    if "if (p.juliaIterStart > p.juliaIterStop)" not in nf:
        issues.append("missing juliaIterStart/Stop swap in validation")

    for start, stop in JULIA_ITER_PARAMS:
        if start not in registered or stop not in registered:
            issues.append(f"missing iter window params: {start}/{stop}")

    # Mobius params registered
    for p in JULIA_MOBIUS_PARAMS:
        if p not in registered:
            issues.append(f"missing Mobius param: {p}")

    # NaN guards for key julia doubles
    for field in ("juliaCMul", "juliaCPower", "juliaCRadius", "juliaPulseFreq"):
        if f"std::isnan(p.{field})" not in nf:
            issues.append(f"missing NaN guard: {field}")

    # UI gray-out hooks
    for hook in (
        "comboBox_mutation_julia_injection",
        "comboBox_mutation_julia_start",
        "comboBox_mutation_julia_c_transform",
        "comboBox_mutation_julia_dynamic",
        "comboBox_mutation_julia_multi",
        "ApplyJuliaGrayOut",
    ):
        if hook not in dock and hook not in REGISTRY.read_text(encoding="utf-8"):
            issues.append(f"missing UI/gray-out hook: {hook}")

    report = {
        "julia_params_registered": len(registered),
        "julia_params_read": len(reads & registered),
        "issues": issues,
    }

    print("Julia mutation audit")
    print(f"  registered: {report['julia_params_registered']}")
    print(f"  read:       {report['julia_params_read']}")
    if issues:
        print(f"  issues: {len(issues)}")
        for issue in issues[:15]:
            print(f"    - {issue}")
    else:
        print("  issues: 0")

    if args.json:
        Path(args.json).write_text(json.dumps(report, indent=2), encoding="utf-8")

    if args.ci and issues:
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())

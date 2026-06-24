#!/usr/bin/env python3
"""
Mutation parameter matrix audit — stability gate.

Reports registered/read/UI wiring for mutation params, with enabled-flag alias checks.

Usage:
  python3 mutation_audit.py
  python3 mutation_audit.py --json report.json
  python3 mutation_audit.py --ci
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
ALIAS_FILE = ROOT / "mutations" / "config" / "mutation_enabled_aliases.json"
MUTATION_UI_GLOB = list((ROOT / "qt").glob("mutation_*.ui")) + [
    ROOT / "qt" / "dock_mutation_tab.ui"
]


def load_aliases() -> list[dict]:
    if ALIAS_FILE.is_file():
        return json.loads(ALIAS_FILE.read_text(encoding="utf-8")).get("aliases", [])
    return []


def param_base(name: str) -> str:
    return re.sub(r"_\d+$", "", name)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--json", metavar="PATH")
    parser.add_argument("--ci", action="store_true", help="Exit 1 on alias drift issues")
    args = parser.parse_args()

    init = INIT.read_text(encoding="utf-8")
    nf = NINE.read_text(encoding="utf-8")

    registered = sorted(set(re.findall(r'addParam\("(mutation_\w+)"', init)))
    reads = set(re.findall(r'Get<\w+>\("(mutation_\w+)"', nf))
    reads |= set(re.findall(r'LoadMutationEnabled\(\s*generalPar,\s*i,\s*"(mutation_\w+)"', nf))
    reads |= set(re.findall(r'LoadMutationEnabled\(\s*generalPar,\s*i,\s*"(mutation_\w+)"', nf))
    reads |= set(re.findall(r'"(mutation_\w+)"', nf)) & set(registered)

    ui_widgets: set[str] = set()
    for ui_path in MUTATION_UI_GLOB:
        if ui_path.is_file():
            for name in re.findall(r'name="([^"]+)"', ui_path.read_text(encoding="utf-8")):
                if "mutation" in name and name.startswith(("groupCheck_", "spinbox_", "comboBox_", "checkBox_")):
                    ui_widgets.add(name)

    aliases = load_aliases()
    alias_issues = []
    for row in aliases:
        can = row["canonical"]
        leg = row["legacy"]
        widget = row.get("ui_widget", "")
        if can not in registered:
            alias_issues.append(f"canonical not registered: {can}")
        if leg not in registered:
            alias_issues.append(f"legacy not registered: {leg}")
        if can not in reads and leg not in reads:
            alias_issues.append(f"neither canonical nor legacy read: {can}")
        elif can not in reads and leg in reads:
            alias_issues.append(f"runtime reads legacy only (fixed in code?): {leg}")
        if widget and widget not in ui_widgets:
            alias_issues.append(f"UI widget missing: {widget}")

    reg_not_read = [p for p in registered if p not in reads and not p.endswith("_enabled")]
    enabled_reg_not_read = [p for p in registered if p.endswith("_enabled") and p not in reads]

    report = {
        "registered_count": len(registered),
        "read_count": len(reads & set(registered)),
        "enabled_alias_pairs": len(aliases),
        "alias_issues": alias_issues,
        "registered_not_read_sample": reg_not_read[:20],
        "enabled_registered_not_read": enabled_reg_not_read,
        "ui_widget_count": len(ui_widgets),
    }

    print("Mutation parameter audit")
    print(f"  Registered: {report['registered_count']}")
    print(f"  Read:       {report['read_count']}")
    print(f"  Enabled alias pairs: {report['enabled_alias_pairs']}")
    if alias_issues:
        print(f"  Alias issues: {len(alias_issues)}")
        for issue in alias_issues[:10]:
            print(f"    - {issue}")
    if enabled_reg_not_read:
        print(f"  Enabled registered-not-read (non-alias): {enabled_reg_not_read}")

    if args.json:
        Path(args.json).write_text(json.dumps(report, indent=2), encoding="utf-8")

    if args.ci and alias_issues:
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())

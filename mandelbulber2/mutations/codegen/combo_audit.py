#!/usr/bin/env python3
"""
Combo box vs parameter max audit.

Ensures mutation type combo boxes expose at least as many entries as the
registered parameter max (initparameters.cpp).

Usage:
  python3 combo_audit.py
  python3 combo_audit.py --ci
  python3 combo_audit.py --json report.json
"""

from __future__ import annotations

import argparse
import json
import re
import sys
import xml.etree.ElementTree as ET
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent.parent
INIT = ROOT / "src" / "initparameters.cpp"
UI_FILES = list((ROOT / "qt").glob("mutation_*.ui")) + [ROOT / "qt" / "dock_mutation_tab.ui"]

# comboBox_mutation_foo -> mutation_foo (strip comboBox_ prefix)
TYPE_PARAMS = [
    "mutation_inv_type",
    "mutation_clip_type",
    "mutation_jos_de_type",
    "mutation_pk_de_type",
    "mutation_mb_math_type",
    "mutation_warp_dist_type",
    "mutation_sym_kal_type",
    "mutation_abox_type",
    "mutation_noise_type",
    "mutation_orbit_trap_type",
    "mutation_torus_type",
    "mutation_clamp_type",
    "mutation_jb_type",
    "mutation_md_type",
    "mutation_as_type",
    "mutation_sm_type",
    "mutation_blockify_type",
    "mutation_tile_type",
    "mutation_fold_type",
    "mutation_warp_type",
    "mutation_math_type",
    "mutation_julia_injection",
    "mutation_julia_start",
    "mutation_julia_c_transform",
    "mutation_julia_dynamic",
    "mutation_julia_multi",
]


def param_maxes() -> dict[str, int]:
    init = INIT.read_text(encoding="utf-8")
    maxes: dict[str, int] = {}
    for name in TYPE_PARAMS:
        m = re.search(
            rf'addParam\("{re.escape(name)}"\s*,\s*i\s*,\s*\d+\s*,\s*\d+\s*,\s*(\d+)',
            init,
        )
        if m:
            maxes[name] = int(m.group(1))
    return maxes


def combo_item_counts() -> dict[str, int]:
    counts: dict[str, int] = {}
    for ui_path in UI_FILES:
        if not ui_path.is_file():
            continue
        try:
            root = ET.parse(ui_path).getroot()
        except ET.ParseError:
            continue
        for widget in root.iter("widget"):
            cls = widget.attrib.get("class", "")
            name = widget.attrib.get("name", "")
            if cls != "QComboBox" or not name.startswith("comboBox_mutation_"):
                continue
            param = name.replace("comboBox_", "")
            counts[param] = len(list(widget.findall("item")))
    return counts


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--ci", action="store_true")
    parser.add_argument("--json", metavar="PATH")
    args = parser.parse_args()

    maxes = param_maxes()
    combos = combo_item_counts()
    issues: list[str] = []
    warnings: list[str] = []
    rows = []

    for param, pmax in sorted(maxes.items()):
        items = combos.get(param)
        expected = pmax + 1  # indices 0..max inclusive
        if items is None:
            issues.append(f"no combo widget for {param} (max={pmax})")
            rows.append({"param": param, "max": pmax, "combo_items": None, "ok": False})
            continue
        ok = items >= expected
        row = {"param": param, "max": pmax, "combo_items": items, "ok": ok}
        rows.append(row)
        if not ok:
            warnings.append(
                f"{param}: combo has {items} items, param allows 0..{pmax} ({expected} slots)"
            )

    print("Mutation combo audit")
    print(f"  type params checked: {len(maxes)}")
    print(f"  combos found:        {len(combos)}")
    if issues:
        print(f"  missing combos: {len(issues)}")
        for issue in issues:
            print(f"    - {issue}")
    if warnings:
        print(f"  UI label gaps (known debt): {len(warnings)}")
        for w in warnings[:8]:
            print(f"    - {w}")
        if len(warnings) > 8:
            print(f"    ... and {len(warnings) - 8} more")
    if not issues and not warnings:
        print("  all combos cover param max")

    if args.json:
        Path(args.json).write_text(
            json.dumps({"rows": rows, "issues": issues, "warnings": warnings}, indent=2),
            encoding="utf-8",
        )

    if args.ci and issues:
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())

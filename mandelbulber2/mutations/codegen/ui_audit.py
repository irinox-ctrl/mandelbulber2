#!/usr/bin/env python3
"""
Mutation UI audit — widget ↔ param ↔ gray-out wiring.

Validates:
  - groupCheck_mutation_*_enabled widgets exist in .ui
  - matching mutation_*_enabled params registered in initparameters.cpp
  - dock_mutation_tab.cpp connects group toggles to UpdateMutationGrayOut
  - grayOutGroupSystem pairs match mutation_ui_registry system bindings
  - enabled alias config matches UI widgets

Usage:
  python3 ui_audit.py
  python3 ui_audit.py --markdown mutations/audit/UI_AUDIT.md
  python3 ui_audit.py --ci
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent.parent
INIT = ROOT / "src" / "initparameters.cpp"
DOCK_CPP = ROOT / "qt" / "dock_mutation_tab.cpp"
REGISTRY_DATA = ROOT / "src" / "mutation_ui_registry_data.cpp"
REGISTRY_EXT = ROOT / "src" / "mutation_ui_registry_extended_data.cpp"
ALIAS_FILE = ROOT / "mutations" / "config" / "mutation_enabled_aliases.json"
UI_FILES = list((ROOT / "qt").glob("mutation_*.ui")) + [ROOT / "qt" / "dock_mutation_tab.ui"]


def ui_widget_names() -> set[str]:
    names: set[str] = set()
    for path in UI_FILES:
        if path.is_file():
            names.update(re.findall(r'name="([^"]+)"', path.read_text(encoding="utf-8")))
    return names


def registered_enabled_params() -> set[str]:
    init = INIT.read_text(encoding="utf-8")
    return {p for p in re.findall(r'addParam\("(mutation_\w+)"', init) if p.endswith("_enabled")}


def parse_system_bindings(cpp_text: str) -> list[tuple[str, str, str]]:
    return re.findall(
        r'\{\s*"([^"]+)"\s*,\s*"(groupCheck_mutation_[^"]+)"\s*,\s*"(comboBox_mutation_[^"]+)"\s*\}',
        cpp_text,
    )


def parse_dock_group_connects(cpp: str) -> set[str]:
    block = re.search(r"QList<QGroupBox \*> mutationGroups = \{([^}]+)\}", cpp, re.S)
    if not block:
        return set()
    return set(re.findall(r"groupCheck_mutation_\w+", block.group(1)))


def parse_gray_out_pairs(cpp: str) -> list[tuple[str, str]]:
    return re.findall(
        r"grayOutGroupSystem\(\s*[^,]+->(comboBox_mutation_\w+)\s*,\s*[^,]+->(groupCheck_mutation_\w+)\s*\)",
        cpp,
    )


def groupcheck_to_param(widget: str) -> str:
    return widget.replace("groupCheck_", "")


def parse_registry_spinboxes(cpp_text: str) -> set[str]:
    spins: set[str] = set()
    for m in re.finditer(r'\{\s*"[^"]+"\s*,\s*"(spinbox[^"]*)"', cpp_text):
        spins.add(m.group(1))
    return spins


def parse_registry_labels(cpp_text: str) -> set[str]:
    labels: set[str] = set()
    for m in re.finditer(
        r'\{\s*"[^"]+"\s*,\s*(?:"spinbox[^"]*"\s*,\s*)?"(label[^"]*)"',
        cpp_text,
    ):
        labels.add(m.group(1))
    return labels


def panel_spinboxes(widgets: set[str]) -> set[str]:
    skip = ("section_weight", "boolean_op", "_type")
    out: set[str] = set()
    for w in widgets:
        if not w.startswith("spinbox"):
            continue
        if "mutation" not in w:
            continue
        if any(s in w for s in skip):
            continue
        out.add(w)
    return out


def de_panel_spinboxes(widgets: set[str]) -> set[str]:
    """Spinboxes in DE subsystem panels (not inline dock fold/warp/math/julia)."""
    inline_prefixes = (
        "spinbox_mutation_fold_",
        "spinbox_mutation_warp_",
        "spinbox_mutation_math_",
        "spinbox_mutation_pre_",
        "spinbox_mutation_post_",
        "spinboxInt_mutation_iteration_",
        "spinboxInt_mutation_fold_",
        "spinboxInt_mutation_math_",
        "spinboxInt_mutation_warp_",
        "spinboxInt_mutation_pre_",
        "spinboxInt_mutation_post_",
        "spinbox_mutation_kaleidoscope_",
        "spinbox_mutation_julia_",
        "spinboxd_mutation_julia_",
        "spinboxd3_mutation_julia_",
        "spinboxInt_mutation_julia_",
        "spinbox_mutation_master_",
        "spinbox_mutation_trap_",
        "spinbox_mutation_de_",
        "spinboxInt_mutation_de_",
        "spinbox_mutation_z_mix",
        "spinboxInt_mutation_kaleidoscope_sides",
    )
    spins = panel_spinboxes(widgets)
    return {s for s in spins if not any(s.startswith(p) for p in inline_prefixes)}


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--markdown", metavar="PATH")
    parser.add_argument("--json", metavar="PATH")
    parser.add_argument("--ci", action="store_true")
    args = parser.parse_args()

    widgets = ui_widget_names()
    enabled_registered = registered_enabled_params()
    dock = DOCK_CPP.read_text(encoding="utf-8")
    connected_groups = parse_dock_group_connects(dock)
    gray_pairs = parse_gray_out_pairs(dock)

    issues: list[str] = []

    bindings = parse_system_bindings(REGISTRY_DATA.read_text(encoding="utf-8"))
    bindings += parse_system_bindings(REGISTRY_EXT.read_text(encoding="utf-8"))

    reg_data = REGISTRY_DATA.read_text(encoding="utf-8")
    reg_ext = REGISTRY_EXT.read_text(encoding="utf-8")
    reg_spins = parse_registry_spinboxes(reg_data) | parse_registry_spinboxes(reg_ext)
    reg_labels = parse_registry_labels(reg_data) | parse_registry_labels(reg_ext)

    for spin in sorted(reg_spins):
        if spin not in widgets:
            issues.append(f"registry spinbox not in UI: {spin}")
    for label in sorted(reg_labels):
        if label not in widgets:
            issues.append(f"registry label not in UI: {label}")

    covered = reg_spins | reg_labels
    for spin in sorted(de_panel_spinboxes(widgets)):
        if spin not in covered and "master_weight" not in spin:
            issues.append(f"DE panel spinbox missing registry rule: {spin}")

    aliases = []
    if ALIAS_FILE.is_file():
        aliases = json.loads(ALIAS_FILE.read_text(encoding="utf-8")).get("aliases", [])

    # All groupCheck mutation enabled widgets in UI
    ui_enabled_groups = sorted(w for w in widgets if w.startswith("groupCheck_mutation_") and w.endswith("_enabled"))

    for widget in ui_enabled_groups:
        param = groupcheck_to_param(widget)
        if param not in enabled_registered:
            issues.append(f"UI groupCheck without registered param: {widget} → {param}")
        if widget not in connected_groups and widget != "groupCheck_mutation_enabled":
            issues.append(f"groupCheck not wired to UpdateMutationGrayOut: {widget}")

    for widget in connected_groups:
        if widget not in widgets:
            issues.append(f"dock connects missing UI widget: {widget}")

    # Registry bindings vs grayOutGroupSystem
    registry_pairs = {(combo, group) for _, group, combo in bindings}
    gray_set = set(gray_pairs)
    for combo, group in registry_pairs:
        if (combo, group) not in gray_set:
            issues.append(f"registry binding missing grayOutGroupSystem: {combo} + {group}")
    for combo, group in gray_set:
        if (combo, group) not in registry_pairs:
            issues.append(f"grayOutGroupSystem without registry binding: {combo} + {group}")

    # Alias widgets
    for row in aliases:
        widget = row.get("ui_widget", "")
        can = row["canonical"]
        if widget and widget not in widgets:
            issues.append(f"alias config widget missing in UI: {widget}")
        if can not in enabled_registered:
            issues.append(f"alias canonical param not registered: {can}")

    report = {
        "ui_enabled_group_checks": len(ui_enabled_groups),
        "registered_enabled_params": len(enabled_registered),
        "dock_connected_groups": len(connected_groups),
        "registry_system_bindings": len(bindings),
        "gray_out_pairs": len(gray_pairs),
        "issues": issues,
    }

    print("Mutation UI audit")
    print(f"  groupCheck widgets:     {report['ui_enabled_group_checks']}")
    print(f"  registered *_enabled:   {report['registered_enabled_params']}")
    print(f"  dock grayOut connects:  {report['dock_connected_groups']}")
    print(f"  registry bindings:      {report['registry_system_bindings']}")
    print(f"  grayOutGroupSystem pairs: {report['gray_out_pairs']}")
    if issues:
        print(f"  Issues: {len(issues)}")
        for issue in issues[:15]:
            print(f"    - {issue}")
        if len(issues) > 15:
            print(f"    ... and {len(issues) - 15} more")
    else:
        print("  Issues: 0")

    if args.json:
        Path(args.json).write_text(json.dumps(report, indent=2), encoding="utf-8")

    if args.markdown:
        lines = [
            "# Mutation UI Audit",
            "",
            f"- groupCheck widgets: `{report['ui_enabled_group_checks']}`",
            f"- registered enabled params: `{report['registered_enabled_params']}`",
            f"- dock grayOut connects: `{report['dock_connected_groups']}`",
            f"- registry system bindings: `{report['registry_system_bindings']}`",
            f"- grayOutGroupSystem pairs: `{report['gray_out_pairs']}`",
            "",
            "## Issues",
            "",
        ]
        if issues:
            for issue in issues:
                lines.append(f"- {issue}")
        else:
            lines.append("_No issues found._")
        Path(args.markdown).parent.mkdir(parents=True, exist_ok=True)
        Path(args.markdown).write_text("\n".join(lines) + "\n", encoding="utf-8")

    if args.ci and issues:
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())

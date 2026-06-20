#!/usr/bin/env python3
"""
Mandelbulber Formula UI Validator
=================================
Validates formula .ui files for common mistakes BEFORE runtime.

Usage:
    python3 validate_formula_ui.py <ui_file.ui>
    python3 validate_formula_ui.py --all
    python3 validate_formula_ui.py --all --fix

Exit codes:
    0 = all checks passed
    1 = errors found
    2 = warnings only
"""

import argparse
import glob
import sys
import xml.etree.ElementTree as ET
from pathlib import Path

# Valid widget type prefixes and their requirements
VALID_PREFIXES = {
    "spinboxd": {"widget_class": "MyDoubleSpinBox", "needs": ["decimals"]},
    "spinboxd3": {"widget_class": "MyDoubleSpinBox", "needs": ["decimals"], "is_vector3": True},
    "spinboxd4": {"widget_class": "MyDoubleSpinBox", "needs": ["decimals"], "is_vector4": True},
    "spinbox3": {"widget_class": "MyDoubleSpinBox", "needs": ["decimals"], "is_vector3": True},
    "spinbox4": {"widget_class": "MyDoubleSpinBox", "needs": ["decimals"], "is_vector4": True},
    "spinbox": {"widget_class": ["MySpinBox", "MyDoubleSpinBox"], "needs": []},
    "spinboxd": {"widget_class": "MyDoubleSpinBox", "needs": ["decimals"]},
    "spinboxInt": {"widget_class": ["QSpinBox", "MySpinBox"], "needs": []},
    "line": {"widget_class": ["QFrame", "Line"], "needs": []},
    "checkBox": {"widget_class": "MyCheckBox", "needs": []},
    "comboBox": {"widget_class": "MyComboBox", "needs": []},
    "colorButton": {"widget_class": "MyColorButton", "needs": []},
    "label": {"widget_class": "QLabel", "needs": []},
    "groupBox": {"widget_class": "QGroupBox", "needs": []},
    "groupCheck": {"widget_class": "MyGroupBox", "needs": []},
    "slider": {"widget_class": "QSlider", "needs": [], "partner": "spinbox_"},
    "sliderInt": {"widget_class": "QSlider", "needs": [], "partner": "spinboxInt_"},
    "slider3": {"widget_class": "QSlider", "needs": [], "partner": "spinbox3_"},
    "slider4": {"widget_class": "QSlider", "needs": [], "partner": "spinbox4_"},
    "dial": {"widget_class": "QDial", "needs": [], "partner": "spinboxd_"},
    "dial3": {"widget_class": "QDial", "needs": [], "partner": "spinboxd3_"},
    "dial4": {"widget_class": "QDial", "needs": [], "partner": "spinboxd4_"},
    "logslider": {"widget_class": "QSlider", "needs": [], "partner": "logedit_"},
    "logslidervect3": {"widget_class": "QSlider", "needs": [], "partner": "logvect3_"},
    "logedit": {"widget_class": "QLineEdit", "needs": []},
    "logvect3": {"widget_class": "QLineEdit", "needs": [], "is_vector3": True},
    "edit": {"widget_class": "QLineEdit", "needs": []},
    "vect3": {"widget_class": ["QLineEdit", "MyLineEdit"], "needs": [], "is_vector3": True},
    "vect4": {"widget_class": ["QLineEdit", "MyLineEdit"], "needs": [], "is_vector4": True},
    "keySequenceEdit": {"widget_class": "QKeySequenceEdit", "needs": []},
}

# Widgets that should be declared in <customwidgets>
CUSTOM_WIDGET_CLASSES = {
    "MyDoubleSpinBox", "MySpinBox", "MyCheckBox", "MyComboBox",
    "MyGroupBox", "MyLineEdit", "MyColorButton", "FileSelectWidget",
    "cMaterialSelector"
}


def parse_name(name):
    """Parse widget name into prefix and parameter name."""
    if "_" not in name:
        return None, None
    first_underscore = name.index("_")
    prefix = name[:first_underscore]
    param = name[first_underscore + 1:]
    return prefix, param


def get_widget_properties(widget):
    """Extract properties from a widget XML element."""
    props = {}
    for prop in widget.findall(".//property"):
        pname = prop.get("name")
        # Simple value extraction
        for child in prop:
            tag = child.tag
            text = child.text
            if text:
                try:
                    props[pname] = int(text)
                except ValueError:
                    try:
                        props[pname] = float(text)
                    except ValueError:
                        props[pname] = text
            break
    return props


def validate_ui_file(filepath):
    """Validate a single .ui file. Returns (errors, warnings, info)."""
    errors = []
    warnings = []
    info = []

    filepath = Path(filepath)
    if not filepath.exists():
        errors.append(f"File not found: {filepath}")
        return errors, warnings, info

    # Parse XML
    try:
        tree = ET.parse(filepath)
    except ET.ParseError as e:
        errors.append(f"Invalid XML: {e}")
        return errors, warnings, info

    root = tree.getroot()

    # Check root element
    if root.tag != "ui":
        errors.append(f"Root element is <{root.tag}>, expected <ui>")
        return errors, warnings, info

    # Collect all widgets
    widgets = root.findall(".//widget")
    widget_names = {}
    widget_classes = {}
    for w in widgets:
        name = w.get("name")
        class_name = w.get("class")
        if name and name != "Form":
            widget_names[name] = w
            widget_classes[name] = class_name

    # Check customwidgets declaration
    customwidgets_declared = set()
    for cw in root.findall(".//customwidget/class"):
        customwidgets_declared.add(cw.text)

    for cls in CUSTOM_WIDGET_CLASSES:
        used = cls in widget_classes.values()
        declared = cls in customwidgets_declared
        if used and not declared:
            warnings.append(f"Custom widget '{cls}' is used but not declared in <customwidgets>")
        if declared and not used:
            info.append(f"Custom widget '{cls}' is declared but not used")

    # Validate each named widget
    vector3_bases = {}
    vector4_bases = {}

    for name, w in widget_names.items():
        prefix, param = parse_name(name)
        class_name = widget_classes.get(name, "")
        props = get_widget_properties(w)

        if prefix is None:
            warnings.append(f"Widget '{name}' has no underscore prefix (naming convention)")
            continue

        if prefix not in VALID_PREFIXES:
            warnings.append(f"Unknown prefix '{prefix}' in widget name '{name}'")
            continue

        spec = VALID_PREFIXES[prefix]

        # Check expected widget class
        expected_class = spec.get("widget_class")
        if expected_class:
            expected_list = expected_class if isinstance(expected_class, list) else [expected_class]
            if class_name not in expected_list:
                expected_str = "' or '".join(expected_list)
                warnings.append(
                    f"Widget '{name}' has class '{class_name}' but prefix '{prefix}' "
                    f"expects '{expected_str}'"
                )

        # Check required properties
        for need in spec.get("needs", []):
            if need not in props:
                warnings.append(f"Widget '{name}' missing required property '{need}'")

        # Track vector components
        if spec.get("is_vector3") or spec.get("is_vector4"):
            if "_" in param:
                parts = param.rsplit("_", 1)
                if len(parts) == 2 and parts[1] in ("x", "y", "z", "w"):
                    base = parts[0]
                    axis = parts[1]
                    if spec.get("is_vector3"):
                        vector3_bases.setdefault(base, set()).add(axis)
                    elif spec.get("is_vector4"):
                        vector4_bases.setdefault(base, set()).add(axis)

        # Check partner widget exists (slider/dial → spinbox)
        partner_prefix = spec.get("partner")
        if partner_prefix:
            partner_name = partner_prefix + param
            if partner_name not in widget_names:
                errors.append(
                    f"Widget '{name}' has no partner '{partner_name}'. "
                    f"AutomatedWidgets will fail to connect signals."
                )

    # Skip vector completeness check for widgets whose base ends with digits
    # (e.g., transf_addition_constant_111 is NOT a vector, it's a scalar with numbers in name)
    vector3_bases_clean = {}
    for base, axes in vector3_bases.items():
        if base and not base[-1].isdigit():
            vector3_bases_clean[base] = axes

    vector4_bases_clean = {}
    for base, axes in vector4_bases.items():
        if base and not base[-1].isdigit():
            vector4_bases_clean[base] = axes

    # Check vector completeness
    for base, axes in vector3_bases_clean.items():
        missing = {"x", "y", "z"} - axes
        if missing:
            errors.append(
                f"CVector3 '{base}' is missing axes: {', '.join(sorted(missing))}"
            )

    for base, axes in vector4_bases_clean.items():
        missing = {"x", "y", "z", "w"} - axes
        if missing:
            errors.append(
                f"CVector4 '{base}' is missing axes: {', '.join(sorted(missing))}"
            )

    # Check for duplicate widget names
    name_counts = {}
    for name in widget_names:
        name_counts[name] = name_counts.get(name, 0) + 1
    for name, count in name_counts.items():
        if count > 1:
            errors.append(f"Duplicate widget name: '{name}' appears {count} times")

    # Check layout spacing (Mandelbulber uses tight spacing)
    for layout in root.findall(".//layout"):
        spacing = layout.find("property[@name='spacing']")
        if spacing is not None:
            val = spacing.find(".//number")
            if val is not None and val.text:
                try:
                    if int(val.text) > 5:
                        info.append(
                            f"Layout '{layout.get('name')}' has spacing={val.text}. "
                            f"Mandelbulber typically uses 2."
                        )
                except ValueError:
                    pass

    return errors, warnings, info


def main():
    parser = argparse.ArgumentParser(
        description="Validate Mandelbulber formula .ui files"
    )
    parser.add_argument("files", nargs="*", help=".ui files to validate")
    parser.add_argument(
        "--all", action="store_true",
        help="Validate all formula UI files in deploy/share/mandelbulber2/formula/ui/"
    )
    parser.add_argument(
        "--strict", action="store_true",
        help="Treat warnings as errors"
    )

    args = parser.parse_args()

    if args.all:
        ui_dir = Path(__file__).parent.parent / "deploy" / "share" / "mandelbulber2" / "formula" / "ui"
        files = sorted(ui_dir.glob("*.ui"))
    elif args.files:
        files = [Path(f) for f in args.files]
    else:
        print("Usage: validate_formula_ui.py <file.ui> | --all")
        sys.exit(1)

    total_errors = 0
    total_warnings = 0
    total_files = 0

    for f in files:
        total_files += 1
        errors, warnings, info = validate_ui_file(f)

        if errors or warnings or info:
            print(f"\n{'='*60}")
            print(f"📄 {f.name}")
            print(f"{'='*60}")

            for e in errors:
                print(f"   ❌ ERROR: {e}")
            for w in warnings:
                print(f"   ⚠️  WARNING: {w}")
            for i in info:
                print(f"   ℹ️  INFO: {i}")

            if not errors and not warnings and not info:
                print("   ✅ Passed")

        total_errors += len(errors)
        total_warnings += len(warnings)

    print(f"\n{'='*60}")
    print(f"📊 Summary: {total_files} files checked")
    print(f"   ❌ Errors:   {total_errors}")
    print(f"   ⚠️  Warnings: {total_warnings}")

    if total_errors > 0:
        print(f"\n   Result: FAILED")
        sys.exit(1)
    elif total_warnings > 0 and args.strict:
        print(f"\n   Result: FAILED (strict mode)")
        sys.exit(1)
    elif total_warnings > 0:
        print(f"\n   Result: PASSED with warnings")
        sys.exit(2)
    else:
        print(f"\n   Result: ALL PASSED ✅")
        sys.exit(0)


if __name__ == "__main__":
    main()

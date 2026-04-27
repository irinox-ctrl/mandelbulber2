#!/usr/bin/env python3
"""
Mandelbulber Formula UI Generator
=================================
Generates complete .ui XML files from a simple parameter definition.
No more hand-writing 300+ lines of XML!

Usage:
    python3 generate_formula_ui.py --input formula_params.json --output my_formula.ui
    python3 generate_formula_ui.py --demo

JSON format:
    {
      "formula": {
        "internal_name": "my_formula",
        "display_name": "My Formula"
      },
      "parameters": [
        {
          "name": "scale",
          "type": "double",
          "label": "Scale",
          "default": 2.0,
          "min": 0.001,
          "max": 100.0,
          "step": 0.1,
          "decimals": 6
        }
      ]
    }
"""

import argparse
import json
import sys
from pathlib import Path
from typing import List, Dict, Any


class FormulaUIGenerator:
    """Generates Qt UI XML from parameter definitions."""

    def __init__(self, formula_name: str, display_name: str):
        self.formula_name = formula_name
        self.display_name = display_name

    def generate(self, parameters: List[Dict[str, Any]]) -> str:
        """Generate complete .ui XML."""
        lines = []

        # XML header
        lines.append('<?xml version="1.0" encoding="UTF-8"?>')
        lines.append('<ui version="4.0">')
        lines.append(f' <class>{self.formula_name}</class>')
        lines.append(' <widget class="QWidget" name="Form">')
        lines.append('  <property name="geometry">')
        lines.append('   <rect>')
        lines.append('    <x>0</x>')
        lines.append('    <y>0</y>')
        lines.append('    <width>799</width>')
        height = min(800, 100 + len(parameters) * 45)
        lines.append(f'    <height>{height}</height>')
        lines.append('   </rect>')
        lines.append('  </property>')
        lines.append('  <property name="windowTitle">')
        lines.append(f'   <string notr="true">{self.formula_name}</string>')
        lines.append('  </property>')

        # Main layout
        lines.append('  <layout class="QVBoxLayout" name="verticalLayout">')
        for margin in ['left', 'top', 'right', 'bottom']:
            lines.append(f'   <property name="{margin}Margin">')
            lines.append('    <number>2</number>')
            lines.append('   </property>')
        lines.append('   <property name="spacing">')
        lines.append('    <number>2</number>')
        lines.append('   </property>')

        # Title
        lines.append('   <item>')
        lines.append('    <widget class="QLabel" name="label_title">')
        lines.append('     <property name="text">')
        lines.append(f'      <string notr="true">{self.display_name}</string>')
        lines.append('     </property>')
        lines.append('    </widget>')
        lines.append('   </item>')

        # Parameter grid
        lines.append('   <item>')
        lines.append('    <layout class="QGridLayout" name="gridLayout_params">')
        lines.append('     <property name="spacing">')
        lines.append('      <number>2</number>')
        lines.append('     </property>')

        for row, param in enumerate(parameters):
            lines.extend(self._generate_parameter(param, row))

        lines.append('    </layout>')
        lines.append('   </item>')

        # Spacer
        lines.append('   <item>')
        lines.append('    <spacer name="verticalSpacer">')
        lines.append('     <property name="orientation">')
        lines.append('      <enum>Qt::Vertical</enum>')
        lines.append('     </property>')
        lines.append('     <property name="sizeHint" stdset="0">')
        lines.append('      <size>')
        lines.append('       <width>20</width>')
        lines.append('       <height>40</height>')
        lines.append('      </size>')
        lines.append('     </property>')
        lines.append('    </spacer>')
        lines.append('   </item>')

        lines.append('  </layout>')
        lines.append(' </widget>')

        # Custom widgets
        lines.append(' <customwidgets>')
        for cls, extends, header in [
            ("MyDoubleSpinBox", "QDoubleSpinBox", "my_double_spin_box.h"),
            ("MySpinBox", "QSpinBox", "my_spin_box.h"),
            ("MyCheckBox", "QCheckBox", "my_check_box.h"),
            ("MyComboBox", "QComboBox", "my_combo_box.h"),
            ("MyGroupBox", "QGroupBox", "my_group_box.h"),
            ("MyColorButton", "QPushButton", "my_color_button.h"),
        ]:
            lines.append('  <customwidget>')
            lines.append(f'   <class>{cls}</class>')
            lines.append(f'   <extends>{extends}</extends>')
            lines.append(f'   <header>{header}</header>')
            lines.append('  </customwidget>')
        lines.append(' </customwidgets>')

        lines.append(' <resources/>')
        lines.append(' <connections/>')
        lines.append('</ui>')

        return '\n'.join(lines)

    def _generate_parameter(self, param: Dict[str, Any], row: int) -> List[str]:
        """Generate widgets for a single parameter."""
        ptype = param.get("type", "double")
        pname = param["name"]
        label = param.get("label", pname)

        generators = {
            "double": self._generate_double,
            "cvector3": self._generate_cvector3,
            "cvector4": self._generate_cvector4,
            "int": self._generate_int,
            "bool": self._generate_bool,
            "enum": self._generate_enum,
            "color": self._generate_color,
        }

        gen = generators.get(ptype)
        if not gen:
            print(f"⚠️  Unknown parameter type '{ptype}', using 'double'", file=sys.stderr)
            gen = self._generate_double

        return gen(param, row)

    def _generate_label(self, label: str, row: int, suffix: str = "") -> List[str]:
        """Generate a QLabel for a parameter."""
        name = f"label_{self.formula_name}_{label.lower().replace(' ', '_')}{suffix}"
        return [
            f'     <item row="{row}" column="0">',
            f'      <widget class="QLabel" name="{name}">',
            '       <property name="text">',
            f'        <string notr="true">{label}:</string>',
            '       </property>',
            '      </widget>',
            '     </item>',
        ]

    def _generate_double(self, param: Dict[str, Any], row: int) -> List[str]:
        """Generate a double spinbox parameter."""
        pname = param["name"]
        label = param.get("label", pname)
        widget_name = f"spinboxd_{self.formula_name}_{pname}"

        lines = self._generate_label(label, row)
        lines.append(f'     <item row="{row}" column="1">')
        lines.append(f'      <widget class="MyDoubleSpinBox" name="{widget_name}">')

        props = {
            "decimals": param.get("decimals", 6),
        }
        if "min" in param:
            props["minimum"] = param["min"]
        if "max" in param:
            props["maximum"] = param["max"]
        if "step" in param:
            props["singleStep"] = param["step"]
        if "default" in param:
            props["value"] = param["default"]

        for prop, val in props.items():
            if isinstance(val, int):
                lines.append(f'       <property name="{prop}">')
                lines.append(f'        <number>{val}</number>')
                lines.append('       </property>')
            else:
                lines.append(f'       <property name="{prop}">')
                lines.append(f'        <double>{val}</double>')
                lines.append('       </property>')

        lines.append('      </widget>')
        lines.append('     </item>')
        return lines

    def _generate_cvector3(self, param: Dict[str, Any], row: int) -> List[str]:
        """Generate 3 double spinboxes for CVector3."""
        pname = param["name"]
        label = param.get("label", pname)
        default = param.get("default", [0.0, 0.0, 0.0])

        lines = self._generate_label(label, row)
        lines.append(f'     <item row="{row}" column="1">')
        lines.append(f'      <layout class="QHBoxLayout" name="hLayout_{pname}">')

        for i, axis in enumerate(["x", "y", "z"]):
            widget_name = f"spinboxd3_{self.formula_name}_{pname}_{axis}"
            lines.append('       <item>')
            lines.append(f'        <widget class="MyDoubleSpinBox" name="{widget_name}">')
            lines.append('         <property name="sizePolicy">')
            lines.append('          <sizepolicy hsizetype="Minimum" vsizetype="Maximum">')
            lines.append('           <horstretch>0</horstretch>')
            lines.append('           <verstretch>0</verstretch>')
            lines.append('          </sizepolicy>')
            lines.append('         </property>')
            lines.append(f'         <property name="decimals">')
            lines.append(f'          <number>{param.get("decimals", 6)}</number>')
            lines.append('         </property>')

            if "min" in param:
                lines.append(f'         <property name="minimum">')
                lines.append(f'          <double>{param["min"]}</double>')
                lines.append('         </property>')
            if "max" in param:
                lines.append(f'         <property name="maximum">')
                lines.append(f'          <double>{param["max"]}</double>')
                lines.append('         </property>')
            if "step" in param:
                lines.append(f'         <property name="singleStep">')
                lines.append(f'          <double>{param["step"]}</double>')
                lines.append('         </property>')
            if default and i < len(default):
                lines.append(f'         <property name="value">')
                lines.append(f'          <double>{default[i]}</double>')
                lines.append('         </property>')

            lines.append('        </widget>')
            lines.append('       </item>')

        lines.append('      </layout>')
        lines.append('     </item>')
        return lines

    def _generate_cvector4(self, param: Dict[str, Any], row: int) -> List[str]:
        """Generate 4 double spinboxes for CVector4."""
        pname = param["name"]
        label = param.get("label", pname)
        default = param.get("default", [0.0, 0.0, 0.0, 1.0])

        lines = self._generate_label(label, row)
        lines.append(f'     <item row="{row}" column="1">')
        lines.append(f'      <layout class="QHBoxLayout" name="hLayout_{pname}">')

        for i, axis in enumerate(["x", "y", "z", "w"]):
            widget_name = f"spinboxd4_{self.formula_name}_{pname}_{axis}"
            lines.append('       <item>')
            lines.append(f'        <widget class="MyDoubleSpinBox" name="{widget_name}">')
            lines.append(f'         <property name="decimals">')
            lines.append(f'          <number>{param.get("decimals", 6)}</number>')
            lines.append('         </property>')
            if "min" in param:
                lines.append(f'         <property name="minimum">')
                lines.append(f'          <double>{param["min"]}</double>')
                lines.append('         </property>')
            if "max" in param:
                lines.append(f'         <property name="maximum">')
                lines.append(f'          <double>{param["max"]}</double>')
                lines.append('         </property>')
            if default and i < len(default):
                lines.append(f'         <property name="value">')
                lines.append(f'          <double>{default[i]}</double>')
                lines.append('         </property>')
            lines.append('        </widget>')
            lines.append('       </item>')

        lines.append('      </layout>')
        lines.append('     </item>')
        return lines

    def _generate_int(self, param: Dict[str, Any], row: int) -> List[str]:
        """Generate an int spinbox parameter."""
        pname = param["name"]
        label = param.get("label", pname)
        widget_name = f"spinbox_{self.formula_name}_{pname}"

        lines = self._generate_label(label, row)
        lines.append(f'     <item row="{row}" column="1">')
        lines.append(f'      <widget class="MySpinBox" name="{widget_name}">')

        if "min" in param:
            lines.append(f'       <property name="minimum">')
            lines.append(f'        <number>{int(param["min"])}</number>')
            lines.append('       </property>')
        if "max" in param:
            lines.append(f'       <property name="maximum">')
            lines.append(f'        <number>{int(param["max"])}</number>')
            lines.append('       </property>')
        if "default" in param:
            lines.append(f'       <property name="value">')
            lines.append(f'        <number>{int(param["default"])}</number>')
            lines.append('       </property>')

        lines.append('      </widget>')
        lines.append('     </item>')
        return lines

    def _generate_bool(self, param: Dict[str, Any], row: int) -> List[str]:
        """Generate a checkbox parameter."""
        pname = param["name"]
        label = param.get("label", pname)
        widget_name = f"checkBox_{self.formula_name}_{pname}"

        lines = []
        lines.append(f'     <item row="{row}" column="0" colspan="2">')
        lines.append(f'      <widget class="MyCheckBox" name="{widget_name}">')
        lines.append('       <property name="text">')
        lines.append(f'        <string notr="true">{label}</string>')
        lines.append('       </property>')
        if param.get("default", False):
            lines.append('       <property name="checked">')
            lines.append('        <bool>true</bool>')
            lines.append('       </property>')
        lines.append('      </widget>')
        lines.append('     </item>')
        return lines

    def _generate_enum(self, param: Dict[str, Any], row: int) -> List[str]:
        """Generate a combobox parameter."""
        pname = param["name"]
        label = param.get("label", pname)
        widget_name = f"comboBox_{self.formula_name}_{pname}"
        options = param.get("options", [])

        lines = self._generate_label(label, row)
        lines.append(f'     <item row="{row}" column="1">')
        lines.append(f'      <widget class="MyComboBox" name="{widget_name}">')

        for opt in options:
            lines.append('       <item>')
            lines.append('        <property name="text">')
            lines.append(f'         <string>{opt}</string>')
            lines.append('        </property>')
            lines.append('       </item>')

        lines.append('      </widget>')
        lines.append('     </item>')
        return lines

    def _generate_color(self, param: Dict[str, Any], row: int) -> List[str]:
        """Generate a color button parameter."""
        pname = param["name"]
        label = param.get("label", pname)
        widget_name = f"colorButton_{self.formula_name}_{pname}"

        lines = self._generate_label(label, row)
        lines.append(f'     <item row="{row}" column="1">')
        lines.append(f'      <widget class="MyColorButton" name="{widget_name}">')
        lines.append('       <property name="text">')
        lines.append('        <string>Color</string>')
        lines.append('       </property>')
        lines.append('      </widget>')
        lines.append('     </item>')
        return lines


def demo():
    """Run a demo generation."""
    print("=" * 60)
    print("Mandelbulber Formula UI Generator — DEMO")
    print("=" * 60)

    generator = FormulaUIGenerator("transf_rotation_v2", "T>Rotation V2")

    params = [
        {
            "name": "rotation",
            "type": "cvector3",
            "label": "Rotation (alpha, beta, gamma)",
            "default": [0.0, 0.0, 0.0],
            "min": -36000.0,
            "max": 36000.0,
            "step": 1.0,
            "decimals": 6,
        },
        {
            "name": "enabled",
            "type": "bool",
            "label": "Enable rotation",
            "default": True,
        },
        {
            "name": "start_iteration",
            "type": "int",
            "label": "Start at iteration",
            "default": 0,
            "min": 0,
            "max": 250,
        },
        {
            "name": "mode",
            "type": "enum",
            "label": "Mode",
            "options": ["Linear", "Spherical", "Cylindrical"],
        },
        {
            "name": "color",
            "type": "color",
            "label": "Highlight color",
        },
    ]

    xml = generator.generate(params)

    output = Path(__file__).parent / "demo_output.ui"
    output.write_text(xml, encoding="utf-8")

    print(f"\n✅ Generated: {output}")
    print(f"   Lines: {len(xml.splitlines())}")
    print(f"   Parameters: {len(params)}")
    print(f"\n   Types used:")
    for p in params:
        print(f"     - {p['name']}: {p['type']}")

    # Validate it
    print(f"\n   Running validation...")
    import subprocess
    result = subprocess.run(
        [sys.executable, str(Path(__file__).parent / "validate_formula_ui.py"), str(output)],
        capture_output=True, text=True
    )
    print(result.stdout)


def main():
    parser = argparse.ArgumentParser(description="Generate Mandelbulber formula .ui files")
    parser.add_argument("--input", "-i", help="JSON parameter definition file")
    parser.add_argument("--output", "-o", help="Output .ui file")
    parser.add_argument("--demo", action="store_true", help="Run demo")

    args = parser.parse_args()

    if args.demo:
        demo()
        return

    if not args.input or not args.output:
        print("Usage: generate_formula_ui.py --input params.json --output formula.ui")
        print("       generate_formula_ui.py --demo")
        sys.exit(1)

    # Load JSON
    with open(args.input, "r", encoding="utf-8") as f:
        spec = json.load(f)

    formula = spec.get("formula", {})
    params = spec.get("parameters", [])

    generator = FormulaUIGenerator(
        formula.get("internal_name", "unknown"),
        formula.get("display_name", "Unknown")
    )

    xml = generator.generate(params)

    output = Path(args.output)
    output.write_text(xml, encoding="utf-8")

    print(f"✅ Generated: {output}")
    print(f"   Lines: {len(xml.splitlines())}")
    print(f"   Parameters: {len(params)}")

    # Auto-validate
    print(f"\n   Validating...")
    import subprocess
    result = subprocess.run(
        [sys.executable, str(Path(__file__).parent / "validate_formula_ui.py"), str(output)],
        capture_output=True, text=True
    )
    print(result.stdout)


if __name__ == "__main__":
    main()

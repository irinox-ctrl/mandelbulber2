#!/usr/bin/env python3
"""
UI FILE GENERATOR
=================
Genereer Qt UI files (.ui XML) automatisch van parameter definities!

PROBLEEM:
- Elke nieuwe formule = 260+ regels XML handmatig editen
- Repetitieve spinbox definities voor x/y/z parameters
- Copy-paste errors
- Tijdsintensief: 1-2 uur per formule

OPLOSSING:
- Definieer parameters in simpel formaat
- Tool genereert complete .ui XML
- Support voor: CVector3, CVector4, double, int, bool, enum
- Consistent naming: spinboxd3_formula_name_parameter_x

TIJDSBESPARING: 1-2 uur per formule!

Author: Claude + Joeri
Version: 1.0
Date: 2026-04-19
"""

import sys
from pathlib import Path
from typing import List, Dict, Optional, Tuple
from dataclasses import dataclass
from enum import Enum


class ParamType(Enum):
    """Parameter types"""
    CVECTOR3 = "CVector3"
    CVECTOR4 = "CVector4"
    DOUBLE = "double"
    INT = "int"
    BOOL = "bool"
    ENUM = "enum"
    COLOR = "color"


@dataclass
class Parameter:
    """Parameter definition"""
    name: str
    type: ParamType
    display_label: str
    default: any
    min_val: float = None
    max_val: float = None
    step: float = None
    decimals: int = 6
    enum_options: List[str] = None
    tooltip: str = ""


class UIGenerator:
    """Generate Qt UI XML from parameter definitions"""

    def __init__(self, formula_name: str, display_name: str):
        self.formula_name = formula_name
        self.display_name = display_name
        self.widget_counter = 0

    def generate(self, parameters: List[Parameter], output_file: Path) -> bool:
        """
        Generate complete .ui XML file

        Args:
            parameters: List of parameter definitions
            output_file: Where to save .ui file

        Returns:
            True if successful
        """

        print(f"🎨 Generating UI for: {self.display_name}")
        print(f"Parameters: {len(parameters)}")
        print(f"Output: {output_file}")
        print()

        xml = self._generate_xml(parameters)

        try:
            with open(output_file, 'w', encoding='utf-8') as f:
                f.write(xml)

            print(f"✅ Generated: {output_file}")
            print(f"   Lines: {len(xml.splitlines())}")
            return True

        except Exception as e:
            print(f"❌ Error writing file: {e}")
            return False

    def _generate_xml(self, parameters: List[Parameter]) -> str:
        """Generate complete XML"""

        xml = []

        # Header
        xml.append('<?xml version="1.0" encoding="UTF-8"?>')
        xml.append('<ui version="4.0">')
        xml.append(f' <class>{self.formula_name}</class>')
        xml.append(' <widget class="QWidget" name="Form">')
        xml.append('  <property name="geometry">')
        xml.append('   <rect>')
        xml.append('    <x>0</x>')
        xml.append('    <y>0</y>')
        xml.append('    <width>799</width>')
        xml.append(f'    <height>{min(800, 100 + len(parameters) * 40)}</height>')
        xml.append('   </rect>')
        xml.append('  </property>')
        xml.append('  <property name="windowTitle">')
        xml.append(f'   <string notr="true">{self.formula_name}</string>')
        xml.append('  </property>')

        # Main layout
        xml.append('  <layout class="QVBoxLayout" name="verticalLayout">')
        xml.append('   <property name="spacing">')
        xml.append('    <number>2</number>')
        xml.append('   </property>')
        xml.append('   <property name="leftMargin">')
        xml.append('    <number>2</number>')
        xml.append('   </property>')
        xml.append('   <property name="topMargin">')
        xml.append('    <number>2</number>')
        xml.append('   </property>')
        xml.append('   <property name="rightMargin">')
        xml.append('    <number>2</number>')
        xml.append('   </property>')
        xml.append('   <property name="bottomMargin">')
        xml.append('    <number>2</number>')
        xml.append('   </property>')

        # Title label
        xml.append('   <item>')
        xml.append('    <widget class="QLabel" name="label_title">')
        xml.append('     <property name="text">')
        xml.append(f'      <string notr="true">{self.display_name}</string>')
        xml.append('     </property>')
        xml.append('    </widget>')
        xml.append('   </item>')

        # Parameters grid
        xml.append('   <item>')
        xml.append('    <layout class="QGridLayout" name="gridLayout_params">')
        xml.append('     <property name="spacing">')
        xml.append('      <number>2</number>')
        xml.append('     </property>')

        row = 0
        for param in parameters:
            xml.extend(self._generate_parameter_widgets(param, row))
            row += 1

        xml.append('    </layout>')
        xml.append('   </item>')

        # Spacer
        xml.append('   <item>')
        xml.append('    <spacer name="verticalSpacer">')
        xml.append('     <property name="orientation">')
        xml.append('      <enum>Qt::Vertical</enum>')
        xml.append('     </property>')
        xml.append('     <property name="sizeHint" stdset="0">')
        xml.append('      <size>')
        xml.append('       <width>20</width>')
        xml.append('       <height>40</height>')
        xml.append('      </size>')
        xml.append('     </property>')
        xml.append('    </spacer>')
        xml.append('   </item>')

        # Close layout and widget
        xml.append('  </layout>')
        xml.append(' </widget>')

        # Custom widgets
        xml.append(' <customwidgets>')
        xml.append('  <customwidget>')
        xml.append('   <class>MyDoubleSpinBox</class>')
        xml.append('   <extends>QDoubleSpinBox</extends>')
        xml.append('   <header>my_double_spin_box.h</header>')
        xml.append('  </customwidget>')
        xml.append('  <customwidget>')
        xml.append('   <class>MySpinBox</class>')
        xml.append('   <extends>QSpinBox</extends>')
        xml.append('   <header>my_spin_box.h</header>')
        xml.append('  </customwidget>')
        xml.append('  <customwidget>')
        xml.append('   <class>MyCheckBox</class>')
        xml.append('   <extends>QCheckBox</extends>')
        xml.append('   <header>my_check_box.h</header>')
        xml.append('  </customwidget>')
        xml.append('  <customwidget>')
        xml.append('   <class>MyGroupBox</class>')
        xml.append('   <extends>QGroupBox</extends>')
        xml.append('   <header>my_group_box.h</header>')
        xml.append('  </customwidget>')
        xml.append('  <customwidget>')
        xml.append('   <class>MyComboBox</class>')
        xml.append('   <extends>QComboBox</extends>')
        xml.append('   <header>my_combo_box.h</header>')
        xml.append('  </customwidget>')
        xml.append('  <customwidget>')
        xml.append('   <class>MyColorButton</class>')
        xml.append('   <extends>QPushButton</extends>')
        xml.append('   <header>my_color_button.h</header>')
        xml.append('  </customwidget>')
        xml.append(' </customwidgets>')
        xml.append(' <resources/>')
        xml.append(' <connections/>')
        xml.append('</ui>')

        return '\n'.join(xml)

    def _generate_parameter_widgets(self, param: Parameter, row: int) -> List[str]:
        """Generate widgets for a parameter"""

        xml = []

        if param.type == ParamType.CVECTOR3:
            xml.extend(self._generate_cvector3(param, row))
        elif param.type == ParamType.CVECTOR4:
            xml.extend(self._generate_cvector4(param, row))
        elif param.type == ParamType.DOUBLE:
            xml.extend(self._generate_double(param, row))
        elif param.type == ParamType.INT:
            xml.extend(self._generate_int(param, row))
        elif param.type == ParamType.BOOL:
            xml.extend(self._generate_bool(param, row))
        elif param.type == ParamType.ENUM:
            xml.extend(self._generate_enum(param, row))
        elif param.type == ParamType.COLOR:
            xml.extend(self._generate_color(param, row))

        return xml

    def _generate_cvector3(self, param: Parameter, row: int) -> List[str]:
        """Generate CVector3 widgets (3 spinboxes for x,y,z)"""

        xml = []

        # Label
        xml.append(f'     <item row="{row}" column="0">')
        xml.append(f'      <widget class="QLabel" name="label_{param.name}">')
        xml.append('       <property name="text">')
        xml.append(f'        <string notr="true">{param.display_label}</string>')
        xml.append('       </property>')
        if param.tooltip:
            xml.append('       <property name="toolTip">')
            xml.append(f'        <string>{param.tooltip}</string>')
            xml.append('       </property>')
        xml.append('      </widget>')
        xml.append('     </item>')

        # X, Y, Z spinboxes in horizontal layout
        xml.append(f'     <item row="{row}" column="1">')
        xml.append('      <layout class="QHBoxLayout" name="hLayout_' + param.name + '">')

        for axis, label in [('x', 'X'), ('y', 'Y'), ('z', 'Z')]:
            widget_name = f"spinboxd3_{self.formula_name}_{param.name}_{axis}"

            xml.append('       <item>')
            xml.append(f'        <widget class="MyDoubleSpinBox" name="{widget_name}">')
            xml.append('         <property name="sizePolicy">')
            xml.append('          <sizepolicy hsizetype="Minimum" vsizetype="Maximum">')
            xml.append('           <horstretch>0</horstretch>')
            xml.append('           <verstretch>0</verstretch>')
            xml.append('          </sizepolicy>')
            xml.append('         </property>')

            if param.tooltip:
                xml.append('         <property name="toolTip">')
                xml.append(f'          <string>{param.tooltip} ({label})</string>')
                xml.append('         </property>')

            xml.append('         <property name="prefix">')
            xml.append('          <string/>')
            xml.append('         </property>')
            xml.append('         <property name="suffix">')
            xml.append('          <string/>')
            xml.append('         </property>')
            xml.append('         <property name="decimals">')
            xml.append(f'          <number>{param.decimals}</number>')
            xml.append('         </property>')

            if param.min_val is not None:
                xml.append('         <property name="minimum">')
                xml.append(f'          <double>{param.min_val}</double>')
                xml.append('         </property>')

            if param.max_val is not None:
                xml.append('         <property name="maximum">')
                xml.append(f'          <double>{param.max_val}</double>')
                xml.append('         </property>')

            if param.step is not None:
                xml.append('         <property name="singleStep">')
                xml.append(f'          <double>{param.step}</double>')
                xml.append('         </property>')

            if param.default:
                default_val = param.default[['x','y','z'].index(axis)] if isinstance(param.default, (list, tuple)) else 0.0
                xml.append('         <property name="value">')
                xml.append(f'          <double>{default_val}</double>')
                xml.append('         </property>')

            xml.append('        </widget>')
            xml.append('       </item>')

        xml.append('      </layout>')
        xml.append('     </item>')

        return xml

    def _generate_cvector4(self, param: Parameter, row: int) -> List[str]:
        """Generate CVector4 widgets (4 spinboxes)"""

        xml = []

        # Similar to CVector3 but with w component
        xml.append(f'     <item row="{row}" column="0">')
        xml.append(f'      <widget class="QLabel" name="label_{param.name}">')
        xml.append('       <property name="text">')
        xml.append(f'        <string notr="true">{param.display_label}</string>')
        xml.append('       </property>')
        xml.append('      </widget>')
        xml.append('     </item>')

        xml.append(f'     <item row="{row}" column="1">')
        xml.append('      <layout class="QHBoxLayout" name="hLayout_' + param.name + '">')

        for axis in ['x', 'y', 'z', 'w']:
            widget_name = f"spinboxd4_{self.formula_name}_{param.name}_{axis}"

            xml.append('       <item>')
            xml.append(f'        <widget class="MyDoubleSpinBox" name="{widget_name}">')
            xml.append('         <property name="decimals">')
            xml.append(f'          <number>{param.decimals}</number>')
            xml.append('         </property>')

            if param.min_val is not None:
                xml.append('         <property name="minimum">')
                xml.append(f'          <double>{param.min_val}</double>')
                xml.append('         </property>')

            if param.max_val is not None:
                xml.append('         <property name="maximum">')
                xml.append(f'          <double>{param.max_val}</double>')
                xml.append('         </property>')

            xml.append('        </widget>')
            xml.append('       </item>')

        xml.append('      </layout>')
        xml.append('     </item>')

        return xml

    def _generate_double(self, param: Parameter, row: int) -> List[str]:
        """Generate double spinbox"""

        xml = []
        widget_name = f"spinboxd_{self.formula_name}_{param.name}"

        xml.append(f'     <item row="{row}" column="0">')
        xml.append(f'      <widget class="QLabel" name="label_{param.name}">')
        xml.append('       <property name="text">')
        xml.append(f'        <string notr="true">{param.display_label}</string>')
        xml.append('       </property>')
        xml.append('      </widget>')
        xml.append('     </item>')

        xml.append(f'     <item row="{row}" column="1">')
        xml.append(f'      <widget class="MyDoubleSpinBox" name="{widget_name}">')
        xml.append('       <property name="decimals">')
        xml.append(f'        <number>{param.decimals}</number>')
        xml.append('       </property>')

        if param.min_val is not None:
            xml.append('       <property name="minimum">')
            xml.append(f'        <double>{param.min_val}</double>')
            xml.append('       </property>')

        if param.max_val is not None:
            xml.append('       <property name="maximum">')
            xml.append(f'        <double>{param.max_val}</double>')
            xml.append('       </property>')

        if param.step is not None:
            xml.append('       <property name="singleStep">')
            xml.append(f'        <double>{param.step}</double>')
            xml.append('       </property>')

        if param.default is not None:
            xml.append('       <property name="value">')
            xml.append(f'        <double>{param.default}</double>')
            xml.append('       </property>')

        xml.append('      </widget>')
        xml.append('     </item>')

        return xml

    def _generate_int(self, param: Parameter, row: int) -> List[str]:
        """Generate int spinbox"""

        xml = []
        widget_name = f"spinbox_{self.formula_name}_{param.name}"

        xml.append(f'     <item row="{row}" column="0">')
        xml.append(f'      <widget class="QLabel" name="label_{param.name}">')
        xml.append('       <property name="text">')
        xml.append(f'        <string notr="true">{param.display_label}</string>')
        xml.append('       </property>')
        xml.append('      </widget>')
        xml.append('     </item>')

        xml.append(f'     <item row="{row}" column="1">')
        xml.append(f'      <widget class="MySpinBox" name="{widget_name}">')

        if param.min_val is not None:
            xml.append('       <property name="minimum">')
            xml.append(f'        <number>{int(param.min_val)}</number>')
            xml.append('       </property>')

        if param.max_val is not None:
            xml.append('       <property name="maximum">')
            xml.append(f'        <number>{int(param.max_val)}</number>')
            xml.append('       </property>')

        if param.default is not None:
            xml.append('       <property name="value">')
            xml.append(f'        <number>{int(param.default)}</number>')
            xml.append('       </property>')

        xml.append('      </widget>')
        xml.append('     </item>')

        return xml

    def _generate_bool(self, param: Parameter, row: int) -> List[str]:
        """Generate checkbox"""

        xml = []
        widget_name = f"checkBox_{self.formula_name}_{param.name}"

        xml.append(f'     <item row="{row}" column="0" colspan="2">')
        xml.append(f'      <widget class="MyCheckBox" name="{widget_name}">')
        xml.append('       <property name="text">')
        xml.append(f'        <string notr="true">{param.display_label}</string>')
        xml.append('       </property>')

        if param.default:
            xml.append('       <property name="checked">')
            xml.append(f'        <bool>{str(param.default).lower()}</bool>')
            xml.append('       </property>')

        xml.append('      </widget>')
        xml.append('     </item>')

        return xml

    def _generate_enum(self, param: Parameter, row: int) -> List[str]:
        """Generate combobox for enum"""

        xml = []
        widget_name = f"comboBox_{self.formula_name}_{param.name}"

        xml.append(f'     <item row="{row}" column="0">')
        xml.append(f'      <widget class="QLabel" name="label_{param.name}">')
        xml.append('       <property name="text">')
        xml.append(f'        <string notr="true">{param.display_label}</string>')
        xml.append('       </property>')
        xml.append('      </widget>')
        xml.append('     </item>')

        xml.append(f'     <item row="{row}" column="1">')
        xml.append(f'      <widget class="MyComboBox" name="{widget_name}">')

        if param.enum_options:
            for option in param.enum_options:
                xml.append('       <item>')
                xml.append('        <property name="text">')
                xml.append(f'         <string>{option}</string>')
                xml.append('        </property>')
                xml.append('       </item>')

        xml.append('      </widget>')
        xml.append('     </item>')

        return xml

    def _generate_color(self, param: Parameter, row: int) -> List[str]:
        """Generate color button"""

        xml = []
        widget_name = f"colorButton_{self.formula_name}_{param.name}"

        xml.append(f'     <item row="{row}" column="0">')
        xml.append(f'      <widget class="QLabel" name="label_{param.name}">')
        xml.append('       <property name="text">')
        xml.append(f'        <string notr="true">{param.display_label}</string>')
        xml.append('       </property>')
        xml.append('      </widget>')
        xml.append('     </item>')

        xml.append(f'     <item row="{row}" column="1">')
        xml.append(f'      <widget class="MyColorButton" name="{widget_name}">')
        xml.append('       <property name="text">')
        xml.append('        <string>Color</string>')
        xml.append('       </property>')
        xml.append('      </widget>')
        xml.append('     </item>')

        return xml


def demo_rotation_transform():
    """Demo: Generate rotation transform UI"""

    print("="*70)
    print("DEMO: Rotation Transform UI")
    print("="*70 + "\n")

    generator = UIGenerator("transf_rotation_v2", "T>Rotation V2")

    parameters = [
        Parameter(
            name="rotation",
            type=ParamType.CVECTOR3,
            display_label="Rotation (alpha, beta, gamma)",
            default=(0.0, 0.0, 0.0),
            min_val=-36000.0,
            max_val=36000.0,
            step=1.0,
            decimals=6,
            tooltip="Rotation angles in degrees"
        ),
        Parameter(
            name="enabled",
            type=ParamType.BOOL,
            display_label="Enable rotation",
            default=True
        ),
        Parameter(
            name="start_iteration",
            type=ParamType.INT,
            display_label="Start at iteration",
            default=0,
            min_val=0,
            max_val=250
        )
    ]

    output_dir = Path(__file__).parent / "generated_ui"
    output_dir.mkdir(exist_ok=True)

    output_file = output_dir / "transf_rotation_v2.ui"

    success = generator.generate(parameters, output_file)

    if success:
        print(f"\n✅ Demo successful!")
        print(f"📁 Check: {output_file}")


def demo_complex_transform():
    """Demo: Complex transform with all parameter types"""

    print("\n" + "="*70)
    print("DEMO: Complex Transform UI")
    print("="*70 + "\n")

    generator = UIGenerator("transf_advanced_demo", "T>Advanced Demo")

    parameters = [
        Parameter(
            name="position",
            type=ParamType.CVECTOR3,
            display_label="Position",
            default=(0.0, 0.0, 0.0),
            min_val=-100.0,
            max_val=100.0,
            tooltip="Transform position in 3D space"
        ),
        Parameter(
            name="scale",
            type=ParamType.DOUBLE,
            display_label="Scale factor",
            default=1.0,
            min_val=0.001,
            max_val=100.0,
            step=0.1,
            decimals=3
        ),
        Parameter(
            name="iterations",
            type=ParamType.INT,
            display_label="Iterations",
            default=10,
            min_val=1,
            max_val=250
        ),
        Parameter(
            name="enabled",
            type=ParamType.BOOL,
            display_label="Enable transform",
            default=True
        ),
        Parameter(
            name="mode",
            type=ParamType.ENUM,
            display_label="Mode",
            enum_options=["Linear", "Spherical", "Cylindrical", "Custom"],
            default=0
        ),
        Parameter(
            name="color",
            type=ParamType.COLOR,
            display_label="Highlight color",
            default=(255, 128, 0)
        ),
        Parameter(
            name="quaternion",
            type=ParamType.CVECTOR4,
            display_label="Quaternion (x,y,z,w)",
            default=(0.0, 0.0, 0.0, 1.0),
            min_val=-1.0,
            max_val=1.0
        )
    ]

    output_dir = Path(__file__).parent / "generated_ui"
    output_dir.mkdir(exist_ok=True)

    output_file = output_dir / "transf_advanced_demo.ui"

    success = generator.generate(parameters, output_file)

    if success:
        print(f"\n✅ Demo successful!")
        print(f"📁 Check: {output_file}")
        print(f"\n💡 This UI has ALL parameter types!")


def interactive_menu():
    """Interactive UI generator"""

    print("╔" + "═"*68 + "╗")
    print("║" + " "*22 + "UI GENERATOR v1.0" + " "*29 + "║")
    print("╚" + "═"*68 + "╝\n")

    print("Generate Qt UI files from parameter definitions!\n")

    formula_name = input("Formula internal name (e.g., 'transf_rotation'): ").strip()
    if not formula_name:
        print("❌ Name required")
        return

    display_name = input("Display name (e.g., 'T>Rotation'): ").strip()
    if not display_name:
        display_name = formula_name

    generator = UIGenerator(formula_name, display_name)

    parameters = []

    print("\nAdd parameters (empty name to finish):\n")
    print("Parameter types:")
    print("  1. CVector3 (x,y,z)")
    print("  2. CVector4 (x,y,z,w)")
    print("  3. double")
    print("  4. int")
    print("  5. bool")
    print("  6. enum")
    print("  7. color")
    print()

    while True:
        param_name = input(f"\nParameter {len(parameters)+1} name (or Enter to finish): ").strip()
        if not param_name:
            break

        param_type_str = input("  Type (1-7): ").strip()
        type_map = {
            '1': ParamType.CVECTOR3,
            '2': ParamType.CVECTOR4,
            '3': ParamType.DOUBLE,
            '4': ParamType.INT,
            '5': ParamType.BOOL,
            '6': ParamType.ENUM,
            '7': ParamType.COLOR
        }

        if param_type_str not in type_map:
            print("  ❌ Invalid type")
            continue

        param_type = type_map[param_type_str]

        label = input(f"  Display label (default '{param_name}'): ").strip() or param_name

        param = Parameter(
            name=param_name,
            type=param_type,
            display_label=label,
            default=None
        )

        # Type-specific settings
        if param_type in [ParamType.CVECTOR3, ParamType.CVECTOR4, ParamType.DOUBLE]:
            min_str = input("  Min value (Enter for default): ").strip()
            if min_str:
                param.min_val = float(min_str)

            max_str = input("  Max value (Enter for default): ").strip()
            if max_str:
                param.max_val = float(max_str)

        elif param_type == ParamType.INT:
            min_str = input("  Min value (Enter for 0): ").strip()
            param.min_val = int(min_str) if min_str else 0

            max_str = input("  Max value (Enter for 100): ").strip()
            param.max_val = int(max_str) if max_str else 100

        elif param_type == ParamType.ENUM:
            options_str = input("  Enum options (comma-separated): ").strip()
            param.enum_options = [o.strip() for o in options_str.split(',')]

        parameters.append(param)
        print(f"  ✅ Added: {param.name} ({param.type.value})")

    if not parameters:
        print("\n⚠️  No parameters defined")
        return

    # Generate
    output_dir = Path(__file__).parent / "generated_ui"
    output_dir.mkdir(exist_ok=True)
    output_file = output_dir / f"{formula_name}.ui"

    print(f"\n{'='*70}")
    print("GENERATING UI")
    print(f"{'='*70}\n")

    success = generator.generate(parameters, output_file)

    if success:
        print(f"\n🎉 SUCCESS!")
        print(f"\nNext steps:")
        print(f"1. Review: {output_file}")
        print(f"2. Copy to: mandelbulber2/formula/ui/{formula_name}.ui")
        print(f"3. Rebuild Mandelbulber")


def main():
    """Main entry point"""

    if len(sys.argv) > 1 and sys.argv[1] == '--demo':
        demo_rotation_transform()
        demo_complex_transform()
    else:
        interactive_menu()


if __name__ == "__main__":
    main()

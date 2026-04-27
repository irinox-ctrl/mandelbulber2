#!/usr/bin/env python3
"""
PARAMETER REGISTRATION GENERATOR
=================================
Auto-generate parameter registration code from schema!

PROBLEEM:
- 1277 handmatige par->addParam() calls in initparameters.cpp
- Elke feature = 50-100 regels repetitive code
- Parameters moeten ook geladen worden in fractal.cpp (473 calls)
- Copy-paste errors
- Naming inconsistencies

OPLOSSING:
- Define parameters in simpel YAML/JSON schema
- Generate registration code (initparameters.cpp)
- Generate loading code (fractal.cpp)
- Generate UI widgets (integration met ui_generator.py)
- All-in-one parameter system!

TIJDSBESPARING: Uren per feature!

Author: Claude + Joeri
Version: 1.0
Date: 2026-04-19
"""

import sys
import json
import yaml
from pathlib import Path
from typing import List, Dict, Optional, Any
from dataclasses import dataclass, field
from enum import Enum


class ParamType(Enum):
    """Parameter types"""
    BOOL = "bool"
    INT = "int"
    DOUBLE = "double"
    STRING = "QString"
    CVECTOR3 = "CVector3"
    CVECTOR4 = "CVector4"
    SRGB = "sRGB"


class MorphType(Enum):
    """Morphing interpolation types"""
    NONE = "morphNone"
    LINEAR = "morphLinear"
    AKIMA = "morphAkima"
    AKIMA_ANGLE = "morphAkimaAngle"


class ParamSaveType(Enum):
    """Parameter save types"""
    STANDARD = "paramStandard"
    NO_SAVE = "paramNoSave"
    ONLY_FOR_NET_RENDER = "paramOnlyForNetRender"
    APP_ONLY = "paramApp"


@dataclass
class ParameterDefinition:
    """Single parameter definition"""
    name: str
    type: ParamType
    default: Any
    morph: MorphType = MorphType.LINEAR
    save_type: ParamSaveType = ParamSaveType.STANDARD

    # Optional constraints
    min_val: Optional[float] = None
    max_val: Optional[float] = None
    enum_options: Optional[List[str]] = None

    # UI
    display_label: Optional[str] = None
    tooltip: Optional[str] = None

    # Grouping
    prefix: str = ""  # e.g., "fake_lights_" or "transf_"
    index: Optional[int] = None  # For arrays (light1, light2, etc.)


@dataclass
class ParameterGroup:
    """Group of related parameters"""
    group_name: str
    prefix: str
    description: str
    parameters: List[ParameterDefinition] = field(default_factory=list)

    # Array support
    is_array: bool = False
    array_size: int = 1


class ParameterRegistrationGenerator:
    """Generate parameter registration code"""

    def __init__(self):
        pass

    def generate_registration_code(
        self,
        group: ParameterGroup,
        output_file: Path
    ) -> bool:
        """
        Generate C++ registration code for initparameters.cpp

        Args:
            group: Parameter group definition
            output_file: Where to save generated code

        Returns:
            True if successful
        """

        print(f"🔧 Generating registration code for: {group.group_name}")
        print(f"   Parameters: {len(group.parameters)}")
        print(f"   Prefix: {group.prefix}")

        code = []

        # Header comment
        code.append(f"// {group.group_name} - AUTO-GENERATED")
        code.append(f"// {group.description}")
        code.append("")

        if group.is_array:
            # Generate for each array element
            code.append(f"// Array of {group.array_size} {group.group_name}")
            code.append(f"for (int i = 0; i < {group.array_size}; i++)")
            code.append("{")

            for param in group.parameters:
                code.extend(self._generate_param_registration(param, array_index="i"))

            code.append("}")
        else:
            # Single set of parameters
            for param in group.parameters:
                code.extend(self._generate_param_registration(param))

        # Write to file
        code_str = '\n'.join(code)

        try:
            with open(output_file, 'w') as f:
                f.write(code_str)

            print(f"✅ Generated: {output_file}")
            print(f"   Lines: {len(code)}")
            return True

        except Exception as e:
            print(f"❌ Error: {e}")
            return False

    def _generate_param_registration(
        self,
        param: ParameterDefinition,
        array_index: Optional[str] = None
    ) -> List[str]:
        """Generate registration code for a single parameter"""

        code = []

        # Build parameter name
        if array_index:
            param_name = f'{param.prefix}{param.name}_" + QString::number({array_index}) + "'
        else:
            param_name = f'"{param.prefix}{param.name}"'

        # Build default value
        default_val = self._format_default_value(param.default, param.type)

        # Build registration line based on type
        if param.min_val is not None and param.max_val is not None:
            # Has min/max constraints
            code.append(
                f'\tpar->addParam({param_name}, {default_val}, '
                f'{param.min_val}, {param.max_val}, '
                f'{param.morph.value}, {param.save_type.value});'
            )
        elif param.enum_options:
            # Has enum options
            options_str = ', '.join(f'"{opt}"' for opt in param.enum_options)
            code.append(
                f'\tpar->addParam({param_name}, {default_val}, '
                f'{param.morph.value}, {param.save_type.value}, '
                f'QStringList({{{options_str}}}));'
            )
        else:
            # Standard parameter
            code.append(
                f'\tpar->addParam({param_name}, {default_val}, '
                f'{param.morph.value}, {param.save_type.value});'
            )

        return code

    def _format_default_value(self, value: Any, param_type: ParamType) -> str:
        """Format default value for C++ code"""

        if param_type == ParamType.BOOL:
            return "true" if value else "false"

        elif param_type == ParamType.INT:
            return str(int(value))

        elif param_type == ParamType.DOUBLE:
            return f"{float(value)}"

        elif param_type == ParamType.STRING:
            return f'QString("{value}")'

        elif param_type == ParamType.CVECTOR3:
            if isinstance(value, (list, tuple)) and len(value) == 3:
                return f"CVector3({value[0]}, {value[1]}, {value[2]})"
            return "CVector3(0.0, 0.0, 0.0)"

        elif param_type == ParamType.CVECTOR4:
            if isinstance(value, (list, tuple)) and len(value) == 4:
                return f"CVector4({value[0]}, {value[1]}, {value[2]}, {value[3]})"
            return "CVector4(0.0, 0.0, 0.0, 0.0)"

        elif param_type == ParamType.SRGB:
            if isinstance(value, (list, tuple)) and len(value) == 3:
                return f"sRGB({value[0]}, {value[1]}, {value[2]})"
            return "sRGB(255, 255, 255)"

        return str(value)

    def generate_loading_code(
        self,
        group: ParameterGroup,
        output_file: Path,
        struct_name: str = "fractal"
    ) -> bool:
        """
        Generate C++ loading code for fractal.cpp

        Args:
            group: Parameter group definition
            output_file: Where to save generated code
            struct_name: Target struct name (e.g., "fractal", "transformCommon")

        Returns:
            True if successful
        """

        print(f"\n📥 Generating loading code for: {group.group_name}")

        code = []

        # Header comment
        code.append(f"// {group.group_name} - AUTO-GENERATED LOADING CODE")
        code.append("")

        if group.is_array:
            code.append(f"// Load {group.array_size} {group.group_name}")
            code.append(f"for (int i = 0; i < {group.array_size}; i++)")
            code.append("{")

            for param in group.parameters:
                code.extend(self._generate_param_loading(param, struct_name, array_index="i"))

            code.append("}")
        else:
            for param in group.parameters:
                code.extend(self._generate_param_loading(param, struct_name))

        # Write to file
        code_str = '\n'.join(code)

        try:
            with open(output_file, 'w') as f:
                f.write(code_str)

            print(f"✅ Generated: {output_file}")
            print(f"   Lines: {len(code)}")
            return True

        except Exception as e:
            print(f"❌ Error: {e}")
            return False

    def _generate_param_loading(
        self,
        param: ParameterDefinition,
        struct_name: str,
        array_index: Optional[str] = None
    ) -> List[str]:
        """Generate loading code for a single parameter"""

        code = []

        # Build parameter name
        if array_index:
            param_name = f'{param.prefix}{param.name}_" + QString::number({array_index}) + "'
        else:
            param_name = f'"{param.prefix}{param.name}"'

        # Build struct member access
        member_name = param.name
        if array_index:
            struct_access = f"{struct_name}.{member_name}[{array_index}]"
        else:
            struct_access = f"{struct_name}.{member_name}"

        # Get type template
        type_template = self._get_cpp_type(param.type)

        # Generate getter call
        if array_index:
            code.append(
                f'\t{struct_access} = container->Get<{type_template}>({param_name}, fractalNumber);'
            )
        else:
            code.append(
                f'\t{struct_access} = container->Get<{type_template}>({param_name}, fractalNumber);'
            )

        return code

    def _get_cpp_type(self, param_type: ParamType) -> str:
        """Get C++ type string for template"""

        type_map = {
            ParamType.BOOL: "bool",
            ParamType.INT: "int",
            ParamType.DOUBLE: "double",
            ParamType.STRING: "QString",
            ParamType.CVECTOR3: "CVector3",
            ParamType.CVECTOR4: "CVector4",
            ParamType.SRGB: "sRGB"
        }

        return type_map.get(param_type, "double")


def load_schema_from_yaml(yaml_file: Path) -> ParameterGroup:
    """Load parameter schema from YAML file"""

    try:
        with open(yaml_file, 'r') as f:
            data = yaml.safe_load(f)

        # Parse parameters
        parameters = []

        for param_data in data.get('parameters', []):
            param = ParameterDefinition(
                name=param_data['name'],
                type=ParamType(param_data['type']),
                default=param_data['default'],
                morph=MorphType(param_data.get('morph', 'morphLinear')),
                save_type=ParamSaveType(param_data.get('save_type', 'paramStandard')),
                min_val=param_data.get('min'),
                max_val=param_data.get('max'),
                enum_options=param_data.get('enum_options'),
                display_label=param_data.get('label'),
                tooltip=param_data.get('tooltip'),
                prefix=data.get('prefix', '')
            )
            parameters.append(param)

        # Create group
        group = ParameterGroup(
            group_name=data['group_name'],
            prefix=data.get('prefix', ''),
            description=data.get('description', ''),
            parameters=parameters,
            is_array=data.get('is_array', False),
            array_size=data.get('array_size', 1)
        )

        return group

    except Exception as e:
        print(f"❌ Error loading schema: {e}")
        return None


def demo_light_parameters():
    """Demo: Generate light parameter registration"""

    print("=" * 70)
    print("DEMO: Light Parameters")
    print("=" * 70 + "\n")

    # Define light parameters
    group = ParameterGroup(
        group_name="Light System",
        prefix="light_",
        description="Light source parameters",
        is_array=True,
        array_size=4
    )

    # Add parameters
    group.parameters = [
        ParameterDefinition(
            name="enabled",
            type=ParamType.BOOL,
            default=False,
            morph=MorphType.NONE,
            display_label="Enable light"
        ),
        ParameterDefinition(
            name="intensity",
            type=ParamType.DOUBLE,
            default=1.0,
            min_val=0.0,
            max_val=100.0,
            morph=MorphType.LINEAR,
            display_label="Intensity"
        ),
        ParameterDefinition(
            name="position",
            type=ParamType.CVECTOR3,
            default=(0.0, 3.0, -3.0),
            morph=MorphType.AKIMA,
            display_label="Position"
        ),
        ParameterDefinition(
            name="color",
            type=ParamType.SRGB,
            default=(255, 255, 255),
            morph=MorphType.LINEAR,
            display_label="Color"
        ),
        ParameterDefinition(
            name="type",
            type=ParamType.INT,
            default=0,
            enum_options=["directional", "point", "spot"],
            morph=MorphType.LINEAR,
            display_label="Light type"
        )
    ]

    # Generate
    generator = ParameterRegistrationGenerator()

    output_dir = Path(__file__).parent / "generated_parameters"
    output_dir.mkdir(exist_ok=True)

    # Registration code
    reg_file = output_dir / "light_registration.cpp"
    generator.generate_registration_code(group, reg_file)

    # Loading code
    load_file = output_dir / "light_loading.cpp"
    generator.generate_loading_code(group, load_file, "lights")

    print(f"\n✅ Demo complete!")
    print(f"📁 Check: {output_dir}")


def demo_transform_parameters():
    """Demo: Generate transform parameter registration"""

    print("\n" + "=" * 70)
    print("DEMO: Transform Parameters")
    print("=" * 70 + "\n")

    # Define transform parameters
    group = ParameterGroup(
        group_name="Advanced Rotation Transform",
        prefix="transf_advanced_rotation_",
        description="Advanced rotation with multiple axes"
    )

    group.parameters = [
        ParameterDefinition(
            name="enabled",
            type=ParamType.BOOL,
            default=False,
            morph=MorphType.LINEAR,
            display_label="Enable transform"
        ),
        ParameterDefinition(
            name="rotation",
            type=ParamType.CVECTOR3,
            default=(0.0, 0.0, 0.0),
            min_val=-360.0,
            max_val=360.0,
            morph=MorphType.AKIMA_ANGLE,
            display_label="Rotation angles (degrees)"
        ),
        ParameterDefinition(
            name="center",
            type=ParamType.CVECTOR3,
            default=(0.0, 0.0, 0.0),
            min_val=-10.0,
            max_val=10.0,
            morph=MorphType.AKIMA,
            display_label="Rotation center"
        ),
        ParameterDefinition(
            name="start_iteration",
            type=ParamType.INT,
            default=0,
            min_val=0,
            max_val=250,
            morph=MorphType.LINEAR,
            display_label="Start at iteration"
        ),
        ParameterDefinition(
            name="stop_iteration",
            type=ParamType.INT,
            default=250,
            min_val=0,
            max_val=250,
            morph=MorphType.LINEAR,
            display_label="Stop at iteration"
        )
    ]

    # Generate
    generator = ParameterRegistrationGenerator()

    output_dir = Path(__file__).parent / "generated_parameters"
    output_dir.mkdir(exist_ok=True)

    reg_file = output_dir / "transform_rotation_registration.cpp"
    generator.generate_registration_code(group, reg_file)

    load_file = output_dir / "transform_rotation_loading.cpp"
    generator.generate_loading_code(group, load_file, "transformCommon")

    print(f"\n✅ Demo complete!")


def interactive_menu():
    """Interactive parameter definition"""

    print("╔" + "═"*68 + "╗")
    print("║" + " "*12 + "PARAMETER REGISTRATION GENERATOR v1.0" + " "*19 + "║")
    print("╚" + "═"*68 + "╝\n")

    group_name = input("Parameter group name (e.g., 'Advanced Fold'): ").strip()
    if not group_name:
        print("❌ Name required")
        return

    prefix = input("Parameter prefix (e.g., 'transf_fold_'): ").strip()
    description = input("Description: ").strip()

    is_array = input("Array of parameters? (y/n): ").strip().lower() == 'y'
    array_size = 1
    if is_array:
        array_size = int(input("Array size: ").strip())

    group = ParameterGroup(
        group_name=group_name,
        prefix=prefix,
        description=description,
        is_array=is_array,
        array_size=array_size
    )

    # Add parameters
    print("\nAdd parameters (empty name to finish):")
    print("Types: bool, int, double, QString, CVector3, CVector4, sRGB")
    print()

    while True:
        param_name = input(f"\nParameter {len(group.parameters)+1} name (Enter to finish): ").strip()
        if not param_name:
            break

        param_type_str = input("  Type: ").strip()
        try:
            param_type = ParamType(param_type_str)
        except:
            print("  ❌ Invalid type")
            continue

        default_str = input("  Default value: ").strip()

        # Parse default based on type
        if param_type == ParamType.BOOL:
            default = default_str.lower() in ['true', '1', 'yes']
        elif param_type == ParamType.INT:
            default = int(default_str)
        elif param_type == ParamType.DOUBLE:
            default = float(default_str)
        elif param_type in [ParamType.CVECTOR3, ParamType.CVECTOR4]:
            default = tuple(float(x) for x in default_str.split(','))
        else:
            default = default_str

        param = ParameterDefinition(
            name=param_name,
            type=param_type,
            default=default,
            prefix=prefix
        )

        # Optional constraints
        if param_type in [ParamType.INT, ParamType.DOUBLE]:
            min_str = input("  Min (Enter to skip): ").strip()
            if min_str:
                param.min_val = float(min_str)

            max_str = input("  Max (Enter to skip): ").strip()
            if max_str:
                param.max_val = float(max_str)

        group.parameters.append(param)
        print(f"  ✅ Added: {param.name}")

    if not group.parameters:
        print("\n⚠️  No parameters defined")
        return

    # Generate
    print(f"\n{'='*70}")
    print("GENERATING CODE")
    print(f"{'='*70}\n")

    generator = ParameterRegistrationGenerator()

    output_dir = Path(__file__).parent / "generated_parameters"
    output_dir.mkdir(exist_ok=True)

    # Files
    reg_file = output_dir / f"{prefix}registration.cpp"
    load_file = output_dir / f"{prefix}loading.cpp"

    generator.generate_registration_code(group, reg_file)
    generator.generate_loading_code(group, load_file)

    print(f"\n🎉 SUCCESS!")
    print(f"\nGenerated files:")
    print(f"  Registration: {reg_file}")
    print(f"  Loading:      {load_file}")
    print(f"\nNext steps:")
    print(f"1. Copy registration code to initparameters.cpp")
    print(f"2. Copy loading code to fractal.cpp")
    print(f"3. Rebuild Mandelbulber")


def main():
    """Main entry"""

    if len(sys.argv) > 1 and sys.argv[1] == '--demo':
        demo_light_parameters()
        demo_transform_parameters()
    else:
        interactive_menu()


if __name__ == "__main__":
    main()

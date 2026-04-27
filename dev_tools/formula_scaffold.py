#!/usr/bin/env python3
"""
COMPLETE FORMULA SCAFFOLD GENERATOR
====================================
Genereer ALLE 6-7 bestanden voor een nieuwe formule in één keer!

PROBLEEM:
- Nieuwe formule = 6-7 bestanden aanmaken
- Constructor boilerplate (50+ regels)
- Registration in 3 files
- UI file (260+ regels XML)
- Enum ID vinden
- Naming conventions
- TIJDSINTENSIEF: 1-2 uur per formule!

OPLOSSING:
- Genereer alles in één commando
- Consistent naming
- Auto enum ID selection
- Ready-to-compile code
- Alleen FormulaCode invullen!

TIJDSBESPARING: 1 uur per formule!

Integration met:
- ui_generator.py (UI files)
- formula_validator.py (validation)
- find_next_formula_id.py (enum IDs)

Author: Claude + Joeri
Version: 1.0
Date: 2026-04-19
"""

import sys
import re
from pathlib import Path
from typing import List, Dict, Optional, Tuple
from dataclasses import dataclass
from enum import Enum
import subprocess

# Import UI generator if available
try:
    from ui_generator import UIGenerator, Parameter, ParamType
    UI_GENERATOR_AVAILABLE = True
except:
    UI_GENERATOR_AVAILABLE = False


class FormulaType(Enum):
    """Formula types"""
    TRANSFORM = "transform"
    FRACTAL = "fractal"
    PRIMITIVE = "primitive"
    DIFS = "difs"


class DEType(Enum):
    """Distance estimation types"""
    ANALYTIC_LINEAR = "analyticDEType + linearDEFunction"
    ANALYTIC_LOG = "analyticDEType + logarithmicDEFunction"
    PSEUDO_KLEINIAN = "pseudoKleinianDEType"
    CUSTOM = "analyticDEType + customDEFunction"
    NONE = "analyticDEType + withoutDEFunction"


@dataclass
class FormulaScaffoldConfig:
    """Configuration for formula scaffold"""
    internal_name: str
    display_name: str
    formula_type: FormulaType
    de_type: DEType
    description: str
    parameters: List[any] = None
    base_formula: Optional[str] = None  # Copy parameters from base


class FormulaScaffold:
    """Generate complete formula scaffold"""

    def __init__(self, base_dir: Path, output_dir: Path):
        self.base_dir = base_dir
        self.output_dir = output_dir
        self.output_dir.mkdir(parents=True, exist_ok=True)

    def generate(self, config: FormulaScaffoldConfig) -> Dict[str, Path]:
        """
        Generate all files for new formula

        Returns:
            Dict of {file_type: path} for generated files
        """

        print("=" * 70)
        print("🏗️  FORMULA SCAFFOLD GENERATOR")
        print("=" * 70)
        print(f"Name: {config.display_name}")
        print(f"Internal: {config.internal_name}")
        print(f"Type: {config.formula_type.value}")
        print(f"DE: {config.de_type.value}")
        print("=" * 70 + "\n")

        generated = {}

        # 1. Find next enum ID
        enum_id = self._find_next_enum_id()
        print(f"📋 Enum ID: {enum_id}")

        # 2. Generate class name
        class_name = self._to_class_name(config.internal_name)
        print(f"📝 Class: {class_name}")

        # 3. Generate CPP file
        cpp_file = self._generate_cpp(config, class_name, enum_id)
        generated['cpp'] = cpp_file
        print(f"✅ CPP: {cpp_file}")

        # 4. Generate UI file
        if UI_GENERATOR_AVAILABLE and config.parameters:
            ui_file = self._generate_ui(config)
            generated['ui'] = ui_file
            print(f"✅ UI: {ui_file}")
        else:
            print(f"⚠️  UI: Skipped (no parameters or UI generator not available)")

        # 5. Generate registration instructions
        reg_file = self._generate_registration_instructions(config, class_name, enum_id)
        generated['registration'] = reg_file
        print(f"✅ Registration: {reg_file}")

        # 6. Summary
        print(f"\n{'='*70}")
        print("📊 SUMMARY")
        print(f"{'='*70}\n")
        print(f"Generated {len(generated)} files:")
        for ftype, fpath in generated.items():
            print(f"  {ftype:15} → {fpath.name}")

        print(f"\n📁 Output directory: {self.output_dir}")

        return generated

    def _find_next_enum_id(self) -> int:
        """Find next available enum ID"""

        # Try to find enum file
        enum_file = self.base_dir / "formula" / "definition" / "all_fractal_list_enums.hpp"

        if not enum_file.exists():
            print(f"⚠️  Enum file not found, using default ID 1000")
            return 1000

        try:
            with open(enum_file, 'r') as f:
                content = f.read()

            # Find all enum values
            pattern = r'=\s*(\d+)'
            matches = re.findall(pattern, content)
            ids = [int(m) for m in matches]

            if ids:
                next_id = max(ids) + 1
                return next_id
            else:
                return 1000

        except Exception as e:
            print(f"⚠️  Error reading enum file: {e}")
            return 1000

    def _to_class_name(self, internal_name: str) -> str:
        """Convert internal_name to ClassName"""
        parts = internal_name.split('_')
        return 'cFractal' + ''.join(p.capitalize() for p in parts)

    def _generate_cpp(
        self,
        config: FormulaScaffoldConfig,
        class_name: str,
        enum_id: int
    ) -> Path:
        """Generate CPP implementation file"""

        # Determine DE settings
        de_settings = self._get_de_settings(config.de_type)

        cpp = f'''/**
 * Mandelbulber v2, a 3D fractal generator
 *
 * {config.display_name}
 * {config.description}
 *
 * AUTO-GENERATED by Formula Scaffold Tool
 * Author: Your Name
 * Date: {self._get_date()}
 */

#include "all_fractal_definitions.h"

class {class_name} : public cAbstractFractal
{{
public:
\t{class_name}();
\tvoid FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux) override;
}};

{class_name}::{class_name}() : cAbstractFractal()
{{
\tnameInComboBox = "{config.display_name}";
\tinternalName = "{config.internal_name}";
\tinternalID = fractal::{config.internal_name};
\t{de_settings['de_type']}
\t{de_settings['de_function_type']}
\tcpixelAddition = cpixelDisabledByDefault;
\tdefaultBailout = 100.0;
\t{de_settings['de_analytic_function']}
\tcoloringFunction = coloringFunctionDefault;
}}

void {class_name}::FormulaCode(
\tCVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{{
\t// TODO: Implement your formula here!
\t//
\t// Example transform:
\t// z = z * fractal->transformCommon.scale;
\t// aux.DE = aux.DE * fractal->transformCommon.scale;
\t//
\t// Example condition:
\t// if (aux.i >= fractal->transformCommon.startIterations
\t//     && aux.i < fractal->transformCommon.stopIterations)
\t// {{
\t//     // Apply transform
\t// }}
\t//
\t// Available parameters:
\t// - fractal->transformCommon.scale (double)
\t// - fractal->transformCommon.offset000 (CVector3)
\t// - fractal->transformCommon.rotation (CVector3)
\t// - fractal->transformCommon.startIterations (int)
\t// - fractal->transformCommon.functionEnabledFalse (bool)
\t//
\t// IMPORTANT: Always update aux.DE when you modify z!

\t// Placeholder - remove this and add your code:
\tQ_UNUSED(z);
\tQ_UNUSED(fractal);
\tQ_UNUSED(aux);
}}
'''

        # Save to file
        cpp_file = self.output_dir / f"fractal_{config.internal_name}.cpp"

        with open(cpp_file, 'w') as f:
            f.write(cpp)

        return cpp_file

    def _get_de_settings(self, de_type: DEType) -> Dict[str, str]:
        """Get DE type settings"""

        if de_type == DEType.ANALYTIC_LINEAR:
            return {
                'de_type': 'DEType = analyticDEType;',
                'de_function_type': 'DEFunctionType = linearDEFunction;',
                'de_analytic_function': 'DEAnalyticFunction = analyticFunctionLinear;'
            }
        elif de_type == DEType.ANALYTIC_LOG:
            return {
                'de_type': 'DEType = analyticDEType;',
                'de_function_type': 'DEFunctionType = logarithmicDEFunction;',
                'de_analytic_function': 'DEAnalyticFunction = analyticFunctionLogarithmic;'
            }
        elif de_type == DEType.PSEUDO_KLEINIAN:
            return {
                'de_type': 'DEType = pseudoKleinianDEType;',
                'de_function_type': 'DEFunctionType = pseudoKleinianDEFunction;',
                'de_analytic_function': 'DEAnalyticFunction = analyticFunctionPseudoKleinian;'
            }
        elif de_type == DEType.CUSTOM:
            return {
                'de_type': 'DEType = analyticDEType;',
                'de_function_type': 'DEFunctionType = customDEFunction;',
                'de_analytic_function': 'DEAnalyticFunction = analyticFunctionCustomDE;'
            }
        else:  # NONE
            return {
                'de_type': 'DEType = analyticDEType;',
                'de_function_type': 'DEFunctionType = withoutDEFunction;',
                'de_analytic_function': 'DEAnalyticFunction = analyticFunctionIFS;'
            }

    def _generate_ui(self, config: FormulaScaffoldConfig) -> Path:
        """Generate UI file"""

        if not UI_GENERATOR_AVAILABLE:
            return None

        generator = UIGenerator(config.internal_name, config.display_name)

        ui_file = self.output_dir / f"{config.internal_name}.ui"

        generator.generate(config.parameters, ui_file)

        return ui_file

    def _generate_registration_instructions(
        self,
        config: FormulaScaffoldConfig,
        class_name: str,
        enum_id: int
    ) -> Path:
        """Generate instructions for manual registration"""

        instructions = f'''REGISTRATION INSTRUCTIONS
========================

Formula: {config.display_name}
Internal name: {config.internal_name}
Class name: {class_name}
Enum ID: {enum_id}

You need to manually add this formula to 3 files:

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

FILE 1: formula/definition/all_fractal_definitions.h
----------------------------------------------------

Add this line with other FRACTAL_CLASS declarations:

FRACTAL_CLASS({class_name}, {config.internal_name})

Location: Find similar declarations like:
  FRACTAL_CLASS(cFractalTransfRotation, transf_rotation)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

FILE 2: formula/definition/all_fractal_list.cpp
-----------------------------------------------

Add this entry to the list[] array:

\t{{{class_name}::automaticName, typeid({class_name}).name()}},

Location: Find similar entries like:
  {{cFractalTransfRotation::automaticName, typeid(cFractalTransfRotation).name()}},

IMPORTANT: Add comma at the end!

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

FILE 3: formula/definition/all_fractal_list_enums.hpp
-----------------------------------------------------

Add this enum entry:

\t{config.internal_name} = {enum_id},

Location: Inside the fractal namespace enum, find entries like:
  transf_rotation = 123,

IMPORTANT: Add comma at the end!

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

COPY FILES TO MANDELBULBER:
---------------------------

# Copy CPP file
cp {self.output_dir}/fractal_{config.internal_name}.cpp \\
   mandelbulber2/formula/definition/

# Copy UI file (if generated)
cp {self.output_dir}/{config.internal_name}.ui \\
   mandelbulber2/formula/ui/

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

REBUILD MANDELBULBER:
---------------------

cd mandelbulber2/qmake
qmake
make -j8

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

TESTING:
--------

1. Start Mandelbulber
2. Load test.fract
3. Formula tab → Slot 1 → Find "{config.display_name}"
4. Test rendering
5. Check for crashes/errors

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

VALIDATION:
-----------

Run formula validator:

python3 formula_validator.py {self.output_dir}/fractal_{config.internal_name}.cpp

Expected: PASS with score ≥ 70%

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

NEXT STEPS:
-----------

1. ✅ Files generated
2. ⏳ Add manual registrations (3 files above)
3. ⏳ Copy files to Mandelbulber
4. ⏳ Implement FormulaCode() in CPP file
5. ⏳ Rebuild Mandelbulber
6. ⏳ Test in UI

💡 TIP: Keep this file open while doing manual registration!

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
'''

        reg_file = self.output_dir / "REGISTRATION_INSTRUCTIONS.txt"

        with open(reg_file, 'w') as f:
            f.write(instructions)

        return reg_file

    def _get_date(self) -> str:
        """Get current date"""
        from datetime import datetime
        return datetime.now().strftime("%Y-%m-%d")


def interactive_menu():
    """Interactive scaffold generator"""

    print("╔" + "═"*68 + "╗")
    print("║" + " "*17 + "FORMULA SCAFFOLD GENERATOR v1.0" + " "*20 + "║")
    print("╚" + "═"*68 + "╝\n")

    print("Generate complete formula scaffold (all files at once)!\n")

    # Get basic info
    internal_name = input("Internal name (e.g., 'transf_my_rotation'): ").strip()
    if not internal_name:
        print("❌ Name required")
        return

    display_name = input(f"Display name (e.g., 'T>My Rotation'): ").strip()
    if not display_name:
        display_name = internal_name

    description = input("Short description: ").strip() or "Custom formula"

    # Formula type
    print("\nFormula type:")
    print("  1. Transform")
    print("  2. Fractal")
    print("  3. Primitive (DIFS)")
    print("  4. Other")

    ftype_choice = input("Choice (1-4): ").strip()
    ftype_map = {
        '1': FormulaType.TRANSFORM,
        '2': FormulaType.FRACTAL,
        '3': FormulaType.DIFS,
        '4': FormulaType.TRANSFORM
    }
    formula_type = ftype_map.get(ftype_choice, FormulaType.TRANSFORM)

    # DE type
    print("\nDistance estimation type:")
    print("  1. Linear (transforms, simple operations)")
    print("  2. Logarithmic (power fractals like Mandelbulb)")
    print("  3. Pseudo-Kleinian (sphere inversions)")
    print("  4. Custom (clipping, custom DE)")
    print("  5. None (no DE modification)")

    de_choice = input("Choice (1-5): ").strip()
    de_map = {
        '1': DEType.ANALYTIC_LINEAR,
        '2': DEType.ANALYTIC_LOG,
        '3': DEType.PSEUDO_KLEINIAN,
        '4': DEType.CUSTOM,
        '5': DEType.NONE
    }
    de_type = de_map.get(de_choice, DEType.ANALYTIC_LINEAR)

    # Parameters
    parameters = []

    add_params = input("\nAdd UI parameters? (y/n): ").strip().lower()

    if add_params == 'y' and UI_GENERATOR_AVAILABLE:
        print("\nAdd parameters (empty to finish):")
        print("Types: cvector3, double, int, bool")

        from ui_generator import Parameter, ParamType

        while True:
            pname = input(f"\n  Parameter {len(parameters)+1} name (Enter to finish): ").strip()
            if not pname:
                break

            ptype_str = input("  Type (cvector3/double/int/bool): ").strip().lower()

            ptype_map = {
                'cvector3': ParamType.CVECTOR3,
                'double': ParamType.DOUBLE,
                'int': ParamType.INT,
                'bool': ParamType.BOOL
            }

            if ptype_str not in ptype_map:
                print("  ❌ Invalid type")
                continue

            param = Parameter(
                name=pname,
                type=ptype_map[ptype_str],
                display_label=pname.replace('_', ' ').title(),
                default=None
            )

            # Ranges for numeric types
            if ptype_str in ['cvector3', 'double']:
                min_val = input("  Min (default -100): ").strip()
                param.min_val = float(min_val) if min_val else -100.0

                max_val = input("  Max (default 100): ").strip()
                param.max_val = float(max_val) if max_val else 100.0

            elif ptype_str == 'int':
                param.min_val = 0
                param.max_val = 250

            parameters.append(param)
            print(f"  ✅ Added: {param.name}")

    # Create config
    config = FormulaScaffoldConfig(
        internal_name=internal_name,
        display_name=display_name,
        formula_type=formula_type,
        de_type=de_type,
        description=description,
        parameters=parameters if parameters else None
    )

    # Generate
    base_dir = Path(__file__).parent.parent / "mandelbulber2"
    output_dir = Path(__file__).parent / "generated_formulas"

    scaffold = FormulaScaffold(base_dir, output_dir)

    print(f"\n{'='*70}")
    print("GENERATING SCAFFOLD")
    print(f"{'='*70}\n")

    generated = scaffold.generate(config)

    print(f"\n{'='*70}")
    print("🎉 SCAFFOLD COMPLETE!")
    print(f"{'='*70}\n")

    print(f"📁 All files in: {output_dir}")
    print(f"\n📋 NEXT: Read REGISTRATION_INSTRUCTIONS.txt for manual steps!")


def main():
    """Main entry"""
    interactive_menu()


if __name__ == "__main__":
    main()

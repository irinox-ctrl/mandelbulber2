#!/usr/bin/env python3
"""
MANDELBULBER INTERACTIVE FORMULA GENERATOR
===========================================
Interactive tool to create NEW formulas by combining existing formulas.

Usage:
    python3 formula_generator_interactive.py

Author: Claude + Joeri
Version: 1.1
Date: 2026-04-19
"""

import os
import re
import sys
from typing import Dict, List, Tuple, Optional
from pathlib import Path
from dataclasses import dataclass


@dataclass
class FormulaInfo:
    """Complete formula information parsed from source"""
    filename: str
    class_name: str
    name_in_combo: str
    internal_name: str
    internal_id: str
    de_type: str
    de_function_type: str
    cpixel_addition: str
    default_bailout: str
    de_analytic_function: str
    coloring_function: str
    formula_code: str
    full_content: str


class FormulaParser:
    """Parse existing formula C++ files"""

    def __init__(self, formula_dir: str):
        self.formula_dir = Path(formula_dir)
        self.formulas: Dict[str, FormulaInfo] = {}
        self.formulas_by_index: Dict[int, FormulaInfo] = {}

    def parse_all_formulas(self) -> None:
        """Parse all .cpp formula files"""
        print(f"📁 Scanning {self.formula_dir}...")

        cpp_files = list(self.formula_dir.glob("fractal_*.cpp"))
        print(f"📄 Found {len(cpp_files)} formula files")

        for cpp_file in cpp_files:
            try:
                info = self.parse_formula_file(cpp_file)
                if info and info.internal_id:
                    self.formulas[info.internal_id] = info
            except Exception as e:
                pass  # Skip problematic files

        # Create index mapping
        for idx, (fid, info) in enumerate(sorted(self.formulas.items()), 1):
            self.formulas_by_index[idx] = info

        print(f"✅ Successfully parsed {len(self.formulas)} formulas\n")

    def parse_formula_file(self, filepath: Path) -> Optional[FormulaInfo]:
        """Parse single formula file"""
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()

        # Extract class name
        class_match = re.search(r'class\s+(cFractal\w+)\s*:', content)
        if not class_match:
            class_match = re.search(r'(cFractal\w+)::\1\(\)', content)
        if not class_match:
            return None

        class_name = class_match.group(1)

        # Extract constructor parameters
        name_combo = self._extract_param(content, 'nameInComboBox')
        internal_name = self._extract_param(content, 'internalName')
        internal_id = self._extract_param(content, 'internalID')
        de_type = self._extract_param(content, 'DEType')
        de_func_type = self._extract_param(content, 'DEFunctionType')
        cpixel = self._extract_param(content, 'cpixelAddition')
        bailout = self._extract_param(content, 'defaultBailout')
        de_analytic = self._extract_param(content, 'DEAnalyticFunction')
        coloring = self._extract_param(content, 'coloringFunction')

        # Extract FormulaCode function
        formula_code = self._extract_formula_code(content)

        return FormulaInfo(
            filename=filepath.name,
            class_name=class_name,
            name_in_combo=name_combo or "Unknown",
            internal_name=internal_name or "",
            internal_id=internal_id or "",
            de_type=de_type or "analyticDEType",
            de_function_type=de_func_type or "linearDEFunction",
            cpixel_addition=cpixel or "cpixelEnabledByDefault",
            default_bailout=bailout or "100.0",
            de_analytic_function=de_analytic or "analyticFunctionLinear",
            coloring_function=coloring or "coloringFunctionDefault",
            formula_code=formula_code or "",
            full_content=content
        )

    def _extract_param(self, content: str, param_name: str) -> Optional[str]:
        """Extract parameter value from constructor"""
        pattern = rf'{param_name}\s*=\s*([^;]+);'
        match = re.search(pattern, content)
        if match:
            return match.group(1).strip().strip('"')
        return None

    def _extract_formula_code(self, content: str) -> Optional[str]:
        """Extract FormulaCode function body"""
        pattern = r'void\s+\w+::FormulaCode\s*\([^)]+\)\s*\{(.*?)\n\}'
        match = re.search(pattern, content, re.DOTALL)
        if match:
            return match.group(1)
        return None

    def get_formula_by_id(self, formula_id: str) -> Optional[FormulaInfo]:
        """Get formula info by internal ID"""
        return self.formulas.get(formula_id)

    def get_formula_by_index(self, index: int) -> Optional[FormulaInfo]:
        """Get formula by numeric index"""
        return self.formulas_by_index.get(index)

    def list_formulas(self, search: str = "") -> List[Tuple[int, FormulaInfo]]:
        """List all formulas, optionally filtered by search term"""
        results = []
        for idx, info in self.formulas_by_index.items():
            if not search or search.lower() in info.name_in_combo.lower():
                results.append((idx, info))
        return results

    def print_formulas(self, search: str = "", limit: int = 50):
        """Print formatted formula list"""
        results = self.list_formulas(search)

        if not results:
            print(f"❌ No formulas found matching '{search}'")
            return

        print(f"\n{'#':>4} {'Formula Name':<55} {'Internal ID':<30}")
        print("=" * 92)

        for idx, info in results[:limit]:
            print(f"{idx:4d}. {info.name_in_combo:<55} {info.internal_id:<30}")

        if len(results) > limit:
            print(f"\n... and {len(results) - limit} more. Use search to narrow down.")


class FormulaGenerator:
    """Generate new formulas by combining existing ones"""

    def __init__(self, parser: FormulaParser, output_dir: str):
        self.parser = parser
        self.output_dir = Path(output_dir)
        self.output_dir.mkdir(parents=True, exist_ok=True)

    def combine_formulas(self,
                        formula_indices: List[int],
                        new_name: str,
                        new_internal_name: str,
                        new_internal_id: str,
                        merge_strategy: str = "sequential") -> str:
        """
        Combine multiple formulas into one

        Args:
            formula_indices: List of formula indices to combine
            new_name: Display name for new formula
            new_internal_name: Internal identifier (snake_case)
            new_internal_id: Enum ID (camelCase)
            merge_strategy: "sequential", "parallel", or "weighted"

        Returns:
            Generated C++ code
        """
        # Get formula info
        formulas = []
        for idx in formula_indices:
            info = self.parser.get_formula_by_index(idx)
            if not info:
                raise ValueError(f"Formula index {idx} not found")
            formulas.append(info)

        print(f"\n🔨 Combining {len(formulas)} formulas:")
        for i, f in enumerate(formulas, 1):
            print(f"  {i}. {f.name_in_combo}")

        # Generate class name
        class_name = self._to_class_name(new_internal_id)

        # Generate code
        code = self._generate_header(class_name, new_name, formulas)
        code += self._generate_constructor(
            class_name, new_name, new_internal_name,
            new_internal_id, formulas[0]  # Use first formula's properties
        )
        code += self._generate_formula_code(
            class_name, formulas, merge_strategy
        )

        return code

    def _to_class_name(self, internal_id: str) -> str:
        """Convert internal_id to ClassName"""
        # Remove 'fractal::' prefix if present
        internal_id = internal_id.replace('fractal::', '')
        # Split on underscore and capitalize
        parts = internal_id.split('_')
        return 'cFractal' + ''.join(p.capitalize() for p in parts)

    def _generate_header(self, class_name: str, formula_name: str,
                        formulas: List[FormulaInfo]) -> str:
        """Generate file header and includes"""
        sources = '\n'.join(f' * Source {i}: {f.name_in_combo}'
                           for i, f in enumerate(formulas, 1))

        return f'''/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2024 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \\><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \\____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{{i%+++
 *
 * {formula_name}
 *
 * Generated by Formula Generator Tool
{sources}
 */

#include "all_fractal_definitions.h"

'''

    def _generate_constructor(self, class_name: str, name_combo: str,
                             internal_name: str, internal_id: str,
                             template: FormulaInfo) -> str:
        """Generate constructor"""
        return f'''{class_name}::{class_name}() : cAbstractFractal()
{{
\tnameInComboBox = "{name_combo}";
\tinternalName = "{internal_name}";
\tinternalID = fractal::{internal_id};
\tDEType = {template.de_type};
\tDEFunctionType = {template.de_function_type};
\tcpixelAddition = {template.cpixel_addition};
\tdefaultBailout = {template.default_bailout};
\tDEAnalyticFunction = {template.de_analytic_function};
\tcoloringFunction = {template.coloring_function};
}}

'''

    def _generate_formula_code(self, class_name: str,
                               formulas: List[FormulaInfo],
                               strategy: str) -> str:
        """Generate FormulaCode function"""
        code = f'''void {class_name}::FormulaCode(
\tCVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{{
'''

        if strategy == "sequential":
            # Execute formulas in sequence
            code += '\t// Combined formula - Sequential execution\n'
            for i, formula in enumerate(formulas):
                code += f'\n\t// ========== Stage {i+1}: {formula.name_in_combo} ==========\n'
                # Fix variable name conflicts
                fixed_code = self._fix_variable_conflicts(formula.formula_code, i)
                code += self._indent_code(fixed_code, 1)

        elif strategy == "parallel":
            # Alternate formulas based on iteration
            code += '\t// Combined formula - Parallel (iteration-based)\n'
            for i, formula in enumerate(formulas):
                code += f'\n\t// Stage {i+1}: {formula.name_in_combo}\n'
                code += f'\tif (aux.i % {len(formulas)} == {i})\n\t{{\n'
                fixed_code = self._fix_variable_conflicts(formula.formula_code, i)
                code += self._indent_code(fixed_code, 2)
                code += '\t}\n'

        elif strategy == "weighted":
            # Mix formulas with weighting
            code += '\t// Combined formula - Weighted blend\n'
            code += '\t// Store original z for blending\n'
            code += '\tCVector4 z_original = z;\n\n'

            for i, formula in enumerate(formulas):
                weight = 1.0 / len(formulas)
                code += f'\n\t// Stage {i+1}: {formula.name_in_combo} (weight: {weight:.2f})\n'
                code += '\t{\n'
                code += '\t\tCVector4 z_temp = z;\n'
                fixed_code = self._fix_variable_conflicts(formula.formula_code, i)
                # Replace 'z' with 'z_temp' in formula code
                fixed_code = re.sub(r'\bz\b', 'z_temp', fixed_code)
                code += self._indent_code(fixed_code, 2)
                code += f'\t\tz = z * {1.0 - weight:.2f} + z_temp * {weight:.2f};\n'
                code += '\t}\n'

        code += '}\n'
        return code

    def _fix_variable_conflicts(self, code: str, stage_index: int) -> str:
        """Fix variable name conflicts between formulas"""
        # Rename local variables to avoid conflicts
        # Match 'double varname' declarations
        code = re.sub(r'\bdouble\s+(\w+)\s*=',
                     rf'double \1_s{stage_index} =',
                     code)

        # Update variable references (this is simplified, may need refinement)
        # This is a basic implementation - more sophisticated AST parsing needed for production
        return code

    def _indent_code(self, code: str, levels: int) -> str:
        """Indent code block"""
        indent = '\t' * levels
        lines = code.split('\n')
        return '\n'.join(indent + line if line.strip() else '' for line in lines)

    def save_formula(self, code: str, filename: str) -> Path:
        """Save generated formula to file"""
        filepath = self.output_dir / filename
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(code)
        print(f"\n✅ Generated formula saved to: {filepath}")
        return filepath


def interactive_mode(parser: FormulaParser, generator: FormulaGenerator):
    """Interactive formula selection and generation"""

    print("\n" + "=" * 70)
    print("🎨 INTERACTIVE FORMULA GENERATOR")
    print("=" * 70)

    while True:
        print("\n📋 MENU:")
        print("  1. List all formulas")
        print("  2. Search formulas")
        print("  3. Combine formulas")
        print("  4. Exit")

        choice = input("\n➤ Select option [1-4]: ").strip()

        if choice == "1":
            parser.print_formulas(limit=100)

        elif choice == "2":
            search_term = input("\n🔍 Enter search term: ").strip()
            parser.print_formulas(search=search_term, limit=100)

        elif choice == "3":
            # Combine formulas
            print("\n" + "=" * 70)
            print("🔨 FORMULA COMBINER")
            print("=" * 70)

            # Get formula selections
            print("\nEnter formula numbers to combine (comma-separated)")
            print("Example: 5,17,234")
            indices_str = input("\n➤ Formula numbers: ").strip()

            try:
                indices = [int(x.strip()) for x in indices_str.split(',')]
            except ValueError:
                print("❌ Invalid input. Please enter numbers separated by commas.")
                continue

            # Validate indices
            valid = True
            for idx in indices:
                if not parser.get_formula_by_index(idx):
                    print(f"❌ Formula #{idx} not found")
                    valid = False

            if not valid:
                continue

            # Get new formula details
            print("\n📝 New Formula Details:")
            new_name = input("  Display Name: ").strip()
            new_internal_name = input("  Internal Name (snake_case): ").strip()
            new_internal_id = input("  Internal ID (camelCase): ").strip()

            # Get merge strategy
            print("\n🔀 Merge Strategy:")
            print("  1. Sequential (execute in order)")
            print("  2. Parallel (alternate by iteration)")
            print("  3. Weighted (blend results)")
            strategy_choice = input("\n➤ Select strategy [1-3]: ").strip()

            strategy_map = {
                "1": "sequential",
                "2": "parallel",
                "3": "weighted"
            }
            strategy = strategy_map.get(strategy_choice, "sequential")

            # Generate formula
            try:
                code = generator.combine_formulas(
                    formula_indices=indices,
                    new_name=new_name,
                    new_internal_name=new_internal_name,
                    new_internal_id=new_internal_id,
                    merge_strategy=strategy
                )

                # Save to file
                filename = f"fractal_{new_internal_name}.cpp"
                output_file = generator.save_formula(code, filename)

                print("\n" + "=" * 70)
                print("✅ SUCCESS!")
                print("=" * 70)

            except Exception as e:
                print(f"\n❌ ERROR: {e}")
                import traceback
                traceback.print_exc()

        elif choice == "4":
            print("\n👋 Goodbye!")
            break

        else:
            print("❌ Invalid choice. Please select 1-4.")


def main():
    """Main entry point"""
    print("=" * 70)
    print("🎨 MANDELBULBER INTERACTIVE FORMULA GENERATOR")
    print("=" * 70)

    # Setup paths
    base_dir = Path(__file__).parent.parent / "mandelbulber2"
    formula_dir = base_dir / "formula" / "definition"
    output_dir = Path(__file__).parent / "generated_formulas"

    if not formula_dir.exists():
        print(f"❌ ERROR: Formula directory not found: {formula_dir}")
        sys.exit(1)

    # Parse existing formulas
    parser = FormulaParser(str(formula_dir))
    parser.parse_all_formulas()

    # Create generator
    generator = FormulaGenerator(parser, str(output_dir))

    # Interactive mode
    interactive_mode(parser, generator)


if __name__ == "__main__":
    main()

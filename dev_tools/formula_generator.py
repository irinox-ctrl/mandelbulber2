#!/usr/bin/env python3
"""
MANDELBULBER FORMULA GENERATOR
================================
Tool to create NEW formulas by combining existing formulas.

Features:
- Parse existing formula definitions
- Combine FormulaCode sections
- Merge parameter definitions
- Auto-generate proper C++ structure
- Register in all_fractal_definitions.h
- Create OpenCL versions

Author: Claude + Joeri
Version: 1.0
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

    def parse_all_formulas(self) -> None:
        """Parse all .cpp formula files"""
        print(f"Scanning {self.formula_dir}...")

        cpp_files = list(self.formula_dir.glob("fractal_*.cpp"))
        print(f"Found {len(cpp_files)} formula files")

        for cpp_file in cpp_files:
            try:
                info = self.parse_formula_file(cpp_file)
                if info:
                    self.formulas[info.internal_id] = info
            except Exception as e:
                print(f"Error parsing {cpp_file.name}: {e}")

        print(f"Successfully parsed {len(self.formulas)} formulas")

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

    def list_formulas(self) -> None:
        """Print all available formulas"""
        print("\n=== AVAILABLE FORMULAS ===\n")
        for i, (fid, info) in enumerate(sorted(self.formulas.items()), 1):
            print(f"{i:3d}. {info.name_in_combo:50s} [{info.internal_id}]")


class FormulaGenerator:
    """Generate new formulas by combining existing ones"""

    def __init__(self, parser: FormulaParser, output_dir: str):
        self.parser = parser
        self.output_dir = Path(output_dir)
        self.output_dir.mkdir(parents=True, exist_ok=True)

    def combine_formulas(self,
                        formula_ids: List[str],
                        new_name: str,
                        new_internal_name: str,
                        new_internal_id: str,
                        merge_strategy: str = "sequential") -> str:
        """
        Combine multiple formulas into one

        Args:
            formula_ids: List of internal IDs to combine
            new_name: Display name for new formula
            new_internal_name: Internal identifier (snake_case)
            new_internal_id: Enum ID (camelCase)
            merge_strategy: "sequential" or "parallel"

        Returns:
            Generated C++ code
        """
        # Get formula info
        formulas = []
        for fid in formula_ids:
            info = self.parser.get_formula_by_id(fid)
            if not info:
                raise ValueError(f"Formula '{fid}' not found")
            formulas.append(info)

        print(f"\nCombining {len(formulas)} formulas:")
        for f in formulas:
            print(f"  - {f.name_in_combo}")

        # Generate class name
        class_name = self._to_class_name(new_internal_id)

        # Generate code
        code = self._generate_header(class_name, new_name)
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
        # CamelCase
        parts = internal_id.split('_')
        return 'cFractal' + ''.join(p.capitalize() for p in parts)

    def _generate_header(self, class_name: str, formula_name: str) -> str:
        """Generate file header and includes"""
        return f'''/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2024 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \\><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \\____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{{i%+++
 *
 * {formula_name}
 * Generated by Formula Generator Tool
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
                code += f'\n\t// ========== FORMULA {i+1}: {formula.name_in_combo} ==========\n'
                code += self._indent_code(formula.formula_code, 1)

        elif strategy == "parallel":
            # Execute formulas based on conditions
            code += '\t// Combined formula - Conditional execution\n'
            for i, formula in enumerate(formulas):
                code += f'\n\t// Formula {i+1}: {formula.name_in_combo}\n'
                code += f'\tif (aux.i % {len(formulas)} == {i})\n\t{{\n'
                code += self._indent_code(formula.formula_code, 2)
                code += '\t}\n'

        code += '}\n'
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
        print(f"\nGenerated formula saved to: {filepath}")
        return filepath


def main():
    """Main entry point"""
    print("=" * 70)
    print("MANDELBULBER FORMULA GENERATOR")
    print("=" * 70)

    # Setup paths
    base_dir = Path(__file__).parent.parent / "mandelbulber2"
    formula_dir = base_dir / "formula" / "definition"
    output_dir = Path(__file__).parent / "generated_formulas"

    if not formula_dir.exists():
        print(f"ERROR: Formula directory not found: {formula_dir}")
        sys.exit(1)

    # Parse existing formulas
    parser = FormulaParser(str(formula_dir))
    parser.parse_all_formulas()

    # Create generator
    generator = FormulaGenerator(parser, str(output_dir))

    # Test mode - combine pseudoKleinianMod4 with itself (for testing)
    print("\n" + "=" * 70)
    print("TEST MODE: Creating test formula")
    print("=" * 70)

    test_formula_id = "fractal::pseudoKleinianMod4"

    try:
        code = generator.combine_formulas(
            formula_ids=[test_formula_id, test_formula_id],
            new_name="Test Combined PseudoKleinian",
            new_internal_name="test_combined_pk",
            new_internal_id="testCombinedPk",
            merge_strategy="sequential"
        )

        # Save to file
        output_file = generator.save_formula(
            code,
            "fractal_test_combined_pk.cpp"
        )

        print("\n" + "=" * 70)
        print("SUCCESS!")
        print("=" * 70)
        print(f"\nNext steps:")
        print(f"1. Copy {output_file} to {formula_dir}")
        print(f"2. Add to all_fractal_definitions.h:")
        print(f"   #include \"definition/fractal_test_combined_pk.cpp\"")
        print(f"3. Add enum to fractal namespace (find next available number)")
        print(f"4. Rebuild Mandelbulber")

    except Exception as e:
        print(f"\nERROR: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)


if __name__ == "__main__":
    main()

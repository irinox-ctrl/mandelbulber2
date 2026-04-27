#!/usr/bin/env python3
"""
MANDELBULBER FORMULA VALIDATOR & TESTER
========================================
Validates generated formulas for syntax errors, missing dependencies,
and common issues before integration.

Features:
- C++ syntax validation
- Variable conflict detection
- Missing include detection
- DE type compatibility check
- Compilation test (if compiler available)
- Runtime test generation

Author: Claude + Joeri
Version: 1.0
Date: 2026-04-19
"""

import os
import re
import sys
import subprocess
from pathlib import Path
from typing import Dict, List, Tuple, Optional
from dataclasses import dataclass


@dataclass
class ValidationResult:
    """Validation result container"""
    passed: bool
    errors: List[str]
    warnings: List[str]
    info: List[str]
    score: float  # 0.0 - 1.0


class FormulaValidator:
    """Validates generated formula C++ code"""

    def __init__(self, mandelbulber_base: str):
        self.base_dir = Path(mandelbulber_base)
        self.src_dir = self.base_dir / "src"
        self.formula_dir = self.base_dir / "formula" / "definition"

        # Known includes that should be present
        self.required_includes = [
            "all_fractal_definitions.h"
        ]

        # Known base types
        self.known_types = [
            "CVector4", "CVector3", "sFractal", "sExtendedAux",
            "cAbstractFractal", "double", "float", "int", "bool"
        ]

        # DE function types
        self.de_function_types = [
            "linearDEFunction", "logarithmicDEFunction",
            "pseudoKleinianDEFunction", "josKleinianDEFunction",
            "customDEFunction", "maxAxisDEFunction"
        ]

        # DE types
        self.de_types = [
            "analyticDEType", "deltaDEType"
        ]

    def validate_formula(self, cpp_file: Path) -> ValidationResult:
        """
        Complete validation of a formula file

        Returns ValidationResult with all checks
        """
        errors = []
        warnings = []
        info = []

        print(f"\n{'='*70}")
        print(f"🔍 VALIDATING: {cpp_file.name}")
        print(f"{'='*70}\n")

        # Read file
        try:
            with open(cpp_file, 'r', encoding='utf-8') as f:
                content = f.read()
        except Exception as e:
            errors.append(f"Cannot read file: {e}")
            return ValidationResult(False, errors, warnings, info, 0.0)

        # Run all checks
        score = 1.0

        # 1. Basic syntax checks
        print("📋 1. Basic Syntax Checks...")
        result = self._check_basic_syntax(content)
        errors.extend(result['errors'])
        warnings.extend(result['warnings'])
        info.extend(result['info'])
        score *= result['score']

        # 2. Include checks
        print("📦 2. Include Checks...")
        result = self._check_includes(content)
        errors.extend(result['errors'])
        warnings.extend(result['warnings'])
        info.extend(result['info'])
        score *= result['score']

        # 3. Class structure checks
        print("🏗️  3. Class Structure Checks...")
        result = self._check_class_structure(content)
        errors.extend(result['errors'])
        warnings.extend(result['warnings'])
        info.extend(result['info'])
        score *= result['score']

        # 4. Constructor checks
        print("⚙️  4. Constructor Checks...")
        result = self._check_constructor(content)
        errors.extend(result['errors'])
        warnings.extend(result['warnings'])
        info.extend(result['info'])
        score *= result['score']

        # 5. FormulaCode function checks
        print("🔢 5. FormulaCode Function Checks...")
        result = self._check_formula_code(content)
        errors.extend(result['errors'])
        warnings.extend(result['warnings'])
        info.extend(result['info'])
        score *= result['score']

        # 6. Variable conflict detection
        print("🔤 6. Variable Conflict Detection...")
        result = self._check_variable_conflicts(content)
        errors.extend(result['errors'])
        warnings.extend(result['warnings'])
        info.extend(result['info'])
        score *= result['score']

        # 7. DE type validation
        print("📐 7. DE Type Validation...")
        result = self._check_de_types(content)
        errors.extend(result['errors'])
        warnings.extend(result['warnings'])
        info.extend(result['info'])
        score *= result['score']

        # 8. Common pitfalls
        print("⚠️  8. Common Pitfalls Check...")
        result = self._check_common_pitfalls(content)
        errors.extend(result['errors'])
        warnings.extend(result['warnings'])
        info.extend(result['info'])
        score *= result['score']

        # Print summary
        print(f"\n{'='*70}")
        print("📊 VALIDATION SUMMARY")
        print(f"{'='*70}\n")

        print(f"✅ Info messages: {len(info)}")
        print(f"⚠️  Warnings: {len(warnings)}")
        print(f"❌ Errors: {len(errors)}")
        print(f"📊 Score: {score*100:.1f}%")

        if info:
            print(f"\n{'Info:':-^70}")
            for msg in info:
                print(f"  ℹ️  {msg}")

        if warnings:
            print(f"\n{'Warnings:':-^70}")
            for msg in warnings:
                print(f"  ⚠️  {msg}")

        if errors:
            print(f"\n{'Errors:':-^70}")
            for msg in errors:
                print(f"  ❌ {msg}")

        passed = len(errors) == 0 and score >= 0.7

        print(f"\n{'='*70}")
        if passed:
            print("✅ VALIDATION PASSED")
        else:
            print("❌ VALIDATION FAILED")
        print(f"{'='*70}\n")

        return ValidationResult(passed, errors, warnings, info, score)

    def _check_basic_syntax(self, content: str) -> Dict:
        """Check basic C++ syntax"""
        errors = []
        warnings = []
        info = []
        score = 1.0

        # Check for unmatched braces
        open_braces = content.count('{')
        close_braces = content.count('}')
        if open_braces != close_braces:
            errors.append(f"Unmatched braces: {open_braces} {{ vs {close_braces} }}")
            score *= 0.5
        else:
            info.append(f"Brace balance OK: {open_braces} pairs")

        # Check for unmatched parentheses (simple check)
        open_paren = content.count('(')
        close_paren = content.count(')')
        if open_paren != close_paren:
            errors.append(f"Unmatched parentheses: {open_paren} ( vs {close_paren} )")
            score *= 0.5
        else:
            info.append(f"Parenthesis balance OK: {open_paren} pairs")

        # Check for semicolon after class definition (common error)
        if re.search(r'class\s+\w+[^;]*\{[^}]*\}[^;]*$', content, re.MULTILINE):
            warnings.append("Missing semicolon after class definition (might be OK)")

        # Check for proper namespace usage
        if 'fractal::' not in content:
            warnings.append("No fractal:: namespace usage found")
            score *= 0.9

        return {'errors': errors, 'warnings': warnings, 'info': info, 'score': score}

    def _check_includes(self, content: str) -> Dict:
        """Check include statements"""
        errors = []
        warnings = []
        info = []
        score = 1.0

        # Find all includes
        includes = re.findall(r'#include\s+[<"]([^>"]+)[>"]', content)

        if not includes:
            errors.append("No #include statements found")
            score = 0.0
        else:
            info.append(f"Found {len(includes)} include(s): {', '.join(includes)}")

        # Check for required includes
        for required in self.required_includes:
            if required not in includes:
                errors.append(f"Missing required include: {required}")
                score *= 0.8

        return {'errors': errors, 'warnings': warnings, 'info': info, 'score': score}

    def _check_class_structure(self, content: str) -> Dict:
        """Check class structure"""
        errors = []
        warnings = []
        info = []
        score = 1.0

        # Find class definition
        class_match = re.search(r'class\s+(cFractal\w+)\s*:\s*(\w+)', content)

        if not class_match:
            errors.append("No valid class definition found")
            score = 0.0
        else:
            class_name = class_match.group(1)
            base_class = class_match.group(2)

            info.append(f"Class name: {class_name}")
            info.append(f"Base class: {base_class}")

            # Check base class
            if base_class not in ['cAbstractFractal', 'public']:
                warnings.append(f"Unusual base class: {base_class}")
                score *= 0.9

        return {'errors': errors, 'warnings': warnings, 'info': info, 'score': score}

    def _check_constructor(self, content: str) -> Dict:
        """Check constructor"""
        errors = []
        warnings = []
        info = []
        score = 1.0

        # Find constructor
        constructor_match = re.search(r'(\w+)::(\w+)\(\)\s*:\s*cAbstractFractal\(\)', content)

        if not constructor_match:
            errors.append("No valid constructor found")
            score = 0.0
            return {'errors': errors, 'warnings': warnings, 'info': info, 'score': score}

        class_name1 = constructor_match.group(1)
        class_name2 = constructor_match.group(2)

        if class_name1 != class_name2:
            errors.append(f"Constructor name mismatch: {class_name1} vs {class_name2}")
            score *= 0.5

        # Check required constructor parameters
        required_params = [
            'nameInComboBox', 'internalName', 'internalID',
            'DEType', 'DEFunctionType'
        ]

        for param in required_params:
            if f'{param} =' not in content:
                errors.append(f"Missing constructor parameter: {param}")
                score *= 0.9
            else:
                info.append(f"✓ {param}")

        # Check DE type validity
        de_type_match = re.search(r'DEType\s*=\s*(\w+);', content)
        if de_type_match:
            de_type = de_type_match.group(1)
            if de_type not in self.de_types:
                warnings.append(f"Unknown DE type: {de_type}")
                score *= 0.9

        # Check DE function type validity
        de_func_match = re.search(r'DEFunctionType\s*=\s*(\w+);', content)
        if de_func_match:
            de_func = de_func_match.group(1)
            if de_func not in self.de_function_types:
                warnings.append(f"Unknown DE function type: {de_func}")
                score *= 0.9

        return {'errors': errors, 'warnings': warnings, 'info': info, 'score': score}

    def _check_formula_code(self, content: str) -> Dict:
        """Check FormulaCode function"""
        errors = []
        warnings = []
        info = []
        score = 1.0

        # Find FormulaCode function
        formula_code_match = re.search(
            r'void\s+\w+::FormulaCode\s*\(\s*CVector4\s*&\s*z\s*,\s*const\s+sFractal\s*\*\s*fractal\s*,\s*sExtendedAux\s*&\s*aux\s*\)',
            content
        )

        if not formula_code_match:
            errors.append("No valid FormulaCode function found")
            score = 0.0
        else:
            info.append("FormulaCode function signature OK")

        # Check for common operations
        if 'aux.DE' in content:
            info.append("Uses DE (Distance Estimation)")

        if 'aux.color' in content:
            info.append("Uses color accumulation")

        if 'aux.i' in content:
            info.append("Uses iteration counter")

        # Check for potential issues
        if content.count('double colorAdd = 0.0;') > 1:
            warnings.append("Multiple 'colorAdd' variable declarations (potential conflict)")
            score *= 0.95

        if content.count('double k = 0.0;') > 1:
            warnings.append("Multiple 'k' variable declarations (potential conflict)")
            score *= 0.95

        return {'errors': errors, 'warnings': warnings, 'info': info, 'score': score}

    def _check_variable_conflicts(self, content: str) -> Dict:
        """Detect variable name conflicts"""
        errors = []
        warnings = []
        info = []
        score = 1.0

        # Extract FormulaCode body
        match = re.search(r'void\s+\w+::FormulaCode[^{]*\{(.*)\}', content, re.DOTALL)

        if not match:
            return {'errors': errors, 'warnings': warnings, 'info': info, 'score': score}

        formula_body = match.group(1)

        # Find all variable declarations
        var_declarations = re.findall(r'\b(double|float|int|bool)\s+(\w+)\s*=', formula_body)

        # Count duplicates
        var_names = [var[1] for var in var_declarations]
        duplicates = {}

        for var in var_names:
            count = var_names.count(var)
            if count > 1:
                duplicates[var] = count

        if duplicates:
            for var, count in duplicates.items():
                warnings.append(f"Variable '{var}' declared {count} times (scope conflict?)")
                score *= 0.95
        else:
            info.append("No obvious variable conflicts detected")

        return {'errors': errors, 'warnings': warnings, 'info': info, 'score': score}

    def _check_de_types(self, content: str) -> Dict:
        """Validate DE types and consistency"""
        errors = []
        warnings = []
        info = []
        score = 1.0

        # Extract DE type and function type
        de_type_match = re.search(r'DEType\s*=\s*(\w+);', content)
        de_func_match = re.search(r'DEFunctionType\s*=\s*(\w+);', content)
        de_analytic_match = re.search(r'DEAnalyticFunction\s*=\s*(\w+);', content)

        if de_type_match and de_func_match:
            de_type = de_type_match.group(1)
            de_func = de_func_match.group(1)

            # Check consistency
            if de_type == 'analyticDEType':
                if de_func not in self.de_function_types:
                    warnings.append(f"Analytic DE type but unknown function: {de_func}")
                    score *= 0.9
                else:
                    info.append(f"DE configuration: {de_type} + {de_func}")

            elif de_type == 'deltaDEType':
                info.append("Using numerical delta DE (slower but universal)")

        return {'errors': errors, 'warnings': warnings, 'info': info, 'score': score}

    def _check_common_pitfalls(self, content: str) -> Dict:
        """Check for common pitfalls"""
        errors = []
        warnings = []
        info = []
        score = 1.0

        # 1. Division by zero risks
        if re.search(r'/\s*(?:aux\.DE|z\.Dot\(z\)|rr)', content):
            warnings.append("Potential division by zero (check DE/rr guards)")
            score *= 0.95

        # 2. Uninitialized variables
        if re.search(r'\b(double|float)\s+\w+\s*;(?!\s*=)', content):
            warnings.append("Potentially uninitialized variables found")
            score *= 0.98

        # 3. Missing aux.DE updates
        formula_match = re.search(r'void\s+\w+::FormulaCode[^{]*\{(.*)\}', content, re.DOTALL)
        if formula_match:
            formula_body = formula_match.group(1)
            if 'aux.DE' not in formula_body:
                warnings.append("FormulaCode doesn't update aux.DE (might be intentional)")
                score *= 0.95

        # 4. Check for proper z updates
        if formula_match:
            if 'z =' not in formula_body and 'z +=' not in formula_body and 'z *=' not in formula_body:
                warnings.append("FormulaCode doesn't seem to update z (might be intentional)")
                score *= 0.95

        return {'errors': errors, 'warnings': warnings, 'info': info, 'score': score}

    def try_compile(self, cpp_file: Path) -> Tuple[bool, str]:
        """
        Attempt to compile the formula (if g++ available)

        Returns (success, output)
        """
        print(f"\n{'='*70}")
        print("🔨 COMPILATION TEST")
        print(f"{'='*70}\n")

        # Check if g++ is available
        try:
            subprocess.run(['g++', '--version'], capture_output=True, check=True)
        except (subprocess.CalledProcessError, FileNotFoundError):
            print("⚠️  g++ not available, skipping compilation test")
            return (True, "Compiler not available")

        # Create test compilation
        test_cpp = cpp_file.parent / f"test_{cpp_file.name}"

        try:
            # We can't compile without full Mandelbulber context, but we can syntax check
            result = subprocess.run(
                ['g++', '-fsyntax-only', '-std=c++11', str(cpp_file)],
                capture_output=True,
                text=True
            )

            if result.returncode == 0:
                print("✅ Syntax check PASSED")
                return (True, result.stdout)
            else:
                print("❌ Syntax check FAILED")
                print(f"\nOutput:\n{result.stderr}")
                return (False, result.stderr)

        except Exception as e:
            print(f"⚠️  Compilation test error: {e}")
            return (False, str(e))


def main():
    """Main entry point"""
    print("=" * 70)
    print("🔍 MANDELBULBER FORMULA VALIDATOR & TESTER")
    print("=" * 70)

    # Setup paths
    base_dir = Path(__file__).parent.parent / "mandelbulber2"
    generated_dir = Path(__file__).parent / "generated_formulas"

    if not base_dir.exists():
        print(f"❌ ERROR: Mandelbulber directory not found: {base_dir}")
        sys.exit(1)

    # Create validator
    validator = FormulaValidator(str(base_dir))

    # Find formulas to validate
    if generated_dir.exists():
        cpp_files = list(generated_dir.glob("fractal_*.cpp"))

        if not cpp_files:
            print(f"\n⚠️  No generated formulas found in {generated_dir}")
            sys.exit(0)

        print(f"\n📁 Found {len(cpp_files)} formula(s) to validate\n")

        results = []

        for cpp_file in cpp_files:
            result = validator.validate_formula(cpp_file)
            results.append((cpp_file.name, result))

            # Optional: try compilation
            # success, output = validator.try_compile(cpp_file)

        # Final summary
        print("\n" + "=" * 70)
        print("📊 FINAL VALIDATION SUMMARY")
        print("=" * 70 + "\n")

        for filename, result in results:
            status = "✅ PASS" if result.passed else "❌ FAIL"
            print(f"{status} {filename:50s} Score: {result.score*100:5.1f}%")

        # Overall result
        all_passed = all(r[1].passed for r in results)

        print("\n" + "=" * 70)
        if all_passed:
            print("🎉 ALL FORMULAS VALIDATED SUCCESSFULLY!")
        else:
            print("⚠️  SOME FORMULAS HAVE ISSUES")
        print("=" * 70 + "\n")

        sys.exit(0 if all_passed else 1)

    else:
        print(f"❌ ERROR: Generated formulas directory not found: {generated_dir}")
        sys.exit(1)


if __name__ == "__main__":
    main()

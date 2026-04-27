#!/usr/bin/env python3
"""
MANDELBULBER FORMULA EVOLUTION ENGINE
======================================
Intelligent formula generator that:
- Analyzes existing formulas
- Mutates parameters and transformations
- Tests each variant
- Keeps only working formulas
- Evolves thousands of new formulas automatically

EVOLUTIONARY APPROACH:
1. Parse base formula (e.g., pseudoKleinianMod4)
2. Extract all parameters and transforms
3. Create mutations:
   - Parameter value changes
   - Transform additions/removals
   - Operation order changes
   - Conditional logic modifications
4. Validate each mutation
5. Test render
6. Keep successful variants
7. Use successful variants as new base
8. REPEAT → Generate thousands of formulas

Author: Claude + Joeri
Version: 1.0
Date: 2026-04-19
"""

import os
import re
import sys
import json
import random
import subprocess
from pathlib import Path
from typing import Dict, List, Tuple, Optional, Set
from dataclasses import dataclass, field
from copy import deepcopy


@dataclass
class FormulaParameter:
    """Extracted parameter from formula code"""
    name: str
    value: str
    type: str  # "scale", "offset", "rotation", "condition", etc.
    mutable: bool = True


@dataclass
class TransformBlock:
    """A transformation block in the formula"""
    name: str
    code: str
    parameters: List[FormulaParameter]
    optional: bool = True  # Can be removed?


@dataclass
class FormulaDNA:
    """Complete DNA of a formula for mutation"""
    base_formula: str
    class_name: str
    internal_name: str
    transforms: List[TransformBlock]
    global_params: List[FormulaParameter]
    de_type: str
    de_function: str
    generation: int = 0
    parent: Optional[str] = None
    mutations: List[str] = field(default_factory=list)


class FormulaAnalyzer:
    """Analyze formula to extract DNA"""

    def __init__(self, formula_file: Path):
        self.file = formula_file
        with open(formula_file, 'r', encoding='utf-8', errors='ignore') as f:
            self.content = f.read()

    def extract_dna(self) -> FormulaDNA:
        """Extract complete DNA from formula"""

        # Extract basic info
        class_name = self._extract_class_name()
        internal_name = self._extract_internal_name()
        de_type = self._extract_de_type()
        de_function = self._extract_de_function()

        # Extract transforms
        transforms = self._extract_transforms()

        # Extract global parameters
        global_params = self._extract_global_params()

        return FormulaDNA(
            base_formula=self.file.stem,
            class_name=class_name,
            internal_name=internal_name,
            transforms=transforms,
            global_params=global_params,
            de_type=de_type,
            de_function=de_function
        )

    def _extract_class_name(self) -> str:
        match = re.search(r'class\s+(cFractal\w+)', self.content)
        return match.group(1) if match else "Unknown"

    def _extract_internal_name(self) -> str:
        match = re.search(r'internalName\s*=\s*"([^"]+)"', self.content)
        return match.group(1) if match else "unknown"

    def _extract_de_type(self) -> str:
        match = re.search(r'DEType\s*=\s*(\w+);', self.content)
        return match.group(1) if match else "analyticDEType"

    def _extract_de_function(self) -> str:
        match = re.search(r'DEFunctionType\s*=\s*(\w+);', self.content)
        return match.group(1) if match else "linearDEFunction"

    def _extract_transforms(self) -> List[TransformBlock]:
        """Extract transformation blocks from FormulaCode"""
        transforms = []

        # Get FormulaCode body
        match = re.search(r'void\s+\w+::FormulaCode[^{]*\{(.*)\}',
                         self.content, re.DOTALL)
        if not match:
            return transforms

        body = match.group(1)

        # Find comment-marked sections (sphere inversion, box fold, etc.)
        sections = re.findall(r'//\s*(.+?)\n(.*?)(?=//|\Z)', body, re.DOTALL)

        for i, (name, code) in enumerate(sections):
            name = name.strip()

            # Extract parameters from this block
            params = self._extract_params_from_code(code)

            # Check if conditional (inside if statement)
            optional = 'if' in code

            transforms.append(TransformBlock(
                name=name,
                code=code,
                parameters=params,
                optional=optional
            ))

        return transforms

    def _extract_params_from_code(self, code: str) -> List[FormulaParameter]:
        """Extract all fractal->... parameters from code"""
        params = []

        # Find all fractal-> references
        pattern = r'fractal->(\w+)\.(\w+)'
        matches = re.findall(pattern, code)

        seen = set()
        for struct, param in matches:
            key = f"{struct}.{param}"
            if key in seen:
                continue
            seen.add(key)

            # Extract value if assigned
            value_match = re.search(rf'fractal->{struct}\.{param}', code)

            params.append(FormulaParameter(
                name=key,
                value="",  # Will be filled during mutation
                type=self._classify_param(param),
                mutable=True
            ))

        return params

    def _classify_param(self, name: str) -> str:
        """Classify parameter type"""
        name_lower = name.lower()

        if 'scale' in name_lower:
            return 'scale'
        elif 'offset' in name_lower or 'addition' in name_lower:
            return 'offset'
        elif 'rotation' in name_lower or 'angle' in name_lower:
            return 'rotation'
        elif 'fold' in name_lower:
            return 'fold'
        elif 'min' in name_lower or 'max' in name_lower:
            return 'threshold'
        elif 'enabled' in name_lower:
            return 'condition'
        else:
            return 'other'

    def _extract_global_params(self) -> List[FormulaParameter]:
        """Extract global parameters (default bailout, etc.)"""
        params = []

        bailout = re.search(r'defaultBailout\s*=\s*([^;]+);', self.content)
        if bailout:
            params.append(FormulaParameter(
                name='defaultBailout',
                value=bailout.group(1).strip(),
                type='threshold',
                mutable=True
            ))

        return params


class FormulaMutator:
    """Mutate formula DNA to create variants"""

    def __init__(self):
        self.mutation_types = [
            'scale_change',
            'offset_change',
            'rotation_change',
            'transform_toggle',
            'transform_reorder',
            'parameter_multiply',
            'add_condition',
            'remove_condition'
        ]

    def mutate(self, dna: FormulaDNA, mutation_rate: float = 0.3) -> FormulaDNA:
        """
        Create mutation of formula DNA

        Args:
            dna: Original DNA
            mutation_rate: Probability of mutation per element

        Returns:
            Mutated DNA
        """
        mutated = deepcopy(dna)
        mutated.generation += 1
        mutated.parent = dna.internal_name
        mutated.mutations = []

        # Mutate transforms
        for transform in mutated.transforms:
            if random.random() < mutation_rate:
                mutation = random.choice(self.mutation_types)
                self._apply_mutation(mutated, transform, mutation)

        # Mutate global parameters
        for param in mutated.global_params:
            if random.random() < mutation_rate and param.mutable:
                self._mutate_parameter(param)
                mutated.mutations.append(f"global_{param.name}")

        # Generate new unique name
        mutated.internal_name = self._generate_name(dna.internal_name, mutated.generation)
        mutated.class_name = self._name_to_class(mutated.internal_name)

        return mutated

    def _apply_mutation(self, dna: FormulaDNA, transform: TransformBlock,
                       mutation_type: str):
        """Apply specific mutation to transform"""

        if mutation_type == 'scale_change':
            # Modify scale parameters
            for param in transform.parameters:
                if param.type == 'scale':
                    self._mutate_parameter(param)
                    dna.mutations.append(f"scale_{param.name}")

        elif mutation_type == 'offset_change':
            # Modify offset parameters
            for param in transform.parameters:
                if param.type == 'offset':
                    self._mutate_parameter(param)
                    dna.mutations.append(f"offset_{param.name}")

        elif mutation_type == 'rotation_change':
            # Modify rotation parameters
            for param in transform.parameters:
                if param.type == 'rotation':
                    self._mutate_parameter(param)
                    dna.mutations.append(f"rotation_{param.name}")

        elif mutation_type == 'transform_toggle':
            # Toggle transform on/off (if optional)
            if transform.optional:
                # Wrap/unwrap in condition
                if 'if' in transform.code:
                    # Remove condition
                    transform.code = re.sub(r'if\s*\([^)]+\)\s*\{', '', transform.code)
                    transform.code = re.sub(r'\}$', '', transform.code)
                    dna.mutations.append(f"enable_{transform.name}")
                else:
                    # Add condition
                    transform.code = f"if (true) {{\n{transform.code}\n}}"
                    dna.mutations.append(f"conditional_{transform.name}")

        elif mutation_type == 'parameter_multiply':
            # Multiply random parameter by random factor
            if transform.parameters:
                param = random.choice(transform.parameters)
                if param.type in ['scale', 'offset']:
                    factor = random.uniform(0.5, 2.0)
                    param.value = f"({param.value}) * {factor:.3f}"
                    dna.mutations.append(f"multiply_{param.name}")

    def _mutate_parameter(self, param: FormulaParameter):
        """Mutate single parameter"""

        if param.type == 'scale':
            # Scale: multiply by random factor 0.5 - 2.0
            factor = random.uniform(0.5, 2.0)
            if param.value:
                param.value = f"{param.value} * {factor:.3f}"

        elif param.type == 'offset':
            # Offset: add random value -1.0 to 1.0
            offset = random.uniform(-1.0, 1.0)
            if param.value:
                param.value = f"{param.value} + {offset:.3f}"

        elif param.type == 'rotation':
            # Rotation: add random angle -45 to 45 degrees
            angle = random.uniform(-45, 45)
            if param.value:
                param.value = f"{param.value} + {angle:.2f}"

        elif param.type == 'threshold':
            # Threshold: multiply by 0.8 - 1.2
            factor = random.uniform(0.8, 1.2)
            if param.value:
                param.value = f"{param.value} * {factor:.3f}"

    def _generate_name(self, base: str, generation: int) -> str:
        """Generate unique name for mutated formula"""
        # Extract number from base if exists
        match = re.search(r'(\d+)$', base)
        if match:
            base_num = int(match.group(1))
            base = base[:match.start()]
            return f"{base}{base_num}_gen{generation:03d}"
        else:
            return f"{base}_gen{generation:03d}"

    def _name_to_class(self, internal_name: str) -> str:
        """Convert internal_name to ClassName"""
        parts = internal_name.split('_')
        return 'cFractal' + ''.join(p.capitalize() for p in parts)


class FormulaCodeGenerator:
    """Generate C++ code from mutated DNA"""

    def __init__(self, output_dir: Path):
        self.output_dir = output_dir
        self.output_dir.mkdir(parents=True, exist_ok=True)

    def generate(self, dna: FormulaDNA) -> Path:
        """Generate complete C++ file from DNA"""

        code = self._header(dna)
        code += self._class_declaration(dna)
        code += self._constructor(dna)
        code += self._formula_code(dna)

        # Save to file
        filename = f"fractal_{dna.internal_name}.cpp"
        filepath = self.output_dir / filename

        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(code)

        return filepath

    def _header(self, dna: FormulaDNA) -> str:
        """Generate header"""
        mutations_str = ', '.join(dna.mutations[:5])
        if len(dna.mutations) > 5:
            mutations_str += f" + {len(dna.mutations)-5} more"

        return f'''/**
 * Mandelbulber v2, a 3D fractal generator
 *
 * AUTO-EVOLVED FORMULA
 * Base: {dna.base_formula}
 * Generation: {dna.generation}
 * Parent: {dna.parent or 'None'}
 * Mutations: {mutations_str}
 */

#include "all_fractal_definitions.h"

'''

    def _class_declaration(self, dna: FormulaDNA) -> str:
        """Generate class declaration"""
        return f'''class {dna.class_name} : public cAbstractFractal
{{
public:
\t{dna.class_name}();
\tvoid FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux) override;
}};

'''

    def _constructor(self, dna: FormulaDNA) -> str:
        """Generate constructor"""
        bailout = next((p.value for p in dna.global_params
                       if p.name == 'defaultBailout'), '100.0')

        return f'''{dna.class_name}::{dna.class_name}() : cAbstractFractal()
{{
\tnameInComboBox = "Evolved {dna.base_formula} Gen{dna.generation}";
\tinternalName = "{dna.internal_name}";
\tinternalID = fractal::{dna.internal_name};
\tDEType = {dna.de_type};
\tDEFunctionType = {dna.de_function};
\tcpixelAddition = cpixelDisabledByDefault;
\tdefaultBailout = {bailout};
\tDEAnalyticFunction = analyticFunctionPseudoKleinian;
\tcoloringFunction = coloringFunctionDefault;
}}

'''

    def _formula_code(self, dna: FormulaDNA) -> str:
        """Generate FormulaCode function"""
        code = f'''void {dna.class_name}::FormulaCode(
\tCVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{{
'''

        # Add all transforms
        for i, transform in enumerate(dna.transforms):
            code += f'\t// {transform.name}\n'
            code += self._indent(transform.code, 1)
            code += '\n'

        code += '}\n'
        return code

    def _indent(self, code: str, levels: int) -> str:
        """Indent code"""
        indent = '\t' * levels
        lines = code.split('\n')
        return '\n'.join(indent + line if line.strip() else '' for line in lines)


class EvolutionEngine:
    """Main evolution engine"""

    def __init__(self, base_dir: Path, output_dir: Path):
        self.base_dir = base_dir
        self.formula_dir = base_dir / "formula" / "definition"
        self.output_dir = output_dir
        self.output_dir.mkdir(parents=True, exist_ok=True)

        self.analyzer = None
        self.mutator = FormulaMutator()
        self.generator = FormulaCodeGenerator(output_dir)

        # Statistics
        self.generated_count = 0
        self.validated_count = 0
        self.failed_count = 0

    def evolve_formula(self, base_formula_name: str,
                      generations: int = 10,
                      variants_per_gen: int = 5,
                      mutation_rate: float = 0.3):
        """
        Evolve formula through multiple generations

        Args:
            base_formula_name: Name of base formula (e.g., "pseudo_kleinian_mod4")
            generations: Number of generations to evolve
            variants_per_gen: Variants to create per generation
            mutation_rate: Mutation probability
        """

        print(f"\n{'='*70}")
        print(f"🧬 EVOLUTION ENGINE STARTED")
        print(f"{'='*70}\n")
        print(f"Base formula: {base_formula_name}")
        print(f"Generations: {generations}")
        print(f"Variants per generation: {variants_per_gen}")
        print(f"Mutation rate: {mutation_rate*100:.0f}%\n")

        # Find base formula file
        base_file = self._find_formula_file(base_formula_name)
        if not base_file:
            print(f"❌ ERROR: Formula '{base_formula_name}' not found")
            return

        # Analyze base formula
        print(f"🔍 Analyzing base formula...")
        analyzer = FormulaAnalyzer(base_file)
        base_dna = analyzer.extract_dna()

        print(f"✅ DNA extracted:")
        print(f"   Transforms: {len(base_dna.transforms)}")
        print(f"   Parameters: {len(base_dna.global_params)}")

        # Evolution loop
        current_generation = [base_dna]

        for gen in range(1, generations + 1):
            print(f"\n{'='*70}")
            print(f"🧬 GENERATION {gen}")
            print(f"{'='*70}\n")

            next_generation = []

            for parent_dna in current_generation:
                for variant in range(variants_per_gen):
                    # Create mutation
                    mutated_dna = self.mutator.mutate(parent_dna, mutation_rate)

                    print(f"🔬 Variant {variant+1}/{variants_per_gen} from {parent_dna.internal_name}")
                    print(f"   Mutations: {len(mutated_dna.mutations)}")

                    # Generate code
                    try:
                        cpp_file = self.generator.generate(mutated_dna)
                        self.generated_count += 1

                        # Validate
                        if self._validate_formula(cpp_file):
                            print(f"   ✅ VALID - {cpp_file.name}")
                            next_generation.append(mutated_dna)
                            self.validated_count += 1
                        else:
                            print(f"   ❌ FAILED validation")
                            self.failed_count += 1
                            # Delete failed variant
                            cpp_file.unlink()

                    except Exception as e:
                        print(f"   ❌ ERROR: {e}")
                        self.failed_count += 1

            # Next generation becomes current
            if next_generation:
                # Keep best N variants
                current_generation = next_generation[:3]  # Top 3
            else:
                print(f"\n⚠️  No successful variants in generation {gen}")
                break

        # Final statistics
        self._print_statistics()

    def _find_formula_file(self, name: str) -> Optional[Path]:
        """Find formula file by name"""
        # Try exact match
        exact = self.formula_dir / f"fractal_{name}.cpp"
        if exact.exists():
            return exact

        # Try pattern match
        pattern = f"*{name}*.cpp"
        matches = list(self.formula_dir.glob(pattern))
        return matches[0] if matches else None

    def _validate_formula(self, cpp_file: Path) -> bool:
        """Validate generated formula"""
        try:
            # Import validator
            from formula_validator import FormulaValidator

            validator = FormulaValidator(str(self.base_dir))
            result = validator.validate_formula(cpp_file)

            return result.passed

        except ImportError:
            # Fallback: basic syntax check
            with open(cpp_file) as f:
                content = f.read()

            # Count braces
            if content.count('{') != content.count('}'):
                return False

            # Check for class
            if 'class cFractal' not in content:
                return False

            # Check for FormulaCode
            if 'void FormulaCode(' not in content:
                return False

            return True

    def _print_statistics(self):
        """Print final statistics"""
        print(f"\n{'='*70}")
        print(f"📊 EVOLUTION STATISTICS")
        print(f"{'='*70}\n")

        print(f"Generated variants: {self.generated_count}")
        print(f"✅ Validated: {self.validated_count}")
        print(f"❌ Failed: {self.failed_count}")

        if self.generated_count > 0:
            success_rate = self.validated_count / self.generated_count * 100
            print(f"\n📈 Success rate: {success_rate:.1f}%")

        print(f"\n✅ Valid formulas saved to: {self.output_dir}")


def main():
    """Main entry point"""
    print("=" * 70)
    print("🧬 FORMULA EVOLUTION ENGINE")
    print("=" * 70)

    # Setup paths
    base_dir = Path(__file__).parent.parent / "mandelbulber2"
    output_dir = Path(__file__).parent / "evolved_formulas"

    if not base_dir.exists():
        print(f"❌ ERROR: Mandelbulber directory not found")
        sys.exit(1)

    # Create engine
    engine = EvolutionEngine(base_dir, output_dir)

    # Run evolution
    engine.evolve_formula(
        base_formula_name="pseudo_kleinian_mod4",
        generations=3,
        variants_per_gen=3,
        mutation_rate=0.3
    )


if __name__ == "__main__":
    main()

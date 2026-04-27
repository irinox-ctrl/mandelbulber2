#!/usr/bin/env python3
"""
SMART FORMULA EVOLUTION ENGINE V2
===================================
INTELLIGENT evolution with:
- Formula type recognition
- Valid parameter ranges per type
- Mathematical operation injection
- Context-aware mutations
- Type-safe transformations

INTELLIGENTIE:
1. Herkent formule type (Power, IFS, Kleinian, Transform)
2. Kent geldige parameter ranges per type
3. Injecteert alleen passende wiskunde
4. Valideert voor generatie
5. Leert van successen

Author: Claude + Joeri
Version: 2.0
Date: 2026-04-19
"""

import os
import re
import sys
import json
import random
from pathlib import Path
from typing import Dict, List, Tuple, Optional, Set
from dataclasses import dataclass, field
from enum import Enum


class FormulaType(Enum):
    """Formula categories met eigen regels"""
    POWER = "power"              # Mandelbulb, Mandelbrot
    IFS = "ifs"                  # Menger, Koch, Sierpinski
    KLEINIAN = "kleinian"        # Pseudo-Kleinian variants
    TRANSFORM = "transform"      # Rotations, folds, scales
    HYBRID = "hybrid"            # Mixed types
    UNKNOWN = "unknown"


class MathOperation(Enum):
    """Toegestane wiskundige operaties"""
    # Basic
    ADD = "+"
    SUBTRACT = "-"
    MULTIPLY = "*"
    DIVIDE = "/"

    # Power
    POWER = "pow"
    SQUARE = "square"
    SQRT = "sqrt"

    # Trigonometric
    SIN = "sin"
    COS = "cos"
    TAN = "tan"
    ASIN = "asin"
    ACOS = "acos"
    ATAN = "atan"

    # Hyperbolic
    SINH = "sinh"
    COSH = "cosh"
    TANH = "tanh"

    # Exponential
    EXP = "exp"
    LOG = "log"

    # Special
    ABS = "fabs"
    SIGN = "sign"
    MIN = "min"
    MAX = "max"
    CLAMP = "clamp"
    MIX = "mix"


@dataclass
class ParameterConstraint:
    """Parameter constraints per type"""
    name: str
    type: str
    min_value: float
    max_value: float
    safe_range: Tuple[float, float]  # Veilige range voor mutatie
    formula_types: List[FormulaType]  # Voor welke types geldig


@dataclass
class MathInjection:
    """Mathematical operation injection"""
    operation: MathOperation
    target: str  # Wat te vervangen (z, z.x, aux.DE, etc.)
    formula_types: List[FormulaType]  # Voor welke types veilig
    probability: float  # Kans van injectie


class FormulaTypeClassifier:
    """Classificeer formules in types"""

    def __init__(self):
        # Keywords per type
        self.type_keywords = {
            FormulaType.POWER: [
                'power', 'mandelbulb', 'mandelbrot', 'julia',
                'bulb', 'pow', 'exponent'
            ],
            FormulaType.IFS: [
                'menger', 'koch', 'sierpinski', 'ifs',
                'sponge', 'gasket', 'tree'
            ],
            FormulaType.KLEINIAN: [
                'kleinian', 'apollonian', 'circle',
                'sphere_inversion', 'mobius'
            ],
            FormulaType.TRANSFORM: [
                'transf', 'rotation', 'fold', 'scale',
                'offset', 'benesi', 'box_fold'
            ]
        }

    def classify(self, formula_name: str, code: str) -> FormulaType:
        """Classificeer formule type"""
        name_lower = formula_name.lower()
        code_lower = code.lower()

        scores = {ft: 0 for ft in FormulaType}

        # Check keywords in naam en code
        for formula_type, keywords in self.type_keywords.items():
            for keyword in keywords:
                if keyword in name_lower:
                    scores[formula_type] += 3
                if keyword in code_lower:
                    scores[formula_type] += 1

        # Check code patterns
        if 'pow(' in code_lower:
            scores[FormulaType.POWER] += 2
        if 'fabs(z' in code_lower and 'swap' in code_lower:
            scores[FormulaType.IFS] += 2
        if 'sphere' in code_lower and 'inversion' in code_lower:
            scores[FormulaType.KLEINIAN] += 2

        # Vind hoogste score
        max_score = max(scores.values())
        if max_score == 0:
            return FormulaType.UNKNOWN

        best_type = max(scores.items(), key=lambda x: x[1])[0]
        return best_type


class ParameterRulesEngine:
    """Definieer geldige parameter ranges per formule type"""

    def __init__(self):
        self.constraints = self._build_constraints()

    def _build_constraints(self) -> List[ParameterConstraint]:
        """Bouw parameter constraint database"""
        return [
            # SCALE parameters
            ParameterConstraint(
                name="scale",
                type="scale",
                min_value=0.01,
                max_value=10.0,
                safe_range=(0.5, 3.0),
                formula_types=[FormulaType.POWER, FormulaType.IFS, FormulaType.KLEINIAN]
            ),

            # OFFSET parameters
            ParameterConstraint(
                name="offset",
                type="offset",
                min_value=-5.0,
                max_value=5.0,
                safe_range=(-2.0, 2.0),
                formula_types=[FormulaType.POWER, FormulaType.IFS, FormulaType.KLEINIAN, FormulaType.TRANSFORM]
            ),

            # ROTATION parameters (degrees)
            ParameterConstraint(
                name="rotation",
                type="rotation",
                min_value=-180.0,
                max_value=180.0,
                safe_range=(-90.0, 90.0),
                formula_types=[FormulaType.POWER, FormulaType.TRANSFORM]
            ),

            # BAILOUT parameters
            ParameterConstraint(
                name="bailout",
                type="threshold",
                min_value=1.0,
                max_value=1000.0,
                safe_range=(2.0, 100.0),
                formula_types=[FormulaType.POWER, FormulaType.KLEINIAN]
            ),

            # MIN RADIUS (voor sphere folding)
            ParameterConstraint(
                name="minR",
                type="threshold",
                min_value=0.01,
                max_value=2.0,
                safe_range=(0.1, 1.0),
                formula_types=[FormulaType.IFS, FormulaType.KLEINIAN]
            ),

            # FIXED RADIUS
            ParameterConstraint(
                name="fixedR",
                type="threshold",
                min_value=0.1,
                max_value=5.0,
                safe_range=(0.5, 2.0),
                formula_types=[FormulaType.IFS, FormulaType.KLEINIAN]
            ),

            # POWER exponent
            ParameterConstraint(
                name="power",
                type="power",
                min_value=2.0,
                max_value=20.0,
                safe_range=(2.0, 12.0),
                formula_types=[FormulaType.POWER]
            ),

            # FOLD limit
            ParameterConstraint(
                name="foldingLimit",
                type="threshold",
                min_value=0.1,
                max_value=5.0,
                safe_range=(0.5, 2.0),
                formula_types=[FormulaType.IFS, FormulaType.TRANSFORM]
            ),
        ]

    def get_constraint(self, param_type: str, formula_type: FormulaType) -> Optional[ParameterConstraint]:
        """Vind constraint voor parameter type en formule type"""
        for constraint in self.constraints:
            if constraint.type == param_type and formula_type in constraint.formula_types:
                return constraint
        return None

    def get_safe_value(self, param_type: str, formula_type: FormulaType, current_value: float = None) -> float:
        """Generate veilige waarde voor parameter"""
        constraint = self.get_constraint(param_type, formula_type)

        if not constraint:
            # Fallback voor unknown types
            if current_value is not None:
                return current_value * random.uniform(0.8, 1.2)
            return random.uniform(0.5, 2.0)

        min_val, max_val = constraint.safe_range

        if current_value is not None:
            # Muteer binnen veilige range
            variation = (max_val - min_val) * 0.2
            new_value = current_value + random.uniform(-variation, variation)
            return max(min_val, min(max_val, new_value))
        else:
            # Nieuwe random waarde in safe range
            return random.uniform(min_val, max_val)


class MathInjector:
    """Inject wiskundige operaties in formules"""

    def __init__(self):
        self.injections = self._build_injection_rules()

    def _build_injection_rules(self) -> List[MathInjection]:
        """Definieer veilige math injecties per type"""
        return [
            # POWER FRACTALS - trigonometrie is veilig
            MathInjection(
                operation=MathOperation.SIN,
                target="z",
                formula_types=[FormulaType.POWER],
                probability=0.2
            ),
            MathInjection(
                operation=MathOperation.COS,
                target="z",
                formula_types=[FormulaType.POWER],
                probability=0.2
            ),

            # IFS - absolute values en min/max veilig
            MathInjection(
                operation=MathOperation.ABS,
                target="z",
                formula_types=[FormulaType.IFS, FormulaType.TRANSFORM],
                probability=0.3
            ),
            MathInjection(
                operation=MathOperation.MAX,
                target="z.x",
                formula_types=[FormulaType.IFS],
                probability=0.15
            ),

            # KLEINIAN - log/exp voorzichtig
            MathInjection(
                operation=MathOperation.LOG,
                target="rr",
                formula_types=[FormulaType.KLEINIAN],
                probability=0.1
            ),

            # ALLE TYPES - square veilig
            MathInjection(
                operation=MathOperation.SQUARE,
                target="z",
                formula_types=[FormulaType.POWER, FormulaType.IFS, FormulaType.KLEINIAN],
                probability=0.15
            ),

            # TRANSFORMS - mix operations
            MathInjection(
                operation=MathOperation.MIX,
                target="z",
                formula_types=[FormulaType.TRANSFORM],
                probability=0.1
            ),
        ]

    def get_valid_injections(self, formula_type: FormulaType) -> List[MathInjection]:
        """Krijg geldige injecties voor formule type"""
        return [inj for inj in self.injections if formula_type in inj.formula_types]

    def inject_operation(self, code: str, formula_type: FormulaType) -> Tuple[str, List[str]]:
        """
        Injecteer wiskundige operatie in code

        Returns:
            (modified_code, list of mutations)
        """
        valid_injections = self.get_valid_injections(formula_type)

        if not valid_injections:
            return code, []

        mutations = []
        modified_code = code

        for injection in valid_injections:
            if random.random() < injection.probability:
                # Inject operatie
                modified_code, mutation = self._apply_injection(
                    modified_code, injection
                )
                if mutation:
                    mutations.append(mutation)

        return modified_code, mutations

    def _apply_injection(self, code: str, injection: MathInjection) -> Tuple[str, Optional[str]]:
        """Apply specific injection"""
        target = injection.target
        op = injection.operation

        # Find target in code
        pattern = rf'\b{re.escape(target)}\b(?!\w)'

        if not re.search(pattern, code):
            return code, None

        # Choose injection strategy based on operation
        if op == MathOperation.SIN:
            replacement = f'CVector4(sin({target}.x), sin({target}.y), sin({target}.z), {target}.w)'
            mutation = f"inject_sin_{target}"

        elif op == MathOperation.COS:
            replacement = f'CVector4(cos({target}.x), cos({target}.y), cos({target}.z), {target}.w)'
            mutation = f"inject_cos_{target}"

        elif op == MathOperation.ABS:
            replacement = f'fabs({target})'
            mutation = f"inject_abs_{target}"

        elif op == MathOperation.SQUARE:
            replacement = f'({target} * {target})'
            mutation = f"inject_square_{target}"

        elif op == MathOperation.LOG:
            # Veilig met guard
            replacement = f'({target} > 0.0001 ? log({target}) : 0.0)'
            mutation = f"inject_log_{target}"

        elif op == MathOperation.MAX:
            replacement = f'max({target}, 0.0)'
            mutation = f"inject_max_{target}"

        else:
            return code, None

        # Apply eerste match only (veilig)
        modified = re.sub(pattern, replacement, code, count=1)

        if modified != code:
            return modified, mutation

        return code, None



    def __init__(self):
        self.classifier = FormulaTypeClassifier()
        self.param_rules = ParameterRulesEngine()
        self.math_injector = MathInjector()

    def mutate_smart(self, dna: 'FormulaDNA', mutation_rate: float = 0.3) -> 'FormulaDNA':
        """
        Slimme mutatie met type-awareness
        """
        from formula_evolution_engine import FormulaDNA, TransformBlock, FormulaParameter
        from copy import deepcopy

        mutated = deepcopy(dna)
        mutated.generation += 1
        mutated.parent = dna.internal_name
        mutated.mutations = []

        # Classificeer formule type
        full_code = '\n'.join(t.code for t in dna.transforms)
        formula_type = self.classifier.classify(dna.base_formula, full_code)

        print(f"   📊 Classified as: {formula_type.value}")

        # Muteer parameters met type-awareness
        for transform in mutated.transforms:
            for param in transform.parameters:
                if random.random() < mutation_rate and param.mutable:
                    # Gebruik type-aware mutation
                    self._mutate_parameter_smart(param, formula_type)
                    mutated.mutations.append(f"smart_{param.type}_{param.name}")

        # Inject mathematics
        if random.random() < mutation_rate:
            for i, transform in enumerate(mutated.transforms):
                modified_code, math_mutations = self.math_injector.inject_operation(
                    transform.code, formula_type
                )
                if math_mutations:
                    transform.code = modified_code
                    mutated.mutations.extend(math_mutations)

        # Generate nieuwe naam
        mutated.internal_name = self._generate_name(dna.internal_name, mutated.generation)
        mutated.class_name = self._name_to_class(mutated.internal_name)

        return mutated

    def _mutate_parameter_smart(self, param: 'FormulaParameter', formula_type: FormulaType):
        """Muteer parameter met type constraints"""

        # Probeer constraint te vinden
        constraint = self.param_rules.get_constraint(param.type, formula_type)

        if constraint:
            # Gebruik safe range
            try:
                current = float(param.value) if param.value else None
            except:
                current = None

            new_value = self.param_rules.get_safe_value(param.type, formula_type, current)
            param.value = f"{new_value:.4f}"

        else:
            # Fallback: conservatieve mutatie
            if param.type == 'scale':
                factor = random.uniform(0.7, 1.4)
                if param.value:
                    param.value = f"{param.value} * {factor:.3f}"

            elif param.type == 'offset':
                offset = random.uniform(-0.5, 0.5)
                if param.value:
                    param.value = f"{param.value} + {offset:.3f}"

    def _generate_name(self, base: str, generation: int) -> str:
        """Generate unique name"""
        match = re.search(r'(\d+)$', base)
        if match:
            base_num = int(match.group(1))
            base = base[:match.start()]
            return f"{base}{base_num}_smart_gen{generation:03d}"
        else:
            return f"{base}_smart_gen{generation:03d}"

    def _name_to_class(self, internal_name: str) -> str:
        """Convert to class name"""
        parts = internal_name.split('_')
        return 'cFractal' + ''.join(p.capitalize() for p in parts)


def main():
    """Test smart evolution"""
    print("=" * 70)
    print("🧠 SMART FORMULA EVOLUTION ENGINE V2")
    print("=" * 70)

    # Test classifier
    classifier = FormulaTypeClassifier()

    test_cases = [
        ("pseudo_kleinian_mod4", "sphere inversion kleinian"),
        ("mandelbulb_power2", "pow(z, 8) mandelbulb"),
        ("menger_sponge", "fabs(z) swap IFS"),
        ("transf_rotation", "rotation fold transform"),
    ]

    print("\n🔬 TESTING CLASSIFIER:\n")
    for name, code in test_cases:
        ftype = classifier.classify(name, code)
        print(f"  {name:30s} → {ftype.value:15s}")

    # Test parameter rules
    rules = ParameterRulesEngine()

    print("\n📏 TESTING PARAMETER RULES:\n")
    for formula_type in [FormulaType.POWER, FormulaType.IFS, FormulaType.KLEINIAN]:
        safe_scale = rules.get_safe_value('scale', formula_type)
        safe_offset = rules.get_safe_value('offset', formula_type)
        print(f"  {formula_type.value:15s} → scale: {safe_scale:.3f}, offset: {safe_offset:.3f}")

    # Test math injector
    injector = MathInjector()

    print("\n➕ TESTING MATH INJECTION:\n")
    test_code = "z = z * scale + offset;"

    for formula_type in [FormulaType.POWER, FormulaType.IFS]:
        modified, mutations = injector.inject_operation(test_code, formula_type)
        print(f"  {formula_type.value:15s} → mutations: {mutations}")
        if mutations:
            print(f"    Code: {modified[:60]}...")

    print("\n" + "=" * 70)
    print("✅ SMART EVOLUTION SYSTEM READY!")
    print("=" * 70)


if __name__ == "__main__":
    main()

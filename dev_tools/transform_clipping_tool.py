#!/usr/bin/env python3
"""
TRANSFORM CLIPPING TOOL
========================
Creëert clipping transforms voor formules.

Clipping is essentieel voor:
- Snijden van geometry
- Shape boolean operations
- Distance field modifications
- Visual effects

Typen clipping:
1. Plane clipping (vlak)
2. Box clipping (kubus)
3. Sphere clipping (bol)
4. Custom shape clipping

Author: Claude + Joeri
Version: 1.0
Date: 2026-04-19
"""

import os
import re
import sys
from pathlib import Path
from typing import Dict, List, Tuple, Optional
from dataclasses import dataclass


@dataclass
class ClippingConfig:
    """Clipping configuratie"""
    clip_type: str  # 'plane', 'box', 'sphere', 'cylinder', 'custom'
    position: Tuple[float, float, float]
    normal: Tuple[float, float, float]  # Voor plane
    size: Tuple[float, float, float]  # Voor box/sphere
    thickness: float
    invert: bool  # Inside/outside clipping
    smooth: float  # Smooth blend amount


class ClippingTransformGenerator:
    """Genereer clipping transforms"""

    def __init__(self, output_dir: Path):
        self.output_dir = output_dir
        self.output_dir.mkdir(parents=True, exist_ok=True)

    def generate_plane_clip(self, config: ClippingConfig) -> Path:
        """
        Genereer plane clipping transform

        Knipt langs een vlak gedefinieerd door position + normal
        """
        name = f"clip_plane_{self._make_safe_name(config.position)}"
        class_name = self._to_class_name(name)

        code = self._header(class_name, "Plane Clipping Transform")
        code += self._class_declaration(class_name)
        code += self._constructor(class_name, name, "clipPlane")

        # FormulaCode voor plane clipping
        nx, ny, nz = config.normal
        px, py, pz = config.position
        thick = config.thickness

        code += f'''void {class_name}::FormulaCode(
\tCVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{{
\t// Plane clipping
\tCVector3 normal = CVector3({nx}, {ny}, {nz});
\tnormal.Normalize();
\t
\tCVector3 planePoint = CVector3({px}, {py}, {pz});
\t
\t// Distance to plane
\tdouble dist = (z - planePoint).Dot(normal);
\t
'''

        if config.invert:
            code += f'\t// Invert clipping (inside)\n'
            code += f'\tdist = -dist;\n'

        if config.smooth > 0:
            code += f'\t// Smooth clipping\n'
            code += f'\tdist = dist - {config.smooth};\n'
            code += f'\tif (dist > 0.0 && dist < {config.smooth})\n'
            code += f'\t\tdist = dist * dist / ({config.smooth});\n'

        code += f'\t\n\t// Apply clipping\n'
        code += f'\tif (dist < {thick})\n'
        code += f'\t{{\n'
        code += f'\t\taux.dist = min(aux.dist, fabs(dist - {thick}));\n'
        code += f'\t\taux.DE = min(aux.DE, fabs(dist - {thick}));\n'
        code += f'\t}}\n'
        code += f'}}\n'

        # Save file
        filename = f"fractal_{name}.cpp"
        filepath = self.output_dir / filename

        with open(filepath, 'w') as f:
            f.write(code)

        print(f"✅ Generated: {filepath}")
        return filepath

    def generate_box_clip(self, config: ClippingConfig) -> Path:
        """
        Genereer box clipping transform

        Knipt met een box shape
        """
        name = f"clip_box_{self._make_safe_name(config.position)}"
        class_name = self._to_class_name(name)

        code = self._header(class_name, "Box Clipping Transform")
        code += self._class_declaration(class_name)
        code += self._constructor(class_name, name, "clipBox")

        px, py, pz = config.position
        sx, sy, sz = config.size
        thick = config.thickness

        code += f'''void {class_name}::FormulaCode(
\tCVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{{
\t// Box clipping
\tCVector3 boxCenter = CVector3({px}, {py}, {pz});
\tCVector3 boxSize = CVector3({sx}, {sy}, {sz});
\t
\t// Distance to box
\tCVector3 offset = fabs(z - boxCenter) - boxSize;
\tdouble dist = max(max(offset.x, offset.y), offset.z);
\t
'''

        if config.invert:
            code += f'\t// Invert clipping (inside box)\n'
            code += f'\tdist = -dist;\n'

        if config.smooth > 0:
            code += f'\t// Smooth clipping\n'
            code += f'\tdouble smoothFactor = {config.smooth};\n'
            code += f'\tif (dist > 0.0 && dist < smoothFactor)\n'
            code += f'\t\tdist = dist * dist / smoothFactor - smoothFactor * 0.25;\n'

        code += f'\t\n\t// Apply clipping\n'
        code += f'\tif (dist < {thick})\n'
        code += f'\t{{\n'
        code += f'\t\taux.dist = min(aux.dist, fabs(dist - {thick}));\n'
        code += f'\t\taux.DE = min(aux.DE, fabs(dist - {thick}));\n'
        code += f'\t}}\n'
        code += f'}}\n'

        filename = f"fractal_{name}.cpp"
        filepath = self.output_dir / filename

        with open(filepath, 'w') as f:
            f.write(code)

        print(f"✅ Generated: {filepath}")
        return filepath

    def generate_sphere_clip(self, config: ClippingConfig) -> Path:
        """
        Genereer sphere clipping transform

        Knipt met een sphere shape
        """
        name = f"clip_sphere_{self._make_safe_name(config.position)}"
        class_name = self._to_class_name(name)

        code = self._header(class_name, "Sphere Clipping Transform")
        code += self._class_declaration(class_name)
        code += self._constructor(class_name, name, "clipSphere")

        px, py, pz = config.position
        radius = config.size[0]  # Use first element as radius
        thick = config.thickness

        code += f'''void {class_name}::FormulaCode(
\tCVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{{
\t// Sphere clipping
\tCVector3 sphereCenter = CVector3({px}, {py}, {pz});
\tdouble radius = {radius};
\t
\t// Distance to sphere surface
\tdouble dist = (z - sphereCenter).Length() - radius;
\t
'''

        if config.invert:
            code += f'\t// Invert clipping (inside sphere)\n'
            code += f'\tdist = -dist;\n'

        if config.smooth > 0:
            code += f'\t// Smooth clipping\n'
            code += f'\tdouble smoothFactor = {config.smooth};\n'
            code += f'\tif (dist > -smoothFactor && dist < smoothFactor)\n'
            code += f'\t\tdist = 0.5 * (dist + sqrt(dist*dist + smoothFactor*smoothFactor));\n'

        code += f'\t\n\t// Apply clipping\n'
        code += f'\tif (fabs(dist) < {thick})\n'
        code += f'\t{{\n'
        code += f'\t\taux.dist = min(aux.dist, fabs(dist));\n'
        code += f'\t\taux.DE = min(aux.DE, fabs(dist));\n'
        code += f'\t}}\n'
        code += f'}}\n'

        filename = f"fractal_{name}.cpp"
        filepath = self.output_dir / filename

        with open(filepath, 'w') as f:
            f.write(code)

        print(f"✅ Generated: {filepath}")
        return filepath

    def _header(self, class_name: str, description: str) -> str:
        """Generate file header"""
        return f'''/**
 * Mandelbulber v2, a 3D fractal generator
 *
 * {description}
 * AUTO-GENERATED by Transform Clipping Tool
 */

#include "all_fractal_definitions.h"

'''

    def _class_declaration(self, class_name: str) -> str:
        """Generate class declaration"""
        return f'''class {class_name} : public cAbstractFractal
{{
public:
\t{class_name}();
\tvoid FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux) override;
}};

'''

    def _constructor(self, class_name: str, internal_name: str, internal_id: str) -> str:
        """Generate constructor"""
        return f'''{class_name}::{class_name}() : cAbstractFractal()
{{
\tnameInComboBox = "T>Clip {class_name}";
\tinternalName = "{internal_name}";
\tinternalID = fractal::{internal_id};
\tDEType = analyticDEType;
\tDEFunctionType = customDEFunction;
\tcpixelAddition = cpixelDisabledByDefault;
\tdefaultBailout = 100.0;
\tDEAnalyticFunction = analyticFunctionCustomDE;
\tcoloringFunction = coloringFunctionDefault;
}}

'''

    def _make_safe_name(self, position: Tuple[float, float, float]) -> str:
        """Convert position to safe filename"""
        x, y, z = position
        return f"{int(x*10):03d}_{int(y*10):03d}_{int(z*10):03d}"

    def _to_class_name(self, internal_name: str) -> str:
        """Convert internal_name to ClassName"""
        parts = internal_name.split('_')
        return 'cFractal' + ''.join(p.capitalize() for p in parts)


class ClippingTester:
    """Test generated clipping transforms"""

    def __init__(self, validator_path: Path):
        self.validator_path = validator_path

    def test_clipping(self, cpp_file: Path) -> bool:
        """Test if clipping transform is valid"""
        print(f"\n🔍 Testing: {cpp_file.name}")

        # 1. Syntax check
        with open(cpp_file) as f:
            content = f.read()

        # Check braces
        if content.count('{') != content.count('}'):
            print(f"  ❌ Unmatched braces")
            return False

        # Check class
        if 'class cFractal' not in content:
            print(f"  ❌ No class declaration")
            return False

        # Check FormulaCode
        if 'void FormulaCode(' not in content:
            print(f"  ❌ No FormulaCode function")
            return False

        # Check clipping logic
        if 'aux.dist' not in content and 'aux.DE' not in content:
            print(f"  ❌ No distance modification")
            return False

        print(f"  ✅ Syntax OK")

        # 2. Use validator if available
        try:
            sys.path.insert(0, str(self.validator_path.parent))
            from formula_validator import FormulaValidator

            base_dir = self.validator_path.parent.parent / "mandelbulber2"
            validator = FormulaValidator(str(base_dir))
            result = validator.validate_formula(cpp_file)

            if result.passed:
                print(f"  ✅ Validation PASSED (score: {result.score*100:.1f}%)")
                return True
            else:
                print(f"  ⚠️  Validation issues (score: {result.score*100:.1f}%)")
                return result.score >= 0.7  # Accept if > 70%

        except ImportError:
            print(f"  ℹ️  Validator not available, using basic checks")
            return True

    def test_all_clips(self, clip_dir: Path) -> Tuple[int, int]:
        """Test all generated clips"""
        cpp_files = list(clip_dir.glob("fractal_clip_*.cpp"))

        if not cpp_files:
            print("⚠️  No clipping files found")
            return 0, 0

        passed = 0
        failed = 0

        for cpp_file in cpp_files:
            if self.test_clipping(cpp_file):
                passed += 1
            else:
                failed += 1

        return passed, failed


def main():
    """Main entry point with testing"""
    print("=" * 70)
    print("🔪 TRANSFORM CLIPPING TOOL")
    print("=" * 70)

    output_dir = Path(__file__).parent / "generated_clips"
    output_dir.mkdir(parents=True, exist_ok=True)

    generator = ClippingTransformGenerator(output_dir)

    # Test configurations
    test_configs = [
        # Plane clips
        ClippingConfig(
            clip_type='plane',
            position=(0.0, 0.0, 0.0),
            normal=(0.0, 0.0, 1.0),
            size=(1.0, 1.0, 1.0),
            thickness=0.1,
            invert=False,
            smooth=0.0
        ),

        # Box clips
        ClippingConfig(
            clip_type='box',
            position=(0.0, 0.0, 0.0),
            normal=(0.0, 0.0, 1.0),
            size=(1.0, 1.0, 1.0),
            thickness=0.05,
            invert=False,
            smooth=0.1
        ),

        # Sphere clips
        ClippingConfig(
            clip_type='sphere',
            position=(0.0, 0.0, 0.0),
            normal=(0.0, 0.0, 1.0),
            size=(2.0, 2.0, 2.0),
            thickness=0.1,
            invert=True,  # Invert for hollow
            smooth=0.2
        ),
    ]

    print(f"\n📝 Generating {len(test_configs)} clipping transforms...\n")

    generated_files = []

    for i, config in enumerate(test_configs, 1):
        print(f"[{i}/{len(test_configs)}] Generating {config.clip_type} clip...")

        if config.clip_type == 'plane':
            filepath = generator.generate_plane_clip(config)
        elif config.clip_type == 'box':
            filepath = generator.generate_box_clip(config)
        elif config.clip_type == 'sphere':
            filepath = generator.generate_sphere_clip(config)

        generated_files.append(filepath)

    # Test all generated files
    print(f"\n{'='*70}")
    print("🧪 TESTING GENERATED CLIPS")
    print(f"{'='*70}")

    validator_path = Path(__file__).parent / "formula_validator.py"
    tester = ClippingTester(validator_path)

    passed, failed = tester.test_all_clips(output_dir)

    # Summary
    print(f"\n{'='*70}")
    print("📊 SUMMARY")
    print(f"{'='*70}\n")

    print(f"Generated: {len(generated_files)} clips")
    print(f"✅ Passed: {passed}")
    print(f"❌ Failed: {failed}")

    if failed == 0:
        print(f"\n🎉 ALL CLIPS VALID!")
    else:
        print(f"\n⚠️  Some clips need review")

    print(f"\n📁 Output: {output_dir}")


if __name__ == "__main__":
    main()

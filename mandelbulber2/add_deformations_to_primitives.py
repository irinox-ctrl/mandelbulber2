#!/usr/bin/env python3
"""
Add deformation calls to all primitive distance functions
"""

import re

primitives_cl = '../opencl/engines/primitives.cl'

# Read file
with open(primitives_cl, 'r') as f:
    content = f.read()

# List of primitive functions to patch (excluding Water which has different signature)
primitives_to_patch = [
    'PrimitivePlane',
    'PrimitiveSphere',
    'PrimitiveRectangle',
    'PrimitiveCylinder',
    'PrimitiveCircle',
    'PrimitiveCone',
    'PrimitiveTorus',
    'PrimitivePrism',
    'PrimitiveEllipsoid'
]

for prim in primitives_to_patch:
    # Pattern: function declaration followed by point calculation
    pattern = rf'(float {prim}\(__global sPrimitiveCl \*primitive, float3 _point\)\s*\{{\s*float3 point = _point - primitive->object\.position;)'

    # Check if deformation already added
    if re.search(rf'{prim}.*ApplyAllDeformations', content, re.DOTALL):
        print(f"✓ {prim} already has deformations")
        continue

    # Add deformation call
    replacement = rf'\1\n\n\t// Apply deformations (bend/twist/taper)\n\tpoint = ApplyAllDeformations(point, primitive);'

    new_content = re.sub(pattern, replacement, content)

    if new_content != content:
        print(f"✓ Added deformations to {prim}")
        content = new_content
    else:
        print(f"✗ Could not patch {prim}")

# Write back
with open(primitives_cl, 'w') as f:
    f.write(content)

print("\nDone! Deformations added to all primitives.")

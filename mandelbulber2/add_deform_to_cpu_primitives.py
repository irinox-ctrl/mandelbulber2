#!/usr/bin/env python3
"""
Add CPU deformation code to all primitive distance functions
"""

import re

primitives_cpp = '../src/primitive.cpp'

# The deformation code to insert (AFTER rotation)
deformation_code = '''
	// Apply deformations AFTER rotation
	if (deformBendEnable && fabs(deformBendAngle) > 1e-5)
	{
		double k = deformBendAngle;
		if (deformBendAxis == 0)  // bend along X
		{
			double cx = cos(k * point.x), sx = sin(k * point.x);
			point = CVector3(sx/k, point.y, point.z + (1.0-cx)/k);
		}
		else if (deformBendAxis == 1)  // bend along Y
		{
			double cy = cos(k * point.y), sy = sin(k * point.y);
			point = CVector3(point.x, sy/k, point.z + (1.0-cy)/k);
		}
		else  // bend along Z
		{
			double cz = cos(k * point.z), sz = sin(k * point.z);
			point = CVector3(point.x + (1.0-cz)/k, point.y, sz/k);
		}
	}

	if (deformTwistEnable && fabs(deformTwistAngle) > 1e-5)
	{
		double k, c, s;
		if (deformTwistAxis == 0) {
			k = deformTwistAngle * point.x; c = cos(k); s = sin(k);
			point = CVector3(point.x, c*point.y - s*point.z, s*point.y + c*point.z);
		}
		else if (deformTwistAxis == 1) {
			k = deformTwistAngle * point.y; c = cos(k); s = sin(k);
			point = CVector3(c*point.x - s*point.z, point.y, s*point.x + c*point.z);
		}
		else {
			k = deformTwistAngle * point.z; c = cos(k); s = sin(k);
			point = CVector3(c*point.x - s*point.y, s*point.x + c*point.y, point.z);
		}
	}

	if (deformTaperEnable && fabs(deformTaperRate) > 1e-5)
	{
		double k;
		if (deformTaperAxis == 0) {
			k = max(1.0 + deformTaperRate * point.x, 0.01);
			point = CVector3(point.x, point.y*k, point.z*k);
		}
		else if (deformTaperAxis == 1) {
			k = max(1.0 + deformTaperRate * point.y, 0.01);
			point = CVector3(point.x*k, point.y, point.z*k);
		}
		else {
			k = max(1.0 + deformTaperRate * point.z, 0.01);
			point = CVector3(point.x*k, point.y*k, point.z);
		}
	}
'''

# List of primitives to patch (and their rotation patterns)
primitives_to_patch = [
    ('sPrimitiveSphere::PrimitiveDistance', r'point = rotationMatrix\.RotateVector\(point\);'),
    ('sPrimitiveCylinder::PrimitiveDistance', r'point = rotationMatrix\.RotateVector\(point\);'),
    ('sPrimitiveCircle::PrimitiveDistance', r'point = rotationMatrix\.RotateVector\(point\);'),
    ('sPrimitiveCone::PrimitiveDistance', r'point = rotationMatrix\.RotateVector\(point\);'),
    ('sPrimitiveTorus::PrimitiveDistance', r'point = rotationMatrix\.RotateVector\(point\);'),
    ('sPrimitivePrism::PrimitiveDistance', r'point = rotationMatrix\.RotateVector\(point\);'),
    ('sPrimitiveEllipsoid::PrimitiveDistance', r'point = rotationMatrix\.RotateVector\(point\);'),
    ('sPrimitivePlane::PrimitiveDistance', r'point = rotationMatrix\.RotateVector\(point\);'),
    ('sPrimitiveRectangle::PrimitiveDistance', r'point = rotationMatrix\.RotateVector\(point\);'),
]

with open(primitives_cpp, 'r') as f:
    content = f.read()

for prim_name, rotation_pattern in primitives_to_patch:
    # Find the function
    func_pattern = rf'(double {prim_name}.*?\{{.*?{rotation_pattern})'

    matches = list(re.finditer(func_pattern, content, re.DOTALL))

    for match in matches:
        section_start = match.start()
        section_end = match.end()

        # Check if deformation already added (within next 200 chars)
        check_section = content[section_end:section_end+200]

        if 'deformBendEnable' not in check_section:
            # Insert deformation code AFTER rotation
            before = content[:section_end]
            after = content[section_end:]
            content = before + deformation_code + after
            print(f"✓ Added deformation to {prim_name}")
        else:
            print(f"⊘ {prim_name} already has deformation")
        break  # Only process first match per primitive

# Write back
with open(primitives_cpp, 'w') as f:
    f.write(content)

print("\nDone! CPU deformations added to all primitives.")

#ifdef FAKE_LIGHTS

// Helper: 2D extrusion
static inline float Extrude2D(float d2d, float z)
{
	return sqrt(d2d * d2d + z * z);
}

// Helper: mod for patterns
static inline float SdfMod(float x, float y)
{
	return x - y * floor(x / y);
}

// Helper: Koch snowflake distance
static inline float KochSnowflakeDist(float x, float y, float size)
{
	x /= size;
	y /= size;
	for (int i = 0; i < 2; i++)
	{
		x = fabs(x);
		y = fabs(y);
		float dot = x * 0.5f + y * 0.86602540378f;
		if (dot > y)
		{
			float tx = dot;
			float ty = x * 0.86602540378f - y * 0.5f;
			x = tx;
			y = ty;
		}
		x = x * 3.0f - 2.0f;
		y = y * 3.0f;
		if (x < -1.0f) x = -2.0f - x;
	}
	return (y - 0.5f) * size;
}

// Helper: Menger sponge distance
static inline float MengerSpongeDist(float3 p, float size)
{
	float3 s = p / size;
	float d = fmax(fabs(s.x), fmax(fabs(s.y), fabs(s.z))) - 1.0f;
	for (int i = 0; i < 2; i++)
	{
		s.x = fabs(s.x);
		s.y = fabs(s.y);
		s.z = fabs(s.z);
		if (s.x < s.y) { float t = s.x; s.x = s.y; s.y = t; }
		if (s.x < s.z) { float t = s.x; s.x = s.z; s.z = t; }
		if (s.y < s.z) { float t = s.y; s.y = s.z; s.z = t; }
		s = s * 3.0f - (float3)(2.0f, 2.0f, 2.0f);
		if (s.z < -1.0f) s.z = -2.0f - s.z;
		if (s.y < -1.0f) s.y = -2.0f - s.y;
		if (s.x < -1.0f) s.x = -2.0f - s.x;
	}
	return d * size * pow(3.0f, -2.0f);
}

// Helper: Sierpinski tetrahedron distance
static inline float SierpinskiTetraDist(float3 p, float size)
{
	float3 s = p / size;
	for (int i = 0; i < 2; i++)
	{
		if (s.x + s.y < 0.0f) { float t = s.x; s.x = -s.y; s.y = -t; }
		if (s.x + s.z < 0.0f) { float t = s.x; s.x = -s.z; s.z = -t; }
		if (s.y + s.z < 0.0f) { float t = s.y; s.y = -s.z; s.z = -t; }
		s = s * 2.0f - (float3)(1.0f, 1.0f, 1.0f);
	}
	return (length(s) - 1.73205f) * size * pow(2.0f, -2.0f);
}

// Helper: Apollonian distance
static inline float ApollonianDist(float3 p, float size)
{
	float3 s = p / size;
	float scale = 1.0f;
	for (int i = 0; i < 3; i++)
	{
		s.x = fabs(s.x);
		s.y = fabs(s.y);
		s.z = fabs(s.z);
		float r2 = dot(s, s);
		if (r2 < 0.001f) r2 = 0.001f;
		s = s * (1.0f / r2);
		s = s * 2.5f - (float3)(1.0f, 1.0f, 1.0f);
		scale *= 2.5f;
	}
	return length(s) * size / scale;
}

// Apply universal shape modifiers to delta
static inline float3 ApplyShapeModifiers(float3 delta, __constant sClInConstants *consts)
{
	// 1. Fold symmetry (radial folding in XY plane)
	int fold = consts->params.common.fakeLightsShapeFoldSymmetry;
	if (fold > 1)
	{
		float angle = atan2(delta.y, delta.x);
		float r = length(delta.xy);
		float period = 2.0f * 3.14159265359f / (float)fold;
		angle = fmod(angle + period / 2.0f, period);
		if (angle < 0.0f) angle += period;
		angle -= period / 2.0f;
		delta.x = cos(angle) * r;
		delta.y = sin(angle) * r;
	}

	// 2. Taper: scale xz based on y
	float taperScale = 1.0f + consts->params.common.fakeLightsShapeTaper * delta.y;
	if (taperScale < 1e-10f) taperScale = 1e-10f;
	delta.x *= taperScale;
	delta.z *= taperScale;

	// 3. Twist: rotate xz around y
	float twistAngle = consts->params.common.fakeLightsShapeTwist * delta.y;
	float cosT = cos(twistAngle);
	float sinT = sin(twistAngle);
	float nx = delta.x * cosT - delta.z * sinT;
	float nz = delta.x * sinT + delta.z * cosT;
	delta.x = nx;
	delta.z = nz;

	// 4. Bend: curve space around a circle
	float bend = consts->params.common.fakeLightsShapeBend;
	if (fabs(bend) > 1e-10f)
	{
		float bendAngle = bend * delta.y;
		delta.y = sin(bendAngle) / bend;
		delta.x += (1.0f - cos(bendAngle)) / bend;
	}

	// 5. Repeat / Tiling
	float repeatX = consts->params.common.fakeLightsShapeRepeatX;
	float repeatY = consts->params.common.fakeLightsShapeRepeatY;
	float repeatZ = consts->params.common.fakeLightsShapeRepeatZ;
	if (repeatX > 1e-10f) delta.x = SdfMod(delta.x + repeatX * 0.5f, repeatX) - repeatX * 0.5f;
	if (repeatY > 1e-10f) delta.y = SdfMod(delta.y + repeatY * 0.5f, repeatY) - repeatY * 0.5f;
	if (repeatZ > 1e-10f) delta.z = SdfMod(delta.z + repeatZ * 0.5f, repeatZ) - repeatZ * 0.5f;

	// 6. Wobble
	float wobbleAmp = consts->params.common.fakeLightsShapeWobbleAmplitude;
	float wobbleFreq = consts->params.common.fakeLightsShapeWobbleFrequency;
	if (fabs(wobbleAmp) > 1e-10f && fabs(wobbleFreq) > 1e-10f)
	{
		delta.x += wobbleAmp * sin(wobbleFreq * delta.y);
		delta.y += wobbleAmp * sin(wobbleFreq * delta.z);
		delta.z += wobbleAmp * sin(wobbleFreq * delta.x);
	}

	// 7. Spiral: rotate xz around y, angle increases with radius
	float spiral = consts->params.common.fakeLightsShapeSpiral;
	if (fabs(spiral) > 1e-10f)
	{
		float r = length(delta.xz);
		float angle = spiral * r;
		float cosS = cos(angle);
		float sinS = sin(angle);
		float nx = delta.x * cosS - delta.z * sinS;
		float nz = delta.x * sinS + delta.z * cosS;
		delta.x = nx;
		delta.z = nz;
	}

	// 8. Wave: sinus displacement per axis
	float waveFreq = consts->params.common.fakeLightsShapeWaveFrequency;
	if (fabs(waveFreq) > 1e-10f)
	{
		delta.x += consts->params.common.fakeLightsShapeWaveX * sin(waveFreq * delta.x);
		delta.y += consts->params.common.fakeLightsShapeWaveY * sin(waveFreq * delta.y);
		delta.z += consts->params.common.fakeLightsShapeWaveZ * sin(waveFreq * delta.z);
	}

	// 9. Scale
	float scaleX = consts->params.common.fakeLightsShapeScaleX;
	float scaleY = consts->params.common.fakeLightsShapeScaleY;
	float scaleZ = consts->params.common.fakeLightsShapeScaleZ;
	if (fabs(scaleX) > 1e-10f) delta.x /= scaleX;
	if (fabs(scaleY) > 1e-10f) delta.y /= scaleY;
	if (fabs(scaleZ) > 1e-10f) delta.z /= scaleZ;

	// 8. Mirror
	if (consts->params.common.fakeLightsShapeMirrorX) delta.x = fabs(delta.x);
	if (consts->params.common.fakeLightsShapeMirrorY) delta.y = fabs(delta.y);
	if (consts->params.common.fakeLightsShapeMirrorZ) delta.z = fabs(delta.z);

	return delta;
}

float OrbitTrapShapeDistance(float4 z4, __constant sClInConstants *consts, sClCalcParams *calcParams)
{
	float dist = 0.0f;
	float3 z = z4.xyz;
	float3 orbitTrapPos = (calcParams != NULL) ? calcParams->orbitTrap : consts->params.common.fakeLightsOrbitTrap;
	float3 delta = z - orbitTrapPos;
	float thicknessDivisor = consts->params.common.fakeLightsThickness;
#ifdef FAKE_LIGHTS_POINT
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	dist = length(delta);
#endif

#ifdef FAKE_LIGHTS_LINE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	// Line with thickness (radius) - distance from Y axis with offset
	dist = length(delta.yz) - consts->params.common.fakeLightsOrbitTrapSize;
	thicknessDivisor = consts->params.common.fakeLightsShapeLineThickness;
#endif

#ifdef FAKE_LIGHTS_CIRCLE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float lengthYZ = length(delta.yz) - consts->params.common.fakeLightsOrbitTrapSize;
	dist = length((float2){lengthYZ, delta.x});
#endif

#ifdef FAKE_LIGHTS_SQUARE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;

	float dy = max(fabs(fabs(delta.y) - size), fabs(delta.z) - size);
	float dz = max(fabs(fabs(delta.z) - size), fabs(delta.y) - size);
	float deltaRect = min(dy, dz);
	dist = length((float2){deltaRect, delta.x});
#endif

#ifdef FAKE_LIGHTS_SPHERE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float lengthYZ = length(delta.yz) - consts->params.common.fakeLightsOrbitTrapSize;
	float distYZ = length((float2){lengthYZ, delta.x});

	float lengthXZ = length(delta.xz) - consts->params.common.fakeLightsOrbitTrapSize;
	float distXZ = length((float2){lengthXZ, delta.y});

	float lengthXY = length(delta.xy) - consts->params.common.fakeLightsOrbitTrapSize;
	float distXY = length((float2){lengthXY, delta.z});

	dist = min(min(distYZ, distXZ), distXY);
#endif

#ifdef FAKE_LIGHTS_CUBE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;

	float dy_x = max(fabs(fabs(delta.y) - size), fabs(delta.z) - size);
	float dz_x = max(fabs(fabs(delta.z) - size), fabs(delta.y) - size);
	float dx_z = max(fabs(fabs(delta.x) - size), fabs(delta.z) - size);
	float deltaRectYZ = min(dy_x, dz_x);
	float distYZ = length((float2){deltaRectYZ, fabs(fabs(delta.x) - size)});
	float distXZ = length((float2){dx_z, fabs(fabs(delta.y) - size)});

	dist = min(distYZ, distXZ);
#endif

#ifdef FAKE_LIGHTS_TRIANGLE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float angle = atan2(delta.z, delta.y);
	float radius = length(delta.yz);
	float triangleRadius = size * cos(M_PI_F / 3.0f) / cos(fmod(angle + M_PI_F / 3.0f, 2.0f * M_PI_F / 3.0f) - M_PI_F / 3.0f);
	dist = fabs(radius - triangleRadius) + fabs(delta.x);
#endif

#ifdef FAKE_LIGHTS_HEXAGON
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float angle = atan2(delta.z, delta.y);
	float radius = length(delta.yz);
	float hexRadius = size * cos(M_PI_F / 6.0f) / cos(fmod(angle + M_PI_F / 6.0f, M_PI_F / 3.0f) - M_PI_F / 6.0f);
	dist = fabs(radius - hexRadius) + fabs(delta.x);
#endif

#ifdef FAKE_LIGHTS_TORUS
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float majorRadius = size;
	float minorRadius = size * 0.3f;
	float lengthYZ = length(delta.yz) - majorRadius;
	dist = length((float2){lengthYZ, delta.x}) - minorRadius;
#endif

#ifdef FAKE_LIGHTS_CYLINDER
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float distYZ = length(delta.yz) - size;
	dist = max(distYZ, fabs(delta.x) - size);
#endif

#ifdef FAKE_LIGHTS_CONE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float coneRadius = size * (1.0f - fabs(delta.x) / (size * 2.0f));
	float distRadial = length(delta.yz) - coneRadius;
	dist = max(distRadial, fabs(delta.x) - size * 2.0f);
#endif

#ifdef FAKE_LIGHTS_PYRAMID
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float baseDist = max(fabs(delta.y), fabs(delta.z)) - size * (1.0f - fabs(delta.x) / (size * 2.0f));
	dist = max(baseDist, fabs(delta.x) - size * 2.0f);
#endif

#ifdef FAKE_LIGHTS_OCTAHEDRON
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	dist = (fabs(delta.x) + fabs(delta.y) + fabs(delta.z) - size);
#endif

#ifdef FAKE_LIGHTS_ELLIPSE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float lengthYZ = sqrt(delta.y * delta.y + (delta.z * 1.5f) * (delta.z * 1.5f)) - size;
	dist = sqrt(lengthYZ * lengthYZ + delta.x * delta.x);
#endif

#ifdef FAKE_LIGHTS_RECTANGLE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float dy = max(fabs(delta.y) - size * 1.5f, 0.0f);
	float dz = max(fabs(delta.z) - size * 0.7f, 0.0f);
	dist = sqrt(dy * dy + dz * dz + delta.x * delta.x);
#endif

#ifdef FAKE_LIGHTS_CROSS
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float armY = max(fabs(delta.y) - size, fabs(delta.z) - size * 0.3f);
	float armZ = max(fabs(delta.z) - size, fabs(delta.y) - size * 0.3f);
	dist = min(armY, armZ) + fabs(delta.x);
#endif

#ifdef FAKE_LIGHTS_STAR
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float angle = atan2(delta.z, delta.y);
	float radius = length(delta.yz);
	float starRadius = size * (0.5f + 0.5f * cos(5.0f * angle));
	dist = fabs(radius - starRadius) + fabs(delta.x);
#endif

#ifdef FAKE_LIGHTS_DIAMOND
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	dist = (fabs(delta.y) + fabs(delta.z) - size * 1.414f) + fabs(delta.x);
#endif

#ifdef FAKE_LIGHTS_RING
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float radius = length(delta.yz);
	dist = fabs(radius - size);
#endif

#ifdef FAKE_LIGHTS_CAPSULE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float radius = size * 0.3f;
	float lengthYZ = length(delta.yz);
	float distYZ = max(lengthYZ - size, 0.0f);
	dist = length((float2){distYZ, delta.x}) - radius;
#endif

#ifdef FAKE_LIGHTS_PRISM
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float q = fabs(delta.y) * 0.866025f + delta.z * 0.5f;
	dist = max(q, -delta.z) - size * 0.5f;
#endif

#ifdef FAKE_LIGHTS_TORUS_KNOT
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float p = 2.0f, q = 3.0f;
	float r = length(delta.yz);
	float theta = atan2(delta.z, delta.y);
	float majorRadius = size;
	float minorRadius = size * 0.2f;
	float knotX = (majorRadius + minorRadius * cos(q * theta)) * cos(p * theta);
	float knotY = (majorRadius + minorRadius * cos(q * theta)) * sin(p * theta);
	float knotZ = minorRadius * sin(q * theta);
	dist = sqrt(pow(r - sqrt(knotX * knotX + knotY * knotY), 2) + pow(delta.x - knotZ, 2));
#endif

#ifdef FAKE_LIGHTS_BOX_FRAME
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float thickness = size * 0.2f;
	float onEdgeX = (fabs(delta.x) > size - thickness && fabs(delta.y) < size && fabs(delta.z) < size) ? fabs(fabs(delta.x) - size) : 1000.0f;
	float onEdgeY = (fabs(delta.y) > size - thickness && fabs(delta.x) < size && fabs(delta.z) < size) ? fabs(fabs(delta.y) - size) : 1000.0f;
	float onEdgeZ = (fabs(delta.z) > size - thickness && fabs(delta.x) < size && fabs(delta.y) < size) ? fabs(fabs(delta.z) - size) : 1000.0f;
	dist = min(min(onEdgeX, onEdgeY), onEdgeZ);
#endif

#ifdef FAKE_LIGHTS_CONE_INFINITE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float coneAngle = 0.3f;
	float distRadial = length(delta.yz) - fabs(delta.x) * coneAngle;
	dist = distRadial;
#endif

#ifdef FAKE_LIGHTS_CYLINDER_CAP
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float radius = size * 0.3f;
	float distYZ = length(delta.yz) - radius;
	float distX = fabs(delta.x) - size;
	dist = max(distYZ, distX);
#endif

#ifdef FAKE_LIGHTS_SUPERELLIPSOID
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float e = 0.5f;
	dist = pow(pow(fabs(delta.x), e) + pow(fabs(delta.y), e) + pow(fabs(delta.z), e), 1.0f / e) - size;
#endif

#ifdef FAKE_LIGHTS_PLANE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	dist = fabs(delta.x) - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_DISC
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float r = length(delta.yz);
	dist = max(fabs(delta.x) - size * 0.1f, r - size);
#endif

#ifdef FAKE_LIGHTS_GEAR
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float angle = atan2(delta.z, delta.y);
	float r = length(delta.yz);
	float gearRadius = size * (0.7f + 0.3f * cos(6.0f * angle));
	dist = fabs(r - gearRadius) + fabs(delta.x) * 0.1f;
#endif

#ifdef FAKE_LIGHTS_SPIRAL
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float angle = atan2(delta.z, delta.y);
	float r = length(delta.yz);
	float spiralRadius = size * (0.1f + 0.9f * fmod(angle / (2.0f * M_PI_F) + 3.0f, 1.0f));
	dist = fabs(r - spiralRadius) + fabs(delta.x) * 0.1f;
#endif

#ifdef FAKE_LIGHTS_HEART
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float hy = delta.y / size;
	float hz = delta.z / size;
	float heart = pow(hy * hy + hz * hz - 1.0f, 3) - hy * hy * hz * hz * hz;
	dist = fabs(heart) * size * 0.1f + fabs(delta.x) * 0.1f;
#endif

#ifdef FAKE_LIGHTS_CRESCENT
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float r1 = length(delta.yz) - size;
	float r2 = length((float2){delta.y - size * 0.5f, delta.z}) - size * 0.8f;
	dist = max(r1, -r2) + fabs(delta.x) * 0.1f;
#endif

#ifdef FAKE_LIGHTS_ARROW
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float ay = delta.y / size;
	float az = delta.z / size;
	float shaft = max(fabs(ay) - 1.0f, fabs(az) - 0.15f);
	float head = max(max(-ay - 0.3f, fabs(az) - (0.7f + ay)), ay - 0.3f);
	dist = min(shaft, head) * size + fabs(delta.x) * 0.1f;
#endif

#ifdef FAKE_LIGHTS_ROUNDED_BOX
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float radius = size * 0.2f;
	float3 d = fabs(delta) - size + radius;
	dist = length(max(d, 0.0f)) + min(max(d.x, max(d.y, d.z)), 0.0f) - radius;
#endif

#ifdef FAKE_LIGHTS_POLYGON_5
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float sizeP5 = consts->params.common.fakeLightsOrbitTrapSize;
	float angleP5 = atan2(delta.z, delta.y);
	float rP5 = length(delta.yz);
	float polyRadiusP5 = sizeP5 * cos(3.14159265359f / 5.0f) / cos(fmod(angleP5 + 3.14159265359f / 5.0f, 2.0f * 3.14159265359f / 5.0f) - 3.14159265359f / 5.0f);
	dist = fabs(rP5 - polyRadiusP5) + fabs(delta.x) * 0.1f;
#endif

#ifdef FAKE_LIGHTS_POLYGON_8
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float sizeP8 = consts->params.common.fakeLightsOrbitTrapSize;
	float angleP8 = atan2(delta.z, delta.y);
	float rP8 = length(delta.yz);
	float polyRadiusP8 = sizeP8 * cos(3.14159265359f / 8.0f) / cos(fmod(angleP8 + 3.14159265359f / 8.0f, 3.14159265359f / 4.0f) - 3.14159265359f / 8.0f);
	dist = fabs(rP8 - polyRadiusP8) + fabs(delta.x) * 0.1f;
#endif

#ifdef FAKE_LIGHTS_STADIUM
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float dy = max(fabs(delta.y) - size * 2.0f, 0.0f);
	float dz = fabs(delta.z) - size;
	dist = sqrt(dy * dy + max(dz, 0.0f) * max(dz, 0.0f)) + min(0.0f, dz) + fabs(delta.x) * 0.1f;
#endif

#ifdef FAKE_LIGHTS_TREFOIL_KNOT
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float t = atan2(delta.z, delta.y);
	float r = length(delta.yz);
	float majorR = size;
	float minorR = size * 0.25f;
	float knotY = (majorR + minorR * cos(3.0f * t)) * cos(2.0f * t);
	float knotZ = (majorR + minorR * cos(3.0f * t)) * sin(2.0f * t);
	float distYZ = fabs(r - sqrt(knotY * knotY + knotZ * knotZ));
	dist = sqrt(distYZ * distYZ + delta.x * delta.x) - minorR * 0.5f;
#endif

#ifdef FAKE_LIGHTS_FIGURE_EIGHT
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float fy = delta.y / size;
	float fz = delta.z / size;
	float curveY = sin(fy * 2.0f);
	float curveZ = sin(fy * 4.0f) * 0.5f;
	dist = sqrt((fz - curveZ) * (fz - curveZ) + (fy - curveY) * (fy - curveY)) * size + fabs(delta.x) * 0.1f;
#endif

#ifdef FAKE_LIGHTS_MOBIUS_STRIP
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float r = length(delta.xy);
	float angle = atan2(delta.y, delta.x);
	float width = size * 0.3f;
	float distToCenter = fabs(r - size);
	float twist = delta.z - width * sin(angle * 0.5f);
	dist = sqrt(distToCenter * distToCenter + twist * twist) - width * 0.1f;
#endif

#ifdef FAKE_LIGHTS_TORUS_SECTOR
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float angle = atan2(delta.z, delta.y);
	float r = length(delta.yz);
	float sector = (angle > 0.0f && angle < M_PI_F / 2.0f) ? 0.0f : min(fabs(angle), fabs(angle - M_PI_F / 2.0f));
	float majorR = size;
	float minorR = size * 0.3f;
	float distToTube = fabs(r - majorR);
	dist = sqrt(distToTube * distToTube + delta.x * delta.x + sector * majorR) - minorR;
#endif

#ifdef FAKE_LIGHTS_HELIX
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float t = delta.x / size * 2.0f;
	float helixY = cos(t) * size;
	float helixZ = sin(t) * size;
	dist = length((float2){delta.y - helixY, delta.z - helixZ}) - size * 0.2f;
#endif

#ifdef FAKE_LIGHTS_CONE_ROUNDED
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float h = size * 2.0f;
	float r = size;
	float y = delta.y + h * 0.5f;
	float coneR = r * (1.0f - y / h);
	float distRadial = length(delta.xz) - coneR;
	float distHeight = max(y - h, -y);
	dist = max(distRadial, distHeight);
#endif

#ifdef FAKE_LIGHTS_CYLINDER_HOLLOW
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float outerR = size;
	float innerR = size * 0.7f;
	float r = length(delta.yz);
	dist = max(fabs(r - (outerR + innerR) * 0.5f) - (outerR - innerR) * 0.5f, fabs(delta.x) - size * 2.0f);
#endif

#ifdef FAKE_LIGHTS_SPHERE_HOLLOW
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float outerR = size;
	float innerR = size * 0.8f;
	float r = length(delta);
	dist = fabs(r - (outerR + innerR) * 0.5f) - (outerR - innerR) * 0.5f;
#endif

#ifdef FAKE_LIGHTS_TORUS_TWIST
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float angle = atan2(delta.z, delta.y);
	float r = length(delta.yz);
	float twist = angle * 2.0f;
	float majorR = size;
	float minorR = size * 0.3f;
	float twistedX = delta.x * cos(twist) - (r - majorR) * sin(twist);
	float twistedR = delta.x * sin(twist) + (r - majorR) * cos(twist);
	dist = sqrt(twistedX * twistedX + twistedR * twistedR) - minorR;
#endif

#ifdef FAKE_LIGHTS_GRID
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// 2D Grid lines in XY plane
	float gx = fabs(fmod(delta.x, size) - size * 0.5f);
	float gy = fabs(fmod(delta.y, size) - size * 0.5f);
	float lineWidth = size * 0.15f;
	// Distance to grid lines
	float distToLine = min(gx, gy);
	dist = max(distToLine - lineWidth, fabs(delta.z) * 0.5f);
#endif

#ifdef FAKE_LIGHTS_LATTICE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// 3D Grid/Lattice structure
	float gx = fabs(fmod(delta.x, size) - size * 0.5f);
	float gy = fabs(fmod(delta.y, size) - size * 0.5f);
	float gz = fabs(fmod(delta.z, size) - size * 0.5f);
	float lineWidth = size * 0.12f;
	// Distance to nearest grid line in all 3 axes
	dist = min(min(gx, gy), gz) - lineWidth;
#endif

#ifdef FAKE_LIGHTS_SPONGE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float scale = 1.0f;
	float d = length(delta);
	for (int i = 0; i < 3; i++)
	{
		scale *= 3.0f;
		float px = fabs(fmod(delta.x * scale, 3.0f) - 1.5f);
		float py = fabs(fmod(delta.y * scale, 3.0f) - 1.5f);
		float pz = fabs(fmod(delta.z * scale, 3.0f) - 1.5f);
		if (px > pz) { float t = px; px = pz; pz = t; }
		if (px > py) { float t = px; px = py; py = t; }
		if (pz > py) { float t = pz; pz = py; py = t; }
		if (py > 1.0f)
		{
			d = min(d, (py - 1.0f) / scale);
		}
	}
	dist = d - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_KNOT_34
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float sizeK34 = consts->params.common.fakeLightsOrbitTrapSize;
	float tK34 = atan2(delta.y, delta.x);
	float rK34 = length(delta.xy);
	float RK34 = sizeK34;
	float PK34 = 3.0f;
	float QK34 = 4.0f;
	float pxK34 = (RK34 + sizeK34 * 0.3f * cos(QK34 * tK34)) * cos(PK34 * tK34);
	float pyK34 = (RK34 + sizeK34 * 0.3f * cos(QK34 * tK34)) * sin(PK34 * tK34);
	float pzK34 = sizeK34 * 0.3f * sin(QK34 * tK34);
	dist = sqrt(pow(rK34 * cos(tK34) - pxK34, 2.0f) + pow(rK34 * sin(tK34) - pyK34, 2.0f) + pow(delta.z - pzK34, 2.0f)) - sizeK34 * 0.1f;
#endif

#ifdef FAKE_LIGHTS_SPIRAL_3D
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float sizeS3D = consts->params.common.fakeLightsOrbitTrapSize;
	float tS3D = delta.y;
	float radiusS3D = sizeS3D * 0.5f;
	float turnsS3D = 2.0f;
	float angleS3D = turnsS3D * tS3D / sizeS3D * 3.14159265359f;
	float pxS3D = radiusS3D * cos(angleS3D);
	float pzS3D = radiusS3D * sin(angleS3D);
	dist = sqrt(pow(delta.x - pxS3D, 2.0f) + pow(delta.z - pzS3D, 2.0f)) - sizeS3D * 0.1f;
#endif

#ifdef FAKE_LIGHTS_TREE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float r = length(delta.xz);
	float h = delta.y;
	float angle = atan2(delta.z, delta.x);
	float branch = fmod(angle * 4.0f + h * 2.0f, 2.0f * M_PI_F);
	float branchR = size * (1.0f - h / (size * 4.0f)) * (0.5f + 0.3f * cos(branch));
	dist = sqrt(pow(r - branchR, 2.0f) + pow(fmod(h, size) - size * 0.5f, 2.0f)) - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_NOISE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float px = delta.x / size;
	float py = delta.y / size;
	float pz = delta.z / size;
	float noise = sin(px * 3.7f) * sin(py * 4.3f) * sin(pz * 5.1f);
	noise += 0.5f * sin(px * 7.3f + 1.0f) * sin(py * 8.7f + 2.0f) * sin(pz * 9.1f + 3.0f);
	dist = length(delta) - size * (0.8f + 0.4f * noise);
#endif

#ifdef FAKE_LIGHTS_MANDELBROT_2D
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float sizeM2D = consts->params.common.fakeLightsOrbitTrapSize;
	float cxM2D = delta.x / sizeM2D;
	float cyM2D = delta.y / sizeM2D;
	float zxM2D = cxM2D;
	float zyM2D = cyM2D;
	float lenM2D = 0.0f;
	for (int iM2D = 0; iM2D < 20; iM2D++)
	{
		float zx2M2D = zxM2D * zxM2D - zyM2D * zyM2D + cxM2D;
		zyM2D = 2.0f * zxM2D * zyM2D + cyM2D;
		zxM2D = zx2M2D;
		lenM2D = zxM2D * zxM2D + zyM2D * zyM2D;
		if (lenM2D > 4.0f) break;
	}
	dist = sqrt(lenM2D) * sizeM2D - sizeM2D * 0.1f;
#endif

#ifdef FAKE_LIGHTS_JULIA_2D
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float sizeJ2D = consts->params.common.fakeLightsOrbitTrapSize;
	float zxJ2D = delta.x / sizeJ2D;
	float zyJ2D = delta.y / sizeJ2D;
	float cxJ2D = 0.355f;
	float cyJ2D = 0.355f;
	float lenJ2D = 0.0f;
	for (int iJ2D = 0; iJ2D < 20; iJ2D++)
	{
		float zx2J2D = zxJ2D * zxJ2D - zyJ2D * zyJ2D + cxJ2D;
		zyJ2D = 2.0f * zxJ2D * zyJ2D + cyJ2D;
		zxJ2D = zx2J2D;
		lenJ2D = zxJ2D * zxJ2D + zyJ2D * zyJ2D;
		if (lenJ2D > 4.0f) break;
	}
	dist = sqrt(lenJ2D) * sizeJ2D - sizeJ2D * 0.1f;
#endif

#ifdef FAKE_LIGHTS_VORONOI
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Voronoi cell pattern
	float px = delta.x / size;
	float py = delta.y / size;
	float pz = delta.z / size;
	float cx = floor(px);
	float cy = floor(py);
	float cz = floor(pz);
	float lx = px - cx;
	float ly = py - cy;
	float lz = pz - cz;
	float minDist1 = 10.0f;
	float minDist2 = 10.0f;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			for (int k = -1; k <= 1; k++)
			{
				float nx = cx + i;
				float ny = cy + j;
				float nz = cz + k;
				float rnd = sin(nx * 12.9898f + ny * 78.233f + nz * 43.123f) * 43758.5453f;
				rnd = rnd - floor(rnd);
				float ptx = rnd;
				float pty = rnd * 1.3f - floor(rnd * 1.3f);
				float ptz = rnd * 2.7f - floor(rnd * 2.7f);
				float dx = lx - ptx - i;
				float dy = ly - pty - j;
				float dz = lz - ptz - k;
				float d = sqrt(dx * dx + dy * dy + dz * dz);
				if (d < minDist1)
				{
					minDist2 = minDist1;
					minDist1 = d;
				}
				else if (d < minDist2)
				{
					minDist2 = d;
				}
			}
		}
	}
	// Cell edges where the magic happens
	dist = (minDist2 - minDist1) * size;
#endif

#ifdef FAKE_LIGHTS_SIERPINSKI
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float px = delta.x / size;
	float py = delta.y / size;
	float pz = delta.z / size;
	float d = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		px = fabs(px);
		py = fabs(py);
		pz = fabs(pz);
		if (px + py + pz > 1.0f)
		{
			d = (px + py + pz - 1.0f) / pow(2.0f, (float)i);
			break;
		}
		px = px * 2.0f - 1.0f;
		py = py * 2.0f - 1.0f;
		pz = pz * 2.0f - 1.0f;
	}
	dist = d * size;
#endif

#ifdef FAKE_LIGHTS_KOCH
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float r = length(delta.xz) / size;
	float angle = atan2(delta.z, delta.x);
	float kochDist = fabs(sin(3.0f * angle)) * 0.3f * sin(log(r) * 2.0f);
	dist = fabs(r - 1.0f - kochDist) * size - size * 0.05f;
#endif

#ifdef FAKE_LIGHTS_DRAGON
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float zx = delta.x / size;
	float zy = delta.z / size;
	float cx = 0.45f;
	float cy = 0.0f;
	float len = 0.0f;
	for (int i = 0; i < 20; i++)
	{
		float zx2 = zx * zx - zy * zy + cx;
		zy = 2.0f * fabs(zx * zy) - cy;
		zx = zx2;
		len = zx * zx + zy * zy;
		if (len > 4.0f) break;
	}
	dist = sqrt(len) * size - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_HILBERT
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float px = delta.x / size;
	float py = delta.y / size;
	float pz = delta.z / size;
	float curve = sin(px * 2.0f) * sin(py * 2.0f) * sin(pz * 2.0f);
	curve += sin(px * 4.0f + 1.0f) * sin(py * 4.0f + 2.0f) * sin(pz * 4.0f + 3.0f) * 0.5f;
	dist = length(delta) - size * (0.5f + 0.3f * curve);
#endif

#ifdef FAKE_LIGHTS_GYROID
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Gyroid minimal surface - period matches sphere diameter (2*size)
	float px = delta.x * M_PI_F / size;
	float py = delta.y * M_PI_F / size;
	float pz = delta.z * M_PI_F / size;
	float g = sin(px) * cos(py) + sin(py) * cos(pz) + sin(pz) * cos(px);
	// Thickened surface
	dist = fabs(g) * size * 0.3f - size * 0.08f;
#endif

#ifdef FAKE_LIGHTS_SCHWARZ_P
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Schwarz P (Primitive) minimal surface - period matches sphere diameter
	float px = delta.x * M_PI_F / size;
	float py = delta.y * M_PI_F / size;
	float pz = delta.z * M_PI_F / size;
	float s = cos(px) + cos(py) + cos(pz);
	// Thickened surface
	dist = fabs(s) * size * 0.25f - size * 0.12f;
#endif

#ifdef FAKE_LIGHTS_SCHWARZ_D
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Schwarz D (Diamond) minimal surface - period matches sphere diameter
	float px = delta.x * M_PI_F / size;
	float py = delta.y * M_PI_F / size;
	float pz = delta.z * M_PI_F / size;
	float s = sin(px) * sin(py) * sin(pz) + sin(px) * cos(py) * cos(pz) 
	        + cos(px) * sin(py) * cos(pz) + cos(px) * cos(py) * sin(pz);
	// Thickened surface
	dist = fabs(s) * size * 0.25f - size * 0.12f;
#endif

#ifdef FAKE_LIGHTS_NEOVIUS
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Neovius minimal surface - smaller period for more features
	float px = delta.x * 2.0f * M_PI_F / size;
	float py = delta.y * 2.0f * M_PI_F / size;
	float pz = delta.z * 2.0f * M_PI_F / size;
	float n = 3.0f * (cos(px) + cos(py) + cos(pz)) + 4.0f * cos(px) * cos(py) * cos(pz);
	// Much thicker surface for visibility
	dist = fabs(n) * size * 0.15f - size * 0.12f;
#endif

#ifdef FAKE_LIGHTS_LABYRINTH
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// 3D Maze - walls at grid lines with passages
	float cellSize = size;
	float wallThick = size * 0.15f;
	// Distance to nearest cell border in each axis
	float dx = fabs(fmod(delta.x, cellSize) - cellSize * 0.5f);
	float dy = fabs(fmod(delta.y, cellSize) - cellSize * 0.5f);
	float dz = fabs(fmod(delta.z, cellSize) - cellSize * 0.5f);
	// Distance to walls (closest border)
	float distToWall = min(min(dx, dy), dz);
	// Create maze pattern - remove some walls based on cell position
	int cellX = (int)floor(delta.x / cellSize);
	int cellY = (int)floor(delta.y / cellSize);
	int cellZ = (int)floor(delta.z / cellSize);
	// Simple hash for which walls exist
	bool removeX = ((cellX + cellY + cellZ) % 3) == 0;
	bool removeY = ((cellX + cellY * 2 + cellZ) % 3) == 0;
	bool removeZ = ((cellX + cellY + cellZ * 2) % 3) == 0;
	// Apply wall removal
	if (removeX && dx < dy && dx < dz) distToWall = 999.0f;
	if (removeY && dy < dx && dy < dz) distToWall = 999.0f;
	if (removeZ && dz < dx && dz < dy) distToWall = 999.0f;
	// Distance field: positive outside walls, negative inside (solid)
	dist = distToWall - wallThick;
#endif

#ifdef FAKE_LIGHTS_FIBER
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Fiber bundle along Z axis with spiral twist - scale everything
	float angle = atan2(delta.y, delta.x);
	float r = length(delta.xy) / size; // Normalized radius
	float fibers = 5.0f; // Number of fibers
	float twist = 2.0f;  // Twist amount per unit
	float zNorm = delta.z / size; // Normalized Z
	float fiberAngle = fmod(angle * fibers + zNorm * twist, 2.0f * M_PI_F);
	float distToFiber = fabs(sin(fiberAngle)) * r * size; // Scale back to world
	dist = distToFiber - size * 0.1f + fabs(fmod(zNorm, 1.0f) - 0.5f) * size * 0.2f;
#endif

#ifdef FAKE_LIGHTS_ASTROID
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Astroid: hypocycloid with 4 cusps
	float t = atan2(delta.z, delta.y);
	float a = size;
	float astY = a * pow(cos(t), 3);
	float astZ = a * pow(sin(t), 3);
	dist = sqrt(pow(delta.y - astY, 2.0f) + pow(delta.z - astZ, 2.0f)) + fabs(delta.x) * 0.2f;
#endif

#ifdef FAKE_LIGHTS_DELTOID
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Deltoid: hypocycloid with 3 cusps
	float t = atan2(delta.z, delta.y);
	float a = size * 0.67f;
	float delY = a * (2.0f * cos(t) + cos(2.0f * t));
	float delZ = a * (2.0f * sin(t) - sin(2.0f * t));
	dist = sqrt(pow(delta.y - delY, 2.0f) + pow(delta.z - delZ, 2.0f)) + fabs(delta.x) * 0.2f;
#endif

#ifdef FAKE_LIGHTS_LEMNISCATE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Lemniscate of Bernoulli (figure-8)
	float t = atan2(delta.z, delta.y);
	float a = size;
	float denom = 1.0f + sin(t) * sin(t);
	float lemY = a * cos(t) / denom;
	float lemZ = a * sin(t) * cos(t) / denom;
	dist = sqrt(pow(delta.y - lemY, 2.0f) + pow(delta.z - lemZ, 2.0f)) + fabs(delta.x) * 0.2f;
#endif

#ifdef FAKE_LIGHTS_LIMACON
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Limacon (snail shell)
	float t = atan2(delta.z, delta.y);
	float a = size * 0.5f;
	float b = size * 0.8f;
	float limR = b + a * cos(t);
	float limY = limR * cos(t);
	float limZ = limR * sin(t);
	dist = sqrt(pow(delta.y - limY, 2.0f) + pow(delta.z - limZ, 2.0f)) + fabs(delta.x) * 0.2f;
#endif

#ifdef FAKE_LIGHTS_SPHERICAL_HARMONICS
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Spherical harmonics Y(3,2)
	float r = length(delta) / size;
	float phi = atan2(delta.z, length(delta.xy));
	float theta = atan2(delta.y, delta.x);
	float sh = sin(theta) * sin(theta) * cos(2.0f * phi) * sin(3.0f * theta);
	dist = fabs(r - 1.0f - sh * 0.3f) * size;
#endif

#ifdef FAKE_LIGHTS_SUPERFORMULA
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Superformula (generalized superellipse)
	float phi = atan2(delta.z, delta.y);
	float theta = atan2(delta.x, length(delta.yz));
	float m = 6.0f, n1 = 1.0f, n2 = 1.0f, n3 = 1.0f, a = 1.0f, b = 1.0f;
	float r1 = pow(pow(fabs(cos(m * phi / 4.0f) / a), n2) + pow(fabs(sin(m * phi / 4.0f) / b), n3), -1.0f / n1);
	float r2 = r1 * (1.0f + 0.3f * cos(3.0f * theta));
	float r = length(delta.yz);
	dist = fabs(r - r2 * size) + fabs(delta.x) * 0.15f;
#endif

#ifdef FAKE_LIGHTS_FERN
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Barnsley fern inspired shape
	float r = length(delta.xz) / size;
	float angle = atan2(delta.z, delta.x);
	float fernR = exp(-r * 0.5f) * (1.0f + 0.3f * sin(5.0f * angle + r * 2.0f));
	dist = fabs(r - fernR) * size + fabs(delta.y) * 0.3f;
#endif

#ifdef FAKE_LIGHTS_SHELL
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Seashell (logarithmic spiral)
	float t = delta.y / size * 0.5f;
	float a = size * 0.1f;
	float b = 0.3f;
	float shellR = a * exp(b * t);
	float angle = t * 3.0f;
	float shellX = shellR * cos(angle);
	float shellZ = shellR * sin(angle);
	dist = sqrt(pow(delta.x - shellX, 2.0f) + pow(delta.z - shellZ, 2.0f)) + fabs(fmod(t, 1.0f) - 0.5f) * size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_CORAL
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Coral branching structure
	float r = length(delta.xz);
	float h = delta.y;
	float angle = atan2(delta.z, delta.x);
	float branches = 6.0f;
	float branch = fmod(angle * branches + h * 1.5f, 2.0f * M_PI_F);
	float coralR = size * (1.0f - h / (size * 3.0f)) * (0.3f + 0.2f * fabs(sin(branch)));
	dist = sqrt(pow(r - coralR, 2.0f) + pow(fmod(h, size * 0.5f) - size * 0.25f, 2.0f)) - size * 0.05f;
#endif

#ifdef FAKE_LIGHTS_CRYSTAL
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Crystal/gem facets
	float px = delta.x / size;
	float py = delta.y / size;
	float pz = delta.z / size;
	float facets = fabs(px) + fabs(py) + fabs(pz);
	dist = fabs(facets - 1.5f) * size - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_HONEYCOMB
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Hexagonal honeycomb pattern
	float px = delta.x / size;
	float py = delta.y / size;
	float xHex = px * 2.0f / sqrt(3.0f);
	float yHex = py + floor(px) * 0.5f;
	float ix = floor(xHex);
	float iy = floor(yHex);
	float fx = xHex - ix;
	float fy = yHex - iy;
	float distHex = (fx + fy > 1.0f) ? 1.0f - fx : fy;
	dist = distHex * size * 0.5f + fabs(delta.z) * 0.3f;
#endif

#ifdef FAKE_LIGHTS_CHAIN
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Chain of linked rings
	float t = delta.z / (size * 0.8f);
	float link = fmod(t, 2.0f);
	float offset = ((int)floor(t) % 2 == 0) ? 0.0f : size * 0.5f;
	float linkY = (link < 1.0f) ? cos(link * M_PI_F) * size * 0.3f : 0.0f;
	float linkX = sin(link * M_PI_F) * size * 0.3f + offset;
	dist = sqrt(pow(delta.x - linkX, 2.0f) + pow(delta.y - linkY, 2.0f)) - size * 0.15f;
#endif

#ifdef FAKE_LIGHTS_WOVEN
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Woven/basket pattern
	float px = delta.x / size;
	float py = delta.y / size;
	float weaveX = fabs(sin(py * M_PI_F)) * size * 0.3f;
	float weaveY = fabs(sin(px * M_PI_F)) * size * 0.3f;
	float distX = fabs(delta.x - weaveX);
	float distY = fabs(delta.y - weaveY);
	dist = min(distX, distY) - size * 0.08f + fabs(delta.z) * 0.2f;
#endif

#ifdef FAKE_LIGHTS_NET
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Net/mesh pattern
	float px = delta.x / size;
	float py = delta.y / size;
	float gx = fabs(fmod(px, 1.0f) - 0.5f);
	float gy = fabs(fmod(py, 1.0f) - 0.5f);
	float lineWidth = 0.08f;
	float distGrid = (gx < gy) ? gx : gy;
	dist = distGrid * size - size * lineWidth + fabs(delta.z) * 0.15f;
#endif

#ifdef FAKE_LIGHTS_COIL
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Spring/coil shape
	float t = delta.y / size * 2.0f;
	float radius = size * 0.4f;
	float coilX = radius * cos(t * M_PI_F * 2.0f);
	float coilZ = radius * sin(t * M_PI_F * 2.0f);
	dist = sqrt(pow(delta.x - coilX, 2.0f) + pow(delta.z - coilZ, 2.0f)) - size * 0.12f;
#endif

#ifdef FAKE_LIGHTS_VORTEX
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Vortex/swirl
	float r = length(delta.xz);
	float angle = atan2(delta.z, delta.x);
	float spiralR = size * (1.0f - fabs(delta.y) / (size * 2.0f));
	float spiralAngle = angle + delta.y * 2.0f;
	float vorX = spiralR * cos(spiralAngle);
	float vorZ = spiralR * sin(spiralAngle);
	dist = sqrt(pow(delta.x - vorX, 2.0f) + pow(delta.z - vorZ, 2.0f)) + fabs(r - spiralR) * 0.3f;
#endif

#ifdef FAKE_LIGHTS_RIPPLE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Ripple/wave pattern
	float r = length(delta.xz);
	float ripples = 4.0f;
	float wave = sin(r / size * ripples * M_PI_F) * size * 0.2f;
	dist = fabs(delta.y - wave) - size * 0.08f;
#endif

#ifdef FAKE_LIGHTS_SHOCKWAVE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Shockwave/explosion ring
	float r = length(delta.xz);
	float t = delta.y / size;
	float ringR = size * (0.5f + t * 0.5f);
	float shock = exp(-t * t * 2.0f) * size * 0.3f;
	dist = fabs(r - ringR) - shock + fabs(delta.y) * 0.1f;
#endif

#ifdef FAKE_LIGHTS_ORBITAL
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Planetary orbits
	float r = length(delta.xz);
	float angle = atan2(delta.z, delta.x);
	float orbits = 3.0f;
	float orbitR = size * (0.3f + 0.7f * (fmod(angle * orbits / (2.0f * M_PI_F) + 0.5f, 1.0f)));
	dist = fabs(r - orbitR) - size * 0.08f + fabs(delta.y) * 0.15f;
#endif

#ifdef FAKE_LIGHTS_JULIA_3D
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float sizeJ3D = consts->params.common.fakeLightsOrbitTrapSize;
	float zxJ3D = delta.x / sizeJ3D;
	float zyJ3D = delta.y / sizeJ3D;
	float zzJ3D = delta.z / sizeJ3D;
	float cxJ3D = 0.3f, cyJ3D = 0.5f, czJ3D = 0.2f;
	float lenJ3D = 0.0f;
	for (int iJ3D = 0; iJ3D < 15; iJ3D++)
	{
		float zx2J3D = zxJ3D * zxJ3D - zyJ3D * zyJ3D - zzJ3D * zzJ3D + cxJ3D;
		float zy2J3D = 2.0f * zxJ3D * zyJ3D + cyJ3D;
		float zz2J3D = 2.0f * zxJ3D * zzJ3D + czJ3D;
		zxJ3D = zx2J3D; zyJ3D = zy2J3D; zzJ3D = zz2J3D;
		lenJ3D = zxJ3D * zxJ3D + zyJ3D * zyJ3D + zzJ3D * zzJ3D;
		if (lenJ3D > 4.0f) break;
	}
	dist = sqrt(lenJ3D) * sizeJ3D - sizeJ3D * 0.1f;
#endif

#ifdef FAKE_LIGHTS_MANDELBROT_3D
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float sizeM3D = consts->params.common.fakeLightsOrbitTrapSize;
	float cxM3D = delta.x / sizeM3D;
	float cyM3D = delta.y / sizeM3D;
	float czM3D = delta.z / sizeM3D;
	float zxM3D = 0.0f, zyM3D = 0.0f, zzM3D = 0.0f;
	float lenM3D = 0.0f;
	for (int iM3D = 0; iM3D < 15; iM3D++)
	{
		float zx2M3D = zxM3D * zxM3D - zyM3D * zyM3D - zzM3D * zzM3D + cxM3D;
		float zy2M3D = 2.0f * zxM3D * zyM3D + cyM3D;
		float zz2M3D = 2.0f * zxM3D * zzM3D + czM3D;
		zxM3D = zx2M3D; zyM3D = zy2M3D; zzM3D = zz2M3D;
		lenM3D = zxM3D * zxM3D + zyM3D * zyM3D + zzM3D * zzM3D;
		if (lenM3D > 4.0f) break;
	}
	dist = sqrt(lenM3D) * sizeM3D - sizeM3D * 0.1f;
#endif

#ifdef FAKE_LIGHTS_NEBULA
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	// Nebula cloud
	float px = delta.x / size;
	float py = delta.y / size;
	float pz = delta.z / size;
	float noise = sin(px * 2.0f) * sin(py * 3.0f) * sin(pz * 2.5f);
	noise += 0.5f * sin(px * 5.0f + py * 4.0f) * sin(pz * 3.0f + px * 2.0f);
	float r = length(delta) / size;
	dist = (r - 1.0f - noise * 0.3f) * size;
#endif

#ifdef FAKE_LIGHTS_BURNING_SHIP
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float cx = delta.x / size;
	float cy = delta.y / size;
	float zx = 0.0f, zy = 0.0f;
	float len = 0.0f;
	for (int i = 0; i < 20; i++)
	{
		float zx2 = zx * zx - zy * zy + cx;
		float zy2 = 2.0f * fabs(zx * zy) + cy;
		zx = fabs(zx2); zy = fabs(zy2);
		len = zx * zx + zy * zy;
		if (len > 4.0f) break;
	}
	dist = sqrt(len) * size - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_TRICORN
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float cx = delta.x / size;
	float cy = delta.y / size;
	float zx = 0.0f, zy = 0.0f;
	float len = 0.0f;
	for (int i = 0; i < 20; i++)
	{
		float zx2 = zx * zx - zy * zy + cx;
		float zy2 = -2.0f * zx * zy + cy;
		zx = zx2; zy = zy2;
		len = zx * zx + zy * zy;
		if (len > 4.0f) break;
	}
	dist = sqrt(len) * size - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_MULTIBROT
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float cx = delta.x / size;
	float cy = delta.y / size;
	float zx = 0.0f, zy = 0.0f;
	float len = 0.0f;
	for (int i = 0; i < 20; i++)
	{
		float r = sqrt(zx * zx + zy * zy);
		float theta = atan2(zy, zx);
		float r5 = r * r * r * r * r;
		float zx2 = r5 * cos(5.0f * theta) + cx;
		float zy2 = r5 * sin(5.0f * theta) + cy;
		zx = zx2; zy = zy2;
		len = zx * zx + zy * zy;
		if (len > 4.0f) break;
	}
	dist = sqrt(len) * size - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_PHOENIX
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float cx = delta.x / size;
	float cy = delta.y / size;
	float zx = 0.0f, zy = 0.0f;
	float wx = 0.0f, wy = 0.0f;
	float len = 0.0f;
	for (int i = 0; i < 20; i++)
	{
		float zx2 = zx * zx - zy * zy + cx + cy * wx;
		float zy2 = 2.0f * zx * zy + cy * wy;
		wx = zx; wy = zy;
		zx = zx2; zy = zy2;
		len = zx * zx + zy * zy;
		if (len > 4.0f) break;
	}
	dist = sqrt(len) * size - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_NEWTON
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float zx = delta.x / size;
	float zy = delta.y / size;
	for (int i = 0; i < 10; i++)
	{
		float r2 = zx * zx + zy * zy;
		float r4 = r2 * r2;
		float denom = 3.0f * r4;
		float zx2 = (2.0f * zx * r2 + 1.0f) / denom;
		float zy2 = 2.0f * zy / denom;
		zx = zx2; zy = zy2;
	}
	dist = fabs(zx * zy) * size;
#endif

#ifdef FAKE_LIGHTS_NOVA
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float cx = delta.x / size;
	float cy = delta.y / size;
	float zx = 1.0f, zy = 0.0f;
	float len = 0.0f;
	for (int i = 0; i < 15; i++)
	{
		float r2 = zx * zx + zy * zy;
		float r3 = r2 * sqrt(r2);
		float zx2 = zx - (zx * r2 - zx) / r3 + cx;
		float zy2 = zy - (zy * r2 + zy) / r3 + cy;
		zx = zx2; zy = zy2;
		len = zx * zx + zy * zy;
		if (len > 4.0f) break;
	}
	dist = sqrt(len) * size - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_SPIDER
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float cx = delta.x / size;
	float cy = delta.y / size;
	float zx = 0.0f, zy = 0.0f;
	float len = 0.0f;
	for (int i = 0; i < 20; i++)
	{
		float zx2 = zx * zx - zy * zy + cx;
		float zy2 = 2.0f * zx * zy + cy;
		zx = zx2 / (1.0f + zx2); zy = zy2 / (1.0f + zy2);
		len = zx * zx + zy * zy;
		if (len > 4.0f) break;
	}
	dist = sqrt(len) * size - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_DENDRITE
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float cx = delta.x / size;
	float cy = delta.y / size;
	float zx = 0.0f, zy = 0.0f;
	float len = 0.0f;
	for (int i = 0; i < 20; i++)
	{
		float zx2 = zx * zx - zy * zy + cx - 0.5f;
		float zy2 = 2.0f * zx * zy + cy;
		zx = fabs(zx2); zy = fabs(zy2);
		len = zx * zx + zy * zy;
		if (len > 4.0f) break;
	}
	dist = sqrt(len) * size - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_LORENZ
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float x = delta.x / size;
	float y = delta.y / size;
	float z = delta.z / size;
	float minDist = 999.0f;
	float px = 0.1f, py = 0.0f, pz = 0.0f;
	for (int i = 0; i < 50; i++)
	{
		float dt = 0.01f;
		float dx = 10.0f * (py - px) * dt;
		float dy = (px * (28.0f - pz) - py) * dt;
		float dz = (px * py - 8.0f/3.0f * pz) * dt;
		px += dx; py += dy; pz += dz;
		float d = sqrt(pow(x - px, 2.0f) + pow(y - py, 2.0f) + pow(z - pz, 2.0f));
		if (d < minDist) minDist = d;
	}
	dist = minDist * size - size * 0.05f;
#endif

#ifdef FAKE_LIGHTS_ROSSLER
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float x = delta.x / size;
	float y = delta.y / size;
	float z = delta.z / size;
	float minDist = 999.0f;
	float px = 0.1f, py = 0.0f, pz = 0.0f;
	for (int i = 0; i < 50; i++)
	{
		float dt = 0.05f;
		float dx = (-py - pz) * dt;
		float dy = (px + 0.2f * py) * dt;
		float dz = (0.2f + pz * (px - 5.7f)) * dt;
		px += dx; py += dy; pz += dz;
		float d = sqrt(pow(x - px, 2.0f) + pow(y - py, 2.0f) + pow(z - pz, 2.0f));
		if (d < minDist) minDist = d;
	}
	dist = minDist * size - size * 0.05f;
#endif

#ifdef FAKE_LIGHTS_POLYFOLD
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float cx = delta.x / size;
	float cy = delta.y / size;
	float zx = cx, zy = cy;
	float len = 0.0f;
	for (int i = 0; i < 15; i++)
	{
		float angle = atan2(zy, zx);
		float r = sqrt(zx * zx + zy * zy);
		angle = fmod(angle * 3.0f, 2.0f * M_PI_F);
		zx = r * cos(angle) + cx;
		zy = r * sin(angle) + cy;
		len = zx * zx + zy * zy;
		if (len > 4.0f) break;
	}
	dist = sqrt(len) * size - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_APOLLONIAN
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float px = delta.x / size;
	float py = delta.y / size;
	float pz = delta.z / size;
	float d = 1.0f;
	for (int i = 0; i < 3; i++)
	{
		float scale = pow(3.0f, (float)i);
		float sx = fmod(px * scale, 1.0f) - 0.5f;
		float sy = fmod(py * scale, 1.0f) - 0.5f;
		float sz = fmod(pz * scale, 1.0f) - 0.5f;
		float sd = sqrt(sx * sx + sy * sy + sz * sz) - 0.3f / scale;
		if (sd < d) d = sd;
	}
	dist = d * size;
#endif

#ifdef FAKE_LIGHTS_KLEINIAN
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float cx = delta.x / size;
	float cy = delta.y / size;
	float zx = cx, zy = cy;
	float len = 0.0f;
	for (int i = 0; i < 15; i++)
	{
		if (zx * zx + zy * zy < 1.0f)
		{
			float zx2 = zx + 1.0f;
			float zy2 = zy;
			zx = zx2; zy = zy2;
		}
		else
		{
			float denom = zx * zx + zy * zy;
			float zx2 = zx / denom;
			float zy2 = -zy / denom;
			zx = zx2 + cx;
			zy = zy2 + cy;
		}
		len = zx * zx + zy * zy;
		if (len > 4.0f) break;
	}
	dist = sqrt(len) * size - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_FIBONACCI
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float r = length(delta.xz) / size;
	float angle = atan2(delta.z, delta.x);
	float phi = (1.0f + sqrt(5.0f)) / 2.0f;
	float spiral = fmod(angle + log(r + 0.1f) * phi, 2.0f * M_PI_F);
	dist = fabs(sin(spiral * 5.0f)) * size * 0.3f + fabs(delta.y) * 0.2f;
#endif

#ifdef FAKE_LIGHTS_CELTIC
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float cx = delta.x / size;
	float cy = delta.y / size;
	float zx = cx, zy = cy;
	float len = 0.0f;
	for (int i = 0; i < 15; i++)
	{
		float zx2 = zx * zx - zy * zy + cx - 0.8f;
		float zy2 = 2.0f * zx * zy + cy;
		zx = fabs(zx2) - 0.5f; zy = fabs(zy2) - 0.5f;
		len = zx * zx + zy * zy;
		if (len > 4.0f) break;
	}
	dist = sqrt(len) * size - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_CROWN
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float cx = delta.x / size;
	float cy = delta.y / size;
	float zx = 0.0f, zy = 0.0f;
	float len = 0.0f;
	for (int i = 0; i < 20; i++)
	{
		float zx2 = zx * zx - zy * zy + cx;
		float zy2 = 2.0f * zx * fabs(zy) + cy;
		zx = zx2 - 0.5f; zy = fabs(zy2) - 0.5f;
		len = zx * zx + zy * zy;
		if (len > 4.0f) break;
	}
	dist = sqrt(len) * size - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_CACTUS
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float cx = delta.x / size;
	float cy = delta.y / size;
	float zx = cx, zy = cy;
	float len = 0.0f;
	for (int i = 0; i < 15; i++)
	{
		float r = sqrt(zx * zx + zy * zy);
		float theta = atan2(zy, zx);
		float r4 = r * r * r * r;
		float zx2 = r4 * cos(4.0f * theta) + cx;
		float zy2 = r4 * sin(4.0f * theta) + cy;
		zx = fabs(zx2) - 0.3f; zy = fabs(zy2) - 0.3f;
		len = zx * zx + zy * zy;
		if (len > 4.0f) break;
	}
	dist = sqrt(len) * size - size * 0.1f;
#endif

#ifdef FAKE_LIGHTS_SIEGEL_DISK
	delta = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, delta);
	delta = ApplyShapeModifiers(delta, consts);
	float sizeSD = consts->params.common.fakeLightsOrbitTrapSize;
	float cxSD = delta.x / sizeSD;
	float cySD = delta.y / sizeSD;
	float zxSD = cxSD, zySD = cySD;
	float lambdaSD = 0.5f + 0.5f * sqrt(5.0f);
	float lenSD = 0.0f;
	for (int iSD = 0; iSD < 20; iSD++)
	{
		float angleSD = atan2(zySD, zxSD) * lambdaSD;
		float rSD = sqrt(zxSD * zxSD + zySD * zySD);
		float zx2SD = rSD * cos(angleSD) + cxSD * 0.1f;
		float zy2SD = rSD * sin(angleSD) + cySD * 0.1f;
		zxSD = zx2SD; zySD = zy2SD;
		lenSD = zxSD * zxSD + zySD * zySD;
		if (lenSD > 4.0f) break;
	}
	dist = sqrt(lenSD) * sizeSD - sizeSD * 0.1f;
#endif


	dist -= consts->params.common.fakeLightsShapeChamfer;
	if (dist < 0.0f) dist = 0.0f;
	dist -= consts->params.common.fakeLightsShapeInflate;
	if (dist < 0.0f) dist = 0.0f;
	return dist / thicknessDivisor;
}

#endif // FAKE_LIGHTS
/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2019 Mandelbulber Team        §R-==%w["'~5]m%=L.=~5N
 *                                        ,=mm=§M ]=4 yJKA"/-Nsaj  "Bw,==,,
 * This file is part of Mandelbulber.    §R.r= jw",M  Km .mM  FW ",§=ß., ,TN
 *                                     ,4R =%["w[N=7]J '"5=],""]]M,w,-; T=]M
 * Mandelbulber is free software:     §R.ß~-Q/M=,=5"v"]=Qf,'§"M= =,M.§ Rz]M"Kw
 * you can redistribute it and/or     §w "xDY.J ' -"m=====WeC=\ ""%""y=%"]"" §
 * modify it under the terms of the    "§M=M =D=4"N #"%==A%p M§ M6  R' #"=~.4M
 * GNU General Public License as        §W =, ][T"]C  §  § '§ e===~ U  ![Z ]N
 * published by the                    4M",,Jm=,"=e~  §  §  j]]""N  BmM"py=ßM
 * Free Software Foundation,          ]§ T,M=& 'YmMMpM9MMM%=w=,,=MT]M m§;'§,
 * either version 3 of the License,    TWw [.j"5=~N[=§%=%W,T ]R,"=="Y[LFT ]N
 * or (at your option)                   TW=,-#"%=;[  =Q:["V""  ],,M.m == ]N
 * any later version.                      J§"mr"] ,=,," =="""J]= M"M"]==ß"
 *                                          §= "=C=4 §"eM "=B:m|4"]#F,§~
 * Mandelbulber is distributed in            "9w=,,]w em%wJ '"~" ,=,,ß"
 * the hope that it will be useful,                 . "K=  ,=RMMMßM"""
 * but WITHOUT ANY WARRANTY;                            .'''
 * without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with Mandelbulber. If not, see <http://www.gnu.org/licenses/>.
 *
 * ###########################################################################
 *
 * Authors: Krzysztof Marczak (buddhi1980@gmail.com)
 *
 * calculation of distance from orbit trap for "fake lights"
 * GPU version with full V2 shape support
 */

#ifdef FAKE_LIGHTS

// Helper for 2D SDF extrusion
inline float Extrude2D(float d2d, float z)
{
	return sqrt(d2d * d2d + z * z);
}

// Helper: sign
inline float SdfSign(float x) { return (x > 0.0f) ? 1.0f : ((x < 0.0f) ? -1.0f : 0.0f); }

// Helper: mod for SDF patterns (same as CPU: x - y * floor(x/y))
inline float SdfMod(float x, float y) { return x - y * floor(x / y); }

// Helper: Koch snowflake iteration (2D, returns distance in XY plane)
inline float KochSnowflakeDist(float x, float y, float size)
{
	x /= size;
	y /= size;
	for (int i = 0; i < 2; i++)
	{
		x = fabs(x);
		y = fabs(y);
		float dotxy = x * 0.5f + y * 0.86602540378f;
		if (dotxy > y)
		{
			x = dotxy;
			y = x * 0.86602540378f - y * 0.5f;
		}
		x = x * 3.0f - 2.0f;
		y = y * 3.0f;
		if (x < -1.0f) x = -2.0f - x;
	}
	return (y - 0.5f) * size;
}

// Helper: Menger sponge distance (approximate, 2 iterations)
inline float MengerSpongeDist(float3 p, float size)
{
	float3 s = p / size;
	float d = max(fabs(s.x), max(fabs(s.y), fabs(s.z))) - 1.0f;
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

// Helper: Sierpinski tetrahedron distance (approximate, 2 iterations)
inline float SierpinskiTetraDist(float3 p, float size)
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

// Helper: Apollonian distance (approximate)
inline float ApollonianDist(float3 p, float size)
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
inline float3 ApplyShapeModifiers(float3 delta, __constant sClInConstants *consts)
{
	// 1. 3D Repeat / Tiling
	float repeatX = consts->params.common.fakeLightsShapeRepeatX;
	float repeatY = consts->params.common.fakeLightsShapeRepeatY;
	float repeatZ = consts->params.common.fakeLightsShapeRepeatZ;
	if (repeatX > 0.0f)
	{
		float half = repeatX * 0.5f;
		delta.x = fmod(delta.x + half, repeatX);
		if (delta.x < 0.0f) delta.x += repeatX;
		delta.x -= half;
	}
	if (repeatY > 0.0f)
	{
		float half = repeatY * 0.5f;
		delta.y = fmod(delta.y + half, repeatY);
		if (delta.y < 0.0f) delta.y += repeatY;
		delta.y -= half;
	}
	if (repeatZ > 0.0f)
	{
		float half = repeatZ * 0.5f;
		delta.z = fmod(delta.z + half, repeatZ);
		if (delta.z < 0.0f) delta.z += repeatZ;
		delta.z -= half;
	}

	// 2. Polar / Radial repeat (around Y axis)
	int radialCount = consts->params.common.fakeLightsRadialRepeatCount;
	if (radialCount > 1)
	{
		float angle = atan2(delta.z, delta.x);
		float r = sqrt(delta.x * delta.x + delta.z * delta.z);
		float sector = 2.0f * 3.14159265359f / (float)radialCount;
		angle = fmod(angle + sector / 2.0f, sector);
		if (angle < 0.0f) angle += sector;
		angle -= sector / 2.0f;
		delta.x = cos(angle) * r - consts->params.common.fakeLightsRadialRepeatRadius;
		delta.z = sin(angle) * r;
	}

	// 3. Displacement (Wobble)
	float wobbleAmp = consts->params.common.fakeLightsShapeWobbleAmplitude;
	float wobbleFreq = consts->params.common.fakeLightsShapeWobbleFrequency;
	if (wobbleAmp > 0.0f && wobbleFreq > 0.0f)
	{
		delta.x += wobbleAmp * sin(wobbleFreq * delta.y);
		delta.y += wobbleAmp * sin(wobbleFreq * delta.z);
		delta.z += wobbleAmp * sin(wobbleFreq * delta.x);
	}

	// 4. Fold symmetry (radial folding in XY plane)
	int fold = consts->params.common.fakeLightsShapeFoldSymmetry;
	if (fold > 1)
	{
		float angle = atan2(delta.y, delta.x);
		float r = sqrt(delta.x * delta.x + delta.y * delta.y);
		float period = 2.0f * 3.14159265359f / (float)fold;
		angle = fmod(angle + period / 2.0f, period);
		if (angle < 0.0f) angle += period;
		angle -= period / 2.0f;
		delta.x = cos(angle) * r;
		delta.y = sin(angle) * r;
	}

	// 5. Taper: scale xz based on y
	float taperScale = 1.0f + consts->params.common.fakeLightsShapeTaper * delta.y;
	if (taperScale < 1e-10f) taperScale = 1e-10f;
	delta.x *= taperScale;
	delta.z *= taperScale;

	// 6. Twist: rotate xz around y
	float twistAngle = consts->params.common.fakeLightsShapeTwist * delta.y;
	float cosT = cos(twistAngle);
	float sinT = sin(twistAngle);
	float nx = delta.x * cosT - delta.z * sinT;
	float nz = delta.x * sinT + delta.z * cosT;
	delta.x = nx;
	delta.z = nz;

	// 7. Bend: curve space around a circle
	float bend = consts->params.common.fakeLightsShapeBend;
	if (fabs(bend) > 1e-10f)
	{
		float bendAngle = bend * delta.y;
		delta.y = sin(bendAngle) / bend;
		delta.x += (1.0f - cos(bendAngle)) / bend;
	}

	return delta;
}

inline float ShapeDistanceInternal(float3 delta, int shapeId, __constant sClInConstants *consts)
{
	float dist = 0.0f;
	float size = consts->params.common.fakeLightsOrbitTrapSize;
	float3 d = delta;
	
	switch (shapeId)
	{
		case fakeLightsShapePoint:
		{
			d = ApplyShapeModifiers(d, consts);
			dist = length(d) - size;
			break;
		}
		case fakeLightsShapeLine:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			dist = sqrt(d.y * d.y + d.z * d.z) - size;
			break;
		}
		case fakeLightsShapeCircle:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float lengthYZ = sqrt(d.y * d.y + d.z * d.z) - size;
			dist = sqrt(lengthYZ * lengthYZ + d.x * d.x);
			break;
		}
		case fakeLightsShapeSquare:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float dy = max(fabs(fabs(d.y) - size), fabs(d.z) - size);
			float dz = max(fabs(fabs(d.z) - size), fabs(d.y) - size);
			float deltaRect = min(dy, dz);
			dist = sqrt(deltaRect * deltaRect + d.x * d.x);
			break;
		}
		case fakeLightsShapeSphere:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float lengthYZ = sqrt(d.y * d.y + d.z * d.z) - size;
			float distYZ = sqrt(lengthYZ * lengthYZ + d.x * d.x);
			float lengthXZ = sqrt(d.x * d.x + d.z * d.z) - size;
			float distXZ = sqrt(lengthXZ * lengthXZ + d.y * d.y);
			float lengthXY = sqrt(d.x * d.x + d.y * d.y) - size;
			float distXY = sqrt(lengthXY * lengthXY + d.z * d.z);
			dist = min(min(distYZ, distXZ), distXY);
			break;
		}
		case fakeLightsShapeCube:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float dy_x = max(fabs(fabs(d.y) - size), fabs(d.z) - size);
			float dz_x = max(fabs(fabs(d.z) - size), fabs(d.y) - size);
			float dx_z = max(fabs(fabs(d.y) - size), fabs(d.x) - size);
			float deltaRectYZ = min(dy_x, dz_x);
			float distYZ = sqrt(deltaRectYZ * deltaRectYZ + fabs(fabs(d.x) - size) * fabs(fabs(d.x) - size));
			float distXZ = sqrt(dx_z * dx_z + fabs(fabs(d.z) - size) * fabs(fabs(d.z) - size));
			dist = min(distYZ, distXZ);
			break;
		}
		case fakeLightsShapeTorus:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float q = sqrt(d.x * d.x + d.y * d.y) - size;
			dist = sqrt(q * q + d.z * d.z);
			break;
		}
		case fakeLightsShapeTriangle:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float h = size * 1.5f;
			float d2d = max(fabs(d.x) * 0.86602540378f + d.y * 0.5f, -d.y) - h / 3.0f;
			dist = Extrude2D(d2d, d.z);
			break;
		}
		case fakeLightsShapeHexagon:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float d2d = max(fabs(d.x) * 0.86602540378f + fabs(d.y) * 0.5f, fabs(d.y)) - size;
			dist = Extrude2D(d2d, d.z);
			break;
		}
		case fakeLightsShapeStar:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float a = atan2(d.y, d.x);
			float r = sqrt(d.x * d.x + d.y * d.y);
			float points = consts->params.common.fakeLightsShapeParam1;
			if (points < 2.0f) points = 5.0f;
			float d2d = r - size * (0.55f + 0.45f * cos(a * points));
			dist = Extrude2D(d2d, d.z);
			break;
		}
		case fakeLightsShapeCross:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float r = size;
			float dd1 = sqrt(d.y * d.y + d.z * d.z) - r;
			float dd2 = sqrt(d.x * d.x + d.z * d.z) - r;
			float dd3 = sqrt(d.x * d.x + d.y * d.y) - r;
			dist = min(min(dd1, dd2), dd3);
			break;
		}
		case fakeLightsShapeCapsule:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float h = size;
			float r = h * consts->params.common.fakeLightsShapeParam2;
			if (r < 0.0f) r = h * 0.2f;
			float py = d.y;
			if (py < -h) py = -h;
			if (py > h) py = h;
			dist = sqrt(d.x * d.x + (d.y - py) * (d.y - py) + d.z * d.z) - r;
			break;
		}
		case fakeLightsShapeCone:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float c = size * consts->params.common.fakeLightsShapeParam2;
			if (c <= 0.0f) c = size * 0.3f;
			dist = sqrt(d.x * d.x + d.z * d.z) - c * fabs(d.y);
			break;
		}
		case fakeLightsShapePyramid:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float h = size;
			float m = max(fabs(d.x), fabs(d.z));
			dist = max(m + d.y * 0.5f - h * 0.5f, d.y);
			break;
		}
		case fakeLightsShapeTetrahedron:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float md = max(max(-d.x - d.y - d.z, d.x + d.y - d.z),
				max(d.x - d.y + d.z, -d.x + d.y + d.z));
			dist = md * 0.57735026919f - size * 0.57735026919f;
			break;
		}
		case fakeLightsShapeOctahedron:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			dist = (fabs(d.x) + fabs(d.y) + fabs(d.z) - size) * 0.57735026919f;
			break;
		}
		case fakeLightsShapeDodecahedron:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float px = fabs(d.x);
			float py = fabs(d.y);
			float pz = fabs(d.z);
			float dd = max(max(px + py + pz, px + py - pz),
				max(px - py + pz, -px + py + pz));
			dist = dd * 0.57735f - size * 0.57735f + (px * py + py * pz + pz * px) * 0.05f / size;
			break;
		}
		case fakeLightsShapeIcosahedron:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float px = fabs(d.x);
			float py = fabs(d.y);
			float pz = fabs(d.z);
			float m = max(max(px, py), pz);
			dist = (px + py + pz - size) * 0.57735f + (px * py * pz) * 0.1f / (size * size);
			break;
		}
		case fakeLightsShapeMengerSponge:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			dist = MengerSpongeDist(d, size);
			break;
		}
		case fakeLightsShapeSierpinskiTetrahedron:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			dist = SierpinskiTetraDist(d, size);
			break;
		}
		case fakeLightsShapeKochSnowflake:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			dist = Extrude2D(KochSnowflakeDist(d.x, d.y, size), d.z);
			break;
		}
		case fakeLightsShapeHexGrid:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float s = size * 0.5f;
			float qx = d.x * 0.57735026918f;
			float qy = d.y + d.x * 0.33333333333f;
			float rx = SdfMod(qx, s) - s * 0.5f;
			float ry = SdfMod(qy, s) - s * 0.5f;
			float d2d = max(fabs(rx) * 0.86602540378f + fabs(ry) * 0.5f, fabs(ry)) - s * 0.5f;
			dist = Extrude2D(d2d, d.z);
			break;
		}
		case fakeLightsShapeSpiral:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float a = atan2(d.y, d.x);
			float r = sqrt(d.x * d.x + d.y * d.y);
			float step = consts->params.common.fakeLightsShapeParam1;
			if (step <= 0.0f) step = 0.15f;
			float spiralR = size * (0.1f + step * a);
			dist = Extrude2D(fabs(r - spiralR), d.z);
			break;
		}
		case fakeLightsShapeGrid:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float s = size;
			float dx = SdfMod(d.x + s * 0.5f, s) - s * 0.5f;
			float dy = SdfMod(d.y + s * 0.5f, s) - s * 0.5f;
			float dz = SdfMod(d.z + s * 0.5f, s) - s * 0.5f;
			float dd1 = sqrt(dx * dx + dy * dy) - s * 0.1f;
			float dd2 = sqrt(dy * dy + dz * dz) - s * 0.1f;
			float dd3 = sqrt(dx * dx + dz * dz) - s * 0.1f;
			dist = min(min(dd1, dd2), dd3);
			break;
		}
		case fakeLightsShapeBuckyball:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			float px = fabs(d.x);
			float py = fabs(d.y);
			float pz = fabs(d.z);
			float dd1 = max(max(px + py + pz, px + py - pz),
				max(px - py + pz, -px + py + pz)) * 0.57735f - size * 0.57735f;
			float dd2 = (px + py + pz - size) * 0.57735f + (px * py * pz) * 0.1f / (size * size);
			dist = max(dd1, dd2) * 0.95f;
			break;
		}
		case fakeLightsShapeApollonian:
		{
			d = Matrix33MulFloat3(consts->params.common.mRotFakeLightsRotation, d);
			d = ApplyShapeModifiers(d, consts);
			dist = ApollonianDist(d, size);
			break;
		}
		default:
		{
			d = ApplyShapeModifiers(d, consts);
			dist = length(d) - size;
			break;
		}
	}
	return dist;
}

float OrbitTrapShapeDistance(float4 z4, float3 orbitTrapPos, __constant sClInConstants *consts)
{
	float3 delta = z4.xyz - orbitTrapPos;

	float distA = ShapeDistanceInternal(delta, consts->params.common.fakeLightsOrbitTrapShape, consts);
	float dist = distA;

	if (consts->params.common.fakeLightsBlendAmount > 0.0f)
	{
		float distB = ShapeDistanceInternal(delta, consts->params.common.fakeLightsBlendShape, consts);
		dist = distA * (1.0f - consts->params.common.fakeLightsBlendAmount)
				+ distB * consts->params.common.fakeLightsBlendAmount;
	}

	// Chamfer / Round: offset the distance to round sharp edges
	if (consts->params.common.fakeLightsShapeChamfer > 0.0f)
	{
		dist -= consts->params.common.fakeLightsShapeChamfer;
	}

	// Onion / Hollow-shell: turn solid shape into thin shell
	if (consts->params.common.fakeLightsOnionThickness > 0.0f)
	{
		dist = fabs(dist) - consts->params.common.fakeLightsOnionThickness;
	}

	return dist / consts->params.common.fakeLightsThickness;
}

#endif // FAKE_LIGHTS

/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2018-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
 *                                        ,=mm=§M ]=4 yJKA"/-Nsaj  "Bw,==,,
 * This file is part of Mandelbulber.    §R.r= jw",M  Km .mM  FW ",§=ß., ,TN
 *                                     ,4R =%["w[N=7]J '"5=],""]]M,w,-; T=]M
 * Mandelbulber is free software:     §R.ß~-Q/M=,=5"v"]=Qf,'§"M= =,M.§ Rz]M"Kw
 * you can redistribute it and/or     §w "xDY.J ' -"m=====WeC=\ ""%""y=%"]"" §
 * modify it under the terms of the    "§M=M =D=4"N #"%==A%p M§ M6  R' #"=~.4M
 * GNU General Public License as        §W =, ][T"]C  §  § '§ e===~ U  !§[Z ]N
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
 * calculation of distance to primitive objects for opencl
 */

#ifdef USE_PRIMITIVES

float3 TransformPrimitivePoint(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point;
	if (primitive->object.useWorldSpacePivot)
	{
		point = _point - primitive->object.pivot;
		point = Matrix33MulFloat3(primitive->object.rotationMatrix, point);
		point = point + primitive->object.pivot;
		point = point - primitive->object.position;
	}
	else
	{
		point = _point - primitive->object.position;
		point = point - primitive->object.pivot;
		point = Matrix33MulFloat3(primitive->object.rotationMatrix, point);
		point = point + primitive->object.pivot;
	}

	if (primitive->object.mirrorX) point.x = fabs(point.x);
	if (primitive->object.mirrorY) point.y = fabs(point.y);
	if (primitive->object.mirrorZ) point.z = fabs(point.z);

	point.x /= max(primitive->object.primitiveScale.x, 1e-10f);
	point.y /= max(primitive->object.primitiveScale.y, 1e-10f);
	point.z /= max(primitive->object.primitiveScale.z, 1e-10f);

	return point;
}

float GetPrimitiveMinScale(__global sPrimitiveCl *primitive)
{
	float ms = primitive->object.primitiveScale.x;
	if (primitive->object.primitiveScale.y < ms) ms = primitive->object.primitiveScale.y;
	if (primitive->object.primitiveScale.z < ms) ms = primitive->object.primitiveScale.z;
	return ms;
}

float3 CalculateCloneOffsetOpenCL(__global sPrimitiveCl *primitive, int index)
{
	if (!primitive->object.clonerEnabled || primitive->object.clonerCount <= 1)
		return (float3){0.0f, 0.0f, 0.0f};

	switch (primitive->object.clonerMode)
	{
		case 0: // Linear
		{
			return primitive->object.clonerOffset * (float)index;
		}
		case 1: // Radial
		{
			if (primitive->object.clonerCount <= 1)
				return (float3){0.0f, 0.0f, 0.0f};
			float t = (float)index / (float)(primitive->object.clonerCount - 1);
			float angle = primitive->object.clonerStartAngle
				+ (primitive->object.clonerEndAngle - primitive->object.clonerStartAngle) * t;
			float radius = primitive->object.clonerRadius;
			switch (primitive->object.clonerPlane)
			{
				case 0: return (float3){radius * cos(angle), radius * sin(angle), 0.0f};
				case 1: return (float3){radius * cos(angle), 0.0f, radius * sin(angle)};
				case 2: return (float3){0.0f, radius * cos(angle), radius * sin(angle)};
			}
			return (float3){0.0f, 0.0f, 0.0f};
		}
		case 2: // Grid
		{
			float3 count = primitive->object.clonerGridCount;
			float3 size = primitive->object.clonerGridSize;
			int ix = index % (int)count.x;
			int iy = (index / (int)count.x) % (int)count.y;
			int iz = index / ((int)count.x * (int)count.y);
			return (float3){
				(ix - (count.x - 1.0f) * 0.5f) * size.x,
				(iy - (count.y - 1.0f) * 0.5f) * size.y,
				(iz - (count.z - 1.0f) * 0.5f) * size.z};
		}
		case 3: // Honeycomb
		{
			float s = primitive->object.clonerHoneycombSpacing;
			if (s < 1e-10f) s = 1.0f;
			int cx = (int)primitive->object.clonerGridCount.x;
			int cy = (int)primitive->object.clonerGridCount.y;
			if (cx < 1) cx = 1;
			if (cy < 1) cy = 1;
			int ix = index % cx;
			int iy = index / cx;
			float px = ix * s + (iy % 2) * s * 0.5f;
			float py = iy * s * 0.866025f;
			switch (primitive->object.clonerPlane)
			{
				case 0: return (float3){px, py, 0.0f};
				case 1: return (float3){px, 0.0f, py};
				case 2: return (float3){0.0f, px, py};
			}
			return (float3){px, py, 0.0f};
		}
		case 4: // Fibonacci sphere
		{
			if (primitive->object.clonerCount <= 1) return (float3){0.0f, 0.0f, 0.0f};
			float golden = (1.0f + native_sqrt(5.0f)) / 2.0f;
			float theta = 2.0f * M_PI_F * index / golden;
			float phi2 = acos(1.0f - 2.0f * (index + 0.5f) / primitive->object.clonerCount);
			float r = primitive->object.clonerRadius;
			return (float3){r * native_sin(phi2) * native_cos(theta),
							r * native_sin(phi2) * native_sin(theta),
							r * native_cos(phi2)};
		}
		case 5: // Random
		{
			uint sd = ((uint)primitive->object.clonerRandomSeed * 73856093u) ^ ((uint)index * 19349663u);
			float rx, ry, rz;
			sd = (sd << 13u) ^ sd;
			sd = sd * (sd * sd * 15731u + 789221u) + 1376312589u;
			rx = ((float)(sd & 0x7fffffffu) / (float)0x7fffffffu) * 2.0f - 1.0f;
			sd = (sd << 13u) ^ sd;
			sd = sd * (sd * sd * 15731u + 789221u) + 1376312589u;
			ry = ((float)(sd & 0x7fffffffu) / (float)0x7fffffffu) * 2.0f - 1.0f;
			sd = (sd << 13u) ^ sd;
			sd = sd * (sd * sd * 15731u + 789221u) + 1376312589u;
			rz = ((float)(sd & 0x7fffffffu) / (float)0x7fffffffu) * 2.0f - 1.0f;
			return (float3){rx * primitive->object.clonerRandomBounds.x,
							ry * primitive->object.clonerRandomBounds.y,
							rz * primitive->object.clonerRandomBounds.z};
		}
		case 6: // Spiral
		{
			if (primitive->object.clonerCount <= 1) return (float3){0.0f, 0.0f, 0.0f};
			float t = (float)index / (float)(primitive->object.clonerCount - 1);
			float angle2 = t * primitive->object.clonerSpiralTurns * 2.0f * M_PI_F;
			float r2 = primitive->object.clonerRadius * t;
			float h = t * primitive->object.clonerSpiralHeight;
			switch (primitive->object.clonerPlane)
			{
				case 0: return (float3){native_cos(angle2) * r2, native_sin(angle2) * r2, h};
				case 1: return (float3){native_cos(angle2) * r2, h, native_sin(angle2) * r2};
				case 2: return (float3){h, native_cos(angle2) * r2, native_sin(angle2) * r2};
			}
			return (float3){native_cos(angle2) * r2, native_sin(angle2) * r2, h};
		}
	}
	return (float3){0.0f, 0.0f, 0.0f};
}

float RandFloatEffector(int s, int idx, int comp)
{
	uint x = ((uint)s * 73856093u) ^ ((uint)idx * 19349663u) ^ ((uint)comp * 83492791u);
	x = (x << 13u) ^ x;
	x = x * (x * x * 15731u + 789221u) + 1376312589u;
	return ((float)(x & 0x7fffffffu) / (float)0x7fffffffu) * 2.0f - 1.0f;
}

typedef struct
{
	float3 offset;
	float3 rotation;
	float3 scale;
} sCloneTransformCl;

sCloneTransformCl ApplyCloneTransformOpenCL(__global sPrimitiveCl *primitive, int index)
{
	sCloneTransformCl result;
	result.offset = CalculateCloneOffsetOpenCL(primitive, index);
	result.rotation = (float3){0.0f, 0.0f, 0.0f};
	result.scale = (float3){1.0f, 1.0f, 1.0f};

	for (int ei = 0; ei < 4; ei++)
	{
		int effType = primitive->effectors[ei].type;
		if (effType == 0) continue;

		float strength = primitive->effectors[ei].strength;
		if (strength < 1e-10f) continue;

		int mode = primitive->effectors[ei].mode;
		int seed = primitive->effectors[ei].seed;
		float3 posAmp = primitive->effectors[ei].posAmp;
		float3 rotAmp = primitive->effectors[ei].rotAmp;
		float3 scaleAmp = primitive->effectors[ei].scaleAmp;

		float3 posOff = (float3){0.0f, 0.0f, 0.0f};
		float3 rotOff = (float3){0.0f, 0.0f, 0.0f};
		float3 scaleMul = (float3){1.0f, 1.0f, 1.0f};

		switch (effType)
		{
			case 1: // Random
			{
				posOff.x = RandFloatEffector(seed, index, 0) * posAmp.x * strength;
				posOff.y = RandFloatEffector(seed, index, 1) * posAmp.y * strength;
				posOff.z = RandFloatEffector(seed, index, 2) * posAmp.z * strength;
				rotOff.x = RandFloatEffector(seed, index, 3) * rotAmp.x * strength;
				rotOff.y = RandFloatEffector(seed, index, 4) * rotAmp.y * strength;
				rotOff.z = RandFloatEffector(seed, index, 5) * rotAmp.z * strength;
				scaleMul.x = 1.0f + RandFloatEffector(seed, index, 6) * scaleAmp.x * strength;
				scaleMul.y = 1.0f + RandFloatEffector(seed, index, 7) * scaleAmp.y * strength;
				scaleMul.z = 1.0f + RandFloatEffector(seed, index, 8) * scaleAmp.z * strength;
				break;
			}
			case 2: // Step
			{
				float t = (float)index * strength;
				posOff = posAmp * t;
				rotOff = rotAmp * t;
				scaleMul.x = 1.0f + scaleAmp.x * t;
				scaleMul.y = 1.0f + scaleAmp.y * t;
				scaleMul.z = 1.0f + scaleAmp.z * t;
				break;
			}
			case 3: // Formula
			{
				float fi = (float)index;
				int preset = primitive->effectors[ei].formulaPreset;
				switch (preset)
				{
					case 0: posOff.x = sin(fi * 0.5f) * strength; break;
					case 1: posOff.y = cos(fi * 0.5f) * strength; break;
					case 2:
						posOff.x = sin(fi * 0.3f) * strength;
						posOff.y = cos(fi * 0.4f) * strength;
						posOff.z = sin(fi * 0.5f + 1.0f) * strength;
						break;
					case 3:
						posOff.x = cos(fi * 0.5f) * strength;
						posOff.y = sin(fi * 0.5f) * strength;
						break;
				}
				break;
			}
			case 4: // Time
			{
				float timeOffset = primitive->effectors[ei].timeOffset;
				float timeScale = primitive->effectors[ei].timeScale;
				float phase = timeOffset * 0.1f + (float)index * timeScale * 0.1f;
				posOff.x = sin(phase) * strength;
				posOff.y = cos(phase * 1.3f) * strength;
				posOff.z = sin(phase * 0.7f) * strength;
				break;
			}
		}

		switch (mode)
		{
			case 0: // POSITION
				result.offset += posOff;
				break;
			case 1: // ROTATION
				result.rotation += rotOff;
				break;
			case 2: // SCALE
				result.scale = result.scale * scaleMul;
				break;
			case 3: // ALL
			default:
				result.offset += posOff;
				result.rotation += rotOff;
				result.scale = result.scale * scaleMul;
				break;
		}
	}

	return result;
}

float3 modVector3(float3 a, float3 b)
{
	return (float3){fmod(a.x, b.x), fmod(a.y, b.y), fmod(a.z, b.z)};
}

float3 repeatMod(float3 point, float3 repeatVec)
{
	if (length(repeatVec) == 0.0f) return point;
	float3 repeatHalf = repeatVec * 0.5f;
	return modVector3(modVector3(point - repeatHalf, repeatVec) + repeatVec, repeatVec) - repeatHalf;
}

float3 repeatModMirror(float3 point, float3 repeatVec)
{
	if (length(repeatVec) == 0.0f) return point;
	float3 repeatHalf = repeatVec * 0.5f;
	float3 modded = modVector3(modVector3(point - repeatHalf, repeatVec) + repeatVec, repeatVec) - repeatHalf;
	return (float3){fabs(modded.x), fabs(modded.y), fabs(modded.z)};
}

float3 repeatModRotation(float3 point, float3 repeatVec, float stepDegrees)
{
	if (length(repeatVec) == 0.0f) return point;
	float3 modded = repeatMod(point, repeatVec);
	float angle = stepDegrees * M_PI_F / 180.0f;
	float cosA = cos(angle);
	float sinA = sin(angle);
	return (float3){modded.x * cosA - modded.y * sinA, modded.x * sinA + modded.y * cosA, modded.z};
}

float3 repeatModFibonacci(float3 point, int count, float spread)
{
	(void)count;
	if (length(point) == 0.0f) return point;
	float goldenAngle = M_PI_F * (3.0f - sqrt(5.0f));
	float r = length(point);
	float theta = atan2(point.y, point.x);
	float ringSpacing = spread * 0.5f;
	int ring = (int)(r / ringSpacing);
	if (ring < 1) ring = 1;
	float targetR = ring * ringSpacing;
	float targetTheta = fmod(ring * goldenAngle + theta, 2.0f * M_PI_F);
	return (float3){targetR * cos(targetTheta), targetR * sin(targetTheta), point.z};
}

float3 repeatModBrick(float3 point, float3 repeatVec)
{
	if (length(repeatVec) == 0.0f) return point;
	float3 modded = repeatMod(point, repeatVec);
	int cellY = (int)(floor(point.y / repeatVec.y));
	int cellZ = (int)(floor(point.z / repeatVec.z));
	if (cellY % 2 != 0) modded.x += repeatVec.x * 0.5f;
	if (cellZ % 4 != 0) modded.x += repeatVec.x * 0.25f;
	return modded;
}

float3 repeatModHoneycomb(float3 point, float3 repeatVec)
{
	if (length(repeatVec) == 0.0f) return point;
	float hexW = repeatVec.x;
	float hexH = repeatVec.y * sqrt(3.0f) / 2.0f;
	int row = (int)(floor(point.y / hexH));
	float offsetX = (row % 2) * hexW * 0.5f;
	float localX = point.x - offsetX;
	int col = (int)(floor(localX / hexW));
	float3 modded = (float3){localX - col * hexW, point.y - row * hexH, point.z};
	modded.x += offsetX;
	return modded;
}

float3 repeatModSpiral(float3 point, float3 repeatVec, float3 step, float3 angle, float3 radius)
{
	(void)angle;
	(void)radius;
	if (length(repeatVec) == 0.0f) return point;
	float3 modded = repeatMod(point, repeatVec);
	int cellX = (int)(floor(point.x / repeatVec.x));
	int cellY = (int)(floor(point.y / repeatVec.y));
	int cellZ = (int)(floor(point.z / repeatVec.z));
	int cellIdx = cellX + cellY * 10 + cellZ * 100;
	float t = cellIdx * 0.1f;
	modded.x += step.x * t * cos(t);
	modded.y += step.y * t * sin(t);
	modded.z += step.z * t;
	return modded;
}

float3 repeatModWave(float3 point, float3 repeatVec, float3 amplitude, float3 frequency,
	float3 phase, int axis)
{
	if (length(repeatVec) == 0.0f) return point;
	float3 modded = repeatMod(point, repeatVec);
	if (axis == 0)
	{
		modded.y += amplitude.y * sin(modded.x * frequency.y + phase.y);
		modded.z += amplitude.z * sin(modded.x * frequency.z + phase.z);
	}
	else if (axis == 1)
	{
		modded.x += amplitude.x * sin(modded.y * frequency.x + phase.x);
		modded.z += amplitude.z * sin(modded.y * frequency.z + phase.z);
	}
	else
	{
		modded.x += amplitude.x * sin(modded.z * frequency.x + phase.x);
		modded.y += amplitude.y * sin(modded.z * frequency.y + phase.y);
	}
	return modded;
}

float3 ApplyRepeat(float3 point, __global sPrimitiveCl *primitive)
{
	float3 pointRepeated = point;
	switch (primitive->object.repeatMode)
	{
		case 0: pointRepeated = repeatMod(point, primitive->object.repeat); break;
		case 1: pointRepeated = repeatModMirror(point, primitive->object.repeat); break;
		case 2: pointRepeated = repeatModRotation(point, primitive->object.repeat, primitive->object.repeatRotationStep); break;
		case 3: pointRepeated = repeatModFibonacci(point, primitive->object.repeatFibonacciCount, primitive->object.repeatFibonacciSpread); break;
		case 4: pointRepeated = repeatModBrick(point, primitive->object.repeat); break;
		case 7: pointRepeated = repeatModHoneycomb(point, primitive->object.repeat); break;
		case 12: pointRepeated = repeatModSpiral(point, primitive->object.repeat, primitive->object.repeatSpiralStep, primitive->object.repeatSpiralAngle, primitive->object.repeatSpiralRadius); break;
		case 13: pointRepeated = repeatModWave(point, primitive->object.repeat, primitive->object.repeatWaveAmplitude, primitive->object.repeatWaveFrequency, primitive->object.repeatWavePhase, primitive->object.repeatWaveAxis); break;
		default: pointRepeated = repeatMod(point, primitive->object.repeat); break;
	}
	return pointRepeated;
}

float3 ApplyDeformations(float3 point, __global sPrimitiveCl *primitive)
{
	float3 result = point;
	// Bend
	if (primitive->object.deformBendEnable && fabs(primitive->object.deformBendAngle) > 1e-5f)
	{
		float k = primitive->object.deformBendAngle;
		if (primitive->object.deformBendAxis == 0)
		{
			float cx = cos(k * result.x), sx = sin(k * result.x);
			result = (float3){sx / k, result.y, result.z + (1.0f - cx) / k};
		}
		else if (primitive->object.deformBendAxis == 1)
		{
			float cy = cos(k * result.y), sy = sin(k * result.y);
			result = (float3){result.x, sy / k, result.z + (1.0f - cy) / k};
		}
		else
		{
			float cz = cos(k * result.z), sz = sin(k * result.z);
			result = (float3){result.x + (1.0f - cz) / k, result.y, sz / k};
		}
	}
	// Twist
	if (primitive->object.deformTwistEnable && fabs(primitive->object.deformTwistAngle) > 1e-5f)
	{
		float k, c, s;
		if (primitive->object.deformTwistAxis == 0) {
			k = primitive->object.deformTwistAngle * result.x; c = cos(k); s = sin(k);
			result = (float3){result.x, c * result.y - s * result.z, s * result.y + c * result.z};
		}
		else if (primitive->object.deformTwistAxis == 1) {
			k = primitive->object.deformTwistAngle * result.y; c = cos(k); s = sin(k);
			result = (float3){c * result.x - s * result.z, result.y, s * result.x + c * result.z};
		}
		else {
			k = primitive->object.deformTwistAngle * result.z; c = cos(k); s = sin(k);
			result = (float3){c * result.x - s * result.y, s * result.x + c * result.y, result.z};
		}
	}
	// Taper
	if (primitive->object.deformTaperEnable && fabs(primitive->object.deformTaperRate) > 1e-5f)
	{
		float k;
		if (primitive->object.deformTaperAxis == 0) {
			k = max(1.0f + primitive->object.deformTaperRate * result.x, 0.01f);
			result = (float3){result.x, result.y * k, result.z * k};
		}
		else if (primitive->object.deformTaperAxis == 1) {
			k = max(1.0f + primitive->object.deformTaperRate * result.y, 0.01f);
			result = (float3){result.x * k, result.y, result.z * k};
		}
		else {
			k = max(1.0f + primitive->object.deformTaperRate * result.z, 0.01f);
			result = (float3){result.x * k, result.y * k, result.z};
		}
	}
	return result;
}

#ifdef USE_PRIMITIVE_PLANE
float PrimitivePlane(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);
	point = ApplyRepeat(point, primitive);
	float dist = point.z;
	dist = primitive->data.plane.empty ? fabs(dist) : dist;
	dist = max(dist - primitive->object.wallThickness, 0.0f);
	return dist;
}
#endif

#ifdef USE_PRIMITIVE_BOX
float PrimitiveBox(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);
	point = ApplyRepeat(point, primitive);
	point = modRepeat(point, primitive->data.box.repeat);

	float boxDist = -1e6f;
	if (primitive->data.box.empty)
	{
		boxDist = max(fabs(point.x) - primitive->object.size.x * 0.5f, boxDist);
		boxDist = max(fabs(point.y) - primitive->object.size.y * 0.5f, boxDist);
		boxDist = max(fabs(point.z) - primitive->object.size.z * 0.5f, boxDist);
		boxDist = fabs(boxDist);
	}
	else
	{
		float3 boxTemp;
		boxTemp.x = max(fabs(point.x) - primitive->object.size.x * 0.5f, 0.0f);
		boxTemp.y = max(fabs(point.y) - primitive->object.size.y * 0.5f, 0.0f);
		boxTemp.z = max(fabs(point.z) - primitive->object.size.z * 0.5f, 0.0f);
		boxDist = length(boxTemp) - primitive->data.box.rounding;
	}

	boxDist = max(boxDist - primitive->object.wallThickness, 0.0f);

	if (primitive->data.box.limitsEnable)
	{
		float3 distanceAxial =
			max(point - primitive->data.box.limitsMax, primitive->data.box.limitsMin - point);
		float limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		boxDist = max(boxDist, limitBoxDist);
	}
	return boxDist;
}
#endif

#ifdef USE_PRIMITIVE_SPHERE
float PrimitiveSphere(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);
	point = ApplyRepeat(point, primitive);
	point = modRepeat(point, primitive->data.sphere.repeat);
	float dist = length(point) - primitive->data.sphere.radius;
	dist = primitive->data.sphere.empty ? fabs(dist) : dist;
	dist = max(dist - primitive->object.wallThickness, 0.0f);

	if (primitive->data.sphere.limitsEnable)
	{
		float3 distanceAxial =
			max(point - primitive->data.sphere.limitsMax, primitive->data.sphere.limitsMin - point);
		float limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		dist = max(dist, limitBoxDist);
	}
	return dist;
}
#endif

#ifdef USE_PRIMITIVE_RECTANGLE
float PrimitiveRectangle(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);
	point = ApplyRepeat(point, primitive);
	float3 boxTemp;
	boxTemp.x = max(fabs(point.x) - primitive->data.rectangle.width * 0.5f, 0.0f);
	boxTemp.y = max(fabs(point.y) - primitive->data.rectangle.height * 0.5f, 0.0f);
	boxTemp.z = fabs(point.z);
	return length(boxTemp);
}
#endif

#ifdef USE_PRIMITIVE_CYLINDER
float PrimitiveCylinder(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);
	point = ApplyRepeat(point, primitive);
	point = modRepeat(point, primitive->data.cylinder.repeat);
	float2 cylTemp = (float2){point.x, point.y};
	float dist = length(cylTemp) - primitive->data.cylinder.radius;
	if (!primitive->data.cylinder.caps) dist = fabs(dist);
	dist = max(fabs(point.z) - primitive->data.cylinder.height * 0.5f, dist);
	dist = primitive->data.cylinder.empty ? fabs(dist) : dist;
	dist = max(dist - primitive->object.wallThickness, 0.0f);

	if (primitive->data.cylinder.limitsEnable)
	{
		float3 distanceAxial =
			max(point - primitive->data.cylinder.limitsMax, primitive->data.cylinder.limitsMin - point);
		float limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		dist = max(dist, limitBoxDist);
	}
	return dist;
}
#endif

#ifdef USE_PRIMITIVE_CIRCLE
float PrimitiveCircle(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);
	point = ApplyRepeat(point, primitive);
	float2 circleTemp = (float2){point.x, point.y};
	float distTemp = length(circleTemp) - primitive->data.circle.radius;
	distTemp = max(fabs(point.z), distTemp);
	return distTemp;
}
#endif

#ifdef USE_PRIMITIVE_CONE
float PrimitiveCone(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);
	point = ApplyRepeat(point, primitive);
	point = modRepeat(point, primitive->data.cone.repeat);
	point.z -= primitive->data.cone.height;
	float q = sqrt(point.x * point.x + point.y * point.y);
	float2 vect = (float2){q, point.z};
	float dist = dot(primitive->data.cone.wallNormal, vect);
	if (!primitive->data.cone.caps) dist = fabs(dist);
	dist = max(-point.z - primitive->data.cone.height, dist);
	dist = primitive->data.cone.empty ? fabs(dist) : dist;
	dist = max(dist - primitive->object.wallThickness, 0.0f);

	if (primitive->data.cone.limitsEnable)
	{
		float3 distanceAxial =
			max(point - primitive->data.cone.limitsMax, primitive->data.cone.limitsMin - point);
		float limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		dist = max(dist, limitBoxDist);
	}
	return dist;
}
#endif

#ifdef USE_PRIMITIVE_WATER
float PrimitiveWater(__global sPrimitiveCl *primitive, float3 _point, float distanceFromAnother)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);
	point = ApplyRepeat(point, primitive);

	float length = primitive->data.water.length;
	if (primitive->data.water.waveFromObjectsEnable)
	{
		point.x += length * 20.0f * exp(-distanceFromAnother / length / 5.0f)
							 * primitive->data.water.waveFromObjectsRelativeAmplitude;
	}

	float amplitude = length * primitive->data.water.relativeAmplitude;
	float objectWave = 0.0f;

	float planeDistance = point.z;
	if (planeDistance < amplitude * 10.0f)
	{
		float phase = -primitive->data.water.animSpeed * primitive->data.water.animFrame * 0.1f;

		if (primitive->data.water.waveFromObjectsEnable)
		{
			objectWave = sin(distanceFromAnother / length * 5.0f - phase * 2.0f)
									 * exp(-distanceFromAnother / length / 5.0f)
									 * primitive->data.water.waveFromObjectsRelativeAmplitude;
		}

		float k = 0.23f;
		float waveXTemp;
		float waveYTemp;
		float waveX = objectWave;
		float waveY = -objectWave;
		float p = 1.0f;
		float p2 = 0.05f;

		point.x += phase * 0.05f * (primitive->data.water.animProgressionSpeed * 3.0f - 3.0f);

		for (int i = 1; i <= primitive->data.water.iterations; i++)
		{
			float p3 = p * p2;
			float shift = phase / (i / 2.697f + 1.0f);
			waveXTemp = sin(i + 0.4f * (waveX)*p3 + sin(k * point.y / length * p3 + shift * 0.134f * p3)
											+ point.x / length * p3 + shift * p3)
									/ p;
			waveYTemp = cos(i + 0.4f * (waveY)*p3 + sin(point.x / length * p3 + shift * 0.0179f * p3)
											+ k * point.y / length * p3 + shift * 0.023f * p3)
									/ p;
			waveX += waveXTemp;
			waveY += waveYTemp;
			p2 = p2 + (1.0f - p2 + 0.5f * sin(shift * 0.0323f)) * 0.7f;
			p *= 1.872f;
		}

		planeDistance += (waveX + waveY) * amplitude;
	}
	planeDistance = primitive->data.water.empty ? fabs(planeDistance) : planeDistance;
	planeDistance = max(planeDistance - primitive->object.wallThickness, 0.0f);

	if (primitive->data.water.limitsEnable)
	{
		float3 distanceAxial =
			max(point - primitive->data.water.limitsMax, primitive->data.water.limitsMin - point);
		float limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		planeDistance = max(planeDistance, limitBoxDist);
	}
	return planeDistance;
}
#endif

#ifdef USE_PRIMITIVE_TORUS
float PrimitiveTorus(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);
	point = ApplyRepeat(point, primitive);
	point = modRepeat(point, primitive->data.torus.repeat);

	float2 pointXY = (float2){point.x, point.y};
	float d1 =
		LengthPow(pointXY, pow(2.0f, primitive->data.torus.radiusLPow)) - primitive->data.torus.radius;
	float2 pointDZ = (float2){d1, point.z};

	float dist = LengthPow(pointDZ, pow(2.0f, primitive->data.torus.tubeRadiusLPow))
							 - primitive->data.torus.tubeRadius;
	dist = primitive->data.torus.empty ? fabs(dist) : dist;
	dist = max(dist - primitive->object.wallThickness, 0.0f);

	if (primitive->data.torus.limitsEnable)
	{
		float3 distanceAxial =
			max(point - primitive->data.torus.limitsMax, primitive->data.torus.limitsMin - point);
		float limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		dist = max(dist, limitBoxDist);
	}
	return dist;
}
#endif

#ifdef USE_PRIMITIVE_PRISM
float PrimitivePrism(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);
	point = ApplyRepeat(point, primitive);
	point = modRepeat(point, primitive->data.prism.repeat);

	float3 q = fabs(point);

	float prismDistance = max(q.z - primitive->data.prism.height,
		max(q.x * primitive->data.prism.normals.y + point.y * primitive->data.prism.normals.z,
			-point.y + primitive->data.prism.triangleHeight)
			- primitive->data.prism.triangleHeight);

	prismDistance = primitive->data.prism.empty ? fabs(prismDistance) : prismDistance;
	prismDistance = max(prismDistance - primitive->object.wallThickness, 0.0f);

	return prismDistance;
}
#endif

#ifdef USE_PRIMITIVE_ELLIPSOID
float PrimitiveEllipsoid(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);
	point = ApplyRepeat(point, primitive);
	point = modRepeat(point, primitive->data.ellipsoid.repeat);

	float k0 = length(point / primitive->object.size);
	float k1 = length(point / (primitive->object.size * primitive->object.size));
	float dist = k0 * (k0 - 1.0f) / k1;

	dist = primitive->data.ellipsoid.empty ? fabs(dist) : dist;
	dist = max(dist - primitive->object.wallThickness, 0.0f);

	if (primitive->data.ellipsoid.limitsEnable)
	{
		float3 distanceAxial =
			max(point - primitive->data.ellipsoid.limitsMax, primitive->data.ellipsoid.limitsMin - point);
		float limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		dist = max(dist, limitBoxDist);
	}
	return dist;
}
#endif

#ifdef USE_PRIMITIVE_CAPSULE
float PrimitiveCapsule(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);
	point = ApplyRepeat(point, primitive);
	point = modRepeat(point, primitive->data.capsule.repeat);

	float halfH = primitive->data.capsule.height * 0.5f;
	point.z -= clamp(point.z, -halfH, halfH);
	float dist = length(point) - primitive->data.capsule.radius;

	dist = primitive->data.capsule.empty ? fabs(dist) : dist;
	dist = max(dist - primitive->object.wallThickness, 0.0f);

	if (primitive->data.capsule.limitsEnable)
	{
		float3 distanceAxial =
			max(point - primitive->data.capsule.limitsMax, primitive->data.capsule.limitsMin - point);
		float limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		dist = max(dist, limitBoxDist);
	}
	return dist;
}
#endif

#ifdef USE_PRIMITIVE_HEXPRISM
float PrimitiveHexPrism(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);
	point = ApplyRepeat(point, primitive);
	point = modRepeat(point, primitive->data.hexprism.repeat);

	float r = primitive->object.size.x;
	float3 absP = (float3)(fabs(point.x), fabs(point.y), fabs(point.z));
	float k = -0.8660254037844386f;
	float px = absP.x, py = absP.y;
	float t = 2.0f * min(k * px + 0.5f * py, 0.0f);
	px -= t * k;
	py -= t * 0.5f;
	px -= clamp(px, -r, r);
	float d2d = native_sqrt(px * px + max(py - r, 0.0f) * max(py - r, 0.0f))
		* ((py - r > 0.0f) ? 1.0f : -1.0f);
	float dist = max(d2d, absP.z - primitive->data.hexprism.height * 0.5f);

	dist = primitive->data.hexprism.empty ? fabs(dist) : dist;
	dist = max(dist - primitive->object.wallThickness, 0.0f);

	if (primitive->data.hexprism.limitsEnable)
	{
		float3 distanceAxial =
			max(point - primitive->data.hexprism.limitsMax, primitive->data.hexprism.limitsMin - point);
		float limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		dist = max(dist, limitBoxDist);
	}
	return dist;
}
#endif

#ifdef USE_PRIMITIVE_LAVAPLANE
float PrimitiveLavaPlane(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);

	float displacement = 0.0f;
	float freq = 1.0f / max(primitive->data.lavaplane.waveScale, 1e-10f);
	float amp = primitive->data.lavaplane.waveHeight;
	for (int i = 0; i < primitive->data.lavaplane.waveOctaves; i++)
	{
		displacement += amp * native_sin(point.x * freq) * native_cos(point.y * freq);
		freq *= 2.0f;
		amp *= 0.5f;
	}
	float dist = point.z - displacement;
	dist = primitive->data.lavaplane.empty ? fabs(dist) : dist;
	return dist;
}
#endif

#ifdef USE_PRIMITIVE_OCTAHEDRON
float PrimitiveOctahedron(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);
	point = ApplyRepeat(point, primitive);
	point = modRepeat(point, primitive->data.octahedron.repeat);

	float s = primitive->object.size.x;
	float3 absP = (float3)(fabs(point.x), fabs(point.y), fabs(point.z));
	float dist = (absP.x + absP.y + absP.z - s) * 0.57735026919f;

	dist = primitive->data.octahedron.empty ? fabs(dist) : dist;
	dist = max(dist - primitive->object.wallThickness, 0.0f);

	if (primitive->data.octahedron.limitsEnable)
	{
		float3 distanceAxial =
			max(point - primitive->data.octahedron.limitsMax, primitive->data.octahedron.limitsMin - point);
		float limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		dist = max(dist, limitBoxDist);
	}
	return dist;
}
#endif

#ifdef USE_PRIMITIVE_PYRAMID
float PrimitivePyramid(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);
	point = ApplyRepeat(point, primitive);
	point = modRepeat(point, primitive->data.pyramid.repeat);

	float h = max(primitive->data.pyramid.height, 1e-10f);
	float b = max(primitive->data.pyramid.baseSize, 1e-10f) * 0.5f;
	float m2 = h * h / (b * b);
	float3 absP = (float3)(fabs(point.x), fabs(point.y), point.z);
	absP.x -= clamp(absP.x, -b, b);
	absP.y -= clamp(absP.y, -b, b);
	float d1 = max(absP.x, absP.y);
	float d2 = (point.z - h) * m2 / native_sqrt(m2 + 1.0f);
	float distBase = -point.z;
	float dist = max(d1, max(d2, distBase));

	dist = primitive->data.pyramid.empty ? fabs(dist) : dist;
	dist = max(dist - primitive->object.wallThickness, 0.0f);

	if (primitive->data.pyramid.limitsEnable)
	{
		float3 distanceAxial =
			max(point - primitive->data.pyramid.limitsMax, primitive->data.pyramid.limitsMin - point);
		float limitBoxDist = max(max(distanceAxial.x, distanceAxial.y), distanceAxial.z);
		dist = max(dist, limitBoxDist);
	}
	return dist;
}
#endif

#ifdef USE_PRIMITIVE_TERRAINPLANE
float terrainHashCl(float x, float y)
{
	float n = native_sin(x * 127.1f + y * 311.7f) * 43758.5453123f;
	return n - floor(n);
}

float terrainNoiseCl(float x, float y)
{
	float ix = floor(x), iy = floor(y);
	float fx = x - ix, fy = y - iy;
	fx = fx * fx * (3.0f - 2.0f * fx);
	fy = fy * fy * (3.0f - 2.0f * fy);
	float a = terrainHashCl(ix, iy);
	float b = terrainHashCl(ix + 1.0f, iy);
	float c = terrainHashCl(ix, iy + 1.0f);
	float d = terrainHashCl(ix + 1.0f, iy + 1.0f);
	return a + (b - a) * fx + (c - a) * fy + (a - b - c + d) * fx * fy;
}

float terrainFBMCl(float x, float y, int octs, float rough, float lac)
{
	float value = 0.0f, amp = 1.0f, freq = 1.0f, maxAmp = 0.0f;
	for (int i = 0; i < octs; i++)
	{
		value += amp * (terrainNoiseCl(x * freq, y * freq) * 2.0f - 1.0f);
		maxAmp += amp;
		amp *= rough;
		freq *= lac;
	}
	return value / max(maxAmp, 1e-10f);
}

float PrimitiveTerrainPlane(__global sPrimitiveCl *primitive, float3 _point)
{
	float3 point = TransformPrimitivePoint(primitive, _point);
	point = ApplyDeformations(point, primitive);

	float freq = max(primitive->data.terrainplane.frequency, 1e-10f);
	float px = point.x * freq;
	float py = point.y * freq;
	float amp = primitive->data.terrainplane.amplitude;
	float rough = primitive->data.terrainplane.roughness;
	float lac = primitive->data.terrainplane.lacunarity;
	float ds = primitive->data.terrainplane.detailScale;
	float eros = primitive->data.terrainplane.erosion;
	int octs = primitive->data.terrainplane.octaves;
	float displacement = 0.0f;

	switch (primitive->data.terrainplane.terrainType)
	{
		case 0: // Sand
		{
			displacement = amp * terrainFBMCl(px, py, octs, 0.4f, lac);
			displacement += native_sin(px * 8.0f + py * 3.0f) * amp * 0.15f * ds;
			break;
		}
		case 1: // Mud
		{
			float base = terrainFBMCl(px * 0.5f, py * 0.5f, octs, rough, lac);
			float cracks = fabs(terrainFBMCl(px * 3.0f, py * 3.0f, 3, 0.5f, 2.0f));
			displacement = amp * (base * 0.7f - cracks * 0.3f * ds);
			break;
		}
		case 2: // Ice
		{
			float flat = terrainFBMCl(px, py, octs, 0.3f, lac) * 0.1f;
			float crack = fabs(terrainFBMCl(px * 4.0f, py * 4.0f, 4, 0.5f, 2.0f));
			crack = crack * crack * crack;
			displacement = amp * (flat - crack * ds * 0.5f);
			break;
		}
		case 3: // Grass
		{
			float base = terrainFBMCl(px, py, octs, rough, lac);
			float micro = terrainFBMCl(px * 10.0f, py * 10.0f, 3, 0.6f, 2.0f) * ds * 0.2f;
			displacement = amp * (base + micro);
			break;
		}
		case 4: // Rock
		{
			displacement = amp * terrainFBMCl(px, py, octs, rough, lac);
			float sharp = terrainFBMCl(px * 2.0f, py * 2.0f, 4, 0.7f, 2.5f);
			displacement += amp * fabs(sharp) * ds * 0.3f;
			break;
		}
		case 5: // Snow
		{
			displacement = amp * terrainFBMCl(px * 0.7f, py * 0.7f, octs, 0.35f, lac);
			displacement += native_sin(px * 2.0f + py * 0.5f) * amp * 0.2f;
			break;
		}
		case 6: // Magma
		{
			float turb = 0.0f, tF = 1.0f, tA = 1.0f;
			for (int i = 0; i < octs; i++)
			{
				turb += tA * fabs(terrainNoiseCl(px * tF, py * tF) * 2.0f - 1.0f);
				tA *= rough;
				tF *= lac;
			}
			displacement = amp * turb * (1.0f - eros * 0.5f);
			break;
		}
		case 7: // Crystal
		{
			float n = terrainFBMCl(px, py, octs, rough, lac);
			float dsc = max(ds, 1e-10f);
			displacement = amp * floor(n * 6.0f * dsc) / (6.0f * dsc);
			break;
		}
		case 8: // Moss
		{
			float base = terrainFBMCl(px * 0.8f, py * 0.8f, octs, 0.5f, lac);
			float bumps = 0.5f + 0.5f * terrainFBMCl(px * 5.0f, py * 5.0f, 3, 0.4f, 2.0f);
			bumps = bumps * bumps;
			displacement = amp * (base * 0.6f + bumps * 0.4f * ds);
			break;
		}
		case 9: // Volcanic
		{
			float n = terrainFBMCl(px, py, octs, rough, lac);
			float er = max(eros, 0.01f);
			float shaped = (n > 0.0f) ? pow(n, 0.5f + er) : -pow(-n, 0.5f + er);
			displacement = amp * shaped;
			break;
		}
		case 10: // Dunes
		{
			float mainWave = native_sin(px * 3.0f + py * 1.5f) * 0.5f + 0.5f;
			mainWave = pow(mainWave, 1.5f);
			float detail = terrainFBMCl(px * 4.0f, py * 4.0f, 3, 0.4f, 2.0f) * ds * 0.15f;
			displacement = amp * (mainWave + detail);
			break;
		}
		case 11: // Coral
		{
			float n1 = terrainFBMCl(px, py, octs, rough, lac);
			float n2 = terrainFBMCl(px + 5.2f, py + 1.3f, octs, rough, lac);
			float warp = terrainFBMCl(px + n1 * 2.0f, py + n2 * 2.0f, 3, 0.5f, 2.0f);
			displacement = amp * warp * ds;
			break;
		}
		default:
			displacement = amp * terrainFBMCl(px, py, octs, rough, lac);
			break;
	}

	float dist = point.z - displacement;
	dist = primitive->data.terrainplane.empty ? fabs(dist) : dist;
	return dist;
}
#endif

// Helper: evaluate one primitive's distance (all clones, all types)
float EvaluatePrimitiveDistCl(sRenderData *renderData, __global sPrimitiveCl *primitive,
	float3 point2, float currentDist)
{
	int cloneCount = primitive->object.clonerEnabled ? primitive->object.clonerCount : 1;
	float distTemp = 1e20f;

	for (int ci = 0; ci < cloneCount; ci++)
	{
		sCloneTransformCl cloneTransform = ApplyCloneTransformOpenCL(primitive, ci);
		float3 point3 = point2 - cloneTransform.offset;

		if (length(cloneTransform.rotation) > 1e-10f)
		{
			matrix33 cloneRotMatrix = (matrix33){
				(float3){1.0f, 0.0f, 0.0f},
				(float3){0.0f, 1.0f, 0.0f},
				(float3){0.0f, 0.0f, 1.0f}};
			cloneRotMatrix = RotateZ(cloneRotMatrix, cloneTransform.rotation.z * M_PI_F / 180.0f);
			cloneRotMatrix = RotateY(cloneRotMatrix, cloneTransform.rotation.y * M_PI_F / 180.0f);
			cloneRotMatrix = RotateX(cloneRotMatrix, cloneTransform.rotation.x * M_PI_F / 180.0f);
			point3 = Matrix33MulFloat3(cloneRotMatrix, point3);
		}

		float minCloneScale = 1.0f;
		if (cloneTransform.scale.x > 1e-10f && cloneTransform.scale.y > 1e-10f
				&& cloneTransform.scale.z > 1e-10f)
		{
			point3.x /= cloneTransform.scale.x;
			point3.y /= cloneTransform.scale.y;
			point3.z /= cloneTransform.scale.z;
			minCloneScale = fmin(cloneTransform.scale.x, fmin(cloneTransform.scale.y, cloneTransform.scale.z));
		}

		float dTemp = 0.0f;

		switch (primitive->object.objectType)
		{
#ifdef USE_PRIMITIVE_PLANE
			case objPlane: dTemp = PrimitivePlane(primitive, point3); break;
#endif
#ifdef USE_PRIMITIVE_BOX
			case objBox: dTemp = PrimitiveBox(primitive, point3); break;
#endif
#ifdef USE_PRIMITIVE_SPHERE
			case objSphere: dTemp = PrimitiveSphere(primitive, point3); break;
#endif
#ifdef USE_PRIMITIVE_RECTANGLE
			case objRectangle: dTemp = PrimitiveRectangle(primitive, point3); break;
#endif
#ifdef USE_PRIMITIVE_CYLINDER
			case objCylinder: dTemp = PrimitiveCylinder(primitive, point3); break;
#endif
#ifdef USE_PRIMITIVE_CIRCLE
			case objCircle: dTemp = PrimitiveCircle(primitive, point3); break;
#endif
#ifdef USE_PRIMITIVE_CONE
			case objCone: dTemp = PrimitiveCone(primitive, point3); break;
#endif
#ifdef USE_PRIMITIVE_WATER
			case objWater: dTemp = PrimitiveWater(primitive, point3, currentDist); break;
#endif
#ifdef USE_PRIMITIVE_TORUS
			case objTorus: dTemp = PrimitiveTorus(primitive, point3); break;
#endif
#ifdef USE_PRIMITIVE_PRISM
			case objPrism: dTemp = PrimitivePrism(primitive, point3); break;
#endif
#ifdef USE_PRIMITIVE_ELLIPSOID
			case objEllipsoid: dTemp = PrimitiveEllipsoid(primitive, point3); break;
#endif
#ifdef USE_PRIMITIVE_CAPSULE
			case objCapsule: dTemp = PrimitiveCapsule(primitive, point3); break;
#endif
#ifdef USE_PRIMITIVE_HEXPRISM
			case objHexPrism: dTemp = PrimitiveHexPrism(primitive, point3); break;
#endif
#ifdef USE_PRIMITIVE_LAVAPLANE
			case objLavaPlane: dTemp = PrimitiveLavaPlane(primitive, point3, currentDist); break;
#endif
#ifdef USE_PRIMITIVE_OCTAHEDRON
			case objOctahedron: dTemp = PrimitiveOctahedron(primitive, point3); break;
#endif
#ifdef USE_PRIMITIVE_PYRAMID
			case objPyramid: dTemp = PrimitivePyramid(primitive, point3); break;
#endif
#ifdef USE_PRIMITIVE_TERRAINPLANE
			case objTerrainPlane: dTemp = PrimitiveTerrainPlane(primitive, point3); break;
#endif
			default: break;
		}

		dTemp *= GetPrimitiveMinScale(primitive);
		dTemp *= minCloneScale;
		if (dTemp < distTemp) distTemp = dTemp;
	}
	return distTemp;
}

// Helper: apply boolean operator on GPU
void ApplyBooleanOpCl(int booleanOp, float *distance, float distTemp,
	float detailSize, bool normalCalculationMode, int *closestObject, int objectId,
	bool smoothEnable, float smoothDist)
{
	switch (booleanOp)
	{
		case clPrimBooleanOperatorOR:
		{
			if (distTemp < *distance) *closestObject = objectId;
			if (smoothEnable)
				*distance = opSmoothUnion(distTemp, *distance, smoothDist);
			else
				*distance = fmin(*distance, distTemp);
			break;
		}
		case clPrimBooleanOperatorAND:
		{
			if (distTemp > *distance) *closestObject = objectId;
			*distance = fmax(*distance, distTemp);
			break;
		}
		case clPrimBooleanOperatorSUB:
		{
			const float limit = 1.5f;
			if (*distance < detailSize)
			{
				if (distTemp < detailSize * limit * 1.5f) *closestObject = objectId;
				if (distTemp < detailSize * limit)
				{
					if (normalCalculationMode)
						*distance = fmax(detailSize * limit - distTemp, *distance);
					else
						*distance = detailSize * limit;
				}
				else
				{
					*distance = fmax(detailSize * limit - distTemp, *distance);
					if (*distance < 0.0f) *distance = 0.0f;
				}
			}
			break;
		}
		case clPrimBooleanOperatorRevSUB:
		{
			int closestObjectTemp = *closestObject;
			*closestObject = objectId;
			const float limit = 1.5f;
			if (distTemp < detailSize)
			{
				if (*distance < detailSize * limit * 1.5f) *closestObject = closestObjectTemp;
				if (*distance < detailSize * limit)
				{
					if (normalCalculationMode)
						*distance = fmax(detailSize * limit - *distance, distTemp);
					else
						*distance = detailSize * limit;
				}
				else
				{
					distTemp = fmax(detailSize * limit - *distance, distTemp);
					*distance = distTemp;
					if (*distance < 0.0f) *distance = 0.0f;
				}
			}
			else
			{
				*distance = distTemp;
			}
			break;
		}
		case clPrimBooleanOperatorSmoothOR:
		{
			float r = smoothDist;
			if (r < 1e-10f) r = 0.1f;
			if (distTemp < *distance) *closestObject = objectId;
			*distance = opSmoothUnion(distTemp, *distance, r);
			break;
		}
		case clPrimBooleanOperatorSmoothAND:
		{
			float r = smoothDist;
			if (r < 1e-10f) r = 0.1f;
			if (distTemp > *distance) *closestObject = objectId;
			*distance = opSmoothIntersection(*distance, distTemp, r);
			break;
		}
		case clPrimBooleanOperatorSmoothSUB:
		{
			float r = smoothDist;
			if (r < 1e-10f) r = 0.1f;
			if (distTemp < detailSize) *closestObject = objectId;
			*distance = opSmoothSubtraction(distTemp, *distance, r);
			break;
		}
	}
}

#define MAX_GROUPS_CL 32

float TotalDistanceToPrimitives(__constant sClInConstants *consts, sRenderData *renderData,
	float3 point, float fractalDistance, float detailSize, bool normalCalculationMode,
	int *closestObjectId, int objectIdForVolumetrics)
{
	int numberOfPrimitives = renderData->numberOfPrimitives;
	int closestObject = *closestObjectId;
	float dist = fractalDistance;

	float3 point2 = point - renderData->primitivesGlobalData->allPrimitivesPosition;
	point2 = Matrix33MulFloat3(renderData->primitivesGlobalData->mRotAllPrimitivesRotation, point2);

	// Group-aware boolean evaluation
	// Pass 1: evaluate groups
	float groupDist[MAX_GROUPS_CL];
	int groupClosest[MAX_GROUPS_CL];
	int groupIds[MAX_GROUPS_CL];
	int groupBoolOps[MAX_GROUPS_CL];
	float groupSmoothR[MAX_GROUPS_CL];
	bool groupActive[MAX_GROUPS_CL];
	int numGroups = 0;

	// Initialize
	for (int g = 0; g < MAX_GROUPS_CL; g++)
	{
		groupDist[g] = 1e20f;
		groupClosest[g] = -1;
		groupActive[g] = false;
	}

	// First pass: evaluate grouped primitives
	for (int i = 0; i < numberOfPrimitives; i++)
	{
		__global sPrimitiveCl *primitive = &renderData->primitives[i];
		if (!primitive->object.enable) continue;
		if (!primitive->object.groupEnabled) continue;
		if (primitive->object.groupId <= 0) continue;

		int gid = primitive->object.groupId;

		// Find or allocate group slot
		int gSlot = -1;
		for (int g = 0; g < numGroups; g++)
		{
			if (groupIds[g] == gid) { gSlot = g; break; }
		}
		if (gSlot < 0 && numGroups < MAX_GROUPS_CL)
		{
			gSlot = numGroups++;
			groupIds[gSlot] = gid;
			groupDist[gSlot] = 1e20f;
			groupClosest[gSlot] = -1;
			groupBoolOps[gSlot] = primitive->object.groupBooleanOperator;
			groupSmoothR[gSlot] = primitive->object.groupSmoothRadius;
			groupActive[gSlot] = true;
		}
		if (gSlot < 0) continue;

		float distTemp = EvaluatePrimitiveDistCl(renderData, primitive, point2, groupDist[gSlot]);

		if (objectIdForVolumetrics == primitive->object.objectId)
		{
			*closestObjectId = primitive->object.objectId;
			return distTemp;
		}
		if (primitive->object.usedForVolumetric) continue;

		// First member in group: set distance directly
		if (groupDist[gSlot] >= 1e19f)
		{
			groupDist[gSlot] = distTemp;
			groupClosest[gSlot] = primitive->object.objectId;
		}
		else
		{
			ApplyBooleanOpCl(primitive->booleanOperator, &groupDist[gSlot], distTemp,
				detailSize, normalCalculationMode, &groupClosest[gSlot],
				primitive->object.objectId, primitive->object.smoothDeCombineEnable,
				primitive->object.smoothDeCombineDistance);
		}
	}

	// Combine group results into scene
	for (int g = 0; g < numGroups; g++)
	{
		if (!groupActive[g] || groupDist[g] >= 1e19f) continue;
		ApplyBooleanOpCl(groupBoolOps[g], &dist, groupDist[g],
			detailSize, normalCalculationMode, &closestObject,
			groupClosest[g], true, groupSmoothR[g]);
	}

	// Second pass: evaluate ungrouped primitives (flat chain, backward compatible)
	for (int i = 0; i < numberOfPrimitives; i++)
	{
		__global sPrimitiveCl *primitive = &renderData->primitives[i];
		if (!primitive->object.enable) continue;
		if (!primitive->object.groupEnabled) continue;
		if (primitive->object.groupId > 0) continue;

		float distTemp = EvaluatePrimitiveDistCl(renderData, primitive, point2, dist);

		if (objectIdForVolumetrics == primitive->object.objectId)
		{
			*closestObjectId = primitive->object.objectId;
			return distTemp;
		}
		if (primitive->object.usedForVolumetric) continue;

#ifdef USE_DISPLACEMENT_TEXTURE
		distTemp = DisplacementMap(distTemp, point2, primitive->object.objectId, renderData, 1.0f);
#endif

#if defined(USE_PERLIN_NOISE) && defined(USE_PERLIN_NOISE_DISPLACEMENT)
		distTemp = PerlinNoiseDisplacement(distTemp, point2, renderData, primitive->object.objectId);
#endif

		// Boolean target: if targeting a specific group, combine with that group
		if (primitive->object.booleanTargetGroupId >= 0)
		{
			int targetSlot = -1;
			for (int g = 0; g < numGroups; g++)
			{
				if (groupIds[g] == primitive->object.booleanTargetGroupId)
				{
					targetSlot = g;
					break;
				}
			}
			if (targetSlot >= 0 && groupActive[targetSlot])
			{
				ApplyBooleanOpCl(primitive->booleanOperator, &groupDist[targetSlot], distTemp,
					detailSize, normalCalculationMode, &groupClosest[targetSlot],
					primitive->object.objectId, primitive->object.smoothDeCombineEnable,
					primitive->object.smoothDeCombineDistance);
				// Re-combine groups into scene
				dist = fractalDistance;
				closestObject = *closestObjectId;
				for (int g = 0; g < numGroups; g++)
				{
					if (!groupActive[g] || groupDist[g] >= 1e19f) continue;
					ApplyBooleanOpCl(groupBoolOps[g], &dist, groupDist[g],
						detailSize, normalCalculationMode, &closestObject,
						groupClosest[g], true, groupSmoothR[g]);
				}
				continue;
			}
		}

		ApplyBooleanOpCl(primitive->booleanOperator, &dist, distTemp,
			detailSize, normalCalculationMode, &closestObject,
			primitive->object.objectId, primitive->object.smoothDeCombineEnable,
			primitive->object.smoothDeCombineDistance);
	}

	*closestObjectId = closestObject;
	return dist;
}

#endif // USE_PRIMITIVES

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
	if (primitive->object.useWorldSpacePivot)
	{
		float3 point = _point - primitive->object.pivot;
		point = Matrix33MulFloat3(primitive->object.rotationMatrix, point);
		point = point + primitive->object.pivot;
		point = point - primitive->object.position;
		return point;
	}
	else
	{
		float3 point = _point - primitive->object.position;
		point = point - primitive->object.pivot;
		point = Matrix33MulFloat3(primitive->object.rotationMatrix, point);
		point = point + primitive->object.pivot;
		return point;
	}
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

float TotalDistanceToPrimitives(__global const sClInConstants *consts, sRenderData *renderData,
	float3 point, float fractalDistance, float detailSize, bool normalCalculationMode,
	int *closestObjectId, int objectIdForVolumetrics)
{
	int numberOfPrimitives = renderData->numberOfPrimitives;
	int closestObject = *closestObjectId;
	float dist = fractalDistance;

	float3 point2 = point - renderData->primitivesGlobalData->allPrimitivesPosition;
	point2 = Matrix33MulFloat3(renderData->primitivesGlobalData->mRotAllPrimitivesRotation, point2);

	for (int i = 0; i < numberOfPrimitives; i++)
	{
		__global sPrimitiveCl *primitive = &renderData->primitives[i];

		if (primitive->object.enable)
		{
			int cloneCount = primitive->object.clonerEnabled ? primitive->object.clonerCount : 1;
			float distTemp = 1e20f;

			for (int ci = 0; ci < cloneCount; ci++)
			{
				sCloneTransformCl cloneTransform = ApplyCloneTransformOpenCL(primitive, ci);
				float3 point3 = point2 - cloneTransform.offset;

				// Apply per-clone rotation
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

				// Apply per-clone scale
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
					case objPlane:
					{
						dTemp = PrimitivePlane(primitive, point3);
						break;
					}
#endif

#ifdef USE_PRIMITIVE_BOX
					case objBox:
					{
						dTemp = PrimitiveBox(primitive, point3);
						break;
					}
#endif

#ifdef USE_PRIMITIVE_SPHERE
					case objSphere:
					{
						dTemp = PrimitiveSphere(primitive, point3);
						break;
					}
#endif

#ifdef USE_PRIMITIVE_RECTANGLE
					case objRectangle:
					{
						dTemp = PrimitiveRectangle(primitive, point3);
						break;
					}
#endif

#ifdef USE_PRIMITIVE_CYLINDER
					case objCylinder:
					{
						dTemp = PrimitiveCylinder(primitive, point3);
						break;
					}
#endif

#ifdef USE_PRIMITIVE_CIRCLE
					case objCircle:
					{
						dTemp = PrimitiveCircle(primitive, point3);
						break;
					}
#endif

#ifdef USE_PRIMITIVE_CONE
					case objCone:
					{
						dTemp = PrimitiveCone(primitive, point3);
						break;
					}
#endif

#ifdef USE_PRIMITIVE_WATER
					case objWater:
					{
						dTemp = PrimitiveWater(primitive, point3, dist);
						break;
					}
#endif

#ifdef USE_PRIMITIVE_TORUS
					case objTorus:
					{
						dTemp = PrimitiveTorus(primitive, point3);
						break;
					}
#endif

#ifdef USE_PRIMITIVE_PRISM
					case objPrism:
					{
						dTemp = PrimitivePrism(primitive, point3);
						break;
					}
#endif

#ifdef USE_PRIMITIVE_ELLIPSOID
					case objEllipsoid:
					{
						dTemp = PrimitiveEllipsoid(primitive, point3);
						break;
					}
#endif

					default: break;
				}

				dTemp *= minCloneScale;
				if (dTemp < distTemp)
					distTemp = dTemp;
			}

			if (objectIdForVolumetrics == primitive->object.objectId)
			{
				return distTemp;
			}
			else
			{
				if (primitive->object.usedForVolumetric)
					continue; // skip distance calculation if primitive is used for volumetric effects
			}

#ifdef USE_DISPLACEMENT_TEXTURE
			distTemp = DisplacementMap(distTemp, point2, primitive->object.objectId, renderData, 1.0f);
#endif

#if defined(USE_PERLIN_NOISE) && defined(USE_PERLIN_NOISE_DISPLACEMENT)
			distTemp = PerlinNoiseDisplacement(distTemp, point2, renderData, primitive->object.objectId);
#endif // USE_PERLIN_NOISE

			switch (primitive->booleanOperator)
			{
				case clPrimBooleanOperatorOR:
				{
					if (distTemp < dist)
					{
						closestObject = primitive->object.objectId;
					}

					if (primitive->object.smoothDeCombineEnable)
					{
						dist = opSmoothUnion(distTemp, dist, primitive->object.smoothDeCombineDistance);
					}
					else
					{
						dist = min(distTemp, dist);
					}
					break;
				}
				case clPrimBooleanOperatorAND:
				{
					if (distTemp > dist)
					{
						closestObject = primitive->object.objectId;
					}
					dist = max(dist, distTemp);
					break;
				}
				case clPrimBooleanOperatorSUB:
				{
					const float limit = 1.5f;
					if (dist < detailSize) // if inside 1st
					{
						if (distTemp < detailSize * limit * 1.5f)
						{
							closestObject = primitive->object.objectId;
						}

						if (distTemp < detailSize * limit) // if inside 2nd
						{
							if (normalCalculationMode)
							{
								dist = max(detailSize * limit - distTemp, dist);
							}
							else
							{
								dist = detailSize * limit;
							}
						}
						else // if outside of 2nd
						{
							dist = max(detailSize * limit - distTemp, dist);
							if (dist < 0.0f) dist = 0.0f;
						}
					}
					break;
				}
				case clPrimBooleanOperatorRevSUB:
				{
					int closestObjectTemp = closestObject;
					closestObject = primitive->object.objectId;
					const float limit = 1.5f;
					if (distTemp < detailSize) // if inside 2nd
					{
						if (dist < detailSize * limit * 1.5f)
						{
							closestObject = closestObjectTemp;
						}

						if (dist < detailSize * limit) // if inside 1st
						{
							if (normalCalculationMode)
							{
								dist = max(detailSize * limit - dist, distTemp);
							}
							else
							{
								dist = detailSize * limit;
							}
						}
						else // if outside of 1st
						{
							distTemp = max(detailSize * limit - dist, distTemp);
							dist = distTemp;
							if (dist < 0.0f) dist = 0.0f;
						}
					}
					else
					{
						dist = distTemp;
					}
					break;
				}
			} // switch
		}
	}

	*closestObjectId = closestObject;
	return dist;
}

#endif // USE_PRIMITIVES

/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2017-26 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * Single Trap Light v1 - OpenCL shader
 * Parallel to src/single_trap_light_shader.cpp (CPU version)
 */

#define SINGLE_TRAP_FALLOFF_RADIUS 5.0f  /* hardcoded v1, matches CPU kFalloffRadius */

/* Build rotation matrix from Euler angles in degrees
 * Matches CPU CRotationMatrix::SetRotation2 (Z-Y-X order)
 */
static inline float3 RotateVectorByEulerDegrees(float3 v, float3 euler_deg)
{
	// Identity matrix
	matrix33 rot;
	rot.m1 = (float3)(1.0f, 0.0f, 0.0f);
	rot.m2 = (float3)(0.0f, 1.0f, 0.0f);
	rot.m3 = (float3)(0.0f, 0.0f, 1.0f);

	// Convert degrees → radians
	float3 euler_rad = euler_deg * (M_PI_F / 180.0f);

	// Apply rotations: Z → Y → X (matching CPU SetRotation2)
	rot = RotateZ(rot, euler_rad.z);
	rot = RotateY(rot, euler_rad.y);
	rot = RotateX(rot, euler_rad.x);

	return Matrix33MulFloat3(rot, v);
}

/* Capsule SDF — identiek aan CPU implementation */
static inline float SingleTrapDistanceGPU(float3 point, __global const sClSingleTrapLight *light)
{
	/* Rotate local half-axis (0, size/2, 0) to world space */
	float3 half_local = (float3)(0.0f, light->size * 0.5f, 0.0f);
	float3 half_world = RotateVectorByEulerDegrees(half_local, light->rotation);

	float3 a = light->center - half_world;
	float3 b = light->center + half_world;

	/* Standard capsule SDF */
	float3 pa = point - a;
	float3 ba = b - a;
	float denom = dot(ba, ba);
	if (denom < 1e-20f)
	{
		/* Degenerate: size ≈ 0 → sphere at center */
		return length(point - light->center) - light->radius;
	}
	float h = clamp(dot(pa, ba) / denom, 0.0f, 1.0f);
	return length(pa - ba * h) - light->radius;
}

/* Hermite smooth falloff */
static inline float SingleTrapFalloffGPU(float distance, float falloff_radius)
{
	if (distance >= falloff_radius) return 0.0f;
	if (distance <= 0.0f) return 1.0f;
	float t = (falloff_radius - distance) / falloff_radius;
	t = clamp(t, 0.0f, 1.0f);
	return t * t * (3.0f - 2.0f * t);
}

/* Full evaluation — returns RGB contribution */
float3 SingleTrapLightShaderGPU(__constant sClInConstants *consts, float3 point)
{
	__global const sClSingleTrapLight *light = &consts->params.singleTrapLight0;

	if (light->enabled == 0) return (float3)(0.0f, 0.0f, 0.0f);

	float dist = SingleTrapDistanceGPU(point, light);
	if (dist >= SINGLE_TRAP_FALLOFF_RADIUS) return (float3)(0.0f, 0.0f, 0.0f);

	float falloff = SingleTrapFalloffGPU(dist, SINGLE_TRAP_FALLOFF_RADIUS);
	float weight = light->intensity * falloff;

	/* color is already in float (0..1 range) — converted in copy function */
	return light->color * weight;
}

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
 * Glow Sphere - OpenCL shader (renders visible sphere + emits light)
 */

#define GLOW_SPHERE_FALLOFF_RADIUS 5.0f

/* Sphere SDF */
static inline float GlowSphereDistance(float3 point, float3 position, float radius)
{
	return length(point - position) - radius;
}

/* Hermite smooth falloff */
static inline float GlowSphereFalloff(float distance, float falloff_radius)
{
	if (distance >= falloff_radius) return 0.0f;
	if (distance <= 0.0f) return 1.0f;
	float t = (falloff_radius - distance) / falloff_radius;
	t = clamp(t, 0.0f, 1.0f);
	return t * t * (3.0f - 2.0f * t);
}

/* Returns RGB glow contribution */
float3 GlowSphereShaderGPU(__constant sClInConstants *consts, float3 point)
{
	__constant sGlowSphereCl *sphere = &consts->params.glowSphere1;

	if (sphere->enabled == 0) return (float3)(0.0f, 0.0f, 0.0f);

	float dist = GlowSphereDistance(point, sphere->position, sphere->radius);
	if (dist >= GLOW_SPHERE_FALLOFF_RADIUS) return (float3)(0.0f, 0.0f, 0.0f);

	float falloff = GlowSphereFalloff(dist, GLOW_SPHERE_FALLOFF_RADIUS);
	float weight = sphere->intensity * falloff;

	return sphere->color * weight;
}

/* Returns distance to sphere surface (for ray-marching - makes sphere solid/visible) */
float GlowSphereDistanceGPU(__constant sClInConstants *consts, float3 point)
{
	__constant sGlowSphereCl *sphere = &consts->params.glowSphere1;

	if (sphere->enabled == 0) return 1e20f;  // infinite distance if disabled

	return GlowSphereDistance(point, sphere->position, sphere->radius);
}

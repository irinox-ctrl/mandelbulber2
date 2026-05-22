/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2017-26 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
 *                                        ,=mm=§M ]=4 yJKA"/-Nsaj  "Bw,==,,
 * This file is part of Mandelbulber.    §R.r= jw",M  Km .mM  FW ",§=ß., ,TN
 *                                     ,4R =%["w[N=7]J '"5=],"""]M,w,-; T=]M
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
 * Multi-sphere support: up to 4 glow spheres
 */

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

/* Single sphere: returns RGB glow contribution */
static inline float3 _GlowSphereShaderSingle(__global const sGlowSphereCl *sphere, int frameNo, float3 point)
{
	if (sphere->enabled == 0) return (float3)(0.0f, 0.0f, 0.0f);

	float dist = GlowSphereDistance(point, sphere->position.xyz, sphere->radius);
	if (dist >= sphere->falloffRadius) return (float3)(0.0f, 0.0f, 0.0f);

	float falloff = GlowSphereFalloff(dist, sphere->falloffRadius);

	// Color gradient: innerColor at surface → outerColor at falloff edge
	float t = clamp(dist / sphere->falloffRadius, 0.0f, 1.0f);
	float3 color = mix(sphere->color.xyz, sphere->outerColor.xyz, t);

	// Pulse animation
	float pulse = 1.0f;
	if (sphere->pulseSpeed > 0.0f || sphere->pulseAmount > 0.0f)
	{
		float angle = (float)frameNo * sphere->pulseSpeed;
		pulse = 1.0f + sphere->pulseAmount * sin(angle);
	}

	float weight = sphere->intensity * falloff * pulse;

	float3 result = color * weight;
	return clamp(result, 0.0f, 1e6f);
}

/* Multi-sphere: returns summed RGB glow contribution */
float3 GlowSphereShaderGPU(__constant sClInConstants *consts, float3 point)
{
	int frameNo = consts->params.frameNo;
	float3 result = (float3)(0.0f, 0.0f, 0.0f);
	result += _GlowSphereShaderSingle(&consts->params.glowSphere1, frameNo, point);
	result += _GlowSphereShaderSingle(&consts->params.glowSphere2, frameNo, point);
	result += _GlowSphereShaderSingle(&consts->params.glowSphere3, frameNo, point);
	result += _GlowSphereShaderSingle(&consts->params.glowSphere4, frameNo, point);
	return result;
}

/* Single sphere: returns RGB diffuse lighting at a surface point */
static inline float3 _GlowSphereSurfaceLightSingle(__global const sGlowSphereCl *sphere, int frameNo,
	float3 surfacePoint, float3 normal, float shading)
{
	if (sphere->enabled == 0) return (float3)(0.0f);

	float3 toSphere = sphere->position.xyz - surfacePoint;
	float dist = length(toSphere);
	if (dist < 1e-20f) return (float3)(0.0f);

	float3 lightDir = toSphere / dist;
	float diffuse = dot(normal, lightDir);
	if (diffuse < 0.0f) diffuse = 0.0f;
	diffuse = 1.0f - shading + diffuse * shading;

	float3 glowColor = _GlowSphereShaderSingle(sphere, frameNo, surfacePoint);
	return glowColor * diffuse;
}

/* Multi-sphere: returns summed RGB diffuse lighting */
float3 GlowSphereSurfaceLightGPU(__constant sClInConstants *consts, float3 surfacePoint, float3 normal,
	float shading)
{
	int frameNo = consts->params.frameNo;
	float3 result = (float3)(0.0f, 0.0f, 0.0f);
	result += _GlowSphereSurfaceLightSingle(&consts->params.glowSphere1, frameNo, surfacePoint, normal, shading);
	result += _GlowSphereSurfaceLightSingle(&consts->params.glowSphere2, frameNo, surfacePoint, normal, shading);
	result += _GlowSphereSurfaceLightSingle(&consts->params.glowSphere3, frameNo, surfacePoint, normal, shading);
	result += _GlowSphereSurfaceLightSingle(&consts->params.glowSphere4, frameNo, surfacePoint, normal, shading);
	return result;
}

/* Single sphere: returns distance to sphere surface */
static inline float _GlowSphereDistanceSingle(__global const sGlowSphereCl *sphere, float3 point)
{
	if (sphere->enabled == 0) return 1e30f;
	return GlowSphereDistance(point, sphere->position.xyz, sphere->radius);
}

/* Multi-sphere: returns minimum distance to any enabled sphere */
float GlowSphereDistanceGPU(__constant sClInConstants *consts, float3 point)
{
	float d1 = _GlowSphereDistanceSingle(&consts->params.glowSphere1, point);
	float d2 = _GlowSphereDistanceSingle(&consts->params.glowSphere2, point);
	float d3 = _GlowSphereDistanceSingle(&consts->params.glowSphere3, point);
	float d4 = _GlowSphereDistanceSingle(&consts->params.glowSphere4, point);
	return min(min(min(d1, d2), d3), d4);
}

/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2014-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * Glow Sphere - simple placeable light source (visible sphere that emits light)
 */

#ifndef MANDELBULBER2_SRC_GLOW_SPHERE_HPP_
#define MANDELBULBER2_SRC_GLOW_SPHERE_HPP_

#include <algorithm>

#include "algebra.hpp"
#include "color_structures.hpp"

struct sGlowSphere
{
	bool enabled;
	CVector3 position;
	CVector3 rotation;  // currently unused, reserved for future
	double radius;
	sRGB color;         // emission color at sphere surface (0-65535 per channel)
	sRGB outerColor;    // emission color at falloff edge (0-65535 per channel)
	double intensity;   // brightness multiplier
	double falloffRadius; // light falloff distance (was hardcoded 5.0)
	double pulseSpeed;  // pulsation speed (rad/frame, 0 = no pulse)
	double pulseAmount; // pulsation strength (0-1, 0 = no pulse)

	sGlowSphere()
		: enabled(false)
		, position(2.0, 0.0, 0.0)
		, rotation(0.0, 0.0, 0.0)
		, radius(0.5)
		, color(65535, 65535, 65535)
		, outerColor(65535, 0, 0)
		, intensity(2.0)
		, falloffRadius(5.0)
		, pulseSpeed(0.0)
		, pulseAmount(0.3)
	{
	}
};

namespace glow_sphere
{
// Sphere SDF (CPU version)
inline double GlowSphereDistance(const CVector3 &point, const CVector3 &position, double radius)
{
	return (point - position).Length() - radius;
}

// Hermite smoothstep falloff (CPU version)
inline double GlowSphereFalloff(double distance, double falloff_radius)
{
	if (distance >= falloff_radius) return 0.0;
	if (distance <= 0.0) return 1.0;
	double t = (falloff_radius - distance) / falloff_radius;
	t = std::max(0.0, std::min(1.0, t));
	return t * t * (3.0 - 2.0 * t);
}

// Surface light — returns RGB diffuse lighting from glow sphere at a surface point
// Forward declaration
inline sRGBFloat GlowSphereShader(const CVector3 &point, const sGlowSphere &sphere, double frameNo);

inline sRGBFloat GlowSphereSurfaceLight(const CVector3 &surfacePoint, const CVector3 &normal,
	float shading, const sGlowSphere &sphere, double frameNo)
{
	if (!sphere.enabled) return sRGBFloat(0.0f, 0.0f, 0.0f);

	CVector3 toSphere = sphere.position - surfacePoint;
	double dist = toSphere.Length();
	if (dist < 1e-20) return sRGBFloat(0.0f, 0.0f, 0.0f);

	CVector3 lightDir = toSphere / dist;
	double diffuse = normal.Dot(lightDir);
	if (diffuse < 0.0) diffuse = 0.0;
	diffuse = 1.0 - shading + diffuse * shading;

	sRGBFloat glowColor = GlowSphereShader(surfacePoint, sphere, frameNo);

	return sRGBFloat(
		glowColor.R * float(diffuse),
		glowColor.G * float(diffuse),
		glowColor.B * float(diffuse));
}

// Light shader — returns RGB glow contribution (CPU version)
inline sRGBFloat GlowSphereShader(
	const CVector3 &point, const sGlowSphere &sphere, double frameNo = 0.0)
{
	if (!sphere.enabled) return sRGBFloat(0.0f, 0.0f, 0.0f);

	double dist = GlowSphereDistance(point, sphere.position, sphere.radius);
	if (dist >= sphere.falloffRadius) return sRGBFloat(0.0f, 0.0f, 0.0f);

	double falloff = GlowSphereFalloff(dist, sphere.falloffRadius);

	// Color gradient: innerColor at surface → outerColor at falloff edge
	double t = dist / sphere.falloffRadius;
	if (t < 0.0) t = 0.0;
	if (t > 1.0) t = 1.0;

	sRGBFloat innerC(
		sphere.color.R / 65535.0f,
		sphere.color.G / 65535.0f,
		sphere.color.B / 65535.0f);
	sRGBFloat outerC(
		sphere.outerColor.R / 65535.0f,
		sphere.outerColor.G / 65535.0f,
		sphere.outerColor.B / 65535.0f);

	sRGBFloat color(
		innerC.R * (1.0f - t) + outerC.R * t,
		innerC.G * (1.0f - t) + outerC.G * t,
		innerC.B * (1.0f - t) + outerC.B * t);

	// Pulse animation
	double pulse = 1.0;
	if (sphere.pulseSpeed > 0.0 || sphere.pulseAmount > 0.0)
	{
		double angle = frameNo * sphere.pulseSpeed;
		pulse = 1.0 + sphere.pulseAmount * sin(angle);
	}

	double weight = sphere.intensity * falloff * pulse;

	sRGBFloat result(color.R * weight, color.G * weight, color.B * weight);

	// Clamp to prevent extreme values / NaN propagation
	result.R = std::min(result.R, 1e6f);
	result.G = std::min(result.G, 1e6f);
	result.B = std::min(result.B, 1e6f);

	return result;
}

// Multi-sphere helpers: accumulate contributions from up to 4 spheres
// Used by CPU shaders to avoid duplicating iteration logic in every caller
inline sRGBFloat GlowSphereShaderMulti(const CVector3 &point, double frameNo,
	const sGlowSphere *s1, const sGlowSphere *s2, const sGlowSphere *s3, const sGlowSphere *s4)
{
	sRGBFloat result(0.0f, 0.0f, 0.0f);
	if (s1 && s1->enabled)
	{
		sRGBFloat c = GlowSphereShader(point, *s1, frameNo);
		result.R += c.R; result.G += c.G; result.B += c.B;
	}
	if (s2 && s2->enabled)
	{
		sRGBFloat c = GlowSphereShader(point, *s2, frameNo);
		result.R += c.R; result.G += c.G; result.B += c.B;
	}
	if (s3 && s3->enabled)
	{
		sRGBFloat c = GlowSphereShader(point, *s3, frameNo);
		result.R += c.R; result.G += c.G; result.B += c.B;
	}
	if (s4 && s4->enabled)
	{
		sRGBFloat c = GlowSphereShader(point, *s4, frameNo);
		result.R += c.R; result.G += c.G; result.B += c.B;
	}
	result.R = std::min(result.R, 1e6f);
	result.G = std::min(result.G, 1e6f);
	result.B = std::min(result.B, 1e6f);
	return result;
}

inline sRGBFloat GlowSphereSurfaceLightMulti(const CVector3 &surfacePoint, const CVector3 &normal,
	float shading, double frameNo,
	const sGlowSphere *s1, const sGlowSphere *s2, const sGlowSphere *s3, const sGlowSphere *s4)
{
	sRGBFloat result(0.0f, 0.0f, 0.0f);
	if (s1 && s1->enabled)
	{
		sRGBFloat c = GlowSphereSurfaceLight(surfacePoint, normal, shading, *s1, frameNo);
		result.R += c.R; result.G += c.G; result.B += c.B;
	}
	if (s2 && s2->enabled)
	{
		sRGBFloat c = GlowSphereSurfaceLight(surfacePoint, normal, shading, *s2, frameNo);
		result.R += c.R; result.G += c.G; result.B += c.B;
	}
	if (s3 && s3->enabled)
	{
		sRGBFloat c = GlowSphereSurfaceLight(surfacePoint, normal, shading, *s3, frameNo);
		result.R += c.R; result.G += c.G; result.B += c.B;
	}
	if (s4 && s4->enabled)
	{
		sRGBFloat c = GlowSphereSurfaceLight(surfacePoint, normal, shading, *s4, frameNo);
		result.R += c.R; result.G += c.G; result.B += c.B;
	}
	return result;
}

inline double GlowSphereDistanceMulti(const CVector3 &point,
	const sGlowSphere *s1, const sGlowSphere *s2, const sGlowSphere *s3, const sGlowSphere *s4)
{
	double d1 = (s1 && s1->enabled) ? GlowSphereDistance(point, s1->position, s1->radius) : 1e30;
	double d2 = (s2 && s2->enabled) ? GlowSphereDistance(point, s2->position, s2->radius) : 1e30;
	double d3 = (s3 && s3->enabled) ? GlowSphereDistance(point, s3->position, s3->radius) : 1e30;
	double d4 = (s4 && s4->enabled) ? GlowSphereDistance(point, s4->position, s4->radius) : 1e30;
	return std::min(std::min(std::min(d1, d2), d3), d4);
}

} // namespace glow_sphere

#endif /* MANDELBULBER2_SRC_GLOW_SPHERE_HPP_ */

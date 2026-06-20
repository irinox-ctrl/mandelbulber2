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
 * Single Trap Light v1 - CPU evaluation
 */

#include "single_trap_light_shader.hpp"

#include <algorithm>
#include <cmath>

/* Hardcoded falloff radius for v1 (later will be parameter) */
static const double kFalloffRadius = 5.0;

double SingleTrapLightDistance(const CVector3 &point, const sSingleTrapLight &light)
{
	/* Build rotation matrix from Euler angles in degrees */
	CRotationMatrix rot;
	rot.SetRotation2(light.rotation * (M_PI / 180.0));

	/* Local capsule lies along local Y-axis */
	CVector3 halfLocal(0.0, light.size * 0.5, 0.0);
	CVector3 halfWorld = rot.RotateVector(halfLocal);

	CVector3 a = light.center - halfWorld;
	CVector3 b = light.center + halfWorld;

	/* Standard capsule SDF */
	CVector3 pa = point - a;
	CVector3 ba = b - a;
	double denom = ba.Dot(ba);
	if (denom < 1e-30)
	{
		/* Degenerate: size ≈ 0 → sphere at center */
		return (point - light.center).Length() - light.radius;
	}
	double h = pa.Dot(ba) / denom;
	if (h < 0.0) h = 0.0;
	if (h > 1.0) h = 1.0;
	CVector3 closest = ba * h;
	return (pa - closest).Length() - light.radius;
}

double SingleTrapLightFalloff(double distance, double falloffRadius)
{
	if (distance >= falloffRadius) return 0.0;
	if (distance <= 0.0) return 1.0;
	double t = (falloffRadius - distance) / falloffRadius;
	if (t < 0.0) t = 0.0;
	if (t > 1.0) t = 1.0;
	return t * t * (3.0 - 2.0 * t); /* Hermite smooth */
}

sRGBFloat SingleTrapLightEvaluate(const CVector3 &point, const sSingleTrapLight &light)
{
	if (!light.enabled) return sRGBFloat(0.0f, 0.0f, 0.0f);

	double dist = SingleTrapLightDistance(point, light);
	if (dist >= kFalloffRadius) return sRGBFloat(0.0f, 0.0f, 0.0f);

	double falloff = SingleTrapLightFalloff(dist, kFalloffRadius);
	double weight = light.intensity * falloff;

	/* sRGB (0..65535) → float (0..1) then multiply */
	sRGBFloat out;
	out.R = float(light.color.R / 65535.0 * weight);
	out.G = float(light.color.G / 65535.0 * weight);
	out.B = float(light.color.B / 65535.0 * weight);
	return out;
}

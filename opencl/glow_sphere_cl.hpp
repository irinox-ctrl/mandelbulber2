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
 * Glow Sphere - OpenCL struct definition
 */

#ifndef MANDELBULBER2_OPENCL_GLOW_SPHERE_CL_HPP_
#define MANDELBULBER2_OPENCL_GLOW_SPHERE_CL_HPP_

#ifndef OPENCL_KERNEL_CODE
#include "src/glow_sphere.hpp"
#endif /* OPENCL_KERNEL_CODE */

typedef struct
{
	cl_float4 position;     // float4 for predictable alignment
	cl_float4 rotation;     // currently unused but reserved
	cl_float4 color;        // inner color at sphere surface, normalized RGB (0.0-1.0)
	cl_float4 outerColor;   // outer color at falloff edge, normalized RGB (0.0-1.0)
	cl_float radius;
	cl_float intensity;
	cl_float falloffRadius; // light falloff distance
	cl_float pulseSpeed;    // pulsation speed (rad/frame, 0 = no pulse)
	cl_float pulseAmount;   // pulsation strength (0-1, 0 = no pulse)
	cl_int enabled;
	cl_int _pad[2];         // explicit padding to align struct to 16 bytes
} sGlowSphereCl;

#ifndef OPENCL_KERNEL_CODE
inline sGlowSphereCl clCopySGlowSphere(const sGlowSphere &source)
{
	sGlowSphereCl target;
	target.enabled = source.enabled ? 1 : 0;
	target.position = toClFloat3(source.position);
	target.rotation = toClFloat3(source.rotation);
	target.radius = static_cast<cl_float>(source.radius);
	target.color = toClFloat3(sRGBFloat(source.color.R / 65535.0f, source.color.G / 65535.0f, source.color.B / 65535.0f));
	target.outerColor = toClFloat3(sRGBFloat(source.outerColor.R / 65535.0f, source.outerColor.G / 65535.0f, source.outerColor.B / 65535.0f));
	target.intensity = static_cast<cl_float>(source.intensity);
	target.falloffRadius = static_cast<cl_float>(source.falloffRadius);
	target.pulseSpeed = static_cast<cl_float>(source.pulseSpeed);
	target.pulseAmount = static_cast<cl_float>(source.pulseAmount);
	return target;
}
#endif

#endif /* MANDELBULBER2_OPENCL_GLOW_SPHERE_CL_HPP_ */

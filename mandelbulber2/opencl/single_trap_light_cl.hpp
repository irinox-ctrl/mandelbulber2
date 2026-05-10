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
 * Single Trap Light v1 - OpenCL struct (separate from fake_lights System 1)
 */

#ifndef MANDELBULBER2_OPENCL_SINGLE_TRAP_LIGHT_CL_HPP_
#define MANDELBULBER2_OPENCL_SINGLE_TRAP_LIGHT_CL_HPP_

#ifndef OPENCL_KERNEL_CODE
#include "opencl_algebra.h"
#include "src/single_trap_light.hpp"
#endif /* OPENCL_KERNEL_CODE */

typedef struct
{
	cl_float3 center;      // offset 0,  size 16
	cl_float3 rotation;    // offset 16, size 16
	cl_float3 color;       // offset 32, size 16 (sRGB → float3, /65535.0)
	cl_float size;         // offset 48, size 4
	cl_float radius;       // offset 52, size 4
	cl_float intensity;    // offset 56, size 4
	cl_int enabled;        // offset 60, size 4
	cl_int dummy0;         // offset 64, size 4  (padding to 80)
	cl_int dummy1;         // offset 68, size 4
	cl_int dummy2;         // offset 72, size 4
	cl_int dummy3;         // offset 76, size 4
} sClSingleTrapLight;      // total: 80 bytes (5×16)

#ifndef OPENCL_KERNEL_CODE
inline sClSingleTrapLight clCopySSingleTrapLight(const sSingleTrapLight &source)
{
	sClSingleTrapLight target;
	target.enabled = source.enabled ? 1 : 0;
	target.center = toClFloat3(source.center);
	target.rotation = toClFloat3(source.rotation);
	target.color = {{cl_float(source.color.R / 65535.0), cl_float(source.color.G / 65535.0),
		cl_float(source.color.B / 65535.0), cl_float(0.0)}};
	target.size = cl_float(source.size);
	target.radius = cl_float(source.radius);
	target.intensity = cl_float(source.intensity);
	target.dummy0 = 0;
	target.dummy1 = 0;
	target.dummy2 = 0;
	target.dummy3 = 0;
	return target;
}
#endif /* OPENCL_KERNEL_CODE */

#endif /* MANDELBULBER2_OPENCL_SINGLE_TRAP_LIGHT_CL_HPP_ */

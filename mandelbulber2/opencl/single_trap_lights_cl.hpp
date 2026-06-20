/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2014-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
 *                                        ,=mm=§M ]=4 yJKA"/-Nsaj  "Bw,==,,
 * This file is part of Mandelbulber.    §R.r= jw",M  Km .mM  FW ",§=ß., ,TN
 *                                     ,4R =%["w[N=7]J '"5=],","]]M,w,-; T=]M
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
 * Single Trap Lights — OpenCL struct definition
 */

#ifndef MANDELBULBER2_OPENCL_SINGLE_TRAP_LIGHTS_CL_HPP_
#define MANDELBULBER2_OPENCL_SINGLE_TRAP_LIGHTS_CL_HPP_

#ifndef OPENCL_KERNEL_CODE
#include "opencl_algebra.h"
#include "src/single_trap_lights.hpp"
#endif

typedef struct
{
	cl_int enabled;
	cl_int shape;
	cl_int preTransformed;
	cl_int positionMode;
	cl_float4 position;
	cl_float4 rotation;
	cl_float4 color;
	cl_float4 gradientColor;
	matrix33 mRotRotation;
	cl_float size;
	cl_float size2;
	cl_float thickness;
	cl_float intensity;
	cl_float visibility;
	cl_float maxDistance;
	cl_float sharpening;
	cl_float blur;
	cl_float solidIntensity;
	cl_float softness;
	cl_float relativeSize;
	cl_int coloringMode;
	cl_int falloffType;
	cl_float edgeSoftness;
	cl_float animOrbitRadius;
	cl_float animOrbitSpeed;
	cl_float animPulsateSpeed;
	cl_float animPulsateAmount;
	cl_int _pad[2];
} sSingleTrapLightLayerCl;

typedef struct
{
	cl_int enabled;
	cl_int activeLayerCount;
	cl_int soloLayerIndex;
	cl_int combineMode;
	sSingleTrapLightLayerCl layers[20];
} sSingleTrapLightsCl;

#ifndef OPENCL_KERNEL_CODE
inline sSingleTrapLightLayerCl clCopySSingleTrapLightLayerCl(const sSingleTrapLightLayer &source)
{
	sSingleTrapLightLayerCl target;
	target.enabled = source.enabled ? 1 : 0;
	target.shape = source.shape;
	target.preTransformed = source.preTransformed ? 1 : 0;
	target.positionMode = source.positionMode;
	target.position = toClFloat3(source.position);
	target.rotation = toClFloat3(source.rotation);
	target.color = toClFloat3(source.color);
	target.gradientColor = toClFloat3(source.gradientColor);
	target.mRotRotation = toClMatrix33(source.mRotRotation);
	target.size = cl_float(source.size);
	target.size2 = cl_float(source.size2);
	target.thickness = cl_float(source.thickness);
	target.intensity = cl_float(source.intensity);
	target.visibility = cl_float(source.visibility);
	target.maxDistance = cl_float(source.maxDistance);
	target.sharpening = cl_float(source.sharpening);
	target.blur = cl_float(source.blur);
	target.solidIntensity = cl_float(source.solidIntensity);
	target.softness = cl_float(source.softness);
	target.relativeSize = cl_float(source.relativeSize);
	target.coloringMode = source.coloringMode;
	target.falloffType = source.falloffType;
	target.edgeSoftness = cl_float(source.edgeSoftness);
	target.animOrbitRadius = cl_float(source.animOrbitRadius);
	target.animOrbitSpeed = cl_float(source.animOrbitSpeed);
	target.animPulsateSpeed = cl_float(source.animPulsateSpeed);
	target.animPulsateAmount = cl_float(source.animPulsateAmount);
	target._pad[0] = 0;
	target._pad[1] = 0;
	return target;
}
#endif

#endif /* MANDELBULBER2_OPENCL_SINGLE_TRAP_LIGHTS_CL_HPP_ */

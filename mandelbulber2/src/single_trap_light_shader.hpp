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
 * Separate light system (apart from fake_lights System 1)
 *
 * Pure function: given sample-point + light-struct → RGB contribution.
 * No shader integration here (that is Prompt D).
 */

#ifndef MANDELBULBER2_SRC_SINGLE_TRAP_LIGHT_SHADER_HPP_
#define MANDELBULBER2_SRC_SINGLE_TRAP_LIGHT_SHADER_HPP_

#include "algebra.hpp"
#include "color_structures.hpp"
#include "single_trap_light.hpp"

/* Signed distance from point to capsule (center + rotation + size + radius).
 * Returns distance in world-space units. Negative = inside the tube.
 */
double SingleTrapLightDistance(const CVector3 &point, const sSingleTrapLight &light);

/* Smooth Hermite falloff. Returns 0..1.
 * At distance = 0 → 1.0
 * At distance >= falloffRadius → 0.0
 */
double SingleTrapLightFalloff(double distance, double falloffRadius);

/* Evaluate full light contribution for a given point.
 * Returns RGB additive contribution (0..∞ per channel).
 * If light disabled, returns (0, 0, 0).
 */
sRGBFloat SingleTrapLightEvaluate(const CVector3 &point, const sSingleTrapLight &light);

#endif /* MANDELBULBER2_SRC_SINGLE_TRAP_LIGHT_SHADER_HPP_ */

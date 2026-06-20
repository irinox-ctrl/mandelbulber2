/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2022 Mandelbulber Team        §R-==%w["'~5]m%=L.=~5N
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
 * but WITHOUT ANY WARRANTY;                            . '''
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
 * cRenderWorker::DistanceFogOpacity method - calculates opacity for distance fog effect
 */

#include <cmath>

#include "algebra.hpp"
#include "fractparams.hpp"
#include "render_worker.hpp"

namespace
{
double FinishDistFogOpacity(const double densityTemp, const double volFogDensity)
{
	double distFogOpacity =
		0.3 * volFogDensity * densityTemp / (1.0 + volFogDensity * densityTemp) - 0.001;
	if (distFogOpacity < 0.0) distFogOpacity = 0.0;
	return distFogOpacity;
}
} // namespace

double cRenderWorker::DistanceFogOpacity(const double step, double distance,
	double volFogDistanceFromSurface, double volFogDistanceFactor, double volFogDensity,
	double depthAlongRay, const CVector3 &point, double &distanceShifted) const
{
	const int mode = params->volFogMode;
	const double factor = std::max(volFogDistanceFactor, 1e-9);
	const double offset = volFogDistanceFromSurface;
	double densityTemp = 0.0;

	switch (mode)
	{
		case 1: // exponential depth fog
			distanceShifted = std::max(depthAlongRay - offset, 0.0);
			densityTemp = step * volFogDensity * std::exp(-distanceShifted / factor);
			break;
		case 2: // height fog
			distanceShifted = std::max(point.y - offset, 0.0);
			densityTemp = step * volFogDistanceFactor * std::exp(-distanceShifted / factor);
			break;
		case 3: // distance from camera
		{
			const CVector3 toPoint = point - params->camera;
			distanceShifted = toPoint.Length();
			densityTemp = step * volFogDistanceFactor * distanceShifted
										/ (distanceShifted * distanceShifted + factor * factor);
			break;
		}
		case 4: // hybrid surface shell + depth
		{
			const double shellShifted = fabs(distance - offset) + 0.1 * offset;
			const double shellDensity = step * volFogDistanceFactor
																	/ (shellShifted * shellShifted + factor * factor);
			const double depthShifted = std::max(depthAlongRay - offset, 0.0);
			const double depthDensity = step * volFogDensity * std::exp(-depthShifted / factor);
			distanceShifted = 0.5 * shellShifted + 0.5 * depthShifted;
			densityTemp = 0.5 * shellDensity + 0.5 * depthDensity;
			break;
		}
		default: // surface shell (Lorentzian)
			distanceShifted = fabs(distance - offset) + 0.1 * offset;
			densityTemp = step * volFogDistanceFactor
										/ (distanceShifted * distanceShifted + factor * factor);
			break;
	}

	return FinishDistFogOpacity(densityTemp, volFogDensity);
}

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
 * calculates opacity for distance fog effect
 */

#ifdef VOLUMETRIC_FOG

float FinishDistFogOpacity(float densityTemp, float volFogDensity)
{
	float distFogOpacity =
		0.3f * volFogDensity * densityTemp / (1.0f + volFogDensity * densityTemp) - 0.001f;
	return clamp(distFogOpacity, 0.0f, 1.0f);
}

float DistanceFogOpacity(float step, float distance, float volFogDistanceFromSurface,
	float volFogDistanceFactor, float volFogDensity, int volFogMode, float depthAlongRay,
	float3 point, float3 camera, float *distanceShifted)
{
	const float factor = max(volFogDistanceFactor, 1e-9f);
	const float offset = volFogDistanceFromSurface;
	float densityTemp = 0.0f;

	switch (volFogMode)
	{
		case 1: // exponential depth fog
			*distanceShifted = max(depthAlongRay - offset, 0.0f);
			densityTemp = step * volFogDensity * exp(-(*distanceShifted) / factor);
			break;
		case 2: // height fog
			*distanceShifted = max(point.y - offset, 0.0f);
			densityTemp = step * volFogDistanceFactor * exp(-(*distanceShifted) / factor);
			break;
		case 3: // distance from camera
		{
			float3 toPoint = point - camera;
			*distanceShifted = fast_length(toPoint);
			densityTemp = step * volFogDistanceFactor * (*distanceShifted)
										/ ((*distanceShifted) * (*distanceShifted) + factor * factor);
			break;
		}
		case 4: // hybrid surface shell + depth
		{
			float shellShifted = fabs(distance - offset) + 0.1f * offset;
			float shellDensity = step * volFogDistanceFactor
													 / (shellShifted * shellShifted + factor * factor);
			float depthShifted = max(depthAlongRay - offset, 0.0f);
			float depthDensity = step * volFogDensity * exp(-depthShifted / factor);
			*distanceShifted = 0.5f * shellShifted + 0.5f * depthShifted;
			densityTemp = 0.5f * shellDensity + 0.5f * depthDensity;
			break;
		}
		default: // surface shell (Lorentzian)
			*distanceShifted = fabs(distance - offset) + 0.1f * offset;
			densityTemp = step * volFogDistanceFactor
										/ ((*distanceShifted) * (*distanceShifted) + factor * factor);
			break;
	}

	return FinishDistFogOpacity(densityTemp, volFogDensity);
}
#endif // VOLUMETRIC_FOG

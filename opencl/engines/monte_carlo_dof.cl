/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2017-18 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * Fast opencl implementation for rendering dof effect with monte carlo approach
 */

#ifdef MONTE_CARLO_DOF

inline float2 HexagonalApertureSample(int *randomSeed)
{
	float u = (Random(1000, randomSeed) / 1000.0f) * 2.0f - 1.0f;
	float v = (Random(1000, randomSeed) / 1000.0f) * 2.0f - 1.0f;

	if (fabs(v) > 0.866f)
	{
		u *= 0.5f;
		v = sign(v) * 0.866f;
	}
	if (fabs(u) > 1.0f - fabs(v) * 0.577350269f)
	{
		float tmp = u;
		u = (u + v * 1.154700538f) * 0.5f;
		v = (v - tmp * 0.866025404f) * 0.5f;
	}
	return (float2){u, v};
}

inline void MonteCarloDOF(float3 *startRay, float3 *viewVector, __constant sClInConstants *consts,
	matrix33 mRot, int *randomSeed)
{
#ifdef PERSP_THREE_POINT
	float randR = 0.0015f * consts->params.DOFRadius * consts->params.DOFFocus;
	float2 hex = HexagonalApertureSample(randomSeed);
	float3 randVector = (float3){randR * hex.x, 0.0f, randR * hex.y};
	float3 randVectorRot = Matrix33MulFloat3(mRot, randVector);
	float3 viewVectorTemp = *viewVector;
	viewVectorTemp -= randVectorRot / consts->params.DOFFocus;
	*viewVector = viewVectorTemp;
	*startRay = consts->params.camera + randVectorRot;
#else
	float3 viewVectorTemp = *viewVector;
	float randR = 0.0015f * consts->params.DOFRadius * consts->params.DOFFocus;
	float2 hex = HexagonalApertureSample(randomSeed);
	float3 randVector = (float3){randR * hex.x, 0.0f, randR * hex.y};

	float3 side = cross(viewVectorTemp, consts->params.topVector);
	side = normalize(side);
	float3 topTemp = cross(side, viewVectorTemp);
	topTemp = normalize(topTemp);
	float3 randVectorRot = side * randVector.x + topTemp * randVector.z;

	viewVectorTemp -= randVectorRot / consts->params.DOFFocus;
	*viewVector = viewVectorTemp;
	*startRay = consts->params.camera + randVectorRot;
#endif
}

#endif

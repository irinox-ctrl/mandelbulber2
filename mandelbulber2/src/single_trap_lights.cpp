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
 * Single Trap Lights — SDF core functions
 */

#include "single_trap_lights.hpp"
#include <algorithm>

double SingleTrapLightDistance(CVector3 point, const sSingleTrapLightLayer &layer)
{
	CVector3 delta = point - layer.position;
	delta = layer.mRotRotation.RotateVector(delta);

	double dist = 0.0;
	switch (layer.shape)
	{
		case params::singleTrapLightShapePoint:
		{
			dist = delta.Length() - layer.size;
			break;
		}
		case params::singleTrapLightShapeLine:
		{
			dist = sqrt(delta.y * delta.y + delta.z * delta.z) - layer.size;
			break;
		}
		case params::singleTrapLightShapeCircle:
		{
			double lengthYZ = sqrt(delta.y * delta.y + delta.z * delta.z) - layer.size;
			dist = sqrt(lengthYZ * lengthYZ + delta.x * delta.x);
			break;
		}
		case params::singleTrapLightShapeSquare:
		{
			double dy = std::max(fabs(fabs(delta.y) - layer.size), fabs(delta.z) - layer.size);
			double dz = std::max(fabs(fabs(delta.z) - layer.size), fabs(delta.y) - layer.size);
			double deltaRect = std::min(dy, dz);
			dist = sqrt(deltaRect * deltaRect + delta.x * delta.x);
			break;
		}
		case params::singleTrapLightShapeSphere:
		{
			dist = delta.Length() - layer.size;
			break;
		}
		case params::singleTrapLightShapeCube:
		{
			double size = layer.size;
			double dy_x = std::max(fabs(fabs(delta.y) - size), fabs(delta.z) - size);
			double dz_x = std::max(fabs(fabs(delta.z) - size), fabs(delta.y) - size);
			double dx_z = std::max(fabs(fabs(delta.y) - size), fabs(delta.x) - size);
			double deltaRectYZ = std::min(dy_x, dz_x);
			double distYZ = sqrt(deltaRectYZ * deltaRectYZ + fabs(fabs(delta.x) - size) * fabs(fabs(delta.x) - size));
			double distXZ = sqrt(dx_z * dx_z + fabs(fabs(delta.z) - size) * fabs(fabs(delta.z) - size));
			dist = std::min(distYZ, distXZ);
			break;
		}
		case params::singleTrapLightShapeTorus:
		{
			double q = sqrt(delta.y * delta.y + delta.z * delta.z) - layer.size;
			dist = sqrt(q * q + delta.x * delta.x) - layer.size2;
			break;
		}
		case params::singleTrapLightShapeCapsule:
		{
			CVector3 a(0.0, -layer.size, 0.0);
			CVector3 b(0.0, layer.size, 0.0);
			CVector3 pa = delta - a;
			CVector3 ba = b - a;
			double h = std::max(0.0, std::min(1.0, pa.Dot(ba) / ba.Dot(ba)));
			dist = (pa - ba * h).Length() - layer.size2;
			break;
		}
		case params::singleTrapLightShapeRing:
		{
			double l = sqrt(delta.y * delta.y + delta.z * delta.z);
			dist = fabs(l - layer.size) - layer.size2;
			break;
		}
		case params::singleTrapLightShapeEllipse:
		{
			double k = sqrt((delta.y * delta.y) / (layer.size * layer.size) + (delta.z * delta.z) / (layer.size2 * layer.size2));
			if (k < 1e-10) k = 1e-10;
			dist = sqrt(delta.y * delta.y + delta.z * delta.z) / k - layer.size;
			break;
		}
		case params::singleTrapLightShapeCross:
		{
			double sx = layer.size;
			double sy = layer.size2;
			double sz = layer.size2;
			double d1 = sqrt(delta.y * delta.y + delta.z * delta.z) - sy;
			d1 = sqrt(d1 * d1 + delta.x * delta.x) - sx;
			double d2 = sqrt(delta.x * delta.x + delta.z * delta.z) - sz;
			d2 = sqrt(d2 * d2 + delta.y * delta.y) - sy;
			double d3 = sqrt(delta.x * delta.x + delta.y * delta.y) - sx;
			d3 = sqrt(d3 * d3 + delta.z * delta.z) - sz;
			dist = std::min(std::min(d1, d2), d3);
			break;
		}
		case params::singleTrapLightShapeCylinder:
		{
			double d1 = sqrt(delta.y * delta.y + delta.z * delta.z) - layer.size;
			double d2 = fabs(delta.x) - layer.size2;
			double dx = std::max(d1, 0.0);
			double dy = std::max(d2, 0.0);
			dist = sqrt(dx * dx + dy * dy) + std::min(std::max(d1, d2), 0.0);
			break;
		}
		case params::singleTrapLightShapePlane:
		{
			dist = fabs(delta.x) - layer.size;
			break;
		}
		case params::singleTrapLightShapeDisc:
		{
			double l = sqrt(delta.y * delta.y + delta.z * delta.z);
			double d1 = l - layer.size;
			double d2 = fabs(delta.x) - layer.size2;
			double dx = std::max(d1, 0.0);
			double dy = std::max(d2, 0.0);
			dist = sqrt(dx * dx + dy * dy) + std::min(std::max(d1, d2), 0.0);
			break;
		}
	}
	if (layer.edgeSoftness > 0.0)
	{
		const double es = layer.edgeSoftness * 2.5;
		dist = sqrt(dist * dist + es * es) - es;
	}
	return dist / layer.thickness;
}

CVector3 SingleTrapLightNormal(CVector3 point, const sSingleTrapLightLayer &layer, double delta)
{
	double rC = 1.0 / (SingleTrapLightDistance(point, layer) + 1e-30);
	double rx = 1.0 / (SingleTrapLightDistance(point + CVector3(delta, 0.0, 0.0), layer) + 1e-30);
	double ry = 1.0 / (SingleTrapLightDistance(point + CVector3(0.0, delta, 0.0), layer) + 1e-30);
	double rz = 1.0 / (SingleTrapLightDistance(point + CVector3(0.0, 0.0, delta), layer) + 1e-30);
	CVector3 normal(rC - rx, rC - ry, rC - rz);
	normal.Normalize();
	return normal;
}

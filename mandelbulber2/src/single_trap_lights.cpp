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
		case params::singleTrapLightShapeCone:
		{
			// Cone: apex at (-size2, 0, 0), base at (size2, 0, 0) with radius size
			double qx = sqrt(delta.y * delta.y + delta.z * delta.z);
			double qy = delta.x;
			double tix = 0.0, tiy = -layer.size2;
			double bax = layer.size, bay = layer.size2;
			double cbx = tix - bax, cby = tiy - bay;
			double dotCb = cbx * cbx + cby * cby;
			double dotQCb = (qx - bax) * cbx + (qy - bay) * cby;
			double h = std::max(0.0, std::min(1.0, dotQCb / dotCb));
			double rx = qx - bax - cbx * h;
			double ry = qy - bay - cby * h;
			dist = sqrt(rx * rx + ry * ry);
			break;
		}
		case params::singleTrapLightShapeHexagon:
		{
			// 2D hexagon in YZ, extruded along X
			const double k = sqrt(3.0);
			double pz = fabs(delta.z);
			double py = fabs(delta.y);
			double d2 = std::max(pz * k + py * 0.5, py) - layer.size;
			double dx = fabs(delta.x) - layer.size2;
			double dOut = sqrt(std::max(d2, 0.0) * std::max(d2, 0.0) + std::max(dx, 0.0) * std::max(dx, 0.0));
			double dIn = std::min(std::max(d2, dx), 0.0);
			dist = dOut + dIn;
			break;
		}
		case params::singleTrapLightShapeTriangle:
		{
			// 2D equilateral triangle in YZ, extruded along X
			const double k = sqrt(3.0);
			double pz = fabs(delta.z);
			double py = delta.y;
			double d2 = std::max(pz * k + py, -py + pz * k) * 0.5 - layer.size;
			double dx = fabs(delta.x) - layer.size2;
			double dOut = sqrt(std::max(d2, 0.0) * std::max(d2, 0.0) + std::max(dx, 0.0) * std::max(dx, 0.0));
			double dIn = std::min(std::max(d2, dx), 0.0);
			dist = dOut + dIn;
			break;
		}
		case params::singleTrapLightShapeRoundedBox:
		{
			CVector3 q = CVector3(fabs(delta.x), fabs(delta.y), fabs(delta.z)) - CVector3(layer.size, layer.size, layer.size) + CVector3(layer.size2, layer.size2, layer.size2);
			dist = sqrt(std::max(q.x, 0.0) * std::max(q.x, 0.0) + std::max(q.y, 0.0) * std::max(q.y, 0.0) + std::max(q.z, 0.0) * std::max(q.z, 0.0))
				+ std::min(std::max(q.x, std::max(q.y, q.z)), 0.0) - layer.size2;
			break;
		}
		case params::singleTrapLightShapeDiamond:
		{
			// Octahedron: |x|+|y|+|z| = size
			dist = (fabs(delta.x) + fabs(delta.y) + fabs(delta.z) - layer.size) / sqrt(3.0);
			break;
		}
		case params::singleTrapLightShapeHollowSphere:
		{
			dist = fabs(delta.Length() - layer.size);
			break;
		}
		case params::singleTrapLightShapeHollowCube:
		{
			CVector3 q = CVector3(fabs(delta.x), fabs(delta.y), fabs(delta.z)) - CVector3(layer.size, layer.size, layer.size);
			dist = fabs(sqrt(std::max(q.x, 0.0) * std::max(q.x, 0.0) + std::max(q.y, 0.0) * std::max(q.y, 0.0) + std::max(q.z, 0.0) * std::max(q.z, 0.0))
				+ std::min(std::max(q.x, std::max(q.y, q.z)), 0.0));
			break;
		}
		case params::singleTrapLightShapeEllipsoid:
		{
			// Approximate ellipsoid: size=Y radius, size2=Z radius, X=(size+size2)/2
			CVector3 r = CVector3((layer.size + layer.size2) * 0.5, layer.size, layer.size2);
			CVector3 p = CVector3(delta.x / r.x, delta.y / r.y, delta.z / r.z);
			dist = (p.Length() - 1.0) * std::min(r.x, std::min(r.y, r.z));
			break;
		}
		case params::singleTrapLightShapeSuperellipsoid:
		{
			// Superellipsoid with n=4: size=Y scale, size2=Z scale, X=(size+size2)/2
			CVector3 r = CVector3((layer.size + layer.size2) * 0.5, layer.size, layer.size2);
			double n = 4.0;
			dist = pow(pow(fabs(delta.x / r.x), n) + pow(fabs(delta.y / r.y), n)
							 + pow(fabs(delta.z / r.z), n), 1.0 / n) - 1.0;
			break;
		}
		case params::singleTrapLightShapeStar5:
		{
			// 2D 5-point star in YZ, extruded along X (simple approximation)
			double angle = atan2(delta.z, delta.y);
			double r = sqrt(delta.y * delta.y + delta.z * delta.z);
			double starR = layer.size * (0.5 + 0.5 * cos(5.0 * angle)) * 0.6 + layer.size * 0.2;
			double d2 = r - starR;
			double dx = fabs(delta.x) - layer.size2;
			double dOut = sqrt(std::max(d2, 0.0) * std::max(d2, 0.0) + std::max(dx, 0.0) * std::max(dx, 0.0));
			double dIn = std::min(std::max(d2, dx), 0.0);
			dist = dOut + dIn;
			break;
		}
		case params::singleTrapLightShapeStar6:
		{
			// 2D 6-point star in YZ, extruded along X (simple approximation)
			double angle = atan2(delta.z, delta.y);
			double r = sqrt(delta.y * delta.y + delta.z * delta.z);
			double starR = layer.size * (0.5 + 0.5 * cos(6.0 * angle)) * 0.6 + layer.size * 0.2;
			double d2 = r - starR;
			double dx = fabs(delta.x) - layer.size2;
			double dOut = sqrt(std::max(d2, 0.0) * std::max(d2, 0.0) + std::max(dx, 0.0) * std::max(dx, 0.0));
			double dIn = std::min(std::max(d2, dx), 0.0);
			dist = dOut + dIn;
			break;
		}
		case params::singleTrapLightShapeGear:
		{
			// 2D gear in YZ, extruded along X (simple approximation)
			double angle = atan2(delta.z, delta.y);
			double r = sqrt(delta.y * delta.y + delta.z * delta.z);
			double teeth = 8.0;
			double gearR = layer.size * (0.7 + 0.3 * cos(teeth * angle));
			double d2 = r - gearR;
			double dx = fabs(delta.x) - layer.size2;
			double dOut = sqrt(std::max(d2, 0.0) * std::max(d2, 0.0) + std::max(dx, 0.0) * std::max(dx, 0.0));
			double dIn = std::min(std::max(d2, dx), 0.0);
			dist = dOut + dIn;
			break;
		}
		case params::singleTrapLightShapeHeart:
		{
			// 2D heart in YZ, extruded along X (simple approximation)
			double y = delta.y / layer.size;
			double z = delta.z / layer.size;
			double d2 = pow(y * y + z * z - 1.0, 3.0) - y * y * z * z * z;
			d2 = (d2 > 0.0 ? 1.0 : -1.0) * pow(fabs(d2), 1.0 / 6.0) * layer.size;
			double dx = fabs(delta.x) - layer.size2;
			double dOut = sqrt(std::max(d2, 0.0) * std::max(d2, 0.0) + std::max(dx, 0.0) * std::max(dx, 0.0));
			double dIn = std::min(std::max(d2, dx), 0.0);
			dist = dOut + dIn;
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

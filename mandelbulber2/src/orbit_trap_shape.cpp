/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2019 Mandelbulber Team        §R-==%w["'~5]m%=L.=~5N
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
 * OrbitTrapShapeDistance - Function to calculate distance from different
 * shapes of orbit traps
 */

#include "orbit_trap_shape.hpp"

using std::max;
using std::min;

// Helper for 2D SDF extrusion
static inline double Extrude2D(double d2d, double z)
{
	return sqrt(d2d * d2d + z * z);
}

// Helper: sign
static inline double SdfSign(double x) { return (x > 0.0) ? 1.0 : ((x < 0.0) ? -1.0 : 0.0); }

// Helper: mod for SDF patterns
static inline double SdfMod(double x, double y) { return x - y * floor(x / y); }

// Helper: Koch snowflake iteration (2D, returns distance in XY plane)
static double KochSnowflakeDist(double x, double y, double size)
{
	// Scale to unit
	x /= size;
	y /= size;
	// Rotate to align with snowflake
	for (int i = 0; i < 2; i++) // 2 iterations
	{
		x = fabs(x);
		y = fabs(y);
		// Fold around 60 degrees
		double dot = x * 0.5 + y * 0.86602540378;
		if (dot > y)
		{
			x = dot;
			y = x * 0.86602540378 - y * 0.5;
		}
		else
		{
			x = x;
			y = y;
		}
		x = x * 3.0 - 2.0;
		y = y * 3.0;
		if (x < -1.0) x = -2.0 - x;
	}
	// Distance to the base triangle edge
	return (y - 0.5) * size;
}

// Helper: Menger sponge distance (approximate, 2 iterations)
static double MengerSpongeDist(CVector3 p, double size)
{
	CVector3 s = p / size;
	double d = max(fabs(s.x), max(fabs(s.y), fabs(s.z))) - 1.0;
	for (int i = 0; i < 2; i++)
	{
		s.x = fabs(s.x);
		s.y = fabs(s.y);
		s.z = fabs(s.z);
		if (s.x < s.y) { double t = s.x; s.x = s.y; s.y = t; }
		if (s.x < s.z) { double t = s.x; s.x = s.z; s.z = t; }
		if (s.y < s.z) { double t = s.y; s.y = s.z; s.z = t; }
		s = s * 3.0 - CVector3(2.0, 2.0, 2.0);
		if (s.z < -1.0) s.z = -2.0 - s.z;
		if (s.y < -1.0) s.y = -2.0 - s.y;
		if (s.x < -1.0) s.x = -2.0 - s.x;
	}
	return d * size * pow(3.0, -2.0);
}

// Apply universal shape modifiers to delta
static CVector3 ApplyShapeModifiers(CVector3 delta, const sCommonParams *par)
{
	// 1. 3D Repeat / Tiling
	if (par->fakeLightsShapeRepeatX > 0.0)
	{
		double half = par->fakeLightsShapeRepeatX * 0.5;
		delta.x = fmod(delta.x + half, par->fakeLightsShapeRepeatX);
		if (delta.x < 0.0) delta.x += par->fakeLightsShapeRepeatX;
		delta.x -= half;
	}
	if (par->fakeLightsShapeRepeatY > 0.0)
	{
		double half = par->fakeLightsShapeRepeatY * 0.5;
		delta.y = fmod(delta.y + half, par->fakeLightsShapeRepeatY);
		if (delta.y < 0.0) delta.y += par->fakeLightsShapeRepeatY;
		delta.y -= half;
	}
	if (par->fakeLightsShapeRepeatZ > 0.0)
	{
		double half = par->fakeLightsShapeRepeatZ * 0.5;
		delta.z = fmod(delta.z + half, par->fakeLightsShapeRepeatZ);
		if (delta.z < 0.0) delta.z += par->fakeLightsShapeRepeatZ;
		delta.z -= half;
	}

	// 2. Polar / Radial repeat (around Y axis)
	int radialCount = par->fakeLightsRadialRepeatCount;
	if (radialCount > 1)
	{
		double angle = atan2(delta.z, delta.x);
		double r = sqrt(delta.x * delta.x + delta.z * delta.z);
		double sector = 2.0 * M_PI / radialCount;
		angle = fmod(angle + sector / 2.0, sector);
		if (angle < 0.0) angle += sector;
		angle -= sector / 2.0;
		delta.x = cos(angle) * r - par->fakeLightsRadialRepeatRadius;
		delta.z = sin(angle) * r;
	}

	// 3. Displacement (Wobble)
	if (par->fakeLightsShapeWobbleAmplitude > 0.0 && par->fakeLightsShapeWobbleFrequency > 0.0)
	{
		double wa = par->fakeLightsShapeWobbleAmplitude;
		double wf = par->fakeLightsShapeWobbleFrequency;
		delta.x += wa * sin(wf * delta.y);
		delta.y += wa * sin(wf * delta.z);
		delta.z += wa * sin(wf * delta.x);
	}

	// 3. Fold symmetry (radial folding in XY plane)
	int fold = par->fakeLightsShapeFoldSymmetry;
	if (fold > 1)
	{
		double angle = atan2(delta.y, delta.x);
		double r = sqrt(delta.x * delta.x + delta.y * delta.y);
		double period = 2.0 * M_PI / fold;
		angle = fmod(angle + period / 2.0, period);
		if (angle < 0.0) angle += period;
		angle -= period / 2.0;
		delta.x = cos(angle) * r;
		delta.y = sin(angle) * r;
	}

	// 4. Taper: scale xz based on y
	double taperScale = 1.0 + par->fakeLightsShapeTaper * delta.y;
	if (taperScale < 1e-10) taperScale = 1e-10;
	delta.x *= taperScale;
	delta.z *= taperScale;

	// 5. Twist: rotate xz around y
	double twistAngle = par->fakeLightsShapeTwist * delta.y;
	double cosT = cos(twistAngle);
	double sinT = sin(twistAngle);
	double nx = delta.x * cosT - delta.z * sinT;
	double nz = delta.x * sinT + delta.z * cosT;
	delta.x = nx;
	delta.z = nz;

	// 6. Bend: curve space around a circle
	if (fabs(par->fakeLightsShapeBend) > 1e-10)
	{
		double bendAngle = par->fakeLightsShapeBend * delta.y;
		delta.y = sin(bendAngle) / par->fakeLightsShapeBend;
		delta.x += (1.0 - cos(bendAngle)) / par->fakeLightsShapeBend;
	}

	return delta;
}

// Helper: Sierpinski tetrahedron distance (approximate, 2 iterations)
static double SierpinskiTetraDist(CVector3 p, double size)
{
	CVector3 s = p / size;
	for (int i = 0; i < 2; i++)
	{
		if (s.x + s.y < 0.0) { double t = s.x; s.x = -s.y; s.y = -t; }
		if (s.x + s.z < 0.0) { double t = s.x; s.x = -s.z; s.z = -t; }
		if (s.y + s.z < 0.0) { double t = s.y; s.y = -s.z; s.z = -t; }
		s = s * 2.0 - CVector3(1.0, 1.0, 1.0);
	}
	return (s.Length() - 1.73205) * size * pow(2.0, -2.0);
}

// Helper: Apollonian distance (approximate)
static double ApollonianDist(CVector3 p, double size)
{
	CVector3 s = p / size;
	double scale = 1.0;
	for (int i = 0; i < 3; i++)
	{
		s.x = fabs(s.x);
		s.y = fabs(s.y);
		s.z = fabs(s.z);
		// inversion
		double r2 = s.Dot(s);
		if (r2 < 0.001) r2 = 0.001;
		s = s * (1.0 / r2);
		s = s * 2.5 - CVector3(1.0, 1.0, 1.0);
		scale *= 2.5;
	}
	return s.Length() * size / scale;
}

static double ShapeDistanceInternal(CVector3 delta, int shapeId, const sCommonParams *par)
{
	double dist = 0.0;
	switch (shapeId)
	{
		case params::fakeLightsShapePoint:
		{
			delta = ApplyShapeModifiers(delta, par);
			dist = delta.Length() - par->fakeLightsOrbitTrapSize;
			break;
		}
		case params::fakeLightsShapeLine:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			dist = sqrt(delta.y * delta.y + delta.z * delta.z) - par->fakeLightsOrbitTrapSize;
			break;
		}
		case params::fakeLightsShapeCircle:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double lengthYZ = sqrt(delta.y * delta.y + delta.z * delta.z) - par->fakeLightsOrbitTrapSize;
			dist = sqrt(lengthYZ * lengthYZ + delta.x * delta.x);
			break;
		}
		case params::fakeLightsShapeSquare:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double dy = max(fabs(fabs(delta.y) - par->fakeLightsOrbitTrapSize),
				fabs(delta.z) - par->fakeLightsOrbitTrapSize);
			double dz = max(fabs(fabs(delta.z) - par->fakeLightsOrbitTrapSize),
				fabs(delta.y) - par->fakeLightsOrbitTrapSize);
			double deltaRect = min(dy, dz);
			dist = sqrt(deltaRect * deltaRect + delta.x * delta.x);
			break;
		}
		case params::fakeLightsShapeSphere:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double lengthYZ = sqrt(delta.y * delta.y + delta.z * delta.z) - par->fakeLightsOrbitTrapSize;
			double distYZ = sqrt(lengthYZ * lengthYZ + delta.x * delta.x);
			double lengthXZ = sqrt(delta.x * delta.x + delta.z * delta.z) - par->fakeLightsOrbitTrapSize;
			double distXZ = sqrt(lengthXZ * lengthXZ + delta.y * delta.y);
			double lengthXY = sqrt(delta.x * delta.x + delta.y * delta.y) - par->fakeLightsOrbitTrapSize;
			double distXY = sqrt(lengthXY * lengthXY + delta.z * delta.z);
			dist = min(min(distYZ, distXZ), distXY);
			break;
		}
		case params::fakeLightsShapeCube:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double dy_x = max(fabs(fabs(delta.y) - size), fabs(delta.z) - size);
			double dz_x = max(fabs(fabs(delta.z) - size), fabs(delta.y) - size);
			double dx_z = max(fabs(fabs(delta.y) - size), fabs(delta.x) - size);
			double deltaRectYZ = min(dy_x, dz_x);
			double distYZ = CVector2<double>(deltaRectYZ, fabs(fabs(delta.x) - size)).Length();
			double distXZ = CVector2<double>(dx_z, fabs(fabs(delta.z) - size)).Length();
			dist = min(distYZ, distXZ);
			break;
		}
		case params::fakeLightsShapeTorus:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double q = sqrt(delta.x * delta.x + delta.y * delta.y) - par->fakeLightsOrbitTrapSize;
			dist = sqrt(q * q + delta.z * delta.z);
			break;
		}
		case params::fakeLightsShapeTriangle:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double h = par->fakeLightsOrbitTrapSize * 1.5;
			double d2d = max(fabs(delta.x) * 0.86602540378 + delta.y * 0.5, -delta.y) - h / 3.0;
			dist = Extrude2D(d2d, delta.z);
			break;
		}
		case params::fakeLightsShapeHexagon:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double d2d = max(fabs(delta.x) * 0.86602540378 + fabs(delta.y) * 0.5, fabs(delta.y))
						 - par->fakeLightsOrbitTrapSize;
			dist = Extrude2D(d2d, delta.z);
			break;
		}
		case params::fakeLightsShapeStar:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double a = atan2(delta.y, delta.x);
			double r = sqrt(delta.x * delta.x + delta.y * delta.y);
			double points = par->fakeLightsShapeParam1;
			if (points < 2.0) points = 5.0;
			double d2d = r - par->fakeLightsOrbitTrapSize * (0.55 + 0.45 * cos(a * points));
			dist = Extrude2D(d2d, delta.z);
			break;
		}
		case params::fakeLightsShapeCross:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double r = par->fakeLightsOrbitTrapSize;
			double d1 = sqrt(delta.y * delta.y + delta.z * delta.z) - r;
			double d2 = sqrt(delta.x * delta.x + delta.z * delta.z) - r;
			double d3 = sqrt(delta.x * delta.x + delta.y * delta.y) - r;
			dist = min(min(d1, d2), d3);
			break;
		}
		case params::fakeLightsShapeCapsule:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double h = par->fakeLightsOrbitTrapSize;
			double r = h * par->fakeLightsShapeParam2;
			if (r < 0.0) r = h * 0.2;
			double py = delta.y;
			if (py < -h) py = -h;
			if (py > h) py = h;
			dist = sqrt(delta.x * delta.x + (delta.y - py) * (delta.y - py) + delta.z * delta.z) - r;
			break;
		}
		case params::fakeLightsShapeCone:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double c = par->fakeLightsOrbitTrapSize * par->fakeLightsShapeParam2;
			if (c <= 0.0) c = par->fakeLightsOrbitTrapSize * 0.3;
			dist = sqrt(delta.x * delta.x + delta.z * delta.z) - c * fabs(delta.y);
			break;
		}
		case params::fakeLightsShapePyramid:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double h = par->fakeLightsOrbitTrapSize;
			double m = max(fabs(delta.x), fabs(delta.z));
			dist = max(m + delta.y * 0.5 - h * 0.5, delta.y);
			break;
		}
		case params::fakeLightsShapeTetrahedron:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double md = max(max(-delta.x - delta.y - delta.z, delta.x + delta.y - delta.z),
						max(delta.x - delta.y + delta.z, -delta.x + delta.y + delta.z));
			dist = md * 0.57735026919 - par->fakeLightsOrbitTrapSize * 0.57735026919;
			break;
		}
		case params::fakeLightsShapeOctahedron:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			dist = (fabs(delta.x) + fabs(delta.y) + fabs(delta.z) - par->fakeLightsOrbitTrapSize)
					 * 0.57735026919;
			break;
		}
		case params::fakeLightsShapeDodecahedron:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double px = fabs(delta.x);
			double py = fabs(delta.y);
			double pz = fabs(delta.z);
			double d = max(max(px + py + pz, px + py - pz),
						max(px - py + pz, -px + py + pz));
			double r = par->fakeLightsOrbitTrapSize;
			dist = d * 0.57735 - r * 0.57735 + (px * py + py * pz + pz * px) * 0.05 / r;
			break;
		}
		case params::fakeLightsShapeIcosahedron:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double px = fabs(delta.x);
			double py = fabs(delta.y);
			double pz = fabs(delta.z);
			double m = max(max(px, py), pz);
			double r = par->fakeLightsOrbitTrapSize;
			dist = (px + py + pz - r) * 0.57735 + (px * py * pz) * 0.1 / (r * r);
			break;
		}
		case params::fakeLightsShapeMengerSponge:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			dist = MengerSpongeDist(delta, par->fakeLightsOrbitTrapSize);
			break;
		}
		case params::fakeLightsShapeSierpinskiTetrahedron:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			dist = SierpinskiTetraDist(delta, par->fakeLightsOrbitTrapSize);
			break;
		}
		case params::fakeLightsShapeKochSnowflake:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			dist = Extrude2D(KochSnowflakeDist(delta.x, delta.y, par->fakeLightsOrbitTrapSize), delta.z);
			break;
		}
		case params::fakeLightsShapeHexGrid:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double s = par->fakeLightsOrbitTrapSize * 0.5;
			double qx = delta.x * 0.57735026918;
			double qy = delta.y + delta.x * 0.33333333333;
			double rx = SdfMod(qx, s) - s * 0.5;
			double ry = SdfMod(qy, s) - s * 0.5;
			double d2d = max(fabs(rx) * 0.86602540378 + fabs(ry) * 0.5, fabs(ry)) - s * 0.5;
			dist = Extrude2D(d2d, delta.z);
			break;
		}
		case params::fakeLightsShapeSpiral:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double a = atan2(delta.y, delta.x);
			double r = sqrt(delta.x * delta.x + delta.y * delta.y);
			double step = par->fakeLightsShapeParam1;
			if (step <= 0.0) step = 0.15;
			double spiralR = par->fakeLightsOrbitTrapSize * (0.1 + step * a);
			dist = Extrude2D(fabs(r - spiralR), delta.z);
			break;
		}
		case params::fakeLightsShapeGrid:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double s = par->fakeLightsOrbitTrapSize;
			double dx = SdfMod(delta.x + s * 0.5, s) - s * 0.5;
			double dy = SdfMod(delta.y + s * 0.5, s) - s * 0.5;
			double dz = SdfMod(delta.z + s * 0.5, s) - s * 0.5;
			double d1 = sqrt(dx * dx + dy * dy) - s * 0.1;
			double d2 = sqrt(dy * dy + dz * dz) - s * 0.1;
			double d3 = sqrt(dx * dx + dz * dz) - s * 0.1;
			dist = min(min(d1, d2), d3);
			break;
		}
		case params::fakeLightsShapeBuckyball:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double px = fabs(delta.x);
			double py = fabs(delta.y);
			double pz = fabs(delta.z);
			double r = par->fakeLightsOrbitTrapSize;
			double d1 = max(max(px + py + pz, px + py - pz),
						max(px - py + pz, -px + py + pz)) * 0.57735 - r * 0.57735;
			double d2 = (px + py + pz - r) * 0.57735 + (px * py * pz) * 0.1 / (r * r);
			dist = max(d1, d2) * 0.95;
			break;
		}
		case params::fakeLightsShapeApollonian:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			dist = ApollonianDist(delta, par->fakeLightsOrbitTrapSize);
			break;
		}
	}
	return dist;
}

double OrbitTrapShapeDistance(CVector4 z4, const sCommonParams *par)
{
	CVector3 z = z4.GetXYZ();
	CVector3 delta = z - par->fakeLightsOrbitTrap;

	double distA = ShapeDistanceInternal(delta, par->fakeLightsOrbitTrapShape, par);
	double dist = distA;

	if (par->fakeLightsBlendAmount > 0.0)
	{
		double distB = ShapeDistanceInternal(delta, par->fakeLightsBlendShape, par);
		dist = distA * (1.0 - par->fakeLightsBlendAmount) + distB * par->fakeLightsBlendAmount;
	}

	// Chamfer / Round: offset the distance to round sharp edges
	if (par->fakeLightsShapeChamfer > 0.0)
	{
		dist -= par->fakeLightsShapeChamfer;
	}

	// Onion / Hollow-shell: turn solid shape into thin shell
	if (par->fakeLightsOnionThickness > 0.0)
	{
		dist = fabs(dist) - par->fakeLightsOnionThickness;
	}

	return dist / par->fakeLightsThickness;
}

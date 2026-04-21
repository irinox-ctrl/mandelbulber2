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
	// 1. Fold symmetry (radial folding in XY plane)
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

	// 2. Taper: scale xz based on y
	double taperScale = 1.0 + par->fakeLightsShapeTaper * delta.y;
	if (taperScale < 1e-10) taperScale = 1e-10;
	delta.x *= taperScale;
	delta.z *= taperScale;

	// 3. Twist: rotate xz around y
	double twistAngle = par->fakeLightsShapeTwist * delta.y;
	double cosT = cos(twistAngle);
	double sinT = sin(twistAngle);
	double nx = delta.x * cosT - delta.z * sinT;
	double nz = delta.x * sinT + delta.z * cosT;
	delta.x = nx;
	delta.z = nz;

	// 4. Bend: curve space around a circle
	if (fabs(par->fakeLightsShapeBend) > 1e-10)
	{
		double bendAngle = par->fakeLightsShapeBend * delta.y;
		delta.y = sin(bendAngle) / par->fakeLightsShapeBend;
		delta.x += (1.0 - cos(bendAngle)) / par->fakeLightsShapeBend;
	}

	// 5. Repeat / Tiling
	double repeatX = par->fakeLightsShapeRepeatX;
	double repeatY = par->fakeLightsShapeRepeatY;
	double repeatZ = par->fakeLightsShapeRepeatZ;
	if (repeatX > 1e-10) delta.x = SdfMod(delta.x + repeatX * 0.5, repeatX) - repeatX * 0.5;
	if (repeatY > 1e-10) delta.y = SdfMod(delta.y + repeatY * 0.5, repeatY) - repeatY * 0.5;
	if (repeatZ > 1e-10) delta.z = SdfMod(delta.z + repeatZ * 0.5, repeatZ) - repeatZ * 0.5;

	// 6. Wobble
	double wobbleAmp = par->fakeLightsShapeWobbleAmplitude;
	double wobbleFreq = par->fakeLightsShapeWobbleFrequency;
	if (fabs(wobbleAmp) > 1e-10 && fabs(wobbleFreq) > 1e-10)
	{
		delta.x += wobbleAmp * sin(wobbleFreq * delta.y);
		delta.y += wobbleAmp * sin(wobbleFreq * delta.z);
		delta.z += wobbleAmp * sin(wobbleFreq * delta.x);
	}

	// 7. Spiral: rotate xz around y, angle increases with radius
	double spiral = par->fakeLightsShapeSpiral;
	if (fabs(spiral) > 1e-10)
	{
		double r = sqrt(delta.x * delta.x + delta.z * delta.z);
		double angle = spiral * r;
		double cosS = cos(angle);
		double sinS = sin(angle);
		double nx = delta.x * cosS - delta.z * sinS;
		double nz = delta.x * sinS + delta.z * cosS;
		delta.x = nx;
		delta.z = nz;
	}

	// 8. Wave: sinus displacement per axis
	double waveFreq = par->fakeLightsShapeWaveFrequency;
	if (fabs(waveFreq) > 1e-10)
	{
		delta.x += par->fakeLightsShapeWaveX * sin(waveFreq * delta.x);
		delta.y += par->fakeLightsShapeWaveY * sin(waveFreq * delta.y);
		delta.z += par->fakeLightsShapeWaveZ * sin(waveFreq * delta.z);
	}

	// 9. Scale
	double scaleX = par->fakeLightsShapeScaleX;
	double scaleY = par->fakeLightsShapeScaleY;
	double scaleZ = par->fakeLightsShapeScaleZ;
	if (fabs(scaleX) > 1e-10) delta.x /= scaleX;
	if (fabs(scaleY) > 1e-10) delta.y /= scaleY;
	if (fabs(scaleZ) > 1e-10) delta.z /= scaleZ;

	// 8. Mirror
	if (par->fakeLightsShapeMirrorX) delta.x = fabs(delta.x);
	if (par->fakeLightsShapeMirrorY) delta.y = fabs(delta.y);
	if (par->fakeLightsShapeMirrorZ) delta.z = fabs(delta.z);

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

double OrbitTrapShapeDistance(CVector4 z4, const sCommonParams *par)
{
	double dist = 0.0;
	CVector3 z = z4.GetXYZ();
	CVector3 delta = z - par->fakeLightsOrbitTrap;
	double thicknessDivisor = par->fakeLightsThickness;

	switch (par->fakeLightsOrbitTrapShape)
	{
		case params::fakeLightsShapePoint:
		{
			dist = delta.Length();
			break;
		}
		case params::fakeLightsShapeLine:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			// Line with thickness (radius) - distance from Y axis with offset
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
			double dx_z = max(fabs(fabs(delta.x) - size), fabs(delta.z) - size);
			double deltaRectYZ = min(dy_x, dz_x);
			double distYZ = CVector2<double>(deltaRectYZ, fabs(fabs(delta.x) - size)).Length();
			double distXZ = CVector2<double>(dx_z, fabs(fabs(delta.y) - size)).Length();

			dist = min(distYZ, distXZ);
			break;
		}
		case params::fakeLightsShapeTriangle:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double angle = atan2(delta.z, delta.y);
			double radius = sqrt(delta.y * delta.y + delta.z * delta.z);
			double triangleRadius = size * cos(M_PI / 3.0) / cos(fmod(angle + M_PI / 3.0, 2.0 * M_PI / 3.0) - M_PI / 3.0);
			dist = fabs(radius - triangleRadius) + fabs(delta.x);
			break;
		}
		case params::fakeLightsShapeHexagon:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double angle = atan2(delta.z, delta.y);
			double radius = sqrt(delta.y * delta.y + delta.z * delta.z);
			double hexRadius = size * cos(M_PI / 6.0) / cos(fmod(angle + M_PI / 6.0, M_PI / 3.0) - M_PI / 6.0);
			dist = fabs(radius - hexRadius) + fabs(delta.x);
			break;
		}
		case params::fakeLightsShapeTorus:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double majorRadius = size;
			double minorRadius = size * 0.3;
			double lengthYZ = sqrt(delta.y * delta.y + delta.z * delta.z) - majorRadius;
			dist = sqrt(lengthYZ * lengthYZ + delta.x * delta.x) - minorRadius;
			break;
		}
		case params::fakeLightsShapeCylinder:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Cylinder along Y axis with rounded caps
			double distYZ = sqrt(delta.y * delta.y + delta.z * delta.z) - size;
			dist = max(distYZ, fabs(delta.x) - size);
			break;
		}
		case params::fakeLightsShapeCone:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double angle = atan2(sqrt(delta.y * delta.y + delta.z * delta.z), fabs(delta.x));
			double coneRadius = size * (1.0 - fabs(delta.x) / (size * 2.0));
			double distRadial = sqrt(delta.y * delta.y + delta.z * delta.z) - coneRadius;
			dist = max(distRadial, fabs(delta.x) - size * 2.0);
			break;
		}
		case params::fakeLightsShapePyramid:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double baseDist = max(fabs(delta.y), fabs(delta.z)) - size * (1.0 - fabs(delta.x) / (size * 2.0));
			dist = max(baseDist, fabs(delta.x) - size * 2.0);
			break;
		}
		case params::fakeLightsShapeOctahedron:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			dist = (fabs(delta.x) + fabs(delta.y) + fabs(delta.z) - size);
			break;
		}
		case params::fakeLightsShapeEllipse:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double lengthYZ = sqrt(delta.y * delta.y + (delta.z * 1.5) * (delta.z * 1.5)) - size;
			dist = sqrt(lengthYZ * lengthYZ + delta.x * delta.x);
			break;
		}
		case params::fakeLightsShapeRectangle:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double dy = max(fabs(delta.y) - size * 1.5, 0.0);
			double dz = max(fabs(delta.z) - size * 0.7, 0.0);
			dist = sqrt(dy * dy + dz * dz + delta.x * delta.x);
			break;
		}
		case params::fakeLightsShapeCross:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double armY = max(fabs(delta.y) - size, fabs(delta.z) - size * 0.3);
			double armZ = max(fabs(delta.z) - size, fabs(delta.y) - size * 0.3);
			dist = min(armY, armZ) + fabs(delta.x);
			break;
		}
		case params::fakeLightsShapeStar:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double angle = atan2(delta.z, delta.y);
			double radius = sqrt(delta.y * delta.y + delta.z * delta.z);
			double starAngle = fmod(angle + M_PI / 5.0, 2.0 * M_PI / 5.0) - M_PI / 5.0;
			double starRadius = size * (0.5 + 0.5 * cos(5.0 * angle));
			dist = fabs(radius - starRadius) + fabs(delta.x);
			break;
		}
		case params::fakeLightsShapeDiamond:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			dist = (fabs(delta.y) + fabs(delta.z) - size * 1.414) + fabs(delta.x);
			break;
		}
		case params::fakeLightsShapeRing:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double radius = sqrt(delta.y * delta.y + delta.z * delta.z);
			dist = fabs(radius - size);
			break;
		}
		case params::fakeLightsShapeCapsule:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double radius = size * 0.3;
			double lengthYZ = sqrt(delta.y * delta.y + delta.z * delta.z);
			double distYZ = max(lengthYZ - size, 0.0);
			dist = sqrt(distYZ * distYZ + delta.x * delta.x) - radius;
			break;
		}
		case params::fakeLightsShapePrism:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double q = fabs(delta.y) * 0.866025 + delta.z * 0.5;
			dist = max(q, -delta.z) - size * 0.5;
			break;
		}
		case params::fakeLightsShapeTorusKnot:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double p = 2.0, q = 3.0;
			double r = sqrt(delta.y * delta.y + delta.z * delta.z);
			double theta = atan2(delta.z, delta.y);
			double phi = theta * q / p;
			double majorRadius = size;
			double minorRadius = size * 0.2;
			double knotX = (majorRadius + minorRadius * cos(q * theta)) * cos(p * theta);
			double knotY = (majorRadius + minorRadius * cos(q * theta)) * sin(p * theta);
			double knotZ = minorRadius * sin(q * theta);
			dist = sqrt(pow(r - sqrt(knotX * knotX + knotY * knotY), 2) + pow(delta.x - knotZ, 2));
			break;
		}
		case params::fakeLightsShapeBoxFrame:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double thickness = size * 0.2;
			double dX = max(fabs(delta.x) - size, 0.0);
			double dY = max(fabs(delta.y) - size, 0.0);
			double dZ = max(fabs(delta.z) - size, 0.0);
			double distEdges = sqrt(dX * dX + dY * dY + dZ * dZ) - thickness;
			// Frame consists of edges only
			double onEdgeX = (fabs(delta.x) > size - thickness && fabs(delta.y) < size && fabs(delta.z) < size) ? fabs(fabs(delta.x) - size) : 1000.0;
			double onEdgeY = (fabs(delta.y) > size - thickness && fabs(delta.x) < size && fabs(delta.z) < size) ? fabs(fabs(delta.y) - size) : 1000.0;
			double onEdgeZ = (fabs(delta.z) > size - thickness && fabs(delta.x) < size && fabs(delta.y) < size) ? fabs(fabs(delta.z) - size) : 1000.0;
			dist = min(min(onEdgeX, onEdgeY), onEdgeZ);
			break;
		}
		case params::fakeLightsShapeConeInfinite:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double coneAngle = 0.3;
			double distRadial = sqrt(delta.y * delta.y + delta.z * delta.z) - fabs(delta.x) * coneAngle;
			dist = distRadial;
			break;
		}
		case params::fakeLightsShapeCylinderCap:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double radius = size * 0.3;
			double distYZ = sqrt(delta.y * delta.y + delta.z * delta.z) - radius;
			double distX = fabs(delta.x) - size;
			// Blend between cylinder and spherical caps
			dist = max(distYZ, distX);
			break;
		}
		case params::fakeLightsShapeSuperellipsoid:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double e = 0.5; // Exponent
			dist = pow(pow(fabs(delta.x), e) + pow(fabs(delta.y), e) + pow(fabs(delta.z), e), 1.0 / e) - size;
			break;
		}
		case params::fakeLightsShapePlane:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Infinite plane at X=0 with thickness
			dist = fabs(delta.x) - size * 0.1;
			break;
		}
		case params::fakeLightsShapeDisc:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double r = sqrt(delta.y * delta.y + delta.z * delta.z);
			// Solid disc in YZ plane
			dist = max(fabs(delta.x) - size * 0.1, r - size);
			break;
		}
		case params::fakeLightsShapeGear:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double angle = atan2(delta.z, delta.y);
			double r = sqrt(delta.y * delta.y + delta.z * delta.z);
			// 6 teeth gear
			double gearRadius = size * (0.7 + 0.3 * cos(6.0 * angle));
			dist = fabs(r - gearRadius) + fabs(delta.x) * 0.1;
			break;
		}
		case params::fakeLightsShapeSpiral:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double angle = atan2(delta.z, delta.y);
			double r = sqrt(delta.y * delta.y + delta.z * delta.z);
			// Archimedean spiral with 3 turns
			double spiralRadius = size * (0.1 + 0.9 * fmod(angle / (2.0 * M_PI) + 3.0, 1.0));
			dist = fabs(r - spiralRadius) + fabs(delta.x) * 0.1;
			break;
		}
		case params::fakeLightsShapeHeart:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double y = delta.y / size;
			double z = delta.z / size;
			// Heart shape equation
			double heart = pow(y * y + z * z - 1.0, 3) - y * y * z * z * z;
			dist = fabs(heart) * size * 0.1 + fabs(delta.x) * 0.1;
			break;
		}
		case params::fakeLightsShapeCrescent:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Two circles creating crescent
			double r1 = sqrt(delta.y * delta.y + delta.z * delta.z) - size;
			double r2 = sqrt((delta.y - size * 0.5) * (delta.y - size * 0.5) + delta.z * delta.z) - size * 0.8;
			dist = max(r1, -r2) + fabs(delta.x) * 0.1;
			break;
		}
		case params::fakeLightsShapeArrow:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double y = delta.y / size;
			double z = delta.z / size;
			// Arrow pointing along Y axis
			double shaft = max(fabs(y) - 1.0, fabs(z) - 0.15);
			double head = max(max(-y - 0.3, fabs(z) - (0.7 + y)), y - 0.3);
			dist = min(shaft, head) * size + fabs(delta.x) * 0.1;
			break;
		}
		case params::fakeLightsShapeRoundedBox:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double radius = size * 0.2;
			// Box with rounded edges
			CVector3 d = CVector3(fabs(delta.x), fabs(delta.y), fabs(delta.z)) - CVector3(size - radius, size - radius, size - radius);
			CVector3 dMax = CVector3(max(d.x, 0.0), max(d.y, 0.0), max(d.z, 0.0));
			dist = dMax.Length() + min(max(d.x, max(d.y, d.z)), 0.0) - radius;
			break;
		}
		case params::fakeLightsShapeStadium:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double width = size;
			double length = size * 2.0;
			// Rectangle with semicircles on ends
			double dy = max(fabs(delta.y) - length, 0.0);
			double dz = fabs(delta.z) - width;
			dist = sqrt(dy * dy + max(dz, 0.0) * max(dz, 0.0)) + min(0.0, dz) + fabs(delta.x) * 0.1;
			break;
		}
		case params::fakeLightsShapePolygon5:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double angle = atan2(delta.z, delta.y);
			double r = sqrt(delta.y * delta.y + delta.z * delta.z);
			// Pentagon
			double polyRadius = size * cos(M_PI / 5.0) / cos(fmod(angle + M_PI / 5.0, 2.0 * M_PI / 5.0) - M_PI / 5.0);
			dist = fabs(r - polyRadius) + fabs(delta.x) * 0.1;
			break;
		}
		case params::fakeLightsShapePolygon8:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double angle = atan2(delta.z, delta.y);
			double r = sqrt(delta.y * delta.y + delta.z * delta.z);
			// Octagon
			double polyRadius = size * cos(M_PI / 8.0) / cos(fmod(angle + M_PI / 8.0, M_PI / 4.0) - M_PI / 8.0);
			dist = fabs(r - polyRadius) + fabs(delta.x) * 0.1;
			break;
		}
		case params::fakeLightsShapeTrefoilKnot:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double t = atan2(delta.z, delta.y);
			double r = sqrt(delta.y * delta.y + delta.z * delta.z);
			// Trefoil knot (2,3)
			double majorR = size;
			double minorR = size * 0.25;
			double knotY = (majorR + minorR * cos(3.0 * t)) * cos(2.0 * t);
			double knotZ = (majorR + minorR * cos(3.0 * t)) * sin(2.0 * t);
			double distYZ = sqrt((r - sqrt(knotY * knotY + knotZ * knotZ)) * (r - sqrt(knotY * knotY + knotZ * knotZ)));
			dist = sqrt(distYZ * distYZ + delta.x * delta.x) - minorR * 0.5;
			break;
		}
		case params::fakeLightsShapeFigureEight:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double y = delta.y / size;
			double z = delta.z / size;
			// Figure-8 curve
			double curveY = sin(y * 2.0);
			double curveZ = sin(y * 4.0) * 0.5;
			dist = sqrt((z - curveZ) * (z - curveZ) + (y - curveY) * (y - curveY)) * size + fabs(delta.x) * 0.1;
			break;
		}
		case params::fakeLightsShapeMobiusStrip:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double r = sqrt(delta.x * delta.x + delta.y * delta.y);
			double angle = atan2(delta.y, delta.x);
			// Mobius strip
			double width = size * 0.3;
			double distToCenter = fabs(r - size);
			double twist = delta.z - width * sin(angle * 0.5);
			dist = sqrt(distToCenter * distToCenter + twist * twist) - width * 0.1;
			break;
		}
		case params::fakeLightsShapeTorusSector:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double angle = atan2(delta.z, delta.y);
			double r = sqrt(delta.y * delta.y + delta.z * delta.z);
			// 90 degree sector of torus
			double sector = (angle > 0 && angle < M_PI / 2.0) ? 0.0 : min(fabs(angle), fabs(angle - M_PI / 2.0));
			double majorR = size;
			double minorR = size * 0.3;
			double distToTube = fabs(r - majorR);
			dist = sqrt(distToTube * distToTube + delta.x * delta.x + sector * majorR) - minorR;
			break;
		}
		case params::fakeLightsShapeHelix:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double t = delta.x / size * 2.0;
			double helixY = cos(t) * size;
			double helixZ = sin(t) * size;
			dist = sqrt((delta.y - helixY) * (delta.y - helixY) + (delta.z - helixZ) * (delta.z - helixZ)) - size * 0.2;
			break;
		}
		case params::fakeLightsShapeConeRounded:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double h = size * 2.0;
			double r = size;
			double y = delta.y + h * 0.5;
			// Cone with rounded tip
			double coneR = r * (1.0 - y / h);
			double distRadial = sqrt(delta.x * delta.x + delta.z * delta.z) - coneR;
			double distHeight = max(y - h, -y);
			dist = max(distRadial, distHeight);
			break;
		}
		case params::fakeLightsShapeCylinderHollow:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double outerR = size;
			double innerR = size * 0.7;
			double r = sqrt(delta.y * delta.y + delta.z * delta.z);
			// Hollow cylinder (tube)
			dist = max(fabs(r - (outerR + innerR) * 0.5) - (outerR - innerR) * 0.5, fabs(delta.x) - size * 2.0);
			break;
		}
		case params::fakeLightsShapeSphereHollow:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double outerR = size;
			double innerR = size * 0.8;
			double r = delta.Length();
			// Hollow sphere (spherical shell)
			dist = fabs(r - (outerR + innerR) * 0.5) - (outerR - innerR) * 0.5;
			break;
		}
		case params::fakeLightsShapeTorusTwist:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double angle = atan2(delta.z, delta.y);
			double r = sqrt(delta.y * delta.y + delta.z * delta.z);
			// Torus with twisted cross-section
			double twist = angle * 2.0;
			double majorR = size;
			double minorR = size * 0.3;
			double twistedX = delta.x * cos(twist) - (r - majorR) * sin(twist);
			double twistedR = delta.x * sin(twist) + (r - majorR) * cos(twist);
			dist = sqrt(twistedX * twistedX + twistedR * twistedR) - minorR;
			break;
		}
		case params::fakeLightsShapeGrid:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// 2D Grid lines in XY plane
			double gx = fabs(fmod(delta.x, size) - size * 0.5);
			double gy = fabs(fmod(delta.y, size) - size * 0.5);
			double lineWidth = size * 0.15;
			// Distance to grid lines
			double distToLine = min(gx, gy);
			dist = max(distToLine - lineWidth, fabs(delta.z) * 0.5);
			break;
		}
		case params::fakeLightsShapeLattice:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// 3D Grid/Lattice structure
			double gx = fabs(fmod(delta.x, size) - size * 0.5);
			double gy = fabs(fmod(delta.y, size) - size * 0.5);
			double gz = fabs(fmod(delta.z, size) - size * 0.5);
			double lineWidth = size * 0.12;
			// Distance to nearest grid line in all 3 axes
			dist = min(min(gx, gy), gz) - lineWidth;
			break;
		}
		case params::fakeLightsShapeSponge:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double scale = 1.0;
			double d = delta.Length();
			for (int i = 0; i < 3; i++)
			{
				scale *= 3.0;
				double px = fabs(fmod(delta.x * scale, 3.0) - 1.5);
				double py = fabs(fmod(delta.y * scale, 3.0) - 1.5);
				double pz = fabs(fmod(delta.z * scale, 3.0) - 1.5);
				if (px > pz) { double t = px; px = pz; pz = t; }
				if (px > py) { double t = px; px = py; py = t; }
				if (pz > py) { double t = pz; pz = py; py = t; }
				if (py > 1.0)
				{
					d = min(d, (py - 1.0) / scale);
				}
			}
			dist = d - size * 0.1;
			break;
		}
		case params::fakeLightsShapeTree:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double r = sqrt(delta.x * delta.x + delta.z * delta.z);
			double h = delta.y;
			double angle = atan2(delta.z, delta.x);
			double branch = fmod(angle * 4.0 + h * 2.0, 2.0 * M_PI);
			double branchR = size * (1.0 - h / (size * 4.0)) * (0.5 + 0.3 * cos(branch));
			dist = sqrt(pow(r - branchR, 2.0) + pow(fmod(h, size) - size * 0.5, 2.0)) - size * 0.1;
			break;
		}
		case params::fakeLightsShapeKnot34:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double t = atan2(delta.y, delta.x);
			double r = sqrt(delta.x * delta.x + delta.y * delta.y);
			double R = size;
			double P = 3.0;
			double Q = 4.0;
			double px = (R + size * 0.3 * cos(Q * t)) * cos(P * t);
			double py = (R + size * 0.3 * cos(Q * t)) * sin(P * t);
			double pz = size * 0.3 * sin(Q * t);
			dist = sqrt(pow(r * cos(t) - px, 2.0) + pow(r * sin(t) - py, 2.0) + pow(delta.z - pz, 2.0)) - size * 0.1;
			break;
		}
		case params::fakeLightsShapeSpiral3D:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double t = delta.y;
			double radius = size * 0.5;
			double turns = 2.0;
			double angle = turns * t / size * M_PI;
			double px = radius * cos(angle);
			double pz = radius * sin(angle);
			dist = sqrt(pow(delta.x - px, 2.0) + pow(delta.z - pz, 2.0)) - size * 0.1;
			break;
		}
		case params::fakeLightsShapeNoise:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double px = delta.x / size;
			double py = delta.y / size;
			double pz = delta.z / size;
			double noise = sin(px * 3.7) * sin(py * 4.3) * sin(pz * 5.1);
			noise += 0.5 * sin(px * 7.3 + 1.0) * sin(py * 8.7 + 2.0) * sin(pz * 9.1 + 3.0);
			dist = delta.Length() - size * (0.8 + 0.4 * noise);
			break;
		}
		case params::fakeLightsShapeVoronoi:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double px = delta.x / size;
			double py = delta.y / size;
			double pz = delta.z / size;
			double cx = floor(px);
			double cy = floor(py);
			double cz = floor(pz);
			double lx = px - cx;
			double ly = py - cy;
			double lz = pz - cz;
			double minDist = 10.0;
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					for (int k = -1; k <= 1; k++)
					{
						double nx = cx + i;
						double ny = cy + j;
						double nz = cz + k;
						double rnd = sin(nx * 12.9898 + ny * 78.233 + nz * 43.123) * 43758.5453;
						rnd = rnd - floor(rnd);
						double ptx = rnd;
						double pty = rnd * 1.3 - floor(rnd * 1.3);
						double ptz = rnd * 2.7 - floor(rnd * 2.7);
						double dx = lx - ptx - i;
						double dy = ly - pty - j;
						double dz = lz - ptz - k;
						double d = sqrt(dx * dx + dy * dy + dz * dz);
						if (d < minDist) minDist = d;
					}
				}
			}
			dist = minDist * size - size * 0.05;
			break;
		}
		case params::fakeLightsShapeMandelbrot2D:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double cx = delta.x / size;
			double cy = delta.y / size;
			double zx = cx;
			double zy = cy;
			double len = 0.0;
			for (int i = 0; i < 20; i++)
			{
				double zx2 = zx * zx - zy * zy + cx;
				zy = 2.0 * zx * zy + cy;
				zx = zx2;
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeJulia2D:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double zx = delta.x / size;
			double zy = delta.y / size;
			double cx = 0.355;
			double cy = 0.355;
			double len = 0.0;
			for (int i = 0; i < 20; i++)
			{
				double zx2 = zx * zx - zy * zy + cx;
				zy = 2.0 * zx * zy + cy;
				zx = zx2;
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeSierpinski:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double px = delta.x / size;
			double py = delta.y / size;
			double pz = delta.z / size;
			double d = 0.0;
			for (int i = 0; i < 4; i++)
			{
				px = fabs(px);
				py = fabs(py);
				pz = fabs(pz);
				if (px + py + pz > 1.0)
				{
					d = (px + py + pz - 1.0) / pow(2.0, i);
					break;
				}
				px = px * 2.0 - 1.0;
				py = py * 2.0 - 1.0;
				pz = pz * 2.0 - 1.0;
			}
			dist = d * size;
			break;
		}
		case params::fakeLightsShapeKoch:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double r = sqrt(delta.x * delta.x + delta.z * delta.z) / size;
			double angle = atan2(delta.z, delta.x);
			double kochDist = fabs(sin(3.0 * angle)) * 0.3 * sin(log(r) * 2.0);
			dist = fabs(r - 1.0 - kochDist) * size - size * 0.05;
			break;
		}
		case params::fakeLightsShapeDragon:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double zx = delta.x / size;
			double zy = delta.z / size;
			double cx = 0.45;
			double cy = 0.0;
			double len = 0.0;
			for (int i = 0; i < 20; i++)
			{
				double zx2 = zx * zx - zy * zy + cx;
				zy = 2.0 * fabs(zx * zy) - cy;
				zx = zx2;
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeHilbert:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			double px = delta.x / size;
			double py = delta.y / size;
			double pz = delta.z / size;
			double curve = sin(px * 2.0) * sin(py * 2.0) * sin(pz * 2.0);
			curve += sin(px * 4.0 + 1.0) * sin(py * 4.0 + 2.0) * sin(pz * 4.0 + 3.0) * 0.5;
			dist = delta.Length() - size * (0.5 + 0.3 * curve);
			break;
		}
		case params::fakeLightsShapeGyroid:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Gyroid minimal surface - period matches sphere diameter (2*size)
			double px = delta.x * M_PI / size;
			double py = delta.y * M_PI / size;
			double pz = delta.z * M_PI / size;
			double g = sin(px) * cos(py) + sin(py) * cos(pz) + sin(pz) * cos(px);
			// Thickened surface
			dist = fabs(g) * size * 0.3 - size * 0.08;
			break;
		}
		case params::fakeLightsShapeSchwarzP:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Schwarz P (Primitive) minimal surface - period matches sphere diameter
			double px = delta.x * M_PI / size;
			double py = delta.y * M_PI / size;
			double pz = delta.z * M_PI / size;
			double s = cos(px) + cos(py) + cos(pz);
			// Thickened surface
			dist = fabs(s) * size * 0.25 - size * 0.12;
			break;
		}
		case params::fakeLightsShapeSchwarzD:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Schwarz D (Diamond) minimal surface - period matches sphere diameter
			double px = delta.x * M_PI / size;
			double py = delta.y * M_PI / size;
			double pz = delta.z * M_PI / size;
			double s = sin(px) * sin(py) * sin(pz) + sin(px) * cos(py) * cos(pz) 
			         + cos(px) * sin(py) * cos(pz) + cos(px) * cos(py) * sin(pz);
			// Thickened surface
			dist = fabs(s) * size * 0.25 - size * 0.12;
			break;
		}
		case params::fakeLightsShapeNeovius:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Neovius minimal surface - smaller period for more features
			double px = delta.x * 2.0 * M_PI / size;
			double py = delta.y * 2.0 * M_PI / size;
			double pz = delta.z * 2.0 * M_PI / size;
			double n = 3.0 * (cos(px) + cos(py) + cos(pz)) + 4.0 * cos(px) * cos(py) * cos(pz);
			// Much thicker surface for visibility
			dist = fabs(n) * size * 0.15 - size * 0.12;
			break;
		}
		case params::fakeLightsShapeLabyrinth:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// 3D Maze - walls at grid lines with passages
			double cellSize = size;
			double wallThick = size * 0.15;
			// Distance to nearest cell border in each axis
			double dx = fabs(fmod(delta.x, cellSize) - cellSize * 0.5);
			double dy = fabs(fmod(delta.y, cellSize) - cellSize * 0.5);
			double dz = fabs(fmod(delta.z, cellSize) - cellSize * 0.5);
			// Distance to walls (closest border)
			double distToWall = min(min(dx, dy), dz);
			// Create maze pattern - remove some walls based on cell position
			int cellX = (int)floor(delta.x / cellSize);
			int cellY = (int)floor(delta.y / cellSize);
			int cellZ = (int)floor(delta.z / cellSize);
			// Simple hash for which walls exist
			bool removeX = ((cellX + cellY + cellZ) % 3) == 0;
			bool removeY = ((cellX + cellY * 2 + cellZ) % 3) == 0;
			bool removeZ = ((cellX + cellY + cellZ * 2) % 3) == 0;
			// Apply wall removal
			if (removeX && dx < dy && dx < dz) distToWall = 999.0;
			if (removeY && dy < dx && dy < dz) distToWall = 999.0;
			if (removeZ && dz < dx && dz < dy) distToWall = 999.0;
			// Distance field: positive outside walls, negative inside (solid)
			dist = distToWall - wallThick;
			break;
		}
		case params::fakeLightsShapeFiber:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Fiber bundle along Z axis with spiral twist - scale everything
			double angle = atan2(delta.y, delta.x);
			double r = sqrt(delta.x * delta.x + delta.y * delta.y) / size; // Normalized radius
			double fibers = 5.0; // Number of fibers
			double twist = 2.0;  // Twist amount per unit
			double zNorm = delta.z / size; // Normalized Z
			double fiberAngle = fmod(angle * fibers + zNorm * twist, 2.0 * M_PI);
			double distToFiber = fabs(sin(fiberAngle)) * r * size; // Scale back to world
			dist = distToFiber - size * 0.1 + fabs(fmod(zNorm, 1.0) - 0.5) * size * 0.2;
			break;
		}
		case params::fakeLightsShapeAstroid:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Astroid: hypocycloid with 4 cusps
			double t = atan2(delta.z, delta.y);
			double a = size;
			double astY = a * pow(cos(t), 3);
			double astZ = a * pow(sin(t), 3);
			dist = sqrt(pow(delta.y - astY, 2.0) + pow(delta.z - astZ, 2.0)) + fabs(delta.x) * 0.2;
			break;
		}
		case params::fakeLightsShapeDeltoid:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Deltoid: hypocycloid with 3 cusps
			double t = atan2(delta.z, delta.y);
			double a = size * 0.67;
			double delY = a * (2.0 * cos(t) + cos(2.0 * t));
			double delZ = a * (2.0 * sin(t) - sin(2.0 * t));
			dist = sqrt(pow(delta.y - delY, 2.0) + pow(delta.z - delZ, 2.0)) + fabs(delta.x) * 0.2;
			break;
		}
		case params::fakeLightsShapeLemniscate:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Lemniscate of Bernoulli (figure-8)
			double t = atan2(delta.z, delta.y);
			double a = size;
			double lemY = a * cos(t) / (1.0 + sin(t) * sin(t));
			double lemZ = a * sin(t) * cos(t) / (1.0 + sin(t) * sin(t));
			dist = sqrt(pow(delta.y - lemY, 2.0) + pow(delta.z - lemZ, 2.0)) + fabs(delta.x) * 0.2;
			break;
		}
		case params::fakeLightsShapeLimacon:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Limacon (snail shell)
			double t = atan2(delta.z, delta.y);
			double a = size * 0.5;
			double b = size * 0.8;
			double limR = b + a * cos(t);
			double limY = limR * cos(t);
			double limZ = limR * sin(t);
			dist = sqrt(pow(delta.y - limY, 2.0) + pow(delta.z - limZ, 2.0)) + fabs(delta.x) * 0.2;
			break;
		}
		case params::fakeLightsShapeSphericalHarmonics:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Spherical harmonics Y(3,2)
			double r = delta.Length() / size;
			double phi = atan2(delta.z, sqrt(delta.x * delta.x + delta.y * delta.y));
			double theta = atan2(delta.y, delta.x);
			double sh = sin(theta) * sin(theta) * cos(2.0 * phi) * sin(3.0 * theta);
			dist = fabs(r - 1.0 - sh * 0.3) * size;
			break;
		}
		case params::fakeLightsShapeSuperformula:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Superformula (generalized superellipse)
			double phi = atan2(delta.z, delta.y);
			double theta = atan2(delta.x, sqrt(delta.y * delta.y + delta.z * delta.z));
			double m = 6.0, n1 = 1.0, n2 = 1.0, n3 = 1.0, a = 1.0, b = 1.0;
			double r1 = pow(pow(fabs(cos(m * phi / 4.0) / a), n2) + pow(fabs(sin(m * phi / 4.0) / b), n3), -1.0 / n1);
			double r2 = r1 * (1.0 + 0.3 * cos(3.0 * theta));
			double r = sqrt(delta.y * delta.y + delta.z * delta.z);
			dist = fabs(r - r2 * size) + fabs(delta.x) * 0.15;
			break;
		}
		case params::fakeLightsShapeFern:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Barnsley fern inspired shape
			double r = sqrt(delta.x * delta.x + delta.z * delta.z) / size;
			double angle = atan2(delta.z, delta.x);
			double fernR = exp(-r * 0.5) * (1.0 + 0.3 * sin(5.0 * angle + r * 2.0));
			dist = fabs(r - fernR) * size + fabs(delta.y) * 0.3;
			break;
		}
		case params::fakeLightsShapeShell:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Seashell (logarithmic spiral)
			double t = delta.y / size * 0.5;
			double a = size * 0.1;
			double b = 0.3;
			double shellR = a * exp(b * t);
			double angle = t * 3.0;
			double shellX = shellR * cos(angle);
			double shellZ = shellR * sin(angle);
			dist = sqrt(pow(delta.x - shellX, 2.0) + pow(delta.z - shellZ, 2.0)) + fabs(fmod(t, 1.0) - 0.5) * size * 0.1;
			break;
		}
		case params::fakeLightsShapeCoral:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Coral branching structure
			double r = sqrt(delta.x * delta.x + delta.z * delta.z);
			double h = delta.y;
			double angle = atan2(delta.z, delta.x);
			double branches = 6.0;
			double branch = fmod(angle * branches + h * 1.5, 2.0 * M_PI);
			double coralR = size * (1.0 - h / (size * 3.0)) * (0.3 + 0.2 * fabs(sin(branch)));
			dist = sqrt(pow(r - coralR, 2.0) + pow(fmod(h, size * 0.5) - size * 0.25, 2.0)) - size * 0.05;
			break;
		}
		case params::fakeLightsShapeCrystal:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Crystal/gem facets
			double px = delta.x / size;
			double py = delta.y / size;
			double pz = delta.z / size;
			double facets = fabs(px) + fabs(py) + fabs(pz);
			dist = fabs(facets - 1.5) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeHoneycomb:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Hexagonal honeycomb pattern
			double px = delta.x / size;
			double py = delta.y / size;
			double xHex = px * 2.0 / sqrt(3.0);
			double yHex = py + floor(px) * 0.5;
			double ix = floor(xHex);
			double iy = floor(yHex);
			double fx = xHex - ix;
			double fy = yHex - iy;
			double distHex = (fx + fy > 1.0) ? 1.0 - fx : fy;
			dist = distHex * size * 0.5 + fabs(delta.z) * 0.3;
			break;
		}
		case params::fakeLightsShapeChain:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Chain of linked rings
			double t = delta.z / (size * 0.8);
			double link = fmod(t, 2.0);
			double offset = ((int)floor(t) % 2 == 0) ? 0.0 : size * 0.5;
			double linkY = (link < 1.0) ? cos(link * M_PI) * size * 0.3 : 0.0;
			double linkX = sin(link * M_PI) * size * 0.3 + offset;
			dist = sqrt(pow(delta.x - linkX, 2.0) + pow(delta.y - linkY, 2.0)) - size * 0.15;
			break;
		}
		case params::fakeLightsShapeWoven:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Woven/basket pattern
			double px = delta.x / size;
			double py = delta.y / size;
			double weaveX = fabs(sin(py * M_PI)) * size * 0.3;
			double weaveY = fabs(sin(px * M_PI)) * size * 0.3;
			double distX = fabs(delta.x - weaveX);
			double distY = fabs(delta.y - weaveY);
			dist = min(distX, distY) - size * 0.08 + fabs(delta.z) * 0.2;
			break;
		}
		case params::fakeLightsShapeNet:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Net/mesh pattern
			double px = delta.x / size;
			double py = delta.y / size;
			double gx = fabs(fmod(px, 1.0) - 0.5);
			double gy = fabs(fmod(py, 1.0) - 0.5);
			double lineWidth = 0.08;
			double distGrid = (gx < gy) ? gx : gy;
			dist = distGrid * size - size * lineWidth + fabs(delta.z) * 0.15;
			break;
		}
		case params::fakeLightsShapeCoil:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Spring/coil shape
			double t = delta.y / size * 2.0;
			double radius = size * 0.4;
			double coilX = radius * cos(t * M_PI * 2.0);
			double coilZ = radius * sin(t * M_PI * 2.0);
			dist = sqrt(pow(delta.x - coilX, 2.0) + pow(delta.z - coilZ, 2.0)) - size * 0.12;
			break;
		}
		case params::fakeLightsShapeVortex:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Vortex/swirl
			double r = sqrt(delta.x * delta.x + delta.z * delta.z);
			double angle = atan2(delta.z, delta.x);
			double spiralR = size * (1.0 - fabs(delta.y) / (size * 2.0));
			double spiralAngle = angle + delta.y * 2.0;
			double vorX = spiralR * cos(spiralAngle);
			double vorZ = spiralR * sin(spiralAngle);
			dist = sqrt(pow(delta.x - vorX, 2.0) + pow(delta.z - vorZ, 2.0)) + fabs(r - spiralR) * 0.3;
			break;
		}
		case params::fakeLightsShapeRipple:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Ripple/wave pattern
			double r = sqrt(delta.x * delta.x + delta.z * delta.z);
			double ripples = 4.0;
			double wave = sin(r / size * ripples * M_PI) * size * 0.2;
			dist = fabs(delta.y - wave) - size * 0.08;
			break;
		}
		case params::fakeLightsShapeShockwave:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Shockwave/explosion ring
			double r = sqrt(delta.x * delta.x + delta.z * delta.z);
			double t = delta.y / size;
			double ringR = size * (0.5 + t * 0.5);
			double shock = exp(-t * t * 2.0) * size * 0.3;
			dist = fabs(r - ringR) - shock + fabs(delta.y) * 0.1;
			break;
		}
		case params::fakeLightsShapeOrbital:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Planetary orbits
			double r = sqrt(delta.x * delta.x + delta.z * delta.z);
			double angle = atan2(delta.z, delta.x);
			double orbits = 3.0;
			double orbitR = size * (0.3 + 0.7 * (fmod(angle * orbits / (2.0 * M_PI) + 0.5, 1.0)));
			dist = fabs(r - orbitR) - size * 0.08 + fabs(delta.y) * 0.15;
			break;
		}
		case params::fakeLightsShapeNebula:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Nebula cloud
			double px = delta.x / size;
			double py = delta.y / size;
			double pz = delta.z / size;
			double noise = sin(px * 2.0) * sin(py * 3.0) * sin(pz * 2.5);
			noise += 0.5 * sin(px * 5.0 + py * 4.0) * sin(pz * 3.0 + px * 2.0);
			double r = delta.Length() / size;
			dist = (r - 1.0 - noise * 0.3) * size;
			break;
		}
		case params::fakeLightsShapeJulia3D:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// 3D Julia set (quaternion-style)
			double zx = delta.x / size;
			double zy = delta.y / size;
			double zz = delta.z / size;
			double cx = 0.3, cy = 0.5, cz = 0.2;
			double len = 0.0;
			for (int i = 0; i < 15; i++)
			{
				double zx2 = zx * zx - zy * zy - zz * zz + cx;
				double zy2 = 2.0 * zx * zy + cy;
				double zz2 = 2.0 * zx * zz + cz;
				zx = zx2; zy = zy2; zz = zz2;
				len = zx * zx + zy * zy + zz * zz;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeMandelbrot3D:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// 3D Mandelbrot (quaternion-style)
			double cx = delta.x / size;
			double cy = delta.y / size;
			double cz = delta.z / size;
			double zx = 0, zy = 0, zz = 0;
			double len = 0.0;
			for (int i = 0; i < 15; i++)
			{
				double zx2 = zx * zx - zy * zy - zz * zz + cx;
				double zy2 = 2.0 * zx * zy + cy;
				double zz2 = 2.0 * zx * zz + cz;
				zx = zx2; zy = zy2; zz = zz2;
				len = zx * zx + zy * zy + zz * zz;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeBurningShip:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Burning Ship fractal
			double cx = delta.x / size;
			double cy = delta.y / size;
			double zx = 0, zy = 0;
			double len = 0.0;
			for (int i = 0; i < 20; i++)
			{
				double zx2 = zx * zx - zy * zy + cx;
				double zy2 = 2.0 * fabs(zx * zy) + cy;
				zx = fabs(zx2); zy = fabs(zy2);
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeTricorn:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Tricorn/Mandelbar (conjugate)
			double cx = delta.x / size;
			double cy = delta.y / size;
			double zx = 0, zy = 0;
			double len = 0.0;
			for (int i = 0; i < 20; i++)
			{
				double zx2 = zx * zx - zy * zy + cx;
				double zy2 = -2.0 * zx * zy + cy;
				zx = zx2; zy = zy2;
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeMultibrot:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Multibrot (z^5 + c)
			double cx = delta.x / size;
			double cy = delta.y / size;
			double zx = 0, zy = 0;
			double len = 0.0;
			for (int i = 0; i < 20; i++)
			{
				double r = sqrt(zx * zx + zy * zy);
				double theta = atan2(zy, zx);
				double r5 = r * r * r * r * r;
				double zx2 = r5 * cos(5.0 * theta) + cx;
				double zy2 = r5 * sin(5.0 * theta) + cy;
				zx = zx2; zy = zy2;
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapePhoenix:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Phoenix double spiral
			double cx = delta.x / size;
			double cy = delta.y / size;
			double zx = 0, zy = 0;
			double wx = 0, wy = 0;
			double len = 0.0;
			for (int i = 0; i < 20; i++)
			{
				double zx2 = zx * zx - zy * zy + cx + cy * wx;
				double zy2 = 2.0 * zx * zy + cy * wy;
				wx = zx; wy = zy;
				zx = zx2; zy = zy2;
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeNewton:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Newton's method for z^3 - 1 = 0
			double zx = delta.x / size;
			double zy = delta.y / size;
			for (int i = 0; i < 10; i++)
			{
				double r2 = zx * zx + zy * zy;
				double r4 = r2 * r2;
				double denom = 3.0 * r4;
				double zx2 = (2.0 * zx * r2 + 1.0) / denom;
				double zy2 = 2.0 * zy / denom;
				zx = zx2; zy = zy2;
			}
			dist = fabs(zx * zy) * size;
			break;
		}
		case params::fakeLightsShapeNova:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Nova fractal
			double cx = delta.x / size;
			double cy = delta.y / size;
			double zx = 1.0, zy = 0.0;
			double len = 0.0;
			for (int i = 0; i < 15; i++)
			{
				double r2 = zx * zx + zy * zy;
				double r3 = r2 * sqrt(r2);
				double zx2 = zx - (zx * r2 - zx) / r3 + cx;
				double zy2 = zy - (zy * r2 + zy) / r3 + cy;
				zx = zx2; zy = zy2;
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeSpider:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Spider web fractal
			double cx = delta.x / size;
			double cy = delta.y / size;
			double zx = 0, zy = 0;
			double len = 0.0;
			for (int i = 0; i < 20; i++)
			{
				double zx2 = zx * zx - zy * zy + cx;
				double zy2 = 2.0 * zx * zy + cy;
				zx = zx2 / (1.0 + zx2); zy = zy2 / (1.0 + zy2);
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeDendrite:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Dendrite crystal fractal
			double cx = delta.x / size;
			double cy = delta.y / size;
			double zx = 0, zy = 0;
			double len = 0.0;
			for (int i = 0; i < 20; i++)
			{
				double zx2 = zx * zx - zy * zy + cx - 0.5;
				double zy2 = 2.0 * zx * zy + cy;
				zx = fabs(zx2); zy = fabs(zy2);
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeLorenz:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Lorenz attractor (point cloud)
			double x = delta.x / size;
			double y = delta.y / size;
			double z = delta.z / size;
			double t = 0.0;
			double minDist = 999.0;
			double px = 0.1, py = 0.0, pz = 0.0;
			for (int i = 0; i < 50; i++)
			{
				double dt = 0.01;
				double dx = 10.0 * (py - px) * dt;
				double dy = (px * (28.0 - pz) - py) * dt;
				double dz = (px * py - 8.0/3.0 * pz) * dt;
				px += dx; py += dy; pz += dz;
				double d = sqrt(pow(x - px, 2.0) + pow(y - py, 2.0) + pow(z - pz, 2.0));
				if (d < minDist) minDist = d;
			}
			dist = minDist * size - size * 0.05;
			break;
		}
		case params::fakeLightsShapeRossler:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Rossler attractor (point cloud)
			double x = delta.x / size;
			double y = delta.y / size;
			double z = delta.z / size;
			double minDist = 999.0;
			double px = 0.1, py = 0.0, pz = 0.0;
			for (int i = 0; i < 50; i++)
			{
				double dt = 0.05;
				double dx = (-py - pz) * dt;
				double dy = (px + 0.2 * py) * dt;
				double dz = (0.2 + pz * (px - 5.7)) * dt;
				px += dx; py += dy; pz += dz;
				double d = sqrt(pow(x - px, 2.0) + pow(y - py, 2.0) + pow(z - pz, 2.0));
				if (d < minDist) minDist = d;
			}
			dist = minDist * size - size * 0.05;
			break;
		}
		case params::fakeLightsShapePolyfold:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Polygon folding fractal
			double cx = delta.x / size;
			double cy = delta.y / size;
			double zx = cx, zy = cy;
			double len = 0.0;
			for (int i = 0; i < 15; i++)
			{
				double angle = atan2(zy, zx);
				double r = sqrt(zx * zx + zy * zy);
				angle = fmod(angle * 3.0, 2.0 * M_PI);
				zx = r * cos(angle) + cx;
				zy = r * sin(angle) + cy;
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeApollonian:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Apollonian sphere packing (simplified)
			double px = delta.x / size;
			double py = delta.y / size;
			double pz = delta.z / size;
			double d = 1.0;
			for (int i = 0; i < 3; i++)
			{
				double scale = pow(3.0, i);
				double sx = fmod(px * scale, 1.0) - 0.5;
				double sy = fmod(py * scale, 1.0) - 0.5;
				double sz = fmod(pz * scale, 1.0) - 0.5;
				double sd = sqrt(sx * sx + sy * sy + sz * sz) - 0.3 / scale;
				if (sd < d) d = sd;
			}
			dist = d * size;
			break;
		}
		case params::fakeLightsShapeKleinian:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Kleinian group limit set (simplified)
			double cx = delta.x / size;
			double cy = delta.y / size;
			double zx = cx, zy = cy;
			double len = 0.0;
			for (int i = 0; i < 15; i++)
			{
				if (zx * zx + zy * zy < 1.0)
				{
					double zx2 = zx + 1.0;
					double zy2 = zy;
					zx = zx2; zy = zy2;
				}
				else
				{
					double denom = zx * zx + zy * zy;
					double zx2 = zx / denom;
					double zy2 = -zy / denom;
					zx = zx2 + cx;
					zy = zy2 + cy;
				}
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeFibonacci:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Fibonacci spiral fractal
			double r = sqrt(delta.x * delta.x + delta.z * delta.z) / size;
			double angle = atan2(delta.z, delta.x);
			double phi = (1.0 + sqrt(5.0)) / 2.0;
			double spiral = fmod(angle + log(r + 0.1) * phi, 2.0 * M_PI);
			dist = fabs(sin(spiral * 5.0)) * size * 0.3 + fabs(delta.y) * 0.2;
			break;
		}
		case params::fakeLightsShapeCeltic:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Celtic knot fractal
			double cx = delta.x / size;
			double cy = delta.y / size;
			double zx = cx, zy = cy;
			double len = 0.0;
			for (int i = 0; i < 15; i++)
			{
				double zx2 = zx * zx - zy * zy + cx - 0.8;
				double zy2 = 2.0 * zx * zy + cy;
				zx = fabs(zx2) - 0.5; zy = fabs(zy2) - 0.5;
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeCrown:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Crown fractal
			double cx = delta.x / size;
			double cy = delta.y / size;
			double zx = 0, zy = 0;
			double len = 0.0;
			for (int i = 0; i < 20; i++)
			{
				double zx2 = zx * zx - zy * zy + cx;
				double zy2 = 2.0 * zx * fabs(zy) + cy;
				zx = zx2 - 0.5; zy = fabs(zy2) - 0.5;
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeCactus:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Cactus fractal
			double cx = delta.x / size;
			double cy = delta.y / size;
			double zx = cx, zy = cy;
			double len = 0.0;
			for (int i = 0; i < 15; i++)
			{
				double r = sqrt(zx * zx + zy * zy);
				double theta = atan2(zy, zx);
				double r4 = r * r * r * r;
				double zx2 = r4 * cos(4.0 * theta) + cx;
				double zy2 = r4 * sin(4.0 * theta) + cy;
				zx = fabs(zx2) - 0.3; zy = fabs(zy2) - 0.3;
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
		case params::fakeLightsShapeSiegelDisk:
		{
			delta = par->mRotFakeLightsRotation.RotateVector(delta);
			delta = ApplyShapeModifiers(delta, par);
			double size = par->fakeLightsOrbitTrapSize;
			// Siegel disk fractal
			double cx = delta.x / size;
			double cy = delta.y / size;
			double zx = cx, zy = cy;
			double lambda = 0.5 + 0.5 * sqrt(5.0);
			double len = 0.0;
			for (int i = 0; i < 20; i++)
			{
				double angle = atan2(zy, zx) * lambda;
				double r = sqrt(zx * zx + zy * zy);
				double zx2 = r * cos(angle) + cx * 0.1;
				double zy2 = r * sin(angle) + cy * 0.1;
				zx = zx2; zy = zy2;
				len = zx * zx + zy * zy;
				if (len > 4.0) break;
			}
			dist = sqrt(len) * size - size * 0.1;
			break;
		}
	}

	return dist / par->fakeLightsThickness;
}

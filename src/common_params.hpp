/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2017-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * data structure common for main parameters and fractal parameters
 */

#ifndef MANDELBULBER2_SRC_COMMON_PARAMS_HPP_
#define MANDELBULBER2_SRC_COMMON_PARAMS_HPP_

#include "algebra.hpp"

namespace params
{
enum enumFakeLightsShape
{
	fakeLightsShapePoint = 0,
	fakeLightsShapeLine = 1,
	fakeLightsShapeCircle = 2,
	fakeLightsShapeSquare = 3,
	fakeLightsShapeSphere = 4,
	fakeLightsShapeCube = 5,
	fakeLightsShapeTriangle = 6,
	fakeLightsShapeHexagon = 7,
	fakeLightsShapeTorus = 8,
	fakeLightsShapeCylinder = 9,
	fakeLightsShapeCone = 10,
	fakeLightsShapePyramid = 11,
	fakeLightsShapeOctahedron = 12,
	fakeLightsShapeEllipse = 13,
	fakeLightsShapeRectangle = 14,
	fakeLightsShapeCross = 15,
	fakeLightsShapeStar = 16,
	fakeLightsShapeDiamond = 17,
	fakeLightsShapeRing = 18,
	fakeLightsShapeCapsule = 19,
	fakeLightsShapePrism = 20,
	fakeLightsShapeTorusKnot = 21,
	fakeLightsShapeBoxFrame = 22,
	fakeLightsShapeConeInfinite = 23,
	fakeLightsShapeCylinderCap = 24,
	fakeLightsShapeSuperellipsoid = 25,
	fakeLightsShapePlane = 26,
	fakeLightsShapeDisc = 27,
	fakeLightsShapeGear = 28,
	fakeLightsShapeSpiral = 29,
	fakeLightsShapeHeart = 30,
	fakeLightsShapeCrescent = 31,
	fakeLightsShapeArrow = 32,
	fakeLightsShapeRoundedBox = 33,
	fakeLightsShapeStadium = 34,
	fakeLightsShapePolygon5 = 35,
	fakeLightsShapePolygon8 = 36,
	fakeLightsShapeTrefoilKnot = 37,
	fakeLightsShapeFigureEight = 38,
	fakeLightsShapeMobiusStrip = 39,
	fakeLightsShapeTorusSector = 40,
	fakeLightsShapeHelix = 41,
	fakeLightsShapeConeRounded = 42,
	fakeLightsShapeCylinderHollow = 43,
	fakeLightsShapeSphereHollow = 44,
	fakeLightsShapeTorusTwist = 45,
	fakeLightsShapeGrid = 46,
	fakeLightsShapeLattice = 47,
	fakeLightsShapeSponge = 48,
	fakeLightsShapeTree = 49,
	fakeLightsShapeKnot34 = 50,
	fakeLightsShapeSpiral3D = 51,
	fakeLightsShapeNoise = 52,
	fakeLightsShapeVoronoi = 53,
	fakeLightsShapeMandelbrot2D = 54,
	fakeLightsShapeJulia2D = 55,
	fakeLightsShapeSierpinski = 56,
	fakeLightsShapeKoch = 57,
	fakeLightsShapeDragon = 58,
	fakeLightsShapeHilbert = 59,
	fakeLightsShapeGyroid = 60,
	fakeLightsShapeSchwarzP = 61,
	fakeLightsShapeSchwarzD = 62,
	fakeLightsShapeNeovius = 63,
	fakeLightsShapeLabyrinth = 64,
	fakeLightsShapeFiber = 65,
	fakeLightsShapeAstroid = 66,
	fakeLightsShapeDeltoid = 67,
	fakeLightsShapeLemniscate = 68,
	fakeLightsShapeLimacon = 69,
	fakeLightsShapeSphericalHarmonics = 70,
	fakeLightsShapeSuperformula = 71,
	fakeLightsShapeFern = 72,
	fakeLightsShapeShell = 73,
	fakeLightsShapeCoral = 74,
	fakeLightsShapeCrystal = 75,
	fakeLightsShapeHoneycomb = 76,
	fakeLightsShapeChain = 77,
	fakeLightsShapeWoven = 78,
	fakeLightsShapeNet = 79,
	fakeLightsShapeCoil = 80,
	fakeLightsShapeVortex = 81,
	fakeLightsShapeRipple = 82,
	fakeLightsShapeShockwave = 83,
	fakeLightsShapeOrbital = 84,
	fakeLightsShapeNebula = 85,
	fakeLightsShapeJulia3D = 86,
	fakeLightsShapeMandelbrot3D = 87,
	fakeLightsShapeBurningShip = 88,
	fakeLightsShapeTricorn = 89,
	fakeLightsShapeMultibrot = 90,
	fakeLightsShapePhoenix = 91,
	fakeLightsShapeNewton = 92,
	fakeLightsShapeNova = 93,
	fakeLightsShapeSpider = 94,
	fakeLightsShapeDendrite = 95,
	fakeLightsShapeLorenz = 96,
	fakeLightsShapeRossler = 97,
	fakeLightsShapePolyfold = 98,
	fakeLightsShapeApollonian = 99,
	fakeLightsShapeKleinian = 100,
	fakeLightsShapeFibonacci = 101,
	fakeLightsShapeCeltic = 102,
	fakeLightsShapeCrown = 103,
	fakeLightsShapeCactus = 104,
	fakeLightsShapeSiegelDisk = 105
};

enum enumFakeLightsPositionMode
{
	fakeLightsPositionWorld = 0,
	fakeLightsPositionCamera = 1,
	fakeLightsPositionTarget = 2,
	fakeLightsPositionFractalCenter = 3,
	fakeLightsPositionPathCircle = 4,
	fakeLightsPositionPathSpiral = 5,
	fakeLightsPositionOrbitTarget = 6
};

enum enumFakeLightsDecay
{
	fakeLightsDecay1R2 = 0,
	fakeLightsDecay1R = 1,
	fakeLightsDecay1R3 = 2,
	fakeLightsDecayLinear = 3,
	fakeLightsDecayExp = 4
};
};

struct sFakeLightsModeParams
{
	CVector3 offset = CVector3(0.0, 0.0, 0.0);
	double scale = 1.0;
	CVector3 rotation = CVector3(0.0, 0.0, 0.0);
	double pathRadius = 0.0;
};

struct sFractalFoldings
{
	double boxLimit; // parameters of TGlad's folding
	double boxValue;
	double sphericalOuter;
	double sphericalInner;
	bool boxEnable;
	bool sphericalEnable;
};

struct sCommonParams
{
	bool iterThreshMode;
	bool fakeLightsRelativeCenter;
	bool fakeLightsColor2Enabled;
	bool fakeLightsColor3Enabled;

	int fakeLightsMaxIter;
	int fakeLightsMinIter;
	int fakeLightsCenterIteration;

	params::enumFakeLightsShape fakeLightsOrbitTrapShape;

	double fakeLightsOrbitTrapSize;
	double fakeLightsThickness;
	double linearDEOffset;

	CVector3 fakeLightsOrbitTrap;
	CVector3 fakeLightsRotation;
	CVector3 fractalPosition;
	bool fakeLightsMultiCenterEnabled = false;
	CVector3 fakeLightsMultiCenter[24];
	double fakeLightsMultiCenterWeight[24];
	params::enumFakeLightsDecay fakeLightsDecayFunction = params::fakeLightsDecay1R2;
	CVector3 fractalRotation;
	CVector3 repeat;
	CRotationMatrix mRotFractalRotation;
	CVector3 positionIterStart;
	CVector3 positionIterStop;
	CVector3 rotationIterStart;
	CVector3 rotationIterStop;
	CVector3 repeatIterStart;
	CVector3 repeatIterStop;
	CRotationMatrix mRotFakeLightsRotation;

	sFractalFoldings foldings;

	// V2: Positioning mode (added at END per PROTOCOL)
	params::enumFakeLightsPositionMode fakeLightsPositionMode = params::fakeLightsPositionWorld;

	// V2: Per-mode fine-tuning parameters
	sFakeLightsModeParams fakeLightsModes[7];

	// V2: Universal shape modifiers (applied to all orbit trap shapes)
	double fakeLightsShapeTwist = 0.0;
	double fakeLightsShapeBend = 0.0;
	double fakeLightsShapeTaper = 0.0;
	int fakeLightsShapeFoldSymmetry = 0;

	// V2: Additional modifiers
	double fakeLightsShapeRepeatX = 0.0;
	double fakeLightsShapeRepeatY = 0.0;
	double fakeLightsShapeRepeatZ = 0.0;
	double fakeLightsShapeWobbleAmplitude = 0.0;
	double fakeLightsShapeWobbleFrequency = 0.0;
	double fakeLightsShapeChamfer = 0.0;

	// V2: Shape transforms
	double fakeLightsShapeScaleX = 1.0;
	double fakeLightsShapeScaleY = 1.0;
	double fakeLightsShapeScaleZ = 1.0;
	bool fakeLightsShapeMirrorX = false;
	bool fakeLightsShapeMirrorY = false;
	bool fakeLightsShapeMirrorZ = false;
	double fakeLightsShapeInflate = 0.0;
	double fakeLightsShapeLineLength = 0.0;
	double fakeLightsShapeTubeRadius = 0.0;
	double fakeLightsShapeLineThickness = 1.0;
	double fakeLightsShapeFalloff = 1.0;
	double fakeLightsShapeMaskRadius = 0.0;
	double fakeLightsShapeMaskSoftness = 0.1;

	// V2: New modifiers (spiral, wave)
	double fakeLightsShapeSpiral = 0.0;
	double fakeLightsShapeWaveX = 0.0;
	double fakeLightsShapeWaveY = 0.0;
	double fakeLightsShapeWaveZ = 0.0;
	double fakeLightsShapeWaveFrequency = 1.0;

	// V2: Smooth mode transition speed (0 = instant)
	double fakeLightsTransitionSpeed = 0.0;

	// V2: Transition interpolation state
	params::enumFakeLightsPositionMode fakeLightsTransitionSourceMode = params::fakeLightsPositionWorld;
	double fakeLightsTransitionBlend = 1.0;
	bool fakeLightsOrbitTrapPreTransformed = false;
};

#endif /* MANDELBULBER2_SRC_COMMON_PARAMS_HPP_ */

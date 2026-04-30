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
 * Single Trap Lights — multi-layer spatial light system
 */

#ifndef MANDELBULBER2_SRC_SINGLE_TRAP_LIGHTS_HPP_
#define MANDELBULBER2_SRC_SINGLE_TRAP_LIGHTS_HPP_

#include "algebra.hpp"
#include "color_structures.hpp"

namespace params
{
enum enumSingleTrapLightShape
{
	singleTrapLightShapePoint = 0,
	singleTrapLightShapeLine = 1,
	singleTrapLightShapeCircle = 2,
	singleTrapLightShapeSquare = 3,
	singleTrapLightShapeSphere = 4,
	singleTrapLightShapeCube = 5,
	singleTrapLightShapeTorus = 6,
	singleTrapLightShapeCapsule = 7,
	singleTrapLightShapeRing = 8,
	singleTrapLightShapeEllipse = 9,
	singleTrapLightShapeCross = 10,
	singleTrapLightShapeCylinder = 11,
	singleTrapLightShapePlane = 12,
	singleTrapLightShapeDisc = 13,
	singleTrapLightShapeCone = 14,
	singleTrapLightShapeHexagon = 15,
	singleTrapLightShapeTriangle = 16,
	singleTrapLightShapeRoundedBox = 17,
	singleTrapLightShapeDiamond = 18,
	singleTrapLightShapeHollowSphere = 19,
	singleTrapLightShapeHollowCube = 20,
	singleTrapLightShapeEllipsoid = 21,
	singleTrapLightShapeSuperellipsoid = 22,
	singleTrapLightShapeStar5 = 23,
	singleTrapLightShapeStar6 = 24,
	singleTrapLightShapeGear = 25,
	singleTrapLightShapeHeart = 26
};

enum enumSingleTrapLightColoringMode
{
	singleTrapLightColoringSolid = 0,
	singleTrapLightColoringDistance = 1,
	singleTrapLightColoringOrbitTrap = 2
};

enum enumSingleTrapLightFalloffType
{
	singleTrapLightFalloffGaussian = 0,
	singleTrapLightFalloffInverseSquare = 1,
	singleTrapLightFalloffLinear = 2,
	singleTrapLightFalloffExponential = 3,
	singleTrapLightFalloffSmoothstep = 4
};

enum enumSingleTrapLightsCombineMode
{
	singleTrapLightsCombineAdd = 0,
	singleTrapLightsCombineMax = 1
};
} // namespace params

const int MAX_SINGLE_TRAP_LIGHT_LAYERS = 20;

struct sSingleTrapLightLayer
{
	bool enabled;
	params::enumSingleTrapLightShape shape;
	CVector3 position;
	double size;
	double size2;
	double thickness;
	CVector3 rotation;
	CRotationMatrix mRotRotation;
	double intensity;
	sRGBFloat color;
	sRGBFloat gradientColor;
	// Fine-tuning parameters
	double visibility;
	double maxDistance;
	double sharpening;
	double blur;
	double solidIntensity;
	double softness;
	double relativeSize;
	bool preTransformed;
	int positionMode;
	params::enumSingleTrapLightColoringMode coloringMode;
	params::enumSingleTrapLightFalloffType falloffType;
	double edgeSoftness;
	// Animation parameters
	double animOrbitRadius;
	double animOrbitSpeed;
	double animPulsateSpeed;
	double animPulsateAmount;

	sSingleTrapLightLayer()
			: enabled(false),
				shape(params::singleTrapLightShapePoint),
				position(CVector3(0.0, 0.0, 0.0)),
				size(1.0),
				size2(0.25),
				thickness(1.0),
				rotation(CVector3(0.0, 0.0, 0.0)),
				intensity(1.0),
				color(sRGBFloat(1.0f, 1.0f, 1.0f)),
				gradientColor(sRGBFloat(1.0f, 1.0f, 1.0f)),
				visibility(1.0),
				maxDistance(5.0),
				sharpening(1.0),
				blur(0.0),
				solidIntensity(1.0),
				softness(0.0),
				relativeSize(1.0),
				preTransformed(false),
				positionMode(0),
				coloringMode(params::singleTrapLightColoringSolid),
				falloffType(params::singleTrapLightFalloffGaussian),
				edgeSoftness(0.0),
				animOrbitRadius(0.0),
				animOrbitSpeed(0.0),
				animPulsateSpeed(0.0),
				animPulsateAmount(0.0)
	{
	}

	void UpdateRotationMatrix()
	{
		mRotRotation.SetRotation2(rotation * M_PI / 180.0);
	}
};

struct sSingleTrapLights
{
	bool enabled;
	int activeLayerCount;
	/** 0 = all enabled layers; 1..MAX = only that layer index (same numbering as UI). */
	int soloLayerIndex;
	params::enumSingleTrapLightsCombineMode combineMode;
	sSingleTrapLightLayer layers[MAX_SINGLE_TRAP_LIGHT_LAYERS];

	sSingleTrapLights()
			: enabled(false),
				activeLayerCount(1),
				soloLayerIndex(0),
				combineMode(params::singleTrapLightsCombineAdd)
	{
	}
};

// Core functions
double SingleTrapLightDistance(CVector3 point, const sSingleTrapLightLayer &layer);
CVector3 SingleTrapLightNormal(CVector3 point, const sSingleTrapLightLayer &layer, double delta);

#endif /* MANDELBULBER2_SRC_SINGLE_TRAP_LIGHTS_HPP_ */

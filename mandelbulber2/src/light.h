/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2020-22 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * TODO: description
 */

#ifndef MANDELBULBER2_SRC_LIGHT_H_
#define MANDELBULBER2_SRC_LIGHT_H_

#include <memory>

#include <QString>
#include <QStringList>

#include "algebra.hpp"
#include "color_structures.hpp"
#include "texture.hpp"

// forward declarations
class cParameterContainer;
class cPrimitives;

class cLight
{
public:
	cLight();
	cLight(int _id, const std::shared_ptr<cParameterContainer> lightParam, bool loadTextures,
		bool quiet, bool useNetRender);
	//	~cLight();
	//	cLight(cLight &&) = default;
	//	cLight(const cLight &) = default;
	//	cLight

	void setParameters(int _id, const std::shared_ptr<cParameterContainer> lightParam,
		bool loadTextures, bool quiet, bool useNetRender);

	static QString Name(const QString &name, int lightId)
	{
		return QString("light%1_").arg(lightId) + name;
	}

	inline float Decay(float distance) const
	{
		if (decayFunction == lightDecaySmooth)
			return (1.0f + distance) * (1.0f + distance);  // smooth: 1/(1+d)² — no singularity at d=0
		if (decayFunction == lightDecayPhysical)
			return distance * distance + 1.0f;  // physical: 1/(d²+1) — inverse-square without d=0 singularity
		return pow(distance, float(decayFunction + 1));
	}
	float CalculateCone(CVector3 point, const CVector3 &lightVector, sRGBFloat &outColor) const;
	CVector3 CalculateLightVector(const CVector3 &point, double delta, double resolution,
		double viewDistanceMax, double &outDistance, const class cPrimitives *primitives = nullptr) const;
	CVector3 CalculateBeam(const CVector3 &point1, const CVector3 &point2) const;

	static const QStringList paramsList;

	enum enumLightType
	{
		lightDirectional = 0,
		lightPoint = 1,
		lightConical = 2,
		lightProjection = 3,
		lightBeam = 4,
		lightPrimitive = 5
	};

	enum enumLightDecayFunction
	{
		lightDecay1R = 0,
		lightDecay1R2 = 1,
		lightDecay1R3 = 2,
		lightDecaySmooth = 3,
		lightDecayPhysical = 4
	};

	bool enabled = false;
	bool castShadows = false;
	bool penetrating = false;
	bool relativePosition = false;
	bool repeatTexture = false;
	bool useTargetPoint = false;
	bool volumetric = false;

	// === AUX LIGHTS UPGRADE ===
	bool useColorTemperature = false;
	float colorTemperature = 5500.0f;

	enum enumShadowType { shadowHard = 0, shadowPCF = 1, shadowPCSS = 2 };
	enumShadowType shadowType = shadowHard;
	int shadowSamples = 16;
	float shadowSoftness = 0.5f;
	float shadowBias = 0.001f;
	bool useShadowNoise = false;

	bool affectDiffuse = true;
	bool affectSpecular = true;
	bool affectVolumetric = true;
	int lightGroup = 0;

	bool useAreaLight = false;
	float areaLightRadius = 0.1f;
	int areaLightSamples = 4;

	float angularDiameter = 0.53f;
	bool useAngularSize = false;
	float atmosphericDensity = 0.0f;
	float atmosphericScatteringIntensity = 1.0f;
	sRGBFloat atmosphericColor = sRGBFloat(0.55f, 0.75f, 1.0f);

	float penumbraAngle = 5.0f;
	float penumbraSoftness = 0.5f;

	float projectionSoftEdge = 0.1f;
	float projectionFeather = 0.0f;
	int projectionBlendMode = 0;

	float beamLength = 100.0f;
	float beamFalloff = 1.0f;
	int beamVolumeSamples = 16;
	bool beamUseNoise = false;
	float beamNoiseScale = 1.0f;
	float beamNoiseStrength = 0.3f;

	int id = -1;
	int primitiveId = -1;

	float coneAngle = 0.0f;
	float coneSoftAngle = 0.0f;
	float intensity = 0.0f;
	float visibility = 0.0f;
	float volumetricVisibility = 0.0f;
	float size = 0.0f;
	float softShadowCone = 0.0f;
	float contourSharpness = 0.0f;
	float coneRatio = 0.0;
	float coneSoftRatio = 0.0;
	float projectionHorizontalRatio = 0.0;
	float projectionVerticalRatio = 0.0;

	CVector3 position;
	CVector3 rotation;
	CVector3 target;
	CVector3 lightDirection;
	CVector3 lightTopVector;
	CVector3 lightRightVector;

	sRGBFloat color;

	CRotationMatrix rotMatrix;

	enumLightType type = lightDirectional;
	enumLightDecayFunction decayFunction = lightDecay1R;

	cTexture colorTexture;
};

#endif /* MANDELBULBER2_SRC_LIGHT_H_ */

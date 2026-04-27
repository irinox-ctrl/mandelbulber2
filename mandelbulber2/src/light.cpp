/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2020-23 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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

#include "light.h"

#include "camera_target.hpp"
#include "common_math.h"
#include "parameters.hpp"
#include "primitives.h"
#include "primitive.hpp"

cLight::cLight()
{
	// nothing to construct
}

cLight::cLight(int _id, const std::shared_ptr<cParameterContainer> lightParam, bool loadTextures,
	bool quiet, bool useNetRender)
{
	setParameters(_id, lightParam, loadTextures, quiet, useNetRender);
}

// cLight::~cLight() = default;

// this static list will be use to optimize usage of material parameters
const QStringList cLight::paramsList = {"is_defined", "enabled", "cast_shadows", "penetrating",
	"relative_position", "volumetric", "cone_angle", "cone_soft_angle", "intensity", "visibility",
	"volumetric_visibility", "size", "soft_shadow_cone", "contour_sharpness", "position", "rotation",
	"use_target_point", "target", "alpha", "beta", "color", "type", "decayFunction", "file_texture",
	"repeat_texture", "projection_horizonal_angle", "projection_vertical_angle", "name", "primitive_id",
	"use_color_temperature", "color_temperature",
	"shadow_type", "shadow_samples", "shadow_softness", "shadow_bias", "use_shadow_noise",
	"affect_diffuse", "affect_specular", "affect_volumetric", "light_group",
	"use_area_light", "area_light_radius", "area_light_samples",
	"angular_diameter", "use_angular_size", "atmospheric_density",
	"atmospheric_scattering_intensity", "atmospheric_color",
	"penumbra_angle", "penumbra_softness",
	"projection_soft_edge", "projection_feather", "projection_blend_mode",
	"beam_length", "beam_falloff", "beam_volume_samples",
	"beam_use_noise", "beam_noise_scale", "beam_noise_strength"};

void cLight::setParameters(int _id, const std::shared_ptr<cParameterContainer> lightParam,
	bool loadTextures, bool quiet, bool useNetRender)
{
	id = _id;

	int frameNo = lightParam->Get<int>("frame_no");

	enabled = lightParam->Get<bool>(Name("enabled", id));
	type = enumLightType(lightParam->Get<int>(Name("type", id)));
	primitiveId = lightParam->Get<int>(Name("primitive_id", id));
	castShadows = lightParam->Get<bool>(Name("cast_shadows", id));
	penetrating = lightParam->Get<bool>(Name("penetrating", id));
	relativePosition = lightParam->Get<bool>(Name("relative_position", id));
	repeatTexture = lightParam->Get<bool>(Name("repeat_texture", id));
	volumetric = lightParam->Get<bool>(Name("volumetric", id));
	useTargetPoint = lightParam->Get<bool>(Name("use_target_point", id));

	double allLightsIntensity = lightParam->Get<double>("all_lights_intensity");
	double allLightsVisibility = lightParam->Get<double>("all_lights_visibility");
	double allLightsSize = lightParam->Get<double>("all_lights_size");

	coneAngle = lightParam->Get<double>(Name("cone_angle", id)) / 180.0 * M_PI;
	coneSoftAngle = lightParam->Get<double>(Name("cone_soft_angle", id)) / 180.0 * M_PI;
	intensity = lightParam->Get<double>(Name("intensity", id)) * allLightsIntensity;
	visibility = lightParam->Get<double>(Name("visibility", id)) * allLightsVisibility;
	volumetricVisibility = lightParam->Get<double>(Name("volumetric_visibility", id));
	size = lightParam->Get<double>(Name("size", id)) * allLightsSize;
	softShadowCone = lightParam->Get<double>(Name("soft_shadow_cone", id)) / 180.0 * M_PI;
	contourSharpness = lightParam->Get<double>(Name("contour_sharpness", id));

	rotation = lightParam->Get<CVector3>(Name("rotation", id)) / 180.0 * M_PI;

	if (type == lightDirectional)
	{
		rotation *= CVector3(1.0, -1.0, 1.0);
	}
	else
	{
		rotation *= CVector3(-1.0, 1.0, 1.0);
	}

	rotMatrix.SetRotation(rotation);

	if (relativePosition)
	{
		CVector3 camera = lightParam->Get<CVector3>("camera");
		CVector3 camTarget = lightParam->Get<CVector3>("target");
		CVector3 top = lightParam->Get<CVector3>("camera_top");
		cCameraTarget cameraTarget(camera, camTarget, top);

		// qDebug() << camera.Debug() << target.Debug() << top.Debug();

		CVector3 deltaPosition = lightParam->Get<CVector3>(Name("position", id));
		CVector3 deltaPositionRotated = cameraTarget.GetForwardVector() * deltaPosition.z
																		+ cameraTarget.GetTopVector() * deltaPosition.y
																		+ cameraTarget.GetRightVector() * deltaPosition.x;
		position = camera + deltaPositionRotated;

		CVector3 deltaTarget = lightParam->Get<CVector3>(Name("target", id));
		CVector3 deltaTargetRotated = cameraTarget.GetForwardVector() * deltaTarget.z
																	+ cameraTarget.GetTopVector() * deltaTarget.y
																	+ cameraTarget.GetRightVector() * deltaTarget.x;

		target = camera + deltaTargetRotated;

		if (useTargetPoint)
		{
			lightDirection = position - target;
			if (lightDirection.Length() > 0)
				lightDirection.Normalize();
			else
				lightDirection = (-1.0) * cameraTarget.GetForwardVector();

			lightTopVector = cameraTarget.GetTopVector();

			lightRightVector = lightDirection.Cross(lightTopVector);
			lightRightVector.Normalize();

			lightTopVector = lightDirection.Cross(lightRightVector);
			lightTopVector.Normalize();
		}
		else
		{
			lightDirection = (-1.0) * cameraTarget.GetForwardVector();
			lightDirection =
				lightDirection.RotateAroundVectorByAngle(cameraTarget.GetForwardVector(), rotation.z);
			lightDirection =
				lightDirection.RotateAroundVectorByAngle(cameraTarget.GetRightVector(), rotation.y);
			lightDirection =
				lightDirection.RotateAroundVectorByAngle(cameraTarget.GetTopVector(), rotation.x);

			lightTopVector = cameraTarget.GetTopVector();
			lightTopVector =
				lightTopVector.RotateAroundVectorByAngle(cameraTarget.GetForwardVector(), rotation.z);
			lightTopVector =
				lightTopVector.RotateAroundVectorByAngle(cameraTarget.GetRightVector(), rotation.y);
			lightTopVector =
				lightTopVector.RotateAroundVectorByAngle(cameraTarget.GetTopVector(), rotation.x);
		}

		lightRightVector = lightDirection.Cross(lightTopVector);
		lightRightVector.Normalize();
	}
	else
	{
		position = lightParam->Get<CVector3>(Name("position", id));
		target = lightParam->Get<CVector3>(Name("target", id));

		if (useTargetPoint)
		{
			target = lightParam->Get<CVector3>(Name("target", id));
			lightDirection = position - target;
			if (lightDirection.Length() > 0)
				lightDirection.Normalize();
			else
				lightDirection = CVector3(1.0, 0.0, 0.0);

			lightTopVector = CVector3(0.0, 0.0, 1.0);

			lightRightVector = lightDirection.Cross(lightTopVector);
			lightRightVector.Normalize();

			lightTopVector = lightDirection.Cross(lightRightVector);
			lightTopVector.Normalize();
		}
		else
		{
			lightDirection = rotMatrix.RotateVector(CVector3(0.0, -1.0, 0.0));
			lightTopVector = rotMatrix.RotateVector(CVector3(0.0, 0.0, 1.0));
			lightRightVector = rotMatrix.RotateVector(CVector3(-1.0, 0.0, 0.0));
		}
	}

	color = toRGBFloat(lightParam->Get<sRGB>(Name("color", id)));

	decayFunction = enumLightDecayFunction(lightParam->Get<int>(Name("decayFunction", id)));

	// === AUX LIGHTS UPGRADE ===
	useColorTemperature = lightParam->Get<bool>(Name("use_color_temperature", id));
	colorTemperature = lightParam->Get<double>(Name("color_temperature", id));
	shadowType = enumShadowType(lightParam->Get<int>(Name("shadow_type", id)));
	shadowSamples = lightParam->Get<int>(Name("shadow_samples", id));
	shadowSoftness = lightParam->Get<double>(Name("shadow_softness", id));
	shadowBias = lightParam->Get<double>(Name("shadow_bias", id));
	useShadowNoise = lightParam->Get<bool>(Name("use_shadow_noise", id));
	affectDiffuse = lightParam->Get<bool>(Name("affect_diffuse", id));
	affectSpecular = lightParam->Get<bool>(Name("affect_specular", id));
	affectVolumetric = lightParam->Get<bool>(Name("affect_volumetric", id));
	lightGroup = lightParam->Get<int>(Name("light_group", id));
	useAreaLight = lightParam->Get<bool>(Name("use_area_light", id));
	areaLightRadius = lightParam->Get<double>(Name("area_light_radius", id));
	areaLightSamples = lightParam->Get<int>(Name("area_light_samples", id));
	angularDiameter = lightParam->Get<double>(Name("angular_diameter", id));
	useAngularSize = lightParam->Get<bool>(Name("use_angular_size", id));
	atmosphericDensity = lightParam->Get<double>(Name("atmospheric_density", id));
	atmosphericScatteringIntensity = lightParam->Get<double>(Name("atmospheric_scattering_intensity", id));
	atmosphericColor = toRGBFloat(lightParam->Get<sRGB>(Name("atmospheric_color", id)));
	penumbraAngle = lightParam->Get<double>(Name("penumbra_angle", id));
	penumbraSoftness = lightParam->Get<double>(Name("penumbra_softness", id));
	projectionSoftEdge = lightParam->Get<double>(Name("projection_soft_edge", id));
	projectionFeather = lightParam->Get<double>(Name("projection_feather", id));
	projectionBlendMode = lightParam->Get<int>(Name("projection_blend_mode", id));
	beamLength = lightParam->Get<double>(Name("beam_length", id));
	beamFalloff = lightParam->Get<double>(Name("beam_falloff", id));
	beamVolumeSamples = lightParam->Get<int>(Name("beam_volume_samples", id));
	beamUseNoise = lightParam->Get<bool>(Name("beam_use_noise", id));
	beamNoiseScale = lightParam->Get<double>(Name("beam_noise_scale", id));
	beamNoiseStrength = lightParam->Get<double>(Name("beam_noise_strength", id));

	coneRatio = sin(coneAngle);
	coneSoftRatio = sin(coneSoftAngle + coneAngle);
	projectionHorizontalRatio =
		tan(lightParam->Get<double>(Name("projection_horizonal_angle", id)) / 360.0 * M_PI) * 2.0;
	projectionVerticalRatio =
		tan(lightParam->Get<double>(Name("projection_vertical_angle", id)) / 360.0 * M_PI) * 2.0;

	if (loadTextures)
	{
		if (type == lightProjection)
		{
			colorTexture = cTexture(lightParam->Get<QString>(Name("file_texture", id)),
				cTexture::doNotUseMipmaps, frameNo, quiet, useNetRender);
		}
	}
}

float cLight::CalculateCone(CVector3 point, const CVector3 &lightVector, sRGBFloat &outColor) const
{
	outColor = {1.0, 1.0, 1.0};
	float intens = 1.0;

	if (type == lightConical)
	{
		if ((point - position).Dot(lightDirection) > 0.0)
		{
			intens = 0.0;
		}
		else
		{
			double tipSize = size * 0.5;
			double distanceToAxis = fabs((point - position).Cross(lightDirection)).Length();
			double cone = (point - position).Length();
			double cone1 = cone * coneRatio;
			double cone2 = cone * coneSoftRatio;
			if (distanceToAxis < tipSize + cone1)
			{
				intens = 1.0;
			}
			else if (distanceToAxis < tipSize + cone2)
			{
				intens = (tipSize + cone2 - distanceToAxis) / (cone2 - cone1);
			}
			else
			{
				intens = 0.0;
			}

			intens = intens * (tipSize * tipSize) / ((tipSize + cone1) * (tipSize + cone1));
		}
	}
	else if (type == lightProjection)
	{
		double axiality = lightVector.Dot(lightDirection);
		if (axiality > 0.0 && projectionHorizontalRatio > 0.0 && projectionVerticalRatio > 0.0)
		{
			double texX = lightRightVector.Dot(lightVector) / projectionHorizontalRatio / axiality + 0.5;
			double texY = lightTopVector.Dot(lightVector) / projectionVerticalRatio / axiality + 0.5;

			if (repeatTexture || (texX > 0.0 && texX < 1.0 && texY > 0.0 && texY < 1.0))
			{
				sRGBFloat pixel = colorTexture.Pixel(CVector2<float>(texX, texY), 0.0);
				outColor = pixel;
				intens = 1.0;
			}
			else
			{
				outColor = {0.0, 0.0, 0.0};
				intens = 0.0;
			}
		}
		else
		{
			outColor = {0.0, 0.0, 0.0};
			intens = 0.0;
		}
	}
	return intens;
}

CVector3 cLight::CalculateLightVector(const CVector3 &point, double delta, double resolution,
	double viewDistanceMax, double &outDistance, const cPrimitives *primitives) const
{
	CVector3 lightVector;
	if (type == cLight::lightDirectional)
	{
		lightVector = lightDirection;
		if (penetrating)
		{
			outDistance = delta / resolution;
		}
		else
		{
			outDistance = viewDistanceMax;
		}
	}
	else if (type == cLight::lightPrimitive && primitives != nullptr && primitiveId >= 0)
	{
		// Find the primitive with matching objectId
		const sPrimitiveBasic *primitive = nullptr;
		for (int i = 0; i < primitives->GetNumberOfPrimivives(); i++)
		{
			if (primitives->GetPrimitive(i)->objectId == primitiveId)
			{
				primitive = primitives->GetPrimitive(i).get();
				break;
			}
		}

		if (primitive != nullptr && primitive->enable)
		{
			// Sphere trace to find closest point on primitive surface
			CVector3 primitiveCenter = primitive->position;
			CVector3 direction = primitiveCenter - point;
			double totalDistance = direction.Length();

			if (totalDistance > 0.0)
			{
				direction.Normalize();

				// Sphere trace from point towards primitive
				CVector3 currentPoint = point;
				double marchDistance = 0.0;
				const int maxSteps = 64;
				const double minDistance = delta * 0.1; // Close enough to surface

				for (int step = 0; step < maxSteps && marchDistance < totalDistance * 2.0; step++)
				{
					double dist = primitive->PrimitiveDistance(currentPoint);

					if (fabs(dist) < minDistance)
					{
						// Found surface point
						lightVector = currentPoint - point;
						outDistance = lightVector.Length();
						if (outDistance > 0.0)
							lightVector.Normalize();
						else
							lightVector = direction;
						return lightVector;
					}

					// March towards surface (from inside or outside)
					double stepSize = fabs(dist) * 0.5; // Conservative step
					currentPoint = currentPoint + direction * stepSize;
					marchDistance += stepSize;
				}
			}

			// Fallback: use primitive center
			lightVector = primitiveCenter - point;
			outDistance = lightVector.Length();
			if (outDistance > 0.0)
				lightVector.Normalize();
			else
				lightVector = CVector3(0.0, 1.0, 0.0);
		}
		else
		{
			// Primitive not found or disabled, fallback to default
			lightVector = CVector3(0.0, 1.0, 0.0);
			outDistance = viewDistanceMax;
		}
	}
	else
	{
		CVector3 d = CalculateBeam(position, target) - point;
		lightVector = d;
		lightVector.Normalize();
		outDistance = d.Length();
	}

	return lightVector;
}

CVector3 cLight::CalculateBeam(const CVector3 &point1, const CVector3 &point2) const
{
	if (type == cLight::lightBeam)
	{
		CVector3 direction = point2 - point1;
		return point1 + direction * Random(10000) / 10000.0;
	}
	else
	{
		return point1;
	}
}

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
	"volumetric_visibility", "size", "soft_shadow_cone", "contour_sharpness", "beam_radius",
	"beam_soft_edge", "beam_fade_in", "beam_fade_out", "position", "rotation",
	"use_target_point", "target", "alpha", "beta", "color", "type", "decayFunction", "file_texture",
	"file_texture_alpha", "repeat_texture", "projection_horizonal_angle", "projection_vertical_angle",
	"projection_soft_edge", "projection_intensity", "projection_use_as_mask", "projection_texture_offset_x",
	"projection_texture_offset_y", "projection_texture_offset_z",
	"projection_texture_scale_x", "projection_texture_scale_y", "projection_texture_scale_z",
	"projection_texture_rotation_x", "projection_texture_rotation_y", "projection_texture_rotation_z",
	"projection_repeat_mode", "projection_use_alpha_as_mask", "projection_use_texture_alpha_as_mask",
	"projection_invert_alpha_mask",
	"projection_blend_mode",
	"alpha_texture_offset_x", "alpha_texture_offset_y", "alpha_texture_scale_x", "alpha_texture_scale_y",
	"alpha_texture_rotation_z", "alpha_texture_repeat_mode", "alpha_texture_soft_edge",
	"snap_to_surface", "surface_offset", "name", "orbit_distance", "orbit_yaw", "orbit_pitch",
	"auto_intensity", "auto_intensity_factor"};

void cLight::setParameters(int _id, const std::shared_ptr<cParameterContainer> lightParam,
	bool loadTextures, bool quiet, bool useNetRender)
{
	id = _id;

	int frameNo = lightParam->Get<int>("frame_no");

	enabled = lightParam->Get<bool>(Name("enabled", id));
	type = enumLightType(lightParam->Get<int>(Name("type", id)));
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
	beamRadius = lightParam->Get<double>(Name("beam_radius", id));
	beamSoftEdge = lightParam->Get<double>(Name("beam_soft_edge", id));
	beamFadeIn = lightParam->Get<double>(Name("beam_fade_in", id));
	beamFadeOut = lightParam->Get<double>(Name("beam_fade_out", id));

	rotation = lightParam->Get<CVector3>(Name("rotation", id)) / 180.8 * M_PI;

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

	coneRatio = sin(coneAngle);
	coneSoftRatio = sin(coneSoftAngle + coneAngle);
	projectionHorizontalRatio =
		tan(lightParam->Get<double>(Name("projection_horizonal_angle", id)) / 360.0 * M_PI) * 2.0;
	projectionVerticalRatio =
		tan(lightParam->Get<double>(Name("projection_vertical_angle", id)) / 360.0 * M_PI) * 2.0;
	projectionSoftEdge = lightParam->Get<double>(Name("projection_soft_edge", id));
	projectionIntensity = lightParam->Get<double>(Name("projection_intensity", id));
	projectionUseAsMask = lightParam->Get<bool>(Name("projection_use_as_mask", id));
	projectionTextureOffsetX = lightParam->Get<double>(Name("projection_texture_offset_x", id));
	projectionTextureOffsetY = lightParam->Get<double>(Name("projection_texture_offset_y", id));
	projectionTextureOffsetZ = lightParam->Get<double>(Name("projection_texture_offset_z", id));
	projectionTextureScaleX = lightParam->Get<double>(Name("projection_texture_scale_x", id));
	projectionTextureScaleY = lightParam->Get<double>(Name("projection_texture_scale_y", id));
	projectionTextureScaleZ = lightParam->Get<double>(Name("projection_texture_scale_z", id));
	projectionTextureRotationX = lightParam->Get<double>(Name("projection_texture_rotation_x", id));
	projectionTextureRotationY = lightParam->Get<double>(Name("projection_texture_rotation_y", id));
	projectionTextureRotationZ = lightParam->Get<double>(Name("projection_texture_rotation_z", id));
	projectionRepeatMode = lightParam->Get<int>(Name("projection_repeat_mode", id));
	projectionUseAlphaAsMask = lightParam->Get<bool>(Name("projection_use_alpha_as_mask", id));
	projectionUseTextureAlphaAsMask = lightParam->Get<bool>(Name("projection_use_texture_alpha_as_mask", id));
	projectionInvertAlphaMask = lightParam->Get<bool>(Name("projection_invert_alpha_mask", id));
	projectionBlendMode = lightParam->Get<int>(Name("projection_blend_mode", id));
	alphaTextureOffsetX = lightParam->Get<double>(Name("alpha_texture_offset_x", id));
	alphaTextureOffsetY = lightParam->Get<double>(Name("alpha_texture_offset_y", id));
	alphaTextureScaleX = lightParam->Get<double>(Name("alpha_texture_scale_x", id));
	alphaTextureScaleY = lightParam->Get<double>(Name("alpha_texture_scale_y", id));
	alphaTextureRotationZ = lightParam->Get<double>(Name("alpha_texture_rotation_z", id));
	alphaTextureRepeatMode = lightParam->Get<int>(Name("alpha_texture_repeat_mode", id));
	alphaTextureSoftEdge = lightParam->Get<double>(Name("alpha_texture_soft_edge", id));

	// backward compatibility: old repeat_texture parameter maps to Repeat mode
	if (repeatTexture && projectionRepeatMode == 0)
	{
		projectionRepeatMode = 1;
	}

	if (loadTextures)
	{
		if (type == lightProjection)
		{
			colorTexture = cTexture(lightParam->Get<QString>(Name("file_texture", id)),
				cTexture::doNotUseMipmaps, frameNo, quiet, useNetRender);
			QString alphaTextureFile = lightParam->Get<QString>(Name("file_texture_alpha", id));
			if (!alphaTextureFile.isEmpty())
			{
				alphaTexture = cTexture(alphaTextureFile, cTexture::doNotUseMipmaps, frameNo, quiet, useNetRender);
			}
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
			// Apply Z transforms to axiality (depth scaling/offset)
			double effectiveAxiality = axiality * projectionTextureScaleZ + projectionTextureOffsetZ;
			if (effectiveAxiality > 0.0)
			{
				// Rotate lightVector around light axes for 3D texture rotation
				CVector3 rotatedLightVector = lightVector;
				if (projectionTextureRotationX != 0.0)
				{
					double rad = projectionTextureRotationX * M_PI / 180.0;
					rotatedLightVector = rotatedLightVector.RotateAroundVectorByAngle(lightRightVector, rad);
				}
				if (projectionTextureRotationY != 0.0)
				{
					double rad = projectionTextureRotationY * M_PI / 180.0;
					rotatedLightVector = rotatedLightVector.RotateAroundVectorByAngle(lightTopVector, rad);
				}

				double texX = lightRightVector.Dot(rotatedLightVector) / projectionHorizontalRatio / effectiveAxiality + 0.5;
				double texY = lightTopVector.Dot(rotatedLightVector) / projectionVerticalRatio / effectiveAxiality + 0.5;

				// Apply UV transform for color texture
				double colorTexX = texX;
				double colorTexY = texY;
				{
					double u = colorTexX - 0.5;
					double v = colorTexY - 0.5;
					u *= projectionTextureScaleX;
					v *= projectionTextureScaleY;
					if (projectionTextureRotationZ != 0.0)
					{
						double rad = projectionTextureRotationZ * M_PI / 180.0;
						double c = cos(rad);
						double s = sin(rad);
						double ur = u * c - v * s;
						double vr = u * s + v * c;
						u = ur;
						v = vr;
					}
					u += projectionTextureOffsetX;
					v += projectionTextureOffsetY;
					colorTexX = u + 0.5;
					colorTexY = v + 0.5;
				}

				// Apply UV transform for alpha texture
				double alphaTexX = texX;
				double alphaTexY = texY;
				{
					double u = alphaTexX - 0.5;
					double v = alphaTexY - 0.5;
					u *= alphaTextureScaleX;
					v *= alphaTextureScaleY;
					if (alphaTextureRotationZ != 0.0)
					{
						double rad = alphaTextureRotationZ * M_PI / 180.0;
						double c = cos(rad);
						double s = sin(rad);
						double ur = u * c - v * s;
						double vr = u * s + v * c;
						u = ur;
						v = vr;
					}
					u += alphaTextureOffsetX;
					v += alphaTextureOffsetY;
					alphaTexX = u + 0.5;
					alphaTexY = v + 0.5;
				}

				double fade = 1.0;
				double alphaFade = 1.0;
				bool outOfBounds = false;

				if (projectionRepeatMode == 0) // Clamp
				{
					if (projectionSoftEdge > 0.0)
					{
						double effectiveEdge = std::min(projectionSoftEdge, 0.5f);
						auto edgeFade = [&](double t) -> double {
							if (t <= 0.0 || t >= 1.0) return 0.0;
							if (t < effectiveEdge) return t / effectiveEdge;
							if (t > 1.0 - effectiveEdge) return (1.0 - t) / effectiveEdge;
							return 1.0;
						};
						double fx = edgeFade(colorTexX);
						double fy = edgeFade(colorTexY);
						fade = std::max(0.0, std::min(1.0, fx * fy));
					}

					if (colorTexX <= 0.0 || colorTexX >= 1.0 || colorTexY <= 0.0 || colorTexY >= 1.0)
					{
						if (fade <= 0.0) outOfBounds = true;
						}
				}
				else if (projectionRepeatMode == 1) // Repeat
					{
						colorTexX = colorTexX - floor(colorTexX);
						colorTexY = colorTexY - floor(colorTexY);
					}
					else if (projectionRepeatMode == 2) // Mirror
					{
						colorTexX = fabs(fmod(colorTexX, 2.0) - 1.0);
						colorTexY = fabs(fmod(colorTexY, 2.0) - 1.0);
					}

					// Alpha texture repeat mode
					if (alphaTextureRepeatMode == 1) // Repeat
					{
						alphaTexX = alphaTexX - floor(alphaTexX);
						alphaTexY = alphaTexY - floor(alphaTexY);
					}
					else if (alphaTextureRepeatMode == 2) // Mirror
					{
						alphaTexX = fabs(fmod(alphaTexX, 2.0) - 1.0);
						alphaTexY = fabs(fmod(alphaTexY, 2.0) - 1.0);
					}
					else if (alphaTextureRepeatMode == 0) // Clamp
					{
						if (alphaTextureSoftEdge > 0.0)
						{
							double effectiveEdge = std::min(alphaTextureSoftEdge, 0.5f);
							auto edgeFade = [&](double t) -> double {
								if (t <= 0.0 || t >= 1.0) return 0.0;
								if (t < effectiveEdge) return t / effectiveEdge;
								if (t > 1.0 - effectiveEdge) return (1.0 - t) / effectiveEdge;
								return 1.0;
							};
							double fx = edgeFade(alphaTexX);
							double fy = edgeFade(alphaTexY);
							alphaFade = std::max(0.0, std::min(1.0, fx * fy));
						}
					}

					if (!outOfBounds)
					{
						float colorSampleX = (projectionRepeatMode == 0) ? std::max(0.0, std::min(1.0, colorTexX)) : colorTexX;
						float colorSampleY = (projectionRepeatMode == 0) ? std::max(0.0, std::min(1.0, colorTexY)) : colorTexY;
						float alphaSampleX = (alphaTextureRepeatMode == 0) ? std::max(0.0, std::min(1.0, alphaTexX)) : alphaTexX;
						float alphaSampleY = (alphaTextureRepeatMode == 0) ? std::max(0.0, std::min(1.0, alphaTexY)) : alphaTexY;
						sRGBFloat pixel = colorTexture.Pixel(CVector2<float>(colorSampleX, colorSampleY), 0.0);

						if (projectionUseTextureAlphaAsMask && alphaTexture.IsLoaded())
						{
							float alpha = alphaTexture.PixelAlpha(CVector2<float>(alphaSampleX, alphaSampleY));
							if (projectionInvertAlphaMask) alpha = 1.0f - alpha;
							outColor = pixel;
							intens = alpha * fade * alphaFade * projectionIntensity;
						}
					else if (projectionUseAlphaAsMask && colorTexture.HasAlpha())
					{
						float alpha = colorTexture.PixelAlpha(CVector2<float>(colorSampleX, colorSampleY));
						if (projectionInvertAlphaMask) alpha = 1.0f - alpha;
						outColor = {1.0, 1.0, 1.0};
						intens = alpha * fade * projectionIntensity;
					}
					else if (projectionUseAsMask)
					{
						double luminance = pixel.R * 0.299 + pixel.G * 0.587 + pixel.B * 0.114;
						if (projectionInvertAlphaMask) luminance = 1.0 - luminance;
						outColor = {1.0, 1.0, 1.0};
						intens = luminance * fade * projectionIntensity;
					}
					else
					{
						outColor = pixel;
						intens = fade * projectionIntensity;
					}
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
		else
		{
			outColor = {0.0, 0.0, 0.0};
			intens = 0.0;
		}
	}
	return intens;
}

CVector3 cLight::CalculateLightVector(const CVector3 &point, double delta, double resolution,
	double viewDistanceMax, double &outDistance, double *outBeamFade) const
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
		if (outBeamFade) *outBeamFade = 1.0;
	}
	else
	{
		double fade = 1.0;
		CVector3 d = CalculateBeam(position, target, &fade) - point;
		lightVector = d;
		lightVector.Normalize();
		outDistance = d.Length();
		if (outBeamFade) *outBeamFade = fade;
	}

	return lightVector;
}

CVector3 cLight::CalculateBeam(const CVector3 &point1, const CVector3 &point2, double *outFade) const
{
	if (type == cLight::lightBeam)
	{
		CVector3 direction = point2 - point1;
		double t = Random(10000) / 10000.0;
		CVector3 pointOnLine = point1 + direction * t;
		double fade = 1.0;

		// Length-wise fade
		if (beamFadeIn > 0.0 && t < beamFadeIn)
		{
			fade *= t / beamFadeIn;
		}
		if (beamFadeOut > 0.0 && t > (1.0 - beamFadeOut))
		{
			fade *= (1.0 - t) / beamFadeOut;
		}

		if (beamRadius > 0.0)
		{
			// Generate a random offset perpendicular to the beam direction
			CVector3 dirNormalized = direction;
			dirNormalized.Normalize();

			// Find a perpendicular vector
			CVector3 perp1;
			if (fabs(dirNormalized.z) < 0.99)
			{
				perp1 = CVector3(0.0, 0.0, 1.0).Cross(dirNormalized);
			}
			else
			{
				perp1 = CVector3(1.0, 0.0, 0.0).Cross(dirNormalized);
			}
			perp1.Normalize();
			CVector3 perp2 = dirNormalized.Cross(perp1);

			// Uniform distribution over disk: r = radius * sqrt(random)
			double angle = Random(10000) / 10000.0 * 2.0 * M_PI;
			double r = beamRadius * sqrt(Random(10000) / 10000.0);

			pointOnLine += perp1 * cos(angle) * r + perp2 * sin(angle) * r;

			// Calculate radial fade
			if (beamSoftEdge > 0.0)
			{
				double innerRadius = beamRadius * (1.0 - beamSoftEdge);
				if (r <= innerRadius)
				{
					// fade stays unchanged
				}
				else if (r < beamRadius)
				{
					fade *= 1.0 - (r - innerRadius) / (beamRadius * beamSoftEdge);
				}
				else
				{
					fade = 0.0;
				}
			}
		}

		if (outFade) *outFade = fade;
		return pointOnLine;
	}
	else
	{
		if (outFade) *outFade = 1.0;
		return point1;
	}
}

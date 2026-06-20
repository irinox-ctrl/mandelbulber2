/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2018-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * cRenderWorker::VolumetricShader method - calculates volumetric shaders
 */

#include <algorithm>
#include <cmath>

#include "algebra.hpp"
#include "ao_modes.h"
#include "calculate_distance.hpp"
#include "calculation_mode.h"
#include "color_structures.hpp"
#include "compute_fractal.hpp"
#include "fractparams.hpp"
#include "lights.hpp"
#include "nine_fractals.hpp"
#include "render_data.hpp"
#include "render_worker.hpp"
#include "glow_sphere.hpp"

namespace
{
float VolumetricAlpha(const float opticalDepth)
{
	const float depth = clamp(opticalDepth, 0.0f, 12.0f);
	return 1.0f - std::exp(-depth);
}

float VolumetricStepJitterScale(const CVector3 &point, int stepIndex, bool blueNoise,
	float strengthPercent)
{
	const float strength = strengthPercent * 0.01f;
	float t = 0.0f;
	if (blueNoise)
	{
		const int seed =
			int(fabs(point.x * 127.1 + point.y * 311.7 + point.z * 74.7) * 1000.0) + stepIndex * 17;
		const float v = float(seed % 10007) * 0.000099930f + float((seed / 10007) % 997) * 0.00100301f;
		t = v - floor(v);
		t = float(fmod(52.9829189 * fmod(double(t), 1.0), 1.0));
	}
	else
	{
		t = float(Random(1000) / 10000.0);
	}
	return 1.0f - strength * t;
}
} // namespace

void cRenderWorker::RayleighScattering(const CVector3 &lightVectorTemp,
	const sShaderInputData &input, sRGBFloat &raleighScatteringRGB, sRGBFloat &mieScatteringRGB) const
{
	if (params->rayleighScatteringBlue > 0.0f)
	{
		float raleighScattering =
			(1.0 + pow(lightVectorTemp.Dot(input.viewVector), 2.0)) * params->rayleighScatteringBlue;
		raleighScatteringRGB.R = 1.0;
		raleighScatteringRGB.G = (1.0 + 0.2 * raleighScattering);
		raleighScatteringRGB.B = (1.0 + 2.0 * raleighScattering);
	}
	if (params->rayleighScatteringRed > 0.0f)
	{
		float mieScatteringR =
			pow(lightVectorTemp.Dot(input.viewVector) * 0.5 + 0.5, 15.0) * params->rayleighScatteringRed;
		float mieScatteringG =
			pow(lightVectorTemp.Dot(input.viewVector) * 0.5 + 0.5, 10.0) * params->rayleighScatteringRed;
		mieScatteringRGB.R = (1.0 + 5.0 * mieScatteringR);
		mieScatteringRGB.G = (1.0 + mieScatteringG);
		mieScatteringRGB.B = 1.0;
	}
}

sRGBAFloat cRenderWorker::VolumetricShader(
	const sShaderInputData &input, sRGBAFloat oldPixel, sRGBAFloat *opacityOut) const
{
	sRGBAFloat output;
	float totalOpacity = 0.0;
	float transmittance = 1.0f;

	output.R = oldPixel.R;
	output.G = oldPixel.G;
	output.B = oldPixel.B;
	output.A = oldPixel.A;

	// visible lights init
	int numberOfLights = data->lights.GetNumberOfLights();
	if (numberOfLights < 4) numberOfLights = 4;

	// glow init
	float glow = input.stepCount * params->glowIntensity / 512.0f * float(params->DEFactor);
	float glowN = 1.0f - glow;
	if (glowN < 0.0f) glowN = 0.0f;
	float glowR = (params->glowColor1.R * glowN + params->glowColor2.R * glow);
	float glowG = (params->glowColor1.G * glowN + params->glowColor2.G * glow);
	float glowB = (params->glowColor1.B * glowN + params->glowColor2.B * glow);

	double totalStep = 0.0;

	// qDebug() << "Start volumetric shader &&&&&&&&&&&&&&&&&&&&";

	int numberOfSteps;
	bool recalcStepsMode;
	double scan = 0.0f;
	double lastCloudDistance = params->cloudsPeriod;
	bool end = false;

	if (!qFuzzyCompare(params->volumetricLightDEFactor, 1.0) || params->cloudsEnable)
	{
		numberOfSteps = params->maxRaymarchingSteps;
		if (params->volumetricMaxSteps > 0)
			numberOfSteps = std::min(numberOfSteps, params->volumetricMaxSteps);
		if (params->volumetricPreviewActive)
			numberOfSteps = std::max(numberOfSteps / 2, 12);
		recalcStepsMode = true;
		scan = CalcDistThresh(input.point);
	}
	else
	{
		numberOfSteps = input.stepCount - 1;
		recalcStepsMode = false;
	}

	sShaderInputData input2 = input;
	for (int index = numberOfSteps; index > 0; index--)
	{
		double step;
		double distance;
		CVector3 point;
		int iterations = 0;

		// distance, points and steps are recalculated when custom DE step is usew=d
		if (recalcStepsMode)
		{
			point = input.point - input.viewVector * scan;

			input2.point = point;
			input2.distThresh = CalcDistThresh(point);
			input2.delta = CalcDelta(point);

			sDistanceOut distanceOut;
			sDistanceIn distanceIn(point, input2.distThresh, false);
			distance = CalculateDistance(*params, *fractal, distanceIn, &distanceOut, data);
			iterations = distanceOut.iters;

			step = (min(distance, lastCloudDistance) - 0.5 * input2.distThresh) * params->DEFactor
						 * params->volumetricLightDEFactor;

			step *= VolumetricStepJitterScale(point, numberOfSteps - index,
				params->volumetricBlueNoiseJitter, params->volumetricJitterStrength);

			if (params->volumetricPreviewActive)
				step *= params->volumetricPreviewStepMul;

			if (params->advancedQuality)
			{
				step = clamp(step, params->absMinMarchingStep, params->absMaxMarchingStep);

				if (input2.distThresh > params->absMinMarchingStep)
					step = clamp(step, params->relMinMarchingStep * input2.distThresh,
						params->relMaxMarchingStep * input2.distThresh);
			}

			step = max(step, input2.distThresh);

			end = false;
			if (step > input.depth - scan)
			{
				step = input.depth - scan;
				end = true;
			}
			scan += step;

			// qDebug() << point.Debug() << distance << step << input.depth - scan << lastCloudDistance;
		}
		// distance, points and steps are taken from arrays
		else
		{
			step = input.stepBuff[index].step;
			distance = input.stepBuff[index].distance;
			point = input.stepBuff[index].point;
			iterations = input.stepBuff[index].iters;

			totalStep += step;

			input2.point = point;
			input2.distThresh = input.stepBuff[index].distThresh;
			input2.delta = CalcDelta(point);

			// qDebug() << "i" << index << "dist" << distance << "iters" << input.stepBuff[index].iters <<
			// "distThresh" << input2.distThresh << "step" << step << "point" << point.Debug();

			if (totalStep < 1e-10 * CalcDistThresh(point)) // if two steps are the same
			{
				continue;
			}
			step = totalStep;
			totalStep = 0.0;
		}

		//------------------- glow
		if (params->glowEnabled && input.stepCount > 0)
		{
			float glowOpacity = glow / input.stepCount * params->volumetricLightDEFactor;
			if (glowOpacity > 1.0f) glowOpacity = 1.0f;
			output.R = glowOpacity * glowR + (1.0f - glowOpacity) * output.R;
			output.G = glowOpacity * glowG + (1.0f - glowOpacity) * output.G;
			output.B = glowOpacity * glowB + (1.0f - glowOpacity) * output.B;
			output.A += glowOpacity;
		}
		// qDebug() << "step" << step;

		//---------------------- volumetric lights with shadows in fog

		float iterFogOpacity = 0.0f;
		sRGBFloat iterFogCol;

		float basicFogOpacity = 0.0f;
		if (params->fogEnabled)
		{
			basicFogOpacity = step / params->fogVisibility;

			if (params->primitives.primitiveIndexForBasicFog >= 0)
			{
				int closestId = -1;
				if (params->primitives.TotalDistance(point, distance, input2.delta, false, &closestId, data,
							params->primitives.primitiveIndexForBasicFog)
						> input2.delta)
					basicFogOpacity = 0;
			}
		}

		if (params->iterFogEnabled)
		{
			iterFogOpacity = IterOpacity(step, iterations, params->iterFogEffectiveN,
				params->iterFogOpacityTrim, params->iterFogOpacityTrimHigh, params->iterFogOpacity);

			if (iterFogOpacity > 0.0 && params->primitives.primitiveIndexForIterFog >= 0)
			{
				int closestId = -1;
				if (params->primitives.TotalDistance(point, distance, input2.delta, false, &closestId, data,
							params->primitives.primitiveIndexForIterFog)
						> input2.delta)
					iterFogOpacity = 0;
			}

			if (iterFogOpacity > 0.0)
			{
				// fog colour
				const float denom1 = std::max(
					1e-3f, params->iterFogColor1Maxiter - params->iterFogOpacityTrim);
				float iterFactor1 = (iterations - params->iterFogOpacityTrim) / denom1;
				float k = iterFactor1;
				if (k > 1.0f) k = 1.0f;
				if (k < 0.0f) k = 0.0f;
				float kn = 1.0f - k;
				iterFogCol.R = params->iterFogColour1.R * kn + params->iterFogColour2.R * k;
				iterFogCol.G = params->iterFogColour1.G * kn + params->iterFogColour2.G * k;
				iterFogCol.B = params->iterFogColour1.B * kn + params->iterFogColour2.B * k;

				const float denom2 = std::max(
					1e-3f, params->iterFogColor2Maxiter - params->iterFogColor1Maxiter);
				float iterFactor2 = (iterations - params->iterFogColor1Maxiter) / denom2;
				float k2 = iterFactor2;
				if (k2 < 0.0f) k2 = 0.0;
				if (k2 > 1.0f) k2 = 1.0;
				kn = 1.0f - k2;
				iterFogCol.R = iterFogCol.R * kn + params->iterFogColour3.R * k2;
				iterFogCol.G = iterFogCol.G * kn + params->iterFogColour3.G * k2;
				iterFogCol.B = iterFogCol.B * kn + params->iterFogColour3.B * k2;
			}
			//----
		}

		double cloudsOpacity = 0.0;
		double cloudDensity = 0.0;
		CVector3 deltaCloud;

		if (params->cloudsEnable)
		{
			double distanceToClouds = 0.0;
			bool calculateClouds = true;

			if (params->primitives.primitiveIndexForClouds >= 0)
			{
				int closestId = -1;
				if (params->primitives.TotalDistance(point, distance, input2.delta, false, &closestId, data,
							params->primitives.primitiveIndexForClouds)
						> input2.delta)
				{
					cloudDensity = 0;
					calculateClouds = false;
				}
			}

			if (calculateClouds)
			{
				cloudDensity = CloudOpacity(point, distance, input2.delta, &distanceToClouds);
			}
			else
			{
				distanceToClouds = distance;
			}

			if (cloudDensity > 0.0 && !params->cloudsCastShadows)
			{
				double delta = params->cloudsPeriod / pow(2.0, params->cloudsIterations) * 5.0f;
				double distanceToCloudsDummy = 0.0;
				deltaCloud.x = CloudOpacity(point + CVector3(delta, 0.0, 0.0), distance, input2.delta,
												 &distanceToCloudsDummy)
											 - cloudDensity;
				deltaCloud.y = CloudOpacity(point + CVector3(0.0, delta, 0.0), distance, input2.delta,
												 &distanceToCloudsDummy)
											 - cloudDensity;
				deltaCloud.z = CloudOpacity(point + CVector3(0.0, 0.0, delta), distance, input2.delta,
												 &distanceToCloudsDummy)
											 - cloudDensity;

				if (deltaCloud.Length() > 0.0)
				{
					deltaCloud.Normalize();
				}
			}

			cloudsOpacity = cloudDensity * step;
			// qDebug() << cloud;

			lastCloudDistance = distanceToClouds;
		}

		double distFogOpacity = 0.0;
		sRGBFloat distFogColor(0.0, 0.0, 0.0);

		//-------------------- volumetric fog
		if (params->volFogDensity > 0.0f && params->volFogEnabled)
		{
			double colourThresh = params->volFogColour1Distance;
			double colourThresh2 = params->volFogColour2Distance;

			double distanceShifted;
			const double depthAlongRay = (point - params->camera).Dot(input.viewVector);
			distFogOpacity = DistanceFogOpacity(step, distance, params->volFogDistanceFromSurface,
				params->volFogDistanceFactor, params->volFogDensity, std::max(depthAlongRay, 0.0), point,
				distanceShifted);

			if (distFogOpacity > 0.0 && params->primitives.primitiveIndexForDistFog >= 0)
			{
				int closestId = -1;
				if (params->primitives.TotalDistance(point, distance, input2.delta, false, &closestId, data,
							params->primitives.primitiveIndexForDistFog)
						> input2.delta)
					distFogOpacity = 0;
			}

			float k = distanceShifted / colourThresh;
			if (k > 1) k = 1.0f;
			float kn = 1.0f - k;
			float fogTempR = params->volFogColour1.R * kn + params->volFogColour2.R * k;
			float fogTempG = params->volFogColour1.G * kn + params->volFogColour2.G * k;
			float fogTempB = params->volFogColour1.B * kn + params->volFogColour2.B * k;

			float k2 = distanceShifted / colourThresh2 * k;
			if (k2 > 1) k2 = 1.0;
			kn = 1.0f - k2;
			distFogColor.R = fogTempR * kn + params->volFogColour3.R * k2;
			distFogColor.G = fogTempG * kn + params->volFogColour3.G * k2;
			distFogColor.B = fogTempB * kn + params->volFogColour3.B * k2;
		}

		sRGBAFloat totalLightsWithShadows(0.0, 0.0, 0.0, 0.0);
		sRGBAFloat totalLights(0.0, 0.0, 0.0, 0.0);
		sRGBAFloat totalLightsClouds(0.0, 0.0, 0.0, 0.0);

		for (int i = 0; i < data->lights.GetNumberOfLights(); i++)
		{
			if (data->lights.IsAnyLightEnabled())
			{
				const cLight *light = data->lights.GetLight(i);
				if (light->enabled)
				{
					bool shadowNeeded = false;
					bool lightNeeded = false;

					if (light->volumetric)
					{
						shadowNeeded = true;
						lightNeeded = true;
					}

					if (params->iterFogEnabled && iterFogOpacity > 0.0)
					{
						lightNeeded = true;
						if (params->iterFogShadows) shadowNeeded = true;
					}

					if (params->cloudsEnable && cloudsOpacity > 0.0)
					{
						lightNeeded = true;
						if (params->cloudsCastShadows) shadowNeeded = true;
					}

					if (params->distanceFogShadows && distFogOpacity > 0.0)
					{
						lightNeeded = true;
						shadowNeeded = true;
					}

					if (params->fogCastShadows && basicFogOpacity > 0.0)
					{
						lightNeeded = true;
						shadowNeeded = true;
					}

					if (!light->castShadows) shadowNeeded = false;

					if (lightNeeded)
					{
						double distanceLight = 0.0;
						CVector3 lightVectorTemp = light->CalculateLightVector(
							point, input2.delta, params->resolution, params->viewDistanceMax, distanceLight);

						float lightIntensity;
						if (light->type == cLight::lightDirectional)
							lightIntensity = light->intensity;
						else if (light->type == cLight::lightConical || light->type == cLight::lightProjection)
							lightIntensity = light->intensity * 10.0;
						else
							lightIntensity = light->intensity / light->Decay(distanceLight) * 4.0;

						sRGBFloat textureColor(0.0, 0.0, 0.0);
						lightIntensity *= light->CalculateCone(point, lightVectorTemp, textureColor);

						sRGBAFloat lightShadow(0.0, 0.0, 0.0, 0.0);
						if (shadowNeeded)
						{
							if (lightIntensity > 1e-3)
								lightShadow = AuxShadow(input2, light, distanceLight, lightVectorTemp);
							else
								lightShadow = sRGBAFloat();
						}

						sRGBFloat raleighScatteringRGB(1.0, 1.0, 1.0);
						sRGBFloat mieScatteringRGB(1.0, 1.0, 1.0);

						RayleighScattering(lightVectorTemp, input, raleighScatteringRGB, mieScatteringRGB);

						sRGBFloat calculatedLight(0.0, 0.0, 0.0);
						calculatedLight.R = light->color.R * lightIntensity * textureColor.R
																* raleighScatteringRGB.R * mieScatteringRGB.R;
						calculatedLight.G = light->color.G * lightIntensity * textureColor.G
																* raleighScatteringRGB.G * mieScatteringRGB.G;
						calculatedLight.B = light->color.B * lightIntensity * textureColor.B
																* raleighScatteringRGB.B * mieScatteringRGB.B;

						totalLightsWithShadows.R += calculatedLight.R * lightShadow.R;
						totalLightsWithShadows.G += calculatedLight.G * lightShadow.G;
						totalLightsWithShadows.B += calculatedLight.B * lightShadow.B;

						totalLights.R += calculatedLight.R;
						totalLights.G += calculatedLight.G;
						totalLights.B += calculatedLight.B;

						double shadeClouds = clamp(-lightVectorTemp.Dot(deltaCloud), 0.0, 1.0);
						totalLightsClouds.R += calculatedLight.R * shadeClouds;
						totalLightsClouds.G += calculatedLight.G * shadeClouds;
						totalLightsClouds.B += calculatedLight.B * shadeClouds;

						if (light->volumetric)
						{
							output.R +=
								calculatedLight.R * light->volumetricVisibility * lightShadow.R * float(step);
							output.G +=
								calculatedLight.G * light->volumetricVisibility * lightShadow.G * float(step);
							output.B +=
								calculatedLight.B * light->volumetricVisibility * lightShadow.B * float(step);
							output.A +=
								lightShadow.A * float(step) * lightIntensity * light->volumetricVisibility;
						}
					} // if light needed
				} // if light enabled
			} // if any light enabled
		} // next light

		if (params->DOFMonteCarloGlobalIllumination && params->monteCarloGIOfVolumetric)
		{
			sRGBFloat gi = GlobalIlumination(input2, sRGBAFloat(1.0, 1.0, 1.0, 0.0), true);
			totalLights.R += gi.R;
			totalLights.G += gi.G;
			totalLights.B += gi.B;
			totalLightsWithShadows.R += gi.R;
			totalLightsWithShadows.G += gi.G;
			totalLightsWithShadows.B += gi.B;
		}

		sRGBAFloat AO(0.0, 0.0, 0.0, 0.0);

		if (params->ambientOcclusionEnabled
				&& params->ambientOcclusionMode == params::AOModeMultipleRays)
		{
			if ((params->iterFogEnabled && iterFogOpacity > 0.0)
				/*|| (params->volFogEnabled && distFogOpacity > 0.0)*/)
			{
				AO = AmbientOcclusion(input2);
				AO.R *= params->ambientOcclusion;
				AO.G *= params->ambientOcclusion;
				AO.B *= params->ambientOcclusion;
			}
		}

		if (params->iterFogEnabled && iterFogOpacity > 0.0)
		{
			sRGBAFloat light = (params->iterFogShadows) ? totalLightsWithShadows : totalLights;

			const float alpha = VolumetricAlpha(float(iterFogOpacity));

			output.R =
				output.R * (1.0f - alpha)
				+ (light.R * params->iterFogBrightnessBoost + AO.R) * alpha * iterFogCol.R;

			output.G =
				output.G * (1.0f - alpha)
				+ (light.G * params->iterFogBrightnessBoost + AO.G) * alpha * iterFogCol.G;

			output.B =
				output.B * (1.0f - alpha)
				+ (light.B * params->iterFogBrightnessBoost + AO.B) * alpha * iterFogCol.B;

			totalOpacity = alpha + (1.0f - alpha) * totalOpacity;
			output.A = alpha + (1.0f - alpha) * output.A;
			transmittance *= (1.0f - alpha);
		}

		if (params->cloudsEnable && cloudsOpacity > 0.0)
		{
			sRGBAFloat light = (params->cloudsCastShadows) ? totalLightsWithShadows : totalLightsClouds;

			double ambient = params->cloudsAmbientLight;
			double nAmbient = 1.0 - params->cloudsAmbientLight;

			light.R = ambient * totalLights.R + nAmbient * light.R;
			light.G = ambient * totalLights.G + nAmbient * light.G;
			light.B = ambient * totalLights.B + nAmbient * light.B;

			const float alpha = VolumetricAlpha(float(cloudsOpacity));

			output.R = output.R * (1.0f - alpha) + (light.R + AO.R) * alpha * params->cloudsColor.R;
			output.G = output.G * (1.0f - alpha) + (light.G + AO.G) * alpha * params->cloudsColor.G;
			output.B = output.B * (1.0f - alpha) + (light.B + AO.B) * alpha * params->cloudsColor.B;
			totalOpacity = alpha + (1.0f - alpha) * totalOpacity;
			output.A = alpha + (1.0f - alpha) * output.A;
			transmittance *= (1.0f - alpha);
		}

		if (params->volFogEnabled && distFogOpacity > 0.0)
		{
			sRGBAFloat light =
				(params->distanceFogShadows) ? totalLightsWithShadows : sRGBFloat(1.0, 1.0, 1.0);

			const float alpha = VolumetricAlpha(float(distFogOpacity));

			output.R =
				alpha * distFogColor.R * (light.R + AO.R) + (1.0f - alpha) * output.R;
			output.G =
				alpha * distFogColor.G * (light.G + AO.G) + (1.0f - alpha) * output.G;
			output.B =
				alpha * distFogColor.B * (light.B + AO.B) + (1.0f - alpha) * output.B;

			totalOpacity = alpha + (1.0f - alpha) * totalOpacity;
			output.A = alpha + (1.0f - alpha) * output.A;
			transmittance *= (1.0f - alpha);
		}

		//----------------------- basic fog
		if (params->fogEnabled && basicFogOpacity > 0.0)
		{

			sRGBAFloat light =
				(params->fogCastShadows) ? totalLightsWithShadows : sRGBFloat(1.0, 1.0, 1.0);
			const float alpha = VolumetricAlpha(float(basicFogOpacity));
			output.R = alpha * params->fogColor.R * (light.R + AO.R) + (1.0f - alpha) * output.R;
			output.G = alpha * params->fogColor.G * (light.G + AO.G) + (1.0f - alpha) * output.G;
			output.B = alpha * params->fogColor.B * (light.B + AO.B) + (1.0f - alpha) * output.B;
			totalOpacity = alpha + (1.0f - alpha) * totalOpacity;
			output.A = alpha + (1.0f - alpha) * output.A;
			transmittance *= (1.0f - alpha);
		}

		//------------------ visible light
		if (data->lights.IsAnyLightEnabled())
		{
			for (int i = 0; i < data->lights.GetNumberOfLights(); ++i)
			{
				const cLight *light = data->lights.GetLight(i);
				if (light->enabled && light->intensity > 0.0 && light->visibility > 0.0
						&& light->type != cLight::lightDirectional)
				{
					double lastMiniSteps = -1.0;
					double miniStep;

					double beamFade = 1.0;
					CVector3 lightPosition = light->CalculateBeam(light->position, light->target, &beamFade);

					for (double miniSteps = 0.0; miniSteps < step; miniSteps += miniStep)
					{
						CVector3 lightDistVect = point - input.viewVector * miniSteps - lightPosition;
						double lightDist = lightDistVect.Length();
						double lightSize = sqrt(light->intensity) * light->size;

						double distToLightSurface = lightDist - lightSize;
						if (distToLightSurface < 0.0) distToLightSurface = 0.0;

						miniStep = 0.1 * (distToLightSurface + 0.1 * distToLightSurface);
						if (miniStep > step - miniSteps) miniStep = step - miniSteps;
						if (miniStep < step * 0.001) miniStep = step * 0.001;

						double r2 = lightDist / lightSize;

						double bellFunction;
						if (light->type == cLight::lightConical || light->type == cLight::lightProjection)
						{
							bellFunction = 1.0;
						}
						else
						{
							bellFunction = 1.0 / (1.0 + pow(r2, double((light->decayFunction + 1) * 2)));
						}

						CVector3 lightDirection = lightDistVect;
						lightDirection.Normalize();
						sRGBFloat textureColor;
						bellFunction *= light->CalculateCone(point, (-1.0) * lightDirection, textureColor);
						bellFunction *= beamFade;

						float lightDensity = miniStep * bellFunction * light->visibility / lightSize;

						lightDensity *= 1.0f + params->cloudsLightsBoost * cloudDensity;

						output.R += lightDensity * light->color.R * textureColor.R;
						output.G += lightDensity * light->color.G * textureColor.G;
						output.B += lightDensity * light->color.B * textureColor.B;
						output.A += lightDensity;

						if (miniSteps == lastMiniSteps)
						{
							// qWarning() << "Dead computation\n"
							//		<< "\pointN:" << (point - input.viewVector * miniSteps).Debug();
							break;
						}
						lastMiniSteps = miniSteps;
					}
				}
			}
		}

		// fake lights (orbit trap) — only if Single Trap Lights is disabled
		if (!params->singleTrapLights.enabled && params->fakeLightsEnabled)
		{
			int fakeLightMaxLoop = 1;
			if (params->common.fakeLightsColor2Enabled) fakeLightMaxLoop = 2;
			if (params->common.fakeLightsColor3Enabled) fakeLightMaxLoop = 3;

			// V2: Create a mutable copy of common params for position calculation
			sCommonParams commonWithPosition = params->common;

			// V2: Calculate orbit trap position based on positioning mode
			if (params->common.fakeLightsOrbitTrapPreTransformed)
			{
				commonWithPosition.fakeLightsOrbitTrap = params->common.fakeLightsOrbitTrap;
			}
			else
			{
				int posMode = params->common.fakeLightsPositionMode;
				const sFakeLightsModeParams &mode = params->common.fakeLightsModes[posMode];
				CRotationMatrix modeRot;
				modeRot.SetRotation2(mode.rotation * M_PI / 180.0);
				CVector3 transformedTrap =
					mode.offset + modeRot.RotateVector(params->common.fakeLightsOrbitTrap * mode.scale);

				if (posMode == params::fakeLightsPositionCamera)
				{
					commonWithPosition.fakeLightsOrbitTrap = params->camera + transformedTrap;
				}
				else if (posMode == params::fakeLightsPositionTarget)
				{
					commonWithPosition.fakeLightsOrbitTrap = params->target + transformedTrap;
				}
				else if (posMode == params::fakeLightsPositionPathCircle)
				{
					double angle = mode.rotation.y * M_PI / 180.0;
					CVector3 pathOffset(cos(angle) * mode.pathRadius, 0.0, sin(angle) * mode.pathRadius);
					commonWithPosition.fakeLightsOrbitTrap = transformedTrap + pathOffset;
				}
				else if (posMode == params::fakeLightsPositionPathSpiral)
				{
					double angle = mode.rotation.y * M_PI / 180.0;
					double yOffset = angle * mode.pathRadius * 0.1;
					CVector3 pathOffset(cos(angle) * mode.pathRadius, yOffset, sin(angle) * mode.pathRadius);
					commonWithPosition.fakeLightsOrbitTrap = transformedTrap + pathOffset;
				}
				else if (posMode == params::fakeLightsPositionOrbitTarget)
				{
					double angle = mode.rotation.y * M_PI / 180.0;
					CVector3 pathOffset(cos(angle) * mode.pathRadius, 0.0, sin(angle) * mode.pathRadius);
					commonWithPosition.fakeLightsOrbitTrap = params->target + transformedTrap + pathOffset;
				}
				else
				{
					commonWithPosition.fakeLightsOrbitTrap = transformedTrap;
				}
			}

			for (int fakeLightLoop = 0; fakeLightLoop < fakeLightMaxLoop; fakeLightLoop++)
			{
				sFractalIn fractIn(point, params->minN, -1, 1, fakeLightLoop, &commonWithPosition, -1, false);
				sFractalOut fractOut;
	fractOut.normal = CVector3(0, 0, 0);
				Compute<fractal::calcModeOrbitTrap>(*fractal, nullptr, fractIn, &fractOut);
				float r = fractOut.orbitTrapR;
				r = sqrtf(1.0f / (r + 1.0e-20f));
				float fakeLight = 1.0f
															/ (powf(r, 10.0f / params->fakeLightsVisibilitySize)
																		* powf(10.0f, 10.0f / params->fakeLightsVisibilitySize)
																	+ 0.1f);

				// V2: Distance-based intensity mask
				float maskRadius = commonWithPosition.fakeLightsShapeMaskRadius;
				float maskSoftness = commonWithPosition.fakeLightsShapeMaskSoftness;
				if (maskRadius > 1e-10f)
				{
					float edge = maskRadius + maskSoftness;
					float factor = 1.0f;
					if (r < maskRadius)
						factor = 0.0f;
					else if (r < edge && maskSoftness > 1e-10f)
						factor = (r - maskRadius) / maskSoftness;
					if (factor < 0.0f) factor = 0.0f;
					if (factor > 1.0f) factor = 1.0f;
					fakeLight *= factor;
				}

				// V2: Distance masking based on DE from fractal surface
				if (params->fakeLightsMaskEnabled)
				{
					float normalizedDist = float(distance) / (float(params->fakeLightsMaskThreshold) + 1e-10f);
					float maskFactor = 1.0f / (1.0f + powf(normalizedDist, params->fakeLightsMaskSharpness));
					fakeLight *= maskFactor;
				}

				fakeLight *= 1.0f + params->cloudsLightsBoost * cloudDensity;

				sRGBFloat color;
				if (fakeLightLoop == 0 && commonWithPosition.fakeLightsMultiCenterEnabled
					&& fractOut.orbitTrapCenterIndex >= 0 && fractOut.orbitTrapCenterIndex < 24)
				{
					color = params->fakeLightsMultiCenterColor[fractOut.orbitTrapCenterIndex];
				}
				else
				{
					switch (fakeLightLoop)
					{
						case 0: color = params->fakeLightsColor; break;
						case 1: color = params->fakeLightsColor2; break;
						case 2: color = params->fakeLightsColor3; break;
						default: color = params->fakeLightsColor; break;
					}
				}

				output.R += fakeLight * float(step) * params->fakeLightsVisibility * color.R;
				output.G += fakeLight * float(step) * params->fakeLightsVisibility * color.G;
				output.B += fakeLight * float(step) * params->fakeLightsVisibility * color.B;
				output.A += fakeLight * float(step) * params->fakeLightsVisibility;
			}
		}

		// Single Trap Lights (volumetric)
		if (params->singleTrapLights.enabled)
		{
			const int soloLayer = params->singleTrapLights.soloLayerIndex;
			const int combineMode = int(params->singleTrapLights.combineMode);
			float stlR = 0.0f;
			float stlG = 0.0f;
			float stlB = 0.0f;
			int processedLayers = 0;

			for (int i = 0; i < params->singleTrapLights.activeLayerCount; i++)
			{
				const sSingleTrapLightLayer &layer = params->singleTrapLights.layers[i];
				if (!layer.enabled) continue;
				if (soloLayer > 0 && soloLayer != i + 1) continue;

				CVector3 effectivePosition = layer.position;
				if (!layer.preTransformed)
				{
					if (layer.positionMode == 1) effectivePosition += params->camera;
					else if (layer.positionMode == 2) effectivePosition += params->common.fractalPosition;
					else if (layer.positionMode == 3) effectivePosition += params->target;
				}

				// Apply animation
				double time = params->frameNo;
				double animatedSize = layer.size;
				if (layer.animOrbitSpeed != 0.0 || layer.animPulsateSpeed != 0.0)
				{
					double orbitAngle = time * layer.animOrbitSpeed * 0.01 + i * 0.7;
					effectivePosition.x += cos(orbitAngle) * layer.animOrbitRadius;
					effectivePosition.y += sin(orbitAngle) * layer.animOrbitRadius;

					double pulsate = 1.0 + sin(time * layer.animPulsateSpeed * 0.1 + i * 1.3) * layer.animPulsateAmount;
					animatedSize *= pulsate;
				}

				if (layer.maxDistance > 1e-30)
				{
					const double rs = fabs(layer.relativeSize);
					const double sz = std::max(fabs(animatedSize), fabs(layer.size2)) * rs
						+ fabs(layer.edgeSoftness) * rs;
					const double margin = sz + layer.maxDistance * rs + fabs(layer.animOrbitRadius);
					const double dx = point.x - effectivePosition.x;
					const double dy = point.y - effectivePosition.y;
					const double dz = point.z - effectivePosition.z;
					if (sqrt(dx * dx + dy * dy + dz * dz) > margin * 2.8) continue;
				}

				CVector3 adjustedPoint = point - effectivePosition + layer.position * layer.relativeSize;
				CVector3 scaledPoint = adjustedPoint / layer.relativeSize;
				sSingleTrapLightLayer animatedLayer = layer;
				animatedLayer.size = animatedSize;
				double rawDistance = SingleTrapLightDistance(scaledPoint, animatedLayer) * layer.relativeSize;
				double distance = rawDistance;
				if (distance < 0.0) distance = 0.0;

				const double maxDistFade = layer.maxDistance;
				double volFade = 1.0;
				if (maxDistFade > 1e-30 && distance > 0.0)
				{
					double t = distance / maxDistFade;
					if (t >= 1.0) continue;
					t = t * t * (3.0 - 2.0 * t);
					volFade = 1.0 - t;
				}

				const double blur = layer.blur;
				double distForFalloff = distance;
				if (blur > 1e-20)
				{
					const double blurScale = blur * (0.4 + 0.65 * fabs(layer.relativeSize));
					distForFalloff = std::sqrt(distance * distance + blurScale * blurScale);
				}
				double effectiveSharpening =
					layer.sharpening / (1.0 + blur * 1.75 + blur * blur * 0.4);
				const double effectiveDist = distForFalloff;
				double falloff;
				switch (layer.falloffType)
				{
					case params::singleTrapLightFalloffInverseSquare:
						falloff = 1.0 / (1.0 + effectiveDist * effectiveDist * effectiveSharpening);
						break;
					case params::singleTrapLightFalloffLinear:
						falloff = std::max(
							0.0, 1.0 - effectiveDist * std::sqrt(effectiveSharpening) * 1.35);
						break;
					case params::singleTrapLightFalloffExponential:
						falloff = exp(-effectiveDist * std::sqrt(effectiveSharpening) * 1.15);
						break;
					case params::singleTrapLightFalloffSmoothstep:
					{
						double edge = 1.0 / std::sqrt(effectiveSharpening + 1e-30);
						double tSmooth = effectiveDist / edge;
						if (tSmooth >= 1.0) falloff = 0.0;
						else if (tSmooth <= 0.0) falloff = 1.0;
						else falloff = 1.0 - tSmooth * tSmooth * (3.0 - 2.0 * tSmooth);
						break;
					}
					default:
						falloff = exp(-effectiveDist * effectiveDist * effectiveSharpening);
						break;
				}
				if (layer.softness > 0.0 && distForFalloff > 0.0)
					falloff *= exp(-distForFalloff * layer.softness * 1.2);
				double solidBoost = (rawDistance < 0.0) ? layer.solidIntensity : 1.0;
				double innerGlow = 1.0;
				if (rawDistance < 0.0)
				{
					double depth = std::min(1.0, -rawDistance / 2.0);
					innerGlow = 1.0 + layer.softness * depth * 3.2;
				}
				float light =
					float(layer.intensity * layer.visibility * falloff * solidBoost * innerGlow * volFade);
				double gradT = 0.0;
				if (layer.maxDistance > 1e-30)
					gradT = std::min(1.0, distance / layer.maxDistance);
				if (gradT > 1.0) gradT = 1.0;
				float gradTf = float(gradT);
				sRGBFloat layerColor;
				layerColor.R = layer.color.R * (1.0f - gradTf) + layer.gradientColor.R * gradTf;
				layerColor.G = layer.color.G * (1.0f - gradTf) + layer.gradientColor.G * gradTf;
				layerColor.B = layer.color.B * (1.0f - gradTf) + layer.gradientColor.B * gradTf;
				// Orbit mode: surface shader uses fractal orbitTrapR; volumetric uses distance as a cheap proxy.
				if (layer.coloringMode == params::singleTrapLightColoringDistance
						|| layer.coloringMode == params::singleTrapLightColoringOrbitTrap)
				{
					layerColor.R *= (1.0f - gradTf);
					layerColor.G *= (1.0f - gradTf);
					layerColor.B *= (1.0f - gradTf);
				}

				const float cr = light * layerColor.R;
				const float cg = light * layerColor.G;
				const float cb = light * layerColor.B;
				switch (combineMode)
				{
					case 1: // Max per channel
						stlR = std::max(stlR, cr);
						stlG = std::max(stlG, cg);
						stlB = std::max(stlB, cb);
						break;
					case 2: // Screen
						stlR = stlR + cr - stlR * cr;
						stlG = stlG + cg - stlG * cg;
						stlB = stlB + cb - stlB * cb;
						break;
					case 3: // Average
						stlR = (stlR * float(processedLayers) + cr) / float(processedLayers + 1);
						stlG = (stlG * float(processedLayers) + cg) / float(processedLayers + 1);
						stlB = (stlB * float(processedLayers) + cb) / float(processedLayers + 1);
						processedLayers++;
						break;
					case 4: // Multiply
						if (processedLayers == 0)
						{
							stlR = cr;
							stlG = cg;
							stlB = cb;
						}
						else
						{
							stlR = stlR * cr;
							stlG = stlG * cg;
							stlB = stlB * cb;
						}
						processedLayers++;
						break;
					default: // Add
						stlR += cr;
						stlG += cg;
						stlB += cb;
						break;
				}
			}

			output.R += stlR * float(step);
			output.G += stlG * float(step);
			output.B += stlB * float(step);
		}

		// Pattern line traps (volumetric) — same world-space lines as surface shader
		if (params->patternLineTraps.enabled)
		{
			const int soloPl = params->patternLineTraps.soloLayerIndex;
			for (int pi = 0; pi < PATTERN_LINE_TRAP_COUNT; pi++)
			{
				if (soloPl > 0 && soloPl != pi + 1) continue;
				const sPatternLineTrapLayer &layer = params->patternLineTraps.layers[pi];
				if (!layer.enabled) continue;

				sPatternLineTrapLayer effLayer = layer;
				const double camDist = (params->camera - layer.position).Length();
				effLayer.radius = PatternLineTrapEffectiveRadius(layer, camDist);

				CVector3 delta = point - layer.position;
				delta = effLayer.mRotRotation.RotateVector(delta);

				if (effLayer.maxDistance > 1e-30 || effLayer.segmentHalfLength > 1e-30)
				{
					double margin =
						PatternLineTrapProfileExtent(effLayer) + fabs(effLayer.edgeSoftness);
					if (effLayer.maxDistance > 1e-30) margin += effLayer.maxDistance;
					if (effLayer.segmentHalfLength > 1e-30) margin += effLayer.segmentHalfLength;
					if (delta.Length() > margin * 2.8) continue;
				}

				double axialFade = 1.0;
				if (effLayer.segmentHalfLength > 1e-30)
				{
					const double ax = fabs(delta.x);
					double t = ax / effLayer.segmentHalfLength;
					if (t >= 1.0) continue;
					t = t * t * (3.0 - 2.0 * t);
					axialFade = 1.0 - t;
				}

				const double rawDist = PatternLineTrapProfileRawDist(effLayer, delta.y, delta.z);
				const double wallDist = PatternLineTrapWallDist(effLayer, rawDist);

				double volFade = 1.0;
				if (effLayer.maxDistance > 1e-30)
				{
					double t = wallDist / effLayer.maxDistance;
					if (t >= 1.0) continue;
					t = t * t * (3.0 - 2.0 * t);
					volFade = 1.0 - t;
				}

				const double falloff = PatternLineTrapGlowFalloff(effLayer, wallDist);
				const double intens = effLayer.intensity * falloff * volFade * axialFade;
				const double tGrad = PatternLineTrapGradientT(effLayer, wallDist);
				const sRGBFloat grad = PatternLineTrapGradientRgb(effLayer, tGrad);

				if (params->patternLineTraps.combineMode == 0)
				{
					output.R += float(intens * double(grad.R) * step);
					output.G += float(intens * double(grad.G) * step);
					output.B += float(intens * double(grad.B) * step);
				}
				else
				{
					output.R = std::max(output.R, float(intens * double(grad.R) * step));
					output.G = std::max(output.G, float(intens * double(grad.G) * step));
					output.B = std::max(output.B, float(intens * double(grad.B) * step));
				}
			}
		}

		// Glow spheres volumetric contribution
		sRGBFloat glowSphereColor = glow_sphere::GlowSphereShaderMulti(point, params->frameNo,
			&params->glowSphere1, &params->glowSphere2, &params->glowSphere3, &params->glowSphere4);
		if (glowSphereColor.R > 0.0f || glowSphereColor.G > 0.0f || glowSphereColor.B > 0.0f)
		{
			output.R += glowSphereColor.R * float(step);
			output.G += glowSphereColor.G * float(step);
			output.B += glowSphereColor.B * float(step);
			output.A += (glowSphereColor.R + glowSphereColor.G + glowSphereColor.B) / 3.0f * float(step);
		}

		if (totalOpacity > 1.0f) totalOpacity = 1.0f;
		if (output.A > 1.0f) output.A = 1.0f;
		(*opacityOut).R = totalOpacity;
		(*opacityOut).G = totalOpacity;
		(*opacityOut).B = totalOpacity;

		if (totalOpacity > 0.98f || transmittance < 0.02f) end = true;
		if (end) break;

	} // next stepCount

	return output;
}

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
 * Single Trap Lights — CPU surface shader
 */

#include "compute_fractal.hpp"
#include "fractparams.hpp"
#include "render_worker.hpp"
#include "single_trap_lights.hpp"

#include <algorithm>
#include <cmath>

sRGBAFloat cRenderWorker::SingleTrapLights(
	const sShaderInputData &input, sRGBAFloat surfaceColor) const
{
	Q_UNUSED(surfaceColor)

	sRGBAFloat result(0.0, 0.0, 0.0, 0.0);

	if (!params->singleTrapLights.enabled) return result;

	bool needOrbitColor = false;
	const int soloLayer = params->singleTrapLights.soloLayerIndex;
	for (int j = 0; j < params->singleTrapLights.activeLayerCount; j++)
	{
		if (soloLayer > 0 && soloLayer != j + 1) continue;
		const sSingleTrapLightLayer &lj = params->singleTrapLights.layers[j];
		if (lj.enabled && lj.coloringMode == params::singleTrapLightColoringOrbitTrap)
		{
			needOrbitColor = true;
			break;
		}
	}
	double orbitTrapRForColor = 0.0;
	if (needOrbitColor)
	{
		sCommonParams commonWithPosition = CommonParamsWithAdjustedFakeLightsOrbitTrap();
		sFractalIn fractIn(input.point, params->minN, -1, 1, 0, &commonWithPosition, -1, false);
		sFractalOut fractOut;
		fractOut.normal = CVector3(0, 0, 0);
		Compute<fractal::calcModeOrbitTrap>(*fractal, nullptr, fractIn, &fractOut);
		orbitTrapRForColor = fractOut.orbitTrapR;
	}

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
			const double dx = input.point.x - effectivePosition.x;
			const double dy = input.point.y - effectivePosition.y;
			const double dz = input.point.z - effectivePosition.z;
			if (sqrt(dx * dx + dy * dy + dz * dz) > margin * 2.8) continue;
		}

		CVector3 adjustedPoint = input.point - effectivePosition + layer.position * layer.relativeSize;
		CVector3 scaledPoint = adjustedPoint / layer.relativeSize;
		sSingleTrapLightLayer animatedLayer = layer;
		animatedLayer.size = animatedSize;
		double rawDistance = SingleTrapLightDistance(scaledPoint, animatedLayer) * layer.relativeSize;
		double distance = rawDistance;
		if (distance < 0.0) distance = 0.0;

		// Soft fade from surface to maxDistance (eliminates hard edge). maxDistance <= 0 → no cap.
		const double maxDistFade = layer.maxDistance;
		double fade = 1.0;
		if (maxDistFade > 1e-30 && distance > 0.0)
		{
			double t = distance / maxDistFade;
			if (t >= 1.0) continue;
			// Smoothstep for gentle fade: t^2 * (3 - 2t)
			t = t * t * (3.0 - 2.0 * t);
			fade = 1.0 - t;
		}

		// Blur: widen the falloff (distance mollification) + soften sharpening — "vervaging" must read in-image.
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
				double t = effectiveDist / edge;
				if (t >= 1.0) falloff = 0.0;
				else if (t <= 0.0) falloff = 1.0;
				else falloff = 1.0 - t * t * (3.0 - 2.0 * t);
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
		double intensity = layer.intensity * layer.visibility * falloff * solidBoost * innerGlow * fade;

		double gradT = 0.0;
		if (layer.coloringMode == params::singleTrapLightColoringOrbitTrap)
		{
			const double mdBlend = std::max(layer.maxDistance, 1e-20);
			gradT = orbitTrapRForColor / (orbitTrapRForColor + mdBlend);
		}
		else if (layer.maxDistance > 1e-30)
		{
			gradT = std::min(1.0, distance / layer.maxDistance);
		}
		if (gradT > 1.0) gradT = 1.0;

		float gradTf = float(gradT);
		sRGBFloat layerColor;
		layerColor.R = layer.color.R * (1.0f - gradTf) + layer.gradientColor.R * gradTf;
		layerColor.G = layer.color.G * (1.0f - gradTf) + layer.gradientColor.G * gradTf;
		layerColor.B = layer.color.B * (1.0f - gradTf) + layer.gradientColor.B * gradTf;
		if (layer.coloringMode == params::singleTrapLightColoringDistance
				|| layer.coloringMode == params::singleTrapLightColoringOrbitTrap)
		{
			layerColor.R *= (1.0f - gradTf);
			layerColor.G *= (1.0f - gradTf);
			layerColor.B *= (1.0f - gradTf);
		}

		const float cr = float(intensity * double(layerColor.R));
		const float cg = float(intensity * double(layerColor.G));
		const float cb = float(intensity * double(layerColor.B));
		if (params->singleTrapLights.combineMode == params::singleTrapLightsCombineMax)
		{
			result.R = std::max(result.R, cr);
			result.G = std::max(result.G, cg);
			result.B = std::max(result.B, cb);
		}
		else
		{
			result.R += cr;
			result.G += cg;
			result.B += cb;
		}
	}

	return result;
}

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
 * cRenderWorker::LightShading method - calculates auxiliary light sources
 */
#include "common_math.h"
#include "fractparams.hpp"
#include "lights.hpp"
#include "material.h"
#include "render_worker.hpp"

sRGBAFloat cRenderWorker::LightShading(sShaderInputData &input, sRGBAFloat surfaceColor,
	const cLight *light, sGradientsCollection *gradients, sRGBAFloat *outSpecular,
	sRGBAFloat *outShadow) const
{
	sRGBAFloat shading;

	double distance = 0.0;
	CVector3 lightVector = light->CalculateLightVector(
		input.point, input.delta, params->resolution, params->viewDistanceMax, distance, &params->primitives);

	// intensity of lights is divided by 6 because of backward compatibility. There was an error
	// where number of light was always 24
	// float intensity = 100.0f * light->intensity / light->Decay(distance) / number / 6;
	float intensity;
	if (light->type == cLight::lightDirectional)
	{
		intensity = light->intensity;
	}
	else if (light->type == cLight::lightConical)
	{
		intensity = light->intensity * 10.0;
	}
	else
	{
		intensity = 100.0f * light->intensity / light->Decay(distance) / 6.0f;
	}

	sRGBFloat textureColor;
	intensity *= light->CalculateCone(input.point, lightVector, textureColor);

	float shade = input.normal.Dot(lightVector);
	if (shade < 0) shade = 0;
	shade = 1.0f - input.material->shading + shade * input.material->shading;

	shade = shade * intensity;
	if (shade > 500.0f) shade = 500.0f;

	// specular
	sRGBAFloat specular =
		SpecularHighlightCombined(input, lightVector, surfaceColor, gradients->diffuse);
	specular.R *= intensity;
	specular.G *= intensity;
	specular.B *= intensity;

	if (input.material->useColorsFromPalette && input.material->specularGradientEnable)
	{
		specular.R *= gradients->specular.R;
		specular.G *= gradients->specular.G;
		specular.B *= gradients->specular.B;
	}

	float specularMax = dMax(specular.R, specular.G, specular.B);

	// calculate shadow
	sRGBAFloat auxShadow(1.0, 1.0, 1.0, 1.0);
	if (light->castShadows)
	{
		if (shade > 0.01f || specularMax > 0.01f)
		{
			auxShadow = AuxShadow(input, light, distance, lightVector);
			specular.R *= auxShadow.R;
			specular.G *= auxShadow.G;
			specular.B *= auxShadow.B;
		}
		else
		{
			auxShadow = sRGBAFloat();
			specular = sRGBAFloat();
		}
	}

	// === AUX LIGHTS: Apply color temperature ===
	sRGBFloat lightColor = light->color;
	if (light->useColorTemperature)
	{
		// Match OpenCL KelvinToRGB_CL: invalid/low values would make log(temp) undefined on CPU
		const float kelvin = qBound(1000.0f, light->colorTemperature, 40000.0f);
		float temp = kelvin / 100.0f;
		float r, g, b;
		if (temp <= 66.0f) r = 255.0f;
		else { r = 329.698727446f * pow(temp - 60.0f, -0.1332047592f); r = qBound(0.0f, r, 255.0f); }
		if (temp <= 66.0f) { g = 99.4708025861f * log(temp) - 161.1195681661f; g = qBound(0.0f, g, 255.0f); }
		else { g = 288.1221695283f * pow(temp - 60.0f, -0.0755148492f); g = qBound(0.0f, g, 255.0f); }
		if (temp >= 66.0f) b = 255.0f;
		else if (temp <= 19.0f) b = 0.0f;
		else { b = 138.5177312231f * log(temp - 10.0f) - 305.0447927307f; b = qBound(0.0f, b, 255.0f); }
		lightColor = sRGBFloat(r / 255.0f, g / 255.0f, b / 255.0f);
	}

	shading.R = shade * lightColor.R * auxShadow.R * textureColor.R;
	shading.G = shade * lightColor.G * auxShadow.G * textureColor.G;
	shading.B = shade * lightColor.B * auxShadow.B * textureColor.B;

	// === AUX LIGHTS: Atmospheric scattering for directional lights ===
	if (light->type == cLight::lightDirectional && light->atmosphericDensity > 0.0f)
	{
		CVector3 viewDir = input.viewVector;
		viewDir.Normalize();
		float cosTheta = viewDir.Dot(lightVector);
		float phase = 0.75f * (1.0f + cosTheta * cosTheta);
		float atten = 1.0f - exp(-distance * light->atmosphericDensity * 0.01f);
		float intensity_atm = light->atmosphericScatteringIntensity;
		// Single multiply by tint; per-channel 0.28/0.58/1.0 on top of a blueish tint
		// oversaturated the B channel when atten -> 1 (directional, large distance).
		const float a = phase * atten * intensity_atm;
		shading.R += a * light->atmosphericColor.R;
		shading.G += a * light->atmosphericColor.G;
		shading.B += a * light->atmosphericColor.B;
	}

	outSpecular->R = specular.R * lightColor.R * textureColor.R;
	outSpecular->G = specular.G * lightColor.G * textureColor.G;
	outSpecular->B = specular.B * lightColor.B * textureColor.B;

	*outShadow = auxShadow;

	return shading;
}

/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2018-22 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * calculation of auxiliary light sources
 */

#ifdef AUX_LIGHTS

float3 CalculateBeam(__global sLightCl *light, float3 point1, float3 point2, int *randomSeed)
{
	if (light->type == lightBeam)
	{
		float3 direction = point2 - point1;
		return point1 + direction * Random(10000, randomSeed) / 10000.0f;
	}
	else
	{
		return point1;
	}
}

float3 CalculateLightVector(__global sLightCl *light, float3 point, float delta, float resolution,
	float viewDistanceMax, float *outDistance, int *randomSeed, sRenderData *renderData)
{
	float3 lightVector;
	if (light->type == lightDirectional)
	{
		lightVector = light->lightDirection;
		if (light->penetrating)
		{
			*outDistance = delta / resolution;
		}
		else
		{
			*outDistance = viewDistanceMax;
		}
	}
	else if (light->type == lightPrimitive && light->primitiveId >= 0)
	{
		// Find primitive with matching objectId
		float3 primitiveCenter = point; // fallback
		bool found = false;

		for (int i = 0; i < renderData->numberOfPrimitives; i++)
		{
			if (renderData->primitives[i].object.objectId == light->primitiveId && renderData->primitives[i].object.enable)
			{
				primitiveCenter = renderData->primitives[i].object.position;
				found = true;
				break;
			}
		}

		if (found)
		{
			// Use primitive center as light source
			float3 d = primitiveCenter - point;
			lightVector = normalize(d);
			*outDistance = length(d);
		}
		else
		{
			// Primitive not found, fallback
			lightVector = (float3)(0.0f, 1.0f, 0.0f);
			*outDistance = viewDistanceMax;
		}
	}
	else
	{
		float3 d = CalculateBeam(light, light->position, light->target, randomSeed) - point;
		lightVector = normalize(d);
		*outDistance = length(d);
	}
	return lightVector;
}

float LightDecay(float dist, enumLightDecayFunctionCl decayFunction)
{
	if (decayFunction == lightDecaySmooth)
		return (1.0f + dist) * (1.0f + dist);  // smooth: 1/(1+d)²
	if (decayFunction == lightDecayPhysical)
		return dist * dist + 1.0f;  // physical: 1/(d²+1)
	return pown(dist, (int)decayFunction + 1);
}

float CalculateLightCone(__global sLightCl *light, sRenderData *renderData, float3 point,
	float3 lightVector, float3 *outColor)
{
	float3 color = 1.0f;
	float intensity = 1.0f;

	if (light->type == lightConical)
	{
#ifdef LIGHT_CONICAL
		if (dot(point - light->position, light->lightDirection) > 0.0f)
		{
			intensity = 0.0f;
		}
		else
		{
			float tipSize = light->size * 0.5f;
			float distanceToAxis = length(cross(point - light->position, light->lightDirection));
			float cone = length(point - light->position);
			float cone1 = cone * light->coneRatio;
			float cone2 = cone * light->coneSoftRatio;
			if (distanceToAxis < tipSize + cone1)
			{
				intensity = 1.0f;
			}
			else if (distanceToAxis < tipSize + cone2)
			{
				intensity = (tipSize + cone2 - distanceToAxis) / (cone2 - cone1);
			}
			else
			{
				intensity = 0.0f;
			}

			intensity = intensity * (tipSize * tipSize) / ((tipSize + cone1) * (tipSize + cone1));
		}
#endif // LIGHT_CONICAL
	}
	else if (light->type == lightProjection)
	{
#ifdef USE_LIGHT_TEXTURE
		if (light->colorTextureIndex >= 0)
		{
			float axiality = dot(lightVector, light->lightDirection);
			if (axiality > 0.0f && light->projectionHorizontalRatio > 0.0f
					&& light->projectionVerticalRatio > 0.0f)
			{
				float texX =
					dot(light->lightRightVector, lightVector) / light->projectionHorizontalRatio / axiality
					+ 0.5f;
				float texY =
					dot(light->lightTopVector, lightVector) / light->projectionVerticalRatio / axiality
					+ 0.5f;

				if (light->repeatTexture || (texX > 0.0f && texX < 1.0f && texY > 0.0f && texY < 1.0f))
				{
					float2 texturePoint = (float2){texX, texY};

					int2 textureSize = renderData->textureSizes[light->colorTextureIndex];
					__global uchar4 *texture = renderData->textures[light->colorTextureIndex];

					float3 texOut = BicubicInterpolation(
						texturePoint.x, texturePoint.y, texture, textureSize.x, textureSize.y);

					color = texOut;
					intensity = 1.0f;
				}
				else
				{
					color = 0.0f;
					intensity = 0.0f;
				}
			}
			else
			{
				color = 0.0f;
				intensity = 0.0f;
			}
		}
#endif // USE_LIGHT_TEXTURE
	}

	*outColor = color;
	return intensity;
}

// === AUX LIGHTS: Kelvin to RGB ===
float3 KelvinToRGB_CL(float kelvin)
{
	kelvin = clamp(kelvin, 1000.0f, 40000.0f);
	float temp = kelvin / 100.0f;
	float r, g, b;
	if (temp <= 66.0f) r = 255.0f;
	else { r = 329.698727446f * pow(temp - 60.0f, -0.1332047592f); r = clamp(r, 0.0f, 255.0f); }
	if (temp <= 66.0f) { g = 99.4708025861f * log(temp) - 161.1195681661f; g = clamp(g, 0.0f, 255.0f); }
	else { g = 288.1221695283f * pow(temp - 60.0f, -0.0755148492f); g = clamp(g, 0.0f, 255.0f); }
	if (temp >= 66.0f) b = 255.0f;
	else if (temp <= 19.0f) b = 0.0f;
	else { b = 138.5177312231f * log(temp - 10.0f) - 305.0447927307f; b = clamp(b, 0.0f, 255.0f); }
	return (float3)(r / 255.0f, g / 255.0f, b / 255.0f);
}

// === AUX LIGHTS: Atmospheric scattering ===
float3 CalculateAtmosphericScattering_CL(float3 viewDir, float3 lightDir,
	float dist, float density, float intensity, float3 tint)
{
	if (density <= 0.0f) return (float3)(0.0f, 0.0f, 0.0f);
	float cosTheta = dot(viewDir, lightDir);
	float phase = 0.75f * (1.0f + cosTheta * cosTheta);
	float atten = 1.0f - exp(-dist * density * 0.01f);
	float a = phase * atten * intensity;
	return a * tint;
}

float3 LightShading(__constant sClInConstants *consts, sRenderData *renderData,
	sShaderInputDataCl *input, sClCalcParams *calcParam, float3 surfaceColor,
	__global sLightCl *light, sClGradientsCollection *gradients, float3 *outSpecular,
	float3 *outShadow)
{
	float3 shading = 0.0f;

	float dist = 0.0f;

	float3 lightVector = CalculateLightVector(light, input->point, input->delta,
		consts->params.resolution, consts->params.viewDistanceMax, &dist, &input->randomSeed, renderData);

	float intensity = 0.0f;
	if (light->type == lightDirectional)
	{
		intensity = light->intensity;
	}
	else if (light->type == lightConical)
	{
		intensity = 10.0f * light->intensity;
	}
	else
	{
		intensity = 100.0f * light->intensity / LightDecay(dist, light->decayFunction) / 6.0f;
	}

	float3 textureColor;
	intensity *= CalculateLightCone(light, renderData, input->point, lightVector, &textureColor);

	float shade = dot(input->normal, lightVector);
	if (shade < 0.0f) shade = 0.0f;
	shade = 1.0f - input->material->shading + shade * input->material->shading;

	shade = shade * intensity;
	if (shade > 500.0f) shade = 500.0f;

	// specular
	float3 specular =
		SpecularHighlightCombined(input, calcParam, lightVector, surfaceColor, gradients) * intensity;

#ifdef USE_SPECULAR_GRADIENT
	if (input->material->useColorsFromPalette && input->material->specularGradientEnable)
	{
		specular *= gradients->specular;
	}
#endif

	float specularMax = max(max(specular.s0, specular.s1), specular.s2);

	// calculate shadow

	float3 auxShadow = 1.0f;
#ifdef SHADOWS
	if (light->castShadows)
	{
		if (shade > 0.001f || specularMax > 0.001f)
		{
			auxShadow =
				AuxShadow(consts, renderData, input, light, dist, lightVector, calcParam, light->intensity);
			specular *= auxShadow;
		}
		else
		{
			auxShadow = 0.0f;
			specular = 0.0f;
		}
	}
#endif // SHADOWS

	// === AUX LIGHTS: Apply color temperature ===
	float3 lightColor = light->color;
	if (light->useColorTemperature)
		lightColor = KelvinToRGB_CL(light->colorTemperature);

	shading = shade * lightColor * auxShadow * textureColor;

	// === AUX LIGHTS: Atmospheric scattering for directional lights ===
	if (light->type == lightDirectional && light->atmosphericDensity > 0.0f)
	{
		float3 viewDir = normalize(input->viewVector);
		float3 atmosphericContrib = CalculateAtmosphericScattering_CL(
			viewDir, lightVector, dist, light->atmosphericDensity,
			light->atmosphericScatteringIntensity, light->atmosphericColor);
		shading += atmosphericContrib;
	}

	*outSpecular = specular * lightColor * textureColor;

	*outShadow = auxShadow;

	return shading;
}
#endif // AUX_LIGHTS

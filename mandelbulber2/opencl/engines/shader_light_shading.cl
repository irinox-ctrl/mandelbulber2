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
	float viewDistanceMax, float *outDistance, int *randomSeed)
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
		intensity = 0.0f;
		color = 0.0f;
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

				// Apply UV transform: scale, rotation, offset
				{
					float u = texX - 0.5f;
					float v = texY - 0.5f;
					u *= light->projectionParams1.z;
					v *= light->projectionParams1.w;
					float rot = light->projectionParams2.x;
					if (rot != 0.0f)
					{
						float rad = rot * 3.14159265f / 180.0f;
						float c = cos(rad);
						float s = sin(rad);
						float ur = u * c - v * s;
						float vr = u * s + v * c;
						u = ur;
						v = vr;
					}
					u += light->projectionParams1.x;
					v += light->projectionParams1.y;
					texX = u + 0.5f;
					texY = v + 0.5f;
				}

				int repeatMode = (int)light->projectionParams2.y;
				bool useRepeat = light->repeatTexture || repeatMode != 0;

				float fade = 1.0f;
				int outOfBounds = 0;

				if (repeatMode == 0) // Clamp
				{
					if (light->projectionSoftEdge > 0.0f)
					{
						float effectiveEdge = min(light->projectionSoftEdge, 0.5f);
						float fx, fy;
						if (texX <= 0.0f || texX >= 1.0f) fx = 0.0f;
						else if (texX < effectiveEdge) fx = texX / effectiveEdge;
						else if (texX > 1.0f - effectiveEdge) fx = (1.0f - texX) / effectiveEdge;
						else fx = 1.0f;

						if (texY <= 0.0f || texY >= 1.0f) fy = 0.0f;
						else if (texY < effectiveEdge) fy = texY / effectiveEdge;
						else if (texY > 1.0f - effectiveEdge) fy = (1.0f - texY) / effectiveEdge;
						else fy = 1.0f;

						fade = clamp(fx * fy, 0.0f, 1.0f);
					}

					if (texX <= 0.0f || texX >= 1.0f || texY <= 0.0f || texY >= 1.0f)
					{
						if (fade <= 0.0f) outOfBounds = 1;
					}
				}
				else if (repeatMode == 1) // Repeat
				{
					texX = texX - floor(texX);
					texY = texY - floor(texY);
				}
				else if (repeatMode == 2) // Mirror
				{
					texX = fabs(fmod(texX, 2.0f) - 1.0f);
					texY = fabs(fmod(texY, 2.0f) - 1.0f);
				}

				if (!outOfBounds)
				{
					float sampleX = (repeatMode == 0) ? clamp(texX, 0.0f, 1.0f) : texX;
					float sampleY = (repeatMode == 0) ? clamp(texY, 0.0f, 1.0f) : texY;

					float2 texturePoint = (float2){sampleX, sampleY};

					int2 textureSize = renderData->textureSizes[light->colorTextureIndex];
					__global uchar4 *texture = renderData->textures[light->colorTextureIndex];

					float3 texOut = BicubicInterpolation(
						texturePoint.x, texturePoint.y, texture, textureSize.x, textureSize.y);

					if (light->projectionUseAsMask)
					{
						float luminance = dot(texOut, (float3)(0.299f, 0.587f, 0.114f));
						color = 1.0f;
						intensity = luminance * fade;
					}
					else
					{
						color = texOut;
						intensity = fade;
					}
				}
			}
		}
#endif // USE_LIGHT_TEXTURE
	}

	*outColor = color;
	return intensity;
}

float3 LightShading(__constant sClInConstants *consts, sRenderData *renderData,
	sShaderInputDataCl *input, sClCalcParams *calcParam, float3 surfaceColor,
	__global sLightCl *light, sClGradientsCollection *gradients, float3 *outSpecular,
	float3 *outShadow)
{
	float3 shading = 0.0f;

	float dist = 0.0f;

	float3 lightVector = CalculateLightVector(light, input->point, input->delta,
		consts->params.resolution, consts->params.viewDistanceMax, &dist, &input->randomSeed);

	float intensity = 0.0f;
	if (light->type == lightDirectional)
	{
		intensity = light->intensity;
	}
	else if (light->type == lightConical || light->type == lightProjection)
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

	shading = shade * light->color * auxShadow * textureColor;
	*outSpecular = specular * light->color * textureColor;

	*outShadow = auxShadow;

	return shading;
}
#endif // AUX_LIGHTS

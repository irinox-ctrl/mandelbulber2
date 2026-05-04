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

float3 CalculateBeam(__global sLightCl *light, float3 point1, float3 point2, int *randomSeed,
	float *outFade)
{
	if (light->type == lightBeam)
	{
		float3 direction = point2 - point1;
		float3 pointOnLine = point1 + direction * Random(10000, randomSeed) / 10000.0f;
		float fade = 1.0f;

		if (light->beamRadius > 0.0f)
		{
			// Generate a random offset perpendicular to the beam direction
			float3 dirNormalized = normalize(direction);

			// Find a perpendicular vector
			float3 perp1;
			if (fabs(dirNormalized.z) < 0.99f)
			{
				perp1 = cross((float3)(0.0f, 0.0f, 1.0f), dirNormalized);
			}
			else
			{
				perp1 = cross((float3)(1.0f, 0.0f, 0.0f), dirNormalized);
			}
			perp1 = normalize(perp1);
			float3 perp2 = cross(dirNormalized, perp1);

			// Uniform distribution over disk: r = radius * sqrt(random)
			float angle = Random(10000, randomSeed) / 10000.0f * 2.0f * M_PI_F;
			float r = light->beamRadius * sqrt(Random(10000, randomSeed) / 10000.0f);

			pointOnLine += perp1 * cos(angle) * r + perp2 * sin(angle) * r;

			// Calculate radial fade
			if (light->beamSoftEdge > 0.0f)
			{
				float innerRadius = light->beamRadius * (1.0f - light->beamSoftEdge);
				if (r <= innerRadius)
				{
					fade = 1.0f;
				}
				else if (r < light->beamRadius)
				{
					fade = 1.0f - (r - innerRadius) / (light->beamRadius * light->beamSoftEdge);
				}
				else
				{
					fade = 0.0f;
				}
			}
		}

		if (outFade) *outFade = fade;
		return pointOnLine;
	}
	else
	{
		if (outFade) *outFade = 1.0f;
		return point1;
	}
}

float3 CalculateLightVector(__global sLightCl *light, float3 point, float delta, float resolution,
	float viewDistanceMax, float *outDistance, int *randomSeed, float *outBeamFade)
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
		if (outBeamFade) *outBeamFade = 1.0f;
	}
	else
	{
		float fade = 1.0f;
		float3 d = CalculateBeam(light, light->position, light->target, randomSeed, &fade) - point;
		lightVector = normalize(d);
		*outDistance = length(d);
		if (outBeamFade) *outBeamFade = fade;
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
				// Apply Z transforms to axiality (depth scaling/offset)
				float effectiveAxiality = axiality * light->projectionParams3.y + light->projectionParams3.x;
				if (effectiveAxiality > 0.0f)
				{
					// Rotate lightVector around light axes for 3D texture rotation
					float3 rotatedLightVector = lightVector;
					float rotX = light->projectionParams3.z;
					if (rotX != 0.0f)
					{
						float rad = rotX * 3.14159265f / 180.0f;
						float c = cos(rad);
						float s = sin(rad);
						// rotate around lightRightVector
						float3 axis = light->lightRightVector;
						rotatedLightVector =
							rotatedLightVector * c + cross(axis, rotatedLightVector) * s
							+ axis * dot(axis, rotatedLightVector) * (1.0f - c);
					}
					float rotY = light->projectionParams3.w;
					if (rotY != 0.0f)
					{
						float rad = rotY * 3.14159265f / 180.0f;
						float c = cos(rad);
						float s = sin(rad);
						// rotate around lightTopVector
						float3 axis = light->lightTopVector;
						rotatedLightVector =
							rotatedLightVector * c + cross(axis, rotatedLightVector) * s
							+ axis * dot(axis, rotatedLightVector) * (1.0f - c);
					}

					float texX =
						dot(light->lightRightVector, rotatedLightVector) / light->projectionHorizontalRatio / effectiveAxiality
						+ 0.5f;
					float texY =
						dot(light->lightTopVector, rotatedLightVector) / light->projectionVerticalRatio / effectiveAxiality
						+ 0.5f;

						// Apply UV transform for color texture
						float colorTexX = texX;
						float colorTexY = texY;
						{
							float u = colorTexX - 0.5f;
								float v = colorTexY - 0.5f;
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
								colorTexX = u + 0.5f;
								colorTexY = v + 0.5f;
							}

							// Apply UV transform for alpha texture
							float alphaTexX = texX;
							float alphaTexY = texY;
							{
								float u = alphaTexX - 0.5f;
								float v = alphaTexY - 0.5f;
								u *= light->alphaTextureParams1.z;
								v *= light->alphaTextureParams1.w;
								float rot = light->alphaTextureParams2.x;
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
								u += light->alphaTextureParams1.x;
								v += light->alphaTextureParams1.y;
								alphaTexX = u + 0.5f;
								alphaTexY = v + 0.5f;
							}

							int repeatMode = (int)light->projectionParams2.y;
							bool useRepeat = light->repeatTexture || repeatMode != 0;

							float fade = 1.0f;
							float alphaFade = 1.0f;
							int outOfBounds = 0;

							if (repeatMode == 0) // Clamp
							{
								if (light->projectionSoftEdge > 0.0f)
								{
									float effectiveEdge = min(light->projectionSoftEdge, 0.5f);
									float fx, fy;
									if (colorTexX <= 0.0f || colorTexX >= 1.0f) fx = 0.0f;
									else if (colorTexX < effectiveEdge) fx = colorTexX / effectiveEdge;
									else if (colorTexX > 1.0f - effectiveEdge) fx = (1.0f - colorTexX) / effectiveEdge;
									else fx = 1.0f;

									if (colorTexY <= 0.0f || colorTexY >= 1.0f) fy = 0.0f;
									else if (colorTexY < effectiveEdge) fy = colorTexY / effectiveEdge;
									else if (colorTexY > 1.0f - effectiveEdge) fy = (1.0f - colorTexY) / effectiveEdge;
									else fy = 1.0f;

									fade = clamp(fx * fy, 0.0f, 1.0f);
								}

								if (colorTexX <= 0.0f || colorTexX >= 1.0f || colorTexY <= 0.0f || colorTexY >= 1.0f)
								{
									if (fade <= 0.0f) outOfBounds = 1;
								}
							}
							else if (repeatMode == 1) // Repeat
							{
								colorTexX = colorTexX - floor(colorTexX);
								colorTexY = colorTexY - floor(colorTexY);
							}
							else if (repeatMode == 2) // Mirror
							{
								colorTexX = fabs(fmod(colorTexX, 2.0f) - 1.0f);
								colorTexY = fabs(fmod(colorTexY, 2.0f) - 1.0f);
							}

							int alphaRepeatMode = (int)light->alphaTextureParams2.y;
							if (alphaRepeatMode == 1) // Repeat
							{
								alphaTexX = alphaTexX - floor(alphaTexX);
								alphaTexY = alphaTexY - floor(alphaTexY);
							}
							else if (alphaRepeatMode == 2) // Mirror
							{
								alphaTexX = fabs(fmod(alphaTexX, 2.0f) - 1.0f);
								alphaTexY = fabs(fmod(alphaTexY, 2.0f) - 1.0f);
							}
							else if (alphaRepeatMode == 0) // Clamp
							{
								float alphaSoftEdge = light->alphaTextureParams2.z;
								if (alphaSoftEdge > 0.0f)
								{
									float effectiveEdge = min(alphaSoftEdge, 0.5f);
									float fx, fy;
									if (alphaTexX <= 0.0f || alphaTexX >= 1.0f) fx = 0.0f;
									else if (alphaTexX < effectiveEdge) fx = alphaTexX / effectiveEdge;
									else if (alphaTexX > 1.0f - effectiveEdge) fx = (1.0f - alphaTexX) / effectiveEdge;
									else fx = 1.0f;

									if (alphaTexY <= 0.0f || alphaTexY >= 1.0f) fy = 0.0f;
									else if (alphaTexY < effectiveEdge) fy = alphaTexY / effectiveEdge;
									else if (alphaTexY > 1.0f - effectiveEdge) fy = (1.0f - alphaTexY) / effectiveEdge;
									else fy = 1.0f;

									alphaFade = clamp(fx * fy, 0.0f, 1.0f);
								}
							}

							if (!outOfBounds)
							{
								float colorSampleX = (repeatMode == 0) ? clamp(colorTexX, 0.0f, 1.0f) : colorTexX;
								float colorSampleY = (repeatMode == 0) ? clamp(colorTexY, 0.0f, 1.0f) : colorTexY;
								float alphaSampleX = (alphaRepeatMode == 0) ? clamp(alphaTexX, 0.0f, 1.0f) : alphaTexX;
								float alphaSampleY = (alphaRepeatMode == 0) ? clamp(alphaTexY, 0.0f, 1.0f) : alphaTexY;

								float2 colorTexturePoint = (float2){colorSampleX, colorSampleY};
								float2 alphaTexturePoint = (float2){alphaSampleX, alphaSampleY};

								int2 textureSize = renderData->textureSizes[light->colorTextureIndex];
								__global uchar4 *texture = renderData->textures[light->colorTextureIndex];

								float3 texOut = BicubicInterpolation(
									colorTexturePoint.x, colorTexturePoint.y, texture, textureSize.x, textureSize.y);

								if (light->alphaTextureIndex >= 0 && light->projectionParams2.w > 0.5f)
								{
									// Separate alpha texture mask mode
									int2 alphaTextureSize = renderData->textureSizes[light->alphaTextureIndex];
									__global uchar4 *alphaTexture = renderData->textures[light->alphaTextureIndex];
									float alpha = SampleTextureAlpha(
										alphaTexturePoint.x, alphaTexturePoint.y, alphaTexture, alphaTextureSize.x, alphaTextureSize.y);
									if (light->projectionInvertAlphaMask) alpha = 1.0f - alpha;
									color = texOut;
									intensity = alpha * fade * alphaFade * light->projectionIntensity;
								}
								else if (light->projectionParams2.z > 0.5f)
								{
									// Alpha mask mode: sample alpha from texture s3 channel
									float alpha = SampleTextureAlpha(
										colorTexturePoint.x, colorTexturePoint.y, texture, textureSize.x, textureSize.y);
									if (light->projectionInvertAlphaMask) alpha = 1.0f - alpha;
									color = 1.0f;
									intensity = alpha * fade * light->projectionIntensity;
								}
								else if (light->projectionUseAsMask)
								{
									float luminance = dot(texOut, (float3)(0.299f, 0.587f, 0.114f));
									if (light->projectionInvertAlphaMask) luminance = 1.0f - luminance;
									color = 1.0f;
									intensity = luminance * fade * light->projectionIntensity;
								}
								else
								{
									color = texOut;
									intensity = fade * light->projectionIntensity;
								}
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
	float beamFade = 1.0f;

	float3 lightVector = CalculateLightVector(light, input->point, input->delta,
		consts->params.resolution, consts->params.viewDistanceMax, &dist, &input->randomSeed, &beamFade);

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
	intensity *= beamFade;

	// Apply blend mode between light color and projection texture color
	float3 blendedColor;
	switch (light->projectionBlendMode)
	{
		case 1: // Add
			blendedColor = light->color + textureColor;
			break;
		case 2: // Screen
			blendedColor = light->color + textureColor - light->color * textureColor;
			break;
		case 3: // Overlay
			blendedColor.s0 = (light->color.s0 < 0.5f)
										? 2.0f * light->color.s0 * textureColor.s0
										: 1.0f - 2.0f * (1.0f - light->color.s0) * (1.0f - textureColor.s0);
			blendedColor.s1 = (light->color.s1 < 0.5f)
										? 2.0f * light->color.s1 * textureColor.s1
										: 1.0f - 2.0f * (1.0f - light->color.s1) * (1.0f - textureColor.s1);
			blendedColor.s2 = (light->color.s2 < 0.5f)
										? 2.0f * light->color.s2 * textureColor.s2
										: 1.0f - 2.0f * (1.0f - light->color.s2) * (1.0f - textureColor.s2);
			break;
		default: // Multiply (case 0)
			blendedColor = light->color * textureColor;
			break;
	}

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

	shading = shade * auxShadow * blendedColor;
	*outSpecular = specular * blendedColor;

	*outShadow = auxShadow;

	return shading;
}
#endif // AUX_LIGHTS

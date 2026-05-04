/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2018-23 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * surface color calculation
 */

float3 GradientInterpolate(
	int paletteIndex, float pos, int mode, int gradientSize, __global float4 *palette,
	__global float4 *midpoints, int numMidpoints)
{
	float3 color = 0.0f;
	// if last element then just copy color value (no interpolation)
	if (paletteIndex == gradientSize - 1)
	{
		color = palette[paletteIndex - 1].xyz;
	}
	else
	{
		// interpolation
		float3 color1 = palette[paletteIndex].xyz;
		float pos1 = palette[paletteIndex].w;
		float3 color2 = palette[paletteIndex + 1].xyz;
		float pos2 = palette[paletteIndex + 1].w;

		// relative delta
		if (pos2 - pos1 > 0.0f)
		{
			float delta = (pos - pos1) / (pos2 - pos1);

			// apply midpoint curve if available
			if (numMidpoints > 0 && paletteIndex < numMidpoints)
			{
				float m = midpoints[paletteIndex].x;
				if (m > 0.0f && m < 1.0f)
				{
					if (delta < m)
						delta = 0.5f * delta / m;
					else
						delta = 0.5f + 0.5f * (delta - m) / (1.0f - m);
				}
			}

			// mode: 0=Linear, 1=Smooth, 2=Spline
			if (mode == 1) // Smooth (cosine)
			{
				delta = 0.5f * (1.0f - cos(delta * M_PI_F));
			}
			else if (mode == 2) // Spline (Catmull-Rom)
			{
				float3 p0 = (paletteIndex > 0) ? palette[paletteIndex - 1].xyz : color1;
				float3 p1 = color1;
				float3 p2 = color2;
				float3 p3 = (paletteIndex + 2 < gradientSize) ? palette[paletteIndex + 2].xyz : color2;

				float t2 = delta * delta;
				float t3 = t2 * delta;

				color = 0.5f * ((2.0f * p1) + (-p0 + p2) * delta
								+ (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t2
								+ (-p0 + 3.0f * p1 - 3.0f * p2 + p3) * t3);
			}
			// else mode == 0, keep linear delta

			if (mode != 2)
			{
				float nDelta = 1.0f - delta;
				color.s0 = color1.s0 * nDelta + color2.s0 * delta;
				color.s1 = color1.s1 * nDelta + color2.s1 * delta;
				color.s2 = color1.s2 * nDelta + color2.s2 * delta;
			}
		}
		else
		{
			color = color1;
		}
	}
	return color;
}

int GradientIterator(
	int paletteIndex, float colorPosition, int gradientSize, __global float4 *palette)
{
	int newIndex = paletteIndex;
	while (newIndex < gradientSize - 1 && colorPosition > palette[newIndex + 1].s3)
	{
		newIndex++;
	}
	return newIndex;
}

float3 GetColorFromGradient(float position, int mode, int gradientSize,
	__global float4 *palette, __global float4 *midpoints, int numMidpoints)
{
	int paletteIndex = GradientIterator(0, position, gradientSize, palette);
	return GradientInterpolate(
		paletteIndex, position, mode, gradientSize, palette, midpoints, numMidpoints);
}

float GetAlphaFromGradient(float position, int gradientSize, __global float4 *palette)
{
	if (gradientSize < 2) return 1.0f;
	int paletteIndex = GradientIterator(0, position, gradientSize, palette);
	// if last element then just copy alpha value
	if (paletteIndex == gradientSize - 1)
	{
		return palette[paletteIndex - 1].x;
	}
	float alpha1 = palette[paletteIndex].x;
	float pos1 = palette[paletteIndex].w;
	float alpha2 = palette[paletteIndex + 1].x;
	float pos2 = palette[paletteIndex + 1].w;
	if (pos2 - pos1 > 0.0f)
	{
		float delta = (position - pos1) / (pos2 - pos1);
		return alpha1 * (1.0f - delta) + alpha2 * delta;
	}
	return alpha1;
}

float3 SurfaceColor(__constant sClInConstants *consts, sRenderData *renderData,
	sShaderInputDataCl *input, sClCalcParams *calcParams, sClGradientsCollection *gradients)
{
	float3 out;
	calcParams->distThresh = input->distThresh;
	calcParams->detailSize = input->delta;

	formulaOut fout;
	fout.z = 0.0f;
	fout.iters = 0;
	fout.distance = 0.0f;
	fout.colorIndex = 0.0f;
	fout.maxiter = false;

#ifdef USE_SURFACE_GRADIENT
	gradients->surface = 1.0f;
#endif
#ifdef USE_SPECULAR_GRADIENT
	gradients->specular = 1.0f;
#endif
#ifdef USE_DIFFUSE_GRADIENT
	gradients->diffuse = 1.0f;
#endif
#ifdef USE_LUMINOSITY_GRADIENT
	gradients->luminosity = 0.0f;
#endif
#ifdef USE_ROUGHNESS_GRADIENT
	gradients->roughness = 1.0f;
#endif
#ifdef USE_REFLECTANCE_GRADIENT
	gradients->reflectance = 1.0f;
#endif
#ifdef USE_TRANSPARENCY_GRADIENT
	gradients->transparency = 1.0f;
#endif

	float3 pointTemp = input->point;
	float3 color = (float3){1.0f, 1.0f, 1.0f};

#if (defined(BOOLEAN_OPERATORS) || defined(USE_PRIMITIVES)) && defined(FULL_ENGINE)
	enumObjectTypeCl objectType = renderData->objectsData[input->objectId].objectType;
	switch (objectType)
	{
		case objFractal:
		{
#endif // defined(BOOLEAN_OPERATORS) || defined(USE_PRIMITIVES)

#ifdef USE_FRACTAL_COLORING
			if (input->material->useColorsFromPalette)
			{
#ifdef BOOLEAN_OPERATORS
				int formulaIndex = input->objectId;

				pointTemp = pointTemp - consts->params.formulaPosition[formulaIndex];
				pointTemp = Matrix33MulFloat3(consts->params.mRotFormulaRotation[formulaIndex], pointTemp);
				pointTemp = modRepeat(pointTemp, consts->params.formulaRepeat[formulaIndex]);
				pointTemp *= consts->params.formulaScale[formulaIndex];

#else
				int formulaIndex = -1;
#endif
				fout =
					Fractal(consts, pointTemp, calcParams, calcModeColouring, input->material, formulaIndex);
				gradients->colorIndex = fout.colorIndex;
				gradients->iters = fout.iters;
				float nCol = fmod(fabs(fout.colorIndex), 248.0f * 256.0f);

				float colorPosition = fmod(
					nCol / 256.0f / 10.0f * input->material->coloring_speed + input->material->paletteOffset,
					1.0f);

#ifdef USE_SURFACE_GRADIENT
				if (input->material->surfaceGradientEnable)
				{
					float alpha = GetAlphaFromGradient(colorPosition, input->opacitySurfaceLength,
						input->palette + input->opacitySurfaceOffset);
					if (input->material->surfaceGradientMaskEnable)
					{
						color = (float3){alpha, alpha, alpha};
					}
					else
					{
						color = GetColorFromGradient(colorPosition, input->material->surfaceGradientMode,
							input->paletteSurfaceLength, input->palette + input->paletteSurfaceOffset,
							input->palette + input->midpointSurfaceOffset, input->midpointSurfaceLength);
					}
					gradients->surface = color;
				}
				else
#endif
				{
					color = input->material->color;
				}

#ifdef USE_SPECULAR_GRADIENT
				if (input->material->specularGradientEnable)
				{
					float alpha = GetAlphaFromGradient(colorPosition, input->opacitySpecularLength,
						input->palette + input->opacitySpecularOffset);
					if (input->material->specularGradientMaskEnable)
					{
						gradients->specular = (float3){alpha, alpha, alpha};
					}
					else
					{
						gradients->specular = GetColorFromGradient(colorPosition,
							input->material->specularGradientMode, input->paletteSpecularLength,
							input->palette + input->paletteSpecularOffset,
							input->palette + input->midpointSpecularOffset, input->midpointSpecularLength);
					}
				}
#endif
#ifdef USE_DIFFUSE_GRADIENT
				if (input->material->diffuseGradientEnable)
				{
					float alpha = GetAlphaFromGradient(colorPosition, input->opacityDiffuseLength,
						input->palette + input->opacityDiffuseOffset);
					if (input->material->diffuseGradientMaskEnable)
					{
						gradients->diffuse = (float3){alpha, alpha, alpha};
					}
					else
					{
						gradients->diffuse = GetColorFromGradient(colorPosition,
							input->material->diffuseGradientMode, input->paletteDiffuseLength,
							input->palette + input->paletteDiffuseOffset,
							input->palette + input->midpointDiffuseOffset, input->midpointDiffuseLength);
					}
				}
#endif
#ifdef USE_LUMINOSITY_GRADIENT
				if (input->material->luminosityGradientEnable)
				{
					float alpha = GetAlphaFromGradient(colorPosition, input->opacityLuminosityLength,
						input->palette + input->opacityLuminosityOffset);
					if (input->material->luminosityGradientMaskEnable)
					{
						gradients->luminosity = (float3){alpha, alpha, alpha};
					}
					else
					{
						gradients->luminosity = GetColorFromGradient(colorPosition,
							input->material->luminosityGradientMode, input->paletteLuminosityLength,
							input->palette + input->paletteLuminosityOffset,
							input->palette + input->midpointLuminosityOffset, input->midpointLuminosityLength);
					}
				}
#endif
#ifdef USE_ROUGHNESS_GRADIENT
				if (input->material->roughnessGradientEnable)
				{
					float alpha = GetAlphaFromGradient(colorPosition, input->opacityRoughnessLength,
						input->palette + input->opacityRoughnessOffset);
					if (input->material->roughnessGradientMaskEnable)
					{
						gradients->roughness = (float3){alpha, alpha, alpha};
					}
					else
					{
						gradients->roughness = GetColorFromGradient(colorPosition,
							input->material->roughnessGradientMode, input->paletteRoughnessLength,
							input->palette + input->paletteRoughnessOffset,
							input->palette + input->midpointRoughnessOffset, input->midpointRoughnessLength);
					}
				}
#endif
#ifdef USE_REFLECTANCE_GRADIENT
				if (input->material->reflectanceGradientEnable)
				{
					float alpha = GetAlphaFromGradient(colorPosition, input->opacityReflectanceLength,
						input->palette + input->opacityReflectanceOffset);
					if (input->material->reflectanceGradientMaskEnable)
					{
						gradients->reflectance = (float3){alpha, alpha, alpha};
					}
					else
					{
						gradients->reflectance = GetColorFromGradient(colorPosition,
							input->material->reflectanceGradientMode, input->paletteReflectanceLength,
							input->palette + input->paletteReflectanceOffset,
							input->palette + input->midpointReflectanceOffset, input->midpointReflectanceLength);
					}
				}
#endif
#ifdef USE_TRANSPARENCY_GRADIENT
				if (input->material->transparencyGradientEnable)
				{
					float alpha = GetAlphaFromGradient(colorPosition, input->opacityTransparencyLength,
						input->palette + input->opacityTransparencyOffset);
					if (input->material->transparencyGradientMaskEnable)
					{
						gradients->transparency = (float3){alpha, alpha, alpha};
					}
					else
					{
						gradients->transparency = GetColorFromGradient(colorPosition,
							input->material->transparencyGradientMode, input->paletteTransparencyLength,
							input->palette + input->paletteTransparencyOffset,
							input->palette + input->midpointTransparencyOffset, input->midpointTransparencyLength);
					}
				}
#endif
			}
			else
#endif // USE_FRACTAL_COLORING
			{
				color = input->material->color;
			}
#if (defined(BOOLEAN_OPERATORS) || defined(USE_PRIMITIVES)) && defined(FULL_ENGINE)
			break;
		}
		case objPlane:
		case objWater:
		case objSphere:
		case objBox:
		case objRectangle:
		case objCircle:
		case objCone:
		case objTorus:
		case objCylinder:
		case objPrism:
		case objEllipsoid:
		{
			color = input->material->color;
			break;
		}
		case objNone:
		{
			color = 0.0f;
		}
	}
#endif

	out = (float3){color.x, color.y, color.z};

	return out;
}

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

// ===================================================================
// HSL COLOR SPACE HELPERS FOR OPENCL
// ===================================================================

void RGBtoHSL(float r, float g, float b, float *h, float *s, float *l)
{
	r = clamp(r, 0.0f, 1.0f);
	g = clamp(g, 0.0f, 1.0f);
	b = clamp(b, 0.0f, 1.0f);
	float maxVal = fmax(r, fmax(g, b));
	float minVal = fmin(r, fmin(g, b));
	*l = (maxVal + minVal) / 2.0f;
	if (maxVal == minVal)
	{
		*h = *s = 0.0f;
	}
	else
	{
		float d = maxVal - minVal;
		*s = *l > 0.5f ? d / (2.0f - maxVal - minVal) : d / (maxVal + minVal);
		if (maxVal == r)
			*h = (g - b) / d + (g < b ? 6.0f : 0.0f);
		else if (maxVal == g)
			*h = (b - r) / d + 2.0f;
		else
			*h = (r - g) / d + 4.0f;
		*h /= 6.0f;
	}
}

float3 HSLtoRGB(float h, float s, float l)
{
	h = fmod(h + 1.0f, 1.0f);
	s = clamp(s, 0.0f, 1.0f);
	l = clamp(l, 0.0f, 1.0f);
	float r, g, b;
	if (s == 0.0f)
	{
		r = g = b = l;
	}
	else
	{
		float q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
		float p = 2.0f * l - q;
		float t1 = h + 1.0f / 3.0f;
		float t2 = h;
		float t3 = h - 1.0f / 3.0f;
		if (t1 < 0.0f) t1 += 1.0f;
		if (t1 > 1.0f) t1 -= 1.0f;
		if (t2 < 0.0f) t2 += 1.0f;
		if (t2 > 1.0f) t2 -= 1.0f;
		if (t3 < 0.0f) t3 += 1.0f;
		if (t3 > 1.0f) t3 -= 1.0f;
		float c1 = (t1 < 1.0f / 6.0f) ? p + (q - p) * 6.0f * t1
					: (t1 < 1.0f / 2.0f) ? q
										 : (t1 < 2.0f / 3.0f) ? p + (q - p) * (2.0f / 3.0f - t1) * 6.0f
																								 : p;
		float c2 = (t2 < 1.0f / 6.0f) ? p + (q - p) * 6.0f * t2
					: (t2 < 1.0f / 2.0f) ? q
										 : (t2 < 2.0f / 3.0f) ? p + (q - p) * (2.0f / 3.0f - t2) * 6.0f
																								 : p;
		float c3 = (t3 < 1.0f / 6.0f) ? p + (q - p) * 6.0f * t3
					: (t3 < 1.0f / 2.0f) ? q
										 : (t3 < 2.0f / 3.0f) ? p + (q - p) * (2.0f / 3.0f - t3) * 6.0f
																								 : p;
		r = c1; g = c2; b = c3;
	}
	return (float3)(r, g, b);
}

float InterpolateHue(float h1, float h2, float delta, int shortestPath)
{
	float diff = h2 - h1;
	if (shortestPath)
	{
		if (diff > 0.5f) h2 -= 1.0f;
		else if (diff < -0.5f) h2 += 1.0f;
	}
	else
	{
		if (diff > 0.0f && diff < 0.5f) h2 -= 1.0f;
		else if (diff < 0.0f && diff > -0.5f) h2 += 1.0f;
	}
	float h = h1 + (h2 - h1) * delta;
	return fmod(h + 1.0f, 1.0f);
}

float CubicInterpolate(float y0, float y1, float y2, float y3, float mu)
{
	float a0 = -0.5f * y0 + 1.5f * y1 - 1.5f * y2 + 0.5f * y3;
	float a1 = y0 - 2.5f * y1 + 2.0f * y2 - 0.5f * y3;
	float a2 = -0.5f * y0 + 0.5f * y2;
	float a3 = y1;
	return a0 * mu * mu * mu + a1 * mu * mu + a2 * mu + a3;
}

float3 GradientInterpolate(int paletteIndex, float pos, bool smooth, int gradientSize,
	__global float4 *palette, __global float4 *midpoints, int midpointSize, int mode)
{
	float3 color = 0.0f;
	if (paletteIndex == gradientSize - 1)
	{
		color = palette[paletteIndex].xyz;
	}
	else
	{
		float3 color1 = palette[paletteIndex].xyz;
		float pos1 = palette[paletteIndex].w;
		float3 color2 = palette[paletteIndex + 1].xyz;
		float pos2 = palette[paletteIndex + 1].w;

		if (pos2 - pos1 > 0.0f)
		{
			float delta = (pos - pos1) / (pos2 - pos1);

			// Apply per-segment mode override BEFORE computing useSmooth
			if (midpoints && paletteIndex < midpointSize)
			{
				// Per-segment interpolation mode override (stored in y component)
				mode = clamp((int)midpoints[paletteIndex].s1, 0, 7);
			}

			bool useSmooth = (mode == 1) || (mode == 0 && smooth);
			if (useSmooth) delta = 0.5f * (1.0f - cos(delta * M_PI_F));

			if (midpoints && paletteIndex < midpointSize)
			{
				float m = clamp(midpoints[paletteIndex].s0, 0.01f, 0.99f);
				if (delta < m)
					delta = 0.5f * delta / m;
				else
					delta = 0.5f + 0.5f * (delta - m) / (1.0f - m);
			}

			// Quadratic Bezier uses midpoint as control point
			if (mode == 6)
			{
				float mp = (midpoints && paletteIndex < midpointSize) 
					? clamp(midpoints[paletteIndex].s0, 0.01f, 0.99f) : 0.5f;
				delta = 2.0f * (1.0f - delta) * delta * mp + delta * delta;
			}

			// PowerCurve uses midpoint as gamma exponent
			if (mode == 7)
			{
				float mp = (midpoints && paletteIndex < midpointSize)
					? clamp(midpoints[paletteIndex].s0, 0.01f, 0.99f) : 0.5f;
				float gamma = log(0.5f) / log(mp);
				delta = pow(delta, gamma);
			}

			switch (mode)
			{
				case 5: // Constant
					color = delta < 0.5f ? color1 : color2;
					break;
				case 2: // HSLShort
				case 3: // HSLLong
				{
					float h1, s1, l1, h2, s2, l2;
					RGBtoHSL(color1.x, color1.y, color1.z, &h1, &s1, &l1);
					RGBtoHSL(color2.x, color2.y, color2.z, &h2, &s2, &l2);
					float h = InterpolateHue(h1, h2, delta, mode == 2);
					float s = s1 * (1.0f - delta) + s2 * delta;
					float l = l1 * (1.0f - delta) + l2 * delta;
					color = HSLtoRGB(h, s, l);
					break;
				}
				case 4: // Cubic
				{
					int n = gradientSize;
					int i = paletteIndex;
					float y0[3], y1[3], y2[3], y3[3];
					for (int ch = 0; ch < 3; ch++)
					{
						y0[ch] = palette[clamp(i - 1, 0, n - 1)][ch];
						y1[ch] = palette[clamp(i, 0, n - 1)][ch];
						y2[ch] = palette[clamp(i + 1, 0, n - 1)][ch];
						y3[ch] = palette[clamp(i + 2, 0, n - 1)][ch];
					}
					color.x = clamp(CubicInterpolate(y0[0], y1[0], y2[0], y3[0], delta), 0.0f, 1.0f);
					color.y = clamp(CubicInterpolate(y0[1], y1[1], y2[1], y3[1], delta), 0.0f, 1.0f);
					color.z = clamp(CubicInterpolate(y0[2], y1[2], y2[2], y3[2], delta), 0.0f, 1.0f);
					break;
				}
				case 0: // Linear
				case 1: // Smooth
				case 6: // QuadraticBezier
				case 7: // PowerCurve
				default:
				{
					float nDelta = 1.0f - delta;
					color = color1 * nDelta + color2 * delta;
					break;
				}
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

float3 GetColorFromGradient(float position, bool smooth, int gradientSize,
	__global float4 *palette, __global float4 *midpoints, int midpointSize, int mode)
{
	int paletteIndex = GradientIterator(0, position, gradientSize, palette);
	return GradientInterpolate(paletteIndex, position, smooth, gradientSize, palette, midpoints, midpointSize, mode);
}

float3 ApplyBlendMode(float3 base, float3 blend, float opacity, int mode)
{
	float3 out;
	switch (mode)
	{
		case 1: // Multiply
			out = base * blend;
			break;
		case 2: // Screen
			out = 1.0f - (1.0f - base) * (1.0f - blend);
			break;
		case 3: // Overlay
			out.x = base.x < 0.5f ? 2.0f * base.x * blend.x : 1.0f - 2.0f * (1.0f - base.x) * (1.0f - blend.x);
			out.y = base.y < 0.5f ? 2.0f * base.y * blend.y : 1.0f - 2.0f * (1.0f - base.y) * (1.0f - blend.y);
			out.z = base.z < 0.5f ? 2.0f * base.z * blend.z : 1.0f - 2.0f * (1.0f - base.z) * (1.0f - blend.z);
			break;
		case 4: // Soft Light
			out.x = blend.x < 0.5f
						? 2.0f * base.x * blend.x + base.x * base.x * (1.0f - 2.0f * blend.x)
						: 2.0f * base.x * (1.0f - blend.x) + sqrt(base.x) * (2.0f * blend.x - 1.0f);
			out.y = blend.y < 0.5f
						? 2.0f * base.y * blend.y + base.y * base.y * (1.0f - 2.0f * blend.y)
						: 2.0f * base.y * (1.0f - blend.y) + sqrt(base.y) * (2.0f * blend.y - 1.0f);
			out.z = blend.z < 0.5f
						? 2.0f * base.z * blend.z + base.z * base.z * (1.0f - 2.0f * blend.z)
						: 2.0f * base.z * (1.0f - blend.z) + sqrt(base.z) * (2.0f * blend.z - 1.0f);
			break;
		case 5: // Hard Light
			out.x = blend.x < 0.5f ? 2.0f * base.x * blend.x : 1.0f - 2.0f * (1.0f - base.x) * (1.0f - blend.x);
			out.y = blend.y < 0.5f ? 2.0f * base.y * blend.y : 1.0f - 2.0f * (1.0f - base.y) * (1.0f - blend.y);
			out.z = blend.z < 0.5f ? 2.0f * base.z * blend.z : 1.0f - 2.0f * (1.0f - base.z) * (1.0f - blend.z);
			break;
		default: // Normal
			out = blend;
			break;
	}
	return base * (1.0f - opacity) + out * opacity;
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
					float3 gradientColor = GetColorFromGradient(colorPosition, false, input->paletteSurfaceLength,
						input->palette + input->paletteSurfaceOffset,
						input->palette + input->midpointSurfaceOffset, input->midpointSurfaceLength,
						input->material->surfaceGradientInterpolationMode);
					float opacity = 1.0f;
					if (input->material->surfaceGradientMaskEnable)
					{
						opacity = GetColorFromGradient(colorPosition, false, input->opacitySurfaceLength,
							input->palette + input->opacitySurfaceOffset, NULL, 0, 0).x;
					}
					color = ApplyBlendMode(input->material->color, gradientColor, opacity,
						input->material->surfaceGradientBlendMode);
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
					gradients->specular = GetColorFromGradient(colorPosition, false,
						input->paletteSpecularLength, input->palette + input->paletteSpecularOffset,
						input->palette + input->midpointSpecularOffset, input->midpointSpecularLength, 0);
				}
#endif
#ifdef USE_DIFFUSE_GRADIENT
				if (input->material->diffuseGradientEnable)
				{
					gradients->diffuse = GetColorFromGradient(colorPosition, false,
						input->paletteDiffuseLength, input->palette + input->paletteDiffuseOffset,
						input->palette + input->midpointDiffuseOffset, input->midpointDiffuseLength, 0);
				}
#endif
#ifdef USE_LUMINOSITY_GRADIENT
				if (input->material->luminosityGradientEnable)
				{
					gradients->luminosity = GetColorFromGradient(colorPosition, false,
						input->paletteLuminosityLength, input->palette + input->paletteLuminosityOffset,
						input->palette + input->midpointLuminosityOffset, input->midpointLuminosityLength, 0);
				}
#endif
#ifdef USE_ROUGHNESS_GRADIENT
				if (input->material->roughnessGradientEnable)
				{
					gradients->roughness = GetColorFromGradient(colorPosition, false,
						input->paletteRoughnessLength, input->palette + input->paletteRoughnessOffset,
						input->palette + input->midpointRoughnessOffset, input->midpointRoughnessLength, 0);
				}
#endif
#ifdef USE_REFLECTANCE_GRADIENT
				if (input->material->reflectanceGradientEnable)
				{
					gradients->reflectance = GetColorFromGradient(colorPosition, false,
						input->paletteReflectanceLength, input->palette + input->paletteReflectanceOffset,
						input->palette + input->midpointReflectanceOffset, input->midpointReflectanceLength, 0);
				}
#endif
#ifdef USE_TRANSPARENCY_GRADIENT
				if (input->material->transparencyGradientEnable)
				{
					gradients->transparency = GetColorFromGradient(colorPosition, false,
						input->paletteTransparencyLength, input->palette + input->paletteTransparencyOffset,
						input->palette + input->midpointTransparencyOffset, input->midpointTransparencyLength, 0);
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

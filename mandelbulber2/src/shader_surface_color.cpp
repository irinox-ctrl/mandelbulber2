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
 * cRenderWorker::SurfaceColour method - calculates color of fractal surface
 */
#include "compute_fractal.hpp"
#include "fractparams.hpp"
#include "render_data.hpp"
#include "render_worker.hpp"

sRGBAFloat cRenderWorker::SurfaceColour(
	CVector3 point, const sShaderInputData &input, sGradientsCollection *gradients) const
{
	sRGBAFloat out;

	switch (data->objectData[input.objectId].objectType)
	{
		case fractal::objFractal:
		{
			sRGBFloat colour(1.0, 1.0, 1.0);
			if (input.material->useColorsFromPalette)
			{
				int formulaIndex = input.objectId;

				CVector3 tempPoint = point;

				if (!params->booleanOperatorsEnabled)
					formulaIndex = -1;
				else
				{
					tempPoint = tempPoint - params->formulaPosition[formulaIndex];
					tempPoint = params->mRotFormulaRotation[formulaIndex].RotateVector(tempPoint);
					tempPoint = tempPoint.repeatMod(params->formulaRepeat[formulaIndex]);
					tempPoint *= params->formulaScale[formulaIndex];
				}

				sFractalIn fractIn(
					tempPoint, 0, -1, 4, 0, &params->common, formulaIndex, false, input.material);
				sFractalOut fractOut;
	fractOut.normal = CVector3(0, 0, 0);
				Compute<fractal::calcModeColouring>(*fractal, nullptr, fractIn, &fractOut);
				gradients->colorIndex = fractOut.colorIndex;
				gradients->iters = fractOut.iters;
				double nrCol = fmod(fabs(fractOut.colorIndex), 248.0 * 256.0); // kept for compatibility

				double rawColorPosition = nrCol / 256.0 / 10.0 * input.material->coloring_speed
					+ input.material->paletteOffset;

				// Apply gradient transform (scale, offset, repeat)
				double colorPosition = rawColorPosition * input.material->gradientScale
					+ input.material->gradientOffset;
				switch (input.material->gradientRepeatMode)
				{
					case 1: // Repeat
					{
						colorPosition = fmod(colorPosition, 1.0);
						if (colorPosition < 0.0) colorPosition += 1.0;
						break;
					}
					case 2: // Mirror
					{
						colorPosition = fmod(colorPosition, 2.0);
						if (colorPosition < 0.0) colorPosition += 2.0;
						if (colorPosition > 1.0) colorPosition = 2.0 - colorPosition;
						break;
					}
					case 3: // MirrorOnce
					{
						if (colorPosition < 0.0) colorPosition = 0.0;
						else if (colorPosition > 2.0) colorPosition = 1.0;
						else
						{
							colorPosition = fmod(colorPosition, 2.0);
							if (colorPosition > 1.0) colorPosition = 2.0 - colorPosition;
						}
						break;
					}
					case 4: // Extend
					case 0: // Clamp
					default:
						if (colorPosition < 0.0) colorPosition = 0.0;
						else if (colorPosition > 1.0) colorPosition = 1.0;
						break;
				}

				if (input.material->surfaceGradientEnable)
				{
					sRGBFloat gradientColor = input.material->gradientSurface.GetColorFloat(colorPosition, false);

					// Apply post-processing (brightness, contrast, saturation, gamma)
					gradientColor.R *= input.material->gradientBrightness;
					gradientColor.G *= input.material->gradientBrightness;
					gradientColor.B *= input.material->gradientBrightness;
					gradientColor.R = (gradientColor.R - 0.5f) * input.material->gradientContrast + 0.5f;
					gradientColor.G = (gradientColor.G - 0.5f) * input.material->gradientContrast + 0.5f;
					gradientColor.B = (gradientColor.B - 0.5f) * input.material->gradientContrast + 0.5f;
					if (input.material->gradientSaturation != 1.0f)
					{
						float maxV = fmaxf(gradientColor.R, fmaxf(gradientColor.G, gradientColor.B));
						float minV = fminf(gradientColor.R, fminf(gradientColor.G, gradientColor.B));
						float l = (maxV + minV) * 0.5f;
						gradientColor.R = l + (gradientColor.R - l) * input.material->gradientSaturation;
						gradientColor.G = l + (gradientColor.G - l) * input.material->gradientSaturation;
						gradientColor.B = l + (gradientColor.B - l) * input.material->gradientSaturation;
					}
					if (input.material->gradientGamma != 1.0f)
					{
						gradientColor.R = powf(fmaxf(0.0f, gradientColor.R), input.material->gradientGamma);
						gradientColor.G = powf(fmaxf(0.0f, gradientColor.G), input.material->gradientGamma);
						gradientColor.B = powf(fmaxf(0.0f, gradientColor.B), input.material->gradientGamma);
					}

					// Apply noise dithering
					if (input.material->gradientNoiseAmount > 0.0f)
					{
						float h = sinf(point.x * 127.1f + point.y * 311.7f + point.z * 74.7f) * 43758.5453f;
						float noise = (h - floorf(h) - 0.5f) * 2.0f * input.material->gradientNoiseAmount;
						gradientColor.R += noise;
						gradientColor.G += noise;
						gradientColor.B += noise;
					}

					float opacity = 1.0f;
					if (input.material->surfaceGradientMaskEnable)
					{
						opacity = input.material->gradientSurface.GetOpacity(colorPosition, false);
						if (input.material->opacityInvert) opacity = 1.0f - opacity;
						if (input.material->maskWhitePoint > input.material->maskBlackPoint)
							opacity = (opacity - input.material->maskBlackPoint)
								/ (input.material->maskWhitePoint - input.material->maskBlackPoint);
						opacity = (opacity - 0.5f) * input.material->maskContrast + 0.5f;
						if (opacity < 0.0f) opacity = 0.0f;
						if (opacity > 1.0f) opacity = 1.0f;
					}
					float baseR = input.material->color.R;
					float baseG = input.material->color.G;
					float baseB = input.material->color.B;
					float blendR = gradientColor.R;
					float blendG = gradientColor.G;
					float blendB = gradientColor.B;
					float outR, outG, outB;
					switch (input.material->surfaceGradientBlendMode)
					{
						case 1: // Multiply
							outR = baseR * blendR;
							outG = baseG * blendG;
							outB = baseB * blendB;
							break;
						case 2: // Screen
							outR = 1.0f - (1.0f - baseR) * (1.0f - blendR);
							outG = 1.0f - (1.0f - baseG) * (1.0f - blendG);
							outB = 1.0f - (1.0f - baseB) * (1.0f - blendB);
							break;
						case 3: // Overlay
							outR = baseR < 0.5f ? 2.0f * baseR * blendR : 1.0f - 2.0f * (1.0f - baseR) * (1.0f - blendR);
							outG = baseG < 0.5f ? 2.0f * baseG * blendG : 1.0f - 2.0f * (1.0f - baseG) * (1.0f - blendG);
							outB = baseB < 0.5f ? 2.0f * baseB * blendB : 1.0f - 2.0f * (1.0f - baseB) * (1.0f - blendB);
							break;
						case 4: // Soft Light
							outR = blendR < 0.5f
									 ? 2.0f * baseR * blendR + baseR * baseR * (1.0f - 2.0f * blendR)
									 : 2.0f * baseR * (1.0f - blendR) + sqrtf(baseR) * (2.0f * blendR - 1.0f);
							outG = blendG < 0.5f
									 ? 2.0f * baseG * blendG + baseG * baseG * (1.0f - 2.0f * blendG)
									 : 2.0f * baseG * (1.0f - blendG) + sqrtf(baseG) * (2.0f * blendG - 1.0f);
							outB = blendB < 0.5f
									 ? 2.0f * baseB * blendB + baseB * baseB * (1.0f - 2.0f * blendB)
									 : 2.0f * baseB * (1.0f - blendB) + sqrtf(baseB) * (2.0f * blendB - 1.0f);
							break;
						case 5: // Hard Light
							outR = blendR < 0.5f ? 2.0f * baseR * blendR
												 : 1.0f - 2.0f * (1.0f - baseR) * (1.0f - blendR);
							outG = blendG < 0.5f ? 2.0f * baseG * blendG
												 : 1.0f - 2.0f * (1.0f - baseG) * (1.0f - blendG);
							outB = blendB < 0.5f ? 2.0f * baseB * blendB
												 : 1.0f - 2.0f * (1.0f - baseB) * (1.0f - blendB);
							break;
						default: // Normal
							outR = blendR;
							outG = blendG;
							outB = blendB;
							break;
					}
					colour.R = baseR * (1.0f - opacity) + outR * opacity;
					colour.G = baseG * (1.0f - opacity) + outG * opacity;
					colour.B = baseB * (1.0f - opacity) + outB * opacity;
					gradients->surface = colour;
				}
				else
				{
					colour.R = input.material->color.R;
					colour.G = input.material->color.G;
					colour.B = input.material->color.B;
				}

				if (input.material->specularGradientEnable)
				{
					sRGBFloat gradColor = input.material->gradientSpecular.GetColorFloat(colorPosition, false);
					if (input.material->specularGradientMaskEnable)
					{
						float opacity = input.material->gradientSpecular.GetOpacity(colorPosition, false);
						if (input.material->opacityInvert) opacity = 1.0f - opacity;
						gradColor.R = gradColor.R * opacity + 1.0f * (1.0f - opacity);
						gradColor.G = gradColor.G * opacity + 1.0f * (1.0f - opacity);
						gradColor.B = gradColor.B * opacity + 1.0f * (1.0f - opacity);
					}
					gradients->specular = gradColor;
				}

				if (input.material->diffuseGradientEnable)
				{
					sRGBFloat gradColor = input.material->gradientDiffuse.GetColorFloat(colorPosition, false);
					if (input.material->diffuseGradientMaskEnable)
					{
						float opacity = input.material->gradientDiffuse.GetOpacity(colorPosition, false);
						if (input.material->opacityInvert) opacity = 1.0f - opacity;
						gradColor.R = gradColor.R * opacity + 1.0f * (1.0f - opacity);
						gradColor.G = gradColor.G * opacity + 1.0f * (1.0f - opacity);
						gradColor.B = gradColor.B * opacity + 1.0f * (1.0f - opacity);
					}
					gradients->diffuse = gradColor;
				}

				if (input.material->luminosityGradientEnable)
				{
					sRGBFloat gradColor = input.material->gradientLuminosity.GetColorFloat(colorPosition, false);
					if (input.material->luminosityGradientMaskEnable)
					{
						float opacity = input.material->gradientLuminosity.GetOpacity(colorPosition, false);
						if (input.material->opacityInvert) opacity = 1.0f - opacity;
						gradColor.R *= opacity;
						gradColor.G *= opacity;
						gradColor.B *= opacity;
					}
					gradients->luminosity = gradColor;
				}

				if (input.material->roughnessGradientEnable)
				{
					sRGBFloat gradColor = input.material->gradientRoughness.GetColorFloat(colorPosition, false);
					if (input.material->roughnessGradientMaskEnable)
					{
						float opacity = input.material->gradientRoughness.GetOpacity(colorPosition, false);
						if (input.material->opacityInvert) opacity = 1.0f - opacity;
						gradColor.R = gradColor.R * opacity + 1.0f * (1.0f - opacity);
						gradColor.G = gradColor.G * opacity + 1.0f * (1.0f - opacity);
						gradColor.B = gradColor.B * opacity + 1.0f * (1.0f - opacity);
					}
					gradients->roughness = gradColor;
				}

				if (input.material->reflectanceGradientEnable)
				{
					sRGBFloat gradColor = input.material->gradientReflectance.GetColorFloat(colorPosition, false);
					if (input.material->reflectanceGradientMaskEnable)
					{
						float opacity = input.material->gradientReflectance.GetOpacity(colorPosition, false);
						if (input.material->opacityInvert) opacity = 1.0f - opacity;
						gradColor.R = gradColor.R * opacity + 1.0f * (1.0f - opacity);
						gradColor.G = gradColor.G * opacity + 1.0f * (1.0f - opacity);
						gradColor.B = gradColor.B * opacity + 1.0f * (1.0f - opacity);
					}
					gradients->reflectance = gradColor;
				}

				if (input.material->transparencyGradientEnable)
				{
					sRGBFloat gradColor = input.material->gradientTransparency.GetColorFloat(colorPosition, false);
					if (input.material->transparencyGradientMaskEnable)
					{
						float opacity = input.material->gradientTransparency.GetOpacity(colorPosition, false);
						if (input.material->opacityInvert) opacity = 1.0f - opacity;
						gradColor.R = gradColor.R * opacity + 1.0f * (1.0f - opacity);
						gradColor.G = gradColor.G * opacity + 1.0f * (1.0f - opacity);
						gradColor.B = gradColor.B * opacity + 1.0f * (1.0f - opacity);
					}
					gradients->trasparency = gradColor;
				}
			}
			else
			{
				colour.R = input.material->color.R;
				colour.G = input.material->color.G;
				colour.B = input.material->color.B;
			}

			out.R = colour.R;
			out.G = colour.G;
			out.B = colour.B;
			break;
		}

		case fractal::objPlane:
		case fractal::objWater:
		case fractal::objSphere:
		case fractal::objBox:
		case fractal::objRectangle:
		case fractal::objCircle:
		case fractal::objCone:
		case fractal::objTorus:
		case fractal::objCylinder:
		case fractal::objPrism:
		case fractal::objEllipsoid:
		{
			out.R = input.material->color.R;
			out.G = input.material->color.G;
			out.B = input.material->color.B;
			break;
		}
		case fractal::objNone:
		{
			out = sRGBAFloat();
			break;
		}
	};

	return out;
}

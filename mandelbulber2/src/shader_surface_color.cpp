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

				double colorPosition = fmod(
					nrCol / 256.0 / 10.0 * input.material->coloring_speed + input.material->paletteOffset,
					1.0);

				if (input.material->surfaceGradientEnable)
				{
					sRGBAFloat rgba = input.material->gradientSurface.GetColorRGBA(colorPosition);
					colour = sRGBFloat(rgba.R, rgba.G, rgba.B);
					if (input.material->surfaceGradientMaskEnable)
					{
						colour.R *= rgba.A;
						colour.G *= rgba.A;
						colour.B *= rgba.A;
					}
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
					sRGBAFloat rgba = input.material->gradientSpecular.GetColorRGBA(colorPosition);
					gradients->specular = sRGBFloat(rgba.R, rgba.G, rgba.B);
					if (input.material->specularGradientMaskEnable)
					{
						gradients->specular.R *= rgba.A;
						gradients->specular.G *= rgba.A;
						gradients->specular.B *= rgba.A;
					}
				}

				if (input.material->diffuseGradientEnable)
				{
					sRGBAFloat rgba = input.material->gradientDiffuse.GetColorRGBA(colorPosition);
					gradients->diffuse = sRGBFloat(rgba.R, rgba.G, rgba.B);
					if (input.material->diffuseGradientMaskEnable)
					{
						gradients->diffuse.R *= rgba.A;
						gradients->diffuse.G *= rgba.A;
						gradients->diffuse.B *= rgba.A;
					}
				}

				if (input.material->luminosityGradientEnable)
				{
					sRGBAFloat rgba = input.material->gradientLuminosity.GetColorRGBA(colorPosition);
					gradients->luminosity = sRGBFloat(rgba.R, rgba.G, rgba.B);
					if (input.material->luminosityGradientMaskEnable)
					{
						gradients->luminosity.R *= rgba.A;
						gradients->luminosity.G *= rgba.A;
						gradients->luminosity.B *= rgba.A;
					}
				}

				if (input.material->roughnessGradientEnable)
				{
					sRGBAFloat rgba = input.material->gradientRoughness.GetColorRGBA(colorPosition);
					gradients->roughness = sRGBFloat(rgba.R, rgba.G, rgba.B);
					if (input.material->roughnessGradientMaskEnable)
					{
						gradients->roughness.R *= rgba.A;
						gradients->roughness.G *= rgba.A;
						gradients->roughness.B *= rgba.A;
					}
				}

				if (input.material->reflectanceGradientEnable)
				{
					sRGBAFloat rgba = input.material->gradientReflectance.GetColorRGBA(colorPosition);
					gradients->reflectance = sRGBFloat(rgba.R, rgba.G, rgba.B);
					if (input.material->reflectanceGradientMaskEnable)
					{
						gradients->reflectance.R *= rgba.A;
						gradients->reflectance.G *= rgba.A;
						gradients->reflectance.B *= rgba.A;
					}
				}

				if (input.material->transparencyGradientEnable)
				{
					sRGBAFloat rgba = input.material->gradientTransparency.GetColorRGBA(colorPosition);
					gradients->trasparency = sRGBFloat(rgba.R, rgba.G, rgba.B);
					if (input.material->transparencyGradientMaskEnable)
					{
						gradients->trasparency.R *= rgba.A;
						gradients->trasparency.G *= rgba.A;
						gradients->trasparency.B *= rgba.A;
					}
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

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
 * cRenderWorker::FakeLights method - calculates lights based on fractal orbit traps
 */
#include "compute_fractal.hpp"
#include "fractparams.hpp"
#include "render_worker.hpp"

sRGBAFloat cRenderWorker::FakeLights(
	const sShaderInputData &input, sRGBAFloat surfaceColor, sRGBAFloat *fakeSpec) const
{
	sRGBAFloat fakeLights(0.0, 0.0, 0.0, 0.0);

	int fakeLightMaxLoop = 1;
	if (params->common.fakeLightsColor2Enabled) fakeLightMaxLoop = 2;
	if (params->common.fakeLightsColor3Enabled) fakeLightMaxLoop = 3;

	// V2: Create a mutable copy of common params for position calculation
	sCommonParams commonWithPosition = params->common;

	// V2: Calculate orbit trap position based on positioning mode
	if (params->common.fakeLightsOrbitTrapPreTransformed)
	{
		// Transition interpolation already computed the blended world position in fractparams.cpp
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

		// Mode 0=World, 1=Camera, 2=Target, 3=FractalCenter, 4=PathCircle, 5=PathSpiral
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
			// World and FractalCenter: transformedTrap is the orbit trap position
			// FractalCenter z-adjustment is handled in compute_fractal.cpp
			commonWithPosition.fakeLightsOrbitTrap = transformedTrap;
		}
	}

	for (int fakeLightLoop = 0; fakeLightLoop < fakeLightMaxLoop; fakeLightLoop++)
	{

		double delta = input.distThresh * params->smoothness;

		sFractalIn fractIn(input.point, params->minN, -1, 1, fakeLightLoop, &commonWithPosition, -1, false);
		sFractalOut fractOut;
	fractOut.normal = CVector3(0, 0, 0);
		Compute<fractal::calcModeOrbitTrap>(*fractal, nullptr, fractIn, &fractOut);
		double rr = fractOut.orbitTrapR;
		double r = 1.0 / (rr + 1e-30);

		double fakeLight = params->fakeLightsIntensity * pow(rr, commonWithPosition.fakeLightsShapeFalloff);

		// V2: Distance-based intensity mask
		// Masks out light within maskRadius of the orbit trap, with softness transition
		double maskRadius = commonWithPosition.fakeLightsShapeMaskRadius;
		double maskSoftness = commonWithPosition.fakeLightsShapeMaskSoftness;
		if (maskRadius > 1e-10)
		{
			double dist = sqrt(r);  // approximate distance from orbit trap
			double edge = maskRadius + maskSoftness;
			double factor = 1.0;
			if (dist < maskRadius)
				factor = 0.0;
			else if (dist < edge && maskSoftness > 1e-10)
				factor = (dist - maskRadius) / maskSoftness;
			if (factor < 0.0) factor = 0.0;
			if (factor > 1.0) factor = 1.0;
			fakeLight *= factor;
		}

		CVector3 deltaX(delta, 0.0, 0.0);
		CVector3 deltaY(0.0, delta, 0.0);
		CVector3 deltaZ(0.0, 0.0, delta);

		fractIn.point = input.point + deltaX;
		Compute<fractal::calcModeOrbitTrap>(*fractal, nullptr, fractIn, &fractOut);
		double rx = 1.0 / (fractOut.orbitTrapR + 1e-30);

		fractIn.point = input.point + deltaY;
		Compute<fractal::calcModeOrbitTrap>(*fractal, nullptr, fractIn, &fractOut);
		double ry = 1.0 / (fractOut.orbitTrapR + 1e-30);

		fractIn.point = input.point + deltaZ;
		Compute<fractal::calcModeOrbitTrap>(*fractal, nullptr, fractIn, &fractOut);
		double rz = 1.0 / (fractOut.orbitTrapR + 1e-30);

		CVector3 fakeLightNormal;
		fakeLightNormal.x = r - rx;
		fakeLightNormal.y = r - ry;
		fakeLightNormal.z = r - rz;

		if (qFuzzyIsNull(fakeLightNormal.x) && qFuzzyIsNull(fakeLightNormal.y)
				&& qFuzzyIsNull(fakeLightNormal.z))
		{
			fakeLightNormal.x = 0.0;
		}
		else
		{
			fakeLightNormal.Normalize();
		}
		float fakeLight2 = fakeLight * input.normal.Dot(fakeLightNormal);
		if (fakeLight2 < 0) fakeLight2 = 0;

		sRGBFloat color;
		if (fakeLightLoop == 0 && commonWithPosition.fakeLightsMultiCenterEnabled
			&& fractOut.orbitTrapCenterIndex >= 0 && fractOut.orbitTrapCenterIndex < 4)
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

		fakeLights.R += fakeLight2 * color.R;
		fakeLights.G += fakeLight2 * color.G;
		fakeLights.B += fakeLight2 * color.B;

		//		sRGBAfloat fakeSpecular =
		//			SpecularHighlightCombined(input, fakeLightNormal, surfaceColor,
		// sRGBFloat(1.0, 1.0, 1.0));
		//
		//		fakeSpec->R = fakeSpecular.R / r * params->fakeLightsColor.R;
		//		fakeSpec->G = fakeSpecular.G / r * params->fakeLightsColor.G;
		//		fakeSpec->B = fakeSpecular.B / r * params->fakeLightsColor.B;

		*fakeSpec = sRGBAFloat();
	}
	return fakeLights;
}

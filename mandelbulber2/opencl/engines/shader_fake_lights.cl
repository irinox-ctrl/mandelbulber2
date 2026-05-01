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
 * calculation light sources based on fractal orbit traps
 */

#ifdef FAKE_LIGHTS
float3 FakeLightsShader(__constant sClInConstants *consts, sShaderInputDataCl *input,
	sClCalcParams *calcParams, float3 surfaceColor, sClGradientsCollection *gradients,
	float3 *specularOut)
{
	float3 fakeLights = 0.0f;

	int fakeLightMaxLoop = 1;
	if (consts->params.common.fakeLightsColor2Enabled) fakeLightMaxLoop = 2;
	if (consts->params.common.fakeLightsColor3Enabled) fakeLightMaxLoop = 3;

	// V2: Adjust orbit trap position for all modes using per-mode params
	float3 orbitTrapAdjusted;
	if (consts->params.common.fakeLightsOrbitTrapPreTransformed)
	{
		orbitTrapAdjusted = consts->params.common.fakeLightsOrbitTrap;
	}
	else
	{
		float3 baseOrbitTrap = consts->params.common.fakeLightsOrbitTrap;
		int posMode = consts->params.common.fakeLightsPositionMode;
		sFakeLightsModeParamsCl modeParams = consts->params.common.fakeLightsModes[posMode];
		float3 transformedTrap = Matrix33MulFloat3(modeParams.mRot, baseOrbitTrap * modeParams.scale)
			+ modeParams.offset;

		if (posMode == 1) // Camera Relative
		{
			orbitTrapAdjusted = consts->params.camera + transformedTrap;
		}
		else if (posMode == 2) // Target Point
		{
			orbitTrapAdjusted = consts->params.target + transformedTrap;
		}
		else if (posMode == 4) // Path Circle
		{
			orbitTrapAdjusted = transformedTrap;
			float angle = modeParams.rotation.y * M_PI_F / 180.0f;
			float3 pathOffset = (float3){cos(angle) * modeParams.pathRadius, 0.0f, sin(angle) * modeParams.pathRadius};
			orbitTrapAdjusted += pathOffset;
		}
		else if (posMode == 5) // Path Spiral
		{
			orbitTrapAdjusted = transformedTrap;
			float angle = modeParams.rotation.y * M_PI_F / 180.0f;
			float yOffset = angle * modeParams.pathRadius * 0.1f;
			float3 pathOffset = (float3){cos(angle) * modeParams.pathRadius, yOffset, sin(angle) * modeParams.pathRadius};
			orbitTrapAdjusted += pathOffset;
		}
		else if (posMode == 6) // Orbit Around Target
		{
			orbitTrapAdjusted = transformedTrap;
			float angle = modeParams.rotation.y * M_PI_F / 180.0f;
			float3 pathOffset = (float3){cos(angle) * modeParams.pathRadius, 0.0f, sin(angle) * modeParams.pathRadius};
			orbitTrapAdjusted = consts->params.target + orbitTrapAdjusted + pathOffset;
		}
		else // World (0) and Fractal Center (3)
		{
			orbitTrapAdjusted = transformedTrap;
		}
	}

	// Store original values to restore later
	float3 originalOrbitTrap = calcParams->orbitTrap;
	int originalOrbitTrapIndex = calcParams->orbitTrapIndex;

	int centerIndex = 0;
	for (int fakeLightLoop = 0; fakeLightLoop < fakeLightMaxLoop; fakeLightLoop++)
	{
		float delta = input->distThresh * consts->params.smoothness;

		calcParams->orbitTrapIndex = fakeLightLoop;
		calcParams->orbitTrap = orbitTrapAdjusted; // V2: Use adjusted orbit trap
		formulaOut outF;
		outF = Fractal(consts, input->point, calcParams, calcModeOrbitTrap, NULL, -1);
		float rr = outF.orbitTrapR;
		if (fakeLightLoop == 0) centerIndex = outF.orbitTrapCenterIndex;
		float r = 1.0f / (rr + 1e-30f);

		float fakeLight = consts->params.fakeLightsIntensity * pow(rr, consts->params.common.fakeLightsShapeFalloff);

		// V2: Distance-based intensity mask
		float maskRadius = consts->params.common.fakeLightsShapeMaskRadius;
		float maskSoftness = consts->params.common.fakeLightsShapeMaskSoftness;
		if (maskRadius > 1e-10f)
		{
			float dist = sqrt(r);  // approximate distance from orbit trap
			float edge = maskRadius + maskSoftness;
			float factor = 1.0f;
			if (dist < maskRadius)
				factor = 0.0f;
			else if (dist < edge && maskSoftness > 1e-10f)
				factor = (dist - maskRadius) / maskSoftness;
			if (factor < 0.0f) factor = 0.0f;
			if (factor > 1.0f) factor = 1.0f;
			fakeLight *= factor;
		}

		float3 out;
		calcParams->distThresh = input->distThresh;
		calcParams->detailSize = input->delta;

		outF = Fractal(
			consts, input->point + (float3){delta, 0.0f, 0.0f}, calcParams, calcModeOrbitTrap, NULL, -1);
		float rx = 1.0f / (outF.orbitTrapR + 1e-30f);

		outF = Fractal(
			consts, input->point + (float3){0.0f, delta, 0.0f}, calcParams, calcModeOrbitTrap, NULL, -1);
		float ry = 1.0f / (outF.orbitTrapR + 1e-30f);

		outF = Fractal(
			consts, input->point + (float3){0.0f, 0.0f, delta}, calcParams, calcModeOrbitTrap, NULL, -1);
		float rz = 1.0f / (outF.orbitTrapR + 1e-30f);

		float3 fakeLightNormal;
		fakeLightNormal.x = r - rx;
		fakeLightNormal.y = r - ry;
		fakeLightNormal.z = r - rz;

		if (length(fakeLightNormal) > 1e-20f)
			fakeLightNormal = normalize(fakeLightNormal);

		float fakeLight2 = fakeLight * dot(input->normal, fakeLightNormal);
		if (fakeLight2 < 0.0f) fakeLight2 = 0.0f;

		float3 color;
		if (fakeLightLoop == 0 && consts->params.common.fakeLightsMultiCenterEnabled && centerIndex >= 0 && centerIndex < 4)
		{
			color = consts->params.fakeLightsMultiCenterColor[centerIndex];
		}
		else
		{
			switch (fakeLightLoop)
			{
				case 0: color = consts->params.fakeLightsColor; break;
				case 1: color = consts->params.fakeLightsColor2; break;
				case 2: color = consts->params.fakeLightsColor3; break;
				default: color = consts->params.fakeLightsColor; break;
			}
		}

		fakeLights += fakeLight2 * color;

		//	float3 fakeSpec =
		//		SpecularHighlightCombined(input, calcParams, fakeLightNormal, surfaceColor, gradients);
		//	fakeSpec = fakeSpec * consts->params.fakeLightsColor / r;
	}

	// V2: Restore original orbit trap
	calcParams->orbitTrap = originalOrbitTrap;
	calcParams->orbitTrapIndex = originalOrbitTrapIndex;

	float3 fakeSpec = 0.0f; // TODO to check why in CPU code it's zero
	*specularOut = fakeSpec;
	return fakeLights;
}
#endif // FAKE_LIGTS

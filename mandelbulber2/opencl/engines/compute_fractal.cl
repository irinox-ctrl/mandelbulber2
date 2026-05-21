/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2017-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * main fractal function for opencl
 */

#ifndef MANDELBULBER2_OPENCL_ENGINES_COMPUTE_FRACTAL_CL_
#define MANDELBULBER2_OPENCL_ENGINES_COMPUTE_FRACTAL_CL_

#ifndef FORMULA_ITER_0
#define FORMULA_ITER_0 DummyIteration
#endif /*FORMULA_ITER_0*/
#ifndef FORMULA_ITER_1
#define FORMULA_ITER_1 DummyIteration
#endif /*FORMULA_ITER_1*/
#ifndef FORMULA_ITER_2
#define FORMULA_ITER_2 DummyIteration
#endif /*FORMULA_ITER_2*/
#ifndef FORMULA_ITER_3
#define FORMULA_ITER_3 DummyIteration
#endif /*FORMULA_ITER_3*/
#ifndef FORMULA_ITER_4
#define FORMULA_ITER_4 DummyIteration
#endif /*FORMULA_ITER_4*/
#ifndef FORMULA_ITER_5
#define FORMULA_ITER_5 DummyIteration
#endif /*FORMULA_ITER_5*/
#ifndef FORMULA_ITER_6
#define FORMULA_ITER_6 DummyIteration
#endif /*FORMULA_ITER_6*/
#ifndef FORMULA_ITER_7
#define FORMULA_ITER_7 DummyIteration
#endif /*FORMULA_ITER_7*/
#ifndef FORMULA_ITER_8
#define FORMULA_ITER_8 DummyIteration
#endif /*FORMULA_ITER_8*/
#ifndef FORMULA_ITER_9
#define FORMULA_ITER_9 DummyIteration
#endif /*FORMULA_ITER_9*/

typedef struct
{
	float4 z;
	float iters;
	float distance;
	float colorIndex;
	float orbitTrapR;
	float pseudoKleinianDE;
	float finalDE;
	int orbitTrapMinIter;
	int orbitTrapCenterIndex;
	int objectId;
	bool maxiter;
} formulaOut;

typedef enum
{
	calcModeNormal = 0,
	calcModeColouring = 1,
	calcModeFake_AO = 2,
	calcModeDeltaDE1 = 3,
	calcModeDeltaDE2 = 4,
	calcModeOrbitTrap = 5,
	calcModeCubeOrbitTrap = 6
} enumCalculationModeCl;

float4 DummyIteration(float4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	aux->r = -1.0f; // signal for main loop to break;
	return 0.0f;
}

formulaOut Fractal(__constant sClInConstants *consts, float3 point, sClCalcParams *calcParam,
	enumCalculationModeCl mode, __global sMaterialCl *material, int forcedFormulaIndex)
{
	// begin
	float dist = 0.0f;

	// repeat, move and rotate
	float3 pointTransformed = point - consts->params.common.fractalPosition;
	pointTransformed = Matrix33MulFloat3(consts->params.common.mRotFractalRotation, pointTransformed);
	pointTransformed = modRepeat(pointTransformed, consts->params.common.repeat);

	float4 point4D = (float4){pointTransformed.x, pointTransformed.y, pointTransformed.z, 0.0f};

	float4 z;
	z.x = pointTransformed.x;
	z.y = pointTransformed.y;
	z.z = pointTransformed.z;

	int maxN;

#ifdef BOOLEAN_OPERATORS
	if (forcedFormulaIndex >= 0)
	{
		z.w = consts->sequence.initialWAxis[forcedFormulaIndex];
		maxN = consts->sequence.formulaMaxiter[forcedFormulaIndex];
	}
	else
	{
		z.w = consts->sequence.initialWAxis[0];
		maxN = consts->sequence.formulaMaxiter[0];
	}
#else
	z.w = consts->sequence.initialWAxis[0];
	maxN = consts->sequence.formulaMaxiter[0];
#endif

	if (calcParam->normalCalculationMode && calcParam->iterThreshMode) maxN *= 5;
	if (mode == calcModeColouring) maxN *= 4;

	float initialWAxisColor = z.w;

	float4 c = z;
	int i;

	formulaOut out;
	out.maxiter = true;
	out.orbitTrapR = 0.0f;
	out.orbitTrapCenterIndex = 0;
	out.colorIndex = 0.0f;

	float colorMin = 1000.0;
	float orbitTrapTotal = 0.0f;
	int orbitTrapMinIter = 0;
	float orbitTrapMinDist = 1e30f;
	float4 autoTrapCenter = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	bool autoTrapCenterSet = false;

	int fractalIndex = 0;
	if (forcedFormulaIndex >= 0) fractalIndex = forcedFormulaIndex;

	// formula init
	sExtendedAuxCl aux;

	aux.c = c;
	aux.const_c = c;
	aux.old_z = z;
	aux.pos_neg = 1.0f;
	aux.r = length(z);
	aux.DE = 1.0f;
	aux.DE0 = 0.0;
	aux.dist = 1000.0f;
	aux.pseudoKleinianDE = 1.0f;
	aux.actualScale = consts->fractal[fractalIndex].mandelbox.scale;
	aux.actualScaleA = 0.0f;
	aux.color = 1.0f;
	aux.colorHybrid = 0.0f;
	aux.temp1000 = 1000.0f;

	int sequence = 0;
	__constant sFractalCl *fractal;

	__constant sFractalCl *defaultFractal = &consts->fractal[fractalIndex];

	__global sFractalColoringCl *fractalColoring = (material) ? &material->fractalColoring : NULL;

	float4 lastZ = 0.0f;
	float4 lastLastZ = 0.0f;

#ifdef FAKE_LIGHTS
	// orbit trap lights initialization
	int fakeLightsMinIter = consts->params.common.fakeLightsMinIter;
	int fakeLightsMaxIter = consts->params.common.fakeLightsMaxIter;

	if (mode == calcModeOrbitTrap)
	{
		if (calcParam->orbitTrapIndex == 0)
		{
			if (consts->params.common.fakeLightsColor2Enabled) fakeLightsMaxIter = fakeLightsMinIter;
		}
		else if (calcParam->orbitTrapIndex == 1)
		{
			fakeLightsMinIter = consts->params.common.fakeLightsMinIter + 1;
			fakeLightsMaxIter = max(fakeLightsMinIter, consts->params.common.fakeLightsMaxIter);
			if (consts->params.common.fakeLightsColor3Enabled) fakeLightsMaxIter = fakeLightsMinIter;
		}
		else if (calcParam->orbitTrapIndex == 2)
		{
			fakeLightsMinIter = consts->params.common.fakeLightsMinIter + 2;
			fakeLightsMaxIter = max(fakeLightsMinIter, consts->params.common.fakeLightsMaxIter);
		}
	}
#endif // FAKE_LIGHTS

	// loop
	for (i = 0; i < maxN; i++)
	{
#if defined(IS_HYBRID) || defined(BOOLEAN_OPERATORS)
		if (forcedFormulaIndex >= 0)
			sequence = forcedFormulaIndex;
		else
			sequence = consts->sequence.hybridSequence[min(i, 249)];
#else
		sequence = 0;
#endif

		fractal = &consts->fractal[sequence];

		aux.i = i;

		lastLastZ = lastZ;
		lastZ = z;

#ifdef BOX_FOLDING
		z = BoxFolding(z, &consts->params.common.foldings, &aux);
		aux.r = length(z);
#endif

#ifdef SPHERICAL_FOLDING
		z = SphericalFolding(z, &consts->params.common.foldings, &aux);
		aux.r = length(z);
#endif

		// temporary values for weight function
#ifdef ITERATION_WEIGHT
		float4 tempZ = z;
		float tempAuxDE = aux.DE;
		float tempAuxDE0 = aux.DE0;
		float tempAuxDist = aux.dist;
		float tempAuxPseudoKleinianDE = aux.pseudoKleinianDE;
		float tempAuxActualScale = aux.actualScale;
		float tempAuxActualScaleA = aux.actualScaleA;
		float tempAuxColor = aux.color;
		float tempAuxColorHybrid = aux.colorHybrid;
		float tempAuxTemp1000 = aux.temp1000;
#endif

		float effectiveWeight = 1.0f;
#ifdef ITERATION_WEIGHT
		if (consts->sequence.isHybrid)
		{
			int deFunc = consts->sequence.DEFunctionType[sequence];
			__constant sClFormulaWeightParams *wp = &consts->sequence.weightParams[sequence];
			int weightMode = wp->mode;

			// Transform passthrough: always weight=1
			if (deFunc == 0 && weightMode == 7) // withoutDEFunction=0, TransformPassthrough=7
			{
				effectiveWeight = 1.0f;
			}
			else
			{
				float standardWeight = consts->sequence.formulaWeight[sequence];

				// Compute actual DE estimate per formula type
				float actualDE = aux.DE;
				if (aux.r > 0.0f)
				{
					if (deFunc == pseudoKleinianDEFunction)
					{
						float rxy = native_sqrt(z.x * z.x + z.y * z.y);
						actualDE = (aux.DE > 0.0f)
							? max(rxy - aux.pseudoKleinianDE, fabs(rxy * z.z) / aux.r) / aux.DE
							: aux.r;
					}
					else if (deFunc == josKleinianDEFunction)
					{
						// Use fractal's actual parameters (tweak005, offset1) via consts
						actualDE = min(z.y, fractal->analyticDE.tweak005)
							/ max(aux.DE, fractal->analyticDE.offset1);
					}
					else if (deFunc == logarithmicDEFunction)
					{
						actualDE = (aux.DE > 0.0f && aux.r > 1.0f)
							? 0.5f * aux.r * native_log(aux.r) / aux.DE : aux.r;
					}
					else if (deFunc == linearDEFunction)
					{
						actualDE = (aux.DE > 0.0f) ? aux.r / aux.DE : aux.r;
					}
					else if (deFunc == customDEFunction)
					{
						actualDE = (aux.dist > 0.0f) ? aux.dist : aux.r;
					}
					else if (deFunc == maxAxisDEFunction)
					{
						float maxZ = max(max(fabs(z.x), fabs(z.y)), fabs(z.z));
						actualDE = (aux.DE > 0.0f) ? maxZ / aux.DE : maxZ;
					}
					else if (deFunc == 0) // withoutDEFunction
					{
						actualDE = aux.r;
					}
				}

				if (weightMode == 0) // Static
				{
					effectiveWeight = wp->staticWeight;
				}
				else if (weightMode == 1) // Iteration
				{
					if (i <= wp->iterStart)
						effectiveWeight = wp->startWeight;
					else if (i >= wp->iterEnd)
						effectiveWeight = wp->endWeight;
					else
					{
						float t = (float)(i - wp->iterStart) / (float)(wp->iterEnd - wp->iterStart);
						int bm = wp->blendMode;
						if (bm == 0) effectiveWeight = wp->startWeight + t * (wp->endWeight - wp->startWeight);
						else if (bm == 1) { float s = t * t * (3.0f - 2.0f * t); effectiveWeight = wp->startWeight + s * (wp->endWeight - wp->startWeight); }
						else if (bm == 2) effectiveWeight = (t < 0.5f) ? wp->startWeight : wp->endWeight;
						else if (bm == 3) effectiveWeight = wp->startWeight * pow(wp->endWeight / max(wp->startWeight, 1e-15f), t);
						else if (bm == 4) effectiveWeight = wp->startWeight + pow(t, 2.0f) * (wp->endWeight - wp->startWeight);
						else if (bm == 5) effectiveWeight = min(wp->startWeight, wp->endWeight);
						else effectiveWeight = max(wp->startWeight, wp->endWeight);
					}
				}
				else if (weightMode == 2) // DE
				{
					float smoothDE = actualDE;
					if (wp->deSmoothRadius > 0.0f)
					{
						float dist = fabs(actualDE - wp->deThreshold);
						if (dist < wp->deSmoothRadius)
						{
							float t = dist / wp->deSmoothRadius;
							smoothDE = wp->deThreshold + (actualDE - wp->deThreshold) * t * t * (3.0f - 2.0f * t);
						}
					}
					float delta = smoothDE - wp->deThreshold;
					float factor = delta * wp->deSensitivity;
					if (wp->deModType == 0) effectiveWeight = wp->deBase + factor;
					else if (wp->deModType == 1) effectiveWeight = wp->deBase + factor * factor * (factor > 0.0f ? 1.0f : -1.0f);
					else if (wp->deModType == 2) effectiveWeight = wp->deBase * exp(factor);
					else if (wp->deModType == 3) effectiveWeight = (fabs(actualDE) > 1e-15f) ? wp->deBase * (wp->deThreshold / actualDE) : 1.0f;
					else effectiveWeight = wp->deBase + (1.0f - wp->deBase) / (1.0f + exp(-factor));
					effectiveWeight = clamp(effectiveWeight, 0.0f, 1.0f);
				}
				else if (weightMode == 3) // ZLength
				{
					float zLen = length(z);
					float delta = zLen - wp->zlengthThreshold;
					float factor = delta * wp->zlengthSens;
					if (wp->zlengthModType == 0) effectiveWeight = wp->zlengthBase + factor;
					else if (wp->zlengthModType == 1) effectiveWeight = wp->zlengthBase + factor * factor * (factor > 0.0f ? 1.0f : -1.0f);
					else if (wp->zlengthModType == 2) effectiveWeight = wp->zlengthBase * exp(factor);
					else if (wp->zlengthModType == 3) effectiveWeight = (fabs(zLen) > 1e-15f) ? wp->zlengthBase * (wp->zlengthThreshold / zLen) : 1.0f;
					else effectiveWeight = wp->zlengthBase + (1.0f - wp->zlengthBase) / (1.0f + exp(-factor));
					effectiveWeight = clamp(effectiveWeight, 0.0f, 1.0f);
				}
				else if (weightMode == 4) // Conditional
				{
					float testValue = 0.0f;
					if (wp->conditionType == 0) testValue = actualDE;
					else if (wp->conditionType == 1) testValue = length(z);
					else if (wp->conditionType == 2) testValue = aux.dist;
					else testValue = (float)i;
					bool condMet = (testValue < wp->conditionThreshold);
					int cb = wp->conditionBlend;
					if (cb == 2) { float blend = (wp->conditionThreshold > 1e-15f) ? clamp(testValue / wp->conditionThreshold, 0.0f, 1.0f) : (condMet ? 0.0f : 1.0f); float s = blend * blend * (3.0f - 2.0f * blend); effectiveWeight = wp->trueWeight * (1.0f - s) + wp->falseWeight * s; }
					else if (cb == 1) { float blend = (wp->conditionThreshold > 1e-15f) ? clamp(testValue / wp->conditionThreshold, 0.0f, 1.0f) : (condMet ? 0.0f : 1.0f); effectiveWeight = wp->trueWeight * (1.0f - blend) + wp->falseWeight * blend; }
					else effectiveWeight = condMet ? wp->trueWeight : wp->falseWeight;
				}
				else if (weightMode == 5) // OrbitTrap
				{
					float orbitDist = length(z);
					float delta = orbitDist - wp->orbitTrapThreshold;
					float factor = delta * wp->orbitTrapSensitivity;
					if (wp->orbitTrapModType == 0) effectiveWeight = wp->orbitTrapBase + factor;
					else if (wp->orbitTrapModType == 1) effectiveWeight = wp->orbitTrapBase + factor * factor * (factor > 0.0f ? 1.0f : -1.0f);
					else if (wp->orbitTrapModType == 2) effectiveWeight = wp->orbitTrapBase * exp(factor);
					else if (wp->orbitTrapModType == 3) effectiveWeight = (fabs(orbitDist) > 1e-15f) ? wp->orbitTrapBase * (wp->orbitTrapThreshold / orbitDist) : 1.0f;
					else effectiveWeight = wp->orbitTrapBase + (1.0f - wp->orbitTrapBase) / (1.0f + exp(-factor));
					effectiveWeight = clamp(effectiveWeight, 0.0f, 1.0f);
				}
				else if (weightMode == 6) // Curve
				{
					float normalized = (wp->curveBase > 1e-15f) ? actualDE / wp->curveBase : actualDE;
					float powered = pow(fabs(normalized * wp->curveSensitivity), wp->curvePower);
					if (wp->curveModType == 0) effectiveWeight = wp->curveBase + powered * (normalized >= 0.0f ? 1.0f : -1.0f);
					else if (wp->curveModType == 1) { float s = powered * powered * (3.0f - 2.0f * powered); effectiveWeight = wp->curveBase + s; }
					else if (wp->curveModType == 2) effectiveWeight = wp->curveBase * exp(powered - 1.0f);
					else if (wp->curveModType == 3) effectiveWeight = (powered > 1e-15f) ? wp->curveBase / powered : 1.0f;
					else effectiveWeight = wp->curveBase + (1.0f - wp->curveBase) / (1.0f + exp(-(powered - 0.5f) * 6.0f));
					effectiveWeight = clamp(effectiveWeight, 0.0f, 1.0f);
				}
				else if (weightMode == 7) // Transform Passthrough
				{
					effectiveWeight = 1.0f;
				}
				else if (weightMode == 8) // DE Ratio
				{
					float ratio = (wp->deRatioOffset > 1e-15f) ? actualDE / wp->deRatioOffset : actualDE;
					ratio *= wp->deRatioScale;
					if (wp->deRatioModType == 0) effectiveWeight = clamp(ratio, 0.0f, 1.0f);
					else if (wp->deRatioModType == 1) { float c = clamp(ratio, 0.0f, 1.0f); effectiveWeight = c * c * (3.0f - 2.0f * c); }
					else if (wp->deRatioModType == 2) effectiveWeight = 1.0f - exp(-fabs(ratio));
					else if (wp->deRatioModType == 3) effectiveWeight = (fabs(ratio) > 1e-15f) ? clamp(1.0f / ratio, 0.0f, 1.0f) : 1.0f;
					else effectiveWeight = 1.0f / (1.0f + exp(-(ratio - 0.5f) * 6.0f));
				}
				else if (weightMode == 9) // Adaptive
				{
					float str = wp->adaptiveStrength;
					if (deFunc == logarithmicDEFunction)
					{
						float norm = (actualDE > 1e-15f) ? native_log(1.0f + actualDE) : 0.0f;
						effectiveWeight = 1.0f / (1.0f + exp(-(norm - 0.5f) * 4.0f * str));
					}
					else if (deFunc == linearDEFunction)
					{
						float norm = clamp(actualDE * str, 0.0f, 1.0f);
						effectiveWeight = norm * norm * (3.0f - 2.0f * norm);
					}
					else if (deFunc == customDEFunction)
					{
						float dist = (aux.dist > 1e-15f) ? aux.dist : actualDE;
						effectiveWeight = (dist > 1e-15f) ? clamp(str / (str + dist), 0.0f, 1.0f) : 1.0f;
					}
					else if (deFunc == pseudoKleinianDEFunction || deFunc == josKleinianDEFunction)
					{
						effectiveWeight = 1.0f / (1.0f + exp(-(actualDE - 0.5f) * 6.0f * str));
					}
					else if (deFunc == 0) // withoutDEFunction
					{
						effectiveWeight = 1.0f;
					}
					else
					{
						float norm = clamp(actualDE * str, 0.0f, 1.0f);
						effectiveWeight = norm * norm * (3.0f - 2.0f * norm);
					}
					effectiveWeight = clamp(effectiveWeight, 0.0f, 1.0f);
				}

				effectiveWeight *= standardWeight;
				if (effectiveWeight > 1.0f) effectiveWeight = 1.0f;

				// Fine-tuning post-processing
				if (wp->weightGamma != 1.0f && effectiveWeight > 0.0f && effectiveWeight < 1.0f)
					effectiveWeight = pow(effectiveWeight, wp->weightGamma);
				if (wp->weightInvert)
					effectiveWeight = 1.0f - effectiveWeight;
				effectiveWeight = clamp(effectiveWeight, wp->weightFloor, wp->weightCeiling);
				if (wp->fadeInIterations > 0 && i < wp->fadeInIterations)
				{
					float fadeT = (float)i / (float)wp->fadeInIterations;
					effectiveWeight *= fadeT * fadeT * (3.0f - 2.0f * fadeT);
				}
				if (wp->fadeOutIterations > 0)
				{
					int maxIter = (weightMode == 1) ? wp->iterEnd : 250;
					int fadeStart = maxIter - wp->fadeOutIterations;
					if (i > fadeStart && i <= maxIter)
					{
						float fadeT = (float)(maxIter - i) / (float)wp->fadeOutIterations;
						effectiveWeight *= fadeT * fadeT * (3.0f - 2.0f * fadeT);
					}
				}
			}
		}
#endif // ITERATION_WEIGHT

#ifdef ITERATION_WEIGHT
		if (effectiveWeight > 0.0f)
		{
#endif

		// -------------- Formula Mutation pre-processing (GPU) ---------------
		float4 preMutZ = z;
		bool mutationActive = consts->sequence.mutationParams[sequence].enabled
			&& i >= consts->sequence.mutationParams[sequence].iterationStart
			&& i < consts->sequence.mutationParams[sequence].iterationStop;
		if (mutationActive)
		{
			__constant sClFormulaMutationParams *mut = &consts->sequence.mutationParams[sequence];

			if (mut->preAbsX) z.x = fabs(z.x);
			if (mut->preAbsY) z.y = fabs(z.y);
			if (mut->preAbsZ) z.z = fabs(z.z);
			z.x += mut->preOffsetX; z.y += mut->preOffsetY; z.z += mut->preOffsetZ;
			if (mut->preRotX != 0.0f || mut->preRotY != 0.0f || mut->preRotZ != 0.0f)
			{
				float3 zr;
				zr.x = mut->preRotMatrix[0]*z.x + mut->preRotMatrix[1]*z.y + mut->preRotMatrix[2]*z.z;
				zr.y = mut->preRotMatrix[3]*z.x + mut->preRotMatrix[4]*z.y + mut->preRotMatrix[5]*z.z;
				zr.z = mut->preRotMatrix[6]*z.x + mut->preRotMatrix[7]*z.y + mut->preRotMatrix[8]*z.z;
				z.x = zr.x; z.y = zr.y; z.z = zr.z;
			}
			if (mut->preScale != 1.0f) { z *= mut->preScale; aux.DE *= mut->preScale; }

			// Fold injection (pre or both)
			if (mut->foldType != 0 && (mut->foldPosition == 0 || mut->foldPosition == 2))
			{
				switch (mut->foldType)
				{
					case 1: // box fold
						if (fabs(z.x) > mut->foldLimit) z.x = sign(z.x) * mut->foldValue - z.x;
						if (fabs(z.y) > mut->foldLimit) z.y = sign(z.y) * mut->foldValue - z.y;
						if (fabs(z.z) > mut->foldLimit) z.z = sign(z.z) * mut->foldValue - z.z;
						break;
					case 2: // sphere fold
					{
						float rr = z.x*z.x + z.y*z.y + z.z*z.z;
						float minR2 = mut->foldLimit * mut->foldLimit;
						float fixR2 = mut->foldValue * mut->foldValue;
						if (rr < minR2) { z *= fixR2/minR2; aux.DE *= fixR2/minR2; }
						else if (rr < fixR2) { z *= fixR2/rr; aux.DE *= fixR2/rr; }
						break;
					}
					case 3: // menger fold
					{
						z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z);
						if (z.x - z.y < 0) { float t = z.y; z.y = z.x; z.x = t; }
						if (z.x - z.z < 0) { float t = z.z; z.z = z.x; z.x = t; }
						if (z.y - z.z < 0) { float t = z.z; z.z = z.y; z.y = t; }
						float s = mut->foldValue;
						z.x = z.x * s - mut->foldLimit * (s - 1.0f);
						z.y = z.y * s - mut->foldLimit * (s - 1.0f);
						z.z = z.z * s;
						if (z.z > 0.5f * mut->foldLimit * (s - 1.0f))
							z.z -= mut->foldLimit * (s - 1.0f);
						aux.DE *= s;
						break;
					}
					case 4: // sierpinski fold
					{
						if (z.x + z.y < 0) { float tx = -z.y; z.y = -z.x; z.x = tx; }
						if (z.x + z.z < 0) { float tx = -z.z; z.z = -z.x; z.x = tx; }
						if (z.y + z.z < 0) { float ty = -z.z; z.z = -z.y; z.y = ty; }
						float s = mut->foldValue;
						z *= s;
						z.x -= mut->foldLimit * (s - 1.0f);
						z.y -= mut->foldLimit * (s - 1.0f);
						z.z -= mut->foldLimit * (s - 1.0f);
						aux.DE *= s;
						break;
					}
					case 5: // abs fold (tglad)
					{
						z.x = fabs(z.x + mut->foldLimit) - fabs(z.x - mut->foldLimit) - z.x;
						z.y = fabs(z.y + mut->foldLimit) - fabs(z.y - mut->foldLimit) - z.y;
						z.z = fabs(z.z + mut->foldLimit) - fabs(z.z - mut->foldLimit) - z.z;
						break;
					}
					case 6: // kaleidoscope
					{
						int sides = mut->kaleidoscopeSides;
						if (sides >= 3)
						{
							float angle = M_PI_F / (float)sides;
							float pAngle = atan2(z.y, z.x);
							float r = native_sqrt(z.x*z.x + z.y*z.y);
							pAngle = fmod(pAngle + angle, 2.0f * angle) - angle;
							z.x = r * native_cos(pAngle);
							z.y = r * native_sin(pAngle);
							z.y = fabs(z.y);
						}
						break;
					}
					case 7: // octahedral fold
					{
						if (z.x + z.y < 0) { float tx = -z.y; z.y = -z.x; z.x = tx; }
						if (z.x + z.z < 0) { float tx = -z.z; z.z = -z.x; z.x = tx; }
						if (z.y + z.z < 0) { float ty = -z.z; z.z = -z.y; z.y = ty; }
						if (z.x - z.y < 0) { float tx = z.y; z.y = z.x; z.x = tx; }
						if (z.x - z.z < 0) { float tx = z.z; z.z = z.x; z.x = tx; }
						break;
					}
				}
			}

			// Component swizzle
			switch (mut->swizzle)
			{
				case 0: break;
				case 1: { float t = z.y; z.y = z.z; z.z = t; } break;
				case 2: { float t = z.x; z.x = z.y; z.y = t; } break;
				case 3: { float t = z.x; z.x = z.y; z.y = z.z; z.z = t; } break;
				case 4: { float t = z.z; z.z = z.y; z.y = z.x; z.x = t; } break;
				case 5: { float t = z.x; z.x = z.z; z.z = t; } break;
			}

			// Warp distortion
			if (mut->warpType == 1) // sine
			{
				z.x += mut->warpAmplitude * native_sin(z.y * mut->warpFrequency);
				z.y += mut->warpAmplitude * native_sin(z.z * mut->warpFrequency);
				z.z += mut->warpAmplitude * native_sin(z.x * mut->warpFrequency);
			}
			else if (mut->warpType == 2) // twist
			{
				float angle = z.z * mut->warpFrequency * M_PI_F / 180.0f;
				float ca = native_cos(angle * mut->warpAmplitude);
				float sa = native_sin(angle * mut->warpAmplitude);
				float nx = z.x * ca - z.y * sa; float ny = z.x * sa + z.y * ca;
				z.x = nx; z.y = ny;
			}
			else if (mut->warpType == 3) // spiral
			{
				float r = native_sqrt(z.x*z.x + z.y*z.y);
				float angle = r * mut->warpFrequency;
				float ca = native_cos(angle * mut->warpAmplitude);
				float sa = native_sin(angle * mut->warpAmplitude);
				float nx = z.x * ca - z.y * sa; float ny = z.x * sa + z.y * ca;
				z.x = nx; z.y = ny;
			}
			else if (mut->warpType == 4) // radial
			{
				float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
				if (r > 1e-21f)
				{
					float warp = mut->warpAmplitude * native_sin(r * mut->warpFrequency);
					z.x += z.x / r * warp; z.y += z.y / r * warp; z.z += z.z / r * warp;
				}
			}
			else if (mut->warpType == 5) // cylindrical
			{
				float r = native_sqrt(z.x*z.x + z.y*z.y);
				if (r > 1e-21f)
				{
					float angle = atan2(z.y, z.x);
					angle += mut->warpAmplitude * native_sin(z.z * mut->warpFrequency);
					z.x = r * native_cos(angle); z.y = r * native_sin(angle);
				}
			}
			else if (mut->warpType == 6) // spherical inversion
			{
				float rr = z.x*z.x + z.y*z.y + z.z*z.z;
				float radius2 = mut->warpFrequency * mut->warpFrequency;
				if (rr > 1e-21f)
				{
					float factor = radius2 / rr;
					factor = 1.0f + (factor - 1.0f) * mut->warpAmplitude;
					z *= factor; aux.DE *= fabs(factor);
				}
			}
			else if (mut->warpType == 7) // mobius
			{
				float r2 = z.x*z.x + z.y*z.y;
				if (r2 > 1e-21f)
				{
					float angle = mut->warpAmplitude * mut->warpFrequency / (r2 + 1.0f);
					float ca = native_cos(angle); float sa = native_sin(angle);
					float nx = z.x * ca - z.y * sa; float ny = z.x * sa + z.y * ca;
					z.x = nx; z.y = ny;
				}
			}

			// Math injection (GPU)
			if (mut->mathType != 0)
			{
				float4 mathZ = z;
				switch (mut->mathType)
				{
					case 1: // SinPower
					{
						float p = mut->mathP1;
						mathZ.x = sign(native_sin(z.x)) * pow(fabs(native_sin(z.x)), p);
						mathZ.y = sign(native_sin(z.y)) * pow(fabs(native_sin(z.y)), p);
						mathZ.z = sign(native_sin(z.z)) * pow(fabs(native_sin(z.z)), p);
						break;
					}
					case 2: // CoshField
					{
						float freq = mut->mathP1;
						float amp = mut->mathP2;
						mathZ.x = z.x + amp * (cosh(z.y * freq) - 1.0f);
						mathZ.y = z.y + amp * (cosh(z.z * freq) - 1.0f);
						mathZ.z = z.z + amp * (cosh(z.x * freq) - 1.0f);
						break;
					}
					case 3: // ExpMap
					{
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						if (r > 1e-21f)
						{
							float er = native_exp(mut->mathP1 * native_log(r + 1.0f));
							float theta = atan2(native_sqrt(z.x*z.x + z.y*z.y), z.z);
							float phi = atan2(z.y, z.x);
							mathZ.x = er * native_sin(theta + mut->mathP2) * native_cos(phi + mut->mathP3);
							mathZ.y = er * native_sin(theta + mut->mathP2) * native_sin(phi + mut->mathP3);
							mathZ.z = er * native_cos(theta + mut->mathP2);
						}
						break;
					}
					case 4: // LogSpiral
					{
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						if (r > 1e-21f)
						{
							float lr = native_log(r + 1e-21f) * mut->mathP1;
							float theta = atan2(native_sqrt(z.x*z.x + z.y*z.y), z.z);
							float phi = atan2(z.y, z.x);
							float spiralAngle = phi + lr * mut->mathP2;
							float newR = native_exp(lr);
							mathZ.x = newR * native_sin(theta) * native_cos(spiralAngle);
							mathZ.y = newR * native_sin(theta) * native_sin(spiralAngle);
							mathZ.z = newR * native_cos(theta);
						}
						break;
					}
					case 5: // PowerN
					{
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						if (r > 1e-21f)
						{
							float n = mut->mathP1;
							float theta = acos(z.z / r);
							float phi = atan2(z.y, z.x);
							float rn = pow(r, n);
							float nTheta = n * theta + mut->mathP2;
							float nPhi = n * phi + mut->mathP3;
							mathZ.x = rn * native_sin(nTheta) * native_cos(nPhi);
							mathZ.y = rn * native_sin(nTheta) * native_sin(nPhi);
							mathZ.z = rn * native_cos(nTheta);
							aux.DE = pow(r, n - 1.0f) * n * aux.DE + 1.0f;
						}
						break;
					}
					case 6: // ComplexMul
					{
						float cr = mut->mathP1;
						float ci = mut->mathP2;
						mathZ.x = z.x * cr - z.y * ci;
						mathZ.y = z.x * ci + z.y * cr;
						mathZ.z = z.z * native_sqrt(cr*cr + ci*ci);
						break;
					}
					case 7: // QuaternionMul
					{
						float qr = mut->mathP1, qi = mut->mathP2;
						float qj = mut->mathP3, qk = mut->mathP4;
						float zi = z.x, zj = z.y, zk = z.z;
						mathZ.x = zi*qr + zj*qk - zk*qj;
						mathZ.y = -zi*qk + zj*qr + zk*qi;
						mathZ.z = zi*qj - zj*qi + zk*qr;
						break;
					}
					case 8: // Bilinear
					{
						float a = mut->mathP1, b = mut->mathP2;
						float c = mut->mathP3, d = mut->mathP4;
						float rxy = native_sqrt(z.x*z.x + z.y*z.y);
						float denom = c * rxy + d;
						if (fabs(denom) > 1e-21f)
						{
							float scale = (a * rxy + b) / denom;
							mathZ.x = z.x * scale; mathZ.y = z.y * scale; mathZ.z = z.z * scale;
							aux.DE *= fabs(scale);
						}
						break;
					}
					case 9: // InvCylindrical
					{
						float rxy = native_sqrt(z.x*z.x + z.y*z.y);
						float radius = mut->mathP1;
						if (rxy > 1e-21f)
						{
							float radius2 = radius * radius;
							float scale = radius2 / (rxy * rxy);
							mathZ.x = z.x * scale; mathZ.y = z.y * scale; mathZ.z = z.z;
							aux.DE *= scale;
						}
						break;
					}
					case 10: // SpiralPower
					{
						float angle = mut->mathP1 * M_PI_F / 180.0f;
						float scale = mut->mathP2 != 0.0f ? mut->mathP2 : 1.0f;
						float ca = native_cos(angle); float sa = native_sin(angle);
						mathZ.x = (z.x * ca - z.y * sa) * scale;
						mathZ.y = (z.x * sa + z.y * ca) * scale;
						mathZ.z = z.z * scale;
						aux.DE *= fabs(scale);
						break;
					}
					case 11: // HyperbolicRot
					{
						float angle = mut->mathP1;
						float ch = cosh(angle); float sh = sinh(angle);
						mathZ.x = z.x * ch + z.z * sh;
						mathZ.z = z.x * sh + z.z * ch;
						mathZ.y = z.y;
						break;
					}
				}
				if (mut->mathMix < 1.0f)
				{
					float m = mut->mathMix;
					z = mathZ * m + z * (1.0f - m);
				}
				else
				{
					z = mathZ;
				}
			}
		}

#if defined(IS_HYBRID) || defined(BOOLEAN_OPERATORS)
			switch (sequence)
			{
				case 0: z = FORMULA_ITER_0(z, fractal, &aux); break;
				case 1: z = FORMULA_ITER_1(z, fractal, &aux); break;
				case 2: z = FORMULA_ITER_2(z, fractal, &aux); break;
				case 3: z = FORMULA_ITER_3(z, fractal, &aux); break;
				case 4: z = FORMULA_ITER_4(z, fractal, &aux); break;
				case 5: z = FORMULA_ITER_5(z, fractal, &aux); break;
				case 6: z = FORMULA_ITER_6(z, fractal, &aux); break;
				case 7: z = FORMULA_ITER_7(z, fractal, &aux); break;
				case 8: z = FORMULA_ITER_8(z, fractal, &aux); break;
			}
#else	 // not HYBRID and not BOOLEAN
		z = FORMULA_ITER_0(z, fractal, &aux);
#endif // defined(IS_HYBRID) || defined(BOOLEAN_OPERATORS)

		if (aux.r < 0.0f) // if was run DummyIteration
		{
			float high = consts->sequence.bailout[sequence] * 10.0f;
			z = high;
			aux.r = length(z);
			out.distance = 10.0f;
			out.iters = 1;
			out.z = z;
			out.colorIndex = 0.0f;
			return out;
		}

		// addition of constant (inside weight guard — skipped when weight=0)
		if (consts->sequence.addCConstant[sequence])
		{
			switch (fractal->formula)
			{
				case 64: // aboxMod1
				case 73: // amazingSurf
				{
					if (consts->sequence.juliaEnabled[sequence])
					{
						float4 juliaC = consts->sequence.juliaConstant[sequence]
														* consts->sequence.constantMultiplier[sequence];
						z += (float4){juliaC.y, juliaC.x, juliaC.z, juliaC.w};
					}
					else
					{
						z += (float4){aux.const_c.y, aux.const_c.x, aux.const_c.z, aux.const_c.w}
								 * consts->sequence.constantMultiplier[sequence];
					}
					break;
				}

				default:
				{
					if (consts->sequence.juliaEnabled[sequence])
					{
						z += consts->sequence.juliaConstant[sequence]
								 * consts->sequence.constantMultiplier[sequence];
					}
					else
					{
						z += aux.const_c * consts->sequence.constantMultiplier[sequence];
					}
				}
			}
		}

#ifdef ITERATION_WEIGHT
		}
#endif

		// -------------- Formula Mutation post-processing (GPU) ---------------
		if (mutationActive)
		{
			__constant sClFormulaMutationParams *mut = &consts->sequence.mutationParams[sequence];

			// Fold injection (post or both)
			if (mut->foldType != 0 && (mut->foldPosition == 1 || mut->foldPosition == 2))
			{
				switch (mut->foldType)
				{
					case 1:
						if (fabs(z.x) > mut->foldLimit) z.x = sign(z.x) * mut->foldValue - z.x;
						if (fabs(z.y) > mut->foldLimit) z.y = sign(z.y) * mut->foldValue - z.y;
						if (fabs(z.z) > mut->foldLimit) z.z = sign(z.z) * mut->foldValue - z.z;
						break;
					case 2:
					{
						float rr = z.x*z.x + z.y*z.y + z.z*z.z;
						float minR2 = mut->foldLimit * mut->foldLimit;
						float fixR2 = mut->foldValue * mut->foldValue;
						if (rr < minR2) { z *= fixR2/minR2; aux.DE *= fixR2/minR2; }
						else if (rr < fixR2) { z *= fixR2/rr; aux.DE *= fixR2/rr; }
						break;
					}
					case 3:
					{
						z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z);
						if (z.x - z.y < 0) { float t = z.y; z.y = z.x; z.x = t; }
						if (z.x - z.z < 0) { float t = z.z; z.z = z.x; z.x = t; }
						if (z.y - z.z < 0) { float t = z.z; z.z = z.y; z.y = t; }
						float s = mut->foldValue;
						z.x = z.x * s - mut->foldLimit * (s - 1.0f);
						z.y = z.y * s - mut->foldLimit * (s - 1.0f);
						z.z = z.z * s;
						if (z.z > 0.5f * mut->foldLimit * (s - 1.0f))
							z.z -= mut->foldLimit * (s - 1.0f);
						aux.DE *= s;
						break;
					}
					case 4:
					{
						if (z.x + z.y < 0) { float tx = -z.y; z.y = -z.x; z.x = tx; }
						if (z.x + z.z < 0) { float tx = -z.z; z.z = -z.x; z.x = tx; }
						if (z.y + z.z < 0) { float ty = -z.z; z.z = -z.y; z.y = ty; }
						float s = mut->foldValue;
						z *= s;
						z.x -= mut->foldLimit * (s - 1.0f);
						z.y -= mut->foldLimit * (s - 1.0f);
						z.z -= mut->foldLimit * (s - 1.0f);
						aux.DE *= s;
						break;
					}
					case 5:
					{
						z.x = fabs(z.x + mut->foldLimit) - fabs(z.x - mut->foldLimit) - z.x;
						z.y = fabs(z.y + mut->foldLimit) - fabs(z.y - mut->foldLimit) - z.y;
						z.z = fabs(z.z + mut->foldLimit) - fabs(z.z - mut->foldLimit) - z.z;
						break;
					}
					case 6:
					{
						int sides = mut->kaleidoscopeSides;
						if (sides >= 3)
						{
							float angle = M_PI_F / (float)sides;
							float pAngle = atan2(z.y, z.x);
							float r = native_sqrt(z.x*z.x + z.y*z.y);
							pAngle = fmod(pAngle + angle, 2.0f * angle) - angle;
							z.x = r * native_cos(pAngle);
							z.y = r * native_sin(pAngle);
							z.y = fabs(z.y);
						}
						break;
					}
					case 7:
					{
						if (z.x + z.y < 0) { float tx = -z.y; z.y = -z.x; z.x = tx; }
						if (z.x + z.z < 0) { float tx = -z.z; z.z = -z.x; z.x = tx; }
						if (z.y + z.z < 0) { float ty = -z.z; z.z = -z.y; z.y = ty; }
						if (z.x - z.y < 0) { float tx = z.y; z.y = z.x; z.x = tx; }
						if (z.x - z.z < 0) { float tx = z.z; z.z = z.x; z.x = tx; }
						break;
					}
				}
			}

			// Post-rotation
			if (mut->postRotX != 0.0f || mut->postRotY != 0.0f || mut->postRotZ != 0.0f)
			{
				float3 zr;
				zr.x = mut->postRotMatrix[0]*z.x + mut->postRotMatrix[1]*z.y + mut->postRotMatrix[2]*z.z;
				zr.y = mut->postRotMatrix[3]*z.x + mut->postRotMatrix[4]*z.y + mut->postRotMatrix[5]*z.z;
				zr.z = mut->postRotMatrix[6]*z.x + mut->postRotMatrix[7]*z.y + mut->postRotMatrix[8]*z.z;
				z.x = zr.x; z.y = zr.y; z.z = zr.z;
			}
			if (mut->postScale != 1.0f) { z *= mut->postScale; aux.DE *= mut->postScale; }
			z.x += mut->postOffsetX; z.y += mut->postOffsetY; z.z += mut->postOffsetZ;
			if (mut->zMix < 1.0f) { float m = mut->zMix; z = z * m + preMutZ * (1.0f - m); }
			if (mut->deScale != 1.0f) aux.DE *= mut->deScale;
		}

#ifdef ITERATION_WEIGHT
		// Apply weight blending in hybrid mode
		if (consts->sequence.isHybrid && effectiveWeight < 1.0f)
		{
			__constant sClFormulaWeightParams *wp = &consts->sequence.weightParams[sequence];
			bool isPKFormula = (consts->sequence.DEFunctionType[sequence] == pseudoKleinianDEFunction);
			float blendCurve = wp->componentBlendCurve;
			if (wp->separateComponents)
			{
				float kz = effectiveWeight * wp->zVectorWeight;
				float kde = effectiveWeight * wp->deComponentWeight;
				float kdist = effectiveWeight * wp->distComponentWeight;
				float kcol = effectiveWeight * wp->colorComponentWeight;

				if (blendCurve != 1.0f)
				{
					if (kz > 0.0f && kz < 1.0f) kz = pow(kz, blendCurve);
					if (kde > 0.0f && kde < 1.0f) kde = pow(kde, blendCurve);
					if (kdist > 0.0f && kdist < 1.0f) kdist = pow(kdist, blendCurve);
					if (kcol > 0.0f && kcol < 1.0f) kcol = pow(kcol, blendCurve);
				}

				if (kz < 1.0f) z = SmoothCVector(tempZ, z, kz);

				if (kde < 1.0f)
				{
					float kden = 1.0f - kde;
					aux.DE = aux.DE * kde + tempAuxDE * kden;
					aux.DE0 = aux.DE0 * kde + tempAuxDE0 * kden;
					if (isPKFormula)
						aux.pseudoKleinianDE = aux.pseudoKleinianDE * kde + tempAuxPseudoKleinianDE * kden;
					aux.actualScale = aux.actualScale * kde + tempAuxActualScale * kden;
					aux.actualScaleA = aux.actualScaleA * kde + tempAuxActualScaleA * kden;
				}

				if (kdist < 1.0f)
				{
					float kdistn = 1.0f - kdist;
					aux.dist = aux.dist * kdist + tempAuxDist * kdistn;
				}

				if (kcol < 1.0f)
				{
					float kcoln = 1.0f - kcol;
					aux.color = aux.color * kcol + tempAuxColor * kcoln;
					aux.colorHybrid = aux.colorHybrid * kcol + tempAuxColorHybrid * kcoln;
					aux.temp1000 = aux.temp1000 * kcol + tempAuxTemp1000 * kcoln;
				}
			}
			else
			{
				float k = effectiveWeight;
				if (blendCurve != 1.0f && k > 0.0f && k < 1.0f) k = pow(k, blendCurve);
				z = SmoothCVector(tempZ, z, k);
				float kn = 1.0f - k;
				aux.DE = aux.DE * k + tempAuxDE * kn;
				aux.DE0 = aux.DE0 * k + tempAuxDE0 * kn;
				aux.dist = aux.dist * k + tempAuxDist * kn;
				if (isPKFormula)
					aux.pseudoKleinianDE = aux.pseudoKleinianDE * k + tempAuxPseudoKleinianDE * kn;
				aux.actualScale = aux.actualScale * k + tempAuxActualScale * kn;
				aux.actualScaleA = aux.actualScaleA * k + tempAuxActualScaleA * kn;
				aux.color = aux.color * k + tempAuxColor * kn;
				aux.colorHybrid = aux.colorHybrid * k + tempAuxColorHybrid * kn;
				aux.temp1000 = aux.temp1000 * k + tempAuxTemp1000 * kn;
			}
		}
#endif // ITERATION_WEIGHT

		// calculate r

		aux.r = length(z);

		// escape conditions
		if (consts->sequence.checkForBailout[sequence])
		{
			// mode normal or deltaDE center point
			if (mode == calcModeNormal || mode == calcModeDeltaDE1)
			{
				if (aux.r > consts->sequence.bailout[sequence])
				{
					out.maxiter = false;
					break;
				}

				if (consts->sequence.useAdditionalBailoutCond[sequence])
				{
					out.maxiter = false;
					if (length(z - lastZ) / aux.r < 0.1f / consts->sequence.bailout[sequence]) break;
					if (length(z - lastLastZ) / aux.r < 0.1f / consts->sequence.bailout[sequence]) break;
				}
			}
			else if (mode == calcModeDeltaDE2)
			{
				if (i == calcParam->deltaDEMaxN) break;
			}
			else if (mode == calcModeColouring)
			{
				float len = 0.0f;
				float4 colorZ = z;
				if (!fractalColoring->color4dEnabledFalse) colorZ.w = 0.0f;
#ifdef USE_COLORING_MODES
				switch (fractalColoring->coloringAlgorithm)
				{
					case fractalColoringCl_Standard:
					{
						len = length(colorZ);
						break;
					}
					case fractalColoringCl_ZDotPoint:
					{
						len = fabs(dot((float4){point4D.x, point4D.y, point4D.z, initialWAxisColor}, colorZ));
						break;
					}
					case fractalColoringCl_Sphere:
					{
						len = fabs(length(colorZ - (float4){point4D.x, point4D.y, point4D.z, initialWAxisColor})
											 - fractalColoring->sphereRadius);
						break;
					}
					case fractalColoringCl_Cross:
					{
						len = min(min(fabs(colorZ.x), fabs(colorZ.y)), fabs(colorZ.z));
						if (fractalColoring->color4dEnabledFalse) len = min(len, fabs(colorZ.w));
						break;
					}
					case fractalColoringCl_Line:
					{
						len = fabs(dot(fractalColoring->lineDirection, colorZ));
						break;
					}
					case fractalColoringCl_Cylinder:
					{
						float distFromAxis = sqrt(colorZ.x * colorZ.x + colorZ.y * colorZ.y);
						len = fabs(distFromAxis - fractalColoring->sphereRadius);
						break;
					}
					case fractalColoringCl_Torus:
					{
						float majorR = fractalColoring->sphereRadius;
						float distXY = sqrt(colorZ.x * colorZ.x + colorZ.y * colorZ.y) - majorR;
						len = sqrt(distXY * distXY + colorZ.z * colorZ.z);
						break;
					}
					case fractalColoringCl_None:
					{
						len = aux.r;
						break;
					}
				}
#else
				len = length(colorZ);
#endif // USE_COLORING_MODES
				if (!fractalColoring->colorPreV215False)
				{
					if (fractal->formula != 8)
					{
						if (len < colorMin) colorMin = len;
						if (aux.r > consts->sequence.bailout[sequence]) break;
						if (consts->sequence.useAdditionalBailoutCond[sequence]
								&& length(z - lastZ) / aux.r < 1e-15f)
							break;
					}
					else // for Mandelbox. Note in Normal Mode (abox_color) colorMin = 0, else has a value
					{
						if (fractalColoring->coloringAlgorithm == fractalColoringCl_Standard)
						{
							if (aux.r > 1e15f || length(z - lastZ) / aux.r < 1e-15f) break;
						}
						else
						{
							if (len < colorMin) colorMin = len; // colorMin for hybrid mode ??
							if (aux.r > consts->sequence.bailout[sequence] || length(z - lastZ) / aux.r < 1e-15f)
								break;
						}
					}
				}
				else // pre-2.15
				{
					if (fractal->formula != 8) // if not mandelbox
					{
						if (len < colorMin) colorMin = len;
						if (aux.r > 1e15f || length(z - lastZ) / aux.r < 1e-15f) break;
					}
					else
					{
						if (aux.r > 1e15f || length(z - lastZ) / aux.r < 1e-15f) break;
					}
					// if (aux.r > 1e15f) break; // old
				}
			}
#ifdef FAKE_LIGHTS
			// Auto-center: capture z at specified iteration
			if (mode == calcModeOrbitTrap && !autoTrapCenterSet
				&& consts->params.common.fakeLightsCenterIteration > 0
				&& i == consts->params.common.fakeLightsCenterIteration)
			{
				autoTrapCenter = z;
				autoTrapCenterSet = true;
			}

			if (mode == calcModeOrbitTrap)
			{
				float4 trapPoint;
				if (autoTrapCenterSet)
				{
					trapPoint = z - autoTrapCenter;
				}
				else if (consts->params.common.fakeLightsRelativeCenter)
				{
					trapPoint = z - aux.const_c;
				}
				else
				{
					trapPoint = z;
				}
						float distance;
						int minCenterIndex = 0;
				if (consts->params.common.fakeLightsMultiCenterEnabled)
				{
					// Multi-center: evaluate distance to all 24 trap positions, take weighted minimum
					distance = 1e30f;
					for (int mc = 0; mc < 24; mc++)
					{
						if (consts->params.common.fakeLightsMultiCenterWeight[mc] <= 0.0f) continue;

						// OrbitTrapShapeDistance calculates: delta = z - par->fakeLightsOrbitTrap
						// We want: delta = trapPoint - multiCenter[mc]
						// So: pass (trapPoint - multiCenter[mc] + par->fakeLightsOrbitTrap) as input
						float4 shiftedPoint = trapPoint
							- (float4)(consts->params.common.fakeLightsMultiCenter[mc].x,
							           consts->params.common.fakeLightsMultiCenter[mc].y,
							           consts->params.common.fakeLightsMultiCenter[mc].z, 0.0f)
							+ (float4)(consts->params.common.fakeLightsOrbitTrap.x,
							           consts->params.common.fakeLightsOrbitTrap.y,
							           consts->params.common.fakeLightsOrbitTrap.z, 0.0f);

						float d = OrbitTrapShapeDistance(shiftedPoint, consts, calcParam);
						d /= consts->params.common.fakeLightsMultiCenterWeight[mc];
							if (d < distance)
							{
								distance = d;
								minCenterIndex = mc;
							}
					}
				}
				else
				{
					distance = OrbitTrapShapeDistance(trapPoint, consts, calcParam);
				}

				if (i >= fakeLightsMinIter && i <= fakeLightsMaxIter)
				{
					float contribution;
					switch (consts->params.common.fakeLightsDecayFunction)
					{
						case 1: // fakeLightsDecay1R
							contribution = 1.0f / (distance + 1e-30f);
							break;
						case 2: // fakeLightsDecay1R3
							contribution = 1.0f / (distance * distance * distance + 1e-30f);
							break;
						case 3: // fakeLightsDecayLinear
							contribution = max(1.0f - distance * 0.1f, 0.0f);
							break;
						case 4: // fakeLightsDecayExp
							contribution = exp(-distance);
							break;
						default: // fakeLightsDecay1R2 (case 0)
							contribution = 1.0f / (distance * distance + 1e-30f);
							break;
					}
					orbitTrapTotal += contribution;

					// Track which iteration had the closest approach
					if (distance < orbitTrapMinDist)
					{
						orbitTrapMinDist = distance;
						orbitTrapMinIter = i;
						out.orbitTrapCenterIndex = minCenterIndex;
					}
				}
				if (distance > consts->sequence.bailout[sequence])
				{
					out.orbitTrapR = orbitTrapTotal;
					out.orbitTrapMinIter = orbitTrapMinIter;
					break;
				}
			}
#endif // FAKE_LIGHTS
#ifdef FRACTALIZE_TEXTURE
			else if (mode == calcModeCubeOrbitTrap)
			{
				if (i >= material->textureFractalizeStartIteration)
				{
					float size = material->textureFractalizeCubeSize * material->textureFractalizeSizeMultiplier;
					float3 trapCenter = pointTransformed + material->textureFractalizeOrbitTrapPosition;
					float3 zz = z.xyz - trapCenter;
					bool trapHit = false;

					switch (material->textureFractalizeShape)
					{
						case 0: // fractalizeShapeCube
						{
							if (zz.x > -size && zz.x < size && zz.y > -size && zz.y < size && zz.z > -size
									&& zz.z < size)
							{
								trapHit = true;
							}
							break;
						}
						case 1: // fractalizeShapeSphere
						{
							if (length(zz) < size)
							{
								trapHit = true;
							}
							break;
						}
						case 2: // fractalizeShapeCross
						{
							float minDist = min(min(fabs(zz.x), fabs(zz.y)), fabs(zz.z));
							if (minDist < size)
							{
								trapHit = true;
							}
							break;
						}
						case 3: // fractalizeShapeLine
						{
							// Line along Z axis by default (user can rotate with texture rotation)
							float distFromLine = sqrt(zz.x * zz.x + zz.y * zz.y);
							if (distFromLine < size)
							{
								trapHit = true;
							}
							break;
						}
						case 4: // fractalizeShapePlane
						{
							if (fabs(zz.z) < size)
							{
								trapHit = true;
							}
							break;
						}
						case 5: // fractalizeShapeCylinder
						{
							float distFromAxis = sqrt(zz.x * zz.x + zz.y * zz.y);
							if (distFromAxis < size && fabs(zz.z) < size * 2.0f)
							{
								trapHit = true;
							}
							break;
						}
						case 6: // fractalizeShapeTorus
						{
							float majorR = size;
							float minorR = size * 0.4f;
							float distXY = sqrt(zz.x * zz.x + zz.y * zz.y) - majorR;
							float distTorus = sqrt(distXY * distXY + zz.z * zz.z);
							if (distTorus < minorR)
							{
								trapHit = true;
							}
							break;
						}
						case 7: // fractalizeShapeSpiral
						{
							float angle = atan2(zz.y, zz.x);
							float r = sqrt(zz.x * zz.x + zz.y * zz.y);
							float spiralR = size * (angle + M_PI_F) / (2.0f * M_PI_F);
							float spiralDist = fmod(fabs(r - spiralR), size);
							if (spiralDist > size * 0.5f) spiralDist = size - spiralDist;
							if (spiralDist < size * 0.3f && fabs(zz.z) < size)
							{
								trapHit = true;
							}
							break;
						}
					}

					if (trapHit)
					{
						out.colorIndex = (fabs(z.x - size) + fabs(z.y - size) + fabs(z.z - size)) * 100.0f;
						out.iters = i + 1;
						out.z = z;

						// If iteration blending is disabled, return immediately
						if (!material->textureFractalizeIterationBlend)
						{
							return out;
						}
						// Otherwise continue iterating to blend between iteration levels
					}
				}
				if (aux.r > material->textureFractalizeCubeSize * 100.0f)
				{
					out.colorIndex = 0.0f;
					out.iters = i + 1;
					out.z = z;
					return out;
				}
			}
#endif // FRACTALIZE_TEXTURE
		}
	}

	if (mode == calcModeOrbitTrap)
	{
		out.orbitTrapR = orbitTrapTotal;
	}

	// calculate estimated distance

#ifdef IS_HYBRID
#ifdef ANALYTIC_LOG_DE
	if (aux.r > 1.0f)
		dist = 0.5f * aux.r * native_log(aux.r) / fabs(aux.DE);
	else
		dist = 0.0f;
#elif ANALYTIC_LINEAR_DE
	dist = (aux.r - consts->params.common.linearDEOffset) / fabs(aux.DE);
#elif ANALYTIC_PSEUDO_KLEINIAN_DE
	float rxy = length(z.xy);
	dist = max(rxy - aux.pseudoKleinianDE, fabs(rxy * z.z) / aux.r) / fabs(aux.DE);
#elif ANALYTIC_JOS_KLEINIAN_DE
	if (consts->fractal[0].transformCommon.spheresEnabled)
		z.y = min(z.y, consts->fractal[0].transformCommon.foldingValue - z.y);
	dist = min(z.y, consts->fractal[0].analyticDE.tweak005)
				 / max(fabs(aux.DE), consts->fractal[0].analyticDE.offset1);
#elif ANALYTIC_CUSTOM_DE
	dist = aux.dist;
#elif ANALYTIC_MAXAXIS_DE
	float4 absZ = fabs(z);
	float rd = max(absZ.x, max(absZ.y, absZ.z));
	dist = rd / aux.DE;
#else
	dist = length(z);
#endif

#else //  IS_NOT HYBRID
	if (aux.DE > 0.0)
	{
		switch (consts->sequence.DEAnalyticFunction[sequence])
		{
			case clAnalyticFunctionLogarithmic:
			{
				if (aux.r > 1.0f)
					dist = 0.5f * aux.r * native_log(aux.r) / aux.DE;
				else
					dist = 0.0f;
				break;
			}
			case clAnalyticFunctionLinear:
			{
				dist = aux.r / aux.DE;
				break;
			}
			case clAnalyticFunctionIFS:
			{
				dist = (aux.r - 2.0) / aux.DE;
				break;
			}
			case clAnalyticFunctionPseudoKleinian:
			{
				float rxy = length(z.xy);
				dist = max(rxy - aux.pseudoKleinianDE, fabs(rxy * z.z) / aux.r) / aux.DE;
				break;
			}
			case clAnalyticFunctionJosKleinian:
			{
				if (fractal->transformCommon.spheresEnabled)
					z.y = min(z.y, fractal->transformCommon.foldingValue - z.y);
				dist = min(z.y, fractal->analyticDE.tweak005) / max(aux.DE, fractal->analyticDE.offset1);
				break;
			}
			case clAnalyticFunctionCustomDE:
			{
				dist = aux.dist;
				break;
			}
			case clAnalyticFunctionMaxAxis:
			{
				float4 absZ = fabs(z);
				float rd = max(absZ.x, max(absZ.y, absZ.z));
				dist = rd / aux.DE;
				break;
			}
			case clAnalyticFunctionNone: dist = -1.0; break;
			case clAnalyticFunctionUndefined: dist = aux.r; break;
		}
	}
	else
		dist = 0;

#endif // IS_HYBRID

#ifdef USE_FRACTAL_COLORING
	if (mode == calcModeColouring)
	{
		enumColoringFunctionCl coloringFunction = consts->sequence.coloringFunction[sequence];
		out.colorIndex = CalculateColorIndex(consts->sequence.isHybrid, aux.r, z, colorMin, &aux,
			fractalColoring, coloringFunction, defaultFractal);
	}
#endif

#ifdef DELTA_JOS_KLEINIAN_DE
	// needed for JosKleinian fractal to calculate spheres in deltaDE mode
	if (consts->fractal[sequence].transformCommon.spheresEnabled)
		z.y = min(z.y, consts->fractal[sequence].transformCommon.foldingValue - z.y);
#endif

	// end
	if (dist < 0.0f) dist = 0.0f;
	out.distance = dist;
	out.iters = i + 1;
	{
		float r = length(z.xyz);
		float bailout = consts->sequence.bailout[0];
		if (!out.maxiter && r > bailout && bailout > 1.0f)
			out.iters = out.iters + 1.0f
				- native_log(native_log(r) / native_log(bailout)) / native_log(2.0f);
	}
	out.z = z;
	out.orbitTrapMinIter = orbitTrapMinIter;
	out.pseudoKleinianDE = aux.pseudoKleinianDE;
	out.finalDE = aux.DE;

	return out;
}

#endif /* MANDELBULBER2_OPENCL_ENGINES_COMPUTE_FRACTAL_CL_ */

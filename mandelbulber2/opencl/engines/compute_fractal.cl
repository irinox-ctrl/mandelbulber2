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

	// v7.5 — Julia start mode (z₀ override, GPU)
	{
		__global const sClFormulaMutationParams *jm0 = &consts->sequence.mutationParams[0];
		if (jm0->enabled && jm0->juliaStart != 0)
		{
			if (jm0->juliaStart == 1) z = aux.const_c; // z₀ = c
			else if (jm0->juliaStart == 2) z = z + aux.const_c; // z₀ = ray + c
			else if (jm0->juliaStart == 3) { aux.const_c = z; aux.c = z; z = (float4)(0.0f, 0.0f, 0.0f, 0.0f); }
			else if (jm0->juliaStart == 4) z = (float4)(aux.const_c.x, aux.const_c.y, aux.const_c.z, aux.const_c.w);
		}
	}

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
			__global const sClFormulaWeightParams *wp = &consts->sequence.weightParams[sequence];
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

		// -------------- Formula Mutation pre-processing (GPU) ---------------
		float4 preMutZ = z;
		bool mutationActive = consts->sequence.mutationParams[sequence].enabled
			&& i >= consts->sequence.mutationParams[sequence].iterationStart
			&& i < consts->sequence.mutationParams[sequence].iterationStop;

#ifdef ITERATION_WEIGHT
		if (effectiveWeight > 0.0f)
		{
#endif
		if (mutationActive)
		{
			__global const sClFormulaMutationParams *mut = &consts->sequence.mutationParams[sequence];

			if (mut->preAbsX) z.x = fabs(z.x);
			if (mut->preAbsY) z.y = fabs(z.y);
			if (mut->preAbsZ) z.z = fabs(z.z);
			z.x += mut->preOffsetX; z.y += mut->preOffsetY; z.z += mut->preOffsetZ;
			if (mut->preRotX != 0.0f || mut->preRotY != 0.0f || mut->preRotZ != 0.0f)
			{
				z.xyz = Matrix33MulFloat3(mut->preRotMatrix, z.xyz);
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
					case 8: // smooth fold (tanh)
					{
						float k = (mut->foldLimit > 0.0f) ? mut->foldLimit : 1.0f;
						z.x -= tanh(k * z.x);
						z.y -= tanh(k * z.y);
						z.z -= tanh(k * z.z);
						break;
					}
					case 9: // polynomial fold (Chebyshev z³-3z)
					{
						z.x = z.x * z.x * z.x - 3.0f * z.x;
						z.y = z.y * z.y * z.y - 3.0f * z.y;
						z.z = z.z * z.z * z.z - 3.0f * z.z;
						break;
					}
					case 10: // circular fold
					{
						float rad = (mut->foldValue > 0.0f) ? mut->foldValue : 1.0f;
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						if (r > 1e-21f) { float s = rad / r; z.x *= s; z.y *= s; z.z *= s; }
						break;
					}
					case 11: // spiral fold
					{
						float r = native_sqrt(z.x*z.x + z.y*z.y);
						float angle = r * mut->foldLimit;
						float ca = native_cos(angle); float sa = native_sin(angle);
						float nx = z.x * ca - z.y * sa;
						float ny = z.x * sa + z.y * ca;
						z.x = nx; z.y = ny;
						break;
					}
					case 12: // sinusoidal fold
					{
						float a = mut->foldValue;
						float b = (mut->foldLimit > 0.0f) ? mut->foldLimit : 1.0f;
						z.x += a * native_sin(b * z.x);
						z.y += a * native_sin(b * z.y);
						z.z += a * native_sin(b * z.z);
						break;
					}
					case 13: // exponential fold
					{
						z.x *= native_exp(-z.x * z.x);
						z.y *= native_exp(-z.y * z.y);
						z.z *= native_exp(-z.z * z.z);
						break;
					}
					case 14: // logarithmic fold
					{
						float rx = fabs(z.x); float ry = fabs(z.y); float rz = fabs(z.z);
						z.x *= native_log(1.0f + rx);
						z.y *= native_log(1.0f + ry);
						z.z *= native_log(1.0f + rz);
						break;
					}
					case 15: // power fold
					{
						float p = (mut->foldValue > 0.0f) ? mut->foldValue : 2.0f;
						float ax = fabs(z.x); float ay = fabs(z.y); float az = fabs(z.z);
						z.x = sign(z.x) * native_powr(max(ax, 1e-21f), p);
						z.y = sign(z.y) * native_powr(max(ay, 1e-21f), p);
						z.z = sign(z.z) * native_powr(max(az, 1e-21f), p);
						break;
					}
					case 16: // smooth abs
					{
						float k = (mut->foldLimit > 0.0f) ? mut->foldLimit : 5.0f;
						z.x = z.x * tanh(k * z.x);
						z.y = z.y * tanh(k * z.y);
						z.z = z.z * tanh(k * z.z);
						break;
					}
					case 17: // modulo wrap
					{
						float period = (mut->foldValue > 0.0f) ? mut->foldValue : 2.0f;
						z.x = fmod(z.x + period * 0.5f, period) - period * 0.5f;
						z.y = fmod(z.y + period * 0.5f, period) - period * 0.5f;
						z.z = fmod(z.z + period * 0.5f, period) - period * 0.5f;
						break;
					}
					case 18: // nested abs
					{
						float c = (mut->foldLimit > 0.0f) ? mut->foldLimit : 1.0f;
						z.x = fabs(fabs(z.x) - c);
						z.y = fabs(fabs(z.y) - c);
						z.z = fabs(fabs(z.z) - c);
						break;
					}
					case 19: // sawtooth
					{
						z.x = 2.0f * (z.x * 0.5f - floor(z.x * 0.5f + 0.5f));
						z.y = 2.0f * (z.y * 0.5f - floor(z.y * 0.5f + 0.5f));
						z.z = 2.0f * (z.z * 0.5f - floor(z.z * 0.5f + 0.5f));
						break;
					}
					case 20: // Bipolar
					{
						float c1 = mut->foldLimit;
						float c2 = -mut->foldLimit;
						z.x = fabs(z.x - c1) - fabs(z.x - c2);
						z.y = fabs(z.y - c1) - fabs(z.y - c2);
						z.z = fabs(z.z - c1) - fabs(z.z - c2);
						break;
					}
					case 21: // RadialBox
					{
						float r = native_sqrt(z.x*z.x + z.y*z.y);
						float theta = atan2(z.y, z.x);
						float foldR = mut->foldLimit;
						if (r > foldR) r = 2.0f * foldR - r;
						if (r < -foldR) r = -2.0f * foldR - r;
						z.x = r * native_cos(theta);
						z.y = r * native_sin(theta);
						aux.DE *= r / max(native_sqrt(z.x*z.x + z.y*z.y), 1e-21f);
						break;
					}
					case 22: // Shear
					{
						float lim = mut->foldLimit;
						if (z.x > lim) z.x = 2.0f * lim - z.x;
						else if (z.x < -lim) z.x = -2.0f * lim - z.x;
						if (z.y > lim) z.y = 2.0f * lim - z.y;
						else if (z.y < -lim) z.y = -2.0f * lim - z.y;
						z.x += mut->foldValue * z.y;
						z.y += mut->foldValue * z.z;
						break;
					}
					case 23: // 3DCross
					{
						float lim = mut->foldLimit;
						int phase = i % 3;
						if (phase == 0) {
							if (z.x > lim) z.x = 2.0f*lim - z.x;
							if (z.x < -lim) z.x = -2.0f*lim - z.x;
							if (z.y > lim) z.y = 2.0f*lim - z.y;
							if (z.y < -lim) z.y = -2.0f*lim - z.y;
						} else if (phase == 1) {
							if (z.y > lim) z.y = 2.0f*lim - z.y;
							if (z.y < -lim) z.y = -2.0f*lim - z.y;
							if (z.z > lim) z.z = 2.0f*lim - z.z;
							if (z.z < -lim) z.z = -2.0f*lim - z.z;
						} else {
							if (z.z > lim) z.z = 2.0f*lim - z.z;
							if (z.z < -lim) z.z = -2.0f*lim - z.z;
							if (z.x > lim) z.x = 2.0f*lim - z.x;
							if (z.x < -lim) z.x = -2.0f*lim - z.x;
						}
						break;
					}
					case 24: // Conformal
					{
						float r2 = z.x*z.x + z.y*z.y + z.z*z.z;
						if (r2 > 1e-21f)
						{
							z.x += z.x / r2;
							z.y += z.y / r2;
							z.z += z.z / r2;
							aux.DE *= fabs(1.0f - 1.0f / r2);
						}
						break;
					}
					case 25: // Rotation
					{
						float lim = mut->foldLimit;
						if (z.x > lim) z.x = 2.0f*lim - z.x;
						if (z.x < -lim) z.x = -2.0f*lim - z.x;
						if (z.y > lim) z.y = 2.0f*lim - z.y;
						if (z.y < -lim) z.y = -2.0f*lim - z.y;
						if (z.z > lim) z.z = 2.0f*lim - z.z;
						if (z.z < -lim) z.z = -2.0f*lim - z.z;
						float t = z.x; z.x = -z.y; z.y = t;
						break;
					}
					case 26: // ScalePulse
					{
						float lim = mut->foldLimit;
						if (z.x > lim) z.x = 2.0f*lim - z.x;
						if (z.x < -lim) z.x = -2.0f*lim - z.x;
						if (z.y > lim) z.y = 2.0f*lim - z.y;
						if (z.y < -lim) z.y = -2.0f*lim - z.y;
						if (z.z > lim) z.z = 2.0f*lim - z.z;
						if (z.z < -lim) z.z = -2.0f*lim - z.z;
						float pulse = 1.0f + 0.2f * native_sin((float)i * mut->foldValue);
						z *= pulse;
						aux.DE *= fabs(pulse);
						break;
					}
					case 27: // TriangleWave
					{
						z.x = 2.0f * fabs(z.x * 0.5f - floor(z.x * 0.5f + 0.5f));
						z.y = 2.0f * fabs(z.y * 0.5f - floor(z.y * 0.5f + 0.5f));
						z.z = 2.0f * fabs(z.z * 0.5f - floor(z.z * 0.5f + 0.5f));
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
			else if (mut->warpType == 8) // IFS contraction
			{
				float s0 = mut->warpAmplitude;
				float a = mut->warpFrequency;
				float s = s0 * (1.0f + a * native_sin((float)aux.i));
				z *= s;
				aux.DE = aux.DE * fabs(s) + 1.0f;
			}
			else if (mut->warpType == 9) // IFS rotation (golden angle)
			{
				float goldenAngle = 2.399963229728653f;
				float angle = goldenAngle * aux.i * mut->warpAmplitude;
				float ca = native_cos(angle); float sa = native_sin(angle);
				float nx = z.x * ca - z.y * sa; float ny = z.x * sa + z.y * ca;
				z.x = nx; z.y = ny;
			}
			else if (mut->warpType == 10) // Polar IFS
			{
				float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
				if (r > 1e-21f)
				{
					float theta = acos(z.z / r);
					float phi = atan2(z.y, z.x);
					float sr = mut->warpAmplitude;
					r *= sr;
					theta *= mut->warpFrequency;
					z.x = r * native_sin(theta) * native_cos(phi);
					z.y = r * native_sin(theta) * native_sin(phi);
					z.z = r * native_cos(theta);
					aux.DE = aux.DE * fabs(sr) + 1.0f;
				}
			}
			else if (mut->warpType == 11) // Shear IFS
			{
				z.x += mut->warpAmplitude * z.y;
				z.y += mut->warpFrequency * z.z;
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
					case 12: // SphereInversion3D
					{
						float cx = mut->mathP1, cy = mut->mathP2, cz = mut->mathP3;
						float r = (mut->mathP4 != 0.0f) ? mut->mathP4 : 1.0f;
						float dx = z.x - cx, dy = z.y - cy, dz = z.z - cz;
						float d2 = dx*dx + dy*dy + dz*dz;
						if (d2 > 1e-21f)
						{
							float factor = r * r / d2;
							mathZ.x = cx + dx * factor;
							mathZ.y = cy + dy * factor;
							mathZ.z = cz + dz * factor;
							aux.DE *= factor;
						}
						break;
					}
					case 13: // Loxodromic
					{
						float s = (mut->mathP1 != 0.0f) ? mut->mathP1 : 1.0f;
						float theta = mut->mathP2 * M_PI_F / 180.0f;
						float axPhi = mut->mathP3 * M_PI_F / 180.0f;
						float axPsi = mut->mathP4 * M_PI_F / 180.0f;
						float axX = cos(axPhi) * cos(axPsi);
						float axY = cos(axPhi) * sin(axPsi);
						float axZ = sin(axPhi);
						float ct = cos(theta), st = sin(theta);
						float dot = z.x*axX + z.y*axY + z.z*axZ;
						float crx = axY*z.z - axZ*z.y;
						float cry = axZ*z.x - axX*z.z;
						float crz = axX*z.y - axY*z.x;
						mathZ.x = (z.x * ct + crx * st + axX * dot * (1.0f - ct)) * s;
						mathZ.y = (z.y * ct + cry * st + axY * dot * (1.0f - ct)) * s;
						mathZ.z = (z.z * ct + crz * st + axZ * dot * (1.0f - ct)) * s;
						aux.DE *= fabs(s);
						break;
					}
					case 14: // Parabolic
					{
						float a = mut->mathP1, b = mut->mathP2, c = mut->mathP3;
						float denom = 1.0f + c * z.z;
						if (fabs(denom) > 1e-21f)
						{
							mathZ.x = (z.x + a) / denom;
							mathZ.y = (z.y + b) / denom;
							mathZ.z = z.z / denom;
							aux.DE /= fabs(denom);
						}
						break;
					}
					case 15: // SchottkyDual
					{
						float c1x = mut->mathP1, c1y = mut->mathP2, c1z = mut->mathP3;
						float r1 = (mut->mathP4 != 0.0f) ? mut->mathP4 : 1.0f;
						float c2x = mut->mathP5, c2y = mut->mathP6, c2z = mut->mathP7;
						float r2 = (mut->mathP8 != 0.0f) ? mut->mathP8 : 1.0f;
						float dx1 = z.x - c1x, dy1 = z.y - c1y, dz1 = z.z - c1z;
						float d1sq = dx1*dx1 + dy1*dy1 + dz1*dz1;
						if (d1sq < r1 * r1 && d1sq > 1e-21f)
						{
							float f = r1 * r1 / d1sq;
							mathZ.x = c1x + dx1 * f;
							mathZ.y = c1y + dy1 * f;
							mathZ.z = c1z + dz1 * f;
							aux.DE *= f;
							break;
						}
						float dx2 = z.x - c2x, dy2 = z.y - c2y, dz2 = z.z - c2z;
						float d2sq = dx2*dx2 + dy2*dy2 + dz2*dz2;
						if (d2sq < r2 * r2 && d2sq > 1e-21f)
						{
							float f = r2 * r2 / d2sq;
							mathZ.x = c2x + dx2 * f;
							mathZ.y = c2y + dy2 * f;
							mathZ.z = c2z + dz2 * f;
							aux.DE *= f;
						}
						break;
					}
					case 16: // FibonacciWord
					{
						int n = i % 64;
						int a_fib = 1, b_fib = 0, temp_fib;
						for (int fi = 0; fi < n; fi++)
						{ temp_fib = a_fib; a_fib = a_fib + b_fib; b_fib = temp_fib; }
						bool useT1 = (a_fib % 2 == 0);
						if (useT1)
						{
							float angle = mut->mathP1 * M_PI_F / 180.0f;
							float sc = (mut->mathP2 != 0.0f) ? mut->mathP2 : 1.0f;
							float ca = cos(angle), sa = sin(angle);
							mathZ.x = (z.x * ca - z.y * sa) * sc;
							mathZ.y = (z.x * sa + z.y * ca) * sc;
							mathZ.z = z.z * sc;
							aux.DE *= fabs(sc);
						}
						else
						{
							float lim = (mut->mathP3 != 0.0f) ? mut->mathP3 : 1.0f;
							float val = (mut->mathP4 != 0.0f) ? mut->mathP4 : 2.0f;
							if (z.x > lim) mathZ.x = val - z.x;
							else if (z.x < -lim) mathZ.x = -val - z.x;
							if (z.y > lim) mathZ.y = val - z.y;
							else if (z.y < -lim) mathZ.y = -val - z.y;
							if (z.z > lim) mathZ.z = val - z.z;
							else if (z.z < -lim) mathZ.z = -val - z.z;
						}
						break;
					}
					case 17: // MaskitBend
					{
						float muRe = mut->mathP1, muIm = mut->mathP2;
						float bendAngle = mut->mathP3 * M_PI_F / 180.0f;
						float r2 = z.x*z.x + z.y*z.y + z.z*z.z;
						if (r2 > 1e-21f)
						{
							float invX = z.x / r2, invY = -z.y / r2, invZ = -z.z / r2;
							mathZ.x = muRe + invX;
							mathZ.y = muIm + invY;
							mathZ.z = invZ;
							if (fabs(bendAngle) > 1e-12f)
							{
								float cb = cos(bendAngle), sb = sin(bendAngle);
								float ty = mathZ.y * cb - mathZ.z * sb;
								float tz = mathZ.y * sb + mathZ.z * cb;
								mathZ.y = ty; mathZ.z = tz;
							}
							aux.DE = aux.DE / r2 + 1.0f;
						}
						break;
					}
					case 18: // EllipsoidInversion
					{
						float axX = (mut->mathP1 != 0.0f) ? mut->mathP1 : 1.0f;
						float axY = (mut->mathP2 != 0.0f) ? mut->mathP2 : 1.0f;
						float axZ = (mut->mathP3 != 0.0f) ? mut->mathP3 : 1.0f;
						float r = (mut->mathP4 != 0.0f) ? mut->mathP4 : 1.0f;
						float sx = z.x * axX, sy = z.y * axY, sz = z.z * axZ;
						float d2 = sx*sx + sy*sy + sz*sz;
						if (d2 > 1e-21f)
						{
							float factor = r * r / d2;
							mathZ.x = sx * factor / axX;
							mathZ.y = sy * factor / axY;
							mathZ.z = sz * factor / axZ;
							aux.DE *= factor;
						}
						break;
					}
					case 19: // TorusInversion
					{
						float R = (mut->mathP1 != 0.0f) ? mut->mathP1 : 2.0f;
						float r = (mut->mathP2 != 0.0f) ? mut->mathP2 : 1.0f;
						float rxy = native_sqrt(z.x*z.x + z.y*z.y);
						if (rxy > 1e-21f)
						{
							float dRing = rxy - R;
							float dTorus = native_sqrt(dRing*dRing + z.z*z.z);
							if (dTorus > 1e-21f)
							{
								float factor = r * r / (dTorus * dTorus);
								float scale = (R + dRing * factor) / rxy;
								mathZ.x = z.x * scale;
								mathZ.y = z.y * scale;
								mathZ.z = z.z * factor;
								aux.DE *= factor;
							}
						}
						break;
					}
					case 20: // QuatJuliaKleinian
					{
						float qr = mut->mathP4, qi = z.x, qj = z.y, qk = z.z;
						float ni = 2.0f*qr*qi;
						float nj = 2.0f*qr*qj;
						float nk = 2.0f*qr*qk;
						mathZ.x = ni + mut->mathP1;
						mathZ.y = nj + mut->mathP2;
						mathZ.z = nk + mut->mathP3;
						aux.DE = 2.0f * aux.r * aux.DE + 1.0f;
						break;
					}
					case 21: // PoincareBall
					{
						float r2 = z.x*z.x + z.y*z.y + z.z*z.z;
						float curvature = (mut->mathP1 != 0.0f) ? mut->mathP1 : 1.0f;
						if (r2 < 1.0f - 1e-12f)
						{
							float metricFactor = 2.0f / (1.0f - r2);
							float sr = native_sqrt(r2);
							float hypR = curvature * native_log((1.0f + sr) / (1.0f - sr));
							float scale = tanh(hypR * mut->mathP2) / (sr + 1e-21f);
							mathZ.x = z.x * scale;
							mathZ.y = z.y * scale;
							mathZ.z = z.z * scale;
							aux.DE *= metricFactor * fabs(scale);
						}
						else
						{
							float rr = native_sqrt(r2);
							float scale = 0.999f / rr;
							mathZ.x = z.x * scale;
							mathZ.y = z.y * scale;
							mathZ.z = z.z * scale;
						}
						break;
					}
					case 22: // LorentzBoost
					{
						float vx = mut->mathP1, vy = mut->mathP2, vz = mut->mathP3;
						float v = mut->mathP4;
						float vLen = native_sqrt(vx*vx + vy*vy + vz*vz);
						if (vLen > 1e-21f && fabs(v) < 1.0f - 1e-12f)
						{
							vx /= vLen; vy /= vLen; vz /= vLen;
							float gamma = 1.0f / native_sqrt(1.0f - v*v);
							float w = native_sqrt(1.0f + z.x*z.x + z.y*z.y + z.z*z.z);
							float zDotV = z.x*vx + z.y*vy + z.z*vz;
							float parNew = gamma * (zDotV - v * w);
							float wNew = gamma * (w - v * zDotV);
							mathZ.x = z.x + (parNew - zDotV) * vx;
							mathZ.y = z.y + (parNew - zDotV) * vy;
							mathZ.z = z.z + (parNew - zDotV) * vz;
							if (wNew > 1e-21f)
							{
								float projScale = native_sqrt(wNew*wNew - 1.0f) /
									(native_sqrt(mathZ.x*mathZ.x + mathZ.y*mathZ.y + mathZ.z*mathZ.z) + 1e-21f);
								if (projScale > 0.0f && projScale < 100.0f)
								{
									mathZ.x *= projScale;
									mathZ.y *= projScale;
									mathZ.z *= projScale;
								}
							}
							aux.DE *= gamma;
						}
						break;
					}
					case 23: // ConformeFlow
					{
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						float harmonic = (r > 1e-21f) ? mut->mathP1 / r : 0.0f;
						float radial = mut->mathP2 * r;
						float sinusoidal = mut->mathP3 * native_sin(r * mut->mathP4);
						float u = harmonic + radial + sinusoidal;
						float confFactor = exp(2.0f * u);
						if (confFactor > 100.0f) confFactor = 100.0f;
						if (confFactor < 0.01f) confFactor = 0.01f;
						mathZ.x = z.x * confFactor;
						mathZ.y = z.y * confFactor;
						mathZ.z = z.z * confFactor;
						aux.DE *= confFactor;
						break;
					}
					case 24: // FractionalPower
					{
						float p = (mut->mathP1 != 0.0f) ? mut->mathP1 : 2.718281828f;
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						if (r > 1e-21f)
						{
							float theta = acos(z.z / r);
							float phi = atan2(z.y, z.x);
							float rp = native_powr(r, p);
							mathZ.x = rp * native_sin(theta * p) * native_cos(phi * p);
							mathZ.y = rp * native_sin(theta * p) * native_sin(phi * p);
							mathZ.z = rp * native_cos(theta * p);
							aux.DE = aux.DE * p * native_powr(r, p - 1.0f) + 1.0f;
						}
						break;
					}
					case 25: // AnisotropePower
					{
						float px = (mut->mathP1 != 0.0f) ? mut->mathP1 : 2.0f;
						float py = (mut->mathP2 != 0.0f) ? mut->mathP2 : 2.0f;
						float pz = (mut->mathP3 != 0.0f) ? mut->mathP3 : 2.0f;
						float ax = fabs(z.x); float ay = fabs(z.y); float az = fabs(z.z);
						mathZ.x = sign(z.x) * native_powr(max(ax, 1e-21f), px);
						mathZ.y = sign(z.y) * native_powr(max(ay, 1e-21f), py);
						mathZ.z = sign(z.z) * native_powr(max(az, 1e-21f), pz);
						float maxP = max(px, max(py, pz));
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						aux.DE = aux.DE * maxP * native_powr(max(r, 1e-21f), maxP - 1.0f) + 1.0f;
						break;
					}
					case 26: // HyperbolicTrigPower
					{
						float p = (mut->mathP1 != 0.0f) ? mut->mathP1 : 2.0f;
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						if (r > 1e-21f)
						{
							float theta = acos(z.z / r);
							float phi = atan2(z.y, z.x);
							float rp = native_powr(r, p);
							mathZ.x = rp * sinh(theta * p) * native_cos(phi * p);
							mathZ.y = rp * sinh(theta * p) * native_sin(phi * p);
							mathZ.z = rp * cosh(theta * p);
							aux.DE = aux.DE * p * native_powr(r, p - 1.0f) * cosh(theta) + 1.0f;
						}
						break;
					}
					case 27: // LogarithmicRadius
					{
						float p = (mut->mathP1 != 0.0f) ? mut->mathP1 : 2.0f;
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						if (r > 1e-21f)
						{
							float rp = native_powr(r, p);
							float lr = native_log(1.0f + rp);
							float sc = lr / r;
							mathZ.x = z.x * sc;
							mathZ.y = z.y * sc;
							mathZ.z = z.z * sc;
							aux.DE *= p * native_powr(r, p - 1.0f) / (1.0f + rp);
						}
						break;
					}
					case 28: // PolarSwap
					{
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						if (r > 1e-21f)
						{
							float theta = acos(z.z / r);
							float phi = atan2(z.y, z.x);
							float tmp = theta; theta = phi; phi = tmp;
							mathZ.x = r * native_sin(theta) * native_cos(phi);
							mathZ.y = r * native_sin(theta) * native_sin(phi);
							mathZ.z = r * native_cos(theta);
						}
						break;
					}
					case 29: // RadialModulation
					{
						float amp = (mut->mathP1 != 0.0f) ? mut->mathP1 : 0.1f;
						float freq = (mut->mathP2 != 0.0f) ? mut->mathP2 : 10.0f;
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						if (r > 1e-21f)
						{
							float theta = acos(z.z / r);
							float mod = 1.0f + amp * native_sin(freq * theta);
							mathZ.x = z.x * mod;
							mathZ.y = z.y * mod;
							mathZ.z = z.z * mod;
							aux.DE *= fabs(mod);
						}
						break;
					}
					case 30: // DualQuaternion
					{
						float q1w = (mut->mathP1 != 0.0f) ? mut->mathP1 : 1.0f;
						float q1i = mut->mathP2; float q1j = mut->mathP3; float q1k = mut->mathP4;
						float q2w = (mut->mathP5 != 0.0f) ? mut->mathP5 : 1.0f;
						float q2i = mut->mathP6; float q2j = mut->mathP7; float q2k = mut->mathP8;
						float tw = -q1i*z.x - q1j*z.y - q1k*z.z;
						float tx = q1w*z.x + q1j*z.z - q1k*z.y;
						float ty = q1w*z.y + q1k*z.x - q1i*z.z;
						float tz = q1w*z.z + q1i*z.y - q1j*z.x;
						mathZ.x = tw*q2i + tx*q2w + ty*q2k - tz*q2j;
						mathZ.y = tw*q2j + ty*q2w + tz*q2i - tx*q2k;
						mathZ.z = tw*q2k + tz*q2w + tx*q2j - ty*q2i;
						break;
					}
					case 31: // OctonionPower
					{
						float p = (mut->mathP1 != 0.0f) ? mut->mathP1 : 2.0f;
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z
							+ mut->mathP2*mut->mathP2 + mut->mathP3*mut->mathP3);
						if (r > 1e-21f)
						{
							float theta = acos(z.z / r);
							float phi = atan2(z.y, z.x);
							float rp = native_powr(r, p);
							mathZ.x = rp * native_sin(theta * p) * native_cos(phi * p);
							mathZ.y = rp * native_sin(theta * p) * native_sin(phi * p);
							mathZ.z = rp * native_cos(theta * p);
							aux.DE = aux.DE * p * native_powr(r, p - 1.0f) + 1.0f;
						}
						break;
					}
					case 32: // QuaternionMobius
					{
						float a = (mut->mathP1 != 0.0f) ? mut->mathP1 : 1.0f;
						float b = mut->mathP2;
						float c = mut->mathP3;
						float d = (mut->mathP4 != 0.0f) ? mut->mathP4 : 1.0f;
						float nx = a * z.x + b;
						float ny = a * z.y;
						float nz = a * z.z;
						float dr2 = c * z.x + d;
						float di = c * z.y;
						float dk = c * z.z;
						float denom = dr2*dr2 + di*di + dk*dk;
						if (denom > 1e-21f)
						{
							mathZ.x = (nx*dr2 + ny*di + nz*dk) / denom;
							mathZ.y = (ny*dr2 - nx*di) / denom;
							mathZ.z = (nz*dr2 - nx*dk) / denom;
							float adbc = fabs(a*d - b*c);
							aux.DE *= adbc / denom;
						}
						break;
					}
					case 33: // SplitQuaternion
					{
						float p = (mut->mathP1 != 0.0f) ? mut->mathP1 : 2.0f;
						float r = native_sqrt(fabs(z.x*z.x + z.y*z.y - z.z*z.z));
						if (r > 1e-21f)
						{
							float rxy = native_sqrt(z.x*z.x + z.y*z.y);
							float theta = atanh(z.z / max(rxy, 1e-21f));
							float phi = atan2(z.y, z.x);
							float rp = native_powr(max(r, 1e-21f), p);
							mathZ.x = rp * cosh(theta * p) * native_cos(phi * p);
							mathZ.y = rp * cosh(theta * p) * native_sin(phi * p);
							mathZ.z = rp * sinh(theta * p);
							aux.DE = aux.DE * p * native_powr(max(r, 1e-21f), p - 1.0f) + 1.0f;
						}
						break;
					}
					case 34: // FordCircles
					{
						int N = (mut->mathP1 > 0.5f) ? (int)mut->mathP1 : 3;
						float r2 = z.x*z.x + z.y*z.y + z.z*z.z;
						if (r2 > 1e-21f)
						{
							for (int n = 1; n <= N; n++)
							{
								float nn = (float)(n * n);
								float factor = 1.0f / (nn * r2);
								mathZ.x = z.x + z.x * factor;
								mathZ.y = z.y + z.y * factor;
								mathZ.z = z.z + z.z * factor;
								aux.DE *= (1.0f + factor);
							}
						}
						break;
					}
					case 35: // ApollonianNet
					{
						float rad = (mut->mathP1 > 0.0f) ? mut->mathP1 : 1.0f;
						float4 centers[4];
						centers[0] = (float4)(1.0f, 1.0f, 1.0f, 0.0f);
						centers[1] = (float4)(1.0f, -1.0f, -1.0f, 0.0f);
						centers[2] = (float4)(-1.0f, 1.0f, -1.0f, 0.0f);
						centers[3] = (float4)(-1.0f, -1.0f, 1.0f, 0.0f);
						float minDist = 1e20f; int closest = 0;
						for (int s = 0; s < 4; s++)
						{
							float4 diff = z - centers[s];
							float d = dot(diff, diff);
							if (d < minDist) { minDist = d; closest = s; }
						}
						if (minDist > 1e-21f)
						{
							float r2 = rad * rad;
							float4 diff = z - centers[closest];
							float factor = r2 / minDist;
							mathZ = centers[closest] + diff * factor;
							aux.DE *= factor;
						}
						break;
					}
					case 36: // ConformalWedge
					{
						float alpha = (mut->mathP1 != 0.0f) ? mut->mathP1 : 2.0f;
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						if (r > 1e-21f)
						{
							float theta = acos(z.z / r);
							float phi = atan2(z.y, z.x);
							float rp = native_powr(r, alpha);
							mathZ.x = rp * native_sin(theta * alpha) * native_cos(phi * alpha);
							mathZ.y = rp * native_sin(theta * alpha) * native_sin(phi * alpha);
							mathZ.z = rp * native_cos(theta * alpha);
							aux.DE = aux.DE * alpha * native_powr(r, alpha - 1.0f) + 1.0f;
						}
						break;
					}
					case 37: // CircleInvChain
					{
						float r1 = (mut->mathP1 > 0.0f) ? mut->mathP1 : 1.0f;
						float r2c = (mut->mathP2 > 0.0f) ? mut->mathP2 : 0.8f;
						float r3 = (mut->mathP3 > 0.0f) ? mut->mathP3 : 0.6f;
						float spacing = (mut->mathP4 != 0.0f) ? mut->mathP4 : 2.0f;
						float radii[3]; radii[0] = r1; radii[1] = r2c; radii[2] = r3;
						float offsets[3]; offsets[0] = -spacing; offsets[1] = 0.0f; offsets[2] = spacing;
						for (int c = 0; c < 3; c++)
						{
							float dx = z.x - offsets[c];
							float dist2 = dx*dx + z.y*z.y + z.z*z.z;
							if (dist2 > 1e-21f && dist2 < radii[c] * radii[c])
							{
								float factor = (radii[c] * radii[c]) / dist2;
								mathZ.x = offsets[c] + dx * factor;
								mathZ.y = z.y * factor;
								mathZ.z = z.z * factor;
								aux.DE *= factor;
							}
						}
						break;
					}
					case 38: // HyperbolicSine
					{
						float amp = (mut->mathP1 != 0.0f) ? mut->mathP1 : 1.0f;
						mathZ.x = amp * sinh(z.x);
						mathZ.y = amp * sinh(z.y);
						mathZ.z = amp * sinh(z.z);
						aux.DE = aux.DE * amp * cosh(native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z)) + 1.0f;
						break;
					}
					case 39: // BesselApprox
					{
						float freq = (mut->mathP1 != 0.0f) ? mut->mathP1 : 1.0f;
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						if (r > 1e-21f)
						{
							float j0 = native_cos(freq * r) / native_sqrt(max(r, 1e-21f));
							mathZ.x = z.x * j0;
							mathZ.y = z.y * j0;
							mathZ.z = z.z * j0;
							aux.DE = aux.DE * fabs(j0) + 1.0f;
						}
						break;
					}
					case 40: // LambertW
					{
						float amp = (mut->mathP1 != 0.0f) ? mut->mathP1 : 1.0f;
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						float er = native_exp(min(r, 20.0f));
						mathZ.x = amp * z.x * er;
						mathZ.y = amp * z.y * er;
						mathZ.z = amp * z.z * er;
						aux.DE = aux.DE * amp * er * (1.0f + r) + 1.0f;
						break;
					}
					case 41: // ErrorFunction
					{
						float scale = (mut->mathP1 != 0.0f) ? mut->mathP1 : 1.0f;
						float sqrtPi = 1.7724538509f;
						mathZ.x = scale * tanh(sqrtPi * z.x);
						mathZ.y = scale * tanh(sqrtPi * z.y);
						mathZ.z = scale * tanh(sqrtPi * z.z);
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						float erfDeriv = 2.0f / sqrtPi * native_exp(-r*r);
						aux.DE = aux.DE * scale * erfDeriv + 1.0f;
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

		// v7.5 — Julia pre-fold injection (GPU)
		if (mutationActive && consts->sequence.mutationParams[sequence].juliaInjection != 0)
		{
			__global const sClFormulaMutationParams *jm = &consts->sequence.mutationParams[sequence];
			float4 juliaC = aux.const_c * jm->juliaCMul;
			// C-transform
			if (jm->juliaCTransform == 1) { // spherical
				float cLen = length(juliaC);
				if (cLen > 1e-21f) juliaC = juliaC * (jm->juliaCRadius / cLen);
			} else if (jm->juliaCTransform == 2) { // Möbius
				float denom = length(juliaC) + jm->juliaCMobiusD;
				if (fabs(denom) > 1e-21f)
					juliaC = (juliaC * jm->juliaCMobiusA + (float4)(jm->juliaCMobiusB, jm->juliaCMobiusB, jm->juliaCMobiusB, 0.0f)) * (1.0f / denom);
			} else if (jm->juliaCTransform == 3) { // rotate
				float3 jcR = Matrix33MulFloat3(jm->juliaCRotMatrix, juliaC.xyz);
				juliaC.xyz = jcR;
			} else if (jm->juliaCTransform == 4) { // power
				float r = length(juliaC);
				if (r > 1e-21f) {
					float th = atan2(juliaC.y, juliaC.x);
					float ph = acos(clamp(juliaC.z / r, -1.0f, 1.0f));
					float rp = native_powr(r, jm->juliaCPower);
					juliaC.x = rp * native_sin(ph * jm->juliaCPower) * native_cos(th * jm->juliaCPower);
					juliaC.y = rp * native_sin(ph * jm->juliaCPower) * native_sin(th * jm->juliaCPower);
					juliaC.z = rp * native_cos(ph * jm->juliaCPower);
				}
			} else if (jm->juliaCTransform == 5) { // quaternion
				float cLen = length(juliaC);
				float qw = native_cos(cLen * 0.5f);
				float qs = (cLen > 1e-21f) ? native_sin(cLen * 0.5f) / cLen : 0.0f;
				float qi = juliaC.x * qs, qj = juliaC.y * qs, qk = juliaC.z * qs;
				float zw = 0.0f;
				float nx = qw*z.x + qi*zw + qj*z.z - qk*z.y;
				float ny = qw*z.y - qi*z.z + qj*zw + qk*z.x;
				float nz = qw*z.z + qi*z.y - qj*z.x + qk*zw;
				juliaC = (float4)(nx, ny, nz, 0.0f);
			}
			// Dynamic modulation
			if (jm->juliaDynamic == 1) juliaC *= (1.0f + 0.1f * length(z));
			else if (jm->juliaDynamic == 2) juliaC *= native_sin((float)i * jm->juliaPulseFreq) * jm->juliaPulseAmp;
			else if (jm->juliaDynamic == 3) { if (length(z) > consts->sequence.bailout[sequence] * 0.5f) juliaC *= 2.0f; }
			else if (jm->juliaDynamic == 4) juliaC = juliaC * (1.0f - jm->juliaAbsorb) + z * jm->juliaAbsorb;
			else if (jm->juliaDynamic == 5) juliaC = juliaC + (z - lastZ) * 0.1f;
			// Multi-C modes
			if (jm->juliaMulti == 1) { if (z.x < 0.0f) juliaC = (float4)(jm->juliaBipolarCRx, jm->juliaBipolarCRy, jm->juliaBipolarCRz, 0.0f); }
			else if (jm->juliaMulti == 2) {
				if (i % 4 == 1) juliaC = (float4)(juliaC.y, juliaC.z, juliaC.w, juliaC.x);
				else if (i % 4 == 2) juliaC = (float4)(juliaC.z, juliaC.w, juliaC.x, juliaC.y);
				else if (i % 4 == 3) juliaC = (float4)(juliaC.w, juliaC.x, juliaC.y, juliaC.z);
			}
			else if (jm->juliaMulti == 3) {
				juliaC += (float4)(jm->juliaFourierC2x, jm->juliaFourierC2y, jm->juliaFourierC2z, 0.0f) * native_sin((float)i)
						+ (float4)(jm->juliaFourierC3x, jm->juliaFourierC3y, jm->juliaFourierC3z, 0.0f) * native_cos((float)i * 0.5f);
			}
			else if (jm->juliaMulti == 4) {
				float n = native_sin(z.x * jm->juliaNoiseFreq) * native_cos(z.y * jm->juliaNoiseFreq * 0.7f) * native_sin(z.z * jm->juliaNoiseFreq * 1.3f);
				juliaC += (float4)(n, n, n, 0.0f) * jm->juliaNoiseAmp;
			}
			else if (jm->juliaMulti == 5) juliaC = juliaC + z * 0.01f;
			// Injection point
			if (jm->juliaInjection == 1 || jm->juliaInjection == 4) z += juliaC; // pre-fold or dual
			else if (jm->juliaInjection == 5) { // pre-scale damping
				float r = length(z);
				float bail = consts->sequence.bailout[sequence];
				float factor = (bail > 1e-21f) ? r / bail : 1.0f;
				z += juliaC * factor;
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

		// v7.5 — Julia mid/post injection (GPU)
		if (mutationActive && (consts->sequence.mutationParams[sequence].juliaInjection == 2
			|| consts->sequence.mutationParams[sequence].juliaInjection == 3
			|| consts->sequence.mutationParams[sequence].juliaInjection == 4))
		{
			__global const sClFormulaMutationParams *jm = &consts->sequence.mutationParams[sequence];
			float4 juliaC = aux.const_c * jm->juliaCMul;
			if (jm->juliaCTransform == 1) {
				float cLen = length(juliaC);
				if (cLen > 1e-21f) juliaC = juliaC * (jm->juliaCRadius / cLen);
			} else if (jm->juliaCTransform == 3) {
				float3 jcR = Matrix33MulFloat3(jm->juliaCRotMatrix, juliaC.xyz);
				juliaC.xyz = jcR;
			}
			if (jm->juliaDynamic == 2) juliaC *= native_sin((float)i * jm->juliaPulseFreq) * jm->juliaPulseAmp;
			else if (jm->juliaDynamic == 4) juliaC = juliaC * (1.0f - jm->juliaAbsorb) + z * jm->juliaAbsorb;
			z += juliaC;
		}

		// -------------- Formula Mutation post-processing (GPU) ---------------
		if (mutationActive)
		{
			__global const sClFormulaMutationParams *mut = &consts->sequence.mutationParams[sequence];

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
					case 8:
					{
						float k = (mut->foldLimit > 0.0f) ? mut->foldLimit : 1.0f;
						z.x -= tanh(k * z.x);
						z.y -= tanh(k * z.y);
						z.z -= tanh(k * z.z);
						break;
					}
					case 9:
					{
						z.x = z.x * z.x * z.x - 3.0f * z.x;
						z.y = z.y * z.y * z.y - 3.0f * z.y;
						z.z = z.z * z.z * z.z - 3.0f * z.z;
						break;
					}
					case 10:
					{
						float rad = (mut->foldValue > 0.0f) ? mut->foldValue : 1.0f;
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						if (r > 1e-21f) { float s = rad / r; z.x *= s; z.y *= s; z.z *= s; }
						break;
					}
					case 11:
					{
						float r = native_sqrt(z.x*z.x + z.y*z.y);
						float angle = r * mut->foldLimit;
						float ca = native_cos(angle); float sa = native_sin(angle);
						float nx = z.x * ca - z.y * sa;
						float ny = z.x * sa + z.y * ca;
						z.x = nx; z.y = ny;
						break;
					}
					case 12:
					{
						float a = mut->foldValue;
						float b = (mut->foldLimit > 0.0f) ? mut->foldLimit : 1.0f;
						z.x += a * native_sin(b * z.x);
						z.y += a * native_sin(b * z.y);
						z.z += a * native_sin(b * z.z);
						break;
					}
					case 13:
					{
						z.x *= native_exp(-z.x * z.x);
						z.y *= native_exp(-z.y * z.y);
						z.z *= native_exp(-z.z * z.z);
						break;
					}
					case 14:
					{
						float rx = fabs(z.x); float ry = fabs(z.y); float rz = fabs(z.z);
						z.x *= native_log(1.0f + rx);
						z.y *= native_log(1.0f + ry);
						z.z *= native_log(1.0f + rz);
						break;
					}
					case 15:
					{
						float p = (mut->foldValue > 0.0f) ? mut->foldValue : 2.0f;
						float ax = fabs(z.x); float ay = fabs(z.y); float az = fabs(z.z);
						z.x = sign(z.x) * native_powr(max(ax, 1e-21f), p);
						z.y = sign(z.y) * native_powr(max(ay, 1e-21f), p);
						z.z = sign(z.z) * native_powr(max(az, 1e-21f), p);
						break;
					}
					case 16: // smooth abs
					{
						float k = (mut->foldLimit > 0.0f) ? mut->foldLimit : 5.0f;
						z.x = z.x * tanh(k * z.x);
						z.y = z.y * tanh(k * z.y);
						z.z = z.z * tanh(k * z.z);
						break;
					}
					case 17: // modulo wrap
					{
						float period = (mut->foldValue > 0.0f) ? mut->foldValue : 2.0f;
						z.x = fmod(z.x + period * 0.5f, period) - period * 0.5f;
						z.y = fmod(z.y + period * 0.5f, period) - period * 0.5f;
						z.z = fmod(z.z + period * 0.5f, period) - period * 0.5f;
						break;
					}
					case 18: // nested abs
					{
						float c = (mut->foldLimit > 0.0f) ? mut->foldLimit : 1.0f;
						z.x = fabs(fabs(z.x) - c);
						z.y = fabs(fabs(z.y) - c);
						z.z = fabs(fabs(z.z) - c);
						break;
					}
					case 19: // sawtooth
					{
						z.x = 2.0f * (z.x * 0.5f - floor(z.x * 0.5f + 0.5f));
						z.y = 2.0f * (z.y * 0.5f - floor(z.y * 0.5f + 0.5f));
						z.z = 2.0f * (z.z * 0.5f - floor(z.z * 0.5f + 0.5f));
						break;
					}
					case 20: // Bipolar
					{
						float c1 = mut->foldLimit;
						float c2 = -mut->foldLimit;
						z.x = fabs(z.x - c1) - fabs(z.x - c2);
						z.y = fabs(z.y - c1) - fabs(z.y - c2);
						z.z = fabs(z.z - c1) - fabs(z.z - c2);
						break;
					}
					case 21: // RadialBox
					{
						float r = native_sqrt(z.x*z.x + z.y*z.y);
						float theta = atan2(z.y, z.x);
						float foldR = mut->foldLimit;
						if (r > foldR) r = 2.0f * foldR - r;
						if (r < -foldR) r = -2.0f * foldR - r;
						z.x = r * native_cos(theta);
						z.y = r * native_sin(theta);
						aux.DE *= r / max(native_sqrt(z.x*z.x + z.y*z.y), 1e-21f);
						break;
					}
					case 22: // Shear
					{
						float lim = mut->foldLimit;
						if (z.x > lim) z.x = 2.0f * lim - z.x;
						else if (z.x < -lim) z.x = -2.0f * lim - z.x;
						if (z.y > lim) z.y = 2.0f * lim - z.y;
						else if (z.y < -lim) z.y = -2.0f * lim - z.y;
						z.x += mut->foldValue * z.y;
						z.y += mut->foldValue * z.z;
						break;
					}
					case 23: // 3DCross
					{
						float lim = mut->foldLimit;
						int phase = i % 3;
						if (phase == 0) {
							if (z.x > lim) z.x = 2.0f*lim - z.x;
							if (z.x < -lim) z.x = -2.0f*lim - z.x;
							if (z.y > lim) z.y = 2.0f*lim - z.y;
							if (z.y < -lim) z.y = -2.0f*lim - z.y;
						} else if (phase == 1) {
							if (z.y > lim) z.y = 2.0f*lim - z.y;
							if (z.y < -lim) z.y = -2.0f*lim - z.y;
							if (z.z > lim) z.z = 2.0f*lim - z.z;
							if (z.z < -lim) z.z = -2.0f*lim - z.z;
						} else {
							if (z.z > lim) z.z = 2.0f*lim - z.z;
							if (z.z < -lim) z.z = -2.0f*lim - z.z;
							if (z.x > lim) z.x = 2.0f*lim - z.x;
							if (z.x < -lim) z.x = -2.0f*lim - z.x;
						}
						break;
					}
					case 24: // Conformal
					{
						float r2 = z.x*z.x + z.y*z.y + z.z*z.z;
						if (r2 > 1e-21f)
						{
							z.x += z.x / r2;
							z.y += z.y / r2;
							z.z += z.z / r2;
							aux.DE *= fabs(1.0f - 1.0f / r2);
						}
						break;
					}
					case 25: // Rotation
					{
						float lim = mut->foldLimit;
						if (z.x > lim) z.x = 2.0f*lim - z.x;
						if (z.x < -lim) z.x = -2.0f*lim - z.x;
						if (z.y > lim) z.y = 2.0f*lim - z.y;
						if (z.y < -lim) z.y = -2.0f*lim - z.y;
						if (z.z > lim) z.z = 2.0f*lim - z.z;
						if (z.z < -lim) z.z = -2.0f*lim - z.z;
						float t = z.x; z.x = -z.y; z.y = t;
						break;
					}
					case 26: // ScalePulse
					{
						float lim = mut->foldLimit;
						if (z.x > lim) z.x = 2.0f*lim - z.x;
						if (z.x < -lim) z.x = -2.0f*lim - z.x;
						if (z.y > lim) z.y = 2.0f*lim - z.y;
						if (z.y < -lim) z.y = -2.0f*lim - z.y;
						if (z.z > lim) z.z = 2.0f*lim - z.z;
						if (z.z < -lim) z.z = -2.0f*lim - z.z;
						float pulse = 1.0f + 0.2f * native_sin((float)i * mut->foldValue);
						z *= pulse;
						aux.DE *= fabs(pulse);
						break;
					}
					case 27: // TriangleWave
					{
						z.x = 2.0f * fabs(z.x * 0.5f - floor(z.x * 0.5f + 0.5f));
						z.y = 2.0f * fabs(z.y * 0.5f - floor(z.y * 0.5f + 0.5f));
						z.z = 2.0f * fabs(z.z * 0.5f - floor(z.z * 0.5f + 0.5f));
						break;
					}
				}
			}

			// Post-rotation
			if (mut->postRotX != 0.0f || mut->postRotY != 0.0f || mut->postRotZ != 0.0f)
			{
				z.xyz = Matrix33MulFloat3(mut->postRotMatrix, z.xyz);
			}
			if (mut->postScale != 1.0f) { z *= mut->postScale; aux.DE *= mut->postScale; }
			z.x += mut->postOffsetX; z.y += mut->postOffsetY; z.z += mut->postOffsetZ;
			if (mut->zMix < 1.0f) { float m = mut->zMix; z = z * m + preMutZ * (1.0f - m); }
			if (mut->deScale != 1.0f) aux.DE *= mut->deScale;

			// DE tweak (Familie 10)
			if (mut->deTweak == 1) aux.DE = native_log(1.0f + fabs(aux.DE));
			else if (mut->deTweak == 2) aux.DE = native_exp(aux.DE) - 1.0f;
			else if (mut->deTweak == 3) { float noise = mut->deTweakP1 * native_sin(z.x*13.7f + z.y*7.3f + z.z*11.1f); aux.DE += noise; }
			else if (mut->deTweak == 4) { aux.DE *= (1.0f + mut->deTweakP1 * native_sin(mut->deTweakP2 * aux.dist)); }
			else if (mut->deTweak == 5) aux.DE *= 0.9f;
			else if (mut->deTweak == 6) aux.DE *= 1.1f;

			// Orbit trap (Familie 10)
			if (mut->orbitTrap == 1) {
				float dx = z.x - mut->trapCenterX; float dy = z.y - mut->trapCenterY; float dz = z.z - mut->trapCenterZ;
				float dist2 = native_sqrt(dx*dx + dy*dy + dz*dz);
				float tv = fabs(dist2 - mut->trapRadius);
				if (tv < aux.color) aux.color = tv;
			} else if (mut->orbitTrap == 2) {
				float tv = min(min(fabs(z.x), fabs(z.y)), fabs(z.z));
				if (tv < aux.color) aux.color = tv;
			} else if (mut->orbitTrap == 3) {
				float tv = native_sqrt(z.y*z.y + z.z*z.z);
				if (tv < aux.color) aux.color = tv;
			} else if (mut->orbitTrap == 4) {
				float dxy = native_sqrt(z.x*z.x + z.y*z.y) - mut->trapRadius;
				float tv = fabs(native_sqrt(dxy*dxy + z.z*z.z) - mut->deTweakP1);
				if (tv < aux.color) aux.color = tv;
			} else if (mut->orbitTrap == 5) {
				float tv = fabs(atan2(z.y, z.x));
				if (tv < aux.color) aux.color = tv;
			}

			// Curvature coloring
			if (mut->curvatureColoring != 0) {
				float prevDE2 = (aux.DE != 0.0f) ? aux.DE : 1.0f;
				float curv = aux.DE / prevDE2;
				if (curv < aux.color) aux.color = curv;
			}
		}

#ifdef ITERATION_WEIGHT
		// Apply weight blending in hybrid mode
		if (consts->sequence.isHybrid && effectiveWeight < 1.0f)
		{
			__global const sClFormulaWeightParams *wp = &consts->sequence.weightParams[sequence];
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

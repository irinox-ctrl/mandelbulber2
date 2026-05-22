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
		__constant sClFormulaMutationParams *jm0 = &consts->sequence.mutationParams[0];
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
					else if (wp->deModType == 2) effectiveWeight = wp->deBase * native_exp(factor);
					else if (wp->deModType == 3) effectiveWeight = (fabs(actualDE) > 1e-15f) ? wp->deBase * (wp->deThreshold / actualDE) : 1.0f;
					else effectiveWeight = wp->deBase + (1.0f - wp->deBase) / (1.0f + native_exp(-factor));
					effectiveWeight = clamp(effectiveWeight, 0.0f, 1.0f);
				}
				else if (weightMode == 3) // ZLength
				{
					float zLen = length(z);
					float delta = zLen - wp->zlengthThreshold;
					float factor = delta * wp->zlengthSens;
					if (wp->zlengthModType == 0) effectiveWeight = wp->zlengthBase + factor;
					else if (wp->zlengthModType == 1) effectiveWeight = wp->zlengthBase + factor * factor * (factor > 0.0f ? 1.0f : -1.0f);
					else if (wp->zlengthModType == 2) effectiveWeight = wp->zlengthBase * native_exp(factor);
					else if (wp->zlengthModType == 3) effectiveWeight = (fabs(zLen) > 1e-15f) ? wp->zlengthBase * (wp->zlengthThreshold / zLen) : 1.0f;
					else effectiveWeight = wp->zlengthBase + (1.0f - wp->zlengthBase) / (1.0f + native_exp(-factor));
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
					else if (wp->orbitTrapModType == 2) effectiveWeight = wp->orbitTrapBase * native_exp(factor);
					else if (wp->orbitTrapModType == 3) effectiveWeight = (fabs(orbitDist) > 1e-15f) ? wp->orbitTrapBase * (wp->orbitTrapThreshold / orbitDist) : 1.0f;
					else effectiveWeight = wp->orbitTrapBase + (1.0f - wp->orbitTrapBase) / (1.0f + native_exp(-factor));
					effectiveWeight = clamp(effectiveWeight, 0.0f, 1.0f);
				}
				else if (weightMode == 6) // Curve
				{
					float normalized = (wp->curveBase > 1e-15f) ? actualDE / wp->curveBase : actualDE;
					float powered = pow(fabs(normalized * wp->curveSensitivity), wp->curvePower);
					if (wp->curveModType == 0) effectiveWeight = wp->curveBase + powered * (normalized >= 0.0f ? 1.0f : -1.0f);
					else if (wp->curveModType == 1) { float s = powered * powered * (3.0f - 2.0f * powered); effectiveWeight = wp->curveBase + s; }
					else if (wp->curveModType == 2) effectiveWeight = wp->curveBase * native_exp(powered - 1.0f);
					else if (wp->curveModType == 3) effectiveWeight = (powered > 1e-15f) ? wp->curveBase / powered : 1.0f;
					else effectiveWeight = wp->curveBase + (1.0f - wp->curveBase) / (1.0f + native_exp(-(powered - 0.5f) * 6.0f));
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
					else if (wp->deRatioModType == 2) effectiveWeight = 1.0f - native_exp(-fabs(ratio));
					else if (wp->deRatioModType == 3) effectiveWeight = (fabs(ratio) > 1e-15f) ? clamp(1.0f / ratio, 0.0f, 1.0f) : 1.0f;
					else effectiveWeight = 1.0f / (1.0f + native_exp(-(ratio - 0.5f) * 6.0f));
				}
				else if (weightMode == 9) // Adaptive
				{
					float str = wp->adaptiveStrength;
					if (deFunc == logarithmicDEFunction)
					{
						float norm = (actualDE > 1e-15f) ? native_log(1.0f + actualDE) : 0.0f;
						effectiveWeight = 1.0f / (1.0f + native_exp(-(norm - 0.5f) * 4.0f * str));
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
						effectiveWeight = 1.0f / (1.0f + native_exp(-(actualDE - 0.5f) * 6.0f * str));
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
			__constant sClFormulaMutationParams *mut = &consts->sequence.mutationParams[sequence];

			// Pre-transform (per-section iteration range)
			if (i >= mut->preIterStart && i < mut->preIterStop)
			{
				if (mut->preAbsX) z.x = fabs(z.x);
				if (mut->preAbsY) z.y = fabs(z.y);
				if (mut->preAbsZ) z.z = fabs(z.z);
				z.x += mut->preOffsetX; z.y += mut->preOffsetY; z.z += mut->preOffsetZ;
				if (mut->preRotX != 0.0f || mut->preRotY != 0.0f || mut->preRotZ != 0.0f)
				{
					z.xyz = Matrix33MulFloat3(mut->preRotMatrix, z.xyz);
				}
				if (mut->preScale != 1.0f) { z *= mut->preScale; aux.DE *= mut->preScale; }
			}

			// v7.6 — Inversion (per-section iteration range)
			if (i >= mut->invIterStart && i < mut->invIterStop && mut->inversionType != 0)
			{
				float3 zz = z.xyz;
				if (mut->invPreRotX != 0.0f || mut->invPreRotY != 0.0f || mut->invPreRotZ != 0.0f)
					zz = Matrix33MulFloat3(mut->invPreRotMatrix, zz);
				zz.x -= mut->invCenterX; zz.y -= mut->invCenterY; zz.z -= mut->invCenterZ;
				float mde = 1.0f;
				float a = mut->invParamA, b = mut->invParamB, c = mut->invParamC;
				float R = mut->invRadius, sc = mut->invScale;
				float rr;
				switch (mut->inversionType)
				{
					case 1: // Ellipsoid Inversion
					{
						rr = (zz.x/a)*(zz.x/a) + (zz.y/b)*(zz.y/b) + (zz.z/c)*(zz.z/c);
						if (rr < 1e-21f) rr = 1e-21f;
						mde = 1.0f/rr;
						zz.x *= mde * a * a; zz.y *= mde * b * b; zz.z *= mde * c * c;
						mde = 1.0f/rr;
						break;
					}
					case 2: // Cylinder Inversion
					{
						rr = zz.x * zz.x + zz.y * zz.y;
						if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr;
						zz.x *= mde; zz.y *= mde;
						break;
					}
					case 3: // Torus Inversion
					{
						float rxy = native_sqrt(zz.x * zz.x + zz.y * zz.y);
						rr = (rxy - a) * (rxy - a) + zz.z * zz.z;
						if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr;
						zz *= mde;
						break;
					}
					case 4: // Hyperboloid Inversion
					{
						rr = (zz.x/a)*(zz.x/a) + (zz.y/b)*(zz.y/b) - (zz.z/c)*(zz.z/c);
						if (fabs(rr) < 1e-21f) rr = 1e-21f;
						mde = 1.0f / fabs(rr);
						zz *= mde;
						break;
					}
					case 5: // Paraboloid Inversion
					{
						rr = zz.x * zz.x + zz.y * zz.y - a * zz.z;
						if (fabs(rr) < 1e-21f) rr = 1e-21f;
						mde = 1.0f / fabs(rr);
						zz *= mde;
						break;
					}
					case 6: // Cone Inversion
					{
						float tanA = native_tan(mut->invAngle * M_PI_F / 180.0f);
						rr = zz.x * zz.x + zz.y * zz.y - tanA * tanA * zz.z * zz.z;
						if (fabs(rr) < 1e-21f) rr = 1e-21f;
						mde = 1.0f / fabs(rr);
						zz *= mde;
						break;
					}
					case 7: // Saddle Inversion
					{
						rr = (zz.x/a)*(zz.x/a) - (zz.y/b)*(zz.y/b) - zz.z;
						if (fabs(rr) < 1e-21f) rr = 1e-21f;
						mde = 1.0f / fabs(rr);
						zz *= mde;
						break;
					}
					case 8: // Spiral Inversion
					{
						float r2d = native_sqrt(zz.x * zz.x + zz.y * zz.y);
						float theta = atan2(zz.y, zz.x);
						float k = mut->invFrequency;
						rr = r2d * native_exp(-k * theta);
						if (fabs(rr) < 1e-21f) rr = 1e-21f;
						mde = 1.0f / rr;
						zz *= mde;
						break;
					}
					case 9: // Lemniscate Inversion
					{
						float x2 = zz.x * zz.x, y2 = zz.y * zz.y;
						rr = (x2 + y2) * (x2 + y2) - a * a * (x2 - y2);
						if (fabs(rr) < 1e-21f) rr = 1e-21f;
						mde = 1.0f / fabs(rr);
						zz *= mde;
						break;
					}
					case 10: // Cassini Inversion
					{
						float d1sq = (zz.x - a) * (zz.x - a) + zz.y * zz.y;
						float d2sq = (zz.x + a) * (zz.x + a) + zz.y * zz.y;
						rr = d1sq * d2sq + zz.z * zz.z;
						if (fabs(rr) < 1e-21f) rr = 1e-21f;
						mde = 1.0f / rr;
						zz *= mde;
						break;
					}
					case 11: // Dipole Inversion
					{
						float3 c1 = (float3){mut->invCenterX, mut->invCenterY, mut->invCenterZ};
						float3 c2 = (float3){mut->invCenter2X, mut->invCenter2Y, mut->invCenter2Z};
						float3 zr = zz + (float3){mut->invCenterX, mut->invCenterY, mut->invCenterZ};
						float d1 = dot(zr - c1, zr - c1); if (d1 < 1e-21f) d1 = 1e-21f;
						float d2 = dot(zr - c2, zr - c2); if (d2 < 1e-21f) d2 = 1e-21f;
						mde = R * R / d1 - mut->invRadius2 * mut->invRadius2 / d2;
						zz *= mde;
						mde = fabs(mde);
						break;
					}
					case 12: // Multipoint Inversion
					{
						float3 c1 = (float3){0.0f, 0.0f, 0.0f};
						float3 c2 = (float3){mut->invCenter2X, mut->invCenter2Y, mut->invCenter2Z};
						float w1 = mut->invWeight, w2 = 1.0f - w1;
						float d1 = dot(zz - c1, zz - c1); if (d1 < 1e-21f) d1 = 1e-21f;
						float d2 = dot(zz - c2, zz - c2); if (d2 < 1e-21f) d2 = 1e-21f;
						mde = w1 * R * R / d1 + w2 * mut->invRadius2 * mut->invRadius2 / d2;
						zz *= mde;
						mde = fabs(mde);
						break;
					}
					case 13: // Chain Inversion (2-step)
					{
						float3 c1 = (float3){0.0f, 0.0f, 0.0f};
						float3 c2 = (float3){mut->invCenter2X, mut->invCenter2Y, mut->invCenter2Z};
						float d1 = dot(zz - c1, zz - c1); if (d1 < 1e-21f) d1 = 1e-21f;
						float m1 = R * R / d1;
						float3 z1 = c1 + (zz - c1) * m1;
						float d2 = dot(z1 - c2, z1 - c2); if (d2 < 1e-21f) d2 = 1e-21f;
						float m2 = mut->invRadius2 * mut->invRadius2 / d2;
						zz = c2 + (z1 - c2) * m2;
						mde = m1 * m2;
						break;
					}
					case 14: // Nest Inversion (K-step)
					{
						mde = 1.0f;
						float3 cc = (float3){0.0f, 0.0f, 0.0f};
						float rk = R;
						for (int k = 0; k < mut->invNSteps && k < 8; k++)
						{
							float3 delta = zz - cc;
							float dk = dot(delta, delta); if (dk < 1e-21f) dk = 1e-21f;
							float mk = rk * rk / dk;
							zz = cc + delta * mk;
							mde *= mk;
							cc.x += mut->invCenter2X / (float)(k + 1);
							cc.y += mut->invCenter2Y / (float)(k + 1);
							cc.z += mut->invCenter2Z / (float)(k + 1);
							rk *= 0.8f;
						}
						mde = fabs(mde);
						break;
					}
					case 15: // Apollonian Inversion
					{
						float3 centers[4];
						centers[0] = (float3){a, 0.0f, 0.0f};
						centers[1] = (float3){-a, 0.0f, 0.0f};
						centers[2] = (float3){0.0f, a, 0.0f};
						centers[3] = (float3){0.0f, 0.0f, a};
						float minD = 1e20f; int nearest = 0;
						for (int k = 0; k < 4; k++)
						{
							float d = dot(zz - centers[k], zz - centers[k]);
							if (d < minD) { minD = d; nearest = k; }
						}
						if (minD < 1e-21f) minD = 1e-21f;
						mde = R * R / minD;
						zz = centers[nearest] + (zz - centers[nearest]) * mde;
						break;
					}
					case 16: // Ford Circle Inversion
					{
						float q = max(1.0f, a);
						float cr = 1.0f / (2.0f * q * q);
						float3 fc = (float3){1.0f / q, cr, 0.0f};
						float d = dot(zz - fc, zz - fc); if (d < 1e-21f) d = 1e-21f;
						mde = cr * cr / d;
						zz = fc + (zz - fc) * mde;
						break;
					}
					case 17: // Schottky Group Inversion
					{
						float3 c1 = (float3){a, 0.0f, 0.0f};
						float3 c2 = (float3){-a, 0.0f, 0.0f};
						float d1 = dot(zz - c1, zz - c1); if (d1 < 1e-21f) d1 = 1e-21f;
						float d2 = dot(zz - c2, zz - c2); if (d2 < 1e-21f) d2 = 1e-21f;
						if (d1 < d2) { mde = R * R / d1; zz = c1 + (zz - c1) * mde; }
						else { mde = R * R / d2; zz = c2 + (zz - c2) * mde; }
						break;
					}
					case 18: // Fuchsian Inversion
					{
						float cz_d = c * zz.x + 1.0f;
						float denom = cz_d * cz_d + c * c * zz.y * zz.y;
						if (denom < 1e-21f) denom = 1e-21f;
						mde = 1.0f / denom;
						float nx = (a * zz.x + b) * cz_d + a * c * zz.y * zz.y;
						float ny = zz.y * (a - b * c);
						zz.x = nx * mde; zz.y = ny * mde;
						break;
					}
					case 19: // Modular Inversion (SL(2,Z))
					{
						rr = zz.x * zz.x + zz.y * zz.y;
						if (rr < 1e-21f) rr = 1e-21f;
						if (rr < 1.0f) { mde = 1.0f / rr; zz.x *= mde; zz.y *= -mde; }
						else { mde = 1.0f; }
						if (zz.x > 0.5f) zz.x -= 1.0f;
						if (zz.x < -0.5f) zz.x += 1.0f;
						break;
					}
					case 20: // Hecke Inversion
					{
						float lambda = 2.0f * native_cos(M_PI_F / a);
						rr = zz.x * zz.x + zz.y * zz.y;
						if (rr < 1e-21f) rr = 1e-21f;
						if (rr < 1.0f) { mde = 1.0f / rr; zz.x *= mde; zz.y *= -mde; }
						else { mde = 1.0f; }
						if (zz.x > lambda * 0.5f) zz.x -= lambda;
						if (zz.x < -lambda * 0.5f) zz.x += lambda;
						break;
					}
					case 21: // Inversion with Pre-Rotation (already handled by invPreRotMatrix)
					{
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						break;
					}
					case 22: // Inversion with Pre-Shear
					{
						zz.x += mut->invAmplitude * zz.y;
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						zz.x -= mut->invAmplitude * zz.y;
						break;
					}
					case 23: // Inversion with Pre-Fold
					{
						float lim = a;
						if (zz.x > lim) zz.x = 2.0f * lim - zz.x;
						if (zz.x < -lim) zz.x = -2.0f * lim - zz.x;
						if (zz.y > lim) zz.y = 2.0f * lim - zz.y;
						if (zz.y < -lim) zz.y = -2.0f * lim - zz.y;
						if (zz.z > lim) zz.z = 2.0f * lim - zz.z;
						if (zz.z < -lim) zz.z = -2.0f * lim - zz.z;
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						break;
					}
					case 24: // Inversion with Pre-Abs
					{
						zz.x = fabs(zz.x); zz.y = fabs(zz.y); zz.z = fabs(zz.z);
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						break;
					}
					case 25: // Inversion with Post-Scale Pulse
					{
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						float pulse = sc * (1.0f + 0.1f * native_sin((float)i * mut->invFrequency));
						zz *= pulse; mde *= fabs(pulse);
						break;
					}
					case 26: // Inversion with Post-Offset Wave
					{
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						float freq = mut->invFrequency;
						zz.x += mut->invAmplitude * native_sin(freq * zz.x);
						zz.y += mut->invAmplitude * native_sin(freq * zz.y);
						zz.z += mut->invAmplitude * native_sin(freq * zz.z);
						break;
					}
					case 27: // Inversion with Iterative Angle
					{
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						float ga = (float)i * 2.399963f; // golden angle
						float cosA = native_cos(ga), sinA = native_sin(ga);
						float tx = zz.x * cosA - zz.y * sinA;
						zz.y = zz.x * sinA + zz.y * cosA;
						zz.x = tx;
						break;
					}
					case 28: // DE-Aware Inversion
					{
						if (aux.DE < mut->invThreshold)
						{
							rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
							mde = R * R / rr; zz *= mde;
						}
						break;
					}
					case 29: // Color-Trigger Inversion
					{
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						aux.color += mut->invColorFactor * fabs(mde - 1.0f);
						break;
					}
					case 30: // Orbit-Trap Inversion
					{
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						float trap = length(zz);
						if (trap < aux.color) aux.color = trap;
						break;
					}
					case 31: // Quaternion Inversion
					{
						float4 q = (float4){zz.x, zz.y, zz.z, z.w};
						float qn = dot(q, q); if (qn < 1e-21f) qn = 1e-21f;
						mde = 1.0f / qn;
						q = (float4){q.x, -q.y, -q.z, -q.w} * mde;
						zz = q.xyz; z.w = q.w;
						break;
					}
					case 32: // Dual Complex Inversion
					{
						float n1 = zz.x * zz.x + zz.y * zz.y; if (n1 < 1e-21f) n1 = 1e-21f;
						float n2 = zz.z * zz.z + z.w * z.w; if (n2 < 1e-21f) n2 = 1e-21f;
						zz.x /= n1; zz.y /= -n1;
						zz.z /= n2; z.w /= -n2;
						mde = max(1.0f / n1, 1.0f / n2);
						break;
					}
					case 33: // Split Complex Inversion
					{
						float denom = zz.x * zz.x - zz.y * zz.y;
						if (fabs(denom) < 1e-21f) denom = 1e-21f;
						mde = 1.0f / fabs(denom);
						zz.x = zz.x / denom; zz.y = -zz.y / denom;
						break;
					}
					case 34: // Dual Number Inversion
					{
						if (fabs(zz.x) < 1e-21f) zz.x = 1e-21f;
						mde = 1.0f / (zz.x * zz.x);
						float ox = 1.0f / zz.x;
						float oy = -zz.y / (zz.x * zz.x);
						zz.x = ox; zz.y = oy;
						break;
					}
					case 35: // Octonion Inversion
					{
						float on = dot(zz, zz) + z.w * z.w;
						if (on < 1e-21f) on = 1e-21f;
						mde = 1.0f / on;
						zz *= mde; z.w *= -mde;
						zz.y = -zz.y; zz.z = -zz.z;
						break;
					}
					case 36: // Sedenion Inversion
					{
						float sn = dot(zz, zz) + z.w * z.w;
						if (sn < 1e-21f) sn = 1e-21f;
						mde = 1.0f / sn;
						zz = (float3){zz.x, -zz.y, -zz.z} * mde;
						z.w *= -mde;
						break;
					}
					case 37: // Clifford Algebra Inversion
					{
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = 1.0f / rr;
						zz *= mde;
						break;
					}
					case 38: // Grassmann Algebra Inversion
					{
						float hodge = zz.x * (zz.y * zz.z);
						if (fabs(hodge) < 1e-21f) hodge = 1e-21f;
						mde = 1.0f / fabs(hodge);
						zz.x = (zz.y * zz.z) * mde;
						zz.y = (zz.x * zz.z) * mde;
						zz.z = (zz.x * zz.y) * mde;
						break;
					}
					case 39: // Non-Commutative Inversion
					{
						float detA = zz.x * zz.y - zz.z * zz.z;
						if (fabs(detA) < 1e-21f) detA = 1e-21f;
						mde = 1.0f / fabs(detA);
						float tx = zz.y * mde;
						zz.y = zz.x * mde;
						zz.x = tx;
						zz.z = -zz.z * mde;
						break;
					}
					case 40: // Probabilistic Inversion
					{
						float hash = fabs(native_sin(zz.x * 12.9898f + zz.y * 78.233f + zz.z * 45.164f) * 43758.5453f);
						hash = hash - floor(hash);
						float p = mut->invWeight;
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						if (hash < p) { mde = R * R / rr; zz *= mde; }
						else { mde = 1.0f; }
						mde = (1.0f - p) + p * mde;
						break;
					}
					case 41: // Inversion × Spherical Fold
					{
						rr = dot(zz, zz);
						float minR2 = mut->invMinR * mut->invMinR;
						float maxR2 = mut->invMaxR * mut->invMaxR;
						if (rr < minR2) mde = maxR2 / minR2;
						else if (rr < maxR2) mde = maxR2 / rr;
						else mde = 1.0f;
						zz *= mde;
						break;
					}
					case 42: // Inversion × Box Fold
					{
						float lim = a;
						if (zz.x > lim) zz.x = 2.0f * lim - zz.x;
						if (zz.x < -lim) zz.x = -2.0f * lim - zz.x;
						if (zz.y > lim) zz.y = 2.0f * lim - zz.y;
						if (zz.y < -lim) zz.y = -2.0f * lim - zz.y;
						if (zz.z > lim) zz.z = 2.0f * lim - zz.z;
						if (zz.z < -lim) zz.z = -2.0f * lim - zz.z;
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						lim = b;
						if (zz.x > lim) zz.x = 2.0f * lim - zz.x;
						if (zz.x < -lim) zz.x = -2.0f * lim - zz.x;
						if (zz.y > lim) zz.y = 2.0f * lim - zz.y;
						if (zz.y < -lim) zz.y = -2.0f * lim - zz.y;
						if (zz.z > lim) zz.z = 2.0f * lim - zz.z;
						if (zz.z < -lim) zz.z = -2.0f * lim - zz.z;
						break;
					}
					case 43: // Inversion × Möbius
					{
						float cz_d2 = c * zz.x + 1.0f;
						float denom2 = cz_d2 * cz_d2 + c * c * zz.y * zz.y;
						if (denom2 < 1e-21f) denom2 = 1e-21f;
						float mobMde = (a * 1.0f - b * c) / denom2;
						zz.x = (a * zz.x + b) / (c * zz.x + 1.0f + 1e-21f);
						zz.y = zz.y * mobMde;
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						mde *= fabs(mobMde);
						break;
					}
					case 44: // Inversion × Kleinian
					{
						float3 dynC = zz * mut->invAmplitude;
						rr = dot(zz - dynC, zz - dynC); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr;
						zz = dynC + (zz - dynC) * mde;
						break;
					}
					case 45: // Inversion × Julia
					{
						float3 jc = (float3){mut->invCenter2X, mut->invCenter2Y, mut->invCenter2Z};
						rr = dot(zz - jc, zz - jc); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr;
						zz = jc + (zz - jc) * mde;
						break;
					}
					case 46: // Inversion × IFS
					{
						float3 ifs_c = (float3){a, b, c};
						float d = dot(zz - ifs_c, zz - ifs_c); if (d < 1e-21f) d = 1e-21f;
						mde = R * R / d;
						zz = ifs_c + (zz - ifs_c) * mde;
						zz.x = fabs(zz.x); zz.y = fabs(zz.y);
						break;
					}
					case 47: // Inversion × Loxodromic
					{
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						float theta = mut->invAngle * M_PI_F / 180.0f;
						float cosT = native_cos(theta), sinT = native_sin(theta);
						float tx2 = zz.x * cosT - zz.y * sinT;
						zz.y = zz.x * sinT + zz.y * cosT;
						zz.x = tx2;
						zz *= sc;
						mde *= fabs(sc);
						break;
					}
					case 48: // Inversion × Parabolic
					{
						zz.x += mut->invAmplitude;
						zz.y += mut->invAmplitude * zz.x * zz.x;
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						break;
					}
					case 49: // Inversion × Elliptic
					{
						float theta = mut->invAngle * M_PI_F / 180.0f;
						float cosT = native_cos(theta), sinT = native_sin(theta);
						float tx3 = zz.x * cosT - zz.y * sinT;
						zz.y = zz.x * sinT + zz.y * cosT;
						zz.x = tx3;
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						break;
					}
					case 50: // Inversion × Hyperbolic Translation (Poincaré ball)
					{
						float3 aa = (float3){mut->invCenter2X, mut->invCenter2Y, mut->invCenter2Z};
						float an = dot(aa, aa);
						float za = dot(zz, aa);
						float zn = dot(zz, zz);
						float denom3 = 1.0f + 2.0f * za + an * zn;
						if (fabs(denom3) < 1e-21f) denom3 = 1e-21f;
						zz = (zz * (1.0f + 2.0f * za + an) + aa * (1.0f + zn)) / denom3;
						mde = (1.0f - an) / (denom3 * denom3);
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						float invMde = R * R / rr;
						zz *= invMde;
						mde *= invMde;
						mde = fabs(mde);
						break;
					}
				}
				zz.x += mut->invCenterX; zz.y += mut->invCenterY; zz.z += mut->invCenterZ;
				if (mut->invPreRotX != 0.0f || mut->invPreRotY != 0.0f || mut->invPreRotZ != 0.0f)
				{
					matrix33 invRot;
					invRot.m1 = (float3){mut->invPreRotMatrix.m1.x, mut->invPreRotMatrix.m2.x, mut->invPreRotMatrix.m3.x};
					invRot.m2 = (float3){mut->invPreRotMatrix.m1.y, mut->invPreRotMatrix.m2.y, mut->invPreRotMatrix.m3.y};
					invRot.m3 = (float3){mut->invPreRotMatrix.m1.z, mut->invPreRotMatrix.m2.z, mut->invPreRotMatrix.m3.z};
					zz = Matrix33MulFloat3(invRot, zz);
				}
				z.xyz = zz;
				aux.DE *= fabs(mde);
			}

			// Fold injection (pre or both)
			if (i >= mut->foldIterStart && i < mut->foldIterStop
				&& mut->foldType != 0 && (mut->foldPosition == 0 || mut->foldPosition == 2))
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

			// Warp distortion (per-section iteration range)
			if (i >= mut->warpIterStart && i < mut->warpIterStop) {
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
			} // end warp iteration range

			// Math injection (GPU, per-section iteration range)
			if (i >= mut->mathIterStart && i < mut->mathIterStop
				&& mut->mathType != 0)
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
						float axX = native_cos(axPhi) * native_cos(axPsi);
						float axY = native_cos(axPhi) * native_sin(axPsi);
						float axZ = native_sin(axPhi);
						float ct = native_cos(theta), st = native_sin(theta);
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
							float ca = native_cos(angle), sa = native_sin(angle);
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
								float cb = native_cos(bendAngle), sb = native_sin(bendAngle);
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
						float confFactor = native_exp(2.0f * u);
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

		// v7.5 — Julia pre-fold injection (GPU, per-section iteration range)
		if (mutationActive
			&& i >= consts->sequence.mutationParams[sequence].juliaIterStart
			&& i < consts->sequence.mutationParams[sequence].juliaIterStop
			&& consts->sequence.mutationParams[sequence].juliaInjection != 0)
		{
			__constant sClFormulaMutationParams *jm = &consts->sequence.mutationParams[sequence];
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

		// v7.5 — Julia mid/post injection (GPU, per-section iteration range)
		if (mutationActive
			&& i >= consts->sequence.mutationParams[sequence].juliaIterStart
			&& i < consts->sequence.mutationParams[sequence].juliaIterStop
			&& (consts->sequence.mutationParams[sequence].juliaInjection == 2
			|| consts->sequence.mutationParams[sequence].juliaInjection == 3
			|| consts->sequence.mutationParams[sequence].juliaInjection == 4))
		{
			__constant sClFormulaMutationParams *jm = &consts->sequence.mutationParams[sequence];
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
			__constant sClFormulaMutationParams *mut = &consts->sequence.mutationParams[sequence];

			// Fold injection (post or both, per-section iteration range)
			if (i >= mut->foldIterStart && i < mut->foldIterStop
				&& mut->foldType != 0 && (mut->foldPosition == 1 || mut->foldPosition == 2))
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

			// Post-transform (per-section iteration range)
			if (i >= mut->postIterStart && i < mut->postIterStop)
			{
				if (mut->postRotX != 0.0f || mut->postRotY != 0.0f || mut->postRotZ != 0.0f)
				{
					z.xyz = Matrix33MulFloat3(mut->postRotMatrix, z.xyz);
				}
				if (mut->postScale != 1.0f) { z *= mut->postScale; aux.DE *= mut->postScale; }
				z.x += mut->postOffsetX; z.y += mut->postOffsetY; z.z += mut->postOffsetZ;
			}
			if (mut->zMix < 1.0f) { float m = mut->zMix; z = z * m + preMutZ * (1.0f - m); }

			// v7.6 — Clip system (per-section iteration range)
			if (i >= mut->clipIterStart && i < mut->clipIterStop && mut->clipType != 0)
			{
				float3 cz = z.xyz;
				if (mut->clipPreRotX != 0.0f || mut->clipPreRotY != 0.0f || mut->clipPreRotZ != 0.0f)
					cz = Matrix33MulFloat3(mut->clipPreRotMatrix, cz);
				cz.x -= mut->clipCenterX; cz.y -= mut->clipCenterY; cz.z -= mut->clipCenterZ;
				float clipDist = 1e10f;
				float sx = mut->clipSizeX, sy = mut->clipSizeY, sz = mut->clipSizeZ;
				float cr = mut->clipRadius, cR = mut->clipMajorRadius;
				float ca = mut->clipParamA, cb = mut->clipParamB, cc = mut->clipParamC;
				switch (mut->clipType)
				{
					case 1: // Ellipsoid Clip
					{
						clipDist = native_sqrt((cz.x/sx)*(cz.x/sx) + (cz.y/sy)*(cz.y/sy) + (cz.z/sz)*(cz.z/sz)) - 1.0f;
						break;
					}
					case 2: // Torus Clip
					{
						float rxy = native_sqrt(cz.x * cz.x + cz.y * cz.y) - cR;
						clipDist = native_sqrt(rxy * rxy + cz.z * cz.z) - cr;
						break;
					}
					case 3: // Cylinder (infinite) Clip
					{
						clipDist = native_sqrt(cz.x * cz.x + cz.y * cz.y) - cr;
						break;
					}
					case 4: // Cone Clip
					{
						float tanAlpha = native_tan(mut->clipAngle * M_PI_F / 180.0f);
						clipDist = native_sqrt(cz.x * cz.x + cz.y * cz.y) - tanAlpha * fabs(cz.z);
						break;
					}
					case 5: // Hyperboloid Clip
					{
						clipDist = (cz.x/sx)*(cz.x/sx) + (cz.y/sy)*(cz.y/sy) - (cz.z/sz)*(cz.z/sz) - 1.0f;
						break;
					}
					case 6: // Paraboloid Clip
					{
						clipDist = cz.x * cz.x + cz.y * cz.y - ca * cz.z;
						break;
					}
					case 7: // Saddle Clip
					{
						clipDist = (cz.x/sx)*(cz.x/sx) - (cz.y/sy)*(cz.y/sy) - cz.z;
						break;
					}
					case 8: // Spiral Clip
					{
						float r2d = native_sqrt(cz.x * cz.x + cz.y * cz.y);
						float theta = atan2(cz.y, cz.x);
						clipDist = r2d - ca * native_exp(cb * theta);
						break;
					}
					case 9: // Wave Clip
					{
						float freq = mut->clipFrequency;
						float amp = mut->clipAmplitude;
						clipDist = cz.z - amp * native_sin(freq * cz.x) * native_sin(freq * cz.y);
						break;
					}
					case 10: // Noise Clip
					{
						float n = native_sin(cz.x * 12.9898f + cz.y * 78.233f) * 43758.5453f;
						n = (n - floor(n)) * 2.0f - 1.0f;
						float n2 = native_sin(cz.y * 19.8672f + cz.z * 53.471f) * 28947.3125f;
						n2 = (n2 - floor(n2)) * 2.0f - 1.0f;
						clipDist = cz.z - mut->clipAmplitude * (n + n2) * 0.5f;
						break;
					}
					case 11: // Union (OR) Clip
					{
						float d1 = native_sqrt((cz.x/sx)*(cz.x/sx) + (cz.y/sy)*(cz.y/sy) + (cz.z/sz)*(cz.z/sz)) - 1.0f;
						float d2 = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						clipDist = min(d1, d2);
						break;
					}
					case 12: // Difference (A - B) Clip
					{
						float dA = native_sqrt((cz.x/sx)*(cz.x/sx) + (cz.y/sy)*(cz.y/sy) + (cz.z/sz)*(cz.z/sz)) - 1.0f;
						float dB = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						clipDist = max(dA, -dB);
						break;
					}
					case 13: // XOR Clip
					{
						float dA2 = native_sqrt((cz.x/sx)*(cz.x/sx) + (cz.y/sy)*(cz.y/sy) + (cz.z/sz)*(cz.z/sz)) - 1.0f;
						float dB2 = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						clipDist = max(min(dA2, dB2), -max(dA2, dB2));
						break;
					}
					case 14: // Smooth Union Clip
					{
						float d1s = native_sqrt((cz.x/sx)*(cz.x/sx) + (cz.y/sy)*(cz.y/sy) + (cz.z/sz)*(cz.z/sz)) - 1.0f;
						float d2s = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						float k = mut->clipSmoothK;
						float h = clamp(0.5f + 0.5f * (d2s - d1s) / k, 0.0f, 1.0f);
						clipDist = mix(d2s, d1s, h) - k * h * (1.0f - h);
						break;
					}
					case 15: // Smooth Difference Clip
					{
						float dAs = native_sqrt((cz.x/sx)*(cz.x/sx) + (cz.y/sy)*(cz.y/sy) + (cz.z/sz)*(cz.z/sz)) - 1.0f;
						float dBs = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						float k2 = mut->clipSmoothK;
						float h2 = clamp(0.5f - 0.5f * (dAs + dBs) / k2, 0.0f, 1.0f);
						clipDist = mix(dAs, -dBs, h2) + k2 * h2 * (1.0f - h2);
						break;
					}
					case 16: // Chain Clip (3 stages)
					{
						float dc1 = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						float dc2 = max(fabs(cz.x) - sx, max(fabs(cz.y) - sy, fabs(cz.z) - sz));
						float dc3 = native_sqrt(cz.x*cz.x + cz.y*cz.y) - cr * 0.5f;
						clipDist = max(dc1, max(dc2, dc3));
						break;
					}
					case 17: // Array (Grid) Clip
					{
						float3 rp = cz;
						if (sx > 0.001f) rp.x = fmod(cz.x + sx * 0.5f, sx) - sx * 0.5f;
						if (sy > 0.001f) rp.y = fmod(cz.y + sy * 0.5f, sy) - sy * 0.5f;
						if (sz > 0.001f) rp.z = fmod(cz.z + sz * 0.5f, sz) - sz * 0.5f;
						clipDist = native_sqrt(rp.x*rp.x + rp.y*rp.y + rp.z*rp.z) - cr;
						break;
					}
					case 18: // Random Array Clip
					{
						float3 cell;
						cell.x = (sx > 0.001f) ? floor(cz.x / sx) : 0.0f;
						cell.y = (sy > 0.001f) ? floor(cz.y / sy) : 0.0f;
						cell.z = (sz > 0.001f) ? floor(cz.z / sz) : 0.0f;
						float h = fabs(native_sin(cell.x * 127.1f + cell.y * 311.7f + cell.z * 74.7f) * 43758.5453f);
						h = h - floor(h);
						float3 rp2 = cz;
						if (sx > 0.001f) rp2.x = fmod(cz.x + sx * 0.5f, sx) - sx * 0.5f;
						if (sy > 0.001f) rp2.y = fmod(cz.y + sy * 0.5f, sy) - sy * 0.5f;
						if (sz > 0.001f) rp2.z = fmod(cz.z + sz * 0.5f, sz) - sz * 0.5f;
						clipDist = native_sqrt(rp2.x*rp2.x + rp2.y*rp2.y + rp2.z*rp2.z) - cr * (0.5f + h);
						break;
					}
					case 19: // Hierarchical Clip
					{
						float coarse = max(fabs(cz.x) - sx * 2.0f, max(fabs(cz.y) - sy * 2.0f, fabs(cz.z) - sz * 2.0f));
						float fine = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						clipDist = (coarse < 0.0f) ? fine : coarse;
						break;
					}
					case 20: // Fractal Clip
					{
						float3 fz = cz;
						float fscale = 1.0f;
						for (int k = 0; k < 4; k++)
						{
							fz = fabs(fz) * 2.0f - (float3){ca, ca, ca};
							fscale *= 2.0f;
						}
						clipDist = (length(fz) - cr) / fscale;
						break;
					}
					case 21: // Clip with Pre-Rotation (handled by clipPreRotMatrix)
					{
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						break;
					}
					case 22: // Clip with Pre-Scale
					{
						float3 scaled = cz;
						scaled.x *= sx; scaled.y *= sy; scaled.z *= sz;
						clipDist = native_sqrt(scaled.x*scaled.x + scaled.y*scaled.y + scaled.z*scaled.z) - cr;
						break;
					}
					case 23: // Clip with Pre-Shear
					{
						float3 sheared = cz;
						sheared.x += mut->clipAmplitude * cz.y;
						clipDist = native_sqrt(sheared.x*sheared.x + sheared.y*sheared.y + sheared.z*sheared.z) - cr;
						break;
					}
					case 24: // Clip with Pre-Fold
					{
						float3 folded = cz;
						float lim = ca;
						if (folded.x > lim) folded.x = 2.0f * lim - folded.x;
						if (folded.x < -lim) folded.x = -2.0f * lim - folded.x;
						if (folded.y > lim) folded.y = 2.0f * lim - folded.y;
						if (folded.y < -lim) folded.y = -2.0f * lim - folded.y;
						if (folded.z > lim) folded.z = 2.0f * lim - folded.z;
						if (folded.z < -lim) folded.z = -2.0f * lim - folded.z;
						clipDist = native_sqrt(folded.x*folded.x + folded.y*folded.y + folded.z*folded.z) - cr;
						break;
					}
					case 25: // Clip with Pre-Abs
					{
						float3 absed = cz;
						absed.x = fabs(absed.x); absed.y = fabs(absed.y); absed.z = fabs(absed.z);
						clipDist = native_sqrt(absed.x*absed.x + absed.y*absed.y + absed.z*absed.z) - cr;
						break;
					}
					case 26: // Clip with Post-Offset
					{
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						float pulse = 1.0f + 0.1f * native_sin((float)i * mut->clipFrequency);
						clipDist *= pulse;
						break;
					}
					case 27: // Clip with Post-Scale
					{
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						float scaleFactor = ca * (1.0f + 0.1f * (float)i / 250.0f);
						clipDist *= scaleFactor;
						break;
					}
					case 28: // Clip with Color-Depth
					{
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						if (clipDist < 0.0f) aux.color += fabs(clipDist) * mut->clipAmplitude;
						break;
					}
					case 29: // Clip with Orbit-Trap
					{
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						float trap = length(cz);
						if (trap < aux.color) aux.color = trap;
						break;
					}
					case 30: // Clip with DE-Visualization
					{
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						aux.color = native_log(1.0f + fabs(aux.dist)) * mut->clipAmplitude;
						break;
					}
					case 31: // Star (n-point) Clip
					{
						float r2d = native_sqrt(cz.x * cz.x + cz.y * cz.y);
						float theta = atan2(cz.y, cz.x);
						int n = mut->clipNPoints;
						float starR = cr * (1.0f + mut->clipAmplitude * native_cos((float)n * theta));
						clipDist = r2d - starR;
						break;
					}
					case 32: // Heart Clip
					{
						float x2h = cz.x * cz.x + cz.y * cz.y;
						clipDist = (x2h - 1.0f) * (x2h - 1.0f) * (x2h - 1.0f) - cz.x * cz.x * cz.y * cz.y * cz.y;
						break;
					}
					case 33: // Superformula Clip
					{
						float r2d2 = native_sqrt(cz.x * cz.x + cz.y * cz.y);
						float theta2 = atan2(cz.y, cz.x);
						float m = (float)mut->clipNPoints;
						float n1 = ca, n2 = cb, n3 = cc;
						float t = m * theta2 / 4.0f;
						float r_sf = native_powr(
							native_powr(fabs(native_cos(t) / sx), n2) +
							native_powr(fabs(native_sin(t) / sy), n3), -1.0f / n1);
						clipDist = r2d2 - r_sf * cr;
						break;
					}
					case 34: // Gear Clip
					{
						float r2d3 = native_sqrt(cz.x * cz.x + cz.y * cz.y);
						float theta3 = atan2(cz.y, cz.x);
						int ng = mut->clipNPoints;
						float gearR = cr * (1.0f + 0.1f * tanh(native_sin((float)ng * theta3)));
						clipDist = r2d3 - gearR;
						break;
					}
					case 35: // Spiral Galaxy Clip
					{
						float r2d4 = native_sqrt(cz.x * cz.x + cz.y * cz.y);
						float theta4 = atan2(cz.y, cz.x);
						int ns = mut->clipNPoints;
						float spiralR = ca * native_exp(-cb * theta4) * (1.0f + cc * native_cos((float)ns * theta4));
						clipDist = r2d4 - spiralR;
						break;
					}
					case 36: // Voronoi Clip
					{
						float3 seeds[4];
						seeds[0] = (float3){ca, 0.0f, 0.0f};
						seeds[1] = (float3){-ca, cb, 0.0f};
						seeds[2] = (float3){0.0f, -ca, cc};
						seeds[3] = (float3){cb, cc, -ca};
						float minVD = 1e20f;
						for (int k = 0; k < 4; k++)
						{
							float vd = length(cz - seeds[k]);
							if (vd < minVD) minVD = vd;
						}
						clipDist = minVD - cr;
						break;
					}
					case 37: // Delaunay Clip
					{
						float3 edges[3];
						edges[0] = (float3){ca, 0.0f, 0.0f};
						edges[1] = (float3){-ca * 0.5f, ca * 0.866f, 0.0f};
						edges[2] = (float3){-ca * 0.5f, -ca * 0.866f, 0.0f};
						float minED = 1e20f;
						for (int k = 0; k < 3; k++)
						{
							float3 e = edges[(k + 1) % 3] - edges[k];
							float3 p = cz - edges[k];
							float t = clamp(dot(p, e) / dot(e, e), 0.0f, 1.0f);
							float ed = length(p - e * t);
							if (ed < minED) minED = ed;
						}
						clipDist = minED - cr;
						break;
					}
					case 38: // L-System Clip
					{
						float3 lz = cz;
						float lscale = 1.0f;
						for (int k = 0; k < 3; k++)
						{
							lz = fabs(lz);
							if (lz.x < lz.y) { float t = lz.x; lz.x = lz.y; lz.y = t; }
							if (lz.x < lz.z) { float t = lz.x; lz.x = lz.z; lz.z = t; }
							if (lz.y < lz.z) { float t = lz.y; lz.y = lz.z; lz.z = t; }
							lz = lz * ca - (float3){cb, cb, cb} * (ca - 1.0f);
							lscale *= ca;
						}
						clipDist = (length(lz) - cr) / lscale;
						break;
					}
					case 39: // Julia Set Clip (2D extruded)
					{
						float jx = cz.x, jy = cz.y;
						for (int k = 0; k < 8; k++)
						{
							float tx = jx * jx - jy * jy + ca;
							jy = 2.0f * jx * jy + cb;
							jx = tx;
							if (jx * jx + jy * jy > 4.0f) break;
						}
						float jDist = (jx * jx + jy * jy > 4.0f) ? -cr : cr;
						clipDist = max(jDist, fabs(cz.z) - sz);
						break;
					}
					case 40: // Mandelbrot Set Clip (2D extruded)
					{
						float mx = 0.0f, my = 0.0f;
						for (int k = 0; k < 8; k++)
						{
							float tx2 = mx * mx - my * my + cz.x;
							my = 2.0f * mx * my + cz.y;
							mx = tx2;
							if (mx * mx + my * my > 4.0f) break;
						}
						float mDist = (mx * mx + my * my > 4.0f) ? -cr : cr;
						clipDist = max(mDist, fabs(cz.z) - sz);
						break;
					}
					case 41: // 4D Hypercube Clip
					{
						clipDist = max(max(fabs(cz.x), fabs(cz.y)), max(fabs(cz.z), fabs(z.w))) - cr;
						break;
					}
					case 42: // 4D Hypersphere Clip
					{
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z + z.w*z.w) - cr;
						break;
					}
					case 43: // Time-Dependent Clip
					{
						float time = (float)i * mut->clipFrequency;
						float tR = cr * (1.0f + mut->clipAmplitude * native_sin(time));
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - tR;
						break;
					}
					case 44: // Orbit-Dependent Clip
					{
						float orbitR = cr * (1.0f + mut->clipAmplitude * native_sin(aux.color * mut->clipFrequency));
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - orbitR;
						break;
					}
					case 45: // DE-Dependent Clip
					{
						float deR = cr * (1.0f + mut->clipAmplitude * native_log(1.0f + fabs(aux.DE)));
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - deR;
						break;
					}
					case 46: // Color-Dependent Clip
					{
						float colR = cr * (1.0f + mut->clipAmplitude * native_sin(aux.color * mut->clipFrequency));
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - colR;
						break;
					}
					case 47: // Iteration-Dependent Clip
					{
						float iterR = cr * (1.0f + mut->clipAmplitude * (float)i / 250.0f);
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - iterR;
						break;
					}
					case 48: // Random-Dependent Clip
					{
						float rh = fabs(native_sin((float)i * 12.9898f + cz.x * 78.233f) * 43758.5453f);
						rh = rh - floor(rh);
						float randR = cr * (1.0f + mut->clipAmplitude * (rh - 0.5f));
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - randR;
						break;
					}
					case 49: // Neural-Dependent Clip (simplified MLP)
					{
						float nx = tanh(ca * cz.x + cb * cz.y + cc * cz.z);
						float ny = tanh(cb * cz.x - ca * cz.y + cc * cz.z);
						float nz = tanh(cc * cz.x + ca * cz.y - cb * cz.z);
						clipDist = native_sqrt(nx*nx + ny*ny + nz*nz) - cr;
						break;
					}
					case 50: // Fractal Recursion Clip
					{
						float3 rz = cz;
						float rscale = 1.0f;
						for (int k = 0; k < 5; k++)
						{
							rz = fabs(rz) * 2.0f - (float3){ca, ca, ca};
							rscale *= 2.0f;
							float rd = native_sqrt(rz.x*rz.x + rz.y*rz.y + rz.z*rz.z) - cr;
							rd /= rscale;
							if (rd < clipDist) clipDist = rd;
						}
						break;
					}
				}
				// Apply boolean operation
				int bop = mut->clipBooleanOp;
				if (bop == 0) aux.dist = max(aux.dist, clipDist); // Intersection (AND)
				else if (bop == 1) aux.dist = min(aux.dist, clipDist); // Union (OR)
				else if (bop == 2) aux.dist = max(aux.dist, -clipDist); // Difference (A-B)
				else if (bop == 3) aux.dist = max(min(aux.dist, clipDist), -max(aux.dist, clipDist)); // XOR
				else if (bop == 4) // Smooth union
				{
					float kk = mut->clipSmoothK;
					float hh = clamp(0.5f + 0.5f * (clipDist - aux.dist) / kk, 0.0f, 1.0f);
					aux.dist = mix(clipDist, aux.dist, hh) - kk * hh * (1.0f - hh);
				}
				else if (bop == 5) // Smooth difference
				{
					float kk2 = mut->clipSmoothK;
					float hh2 = clamp(0.5f - 0.5f * (aux.dist + clipDist) / kk2, 0.0f, 1.0f);
					aux.dist = mix(aux.dist, -clipDist, hh2) + kk2 * hh2 * (1.0f - hh2);
				}
			}

			// v7.7 — Jos Leys DE system (per-section iteration range)
			if (i >= mut->josIterStart && i < mut->josIterStop && mut->josLeysDeType != 0)
			{
				float jf = mut->josFactor;
				float ja = mut->josParamA, jb = mut->josParamB, jc = mut->josParamC, jd = mut->josParamD;
				float jfreq = mut->josFreq, jamp = mut->josAmp, jsc = mut->josScale, jph = mut->josPhase;
				float zx = z.x, zy = z.y, zz2 = z.z;
				float rr = zx*zx + zy*zy + zz2*zz2; if (rr < 1e-21f) rr = 1e-21f;
				float r = native_sqrt(rr);
				switch (mut->josLeysDeType)
				{
					case 1: { float k1=ja,k2=jb,k3=jc,k4=jd; float curv=(k1+k2+k3+k4)/fmax(1.0f,r); aux.DE*=(1.0f+jf*curv); break; }
					case 2: { float phi=atan2(zy,zx); float sp=ja*native_exp(2.0f*M_PI_F*(jb*phi+jc*native_log(fmax(1e-10f,r)))); aux.DE*=(1.0f+jf*sp); break; }
					case 3: { float prod=1.0f; for(int k=0;k<4;k++){float dk=r+ja*(float)(k+1); prod*=fmax(0.01f,dk);} aux.DE*=(1.0f+jf*jsc/fmax(1e-10f,prod)); break; }
					case 4: { float af=ja*native_log(fmax(1e-10f,r))+jb*atan2(zy,zx); aux.DE*=(1.0f+jf*tanh(af)); break; }
					case 5: { float hyp=4.0f*M_PI_F*(ja-1.0f)/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*tanh(hyp)); break; }
					case 6: { float bel=ja*zy/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*tanh(bel)); break; }
					case 7: { float tr=ja*jb/fmax(1e-10f,r); aux.DE*=(1.0f+jf*tanh(tr)); break; }
					case 8: { float rl=ja/(fmax(1e-10f,r*r)+jb*jb); aux.DE*=(1.0f+jf*rl); break; }
					case 9: { float bs=ja*jb*jc/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*tanh(bs)); break; }
					case 10: { float ew=ja*native_sin(jfreq*zx)*native_cos(jfreq*zy)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*ew); break; }
					case 11: { float hc=native_exp(-fabs(zy))*ja/fmax(1e-10f,r); aux.DE*=(1.0f+jf*hc); break; }
					case 12: { float q2=fmax(1.0f,ja); float fr2=1.0f/(2.0f*q2*q2); aux.DE*=(1.0f+jf*fr2/fmax(1e-10f,r)); break; }
					case 13: { float med=(zx+zy)/(fmax(1e-10f,2.0f*r)); aux.DE*=(1.0f+jf*ja*med); break; }
					case 14: { float jt=ja*native_sin(M_PI_F*zx/fmax(0.01f,jb))*native_sin(M_PI_F*zy/fmax(0.01f,jc)); aux.DE*=(1.0f+jf*jt/fmax(1e-10f,rr)); break; }
					case 15: { float eta=native_exp(M_PI_F*zy/(12.0f*fmax(0.01f,ja))); for(int n=1;n<8;n++) eta*=(1.0f-native_exp(-2.0f*M_PI_F*n*fabs(zy)/fmax(0.01f,ja))); aux.DE*=(1.0f+jf*fabs(eta)); break; }
					case 16: { float wp=1.0f/(rr+1e-10f); for(int n=1;n<6;n++){float dn2=(zx-n*ja)*(zx-n*ja)+(zy-n*jb)*(zy-n*jb)+zz2*zz2; wp+=1.0f/fmax(1e-10f,dn2)-1.0f/(n*n*ja*ja+n*n*jb*jb+1e-10f);} aux.DE*=(1.0f+jf*fabs(wp)); break; }
					case 17: { float th=0.0f; for(int n=0;n<8;n++){float qn=native_exp(-M_PI_F*n*n*fabs(zy)/fmax(0.01f,ja)); th+=qn*native_cos(2.0f*M_PI_F*n*zx/fmax(0.01f,ja));} aux.DE*=(1.0f+jf*fabs(th)); break; }
					case 18: { float eis=0.0f; for(int m=-3;m<=3;m++) for(int n=-3;n<=3;n++){if(m==0&&n==0)continue; float dn=m*ja+n*jb; eis+=1.0f/fmax(1e-10f,native_powr(fabs(dn*dn+rr),jc));} aux.DE*=(1.0f+jf*fabs(eis)); break; }
					case 19: { float hek=ja*native_sin(jfreq*r)*native_cos(jfreq*atan2(zy,zx)+jph); aux.DE*=(1.0f+jf*hek/fmax(1e-10f,r)); break; }
					case 20: { float maas=ja*native_sin(jfreq*native_log(fmax(1e-10f,r)))*native_cos(jfreq*atan2(zy,zx)); aux.DE*=(1.0f+jf*maas); break; }
					case 21: { float selb=1.0f; for(int k=1;k<=5;k++){selb*=(1.0f-native_exp(-ja*k*r));} aux.DE*=(1.0f+jf*(1.0f-fabs(selb))); break; }
					case 22: { float ruel=1.0f; for(int k=1;k<=5;k++){ruel*=(1.0f-native_exp(-ja*k*native_log(fmax(1e-10f,r))));} aux.DE*=(1.0f+jf*fabs(ruel)); break; }
					case 23: { float dz=ja*native_sin(jfreq*r)*native_exp(-jb*r); aux.DE*=(1.0f+jf*dz); break; }
					case 24: { float gut=0.0f; for(int p=1;p<=5;p++){gut+=ja*native_cos(jfreq*p*r+jph)/fmax(1.0f,(float)p);} aux.DE*=(1.0f+jf*gut/fmax(1e-10f,r)); break; }
					case 25: { float berry=ja*zy*zz2/fmax(1e-10f,rr*r); aux.DE*=(1.0f+jf*berry); break; }
					case 26: { float hann=ja*zx*zy/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*hann); break; }
					case 27: { float ab_ph=ja*atan2(zy,zx)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*ab_ph); break; }
					case 28: { float ac_ph=ja*jb*zz2/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*ac_ph); break; }
					case 29: { float sab=ja*native_sin(jfreq*r)*zy/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*sab); break; }
					case 30: { float hmw=ja*(zx*zy-zy*zz2)/fmax(1e-10f,rr*r); aux.DE*=(1.0f+jf*hmw); break; }
					case 31: { float ana=ja*native_sin(jfreq*rr+jph)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*ana); break; }
					case 32: { float panch=ja*native_cos(jfreq*zx)*native_cos(jfreq*zy)*native_cos(jfreq*zz2); aux.DE*=(1.0f+jf*panch/fmax(1e-10f,r)); break; }
					case 33: { float mt=ja/(2.0f*fmax(1e-10f,fabs(zx-zy))); aux.DE*=(1.0f+jf*tanh(mt)); break; }
					case 34: { float ml=M_PI_F*ja/(2.0f*fmax(1e-10f,r)); aux.DE*=(1.0f+jf*tanh(ml)); break; }
					case 35: { float sw=ja*jb/(fmax(1e-10f,r)*jc); aux.DE*=(1.0f+jf*tanh(sw)); break; }
					case 36: { float pw=ja*native_exp(-jb*rr); aux.DE*=(1.0f+jf*pw); break; }
					case 37: { float gp=ja*native_sqrt(fmax(0.0f,r/jb)); aux.DE*=(1.0f+jf*tanh(gp)); break; }
					case 38: { float rov=ja*native_sin(jfreq*zx+jph)*native_cos(jfreq*zy); aux.DE*=(1.0f+jf*rov/fmax(1e-10f,r)); break; }
					case 39: { float barb=ja*native_sqrt(fmax(0.0f,zx*zx+zy*zy))/fmax(1e-10f,r); aux.DE*=(1.0f+jf*barb); break; }
					case 40: { float con=ja*native_exp(-jb*fabs(zz2))*native_sin(jfreq*r); aux.DE*=(1.0f+jf*con); break; }
					case 41: { float ach=ja*native_sin(jfreq*zx)*native_sin(jfreq*zy)*native_cos(jfreq*zz2)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*ach); break; }
					case 42: { float que=ja/(fmax(1e-10f,rr)); aux.DE*=(1.0f+jf*que); break; }
					case 43: { float rw=0.0f; for(int n=1;n<=8;n++){rw+=native_cos(jfreq*n*zx+jph*n)*native_exp(-jb*n);} aux.DE*=(1.0f+jf*ja*rw/fmax(1e-10f,r)); break; }
					case 44: { float nd=ja*floor(native_sin(jfreq*zx)*native_sin(jfreq*zy)*4.0f+2.0f)/4.0f; aux.DE*=(1.0f+jf*nd); break; }
					case 45: { float nl=ja*fabs(native_sin(jfreq*zx)*native_cos(jfreq*zy))*jb; aux.DE*=(1.0f+jf*nl/fmax(1e-10f,r)); break; }
					case 46: { float pc=ja*(tanh(jb*(r-jc))+1.0f)*0.5f; aux.DE*=(1.0f+jf*pc); break; }
					case 47: { float ip=ja*tanh(jb*(native_sin(jfreq*zx)+native_sin(jfreq*zy)+native_sin(jfreq*zz2))); aux.DE*=(1.0f+jf*ip); break; }
					case 48: { float cle=ja*native_sin(jfreq*atan2(zy,zx))*native_exp(-jb*r); aux.DE*=(1.0f+jf*cle); break; }
					case 49: { float sle=ja*zy/(fmax(1e-10f,rr))*native_exp(-jb*fabs(zx)); aux.DE*=(1.0f+jf*sle); break; }
					case 50: { float gff=ja*native_cos(jfreq*zx)*native_cos(jfreq*zy)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*gff); break; }
					case 51: { float lqg=ja*native_exp(fmin(jb*native_sin(jfreq*r+jph),20.0f)); aux.DE*=(1.0f+jf*lqg/fmax(1e-10f,r)); break; }
					case 52: { float bm=ja*native_sqrt(fmax(0.0f,rr-jb*jb))/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*bm); break; }
					case 53: { float pm2=ja*(2.0f-fabs(zx)+fabs(zy)-fabs(zz2))/fmax(1e-10f,r); aux.DE*=(1.0f+jf*tanh(pm2)); break; }
					case 54: { float tt=ja*(zx*zy+zy*zz2+zz2*zx)/fmax(1e-10f,rr*r); aux.DE*=(1.0f+jf*tt); break; }
					case 55: { float jon=ja*native_sin(M_PI_F*jb*r+jph)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*jon); break; }
					case 56: { float hom=ja*(native_sin(jfreq*zx)+native_sin(jfreq*zy))*jb/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*hom); break; }
					case 57: { float kau=ja*tanh(jb*native_sin(jfreq*r)*native_cos(jfreq*atan2(zy,zx))); aux.DE*=(1.0f+jf*kau); break; }
					case 58: { float cs=ja*native_sin(jfreq*zx)*native_sin(jfreq*zy)*native_sin(jfreq*zz2)/(fmax(1e-10f,r*r)); aux.DE*=(1.0f+jf*cs); break; }
					case 59: { float wrt=ja*jb*native_cos(jfreq*r+jph)/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*wrt); break; }
					case 60: { float tv=ja*jb*jc/(fmax(1e-10f,rr*r)); aux.DE*=(1.0f+jf*tanh(tv)); break; }
					case 61: { float cy=ja*native_powr(fmax(1e-10f,r),jb-3.0f); aux.DE*=(1.0f+jf*cy); break; }
					case 62: { float dw=ja/(fmax(1e-10f,rr))*native_cos(jfreq*zz2); aux.DE*=(1.0f+jf*dw); break; }
					case 63: { float yd=ja*jb*(zx*zy-zy*zx)/(fmax(1e-10f,rr)); aux.DE*=(1.0f+jf*yd*jc); break; }
					case 64: { float mtc=ja*native_sin(jfreq*zx+jph)*native_cos(jfreq*zy)*native_sin(jfreq*zz2)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*mtc); break; }
					case 65: { float fus=ja*(native_sin(jb*zx)*native_sin(jc*zy)+native_sin(jd*zz2))/fmax(1e-10f,r); aux.DE*=(1.0f+jf*fus); break; }
					case 66: { float bra=ja*native_cos(jfreq*atan2(zy,zx)+jph)*native_cos(jfreq*atan2(zz2,r)); aux.DE*=(1.0f+jf*bra); break; }
					case 67: { float rib=ja*native_sin(jfreq*r)*native_cos(jb*atan2(zy,zx)+jph); aux.DE*=(1.0f+jf*rib/fmax(1e-10f,r)); break; }
					case 68: { float hopf=ja*jb*tanh(jc*(zx*zy+zy*zz2)); aux.DE*=(1.0f+jf*hopf/fmax(1e-10f,r)); break; }
					case 69: { float qg=ja*native_powr(fmax(1e-10f,r),-jb)*native_sin(jfreq*r+jph); aux.DE*=(1.0f+jf*qg); break; }
					case 70: { float dd=ja*jb*(1.0f/(fmax(1e-10f,rr))+zx*zy/(fmax(1e-10f,rr*r))); aux.DE*=(1.0f+jf*tanh(dd)); break; }
					case 71: { float nich=ja*native_exp(-jb*rr)*native_sin(jfreq*zx)*native_cos(jfreq*zy); aux.DE*=(1.0f+jf*nich); break; }
					case 72: { float rack=ja*(zx*zx-zy*zy)/(fmax(1e-10f,rr))*jb; aux.DE*=(1.0f+jf*rack); break; }
					case 73: { float quan=ja*(zx*zx*zx-3.0f*zx*zy*zy)/(fmax(1e-10f,rr*r))*jb; aux.DE*=(1.0f+jf*quan); break; }
					case 74: { float biq=ja*native_sin(jfreq*(zx+zy))*native_cos(jfreq*(zx-zy))/fmax(1e-10f,r); aux.DE*=(1.0f+jf*biq); break; }
					case 75: { float ske=ja*jb*native_sin(jfreq*r+jph)/(fmax(1e-10f,rr)); aux.DE*=(1.0f+jf*ske); break; }
					case 76: { float khov=ja*native_powr(fmax(1e-10f,fabs(native_sin(jfreq*r))),2.0f)*jb/fmax(1e-10f,r); aux.DE*=(1.0f+jf*khov); break; }
					case 77: { float hf=ja*native_exp(-jb*r)*native_cos(jfreq*zz2+jph); aux.DE*=(1.0f+jf*hf); break; }
					case 78: { float kf=ja*atan2(zy,zx)*native_exp(-jb*fabs(zz2))/M_PI_F; aux.DE*=(1.0f+jf*kf/fmax(1e-10f,r)); break; }
					case 79: { float ech2=ja*native_sin(jfreq*zx)*native_exp(-jb*zy)*native_cos(jfreq*zz2)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*ech2); break; }
					case 80: { float sft=ja*native_cos(jfreq*r)*native_sin(jfreq*atan2(zy,zx)+jph)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*sft); break; }
					case 81: { float lag=ja*(zx*zy+zy*zz2)/(fmax(1e-10f,rr))*jb; aux.DE*=(1.0f+jf*lag); break; }
					case 82: { float fuk=ja*native_sin(jb*zx)*native_cos(jc*zy)*native_sin(jd*zz2)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*fuk); break; }
					case 83: { float mir=ja*(native_sin(jfreq*zx)*native_sin(jfreq*zy)-native_cos(jfreq*zz2))/fmax(1e-10f,r); aux.DE*=(1.0f+jf*mir); break; }
					case 84: { float hmir=ja*native_cos(jfreq*(zx+zy+zz2)+jph)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*hmir); break; }
					case 85: { float syz=ja*native_sin(jfreq*r)*native_sin(jfreq*atan2(zy,zx))*native_cos(jfreq*zz2/fmax(0.01f,jb)); aux.DE*=(1.0f+jf*syz); break; }
					case 86: { float slag=ja*native_cos(jfreq*zx+jph)*jb; aux.DE*=(1.0f+jf*slag/fmax(1e-10f,r)); break; }
					case 87: { float g2=ja*native_sin(jfreq*zx)*native_sin(jfreq*zy)*native_sin(jfreq*zz2)*jb; aux.DE*=(1.0f+jf*g2/fmax(1e-10f,rr)); break; }
					case 88: { float sp7=ja*native_cos(jfreq*(zx*zy+zy*zz2+zz2*zx)/fmax(1e-10f,rr)+jph); aux.DE*=(1.0f+jf*sp7); break; }
					case 89: { float cy2=ja*native_exp(-jb*rr)*jc; aux.DE*=(1.0f+jf*cy2); break; }
					case 90: { float hkah=ja*(zx*zx-zy*zy+zz2*zz2)/(fmax(1e-10f,rr*r))*jb; aux.DE*=(1.0f+jf*hkah); break; }
					case 91: { float qkah=ja*jb*(zx*zy*zz2)/(fmax(1e-10f,rr*rr)); aux.DE*=(1.0f+jf*tanh(qkah)); break; }
					case 92: { float sas=ja*native_sqrt(fmax(0.0f,r-jb))/fmax(1e-10f,r); aux.DE*=(1.0f+jf*sas); break; }
					case 93: { float s3s=ja*(native_sin(jfreq*zx)+native_sin(jfreq*zy)+native_sin(jfreq*zz2))/(3.0f*fmax(1e-10f,r)); aux.DE*=(1.0f+jf*s3s); break; }
					case 94: { float exh=ja*native_powr(fmax(1e-10f,r),-jb)*native_cos(jfreq*r+jph); aux.DE*=(1.0f+jf*exh); break; }
					case 95: { float joy=ja*native_sin(jfreq*zx/fmax(0.01f,jb))*native_sin(jfreq*zy/fmax(0.01f,jc))*native_sin(jfreq*zz2/fmax(0.01f,jd)); aux.DE*=(1.0f+jf*joy); break; }
					case 96: { float kov=ja*native_exp(-jb*fabs(zz2))*native_cos(jfreq*native_sqrt(fmax(0.0f,zx*zx+zy*zy))); aux.DE*=(1.0f+jf*kov); break; }
					case 97: { float chnp=ja*jb*tanh(jc*r-jd); aux.DE*=(1.0f+jf*chnp/fmax(1e-10f,r)); break; }
					case 98: { float bsr=ja*native_exp(-jb*r)*native_cos(jfreq*r+jph)*jc; aux.DE*=(1.0f+jf*bsr); break; }
					case 99: { float ah=ja*jb/(fmax(1e-10f,rr))*native_cos(jfreq*atan2(zy,zx)+jph); aux.DE*=(1.0f+jf*ah); break; }
					case 100: { float gh=ja*jb*jc/fmax(1e-10f,r)*native_sin(jfreq*zz2+jph); aux.DE*=(1.0f+jf*gh); break; }
				}
			}

			// v7.7 — Pseudokleinian DE system (per-section iteration range)
			if (i >= mut->pkIterStart && i < mut->pkIterStop && mut->pseudoKleinianDeType != 0)
			{
				float pf = mut->pkFactor;
				float pa = mut->pkParamA, pb = mut->pkParamB, pc = mut->pkParamC, pd = mut->pkParamD;
				float pfreq = mut->pkFreq, pamp = mut->pkAmp, psc = mut->pkScale, pph = mut->pkPhase;
				float zx = z.x, zy = z.y, zz2 = z.z;
				float rr = zx*zx + zy*zy + zz2*zz2; if (rr < 1e-21f) rr = 1e-21f;
				float r = native_sqrt(rr);
				switch (mut->pseudoKleinianDeType)
				{
					case 1: { float mu=pa*zy/fmax(1e-10f,rr); aux.DE*=(1.0f+pf*tanh(mu)); break; }
					case 2: { float bers=pa*native_log(fmax(1e-10f,r))*pb; aux.DE*=(1.0f+pf*tanh(bers)); break; }
					case 3: { float eq=pa*native_sin(pfreq*zx)*native_cos(pfreq*zy); aux.DE*=(1.0f+pf*eq/fmax(1e-10f,r)); break; }
					case 4: { float bc=pa*pb*zy/fmax(1e-10f,rr); aux.DE*=(1.0f+pf*bc); break; }
					case 5: { float ham=pa*native_exp(-pb*r)*native_sin(pfreq*zx); aux.DE*=(1.0f+pf*ham); break; }
					case 6: { float wp=pa*pb/(fmax(1e-10f,rr)); aux.DE*=(1.0f+pf*wp); break; }
					case 7: { float tm=pa*fabs(zx-zy)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*tanh(tm)); break; }
					case 8: { float kob=pa*tanh(pb*r)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*kob); break; }
					case 9: { float car=pa*fabs(native_sin(pfreq*r))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*car); break; }
					case 10: { float berg=pa*pb*native_cos(pfreq*zx+pph)*native_cos(pfreq*zy)/fmax(1e-10f,rr); aux.DE*=(1.0f+pf*berg); break; }
					case 11: { float ke=pa*pb/fmax(1e-10f,r)*tanh(pc*rr); aux.DE*=(1.0f+pf*ke); break; }
					case 12: { float csc2=pa*tanh(pb*(r-pc)); aux.DE*=(1.0f+pf*csc2); break; }
					case 13: { float duy=pa*pb*native_exp(-pc*rr); aux.DE*=(1.0f+pf*duy); break; }
					case 14: { float hk=pa*native_sin(pfreq*zx)*native_cos(pfreq*zy)*native_exp(-pb*fabs(zz2)); aux.DE*=(1.0f+pf*hk); break; }
					case 15: { float nah=pa*pb*(zx*zy+zy*zz2)/(fmax(1e-10f,rr*r)); aux.DE*=(1.0f+pf*nah); break; }
					case 16: { float hm=pa*native_exp(-pb*rr)*native_cos(pfreq*r+pph); aux.DE*=(1.0f+pf*hm); break; }
					case 17: { float ms=pa*(1.0f-zz2/fmax(1e-10f,r)); aux.DE*=(1.0f+pf*ms*pb); break; }
					case 18: { float cmc=pa*native_cos(pfreq*zx)*native_cos(pfreq*zy)*pb; aux.DE*=(1.0f+pf*cmc/fmax(1e-10f,r)); break; }
					case 19: { float wil=pa*(zx*zx+zy*zy)/(fmax(1e-10f,rr*r))*pb; aux.DE*=(1.0f+pf*wil); break; }
					case 20: { float iso=pa*native_cos(pfreq*zx+pph)*native_cos(pfreq*zy)*pb; aux.DE*=(1.0f+pf*iso); break; }
					case 21: { float lax=pa*native_sin(pfreq*zx)*native_cos(pfreq*zy)*native_sin(pfreq*zz2)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*lax); break; }
					case 22: { float bac=pa*native_exp(-pb*r)*native_sin(pfreq*r+pph); aux.DE*=(1.0f+pf*bac); break; }
					case 23: { float dar=pa*pb*native_cos(pfreq*r+pph)/fmax(1e-10f,rr); aux.DE*=(1.0f+pf*dar); break; }
					case 24: { float mou=pa*native_sin(pfreq*zx)*native_sin(pfreq*zy)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*mou); break; }
					case 25: { float hir=pa*pb*native_exp(-pc*rr)*native_cos(pfreq*r); aux.DE*=(1.0f+pf*hir); break; }
					case 26: { float sat=pa*native_sin(pfreq*zx+pph)*native_cos(pfreq*zy)*native_sin(pfreq*zz2)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*sat); break; }
					case 27: { float kp=pa*(native_sin(pfreq*zx)*native_cos(pfreq*zy)+native_sin(pfreq*zy)*native_cos(pfreq*zz2))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*kp); break; }
					case 28: { float kdv=pa*native_sin(pfreq*zx+pph)*native_exp(-pb*zy*zy)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*kdv); break; }
					case 29: { float nls=pa*native_exp(-pb*(zx*zx+zy*zy))*native_cos(pfreq*zz2+pph); aux.DE*=(1.0f+pf*nls); break; }
					case 30: { float sg=pa*native_sin(native_sin(pfreq*zx+pph))*pb; aux.DE*=(1.0f+pf*sg/fmax(1e-10f,r)); break; }
					case 31: { float toda=pa*native_exp(pb*(zx-zy))-pa*native_exp(pb*(zy-zz2)); aux.DE*=(1.0f+pf*tanh(toda)/fmax(1e-10f,r)); break; }
					case 32: { float cm=0.0f; {float d1=zx-zy; float d2=zy-zz2; float d3=zx-zz2; cm=pa*(1.0f/fmax(1e-10f,d1*d1*d1)+1.0f/fmax(1e-10f,d2*d2*d2)+1.0f/fmax(1e-10f,d3*d3*d3));} aux.DE*=(1.0f+pf*tanh(cm)); break; }
					case 33: { float rs=pa*tanh(pb*(zx-zy))*tanh(pb*(zy-zz2))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*rs); break; }
					case 34: { float hs=pa*pb*(zx*zy+zy*zz2+zz2*zx)/(fmax(1e-10f,rr*r)); aux.DE*=(1.0f+pf*hs); break; }
					case 35: { float bm=pa*native_sin(pfreq*zx)*native_sin(pfreq*zy)*pb/fmax(1e-10f,r); aux.DE*=(1.0f+pf*bm); break; }
					case 36: { float aci=pa*native_sin(pfreq*r+pph)*native_cos(pfreq*atan2(zy,zx))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*aci); break; }
					case 37: { float sep=pa*(native_sin(pb*zx)+native_sin(pc*zy)+native_sin(pd*zz2))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*sep); break; }
					case 38: { float aa=pa*native_cos(pfreq*r)*pfreq/fmax(1e-10f,r); aux.DE*=(1.0f+pf*aa); break; }
					case 39: { float kam=pa*native_cos(pfreq*r+pph)*(1.0f-pb/fmax(1e-10f,r)); aux.DE*=(1.0f+pf*kam); break; }
					case 40: { float nek=pa*native_exp(-1.0f/fmax(1e-10f,native_powr(fmax(1e-10f,pb),pc))); aux.DE*=(1.0f+pf*nek); break; }
					case 41: { float ard=pa*native_sin(pfreq*zx)*native_cos(pfreq*zy)*native_sin(pfreq*zz2)/fmax(1e-10f,rr); aux.DE*=(1.0f+pf*ard); break; }
					case 42: { float abm=pa*fabs(native_sin(pfreq*zx+pph))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*abm); break; }
					case 43: { float mse=pa*pb*native_exp(-pc*rr)*native_sin(pfreq*zx); aux.DE*=(1.0f+pf*mse); break; }
					case 44: { float pei=pa*(1.0f-native_exp(-pb*fabs(zx-zy)))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*pei); break; }
					case 45: { float fk=pa*native_sin(pfreq*zx+pph)*native_cos(pb*zy); aux.DE*=(1.0f+pf*fk/fmax(1e-10f,r)); break; }
					case 46: { float sm=pa*native_sin(pfreq*atan2(zy,zx)+pph)*pb; aux.DE*=(1.0f+pf*sm/fmax(1e-10f,r)); break; }
					case 47: { float chi=pa*tanh(pb*(r-pc)); aux.DE*=(1.0f+pf*chi); break; }
					case 48: { float gre=0.5f*(1.0f-pa*native_cos(pfreq*r+pph)/fmax(1e-10f,r)); aux.DE*=(1.0f+pf*gre); break; }
					case 49: { float rg=pa*native_powr(fmax(1e-10f,r),-pb)*native_cos(pfreq*native_log(fmax(1e-10f,r))+pph); aux.DE*=(1.0f+pf*rg); break; }
					case 50: { float fg=pa*4.669201609f*native_sin(pfreq*r+pph)/(fmax(1e-10f,r)); aux.DE*=(1.0f+pf*fg); break; }
					case 51: { float sh3=pa*floor(native_sin(pfreq*zx)*3.0f+1.5f)/3.0f; aux.DE*=(1.0f+pf*sh3); break; }
					case 52: { float sar=pa*(native_sin(pfreq*zx)*native_sin(pfreq*zy)*native_sin(pfreq*zz2)>0.0f?1.0f:-1.0f)*pb; aux.DE*=(1.0f+pf*sar/fmax(1e-10f,r)); break; }
					case 53: { float sml=pa*tanh(pb*zx)*tanh(pb*zy); aux.DE*=(1.0f+pf*sml); break; }
					case 54: { float ano=pa*fabs(fmod(pb*zx+pc*zy,1.0f)-0.5f)*4.0f; aux.DE*=(1.0f+pf*ano/fmax(1e-10f,r)); break; }
					case 55: { float axa=pa*native_exp(-pb*r)*native_cos(pfreq*r+pph); aux.DE*=(1.0f+pf*axa); break; }
					case 56: { float srb=pa*pb*native_exp(-pc*rr)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*srb); break; }
					case 57: { float pes=pa*native_log(fmax(1e-10f,r))*pb; aux.DE*=(1.0f+pf*tanh(pes)); break; }
					case 58: { float ly=pa*pb*native_log(fmax(1e-10f,r))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*tanh(ly)); break; }
					case 59: { float yt=pa*native_exp(-pb*r)*native_sin(pfreq*r+pph); aux.DE*=(1.0f+pf*yt); break; }
					case 60: { float to=pa*pb*native_sin(pfreq*zx)*native_sin(pfreq*zy)/(fmax(1e-10f,rr)); aux.DE*=(1.0f+pf*to); break; }
					case 61: { float rpf=pa*native_exp(-pb*r)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*rpf); break; }
					case 62: { float thf=pa*tanh(pb*(r-pc))*pd; aux.DE*=(1.0f+pf*thf); break; }
					case 63: { float gib=pa*native_exp(-pb*rr)*pc; aux.DE*=(1.0f+pf*gib); break; }
					case 64: { float eqs=pa*native_cos(pfreq*r+pph)/(fmax(1e-10f,r)); aux.DE*=(1.0f+pf*eqs); break; }
					case 65: { float pht=pa*(1.0f/(1.0f+native_exp(-pb*(r-pc)))-0.5f)*2.0f; aux.DE*=(1.0f+pf*pht); break; }
					case 66: { float brf=pa*native_exp(-pb*r)*native_cos(pfreq*atan2(zy,zx)+pph); aux.DE*=(1.0f+pf*brf); break; }
					case 67: { float spc=pa*native_sin(pfreq*zx)*native_cos(pfreq*zy)*native_sin(pfreq*zz2)*pb; aux.DE*=(1.0f+pf*spc/fmax(1e-10f,r)); break; }
					case 68: { float sha=pa*native_exp(-pb*fabs(r-pc)); aux.DE*=(1.0f+pf*sha); break; }
					case 69: { float sst=pa*native_cos(pfreq*r+pph)*native_exp(-pb*r); aux.DE*=(1.0f+pf*sst); break; }
					case 70: { float oms=pa*native_sin(pfreq*zx)*native_sin(pfreq*zy)*pb/fmax(1e-10f,rr); aux.DE*=(1.0f+pf*oms); break; }
					case 71: { float mss=pa*native_exp(-pb*r)*(1.0f-native_cos(pfreq*r)); aux.DE*=(1.0f+pf*mss); break; }
					case 72: { float gfl=-pa*pb*(zx+zy+zz2)/fmax(1e-10f,r*r); aux.DE*=(1.0f+pf*tanh(gfl)); break; }
					case 73: { float mor=pa*(r-pb)*(r-pb)*native_exp(-pc*r); aux.DE*=(1.0f+pf*mor/fmax(1e-10f,r)); break; }
					case 74: { float moh=pa*native_exp(-pb*rr)*native_sin(pfreq*r+pph); aux.DE*=(1.0f+pf*moh); break; }
					case 75: { float flo=pa*native_sin(pfreq*zx)*native_cos(pfreq*zy)*pb; aux.DE*=(1.0f+pf*flo/fmax(1e-10f,r)); break; }
					case 76: { float sca=pa*pb*r*r/(fmax(1e-10f,r*r+pc*pc)); aux.DE*=(1.0f+pf*sca); break; }
					case 77: { float hof=pa*pb/fmax(1e-10f,r); aux.DE*=(1.0f+pf*tanh(hof)); break; }
					case 78: { float hz=pa*M_PI_F*pb/(2.0f*fmax(1e-10f,r)); aux.DE*=(1.0f+pf*tanh(hz)); break; }
					case 79: { float ekh=pa*native_sin(pfreq*r+pph)*pb/fmax(1e-10f,r); aux.DE*=(1.0f+pf*ekh); break; }
					case 80: { float nsq=pa*pb*(1.0f-r/fmax(1e-10f,pc)); aux.DE*=(1.0f+pf*tanh(nsq)); break; }
					case 81: { float emb=pa*pb*native_sin(pfreq*r+pph)/fmax(1e-10f,rr); aux.DE*=(1.0f+pf*emb); break; }
					case 82: { float echc=pa*native_sin(pfreq*zx)*native_cos(pfreq*zy)*pb/fmax(1e-10f,r); aux.DE*=(1.0f+pf*echc); break; }
					case 83: { float fib=pa*native_sin(pfreq*r)*native_cos(1.618033988749f*pfreq*r+pph)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*fib); break; }
					case 84: { float hut=pa*pb*native_sin(pfreq*atan2(zy,zx)+pph)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*hut); break; }
					case 85: { float cmk=pa*native_cos(pfreq*r)*native_exp(-pb*r)*pc; aux.DE*=(1.0f+pf*cmk); break; }
					case 86: { float vfc=pa*pb*native_sin(pfreq*r+pph)/(fmax(1e-10f,r*r)); aux.DE*=(1.0f+pf*vfc); break; }
					case 87: { float pol=pa*native_exp(-pb*rr)*native_cos(pfreq*r)*pc; aux.DE*=(1.0f+pf*pol); break; }
					case 88: { float scc=pa*tanh(pb*r)*native_cos(pfreq*r+pph)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*scc); break; }
					case 89: { float gwi=pa*pb*native_sin(pfreq*zx)*native_sin(pfreq*zy)*native_sin(pfreq*zz2)/(fmax(1e-10f,rr)); aux.DE*=(1.0f+pf*gwi); break; }
					case 90: { float qco=pa*native_cos(pfreq*(zx+zy+zz2)+pph)*pb/fmax(1e-10f,r); aux.DE*=(1.0f+pf*qco); break; }
					case 91: { float msy=pa*(native_sin(pfreq*zx)*native_sin(pfreq*zy)-native_cos(pfreq*zz2))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*msy); break; }
					case 92: { float hv=pa*native_exp(-pb*rr)*native_sin(pfreq*r+pph); aux.DE*=(1.0f+pf*hv); break; }
					case 93: { float bat=pa*native_cos(pfreq*zx+pph)*native_cos(pfreq*zy)*native_cos(pfreq*zz2)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*bat); break; }
					case 94: { float gpo=pa*pb*native_sin(pfreq*r)/(fmax(1e-10f,r*r)); aux.DE*=(1.0f+pf*gpo); break; }
					case 95: { float syzf=pa*native_sin(pfreq*r)*native_sin(pfreq*atan2(zy,zx)+pph)*pb; aux.DE*=(1.0f+pf*syzf/fmax(1e-10f,r)); break; }
					case 96: { float gs=pa*native_exp(-pb*fabs(zz2))*native_cos(pfreq*native_sqrt(fmax(0.0f,zx*zx+zy*zy))+pph); aux.DE*=(1.0f+pf*gs); break; }
					case 97: { float scd=pa*pb*tanh(pc*native_sin(pfreq*r+pph)); aux.DE*=(1.0f+pf*scd/fmax(1e-10f,r)); break; }
					case 98: { float thf2=pa*native_sin(pfreq*zx+pph)*native_cos(pfreq*zy)*pb; aux.DE*=(1.0f+pf*thf2/fmax(1e-10f,r)); break; }
					case 99: { float cla=pa*pb*(zx*zy+zy*zz2+zz2*zx)/(fmax(1e-10f,rr*r)); aux.DE*=(1.0f+pf*cla); break; }
					case 100: { float clv=pa*native_sin(pfreq*(zx*zy+zy*zz2)/fmax(1e-10f,rr)+pph)*pb; aux.DE*=(1.0f+pf*clv); break; }
				}
			}

			// v7.8 [GPU] — Mandelbox Math system (per-section iteration range)
			if (i >= mut->mbIterStart && i < mut->mbIterStop && mut->mbMathType != 0)
			{
				float mf = mut->mbFactor;
				float ma = mut->mbParamA, mb = mut->mbParamB, mc = mut->mbParamC, md = mut->mbParamD;
				float me = mut->mbParamE, mff = mut->mbParamF, mg = mut->mbParamG, mh = mut->mbParamH;
				float zx = z.x, zy = z.y, zz2 = z.z;
				float rr = zx*zx + zy*zy + zz2*zz2; if (rr < 1e-21) rr = 1e-21;
				float r = native_sqrt(rr);
				switch (mut->mbMathType)
			{
					case 1: { if(zx>ma) z.x=mb*2.0-zx; if(zx<-ma) z.x=-mb*2.0-zx; if(zy>ma) z.y=mb*2.0-zy; if(zy<-ma) z.y=-mb*2.0-zy; if(zz2>ma) z.z=mb*2.0-zz2; if(zz2<-ma) z.z=-mb*2.0-zz2; aux.DE*=fabs(mf); break; }
					case 2: { float lim=ma*(1.0+0.1*native_sin(i*mc)); if(fabs(zx)>lim) z.x=copysign(mb*2.0,zx)-zx; if(fabs(zy)>lim) z.y=copysign(mb*2.0,zy)-zy; if(fabs(zz2)>lim) z.z=copysign(mb*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
					case 3: { float sx=ma,sy=mb,sz=mc; float fx=1.0/(1.0+native_exp(-sx*(fabs(zx)-md))); float fy=1.0/(1.0+native_exp(-sy*(fabs(zy)-md))); float fz=1.0/(1.0+native_exp(-sz*(fabs(zz2)-md))); z.x=zx*(1.0-fx)+copysign(me*2.0-fabs(zx),zx)*fx; z.y=zy*(1.0-fy)+copysign(me*2.0-fabs(zy),zy)*fy; z.z=zz2*(1.0-fz)+copysign(me*2.0-fabs(zz2),zz2)*fz; aux.DE*=fabs(mf); break; }
					case 4: { float l1=ma,v1=mb,l2=mc,v2=md; if(fabs(zx)>l1) z.x=copysign(v1*2.0,zx)-zx; if(fabs(zx)>l2) z.x=copysign(v2*2.0,zx)-zx; if(fabs(zy)>l1) z.y=copysign(v1*2.0,zy)-zy; if(fabs(zy)>l2) z.y=copysign(v2*2.0,zy)-zy; if(fabs(zz2)>l1) z.z=copysign(v1*2.0,zz2)-zz2; if(fabs(zz2)>l2) z.z=copysign(v2*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
					case 5: { float rxy=native_sqrt(zx*zx+zy*zy); if(rxy>ma){ float th=atan2(zy,zx); float nr=ma*2.0-rxy; z.x=nr*native_cos(th); z.y=nr*native_sin(th); } aux.DE*=fabs(mf); break; }
					case 6: { float rxy=native_sqrt(zx*zx+zy*zy); float ea=(zx/(ma+1e-21))*(zx/(ma+1e-21))+(zy/(mb+1e-21))*(zy/(mb+1e-21)); if(ea>1.0){ float sc=1.0/native_sqrt(ea); z.x*=sc; z.y*=sc; } aux.DE*=fabs(mf); break; }
					case 7: { if(fabs(zx)+fabs(zy)>ma){ float sx=(zx>0)?1.0:-1.0,sy=(zy>0)?1.0:-1.0; float nx=ma*0.5*sx,ny=ma*0.5*sy; z.x=2.0*nx-zx; z.y=2.0*ny-zy; } aux.DE*=fabs(mf)*1.41421356; break; }
					case 8: { float ax=fabs(zx),ay=fabs(zy); float hx=fmax(ax,ay*0.8660254+ax*0.5); if(hx>ma){ z.x=copysign(ma*2.0-ax,zx); z.y=copysign(ma*2.0-ay,zy); } aux.DE*=fabs(mf); break; }
					case 9: { float ax=fabs(zx),ay=fabs(zy); float ox=fmax(ax,fmax(ay,(ax+ay)*0.7071068)); if(ox>ma){ z.x=copysign(ma*2.0-ax,zx); z.y=copysign(ma*2.0-ay,zy); } aux.DE*=fabs(mf); break; }
					case 10: { float th=atan2(zy,zx); float rxy=native_sqrt(zx*zx+zy*zy); float rlim=ma*(1.0+mb*native_cos(mc*th)); if(rxy>rlim){ float nr=rlim*2.0-rxy; z.x=nr*native_cos(th); z.y=nr*native_sin(th); } aux.DE*=fabs(mf); break; }
					case 11: { float th=atan2(zy,zx); float rxy=native_sqrt(zx*zx+zy*zy); float rlim=ma*native_exp(-mb*th); if(rxy>rlim){ float nr=rlim*2.0-rxy; z.x=nr*native_cos(th); z.y=nr*native_sin(th); } aux.DE*=fabs(mf); break; }
					case 12: { float limy=ma+mb*native_sin(mc*zy); if(fabs(zx)>limy) z.x=copysign(limy*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; aux.DE*=fabs(mf)*(1.0+fabs(mb*mc)); break; }
					case 13: { float h1=ma+mb*native_sin(mc*zx)*native_sin(mc*zy)*native_sin(mc*zz2); if(fabs(zx)>h1) z.x=copysign(h1*2.0,zx)-zx; if(fabs(zy)>h1) z.y=copysign(h1*2.0,zy)-zy; if(fabs(zz2)>h1) z.z=copysign(h1*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
					case 14: { float h1=ma+mb*native_sin(mc*zx)*native_cos(md*zy); if(fabs(zx)>h1) z.x=copysign(h1*2.0,zx)-zx; if(fabs(zy)>h1) z.y=copysign(h1*2.0,zy)-zy; if(fabs(zz2)>h1) z.z=copysign(h1*2.0,zz2)-zz2; aux.DE*=fabs(mf)*(1.0+fabs(mb*mc)); break; }
					case 15: { float jv=ma+0.1*native_sin(mc*zx)*native_sin(mc*zy); if(fabs(zx)>jv) z.x=copysign(jv*2.0,zx)-zx; if(fabs(zy)>jv) z.y=copysign(jv*2.0,zy)-zy; aux.DE*=fabs(mf); break; }
					case 16: { float lt=ma+0.1*native_sin(mb*i); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
					case 17: { float lt=ma*(1.0+0.1*r); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
					case 18: { float cl=fabs(length(z)); float lt=ma+cl*mb; if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
					case 19: { float c1=ma,c2=-ma; if(zx>c1+mb) z.x=2.0*c1+mb*2.0-zx; if(zx<c2-mb) z.x=2.0*c2-mb*2.0-zx; if(zy>c1+mb) z.y=2.0*c1+mb*2.0-zy; if(zy<c2-mb) z.y=2.0*c2-mb*2.0-zy; aux.DE*=fabs(mf); break; }
					case 20: { float lt=ma; for(int n=0;n<3&&n<(int)mb;n++){ lt*=0.5; if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; } aux.DE*=fabs(mf); break; }
					case 21: { if(i>(int)mb){ if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; } aux.DE*=fabs(mf); break; }
					case 22: { float h=(native_sin(i*12.9898+zx*78.233)*43758.5453 - floor(native_sin(i*12.9898+zx*78.233)*43758.5453)); if(h<mc){ if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; } aux.DE*=fabs(mf)*(1.0-mc+mc*mb); break; }
					case 23: { float dt=zx*mc+zy*md+zz2*me; float lt=ma*(1.0+0.1*dt/fmax(1e-10,r)); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
					case 24: { float lt=ma+mc*zx*zx; if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; float lty=ma+mc*zy*zy; if(fabs(zy)>lty) z.y=copysign(lty*2.0,zy)-zy; aux.DE*=fabs(mf)*(1.0+2.0*fabs(mc*r)); break; }
					case 25: { float lt=ma+mb*native_sin(mc*zx); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; float lty=ma+mb*native_sin(mc*zy); if(fabs(zy)>lty) z.y=copysign(lty*2.0,zy)-zy; float ltz=ma+mb*native_sin(mc*zz2); if(fabs(zz2)>ltz) z.z=copysign(ltz*2.0,zz2)-zz2; aux.DE*=fabs(mf)*(1.0+fabs(mb*mc)); break; }
					case 26: { float rre=(zx/(ma+1e-10))*(zx/(ma+1e-10))+(zy/(mb+1e-10))*(zy/(mb+1e-10))+(zz2/(mc+1e-10))*(zz2/(mc+1e-10)); if(rre<1e-21) rre=1e-21; float m2=md*md/rre; z*=m2; aux.DE*=m2; break; }
					case 27: { float rrc=zx*zx+zy*zy; if(rrc<1e-21) rrc=1e-21; float m2=ma*ma/rrc; z.x*=m2; z.y*=m2; z.z*=m2; aux.DE*=m2; break; }
					case 28: { float rxy=native_sqrt(zx*zx+zy*zy); float rrt=(rxy-ma)*(rxy-ma)+zz2*zz2; if(rrt<1e-21) rrt=1e-21; float m2=mb*mb/rrt; z*=m2; aux.DE*=m2; break; }
					case 29: { float rrh=zx*zx+zy*zy-zz2*zz2; float ar=fabs(rrh); if(ar<1e-21) ar=1e-21; float m2=ma*ma/ar; z*=m2; aux.DE*=m2*fmax(1.0,fabs(zz2)); break; }
					case 30: { float rrp=zx*zx+zy*zy-ma*zz2; float ar=fabs(rrp); if(ar<1e-21) ar=1e-21; float m2=mb*mb/ar; z*=m2; aux.DE*=m2*native_sqrt(1.0+4.0*ma*ma); break; }
					case 31: { float mR2=ma*(1.0+0.1*native_sin(i*mc)); float fR2=mb; if(rr<mR2) z*=fR2/mR2; else if(rr<fR2) z*=fR2/rr; aux.DE*=fabs(mf)*fR2/fmax(1e-21,fmin(rr,mR2)); break; }
					case 32: { float mx=ma,my=mb,mz=mc; float rrm=fmax(zx*zx/fmax(1e-21,mx),fmax(zy*zy/fmax(1e-21,my),zz2*zz2/fmax(1e-21,mz))); float fR2=md; if(rrm<fR2){ float m2=fR2/fmax(1e-21,rrm); z*=m2; aux.DE*=m2; } break; }
					case 33: { float mR2_1=ma,f1=mb,mR2_2=mc,f2=md; if(rr<mR2_1){ z*=f1; aux.DE*=f1; } float rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mR2_2){ z*=f2; aux.DE*=f2; } break; }
					case 34: { float sm=mc; float mR2=ma,fR2=mb; float t=1.0/(1.0+native_exp(-sm*(rr-mR2))); float m2=fR2/fmax(1e-21,rr); float sf=(1.0-t)*m2+t*1.0; z*=sf; aux.DE*=sf; break; }
					case 35: { float fR2=mb; float lg=native_log(fmax(1e-21,fR2))/native_log(fmax(1e-21,rr)); z*=lg; aux.DE*=lg/(rr*native_log(fmax(1e-21,rr))); break; }
					case 36: { float fR2=mb; float ex=native_exp(fR2-rr); z*=ex; aux.DE*=ex; break; }
					case 37: { float fR2=mb; float pw=mc; float m2=pow(fmax(1e-21,fR2/rr),pw); z*=m2; aux.DE*=m2; break; }
					case 38: { float k=mc,fR2=mb; float sg=1.0/(1.0+native_exp(k*(rr-fR2))); z*=sg; aux.DE*=sg; break; }
					case 39: { float fR2=mb,sg=mc; float gs=native_exp(-(rr-fR2)*(rr-fR2)/(sg*sg+1e-21)); z*=gs; aux.DE*=gs; break; }
					case 40: { float mR2=ma,fR2=mb,f1=mc; float m2=(rr<mR2)?f1:((rr<fR2)?fR2/rr:1.0); z*=m2; aux.DE*=m2; break; }
					case 41: { float b1=ma,f1=mb,b2=mc,f2=md,b3=me,f3=mff; float m2=(rr<b1)?f1:((rr<b2)?f2:((rr<b3)?f3:1.0)); z*=m2; aux.DE*=m2; break; }
					case 42: { float fR2=mb; if(rr<fR2){ float m2=1.0/fmax(1e-21,rr); z.x=ma+fR2*(zx-ma)*m2; z.y=ma+fR2*(zy-ma)*m2; z.z=ma+fR2*(zz2-ma)*m2; aux.DE*=fR2*m2; } break; }
					case 43: { float fR2=mb; if(rr<fR2){ float den=mc*zx+md+1e-21; z.x=(ma*zx+mb)/(den); z.y=zy/fmax(1e-10,fabs(den)); z.z=zz2/fmax(1e-10,fabs(den)); aux.DE*=fabs(ma*md-mb*mc)/(den*den); } break; }
					case 44: { float fR2=mb; if(rr<fR2){ float qn=rr; if(qn<1e-21) qn=1e-21; float m2=fR2/qn; z*=m2; aux.DE*=m2; } break; }
					case 45: { float dm=fmax(1e-10,acosh(fmax(1.0,r))); float dmax=ma; if(dm<dmax){ float sc=dmax/dm; z*=sc; aux.DE*=sc*dmax/(dm*sinh(dm)+1e-21); } break; }
					case 46: { float ox=ma,oy=mb,oz=mc; float rrc=(zx-ox)*(zx-ox)+(zy-oy)*(zy-oy)+(zz2-oz)*(zz2-oz); if(rrc<1e-21) rrc=1e-21; float fR2=md; if(rrc<fR2){ float m2=fR2/rrc; z*=m2; aux.DE*=m2; } break; }
					case 47: { float th=ma*M_PI_F/180.0; float cs=native_cos(th),sn=native_sin(th); float rx=zx*cs-zy*sn; float ry=zx*sn+zy*cs; float rrc=rx*rx+ry*ry+zz2*zz2; if(rrc<1e-21) rrc=1e-21; float fR2=mb; if(rrc<fR2){ float m2=fR2/rrc; z*=m2; aux.DE*=m2; } break; }
					case 48: { float fR2=ma*(1.0+0.1*native_sin(i*mb)); float mR2=mc; if(rr<mR2){ z*=fR2/mR2; aux.DE*=fR2/mR2; } else if(rr<fR2){ z*=fR2/rr; aux.DE*=fR2/rr; } break; }
					case 49: { float mR2=ma,fR2=mb; float cf=(rr<mR2)?mc:((rr<fR2)?md:0.0); aux.color+=cf; break; }
					case 50: { aux.color+=native_log(fmax(1e-21,aux.DE))*ma; break; }
					case 51: { z.x*=ma; z.y*=mb; z.z*=mc; aux.DE*=fmax(fabs(ma),fmax(fabs(mb),fabs(mc))); break; }
					case 52: { float sc=ma+mb*native_sin(i*mc); z*=sc; aux.DE*=fabs(sc); break; }
					case 53: { float sc=ma*native_exp(-i*mb); z*=sc; aux.DE*=fabs(sc); break; }
					case 54: { float sc=ma/(1.0+native_log(1.0+i)); z*=sc; aux.DE*=fabs(sc); break; }
					case 55: { float p=fmax(0.01,mb); float sc=ma/fmax(1e-10,pow(fmax(1.0,(float)i),p)); z*=sc; aux.DE*=fabs(sc); break; }
					case 56: { float f0=1,f1=1; for(int n=0;n<fmin((float)i,20.0);n++){float t=f1;f1=f0+f1;f0=t;} float sc=ma/fmax(1.0,f1); z*=sc; aux.DE*=fabs(sc); break; }
					case 57: { float ns=native_sin(i*12.9898+zx*78.233)*43758.5453; ns=ns-floor(ns); float sc=ma+ns*mb; z*=sc; aux.DE*=fabs(sc); break; }
					case 58: { float jv=native_sin(i*mb)*native_cos(i*mc); float sc=ma+0.1*fabs(jv); z*=sc; aux.DE*=fabs(sc); break; }
					case 59: { float sc=ma*(1.0+0.1*r); z*=sc; aux.DE*=fabs(sc)*(1.0+0.1*r); break; }
					case 60: { float sc=ma+0.1*native_sin(i*mb); z*=sc; aux.DE*=fabs(sc); break; }
					case 61: { float sc=ma+0.1*mf; z*=sc; aux.DE*=fabs(sc)*1.1; break; }
					case 62: { float sc=(zx>0)?ma:mb; z*=sc; aux.DE*=fmax(fabs(ma),fabs(mb)); break; }
					case 63: { float th=atan2(zy,zx); float sc=ma+mb*native_cos(mc*th); z*=sc; aux.DE*=fabs(sc); break; }
					case 64: { float th=atan2(native_sqrt(zx*zx+zy*zy),zz2); float ph=atan2(zy,zx); float sc=ma+mb*native_cos(mc*th)*native_sin(md*ph); z*=sc; aux.DE*=fabs(sc); break; }
					case 65: { float off=ma+0.1*native_sin(i*mb); z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf); break; }
					case 66: { z.x+=ma; z.y+=mb; z.z+=mc; aux.DE*=fabs(mf); break; }
					case 67: { float cl=length(z); z.x+=cl*ma; z.y+=cl*ma; z.z+=cl*ma; aux.DE*=fabs(mf); break; }
					case 68: { z.x+=zx*0.1*ma; z.y+=zy*0.1*ma; z.z+=zz2*0.1*ma; aux.DE*=fabs(mf); break; }
					case 69: { float ns=native_sin(zx*ma+zy*mb+zz2*mc)*md; z.x+=ns; z.y+=ns; z.z+=ns; aux.DE*=fabs(mf); break; }
					case 70: { float off=ma+0.1*native_sin(i*mb); z.x+=off; z.y+=off*0.5; z.z+=off*0.25; aux.DE*=fabs(mf); break; }
					case 71: { float off=ma+0.1*mf; z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf); break; }
					case 72: { float off=(rr<ma)?mb:mc; z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf); break; }
					case 73: { float off=ma*(1.0+0.1*r); z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf); break; }
					case 74: { float th=i*ma; float spr=mb; z.x+=spr*native_cos(th); z.y+=spr*native_sin(th); aux.DE*=fabs(mf); break; }
					case 75: { z.x+=ma*native_sin(mb*i); z.y+=mc*native_sin(md*i); z.z+=me*native_sin(mff*i); aux.DE*=fabs(mf); break; }
					case 76: { float ga=2.39996322973; float th=i*ga; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx; z.y=ny; aux.DE*=fabs(mf); break; }
					case 77: { float hth=ma*M_PI_F/360.0; float ax=mb,ay=mc,az=md; float nm=native_sqrt(ax*ax+ay*ay+az*az+1e-21); ax/=nm;ay/=nm;az/=nm; float cq=native_cos(hth),sq=native_sin(hth); float qw=cq,qx=sq*ax,qy=sq*ay,qz=sq*az; float nx=zx*(1-2*(qy*qy+qz*qz))+zy*2*(qx*qy-qw*qz)+zz2*2*(qx*qz+qw*qy); float ny=zx*2*(qx*qy+qw*qz)+zy*(1-2*(qx*qx+qz*qz))+zz2*2*(qy*qz-qw*qx); float nz=zx*2*(qx*qz-qw*qy)+zy*2*(qy*qz+qw*qx)+zz2*(1-2*(qx*qx+qy*qy)); z.x=nx;z.y=ny;z.z=nz; aux.DE*=fabs(mf); break; }
					case 78: { float th=ma*M_PI_F/180.0; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx; z.y=ny; float ph=mb*M_PI_F/180.0; float cp=native_cos(ph),sp=native_sin(ph); float nxz=z.x*cp-zz2*sp; float nz=z.x*sp+zz2*cp; z.x=nxz; z.z=nz; aux.DE*=fabs(mf); break; }
					case 79: { float th=ma*M_PI_F/180.0; float cs=native_cos(th),sn=native_sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; float ph=mb*M_PI_F/180.0; cs=native_cos(ph); sn=native_sin(ph); float ty=z.y*cs-zz2*sn; z.z=z.y*sn+zz2*cs; z.y=ty; float ps=mc*M_PI_F/180.0; cs=native_cos(ps);sn=native_sin(ps); float tx=z.x*cs-z.z*sn; z.z=z.x*sn+z.z*cs; z.x=tx; aux.DE*=fabs(mf); break; }
					case 80: { float v=ma; float gm=1.0/native_sqrt(fmax(1e-10,1.0-v*v)); z.x=gm*(zx-v*zz2); z.z=gm*(zz2-v*zx); aux.DE*=fabs(mf)*gm; break; }
					case 81: { z.x+=ma; z.y+=mb*native_sin(mc*zz2); aux.DE*=fabs(mf); break; }
					case 82: { float s=ma; float th=mb*M_PI_F/180.0; float cs=native_cos(th),sn=native_sin(th); z.x=s*(zx*cs-zy*sn); z.y=s*(zx*sn+zy*cs); z.z*=s; aux.DE*=fabs(s)*fabs(mf); break; }
					case 83: { float N=fmax(2.0,ma); float th=2.0*M_PI_F/N; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx; z.y=ny; aux.DE*=fabs(mf); break; }
					case 84: { float ax=native_sin(i*ma),ay=native_cos(i*ma); float nm=native_sqrt(ax*ax+ay*ay+1e-21); ax/=nm; ay/=nm; float th=mb*M_PI_F/180.0; float cs=native_cos(th),sn=native_sin(th); float d=zx*ax+zy*ay; float px=zx-d*ax,py=zy-d*ay; float rx=px*cs-py*sn+d*ax,ry=px*sn+py*cs+d*ay; z.x=rx;z.y=ry; aux.DE*=fabs(mf); break; }
					case 85: { float ns=native_sin(i*12.9898+78.233)*43758.5453; ns=ns-floor(ns); float th=ns*2.0*M_PI_F*ma; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
					case 86: { float th=ma+mb*i; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
					case 87: { float th=ma+mf; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
					case 88: { if(zx>0){ float th=ma*M_PI_F/180.0; float cs=native_cos(th),sn=native_sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; } else { float th=mb*M_PI_F/180.0; float cs=native_cos(th),sn=native_sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; } aux.DE*=fabs(mf); break; }
					case 89: { float th=ma*(1.0+0.1*r); float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
					case 90: { float ph=atan2(zy,zx); float th=ma+mb*native_cos(mc*ph); float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
					case 91: { float N=fmax(2.0,ma); float th=atan2(zy,zx); float sector=2.0*M_PI_F/N; th=fmod(th+sector*0.5+100.0*sector,sector)-sector*0.5; float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(th); z.y=rxy*native_sin(th); aux.DE*=fabs(mf); break; }
					case 92: { float nx=fabs(zx); float ny=fabs(zy); float nz2=fabs(zz2); if(ma>0) z.x=nx; if(mb>0) z.y=ny; if(mc>0) z.z=nz2; aux.DE*=fabs(mf); break; }
					case 93: { z.x+=ma*zy; z.y+=mb*zz2; aux.DE*=fabs(mf)*native_sqrt(1.0+ma*ma+mb*mb); break; }
					case 94: { float rxy=native_sqrt(zx*zx+zy*zy); float th=atan2(zy,zx)+ma*zz2; z.x=rxy*native_cos(th); z.y=rxy*native_sin(th); aux.DE*=fabs(mf)*native_sqrt(1.0+ma*ma*rxy*rxy); break; }
					case 95: { float cv=ma; float rxy=native_sqrt(zx*zx+zy*zy); float th=atan2(zy,zx)+cv*rxy; z.x=rxy*native_cos(th); z.y=rxy*native_sin(th); aux.DE*=fabs(mf)*(1.0+cv*rxy); break; }
					case 96: { float tf=ma; z.x*=(1.0-tf*zz2); z.y*=(1.0-tf*zz2); aux.DE*=fabs(mf)*(1.0-tf*zz2); break; }
					case 97: { float g=ma; float th=atan2(zy,zx)+g*native_log(fmax(1e-10,native_sqrt(zx*zx+zy*zy))); float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(th); z.y=rxy*native_sin(th); aux.DE*=fabs(mf)*g; break; }
					case 98: { float th=ma*native_exp(i*mb); float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
					case 99: { float th=ma*native_log(1.0+i); float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
					case 100: { float p=mb; float th=ma*pow(fmax(1.0,(float)i),p); float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
					case 101: { float w=ma; float rr4=rr+w*w; if(rr4<1e-21) rr4=1e-21; float sc=mf; z.x=zx*sc+w*0.1; z.y=zy*sc; z.z=zz2*sc; aux.DE*=fabs(sc); break; }
					case 102: { float w=ma,v=mb; float rr5=rr+w*w+v*v; if(rr5<1e-21) rr5=1e-21; float sc=mf; z*=sc; z.x+=w*0.05; z.y+=v*0.05; aux.DE*=fabs(sc); break; }
					case 103: { float w=ma*native_sin(mb*i); z.x+=w*0.1; aux.DE*=fabs(mf); break; }
					case 104: { float th4=ma*M_PI_F/180.0; float cs=native_cos(th4),sn=native_sin(th4); float nw=zz2*sn; z.z=zz2*cs; z.x+=nw*0.1; aux.DE*=fabs(mf); break; }
					case 105: { float cx=ma,cy=mb,cz=mc; z.x+=cx*mf; z.y+=cy*mf; z.z+=cz*mf; aux.DE*=fabs(mf); break; }
					case 106: { float qw=ma,qx=zx,qy=zy,qz=zz2; float nm=native_sqrt(qw*qw+qx*qx+qy*qy+qz*qz+1e-21); z.x=qx/nm*mf; z.y=qy/nm*mf; z.z=qz/nm*mf; aux.DE*=fabs(mf)/nm; break; }
					case 107: { float q1w=ma,q2w=mb; float nm1=native_sqrt(zx*zx+zy*zy+q1w*q1w+1e-21); float nm2=native_sqrt(zz2*zz2+q2w*q2w+1e-21); z.x*=nm2/(nm1+1e-21); z.y*=nm2/(nm1+1e-21); aux.DE*=fabs(mf)*nm2/(nm1+1e-21); break; }
					case 108: { float d4=native_sqrt(rr+ma*ma); float td=tanh(d4); z*=td/fmax(1e-10,d4); float ch=cosh(d4); aux.DE*=fabs(mf)/(ch*ch+1e-21); break; }
					case 109: { float rr4=rr+ma*ma; float nm4=native_sqrt(rr4+1e-21); z*=1.0/nm4; aux.DE*=fabs(mf)/nm4; break; }
					case 110: { float rxy=native_sqrt(zx*zx+zy*zy+1e-21); z.x=(rxy-ma)*native_cos(atan2(zy,zx)); z.y=(rxy-ma)*native_sin(atan2(zy,zx)); aux.DE*=fabs(mf)*rxy; break; }
					case 111: { float R=ma,rr2=mb; float th=atan2(zy,zx); z.x=(R+rr2*native_cos(th))*native_cos(mc*i); z.y=(R+rr2*native_cos(th))*native_sin(mc*i); z.z=rr2*native_sin(th); aux.DE*=fabs(mf)*R; break; }
					case 112: { float th=ma*M_PI_F/180.0; float ph=mb*M_PI_F/180.0; float cs1=native_cos(th),sn1=native_sin(th),cs2=native_cos(ph); float nx=zx*cs1-zy*sn1; float ny=zx*sn1+zy*cs1; float nz2=zz2*cs2; z.x=nx;z.y=ny;z.z=nz2; aux.DE*=fabs(mf); break; }
					case 113: { float ga=2.39996322973; float th=i*ga; float r4=native_sqrt(rr+1e-21); z.x=r4*native_cos(th)*native_cos(ma*i); z.y=r4*native_sin(th)*native_cos(ma*i); z.z=r4*native_sin(ma*i); aux.DE*=fabs(mf); break; }
					case 114: { float D=ma; float sc=pow(2.0,D); z*=sc/fmax(1e-10,r); aux.DE*=sc/fmax(1e-10,r); break; }
					case 115: { float h=(native_sin(i*12.9898+78.233)*43758.5453 - floor(native_sin(i*12.9898+78.233)*43758.5453)); if(h<ma){ z.x=-z.x; z.y=-z.y; } aux.DE*=fabs(mf); break; }
					case 116: { float w=ma+0.1*native_sin(i*mb); z.x+=w*0.1; aux.DE*=fabs(mf); break; }
					case 117: { z.x+=0.1*zx*ma; z.y+=0.1*zy*ma; z.z+=0.1*zz2*ma; aux.DE*=fabs(mf)*1.1; break; }
					case 118: { float ns=native_sin(zx*ma+i*mb)*native_cos(zy*mc); z.x+=ns*0.1*md; z.y+=ns*0.1*md; aux.DE*=fabs(mf); break; }
					case 119: { float jv=native_sin(i*ma)*native_cos(i*mb); float sc=mf+0.1*jv; z*=sc; aux.DE*=fabs(sc); break; }
					case 120: { float sc1=ma,sc2=mb; z*=sc1; float rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2>1e-21){ z*=sc2/native_sqrt(rr2); } aux.DE*=fmax(fabs(sc1),fabs(sc2)); break; }
					case 121: { float h=(native_sin(i*12.9898+78.233)*43758.5453 - floor(native_sin(i*12.9898+78.233)*43758.5453)); float w=(h<ma)?mb:mc; z.x+=w*0.1; aux.DE*=fabs(mf); break; }
					case 122: { float h=(native_sin(i*12.9898+zx*78.233)*43758.5453 - floor(native_sin(i*12.9898+zx*78.233)*43758.5453)); float sc=ma+h*mb*0.1; z*=sc; aux.DE*=fabs(sc); break; }
					case 123: { float p=ma; z.x=fmod(zx+p*0.5,p)-p*0.5; z.y=fmod(zy+p*0.5,p)-p*0.5; z.z=fmod(zz2+p*0.5,p)-p*0.5; aux.DE*=fabs(mf)/fmax(0.01,p); break; }
					case 124: { float fR2=ma; if(rr<fR2){ float m2=fR2/fmax(1e-21,rr); z*=m2; aux.DE*=m2; } break; }
					case 125: { if(fabs(zx)>ma) z.x=copysign(ma,zx); if(fabs(zy)>ma) z.y=copysign(ma,zy); if(fabs(zz2)>ma) z.z=copysign(ma,zz2); aux.DE*=fabs(mf); break; }
					case 126: { float dx=fabs(z.x-zx),dy=fabs(z.y-zy),dz=fabs(z.z-zz2); aux.color+=ma*dx+mb*dy+mc*dz; break; }
					case 127: { float mR2=ma,fR2=mb; float t=(rr-mR2)/(fR2-mR2+1e-21); t=fmax(0.0,fmin(1.0,t)); aux.color+=t*mc; break; }
					case 128: { aux.color+=native_log(fabs(mf)+1e-21)*ma; break; }
					case 129: { float th=atan2(zy,zx); aux.color+=fabs(th)*ma; break; }
					case 130: { float td=native_sqrt((zx-ma)*(zx-ma)+(zy-mb)*(zy-mb)+(zz2-mc)*(zz2-mc))-md; aux.color+=fmax(0.0,1.0-fabs(td))*me; break; }
					case 131: { float ax1=ma,ay1=mb,bx1=mc,by1=md; float dx=bx1-ax1,dy=by1-ay1; float t=((zx-ax1)*dx+(zy-ay1)*dy)/(dx*dx+dy*dy+1e-21); t=fmax(0.0,fmin(1.0,t)); float px=ax1+t*dx,py=ay1+t*dy; float dd=native_sqrt((zx-px)*(zx-px)+(zy-py)*(zy-py)); aux.color+=fmax(0.0,1.0-dd)*me; break; }
					case 132: { float dd=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.color+=fmax(0.0,1.0-dd*ma)*mb; break; }
					case 133: { float nx=ma,ny=mb,nz2=mc; float nm=native_sqrt(nx*nx+ny*ny+nz2*nz2+1e-21); float dd=fabs(zx*nx/nm+zy*ny/nm+zz2*nz2/nm-md); aux.color+=fmax(0.0,1.0-dd)*me; break; }
					case 134: { float R=ma,rr2=mb; float rxy=native_sqrt(zx*zx+zy*zy+1e-21); float td=(rxy-R)*(rxy-R)+zz2*zz2-rr2*rr2; aux.color+=fmax(0.0,1.0-fabs(td))*mc; break; }
					case 135: { float jv=native_sin(zx*ma)*native_sin(zy*mb); aux.color+=fabs(jv)*mc; break; }
					case 136: { aux.color+=(float)i/fmax(1.0,ma)*mb; break; }
					case 137: { aux.color+=native_log(fmax(1e-21,aux.DE))*ma; break; }
					case 138: { float spd=native_sqrt((z.x-zx)*(z.x-zx)+(z.y-zy)*(z.y-zy)+(z.z-zz2)*(z.z-zz2)); aux.color+=spd*ma; break; }
					case 139: { aux.color+=r*ma*0.01; break; }
					case 140: { float th=atan2(zy,zx); aux.color+=th*ma; break; }
					case 141: { aux.color+=r*ma; break; }
					case 142: { float p=fmax(0.01,ma); float cx2=floor(zx/p),cy2=floor(zy/p),cz2=floor(zz2/p); float h=(native_sin(cx2*12.9898+cy2*78.233+cz2*37.719)*43758.5453 - floor(native_sin(cx2*12.9898+cy2*78.233+cz2*37.719)*43758.5453)); aux.color+=h*mb; break; }
					case 143: { aux.color+=native_sin(i*ma+mb)*mc; break; }
					case 144: { aux.color=0.9*aux.color+0.1*ma*r; break; }
					case 145: { float ns=native_sin(zx*ma+zy*mb+zz2*mc)*md; aux.color+=ns; break; }
					case 146: { float cl=length(z); aux.color+=cl*ma; break; }
					case 147: { aux.color+=native_sqrt(zx*zx+zy*zy)*ma; break; }
					case 148: { float fc=fabs(z.x-zx)*0.3+r*0.3+fabs(atan2(zy,zx))*0.4; aux.color+=fc*ma; break; }
					case 149: { float ns=native_sin(zx*ma+zy*mb)*native_cos(zz2*mc+i*md); aux.color+=fabs(ns)*me; break; }
					case 150: { float jv=native_sin(zx*ma)*native_sin(zy*mb)*native_sin(zz2*mc); aux.color+=fabs(jv)*md; break; }
					case 151: { float eps=ma*0.001; float dx=(native_sqrt((zx+eps)*(zx+eps)+zy*zy+zz2*zz2)-native_sqrt((zx-eps)*(zx-eps)+zy*zy+zz2*zz2))/(2.0*eps); aux.DE=fmax(1e-21,fabs(dx)*aux.DE); break; }
					case 152: { float de_num=r*0.5; float de_safe=fmin(aux.DE,de_num); aux.DE=de_safe; break; }
					case 153: { aux.DE=0.9*aux.DE+0.1*r*ma; break; }
					case 154: { float prev=aux.DE; aux.DE=prev+0.5*(prev-ma); break; }
					case 155: { float spd=r*0.01; aux.DE=aux.DE*(1.0+0.5*spd); break; }
					case 156: { float tr=ma; aux.DE=fmin(aux.DE,tr); break; }
					case 157: { float j11=1.0+ma*native_cos(zx),j22=1.0+mb*native_cos(zy),j33=1.0+mc*native_cos(zz2); aux.DE*=fmax(fabs(j11),fmax(fabs(j22),fabs(j33))); break; }
					case 158: { float h=ma*native_sin(zx)*native_sin(zy)*native_sin(zz2); aux.DE*=(1.0+h*0.5); break; }
					case 159: { aux.DE=native_log(fmax(1e-21,aux.DE))*ma+mb; break; }
					case 160: { aux.DE=(native_exp(fmin(10.0,aux.DE))-1.0)*ma; break; }
					case 161: { float p=ma; aux.DE=pow(fmax(1e-21,aux.DE),p); break; }
					case 162: { float k=ma,de0=mb; aux.DE=1.0/(1.0+native_exp(-k*(aux.DE-de0))); break; }
					case 163: { float de0=ma,sg=mb; aux.DE=native_exp(-(aux.DE-de0)*(aux.DE-de0)/(sg*sg+1e-21)); break; }
					case 164: { float th2=ma; aux.DE=(aux.DE>th2)?mb:mc; break; }
					case 165: { float b1=ma,d1=mb,b2=mc,d2=md; aux.DE=(aux.DE<b1)?d1:((aux.DE<b2)?d2:aux.DE); break; }
					case 166: { float ns=native_sin(zx*ma+zy*mb+zz2*mc)*md; aux.DE+=ns; aux.DE=fmax(1e-21,aux.DE); break; }
					case 167: { float jv=fabs(native_sin(zx*ma)*native_sin(zy*mb)); aux.DE*=(1.0+0.1*jv); break; }
					case 168: { aux.DE*=(1.0+0.1*native_sin(i*ma)); break; }
					case 169: { aux.DE=0.9*aux.DE+0.1*ma; break; }
					case 170: { float ns=native_sin(zx*ma+zy*mb)*native_cos(zz2*mc+i*md); aux.DE*=(1.0+me*ns); break; }
					case 171: { float fn=native_sin(zx*ma*10.0)*native_sin(zy*mb*10.0)*native_sin(zz2*mc*10.0); aux.DE*=(1.0+0.1*fn); break; }
					case 172: { float spd=r*0.01; aux.DE/=(1.0+spd); break; }
					case 173: { aux.DE*=fabs(mf); break; }
					case 174: { if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; float rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb*mb) z*=mc*mc/(rr2+1e-21); aux.DE*=fabs(mf); break; }
					case 175: { float sc=ma+mb*native_sin(i*mc); z*=sc; if(fabs(z.x)>md) z.x=copysign(md*2.0,z.x)-z.x; aux.DE*=fabs(sc); break; }
					case 176: { float th=ma*M_PI_F/180.0; float cs=native_cos(th),sn=native_sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; if(fabs(z.x)>mb) z.x=copysign(mb*2.0,z.x)-z.x; aux.DE*=fabs(mf); break; }
					case 177: { if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; float rr2=z.x*z.x+z.y*z.y+z.z*z.z; float fR2=mb; if(rr2<mc) z*=fR2/mc; else if(rr2<fR2) z*=fR2/rr2; z*=md; z.x+=me; z.y+=mff; z.z+=mg; aux.DE*=fabs(md); break; }
					case 178: { float th=i*2.39996322973; float cs=native_cos(th),sn=native_sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; if(fabs(z.x)>ma) z.x=copysign(ma*2.0,z.x)-z.x; z*=mb; aux.DE*=fabs(mb); break; }
					case 179: { float rxy=native_sqrt(zx*zx+zy*zy); if(rxy>ma){ float th=atan2(zy,zx); z.x=(ma*2.0-rxy)*native_cos(th); z.y=(ma*2.0-rxy)*native_sin(th); } float rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb) z*=mc/rr2; aux.DE*=fabs(mf); break; }
					case 180: { z.x+=ma*native_sin(mb*zy); z.y+=mc*native_sin(md*zz2); z.z+=me*native_sin(mff*zx); aux.DE*=fabs(mf)*(1.0+fabs(ma*mb)+fabs(mc*md)+fabs(me*mff)); break; }
					case 181: { if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; aux.color+=mb*fabs(z.x-zx); aux.DE*=fabs(mf); break; }
					case 182: { float rr2=rr; float mR2=ma*ma; float fR2=mb*mb; if(rr2<mR2){ z*=fR2/mR2; aux.DE*=fR2/mR2; } else if(rr2<fR2){ z*=fR2/rr2; aux.DE*=fR2/rr2; } aux.color+=mc*native_log(fmax(1e-21,rr2/(mR2+1e-21))); break; }
					case 183: { float sc=ma; z*=sc; aux.DE*=fabs(sc); z.x+=mb; z.y+=mc; z.z+=md; float th=me*M_PI_F/180.0; float cs=native_cos(th),sn=native_sin(th); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; break; }
					case 184: { float lt=ma*(1.0+mb*r/fmax(1e-10,native_sqrt(rr))); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
					case 185: { float mR2=ma*ma; float fR2=mb*mb; float sm=mc; float t=1.0/(1.0+native_exp(-sm*(rr-mR2))); float m2=fR2/fmax(1e-21,rr); float sf=(1.0-t)*m2+t; z*=sf; aux.DE*=sf; z*=md; z.x+=me; aux.DE*=fabs(md); break; }
					case 186: { float N=fmax(2.0,ma); float th=atan2(zy,zx); float sector=2.0*M_PI_F/N; th=fmod(th+sector*0.5+100.0*sector,sector)-sector*0.5; float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(th); z.y=rxy*native_sin(th); if(fabs(z.x)>mb) z.x=copysign(mb*2.0,z.x)-z.x; aux.DE*=fabs(mf); break; }
					case 187: { z.x=fabs(zx); z.y=fabs(zy); z.z=fabs(zz2); if(fabs(z.x)>ma) z.x=ma*2.0-z.x; if(fabs(z.y)>ma) z.y=ma*2.0-z.y; if(fabs(z.z)>ma) z.z=ma*2.0-z.z; aux.DE*=fabs(mf); break; }
					case 188: { if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; float rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb) z*=mc/rr2; else if(rr2<mc) z*=mc/rr2; float th=md*M_PI_F/180.0; float cs=native_cos(th),sn=native_sin(th); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; z*=me; z.x+=mff; aux.DE*=fabs(me); break; }
					case 189: { float rxy=native_sqrt(zx*zx+zy*zy); float th=atan2(zy,zx)+ma*native_sin(mb*zz2); z.x=rxy*native_cos(th); z.y=rxy*native_sin(th); if(fabs(z.x)>mc) z.x=copysign(mc*2.0,z.x)-z.x; aux.DE*=fabs(mf)*(1.0+fabs(ma*mb)); break; }
					case 190: { float pw=ma; float rp=pow(fmax(1e-10,r),pw-1.0); float th=atan2(zy,zx)*pw; float ph=asin(zz2/fmax(1e-10,r))*pw; z.x=rp*native_cos(ph)*native_cos(th); z.y=rp*native_cos(ph)*native_sin(th); z.z=rp*native_sin(ph); aux.DE*=pw*rp; break; }
					case 191: { z.x+=ma*native_sin(mb*i)*native_cos(mc*zy); z.y+=md*native_cos(me*i)*native_sin(mff*zx); z.z+=mg*native_sin(mh*i); aux.DE*=fabs(mf); break; }
					case 192: { float sc=mf; z*=sc; float lt=ma; if(fabs(z.x)>lt) z.x=copysign(lt*2.0,z.x)-z.x; if(fabs(z.y)>lt) z.y=copysign(lt*2.0,z.y)-z.y; if(fabs(z.z)>lt) z.z=copysign(lt*2.0,z.z)-z.z; float rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb) z*=mc/rr2; aux.DE*=fabs(sc); break; }
					case 193: { float p=fmax(0.01,ma); z.x=fmod(zx+p*0.5,p)-p*0.5; z.y=fmod(zy+p*0.5,p)-p*0.5; z.z=fmod(zz2+p*0.5,p)-p*0.5; if(fabs(z.x)>mb) z.x=copysign(mb*2.0,z.x)-z.x; aux.DE*=fabs(mf)/fmax(0.01,p); break; }
					case 194: { float ex=native_exp(-ma*rr); z*=(1.0+mb*ex); aux.DE*=(1.0+mb*ex); break; }
					case 195: { float sg=1.0/(1.0+native_exp(-ma*(r-mb))); z*=(1.0+mc*sg); aux.DE*=(1.0+mc*sg); break; }
					case 196: { z.x+=ma*native_sin(mb*zx)*native_cos(mc*zy); z.y+=md*native_cos(me*zy)*native_sin(mff*zz2); z.z+=mg*native_sin(mh*zz2)*native_cos(ma*zx); aux.DE*=fabs(mf); break; }
					case 197: { float th1=ma*M_PI_F/180.0+mb*native_sin(i*mc); float cs1=native_cos(th1),sn1=native_sin(th1); z.x=zx*cs1-zy*sn1; z.y=zx*sn1+zy*cs1; if(fabs(z.x)>md) z.x=copysign(md*2.0,z.x)-z.x; z*=me; aux.DE*=fabs(me); break; }
					case 198: { float rr2=rr; float fR2=ma*ma; if(rr2<fR2){ float m2=fR2/fmax(1e-21,rr2); z*=m2; aux.DE*=m2; } float th=mb*M_PI_F/180.0; float cs=native_cos(th),sn=native_sin(th); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; z*=mc; z.x+=md; aux.DE*=fabs(mc); break; }
					case 199: { float lt=ma+mb*native_sin(mc*i)*native_cos(md*r); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; float rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<me*me) z*=mff*mff/(rr2+1e-21); z*=mg; aux.DE*=fabs(mg); break; }
					case 200: { if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; float rr2=z.x*z.x+z.y*z.y+z.z*z.z; float fR2=mb*mb; float mR2=mc*mc; if(rr2<mR2) z*=fR2/mR2; else if(rr2<fR2) z*=fR2/rr2; z*=md; z.x+=me; z.y+=mff; z.z+=mg; float th=mh*M_PI_F/180.0; float cs=native_cos(th),sn=native_sin(th); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; aux.DE*=fabs(md); break; }
			}
			}

				// v7.9 — Warp Distortion system (per-section iteration range)
				if (i >= mut->wdIterStart && i < mut->wdIterStop && mut->warpDistType != 0)
				{
					float wf = mut->wdFactor;
					float wa = mut->wdParamA, wb = mut->wdParamB, wc = mut->wdParamC, wd = mut->wdParamD;
					float wfq = mut->wdFreq, wam = mut->wdAmp;
					float wsc = mut->wdScale, wph = mut->wdPhase * M_PI_F / 180.0;
					float zx = z.x, zy = z.y, zz2 = z.z;
					float r = native_sqrt(zx*zx + zy*zy + zz2*zz2 + 1e-21);
					switch(mut->warpDistType)
					{
						case 1: { z.x += wf*wam*native_sin(wfq*zy + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq*native_cos(wfq*zy + wph))); break; }
						case 2: { z.y += wf*wam*native_sin(wfq*zz2 + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq*native_cos(wfq*zz2 + wph))); break; }
						case 3: { z.z += wf*wam*native_sin(wfq*zx + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq*native_cos(wfq*zx + wph))); break; }
						case 4: { z.x += wf*wam*native_sin(wfq*zy + wph); z.y += wf*wam*native_sin(wfq*zz2 + wph); z.z += wf*wam*native_sin(wfq*zx + wph); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq)); break; }
						case 5: { z.x += wf*wam*native_cos(wfq*zy + wph)*native_sin(wfq*zz2); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 6: { float ph = atan2(zy, zx); z.x += wf*wam*native_sin(wfq*ph + wph); z.y += wf*wam*native_cos(wfq*ph + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 7: { float ph = atan2(zy, zx); float th = acos(zz2/r); z.x += wf*wam*native_sin(wfq*th + wph)*native_cos(ph); z.y += wf*wam*native_sin(wfq*th + wph)*native_sin(ph); z.z += wf*wam*native_cos(wfq*th + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 8: { z.x += wf*wam*native_sin(wfq*zy + wph)*native_cos(wfq*zz2); z.y += wf*wam*native_sin(wfq*zz2 + wph)*native_cos(wfq*zx); z.z += wf*wam*native_sin(wfq*zx + wph)*native_cos(wfq*zy); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq)); break; }
						case 9: { z.x += wf*wam*native_sin(wfq*zx + wph); z.y += wf*wb*native_sin(wfq*zy + wph); z.z += wf*wc*native_sin(wfq*zz2 + wph); aux.DE *= (1.0 + fabs(wf*(wam+wb+wc)*wfq/3.0)); break; }
						case 10: { float d = wf*wam*native_sin(wfq*r + wph); z.x += d*zx/r; z.y += d*zy/r; z.z += d*zz2/r; aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 11: { z.x += wf*wam*native_sin(wfq*native_sin(wa*zy) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 12: { z.y += wf*wam*native_sin(wfq*native_cos(wa*zz2) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 13: { z.z += wf*wam*native_cos(wfq*native_sin(wa*zx) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 14: { float d1 = native_sin(wfq*zx+wph); float d2 = native_sin(wa*zy+wb); z.x += wf*wam*native_sin(wfq*d1+d2); z.y += wf*wam*native_cos(wa*d1-d2); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq)); break; }
						case 15: { z.x += wf*wam*native_sin(wfq*(zx*zy) + wph); z.y += wf*wam*native_cos(wfq*(zy*zz2) + wph); z.z += wf*wam*native_sin(wfq*(zz2*zx) + wph); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq)); break; }
						case 16: { float n1 = native_sin(wfq*zx+wa*zy); float n2 = native_sin(wa*zy+wb*zz2); z.x += wf*wam*native_sin(wfq*n1+wph); z.y += wf*wam*native_sin(wfq*n2+wph); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq)); break; }
						case 17: { float n1 = native_cos(wfq*zx)*native_sin(wa*zy); float n2 = native_cos(wa*zy)*native_sin(wb*zz2); float n3 = native_cos(wb*zz2)*native_sin(wfq*zx); z.x += wf*wam*n1; z.y += wf*wam*n2; z.z += wf*wam*n3; aux.DE *= (1.0 + 3.0*fabs(wf*wam)); break; }
						case 18: { z.x += wf*wam*native_sin(wfq*zy*zz2/(r+1e-21) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 19: { float t = wfq*r+wph; z.x += wf*wam*native_sin(t)*native_cos(wa*zy); z.y += wf*wam*native_cos(t)*native_sin(wa*zz2); z.z += wf*wam*native_sin(t)*native_cos(wa*zx); aux.DE *= (1.0 + 3.0*fabs(wf*wam)); break; }
						case 20: { float q = native_sin(wfq*zx+wph)+native_sin(wa*zy+wb)+native_sin(wc*zz2+wd); z.x += wf*wam*native_sin(q); z.y += wf*wam*native_cos(q); z.z += wf*wam*native_sin(q+M_PI_F*0.5); aux.DE *= (1.0 + 3.0*fabs(wf*wam)); break; }
						case 21: { { float v=0; for(int o=0;o<4;o++){float f=wfq*native_pow(2.0,o); v+=native_sin(f*zx+wph)*native_cos(f*zy)/native_pow(2.0,o);} z.x+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
						case 22: { { float v=0; for(int o=0;o<4;o++){float f=wfq*native_pow(2.0,o); v+=native_sin(f*zy+wph)*native_cos(f*zz2)/native_pow(2.0,o);} z.y+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
						case 23: { { float v=0; for(int o=0;o<4;o++){float f=wfq*native_pow(2.0,o); v+=native_sin(f*zz2+wph)*native_cos(f*zx)/native_pow(2.0,o);} z.z+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
						case 24: { { float vx=0,vy=0,vz=0; for(int o=0;o<4;o++){float f=wfq*native_pow(2.0,o); float a=1.0/native_pow(2.0,o); vx+=native_sin(f*zy+wph)*a; vy+=native_sin(f*zz2+wph)*a; vz+=native_sin(f*zx+wph)*a;} z.x+=wf*wam*vx; z.y+=wf*wam*vy; z.z+=wf*wam*vz; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq*4.0)); } break; }
						case 25: { { float vx=0,vy=0,vz=0; for(int o=0;o<int(wa);o++){float f=wfq*native_pow(wb,o); float a=1.0/native_pow(wb,o); vx+=native_sin(f*zy+o*wph)*a; vy+=native_sin(f*zz2+o*wph)*a; vz+=native_sin(f*zx+o*wph)*a;} z.x+=wf*wam*vx; z.y+=wf*wam*vy; z.z+=wf*wam*vz; aux.DE*=(1.0+3.0*fabs(wf*wam)); } break; }
						case 26: { { float v=0; for(int o=0;o<4;o++){float f=wfq*native_pow(2.0,o); v+=fabs(native_sin(f*zx+wph))*native_cos(f*zy)/native_pow(2.0,o);} z.x+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
						case 27: { { float vx=0,vy=0; for(int o=0;o<4;o++){float f=wfq*native_pow(2.0,o); vx+=native_sin(f*zy+wph)*native_cos(f*zz2)/native_pow(2.0,o); vy+=native_cos(f*zx+wph)*native_sin(f*zz2)/native_pow(2.0,o);} z.x+=wf*wam*vx; z.y+=wf*wam*vy; aux.DE*=(1.0+2.0*fabs(wf*wam*wfq*4.0)); } break; }
						case 28: { { float v=0; for(int o=0;o<6;o++){float f=wfq*native_pow(2.0,o); v+=native_sin(f*r+wph)/native_pow(2.0,o);} float d=wf*wam*v; z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0+fabs(wf*wam*wfq*6.0)); } break; }
						case 29: { { float vx=0,vy=0,vz=0; for(int o=0;o<4;o++){float f=wfq*native_pow(2.0,o); float p=wph+o*M_PI_F*0.25; vx+=native_sin(f*zy+p)*native_cos(f*zz2+p)/native_pow(2.0,o); vy+=native_sin(f*zz2+p)*native_cos(f*zx+p)/native_pow(2.0,o); vz+=native_sin(f*zx+p)*native_cos(f*zy+p)/native_pow(2.0,o);} z.x+=wf*wam*vx; z.y+=wf*wam*vy; z.z+=wf*wam*vz; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq*4.0)); } break; }
						case 30: { { float ph2=atan2(zy,zx); float th=acos(zz2/r); float v=0; for(int o=0;o<4;o++){float f=wfq*native_pow(2.0,o); v+=native_sin(f*th+wph)*native_cos(f*ph2)/native_pow(2.0,o);} float d=wf*wam*v; z.x+=d*native_sin(th)*native_cos(ph2); z.y+=d*native_sin(th)*native_sin(ph2); z.z+=d*native_cos(th); aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
						case 31: { z.x += wf*wam*(native_cos(wfq*zy+wph)-native_cos(wfq*zz2+wph)); z.y += wf*wam*(native_cos(wfq*zz2+wph)-native_cos(wfq*zx+wph)); z.z += wf*wam*(native_cos(wfq*zx+wph)-native_cos(wfq*zy+wph)); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq)); break; }
						case 32: { { float cx=-wfq*native_cos(wfq*zy+wph); float cy=-wfq*native_cos(wfq*zz2+wph); float cz=-wfq*native_cos(wfq*zx+wph); z.x+=wf*wam*(cy-cz); z.y+=wf*wam*(cz-cx); z.z+=wf*wam*(cx-cy); aux.DE*=(1.0+3.0*fabs(wf*wam*wfq)); } break; }
						case 33: { z.x += wf*wam*native_sin(wfq*zy+wph)*native_sin(wa*zz2); z.y += -wf*wam*native_sin(wfq*zx+wph)*native_sin(wa*zz2); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq)); break; }
						case 34: { z.x += wf*wam*native_sin(wfq*zz2+wph); z.z += -wf*wam*native_sin(wfq*zx+wph); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq)); break; }
						case 35: { z.y += wf*wam*native_sin(wfq*zx+wph); z.x += -wf*wam*native_sin(wfq*zy+wph); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq)); break; }
						case 36: { { float dx=wf*wam*wfq*native_cos(wfq*zy+wph); float dy=wf*wam*wa*native_cos(wa*zz2+wph); float dz=wf*wam*wfq*native_cos(wfq*zx+wph); z.x+=dy-dz; z.y+=dz-dx; z.z+=dx-dy; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq)); } break; }
						case 37: { { float psi=wf*wam*native_sin(wfq*zx+wph)*native_cos(wa*zy)*native_sin(wb*zz2); z.x+=wf*wam*wa*native_sin(wfq*zx)*native_cos(wa*zy); z.y+=-wf*wam*wfq*native_cos(wfq*zx)*native_sin(wa*zy); aux.DE*=(1.0+2.0*fabs(wf*wam*wfq)); } break; }
						case 38: { { float u=wf*wam*native_sin(wfq*r+wph); z.x+=u*(-zy/r); z.y+=u*(zx/r); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 39: { { float u=wf*wam*native_sin(wfq*zz2+wph); z.x+=u*(-zy/(native_sqrt(zx*zx+zy*zy)+1e-21)); z.y+=u*(zx/(native_sqrt(zx*zx+zy*zy)+1e-21)); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 40: { { float ph2=atan2(zy,zx); float u=wf*wam*native_sin(wfq*ph2+wph); z.z+=u; aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 41: { { float th=wf*wfq*zz2+wph; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0+fabs(wf*wfq*wam)); } break; }
						case 42: { { float th=wf*wfq*zx+wph; float cs=native_cos(th),sn=native_sin(th); float ny=zy*cs-zz2*sn; z.z=zy*sn+zz2*cs; z.y=ny; aux.DE*=(1.0+fabs(wf*wfq*wam)); } break; }
						case 43: { { float th=wf*wfq*zy+wph; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zz2*sn; z.z=zx*sn+zz2*cs; z.x=nx; aux.DE*=(1.0+fabs(wf*wfq*wam)); } break; }
						case 44: { { float th=wf*wfq*r+wph; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0+fabs(wf*wfq*wam)); } break; }
						case 45: { { float a1=wf*wa*native_sin(wfq*zz2+wph); float cs=native_cos(a1),sn=native_sin(a1); float nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; float a2=wf*wb*native_sin(wfq*zx+wph); cs=native_cos(a2); sn=native_sin(a2); float ny=zy*cs-zz2*sn; z.z=zy*sn+zz2*cs; z.y=ny; aux.DE*=(1.0+fabs(wf*(wa+wb)*wfq)); } break; }
						case 46: { { float ph2=atan2(zy,zx)+wf*wam*native_sin(wfq*zz2+wph); float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(ph2); z.y=rxy*native_sin(ph2); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 47: { { float th=acos(zz2/r)+wf*wam*native_sin(wfq*r+wph); float ph2=atan2(zy,zx); z.x=r*native_sin(th)*native_cos(ph2); z.y=r*native_sin(th)*native_sin(ph2); z.z=r*native_cos(th); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 48: { { float a=wf*wam*zz2*wfq; float cs=native_cos(a),sn=native_sin(a); float nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; z.z+=wf*wb*native_sin(wfq*r+wph); aux.DE*=(1.0+fabs(wf*(wam+wb)*wfq)); } break; }
						case 49: { { float a=wf*wam*native_sin(wfq*zz2+wph); z.x=zx*native_cos(a)-zy*native_sin(a)+wf*wb*native_sin(wfq*zy); z.y=zx*native_sin(a)+zy*native_cos(a)+wf*wc*native_cos(wfq*zz2); z.z+=wf*wd*native_sin(wfq*zx+wph); aux.DE*=(1.0+fabs(wf*(wam+wb+wc+wd)*wfq/4.0)); } break; }
						case 50: { { float t=wf*wfq*native_log(r+1e-21)+wph; float cs=native_cos(t),sn=native_sin(t); float nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0+fabs(wf*wfq/(r+1e-21))); } break; }
						case 51: { { float d=wf*wam*native_sin(wfq*r+wph); z*=(1.0+d/r); aux.DE*=(1.0+fabs(d/r)); } break; }
						case 52: { { float d=wf*wam/(1.0+native_exp(-wfq*(r-wa))); z*=(1.0+d); aux.DE*=(1.0+fabs(d)); } break; }
						case 53: { { float d=wf*wam*native_exp(-wfq*r*r); z*=(1.0+d); aux.DE*=(1.0+fabs(d)); } break; }
						case 54: { { float d=wf*wam*native_exp(-wfq*fabs(r-wa)); z*=(1.0+d); aux.DE*=(1.0+fabs(d)); } break; }
						case 55: { { float d=wf*wam*(native_sin(wfq*r+wph)+native_sin(wa*r+wb))*0.5; z*=(1.0+d/r); aux.DE*=(1.0+fabs(d/r)); } break; }
						case 56: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21); float d=wf*wam*native_sin(wfq*rxy+wph); z.x+=d*zx/rxy; z.y+=d*zy/rxy; aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 57: { { float d=wf*wam*native_sin(wfq*zz2+wph)*native_exp(-wa*native_sqrt(zx*zx+zy*zy)); z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0+fabs(d)); } break; }
						case 58: { { float ph2=atan2(zy,zx); float th=acos(zz2/r); float d=wf*wam*native_sin(wfq*ph2*wa+wph)*native_sin(wb*th); z.x+=d*native_sin(th)*native_cos(ph2); z.y+=d*native_sin(th)*native_sin(ph2); z.z+=d*native_cos(th); aux.DE*=(1.0+fabs(wf*wam)); } break; }
						case 59: { { float nr=r+wf*wam*native_sin(wfq*r+wph); z*=(nr/r); aux.DE*=(nr/r); } break; }
						case 60: { { float f2=1.0+wf*wam*native_sin(wfq*r+wph)/(r+1e-21); z*=f2; aux.DE*=fabs(f2); } break; }
						case 61: { z.x += wf*wam*native_sin(wfq*floor(zy*wa)/wa + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 62: { z.y += wf*wam*native_sin(wfq*floor(zz2*wa)/wa + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 63: { z.z += wf*wam*native_sin(wfq*floor(zx*wa)/wa + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 64: { { float gx=floor(zx*wa+0.5)/wa; float gy=floor(zy*wa+0.5)/wa; z.x+=wf*wam*native_sin(wfq*gy+wph); z.y+=wf*wam*native_cos(wfq*gx+wph); aux.DE*=(1.0+2.0*fabs(wf*wam*wfq)); } break; }
						case 65: { { float fx=zx-floor(zx*wa)/wa; float fy=zy-floor(zy*wa)/wa; z.x+=wf*wam*native_sin(wfq*fx*M_PI_F*2.0+wph); z.y+=wf*wam*native_sin(wfq*fy*M_PI_F*2.0+wph); aux.DE*=(1.0+2.0*fabs(wf*wam*wfq)); } break; }
						case 66: { { float d=zx*wa-floor(zx*wa+0.5); z.x+=wf*wam*d*native_sin(wfq*zy+wph); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 67: { { float d=native_sin(wfq*zx+wph)*native_sin(wa*zy+wb)*native_sin(wc*zz2+wd); z.x+=wf*wam*d; z.y+=wf*wam*d; z.z+=wf*wam*d; aux.DE*=(1.0+3.0*fabs(wf*wam)); } break; }
						case 68: { { float d=wf*wam*native_sin(wfq*(zx+zy+zz2)+wph); z.x+=d; z.y+=d; z.z+=d; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq)); } break; }
						case 69: { { float d=wf*wam*native_sin(wfq*(zx*zy+zy*zz2+zz2*zx)/(r*r+1e-21)+wph); z.x+=d; z.y+=d; z.z+=d; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq)); } break; }
						case 70: { { float v=wf*wam*native_cos(wfq*zx+wph)*native_cos(wa*zy+wb)*native_cos(wc*zz2+wd); z.x+=v*native_sin(wfq*zy); z.y+=v*native_sin(wa*zz2); z.z+=v*native_sin(wc*zx); aux.DE*=(1.0+3.0*fabs(wf*wam)); } break; }
						case 71: { { float d=wf*wam*native_exp(-wfq*(zx*zx+zy*zy)); z.z+=d; aux.DE*=(1.0+fabs(d)); } break; }
						case 72: { { float d=wf*wam*native_exp(-wfq*r)*native_sin(wa*r+wph); z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0+fabs(d)); } break; }
						case 73: { { float d=wf*wam*native_exp(-wfq*fabs(zz2))*native_sin(wa*native_sqrt(zx*zx+zy*zy)+wph); z.z+=d; aux.DE*=(1.0+fabs(d)); } break; }
						case 74: { { float d=wf*wam/(1.0+wfq*(zx*zx+zy*zy+zz2*zz2)); z.x+=d*native_sin(wa*zy+wph); z.y+=d*native_cos(wa*zz2+wph); aux.DE*=(1.0+2.0*fabs(d*wa)); } break; }
						case 75: { { z *= (1.0 + wf*wam*native_pow(fabs(native_sin(wfq*r+wph)), wa)); aux.DE *= (1.0 + fabs(wf*wam)); } break; }
						case 76: { { float p=wf*wam*native_pow(r+1e-21, wa-1.0)*native_sin(wfq*r+wph); z.x+=p*zx; z.y+=p*zy; z.z+=p*zz2; aux.DE*=(1.0+fabs(p*r)); } break; }
						case 77: { { float d=wf*wam*native_tanh(wfq*(r-wa)); z*=(1.0+d); aux.DE*=(1.0+fabs(d)); } break; }
						case 78: { { float d=wf*wam*native_log(1.0+wfq*r)*native_sin(wa*r+wph)/(r+1e-21); z.x+=d*zx; z.y+=d*zy; z.z+=d*zz2; aux.DE*=(1.0+fabs(d*r)); } break; }
						case 79: { { float d=wf*wam*native_sin(wfq*native_log(r+1e-21)+wph); z*=(1.0+d/r); aux.DE*=(1.0+fabs(d/r)); } break; }
						case 80: { { float sg=1.0/(1.0+native_exp(-wfq*(r-wa))); z*=(1.0+wf*wam*(2.0*sg-1.0)); aux.DE*=(1.0+fabs(wf*wam*(2.0*sg-1.0))); } break; }
						case 81: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21); float d=wf*wam*native_sin(wfq*rxy+wph); z.z+=d; aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 82: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21); float d=wf*wam*native_sin(wfq*zz2+wph); z.x+=d*zx/rxy; z.y+=d*zy/rxy; aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 83: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21); float rt=rxy-wa; float dt=native_sqrt(rt*rt+zz2*zz2); float d=wf*wam*native_sin(wfq*dt+wph); z.x+=d*(rt/dt)*(zx/rxy); z.y+=d*(rt/dt)*(zy/rxy); z.z+=d*(zz2/dt); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 84: { { float ph2=atan2(zy,zx); float d=wf*wam*native_sin(wfq*ph2*wa+wph); z.z+=d; aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 85: { { float ph2=atan2(zy,zx); float rxy=native_sqrt(zx*zx+zy*zy+1e-21); z.x+=-wf*wam*native_sin(ph2)*native_sin(wfq*zz2+wph); z.y+=wf*wam*native_cos(ph2)*native_sin(wfq*zz2+wph); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 86: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21); float d=wf*wam*native_sin(wfq*rxy+wph)*native_cos(wa*zz2); z.x+=d*zx/rxy; z.y+=d*zy/rxy; z.z+=wf*wam*native_cos(wfq*rxy+wph)*native_sin(wa*zz2); aux.DE*=(1.0+2.0*fabs(wf*wam*wfq)); } break; }
						case 87: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21); float ph2=atan2(zy,zx)+wf*wam*native_sin(wfq*zz2+wph)/rxy; z.x=rxy*native_cos(ph2); z.y=rxy*native_sin(ph2); aux.DE*=(1.0+fabs(wf*wam*wfq/rxy)); } break; }
						case 88: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21); float ph2=atan2(zy,zx); float nr=rxy+wf*wam*native_sin(wfq*zz2+wph)*native_sin(wa*ph2); z.x=nr*native_cos(ph2); z.y=nr*native_sin(ph2); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 89: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21); z.z+=wf*wam*native_sin(wfq*rxy+wph)*native_cos(wa*atan2(zy,zx)); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 90: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21); float rt=rxy-wa; float ang=atan2(zz2,rt); float d=wf*wam*native_sin(wfq*ang+wph); z.x+=d*(zx/rxy); z.y+=d*(zy/rxy); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 91: { { float a=wf*wa; float b=wf*wb; z.x=zx+a*native_sin(wfq*zy); z.y=zy+b*native_sin(wfq*zx); aux.DE*=(1.0+fabs((a+b)*wfq)); } break; }
						case 92: { { float k=wf*wam; z.x=zx+k*zy; z.y=zy+k*native_sin(wfq*zx+wph); aux.DE*=(1.0+fabs(k*wfq)); } break; }
						case 93: { { z.x=r*native_cos(wfq*zy/r+wph); z.y=r*native_sin(wfq*zy/r+wph); aux.DE*=(1.0+fabs(wf*wam*wfq/r)); } break; }
						case 94: { { float nr=r+wf*wam*native_sin(wfq*atan2(zy,zx)*wa+wph); z*=(nr/r); aux.DE*=(nr/r); } break; }
						case 95: { { float th=wf*wam/(r*r+1e-10); float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0+fabs(wf*wam*2.0*r/((r*r+1e-10)*(r*r+1e-10)))); } break; }
						case 96: { { float denom=zx*zx+zy*zy+1e-21; z.x=wf*wam*zx/denom+wsc*native_sin(wfq*zy+wph); z.y=-wf*wam*zy/denom+wsc*native_cos(wfq*zx+wph); aux.DE*=(1.0+fabs(wf*wam/denom)+fabs(wsc*wfq)); } break; }
						case 97: { { float a1=wfq; float a2=wa; z.x=zx*native_cos(a1*zy)-zy*native_sin(a1*zy)+wf*wam*native_sin(a2*zz2+wph); z.y=zx*native_sin(a1*zy)+zy*native_cos(a1*zy)+wf*wam*native_cos(a2*zz2+wph); aux.DE*=(1.0+fabs(wf*wam*a1)+fabs(wf*wam*a2)); } break; }
						case 98: { { float lx=wf*wam*native_sin(wfq*zy+wph)*(1.0-native_exp(-wa*r)); float ly=wf*wb*native_sin(wfq*zz2+wph)*(1.0-native_exp(-wa*r)); float lz=wf*wc*native_sin(wfq*zx+wph)*(1.0-native_exp(-wa*r)); z.x+=lx; z.y+=ly; z.z+=lz; aux.DE*=(1.0+fabs(wf*(wam+wb+wc)*wfq/3.0)); } break; }
						case 99: { { float t=wfq*r+wph; float d=wf*wam*native_sin(t)*native_sin(wa*t); z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0+fabs(d)); } break; }
						case 100: { { float d=wf*wam*(native_sin(wfq*zx+wph)+native_sin(wa*zy+wb)+native_sin(wc*zz2+wd)); z*=(1.0+d/(3.0*r)); aux.DE*=(1.0+fabs(d/(3.0*r))); } break; }
					}
				}

				// v7.9 — Symmetry/Kaleidoscope system (per-section iteration range)
				if (i >= mut->skIterStart && i < mut->skIterStop && mut->symKalType != 0)
				{
					float sf = mut->skFactor;
					float sa = mut->skParamA, sb = mut->skParamB, sc = mut->skParamC, sd = mut->skParamD;
					float sfq = mut->skFreq, sam = mut->skAmp;
					float sang = mut->skAngle * M_PI_F / 180.0, soff = mut->skOffset;
					float zx = z.x, zy = z.y, zz2 = z.z;
					float r = native_sqrt(zx*zx + zy*zy + zz2*zz2 + 1e-21);
					switch(mut->symKalType)
					{
						case 1: { z.x = fabs(z.x); break; }
						case 2: { z.y = fabs(z.y); break; }
						case 3: { z.z = fabs(z.z); break; }
						case 4: { z.x = fabs(z.x); z.y = fabs(z.y); break; }
						case 5: { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); break; }
						case 6: { if(z.x < 0) z.x = -z.x - soff; else z.x = z.x + soff; break; }
						case 7: { if(z.y < 0) z.y = -z.y - soff; else z.y = z.y + soff; break; }
						case 8: { if(z.x + z.y < 0) { float t = z.x; z.x = -z.y; z.y = -t; } break; }
						case 9: { if(z.x - z.y < 0) { float t = z.x; z.x = z.y; z.y = t; } break; }
						case 10: { if(z.x + z.z < 0) { float t = z.x; z.x = -z.z; z.z = -t; } break; }
						case 11: { { float ang2 = atan2(zy, zx); float n = fmax(1.0, sa); float sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } break; }
						case 12: { { float ang2 = atan2(zy, zx); float n = 3.0; float sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } break; }
						case 13: { { float ang2 = atan2(zy, zx); float n = 4.0; float sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } break; }
						case 14: { { float ang2 = atan2(zy, zx); float n = 5.0; float sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } break; }
						case 15: { { float ang2 = atan2(zy, zx); float n = 6.0; float sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } break; }
						case 16: { { float ang2 = atan2(zy, zx); float n = 8.0; float sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } break; }
						case 17: { { float ang2 = atan2(zy, zx); float n = 12.0; float sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } break; }
						case 18: { { float ang2 = atan2(zz2, zx); float n = fmax(1.0, sa); float sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; float rxz = native_sqrt(zx*zx+zz2*zz2); z.x = rxz*native_cos(ang2); z.z = rxz*native_sin(ang2); } break; }
						case 19: { { float ang2 = atan2(zz2, zy); float n = fmax(1.0, sa); float sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; float ryz = native_sqrt(zy*zy+zz2*zz2); z.y = ryz*native_cos(ang2); z.z = ryz*native_sin(ang2); } break; }
						case 20: { { float ang2 = atan2(zy, zx); float n = fmax(1.0, sa); float sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector); if(fmod(floor(ang2/sector), 2.0) > 0.5) ang2 = sector - fmod(ang2, sector); else ang2 = fmod(ang2, sector); ang2 -= sector*0.5; float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } break; }
						case 21: { { float cs = native_cos(sang), sn = native_sin(sang); float nx = zx*cs - zy*sn; z.y = zx*sn + zy*cs; z.x = fabs(nx); } break; }
						case 22: { { float cs = native_cos(sang), sn = native_sin(sang); z.x = fabs(zx); float nx = zx*cs - zy*sn; z.y = zx*sn + zy*cs; z.x = nx; z.x = fabs(z.x); } break; }
						case 23: { { if(z.x + z.y < soff) { float t = z.x; z.x = -z.y; z.y = -t; } float cs = native_cos(sang), sn = native_sin(sang); float nx = zx*cs - zy*sn; z.y = zx*sn + zy*cs; z.x = nx; } break; }
						case 24: { { z.x = fabs(z.x); z.y = fabs(z.y); float cs = native_cos(sang), sn = native_sin(sang); float nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; z.x = fabs(z.x); } break; }
						case 25: { { z.x = fabs(z.x) + soff; z.y = fabs(z.y) + soff; float cs = native_cos(sang), sn = native_sin(sang); float nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } break; }
						case 26: { { for(int k=0; k<int(sa); k++) { z.x = fabs(z.x); z.y = fabs(z.y); float cs = native_cos(sang), sn = native_sin(sang); float nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } } break; }
						case 27: { { for(int k=0; k<int(sa); k++) { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); float cs = native_cos(sang+k*sb), sn = native_sin(sang+k*sb); float nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } } break; }
						case 28: { { float cs1 = native_cos(sang), sn1 = native_sin(sang); float nx = zx*cs1 - zy*sn1; z.y = zx*sn1 + zy*cs1; z.x = nx; z.x = fabs(z.x); float cs2 = native_cos(-sang), sn2 = native_sin(-sang); nx = z.x*cs2 - z.y*sn2; z.y = z.x*sn2 + z.y*cs2; z.x = nx; } break; }
						case 29: { { z.x = fabs(z.x); if(z.x - z.y < 0) { float t = z.x; z.x = z.y; z.y = t; } z.y = fabs(z.y); float cs = native_cos(sang), sn = native_sin(sang); float nx = z.x*cs - z.z*sn; z.z = z.x*sn + z.z*cs; z.x = nx; } break; }
						case 30: { { float n = fmax(2.0, sa); for(int k=0; k<int(n); k++) { float a = k * 2.0*M_PI_F/n; float cs = native_cos(a), sn = native_sin(a); float d = z.x*cs + z.y*sn; if(d < 0) { z.x -= 2.0*d*cs; z.y -= 2.0*d*sn; } } } break; }
						case 31: { { z.x = fabs(z.x); z.y = fabs(z.y); if(z.y > z.x) { float t=z.x; z.x=z.y; z.y=t; } z.x -= sa; z.y -= sb; } break; }
						case 32: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.y > z.x) { float t=z.x; z.x=z.y; z.y=t; } if(z.z > z.x) { float t=z.x; z.x=z.z; z.z=t; } if(z.z > z.y) { float t=z.y; z.y=z.z; z.z=t; } z -= (float3)(sa, sb, sc); } break; }
						case 33: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.x - z.y < 0) { float t=z.x; z.x=z.y; z.y=t; } if(z.x - z.z < 0) { float t=z.x; z.x=z.z; z.z=t; } if(z.y - z.z < 0) { float t=z.y; z.y=z.z; z.z=t; } z.x -= sa; z.y -= sb; z.z -= sc; float cs = native_cos(sang), sn = native_sin(sang); float nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } break; }
						case 34: { { z.x = fabs(z.x); z.y = fabs(z.y); float d = z.x*native_cos(sang) + z.y*native_sin(sang); if(d < 0) { z.x -= 2.0*d*native_cos(sang); z.y -= 2.0*d*native_sin(sang); } z -= (float3)(sa, sb, 0); } break; }
						case 35: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); z.x -= sa; z.y -= sb; z.z -= sc; if(z.y > z.x) { float t=z.x; z.x=z.y; z.y=t; } if(z.z > z.x) { float t=z.x; z.x=z.z; z.z=t; } if(z.z > z.y) { float t=z.y; z.y=z.z; z.z=t; } } break; }
						case 36: { { float d = 2.0*fmax(0.0, z.x*native_cos(sang) + z.y*native_sin(sang)); z.x -= d*native_cos(sang); z.y -= d*native_sin(sang); z.x = fabs(z.x); } break; }
						case 37: { { z.x = fabs(z.x); z.y = fabs(z.y); float a = sang; for(int k=0; k<3; k++) { float d = 2.0*fmin(0.0, z.x*native_cos(a) + z.y*native_sin(a)); z.x -= d*native_cos(a); z.y -= d*native_sin(a); a += M_PI_F/3.0; } z -= (float3)(sa, sb, 0); } break; }
						case 38: { { for(int k=0; k<int(fmax(1,sa)); k++) { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); z.x -= sb; z.y -= sc; z.z -= sd; if(z.y > z.x) { float t=z.x; z.x=z.y; z.y=t; } if(z.z > z.x) { float t=z.x; z.x=z.z; z.z=t; } if(z.z > z.y) { float t=z.y; z.y=z.z; z.z=t; } z *= sf; aux.DE *= fabs(sf); } } break; }
						case 39: { { for(int k=0; k<int(fmax(1,sa)); k++) { float cs = native_cos(sang+k*sb), sn = native_sin(sang+k*sb); float d = z.x*cs + z.y*sn; if(d < 0) { z.x -= 2.0*d*cs; z.y -= 2.0*d*sn; } z.x = fabs(z.x) - sc; z.y = fabs(z.y) - sd; } } break; }
						case 40: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); z.x = z.x - sa*round(z.x/fmax(sa,1e-21)); z.y = z.y - sb*round(z.y/fmax(sb,1e-21)); z.z = z.z - sc*round(z.z/fmax(sc,1e-21)); } break; }
						case 41: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.x - z.y < 0) { float t=z.x; z.x=z.y; z.y=t; } if(z.x - z.z < 0) { float t=z.x; z.x=z.z; z.z=t; } if(z.y - z.z < 0) { float t=z.y; z.y=z.z; z.z=t; } z *= sf; z -= (float3)(sa, sb, sc) * (sf - 1.0); aux.DE = aux.DE * fabs(sf) + 1.0; } break; }
						case 42: { { if(z.x + z.y < 0) { float t=-z.y; z.y=-z.x; z.x=t; } if(z.x + z.z < 0) { float t=-z.z; z.z=-z.x; z.x=t; } if(z.y + z.z < 0) { float t=-z.z; z.z=-z.y; z.y=t; } z *= sf; z -= (float3)(sa, sb, sc) * (sf - 1.0); aux.DE = aux.DE * fabs(sf) + 1.0; } break; }
						case 43: { { z.x = fabs(z.x); z.y = fabs(z.y); if(z.x - z.y < 0) { float t=z.x; z.x=z.y; z.y=t; } z.x -= sa; z *= sf; z.x += sa; aux.DE = aux.DE * fabs(sf) + 1.0; } break; }
						case 44: { { z = fabs(z); if(z.x - z.y < 0) { float t=z.x; z.x=z.y; z.y=t; } if(z.x - z.z < 0) { float t=z.x; z.x=z.z; z.z=t; } if(z.y - z.z < 0) { float t=z.y; z.y=z.z; z.z=t; } z.z -= 0.5*sc*(sf-1.0)/sf; z.z = fabs(z.z); z.z += 0.5*sc*(sf-1.0)/sf; z *= sf; z -= (float3)(sa,sb,sc)*(sf-1.0); aux.DE = aux.DE*fabs(sf)+1.0; } break; }
						case 45: { { z = fabs(z); float t; if(z.x-z.y<0){t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){t=z.y;z.y=z.z;z.z=t;} z *= sf; z -= (float3)(1,1,1)*(sf-1.0)*sa; aux.DE=aux.DE*fabs(sf)+1.0; z.x=fabs(z.x); z.y=fabs(z.y); } break; }
						case 46: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); float d1 = z.x - z.y; float d2 = z.y - z.z; if(d1 < 0){float t=z.x;z.x=z.y;z.y=t;} if(d2 < 0){float t=z.y;z.y=z.z;z.z=t;} if(z.x-z.y < 0){float t=z.x;z.x=z.y;z.y=t;} z -= (float3)(sa,sb,sc); z *= sf; z += (float3)(sa,sb,sc); aux.DE = aux.DE*fabs(sf)+1.0; } break; }
						case 47: { { z.x = sa - fabs(z.x - sa); z.y = sb - fabs(z.y - sb); z.z = sc - fabs(z.z - sc); } break; }
						case 48: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.x>sa) z.x=2.0*sa-z.x; if(z.y>sb) z.y=2.0*sb-z.y; if(z.z>sc) z.z=2.0*sc-z.z; } break; }
						case 49: { { float p=sa; z.x = z.x - p*floor(z.x/p+0.5); z.y = z.y - p*floor(z.y/p+0.5); z.z = z.z - p*floor(z.z/p+0.5); } break; }
						case 50: { { float px=sa, py=sb; z.x = z.x - px*floor(z.x/px+0.5); z.y = z.y - py*floor(z.y/py+0.5); } break; }
						case 51: { { float ph2=atan2(zy,zx); float n=fmax(1.0,sa); float s=2.0*M_PI_F/n; ph2=fmod(ph2+10.0*M_PI_F,s)-s*0.5; float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(ph2); z.y=rxy*native_sin(ph2); z.z=fabs(z.z); } break; }
						case 52: { { float ph2=atan2(zy,zx); float th=acos(zz2/r); float n=fmax(1.0,sa); float sp=2.0*M_PI_F/n; ph2=fmod(ph2+10.0*M_PI_F,sp)-sp*0.5; float m=fmax(1.0,sb); float st=M_PI_F/m; th=fmod(th+10.0*M_PI_F,st); z.x=r*native_sin(th)*native_cos(ph2); z.y=r*native_sin(th)*native_sin(ph2); z.z=r*native_cos(th); } break; }
						case 53: { { float ph2=atan2(zy,zx)+sang; float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(ph2); z.y=rxy*native_sin(ph2); z.z=fabs(zz2); } break; }
						case 54: { { float rxy=native_sqrt(zx*zx+zy*zy); if(rxy>sa) { float f=sa/rxy; z.x*=f; z.y*=f; } } break; }
						case 55: { { if(r>sa) z*=sa/r; } break; }
						case 56: { { if(r<sa) z*=sa*sa/(r*r); else if(r<sb) z*=sa*sa/(r*r); } break; }
						case 57: { { float rr=r*r; if(rr<sa*sa) z*=sb*sb/(sa*sa); else if(rr<sb*sb) z*=sb*sb/rr; } break; }
						case 58: { { float th=acos(zz2/r); float n=fmax(1.0,sa); float st=M_PI_F/n; th=fmod(th+10.0*M_PI_F,st); z.x=r*native_sin(th)*native_cos(atan2(zy,zx)); z.y=r*native_sin(th)*native_sin(atan2(zy,zx)); z.z=r*native_cos(th); } break; }
						case 59: { { float p=sa; z.x=z.x-p*round(z.x/p); z.y=z.y-p*round(z.y/p); z.z=z.z-p*round(z.z/p); } break; }
						case 60: { { z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; z.z=fabs(z.z)-sc; if(z.x<0) z.x=-z.x; if(z.y<0) z.y=-z.y; if(z.z<0) z.z=-z.z; } break; }
						case 61: { { float px=fmax(sa,0.01); z.x=z.x-px*floor(z.x/px); z.y=fabs(z.y); } break; }
						case 62: { { float px=fmax(sa,0.01), py=fmax(sb,0.01); z.x=z.x-px*floor(z.x/px); z.y=z.y-py*floor(z.y/py); } break; }
						case 63: { { float px=fmax(sa,0.01), py=fmax(sb,0.01); z.x=z.x-px*floor(z.x/px); z.y=z.y-py*floor(z.y/py); z.x=fabs(z.x-px*0.5); } break; }
						case 64: { { float px=fmax(sa,0.01), py=fmax(sb,0.01); float ix=floor(z.x/px); z.x=z.x-px*ix; z.y=z.y-py*floor(z.y/py); if(fmod(ix,2.0)>0.5) z.x=px-z.x; } break; }
						case 65: { { float p=fmax(sa,0.01); float a60=M_PI_F/3.0; float ux=p, uy=0; float vx=p*native_cos(a60), vy=p*native_sin(a60); float det=ux*vy-uy*vx; float ix=floor((z.x*vy-z.y*vx)/det+0.5); float iy=floor((z.y*ux-z.x*uy)/det+0.5); z.x-=ix*ux+iy*vx; z.y-=ix*uy+iy*vy; } break; }
						case 66: { { float px=fmax(sa,0.01), py=fmax(sb,0.01), pz=fmax(sc,0.01); z.x=z.x-px*floor(z.x/px); z.y=z.y-py*floor(z.y/py); z.z=z.z-pz*floor(z.z/pz); } break; }
						case 67: { { float px=fmax(sa,0.01), py=fmax(sb,0.01), pz=fmax(sc,0.01); z.x=z.x-px*round(z.x/px); z.y=z.y-py*round(z.y/py); z.z=z.z-pz*round(z.z/pz); z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); } break; }
						case 68: { { float p=fmax(sa,0.01); z.x=z.x-p*round(z.x/p); z.y=z.y-p*round(z.y/p); z.z=z.z-p*round(z.z/p); float cs=native_cos(sang),sn=native_sin(sang); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } break; }
						case 69: { { float p=fmax(sa,0.01); float ix=round(z.x/p); float iy=round(z.y/p); z.x-=ix*p; z.y-=iy*p; float a=sang*(ix+iy); float cs=native_cos(a),sn=native_sin(a); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } break; }
						case 70: { { float p=fmax(sa,0.01); z.x=z.x-p*floor(z.x/p+0.5); z.y=z.y-p*floor(z.y/p+0.5); float cs=native_cos(sang),sn=native_sin(sang); if(z.x+z.y>0) { float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } } break; }
						case 71: { if(z.x*z.y > 0) { float t=z.x; z.x=z.y; z.y=t; } break; }
						case 72: { if(z.x*z.y < 0) { z.x = fabs(z.x); z.y = fabs(z.y); } break; }
						case 73: { if(r < sa) { z *= sf; aux.DE *= fabs(sf); } else { z.x = fabs(z.x); z.y = fabs(z.y); } break; }
						case 74: { if(fmod(float(i), sa) < sb) { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); } break; }
						case 75: { { float d = z.x*native_cos(sang) + z.y*native_sin(sang); if(d < soff) { z.x -= 2.0*(d-soff)*native_cos(sang); z.y -= 2.0*(d-soff)*native_sin(sang); } } break; }
						case 76: { { float d1 = z.x*native_cos(sang)+z.y*native_sin(sang); if(d1<0){z.x-=2.0*d1*native_cos(sang);z.y-=2.0*d1*native_sin(sang);} float a2=sang+M_PI_F/fmax(1.0,sa); float d2=z.x*native_cos(a2)+z.y*native_sin(a2); if(d2<0){z.x-=2.0*d2*native_cos(a2);z.y-=2.0*d2*native_sin(a2);} } break; }
						case 77: { { for(int k=0;k<int(fmax(1,sa));k++){ z.x=fabs(z.x)-sb; z.y=fabs(z.y)-sc; if(z.x<z.y){float t=z.x;z.x=z.y;z.y=t;} } } break; }
						case 78: { { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); float m=fmax(fmax(z.x,z.y),z.z); if(m==z.y){float t=z.x;z.x=z.y;z.y=t;} if(m==z.z){float t=z.x;z.x=z.z;z.z=t;} } break; }
						case 79: { { z.x = sa*floor(z.x/fmax(sa,0.01)+0.5)*2.0-z.x; z.y = sb*floor(z.y/fmax(sb,0.01)+0.5)*2.0-z.y; } break; }
						case 80: { { float a=sang; for(int k=0;k<3;k++){ z.x=fabs(z.x); float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0){z.x-=2.0*d*native_cos(a);z.y-=2.0*d*native_sin(a);} a+=M_PI_F/3.0*sf; } } break; }
						case 81: { { float n=fmax(2.0,sa+sb*native_sin(sfq*i)); float ang2=atan2(zy,zx); float s=2.0*M_PI_F/n; ang2=fmod(ang2+10.0*M_PI_F,s)-s*0.5; float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(ang2); z.y=rxy*native_sin(ang2); } break; }
						case 82: { { float a=sang+sam*native_sin(sfq*i); float cs=native_cos(a),sn=native_sin(a); z.x=fabs(z.x); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } break; }
						case 83: { { float d=sf*sam*native_sin(sfq*r+sang); z.x=fabs(z.x)+d; z.y=fabs(z.y)+d; z.z=fabs(z.z)+d; aux.DE*=(1.0+fabs(d)/r); } break; }
						case 84: { { float n=fmax(2.0,sa); float ang2=atan2(zy,zx); float s=2.0*M_PI_F/n; ang2=fmod(ang2+10.0*M_PI_F+sam*native_sin(sfq*i),s)-s*0.5; float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(ang2); z.y=rxy*native_sin(ang2); } break; }
						case 85: { { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); z *= sf + sam*native_sin(sfq*i); aux.DE *= fabs(sf + sam*native_sin(sfq*i)); z -= (float3)(sa,sb,sc)*(sf-1.0); } break; }
						case 86: { { if(i%2==0){z.x=fabs(z.x);z.y=fabs(z.y);} else{float cs=native_cos(sang),sn=native_sin(sang);float nx=z.x*cs-z.y*sn;z.y=z.x*sn+z.y*cs;z.x=nx;} } break; }
						case 87: { { float rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sa*sa){z*=sb*sb/(sa*sa);aux.DE*=sb*sb/(sa*sa);} else if(rr<sb*sb){z*=sb*sb/rr;aux.DE*=sb*sb/rr;} z.x=fabs(z.x); z.y=fabs(z.y); } break; }
						case 88: { { if(z.x+z.y<0){float t=-z.y;z.y=-z.x;z.x=t;} if(z.x+z.z<0){float t=-z.z;z.z=-z.x;z.x=t;} z *= sf; z -= (float3)(sa,sb,sc)*(sf-1.0); aux.DE=aux.DE*fabs(sf)+1.0; if(z.y-z.z<0){float t=z.y;z.y=z.z;z.z=t;} } break; }
						case 89: { { z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; if(z.x<z.y){float t=z.x;z.x=z.y;z.y=t;} float rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sc*sc){float m=sd*sd/(sc*sc);z*=m;aux.DE*=m;} else if(rr<sd*sd){float m=sd*sd/rr;z*=m;aux.DE*=m;} } break; }
						case 90: { { float p=fmax(sa,0.01); z.x=z.x-p*round(z.x/p); z.y=z.y-p*round(z.y/p); z.x=fabs(z.x); z.y=fabs(z.y); if(z.x<z.y){float t=z.x;z.x=z.y;z.y=t;} z *= sf; aux.DE *= fabs(sf); z -= (float3)(sb,sc,0)*(sf-1.0); } break; }
						case 91: { { z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; z.z=fabs(z.z)-sc; if(z.x<z.y){float t=z.x;z.x=z.y;z.y=t;} if(z.x<z.z){float t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){float t=z.y;z.y=z.z;z.z=t;} z*=sf; aux.DE*=fabs(sf); z+=(float3)(sa,sb,sc); } break; }
						case 92: { { float cs=native_cos(sang),sn=native_sin(sang); z.x=fabs(z.x); z.y=fabs(z.y); float d=z.x*sn+z.y*cs; if(d<0){z.x-=2.0*d*sn;z.y-=2.0*d*cs;} z.x-=sa; z.y-=sb; z*=sf; z.x+=sa; z.y+=sb; aux.DE=aux.DE*fabs(sf)+1.0; } break; }
						case 93: { { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); if(z.x-z.y<0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){float t=z.x;z.x=z.z;z.z=t;} z*=sf; z.x-=sa*(sf-1.0); z.y-=sb*(sf-1.0); z.z-=sc*(sf-1.0); float rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sd*sd){z*=sd*sd/rr;aux.DE*=sd*sd/rr;} aux.DE=aux.DE*fabs(sf)+1.0; } break; }
						case 94: { { for(int k=0;k<int(fmax(1,sa));k++){ z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); if(z.x-z.y<0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){float t=z.y;z.y=z.z;z.z=t;} z.x-=sb; z.y-=sc; z.z-=sd; float cs=native_cos(sang+k*sfq),sn=native_sin(sang+k*sfq); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; z.x+=sb; z.y+=sc; z.z+=sd; } } break; }
						case 95: { { float n=fmax(2.0,sa); for(int k=0;k<int(n);k++){ float a=k*M_PI_F/n; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0){z.x-=2.0*d*native_cos(a);z.y-=2.0*d*native_sin(a);} } z.z=fabs(z.z); } break; }
						case 96: { { z=fabs(z); if(z.x<z.y){float t=z.x;z.x=z.y;z.y=t;} if(z.x<z.z){float t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){float t=z.y;z.y=z.z;z.z=t;} z-=(float3)(sa,sb,sc); float rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sd*sd){float m=sf*sf/fmax(rr,1e-21);z*=m;aux.DE*=m;} z*=sf;aux.DE*=fabs(sf); z+=(float3)(sa,sb,sc); } break; }
						case 97: { { float a=2.0*M_PI_F/fmax(1.0,sa); float cs=native_cos(a),sn=native_sin(a); z.x=fabs(z.x); z.y=fabs(z.y); float d=z.x*sn+z.y*cs-soff; if(d>0){z.x-=d*sn;z.y-=d*cs;} z.x-=sb; z*=sf; z.x+=sb; aux.DE=aux.DE*fabs(sf)+1.0; } break; }
						case 98: { { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); float d=2.0*fmin(0.0,z.x+z.y+z.z-sa); z.x-=d/3.0; z.y-=d/3.0; z.z-=d/3.0; } break; }
						case 99: { { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); if(z.x-z.y<0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){float t=z.y;z.y=z.z;z.z=t;} z.z-=0.5*sa; z.z=-fabs(z.z)+0.5*sa; float cs=native_cos(sang),sn=native_sin(sang); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } break; }
						case 100: { { z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; z.z=fabs(z.z)-sc; if(z.x<z.y){float t=z.x;z.x=z.y;z.y=t;} if(z.x<z.z){float t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){float t=z.y;z.y=z.z;z.z=t;} float rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sd*sd){float m=sf*sf/fmax(rr,1e-21);z*=m;aux.DE*=m;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0; z+=(float3)(sa,sb,sc)*(1.0-sf); } break; }
					}
				}

				// v7.9 — Abox DE system (per-section iteration range)
				if (i >= mut->abIterStart && i < mut->abIterStop && mut->aboxType != 0)
				{
					float af = mut->abFactor;
					float aa = mut->abParamA, ab = mut->abParamB, ac = mut->abParamC, ad = mut->abParamD;
					float ae = mut->abParamE, aff = mut->abParamF, ag = mut->abParamG, ah = mut->abParamH;
					float zx = z.x, zy = z.y, zz2 = z.z;
					float r = native_sqrt(zx*zx + zy*zy + zz2*zz2 + 1e-21);
					float rr = r*r;
					switch(mut->aboxType)
					{
						case 1: { aux.DE *= (1.0 + af * aa); break; }
						case 2: { aux.DE *= (1.0 + af * aa * native_sin(ab * r)); break; }
						case 3: { aux.DE *= (1.0 + af * aa * native_cos(ab * r)); break; }
						case 4: { aux.DE *= (1.0 + af * aa * native_exp(-ab * r)); break; }
						case 5: { aux.DE *= (1.0 + af * aa * native_exp(-ab * rr)); break; }
						case 6: { aux.DE *= (1.0 + af * aa * native_log(1.0 + ab * r)); break; }
						case 7: { aux.DE *= (1.0 + af * aa * native_tanh(ab * r)); break; }
						case 8: { aux.DE *= (1.0 + af * aa * native_sin(ab * zx) * native_cos(ac * zy)); break; }
						case 9: { aux.DE *= (1.0 + af * aa * native_sin(ab * zy) * native_cos(ac * zz2)); break; }
						case 10: { aux.DE *= (1.0 + af * aa * native_sin(ab * zz2) * native_cos(ac * zx)); break; }
						case 11: { aux.DE *= (1.0 + af * aa * (native_sin(ab*zx) + native_sin(ac*zy) + native_sin(ad*zz2)) / 3.0); break; }
						case 12: { aux.DE *= (1.0 + af * aa / (1.0 + ab * rr)); break; }
						case 13: { aux.DE *= (1.0 + af * aa * native_pow(r, ab - 1.0)); break; }
						case 14: { aux.DE *= (1.0 + af * aa * fabs(native_sin(ab * r))); break; }
						case 15: { aux.DE *= (1.0 + af * aa * (1.0 - native_exp(-ab * r))); break; }
						case 16: { { float sg = 1.0/(1.0+native_exp(-aa*(r-ab))); aux.DE *= (1.0 + af * sg); } break; }
						case 17: { aux.DE *= (1.0 + af * aa * native_sin(ab*zx)*native_sin(ac*zy)*native_sin(ad*zz2)); break; }
						case 18: { aux.DE *= (1.0 + af * aa * native_cos(ab*zx)*native_cos(ac*zy)*native_cos(ad*zz2)); break; }
						case 19: { aux.DE *= (1.0 + af * aa * native_sin(ab*r+ac*atan2(zy,zx))); break; }
						case 20: { aux.DE *= (1.0 + af * aa * native_sin(ab*r)*native_cos(ac*acos(zz2/r))); break; }
						case 21: { { float v = 0; for(int o=0;o<4;o++) v += native_sin(ab*native_pow(2.0,o)*r)/(native_pow(2.0,o)); aux.DE *= (1.0 + af * aa * v); } break; }
						case 22: { aux.DE *= (1.0 + af * aa * (zx*zy+zy*zz2+zz2*zx)/(rr+1e-21)); break; }
						case 23: { aux.DE *= (1.0 + af * aa * fabs(zx*zy*zz2)/(r*r*r+1e-21)); break; }
						case 24: { aux.DE *= (1.0 + af * aa * native_sin(ab*(zx*zx-zy*zy)/(rr+1e-21))); break; }
						case 25: { aux.DE *= (1.0 + af * aa * atan2(native_sqrt(zx*zx+zy*zy), zz2) / M_PI_F); break; }
						case 26: { { float rr2=rr; if(rr2<aa*aa) { float m=ab*ab/fmax(rr2,1e-21); aux.DE*=m; } aux.DE*=(1.0+af*0.1); } break; }
						case 27: { { float rr2=rr; float mR2=aa*aa; float fR2=ab*ab; if(rr2<mR2) aux.DE*=fR2/mR2; else if(rr2<fR2) aux.DE*=fR2/rr2; } break; }
						case 28: { aux.DE *= (1.0 + af * aa * native_exp(-ab*(r-ac)*(r-ac))); break; }
						case 29: { aux.DE *= (1.0 + af * aa * (1.0/(1.0+native_exp(-ab*(r-ac))) - 0.5)); break; }
						case 30: { aux.DE *= (1.0 + af * aa * native_sin(ab*r)*native_exp(-ac*r)); break; }
						case 31: { aux.DE *= (1.0 + af * aa * fabs(native_sin(ab*r+ac))*native_exp(-ad*r)); break; }
						case 32: { { float s = aa * native_sin(ab*r+ac*atan2(zy,zx)) * native_exp(-ad*r); aux.DE *= (1.0 + af*s); } break; }
						case 33: { aux.DE *= (1.0 + af * aa * native_tanh(ab*(r-ac))); break; }
						case 34: { aux.DE *= (1.0 + af * aa * native_sin(ab*native_log(r+1e-21))); break; }
						case 35: { aux.DE *= (1.0 + af * aa * native_cos(ab*native_log(r+1e-21)+ac)); break; }
						case 36: { { float ph=atan2(zy,zx); float th=acos(zz2/r); aux.DE*=(1.0+af*aa*native_sin(ab*ph)*native_sin(ac*th)); } break; }
						case 37: { { float ph=atan2(zy,zx); aux.DE*=(1.0+af*aa*native_cos(ab*ph+ac*r)); } break; }
						case 38: { aux.DE *= fmax(0.01, 1.0 + af * aa * native_sin(ab*r) * native_cos(ac*r)); break; }
						case 39: { { float d=r-aa; aux.DE*=(1.0+af*ab*native_exp(-ac*d*d)); } break; }
						case 40: { aux.DE *= (1.0 + af * aa * native_sin(ab*r) / (r+1e-21)); break; }
						case 41: { { float n=native_sin(aa*zx)*native_sin(ab*zy)*native_sin(ac*zz2); aux.DE*=(1.0+af*ad*n); } break; }
						case 42: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21); aux.DE*=(1.0+af*aa*native_sin(ab*rxy+ac*zz2)); } break; }
						case 43: { aux.DE *= (1.0 + af * aa * native_cos(ab*zx+ac*zy+ad*zz2)); break; }
						case 44: { { float v=aa*native_sin(ab*r)+ac*native_cos(ad*r); aux.DE*=(1.0+af*v*0.5); } break; }
						case 45: { aux.DE *= fmax(0.01, 1.0 + af * aa * native_pow(fabs(native_sin(ab*r)), ac)); break; }
						case 46: { aux.DE *= (1.0 + af * aa * native_sin(ab*r*r/(r+1e-21))); break; }
						case 47: { { float f=aa+ab*native_sin(ac*i); aux.DE*=(1.0+af*f); } break; }
						case 48: { { float rr2=rr; float minR=aa; float fixR=ab; if(rr2<minR*minR){float m=fixR*fixR/(minR*minR);aux.DE*=m;} else if(rr2<fixR*fixR){float m=fixR*fixR/rr2;aux.DE*=m;} aux.DE*=(1.0+af*ac*native_sin(ad*r)); } break; }
						case 49: { aux.DE *= (1.0 + af * aa * (native_sin(ab*r) + native_cos(ac*r*r/(r+1e-21))) * 0.5); break; }
						case 50: { { float d=fabs(r-aa); float ring=native_exp(-ab*d*d); aux.DE*=(1.0+af*ac*ring); } break; }
						case 51: { aux.DE *= fabs(aa); break; }
						case 52: { aux.DE *= fabs(aa + ab*native_sin(ac*i)); break; }
						case 53: { aux.DE *= fabs(aa * native_pow(ab, ac)); break; }
						case 54: { aux.DE *= fabs(aa + ab * r); break; }
						case 55: { aux.DE *= fmax(0.01, fabs(aa + ab * native_sin(ac * r))); break; }
						case 56: { aux.DE *= fabs(aa + ab * native_exp(-ac * i)); break; }
						case 57: { aux.DE *= fabs(aa + ab * native_log(1.0 + ac * i)); break; }
						case 58: { { float golden=1.6180339887; aux.DE*=fabs(aa+ab*native_pow(golden,ac*i-ad)); } break; }
						case 59: { aux.DE *= fabs(aa + ab * native_sin(ac * i) * native_cos(ad * r)); break; }
						case 60: { { float s=aa+ab*native_tanh(ac*(i-ad)); aux.DE*=fabs(s); } break; }
						case 61: { aux.DE *= fmax(0.01, fabs(aa + ab * fmod(float(i) * ac, ad))); break; }
						case 62: { aux.DE *= fabs(aa + ab / (1.0 + ac * i)); break; }
						case 63: { { float ph=atan2(zy,zx); aux.DE*=fabs(aa+ab*native_sin(ac*ph)); } break; }
						case 64: { aux.DE *= fabs(aa + ab * (zx*zx - zy*zy) / (rr + 1e-21)); break; }
						case 65: { aux.DE *= fabs(aa + ab * native_sin(ac * i * M_PI_F / ad)); break; }
						case 66: { { float s=aa*(1.0+ab*native_sin(ac*float(i))); aux.DE*=fabs(s); } break; }
						case 67: { aux.DE *= fabs(aa + ab * fabs(native_sin(ac * r + ad * i))); break; }
						case 68: { { float s=aa+ab*native_cos(ac*r)*native_sin(ad*i*0.1); aux.DE*=fabs(s); } break; }
						case 69: { aux.DE *= fabs(aa + ab * (native_sin(ac*zx)+native_sin(ad*zy)+native_sin(ae*zz2))/3.0); break; }
						case 70: { { float rat=aa/fmax(ab,1e-21); float s=native_pow(fabs(rat),ac); aux.DE*=s; } break; }
						case 71: { aux.DE *= fmax(0.01, fabs(aa * native_exp(-ab * fabs(native_sin(ac * r))))); break; }
						case 72: { { float s=aa+ab*native_pow(fabs(native_sin(ac*r)),ad); aux.DE*=fabs(s); } break; }
						case 73: { aux.DE *= fabs(aa + ab * native_tanh(ac * native_sin(ad * r))); break; }
						case 74: { { float mix=0.5+0.5*native_sin(ac*i); float s=aa*(1.0-mix)+ab*mix; aux.DE*=fabs(s); } break; }
						case 75: { aux.DE *= fabs(aa + ab * native_sin(ac * r) * native_log(1.0 + ad * r)); break; }
						case 76: { { float a=aa*M_PI_F/180.0; aux.DE*=(1.0+af*fabs(native_sin(a))); } break; }
						case 77: { { float a=aa*M_PI_F/180.0+ab*native_sin(ac*i); aux.DE*=(1.0+af*fabs(native_sin(a))); } break; }
						case 78: { aux.DE *= (1.0 + af * aa * native_sin(ab*atan2(zy,zx))); break; }
						case 79: { aux.DE *= (1.0 + af * aa * native_cos(ab*atan2(zy,zx)+ac*acos(zz2/r))); break; }
						case 80: { { float ph=atan2(zy,zx); float n=fmax(1.0,aa); float s=2.0*M_PI_F/n; float sector=fmod(ph+10.0*M_PI_F,s)/s; aux.DE*=(1.0+af*ab*native_sin(M_PI_F*sector)); } break; }
						case 81: { aux.DE *= (1.0 + af * aa * fabs(native_sin(ab * atan2(zz2, native_sqrt(zx*zx+zy*zy+1e-21))))); break; }
						case 82: { { float q1=zx*native_cos(aa)-zy*native_sin(aa); float q2=zx*native_sin(aa)+zy*native_cos(aa); aux.DE*=(1.0+af*ab*native_sin(ac*q1)*native_cos(ad*q2)); } break; }
						case 83: { aux.DE *= (1.0 + af * aa * native_cos(ab * (zx+zy+zz2))); break; }
						case 84: { { float cs=native_cos(aa*M_PI_F/180.0),sn=native_sin(aa*M_PI_F/180.0); float rxy=native_sqrt(zx*zx+zy*zy+1e-21); float nph=atan2(zy,zx)+ab*native_sin(ac*rxy); aux.DE*=(1.0+af*ad*native_sin(ae*nph)); } break; }
						case 85: { aux.DE *= (1.0 + af * aa * native_sin(ab*(zx*zy+zy*zz2+zz2*zx)/(rr+1e-21))); break; }
						case 86: { { float gld=aa*0.618033988749895; aux.DE*=(1.0+af*ab*native_sin(ac*gld*i)); } break; }
						case 87: { aux.DE *= (1.0 + af * aa * native_sin(ab*r+ac*atan2(zy,zx)+ad*i*0.1)); break; }
						case 88: { { float sw=fabs(zx)>fabs(zy)?zx:zy; aux.DE*=(1.0+af*aa*native_sin(ab*sw)); } break; }
						case 89: { aux.DE *= (1.0 + af * aa * native_cos(ab*zx*zy/(r+1e-21))); break; }
						case 90: { { float fld=aa*(fabs(zx)+fabs(zy)+fabs(zz2)); aux.DE*=(1.0+af*ab*native_sin(fld)); } break; }
						case 91: { aux.DE *= (1.0 + af * aa * native_sin(ab*i) * native_cos(ac*r) * native_sin(ad*atan2(zy,zx))); break; }
						case 92: { { float sym=fabs(zx-zy)+fabs(zy-zz2)+fabs(zz2-zx); aux.DE*=(1.0+af*aa*native_sin(ab*sym)); } break; }
						case 93: { aux.DE *= (1.0 + af * aa * native_tanh(ab*native_sin(ac*atan2(zy,zx)))); break; }
						case 94: { { float det=zx*zy-zy*zz2+zz2*zx; aux.DE*=(1.0+af*aa*native_sin(ab*det/(rr+1e-21))); } break; }
						case 95: { aux.DE *= (1.0 + af * aa * native_sin(ab*r) * native_sin(ac*atan2(zy,zx)+ad*acos(zz2/r))); break; }
						case 96: { { float tw=aa*zz2+ab; float cs=native_cos(tw),sn=native_sin(tw); aux.DE*=(1.0+af*ac*fabs(sn)); } break; }
						case 97: { aux.DE *= (1.0 + af * aa * fabs(native_sin(ab*zx))*fabs(native_sin(ac*zy))*fabs(native_sin(ad*zz2))); break; }
						case 98: { { float mir=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.DE*=(1.0+af*aa*native_sin(ab*mir)); } break; }
						case 99: { { float mx=fmax(fabs(zx),fmax(fabs(zy),fabs(zz2))); aux.DE*=(1.0+af*aa*native_cos(ab*mx)); } break; }
						case 100: { aux.DE *= (1.0 + af * aa * native_sin(ab*r+ac*native_sin(ad*r))); break; }
						case 101: { { float w=aa*native_sin(ab*r); aux.DE*=(1.0+af*ac*fabs(w)); } break; }
						case 102: { { float r4=native_sqrt(rr+aa*aa*native_sin(ab*r)*native_sin(ab*r)); aux.DE*=(1.0+af*ac*(r4-r)/(r+1e-21)); } break; }
						case 103: { { float w=aa*native_cos(ab*zx+ac*zy); aux.DE*=(1.0+af*ad*w*w); } break; }
						case 104: { { float w=aa*native_sin(ab*i*0.1); float r4=native_sqrt(rr+w*w); aux.DE*=(1.0+af*ac*native_sin(ad*r4)); } break; }
						case 105: { aux.DE *= (1.0 + af * aa * native_sin(ab*(zx*zx+zy*zy-zz2*zz2)/(rr+1e-21))); break; }
						case 106: { { float w=aa*native_sin(ab*r+ac*i*0.1); aux.DE*=(1.0+af*ad*native_exp(-ae*w*w)); } break; }
						case 107: { { float q=zx*zx-zy*zy; float s=2.0*zx*zy; aux.DE*=(1.0+af*aa*native_sin(ab*q/(rr+1e-21))*native_cos(ac*s/(rr+1e-21))); } break; }
						case 108: { aux.DE *= (1.0 + af * aa * native_sin(ab*(zx*zy+ac*zz2))); break; }
						case 109: { { float hd=native_sin(aa*zx)*native_cos(ab*zy)+native_sin(ac*zy)*native_cos(ad*zz2)+native_sin(ae*zz2)*native_cos(aff*zx); aux.DE*=(1.0+af*ag*hd/3.0); } break; }
						case 110: { { float cr=zx*zx+zy*zy; float ci=2.0*zx*zy; float r4=native_sqrt(cr*cr+ci*ci+zz2*zz2); aux.DE*=(1.0+af*aa*native_sin(ab*r4)); } break; }
						case 111: { aux.DE *= (1.0 + af * aa * native_tanh(ab*(zx*zx+zy*zy-zz2*zz2))); break; }
						case 112: { aux.DE *= (1.0 + af * aa * native_sin(ab*zx+ac) * native_sin(ad*zy+ae) * native_cos(aff*zz2)); break; }
						case 113: { { float p=aa*zx*zy*zz2/(r*r*r+1e-21); aux.DE*=(1.0+af*ab*native_sin(ac*p)); } break; }
						case 114: { { float s1=native_sin(aa*r),s2=native_sin(ab*r); float w=s1*s1-s2*s2; aux.DE*=(1.0+af*ac*w); } break; }
						case 115: { aux.DE *= (1.0 + af * aa * native_cos(ab*r*r/(r+1e-21)+ac*native_sin(ad*r))); break; }
						case 116: { { float w=aa*native_sin(ab*(zx+zy+zz2))+ac*native_cos(ad*(zx-zy+zz2)); aux.DE*=(1.0+af*w*0.5); } break; }
						case 117: { aux.DE *= (1.0 + af * aa * native_sin(ab*zx*zx/(rr+1e-21)+ac*zy*zy/(rr+1e-21))); break; }
						case 118: { { float v=aa*native_sin(ab*r)+ac*native_sin(ad*r)+ae*native_sin(aff*r); aux.DE*=(1.0+af*v/3.0); } break; }
						case 119: { aux.DE *= (1.0 + af * aa * native_exp(-ab*fabs(zx*zy*zz2)/(r*r*r+1e-21))); break; }
						case 120: { { float w=aa+ab*native_sin(ac*r+ad*native_sin(ae*r)); aux.DE*=(1.0+af*w); } break; }
						case 121: { aux.DE *= (1.0 + af * aa * native_sin(ab*(r - floor(r*ac)/ac))); break; }
						case 122: { { float ph4=atan2(zz2,native_sqrt(zx*zx+zy*zy+1e-21)); aux.DE*=(1.0+af*aa*native_sin(ab*ph4+ac*r)); } break; }
						case 123: { aux.DE *= (1.0 + af * aa * fabs(native_sin(ab*r)*native_cos(ac*r)*native_sin(ad*r))); break; }
						case 124: { { float v=aa*native_sin(ab*zx)*native_cos(ac*zx)+ad*native_sin(ae*zy)*native_cos(aff*zy); aux.DE*=(1.0+af*v*0.5); } break; }
						case 125: { aux.DE *= (1.0 + af * aa * (native_sin(ab*r)+native_sin(ac*r)+native_sin(ad*r)+native_sin(ae*r))/4.0); break; }
						case 126: { aux.DE *= (1.0 + af * aa * fabs(zx)/(r+1e-21)); break; }
						case 127: { aux.DE *= (1.0 + af * aa * fabs(zy)/(r+1e-21)); break; }
						case 128: { aux.DE *= (1.0 + af * aa * fabs(zz2)/(r+1e-21)); break; }
						case 129: { { float orb=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.DE*=(1.0+af*aa*native_sin(ab*orb)); } break; }
						case 130: { { float orb=fmax(fabs(zx),fmax(fabs(zy),fabs(zz2))); aux.DE*=(1.0+af*aa*native_cos(ab*orb)); } break; }
						case 131: { { float orb=native_sqrt(zx*zx+zy*zy); aux.DE*=(1.0+af*aa*native_sin(ab*orb)); } break; }
						case 132: { { float dt=fabs(native_sqrt(zx*zx+zy*zy)-aa); aux.DE*=(1.0+af*ab*native_exp(-ac*dt*dt)); } break; }
						case 133: { { float ds=fmax(fabs(zx)-aa,fabs(zy)-ab); ds=fmax(ds,fabs(zz2)-ac); aux.DE*=(1.0+af*ad*native_exp(-ae*ds*ds)); } break; }
						case 134: { { float dp=fabs(zx*native_cos(aa)+zy*native_sin(aa)-ab); aux.DE*=(1.0+af*ac*native_exp(-ad*dp*dp)); } break; }
						case 135: { { float dl=fabs(zx-aa*zy-ab); aux.DE*=(1.0+af*ac*native_exp(-ad*dl*dl)); } break; }
						case 136: { { float c=fabs(native_sin(aa*zx)+native_sin(ab*zy)+native_sin(ac*zz2))/3.0; aux.DE*=(1.0+af*ad*c); } break; }
						case 137: { { float c=fabs(native_sin(aa*r)*native_cos(ab*atan2(zy,zx))); aux.DE*=(1.0+af*ac*c); } break; }
						case 138: { { float c=fabs(zx*zy+zy*zz2+zz2*zx)/(rr+1e-21); aux.DE*=(1.0+af*aa*c); } break; }
						case 139: { { float h=atan2(zy,zx)/(2.0*M_PI_F)+0.5; aux.DE*=(1.0+af*aa*native_sin(ab*h*M_PI_F*2.0)); } break; }
						case 140: { { float s=r/(r+aa); aux.DE*=(1.0+af*ab*s); } break; }
						case 141: { { float v=native_sin(aa*zx)*native_sin(ab*zy)+native_sin(ac*zy)*native_sin(ad*zz2); aux.DE*=(1.0+af*ae*v*0.5); } break; }
						case 142: { { float orb=fabs(zx-floor(zx*aa)/aa)*fabs(zy-floor(zy*ab)/ab); aux.DE*=(1.0+af*ac*native_sin(ad*orb)); } break; }
						case 143: { aux.DE *= (1.0 + af * aa * native_sin(ab * (fabs(zx)+fabs(zy)+fabs(zz2)))); break; }
						case 144: { { float d2=fabs(zx*zx/fmax(aa*aa,0.01)+zy*zy/fmax(ab*ab,0.01)-1.0); aux.DE*=(1.0+af*ac*native_exp(-ad*d2)); } break; }
						case 145: { { float sp=zx*native_cos(aa*zy)+zy*native_cos(aa*zz2)+zz2*native_cos(aa*zx); aux.DE*=(1.0+af*ab*native_sin(ac*sp)); } break; }
						case 146: { { float cl=native_sin(aa*length(z)+ab*r); aux.DE*=(1.0+af*ac*cl); } break; }
						case 147: { { float it=float(i)/fmax(float(aa),1.0); aux.DE*=(1.0+af*ab*native_sin(ac*it*M_PI_F)); } break; }
						case 148: { { float gr=native_sin(aa*zx*zy/(r+1e-21))+native_cos(ab*zy*zz2/(r+1e-21)); aux.DE*=(1.0+af*ac*gr*0.5); } break; }
						case 149: { { float pat=native_sin(aa*zx)*native_cos(ab*zy)*native_sin(ac*zz2)*native_cos(ad*r); aux.DE*=(1.0+af*ae*pat); } break; }
						case 150: { { float comb=aa*native_sin(ab*r)+ac*native_cos(ad*atan2(zy,zx))+ae*native_sin(aff*acos(zz2/r)); aux.DE*=(1.0+af*comb/3.0); } break; }
						case 151: { { float de=aa*r*native_log(r+1e-21)/fmax(ab,0.01); aux.DE*=(1.0+af*de/(r+1e-21)); } break; }
						case 152: { aux.DE *= fmax(0.01, 1.0 + af * aa * r * native_sin(ab*native_log(r+1e-21)+ac)); break; }
						case 153: { { float lip=aa*fmin(1.0,ab/fmax(r,1e-21)); aux.DE*=(1.0+af*lip); } break; }
						case 154: { aux.DE *= (1.0 + af * aa * native_exp(-ab*r) * native_sin(ac*r+ad)); break; }
						case 155: { { float bess=native_sin(aa*r)/(aa*r+1e-21); aux.DE*=(1.0+af*ab*bess); } break; }
						case 156: { { float cheb=native_cos(aa*acos(fmin(1.0,fmax(-1.0,zz2/r)))); aux.DE*=(1.0+af*ab*cheb); } break; }
						case 157: { { float leg=(3.0*(zz2/r)*(zz2/r)-1.0)*0.5; aux.DE*=(1.0+af*aa*leg); } break; }
						case 158: { { float herm=(4.0*(zz2/r)*(zz2/r)-2.0)*native_exp(-(zz2/r)*(zz2/r)*0.5); aux.DE*=(1.0+af*aa*ab*herm); } break; }
						case 159: { { float lag=1.0-aa*r+aa*aa*r*r*0.5; aux.DE*=(1.0+af*ab*lag*native_exp(-ac*r)); } break; }
						case 160: { aux.DE *= (1.0 + af * aa * native_sin(ab*r+ac) * native_sin(ad*r+ae) * native_sin(aff*r+ag)); break; }
						case 161: { { float gr=aa*r*native_exp(-ab*r*r)*native_sin(ac*r); aux.DE*=(1.0+af*gr); } break; }
						case 162: { aux.DE *= (1.0 + af * aa * native_sin(ab*r) * native_tanh(ac*r)); break; }
						case 163: { { float sg=1.0/(1.0+native_exp(-aa*(r-ab))); aux.DE*=(1.0+af*ac*sg*(1.0-sg)); } break; }
						case 164: { { float gau=native_exp(-aa*(r-ab)*(r-ab)); aux.DE*=(1.0+af*ac*gau); } break; }
						case 165: { { float stp=(r>aa)?ab:ac; aux.DE*=(1.0+af*stp); } break; }
						case 166: { { float bnd=aa*native_sin(floor(r*ab)*M_PI_F/ab); aux.DE*=(1.0+af*bnd); } break; }
						case 167: { { float v=0; for(int o=0;o<4;o++){v+=native_sin(aa*native_pow(2.0,o)*r+ab*o)/(native_pow(2.0,o));} aux.DE*=(1.0+af*ac*v); } break; }
						case 168: { { float jc=aa*native_sin(ab*r)+ac*native_sin(ad*atan2(zy,zx)); aux.DE*=(1.0+af*jc*0.5); } break; }
						case 169: { { float tmp=aa+ab*native_sin(ac*r)*native_cos(ad*i*0.1); aux.DE*=(1.0+af*tmp); } break; }
						case 170: { { float fb=0; float prev=aa; float curr=ab; for(int k=0;k<6;k++){float nxt=prev+curr; fb+=native_sin(nxt*r)/(nxt+1.0); prev=curr; curr=nxt;} aux.DE*=(1.0+af*ac*fb); } break; }
						case 171: { { float orb=r; float v=aa*native_sin(ab*orb)+ac*native_cos(ad*orb*orb/(r+1e-21)); aux.DE*=(1.0+af*v); } break; }
						case 172: { aux.DE *= (1.0 + af * aa * fabs(native_sin(ab*r)) * fabs(native_cos(ac*r))); break; }
						case 173: { aux.DE *= fabs(aa); break; }
						case 174: { aux.DE *= (1.0 + fabs(aa*M_PI_F/180.0) * ab); break; }
						case 175: { aux.DE *= (1.0 + fabs(aa + ab + ac)); break; }
						case 176: { aux.DE *= fmax(0.01, aa * float(i) / fmax(float(ab), 1.0)); break; }
						case 177: { { if(fabs(zx)>aa||fabs(zy)>aa||fabs(zz2)>aa) aux.DE*=ab; } break; }
						case 178: { { float d=native_sqrt((zx-aa)*(zx-aa)+(zy-ab)*(zy-ab)+(zz2-ac)*(zz2-ac)); if(d<ad) aux.DE*=ae; } break; }
						case 179: { { if(fabs(zx)<aa && fabs(zy)<aa) aux.DE*=ab; } break; }
						case 180: { aux.DE *= (1.0 + 0.1 * aa * fabs(native_sin(ab*r))); break; }
						case 181: { aux.DE *= (1.0 - aa * ab * native_exp(-ac*r)); break; }
						case 182: { aux.DE /= fmax(0.01, 1.0 + aa * ab); break; }
						case 183: { aux.DE *= (1.0 + aa * ab * r); break; }
						case 184: { aux.DE /= fmax(0.01, 1.0 + aa * ab * native_sin(ac*r)); break; }
						case 185: { aux.DE *= (1.0 + aa * ab * r); break; }
						case 186: { aux.DE *= (1.0 + aa * fabs(ab - 550.0) * 0.001); break; }
						case 187: { aux.DE *= (1.0 + aa * fabs(native_sin(ab*zx)*native_cos(ac*zy))); break; }
						case 188: { { float fr=native_pow(fabs(1.0-fabs(zz2)/r),5.0); aux.DE*=(1.0+aa*fr); } break; }
						case 189: { { float tf=native_sin(aa*r+ab)*native_cos(ac*r); aux.DE*=(1.0+ad*fabs(tf)); } break; }
						case 190: { { float an=fabs(zx*aa+zy*ab+zz2*ac)/(r+1e-21); aux.DE*=(1.0+ad*an); } break; }
						case 191: { aux.DE /= fmax(0.01, 1.0 + aa * ab); break; }
						case 192: { aux.DE *= (1.0 + aa * native_exp(-ab * r)); break; }
						case 193: { aux.DE *= (1.0 + aa * ab * r); break; }
						case 194: { aux.DE += aa * ab * native_sin(ac*zx)*native_cos(ad*zy); break; }
						case 195: { aux.DE *= (1.0 + aa * ab * native_sin(ac*zx+ad*zy+ae*zz2)); break; }
						case 196: { aux.DE *= fmax(0.01, aa * ab / fmax(ac, 0.01)); break; }
						case 197: { aux.DE /= fmax(0.01, aa); break; }
						case 198: { aux.DE *= native_exp(-aa * ab * r); break; }
						case 199: { aux.DE *= (1.0 + aa * ab * (1.0 + ac*native_cos(ad*atan2(zy,zx)))); break; }
						case 200: { aux.DE /= fmax(0.01, 1.0 + aa * ab); break; }
						case 201: { { float curl=native_sin(aa*zy+ab*zz2)-native_sin(aa*zz2+ab*zx); aux.DE*=(1.0+ac*fabs(curl)); } break; }
						case 202: { { float grad=(zx*aa+zy*ab+zz2*ac)/(rr+1e-21); aux.DE/=fmax(0.01,1.0+ad*fabs(grad)); } break; }
						case 203: { aux.DE *= (1.0 + aa * ab / fmax(rr, 1e-21)); break; }
						case 204: { { float v2=aa*aa; float c2=ab*ab; aux.DE*=native_sqrt(fmax(0.01,1.0-v2/fmax(c2,1e-21))); } break; }
						case 205: { aux.DE *= native_exp(-aa * fabs(r - ab)); break; }
						case 206: { { float psi=native_sin(aa*zx)*native_sin(ab*zy)*native_sin(ac*zz2); aux.DE*=fmax(0.01,psi*psi); } break; }
						case 207: { aux.DE *= (1.0 + aa / fmax(2.0 * ab * r, 1e-21)); break; }
						case 208: { aux.DE *= (1.0 + aa * (zx*ab + zy*ac + zz2*ad)/(r+1e-21)); break; }
						case 209: { { float corr=native_sin(aa*zx)*native_sin(aa*(-zx))+native_cos(ab*zy)*native_cos(ab*(-zy)); aux.DE*=(1.0+ac*fabs(corr)); } break; }
						case 210: { aux.DE *= native_exp(-aa * ab * float(i) * 0.01); break; }
						case 211: { { float ent=native_sin(aa*zx)*native_log(fabs(native_sin(aa*zx))+1e-21)+native_sin(ab*zy)*native_log(fabs(native_sin(ab*zy))+1e-21); aux.DE*=(1.0+ac*fabs(ent)*0.1); } break; }
						case 212: { aux.DE *= (1.0 + aa / fmax(ab * ac, 1e-21)); break; }
						case 213: { { float vg=(native_sin(aa*(zx+0.01))-native_sin(aa*zx))/0.01; aux.DE*=(1.0+ab*fabs(vg)); } break; }
						case 214: { { float curv=(native_sin(aa*zx+0.01)+native_sin(aa*zx-0.01)-2.0*native_sin(aa*zx))/0.0001; aux.DE*=(1.0+ab*fabs(curv)); } break; }
						case 215: { aux.DE *= (1.0 + aa * native_cos(ab) / fmax(ac, 0.01)); break; }
						case 216: { { float cg=(native_sin(aa*(zx+0.01))-native_sin(aa*zx))/0.01; aux.DE*=(1.0+ab*fabs(cg)); } break; }
						case 217: { { float lap=native_sin(aa*(zx+0.01))+native_sin(aa*(zx-0.01))-2.0*native_sin(aa*zx); aux.DE+=ab*lap; } break; }
						case 218: { { float adv=(native_sin(aa*zx)-native_sin(aa*(zx-0.01)))/0.01; aux.DE*=(1.0+ab*fabs(adv)); } break; }
						case 219: { { float v=0; for(int o=0;o<4;o++){v+=native_sin(aa*native_pow(2.0,o)*r)/native_pow(2.0,o);} aux.DE*=(1.0+ab*fabs(v)); } break; }
						case 220: { { float sh=(r>aa)?ab:0.0; aux.DE*=(1.0+ac*sh); } break; }
						case 221: { { float dw=aa-ab; float bw=ac*0.5; float q=ad/fmax(native_sqrt(dw*dw+bw*bw),1e-21); aux.DE*=(1.0+af*q); } break; }
						case 222: { aux.DE *= (1.0 + aa * native_cos(ab * r + ac)); break; }
						case 223: { aux.DE *= (1.0 + aa / fmax(ab, 1e-21) * native_cos(ac)); break; }
						case 224: { aux.DE *= (1.0 + aa * native_cos(2.0 * ab * atan2(zy, zx))); break; }
						case 225: { aux.DE *= (1.0 + aa * fabs(native_sin(2.0 * ab * atan2(zz2, native_sqrt(zx*zx+zy*zy+1e-21))))); break; }
						case 226: { aux.DE *= (1.0 + aa * ab * ac); break; }
						case 227: { { float lp=fmod(r*aa, ab); aux.DE*=(1.0+ac*native_sin(M_PI_F*lp/fmax(ab,0.01))); } break; }
						case 228: { { float skin=native_exp(-fabs(zz2)*aa/fmax(ab,0.01)); aux.DE*=(1.0+ac*skin); } break; }
						case 229: { aux.DE *= (1.0 + aa * fabs(ab)); break; }
						case 230: { { float wn=floor(atan2(zy,zx)*aa/(2.0*M_PI_F)+0.5); aux.DE*=(1.0+ab*fabs(wn)); } break; }
						case 231: { { float tc=floor(atan2(zy,zx)*aa/(2.0*M_PI_F)+0.5); aux.DE*=(1.0+ab*fabs(tc)*native_sin(ac*r)); } break; }
						case 232: { { float vort=fabs(-aa*zy/(rr+1e-21)-(-ab*zx/(rr+1e-21))); aux.DE*=(1.0+ac*vort); } break; }
						case 233: { { float sw=2.0f/(native_exp(aa*fabs(r-ab))+native_exp(-aa*fabs(r-ab))); aux.DE*=(1.0+ac*sw); } break; }
						case 234: { { float inst=native_exp(-aa*(rr+1e-21)); aux.DE*=(1.0+ab*inst); } break; }
						case 235: { aux.DE *= (1.0 + aa / fmax(r, 1e-21)); break; }
						case 236: { { float sl=fabs(native_sqrt(zx*zx+zy*zy)); aux.DE*=(1.0+aa*native_log(sl+1e-21)*ab); } break; }
						case 237: { { float bd=native_exp(-aa*fabs(zz2-ab)); aux.DE*=(1.0+ac*bd); } break; }
						case 238: { { float wh=native_exp(-(r-aa)*(r-aa)/(fmax(ab*ab,0.01))); aux.DE*=(1.0+ac*wh); } break; }
						case 239: { aux.DE /= fmax(0.01, 1.0 - aa / fmax(r, aa + 1e-21)); break; }
						case 240: { { float jet=native_exp(-fabs(native_sqrt(zx*zx+zy*zy)-aa)/(fmax(ab,0.01))); aux.DE*=(1.0+ac*jet); } break; }
						case 241: { { float halo=1.0/(1.0+native_pow(r/fmax(aa,0.01),2.0)); aux.DE*=(1.0+ab*halo); } break; }
						case 242: { aux.DE *= native_exp(fmin(aa * ab * r, 20.0f)); break; }
						case 243: { { float cs2=native_log(fmax(fabs(native_sqrt(zx*zx+zy*zy)),1e-21)/fmax(aa,0.01)); aux.DE*=(1.0+ab*ac*cs2); } break; }
						case 244: { aux.DE *= (1.0 + aa * native_tanh(fabs(zz2 - ab) / fmax(ac, 0.01))); break; }
						case 245: { { float ylm=native_sin(aa*acos(zz2/r))*native_cos(ab*atan2(zy,zx)); aux.DE*=(1.0+ac*fabs(ylm)); } break; }
						case 246: { aux.DE *= native_exp(aa * ab); break; }
						case 247: { { float rh=aa*ab*native_exp(-ac*float(i)*0.01); aux.DE*=(1.0+rh); } break; }
						case 248: { { float ns=aa*ab*native_sin(ac*r)/(1.0+ad*r); aux.DE*=(1.0+ns); } break; }
						case 249: { { float rc=aa*native_exp(-ab/(fmax(ac*r,0.01))); aux.DE*=(1.0+rc); } break; }
						case 250: { { float sf2=1.0+aa*r; aux.DE*=sf2*native_sqrt(fmax(0.01,ab*ac/(fmax(r,1e-21)))); } break; }
						case 251: { { float sf2=fmax(0.01,1.0+aa*r); aux.DE/=sf2; } break; }
						case 252: { aux.DE *= (1.0 + aa * (1.0 - native_exp(-float(i) * 0.01 / fmax(ab, 0.01)))); break; }
						case 253: { { float bn=native_exp(-aa*rr)*ab; aux.DE*=(1.0+bn); } break; }
						case 254: { { float fv=aa*native_exp(-ab*rr); aux.DE*=(1.0+fv); } break; }
						case 255: { { float op=native_sin(aa*r)*native_sin(aa*r); aux.DE*=(1.0+ab*op); } break; }
						case 256: { { float d=fabs(r-aa); aux.DE*=fmax(0.01,native_pow(d+1e-21,-ab)); } break; }
						case 257: { aux.DE *= (1.0 + aa * native_log(fmax(ab, 0.01) / fmax(r, 1e-21))); break; }
						case 258: { { float div=(native_sin(aa*(zx+0.01))-native_sin(aa*zx))/0.01; aux.DE*=(1.0+ab*fabs(div)); } break; }
						case 259: { { float vev=aa*r*r; aux.DE*=(1.0+ab*vev); } break; }
						case 260: { { float grd=(native_sin(aa*(r+0.01))-native_sin(aa*r))/0.01; aux.DE*=(1.0+ab*fabs(grd)); } break; }
						case 261: { aux.DE *= (1.0 + aa * ab * rr); break; }
						case 262: { { float a2=native_sin(aa*zx)*native_sin(aa*zx)+native_sin(ab*zy)*native_sin(ab*zy); aux.DE*=(1.0+ac*ad*a2); } break; }
						case 263: { { float psi2=native_sin(aa*r)*native_sin(aa*r); aux.DE*=(1.0+ab*psi2); } break; }
						case 264: { { float phi=native_sin(aa*r); aux.DE*=(1.0+ab*phi*phi+ac*phi*phi*phi*phi); } break; }
						case 265: { { float tmn=(zx*zx+zy*zy+zz2*zz2)/(rr+1e-21); aux.DE*=(1.0+aa*ab*tmn); } break; }
						case 266: { { float sp=native_sin(aa*zx)*native_cos(ab*zy); aux.DE*=(1.0+ac*fabs(sp)); } break; }
						case 267: { { float rs=native_sin(aa*r)*fabs(native_cos(ab*atan2(zy,zx))); aux.DE*=(1.0+ac*rs*rs); } break; }
						case 268: { { float kr=native_sin(aa*zx)*native_sin(ab*zy)-native_cos(aa*zx)*native_cos(ab*zy); aux.DE*=(1.0+ac*kr*kr); } break; }
						case 269: { { float gv=native_sin(aa*r)*native_sin(ab*r); aux.DE*=(1.0+ac*gv*gv); } break; }
						case 270: { { float xs=fabs(native_sin(aa*r)-zx); aux.DE*=(1.0+ab*xs*xs); } break; }
						case 271: { { float m5=native_sin(aa*r)*native_sin(ab*r)*native_sin(ac*r); aux.DE*=(1.0+ad*m5*m5); } break; }
						case 272: { { float wf2=native_exp(-aa*fabs(zz2)); aux.DE*=(1.0+ab*ac*wf2); } break; }
						case 273: { { float kk=native_sin(aa*r/fmax(ab,0.01))*native_sin(ac*r/fmax(ab,0.01)); aux.DE*=(1.0+ad*kk); } break; }
						case 274: { aux.DE *= native_exp(-aa * fabs(zz2 - ab)); break; }
						case 275: { { float av=r>1e-21?(fabs(zx)+fabs(zy)+fabs(zz2))/(r):1.0; aux.DE*=(1.0+aa*ab*av); } break; }
						case 276: { { float cf=1.0/(1.0+aa*rr); aux.DE*=(1.0+ab*cf); } break; }
						case 277: { { float ms=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.DE*=(1.0+aa*ms); } break; }
						case 278: { { float fw=native_exp(-aa*fabs(r-ab)*fabs(r-ab)*1000.0); aux.DE*=(1.0+ac*fw); } break; }
						case 279: { { float ee=native_sin(aa*zx)*native_sin(aa*(-zx+ab)); aux.DE*=(1.0+ac*fabs(ee)); } break; }
						case 280: { { float vol=r*r*r; aux.DE*=(1.0+aa*vol/(vol+ab+1e-21)); } break; }
						case 281: { { float ly=native_exp(aa*float(i)*0.01); aux.DE*=(1.0+ab*fmin(ly,ac)); } break; }
						case 282: { { float bv=fabs(zx-aa*native_sin(ab*zy))/(float(i)+1.0); aux.DE*=(1.0+ac*bv); } break; }
						case 283: { { float scr=native_log(fmax(aa,1.0))*ab*native_sin(ac*r); aux.DE*=(1.0+fabs(scr)*0.01); } break; }
						case 284: { { float sff=native_sin(aa*float(i)*0.1)*native_sin(ab*float(i)*0.1); aux.DE*=(1.0+ac*fabs(sff)); } break; }
						case 285: { { float goe=native_sin(aa*r)*native_cos(ab*r)*native_sin(ac*r); aux.DE*=(1.0+ad*fabs(goe)); } break; }
						case 286: { { float syk=native_sin(aa*zx)*native_sin(ab*zy)*native_sin(ac*zz2)*native_sin(ad*r); aux.DE*=(1.0+ae*fabs(syk)); } break; }
						case 287: { { float bd2=native_sin(aa*r)*native_sin(aa*r); float ent=bd2*native_log(bd2+1e-21); aux.DE*=(1.0+ab*fabs(ent)); } break; }
						case 288: { { float ml=floor(native_log(r+1e-21)/native_log(fmax(aa,1.01))); aux.DE*=(1.0+ab*native_sin(ac*ml)); } break; }
						case 289: { { float cd=floor(r*aa); float le=native_exp(-ab*cd); aux.DE*=(1.0+ac*le); } break; }
						case 290: { { float wn2=floor(atan2(zy,zx)*aa/(2.0*M_PI_F)+0.5); aux.DE*=(1.0+ab*native_sin(ac*wn2)); } break; }
						case 291: { { float sw2=floor(zx*aa+0.5)*floor(zy*ab+0.5); aux.DE*=(1.0+ac*native_sin(ad*sw2)); } break; }
						case 292: { { float cc=floor(r*aa)*3.0; aux.DE*=(1.0+ab*native_sin(ac*cc)); } break; }
						case 293: { { float pc=fmod(floor(r*aa),ab); aux.DE*=(1.0+ac*native_sin(ad*pc)); } break; }
						case 294: { { float ce=native_sin(aa*zx)*native_cos(ab*zy)*native_sin(ac*zz2); aux.DE*=(1.0+ad*fabs(ce)); } break; }
						case 295: { { float ev=native_sin(aa*r)*native_sin(aa*r)+native_cos(ab*r)*native_cos(ab*r); aux.DE*=(1.0+ac*ev*0.5); } break; }
						case 296: { { float sgn=native_sin(aa*r)>0?1.0:-1.0; float mc=native_exp(-ab*rr)*sgn; aux.DE*=(1.0+ac*fabs(mc)); } break; }
						case 297: { { float pur=native_sin(aa*r)*native_sin(aa*r); aux.DE*=(1.0+ab*pur*pur); } break; }
						case 298: { { float wig=native_sin(aa*zx)*native_cos(ab*zy); aux.DE*=(1.0+ac*fabs(wig)); } break; }
						case 299: { { float hus=native_exp(-aa*(zx*zx+zy*zy))*native_sin(ab*r); aux.DE*=(1.0+ac*fabs(hus)); } break; }
						case 300: { { float mi=native_sin(aa*r)*native_sin(ab*r); aux.DE*=(1.0+ac*mi*mi); } break; }
					case 301: { float psi = native_sin(aa*r + ab*z.x); aux.DE *= (1.0 + af * psi*psi); break; }
					case 302: { float psi_f = native_cos(aa*r); float psi_i = native_sin(ab*r); float overlap = psi_f*psi_i + 1e-21; float wv = (psi_f*native_sin(ac*z.x)) / overlap; aux.DE *= (1.0 + af * fabs(wv)); break; }
					case 303: { float rate = fabs(aa); float variance = z.x*z.x + z.y*z.y; aux.DE *= (1.0 + af * native_exp(-rate * (float)i * 0.01 * variance)); break; }
					case 304: { float E = aa*r; float t = (float)i * 0.01; aux.DE *= (1.0 + af * fabs(ab) * native_sin(E*t)*native_sin(E*t)); break; }
					case 305: { float path1 = native_sin(aa*z.x + ab*z.y); float path2 = native_sin(ac*z.x - ab*z.y); aux.DE *= (1.0 + af * fabs(path1 - path2)); break; }
					case 306: { float choice_time = fabs(aa) * 10.0; float theta = (float)i > choice_time ? 1.0 : 0.0; aux.DE *= (1.0 + af * ab * theta); break; }
					case 307: { float visibility = native_cos(aa*r)*native_cos(aa*r); float erased = native_sin(ab*z.x + ac*z.y); aux.DE *= (1.0 + af * visibility * erased*erased); break; }
					case 308: { float source = native_sin(aa*z.x + ab*z.y + ac*z.z); float target = native_sin(aa*(z.x+ad) + ab*(z.y+ae) + ac*(z.z+aff)); float fidelity = source*target; aux.DE *= (1.0 + af * fabs(fidelity)); break; }
					case 309: { float psi = native_sin(aa*r); float clone = native_sin(aa*r + ab*0.1); float fidelity = 1.0 - (psi-clone)*(psi-clone)*0.5; aux.DE *= (1.0 + af * fmax(fidelity, 0.0)); break; }
					case 310: { float Iz = native_sin(aa*z.x)*native_sin(ab*z.y); float classical = native_sin(aa*z.x)*0.5; float discord = fabs(Iz - classical); aux.DE *= (1.0 + af * discord); break; }
					case 311: { float epr = native_sin(aa*z.x)*native_cos(ab*z.y) - native_cos(aa*z.x)*native_sin(ab*z.y); aux.DE *= (1.0 + af * fabs(epr)); break; }
					case 312: { float v1 = native_sin(aa*z.x)*native_sin(aa*z.y); float v2 = native_cos(ab*z.y)*native_cos(ab*z.z); float violation = fabs(v1 + v2) - 1.0; aux.DE *= (1.0 + af * fmax(violation, 0.0)); break; }
					case 313: { float ca = native_cos(aa*z.x); float cb = native_cos(ab*z.y); float corr = ca*cb + ca*native_sin(ab*z.y) + native_sin(aa*z.x)*cb - native_sin(aa*z.x)*native_sin(ab*z.y); aux.DE *= (1.0 + af * fabs(corr) * 0.25); break; }
					case 314: { float S = 2.0*native_sqrt(2.0)*native_sin(aa*r)*native_cos(ab*r); float violation = fmax(fabs(S) - 2.0, 0.0); aux.DE *= (1.0 + af * violation); break; }
					case 315: { float bound = 2.0*native_sqrt(2.0); float corr = bound * native_cos(aa*r) * native_sin(ab*z.x); aux.DE *= (1.0 + af * fabs(corr) / bound); break; }
					case 316: { float t1 = native_sin(aa*(float)i*0.1); float t2 = native_sin(aa*((float)i+ab)*0.1); float temporal = t1*t2 + t1*native_sin(aa*((float)i+ac)*0.1); aux.DE *= (1.0 + af * fabs(temporal)); break; }
					case 317: { float rho = native_sin(aa*z.x)*native_sin(aa*z.x) + native_cos(ab*z.y)*native_cos(ab*z.y); float witness = rho - ac; aux.DE *= (1.0 + af * fmax(-witness, 0.0)); break; }
					case 318: { float dpsi = aa*native_cos(aa*r + ab*z.x); float fisher = 4.0*dpsi*dpsi; aux.DE *= (1.0 + af * fisher / (1.0 + fisher)); break; }
					case 319: { float F_Q = 4.0*(aa*native_cos(aa*r))*(aa*native_cos(aa*r)); float bound = 1.0/native_sqrt(fmax(ab*F_Q, 1e-21)); aux.DE *= (1.0 + af * bound); break; }
					case 320: { float N = fmax(fabs(aa)*10.0, 1.0); float dphi = 1.0/(N*native_sqrt(fmax(fabs(ab), 1e-21))); float sql = 1.0/native_sqrt(N); float gain = (sql*sql)/(dphi*dphi+1e-21); aux.DE *= (1.0 + af * fmin(gain, 10.0) * native_sin(ac*r)*native_sin(ac*r)); break; }
					case 321: { float T2 = fabs(aa) + 0.01; float sensitivity = 1.0/(ab*native_sqrt(T2)+1e-21); aux.DE *= (1.0 + af * native_sin(ac*r)*native_sin(ac*r) * fmin(sensitivity, 10.0)); break; }
					case 322: { float lambda_r = fabs(aa)+0.1; float NA = fabs(ab)+0.1; float N_ph = fmax(fabs(ac)*10, 1.0); float res = lambda_r/(2.0*NA*native_sqrt(N_ph)); aux.DE *= (1.0 + af * native_sin(r/fmax(res,0.01))*native_sin(r/fmax(res,0.01))); break; }
					case 323: { float N = fmax(fabs(aa)*5, 1.0); float pattern = native_sin(N*ab*z.x)*native_sin(N*ab*z.y); aux.DE *= (1.0 + af * pattern*pattern); break; }
					case 324: { float snr_q = native_exp(-aa*r*r); float snr_c = native_exp(-ab*r*r); float advantage = snr_q/(snr_c+1e-21); aux.DE *= (1.0 + af * fmin(advantage, 10.0)); break; }
					case 325: { float tau = fabs(aa)*r; float N_s = fmax(fabs(ab), 0.1); float N_i = fmax(fabs(ac), 0.1); float range_res = tau/(2.0*native_sqrt(N_s*N_i)+1e-21); aux.DE *= (1.0 + af * native_sin(range_res)*native_sin(range_res)); break; }
					case 326: { float omega_rot = aa*z.x + ab*z.y; float phase = ac*omega_rot; aux.DE *= (1.0 + af * native_sin(phase)*native_sin(phase)); break; }
					case 327: { float g_eff = aa; float T = fabs(ab)+0.01; float phase = g_eff*T*T*ac; aux.DE *= (1.0 + af * native_cos(phase)*native_cos(phase)); break; }
					case 328: { float omega0 = fabs(aa)*100.0+1.0; float tau_c = fabs(ab)+0.01; float stability = 1.0/(omega0*native_sqrt(tau_c*(float)(i+1)*0.01)+1e-21); aux.DE *= (1.0 + af * fmin(stability*ac, 5.0)); break; }
					case 329: { float B = aa*z.x + ab*z.y + ac*z.z; float sensitivity = native_sin(ad*B); aux.DE *= (1.0 + af * sensitivity*sensitivity); break; }
					case 330: { float k_eff = aa; float T = fabs(ab)+0.01; float accel = k_eff*T*T*ac*r; aux.DE *= (1.0 + af * native_sin(accel)*native_sin(accel)); break; }
					case 331: { float T_eff = fabs(aa)*r + 0.01; float C = fabs(ab)+0.1; float dE = fabs(ac)+0.01; float res = T_eff*T_eff/(C*dE); aux.DE *= (1.0 + af * fmin(res, 10.0)); break; }
					case 332: { float pressure = aa*r*r + ab*z.x; float sensitivity = native_sin(ac*pressure); aux.DE *= (1.0 + af * sensitivity*sensitivity); break; }
					case 333: { float dL = aa*(z.x - z.y); float L = fmax(r, 0.01); float strain = dL/L; float gauge = ab*strain; aux.DE *= (1.0 + af * native_sin(gauge)*native_sin(gauge)); break; }
					case 334: { float omega0 = fabs(aa)+0.1; float Q = fabs(ab)+1.0; float force = ac/(2.0*Q*omega0+1e-21); aux.DE *= (1.0 + af * native_sin(force*r)*native_sin(force*r)); break; }
					case 335: { float torque = aa*z.x*z.y - ab*z.y*z.z; float thermal = fabs(ac)+0.01; aux.DE *= (1.0 + af * fabs(torque)/(thermal+fabs(torque))); break; }
					case 336: { float E_field = aa*z.x + ab*z.y + ac*z.z; float rydberg = native_sin(ad*E_field*E_field); aux.DE *= (1.0 + af * rydberg*rydberg); break; }
					case 337: { float V_jj = aa*native_sin(ab*r); float josephson = native_cos(ac*V_jj); aux.DE *= (1.0 + af * (1.0 - josephson*josephson)); break; }
					case 338: { float tunnel = native_exp(-aa*fabs(r-ab)); float current = ac*tunnel; aux.DE *= (1.0 + af * fabs(current)); break; }
					case 339: { float n = floor(fabs(aa)*r*5.0+0.5); float R_H = 1.0/(fmax(n,1.0)*ab+1e-21); aux.DE *= (1.0 + af * fmin(R_H, 10.0)); break; }
					case 340: { float C_q = aa*aa/(2.0*(fabs(ab)+0.01)); float charging = native_exp(-C_q*r*r); aux.DE *= (1.0 + af * charging); break; }
					case 341: { float flux = aa*z.x*z.y; float inductance = native_cos(ab*flux); aux.DE *= (1.0 + af * inductance*inductance); break; }
					case 342: { float L_q = fabs(aa)+0.01; float C_q = fabs(ab)+0.01; float Z = native_sqrt(L_q/C_q); float match = 1.0/(1.0 + (Z-ac)*(Z-ac)); aux.DE *= (1.0 + af * match); break; }
					case 343: { float omega = aa*r; float n_th = 1.0/(native_exp(fabs(ab)*omega+1e-21)-1.0+1e-21); float psd = omega*(n_th+0.5); aux.DE *= (1.0 + af * fmin(fabs(psd), 10.0)); break; }
					case 344: { float dE = fabs(aa)*r; float tau = fmax(fabs(ab),0.01); float uncertainty = dE*tau; aux.DE *= (1.0 + af * native_exp(-uncertainty)); break; }
					case 345: { float W = aa*r*r; float T_eff = fmax(fabs(ab), 0.01); float jarzynski = native_exp(-W/T_eff); aux.DE *= (1.0 + af * jarzynski); break; }
					case 346: { float Q_heat = aa*r; float T_eff = fmax(fabs(ab), 0.01); float C = fmax(fabs(ac), 0.01); float fluct = Q_heat/(T_eff*T_eff*C+1e-21); aux.DE *= (1.0 + af * native_exp(-fabs(fluct))); break; }
					case 347: { float sigma = fabs(aa)*r*r; float relax = fmax(fabs(ab), 0.01); float prod = sigma/relax; aux.DE *= (1.0 + af * (1.0 - native_exp(-prod))); break; }
					case 348: { float W = aa*(z.x*z.x + z.y*z.y); float T_eff = fmax(fabs(ab), 0.01); float ratio = native_exp(-W/T_eff); aux.DE *= (1.0 + af * fmin(ratio, 10.0)); break; }
					case 349: { float info = fabs(native_sin(aa*z.x)*native_cos(ab*z.y)); float work = ac*info*native_log(2.0); aux.DE *= (1.0 + af * fabs(work)/(1.0+fabs(work))); break; }
					case 350: { float W = fabs(aa)*native_log(2.0)*native_sin(ab*r)*native_sin(ab*r); aux.DE *= (1.0 + af * W); break; }
					case 351: { float T_hot = fmax(fabs(aa)*r, 0.01); float T_cold = fmax(fabs(ab)*0.5, 0.001); float eff = 1.0 - T_cold/T_hot; float qcorr = native_sin(ac*r)*native_sin(ac*r); aux.DE *= (1.0 + af * fabs(eff) * qcorr); break; }
					case 352: { float w_cold = fabs(aa)+0.1; float w_hot = fabs(ab)+0.2; float eff = 1.0 - w_cold/w_hot; float adiabatic = native_cos(ac*r)*native_cos(ac*r); aux.DE *= (1.0 + af * fabs(eff) * adiabatic); break; }
					case 353: { float V_ratio = fmax(fabs(aa), 0.1)/fmax(fabs(ab), 0.1); float T_ratio = fmax(fabs(ac), 0.1)/fmax(fabs(ad), 0.1); float eff = native_log(fmax(V_ratio,1e-21f))/(native_log(fmax(T_ratio,1e-21f))+1e-21f); aux.DE *= (1.0 + af * fmin(fabs(eff), 5.0) * native_sin(r)*native_sin(r)); break; }
					case 354: { float gamma_g = 1.4; float ratio = fmax(fabs(aa), 0.1); float eff = 1.0 - (pow(ratio, gamma_g)-1.0)/(gamma_g*(ratio-1.0)+1e-21); aux.DE *= (1.0 + af * fabs(eff) * native_sin(ab*r)*native_sin(ab*r)); break; }
					case 355: { float P_ratio = fmax(fabs(aa), 0.1); float gamma_g = 1.4; float eff = 1.0 - pow(1.0/P_ratio, (gamma_g-1.0)/gamma_g); aux.DE *= (1.0 + af * fabs(eff) * native_cos(ab*r)*native_cos(ab*r)); break; }
					case 356: { float T_ratio = fmax(fabs(aa)+0.1, 0.01) / fmax(fabs(ab)+0.1, 0.01); float regen = fmin(fabs(ac), 1.0); float eff = (1.0 - 1.0/T_ratio) * regen; aux.DE *= (1.0 + af * fabs(eff)); break; }
					case 357: { float expansion = fmax(fabs(aa), 0.1); float T_ratio = fmax(fabs(ab)+0.1, 0.01)/fmax(fabs(ac)+0.1, 0.01); float eff = (1.0 - 1.0/T_ratio)*expansion/(expansion+1.0); aux.DE *= (1.0 + af * fabs(eff) * native_sin(ad*r)*native_sin(ad*r)); break; }
					case 358: { float T_ratio = fmax(fabs(aa)+0.1,0.01)/fmax(fabs(ab)+0.1,0.01); float loss = 1.0-fmin(fabs(ac),0.99); float eff = (1.0-1.0/T_ratio)*loss; aux.DE *= (1.0 + af * fabs(eff) * native_cos(ad*r)*native_cos(ad*r)); break; }
					case 359: { float T_cold = fmax(fabs(aa),0.01); float T_hot = fmax(fabs(ab),0.02); float cop = T_cold/(T_hot-T_cold+1e-21); float qcop = cop*native_sin(ac*r)*native_sin(ac*r); aux.DE *= (1.0 + af * fmin(fabs(qcop),10.0)); break; }
					case 360: { float T_hot = fmax(fabs(aa),0.02); float T_cold = fmax(fabs(ab),0.01); float cop = T_hot/(T_hot-T_cold+1e-21); float enhance = native_cos(ac*r)*native_cos(ac*r); aux.DE *= (1.0 + af * fmin(cop*enhance,10.0)); break; }
					case 361: { float k = aa; float Gamma = fabs(ab)+0.01; float delta = fabs(ac)+0.01; float cooling = Gamma/(2.0*(1.0 + 4.0*delta*delta/(Gamma*Gamma))); aux.DE *= (1.0 + af * cooling * native_sin(k*r)*native_sin(k*r)); break; }
					case 362: { float U0 = aa; float delta = fabs(ab)+0.01; float pol_grad = native_sin(ac*z.x)*native_cos(ac*z.y); float eff = U0/(delta+1e-21)*pol_grad*pol_grad; aux.DE *= (1.0 + af * fmin(fabs(eff),10.0)); break; }
					case 363: { float T_ratio = fmax(fabs(aa),0.01)/fmax(fabs(ab),0.01); float eta = fabs(ac)+1.0; float eff = pow(T_ratio, 3.0)*eta; aux.DE *= (1.0 + af * fmin(fabs(eff),10.0) * native_sin(r)*native_sin(r)); break; }
					case 364: { float m_ratio = fmax(fabs(aa),0.1)/fmax(fabs(ab),0.1); float collision = fabs(ac); float eff = m_ratio*collision; aux.DE *= (1.0 + af * fmin(eff,10.0) * native_sin(ad*r)*native_sin(ad*r)); break; }
					case 365: { float eta = fabs(aa)*0.1; float Omega = fabs(ab)+0.1; float nu_m = fabs(ac)+0.1; float eff = eta*Omega*Omega/((fabs(ad)+0.01)*nu_m); aux.DE *= (1.0 + af * fmin(eff,10.0)); break; }
					case 366: { float Sxy = native_sin(aa*z.x)*native_cos(ab*z.y); float Sxx = native_sin(aa*z.x)*native_sin(aa*z.x)+0.01; float Syy = native_cos(ab*z.y)*native_cos(ab*z.y)+0.01; float gain = Sxy*Sxy/(Sxx*Syy); aux.DE *= (1.0 + af * fabs(gain)); break; }
					case 367: { float g = fabs(aa)+0.01; float kappa = fabs(ab)+0.01; float delta = fabs(ac)+0.01; float cooling = g*g/(kappa*kappa+delta*delta); float n_ph = native_sin(ad*r)*native_sin(ad*r)*10.0; aux.DE *= (1.0 + af * cooling*fmin(n_ph,10.0)); break; }
					case 368: { float Cg = fabs(aa)+0.01; float Vg = ab; float C = fabs(ac)+0.01; float coupling = Cg*Vg/C; aux.DE *= (1.0 + af * native_sin(coupling*r)*native_sin(coupling*r)); break; }
					case 369: { float S = aa; float sigma = fabs(ab)+0.01; float T_eff = fabs(ac)*r+0.01; float kappa = fabs(ad)+0.01; float ZT = S*S*sigma*T_eff/kappa; aux.DE *= (1.0 + af * fmin(ZT,10.0)); break; }
					case 370: { float Ss = aa; float gradT = ab*z.x+ac*z.y; float spin_pol = native_sin(ad*r); aux.DE *= (1.0 + af * fabs(Ss*gradT*spin_pol)); break; }
					case 371: { float Bz = aa; float gradT = ab*z.x; float Ey = ac*gradT*Bz; aux.DE *= (1.0 + af * native_sin(Ey)*native_sin(Ey)); break; }
					case 372: { float n_level = floor(fabs(aa)*r*5.0+0.5); float conductance = fmax(n_level,1.0)*ab; aux.DE *= (1.0 + af * fmin(fabs(conductance),10.0) * native_sin(ac*r)*native_sin(ac*r)); break; }
					case 373: { float edge = native_exp(-aa*fabs(z.x)); float helical = native_sin(ab*z.y); aux.DE *= (1.0 + af * edge * helical*helical); break; }
					case 374: { float chern = floor(fabs(aa)*2.0+0.5); float mag_order = native_sin(ab*z.x)*native_sin(ab*z.y); aux.DE *= (1.0 + af * fabs(chern) * mag_order*mag_order); break; }
					case 375: { float valley = native_sin(aa*z.x)*native_cos(ab*z.y) - native_cos(aa*z.x)*native_sin(ab*z.y); float broken_inv = native_sin(ac*r); aux.DE *= (1.0 + af * fabs(valley*broken_inv)); break; }
					case 376: { float bulk_gap = fabs(aa); float surface = native_sin(ab*z.x)*native_sin(ab*z.y)*native_exp(-ac*fabs(z.z)); float k_F = ad*r; aux.DE *= (1.0 + af * bulk_gap*fabs(surface)*fmin(k_F,5.0)); break; }
					case 377: { float kx = aa*z.x; float ky = ab*z.y; float kz = ac*z.z; float chirality = kx*kx + ky*ky - kz*kz; float fermi_arc = native_exp(-fabs(chirality)*ad); aux.DE *= (1.0 + af * fermi_arc); break; }
					case 378: { float E_D = aa; float v_F = fabs(ab)+0.01; float k = ac*r; float cone = fabs(E_D)/(v_F*fmax(fabs(k),0.01)); aux.DE *= (1.0 + af * fmin(cone,10.0) * native_sin(r)*native_sin(r)); break; }
					case 379: { float xi = fmax(fabs(aa),0.01); float L = fabs(ab)*r; float overlap = native_exp(-L/xi); float gap = fabs(ac); aux.DE *= (1.0 + af * overlap*gap); break; }
					case 380: { float J = fabs(aa)+0.01; float alpha = fabs(ab)+0.01; float g = fabs(ac)+0.01; float gap = J*native_exp(-1.0/(alpha*g)); aux.DE *= (1.0 + af * gap * native_sin(ad*r)*native_sin(ad*r)); break; }
					case 381: { float J = fabs(aa)+0.01; float h = fabs(ab)+0.01; float gap = fabs(J-h)/J; float crit_exp = fabs(ac)+0.5; aux.DE *= (1.0 + af * pow(fmax(gap,1e-10), crit_exp)); break; }
					case 382: { float J = aa; float Si = native_sin(ab*z.x); float Sj = native_sin(ab*z.y); float coupling = J*Si*Sj; aux.DE *= (1.0 + af * fabs(coupling)); break; }
					case 383: { float J = aa; float Sx = native_sin(ab*z.x)*native_cos(ac*z.y); float Sy = native_cos(ab*z.x)*native_sin(ac*z.y); float coupling = J*(Sx+Sy); aux.DE *= (1.0 + af * fabs(coupling)); break; }
					case 384: { float J = aa; float q = fmax(floor(fabs(ab)*5+2), 2.0); float sigma_i = floor(native_sin(ac*z.x)*q); float sigma_j = floor(native_sin(ac*z.y)*q); float delta_s = (sigma_i == sigma_j) ? 1.0 : 0.0; aux.DE *= (1.0 + af * J*delta_s); break; }
					case 385: { float J = aa; float q = fmax(floor(fabs(ab)*5+2), 2.0); float angle = 2.0*M_PI_F/q; float sigma_diff = native_sin(ac*z.x) - native_sin(ac*z.y); aux.DE *= (1.0 + af * J*native_cos(angle*sigma_diff)); break; }
					case 386: { float J = aa; float lambda = ab; float sigma = native_sin(ac*z.x)*native_sin(ac*z.y); float tau = native_cos(ad*z.x)*native_cos(ad*z.y); float coupling = J*(sigma + tau + lambda*sigma*tau); aux.DE *= (1.0 + af * fabs(coupling)); break; }
					case 387: { float W = aa; float X = ab; float Y = ac; float sigma = native_sin(ad*z.x)*native_sin(ad*z.y); float tau = native_cos(ad*z.x)*native_cos(ad*z.y); float v = W*sigma + X*tau + Y*sigma*tau; aux.DE *= (1.0 + af * fabs(v)); break; }
					case 388: { float U = fabs(aa)+0.01; float t = fabs(ab)+0.01; float n_up = native_sin(ac*z.x)*native_sin(ac*z.x); float n_down = native_cos(ac*z.y)*native_cos(ac*z.y); float mott = U*n_up*n_down/t; aux.DE *= (1.0 + af * fmin(mott,10.0)); break; }
					case 389: { float t = fabs(aa)+0.01; float J = ab; float hop = t*native_sin(ac*z.x)*native_cos(ac*z.y); float exchange = J*native_sin(ad*z.x)*native_sin(ad*z.y); aux.DE *= (1.0 + af * fabs(hop + exchange)); break; }
					case 390: { float xi_loc = fmax(fabs(aa),0.01); float disorder = fabs(ab); float loc = native_exp(-r/xi_loc)*disorder; aux.DE *= (1.0 + af * loc); break; }
					case 391: { float U = fabs(aa)+0.01; float U_c = fabs(ab)+0.01; float n = native_sin(ac*r)*0.5+0.5; float gap = (U/U_c)*(n-0.5)*(n-0.5); aux.DE *= (1.0 + af * fmin(gap*4.0,10.0)); break; }
					case 392: { float alpha = aa; float u = ab; float k_F = ac; float gap = 2.0*fabs(alpha*u)*fabs(native_cos(2.0*k_F*z.x)); aux.DE *= (1.0 + af * fmin(gap,10.0)); break; }
					case 393: { float J = fabs(aa)+0.01; float g = fabs(ab)+0.01; float gap = J*native_exp(-M_PI_F*J/(g*g)); float singlet = native_cos(ac*z.x)*native_cos(ac*z.y); aux.DE *= (1.0 + af * gap*singlet*singlet); break; }
					case 394: { float J = fabs(aa)+0.01; float S = fmax(floor(fabs(ab)+1),1.0); float gap = J*native_exp(-M_PI_F*S); float string_order = native_sin(ac*r); aux.DE *= (1.0 + af * gap*string_order*string_order); break; }
					case 395: { float J = fabs(aa)+0.01; float SiSj = native_sin(ab*z.x)*native_sin(ab*z.y); float SiSj2 = SiSj*SiSj; float aklt = J*(SiSj + SiSj2/3.0); aux.DE *= (1.0 + af * fabs(aklt)); break; }
					case 396: { float J = fabs(aa)+0.01; float Av = native_sin(ab*z.x)*native_sin(ab*z.y); float Bp = native_cos(ac*z.x)*native_cos(ac*z.y); float toric = 4.0*J*(Av*Av + Bp*Bp); aux.DE *= (1.0 + af * fmin(toric,10.0)); break; }
					case 397: { float F1 = native_sin(aa*z.x); float F2 = native_sin(ab*z.y); float F3 = native_cos(ac*z.x); float F4 = native_cos(ad*z.y); float wen = F1*F2*F3*F4; aux.DE *= (1.0 + af * fabs(wen)); break; }
					case 398: { float sn = native_sin(aa*z.x+ab*z.y); float fusion = sn*sn; float F_sym = native_cos(ac*r)*native_cos(ac*r); float lw = fusion*F_sym; aux.DE *= (1.0 + af * lw); break; }
					case 399: { float psi = native_sin(aa*z.x + ab*(float)i*0.1); float coin = native_cos(ac*z.y); float walker = psi*psi*coin*coin; aux.DE *= (1.0 + af * walker); break; }
					case 400: { float rule = native_sin(aa*z.x)*native_sin(ab*z.y)*native_cos(ac*z.z); float evolution = native_cos(ad*(float)i*0.1); float qca = rule*evolution; aux.DE *= (1.0 + af * qca*qca); break; }
					}
				}


			// v7.10 [GPU] — Noise & Procedural DE system (per-section iteration range)
			if (i >= mut->noiseIterStart && i < mut->noiseIterStop && mut->noiseType != 0)
			{
				float na = mut->noiseParamA, nb = mut->noiseParamB, nc = mut->noiseParamC, nd = mut->noiseParamD;
				float nf = mut->noiseFactor, nfq = mut->noiseFreq, nam = mut->noiseAmp;
				float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
				switch(mut->noiseType) {
					case 1: { float h = native_sin(na*z.x*12.9898 + nb*z.y*78.233 + nc*z.z*45.164)*43758.5453; h = h - floor(h); aux.DE *= (1.0 + nf*h); break; }
					case 2: { float h1 = native_sin(na*z.x*12.9898 + z.y*78.233)*43758.5453; h1=h1-floor(h1); float h2 = native_sin(z.y*12.9898 + na*z.z*78.233)*43758.5453; h2=h2-floor(h2); aux.DE *= (1.0 + nf*(h1+h2)*0.5); break; }
					case 3: { float p = na*z.x + nb*z.y + nc*z.z; float h = native_sin(p*127.1)*43758.5453; h=h-floor(h); float h2 = native_sin(p*269.5)*43758.5453; h2=h2-floor(h2); aux.DE *= (1.0 + nf*fabs(h-h2)); break; }
					case 4: { float fx = z.x*nfq; float fy = z.y*nfq; float fz = z.z*nfq; float ix = floor(fx); float iy = floor(fy); float iz = floor(fz); float tx = fx-ix; float ty = fy-iy; float tz = fz-iz; float h000 = native_sin(ix*127.1+iy*311.7+iz*74.7)*43758.5453; h000=h000-floor(h000); float h100 = native_sin((ix+1)*127.1+iy*311.7+iz*74.7)*43758.5453; h100=h100-floor(h100); float v = h000*(1.0-tx) + h100*tx; aux.DE *= (1.0 + nf*v); break; }
					case 5: { float fx = z.x*nfq; float fy = z.y*nfq; float h00 = native_sin(floor(fx)*127.1+floor(fy)*311.7)*43758.5453; h00=h00-floor(h00); float h10 = native_sin((floor(fx)+1)*127.1+floor(fy)*311.7)*43758.5453; h10=h10-floor(h10); float h01 = native_sin(floor(fx)*127.1+(floor(fy)+1)*311.7)*43758.5453; h01=h01-floor(h01); float h11 = native_sin((floor(fx)+1)*127.1+(floor(fy)+1)*311.7)*43758.5453; h11=h11-floor(h11); float tx=fx-floor(fx); float ty=fy-floor(fy); float v = h00*(1-tx)*(1-ty)+h10*tx*(1-ty)+h01*(1-tx)*ty+h11*tx*ty; aux.DE *= (1.0 + nf*v); break; }
					case 6: { float h = native_sin(z.x*na*12.9898 + z.y*nb*78.233 + z.z*nc*45.164 + nd*i)*43758.5453; h=h-floor(h); h = h*h*(3.0-2.0*h); aux.DE *= (1.0 + nf*h); break; }
					case 7: { float h = native_sin(z.x*nfq + z.y*nfq*1.3 + z.z*nfq*0.7)*43758.5453; h=h-floor(h); h = 6.0*h*h*h*h*h - 15.0*h*h*h*h + 10.0*h*h*h; aux.DE *= (1.0 + nf*h); break; }
					case 8: { float p = na*z.x*nfq + nb*z.y*nfq + nc*z.z*nfq; float h = native_sin(p)*0.5+0.5; aux.DE *= (1.0 + nf*h*h); break; }
					case 9: { float h1 = native_sin(z.x*nfq*12.9898)*43758.5453; h1=h1-floor(h1); float h2 = native_sin(z.y*nfq*78.233)*43758.5453; h2=h2-floor(h2); float h3 = native_sin(z.z*nfq*45.164)*43758.5453; h3=h3-floor(h3); aux.DE *= (1.0 + nf*(h1*h2*h3)); break; }
					case 10: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float h = native_sin(r*nfq)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h); break; }
					case 11: { float gx = native_sin(z.x*nfq*127.1+z.y*311.7)*2.0-1.0; float gy = native_sin(z.y*nfq*269.5+z.z*183.3)*2.0-1.0; float gz = native_sin(z.z*nfq*419.2+z.x*371.9)*2.0-1.0; float v = (gx*z.x+gy*z.y+gz*z.z)*nam; aux.DE *= (1.0 + nf*native_sin(v)); break; }
					case 12: { float px = z.x*nfq; float py = z.y*nfq; float g1 = native_sin(floor(px)*127.1+floor(py)*311.7)*2.0-1.0; float g2 = native_sin((floor(px)+1)*127.1+floor(py)*311.7)*2.0-1.0; float t = px-floor(px); t = t*t*(3.0-2.0*t); float v = g1*(1.0-t)+g2*t; aux.DE *= (1.0 + nf*v); break; }
					case 13: { float px = z.x*nfq; float py = z.y*nfq; float pz = z.z*nfq; float g = native_sin(px*127.1+py*311.7+pz*74.7)*2.0-1.0; float t = g*g*(3.0-2.0*g); aux.DE *= (1.0 + nf*t*nam); break; }
					case 14: { float v = native_sin(z.x*nfq)*native_cos(z.y*nfq*1.3)*native_sin(z.z*nfq*0.7); aux.DE *= (1.0 + nf*v*nam); break; }
					case 15: { float v1 = native_sin(z.x*nfq+z.y*nfq*0.5); float v2 = native_sin(z.y*nfq*1.3+z.z*nfq*0.7); float v3 = native_sin(z.z*nfq*0.9+z.x*nfq*1.1); aux.DE *= (1.0 + nf*(v1+v2+v3)/3.0); break; }
					case 16: { float px = z.x*nfq; float h = native_sin(px*12.9898+z.y*nfq*78.233)*43758.5453; h=h-floor(h); float g = (h*2.0-1.0)*(px-floor(px)); aux.DE *= (1.0 + nf*g); break; }
					case 17: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float th = atan2(z.y,z.x); float v = native_sin(r*nfq+th*na)*nam; aux.DE *= (1.0 + nf*v); break; }
					case 18: { float v = native_sin(z.x*nfq)*native_sin(z.y*nfq)*native_sin(z.z*nfq); v = v*v*(3.0-2.0*v); aux.DE *= (1.0 + nf*v*nam); break; }
					case 19: { float dx = native_sin(z.x*nfq*12.9898)*2.0-1.0; float dy = native_sin(z.y*nfq*78.233)*2.0-1.0; float dz = native_sin(z.z*nfq*45.164)*2.0-1.0; float v = native_sqrt(dx*dx+dy*dy+dz*dz); aux.DE *= (1.0 + nf*(v-1.0)*nam); break; }
					case 20: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float phi = atan2(z.y,z.x); float theta = acos(z.z/fmax(r,1e-21)); float v = native_sin(r*nfq)*native_cos(phi*na)*native_sin(theta*nb); aux.DE *= (1.0 + nf*v); break; }
					case 21: { float v=0, a=nam, f=nfq; for(int k=0;k<4;k++){ v += a*native_sin(z.x*f*12.9898+z.y*f*78.233+z.z*f*45.164); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 22: { float v=0, a=nam, f=nfq; for(int k=0;k<6;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 23: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*fabs(h*2.0-1.0); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 24: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*(1.0-fabs(h*2.0-1.0)); f*=na; a*=nb; } aux.DE *= (1.0 + nf*v); break; }
					case 25: { float v=0, a=nam, f=nfq, px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ float h=native_sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; float d=native_sin(px*f*269.5+py*f*183.3)*43758.5453; d=d-floor(d); px+=d*na; py+=d*nb; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 26: { float v=0, a=1.0, f=nfq, mx=0; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; mx+=a; f*=2.0; a*=0.5; } v/=fmax(mx,1e-21); aux.DE *= (1.0 + nf*v*nam); break; }
					case 27: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h1=native_sin(z.x*f+z.y*f*1.3)*0.5+0.5; float h2=native_sin(z.y*f*0.7+z.z*f*1.1)*0.5+0.5; v+=a*fmin(h1,h2); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 28: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h1=native_sin(z.x*f+z.y*f*1.3)*0.5+0.5; float h2=native_sin(z.y*f*0.7+z.z*f*1.1)*0.5+0.5; v+=a*fmax(h1,h2); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 29: { float v=0, a=nam, f=nfq; float cs=native_cos(nd*M_PI_F/180.0), sn=native_sin(nd*M_PI_F/180.0); float px=z.x,py=z.y; for(int k=0;k<5;k++){ float h=native_sin(px*f*127.1+py*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; float nx=px*cs-py*sn; py=px*sn+py*cs; px=nx; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 30: { float v=0, a=nam, f=nfq; for(int k=0;k<6;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*native_sin(h*M_PI_F); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 31: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float r2=z.x*z.x+z.y*z.y+z.z*z.z; float h=native_sin(r2*f)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 32: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f)*native_cos(z.y*f)*native_sin(z.z*f); v+=a*h; f*=na; a*=nb; } aux.DE *= (1.0 + nf*v); break; }
					case 33: { float v=0, w=1.0, f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=w*h; w*=h; f*=2.0; } aux.DE *= (1.0 + nf*v*nam); break; }
					case 34: { float v=1.0, f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v*=(h*0.5+0.75); f*=2.0; } aux.DE *= (1.0 + nf*(v-1.0)*nam); break; }
					case 35: { float v=0, a=nam, f=nfq; float px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ float h=native_sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; px=fabs(px)*2.0-na; py=fabs(py)*2.0-nb; pz=fabs(pz)*2.0-nc; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 36: { float md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=floor(z.x*nfq)+dx+0.5; float cy=floor(z.y*nfq)+dy+0.5; float cz=floor(z.z*nfq)+dz+0.5; float h=native_sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h*0.5; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md)md=d; } aux.DE *= (1.0 + nf*native_sqrt(md)*nam); break; }
					case 37: { float md1=1e10,md2=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=floor(z.x*nfq)+dx; float cy=floor(z.y*nfq)+dy; float cz=floor(z.z*nfq)+dz; float h=native_sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md1){md2=md1;md1=d;}else if(d<md2)md2=d; } aux.DE *= (1.0 + nf*(native_sqrt(md2)-native_sqrt(md1))*nam); break; }
					case 38: { float md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ float cx=floor(z.x*nfq)+dx+0.5; float cy=floor(z.y*nfq)+dy+0.5; float h=native_sin(cx*127.1+cy*311.7)*43758.5453; h=h-floor(h); cx+=h*0.5; float d=fabs(z.x*nfq-cx)+fabs(z.y*nfq-cy); if(d<md)md=d; } aux.DE *= (1.0 + nf*md*nam); break; }
					case 39: { float md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=floor(z.x*nfq)+dx; float cy=floor(z.y*nfq)+dy; float cz=floor(z.z*nfq)+dz; float h=native_sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; float d=fmax(fabs(z.x*nfq-cx),fmax(fabs(z.y*nfq-cy),fabs(z.z*nfq-cz))); if(d<md)md=d; } aux.DE *= (1.0 + nf*md*nam); break; }
					case 40: { float md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=floor(z.x*nfq)+dx; float cy=floor(z.y*nfq)+dy; float cz=floor(z.z*nfq)+dz; float h1=native_sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h1=h1-floor(h1); float h2=native_sin(cx*269.5+cy*183.3+cz*346.9)*43758.5453; h2=h2-floor(h2); float h3=native_sin(cx*419.2+cy*371.9+cz*529.7)*43758.5453; h3=h3-floor(h3); float d=(z.x*nfq-cx-h1)*(z.x*nfq-cx-h1)+(z.y*nfq-cy-h2)*(z.y*nfq-cy-h2)+(z.z*nfq-cz-h3)*(z.z*nfq-cz-h3); if(d<md)md=d; } aux.DE *= (1.0 + nf*native_sqrt(md)*nam); break; }
					case 41: { float md1=1e10,md2=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=floor(z.x*nfq)+dx; float cy=floor(z.y*nfq)+dy; float cz=floor(z.z*nfq)+dz; float h=native_sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md1){md2=md1;md1=d;}else if(d<md2)md2=d; } aux.DE *= (1.0 + nf*md1*md2*nam); break; }
					case 42: { float md=1e10; float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float th=atan2(z.y,z.x); for(int k=0;k<8;k++){ float a2=k*M_PI_F*2.0/8.0; float d=fabs(th-a2); if(d>M_PI_F)d=2.0*M_PI_F-d; if(d<md)md=d; } aux.DE *= (1.0 + nf*md*r*nam*nfq); break; }
					case 43: { float v=0; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=floor(z.x*nfq)+dx; float cy=floor(z.y*nfq)+dy; float cz=floor(z.z*nfq)+dz; float h=native_sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); float d=(z.x*nfq-cx-h)*(z.x*nfq-cx-h)+(z.y*nfq-cy-h)*(z.y*nfq-cy-h)+(z.z*nfq-cz-h)*(z.z*nfq-cz-h); v+=native_exp(-na*d); } aux.DE *= (1.0 + nf*(1.0-v)*nam); break; }
					case 44: { float md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=floor(z.x*nfq)+dx; float cy=floor(z.y*nfq)+dy; float cz=floor(z.z*nfq)+dz; float h=native_sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; float d=native_sqrt((z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz)); if(d<md)md=d; } float v=native_sin(md*M_PI_F*na); aux.DE *= (1.0 + nf*v*nam); break; }
					case 45: { float md=1e10,cd=0; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=floor(z.x*nfq)+dx; float cy=floor(z.y*nfq)+dy; float cz=floor(z.z*nfq)+dz; float h=native_sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md){md=d;cd=h;} } aux.DE *= (1.0 + nf*cd*nam); break; }
					case 46: { float md1=1e10,md2=1e10,md3=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=floor(z.x*nfq)+dx; float cy=floor(z.y*nfq)+dy; float cz=floor(z.z*nfq)+dz; float h=native_sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md1){md3=md2;md2=md1;md1=d;}else if(d<md2){md3=md2;md2=d;}else if(d<md3)md3=d; } aux.DE *= (1.0 + nf*(native_sqrt(md3)-native_sqrt(md1))*nam); break; }
					case 47: { float md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ float cx=floor(z.x*nfq)+dx; float cy=floor(z.y*nfq)+dy; float h=native_sin(cx*127.1+cy*311.7)*43758.5453; h=h-floor(h); cx+=h*na; float hy=native_sin(cx*269.5+cy*183.3)*43758.5453; hy=hy-floor(hy); cy+=hy*nb; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy); if(d<md)md=d; } float v = native_sin(z.z*nfq)*0.5+0.5; aux.DE *= (1.0 + nf*(native_sqrt(md)+v*nc)*nam); break; }
					case 48: { float md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=floor(z.x*nfq)+dx; float cy=floor(z.y*nfq)+dy; float cz=floor(z.z*nfq)+dz; float h=native_sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md)md=d; } md=native_sqrt(md); float v=md-floor(md*na)/na; aux.DE *= (1.0 + nf*v*nam); break; }
					case 49: { float v=0,a=nam,f=nfq; for(int k=0;k<4;k++){ float md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ float cx=floor(z.x*f)+dx; float cy=floor(z.y*f)+dy; float h=native_sin(cx*127.1+cy*311.7)*43758.5453; h=h-floor(h); cx+=h; float d=(z.x*f-cx)*(z.x*f-cx)+(z.y*f-cy)*(z.y*f-cy); if(d<md)md=d; } v+=a*native_sqrt(md); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 50: { float md=1e10; int nn = (int)fmax(2.0, fmin(na*8.0, 20.0)); for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=floor(z.x*nfq)+dx; float cy=floor(z.y*nfq)+dy; float cz=floor(z.z*nfq)+dz; for(int p=0;p<2;p++){ float h1=native_sin((cx+p*0.5)*127.1+cy*311.7+cz*74.7)*43758.5453; h1=h1-floor(h1); float h2=native_sin(cx*269.5+(cy+p*0.5)*183.3+cz*346.9)*43758.5453; h2=h2-floor(h2); float d=(z.x*nfq-cx-h1)*(z.x*nfq-cx-h1)+(z.y*nfq-cy-h2)*(z.y*nfq-cy-h2)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md)md=d; } } aux.DE *= (1.0 + nf*native_sqrt(md)*nam); break; }
					case 51: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); float r2=fabs(h*2.0-1.0); v+=a*(1.0-r2); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v*v); break; }
					case 52: { float v=0,a=nam,f=nfq,w=1.0; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); float r2=1.0-fabs(h*2.0-1.0); r2*=r2; v+=r2*a*w; w=fmin(r2*na, 1.0); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 53: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f+z.y*f*1.3+z.z*f*0.7); v+=a*fabs(h); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 54: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*fabs(native_sin(h*M_PI_F*na)); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 55: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f+z.y*f*1.3+z.z*f*0.7); float ridge=1.0-fabs(h); ridge=ridge*ridge; v+=a*ridge; f*=na; a*=nb; } aux.DE *= (1.0 + nf*v); break; }
					case 56: { float v=0,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v=fmax(v,h*nam/(1.0+k*0.5)); f*=2.0; } aux.DE *= (1.0 + nf*v); break; }
					case 57: { float v=0,a=nam,f=nfq,prev=0; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); float cur=fabs(h*2.0-1.0); v+=a*cur*prev; prev=cur; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 58: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h1=native_sin(z.x*f+z.y*f*1.3)*0.5+0.5; float h2=native_sin(z.y*f*0.7+z.z*f*1.1)*0.5+0.5; float h3=native_sin(z.z*f*0.9+z.x*f*1.5)*0.5+0.5; v+=a*(h1+h2+h3)/3.0; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*(v*2.0-1.0)); break; }
					case 59: { float v=0,a=nam,f=nfq; for(int k=0;k<6;k++){ float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float h=native_sin(r*f)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 60: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f+z.y*f*1.3+z.z*f*0.7); float billow=fabs(h)*2.0-1.0; v+=a*billow; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 61: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f+z.y*f*0.7+z.z*f*1.3)*0.5+0.5; v+=a*pow(h, na); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 62: { float v=0,a=nam,f=nfq; float px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ float h=native_sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*fabs(h*2.0-1.0); float wx=native_sin(py*f*269.5)*na; float wy=native_sin(pz*f*183.3)*nb; float wz=native_sin(px*f*419.2)*nc; px+=wx; py+=wy; pz+=wz; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 63: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); if(k%2==0) v+=a*h; else v+=a*(1.0-h); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 64: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f+z.y*f*1.3+z.z*f*0.7); float hs=h*h*sign(h); v+=a*hs; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 65: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7+nd*i)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 66: { float wx=z.x+nam*native_sin(z.y*nfq); float wy=z.y+nam*native_sin(z.z*nfq); float wz=z.z+nam*native_sin(z.x*nfq); float h=native_sin(wx*127.1+wy*311.7+wz*74.7)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h); break; }
					case 67: { float wx=z.x+nam*native_sin(z.y*nfq+z.z*nfq*0.5); float wy=z.y+nam*native_sin(z.z*nfq*1.3+z.x*nfq*0.7); float wz=z.z+nam*native_sin(z.x*nfq*0.9+z.y*nfq*1.1); float wx2=wx+nb*native_sin(wy*nfq*2.0); float wy2=wy+nb*native_sin(wz*nfq*2.0); float wz2=wz+nb*native_sin(wx*nfq*2.0); float h=native_sin(wx2*127.1+wy2*311.7+wz2*74.7)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h); break; }
					case 68: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float th=atan2(z.y,z.x)+nam*native_sin(r*nfq); float ph=acos(z.z/fmax(r,1e-21))+nb*native_cos(r*nfq*0.7); float h=native_sin(th*na+ph*nc)*0.5+0.5; aux.DE *= (1.0 + nf*h); break; }
					case 69: { float h1=native_sin(z.x*nfq*127.1+z.y*nfq*311.7)*43758.5453; h1=h1-floor(h1); float h2=native_sin(z.y*nfq*269.5+z.z*nfq*183.3)*43758.5453; h2=h2-floor(h2); float wx=z.x+(h1*2.0-1.0)*nam; float wy=z.y+(h2*2.0-1.0)*nam; float v=native_sin(wx*nfq*na+wy*nfq*nb); aux.DE *= (1.0 + nf*v); break; }
					case 70: { float v=0,f=nfq,a=nam; float px=z.x,py=z.y,pz=z.z; for(int k=0;k<4;k++){ float h=native_sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; px+=native_sin(py*f*na)*nb; py+=native_sin(pz*f*na)*nb; pz+=native_sin(px*f*na)*nb; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 71: { float wx=z.x+nam*native_sin(z.y*nfq)*native_cos(z.z*nfq*0.5); float wy=z.y+nam*native_cos(z.x*nfq*0.7)*native_sin(z.z*nfq); float v=native_sin(wx*na)*native_cos(wy*nb); aux.DE *= (1.0 + nf*v); break; }
					case 72: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float wr=r+nam*native_sin(r*nfq); float h=native_sin(wr*na*127.1)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h); break; }
					case 73: { float v=native_sin(z.x*nfq+nam*native_sin(z.y*nfq+nam*native_sin(z.z*nfq))); aux.DE *= (1.0 + nf*v); break; }
					case 74: { float t=nd*i*0.01; float wx=z.x+nam*native_sin(z.y*nfq+t); float wy=z.y+nam*native_sin(z.z*nfq+t*1.3); float wz=z.z+nam*native_sin(z.x*nfq+t*0.7); float h=native_sin(wx*127.1+wy*311.7+wz*74.7)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h); break; }
					case 75: { float scale=nfq; float wx=z.x*scale; float wy=z.y*scale; float wz=z.z*scale; for(int k=0;k<3;k++){ wx=native_sin(wx*na+wy); wy=native_cos(wy*nb+wz); wz=native_sin(wz*nc+wx); } float h=native_sin(wx+wy+wz)*0.5+0.5; aux.DE *= (1.0 + nf*h*nam); break; }
					case 76: { float h1=native_sin(z.x*nfq+z.y*nfq*0.5)*0.5+0.5; float h2=native_sin(z.y*nfq*1.3+z.z*nfq*0.7)*0.5+0.5; float v=native_sin((z.x+h1*nam)*na)*native_cos((z.y+h2*nam)*nb); aux.DE *= (1.0 + nf*v); break; }
					case 77: { float wx=z.x+nam*native_sin(nfq*z.y); float wy=z.y+nam*native_cos(nfq*z.x); float v1=native_sin(wx*na); float v2=native_cos(wy*nb); float v=v1*v2; z.x+=nf*v*nc*0.01; z.y+=nf*v*nd*0.01; aux.DE *= (1.0 + nf*fabs(v)*0.1); break; }
					case 78: { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float h=native_sin(r2*nfq)*43758.5453; h=h-floor(h); float wx=z.x*(1.0+h*nam); float wy=z.y*(1.0+h*nam); float v=native_sin(wx*na+wy*nb)*0.5+0.5; aux.DE *= (1.0 + nf*v); break; }
					case 79: { float v=0,f=nfq; for(int k=0;k<4;k++){ float h=native_sin(z.x*f+native_sin(z.y*f*na)*nam); v+=h/(1.0+k); f*=2.0; } aux.DE *= (1.0 + nf*v*0.25); break; }
					case 80: { float wx=z.x+nam*native_sin(z.y*nfq)*native_sin(z.z*nfq*0.5); float wy=z.y+nam*native_sin(z.z*nfq*0.7)*native_sin(z.x*nfq); float wz=z.z+nam*native_sin(z.x*nfq*1.3)*native_sin(z.y*nfq*0.9); float v=native_sin(wx*na)*native_sin(wy*nb)*native_sin(wz*nc); aux.DE *= (1.0 + nf*v); break; }
					case 81: { float s=(z.x+z.y+z.z)/3.0; float ix=floor(z.x+s); float iy=floor(z.y+s); float iz=floor(z.z+s); float t=(ix+iy+iz)/6.0; float x0=z.x-ix+t; float y0=z.y-iy+t; float z0=z.z-iz+t; float h=native_sin(ix*127.1+iy*311.7+iz*74.7)*43758.5453; h=h-floor(h); float v=fmax(0.0,0.6-x0*x0-y0*y0-z0*z0); v=v*v*v*v*h; aux.DE *= (1.0 + nf*v*nam*32.0); break; }
					case 82: { float s=(z.x+z.y+z.z)*nfq/3.0; float v=native_sin(s*127.1)*43758.5453; v=v-floor(v); float v2=native_sin(s*269.5)*43758.5453; v2=v2-floor(v2); aux.DE *= (1.0 + nf*(v*na+v2*nb)*0.5*nam); break; }
					case 83: { float skew=(z.x+z.y)*nfq*(native_sqrt(3.0)-1.0)/2.0; float ix=floor(z.x*nfq+skew); float iy=floor(z.y*nfq+skew); float unskew=(ix+iy)*(3.0-native_sqrt(3.0))/6.0; float x0=z.x*nfq-ix+unskew; float y0=z.y*nfq-iy+unskew; float h=native_sin(ix*127.1+iy*311.7)*43758.5453; h=h-floor(h); float t0=0.5-x0*x0-y0*y0; float v=t0>0?t0*t0*t0*t0*h:0; aux.DE *= (1.0 + nf*v*nam*70.0); break; }
					case 84: { float v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float s=(z.x*f+z.y*f+z.z*f)/3.0; float h=native_sin(s*127.1+k*519.3)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 85: { float v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float s=(z.x*f+z.y*f+z.z*f)/3.0; float h=native_sin(s*127.1+k*519.3)*43758.5453; h=h-floor(h); v+=a*fabs(h*2.0-1.0); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 86: { float v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float s=(z.x*f+z.y*f+z.z*f)/3.0; float h=native_sin(s*127.1+k*519.3)*43758.5453; h=h-floor(h); float ridge=1.0-fabs(h*2.0-1.0); ridge*=ridge; v+=a*ridge; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 87: { float s=(z.x+z.y+z.z)*nfq; float v1=native_sin(s*na)*0.5+0.5; float v2=native_sin(s*nb+M_PI_F*0.5)*0.5+0.5; float v=v1*v2; aux.DE *= (1.0 + nf*v*nam); break; }
					case 88: { float v=0; float px=z.x*nfq,py=z.y*nfq,pz=z.z*nfq; for(int k=0;k<4;k++){ float s=(px+py+pz)/3.0; float h=native_sin(s*127.1+k*91.7)*43758.5453; h=h-floor(h); v+=h*nam/(1.0+k); px+=native_sin(py)*na; py+=native_sin(pz)*nb; pz+=native_sin(px)*nc; } aux.DE *= (1.0 + nf*v*0.25); break; }
					case 89: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float th=atan2(z.y,z.x); float s=(r*nfq+th*na)/3.0; float h=native_sin(s*127.1)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h*nam); break; }
					case 90: { float v=0,f=nfq,a=nam; float cs=native_cos(nd*M_PI_F/180.0),sn=native_sin(nd*M_PI_F/180.0); float px=z.x,py=z.y; for(int k=0;k<5;k++){ float s=(px*f+py*f+z.z*f)/3.0; float h=native_sin(s*127.1+k*519.3)*43758.5453; h=h-floor(h); v+=a*h; float nx=px*cs-py*sn; py=px*sn+py*cs; px=nx; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 91: { float vn=native_sin(z.x*nfq*127.1+z.y*nfq*311.7+z.z*nfq*74.7)*43758.5453; vn=vn-floor(vn); float md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ float cx=floor(z.x*nfq)+dx; float cy=floor(z.y*nfq)+dy; float h=native_sin(cx*127.1+cy*311.7)*43758.5453; h=h-floor(h); cx+=h; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy); if(d<md)md=d; } aux.DE *= (1.0 + nf*(vn*na+native_sqrt(md)*nb)*nam); break; }
					case 92: { float v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*native_sin(h*M_PI_F*2.0*na); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 93: { float t=nd*i*0.1; float v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7+t)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 94: { float v1=0,v2=0,f=nfq,a=nam; for(int k=0;k<4;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v1+=a*h; v2+=a*fabs(h*2.0-1.0); f*=2.0; a*=0.5; } float blend=native_sin(z.x*na+z.y*nb)*0.5+0.5; aux.DE *= (1.0 + nf*(v1*blend+v2*(1.0-blend))); break; }
					case 95: { float v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); float erosion=native_exp(-na*h); v+=a*erosion; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 96: { float v=0,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); float terrace=floor(h*na+0.5)/fmax(na,1e-21); v+=terrace/(1.0+k); f*=2.0; } aux.DE *= (1.0 + nf*v*nam*0.2); break; }
					case 97: { float v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); float swiss=fabs(h*2.0-1.0); swiss=1.0-swiss*swiss; v+=a*swiss; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 98: { float v=0,f=nfq,a=nam; float px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ float h=native_sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; float wx=native_sin(py*f*na)*nb*a; float wy=native_sin(pz*f*na)*nb*a; float wz=native_sin(px*f*na)*nb*a; px+=wx; py+=wy; pz+=wz; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 99: { float v=0,f=nfq,a=nam; float offset=0; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7+offset)*43758.5453; h=h-floor(h); float r=fabs(h*2.0-1.0); r=offset+r*r*na; v+=a*r; offset=r; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 100: { float v1=0,v2=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v1+=a*h; float ridge=1.0-fabs(h*2.0-1.0); v2+=a*ridge*ridge; f*=2.0; a*=0.5; } float t=native_sin(z.x*na+z.y*nb+z.z*nc)*0.5+0.5; aux.DE *= (1.0 + nf*(v1*(1.0-t)+v2*t)); break; }
				}
			}

			// v7.10 [GPU] — Orbit Trap DE system (per-section iteration range)
			if (i >= mut->orbitIterStart && i < mut->orbitIterStop && mut->orbitTrapType != 0)
			{
				float oa = mut->orbitParamA, ob = mut->orbitParamB, oc = mut->orbitParamC, od = mut->orbitParamD;
				float of = mut->orbitFactor;
				switch(mut->orbitTrapType) {
					case 1: { float d = native_sqrt((z.x-oa)*(z.x-oa)+(z.y-ob)*(z.y-ob)+(z.z-oc)*(z.z-oc)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 2: { float d = fabs(z.x-oa)+fabs(z.y-ob)+fabs(z.z-oc); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 3: { float d = fmax(fabs(z.x-oa),fmax(fabs(z.y-ob),fabs(z.z-oc))); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 4: { float d1=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float d2=native_sqrt((z.x-oa)*(z.x-oa)+(z.y-ob)*(z.y-ob)+(z.z-oc)*(z.z-oc)); aux.DE *= (1.0 + of*native_exp(-od*fmin(d1,d2))); break; }
					case 5: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float ring=fabs(d-oa); aux.DE *= (1.0 + of*native_exp(-od*ring)); break; }
					case 6: { float dx=z.x-oa*round(z.x/fmax(oa,1e-21)); float dy=z.y-ob*round(z.y/fmax(ob,1e-21)); float dz=z.z-oc*round(z.z/fmax(oc,1e-21)); float d=native_sqrt(dx*dx+dy*dy+dz*dz); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 7: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float shell=fabs(d-oa); float shell2=fabs(d-ob); aux.DE *= (1.0 + of*native_exp(-od*fmin(shell,shell2))); break; }
					case 8: { float ph=atan2(z.y,z.x); float r=native_sqrt(z.x*z.x+z.y*z.y); float spiral_r=oa+ob*ph/(2.0*M_PI_F); float d=fabs(r-spiral_r); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 9: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float v=native_sin(d*oa*M_PI_F)*0.5+0.5; aux.DE *= (1.0 + of*v); break; }
					case 10: { int nn=(int)fmax(2,fmin(oa*6,12)); float md=1e10; for(int k=0;k<nn;k++){ float ang=k*2.0*M_PI_F/nn; float cx=ob*native_cos(ang); float cy=ob*native_sin(ang); float d=(z.x-cx)*(z.x-cx)+(z.y-cy)*(z.y-cy)+z.z*z.z; if(d<md)md=d; } aux.DE *= (1.0 + of*native_exp(-od*native_sqrt(md))); break; }
					case 11: { float d=z.x*z.x/(oa*oa+1e-21)+z.y*z.y/(ob*ob+1e-21)+z.z*z.z/(oc*oc+1e-21); d=fabs(native_sqrt(d)-1.0); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 12: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float th=atan2(z.y,z.x); float d=fabs(r-oa*(1.0+ob*native_cos(oc*th))); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 13: { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float inv_r=oa*oa/fmax(r2,1e-21); float d=fabs(inv_r-1.0)*native_sqrt(r2); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 14: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float s=native_sin(d*oa); float c=native_cos(d*ob); aux.DE *= (1.0 + of*(s*s+c*c*0.5)*native_exp(-od*d)); break; }
					case 15: { float d=fabs(z.x*oa+z.y*ob+z.z*oc)/fmax(native_sqrt(oa*oa+ob*ob+oc*oc),1e-21); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 16: { float d=native_sqrt(z.y*z.y+z.z*z.z); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 17: { float d=native_sqrt(z.x*z.x+z.z*z.z); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 18: { float d=native_sqrt(z.x*z.x+z.y*z.y); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 19: { float d=fabs(z.x*oa+z.y*ob+z.z*oc-od); aux.DE *= (1.0 + of*native_exp(-d)); break; }
					case 20: { float d=fmin(fabs(z.x),fmin(fabs(z.y),fabs(z.z))); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 21: { float d1=fabs(z.x); float d2=fabs(z.y); float d3=fabs(z.z); aux.DE *= (1.0 + of*native_exp(-od*fmin(d1,d2))*native_exp(-od*d3)); break; }
					case 22: { float d=fmin(native_sqrt(z.x*z.x+z.y*z.y),native_sqrt(z.y*z.y+z.z*z.z)); d=fmin(d,native_sqrt(z.x*z.x+z.z*z.z)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 23: { float d1=fabs(z.x-oa); float d2=fabs(z.y-ob); float d3=fabs(z.z-oc); float d=d1*d2*d3; aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 24: { float cs=native_cos(oa*M_PI_F/180.0),sn=native_sin(oa*M_PI_F/180.0); float rx=z.x*cs-z.y*sn; float ry=z.x*sn+z.y*cs; float d=fabs(ry); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 25: { float d=fmin(fabs(z.x),fabs(z.y)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 26: { float d1=fabs(z.y-oa*z.x); float d2=fabs(z.y+oa*z.x); aux.DE *= (1.0 + of*native_exp(-od*fmin(d1,d2))); break; }
					case 27: { float ph=atan2(z.y,z.x); int n=(int)fmax(3,fmin(oa,12)); float seg=2.0*M_PI_F/n; float sph=fmod(ph+M_PI_F,seg)-seg*0.5; float r=native_sqrt(z.x*z.x+z.y*z.y); float d=fabs(r*native_sin(sph)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 28: { float d1=fabs(z.x*native_sin(oa*M_PI_F/180.0)-z.y*native_cos(oa*M_PI_F/180.0)); float d2=fabs(z.x*native_sin(ob*M_PI_F/180.0)-z.y*native_cos(ob*M_PI_F/180.0)); aux.DE *= (1.0 + of*native_exp(-od*(d1+d2))); break; }
					case 29: { float d=fabs(z.z-oa*native_sin(ob*z.x)*native_cos(oc*z.y)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 30: { float r=native_sqrt(z.x*z.x+z.y*z.y); float d=fabs(z.z-oa*native_sin(ob*r)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 31: { float r=native_sqrt(z.x*z.x+z.y*z.y); float d=fabs(r-oa); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 32: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float d=fabs(r-oa); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 33: { float r=native_sqrt(z.x*z.x+z.y*z.y); float d=native_sqrt((r-oa)*(r-oa)+z.z*z.z)-ob; aux.DE *= (1.0 + of*native_exp(-od*fabs(d))); break; }
					case 34: { float r=native_sqrt(z.x*z.x+z.y*z.y); float th=atan2(z.y,z.x); float sf2=pow(fabs(native_cos(oa*th/4.0)),ob)+pow(fabs(native_sin(oa*th/4.0)),ob); float sr=oc*pow(sf2,-1.0/fmax(ob,1e-21)); float d=fabs(r-sr); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 35: { float ph=atan2(z.y,z.x); float r=native_sqrt(z.x*z.x+z.y*z.y); int n=(int)fmax(3,fmin(oa,12)); float star_r=ob*(1.0+oc*native_cos(n*ph)); float d=fabs(r-star_r); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 36: { float r=native_sqrt(z.x*z.x+z.y*z.y); float ph=atan2(z.y,z.x); float lemnR=oa*oa*native_cos(2.0*ph); float d=fabs(r*r-lemnR); aux.DE *= (1.0 + of*native_exp(-od*d*0.5)); break; }
					case 37: { float r=native_sqrt(z.x*z.x+z.y*z.y); float ph=atan2(z.y,z.x); float rose_r=oa*native_sin(ob*ph); float d=fabs(r-fabs(rose_r)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 38: { float ph=atan2(z.y,z.x); float r=native_sqrt(z.x*z.x+z.y*z.y); float spiral_r=oa*native_exp(ob*ph); float d=fabs(r-spiral_r); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 39: { float r=native_sqrt(z.x*z.x+z.y*z.y); float ph=atan2(z.y,z.x); float heart_r=oa*(1.0-native_sin(ph)); float d=fabs(r-heart_r); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 40: { float d1=native_sqrt(z.x*z.x+z.y*z.y)-oa; float d2=native_sqrt(z.y*z.y+z.z*z.z)-oa; float d3=native_sqrt(z.x*z.x+z.z*z.z)-oa; float d=fmin(fabs(d1),fmin(fabs(d2),fabs(d3))); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 41: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float d1=fabs(r-oa); float d2=fabs(r-ob); aux.DE *= (1.0 + of*native_exp(-od*d1)*native_exp(-od*d2)); break; }
					case 42: { float r=native_sqrt(z.x*z.x+z.y*z.y); float d=r*r-(oa*z.x+ob*z.y); d=fabs(d)/fmax(r+1e-21, 1e-21); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 43: { float ex=z.x*z.x/(oa*oa+1e-21); float ey=z.y*z.y/(ob*ob+1e-21); float d=fabs(ex+ey-1.0)*native_sqrt(oa*oa+ob*ob); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 44: { float r=native_sqrt(z.x*z.x+z.y*z.y); float t2=native_sqrt((r-oa)*(r-oa)+z.z*z.z); float d=fabs(t2-ob)+fabs(z.z)*oc; aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 45: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float ph=atan2(z.y,z.x); float th=acos(z.z/fmax(r,1e-21)); float d=fabs(r-oa*(1.0+ob*native_sin(oc*ph)*native_cos(od*th))); aux.DE *= (1.0 + of*native_exp(-d)); break; }
					case 46: { float d=fabs(z.x*z.x+z.y*z.y-oa*z.z*z.z); d=native_sqrt(d); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 47: { float d=fabs(z.x*z.x/fmax(oa*oa,1e-21)+z.y*z.y/fmax(ob*ob,1e-21)-z.z*z.z/fmax(oc*oc,1e-21)-1.0); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 48: { float r=native_sqrt(z.x*z.x+z.y*z.y); float ph=atan2(z.y,z.x); float cyl_r=oa+ob*native_sin(oc*z.z)*native_cos(od*ph); float d=fabs(r-cyl_r); aux.DE *= (1.0 + of*native_exp(-d)); break; }
					case 49: { float d1=fabs(fmax(fabs(z.x),fabs(z.y))-oa); float d2=fabs(fmax(fabs(z.y),fabs(z.z))-oa); float d3=fabs(fmax(fabs(z.x),fabs(z.z))-oa); float d=fmin(d1,fmin(d2,d3)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 50: { float dx=fabs(fabs(z.x)-oa); float dy=fabs(fabs(z.y)-oa); float dz=fabs(fabs(z.z)-oa); float d=dx+dy+dz; aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 51: { float d1=fabs(z.x); float d2=fabs(z.y); float d=fmin(d1,d2); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 52: { float d1=fmin(fabs(z.x),fabs(z.y)); float d2=fabs(z.z); aux.DE *= (1.0 + of*native_exp(-od*(d1+d2*oa))); break; }
					case 53: { float gx=fabs(z.x-oa*round(z.x/fmax(oa,1e-21))); float gy=fabs(z.y-ob*round(z.y/fmax(ob,1e-21))); float d=fmin(gx,gy); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 54: { float gx=fabs(z.x-oa*round(z.x/fmax(oa,1e-21))); float gy=fabs(z.y-oa*round(z.y/fmax(oa,1e-21))); float gz=fabs(z.z-oa*round(z.z/fmax(oa,1e-21))); float d=fmin(gx,fmin(gy,gz)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 55: { float cs=native_cos(oa*M_PI_F/180.0),sn=native_sin(oa*M_PI_F/180.0); float rx=z.x*cs-z.y*sn; float ry=z.x*sn+z.y*cs; float d=fmin(fabs(rx),fabs(ry)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 56: { float ph=atan2(z.y,z.x); int n=(int)fmax(3,fmin(oa,16)); float d=native_sqrt(z.x*z.x+z.y*z.y)*fabs(native_sin(n*ph*0.5)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 57: { float d1=fabs(z.x-z.y); float d2=fabs(z.x+z.y); float d=fmin(d1,d2)*0.7071; aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 58: { float gx=oa>0.001?fabs(native_sin(z.x*M_PI_F/oa)):fabs(z.x); float gy=ob>0.001?fabs(native_sin(z.y*M_PI_F/ob)):fabs(z.y); float d=gx*gy; aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 59: { float d1=fmin(fabs(z.x-oa),fabs(z.x+oa)); float d2=fmin(fabs(z.y-ob),fabs(z.y+ob)); float d3=fmin(fabs(z.z-oc),fabs(z.z+oc)); float d=fmin(d1,fmin(d2,d3)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 60: { float r=native_sqrt(z.x*z.x+z.y*z.y); float ph=atan2(z.y,z.x); int n=(int)fmax(3,fmin(oa,16)); float seg=2.0*M_PI_F/n; float sph=fmod(ph+M_PI_F+seg*0.5,seg)-seg*0.5; float d=r*fabs(native_sin(sph)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 61: { float d=fabs(z.x*z.x-z.y*z.y-oa*oa); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 62: { float hx=z.x*2.0/3.0+z.y/3.0; float hy=z.y*2.0/native_sqrt(3.0); float d=fmin(fabs(hx-round(hx)),fabs(hy-round(hy)))*oa; aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 63: { float d=native_sin(z.x*oa*M_PI_F)*native_sin(z.y*ob*M_PI_F)*native_sin(z.z*oc*M_PI_F); aux.DE *= (1.0 + of*fabs(d)); break; }
					case 64: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float ph=atan2(z.y,z.x); float th=acos(z.z/fmax(r,1e-21)); float d=fabs(native_sin(oa*ph)*native_sin(ob*th))*r; aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 65: { float gx=fabs(z.x-oa*round(z.x/fmax(oa,1e-21))); float gy=fabs(z.y-ob*round(z.y/fmax(ob,1e-21))); float d=native_sqrt(gx*gx+gy*gy); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 66: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float w=native_exp(-oa*(float)i); aux.DE *= (1.0 + of*native_exp(-od*d)*w); break; }
					case 67: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float phase=native_sin(ob*(float)i*M_PI_F/180.0)*0.5+0.5; aux.DE *= (1.0 + of*native_exp(-od*d)*phase); break; }
					case 68: { float d=native_sqrt((z.x-oa*native_sin(ob*i))*(z.x-oa*native_sin(ob*i))+(z.y-oa*native_cos(ob*i))*(z.y-oa*native_cos(ob*i))+z.z*z.z); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 69: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float trap_r=oa+ob*(float)i; float ring=fabs(d-trap_r); aux.DE *= (1.0 + of*native_exp(-od*ring)); break; }
					case 70: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(d < oa) { aux.DE *= (1.0 + of*native_exp(-od*(oa-d))); } break; }
					case 71: { float d=fabs(z.x)+fabs(z.y)+fabs(z.z); float w = (i%2==0) ? 1.0 : -0.5; aux.DE *= (1.0 + of*w*native_exp(-od*d)); break; }
					case 72: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float v=native_sin(d*oa+ob*(float)i); aux.DE *= (1.0 + of*v*v); break; }
					case 73: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float prevR=in->point.Length(); float dr=fabs(r-prevR); aux.DE *= (1.0 + of*native_exp(-od*dr)); break; }
					case 74: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float n=fmax(1.0,oa*10.0); float trap=fabs(d-round(d*n)/n)*n; aux.DE *= (1.0 + of*native_exp(-od*trap)); break; }
					case 75: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float v=1.0/(1.0+native_exp(-oa*(d-ob))); aux.DE *= (1.0 + of*(v-0.5)*2.0); break; }
					case 76: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float decay=native_exp(-oa*d); float osc=native_sin(ob*d+oc*(float)i); aux.DE *= (1.0 + of*decay*osc); break; }
					case 77: { float d=fabs(z.x*z.y)+fabs(z.y*z.z)+fabs(z.z*z.x); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 78: { float d=z.x*z.x+z.y*z.y+z.z*z.z; float v=native_exp(-oa*d)*native_sin(ob*native_sqrt(d)); aux.DE *= (1.0 + of*v); break; }
					case 79: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float ph=atan2(z.y,z.x); float d=fabs(r-oa)*fabs(native_sin(ob*ph)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 80: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float cs=native_cos(oa*(float)i*M_PI_F/180.0); float sn=native_sin(oa*(float)i*M_PI_F/180.0); float rd=fabs((z.x*cs-z.y*sn)); aux.DE *= (1.0 + of*native_exp(-od*rd)); break; }
					case 81: { float d=fabs(z.x*z.x+z.y*z.y-oa*oa*z.z); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 82: { float r=native_sqrt(z.x*z.x+z.y*z.y); float ph=atan2(z.y,z.x); float d=fabs(r-oa*fabs(native_cos(ob*ph/2.0))); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 83: { float mx=fabs(z.x); float my=fabs(z.y); float mz=fabs(z.z); if(mx<my){float t=mx;mx=my;my=t;} if(mx<mz){float t=mx;mx=mz;mz=t;} float d=mx-oa; aux.DE *= (1.0 + of*native_exp(-od*fabs(d))); break; }
					case 84: { float d1=native_sqrt(z.x*z.x+z.y*z.y)-oa; float d2=fabs(z.z)-ob; float d=native_sqrt(fmax(d1,0.0)*fmax(d1,0.0)+fmax(d2,0.0)*fmax(d2,0.0))+fmin(fmax(d1,d2),0.0); aux.DE *= (1.0 + of*native_exp(-od*fabs(d))); break; }
					case 85: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float ph=atan2(z.y,z.x); float th=acos(z.z/fmax(r,1e-21)); int nph=(int)fmax(2,oa*4); int nth=(int)fmax(2,ob*4); float dph=fabs(native_sin(nph*ph*0.5)); float dth=fabs(native_sin(nth*th*0.5)); float d=r*dph*dth; aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 86: { float d=fabs(native_sin(z.x*oa)*native_sin(z.y*ob)*native_sin(z.z*oc)); aux.DE *= (1.0 + of*d); break; }
					case 87: { float d1=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-oa; float d2=fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z)))-ob; float d=fmax(d1,-d2); aux.DE *= (1.0 + of*native_exp(-od*fabs(d))); break; }
					case 88: { float r=native_sqrt(z.x*z.x+z.y*z.y); float d=native_sqrt((r-oa)*(r-oa)+z.z*z.z); float knot=fabs(d-ob*fabs(native_sin(oc*atan2(z.z,r-oa)))); aux.DE *= (1.0 + of*native_exp(-od*knot)); break; }
					case 89: { float d=pow(fabs(z.x),oa)+pow(fabs(z.y),oa)+pow(fabs(z.z),oa); d=pow(d,1.0/fmax(oa,1e-21))-ob; aux.DE *= (1.0 + of*native_exp(-od*fabs(d))); break; }
					case 90: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float th=atan2(z.y,z.x); float d=fabs(r-oa*(native_sin(ob*th)*native_sin(ob*th)+oc)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 91: { float d1=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float d2=native_sqrt((z.x-oa)*(z.x-oa)+(z.y-ob)*(z.y-ob)+(z.z-oc)*(z.z-oc)); float d=fabs(d1-d2); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 92: { float d=fabs(z.x*z.y*z.z); d=pow(d,1.0/3.0); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 93: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float ph=atan2(z.y,z.x); float clover=oa*fabs(native_sin(ob*ph)); float d=fabs(r-clover); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 94: { float d1=fabs(z.x)-oa; float d2=fabs(z.y)-ob; float d3=fabs(z.z)-oc; float outside=native_sqrt(fmax(d1,0.0)*fmax(d1,0.0)+fmax(d2,0.0)*fmax(d2,0.0)+fmax(d3,0.0)*fmax(d3,0.0)); float inside=fmin(fmax(d1,fmax(d2,d3)),0.0); float d=outside+inside; aux.DE *= (1.0 + of*native_exp(-od*fabs(d))); break; }
					case 95: { float md=1e10; for(int k=0;k<(int)fmax(2,fmin(oa*4,8));k++){ float ang=k*2.0*M_PI_F/fmax(oa*4,2); float cx=ob*native_cos(ang); float cy=ob*native_sin(ang); for(int j=0;j<(int)fmax(2,fmin(oc*4,8));j++){ float az=j*2.0*M_PI_F/fmax(oc*4,2); float cz=od*native_sin(az); float d=(z.x-cx)*(z.x-cx)+(z.y-cy)*(z.y-cy)+(z.z-cz)*(z.z-cz); if(d<md)md=d; }} aux.DE *= (1.0 + of*native_exp(-native_sqrt(md))); break; }
					case 96: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float d=native_sin(r*oa)*native_sin(z.x*ob)*native_sin(z.y*oc); aux.DE *= (1.0 + of*fabs(d)); break; }
					case 97: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float ph=atan2(z.y,z.x); float th=acos(z.z/fmax(r,1e-21)); float Y=native_sin(th)*native_cos(oa*ph); float d=fabs(r-ob*(1.0+oc*Y)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 98: { float d=0; for(int k=1;k<=(int)fmax(1,fmin(oa*4,6));k++){ float rk=ob*(float)k; float dk=fabs(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-rk); d+=native_exp(-oc*dk); } aux.DE *= (1.0 + of*d/(oa*4+1e-21)); break; }
					case 99: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float d=fabs(r-oa); float v=native_exp(-ob*d)*native_cos(oc*d); z.x += of*v*z.x/fmax(r,1e-21)*0.01; z.y += of*v*z.y/fmax(r,1e-21)*0.01; z.z += of*v*z.z/fmax(r,1e-21)*0.01; aux.DE *= (1.0 + of*fabs(v)*0.1); break; }
					case 100: { float d1=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-oa; float d2=native_sqrt((z.x-ob)*(z.x-ob)+z.y*z.y+z.z*z.z)-oc; float d=fmin(fabs(d1),fabs(d2)); float blend=native_sin(z.x*od+z.y*od)*0.5+0.5; aux.DE *= (1.0 + of*(d1*(1.0-blend)+d2*blend)*native_exp(-d)); break; }
				}
			}

			// v7.12 [GPU] — MandelTorus DE system (per-section iteration range)
			if (i >= mut->torusIterStart && i < mut->torusIterStop && mut->torusType != 0)
			{
				float tf = mut->torusFactor;
				float ta = mut->torusParamA, tb = mut->torusParamB, tc = mut->torusParamC, td = mut->torusParamD;
				switch(mut->torusType) {
					case 1: { float k = ta; float DE0 = tb; aux.DE = 1.0/(1.0 + native_exp(-k*(aux.DE - DE0))); break; }
					case 2: { float DE0 = ta; float sigma = fmax(fabs(tb), 0.01); aux.DE *= native_exp(-(aux.DE-DE0)*(aux.DE-DE0)/(sigma*sigma)); break; }
					case 3: { float threshold = ta; float DE_max = fabs(tb)+1.0; float DE_min = fabs(tc)*0.01; aux.DE = (aux.DE > threshold) ? DE_max : DE_min; break; }
					case 4: { float b1=ta, b2=tb; float d1=fabs(tc),d2=fabs(td); if(aux.DE<b1) aux.DE=d1; else if(aux.DE<b2) aux.DE=d2; break; }
					case 5: { float h = native_sin(z.x*127.1+z.y*311.7+z.z*74.7)*43758.5453; h=h-floor(h); aux.DE += tf*(h*2.0-1.0)*ta; break; }
					case 6: { float jx=z.x*z.x-z.y*z.y+ta; float jy=2.0*z.x*z.y+tb; float julia_mag=native_sqrt(jx*jx+jy*jy); aux.DE *= (1.0 + tf*0.1*julia_mag); break; }
					case 7: { aux.DE *= (1.0 + tf*0.1*native_sin(ta*(float)i*0.1)); break; }
					case 8: { float alpha=fmin(fmax(ta,0.01),0.99); aux.DE = alpha*aux.DE + (1.0-alpha)*tb; break; }
					case 9: { float h1=native_sin(ta*z.x+tb*z.y+tc*z.z); float h2=native_sin(td*h1+ta*aux.DE); aux.DE *= (1.0 + tf*h2); break; }
					case 10: { float v=0,f=ta,a=1.0; for(int k=0;k<4;k++){float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453;h=h-floor(h);v+=a*h;f*=2.0;a*=0.5;} aux.DE *= (1.0 + tf*0.1*v); break; }
					case 11: { float speed = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE /= (1.0 + tf*speed*ta); break; }
					case 12: { float sc = fabs(ta) + 0.01; aux.DE *= sc; break; }
					case 13: { float angle = atan2(z.y,z.x); aux.DE *= (1.0 + tf*fabs(angle)*ta/(M_PI_F)); break; }
					case 14: { float shear = fabs(z.x*z.y*ta) + fabs(z.y*z.z*tb) + fabs(z.z*z.x*tc); aux.DE *= (1.0 + tf*shear); break; }
					case 15: { float progress = (float)i / fmax((float)(i+10), 1.0); aux.DE *= (1.0 + tf*(1.0-progress)*ta); break; }
					case 16: { float box = fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z))); if(box > fabs(ta)) aux.DE *= (1.0 + tf*tb); break; }
					case 17: { float d = native_sqrt((z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc)); if(d < fabs(td)) aux.DE *= (1.0 + tf); break; }
					case 18: { float w = fabs(ta)+0.01; if(fabs(z.x)<w && fabs(z.y)<w) aux.DE *= (1.0 + tf*tb); break; }
					case 19: { float intensity = native_sin(z.x*ta)*native_sin(z.y*tb)*native_sin(z.z*tc); aux.DE *= (1.0 + tf*0.1*intensity*intensity); break; }
					case 20: { float ao = 1.0/(1.0 + (float)i*ta*0.01); aux.DE *= (1.0 - tf*ao*fabs(tb)); break; }
					case 21: { float gi = native_sin(z.x*ta+z.y*tb)*0.5+0.5; aux.DE /= (1.0 + tf*gi*fabs(tc)); break; }
					case 22: { float depth = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0 + tf*ta*depth); break; }
					case 23: { float light_accum = native_sin(z.x*ta)*native_sin(z.y*ta)*0.5+0.5; aux.DE /= (1.0 + tf*light_accum*tb); break; }
					case 24: { float ss_depth = native_exp(-fabs(ta)*native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)); aux.DE *= (1.0 + tf*ss_depth*tb); break; }
					case 25: { float wl_diff = fabs(z.x*ta - tb); aux.DE *= (1.0 + tf*tc*wl_diff); break; }
					case 26: { float caustic = native_sin(z.x*ta*10.0)*native_sin(z.y*tb*10.0); aux.DE *= (1.0 + tf*caustic*caustic*tc); break; }
					case 27: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float view_dot = z.z/fmax(r,1e-21); float fresnel = pow(fmax(1.0-fabs(view_dot),0.0), ta); aux.DE *= (1.0 + tf*fresnel*tb); break; }
					case 28: { float thin_film = native_sin(ta*native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*M_PI_F*2.0); aux.DE *= (1.0 + tf*thin_film*thin_film*tb); break; }
					case 29: { float tangent_dot = fabs(z.x*native_cos(ta)+z.y*native_sin(ta))/fmax(native_sqrt(z.x*z.x+z.y*z.y),1e-21); aux.DE *= (1.0 + tf*tangent_dot*tb); break; }
					case 30: { float subdiv = fmax(1.0, floor(ta*(float)i*0.1+1.0)); aux.DE /= subdiv*tf+1.0; break; }
					case 31: { float dist = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float lod = fmin(dist*ta, tb); aux.DE *= (1.0 + tf*lod); break; }
					case 32: { float edge = fabs(z.x-round(z.x*ta)/fmax(ta,1e-21)) + fabs(z.y-round(z.y*ta)/fmax(ta,1e-21)); aux.DE *= (1.0 + tf*edge*tb); break; }
					case 33: { float h = native_sin(z.x*ta*10.0)*native_sin(z.y*tb*10.0)*native_sin(z.z*tc*10.0); aux.DE += tf*h*td; break; }
					case 34: { float perturb = native_sin(z.x*ta*20.0)*native_cos(z.y*tb*20.0)*native_sin(z.z*tc*20.0); aux.DE *= (1.0 + tf*perturb*td); break; }
					case 35: { float depth = native_sin(z.x*ta+z.y*tb)*0.5+0.5; aux.DE *= (1.0 + tf*depth*tc); break; }
					case 36: { float n = fmax(fabs(ta), 0.1); aux.DE /= n; break; }
					case 37: { float dist = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= native_exp(-tf*fabs(ta)*dist); break; }
					case 38: { float cos_th = z.z/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),1e-21); float phase = (1.0-ta*ta)/(1.0+ta*ta-2.0*ta*cos_th+1e-21); aux.DE *= (1.0 + tf*phase*tb); break; }
					case 39: { float emission = native_sin(z.x*ta)*native_sin(z.y*ta)*native_sin(z.z*ta); emission = emission*emission; aux.DE /= (1.0 + tf*emission*tb); break; }
					case 40: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float theta = atan2(z.z,r2d-ta); float twist = native_sin(tb*phi + tc*theta); aux.DE *= (1.0 + tf*twist*twist); break; }
					case 41: { float R = fabs(ta)+0.1; float r_min = fabs(tb)+0.01; float ratio = R/r_min; aux.DE *= (1.0 + tf*ratio*0.1); break; }
					case 42: { float R = fabs(ta)+0.1; float r_min = fabs(tb)+0.01; float ratio = r_min/R; aux.DE *= (1.0 + tf*ratio); break; }
					case 43: { float phi = atan2(z.y,z.x); float revolutions = ta*phi/(2.0*M_PI_F); aux.DE *= (1.0 + tf*native_sin(revolutions*2.0*M_PI_F)*tb); break; }
					case 44: { float r2 = z.x*z.x+z.y*z.y+z.z*z.z+1e-21; float w = native_sin(ta*r2); float hopf = native_cos(tb*atan2(z.y,z.x))*native_sin(tc*acos(z.z/native_sqrt(r2))); aux.DE *= (1.0 + tf*w*hopf); break; }
					case 45: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float helix_r = ta + tb*native_sin(tc*phi); float d = fabs(r2d - helix_r); aux.DE *= (1.0 + tf*native_exp(-td*d)); break; }
					case 46: { float phi = atan2(z.y,z.x); float half_twist = native_sin(phi*0.5); float r2d = native_sqrt(z.x*z.x+z.y*z.y); float torus_d = fabs(r2d-ta); aux.DE *= (1.0 + tf*half_twist*half_twist*native_exp(-tb*torus_d)); break; }
					case 47: { float phi = atan2(z.y,z.x); float R = ta; float r_k = tb*(1.0+0.5*native_cos(phi)); float r2d = native_sqrt(z.x*z.x+z.y*z.y); float d = fabs(r2d-R) + fabs(z.z)*r_k; aux.DE *= (1.0 + tf*native_exp(-tc*d)); break; }
					case 48: { float phi = atan2(z.y,z.x); float genus = fmax(floor(fabs(ta)*3+1),1.0); float fiber = native_sin(genus*phi)*native_cos(tb*z.z); aux.DE *= (1.0 + tf*fiber*fiber*tc); break; }
					case 49: { float phi = atan2(z.y,z.x); float wrapping = floor(fabs(ta)*4+2); float companion = native_sin(wrapping*phi)*tb; float r2d = native_sqrt(z.x*z.x+z.y*z.y); float d = fabs(r2d-tc-companion); aux.DE *= (1.0 + tf*native_exp(-td*d)); break; }
					case 50: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float neg_curv = native_sin(ta*phi)*native_sin(tb*z.z)*native_exp(-tc*fabs(r2d-td)); aux.DE *= (1.0 + tf*neg_curv*neg_curv); break; }
					case 51: { float phi = atan2(z.y,z.x); float r2d = native_sqrt(z.x*z.x+z.y*z.y); float p=fmax(floor(fabs(ta)*3+2),2.0); float q=fmax(floor(fabs(tb)*3+3),3.0); float knot_r = tc + td*native_cos(q*phi); float knot_z2 = td*native_sin(q*phi); float d = native_sqrt((r2d-knot_r)*(r2d-knot_r)+(z.z-knot_z2)*(z.z-knot_z2)); aux.DE *= (1.0 + tf*native_exp(-d*5.0)); break; }
					case 52: { float phi = atan2(z.y,z.x); float r2d = native_sqrt(z.x*z.x+z.y*z.y); float trefoil_r = ta*(2.0+native_cos(3.0*phi)); float trefoil_z = ta*native_sin(3.0*phi); float d = native_sqrt((r2d-trefoil_r)*(r2d-trefoil_r)+(z.z-trefoil_z)*(z.z-trefoil_z)); aux.DE *= (1.0 + tf*native_exp(-tb*d)); break; }
					case 53: { float phi = atan2(z.y,z.x); float r2d = native_sqrt(z.x*z.x+z.y*z.y); float cinquefoil_r = ta*(2.0+native_cos(5.0*phi)); float cinquefoil_z = ta*native_sin(5.0*phi); float d = native_sqrt((r2d-cinquefoil_r)*(r2d-cinquefoil_r)+(z.z-cinquefoil_z)*(z.z-cinquefoil_z)); aux.DE *= (1.0 + tf*native_exp(-tb*d)); break; }
					case 54: { float phi = atan2(z.y,z.x); float r2d = native_sqrt(z.x*z.x+z.y*z.y); float fig8_r = ta*(2.0+native_cos(2.0*phi)); float fig8_z = ta*native_sin(4.0*phi)*0.5; float d = native_sqrt((r2d-fig8_r)*(r2d-fig8_r)+(z.z-fig8_z)*(z.z-fig8_z)); aux.DE *= (1.0 + tf*native_exp(-tb*d)); break; }
					case 55: { float t2 = atan2(z.y,z.x)*ta; float r2d = native_sqrt(z.x*z.x+z.y*z.y); float lissajous_r = tb*(2.0+native_sin(3.0*t2)*native_cos(2.0*t2)); float d = fabs(r2d-lissajous_r)+fabs(z.z)*tc; aux.DE *= (1.0 + tf*native_exp(-d*td)); break; }
					case 56: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float theta = atan2(z.z,r2d-ta); float bump = native_sin(tb*phi)*native_sin(tc*theta); aux.DE *= (1.0 + tf*bump*bump*td); break; }
					case 57: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float R = ta; float r = tb; float torus_d = native_sqrt((r2d-R)*(r2d-R)+z.z*z.z)-r; float corrugation = native_sin(tc*atan2(z.y,z.x)*10.0)*td; aux.DE *= (1.0 + tf*native_exp(-(torus_d-corrugation)*(torus_d-corrugation))); break; }
					case 58: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float wave_R = ta + tb*native_sin(tc*phi)*native_sin(td*z.z); float d = fabs(r2d-wave_R); aux.DE *= (1.0 + tf*native_exp(-d*5.0)); break; }
					case 59: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float spiral_R = ta + tb*phi/(2.0*M_PI_F); float d = fabs(r2d-spiral_R)+fabs(z.z)*tc; aux.DE *= (1.0 + tf*native_exp(-d*td)); break; }
					case 60: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float star_n = fmax(floor(fabs(ta)*5+3),3.0); float phi = atan2(z.y,z.x); float star_R = tb*(1.0+tc*native_cos(star_n*phi)); float d = fabs(r2d-star_R)+fabs(z.z)*td; aux.DE *= (1.0 + tf*native_exp(-d*5.0)); break; }
					case 61: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float R = ta; float r = tb; float torus_d = native_sqrt((r2d-R)*(r2d-R)+z.z*z.z)-r; float fracture = native_sin(z.x*tc*20.0)*native_sin(z.y*tc*20.0)*td; aux.DE *= (1.0 + tf*native_exp(-fabs(torus_d)*5.0)*(1.0+fracture)); break; }
					case 62: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float egg_R = ta*(1.0+tb*native_sin(phi)); float d = native_sqrt((r2d-egg_R)*(r2d-egg_R)+z.z*z.z)-tc; aux.DE *= (1.0 + tf*native_exp(-fabs(d)*td)); break; }
					case 63: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float gear_n = fmax(floor(fabs(ta)*8+4),4.0); float gear_R = tb*(1.0+tc*fmax(native_cos(gear_n*phi)-0.5,0.0)); float d = fabs(r2d-gear_R); aux.DE *= (1.0 + tf*native_exp(-d*td*10.0)); break; }
					case 64: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float R = ta; float r = tb; float torus_d = native_sqrt((r2d-R)*(r2d-R)+z.z*z.z)-r; float erosion = native_sin(z.x*tc*5.0)*native_sin(z.y*tc*5.0)*native_sin(z.z*tc*5.0); aux.DE *= (1.0 + tf*native_exp(-fabs(torus_d)*5.0)*fabs(erosion)*td); break; }
					case 65: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float theta = atan2(z.z,r2d-ta); float superformula = pow(fabs(native_cos(tb*theta/4.0)),tc)+pow(fabs(native_sin(tb*theta/4.0)),tc); float sf_r = td*pow(superformula,-1.0/fmax(tc,0.01)); float d = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-sf_r; aux.DE *= (1.0 + tf*native_exp(-fabs(d)*5.0)); break; }
					case 66: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float R = ta; float gravity = 1.0/fmax((r2d-R)*(r2d-R)+z.z*z.z+0.01, 0.01); aux.DE *= (1.0 + tf*fmin(gravity*tb,10.0)); break; }
					case 67: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float B_field = ta*native_sin(tb*phi)/(fmax(fabs(r2d-tc),0.01)); aux.DE *= (1.0 + tf*fmin(fabs(B_field),10.0)*td); break; }
					case 68: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float vortex = ta*native_exp(-tb*((r2d-tc)*(r2d-tc)+z.z*z.z)); float circulation = native_sin(td*atan2(z.y,z.x)); aux.DE *= (1.0 + tf*vortex*circulation); break; }
					case 69: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float plasma = native_sin(ta*r2d)*native_cos(tb*phi)*native_sin(tc*z.z); float temperature = native_exp(-td*native_sqrt((r2d-1.0)*(r2d-1.0)+z.z*z.z)); aux.DE *= (1.0 + tf*plasma*temperature); break; }
					case 70: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float R = ta; float charge = tb/fmax(native_sqrt((r2d-R)*(r2d-R)+z.z*z.z),0.01); float screen = native_exp(-tc*native_sqrt((r2d-R)*(r2d-R)+z.z*z.z)); aux.DE *= (1.0 + tf*charge*screen*td); break; }
					case 71: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float wave1 = native_sin(ta*phi + tb*z.z); float wave2 = native_sin(tc*phi - tb*z.z); float interference = (wave1+wave2)*(wave1+wave2)*0.25; aux.DE *= (1.0 + tf*interference*td); break; }
					case 72: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float R = ta; float thermal = native_exp(-tb*((r2d-R)*(r2d-R)+z.z*z.z)); float fluctuation = native_sin(tc*z.x)*native_sin(tc*z.y)*native_sin(tc*z.z); aux.DE *= (1.0 + tf*thermal*(1.0+td*fluctuation)); break; }
					case 73: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); int modes = (int)fmax(2,fmin(ta*5,10)); float v = 0; for(int m=1;m<=modes;m++) v+=native_sin(m*phi*tb)*native_cos(m*z.z*tc)/m; aux.DE *= (1.0 + tf*v*v*td); break; }
					case 74: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float R = ta; float diffusion = 1.0/(1.0 + tb*(float)i*0.01); float concentration = native_exp(-tc*fabs(r2d-R))*diffusion; aux.DE *= (1.0 + tf*concentration*td); break; }
					case 75: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float reaction = native_sin(ta*phi)*native_sin(tb*z.z); float diffuse = native_exp(-tc*((r2d-td)*(r2d-td))); float rd = reaction*diffuse; aux.DE *= (1.0 + tf*rd*rd); break; }
					case 76: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float d1 = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; float d2 = native_sqrt((r2d-tc)*(r2d-tc)+z.z*z.z)-td; aux.DE *= (1.0 + tf*native_exp(-fmin(d1*d1,d2*d2)*5.0)); break; }
					case 77: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float ryz = native_sqrt(z.y*z.y+z.z*z.z); float d1 = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; float d2 = native_sqrt((ryz-ta)*(ryz-ta)+z.x*z.x)-tb; aux.DE *= (1.0 + tf*native_exp(-fmin(d1*d1,d2*d2)*tc)); break; }
					case 78: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float rxz = native_sqrt(z.x*z.x+z.z*z.z); float ryz = native_sqrt(z.y*z.y+z.z*z.z); float d1=fabs(native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb); float d2=fabs(native_sqrt((rxz-ta)*(rxz-ta)+z.y*z.y)-tb); float d3=fabs(native_sqrt((ryz-ta)*(ryz-ta)+z.x*z.x)-tb); aux.DE *= (1.0 + tf*native_exp(-fmin(d1,fmin(d2,d3))*tc)); break; }
					case 79: { float phi = atan2(z.y,z.x); float r2d = native_sqrt(z.x*z.x+z.y*z.y); int n = (int)fmax(2,fmin(ta*4,8)); float md = 1e10; for(int k=0;k<n;k++){ float ang = k*2.0*M_PI_F/n; float cx = tb*native_cos(ang); float cy = tb*native_sin(ang); float d = native_sqrt((z.x-cx)*(z.x-cx)+(z.y-cy)*(z.y-cy)+z.z*z.z)-tc; if(fabs(d)<md) md=fabs(d); } aux.DE *= (1.0 + tf*native_exp(-md*td)); break; }
					case 80: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float R_var = ta + tb*native_sin(tc*phi); float torus_d = native_sqrt((r2d-R_var)*(r2d-R_var)+z.z*z.z)-td; aux.DE *= (1.0 + tf*native_exp(-torus_d*torus_d*5.0)); break; }
					case 81: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float d1 = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; float d2 = native_sqrt((r2d-ta)*(r2d-ta)+(z.z-tc)*(z.z-tc))-tb; aux.DE *= (1.0 + tf*native_exp(-fmin(fabs(d1),fabs(d2))*td)); break; }
					case 82: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float R1 = ta; float r1 = tb; float R2 = tc; float r2 = td; float d1 = native_sqrt((r2d-R1)*(r2d-R1)+z.z*z.z)-r1; float d2 = native_sqrt((r2d-R2)*(r2d-R2)+z.z*z.z)-r2; float smooth = -native_log(fmax(native_exp(-d1*5.0f)+native_exp(-d2*5.0f),1e-21f))/5.0f; aux.DE *= (1.0 + tf*native_exp(-smooth*smooth)); break; }
					case 83: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float torus_d = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; float sphere_d = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-tc; float d = fmax(torus_d, -sphere_d); aux.DE *= (1.0 + tf*native_exp(-fabs(d)*td)); break; }
					case 84: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float torus_d = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; float box_d = fmax(fabs(z.x)-tc,fmax(fabs(z.y)-tc,fabs(z.z)-td))-0.0; float d = fmax(torus_d,box_d); aux.DE *= (1.0 + tf*native_exp(-fabs(d)*5.0)); break; }
					case 85: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float inner_r = tb*(1.0+tc*native_sin(td*phi)); float torus_d = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-inner_r; aux.DE *= (1.0 + tf*native_exp(-torus_d*torus_d*5.0)); break; }
					case 86: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float flow = native_sin(ta*phi-(float)i*tb*0.1); float torus_d = native_sqrt((r2d-tc)*(r2d-tc)+z.z*z.z)-td; aux.DE *= (1.0 + tf*flow*flow*native_exp(-fabs(torus_d)*5.0)); break; }
					case 87: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float omega = ta*(float)i*0.01; float R_t = tb*(1.0+tc*native_sin(omega)); float torus_d = native_sqrt((r2d-R_t)*(r2d-R_t)+z.z*z.z)-td; aux.DE *= (1.0 + tf*native_exp(-torus_d*torus_d*5.0)); break; }
					case 88: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float stretch = 1.0 + ta*native_sin(tb*phi); float torus_d = native_sqrt((r2d-tc*stretch)*(r2d-tc*stretch)+z.z*z.z)-td/stretch; aux.DE *= (1.0 + tf*native_exp(-torus_d*torus_d*5.0)); break; }
					case 89: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phase = ta*(float)i*0.1; float wobble_z = tb*native_sin(phase); float torus_d = native_sqrt((r2d-tc)*(r2d-tc)+(z.z-wobble_z)*(z.z-wobble_z))-td; aux.DE *= (1.0 + tf*native_exp(-torus_d*torus_d*5.0)); break; }
					case 90: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float pulse = native_exp(-ta*((float)i*0.1-tb)*((float)i*0.1-tb)); float torus_d = native_sqrt((r2d-tc)*(r2d-tc)+z.z*z.z)-td*(1.0+pulse); aux.DE *= (1.0 + tf*native_exp(-torus_d*torus_d*5.0)); break; }
					case 91: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float bifurcation = ta*native_sin(tb*phi)*native_sin(tc*phi*2.0); float torus_d = native_sqrt((r2d-td-bifurcation)*(r2d-td-bifurcation)+z.z*z.z)-0.3; aux.DE *= (1.0 + tf*native_exp(-torus_d*torus_d*5.0)); break; }
					case 92: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float chaos = native_sin(ta*z.x)*native_cos(tb*z.y)*native_sin(tc*z.z); float torus_d = native_sqrt((r2d-td)*(r2d-td)+z.z*z.z)-fabs(chaos)*0.5; aux.DE *= (1.0 + tf*native_exp(-torus_d*torus_d*5.0)); break; }
					case 93: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float soliton = 1.0/cosh(ta*(r2d-tb)); float torus_phase = native_sin(tc*phi+td*z.z); aux.DE *= (1.0 + tf*soliton*torus_phase*torus_phase); break; }
					case 94: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float breather = native_sin(ta*(float)i*0.1)*native_sin(tb*phi)/cosh(tc*(r2d-td)); aux.DE *= (1.0 + tf*breather*breather); break; }
					case 95: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float torus_d = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; float damping = native_exp(-tc*(float)i*0.01); aux.DE *= (1.0 + tf*native_sin(torus_d*td*10.0)*damping); break; }
					case 96: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float theta = atan2(z.z,r2d-ta); float villarceau = native_sin(phi+theta*tb)*native_sin(phi-theta*tb); aux.DE *= (1.0 + tf*villarceau*villarceau*tc); break; }
					case 97: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float dupin = ta*(1.0+tb*native_cos(phi))*(1.0+tc*native_cos(atan2(z.z,r2d-ta))); float d = fabs(native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-dupin*0.3); aux.DE *= (1.0 + tf*native_exp(-d*td)); break; }
					case 98: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float theta = atan2(z.z,r2d-ta); float clifford_r = ta*(native_cos(tb*phi)*native_cos(tc*theta)); float clifford_d = fabs(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-fabs(clifford_r)); aux.DE *= (1.0 + tf*native_exp(-clifford_d*td)); break; }
					case 99: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float lawson_r = ta*native_cos(tb*phi)*native_cos(tc*z.z); float d = fabs(r2d-fabs(lawson_r)-td); aux.DE *= (1.0 + tf*native_exp(-d*5.0)); break; }
					case 100: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float theta = atan2(z.z,r2d-ta); float p=fmax(ta,0.1); float q=fmax(tb,0.1); float torus_knot_r = tc*(2.0+native_cos(q/p*phi)); float torus_knot_z = tc*native_sin(q/p*phi); float d = native_sqrt((r2d-torus_knot_r)*(r2d-torus_knot_r)+(z.z-torus_knot_z)*(z.z-torus_knot_z))-td; aux.DE *= (1.0 + tf*native_exp(-fabs(d)*5.0)); break; }
				}
			}


				// v7.13 — Amazing Surf 1-4 DE system (per-section iteration range)
				if (i >= mut->asIterStart && i < mut->asIterStop && mut->asType != 0)
				{
					float sf = mut->asFactor;
					float ta = mut->asParamA, tb = mut->asParamB;
					float tc = mut->asParamC, td = mut->asParamD;
					switch(mut->asType) {
						case 1: { float k = ta; float DE0 = tb; aux->DE = 1.0/(1.0 + native_exp(-k*(aux->DE - DE0))); break; }
						case 2: { float DE0 = ta; float sigma = fmax(fabs(tb), 0.01); aux->DE *= native_exp(-(aux->DE-DE0)*(aux->DE-DE0)/(sigma*sigma)); break; }
						case 3: { float threshold = ta; float DE_max = fabs(tb)+1.0; float DE_min = fabs(tc)*0.01; aux->DE = (aux->DE > threshold) ? DE_max : DE_min; break; }
						case 4: { float b1=ta, b2=tb; float d1=fabs(tc),d2=fabs(td); if(aux->DE<b1) aux->DE=d1; else if(aux->DE<b2) aux->DE=d2; break; }
						case 5: { float h = native_sin(z.x*127.1+z.y*311.7+z.z*74.7)*43758.5453; h=h-floor(h); aux->DE += sf*(h*2.0-1.0)*ta; break; }
						case 6: { float jx=z.x*z.x-z.y*z.y+ta; float jy=2.0*z.x*z.y+tb; float julia_mag=native_sqrt(jx*jx+jy*jy); aux->DE *= (1.0 + sf*0.1*julia_mag); break; }
						case 7: { aux->DE *= (1.0 + sf*0.1*native_sin(ta*(double)i*0.1)); break; }
						case 8: { float alpha=fmin(fmax(ta,0.01),0.99); aux->DE = alpha*aux->DE + (1.0-alpha)*tb; break; }
						case 9: { float h1=native_sin(ta*z.x+tb*z.y+tc*z.z); float h2=native_sin(td*h1+ta*aux->DE); aux->DE *= (1.0 + sf*h2); break; }
						case 10: { float v=0,f=ta,a=1.0; for(int k=0;k<4;k++){float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453;h=h-floor(h);v+=a*h;f*=2.0;a*=0.5;} aux->DE *= (1.0 + sf*0.1*v); break; }
						case 11: { float speed = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux->DE /= (1.0 + sf*speed*ta); break; }
						case 12: { float sc = fabs(ta) + 0.01; aux->DE *= sc; break; }
						case 13: { float angle = atan2(z.y,z.x); aux->DE *= (1.0 + sf*fabs(angle)*ta/M_PI_F); break; }
						case 14: { float shear = fabs(z.x*z.y*ta) + fabs(z.y*z.z*tb) + fabs(z.z*z.x*tc); aux->DE *= (1.0 + sf*shear); break; }
						case 15: { float progress = (double)i / fmax((double)(i+10), 1.0); aux->DE *= (1.0 + sf*(1.0-progress)*ta); break; }
						case 16: { float box = fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z))); if(box > fabs(ta)) aux->DE *= (1.0 + sf*tb); break; }
						case 17: { float d = native_sqrt((z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc)); if(d < fabs(td)) aux->DE *= (1.0 + sf); break; }
						case 18: { float w = fabs(ta)+0.01; if(fabs(z.x)<w && fabs(z.y)<w) aux->DE *= (1.0 + sf*tb); break; }
						case 19: { float intensity = native_sin(z.x*ta)*native_sin(z.y*tb)*native_sin(z.z*tc); aux->DE *= (1.0 + sf*0.1*intensity*intensity); break; }
						case 20: { float ao = 1.0/(1.0 + (double)i*ta*0.01); aux->DE *= (1.0 - sf*ao*fabs(tb)); break; }
						case 21: { float gi = native_sin(z.x*ta+z.y*tb)*0.5+0.5; aux->DE /= (1.0 + sf*gi*fabs(tc)); break; }
						case 22: { float depth = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux->DE *= (1.0 + sf*ta*depth); break; }
						case 23: { float light_accum = native_sin(z.x*ta)*native_sin(z.y*ta)*0.5+0.5; aux->DE /= (1.0 + sf*light_accum*tb); break; }
						case 24: { float ss_depth = native_exp(-fabs(ta)*native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)); aux->DE *= (1.0 + sf*ss_depth*tb); break; }
						case 25: { float wl_diff = fabs(z.x*ta - tb); aux->DE *= (1.0 + sf*tc*wl_diff); break; }
						case 26: { float caustic = native_sin(z.x*ta*10.0)*native_sin(z.y*tb*10.0); aux->DE *= (1.0 + sf*caustic*caustic*tc); break; }
						case 27: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float view_dot = z.z/fmax(r,1e-21); float fresnel = pow(fmax(1.0-fabs(view_dot),0.0), ta); aux->DE *= (1.0 + sf*fresnel*tb); break; }
						case 28: { float thin_film = native_sin(ta*native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*M_PI_F*2.0); aux->DE *= (1.0 + sf*thin_film*thin_film*tb); break; }
						case 29: { float tangent_dot = fabs(z.x*native_cos(ta)+z.y*native_sin(ta))/fmax(native_sqrt(z.x*z.x+z.y*z.y),1e-21); aux->DE *= (1.0 + sf*tangent_dot*tb); break; }
						case 30: { float subdiv = fmax(1.0, fabs(ta)); aux->DE /= (1.0 + sf*subdiv*tb); break; }
						case 31: { float dist = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float lod = fmax(0.1, dist*ta); aux->DE *= lod; break; }
						case 32: { float edge_len = fabs(z.x-z.y) + fabs(z.y-z.z) + fabs(z.z-z.x); aux->DE *= (1.0 + sf*ta*edge_len*tb); break; }
						case 33: { float disp = native_sin(z.x*ta*5.0)*native_sin(z.y*tb*5.0)*native_sin(z.z*tc*5.0); aux->DE += sf*disp*td; break; }
						case 34: { float h = native_sin(z.x*ta*7.0+z.y*tb*11.0+z.z*tc*13.0)*43758.5453; h=h-floor(h); aux->DE *= (1.0 + sf*(h*2.0-1.0)*td*0.1); break; }
						case 35: { float parallax = fabs(ta)*z.z/fmax(fabs(tb),0.01); aux->DE *= (1.0 + sf*parallax*0.1); break; }
						case 36: { float n = fmax(fabs(ta)+1.0, 1.01); aux->DE /= n; break; }
						case 37: { float dist_traveled = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux->DE *= native_exp(-sf*fabs(ta)*dist_traveled); break; }
						case 38: { float cos_theta = z.z/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),1e-21); float phase = (1.0+cos_theta*cos_theta)*0.75; aux->DE *= (1.0 + sf*phase*ta); break; }
						case 39: { float emission = native_sin(z.x*ta)*native_sin(z.y*ta)*0.5+0.5; aux->DE /= (1.0 + sf*emission*fabs(tb)); break; }
						case 40: { float curl_approx = native_sin(z.y*ta)*native_cos(z.z*tb) - native_cos(z.y*ta)*native_sin(z.z*tb); aux->DE *= (1.0 + sf*fabs(curl_approx)*tc); break; }
						case 41: { float grad = (native_sin(z.x*ta)-native_sin((z.x+0.01)*ta))/0.01; aux->DE /= (1.0 + sf*fabs(grad)*tb); break; }
						case 42: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float mass_d = fmax(r - ta, 0.01); aux->DE *= (1.0 + sf*tb/(mass_d*mass_d)); break; }
						case 43: { float v2 = (z.x*z.x+z.y*z.y+z.z*z.z)*ta*ta; float lorentz = native_sqrt(fmax(1.0 - fmin(v2, 0.99), 0.01)); aux->DE *= lorentz; break; }
						case 44: { float barrier = fabs(z.x - ta); aux->DE *= native_exp(-sf*fabs(tb)*barrier); break; }
						case 45: { float psi2 = native_sin(ta*z.x)*native_sin(tb*z.y)*native_sin(tc*z.z); aux->DE *= (1.0 + sf*psi2*psi2); break; }
						case 46: { float momentum = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*ta; float pos = fmax(fabs(z.x), 0.01); aux->DE *= (1.0 + sf*tb/(2.0*momentum*pos+0.01)); break; }
						case 47: { float spin_dot = z.x*native_sin(ta)+z.y*native_cos(ta)+z.z*native_sin(tb); aux->DE *= (1.0 + sf*tc*spin_dot); break; }
						case 48: { float corr = native_sin(z.x*ta)*native_sin((-z.x)*ta) + native_sin(z.y*tb)*native_sin((-z.y)*tb); aux->DE *= (1.0 + sf*fabs(corr)*tc); break; }
						case 49: { float decay = native_exp(-sf*fabs(ta)*(double)i*0.01); aux->DE *= decay; break; }
						case 50: { float entropy = native_sin(z.x*ta*3.0)*native_sin(z.y*tb*5.0)*native_sin(z.z*tc*7.0); float temp = fabs(td)+0.01; aux->DE *= (1.0 + sf*temp*entropy*entropy); break; }
						case 51: { float kT = fmax(fabs(ta)*fabs(tb), 0.01); aux->DE *= (1.0 + sf*tc/kT); break; }
						case 52: { float vel_grad = fabs(z.x-z.y)*ta + fabs(z.y-z.z)*tb; aux->DE *= (1.0 + sf*tc*vel_grad); break; }
						case 53: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float curv = 1.0/fmax(r,0.01); aux->DE *= (1.0 + sf*ta*curv); break; }
						case 54: { float tube_r = fmax(fabs(native_sqrt(z.x*z.x+z.y*z.y) - ta), 0.01); aux->DE *= (1.0 + sf*native_cos(tb)/tube_r); break; }
						case 55: { float conc_grad = fabs(native_sin(z.x*ta) - native_sin(z.y*ta)); aux->DE *= (1.0 + sf*tb*conc_grad); break; }
						case 56: { float lap = native_sin((z.x+0.01)*ta)+native_sin((z.x-0.01)*ta)-2.0*native_sin(z.x*ta); aux->DE += sf*tb*lap; break; }
						case 57: { float vel_dot = native_sin(z.x*ta)*native_cos(z.y*tb); aux->DE *= (1.0 + sf*vel_dot*tc); break; }
						case 58: { float v=0,f=ta,a=1.0; for(int k=0;k<4;k++){float h=native_sin(z.x*f*12.9+z.y*f*78.2+z.z*f*45.1)*43758.5453;h=h-floor(h);v+=a*h;f*=2.0;a*=0.5;} aux->DE *= (1.0 + sf*v*tb); break; }
						case 59: { float front = fabs(z.x - ta*i*0.01); float shock = (front < fabs(tb)) ? tc : 1.0; aux->DE *= shock; break; }
						case 60: { float freq_diff = fabs(native_sin(z.x*ta) - native_sin(z.x*tb)); float Q = fmax(fabs(tc), 0.1); aux->DE *= (1.0 + sf*Q*1.0/fmax(freq_diff+0.01, 0.01)); break; }
						case 61: { float phase_diff = ta*z.x - tb*z.y; aux->DE *= (1.0 + sf*native_cos(phase_diff)*tc); break; }
						case 62: { float v_source = ta * 0.1; float angle = atan2(z.y, z.x); aux->DE *= (1.0 + sf*v_source*native_cos(angle)*tb); break; }
						case 63: { float theta = atan2(z.y, z.x); aux->DE *= (1.0 + sf*ta*native_cos(2.0*theta)); break; }
						case 64: { float phi2 = atan2(z.z, native_sqrt(z.x*z.x+z.y*z.y)); aux->DE *= (1.0 + sf*ta*fabs(native_sin(2.0*phi2))); break; }
						case 65: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float path = r * fabs(ta) * fabs(tb); aux->DE *= (1.0 + sf*tc*path); break; }
						case 66: { float lat_pt = fmod(fabs(z.x*ta), 1.0); float bandgap = (lat_pt < 0.5) ? 1.0 : tb; aux->DE *= bandgap; break; }
						case 67: { float surf_dist = fabs(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z) - ta); float skin = fmax(fabs(tb), 0.01); aux->DE *= (1.0 + sf*tc*native_exp(-surf_dist/skin)); break; }
						case 68: { float neg_idx = fabs(ta); aux->DE *= (1.0 + sf*neg_idx*fabs(tb)); break; }
						case 69: { float winding = native_sin(z.x*ta)*native_cos(z.y*tb) + native_cos(z.x*ta)*native_sin(z.y*tb); aux->DE *= (1.0 + sf*fabs(winding)*tc); break; }
						case 70: { float charge = native_sin(z.x*ta*5.0)*native_sin(z.y*tb*5.0)*native_sin(z.z*tc*5.0); aux->DE *= (1.0 + sf*charge*charge*td); break; }
						case 71: { float curl_mag = fabs(native_sin(z.y*ta)-native_sin(z.z*ta)) + fabs(native_sin(z.z*tb)-native_sin(z.x*tb)); aux->DE *= (1.0 + sf*curl_mag*tc); break; }
						case 72: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float sech_val = 1.0/cosh(fmin(ta*(r-tb), 20.0)); aux->DE *= (1.0 + sf*tc*sech_val); break; }
						case 73: { float S = fabs(ta)*native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux->DE *= (1.0 + sf*tb*native_exp(-fmin(S,20.0))); break; }
						case 74: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float monopole = fabs(ta)/fmax(r,0.01); aux->DE *= (1.0 + sf*monopole*tb); break; }
						case 75: { float d_axis = native_sqrt(z.y*z.y+z.z*z.z); aux->DE *= (1.0 + sf*ta*native_log(fmax(d_axis,0.01))*tb); break; }
						case 76: { float d_brane = fabs(z.x - ta); float delta_approx = native_exp(-d_brane*d_brane*100.0); aux->DE *= (1.0 + sf*tb*delta_approx); break; }
						case 77: { float throat_d = (z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc); float throat_r = fmax(fabs(td), 0.01); aux->DE *= (1.0 + sf*native_exp(-throat_d/(throat_r*throat_r))); break; }
						case 78: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float rs = fmax(fabs(ta), 0.01); aux->DE /= fmax(1.0 - rs/fmax(r,rs+0.01), 0.01); break; }
						case 79: { float jet_d = z.y*z.y+z.z*z.z; float jet_w = fmax(fabs(tb), 0.01); aux->DE *= (1.0 + sf*ta*native_exp(-jet_d/(jet_w*jet_w))); break; }
						case 80: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float halo = 1.0/(1.0 + r*r/(fmax(ta*ta,0.01))); aux->DE *= (1.0 + sf*tb*halo); break; }
						case 81: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux->DE *= native_exp(sf*fabs(ta)*r*0.01); break; }
						case 82: { float d_string = native_sqrt(z.y*z.y+z.z*z.z); float horizon = fmax(fabs(tb), 0.01); aux->DE *= (1.0 + sf*ta*native_log(fmax(d_string/horizon,0.01))); break; }
						case 83: { float d_wall = fabs(z.x - ta); float thickness = fmax(fabs(tb), 0.01); aux->DE *= (1.0 + sf*tc*tanh(d_wall/thickness)); break; }
						case 84: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float theta2 = atan2(z.y,z.x); float phi2 = acos(z.z/fmax(r,1e-21)); float Ylm = native_sin(ta*theta2)*native_cos(tb*phi2); aux->DE *= (1.0 + sf*tc*Ylm*Ylm); break; }
						case 85: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float efold = r*fabs(ta); aux->DE *= native_exp(sf*fmin(efold*tb, 10.0)); break; }
						case 86: { float decay_t = native_exp(-fabs(ta)*(double)i*0.01); aux->DE *= (1.0 + sf*tb*decay_t*tc); break; }
						case 87: { float baryon = native_sin(z.x*ta)*native_sin(z.y*tb); float rate = native_exp(-fabs(tc)*(double)i*0.01); aux->DE *= (1.0 + sf*baryon*baryon*rate*td); break; }
						case 88: { float ion_frac = native_exp(-fabs(ta)/fmax(fabs(tb)*(double)i*0.01+0.01, 0.01)); aux->DE *= (1.0 + sf*ion_frac*tc); break; }
						case 89: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float scale_a = fmax(r*ta, 0.01); float energy = 1.0/(scale_a*scale_a); aux->DE *= (1.0 + sf*native_sqrt(energy)*tb); break; }
						case 90: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float scale_a = fmax(r*ta, 0.01); aux->DE /= fmax(scale_a*tb, 0.01); break; }
						case 91: { float ent_max = fabs(ta); float heat_time = fmax(fabs(tb), 0.01); aux->DE *= (1.0 + sf*ent_max*(1.0-native_exp(-(double)i*0.01/heat_time))); break; }
						case 92: { float bubble = native_sin(z.x*ta*5.0)*native_sin(z.y*tb*5.0)*native_sin(z.z*tc*5.0); aux->DE *= (1.0 + sf*fabs(bubble)*td); break; }
						case 93: { float barrier2 = fabs(ta); float tunnel = native_exp(-barrier2*native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)); aux->DE *= (1.0 + sf*tunnel*tb); break; }
						case 94: { float order = native_sin(z.x*ta)*native_sin(z.y*tb); float latent = fabs(tc); aux->DE *= (1.0 + sf*latent*order*order); break; }
						case 95: { float d_crit = native_sqrt((z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc)); float expo = fmax(fabs(td), 0.1); aux->DE *= pow(fmax(d_crit, 0.01), -expo); break; }
						case 96: { float cutoff = fmax(fabs(ta), 0.01); float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux->DE *= (1.0 + sf*tb*native_log(fmax(cutoff/fmax(r,0.01), 0.01))); break; }
						case 97: { float div_approx = native_cos(z.x*ta)*native_sin(z.y*tb)*native_cos(z.z*tc); aux->DE *= (1.0 + sf*fabs(div_approx)*td); break; }
						case 98: { float vev = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*ta; aux->DE *= (1.0 + sf*vev*vev*tb); break; }
						case 99: { float grad_phase = fabs(native_cos(z.x*ta)-native_cos(z.y*ta)) + fabs(native_cos(z.y*tb)-native_cos(z.z*tb)); aux->DE *= (1.0 + sf*tc*grad_phase); break; }
						case 100: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float higgs = ta*tb*r*r; aux->DE *= (1.0 + sf*higgs); break; }
					}
				}

				// v7.13 — SphereTree/Menger DE system (per-section iteration range)
				if (i >= mut->smIterStart && i < mut->smIterStop && mut->smType != 0)
				{
					float sf = mut->smFactor;
					float ta = mut->smParamA, tb = mut->smParamB;
					float tc = mut->smParamC, td = mut->smParamD;
					switch(mut->smType) {
						case 1: { float branch = 2.0 + floor(3.0*native_sin((double)i*ta*0.1)); aux->DE *= fmax(branch*tb, 0.01); break; }
						case 2: { float bx=fmax(ta,1.0),by=fmax(tb,1.0),bz=fmax(tc,1.0); aux->DE *= fmax(fmax(bx,by),bz)*sf; break; }
						case 3: { float angle = (double)i * 2.39996322972865332 * ta; float cosA=native_cos(angle),sinA=native_sin(angle); float nx=z.x*cosA-z.y*sinA; z.y=z.x*sinA+z.y*cosA; z.x=nx; break; }
						case 4: { float jm = native_sin(z.x*ta)*native_cos(z.y*tb); float r_ratio = 1.0 + sf*0.3*jm; aux->DE *= r_ratio; break; }
						case 5: { float h = native_sin(z.x*ta*127.1+z.y*ta*311.7+z.z*ta*74.7)*43758.5453; h=h-floor(h); aux->DE *= (1.0 + sf*(h*2.0-1.0)*tb); break; }
						case 6: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float d1 = r - ta; float d2 = r - tb; aux->DE *= (1.0 + sf*native_exp(-fmin(d1*d1,d2*d2)*tc)); break; }
						case 7: { float w = fabs(ta)+0.01; float wd = w*native_sin(z.x*tb)*native_cos(z.y*tc); aux->DE *= (1.0 + sf*wd*td); break; }
						case 8: { float ax=fmax(fabs(ta),0.01),ay=fmax(fabs(tb),0.01),az=fmax(fabs(tc),0.01); float ell = native_sqrt((z.x/ax)*(z.x/ax)+(z.y/ay)*(z.y/ay)+(z.z/az)*(z.z/az))-1.0; aux->DE *= (1.0 + sf*native_exp(-ell*ell*td)); break; }
						case 9: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float R=fabs(ta)+0.1,r=fabs(tb)+0.01; float td2 = (r2d-R)*(r2d-R)+z.z*z.z-r*r; aux->DE *= (1.0 + sf*native_exp(-fabs(td2)*tc)); break; }
						case 10: { float px=z.x,py=z.y,pz=z.z; float seg_d=fabs(pz)-fabs(ta); float cap_d=native_sqrt(px*px+py*py+fmax(seg_d,0.0)*fmax(seg_d,0.0))-fabs(tb); aux->DE *= (1.0 + sf*native_exp(-cap_d*cap_d*tc)); break; }
						case 11: { float theta=atan2(z.y,z.x); float phi2=acos(z.z/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),1e-21)); float m=fmax(ta,1.0); float sf_r=pow(fmax(pow(fabs(native_cos(m*theta/4.0)),tc)+pow(fabs(native_sin(m*theta/4.0)),tc),1e-21),-1.0/fmax(tb,0.1)); float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux->DE *= (1.0 + sf*native_exp(-fabs(r-sf_r*td)*5.0)); break; }
						case 12: { float jx=z.x*z.x-z.y*z.y+ta; float jy=2.0*z.x*z.y+tb; z.x=jx; z.y=jy; aux->DE *= 2.0*native_sqrt(jx*jx+jy*jy); break; }
						case 13: { float mx=z.x*z.x-z.y*z.y+z.x; float my=2.0*z.x*z.y+z.y; z.x=mx; z.y=my; aux->DE *= 2.0*native_sqrt(mx*mx+my*my); break; }
						case 14: { float a1=ta*M_PI_F/180.0; float a2=tb*M_PI_F/180.0; float ca1=native_cos(a1),sa1=native_sin(a1); float newx=z.x+z.x*ca1-z.y*sa1; float newy=z.y+z.x*sa1+z.y*ca1; z.x=newx*0.5; z.y=newy*0.5; z.z*=tc; aux->DE *= fabs(tc); break; }
						case 15: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float koch_amp = ta*native_sin(r*tb*10.0); aux->DE *= (1.0 + sf*koch_amp*koch_amp); break; }
						case 16: { float scale4 = fabs(ta)+1.0; if(z.x+z.y<0.0){float t=z.x;z.x=-z.y;z.y=-t;} if(z.x+z.z<0.0){float t=z.x;z.x=-z.z;z.z=-t;} if(z.y+z.z<0.0){float t=z.y;z.y=-z.z;z.z=-t;} z = z*scale4 - (float4)(1,1,1,0)*(scale4-1.0)*tb; aux->DE = aux->DE*scale4+1.0; break; }
						case 17: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(r<1e-21)r=1e-21; float mde=ta*ta/r/r; z*=mde; aux->DE*=mde; break; }
						case 18: { float h=native_sin(z.x*ta*12.9898+z.y*tb*78.233+z.z*tc*45.164)*43758.5453; h=h-floor(h); z.x+=h*td*0.1; z.y+=(1.0-h)*td*0.1; break; }
						case 19: { float min_dist=fabs(ta)+0.1; float h=native_sin(z.x*12.9898+z.y*78.233)*43758.5453; h=h-floor(h); z.x=floor(z.x/min_dist+h)*min_dist; z.y=floor(z.y/min_dist+h)*min_dist; break; }
						case 20: { float h=native_sin(z.x*12.9898+z.y*78.233+z.z*45.164)*43758.5453; h=fabs(h-floor(h)); z.x+=h*ta*0.1; z.y+=(1.0-h)*tb*0.1; z.z+=fabs(native_sin(h*tc))*td*0.1; break; }
						case 21: { float theta = (double)i * 2.39996322972865332; float r = native_sqrt((double)i+0.5)*ta; z.x += r*native_cos(theta)*sf*0.1; z.y += r*native_sin(theta)*sf*0.1; break; }
						case 22: { float phi3 = 1.6180339887; float r_n = ta/pow(phi3, (double)i); aux->DE *= 1.0/phi3; z *= r_n/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),0.01); break; }
						case 23: { float r_n = ta * native_exp(-(double)i * fabs(tb)); aux->DE *= native_exp(-fabs(tb)); z *= r_n/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),0.01); break; }
						case 24: { float n = fmax((double)i+1.0, 1.0); float r_n = ta / (1.0 + native_log(n)*tb); aux->DE *= 1.0/(1.0+native_log(n)*tb); z *= r_n/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),0.01); break; }
						case 25: { float n = fmax((double)i+1.0, 1.0); float p = fmax(fabs(ta), 0.1); aux->DE *= 1.0/pow(n,p); break; }
						case 26: { float sc = 3.0 + 0.5*native_sin((double)i*ta); z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 27: { float sx=fmax(ta,1.0),sy=fmax(tb,1.0),sz=fmax(tc,1.0); z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z.x=z.x*sx-(sx-1.0); z.y=z.y*sy-(sy-1.0); z.z=z.z*sz-(sz-1.0); aux->DE=aux->DE*fmax(fmax(sx,sy),sz)+1.0; break; }
						case 28: { float h=native_sin(z.x*ta*127.1+z.y*ta*311.7+z.z*ta*74.7)*43758.5453; h=h-floor(h); float sc=3.0; z=fabs(z)+(float4)(h*tb,h*tb,h*tb,0)*0.1; if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 29: { float angle=ta*M_PI_F/180.0; float ca=native_cos(angle),sa=native_sin(angle); float nx=z.x*ca-z.y*sa; float ny=z.x*sa+z.y*ca; z.x=fabs(nx);z.y=fabs(ny);z.z=fabs(z.z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} float sc=3.0; z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 30: { float eps=fmax(fabs(ta),0.01); float sc=3.0; z.x=fabs(z.x);z.y=fabs(z.y);z.z=fabs(z.z); float t; if(z.x<z.y){t=z.x+(z.y-z.x)*0.5*(1.0+tanh((z.y-z.x)/eps));z.y=z.y-(z.y-z.x)*0.5*(1.0+tanh((z.y-z.x)/eps));z.x=z.y;z.y=t;} if(z.x<z.z){t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 31: { float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0)+(float4)(ta,tb,tc,0); aux->DE=aux->DE*sc+1.0; break; }
						case 32: { float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); z.x+=aux->const_c.x*ta; z.y+=aux->const_c.y*ta; z.z+=aux->const_c.z*ta; aux->DE=aux->DE*sc+1.0; break; }
						case 33: { float sc=3.0; float period=fmax(fabs(ta),0.1); z=(float4)(fmod(z.x+100.0*period,period)-period*0.5, fmod(z.y+100.0*period,period)-period*0.5, fmod(z.z+100.0*period,period)-period*0.5, z.w); z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 34: { float sc=3.0; float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<1e-21)r2=1e-21; float inv=ta*ta/r2; z*=inv; aux->DE*=inv; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 35: { float lim=fabs(ta)+0.5; if(z.x>lim)z.x=2.0*lim-z.x; if(z.x<-lim)z.x=-2.0*lim-z.x; if(z.y>lim)z.y=2.0*lim-z.y; if(z.y<-lim)z.y=-2.0*lim-z.y; if(z.z>lim)z.z=2.0*lim-z.z; if(z.z<-lim)z.z=-2.0*lim-z.z; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 36: { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=fabs(ta)*fabs(ta); float fixedR2=1.0; float m; if(r2<minR2)m=fixedR2/minR2; else if(r2<fixedR2)m=fixedR2/r2; else m=1.0; z*=m; aux->DE*=m; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 37: { int n=(int)fmax(ta,2.0); float angle=M_PI_F/n; for(int k=0;k<n;k++){float a=k*2.0*angle; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0){z.x-=2.0*d*native_cos(a);z.y-=2.0*d*native_sin(a);}} float sc=3.0; z=z*sc-(float4)(1,1,1,0)*(sc-1.0)*tb; aux->DE=aux->DE*sc+1.0; break; }
						case 38: { z.x=fabs(z.x);z.y=-fabs(z.y);z.z=fabs(z.z); float sc=3.0; if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0)*ta; aux->DE=aux->DE*sc+1.0; break; }
						case 39: { float twist_k=ta*0.01; float angle=twist_k*(double)i; float ca=native_cos(angle),sa=native_sin(angle); float nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 40: { float bend=ta*0.001; z.z+=bend*(z.x*z.x+z.y*z.y); float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 41: { float shear=ta*0.1; z.x+=shear*z.y; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 42: { float taper=ta*0.01; z.x*=(1.0-taper*z.z); z.y*=(1.0-taper*z.z); float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 43: { float period=fmax(fabs(ta),0.1); z=(float4)(fmod(z.x+100.0*period,period)-period*0.5, fmod(z.y+100.0*period,period)-period*0.5, fmod(z.z+100.0*period,period)-period*0.5, z.w); float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 44: { float sc1=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc1-(float4)(1,1,1,0)*(sc1-1.0); aux->DE=aux->DE*sc1+1.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc1-(float4)(1,1,1,0)*(sc1-1.0); aux->DE=aux->DE*sc1+1.0; break; }
						case 45: { float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*fabs(sc)+1.0; float surfScale=fabs(ta)+0.5; z.x=fabs(z.x+surfScale)-fabs(z.x-surfScale)-z.x; z.y=fabs(z.y+surfScale)-fabs(z.y-surfScale)-z.y; break; }
						case 46: { float sc=3.0; float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=fabs(ta)*fabs(ta); float fixedR2=1.0; float m; if(r2<minR2)m=fixedR2/minR2; else if(r2<fixedR2)m=fixedR2/r2; else m=1.0; z*=m; aux->DE=aux->DE*m; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 47: { float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; float k_angle=ta*M_PI_F/180.0; CVector3 nv(native_cos(k_angle),native_sin(k_angle),0); CVector3 zv=z.xyz; float dot=zv, nv); if(dot<0){zv=zv-nv*(2.0*dot); z=(float4)(zv,z.w);} break; }
						case 48: { float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; z+=(float4)(aux->const_c.x*ta,aux->const_c.y*ta,aux->const_c.z*ta,0)*tb; break; }
						case 49: { float sc=3.0+0.1*native_sin((double)i*ta); z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*fabs(sc)+1.0; z=(float4)(0.9*z.x+0.1*ta,0.9*z.y+0.1*tb,0.9*z.z+0.1*tc,z.w); break; }
						case 50: { float h1=native_sin(ta*z.x+tb*z.y+tc*z.z); float h2=native_sin(td*h1+ta*(double)i*0.1); float sc=3.0+sf*h2*0.1; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*fabs(sc)+1.0; break; }
						case 51: { float sc=3.0; CVector4 zz=fabs(z); float vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){float t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=(float4)(vals[0],vals[1],vals[2],vals[3])*sc-(float4)(1,1,1,1)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 52: { float sc=3.0; float v[5]={fabs(z.x),fabs(z.y),fabs(z.z),fabs(z.w),fabs(native_sin(z.x+z.y))}; for(int a=0;a<5;a++)for(int b=a+1;b<5;b++){if(v[a]<v[b]){float t=v[a];v[a]=v[b];v[b]=t;}} z=(float4)(v[0],v[1],v[2],v[3])*sc-(float4)(1,1,1,1)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 53: { float sc=3.0; z.w=ta; CVector4 zz=fabs(z); float vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){float t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=(float4)(vals[0],vals[1],vals[2],vals[3])*sc-(float4)(1,1,1,1)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 54: { float angle4d=ta*M_PI_F/180.0*(double)i; float ca=native_cos(angle4d),sa=native_sin(angle4d); float nx=z.x*ca-z.w*sa; z.w=z.x*sa+z.w*ca; z.x=nx; float sc=3.0; CVector4 zz=fabs(z); float vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){float t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=(float4)(vals[0],vals[1],vals[2],vals[3])*sc-(float4)(1,1,1,1)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 55: { float sc=3.0; CVector4 zz=fabs(z); float vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){float t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=(float4)(vals[0],vals[1],vals[2],vals[3])*sc-(float4)(1,1,1,1)*(sc-1.0)+(float4)(ta,tb,tc,td); aux->DE=aux->DE*sc+1.0; break; }
						case 56: { float sc=3.0; float qn=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w); z.w=qn*ta; CVector4 zz=fabs(z); float vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){float t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=(float4)(vals[0],vals[1],vals[2],vals[3])*sc-(float4)(1,1,1,1)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 57: { float sc=3.0; float qr=z.x,qi=z.y,qj=z.z,qk=z.w; z.x=qr*qi-qj*qk; z.y=qr*qj+qi*qk; z.z=qr*qk-qi*qj; z.w=qr*qr-qi*qi-qj*qj-qk*qk; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,1)*(sc-1.0)*ta; aux->DE=aux->DE*sc+1.0; break; }
						case 58: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w); float d=tanh(fmin(r*ta,10.0)); CVector4 unit=z/fmax(r,1e-21); z=unit*d; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); float ch=cosh(fmin(r*ta,20.0)); aux->DE=aux->DE*sc/(ch*ch)+1.0; break; }
						case 59: { float r4=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w); if(r4>1e-21){z/=r4;} float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0)*ta; aux->DE=aux->DE*sc+1.0; break; }
						case 60: { float r2d=native_sqrt(z.x*z.x+z.y*z.y); float theta=atan2(z.y,z.x); z.x=r2d; z.y=theta*ta; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); z.x=z.x*native_cos(z.y/fmax(ta,0.01))-z.z*native_sin(z.y/fmax(ta,0.01)); aux->DE=aux->DE*sc+1.0; break; }
						case 61: { float R=fabs(ta)+0.5; float r2d=native_sqrt(z.x*z.x+z.y*z.y); z.x=r2d-R; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 62: { float theta4=ta*M_PI_F/180.0; float ca=native_cos(theta4),sa=native_sin(theta4); float nx=z.z*ca-z.w*sa; z.w=z.z*sa+z.w*ca; z.z=nx; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 63: { float golden=2.39996322972865332; float theta=(double)i*golden*ta; z.x+=native_cos(theta)*tb*0.01; z.y+=native_sin(theta)*tb*0.01; z.z+=native_cos(theta*0.5)*tc*0.01; z.w=native_sin(theta*0.5)*td*0.01; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 64: { float D=2.7268; float sc=pow(3.0,D/3.0); z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0)*ta; aux->DE=aux->DE*sc+1.0; break; }
						case 65: { float h=native_sin(z.x*12.9898+z.y*78.233+z.z*45.164+(double)i*ta)*43758.5453; h=h-floor(h); float sc=3.0; z=fabs(z); float vals[3]={z.x,z.y,z.z}; if(h>0.5){if(vals[0]<vals[1]){float t=vals[0];vals[0]=vals[1];vals[1]=t;}} if(h>0.25){if(vals[0]<vals[2]){float t=vals[0];vals[0]=vals[2];vals[2]=t;}} if(h>0.75){if(vals[1]<vals[2]){float t=vals[1];vals[1]=vals[2];vals[2]=t;}} z=(float4)(vals[0],vals[1],vals[2],z.w)*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 66: { float sc=3.0; float sq32=0.866025; z=fabs(z); float d=z.x*sq32+z.y*0.5; if(d<0.0){z.x-=2.0*d*sq32;z.y-=d;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0)*ta; aux->DE=aux->DE*sc+1.0; break; }
						case 67: { float sc=3.0; float a60=M_PI_F/3.0; for(int k=0;k<6;k++){float a=k*a60; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0){z.x-=2.0*d*native_cos(a);z.y-=2.0*d*native_sin(a);}} z=z*sc-(float4)(1,1,1,0)*(sc-1.0)*ta; aux->DE=aux->DE*sc+1.0; break; }
						case 68: { float sc=3.0; float a45=M_PI_F/4.0; for(int k=0;k<8;k++){float a=k*a45; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0){z.x-=2.0*d*native_cos(a);z.y-=2.0*d*native_sin(a);}} z=z*sc-(float4)(1,1,1,0)*(sc-1.0)*ta; aux->DE=aux->DE*sc+1.0; break; }
						case 69: { float sc=3.0; float a30=M_PI_F/6.0; for(int k=0;k<12;k++){float a=k*a30; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0){z.x-=2.0*d*native_cos(a);z.y-=2.0*d*native_sin(a);}} z=z*sc-(float4)(1,1,1,0)*(sc-1.0)*ta; aux->DE=aux->DE*sc+1.0; break; }
						case 70: { float sc=3.0; float a72=M_PI_F*2.0/5.0; for(int k=0;k<5;k++){float a=k*a72; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0){z.x-=2.0*d*native_cos(a);z.y-=2.0*d*native_sin(a);}} z=z*sc-(float4)(1,1,1,0)*(sc-1.0)*ta; aux->DE=aux->DE*sc+1.0; break; }
						case 71: { float sc=3.0; float a60=M_PI_F/3.0; for(int k=0;k<6;k++){float a=k*a60; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0){z.x-=2.0*d*native_cos(a);z.y-=2.0*d*native_sin(a);}} z=z*sc-(float4)(1,1,1,0)*(sc-1.0)*ta; aux->DE=aux->DE*sc+1.0; break; }
						case 72: { float sc=3.0; float a45=M_PI_F/4.0; for(int k=0;k<8;k++){float a=k*a45; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0){z.x-=2.0*d*native_cos(a);z.y-=2.0*d*native_sin(a);}} z=z*sc-(float4)(1,1,1,0)*(sc-1.0)*ta; aux->DE=aux->DE*sc+1.0; break; }
						case 73: { float sc=3.0; float a36=M_PI_F/5.0; for(int k=0;k<10;k++){float a=k*a36; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0){z.x-=2.0*d*native_cos(a);z.y-=2.0*d*native_sin(a);}} z=z*sc-(float4)(1,1,1,0)*(sc-1.0)*ta; aux->DE=aux->DE*sc+1.0; break; }
						case 74: { int n=(int)fmax(ta,3.0); float sc=3.0; float aStep=M_PI_F*2.0/n; for(int k=0;k<n&&k<16;k++){float a=k*aStep; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0){z.x-=2.0*d*native_cos(a);z.y-=2.0*d*native_sin(a);}} z=z*sc-(float4)(1,1,1,0)*(sc-1.0)*tb; aux->DE=aux->DE*sc+1.0; break; }
						case 75: { float sc=3.0; int n=(int)fmax(ta,3.0); float amp=fabs(tb); float theta=atan2(z.y,z.x); float r2d=native_sqrt(z.x*z.x+z.y*z.y); float star_r=r2d*(1.0+amp*native_cos(n*theta)); z.x=star_r*native_cos(theta); z.y=star_r*native_sin(theta); z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 76: { float sc=3.0; float theta=atan2(z.y,z.x); float r2d=native_sqrt(z.x*z.x+z.y*z.y); float heart_r=r2d*(1.0-native_sin(theta)*fabs(ta)); z.x=heart_r*native_cos(theta); z.y=heart_r*native_sin(theta); z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 77: { float spiral_a=ta*0.01*(double)i; float ca=native_cos(spiral_a),sa=native_sin(spiral_a); float nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 78: { float r2=z.x*z.x+z.y*z.y; z.z+=ta*0.001*r2; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 79: { float r2d=native_sqrt(z.x*z.x+z.y*z.y); float taper_w=1.0-ta*0.01*fabs(r2d); z.x*=taper_w; z.y*=taper_w; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 80: { float twist_a=ta*0.01*native_sqrt(z.x*z.x+z.y*z.y); float ca=native_cos(twist_a),sa=native_sin(twist_a); float nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 81: { float eps=fmax(fabs(ta),0.01); float sc=3.0; z=fabs(z); float t; if(z.x<z.y){float blend=0.5+0.5*tanh((z.y-z.x)/eps);t=z.x*(1.0-blend)+z.y*blend;z.y=z.y*(1.0-blend)+z.x*blend;z.x=t;} if(z.x<z.z){t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 82: { float h=native_sin(z.x*ta*127.1+z.y*ta*311.7+z.z*ta*74.7)*43758.5453; h=h-floor(h); z+=(float4)(h,1.0-h,h*0.5,0)*tb*0.01; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 83: { float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0)+(float4)(ta,tb,tc,0); aux->DE=aux->DE*sc+1.0; break; }
						case 84: { float period=fmax(fabs(ta),0.1); z=(float4)(fmod(fabs(z.x)+100.0*period,period)-period*0.5, fmod(fabs(z.y)+100.0*period,period)-period*0.5, fmod(fabs(z.z)+100.0*period,period)-period*0.5, z.w); float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 85: { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<1e-21)r2=1e-21; float inv=ta*ta/r2; z*=inv; aux->DE*=inv; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 86: { float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux->DE*=(1.0+sf*native_exp(-r*ta)*tb); break; }
						case 87: { float sc=3.0; if(z.x+z.y<0.0){float t=z.x;z.x=-z.y;z.y=-t;} if(z.x+z.z<0.0){float t=z.x;z.x=-z.z;z.z=-t;} if(z.y+z.z<0.0){float t=z.y;z.y=-z.z;z.z=-t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0)*ta; aux->DE=aux->DE*sc+1.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 88: { float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; float koch_scale=2.0*ta; z.x=fabs(z.x)-koch_scale*0.5; z.y=fabs(z.y)-koch_scale*0.5; break; }
						case 89: { float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; if(z.x>0)z.x=-(z.x-1.0); break; }
						case 90: { float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; float fern_angle=ta*M_PI_F/180.0; float ca=native_cos(fern_angle),sa=native_sin(fern_angle); float nx=z.x*ca-z.z*sa; z.z=z.x*sa+z.z*ca; z.x=nx; z*=0.85*tb; aux->DE*=0.85*fabs(tb); break; }
						case 91: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; float shell=fabs(r-ta)-tb; aux->DE*=(1.0+sf*native_exp(-shell*shell*tc)); break; }
						case 92: { float period=fmax(fabs(ta),0.1); z=(float4)(fmod(z.x+100.0*period,period)-period*0.5, fmod(z.y+100.0*period,period)-period*0.5, fmod(z.z+100.0*period,period)-period*0.5, z.w); float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 93: { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<1e-21)r2=1e-21; float inv=ta*ta/r2; z*=inv; aux->DE*=inv; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 94: { float clip=fabs(ta); z.x=fmin(fmax(z.x,-clip),clip); z.y=fmin(fmax(z.y,-clip),clip); z.z=fmin(fmax(z.z,-clip),clip); float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 95: { float lim=fabs(ta)+0.5; if(z.x>lim)z.x=2.0*lim-z.x; if(z.x<-lim)z.x=-2.0*lim-z.x; if(z.y>lim)z.y=2.0*lim-z.y; if(z.y<-lim)z.y=-2.0*lim-z.y; if(z.z>lim)z.z=2.0*lim-z.z; if(z.z<-lim)z.z=-2.0*lim-z.z; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 96: { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=fabs(ta)*fabs(ta); float fixedR2=1.0; float m; if(r2<minR2)m=fixedR2/minR2; else if(r2<fixedR2)m=fixedR2/r2; else m=1.0; z*=m; aux->DE*=m; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 97: { float angle=ta*M_PI_F/180.0*(double)i; float ca=native_cos(angle),sa=native_sin(angle); float nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+1.0; break; }
						case 98: { float sc=3.0*(1.0+sf*0.1*native_sin((double)i*ta)); z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*fabs(sc)+1.0; break; }
						case 99: { float sc=3.0; float offset=fabs(ta); z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*sc+offset; break; }
						case 100: { float h1=native_sin(ta*z.x+tb*z.y+tc*z.z); float h2=native_sin(td*h1+ta*(double)i*0.1); float sc=3.0+sf*h2*0.05; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0)*(sc-1.0); aux->DE=aux->DE*fabs(sc)+1.0; break; }
					}
				}

			// DE tweak (per-section iteration range)
			if (i >= mut->deIterStart && i < mut->deIterStop) {
			if (mut->deScale != 1.0f) aux.DE *= mut->deScale;

			// DE tweak (Familie 10)
			if (mut->deTweak == 1) aux.DE = native_log(1.0f + fabs(aux.DE));
			else if (mut->deTweak == 2) aux.DE = native_exp(aux.DE) - 1.0f;
			else if (mut->deTweak == 3) { float noise = mut->deTweakP1 * native_sin(z.x*13.7f + z.y*7.3f + z.z*11.1f); aux.DE += noise; }
			else if (mut->deTweak == 4) { aux.DE *= (1.0f + mut->deTweakP1 * native_sin(mut->deTweakP2 * aux.dist)); }
			else if (mut->deTweak == 5) aux.DE *= 0.9f;
			else if (mut->deTweak == 6) aux.DE *= 1.1f;
			} // end DE iteration range

			// Orbit trap
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
						float distFromAxis = native_sqrt(colorZ.x * colorZ.x + colorZ.y * colorZ.y);
						len = fabs(distFromAxis - fractalColoring->sphereRadius);
						break;
					}
					case fractalColoringCl_Torus:
					{
						float majorR = fractalColoring->sphereRadius;
						float distXY = native_sqrt(colorZ.x * colorZ.x + colorZ.y * colorZ.y) - majorR;
						len = native_sqrt(distXY * distXY + colorZ.z * colorZ.z);
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
							contribution = native_exp(-distance);
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
							float distFromLine = native_sqrt(zz.x * zz.x + zz.y * zz.y);
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
							float distFromAxis = native_sqrt(zz.x * zz.x + zz.y * zz.y);
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
							float distXY = native_sqrt(zz.x * zz.x + zz.y * zz.y) - majorR;
							float distTorus = native_sqrt(distXY * distXY + zz.z * zz.z);
							if (distTorus < minorR)
							{
								trapHit = true;
							}
							break;
						}
						case 7: // fractalizeShapeSpiral
						{
							float angle = atan2(zz.y, zz.x);
							float r = native_sqrt(zz.x * zz.x + zz.y * zz.y);
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

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

	int globalCap = consts->params.N;
	if (calcParam->normalCalculationMode && calcParam->iterThreshMode) globalCap *= 5;
	if (mode == calcModeColouring) globalCap *= 4;
	if (maxN > globalCap) maxN = globalCap;

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

#ifdef USE_MUTATION
	// v7.5 — Julia start mode (z₀ override, GPU)
	{
		__constant sClFormulaMutationParams *jm0 = &consts->sequence.mutationParams[0];
		if (jm0->enabled && jm0->juliaStart != 0)
		{
			if (jm0->juliaStart == 1) z = aux.const_c; // z₀ = c
			else if (jm0->juliaStart == 2) z = z + aux.const_c; // z₀ = ray + c
			else if (jm0->juliaStart == 3) { aux.const_c = z; aux.c = z; z = (float4)(0.0f, 0.0f, 0.0f, 0.0f); }
			else if (jm0->juliaStart == 4) z = (float4)(aux.const_c.x, aux.const_c.y, aux.const_c.z, aux.const_c.w);
			else if (jm0->juliaStart == 5) { // inversion
				float r2 = dot(aux.const_c, aux.const_c);
				if (r2 > 1e-21f) z = aux.const_c * (1.0f / r2);
				else z = aux.const_c;
			}
			else if (jm0->juliaStart == 6) { // spherical
				float radius = (jm0->juliaCRadius != 0.0f) ? jm0->juliaCRadius : 1.0f;
				float cLen = length(aux.const_c);
				if (cLen > 1e-21f) z = aux.const_c * (radius / cLen);
				else z = (float4)(radius, 0.0f, 0.0f, 0.0f);
			}
			else if (jm0->juliaStart == 7) { // bipolar
				if (z.x >= 0.0f) z = aux.const_c;
				else z = (float4)(jm0->juliaBipolarCRx, jm0->juliaBipolarCRy, jm0->juliaBipolarCRz, 0.0f);
			}
			else if (jm0->juliaStart == 8) { // lattice
				float grid = (jm0->juliaCRadius != 0.0f) ? jm0->juliaCRadius : 1.0f;
				z.x = floor(aux.const_c.x / grid + 0.5f) * grid;
				z.y = floor(aux.const_c.y / grid + 0.5f) * grid;
				z.z = floor(aux.const_c.z / grid + 0.5f) * grid;
			}
			else if (jm0->juliaStart == 9) { // perturb
				float eps = (jm0->juliaStartEpsilon != 0.0f) ? jm0->juliaStartEpsilon : 0.001f;
				z = z + aux.const_c * eps;
			}
		}
	}
#endif // USE_MUTATION (julia start)

	// Cinema4D-style accumulator voor calcModeCubeOrbitTrap
	float3 accumZ = (float3)(0.0f, 0.0f, 0.0f);
	float accumWeight = 0.0f;
	float closestSdf = 1e10f;
	float3 closestZ = (float3)(0.0f, 0.0f, 0.0f);
	int closestIter = 0;

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
#ifdef USE_MUTATION
		// BUG-004: bounds check on sequence index
		if (sequence < 0 || sequence >= NUMBER_OF_FRACTALS) sequence = 0;
		float4 preMutZ = z;
		// BUG-003: clamp iteration stop to maxN
		int mutIterStopGpu = min(consts->sequence.mutationParams[sequence].iterationStop, maxN);
		bool mutationActive = consts->sequence.mutationParams[sequence].enabled
			&& i >= consts->sequence.mutationParams[sequence].iterationStart
			&& i < mutIterStopGpu;
#else
		bool mutationActive = false;
#endif

#ifdef ITERATION_WEIGHT
		if (effectiveWeight > 0.0f)
		{
#endif
#ifdef USE_MUTATION
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
			if (mut->inversionEnabled && i >= mut->invIterStart && i < mut->invIterStop && mut->inversionType != 0)
			{
				float4 z_orig_inv = z; float de_orig_inv = aux.DE;
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
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_1)
					case 1: // Ellipsoid Inversion
					{
						rr = (zz.x/a)*(zz.x/a) + (zz.y/b)*(zz.y/b) + (zz.z/c)*(zz.z/c);
						if (rr < 1e-21f) rr = 1e-21f;
						mde = 1.0f/rr;
						zz.x *= mde * a * a; zz.y *= mde * b * b; zz.z *= mde * c * c;
						mde = 1.0f/rr;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_2)
					case 2: // Cylinder Inversion
					{
						rr = zz.x * zz.x + zz.y * zz.y;
						if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr;
						zz.x *= mde; zz.y *= mde;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_3)
					case 3: // Torus Inversion
					{
						float rxy = native_sqrt(zz.x * zz.x + zz.y * zz.y);
						rr = (rxy - a) * (rxy - a) + zz.z * zz.z;
						if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr;
						zz *= mde;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_4)
					case 4: // Hyperboloid Inversion
					{
						rr = (zz.x/a)*(zz.x/a) + (zz.y/b)*(zz.y/b) - (zz.z/c)*(zz.z/c);
						if (fabs(rr) < 1e-21f) rr = 1e-21f;
						mde = 1.0f / fabs(rr);
						zz *= mde;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_5)
					case 5: // Paraboloid Inversion
					{
						rr = zz.x * zz.x + zz.y * zz.y - a * zz.z;
						if (fabs(rr) < 1e-21f) rr = 1e-21f;
						mde = 1.0f / fabs(rr);
						zz *= mde;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_6)
					case 6: // Cone Inversion
					{
						float tanA = tan(mut->invAngle * M_PI_F / 180.0f);
						rr = zz.x * zz.x + zz.y * zz.y - tanA * tanA * zz.z * zz.z;
						if (fabs(rr) < 1e-21f) rr = 1e-21f;
						mde = 1.0f / fabs(rr);
						zz *= mde;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_7)
					case 7: // Saddle Inversion
					{
						rr = (zz.x/a)*(zz.x/a) - (zz.y/b)*(zz.y/b) - zz.z;
						if (fabs(rr) < 1e-21f) rr = 1e-21f;
						mde = 1.0f / fabs(rr);
						zz *= mde;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_8)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_9)
					case 9: // Lemniscate Inversion
					{
						float x2 = zz.x * zz.x, y2 = zz.y * zz.y;
						rr = (x2 + y2) * (x2 + y2) - a * a * (x2 - y2);
						if (fabs(rr) < 1e-21f) rr = 1e-21f;
						mde = 1.0f / fabs(rr);
						zz *= mde;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_10)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_11)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_12)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_13)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_14)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_15)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_16)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_17)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_18)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_19)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_20)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_21)
					case 21: // Inversion with Pre-Rotation (already handled by invPreRotMatrix)
					{
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_22)
					case 22: // Inversion with Pre-Shear
					{
						zz.x += mut->invAmplitude * zz.y;
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						zz.x -= mut->invAmplitude * zz.y;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_23)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_24)
					case 24: // Inversion with Pre-Abs
					{
						zz.x = fabs(zz.x); zz.y = fabs(zz.y); zz.z = fabs(zz.z);
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_25)
					case 25: // Inversion with Post-Scale Pulse
					{
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						float pulse = sc * (1.0f + 0.1f * native_sin((float)i * mut->invFrequency));
						zz *= pulse; mde *= fabs(pulse);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_26)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_27)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_28)
					case 28: // DE-Aware Inversion
					{
						if (aux.DE < mut->invThreshold)
						{
							rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
							mde = R * R / rr; zz *= mde;
						}
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_29)
					case 29: // Color-Trigger Inversion
					{
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						aux.color += mut->invColorFactor * fabs(mde - 1.0f);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_30)
					case 30: // Orbit-Trap Inversion
					{
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						float trap = length(zz);
						if (trap < aux.color) aux.color = trap;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_31)
					case 31: // Quaternion Inversion
					{
						float4 q = (float4){zz.x, zz.y, zz.z, z.w};
						float qn = dot(q, q); if (qn < 1e-21f) qn = 1e-21f;
						mde = 1.0f / qn;
						q = (float4){q.x, -q.y, -q.z, -q.w} * mde;
						zz = q.xyz; z.w = q.w;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_32)
					case 32: // Dual Complex Inversion
					{
						float n1 = zz.x * zz.x + zz.y * zz.y; if (n1 < 1e-21f) n1 = 1e-21f;
						float n2 = zz.z * zz.z + z.w * z.w; if (n2 < 1e-21f) n2 = 1e-21f;
						zz.x /= n1; zz.y /= -n1;
						zz.z /= n2; z.w /= -n2;
						mde = max(1.0f / n1, 1.0f / n2);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_33)
					case 33: // Split Complex Inversion
					{
						float denom = zz.x * zz.x - zz.y * zz.y;
						if (fabs(denom) < 1e-21f) denom = 1e-21f;
						mde = 1.0f / fabs(denom);
						zz.x = zz.x / denom; zz.y = -zz.y / denom;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_34)
					case 34: // Dual Number Inversion
					{
						if (fabs(zz.x) < 1e-21f) zz.x = 1e-21f;
						mde = 1.0f / (zz.x * zz.x);
						float ox = 1.0f / zz.x;
						float oy = -zz.y / (zz.x * zz.x);
						zz.x = ox; zz.y = oy;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_35)
					case 35: // Octonion Inversion
					{
						float on = dot(zz, zz) + z.w * z.w;
						if (on < 1e-21f) on = 1e-21f;
						mde = 1.0f / on;
						zz *= mde; z.w *= -mde;
						zz.y = -zz.y; zz.z = -zz.z;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_36)
					case 36: // Sedenion Inversion
					{
						float sn = dot(zz, zz) + z.w * z.w;
						if (sn < 1e-21f) sn = 1e-21f;
						mde = 1.0f / sn;
						zz = (float3){zz.x, -zz.y, -zz.z} * mde;
						z.w *= -mde;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_37)
					case 37: // Clifford Algebra Inversion
					{
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = 1.0f / rr;
						zz *= mde;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_38)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_39)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_40)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_41)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_42)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_43)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_44)
					case 44: // Inversion × Kleinian
					{
						float3 dynC = zz * mut->invAmplitude;
						rr = dot(zz - dynC, zz - dynC); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr;
						zz = dynC + (zz - dynC) * mde;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_45)
					case 45: // Inversion × Julia
					{
						float3 jc = (float3){mut->invCenter2X, mut->invCenter2Y, mut->invCenter2Z};
						rr = dot(zz - jc, zz - jc); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr;
						zz = jc + (zz - jc) * mde;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_46)
					case 46: // Inversion × IFS
					{
						float3 ifs_c = (float3){a, b, c};
						float d = dot(zz - ifs_c, zz - ifs_c); if (d < 1e-21f) d = 1e-21f;
						mde = R * R / d;
						zz = ifs_c + (zz - ifs_c) * mde;
						zz.x = fabs(zz.x); zz.y = fabs(zz.y);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_47)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_48)
					case 48: // Inversion × Parabolic
					{
						zz.x += mut->invAmplitude;
						zz.y += mut->invAmplitude * zz.x * zz.x;
						rr = dot(zz, zz); if (rr < 1e-21f) rr = 1e-21f;
						mde = R * R / rr; zz *= mde;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_49)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_INVERSIONTYPE_50)
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
#endif
					default: break;
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
				float inv_blend = clamp(mut->inversionWeight * mut->masterWeight, 0.0f, 1.0f);
				z = z_orig_inv + (z - z_orig_inv) * inv_blend;
				aux.DE = de_orig_inv + (aux.DE - de_orig_inv) * inv_blend;
			}

			// Fold injection (pre or both)
			if (i >= mut->foldIterStart && i < mut->foldIterStop
				&& mut->foldType != 0 && (mut->foldPosition == 0 || mut->foldPosition == 2))
			{
				switch (mut->foldType)
				{
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_1)
					case 1: // box fold
						if (fabs(z.x) > mut->foldLimit) z.x = sign(z.x) * mut->foldValue - z.x;
						if (fabs(z.y) > mut->foldLimit) z.y = sign(z.y) * mut->foldValue - z.y;
						if (fabs(z.z) > mut->foldLimit) z.z = sign(z.z) * mut->foldValue - z.z;
						break;
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_2)
					case 2: // sphere fold
					{
						float rr = z.x*z.x + z.y*z.y + z.z*z.z;
						float minR2 = mut->foldLimit * mut->foldLimit;
						float fixR2 = mut->foldValue * mut->foldValue;
						if (rr < minR2) { z *= fixR2/minR2; aux.DE *= fixR2/minR2; }
						else if (rr < fixR2) { z *= fixR2/rr; aux.DE *= fixR2/rr; }
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_3)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_4)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_5)
					case 5: // abs fold (tglad)
					{
						z.x = fabs(z.x + mut->foldLimit) - fabs(z.x - mut->foldLimit) - z.x;
						z.y = fabs(z.y + mut->foldLimit) - fabs(z.y - mut->foldLimit) - z.y;
						z.z = fabs(z.z + mut->foldLimit) - fabs(z.z - mut->foldLimit) - z.z;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_6)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_7)
					case 7: // octahedral fold
					{
						if (z.x + z.y < 0) { float tx = -z.y; z.y = -z.x; z.x = tx; }
						if (z.x + z.z < 0) { float tx = -z.z; z.z = -z.x; z.x = tx; }
						if (z.y + z.z < 0) { float ty = -z.z; z.z = -z.y; z.y = ty; }
						if (z.x - z.y < 0) { float tx = z.y; z.y = z.x; z.x = tx; }
						if (z.x - z.z < 0) { float tx = z.z; z.z = z.x; z.x = tx; }
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_8)
					case 8: // smooth fold (tanh)
					{
						float k = (mut->foldLimit > 0.0f) ? mut->foldLimit : 1.0f;
						z.x -= tanh(k * z.x);
						z.y -= tanh(k * z.y);
						z.z -= tanh(k * z.z);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_9)
					case 9: // polynomial fold (Chebyshev z³-3z)
					{
						z.x = z.x * z.x * z.x - 3.0f * z.x;
						z.y = z.y * z.y * z.y - 3.0f * z.y;
						z.z = z.z * z.z * z.z - 3.0f * z.z;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_10)
					case 10: // circular fold
					{
						float rad = (mut->foldValue > 0.0f) ? mut->foldValue : 1.0f;
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						if (r > 1e-21f) { float s = rad / r; z.x *= s; z.y *= s; z.z *= s; }
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_11)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_12)
					case 12: // sinusoidal fold
					{
						float a = mut->foldValue;
						float b = (mut->foldLimit > 0.0f) ? mut->foldLimit : 1.0f;
						z.x += a * native_sin(b * z.x);
						z.y += a * native_sin(b * z.y);
						z.z += a * native_sin(b * z.z);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_13)
					case 13: // exponential fold
					{
						z.x *= native_exp(-z.x * z.x);
						z.y *= native_exp(-z.y * z.y);
						z.z *= native_exp(-z.z * z.z);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_14)
					case 14: // logarithmic fold
					{
						float rx = fabs(z.x); float ry = fabs(z.y); float rz = fabs(z.z);
						z.x *= native_log(1.0f + rx);
						z.y *= native_log(1.0f + ry);
						z.z *= native_log(1.0f + rz);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_15)
					case 15: // power fold
					{
						float p = (mut->foldValue > 0.0f) ? mut->foldValue : 2.0f;
						float ax = fabs(z.x); float ay = fabs(z.y); float az = fabs(z.z);
						z.x = sign(z.x) * native_powr(max(ax, 1e-21f), p);
						z.y = sign(z.y) * native_powr(max(ay, 1e-21f), p);
						z.z = sign(z.z) * native_powr(max(az, 1e-21f), p);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_16)
					case 16: // smooth abs
					{
						float k = (mut->foldLimit > 0.0f) ? mut->foldLimit : 5.0f;
						z.x = z.x * tanh(k * z.x);
						z.y = z.y * tanh(k * z.y);
						z.z = z.z * tanh(k * z.z);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_17)
					case 17: // modulo wrap
					{
						float period = (mut->foldValue > 0.0f) ? mut->foldValue : 2.0f;
						z.x = fmod(z.x + period * 0.5f, period) - period * 0.5f;
						z.y = fmod(z.y + period * 0.5f, period) - period * 0.5f;
						z.z = fmod(z.z + period * 0.5f, period) - period * 0.5f;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_18)
					case 18: // nested abs
					{
						float c = (mut->foldLimit > 0.0f) ? mut->foldLimit : 1.0f;
						z.x = fabs(fabs(z.x) - c);
						z.y = fabs(fabs(z.y) - c);
						z.z = fabs(fabs(z.z) - c);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_19)
					case 19: // sawtooth
					{
						z.x = 2.0f * (z.x * 0.5f - floor(z.x * 0.5f + 0.5f));
						z.y = 2.0f * (z.y * 0.5f - floor(z.y * 0.5f + 0.5f));
						z.z = 2.0f * (z.z * 0.5f - floor(z.z * 0.5f + 0.5f));
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_20)
					case 20: // Bipolar
					{
						float c1 = mut->foldLimit;
						float c2 = -mut->foldLimit;
						z.x = fabs(z.x - c1) - fabs(z.x - c2);
						z.y = fabs(z.y - c1) - fabs(z.y - c2);
						z.z = fabs(z.z - c1) - fabs(z.z - c2);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_21)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_22)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_23)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_24)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_25)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_26)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_27)
					case 27: // TriangleWave
					{
						z.x = 2.0f * fabs(z.x * 0.5f - floor(z.x * 0.5f + 0.5f));
						z.y = 2.0f * fabs(z.y * 0.5f - floor(z.y * 0.5f + 0.5f));
						z.z = 2.0f * fabs(z.z * 0.5f - floor(z.z * 0.5f + 0.5f));
						break;
					}
#endif
				}
			}

			// Component swizzle
			switch (mut->swizzle)
			{
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SWIZZLE_0)
				case 0: break;
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SWIZZLE_1)
				case 1: { float t = z.y; z.y = z.z; z.z = t; } break;
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SWIZZLE_2)
				case 2: { float t = z.x; z.x = z.y; z.y = t; } break;
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SWIZZLE_3)
				case 3: { float t = z.x; z.x = z.y; z.y = z.z; z.z = t; } break;
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SWIZZLE_4)
				case 4: { float t = z.z; z.z = z.y; z.y = z.x; z.x = t; } break;
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SWIZZLE_5)
				case 5: { float t = z.x; z.x = z.z; z.z = t; } break;
#endif
			}
#endif

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
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_1)
					case 1: // SinPower
					{
						float p = mut->mathP1;
						mathZ.x = sign(native_sin(z.x)) * pow(fabs(native_sin(z.x)), p);
						mathZ.y = sign(native_sin(z.y)) * pow(fabs(native_sin(z.y)), p);
						mathZ.z = sign(native_sin(z.z)) * pow(fabs(native_sin(z.z)), p);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_2)
					case 2: // CoshField
					{
						float freq = mut->mathP1;
						float amp = mut->mathP2;
						mathZ.x = z.x + amp * (cosh(z.y * freq) - 1.0f);
						mathZ.y = z.y + amp * (cosh(z.z * freq) - 1.0f);
						mathZ.z = z.z + amp * (cosh(z.x * freq) - 1.0f);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_3)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_4)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_5)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_6)
					case 6: // ComplexMul
					{
						float cr = mut->mathP1;
						float ci = mut->mathP2;
						mathZ.x = z.x * cr - z.y * ci;
						mathZ.y = z.x * ci + z.y * cr;
						mathZ.z = z.z * native_sqrt(cr*cr + ci*ci);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_7)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_8)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_9)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_10)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_11)
					case 11: // HyperbolicRot
					{
						float angle = mut->mathP1;
						float ch = cosh(angle); float sh = sinh(angle);
						mathZ.x = z.x * ch + z.z * sh;
						mathZ.z = z.x * sh + z.z * ch;
						mathZ.y = z.y;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_12)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_13)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_14)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_15)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_16)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_17)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_18)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_19)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_20)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_21)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_22)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_23)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_24)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_25)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_26)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_27)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_28)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_29)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MATHTYPE_30)
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
#endif
					default: break;
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
#endif // USE_MUTATION (pre-fold)

#ifdef USE_MUTATION
		// v7.5 — Julia pre-fold injection (GPU, per-section iteration range)
		if (mutationActive
			&& i >= consts->sequence.mutationParams[sequence].juliaIterStart
			&& i < consts->sequence.mutationParams[sequence].juliaIterStop
			&& consts->sequence.mutationParams[sequence].juliaInjection != 0)
		{
			__constant sClFormulaMutationParams *jm = &consts->sequence.mutationParams[sequence];
			// BUG-002: fallback if aux.const_c is zero
			if (length(aux.const_c) < 1e-21f) aux.const_c = z;
			// BUG-005: NaN/Inf guard on julia params
			float safeCMulGpu = jm->juliaCMul;
			if (isnan(safeCMulGpu) || isinf(safeCMulGpu)) safeCMulGpu = 1.0f;
			float4 juliaC = aux.const_c * safeCMulGpu;
			// C-transform (with per-subsystem iter range + strength)
			if (jm->juliaCTransform != 0
				&& i >= jm->juliaCTransformIterStart && i < jm->juliaCTransformIterStop) {
			float4 juliaCPre = juliaC; // save untransformed for strength blending
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
			} else if (jm->juliaCTransform == 6) { // logarithmic
				float cLen = length(juliaC);
				if (cLen > 1e-21f) juliaC = juliaC * (native_log(cLen) / cLen);
			} else if (jm->juliaCTransform == 7) { // exponential
				juliaC.x = native_exp(juliaC.x);
				juliaC.y = native_exp(juliaC.y);
				juliaC.z = native_exp(juliaC.z);
			} else if (jm->juliaCTransform == 8) { // inversion
				float r2 = dot(juliaC, juliaC);
				if (r2 > 1e-21f) juliaC = juliaC * (1.0f / r2);
			} else if (jm->juliaCTransform == 9) { // box fold on c
				float lim = (jm->juliaBoxFoldLimit != 0.0f) ? jm->juliaBoxFoldLimit : 1.0f;
				if (juliaC.x > lim) juliaC.x = 2.0f*lim - juliaC.x;
				else if (juliaC.x < -lim) juliaC.x = -2.0f*lim - juliaC.x;
				if (juliaC.y > lim) juliaC.y = 2.0f*lim - juliaC.y;
				else if (juliaC.y < -lim) juliaC.y = -2.0f*lim - juliaC.y;
				if (juliaC.z > lim) juliaC.z = 2.0f*lim - juliaC.z;
				else if (juliaC.z < -lim) juliaC.z = -2.0f*lim - juliaC.z;
			} else if (jm->juliaCTransform == 10) { // spiral
				float angle = jm->juliaSpiralAngle * M_PI_F / 180.0f;
				float cs = native_cos(angle), sn = native_sin(angle);
				float tnx = juliaC.x * cs - juliaC.y * sn;
				float tny = juliaC.x * sn + juliaC.y * cs;
				juliaC.x = tnx; juliaC.y = tny;
			} else if (jm->juliaCTransform == 11) { // mandelbrot iterate
				float cx = juliaC.x, cy = juliaC.y, cz = juliaC.z;
				juliaC.x = cx*cx - cy*cy + aux.const_c.x * jm->juliaCMul;
				juliaC.y = 2.0f*cx*cy + aux.const_c.y * jm->juliaCMul;
				juliaC.z = cz + aux.const_c.z * jm->juliaCMul;
			}
			// Blend C-transform by strength (0=bypass, 1=full transform)
			float ctStr = jm->juliaCTransformStrength;
			if (ctStr != 1.0f) juliaC = juliaCPre + (juliaC - juliaCPre) * ctStr;
			} // end C-transform iter range check
			// Dynamic modulation (with per-subsystem iter range + strength)
			if (jm->juliaDynamic != 0
				&& i >= jm->juliaDynamicIterStart && i < jm->juliaDynamicIterStop) {
			float4 juliaCPreDyn = juliaC;
			// Dynamic modulation
			if (jm->juliaDynamic == 1) juliaC *= (1.0f + 0.1f * length(z));
			else if (jm->juliaDynamic == 2) juliaC *= native_sin((float)i * jm->juliaPulseFreq) * jm->juliaPulseAmp;
			else if (jm->juliaDynamic == 3) { if (length(z) > consts->sequence.bailout[sequence] * 0.5f) juliaC *= 2.0f; }
			else if (jm->juliaDynamic == 4) juliaC = juliaC * (1.0f - jm->juliaAbsorb) + z * jm->juliaAbsorb;
			else if (jm->juliaDynamic == 5) juliaC = juliaC + (z - lastZ) * 0.1f;
			else if (jm->juliaDynamic == 6) { // exp decay
				float decay = (jm->juliaDecayRate != 0.0f) ? jm->juliaDecayRate : 0.1f;
				juliaC *= native_exp(-decay * (float)i);
			}
			else if (jm->juliaDynamic == 7) { // saw
				float freq = (jm->juliaPulseFreq != 0.0f) ? jm->juliaPulseFreq : 0.5f;
				float t = (float)i * freq;
				juliaC *= (t - floor(t));
			}
			else if (jm->juliaDynamic == 8) { // smooth step
				float range = (float)(jm->juliaIterStop - jm->juliaIterStart);
				if (range > 0.0f) {
					float t = ((float)i - (float)jm->juliaIterStart) / range;
					t = t * t * (3.0f - 2.0f * t);
					juliaC *= t;
				}
			}
			else if (jm->juliaDynamic == 9) { // chaos
				float r = (jm->juliaChaosR != 0.0f) ? jm->juliaChaosR : 3.8f;
				float x = fmod(fabs(length(juliaC)) * 0.1f, 1.0f);
				x = r * x * (1.0f - x);
				juliaC *= x;
			}
			else if (jm->juliaDynamic == 10) { // spiral
				float angle = jm->juliaSpiralAngle * M_PI_F / 180.0f * (float)i;
				float cs = native_cos(angle), sn = native_sin(angle);
				float tnx = juliaC.x * cs - juliaC.y * sn;
				float tny = juliaC.x * sn + juliaC.y * cs;
				juliaC.x = tnx; juliaC.y = tny;
			}
			else if (jm->juliaDynamic == 11) { // bounce
				float freq = (jm->juliaPulseFreq != 0.0f) ? jm->juliaPulseFreq : 1.0f;
				juliaC *= fabs(native_sin((float)i * freq));
			}
			// Blend dynamic by strength
			float dynStr = jm->juliaDynamicStrength;
			if (dynStr != 1.0f) juliaC = juliaCPreDyn + (juliaC - juliaCPreDyn) * dynStr;
			} // end dynamic iter range check
			// Multi-C modes (with per-subsystem iter range + strength)
			if (jm->juliaMulti != 0
				&& i >= jm->juliaMultiIterStart && i < jm->juliaMultiIterStop) {
			float4 juliaCPreMulti = juliaC;
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
			else if (jm->juliaMulti == 6) { // octave noise
				float n1 = native_sin(z.x * jm->juliaNoiseFreq) * jm->juliaNoiseAmp;
				float n2 = native_sin(z.y * jm->juliaNoiseFreq * 2.0f) * jm->juliaNoiseAmp * 0.5f;
				float n3 = native_sin(z.z * jm->juliaNoiseFreq * 4.0f) * jm->juliaNoiseAmp * 0.25f;
				juliaC += (float4)(n1+n2+n3, n2+n3+n1*0.5f, n3+n1*0.25f+n2*0.5f, 0.0f);
			}
			else if (jm->juliaMulti == 7) { // phase shift
				float phase = (float)i * 2.0f * M_PI_F / 3.0f;
				juliaC += (float4)(jm->juliaFourierC2x, jm->juliaFourierC2y, jm->juliaFourierC2z, 0.0f) * native_sin(phase)
						+ (float4)(jm->juliaFourierC3x, jm->juliaFourierC3y, jm->juliaFourierC3z, 0.0f) * native_cos(phase);
			}
			else if (jm->juliaMulti == 8) { // orbit split
				int quadrant = (z.x >= 0.0f ? 1 : 0) + (z.y >= 0.0f ? 2 : 0);
				if (quadrant == 1) juliaC = (float4)(jm->juliaBipolarCRx, jm->juliaBipolarCRy, jm->juliaBipolarCRz, 0.0f);
				else if (quadrant == 2) juliaC = (float4)(jm->juliaFourierC2x, jm->juliaFourierC2y, jm->juliaFourierC2z, 0.0f);
				else if (quadrant == 3) juliaC = (float4)(jm->juliaFourierC3x, jm->juliaFourierC3y, jm->juliaFourierC3z, 0.0f);
			}
			else if (jm->juliaMulti == 9) { // iter modulo
				int phase = i % 3;
				if (phase == 1) juliaC = (float4)(jm->juliaFourierC2x, jm->juliaFourierC2y, jm->juliaFourierC2z, 0.0f);
				else if (phase == 2) juliaC = (float4)(jm->juliaFourierC3x, jm->juliaFourierC3y, jm->juliaFourierC3z, 0.0f);
			}
			else if (jm->juliaMulti == 10) { // dist band
				float d = length(z);
				float mid = (jm->juliaDistBandMid != 0.0f) ? jm->juliaDistBandMid : 1.0f;
				float far = (jm->juliaDistBandFar != 0.0f) ? jm->juliaDistBandFar : 2.0f;
				if (d > far) juliaC = (float4)(jm->juliaFourierC3x, jm->juliaFourierC3y, jm->juliaFourierC3z, 0.0f);
				else if (d > mid) juliaC = (float4)(jm->juliaFourierC2x, jm->juliaFourierC2y, jm->juliaFourierC2z, 0.0f);
			}
			else if (jm->juliaMulti == 11) { // random
				float seed = native_sin((float)i * 12.9898f + z.x * 78.233f) * 43758.5453f;
				seed = seed - floor(seed);
				if (seed > 0.66f) juliaC = (float4)(jm->juliaFourierC3x, jm->juliaFourierC3y, jm->juliaFourierC3z, 0.0f);
				else if (seed > 0.33f) juliaC = (float4)(jm->juliaFourierC2x, jm->juliaFourierC2y, jm->juliaFourierC2z, 0.0f);
			}
			// Blend multi-C by strength
			float multiStr = jm->juliaMultiStrength;
			if (multiStr != 1.0f) juliaC = juliaCPreMulti + (juliaC - juliaCPreMulti) * multiStr;
			} // end multi-C iter range check
			// Apply injection strength (scales final juliaC before adding to z)
			float injStr = jm->juliaInjectionStrength;
			if (injStr != 1.0f) juliaC *= injStr;
			// Injection point
			if (jm->juliaInjection == 1 || jm->juliaInjection == 4) z += juliaC; // pre-fold or dual
			else if (jm->juliaInjection == 5) { // pre-scale damping
				float r = length(z);
				float bail = consts->sequence.bailout[sequence];
				float factor = (bail > 1e-21f) ? r / bail : 1.0f;
				z += juliaC * factor;
			}
			else if (jm->juliaInjection == 7) { // alternating: pre on even
				if (i % 2 == 0) z += juliaC;
			}
			else if (jm->juliaInjection == 8) { // radial
				float r = length(z);
				float bail = consts->sequence.bailout[sequence];
				z += juliaC * ((bail > 1e-21f) ? r / bail : 1.0f);
			}
			else if (jm->juliaInjection == 9) { // conditional
				float threshold = (jm->juliaThreshold != 0.0f) ? jm->juliaThreshold : 1.0f;
				if (length(z) > threshold) z += juliaC;
			}
			else if (jm->juliaInjection == 10) { // gradient
				float range = (float)(jm->juliaIterStop - jm->juliaIterStart);
				float t = (range > 0.0f) ? ((float)i - (float)jm->juliaIterStart) / range : 1.0f;
				float endMul = (jm->juliaGradientEnd != 0.0f) ? jm->juliaGradientEnd : 0.0f;
				z += juliaC * (1.0f - t + endMul * t);
			}
			else if (jm->juliaInjection == 11) { // layered
				int mid = (jm->juliaIterStart + jm->juliaIterStop) / 2;
				if (i >= mid)
					z += (float4)(jm->juliaLayerC2x, jm->juliaLayerC2y, jm->juliaLayerC2z, 0.0f);
				else
					z += juliaC;
			}
			// DE correction for sharper rendering with mutations
			if (jm->juliaDEFactor != 1.0f) aux.DE *= jm->juliaDEFactor;
			// BUG-005: final NaN/Inf guard after julia injection
			if (isnan(z.x) || isinf(z.x) || isnan(z.y) || isinf(z.y)
				|| isnan(z.z) || isinf(z.z))
			{
				z = preMutZ;
			}
		}
#endif // USE_MUTATION (julia pre-fold)

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
			// Per-component controls for constant multiplier (works in both modes)
			float4 mul = consts->sequence.constantMultiplier[sequence];
			float4 cStart = consts->sequence.constCIterStart[sequence];
			float4 cStop = consts->sequence.constCIterStop[sequence];
			float4 cWeight = consts->sequence.constCWeight[sequence];
			float mx = (i >= (int)cStart.x && i < (int)cStop.x) ? mul.x * cWeight.x : 1.0f;
			float my = (i >= (int)cStart.y && i < (int)cStop.y) ? mul.y * cWeight.y : 1.0f;
			float mz = (i >= (int)cStart.z && i < (int)cStop.z) ? mul.z * cWeight.z : 1.0f;

			if (consts->sequence.juliaEnabled[sequence])
			{
				float4 juliaC = consts->sequence.juliaConstant[sequence];
				juliaC.x *= mx;
				juliaC.y *= my;
				juliaC.z *= mz;

				// Per-component iteration range + weight for Julia c
				float4 jStart = consts->sequence.juliaCIterStart[sequence];
				float4 jStop = consts->sequence.juliaCIterStop[sequence];
				float4 jWeight = consts->sequence.juliaCWeight[sequence];
				if (i < (int)jStart.x || i >= (int)jStop.x) juliaC.x = 0.0f;
				else juliaC.x *= jWeight.x;
				if (i < (int)jStart.y || i >= (int)jStop.y) juliaC.y = 0.0f;
				else juliaC.y *= jWeight.y;
				if (i < (int)jStart.z || i >= (int)jStop.z) juliaC.z = 0.0f;
				else juliaC.z *= jWeight.z;

				switch (fractal->formula)
				{
					case 64: // aboxMod1
					case 73: // amazingSurf
						z += (float4){juliaC.y, juliaC.x, juliaC.z, juliaC.w};
						break;
					default:
						z += juliaC;
						break;
				}
			}
			else
			{
				float4 c4;
				c4.x = aux.const_c.x * mx;
				c4.y = aux.const_c.y * my;
				c4.z = aux.const_c.z * mz;
				c4.w = 0.0f;

				switch (fractal->formula)
				{
					case 64: // aboxMod1
					case 73: // amazingSurf
						z += (float4){c4.y, c4.x, c4.z, c4.w};
						break;
					default:
						z += c4;
						break;
				}
			}
		}

#ifdef ITERATION_WEIGHT
		}
#endif

		// Per-iteration position/rotation/repeat transforms (per-axis iter range)
		{
			float3 pos = consts->params.common.fractalPosition;
			float3 ps = consts->params.common.positionIterStart;
			float3 pe = consts->params.common.positionIterStop;
			if (pos.x != 0.0f && i >= (int)ps.x && i < (int)pe.x) z.x += pos.x;
			if (pos.y != 0.0f && i >= (int)ps.y && i < (int)pe.y) z.y += pos.y;
			if (pos.z != 0.0f && i >= (int)ps.z && i < (int)pe.z) z.z += pos.z;

			float3 rot = consts->params.common.fractalRotation;
			float3 rs = consts->params.common.rotationIterStart;
			float3 re = consts->params.common.rotationIterStop;
			if (rot.x != 0.0f && i >= (int)rs.x && i < (int)re.x)
			{
				float rx = rot.x * M_PI_F / 180.0f;
				float cR = native_cos(rx), sR = native_sin(rx);
				float ty = z.y * cR - z.z * sR;
				float tz = z.y * sR + z.z * cR;
				z.y = ty; z.z = tz;
			}
			if (rot.y != 0.0f && i >= (int)rs.y && i < (int)re.y)
			{
				float ry = rot.y * M_PI_F / 180.0f;
				float cR = native_cos(ry), sR = native_sin(ry);
				float tx = z.x * cR + z.z * sR;
				float tz = -z.x * sR + z.z * cR;
				z.x = tx; z.z = tz;
			}
			if (rot.z != 0.0f && i >= (int)rs.z && i < (int)re.z)
			{
				float rz = rot.z * M_PI_F / 180.0f;
				float cR = native_cos(rz), sR = native_sin(rz);
				float tx = z.x * cR - z.y * sR;
				float ty = z.x * sR + z.y * cR;
				z.x = tx; z.y = ty;
			}

			float3 rep = consts->params.common.repeat;
			float3 rps = consts->params.common.repeatIterStart;
			float3 rpe = consts->params.common.repeatIterStop;
			if (rep.x != 0.0f && i >= (int)rps.x && i < (int)rpe.x)
				z.x = z.x - rep.x * round(z.x / rep.x);
			if (rep.y != 0.0f && i >= (int)rps.y && i < (int)rpe.y)
				z.y = z.y - rep.y * round(z.y / rep.y);
			if (rep.z != 0.0f && i >= (int)rps.z && i < (int)rpe.z)
				z.z = z.z - rep.z * round(z.z / rep.z);
		}

#ifdef USE_MUTATION
		// v7.5 — Julia mid/post injection (GPU, per-section iteration range)
		if (mutationActive
			&& i >= consts->sequence.mutationParams[sequence].juliaIterStart
			&& i < consts->sequence.mutationParams[sequence].juliaIterStop
			&& (consts->sequence.mutationParams[sequence].juliaInjection == 2
			|| consts->sequence.mutationParams[sequence].juliaInjection == 3
			|| consts->sequence.mutationParams[sequence].juliaInjection == 4
			|| consts->sequence.mutationParams[sequence].juliaInjection == 6
			|| consts->sequence.mutationParams[sequence].juliaInjection == 7))
		{
			__constant sClFormulaMutationParams *jm = &consts->sequence.mutationParams[sequence];
			// Type 7 (alternating): only inject post on odd iterations
			bool doPost = true;
			if (jm->juliaInjection == 7 && (i % 2 == 0)) doPost = false;
			if (doPost) {
			// BUG-002: fallback if aux.const_c is zero
			if (length(aux.const_c) < 1e-21f) aux.const_c = z;
			// BUG-005: NaN/Inf guard on julia params
			float safeCMulGpuMP = jm->juliaCMul;
			if (isnan(safeCMulGpuMP) || isinf(safeCMulGpuMP)) safeCMulGpuMP = 1.0f;
			float4 juliaC = aux.const_c * safeCMulGpuMP;
			// C-transform (with per-subsystem iter range + strength)
			if (jm->juliaCTransform != 0
				&& i >= jm->juliaCTransformIterStart && i < jm->juliaCTransformIterStop) {
			float4 juliaCPreCT = juliaC;
			if (jm->juliaCTransform == 1) {
				float cLen = length(juliaC);
				if (cLen > 1e-21f) juliaC = juliaC * (jm->juliaCRadius / cLen);
			} else if (jm->juliaCTransform == 2) {
				float denom = length(juliaC) + jm->juliaCMobiusD;
				if (fabs(denom) > 1e-21f)
					juliaC = (juliaC * jm->juliaCMobiusA + (float4)(jm->juliaCMobiusB, jm->juliaCMobiusB, jm->juliaCMobiusB, 0.0f)) * (1.0f / denom);
			} else if (jm->juliaCTransform == 3) {
				float3 jcR = Matrix33MulFloat3(jm->juliaCRotMatrix, juliaC.xyz);
				juliaC.xyz = jcR;
			} else if (jm->juliaCTransform == 4) {
				float r = length(juliaC);
				if (r > 1e-21f) {
					float th = atan2(juliaC.y, juliaC.x);
					float ph = acos(clamp(juliaC.z / r, -1.0f, 1.0f));
					float rp = native_powr(r, jm->juliaCPower);
					juliaC.x = rp * native_sin(ph * jm->juliaCPower) * native_cos(th * jm->juliaCPower);
					juliaC.y = rp * native_sin(ph * jm->juliaCPower) * native_sin(th * jm->juliaCPower);
					juliaC.z = rp * native_cos(ph * jm->juliaCPower);
				}
			} else if (jm->juliaCTransform == 5) {
				float cLen = length(juliaC);
				float qw = native_cos(cLen * 0.5f);
				float qs = (cLen > 1e-21f) ? native_sin(cLen * 0.5f) / cLen : 0.0f;
				float qi = juliaC.x * qs, qj = juliaC.y * qs, qk = juliaC.z * qs;
				float zw = 0.0f;
				float nx = qw*z.x + qi*zw + qj*z.z - qk*z.y;
				float ny = qw*z.y - qi*z.z + qj*zw + qk*z.x;
				float nz = qw*z.z + qi*z.y - qj*z.x + qk*zw;
				juliaC = (float4)(nx, ny, nz, 0.0f);
			} else if (jm->juliaCTransform == 6) {
				float cLen = length(juliaC);
				if (cLen > 1e-21f) juliaC = juliaC * (native_log(cLen) / cLen);
			} else if (jm->juliaCTransform == 7) {
				juliaC.x = native_exp(juliaC.x);
				juliaC.y = native_exp(juliaC.y);
				juliaC.z = native_exp(juliaC.z);
			} else if (jm->juliaCTransform == 8) {
				float r2 = dot(juliaC, juliaC);
				if (r2 > 1e-21f) juliaC = juliaC * (1.0f / r2);
			} else if (jm->juliaCTransform == 9) {
				float lim = (jm->juliaBoxFoldLimit != 0.0f) ? jm->juliaBoxFoldLimit : 1.0f;
				if (juliaC.x > lim) juliaC.x = 2.0f*lim - juliaC.x;
				else if (juliaC.x < -lim) juliaC.x = -2.0f*lim - juliaC.x;
				if (juliaC.y > lim) juliaC.y = 2.0f*lim - juliaC.y;
				else if (juliaC.y < -lim) juliaC.y = -2.0f*lim - juliaC.y;
				if (juliaC.z > lim) juliaC.z = 2.0f*lim - juliaC.z;
				else if (juliaC.z < -lim) juliaC.z = -2.0f*lim - juliaC.z;
			} else if (jm->juliaCTransform == 10) {
				float angle = jm->juliaSpiralAngle * M_PI_F / 180.0f;
				float cs = native_cos(angle), sn = native_sin(angle);
				float tnx = juliaC.x * cs - juliaC.y * sn;
				float tny = juliaC.x * sn + juliaC.y * cs;
				juliaC.x = tnx; juliaC.y = tny;
			} else if (jm->juliaCTransform == 11) {
				float cx = juliaC.x, cy = juliaC.y, cz = juliaC.z;
				juliaC.x = cx*cx - cy*cy + aux.const_c.x * jm->juliaCMul;
				juliaC.y = 2.0f*cx*cy + aux.const_c.y * jm->juliaCMul;
				juliaC.z = cz + aux.const_c.z * jm->juliaCMul;
			}
			// Blend C-transform by strength
			float ctStrMP = jm->juliaCTransformStrength;
			if (ctStrMP != 1.0f) juliaC = juliaCPreCT + (juliaC - juliaCPreCT) * ctStrMP;
			} // end C-transform iter range (mid/post)
			// Dynamic modulation (with per-subsystem iter range + strength)
			if (jm->juliaDynamic != 0
				&& i >= jm->juliaDynamicIterStart && i < jm->juliaDynamicIterStop) {
			float4 juliaCPreDynMP = juliaC;
			if (jm->juliaDynamic == 1) juliaC *= (1.0f + 0.1f * length(z));
			else if (jm->juliaDynamic == 2) juliaC *= native_sin((float)i * jm->juliaPulseFreq) * jm->juliaPulseAmp;
			else if (jm->juliaDynamic == 3) { if (length(z) > consts->sequence.bailout[sequence] * 0.5f) juliaC *= 2.0f; }
			else if (jm->juliaDynamic == 4) juliaC = juliaC * (1.0f - jm->juliaAbsorb) + z * jm->juliaAbsorb;
			else if (jm->juliaDynamic == 5) juliaC = juliaC + (z - lastZ) * 0.1f;
			else if (jm->juliaDynamic == 6) {
				float decay = (jm->juliaDecayRate != 0.0f) ? jm->juliaDecayRate : 0.1f;
				juliaC *= native_exp(-decay * (float)i);
			}
			else if (jm->juliaDynamic == 7) {
				float freq = (jm->juliaPulseFreq != 0.0f) ? jm->juliaPulseFreq : 0.5f;
				float t = (float)i * freq;
				juliaC *= (t - floor(t));
			}
			else if (jm->juliaDynamic == 8) {
				float range = (float)(jm->juliaIterStop - jm->juliaIterStart);
				if (range > 0.0f) {
					float t = ((float)i - (float)jm->juliaIterStart) / range;
					t = t * t * (3.0f - 2.0f * t);
					juliaC *= t;
				}
			}
			else if (jm->juliaDynamic == 9) {
				float r = (jm->juliaChaosR != 0.0f) ? jm->juliaChaosR : 3.8f;
				float x = fmod(fabs(length(juliaC)) * 0.1f, 1.0f);
				x = r * x * (1.0f - x);
				juliaC *= x;
			}
			else if (jm->juliaDynamic == 10) {
				float angle = jm->juliaSpiralAngle * M_PI_F / 180.0f * (float)i;
				float cs = native_cos(angle), sn = native_sin(angle);
				float tnx = juliaC.x * cs - juliaC.y * sn;
				float tny = juliaC.x * sn + juliaC.y * cs;
				juliaC.x = tnx; juliaC.y = tny;
			}
			else if (jm->juliaDynamic == 11) {
				juliaC *= fabs(native_sin((float)i * jm->juliaPulseFreq));
			}
			// Blend dynamic by strength
			float dynStrMP = jm->juliaDynamicStrength;
			if (dynStrMP != 1.0f) juliaC = juliaCPreDynMP + (juliaC - juliaCPreDynMP) * dynStrMP;
			} // end dynamic iter range (mid/post)
			// Apply injection strength
			float injStrMP = jm->juliaInjectionStrength;
			if (injStrMP != 1.0f) juliaC *= injStrMP;
			z += juliaC;
			// DE correction
			if (jm->juliaDEFactor != 1.0f) aux.DE *= jm->juliaDEFactor;
			} // end doPost
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
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_1)
					case 1:
						if (fabs(z.x) > mut->foldLimit) z.x = sign(z.x) * mut->foldValue - z.x;
						if (fabs(z.y) > mut->foldLimit) z.y = sign(z.y) * mut->foldValue - z.y;
						if (fabs(z.z) > mut->foldLimit) z.z = sign(z.z) * mut->foldValue - z.z;
						break;
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_2)
					case 2:
					{
						float rr = z.x*z.x + z.y*z.y + z.z*z.z;
						float minR2 = mut->foldLimit * mut->foldLimit;
						float fixR2 = mut->foldValue * mut->foldValue;
						if (rr < minR2) { z *= fixR2/minR2; aux.DE *= fixR2/minR2; }
						else if (rr < fixR2) { z *= fixR2/rr; aux.DE *= fixR2/rr; }
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_3)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_4)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_5)
					case 5:
					{
						z.x = fabs(z.x + mut->foldLimit) - fabs(z.x - mut->foldLimit) - z.x;
						z.y = fabs(z.y + mut->foldLimit) - fabs(z.y - mut->foldLimit) - z.y;
						z.z = fabs(z.z + mut->foldLimit) - fabs(z.z - mut->foldLimit) - z.z;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_6)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_7)
					case 7:
					{
						if (z.x + z.y < 0) { float tx = -z.y; z.y = -z.x; z.x = tx; }
						if (z.x + z.z < 0) { float tx = -z.z; z.z = -z.x; z.x = tx; }
						if (z.y + z.z < 0) { float ty = -z.z; z.z = -z.y; z.y = ty; }
						if (z.x - z.y < 0) { float tx = z.y; z.y = z.x; z.x = tx; }
						if (z.x - z.z < 0) { float tx = z.z; z.z = z.x; z.x = tx; }
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_8)
					case 8:
					{
						float k = (mut->foldLimit > 0.0f) ? mut->foldLimit : 1.0f;
						z.x -= tanh(k * z.x);
						z.y -= tanh(k * z.y);
						z.z -= tanh(k * z.z);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_9)
					case 9:
					{
						z.x = z.x * z.x * z.x - 3.0f * z.x;
						z.y = z.y * z.y * z.y - 3.0f * z.y;
						z.z = z.z * z.z * z.z - 3.0f * z.z;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_10)
					case 10:
					{
						float rad = (mut->foldValue > 0.0f) ? mut->foldValue : 1.0f;
						float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
						if (r > 1e-21f) { float s = rad / r; z.x *= s; z.y *= s; z.z *= s; }
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_11)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_12)
					case 12:
					{
						float a = mut->foldValue;
						float b = (mut->foldLimit > 0.0f) ? mut->foldLimit : 1.0f;
						z.x += a * native_sin(b * z.x);
						z.y += a * native_sin(b * z.y);
						z.z += a * native_sin(b * z.z);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_13)
					case 13:
					{
						z.x *= native_exp(-z.x * z.x);
						z.y *= native_exp(-z.y * z.y);
						z.z *= native_exp(-z.z * z.z);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_14)
					case 14:
					{
						float rx = fabs(z.x); float ry = fabs(z.y); float rz = fabs(z.z);
						z.x *= native_log(1.0f + rx);
						z.y *= native_log(1.0f + ry);
						z.z *= native_log(1.0f + rz);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_15)
					case 15:
					{
						float p = (mut->foldValue > 0.0f) ? mut->foldValue : 2.0f;
						float ax = fabs(z.x); float ay = fabs(z.y); float az = fabs(z.z);
						z.x = sign(z.x) * native_powr(max(ax, 1e-21f), p);
						z.y = sign(z.y) * native_powr(max(ay, 1e-21f), p);
						z.z = sign(z.z) * native_powr(max(az, 1e-21f), p);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_16)
					case 16: // smooth abs
					{
						float k = (mut->foldLimit > 0.0f) ? mut->foldLimit : 5.0f;
						z.x = z.x * tanh(k * z.x);
						z.y = z.y * tanh(k * z.y);
						z.z = z.z * tanh(k * z.z);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_17)
					case 17: // modulo wrap
					{
						float period = (mut->foldValue > 0.0f) ? mut->foldValue : 2.0f;
						z.x = fmod(z.x + period * 0.5f, period) - period * 0.5f;
						z.y = fmod(z.y + period * 0.5f, period) - period * 0.5f;
						z.z = fmod(z.z + period * 0.5f, period) - period * 0.5f;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_18)
					case 18: // nested abs
					{
						float c = (mut->foldLimit > 0.0f) ? mut->foldLimit : 1.0f;
						z.x = fabs(fabs(z.x) - c);
						z.y = fabs(fabs(z.y) - c);
						z.z = fabs(fabs(z.z) - c);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_19)
					case 19: // sawtooth
					{
						z.x = 2.0f * (z.x * 0.5f - floor(z.x * 0.5f + 0.5f));
						z.y = 2.0f * (z.y * 0.5f - floor(z.y * 0.5f + 0.5f));
						z.z = 2.0f * (z.z * 0.5f - floor(z.z * 0.5f + 0.5f));
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_20)
					case 20: // Bipolar
					{
						float c1 = mut->foldLimit;
						float c2 = -mut->foldLimit;
						z.x = fabs(z.x - c1) - fabs(z.x - c2);
						z.y = fabs(z.y - c1) - fabs(z.y - c2);
						z.z = fabs(z.z - c1) - fabs(z.z - c2);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_21)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_22)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_23)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_24)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_25)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_26)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_FOLDTYPE_27)
					case 27: // TriangleWave
					{
						z.x = 2.0f * fabs(z.x * 0.5f - floor(z.x * 0.5f + 0.5f));
						z.y = 2.0f * fabs(z.y * 0.5f - floor(z.y * 0.5f + 0.5f));
						z.z = 2.0f * fabs(z.z * 0.5f - floor(z.z * 0.5f + 0.5f));
						break;
					}
#endif
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
			if (mut->clipEnabled && i >= mut->clipIterStart && i < mut->clipIterStop && mut->clipType != 0)
			{
				float4 z_orig_clip = z; float de_orig_clip = aux.DE;
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
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_1)
					case 1: // Ellipsoid Clip
					{
						clipDist = native_sqrt((cz.x/sx)*(cz.x/sx) + (cz.y/sy)*(cz.y/sy) + (cz.z/sz)*(cz.z/sz)) - 1.0f;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_2)
					case 2: // Torus Clip
					{
						float rxy = native_sqrt(cz.x * cz.x + cz.y * cz.y) - cR;
						clipDist = native_sqrt(rxy * rxy + cz.z * cz.z) - cr;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_3)
					case 3: // Cylinder (infinite) Clip
					{
						clipDist = native_sqrt(cz.x * cz.x + cz.y * cz.y) - cr;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_4)
					case 4: // Cone Clip
					{
						float tanAlpha = tan(mut->clipAngle * M_PI_F / 180.0f);
						clipDist = native_sqrt(cz.x * cz.x + cz.y * cz.y) - tanAlpha * fabs(cz.z);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_5)
					case 5: // Hyperboloid Clip
					{
						clipDist = (cz.x/sx)*(cz.x/sx) + (cz.y/sy)*(cz.y/sy) - (cz.z/sz)*(cz.z/sz) - 1.0f;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_6)
					case 6: // Paraboloid Clip
					{
						clipDist = cz.x * cz.x + cz.y * cz.y - ca * cz.z;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_7)
					case 7: // Saddle Clip
					{
						clipDist = (cz.x/sx)*(cz.x/sx) - (cz.y/sy)*(cz.y/sy) - cz.z;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_8)
					case 8: // Spiral Clip
					{
						float r2d = native_sqrt(cz.x * cz.x + cz.y * cz.y);
						float theta = atan2(cz.y, cz.x);
						clipDist = r2d - ca * native_exp(cb * theta);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_9)
					case 9: // Wave Clip
					{
						float freq = mut->clipFrequency;
						float amp = mut->clipAmplitude;
						clipDist = cz.z - amp * native_sin(freq * cz.x) * native_sin(freq * cz.y);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_10)
					case 10: // Noise Clip
					{
						float n = native_sin(cz.x * 12.9898f + cz.y * 78.233f) * 43758.5453f;
						n = (n - floor(n)) * 2.0f - 1.0f;
						float n2 = native_sin(cz.y * 19.8672f + cz.z * 53.471f) * 28947.3125f;
						n2 = (n2 - floor(n2)) * 2.0f - 1.0f;
						clipDist = cz.z - mut->clipAmplitude * (n + n2) * 0.5f;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_11)
					case 11: // Union (OR) Clip
					{
						float d1 = native_sqrt((cz.x/sx)*(cz.x/sx) + (cz.y/sy)*(cz.y/sy) + (cz.z/sz)*(cz.z/sz)) - 1.0f;
						float d2 = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						clipDist = min(d1, d2);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_12)
					case 12: // Difference (A - B) Clip
					{
						float dA = native_sqrt((cz.x/sx)*(cz.x/sx) + (cz.y/sy)*(cz.y/sy) + (cz.z/sz)*(cz.z/sz)) - 1.0f;
						float dB = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						clipDist = max(dA, -dB);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_13)
					case 13: // XOR Clip
					{
						float dA2 = native_sqrt((cz.x/sx)*(cz.x/sx) + (cz.y/sy)*(cz.y/sy) + (cz.z/sz)*(cz.z/sz)) - 1.0f;
						float dB2 = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						clipDist = max(min(dA2, dB2), -max(dA2, dB2));
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_14)
					case 14: // Smooth Union Clip
					{
						float d1s = native_sqrt((cz.x/sx)*(cz.x/sx) + (cz.y/sy)*(cz.y/sy) + (cz.z/sz)*(cz.z/sz)) - 1.0f;
						float d2s = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						float k = mut->clipSmoothK;
						float h = clamp(0.5f + 0.5f * (d2s - d1s) / k, 0.0f, 1.0f);
						clipDist = mix(d2s, d1s, h) - k * h * (1.0f - h);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_15)
					case 15: // Smooth Difference Clip
					{
						float dAs = native_sqrt((cz.x/sx)*(cz.x/sx) + (cz.y/sy)*(cz.y/sy) + (cz.z/sz)*(cz.z/sz)) - 1.0f;
						float dBs = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						float k2 = mut->clipSmoothK;
						float h2 = clamp(0.5f - 0.5f * (dAs + dBs) / k2, 0.0f, 1.0f);
						clipDist = mix(dAs, -dBs, h2) + k2 * h2 * (1.0f - h2);
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_16)
					case 16: // Chain Clip (3 stages)
					{
						float dc1 = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						float dc2 = max(fabs(cz.x) - sx, max(fabs(cz.y) - sy, fabs(cz.z) - sz));
						float dc3 = native_sqrt(cz.x*cz.x + cz.y*cz.y) - cr * 0.5f;
						clipDist = max(dc1, max(dc2, dc3));
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_17)
					case 17: // Array (Grid) Clip
					{
						float3 rp = cz;
						if (sx > 0.001f) rp.x = fmod(cz.x + sx * 0.5f, sx) - sx * 0.5f;
						if (sy > 0.001f) rp.y = fmod(cz.y + sy * 0.5f, sy) - sy * 0.5f;
						if (sz > 0.001f) rp.z = fmod(cz.z + sz * 0.5f, sz) - sz * 0.5f;
						clipDist = native_sqrt(rp.x*rp.x + rp.y*rp.y + rp.z*rp.z) - cr;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_18)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_19)
					case 19: // Hierarchical Clip
					{
						float coarse = max(fabs(cz.x) - sx * 2.0f, max(fabs(cz.y) - sy * 2.0f, fabs(cz.z) - sz * 2.0f));
						float fine = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						clipDist = (coarse < 0.0f) ? fine : coarse;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_20)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_21)
					case 21: // Clip with Pre-Rotation (handled by clipPreRotMatrix)
					{
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_22)
					case 22: // Clip with Pre-Scale
					{
						float3 scaled = cz;
						scaled.x *= sx; scaled.y *= sy; scaled.z *= sz;
						clipDist = native_sqrt(scaled.x*scaled.x + scaled.y*scaled.y + scaled.z*scaled.z) - cr;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_23)
					case 23: // Clip with Pre-Shear
					{
						float3 sheared = cz;
						sheared.x += mut->clipAmplitude * cz.y;
						clipDist = native_sqrt(sheared.x*sheared.x + sheared.y*sheared.y + sheared.z*sheared.z) - cr;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_24)
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
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_25)
					case 25: // Clip with Pre-Abs
					{
						float3 absed = cz;
						absed.x = fabs(absed.x); absed.y = fabs(absed.y); absed.z = fabs(absed.z);
						clipDist = native_sqrt(absed.x*absed.x + absed.y*absed.y + absed.z*absed.z) - cr;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_26)
					case 26: // Clip with Post-Offset
					{
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						float pulse = 1.0f + 0.1f * native_sin((float)i * mut->clipFrequency);
						clipDist *= pulse;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_27)
					case 27: // Clip with Post-Scale
					{
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						float scaleFactor = ca * (1.0f + 0.1f * (float)i / 250.0f);
						clipDist *= scaleFactor;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_28)
					case 28: // Clip with Color-Depth
					{
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						if (clipDist < 0.0f) aux.color += fabs(clipDist) * mut->clipAmplitude;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_29)
					case 29: // Clip with Orbit-Trap
					{
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						float trap = length(cz);
						if (trap < aux.color) aux.color = trap;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_30)
					case 30: // Clip with DE-Visualization
					{
						clipDist = native_sqrt(cz.x*cz.x + cz.y*cz.y + cz.z*cz.z) - cr;
						aux.color = native_log(1.0f + fabs(aux.dist)) * mut->clipAmplitude;
						break;
					}
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_31)
					case 31: { float r2d=native_sqrt(cz.x*cz.x+cz.y*cz.y), theta=atan2(cz.y,cz.x); int n=mut->clipNPoints;{ float starR=cr*(1.0f+mut->clipAmplitude*native_cos((float)n*theta)); clipDist=r2d-starR; } break; } // Star polygon clip
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_32)
					case 32: { float x2h=cz.x*cz.x+cz.y*cz.y; clipDist=(x2h-1.0f)*(x2h-1.0f)*(x2h-1.0f)-cz.x*cz.x*cz.y*cz.y*cz.y; break; } // Heart surface clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_33)
					case 33: { float r2d2=native_sqrt(cz.x*cz.x+cz.y*cz.y), theta2=atan2(cz.y,cz.x), m=(float)mut->clipNPoints, n1=ca,n2=cb,n3=cc, t=m*theta2/4.0f, r_sf=pow(pow(fabs(native_cos(t)/sx),n2)+pow(fabs(native_sin(t)/sy),n3),-1.0f/n1); clipDist=r2d2-r_sf*cr; break; } // Superformula clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_34)
					case 34: { float r2d3=native_sqrt(cz.x*cz.x+cz.y*cz.y), theta3=atan2(cz.y,cz.x); int ng=mut->clipNPoints;{ float gearR=cr*(1.0f+0.1f*tanh(native_sin((float)ng*theta3))); clipDist=r2d3-gearR; } break; } // Gear clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_35)
					case 35: { float r2d4=native_sqrt(cz.x*cz.x+cz.y*cz.y), theta4=atan2(cz.y,cz.x); int ns=mut->clipNPoints;{ float spiralR=ca*native_exp(-cb*theta4)*(1.0f+cc*native_cos((float)ns*theta4)); clipDist=r2d4-spiralR; } break; } // Spiral polygon clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_36)
					case 36: { float3 seeds0=(float3)(ca,0.0f,0.0f), seeds1=(float3)(-ca,cb,0.0f), seeds2=(float3)(0.0f,-ca,cc), seeds3=(float3)(cb,cc,-ca); { float minVD=1e20f, vd0=length(cz-seeds0); if(vd0<minVD)minVD=vd0;float vd1=length(cz-seeds1); if(vd1<minVD)minVD=vd1; float vd2=length(cz-seeds2); if(vd2<minVD)minVD=vd2; float vd3=length(cz-seeds3); if(vd3<minVD)minVD=vd3; clipDist=minVD-cr; } break; } // Voronoi clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_37)
					case 37: { float3 e0=(float3)(ca,0.0f,0.0f),e1=(float3)(-ca*0.5f,ca*0.866f,0.0f),e2=(float3)(-ca*0.5f,-ca*0.866f,0.0f); { float minED=1e20f; for(int k=0;k<3;k++){float3 ea,eb; if(k==0){ea=e0;eb=e1;} else if(k==1){ea=e1;eb=e2;} else{ea=e2;eb=e0;} float3 ev=eb-ea; float3 pv=cz-ea;float t=fmax(0.0f,fmin(1.0f,dot(pv,ev)/dot(ev,ev))); float ed=length(pv-ev*t); if(ed<minED)minED=ed;} clipDist=minED-cr; } break; } // Triangle edge clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_38)
					case 38: { float3 lz=cz;float lscale=1.0f; for(int k=0;k<3;k++){lz.x=fabs(lz.x);lz.y=fabs(lz.y);lz.z=fabs(lz.z); if(lz.x<lz.y){float t=lz.x;lz.x=lz.y;lz.y=t;} if(lz.x<lz.z){float t=lz.x;lz.x=lz.z;lz.z=t;} if(lz.y<lz.z){float t=lz.y;lz.y=lz.z;lz.z=t;} lz=lz*ca-(float3)(cb,cb,cb)*(ca-1.0f); lscale*=ca;} clipDist=(length(lz)-cr)/lscale; break; } // Menger sponge clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_39)
					case 39: { float jx=cz.x,jy=cz.y; for(int k=0;k<8;k++){float tx=jx*jx-jy*jy+ca; jy=2.0f*jx*jy+cb; jx=tx; if(jx*jx+jy*jy>4.0f)break;} float jDist=(jx*jx+jy*jy>4.0f)?-cr:cr; clipDist=fmax(jDist,fabs(cz.z)-sz); break; } // Julia set clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_40)
					case 40: { float mx=0.0f,my=0.0f; for(int k=0;k<8;k++){float tx2=mx*mx-my*my+cz.x; my=2.0f*mx*my+cz.y; mx=tx2; if(mx*mx+my*my>4.0f)break;} float mDist=(mx*mx+my*my>4.0f)?-cr:cr; clipDist=fmax(mDist,fabs(cz.z)-sz); break; } // Mandelbrot clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_41)
					case 41: { clipDist=fmax(fmax(fabs(cz.x),fabs(cz.y)),fmax(fabs(cz.z),fabs(z.w)))-cr; break; } // 4D hypercube clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_42)
					case 42: { clipDist=native_sqrt(cz.x*cz.x+cz.y*cz.y+cz.z*cz.z+z.w*z.w)-cr; break; } // 4D hypersphere clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_43)
					case 43: { float time=(float)i*mut->clipFrequency, tR=cr*(1.0f+mut->clipAmplitude*native_sin(time)); clipDist=length(cz)-tR; break; } // Temporal pulsing clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_44)
					case 44: { float orbitR=cr*(1.0f+mut->clipAmplitude*native_sin(aux.color*mut->clipFrequency)); clipDist=length(cz)-orbitR; break; } // Orbit-reactive clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_45)
					case 45: { float deR=cr*(1.0f+mut->clipAmplitude*native_log(1.0f+fabs(aux.DE))); clipDist=length(cz)-deR; break; } // DE-reactive clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_46)
					case 46: { float colR=cr*(1.0f+mut->clipAmplitude*native_sin(aux.color*mut->clipFrequency)); clipDist=length(cz)-colR; break; } // Color-reactive clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_47)
					case 47: { float iterR=cr*(1.0f+mut->clipAmplitude*(float)i/250.0f); clipDist=length(cz)-iterR; break; } // Progressive clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_48)
					case 48: { float rh=fabs(native_sin((float)i*12.9898f+cz.x*78.233f)*43758.5453f); rh=rh-floor(rh); { float randR=cr*(1.0f+mut->clipAmplitude*(rh-0.5f)); clipDist=length(cz)-randR; } break; } // Random jitter clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_49)
					case 49: { float nx=tanh(ca*cz.x+cb*cz.y+cc*cz.z), ny=tanh(cb*cz.x-ca*cz.y+cc*cz.z), nz=tanh(cc*cz.x+ca*cz.y-cb*cz.z); clipDist=native_sqrt(nx*nx+ny*ny+nz*nz)-cr; break; } // Neural tanh clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_50)
					case 50: { float3 rz=cz;{ float rscale=1.0f; clipDist=1e10f; for(int k=0;k<5;k++){rz.x=fabs(rz.x)*2.0f-ca; rz.y=fabs(rz.y)*2.0f-ca; rz.z=fabs(rz.z)*2.0f-ca; rscale*=2.0f; float rd=length(rz)-cr; rd/=rscale; if(rd<clipDist)clipDist=rd;} } break; } // Recursive fractal clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_51)
					case 51: { clipDist=native_sin(cz.x*ca)*native_cos(cz.y*ca)+native_sin(cz.y*ca)*native_cos(cz.z*ca)+native_sin(cz.z*ca)*native_cos(cz.x*ca)-cr; break; } // Gyroid surface
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_52)
					case 52: { clipDist=native_cos(cz.x*ca)+native_cos(cz.y*ca)+native_cos(cz.z*ca)-cr; break; } // Schwarz P surface
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_53)
					case 53: { clipDist=native_sin(cz.x*ca)*native_sin(cz.y*ca)*native_sin(cz.z*ca)+native_sin(cz.x*ca)*native_cos(cz.y*ca)*native_cos(cz.z*ca)+native_cos(cz.x*ca)*native_sin(cz.y*ca)*native_cos(cz.z*ca)+native_cos(cz.x*ca)*native_cos(cz.y*ca)*native_sin(cz.z*ca)-cr; break; } // Diamond surface
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_54)
					case 54: { clipDist=0.5f*(native_sin(2.0f*cz.x*ca)*native_cos(cz.y*ca)*native_sin(cz.z*ca)+native_sin(2.0f*cz.y*ca)*native_cos(cz.z*ca)*native_sin(cz.x*ca)+native_sin(2.0f*cz.z*ca)*native_cos(cz.x*ca)*native_sin(cz.y*ca))-0.5f*(native_cos(2.0f*cz.x*ca)*native_cos(2.0f*cz.y*ca)+native_cos(2.0f*cz.y*ca)*native_cos(2.0f*cz.z*ca)+native_cos(2.0f*cz.z*ca)*native_cos(2.0f*cz.x*ca))-cr; break; } // Lidinoid surface
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_55)
					case 55: { clipDist=3.0f*(native_cos(cz.x*ca)+native_cos(cz.y*ca)+native_cos(cz.z*ca))+4.0f*native_cos(cz.x*ca)*native_cos(cz.y*ca)*native_cos(cz.z*ca)-cr; break; } // Neovius surface
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_56)
					case 56: { float t56=atan2(cz.y,cz.x), kx=native_cos(2.0f*t56)*(cR+cr*native_cos(3.0f*t56)), ky=native_sin(2.0f*t56)*(cR+cr*native_cos(3.0f*t56)), kz=cr*native_sin(3.0f*t56); clipDist=native_sqrt((cz.x-kx)*(cz.x-kx)+(cz.y-ky)*(cz.y-ky)+(cz.z-kz)*(cz.z-kz))-ca; break; } // Torus knot
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_57)
					case 57: { clipDist=cz.x*cz.x*cz.z+cz.y*cz.y*cz.z-ca*cz.x*cz.y-cr; break; } // Cross-cap surface
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_58)
					case 58: { float phi58=0.5f*(1.0f+native_sqrt(5.0f)), p2=phi58*phi58, r2=cz.x*cz.x+cz.y*cz.y+cz.z*cz.z; clipDist=4.0f*(p2*cz.x*cz.x-cz.y*cz.y)*(p2*cz.y*cz.y-cz.z*cz.z)*(p2*cz.z*cz.z-cz.x*cz.x)-(1.0f+2.0f*phi58)*(r2-ca*ca)*(r2-ca*ca); break; } // Barth sextic
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_59)
					case 59: { clipDist=cz.x*cz.x*cz.y*cz.y+cz.y*cz.y*cz.z*cz.z+cz.z*cz.z*cz.x*cz.x-ca*cz.x*cz.y*cz.z; break; } // Steiner surface
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_60)
					case 60: { float r60=length(cz); if(r60<1e-15f)r60=1e-15f;{ float x60=cz.x/r60,y60=cz.y/r60,z60=cz.z/r60; clipDist=64.0f*x60*x60*x60*z60-48.0f*x60*z60*(3.0f*x60*x60+z60*z60)+12.0f*z60*(x60*x60-z60*z60)+x60*x60+y60*y60+z60*z60-cr*cr; } break; } // Boy surface approx
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_61)
					case 61: { float r61=length(cz); clipDist=r61*native_exp(-ca*r61)-cr; break; } // Exponential decay shell
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_62)
					case 62: { float r62=native_sqrt(cz.x*cz.x+cz.y*cz.y), t62=atan2(cz.y,cz.x), spiralR=ca*native_exp(cb*t62); clipDist=fabs(r62-spiralR)+fabs(cz.z)-cr; break; } // Logarithmic spiral shell
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_63)
					case 63: { float t63=atan2(cz.y,cz.x), r63=native_sqrt(cz.x*cz.x+cz.y*cz.y), h1=r63-cR-cr*native_cos(ca*cz.z), h2=r63-cR+cr*native_cos(ca*cz.z+M_PI_F); clipDist=fmin(native_sqrt(h1*h1+pow(cr*native_sin(ca*cz.z),2.0f)),native_sqrt(h2*h2+pow(cr*native_sin(ca*cz.z+M_PI_F),2.0f)))-cb; break; } // Double helix
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_64)
					case 64: { float dx64=fabs(cz.x)-sx, dy64=fabs(cz.y)-sy, dz64=fabs(cz.z)-sz, chamfer=ca; clipDist=fmax(fmax(dx64,fmax(dy64,dz64)),(dx64+dy64+dz64)*chamfer); break; } // Chamfered cube
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_65)
					case 65: { float dx65=fmax(fabs(cz.x)-sx,0.0f), dy65=fmax(fabs(cz.y)-sy,0.0f), dz65=fmax(fabs(cz.z)-sz,0.0f); clipDist=native_sqrt(dx65*dx65+dy65*dy65+dz65*dz65)-cr; break; } // Rounded box
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_66)
					case 66: { clipDist=fabs(cz.x)+fabs(cz.y)+fabs(cz.z)-cr; break; } // Octahedron
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_67)
					case 67: { float phi67=0.5f*(1.0f+native_sqrt(5.0f)); clipDist=fmax(fmax(fabs(cz.x)+phi67*fabs(cz.y),fabs(cz.y)+phi67*fabs(cz.z)),fabs(cz.z)+phi67*fabs(cz.x))-cr*(1.0f+phi67); break; } // Dodecahedron approx
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_68)
					case 68: { float phi68=0.5f*(1.0f+native_sqrt(5.0f)); clipDist=fmax(fabs(cz.x)+phi68*fabs(cz.z),fmax(fabs(cz.y)+phi68*fabs(cz.x),fabs(cz.z)+phi68*fabs(cz.y)))-cr*phi68*phi68; break; } // Icosahedron approx
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_69)
					case 69: { float d69a=fmax(fabs(cz.x),fmax(fabs(cz.y),fabs(cz.z)))-sx, d69b=(fabs(cz.x)+fabs(cz.y)+fabs(cz.z))*0.577f-cr; clipDist=fmax(d69a,d69b); break; } // Truncated octahedron
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_70)
					case 70: { float q70x=fabs(cz.x), q70y=fabs(cz.y); clipDist=fmax(q70x*0.866f+q70y*0.5f,q70y)-cr; clipDist=fmax(clipDist,fabs(cz.z)-sz); break; } // Hex prism
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_71)
					case 71: { clipDist=fmax(fabs(cz.z)-sz,fmax(fabs(cz.x)*0.866f+cz.y*0.5f,-cz.y)-cr); break; } // Triangular prism
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_72)
					case 72: { float rxy72a=native_sqrt(cz.x*cz.x+cz.y*cz.y), d72a=native_sqrt((rxy72a-cR)*(rxy72a-cR)+cz.z*cz.z)-cr, ryz72=native_sqrt(cz.y*cz.y+cz.z*cz.z), d72b=native_sqrt((ryz72-cR)*(ryz72-cR)+cz.x*cz.x)-cr; clipDist=fmin(d72a,d72b); break; } // Link
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_73)
					case 73: { float r73=native_sqrt(cz.x*cz.x+cz.y*cz.y)-cr, h73=fabs(cz.z)-sz; clipDist=fmin(fmax(r73,h73),0.0f)+native_sqrt(fmax(r73,0.0f)*fmax(r73,0.0f)+fmax(h73,0.0f)*fmax(h73,0.0f)); break; } // Capped cylinder
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_74)
					case 74: { float capH=fmax(0.0f,fmin(sz,cz.z)); clipDist=native_sqrt(cz.x*cz.x+cz.y*cz.y+(cz.z-capH)*(cz.z-capH))-cr; break; } // Capsule
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_75)
					case 75: { float t75=atan2(cz.y,cz.x), r75=native_sqrt(cz.x*cz.x+cz.y*cz.y), knotR=cR+cr*native_cos(3.0f*t75); clipDist=native_sqrt((r75-knotR)*(r75-knotR)+cz.z*cz.z)-ca; break; } // Trefoil knot
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_76)
					case 76: { float t76=atan2(cz.y,cz.x), r76=native_sqrt(cz.x*cz.x+cz.y*cz.y)-cR, localZ=cz.z*native_cos(t76*0.5f)-r76*native_sin(t76*0.5f); clipDist=fabs(localZ)-ca; break; } // Mobius strip approx
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_77)
					case 77: { float sc77x=native_sin(cz.x*ca)*native_sin(cz.x*ca), sc77y=native_sin(cz.y*ca)*native_sin(cz.y*ca), sc77z=native_sin(cz.z*ca)*native_sin(cz.z*ca); clipDist=sc77x+sc77y+sc77z-cr; break; } // Sine cage
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_78)
					case 78: { clipDist=cz.x*cz.x*cz.x*cz.x+cz.y*cz.y*cz.y*cz.y+cz.z*cz.z*cz.z*cz.z-ca*(cz.x*cz.x+cz.y*cz.y+cz.z*cz.z); break; } // Pillow shape
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_79)
					case 79: { float n79=native_sin(ca*cz.x)*native_sin(ca*cz.y)*native_sin(ca*cz.z); clipDist=length(cz)-cr-cb*n79; break; } // Displacement sphere
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_80)
					case 80: { float r80=native_sqrt(cz.x*cz.x+cz.y*cz.y)-cR, ang80=ca*atan2(cz.y,cz.x)/(2.0f*M_PI_F); clipDist=r80*r80+(cz.z-ang80)*(cz.z-ang80)-cr*cr; break; } // Corkscrew
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_81)
					case 81: { float u81=atan2(cz.y,cz.x), v81=atan2(cz.z,native_sqrt(cz.x*cz.x+cz.y*cz.y)-cR), kb=ca*(1.0f-0.5f*native_cos(u81))*native_sin(v81)-cb*native_cos(v81); clipDist=fabs(kb)-cr; break; } // Klein bottle section
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_82)
					case 82: { float r82=native_sqrt(cz.x*cz.x+cz.y*cz.y), wave82=cr+ca*native_sin(cb*cz.z); clipDist=r82-wave82; break; } // Wavy cylinder
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_83)
					case 83: { float twist83=ca*cz.z, rx83=cz.x*native_cos(twist83)-cz.y*native_sin(twist83), ry83=cz.x*native_sin(twist83)+cz.y*native_cos(twist83); clipDist=fmax(fabs(rx83)-sx,fmax(fabs(ry83)-sy,fabs(cz.z)-sz)); break; } // Twisted box
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_84)
					case 84: { float bend84=ca*cz.x, bz84=cz.z+bend84*bend84, rxy84=native_sqrt(cz.x*cz.x+cz.y*cz.y)-cR; clipDist=native_sqrt(rxy84*rxy84+bz84*bz84)-cr; break; } // Bent torus
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_85)
					case 85: { clipDist=cz.z-ca*native_sin(cb*cz.x)-cc*native_cos(cb*cz.y)-cr; break; } // Corrugated plane
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_86)
					case 86: { float r86=length(cz); if(r86<1e-15f)r86=1e-15f;{ float theta86=acos(cz.z/r86), phi86=atan2(cz.y,cz.x), m86=(float)mut->clipNPoints, st86=pow(pow(fabs(native_cos(m86*theta86/4.0f)),cb)+pow(fabs(native_sin(m86*theta86/4.0f)),cc),-1.0f/ca), sp86=pow(pow(fabs(native_cos(m86*phi86/4.0f)),cb)+pow(fabs(native_sin(m86*phi86/4.0f)),cc),-1.0f/ca); clipDist=r86-cr*st86*sp86; } break; } // Supershape 3D
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_87)
					case 87: { float r87=length(cz), cosTheta87=cz.z/(r87+1e-15f); clipDist=r87-cr*(1.0f+ca*cosTheta87); break; } // Egg shape
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_88)
					case 88: { float x2_88=cz.x*cz.x,y2_88=cz.y*cz.y,z2_88=cz.z*cz.z; clipDist=2.0f*y2_88*(y2_88-ca*ca)*(y2_88-ca*ca)-x2_88*x2_88+2.0f*ca*ca*(x2_88-z2_88*3.0f)*(x2_88-z2_88); break; } // Genus-2 surface
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_89)
					case 89: { float fx89=fabs(fmod(cz.x+ca,2.0f*ca))-ca, fy89=fabs(fmod(cz.y+ca,2.0f*ca))-ca, fz89=fabs(fmod(cz.z+ca,2.0f*ca))-ca; clipDist=native_sqrt(fx89*fx89+fy89*fy89+fz89*fz89)-cr; break; } // Folded sphere
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_90)
					case 90: { clipDist=fmax(fmax(fabs(cz.x+cz.y),fabs(cz.x-cz.y)),fmax(fabs(cz.y+cz.z),fmax(fabs(cz.y-cz.z),fmax(fabs(cz.x+cz.z),fabs(cz.x-cz.z)))))-cr; break; } // Rhombic dodecahedron
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_91)
					case 91: { clipDist=fmax(fabs(cz.x+cz.y+cz.z),fmax(fabs(cz.x-cz.y-cz.z),fmax(fabs(-cz.x+cz.y-cz.z),fabs(-cz.x-cz.y+cz.z))))-cr; break; } // Tetrahedral symmetry
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_92)
					case 92: { clipDist=native_sin(ca*cz.x)+native_sin(ca*cz.y)+native_sin(ca*cz.z)-cr; break; } // Egg crate
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_93)
					case 93: { float denom93=native_cos(ca*cz.y)*native_cos(ca*cz.z)+1e-10f; clipDist=native_sin(ca*cz.x)-native_sin(ca*cz.y)*native_sin(ca*cz.z)/denom93; break; } // Scherk surface
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_94)
					case 94: { float u94=cz.x,v94=cz.y, ex94=u94-u94*u94*u94/3.0f+u94*v94*v94, ey94=v94-v94*v94*v94/3.0f+v94*u94*u94, ez94=u94*u94-v94*v94; clipDist=native_sqrt((cz.x-ex94)*(cz.x-ex94)+(cz.y-ey94)*(cz.y-ey94)+(cz.z-ez94)*(cz.z-ez94))-cr; break; } // Enneper surface
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_95)
					case 95: { clipDist=cz.x*cz.x/fmax(sx*sx,1e-10f)-cz.y*cz.y/fmax(sy*sy,1e-10f)-cz.z; break; } // Saddle clip
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_96)
					case 96: { clipDist=cz.x*(cz.x*cz.x-3.0f*cz.y*cz.y)-ca*cz.z; break; } // Monkey saddle
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_97)
					case 97: { clipDist=fabs(cz.x)+fabs(cz.y)+fabs(cz.z)+fabs(z.w)-cr; break; } // Cross-polytope
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_98)
					case 98: { clipDist=cz.x*cz.x/fmax(sx*sx,1e-10f)+cz.y*cz.y/fmax(sy*sy,1e-10f)-cz.z; break; } // Elliptic paraboloid
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_99)
					case 99: { float d99s=length(cz)-cr, d99b=fmax(fabs(cz.x)-sx,fmax(fabs(cz.y)-sy,fabs(cz.z)-sz)), k99=mut->clipSmoothK, h99=fmax(0.0f,fmin(1.0f,0.5f-0.5f*(d99s-d99b)/fmax(k99,1e-10f))); clipDist=d99s*(1.0f-h99)+d99b*h99+k99*h99*(1.0f-h99); break; } // Smooth intersection
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLIPTYPE_100)
					case 100: { float3 ifs=cz;float ifsScale=1.0f; for(int k=0;k<6;k++){if(ifs.x+ifs.y<0.0f){float t=-ifs.y;ifs.y=-ifs.x;ifs.x=t;} if(ifs.x+ifs.z<0.0f){float t=-ifs.z;ifs.z=-ifs.x;ifs.x=t;} if(ifs.y+ifs.z<0.0f){float t=-ifs.z;ifs.z=-ifs.y;ifs.y=t;} ifs=ifs*ca-(float3)(cb,cb,cb)*(ca-1.0f); ifsScale*=ca;} clipDist=(length(ifs)-cr)/ifsScale; break; } // Sierpinski IFS
#endif

					default: break;
#endif
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

				// Apply clip to z (clip points inside the shape)
				if (clipDist < 0.0f)
				{
					cz.x = 0.0f;
					cz.y = 0.0f;
					cz.z = 0.0f;
				}
				cz.x += mut->clipCenterX; cz.y += mut->clipCenterY; cz.z += mut->clipCenterZ;
				z.xyz = cz;
				float clip_blend = clamp(mut->clipWeight * mut->masterWeight, 0.0f, 1.0f);
				z = z_orig_clip + (z - z_orig_clip) * clip_blend;
				aux.DE = de_orig_clip + (aux.DE - de_orig_clip) * clip_blend;
			}

			// v7.7 — Jos Leys DE system (per-section iteration range)
			if (i >= mut->josIterStart && i < mut->josIterStop && mut->josLeysDeType != 0)
			{
				float jf = mut->josFactor * mut->josLeysWeight * mut->masterWeight;
				float ja = mut->josParamA, jb = mut->josParamB, jc = mut->josParamC, jd = mut->josParamD;
				float jfreq = mut->josFreq, jamp = mut->josAmp, jsc = mut->josScale, jph = mut->josPhase;
				float zx = z.x, zy = z.y, zz2 = z.z;
				float rr = zx*zx + zy*zy + zz2*zz2; if (rr < 1e-21f) rr = 1e-21f;
				float r = native_sqrt(rr);
				switch (mut->josLeysDeType)
				{
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_1)
					case 1: { float k1=ja,k2=jb,k3=jc,k4=jd, curv=(k1+k2+k3+k4)/fmax(1.0f,r); aux.DE*=(1.0f+jf*curv); break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_2)
					case 2: { float phi=atan2(zy,zx), sp=ja*native_exp(2.0f*M_PI_F*(jb*phi+jc*native_log(fmax(1e-10f,r)))); aux.DE*=(1.0f+jf*sp); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_3)
					case 3: { float prod=1.0f; for(int k=0;k<4;k++){float dk=r+ja*(float)(k+1); prod*=fmax(0.01f,dk);} aux.DE*=(1.0f+jf*jsc/fmax(1e-10f,prod)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_4)
					case 4: { float af=ja*native_log(fmax(1e-10f,r))+jb*atan2(zy,zx); aux.DE*=(1.0f+jf*tanh(af)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_5)
					case 5: { float hyp=4.0f*M_PI_F*(ja-1.0f)/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*tanh(hyp)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_6)
					case 6: { float bel=ja*zy/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*tanh(bel)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_7)
					case 7: { float tr=ja*jb/fmax(1e-10f,r); aux.DE*=(1.0f+jf*tanh(tr)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_8)
					case 8: { float rl=ja/(fmax(1e-10f,r*r)+jb*jb); aux.DE*=(1.0f+jf*rl); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_9)
					case 9: { float bs=ja*jb*jc/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*tanh(bs)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_10)
					case 10: { float ew=ja*native_sin(jfreq*zx)*native_cos(jfreq*zy)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*ew); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_11)
					case 11: { float hc=native_exp(-fabs(zy))*ja/fmax(1e-10f,r); aux.DE*=(1.0f+jf*hc); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_12)
					case 12: { float q2=fmax(1.0f,ja), fr2=1.0f/(2.0f*q2*q2); aux.DE*=(1.0f+jf*fr2/fmax(1e-10f,r)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_13)
					case 13: { float med=(zx+zy)/(fmax(1e-10f,2.0f*r)); aux.DE*=(1.0f+jf*ja*med); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_14)
					case 14: { float jt=ja*native_sin(M_PI_F*zx/fmax(0.01f,jb))*native_sin(M_PI_F*zy/fmax(0.01f,jc)); aux.DE*=(1.0f+jf*jt/fmax(1e-10f,rr)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_15)
					case 15: { float eta=native_exp(M_PI_F*zy/(12.0f*fmax(0.01f,ja))); for(int n=1;n<8;n++) eta*=(1.0f-native_exp(-2.0f*M_PI_F*n*fabs(zy)/fmax(0.01f,ja))); aux.DE*=(1.0f+jf*fabs(eta)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_16)
					case 16: { float wp=1.0f/(rr+1e-10f); for(int n=1;n<6;n++){float dn2=(zx-n*ja)*(zx-n*ja)+(zy-n*jb)*(zy-n*jb)+zz2*zz2; wp+=1.0f/fmax(1e-10f,dn2)-1.0f/(n*n*ja*ja+n*n*jb*jb+1e-10f);} aux.DE*=(1.0f+jf*fabs(wp)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_17)
					case 17: { float th=0.0f; for(int n=0;n<8;n++){float qn=native_exp(-M_PI_F*n*n*fabs(zy)/fmax(0.01f,ja)); th+=qn*native_cos(2.0f*M_PI_F*n*zx/fmax(0.01f,ja));} aux.DE*=(1.0f+jf*fabs(th)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_18)
					case 18: { float eis=0.0f; for(int m=-3;m<=3;m++) for(int n=-3;n<=3;n++){if(m==0&&n==0)continue;float dn=m*ja+n*jb; eis+=1.0f/fmax(1e-10f,native_powr(fabs(dn*dn+rr),jc));} aux.DE*=(1.0f+jf*fabs(eis)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_19)
					case 19: { float hek=ja*native_sin(jfreq*r)*native_cos(jfreq*atan2(zy,zx)+jph); aux.DE*=(1.0f+jf*hek/fmax(1e-10f,r)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_20)
					case 20: { float maas=ja*native_sin(jfreq*native_log(fmax(1e-10f,r)))*native_cos(jfreq*atan2(zy,zx)); aux.DE*=(1.0f+jf*maas); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_21)
					case 21: { float selb=1.0f; for(int k=1;k<=5;k++){selb*=(1.0f-native_exp(-ja*k*r));} aux.DE*=(1.0f+jf*(1.0f-fabs(selb))); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_22)
					case 22: { float ruel=1.0f; for(int k=1;k<=5;k++){ruel*=(1.0f-native_exp(-ja*k*native_log(fmax(1e-10f,r))));} aux.DE*=(1.0f+jf*fabs(ruel)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_23)
					case 23: { float dz=ja*native_sin(jfreq*r)*native_exp(-jb*r); aux.DE*=(1.0f+jf*dz); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_24)
					case 24: { float gut=0.0f; for(int p=1;p<=5;p++){gut+=ja*native_cos(jfreq*p*r+jph)/fmax(1.0f,(float)p);} aux.DE*=(1.0f+jf*gut/fmax(1e-10f,r)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_25)
					case 25: { float berry=ja*zy*zz2/fmax(1e-10f,rr*r); aux.DE*=(1.0f+jf*berry); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_26)
					case 26: { float hann=ja*zx*zy/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*hann); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_27)
					case 27: { float ab_ph=ja*atan2(zy,zx)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*ab_ph); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_28)
					case 28: { float ac_ph=ja*jb*zz2/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*ac_ph); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_29)
					case 29: { float sab=ja*native_sin(jfreq*r)*zy/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*sab); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_30)
					case 30: { float hmw=ja*(zx*zy-zy*zz2)/fmax(1e-10f,rr*r); aux.DE*=(1.0f+jf*hmw); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_31)
					case 31: { float ana=ja*native_sin(jfreq*rr+jph)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*ana); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_32)
					case 32: { float panch=ja*native_cos(jfreq*zx)*native_cos(jfreq*zy)*native_cos(jfreq*zz2); aux.DE*=(1.0f+jf*panch/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_33)
					case 33: { float mt=ja/(2.0f*fmax(1e-10f,fabs(zx-zy))); aux.DE*=(1.0f+jf*tanh(mt)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_34)
					case 34: { float ml=M_PI_F*ja/(2.0f*fmax(1e-10f,r)); aux.DE*=(1.0f+jf*tanh(ml)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_35)
					case 35: { float sw=ja*jb/(fmax(1e-10f,r)*jc); aux.DE*=(1.0f+jf*tanh(sw)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_36)
					case 36: { float pw=ja*native_exp(-jb*rr); aux.DE*=(1.0f+jf*pw); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_37)
					case 37: { float gp=ja*native_sqrt(fmax(0.0f,r/jb)); aux.DE*=(1.0f+jf*tanh(gp)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_38)
					case 38: { float rov=ja*native_sin(jfreq*zx+jph)*native_cos(jfreq*zy); aux.DE*=(1.0f+jf*rov/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_39)
					case 39: { float barb=ja*native_sqrt(fmax(0.0f,zx*zx+zy*zy))/fmax(1e-10f,r); aux.DE*=(1.0f+jf*barb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_40)
					case 40: { float con=ja*native_exp(-jb*fabs(zz2))*native_sin(jfreq*r); aux.DE*=(1.0f+jf*con); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_41)
					case 41: { float ach=ja*native_sin(jfreq*zx)*native_sin(jfreq*zy)*native_cos(jfreq*zz2)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*ach); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_42)
					case 42: { float que=ja/(fmax(1e-10f,rr)); aux.DE*=(1.0f+jf*que); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_43)
					case 43: { float rw=0.0f; for(int n=1;n<=8;n++){rw+=native_cos(jfreq*n*zx+jph*n)*native_exp(-jb*n);} aux.DE*=(1.0f+jf*ja*rw/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_44)
					case 44: { float nd=ja*native_floor(native_sin(jfreq*zx)*native_sin(jfreq*zy)*4.0f+2.0f)/4.0f; aux.DE*=(1.0f+jf*nd); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_45)
					case 45: { float nl=ja*fabs(native_sin(jfreq*zx)*native_cos(jfreq*zy))*jb; aux.DE*=(1.0f+jf*nl/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_46)
					case 46: { float pc=ja*(tanh(jb*(r-jc))+1.0f)*0.5f; aux.DE*=(1.0f+jf*pc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_47)
					case 47: { float ip=ja*tanh(jb*(native_sin(jfreq*zx)+native_sin(jfreq*zy)+native_sin(jfreq*zz2))); aux.DE*=(1.0f+jf*ip); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_48)
					case 48: { float cle=ja*native_sin(jfreq*atan2(zy,zx))*native_exp(-jb*r); aux.DE*=(1.0f+jf*cle); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_49)
					case 49: { float sle=ja*zy/(fmax(1e-10f,rr))*native_exp(-jb*fabs(zx)); aux.DE*=(1.0f+jf*sle); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_50)
					case 50: { float gff=ja*native_cos(jfreq*zx)*native_cos(jfreq*zy)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*gff); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_51)
					case 51: { float lqg=ja*native_exp(fmin(jb*native_sin(jfreq*r+jph),20.0f)); aux.DE*=(1.0f+jf*lqg/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_52)
					case 52: { float bm=ja*native_sqrt(fmax(0.0f,rr-jb*jb))/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*bm); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_53)
					case 53: { float pm2=ja*(2.0f-fabs(zx)+fabs(zy)-fabs(zz2))/fmax(1e-10f,r); aux.DE*=(1.0f+jf*tanh(pm2)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_54)
					case 54: { float tt=ja*(zx*zy+zy*zz2+zz2*zx)/fmax(1e-10f,rr*r); aux.DE*=(1.0f+jf*tt); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_55)
					case 55: { float jon=ja*native_sin(M_PI_F*jb*r+jph)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*jon); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_56)
					case 56: { float hom=ja*(native_sin(jfreq*zx)+native_sin(jfreq*zy))*jb/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*hom); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_57)
					case 57: { float kau=ja*tanh(jb*native_sin(jfreq*r)*native_cos(jfreq*atan2(zy,zx))); aux.DE*=(1.0f+jf*kau); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_58)
					case 58: { float cs=ja*native_sin(jfreq*zx)*native_sin(jfreq*zy)*native_sin(jfreq*zz2)/(fmax(1e-10f,r*r)); aux.DE*=(1.0f+jf*cs); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_59)
					case 59: { float wrt=ja*jb*native_cos(jfreq*r+jph)/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*wrt); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_60)
					case 60: { float tv=ja*jb*jc/(fmax(1e-10f,rr*r)); aux.DE*=(1.0f+jf*tanh(tv)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_61)
					case 61: { float cy=ja*native_pow(fmax(1e-10f,r),jb-3.0f); aux.DE*=(1.0f+jf*cy); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_62)
					case 62: { float dw=ja/(fmax(1e-10f,rr))*native_cos(jfreq*zz2); aux.DE*=(1.0f+jf*dw); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_63)
					case 63: { float yd=ja*jb*(zx*zy-zy*zx)/(fmax(1e-10f,rr)); aux.DE*=(1.0f+jf*yd*jc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_64)
					case 64: { float mtc=ja*native_sin(jfreq*zx+jph)*native_cos(jfreq*zy)*native_sin(jfreq*zz2)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*mtc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_65)
					case 65: { float fus=ja*(native_sin(jb*zx)*native_sin(jc*zy)+native_sin(jd*zz2))/fmax(1e-10f,r); aux.DE*=(1.0f+jf*fus); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_66)
					case 66: { float bra=ja*native_cos(jfreq*atan2(zy,zx)+jph)*native_cos(jfreq*atan2(zz2,r)); aux.DE*=(1.0f+jf*bra); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_67)
					case 67: { float rib=ja*native_sin(jfreq*r)*native_cos(jb*atan2(zy,zx)+jph); aux.DE*=(1.0f+jf*rib/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_68)
					case 68: { float hopf=ja*jb*tanh(jc*(zx*zy+zy*zz2)); aux.DE*=(1.0f+jf*hopf/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_69)
					case 69: { float qg=ja*native_pow(fmax(1e-10f,r),-jb)*native_sin(jfreq*r+jph); aux.DE*=(1.0f+jf*qg); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_70)
					case 70: { float dd=ja*jb*(1.0f/(fmax(1e-10f,rr))+zx*zy/(fmax(1e-10f,rr*r))); aux.DE*=(1.0f+jf*tanh(dd)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_71)
					case 71: { float nich=ja*native_exp(-jb*rr)*native_sin(jfreq*zx)*native_cos(jfreq*zy); aux.DE*=(1.0f+jf*nich); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_72)
					case 72: { float rack=ja*(zx*zx-zy*zy)/(fmax(1e-10f,rr))*jb; aux.DE*=(1.0f+jf*rack); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_73)
					case 73: { float quan=ja*(zx*zx*zx-3.0f*zx*zy*zy)/(fmax(1e-10f,rr*r))*jb; aux.DE*=(1.0f+jf*quan); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_74)
					case 74: { float biq=ja*native_sin(jfreq*(zx+zy))*native_cos(jfreq*(zx-zy))/fmax(1e-10f,r); aux.DE*=(1.0f+jf*biq); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_75)
					case 75: { float ske=ja*jb*native_sin(jfreq*r+jph)/(fmax(1e-10f,rr)); aux.DE*=(1.0f+jf*ske); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_76)
					case 76: { float khov=ja*native_pow(fmax(1e-10f,native_sin(jfreq*r)),2.0f)*jb/fmax(1e-10f,r); aux.DE*=(1.0f+jf*khov); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_77)
					case 77: { float hf=ja*native_exp(-jb*r)*native_cos(jfreq*zz2+jph); aux.DE*=(1.0f+jf*hf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_78)
					case 78: { float kf=ja*atan2(zy,zx)*native_exp(-jb*fabs(zz2))/M_PI_F; aux.DE*=(1.0f+jf*kf/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_79)
					case 79: { float ech2=ja*native_sin(jfreq*zx)*native_exp(-jb*zy)*native_cos(jfreq*zz2)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*ech2); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_80)
					case 80: { float sft=ja*native_cos(jfreq*r)*native_sin(jfreq*atan2(zy,zx)+jph)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*sft); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_81)
					case 81: { float lag=ja*(zx*zy+zy*zz2)/(fmax(1e-10f,rr))*jb; aux.DE*=(1.0f+jf*lag); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_82)
					case 82: { float fuk=ja*native_sin(jb*zx)*native_cos(jc*zy)*native_sin(jd*zz2)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*fuk); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_83)
					case 83: { float mir=ja*(native_sin(jfreq*zx)*native_sin(jfreq*zy)-native_cos(jfreq*zz2))/fmax(1e-10f,r); aux.DE*=(1.0f+jf*mir); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_84)
					case 84: { float hmir=ja*native_cos(jfreq*(zx+zy+zz2)+jph)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*hmir); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_85)
					case 85: { float syz=ja*native_sin(jfreq*r)*native_sin(jfreq*atan2(zy,zx))*native_cos(jfreq*zz2/fmax(0.01f,jb)); aux.DE*=(1.0f+jf*syz); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_86)
					case 86: { float slag=ja*native_cos(jfreq*zx+jph)*jb; aux.DE*=(1.0f+jf*slag/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_87)
					case 87: { float g2=ja*native_sin(jfreq*zx)*native_sin(jfreq*zy)*native_sin(jfreq*zz2)*jb; aux.DE*=(1.0f+jf*g2/fmax(1e-10f,rr)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_88)
					case 88: { float sp7=ja*native_cos(jfreq*(zx*zy+zy*zz2+zz2*zx)/fmax(1e-10f,rr)+jph); aux.DE*=(1.0f+jf*sp7); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_89)
					case 89: { float cy2=ja*native_exp(-jb*rr)*jc; aux.DE*=(1.0f+jf*cy2); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_90)
					case 90: { float hkah=ja*(zx*zx-zy*zy+zz2*zz2)/(fmax(1e-10f,rr*r))*jb; aux.DE*=(1.0f+jf*hkah); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_91)
					case 91: { float qkah=ja*jb*(zx*zy*zz2)/(fmax(1e-10f,rr*rr)); aux.DE*=(1.0f+jf*tanh(qkah)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_92)
					case 92: { float sas=ja*native_sqrt(fmax(0.0f,r-jb))/fmax(1e-10f,r); aux.DE*=(1.0f+jf*sas); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_93)
					case 93: { float s3s=ja*(native_sin(jfreq*zx)+native_sin(jfreq*zy)+native_sin(jfreq*zz2))/(3.0f*fmax(1e-10f,r)); aux.DE*=(1.0f+jf*s3s); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_94)
					case 94: { float exh=ja*native_pow(fmax(1e-10f,r),-jb)*native_cos(jfreq*r+jph); aux.DE*=(1.0f+jf*exh); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_95)
					case 95: { float joy=ja*native_sin(jfreq*zx/fmax(0.01f,jb))*native_sin(jfreq*zy/fmax(0.01f,jc))*native_sin(jfreq*zz2/fmax(0.01f,jd)); aux.DE*=(1.0f+jf*joy); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_96)
					case 96: { float kov=ja*native_exp(-jb*fabs(zz2))*native_cos(jfreq*native_sqrt(fmax(0.0f,zx*zx+zy*zy))); aux.DE*=(1.0f+jf*kov); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_97)
					case 97: { float chnp=ja*jb*tanh(jc*r-jd); aux.DE*=(1.0f+jf*chnp/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_98)
					case 98: { float bs=ja*native_exp(-jb*r)*native_cos(jfreq*r+jph)*jc; aux.DE*=(1.0f+jf*bs); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_99)
					case 99: { float ah=ja*jb/(fmax(1e-10f,rr))*native_cos(jfreq*atan2(zy,zx)+jph); aux.DE*=(1.0f+jf*ah); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JOSLEYSDETYPE_100)
					case 100: { float gh=ja*jb*jc/fmax(1e-10f,r)*native_sin(jfreq*zz2+jph); aux.DE*=(1.0f+jf*gh); break; }
#endif

					default: break;
#endif
				}
			}

			// v7.7 — Pseudokleinian DE system (per-section iteration range)
			if (i >= mut->pkIterStart && i < mut->pkIterStop && mut->pseudoKleinianDeType != 0)
			{
				float pf = mut->pkFactor * mut->pkWeight * mut->masterWeight;
				float pa = mut->pkParamA, pb = mut->pkParamB, pc = mut->pkParamC, pd = mut->pkParamD;
				float pfreq = mut->pkFreq, pamp = mut->pkAmp, psc = mut->pkScale, pph = mut->pkPhase;
				float zx = z.x, zy = z.y, zz2 = z.z;
				float rr = zx*zx + zy*zy + zz2*zz2; if (rr < 1e-21f) rr = 1e-21f;
				float r = native_sqrt(rr);
				switch (mut->pseudoKleinianDeType)
				{
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_1)
					case 1: { float mu=pa*zy/fmax(1e-10f,rr); aux.DE*=(1.0f+pf*tanh(mu)); break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_2)
					case 2: { float bers=pa*native_log(fmax(1e-10f,r))*pb; aux.DE*=(1.0f+pf*tanh(bers)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_3)
					case 3: { float eq=pa*native_sin(pfreq*zx)*native_cos(pfreq*zy); aux.DE*=(1.0f+pf*eq/fmax(1e-10f,r)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_4)
					case 4: { float bc=pa*pb*zy/fmax(1e-10f,rr); aux.DE*=(1.0f+pf*bc); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_5)
					case 5: { float ham=pa*native_exp(-pb*r)*native_sin(pfreq*zx); aux.DE*=(1.0f+pf*ham); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_6)
					case 6: { float wp=pa*pb/(fmax(1e-10f,rr)); aux.DE*=(1.0f+pf*wp); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_7)
					case 7: { float tm=pa*fabs(zx-zy)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*tanh(tm)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_8)
					case 8: { float kob=pa*tanh(pb*r)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*kob); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_9)
					case 9: { float car=pa*fabs(native_sin(pfreq*r))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*car); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_10)
					case 10: { float berg=pa*pb*native_cos(pfreq*zx+pph)*native_cos(pfreq*zy)/fmax(1e-10f,rr); aux.DE*=(1.0f+pf*berg); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_11)
					case 11: { float ke=pa*pb/fmax(1e-10f,r)*tanh(pc*rr); aux.DE*=(1.0f+pf*ke); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_12)
					case 12: { float csc2=pa*tanh(pb*(r-pc)); aux.DE*=(1.0f+pf*csc2); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_13)
					case 13: { float duy=pa*pb*native_exp(-pc*rr); aux.DE*=(1.0f+pf*duy); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_14)
					case 14: { float hk=pa*native_sin(pfreq*zx)*native_cos(pfreq*zy)*native_exp(-pb*fabs(zz2)); aux.DE*=(1.0f+pf*hk); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_15)
					case 15: { float nah=pa*pb*(zx*zy+zy*zz2)/(fmax(1e-10f,rr*r)); aux.DE*=(1.0f+pf*nah); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_16)
					case 16: { float hm=pa*native_exp(-pb*rr)*native_cos(pfreq*r+pph); aux.DE*=(1.0f+pf*hm); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_17)
					case 17: { float ms=pa*(1.0f-zz2/fmax(1e-10f,r)); aux.DE*=(1.0f+pf*ms*pb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_18)
					case 18: { float cmc=pa*native_cos(pfreq*zx)*native_cos(pfreq*zy)*pb; aux.DE*=(1.0f+pf*cmc/fmax(1e-10f,r)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_19)
					case 19: { float wil=pa*(zx*zx+zy*zy)/(fmax(1e-10f,rr*r))*pb; aux.DE*=(1.0f+pf*wil); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_20)
					case 20: { float iso=pa*native_cos(pfreq*zx+pph)*native_cos(pfreq*zy)*pb; aux.DE*=(1.0f+pf*iso); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_21)
					case 21: { float lax=pa*native_sin(pfreq*zx)*native_cos(pfreq*zy)*native_sin(pfreq*zz2)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*lax); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_22)
					case 22: { float bac=pa*native_exp(-pb*r)*native_sin(pfreq*r+pph); aux.DE*=(1.0f+pf*bac); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_23)
					case 23: { float dar=pa*pb*native_cos(pfreq*r+pph)/fmax(1e-10f,rr); aux.DE*=(1.0f+pf*dar); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_24)
					case 24: { float mou=pa*native_sin(pfreq*zx)*native_sin(pfreq*zy)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*mou); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_25)
					case 25: { float hir=pa*pb*native_exp(-pc*rr)*native_cos(pfreq*r); aux.DE*=(1.0f+pf*hir); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_26)
					case 26: { float sat=pa*native_sin(pfreq*zx+pph)*native_cos(pfreq*zy)*native_sin(pfreq*zz2)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*sat); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_27)
					case 27: { float kp=pa*(native_sin(pfreq*zx)*native_cos(pfreq*zy)+native_sin(pfreq*zy)*native_cos(pfreq*zz2))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*kp); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_28)
					case 28: { float kdv=pa*native_sin(pfreq*zx+pph)*native_exp(-pb*zy*zy)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*kdv); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_29)
					case 29: { float nls=pa*native_exp(-pb*(zx*zx+zy*zy))*native_cos(pfreq*zz2+pph); aux.DE*=(1.0f+pf*nls); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_30)
					case 30: { float sg=pa*native_sin(native_sin(pfreq*zx+pph))*pb; aux.DE*=(1.0f+pf*sg/fmax(1e-10f,r)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_31)
					case 31: { float toda=pa*native_exp(pb*(zx-zy))-pa*native_exp(pb*(zy-zz2)); aux.DE*=(1.0f+pf*tanh(toda)/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_32)
					case 32: { float cm=0.0f; {float d1=zx-zy; float d2=zy-zz2; float d3=zx-zz2; cm=pa*(1.0f/fmax(1e-10f,d1*d1*d1)+1.0f/fmax(1e-10f,d2*d2*d2)+1.0f/fmax(1e-10f,d3*d3*d3));} aux.DE*=(1.0f+pf*tanh(cm)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_33)
					case 33: { float rs=pa*tanh(pb*(zx-zy))*tanh(pb*(zy-zz2))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*rs); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_34)
					case 34: { float hs=pa*pb*(zx*zy+zy*zz2+zz2*zx)/(fmax(1e-10f,rr*r)); aux.DE*=(1.0f+pf*hs); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_35)
					case 35: { float bm=pa*native_sin(pfreq*zx)*native_sin(pfreq*zy)*pb/fmax(1e-10f,r); aux.DE*=(1.0f+pf*bm); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_36)
					case 36: { float aci=pa*native_sin(pfreq*r+pph)*native_cos(pfreq*atan2(zy,zx))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*aci); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_37)
					case 37: { float sep=pa*(native_sin(pb*zx)+native_sin(pc*zy)+native_sin(pd*zz2))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*sep); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_38)
					case 38: { float aa=pa*native_cos(pfreq*r)*pfreq/fmax(1e-10f,r); aux.DE*=(1.0f+pf*aa); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_39)
					case 39: { float kam=pa*native_cos(pfreq*r+pph)*(1.0f-pb/fmax(1e-10f,r)); aux.DE*=(1.0f+pf*kam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_40)
					case 40: { float nek=pa*native_exp(-1.0f/fmax(1e-10f,native_pow(fmax(1e-10f,pb),pc))); aux.DE*=(1.0f+pf*nek); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_41)
					case 41: { float ard=pa*native_sin(pfreq*zx)*native_cos(pfreq*zy)*native_sin(pfreq*zz2)/fmax(1e-10f,rr); aux.DE*=(1.0f+pf*ard); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_42)
					case 42: { float abm=pa*fabs(native_sin(pfreq*zx+pph))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*abm); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_43)
					case 43: { float mse=pa*pb*native_exp(-pc*rr)*native_sin(pfreq*zx); aux.DE*=(1.0f+pf*mse); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_44)
					case 44: { float pei=pa*(1.0f-native_exp(-pb*fabs(zx-zy)))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*pei); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_45)
					case 45: { float fk=pa*native_sin(pfreq*zx+pph)*native_cos(pb*zy); aux.DE*=(1.0f+pf*fk/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_46)
					case 46: { float sm=pa*native_sin(pfreq*atan2(zy,zx)+pph)*pb; aux.DE*=(1.0f+pf*sm/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_47)
					case 47: { float chi=pa*tanh(pb*(r-pc)); aux.DE*=(1.0f+pf*chi); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_48)
					case 48: { float gre=0.5f*(1.0f-pa*native_cos(pfreq*r+pph)/fmax(1e-10f,r)); aux.DE*=(1.0f+pf*gre); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_49)
					case 49: { float rg=pa*native_pow(fmax(1e-10f,r),-pb)*native_cos(pfreq*native_log(fmax(1e-10f,r))+pph); aux.DE*=(1.0f+pf*rg); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_50)
					case 50: { float fg=pa*4.669201609f*native_sin(pfreq*r+pph)/(fmax(1e-10f,r)); aux.DE*=(1.0f+pf*fg); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_51)
					case 51: { float sh3=pa*native_floor(native_sin(pfreq*zx)*3.0f+1.5f)/3.0f; aux.DE*=(1.0f+pf*sh3); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_52)
					case 52: { float sar=pa*(native_sin(pfreq*zx)*native_sin(pfreq*zy)*native_sin(pfreq*zz2)>0.0f?1.0f:-1.0f)*pb; aux.DE*=(1.0f+pf*sar/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_53)
					case 53: { float sml=pa*tanh(pb*zx)*tanh(pb*zy); aux.DE*=(1.0f+pf*sml); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_54)
					case 54: { float ano=pa*fabs(fmod(pb*zx+pc*zy,1.0f)-0.5f)*4.0f; aux.DE*=(1.0f+pf*ano/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_55)
					case 55: { float axa=pa*native_exp(-pb*r)*native_cos(pfreq*r+pph); aux.DE*=(1.0f+pf*axa); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_56)
					case 56: { float srb=pa*pb*native_exp(-pc*rr)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*srb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_57)
					case 57: { float pes=0.0f; {float lya=pa*native_log(fmax(1e-10f,r)); pes=lya*pb;} aux.DE*=(1.0f+pf*tanh(pes)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_58)
					case 58: { float ly=pa*pb*native_log(fmax(1e-10f,r))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*tanh(ly)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_59)
					case 59: { float yt=pa*native_exp(-pb*r)*native_sin(pfreq*r+pph); aux.DE*=(1.0f+pf*yt); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_60)
					case 60: { float to=pa*pb*native_sin(pfreq*zx)*native_sin(pfreq*zy)/(fmax(1e-10f,rr)); aux.DE*=(1.0f+pf*to); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_61)
					case 61: { float rpf=pa*native_exp(-pb*r)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*rpf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_62)
					case 62: { float thf=pa*tanh(pb*(r-pc))*pd; aux.DE*=(1.0f+pf*thf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_63)
					case 63: { float gib=pa*native_exp(-pb*rr)*pc; aux.DE*=(1.0f+pf*gib); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_64)
					case 64: { float eqs=pa*native_cos(pfreq*r+pph)/(fmax(1e-10f,r)); aux.DE*=(1.0f+pf*eqs); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_65)
					case 65: { float pht=pa*(1.0f/(1.0f+native_exp(-pb*(r-pc)))-0.5f)*2.0f; aux.DE*=(1.0f+pf*pht); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_66)
					case 66: { float brf=pa*native_exp(-pb*r)*native_cos(pfreq*atan2(zy,zx)+pph); aux.DE*=(1.0f+pf*brf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_67)
					case 67: { float spc=pa*native_sin(pfreq*zx)*native_cos(pfreq*zy)*native_sin(pfreq*zz2)*pb; aux.DE*=(1.0f+pf*spc/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_68)
					case 68: { float sha=pa*native_exp(-pb*fabs(r-pc)); aux.DE*=(1.0f+pf*sha); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_69)
					case 69: { float sst=pa*native_cos(pfreq*r+pph)*native_exp(-pb*r); aux.DE*=(1.0f+pf*sst); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_70)
					case 70: { float oms=pa*native_sin(pfreq*zx)*native_sin(pfreq*zy)*pb/fmax(1e-10f,rr); aux.DE*=(1.0f+pf*oms); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_71)
					case 71: { float mss=pa*native_exp(-pb*r)*(1.0f-native_cos(pfreq*r)); aux.DE*=(1.0f+pf*mss); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_72)
					case 72: { float gfl=-pa*pb*(zx+zy+zz2)/fmax(1e-10f,r*r); aux.DE*=(1.0f+pf*tanh(gfl)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_73)
					case 73: { float mor=pa*(r-pb)*(r-pb)*native_exp(-pc*r); aux.DE*=(1.0f+pf*mor/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_74)
					case 74: { float moh=pa*native_exp(-pb*rr)*native_sin(pfreq*r+pph); aux.DE*=(1.0f+pf*moh); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_75)
					case 75: { float flo=pa*native_sin(pfreq*zx)*native_cos(pfreq*zy)*pb; aux.DE*=(1.0f+pf*flo/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_76)
					case 76: { float sca=pa*pb*r*r/(fmax(1e-10f,r*r+pc*pc)); aux.DE*=(1.0f+pf*sca); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_77)
					case 77: { float hof=pa*pb/fmax(1e-10f,r); aux.DE*=(1.0f+pf*tanh(hof)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_78)
					case 78: { float hz=pa*M_PI_F*pb/(2.0f*fmax(1e-10f,r)); aux.DE*=(1.0f+pf*tanh(hz)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_79)
					case 79: { float ekh=pa*native_sin(pfreq*r+pph)*pb/fmax(1e-10f,r); aux.DE*=(1.0f+pf*ekh); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_80)
					case 80: { float nsq=pa*pb*(1.0f-r/fmax(1e-10f,pc)); aux.DE*=(1.0f+pf*tanh(nsq)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_81)
					case 81: { float emb=pa*pb*native_sin(pfreq*r+pph)/fmax(1e-10f,rr); aux.DE*=(1.0f+pf*emb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_82)
					case 82: { float echc=pa*native_sin(pfreq*zx)*native_cos(pfreq*zy)*pb/fmax(1e-10f,r); aux.DE*=(1.0f+pf*echc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_83)
					case 83: { float fib=pa*native_sin(pfreq*r)*native_cos(1.618033988749f*pfreq*r+pph)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*fib); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_84)
					case 84: { float hut=pa*pb*native_sin(pfreq*atan2(zy,zx)+pph)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*hut); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_85)
					case 85: { float cmk=pa*native_cos(pfreq*r)*native_exp(-pb*r)*pc; aux.DE*=(1.0f+pf*cmk); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_86)
					case 86: { float vfc=pa*pb*native_sin(pfreq*r+pph)/(fmax(1e-10f,r*r)); aux.DE*=(1.0f+pf*vfc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_87)
					case 87: { float pol=pa*native_exp(-pb*rr)*native_cos(pfreq*r)*pc; aux.DE*=(1.0f+pf*pol); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_88)
					case 88: { float scc=pa*tanh(pb*r)*native_cos(pfreq*r+pph)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*scc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_89)
					case 89: { float gwi=pa*pb*native_sin(pfreq*zx)*native_sin(pfreq*zy)*native_sin(pfreq*zz2)/(fmax(1e-10f,rr)); aux.DE*=(1.0f+pf*gwi); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_90)
					case 90: { float qco=pa*native_cos(pfreq*(zx+zy+zz2)+pph)*pb/fmax(1e-10f,r); aux.DE*=(1.0f+pf*qco); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_91)
					case 91: { float msy=pa*(native_sin(pfreq*zx)*native_sin(pfreq*zy)-native_cos(pfreq*zz2))/fmax(1e-10f,r); aux.DE*=(1.0f+pf*msy); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_92)
					case 92: { float hv=pa*native_exp(-pb*rr)*native_sin(pfreq*r+pph); aux.DE*=(1.0f+pf*hv); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_93)
					case 93: { float bat=pa*native_cos(pfreq*zx+pph)*native_cos(pfreq*zy)*native_cos(pfreq*zz2)/fmax(1e-10f,r); aux.DE*=(1.0f+pf*bat); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_94)
					case 94: { float gpo=pa*pb*native_sin(pfreq*r)/(fmax(1e-10f,r*r)); aux.DE*=(1.0f+pf*gpo); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_95)
					case 95: { float syzf=pa*native_sin(pfreq*r)*native_sin(pfreq*atan2(zy,zx)+pph)*pb; aux.DE*=(1.0f+pf*syzf/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_96)
					case 96: { float gs=pa*native_exp(-pb*fabs(zz2))*native_cos(pfreq*native_sqrt(fmax(0.0f,zx*zx+zy*zy))+pph); aux.DE*=(1.0f+pf*gs); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_97)
					case 97: { float scd=pa*pb*tanh(pc*native_sin(pfreq*r+pph)); aux.DE*=(1.0f+pf*scd/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_98)
					case 98: { float thf2=pa*native_sin(pfreq*zx+pph)*native_cos(pfreq*zy)*pb; aux.DE*=(1.0f+pf*thf2/fmax(1e-10f,r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_99)
					case 99: { float cla=pa*pb*(zx*zy+zy*zz2+zz2*zx)/(fmax(1e-10f,rr*r)); aux.DE*=(1.0f+pf*cla); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_PKDETYPE_100)
					case 100: { float clv=pa*native_sin(pfreq*(zx*zy+zy*zz2)/fmax(1e-10f,rr)+pph)*pb; aux.DE*=(1.0f+pf*clv); break; }
#endif

					default: break;
#endif
				}
			}

			// v7.8 [GPU] — Mandelbox Math system (per-section iteration range)
			if (i >= mut->mbIterStart && i < mut->mbIterStop && mut->mbMathType != 0)
			{
				float mf = mut->mbFactor * mut->mbMathWeight * mut->masterWeight;
				float ma = mut->mbParamA, mb = mut->mbParamB, mc = mut->mbParamC, md = mut->mbParamD;
				float me = mut->mbParamE, mff = mut->mbParamF, mg = mut->mbParamG, mh = mut->mbParamH;
				float zx = z.x, zy = z.y, zz2 = z.z;
				float rr = zx*zx + zy*zy + zz2*zz2; if (rr < 1e-21) rr = 1e-21;
				float r = native_sqrt(rr);
				switch (mut->mbMathType)
			{
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_1)
					case 1: { if(zx>ma) z.x=mb*2.0-zx; if(zx<-ma) z.x=-mb*2.0-zx; if(zy>ma) z.y=mb*2.0-zy; if(zy<-ma) z.y=-mb*2.0-zy; if(zz2>ma) z.z=mb*2.0-zz2; if(zz2<-ma) z.z=-mb*2.0-zz2; aux.DE*=fabs(mf); break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_2)
					case 2: { float lim=ma*(1.0+0.1*native_sin(i*mc)); if(fabs(zx)>lim) z.x=copysign(mb*2.0,zx)-zx; if(fabs(zy)>lim) z.y=copysign(mb*2.0,zy)-zy; if(fabs(zz2)>lim) z.z=copysign(mb*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_3)
					case 3: { float sx=ma,sy=mb,sz=mc, fx=1.0/(1.0+native_exp(-sx*(fabs(zx)-md))), fy=1.0/(1.0+native_exp(-sy*(fabs(zy)-md))), fz=1.0/(1.0+native_exp(-sz*(fabs(zz2)-md))); z.x=zx*(1.0-fx)+copysign(me*2.0-fabs(zx),zx)*fx; z.y=zy*(1.0-fy)+copysign(me*2.0-fabs(zy),zy)*fy; z.z=zz2*(1.0-fz)+copysign(me*2.0-fabs(zz2),zz2)*fz; aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_4)
					case 4: { float l1=ma,v1=mb,l2=mc,v2=md; if(fabs(zx)>l1) z.x=copysign(v1*2.0,zx)-zx; if(fabs(zx)>l2) z.x=copysign(v2*2.0,zx)-zx; if(fabs(zy)>l1) z.y=copysign(v1*2.0,zy)-zy; if(fabs(zy)>l2) z.y=copysign(v2*2.0,zy)-zy; if(fabs(zz2)>l1) z.z=copysign(v1*2.0,zz2)-zz2; if(fabs(zz2)>l2) z.z=copysign(v2*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_5)
					case 5: { float rxy=native_sqrt(zx*zx+zy*zy); if(rxy>ma){ float th=atan2(zy,zx); float nr=ma*2.0-rxy; z.x=nr*native_cos(th); z.y=nr*native_sin(th); } aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_6)
					case 6: { float rxy=native_sqrt(zx*zx+zy*zy), ea=(zx/(ma+1e-21))*(zx/(ma+1e-21))+(zy/(mb+1e-21))*(zy/(mb+1e-21)); if(ea>1.0){ float sc=1.0/native_sqrt(ea); z.x*=sc; z.y*=sc; } aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_7)
					case 7: { if(fabs(zx)+fabs(zy)>ma){ float sx=(zx>0)?1.0:-1.0,sy=(zy>0)?1.0:-1.0;float nx=ma*0.5*sx,ny=ma*0.5*sy; z.x=2.0*nx-zx; z.y=2.0*ny-zy; } aux.DE*=fabs(mf)*1.41421356; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_8)
					case 8: { float ax=fabs(zx),ay=fabs(zy), hx=fmax(ax,ay*0.8660254+ax*0.5); if(hx>ma){ z.x=copysign(ma*2.0-ax,zx); z.y=copysign(ma*2.0-ay,zy); } aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_9)
					case 9: { float ax=fabs(zx),ay=fabs(zy), ox=fmax(ax,fmax(ay,(ax+ay)*0.7071068)); if(ox>ma){ z.x=copysign(ma*2.0-ax,zx); z.y=copysign(ma*2.0-ay,zy); } aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_10)
					case 10: { float th=atan2(zy,zx), rxy=native_sqrt(zx*zx+zy*zy), rlim=ma*(1.0+mb*native_cos(mc*th)); if(rxy>rlim){ float nr=rlim*2.0-rxy; z.x=nr*native_cos(th); z.y=nr*native_sin(th); } aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_11)
					case 11: { float th=atan2(zy,zx), rxy=native_sqrt(zx*zx+zy*zy), rlim=ma*native_exp(-mb*th); if(rxy>rlim){ float nr=rlim*2.0-rxy; z.x=nr*native_cos(th); z.y=nr*native_sin(th); } aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_12)
					case 12: { float limy=ma+mb*native_sin(mc*zy); if(fabs(zx)>limy) z.x=copysign(limy*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; aux.DE*=fabs(mf)*(1.0+fabs(mb*mc)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_13)
					case 13: { float h1=ma+mb*native_sin(mc*zx)*native_sin(mc*zy)*native_sin(mc*zz2); if(fabs(zx)>h1) z.x=copysign(h1*2.0,zx)-zx; if(fabs(zy)>h1) z.y=copysign(h1*2.0,zy)-zy; if(fabs(zz2)>h1) z.z=copysign(h1*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_14)
					case 14: { float h1=ma+mb*native_sin(mc*zx)*native_cos(md*zy); if(fabs(zx)>h1) z.x=copysign(h1*2.0,zx)-zx; if(fabs(zy)>h1) z.y=copysign(h1*2.0,zy)-zy; if(fabs(zz2)>h1) z.z=copysign(h1*2.0,zz2)-zz2; aux.DE*=fabs(mf)*(1.0+fabs(mb*mc)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_15)
					case 15: { float jv=ma+0.1*native_sin(mc*zx)*native_sin(mc*zy); if(fabs(zx)>jv) z.x=copysign(jv*2.0,zx)-zx; if(fabs(zy)>jv) z.y=copysign(jv*2.0,zy)-zy; aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_16)
					case 16: { float lt=ma+0.1*native_sin(mb*i); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_17)
					case 17: { float lt=ma*(1.0+0.1*r); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_18)
					case 18: { float cl=fabs(length(z)), lt=ma+cl*mb; if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_19)
					case 19: { float c1=ma,c2=-ma; if(zx>c1+mb) z.x=2.0*c1+mb*2.0-zx; if(zx<c2-mb) z.x=2.0*c2-mb*2.0-zx; if(zy>c1+mb) z.y=2.0*c1+mb*2.0-zy; if(zy<c2-mb) z.y=2.0*c2-mb*2.0-zy; aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_20)
					case 20: { float lt=ma; for(int n=0;n<3&&n<(int)mb;n++){ lt*=0.5; if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; } aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_21)
					case 21: { if(i>(int)mb){ if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; } aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_22)
					case 22: { float h=(native_sin(i*12.9898+zx*78.233)*43758.5453 - floor(native_sin(i*12.9898+zx*78.233)*43758.5453)); if(h<mc){ if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; } aux.DE*=fabs(mf)*(1.0-mc+mc*mb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_23)
					case 23: { float dt=zx*mc+zy*md+zz2*me, lt=ma*(1.0+0.1*dt/fmax(1e-10,r)); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_24)
					case 24: { float lt=ma+mc*zx*zx; if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx;{ float lty=ma+mc*zy*zy; if(fabs(zy)>lty) z.y=copysign(lty*2.0,zy)-zy; aux.DE*=fabs(mf)*(1.0+2.0*fabs(mc*r)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_25)
					case 25: { float lt=ma+mb*native_sin(mc*zx); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx;{ float lty=ma+mb*native_sin(mc*zy); if(fabs(zy)>lty) z.y=copysign(lty*2.0,zy)-zy; float ltz=ma+mb*native_sin(mc*zz2); if(fabs(zz2)>ltz) z.z=copysign(ltz*2.0,zz2)-zz2; aux.DE*=fabs(mf)*(1.0+fabs(mb*mc)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_26)
					case 26: { float rre=(zx/(ma+1e-10))*(zx/(ma+1e-10))+(zy/(mb+1e-10))*(zy/(mb+1e-10))+(zz2/(mc+1e-10))*(zz2/(mc+1e-10)); if(rre<1e-21) rre=1e-21;{ float m2=md*md/rre; z*=m2; aux.DE*=m2; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_27)
					case 27: { float rrc=zx*zx+zy*zy; if(rrc<1e-21) rrc=1e-21;{ float m2=ma*ma/rrc; z.x*=m2; z.y*=m2; z.z*=m2; aux.DE*=m2; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_28)
					case 28: { float rxy=native_sqrt(zx*zx+zy*zy), rrt=(rxy-ma)*(rxy-ma)+zz2*zz2; if(rrt<1e-21) rrt=1e-21;{ float m2=mb*mb/rrt; z*=m2; aux.DE*=m2; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_29)
					case 29: { float rrh=zx*zx+zy*zy-zz2*zz2, ar=fabs(rrh); if(ar<1e-21) ar=1e-21;{ float m2=ma*ma/ar; z*=m2; aux.DE*=m2*fmax(1.0,fabs(zz2)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_30)
					case 30: { float rrp=zx*zx+zy*zy-ma*zz2, ar=fabs(rrp); if(ar<1e-21) ar=1e-21;{ float m2=mb*mb/ar; z*=m2; aux.DE*=m2*native_sqrt(1.0+4.0*ma*ma); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_31)
					case 31: { float mR2=ma*(1.0f+0.1f*native_sin(i*mc)); float fR2=mb; if(rr<mR2) z*=fR2/mR2; else if(rr<fR2) z*=fR2/rr; aux.DE*=fabs(mf)*fR2/fmax(1e-21f,fmin(rr,mR2)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_32)
					case 32: { float mx=ma,my=mb,mz=mc; float rrm=fmax(zx*zx/fmax(1e-21f,mx),fmax(zy*zy/fmax(1e-21f,my),zz2*zz2/fmax(1e-21f,mz))); float fR2=md; if(rrm<fR2){ float m2=fR2/fmax(1e-21f,rrm); z*=m2; aux.DE*=m2; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_33)
					case 33: { float mR2_1=ma,f1=mb,mR2_2=mc,f2=md; if(rr<mR2_1){ z*=f1; aux.DE*=f1; } float rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mR2_2){ z*=f2; aux.DE*=f2; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_34)
					case 34: { float sm=mc; float mR2=ma,fR2=mb; float t=1.0f/(1.0f+native_exp(-sm*(rr-mR2))); float m2=fR2/fmax(1e-21f,rr); float sf=(1.0f-t)*m2+t*1.0f; z*=sf; aux.DE*=sf; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_35)
					case 35: { float fR2=mb; float lg=native_log(fmax(1e-21f,fR2))/native_log(fmax(1e-21f,rr)); z*=lg; aux.DE*=lg/(rr*native_log(fmax(1e-21f,rr))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_36)
					case 36: { float fR2=mb; float ex=native_exp(fR2-rr); z*=ex; aux.DE*=ex; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_37)
					case 37: { float fR2=mb; float pw=mc; float m2=native_pow(fmax(1e-21f,fR2/rr),pw); z*=m2; aux.DE*=m2; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_38)
					case 38: { float k=mc,fR2=mb; float sg=1.0f/(1.0f+native_exp(k*(rr-fR2))); z*=sg; aux.DE*=sg; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_39)
					case 39: { float fR2=mb,sg=mc; float gs=native_exp(-(rr-fR2)*(rr-fR2)/(sg*sg+1e-21f)); z*=gs; aux.DE*=gs; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_40)
					case 40: { float mR2=ma,fR2=mb,f1=mc; float m2=(rr<mR2)?f1:((rr<fR2)?fR2/rr:1.0f); z*=m2; aux.DE*=m2; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_41)
					case 41: { float b1=ma,f1=mb,b2=mc,f2=md,b3=me,f3=mff; float m2=(rr<b1)?f1:((rr<b2)?f2:((rr<b3)?f3:1.0f)); z*=m2; aux.DE*=m2; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_42)
					case 42: { float fR2=mb; if(rr<fR2){ float m2=1.0f/fmax(1e-21f,rr); z.x=ma+fR2*(zx-ma)*m2; z.y=ma+fR2*(zy-ma)*m2; z.z=ma+fR2*(zz2-ma)*m2; aux.DE*=fR2*m2; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_43)
					case 43: { float fR2=mb; if(rr<fR2){ float den=mc*zx+md+1e-21f; z.x=(ma*zx+mb)/(den); z.y=zy/fmax(1e-10f,fabs(den)); z.z=zz2/fmax(1e-10f,fabs(den)); aux.DE*=fabs(ma*md-mb*mc)/(den*den); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_44)
					case 44: { float fR2=mb; if(rr<fR2){ float qn=rr; if(qn<1e-21f) qn=1e-21f; float m2=fR2/qn; z*=m2; aux.DE*=m2; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_45)
					case 45: { float dm=fmax(1e-10f,acosh(fmax(1.0f,r))); float dmax=ma; if(dm<dmax){ float sc=dmax/dm; z*=sc; aux.DE*=sc*dmax/(dm*sinh(dm)+1e-21f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_46)
					case 46: { float ox=ma,oy=mb,oz=mc; float rrc=(zx-ox)*(zx-ox)+(zy-oy)*(zy-oy)+(zz2-oz)*(zz2-oz); if(rrc<1e-21f) rrc=1e-21f; float fR2=md; if(rrc<fR2){ float m2=fR2/rrc; z*=m2; aux.DE*=m2; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_47)
					case 47: { float th=ma*M_PI_F/180.0f; float cs=native_cos(th),sn=native_sin(th); float rx=zx*cs-zy*sn; float ry=zx*sn+zy*cs; float rrc=rx*rx+ry*ry+zz2*zz2; if(rrc<1e-21f) rrc=1e-21f; float fR2=mb; if(rrc<fR2){ float m2=fR2/rrc; z*=m2; aux.DE*=m2; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_48)
					case 48: { float fR2=ma*(1.0f+0.1f*native_sin(i*mb)); float mR2=mc; if(rr<mR2){ z*=fR2/mR2; aux.DE*=fR2/mR2; } else if(rr<fR2){ z*=fR2/rr; aux.DE*=fR2/rr; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_49)
					case 49: { float mR2=ma,fR2=mb; float cf=(rr<mR2)?mc:((rr<fR2)?md:0.0f); aux.color+=cf; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_50)
					case 50: { aux.color+=native_log(fmax(1e-21f,aux.DE))*ma; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_51)
					case 51: { z.x*=ma; z.y*=mb; z.z*=mc; aux.DE*=fmax(fabs(ma),fmax(fabs(mb),fabs(mc))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_52)
					case 52: { float sc=ma+mb*native_sin(i*mc); z*=sc; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_53)
					case 53: { float sc=ma*native_exp(-i*mb); z*=sc; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_54)
					case 54: { float sc=ma/(1.0f+native_log(1.0f+i)); z*=sc; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_55)
					case 55: { float p=fmax(0.01f,mb); float sc=ma/fmax(1e-10f,native_pow(fmax(1.0f,(float)i),p)); z*=sc; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_56)
					case 56: { float f0=1,f1=1; for(int n=0;n<fmin((float)i,20.0f);n++){float t=f1;f1=f0+f1;f0=t;} float sc=ma/fmax(1.0f,f1); z*=sc; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_57)
					case 57: { float ns=native_sin(i*12.9898f+zx*78.233f)*43758.5453f; ns=ns-native_floor(ns); float sc=ma+ns*mb; z*=sc; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_58)
					case 58: { float jv=native_sin(i*mb)*native_cos(i*mc); float sc=ma+0.1f*fabs(jv); z*=sc; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_59)
					case 59: { float sc=ma*(1.0f+0.1f*r); z*=sc; aux.DE*=fabs(sc)*(1.0f+0.1f*r); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_60)
					case 60: { float sc=ma+0.1f*native_sin(i*mb); z*=sc; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_61)
					case 61: { float sc=ma+0.1f*mf; z*=sc; aux.DE*=fabs(sc)*1.1f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_62)
					case 62: { float sc=(zx>0)?ma:mb; z*=sc; aux.DE*=fmax(fabs(ma),fabs(mb)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_63)
					case 63: { float th=atan2(zy,zx); float sc=ma+mb*native_cos(mc*th); z*=sc; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_64)
					case 64: { float th=atan2(native_sqrt(zx*zx+zy*zy),zz2); float ph=atan2(zy,zx); float sc=ma+mb*native_cos(mc*th)*native_sin(md*ph); z*=sc; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_65)
					case 65: { float off=ma+0.1f*native_sin(i*mb); z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_66)
					case 66: { z.x+=ma; z.y+=mb; z.z+=mc; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_67)
					case 67: { float cl=length(pointTransformed); z.x+=cl*ma; z.y+=cl*ma; z.z+=cl*ma; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_68)
					case 68: { z.x+=zx*0.1f*ma; z.y+=zy*0.1f*ma; z.z+=zz2*0.1f*ma; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_69)
					case 69: { float ns=native_sin(zx*ma+zy*mb+zz2*mc)*md; z.x+=ns; z.y+=ns; z.z+=ns; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_70)
					case 70: { float off=ma+0.1f*native_sin(i*mb); z.x+=off; z.y+=off*0.5f; z.z+=off*0.25f; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_71)
					case 71: { float off=ma+0.1f*mf; z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_72)
					case 72: { float off=(rr<ma)?mb:mc; z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_73)
					case 73: { float off=ma*(1.0f+0.1f*r); z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_74)
					case 74: { float th=i*ma; float spr=mb; z.x+=spr*native_cos(th); z.y+=spr*native_sin(th); aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_75)
					case 75: { z.x+=ma*native_sin(mb*i); z.y+=mc*native_sin(md*i); z.z+=me*native_sin(mff*i); aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_76)
					case 76: { float ga=2.39996322973f; float th=i*ga; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx; z.y=ny; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_77)
					case 77: { float hth=ma*M_PI_F/360.0f; float ax=mb,ay=mc,az=md; float nm=native_sqrt(ax*ax+ay*ay+az*az+1e-21f); ax/=nm;ay/=nm;az/=nm; float cq=native_cos(hth),sq=native_sin(hth); float qw=cq,qx=sq*ax,qy=sq*ay,qz=sq*az; float nx=zx*(1-2*(qy*qy+qz*qz))+zy*2*(qx*qy-qw*qz)+zz2*2*(qx*qz+qw*qy); float ny=zx*2*(qx*qy+qw*qz)+zy*(1-2*(qx*qx+qz*qz))+zz2*2*(qy*qz-qw*qx); float nz=zx*2*(qx*qz-qw*qy)+zy*2*(qy*qz+qw*qx)+zz2*(1-2*(qx*qx+qy*qy)); z.x=nx;z.y=ny;z.z=nz; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_78)
					case 78: { float th=ma*M_PI_F/180.0f; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx; z.y=ny; float ph=mb*M_PI_F/180.0f; float cp=native_cos(ph),sp=native_sin(ph); float nxz=z.x*cp-zz2*sp; float nz=z.x*sp+zz2*cp; z.x=nxz; z.z=nz; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_79)
					case 79: { float th=ma*M_PI_F/180.0f; float cs=native_cos(th),sn=native_sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; float ph=mb*M_PI_F/180.0f; cs=native_cos(ph); sn=native_sin(ph); float ty=z.y*cs-zz2*sn; z.z=z.y*sn+zz2*cs; z.y=ty; float ps=mc*M_PI_F/180.0f; cs=native_cos(ps);sn=native_sin(ps); float tx=z.x*cs-z.z*sn; z.z=z.x*sn+z.z*cs; z.x=tx; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_80)
					case 80: { float v=ma; float gm=1.0f/native_sqrt(fmax(1e-10f,1.0f-v*v)); z.x=gm*(zx-v*zz2); z.z=gm*(zz2-v*zx); aux.DE*=fabs(mf)*gm; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_81)
					case 81: { z.x+=ma; z.y+=mb*native_sin(mc*zz2); aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_82)
					case 82: { float s=ma; float th=mb*M_PI_F/180.0f; float cs=native_cos(th),sn=native_sin(th); z.x=s*(zx*cs-zy*sn); z.y=s*(zx*sn+zy*cs); z.z*=s; aux.DE*=fabs(s)*fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_83)
					case 83: { float N=fmax(2.0f,ma); float th=2.0f*M_PI_F/N; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx; z.y=ny; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_84)
					case 84: { float ax=native_sin(i*ma),ay=native_cos(i*ma); float nm=native_sqrt(ax*ax+ay*ay+1e-21f); ax/=nm; ay/=nm; float th=mb*M_PI_F/180.0f; float cs=native_cos(th),sn=native_sin(th); float d=zx*ax+zy*ay; float px=zx-d*ax,py=zy-d*ay; float rx=px*cs-py*sn+d*ax,ry=px*sn+py*cs+d*ay; z.x=rx;z.y=ry; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_85)
					case 85: { float ns=native_sin(i*12.9898f+78.233f)*43758.5453f; ns=ns-native_floor(ns); float th=ns*2.0f*M_PI_F*ma; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_86)
					case 86: { float th=ma+mb*i; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_87)
					case 87: { float th=ma+mf; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_88)
					case 88: { if(zx>0){ float th=ma*M_PI_F/180.0f; float cs=native_cos(th),sn=native_sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; } else { float th=mb*M_PI_F/180.0f; float cs=native_cos(th),sn=native_sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; } aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_89)
					case 89: { float th=ma*(1.0f+0.1f*r); float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_90)
					case 90: { float ph=atan2(zy,zx); float th=ma+mb*native_cos(mc*ph); float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_91)
					case 91: { float N=fmax(2.0f,ma); float th=atan2(zy,zx); float sector=2.0f*M_PI_F/N; th=fmod(th+sector*0.5f+100.0f*sector,sector)-sector*0.5f; float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(th); z.y=rxy*native_sin(th); aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_92)
					case 92: { float nx=fabs(zx); float ny=fabs(zy); float nz2=fabs(zz2); if(ma>0) z.x=nx; if(mb>0) z.y=ny; if(mc>0) z.z=nz2; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_93)
					case 93: { z.x+=ma*zy; z.y+=mb*zz2; aux.DE*=fabs(mf)*native_sqrt(1.0f+ma*ma+mb*mb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_94)
					case 94: { float rxy=native_sqrt(zx*zx+zy*zy); float th=atan2(zy,zx)+ma*zz2; z.x=rxy*native_cos(th); z.y=rxy*native_sin(th); aux.DE*=fabs(mf)*native_sqrt(1.0f+ma*ma*rxy*rxy); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_95)
					case 95: { float cv=ma; float rxy=native_sqrt(zx*zx+zy*zy); float th=atan2(zy,zx)+cv*rxy; z.x=rxy*native_cos(th); z.y=rxy*native_sin(th); aux.DE*=fabs(mf)*(1.0f+cv*rxy); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_96)
					case 96: { float tf=ma; z.x*=(1.0f-tf*zz2); z.y*=(1.0f-tf*zz2); aux.DE*=fabs(mf)*(1.0f-tf*zz2); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_97)
					case 97: { float g=ma; float th=atan2(zy,zx)+g*native_log(fmax(1e-10f,native_sqrt(zx*zx+zy*zy))); float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(th); z.y=rxy*native_sin(th); aux.DE*=fabs(mf)*g; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_98)
					case 98: { float th=ma*native_exp(i*mb); float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_99)
					case 99: { float th=ma*native_log(1.0f+i); float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_100)
					case 100: { float p=mb; float th=ma*native_pow(fmax(1.0f,(float)i),p); float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; float ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_101)
					case 101: { float w=ma; float rr4=rr+w*w; if(rr4<1e-21f) rr4=1e-21f; float sc=mf; z.x=zx*sc+w*0.1f; z.y=zy*sc; z.z=zz2*sc; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_102)
					case 102: { float w=ma,v=mb; float rr5=rr+w*w+v*v; if(rr5<1e-21f) rr5=1e-21f; float sc=mf; z*=sc; z.x+=w*0.05f; z.y+=v*0.05f; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_103)
					case 103: { float w=ma*native_sin(mb*i); z.x+=w*0.1f; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_104)
					case 104: { float th4=ma*M_PI_F/180.0f; float cs=native_cos(th4),sn=native_sin(th4); float nw=zz2*sn; z.z=zz2*cs; z.x+=nw*0.1f; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_105)
					case 105: { float cx=ma,cy=mb,cz=mc; (void)md; z.x+=cx*mf; z.y+=cy*mf; z.z+=cz*mf; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_106)
					case 106: { float qw=ma,qx=zx,qy=zy,qz=zz2; float nm=native_sqrt(qw*qw+qx*qx+qy*qy+qz*qz+1e-21f); z.x=qx/nm*mf; z.y=qy/nm*mf; z.z=qz/nm*mf; aux.DE*=fabs(mf)/nm; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_107)
					case 107: { float q1w=ma,q2w=mb; float nm1=native_sqrt(zx*zx+zy*zy+q1w*q1w+1e-21f); float nm2=native_sqrt(zz2*zz2+q2w*q2w+1e-21f); z.x*=nm2/(nm1+1e-21f); z.y*=nm2/(nm1+1e-21f); aux.DE*=fabs(mf)*nm2/(nm1+1e-21f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_108)
					case 108: { float d4=native_sqrt(rr+ma*ma); float td=tanh(d4); z*=td/fmax(1e-10f,d4); float ch=cosh(d4); aux.DE*=fabs(mf)/(ch*ch+1e-21f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_109)
					case 109: { float rr4=rr+ma*ma; float nm4=native_sqrt(rr4+1e-21f); z*=1.0f/nm4; aux.DE*=fabs(mf)/nm4; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_110)
					case 110: { float rxy=native_sqrt(zx*zx+zy*zy+1e-21f); z.x=(rxy-ma)*native_cos(atan2(zy,zx)); z.y=(rxy-ma)*native_sin(atan2(zy,zx)); aux.DE*=fabs(mf)*rxy; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_111)
					case 111: { float R=ma,rr2=mb; float th=atan2(zy,zx); z.x=(R+rr2*native_cos(th))*native_cos(mc*i); z.y=(R+rr2*native_cos(th))*native_sin(mc*i); z.z=rr2*native_sin(th); aux.DE*=fabs(mf)*R; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_112)
					case 112: { float th=ma*M_PI_F/180.0f; float ph=mb*M_PI_F/180.0f; float cs1=native_cos(th),sn1=native_sin(th),cs2=native_cos(ph); float nx=zx*cs1-zy*sn1; float ny=zx*sn1+zy*cs1; float nz2=zz2*cs2; z.x=nx;z.y=ny;z.z=nz2; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_113)
					case 113: { float ga=2.39996322973f; float th=i*ga; float r4=native_sqrt(rr+1e-21f); z.x=r4*native_cos(th)*native_cos(ma*i); z.y=r4*native_sin(th)*native_cos(ma*i); z.z=r4*native_sin(ma*i); aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_114)
					case 114: { float D=ma; float sc=native_pow(2.0f,D); z*=sc/fmax(1e-10f,r); aux.DE*=sc/fmax(1e-10f,r); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_115)
					case 115: { float h=((native_sin(i*12.9898f+78.233f)*43758.5453f) - native_floor(native_sin(i*12.9898f+78.233f)*43758.5453f)); if(h<ma){ z.x=-z.x; z.y=-z.y; } aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_116)
					case 116: { float w=ma+0.1f*native_sin(i*mb); z.x+=w*0.1f; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_117)
					case 117: { z.x+=0.1f*zx*ma; z.y+=0.1f*zy*ma; z.z+=0.1f*zz2*ma; aux.DE*=fabs(mf)*1.1f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_118)
					case 118: { float ns=native_sin(zx*ma+i*mb)*native_cos(zy*mc); z.x+=ns*0.1f*md; z.y+=ns*0.1f*md; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_119)
					case 119: { float jv=native_sin(i*ma)*native_cos(i*mb); float sc=mf+0.1f*jv; z*=sc; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_120)
					case 120: { float sc1=ma,sc2=mb; z*=sc1; float rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2>1e-21f){ z*=sc2/native_sqrt(rr2); } aux.DE*=fmax(fabs(sc1),fabs(sc2)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_121)
					case 121: { float h=((native_sin(i*12.9898f+78.233f)*43758.5453f) - native_floor(native_sin(i*12.9898f+78.233f)*43758.5453f)); float w=(h<ma)?mb:mc; z.x+=w*0.1f; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_122)
					case 122: { float h=((native_sin(i*12.9898f+zx*78.233f)*43758.5453f) - native_floor(native_sin(i*12.9898f+zx*78.233f)*43758.5453f)); float sc=ma+h*mb*0.1f; z*=sc; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_123)
					case 123: { float p=ma; z.x=fmod(zx+p*0.5f,p)-p*0.5f; z.y=fmod(zy+p*0.5f,p)-p*0.5f; z.z=fmod(zz2+p*0.5f,p)-p*0.5f; aux.DE*=fabs(mf)/fmax(0.01f,p); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_124)
					case 124: { float fR2=ma; if(rr<fR2){ float m2=fR2/fmax(1e-21f,rr); z*=m2; aux.DE*=m2; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_125)
					case 125: { if(fabs(zx)>ma) z.x=copysign(ma,zx); if(fabs(zy)>ma) z.y=copysign(ma,zy); if(fabs(zz2)>ma) z.z=copysign(ma,zz2); aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_126)
					case 126: { float dx=fabs(z.x-zx),dy=fabs(z.y-zy),dz=fabs(z.z-zz2); aux.color+=ma*dx+mb*dy+mc*dz; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_127)
					case 127: { float mR2=ma,fR2=mb; float t=(rr-mR2)/(fR2-mR2+1e-21f); t=fmax(0.0f,fmin(1.0f,t)); aux.color+=t*mc; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_128)
					case 128: { aux.color+=native_log(fabs(mf)+1e-21f)*ma; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_129)
					case 129: { float th=atan2(zy,zx); aux.color+=fabs(th)*ma; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_130)
					case 130: { float td=native_sqrt((zx-ma)*(zx-ma)+(zy-mb)*(zy-mb)+(zz2-mc)*(zz2-mc))-md; aux.color+=fmax(0.0f,1.0f-fabs(td))*me; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_131)
					case 131: { float ax1=ma,ay1=mb,bx1=mc,by1=md; float dx=bx1-ax1,dy=by1-ay1; float t=((zx-ax1)*dx+(zy-ay1)*dy)/(dx*dx+dy*dy+1e-21f); t=fmax(0.0f,fmin(1.0f,t)); float px=ax1+t*dx,py=ay1+t*dy; float dd=native_sqrt((zx-px)*(zx-px)+(zy-py)*(zy-py)); aux.color+=fmax(0.0f,1.0f-dd)*me; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_132)
					case 132: { float dd=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.color+=fmax(0.0f,1.0f-dd*ma)*mb; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_133)
					case 133: { float nx=ma,ny=mb,nz2=mc; float nm=native_sqrt(nx*nx+ny*ny+nz2*nz2+1e-21f); float dd=fabs(zx*nx/nm+zy*ny/nm+zz2*nz2/nm-md); aux.color+=fmax(0.0f,1.0f-dd)*me; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_134)
					case 134: { float R=ma,rr2=mb; float rxy=native_sqrt(zx*zx+zy*zy+1e-21f); float td=(rxy-R)*(rxy-R)+zz2*zz2-rr2*rr2; aux.color+=fmax(0.0f,1.0f-fabs(td))*mc; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_135)
					case 135: { float jv=native_sin(zx*ma)*native_sin(zy*mb); aux.color+=fabs(jv)*mc; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_136)
					case 136: { aux.color+=(float)i/fmax(1.0f,ma)*mb; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_137)
					case 137: { aux.color+=native_log(fmax(1e-21f,aux.DE))*ma; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_138)
					case 138: { float spd=native_sqrt((z.x-zx)*(z.x-zx)+(z.y-zy)*(z.y-zy)+(z.z-zz2)*(z.z-zz2)); aux.color+=spd*ma; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_139)
					case 139: { aux.color+=r*ma*0.01f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_140)
					case 140: { float th=atan2(zy,zx); aux.color+=th*ma; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_141)
					case 141: { aux.color+=r*ma; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_142)
					case 142: { float p=fmax(0.01f,ma); float cx2=native_floor(zx/p),cy2=native_floor(zy/p),cz2=native_floor(zz2/p); float h=((native_sin(cx2*12.9898f+cy2*78.233f+cz2*37.719f)*43758.5453f) - native_floor(native_sin(cx2*12.9898f+cy2*78.233f+cz2*37.719f)*43758.5453f)); aux.color+=h*mb; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_143)
					case 143: { aux.color+=native_sin(i*ma+mb)*mc; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_144)
					case 144: { aux.color=0.9f*aux.color+0.1f*ma*r; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_145)
					case 145: { float ns=native_sin(zx*ma+zy*mb+zz2*mc)*md; aux.color+=ns; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_146)
					case 146: { float cl=length(pointTransformed); aux.color+=cl*ma; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_147)
					case 147: { aux.color+=native_sqrt(zx*zx+zy*zy)*ma; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_148)
					case 148: { float fc=fabs(z.x-zx)*0.3f+r*0.3f+fabs(atan2(zy,zx))*0.4f; aux.color+=fc*ma; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_149)
					case 149: { float ns=native_sin(zx*ma+zy*mb)*native_cos(zz2*mc+i*md); aux.color+=fabs(ns)*me; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_150)
					case 150: { float jv=native_sin(zx*ma)*native_sin(zy*mb)*native_sin(zz2*mc); aux.color+=fabs(jv)*md; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_151)
					case 151: { float eps=ma*0.001f; float dx=(native_sqrt((zx+eps)*(zx+eps)+zy*zy+zz2*zz2)-native_sqrt((zx-eps)*(zx-eps)+zy*zy+zz2*zz2))/(2.0f*eps); aux.DE=fmax(1e-21f,fabs(dx)*aux.DE); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_152)
					case 152: { float de_num=r*0.5f; float de_safe=fmin(aux.DE,de_num); aux.DE=de_safe; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_153)
					case 153: { aux.DE=0.9f*aux.DE+0.1f*r*ma; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_154)
					case 154: { float prev=aux.DE; aux.DE=prev+0.5f*(prev-ma); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_155)
					case 155: { float spd=r*0.01f; aux.DE=aux.DE*(1.0f+0.5f*spd); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_156)
					case 156: { float tr=ma; aux.DE=fmin(aux.DE,tr); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_157)
					case 157: { float j11=1.0f+ma*native_cos(zx),j22=1.0f+mb*native_cos(zy),j33=1.0f+mc*native_cos(zz2); aux.DE*=fmax(fabs(j11),fmax(fabs(j22),fabs(j33))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_158)
					case 158: { float h=ma*native_sin(zx)*native_sin(zy)*native_sin(zz2); aux.DE*=(1.0f+h*0.5f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_159)
					case 159: { aux.DE=native_log(fmax(1e-21f,aux.DE))*ma+mb; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_160)
					case 160: { aux.DE=(native_exp(fmin(10.0f,aux.DE))-1.0f)*ma; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_161)
					case 161: { float p=ma; aux.DE=native_pow(fmax(1e-21f,aux.DE),p); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_162)
					case 162: { float k=ma,de0=mb; aux.DE=1.0f/(1.0f+native_exp(-k*(aux.DE-de0))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_163)
					case 163: { float de0=ma,sg=mb; aux.DE=native_exp(-(aux.DE-de0)*(aux.DE-de0)/(sg*sg+1e-21f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_164)
					case 164: { float th2=ma; aux.DE=(aux.DE>th2)?mb:mc; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_165)
					case 165: { float b1=ma,d1=mb,b2=mc,d2=md; aux.DE=(aux.DE<b1)?d1:((aux.DE<b2)?d2:aux.DE); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_166)
					case 166: { float ns=native_sin(zx*ma+zy*mb+zz2*mc)*md; aux.DE+=ns; aux.DE=fmax(1e-21f,aux.DE); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_167)
					case 167: { float jv=fabs(native_sin(zx*ma)*native_sin(zy*mb)); aux.DE*=(1.0f+0.1f*jv); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_168)
					case 168: { aux.DE*=(1.0f+0.1f*native_sin(i*ma)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_169)
					case 169: { aux.DE=0.9f*aux.DE+0.1f*ma; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_170)
					case 170: { float ns=native_sin(zx*ma+zy*mb)*native_cos(zz2*mc+i*md); aux.DE*=(1.0f+me*ns); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_171)
					case 171: { float fn=native_sin(zx*ma*10.0f)*native_sin(zy*mb*10.0f)*native_sin(zz2*mc*10.0f); aux.DE*=(1.0f+0.1f*fn); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_172)
					case 172: { float spd=r*0.01f; aux.DE/=(1.0f+spd); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_173)
					case 173: { aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_174)
					case 174: { if(fabs(zx)>ma) z.x=copysign(ma*2.0f,zx)-zx; float rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb*mb) z*=mc*mc/(rr2+1e-21f); aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_175)
					case 175: { float sc=ma+mb*native_sin(i*mc); z*=sc; if(fabs(z.x)>md) z.x=copysign(md*2.0f,z.x)-z.x; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_176)
					case 176: { float th=ma*M_PI_F/180.0f; float cs=native_cos(th),sn=native_sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; if(fabs(z.x)>mb) z.x=copysign(mb*2.0f,z.x)-z.x; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_177)
					case 177: { if(fabs(zx)>ma) z.x=copysign(ma*2.0f,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0f,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0f,zz2)-zz2; float rr2=z.x*z.x+z.y*z.y+z.z*z.z; float fR2=mb; if(rr2<mc) z*=fR2/mc; else if(rr2<fR2) z*=fR2/rr2; z*=md; z.x+=me; z.y+=mff; z.z+=mg; aux.DE*=fabs(md); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_178)
					case 178: { float th=i*2.39996322973f; float cs=native_cos(th),sn=native_sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; if(fabs(z.x)>ma) z.x=copysign(ma*2.0f,z.x)-z.x; z*=mb; aux.DE*=fabs(mb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_179)
					case 179: { float rxy=native_sqrt(zx*zx+zy*zy); if(rxy>ma){ float th=atan2(zy,zx); z.x=(ma*2.0f-rxy)*native_cos(th); z.y=(ma*2.0f-rxy)*native_sin(th); } float rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb) z*=mc/rr2; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_180)
					case 180: { z.x+=ma*native_sin(mb*zy); z.y+=mc*native_sin(md*zz2); z.z+=me*native_sin(mff*zx); aux.DE*=fabs(mf)*(1.0f+fabs(ma*mb)+fabs(mc*md)+fabs(me*mff)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_181)
					case 181: { if(fabs(zx)>ma) z.x=copysign(ma*2.0f,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0f,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0f,zz2)-zz2; aux.color+=mb*fabs(z.x-zx); aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_182)
					case 182: { float rr2=rr; float mR2=ma*ma; float fR2=mb*mb; if(rr2<mR2){ z*=fR2/mR2; aux.DE*=fR2/mR2; } else if(rr2<fR2){ z*=fR2/rr2; aux.DE*=fR2/rr2; } aux.color+=mc*native_log(fmax(1e-21f,rr2/(mR2+1e-21f))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_183)
					case 183: { float sc=ma; z*=sc; aux.DE*=fabs(sc); z.x+=mb; z.y+=mc; z.z+=md; float th=me*M_PI_F/180.0f; float cs=native_cos(th),sn=native_sin(th); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_184)
					case 184: { float lt=ma*(1.0f+mb*r/fmax(1e-10f,native_sqrt(rr))); if(fabs(zx)>lt) z.x=copysign(lt*2.0f,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0f,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0f,zz2)-zz2; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_185)
					case 185: { float mR2=ma*ma; float fR2=mb*mb; float sm=mc; float t=1.0f/(1.0f+native_exp(-sm*(rr-mR2))); float m2=fR2/fmax(1e-21f,rr); float sf=(1.0f-t)*m2+t; z*=sf; aux.DE*=sf; z*=md; z.x+=me; aux.DE*=fabs(md); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_186)
					case 186: { float N=fmax(2.0f,ma); float th=atan2(zy,zx); float sector=2.0f*M_PI_F/N; th=fmod(th+sector*0.5f+100.0f*sector,sector)-sector*0.5f; float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(th); z.y=rxy*native_sin(th); if(fabs(z.x)>mb) z.x=copysign(mb*2.0f,z.x)-z.x; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_187)
					case 187: { z.x=fabs(zx); z.y=fabs(zy); z.z=fabs(zz2); if(fabs(z.x)>ma) z.x=ma*2.0f-z.x; if(fabs(z.y)>ma) z.y=ma*2.0f-z.y; if(fabs(z.z)>ma) z.z=ma*2.0f-z.z; aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_188)
					case 188: { if(fabs(zx)>ma) z.x=copysign(ma*2.0f,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0f,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0f,zz2)-zz2; float rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb) z*=mc/rr2; else if(rr2<mc) z*=mc/rr2; float th=md*M_PI_F/180.0f; float cs=native_cos(th),sn=native_sin(th); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; z*=me; z.x+=mff; aux.DE*=fabs(me); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_189)
					case 189: { float rxy=native_sqrt(zx*zx+zy*zy); float th=atan2(zy,zx)+ma*native_sin(mb*zz2); z.x=rxy*native_cos(th); z.y=rxy*native_sin(th); if(fabs(z.x)>mc) z.x=copysign(mc*2.0f,z.x)-z.x; aux.DE*=fabs(mf)*(1.0f+fabs(ma*mb)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_190)
					case 190: { float pw=ma; float rp=native_pow(fmax(1e-10f,r),pw-1.0f); float th=atan2(zy,zx)*pw; float ph=native_asin(zz2/fmax(1e-10f,r))*pw; z.x=rp*native_cos(ph)*native_cos(th); z.y=rp*native_cos(ph)*native_sin(th); z.z=rp*native_sin(ph); aux.DE*=pw*rp; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_191)
					case 191: { z.x+=ma*native_sin(mb*i)*native_cos(mc*zy); z.y+=md*native_cos(me*i)*native_sin(mff*zx); z.z+=mg*native_sin(mh*i); aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_192)
					case 192: { float sc=mf; z*=sc; float lt=ma; if(fabs(z.x)>lt) z.x=copysign(lt*2.0f,z.x)-z.x; if(fabs(z.y)>lt) z.y=copysign(lt*2.0f,z.y)-z.y; if(fabs(z.z)>lt) z.z=copysign(lt*2.0f,z.z)-z.z; float rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb) z*=mc/rr2; aux.DE*=fabs(sc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_193)
					case 193: { float p=fmax(0.01f,ma); z.x=fmod(zx+p*0.5f,p)-p*0.5f; z.y=fmod(zy+p*0.5f,p)-p*0.5f; z.z=fmod(zz2+p*0.5f,p)-p*0.5f; if(fabs(z.x)>mb) z.x=copysign(mb*2.0f,z.x)-z.x; aux.DE*=fabs(mf)/fmax(0.01f,p); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_194)
					case 194: { float ex=native_exp(-ma*rr); z*=(1.0f+mb*ex); aux.DE*=(1.0f+mb*ex); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_195)
					case 195: { float sg=1.0f/(1.0f+native_exp(-ma*(r-mb))); z*=(1.0f+mc*sg); aux.DE*=(1.0f+mc*sg); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_196)
					case 196: { z.x+=ma*native_sin(mb*zx)*native_cos(mc*zy); z.y+=md*native_cos(me*zy)*native_sin(mff*zz2); z.z+=mg*native_sin(mh*zz2)*native_cos(ma*zx); aux.DE*=fabs(mf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_197)
					case 197: { float th1=ma*M_PI_F/180.0f+mb*native_sin(i*mc); float cs1=native_cos(th1),sn1=native_sin(th1); z.x=zx*cs1-zy*sn1; z.y=zx*sn1+zy*cs1; if(fabs(z.x)>md) z.x=copysign(md*2.0f,z.x)-z.x; z*=me; aux.DE*=fabs(me); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_198)
					case 198: { float rr2=rr; float fR2=ma*ma; if(rr2<fR2){ float m2=fR2/fmax(1e-21f,rr2); z*=m2; aux.DE*=m2; } float th=mb*M_PI_F/180.0f; float cs=native_cos(th),sn=native_sin(th); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; z*=mc; z.x+=md; aux.DE*=fabs(mc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_199)
					case 199: { float lt=ma+mb*native_sin(mc*i)*native_cos(md*r); if(fabs(zx)>lt) z.x=copysign(lt*2.0f,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0f,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0f,zz2)-zz2; float rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<me*me) z*=mff*mff/(rr2+1e-21f); z*=mg; aux.DE*=fabs(mg); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MBMATHTYPE_200)
					case 200: { if(fabs(zx)>ma) z.x=copysign(ma*2.0f,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0f,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0f,zz2)-zz2; float rr2=z.x*z.x+z.y*z.y+z.z*z.z; float fR2=mb*mb; float mR2=mc*mc; if(rr2<mR2) z*=fR2/mR2; else if(rr2<fR2) z*=fR2/rr2; z*=md; z.x+=me; z.y+=mff; z.z+=mg; float th=mh*M_PI_F/180.0f; float cs=native_cos(th),sn=native_sin(th); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; aux.DE*=fabs(md); break; }
#endif

					default: break;
#endif
			}
			}

				// v7.9 — Warp Distortion system (per-section iteration range)
				if (i >= mut->wdIterStart && i < mut->wdIterStop && mut->warpDistType != 0)
				{
					float wf = mut->wdFactor * mut->warpDistWeight * mut->masterWeight;
					float wa = mut->wdParamA, wb = mut->wdParamB, wc = mut->wdParamC, wd = mut->wdParamD;
					float wfq = mut->wdFreq, wam = mut->wdAmp;
					float wsc = mut->wdScale, wph = mut->wdPhase * M_PI_F / 180.0;
					float zx = z.x, zy = z.y, zz2 = z.z;
					float r = native_sqrt(zx*zx + zy*zy + zz2*zz2 + 1e-21);
					switch(mut->warpDistType)
					{
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_1)
						case 1: { z.x += wf*wam*native_sin(wfq*zy + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq*native_cos(wfq*zy + wph))); break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_2)
						case 2: { z.y += wf*wam*native_sin(wfq*zz2 + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq*native_cos(wfq*zz2 + wph))); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_3)
						case 3: { z.z += wf*wam*native_sin(wfq*zx + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq*native_cos(wfq*zx + wph))); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_4)
						case 4: { z.x += wf*wam*native_sin(wfq*zy + wph); z.y += wf*wam*native_sin(wfq*zz2 + wph); z.z += wf*wam*native_sin(wfq*zx + wph); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_5)
						case 5: { z.x += wf*wam*native_cos(wfq*zy + wph)*native_sin(wfq*zz2); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_6)
						case 6: { float ph = atan2(zy, zx); z.x += wf*wam*native_sin(wfq*ph + wph); z.y += wf*wam*native_cos(wfq*ph + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_7)
						case 7: { float ph = atan2(zy, zx), th = acos(zz2/r); z.x += wf*wam*native_sin(wfq*th + wph)*native_cos(ph); z.y += wf*wam*native_sin(wfq*th + wph)*native_sin(ph); z.z += wf*wam*native_cos(wfq*th + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_8)
						case 8: { z.x += wf*wam*native_sin(wfq*zy + wph)*native_cos(wfq*zz2); z.y += wf*wam*native_sin(wfq*zz2 + wph)*native_cos(wfq*zx); z.z += wf*wam*native_sin(wfq*zx + wph)*native_cos(wfq*zy); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_9)
						case 9: { z.x += wf*wam*native_sin(wfq*zx + wph); z.y += wf*wb*native_sin(wfq*zy + wph); z.z += wf*wc*native_sin(wfq*zz2 + wph); aux.DE *= (1.0 + fabs(wf*(wam+wb+wc)*wfq/3.0)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_10)
						case 10: { float d = wf*wam*native_sin(wfq*r + wph); z.x += d*zx/r; z.y += d*zy/r; z.z += d*zz2/r; aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_11)
						case 11: { z.x += wf*wam*native_sin(wfq*native_sin(wa*zy) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_12)
						case 12: { z.y += wf*wam*native_sin(wfq*native_cos(wa*zz2) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_13)
						case 13: { z.z += wf*wam*native_cos(wfq*native_sin(wa*zx) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_14)
						case 14: { float d1 = native_sin(wfq*zx+wph), d2 = native_sin(wa*zy+wb); z.x += wf*wam*native_sin(wfq*d1+d2); z.y += wf*wam*native_cos(wa*d1-d2); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_15)
						case 15: { z.x += wf*wam*native_sin(wfq*(zx*zy) + wph); z.y += wf*wam*native_cos(wfq*(zy*zz2) + wph); z.z += wf*wam*native_sin(wfq*(zz2*zx) + wph); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_16)
						case 16: { float n1 = native_sin(wfq*zx+wa*zy), n2 = native_sin(wa*zy+wb*zz2); z.x += wf*wam*native_sin(wfq*n1+wph); z.y += wf*wam*native_sin(wfq*n2+wph); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_17)
						case 17: { float n1 = native_cos(wfq*zx)*native_sin(wa*zy), n2 = native_cos(wa*zy)*native_sin(wb*zz2), n3 = native_cos(wb*zz2)*native_sin(wfq*zx); z.x += wf*wam*n1; z.y += wf*wam*n2; z.z += wf*wam*n3; aux.DE *= (1.0 + 3.0*fabs(wf*wam)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_18)
						case 18: { z.x += wf*wam*native_sin(wfq*zy*zz2/(r+1e-21) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_19)
						case 19: { float t = wfq*r+wph; z.x += wf*wam*native_sin(t)*native_cos(wa*zy); z.y += wf*wam*native_cos(t)*native_sin(wa*zz2); z.z += wf*wam*native_sin(t)*native_cos(wa*zx); aux.DE *= (1.0 + 3.0*fabs(wf*wam)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_20)
						case 20: { float q = native_sin(wfq*zx+wph)+native_sin(wa*zy+wb)+native_sin(wc*zz2+wd); z.x += wf*wam*native_sin(q); z.y += wf*wam*native_cos(q); z.z += wf*wam*native_sin(q+M_PI_F*0.5); aux.DE *= (1.0 + 3.0*fabs(wf*wam)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_21)
						case 21: { { float v=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o); v+=native_sin(f*zx+wph)*native_cos(f*zy)/pow(2.0,o);} z.x+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_22)
						case 22: { { float v=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o); v+=native_sin(f*zy+wph)*native_cos(f*zz2)/pow(2.0,o);} z.y+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_23)
						case 23: { { float v=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o); v+=native_sin(f*zz2+wph)*native_cos(f*zx)/pow(2.0,o);} z.z+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_24)
						case 24: { { float vx=0,vy=0,vz=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o), a=1.0/pow(2.0,o); vx+=native_sin(f*zy+wph)*a; vy+=native_sin(f*zz2+wph)*a; vz+=native_sin(f*zx+wph)*a;} z.x+=wf*wam*vx; z.y+=wf*wam*vy; z.z+=wf*wam*vz; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq*4.0)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_25)
						case 25: { { float vx=0,vy=0,vz=0; for(int o=0;o<(int)(wa);o++){float f=wfq*pow(wb,o), a=1.0/pow(wb,o); vx+=native_sin(f*zy+o*wph)*a; vy+=native_sin(f*zz2+o*wph)*a; vz+=native_sin(f*zx+o*wph)*a;} z.x+=wf*wam*vx; z.y+=wf*wam*vy; z.z+=wf*wam*vz; aux.DE*=(1.0+3.0*fabs(wf*wam)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_26)
						case 26: { { float v=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o); v+=fabs(native_sin(f*zx+wph))*native_cos(f*zy)/pow(2.0,o);} z.x+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_27)
						case 27: { { float vx=0,vy=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o); vx+=native_sin(f*zy+wph)*native_cos(f*zz2)/pow(2.0,o); vy+=native_cos(f*zx+wph)*native_sin(f*zz2)/pow(2.0,o);} z.x+=wf*wam*vx; z.y+=wf*wam*vy; aux.DE*=(1.0+2.0*fabs(wf*wam*wfq*4.0)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_28)
						case 28: { { float v=0; for(int o=0;o<6;o++){float f=wfq*pow(2.0,o); v+=native_sin(f*r+wph)/pow(2.0,o);} float d=wf*wam*v; z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0+fabs(wf*wam*wfq*6.0)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_29)
						case 29: { { float vx=0,vy=0,vz=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o), p=wph+o*M_PI_F*0.25; vx+=native_sin(f*zy+p)*native_cos(f*zz2+p)/pow(2.0,o); vy+=native_sin(f*zz2+p)*native_cos(f*zx+p)/pow(2.0,o); vz+=native_sin(f*zx+p)*native_cos(f*zy+p)/pow(2.0,o);} z.x+=wf*wam*vx; z.y+=wf*wam*vy; z.z+=wf*wam*vz; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq*4.0)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_30)
						case 30: { { float ph2=atan2(zy,zx), th=acos(zz2/r), v=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o); v+=native_sin(f*th+wph)*native_cos(f*ph2)/pow(2.0,o);} float d=wf*wam*v; z.x+=d*native_sin(th)*native_cos(ph2); z.y+=d*native_sin(th)*native_sin(ph2); z.z+=d*native_cos(th); aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_31)
						case 31: { z.x += wf*wam*(native_cos(wfq*zy+wph)-native_cos(wfq*zz2+wph)); z.y += wf*wam*(native_cos(wfq*zz2+wph)-native_cos(wfq*zx+wph)); z.z += wf*wam*(native_cos(wfq*zx+wph)-native_cos(wfq*zy+wph)); aux.DE *= (1.0f + 3.0f*fabs(wf*wam*wfq)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_32)
						case 32: { { float cx=-wfq*native_cos(wfq*zy+wph); float cy=-wfq*native_cos(wfq*zz2+wph); float cz=-wfq*native_cos(wfq*zx+wph); z.x+=wf*wam*(cy-cz); z.y+=wf*wam*(cz-cx); z.z+=wf*wam*(cx-cy); aux.DE*=(1.0f+3.0f*fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_33)
						case 33: { z.x += wf*wam*native_sin(wfq*zy+wph)*native_sin(wa*zz2); z.y += -wf*wam*native_sin(wfq*zx+wph)*native_sin(wa*zz2); aux.DE *= (1.0f + 2.0f*fabs(wf*wam*wfq)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_34)
						case 34: { z.x += wf*wam*native_sin(wfq*zz2+wph); z.z += -wf*wam*native_sin(wfq*zx+wph); aux.DE *= (1.0f + 2.0f*fabs(wf*wam*wfq)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_35)
						case 35: { z.y += wf*wam*native_sin(wfq*zx+wph); z.x += -wf*wam*native_sin(wfq*zy+wph); aux.DE *= (1.0f + 2.0f*fabs(wf*wam*wfq)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_36)
						case 36: { { float dx=wf*wam*wfq*native_cos(wfq*zy+wph); float dy=wf*wam*wa*native_cos(wa*zz2+wph); float dz=wf*wam*wfq*native_cos(wfq*zx+wph); z.x+=dy-dz; z.y+=dz-dx; z.z+=dx-dy; aux.DE*=(1.0f+3.0f*fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_37)
						case 37: { { float psi=wf*wam*native_sin(wfq*zx+wph)*native_cos(wa*zy)*native_sin(wb*zz2); z.x+=wf*wam*wa*native_sin(wfq*zx)*native_cos(wa*zy); z.y+=-wf*wam*wfq*native_cos(wfq*zx)*native_sin(wa*zy); aux.DE*=(1.0f+2.0f*fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_38)
						case 38: { { float u=wf*wam*native_sin(wfq*r+wph); z.x+=u*(-zy/r); z.y+=u*(zx/r); aux.DE*=(1.0f+fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_39)
						case 39: { { float u=wf*wam*native_sin(wfq*zz2+wph); z.x+=u*(-zy/(native_sqrt(zx*zx+zy*zy)+1e-21f)); z.y+=u*(zx/(native_sqrt(zx*zx+zy*zy)+1e-21f)); aux.DE*=(1.0f+fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_40)
						case 40: { { float ph2=atan2(zy,zx); float u=wf*wam*native_sin(wfq*ph2+wph); z.z+=u; aux.DE*=(1.0f+fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_41)
						case 41: { { float th=wf*wfq*zz2+wph; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0f+fabs(wf*wfq*wam)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_42)
						case 42: { { float th=wf*wfq*zx+wph; float cs=native_cos(th),sn=native_sin(th); float ny=zy*cs-zz2*sn; z.z=zy*sn+zz2*cs; z.y=ny; aux.DE*=(1.0f+fabs(wf*wfq*wam)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_43)
						case 43: { { float th=wf*wfq*zy+wph; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zz2*sn; z.z=zx*sn+zz2*cs; z.x=nx; aux.DE*=(1.0f+fabs(wf*wfq*wam)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_44)
						case 44: { { float th=wf*wfq*r+wph; float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0f+fabs(wf*wfq*wam)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_45)
						case 45: { { float a1=wf*wa*native_sin(wfq*zz2+wph); float cs=native_cos(a1),sn=native_sin(a1); float nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; float a2=wf*wb*native_sin(wfq*zx+wph); cs=native_cos(a2); sn=native_sin(a2); float ny=zy*cs-zz2*sn; z.z=zy*sn+zz2*cs; z.y=ny; aux.DE*=(1.0f+fabs(wf*(wa+wb)*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_46)
						case 46: { { float ph2=atan2(zy,zx)+wf*wam*native_sin(wfq*zz2+wph); float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(ph2); z.y=rxy*native_sin(ph2); aux.DE*=(1.0f+fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_47)
						case 47: { { float th=native_acos(zz2/r)+wf*wam*native_sin(wfq*r+wph); float ph2=atan2(zy,zx); z.x=r*native_sin(th)*native_cos(ph2); z.y=r*native_sin(th)*native_sin(ph2); z.z=r*native_cos(th); aux.DE*=(1.0f+fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_48)
						case 48: { { float a=wf*wam*zz2*wfq; float cs=native_cos(a),sn=native_sin(a); float nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; z.z+=wf*wb*native_sin(wfq*r+wph); aux.DE*=(1.0f+fabs(wf*(wam+wb)*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_49)
						case 49: { { float a=wf*wam*native_sin(wfq*zz2+wph); z.x=zx*native_cos(a)-zy*native_sin(a)+wf*wb*native_sin(wfq*zy); z.y=zx*native_sin(a)+zy*native_cos(a)+wf*wc*native_cos(wfq*zz2); z.z+=wf*wd*native_sin(wfq*zx+wph); aux.DE*=(1.0f+fabs(wf*(wam+wb+wc+wd)*wfq/4.0f)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_50)
						case 50: { { float t=wf*wfq*native_log(r+1e-21f)+wph; float cs=native_cos(t),sn=native_sin(t); float nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0f+fabs(wf*wfq/(r+1e-21f))); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_51)
						case 51: { { float d=wf*wam*native_sin(wfq*r+wph); z*=(1.0f+d/r); aux.DE*=(1.0f+fabs(d/r)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_52)
						case 52: { { float d=wf*wam/(1.0f+native_exp(-wfq*(r-wa))); z*=(1.0f+d); aux.DE*=(1.0f+fabs(d)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_53)
						case 53: { { float d=wf*wam*native_exp(-wfq*r*r); z*=(1.0f+d); aux.DE*=(1.0f+fabs(d)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_54)
						case 54: { { float d=wf*wam*native_exp(-wfq*fabs(r-wa)); z*=(1.0f+d); aux.DE*=(1.0f+fabs(d)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_55)
						case 55: { { float d=wf*wam*(native_sin(wfq*r+wph)+native_sin(wa*r+wb))*0.5f; z*=(1.0f+d/r); aux.DE*=(1.0f+fabs(d/r)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_56)
						case 56: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21f); float d=wf*wam*native_sin(wfq*rxy+wph); z.x+=d*zx/rxy; z.y+=d*zy/rxy; aux.DE*=(1.0f+fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_57)
						case 57: { { float d=wf*wam*native_sin(wfq*zz2+wph)*native_exp(-wa*native_sqrt(zx*zx+zy*zy)); z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0f+fabs(d)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_58)
						case 58: { { float ph2=atan2(zy,zx); float th=native_acos(zz2/r); float d=wf*wam*native_sin(wfq*ph2*wa+wph)*native_sin(wb*th); z.x+=d*native_sin(th)*native_cos(ph2); z.y+=d*native_sin(th)*native_sin(ph2); z.z+=d*native_cos(th); aux.DE*=(1.0f+fabs(wf*wam)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_59)
						case 59: { { float nr=r+wf*wam*native_sin(wfq*r+wph); z*=(nr/r); aux.DE*=(nr/r); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_60)
						case 60: { { float f2=1.0f+wf*wam*native_sin(wfq*r+wph)/(r+1e-21f); z*=f2; aux.DE*=fabs(f2); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_61)
						case 61: { z.x += wf*wam*native_sin(wfq*native_floor(zy*wa)/wa + wph); aux.DE *= (1.0f + fabs(wf*wam*wfq)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_62)
						case 62: { z.y += wf*wam*native_sin(wfq*native_floor(zz2*wa)/wa + wph); aux.DE *= (1.0f + fabs(wf*wam*wfq)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_63)
						case 63: { z.z += wf*wam*native_sin(wfq*native_floor(zx*wa)/wa + wph); aux.DE *= (1.0f + fabs(wf*wam*wfq)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_64)
						case 64: { { float gx=native_floor(zx*wa+0.5f)/wa; float gy=native_floor(zy*wa+0.5f)/wa; z.x+=wf*wam*native_sin(wfq*gy+wph); z.y+=wf*wam*native_cos(wfq*gx+wph); aux.DE*=(1.0f+2.0f*fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_65)
						case 65: { { float fx=zx-native_floor(zx*wa)/wa; float fy=zy-native_floor(zy*wa)/wa; z.x+=wf*wam*native_sin(wfq*fx*M_PI_F*2.0f+wph); z.y+=wf*wam*native_sin(wfq*fy*M_PI_F*2.0f+wph); aux.DE*=(1.0f+2.0f*fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_66)
						case 66: { { float d=zx*wa-native_floor(zx*wa+0.5f); z.x+=wf*wam*d*native_sin(wfq*zy+wph); aux.DE*=(1.0f+fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_67)
						case 67: { { float d=native_sin(wfq*zx+wph)*native_sin(wa*zy+wb)*native_sin(wc*zz2+wd); z.x+=wf*wam*d; z.y+=wf*wam*d; z.z+=wf*wam*d; aux.DE*=(1.0f+3.0f*fabs(wf*wam)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_68)
						case 68: { { float d=wf*wam*native_sin(wfq*(zx+zy+zz2)+wph); z.x+=d; z.y+=d; z.z+=d; aux.DE*=(1.0f+3.0f*fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_69)
						case 69: { { float d=wf*wam*native_sin(wfq*(zx*zy+zy*zz2+zz2*zx)/(r*r+1e-21f)+wph); z.x+=d; z.y+=d; z.z+=d; aux.DE*=(1.0f+3.0f*fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_70)
						case 70: { { float v=wf*wam*native_cos(wfq*zx+wph)*native_cos(wa*zy+wb)*native_cos(wc*zz2+wd); z.x+=v*native_sin(wfq*zy); z.y+=v*native_sin(wa*zz2); z.z+=v*native_sin(wc*zx); aux.DE*=(1.0f+3.0f*fabs(wf*wam)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_71)
						case 71: { { float d=wf*wam*native_exp(-wfq*(zx*zx+zy*zy)); z.z+=d; aux.DE*=(1.0f+fabs(d)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_72)
						case 72: { { float d=wf*wam*native_exp(-wfq*r)*native_sin(wa*r+wph); z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0f+fabs(d)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_73)
						case 73: { { float d=wf*wam*native_exp(-wfq*fabs(zz2))*native_sin(wa*native_sqrt(zx*zx+zy*zy)+wph); z.z+=d; aux.DE*=(1.0f+fabs(d)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_74)
						case 74: { { float d=wf*wam/(1.0f+wfq*(zx*zx+zy*zy+zz2*zz2)); z.x+=d*native_sin(wa*zy+wph); z.y+=d*native_cos(wa*zz2+wph); aux.DE*=(1.0f+2.0f*fabs(d*wa)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_75)
						case 75: { { z *= (1.0f + wf*wam*native_pow(fabs(native_sin(wfq*r+wph)), wa)); aux.DE *= (1.0f + fabs(wf*wam)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_76)
						case 76: { { float p=wf*wam*native_pow(r+1e-21f, wa-1.0f)*native_sin(wfq*r+wph); z.x+=p*zx; z.y+=p*zy; z.z+=p*zz2; aux.DE*=(1.0f+fabs(p*r)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_77)
						case 77: { { float d=wf*wam*tanh(wfq*(r-wa)); z*=(1.0f+d); aux.DE*=(1.0f+fabs(d)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_78)
						case 78: { { float d=wf*wam*native_log(1.0f+wfq*r)*native_sin(wa*r+wph)/(r+1e-21f); z.x+=d*zx; z.y+=d*zy; z.z+=d*zz2; aux.DE*=(1.0f+fabs(d*r)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_79)
						case 79: { { float d=wf*wam*native_sin(wfq*native_log(r+1e-21f)+wph); z*=(1.0f+d/r); aux.DE*=(1.0f+fabs(d/r)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_80)
						case 80: { { float sg=1.0f/(1.0f+native_exp(-wfq*(r-wa))); z*=(1.0f+wf*wam*(2.0f*sg-1.0f)); aux.DE*=(1.0f+fabs(wf*wam*(2.0f*sg-1.0f))); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_81)
						case 81: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21f); float d=wf*wam*native_sin(wfq*rxy+wph); z.z+=d; aux.DE*=(1.0f+fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_82)
						case 82: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21f); float d=wf*wam*native_sin(wfq*zz2+wph); z.x+=d*zx/rxy; z.y+=d*zy/rxy; aux.DE*=(1.0f+fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_83)
						case 83: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21f); float rt=rxy-wa; float dt=native_sqrt(rt*rt+zz2*zz2); float d=wf*wam*native_sin(wfq*dt+wph); z.x+=d*(rt/dt)*(zx/rxy); z.y+=d*(rt/dt)*(zy/rxy); z.z+=d*(zz2/dt); aux.DE*=(1.0f+fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_84)
						case 84: { { float ph2=atan2(zy,zx); float d=wf*wam*native_sin(wfq*ph2*wa+wph); z.z+=d; aux.DE*=(1.0f+fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_85)
						case 85: { { float ph2=atan2(zy,zx); float rxy=native_sqrt(zx*zx+zy*zy+1e-21f); z.x+=-wf*wam*native_sin(ph2)*native_sin(wfq*zz2+wph); z.y+=wf*wam*native_cos(ph2)*native_sin(wfq*zz2+wph); aux.DE*=(1.0f+fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_86)
						case 86: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21f); float d=wf*wam*native_sin(wfq*rxy+wph)*native_cos(wa*zz2); z.x+=d*zx/rxy; z.y+=d*zy/rxy; z.z+=wf*wam*native_cos(wfq*rxy+wph)*native_sin(wa*zz2); aux.DE*=(1.0f+2.0f*fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_87)
						case 87: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21f); float ph2=atan2(zy,zx)+wf*wam*native_sin(wfq*zz2+wph)/rxy; z.x=rxy*native_cos(ph2); z.y=rxy*native_sin(ph2); aux.DE*=(1.0f+fabs(wf*wam*wfq/rxy)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_88)
						case 88: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21f); float ph2=atan2(zy,zx); float nr=rxy+wf*wam*native_sin(wfq*zz2+wph)*native_sin(wa*ph2); z.x=nr*native_cos(ph2); z.y=nr*native_sin(ph2); aux.DE*=(1.0f+fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_89)
						case 89: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21f); z.z+=wf*wam*native_sin(wfq*rxy+wph)*native_cos(wa*atan2(zy,zx)); aux.DE*=(1.0f+fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_90)
						case 90: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21f); float rt=rxy-wa; float ang=atan2(zz2,rt); float d=wf*wam*native_sin(wfq*ang+wph); z.x+=d*(zx/rxy); z.y+=d*(zy/rxy); aux.DE*=(1.0f+fabs(wf*wam*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_91)
						case 91: { { float a=wf*wa; float b=wf*wb; z.x=zx+a*native_sin(wfq*zy); z.y=zy+b*native_sin(wfq*zx); aux.DE*=(1.0f+fabs((a+b)*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_92)
						case 92: { { float k=wf*wam; z.x=zx+k*zy; z.y=zy+k*native_sin(wfq*zx+wph); aux.DE*=(1.0f+fabs(k*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_93)
						case 93: { { z.x=r*native_cos(wfq*zy/r+wph); z.y=r*native_sin(wfq*zy/r+wph); aux.DE*=(1.0f+fabs(wf*wam*wfq/r)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_94)
						case 94: { { float nr=r+wf*wam*native_sin(wfq*atan2(zy,zx)*wa+wph); z*=(nr/r); aux.DE*=(nr/r); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_95)
						case 95: { { float th=wf*wam/(r*r+1e-10f); float cs=native_cos(th),sn=native_sin(th); float nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0f+fabs(wf*wam*2.0f*r/((r*r+1e-10f)*(r*r+1e-10f)))); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_96)
						case 96: { { float denom=zx*zx+zy*zy+1e-21f; z.x=wf*wam*zx/denom+wsc*native_sin(wfq*zy+wph); z.y=-wf*wam*zy/denom+wsc*native_cos(wfq*zx+wph); aux.DE*=(1.0f+fabs(wf*wam/denom)+fabs(wsc*wfq)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_97)
						case 97: { { float a1=wfq; float a2=wa; z.x=zx*native_cos(a1*zy)-zy*native_sin(a1*zy)+wf*wam*native_sin(a2*zz2+wph); z.y=zx*native_sin(a1*zy)+zy*native_cos(a1*zy)+wf*wam*native_cos(a2*zz2+wph); aux.DE*=(1.0f+fabs(wf*wam*a1)+fabs(wf*wam*a2)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_98)
						case 98: { { float lx=wf*wam*native_sin(wfq*zy+wph)*(1.0f-native_exp(-wa*r)); float ly=wf*wb*native_sin(wfq*zz2+wph)*(1.0f-native_exp(-wa*r)); float lz=wf*wc*native_sin(wfq*zx+wph)*(1.0f-native_exp(-wa*r)); z.x+=lx; z.y+=ly; z.z+=lz; aux.DE*=(1.0f+fabs(wf*(wam+wb+wc)*wfq/3.0f)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_99)
						case 99: { { float t=wfq*r+wph; float d=wf*wam*native_sin(t)*native_sin(wa*t); z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0f+fabs(d)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_WARPDISTTYPE_100)
						case 100: { { float d=wf*wam*(native_sin(wfq*zx+wph)+native_sin(wa*zy+wb)+native_sin(wc*zz2+wd)); z*=(1.0f+d/(3.0f*r)); aux.DE*=(1.0f+fabs(d/(3.0f*r))); } break; }
#endif

					default: break;
#endif
					}
				}

				// v7.9 — Symmetry/Kaleidoscope system (per-section iteration range)
				if (i >= mut->skIterStart && i < mut->skIterStop && mut->symKalType != 0)
				{
					float sf = mut->skFactor * mut->symmetryWeight * mut->masterWeight;
					float sa = mut->skParamA, sb = mut->skParamB, sc = mut->skParamC, sd = mut->skParamD;
					float sfq = mut->skFreq, sam = mut->skAmp;
					float sang = mut->skAngle * M_PI_F / 180.0, soff = mut->skOffset;
					float zx = z.x, zy = z.y, zz2 = z.z;
					float r = native_sqrt(zx*zx + zy*zy + zz2*zz2 + 1e-21);
					float4 z_orig_sk = z; float de_orig_sk = aux.DE;
					switch(mut->symKalType)
					{
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_1)
						case 1: { z.x = fabs(z.x); break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_2)
						case 2: { z.y = fabs(z.y); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_3)
						case 3: { z.z = fabs(z.z); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_4)
						case 4: { z.x = fabs(z.x); z.y = fabs(z.y); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_5)
						case 5: { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_6)
						case 6: { if(z.x < 0) z.x = -z.x - soff; else z.x = z.x + soff; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_7)
						case 7: { if(z.y < 0) z.y = -z.y - soff; else z.y = z.y + soff; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_8)
						case 8: { if(z.x + z.y < 0) { float t = z.x; z.x = -z.y; z.y = -t; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_9)
						case 9: { if(z.x - z.y < 0) { float t = z.x; z.x = z.y; z.y = t; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_10)
						case 10: { if(z.x + z.z < 0) { float t = z.x; z.x = -z.z; z.z = -t; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_11)
						case 11: { { float ang2 = atan2(zy, zx), n = fmax(1.0, sa), sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5;{ float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_12)
						case 12: { { float ang2 = atan2(zy, zx), n = 3.0, sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; { float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_13)
						case 13: { { float ang2 = atan2(zy, zx), n = 4.0, sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; { float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_14)
						case 14: { { float ang2 = atan2(zy, zx), n = 5.0, sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; { float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_15)
						case 15: { { float ang2 = atan2(zy, zx), n = 6.0, sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; { float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_16)
						case 16: { { float ang2 = atan2(zy, zx), n = 8.0, sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; { float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_17)
						case 17: { { float ang2 = atan2(zy, zx), n = 12.0, sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; { float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_18)
						case 18: { { float ang2 = atan2(zz2, zx), n = fmax(1.0, sa), sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5;{ float rxz = native_sqrt(zx*zx+zz2*zz2); z.x = rxz*native_cos(ang2); z.z = rxz*native_sin(ang2); } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_19)
						case 19: { { float ang2 = atan2(zz2, zy), n = fmax(1.0, sa), sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5;{ float ryz = native_sqrt(zy*zy+zz2*zz2); z.y = ryz*native_cos(ang2); z.z = ryz*native_sin(ang2); } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_20)
						case 20: { { float ang2 = atan2(zy, zx), n = fmax(1.0, sa), sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector); if(fmod(floor(ang2/sector), 2.0) > 0.5) ang2 = sector - fmod(ang2, sector); else ang2 = fmod(ang2, sector); ang2 -= sector*0.5;{ float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_21)
						case 21: { { float cs = native_cos(sang), sn = native_sin(sang), nx = zx*cs - zy*sn; z.y = zx*sn + zy*cs; z.x = fabs(nx); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_22)
						case 22: { { float cs = native_cos(sang), sn = native_sin(sang); z.x = fabs(zx); { float nx = zx*cs - zy*sn; z.y = zx*sn + zy*cs; z.x = nx; z.x = fabs(z.x); } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_23)
						case 23: { { if(z.x + z.y < soff) { float t = z.x; z.x = -z.y; z.y = -t; } float cs = native_cos(sang), sn = native_sin(sang), nx = zx*cs - zy*sn; z.y = zx*sn + zy*cs; z.x = nx; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_24)
						case 24: { { z.x = fabs(z.x); z.y = fabs(z.y); { float cs = native_cos(sang), sn = native_sin(sang); float nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; z.x = fabs(z.x); } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_25)
						case 25: { { z.x = fabs(z.x) + soff; z.y = fabs(z.y) + soff; { float cs = native_cos(sang), sn = native_sin(sang); float nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_26)
						case 26: { { for(int k=0; k<(int)(sa); k++) { z.x = fabs(z.x); z.y = fabs(z.y); float cs = native_cos(sang), sn = native_sin(sang); float nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_27)
						case 27: { { for(int k=0; k<(int)(sa); k++) { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); float cs = native_cos(sang+k*sb), sn = native_sin(sang+k*sb); float nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_28)
						case 28: { { float cs1 = native_cos(sang), sn1 = native_sin(sang), nx = zx*cs1 - zy*sn1; z.y = zx*sn1 + zy*cs1; z.x = nx; z.x = fabs(z.x); { float cs2 = native_cos(-sang), sn2 = native_sin(-sang); nx = z.x*cs2 - z.y*sn2; z.y = z.x*sn2 + z.y*cs2; z.x = nx; } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_29)
						case 29: { { z.x = fabs(z.x); if(z.x - z.y < 0) { float t = z.x; z.x = z.y; z.y = t; } z.y = fabs(z.y); { float cs = native_cos(sang), sn = native_sin(sang), nx = z.x*cs - z.z*sn; z.z = z.x*sn + z.z*cs; z.x = nx; } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_30)
						case 30: { { float n = fmax(2.0, sa); for(int k=0; k<(int)(n); k++) { float a = k * 2.0*M_PI_F/n, cs = native_cos(a), sn = native_sin(a), d = z.x*cs + z.y*sn; if(d < 0) { z.x -= 2.0*d*cs; z.y -= 2.0*d*sn; } } } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_31)
						case 31: { { z.x = fabs(z.x); z.y = fabs(z.y); if(z.y > z.x) { float t=z.x; z.x=z.y; z.y=t; } z.x -= sa; z.y -= sb; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_32)
						case 32: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.y > z.x) { float t=z.x; z.x=z.y; z.y=t; } if(z.z > z.x) { float t=z.x; z.x=z.z; z.z=t; } if(z.z > z.y) { float t=z.y; z.y=z.z; z.z=t; } z.x -= sa; z.y -= sb; z.z -= sc; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_33)
						case 33: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.x - z.y < 0) { float t=z.x; z.x=z.y; z.y=t; } if(z.x - z.z < 0) { float t=z.x; z.x=z.z; z.z=t; } if(z.y - z.z < 0) { float t=z.y; z.y=z.z; z.z=t; } z.x -= sa; z.y -= sb; z.z -= sc; float cs = native_cos(sang), sn = native_sin(sang); float nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_34)
						case 34: { { z.x = fabs(z.x); z.y = fabs(z.y); float d = z.x*native_cos(sang) + z.y*native_sin(sang); if(d < 0) { z.x -= 2.0f*d*native_cos(sang); z.y -= 2.0f*d*native_sin(sang); } z.x -= sa; z.y -= sb; z.z -= 0; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_35)
						case 35: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); z.x -= sa; z.y -= sb; z.z -= sc; if(z.y > z.x) { float t=z.x; z.x=z.y; z.y=t; } if(z.z > z.x) { float t=z.x; z.x=z.z; z.z=t; } if(z.z > z.y) { float t=z.y; z.y=z.z; z.z=t; } } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_36)
						case 36: { { float d = 2.0f*fmax(0.0f, z.x*native_cos(sang) + z.y*native_sin(sang)); z.x -= d*native_cos(sang); z.y -= d*native_sin(sang); z.x = fabs(z.x); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_37)
						case 37: { { z.x = fabs(z.x); z.y = fabs(z.y); float a = sang; for(int k=0; k<3; k++) { float d = 2.0f*fmin(0.0f, z.x*native_cos(a) + z.y*native_sin(a)); z.x -= d*native_cos(a); z.y -= d*native_sin(a); a += M_PI_F/3.0f; } z.x -= sa; z.y -= sb; z.z -= 0; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_38)
						case 38: { { for(int k=0; k<(int)(fmax(1,sa)); k++) { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); z.x -= sb; z.y -= sc; z.z -= sd; if(z.y > z.x) { float t=z.x; z.x=z.y; z.y=t; } if(z.z > z.x) { float t=z.x; z.x=z.z; z.z=t; } if(z.z > z.y) { float t=z.y; z.y=z.z; z.z=t; } z *= sf; aux.DE *= fabs(sf); } } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_39)
						case 39: { { for(int k=0; k<(int)(fmax(1,sa)); k++) { float cs = native_cos(sang+k*sb), sn = native_sin(sang+k*sb); float d = z.x*cs + z.y*sn; if(d < 0) { z.x -= 2.0f*d*cs; z.y -= 2.0f*d*sn; } z.x = fabs(z.x) - sc; z.y = fabs(z.y) - sd; } } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_40)
						case 40: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); z.x = z.x - sa*round(z.x/fmax(sa,1e-21f)); z.y = z.y - sb*round(z.y/fmax(sb,1e-21f)); z.z = z.z - sc*round(z.z/fmax(sc,1e-21f)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_41)
						case 41: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.x - z.y < 0) { float t=z.x; z.x=z.y; z.y=t; } if(z.x - z.z < 0) { float t=z.x; z.x=z.z; z.z=t; } if(z.y - z.z < 0) { float t=z.y; z.y=z.z; z.z=t; } z *= sf; { float _cF=(sf-1.0f); z.x -= sa*_cF; z.y -= sb*_cF; z.z -= sc*_cF; }; aux.DE = aux.DE * fabs(sf) + 1.0f; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_42)
						case 42: { { if(z.x + z.y < 0) { float t=-z.y; z.y=-z.x; z.x=t; } if(z.x + z.z < 0) { float t=-z.z; z.z=-z.x; z.x=t; } if(z.y + z.z < 0) { float t=-z.z; z.z=-z.y; z.y=t; } z *= sf; { float _cF=(sf-1.0f); z.x -= sa*_cF; z.y -= sb*_cF; z.z -= sc*_cF; }; aux.DE = aux.DE * fabs(sf) + 1.0f; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_43)
						case 43: { { z.x = fabs(z.x); z.y = fabs(z.y); if(z.x - z.y < 0) { float t=z.x; z.x=z.y; z.y=t; } z.x -= sa; z *= sf; z.x += sa; aux.DE = aux.DE * fabs(sf) + 1.0f; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_44)
						case 44: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.x - z.y < 0) { float t=z.x; z.x=z.y; z.y=t; } if(z.x - z.z < 0) { float t=z.x; z.x=z.z; z.z=t; } if(z.y - z.z < 0) { float t=z.y; z.y=z.z; z.z=t; } z.z -= 0.5f*sc*(sf-1.0f)/sf; z.z = fabs(z.z); z.z += 0.5f*sc*(sf-1.0f)/sf; z *= sf; { float _cF=(sf-1.0f); z.x -= sa*_cF; z.y -= sb*_cF; z.z -= sc*_cF; }; aux.DE = aux.DE*fabs(sf)+1.0f; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_45)
						case 45: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); float t; if(z.x-z.y<0){t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){t=z.y;z.y=z.z;z.z=t;} z *= sf; float _f45=(sf-1.0f)*sa; z.x -= _f45; z.y -= _f45; z.z -= _f45; aux.DE=aux.DE*fabs(sf)+1.0f; z.x=fabs(z.x); z.y=fabs(z.y); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_46)
						case 46: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); float d1 = z.x - z.y; float d2 = z.y - z.z; if(d1 < 0){float t=z.x;z.x=z.y;z.y=t;} if(d2 < 0){float t=z.y;z.y=z.z;z.z=t;} if(z.x-z.y < 0){float t=z.x;z.x=z.y;z.y=t;} z.x -= sa; z.y -= sb; z.z -= sc; z *= sf; z.x += sa; z.y += sb; z.z += sc; aux.DE = aux.DE*fabs(sf)+1.0f; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_47)
						case 47: { { z.x = sa - fabs(z.x - sa); z.y = sb - fabs(z.y - sb); z.z = sc - fabs(z.z - sc); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_48)
						case 48: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.x>sa) z.x=2.0f*sa-z.x; if(z.y>sb) z.y=2.0f*sb-z.y; if(z.z>sc) z.z=2.0f*sc-z.z; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_49)
						case 49: { { float p=sa; z.x = z.x - p*native_floor(z.x/p+0.5f); z.y = z.y - p*native_floor(z.y/p+0.5f); z.z = z.z - p*native_floor(z.z/p+0.5f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_50)
						case 50: { { float px=sa, py=sb; z.x = z.x - px*native_floor(z.x/px+0.5f); z.y = z.y - py*native_floor(z.y/py+0.5f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_51)
						case 51: { { float ph2=atan2(zy,zx); float n=fmax(1.0f,sa); float s=2.0f*M_PI_F/n; ph2=fmod(ph2+10.0f*M_PI_F,s)-s*0.5f; float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(ph2); z.y=rxy*native_sin(ph2); z.z=fabs(z.z); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_52)
						case 52: { { float ph2=atan2(zy,zx); float th=native_acos(zz2/r); float n=fmax(1.0f,sa); float sp=2.0f*M_PI_F/n; ph2=fmod(ph2+10.0f*M_PI_F,sp)-sp*0.5f; float m=fmax(1.0f,sb); float st=M_PI_F/m; th=fmod(th+10.0f*M_PI_F,st); z.x=r*native_sin(th)*native_cos(ph2); z.y=r*native_sin(th)*native_sin(ph2); z.z=r*native_cos(th); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_53)
						case 53: { { float ph2=atan2(zy,zx)+sang; float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(ph2); z.y=rxy*native_sin(ph2); z.z=fabs(zz2); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_54)
						case 54: { { float rxy=native_sqrt(zx*zx+zy*zy); if(rxy>sa) { float f=sa/rxy; z.x*=f; z.y*=f; } } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_55)
						case 55: { { if(r>sa) z*=sa/r; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_56)
						case 56: { { if(r<sa) z*=sa*sa/(r*r); else if(r<sb) z*=sa*sa/(r*r); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_57)
						case 57: { { float rr=r*r; if(rr<sa*sa) z*=sb*sb/(sa*sa); else if(rr<sb*sb) z*=sb*sb/rr; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_58)
						case 58: { { float th=native_acos(zz2/r); float n=fmax(1.0f,sa); float st=M_PI_F/n; th=fmod(th+10.0f*M_PI_F,st); z.x=r*native_sin(th)*native_cos(atan2(zy,zx)); z.y=r*native_sin(th)*native_sin(atan2(zy,zx)); z.z=r*native_cos(th); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_59)
						case 59: { { float p=sa; z.x=z.x-p*round(z.x/p); z.y=z.y-p*round(z.y/p); z.z=z.z-p*round(z.z/p); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_60)
						case 60: { { z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; z.z=fabs(z.z)-sc; if(z.x<0) z.x=-z.x; if(z.y<0) z.y=-z.y; if(z.z<0) z.z=-z.z; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_61)
						case 61: { { float px=fmax(sa,0.01f); z.x=z.x-px*native_floor(z.x/px); z.y=fabs(z.y); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_62)
						case 62: { { float px=fmax(sa,0.01f), py=fmax(sb,0.01f); z.x=z.x-px*native_floor(z.x/px); z.y=z.y-py*native_floor(z.y/py); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_63)
						case 63: { { float px=fmax(sa,0.01f), py=fmax(sb,0.01f); z.x=z.x-px*native_floor(z.x/px); z.y=z.y-py*native_floor(z.y/py); z.x=fabs(z.x-px*0.5f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_64)
						case 64: { { float px=fmax(sa,0.01f), py=fmax(sb,0.01f); float ix=native_floor(z.x/px); z.x=z.x-px*ix; z.y=z.y-py*native_floor(z.y/py); if(fmod(ix,2.0f)>0.5f) z.x=px-z.x; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_65)
						case 65: { { float p=fmax(sa,0.01f); float a60=M_PI_F/3.0f; float ux=p, uy=0; float vx=p*native_cos(a60), vy=p*native_sin(a60); float det=ux*vy-uy*vx; float ix=native_floor((z.x*vy-z.y*vx)/det+0.5f); float iy=native_floor((z.y*ux-z.x*uy)/det+0.5f); z.x-=ix*ux+iy*vx; z.y-=ix*uy+iy*vy; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_66)
						case 66: { { float px=fmax(sa,0.01f), py=fmax(sb,0.01f), pz=fmax(sc,0.01f); z.x=z.x-px*native_floor(z.x/px); z.y=z.y-py*native_floor(z.y/py); z.z=z.z-pz*native_floor(z.z/pz); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_67)
						case 67: { { float px=fmax(sa,0.01f), py=fmax(sb,0.01f), pz=fmax(sc,0.01f); z.x=z.x-px*round(z.x/px); z.y=z.y-py*round(z.y/py); z.z=z.z-pz*round(z.z/pz); z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_68)
						case 68: { { float p=fmax(sa,0.01f); z.x=z.x-p*round(z.x/p); z.y=z.y-p*round(z.y/p); z.z=z.z-p*round(z.z/p); float cs=native_cos(sang),sn=native_sin(sang); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_69)
						case 69: { { float p=fmax(sa,0.01f); float ix=round(z.x/p); float iy=round(z.y/p); z.x-=ix*p; z.y-=iy*p; float a=sang*(ix+iy); float cs=native_cos(a),sn=native_sin(a); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_70)
						case 70: { { float p=fmax(sa,0.01f); z.x=z.x-p*native_floor(z.x/p+0.5f); z.y=z.y-p*native_floor(z.y/p+0.5f); float cs=native_cos(sang),sn=native_sin(sang); if(z.x+z.y>0) { float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_71)
						case 71: { if(z.x*z.y > 0) { float t=z.x; z.x=z.y; z.y=t; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_72)
						case 72: { if(z.x*z.y < 0) { z.x = fabs(z.x); z.y = fabs(z.y); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_73)
						case 73: { if(r < sa) { z *= sf; aux.DE *= fabs(sf); } else { z.x = fabs(z.x); z.y = fabs(z.y); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_74)
						case 74: { if(fmod((float)(i), sa) < sb) { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_75)
						case 75: { { float d = z.x*native_cos(sang) + z.y*native_sin(sang); if(d < soff) { z.x -= 2.0f*(d-soff)*native_cos(sang); z.y -= 2.0f*(d-soff)*native_sin(sang); } } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_76)
						case 76: { { float d1 = z.x*native_cos(sang)+z.y*native_sin(sang); if(d1<0){z.x-=2.0f*d1*native_cos(sang);z.y-=2.0f*d1*native_sin(sang);} float a2=sang+M_PI_F/fmax(1.0f,sa); float d2=z.x*native_cos(a2)+z.y*native_sin(a2); if(d2<0){z.x-=2.0f*d2*native_cos(a2);z.y-=2.0f*d2*native_sin(a2);} } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_77)
						case 77: { { for(int k=0;k<(int)(fmax(1,sa));k++){ z.x=fabs(z.x)-sb; z.y=fabs(z.y)-sc; if(z.x<z.y){float t=z.x;z.x=z.y;z.y=t;} } } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_78)
						case 78: { { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); float m=fmax(fmax(z.x,z.y),z.z); if(m==z.y){float t=z.x;z.x=z.y;z.y=t;} if(m==z.z){float t=z.x;z.x=z.z;z.z=t;} } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_79)
						case 79: { { z.x = sa*native_floor(z.x/fmax(sa,0.01f)+0.5f)*2.0f-z.x; z.y = sb*native_floor(z.y/fmax(sb,0.01f)+0.5f)*2.0f-z.y; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_80)
						case 80: { { float a=sang; for(int k=0;k<3;k++){ z.x=fabs(z.x); float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0){z.x-=2.0f*d*native_cos(a);z.y-=2.0f*d*native_sin(a);} a+=M_PI_F/3.0f*sf; } } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_81)
						case 81: { { float n=fmax(2.0f,sa+sb*native_sin(sfq*i)); float ang2=atan2(zy,zx); float s=2.0f*M_PI_F/n; ang2=fmod(ang2+10.0f*M_PI_F,s)-s*0.5f; float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(ang2); z.y=rxy*native_sin(ang2); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_82)
						case 82: { { float a=sang+sam*native_sin(sfq*i); float cs=native_cos(a),sn=native_sin(a); z.x=fabs(z.x); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_83)
						case 83: { { float d=sf*sam*native_sin(sfq*r+sang); z.x=fabs(z.x)+d; z.y=fabs(z.y)+d; z.z=fabs(z.z)+d; aux.DE*=(1.0f+fabs(d)/r); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_84)
						case 84: { { float n=fmax(2.0f,sa); float ang2=atan2(zy,zx); float s=2.0f*M_PI_F/n; ang2=fmod(ang2+10.0f*M_PI_F+sam*native_sin(sfq*i),s)-s*0.5f; float rxy=native_sqrt(zx*zx+zy*zy); z.x=rxy*native_cos(ang2); z.y=rxy*native_sin(ang2); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_85)
						case 85: { { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); z *= sf + sam*native_sin(sfq*i); aux.DE *= fabs(sf + sam*native_sin(sfq*i)); { float _cF=(sf-1.0f); z.x -= sa*_cF; z.y -= sb*_cF; z.z -= sc*_cF; }; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_86)
						case 86: { { if(i%2==0){z.x=fabs(z.x);z.y=fabs(z.y);} else{float cs=native_cos(sang),sn=native_sin(sang);float nx=z.x*cs-z.y*sn;z.y=z.x*sn+z.y*cs;z.x=nx;} } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_87)
						case 87: { { float rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sa*sa){z*=sb*sb/(sa*sa);aux.DE*=sb*sb/(sa*sa);} else if(rr<sb*sb){z*=sb*sb/rr;aux.DE*=sb*sb/rr;} z.x=fabs(z.x); z.y=fabs(z.y); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_88)
						case 88: { { if(z.x+z.y<0){float t=-z.y;z.y=-z.x;z.x=t;} if(z.x+z.z<0){float t=-z.z;z.z=-z.x;z.x=t;} z *= sf; { float _cF=(sf-1.0f); z.x -= sa*_cF; z.y -= sb*_cF; z.z -= sc*_cF; }; aux.DE=aux.DE*fabs(sf)+1.0f; if(z.y-z.z<0){float t=z.y;z.y=z.z;z.z=t;} } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_89)
						case 89: { { z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; if(z.x<z.y){float t=z.x;z.x=z.y;z.y=t;} float rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sc*sc){float m=sd*sd/(sc*sc);z*=m;aux.DE*=m;} else if(rr<sd*sd){float m=sd*sd/rr;z*=m;aux.DE*=m;} } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_90)
						case 90: { { float p=fmax(sa,0.01f); z.x=z.x-p*round(z.x/p); z.y=z.y-p*round(z.y/p); z.x=fabs(z.x); z.y=fabs(z.y); if(z.x<z.y){float t=z.x;z.x=z.y;z.y=t;} z *= sf; aux.DE *= fabs(sf); { float _cF=(sf-1.0f); z.x -= sb*_cF; z.y -= sc*_cF; z.z -= 0*_cF; }; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_91)
						case 91: { { z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; z.z=fabs(z.z)-sc; if(z.x<z.y){float t=z.x;z.x=z.y;z.y=t;} if(z.x<z.z){float t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){float t=z.y;z.y=z.z;z.z=t;} z*=sf; aux.DE*=fabs(sf); z.x += sa; z.y += sb; z.z += sc; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_92)
						case 92: { { float cs=native_cos(sang),sn=native_sin(sang); z.x=fabs(z.x); z.y=fabs(z.y); float d=z.x*sn+z.y*cs; if(d<0){z.x-=2.0f*d*sn;z.y-=2.0f*d*cs;} z.x-=sa; z.y-=sb; z*=sf; z.x+=sa; z.y+=sb; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_93)
						case 93: { { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); if(z.x-z.y<0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){float t=z.x;z.x=z.z;z.z=t;} z*=sf; z.x-=sa*(sf-1.0f); z.y-=sb*(sf-1.0f); z.z-=sc*(sf-1.0f); float rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sd*sd){z*=sd*sd/rr;aux.DE*=sd*sd/rr;} aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_94)
						case 94: { { for(int k=0;k<(int)(fmax(1,sa));k++){ z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); if(z.x-z.y<0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){float t=z.y;z.y=z.z;z.z=t;} z.x-=sb; z.y-=sc; z.z-=sd; float cs=native_cos(sang+k*sfq),sn=native_sin(sang+k*sfq); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; z.x+=sb; z.y+=sc; z.z+=sd; } } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_95)
						case 95: { { float n=fmax(2.0f,sa); for(int k=0;k<(int)(n);k++){ float a=k*M_PI_F/n; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0){z.x-=2.0f*d*native_cos(a);z.y-=2.0f*d*native_sin(a);} } z.z=fabs(z.z); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_96)
						case 96: { { z=fabs(z); if(z.x<z.y){float t=z.x;z.x=z.y;z.y=t;} if(z.x<z.z){float t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){float t=z.y;z.y=z.z;z.z=t;} z.x -= sa; z.y -= sb; z.z -= sc; float rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sd*sd){float m=sf*sf/fmax(rr,1e-21f);z*=m;aux.DE*=m;} z*=sf;aux.DE*=fabs(sf); z.x += sa; z.y += sb; z.z += sc; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_97)
						case 97: { { float a=2.0f*M_PI_F/fmax(1.0f,sa); float cs=native_cos(a),sn=native_sin(a); z.x=fabs(z.x); z.y=fabs(z.y); float d=z.x*sn+z.y*cs-soff; if(d>0){z.x-=d*sn;z.y-=d*cs;} z.x-=sb; z*=sf; z.x+=sb; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_98)
						case 98: { { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); float d=2.0f*fmin(0.0f,z.x+z.y+z.z-sa); z.x-=d/3.0f; z.y-=d/3.0f; z.z-=d/3.0f; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_99)
						case 99: { { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); if(z.x-z.y<0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){float t=z.y;z.y=z.z;z.z=t;} z.z-=0.5f*sa; z.z=-fabs(z.z)+0.5f*sa; float cs=native_cos(sang),sn=native_sin(sang); float nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SYMKALTYPE_100)
						case 100: { { z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; z.z=fabs(z.z)-sc; if(z.x<z.y){float t=z.x;z.x=z.y;z.y=t;} if(z.x<z.z){float t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){float t=z.y;z.y=z.z;z.z=t;} float rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sd*sd){float m=sf*sf/fmax(rr,1e-21f);z*=m;aux.DE*=m;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; { float _cF=(1.0f-sf); z.x += sa*_cF; z.y += sb*_cF; z.z += sc*_cF; }; } break; }
#endif

					default: break;
#endif
					}
					float sk_blend = clamp(mut->symmetryWeight * mut->masterWeight, 0.0f, 1.0f);
					z = z_orig_sk + (z - z_orig_sk) * sk_blend;
					aux.DE = de_orig_sk + (aux.DE - de_orig_sk) * sk_blend;
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
					float de_orig_ab = aux.DE;
					switch(mut->aboxType)
					{
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_1)
						case 1: { aux.DE *= (1.0 + af * aa); break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_2)
						case 2: { aux.DE *= (1.0 + af * aa * native_sin(ab * r)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_3)
						case 3: { aux.DE *= (1.0 + af * aa * native_cos(ab * r)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_4)
						case 4: { aux.DE *= (1.0 + af * aa * native_exp(-ab * r)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_5)
						case 5: { aux.DE *= (1.0 + af * aa * native_exp(-ab * rr)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_6)
						case 6: { aux.DE *= (1.0 + af * aa * native_log(1.0 + ab * r)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_7)
						case 7: { aux.DE *= (1.0 + af * aa * tanh(ab * r)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_8)
						case 8: { aux.DE *= (1.0 + af * aa * native_sin(ab * zx) * native_cos(ac * zy)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_9)
						case 9: { aux.DE *= (1.0 + af * aa * native_sin(ab * zy) * native_cos(ac * zz2)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_10)
						case 10: { aux.DE *= (1.0 + af * aa * native_sin(ab * zz2) * native_cos(ac * zx)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_11)
						case 11: { aux.DE *= (1.0 + af * aa * (native_sin(ab*zx) + native_sin(ac*zy) + native_sin(ad*zz2)) / 3.0); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_12)
						case 12: { aux.DE *= (1.0 + af * aa / (1.0 + ab * rr)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_13)
						case 13: { aux.DE *= (1.0 + af * aa * pow(r, ab - 1.0)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_14)
						case 14: { aux.DE *= (1.0 + af * aa * fabs(native_sin(ab * r))); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_15)
						case 15: { aux.DE *= (1.0 + af * aa * (1.0 - native_exp(-ab * r))); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_16)
						case 16: { { float sg = 1.0/(1.0+native_exp(-aa*(r-ab))); aux.DE *= (1.0 + af * sg); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_17)
						case 17: { aux.DE *= (1.0 + af * aa * native_sin(ab*zx)*native_sin(ac*zy)*native_sin(ad*zz2)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_18)
						case 18: { aux.DE *= (1.0 + af * aa * native_cos(ab*zx)*native_cos(ac*zy)*native_cos(ad*zz2)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_19)
						case 19: { aux.DE *= (1.0 + af * aa * native_sin(ab*r+ac*atan2(zy,zx))); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_20)
						case 20: { aux.DE *= (1.0 + af * aa * native_sin(ab*r)*native_cos(ac*acos(zz2/r))); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_21)
						case 21: { { float v = 0; for(int o=0;o<4;o++) v += native_sin(ab*pow(2.0,o)*r)/(pow(2.0,o)); aux.DE *= (1.0 + af * aa * v); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_22)
						case 22: { aux.DE *= (1.0 + af * aa * (zx*zy+zy*zz2+zz2*zx)/(rr+1e-21)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_23)
						case 23: { aux.DE *= (1.0 + af * aa * fabs(zx*zy*zz2)/(r*r*r+1e-21)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_24)
						case 24: { aux.DE *= (1.0 + af * aa * native_sin(ab*(zx*zx-zy*zy)/(rr+1e-21))); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_25)
						case 25: { aux.DE *= (1.0 + af * aa * atan2(native_sqrt(zx*zx+zy*zy), zz2) / M_PI_F); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_26)
						case 26: { { float rr2=rr; if(rr2<aa*aa) { float m=ab*ab/fmax(rr2,1e-21); aux.DE*=m; } aux.DE*=(1.0+af*0.1); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_27)
						case 27: { { float rr2=rr, mR2=aa*aa, fR2=ab*ab; if(rr2<mR2) aux.DE*=fR2/mR2; else if(rr2<fR2) aux.DE*=fR2/rr2; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_28)
						case 28: { aux.DE *= (1.0 + af * aa * native_exp(-ab*(r-ac)*(r-ac))); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_29)
						case 29: { aux.DE *= (1.0 + af * aa * (1.0/(1.0+native_exp(-ab*(r-ac))) - 0.5)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_30)
						case 30: { aux.DE *= (1.0 + af * aa * native_sin(ab*r)*native_exp(-ac*r)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_31)
						case 31: { aux.DE *= (1.0f + af * aa * fabs(native_sin(ab*r+ac))*native_exp(-ad*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_32)
						case 32: { { float s = aa * native_sin(ab*r+ac*atan2(zy,zx)) * native_exp(-ad*r); aux.DE *= (1.0f + af*s); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_33)
						case 33: { aux.DE *= (1.0f + af * aa * tanh(ab*(r-ac))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_34)
						case 34: { aux.DE *= (1.0f + af * aa * native_sin(ab*native_log(r+1e-21f))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_35)
						case 35: { aux.DE *= (1.0f + af * aa * native_cos(ab*native_log(r+1e-21f)+ac)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_36)
						case 36: { { float ph=atan2(zy,zx); float th=native_acos(zz2/r); aux.DE*=(1.0f+af*aa*native_sin(ab*ph)*native_sin(ac*th)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_37)
						case 37: { { float ph=atan2(zy,zx); aux.DE*=(1.0f+af*aa*native_cos(ab*ph+ac*r)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_38)
						case 38: { aux.DE *= fmax(0.01f, 1.0f + af * aa * native_sin(ab*r) * native_cos(ac*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_39)
						case 39: { { float d=r-aa; aux.DE*=(1.0f+af*ab*native_exp(-ac*d*d)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_40)
						case 40: { aux.DE *= (1.0f + af * aa * native_sin(ab*r) / (r+1e-21f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_41)
						case 41: { { float n=native_sin(aa*zx)*native_sin(ab*zy)*native_sin(ac*zz2); aux.DE*=(1.0f+af*ad*n); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_42)
						case 42: { { float rxy=native_sqrt(zx*zx+zy*zy+1e-21f); aux.DE*=(1.0f+af*aa*native_sin(ab*rxy+ac*zz2)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_43)
						case 43: { aux.DE *= (1.0f + af * aa * native_cos(ab*zx+ac*zy+ad*zz2)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_44)
						case 44: { { float v=aa*native_sin(ab*r)+ac*native_cos(ad*r); aux.DE*=(1.0f+af*v*0.5f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_45)
						case 45: { aux.DE *= fmax(0.01f, 1.0f + af * aa * native_pow(fabs(native_sin(ab*r)), ac)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_46)
						case 46: { aux.DE *= (1.0f + af * aa * native_sin(ab*r*r/(r+1e-21f))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_47)
						case 47: { { float f=aa+ab*native_sin(ac*i); aux.DE*=(1.0f+af*f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_48)
						case 48: { { float rr2=rr; float minR=aa; float fixR=ab; if(rr2<minR*minR){float m=fixR*fixR/(minR*minR);aux.DE*=m;} else if(rr2<fixR*fixR){float m=fixR*fixR/rr2;aux.DE*=m;} aux.DE*=(1.0f+af*ac*native_sin(ad*r)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_49)
						case 49: { aux.DE *= (1.0f + af * aa * (native_sin(ab*r) + native_cos(ac*r*r/(r+1e-21f))) * 0.5f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_50)
						case 50: { { float d=fabs(r-aa); float ring=native_exp(-ab*d*d); aux.DE*=(1.0f+af*ac*ring); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_51)
						case 51: { aux.DE *= fabs(aa); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_52)
						case 52: { aux.DE *= fabs(aa + ab*native_sin(ac*i)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_53)
						case 53: { aux.DE *= fabs(aa * native_pow(ab, ac)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_54)
						case 54: { aux.DE *= fabs(aa + ab * r); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_55)
						case 55: { aux.DE *= fmax(0.01f, fabs(aa + ab * native_sin(ac * r))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_56)
						case 56: { aux.DE *= fabs(aa + ab * native_exp(-ac * i)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_57)
						case 57: { aux.DE *= fabs(aa + ab * native_log(1.0f + ac * i)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_58)
						case 58: { { float golden=1.6180339887f; aux.DE*=fabs(aa+ab*native_pow(golden,ac*i-ad)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_59)
						case 59: { aux.DE *= fabs(aa + ab * native_sin(ac * i) * native_cos(ad * r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_60)
						case 60: { { float s=aa+ab*tanh(ac*(i-ad)); aux.DE*=fabs(s); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_61)
						case 61: { aux.DE *= fmax(0.01f, fabs(aa + ab * fmod((float)(i) * ac, ad))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_62)
						case 62: { aux.DE *= fabs(aa + ab / (1.0f + ac * i)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_63)
						case 63: { { float ph=atan2(zy,zx); aux.DE*=fabs(aa+ab*native_sin(ac*ph)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_64)
						case 64: { aux.DE *= fabs(aa + ab * (zx*zx - zy*zy) / (rr + 1e-21f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_65)
						case 65: { aux.DE *= fabs(aa + ab * native_sin(ac * i * M_PI_F / ad)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_66)
						case 66: { { float s=aa*(1.0f+ab*native_sin(ac*(float)(i))); aux.DE*=fabs(s); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_67)
						case 67: { aux.DE *= fabs(aa + ab * fabs(native_sin(ac * r + ad * i))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_68)
						case 68: { { float s=aa+ab*native_cos(ac*r)*native_sin(ad*i*0.1f); aux.DE*=fabs(s); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_69)
						case 69: { aux.DE *= fabs(aa + ab * (native_sin(ac*zx)+native_sin(ad*zy)+native_sin(ae*zz2))/3.0f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_70)
						case 70: { { float rat=aa/fmax(ab,1e-21f); float s=native_pow(fabs(rat),ac); aux.DE*=s; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_71)
						case 71: { aux.DE *= fmax(0.01f, fabs(aa * native_exp(-ab * fabs(native_sin(ac * r))))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_72)
						case 72: { { float s=aa+ab*native_pow(fabs(native_sin(ac*r)),ad); aux.DE*=fabs(s); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_73)
						case 73: { aux.DE *= fabs(aa + ab * tanh(ac * native_sin(ad * r))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_74)
						case 74: { { float mix=0.5f+0.5f*native_sin(ac*i); float s=aa*(1.0f-mix)+ab*mix; aux.DE*=fabs(s); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_75)
						case 75: { aux.DE *= fabs(aa + ab * native_sin(ac * r) * native_log(1.0f + ad * r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_76)
						case 76: { { float a=aa*M_PI_F/180.0f; aux.DE*=(1.0f+af*fabs(native_sin(a))); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_77)
						case 77: { { float a=aa*M_PI_F/180.0f+ab*native_sin(ac*i); aux.DE*=(1.0f+af*fabs(native_sin(a))); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_78)
						case 78: { aux.DE *= (1.0f + af * aa * native_sin(ab*atan2(zy,zx))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_79)
						case 79: { aux.DE *= (1.0f + af * aa * native_cos(ab*atan2(zy,zx)+ac*native_acos(zz2/r))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_80)
						case 80: { { float ph=atan2(zy,zx); float n=fmax(1.0f,aa); float s=2.0f*M_PI_F/n; float sector=fmod(ph+10.0f*M_PI_F,s)/s; aux.DE*=(1.0f+af*ab*native_sin(M_PI_F*sector)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_81)
						case 81: { aux.DE *= (1.0f + af * aa * fabs(native_sin(ab * atan2(zz2, native_sqrt(zx*zx+zy*zy+1e-21f))))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_82)
						case 82: { { float q1=zx*native_cos(aa)-zy*native_sin(aa); float q2=zx*native_sin(aa)+zy*native_cos(aa); aux.DE*=(1.0f+af*ab*native_sin(ac*q1)*native_cos(ad*q2)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_83)
						case 83: { aux.DE *= (1.0f + af * aa * native_cos(ab * (zx+zy+zz2))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_84)
						case 84: { { float cs=native_cos(aa*M_PI_F/180.0f),sn=native_sin(aa*M_PI_F/180.0f); float rxy=native_sqrt(zx*zx+zy*zy+1e-21f); float nph=atan2(zy,zx)+ab*native_sin(ac*rxy); aux.DE*=(1.0f+af*ad*native_sin(ae*nph)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_85)
						case 85: { aux.DE *= (1.0f + af * aa * native_sin(ab*(zx*zy+zy*zz2+zz2*zx)/(rr+1e-21f))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_86)
						case 86: { { float gld=aa*0.618033988749895f; aux.DE*=(1.0f+af*ab*native_sin(ac*gld*i)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_87)
						case 87: { aux.DE *= (1.0f + af * aa * native_sin(ab*r+ac*atan2(zy,zx)+ad*i*0.1f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_88)
						case 88: { { float sw=fabs(zx)>fabs(zy)?zx:zy; aux.DE*=(1.0f+af*aa*native_sin(ab*sw)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_89)
						case 89: { aux.DE *= (1.0f + af * aa * native_cos(ab*zx*zy/(r+1e-21f))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_90)
						case 90: { { float fld=aa*(fabs(zx)+fabs(zy)+fabs(zz2)); aux.DE*=(1.0f+af*ab*native_sin(fld)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_91)
						case 91: { aux.DE *= (1.0f + af * aa * native_sin(ab*i) * native_cos(ac*r) * native_sin(ad*atan2(zy,zx))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_92)
						case 92: { { float sym=fabs(zx-zy)+fabs(zy-zz2)+fabs(zz2-zx); aux.DE*=(1.0f+af*aa*native_sin(ab*sym)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_93)
						case 93: { aux.DE *= (1.0f + af * aa * tanh(ab*native_sin(ac*atan2(zy,zx)))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_94)
						case 94: { { float det=zx*zy-zy*zz2+zz2*zx; aux.DE*=(1.0f+af*aa*native_sin(ab*det/(rr+1e-21f))); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_95)
						case 95: { aux.DE *= (1.0f + af * aa * native_sin(ab*r) * native_sin(ac*atan2(zy,zx)+ad*native_acos(zz2/r))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_96)
						case 96: { { float tw=aa*zz2+ab; float cs=native_cos(tw),sn=native_sin(tw); aux.DE*=(1.0f+af*ac*fabs(sn)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_97)
						case 97: { aux.DE *= (1.0f + af * aa * fabs(native_sin(ab*zx))*fabs(native_sin(ac*zy))*fabs(native_sin(ad*zz2))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_98)
						case 98: { { float mir=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.DE*=(1.0f+af*aa*native_sin(ab*mir)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_99)
						case 99: { { float mx=fmax(fabs(zx),fmax(fabs(zy),fabs(zz2))); aux.DE*=(1.0f+af*aa*native_cos(ab*mx)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_100)
						case 100: { aux.DE *= (1.0f + af * aa * native_sin(ab*r+ac*native_sin(ad*r))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_101)
						case 101: { { float w=aa*native_sin(ab*r); aux.DE*=(1.0f+af*ac*fabs(w)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_102)
						case 102: { { float r4=native_sqrt(rr+aa*aa*native_sin(ab*r)*native_sin(ab*r)); aux.DE*=(1.0f+af*ac*(r4-r)/(r+1e-21f)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_103)
						case 103: { { float w=aa*native_cos(ab*zx+ac*zy); aux.DE*=(1.0f+af*ad*w*w); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_104)
						case 104: { { float w=aa*native_sin(ab*i*0.1f); float r4=native_sqrt(rr+w*w); aux.DE*=(1.0f+af*ac*native_sin(ad*r4)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_105)
						case 105: { aux.DE *= (1.0f + af * aa * native_sin(ab*(zx*zx+zy*zy-zz2*zz2)/(rr+1e-21f))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_106)
						case 106: { { float w=aa*native_sin(ab*r+ac*i*0.1f); aux.DE*=(1.0f+af*ad*native_exp(-ae*w*w)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_107)
						case 107: { { float q=zx*zx-zy*zy; float s=2.0f*zx*zy; aux.DE*=(1.0f+af*aa*native_sin(ab*q/(rr+1e-21f))*native_cos(ac*s/(rr+1e-21f))); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_108)
						case 108: { aux.DE *= (1.0f + af * aa * native_sin(ab*(zx*zy+ac*zz2))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_109)
						case 109: { { float hd=native_sin(aa*zx)*native_cos(ab*zy)+native_sin(ac*zy)*native_cos(ad*zz2)+native_sin(ae*zz2)*native_cos(aff*zx); aux.DE*=(1.0f+af*ag*hd/3.0f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_110)
						case 110: { { float cr=zx*zx+zy*zy; float ci=2.0f*zx*zy; float r4=native_sqrt(cr*cr+ci*ci+zz2*zz2); aux.DE*=(1.0f+af*aa*native_sin(ab*r4)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_111)
						case 111: { aux.DE *= (1.0f + af * aa * tanh(ab*(zx*zx+zy*zy-zz2*zz2))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_112)
						case 112: { aux.DE *= (1.0f + af * aa * native_sin(ab*zx+ac) * native_sin(ad*zy+ae) * native_cos(aff*zz2)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_113)
						case 113: { { float p=aa*zx*zy*zz2/(r*r*r+1e-21f); aux.DE*=(1.0f+af*ab*native_sin(ac*p)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_114)
						case 114: { { float s1=native_sin(aa*r),s2=native_sin(ab*r); float w=s1*s1-s2*s2; aux.DE*=(1.0f+af*ac*w); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_115)
						case 115: { aux.DE *= (1.0f + af * aa * native_cos(ab*r*r/(r+1e-21f)+ac*native_sin(ad*r))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_116)
						case 116: { { float w=aa*native_sin(ab*(zx+zy+zz2))+ac*native_cos(ad*(zx-zy+zz2)); aux.DE*=(1.0f+af*w*0.5f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_117)
						case 117: { aux.DE *= (1.0f + af * aa * native_sin(ab*zx*zx/(rr+1e-21f)+ac*zy*zy/(rr+1e-21f))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_118)
						case 118: { { float v=aa*native_sin(ab*r)+ac*native_sin(ad*r)+ae*native_sin(aff*r); aux.DE*=(1.0f+af*v/3.0f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_119)
						case 119: { aux.DE *= (1.0f + af * aa * native_exp(-ab*fabs(zx*zy*zz2)/(r*r*r+1e-21f))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_120)
						case 120: { { float w=aa+ab*native_sin(ac*r+ad*native_sin(ae*r)); aux.DE*=(1.0f+af*w); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_121)
						case 121: { aux.DE *= (1.0f + af * aa * native_sin(ab*(r - native_floor(r*ac)/ac))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_122)
						case 122: { { float ph4=atan2(zz2,native_sqrt(zx*zx+zy*zy+1e-21f)); aux.DE*=(1.0f+af*aa*native_sin(ab*ph4+ac*r)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_123)
						case 123: { aux.DE *= (1.0f + af * aa * fabs(native_sin(ab*r)*native_cos(ac*r)*native_sin(ad*r))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_124)
						case 124: { { float v=aa*native_sin(ab*zx)*native_cos(ac*zx)+ad*native_sin(ae*zy)*native_cos(aff*zy); aux.DE*=(1.0f+af*v*0.5f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_125)
						case 125: { aux.DE *= (1.0f + af * aa * (native_sin(ab*r)+native_sin(ac*r)+native_sin(ad*r)+native_sin(ae*r))/4.0f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_126)
						case 126: { aux.DE *= (1.0f + af * aa * fabs(zx)/(r+1e-21f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_127)
						case 127: { aux.DE *= (1.0f + af * aa * fabs(zy)/(r+1e-21f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_128)
						case 128: { aux.DE *= (1.0f + af * aa * fabs(zz2)/(r+1e-21f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_129)
						case 129: { { float orb=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.DE*=(1.0f+af*aa*native_sin(ab*orb)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_130)
						case 130: { { float orb=fmax(fabs(zx),fmax(fabs(zy),fabs(zz2))); aux.DE*=(1.0f+af*aa*native_cos(ab*orb)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_131)
						case 131: { { float orb=native_sqrt(zx*zx+zy*zy); aux.DE*=(1.0f+af*aa*native_sin(ab*orb)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_132)
						case 132: { { float dt=fabs(native_sqrt(zx*zx+zy*zy)-aa); aux.DE*=(1.0f+af*ab*native_exp(-ac*dt*dt)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_133)
						case 133: { { float ds=fmax(fabs(zx)-aa,fabs(zy)-ab); ds=fmax(ds,fabs(zz2)-ac); aux.DE*=(1.0f+af*ad*native_exp(-ae*ds*ds)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_134)
						case 134: { { float dp=fabs(zx*native_cos(aa)+zy*native_sin(aa)-ab); aux.DE*=(1.0f+af*ac*native_exp(-ad*dp*dp)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_135)
						case 135: { { float dl=fabs(zx-aa*zy-ab); aux.DE*=(1.0f+af*ac*native_exp(-ad*dl*dl)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_136)
						case 136: { { float c=fabs(native_sin(aa*zx)+native_sin(ab*zy)+native_sin(ac*zz2))/3.0f; aux.DE*=(1.0f+af*ad*c); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_137)
						case 137: { { float c=fabs(native_sin(aa*r)*native_cos(ab*atan2(zy,zx))); aux.DE*=(1.0f+af*ac*c); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_138)
						case 138: { { float c=fabs(zx*zy+zy*zz2+zz2*zx)/(rr+1e-21f); aux.DE*=(1.0f+af*aa*c); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_139)
						case 139: { { float h=atan2(zy,zx)/(2.0f*M_PI_F)+0.5f; aux.DE*=(1.0f+af*aa*native_sin(ab*h*M_PI_F*2.0f)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_140)
						case 140: { { float s=r/(r+aa); aux.DE*=(1.0f+af*ab*s); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_141)
						case 141: { { float v=native_sin(aa*zx)*native_sin(ab*zy)+native_sin(ac*zy)*native_sin(ad*zz2); aux.DE*=(1.0f+af*ae*v*0.5f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_142)
						case 142: { { float orb=fabs(zx-native_floor(zx*aa)/aa)*fabs(zy-native_floor(zy*ab)/ab); aux.DE*=(1.0f+af*ac*native_sin(ad*orb)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_143)
						case 143: { aux.DE *= (1.0f + af * aa * native_sin(ab * (fabs(zx)+fabs(zy)+fabs(zz2)))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_144)
						case 144: { { float d2=fabs(zx*zx/fmax(aa*aa,0.01f)+zy*zy/fmax(ab*ab,0.01f)-1.0f); aux.DE*=(1.0f+af*ac*native_exp(-ad*d2)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_145)
						case 145: { { float sp=zx*native_cos(aa*zy)+zy*native_cos(aa*zz2)+zz2*native_cos(aa*zx); aux.DE*=(1.0f+af*ab*native_sin(ac*sp)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_146)
						case 146: { { float cl=native_sin(aa*length(pointTransformed)+ab*r); aux.DE*=(1.0f+af*ac*cl); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_147)
						case 147: { { float it=(float)(i)/fmax((float)(aa),1.0f); aux.DE*=(1.0f+af*ab*native_sin(ac*it*M_PI_F)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_148)
						case 148: { { float gr=native_sin(aa*zx*zy/(r+1e-21f))+native_cos(ab*zy*zz2/(r+1e-21f)); aux.DE*=(1.0f+af*ac*gr*0.5f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_149)
						case 149: { { float pat=native_sin(aa*zx)*native_cos(ab*zy)*native_sin(ac*zz2)*native_cos(ad*r); aux.DE*=(1.0f+af*ae*pat); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_150)
						case 150: { { float comb=aa*native_sin(ab*r)+ac*native_cos(ad*atan2(zy,zx))+ae*native_sin(aff*native_acos(zz2/r)); aux.DE*=(1.0f+af*comb/3.0f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_151)
						case 151: { { float de=aa*r*native_log(r+1e-21f)/fmax(ab,0.01f); aux.DE*=(1.0f+af*de/(r+1e-21f)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_152)
						case 152: { aux.DE *= fmax(0.01f, 1.0f + af * aa * r * native_sin(ab*native_log(r+1e-21f)+ac)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_153)
						case 153: { { float lip=aa*fmin(1.0f,ab/fmax(r,1e-21f)); aux.DE*=(1.0f+af*lip); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_154)
						case 154: { aux.DE *= (1.0f + af * aa * native_exp(-ab*r) * native_sin(ac*r+ad)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_155)
						case 155: { { float bess=native_sin(aa*r)/(aa*r+1e-21f); aux.DE*=(1.0f+af*ab*bess); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_156)
						case 156: { { float cheb=native_cos(aa*native_acos(fmin(1.0f,fmax(-1.0f,zz2/r)))); aux.DE*=(1.0f+af*ab*cheb); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_157)
						case 157: { { float leg=(3.0f*(zz2/r)*(zz2/r)-1.0f)*0.5f; aux.DE*=(1.0f+af*aa*leg); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_158)
						case 158: { { float herm=(4.0f*(zz2/r)*(zz2/r)-2.0f)*native_exp(-(zz2/r)*(zz2/r)*0.5f); aux.DE*=(1.0f+af*aa*ab*herm); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_159)
						case 159: { { float lag=1.0f-aa*r+aa*aa*r*r*0.5f; aux.DE*=(1.0f+af*ab*lag*native_exp(-ac*r)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_160)
						case 160: { aux.DE *= (1.0f + af * aa * native_sin(ab*r+ac) * native_sin(ad*r+ae) * native_sin(aff*r+ag)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_161)
						case 161: { { float gr=aa*r*native_exp(-ab*r*r)*native_sin(ac*r); aux.DE*=(1.0f+af*gr); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_162)
						case 162: { aux.DE *= (1.0f + af * aa * native_sin(ab*r) * tanh(ac*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_163)
						case 163: { { float sg=1.0f/(1.0f+native_exp(-aa*(r-ab))); aux.DE*=(1.0f+af*ac*sg*(1.0f-sg)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_164)
						case 164: { { float gau=native_exp(-aa*(r-ab)*(r-ab)); aux.DE*=(1.0f+af*ac*gau); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_165)
						case 165: { { float stp=(r>aa)?ab:ac; aux.DE*=(1.0f+af*stp); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_166)
						case 166: { { float bnd=aa*native_sin(native_floor(r*ab)*M_PI_F/ab); aux.DE*=(1.0f+af*bnd); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_167)
						case 167: { { float v=0; for(int o=0;o<4;o++){v+=native_sin(aa*native_pow(2.0f,o)*r+ab*o)/(native_pow(2.0f,o));} aux.DE*=(1.0f+af*ac*v); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_168)
						case 168: { { float jc=aa*native_sin(ab*r)+ac*native_sin(ad*atan2(zy,zx)); aux.DE*=(1.0f+af*jc*0.5f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_169)
						case 169: { { float tmp=aa+ab*native_sin(ac*r)*native_cos(ad*i*0.1f); aux.DE*=(1.0f+af*tmp); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_170)
						case 170: { { float fb=0; float prev=aa; float curr=ab; for(int k=0;k<6;k++){float nxt=prev+curr; fb+=native_sin(nxt*r)/(nxt+1.0f); prev=curr; curr=nxt;} aux.DE*=(1.0f+af*ac*fb); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_171)
						case 171: { { float orb=r; float v=aa*native_sin(ab*orb)+ac*native_cos(ad*orb*orb/(r+1e-21f)); aux.DE*=(1.0f+af*v); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_172)
						case 172: { aux.DE *= (1.0f + af * aa * fabs(native_sin(ab*r)) * fabs(native_cos(ac*r))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_173)
						case 173: { aux.DE *= fabs(aa); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_174)
						case 174: { aux.DE *= (1.0f + fabs(aa*M_PI_F/180.0f) * ab); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_175)
						case 175: { aux.DE *= (1.0f + fabs(aa + ab + ac)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_176)
						case 176: { aux.DE *= fmax(0.01f, aa * (float)(i) / fmax((float)(ab), 1.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_177)
						case 177: { { if(fabs(zx)>aa||fabs(zy)>aa||fabs(zz2)>aa) aux.DE*=ab; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_178)
						case 178: { { float d=native_sqrt((zx-aa)*(zx-aa)+(zy-ab)*(zy-ab)+(zz2-ac)*(zz2-ac)); if(d<ad) aux.DE*=ae; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_179)
						case 179: { { if(fabs(zx)<aa && fabs(zy)<aa) aux.DE*=ab; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_180)
						case 180: { aux.DE *= (1.0f + 0.1f * aa * fabs(native_sin(ab*r))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_181)
						case 181: { aux.DE *= (1.0f - aa * ab * native_exp(-ac*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_182)
						case 182: { aux.DE /= fmax(0.01f, 1.0f + aa * ab); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_183)
						case 183: { aux.DE *= (1.0f + aa * ab * r); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_184)
						case 184: { aux.DE /= fmax(0.01f, 1.0f + aa * ab * native_sin(ac*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_185)
						case 185: { aux.DE *= (1.0f + aa * ab * r); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_186)
						case 186: { aux.DE *= (1.0f + aa * fabs(ab - 550.0f) * 0.001f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_187)
						case 187: { aux.DE *= (1.0f + aa * fabs(native_sin(ab*zx)*native_cos(ac*zy))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_188)
						case 188: { { float fr=native_pow(fabs(1.0f-fabs(zz2)/r),5.0f); aux.DE*=(1.0f+aa*fr); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_189)
						case 189: { { float tf=native_sin(aa*r+ab)*native_cos(ac*r); aux.DE*=(1.0f+ad*fabs(tf)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_190)
						case 190: { { float an=fabs(zx*aa+zy*ab+zz2*ac)/(r+1e-21f); aux.DE*=(1.0f+ad*an); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_191)
						case 191: { aux.DE /= fmax(0.01f, 1.0f + aa * ab); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_192)
						case 192: { aux.DE *= (1.0f + aa * native_exp(-ab * r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_193)
						case 193: { aux.DE *= (1.0f + aa * ab * r); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_194)
						case 194: { aux.DE += aa * ab * native_sin(ac*zx)*native_cos(ad*zy); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_195)
						case 195: { aux.DE *= (1.0f + aa * ab * native_sin(ac*zx+ad*zy+ae*zz2)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_196)
						case 196: { aux.DE *= fmax(0.01f, aa * ab / fmax(ac, 0.01f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_197)
						case 197: { aux.DE /= fmax(0.01f, aa); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_198)
						case 198: { aux.DE *= native_exp(-aa * ab * r); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_199)
						case 199: { aux.DE *= (1.0f + aa * ab * (1.0f + ac*native_cos(ad*atan2(zy,zx)))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_200)
						case 200: { aux.DE /= fmax(0.01f, 1.0f + aa * ab); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_201)
						case 201: { { float curl=native_sin(aa*zy+ab*zz2)-native_sin(aa*zz2+ab*zx); aux.DE*=(1.0f+ac*fabs(curl)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_202)
						case 202: { { float grad=(zx*aa+zy*ab+zz2*ac)/(rr+1e-21f); aux.DE/=fmax(0.01f,1.0f+ad*fabs(grad)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_203)
						case 203: { aux.DE *= (1.0f + aa * ab / fmax(rr, 1e-21f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_204)
						case 204: { { float v2=aa*aa; float c2=ab*ab; aux.DE*=native_sqrt(fmax(0.01f,1.0f-v2/fmax(c2,1e-21f))); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_205)
						case 205: { aux.DE *= native_exp(-aa * fabs(r - ab)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_206)
						case 206: { { float psi=native_sin(aa*zx)*native_sin(ab*zy)*native_sin(ac*zz2); aux.DE*=fmax(0.01f,psi*psi); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_207)
						case 207: { aux.DE *= (1.0f + aa / fmax(2.0f * ab * r, 1e-21f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_208)
						case 208: { aux.DE *= (1.0f + aa * (zx*ab + zy*ac + zz2*ad)/(r+1e-21f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_209)
						case 209: { { float corr=native_sin(aa*zx)*native_sin(aa*(-zx))+native_cos(ab*zy)*native_cos(ab*(-zy)); aux.DE*=(1.0f+ac*fabs(corr)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_210)
						case 210: { aux.DE *= native_exp(-aa * ab * (float)(i) * 0.01f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_211)
						case 211: { { float ent=native_sin(aa*zx)*native_log(fabs(native_sin(aa*zx))+1e-21f)+native_sin(ab*zy)*native_log(fabs(native_sin(ab*zy))+1e-21f); aux.DE*=(1.0f+ac*fabs(ent)*0.1f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_212)
						case 212: { aux.DE *= (1.0f + aa / fmax(ab * ac, 1e-21f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_213)
						case 213: { { float vg=(native_sin(aa*(zx+0.01f))-native_sin(aa*zx))/0.01f; aux.DE*=(1.0f+ab*fabs(vg)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_214)
						case 214: { { float curv=(native_sin(aa*zx+0.01f)+native_sin(aa*zx-0.01f)-2.0f*native_sin(aa*zx))/0.0001f; aux.DE*=(1.0f+ab*fabs(curv)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_215)
						case 215: { aux.DE *= (1.0f + aa * native_cos(ab) / fmax(ac, 0.01f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_216)
						case 216: { { float cg=(native_sin(aa*(zx+0.01f))-native_sin(aa*zx))/0.01f; aux.DE*=(1.0f+ab*fabs(cg)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_217)
						case 217: { { float lap=native_sin(aa*(zx+0.01f))+native_sin(aa*(zx-0.01f))-2.0f*native_sin(aa*zx); aux.DE+=ab*lap; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_218)
						case 218: { { float adv=(native_sin(aa*zx)-native_sin(aa*(zx-0.01f)))/0.01f; aux.DE*=(1.0f+ab*fabs(adv)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_219)
						case 219: { { float v=0; for(int o=0;o<4;o++){v+=native_sin(aa*native_pow(2.0f,o)*r)/native_pow(2.0f,o);} aux.DE*=(1.0f+ab*fabs(v)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_220)
						case 220: { { float sh=(r>aa)?ab:0.0f; aux.DE*=(1.0f+ac*sh); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_221)
						case 221: { { float dw=aa-ab; float bw=ac*0.5f; float q=ad/fmax(native_sqrt(dw*dw+bw*bw),1e-21f); aux.DE*=(1.0f+af*q); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_222)
						case 222: { aux.DE *= (1.0f + aa * native_cos(ab * r + ac)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_223)
						case 223: { aux.DE *= (1.0f + aa / fmax(ab, 1e-21f) * native_cos(ac)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_224)
						case 224: { aux.DE *= (1.0f + aa * native_cos(2.0f * ab * atan2(zy, zx))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_225)
						case 225: { aux.DE *= (1.0f + aa * fabs(native_sin(2.0f * ab * atan2(zz2, native_sqrt(zx*zx+zy*zy+1e-21f))))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_226)
						case 226: { aux.DE *= (1.0f + aa * ab * ac); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_227)
						case 227: { { float lp=fmod(r*aa, ab); aux.DE*=(1.0f+ac*native_sin(M_PI_F*lp/fmax(ab,0.01f))); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_228)
						case 228: { { float skin=native_exp(-fabs(zz2)*aa/fmax(ab,0.01f)); aux.DE*=(1.0f+ac*skin); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_229)
						case 229: { aux.DE *= (1.0f + aa * fabs(ab)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_230)
						case 230: { { float wn=native_floor(atan2(zy,zx)*aa/(2.0f*M_PI_F)+0.5f); aux.DE*=(1.0f+ab*fabs(wn)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_231)
						case 231: { { float tc=native_floor(atan2(zy,zx)*aa/(2.0f*M_PI_F)+0.5f); aux.DE*=(1.0f+ab*fabs(tc)*native_sin(ac*r)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_232)
						case 232: { { float vort=fabs(-aa*zy/(rr+1e-21f)-(-ab*zx/(rr+1e-21f))); aux.DE*=(1.0f+ac*vort); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_233)
						case 233: { { float sw=1.0f/cosh(aa*fabs(r-ab)); aux.DE*=(1.0f+ac*sw); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_234)
						case 234: { { float inst=native_exp(-aa*(rr+1e-21f)); aux.DE*=(1.0f+ab*inst); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_235)
						case 235: { aux.DE *= (1.0f + aa / fmax(r, 1e-21f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_236)
						case 236: { { float sl=fabs(native_sqrt(zx*zx+zy*zy)); aux.DE*=(1.0f+aa*native_log(sl+1e-21f)*ab); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_237)
						case 237: { { float bd=native_exp(-aa*fabs(zz2-ab)); aux.DE*=(1.0f+ac*bd); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_238)
						case 238: { { float wh=native_exp(-(r-aa)*(r-aa)/(fmax(ab*ab,0.01f))); aux.DE*=(1.0f+ac*wh); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_239)
						case 239: { aux.DE /= fmax(0.01f, 1.0f - aa / fmax(r, aa + 1e-21f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_240)
						case 240: { { float jet=native_exp(-fabs(native_sqrt(zx*zx+zy*zy)-aa)/(fmax(ab,0.01f))); aux.DE*=(1.0f+ac*jet); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_241)
						case 241: { { float halo=1.0f/(1.0f+native_pow(r/fmax(aa,0.01f),2.0f)); aux.DE*=(1.0f+ab*halo); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_242)
						case 242: { aux.DE *= native_exp(fmin(aa * ab * r, 20.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_243)
						case 243: { { float cs2=native_log(fmax(fabs(native_sqrt(zx*zx+zy*zy)),1e-21f)/fmax(aa,0.01f)); aux.DE*=(1.0f+ab*ac*cs2); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_244)
						case 244: { aux.DE *= (1.0f + aa * tanh(fabs(zz2 - ab) / fmax(ac, 0.01f))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_245)
						case 245: { { float ylm=native_sin(aa*native_acos(zz2/r))*native_cos(ab*atan2(zy,zx)); aux.DE*=(1.0f+ac*fabs(ylm)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_246)
						case 246: { aux.DE *= native_exp(aa * ab); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_247)
						case 247: { { float rh=aa*ab*native_exp(-ac*(float)(i)*0.01f); aux.DE*=(1.0f+rh); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_248)
						case 248: { { float ns=aa*ab*native_sin(ac*r)/(1.0f+ad*r); aux.DE*=(1.0f+ns); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_249)
						case 249: { { float rc=aa*native_exp(-ab/(fmax(ac*r,0.01f))); aux.DE*=(1.0f+rc); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_250)
						case 250: { { float sf2=1.0f+aa*r; aux.DE*=sf2*native_sqrt(fmax(0.01f,ab*ac/(fmax(r,1e-21f)))); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_251)
						case 251: { { float sf2=fmax(0.01f,1.0f+aa*r); aux.DE/=sf2; } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_252)
						case 252: { aux.DE *= (1.0f + aa * (1.0f - native_exp(-(float)(i) * 0.01f / fmax(ab, 0.01f)))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_253)
						case 253: { { float bn=native_exp(-aa*rr)*ab; aux.DE*=(1.0f+bn); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_254)
						case 254: { { float fv=aa*native_exp(-ab*rr); aux.DE*=(1.0f+fv); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_255)
						case 255: { { float op=native_sin(aa*r)*native_sin(aa*r); aux.DE*=(1.0f+ab*op); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_256)
						case 256: { { float d=fabs(r-aa); aux.DE*=fmax(0.01f,native_pow(d+1e-21f,-ab)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_257)
						case 257: { aux.DE *= (1.0f + aa * native_log(fmax(ab, 0.01f) / fmax(r, 1e-21f))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_258)
						case 258: { { float div=(native_sin(aa*(zx+0.01f))-native_sin(aa*zx))/0.01f; aux.DE*=(1.0f+ab*fabs(div)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_259)
						case 259: { { float vev=aa*r*r; aux.DE*=(1.0f+ab*vev); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_260)
						case 260: { { float grd=(native_sin(aa*(r+0.01f))-native_sin(aa*r))/0.01f; aux.DE*=(1.0f+ab*fabs(grd)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_261)
						case 261: { aux.DE *= (1.0f + aa * ab * rr); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_262)
						case 262: { { float a2=native_sin(aa*zx)*native_sin(aa*zx)+native_sin(ab*zy)*native_sin(ab*zy); aux.DE*=(1.0f+ac*ad*a2); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_263)
						case 263: { { float psi2=native_sin(aa*r)*native_sin(aa*r); aux.DE*=(1.0f+ab*psi2); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_264)
						case 264: { { float phi=native_sin(aa*r); aux.DE*=(1.0f+ab*phi*phi+ac*phi*phi*phi*phi); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_265)
						case 265: { { float tmn=(zx*zx+zy*zy+zz2*zz2)/(rr+1e-21f); aux.DE*=(1.0f+aa*ab*tmn); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_266)
						case 266: { { float sp=native_sin(aa*zx)*native_cos(ab*zy); aux.DE*=(1.0f+ac*fabs(sp)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_267)
						case 267: { { float rs=native_sin(aa*r)*fabs(native_cos(ab*atan2(zy,zx))); aux.DE*=(1.0f+ac*rs*rs); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_268)
						case 268: { { float kr=native_sin(aa*zx)*native_sin(ab*zy)-native_cos(aa*zx)*native_cos(ab*zy); aux.DE*=(1.0f+ac*kr*kr); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_269)
						case 269: { { float gv=native_sin(aa*r)*native_sin(ab*r); aux.DE*=(1.0f+ac*gv*gv); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_270)
						case 270: { { float xs=fabs(native_sin(aa*r)-zx); aux.DE*=(1.0f+ab*xs*xs); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_271)
						case 271: { { float m5=native_sin(aa*r)*native_sin(ab*r)*native_sin(ac*r); aux.DE*=(1.0f+ad*m5*m5); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_272)
						case 272: { { float wf2=native_exp(-aa*fabs(zz2)); aux.DE*=(1.0f+ab*ac*wf2); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_273)
						case 273: { { float kk=native_sin(aa*r/fmax(ab,0.01f))*native_sin(ac*r/fmax(ab,0.01f)); aux.DE*=(1.0f+ad*kk); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_274)
						case 274: { aux.DE *= native_exp(-aa * fabs(zz2 - ab)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_275)
						case 275: { { float av=r>1e-21f?(fabs(zx)+fabs(zy)+fabs(zz2))/(r):1.0f; aux.DE*=(1.0f+aa*ab*av); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_276)
						case 276: { { float cf=1.0f/(1.0f+aa*rr); aux.DE*=(1.0f+ab*cf); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_277)
						case 277: { { float ms=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.DE*=(1.0f+aa*ms); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_278)
						case 278: { { float fw=native_exp(-aa*fabs(r-ab)*fabs(r-ab)*1000.0f); aux.DE*=(1.0f+ac*fw); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_279)
						case 279: { { float ee=native_sin(aa*zx)*native_sin(aa*(-zx+ab)); aux.DE*=(1.0f+ac*fabs(ee)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_280)
						case 280: { { float vol=r*r*r; aux.DE*=(1.0f+aa*vol/(vol+ab+1e-21f)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_281)
						case 281: { { float ly=native_exp(aa*(float)(i)*0.01f); aux.DE*=(1.0f+ab*fmin(ly,ac)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_282)
						case 282: { { float bv=fabs(zx-aa*native_sin(ab*zy))/((float)(i)+1.0f); aux.DE*=(1.0f+ac*bv); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_283)
						case 283: { { float scr=native_log(fmax(aa,1.0f))*ab*native_sin(ac*r); aux.DE*=(1.0f+fabs(scr)*0.01f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_284)
						case 284: { { float sff=native_sin(aa*(float)(i)*0.1f)*native_sin(ab*(float)(i)*0.1f); aux.DE*=(1.0f+ac*fabs(sff)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_285)
						case 285: { { float goe=native_sin(aa*r)*native_cos(ab*r)*native_sin(ac*r); aux.DE*=(1.0f+ad*fabs(goe)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_286)
						case 286: { { float syk=native_sin(aa*zx)*native_sin(ab*zy)*native_sin(ac*zz2)*native_sin(ad*r); aux.DE*=(1.0f+ae*fabs(syk)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_287)
						case 287: { { float bd2=native_sin(aa*r)*native_sin(aa*r); float ent=bd2*native_log(bd2+1e-21f); aux.DE*=(1.0f+ab*fabs(ent)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_288)
						case 288: { { float ml=native_floor(native_log(r+1e-21f)/native_log(fmax(aa,1.01f))); aux.DE*=(1.0f+ab*native_sin(ac*ml)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_289)
						case 289: { { float cd=native_floor(r*aa); float le=native_exp(-ab*cd); aux.DE*=(1.0f+ac*le); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_290)
						case 290: { { float wn2=native_floor(atan2(zy,zx)*aa/(2.0f*M_PI_F)+0.5f); aux.DE*=(1.0f+ab*native_sin(ac*wn2)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_291)
						case 291: { { float sw2=native_floor(zx*aa+0.5f)*native_floor(zy*ab+0.5f); aux.DE*=(1.0f+ac*native_sin(ad*sw2)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_292)
						case 292: { { float cc=native_floor(r*aa)*3.0f; aux.DE*=(1.0f+ab*native_sin(ac*cc)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_293)
						case 293: { { float pc=fmod(native_floor(r*aa),ab); aux.DE*=(1.0f+ac*native_sin(ad*pc)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_294)
						case 294: { { float ce=native_sin(aa*zx)*native_cos(ab*zy)*native_sin(ac*zz2); aux.DE*=(1.0f+ad*fabs(ce)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_295)
						case 295: { { float ev=native_sin(aa*r)*native_sin(aa*r)+native_cos(ab*r)*native_cos(ab*r); aux.DE*=(1.0f+ac*ev*0.5f); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_296)
						case 296: { { float sgn=native_sin(aa*r)>0?1.0f:-1.0f; float mc=native_exp(-ab*rr)*sgn; aux.DE*=(1.0f+ac*fabs(mc)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_297)
						case 297: { { float pur=native_sin(aa*r)*native_sin(aa*r); aux.DE*=(1.0f+ab*pur*pur); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_298)
						case 298: { { float wig=native_sin(aa*zx)*native_cos(ab*zy); aux.DE*=(1.0f+ac*fabs(wig)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_299)
						case 299: { { float hus=native_exp(-aa*(zx*zx+zy*zy))*native_sin(ab*r); aux.DE*=(1.0f+ac*fabs(hus)); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_300)
						case 300: { { float mi=native_sin(aa*r)*native_sin(ab*r); aux.DE*=(1.0f+ac*mi*mi); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_301)
						case 301: { float psi = native_sin(aa*r + ab*z.x); aux.DE *= (1.0f + af * psi*psi); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_302)
						case 302: { float psi_f = native_cos(aa*r); float psi_i = native_sin(ab*r); float overlap = psi_f*psi_i + 1e-21f; float wv = (psi_f*native_sin(ac*z.x)) / overlap; aux.DE *= (1.0f + af * fabs(wv)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_303)
						case 303: { float rate = fabs(aa); float variance = z.x*z.x + z.y*z.y; aux.DE *= (1.0f + af * native_exp(-rate * (float)i * 0.01f * variance)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_304)
						case 304: { float E = aa*r; float t = (float)i * 0.01f; aux.DE *= (1.0f + af * fabs(ab) * native_sin(E*t)*native_sin(E*t)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_305)
						case 305: { float path1 = native_sin(aa*z.x + ab*z.y); float path2 = native_sin(ac*z.x - ab*z.y); aux.DE *= (1.0f + af * fabs(path1 - path2)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_306)
						case 306: { float choice_time = fabs(aa) * 10.0f; float theta = (float)i > choice_time ? 1.0f : 0.0f; aux.DE *= (1.0f + af * ab * theta); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_307)
						case 307: { float visibility = native_cos(aa*r)*native_cos(aa*r); float erased = native_sin(ab*z.x + ac*z.y); aux.DE *= (1.0f + af * visibility * erased*erased); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_308)
						case 308: { float source = native_sin(aa*z.x + ab*z.y + ac*z.z); float target = native_sin(aa*(z.x+ad) + ab*(z.y+ae) + ac*(z.z+aff)); float fidelity = source*target; aux.DE *= (1.0f + af * fabs(fidelity)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_309)
						case 309: { float psi = native_sin(aa*r); float clone = native_sin(aa*r + ab*0.1f); float fidelity = 1.0f - (psi-clone)*(psi-clone)*0.5f; aux.DE *= (1.0f + af * fmax(fidelity, 0.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_310)
						case 310: { float Iz = native_sin(aa*z.x)*native_sin(ab*z.y); float classical = native_sin(aa*z.x)*0.5f; float discord = fabs(Iz - classical); aux.DE *= (1.0f + af * discord); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_311)
						case 311: { float epr = native_sin(aa*z.x)*native_cos(ab*z.y) - native_cos(aa*z.x)*native_sin(ab*z.y); aux.DE *= (1.0f + af * fabs(epr)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_312)
						case 312: { float v1 = native_sin(aa*z.x)*native_sin(aa*z.y); float v2 = native_cos(ab*z.y)*native_cos(ab*z.z); float violation = fabs(v1 + v2) - 1.0f; aux.DE *= (1.0f + af * fmax(violation, 0.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_313)
						case 313: { float ca = native_cos(aa*z.x); float cb = native_cos(ab*z.y); float corr = ca*cb + ca*native_sin(ab*z.y) + native_sin(aa*z.x)*cb - native_sin(aa*z.x)*native_sin(ab*z.y); aux.DE *= (1.0f + af * fabs(corr) * 0.25f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_314)
						case 314: { float S = 2.0f*native_sqrt(2.0f)*native_sin(aa*r)*native_cos(ab*r); float violation = fmax(fabs(S) - 2.0f, 0.0f); aux.DE *= (1.0f + af * violation); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_315)
						case 315: { float bound = 2.0f*native_sqrt(2.0f); float corr = bound * native_cos(aa*r) * native_sin(ab*z.x); aux.DE *= (1.0f + af * fabs(corr) / bound); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_316)
						case 316: { float t1 = native_sin(aa*(float)i*0.1f); float t2 = native_sin(aa*((float)i+ab)*0.1f); float temporal = t1*t2 + t1*native_sin(aa*((float)i+ac)*0.1f); aux.DE *= (1.0f + af * fabs(temporal)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_317)
						case 317: { float rho = native_sin(aa*z.x)*native_sin(aa*z.x) + native_cos(ab*z.y)*native_cos(ab*z.y); float witness = rho - ac; aux.DE *= (1.0f + af * fmax(-witness, 0.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_318)
						case 318: { float dpsi = aa*native_cos(aa*r + ab*z.x); float fisher = 4.0f*dpsi*dpsi; aux.DE *= (1.0f + af * fisher / (1.0f + fisher)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_319)
						case 319: { float F_Q = 4.0f*(aa*native_cos(aa*r))*(aa*native_cos(aa*r)); float bound = 1.0f/native_sqrt(fmax(ab*F_Q, 1e-21f)); aux.DE *= (1.0f + af * bound); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_320)
						case 320: { float N = fmax(fabs(aa)*10.0f, 1.0f); float dphi = 1.0f/(N*native_sqrt(fmax(fabs(ab), 1e-21f))); float sql = 1.0f/native_sqrt(N); float gain = (sql*sql)/(dphi*dphi+1e-21f); aux.DE *= (1.0f + af * fmin(gain, 10.0f) * native_sin(ac*r)*native_sin(ac*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_321)
						case 321: { float T2 = fabs(aa) + 0.01f; float sensitivity = 1.0f/(ab*native_sqrt(T2)+1e-21f); aux.DE *= (1.0f + af * native_sin(ac*r)*native_sin(ac*r) * fmin(sensitivity, 10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_322)
						case 322: { float lambda_r = fabs(aa)+0.1f; float NA = fabs(ab)+0.1f; float N_ph = fmax(fabs(ac)*10, 1.0f); float res = lambda_r/(2.0f*NA*native_sqrt(N_ph)); aux.DE *= (1.0f + af * native_sin(r/fmax(res,0.01f))*native_sin(r/fmax(res,0.01f))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_323)
						case 323: { float N = fmax(fabs(aa)*5, 1.0f); float pattern = native_sin(N*ab*z.x)*native_sin(N*ab*z.y); aux.DE *= (1.0f + af * pattern*pattern); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_324)
						case 324: { float snr_q = native_exp(-aa*r*r); float snr_c = native_exp(-ab*r*r); float advantage = snr_q/(snr_c+1e-21f); aux.DE *= (1.0f + af * fmin(advantage, 10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_325)
						case 325: { float tau = fabs(aa)*r; float N_s = fmax(fabs(ab), 0.1f); float N_i = fmax(fabs(ac), 0.1f); float range_res = tau/(2.0f*native_sqrt(N_s*N_i)+1e-21f); aux.DE *= (1.0f + af * native_sin(range_res)*native_sin(range_res)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_326)
						case 326: { float omega_rot = aa*z.x + ab*z.y; float phase = ac*omega_rot; aux.DE *= (1.0f + af * native_sin(phase)*native_sin(phase)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_327)
						case 327: { float g_eff = aa; float T = fabs(ab)+0.01f; float phase = g_eff*T*T*ac; aux.DE *= (1.0f + af * native_cos(phase)*native_cos(phase)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_328)
						case 328: { float omega0 = fabs(aa)*100.0f+1.0f; float tau_c = fabs(ab)+0.01f; float stability = 1.0f/(omega0*native_sqrt(tau_c*(float)(i+1)*0.01f)+1e-21f); aux.DE *= (1.0f + af * fmin(stability*ac, 5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_329)
						case 329: { float B = aa*z.x + ab*z.y + ac*z.z; float sensitivity = native_sin(ad*B); aux.DE *= (1.0f + af * sensitivity*sensitivity); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_330)
						case 330: { float k_eff = aa; float T = fabs(ab)+0.01f; float accel = k_eff*T*T*ac*r; aux.DE *= (1.0f + af * native_sin(accel)*native_sin(accel)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_331)
						case 331: { float T_eff = fabs(aa)*r + 0.01f; float C = fabs(ab)+0.1f; float dE = fabs(ac)+0.01f; float res = T_eff*T_eff/(C*dE); aux.DE *= (1.0f + af * fmin(res, 10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_332)
						case 332: { float pressure = aa*r*r + ab*z.x; float sensitivity = native_sin(ac*pressure); aux.DE *= (1.0f + af * sensitivity*sensitivity); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_333)
						case 333: { float dL = aa*(z.x - z.y); float L = fmax(r, 0.01f); float strain = dL/L; float gauge = ab*strain; aux.DE *= (1.0f + af * native_sin(gauge)*native_sin(gauge)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_334)
						case 334: { float omega0 = fabs(aa)+0.1f; float Q = fabs(ab)+1.0f; float force = ac/(2.0f*Q*omega0+1e-21f); aux.DE *= (1.0f + af * native_sin(force*r)*native_sin(force*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_335)
						case 335: { float torque = aa*z.x*z.y - ab*z.y*z.z; float thermal = fabs(ac)+0.01f; aux.DE *= (1.0f + af * fabs(torque)/(thermal+fabs(torque))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_336)
						case 336: { float E_field = aa*z.x + ab*z.y + ac*z.z; float rydberg = native_sin(ad*E_field*E_field); aux.DE *= (1.0f + af * rydberg*rydberg); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_337)
						case 337: { float V_jj = aa*native_sin(ab*r); float josephson = native_cos(ac*V_jj); aux.DE *= (1.0f + af * (1.0f - josephson*josephson)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_338)
						case 338: { float tunnel = native_exp(-aa*fabs(r-ab)); float current = ac*tunnel; aux.DE *= (1.0f + af * fabs(current)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_339)
						case 339: { float n = native_floor(fabs(aa)*r*5.0f+0.5f); float R_H = 1.0f/(fmax(n,1.0f)*ab+1e-21f); aux.DE *= (1.0f + af * fmin(R_H, 10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_340)
						case 340: { float C_q = aa*aa/(2.0f*(fabs(ab)+0.01f)); float charging = native_exp(-C_q*r*r); aux.DE *= (1.0f + af * charging); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_341)
						case 341: { float flux = aa*z.x*z.y; float inductance = native_cos(ab*flux); aux.DE *= (1.0f + af * inductance*inductance); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_342)
						case 342: { float L_q = fabs(aa)+0.01f; float C_q = fabs(ab)+0.01f; float Z = native_sqrt(L_q/C_q); float match = 1.0f/(1.0f + (Z-ac)*(Z-ac)); aux.DE *= (1.0f + af * match); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_343)
						case 343: { float omega = aa*r; float n_th = 1.0f/(native_exp(fabs(ab)*omega+1e-21f)-1.0f+1e-21f); float psd = omega*(n_th+0.5f); aux.DE *= (1.0f + af * fmin(fabs(psd), 10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_344)
						case 344: { float dE = fabs(aa)*r; float tau = fmax(fabs(ab),0.01f); float uncertainty = dE*tau; aux.DE *= (1.0f + af * native_exp(-uncertainty)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_345)
						case 345: { float W = aa*r*r; float T_eff = fmax(fabs(ab), 0.01f); float jarzynski = native_exp(-W/T_eff); aux.DE *= (1.0f + af * jarzynski); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_346)
						case 346: { float Q_heat = aa*r; float T_eff = fmax(fabs(ab), 0.01f); float C = fmax(fabs(ac), 0.01f); float fluct = Q_heat/(T_eff*T_eff*C+1e-21f); aux.DE *= (1.0f + af * native_exp(-fabs(fluct))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_347)
						case 347: { float sigma = fabs(aa)*r*r; float relax = fmax(fabs(ab), 0.01f); float prod = sigma/relax; aux.DE *= (1.0f + af * (1.0f - native_exp(-prod))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_348)
						case 348: { float W = aa*(z.x*z.x + z.y*z.y); float T_eff = fmax(fabs(ab), 0.01f); float ratio = native_exp(-W/T_eff); aux.DE *= (1.0f + af * fmin(ratio, 10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_349)
						case 349: { float info = fabs(native_sin(aa*z.x)*native_cos(ab*z.y)); float work = ac*info*native_log(2.0f); aux.DE *= (1.0f + af * fabs(work)/(1.0f+fabs(work))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_350)
						case 350: { float W = fabs(aa)*native_log(2.0f)*native_sin(ab*r)*native_sin(ab*r); aux.DE *= (1.0f + af * W); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_351)
						case 351: { float T_hot = fmax(fabs(aa)*r, 0.01f); float T_cold = fmax(fabs(ab)*0.5f, 0.001f); float eff = 1.0f - T_cold/T_hot; float qcorr = native_sin(ac*r)*native_sin(ac*r); aux.DE *= (1.0f + af * fabs(eff) * qcorr); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_352)
						case 352: { float w_cold = fabs(aa)+0.1f; float w_hot = fabs(ab)+0.2f; float eff = 1.0f - w_cold/w_hot; float adiabatic = native_cos(ac*r)*native_cos(ac*r); aux.DE *= (1.0f + af * fabs(eff) * adiabatic); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_353)
						case 353: { float V_ratio = fmax(fabs(aa), 0.1f)/fmax(fabs(ab), 0.1f); float T_ratio = fmax(fabs(ac), 0.1f)/fmax(fabs(ad), 0.1f); float eff = native_log(fmax(V_ratio,1e-21f))/(native_log(fmax(T_ratio,1e-21f))+1e-21f); aux.DE *= (1.0f + af * fmin(fabs(eff), 5.0f) * native_sin(r)*native_sin(r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_354)
						case 354: { float gamma_g = 1.4f; float ratio = fmax(fabs(aa), 0.1f); float eff = 1.0f - (native_pow(ratio, gamma_g)-1.0f)/(gamma_g*(ratio-1.0f)+1e-21f); aux.DE *= (1.0f + af * fabs(eff) * native_sin(ab*r)*native_sin(ab*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_355)
						case 355: { float P_ratio = fmax(fabs(aa), 0.1f); float gamma_g = 1.4f; float eff = 1.0f - native_pow(1.0f/P_ratio, (gamma_g-1.0f)/gamma_g); aux.DE *= (1.0f + af * fabs(eff) * native_cos(ab*r)*native_cos(ab*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_356)
						case 356: { float T_ratio = fmax(fabs(aa)+0.1f, 0.01f) / fmax(fabs(ab)+0.1f, 0.01f); float regen = fmin(fabs(ac), 1.0f); float eff = (1.0f - 1.0f/T_ratio) * regen; aux.DE *= (1.0f + af * fabs(eff)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_357)
						case 357: { float expansion = fmax(fabs(aa), 0.1f); float T_ratio = fmax(fabs(ab)+0.1f, 0.01f)/fmax(fabs(ac)+0.1f, 0.01f); float eff = (1.0f - 1.0f/T_ratio)*expansion/(expansion+1.0f); aux.DE *= (1.0f + af * fabs(eff) * native_sin(ad*r)*native_sin(ad*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_358)
						case 358: { float T_ratio = fmax(fabs(aa)+0.1f,0.01f)/fmax(fabs(ab)+0.1f,0.01f); float loss = 1.0f-fmin(fabs(ac),0.99f); float eff = (1.0f-1.0f/T_ratio)*loss; aux.DE *= (1.0f + af * fabs(eff) * native_cos(ad*r)*native_cos(ad*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_359)
						case 359: { float T_cold = fmax(fabs(aa),0.01f); float T_hot = fmax(fabs(ab),0.02f); float cop = T_cold/(T_hot-T_cold+1e-21f); float qcop = cop*native_sin(ac*r)*native_sin(ac*r); aux.DE *= (1.0f + af * fmin(fabs(qcop),10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_360)
						case 360: { float T_hot = fmax(fabs(aa),0.02f); float T_cold = fmax(fabs(ab),0.01f); float cop = T_hot/(T_hot-T_cold+1e-21f); float enhance = native_cos(ac*r)*native_cos(ac*r); aux.DE *= (1.0f + af * fmin(cop*enhance,10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_361)
						case 361: { float k = aa; float Gamma = fabs(ab)+0.01f; float delta = fabs(ac)+0.01f; float cooling = Gamma/(2.0f*(1.0f + 4.0f*delta*delta/(Gamma*Gamma))); aux.DE *= (1.0f + af * cooling * native_sin(k*r)*native_sin(k*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_362)
						case 362: { float U0 = aa; float delta = fabs(ab)+0.01f; float pol_grad = native_sin(ac*z.x)*native_cos(ac*z.y); float eff = U0/(delta+1e-21f)*pol_grad*pol_grad; aux.DE *= (1.0f + af * fmin(fabs(eff),10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_363)
						case 363: { float T_ratio = fmax(fabs(aa),0.01f)/fmax(fabs(ab),0.01f); float eta = fabs(ac)+1.0f; float eff = native_pow(T_ratio, 3.0f)*eta; aux.DE *= (1.0f + af * fmin(fabs(eff),10.0f) * native_sin(r)*native_sin(r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_364)
						case 364: { float m_ratio = fmax(fabs(aa),0.1f)/fmax(fabs(ab),0.1f); float collision = fabs(ac); float eff = m_ratio*collision; aux.DE *= (1.0f + af * fmin(eff,10.0f) * native_sin(ad*r)*native_sin(ad*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_365)
						case 365: { float eta = fabs(aa)*0.1f; float Omega = fabs(ab)+0.1f; float nu_m = fabs(ac)+0.1f; float eff = eta*Omega*Omega/((fabs(ad)+0.01f)*nu_m); aux.DE *= (1.0f + af * fmin(eff,10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_366)
						case 366: { float Sxy = native_sin(aa*z.x)*native_cos(ab*z.y); float Sxx = native_sin(aa*z.x)*native_sin(aa*z.x)+0.01f; float Syy = native_cos(ab*z.y)*native_cos(ab*z.y)+0.01f; float gain = Sxy*Sxy/(Sxx*Syy); aux.DE *= (1.0f + af * fabs(gain)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_367)
						case 367: { float g = fabs(aa)+0.01f; float kappa = fabs(ab)+0.01f; float delta = fabs(ac)+0.01f; float cooling = g*g/(kappa*kappa+delta*delta); float n_ph = native_sin(ad*r)*native_sin(ad*r)*10.0f; aux.DE *= (1.0f + af * cooling*fmin(n_ph,10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_368)
						case 368: { float Cg = fabs(aa)+0.01f; float Vg = ab; float C = fabs(ac)+0.01f; float coupling = Cg*Vg/C; aux.DE *= (1.0f + af * native_sin(coupling*r)*native_sin(coupling*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_369)
						case 369: { float S = aa; float sigma = fabs(ab)+0.01f; float T_eff = fabs(ac)*r+0.01f; float kappa = fabs(ad)+0.01f; float ZT = S*S*sigma*T_eff/kappa; aux.DE *= (1.0f + af * fmin(ZT,10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_370)
						case 370: { float Ss = aa; float gradT = ab*z.x+ac*z.y; float spin_pol = native_sin(ad*r); aux.DE *= (1.0f + af * fabs(Ss*gradT*spin_pol)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_371)
						case 371: { float Bz = aa; float gradT = ab*z.x; float Ey = ac*gradT*Bz; aux.DE *= (1.0f + af * native_sin(Ey)*native_sin(Ey)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_372)
						case 372: { float n_level = native_floor(fabs(aa)*r*5.0f+0.5f); float conductance = fmax(n_level,1.0f)*ab; aux.DE *= (1.0f + af * fmin(fabs(conductance),10.0f) * native_sin(ac*r)*native_sin(ac*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_373)
						case 373: { float edge = native_exp(-aa*fabs(z.x)); float helical = native_sin(ab*z.y); aux.DE *= (1.0f + af * edge * helical*helical); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_374)
						case 374: { float chern = native_floor(fabs(aa)*2.0f+0.5f); float mag_order = native_sin(ab*z.x)*native_sin(ab*z.y); aux.DE *= (1.0f + af * fabs(chern) * mag_order*mag_order); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_375)
						case 375: { float valley = native_sin(aa*z.x)*native_cos(ab*z.y) - native_cos(aa*z.x)*native_sin(ab*z.y); float broken_inv = native_sin(ac*r); aux.DE *= (1.0f + af * fabs(valley*broken_inv)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_376)
						case 376: { float bulk_gap = fabs(aa); float surface = native_sin(ab*z.x)*native_sin(ab*z.y)*native_exp(-ac*fabs(z.z)); float k_F = ad*r; aux.DE *= (1.0f + af * bulk_gap*fabs(surface)*fmin(k_F,5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_377)
						case 377: { float kx = aa*z.x; float ky = ab*z.y; float kz = ac*z.z; float chirality = kx*kx + ky*ky - kz*kz; float fermi_arc = native_exp(-fabs(chirality)*ad); aux.DE *= (1.0f + af * fermi_arc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_378)
						case 378: { float E_D = aa; float v_F = fabs(ab)+0.01f; float k = ac*r; float cone = fabs(E_D)/(v_F*fmax(fabs(k),0.01f)); aux.DE *= (1.0f + af * fmin(cone,10.0f) * native_sin(r)*native_sin(r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_379)
						case 379: { float xi = fmax(fabs(aa),0.01f); float L = fabs(ab)*r; float overlap = native_exp(-L/xi); float gap = fabs(ac); aux.DE *= (1.0f + af * overlap*gap); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_380)
						case 380: { float J = fabs(aa)+0.01f; float alpha = fabs(ab)+0.01f; float g = fabs(ac)+0.01f; float gap = J*native_exp(-1.0f/(alpha*g)); aux.DE *= (1.0f + af * gap * native_sin(ad*r)*native_sin(ad*r)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_381)
						case 381: { float J = fabs(aa)+0.01f; float h = fabs(ab)+0.01f; float gap = fabs(J-h)/J; float crit_exp = fabs(ac)+0.5f; aux.DE *= (1.0f + af * native_pow(fmax(gap,1e-10f), crit_exp)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_382)
						case 382: { float J = aa; float Si = native_sin(ab*z.x); float Sj = native_sin(ab*z.y); float coupling = J*Si*Sj; aux.DE *= (1.0f + af * fabs(coupling)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_383)
						case 383: { float J = aa; float Sx = native_sin(ab*z.x)*native_cos(ac*z.y); float Sy = native_cos(ab*z.x)*native_sin(ac*z.y); float coupling = J*(Sx+Sy); aux.DE *= (1.0f + af * fabs(coupling)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_384)
						case 384: { float J = aa; float q = fmax(native_floor(fabs(ab)*5+2), 2.0f); float sigma_i = native_floor(native_sin(ac*z.x)*q); float sigma_j = native_floor(native_sin(ac*z.y)*q); float delta_s = (sigma_i == sigma_j) ? 1.0f : 0.0f; aux.DE *= (1.0f + af * J*delta_s); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_385)
						case 385: { float J = aa; float q = fmax(native_floor(fabs(ab)*5+2), 2.0f); float angle = 2.0f*M_PI_F/q; float sigma_diff = native_sin(ac*z.x) - native_sin(ac*z.y); aux.DE *= (1.0f + af * J*native_cos(angle*sigma_diff)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_386)
						case 386: { float J = aa; float lambda = ab; float sigma = native_sin(ac*z.x)*native_sin(ac*z.y); float tau = native_cos(ad*z.x)*native_cos(ad*z.y); float coupling = J*(sigma + tau + lambda*sigma*tau); aux.DE *= (1.0f + af * fabs(coupling)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_387)
						case 387: { float W = aa; float X = ab; float Y = ac; float sigma = native_sin(ad*z.x)*native_sin(ad*z.y); float tau = native_cos(ad*z.x)*native_cos(ad*z.y); float v = W*sigma + X*tau + Y*sigma*tau; aux.DE *= (1.0f + af * fabs(v)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_388)
						case 388: { float U = fabs(aa)+0.01f; float t = fabs(ab)+0.01f; float n_up = native_sin(ac*z.x)*native_sin(ac*z.x); float n_down = native_cos(ac*z.y)*native_cos(ac*z.y); float mott = U*n_up*n_down/t; aux.DE *= (1.0f + af * fmin(mott,10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_389)
						case 389: { float t = fabs(aa)+0.01f; float J = ab; float hop = t*native_sin(ac*z.x)*native_cos(ac*z.y); float exchange = J*native_sin(ad*z.x)*native_sin(ad*z.y); aux.DE *= (1.0f + af * fabs(hop + exchange)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_390)
						case 390: { float xi_loc = fmax(fabs(aa),0.01f); float disorder = fabs(ab); float loc = native_exp(-r/xi_loc)*disorder; aux.DE *= (1.0f + af * loc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_391)
						case 391: { float U = fabs(aa)+0.01f; float U_c = fabs(ab)+0.01f; float n = native_sin(ac*r)*0.5f+0.5f; float gap = (U/U_c)*(n-0.5f)*(n-0.5f); aux.DE *= (1.0f + af * fmin(gap*4.0f,10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_392)
						case 392: { float alpha = aa; float u = ab; float k_F = ac; float gap = 2.0f*fabs(alpha*u)*fabs(native_cos(2.0f*k_F*z.x)); aux.DE *= (1.0f + af * fmin(gap,10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_393)
						case 393: { float J = fabs(aa)+0.01f; float g = fabs(ab)+0.01f; float gap = J*native_exp(-M_PI_F*J/(g*g)); float singlet = native_cos(ac*z.x)*native_cos(ac*z.y); aux.DE *= (1.0f + af * gap*singlet*singlet); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_394)
						case 394: { float J = fabs(aa)+0.01f; float S = fmax(native_floor(fabs(ab)+1),1.0f); float gap = J*native_exp(-M_PI_F*S); float string_order = native_sin(ac*r); aux.DE *= (1.0f + af * gap*string_order*string_order); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_395)
						case 395: { float J = fabs(aa)+0.01f; float SiSj = native_sin(ab*z.x)*native_sin(ab*z.y); float SiSj2 = SiSj*SiSj; float aklt = J*(SiSj + SiSj2/3.0f); aux.DE *= (1.0f + af * fabs(aklt)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_396)
						case 396: { float J = fabs(aa)+0.01f; float Av = native_sin(ab*z.x)*native_sin(ab*z.y); float Bp = native_cos(ac*z.x)*native_cos(ac*z.y); float toric = 4.0f*J*(Av*Av + Bp*Bp); aux.DE *= (1.0f + af * fmin(toric,10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_397)
						case 397: { float F1 = native_sin(aa*z.x); float F2 = native_sin(ab*z.y); float F3 = native_cos(ac*z.x); float F4 = native_cos(ad*z.y); float wen = F1*F2*F3*F4; aux.DE *= (1.0f + af * fabs(wen)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_398)
						case 398: { float sn = native_sin(aa*z.x+ab*z.y); float fusion = sn*sn; float F_sym = native_cos(ac*r)*native_cos(ac*r); float lw = fusion*F_sym; aux.DE *= (1.0f + af * lw); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_399)
						case 399: { float psi = native_sin(aa*z.x + ab*(float)i*0.1f); float coin = native_cos(ac*z.y); float walker = psi*psi*coin*coin; aux.DE *= (1.0f + af * walker); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ABOXTYPE_400)
						case 400: { float rule = native_sin(aa*z.x)*native_sin(ab*z.y)*native_cos(ac*z.z); float evolution = native_cos(ad*(float)i*0.1f); float qca = rule*evolution; aux.DE *= (1.0f + af * qca*qca); break; }
#endif

					default: break;
#endif
					}
					float ab_blend = clamp(mut->aboxWeight * mut->masterWeight, 0.0f, 1.0f);
					aux.DE = de_orig_ab + (aux.DE - de_orig_ab) * ab_blend;
				}


			// v7.10 [GPU] — Noise & Procedural DE system (per-section iteration range)
			if (i >= mut->noiseIterStart && i < mut->noiseIterStop && mut->noiseType != 0)
			{
				float na = mut->noiseParamA, nb = mut->noiseParamB, nc = mut->noiseParamC, nd = mut->noiseParamD;
				float nf = mut->noiseFactor * mut->noiseWeight * mut->masterWeight, nfq = mut->noiseFreq, nam = mut->noiseAmp;
				float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
				switch(mut->noiseType) {
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_1)
					case 1: { float h = native_sin(na*z.x*12.9898 + nb*z.y*78.233 + nc*z.z*45.164)*43758.5453; h = h - floor(h); aux.DE *= (1.0 + nf*h); break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_2)
					case 2: { float h1 = native_sin(na*z.x*12.9898 + z.y*78.233)*43758.5453; h1=h1-floor(h1); { float h2 = native_sin(z.y*12.9898 + na*z.z*78.233)*43758.5453; h2=h2-floor(h2); aux.DE *= (1.0 + nf*(h1+h2)*0.5); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_3)
					case 3: { float p = na*z.x + nb*z.y + nc*z.z, h = native_sin(p*127.1)*43758.5453; h=h-floor(h); { float h2 = native_sin(p*269.5)*43758.5453; h2=h2-floor(h2); aux.DE *= (1.0 + nf*fabs(h-h2)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_4)
					case 4: { float fx = z.x*nfq, fy = z.y*nfq, fz = z.z*nfq, ix = floor(fx), iy = floor(fy), iz = floor(fz), tx = fx-ix, ty = fy-iy, tz = fz-iz, h000 = native_sin(ix*127.1+iy*311.7+iz*74.7)*43758.5453; h000=h000-floor(h000); { float h100 = native_sin((ix+1)*127.1+iy*311.7+iz*74.7)*43758.5453; h100=h100-floor(h100); float v = h000*(1.0-tx) + h100*tx; aux.DE *= (1.0 + nf*v); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_5)
					case 5: { float fx = z.x*nfq, fy = z.y*nfq, h00 = native_sin(floor(fx)*127.1+floor(fy)*311.7)*43758.5453; h00=h00-floor(h00); { float h10 = native_sin((floor(fx)+1)*127.1+floor(fy)*311.7)*43758.5453; h10=h10-floor(h10); float h01 = native_sin(floor(fx)*127.1+(floor(fy)+1)*311.7)*43758.5453; h01=h01-floor(h01); float h11 = native_sin((floor(fx)+1)*127.1+(floor(fy)+1)*311.7)*43758.5453; h11=h11-floor(h11); float tx=fx-floor(fx), ty=fy-floor(fy), v = h00*(1-tx)*(1-ty)+h10*tx*(1-ty)+h01*(1-tx)*ty+h11*tx*ty; aux.DE *= (1.0 + nf*v); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_6)
					case 6: { float h = native_sin(z.x*na*12.9898 + z.y*nb*78.233 + z.z*nc*45.164 + nd*i)*43758.5453; h=h-floor(h); h = h*h*(3.0-2.0*h); aux.DE *= (1.0 + nf*h); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_7)
					case 7: { float h = native_sin(z.x*nfq + z.y*nfq*1.3 + z.z*nfq*0.7)*43758.5453; h=h-floor(h); h = 6.0*h*h*h*h*h - 15.0*h*h*h*h + 10.0*h*h*h; aux.DE *= (1.0 + nf*h); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_8)
					case 8: { float p = na*z.x*nfq + nb*z.y*nfq + nc*z.z*nfq, h = native_sin(p)*0.5+0.5; aux.DE *= (1.0 + nf*h*h); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_9)
					case 9: { float h1 = native_sin(z.x*nfq*12.9898)*43758.5453; h1=h1-floor(h1); { float h2 = native_sin(z.y*nfq*78.233)*43758.5453; h2=h2-floor(h2); float h3 = native_sin(z.z*nfq*45.164)*43758.5453; h3=h3-floor(h3); aux.DE *= (1.0 + nf*(h1*h2*h3)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_10)
					case 10: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), h = native_sin(r*nfq)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_11)
					case 11: { float gx = native_sin(z.x*nfq*127.1+z.y*311.7)*2.0-1.0, gy = native_sin(z.y*nfq*269.5+z.z*183.3)*2.0-1.0, gz = native_sin(z.z*nfq*419.2+z.x*371.9)*2.0-1.0, v = (gx*z.x+gy*z.y+gz*z.z)*nam; aux.DE *= (1.0 + nf*native_sin(v)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_12)
					case 12: { float px = z.x*nfq, py = z.y*nfq, g1 = native_sin(floor(px)*127.1+floor(py)*311.7)*2.0-1.0, g2 = native_sin((floor(px)+1)*127.1+floor(py)*311.7)*2.0-1.0, t = px-floor(px); t = t*t*(3.0-2.0*t); { float v = g1*(1.0-t)+g2*t; aux.DE *= (1.0 + nf*v); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_13)
					case 13: { float px = z.x*nfq, py = z.y*nfq, pz = z.z*nfq, g = native_sin(px*127.1+py*311.7+pz*74.7)*2.0-1.0, t = g*g*(3.0-2.0*g); aux.DE *= (1.0 + nf*t*nam); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_14)
					case 14: { float v = native_sin(z.x*nfq)*native_cos(z.y*nfq*1.3)*native_sin(z.z*nfq*0.7); aux.DE *= (1.0 + nf*v*nam); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_15)
					case 15: { float v1 = native_sin(z.x*nfq+z.y*nfq*0.5), v2 = native_sin(z.y*nfq*1.3+z.z*nfq*0.7), v3 = native_sin(z.z*nfq*0.9+z.x*nfq*1.1); aux.DE *= (1.0 + nf*(v1+v2+v3)/3.0); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_16)
					case 16: { float px = z.x*nfq, h = native_sin(px*12.9898+z.y*nfq*78.233)*43758.5453; h=h-floor(h); { float g = (h*2.0-1.0)*(px-floor(px)); aux.DE *= (1.0 + nf*g); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_17)
					case 17: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), th = atan2(z.y,z.x), v = native_sin(r*nfq+th*na)*nam; aux.DE *= (1.0 + nf*v); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_18)
					case 18: { float v = native_sin(z.x*nfq)*native_sin(z.y*nfq)*native_sin(z.z*nfq); v = v*v*(3.0-2.0*v); aux.DE *= (1.0 + nf*v*nam); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_19)
					case 19: { float dx = native_sin(z.x*nfq*12.9898)*2.0-1.0, dy = native_sin(z.y*nfq*78.233)*2.0-1.0, dz = native_sin(z.z*nfq*45.164)*2.0-1.0, v = native_sqrt(dx*dx+dy*dy+dz*dz); aux.DE *= (1.0 + nf*(v-1.0)*nam); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_20)
					case 20: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), phi = atan2(z.y,z.x), theta = acos(z.z/fmax(r,1e-21)), v = native_sin(r*nfq)*native_cos(phi*na)*native_sin(theta*nb); aux.DE *= (1.0 + nf*v); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_21)
					case 21: { float v=0, a=nam, f=nfq; for(int k=0;k<4;k++){ v += a*native_sin(z.x*f*12.9898+z.y*f*78.233+z.z*f*45.164); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_22)
					case 22: { float v=0, a=nam, f=nfq; for(int k=0;k<6;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_23)
					case 23: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*fabs(h*2.0-1.0); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_24)
					case 24: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*(1.0-fabs(h*2.0-1.0)); f*=na; a*=nb; } aux.DE *= (1.0 + nf*v); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_25)
					case 25: { float v=0, a=nam, f=nfq, px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ float h=native_sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*h;float d=native_sin(px*f*269.5+py*f*183.3)*43758.5453; d=d-floor(d); px+=d*na; py+=d*nb; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_26)
					case 26: { float v=0, a=1.0, f=nfq, mx=0; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; mx+=a; f*=2.0; a*=0.5; } v/=fmax(mx,1e-21); aux.DE *= (1.0 + nf*v*nam); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_27)
					case 27: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h1=native_sin(z.x*f+z.y*f*1.3)*0.5+0.5;float h2=native_sin(z.y*f*0.7+z.z*f*1.1)*0.5+0.5; v+=a*fmin(h1,h2); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_28)
					case 28: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h1=native_sin(z.x*f+z.y*f*1.3)*0.5+0.5;float h2=native_sin(z.y*f*0.7+z.z*f*1.1)*0.5+0.5; v+=a*fmax(h1,h2); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_29)
					case 29: { float v=0, a=nam, f=nfq, cs=native_cos(nd*M_PI_F/180.0), sn=native_sin(nd*M_PI_F/180.0), px=z.x,py=z.y; for(int k=0;k<5;k++){ float h=native_sin(px*f*127.1+py*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*h;float nx=px*cs-py*sn; py=px*sn+py*cs; px=nx; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_30)
					case 30: { float v=0, a=nam, f=nfq; for(int k=0;k<6;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*native_sin(h*M_PI_F); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_31)
					case 31: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float r2=z.x*z.x+z.y*z.y+z.z*z.z;float h=native_sin(r2*f)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_32)
					case 32: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f)*native_cos(z.y*f)*native_sin(z.z*f); v+=a*h; f*=na; a*=nb; } aux.DE *= (1.0f + nf*v); break; }

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_33)
					case 33: { float v=0, w=1.0f, f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f; h=h-native_floor(h); v+=w*h; w*=h; f*=2.0f; } aux.DE *= (1.0f + nf*v*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_34)
					case 34: { float v=1.0f, f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f; h=h-native_floor(h); v*=(h*0.5f+0.75f); f*=2.0f; } aux.DE *= (1.0f + nf*(v-1.0f)*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_35)
					case 35: { float v=0, a=nam, f=nfq; float px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ float h=native_sin(px*f*127.1f+py*f*311.7f+pz*f*74.7f)*43758.5453f; h=h-native_floor(h); v+=a*h; px=fabs(px)*2.0f-na; py=fabs(py)*2.0f-nb; pz=fabs(pz)*2.0f-nc; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_36)
					case 36: { float md=1e10f; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=native_floor(z.x*nfq)+dx+0.5f; float cy=native_floor(z.y*nfq)+dy+0.5f; float cz=native_floor(z.z*nfq)+dz+0.5f; float h=native_sin(cx*127.1f+cy*311.7f+cz*74.7f)*43758.5453f; h=h-native_floor(h); cx+=h*0.5f; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md)md=d; } aux.DE *= (1.0f + nf*native_sqrt(md)*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_37)
					case 37: { float md1=1e10f,md2=1e10f; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=native_floor(z.x*nfq)+dx; float cy=native_floor(z.y*nfq)+dy; float cz=native_floor(z.z*nfq)+dz; float h=native_sin(cx*127.1f+cy*311.7f+cz*74.7f)*43758.5453f; h=h-native_floor(h); cx+=h; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md1){md2=md1;md1=d;}else if(d<md2)md2=d; } aux.DE *= (1.0f + nf*(native_sqrt(md2)-native_sqrt(md1))*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_38)
					case 38: { float md=1e10f; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ float cx=native_floor(z.x*nfq)+dx+0.5f; float cy=native_floor(z.y*nfq)+dy+0.5f; float h=native_sin(cx*127.1f+cy*311.7f)*43758.5453f; h=h-native_floor(h); cx+=h*0.5f; float d=fabs(z.x*nfq-cx)+fabs(z.y*nfq-cy); if(d<md)md=d; } aux.DE *= (1.0f + nf*md*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_39)
					case 39: { float md=1e10f; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=native_floor(z.x*nfq)+dx; float cy=native_floor(z.y*nfq)+dy; float cz=native_floor(z.z*nfq)+dz; float h=native_sin(cx*127.1f+cy*311.7f+cz*74.7f)*43758.5453f; h=h-native_floor(h); cx+=h; float d=fmax(fabs(z.x*nfq-cx),fmax(fabs(z.y*nfq-cy),fabs(z.z*nfq-cz))); if(d<md)md=d; } aux.DE *= (1.0f + nf*md*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_40)
					case 40: { float md=1e10f; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=native_floor(z.x*nfq)+dx; float cy=native_floor(z.y*nfq)+dy; float cz=native_floor(z.z*nfq)+dz; float h1=native_sin(cx*127.1f+cy*311.7f+cz*74.7f)*43758.5453f; h1=h1-native_floor(h1); float h2=native_sin(cx*269.5f+cy*183.3f+cz*346.9f)*43758.5453f; h2=h2-native_floor(h2); float h3=native_sin(cx*419.2f+cy*371.9f+cz*529.7f)*43758.5453f; h3=h3-native_floor(h3); float d=(z.x*nfq-cx-h1)*(z.x*nfq-cx-h1)+(z.y*nfq-cy-h2)*(z.y*nfq-cy-h2)+(z.z*nfq-cz-h3)*(z.z*nfq-cz-h3); if(d<md)md=d; } aux.DE *= (1.0f + nf*native_sqrt(md)*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_41)
					case 41: { float md1=1e10f,md2=1e10f; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=native_floor(z.x*nfq)+dx; float cy=native_floor(z.y*nfq)+dy; float cz=native_floor(z.z*nfq)+dz; float h=native_sin(cx*127.1f+cy*311.7f+cz*74.7f)*43758.5453f; h=h-native_floor(h); cx+=h; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md1){md2=md1;md1=d;}else if(d<md2)md2=d; } aux.DE *= (1.0f + nf*md1*md2*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_42)
					case 42: { float md=1e10f; float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float th=atan2(z.y,z.x); for(int k=0;k<8;k++){ float a2=k*M_PI_F*2.0f/8.0f; float d=fabs(th-a2); if(d>M_PI_F)d=2.0f*M_PI_F-d; if(d<md)md=d; } aux.DE *= (1.0f + nf*md*r*nam*nfq); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_43)
					case 43: { float v=0; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=native_floor(z.x*nfq)+dx; float cy=native_floor(z.y*nfq)+dy; float cz=native_floor(z.z*nfq)+dz; float h=native_sin(cx*127.1f+cy*311.7f+cz*74.7f)*43758.5453f; h=h-native_floor(h); float d=(z.x*nfq-cx-h)*(z.x*nfq-cx-h)+(z.y*nfq-cy-h)*(z.y*nfq-cy-h)+(z.z*nfq-cz-h)*(z.z*nfq-cz-h); v+=native_exp(-na*d); } aux.DE *= (1.0f + nf*(1.0f-v)*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_44)
					case 44: { float md=1e10f; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=native_floor(z.x*nfq)+dx; float cy=native_floor(z.y*nfq)+dy; float cz=native_floor(z.z*nfq)+dz; float h=native_sin(cx*127.1f+cy*311.7f+cz*74.7f)*43758.5453f; h=h-native_floor(h); cx+=h; float d=native_sqrt((z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz)); if(d<md)md=d; } float v=native_sin(md*M_PI_F*na); aux.DE *= (1.0f + nf*v*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_45)
					case 45: { float md=1e10f,cd=0; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=native_floor(z.x*nfq)+dx; float cy=native_floor(z.y*nfq)+dy; float cz=native_floor(z.z*nfq)+dz; float h=native_sin(cx*127.1f+cy*311.7f+cz*74.7f)*43758.5453f; h=h-native_floor(h); cx+=h; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md){md=d;cd=h;} } aux.DE *= (1.0f + nf*cd*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_46)
					case 46: { float md1=1e10f,md2=1e10f,md3=1e10f; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=native_floor(z.x*nfq)+dx; float cy=native_floor(z.y*nfq)+dy; float cz=native_floor(z.z*nfq)+dz; float h=native_sin(cx*127.1f+cy*311.7f+cz*74.7f)*43758.5453f; h=h-native_floor(h); cx+=h; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md1){md3=md2;md2=md1;md1=d;}else if(d<md2){md3=md2;md2=d;}else if(d<md3)md3=d; } aux.DE *= (1.0f + nf*(native_sqrt(md3)-native_sqrt(md1))*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_47)
					case 47: { float md=1e10f; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ float cx=native_floor(z.x*nfq)+dx; float cy=native_floor(z.y*nfq)+dy; float h=native_sin(cx*127.1f+cy*311.7f)*43758.5453f; h=h-native_floor(h); cx+=h*na; float hy=native_sin(cx*269.5f+cy*183.3f)*43758.5453f; hy=hy-native_floor(hy); cy+=hy*nb; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy); if(d<md)md=d; } float v = native_sin(z.z*nfq)*0.5f+0.5f; aux.DE *= (1.0f + nf*(native_sqrt(md)+v*nc)*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_48)
					case 48: { float md=1e10f; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=native_floor(z.x*nfq)+dx; float cy=native_floor(z.y*nfq)+dy; float cz=native_floor(z.z*nfq)+dz; float h=native_sin(cx*127.1f+cy*311.7f+cz*74.7f)*43758.5453f; h=h-native_floor(h); cx+=h; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md)md=d; } md=native_sqrt(md); float v=md-native_floor(md*na)/na; aux.DE *= (1.0f + nf*v*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_49)
					case 49: { float v=0,a=nam,f=nfq; for(int k=0;k<4;k++){ float md=1e10f; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ float cx=native_floor(z.x*f)+dx; float cy=native_floor(z.y*f)+dy; float h=native_sin(cx*127.1f+cy*311.7f)*43758.5453f; h=h-native_floor(h); cx+=h; float d=(z.x*f-cx)*(z.x*f-cx)+(z.y*f-cy)*(z.y*f-cy); if(d<md)md=d; } v+=a*native_sqrt(md); f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_50)
					case 50: { float md=1e10f; int nn = (int)fmax(2.0f, fmin(na*8.0f, 20.0f)); for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ float cx=native_floor(z.x*nfq)+dx; float cy=native_floor(z.y*nfq)+dy; float cz=native_floor(z.z*nfq)+dz; for(int p=0;p<2;p++){ float h1=native_sin((cx+p*0.5f)*127.1f+cy*311.7f+cz*74.7f)*43758.5453f; h1=h1-native_floor(h1); float h2=native_sin(cx*269.5f+(cy+p*0.5f)*183.3f+cz*346.9f)*43758.5453f; h2=h2-native_floor(h2); float d=(z.x*nfq-cx-h1)*(z.x*nfq-cx-h1)+(z.y*nfq-cy-h2)*(z.y*nfq-cy-h2)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md)md=d; } } aux.DE *= (1.0f + nf*native_sqrt(md)*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_51)
					case 51: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f; h=h-native_floor(h); float r2=fabs(h*2.0f-1.0f); v+=a*(1.0f-r2); f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_52)
					case 52: { float v=0,a=nam,f=nfq,w=1.0f; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f; h=h-native_floor(h); float r2=1.0f-fabs(h*2.0f-1.0f); r2*=r2; v+=r2*a*w; w=fmin(r2*na, 1.0f); f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_53)
					case 53: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f+z.y*f*1.3f+z.z*f*0.7f); v+=a*fabs(h); f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_54)
					case 54: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f; h=h-native_floor(h); v+=a*fabs(native_sin(h*M_PI_F*na)); f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_55)
					case 55: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f+z.y*f*1.3f+z.z*f*0.7f); float ridge=1.0f-fabs(h); ridge=ridge*ridge; v+=a*ridge; f*=na; a*=nb; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_56)
					case 56: { float v=0,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f; h=h-native_floor(h); v=fmax(v,h*nam/(1.0f+k*0.5f)); f*=2.0f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_57)
					case 57: { float v=0,a=nam,f=nfq,prev=0; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f; h=h-native_floor(h); float cur=fabs(h*2.0f-1.0f); v+=a*cur*prev; prev=cur; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_58)
					case 58: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h1=native_sin(z.x*f+z.y*f*1.3f)*0.5f+0.5f; float h2=native_sin(z.y*f*0.7f+z.z*f*1.1f)*0.5f+0.5f; float h3=native_sin(z.z*f*0.9f+z.x*f*1.5f)*0.5f+0.5f; v+=a*(h1+h2+h3)/3.0f; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*(v*2.0f-1.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_59)
					case 59: { float v=0,a=nam,f=nfq; for(int k=0;k<6;k++){ float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float h=native_sin(r*f)*43758.5453f; h=h-native_floor(h); v+=a*h; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_60)
					case 60: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f+z.y*f*1.3f+z.z*f*0.7f); float billow=fabs(h)*2.0f-1.0f; v+=a*billow; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_61)
					case 61: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f+z.y*f*0.7f+z.z*f*1.3f)*0.5f+0.5f; v+=a*native_pow(h, na); f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_62)
					case 62: { float v=0,a=nam,f=nfq; float px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ float h=native_sin(px*f*127.1f+py*f*311.7f+pz*f*74.7f)*43758.5453f; h=h-native_floor(h); v+=a*fabs(h*2.0f-1.0f); float wx=native_sin(py*f*269.5f)*na; float wy=native_sin(pz*f*183.3f)*nb; float wz=native_sin(px*f*419.2f)*nc; px+=wx; py+=wy; pz+=wz; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_63)
					case 63: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f; h=h-native_floor(h); if(k%2==0) v+=a*h; else v+=a*(1.0f-h); f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_64)
					case 64: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f+z.y*f*1.3f+z.z*f*0.7f); float hs=h*h*sign(h); v+=a*hs; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_65)
					case 65: { float v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f+nd*i)*43758.5453f; h=h-native_floor(h); v+=a*h; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_66)
					case 66: { float wx=z.x+nam*native_sin(z.y*nfq); float wy=z.y+nam*native_sin(z.z*nfq); float wz=z.z+nam*native_sin(z.x*nfq); float h=native_sin(wx*127.1f+wy*311.7f+wz*74.7f)*43758.5453f; h=h-native_floor(h); aux.DE *= (1.0f + nf*h); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_67)
					case 67: { float wx=z.x+nam*native_sin(z.y*nfq+z.z*nfq*0.5f); float wy=z.y+nam*native_sin(z.z*nfq*1.3f+z.x*nfq*0.7f); float wz=z.z+nam*native_sin(z.x*nfq*0.9f+z.y*nfq*1.1f); float wx2=wx+nb*native_sin(wy*nfq*2.0f); float wy2=wy+nb*native_sin(wz*nfq*2.0f); float wz2=wz+nb*native_sin(wx*nfq*2.0f); float h=native_sin(wx2*127.1f+wy2*311.7f+wz2*74.7f)*43758.5453f; h=h-native_floor(h); aux.DE *= (1.0f + nf*h); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_68)
					case 68: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float th=atan2(z.y,z.x)+nam*native_sin(r*nfq); float ph=native_acos(z.z/fmax(r,1e-21f))+nb*native_cos(r*nfq*0.7f); float h=native_sin(th*na+ph*nc)*0.5f+0.5f; aux.DE *= (1.0f + nf*h); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_69)
					case 69: { float h1=native_sin(z.x*nfq*127.1f+z.y*nfq*311.7f)*43758.5453f; h1=h1-native_floor(h1); float h2=native_sin(z.y*nfq*269.5f+z.z*nfq*183.3f)*43758.5453f; h2=h2-native_floor(h2); float wx=z.x+(h1*2.0f-1.0f)*nam; float wy=z.y+(h2*2.0f-1.0f)*nam; float v=native_sin(wx*nfq*na+wy*nfq*nb); aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_70)
					case 70: { float v=0,f=nfq,a=nam; float px=z.x,py=z.y,pz=z.z; for(int k=0;k<4;k++){ float h=native_sin(px*f*127.1f+py*f*311.7f+pz*f*74.7f)*43758.5453f; h=h-native_floor(h); v+=a*h; px+=native_sin(py*f*na)*nb; py+=native_sin(pz*f*na)*nb; pz+=native_sin(px*f*na)*nb; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_71)
					case 71: { float wx=z.x+nam*native_sin(z.y*nfq)*native_cos(z.z*nfq*0.5f); float wy=z.y+nam*native_cos(z.x*nfq*0.7f)*native_sin(z.z*nfq); float v=native_sin(wx*na)*native_cos(wy*nb); aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_72)
					case 72: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float wr=r+nam*native_sin(r*nfq); float h=native_sin(wr*na*127.1f)*43758.5453f; h=h-native_floor(h); aux.DE *= (1.0f + nf*h); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_73)
					case 73: { float v=native_sin(z.x*nfq+nam*native_sin(z.y*nfq+nam*native_sin(z.z*nfq))); aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_74)
					case 74: { float t=nd*i*0.01f; float wx=z.x+nam*native_sin(z.y*nfq+t); float wy=z.y+nam*native_sin(z.z*nfq+t*1.3f); float wz=z.z+nam*native_sin(z.x*nfq+t*0.7f); float h=native_sin(wx*127.1f+wy*311.7f+wz*74.7f)*43758.5453f; h=h-native_floor(h); aux.DE *= (1.0f + nf*h); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_75)
					case 75: { float scale=nfq; float wx=z.x*scale; float wy=z.y*scale; float wz=z.z*scale; for(int k=0;k<3;k++){ wx=native_sin(wx*na+wy); wy=native_cos(wy*nb+wz); wz=native_sin(wz*nc+wx); } float h=native_sin(wx+wy+wz)*0.5f+0.5f; aux.DE *= (1.0f + nf*h*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_76)
					case 76: { float h1=native_sin(z.x*nfq+z.y*nfq*0.5f)*0.5f+0.5f; float h2=native_sin(z.y*nfq*1.3f+z.z*nfq*0.7f)*0.5f+0.5f; float v=native_sin((z.x+h1*nam)*na)*native_cos((z.y+h2*nam)*nb); aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_77)
					case 77: { float wx=z.x+nam*native_sin(nfq*z.y); float wy=z.y+nam*native_cos(nfq*z.x); float v1=native_sin(wx*na); float v2=native_cos(wy*nb); float v=v1*v2; z.x+=nf*v*nc*0.01f; z.y+=nf*v*nd*0.01f; aux.DE *= (1.0f + nf*fabs(v)*0.1f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_78)
					case 78: { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float h=native_sin(r2*nfq)*43758.5453f; h=h-native_floor(h); float wx=z.x*(1.0f+h*nam); float wy=z.y*(1.0f+h*nam); float v=native_sin(wx*na+wy*nb)*0.5f+0.5f; aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_79)
					case 79: { float v=0,f=nfq; for(int k=0;k<4;k++){ float h=native_sin(z.x*f+native_sin(z.y*f*na)*nam); v+=h/(1.0f+k); f*=2.0f; } aux.DE *= (1.0f + nf*v*0.25f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_80)
					case 80: { float wx=z.x+nam*native_sin(z.y*nfq)*native_sin(z.z*nfq*0.5f); float wy=z.y+nam*native_sin(z.z*nfq*0.7f)*native_sin(z.x*nfq); float wz=z.z+nam*native_sin(z.x*nfq*1.3f)*native_sin(z.y*nfq*0.9f); float v=native_sin(wx*na)*native_sin(wy*nb)*native_sin(wz*nc); aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_81)
					case 81: { float s=(z.x+z.y+z.z)/3.0f; float ix=native_floor(z.x+s); float iy=native_floor(z.y+s); float iz=native_floor(z.z+s); float t=(ix+iy+iz)/6.0f; float x0=z.x-ix+t; float y0=z.y-iy+t; float z0=z.z-iz+t; float h=native_sin(ix*127.1f+iy*311.7f+iz*74.7f)*43758.5453f; h=h-native_floor(h); float v=fmax(0.0f,0.6f-x0*x0-y0*y0-z0*z0); v=v*v*v*v*h; aux.DE *= (1.0f + nf*v*nam*32.0f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_82)
					case 82: { float s=(z.x+z.y+z.z)*nfq/3.0f; float v=native_sin(s*127.1f)*43758.5453f; v=v-native_floor(v); float v2=native_sin(s*269.5f)*43758.5453f; v2=v2-native_floor(v2); aux.DE *= (1.0f + nf*(v*na+v2*nb)*0.5f*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_83)
					case 83: { float skew=(z.x+z.y)*nfq*(native_sqrt(3.0f)-1.0f)/2.0f; float ix=native_floor(z.x*nfq+skew); float iy=native_floor(z.y*nfq+skew); float unskew=(ix+iy)*(3.0f-native_sqrt(3.0f))/6.0f; float x0=z.x*nfq-ix+unskew; float y0=z.y*nfq-iy+unskew; float h=native_sin(ix*127.1f+iy*311.7f)*43758.5453f; h=h-native_floor(h); float t0=0.5f-x0*x0-y0*y0; float v=t0>0?t0*t0*t0*t0*h:0; aux.DE *= (1.0f + nf*v*nam*70.0f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_84)
					case 84: { float v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float s=(z.x*f+z.y*f+z.z*f)/3.0f; float h=native_sin(s*127.1f+k*519.3f)*43758.5453f; h=h-native_floor(h); v+=a*h; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_85)
					case 85: { float v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float s=(z.x*f+z.y*f+z.z*f)/3.0f; float h=native_sin(s*127.1f+k*519.3f)*43758.5453f; h=h-native_floor(h); v+=a*fabs(h*2.0f-1.0f); f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_86)
					case 86: { float v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float s=(z.x*f+z.y*f+z.z*f)/3.0f; float h=native_sin(s*127.1f+k*519.3f)*43758.5453f; h=h-native_floor(h); float ridge=1.0f-fabs(h*2.0f-1.0f); ridge*=ridge; v+=a*ridge; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_87)
					case 87: { float s=(z.x+z.y+z.z)*nfq; float v1=native_sin(s*na)*0.5f+0.5f; float v2=native_sin(s*nb+M_PI_F*0.5f)*0.5f+0.5f; float v=v1*v2; aux.DE *= (1.0f + nf*v*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_88)
					case 88: { float v=0; float px=z.x*nfq,py=z.y*nfq,pz=z.z*nfq; for(int k=0;k<4;k++){ float s=(px+py+pz)/3.0f; float h=native_sin(s*127.1f+k*91.7f)*43758.5453f; h=h-native_floor(h); v+=h*nam/(1.0f+k); px+=native_sin(py)*na; py+=native_sin(pz)*nb; pz+=native_sin(px)*nc; } aux.DE *= (1.0f + nf*v*0.25f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_89)
					case 89: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float th=atan2(z.y,z.x); float s=(r*nfq+th*na)/3.0f; float h=native_sin(s*127.1f)*43758.5453f; h=h-native_floor(h); aux.DE *= (1.0f + nf*h*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_90)
					case 90: { float v=0,f=nfq,a=nam; float cs=native_cos(nd*M_PI_F/180.0f),sn=native_sin(nd*M_PI_F/180.0f); float px=z.x,py=z.y; for(int k=0;k<5;k++){ float s=(px*f+py*f+z.z*f)/3.0f; float h=native_sin(s*127.1f+k*519.3f)*43758.5453f; h=h-native_floor(h); v+=a*h; float nx=px*cs-py*sn; py=px*sn+py*cs; px=nx; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_91)
					case 91: { float vn=native_sin(z.x*nfq*127.1f+z.y*nfq*311.7f+z.z*nfq*74.7f)*43758.5453f; vn=vn-native_floor(vn); float md=1e10f; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ float cx=native_floor(z.x*nfq)+dx; float cy=native_floor(z.y*nfq)+dy; float h=native_sin(cx*127.1f+cy*311.7f)*43758.5453f; h=h-native_floor(h); cx+=h; float d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy); if(d<md)md=d; } aux.DE *= (1.0f + nf*(vn*na+native_sqrt(md)*nb)*nam); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_92)
					case 92: { float v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f; h=h-native_floor(h); v+=a*native_sin(h*M_PI_F*2.0f*na); f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_93)
					case 93: { float t=nd*i*0.1f; float v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f+t)*43758.5453f; h=h-native_floor(h); v+=a*h; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_94)
					case 94: { float v1=0,v2=0,f=nfq,a=nam; for(int k=0;k<4;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f; h=h-native_floor(h); v1+=a*h; v2+=a*fabs(h*2.0f-1.0f); f*=2.0f; a*=0.5f; } float blend=native_sin(z.x*na+z.y*nb)*0.5f+0.5f; aux.DE *= (1.0f + nf*(v1*blend+v2*(1.0f-blend))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_95)
					case 95: { float v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f; h=h-native_floor(h); float erosion=native_exp(-na*h); v+=a*erosion; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_96)
					case 96: { float v=0,f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f; h=h-native_floor(h); float terrace=native_floor(h*na+0.5f)/fmax(na,1e-21f); v+=terrace/(1.0f+k); f*=2.0f; } aux.DE *= (1.0f + nf*v*nam*0.2f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_97)
					case 97: { float v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f; h=h-native_floor(h); float swiss=fabs(h*2.0f-1.0f); swiss=1.0f-swiss*swiss; v+=a*swiss; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_98)
					case 98: { float v=0,f=nfq,a=nam; float px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ float h=native_sin(px*f*127.1f+py*f*311.7f+pz*f*74.7f)*43758.5453f; h=h-native_floor(h); v+=a*h; float wx=native_sin(py*f*na)*nb*a; float wy=native_sin(pz*f*na)*nb*a; float wz=native_sin(px*f*na)*nb*a; px+=wx; py+=wy; pz+=wz; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_99)
					case 99: { float v=0,f=nfq,a=nam; float offset=0; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f+offset)*43758.5453f; h=h-native_floor(h); float r=fabs(h*2.0f-1.0f); r=offset+r*r*na; v+=a*r; offset=r; f*=2.0f; a*=0.5f; } aux.DE *= (1.0f + nf*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_NOISETYPE_100)
					case 100: { float v1=0,v2=0,f=nfq,a=nam; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f; h=h-native_floor(h); v1+=a*h; float ridge=1.0f-fabs(h*2.0f-1.0f); v2+=a*ridge*ridge; f*=2.0f; a*=0.5f; } float t=native_sin(z.x*na+z.y*nb+z.z*nc)*0.5f+0.5f; aux.DE *= (1.0f + nf*(v1*(1.0f-t)+v2*t)); break; }
#endif

					default: break;
#endif
				}
			}

			// v7.10 [GPU] — Orbit Trap DE system (per-section iteration range)
			if (i >= mut->orbitIterStart && i < mut->orbitIterStop && mut->orbitTrapType != 0)
			{
				float oa = mut->orbitParamA, ob = mut->orbitParamB, oc = mut->orbitParamC, od = mut->orbitParamD;
				float of = mut->orbitFactor * mut->orbitTrapWeight * mut->masterWeight;
				switch(mut->orbitTrapType) {
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_1)
					case 1: { float d = native_sqrt((z.x-oa)*(z.x-oa)+(z.y-ob)*(z.y-ob)+(z.z-oc)*(z.z-oc)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_2)
					case 2: { float d = fabs(z.x-oa)+fabs(z.y-ob)+fabs(z.z-oc); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_3)
					case 3: { float d = fmax(fabs(z.x-oa),fmax(fabs(z.y-ob),fabs(z.z-oc))); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_4)
					case 4: { float d1=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), d2=native_sqrt((z.x-oa)*(z.x-oa)+(z.y-ob)*(z.y-ob)+(z.z-oc)*(z.z-oc)); aux.DE *= (1.0 + of*native_exp(-od*fmin(d1,d2))); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_5)
					case 5: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), ring=fabs(d-oa); aux.DE *= (1.0 + of*native_exp(-od*ring)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_6)
					case 6: { float dx=z.x-oa*round(z.x/fmax(oa,1e-21)), dy=z.y-ob*round(z.y/fmax(ob,1e-21)), dz=z.z-oc*round(z.z/fmax(oc,1e-21)), d=native_sqrt(dx*dx+dy*dy+dz*dz); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_7)
					case 7: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), shell=fabs(d-oa), shell2=fabs(d-ob); aux.DE *= (1.0 + of*native_exp(-od*fmin(shell,shell2))); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_8)
					case 8: { float ph=atan2(z.y,z.x), r=native_sqrt(z.x*z.x+z.y*z.y), spiral_r=oa+ob*ph/(2.0*M_PI_F), d=fabs(r-spiral_r); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_9)
					case 9: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), v=native_sin(d*oa*M_PI_F)*0.5+0.5; aux.DE *= (1.0 + of*v); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_10)
					case 10: { int nn=(int)fmax(2,fmin(oa*6,12)); { float md=1e10; for(int k=0;k<nn;k++){ float ang=k*2.0*M_PI_F/nn;float cx=ob*native_cos(ang); float cy=ob*native_sin(ang); float d=(z.x-cx)*(z.x-cx)+(z.y-cy)*(z.y-cy)+z.z*z.z; if(d<md)md=d; } aux.DE *= (1.0 + of*native_exp(-od*native_sqrt(md))); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_11)
					case 11: { float d=z.x*z.x/(oa*oa+1e-21)+z.y*z.y/(ob*ob+1e-21)+z.z*z.z/(oc*oc+1e-21); d=fabs(native_sqrt(d)-1.0); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_12)
					case 12: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), th=atan2(z.y,z.x), d=fabs(r-oa*(1.0+ob*native_cos(oc*th))); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_13)
					case 13: { float r2=z.x*z.x+z.y*z.y+z.z*z.z, inv_r=oa*oa/fmax(r2,1e-21), d=fabs(inv_r-1.0)*native_sqrt(r2); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_14)
					case 14: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), s=native_sin(d*oa), c=native_cos(d*ob); aux.DE *= (1.0 + of*(s*s+c*c*0.5)*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_15)
					case 15: { float d=fabs(z.x*oa+z.y*ob+z.z*oc)/fmax(native_sqrt(oa*oa+ob*ob+oc*oc),1e-21); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_16)
					case 16: { float d=native_sqrt(z.y*z.y+z.z*z.z); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_17)
					case 17: { float d=native_sqrt(z.x*z.x+z.z*z.z); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_18)
					case 18: { float d=native_sqrt(z.x*z.x+z.y*z.y); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_19)
					case 19: { float d=fabs(z.x*oa+z.y*ob+z.z*oc-od); aux.DE *= (1.0 + of*native_exp(-d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_20)
					case 20: { float d=fmin(fabs(z.x),fmin(fabs(z.y),fabs(z.z))); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_21)
					case 21: { float d1=fabs(z.x), d2=fabs(z.y), d3=fabs(z.z); aux.DE *= (1.0 + of*native_exp(-od*fmin(d1,d2))*native_exp(-od*d3)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_22)
					case 22: { float d=fmin(native_sqrt(z.x*z.x+z.y*z.y),native_sqrt(z.y*z.y+z.z*z.z)); d=fmin(d,native_sqrt(z.x*z.x+z.z*z.z)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_23)
					case 23: { float d1=fabs(z.x-oa), d2=fabs(z.y-ob), d3=fabs(z.z-oc), d=d1*d2*d3; aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_24)
					case 24: { float cs=native_cos(oa*M_PI_F/180.0),sn=native_sin(oa*M_PI_F/180.0), rx=z.x*cs-z.y*sn, ry=z.x*sn+z.y*cs, d=fabs(ry); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_25)
					case 25: { float d=fmin(fabs(z.x),fabs(z.y)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_26)
					case 26: { float d1=fabs(z.y-oa*z.x), d2=fabs(z.y+oa*z.x); aux.DE *= (1.0 + of*native_exp(-od*fmin(d1,d2))); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_27)
					case 27: { float ph=atan2(z.y,z.x); int n=(int)fmax(3,fmin(oa,12)); { float seg=2.0*M_PI_F/n, sph=fmod(ph+M_PI_F,seg)-seg*0.5, r=native_sqrt(z.x*z.x+z.y*z.y), d=fabs(r*native_sin(sph)); aux.DE *= (1.0 + of*native_exp(-od*d)); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_28)
					case 28: { float d1=fabs(z.x*native_sin(oa*M_PI_F/180.0)-z.y*native_cos(oa*M_PI_F/180.0)), d2=fabs(z.x*native_sin(ob*M_PI_F/180.0)-z.y*native_cos(ob*M_PI_F/180.0)); aux.DE *= (1.0 + of*native_exp(-od*(d1+d2))); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_29)
					case 29: { float d=fabs(z.z-oa*native_sin(ob*z.x)*native_cos(oc*z.y)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_30)
					case 30: { float r=native_sqrt(z.x*z.x+z.y*z.y), d=fabs(z.z-oa*native_sin(ob*r)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_31)
					case 31: { float r=native_sqrt(z.x*z.x+z.y*z.y), d=fabs(r-oa); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_32)
					case 32: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float d=fabs(r-oa); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_33)
					case 33: { float r=native_sqrt(z.x*z.x+z.y*z.y); float d=native_sqrt((r-oa)*(r-oa)+z.z*z.z)-ob; aux.DE *= (1.0f + of*native_exp(-od*fabs(d))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_34)
					case 34: { float r=native_sqrt(z.x*z.x+z.y*z.y); float th=atan2(z.y,z.x); float sf2=native_pow(fabs(native_cos(oa*th/4.0f)),ob)+native_pow(fabs(native_sin(oa*th/4.0f)),ob); float sr=oc*native_pow(sf2,-1.0f/fmax(ob,1e-21f)); float d=fabs(r-sr); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_35)
					case 35: { float ph=atan2(z.y,z.x); float r=native_sqrt(z.x*z.x+z.y*z.y); int n=(int)fmax(3,fmin(oa,12)); float star_r=ob*(1.0f+oc*native_cos(n*ph)); float d=fabs(r-star_r); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_36)
					case 36: { float r=native_sqrt(z.x*z.x+z.y*z.y); float ph=atan2(z.y,z.x); float lemnR=oa*oa*native_cos(2.0f*ph); float d=fabs(r*r-lemnR); aux.DE *= (1.0f + of*native_exp(-od*d*0.5f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_37)
					case 37: { float r=native_sqrt(z.x*z.x+z.y*z.y); float ph=atan2(z.y,z.x); float rose_r=oa*native_sin(ob*ph); float d=fabs(r-fabs(rose_r)); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_38)
					case 38: { float ph=atan2(z.y,z.x); float r=native_sqrt(z.x*z.x+z.y*z.y); float spiral_r=oa*native_exp(ob*ph); float d=fabs(r-spiral_r); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_39)
					case 39: { float r=native_sqrt(z.x*z.x+z.y*z.y); float ph=atan2(z.y,z.x); float heart_r=oa*(1.0f-native_sin(ph)); float d=fabs(r-heart_r); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_40)
					case 40: { float d1=native_sqrt(z.x*z.x+z.y*z.y)-oa; float d2=native_sqrt(z.y*z.y+z.z*z.z)-oa; float d3=native_sqrt(z.x*z.x+z.z*z.z)-oa; float d=fmin(fabs(d1),fmin(fabs(d2),fabs(d3))); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_41)
					case 41: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float d1=fabs(r-oa); float d2=fabs(r-ob); aux.DE *= (1.0f + of*native_exp(-od*d1)*native_exp(-od*d2)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_42)
					case 42: { float r=native_sqrt(z.x*z.x+z.y*z.y); float d=r*r-(oa*z.x+ob*z.y); d=fabs(d)/fmax(r+1e-21f, 1e-21f); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_43)
					case 43: { float ex=z.x*z.x/(oa*oa+1e-21f); float ey=z.y*z.y/(ob*ob+1e-21f); float d=fabs(ex+ey-1.0f)*native_sqrt(oa*oa+ob*ob); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_44)
					case 44: { float r=native_sqrt(z.x*z.x+z.y*z.y); float t2=native_sqrt((r-oa)*(r-oa)+z.z*z.z); float d=fabs(t2-ob)+fabs(z.z)*oc; aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_45)
					case 45: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float ph=atan2(z.y,z.x); float th=native_acos(z.z/fmax(r,1e-21f)); float d=fabs(r-oa*(1.0f+ob*native_sin(oc*ph)*native_cos(od*th))); aux.DE *= (1.0f + of*native_exp(-d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_46)
					case 46: { float d=fabs(z.x*z.x+z.y*z.y-oa*z.z*z.z); d=native_sqrt(d); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_47)
					case 47: { float d=fabs(z.x*z.x/fmax(oa*oa,1e-21f)+z.y*z.y/fmax(ob*ob,1e-21f)-z.z*z.z/fmax(oc*oc,1e-21f)-1.0f); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_48)
					case 48: { float r=native_sqrt(z.x*z.x+z.y*z.y); float ph=atan2(z.y,z.x); float cyl_r=oa+ob*native_sin(oc*z.z)*native_cos(od*ph); float d=fabs(r-cyl_r); aux.DE *= (1.0f + of*native_exp(-d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_49)
					case 49: { float d1=fabs(fmax(fabs(z.x),fabs(z.y))-oa); float d2=fabs(fmax(fabs(z.y),fabs(z.z))-oa); float d3=fabs(fmax(fabs(z.x),fabs(z.z))-oa); float d=fmin(d1,fmin(d2,d3)); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_50)
					case 50: { float dx=fabs(fabs(z.x)-oa); float dy=fabs(fabs(z.y)-oa); float dz=fabs(fabs(z.z)-oa); float d=dx+dy+dz; aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_51)
					case 51: { float d1=fabs(z.x); float d2=fabs(z.y); float d=fmin(d1,d2); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_52)
					case 52: { float d1=fmin(fabs(z.x),fabs(z.y)); float d2=fabs(z.z); aux.DE *= (1.0f + of*native_exp(-od*(d1+d2*oa))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_53)
					case 53: { float gx=fabs(z.x-oa*round(z.x/fmax(oa,1e-21f))); float gy=fabs(z.y-ob*round(z.y/fmax(ob,1e-21f))); float d=fmin(gx,gy); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_54)
					case 54: { float gx=fabs(z.x-oa*round(z.x/fmax(oa,1e-21f))); float gy=fabs(z.y-oa*round(z.y/fmax(oa,1e-21f))); float gz=fabs(z.z-oa*round(z.z/fmax(oa,1e-21f))); float d=fmin(gx,fmin(gy,gz)); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_55)
					case 55: { float cs=native_cos(oa*M_PI_F/180.0f),sn=native_sin(oa*M_PI_F/180.0f); float rx=z.x*cs-z.y*sn; float ry=z.x*sn+z.y*cs; float d=fmin(fabs(rx),fabs(ry)); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_56)
					case 56: { float ph=atan2(z.y,z.x); int n=(int)fmax(3,fmin(oa,16)); float d=native_sqrt(z.x*z.x+z.y*z.y)*fabs(native_sin(n*ph*0.5f)); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_57)
					case 57: { float d1=fabs(z.x-z.y); float d2=fabs(z.x+z.y); float d=fmin(d1,d2)*0.7071f; aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_58)
					case 58: { float gx=oa>0.001f?fabs(native_sin(z.x*M_PI_F/oa)):fabs(z.x); float gy=ob>0.001f?fabs(native_sin(z.y*M_PI_F/ob)):fabs(z.y); float d=gx*gy; aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_59)
					case 59: { float d1=fmin(fabs(z.x-oa),fabs(z.x+oa)); float d2=fmin(fabs(z.y-ob),fabs(z.y+ob)); float d3=fmin(fabs(z.z-oc),fabs(z.z+oc)); float d=fmin(d1,fmin(d2,d3)); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_60)
					case 60: { float r=native_sqrt(z.x*z.x+z.y*z.y); float ph=atan2(z.y,z.x); int n=(int)fmax(3,fmin(oa,16)); float seg=2.0f*M_PI_F/n; float sph=fmod(ph+M_PI_F+seg*0.5f,seg)-seg*0.5f; float d=r*fabs(native_sin(sph)); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_61)
					case 61: { float d=fabs(z.x*z.x-z.y*z.y-oa*oa); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_62)
					case 62: { float hx=z.x*2.0f/3.0f+z.y/3.0f; float hy=z.y*2.0f/native_sqrt(3.0f); float d=fmin(fabs(hx-round(hx)),fabs(hy-round(hy)))*oa; aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_63)
					case 63: { float d=native_sin(z.x*oa*M_PI_F)*native_sin(z.y*ob*M_PI_F)*native_sin(z.z*oc*M_PI_F); aux.DE *= (1.0f + of*fabs(d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_64)
					case 64: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float ph=atan2(z.y,z.x); float th=native_acos(z.z/fmax(r,1e-21f)); float d=fabs(native_sin(oa*ph)*native_sin(ob*th))*r; aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_65)
					case 65: { float gx=fabs(z.x-oa*round(z.x/fmax(oa,1e-21f))); float gy=fabs(z.y-ob*round(z.y/fmax(ob,1e-21f))); float d=native_sqrt(gx*gx+gy*gy); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_66)
					case 66: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float w=native_exp(-oa*(float)i); aux.DE *= (1.0f + of*native_exp(-od*d)*w); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_67)
					case 67: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float phase=native_sin(ob*(float)i*M_PI_F/180.0f)*0.5f+0.5f; aux.DE *= (1.0f + of*native_exp(-od*d)*phase); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_68)
					case 68: { float d=native_sqrt((z.x-oa*native_sin(ob*i))*(z.x-oa*native_sin(ob*i))+(z.y-oa*native_cos(ob*i))*(z.y-oa*native_cos(ob*i))+z.z*z.z); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_69)
					case 69: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float trap_r=oa+ob*(float)i; float ring=fabs(d-trap_r); aux.DE *= (1.0f + of*native_exp(-od*ring)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_70)
					case 70: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(d < oa) { aux.DE *= (1.0f + of*native_exp(-od*(oa-d))); } break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_71)
					case 71: { float d=fabs(z.x)+fabs(z.y)+fabs(z.z); float w = (i%2==0) ? 1.0f : -0.5f; aux.DE *= (1.0f + of*w*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_72)
					case 72: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float v=native_sin(d*oa+ob*(float)i); aux.DE *= (1.0f + of*v*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_73)
					case 73: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float prevR=length(pointTransformed); float dr=fabs(r-prevR); aux.DE *= (1.0f + of*native_exp(-od*dr)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_74)
					case 74: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float n=fmax(1.0f,oa*10.0f); float trap=fabs(d-round(d*n)/n)*n; aux.DE *= (1.0f + of*native_exp(-od*trap)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_75)
					case 75: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float v=1.0f/(1.0f+native_exp(-oa*(d-ob))); aux.DE *= (1.0f + of*(v-0.5f)*2.0f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_76)
					case 76: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float decay=native_exp(-oa*d); float osc=native_sin(ob*d+oc*(float)i); aux.DE *= (1.0f + of*decay*osc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_77)
					case 77: { float d=fabs(z.x*z.y)+fabs(z.y*z.z)+fabs(z.z*z.x); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_78)
					case 78: { float d=z.x*z.x+z.y*z.y+z.z*z.z; float v=native_exp(-oa*d)*native_sin(ob*native_sqrt(d)); aux.DE *= (1.0f + of*v); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_79)
					case 79: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float ph=atan2(z.y,z.x); float d=fabs(r-oa)*fabs(native_sin(ob*ph)); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_80)
					case 80: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float cs=native_cos(oa*(float)i*M_PI_F/180.0f); float sn=native_sin(oa*(float)i*M_PI_F/180.0f); float rd=fabs((z.x*cs-z.y*sn)); aux.DE *= (1.0f + of*native_exp(-od*rd)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_81)
					case 81: { float d=fabs(z.x*z.x+z.y*z.y-oa*oa*z.z); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_82)
					case 82: { float r=native_sqrt(z.x*z.x+z.y*z.y); float ph=atan2(z.y,z.x); float d=fabs(r-oa*fabs(native_cos(ob*ph/2.0f))); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_83)
					case 83: { float mx=fabs(z.x); float my=fabs(z.y); float mz=fabs(z.z); if(mx<my){float t=mx;mx=my;my=t;} if(mx<mz){float t=mx;mx=mz;mz=t;} float d=mx-oa; aux.DE *= (1.0f + of*native_exp(-od*fabs(d))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_84)
					case 84: { float d1=native_sqrt(z.x*z.x+z.y*z.y)-oa; float d2=fabs(z.z)-ob; float d=native_sqrt(fmax(d1,0.0f)*fmax(d1,0.0f)+fmax(d2,0.0f)*fmax(d2,0.0f))+fmin(fmax(d1,d2),0.0f); aux.DE *= (1.0f + of*native_exp(-od*fabs(d))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_85)
					case 85: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float ph=atan2(z.y,z.x); float th=native_acos(z.z/fmax(r,1e-21f)); int nph=(int)fmax(2,oa*4); int nth=(int)fmax(2,ob*4); float dph=fabs(native_sin(nph*ph*0.5f)); float dth=fabs(native_sin(nth*th*0.5f)); float d=r*dph*dth; aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_86)
					case 86: { float d=fabs(native_sin(z.x*oa)*native_sin(z.y*ob)*native_sin(z.z*oc)); aux.DE *= (1.0f + of*d); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_87)
					case 87: { float d1=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-oa; float d2=fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z)))-ob; float d=fmax(d1,-d2); aux.DE *= (1.0f + of*native_exp(-od*fabs(d))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_88)
					case 88: { float r=native_sqrt(z.x*z.x+z.y*z.y); float d=native_sqrt((r-oa)*(r-oa)+z.z*z.z); float knot=fabs(d-ob*fabs(native_sin(oc*atan2(z.z,r-oa)))); aux.DE *= (1.0f + of*native_exp(-od*knot)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_89)
					case 89: { float d=native_pow(fabs(z.x),oa)+native_pow(fabs(z.y),oa)+native_pow(fabs(z.z),oa); d=native_pow(d,1.0f/fmax(oa,1e-21f))-ob; aux.DE *= (1.0f + of*native_exp(-od*fabs(d))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_90)
					case 90: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float th=atan2(z.y,z.x); float d=fabs(r-oa*(native_sin(ob*th)*native_sin(ob*th)+oc)); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_91)
					case 91: { float d1=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float d2=native_sqrt((z.x-oa)*(z.x-oa)+(z.y-ob)*(z.y-ob)+(z.z-oc)*(z.z-oc)); float d=fabs(d1-d2); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_92)
					case 92: { float d=fabs(z.x*z.y*z.z); d=native_pow(d,1.0f/3.0f); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_93)
					case 93: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float ph=atan2(z.y,z.x); float clover=oa*fabs(native_sin(ob*ph)); float d=fabs(r-clover); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_94)
					case 94: { float d1=fabs(z.x)-oa; float d2=fabs(z.y)-ob; float d3=fabs(z.z)-oc; float outside=native_sqrt(fmax(d1,0.0f)*fmax(d1,0.0f)+fmax(d2,0.0f)*fmax(d2,0.0f)+fmax(d3,0.0f)*fmax(d3,0.0f)); float inside=fmin(fmax(d1,fmax(d2,d3)),0.0f); float d=outside+inside; aux.DE *= (1.0f + of*native_exp(-od*fabs(d))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_95)
					case 95: { float md=1e10f; for(int k=0;k<(int)fmax(2,fmin(oa*4,8));k++){ float ang=k*2.0f*M_PI_F/fmax(oa*4,2); float cx=ob*native_cos(ang); float cy=ob*native_sin(ang); for(int j=0;j<(int)fmax(2,fmin(oc*4,8));j++){ float az=j*2.0f*M_PI_F/fmax(oc*4,2); float cz=od*native_sin(az); float d=(z.x-cx)*(z.x-cx)+(z.y-cy)*(z.y-cy)+(z.z-cz)*(z.z-cz); if(d<md)md=d; }} aux.DE *= (1.0f + of*native_exp(-native_sqrt(md))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_96)
					case 96: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float d=native_sin(r*oa)*native_sin(z.x*ob)*native_sin(z.y*oc); aux.DE *= (1.0f + of*fabs(d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_97)
					case 97: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float ph=atan2(z.y,z.x); float th=native_acos(z.z/fmax(r,1e-21f)); float Y=native_sin(th)*native_cos(oa*ph); float d=fabs(r-ob*(1.0f+oc*Y)); aux.DE *= (1.0f + of*native_exp(-od*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_98)
					case 98: { float d=0; for(int k=1;k<=(int)fmax(1,fmin(oa*4,6));k++){ float rk=ob*(float)k; float dk=fabs(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-rk); d+=native_exp(-oc*dk); } aux.DE *= (1.0f + of*d/(oa*4+1e-21f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_99)
					case 99: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float d=fabs(r-oa); float v=native_exp(-ob*d)*native_cos(oc*d); z.x += of*v*z.x/fmax(r,1e-21f)*0.01f; z.y += of*v*z.y/fmax(r,1e-21f)*0.01f; z.z += of*v*z.z/fmax(r,1e-21f)*0.01f; aux.DE *= (1.0f + of*fabs(v)*0.1f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ORBITTRAPTYPE_100)
					case 100: { float d1=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-oa; float d2=native_sqrt((z.x-ob)*(z.x-ob)+z.y*z.y+z.z*z.z)-oc; float d=fmin(fabs(d1),fabs(d2)); float blend=native_sin(z.x*od+z.y*od)*0.5f+0.5f; aux.DE *= (1.0f + of*(d1*(1.0f-blend)+d2*blend)*native_exp(-d)); break; }
#endif

					default: break;
#endif
				}
			}

			// v7.12 [GPU] — MandelTorus DE system (per-section iteration range)
			if (i >= mut->torusIterStart && i < mut->torusIterStop && mut->torusType != 0)
			{
				float tf = mut->torusFactor * mut->torusWeight * mut->masterWeight;
				float ta = mut->torusParamA, tb = mut->torusParamB, tc = mut->torusParamC, td = mut->torusParamD;
				switch(mut->torusType) {
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_1)
					case 1: { float k = ta, DE0 = tb; aux.DE = 1.0/(1.0 + native_exp(-k*(aux.DE - DE0))); break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_2)
					case 2: { float DE0 = ta, sigma = fmax(fabs(tb), 0.01); aux.DE *= native_exp(-(aux.DE-DE0)*(aux.DE-DE0)/(sigma*sigma)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_3)
					case 3: { float threshold = ta, DE_max = fabs(tb)+1.0, DE_min = fabs(tc)*0.01; aux.DE = (aux.DE > threshold) ? DE_max : DE_min; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_4)
					case 4: { float b1=ta, b2=tb, d1=fabs(tc),d2=fabs(td); if(aux.DE<b1) aux.DE=d1; else if(aux.DE<b2) aux.DE=d2; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_5)
					case 5: { float h = native_sin(z.x*127.1+z.y*311.7+z.z*74.7)*43758.5453; h=h-floor(h); aux.DE += tf*(h*2.0-1.0)*ta; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_6)
					case 6: { float jx=z.x*z.x-z.y*z.y+ta, jy=2.0*z.x*z.y+tb, julia_mag=native_sqrt(jx*jx+jy*jy); aux.DE *= (1.0 + tf*0.1*julia_mag); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_7)
					case 7: { aux.DE *= (1.0 + tf*0.1*native_sin(ta*(float)i*0.1)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_8)
					case 8: { float alpha=fmin(fmax(ta,0.01),0.99); aux.DE = alpha*aux.DE + (1.0-alpha)*tb; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_9)
					case 9: { float h1=native_sin(ta*z.x+tb*z.y+tc*z.z), h2=native_sin(td*h1+ta*aux.DE); aux.DE *= (1.0 + tf*h2); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_10)
					case 10: { float v=0,f=ta,a=1.0; for(int k=0;k<4;k++){float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453;h=h-floor(h);v+=a*h;f*=2.0;a*=0.5;} aux.DE *= (1.0 + tf*0.1*v); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_11)
					case 11: { float speed = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE /= (1.0 + tf*speed*ta); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_12)
					case 12: { float sc = fabs(ta) + 0.01; aux.DE *= sc; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_13)
					case 13: { float angle = atan2(z.y,z.x); aux.DE *= (1.0 + tf*fabs(angle)*ta/(M_PI_F)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_14)
					case 14: { float shear = fabs(z.x*z.y*ta) + fabs(z.y*z.z*tb) + fabs(z.z*z.x*tc); aux.DE *= (1.0 + tf*shear); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_15)
					case 15: { float progress = (float)i / fmax((float)(i+10), 1.0); aux.DE *= (1.0 + tf*(1.0-progress)*ta); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_16)
					case 16: { float box = fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z))); if(box > fabs(ta)) aux.DE *= (1.0 + tf*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_17)
					case 17: { float d = native_sqrt((z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc)); if(d < fabs(td)) aux.DE *= (1.0 + tf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_18)
					case 18: { float w = fabs(ta)+0.01; if(fabs(z.x)<w && fabs(z.y)<w) aux.DE *= (1.0 + tf*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_19)
					case 19: { float intensity = native_sin(z.x*ta)*native_sin(z.y*tb)*native_sin(z.z*tc); aux.DE *= (1.0 + tf*0.1*intensity*intensity); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_20)
					case 20: { float ao = 1.0/(1.0 + (float)i*ta*0.01); aux.DE *= (1.0 - tf*ao*fabs(tb)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_21)
					case 21: { float gi = native_sin(z.x*ta+z.y*tb)*0.5+0.5; aux.DE /= (1.0 + tf*gi*fabs(tc)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_22)
					case 22: { float depth = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0 + tf*ta*depth); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_23)
					case 23: { float light_accum = native_sin(z.x*ta)*native_sin(z.y*ta)*0.5+0.5; aux.DE /= (1.0 + tf*light_accum*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_24)
					case 24: { float ss_depth = native_exp(-fabs(ta)*native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)); aux.DE *= (1.0 + tf*ss_depth*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_25)
					case 25: { float wl_diff = fabs(z.x*ta - tb); aux.DE *= (1.0 + tf*tc*wl_diff); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_26)
					case 26: { float caustic = native_sin(z.x*ta*10.0)*native_sin(z.y*tb*10.0); aux.DE *= (1.0 + tf*caustic*caustic*tc); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_27)
					case 27: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), view_dot = z.z/fmax(r,1e-21), fresnel = pow(fmax(1.0-fabs(view_dot),0.0), ta); aux.DE *= (1.0 + tf*fresnel*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_28)
					case 28: { float thin_film = native_sin(ta*native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*M_PI_F*2.0); aux.DE *= (1.0 + tf*thin_film*thin_film*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_29)
					case 29: { float tangent_dot = fabs(z.x*native_cos(ta)+z.y*native_sin(ta))/fmax(native_sqrt(z.x*z.x+z.y*z.y),1e-21); aux.DE *= (1.0 + tf*tangent_dot*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_30)
					case 30: { float subdiv = fmax(1.0, floor(ta*(float)i*0.1+1.0)); aux.DE /= subdiv*tf+1.0; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_31)
					case 31: { float dist = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), lod = fmin(dist*ta, tb); aux.DE *= (1.0 + tf*lod); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_32)
					case 32: { float edge = fabs(z.x-round(z.x*ta)/fmax(ta,1e-21f)) + fabs(z.y-round(z.y*ta)/fmax(ta,1e-21f)); aux.DE *= (1.0f + tf*edge*tb); break; }

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_33)
					case 33: { float h = native_sin(z.x*ta*10.0f)*native_sin(z.y*tb*10.0f)*native_sin(z.z*tc*10.0f); aux.DE += tf*h*td; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_34)
					case 34: { float perturb = native_sin(z.x*ta*20.0f)*native_cos(z.y*tb*20.0f)*native_sin(z.z*tc*20.0f); aux.DE *= (1.0f + tf*perturb*td); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_35)
					case 35: { float depth = native_sin(z.x*ta+z.y*tb)*0.5f+0.5f; aux.DE *= (1.0f + tf*depth*tc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_36)
					case 36: { float n = fmax(fabs(ta), 0.1f); aux.DE /= n; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_37)
					case 37: { float dist = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= native_exp(-tf*fabs(ta)*dist); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_38)
					case 38: { float cos_th = z.z/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),1e-21f); float phase = (1.0f-ta*ta)/(1.0f+ta*ta-2.0f*ta*cos_th+1e-21f); aux.DE *= (1.0f + tf*phase*tb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_39)
					case 39: { float emission = native_sin(z.x*ta)*native_sin(z.y*ta)*native_sin(z.z*ta); emission = emission*emission; aux.DE /= (1.0f + tf*emission*tb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_40)
					case 40: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float theta = atan2(z.z,r2d-ta); float twist = native_sin(tb*phi + tc*theta); aux.DE *= (1.0f + tf*twist*twist); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_41)
					case 41: { float R = fabs(ta)+0.1f; float r_min = fabs(tb)+0.01f; float ratio = R/r_min; aux.DE *= (1.0f + tf*ratio*0.1f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_42)
					case 42: { float R = fabs(ta)+0.1f; float r_min = fabs(tb)+0.01f; float ratio = r_min/R; aux.DE *= (1.0f + tf*ratio); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_43)
					case 43: { float phi = atan2(z.y,z.x); float revolutions = ta*phi/(2.0f*M_PI_F); aux.DE *= (1.0f + tf*native_sin(revolutions*2.0f*M_PI_F)*tb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_44)
					case 44: { float r2 = z.x*z.x+z.y*z.y+z.z*z.z+1e-21f; float w = native_sin(ta*r2); float hopf = native_cos(tb*atan2(z.y,z.x))*native_sin(tc*native_acos(z.z/native_sqrt(r2))); aux.DE *= (1.0f + tf*w*hopf); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_45)
					case 45: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float helix_r = ta + tb*native_sin(tc*phi); float d = fabs(r2d - helix_r); aux.DE *= (1.0f + tf*native_exp(-td*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_46)
					case 46: { float phi = atan2(z.y,z.x); float half_twist = native_sin(phi*0.5f); float r2d = native_sqrt(z.x*z.x+z.y*z.y); float torus_d = fabs(r2d-ta); aux.DE *= (1.0f + tf*half_twist*half_twist*native_exp(-tb*torus_d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_47)
					case 47: { float phi = atan2(z.y,z.x); float R = ta; float r_k = tb*(1.0f+0.5f*native_cos(phi)); float r2d = native_sqrt(z.x*z.x+z.y*z.y); float d = fabs(r2d-R) + fabs(z.z)*r_k; aux.DE *= (1.0f + tf*native_exp(-tc*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_48)
					case 48: { float phi = atan2(z.y,z.x); float genus = fmax(native_floor(fabs(ta)*3+1),1.0f); float fiber = native_sin(genus*phi)*native_cos(tb*z.z); aux.DE *= (1.0f + tf*fiber*fiber*tc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_49)
					case 49: { float phi = atan2(z.y,z.x); float wrapping = native_floor(fabs(ta)*4+2); float companion = native_sin(wrapping*phi)*tb; float r2d = native_sqrt(z.x*z.x+z.y*z.y); float d = fabs(r2d-tc-companion); aux.DE *= (1.0f + tf*native_exp(-td*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_50)
					case 50: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float neg_curv = native_sin(ta*phi)*native_sin(tb*z.z)*native_exp(-tc*fabs(r2d-td)); aux.DE *= (1.0f + tf*neg_curv*neg_curv); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_51)
					case 51: { float phi = atan2(z.y,z.x); float r2d = native_sqrt(z.x*z.x+z.y*z.y); float p=fmax(native_floor(fabs(ta)*3+2),2.0f); float q=fmax(native_floor(fabs(tb)*3+3),3.0f); float knot_r = tc + td*native_cos(q*phi); float knot_z2 = td*native_sin(q*phi); float d = native_sqrt((r2d-knot_r)*(r2d-knot_r)+(z.z-knot_z2)*(z.z-knot_z2)); aux.DE *= (1.0f + tf*native_exp(-d*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_52)
					case 52: { float phi = atan2(z.y,z.x); float r2d = native_sqrt(z.x*z.x+z.y*z.y); float trefoil_r = ta*(2.0f+native_cos(3.0f*phi)); float trefoil_z = ta*native_sin(3.0f*phi); float d = native_sqrt((r2d-trefoil_r)*(r2d-trefoil_r)+(z.z-trefoil_z)*(z.z-trefoil_z)); aux.DE *= (1.0f + tf*native_exp(-tb*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_53)
					case 53: { float phi = atan2(z.y,z.x); float r2d = native_sqrt(z.x*z.x+z.y*z.y); float cinquefoil_r = ta*(2.0f+native_cos(5.0f*phi)); float cinquefoil_z = ta*native_sin(5.0f*phi); float d = native_sqrt((r2d-cinquefoil_r)*(r2d-cinquefoil_r)+(z.z-cinquefoil_z)*(z.z-cinquefoil_z)); aux.DE *= (1.0f + tf*native_exp(-tb*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_54)
					case 54: { float phi = atan2(z.y,z.x); float r2d = native_sqrt(z.x*z.x+z.y*z.y); float fig8_r = ta*(2.0f+native_cos(2.0f*phi)); float fig8_z = ta*native_sin(4.0f*phi)*0.5f; float d = native_sqrt((r2d-fig8_r)*(r2d-fig8_r)+(z.z-fig8_z)*(z.z-fig8_z)); aux.DE *= (1.0f + tf*native_exp(-tb*d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_55)
					case 55: { float t2 = atan2(z.y,z.x)*ta; float r2d = native_sqrt(z.x*z.x+z.y*z.y); float lissajous_r = tb*(2.0f+native_sin(3.0f*t2)*native_cos(2.0f*t2)); float d = fabs(r2d-lissajous_r)+fabs(z.z)*tc; aux.DE *= (1.0f + tf*native_exp(-d*td)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_56)
					case 56: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float theta = atan2(z.z,r2d-ta); float bump = native_sin(tb*phi)*native_sin(tc*theta); aux.DE *= (1.0f + tf*bump*bump*td); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_57)
					case 57: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float R = ta; float r = tb; float torus_d = native_sqrt((r2d-R)*(r2d-R)+z.z*z.z)-r; float corrugation = native_sin(tc*atan2(z.y,z.x)*10.0f)*td; aux.DE *= (1.0f + tf*native_exp(-(torus_d-corrugation)*(torus_d-corrugation))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_58)
					case 58: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float wave_R = ta + tb*native_sin(tc*phi)*native_sin(td*z.z); float d = fabs(r2d-wave_R); aux.DE *= (1.0f + tf*native_exp(-d*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_59)
					case 59: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float spiral_R = ta + tb*phi/(2.0f*M_PI_F); float d = fabs(r2d-spiral_R)+fabs(z.z)*tc; aux.DE *= (1.0f + tf*native_exp(-d*td)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_60)
					case 60: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float star_n = fmax(native_floor(fabs(ta)*5+3),3.0f); float phi = atan2(z.y,z.x); float star_R = tb*(1.0f+tc*native_cos(star_n*phi)); float d = fabs(r2d-star_R)+fabs(z.z)*td; aux.DE *= (1.0f + tf*native_exp(-d*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_61)
					case 61: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float R = ta; float r = tb; float torus_d = native_sqrt((r2d-R)*(r2d-R)+z.z*z.z)-r; float fracture = native_sin(z.x*tc*20.0f)*native_sin(z.y*tc*20.0f)*td; aux.DE *= (1.0f + tf*native_exp(-fabs(torus_d)*5.0f)*(1.0f+fracture)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_62)
					case 62: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float egg_R = ta*(1.0f+tb*native_sin(phi)); float d = native_sqrt((r2d-egg_R)*(r2d-egg_R)+z.z*z.z)-tc; aux.DE *= (1.0f + tf*native_exp(-fabs(d)*td)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_63)
					case 63: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float gear_n = fmax(native_floor(fabs(ta)*8+4),4.0f); float gear_R = tb*(1.0f+tc*fmax(native_cos(gear_n*phi)-0.5f,0.0f)); float d = fabs(r2d-gear_R); aux.DE *= (1.0f + tf*native_exp(-d*td*10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_64)
					case 64: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float R = ta; float r = tb; float torus_d = native_sqrt((r2d-R)*(r2d-R)+z.z*z.z)-r; float erosion = native_sin(z.x*tc*5.0f)*native_sin(z.y*tc*5.0f)*native_sin(z.z*tc*5.0f); aux.DE *= (1.0f + tf*native_exp(-fabs(torus_d)*5.0f)*fabs(erosion)*td); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_65)
					case 65: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float theta = atan2(z.z,r2d-ta); float superformula = native_pow(fabs(native_cos(tb*theta/4.0f)),tc)+native_pow(fabs(native_sin(tb*theta/4.0f)),tc); float sf_r = td*native_pow(superformula,-1.0f/fmax(tc,0.01f)); float d = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-sf_r; aux.DE *= (1.0f + tf*native_exp(-fabs(d)*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_66)
					case 66: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float R = ta; float gravity = 1.0f/fmax((r2d-R)*(r2d-R)+z.z*z.z+0.01f, 0.01f); aux.DE *= (1.0f + tf*fmin(gravity*tb,10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_67)
					case 67: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float B_field = ta*native_sin(tb*phi)/(fmax(fabs(r2d-tc),0.01f)); aux.DE *= (1.0f + tf*fmin(fabs(B_field),10.0f)*td); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_68)
					case 68: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float vortex = ta*native_exp(-tb*((r2d-tc)*(r2d-tc)+z.z*z.z)); float circulation = native_sin(td*atan2(z.y,z.x)); aux.DE *= (1.0f + tf*vortex*circulation); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_69)
					case 69: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float plasma = native_sin(ta*r2d)*native_cos(tb*phi)*native_sin(tc*z.z); float temperature = native_exp(-td*native_sqrt((r2d-1.0f)*(r2d-1.0f)+z.z*z.z)); aux.DE *= (1.0f + tf*plasma*temperature); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_70)
					case 70: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float R = ta; float charge = tb/fmax(native_sqrt((r2d-R)*(r2d-R)+z.z*z.z),0.01f); float screen = native_exp(-tc*native_sqrt((r2d-R)*(r2d-R)+z.z*z.z)); aux.DE *= (1.0f + tf*charge*screen*td); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_71)
					case 71: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float wave1 = native_sin(ta*phi + tb*z.z); float wave2 = native_sin(tc*phi - tb*z.z); float interference = (wave1+wave2)*(wave1+wave2)*0.25f; aux.DE *= (1.0f + tf*interference*td); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_72)
					case 72: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float R = ta; float thermal = native_exp(-tb*((r2d-R)*(r2d-R)+z.z*z.z)); float fluctuation = native_sin(tc*z.x)*native_sin(tc*z.y)*native_sin(tc*z.z); aux.DE *= (1.0f + tf*thermal*(1.0f+td*fluctuation)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_73)
					case 73: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); int modes = (int)fmax(2,fmin(ta*5,10)); float v = 0; for(int m=1;m<=modes;m++) v+=native_sin(m*phi*tb)*native_cos(m*z.z*tc)/m; aux.DE *= (1.0f + tf*v*v*td); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_74)
					case 74: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float R = ta; float diffusion = 1.0f/(1.0f + tb*(float)i*0.01f); float concentration = native_exp(-tc*fabs(r2d-R))*diffusion; aux.DE *= (1.0f + tf*concentration*td); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_75)
					case 75: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float reaction = native_sin(ta*phi)*native_sin(tb*z.z); float diffuse = native_exp(-tc*((r2d-td)*(r2d-td))); float rd = reaction*diffuse; aux.DE *= (1.0f + tf*rd*rd); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_76)
					case 76: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float d1 = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; float d2 = native_sqrt((r2d-tc)*(r2d-tc)+z.z*z.z)-td; aux.DE *= (1.0f + tf*native_exp(-fmin(d1*d1,d2*d2)*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_77)
					case 77: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float ryz = native_sqrt(z.y*z.y+z.z*z.z); float d1 = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; float d2 = native_sqrt((ryz-ta)*(ryz-ta)+z.x*z.x)-tb; aux.DE *= (1.0f + tf*native_exp(-fmin(d1*d1,d2*d2)*tc)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_78)
					case 78: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float rxz = native_sqrt(z.x*z.x+z.z*z.z); float ryz = native_sqrt(z.y*z.y+z.z*z.z); float d1=fabs(native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb); float d2=fabs(native_sqrt((rxz-ta)*(rxz-ta)+z.y*z.y)-tb); float d3=fabs(native_sqrt((ryz-ta)*(ryz-ta)+z.x*z.x)-tb); aux.DE *= (1.0f + tf*native_exp(-fmin(d1,fmin(d2,d3))*tc)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_79)
					case 79: { float phi = atan2(z.y,z.x); float r2d = native_sqrt(z.x*z.x+z.y*z.y); int n = (int)fmax(2,fmin(ta*4,8)); float md = 1e10f; for(int k=0;k<n;k++){ float ang = k*2.0f*M_PI_F/n; float cx = tb*native_cos(ang); float cy = tb*native_sin(ang); float d = native_sqrt((z.x-cx)*(z.x-cx)+(z.y-cy)*(z.y-cy)+z.z*z.z)-tc; if(fabs(d)<md) md=fabs(d); } aux.DE *= (1.0f + tf*native_exp(-md*td)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_80)
					case 80: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float R_var = ta + tb*native_sin(tc*phi); float torus_d = native_sqrt((r2d-R_var)*(r2d-R_var)+z.z*z.z)-td; aux.DE *= (1.0f + tf*native_exp(-torus_d*torus_d*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_81)
					case 81: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float d1 = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; float d2 = native_sqrt((r2d-ta)*(r2d-ta)+(z.z-tc)*(z.z-tc))-tb; aux.DE *= (1.0f + tf*native_exp(-fmin(fabs(d1),fabs(d2))*td)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_82)
					case 82: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float R1 = ta; float r1 = tb; float R2 = tc; float r2 = td; float d1 = native_sqrt((r2d-R1)*(r2d-R1)+z.z*z.z)-r1; float d2 = native_sqrt((r2d-R2)*(r2d-R2)+z.z*z.z)-r2; float smooth = -native_log(fmax(native_exp(-d1*5.0f)+native_exp(-d2*5.0f),1e-21f))/5.0f; aux.DE *= (1.0f + tf*native_exp(-smooth*smooth)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_83)
					case 83: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float torus_d = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; float sphere_d = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-tc; float d = fmax(torus_d, -sphere_d); aux.DE *= (1.0f + tf*native_exp(-fabs(d)*td)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_84)
					case 84: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float torus_d = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; float box_d = fmax(fabs(z.x)-tc,fmax(fabs(z.y)-tc,fabs(z.z)-td))-0.0f; float d = fmax(torus_d,box_d); aux.DE *= (1.0f + tf*native_exp(-fabs(d)*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_85)
					case 85: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float inner_r = tb*(1.0f+tc*native_sin(td*phi)); float torus_d = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-inner_r; aux.DE *= (1.0f + tf*native_exp(-torus_d*torus_d*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_86)
					case 86: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float flow = native_sin(ta*phi-(float)i*tb*0.1f); float torus_d = native_sqrt((r2d-tc)*(r2d-tc)+z.z*z.z)-td; aux.DE *= (1.0f + tf*flow*flow*native_exp(-fabs(torus_d)*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_87)
					case 87: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float omega = ta*(float)i*0.01f; float R_t = tb*(1.0f+tc*native_sin(omega)); float torus_d = native_sqrt((r2d-R_t)*(r2d-R_t)+z.z*z.z)-td; aux.DE *= (1.0f + tf*native_exp(-torus_d*torus_d*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_88)
					case 88: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float stretch = 1.0f + ta*native_sin(tb*phi); float torus_d = native_sqrt((r2d-tc*stretch)*(r2d-tc*stretch)+z.z*z.z)-td/stretch; aux.DE *= (1.0f + tf*native_exp(-torus_d*torus_d*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_89)
					case 89: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phase = ta*(float)i*0.1f; float wobble_z = tb*native_sin(phase); float torus_d = native_sqrt((r2d-tc)*(r2d-tc)+(z.z-wobble_z)*(z.z-wobble_z))-td; aux.DE *= (1.0f + tf*native_exp(-torus_d*torus_d*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_90)
					case 90: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float pulse = native_exp(-ta*((float)i*0.1f-tb)*((float)i*0.1f-tb)); float torus_d = native_sqrt((r2d-tc)*(r2d-tc)+z.z*z.z)-td*(1.0f+pulse); aux.DE *= (1.0f + tf*native_exp(-torus_d*torus_d*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_91)
					case 91: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float bifurcation = ta*native_sin(tb*phi)*native_sin(tc*phi*2.0f); float torus_d = native_sqrt((r2d-td-bifurcation)*(r2d-td-bifurcation)+z.z*z.z)-0.3f; aux.DE *= (1.0f + tf*native_exp(-torus_d*torus_d*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_92)
					case 92: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float chaos = native_sin(ta*z.x)*native_cos(tb*z.y)*native_sin(tc*z.z); float torus_d = native_sqrt((r2d-td)*(r2d-td)+z.z*z.z)-fabs(chaos)*0.5f; aux.DE *= (1.0f + tf*native_exp(-torus_d*torus_d*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_93)
					case 93: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float soliton = 1.0f/cosh(ta*(r2d-tb)); float torus_phase = native_sin(tc*phi+td*z.z); aux.DE *= (1.0f + tf*soliton*torus_phase*torus_phase); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_94)
					case 94: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float breather = native_sin(ta*(float)i*0.1f)*native_sin(tb*phi)/cosh(tc*(r2d-td)); aux.DE *= (1.0f + tf*breather*breather); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_95)
					case 95: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float torus_d = native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; float damping = native_exp(-tc*(float)i*0.01f); aux.DE *= (1.0f + tf*native_sin(torus_d*td*10.0f)*damping); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_96)
					case 96: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float theta = atan2(z.z,r2d-ta); float villarceau = native_sin(phi+theta*tb)*native_sin(phi-theta*tb); aux.DE *= (1.0f + tf*villarceau*villarceau*tc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_97)
					case 97: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float dupin = ta*(1.0f+tb*native_cos(phi))*(1.0f+tc*native_cos(atan2(z.z,r2d-ta))); float d = fabs(native_sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-dupin*0.3f); aux.DE *= (1.0f + tf*native_exp(-d*td)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_98)
					case 98: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float theta = atan2(z.z,r2d-ta); float clifford_r = ta*(native_cos(tb*phi)*native_cos(tc*theta)); float clifford_d = fabs(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-fabs(clifford_r)); aux.DE *= (1.0f + tf*native_exp(-clifford_d*td)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_99)
					case 99: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float lawson_r = ta*native_cos(tb*phi)*native_cos(tc*z.z); float d = fabs(r2d-fabs(lawson_r)-td); aux.DE *= (1.0f + tf*native_exp(-d*5.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TORUSTYPE_100)
					case 100: { float r2d = native_sqrt(z.x*z.x+z.y*z.y); float phi = atan2(z.y,z.x); float theta = atan2(z.z,r2d-ta); float p=fmax(ta,0.1f); float q=fmax(tb,0.1f); float torus_knot_r = tc*(2.0f+native_cos(q/p*phi)); float torus_knot_z = tc*native_sin(q/p*phi); float d = native_sqrt((r2d-torus_knot_r)*(r2d-torus_knot_r)+(z.z-torus_knot_z)*(z.z-torus_knot_z))-td; aux.DE *= (1.0f + tf*native_exp(-fabs(d)*5.0f)); break; }
#endif

					default: break;
#endif
				}
			}


				// v7.13 — Amazing Surf 1-4 DE system (per-section iteration range)
				if (mut->asEnabled && i >= mut->asIterStart && i < mut->asIterStop && mut->asType != 0)
				{
					float sf = mut->asFactor * mut->asWeight * mut->masterWeight;
					float ta = mut->asParamA, tb = mut->asParamB;
					float tc = mut->asParamC, td = mut->asParamD;
					float4 z_orig_as = z; float de_orig_as = aux.DE;
					switch(mut->asType) {
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_1)
						case 1: { float k = ta, DE0_1 = tb; aux.DE = 1.0/(1.0 + native_exp(-k*(aux.DE - DE0_1))); break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_2)
						case 2: { float DE0_2 = ta, sigma2 = fmax(fabs(tb), 0.01f); aux.DE *= native_exp(-(aux.DE-DE0_2)*(aux.DE-DE0_2)/(sigma2*sigma2)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_3)
						case 3: { float threshold3 = ta, DE_max3 = fabs(tb)+1.0f, DE_min3 = fabs(tc)*0.01f; aux.DE = (aux.DE > threshold3) ? DE_max3 : DE_min3; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_4)
						case 4: { float b1_4=ta, b2_4=tb, d1_4=fabs(tc), d2_4=fabs(td); if(aux.DE<b1_4) aux.DE=d1_4; else if(aux.DE<b2_4) aux.DE=d2_4; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_5)
						case 5: { float h = native_sin(z.x*127.1+z.y*311.7+z.z*74.7)*43758.5453; h=h-floor(h); aux.DE += sf*(h*2.0-1.0)*ta; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_6)
						case 6: { float jx6=z.x*z.x-z.y*z.y+ta, jy6=2.0f*z.x*z.y+tb, julia_mag6=native_sqrt(jx6*jx6+jy6*jy6); aux.DE *= (1.0f + sf*0.1f*julia_mag6); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_7)
						case 7: { aux.DE *= (1.0 + sf*0.1*native_sin(ta*(float)i*0.1)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_8)
						case 8: { float alpha=fmin(fmax(ta,0.01),0.99); aux.DE = alpha*aux.DE + (1.0-alpha)*tb; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_9)
						case 9: { float h1_9=native_sin(ta*z.x+tb*z.y+tc*z.z), h2_9=native_sin(td*h1_9+ta*aux.DE); aux.DE *= (1.0f + sf*h2_9); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_10)
						case 10: { float v=0,f=ta,a=1.0; for(int k=0;k<4;k++){float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453;h=h-floor(h);v+=a*h;f*=2.0;a*=0.5;} aux.DE *= (1.0 + sf*0.1*v); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_11)
						case 11: { float speed = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE /= (1.0 + sf*speed*ta); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_12)
						case 12: { float sc = fabs(ta) + 0.01; aux.DE *= sc; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_13)
						case 13: { float angle = atan2(z.y,z.x); aux.DE *= (1.0 + sf*fabs(angle)*ta/M_PI_F); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_14)
						case 14: { float shear = fabs(z.x*z.y*ta) + fabs(z.y*z.z*tb) + fabs(z.z*z.x*tc); aux.DE *= (1.0 + sf*shear); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_15)
						case 15: { float progress = (float)i / fmax((float)(i+10), 1.0f); aux.DE *= (1.0f + sf*(1.0f-progress)*ta); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_16)
						case 16: { float box = fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z))); if(box > fabs(ta)) aux.DE *= (1.0 + sf*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_17)
						case 17: { float d = native_sqrt((z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc)); if(d < fabs(td)) aux.DE *= (1.0 + sf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_18)
						case 18: { float w = fabs(ta)+0.01; if(fabs(z.x)<w && fabs(z.y)<w) aux.DE *= (1.0 + sf*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_19)
						case 19: { float intensity = native_sin(z.x*ta)*native_sin(z.y*tb)*native_sin(z.z*tc); aux.DE *= (1.0 + sf*0.1*intensity*intensity); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_20)
						case 20: { float ao = 1.0/(1.0 + (float)i*ta*0.01); aux.DE *= (1.0 - sf*ao*fabs(tb)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_21)
						case 21: { float gi = native_sin(z.x*ta+z.y*tb)*0.5+0.5; aux.DE /= (1.0 + sf*gi*fabs(tc)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_22)
						case 22: { float depth = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0 + sf*ta*depth); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_23)
						case 23: { float light_accum = native_sin(z.x*ta)*native_sin(z.y*ta)*0.5+0.5; aux.DE /= (1.0 + sf*light_accum*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_24)
						case 24: { float ss_depth = native_exp(-fabs(ta)*native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)); aux.DE *= (1.0 + sf*ss_depth*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_25)
						case 25: { float wl_diff = fabs(z.x*ta - tb); aux.DE *= (1.0 + sf*tc*wl_diff); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_26)
						case 26: { float caustic = native_sin(z.x*ta*10.0)*native_sin(z.y*tb*10.0); aux.DE *= (1.0 + sf*caustic*caustic*tc); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_27)
						case 27: { float r27 = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), view_dot27 = z.z/fmax(r27,1e-21f), fresnel27 = pow(fmax(1.0f-fabs(view_dot27),0.0f), ta); aux.DE *= (1.0f + sf*fresnel27*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_28)
						case 28: { float thin_film = native_sin(ta*native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*M_PI_F*2.0); aux.DE *= (1.0 + sf*thin_film*thin_film*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_29)
						case 29: { float tangent_dot = fabs(z.x*native_cos(ta)+z.y*native_sin(ta))/fmax(native_sqrt(z.x*z.x+z.y*z.y),1e-21); aux.DE *= (1.0 + sf*tangent_dot*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_30)
						case 30: { float subdiv = fmax(1.0, fabs(ta)); aux.DE /= (1.0 + sf*subdiv*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_31)
						case 31: { float dist31 = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), lod31 = fmax(0.1f, dist31*ta); aux.DE *= lod31; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_32)
						case 32: { float edge_len = fabs(z.x-z.y) + fabs(z.y-z.z) + fabs(z.z-z.x); aux.DE *= (1.0f + sf*ta*edge_len*tb); break; }

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_33)
						case 33: { float disp = native_sin(z.x*ta*5.0f)*native_sin(z.y*tb*5.0f)*native_sin(z.z*tc*5.0f); aux.DE += sf*disp*td; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_34)
						case 34: { float h = native_sin(z.x*ta*7.0f+z.y*tb*11.0f+z.z*tc*13.0f)*43758.5453f; h=h-native_floor(h); aux.DE *= (1.0f + sf*(h*2.0f-1.0f)*td*0.1f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_35)
						case 35: { float parallax = fabs(ta)*z.z/fmax(fabs(tb),0.01f); aux.DE *= (1.0f + sf*parallax*0.1f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_36)
						case 36: { float n = fmax(fabs(ta)+1.0f, 1.01f); aux.DE /= n; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_37)
						case 37: { float dist_traveled = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= native_exp(-sf*fabs(ta)*dist_traveled); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_38)
						case 38: { float cos_theta = z.z/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),1e-21f); float phase = (1.0f+cos_theta*cos_theta)*0.75f; aux.DE *= (1.0f + sf*phase*ta); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_39)
						case 39: { float emission = native_sin(z.x*ta)*native_sin(z.y*ta)*0.5f+0.5f; aux.DE /= (1.0f + sf*emission*fabs(tb)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_40)
						case 40: { float curl_approx = native_sin(z.y*ta)*native_cos(z.z*tb) - native_cos(z.y*ta)*native_sin(z.z*tb); aux.DE *= (1.0f + sf*fabs(curl_approx)*tc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_41)
						case 41: { float grad = (native_sin(z.x*ta)-native_sin((z.x+0.01f)*ta))/0.01f; aux.DE /= (1.0f + sf*fabs(grad)*tb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_42)
						case 42: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float mass_d = fmax(r - ta, 0.01f); aux.DE *= (1.0f + sf*tb/(mass_d*mass_d)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_43)
						case 43: { float v2 = (z.x*z.x+z.y*z.y+z.z*z.z)*ta*ta; float lorentz = native_sqrt(fmax(1.0f - fmin(v2, 0.99f), 0.01f)); aux.DE *= lorentz; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_44)
						case 44: { float barrier = fabs(z.x - ta); aux.DE *= native_exp(-sf*fabs(tb)*barrier); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_45)
						case 45: { float psi2 = native_sin(ta*z.x)*native_sin(tb*z.y)*native_sin(tc*z.z); aux.DE *= (1.0f + sf*psi2*psi2); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_46)
						case 46: { float momentum = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*ta; float pos = fmax(fabs(z.x), 0.01f); aux.DE *= (1.0f + sf*tb/(2.0f*momentum*pos+0.01f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_47)
						case 47: { float spin_dot = z.x*native_sin(ta)+z.y*native_cos(ta)+z.z*native_sin(tb); aux.DE *= (1.0f + sf*tc*spin_dot); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_48)
						case 48: { float corr = native_sin(z.x*ta)*native_sin((-z.x)*ta) + native_sin(z.y*tb)*native_sin((-z.y)*tb); aux.DE *= (1.0f + sf*fabs(corr)*tc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_49)
						case 49: { float decay = native_exp(-sf*fabs(ta)*(float)i*0.01f); aux.DE *= decay; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_50)
						case 50: { float entropy = native_sin(z.x*ta*3.0f)*native_sin(z.y*tb*5.0f)*native_sin(z.z*tc*7.0f); float temp = fabs(td)+0.01f; aux.DE *= (1.0f + sf*temp*entropy*entropy); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_51)
						case 51: { float kT = fmax(fabs(ta)*fabs(tb), 0.01f); aux.DE *= (1.0f + sf*tc/kT); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_52)
						case 52: { float vel_grad = fabs(z.x-z.y)*ta + fabs(z.y-z.z)*tb; aux.DE *= (1.0f + sf*tc*vel_grad); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_53)
						case 53: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float curv = 1.0f/fmax(r,0.01f); aux.DE *= (1.0f + sf*ta*curv); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_54)
						case 54: { float tube_r = fmax(fabs(native_sqrt(z.x*z.x+z.y*z.y) - ta), 0.01f); aux.DE *= (1.0f + sf*native_cos(tb)/tube_r); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_55)
						case 55: { float conc_grad = fabs(native_sin(z.x*ta) - native_sin(z.y*ta)); aux.DE *= (1.0f + sf*tb*conc_grad); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_56)
						case 56: { float lap = native_sin((z.x+0.01f)*ta)+native_sin((z.x-0.01f)*ta)-2.0f*native_sin(z.x*ta); aux.DE += sf*tb*lap; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_57)
						case 57: { float vel_dot = native_sin(z.x*ta)*native_cos(z.y*tb); aux.DE *= (1.0f + sf*vel_dot*tc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_58)
						case 58: { float v=0,f=ta,a=1.0f; for(int k=0;k<4;k++){float h=native_sin(z.x*f*12.9f+z.y*f*78.2f+z.z*f*45.1f)*43758.5453f;h=h-native_floor(h);v+=a*h;f*=2.0f;a*=0.5f;} aux.DE *= (1.0f + sf*v*tb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_59)
						case 59: { float front = fabs(z.x - ta*i*0.01f); float shock = (front < fabs(tb)) ? tc : 1.0f; aux.DE *= shock; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_60)
						case 60: { float freq_diff = fabs(native_sin(z.x*ta) - native_sin(z.x*tb)); float Q = fmax(fabs(tc), 0.1f); aux.DE *= (1.0f + sf*Q*1.0f/fmax(freq_diff+0.01f, 0.01f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_61)
						case 61: { float phase_diff = ta*z.x - tb*z.y; aux.DE *= (1.0f + sf*native_cos(phase_diff)*tc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_62)
						case 62: { float v_source = ta * 0.1f; float angle = atan2(z.y, z.x); aux.DE *= (1.0f + sf*v_source*native_cos(angle)*tb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_63)
						case 63: { float theta = atan2(z.y, z.x); aux.DE *= (1.0f + sf*ta*native_cos(2.0f*theta)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_64)
						case 64: { float phi2 = atan2(z.z, native_sqrt(z.x*z.x+z.y*z.y)); aux.DE *= (1.0f + sf*ta*fabs(native_sin(2.0f*phi2))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_65)
						case 65: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float path = r * fabs(ta) * fabs(tb); aux.DE *= (1.0f + sf*tc*path); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_66)
						case 66: { float lat_pt = fmod(fabs(z.x*ta), 1.0f); float bandgap = (lat_pt < 0.5f) ? 1.0f : tb; aux.DE *= bandgap; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_67)
						case 67: { float surf_dist = fabs(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z) - ta); float skin = fmax(fabs(tb), 0.01f); aux.DE *= (1.0f + sf*tc*native_exp(-surf_dist/skin)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_68)
						case 68: { float neg_idx = fabs(ta); aux.DE *= (1.0f + sf*neg_idx*fabs(tb)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_69)
						case 69: { float winding = native_sin(z.x*ta)*native_cos(z.y*tb) + native_cos(z.x*ta)*native_sin(z.y*tb); aux.DE *= (1.0f + sf*fabs(winding)*tc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_70)
						case 70: { float charge = native_sin(z.x*ta*5.0f)*native_sin(z.y*tb*5.0f)*native_sin(z.z*tc*5.0f); aux.DE *= (1.0f + sf*charge*charge*td); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_71)
						case 71: { float curl_mag = fabs(native_sin(z.y*ta)-native_sin(z.z*ta)) + fabs(native_sin(z.z*tb)-native_sin(z.x*tb)); aux.DE *= (1.0f + sf*curl_mag*tc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_72)
						case 72: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float sech_val = 1.0f/cosh(fmin(ta*(r-tb), 20.0f)); aux.DE *= (1.0f + sf*tc*sech_val); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_73)
						case 73: { float S = fabs(ta)*native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0f + sf*tb*native_exp(-fmin(S,20.0f))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_74)
						case 74: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float monopole = fabs(ta)/fmax(r,0.01f); aux.DE *= (1.0f + sf*monopole*tb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_75)
						case 75: { float d_axis = native_sqrt(z.y*z.y+z.z*z.z); aux.DE *= (1.0f + sf*ta*native_log(fmax(d_axis,0.01f))*tb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_76)
						case 76: { float d_brane = fabs(z.x - ta); float delta_approx = native_exp(-d_brane*d_brane*100.0f); aux.DE *= (1.0f + sf*tb*delta_approx); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_77)
						case 77: { float throat_d = (z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc); float throat_r = fmax(fabs(td), 0.01f); aux.DE *= (1.0f + sf*native_exp(-throat_d/(throat_r*throat_r))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_78)
						case 78: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float rs = fmax(fabs(ta), 0.01f); aux.DE /= fmax(1.0f - rs/fmax(r,rs+0.01f), 0.01f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_79)
						case 79: { float jet_d = z.y*z.y+z.z*z.z; float jet_w = fmax(fabs(tb), 0.01f); aux.DE *= (1.0f + sf*ta*native_exp(-jet_d/(jet_w*jet_w))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_80)
						case 80: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float halo = 1.0f/(1.0f + r*r/(fmax(ta*ta,0.01f))); aux.DE *= (1.0f + sf*tb*halo); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_81)
						case 81: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= native_exp(sf*fabs(ta)*r*0.01f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_82)
						case 82: { float d_string = native_sqrt(z.y*z.y+z.z*z.z); float horizon = fmax(fabs(tb), 0.01f); aux.DE *= (1.0f + sf*ta*native_log(fmax(d_string/horizon,0.01f))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_83)
						case 83: { float d_wall = fabs(z.x - ta); float thickness = fmax(fabs(tb), 0.01f); aux.DE *= (1.0f + sf*tc*tanh(d_wall/thickness)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_84)
						case 84: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float theta2 = atan2(z.y,z.x); float phi2 = native_acos(z.z/fmax(r,1e-21f)); float Ylm = native_sin(ta*theta2)*native_cos(tb*phi2); aux.DE *= (1.0f + sf*tc*Ylm*Ylm); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_85)
						case 85: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float efold = r*fabs(ta); aux.DE *= native_exp(sf*fmin(efold*tb, 10.0f)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_86)
						case 86: { float decay_t = native_exp(-fabs(ta)*(float)i*0.01f); aux.DE *= (1.0f + sf*tb*decay_t*tc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_87)
						case 87: { float baryon = native_sin(z.x*ta)*native_sin(z.y*tb); float rate = native_exp(-fabs(tc)*(float)i*0.01f); aux.DE *= (1.0f + sf*baryon*baryon*rate*td); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_88)
						case 88: { float ion_frac = native_exp(-fabs(ta)/fmax(fabs(tb)*(float)i*0.01f+0.01f, 0.01f)); aux.DE *= (1.0f + sf*ion_frac*tc); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_89)
						case 89: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float scale_a = fmax(r*ta, 0.01f); float energy = 1.0f/(scale_a*scale_a); aux.DE *= (1.0f + sf*native_sqrt(energy)*tb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_90)
						case 90: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float scale_a = fmax(r*ta, 0.01f); aux.DE /= fmax(scale_a*tb, 0.01f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_91)
						case 91: { float ent_max = fabs(ta); float heat_time = fmax(fabs(tb), 0.01f); aux.DE *= (1.0f + sf*ent_max*(1.0f-native_exp(-(float)i*0.01f/heat_time))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_92)
						case 92: { float bubble = native_sin(z.x*ta*5.0f)*native_sin(z.y*tb*5.0f)*native_sin(z.z*tc*5.0f); aux.DE *= (1.0f + sf*fabs(bubble)*td); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_93)
						case 93: { float barrier2 = fabs(ta); float tunnel = native_exp(-barrier2*native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)); aux.DE *= (1.0f + sf*tunnel*tb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_94)
						case 94: { float order = native_sin(z.x*ta)*native_sin(z.y*tb); float latent = fabs(tc); aux.DE *= (1.0f + sf*latent*order*order); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_95)
						case 95: { float d_crit = native_sqrt((z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc)); float expo = fmax(fabs(td), 0.1f); aux.DE *= native_pow(fmax(d_crit, 0.01f), -expo); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_96)
						case 96: { float cutoff = fmax(fabs(ta), 0.01f); float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0f + sf*tb*native_log(fmax(cutoff/fmax(r,0.01f), 0.01f))); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_97)
						case 97: { float div_approx = native_cos(z.x*ta)*native_sin(z.y*tb)*native_cos(z.z*tc); aux.DE *= (1.0f + sf*fabs(div_approx)*td); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_98)
						case 98: { float vev = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*ta; aux.DE *= (1.0f + sf*vev*vev*tb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_99)
						case 99: { float grad_phase = fabs(native_cos(z.x*ta)-native_cos(z.y*ta)) + fabs(native_cos(z.y*tb)-native_cos(z.z*tb)); aux.DE *= (1.0f + sf*tc*grad_phase); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_ASTYPE_100)
						case 100: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float higgs = ta*tb*r*r; aux.DE *= (1.0f + sf*higgs); break; }
#endif

					default: break;
#endif
					}
					float as_blend = clamp(mut->asWeight * mut->masterWeight, 0.0f, 1.0f);
					z = z_orig_as + (z - z_orig_as) * as_blend;
					aux.DE = de_orig_as + (aux.DE - de_orig_as) * as_blend;
				}

				// v7.13 — SphereTree/Menger DE system (per-section iteration range)
				if (mut->smEnabled && i >= mut->smIterStart && i < mut->smIterStop && mut->smType != 0)
				{
					float sf = mut->smFactor * mut->smWeight * mut->masterWeight;
					float ta = mut->smParamA, tb = mut->smParamB;
					float tc = mut->smParamC, td = mut->smParamD;
					float4 z_orig_sm = z; float de_orig_sm = aux.DE;
					switch(mut->smType) {
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_1)
						case 1: { float branch = 2.0 + floor(3.0*native_sin((float)i*ta*0.1)); aux.DE *= fmax(branch*tb, 0.01); break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_2)
						case 2: { float bx=fmax(ta,1.0),by=fmax(tb,1.0),bz=fmax(tc,1.0); aux.DE *= fmax(fmax(bx,by),bz)*sf; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_3)
						case 3: { float angle = (float)i * 2.39996322972865332 * ta, cosA=native_cos(angle),sinA=native_sin(angle), nx=z.x*cosA-z.y*sinA; z.y=z.x*sinA+z.y*cosA; z.x=nx; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_4)
						case 4: { float jm = native_sin(z.x*ta)*native_cos(z.y*tb), r_ratio = 1.0 + sf*0.3*jm; aux.DE *= r_ratio; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_5)
						case 5: { float h = native_sin(z.x*ta*127.1+z.y*ta*311.7+z.z*ta*74.7)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + sf*(h*2.0-1.0)*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_6)
						case 6: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), d1 = r - ta, d2 = r - tb; aux.DE *= (1.0 + sf*native_exp(-fmin(d1*d1,d2*d2)*tc)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_7)
						case 7: { float w = fabs(ta)+0.01, wd = w*native_sin(z.x*tb)*native_cos(z.y*tc); aux.DE *= (1.0 + sf*wd*td); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_8)
						case 8: { float ax=fmax(fabs(ta),0.01),ay=fmax(fabs(tb),0.01),az=fmax(fabs(tc),0.01), ell = native_sqrt((z.x/ax)*(z.x/ax)+(z.y/ay)*(z.y/ay)+(z.z/az)*(z.z/az))-1.0; aux.DE *= (1.0 + sf*native_exp(-ell*ell*td)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_9)
						case 9: { float r2d = native_sqrt(z.x*z.x+z.y*z.y), R=fabs(ta)+0.1,r=fabs(tb)+0.01, td2 = (r2d-R)*(r2d-R)+z.z*z.z-r*r; aux.DE *= (1.0 + sf*native_exp(-fabs(td2)*tc)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_10)
						case 10: { float px=z.x,py=z.y,pz=z.z, seg_d=fabs(pz)-fabs(ta), cap_d=native_sqrt(px*px+py*py+fmax(seg_d,0.0)*fmax(seg_d,0.0))-fabs(tb); aux.DE *= (1.0 + sf*native_exp(-cap_d*cap_d*tc)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_11)
						case 11: { float theta=atan2(z.y,z.x), phi2=acos(z.z/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),1e-21)), m=fmax(ta,1.0), sf_r=pow(fmax(pow(fabs(native_cos(m*theta/4.0)),tc)+pow(fabs(native_sin(m*theta/4.0)),tc),1e-21),-1.0/fmax(tb,0.1)), r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0 + sf*native_exp(-fabs(r-sf_r*td)*5.0)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_12)
						case 12: { float jx=z.x*z.x-z.y*z.y+ta, jy=2.0*z.x*z.y+tb; z.x=jx; z.y=jy; aux.DE *= 2.0*native_sqrt(jx*jx+jy*jy); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_13)
						case 13: { float mx=z.x*z.x-z.y*z.y+z.x, my=2.0*z.x*z.y+z.y; z.x=mx; z.y=my; aux.DE *= 2.0*native_sqrt(mx*mx+my*my); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_14)
						case 14: { float a1=ta*M_PI_F/180.0, a2=tb*M_PI_F/180.0, ca1=native_cos(a1),sa1=native_sin(a1), newx=z.x+z.x*ca1-z.y*sa1, newy=z.y+z.x*sa1+z.y*ca1; z.x=newx*0.5; z.y=newy*0.5; z.z*=tc; aux.DE *= fabs(tc); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_15)
						case 15: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), koch_amp = ta*native_sin(r*tb*10.0); aux.DE *= (1.0 + sf*koch_amp*koch_amp); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_16)
						case 16: { float scale4 = fabs(ta)+1.0; if(z.x+z.y<0.0){float t=z.x;z.x=-z.y;z.y=-t;} if(z.x+z.z<0.0){float t=z.x;z.x=-z.z;z.z=-t;} if(z.y+z.z<0.0){float t=z.y;z.y=-z.z;z.z=-t;} z = z*scale4 - (float4)(1,1,1,0.0f)*(scale4-1.0)*tb; aux.DE = aux.DE*scale4+1.0; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_17)
						case 17: { float r17=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), mde17; if(r17<1e-21f)r17=1e-21f; mde17=ta*ta/r17/r17; z*=mde17; aux.DE*=mde17; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_18)
						case 18: { float h=native_sin(z.x*ta*12.9898+z.y*tb*78.233+z.z*tc*45.164)*43758.5453; h=h-floor(h); z.x+=h*td*0.1; z.y+=(1.0-h)*td*0.1; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_19)
						case 19: { float min_dist=fabs(ta)+0.1, h=native_sin(z.x*12.9898+z.y*78.233)*43758.5453; h=h-floor(h); z.x=floor(z.x/min_dist+h)*min_dist; z.y=floor(z.y/min_dist+h)*min_dist; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_20)
						case 20: { float h=native_sin(z.x*12.9898+z.y*78.233+z.z*45.164)*43758.5453; h=fabs(h-floor(h)); z.x+=h*ta*0.1; z.y+=(1.0-h)*tb*0.1; z.z+=fabs(native_sin(h*tc))*td*0.1; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_21)
						case 21: { float theta = (float)i * 2.39996322972865332, r = native_sqrt((float)i+0.5)*ta; z.x += r*native_cos(theta)*sf*0.1; z.y += r*native_sin(theta)*sf*0.1; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_22)
						case 22: { float phi3 = 1.6180339887, r_n = ta/pow(phi3, (float)i); aux.DE *= 1.0/phi3; z *= r_n/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),0.01); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_23)
						case 23: { float r_n = ta * native_exp(-(float)i * fabs(tb)); aux.DE *= native_exp(-fabs(tb)); z *= r_n/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),0.01); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_24)
						case 24: { float n = fmax((float)(i)+1.0f, 1.0f), r_n = ta / (1.0 + native_log(n)*tb); aux.DE *= 1.0/(1.0+native_log(n)*tb); z *= r_n/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),0.01); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_25)
						case 25: { float n = fmax((float)(i)+1.0f, 1.0f), p = fmax(fabs(ta), 0.1f); aux.DE *= 1.0f/native_powr(n,p); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_26)
						case 26: { float sc = 3.0 + 0.5*native_sin((float)i*ta); z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0.0f)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_27)
						case 27: { float sx=fmax(ta,1.0),sy=fmax(tb,1.0),sz=fmax(tc,1.0); z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z.x=z.x*sx-(sx-1.0); z.y=z.y*sy-(sy-1.0); z.z=z.z*sz-(sz-1.0); aux.DE=aux.DE*fmax(fmax(sx,sy),sz)+1.0; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_28)
						case 28: { float h28=native_sin(z.x*ta*127.1+z.y*ta*311.7+z.z*ta*74.7)*43758.5453, sc28=3.0f; h28=h28-floor(h28); z=fabs(z)+(float4)(h28*tb,h28*tb,h28*tb,0.0f)*0.1f; if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc28-(float4)(1,1,1,0.0f)*(sc28-1.0f); aux.DE=aux.DE*sc28+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_29)
						case 29: { float angle29=ta*M_PI_F/180.0f, ca29=native_cos(angle29),sa29=native_sin(angle29), nx29=z.x*ca29-z.y*sa29, ny29=z.x*sa29+z.y*ca29, sc29=3.0f; z.x=fabs(nx29);z.y=fabs(ny29);z.z=fabs(z.z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc29-(float4)(1,1,1,0.0f)*(sc29-1.0f); aux.DE=aux.DE*sc29+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_30)
						case 30: { float eps30=fmax(fabs(ta),0.01f), sc30=3.0f, t30=0.0f; z.x=fabs(z.x);z.y=fabs(z.y);z.z=fabs(z.z); if(z.x<z.y){t30=z.x+(z.y-z.x)*0.5f*(1.0f+tanh((z.y-z.x)/eps30));z.y=z.y-(z.y-z.x)*0.5f*(1.0f+tanh((z.y-z.x)/eps30));z.x=z.y;z.y=t30;} if(z.x<z.z){t30=z.x;z.x=z.z;z.z=t30;} if(z.y<z.z){t30=z.y;z.y=z.z;z.z=t30;} z=z*sc30-(float4)(1,1,1,0.0f)*(sc30-1.0f); aux.DE=aux.DE*sc30+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_31)
						case 31: { float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0.0f)*(sc-1.0)+(float4)(ta,tb,tc,0.0f); aux.DE=aux.DE*sc+1.0; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_32)
						case 32: { float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); z.x+=aux.const_c.x*ta; z.y+=aux.const_c.y*ta; z.z+=aux.const_c.z*ta; aux.DE=aux.DE*sc+1.0f; break; }

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_33)
						case 33: { float sc=3.0f; float period=fmax(fabs(ta),0.1f); z=float4(fmod(z.x+100.0f*period,period)-period*0.5f, fmod(z.y+100.0f*period,period)-period*0.5f, fmod(z.z+100.0f*period,period)-period*0.5f, z.w); z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_34)
						case 34: { float sc=3.0f; float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<1e-21f)r2=1e-21f; float inv=ta*ta/r2; z*=inv; aux.DE*=inv; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_35)
						case 35: { float lim=fabs(ta)+0.5f; if(z.x>lim)z.x=2.0f*lim-z.x; if(z.x<-lim)z.x=-2.0f*lim-z.x; if(z.y>lim)z.y=2.0f*lim-z.y; if(z.y<-lim)z.y=-2.0f*lim-z.y; if(z.z>lim)z.z=2.0f*lim-z.z; if(z.z<-lim)z.z=-2.0f*lim-z.z; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_36)
						case 36: { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=fabs(ta)*fabs(ta); float fixedR2=1.0f; float m; if(r2<minR2)m=fixedR2/minR2; else if(r2<fixedR2)m=fixedR2/r2; else m=1.0f; z*=m; aux.DE*=m; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_37)
						case 37: { int n=(int)fmax(ta,2.0f); float angle=M_PI_F/n; for(int k=0;k<n;k++){float a=k*2.0f*angle; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0f){z.x-=2.0f*d*native_cos(a);z.y-=2.0f*d*native_sin(a);}} float sc=3.0f; z=z*sc-float4(1,1,1,0)*(sc-1.0f)*tb; aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_38)
						case 38: { z.x=fabs(z.x);z.y=-fabs(z.y);z.z=fabs(z.z); float sc=3.0f; if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_39)
						case 39: { float twist_k=ta*0.01f; float angle=twist_k*(float)i; float ca=native_cos(angle),sa=native_sin(angle); float nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_40)
						case 40: { float bend=ta*0.001f; z.z+=bend*(z.x*z.x+z.y*z.y); float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_41)
						case 41: { float shear=ta*0.1f; z.x+=shear*z.y; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_42)
						case 42: { float taper=ta*0.01f; z.x*=(1.0f-taper*z.z); z.y*=(1.0f-taper*z.z); float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_43)
						case 43: { float period=fmax(fabs(ta),0.1f); z=float4(fmod(z.x+100.0f*period,period)-period*0.5f, fmod(z.y+100.0f*period,period)-period*0.5f, fmod(z.z+100.0f*period,period)-period*0.5f, z.w); float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_44)
						case 44: { float sc1=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc1-float4(1,1,1,0)*(sc1-1.0f); aux.DE=aux.DE*sc1+1.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc1-float4(1,1,1,0)*(sc1-1.0f); aux.DE=aux.DE*sc1+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_45)
						case 45: { float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*fabs(sc)+1.0f; float surfScale=fabs(ta)+0.5f; z.x=fabs(z.x+surfScale)-fabs(z.x-surfScale)-z.x; z.y=fabs(z.y+surfScale)-fabs(z.y-surfScale)-z.y; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_46)
						case 46: { float sc=3.0f; float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=fabs(ta)*fabs(ta); float fixedR2=1.0f; float m; if(r2<minR2)m=fixedR2/minR2; else if(r2<fixedR2)m=fixedR2/r2; else m=1.0f; z*=m; aux.DE=aux.DE*m; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_47)
						case 47: { float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; float k_angle=ta*M_PI_F/180.0f; float3 nv=(float3)(native_cos(k_angle),native_sin(k_angle),0.0f); float3 zv=z.xyz; float dotv=dot(zv,nv); if(dotv<0.0f){zv=zv-nv*(2.0f*dotv); z=(float4)(zv,z.w);} break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_48)
						case 48: { float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; z+=float4(aux.const_c.x*ta,aux.const_c.y*ta,aux.const_c.z*ta,0)*tb; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_49)
						case 49: { float sc=3.0f+0.1f*native_sin((float)i*ta); z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*fabs(sc)+1.0f; z=float4(0.9f*z.x+0.1f*ta,0.9f*z.y+0.1f*tb,0.9f*z.z+0.1f*tc,z.w); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_50)
						case 50: { float h1=native_sin(ta*z.x+tb*z.y+tc*z.z); float h2=native_sin(td*h1+ta*(float)i*0.1f); float sc=3.0f+sf*h2*0.1f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*fabs(sc)+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_51)
						case 51: { float sc=3.0f; float4 zz=fabs(z); float vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){float t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=float4(vals[0],vals[1],vals[2],vals[3])*sc-float4(1,1,1,1)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_52)
						case 52: { float sc=3.0f; float v[5]={fabs(z.x),fabs(z.y),fabs(z.z),fabs(z.w),fabs(native_sin(z.x+z.y))}; for(int a=0;a<5;a++)for(int b=a+1;b<5;b++){if(v[a]<v[b]){float t=v[a];v[a]=v[b];v[b]=t;}} z=float4(v[0],v[1],v[2],v[3])*sc-float4(1,1,1,1)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_53)
						case 53: { float sc=3.0f; z.w=ta; float4 zz=fabs(z); float vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){float t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=float4(vals[0],vals[1],vals[2],vals[3])*sc-float4(1,1,1,1)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_54)
						case 54: { float angle4d=ta*M_PI_F/180.0f*(float)i; float ca=native_cos(angle4d),sa=native_sin(angle4d); float nx=z.x*ca-z.w*sa; z.w=z.x*sa+z.w*ca; z.x=nx; float sc=3.0f; float4 zz=fabs(z); float vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){float t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=float4(vals[0],vals[1],vals[2],vals[3])*sc-float4(1,1,1,1)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_55)
						case 55: { float sc=3.0f; float4 zz=fabs(z); float vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){float t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=float4(vals[0],vals[1],vals[2],vals[3])*sc-float4(1,1,1,1)*(sc-1.0f)+float4(ta,tb,tc,td); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_56)
						case 56: { float sc=3.0f; float qn=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w); z.w=qn*ta; float4 zz=fabs(z); float vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){float t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=float4(vals[0],vals[1],vals[2],vals[3])*sc-float4(1,1,1,1)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_57)
						case 57: { float sc=3.0f; float qr=z.x,qi=z.y,qj=z.z,qk=z.w; z.x=qr*qi-qj*qk; z.y=qr*qj+qi*qk; z.z=qr*qk-qi*qj; z.w=qr*qr-qi*qi-qj*qj-qk*qk; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,1)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_58)
						case 58: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w); float d=tanh(fmin(r*ta,10.0f)); float4 unit=z/fmax(r,1e-21f); z=unit*d; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); float ch=cosh(fmin(r*ta,20.0f)); aux.DE=aux.DE*sc/(ch*ch)+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_59)
						case 59: { float r4=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w); if(r4>1e-21f){z/=r4;} float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_60)
						case 60: { float r2d=native_sqrt(z.x*z.x+z.y*z.y); float theta=atan2(z.y,z.x); z.x=r2d; z.y=theta*ta; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); z.x=z.x*native_cos(z.y/fmax(ta,0.01f))-z.z*native_sin(z.y/fmax(ta,0.01f)); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_61)
						case 61: { float R=fabs(ta)+0.5f; float r2d=native_sqrt(z.x*z.x+z.y*z.y); z.x=r2d-R; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_62)
						case 62: { float theta4=ta*M_PI_F/180.0f; float ca=native_cos(theta4),sa=native_sin(theta4); float nx=z.z*ca-z.w*sa; z.w=z.z*sa+z.w*ca; z.z=nx; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_63)
						case 63: { float golden=2.39996322972865332f; float theta=(float)i*golden*ta; z.x+=native_cos(theta)*tb*0.01f; z.y+=native_sin(theta)*tb*0.01f; z.z+=native_cos(theta*0.5f)*tc*0.01f; z.w=native_sin(theta*0.5f)*td*0.01f; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_64)
						case 64: { float D=2.7268f; float sc=native_pow(3.0f,D/3.0f); z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_65)
						case 65: { float h=native_sin(z.x*12.9898f+z.y*78.233f+z.z*45.164f+(float)i*ta)*43758.5453f; h=h-native_floor(h); float sc=3.0f; z=fabs(z); float vals[3]={z.x,z.y,z.z}; if(h>0.5f){if(vals[0]<vals[1]){float t=vals[0];vals[0]=vals[1];vals[1]=t;}} if(h>0.25f){if(vals[0]<vals[2]){float t=vals[0];vals[0]=vals[2];vals[2]=t;}} if(h>0.75f){if(vals[1]<vals[2]){float t=vals[1];vals[1]=vals[2];vals[2]=t;}} z=float4(vals[0],vals[1],vals[2],z.w)*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_66)
						case 66: { float sc=3.0f; float sq32=0.866025f; z=fabs(z); float d=z.x*sq32+z.y*0.5f; if(d<0.0f){z.x-=2.0f*d*sq32;z.y-=d;} z=z*sc-float4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_67)
						case 67: { float sc=3.0f; float a60=M_PI_F/3.0f; for(int k=0;k<6;k++){float a=k*a60; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0f){z.x-=2.0f*d*native_cos(a);z.y-=2.0f*d*native_sin(a);}} z=z*sc-float4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_68)
						case 68: { float sc=3.0f; float a45=M_PI_F/4.0f; for(int k=0;k<8;k++){float a=k*a45; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0f){z.x-=2.0f*d*native_cos(a);z.y-=2.0f*d*native_sin(a);}} z=z*sc-float4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_69)
						case 69: { float sc=3.0f; float a30=M_PI_F/6.0f; for(int k=0;k<12;k++){float a=k*a30; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0f){z.x-=2.0f*d*native_cos(a);z.y-=2.0f*d*native_sin(a);}} z=z*sc-float4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_70)
						case 70: { float sc=3.0f; float a72=M_PI_F*2.0f/5.0f; for(int k=0;k<5;k++){float a=k*a72; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0f){z.x-=2.0f*d*native_cos(a);z.y-=2.0f*d*native_sin(a);}} z=z*sc-float4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_71)
						case 71: { float sc=3.0f; float a60=M_PI_F/3.0f; for(int k=0;k<6;k++){float a=k*a60; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0f){z.x-=2.0f*d*native_cos(a);z.y-=2.0f*d*native_sin(a);}} z=z*sc-float4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_72)
						case 72: { float sc=3.0f; float a45=M_PI_F/4.0f; for(int k=0;k<8;k++){float a=k*a45; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0f){z.x-=2.0f*d*native_cos(a);z.y-=2.0f*d*native_sin(a);}} z=z*sc-float4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_73)
						case 73: { float sc=3.0f; float a36=M_PI_F/5.0f; for(int k=0;k<10;k++){float a=k*a36; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0f){z.x-=2.0f*d*native_cos(a);z.y-=2.0f*d*native_sin(a);}} z=z*sc-float4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_74)
						case 74: { int n=(int)fmax(ta,3.0f); float sc=3.0f; float aStep=M_PI_F*2.0f/n; for(int k=0;k<n&&k<16;k++){float a=k*aStep; float d=z.x*native_cos(a)+z.y*native_sin(a); if(d<0.0f){z.x-=2.0f*d*native_cos(a);z.y-=2.0f*d*native_sin(a);}} z=z*sc-float4(1,1,1,0)*(sc-1.0f)*tb; aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_75)
						case 75: { float sc=3.0f; int n=(int)fmax(ta,3.0f); float amp=fabs(tb); float theta=atan2(z.y,z.x); float r2d=native_sqrt(z.x*z.x+z.y*z.y); float star_r=r2d*(1.0f+amp*native_cos(n*theta)); z.x=star_r*native_cos(theta); z.y=star_r*native_sin(theta); z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_76)
						case 76: { float sc=3.0f; float theta=atan2(z.y,z.x); float r2d=native_sqrt(z.x*z.x+z.y*z.y); float heart_r=r2d*(1.0f-native_sin(theta)*fabs(ta)); z.x=heart_r*native_cos(theta); z.y=heart_r*native_sin(theta); z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_77)
						case 77: { float spiral_a=ta*0.01f*(float)i; float ca=native_cos(spiral_a),sa=native_sin(spiral_a); float nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_78)
						case 78: { float r2=z.x*z.x+z.y*z.y; z.z+=ta*0.001f*r2; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_79)
						case 79: { float r2d=native_sqrt(z.x*z.x+z.y*z.y); float taper_w=1.0f-ta*0.01f*fabs(r2d); z.x*=taper_w; z.y*=taper_w; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_80)
						case 80: { float twist_a=ta*0.01f*native_sqrt(z.x*z.x+z.y*z.y); float ca=native_cos(twist_a),sa=native_sin(twist_a); float nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_81)
						case 81: { float eps=fmax(fabs(ta),0.01f); float sc=3.0f; z=fabs(z); float t; if(z.x<z.y){float blend=0.5f+0.5f*tanh((z.y-z.x)/eps);t=z.x*(1.0f-blend)+z.y*blend;z.y=z.y*(1.0f-blend)+z.x*blend;z.x=t;} if(z.x<z.z){t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_82)
						case 82: { float h=native_sin(z.x*ta*127.1f+z.y*ta*311.7f+z.z*ta*74.7f)*43758.5453f; h=h-native_floor(h); z+=float4(h,1.0f-h,h*0.5f,0)*tb*0.01f; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_83)
						case 83: { float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f)+float4(ta,tb,tc,0); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_84)
						case 84: { float period=fmax(fabs(ta),0.1f); z=float4(fmod(fabs(z.x)+100.0f*period,period)-period*0.5f, fmod(fabs(z.y)+100.0f*period,period)-period*0.5f, fmod(fabs(z.z)+100.0f*period,period)-period*0.5f, z.w); float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_85)
						case 85: { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<1e-21f)r2=1e-21f; float inv=ta*ta/r2; z*=inv; aux.DE*=inv; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_86)
						case 86: { float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE*=(1.0f+sf*native_exp(-r*ta)*tb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_87)
						case 87: { float sc=3.0f; if(z.x+z.y<0.0f){float t=z.x;z.x=-z.y;z.y=-t;} if(z.x+z.z<0.0f){float t=z.x;z.x=-z.z;z.z=-t;} if(z.y+z.z<0.0f){float t=z.y;z.y=-z.z;z.z=-t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_88)
						case 88: { float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; float koch_scale=2.0f*ta; z.x=fabs(z.x)-koch_scale*0.5f; z.y=fabs(z.y)-koch_scale*0.5f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_89)
						case 89: { float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; if(z.x>0)z.x=-(z.x-1.0f); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_90)
						case 90: { float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; float fern_angle=ta*M_PI_F/180.0f; float ca=native_cos(fern_angle),sa=native_sin(fern_angle); float nx=z.x*ca-z.z*sa; z.z=z.x*sa+z.z*ca; z.x=nx; z*=0.85f*tb; aux.DE*=0.85f*fabs(tb); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_91)
						case 91: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; float shell=fabs(r-ta)-tb; aux.DE*=(1.0f+sf*native_exp(-shell*shell*tc)); break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_92)
						case 92: { float period=fmax(fabs(ta),0.1f); z=float4(fmod(z.x+100.0f*period,period)-period*0.5f, fmod(z.y+100.0f*period,period)-period*0.5f, fmod(z.z+100.0f*period,period)-period*0.5f, z.w); float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_93)
						case 93: { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<1e-21f)r2=1e-21f; float inv=ta*ta/r2; z*=inv; aux.DE*=inv; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_94)
						case 94: { float clip=fabs(ta); z.x=fmin(fmax(z.x,-clip),clip); z.y=fmin(fmax(z.y,-clip),clip); z.z=fmin(fmax(z.z,-clip),clip); float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_95)
						case 95: { float lim=fabs(ta)+0.5f; if(z.x>lim)z.x=2.0f*lim-z.x; if(z.x<-lim)z.x=-2.0f*lim-z.x; if(z.y>lim)z.y=2.0f*lim-z.y; if(z.y<-lim)z.y=-2.0f*lim-z.y; if(z.z>lim)z.z=2.0f*lim-z.z; if(z.z<-lim)z.z=-2.0f*lim-z.z; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_96)
						case 96: { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=fabs(ta)*fabs(ta); float fixedR2=1.0f; float m; if(r2<minR2)m=fixedR2/minR2; else if(r2<fixedR2)m=fixedR2/r2; else m=1.0f; z*=m; aux.DE*=m; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_97)
						case 97: { float angle=ta*M_PI_F/180.0f*(float)i; float ca=native_cos(angle),sa=native_sin(angle); float nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; float sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_98)
						case 98: { float sc=3.0f*(1.0f+sf*0.1f*native_sin((float)i*ta)); z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*fabs(sc)+1.0f; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_99)
						case 99: { float sc=3.0f; float offset=fabs(ta); z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+offset; break; }
#endif

#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_SMTYPE_100)
						case 100: { float h1=native_sin(ta*z.x+tb*z.y+tc*z.z); float h2=native_sin(td*h1+ta*(float)i*0.1f); float sc=3.0f+sf*h2*0.05f; z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-float4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*fabs(sc)+1.0f; break; }
#endif

					default: break;
#endif
					}
					float sm_blend = clamp(mut->smWeight * mut->masterWeight, 0.0f, 1.0f);
					z = z_orig_sm + (z - z_orig_sm) * sm_blend;
					aux.DE = de_orig_sm + (aux.DE - de_orig_sm) * sm_blend;
				}

			// v7.15 — Blockify system (per-section iteration range)
				if (mut->blockifyEnabled && i >= mut->blockifyIterStart && i < mut->blockifyIterStop && mut->blockifyType != 0)
				{
					float sf = mut->blockifyFactor * mut->blockifyWeight * mut->masterWeight;
					float ta = mut->blockifyParamA, tb = mut->blockifyParamB;
					float tc = mut->blockifyParamC, td = mut->blockifyParamD;
					float4 z_orig_bl = z; float de_orig_bl = aux.DE;
					switch(mut->blockifyType) {
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_BLOCKIFYTYPE_1)
						case 1: { float grid = fmax(fabs(ta), 0.01f); z.x = floor(z.x/grid)*grid; z.y = floor(z.y/grid)*grid; z.z = floor(z.z/grid)*grid; break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_BLOCKIFYTYPE_2)
						case 2: { float grid = fmax(fabs(ta), 0.01f); z.x = floor(z.x/grid+0.5f)*grid; z.y = floor(z.y/grid+0.5f)*grid; z.z = floor(z.z/grid+0.5f)*grid; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_BLOCKIFYTYPE_3)
						case 3: { float grid3b = fmax(fabs(ta), 0.01f), qx3=z.x-grid3b*floor(z.x/grid3b), qy3=z.y-grid3b*floor(z.y/grid3b), qz3=z.z-grid3b*floor(z.z/grid3b), d3b=fmin(fmin(fmin(qx3,grid3b-qx3),fmin(qy3,grid3b-qy3)),fmin(qz3,grid3b-qz3)); aux.DE = fmin(aux.DE, d3b*sf); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_BLOCKIFYTYPE_4)
						case 4: { float grid4b = fmax(fabs(ta), 0.01f), blend4b=fmin(fmax(tb,0.0f),1.0f), sx4=floor(z.x/grid4b+0.5f)*grid4b, sy4=floor(z.y/grid4b+0.5f)*grid4b, sz4=floor(z.z/grid4b+0.5f)*grid4b; z.x=z.x*(1.0f-blend4b)+sx4*blend4b; z.y=z.y*(1.0f-blend4b)+sy4*blend4b; z.z=z.z*(1.0f-blend4b)+sz4*blend4b; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_BLOCKIFYTYPE_5)
						case 5: { float grid5b = fmax(fabs(ta), 0.01f), r5b=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), cur5b=r5b; r5b=floor(r5b/grid5b+0.5f)*grid5b; if(cur5b>0.001f){z.x*=r5b/cur5b;z.y*=r5b/cur5b;z.z*=r5b/cur5b;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_BLOCKIFYTYPE_6)
						case 6: { float grid6b = fmax(fabs(ta), 0.01f), off6b=tb; z.x = floor((z.x+off6b)/grid6b)*grid6b-off6b; z.y = floor((z.y+off6b)/grid6b)*grid6b-off6b; z.z = floor((z.z+off6b)/grid6b)*grid6b-off6b; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_BLOCKIFYTYPE_7)
						case 7: { float gx7=fmax(fabs(ta),0.01f),gy7=fmax(fabs(tb),0.01f),gz7=fmax(fabs(tc),0.01f); z.x=floor(z.x/gx7+0.5f)*gx7; z.y=floor(z.y/gy7+0.5f)*gy7; z.z=floor(z.z/gz7+0.5f)*gz7; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_BLOCKIFYTYPE_8)
						case 8: { float grid8b=fmax(fabs(ta),0.01f), t8b=fmin(fmax(sf,0.0f),1.0f), progress8b=(float)i/fmax((float)(i+10),1.0f), blend8b=t8b*progress8b, sx8=floor(z.x/grid8b+0.5f)*grid8b, sy8=floor(z.y/grid8b+0.5f)*grid8b, sz8=floor(z.z/grid8b+0.5f)*grid8b; z.x=z.x*(1.0f-blend8b)+sx8*blend8b; z.y=z.y*(1.0f-blend8b)+sy8*blend8b; z.z=z.z*(1.0f-blend8b)+sz8*blend8b; break; }
#endif
						default: break;
#endif
					}
					float bl_blend = clamp(mut->blockifyWeight * mut->masterWeight, 0.0f, 1.0f);
					z = z_orig_bl + (z - z_orig_bl) * bl_blend;
					aux.DE = de_orig_bl + (aux.DE - de_orig_bl) * bl_blend;
				}

				// v7.15 — Tile system (per-section iteration range)
				if (mut->tileEnabled && i >= mut->tileIterStart && i < mut->tileIterStop && mut->tileType != 0)
				{
					float sf = mut->tileFactor * mut->tileWeight * mut->masterWeight;
					float ta = mut->tileParamA, tb = mut->tileParamB;
					float tc = mut->tileParamC, td = mut->tileParamD;
					float4 z_orig_ti = z; float de_orig_ti = aux.DE;
					switch(mut->tileType) {
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TILETYPE_1)
						case 1: { float period = fmax(fabs(ta), 0.01f); z.x = z.x - period*floor(z.x/period+0.5f); z.y = z.y - period*floor(z.y/period+0.5f); z.z = z.z - period*floor(z.z/period+0.5f); break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TILETYPE_2)
						case 2: { float px=fmax(fabs(ta),0.01f),py=fmax(fabs(tb),0.01f),pz=fmax(fabs(tc),0.01f); z.x=z.x-px*floor(z.x/px+0.5f); z.y=z.y-py*floor(z.y/py+0.5f); z.z=z.z-pz*floor(z.z/pz+0.5f); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TILETYPE_3)
						case 3: { float period=fmax(fabs(ta),0.01f); z.x=fabs(z.x)-period*floor(fabs(z.x)/period); z.y=fabs(z.y)-period*floor(fabs(z.y)/period); z.z=fabs(z.z)-period*floor(fabs(z.z)/period); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TILETYPE_4)
						case 4: { float period4=fmax(fabs(ta),0.01f), half4=period4*0.5f; z.x=fmod(z.x+half4,period4)-half4; z.y=fmod(z.y+half4,period4)-half4; z.z=fmod(z.z+half4,period4)-half4; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TILETYPE_5)
						case 5: { float period5=fmax(fabs(ta),0.01f), r5t=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), cur5=r5t; r5t=fmod(r5t,period5); if(cur5>0.001f){z.x*=r5t/cur5;z.y*=r5t/cur5;z.z*=r5t/cur5;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TILETYPE_6)
						case 6: { float angle6=atan2(z.y,z.x), period6=fmax(fabs(ta),0.01f)*M_PI_F/180.0f, rr6=native_sqrt(z.x*z.x+z.y*z.y); angle6=fmod(angle6+period6*0.5f,period6)-period6*0.5f; z.x=rr6*native_cos(angle6); z.y=rr6*native_sin(angle6); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TILETYPE_7)
						case 7: { float period7=fmax(fabs(ta),0.01f), blend7=fmin(fmax(tb,0.0f),1.0f), tx7=z.x-period7*floor(z.x/period7+0.5f), ty7=z.y-period7*floor(z.y/period7+0.5f), tz7=z.z-period7*floor(z.z/period7+0.5f); z.x=z.x*(1.0f-blend7)+tx7*blend7; z.y=z.y*(1.0f-blend7)+ty7*blend7; z.z=z.z*(1.0f-blend7)+tz7*blend7; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_TILETYPE_8)
						case 8: { float period8=fmax(fabs(ta),0.01f), fix8=(float)(int)floor(z.x/period8), fiy8=(float)(int)floor(z.y/period8); z.x=z.x-period8*floor(z.x/period8+0.5f); z.y=z.y-period8*floor(z.y/period8+0.5f); z.z=z.z-period8*floor(z.z/period8+0.5f); if(((int)fix8+(int)fiy8)%2!=0){z.x=-z.x;z.y=-z.y;} break; }
#endif
						default: break;
#endif
					}
					float ti_blend = clamp(mut->tileWeight * mut->masterWeight, 0.0f, 1.0f);
					z = z_orig_ti + (z - z_orig_ti) * ti_blend;
					aux.DE = de_orig_ti + (aux.DE - de_orig_ti) * ti_blend;
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


				// v7.14 — T Clamp system (per-section iteration range)
				if (mut->clampEnabled && i >= mut->clampIterStart && i < mut->clampIterStop && mut->clampType != 0)
				{
					float sf = mut->clampFactor * mut->clampWeight * mut->masterWeight;
					float ta = mut->clampParamA, tb = mut->clampParamB;
					float tc = mut->clampParamC, td = mut->clampParamD;
					float4 z_orig_cl = z; float de_orig_cl = aux.DE;
					switch(mut->clampType) {
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_1)
case 1: { z.x=fmax(fmin(z.x,ta),-ta); z.y=fmax(fmin(z.y,ta),-ta); z.z=fmax(fmin(z.z,ta),-ta); aux.DE*=sf; break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_2)
						case 2: { z.x=ta*tanh(z.x/fmax(ta,1e-10)); z.y=ta*tanh(z.y/fmax(ta,1e-10)); z.z=ta*tanh(z.z/fmax(ta,1e-10)); aux.DE*=sf; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_3)
						case 3: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(r>ta){float s=ta/r; z*=s; aux.DE*=s*sf;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_4)
						case 4: { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<ta*ta){float s=ta*ta/fmax(r2,1e-21); z*=s; aux.DE*=s;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_5)
						case 5: { if(z.x>ta)z.x=2.0f*ta-z.x; if(z.x<-ta)z.x=-2.0f*ta-z.x; if(z.y>ta)z.y=2.0f*ta-z.y; if(z.y<-ta)z.y=-2.0f*ta-z.y; if(z.z>ta)z.z=2.0f*ta-z.z; if(z.z<-ta)z.z=-2.0f*ta-z.z; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_6)
						case 6: { z.x=fmax(fmin(z.x,ta),-tb); z.y=fmax(fmin(z.y,ta),-tb); z.z=fmax(fmin(z.z,ta),-tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_7)
						case 7: { z.x=fmax(fmin(z.x,ta),-ta); z.y=fmax(fmin(z.y,tb),-tb); z.z=fmax(fmin(z.z,tc),-tc); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_8)
						case 8: { float lim=ta*(1.0f+tb*(float)i/250.0f); z.x=fmax(fmin(z.x,lim),-lim); z.y=fmax(fmin(z.y,lim),-lim); z.z=fmax(fmin(z.z,lim),-lim); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_9)
						case 9: { float lim=ta*fabs(native_sin(tb*(float)i)); z.x=fmax(fmin(z.x,fmax(lim,0.01f)),-fmax(lim,0.01f)); z.y=fmax(fmin(z.y,fmax(lim,0.01f)),-fmax(lim,0.01f)); z.z=fmax(fmin(z.z,fmax(lim,0.01f)),-fmax(lim,0.01f)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_10)
						case 10: { float lim=ta*native_exp(-tb*(float)i/100.0f); z.x=fmax(fmin(z.x,fmax(lim,0.01f)),-fmax(lim,0.01f)); z.y=fmax(fmin(z.y,fmax(lim,0.01f)),-fmax(lim,0.01f)); z.z=fmax(fmin(z.z,fmax(lim,0.01f)),-fmax(lim,0.01f)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_11)
						case 11: { float k=fmax(tb,0.01f); z.x=z.x-fmax(0.0f,fmin(1.0f,0.5f+(z.x-ta)/(2.0f*k)))*(z.x-ta); z.y=z.y-fmax(0.0f,fmin(1.0f,0.5f+(z.y-ta)/(2.0f*k)))*(z.y-ta); z.z=z.z-fmax(0.0f,fmin(1.0f,0.5f+(z.z-ta)/(2.0f*k)))*(z.z-ta); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_12)
						case 12: { if(fabs(z.x)>ta){float s=z.x>0?1:-1; z.x=s*(ta-(z.x-s*ta)*(z.x-s*ta)*tb);} if(fabs(z.y)>ta){float s=z.y>0?1:-1; z.y=s*(ta-(z.y-s*ta)*(z.y-s*ta)*tb);} if(fabs(z.z)>ta){float s=z.z>0?1:-1; z.z=s*(ta-(z.z-s*ta)*(z.z-s*ta)*tb);} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_13)
						case 13: { float rxy=native_sqrt(z.x*z.x+z.y*z.y); if(rxy>ta){float s=ta/rxy; z.x*=s; z.y*=s; aux.DE*=s;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_14)
						case 14: { float rxy=native_sqrt(z.x*z.x+z.y*z.y), lim=ta+tb*fabs(z.z); if(rxy>lim){float s=lim/rxy; z.x*=s; z.y*=s; aux.DE*=s;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_15)
						case 15: { float d=native_sqrt((z.x/fmax(ta,0.01f))*(z.x/fmax(ta,0.01f))+(z.y/fmax(tb,0.01f))*(z.y/fmax(tb,0.01f))+(z.z/fmax(tc,0.01f))*(z.z/fmax(tc,0.01f))); if(d>1.0f){z/=d; aux.DE/=d;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_16)
						case 16: { float rxy=native_sqrt(z.x*z.x+z.y*z.y)-ta, dt=native_sqrt(rxy*rxy+z.z*z.z); if(dt>tb){float s=tb/dt; rxy*=s; z.z*=s;float newR=rxy+ta; if(native_sqrt(z.x*z.x+z.y*z.y)>1e-10){float scale=newR/native_sqrt(z.x*z.x+z.y*z.y); z.x*=scale; z.y*=scale;} aux.DE*=s;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_17)
						case 17: { if(z.x>ta) z.x=ta; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_18)
						case 18: { if(z.x<-ta) z.x=-ta; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_19)
						case 19: { if(z.z>ta) z.z=ta; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_20)
						case 20: { float p=fmax(ta,0.1f); z.x=fmod(z.x+p,2.0f*p)-p; z.y=fmod(z.y+p,2.0f*p)-p; z.z=fmod(z.z+p,2.0f*p)-p; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_21)
						case 21: { float p=fmax(ta,0.1f); z.x=2.0f*fabs(z.x/(2.0f*p)-floor(z.x/(2.0f*p)+0.5f))*p; z.y=2.0f*fabs(z.y/(2.0f*p)-floor(z.y/(2.0f*p)+0.5f))*p; z.z=2.0f*fabs(z.z/(2.0f*p)-floor(z.z/(2.0f*p)+0.5f))*p; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_22)
						case 22: { z.x=ta*(2.0f/(1.0f+native_exp(-2.0f*z.x/fmax(ta,0.01f)))-1.0f); z.y=ta*(2.0f/(1.0f+native_exp(-2.0f*z.y/fmax(ta,0.01f)))-1.0f); z.z=ta*(2.0f/(1.0f+native_exp(-2.0f*z.z/fmax(ta,0.01f)))-1.0f); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_23)
						case 23: { z.x=ta*atan(z.x/fmax(ta,0.01f))*(2.0f/M_PI_F); z.y=ta*atan(z.y/fmax(ta,0.01f))*(2.0f/M_PI_F); z.z=ta*atan(z.z/fmax(ta,0.01f))*(2.0f/M_PI_F); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_24)
						case 24: { float k24=1.0f/fmax(ta,0.01f); z.x=ta*tanh(k24*z.x*1.128f); z.y=ta*tanh(k24*z.y*1.128f); z.z=ta*tanh(k24*z.z*1.128f); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_25)
						case 25: { float p25=fmax(tb,0.1f); if(fabs(z.x)>ta)z.x=z.x>0?ta*pow(ta/z.x,p25):-ta*pow(ta/fabs(z.x),p25); if(fabs(z.y)>ta)z.y=z.y>0?ta*pow(ta/z.y,p25):-ta*pow(ta/fabs(z.y),p25); if(fabs(z.z)>ta)z.z=z.z>0?ta*pow(ta/z.z,p25):-ta*pow(ta/fabs(z.z),p25); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_26)
						case 26: { float lim26=ta*(1.0f+tb*native_sin(aux.color*tc)); z.x=fmax(fmin(z.x,lim26),-lim26); z.y=fmax(fmin(z.y,lim26),-lim26); z.z=fmax(fmin(z.z,lim26),-lim26); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_27)
						case 27: { float lim27=ta*(1.0f+tb*native_log(1.0f+fabs(aux.DE))); z.x=fmax(fmin(z.x,lim27),-lim27); z.y=fmax(fmin(z.y,lim27),-lim27); z.z=fmax(fmin(z.z,lim27),-lim27); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_28)
						case 28: { float lim28=ta+tb*z.x; z.y=fmax(fmin(z.y,fabs(lim28)),-fabs(lim28)); z.z=fmax(fmin(z.z,fabs(lim28)),-fabs(lim28)); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_29)
						case 29: { float theta29=atan2(z.y,z.x), r29=native_sqrt(z.x*z.x+z.y*z.y); if(r29>ta){r29=ta; z.x=r29*native_cos(theta29); z.y=r29*native_sin(theta29); aux.DE*=ta/fmax(native_sqrt(z.x*z.x+z.y*z.y),1e-10);} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_30)
						case 30: { float p30=fmax(ta,0.1f); z.x=floor(z.x/p30+0.5f)*p30; z.y=floor(z.y/p30+0.5f)*p30; z.z=floor(z.z/p30+0.5f)*p30; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_31)
						case 31: { float r31=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(r31<ta&&r31>1e-15){float s=ta/r31; z*=s; aux.DE*=s;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_32)
						case 32: { float r32=native_sqrt(z.x*z.x+z.y*z.y); if(r32>ta&&r32<tb){}else if(r32<=ta){float s=ta/fmax(r32,1e-10); z.x*=s; z.y*=s;} else{float s=tb/r32; z.x*=s; z.y*=s;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_33)
						case 33: { float n33=native_sin(z.x*12.9898f+z.y*78.233f+z.z*45.164f)*43758.5453f; n33=n33-floor(n33); { float lim33=ta*(1.0f+tb*(n33-0.5f)); z.x=fmax(fmin(z.x,lim33),-lim33); z.y=fmax(fmin(z.y,lim33),-lim33); z.z=fmax(fmin(z.z,lim33),-lim33); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_34)
						case 34: { float theta34=atan2(z.y,z.x), r34=native_sqrt(z.x*z.x+z.y*z.y), spiralLim=ta+tb*theta34/(2.0f*M_PI_F); if(r34>spiralLim){z.x*=spiralLim/r34; z.y*=spiralLim/r34;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_35)
						case 35: { float waveLim=ta+tb*native_sin(tc*z.x)*native_sin(tc*z.y); z.z=fmax(fmin(z.z,waveLim),-waveLim); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_36)
						case 36: { if(fabs(z.x)>ta){float t=z.x; z.x=z.y; z.y=t;} if(fabs(z.y)>ta){float t=z.y; z.y=z.z; z.z=t;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_37)
						case 37: { if(z.x>ta)z.x=2.0f*ta-z.x; if(z.y>ta)z.y=2.0f*ta-z.y; if(z.z>ta)z.z=2.0f*ta-z.z; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_38)
						case 38: { float p38=fmax(2.0f*ta,0.01f); z.x=fabs(fmod(z.x+ta,p38)-ta); z.y=fabs(fmod(z.y+ta,p38)-ta); z.z=fabs(fmod(z.z+ta,p38)-ta); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_39)
						case 39: { float s39=z.x>0?1:-1; z.x=s39*fmin(fabs(z.x),ta*native_log(1.0f+fabs(z.x)/fmax(ta,0.01f))); s39=z.y>0?1:-1; z.y=s39*fmin(fabs(z.y),ta*native_log(1.0f+fabs(z.y)/fmax(ta,0.01f))); s39=z.z>0?1:-1; z.z=s39*fmin(fabs(z.z),ta*native_log(1.0f+fabs(z.z)/fmax(ta,0.01f))); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_40)
						case 40: { float step40=fmax(tb,0.01f); z.x=floor(z.x/step40+0.5f)*step40; z.x=fmax(fmin(z.x,ta),-ta); z.y=floor(z.y/step40+0.5f)*step40; z.y=fmax(fmin(z.y,ta),-ta); z.z=floor(z.z/step40+0.5f)*step40; z.z=fmax(fmin(z.z,ta),-ta); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_41)
						case 41: { for(int k=0;k<3;k++){if(z.x>ta)z.x=2.0f*ta-z.x; if(z.x<-ta)z.x=-2.0f*ta-z.x; if(z.y>ta)z.y=2.0f*ta-z.y; if(z.y<-ta)z.y=-2.0f*ta-z.y; if(z.z>ta)z.z=2.0f*ta-z.z; if(z.z<-ta)z.z=-2.0f*ta-z.z; ta*=tb;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_42)
						case 42: { float r42=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(r42>ta){z*=ta/r42; aux.DE*=ta/r42;} if(r42<tb&&r42>1e-15){z*=tb/r42; aux.DE*=tb/r42;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_43)
						case 43: { z.x=ta*z.x/native_sqrt(z.x*z.x+tb*tb); z.y=ta*z.y/native_sqrt(z.y*z.y+tb*tb); z.z=ta*z.z/native_sqrt(z.z*z.z+tb*tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_44)
						case 44: { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); z.x=fmin(z.x,ta); z.y=fmin(z.y,ta); z.z=fmin(z.z,ta); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_45)
						case 45: { float k45=fmax(tb,0.01f); if(fabs(z.x)>ta){float d=(fabs(z.x)-ta)/k45;float s=z.x>0?1:-1; z.x=s*(ta+k45*d/(1.0f+d*d));} if(fabs(z.y)>ta){float d=(fabs(z.y)-ta)/k45; float s=z.y>0?1:-1; z.y=s*(ta+k45*d/(1.0f+d*d));} if(fabs(z.z)>ta){float d=(fabs(z.z)-ta)/k45; float s=z.z>0?1:-1; z.z=s*(ta+k45*d/(1.0f+d*d));} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_46)
						case 46: { float sum46=fabs(z.x)+fabs(z.y)+fabs(z.z); if(sum46>ta){float s=ta/sum46; z*=s; aux.DE*=s;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_47)
						case 47: { if(fabs(z.x)+fabs(z.y)>ta){float s=ta/(fabs(z.x)+fabs(z.y)); z.x*=s; z.y*=s;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_48)
						case 48: { float rxy48=native_sqrt(z.x*z.x+z.y*z.y); if(rxy48>ta){z.x*=ta/rxy48; z.y*=ta/rxy48;} z.z=fmax(fmin(z.z,tb),-tb); break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_49)
						case 49: { float capH49=fmax(0.0f,fmin(ta,z.z)), rd49=native_sqrt(z.x*z.x+z.y*z.y+(z.z-capH49)*(z.z-capH49)); if(rd49>tb){float s=tb/rd49; z.x*=s; z.y*=s; z.z=capH49+(z.z-capH49)*s; aux.DE*=s;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_CLAMPTYPE_50)
						case 50: { float p50=fmax(tc,0.5f), d50=pow(pow(fabs(z.x/fmax(ta,0.01f)),p50)+pow(fabs(z.y/fmax(ta,0.01f)),p50)+pow(fabs(z.z/fmax(tb,0.01f)),p50),1.0f/p50); if(d50>1.0f){z/=d50; aux.DE/=d50;} break; }
#endif
						default: break;
#endif
					}
					float cl_blend = clamp(mut->clampWeight * mut->masterWeight, 0.0f, 1.0f);
					z = z_orig_cl + (z - z_orig_cl) * cl_blend;
					aux.DE = de_orig_cl + (aux.DE - de_orig_cl) * cl_blend;
				}

				// v7.14 — T Julia Box system (per-section iteration range)
				if (mut->jbEnabled && i >= mut->jbIterStart && i < mut->jbIterStop && mut->jbType != 0)
				{
					float sf = mut->jbFactor * mut->jbWeight * mut->masterWeight;
					float ta = mut->jbParamA, tb = mut->jbParamB;
					float tc = mut->jbParamC, td = mut->jbParamD;
					float4 z_orig_jb = z; float de_orig_jb = aux.DE;
					switch(mut->jbType) {
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_1)
case 1: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2jb=z.x*z.x+z.y*z.y+z.z*z.z; float minR2jb=tb*tb; float fixedR2jb=1.0f; if(r2jb<minR2jb){z*=fixedR2jb/minR2jb; aux.DE*=fixedR2jb/minR2jb;} else if(r2jb<fixedR2jb){z*=fixedR2jb/r2jb; aux.DE*=fixedR2jb/r2jb;} z=z*tc+(float4)(td,td,td,0.0f); aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_2)
						case 2: { float a2=ta*M_PI_F/180.0f, c2=native_cos(a2),s2=native_sin(a2), nx2=z.x*c2-z.y*s2; z.y=z.x*s2+z.y*c2; z.x=nx2; z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z;{ float r2jb2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2jb2<0.25f){z*=4.0f; aux.DE*=4.0f;} else if(r2jb2<1.0f){z*=1.0f/r2jb2; aux.DE*=1.0f/r2jb2;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_3)
						case 3: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2mb=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tb*tb; if(r2mb<minR2){z*=1.0f/minR2; aux.DE*=1.0f/minR2;} else if(r2mb<1.0f){z*=1.0f/r2mb; aux.DE*=1.0f/r2mb;} z=z*tc+aux.const_c; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_4)
						case 4: { z=fabs(z+(float4)(ta,ta,ta,0.0f))-(float4)(ta,ta,ta,0.0f); { float r2ab=z.x*z.x+z.y*z.y+z.z*z.z; float minR2ab=tb*tb; if(r2ab<minR2ab){z*=1.0f/minR2ab; aux.DE*=1.0f/minR2ab;} else if(r2ab<1.0f){z*=1.0f/r2ab; aux.DE*=1.0f/r2ab;} z=z*tc+aux.const_c; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_5)
						case 5: { float k5=fmax(td,0.01f); z.x=z.x-k5*tanh((z.x-ta)/k5)+k5*tanh((z.x+ta)/k5)-z.x; z.y=z.y-k5*tanh((z.y-ta)/k5)+k5*tanh((z.y+ta)/k5)-z.y; z.z=z.z-k5*tanh((z.z-ta)/k5)+k5*tanh((z.z+ta)/k5)-z.z;{ float r2sb=z.x*z.x+z.y*z.y+z.z*z.z; if(r2sb<tb*tb){z*=1.0f/(tb*tb); aux.DE*=1.0f/(tb*tb);} else if(r2sb<1.0f){z*=1.0f/r2sb; aux.DE*=1.0f/r2sb;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_6)
						case 6: { z.x=fabs(z.x)-ta; z.y=fabs(z.y)-ta; z.z=fabs(z.z)-ta; { float r2af=z.x*z.x+z.y*z.y+z.z*z.z; if(r2af<tb*tb&&r2af>1e-21){z*=1.0f/(r2af); aux.DE*=1.0f/(r2af);} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_7)
						case 7: { if(z.x>ta)z.x=ta-z.x; if(z.x<-ta)z.x=-ta-z.x; if(z.y>ta)z.y=ta-z.y; if(z.y<-ta)z.y=-ta-z.y; if(z.z>ta)z.z=ta-z.z; if(z.z<-ta)z.z=-ta-z.z; { float r2cf=z.x*z.x+z.y*z.y+z.z*z.z; float minR=tb*tb; if(r2cf<minR){z*=1.0f/minR; aux.DE*=1.0f/minR;} else if(r2cf<1.0f){z*=1.0f/r2cf; aux.DE*=1.0f/r2cf;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_8)
						case 8: { for(int k=0;k<3;k++){z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z;} float r2mf=z.x*z.x+z.y*z.y+z.z*z.z; if(r2mf<tb*tb){z*=1.0f/(tb*tb); aux.DE*=1.0f/(tb*tb);} else if(r2mf<1.0f){z*=1.0f/r2mf; aux.DE*=1.0f/r2mf;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_9)
						case 9: { if(z.x+z.y<0.0f){float t=z.x;z.x=-z.y;z.y=-t;} if(z.x+z.z<0.0f){float t=z.x;z.x=-z.z;z.z=-t;} if(z.y+z.z<0.0f){float t=z.y;z.y=-z.z;z.z=-t;} z=z*ta-(float4)(tb,tb,tb,0.0f)*(ta-1.0f); aux.DE=aux.DE*fabs(ta)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_10)
						case 10: { z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*ta-(float4)(1,1,1,0.0f)*(ta-1.0f)*tb; aux.DE=aux.DE*fabs(ta)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_11)
						case 11: { z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z=z*tc+(float4)(td,td,td,0.0f); aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_12)
						case 12: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_13)
						case 13: { z=z*ta+(float4)(tb,tc,td,0.0f); z.x=fabs(z.x+1.0f)-fabs(z.x-1.0f)-z.x; z.y=fabs(z.y+1.0f)-fabs(z.y-1.0f)-z.y; z.z=fabs(z.z+1.0f)-fabs(z.z-1.0f)-z.z; aux.DE=aux.DE*fabs(ta)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_14)
						case 14: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tc)-fabs(z.z-tc)-z.z; { float r2df=z.x*z.x+z.y*z.y+z.z*z.z; if(r2df<0.25f){z*=4.0f;aux.DE*=4.0f;} else if(r2df<1.0f){z*=1.0f/r2df;aux.DE*=1.0f/r2df;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_15)
						case 15: { z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; { float r2mh=z.x*z.x+z.y*z.y+z.z*z.z; if(r2mh<tb*tb){z*=1.0f/(tb*tb);aux.DE*=1.0f/(tb*tb);} else if(r2mh<1.0f){z*=1.0f/r2mh;aux.DE*=1.0f/r2mh;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_16)
						case 16: { float tw16=ta*M_PI_F/180.0f*z.z, c16=native_cos(tw16),s16=native_sin(tw16), nx16=z.x*c16-z.y*s16; z.y=z.x*s16+z.y*c16; z.x=nx16; z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_17)
						case 17: { float sc17=ta+tb*native_sin((float)i*tc); z.x=fabs(z.x+1.0f)-fabs(z.x-1.0f)-z.x; z.y=fabs(z.y+1.0f)-fabs(z.y-1.0f)-z.y; z.z=fabs(z.z+1.0f)-fabs(z.z-1.0f)-z.z; z*=sc17; aux.DE=aux.DE*fabs(sc17)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_18)
						case 18: { float r218=z.x*z.x+z.y*z.y+z.z*z.z, minR218=ta*ta, fixR218=tb*tb; if(r218<minR218){z*=fixR218/minR218;aux.DE*=fixR218/minR218;} else if(r218<fixR218){z*=fixR218/r218;aux.DE*=fixR218/r218;} float r218b=z.x*z.x+z.y*z.y+z.z*z.z;{ float minR218b=tc*tc; if(r218b<minR218b){z*=1.0f/minR218b;aux.DE*=1.0f/minR218b;} else if(r218b<1.0f){z*=1.0f/r218b;aux.DE*=1.0f/r218b;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_19)
						case 19: { float rxy19=native_sqrt(z.x*z.x+z.y*z.y); if(rxy19<ta&&rxy19>1e-15){z.x*=ta/rxy19; z.y*=ta/rxy19; aux.DE*=ta/rxy19;} z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_20)
						case 20: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; { float r2xz=z.x*z.x+z.z*z.z; if(r2xz<tb*tb){z*=1.0f/(tb*tb);aux.DE*=1.0f/(tb*tb);} else if(r2xz<1.0f){z*=1.0f/r2xz;aux.DE*=1.0f/r2xz;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_21)
						case 21: { z=fabs(z)-(float4)(ta,ta,ta,0.0f); z+=aux.const_c*tb; { float r2ao=z.x*z.x+z.y*z.y+z.z*z.z; if(r2ao<tc*tc){z*=1.0f/(tc*tc);aux.DE*=1.0f/(tc*tc);} else if(r2ao<1.0f){z*=1.0f/r2ao;aux.DE*=1.0f/r2ao;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_22)
						case 22: { if(i%2==0){z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z;} else{z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;}} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_23)
						case 23: { float r2so=z.x*z.x+z.y*z.y+z.z*z.z, minR2so=ta*ta, fixedR2so=tb*tb; if(r2so<minR2so){float m=fixedR2so/minR2so; z*=m; aux.DE*=m;} else if(r2so<fixedR2so){float m=fixedR2so/r2so; z*=m; aux.DE*=m;} break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_24)
						case 24: { if(z.x+z.y<0.0f){float t=-z.y;z.y=-z.x;z.x=t;} if(z.x+z.z<0.0f){float t=-z.z;z.z=-z.x;z.x=t;} if(z.y+z.z<0.0f){float t=-z.z;z.z=-z.y;z.y=t;} z*=ta; z-=(float4)(tb,tb,tb,0.0f)*(ta-1.0f); aux.DE=aux.DE*fabs(ta)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_25)
						case 25: { z.x=fabs(fabs(z.x+ta)-tb)-ta; z.y=fabs(fabs(z.y+ta)-tb)-ta; z.z=fabs(fabs(z.z+ta)-tb)-ta; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_26)
						case 26: { float r2rb=z.x*z.x+z.y*z.y+z.z*z.z, theta26=atan2(z.y,z.x), phi26=atan2(native_sqrt(z.x*z.x+z.y*z.y),z.z), rr26=native_sqrt(r2rb); rr26=fabs(rr26+ta)-fabs(rr26-ta)-rr26; z.x=rr26*native_sin(phi26)*native_cos(theta26); z.y=rr26*native_sin(phi26)*native_sin(theta26); z.z=rr26*native_cos(phi26); z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_27)
						case 27: { float p27=fmax(tb,0.5f); z.x=z.x>0?pow(fabs(z.x),p27):-pow(fabs(z.x),p27); z.y=z.y>0?pow(fabs(z.y),p27):-pow(fabs(z.y),p27); z.z=z.z>0?pow(fabs(z.z),p27):-pow(fabs(z.z),p27); z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_28)
						case 28: { if(i%3==0){z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x;} else if(i%3==1){z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y;} else{z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z;} float r2il=z.x*z.x+z.y*z.y+z.z*z.z; if(r2il<tb*tb){z*=1.0f/(tb*tb);aux.DE*=1.0f/(tb*tb);} else if(r2il<1.0f){z*=1.0f/r2il;aux.DE*=1.0f/r2il;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_29)
						case 29: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2mj=z.x*z.x+z.y*z.y+z.z*z.z; if(r2mj<0.25f){z*=4.0f;aux.DE*=4.0f;} else if(r2mj<1.0f){z*=1.0f/r2mj;aux.DE*=1.0f/r2mj;} z=z*tc+(float4)(td,td,td,0.0f); aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_30)
						case 30: { z*=ta; aux.DE=aux.DE*fabs(ta)+1.0f; { float a30=tb*M_PI_F/180.0f; float c30=native_cos(a30),s30=native_sin(a30); float nx30=z.x*c30-z.y*s30; z.y=z.x*s30+z.y*c30; z.x=nx30; z.x=fabs(z.x+tc)-fabs(z.x-tc)-z.x; z.y=fabs(z.y+tc)-fabs(z.y-tc)-z.y; z.z=fabs(z.z+tc)-fabs(z.z-tc)-z.z; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_31)
						case 31: { float bp31=z.x*z.x+z.y*z.y; if(bp31>1e-21){float inv=ta*ta/bp31; z.x*=inv; z.y*=inv; aux.DE*=inv;} z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_32)
						case 32: { float r2cb=z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w; if(r2cb>1e-21){z*=ta/r2cb; aux.DE*=ta/r2cb;} z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_33)
						case 33: { float lim33=ta*(1.0f+tb*(float)i/250.0f); z.x=fabs(z.x+lim33)-fabs(z.x-lim33)-z.x; z.y=fabs(z.y+lim33)-fabs(z.y-lim33)-z.y; z.z=fabs(z.z+lim33)-fabs(z.z-lim33)-z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_34)
						case 34: { float n34=native_sin(z.x*12.9898f+z.y*78.233f)*43758.5453f; n34=n34-floor(n34); { float lim34=ta+tb*(n34-0.5f); z.x=fabs(z.x+lim34)-fabs(z.x-lim34)-z.x; z.y=fabs(z.y+lim34)-fabs(z.y-lim34)-z.y; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_35)
						case 35: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; z.w=fabs(z.w+ta)-fabs(z.w-ta)-z.w; { float r24d=z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w; if(r24d<tb*tb){z*=1.0f/(tb*tb);aux.DE*=1.0f/(tb*tb);} else if(r24d<1.0f){z*=1.0f/r24d;aux.DE*=1.0f/r24d;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_36)
						case 36: { float q36x=z.x, q36y=z.y*0.866f+z.x*0.5f; if(q36y>ta){q36y=2.0f*ta-q36y;} if(q36x>ta){q36x=2.0f*ta-q36x;} z.x=q36x; z.y=(q36y-z.x*0.5f)/0.866f; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_37)
						case 37: { float d37x=fabs(z.x)-ta, d37y=fabs(z.y)-ta, d37z=fabs(z.z)-ta; if(d37x>0&&d37y>0){z.x*=ta/(ta+d37x); z.y*=ta/(ta+d37y);} if(d37y>0&&d37z>0){z.y*=ta/(ta+d37y); z.z*=ta/(ta+d37z);} if(d37x>0&&d37z>0){z.x*=ta/(ta+d37x); z.z*=ta/(ta+d37z);} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_38)
						case 38: { z.x+=tb*native_sin(ta*z.y)*native_cos(ta*z.z); z.y+=tb*native_sin(ta*z.z)*native_cos(ta*z.x); z.z+=tb*native_cos(ta*z.y)*native_sin(ta*z.x); z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_39)
						case 39: { z.x=fabs(native_cos(z.x*ta))*tb; z.y=fabs(native_cos(z.y*ta))*tb; z.z=fabs(native_cos(z.z*ta))*tb; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_40)
						case 40: { z.x=z.x>0?native_log(1.0f+z.x*ta):-native_log(1.0f-z.x*ta); z.y=z.y>0?native_log(1.0f+z.y*ta):-native_log(1.0f-z.y*ta); z.z=z.z>0?native_log(1.0f+z.z*ta):-native_log(1.0f-z.z*ta); z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_41)
						case 41: { float lim41=ta; z.x=z.x>lim41?lim41-(z.x-lim41)*(z.x-lim41)*tb:z.x<-lim41?-lim41+(z.x+lim41)*(z.x+lim41)*tb:z.x; z.y=z.y>lim41?lim41-(z.y-lim41)*(z.y-lim41)*tb:z.y<-lim41?-lim41+(z.y+lim41)*(z.y+lim41)*tb:z.y; z.z=z.z>lim41?lim41-(z.z-lim41)*(z.z-lim41)*tb:z.z<-lim41?-lim41+(z.z+lim41)*(z.z+lim41)*tb:z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_42)
						case 42: { z.x=fmin(fmax(z.x,-ta),ta); z.y=fmin(fmax(z.y,-ta),ta); z.z=fmin(fmax(z.z,-ta),ta); z.x=fmax(fmin(z.x,tb),-tb); z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_43)
						case 43: { if(fabs(z.x)>ta)z.x=z.x>0?ta:-ta; if(fabs(z.y)>ta)z.y=z.y>0?ta:-ta; if(fabs(z.z)>ta)z.z=z.z>0?ta:-ta; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_44)
						case 44: { float p44=2.0f*ta; z.x=z.x-p44*floor((z.x+ta)/p44); z.y=z.y-p44*floor((z.y+ta)/p44); z.z=z.z-p44*floor((z.z+ta)/p44); z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_45)
						case 45: { float r45=native_sqrt(z.x*z.x+z.y*z.y), th45=atan2(z.y,z.x); th45=fabs(th45+ta)-fabs(th45-ta)-th45; z.x=r45*native_cos(th45); z.y=r45*native_sin(th45); z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_46)
						case 46: { float lim46=ta*(1.0f+tb*native_log(1.0f+fabs(aux.DE))); z.x=fabs(z.x+lim46)-fabs(z.x-lim46)-z.x; z.y=fabs(z.y+lim46)-fabs(z.y-lim46)-z.y; z.z=fabs(z.z+lim46)-fabs(z.z-lim46)-z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_47)
						case 47: { float lim47=ta*(1.0f+tb*native_sin(aux.color*tc)); z.x=fabs(z.x+lim47)-fabs(z.x-lim47)-z.x; z.y=fabs(z.y+lim47)-fabs(z.y-lim47)-z.y; z.z=fabs(z.z+lim47)-fabs(z.z-lim47)-z.z; z*=td; aux.DE=aux.DE*fabs(td)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_48)
						case 48: { float la=ta,lb=tb; for(int k=0;k<3;k++){z.x=fabs(z.x+la)-fabs(z.x-la)-z.x; z.y=fabs(z.y+la)-fabs(z.y-la)-z.y; z.z=fabs(z.z+la)-fabs(z.z-la)-z.z; la*=lb;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_49)
						case 49: { z.x=z.x>ta?z.x-2.0f*ta:z.x<-ta?z.x+2.0f*ta:z.x; z.y=z.y>ta?z.y-2.0f*ta:z.y<-ta?z.y+2.0f*ta:z.y; z.z=z.z>ta?z.z-2.0f*ta:z.z<-ta?z.z+2.0f*ta:z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_JBTYPE_50)
						case 50: { z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2ifs=z.x*z.x+z.y*z.y+z.z*z.z; if(r2ifs<tb*tb){z*=1.0f/(tb*tb);aux.DE*=1.0f/(tb*tb);} else if(r2ifs<1.0f){z*=1.0f/r2ifs;aux.DE*=1.0f/r2ifs;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
#endif
						default: break;
#endif
					}
					float jb_blend = clamp(mut->jbWeight * mut->masterWeight, 0.0f, 1.0f);
					z = z_orig_jb + (z - z_orig_jb) * jb_blend;
					aux.DE = de_orig_jb + (aux.DE - de_orig_jb) * jb_blend;
				}

				// v7.14f — T Mandalay system (per-section iteration range)
				if (mut->mdEnabled && i >= mut->mdIterStart && i < mut->mdIterStop && mut->mdType != 0)
				{
					float sf = mut->mdFactor * mut->mdWeight * mut->masterWeight;
					float ta = mut->mdParamA, tb = mut->mdParamB;
					float tc = mut->mdParamC, td = mut->mdParamD;
					float4 z_orig_md = z; float de_orig_md = aux.DE;
					switch (mut->mdType)
					{
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_1)
						case 1: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tb*tb; if(r2<minR2){z*=1.0f/minR2;aux.DE*=1.0f/minR2;} else if(r2<1.0f){z*=1.0f/r2;aux.DE*=1.0f/r2;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; z+=(float4)(td,td,td,0.0f); } break; }
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_2)
						case 2: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tc)-fabs(z.z-tc)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<0.25f){z*=4.0f;aux.DE*=4.0f;} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_3)
						case 3: { float rxy=native_sqrt(z.x*z.x+z.y*z.y); if(rxy>ta){float s=ta/rxy; z.x*=s; z.y*=s; aux.DE*=s;} float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){z*=1.0f/(tb*tb);aux.DE*=1.0f/(tb*tb);} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_4)
						case 4: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float fixR=tb*tb; float minR=tc*tc; if(r2<minR){z*=fixR/minR;aux.DE*=fixR/minR;} else if(r2<fixR){z*=fixR/r2;aux.DE*=fixR/r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_5)
						case 5: { z=fabs(z+(float4)(ta,ta,ta,0.0f))-(float4)(ta,ta,ta,0.0f); { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb){z*=tc/tb;aux.DE*=tc/tb;} else if(r2<tc){z*=tc/r2;aux.DE*=tc/r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_6)
						case 6: { if(z.x+z.y<0){float t=z.x;z.x=-z.y;z.y=-t;} if(z.x+z.z<0){float t=z.x;z.x=-z.z;z.z=-t;} if(z.y+z.z<0){float t=z.y;z.y=-z.z;z.z=-t;} z=z*ta-(float4)(tb,tb,tb,0.0f)*(ta-1.0f); aux.DE=aux.DE*fabs(ta)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_7)
						case 7: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){float s=tc/(tb*tb); z*=s;aux.DE*=s;} else if(r2<tc){float s=tc/r2; z*=s;aux.DE*=s;} z.z=td*z.z; aux.DE*=fabs(td); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_8)
						case 8: { float a8=ta*M_PI_F/180.0f, c8=native_cos(a8),s8=native_sin(a8), nx=z.x*c8-z.y*s8; z.y=z.x*s8+z.y*c8; z.x=nx; z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z;{ float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<0.25f){z*=4.0f;aux.DE*=4.0f;} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_9)
						case 9: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(r<tb){z*=tc/(tb*tb);aux.DE*=tc/(tb*tb);} else if(r<native_sqrt(tc)){z*=tc/(r*r);aux.DE*=tc/(r*r);} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_10)
						case 10: { z=fabs(z)-(float4)(ta,ta,ta,0.0f); if(z.x<0)z.x=0; if(z.y<0)z.y=0; if(z.z<0)z.z=0; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){z*=1.0f/(tb*tb);aux.DE*=1.0f/(tb*tb);} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; z+=(float4)(td,td,td,0.0f); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_11)
						case 11: { float rxy=native_sqrt(z.x*z.x+z.y*z.y), minR=ta; if(rxy<minR&&rxy>1e-21f){float s=minR/rxy; z.x*=s;z.y*=s;aux.DE*=s;} z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_12)
						case 12: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float sph=fmax(tb*tb/fmax(r2,1e-21f),1.0f); z*=sph*tc; aux.DE=aux.DE*sph*fabs(tc)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_13)
						case 13: { if(z.x-z.y<0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){float t=z.y;z.y=z.z;z.z=t;} z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tc*tc){z*=1.0f/(tc*tc);aux.DE*=1.0f/(tc*tc);} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_14)
						case 14: { z.x=ta*tanh(z.x/fmax(ta,1e-10f)); z.y=ta*tanh(z.y/fmax(ta,1e-10f)); z.z=ta*tanh(z.z/fmax(ta,1e-10f)); { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){z*=tc/(tb*tb);aux.DE*=tc/(tb*tb);} else if(r2<tc){z*=tc/r2;aux.DE*=tc/r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_15)
						case 15: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tb*tb; float fixR2=tc*tc; if(r2<minR2){z*=fixR2/minR2;aux.DE*=fixR2/minR2;} else if(r2<fixR2){z*=fixR2/r2;aux.DE*=fixR2/r2;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; z+=(float4)(td,td,td,0.0f); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_16)
						case 16: { float fold=ta; z.x=fabs(z.x+fold)-fabs(z.x-fold)-z.x; z.y=fabs(z.y+fold)-fabs(z.y-fold)-z.y; z.z=fabs(z.z+fold)-fabs(z.z-fold)-z.z;{ float r2=z.x*z.x+z.y*z.y+z.z*z.z, k=fmax(tb/fmax(r2,1e-21f),1.0f); z*=k; aux.DE*=k; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; z.x+=td; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_17)
						case 17: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb){z*=tc/tb;aux.DE*=tc/tb;} else if(r2<tc){z*=tc/r2;aux.DE*=tc/r2;} float sc=td+sf*native_sin((float)i*0.5f); z*=sc; aux.DE=aux.DE*fabs(sc)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_18)
						case 18: { z.x=clamp(z.x,-ta,ta)*2.0f-z.x; z.y=clamp(z.y,-ta,ta)*2.0f-z.y; z.z=clamp(z.z,-ta,ta)*2.0f-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float k=fmax(tb/fmax(r2,1e-21f),1.0f); z*=k*tc; aux.DE=aux.DE*k*fabs(tc)+1.0f; z+=(float4)(td,0.0f,0.0f,0.0f); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_19)
						case 19: { z=fabs(z+(float4)(ta,tb,ta,0.0f))-(float4)(ta,tb,ta,0.0f); { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tc*tc; if(r2<minR2){float s=td/minR2;z*=s;aux.DE*=s;} else if(r2<td){float s=td/r2;z*=s;aux.DE*=s;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_20)
						case 20: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float theta=atan2(z.y,z.x); float r=native_sqrt(z.x*z.x+z.y*z.y); r=fmax(r,tb); z.x=r*native_cos(theta); z.y=r*native_sin(theta); float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tc*tc){z*=1.0f/(tc*tc);aux.DE*=1.0f/(tc*tc);} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_21)
						case 21: { z=fabs(z)-(float4)(ta,ta,ta,0.0f); z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tc*tc){z*=td/(tc*tc);aux.DE*=td/(tc*tc);} else if(r2<td){z*=td/r2;aux.DE*=td/r2;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_22)
						case 22: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float sph=tb*tb/fmax(r2,tc*tc); z*=sph; aux.DE*=sph; z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_23)
						case 23: { float fold23=ta*(1.0f+tb*(float)i/250.0f); z.x=fabs(z.x+fold23)-fabs(z.x-fold23)-z.x; z.y=fabs(z.y+fold23)-fabs(z.y-fold23)-z.y; z.z=fabs(z.z+fold23)-fabs(z.z-fold23)-z.z;{ float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tc*tc){z*=td/(tc*tc);aux.DE*=td/(tc*tc);} else if(r2<td){z*=td/r2;aux.DE*=td/r2;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_24)
						case 24: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float k=tb/fmax(r,tc); z*=k; aux.DE*=k; z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_25)
						case 25: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tb*tb; float fixR2=tc*tc; float sph=clamp(fixR2/fmax(r2,minR2),1.0f,fixR2/minR2); z*=sph; aux.DE*=sph; z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_26)
						case 26: { if(z.x+z.y<0){float t=-z.y;z.y=-z.x;z.x=t;} if(z.x+z.z<0){float t=-z.z;z.z=-z.x;z.x=t;} z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tc*tc){z*=td/(tc*tc);aux.DE*=td/(tc*tc);} else if(r2<td){z*=td/r2;aux.DE*=td/r2;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_27)
						case 27: { z.x=ta-fabs(z.x-ta); z.y=ta-fabs(z.y-ta); z.z=ta-fabs(z.z-ta); { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){z*=tc/(tb*tb);aux.DE*=tc/(tb*tb);} else if(r2<tc){z*=tc/r2;aux.DE*=tc/r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_28)
						case 28: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float inv=tb/fmax(r2,1e-21f); z*=inv; aux.DE*=inv; z.x+=tc; z.y+=tc; z.z+=td; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_29)
						case 29: { float s29=sf; z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z;{ float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){s29*=tc/(tb*tb);} else if(r2<tc){s29*=tc/r2;} z*=s29; aux.DE=aux.DE*fabs(s29)+1.0f; z+=(float4)(td,td,td,0.0f); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_30)
						case 30: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tc)-fabs(z.z-tc)-z.z; { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(r<td&&r>1e-21f){float s=td/r;z*=s;aux.DE*=s;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_31)
						case 31: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tb*tb; if(r2<minR2){z*=1.0f/minR2;aux.DE*=1.0f/minR2;} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z.x=z.x*tc+td; z.y=z.y*tc; z.z=z.z*tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_32)
						case 32: { float a32=ta*M_PI_F/180.0f, c32=native_cos(a32),s32=native_sin(a32), ny=z.y*c32-z.z*s32; z.z=z.y*s32+z.z*c32; z.y=ny; z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z;{ float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tc*tc){z*=td/(tc*tc);aux.DE*=td/(tc*tc);} else if(r2<td){z*=td/r2;aux.DE*=td/r2;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_33)
						case 33: { z=fabs(z+(float4)(ta,ta,ta,0.0f))-(float4)(ta,ta,ta,0.0f); z=fabs(z+(float4)(tb,tb,tb,0.0f))-(float4)(tb,tb,tb,0.0f); { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tc*tc){z*=td/(tc*tc);aux.DE*=td/(tc*tc);} else if(r2<td){z*=td/r2;aux.DE*=td/r2;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_34)
						case 34: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float smooth=tb*tb/(fmax(r2,tc*tc)); z*=smooth; aux.DE*=smooth; z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_35)
						case 35: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float len=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float k=tb/fmax(len*len,tc); z*=k;aux.DE*=k; z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_36)
						case 36: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float f36=1.0f/(1.0f+native_exp(-tb*(r2-tc))); z*=f36*td; aux.DE=aux.DE*f36*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_37)
						case 37: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tb*tb; float maxSph=tc; float sph=clamp(1.0f/fmax(r2,minR2),1.0f,maxSph); z*=sph; aux.DE*=sph; z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_38)
						case 38: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float sum=fabs(z.x)+fabs(z.y)+fabs(z.z); if(sum>tb){float s=tb/sum;z*=s;aux.DE*=s;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; z+=(float4)(td,0.0f,0.0f,0.0f); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_39)
						case 39: { float fold39=ta+tb*native_sin((float)i*tc); z.x=fabs(z.x+fold39)-fabs(z.x-fold39)-z.x; z.y=fabs(z.y+fold39)-fabs(z.y-fold39)-z.y; z.z=fabs(z.z+fold39)-fabs(z.z-fold39)-z.z;{ float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<0.25f){z*=4.0f;aux.DE*=4.0f;} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_40)
						case 40: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float p=tb/fmax(r2,1e-21f); z.x=z.x*p+tc; z.y=z.y*p+tc; z.z=z.z*p+td; aux.DE=aux.DE*fabs(p)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_41)
						case 41: { if(z.x>ta)z.x=2.0f*ta-z.x; if(z.x<-ta)z.x=-2.0f*ta-z.x; if(z.y>ta)z.y=2.0f*ta-z.y; if(z.y<-ta)z.y=-2.0f*ta-z.y; if(z.z>ta)z.z=2.0f*ta-z.z; if(z.z<-ta)z.z=-2.0f*ta-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){z*=tc/(tb*tb);aux.DE*=tc/(tb*tb);} else if(r2<tc){z*=tc/r2;aux.DE*=tc/r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_42)
						case 42: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR=tb*tb; float fixR=tc*tc; float s42=(r2<minR)?fixR/minR:(r2<fixR)?fixR/r2:1.0f; z*=s42*td; aux.DE=aux.DE*s42*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_43)
						case 43: { z.x=ta-fabs(fabs(z.x)-ta); z.y=ta-fabs(fabs(z.y)-ta); z.z=ta-fabs(fabs(z.z)-ta); { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){z*=tc/(tb*tb);aux.DE*=tc/(tb*tb);} else if(r2<tc){z*=tc/r2;aux.DE*=tc/r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_44)
						case 44: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float invR=1.0f/fmax(r2,tb*tb); z*=invR*tc; aux.DE=aux.DE*invR*fabs(tc)+1.0f; z+=(float4)(td,td,td,0.0f); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_45)
						case 45: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float f45=tb/(1.0f+native_exp(tc*(r-td))); z*=f45; aux.DE*=f45; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_46)
						case 46: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float maxC=fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z))); if(maxC>tb){float s=tb/maxC;z*=s;aux.DE*=s;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; z+=(float4)(td,0.0f,0.0f,0.0f); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_47)
						case 47: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float k47=fmax(tb*tb/fmax(r2,tc*tc),1.0f); z*=k47*td; aux.DE=aux.DE*k47*fabs(td)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_48)
						case 48: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tb*tb; if(r2<minR2){z*=1.0f/minR2;aux.DE*=1.0f/minR2;} else if(r2<1.0f){z/=r2;aux.DE/=r2;} float sc48=tc+td*native_exp(-(float)i*sf); z*=sc48; aux.DE=aux.DE*fabs(sc48)+1.0f; } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_49)
						case 49: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float sph49=fmax(tb/fmax(r2,tc*tc),1.0f); z.x=z.x*sph49*td; z.y=z.y*sph49; z.z=z.z*sph49; aux.DE*=sph49*fabs(td); } break; }
#endif
#if !defined(MUTATION_PRUNE) || defined(MUT_NEED_MDTYPE_50)
						case 50: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; if(z.x-z.y<0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){float t=z.y;z.y=z.z;z.z=t;} float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){z*=tc/(tb*tb);aux.DE*=tc/(tb*tb);} else if(r2<tc){z*=tc/r2;aux.DE*=tc/r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; break; }
#endif
						default: break;
#endif
					}
					float md_blend = clamp(mut->mdWeight * mut->masterWeight, 0.0f, 1.0f);
					z = z_orig_md + (z - z_orig_md) * md_blend;
					aux.DE = de_orig_md + (aux.DE - de_orig_md) * md_blend;
				}

			// Curvature coloring
			if (mut->curvatureColoring != 0) {
				float prevDE2 = (aux.DE != 0.0f) ? aux.DE : 1.0f;
				float curv = aux.DE / prevDE2;
				if (curv < aux.color) aux.color = curv;
			}
		}

		// Post-mutation NaN/Inf recovery
		if (isnan(z.x) || isnan(z.y) || isnan(z.z) || isnan(z.w)
			|| isinf(z.x) || isinf(z.y) || isinf(z.z) || isinf(z.w))
		{
			z = preMutZ;
		}
		if (isnan(aux.DE) || isinf(aux.DE) || aux.DE < 1e-15f || aux.DE > 1e15f)
		{
			aux.DE = 1.0f;
		}
#endif // USE_MUTATION (mid/post + post-processing)

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

					// === Cinema4D-style: compute signed SDF per shape ===
					float sdf = 1e10f;

					switch (material->textureFractalizeShape)
					{
						case 0: // fractalizeShapeCube
						{
							float dx = fabs(zz.x) - size;
							float dy = fabs(zz.y) - size;
							float dz = fabs(zz.z) - size;
							sdf = max(dx, max(dy, dz));
							break;
						}
						case 1: // fractalizeShapeSphere
						{
							sdf = length(zz) - size;
							break;
						}
						case 2: // fractalizeShapeCross
						{
							float dxy = min(fabs(zz.x), fabs(zz.y)) - size;
							float dxz = min(fabs(zz.x), fabs(zz.z)) - size;
							float dyz = min(fabs(zz.y), fabs(zz.z)) - size;
							sdf = min(dxy, min(dxz, dyz));
							break;
						}
						case 3: // fractalizeShapeLine
						{
							sdf = native_sqrt(zz.x * zz.x + zz.y * zz.y) - size;
							break;
						}
						case 4: // fractalizeShapePlane
						{
							sdf = fabs(zz.z) - size;
							break;
						}
						case 5: // fractalizeShapeCylinder
						{
							sdf = native_sqrt(zz.x * zz.x + zz.y * zz.y) - size;
							break;
						}
						case 6: // fractalizeShapeTorus
						{
							float majorR = size * 0.7f;
							float minorR = size * 0.5f;
							float distXY = native_sqrt(zz.x * zz.x + zz.y * zz.y) - majorR;
							sdf = native_sqrt(distXY * distXY + zz.z * zz.z) - minorR;
							break;
						}
						case 7: // fractalizeShapeSpiral
						{
							float angle = atan2(zz.y, zz.x);
							float r = native_sqrt(zz.x * zz.x + zz.y * zz.y);
							float spiralR = fmod(r, size);
							float angleOffset = fmod(angle / (2.0f * M_PI_F) * size, size);
							float spiralDist = fmod(fabs(spiralR - angleOffset), size);
							if (spiralDist > size * 0.5f) spiralDist = size - spiralDist;
							sdf = native_sqrt(spiralDist * spiralDist + zz.z * zz.z) - size * 0.2f;
							break;
						}
					}

					// === Cinema4D-style: Gaussian weight per iteratie ===
					float falloff = size * 0.4f;
					if (falloff < 1e-10f) falloff = 1e-10f;
					float weight = exp(-(sdf * sdf) / (falloff * falloff));

					accumZ += z.xyz * weight;
					accumWeight += weight;

					if (sdf < closestSdf)
					{
						closestSdf = sdf;
						closestZ = z.xyz;
						closestIter = i;
					}

					// Early exit deep inside trap
					if (sdf < -size * 0.5f && !material->textureFractalizeIterationBlend)
					{
						break;
					}
				}
				if (aux.r > material->textureFractalizeCubeSize * 100.0f)
				{
					break;
				}
			}
#endif // FRACTALIZE_TEXTURE
		}
	}

	// === Cinema4D-style: stel output samen na alle iteraties ===
	if (mode == calcModeCubeOrbitTrap)
	{
		if (accumWeight > 1e-10f)
		{
			out.z = (float4)(accumZ / accumWeight, 0.0f);
			// Normaliseer colorIndex: clamp op 1000 zodat gradient consistent is
			out.colorIndex = fmin(accumWeight * 10.0f, 1000.0f);
			out.iters = closestIter + 1;
		}
		else if (closestSdf < 1e9f)
		{
			out.z = (float4)(closestZ, 0.0f);
			out.colorIndex = 0.0f;
			out.iters = closestIter + 1;
		}
		else
		{
			out.z = z;
			out.colorIndex = 0.0f;
			out.iters = i;
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



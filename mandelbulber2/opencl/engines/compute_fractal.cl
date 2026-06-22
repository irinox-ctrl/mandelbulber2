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
						float tanA = tan(mut->invAngle * M_PI_F / 180.0f);
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
						float tanAlpha = tan(mut->clipAngle * M_PI_F / 180.0f);
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
					case 31: { float r2d=native_sqrt(cz.x*cz.x+cz.y*cz.y), theta=atan2(cz.y,cz.x); int n=mut->clipNPoints;{ float starR=cr*(1.0f+mut->clipAmplitude*native_cos((float)n*theta)); clipDist=r2d-starR; } break; } // Star polygon clip
					case 32: { float x2h=cz.x*cz.x+cz.y*cz.y; clipDist=(x2h-1.0f)*(x2h-1.0f)*(x2h-1.0f)-cz.x*cz.x*cz.y*cz.y*cz.y; break; } // Heart surface clip
					case 33: { float r2d2=native_sqrt(cz.x*cz.x+cz.y*cz.y), theta2=atan2(cz.y,cz.x), m=(float)mut->clipNPoints, n1=ca,n2=cb,n3=cc, t=m*theta2/4.0f, r_sf=pow(pow(fabs(native_cos(t)/sx),n2)+pow(fabs(native_sin(t)/sy),n3),-1.0f/n1); clipDist=r2d2-r_sf*cr; break; } // Superformula clip
					case 34: { float r2d3=native_sqrt(cz.x*cz.x+cz.y*cz.y), theta3=atan2(cz.y,cz.x); int ng=mut->clipNPoints;{ float gearR=cr*(1.0f+0.1f*tanh(native_sin((float)ng*theta3))); clipDist=r2d3-gearR; } break; } // Gear clip
					case 35: { float r2d4=native_sqrt(cz.x*cz.x+cz.y*cz.y), theta4=atan2(cz.y,cz.x); int ns=mut->clipNPoints;{ float spiralR=ca*native_exp(-cb*theta4)*(1.0f+cc*native_cos((float)ns*theta4)); clipDist=r2d4-spiralR; } break; } // Spiral polygon clip
					case 36: { float3 seeds0=(float3)(ca,0.0f,0.0f), seeds1=(float3)(-ca,cb,0.0f), seeds2=(float3)(0.0f,-ca,cc), seeds3=(float3)(cb,cc,-ca); { float minVD=1e20f, vd0=length(cz-seeds0); if(vd0<minVD)minVD=vd0;float vd1=length(cz-seeds1); if(vd1<minVD)minVD=vd1; float vd2=length(cz-seeds2); if(vd2<minVD)minVD=vd2; float vd3=length(cz-seeds3); if(vd3<minVD)minVD=vd3; clipDist=minVD-cr; } break; } // Voronoi clip
					case 37: { float3 e0=(float3)(ca,0.0f,0.0f),e1=(float3)(-ca*0.5f,ca*0.866f,0.0f),e2=(float3)(-ca*0.5f,-ca*0.866f,0.0f); { float minED=1e20f; for(int k=0;k<3;k++){float3 ea,eb; if(k==0){ea=e0;eb=e1;} else if(k==1){ea=e1;eb=e2;} else{ea=e2;eb=e0;} float3 ev=eb-ea; float3 pv=cz-ea;float t=fmax(0.0f,fmin(1.0f,dot(pv,ev)/dot(ev,ev))); float ed=length(pv-ev*t); if(ed<minED)minED=ed;} clipDist=minED-cr; } break; } // Triangle edge clip
					case 38: { float3 lz=cz;float lscale=1.0f; for(int k=0;k<3;k++){lz.x=fabs(lz.x);lz.y=fabs(lz.y);lz.z=fabs(lz.z); if(lz.x<lz.y){float t=lz.x;lz.x=lz.y;lz.y=t;} if(lz.x<lz.z){float t=lz.x;lz.x=lz.z;lz.z=t;} if(lz.y<lz.z){float t=lz.y;lz.y=lz.z;lz.z=t;} lz=lz*ca-(float3)(cb,cb,cb)*(ca-1.0f); lscale*=ca;} clipDist=(length(lz)-cr)/lscale; break; } // Menger sponge clip
					case 39: { float jx=cz.x,jy=cz.y; for(int k=0;k<8;k++){float tx=jx*jx-jy*jy+ca; jy=2.0f*jx*jy+cb; jx=tx; if(jx*jx+jy*jy>4.0f)break;} float jDist=(jx*jx+jy*jy>4.0f)?-cr:cr; clipDist=fmax(jDist,fabs(cz.z)-sz); break; } // Julia set clip
					case 40: { float mx=0.0f,my=0.0f; for(int k=0;k<8;k++){float tx2=mx*mx-my*my+cz.x; my=2.0f*mx*my+cz.y; mx=tx2; if(mx*mx+my*my>4.0f)break;} float mDist=(mx*mx+my*my>4.0f)?-cr:cr; clipDist=fmax(mDist,fabs(cz.z)-sz); break; } // Mandelbrot clip
					case 41: { clipDist=fmax(fmax(fabs(cz.x),fabs(cz.y)),fmax(fabs(cz.z),fabs(z.w)))-cr; break; } // 4D hypercube clip
					case 42: { clipDist=native_sqrt(cz.x*cz.x+cz.y*cz.y+cz.z*cz.z+z.w*z.w)-cr; break; } // 4D hypersphere clip
					case 43: { float time=(float)i*mut->clipFrequency, tR=cr*(1.0f+mut->clipAmplitude*native_sin(time)); clipDist=length(cz)-tR; break; } // Temporal pulsing clip
					case 44: { float orbitR=cr*(1.0f+mut->clipAmplitude*native_sin(aux.color*mut->clipFrequency)); clipDist=length(cz)-orbitR; break; } // Orbit-reactive clip
					case 45: { float deR=cr*(1.0f+mut->clipAmplitude*native_log(1.0f+fabs(aux.DE))); clipDist=length(cz)-deR; break; } // DE-reactive clip
					case 46: { float colR=cr*(1.0f+mut->clipAmplitude*native_sin(aux.color*mut->clipFrequency)); clipDist=length(cz)-colR; break; } // Color-reactive clip
					case 47: { float iterR=cr*(1.0f+mut->clipAmplitude*(float)i/250.0f); clipDist=length(cz)-iterR; break; } // Progressive clip
					case 48: { float rh=fabs(native_sin((float)i*12.9898f+cz.x*78.233f)*43758.5453f); rh=rh-floor(rh); { float randR=cr*(1.0f+mut->clipAmplitude*(rh-0.5f)); clipDist=length(cz)-randR; } break; } // Random jitter clip
					case 49: { float nx=tanh(ca*cz.x+cb*cz.y+cc*cz.z), ny=tanh(cb*cz.x-ca*cz.y+cc*cz.z), nz=tanh(cc*cz.x+ca*cz.y-cb*cz.z); clipDist=native_sqrt(nx*nx+ny*ny+nz*nz)-cr; break; } // Neural tanh clip
					case 50: { float3 rz=cz;{ float rscale=1.0f; clipDist=1e10f; for(int k=0;k<5;k++){rz.x=fabs(rz.x)*2.0f-ca; rz.y=fabs(rz.y)*2.0f-ca; rz.z=fabs(rz.z)*2.0f-ca; rscale*=2.0f; float rd=length(rz)-cr; rd/=rscale; if(rd<clipDist)clipDist=rd;} } break; } // Recursive fractal clip
					case 51: { clipDist=native_sin(cz.x*ca)*native_cos(cz.y*ca)+native_sin(cz.y*ca)*native_cos(cz.z*ca)+native_sin(cz.z*ca)*native_cos(cz.x*ca)-cr; break; } // Gyroid surface
					case 52: { clipDist=native_cos(cz.x*ca)+native_cos(cz.y*ca)+native_cos(cz.z*ca)-cr; break; } // Schwarz P surface
					case 53: { clipDist=native_sin(cz.x*ca)*native_sin(cz.y*ca)*native_sin(cz.z*ca)+native_sin(cz.x*ca)*native_cos(cz.y*ca)*native_cos(cz.z*ca)+native_cos(cz.x*ca)*native_sin(cz.y*ca)*native_cos(cz.z*ca)+native_cos(cz.x*ca)*native_cos(cz.y*ca)*native_sin(cz.z*ca)-cr; break; } // Diamond surface
					case 54: { clipDist=0.5f*(native_sin(2.0f*cz.x*ca)*native_cos(cz.y*ca)*native_sin(cz.z*ca)+native_sin(2.0f*cz.y*ca)*native_cos(cz.z*ca)*native_sin(cz.x*ca)+native_sin(2.0f*cz.z*ca)*native_cos(cz.x*ca)*native_sin(cz.y*ca))-0.5f*(native_cos(2.0f*cz.x*ca)*native_cos(2.0f*cz.y*ca)+native_cos(2.0f*cz.y*ca)*native_cos(2.0f*cz.z*ca)+native_cos(2.0f*cz.z*ca)*native_cos(2.0f*cz.x*ca))-cr; break; } // Lidinoid surface
					case 55: { clipDist=3.0f*(native_cos(cz.x*ca)+native_cos(cz.y*ca)+native_cos(cz.z*ca))+4.0f*native_cos(cz.x*ca)*native_cos(cz.y*ca)*native_cos(cz.z*ca)-cr; break; } // Neovius surface
					case 56: { float t56=atan2(cz.y,cz.x), kx=native_cos(2.0f*t56)*(cR+cr*native_cos(3.0f*t56)), ky=native_sin(2.0f*t56)*(cR+cr*native_cos(3.0f*t56)), kz=cr*native_sin(3.0f*t56); clipDist=native_sqrt((cz.x-kx)*(cz.x-kx)+(cz.y-ky)*(cz.y-ky)+(cz.z-kz)*(cz.z-kz))-ca; break; } // Torus knot
					case 57: { clipDist=cz.x*cz.x*cz.z+cz.y*cz.y*cz.z-ca*cz.x*cz.y-cr; break; } // Cross-cap surface
					case 58: { float phi58=0.5f*(1.0f+native_sqrt(5.0f)), p2=phi58*phi58, r2=cz.x*cz.x+cz.y*cz.y+cz.z*cz.z; clipDist=4.0f*(p2*cz.x*cz.x-cz.y*cz.y)*(p2*cz.y*cz.y-cz.z*cz.z)*(p2*cz.z*cz.z-cz.x*cz.x)-(1.0f+2.0f*phi58)*(r2-ca*ca)*(r2-ca*ca); break; } // Barth sextic
					case 59: { clipDist=cz.x*cz.x*cz.y*cz.y+cz.y*cz.y*cz.z*cz.z+cz.z*cz.z*cz.x*cz.x-ca*cz.x*cz.y*cz.z; break; } // Steiner surface
					case 60: { float r60=length(cz); if(r60<1e-15f)r60=1e-15f;{ float x60=cz.x/r60,y60=cz.y/r60,z60=cz.z/r60; clipDist=64.0f*x60*x60*x60*z60-48.0f*x60*z60*(3.0f*x60*x60+z60*z60)+12.0f*z60*(x60*x60-z60*z60)+x60*x60+y60*y60+z60*z60-cr*cr; } break; } // Boy surface approx
					case 61: { float r61=length(cz); clipDist=r61*native_exp(-ca*r61)-cr; break; } // Exponential decay shell
					case 62: { float r62=native_sqrt(cz.x*cz.x+cz.y*cz.y), t62=atan2(cz.y,cz.x), spiralR=ca*native_exp(cb*t62); clipDist=fabs(r62-spiralR)+fabs(cz.z)-cr; break; } // Logarithmic spiral shell
					case 63: { float t63=atan2(cz.y,cz.x), r63=native_sqrt(cz.x*cz.x+cz.y*cz.y), h1=r63-cR-cr*native_cos(ca*cz.z), h2=r63-cR+cr*native_cos(ca*cz.z+M_PI_F); clipDist=fmin(native_sqrt(h1*h1+pow(cr*native_sin(ca*cz.z),2.0f)),native_sqrt(h2*h2+pow(cr*native_sin(ca*cz.z+M_PI_F),2.0f)))-cb; break; } // Double helix
					case 64: { float dx64=fabs(cz.x)-sx, dy64=fabs(cz.y)-sy, dz64=fabs(cz.z)-sz, chamfer=ca; clipDist=fmax(fmax(dx64,fmax(dy64,dz64)),(dx64+dy64+dz64)*chamfer); break; } // Chamfered cube
					case 65: { float dx65=fmax(fabs(cz.x)-sx,0.0f), dy65=fmax(fabs(cz.y)-sy,0.0f), dz65=fmax(fabs(cz.z)-sz,0.0f); clipDist=native_sqrt(dx65*dx65+dy65*dy65+dz65*dz65)-cr; break; } // Rounded box
					case 66: { clipDist=fabs(cz.x)+fabs(cz.y)+fabs(cz.z)-cr; break; } // Octahedron
					case 67: { float phi67=0.5f*(1.0f+native_sqrt(5.0f)); clipDist=fmax(fmax(fabs(cz.x)+phi67*fabs(cz.y),fabs(cz.y)+phi67*fabs(cz.z)),fabs(cz.z)+phi67*fabs(cz.x))-cr*(1.0f+phi67); break; } // Dodecahedron approx
					case 68: { float phi68=0.5f*(1.0f+native_sqrt(5.0f)); clipDist=fmax(fabs(cz.x)+phi68*fabs(cz.z),fmax(fabs(cz.y)+phi68*fabs(cz.x),fabs(cz.z)+phi68*fabs(cz.y)))-cr*phi68*phi68; break; } // Icosahedron approx
					case 69: { float d69a=fmax(fabs(cz.x),fmax(fabs(cz.y),fabs(cz.z)))-sx, d69b=(fabs(cz.x)+fabs(cz.y)+fabs(cz.z))*0.577f-cr; clipDist=fmax(d69a,d69b); break; } // Truncated octahedron
					case 70: { float q70x=fabs(cz.x), q70y=fabs(cz.y); clipDist=fmax(q70x*0.866f+q70y*0.5f,q70y)-cr; clipDist=fmax(clipDist,fabs(cz.z)-sz); break; } // Hex prism
					case 71: { clipDist=fmax(fabs(cz.z)-sz,fmax(fabs(cz.x)*0.866f+cz.y*0.5f,-cz.y)-cr); break; } // Triangular prism
					case 72: { float rxy72a=native_sqrt(cz.x*cz.x+cz.y*cz.y), d72a=native_sqrt((rxy72a-cR)*(rxy72a-cR)+cz.z*cz.z)-cr, ryz72=native_sqrt(cz.y*cz.y+cz.z*cz.z), d72b=native_sqrt((ryz72-cR)*(ryz72-cR)+cz.x*cz.x)-cr; clipDist=fmin(d72a,d72b); break; } // Link
					case 73: { float r73=native_sqrt(cz.x*cz.x+cz.y*cz.y)-cr, h73=fabs(cz.z)-sz; clipDist=fmin(fmax(r73,h73),0.0f)+native_sqrt(fmax(r73,0.0f)*fmax(r73,0.0f)+fmax(h73,0.0f)*fmax(h73,0.0f)); break; } // Capped cylinder
					case 74: { float capH=fmax(0.0f,fmin(sz,cz.z)); clipDist=native_sqrt(cz.x*cz.x+cz.y*cz.y+(cz.z-capH)*(cz.z-capH))-cr; break; } // Capsule
					case 75: { float t75=atan2(cz.y,cz.x), r75=native_sqrt(cz.x*cz.x+cz.y*cz.y), knotR=cR+cr*native_cos(3.0f*t75); clipDist=native_sqrt((r75-knotR)*(r75-knotR)+cz.z*cz.z)-ca; break; } // Trefoil knot
					case 76: { float t76=atan2(cz.y,cz.x), r76=native_sqrt(cz.x*cz.x+cz.y*cz.y)-cR, localZ=cz.z*native_cos(t76*0.5f)-r76*native_sin(t76*0.5f); clipDist=fabs(localZ)-ca; break; } // Mobius strip approx
					case 77: { float sc77x=native_sin(cz.x*ca)*native_sin(cz.x*ca), sc77y=native_sin(cz.y*ca)*native_sin(cz.y*ca), sc77z=native_sin(cz.z*ca)*native_sin(cz.z*ca); clipDist=sc77x+sc77y+sc77z-cr; break; } // Sine cage
					case 78: { clipDist=cz.x*cz.x*cz.x*cz.x+cz.y*cz.y*cz.y*cz.y+cz.z*cz.z*cz.z*cz.z-ca*(cz.x*cz.x+cz.y*cz.y+cz.z*cz.z); break; } // Pillow shape
					case 79: { float n79=native_sin(ca*cz.x)*native_sin(ca*cz.y)*native_sin(ca*cz.z); clipDist=length(cz)-cr-cb*n79; break; } // Displacement sphere
					case 80: { float r80=native_sqrt(cz.x*cz.x+cz.y*cz.y)-cR, ang80=ca*atan2(cz.y,cz.x)/(2.0f*M_PI_F); clipDist=r80*r80+(cz.z-ang80)*(cz.z-ang80)-cr*cr; break; } // Corkscrew
					case 81: { float u81=atan2(cz.y,cz.x), v81=atan2(cz.z,native_sqrt(cz.x*cz.x+cz.y*cz.y)-cR), kb=ca*(1.0f-0.5f*native_cos(u81))*native_sin(v81)-cb*native_cos(v81); clipDist=fabs(kb)-cr; break; } // Klein bottle section
					case 82: { float r82=native_sqrt(cz.x*cz.x+cz.y*cz.y), wave82=cr+ca*native_sin(cb*cz.z); clipDist=r82-wave82; break; } // Wavy cylinder
					case 83: { float twist83=ca*cz.z, rx83=cz.x*native_cos(twist83)-cz.y*native_sin(twist83), ry83=cz.x*native_sin(twist83)+cz.y*native_cos(twist83); clipDist=fmax(fabs(rx83)-sx,fmax(fabs(ry83)-sy,fabs(cz.z)-sz)); break; } // Twisted box
					case 84: { float bend84=ca*cz.x, bz84=cz.z+bend84*bend84, rxy84=native_sqrt(cz.x*cz.x+cz.y*cz.y)-cR; clipDist=native_sqrt(rxy84*rxy84+bz84*bz84)-cr; break; } // Bent torus
					case 85: { clipDist=cz.z-ca*native_sin(cb*cz.x)-cc*native_cos(cb*cz.y)-cr; break; } // Corrugated plane
					case 86: { float r86=length(cz); if(r86<1e-15f)r86=1e-15f;{ float theta86=acos(cz.z/r86), phi86=atan2(cz.y,cz.x), m86=(float)mut->clipNPoints, st86=pow(pow(fabs(native_cos(m86*theta86/4.0f)),cb)+pow(fabs(native_sin(m86*theta86/4.0f)),cc),-1.0f/ca), sp86=pow(pow(fabs(native_cos(m86*phi86/4.0f)),cb)+pow(fabs(native_sin(m86*phi86/4.0f)),cc),-1.0f/ca); clipDist=r86-cr*st86*sp86; } break; } // Supershape 3D
					case 87: { float r87=length(cz), cosTheta87=cz.z/(r87+1e-15f); clipDist=r87-cr*(1.0f+ca*cosTheta87); break; } // Egg shape
					case 88: { float x2_88=cz.x*cz.x,y2_88=cz.y*cz.y,z2_88=cz.z*cz.z; clipDist=2.0f*y2_88*(y2_88-ca*ca)*(y2_88-ca*ca)-x2_88*x2_88+2.0f*ca*ca*(x2_88-z2_88*3.0f)*(x2_88-z2_88); break; } // Genus-2 surface
					case 89: { float fx89=fabs(fmod(cz.x+ca,2.0f*ca))-ca, fy89=fabs(fmod(cz.y+ca,2.0f*ca))-ca, fz89=fabs(fmod(cz.z+ca,2.0f*ca))-ca; clipDist=native_sqrt(fx89*fx89+fy89*fy89+fz89*fz89)-cr; break; } // Folded sphere
					case 90: { clipDist=fmax(fmax(fabs(cz.x+cz.y),fabs(cz.x-cz.y)),fmax(fabs(cz.y+cz.z),fmax(fabs(cz.y-cz.z),fmax(fabs(cz.x+cz.z),fabs(cz.x-cz.z)))))-cr; break; } // Rhombic dodecahedron
					case 91: { clipDist=fmax(fabs(cz.x+cz.y+cz.z),fmax(fabs(cz.x-cz.y-cz.z),fmax(fabs(-cz.x+cz.y-cz.z),fabs(-cz.x-cz.y+cz.z))))-cr; break; } // Tetrahedral symmetry
					case 92: { clipDist=native_sin(ca*cz.x)+native_sin(ca*cz.y)+native_sin(ca*cz.z)-cr; break; } // Egg crate
					case 93: { float denom93=native_cos(ca*cz.y)*native_cos(ca*cz.z)+1e-10f; clipDist=native_sin(ca*cz.x)-native_sin(ca*cz.y)*native_sin(ca*cz.z)/denom93; break; } // Scherk surface
					case 94: { float u94=cz.x,v94=cz.y, ex94=u94-u94*u94*u94/3.0f+u94*v94*v94, ey94=v94-v94*v94*v94/3.0f+v94*u94*u94, ez94=u94*u94-v94*v94; clipDist=native_sqrt((cz.x-ex94)*(cz.x-ex94)+(cz.y-ey94)*(cz.y-ey94)+(cz.z-ez94)*(cz.z-ez94))-cr; break; } // Enneper surface
					case 95: { clipDist=cz.x*cz.x/fmax(sx*sx,1e-10f)-cz.y*cz.y/fmax(sy*sy,1e-10f)-cz.z; break; } // Saddle clip
					case 96: { clipDist=cz.x*(cz.x*cz.x-3.0f*cz.y*cz.y)-ca*cz.z; break; } // Monkey saddle
					case 97: { clipDist=fabs(cz.x)+fabs(cz.y)+fabs(cz.z)+fabs(z.w)-cr; break; } // Cross-polytope
					case 98: { clipDist=cz.x*cz.x/fmax(sx*sx,1e-10f)+cz.y*cz.y/fmax(sy*sy,1e-10f)-cz.z; break; } // Elliptic paraboloid
					case 99: { float d99s=length(cz)-cr, d99b=fmax(fabs(cz.x)-sx,fmax(fabs(cz.y)-sy,fabs(cz.z)-sz)), k99=mut->clipSmoothK, h99=fmax(0.0f,fmin(1.0f,0.5f-0.5f*(d99s-d99b)/fmax(k99,1e-10f))); clipDist=d99s*(1.0f-h99)+d99b*h99+k99*h99*(1.0f-h99); break; } // Smooth intersection
					case 100: { float3 ifs=cz;float ifsScale=1.0f; for(int k=0;k<6;k++){if(ifs.x+ifs.y<0.0f){float t=-ifs.y;ifs.y=-ifs.x;ifs.x=t;} if(ifs.x+ifs.z<0.0f){float t=-ifs.z;ifs.z=-ifs.x;ifs.x=t;} if(ifs.y+ifs.z<0.0f){float t=-ifs.z;ifs.z=-ifs.y;ifs.y=t;} ifs=ifs*ca-(float3)(cb,cb,cb)*(ca-1.0f); ifsScale*=ca;} clipDist=(length(ifs)-cr)/ifsScale; break; } // Sierpinski IFS

					default: break;
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
					case 1: { float k1=ja,k2=jb,k3=jc,k4=jd, curv=(k1+k2+k3+k4)/fmax(1.0f,r); aux.DE*=(1.0f+jf*curv); break; }
					case 2: { float phi=atan2(zy,zx), sp=ja*native_exp(2.0f*M_PI_F*(jb*phi+jc*native_log(fmax(1e-10f,r)))); aux.DE*=(1.0f+jf*sp); break; }
					case 3: { float prod=1.0f; for(int k=0;k<4;k++){float dk=r+ja*(float)(k+1); prod*=fmax(0.01f,dk);} aux.DE*=(1.0f+jf*jsc/fmax(1e-10f,prod)); break; }
					case 4: { float af=ja*native_log(fmax(1e-10f,r))+jb*atan2(zy,zx); aux.DE*=(1.0f+jf*tanh(af)); break; }
					case 5: { float hyp=4.0f*M_PI_F*(ja-1.0f)/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*tanh(hyp)); break; }
					case 6: { float bel=ja*zy/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*tanh(bel)); break; }
					case 7: { float tr=ja*jb/fmax(1e-10f,r); aux.DE*=(1.0f+jf*tanh(tr)); break; }
					case 8: { float rl=ja/(fmax(1e-10f,r*r)+jb*jb); aux.DE*=(1.0f+jf*rl); break; }
					case 9: { float bs=ja*jb*jc/fmax(1e-10f,rr); aux.DE*=(1.0f+jf*tanh(bs)); break; }
					case 10: { float ew=ja*native_sin(jfreq*zx)*native_cos(jfreq*zy)/fmax(1e-10f,r); aux.DE*=(1.0f+jf*ew); break; }
					case 11: { float hc=native_exp(-fabs(zy))*ja/fmax(1e-10f,r); aux.DE*=(1.0f+jf*hc); break; }
					case 12: { float q2=fmax(1.0f,ja), fr2=1.0f/(2.0f*q2*q2); aux.DE*=(1.0f+jf*fr2/fmax(1e-10f,r)); break; }
					case 13: { float med=(zx+zy)/(fmax(1e-10f,2.0f*r)); aux.DE*=(1.0f+jf*ja*med); break; }
					case 14: { float jt=ja*native_sin(M_PI_F*zx/fmax(0.01f,jb))*native_sin(M_PI_F*zy/fmax(0.01f,jc)); aux.DE*=(1.0f+jf*jt/fmax(1e-10f,rr)); break; }
					case 15: { float eta=native_exp(M_PI_F*zy/(12.0f*fmax(0.01f,ja))); for(int n=1;n<8;n++) eta*=(1.0f-native_exp(-2.0f*M_PI_F*n*fabs(zy)/fmax(0.01f,ja))); aux.DE*=(1.0f+jf*fabs(eta)); break; }
					case 16: { float wp=1.0f/(rr+1e-10f); for(int n=1;n<6;n++){float dn2=(zx-n*ja)*(zx-n*ja)+(zy-n*jb)*(zy-n*jb)+zz2*zz2; wp+=1.0f/fmax(1e-10f,dn2)-1.0f/(n*n*ja*ja+n*n*jb*jb+1e-10f);} aux.DE*=(1.0f+jf*fabs(wp)); break; }
					case 17: { float th=0.0f; for(int n=0;n<8;n++){float qn=native_exp(-M_PI_F*n*n*fabs(zy)/fmax(0.01f,ja)); th+=qn*native_cos(2.0f*M_PI_F*n*zx/fmax(0.01f,ja));} aux.DE*=(1.0f+jf*fabs(th)); break; }
					case 18: { float eis=0.0f; for(int m=-3;m<=3;m++) for(int n=-3;n<=3;n++){if(m==0&&n==0)continue;float dn=m*ja+n*jb; eis+=1.0f/fmax(1e-10f,native_powr(fabs(dn*dn+rr),jc));} aux.DE*=(1.0f+jf*fabs(eis)); break; }
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
					default: break;
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
					default: break;
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
					case 1: { if(zx>ma) z.x=mb*2.0-zx; if(zx<-ma) z.x=-mb*2.0-zx; if(zy>ma) z.y=mb*2.0-zy; if(zy<-ma) z.y=-mb*2.0-zy; if(zz2>ma) z.z=mb*2.0-zz2; if(zz2<-ma) z.z=-mb*2.0-zz2; aux.DE*=fabs(mf); break; }
					case 2: { float lim=ma*(1.0+0.1*native_sin(i*mc)); if(fabs(zx)>lim) z.x=copysign(mb*2.0,zx)-zx; if(fabs(zy)>lim) z.y=copysign(mb*2.0,zy)-zy; if(fabs(zz2)>lim) z.z=copysign(mb*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
					case 3: { float sx=ma,sy=mb,sz=mc, fx=1.0/(1.0+native_exp(-sx*(fabs(zx)-md))), fy=1.0/(1.0+native_exp(-sy*(fabs(zy)-md))), fz=1.0/(1.0+native_exp(-sz*(fabs(zz2)-md))); z.x=zx*(1.0-fx)+copysign(me*2.0-fabs(zx),zx)*fx; z.y=zy*(1.0-fy)+copysign(me*2.0-fabs(zy),zy)*fy; z.z=zz2*(1.0-fz)+copysign(me*2.0-fabs(zz2),zz2)*fz; aux.DE*=fabs(mf); break; }
					case 4: { float l1=ma,v1=mb,l2=mc,v2=md; if(fabs(zx)>l1) z.x=copysign(v1*2.0,zx)-zx; if(fabs(zx)>l2) z.x=copysign(v2*2.0,zx)-zx; if(fabs(zy)>l1) z.y=copysign(v1*2.0,zy)-zy; if(fabs(zy)>l2) z.y=copysign(v2*2.0,zy)-zy; if(fabs(zz2)>l1) z.z=copysign(v1*2.0,zz2)-zz2; if(fabs(zz2)>l2) z.z=copysign(v2*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
					case 5: { float rxy=native_sqrt(zx*zx+zy*zy); if(rxy>ma){ float th=atan2(zy,zx); float nr=ma*2.0-rxy; z.x=nr*native_cos(th); z.y=nr*native_sin(th); } aux.DE*=fabs(mf); break; }
					case 6: { float rxy=native_sqrt(zx*zx+zy*zy), ea=(zx/(ma+1e-21))*(zx/(ma+1e-21))+(zy/(mb+1e-21))*(zy/(mb+1e-21)); if(ea>1.0){ float sc=1.0/native_sqrt(ea); z.x*=sc; z.y*=sc; } aux.DE*=fabs(mf); break; }
					case 7: { if(fabs(zx)+fabs(zy)>ma){ float sx=(zx>0)?1.0:-1.0,sy=(zy>0)?1.0:-1.0;float nx=ma*0.5*sx,ny=ma*0.5*sy; z.x=2.0*nx-zx; z.y=2.0*ny-zy; } aux.DE*=fabs(mf)*1.41421356; break; }
					case 8: { float ax=fabs(zx),ay=fabs(zy), hx=fmax(ax,ay*0.8660254+ax*0.5); if(hx>ma){ z.x=copysign(ma*2.0-ax,zx); z.y=copysign(ma*2.0-ay,zy); } aux.DE*=fabs(mf); break; }
					case 9: { float ax=fabs(zx),ay=fabs(zy), ox=fmax(ax,fmax(ay,(ax+ay)*0.7071068)); if(ox>ma){ z.x=copysign(ma*2.0-ax,zx); z.y=copysign(ma*2.0-ay,zy); } aux.DE*=fabs(mf); break; }
					case 10: { float th=atan2(zy,zx), rxy=native_sqrt(zx*zx+zy*zy), rlim=ma*(1.0+mb*native_cos(mc*th)); if(rxy>rlim){ float nr=rlim*2.0-rxy; z.x=nr*native_cos(th); z.y=nr*native_sin(th); } aux.DE*=fabs(mf); break; }
					case 11: { float th=atan2(zy,zx), rxy=native_sqrt(zx*zx+zy*zy), rlim=ma*native_exp(-mb*th); if(rxy>rlim){ float nr=rlim*2.0-rxy; z.x=nr*native_cos(th); z.y=nr*native_sin(th); } aux.DE*=fabs(mf); break; }
					case 12: { float limy=ma+mb*native_sin(mc*zy); if(fabs(zx)>limy) z.x=copysign(limy*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; aux.DE*=fabs(mf)*(1.0+fabs(mb*mc)); break; }
					case 13: { float h1=ma+mb*native_sin(mc*zx)*native_sin(mc*zy)*native_sin(mc*zz2); if(fabs(zx)>h1) z.x=copysign(h1*2.0,zx)-zx; if(fabs(zy)>h1) z.y=copysign(h1*2.0,zy)-zy; if(fabs(zz2)>h1) z.z=copysign(h1*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
					case 14: { float h1=ma+mb*native_sin(mc*zx)*native_cos(md*zy); if(fabs(zx)>h1) z.x=copysign(h1*2.0,zx)-zx; if(fabs(zy)>h1) z.y=copysign(h1*2.0,zy)-zy; if(fabs(zz2)>h1) z.z=copysign(h1*2.0,zz2)-zz2; aux.DE*=fabs(mf)*(1.0+fabs(mb*mc)); break; }
					case 15: { float jv=ma+0.1*native_sin(mc*zx)*native_sin(mc*zy); if(fabs(zx)>jv) z.x=copysign(jv*2.0,zx)-zx; if(fabs(zy)>jv) z.y=copysign(jv*2.0,zy)-zy; aux.DE*=fabs(mf); break; }
					case 16: { float lt=ma+0.1*native_sin(mb*i); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
					case 17: { float lt=ma*(1.0+0.1*r); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
					case 18: { float cl=fabs(length(z)), lt=ma+cl*mb; if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
					case 19: { float c1=ma,c2=-ma; if(zx>c1+mb) z.x=2.0*c1+mb*2.0-zx; if(zx<c2-mb) z.x=2.0*c2-mb*2.0-zx; if(zy>c1+mb) z.y=2.0*c1+mb*2.0-zy; if(zy<c2-mb) z.y=2.0*c2-mb*2.0-zy; aux.DE*=fabs(mf); break; }
					case 20: { float lt=ma; for(int n=0;n<3&&n<(int)mb;n++){ lt*=0.5; if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; } aux.DE*=fabs(mf); break; }
					case 21: { if(i>(int)mb){ if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; } aux.DE*=fabs(mf); break; }
					case 22: { float h=(native_sin(i*12.9898+zx*78.233)*43758.5453 - floor(native_sin(i*12.9898+zx*78.233)*43758.5453)); if(h<mc){ if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; } aux.DE*=fabs(mf)*(1.0-mc+mc*mb); break; }
					case 23: { float dt=zx*mc+zy*md+zz2*me, lt=ma*(1.0+0.1*dt/fmax(1e-10,r)); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
					case 24: { float lt=ma+mc*zx*zx; if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx;{ float lty=ma+mc*zy*zy; if(fabs(zy)>lty) z.y=copysign(lty*2.0,zy)-zy; aux.DE*=fabs(mf)*(1.0+2.0*fabs(mc*r)); } break; }
					case 25: { float lt=ma+mb*native_sin(mc*zx); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx;{ float lty=ma+mb*native_sin(mc*zy); if(fabs(zy)>lty) z.y=copysign(lty*2.0,zy)-zy; float ltz=ma+mb*native_sin(mc*zz2); if(fabs(zz2)>ltz) z.z=copysign(ltz*2.0,zz2)-zz2; aux.DE*=fabs(mf)*(1.0+fabs(mb*mc)); } break; }
					case 26: { float rre=(zx/(ma+1e-10))*(zx/(ma+1e-10))+(zy/(mb+1e-10))*(zy/(mb+1e-10))+(zz2/(mc+1e-10))*(zz2/(mc+1e-10)); if(rre<1e-21) rre=1e-21;{ float m2=md*md/rre; z*=m2; aux.DE*=m2; } break; }
					case 27: { float rrc=zx*zx+zy*zy; if(rrc<1e-21) rrc=1e-21;{ float m2=ma*ma/rrc; z.x*=m2; z.y*=m2; z.z*=m2; aux.DE*=m2; } break; }
					case 28: { float rxy=native_sqrt(zx*zx+zy*zy), rrt=(rxy-ma)*(rxy-ma)+zz2*zz2; if(rrt<1e-21) rrt=1e-21;{ float m2=mb*mb/rrt; z*=m2; aux.DE*=m2; } break; }
					case 29: { float rrh=zx*zx+zy*zy-zz2*zz2, ar=fabs(rrh); if(ar<1e-21) ar=1e-21;{ float m2=ma*ma/ar; z*=m2; aux.DE*=m2*fmax(1.0,fabs(zz2)); } break; }
					case 30: { float rrp=zx*zx+zy*zy-ma*zz2, ar=fabs(rrp); if(ar<1e-21) ar=1e-21;{ float m2=mb*mb/ar; z*=m2; aux.DE*=m2*native_sqrt(1.0+4.0*ma*ma); } break; }
					default: break;
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
						case 1: { z.x += wf*wam*native_sin(wfq*zy + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq*native_cos(wfq*zy + wph))); break; }
						case 2: { z.y += wf*wam*native_sin(wfq*zz2 + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq*native_cos(wfq*zz2 + wph))); break; }
						case 3: { z.z += wf*wam*native_sin(wfq*zx + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq*native_cos(wfq*zx + wph))); break; }
						case 4: { z.x += wf*wam*native_sin(wfq*zy + wph); z.y += wf*wam*native_sin(wfq*zz2 + wph); z.z += wf*wam*native_sin(wfq*zx + wph); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq)); break; }
						case 5: { z.x += wf*wam*native_cos(wfq*zy + wph)*native_sin(wfq*zz2); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 6: { float ph = atan2(zy, zx); z.x += wf*wam*native_sin(wfq*ph + wph); z.y += wf*wam*native_cos(wfq*ph + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 7: { float ph = atan2(zy, zx), th = acos(zz2/r); z.x += wf*wam*native_sin(wfq*th + wph)*native_cos(ph); z.y += wf*wam*native_sin(wfq*th + wph)*native_sin(ph); z.z += wf*wam*native_cos(wfq*th + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 8: { z.x += wf*wam*native_sin(wfq*zy + wph)*native_cos(wfq*zz2); z.y += wf*wam*native_sin(wfq*zz2 + wph)*native_cos(wfq*zx); z.z += wf*wam*native_sin(wfq*zx + wph)*native_cos(wfq*zy); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq)); break; }
						case 9: { z.x += wf*wam*native_sin(wfq*zx + wph); z.y += wf*wb*native_sin(wfq*zy + wph); z.z += wf*wc*native_sin(wfq*zz2 + wph); aux.DE *= (1.0 + fabs(wf*(wam+wb+wc)*wfq/3.0)); break; }
						case 10: { float d = wf*wam*native_sin(wfq*r + wph); z.x += d*zx/r; z.y += d*zy/r; z.z += d*zz2/r; aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 11: { z.x += wf*wam*native_sin(wfq*native_sin(wa*zy) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 12: { z.y += wf*wam*native_sin(wfq*native_cos(wa*zz2) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 13: { z.z += wf*wam*native_cos(wfq*native_sin(wa*zx) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 14: { float d1 = native_sin(wfq*zx+wph), d2 = native_sin(wa*zy+wb); z.x += wf*wam*native_sin(wfq*d1+d2); z.y += wf*wam*native_cos(wa*d1-d2); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq)); break; }
						case 15: { z.x += wf*wam*native_sin(wfq*(zx*zy) + wph); z.y += wf*wam*native_cos(wfq*(zy*zz2) + wph); z.z += wf*wam*native_sin(wfq*(zz2*zx) + wph); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq)); break; }
						case 16: { float n1 = native_sin(wfq*zx+wa*zy), n2 = native_sin(wa*zy+wb*zz2); z.x += wf*wam*native_sin(wfq*n1+wph); z.y += wf*wam*native_sin(wfq*n2+wph); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq)); break; }
						case 17: { float n1 = native_cos(wfq*zx)*native_sin(wa*zy), n2 = native_cos(wa*zy)*native_sin(wb*zz2), n3 = native_cos(wb*zz2)*native_sin(wfq*zx); z.x += wf*wam*n1; z.y += wf*wam*n2; z.z += wf*wam*n3; aux.DE *= (1.0 + 3.0*fabs(wf*wam)); break; }
						case 18: { z.x += wf*wam*native_sin(wfq*zy*zz2/(r+1e-21) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 19: { float t = wfq*r+wph; z.x += wf*wam*native_sin(t)*native_cos(wa*zy); z.y += wf*wam*native_cos(t)*native_sin(wa*zz2); z.z += wf*wam*native_sin(t)*native_cos(wa*zx); aux.DE *= (1.0 + 3.0*fabs(wf*wam)); break; }
						case 20: { float q = native_sin(wfq*zx+wph)+native_sin(wa*zy+wb)+native_sin(wc*zz2+wd); z.x += wf*wam*native_sin(q); z.y += wf*wam*native_cos(q); z.z += wf*wam*native_sin(q+M_PI_F*0.5); aux.DE *= (1.0 + 3.0*fabs(wf*wam)); break; }
						case 21: { { float v=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o); v+=native_sin(f*zx+wph)*native_cos(f*zy)/pow(2.0,o);} z.x+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
						case 22: { { float v=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o); v+=native_sin(f*zy+wph)*native_cos(f*zz2)/pow(2.0,o);} z.y+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
						case 23: { { float v=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o); v+=native_sin(f*zz2+wph)*native_cos(f*zx)/pow(2.0,o);} z.z+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
						case 24: { { float vx=0,vy=0,vz=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o), a=1.0/pow(2.0,o); vx+=native_sin(f*zy+wph)*a; vy+=native_sin(f*zz2+wph)*a; vz+=native_sin(f*zx+wph)*a;} z.x+=wf*wam*vx; z.y+=wf*wam*vy; z.z+=wf*wam*vz; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq*4.0)); } break; }
						case 25: { { float vx=0,vy=0,vz=0; for(int o=0;o<(int)(wa);o++){float f=wfq*pow(wb,o), a=1.0/pow(wb,o); vx+=native_sin(f*zy+o*wph)*a; vy+=native_sin(f*zz2+o*wph)*a; vz+=native_sin(f*zx+o*wph)*a;} z.x+=wf*wam*vx; z.y+=wf*wam*vy; z.z+=wf*wam*vz; aux.DE*=(1.0+3.0*fabs(wf*wam)); } break; }
						case 26: { { float v=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o); v+=fabs(native_sin(f*zx+wph))*native_cos(f*zy)/pow(2.0,o);} z.x+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
						case 27: { { float vx=0,vy=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o); vx+=native_sin(f*zy+wph)*native_cos(f*zz2)/pow(2.0,o); vy+=native_cos(f*zx+wph)*native_sin(f*zz2)/pow(2.0,o);} z.x+=wf*wam*vx; z.y+=wf*wam*vy; aux.DE*=(1.0+2.0*fabs(wf*wam*wfq*4.0)); } break; }
						case 28: { { float v=0; for(int o=0;o<6;o++){float f=wfq*pow(2.0,o); v+=native_sin(f*r+wph)/pow(2.0,o);} float d=wf*wam*v; z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0+fabs(wf*wam*wfq*6.0)); } break; }
						case 29: { { float vx=0,vy=0,vz=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o), p=wph+o*M_PI_F*0.25; vx+=native_sin(f*zy+p)*native_cos(f*zz2+p)/pow(2.0,o); vy+=native_sin(f*zz2+p)*native_cos(f*zx+p)/pow(2.0,o); vz+=native_sin(f*zx+p)*native_cos(f*zy+p)/pow(2.0,o);} z.x+=wf*wam*vx; z.y+=wf*wam*vy; z.z+=wf*wam*vz; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq*4.0)); } break; }
						case 30: { { float ph2=atan2(zy,zx), th=acos(zz2/r), v=0; for(int o=0;o<4;o++){float f=wfq*pow(2.0,o); v+=native_sin(f*th+wph)*native_cos(f*ph2)/pow(2.0,o);} float d=wf*wam*v; z.x+=d*native_sin(th)*native_cos(ph2); z.y+=d*native_sin(th)*native_sin(ph2); z.z+=d*native_cos(th); aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
					default: break;
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
						case 11: { { float ang2 = atan2(zy, zx), n = fmax(1.0, sa), sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5;{ float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
						case 12: { { float ang2 = atan2(zy, zx), n = 3.0, sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; { float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
						case 13: { { float ang2 = atan2(zy, zx), n = 4.0, sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; { float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
						case 14: { { float ang2 = atan2(zy, zx), n = 5.0, sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; { float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
						case 15: { { float ang2 = atan2(zy, zx), n = 6.0, sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; { float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
						case 16: { { float ang2 = atan2(zy, zx), n = 8.0, sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; { float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
						case 17: { { float ang2 = atan2(zy, zx), n = 12.0, sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5; { float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
						case 18: { { float ang2 = atan2(zz2, zx), n = fmax(1.0, sa), sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5;{ float rxz = native_sqrt(zx*zx+zz2*zz2); z.x = rxz*native_cos(ang2); z.z = rxz*native_sin(ang2); } } break; }
						case 19: { { float ang2 = atan2(zz2, zy), n = fmax(1.0, sa), sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector) - sector*0.5;{ float ryz = native_sqrt(zy*zy+zz2*zz2); z.y = ryz*native_cos(ang2); z.z = ryz*native_sin(ang2); } } break; }
						case 20: { { float ang2 = atan2(zy, zx), n = fmax(1.0, sa), sector = 2.0*M_PI_F/n; ang2 = fmod(ang2 + 10.0*M_PI_F, sector); if(fmod(floor(ang2/sector), 2.0) > 0.5) ang2 = sector - fmod(ang2, sector); else ang2 = fmod(ang2, sector); ang2 -= sector*0.5;{ float rxy = native_sqrt(zx*zx+zy*zy); z.x = rxy*native_cos(ang2); z.y = rxy*native_sin(ang2); } } break; }
						case 21: { { float cs = native_cos(sang), sn = native_sin(sang), nx = zx*cs - zy*sn; z.y = zx*sn + zy*cs; z.x = fabs(nx); } break; }
						case 22: { { float cs = native_cos(sang), sn = native_sin(sang); z.x = fabs(zx); { float nx = zx*cs - zy*sn; z.y = zx*sn + zy*cs; z.x = nx; z.x = fabs(z.x); } } break; }
						case 23: { { if(z.x + z.y < soff) { float t = z.x; z.x = -z.y; z.y = -t; } float cs = native_cos(sang), sn = native_sin(sang), nx = zx*cs - zy*sn; z.y = zx*sn + zy*cs; z.x = nx; } break; }
						case 24: { { z.x = fabs(z.x); z.y = fabs(z.y); { float cs = native_cos(sang), sn = native_sin(sang); float nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; z.x = fabs(z.x); } } break; }
						case 25: { { z.x = fabs(z.x) + soff; z.y = fabs(z.y) + soff; { float cs = native_cos(sang), sn = native_sin(sang); float nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } } break; }
						case 26: { { for(int k=0; k<(int)(sa); k++) { z.x = fabs(z.x); z.y = fabs(z.y); float cs = native_cos(sang), sn = native_sin(sang); float nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } } break; }
						case 27: { { for(int k=0; k<(int)(sa); k++) { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); float cs = native_cos(sang+k*sb), sn = native_sin(sang+k*sb); float nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } } break; }
						case 28: { { float cs1 = native_cos(sang), sn1 = native_sin(sang), nx = zx*cs1 - zy*sn1; z.y = zx*sn1 + zy*cs1; z.x = nx; z.x = fabs(z.x); { float cs2 = native_cos(-sang), sn2 = native_sin(-sang); nx = z.x*cs2 - z.y*sn2; z.y = z.x*sn2 + z.y*cs2; z.x = nx; } } break; }
						case 29: { { z.x = fabs(z.x); if(z.x - z.y < 0) { float t = z.x; z.x = z.y; z.y = t; } z.y = fabs(z.y); { float cs = native_cos(sang), sn = native_sin(sang), nx = z.x*cs - z.z*sn; z.z = z.x*sn + z.z*cs; z.x = nx; } } break; }
						case 30: { { float n = fmax(2.0, sa); for(int k=0; k<(int)(n); k++) { float a = k * 2.0*M_PI_F/n, cs = native_cos(a), sn = native_sin(a), d = z.x*cs + z.y*sn; if(d < 0) { z.x -= 2.0*d*cs; z.y -= 2.0*d*sn; } } } break; }
					default: break;
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
						case 1: { aux.DE *= (1.0 + af * aa); break; }
						case 2: { aux.DE *= (1.0 + af * aa * native_sin(ab * r)); break; }
						case 3: { aux.DE *= (1.0 + af * aa * native_cos(ab * r)); break; }
						case 4: { aux.DE *= (1.0 + af * aa * native_exp(-ab * r)); break; }
						case 5: { aux.DE *= (1.0 + af * aa * native_exp(-ab * rr)); break; }
						case 6: { aux.DE *= (1.0 + af * aa * native_log(1.0 + ab * r)); break; }
						case 7: { aux.DE *= (1.0 + af * aa * tanh(ab * r)); break; }
						case 8: { aux.DE *= (1.0 + af * aa * native_sin(ab * zx) * native_cos(ac * zy)); break; }
						case 9: { aux.DE *= (1.0 + af * aa * native_sin(ab * zy) * native_cos(ac * zz2)); break; }
						case 10: { aux.DE *= (1.0 + af * aa * native_sin(ab * zz2) * native_cos(ac * zx)); break; }
						case 11: { aux.DE *= (1.0 + af * aa * (native_sin(ab*zx) + native_sin(ac*zy) + native_sin(ad*zz2)) / 3.0); break; }
						case 12: { aux.DE *= (1.0 + af * aa / (1.0 + ab * rr)); break; }
						case 13: { aux.DE *= (1.0 + af * aa * pow(r, ab - 1.0)); break; }
						case 14: { aux.DE *= (1.0 + af * aa * fabs(native_sin(ab * r))); break; }
						case 15: { aux.DE *= (1.0 + af * aa * (1.0 - native_exp(-ab * r))); break; }
						case 16: { { float sg = 1.0/(1.0+native_exp(-aa*(r-ab))); aux.DE *= (1.0 + af * sg); } break; }
						case 17: { aux.DE *= (1.0 + af * aa * native_sin(ab*zx)*native_sin(ac*zy)*native_sin(ad*zz2)); break; }
						case 18: { aux.DE *= (1.0 + af * aa * native_cos(ab*zx)*native_cos(ac*zy)*native_cos(ad*zz2)); break; }
						case 19: { aux.DE *= (1.0 + af * aa * native_sin(ab*r+ac*atan2(zy,zx))); break; }
						case 20: { aux.DE *= (1.0 + af * aa * native_sin(ab*r)*native_cos(ac*acos(zz2/r))); break; }
						case 21: { { float v = 0; for(int o=0;o<4;o++) v += native_sin(ab*pow(2.0,o)*r)/(pow(2.0,o)); aux.DE *= (1.0 + af * aa * v); } break; }
						case 22: { aux.DE *= (1.0 + af * aa * (zx*zy+zy*zz2+zz2*zx)/(rr+1e-21)); break; }
						case 23: { aux.DE *= (1.0 + af * aa * fabs(zx*zy*zz2)/(r*r*r+1e-21)); break; }
						case 24: { aux.DE *= (1.0 + af * aa * native_sin(ab*(zx*zx-zy*zy)/(rr+1e-21))); break; }
						case 25: { aux.DE *= (1.0 + af * aa * atan2(native_sqrt(zx*zx+zy*zy), zz2) / M_PI_F); break; }
						case 26: { { float rr2=rr; if(rr2<aa*aa) { float m=ab*ab/fmax(rr2,1e-21); aux.DE*=m; } aux.DE*=(1.0+af*0.1); } break; }
						case 27: { { float rr2=rr, mR2=aa*aa, fR2=ab*ab; if(rr2<mR2) aux.DE*=fR2/mR2; else if(rr2<fR2) aux.DE*=fR2/rr2; } break; }
						case 28: { aux.DE *= (1.0 + af * aa * native_exp(-ab*(r-ac)*(r-ac))); break; }
						case 29: { aux.DE *= (1.0 + af * aa * (1.0/(1.0+native_exp(-ab*(r-ac))) - 0.5)); break; }
						case 30: { aux.DE *= (1.0 + af * aa * native_sin(ab*r)*native_exp(-ac*r)); break; }
					default: break;
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
					case 1: { float h = native_sin(na*z.x*12.9898 + nb*z.y*78.233 + nc*z.z*45.164)*43758.5453; h = h - floor(h); aux.DE *= (1.0 + nf*h); break; }
					case 2: { float h1 = native_sin(na*z.x*12.9898 + z.y*78.233)*43758.5453; h1=h1-floor(h1); { float h2 = native_sin(z.y*12.9898 + na*z.z*78.233)*43758.5453; h2=h2-floor(h2); aux.DE *= (1.0 + nf*(h1+h2)*0.5); } break; }
					case 3: { float p = na*z.x + nb*z.y + nc*z.z, h = native_sin(p*127.1)*43758.5453; h=h-floor(h); { float h2 = native_sin(p*269.5)*43758.5453; h2=h2-floor(h2); aux.DE *= (1.0 + nf*fabs(h-h2)); } break; }
					case 4: { float fx = z.x*nfq, fy = z.y*nfq, fz = z.z*nfq, ix = floor(fx), iy = floor(fy), iz = floor(fz), tx = fx-ix, ty = fy-iy, tz = fz-iz, h000 = native_sin(ix*127.1+iy*311.7+iz*74.7)*43758.5453; h000=h000-floor(h000); { float h100 = native_sin((ix+1)*127.1+iy*311.7+iz*74.7)*43758.5453; h100=h100-floor(h100); float v = h000*(1.0-tx) + h100*tx; aux.DE *= (1.0 + nf*v); } break; }
					case 5: { float fx = z.x*nfq, fy = z.y*nfq, h00 = native_sin(floor(fx)*127.1+floor(fy)*311.7)*43758.5453; h00=h00-floor(h00); { float h10 = native_sin((floor(fx)+1)*127.1+floor(fy)*311.7)*43758.5453; h10=h10-floor(h10); float h01 = native_sin(floor(fx)*127.1+(floor(fy)+1)*311.7)*43758.5453; h01=h01-floor(h01); float h11 = native_sin((floor(fx)+1)*127.1+(floor(fy)+1)*311.7)*43758.5453; h11=h11-floor(h11); float tx=fx-floor(fx), ty=fy-floor(fy), v = h00*(1-tx)*(1-ty)+h10*tx*(1-ty)+h01*(1-tx)*ty+h11*tx*ty; aux.DE *= (1.0 + nf*v); } break; }
					case 6: { float h = native_sin(z.x*na*12.9898 + z.y*nb*78.233 + z.z*nc*45.164 + nd*i)*43758.5453; h=h-floor(h); h = h*h*(3.0-2.0*h); aux.DE *= (1.0 + nf*h); break; }
					case 7: { float h = native_sin(z.x*nfq + z.y*nfq*1.3 + z.z*nfq*0.7)*43758.5453; h=h-floor(h); h = 6.0*h*h*h*h*h - 15.0*h*h*h*h + 10.0*h*h*h; aux.DE *= (1.0 + nf*h); break; }
					case 8: { float p = na*z.x*nfq + nb*z.y*nfq + nc*z.z*nfq, h = native_sin(p)*0.5+0.5; aux.DE *= (1.0 + nf*h*h); break; }
					case 9: { float h1 = native_sin(z.x*nfq*12.9898)*43758.5453; h1=h1-floor(h1); { float h2 = native_sin(z.y*nfq*78.233)*43758.5453; h2=h2-floor(h2); float h3 = native_sin(z.z*nfq*45.164)*43758.5453; h3=h3-floor(h3); aux.DE *= (1.0 + nf*(h1*h2*h3)); } break; }
					case 10: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), h = native_sin(r*nfq)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h); break; }
					case 11: { float gx = native_sin(z.x*nfq*127.1+z.y*311.7)*2.0-1.0, gy = native_sin(z.y*nfq*269.5+z.z*183.3)*2.0-1.0, gz = native_sin(z.z*nfq*419.2+z.x*371.9)*2.0-1.0, v = (gx*z.x+gy*z.y+gz*z.z)*nam; aux.DE *= (1.0 + nf*native_sin(v)); break; }
					case 12: { float px = z.x*nfq, py = z.y*nfq, g1 = native_sin(floor(px)*127.1+floor(py)*311.7)*2.0-1.0, g2 = native_sin((floor(px)+1)*127.1+floor(py)*311.7)*2.0-1.0, t = px-floor(px); t = t*t*(3.0-2.0*t); { float v = g1*(1.0-t)+g2*t; aux.DE *= (1.0 + nf*v); } break; }
					case 13: { float px = z.x*nfq, py = z.y*nfq, pz = z.z*nfq, g = native_sin(px*127.1+py*311.7+pz*74.7)*2.0-1.0, t = g*g*(3.0-2.0*g); aux.DE *= (1.0 + nf*t*nam); break; }
					case 14: { float v = native_sin(z.x*nfq)*native_cos(z.y*nfq*1.3)*native_sin(z.z*nfq*0.7); aux.DE *= (1.0 + nf*v*nam); break; }
					case 15: { float v1 = native_sin(z.x*nfq+z.y*nfq*0.5), v2 = native_sin(z.y*nfq*1.3+z.z*nfq*0.7), v3 = native_sin(z.z*nfq*0.9+z.x*nfq*1.1); aux.DE *= (1.0 + nf*(v1+v2+v3)/3.0); break; }
					case 16: { float px = z.x*nfq, h = native_sin(px*12.9898+z.y*nfq*78.233)*43758.5453; h=h-floor(h); { float g = (h*2.0-1.0)*(px-floor(px)); aux.DE *= (1.0 + nf*g); } break; }
					case 17: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), th = atan2(z.y,z.x), v = native_sin(r*nfq+th*na)*nam; aux.DE *= (1.0 + nf*v); break; }
					case 18: { float v = native_sin(z.x*nfq)*native_sin(z.y*nfq)*native_sin(z.z*nfq); v = v*v*(3.0-2.0*v); aux.DE *= (1.0 + nf*v*nam); break; }
					case 19: { float dx = native_sin(z.x*nfq*12.9898)*2.0-1.0, dy = native_sin(z.y*nfq*78.233)*2.0-1.0, dz = native_sin(z.z*nfq*45.164)*2.0-1.0, v = native_sqrt(dx*dx+dy*dy+dz*dz); aux.DE *= (1.0 + nf*(v-1.0)*nam); break; }
					case 20: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), phi = atan2(z.y,z.x), theta = acos(z.z/fmax(r,1e-21)), v = native_sin(r*nfq)*native_cos(phi*na)*native_sin(theta*nb); aux.DE *= (1.0 + nf*v); break; }
					case 21: { float v=0, a=nam, f=nfq; for(int k=0;k<4;k++){ v += a*native_sin(z.x*f*12.9898+z.y*f*78.233+z.z*f*45.164); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 22: { float v=0, a=nam, f=nfq; for(int k=0;k<6;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 23: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*fabs(h*2.0-1.0); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 24: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*(1.0-fabs(h*2.0-1.0)); f*=na; a*=nb; } aux.DE *= (1.0 + nf*v); break; }
					case 25: { float v=0, a=nam, f=nfq, px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ float h=native_sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*h;float d=native_sin(px*f*269.5+py*f*183.3)*43758.5453; d=d-floor(d); px+=d*na; py+=d*nb; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 26: { float v=0, a=1.0, f=nfq, mx=0; for(int k=0;k<5;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; mx+=a; f*=2.0; a*=0.5; } v/=fmax(mx,1e-21); aux.DE *= (1.0 + nf*v*nam); break; }
					case 27: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h1=native_sin(z.x*f+z.y*f*1.3)*0.5+0.5;float h2=native_sin(z.y*f*0.7+z.z*f*1.1)*0.5+0.5; v+=a*fmin(h1,h2); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 28: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float h1=native_sin(z.x*f+z.y*f*1.3)*0.5+0.5;float h2=native_sin(z.y*f*0.7+z.z*f*1.1)*0.5+0.5; v+=a*fmax(h1,h2); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 29: { float v=0, a=nam, f=nfq, cs=native_cos(nd*M_PI_F/180.0), sn=native_sin(nd*M_PI_F/180.0), px=z.x,py=z.y; for(int k=0;k<5;k++){ float h=native_sin(px*f*127.1+py*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*h;float nx=px*cs-py*sn; py=px*sn+py*cs; px=nx; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 30: { float v=0, a=nam, f=nfq; for(int k=0;k<6;k++){ float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*native_sin(h*M_PI_F); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					case 31: { float v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ float r2=z.x*z.x+z.y*z.y+z.z*z.z;float h=native_sin(r2*f)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
					default: break;
				}
			}

			// v7.10 [GPU] — Orbit Trap DE system (per-section iteration range)
			if (i >= mut->orbitIterStart && i < mut->orbitIterStop && mut->orbitTrapType != 0)
			{
				float oa = mut->orbitParamA, ob = mut->orbitParamB, oc = mut->orbitParamC, od = mut->orbitParamD;
				float of = mut->orbitFactor * mut->orbitTrapWeight * mut->masterWeight;
				switch(mut->orbitTrapType) {
					case 1: { float d = native_sqrt((z.x-oa)*(z.x-oa)+(z.y-ob)*(z.y-ob)+(z.z-oc)*(z.z-oc)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 2: { float d = fabs(z.x-oa)+fabs(z.y-ob)+fabs(z.z-oc); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 3: { float d = fmax(fabs(z.x-oa),fmax(fabs(z.y-ob),fabs(z.z-oc))); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 4: { float d1=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), d2=native_sqrt((z.x-oa)*(z.x-oa)+(z.y-ob)*(z.y-ob)+(z.z-oc)*(z.z-oc)); aux.DE *= (1.0 + of*native_exp(-od*fmin(d1,d2))); break; }
					case 5: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), ring=fabs(d-oa); aux.DE *= (1.0 + of*native_exp(-od*ring)); break; }
					case 6: { float dx=z.x-oa*round(z.x/fmax(oa,1e-21)), dy=z.y-ob*round(z.y/fmax(ob,1e-21)), dz=z.z-oc*round(z.z/fmax(oc,1e-21)), d=native_sqrt(dx*dx+dy*dy+dz*dz); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 7: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), shell=fabs(d-oa), shell2=fabs(d-ob); aux.DE *= (1.0 + of*native_exp(-od*fmin(shell,shell2))); break; }
					case 8: { float ph=atan2(z.y,z.x), r=native_sqrt(z.x*z.x+z.y*z.y), spiral_r=oa+ob*ph/(2.0*M_PI_F), d=fabs(r-spiral_r); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 9: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), v=native_sin(d*oa*M_PI_F)*0.5+0.5; aux.DE *= (1.0 + of*v); break; }
					case 10: { int nn=(int)fmax(2,fmin(oa*6,12)); { float md=1e10; for(int k=0;k<nn;k++){ float ang=k*2.0*M_PI_F/nn;float cx=ob*native_cos(ang); float cy=ob*native_sin(ang); float d=(z.x-cx)*(z.x-cx)+(z.y-cy)*(z.y-cy)+z.z*z.z; if(d<md)md=d; } aux.DE *= (1.0 + of*native_exp(-od*native_sqrt(md))); } break; }
					case 11: { float d=z.x*z.x/(oa*oa+1e-21)+z.y*z.y/(ob*ob+1e-21)+z.z*z.z/(oc*oc+1e-21); d=fabs(native_sqrt(d)-1.0); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 12: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), th=atan2(z.y,z.x), d=fabs(r-oa*(1.0+ob*native_cos(oc*th))); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 13: { float r2=z.x*z.x+z.y*z.y+z.z*z.z, inv_r=oa*oa/fmax(r2,1e-21), d=fabs(inv_r-1.0)*native_sqrt(r2); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 14: { float d=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), s=native_sin(d*oa), c=native_cos(d*ob); aux.DE *= (1.0 + of*(s*s+c*c*0.5)*native_exp(-od*d)); break; }
					case 15: { float d=fabs(z.x*oa+z.y*ob+z.z*oc)/fmax(native_sqrt(oa*oa+ob*ob+oc*oc),1e-21); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 16: { float d=native_sqrt(z.y*z.y+z.z*z.z); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 17: { float d=native_sqrt(z.x*z.x+z.z*z.z); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 18: { float d=native_sqrt(z.x*z.x+z.y*z.y); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 19: { float d=fabs(z.x*oa+z.y*ob+z.z*oc-od); aux.DE *= (1.0 + of*native_exp(-d)); break; }
					case 20: { float d=fmin(fabs(z.x),fmin(fabs(z.y),fabs(z.z))); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 21: { float d1=fabs(z.x), d2=fabs(z.y), d3=fabs(z.z); aux.DE *= (1.0 + of*native_exp(-od*fmin(d1,d2))*native_exp(-od*d3)); break; }
					case 22: { float d=fmin(native_sqrt(z.x*z.x+z.y*z.y),native_sqrt(z.y*z.y+z.z*z.z)); d=fmin(d,native_sqrt(z.x*z.x+z.z*z.z)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 23: { float d1=fabs(z.x-oa), d2=fabs(z.y-ob), d3=fabs(z.z-oc), d=d1*d2*d3; aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 24: { float cs=native_cos(oa*M_PI_F/180.0),sn=native_sin(oa*M_PI_F/180.0), rx=z.x*cs-z.y*sn, ry=z.x*sn+z.y*cs, d=fabs(ry); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 25: { float d=fmin(fabs(z.x),fabs(z.y)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 26: { float d1=fabs(z.y-oa*z.x), d2=fabs(z.y+oa*z.x); aux.DE *= (1.0 + of*native_exp(-od*fmin(d1,d2))); break; }
					case 27: { float ph=atan2(z.y,z.x); int n=(int)fmax(3,fmin(oa,12)); { float seg=2.0*M_PI_F/n, sph=fmod(ph+M_PI_F,seg)-seg*0.5, r=native_sqrt(z.x*z.x+z.y*z.y), d=fabs(r*native_sin(sph)); aux.DE *= (1.0 + of*native_exp(-od*d)); } break; }
					case 28: { float d1=fabs(z.x*native_sin(oa*M_PI_F/180.0)-z.y*native_cos(oa*M_PI_F/180.0)), d2=fabs(z.x*native_sin(ob*M_PI_F/180.0)-z.y*native_cos(ob*M_PI_F/180.0)); aux.DE *= (1.0 + of*native_exp(-od*(d1+d2))); break; }
					case 29: { float d=fabs(z.z-oa*native_sin(ob*z.x)*native_cos(oc*z.y)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 30: { float r=native_sqrt(z.x*z.x+z.y*z.y), d=fabs(z.z-oa*native_sin(ob*r)); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					case 31: { float r=native_sqrt(z.x*z.x+z.y*z.y), d=fabs(r-oa); aux.DE *= (1.0 + of*native_exp(-od*d)); break; }
					default: break;
				}
			}

			// v7.12 [GPU] — MandelTorus DE system (per-section iteration range)
			if (i >= mut->torusIterStart && i < mut->torusIterStop && mut->torusType != 0)
			{
				float tf = mut->torusFactor * mut->torusWeight * mut->masterWeight;
				float ta = mut->torusParamA, tb = mut->torusParamB, tc = mut->torusParamC, td = mut->torusParamD;
				switch(mut->torusType) {
					case 1: { float k = ta, DE0 = tb; aux.DE = 1.0/(1.0 + native_exp(-k*(aux.DE - DE0))); break; }
					case 2: { float DE0 = ta, sigma = fmax(fabs(tb), 0.01); aux.DE *= native_exp(-(aux.DE-DE0)*(aux.DE-DE0)/(sigma*sigma)); break; }
					case 3: { float threshold = ta, DE_max = fabs(tb)+1.0, DE_min = fabs(tc)*0.01; aux.DE = (aux.DE > threshold) ? DE_max : DE_min; break; }
					case 4: { float b1=ta, b2=tb, d1=fabs(tc),d2=fabs(td); if(aux.DE<b1) aux.DE=d1; else if(aux.DE<b2) aux.DE=d2; break; }
					case 5: { float h = native_sin(z.x*127.1+z.y*311.7+z.z*74.7)*43758.5453; h=h-floor(h); aux.DE += tf*(h*2.0-1.0)*ta; break; }
					case 6: { float jx=z.x*z.x-z.y*z.y+ta, jy=2.0*z.x*z.y+tb, julia_mag=native_sqrt(jx*jx+jy*jy); aux.DE *= (1.0 + tf*0.1*julia_mag); break; }
					case 7: { aux.DE *= (1.0 + tf*0.1*native_sin(ta*(float)i*0.1)); break; }
					case 8: { float alpha=fmin(fmax(ta,0.01),0.99); aux.DE = alpha*aux.DE + (1.0-alpha)*tb; break; }
					case 9: { float h1=native_sin(ta*z.x+tb*z.y+tc*z.z), h2=native_sin(td*h1+ta*aux.DE); aux.DE *= (1.0 + tf*h2); break; }
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
					case 27: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), view_dot = z.z/fmax(r,1e-21), fresnel = pow(fmax(1.0-fabs(view_dot),0.0), ta); aux.DE *= (1.0 + tf*fresnel*tb); break; }
					case 28: { float thin_film = native_sin(ta*native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*M_PI_F*2.0); aux.DE *= (1.0 + tf*thin_film*thin_film*tb); break; }
					case 29: { float tangent_dot = fabs(z.x*native_cos(ta)+z.y*native_sin(ta))/fmax(native_sqrt(z.x*z.x+z.y*z.y),1e-21); aux.DE *= (1.0 + tf*tangent_dot*tb); break; }
					case 30: { float subdiv = fmax(1.0, floor(ta*(float)i*0.1+1.0)); aux.DE /= subdiv*tf+1.0; break; }
					case 31: { float dist = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), lod = fmin(dist*ta, tb); aux.DE *= (1.0 + tf*lod); break; }
					default: break;
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
						case 1: { float k = ta, DE0_1 = tb; aux.DE = 1.0/(1.0 + native_exp(-k*(aux.DE - DE0_1))); break; }
						case 2: { float DE0_2 = ta, sigma2 = fmax(fabs(tb), 0.01f); aux.DE *= native_exp(-(aux.DE-DE0_2)*(aux.DE-DE0_2)/(sigma2*sigma2)); break; }
						case 3: { float threshold3 = ta, DE_max3 = fabs(tb)+1.0f, DE_min3 = fabs(tc)*0.01f; aux.DE = (aux.DE > threshold3) ? DE_max3 : DE_min3; break; }
						case 4: { float b1_4=ta, b2_4=tb, d1_4=fabs(tc), d2_4=fabs(td); if(aux.DE<b1_4) aux.DE=d1_4; else if(aux.DE<b2_4) aux.DE=d2_4; break; }
						case 5: { float h = native_sin(z.x*127.1+z.y*311.7+z.z*74.7)*43758.5453; h=h-floor(h); aux.DE += sf*(h*2.0-1.0)*ta; break; }
						case 6: { float jx6=z.x*z.x-z.y*z.y+ta, jy6=2.0f*z.x*z.y+tb, julia_mag6=native_sqrt(jx6*jx6+jy6*jy6); aux.DE *= (1.0f + sf*0.1f*julia_mag6); break; }
						case 7: { aux.DE *= (1.0 + sf*0.1*native_sin(ta*(float)i*0.1)); break; }
						case 8: { float alpha=fmin(fmax(ta,0.01),0.99); aux.DE = alpha*aux.DE + (1.0-alpha)*tb; break; }
						case 9: { float h1_9=native_sin(ta*z.x+tb*z.y+tc*z.z), h2_9=native_sin(td*h1_9+ta*aux.DE); aux.DE *= (1.0f + sf*h2_9); break; }
						case 10: { float v=0,f=ta,a=1.0; for(int k=0;k<4;k++){float h=native_sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453;h=h-floor(h);v+=a*h;f*=2.0;a*=0.5;} aux.DE *= (1.0 + sf*0.1*v); break; }
						case 11: { float speed = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE /= (1.0 + sf*speed*ta); break; }
						case 12: { float sc = fabs(ta) + 0.01; aux.DE *= sc; break; }
						case 13: { float angle = atan2(z.y,z.x); aux.DE *= (1.0 + sf*fabs(angle)*ta/M_PI_F); break; }
						case 14: { float shear = fabs(z.x*z.y*ta) + fabs(z.y*z.z*tb) + fabs(z.z*z.x*tc); aux.DE *= (1.0 + sf*shear); break; }
						case 15: { float progress = (float)i / fmax((float)(i+10), 1.0f); aux.DE *= (1.0f + sf*(1.0f-progress)*ta); break; }
						case 16: { float box = fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z))); if(box > fabs(ta)) aux.DE *= (1.0 + sf*tb); break; }
						case 17: { float d = native_sqrt((z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc)); if(d < fabs(td)) aux.DE *= (1.0 + sf); break; }
						case 18: { float w = fabs(ta)+0.01; if(fabs(z.x)<w && fabs(z.y)<w) aux.DE *= (1.0 + sf*tb); break; }
						case 19: { float intensity = native_sin(z.x*ta)*native_sin(z.y*tb)*native_sin(z.z*tc); aux.DE *= (1.0 + sf*0.1*intensity*intensity); break; }
						case 20: { float ao = 1.0/(1.0 + (float)i*ta*0.01); aux.DE *= (1.0 - sf*ao*fabs(tb)); break; }
						case 21: { float gi = native_sin(z.x*ta+z.y*tb)*0.5+0.5; aux.DE /= (1.0 + sf*gi*fabs(tc)); break; }
						case 22: { float depth = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0 + sf*ta*depth); break; }
						case 23: { float light_accum = native_sin(z.x*ta)*native_sin(z.y*ta)*0.5+0.5; aux.DE /= (1.0 + sf*light_accum*tb); break; }
						case 24: { float ss_depth = native_exp(-fabs(ta)*native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)); aux.DE *= (1.0 + sf*ss_depth*tb); break; }
						case 25: { float wl_diff = fabs(z.x*ta - tb); aux.DE *= (1.0 + sf*tc*wl_diff); break; }
						case 26: { float caustic = native_sin(z.x*ta*10.0)*native_sin(z.y*tb*10.0); aux.DE *= (1.0 + sf*caustic*caustic*tc); break; }
						case 27: { float r27 = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), view_dot27 = z.z/fmax(r27,1e-21f), fresnel27 = pow(fmax(1.0f-fabs(view_dot27),0.0f), ta); aux.DE *= (1.0f + sf*fresnel27*tb); break; }
						case 28: { float thin_film = native_sin(ta*native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*M_PI_F*2.0); aux.DE *= (1.0 + sf*thin_film*thin_film*tb); break; }
						case 29: { float tangent_dot = fabs(z.x*native_cos(ta)+z.y*native_sin(ta))/fmax(native_sqrt(z.x*z.x+z.y*z.y),1e-21); aux.DE *= (1.0 + sf*tangent_dot*tb); break; }
						case 30: { float subdiv = fmax(1.0, fabs(ta)); aux.DE /= (1.0 + sf*subdiv*tb); break; }
						case 31: { float dist31 = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), lod31 = fmax(0.1f, dist31*ta); aux.DE *= lod31; break; }
					default: break;
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
						case 1: { float branch = 2.0 + floor(3.0*native_sin((float)i*ta*0.1)); aux.DE *= fmax(branch*tb, 0.01); break; }
						case 2: { float bx=fmax(ta,1.0),by=fmax(tb,1.0),bz=fmax(tc,1.0); aux.DE *= fmax(fmax(bx,by),bz)*sf; break; }
						case 3: { float angle = (float)i * 2.39996322972865332 * ta, cosA=native_cos(angle),sinA=native_sin(angle), nx=z.x*cosA-z.y*sinA; z.y=z.x*sinA+z.y*cosA; z.x=nx; break; }
						case 4: { float jm = native_sin(z.x*ta)*native_cos(z.y*tb), r_ratio = 1.0 + sf*0.3*jm; aux.DE *= r_ratio; break; }
						case 5: { float h = native_sin(z.x*ta*127.1+z.y*ta*311.7+z.z*ta*74.7)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + sf*(h*2.0-1.0)*tb); break; }
						case 6: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), d1 = r - ta, d2 = r - tb; aux.DE *= (1.0 + sf*native_exp(-fmin(d1*d1,d2*d2)*tc)); break; }
						case 7: { float w = fabs(ta)+0.01, wd = w*native_sin(z.x*tb)*native_cos(z.y*tc); aux.DE *= (1.0 + sf*wd*td); break; }
						case 8: { float ax=fmax(fabs(ta),0.01),ay=fmax(fabs(tb),0.01),az=fmax(fabs(tc),0.01), ell = native_sqrt((z.x/ax)*(z.x/ax)+(z.y/ay)*(z.y/ay)+(z.z/az)*(z.z/az))-1.0; aux.DE *= (1.0 + sf*native_exp(-ell*ell*td)); break; }
						case 9: { float r2d = native_sqrt(z.x*z.x+z.y*z.y), R=fabs(ta)+0.1,r=fabs(tb)+0.01, td2 = (r2d-R)*(r2d-R)+z.z*z.z-r*r; aux.DE *= (1.0 + sf*native_exp(-fabs(td2)*tc)); break; }
						case 10: { float px=z.x,py=z.y,pz=z.z, seg_d=fabs(pz)-fabs(ta), cap_d=native_sqrt(px*px+py*py+fmax(seg_d,0.0)*fmax(seg_d,0.0))-fabs(tb); aux.DE *= (1.0 + sf*native_exp(-cap_d*cap_d*tc)); break; }
						case 11: { float theta=atan2(z.y,z.x), phi2=acos(z.z/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),1e-21)), m=fmax(ta,1.0), sf_r=pow(fmax(pow(fabs(native_cos(m*theta/4.0)),tc)+pow(fabs(native_sin(m*theta/4.0)),tc),1e-21),-1.0/fmax(tb,0.1)), r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0 + sf*native_exp(-fabs(r-sf_r*td)*5.0)); break; }
						case 12: { float jx=z.x*z.x-z.y*z.y+ta, jy=2.0*z.x*z.y+tb; z.x=jx; z.y=jy; aux.DE *= 2.0*native_sqrt(jx*jx+jy*jy); break; }
						case 13: { float mx=z.x*z.x-z.y*z.y+z.x, my=2.0*z.x*z.y+z.y; z.x=mx; z.y=my; aux.DE *= 2.0*native_sqrt(mx*mx+my*my); break; }
						case 14: { float a1=ta*M_PI_F/180.0, a2=tb*M_PI_F/180.0, ca1=native_cos(a1),sa1=native_sin(a1), newx=z.x+z.x*ca1-z.y*sa1, newy=z.y+z.x*sa1+z.y*ca1; z.x=newx*0.5; z.y=newy*0.5; z.z*=tc; aux.DE *= fabs(tc); break; }
						case 15: { float r = native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), koch_amp = ta*native_sin(r*tb*10.0); aux.DE *= (1.0 + sf*koch_amp*koch_amp); break; }
						case 16: { float scale4 = fabs(ta)+1.0; if(z.x+z.y<0.0){float t=z.x;z.x=-z.y;z.y=-t;} if(z.x+z.z<0.0){float t=z.x;z.x=-z.z;z.z=-t;} if(z.y+z.z<0.0){float t=z.y;z.y=-z.z;z.z=-t;} z = z*scale4 - (float4)(1,1,1,0.0f)*(scale4-1.0)*tb; aux.DE = aux.DE*scale4+1.0; break; }
						case 17: { float r17=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), mde17; if(r17<1e-21f)r17=1e-21f; mde17=ta*ta/r17/r17; z*=mde17; aux.DE*=mde17; break; }
						case 18: { float h=native_sin(z.x*ta*12.9898+z.y*tb*78.233+z.z*tc*45.164)*43758.5453; h=h-floor(h); z.x+=h*td*0.1; z.y+=(1.0-h)*td*0.1; break; }
						case 19: { float min_dist=fabs(ta)+0.1, h=native_sin(z.x*12.9898+z.y*78.233)*43758.5453; h=h-floor(h); z.x=floor(z.x/min_dist+h)*min_dist; z.y=floor(z.y/min_dist+h)*min_dist; break; }
						case 20: { float h=native_sin(z.x*12.9898+z.y*78.233+z.z*45.164)*43758.5453; h=fabs(h-floor(h)); z.x+=h*ta*0.1; z.y+=(1.0-h)*tb*0.1; z.z+=fabs(native_sin(h*tc))*td*0.1; break; }
						case 21: { float theta = (float)i * 2.39996322972865332, r = native_sqrt((float)i+0.5)*ta; z.x += r*native_cos(theta)*sf*0.1; z.y += r*native_sin(theta)*sf*0.1; break; }
						case 22: { float phi3 = 1.6180339887, r_n = ta/pow(phi3, (float)i); aux.DE *= 1.0/phi3; z *= r_n/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),0.01); break; }
						case 23: { float r_n = ta * native_exp(-(float)i * fabs(tb)); aux.DE *= native_exp(-fabs(tb)); z *= r_n/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),0.01); break; }
						case 24: { float n = fmax((float)(i)+1.0f, 1.0f), r_n = ta / (1.0 + native_log(n)*tb); aux.DE *= 1.0/(1.0+native_log(n)*tb); z *= r_n/fmax(native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z),0.01); break; }
						case 25: { float n = fmax((float)(i)+1.0f, 1.0f), p = fmax(fabs(ta), 0.1f); aux.DE *= 1.0f/native_powr(n,p); break; }
						case 26: { float sc = 3.0 + 0.5*native_sin((float)i*ta); z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0.0f)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }
						case 27: { float sx=fmax(ta,1.0),sy=fmax(tb,1.0),sz=fmax(tc,1.0); z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z.x=z.x*sx-(sx-1.0); z.y=z.y*sy-(sy-1.0); z.z=z.z*sz-(sz-1.0); aux.DE=aux.DE*fmax(fmax(sx,sy),sz)+1.0; break; }
						case 28: { float h28=native_sin(z.x*ta*127.1+z.y*ta*311.7+z.z*ta*74.7)*43758.5453, sc28=3.0f; h28=h28-floor(h28); z=fabs(z)+(float4)(h28*tb,h28*tb,h28*tb,0.0f)*0.1f; if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc28-(float4)(1,1,1,0.0f)*(sc28-1.0f); aux.DE=aux.DE*sc28+1.0f; break; }
						case 29: { float angle29=ta*M_PI_F/180.0f, ca29=native_cos(angle29),sa29=native_sin(angle29), nx29=z.x*ca29-z.y*sa29, ny29=z.x*sa29+z.y*ca29, sc29=3.0f; z.x=fabs(nx29);z.y=fabs(ny29);z.z=fabs(z.z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*sc29-(float4)(1,1,1,0.0f)*(sc29-1.0f); aux.DE=aux.DE*sc29+1.0f; break; }
						case 30: { float eps30=fmax(fabs(ta),0.01f), sc30=3.0f, t30=0.0f; z.x=fabs(z.x);z.y=fabs(z.y);z.z=fabs(z.z); if(z.x<z.y){t30=z.x+(z.y-z.x)*0.5f*(1.0f+tanh((z.y-z.x)/eps30));z.y=z.y-(z.y-z.x)*0.5f*(1.0f+tanh((z.y-z.x)/eps30));z.x=z.y;z.y=t30;} if(z.x<z.z){t30=z.x;z.x=z.z;z.z=t30;} if(z.y<z.z){t30=z.y;z.y=z.z;z.z=t30;} z=z*sc30-(float4)(1,1,1,0.0f)*(sc30-1.0f); aux.DE=aux.DE*sc30+1.0f; break; }
						case 31: { float sc=3.0; z=fabs(z); if(z.x-z.y<0.0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){float t=z.y;z.y=z.z;z.z=t;} z=z*sc-(float4)(1,1,1,0.0f)*(sc-1.0)+(float4)(ta,tb,tc,0.0f); aux.DE=aux.DE*sc+1.0; break; }
					default: break;
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
						case 1: { float grid = fmax(fabs(ta), 0.01f); z.x = floor(z.x/grid)*grid; z.y = floor(z.y/grid)*grid; z.z = floor(z.z/grid)*grid; break; }
						case 2: { float grid = fmax(fabs(ta), 0.01f); z.x = floor(z.x/grid+0.5f)*grid; z.y = floor(z.y/grid+0.5f)*grid; z.z = floor(z.z/grid+0.5f)*grid; break; }
						case 3: { float grid3b = fmax(fabs(ta), 0.01f), qx3=z.x-grid3b*floor(z.x/grid3b), qy3=z.y-grid3b*floor(z.y/grid3b), qz3=z.z-grid3b*floor(z.z/grid3b), d3b=fmin(fmin(fmin(qx3,grid3b-qx3),fmin(qy3,grid3b-qy3)),fmin(qz3,grid3b-qz3)); aux.DE = fmin(aux.DE, d3b*sf); break; }
						case 4: { float grid4b = fmax(fabs(ta), 0.01f), blend4b=fmin(fmax(tb,0.0f),1.0f), sx4=floor(z.x/grid4b+0.5f)*grid4b, sy4=floor(z.y/grid4b+0.5f)*grid4b, sz4=floor(z.z/grid4b+0.5f)*grid4b; z.x=z.x*(1.0f-blend4b)+sx4*blend4b; z.y=z.y*(1.0f-blend4b)+sy4*blend4b; z.z=z.z*(1.0f-blend4b)+sz4*blend4b; break; }
						case 5: { float grid5b = fmax(fabs(ta), 0.01f), r5b=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), cur5b=r5b; r5b=floor(r5b/grid5b+0.5f)*grid5b; if(cur5b>0.001f){z.x*=r5b/cur5b;z.y*=r5b/cur5b;z.z*=r5b/cur5b;} break; }
						case 6: { float grid6b = fmax(fabs(ta), 0.01f), off6b=tb; z.x = floor((z.x+off6b)/grid6b)*grid6b-off6b; z.y = floor((z.y+off6b)/grid6b)*grid6b-off6b; z.z = floor((z.z+off6b)/grid6b)*grid6b-off6b; break; }
						case 7: { float gx7=fmax(fabs(ta),0.01f),gy7=fmax(fabs(tb),0.01f),gz7=fmax(fabs(tc),0.01f); z.x=floor(z.x/gx7+0.5f)*gx7; z.y=floor(z.y/gy7+0.5f)*gy7; z.z=floor(z.z/gz7+0.5f)*gz7; break; }
						case 8: { float grid8b=fmax(fabs(ta),0.01f), t8b=fmin(fmax(sf,0.0f),1.0f), progress8b=(float)i/fmax((float)(i+10),1.0f), blend8b=t8b*progress8b, sx8=floor(z.x/grid8b+0.5f)*grid8b, sy8=floor(z.y/grid8b+0.5f)*grid8b, sz8=floor(z.z/grid8b+0.5f)*grid8b; z.x=z.x*(1.0f-blend8b)+sx8*blend8b; z.y=z.y*(1.0f-blend8b)+sy8*blend8b; z.z=z.z*(1.0f-blend8b)+sz8*blend8b; break; }
						default: break;
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
						case 1: { float period = fmax(fabs(ta), 0.01f); z.x = z.x - period*floor(z.x/period+0.5f); z.y = z.y - period*floor(z.y/period+0.5f); z.z = z.z - period*floor(z.z/period+0.5f); break; }
						case 2: { float px=fmax(fabs(ta),0.01f),py=fmax(fabs(tb),0.01f),pz=fmax(fabs(tc),0.01f); z.x=z.x-px*floor(z.x/px+0.5f); z.y=z.y-py*floor(z.y/py+0.5f); z.z=z.z-pz*floor(z.z/pz+0.5f); break; }
						case 3: { float period=fmax(fabs(ta),0.01f); z.x=fabs(z.x)-period*floor(fabs(z.x)/period); z.y=fabs(z.y)-period*floor(fabs(z.y)/period); z.z=fabs(z.z)-period*floor(fabs(z.z)/period); break; }
						case 4: { float period4=fmax(fabs(ta),0.01f), half4=period4*0.5f; z.x=fmod(z.x+half4,period4)-half4; z.y=fmod(z.y+half4,period4)-half4; z.z=fmod(z.z+half4,period4)-half4; break; }
						case 5: { float period5=fmax(fabs(ta),0.01f), r5t=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z), cur5=r5t; r5t=fmod(r5t,period5); if(cur5>0.001f){z.x*=r5t/cur5;z.y*=r5t/cur5;z.z*=r5t/cur5;} break; }
						case 6: { float angle6=atan2(z.y,z.x), period6=fmax(fabs(ta),0.01f)*M_PI_F/180.0f, rr6=native_sqrt(z.x*z.x+z.y*z.y); angle6=fmod(angle6+period6*0.5f,period6)-period6*0.5f; z.x=rr6*native_cos(angle6); z.y=rr6*native_sin(angle6); break; }
						case 7: { float period7=fmax(fabs(ta),0.01f), blend7=fmin(fmax(tb,0.0f),1.0f), tx7=z.x-period7*floor(z.x/period7+0.5f), ty7=z.y-period7*floor(z.y/period7+0.5f), tz7=z.z-period7*floor(z.z/period7+0.5f); z.x=z.x*(1.0f-blend7)+tx7*blend7; z.y=z.y*(1.0f-blend7)+ty7*blend7; z.z=z.z*(1.0f-blend7)+tz7*blend7; break; }
						case 8: { float period8=fmax(fabs(ta),0.01f), fix8=(float)(int)floor(z.x/period8), fiy8=(float)(int)floor(z.y/period8); z.x=z.x-period8*floor(z.x/period8+0.5f); z.y=z.y-period8*floor(z.y/period8+0.5f); z.z=z.z-period8*floor(z.z/period8+0.5f); if(((int)fix8+(int)fiy8)%2!=0){z.x=-z.x;z.y=-z.y;} break; }
						default: break;
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
case 1: { z.x=fmax(fmin(z.x,ta),-ta); z.y=fmax(fmin(z.y,ta),-ta); z.z=fmax(fmin(z.z,ta),-ta); aux.DE*=sf; break; }
						case 2: { z.x=ta*tanh(z.x/fmax(ta,1e-10)); z.y=ta*tanh(z.y/fmax(ta,1e-10)); z.z=ta*tanh(z.z/fmax(ta,1e-10)); aux.DE*=sf; break; }
						case 3: { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(r>ta){float s=ta/r; z*=s; aux.DE*=s*sf;} break; }
						case 4: { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<ta*ta){float s=ta*ta/fmax(r2,1e-21); z*=s; aux.DE*=s;} break; }
						case 5: { if(z.x>ta)z.x=2.0f*ta-z.x; if(z.x<-ta)z.x=-2.0f*ta-z.x; if(z.y>ta)z.y=2.0f*ta-z.y; if(z.y<-ta)z.y=-2.0f*ta-z.y; if(z.z>ta)z.z=2.0f*ta-z.z; if(z.z<-ta)z.z=-2.0f*ta-z.z; break; }
						case 6: { z.x=fmax(fmin(z.x,ta),-tb); z.y=fmax(fmin(z.y,ta),-tb); z.z=fmax(fmin(z.z,ta),-tb); break; }
						case 7: { z.x=fmax(fmin(z.x,ta),-ta); z.y=fmax(fmin(z.y,tb),-tb); z.z=fmax(fmin(z.z,tc),-tc); break; }
						case 8: { float lim=ta*(1.0f+tb*(float)i/250.0f); z.x=fmax(fmin(z.x,lim),-lim); z.y=fmax(fmin(z.y,lim),-lim); z.z=fmax(fmin(z.z,lim),-lim); break; }
						case 9: { float lim=ta*fabs(native_sin(tb*(float)i)); z.x=fmax(fmin(z.x,fmax(lim,0.01f)),-fmax(lim,0.01f)); z.y=fmax(fmin(z.y,fmax(lim,0.01f)),-fmax(lim,0.01f)); z.z=fmax(fmin(z.z,fmax(lim,0.01f)),-fmax(lim,0.01f)); break; }
						case 10: { float lim=ta*native_exp(-tb*(float)i/100.0f); z.x=fmax(fmin(z.x,fmax(lim,0.01f)),-fmax(lim,0.01f)); z.y=fmax(fmin(z.y,fmax(lim,0.01f)),-fmax(lim,0.01f)); z.z=fmax(fmin(z.z,fmax(lim,0.01f)),-fmax(lim,0.01f)); break; }
						case 11: { float k=fmax(tb,0.01f); z.x=z.x-fmax(0.0f,fmin(1.0f,0.5f+(z.x-ta)/(2.0f*k)))*(z.x-ta); z.y=z.y-fmax(0.0f,fmin(1.0f,0.5f+(z.y-ta)/(2.0f*k)))*(z.y-ta); z.z=z.z-fmax(0.0f,fmin(1.0f,0.5f+(z.z-ta)/(2.0f*k)))*(z.z-ta); break; }
						case 12: { if(fabs(z.x)>ta){float s=z.x>0?1:-1; z.x=s*(ta-(z.x-s*ta)*(z.x-s*ta)*tb);} if(fabs(z.y)>ta){float s=z.y>0?1:-1; z.y=s*(ta-(z.y-s*ta)*(z.y-s*ta)*tb);} if(fabs(z.z)>ta){float s=z.z>0?1:-1; z.z=s*(ta-(z.z-s*ta)*(z.z-s*ta)*tb);} break; }
						case 13: { float rxy=native_sqrt(z.x*z.x+z.y*z.y); if(rxy>ta){float s=ta/rxy; z.x*=s; z.y*=s; aux.DE*=s;} break; }
						case 14: { float rxy=native_sqrt(z.x*z.x+z.y*z.y), lim=ta+tb*fabs(z.z); if(rxy>lim){float s=lim/rxy; z.x*=s; z.y*=s; aux.DE*=s;} break; }
						case 15: { float d=native_sqrt((z.x/fmax(ta,0.01f))*(z.x/fmax(ta,0.01f))+(z.y/fmax(tb,0.01f))*(z.y/fmax(tb,0.01f))+(z.z/fmax(tc,0.01f))*(z.z/fmax(tc,0.01f))); if(d>1.0f){z/=d; aux.DE/=d;} break; }
						case 16: { float rxy=native_sqrt(z.x*z.x+z.y*z.y)-ta, dt=native_sqrt(rxy*rxy+z.z*z.z); if(dt>tb){float s=tb/dt; rxy*=s; z.z*=s;float newR=rxy+ta; if(native_sqrt(z.x*z.x+z.y*z.y)>1e-10){float scale=newR/native_sqrt(z.x*z.x+z.y*z.y); z.x*=scale; z.y*=scale;} aux.DE*=s;} break; }
						case 17: { if(z.x>ta) z.x=ta; break; }
						case 18: { if(z.x<-ta) z.x=-ta; break; }
						case 19: { if(z.z>ta) z.z=ta; break; }
						case 20: { float p=fmax(ta,0.1f); z.x=fmod(z.x+p,2.0f*p)-p; z.y=fmod(z.y+p,2.0f*p)-p; z.z=fmod(z.z+p,2.0f*p)-p; break; }
						case 21: { float p=fmax(ta,0.1f); z.x=2.0f*fabs(z.x/(2.0f*p)-floor(z.x/(2.0f*p)+0.5f))*p; z.y=2.0f*fabs(z.y/(2.0f*p)-floor(z.y/(2.0f*p)+0.5f))*p; z.z=2.0f*fabs(z.z/(2.0f*p)-floor(z.z/(2.0f*p)+0.5f))*p; break; }
						case 22: { z.x=ta*(2.0f/(1.0f+native_exp(-2.0f*z.x/fmax(ta,0.01f)))-1.0f); z.y=ta*(2.0f/(1.0f+native_exp(-2.0f*z.y/fmax(ta,0.01f)))-1.0f); z.z=ta*(2.0f/(1.0f+native_exp(-2.0f*z.z/fmax(ta,0.01f)))-1.0f); break; }
						case 23: { z.x=ta*atan(z.x/fmax(ta,0.01f))*(2.0f/M_PI_F); z.y=ta*atan(z.y/fmax(ta,0.01f))*(2.0f/M_PI_F); z.z=ta*atan(z.z/fmax(ta,0.01f))*(2.0f/M_PI_F); break; }
						case 24: { float k24=1.0f/fmax(ta,0.01f); z.x=ta*tanh(k24*z.x*1.128f); z.y=ta*tanh(k24*z.y*1.128f); z.z=ta*tanh(k24*z.z*1.128f); break; }
						case 25: { float p25=fmax(tb,0.1f); if(fabs(z.x)>ta)z.x=z.x>0?ta*pow(ta/z.x,p25):-ta*pow(ta/fabs(z.x),p25); if(fabs(z.y)>ta)z.y=z.y>0?ta*pow(ta/z.y,p25):-ta*pow(ta/fabs(z.y),p25); if(fabs(z.z)>ta)z.z=z.z>0?ta*pow(ta/z.z,p25):-ta*pow(ta/fabs(z.z),p25); break; }
						case 26: { float lim26=ta*(1.0f+tb*native_sin(aux.color*tc)); z.x=fmax(fmin(z.x,lim26),-lim26); z.y=fmax(fmin(z.y,lim26),-lim26); z.z=fmax(fmin(z.z,lim26),-lim26); break; }
						case 27: { float lim27=ta*(1.0f+tb*native_log(1.0f+fabs(aux.DE))); z.x=fmax(fmin(z.x,lim27),-lim27); z.y=fmax(fmin(z.y,lim27),-lim27); z.z=fmax(fmin(z.z,lim27),-lim27); break; }
						case 28: { float lim28=ta+tb*z.x; z.y=fmax(fmin(z.y,fabs(lim28)),-fabs(lim28)); z.z=fmax(fmin(z.z,fabs(lim28)),-fabs(lim28)); break; }
						case 29: { float theta29=atan2(z.y,z.x), r29=native_sqrt(z.x*z.x+z.y*z.y); if(r29>ta){r29=ta; z.x=r29*native_cos(theta29); z.y=r29*native_sin(theta29); aux.DE*=ta/fmax(native_sqrt(z.x*z.x+z.y*z.y),1e-10);} break; }
						case 30: { float p30=fmax(ta,0.1f); z.x=floor(z.x/p30+0.5f)*p30; z.y=floor(z.y/p30+0.5f)*p30; z.z=floor(z.z/p30+0.5f)*p30; break; }
						case 31: { float r31=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(r31<ta&&r31>1e-15){float s=ta/r31; z*=s; aux.DE*=s;} break; }
						case 32: { float r32=native_sqrt(z.x*z.x+z.y*z.y); if(r32>ta&&r32<tb){}else if(r32<=ta){float s=ta/fmax(r32,1e-10); z.x*=s; z.y*=s;} else{float s=tb/r32; z.x*=s; z.y*=s;} break; }
						case 33: { float n33=native_sin(z.x*12.9898f+z.y*78.233f+z.z*45.164f)*43758.5453f; n33=n33-floor(n33); { float lim33=ta*(1.0f+tb*(n33-0.5f)); z.x=fmax(fmin(z.x,lim33),-lim33); z.y=fmax(fmin(z.y,lim33),-lim33); z.z=fmax(fmin(z.z,lim33),-lim33); } break; }
						case 34: { float theta34=atan2(z.y,z.x), r34=native_sqrt(z.x*z.x+z.y*z.y), spiralLim=ta+tb*theta34/(2.0f*M_PI_F); if(r34>spiralLim){z.x*=spiralLim/r34; z.y*=spiralLim/r34;} break; }
						case 35: { float waveLim=ta+tb*native_sin(tc*z.x)*native_sin(tc*z.y); z.z=fmax(fmin(z.z,waveLim),-waveLim); break; }
						case 36: { if(fabs(z.x)>ta){float t=z.x; z.x=z.y; z.y=t;} if(fabs(z.y)>ta){float t=z.y; z.y=z.z; z.z=t;} break; }
						case 37: { if(z.x>ta)z.x=2.0f*ta-z.x; if(z.y>ta)z.y=2.0f*ta-z.y; if(z.z>ta)z.z=2.0f*ta-z.z; break; }
						case 38: { float p38=fmax(2.0f*ta,0.01f); z.x=fabs(fmod(z.x+ta,p38)-ta); z.y=fabs(fmod(z.y+ta,p38)-ta); z.z=fabs(fmod(z.z+ta,p38)-ta); break; }
						case 39: { float s39=z.x>0?1:-1; z.x=s39*fmin(fabs(z.x),ta*native_log(1.0f+fabs(z.x)/fmax(ta,0.01f))); s39=z.y>0?1:-1; z.y=s39*fmin(fabs(z.y),ta*native_log(1.0f+fabs(z.y)/fmax(ta,0.01f))); s39=z.z>0?1:-1; z.z=s39*fmin(fabs(z.z),ta*native_log(1.0f+fabs(z.z)/fmax(ta,0.01f))); break; }
						case 40: { float step40=fmax(tb,0.01f); z.x=floor(z.x/step40+0.5f)*step40; z.x=fmax(fmin(z.x,ta),-ta); z.y=floor(z.y/step40+0.5f)*step40; z.y=fmax(fmin(z.y,ta),-ta); z.z=floor(z.z/step40+0.5f)*step40; z.z=fmax(fmin(z.z,ta),-ta); break; }
						case 41: { for(int k=0;k<3;k++){if(z.x>ta)z.x=2.0f*ta-z.x; if(z.x<-ta)z.x=-2.0f*ta-z.x; if(z.y>ta)z.y=2.0f*ta-z.y; if(z.y<-ta)z.y=-2.0f*ta-z.y; if(z.z>ta)z.z=2.0f*ta-z.z; if(z.z<-ta)z.z=-2.0f*ta-z.z; ta*=tb;} break; }
						case 42: { float r42=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(r42>ta){z*=ta/r42; aux.DE*=ta/r42;} if(r42<tb&&r42>1e-15){z*=tb/r42; aux.DE*=tb/r42;} break; }
						case 43: { z.x=ta*z.x/native_sqrt(z.x*z.x+tb*tb); z.y=ta*z.y/native_sqrt(z.y*z.y+tb*tb); z.z=ta*z.z/native_sqrt(z.z*z.z+tb*tb); break; }
						case 44: { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); z.x=fmin(z.x,ta); z.y=fmin(z.y,ta); z.z=fmin(z.z,ta); break; }
						case 45: { float k45=fmax(tb,0.01f); if(fabs(z.x)>ta){float d=(fabs(z.x)-ta)/k45;float s=z.x>0?1:-1; z.x=s*(ta+k45*d/(1.0f+d*d));} if(fabs(z.y)>ta){float d=(fabs(z.y)-ta)/k45; float s=z.y>0?1:-1; z.y=s*(ta+k45*d/(1.0f+d*d));} if(fabs(z.z)>ta){float d=(fabs(z.z)-ta)/k45; float s=z.z>0?1:-1; z.z=s*(ta+k45*d/(1.0f+d*d));} break; }
						case 46: { float sum46=fabs(z.x)+fabs(z.y)+fabs(z.z); if(sum46>ta){float s=ta/sum46; z*=s; aux.DE*=s;} break; }
						case 47: { if(fabs(z.x)+fabs(z.y)>ta){float s=ta/(fabs(z.x)+fabs(z.y)); z.x*=s; z.y*=s;} break; }
						case 48: { float rxy48=native_sqrt(z.x*z.x+z.y*z.y); if(rxy48>ta){z.x*=ta/rxy48; z.y*=ta/rxy48;} z.z=fmax(fmin(z.z,tb),-tb); break; }
						case 49: { float capH49=fmax(0.0f,fmin(ta,z.z)), rd49=native_sqrt(z.x*z.x+z.y*z.y+(z.z-capH49)*(z.z-capH49)); if(rd49>tb){float s=tb/rd49; z.x*=s; z.y*=s; z.z=capH49+(z.z-capH49)*s; aux.DE*=s;} break; }
						case 50: { float p50=fmax(tc,0.5f), d50=pow(pow(fabs(z.x/fmax(ta,0.01f)),p50)+pow(fabs(z.y/fmax(ta,0.01f)),p50)+pow(fabs(z.z/fmax(tb,0.01f)),p50),1.0f/p50); if(d50>1.0f){z/=d50; aux.DE/=d50;} break; }
						default: break;
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
case 1: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2jb=z.x*z.x+z.y*z.y+z.z*z.z; float minR2jb=tb*tb; float fixedR2jb=1.0f; if(r2jb<minR2jb){z*=fixedR2jb/minR2jb; aux.DE*=fixedR2jb/minR2jb;} else if(r2jb<fixedR2jb){z*=fixedR2jb/r2jb; aux.DE*=fixedR2jb/r2jb;} z=z*tc+(float4)(td,td,td,0.0f); aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
						case 2: { float a2=ta*M_PI_F/180.0f, c2=native_cos(a2),s2=native_sin(a2), nx2=z.x*c2-z.y*s2; z.y=z.x*s2+z.y*c2; z.x=nx2; z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z;{ float r2jb2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2jb2<0.25f){z*=4.0f; aux.DE*=4.0f;} else if(r2jb2<1.0f){z*=1.0f/r2jb2; aux.DE*=1.0f/r2jb2;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
						case 3: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2mb=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tb*tb; if(r2mb<minR2){z*=1.0f/minR2; aux.DE*=1.0f/minR2;} else if(r2mb<1.0f){z*=1.0f/r2mb; aux.DE*=1.0f/r2mb;} z=z*tc+aux.const_c; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
						case 4: { z=fabs(z+(float4)(ta,ta,ta,0.0f))-(float4)(ta,ta,ta,0.0f); { float r2ab=z.x*z.x+z.y*z.y+z.z*z.z; float minR2ab=tb*tb; if(r2ab<minR2ab){z*=1.0f/minR2ab; aux.DE*=1.0f/minR2ab;} else if(r2ab<1.0f){z*=1.0f/r2ab; aux.DE*=1.0f/r2ab;} z=z*tc+aux.const_c; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
						case 5: { float k5=fmax(td,0.01f); z.x=z.x-k5*tanh((z.x-ta)/k5)+k5*tanh((z.x+ta)/k5)-z.x; z.y=z.y-k5*tanh((z.y-ta)/k5)+k5*tanh((z.y+ta)/k5)-z.y; z.z=z.z-k5*tanh((z.z-ta)/k5)+k5*tanh((z.z+ta)/k5)-z.z;{ float r2sb=z.x*z.x+z.y*z.y+z.z*z.z; if(r2sb<tb*tb){z*=1.0f/(tb*tb); aux.DE*=1.0f/(tb*tb);} else if(r2sb<1.0f){z*=1.0f/r2sb; aux.DE*=1.0f/r2sb;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
						case 6: { z.x=fabs(z.x)-ta; z.y=fabs(z.y)-ta; z.z=fabs(z.z)-ta; { float r2af=z.x*z.x+z.y*z.y+z.z*z.z; if(r2af<tb*tb&&r2af>1e-21){z*=1.0f/(r2af); aux.DE*=1.0f/(r2af);} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
						case 7: { if(z.x>ta)z.x=ta-z.x; if(z.x<-ta)z.x=-ta-z.x; if(z.y>ta)z.y=ta-z.y; if(z.y<-ta)z.y=-ta-z.y; if(z.z>ta)z.z=ta-z.z; if(z.z<-ta)z.z=-ta-z.z; { float r2cf=z.x*z.x+z.y*z.y+z.z*z.z; float minR=tb*tb; if(r2cf<minR){z*=1.0f/minR; aux.DE*=1.0f/minR;} else if(r2cf<1.0f){z*=1.0f/r2cf; aux.DE*=1.0f/r2cf;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
						case 8: { for(int k=0;k<3;k++){z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z;} float r2mf=z.x*z.x+z.y*z.y+z.z*z.z; if(r2mf<tb*tb){z*=1.0f/(tb*tb); aux.DE*=1.0f/(tb*tb);} else if(r2mf<1.0f){z*=1.0f/r2mf; aux.DE*=1.0f/r2mf;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 9: { if(z.x+z.y<0.0f){float t=z.x;z.x=-z.y;z.y=-t;} if(z.x+z.z<0.0f){float t=z.x;z.x=-z.z;z.z=-t;} if(z.y+z.z<0.0f){float t=z.y;z.y=-z.z;z.z=-t;} z=z*ta-(float4)(tb,tb,tb,0.0f)*(ta-1.0f); aux.DE=aux.DE*fabs(ta)+1.0f; break; }
						case 10: { z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z=z*ta-(float4)(1,1,1,0.0f)*(ta-1.0f)*tb; aux.DE=aux.DE*fabs(ta)+1.0f; break; }
						case 11: { z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z=z*tc+(float4)(td,td,td,0.0f); aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 12: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 13: { z=z*ta+(float4)(tb,tc,td,0.0f); z.x=fabs(z.x+1.0f)-fabs(z.x-1.0f)-z.x; z.y=fabs(z.y+1.0f)-fabs(z.y-1.0f)-z.y; z.z=fabs(z.z+1.0f)-fabs(z.z-1.0f)-z.z; aux.DE=aux.DE*fabs(ta)+1.0f; break; }
						case 14: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tc)-fabs(z.z-tc)-z.z; { float r2df=z.x*z.x+z.y*z.y+z.z*z.z; if(r2df<0.25f){z*=4.0f;aux.DE*=4.0f;} else if(r2df<1.0f){z*=1.0f/r2df;aux.DE*=1.0f/r2df;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 15: { z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; { float r2mh=z.x*z.x+z.y*z.y+z.z*z.z; if(r2mh<tb*tb){z*=1.0f/(tb*tb);aux.DE*=1.0f/(tb*tb);} else if(r2mh<1.0f){z*=1.0f/r2mh;aux.DE*=1.0f/r2mh;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
						case 16: { float tw16=ta*M_PI_F/180.0f*z.z, c16=native_cos(tw16),s16=native_sin(tw16), nx16=z.x*c16-z.y*s16; z.y=z.x*s16+z.y*c16; z.x=nx16; z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 17: { float sc17=ta+tb*native_sin((float)i*tc); z.x=fabs(z.x+1.0f)-fabs(z.x-1.0f)-z.x; z.y=fabs(z.y+1.0f)-fabs(z.y-1.0f)-z.y; z.z=fabs(z.z+1.0f)-fabs(z.z-1.0f)-z.z; z*=sc17; aux.DE=aux.DE*fabs(sc17)+1.0f; break; }
						case 18: { float r218=z.x*z.x+z.y*z.y+z.z*z.z, minR218=ta*ta, fixR218=tb*tb; if(r218<minR218){z*=fixR218/minR218;aux.DE*=fixR218/minR218;} else if(r218<fixR218){z*=fixR218/r218;aux.DE*=fixR218/r218;} float r218b=z.x*z.x+z.y*z.y+z.z*z.z;{ float minR218b=tc*tc; if(r218b<minR218b){z*=1.0f/minR218b;aux.DE*=1.0f/minR218b;} else if(r218b<1.0f){z*=1.0f/r218b;aux.DE*=1.0f/r218b;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 19: { float rxy19=native_sqrt(z.x*z.x+z.y*z.y); if(rxy19<ta&&rxy19>1e-15){z.x*=ta/rxy19; z.y*=ta/rxy19; aux.DE*=ta/rxy19;} z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 20: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; { float r2xz=z.x*z.x+z.z*z.z; if(r2xz<tb*tb){z*=1.0f/(tb*tb);aux.DE*=1.0f/(tb*tb);} else if(r2xz<1.0f){z*=1.0f/r2xz;aux.DE*=1.0f/r2xz;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
						case 21: { z=fabs(z)-(float4)(ta,ta,ta,0.0f); z+=aux.const_c*tb; { float r2ao=z.x*z.x+z.y*z.y+z.z*z.z; if(r2ao<tc*tc){z*=1.0f/(tc*tc);aux.DE*=1.0f/(tc*tc);} else if(r2ao<1.0f){z*=1.0f/r2ao;aux.DE*=1.0f/r2ao;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 22: { if(i%2==0){z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z;} else{z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;}} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 23: { float r2so=z.x*z.x+z.y*z.y+z.z*z.z, minR2so=ta*ta, fixedR2so=tb*tb; if(r2so<minR2so){float m=fixedR2so/minR2so; z*=m; aux.DE*=m;} else if(r2so<fixedR2so){float m=fixedR2so/r2so; z*=m; aux.DE*=m;} break; }
						case 24: { if(z.x+z.y<0.0f){float t=-z.y;z.y=-z.x;z.x=t;} if(z.x+z.z<0.0f){float t=-z.z;z.z=-z.x;z.x=t;} if(z.y+z.z<0.0f){float t=-z.z;z.z=-z.y;z.y=t;} z*=ta; z-=(float4)(tb,tb,tb,0.0f)*(ta-1.0f); aux.DE=aux.DE*fabs(ta)+1.0f; break; }
						case 25: { z.x=fabs(fabs(z.x+ta)-tb)-ta; z.y=fabs(fabs(z.y+ta)-tb)-ta; z.z=fabs(fabs(z.z+ta)-tb)-ta; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 26: { float r2rb=z.x*z.x+z.y*z.y+z.z*z.z, theta26=atan2(z.y,z.x), phi26=atan2(native_sqrt(z.x*z.x+z.y*z.y),z.z), rr26=native_sqrt(r2rb); rr26=fabs(rr26+ta)-fabs(rr26-ta)-rr26; z.x=rr26*native_sin(phi26)*native_cos(theta26); z.y=rr26*native_sin(phi26)*native_sin(theta26); z.z=rr26*native_cos(phi26); z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 27: { float p27=fmax(tb,0.5f); z.x=z.x>0?pow(fabs(z.x),p27):-pow(fabs(z.x),p27); z.y=z.y>0?pow(fabs(z.y),p27):-pow(fabs(z.y),p27); z.z=z.z>0?pow(fabs(z.z),p27):-pow(fabs(z.z),p27); z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 28: { if(i%3==0){z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x;} else if(i%3==1){z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y;} else{z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z;} float r2il=z.x*z.x+z.y*z.y+z.z*z.z; if(r2il<tb*tb){z*=1.0f/(tb*tb);aux.DE*=1.0f/(tb*tb);} else if(r2il<1.0f){z*=1.0f/r2il;aux.DE*=1.0f/r2il;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 29: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2mj=z.x*z.x+z.y*z.y+z.z*z.z; if(r2mj<0.25f){z*=4.0f;aux.DE*=4.0f;} else if(r2mj<1.0f){z*=1.0f/r2mj;aux.DE*=1.0f/r2mj;} z=z*tc+(float4)(td,td,td,0.0f); aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
						case 30: { z*=ta; aux.DE=aux.DE*fabs(ta)+1.0f; { float a30=tb*M_PI_F/180.0f; float c30=native_cos(a30),s30=native_sin(a30); float nx30=z.x*c30-z.y*s30; z.y=z.x*s30+z.y*c30; z.x=nx30; z.x=fabs(z.x+tc)-fabs(z.x-tc)-z.x; z.y=fabs(z.y+tc)-fabs(z.y-tc)-z.y; z.z=fabs(z.z+tc)-fabs(z.z-tc)-z.z; } break; }
						case 31: { float bp31=z.x*z.x+z.y*z.y; if(bp31>1e-21){float inv=ta*ta/bp31; z.x*=inv; z.y*=inv; aux.DE*=inv;} z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 32: { float r2cb=z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w; if(r2cb>1e-21){z*=ta/r2cb; aux.DE*=ta/r2cb;} z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 33: { float lim33=ta*(1.0f+tb*(float)i/250.0f); z.x=fabs(z.x+lim33)-fabs(z.x-lim33)-z.x; z.y=fabs(z.y+lim33)-fabs(z.y-lim33)-z.y; z.z=fabs(z.z+lim33)-fabs(z.z-lim33)-z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 34: { float n34=native_sin(z.x*12.9898f+z.y*78.233f)*43758.5453f; n34=n34-floor(n34); { float lim34=ta+tb*(n34-0.5f); z.x=fabs(z.x+lim34)-fabs(z.x-lim34)-z.x; z.y=fabs(z.y+lim34)-fabs(z.y-lim34)-z.y; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
						case 35: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; z.w=fabs(z.w+ta)-fabs(z.w-ta)-z.w; { float r24d=z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w; if(r24d<tb*tb){z*=1.0f/(tb*tb);aux.DE*=1.0f/(tb*tb);} else if(r24d<1.0f){z*=1.0f/r24d;aux.DE*=1.0f/r24d;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
						case 36: { float q36x=z.x, q36y=z.y*0.866f+z.x*0.5f; if(q36y>ta){q36y=2.0f*ta-q36y;} if(q36x>ta){q36x=2.0f*ta-q36x;} z.x=q36x; z.y=(q36y-z.x*0.5f)/0.866f; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 37: { float d37x=fabs(z.x)-ta, d37y=fabs(z.y)-ta, d37z=fabs(z.z)-ta; if(d37x>0&&d37y>0){z.x*=ta/(ta+d37x); z.y*=ta/(ta+d37y);} if(d37y>0&&d37z>0){z.y*=ta/(ta+d37y); z.z*=ta/(ta+d37z);} if(d37x>0&&d37z>0){z.x*=ta/(ta+d37x); z.z*=ta/(ta+d37z);} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 38: { z.x+=tb*native_sin(ta*z.y)*native_cos(ta*z.z); z.y+=tb*native_sin(ta*z.z)*native_cos(ta*z.x); z.z+=tb*native_cos(ta*z.y)*native_sin(ta*z.x); z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 39: { z.x=fabs(native_cos(z.x*ta))*tb; z.y=fabs(native_cos(z.y*ta))*tb; z.z=fabs(native_cos(z.z*ta))*tb; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 40: { z.x=z.x>0?native_log(1.0f+z.x*ta):-native_log(1.0f-z.x*ta); z.y=z.y>0?native_log(1.0f+z.y*ta):-native_log(1.0f-z.y*ta); z.z=z.z>0?native_log(1.0f+z.z*ta):-native_log(1.0f-z.z*ta); z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 41: { float lim41=ta; z.x=z.x>lim41?lim41-(z.x-lim41)*(z.x-lim41)*tb:z.x<-lim41?-lim41+(z.x+lim41)*(z.x+lim41)*tb:z.x; z.y=z.y>lim41?lim41-(z.y-lim41)*(z.y-lim41)*tb:z.y<-lim41?-lim41+(z.y+lim41)*(z.y+lim41)*tb:z.y; z.z=z.z>lim41?lim41-(z.z-lim41)*(z.z-lim41)*tb:z.z<-lim41?-lim41+(z.z+lim41)*(z.z+lim41)*tb:z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 42: { z.x=fmin(fmax(z.x,-ta),ta); z.y=fmin(fmax(z.y,-ta),ta); z.z=fmin(fmax(z.z,-ta),ta); z.x=fmax(fmin(z.x,tb),-tb); z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 43: { if(fabs(z.x)>ta)z.x=z.x>0?ta:-ta; if(fabs(z.y)>ta)z.y=z.y>0?ta:-ta; if(fabs(z.z)>ta)z.z=z.z>0?ta:-ta; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 44: { float p44=2.0f*ta; z.x=z.x-p44*floor((z.x+ta)/p44); z.y=z.y-p44*floor((z.y+ta)/p44); z.z=z.z-p44*floor((z.z+ta)/p44); z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 45: { float r45=native_sqrt(z.x*z.x+z.y*z.y), th45=atan2(z.y,z.x); th45=fabs(th45+ta)-fabs(th45-ta)-th45; z.x=r45*native_cos(th45); z.y=r45*native_sin(th45); z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 46: { float lim46=ta*(1.0f+tb*native_log(1.0f+fabs(aux.DE))); z.x=fabs(z.x+lim46)-fabs(z.x-lim46)-z.x; z.y=fabs(z.y+lim46)-fabs(z.y-lim46)-z.y; z.z=fabs(z.z+lim46)-fabs(z.z-lim46)-z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 47: { float lim47=ta*(1.0f+tb*native_sin(aux.color*tc)); z.x=fabs(z.x+lim47)-fabs(z.x-lim47)-z.x; z.y=fabs(z.y+lim47)-fabs(z.y-lim47)-z.y; z.z=fabs(z.z+lim47)-fabs(z.z-lim47)-z.z; z*=td; aux.DE=aux.DE*fabs(td)+1.0f; break; }
						case 48: { float la=ta,lb=tb; for(int k=0;k<3;k++){z.x=fabs(z.x+la)-fabs(z.x-la)-z.x; z.y=fabs(z.y+la)-fabs(z.y-la)-z.y; z.z=fabs(z.z+la)-fabs(z.z-la)-z.z; la*=lb;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 49: { z.x=z.x>ta?z.x-2.0f*ta:z.x<-ta?z.x+2.0f*ta:z.x; z.y=z.y>ta?z.y-2.0f*ta:z.y<-ta?z.y+2.0f*ta:z.y; z.z=z.z>ta?z.z-2.0f*ta:z.z<-ta?z.z+2.0f*ta:z.z; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 50: { z=fabs(z); if(z.x-z.y<0.0f){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){float t=z.y;z.y=z.z;z.z=t;} z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2ifs=z.x*z.x+z.y*z.y+z.z*z.z; if(r2ifs<tb*tb){z*=1.0f/(tb*tb);aux.DE*=1.0f/(tb*tb);} else if(r2ifs<1.0f){z*=1.0f/r2ifs;aux.DE*=1.0f/r2ifs;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
						default: break;
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
						case 1: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tb*tb; if(r2<minR2){z*=1.0f/minR2;aux.DE*=1.0f/minR2;} else if(r2<1.0f){z*=1.0f/r2;aux.DE*=1.0f/r2;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; z+=(float4)(td,td,td,0.0f); } break; }
						case 2: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tc)-fabs(z.z-tc)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<0.25f){z*=4.0f;aux.DE*=4.0f;} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 3: { float rxy=native_sqrt(z.x*z.x+z.y*z.y); if(rxy>ta){float s=ta/rxy; z.x*=s; z.y*=s; aux.DE*=s;} float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){z*=1.0f/(tb*tb);aux.DE*=1.0f/(tb*tb);} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 4: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float fixR=tb*tb; float minR=tc*tc; if(r2<minR){z*=fixR/minR;aux.DE*=fixR/minR;} else if(r2<fixR){z*=fixR/r2;aux.DE*=fixR/r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 5: { z=fabs(z+(float4)(ta,ta,ta,0.0f))-(float4)(ta,ta,ta,0.0f); { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb){z*=tc/tb;aux.DE*=tc/tb;} else if(r2<tc){z*=tc/r2;aux.DE*=tc/r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 6: { if(z.x+z.y<0){float t=z.x;z.x=-z.y;z.y=-t;} if(z.x+z.z<0){float t=z.x;z.x=-z.z;z.z=-t;} if(z.y+z.z<0){float t=z.y;z.y=-z.z;z.z=-t;} z=z*ta-(float4)(tb,tb,tb,0.0f)*(ta-1.0f); aux.DE=aux.DE*fabs(ta)+1.0f; break; }
						case 7: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){float s=tc/(tb*tb); z*=s;aux.DE*=s;} else if(r2<tc){float s=tc/r2; z*=s;aux.DE*=s;} z.z=td*z.z; aux.DE*=fabs(td); } break; }
						case 8: { float a8=ta*M_PI_F/180.0f, c8=native_cos(a8),s8=native_sin(a8), nx=z.x*c8-z.y*s8; z.y=z.x*s8+z.y*c8; z.x=nx; z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z;{ float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<0.25f){z*=4.0f;aux.DE*=4.0f;} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
						case 9: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(r<tb){z*=tc/(tb*tb);aux.DE*=tc/(tb*tb);} else if(r<native_sqrt(tc)){z*=tc/(r*r);aux.DE*=tc/(r*r);} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 10: { z=fabs(z)-(float4)(ta,ta,ta,0.0f); if(z.x<0)z.x=0; if(z.y<0)z.y=0; if(z.z<0)z.z=0; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){z*=1.0f/(tb*tb);aux.DE*=1.0f/(tb*tb);} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; z+=(float4)(td,td,td,0.0f); } break; }
						case 11: { float rxy=native_sqrt(z.x*z.x+z.y*z.y), minR=ta; if(rxy<minR&&rxy>1e-21f){float s=minR/rxy; z.x*=s;z.y*=s;aux.DE*=s;} z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; break; }
						case 12: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float sph=fmax(tb*tb/fmax(r2,1e-21f),1.0f); z*=sph*tc; aux.DE=aux.DE*sph*fabs(tc)+1.0f; } break; }
						case 13: { if(z.x-z.y<0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){float t=z.y;z.y=z.z;z.z=t;} z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tc*tc){z*=1.0f/(tc*tc);aux.DE*=1.0f/(tc*tc);} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 14: { z.x=ta*tanh(z.x/fmax(ta,1e-10f)); z.y=ta*tanh(z.y/fmax(ta,1e-10f)); z.z=ta*tanh(z.z/fmax(ta,1e-10f)); { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){z*=tc/(tb*tb);aux.DE*=tc/(tb*tb);} else if(r2<tc){z*=tc/r2;aux.DE*=tc/r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 15: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tb*tb; float fixR2=tc*tc; if(r2<minR2){z*=fixR2/minR2;aux.DE*=fixR2/minR2;} else if(r2<fixR2){z*=fixR2/r2;aux.DE*=fixR2/r2;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; z+=(float4)(td,td,td,0.0f); } break; }
						case 16: { float fold=ta; z.x=fabs(z.x+fold)-fabs(z.x-fold)-z.x; z.y=fabs(z.y+fold)-fabs(z.y-fold)-z.y; z.z=fabs(z.z+fold)-fabs(z.z-fold)-z.z;{ float r2=z.x*z.x+z.y*z.y+z.z*z.z, k=fmax(tb/fmax(r2,1e-21f),1.0f); z*=k; aux.DE*=k; z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; z.x+=td; } break; }
						case 17: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb){z*=tc/tb;aux.DE*=tc/tb;} else if(r2<tc){z*=tc/r2;aux.DE*=tc/r2;} float sc=td+sf*native_sin((float)i*0.5f); z*=sc; aux.DE=aux.DE*fabs(sc)+1.0f; } break; }
						case 18: { z.x=clamp(z.x,-ta,ta)*2.0f-z.x; z.y=clamp(z.y,-ta,ta)*2.0f-z.y; z.z=clamp(z.z,-ta,ta)*2.0f-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float k=fmax(tb/fmax(r2,1e-21f),1.0f); z*=k*tc; aux.DE=aux.DE*k*fabs(tc)+1.0f; z+=(float4)(td,0.0f,0.0f,0.0f); } break; }
						case 19: { z=fabs(z+(float4)(ta,tb,ta,0.0f))-(float4)(ta,tb,ta,0.0f); { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tc*tc; if(r2<minR2){float s=td/minR2;z*=s;aux.DE*=s;} else if(r2<td){float s=td/r2;z*=s;aux.DE*=s;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
						case 20: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float theta=atan2(z.y,z.x); float r=native_sqrt(z.x*z.x+z.y*z.y); r=fmax(r,tb); z.x=r*native_cos(theta); z.y=r*native_sin(theta); float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tc*tc){z*=1.0f/(tc*tc);aux.DE*=1.0f/(tc*tc);} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 21: { z=fabs(z)-(float4)(ta,ta,ta,0.0f); z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tc*tc){z*=td/(tc*tc);aux.DE*=td/(tc*tc);} else if(r2<td){z*=td/r2;aux.DE*=td/r2;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
						case 22: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float sph=tb*tb/fmax(r2,tc*tc); z*=sph; aux.DE*=sph; z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 23: { float fold23=ta*(1.0f+tb*(float)i/250.0f); z.x=fabs(z.x+fold23)-fabs(z.x-fold23)-z.x; z.y=fabs(z.y+fold23)-fabs(z.y-fold23)-z.y; z.z=fabs(z.z+fold23)-fabs(z.z-fold23)-z.z;{ float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tc*tc){z*=td/(tc*tc);aux.DE*=td/(tc*tc);} else if(r2<td){z*=td/r2;aux.DE*=td/r2;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
						case 24: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float k=tb/fmax(r,tc); z*=k; aux.DE*=k; z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 25: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tb*tb; float fixR2=tc*tc; float sph=clamp(fixR2/fmax(r2,minR2),1.0f,fixR2/minR2); z*=sph; aux.DE*=sph; z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 26: { if(z.x+z.y<0){float t=-z.y;z.y=-z.x;z.x=t;} if(z.x+z.z<0){float t=-z.z;z.z=-z.x;z.x=t;} z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tc*tc){z*=td/(tc*tc);aux.DE*=td/(tc*tc);} else if(r2<td){z*=td/r2;aux.DE*=td/r2;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
						case 27: { z.x=ta-fabs(z.x-ta); z.y=ta-fabs(z.y-ta); z.z=ta-fabs(z.z-ta); { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){z*=tc/(tb*tb);aux.DE*=tc/(tb*tb);} else if(r2<tc){z*=tc/r2;aux.DE*=tc/r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 28: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float inv=tb/fmax(r2,1e-21f); z*=inv; aux.DE*=inv; z.x+=tc; z.y+=tc; z.z+=td; } break; }
						case 29: { float s29=sf; z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z;{ float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){s29*=tc/(tb*tb);} else if(r2<tc){s29*=tc/r2;} z*=s29; aux.DE=aux.DE*fabs(s29)+1.0f; z+=(float4)(td,td,td,0.0f); } break; }
						case 30: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tc)-fabs(z.z-tc)-z.z; { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(r<td&&r>1e-21f){float s=td/r;z*=s;aux.DE*=s;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
						case 31: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tb*tb; if(r2<minR2){z*=1.0f/minR2;aux.DE*=1.0f/minR2;} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z.x=z.x*tc+td; z.y=z.y*tc; z.z=z.z*tc; aux.DE=aux.DE*fabs(tc)+1.0f; } break; }
						case 32: { float a32=ta*M_PI_F/180.0f, c32=native_cos(a32),s32=native_sin(a32), ny=z.y*c32-z.z*s32; z.z=z.y*s32+z.z*c32; z.y=ny; z.x=fabs(z.x+tb)-fabs(z.x-tb)-z.x; z.y=fabs(z.y+tb)-fabs(z.y-tb)-z.y; z.z=fabs(z.z+tb)-fabs(z.z-tb)-z.z;{ float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tc*tc){z*=td/(tc*tc);aux.DE*=td/(tc*tc);} else if(r2<td){z*=td/r2;aux.DE*=td/r2;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
						case 33: { z=fabs(z+(float4)(ta,ta,ta,0.0f))-(float4)(ta,ta,ta,0.0f); z=fabs(z+(float4)(tb,tb,tb,0.0f))-(float4)(tb,tb,tb,0.0f); { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tc*tc){z*=td/(tc*tc);aux.DE*=td/(tc*tc);} else if(r2<td){z*=td/r2;aux.DE*=td/r2;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; } break; }
						case 34: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float smooth=tb*tb/(fmax(r2,tc*tc)); z*=smooth; aux.DE*=smooth; z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 35: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float len=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float k=tb/fmax(len*len,tc); z*=k;aux.DE*=k; z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 36: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float f36=1.0f/(1.0f+native_exp(-tb*(r2-tc))); z*=f36*td; aux.DE=aux.DE*f36*fabs(td)+1.0f; } break; }
						case 37: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tb*tb; float maxSph=tc; float sph=clamp(1.0f/fmax(r2,minR2),1.0f,maxSph); z*=sph; aux.DE*=sph; z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 38: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float sum=fabs(z.x)+fabs(z.y)+fabs(z.z); if(sum>tb){float s=tb/sum;z*=s;aux.DE*=s;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; z+=(float4)(td,0.0f,0.0f,0.0f); } break; }
						case 39: { float fold39=ta+tb*native_sin((float)i*tc); z.x=fabs(z.x+fold39)-fabs(z.x-fold39)-z.x; z.y=fabs(z.y+fold39)-fabs(z.y-fold39)-z.y; z.z=fabs(z.z+fold39)-fabs(z.z-fold39)-z.z;{ float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<0.25f){z*=4.0f;aux.DE*=4.0f;} else if(r2<1.0f){z/=r2;aux.DE/=r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 40: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float p=tb/fmax(r2,1e-21f); z.x=z.x*p+tc; z.y=z.y*p+tc; z.z=z.z*p+td; aux.DE=aux.DE*fabs(p)+1.0f; } break; }
						case 41: { if(z.x>ta)z.x=2.0f*ta-z.x; if(z.x<-ta)z.x=-2.0f*ta-z.x; if(z.y>ta)z.y=2.0f*ta-z.y; if(z.y<-ta)z.y=-2.0f*ta-z.y; if(z.z>ta)z.z=2.0f*ta-z.z; if(z.z<-ta)z.z=-2.0f*ta-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){z*=tc/(tb*tb);aux.DE*=tc/(tb*tb);} else if(r2<tc){z*=tc/r2;aux.DE*=tc/r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 42: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR=tb*tb; float fixR=tc*tc; float s42=(r2<minR)?fixR/minR:(r2<fixR)?fixR/r2:1.0f; z*=s42*td; aux.DE=aux.DE*s42*fabs(td)+1.0f; } break; }
						case 43: { z.x=ta-fabs(fabs(z.x)-ta); z.y=ta-fabs(fabs(z.y)-ta); z.z=ta-fabs(fabs(z.z)-ta); { float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){z*=tc/(tb*tb);aux.DE*=tc/(tb*tb);} else if(r2<tc){z*=tc/r2;aux.DE*=tc/r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; } break; }
						case 44: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float invR=1.0f/fmax(r2,tb*tb); z*=invR*tc; aux.DE=aux.DE*invR*fabs(tc)+1.0f; z+=(float4)(td,td,td,0.0f); } break; }
						case 45: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r=native_sqrt(z.x*z.x+z.y*z.y+z.z*z.z); float f45=tb/(1.0f+native_exp(tc*(r-td))); z*=f45; aux.DE*=f45; } break; }
						case 46: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float maxC=fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z))); if(maxC>tb){float s=tb/maxC;z*=s;aux.DE*=s;} z*=tc; aux.DE=aux.DE*fabs(tc)+1.0f; z+=(float4)(td,0.0f,0.0f,0.0f); } break; }
						case 47: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float k47=fmax(tb*tb/fmax(r2,tc*tc),1.0f); z*=k47*td; aux.DE=aux.DE*k47*fabs(td)+1.0f; } break; }
						case 48: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float minR2=tb*tb; if(r2<minR2){z*=1.0f/minR2;aux.DE*=1.0f/minR2;} else if(r2<1.0f){z/=r2;aux.DE/=r2;} float sc48=tc+td*native_exp(-(float)i*sf); z*=sc48; aux.DE=aux.DE*fabs(sc48)+1.0f; } break; }
						case 49: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; { float r2=z.x*z.x+z.y*z.y+z.z*z.z; float sph49=fmax(tb/fmax(r2,tc*tc),1.0f); z.x=z.x*sph49*td; z.y=z.y*sph49; z.z=z.z*sph49; aux.DE*=sph49*fabs(td); } break; }
						case 50: { z.x=fabs(z.x+ta)-fabs(z.x-ta)-z.x; z.y=fabs(z.y+ta)-fabs(z.y-ta)-z.y; z.z=fabs(z.z+ta)-fabs(z.z-ta)-z.z; if(z.x-z.y<0){float t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){float t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){float t=z.y;z.y=z.z;z.z=t;} float r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<tb*tb){z*=tc/(tb*tb);aux.DE*=tc/(tb*tb);} else if(r2<tc){z*=tc/r2;aux.DE*=tc/r2;} z*=td; aux.DE=aux.DE*fabs(td)+1.0f; break; }
						default: break;
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



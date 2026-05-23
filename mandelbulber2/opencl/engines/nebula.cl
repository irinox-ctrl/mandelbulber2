/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2017-19 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * Nebula dractal renderig kernel
 */

#define MANDELBULBER_VERSION 2.35

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

float4 DummyIteration(float4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	aux->r = -1.0f; // signal for main loop to break;
	return 0.0f;
}

int GetInteger(int byte, __global char *array)
{
	__global int *intPointer = (__global int *)&array[byte];
	return *intPointer;
}

float3 GradientInterpolate(int paletteIndex, float pos, bool smooth, int gradientSize,
	__global float4 *palette, __global float4 *midpoints, int midpointSize)
{
	float3 color = 0.0f;
	// if last element then just copy color value (no interpolation)
	if (paletteIndex == gradientSize - 1)
	{
		color = palette[paletteIndex - 1].xyz;
	}
	else
	{
		// interpolation
		float3 color1 = palette[paletteIndex].xyz;
		float pos1 = palette[paletteIndex].w;
		float3 color2 = palette[paletteIndex + 1].xyz;
		float pos2 = palette[paletteIndex + 1].w;

		// relative delta
		if (pos2 - pos1 > 0.0f)
		{
			float delta = (pos - pos1) / (pos2 - pos1);

			if (smooth) delta = 0.5f * (1.0f - cos(delta * M_PI_F));

			// apply midpoint curve
			if (midpoints && paletteIndex < midpointSize)
			{
				float m = clamp(midpoints[paletteIndex].s0, 0.01f, 0.99f);
				if (delta < m)
				{
					delta = 0.5f * delta / m;
				}
				else
				{
					delta = 0.5f + 0.5f * (delta - m) / (1.0f - m);
				}
			}

			float nDelta = 1.0f - delta;
			color.s0 = color1.s0 * nDelta + color2.s0 * delta;
			color.s1 = color1.s1 * nDelta + color2.s1 * delta;
			color.s2 = color1.s2 * nDelta + color2.s2 * delta;
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

//------------------ MAIN RENDER FUNCTION --------------------
kernel void Nebula(__global float4 *inOutImage, __constant sClInConstants *consts,
	__global char *inBuff, int4 randomInt4)
{
	const ulong index = get_global_id(0);
	const ulong groupId = get_group_id(0);
	const ulong workGroupSize = get_local_size(0);
	const ulong offset = get_global_offset(0);
	ulong gripIdGlobal = groupId + offset / workGroupSize;

	// calculation is done by blocks of 16x16x16 to reduce variety of calculations within one
	// workgroup
	const uint blockGridSize = max(consts->params.imageHeight / 64, 1);
	const uint numberOfBlocks = blockGridSize * blockGridSize * blockGridSize;

	uint blockId = (uint)(gripIdGlobal % numberOfBlocks);
	uint blockX = (blockId % blockGridSize);
	uint blockY = (uint)(blockId / blockGridSize) % blockGridSize;
	uint blockZ = (uint)(blockId / (blockGridSize * blockGridSize)) % blockGridSize;

	float blockSize = 1.0f / blockGridSize;
	float blockOffsetX = (float)blockX * blockSize;
	float blockOffsetY = (float)blockY * blockSize;
	float blockOffsetZ = (float)blockZ * blockSize;

	int imageSize = consts->params.imageWidth * consts->params.imageHeight;

	// preparation of random seeds
	ulong randomSeedX = randomInt4.x + index;
	ulong randomSeedY = randomInt4.y + index;
	ulong randomSeedZ = randomInt4.z + index;
	ulong randomSeedW = randomInt4.w + index;

	//-------- random seed randomization ----------------
	for (int i = 0; i < 10; i++)
	{
		uint dummyx = RandomL(1298117, &randomSeedX);
		uint dummyy = RandomL(855229, &randomSeedY);
		uint dummyz = RandomL(473167, &randomSeedZ);
		uint dummyw = RandomL(672131, &randomSeedW);

		randomSeedX += dummyx;
		randomSeedY += dummyy;
		randomSeedZ += dummyz;
		randomSeedW += dummyw;
	}

	//-------- decode main data file ----------------
	int gradientsOffset = GetInteger(0, inBuff);
	int paletteItemsOffset = GetInteger(gradientsOffset + sizeof(int) * 0, inBuff);

	int paletteOffsetXAxis = GetInteger(gradientsOffset + sizeof(int) * 1, inBuff);
	int paletteLengthXAxis = GetInteger(gradientsOffset + sizeof(int) * 2, inBuff);

	int paletteOffsetYAxis = GetInteger(gradientsOffset + sizeof(int) * 3, inBuff);
	int paletteLengthYAxis = GetInteger(gradientsOffset + sizeof(int) * 4, inBuff);

	int paletteOffsetZAxis = GetInteger(gradientsOffset + sizeof(int) * 5, inBuff);
	int paletteLengthZAxis = GetInteger(gradientsOffset + sizeof(int) * 6, inBuff);

	int paletteOffsetIterations = GetInteger(gradientsOffset + sizeof(int) * 7, inBuff);
	int paletteLengthIterations = GetInteger(gradientsOffset + sizeof(int) * 8, inBuff);

	__global float4 *gradients = (__global float4 *)&inBuff[paletteItemsOffset];

	float4 point;

#ifdef LIMITS_ENABLED
	point.x = RandomL(2147483647, &randomSeedX) / 2147483647.0f * blockSize + blockOffsetX;
	point.y = RandomL(2147483647, &randomSeedY) / 2147483647.0f * blockSize + blockOffsetY;
	point.z = RandomL(2147483647, &randomSeedZ) / 2147483647.0f * blockSize + blockOffsetZ;

	float3 limitMax = consts->params.limitMax;
	float3 limitMin = consts->params.limitMin;

	// scale point to limits
	point.xyz = point.xyz * (limitMax - limitMin) + limitMin;
#else
	point.x =
		(RandomL(2147483647, &randomSeedX) / 2147483647.0f * blockSize + blockOffsetX - 0.5f) * 4.0f;
	point.y =
		(RandomL(2147483647, &randomSeedY) / 2147483647.0f * blockSize + blockOffsetY - 0.5f) * 4.0f;
	point.z =
		(RandomL(2147483647, &randomSeedZ) / 2147483647.0f * blockSize + blockOffsetZ - 0.5f) * 4.0f;

	float3 limitMax = 2.0f;
	float3 limitMin = -2.0f;
#endif

#ifdef NEBULA_GRID_DOMAIN_ENABLED
	int axisSelection = RandomL(3, &randomSeedW);

	switch (axisSelection)
	{
		case 0:
		{
			ulong pointX = point.x / consts->params.nebulaXGridSize;
			point.x = (float)pointX * consts->params.nebulaXGridSize;

			ulong pointY = point.y / consts->params.nebulaYGridSize;
			point.y = (float)pointY * consts->params.nebulaYGridSize;
			break;
		}
		case 1:
		{
			ulong pointX = point.x / consts->params.nebulaXGridSize;
			point.x = (float)pointX * consts->params.nebulaXGridSize;

			ulong pointZ = point.z / consts->params.nebulaZGridSize;
			point.z = (float)pointZ * consts->params.nebulaZGridSize;
			break;
		}
		case 2:
		{
			ulong pointY = point.y / consts->params.nebulaYGridSize;
			point.y = (float)pointY * consts->params.nebulaYGridSize;

			ulong pointZ = point.z / consts->params.nebulaZGridSize;
			point.z = (float)pointZ * consts->params.nebulaZGridSize;
			break;
		}
	}

#endif

	// repeat, move and rotate
	float3 pointTransformed = point.xyz - consts->params.common.fractalPosition;
	pointTransformed = Matrix33MulFloat3(consts->params.common.mRotFractalRotation, pointTransformed);
	pointTransformed = modRepeat(pointTransformed, consts->params.common.repeat);

	point.w = consts->sequence.initialWAxis[0];

	float4 z = (float4){pointTransformed.x, pointTransformed.y, pointTransformed.z, point.w};
	float4 c = z;
	int i;

	int fractalIndex = 0;

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

	float4 zHistory[MAX_ITERATIONS];

	// v7.5 — Julia start mode (z₀ override, GPU Nebula)
	{
		__constant sClFormulaMutationParams *jm0 = &consts->sequence.mutationParams[0];
		if (jm0->enabled && jm0->juliaStart != 0)
		{
			if (jm0->juliaStart == 1) z = aux.const_c;
			else if (jm0->juliaStart == 2) z = z + aux.const_c;
			else if (jm0->juliaStart == 3) { aux.const_c = z; aux.c = z; z = (float4)(0.0f, 0.0f, 0.0f, 0.0f); }
			else if (jm0->juliaStart == 4) z = (float4)(aux.const_c.x, aux.const_c.y, aux.const_c.z, aux.const_c.w);
		}
	}

	// loop
	for (i = 0; i < MAX_ITERATIONS; i++)
	{

#if defined(IS_HYBRID)
		sequence = consts->sequence.hybridSequence[min(i, 249)];
#else
		sequence = 0;
#endif

		fractal = &consts->fractal[sequence];

		aux.i = i;

		zHistory[i] = z;

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

			if (deFunc == 0 && weightMode == 7)
			{
				effectiveWeight = 1.0f;
			}
			else
			{
				float standardWeight = consts->sequence.formulaWeight[sequence];
				float actualDE = aux.DE;
				if (aux.r > 0.0f)
				{
					if (deFunc == pseudoKleinianDEFunction)
					{
						float rxy = native_sqrt(z.x * z.x + z.y * z.y);
						actualDE = (aux.DE > 0.0f) ? max(rxy - aux.pseudoKleinianDE, fabs(rxy * z.z) / aux.r) / aux.DE : aux.r;
					}
					else if (deFunc == josKleinianDEFunction)
					{
						actualDE = min(z.y, fractal->analyticDE.tweak005) / max(aux.DE, fractal->analyticDE.offset1);
					}
					else if (deFunc == logarithmicDEFunction)
					{
						actualDE = (aux.DE > 0.0f && aux.r > 1.0f) ? 0.5f * aux.r * native_log(aux.r) / aux.DE : aux.r;
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
					else if (deFunc == 0)
					{
						actualDE = aux.r;
					}
				}

				if (weightMode == 0) effectiveWeight = wp->staticWeight;
				else if (weightMode == 1)
				{
					if (i <= wp->iterStart) effectiveWeight = wp->startWeight;
					else if (i >= wp->iterEnd) effectiveWeight = wp->endWeight;
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
				else if (weightMode == 2)
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
				else if (weightMode == 3)
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
				else if (weightMode == 4)
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
				else if (weightMode == 5)
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
				else if (weightMode == 6)
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
				else if (weightMode == 7) effectiveWeight = 1.0f;
				else if (weightMode == 8)
				{
					float ratio = (wp->deRatioOffset > 1e-15f) ? actualDE / wp->deRatioOffset : actualDE;
					ratio *= wp->deRatioScale;
					if (wp->deRatioModType == 0) effectiveWeight = clamp(ratio, 0.0f, 1.0f);
					else if (wp->deRatioModType == 1) { float c = clamp(ratio, 0.0f, 1.0f); effectiveWeight = c * c * (3.0f - 2.0f * c); }
					else if (wp->deRatioModType == 2) effectiveWeight = 1.0f - exp(-fabs(ratio));
					else if (wp->deRatioModType == 3) effectiveWeight = (fabs(ratio) > 1e-15f) ? clamp(1.0f / ratio, 0.0f, 1.0f) : 1.0f;
					else effectiveWeight = 1.0f / (1.0f + exp(-(ratio - 0.5f) * 6.0f));
				}
				else if (weightMode == 9)
				{
					float str = wp->adaptiveStrength;
					if (deFunc == logarithmicDEFunction) { float norm = (actualDE > 1e-15f) ? native_log(1.0f + actualDE) : 0.0f; effectiveWeight = 1.0f / (1.0f + exp(-(norm - 0.5f) * 4.0f * str)); }
					else if (deFunc == linearDEFunction) { float norm = clamp(actualDE * str, 0.0f, 1.0f); effectiveWeight = norm * norm * (3.0f - 2.0f * norm); }
					else if (deFunc == customDEFunction) { float dist = (aux.dist > 1e-15f) ? aux.dist : actualDE; effectiveWeight = (dist > 1e-15f) ? clamp(str / (str + dist), 0.0f, 1.0f) : 1.0f; }
					else if (deFunc == pseudoKleinianDEFunction || deFunc == josKleinianDEFunction) effectiveWeight = 1.0f / (1.0f + exp(-(actualDE - 0.5f) * 6.0f * str));
					else if (deFunc == 0) effectiveWeight = 1.0f;
					else { float norm = clamp(actualDE * str, 0.0f, 1.0f); effectiveWeight = norm * norm * (3.0f - 2.0f * norm); }
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

		// -------------- Formula Mutation pre-processing (GPU Nebula) ---------------
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

			
			// Fold injection (pre or both)
			if (i >= mut->foldIterStart && i < mut->foldIterStop
				&& mut->foldType != 0 && (mut->foldPosition == 0 || mut->foldPosition == 2))
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
					case 16:
					{
						float k = (mut->foldLimit > 0.0f) ? mut->foldLimit : 5.0f;
						z.x = z.x * tanh(k * z.x);
						z.y = z.y * tanh(k * z.y);
						z.z = z.z * tanh(k * z.z);
						break;
					}
					case 17:
					{
						float period = (mut->foldValue > 0.0f) ? mut->foldValue : 2.0f;
						z.x = fmod(z.x + period * 0.5f, period) - period * 0.5f;
						z.y = fmod(z.y + period * 0.5f, period) - period * 0.5f;
						z.z = fmod(z.z + period * 0.5f, period) - period * 0.5f;
						break;
					}
					case 18:
					{
						float c = (mut->foldLimit > 0.0f) ? mut->foldLimit : 1.0f;
						z.x = fabs(fabs(z.x) - c);
						z.y = fabs(fabs(z.y) - c);
						z.z = fabs(fabs(z.z) - c);
						break;
					}
					case 19:
					{
						z.x = 2.0f * (z.x * 0.5f - floor(z.x * 0.5f + 0.5f));
						z.y = 2.0f * (z.y * 0.5f - floor(z.y * 0.5f + 0.5f));
						z.z = 2.0f * (z.z * 0.5f - floor(z.z * 0.5f + 0.5f));
						break;
					}
					case 20: { float c1 = mut->foldLimit; float c2 = -c1; z.x = fabs(z.x-c1)-fabs(z.x-c2); z.y = fabs(z.y-c1)-fabs(z.y-c2); z.z = fabs(z.z-c1)-fabs(z.z-c2); break; }
					case 21:
					{
						float r = native_sqrt(z.x*z.x + z.y*z.y); float theta = atan2(z.y, z.x);
						float foldR = mut->foldLimit;
						if (r > foldR) r = 2.0f*foldR - r; if (r < -foldR) r = -2.0f*foldR - r;
						z.x = r*native_cos(theta); z.y = r*native_sin(theta);
						aux.DE *= r / max(native_sqrt(z.x*z.x+z.y*z.y), 1e-21f); break;
					}
					case 22:
					{
						float lim = mut->foldLimit;
						if (z.x > lim) z.x = 2.0f*lim-z.x; else if (z.x < -lim) z.x = -2.0f*lim-z.x;
						if (z.y > lim) z.y = 2.0f*lim-z.y; else if (z.y < -lim) z.y = -2.0f*lim-z.y;
						z.x += mut->foldValue*z.y; z.y += mut->foldValue*z.z; break;
					}
					case 23:
					{
						float lim = mut->foldLimit; int phase = i % 3;
						if (phase == 0) {
							if (z.x > lim) z.x = 2.0f*lim-z.x; if (z.x < -lim) z.x = -2.0f*lim-z.x;
							if (z.y > lim) z.y = 2.0f*lim-z.y; if (z.y < -lim) z.y = -2.0f*lim-z.y;
						} else if (phase == 1) {
							if (z.y > lim) z.y = 2.0f*lim-z.y; if (z.y < -lim) z.y = -2.0f*lim-z.y;
							if (z.z > lim) z.z = 2.0f*lim-z.z; if (z.z < -lim) z.z = -2.0f*lim-z.z;
						} else {
							if (z.z > lim) z.z = 2.0f*lim-z.z; if (z.z < -lim) z.z = -2.0f*lim-z.z;
							if (z.x > lim) z.x = 2.0f*lim-z.x; if (z.x < -lim) z.x = -2.0f*lim-z.x;
						}
						break;
					}
					case 24:
					{
						float r2 = z.x*z.x+z.y*z.y+z.z*z.z;
						if (r2 > 1e-21f) { z.x += z.x/r2; z.y += z.y/r2; z.z += z.z/r2; aux.DE *= fabs(1.0f-1.0f/r2); }
						break;
					}
					case 25:
					{
						float lim = mut->foldLimit;
						if (z.x > lim) z.x = 2.0f*lim-z.x; if (z.x < -lim) z.x = -2.0f*lim-z.x;
						if (z.y > lim) z.y = 2.0f*lim-z.y; if (z.y < -lim) z.y = -2.0f*lim-z.y;
						if (z.z > lim) z.z = 2.0f*lim-z.z; if (z.z < -lim) z.z = -2.0f*lim-z.z;
						float t = z.x; z.x = -z.y; z.y = t; break;
					}
					case 26:
					{
						float lim = mut->foldLimit;
						if (z.x > lim) z.x = 2.0f*lim-z.x; if (z.x < -lim) z.x = -2.0f*lim-z.x;
						if (z.y > lim) z.y = 2.0f*lim-z.y; if (z.y < -lim) z.y = -2.0f*lim-z.y;
						if (z.z > lim) z.z = 2.0f*lim-z.z; if (z.z < -lim) z.z = -2.0f*lim-z.z;
						float pulse = 1.0f + 0.2f * native_sin((float)i * mut->foldValue);
						z *= pulse; aux.DE *= fabs(pulse); break;
					}
					case 27:
					{
						z.x = 2.0f * fabs(z.x*0.5f - floor(z.x*0.5f+0.5f));
						z.y = 2.0f * fabs(z.y*0.5f - floor(z.y*0.5f+0.5f));
						z.z = 2.0f * fabs(z.z*0.5f - floor(z.z*0.5f+0.5f));
						break;
					}
				}
			}

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
			if (mut->warpType == 1)
			{
				z.x += mut->warpAmplitude * native_sin(z.y * mut->warpFrequency);
				z.y += mut->warpAmplitude * native_sin(z.z * mut->warpFrequency);
				z.z += mut->warpAmplitude * native_sin(z.x * mut->warpFrequency);
			}
			else if (mut->warpType == 2)
			{
				float angle = z.z * mut->warpFrequency * M_PI_F / 180.0f;
				float ca = native_cos(angle * mut->warpAmplitude);
				float sa = native_sin(angle * mut->warpAmplitude);
				float nx = z.x * ca - z.y * sa; float ny = z.x * sa + z.y * ca;
				z.x = nx; z.y = ny;
			}
			else if (mut->warpType == 3)
			{
				float r = native_sqrt(z.x*z.x + z.y*z.y);
				float angle = r * mut->warpFrequency;
				float ca = native_cos(angle * mut->warpAmplitude);
				float sa = native_sin(angle * mut->warpAmplitude);
				float nx = z.x * ca - z.y * sa; float ny = z.x * sa + z.y * ca;
				z.x = nx; z.y = ny;
			}
			else if (mut->warpType == 4)
			{
				float r = native_sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
				if (r > 1e-21f)
				{
					float warp = mut->warpAmplitude * native_sin(r * mut->warpFrequency);
					z.x += z.x/r * warp; z.y += z.y/r * warp; z.z += z.z/r * warp;
				}
			}
			else if (mut->warpType == 5)
			{
				float r = native_sqrt(z.x*z.x + z.y*z.y);
				if (r > 1e-21f)
				{
					float angle = atan2(z.y, z.x);
					angle += mut->warpAmplitude * native_sin(z.z * mut->warpFrequency);
					z.x = r * native_cos(angle); z.y = r * native_sin(angle);
				}
			}
			else if (mut->warpType == 6)
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
			else if (mut->warpType == 7)
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
			else if (mut->warpType == 8)
			{
				float s0 = mut->warpAmplitude;
				float a = mut->warpFrequency;
				float s = s0 * (1.0f + a * native_sin((float)aux.i));
				z *= s;
				aux.DE = aux.DE * fabs(s) + 1.0f;
			}
			else if (mut->warpType == 9)
			{
				float goldenAngle = 2.399963229728653f;
				float angle = goldenAngle * aux.i * mut->warpAmplitude;
				float ca = native_cos(angle); float sa = native_sin(angle);
				float nx = z.x * ca - z.y * sa; float ny = z.x * sa + z.y * ca;
				z.x = nx; z.y = ny;
			}
			else if (mut->warpType == 10)
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
			else if (mut->warpType == 11)
			{
				z.x += mut->warpAmplitude * z.y;
				z.y += mut->warpFrequency * z.z;
			}

			} // end warp iteration range

			// Math injection (GPU Nebula, per-section iteration range)
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

		// v7.5 — Julia pre-fold injection (GPU Nebula, per-section iteration range)
		if (mutationActive
			&& i >= consts->sequence.mutationParams[sequence].juliaIterStart
			&& i < consts->sequence.mutationParams[sequence].juliaIterStop
			&& consts->sequence.mutationParams[sequence].juliaInjection != 0)
		{
			__constant sClFormulaMutationParams *jm = &consts->sequence.mutationParams[sequence];
			float4 juliaC = aux.const_c * jm->juliaCMul;
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
			}
			if (jm->juliaDynamic == 1) juliaC *= (1.0f + 0.1f * length(z));
			else if (jm->juliaDynamic == 2) juliaC *= native_sin((float)i * jm->juliaPulseFreq) * jm->juliaPulseAmp;
			else if (jm->juliaDynamic == 3) { if (length(z) > consts->sequence.bailout[sequence] * 0.5f) juliaC *= 2.0f; }
			else if (jm->juliaDynamic == 4) juliaC = juliaC * (1.0f - jm->juliaAbsorb) + z * jm->juliaAbsorb;
			else if (jm->juliaDynamic == 5) { float4 prevZ = (i > 0) ? zHistory[i-1] : z; juliaC = juliaC + (z - prevZ) * 0.1f; }
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
			if (jm->juliaInjection == 1 || jm->juliaInjection == 4) z += juliaC;
			else if (jm->juliaInjection == 5) {
				float r = length(z);
				float bail = consts->sequence.bailout[sequence];
				float factor = (bail > 1e-21f) ? r / bail : 1.0f;
				z += juliaC * factor;
			}
		}

#if defined(IS_HYBRID)
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
#else	 // not HYBRID
		z = FORMULA_ITER_0(z, fractal, &aux);
#endif // defined(IS_HYBRID)

		if (aux.r < 0.0f) // if was run DummyIteration
		{
			break;
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

		// v7.5 — Julia mid/post injection (GPU Nebula, per-section iteration range)
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

		// -------------- Formula Mutation post-processing (GPU Nebula) ---------------
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
					case 16:
					{
						float k = (mut->foldLimit > 0.0f) ? mut->foldLimit : 5.0f;
						z.x = z.x * tanh(k * z.x);
						z.y = z.y * tanh(k * z.y);
						z.z = z.z * tanh(k * z.z);
						break;
					}
					case 17:
					{
						float period = (mut->foldValue > 0.0f) ? mut->foldValue : 2.0f;
						z.x = fmod(z.x + period * 0.5f, period) - period * 0.5f;
						z.y = fmod(z.y + period * 0.5f, period) - period * 0.5f;
						z.z = fmod(z.z + period * 0.5f, period) - period * 0.5f;
						break;
					}
					case 18:
					{
						float c = (mut->foldLimit > 0.0f) ? mut->foldLimit : 1.0f;
						z.x = fabs(fabs(z.x) - c);
						z.y = fabs(fabs(z.y) - c);
						z.z = fabs(fabs(z.z) - c);
						break;
					}
					case 19:
					{
						z.x = 2.0f * (z.x * 0.5f - floor(z.x * 0.5f + 0.5f));
						z.y = 2.0f * (z.y * 0.5f - floor(z.y * 0.5f + 0.5f));
						z.z = 2.0f * (z.z * 0.5f - floor(z.z * 0.5f + 0.5f));
						break;
					}
					case 20: { float c1 = mut->foldLimit; float c2 = -c1; z.x = fabs(z.x-c1)-fabs(z.x-c2); z.y = fabs(z.y-c1)-fabs(z.y-c2); z.z = fabs(z.z-c1)-fabs(z.z-c2); break; }
					case 21:
					{
						float r = native_sqrt(z.x*z.x + z.y*z.y); float theta = atan2(z.y, z.x);
						float foldR = mut->foldLimit;
						if (r > foldR) r = 2.0f*foldR - r; if (r < -foldR) r = -2.0f*foldR - r;
						z.x = r*native_cos(theta); z.y = r*native_sin(theta);
						aux.DE *= r / max(native_sqrt(z.x*z.x+z.y*z.y), 1e-21f); break;
					}
					case 22:
					{
						float lim = mut->foldLimit;
						if (z.x > lim) z.x = 2.0f*lim-z.x; else if (z.x < -lim) z.x = -2.0f*lim-z.x;
						if (z.y > lim) z.y = 2.0f*lim-z.y; else if (z.y < -lim) z.y = -2.0f*lim-z.y;
						z.x += mut->foldValue*z.y; z.y += mut->foldValue*z.z; break;
					}
					case 23:
					{
						float lim = mut->foldLimit; int phase = i % 3;
						if (phase == 0) {
							if (z.x > lim) z.x = 2.0f*lim-z.x; if (z.x < -lim) z.x = -2.0f*lim-z.x;
							if (z.y > lim) z.y = 2.0f*lim-z.y; if (z.y < -lim) z.y = -2.0f*lim-z.y;
						} else if (phase == 1) {
							if (z.y > lim) z.y = 2.0f*lim-z.y; if (z.y < -lim) z.y = -2.0f*lim-z.y;
							if (z.z > lim) z.z = 2.0f*lim-z.z; if (z.z < -lim) z.z = -2.0f*lim-z.z;
						} else {
							if (z.z > lim) z.z = 2.0f*lim-z.z; if (z.z < -lim) z.z = -2.0f*lim-z.z;
							if (z.x > lim) z.x = 2.0f*lim-z.x; if (z.x < -lim) z.x = -2.0f*lim-z.x;
						}
						break;
					}
					case 24:
					{
						float r2 = z.x*z.x+z.y*z.y+z.z*z.z;
						if (r2 > 1e-21f) { z.x += z.x/r2; z.y += z.y/r2; z.z += z.z/r2; aux.DE *= fabs(1.0f-1.0f/r2); }
						break;
					}
					case 25:
					{
						float lim = mut->foldLimit;
						if (z.x > lim) z.x = 2.0f*lim-z.x; if (z.x < -lim) z.x = -2.0f*lim-z.x;
						if (z.y > lim) z.y = 2.0f*lim-z.y; if (z.y < -lim) z.y = -2.0f*lim-z.y;
						if (z.z > lim) z.z = 2.0f*lim-z.z; if (z.z < -lim) z.z = -2.0f*lim-z.z;
						float t = z.x; z.x = -z.y; z.y = t; break;
					}
					case 26:
					{
						float lim = mut->foldLimit;
						if (z.x > lim) z.x = 2.0f*lim-z.x; if (z.x < -lim) z.x = -2.0f*lim-z.x;
						if (z.y > lim) z.y = 2.0f*lim-z.y; if (z.y < -lim) z.y = -2.0f*lim-z.y;
						if (z.z > lim) z.z = 2.0f*lim-z.z; if (z.z < -lim) z.z = -2.0f*lim-z.z;
						float pulse = 1.0f + 0.2f * native_sin((float)i * mut->foldValue);
						z *= pulse; aux.DE *= fabs(pulse); break;
					}
					case 27:
					{
						z.x = 2.0f * fabs(z.x*0.5f - floor(z.x*0.5f+0.5f));
						z.y = 2.0f * fabs(z.y*0.5f - floor(z.y*0.5f+0.5f));
						z.z = 2.0f * fabs(z.z*0.5f - floor(z.z*0.5f+0.5f));
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

			
			// DE tweak (per-section iteration range)
			if (i >= mut->deIterStart && i < mut->deIterStop) {
			if (mut->deScale != 1.0f) aux.DE *= mut->deScale;
			if (mut->deTweak == 1) aux.DE = native_log(1.0f + fabs(aux.DE));
			else if (mut->deTweak == 2) aux.DE = native_exp(aux.DE) - 1.0f;
			else if (mut->deTweak == 3) { float noise = mut->deTweakP1 * native_sin(z.x*13.7f + z.y*7.3f + z.z*11.1f); aux.DE += noise; }
			else if (mut->deTweak == 4) { aux.DE *= (1.0f + mut->deTweakP1 * native_sin(mut->deTweakP2 * aux.dist)); }
			else if (mut->deTweak == 5) aux.DE *= 0.9f;
			else if (mut->deTweak == 6) aux.DE *= 1.1f;
			} // end DE iteration range

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
			if (aux.r > consts->sequence.bailout[sequence])
			{
				break;
			}
		}
	} // next i;

	if ((aux.i < MAX_ITERATIONS - 1 && consts->params.nebulaOuterEnabled)
			|| (aux.i == MAX_ITERATIONS - 1 && consts->params.nebulaInnerEnabled))
	{
		float3 camera = consts->params.camera;
		float3 target = consts->params.target;
		float3 top = consts->params.topVector;
		float fov = consts->params.fov;

		float3 forward = normalize(target - camera);
		float3 right = normalize(cross(forward, top));

		matrix33 rotationMatrix;
		rotationMatrix.m1.x = right.x;
		rotationMatrix.m1.y = right.y;
		rotationMatrix.m1.z = right.z;
		rotationMatrix.m2.x = top.x;
		rotationMatrix.m2.y = top.y;
		rotationMatrix.m2.z = top.z;
		rotationMatrix.m3.x = forward.x;
		rotationMatrix.m3.y = forward.y;
		rotationMatrix.m3.z = forward.z;

		int width = consts->params.imageWidth;
		int height = consts->params.imageHeight;
		float aspectRatio = (float)width / height;

		for (int i = consts->params.nebulaMinIteration; i < aux.i; i++)
		{
			z = zHistory[i];

			float distFromClipPlane1 = dot(z.xyz - camera, forward);

			if (distFromClipPlane1 > 0.0f)
			{
				float3 viewVector = z.xyz - camera;
				viewVector = Matrix33MulFloat3(rotationMatrix, viewVector);
				float zDepth = length(viewVector);

				viewVector.x /= viewVector.z;
				viewVector.y /= viewVector.z;

				float2 pointPersp;
				pointPersp.x = viewVector.x / fov;
				pointPersp.y = viewVector.y / fov;

				float2 screenPoint =
					(float2){(pointPersp.x / aspectRatio + 0.5f) * width, (-pointPersp.y + 0.5f) * height};

				int2 screenPointInt = (int2){(int)screenPoint.x, (int)screenPoint.y};

				if (screenPointInt.x >= 0 && screenPointInt.x < width && screenPointInt.y >= 0
						&& screenPointInt.y < height)
				{
					// write to output image
					int screenIndex = (int)(screenPointInt.x + screenPointInt.y * width);

#ifdef NEBULA_X_AXIS_COLORS
					float colorPosX =
						(limitMax.x != limitMin.x)
							? clamp((point.x - limitMin.x) / (limitMax.x - limitMin.x), 0.0f, 1.0f)
							: 0.5f;
					float3 gradientColorX = GetColorFromGradient(
						colorPosX, false, paletteLengthXAxis, gradients + paletteOffsetXAxis, NULL, 0, 0);
#else
#ifdef NEBULA_COLOR_MIXING_LIGHTEN
					float3 gradientColorX = (float3){0.0f, 0.0f, 0.0f};
#else
					float3 gradientColorX = (float3){1.0f, 1.0f, 1.0f};
#endif
#endif // NEBULA_X_AXIS_COLORS

#ifdef NEBULA_Y_AXIS_COLORS
					float colorPosY =
						(limitMax.y != limitMin.y)
							? clamp((point.y - limitMin.y) / (limitMax.y - limitMin.y), 0.0f, 1.0f)
							: 0.5f;
					float3 gradientColorY = GetColorFromGradient(
						colorPosY, false, paletteLengthYAxis, gradients + paletteOffsetYAxis, NULL, 0, 0);
#else
#ifdef NEBULA_COLOR_MIXING_LIGHTEN
					float3 gradientColorY = (float3){0.0f, 0.0f, 0.0f};
#else
					float3 gradientColorY = (float3){1.0f, 1.0f, 1.0f};
#endif
#endif // NEBULA_Y_AXIS_COLORS

#ifdef NEBULA_Z_AXIS_COLORS
					float colorPosZ =
						(limitMax.z != limitMin.z)
							? clamp((point.z - limitMin.z) / (limitMax.z - limitMin.z), 0.0f, 1.0f)
							: 0.5f;
					float3 gradientColorZ = GetColorFromGradient(
						colorPosZ, false, paletteLengthZAxis, gradients + paletteOffsetZAxis, NULL, 0, 0);
#else
#ifdef NEBULA_COLOR_MIXING_LIGHTEN
					float3 gradientColorZ = (float3){0.0f, 0.0f, 0.0f};
#else
					float3 gradientColorZ = (float3){1.0f, 1.0f, 1.0f};
#endif
#endif // NEBULA_Z_AXIS_COLORS

#ifdef NEBULA_ITERATIONS_COLORS
					float colorIterations = (float)(i - consts->params.nebulaMinIteration)
																	/ (float)(MAX_ITERATIONS - consts->params.nebulaMinIteration);
					float3 gradientColorIterations = GetColorFromGradient(
						colorIterations, false, paletteLengthIterations, gradients + paletteOffsetIterations, NULL, 0, 0);
#else
#ifdef NEBULA_COLOR_MIXING_LIGHTEN
					float3 gradientColorIterations = (float3){0.0f, 0.0f, 0.0f};
#else
					float3 gradientColorIterations = (float3){1.0f, 1.0f, 1.0f};
#endif
#endif // NEBULA_ITERATIONS_COLORS

					float3 color = 0.0f;

#ifdef NEBULA_COLOR_MIXING_LIGHTEN
					color = gradientColorX + gradientColorY + gradientColorZ + gradientColorIterations;
#endif
#ifdef NEBULA_COLOR_MIXING_DARKEN
					color = gradientColorX * gradientColorY * gradientColorZ * gradientColorIterations;
#endif
#ifdef NEBULA_COLOR_MIXING_DARKEN_BY_BRIGHTNESS
					{
						float luminanceX =
							0.3333f * (gradientColorX.s0 + gradientColorX.s1 + gradientColorX.s2);
						float luminanceY =
							0.3333f * (gradientColorY.s0 + gradientColorY.s1 + gradientColorY.s2);
						float luminanceZ =
							0.3333f * (gradientColorZ.s0 + gradientColorZ.s1 + gradientColorZ.s2);
						float luminanceIterations = 0.3333f
																				* (gradientColorIterations.s0 + gradientColorIterations.s1
																					 + gradientColorIterations.s2);
						float luminance = luminanceX * luminanceY * luminanceZ * luminanceIterations;
						color = luminance
										* (gradientColorX + gradientColorY + gradientColorZ + gradientColorIterations);
					}
#endif

					float4 old = inOutImage[screenIndex];
					float4 outPixel;
					outPixel.s0 = old.s0 + color.s0;
					outPixel.s1 = old.s1 + color.s1;
					outPixel.s2 = old.s2 + color.s2;
					outPixel.s3 = old.s3 + (zDepth - old.s3) * 0.01f; // depth averaging;
					inOutImage[screenIndex] = outPixel;
				}
			}
		}
	}
}

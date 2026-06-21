/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Bristorbrot V2 formula
 * @reference http://www.fractalforums.com/theory/bristorbrot-3d/
 * by Doug Bristor
 */

#include "all_fractal_definitions.h"

cFractalBristorbrot2::cFractalBristorbrot2() : cAbstractFractal()
{
	nameInComboBox = "Bristorbrot V2";
	internalName = "bristorbrot2";
	internalID = fractal::bristorbrot2;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalBristorbrot2::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	aux.DE = aux.DE * 2.0 * aux.r;

	CVector4 zOrig = z;
	CVector4 zz = z * z;
	CVector4 zNew = z;

	// pre abs
	CVector4 zFabs = fabs(z);
	if (fractal->buffalo.preabsx) zOrig.x = zFabs.x;
	if (fractal->buffalo.preabsy) zOrig.y = zFabs.y;
	if (fractal->buffalo.preabsz) zOrig.z = zFabs.z;

	// Bristorbrot V2 formula
	double signT = 1.0; // signT as "sign" is an operation   sign()

	// conditional operation which can create cuts
	if (fractal->transformCommon.functionEnabledFalse && zz.z >= zz.y)
		signT = -1.0; // creates fractal surface modification 2019

	// is preabs is used on z.x, it will be !< 0.0
	if (!fractal->buffalo.preabsy && fractal->transformCommon.functionEnabledxFalse && zOrig.x < 0.0)
		signT = -signT;

	// flips signT but same as using -1.0 scales
	if (fractal->transformCommon.functionEnabledAwFalse) signT = -signT;

	double tmpy = z.y;
	if (fractal->transformCommon.functionEnabledyFalse) tmpy = zFabs.y;
	double tmpz = z.z;
	if (fractal->transformCommon.functionEnabledzFalse) tmpz = zFabs.z;

	zNew.x = zz.x - zz.y - zz.z;
	zNew.y = zOrig.y * (zOrig.x * 2.0 - tmpz * signT * fractal->transformCommon.scaleB1);
	zNew.z = zOrig.z * (zOrig.x * 2.0 + tmpy * signT * fractal->transformCommon.scaleC1);
	z = zNew;

	// post abs
	z.x = fractal->buffalo.absx ? fabs(z.x) : z.x;
	z.y = fractal->buffalo.absy ? fabs(z.y) : z.y;
	z.z = fractal->buffalo.absz ? fabs(z.z) : z.z;

	// offset
	z += fractal->transformCommon.additionConstantA000;

	// analyticDE controls
	if (fractal->analyticDE.enabledFalse)
		aux.DE = aux.DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset1;
	// === General Purpose Multiplier 1 ===
	if (fractal->transformCommon.functionEnabledBxFalse
		&& aux.i >= fractal->transformCommon.startIterationsB
		&& aux.i < fractal->transformCommon.stopIterationsB)
	{
		double val = fractal->transformCommon.scale4;
		switch (fractal->transformCommon.multiplierMode1)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 2 ===
	if (fractal->transformCommon.functionEnabledByFalse
		&& aux.i >= fractal->transformCommon.startIterationsC
		&& aux.i < fractal->transformCommon.stopIterationsC)
	{
		double val = fractal->transformCommon.scale5;
		switch (fractal->transformCommon.multiplierMode2)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 3 ===
	if (fractal->transformCommon.functionEnabledBzFalse
		&& aux.i >= fractal->transformCommon.startIterationsD
		&& aux.i < fractal->transformCommon.stopIterationsD)
	{
		double val = fractal->transformCommon.scale6;
		switch (fractal->transformCommon.multiplierMode3)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 4 ===
	if (fractal->transformCommon.functionEnabledBwFalse
		&& aux.i >= fractal->transformCommon.startIterationsE
		&& aux.i < fractal->transformCommon.stopIterationsE)
	{
		double val = fractal->transformCommon.scale8;
		switch (fractal->transformCommon.multiplierMode4)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 5 ===
	if (fractal->transformCommon.functionEnabledCzFalse
		&& aux.i >= fractal->transformCommon.startIterationsF
		&& aux.i < fractal->transformCommon.stopIterationsF)
	{
		double val = fractal->transformCommon.scale16;
		switch (fractal->transformCommon.multiplierMode5)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

}

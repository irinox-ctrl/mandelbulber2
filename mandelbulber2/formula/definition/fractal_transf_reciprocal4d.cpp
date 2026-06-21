/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Reciprocal4D from M3D, DarkBeam's code
 * @reference
 * http://www.fractalforums.com/mandelbulb-3d/custom-formulas-and-transforms-release-t17106/
 */

#include "all_fractal_definitions.h"

cFractalTransfReciprocal4d::cFractalTransfReciprocal4d() : cAbstractFractal()
{
	nameInComboBox = "T>Reciprocal 4D";
	internalName = "transf_reciprocal4d";
	internalID = fractal::transfReciprocal4d;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfReciprocal4d::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 tempZ = z;

	if (fractal->transformCommon.functionEnabledx)
	{
		if (fractal->transformCommon.functionEnabledAx)
			tempZ.x = (1.0 / fractal->transformCommon.offset1111.x)
								- 1.0 / (fabs(z.x) + fractal->transformCommon.offset1111.x);

		if (fractal->transformCommon.functionEnabledAxFalse)
			tempZ.x = (fractal->transformCommon.offsetA1111.x)
								- 1.0 / (fabs(z.x) + fractal->transformCommon.offset1111.x);

		tempZ.x += fabs(z.x) * fractal->transformCommon.additionConstant0000.x; // function slope
		z.x = sign(z.x) * tempZ.x;
	}

	if (fractal->transformCommon.functionEnabledy)
	{
		if (fractal->transformCommon.functionEnabledAx)
			tempZ.y = (1.0 / fractal->transformCommon.offset1111.y)
								- 1.0 / (fabs(z.y) + fractal->transformCommon.offset1111.y);

		if (fractal->transformCommon.functionEnabledAxFalse)
			tempZ.y = (fractal->transformCommon.offsetA1111.y)
								- 1.0 / (fabs(z.y) + fractal->transformCommon.offset1111.y);

		tempZ.y += fabs(z.y) * fractal->transformCommon.additionConstant0000.y;
		z.y = sign(z.y) * tempZ.y;
	}

	if (fractal->transformCommon.functionEnabledz)
	{
		if (fractal->transformCommon.functionEnabledAx)
			tempZ.z = (1.0 / fractal->transformCommon.offset1111.z)
								- 1.0 / (fabs(z.z) + fractal->transformCommon.offset1111.z);

		if (fractal->transformCommon.functionEnabledAxFalse)
			tempZ.z = (fractal->transformCommon.offsetA1111.z)
								- 1.0 / (fabs(z.z) + fractal->transformCommon.offset1111.z);

		tempZ.z += fabs(z.z) * fractal->transformCommon.additionConstant0000.z;
		z.z = sign(z.z) * tempZ.z;
	}

	if (fractal->transformCommon.functionEnabledw)
	{
		if (fractal->transformCommon.functionEnabledAw)
			tempZ.w = (1.0 / fractal->transformCommon.offset1111.w)
								- 1.0 / (fabs(z.w) + fractal->transformCommon.offset1111.w);

		if (fractal->transformCommon.functionEnabledAwFalse)
			tempZ.w = (fractal->transformCommon.offsetA1111.w)
								- 1.0 / (fabs(z.w) + fractal->transformCommon.offset1111.w);

		tempZ.z += fabs(z.w) * fractal->transformCommon.additionConstant0000.w;
		z.z = sign(z.w) * tempZ.w;
	}

	aux.DE *= fractal->analyticDE.scale1; // DE tweak
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

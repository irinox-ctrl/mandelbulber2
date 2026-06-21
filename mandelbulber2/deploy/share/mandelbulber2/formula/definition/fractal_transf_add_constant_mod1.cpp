/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Adds c constant to z vector
 */

#include "all_fractal_definitions.h"

cFractalTransfAddConstantMod1::cFractalTransfAddConstantMod1() : cAbstractFractal()
{
	nameInComboBox = "T>Add Constant Mod1";
	internalName = "transf_add_constant_mod1";
	internalID = fractal::transfAddConstantMod1;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfAddConstantMod1::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	Q_UNUSED(aux);
	// std offset
	z += fractal->transformCommon.additionConstantA000;
	// polynomial
	if (fractal->transformCommon.functionEnabledBx
			&& aux.i >= fractal->transformCommon.startIterationsX
			&& aux.i < fractal->transformCommon.stopIterationsX)
	{
		CVector4 temp = fractal->transformCommon.additionConstant000;
		CVector4 temp2 = temp * temp;
		CVector4 z2 = z * z * fractal->transformCommon.scaleA1;
		z.x -= ((temp.x * temp2.x) / (z2.x + temp2.x) - 2.0 * temp.x) * fractal->transformCommon.scale1;
		z.y -= ((temp.y * temp2.y) / (z2.y + temp2.y) - 2.0 * temp.y) * fractal->transformCommon.scale1;
		z.z -= ((temp.z * temp2.z) / (z2.z + temp2.z) - 2.0 * temp.z) * fractal->transformCommon.scale1;
	}

	else if (fractal->transformCommon.functionEnabledByFalse
					 && aux.i >= fractal->transformCommon.startIterationsX
					 && aux.i < fractal->transformCommon.stopIterationsX)
	{
		CVector4 temp = fractal->transformCommon.additionConstant000;
		CVector4 temp2 = temp * temp;
		CVector4 z2 = z * z * fractal->transformCommon.scaleA1;

		z.x -= ((temp2.x) / (z2.x + temp2.x) - 2.0 * temp.x)
					 * fractal->transformCommon.scale1; // * sign(z.x);
		z.y -= ((temp2.y) / (z2.y + temp2.y) - 2.0 * temp.y)
					 * fractal->transformCommon.scale1; // * sign(z.y);
		z.z -= ((temp2.z) / (z2.z + temp2.z) - 2.0 * temp.z)
					 * fractal->transformCommon.scale1; // * sign(z.z);
	}
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

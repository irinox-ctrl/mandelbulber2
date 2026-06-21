/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Parabolic Fold by mclarekin
 */

#include "all_fractal_definitions.h"

cFractalTransfParabFold::cFractalTransfParabFold() : cAbstractFractal()
{
	nameInComboBox = "T>Parab Fold";
	internalName = "transf_parab_fold";
	internalID = fractal::transfParabFold;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfParabFold::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 temp = z;

	CVector4 slope2 = fractal->transformCommon.constantMultiplier111;
	CVector4 lengthAdd = fractal->transformCommon.additionConstant000;
	CVector4 factorP;

	factorP.x = -slope2.x / (lengthAdd.x * 2.0);
	factorP.y = -slope2.y / (lengthAdd.y * 2.0);
	factorP.z = -slope2.z / (lengthAdd.z * 2.0);
	factorP.w = 0.0;

	if (temp.x > 0)
	{
		if (temp.x < lengthAdd.x)
		{
			z.x = z.x * z.x * factorP.x;
		}
		else
		{
			z.x = (z.x - lengthAdd.x / 2.0) * slope2.x;
		}
	}
	if (temp.y > 0)
	{
		if (temp.y < lengthAdd.y)
		{
			z.y = z.y * z.y * factorP.y;
		}
		else
		{
			z.y = (z.y - lengthAdd.y / 2.0) * slope2.y;
		}
	}
	if (temp.z > 0)
	{
		if (temp.z < lengthAdd.z)
		{
			z.z = z.z * z.z * factorP.z;
		}
		else
		{
			z.z = (z.z - lengthAdd.z / 2.0) * slope2.z;
		}
	}

	if (temp.x < 0)
	{
		if (temp.x > -lengthAdd.x)
		{
			z.x = z.x * z.x * -factorP.x;
		}
		else
		{
			z.x = (z.x + lengthAdd.x / 2.0) * slope2.x;
		}
	}
	if (temp.y < 0)
	{
		if (temp.y > -lengthAdd.y)
		{
			z.y = z.y * z.y * -factorP.y;
		}
		else
		{
			z.y = (z.y + lengthAdd.y / 2.0) * slope2.y;
		}
	}

	if (temp.z < 0)
	{

		if (temp.z > -lengthAdd.z)
		{
			z.z = z.z * z.z * -factorP.z;
		}
		else
		{
			z.z = (z.z + lengthAdd.z / 2.0) * slope2.z;
		}
	}

	if (fractal->transformCommon.functionEnabledxFalse)
	{
		z = (z - temp) * fractal->transformCommon.scale3D111;
	}
	if (fractal->transformCommon.functionEnabledyFalse)
	{
		z = (z - temp) * temp * fractal->transformCommon.scale3D111;

		z.x = sign(temp.x) * z.x;
		z.y = sign(temp.y) * z.y;
		z.z = sign(temp.z) * z.z;
	}
	if (fractal->transformCommon.functionEnabledzFalse)
	{
		z = (z - temp) * temp * fractal->transformCommon.scale3D111;
	}

	if (fractal->analyticDE.enabled)
	{
		if (!fractal->analyticDE.enabledFalse)
			aux.DE = aux.DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;
		else
		{
			double avgScale = z.Length() / temp.Length();
			aux.DE = aux.DE * avgScale * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;
		}
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

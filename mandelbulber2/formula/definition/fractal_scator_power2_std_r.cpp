/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * quadratic iteration in real or imaginary scator algebra
 * using r = length
 * @reference
 * http://www.fractalforums.com/new-theories-and-research/
 * ix-possibly-the-holy-grail-fractal-%28in-fff-lore%29
 * https://luz.izt.uam.mx/drupal/en/fractals/ix
 * @author Manuel Fernandez-Guasti
 * This formula contains aux.DE
 */

#include "all_fractal_definitions.h"

cFractalScatorPower2StdR::cFractalScatorPower2StdR() : cAbstractFractal()
{
	nameInComboBox = "Scator Power 2 StdR";
	internalName = "scator_power2_std_r";
	internalID = fractal::scatorPower2StdR;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalScatorPower2StdR::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 oldZ = z;

	// Scator real enabled
	CVector4 zz = z * z;
	CVector4 newZ = z;
	if (fractal->transformCommon.functionEnabledFalse)
	{ // scator imaginary
		newZ.x = zz.x - zz.y - zz.z;
		newZ.y = z.x * z.y;
		newZ.z = z.x * z.z;
		newZ *= fractal->transformCommon.constantMultiplier122;
		newZ.x += (zz.y * zz.z) / zz.x;
		newZ.y *= (1.0 - zz.z / zz.x);
		newZ.z *= (1.0 - zz.y / zz.x);
	}
	else
	{ // scator real
		newZ.x = zz.x + zz.y + zz.z;
		newZ.y = z.x * z.y;
		newZ.z = z.x * z.z;
		newZ *= fractal->transformCommon.constantMultiplier122;
		newZ.x += (zz.y * zz.z) / zz.x;
		newZ.y *= (1.0 + zz.z / zz.x);
		newZ.z *= (1.0 + zz.y / zz.x);
	}
	z = newZ;

	if (fractal->analyticDE.enabled)
	{
		double r = aux.r; // r = length;
		double vecDE = 0.0;
		if (!fractal->analyticDE.enabledFalse)
		{
			if (fractal->transformCommon.functionEnabledXFalse)
			{
				r = sqrt(zz.x + zz.y + zz.z + (zz.y * zz.z) / zz.x);
			}
			aux.DE = r * aux.DE * 2.0 * fractal->analyticDE.scale1 + fractal->analyticDE.offset1;
		}
		else
		{
			vecDE = fractal->transformCommon.scaleA1 * z.Length() / oldZ.Length();
			aux.DE =
				max(r, vecDE) * aux.DE * 2.0 * fractal->analyticDE.scale1 + fractal->analyticDE.offset1;
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

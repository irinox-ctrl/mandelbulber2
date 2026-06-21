/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Box Fold 4d Inf (_FoldingInfy)
 * Continuous, seamless folding of 4D space. Boxtiling "enhanced" version.
 * from M3D. Baded on formula by Luca GN 2011,
 * @reference
 * http://www.fractalforums.com/mandelbulb-3d/custom-formulas-and-transforms-release-t17106/
 */

#include "all_fractal_definitions.h"

cFractalTransfBoxFold4dInfy::cFractalTransfBoxFold4dInfy() : cAbstractFractal()
{
	nameInComboBox = "T>Box Fold 4D Infy";
	internalName = "transf_box_fold4d_infy";
	internalID = fractal::transfBoxFold4dInfy;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfBoxFold4dInfy::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// CVector4 oldZ = z;
	CVector4 size = fractal->transformCommon.offset2222;
	CVector4 m = size * fractal->transformCommon.scale4;

	if (!fractal->transformCommon.functionEnabledFalse)
	{
		if (fractal->transformCommon.functionEnabledx && size.x != 0.0)
		{
			z.x -= round(z.x / m.x) * m.x;
			z.x = fabs(z.x + size.x) - fabs(z.x - size.x) - z.x;
		}
		if (fractal->transformCommon.functionEnabledyFalse && size.y != 0.0)
		{
			z.y -= round(z.y / m.y) * m.y;
			z.y = fabs(z.y + size.y) - fabs(z.y - size.y) - z.y;
		}
		if (fractal->transformCommon.functionEnabledzFalse && size.z != 0.0)
		{
			z.z -= round(z.z / m.z) * m.z;
			z.z = fabs(z.z + size.z) - fabs(z.z - size.z) - z.z;
		}
		if (fractal->transformCommon.functionEnabledwFalse && size.w != 0.0)
		{
			z.w -= round(z.w / m.w) * m.w;
			z.w = fabs(z.w + size.w) - fabs(z.w - size.w) - z.w;
		}
	}
	else
	{
		CVector4 repeatPos = fractal->transformCommon.offsetA1111 * 0.5;
		CVector4 repeatNeg = fractal->transformCommon.offsetB1111 * 0.5;

		if (fractal->transformCommon.functionEnabledx && (z.x < (repeatPos.x + 0.5f) * m.x - size.x)
				&& (z.x > (repeatNeg.x + 0.5f) * -m.x + size.x) && (size.x != 0.0f))
		{
			z.x -= round(z.x / m.x) * m.x;
			z.x = fabs(z.x + size.x) - fabs(z.x - size.x) - z.x;
		}
		if (fractal->transformCommon.functionEnabledyFalse && (z.y < (repeatPos.y + 0.5f) * m.y - size.y)
				&& (z.y > (repeatNeg.y + 0.5f) * -m.y + size.y) && (size.y != 0.0f))
		{
			z.y -= round(z.y / m.y) * m.y;
			z.y = fabs(z.y + size.y) - fabs(z.y - size.y) - z.y;
		}
		if (fractal->transformCommon.functionEnabledzFalse && (z.z < (repeatPos.z + 0.5f) * m.z - size.z)
				&& (z.z > (repeatNeg.z + 0.5f) * -m.z + size.z) && (size.z != 0.0f))
		{
			z.z -= round(z.z / m.z) * m.z;
			z.z = fabs(z.z + size.z) - fabs(z.z - size.z) - z.z;
		}
		if (fractal->transformCommon.functionEnabledwFalse && (z.w < (repeatPos.w + 0.5f) * m.w - size.w)
				&& (z.w > (repeatNeg.w + 0.5f) * -m.w + size.w) && size.w != 0.0f)
		{
			z.w -= round(z.w / m.w) * m.w;
			z.w = fabs(z.w + size.w) - fabs(z.w - size.w) - z.w;
		}
	}

	if (fractal->analyticDE.enabled)
	{
		aux.DE = aux.DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;
	}

	if (fractal->transformCommon.addCpixelEnabledFalse)
		aux.const_c = z;
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

/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * TransfSurfFoldMultiIteration
 * Based on amazing_surf_mod1 from Mandelbulb3D
 * This formula contains aux.color, analytic aux.DE and aux.r-dz
 */

#include "all_fractal_definitions.h"

cFractalTransfSurfFoldMulti::cFractalTransfSurfFoldMulti() : cAbstractFractal()
{
	nameInComboBox = "T>Surf Fold Multi";
	internalName = "transf_surf_fold_multi";
	internalID = fractal::transfSurfFoldMulti;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfSurfFoldMulti::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 oldZ = z;
	if (fractal->transformCommon.functionEnabledAx)
	{
		z.x = fabs(z.x + fractal->transformCommon.additionConstant111.x)
					- fabs(z.x - fractal->transformCommon.additionConstant111.x) - z.x;
		z.y = fabs(z.y + fractal->transformCommon.additionConstant111.y)
					- fabs(z.y - fractal->transformCommon.additionConstant111.y) - z.y;
	}

	if (fractal->transformCommon.functionEnabledAyFalse)
	{ // z = fold - fabs( fabs(z) - fold)
		z.x = fractal->transformCommon.additionConstant111.x
					- fabs(fabs(z.x) - fractal->transformCommon.additionConstant111.x);
		z.y = fractal->transformCommon.additionConstant111.y
					- fabs(fabs(z.y) - fractal->transformCommon.additionConstant111.y);
	}

	if (fractal->transformCommon.functionEnabledAzFalse)
	{
		z.x = fabs(z.x + fractal->transformCommon.additionConstant111.x);
		z.y = fabs(z.y + fractal->transformCommon.additionConstant111.y);
	}

	if (fractal->transformCommon.functionEnabledxFalse)
	{ // if z > limit) z =  Value -z,   else if z < limit) z = - Value - z,
		if (z.x > fractal->transformCommon.additionConstant111.x)
		{
			z.x = fractal->mandelbox.foldingValue - z.x;
//			aux.color += fractal->mandelbox.color.factor.x;
		}
		else if (z.x < -fractal->transformCommon.additionConstant111.x)
		{
			z.x = -fractal->mandelbox.foldingValue - z.x;
//			aux.color += fractal->mandelbox.color.factor.x;
		}
		if (z.y > fractal->transformCommon.additionConstant111.y)
		{
			z.y = fractal->mandelbox.foldingValue - z.y;
//			aux.color += fractal->mandelbox.color.factor.y;
		}
		else if (z.y < -fractal->transformCommon.additionConstant111.y)
		{
			z.y = -fractal->mandelbox.foldingValue - z.y;
//			aux.color += fractal->mandelbox.color.factor.y;
		}
	}

	if (fractal->transformCommon.functionEnabledyFalse)
	{ // z = fold2 - fabs( fabs(z + fold) - fold2) - fabs(fold)
		z.x = fractal->transformCommon.offset2
					- fabs(fabs(z.x + fractal->transformCommon.additionConstant111.x)
								 - fractal->transformCommon.offset2)
					- fractal->transformCommon.additionConstant111.x;
		z.y = fractal->transformCommon.offset2
					- fabs(fabs(z.y + fractal->transformCommon.additionConstant111.y)
								 - fractal->transformCommon.offset2)
					- fractal->transformCommon.additionConstant111.y;
	}
	aux.DE = aux.DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset0; // tweak

	if (fractal->foldColor.auxColorEnabledFalse
			&& aux.i >= fractal->foldColor.startIterationsA
				&& aux.i < fractal->foldColor.stopIterationsA)
	{
		double colorAdd = 0.0;
		CVector4 zCol = fabs(z - oldZ);

		if(!fractal->foldColor.auxColorEnabledAFalse)
		{
			if (zCol.x > 0.0)
				colorAdd += fractal->foldColor.difs0000.x * zCol.x;
			if (zCol.y > 0.0)
				colorAdd += fractal->foldColor.difs0000.y * zCol.y;
		}
		else
		{
			if (fabs(z.x) > fractal->transformCommon.additionConstant111.x)
			{
				colorAdd += fractal->foldColor.difs0000.x;
			}
			else
			{
				colorAdd += fractal->foldColor.difs0000.x
						* (1.0 - (fractal->transformCommon.additionConstant111.x
						   - fabs(z.x)) / fractal->transformCommon.additionConstant111.x);
			}

			if (fabs(z.y) > fractal->transformCommon.additionConstant111.y)
			{
				colorAdd += fractal->foldColor.difs0000.y;
			}
			else
			{
				colorAdd += fractal->foldColor.difs0000.y
						* (1.0 - (fractal->transformCommon.additionConstant111.y
								  - fabs(z.y)) / fractal->transformCommon.additionConstant111.y);
			}
		}

		aux.color += colorAdd;
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

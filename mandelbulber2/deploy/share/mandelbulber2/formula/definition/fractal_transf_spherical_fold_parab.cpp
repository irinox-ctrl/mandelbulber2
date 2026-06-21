/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * spherical fold Parab, coded by mclarekin
 * @reference
 * http://www.fractalforums.com/amazing-box-amazing-surf-and-variations/smooth-spherical-fold/msg101051/#new
 * This formula contains aux.color and aux.actualScaleA
 */

#include "all_fractal_definitions.h"

cFractalTransfSphericalFoldParab::cFractalTransfSphericalFoldParab() : cAbstractFractal()
{
	nameInComboBox = "T>Spherical Fold Parab";
	internalName = "transf_spherical_fold_parab";
	internalID = fractal::transfSphericalFoldParab;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfSphericalFoldParab::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	double m = 1.0;
	double rr;
	double colorAdd = 0.0;
	// spherical fold
	if (fractal->transformCommon.functionEnabledSFalse
			&& aux.i >= fractal->transformCommon.startIterationsS
			&& aux.i < fractal->transformCommon.stopIterationsS)
	{
		rr = z.Dot(z);
		double tempM = rr;
		m = fractal->transformCommon.maxMinR2factor;
		// if (r2 < 1e-21) r2 = 1e-21;
		if (rr < fractal->transformCommon.minR2p25)
		{
			if (fractal->transformCommon.functionEnabledAyFalse && m > tempM) m = tempM + (tempM - m);
			z *= m;
			aux.DE = aux.DE * m;
			colorAdd += fractal->mandelbox.color.factorSp1;
		}
		else if (rr < fractal->transformCommon.maxR2d1)
		{
			m = fractal->transformCommon.maxR2d1 / rr;
			if (fractal->transformCommon.functionEnabledAyFalse && m > tempM) m = tempM + (tempM - m);
			z *= m;
			aux.DE = aux.DE * m;
			colorAdd += fractal->mandelbox.color.factorSp2;
		}
	}
	if (aux.i >= fractal->transformCommon.startIterations
			&& aux.i < fractal->transformCommon.stopIterations)
	{
		rr = z.Dot(z);
		z += fractal->mandelbox.offset;
		z *= fractal->transformCommon.scale;
		aux.DE = aux.DE * fabs(fractal->transformCommon.scale) + 1.0;
		double maxScale = fractal->transformCommon.scale4;
		double midPoint = (maxScale - 1.0) * 0.5;
		rr += fractal->transformCommon.offset0;
		double maxR2 = fractal->transformCommon.scale1;
		double halfMax = maxR2 * 0.5;
		double factor = midPoint / (halfMax * halfMax);

		double tempM = rr + fractal->transformCommon.offsetA0;
		if (rr < halfMax)
		{
			if (!fractal->transformCommon.functionEnabledOFalse) m = maxScale - (rr * rr) * factor;
			else m = 1.0 + (maxR2 - rr) * (maxR2 - rr) * factor;
			if (fractal->transformCommon.functionEnabledAxFalse && m > tempM) m = tempM + (tempM - m);
			z *= m;
			aux.DE = aux.DE * m;
			colorAdd += fractal->mandelbox.color.factorSp1;
		}
		else if (rr < maxR2)
		{
			m = 1.0 + (maxR2 - rr) * (maxR2 - rr) * factor;
			if (fractal->transformCommon.functionEnabledAxFalse && m > tempM) m = tempM + (tempM - m);
			z *= m;
			aux.DE = aux.DE * m;
			colorAdd += fractal->mandelbox.color.factorSp2;

			// z -= fractal->mandelbox.offset; //  fixed v2.32
		}
		z -= fractal->mandelbox.offset;
	}

	double useScale = fractal->transformCommon.scaleA1;
	if (fractal->transformCommon.functionEnabledXFalse)
	{
		if (aux.i >= fractal->transformCommon.startIterationsA
			&& aux.i < fractal->transformCommon.stopIterationsA)
		{
			useScale += aux.actualScaleA;
			z *= useScale;

			aux.DE = aux.DE * fabs(useScale) * fractal->analyticDE.scale1 + fractal->analyticDE.offset1;

			// update actualScale for next iteration
			double vary = fractal->transformCommon.scaleVary0
										* (fabs(aux.actualScaleA) - fractal->transformCommon.scaleB1);
			if (fractal->transformCommon.functionEnabledMFalse)
				aux.actualScaleA = -vary;
			else
				aux.actualScaleA = aux.actualScaleA - vary;
		}
		else
		{
			if (!fractal->transformCommon.functionEnabledYFalse)
			{
				z *= useScale;
				aux.DE = aux.DE * fabs(useScale) * fractal->analyticDE.scale1 + fractal->analyticDE.offset1;
			}
		}
	}
	else
	{
		z *= useScale;
		aux.DE = aux.DE * fabs(useScale) * fractal->analyticDE.scale1 + fractal->analyticDE.offset1;
	}

	if (fractal->foldColor.auxColorEnabledFalse && aux.i >= fractal->foldColor.startIterationsA
			&& aux.i < fractal->foldColor.stopIterationsA)
	{
		colorAdd += fractal->foldColor.difs0000.x * m;
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

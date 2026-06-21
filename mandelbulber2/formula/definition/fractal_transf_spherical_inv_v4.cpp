/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * spherical invert v4
 * from M3D. Baded on formula by Luca GN 2011, updated May 2012.
 * @reference
 * http://www.fractalforums.com/mandelbulb-3d/custom-formulas-and-transforms-release-t17106/
 */

#include "all_fractal_definitions.h"

cFractalTransfSphericalInvV4::cFractalTransfSphericalInvV4() : cAbstractFractal()
{
	nameInComboBox = "T>Spherical Invert V4";
	internalName = "transf_spherical_inv_v4";
	internalID = fractal::transfSphericalInvV4;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfSphericalInvV4::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 oldZ = z;
	double RR = 1.0;
	z += fractal->mandelbox.offset;
	z *= fractal->transformCommon.scale;
	aux.DE = aux.DE * fabs(fractal->transformCommon.scale) + 1.0;

	if (!fractal->transformCommon.functionEnabledyFalse) RR = z.Dot(z);
	else RR = oldZ.Dot(oldZ);
	double mde = RR;

	if (fractal->transformCommon.functionEnabledPFalse
			&& aux.i >= fractal->transformCommon.startIterationsP
			&& aux.i < fractal->transformCommon.stopIterationsP1)
	{
		mde = 1.0 / mde;
		z *= mde;
		aux.DE *= mde;
	}

	if (fractal->transformCommon.functionEnabled
			&& aux.i >= fractal->transformCommon.startIterationsC
			&& aux.i < fractal->transformCommon.stopIterationsC1)
	{
		z += fractal->transformCommon.offset000;
		double mn = fractal->transformCommon.minR0;

		// modes
		if (fractal->transformCommon.functionEnabledFalse) // Mode 1
		{
			if (RR < fractal->transformCommon.minR0)
				mde = mn;
		}

		if (fractal->transformCommon.functionEnabledAFalse) // Mode 2
		{
			if (RR < fractal->mandelbox.foldingSphericalFixed)
				mde = mn;
		}

		if (fractal->transformCommon.functionEnabledBFalse) // Mode 3
		{
			if (RR < fractal->mandelbox.foldingSphericalFixed && RR > fractal->transformCommon.minR0)
				mde = mn;
			else if (RR > fractal->mandelbox.foldingSphericalFixed) mde = fractal->mandelbox.foldingSphericalFixed / RR;
		}

		if (fractal->transformCommon.functionEnabledFFalse) // Mode 6
		{
			if (RR < fractal->mandelbox.foldingSphericalFixed && RR > fractal->transformCommon.minR0)
				mde = mn;
			else if (RR > fractal->mandelbox.foldingSphericalFixed) mde = RR / fractal->mandelbox.foldingSphericalFixed;
		}

		if (fractal->transformCommon.functionEnabledDFalse) // Mode 5
		{
			if (RR > fractal->transformCommon.minR0)
				mde = mn;
		}

		if (fractal->transformCommon.functionEnabledCFalse) // Mode 4
		{
			if (RR < fractal->transformCommon.minR0) mde = mn;
			if (RR > fractal->mandelbox.foldingSphericalFixed) mde = fractal->mandelbox.foldingSphericalFixed;
		}

		mde = 1.0 / mde;
		z *= mde;
		aux.DE *= fabs(mde);
		z -= fractal->transformCommon.offset000;

	}
	z -= fractal->mandelbox.offset + fractal->transformCommon.additionConstant000;

	if (fractal->analyticDE.enabledFalse)
	{
		aux.DE = aux.DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;
	}

	// color added v2.32
	if (fractal->foldColor.auxColorEnabledFalse && aux.i >= fractal->foldColor.startIterationsA
			&& aux.i < fractal->foldColor.stopIterationsA)
	{
		double addCol = 0.0f;
		addCol += fractal->foldColor.difs0000.x * mde;
		if (RR > fractal->mandelbox.foldingSphericalFixed) addCol += fractal->foldColor.difs0000.y;
		if (RR < fractal->transformCommon.minR0) addCol += fractal->foldColor.difs0000.z;

	//	aux.color = addCol;

		aux.color += addCol;
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

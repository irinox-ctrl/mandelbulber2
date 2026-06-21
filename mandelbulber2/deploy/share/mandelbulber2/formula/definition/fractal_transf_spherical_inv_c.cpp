/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * inverted sphere z & c- A transform from M3D
 * @reference
 * http://www.fractalforums.com/mandelbulb-3d/custom-formulas-and-transforms-release-t17106/
 * updated v2.12
 */

#include "all_fractal_definitions.h"

cFractalTransfSphericalInvC::cFractalTransfSphericalInvC() : cAbstractFractal()
{
	nameInComboBox = "T>Spherical Invert C";
	internalName = "transf_spherical_inv_c";
	internalID = fractal::transfSphericalInvC;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelAlreadyHas;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfSphericalInvC::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	double rSqrL;
	CVector4 tempC;
if (!fractal->transformCommon.functionEnabledFalse)
	{
	 tempC = aux.const_c;
		tempC *= fractal->transformCommon.constantMultiplier111;
		rSqrL = tempC.Dot(tempC);
		// if (rSqrL < 1e-21) rSqrL = 1e-21;
		rSqrL = 1.0 / rSqrL;
		tempC *= rSqrL;
	}
	else
	{
		tempC = aux.c;
		if (!fractal->transformCommon.functionEnabledAFalse)
		{
			tempC *= fractal->transformCommon.constantMultiplier111;
			rSqrL = tempC.Dot(tempC);
			// if (rSqrL < 1e-21) rSqrL = 1e-21;
			rSqrL = 1.0 / rSqrL;
			tempC *= rSqrL;
			aux.c = tempC;
		}
		else
		{
			rSqrL = tempC.Dot(tempC);
			// if (rSqrL < 1e-21) rSqrL = 1e-21;
			rSqrL = 1.0 / rSqrL;
			tempC *= rSqrL;
			aux.c = tempC;
			tempC *= fractal->transformCommon.constantMultiplier111;
		}
	}

	if (fractal->transformCommon.functionEnabledAwFalse)
	{
		rSqrL = z.Dot(z);
		// if (rSqrL < 1e-21) rSqrL = 1e-21;
		rSqrL = 1.0 / rSqrL;
		z *= rSqrL;
		aux.DE *= rSqrL;
		z += tempC;
	}
	z += tempC;
	// === General Purpose Multiplier 1 ===
	if (fractal->transformCommon.functionEnabledBxFalse
		&& aux.i >= fractal->transformCommon.startIterationsB
		&& aux.i < fractal->transformCommon.stopIterationsB)
	{
		z *= fractal->transformCommon.scale4;
		aux.DE *= fabs(fractal->transformCommon.scale4);
	}

	// === General Purpose Multiplier 2 ===
	if (fractal->transformCommon.functionEnabledByFalse
		&& aux.i >= fractal->transformCommon.startIterationsC
		&& aux.i < fractal->transformCommon.stopIterationsC)
	{
		z *= fractal->transformCommon.scale5;
		aux.DE *= fabs(fractal->transformCommon.scale5);
	}

	// === General Purpose Multiplier 3 ===
	if (fractal->transformCommon.functionEnabledBzFalse
		&& aux.i >= fractal->transformCommon.startIterationsD
		&& aux.i < fractal->transformCommon.stopIterationsD)
	{
		z *= fractal->transformCommon.scale6;
		aux.DE *= fabs(fractal->transformCommon.scale6);
	}

	// === General Purpose Multiplier 4 ===
	if (fractal->transformCommon.functionEnabledBwFalse
		&& aux.i >= fractal->transformCommon.startIterationsE
		&& aux.i < fractal->transformCommon.stopIterationsE)
	{
		z *= fractal->transformCommon.scale8;
		aux.DE *= fabs(fractal->transformCommon.scale8);
	}

	// === General Purpose Multiplier 5 ===
	if (fractal->transformCommon.functionEnabledCzFalse
		&& aux.i >= fractal->transformCommon.startIterationsF
		&& aux.i < fractal->transformCommon.stopIterationsF)
	{
		z *= fractal->transformCommon.scale16;
		aux.DE *= fabs(fractal->transformCommon.scale16);
	}

}

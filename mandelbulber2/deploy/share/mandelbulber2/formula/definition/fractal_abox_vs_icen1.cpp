/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * ABoxVS_icen1, a formula from Mandelbulb3D.
 * Inspired from a 2D formula proposed by Kali at Fractal Forums
 * @reference
 * http://www.fractalforums.com/new-theories-and-research/kaliset-plus-boxfold-nice-new-2d-fractal/msg33670/#new
 * This formula contains aux.color and aux.actualScale
 */

#include "all_fractal_definitions.h"

cFractalAboxVSIcen1::cFractalAboxVSIcen1() : cAbstractFractal()
{
	nameInComboBox = "Abox - VS icen1";
	internalName = "abox_vs_icen1";
	internalID = fractal::aboxVSIcen1;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalAboxVSIcen1::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	aux.actualScale =
		fractal->mandelbox.scale + fractal->mandelboxVary4D.scaleVary * (fabs(aux.actualScale) - 1.0);
	CVector4 c = aux.const_c;
	CVector4 oldZ = z;
	z.x = fabs(z.x + fractal->transformCommon.additionConstant111.x)
				- fabs(z.x - fractal->transformCommon.additionConstant111.x) - z.x;
	z.y = fabs(z.y + fractal->transformCommon.additionConstant111.y)
				- fabs(z.y - fractal->transformCommon.additionConstant111.y) - z.y;
	z.z = fabs(z.z + fractal->transformCommon.additionConstant111.z)
				- fabs(z.z - fractal->transformCommon.additionConstant111.z) - z.z;
	if (z.x != oldZ.x) aux.color += fractal->mandelbox.color.factor.x;
	if (z.y != oldZ.y) aux.color += fractal->mandelbox.color.factor.y;
	if (z.z != oldZ.z) aux.color += fractal->mandelbox.color.factor.z;

	if (fractal->transformCommon.juliaMode)
	{
		z += c * fractal->transformCommon.constantMultiplier111;
	}
	else
	{
		z += fractal->transformCommon.juliaC;
	}

	double rr = z.Dot(z);
	// if (r2 < 1e-21 && r2 > -1e-21)
	//	r2 = (r2 > 0) ? 1e-21 : -1e-21;
	if (rr < fractal->mandelbox.mR2)
	{
		z *= fractal->mandelbox.mboxFactor1;
		aux.DE *= fractal->mandelbox.mboxFactor1;
		aux.color += fractal->mandelbox.color.factorSp1;
	}
	else if (rr < fractal->mandelbox.fR2)
	{
		double tglad_factor2 = fractal->mandelbox.fR2 / rr;
		z *= tglad_factor2;
		aux.DE *= tglad_factor2;
		aux.color += fractal->mandelbox.color.factorSp2;
	}

	z *= aux.actualScale; // aux.actualScale;
	aux.DE = aux.DE * fabs(aux.actualScale) + 1.0;

	if (fractal->transformCommon.rotationEnabled && aux.i >= fractal->transformCommon.startIterations
			&& aux.i < fractal->transformCommon.stopIterations)
	{
		z = fractal->transformCommon.rotationMatrix.RotateVector(z);
	}

	if (fractal->transformCommon.juliaMode)
	{
		z += fractal->transformCommon.juliaC - c * fractal->transformCommon.constantMultiplier111;
	}
	else
	{
		z += c * fractal->transformCommon.constantMultiplier111 + fractal->transformCommon.juliaC;
	}
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

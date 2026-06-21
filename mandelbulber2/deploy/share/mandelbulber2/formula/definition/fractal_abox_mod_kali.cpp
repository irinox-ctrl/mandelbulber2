/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * ABoxModKali, a formula from Mandelbulb3D
 * @reference http://www.fractalforums.com/new-theories-and-research/aboxmodkali-the-2d-version/
 */

#include "all_fractal_definitions.h"

cFractalAboxModKali::cFractalAboxModKali() : cAbstractFractal()
{
	nameInComboBox = "Abox - Mod Kali";
	internalName = "abox_mod_kali";
	internalID = fractal::aboxModKali;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionIFS;
}

void cFractalAboxModKali::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// 3D Rotation
	if (fractal->mandelbox.mainRotationEnabled)
	{
		CVector4 tempVC = CVector4(fractal->mandelbox.rotationMain, 0.0); // constant to be varied
		if (fractal->transformCommon.functionEnabledPFalse)
		{
			if (aux.i >= fractal->transformCommon.startIterations
					&& aux.i < fractal->transformCommon.stopIterations
					&& (fractal->transformCommon.stopIterations - fractal->transformCommon.startIterations
							!= 0))
			{
				double iterationRange =
					fractal->transformCommon.stopIterations - fractal->transformCommon.startIterations;
				double currentIteration = (aux.i - fractal->transformCommon.startIterations);
				tempVC += fractal->transformCommon.offset000 * currentIteration / iterationRange;
			}

			if (aux.i >= fractal->transformCommon.stopIterations)
			{
				tempVC += tempVC + fractal->transformCommon.offset000;
			}
		}

		tempVC *= M_PI_180;

		if (tempVC.x != 0.0) z = z.RotateAroundVectorByAngle(CVector3(1.0, 0.0, 0.0), tempVC.x);
		if (tempVC.y != 0.0) z = z.RotateAroundVectorByAngle(CVector3(0.0, 1.0, 0.0), tempVC.y);
		if (tempVC.z != 0.0) z = z.RotateAroundVectorByAngle(CVector3(0.0, 0.0, 1.0), tempVC.z);
	}

	z = fractal->transformCommon.additionConstant0555 - fabs(z);
	double rr = z.Dot(z);
	double MinR = fractal->transformCommon.minR06;
	double dividend = rr < MinR ? MinR : min(rr, 1.0);
	double m = fractal->transformCommon.scale015 / dividend;
	z = z * m;
	aux.DE = aux.DE * fabs(m) + 1.0;

	// color added v2.32
	if (fractal->foldColor.auxColorEnabledFalse && aux.i >= fractal->foldColor.startIterationsA
			&& aux.i < fractal->foldColor.stopIterationsA)
	{
		aux.color += fractal->foldColor.difs0000.x * dividend;
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

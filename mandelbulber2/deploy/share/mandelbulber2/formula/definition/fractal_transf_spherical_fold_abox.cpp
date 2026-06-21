/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * spherical fold ABox
 * from Fractal Forums and M3D
 * @reference
 * http://www.fractalforums.com/mandelbulb-3d/custom-formulas-and-transforms-release-t17106/
 * This formula contains aux.color
 */

#include "all_fractal_definitions.h"

cFractalTransfSphericalFoldAbox::cFractalTransfSphericalFoldAbox() : cAbstractFractal()
{
	nameInComboBox = "T>Spherical Fold ABox";
	internalName = "transf_spherical_fold_abox";
	internalID = fractal::transfSphericalFoldAbox;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfSphericalFoldAbox::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	double r2 = z.Dot(z);
	z += fractal->mandelbox.offset;
	double sqrtMinR = fractal->transformCommon.sqtR;
	if (r2 < sqrtMinR)
	{
		z *= fractal->transformCommon.mboxFactor1;
		aux.DE *= fractal->transformCommon.mboxFactor1;
		if (fractal->foldColor.auxColorEnabledFalse)
		{
			aux.color += fractal->mandelbox.color.factorSp1;
		}
	}
	else if (r2 < 1.0)
	{
		z *= 1.0 / r2;
		aux.DE *= 1.0 / r2;
		if (fractal->foldColor.auxColorEnabledFalse)
		{
			aux.color += fractal->mandelbox.color.factorSp2;
		}
	}
	z -= fractal->mandelbox.offset;
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

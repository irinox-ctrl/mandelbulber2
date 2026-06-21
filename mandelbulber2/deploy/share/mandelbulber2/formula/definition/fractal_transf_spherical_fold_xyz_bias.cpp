/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * spherical fold XYZ Bias
 * deforms the MinR2 condition
 * This formula contains aux.color
 */

#include "all_fractal_definitions.h"

cFractalTransfSphericalFoldXYZBias::cFractalTransfSphericalFoldXYZBias() : cAbstractFractal()
{
	nameInComboBox = "T>Spherical Fold XYZ Bias";
	internalName = "transf_spherical_fold_xyz_bias";
	internalID = fractal::transfSphericalFoldXYZBias;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfSphericalFoldXYZBias::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 xyzBias;
	double minR2 = fractal->transformCommon.minR2p25;
	double MaxR2 = fractal->transformCommon.maxR2d1;
	double m = fractal->transformCommon.scale;

	if (aux.i >= fractal->transformCommon.startIterationsA
			&& aux.i < fractal->transformCommon.stopIterationsA)
	{
		xyzBias = fabs(aux.c) * fractal->transformCommon.constantMultiplier000;
		minR2 = minR2 + (xyzBias.x + xyzBias.y + xyzBias.z);
	}

	if (fractal->transformCommon.functionEnabledFalse
			&& aux.i >= fractal->transformCommon.startIterationsB
			&& aux.i < fractal->transformCommon.stopIterationsB)
	{
		CVector4 cSquared = aux.c * aux.c;
		xyzBias = cSquared * fractal->transformCommon.scale3D000;
		minR2 = minR2 + (xyzBias.x + xyzBias.y + xyzBias.z);
	}

	if (fractal->transformCommon.functionEnabled && minR2 > MaxR2)
	{
		minR2 = MaxR2; // stop overlapping potential
	}

	double rr = z.Dot(z);
	z += fractal->transformCommon.offset000;

	double colorAdd = 0.0;
	if (rr < minR2)
	{
		m *= fractal->transformCommon.maxR2d1 / minR2;
		colorAdd += fractal->mandelbox.color.factorSp1;
	}
	else if (rr < fractal->transformCommon.maxR2d1)
	{
		m *= fractal->transformCommon.maxR2d1 / rr;
		colorAdd += fractal->mandelbox.color.factorSp2;
	}

	z -= fractal->transformCommon.offset000;

	z *= m;
	aux.DE = aux.DE * fabs(m) + 1.0;

	if (fractal->foldColor.auxColorEnabledFalse)
	{
		colorAdd += fractal->foldColor.difs0000.x * m;
		aux.color += colorAdd;
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

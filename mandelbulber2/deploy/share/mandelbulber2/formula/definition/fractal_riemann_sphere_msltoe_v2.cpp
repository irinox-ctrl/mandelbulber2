/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * RiemannSphereMsltoe Version2
 * @reference
 * http://www.fractalforums.com/theory/alternate-co-ordinate-systems/msg11688/#msg11688
 */

#include "all_fractal_definitions.h"

cFractalRiemannSphereMsltoeV2::cFractalRiemannSphereMsltoeV2() : cAbstractFractal()
{
	nameInComboBox = "Riemann - Sphere Msltoe V2";
	internalName = "riemann_sphere_msltoe_v2";
	internalID = fractal::riemannSphereMsltoeV2;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalRiemannSphereMsltoeV2::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	double theta = 0.0;
	double phi = 0.0;
	double rx;
	double rz;
	double r = aux.r;

	// rotate
	if (fractal->transformCommon.rotationEnabled)
		z = fractal->transformCommon.rotationMatrix.RotateVector(z);
	// invert and scale
	z *= fractal->transformCommon.scale08 / r;

	// if (fabs(z.x) < 1e-21) z.x = 1e-21;
	// if (fabs(z.z) < 1e-21) z.z = 1e-21;

	rx = z.x / (z.y - 1.0);
	theta = 8.0 * atan2(2.0 * rx, rx * rx - 1.0);
	rz = z.z / (z.y - 1.0);
	phi = 8.0 * atan2(2.0 * rz, rz * rz - 1.0);

	theta *= fractal->transformCommon.scaleA1;
	phi *= fractal->transformCommon.scaleB1;

	rx = sin(theta) / (1.0 + cos(theta));
	rz = sin(phi) / (1.0 + cos(phi));
	double rXZ = rx * rx + rz * rz;
	double d = 2.0 / (rXZ + 1.0);

	double a1 = rx * d;
	double b1 = (rXZ - 1.0) * 0.5 * d;
	double c1 = rz * d;

	double rrrr = r * r * r * r;

	z.x = a1 * rrrr;
	z.y = b1 * rrrr;
	z.z = c1 * rrrr;

	z += fractal->transformCommon.offset010;

	if (fractal->analyticDE.enabled)
	{
		aux.DE *= 8.0 * fractal->transformCommon.scale08 * z.Length() / r;
		aux.DE = aux.DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset1;
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

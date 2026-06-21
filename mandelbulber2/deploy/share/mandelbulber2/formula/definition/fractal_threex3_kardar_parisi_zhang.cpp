/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Kardar-Parisi-Zhang.
 * Math: h_t = nu*h_xx + lambda/2*(h_x)² + eta
 */

#include "all_fractal_definitions.h"

cFractalThreex3KardarParisiZhang::cFractalThreex3KardarParisiZhang() : cAbstractFractal()
{
	nameInComboBox = "3x3 V290 Kardar-Parisi-Zhang";
	internalName = "threex3_kardar_parisi_zhang";
	internalID = fractal::threex3KardarParisiZhang;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3KardarParisiZhang::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Kardar-Parisi-Zhang: h_t = nu*h_xx + lambda/2*(h_x)² + eta
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Statistical: Boltzmann-inspired energy landscape
	double beta = fractal->transformCommon.scale1;
	if (beta < 0.01) beta = 1.0;
	double energy = z.x * z.x + z.y * z.y + z.z * z.z;
	double boltz = exp(-beta * energy * 0.01);
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	double rp = pow(r, power) * (1.0 + fractal->transformCommon.offset0 * boltz * 0.1);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
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

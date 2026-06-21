/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Sierpinski-pijlpunt fractaal.
 * Math: z = arrowhead_transform(z, direction) + c
 */

#include "all_fractal_definitions.h"

cFractalThreex3SierpinskiArrowheadFractal::cFractalThreex3SierpinskiArrowheadFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V378 Sierpinski Arrowhead Fractal";
	internalName = "threex3_sierpinski_arrowhead_fractal";
	internalID = fractal::threex3SierpinskiArrowheadFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3SierpinskiArrowheadFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Sierpinski Arrowhead Fractal: z = arrowhead_transform(z, direction) + c
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// L-system: branch-and-rotate
	double angle = fractal->transformCommon.scale1 * M_PI / 6.0;
	if (angle == 0.0) angle = M_PI / 6.0;
	double ca = cos(angle); double sa = sin(angle);
	// Apply rotation based on iteration parity
	if (aux.i % 2 == 0) {
		double tmp = z.x * ca - z.y * sa;
		z.y = z.x * sa + z.y * ca;
		z.x = tmp;
	} else {
		double tmp = z.y * ca - z.z * sa;
		z.z = z.y * sa + z.z * ca;
		z.y = tmp;
	}
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	double rp = pow(r, power);
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

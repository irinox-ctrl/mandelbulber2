/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Cellulaire automaat fractaal.
 * Math: z = rule(z_neighbors) + c met elementaire regel
 */

#include "all_fractal_definitions.h"

cFractalThreex3CellularAutomatonFractal::cFractalThreex3CellularAutomatonFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V363 Cellular Automaton Fractal";
	internalName = "threex3_cellular_automaton_fractal";
	internalID = fractal::threex3CellularAutomatonFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3CellularAutomatonFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Cellular Automaton Fractal: z = rule(z_neighbors) + c met elementaire regel
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Cellular automaton: rule-based folding
	double rule = fractal->transformCommon.scale1;
	if (rule < 1.0) rule = 30.0;
	double threshold = fractal->transformCommon.offset0;
	if (threshold == 0.0) threshold = 0.5;
	// Fold based on threshold
	if (z.x > threshold) z.x = 2.0 * threshold - z.x;
	if (z.x < -threshold) z.x = -2.0 * threshold - z.x;
	if (z.y > threshold) z.y = 2.0 * threshold - z.y;
	if (z.y < -threshold) z.y = -2.0 * threshold - z.y;
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

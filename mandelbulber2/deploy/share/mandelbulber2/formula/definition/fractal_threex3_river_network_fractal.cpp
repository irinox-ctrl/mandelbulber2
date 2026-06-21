/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Rivier-netwerk fractaal.
 * Math: optimal_drainage + erosion
 */

#include "all_fractal_definitions.h"

cFractalThreex3RiverNetworkFractal::cFractalThreex3RiverNetworkFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V467 River Network Fractal";
	internalName = "threex3_river_network_fractal";
	internalID = fractal::threex3RiverNetworkFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3RiverNetworkFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// River Network Fractal: optimal_drainage + erosion
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Biological: branching tree pattern
	double branchAngle = fractal->transformCommon.scale1;
	if (branchAngle < 0.01) branchAngle = 0.5;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Branch perturbation based on radius
	double branch = branchAngle * sin(3.0 * th) * cos(5.0 * ph) * exp(-r * 0.1);
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th + branch) * cos(ph) * rp;
	z.y = cos(th + branch) * sin(ph) * rp;
	z.z = sin(th + branch) * rp;
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

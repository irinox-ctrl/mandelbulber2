/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Percolatie in poreuze media fractaal.
 * Math: pore_network + fluid_displacement
 */

#include "all_fractal_definitions.h"

cFractalThreex3PercolationInPorousMediaFractal::cFractalThreex3PercolationInPorousMediaFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V482 Percolation in Porous Media Fractal";
	internalName = "threex3_percolation_in_porous_media_fractal";
	internalID = fractal::threex3PercolationInPorousMediaFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3PercolationInPorousMediaFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Percolation in Porous Media Fractal: pore_network + fluid_displacement
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Reaction-diffusion: Turing pattern
	double Da = fractal->transformCommon.scale1;
	if (Da < 0.01) Da = 1.0;
	double f_rate = fractal->transformCommon.offset0;
	if (f_rate == 0.0) f_rate = 0.04;
	double k_rate = fractal->transformCommon.offsetA0;
	if (k_rate == 0.0) k_rate = 0.06;
	// Gray-Scott inspired perturbation
	double u = 0.5 + 0.5 * sin(z.x * 3.0);
	double v = 0.5 + 0.5 * cos(z.y * 3.0);
	double reaction = -u * v * v + f_rate * (1.0 - u);
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + Da * reaction * 0.001;
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

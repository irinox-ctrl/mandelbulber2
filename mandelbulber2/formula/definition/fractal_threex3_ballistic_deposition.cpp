/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Ballistische depositie.
 * Math: deeltje valt op willekeurige kolom, blijft liggen bij contact
 */

#include "all_fractal_definitions.h"

cFractalThreex3BallisticDeposition::cFractalThreex3BallisticDeposition() : cAbstractFractal()
{
	nameInComboBox = "3x3 V286 Ballistic Deposition";
	internalName = "threex3_ballistic_deposition";
	internalID = fractal::threex3BallisticDeposition;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3BallisticDeposition::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Ballistic Deposition: deeltje valt op willekeurige kolom, blijft liggen bij contact
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
}

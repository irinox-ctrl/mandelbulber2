/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Vogel-zwerm fractaal.
 * Math: boids: separation + alignment + cohesion
 */

#include "all_fractal_definitions.h"

cFractalThreex3BirdFlockFractal::cFractalThreex3BirdFlockFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V497 Bird Flock Fractal";
	internalName = "threex3_bird_flock_fractal";
	internalID = fractal::threex3BirdFlockFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3BirdFlockFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Bird Flock Fractal: boids: separation + alignment + cohesion
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Crystal: faceted growth
	double symmetry = fractal->transformCommon.scale1;
	if (symmetry < 2.0) symmetry = 6.0;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Faceting via angular quantization
	double phQ = round(ph * symmetry / (2.0 * M_PI)) * 2.0 * M_PI / symmetry;
	double blend = fractal->transformCommon.offset0;
	if (blend == 0.0) blend = 0.1;
	ph = ph * (1.0 - blend) + phQ * blend;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}

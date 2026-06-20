/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Salem-getal fractaal.
 * Math: beta > 1 met |beta_i| <= 1 en één |beta_i| = 1
 */

#include "all_fractal_definitions.h"

cFractalThreex3SalemNumberFractal::cFractalThreex3SalemNumberFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V424 Salem Number Fractal";
	internalName = "threex3_salem_number_fractal";
	internalID = fractal::threex3SalemNumberFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3SalemNumberFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Salem Number Fractal: beta > 1 met |beta_i| <= 1 en één |beta_i| = 1
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Quasicrystal: 5-fold symmetry superposition
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	double quasi = 0.0;
	int folds = max(3, (int)(fractal->transformCommon.scale1));
	if (folds > 12) folds = 12;
	for (int k = 0; k < folds; k++)
		quasi += cos(z.x * cos(k * M_PI / folds) + z.y * sin(k * M_PI / folds));
	double rp = pow(r, power) * (1.0 + fractal->transformCommon.offset0 * quasi * 0.001);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}

/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Snij-en-projectie fractaal.
 * Math: projectie van hoger-dimensionaal rooster op irrationaal vlak
 */

#include "all_fractal_definitions.h"

cFractalThreex3CutAndProjectFractal::cFractalThreex3CutAndProjectFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V418 Cut and Project Fractal";
	internalName = "threex3_cut_and_project_fractal";
	internalID = fractal::threex3CutAndProjectFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3CutAndProjectFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Cut and Project Fractal: projectie van hoger-dimensionaal rooster op irrationaal vlak
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Spin model: nearest-neighbor coupling
	double J = fractal->transformCommon.scale1;
	if (J == 0.0) J = 1.0;
	double coupling = J * (sin(z.x) * sin(z.y) + sin(z.y) * sin(z.z) + sin(z.z) * sin(z.x));
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + fractal->transformCommon.offset0 * coupling * 0.001;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}

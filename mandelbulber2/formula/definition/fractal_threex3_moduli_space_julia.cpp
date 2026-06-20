/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Moduli-ruimte Julia.
 * Math: x = x² + c op M_g Riemann-oppervlak moduli
 */

#include "all_fractal_definitions.h"

cFractalThreex3ModuliSpaceJulia::cFractalThreex3ModuliSpaceJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V129 Moduli Space Julia";
	internalName = "threex3_moduli_space_julia";
	internalID = fractal::threex3ModuliSpaceJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3ModuliSpaceJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Moduli Space Julia: x = x² + c op M_g Riemann-oppervlak moduli
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Clifford algebra rotation
	double angle = fractal->transformCommon.scale1 * M_PI;
	double ca = cos(angle); double sa = sin(angle);
	double rx = z.x * ca - z.y * sa;
	double ry = z.x * sa + z.y * ca;
	double th = asin(z.z / r) * power;
	double ph = atan2(ry, rx) * power;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}

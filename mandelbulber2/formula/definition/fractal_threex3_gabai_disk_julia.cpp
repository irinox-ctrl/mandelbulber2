/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Gabai-schijf Julia.
 * Math: z = z² + c met essentiële schijf
 */

#include "all_fractal_definitions.h"

cFractalThreex3GabaiDiskJulia::cFractalThreex3GabaiDiskJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V185 Gabai Disk Julia";
	internalName = "threex3_gabai_disk_julia";
	internalID = fractal::threex3GabaiDiskJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3GabaiDiskJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Gabai Disk Julia: z = z² + c met essentiële schijf
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Symplectic twist map
	double q1 = z.x; double p1 = z.y; double q2 = z.z;
	double K = fractal->transformCommon.scale1;
	double newP = p1 + K * sin(2.0 * M_PI * q1);
	double newQ = q1 + newP;
	double th = asin(q2 / r) * power;
	double ph = atan2(newP, newQ) * power;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}

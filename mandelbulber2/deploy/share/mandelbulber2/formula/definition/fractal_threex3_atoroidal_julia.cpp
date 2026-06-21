/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Atoroidale Julia.
 * Math: z = z² + c zonder essentiële torus
 */

#include "all_fractal_definitions.h"

cFractalThreex3AtoroidalJulia::cFractalThreex3AtoroidalJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V158 Atoroidal Julia";
	internalName = "threex3_atoroidal_julia";
	internalID = fractal::threex3AtoroidalJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3AtoroidalJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Atoroidal Julia: z = z² + c zonder essentiële torus
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Knot/manifold twist: toroidal mapping
	double R = fractal->transformCommon.scale1;
	if (R < 0.1) R = 2.0;
	double theta = atan2(z.y, z.x);
	double rxy = sqrt(z.x * z.x + z.y * z.y);
	double phi = atan2(z.z, rxy - R);
	double rTube = sqrt((rxy - R) * (rxy - R) + z.z * z.z);
	// Power map on torus
	theta *= power;
	phi *= power;
	rTube = pow(rTube, power);
	double newRxy = R + rTube * cos(phi);
	z.x = newRxy * cos(theta);
	z.y = newRxy * sin(theta);
	z.z = rTube * sin(phi);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
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

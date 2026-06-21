/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Inverse Gudermanniaanse Julia.
 * Math: z = gd⁻¹(z) + c = ln(tan(pi/4 + z/2)) + c
 */

#include "all_fractal_definitions.h"

cFractalThreex3InverseGudermannianJulia::cFractalThreex3InverseGudermannianJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V66 Inverse Gudermannian Julia";
	internalName = "threex3_inverse_gudermannian_julia";
	internalID = fractal::threex3InverseGudermannianJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3InverseGudermannianJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Inverse Gudermannian Julia: z = gd⁻¹(z) + c = ln(tan(pi/4 + z/2)) + c
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	// Hyperbolic: sinh/cosh iteration
	double sh = sinh(z.x * fractal->transformCommon.scale1);
	double ch = cosh(z.y * fractal->transformCommon.scale1);
	double newX = sh * ch + z.x;
	double newY = sin(z.y) * cosh(z.x * 0.5) + z.y;
	double newZ = z.z * power + tanh(z.z) * fractal->transformCommon.offset0;
	aux.DE = aux.DE * fabs(power * ch) + 1.0;
	z.x = newX;
	z.y = newY;
	z.z = newZ;
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

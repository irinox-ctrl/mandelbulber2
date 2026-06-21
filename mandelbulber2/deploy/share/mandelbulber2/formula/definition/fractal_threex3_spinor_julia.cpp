/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Spinor Julia.
 * Math: psi = gamma(psi) + c met Dirac gamma-matrices
 */

#include "all_fractal_definitions.h"

cFractalThreex3SpinorJulia::cFractalThreex3SpinorJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V113 Spinor Julia";
	internalName = "threex3_spinor_julia";
	internalID = fractal::threex3SpinorJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3SpinorJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Spinor Julia: psi = gamma(psi) + c met Dirac gamma-matrices
	// Quaternion-style multiplication with twist
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Higher-dim: quaternion square + perturbation
	double newX = z.x * z.x - z.y * z.y - z.z * z.z + fractal->transformCommon.offset0;
	double newY = 2.0 * z.x * z.y + fractal->transformCommon.offsetA0;
	double newZ = 2.0 * z.x * z.z + fractal->transformCommon.offsetB0;
	// Apply power scaling
	double scale = pow(r, power - 2.0);
	z.x = newX * scale;
	z.y = newY * scale;
	z.z = newZ * scale;
	aux.DE = aux.DE * power * pow(r, power - 1.0) + 1.0;
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

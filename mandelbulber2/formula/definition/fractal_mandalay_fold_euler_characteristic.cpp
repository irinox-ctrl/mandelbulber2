/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Euler-karakteristiek in Mandalay Fold.
 * Math: z = z + chi = V - E + F * alternating_sum_Betti * Gauss_Bonnet * curvature_integral
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldEulerCharacteristic::cFractalMandalayFoldEulerCharacteristic() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V43 Euler Characteristic";
	internalName = "mandalay_fold_euler_characteristic";
	internalID = fractal::mandalayFoldEulerCharacteristic;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldEulerCharacteristic::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Euler Characteristic fold: chi = V - E + F
	double s = fractal->transformCommon.scale08;
	double V = fabs(z.x * z.y * z.z);
	double E = fabs(z.x*z.y) + fabs(z.y*z.z) + fabs(z.x*z.z);
	double F = fabs(z.x) + fabs(z.y) + fabs(z.z);
	double chi = V - E + F;
	z *= (1.0 + chi * s * 0.01);

	// Spherical fold
	double rr = z.Dot(z);
	if (rr < fractal->transformCommon.minR2p25)
	{
		double tglad_factor1 = fractal->transformCommon.maxR2d1 / fractal->transformCommon.minR2p25;
		z *= tglad_factor1;
		aux.DE *= tglad_factor1;
	}
	else if (rr < fractal->transformCommon.maxR2d1)
	{
		double tglad_factor2 = fractal->transformCommon.maxR2d1 / rr;
		z *= tglad_factor2;
		aux.DE *= tglad_factor2;
	}

	// Scale
	double useScale = fractal->transformCommon.scale2;
	z *= useScale;
	aux.DE = aux.DE * fabs(useScale) + 1.0;

	// Rotation
	if (fractal->transformCommon.rotationEnabled)
	{
		z = fractal->transformCommon.rotationMatrix.RotateVector(z);
	}
}

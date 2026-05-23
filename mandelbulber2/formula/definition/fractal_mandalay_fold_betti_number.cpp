/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Betti-getal in Mandalay Fold.
 * Math: z = z + b_k = dim(H_k) * topological_invariant * Euler_characteristic * alternating_sum
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldBettiNumber::cFractalMandalayFoldBettiNumber() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V42 Betti Number";
	internalName = "mandalay_fold_betti_number";
	internalID = fractal::mandalayFoldBettiNumber;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldBettiNumber::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Betti Number fold: topological holes
	double s = fractal->transformCommon.scale08;
	double b0 = 1.0;
	double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
	double b1 = (r > 0.5 && r < 1.5) ? 1.0 : 0.0;
	z.x *= (1.0 + (b0 + b1) * s * 0.1);
	z.y *= (1.0 + (b0 + b1) * s * 0.1);

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

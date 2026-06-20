/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Holonomische benadering in Mandalay Fold.
 * Math: z = z + Eliashberg_Mishachev * C⁰_close * section * jet_bundle * transversal
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldHolonomicApproximation::cFractalMandalayFoldHolonomicApproximation() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V16 Holonomic Approximation";
	internalName = "mandalay_fold_holonomic_approximation";
	internalID = fractal::mandalayFoldHolonomicApproximation;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldHolonomicApproximation::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Holonomic Approximation fold: C0-close sections
	double s = fractal->transformCommon.scale08;
	double t = z.x + z.y + z.z;
	z.x += s * 0.1 * sin(t * 2.0);
	z.y += s * 0.1 * cos(t * 2.0);
	z.z += s * 0.1 * sin(t * 3.0);

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

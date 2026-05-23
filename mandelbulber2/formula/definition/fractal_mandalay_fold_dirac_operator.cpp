/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Dirac-operator in Mandalay Fold.
 * Math: z = z + spin_bundle * Clifford_multiplication * Lichnerowicz_formula * Weitzenböck
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldDiracOperator::cFractalMandalayFoldDiracOperator() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V47 Dirac Operator";
	internalName = "mandalay_fold_dirac_operator";
	internalID = fractal::mandalayFoldDiracOperator;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldDiracOperator::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Dirac Operator fold: Clifford multiplication
	double s = fractal->transformCommon.scale08;
	double nx = z.y * z.z;
	double ny = z.z * z.x;
	double nz = z.x * z.y;
	z.x += nx * s * 0.1;
	z.y += ny * s * 0.1;
	z.z += nz * s * 0.1;

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

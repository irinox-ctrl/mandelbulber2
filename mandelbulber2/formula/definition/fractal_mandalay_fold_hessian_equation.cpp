/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Hessiaanse vergelijking in Mandalay Fold.
 * Math: z = z + S_k(D²u) = f * k-Hessian * Trudinger * Wang
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldHessianEquation::cFractalMandalayFoldHessianEquation() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V9 Hessian Equation";
	internalName = "mandalay_fold_hessian_equation";
	internalID = fractal::mandalayFoldHessianEquation;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldHessianEquation::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Hessian Equation fold: k-Hessian generalization
	double s2 = z.x*z.x + z.y*z.y + z.z*z.z;
	double sk = pow(fabs(s2) + 1e-21, 0.333);
	double s = fractal->transformCommon.scale08;
	z.x *= sk * s + (1.0 - s);
	z.y *= sk * s + (1.0 - s);
	z.z *= sk * s + (1.0 - s);

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

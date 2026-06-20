/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Willmore-stroom in Mandalay Fold.
 * Math: z = z - grad(W) * Kuwert_Schatzle * bending_energy * elastic
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldWillmoreFlow::cFractalMandalayFoldWillmoreFlow() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V4 Willmore Flow";
	internalName = "mandalay_fold_willmore_flow";
	internalID = fractal::mandalayFoldWillmoreFlow;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldWillmoreFlow::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Willmore Flow fold: minimize bending energy
	double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
	if (r > 1e-21) {
		double K = 1.0 / (r * r);
		double H = 1.0 / r;
		double W = H * H - K;
		double dt = fractal->transformCommon.scale08;
		z.x -= W * z.x / r * dt;
		z.y -= W * z.y / r * dt;
		z.z -= W * z.z / r * dt;
	}

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

/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Convexe integratie in Mandalay Fold.
 * Math: z = z + Nash_Kuiper * h-principle * Gromov * isometric_embedding * C¹
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldConvexIntegration::cFractalMandalayFoldConvexIntegration() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V13 Convex Integration";
	internalName = "mandalay_fold_convex_integration";
	internalID = fractal::mandalayFoldConvexIntegration;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldConvexIntegration::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Convex Integration fold: Nash-Kuiper embedding
	double s = fractal->transformCommon.scale08;
	double freq = 3.14159 * 4.0;
	double amp = s * 0.1;
	z.x += amp * sin(freq * z.y) * cos(freq * z.z);
	z.y += amp * sin(freq * z.z) * cos(freq * z.x);
	z.z += amp * sin(freq * z.x) * cos(freq * z.y);

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

/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Mandalay Fold: Valuatietheorie in Mandalay Fold.
 */

REAL4 MandalayFoldValuationTheoryIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	REAL tmp;
	if (z.z > z.y) { tmp = z.y; z.y = z.z; z.z = tmp; }
	if (z.y > z.x) { tmp = z.x; z.x = z.y; z.y = tmp; }
	if (z.z > z.y) { tmp = z.y; z.y = z.z; z.z = tmp; }

	// Valuation Theory fold: Hadwiger decomposition
	REAL V = z.x * z.y * z.z;
	REAL S = fabs(z.x*z.y) + fabs(z.y*z.z) + fabs(z.x*z.z);
	REAL M = fabs(z.x) + fabs(z.y) + fabs(z.z);
	REAL s = fractal->transformCommon.scale08;
	z.x += (V * 0.1 + S * 0.01) * sign(z.x) * s;
	z.y += (V * 0.1 + S * 0.01) * sign(z.y) * s;
	z.z += (V * 0.1 + S * 0.01) * sign(z.z) * s;

	// Spherical fold
	REAL rr = dot(z, z);
	if (rr < fractal->transformCommon.minR2p25)
	{
		REAL tglad_factor1 = fractal->transformCommon.maxR2d1 / fractal->transformCommon.minR2p25;
		z *= tglad_factor1;
		aux->DE *= tglad_factor1;
	}
	else if (rr < fractal->transformCommon.maxR2d1)
	{
		REAL tglad_factor2 = fractal->transformCommon.maxR2d1 / rr;
		z *= tglad_factor2;
		aux->DE *= tglad_factor2;
	}

	// Scale
	REAL useScale = fractal->transformCommon.scale2;
	z *= useScale;
	aux->DE = aux->DE * fabs(useScale) + 1.0f;

	return z;
}

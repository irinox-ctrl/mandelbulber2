/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Mandalay Fold: Vermogendiagram in Mandalay Fold.
 */

REAL4 MandalayFoldPowerDiagramIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	REAL tmp;
	if (z.z > z.y) { tmp = z.y; z.y = z.z; z.z = tmp; }
	if (z.y > z.x) { tmp = z.x; z.x = z.y; z.y = tmp; }
	if (z.z > z.y) { tmp = z.y; z.y = z.z; z.z = tmp; }

	// Power Diagram fold: weighted Voronoi
	REAL s = fractal->transformCommon.scale08;
	REAL w1 = 1.0; REAL w2 = 0.7;
	REAL d1 = z.x*z.x + z.y*z.y + z.z*z.z - w1;
	REAL d2 = (z.x-1.0)*(z.x-1.0) + z.y*z.y + z.z*z.z - w2;
	REAL blend = 1.0 / (1.0 + exp(-(d1 - d2) * 5.0));
	z.x = z.x * (1.0 - blend * s) + (z.x - 0.5) * blend * s;

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

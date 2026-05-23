/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Mandalay Fold: Kanaaloppervlak in Mandalay Fold.
 */

REAL4 MandalayFoldChannelSurfaceIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	REAL tmp;
	if (z.z > z.y) { tmp = z.y; z.y = z.z; z.z = tmp; }
	if (z.y > z.x) { tmp = z.x; z.x = z.y; z.y = tmp; }
	if (z.z > z.y) { tmp = z.y; z.y = z.z; z.z = tmp; }

	// Channel Surface fold: envelope of spheres
	REAL s = fractal->transformCommon.scale08;
	REAL t = atan2(z.y, z.x);
	REAL spine_r = 1.0 + 0.3 * sin(t * 3.0);
	REAL rxy = sqrt(z.x*z.x + z.y*z.y);
	REAL diff = rxy - spine_r;
	z.x += diff * cos(t) * s * 0.5;
	z.y += diff * sin(t) * s * 0.5;

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

/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Mandalay Fold: Laguerre-meetkunde in Mandalay Fold.
 */

REAL4 MandalayFoldLaguerreGeometryIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	REAL tmp;
	if (z.z > z.y) { tmp = z.y; z.y = z.z; z.z = tmp; }
	if (z.y > z.x) { tmp = z.x; z.x = z.y; z.y = tmp; }
	if (z.z > z.y) { tmp = z.y; z.y = z.z; z.z = tmp; }

	// Laguerre Geometry fold: oriented planes
	REAL s = fractal->transformCommon.scale08;
	REAL r2 = z.x*z.x + z.y*z.y + z.z*z.z;
	REAL inv = 1.0 / (r2 + 1.0);
	z.x = z.x * (1.0 - s) + 2.0 * z.x * inv * s;
	z.y = z.y * (1.0 - s) + 2.0 * z.y * inv * s;
	z.z = z.z * (1.0 - s) + (r2 - 1.0) * inv * s;

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


	// === General Purpose Multiplier 1 ===
	if (fractal->transformCommon.functionEnabledBxFalse
		&& aux->i >= fractal->transformCommon.startIterationsB
		&& aux->i < fractal->transformCommon.stopIterationsB)
	{
		REAL val = fractal->transformCommon.scale4;
		switch (fractal->transformCommon.multiplierMode1)
		{
			default:
			case 0: z *= val; aux->DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux->DE *= val; break;
			case 5: aux->color *= val; break;
		}
	}

	// === General Purpose Multiplier 2 ===
	if (fractal->transformCommon.functionEnabledByFalse
		&& aux->i >= fractal->transformCommon.startIterationsC
		&& aux->i < fractal->transformCommon.stopIterationsC)
	{
		REAL val = fractal->transformCommon.scale5;
		switch (fractal->transformCommon.multiplierMode2)
		{
			default:
			case 0: z *= val; aux->DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux->DE *= val; break;
			case 5: aux->color *= val; break;
		}
	}

	// === General Purpose Multiplier 3 ===
	if (fractal->transformCommon.functionEnabledBzFalse
		&& aux->i >= fractal->transformCommon.startIterationsD
		&& aux->i < fractal->transformCommon.stopIterationsD)
	{
		REAL val = fractal->transformCommon.scale6;
		switch (fractal->transformCommon.multiplierMode3)
		{
			default:
			case 0: z *= val; aux->DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux->DE *= val; break;
			case 5: aux->color *= val; break;
		}
	}

	// === General Purpose Multiplier 4 ===
	if (fractal->transformCommon.functionEnabledBwFalse
		&& aux->i >= fractal->transformCommon.startIterationsE
		&& aux->i < fractal->transformCommon.stopIterationsE)
	{
		REAL val = fractal->transformCommon.scale8;
		switch (fractal->transformCommon.multiplierMode4)
		{
			default:
			case 0: z *= val; aux->DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux->DE *= val; break;
			case 5: aux->color *= val; break;
		}
	}

	// === General Purpose Multiplier 5 ===
	if (fractal->transformCommon.functionEnabledCzFalse
		&& aux->i >= fractal->transformCommon.startIterationsF
		&& aux->i < fractal->transformCommon.stopIterationsF)
	{
		REAL val = fractal->transformCommon.scale16;
		switch (fractal->transformCommon.multiplierMode5)
		{
			default:
			case 0: z *= val; aux->DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux->DE *= val; break;
			case 5: aux->color *= val; break;
		}
	}

	return z;
}

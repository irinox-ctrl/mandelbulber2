/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Cayley-Dickson Julia.
 */

REAL4 Threex3CayleyDicksonJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Cayley-Dickson Julia: x = x² + c in Cayley-Dickson constructie
	// Quaternion-style multiplication with twist
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Higher-dim: quaternion square + perturbation
	REAL newX = z.x * z.x - z.y * z.y - z.z * z.z + fractal->transformCommon.offset0;
	REAL newY = 2.0 * z.x * z.y + fractal->transformCommon.offsetA0;
	REAL newZ = 2.0 * z.x * z.z + fractal->transformCommon.offsetB0;
	// Apply power scaling
	REAL scale = pow(r, power - 2.0);
	z.x = newX * scale;
	z.y = newY * scale;
	z.z = newZ * scale;
	aux->DE = aux->DE * power * pow(r, power - 1.0) + 1.0;

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

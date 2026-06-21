/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Dimeren.
 */

REAL4 Threex3DimersIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Dimers: perfecte matching van rooster met gewichten
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Growth: aggregation-inspired radial modulation
	REAL growthRate = fractal->transformCommon.scale1;
	if (growthRate < 0.01) growthRate = 0.5;
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	// Radial fluctuation based on angle
	REAL fluct = 1.0 + growthRate * 0.1 * sin(5.0 * th) * cos(7.0 * ph);
	REAL rp = pow(r, power) * fluct;
	aux->DE = power * pow(r, power - 1.0) * fluct * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;

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

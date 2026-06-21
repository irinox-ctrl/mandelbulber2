/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Duffing-oscillator.
 */

REAL4 Threex3DuffingOscillatorIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Duffing Oscillator: d²x/dt² + delta*dx/dt + alpha*x + beta*x³ = gamma*cos(omega*t)
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	// Flow: Rössler-type 3D attractor
	REAL a = fractal->transformCommon.scale1;
	if (a == 0.0) a = 0.2;
	REAL b = fractal->transformCommon.offset0;
	if (b == 0.0) b = 0.2;
	REAL c = fractal->transformCommon.offsetA0;
	if (c == 0.0) c = 5.7;
	REAL dt = 0.01 * power;
	REAL dx = -(z.y + z.z);
	REAL dy = z.x + a * z.y;
	REAL dz = b + z.z * (z.x - c);
	z.x += dx * dt;
	z.y += dy * dt;
	z.z += dz * dt;
	aux->DE = aux->DE * (1.0 + fabs(dt * (z.x - c))) + 0.01;

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

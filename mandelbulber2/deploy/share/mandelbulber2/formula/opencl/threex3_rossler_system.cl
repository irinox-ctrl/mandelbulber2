/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Rössler-systeem.
 */

REAL4 Threex3RosslerSystemIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Rossler System: dx/dt = -y - z, dy/dt = x + a*y, dz/dt = b + z*(x - c)
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
		z *= fractal->transformCommon.scale4;
		aux->DE *= fabs(fractal->transformCommon.scale4);
	}

	// === General Purpose Multiplier 2 ===
	if (fractal->transformCommon.functionEnabledByFalse
		&& aux->i >= fractal->transformCommon.startIterationsC
		&& aux->i < fractal->transformCommon.stopIterationsC)
	{
		z *= fractal->transformCommon.scale5;
		aux->DE *= fabs(fractal->transformCommon.scale5);
	}

	// === General Purpose Multiplier 3 ===
	if (fractal->transformCommon.functionEnabledBzFalse
		&& aux->i >= fractal->transformCommon.startIterationsD
		&& aux->i < fractal->transformCommon.stopIterationsD)
	{
		z *= fractal->transformCommon.scale6;
		aux->DE *= fabs(fractal->transformCommon.scale6);
	}

	// === General Purpose Multiplier 4 ===
	if (fractal->transformCommon.functionEnabledBwFalse
		&& aux->i >= fractal->transformCommon.startIterationsE
		&& aux->i < fractal->transformCommon.stopIterationsE)
	{
		z *= fractal->transformCommon.scale8;
		aux->DE *= fabs(fractal->transformCommon.scale8);
	}

	// === General Purpose Multiplier 5 ===
	if (fractal->transformCommon.functionEnabledCzFalse
		&& aux->i >= fractal->transformCommon.startIterationsF
		&& aux->i < fractal->transformCommon.stopIterationsF)
	{
		z *= fractal->transformCommon.scale16;
		aux->DE *= fabs(fractal->transformCommon.scale16);
	}

	return z;
}

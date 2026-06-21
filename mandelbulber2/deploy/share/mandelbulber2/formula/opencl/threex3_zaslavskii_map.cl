/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Zaslavskii-afbeelding.
 */

REAL4 Threex3ZaslavskiiMapIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Zaslavskii Map: x_{n+1} = (x_n + nu*(1 + mu*y_n) + epsilon*nu*mu*cos(2*pi*x_n)) mod 1, y_{n+1} = exp(-gamma)*(y_n + epsilon*cos(2*pi*x_n))
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	// Dynamic system: coupled oscillator map
	REAL a = fractal->transformCommon.scale1;
	if (a == 0.0) a = 1.4;
	REAL b = fractal->transformCommon.offset0;
	if (b == 0.0) b = 0.3;
	REAL newX = 1.0 - a * z.x * z.x + z.y;
	REAL newY = b * z.x + z.z * fractal->transformCommon.offsetA0;
	REAL newZ = sin(z.z * power) + z.x * fractal->transformCommon.offsetB0;
	aux->DE = aux->DE * fabs(2.0 * a * z.x) + 1.0;
	z.x = newX;
	z.y = newY;
	z.z = newZ;

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

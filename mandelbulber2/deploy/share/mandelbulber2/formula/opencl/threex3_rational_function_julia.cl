/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Rationale functie Julia.
 */

REAL4 Threex3RationalFunctionJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Rational Function Julia: z = P(z)/Q(z) + c met P, Q polynomen
	REAL r = aux->r;
	REAL th0 = asin(z.z / r) + fractal->bulb.betaAngleOffset;
	REAL ph0 = atan2(z.y, z.x) + fractal->bulb.alphaAngleOffset;
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 3.0;
	REAL rp = pow(r, power - 1.0);
	REAL th = th0 * power;
	REAL ph = ph0 * power;
	REAL cth = cos(th);
	aux->DE = rp * aux->DE * power + 1.0;
	rp *= r;
	REAL newX = cth * cos(ph) * rp;
	REAL newY = cth * sin(ph) * rp;
	REAL newZ = sin(th) * rp;
	// Algebraic twist: add polynomial correction
	REAL corr = fractal->transformCommon.scale1 * sin(power * atan2(newY, newX));
	z.x = newX + corr * fractal->transformCommon.constantMultiplier111.x;
	z.y = newY + corr * fractal->transformCommon.constantMultiplier111.y;
	z.z = newZ + corr * fractal->transformCommon.constantMultiplier111.z;

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

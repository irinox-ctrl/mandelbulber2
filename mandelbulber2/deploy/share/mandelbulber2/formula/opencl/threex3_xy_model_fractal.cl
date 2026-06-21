/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * XY-model fractaal.
 */

REAL4 Threex3XyModelFractalIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// XY Model Fractal: H = -J*sum(cos(theta_i - theta_j)) met continue spin
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Spin model: nearest-neighbor coupling
	REAL J = fractal->transformCommon.scale1;
	if (J == 0.0) J = 1.0;
	REAL coupling = J * (sin(z.x) * sin(z.y) + sin(z.y) * sin(z.z) + sin(z.z) * sin(z.x));
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + fractal->transformCommon.offset0 * coupling * 0.001;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;

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

/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Turmite fractaal.
 */

REAL4 Threex3TurmiteFractalIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Turmite Fractal: z = turmite_move(z, state, rules) + c
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Cellular automaton: rule-based folding
	REAL rule = fractal->transformCommon.scale1;
	if (rule < 1.0) rule = 30.0;
	REAL threshold = fractal->transformCommon.offset0;
	if (threshold == 0.0) threshold = 0.5;
	// Fold based on threshold
	if (z.x > threshold) z.x = 2.0 * threshold - z.x;
	if (z.x < -threshold) z.x = -2.0 * threshold - z.x;
	if (z.y > threshold) z.y = 2.0 * threshold - z.y;
	if (z.y < -threshold) z.y = -2.0 * threshold - z.y;
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
	return z;
}

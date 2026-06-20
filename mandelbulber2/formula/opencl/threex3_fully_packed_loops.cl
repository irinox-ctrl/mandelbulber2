/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Volledig gevulde lussen.
 */

REAL4 Threex3FullyPackedLoopsIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Fully Packed Loops: elke vertex heeft 2 bezette bogen
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
	return z;
}

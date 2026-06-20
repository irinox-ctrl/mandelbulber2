/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Anderson T-motief Julia.
 */

REAL4 Threex3AndersonTMotiveJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Anderson T-Motive Julia: z = z² + c met t-motive structuur
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL th0 = asin(z.z / r);
	REAL ph0 = atan2(z.y, z.x);
	// Cohomological twist: multiple frequency superposition
	REAL k = fractal->transformCommon.scale1;
	if (k < 1.0) k = 1.0;
	REAL th = th0 * power + fractal->transformCommon.offset0 * sin(k * th0);
	REAL ph = ph0 * power + fractal->transformCommon.offsetA0 * sin(k * ph0);
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
	return z;
}

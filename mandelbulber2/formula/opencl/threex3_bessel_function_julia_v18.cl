/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Bessel-functie Julia.
 */

REAL4 Threex3BesselFunctionJuliaV18Iteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Bessel Function Julia: z = J_n(|z|)*z/|z| + c
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	REAL th0 = acos(z.z / r);
	REAL ph0 = atan2(z.y, z.x);
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 3.0;
	// Special function modulation
	REAL mod = sin(power * th0) * cos(power * ph0);
	REAL rp = pow(r, power - 1.0);
	REAL th = th0 * power + fractal->transformCommon.offset0 * mod;
	REAL ph = ph0 * power + fractal->transformCommon.offsetA0 * mod;
	REAL sth = sin(th);
	aux->DE = rp * aux->DE * power + 1.0;
	rp *= r;
	z.x = sth * cos(ph) * rp;
	z.y = sth * sin(ph) * rp;
	z.z = cos(th) * rp;
	return z;
}

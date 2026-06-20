/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Monomiale Julia-set.
 */

REAL4 Threex3MonomialJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Monomial Julia: z = z^n + c met n >= 2
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
	return z;
}

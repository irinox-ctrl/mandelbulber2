/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Fresnel-integraal Julia.
 */

REAL4 Threex3FresnelIntegralJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Fresnel Integral Julia: z = C(z) + i*S(z) + c — Fresnel-cosinus en -sinus
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	// PDE-inspired: diffusion-reaction
	REAL laplacian = (z.x * z.x + z.y * z.y + z.z * z.z) * fractal->transformCommon.scale1;
	REAL reaction = sin(z.x) * cos(z.y) * sin(z.z);
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + fractal->transformCommon.offset0 * reaction;
	z.y = cos(th) * sin(ph) * rp + fractal->transformCommon.offsetA0 * laplacian * 0.001;
	z.z = sin(th) * rp;
	return z;
}

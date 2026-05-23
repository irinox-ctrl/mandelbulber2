/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * 3-mani-fold Julia.
 */

REAL4 Threex33ManifoldJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// 3-Manifold Julia: z = z² + c op M³ met geometrisatie
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Knot/manifold twist: toroidal mapping
	REAL R = fractal->transformCommon.scale1;
	if (R < 0.1) R = 2.0;
	REAL theta = atan2(z.y, z.x);
	REAL rxy = sqrt(z.x * z.x + z.y * z.y);
	REAL phi = atan2(z.z, rxy - R);
	REAL rTube = sqrt((rxy - R) * (rxy - R) + z.z * z.z);
	// Power map on torus
	theta *= power;
	phi *= power;
	rTube = pow(rTube, power);
	REAL newRxy = R + rTube * cos(phi);
	z.x = newRxy * cos(theta);
	z.y = newRxy * sin(theta);
	z.z = rTube * sin(phi);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	return z;
}

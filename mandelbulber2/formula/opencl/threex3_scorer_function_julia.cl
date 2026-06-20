/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Scorer-functie Julia.
 */

REAL4 Threex3ScorerFunctionJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Scorer Function Julia: z = Gi(z) + c of Hi(z) + c — inhomogene Airy
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	// Series summation: harmonic perturbation
	REAL harm = 0.0;
	int terms = max(1, (int)(fractal->transformCommon.scale1));
	for (int n = 1; n <= terms && n <= 8; n++)
		harm += sin(n * th) / (double)n;
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th + harm * 0.1) * cos(ph) * rp;
	z.y = cos(th + harm * 0.1) * sin(ph) * rp;
	z.z = sin(th + harm * 0.1) * rp;
	return z;
}

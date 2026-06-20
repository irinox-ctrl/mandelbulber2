/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Schelp-patroon fractaal.
 */

REAL4 Threex3ShellPatternFractalIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Shell Pattern Fractal: reaction-diffusion op groeiende schelp
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Biological: branching tree pattern
	REAL branchAngle = fractal->transformCommon.scale1;
	if (branchAngle < 0.01) branchAngle = 0.5;
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	// Branch perturbation based on radius
	REAL branch = branchAngle * sin(3.0 * th) * cos(5.0 * ph) * exp(-r * 0.1);
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th + branch) * cos(ph) * rp;
	z.y = cos(th + branch) * sin(ph) * rp;
	z.z = sin(th + branch) * rp;
	return z;
}

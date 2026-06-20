/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Brun-constante fractaal.
 */

REAL4 Threex3BrunConstantFractalIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Brun Constant Fractal: B_2 = sum(1/p + 1/(p+2)) over tweeling-priemen
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	// Wave equation: standing wave modulation
	REAL k_wave = fractal->transformCommon.scale1;
	if (k_wave < 0.1) k_wave = 2.0;
	REAL standing = sin(k_wave * r) * cos(k_wave * th);
	REAL rp = pow(r, power) * (1.0 + fractal->transformCommon.offset0 * standing * 0.01);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
	return z;
}

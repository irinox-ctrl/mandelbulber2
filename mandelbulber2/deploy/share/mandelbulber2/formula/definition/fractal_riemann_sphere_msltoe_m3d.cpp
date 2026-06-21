/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Generalized by darkbeam from a msltoe formula;
 * http://www.fractalforums.com/3d-fractal-generation/riemann-fractals/msg33500/#msg33500
 */

#include "all_fractal_definitions.h"

cFractalRiemannSphereMsltoeM3d::cFractalRiemannSphereMsltoeM3d() : cAbstractFractal()
{
	nameInComboBox = "Riemann - Sphere Msltoe M3D";
	internalName = "riemann_sphere_msltoe_m3d";
	internalID = fractal::riemannSphereMsltoeM3d;
	DEType = deltaDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 1.5;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalRiemannSphereMsltoeM3d::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	if (z.z > fractal->transformCommon.offsetA1) z * 1000.0; // fail bailout check
	else
	{
		z = fractal->transformCommon.rotationMatrix.RotateVector(z);
		double r = aux.r;
		double s, t;
		// if (r < 1e-21) r = 1e-21;
		z *= fractal->transformCommon.scale / r;
		double q = 1.0 / (1.0 - z.z);
		s = z.x * q;
		t = z.y * q;
		double w = 1.0 + s * s + t * t;
		double limit = fractal->transformCommon.scale8 * 8000.0; // fudge
		if (w > limit) w = limit;

		s = fabs(sin(M_PI * s + fractal->transformCommon.offsetA0));
		t = fabs(sin(M_PI * t + fractal->transformCommon.offsetB0));
		s = fabs(s - fractal->transformCommon.offsetC0);
		t = fabs(t - fractal->transformCommon.offsetD0);

		r = -0.25 + fractal->transformCommon.offsetE0 + pow(r, (fractal->transformCommon.scale2 * w));
		w = 2.0 / (1.0 + s * s + t * t);
		z.x = r * s * w;
		z.y = r * t * w;
		z.z = r * (1.0 - w);
		z += fractal->transformCommon.offset001;
	}
	// === General Purpose Multiplier 1 ===
	if (fractal->transformCommon.functionEnabledBxFalse
		&& aux.i >= fractal->transformCommon.startIterationsB
		&& aux.i < fractal->transformCommon.stopIterationsB)
	{
		double val = fractal->transformCommon.scale4;
		switch (fractal->transformCommon.multiplierMode1)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 2 ===
	if (fractal->transformCommon.functionEnabledByFalse
		&& aux.i >= fractal->transformCommon.startIterationsC
		&& aux.i < fractal->transformCommon.stopIterationsC)
	{
		double val = fractal->transformCommon.scale5;
		switch (fractal->transformCommon.multiplierMode2)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 3 ===
	if (fractal->transformCommon.functionEnabledBzFalse
		&& aux.i >= fractal->transformCommon.startIterationsD
		&& aux.i < fractal->transformCommon.stopIterationsD)
	{
		double val = fractal->transformCommon.scale6;
		switch (fractal->transformCommon.multiplierMode3)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 4 ===
	if (fractal->transformCommon.functionEnabledBwFalse
		&& aux.i >= fractal->transformCommon.startIterationsE
		&& aux.i < fractal->transformCommon.stopIterationsE)
	{
		double val = fractal->transformCommon.scale8;
		switch (fractal->transformCommon.multiplierMode4)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 5 ===
	if (fractal->transformCommon.functionEnabledCzFalse
		&& aux.i >= fractal->transformCommon.startIterationsF
		&& aux.i < fractal->transformCommon.stopIterationsF)
	{
		double val = fractal->transformCommon.scale16;
		switch (fractal->transformCommon.multiplierMode5)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

}

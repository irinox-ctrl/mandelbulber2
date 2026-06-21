/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Quaternion4D
 */

#include "all_fractal_definitions.h"

cFractalQuaternion4d::cFractalQuaternion4d() : cAbstractFractal()
{
	nameInComboBox = "Quaternion 4D";
	internalName = "quaternion4d";
	internalID = fractal::quaternion4d;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalQuaternion4d::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	aux.DE *= 2.0 * aux.r;
	z = CVector4(z.x * z.x - z.y * z.y - z.z * z.z - z.w * z.w, z.x * z.y, z.x * z.z, z.w);
	z *= fractal->transformCommon.constantMultiplier1220;
	z += fractal->transformCommon.additionConstant0000;

	// 6 plane rotation
	if (fractal->transformCommon.functionEnabledRFalse
			&& aux.i >= fractal->transformCommon.startIterationsR
			&& aux.i < fractal->transformCommon.stopIterationsR)
	{
		CVector4 tp;
		if (fractal->transformCommon.rotation44a.x != 0)
		{
			tp = z;
			double alpha = fractal->transformCommon.rotation44a.x * M_PI_180;
			z.x = tp.x * cos(alpha) + tp.y * sin(alpha);
			z.y = tp.x * -sin(alpha) + tp.y * cos(alpha);
		}
		if (fractal->transformCommon.rotation44a.y != 0)
		{
			tp = z;
			double beta = fractal->transformCommon.rotation44a.y * M_PI_180;
			z.y = tp.y * cos(beta) + tp.z * sin(beta);
			z.z = tp.y * -sin(beta) + tp.z * cos(beta);
		}
		if (fractal->transformCommon.rotation44a.z != 0)
		{
			tp = z;
			double gamma = fractal->transformCommon.rotation44a.z * M_PI_180;
			z.x = tp.x * cos(gamma) + tp.z * sin(gamma);
			z.z = tp.x * -sin(gamma) + tp.z * cos(gamma);
		}
		if (fractal->transformCommon.rotation44b.x != 0)
		{
			tp = z;
			double delta = fractal->transformCommon.rotation44b.x * M_PI_180;
			z.x = tp.x * cos(delta) + tp.w * sin(delta);
			z.w = tp.x * -sin(delta) + tp.w * cos(delta);
		}
		if (fractal->transformCommon.rotation44b.y != 0)
		{
			tp = z;
			double epsilon = fractal->transformCommon.rotation44b.y * M_PI_180;
			z.y = tp.y * cos(epsilon) + tp.w * sin(epsilon);
			z.w = tp.y * -sin(epsilon) + tp.w * cos(epsilon);
		}
		if (fractal->transformCommon.rotation44b.z != 0)
		{
			tp = z;
			double zeta = fractal->transformCommon.rotation44b.z * M_PI_180;
			z.z = tp.z * cos(zeta) + tp.w * sin(zeta);
			z.w = tp.z * -sin(zeta) + tp.w * cos(zeta);
		}
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

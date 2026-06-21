/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * superformula Johan Gielis
 * https://bsapubs.onlinelibrary.wiley.com/doi/10.3732/ajb.90.3.333
 * http://paulbourke.net/geometry/supershape/
 */

#include "all_fractal_definitions.h"

cFractalTransfDIFSSupershapeV2::cFractalTransfDIFSSupershapeV2() : cAbstractFractal()
{
	nameInComboBox = "T>DIFS Supershape V2";
	internalName = "transf_difs_supershape_v2";
	internalID = fractal::transfDIFSSupershapeV2;
	DEType = analyticDEType;
	DEFunctionType = customDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionCustomDE;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfDIFSSupershapeV2::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	if (fractal->transformCommon.functionEnabledPFalse
			&& aux.i >= fractal->transformCommon.startIterationsP
				&& aux.i < fractal->transformCommon.stopIterationsP1)
	{
		if (fractal->transformCommon.functionEnabledAxFalse)
		{
			if (!fractal->transformCommon.functionEnabledBxFalse)
				z.x = fractal->transformCommon.offset000.x - fabs(z.x);
			else
				z.x = sign(z.x) * (fractal->transformCommon.offset000.x - fabs(z.x));
		}

		if (fractal->transformCommon.functionEnabledAyFalse)
		{
			if (!fractal->transformCommon.functionEnabledByFalse)
				z.y = fractal->transformCommon.offset000.y - fabs(z.y);
			else
				z.y = sign(z.y) * (fractal->transformCommon.offset000.y - fabs(z.y));
		}

		if (fractal->transformCommon.functionEnabledAzFalse)
		{
			if (!fractal->transformCommon.functionEnabledBzFalse)
				z.z = fractal->transformCommon.offset000.z - fabs(z.z);
			else
				z.z = sign(z.z) * (fractal->transformCommon.offset000.z - fabs(z.z));
		}

		z *= fractal->transformCommon.scale1;
		aux.DE *= fractal->transformCommon.scale1;
		z += fractal->transformCommon.offsetA000;
	}

	double r1;
	double phi;
	if (!fractal->transformCommon.functionEnabledAFalse)
		phi = atan2(z.x, z.y);
	else
		phi = atan2(z.y, z.x);

	double t1 = fabs(cos(fractal->transformCommon.constantMultiplierA111.x * phi)
								 * fractal->transformCommon.constantMultiplierA111.y);
	if (fractal->transformCommon.functionEnabledXFalse)
		t1 = pow(t1, fractal->transformCommon.constantMultiplierB111.x);

	double t2 = fabs(sin(fractal->transformCommon.constantMultiplierA111.x * phi)
								 * fractal->transformCommon.constantMultiplierA111.z);
	if (fractal->transformCommon.functionEnabledYFalse)
		t2 = pow(t2, fractal->transformCommon.constantMultiplierB111.y);

	if (!fractal->transformCommon.functionEnabledEFalse)
		r1 = t1 + t2;
	else
		r1 = pow(t1 + t2, fractal->transformCommon.constantMultiplierB111.z);

	if (!fractal->transformCommon.functionEnabledFFalse) r1 = 1.0f / r1; // invert

	CVector4 zc = z;
	double rb = sqrt(z.x * z.x + z.y * z.y);
	zc.x = r1 * cos(phi);
	zc.y = r1 * sin(phi);

	double xyR = sqrt(zc.x * zc.x + zc.y * zc.y);

	if (!fractal->transformCommon.functionEnabledMFalse)
		xyR = rb - xyR - fractal->transformCommon.offsetR0;
	else
	{
		if (!fractal->transformCommon.functionEnabledNFalse)
		{
			rb = rb * (1.0 - fractal->transformCommon.scaleA0)
					 + fractal->transformCommon.offsetR0 * fractal->transformCommon.scaleA0;
			xyR = rb - xyR;
		}
		else
		{
			xyR = rb - xyR;
			rb = rb - fractal->transformCommon.offsetR0;
			xyR = min(rb, xyR);
		}
	}

	double cylR = xyR;
	if (fractal->transformCommon.functionEnabledFalse)
	{
		cylR = fabs(cylR) - fractal->transformCommon.offsetp01;
		cylR = max(cylR, xyR);
	}

	double cylH = fabs(zc.z) - fractal->transformCommon.offsetA1;

	if (fractal->transformCommon.functionEnabledzFalse)
	{
		cylR = cylR + (zc.z * zc.z * fractal->transformCommon.scaleB0);
	}

	cylR = max(cylR, 0.0);
	cylH = max(cylH, 0.0);
	double cylD = sqrt(cylR * cylR + cylH * cylH);
	cylD = min(max(cylR, cylH), 0.0) + cylD;

	double colDist = aux.dist;
	aux.dist = min(aux.dist, cylD / (aux.DE + fractal->analyticDE.offset1));

	if (fractal->foldColor.auxColorEnabledFalse
			&& aux.i >= fractal->foldColor.startIterationsA
			&& aux.i < fractal->foldColor.stopIterationsA)
	{
		if (fractal->foldColor.auxColorEnabledA || colDist != aux.dist)
		{
			double colAdd = fractal->foldColor.difs0000.x
					+ aux.i * fractal->foldColor.difs0;

			if (fractal->foldColor.auxColorEnabledAFalse)
			{
				if (fractal->transformCommon.offsetA1 < fabs(zc.z))
					colAdd = fractal->foldColor.difs0000.y;
				if (xyR <= -fractal->transformCommon.offsetp01)
					colAdd = fractal->foldColor.difs0000.z;

				colAdd += fractal->foldColor.difs0000.w * rb;
			}
			if (!fractal->foldColor.auxColorEnabledBFalse)
			{
				aux.color = colAdd;
			}
			else
			{
				aux.color += colAdd;
			}
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

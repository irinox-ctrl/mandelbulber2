/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * TransfDIFSSpring
 */

#include "all_fractal_definitions.h"

cFractalTransfDIFSSpring::cFractalTransfDIFSSpring() : cAbstractFractal()
{
	nameInComboBox = "T>DIFS Spring";
	internalName = "transf_difs_spring";
	internalID = fractal::transfDIFSSpring;
	DEType = analyticDEType;
	DEFunctionType = customDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionCustomDE;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfDIFSSpring::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 zc = z;

	zc *= fractal->transformCommon.scale1;
	aux.DE *= fractal->transformCommon.scale1;
	zc += fractal->transformCommon.offset000;

	// swap axis
	if (fractal->transformCommon.functionEnabledSwFalse)
	{
		double temp = zc.x;
		zc.x = zc.z;
		zc.z = temp;
	}

	double T = sqrt(zc.x * zc.x + zc.y * zc.y) - fractal->transformCommon.minR05;

	double ht1 = fractal->transformCommon.int8X * fractal->transformCommon.offset01;
	double ht2 = fractal->transformCommon.int8Y * fractal->transformCommon.offsetp01;

	double L = fabs(zc.z) - ht1 - ht2;
	double P;
	if (fabs(zc.z) < ht1)
		P = fractal->transformCommon.offset01;
	else
		P = fractal->transformCommon.offsetp01;
	zc.z += atan2(zc.y, zc.x) / M_PI * P;
	zc.z = (zc.z - P * 2.0 * floor(zc.z / (P * 2.0))) - P;

	// L = max(max(T, L), 0.0);
	// L = sqrt(T * T + L * L);

	double dd;
	if (!fractal->transformCommon.functionEnabledJFalse)
		dd = sqrt(T * T + zc.z * zc.z);
	else
		dd = max(fabs(T), fabs(zc.z));

	dd = max(L, dd);
	double colDist = aux.dist;
	if (!fractal->analyticDE.enabledFalse)
		aux.dist = (dd - fractal->transformCommon.offset0005) / (aux.DE + 1.0);
	else
		aux.dist = min(aux.dist, (dd - fractal->transformCommon.offset0005) / (aux.DE + 1.0));

	aux.DE0 = (dd - fractal->transformCommon.offset0005); // temp testing

	if (fractal->transformCommon.functionEnabledYFalse) z = zc;

	if (fractal->foldColor.auxColorEnabledFalse && colDist != aux.dist
			&& aux.i >= fractal->foldColor.startIterationsA
			&& aux.i < fractal->foldColor.stopIterationsA)
	{
		double addCol = fractal->foldColor.difs0000.w
				+ aux.i * fractal->foldColor.difs0;
		if (P == fractal->transformCommon.offset01)
			addCol += fractal->foldColor.difs0000.x;
		else
			addCol += fractal->foldColor.difs0000.y;
		if (!fractal->foldColor.auxColorEnabledBFalse)
		{
			aux.color = addCol;
		}
		else
		{
			aux.color += addCol; // aux.color default 1
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

/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * TransfDifsBoxIteration  fragmentarium code, mdifs by knighty (jan 2012)
 */

#include "all_fractal_definitions.h"

cFractalTransfDIFSBox::cFractalTransfDIFSBox() : cAbstractFractal()
{
	nameInComboBox = "T>DIFS Box";
	internalName = "transf_difs_box";
	internalID = fractal::transfDIFSBox;
	DEType = analyticDEType;
	DEFunctionType = customDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionCustomDE;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfDIFSBox::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 q = fabs(z) - fractal->transformCommon.additionConstant111;
	CVector4 zc = q;
	zc.x = max(zc.x, 0.0);
	zc.y = max(zc.y, 0.0);
	zc.z = max(zc.z, 0.0);
	double zcd = zc.Length();
	double colDist = aux.dist;
	aux.dist = min(aux.dist, zcd / (aux.DE + 1.0) - fractal->transformCommon.offsetB0);

	if (fractal->foldColor.auxColorEnabledFalse && colDist != aux.dist
			&& aux.i >= fractal->foldColor.startIterationsA
			&& aux.i < fractal->foldColor.stopIterationsA)
	{
		double addCol = fractal->foldColor.difs0000.x
				+ aux.i * fractal->foldColor.difs0;

		if (fractal->foldColor.auxColorEnabledAFalse)
		{
			if (zc.x > max(zc.y, zc.z))
				addCol += fractal->foldColor.difs0000.y;
			if (zc.y > max(zc.x, zc.z))
				addCol += fractal->foldColor.difs0000.z;
			if (zc.z > max(zc.y, zc.x))
				addCol += fractal->foldColor.difs0000.w;

			if (fractal->transformCommon.offset0 != 0.0)
			{
				double t = z.x * z.y;
				if ((t > 0.0 && z.z > 0.0) || (t < 0.0 && z.z < 0.0))
					addCol += fractal->transformCommon.offset0;
			}
		}
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
		z *= fractal->transformCommon.scale4;
		aux.DE *= fabs(fractal->transformCommon.scale4);
	}

	// === General Purpose Multiplier 2 ===
	if (fractal->transformCommon.functionEnabledByFalse
		&& aux.i >= fractal->transformCommon.startIterationsC
		&& aux.i < fractal->transformCommon.stopIterationsC)
	{
		z *= fractal->transformCommon.scale5;
		aux.DE *= fabs(fractal->transformCommon.scale5);
	}

	// === General Purpose Multiplier 3 ===
	if (fractal->transformCommon.functionEnabledBzFalse
		&& aux.i >= fractal->transformCommon.startIterationsD
		&& aux.i < fractal->transformCommon.stopIterationsD)
	{
		z *= fractal->transformCommon.scale6;
		aux.DE *= fabs(fractal->transformCommon.scale6);
	}

	// === General Purpose Multiplier 4 ===
	if (fractal->transformCommon.functionEnabledBwFalse
		&& aux.i >= fractal->transformCommon.startIterationsE
		&& aux.i < fractal->transformCommon.stopIterationsE)
	{
		z *= fractal->transformCommon.scale8;
		aux.DE *= fabs(fractal->transformCommon.scale8);
	}

	// === General Purpose Multiplier 5 ===
	if (fractal->transformCommon.functionEnabledCzFalse
		&& aux.i >= fractal->transformCommon.startIterationsF
		&& aux.i < fractal->transformCommon.stopIterationsF)
	{
		z *= fractal->transformCommon.scale16;
		aux.DE *= fabs(fractal->transformCommon.scale16);
	}

}

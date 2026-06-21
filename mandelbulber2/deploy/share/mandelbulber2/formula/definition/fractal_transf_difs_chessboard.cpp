/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * TransfDIFSChessboard a chessboard pattern on a sdf box
 * http://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
 */

#include "all_fractal_definitions.h"

cFractalTransfDIFSChessboard::cFractalTransfDIFSChessboard() : cAbstractFractal()
{
	nameInComboBox = "T>DIFS Chessboard";
	internalName = "transf_difs_chessboard";
	internalID = fractal::transfDIFSChessboard;
	DEType = analyticDEType;
	DEFunctionType = customDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionCustomDE;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfDIFSChessboard::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 zc = z;
	if (!fractal->foldColor.auxColorEnabledFalse)
	{
		CVector4 col = zc + fractal->transformCommon.offset000;
		CVector4 repeats = fractal->transformCommon.scale3D444;
		repeats.x = floor(repeats.x * col.x);
		repeats.y = floor(repeats.y * col.y);
		repeats.z = floor(repeats.z * col.z);

		double auxCol;
		if (!fractal->transformCommon.functionEnabledCFalse)
		{
			auxCol = repeats.x + repeats.y;
		}
		else
		{
			auxCol = repeats.x + repeats.y + repeats.z;
		}
		auxCol = (auxCol * 0.5 - floor(auxCol * 0.5)) * 2.0;
		if (!fractal->foldColor.auxColorEnabledAFalse)
		{
			aux.color = auxCol;
		}
		else
		{
			aux.color += auxCol;
		}
	}

	double rDE;
	if (!fractal->transformCommon.functionEnabledFalse)
	{
		zc = fabs(zc) - fractal->transformCommon.offset110; // size
		rDE = max(zc.x, max(zc.y, zc.z));
	}
	else
		rDE = zc.z; // plane

	if (fractal->transformCommon.functionEnabledZcFalse
			&& aux.i >= fractal->transformCommon.startIterationsZc
			&& aux.i < fractal->transformCommon.stopIterationsZc)
		z = zc;

	if (!fractal->transformCommon.functionEnabledDFalse)
		aux.dist = min(aux.dist, rDE);
	else
		aux.dist = rDE;
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

/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Hybrid Color Trial2
 *
 *
 * bailout may need to be adjusted with some formulas
 */

#include "all_fractal_definitions.h"

cFractalTransfHybridColor2::cFractalTransfHybridColor2() : cAbstractFractal()
{
	nameInComboBox = "T>Hybrid Color2";
	internalName = "transf_hybrid_color2";
	internalID = fractal::transfHybridColor2;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfHybridColor2::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	if (aux.i >= fractal->transformCommon.startIterationsT
			&& aux.i < fractal->transformCommon.stopIterationsT)
	{
		double componentMaster = 0.0;
		double orbitPoints = 0.0;
		double distL = 0.0;
		double newR = 0.0;
		double lastVec = 0.0;
		double colTiling = 0.0;

		// summation of r
		if (fractal->transformCommon.functionEnabledMFalse)
		{
			newR = aux.r * fractal->transformCommon.scaleD1;
		}

		// max distance travelled
		if (fractal->transformCommon.functionEnabledSFalse)
		{
			CVector4 oldPt = aux.old_z;
			CVector4 newPt = z;
			CVector4 diffZ = oldPt - newPt;
			distL = diffZ.Length() * fractal->transformCommon.scaleC1;
		}

		// last two z lengths
		if (fractal->transformCommon.functionEnabledPFalse)
		{
			if (aux.i < fractal->transformCommon.stopIterationsM) // remove
			{
				CVector4 oldPt = aux.old_z;
				double lastZ = oldPt.Length(); // aux.old_r;
				double newZ = aux.r;
				if (fractal->transformCommon.functionEnabledBwFalse) lastVec = newZ / lastZ;
				if (fractal->transformCommon.functionEnabledByFalse) lastVec = lastZ / newZ;
				if (fractal->transformCommon.functionEnabledBzFalse) lastVec = fabs(lastZ - newZ);
				lastVec *= fractal->transformCommon.scaleB1;
			}
		}

		// orbitTrap points
		if (fractal->transformCommon.functionEnabledBxFalse)
		{
			CVector4 PtOne = z - fractal->transformCommon.offset000;
			double distOne = PtOne.Length(); // * weight
			orbitPoints = distOne;
			if (fractal->transformCommon.functionEnabledAzFalse)
			{
				CVector4 PtTwo = z - fractal->transformCommon.offsetA000;
				double distTwo = PtTwo.Length();
				orbitPoints = min(orbitPoints, distTwo);
			}
			if (fractal->transformCommon.functionEnabledAxFalse)
			{
				CVector4 PtThree = z - fractal->transformCommon.offsetF000;
				double distThree = PtThree.Length();
				orbitPoints = min(orbitPoints, distThree);
			}
			if (fractal->transformCommon.functionEnabledAyFalse)
			{
				CVector4 PtFour = z - fractal->transformCommon.additionConstantA000;
				double distFour = PtFour.Length();
				orbitPoints = min(orbitPoints, distFour);
			}
			orbitPoints *= fractal->transformCommon.scaleA1;
		}


			if (fractal->transformCommon.functionEnabledTFalse)
			{
				// REAL4 tV = 0.0f;
				//	if (fractal->foldColor.auxColorEnabledA) tV = z;
				//	else tV = aux->const_c;
				//	REAL4 tV = aux->const_c * (1.0f - fractal->foldColor.difs0000.w) + z *
				//fractal->foldColor.difs0000.w; // x * (1-a) +y * a

				double Size = 2.0 * fractal->transformCommon.scale3D111.x;
				double bb = ((z.x + Size) / Size) + fractal->transformCommon.additionConstantP000.x;
				bb = fabs(bb - round(bb)) * fractal->transformCommon.constantMultiplierC111.x;
				double dd = ((aux.const_c.x + Size) / Size) + fractal->transformCommon.additionConstantP000.x;
				dd = fabs(dd - round(dd)) * fractal->transformCommon.constantMultiplierC111.x;

				Size = 2.0 * fractal->transformCommon.scale3D111.y;
				double cc = ((z.y + Size) / Size) + fractal->transformCommon.additionConstantP000.y;
				cc = fabs(cc - round(cc)) * fractal->transformCommon.constantMultiplierC111.y;
				double ee = ((aux.const_c.y + Size) / Size) + fractal->transformCommon.additionConstantP000.y;
				ee = fabs(ee - round(ee)) * fractal->transformCommon.constantMultiplierC111.y;

				bb = bb + cc;
				dd = dd + ee;

				if (fractal->transformCommon.functionEnabledAFalse)
				{	Size = 2.0 * fractal->transformCommon.scale3D111.z;
					double aa = ((z.z + Size) / Size) + fractal->transformCommon.additionConstantP000.z;
					aa = fabs(aa - round(aa)) * fractal->transformCommon.constantMultiplierC111.z;
					bb = bb + aa;
					double ff = ((aux.const_c.z + Size) / Size) + fractal->transformCommon.additionConstantP000.z;
					ff = fabs(ff - round(ff)) * fractal->transformCommon.constantMultiplierC111.z;
					dd = dd + ff;
				}
				bb = dd * (1.0 - fractal->foldColor.difs0000.w) + bb * fractal->foldColor.difs0000.w; // mix

				colTiling = fractal->foldColor.difs1 * bb;
			}








		// build  componentMaster
		componentMaster = (distL + orbitPoints + lastVec + newR + colTiling);
		componentMaster *= fractal->transformCommon.scale;

		if (!fractal->transformCommon.functionEnabledFalse)
		{
			aux.colorHybrid += componentMaster;
		}
		else
		{
			aux.temp1000 = min(aux.temp1000, componentMaster);
			aux.colorHybrid = aux.temp1000;
		}
	}
	aux.old_z = z;
	// GPU bypass: skip if all multipliers disabled
	if (fractal->transformCommon.functionEnabledBxFalse || fractal->transformCommon.functionEnabledByFalse || fractal->transformCommon.functionEnabledBzFalse || fractal->transformCommon.functionEnabledBwFalse || fractal->transformCommon.functionEnabledCzFalse)
	{
		// === General Purpose Multiplier 1 ===
		if (fractal->transformCommon.functionEnabledBxFalse
				&& aux.i >= fractal->transformCommon.startIterationsB
				&& aux.i < fractal->transformCommon.stopIterationsB)
		{
			double val = fractal->transformCommon.scale4;

			if (fractal->transformCommon.multiplierInverse1) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode1;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsB - fractal->transformCommon.startIterationsB);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsB) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency1 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsB - fractal->transformCommon.startIterationsB);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsB) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode1)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 2 ===
		if (fractal->transformCommon.functionEnabledByFalse
				&& aux.i >= fractal->transformCommon.startIterationsC
				&& aux.i < fractal->transformCommon.stopIterationsC)
		{
			double val = fractal->transformCommon.scale5;

			if (fractal->transformCommon.multiplierInverse2) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode2;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsC - fractal->transformCommon.startIterationsC);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsC) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency2 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsC - fractal->transformCommon.startIterationsC);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsC) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode2)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 3 ===
		if (fractal->transformCommon.functionEnabledBzFalse
				&& aux.i >= fractal->transformCommon.startIterationsD
				&& aux.i < fractal->transformCommon.stopIterationsD)
		{
			double val = fractal->transformCommon.scale6;

			if (fractal->transformCommon.multiplierInverse3) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode3;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsD - fractal->transformCommon.startIterationsD);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsD) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency3 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsD - fractal->transformCommon.startIterationsD);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsD) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode3)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 4 ===
		if (fractal->transformCommon.functionEnabledBwFalse
				&& aux.i >= fractal->transformCommon.startIterationsE
				&& aux.i < fractal->transformCommon.stopIterationsE)
		{
			double val = fractal->transformCommon.scale8;

			if (fractal->transformCommon.multiplierInverse4) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode4;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsE - fractal->transformCommon.startIterationsE);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsE) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency4 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsE - fractal->transformCommon.startIterationsE);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsE) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode4)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 5 ===
		if (fractal->transformCommon.functionEnabledCzFalse
				&& aux.i >= fractal->transformCommon.startIterationsF
				&& aux.i < fractal->transformCommon.stopIterationsF)
		{
			double val = fractal->transformCommon.scale16;

			if (fractal->transformCommon.multiplierInverse5) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode5;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsF - fractal->transformCommon.startIterationsF);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsF) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency5 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsF - fractal->transformCommon.startIterationsF);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsF) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode5)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}
	}

}

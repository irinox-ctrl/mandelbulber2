/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * DIFSMultiV1
 * http://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
 */

#include "all_fractal_definitions.h"

cFractalDIFSMultiV1::cFractalDIFSMultiV1() : cAbstractFractal()
{
	nameInComboBox = "DIFS Multi V1";
	internalName = "difs_multi_v1";
	internalID = fractal::dIFSMultiV1;
	DEType = analyticDEType;
	DEFunctionType = customDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionCustomDE;
	coloringFunction = coloringFunctionDefault;
}

void cFractalDIFSMultiV1::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	double colorAdd = 0.0;
	CVector4 oldZ = z;
	CVector4 boxFold = fractal->transformCommon.additionConstantA111;

	// abs
	if (fractal->transformCommon.functionEnabledAx
			&& aux.i >= fractal->transformCommon.startIterationsX
			&& aux.i < fractal->transformCommon.stopIterationsX)
		z.x = fabs(z.x);

	if (fractal->transformCommon.functionEnabledAy
			&& aux.i >= fractal->transformCommon.startIterationsY
			&& aux.i < fractal->transformCommon.stopIterationsY)
		z.y = fabs(z.y);

	if (fractal->transformCommon.functionEnabledAzFalse
			&& aux.i >= fractal->transformCommon.startIterationsZ
			&& aux.i < fractal->transformCommon.stopIterationsZ)
		z.z = fabs(z.z);
	if (fractal->transformCommon.functionEnabledFalse)
	{
		// xy box fold
		if (fractal->transformCommon.functionEnabledAFalse
				&& aux.i >= fractal->transformCommon.startIterationsA
				&& aux.i < fractal->transformCommon.stopIterationsA)
		{
			z.x -= boxFold.x;
			z.y -= boxFold.y;
		}
		// xyz box fold
		if (fractal->transformCommon.functionEnabledBFalse
				&& aux.i >= fractal->transformCommon.startIterationsB
				&& aux.i < fractal->transformCommon.stopIterationsB)
			z -= boxFold;

		// polyfold
		if (fractal->transformCommon.functionEnabledPFalse
				&& aux.i >= fractal->transformCommon.startIterationsP
				&& aux.i < fractal->transformCommon.stopIterationsP)
		{
			z.x = fabs(z.x);
			double psi = M_PI / fractal->transformCommon.int6;
			psi = fabs(fmod(atan2(z.y, z.x) + psi, 2.0 * psi) - psi);
			double len = sqrt(z.x * z.x + z.y * z.y);
			z.x = cos(psi) * len;
			z.y = sin(psi) * len;
		}

		// diag fold1
		if (fractal->transformCommon.functionEnabledCxFalse
				&& aux.i >= fractal->transformCommon.startIterationsCx
				&& aux.i < fractal->transformCommon.stopIterationsCx)
			if (z.y > z.x) swap(z.x, z.y);

		// abs offsets
		if (fractal->transformCommon.functionEnabledCFalse
				&& aux.i >= fractal->transformCommon.startIterationsC
				&& aux.i < fractal->transformCommon.stopIterationsC)
		{
			double xOffset = fractal->transformCommon.offsetC0;
			if (z.x < xOffset) z.x = fabs(z.x - xOffset) + xOffset;
		}
		if (fractal->transformCommon.functionEnabledDFalse
				&& aux.i >= fractal->transformCommon.startIterationsD
				&& aux.i < fractal->transformCommon.stopIterationsD)
		{
			double yOffset = fractal->transformCommon.offsetD0;
			if (z.y < yOffset) z.y = fabs(z.y - yOffset) + yOffset;
		}

		// diag fold2
		if (fractal->transformCommon.functionEnabledCyFalse
				&& aux.i >= fractal->transformCommon.startIterationsCy
				&& aux.i < fractal->transformCommon.stopIterationsCy)
			if (z.y > z.x) swap(z.x, z.y);
	}

	// reverse offset part 1
	if (aux.i >= fractal->transformCommon.startIterationsE
			&& aux.i < fractal->transformCommon.stopIterationsE)
		z.x -= fractal->transformCommon.offsetE2;

	if (aux.i >= fractal->transformCommon.startIterationsF
			&& aux.i < fractal->transformCommon.stopIterationsF)
		z.y -= fractal->transformCommon.offsetF2;

	// scale
	double useScale = 1.0;
	if (aux.i >= fractal->transformCommon.startIterationsS
			&& aux.i < fractal->transformCommon.stopIterationsS)
	{
		useScale = aux.actualScaleA + fractal->transformCommon.scale2;
		z *= useScale;
		aux.DE = aux.DE * fabs(useScale) + 1.0;
		// else

		if (fractal->transformCommon.functionEnabledKFalse
				&& aux.i >= fractal->transformCommon.startIterationsK
				&& aux.i < fractal->transformCommon.stopIterationsK)
		{
			// update actualScaleA for next iteration
			double vary = fractal->transformCommon.scaleVary0
										* (fabs(aux.actualScaleA) - fractal->transformCommon.scaleC1);
			aux.actualScaleA -= vary;
		}
	}

	// reverse offset part 2
	if (aux.i >= fractal->transformCommon.startIterationsE
			&& aux.i < fractal->transformCommon.stopIterationsE)
		z.x += fractal->transformCommon.offsetE2;

	if (aux.i >= fractal->transformCommon.startIterationsF
			&& aux.i < fractal->transformCommon.stopIterationsF)
		z.y += fractal->transformCommon.offsetF2;

	// offset
	z += fractal->transformCommon.offset001;

	// rotation
	if (fractal->transformCommon.functionEnabledRFalse
			&& aux.i >= fractal->transformCommon.startIterationsR
			&& aux.i < fractal->transformCommon.stopIterationsR)
	{
		z = fractal->transformCommon.rotationMatrix.RotateVector(z);
	}

	// DE
	double colorDist = aux.dist;
	CVector4 zc = oldZ;

	if (fractal->transformCommon.functionEnabledFFalse) zc = z;

	// box
	if (fractal->transformCommon.functionEnabledM && aux.i >= fractal->transformCommon.startIterations
			&& aux.i < fractal->transformCommon.stopIterations)
	{
		CVector4 boxSize = fractal->transformCommon.additionConstant111;
		CVector4 bxV = zc;
		double bxD = 0.0;
		bxV = fabs(bxV) - boxSize;
		bxD = max(bxV.x, max(bxV.y, bxV.z)); // infnorm
		if (bxD > 0.0)
		{
			bxV.x = max(bxV.x, 0.0);
			bxV.y = max(bxV.y, 0.0);
			bxV.z = max(bxV.z, 0.0);
			aux.DE0 = bxV.Length();
		}
		aux.dist = min(aux.dist, aux.DE0 / aux.DE);
	}
	// sphere
	if (fractal->transformCommon.functionEnabledMFalse
			&& aux.i >= fractal->transformCommon.startIterationsM
			&& aux.i < fractal->transformCommon.stopIterationsM)
	{
		aux.DE0 = zc.Length() - fractal->transformCommon.offsetR1;
		aux.dist = min(aux.dist, aux.DE0 / aux.DE);
	}
	// cylinder
	if (fractal->transformCommon.functionEnabledOFalse
			&& aux.i >= fractal->transformCommon.startIterationsO
			&& aux.i < fractal->transformCommon.stopIterationsO)
	{
		double cylD = 0.0;
		//- fractal->transformCommon.scale0 * aux.i;

		if (fractal->transformCommon.functionEnabledSwFalse) swap(zc.x, zc.z);

		double cylR = sqrt(zc.x * zc.x + zc.y * zc.y);
		double cylH = fabs(zc.z) - fractal->transformCommon.offsetA1;

		double cylRm = cylR - fractal->transformCommon.radius1;

		if (!fractal->transformCommon.functionEnabledXFalse)
		{
			if (!fractal->transformCommon.functionEnabledzFalse) cylR = cylRm;
			cylR = max(cylR, 0.0);
			double cylHm = max(cylH, 0.0);
			cylD = sqrt(cylR * cylR + cylHm * cylHm);
		}
		else
			cylD = sqrt(cylRm * cylRm + cylH * cylH);

		aux.DE0 = min(max(cylRm, cylH) - fractal->transformCommon.offsetR0, 0.0) + cylD;
		aux.dist = min(aux.dist, aux.DE0 / aux.DE);
	}

	// torus
	if (fractal->transformCommon.functionEnabledTFalse
			&& aux.i >= fractal->transformCommon.startIterationsT
			&& aux.i < fractal->transformCommon.stopIterationsT)
	{
		// swap axis
		if (fractal->transformCommon.functionEnabledJFalse) swap(zc.x, zc.z);

		double T1 = sqrt(zc.y * zc.y + zc.x * zc.x) - fractal->transformCommon.offsetT1;
		aux.DE0 = sqrt(T1 * T1 + zc.z * zc.z) - fractal->transformCommon.offset05;
		aux.dist = min(aux.dist, aux.DE0 / aux.DE);
	}

	// prism
	if (fractal->transformCommon.functionEnabledNFalse
			&& aux.i >= fractal->transformCommon.startIterationsN
			&& aux.i < fractal->transformCommon.stopIterationsN)
	{
		// swap axis
		if (fractal->transformCommon.functionEnabledEFalse) swap(zc.x, zc.z);

		aux.DE0 = max(fabs(zc.x) - fractal->transformCommon.offset2,
			max(fabs(zc.y) * SQRT_3_4 + zc.z * 0.5, -zc.z) - fractal->transformCommon.offsetA05);

		aux.dist = min(aux.dist, aux.DE0 / aux.DE);
	}

	// aux.dist tweaks
	if (fractal->analyticDE.enabledFalse)
		aux.dist = aux.dist * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;

	// aux.color
/*	if (fractal->foldColor.auxColorEnabled)
	{
		if (fractal->foldColor.auxColorEnabledFalse)
		{
			colorAdd += fractal->foldColor.difs0000.x * fabs(z.x * z.y); // fabs(zc.x * zc.y)
			colorAdd += fractal->foldColor.difs0000.y * max(z.x, z.y);	 // max(z.x, z.y);
			colorAdd += fractal->foldColor.difs0000.z * (z.x * z.x + z.y * z.y);
			colorAdd += fractal->foldColor.difs0000.w * fabs(zc.x * zc.y);
		}
		colorAdd += fractal->foldColor.difs1;
		if (fractal->foldColor.auxColorEnabledA)
		{
			if (colorDist != aux.dist) aux.color += colorAdd;
		}
		else
			aux.color += colorAdd;
	}*/

	// aux.color
	if (fractal->foldColor.auxColorEnabled && colorDist != aux.dist
			&& aux.i >= fractal->foldColor.startIterationsA
			&& aux.i < fractal->foldColor.stopIterationsA)
	{
		 colorAdd += aux.i * fractal->foldColor.difs1 + fractal->foldColor.difs0;

		if (fractal->foldColor.auxColorEnabledFalse)
		{
			zc = fabs(zc);
			colorAdd += fractal->foldColor.difs0000.x * zc.x * zc.y;
			colorAdd += fractal->foldColor.difs0000.y * max(zc.x, zc.y);
			colorAdd += fractal->foldColor.difs0000.z * (z.x * z.x + z.y * z.y);
		//	colorAdd += fractal->foldColor.difs0000.w * fabs(zc.x * zc.y);
		}

		if (fractal->foldColor.auxColorEnabledA)
		{
			aux.color = colorAdd;
		}
		else
		{
			aux.color += colorAdd;
		}
	}
		// --- IFS/DIFS Extensions (15 parameters) ---
	{
		double ifsFoldOsc = fractal->transformCommon.ifsFoldOscAmp;
		double ifsFoldFreq = fractal->transformCommon.ifsFoldOscFreq;
		double ifsScaleOsc = fractal->transformCommon.ifsScaleOsc;
		double ifsScaleFreq = fractal->transformCommon.ifsScaleOscFreq;
		double ifsPreRot = fractal->transformCommon.ifsPreRotAngle;
		double ifsPostRot = fractal->transformCommon.ifsPostRotAngle;
		double ifsTwZ = fractal->transformCommon.ifsTwistZ;
		double ifsOffWarp = fractal->transformCommon.ifsOffsetWarp;
		double ifsRadDist = fractal->transformCommon.ifsRadialDistort;
		double ifsTurb = fractal->transformCommon.ifsTurbulence;
		double ifsGradCol = fractal->transformCommon.ifsGradientColor;
		double ifsDETw = fractal->transformCommon.ifsDETweak;
		double ifsCpix = fractal->transformCommon.ifsCpixelInject;
		double ifsSphere = fractal->transformCommon.ifsSphereFold;
		double ifsEdgeSoft = fractal->transformCommon.ifsEdgeSoftness;

		// 1-2. Fold oscillation
		if (ifsFoldOsc != 0.0)
		{
			double fOsc = ifsFoldOsc * sin(aux.i * ifsFoldFreq * 0.5);
			z.x += fOsc * sin(z.y * 3.0);
			z.y += fOsc * sin(z.z * 3.0);
			z.z += fOsc * sin(z.x * 3.0);
		}

		// 3-4. Scale oscillation
		if (ifsScaleOsc != 0.0)
		{
			double sOsc = 1.0 + ifsScaleOsc * sin(aux.i * ifsScaleFreq * 0.5);
			z *= sOsc;
			aux.DE *= fabs(sOsc);
		}

		// 5. Pre-rotation
		if (ifsPreRot != 0.0)
		{
			double a = ifsPreRot * M_PI / 180.0 * aux.i;
			double ca = cos(a); double sa = sin(a);
			double px = z.x * ca - z.y * sa;
			double py = z.x * sa + z.y * ca;
			z.x = px; z.y = py;
		}

		// 6. Post-rotation
		if (ifsPostRot != 0.0)
		{
			double a = ifsPostRot * M_PI / 180.0;
			double ca = cos(a); double sa = sin(a);
			double py = z.y * ca - z.z * sa;
			double pz = z.y * sa + z.z * ca;
			z.y = py; z.z = pz;
		}

		// 7. Twist Z
		if (ifsTwZ != 0.0)
		{
			double tw = ifsTwZ * M_PI / 180.0 * z.z;
			double ct = cos(tw); double st = sin(tw);
			double tx = z.x * ct - z.y * st;
			double ty = z.x * st + z.y * ct;
			z.x = tx; z.y = ty;
		}

		// 8. Offset warp
		if (ifsOffWarp != 0.0)
		{
			z.x += ifsOffWarp * sin(z.y * 2.0 + aux.i * 0.5);
			z.y += ifsOffWarp * sin(z.z * 2.0 + aux.i * 0.7);
			z.z += ifsOffWarp * sin(z.x * 2.0 + aux.i * 0.3);
		}

		// 9. Radial distortion
		if (ifsRadDist != 0.0)
		{
			double r = z.Length();
			if (r > 1e-15)
			{
				double distort = 1.0 + ifsRadDist * sin(r * 4.0);
				z *= distort;
				aux.DE *= fabs(distort);
			}
		}

		// 10. Turbulence
		if (ifsTurb != 0.0)
		{
			double hx = sin(z.x * 12.9898 + z.y * 78.233) * 43758.5453;
			hx = hx - floor(hx);
			double hy = sin(z.y * 12.9898 + z.z * 78.233) * 43758.5453;
			hy = hy - floor(hy);
			double hz = sin(z.z * 12.9898 + z.x * 78.233) * 43758.5453;
			hz = hz - floor(hz);
			z.x += (hx - 0.5) * ifsTurb;
			z.y += (hy - 0.5) * ifsTurb;
			z.z += (hz - 0.5) * ifsTurb;
		}

		// 11. Gradient color
		if (ifsGradCol != 0.0)
		{
			aux.color += ifsGradCol * z.Length();
		}

		// 12. DE tweak
		if (ifsDETw != 0.0)
		{
			aux.DE += ifsDETw;
		}

		// 13. C-pixel injection
		if (ifsCpix != 0.0)
		{
			z += aux.const_c * ifsCpix;
		}

		// 14. Sphere fold
		if (ifsSphere != 0.0)
		{
			double r2 = z.Dot(z);
			double minR2 = 0.25;
			double fixedR2 = 1.0;
			if (r2 < minR2)
			{
				double t = fixedR2 / minR2;
				z *= t * ifsSphere;
				aux.DE *= fabs(t * ifsSphere);
			}
			else if (r2 < fixedR2)
			{
				double t = fixedR2 / r2;
				z *= t * ifsSphere;
				aux.DE *= fabs(t * ifsSphere);
			}
		}

		// 15. Edge softness
		if (ifsEdgeSoft != 0.0)
		{
			double r = z.Length();
			if (r > 1e-15)
			{
				double soft = r / (r + ifsEdgeSoft);
				z *= soft;
				aux.DE *= soft;
			}
		}
	}

	// GPU bypass: skip if all multipliers disabled
	if (fractal->transformCommon.multiplierEnabled1 || fractal->transformCommon.multiplierEnabled2 || fractal->transformCommon.multiplierEnabled3 || fractal->transformCommon.multiplierEnabled4 || fractal->transformCommon.multiplierEnabled5)
	{
		double prevMultVal = 1.0;
		// === General Purpose Multiplier 1 ===
		if (fractal->transformCommon.multiplierEnabled1
				&& aux.i >= fractal->transformCommon.multiplierStartIter1
				&& aux.i < fractal->transformCommon.multiplierStopIter1)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode1;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold1)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold1))
			{
				double val = fractal->transformCommon.multiplierScale1;

				if (fractal->transformCommon.multiplierInverse1) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode1;
				double range = (double)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
				double ph = fractal->transformCommon.multiplierPhase1;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.multiplierStartIter1) / range;
					double freq = fractal->transformCommon.multiplierFrequency1;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * sin((t * freq + ph) * 2.0 * M_PI);
					}
					else if (vmode == 2) // Ramp
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + (val - 1.0) * (exp(t * freq) - 1.0) / (exp(freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						double tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = qBound(0.0, t, 1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux.i * 73856093 + 1 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						double noise = (double)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						double pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						double steps = freq;
						if (steps < 1.0) steps = 1.0;
						double st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				double w = fractal->transformCommon.multiplierWeight1;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode1)
				{
					default:
					case 0:
					{
						double valY = fractal->transformCommon.multiplierScaleY1;
						double valZ = fractal->transformCommon.multiplierScaleZ1;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux.DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; aux.DE *= fabs(val); break;
					case 2: z.y *= val; aux.DE *= fabs(val); break;
					case 3: z.z *= val; aux.DE *= fabs(val); break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; aux.DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux.DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 2 ===
		if (fractal->transformCommon.multiplierEnabled2
				&& aux.i >= fractal->transformCommon.multiplierStartIter2
				&& aux.i < fractal->transformCommon.multiplierStopIter2)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode2;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold2)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold2))
			{
				double val = fractal->transformCommon.multiplierScale2;

				if (fractal->transformCommon.multiplierInverse2) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode2;
				double range = (double)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
				double ph = fractal->transformCommon.multiplierPhase2;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.multiplierStartIter2) / range;
					double freq = fractal->transformCommon.multiplierFrequency2;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * sin((t * freq + ph) * 2.0 * M_PI);
					}
					else if (vmode == 2) // Ramp
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + (val - 1.0) * (exp(t * freq) - 1.0) / (exp(freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						double tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = qBound(0.0, t, 1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux.i * 73856093 + 2 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						double noise = (double)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						double pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						double steps = freq;
						if (steps < 1.0) steps = 1.0;
						double st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain2) val *= prevMultVal;

				double w = fractal->transformCommon.multiplierWeight2;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode2)
				{
					default:
					case 0:
					{
						double valY = fractal->transformCommon.multiplierScaleY2;
						double valZ = fractal->transformCommon.multiplierScaleZ2;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux.DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; aux.DE *= fabs(val); break;
					case 2: z.y *= val; aux.DE *= fabs(val); break;
					case 3: z.z *= val; aux.DE *= fabs(val); break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; aux.DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux.DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 3 ===
		if (fractal->transformCommon.multiplierEnabled3
				&& aux.i >= fractal->transformCommon.multiplierStartIter3
				&& aux.i < fractal->transformCommon.multiplierStopIter3)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode3;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold3)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold3))
			{
				double val = fractal->transformCommon.multiplierScale3;

				if (fractal->transformCommon.multiplierInverse3) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode3;
				double range = (double)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
				double ph = fractal->transformCommon.multiplierPhase3;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.multiplierStartIter3) / range;
					double freq = fractal->transformCommon.multiplierFrequency3;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * sin((t * freq + ph) * 2.0 * M_PI);
					}
					else if (vmode == 2) // Ramp
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + (val - 1.0) * (exp(t * freq) - 1.0) / (exp(freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						double tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = qBound(0.0, t, 1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux.i * 73856093 + 3 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						double noise = (double)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						double pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						double steps = freq;
						if (steps < 1.0) steps = 1.0;
						double st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain3) val *= prevMultVal;

				double w = fractal->transformCommon.multiplierWeight3;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode3)
				{
					default:
					case 0:
					{
						double valY = fractal->transformCommon.multiplierScaleY3;
						double valZ = fractal->transformCommon.multiplierScaleZ3;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux.DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; aux.DE *= fabs(val); break;
					case 2: z.y *= val; aux.DE *= fabs(val); break;
					case 3: z.z *= val; aux.DE *= fabs(val); break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; aux.DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux.DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 4 ===
		if (fractal->transformCommon.multiplierEnabled4
				&& aux.i >= fractal->transformCommon.multiplierStartIter4
				&& aux.i < fractal->transformCommon.multiplierStopIter4)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode4;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold4)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold4))
			{
				double val = fractal->transformCommon.multiplierScale4;

				if (fractal->transformCommon.multiplierInverse4) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode4;
				double range = (double)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
				double ph = fractal->transformCommon.multiplierPhase4;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.multiplierStartIter4) / range;
					double freq = fractal->transformCommon.multiplierFrequency4;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * sin((t * freq + ph) * 2.0 * M_PI);
					}
					else if (vmode == 2) // Ramp
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + (val - 1.0) * (exp(t * freq) - 1.0) / (exp(freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						double tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = qBound(0.0, t, 1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux.i * 73856093 + 4 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						double noise = (double)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						double pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						double steps = freq;
						if (steps < 1.0) steps = 1.0;
						double st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain4) val *= prevMultVal;

				double w = fractal->transformCommon.multiplierWeight4;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode4)
				{
					default:
					case 0:
					{
						double valY = fractal->transformCommon.multiplierScaleY4;
						double valZ = fractal->transformCommon.multiplierScaleZ4;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux.DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; aux.DE *= fabs(val); break;
					case 2: z.y *= val; aux.DE *= fabs(val); break;
					case 3: z.z *= val; aux.DE *= fabs(val); break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; aux.DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux.DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 5 ===
		if (fractal->transformCommon.multiplierEnabled5
				&& aux.i >= fractal->transformCommon.multiplierStartIter5
				&& aux.i < fractal->transformCommon.multiplierStopIter5)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode5;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold5)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold5))
			{
				double val = fractal->transformCommon.multiplierScale5;

				if (fractal->transformCommon.multiplierInverse5) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode5;
				double range = (double)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
				double ph = fractal->transformCommon.multiplierPhase5;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.multiplierStartIter5) / range;
					double freq = fractal->transformCommon.multiplierFrequency5;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * sin((t * freq + ph) * 2.0 * M_PI);
					}
					else if (vmode == 2) // Ramp
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + (val - 1.0) * (exp(t * freq) - 1.0) / (exp(freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						double tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = qBound(0.0, t, 1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux.i * 73856093 + 5 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						double noise = (double)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						double pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						double steps = freq;
						if (steps < 1.0) steps = 1.0;
						double st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain5) val *= prevMultVal;

				double w = fractal->transformCommon.multiplierWeight5;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode5)
				{
					default:
					case 0:
					{
						double valY = fractal->transformCommon.multiplierScaleY5;
						double valZ = fractal->transformCommon.multiplierScaleZ5;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux.DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; aux.DE *= fabs(val); break;
					case 2: z.y *= val; aux.DE *= fabs(val); break;
					case 3: z.z *= val; aux.DE *= fabs(val); break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; aux.DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux.DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}
	}

}

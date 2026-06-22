/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Created by Nrx in 2016-09-26
 * https://www.shadertoy.com/view/XlyGDm
 */

#include "all_fractal_definitions.h"

cFractalTransfDIFSDiamond::cFractalTransfDIFSDiamond() : cAbstractFractal()
{
	nameInComboBox = "T>DIFS Diamond";
	internalName = "transf_difs_diamond";
	internalID = fractal::transfDIFSDiamond;
	DEType = analyticDEType;
	DEFunctionType = customDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionCustomDE;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfDIFSDiamond::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 normalTopA = CVector4(0.0, 0.81373347121, 0.5812382, 0.0);
	CVector4 normalTopB = CVector4(0.0, SQRT_1_2, SQRT_1_2, 0.0);
	CVector4 normalTopC = CVector4(0.0, 0.4472135955, 0.8944272, 0.0);
	CVector4 normalBottomA = CVector4(0.0, SQRT_1_2, -SQRT_1_2, 0.0);
	CVector4 normalBottomB = CVector4(0.0, 0.848, -0.53, 0.0);

	if (fractal->transformCommon.functionEnabledPFalse
			&& aux.i >= fractal->transformCommon.startIterationsP
			&& aux.i < fractal->transformCommon.stopIterationsP1)
	{
		// pre abs
		if (fractal->transformCommon.functionEnabledx) z.x = fabs(z.x);
		if (fractal->transformCommon.functionEnabledy) z.y = fabs(z.y);
		if (fractal->transformCommon.functionEnabledzFalse) z.z = fabs(z.z);

		if (fractal->transformCommon.functionEnabledCx)
		{
			double psi = M_PI / fractal->transformCommon.int8X;
			psi = fabs(fmod(atan2(z.y, z.x) + psi, 2.0 * psi) - psi);
			double len = sqrt(z.x * z.x + z.y * z.y);
			z.x = cos(psi) * len;
			z.y = sin(psi) * len;
		}

		if (fractal->transformCommon.functionEnabledCyFalse)
		{
			double psi = M_PI / fractal->transformCommon.int8Y;
			psi = fabs(fmod(atan2(z.z, z.y) + psi, 2.0 * psi) - psi);
			double len = sqrt(z.y * z.y + z.z * z.z);
			z.y = cos(psi) * len;
			z.z = sin(psi) * len;
		}

		// addition constant
		z += fractal->transformCommon.additionConstant000;

		// rotation
		if (fractal->transformCommon.rotation2EnabledFalse)
		{
			z = fractal->transformCommon.rotationMatrix.RotateVector(z);
		}
	}

	CVector4 zc = z;
	zc *= fractal->transformCommon.scale1;
	aux.DE *= fractal->transformCommon.scale1;
	double topCut = zc.z - fractal->transformCommon.offset1;
	double angleStep = M_PI / fractal->transformCommon.int16;
	double angle = angleStep * (0.5 + floor(atan2(zc.x, zc.y) / angleStep));
	double co = cos(angle);
	double si = sin(angle);
	CVector4 q = zc;
	q.z -= fractal->transformCommon.offset0;
	q.x = (co * zc.x - si * zc.y);
	q.y = (co * zc.y + si * zc.x);
	double topA = q.Dot(normalTopA) - fractal->transformCommon.offset2;
	double topC = q.Dot(normalTopC) - fractal->transformCommon.offset105;
	double bottomA = q.Dot(normalBottomA) - fractal->transformCommon.offsetA2 + 0.3;
	angle = -angleStep * 0.5;
	co = cos(angle);
	si = sin(angle);
	q.x = (co * zc.x - si * zc.y);
	q.y = (co * zc.y + si * zc.x);
	angle = angleStep * floor(atan2(q.x, q.y) / angleStep);
	co = cos(angle);
	si = sin(angle);
	q.x = (co * zc.x - si * zc.y);
	q.y = (co * zc.y + si * zc.x);
	double topB = q.Dot(normalTopB) - fractal->transformCommon.offsetE2 + 0.15;
	double bottomB = q.Dot(normalBottomB) - fractal->transformCommon.offsetF2 + 0.1;

	aux.DE0 = max(topCut, max(topA, max(topB, max(topC, max(bottomA, bottomB)))));
	double colDist = aux.dist;
	if (!fractal->analyticDE.enabledFalse)
		aux.dist = aux.DE0 / aux.DE;
	else
		aux.dist = min(aux.dist, aux.DE0 / aux.DE);

	if (fractal->transformCommon.functionEnabledYFalse) z = q;

	if (fractal->foldColor.auxColorEnabledFalse && colDist != aux.dist
			&& aux.i >= fractal->foldColor.startIterationsA
			&& aux.i < fractal->foldColor.stopIterationsA)
	{
		double addCol = fractal->transformCommon.offsetA0
				+ aux.i * fractal->foldColor.difs0;

		CVector4 col = fabs(q);
		addCol += fractal->foldColor.difs0000.x * col.x * col.y;
		addCol += fractal->foldColor.difs0000.y * col.x * col.z;
		addCol += fractal->foldColor.difs0000.z * q.z;
		addCol += fractal->foldColor.difs0000.w * max(col.x, col.y);

		if (!fractal->foldColor.auxColorEnabledBFalse)
		{
			aux.color = addCol;
		}
		else
		{
			aux.color += addCol;
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

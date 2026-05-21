/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Based on a DarkBeam fold formula adapted by Knighty
 * http://www.fractalforums.com/amazing-box-amazing-surf-and-variations/'new'-fractal-type-mandalay/msg81348/#msg81348
 */

#include "all_fractal_definitions.h"

cFractalMandalayBoxV2::cFractalMandalayBoxV2() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Box V2";
	internalName = "mandalay_box_v2";
	internalID = fractal::mandalayBoxV2;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayBoxV2::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	double colorAdd = 0.0;
	double rrCol = 0.0;

	// === #7 Quaternion Pre-Rotation (4D → 3D) ===
	if (fractal->mandalay.quatRotEnabled)
	{
		double qw = fractal->mandalay.quatRot.w;
		double qi = fractal->mandalay.quatRot.x;
		double qj = fractal->mandalay.quatRot.y;
		double qk = fractal->mandalay.quatRot.z;
		// q * z * q^-1 (z as pure quaternion)
		double tx = qw*z.x + qj*z.z - qk*z.y;
		double ty = qw*z.y + qk*z.x - qi*z.z;
		double tz = qw*z.z + qi*z.y - qj*z.x;
		double tw = -(qi*z.x + qj*z.y + qk*z.z);
		z.x = tx*qw - tw*qi - ty*qk + tz*qj;
		z.y = ty*qw - tw*qj - tz*qi + tx*qk;
		z.z = tz*qw - tw*qk - tx*qj + ty*qi;
	}

	// === #3 Pre-Sphere Inversion (Kleinian-style Möbius) ===
	if (fractal->mandalay.preSphereInvertEnabled)
	{
		CVector4 c_inv = fractal->mandalay.invertCenter;
		double radius = c_inv.w;
		CVector4 diff = z - CVector4(c_inv.x, c_inv.y, c_inv.z, 0.0);
		double dist2 = diff.Dot(diff);
		if (dist2 < radius * radius && dist2 > 1e-21)
		{
			double factor = radius * radius / dist2;
			z = CVector4(c_inv.x, c_inv.y, c_inv.z, 0.0) + diff * factor;
			aux.DE *= factor;
		}
	}

	// tglad fold
	if (fractal->transformCommon.functionEnabledAFalse
			&& aux.i >= fractal->transformCommon.startIterationsA
			&& aux.i < fractal->transformCommon.stopIterationsA)
	{
		z.x = fabs(z.x + fractal->transformCommon.additionConstant111.x)
					- fabs(z.x - fractal->transformCommon.additionConstant111.x) - z.x;
		z.y = fabs(z.y + fractal->transformCommon.additionConstant111.y)
					- fabs(z.y - fractal->transformCommon.additionConstant111.y) - z.y;
		if (fractal->transformCommon.functionEnabled)
		{
			z.z = fabs(z.z + fractal->transformCommon.additionConstant111.z)
						- fabs(z.z - fractal->transformCommon.additionConstant111.z) - z.z;
		}
	}

	double signX = sign(z.x);
	double signY = sign(z.y);
	double signZ = sign(z.z);

	if (fractal->transformCommon.functionEnabledPFalse
			&& aux.i >= fractal->transformCommon.startIterationsP
			&& aux.i < fractal->transformCommon.stopIterationsP)
	{
		if (fractal->transformCommon.functionEnabledAx) z.x = fabs(z.x);
		if (fractal->transformCommon.functionEnabledAy) z.y = fabs(z.y);
		if (fractal->transformCommon.functionEnabledAz) z.z = fabs(z.z);
	}
	else
	{
		z = fabs(z);
	}

	// === #6 Variable Clip Limits (adaptive fo/g) ===
	CVector4 fo = fractal->transformCommon.additionConstant0555;
	CVector4 g = fractal->transformCommon.offsetA000;
	if (fractal->mandalay.variableClipEnabled)
	{
		double adaptive = 1.0 + fractal->mandalay.foVary * (aux.r - 1.0);
		fo *= adaptive;
		double gAdaptive = 1.0 + fractal->mandalay.gVary * (aux.r - 1.0);
		g *= gAdaptive;
	}

	// === Mandalay 3D clip (with optional multi-sequencing #2) ===
	int numClipPasses = 1;
	CVector4 foArray[4];
	CVector4 gArray[4];
	foArray[0] = fo;
	gArray[0] = g;

	if (fractal->mandalay.multiClipEnabled && fractal->mandalay.numClips > 1)
	{
		numClipPasses = min(fractal->mandalay.numClips, 4);
		if (numClipPasses > 1) { foArray[1] = fractal->mandalay.fo2; gArray[1] = fractal->mandalay.g2; }
		if (numClipPasses > 2) { foArray[2] = fractal->mandalay.fo3; gArray[2] = fractal->mandalay.g3; }
		if (numClipPasses > 3) { foArray[3] = fractal->mandalay.fo4; gArray[3] = fractal->mandalay.g4; }
	}

	for (int clip = 0; clip < numClipPasses; clip++)
	{
		CVector4 cfo = foArray[clip];
		CVector4 cg = gArray[clip];
		CVector4 p = z;
		CVector4 q = z;
		double t1, t2, v, v1;

		if(p.z > p.y) swap(p.y, p.z);
		t1 = p.x - 2.0 * cfo.x;
		t2 = p.y - 4.0 * cfo.x;
		v = max(fabs(t1 + cfo.x) - cfo.x, t2);
		v1 = max(t1 - cg.x, p.y);
		v = min(v, v1);
		q.x = min(v, p.x);

		if (!fractal->transformCommon.functionEnabledSwFalse) p = z;
		else p = q;

		if(p.x > p.z) swap(p.z, p.x);
		t1 = p.y - 2.0 * cfo.y;
		t2 = p.z - 4.0 * cfo.y;
		v = max(fabs(t1 + cfo.y) - cfo.y, t2);
		v1 = max(t1 - cg.y, p.z);
		v = min(v, v1);
		q.y = min(v, p.y);

		if (!fractal->transformCommon.functionEnabledSwFalse) p = z;
		else p = q;

		if(p.y > p.x) swap(p.x, p.y);
		t1 = p.z - 2.0 * cfo.z;
		t2 = p.x - 4.0 * cfo.z;
		v = max(fabs(t1 + cfo.z) - cfo.z, t2);
		v1 = max(t1 - cg.z, p.x);
		v = min(v, v1);
		q.z = min(v, p.z);

		z = q;
	}

	z.x *= signX;
	z.y *= signY;
	z.z *= signZ;

	// === #1 Cylinder Fold (XY-plane, Z unaffected) ===
	if (fractal->mandalay.cylinderFoldEnabled
			&& aux.i >= fractal->mandalay.startIterationsCy
			&& aux.i < fractal->mandalay.stopIterationsCy)
	{
		double rr_cyl = z.x * z.x + z.y * z.y;
		double minCylR = fractal->mandalay.cylMinR;
		double cylMix = fractal->mandalay.cylMix;
		double useScale_cyl = aux.actualScaleA + fractal->transformCommon.scale2;
		double cyl_dividend = (rr_cyl < minCylR) ? minCylR : min(rr_cyl, 1.0);
		if (cyl_dividend > 1e-21)
		{
			double cyl_m = useScale_cyl / cyl_dividend;
			z.x *= (cyl_m - 1.0) * cylMix + 1.0;
			z.y *= (cyl_m - 1.0) * cylMix + 1.0;
			aux.DE = aux.DE * fabs(cyl_m) + 1.0;
		}
	}

	// === #5 Z-Shear / Parabolische Diepte-Vervorming ===
	if (fractal->mandalay.zShearEnabled)
	{
		double r_xy = z.x * z.x + z.y * z.y;
		z.z += fractal->mandalay.zShearStrength * r_xy;
	}

	// spherical fold
	double useScale = 1.0;
	if (aux.i >= fractal->transformCommon.startIterationsS
			&& aux.i < fractal->transformCommon.stopIterationsS)
	{

		double rr = z.Dot(z);
		rrCol = rr;
		if (rr < fractal->transformCommon.minR2p25)
		{
			double tglad_factor1 = fractal->transformCommon.maxR2d1 / fractal->transformCommon.minR2p25;
			z *= tglad_factor1;
			aux.DE *= tglad_factor1;
		}
		else if (rr < fractal->transformCommon.maxR2d1)
		{
			double tglad_factor2 = fractal->transformCommon.maxR2d1 / rr;
			z *= tglad_factor2;
			aux.DE *= tglad_factor2;
		}
	}

	// === #4 Anisotrope Scale (per-axis) ===
	if (fractal->mandalay.anisotropeScaleEnabled)
	{
		CVector4 s3d = fractal->mandalay.scale3D;
		z.x *= s3d.x;
		z.y *= s3d.y;
		z.z *= s3d.z;
		double maxScale = max(fabs(s3d.x), max(fabs(s3d.y), fabs(s3d.z)));
		aux.DE = aux.DE * maxScale + 1.0;
	}
	else
	{
		// original uniform scale
		useScale = aux.actualScaleA + fractal->transformCommon.scale2;
		z *= useScale;
		aux.DE = aux.DE * fabs(useScale) + 1.0;
	}

	if (fractal->transformCommon.functionEnabledKFalse
			&& aux.i >= fractal->transformCommon.startIterationsK
			&& aux.i < fractal->transformCommon.stopIterationsK)
	{
		// update actualScaleA for next iteration
		double vary = fractal->transformCommon.scaleVary0
									* (fabs(aux.actualScaleA) - fractal->transformCommon.scaleC1);
		aux.actualScaleA -= vary;
	}

	// rotation
	if (fractal->transformCommon.rotationEnabled && aux.i >= fractal->transformCommon.startIterationsR
			&& aux.i < fractal->transformCommon.stopIterationsR)
	{
		z = fractal->transformCommon.rotationMatrix.RotateVector(z);
	}

	if (fractal->analyticDE.enabledFalse)
		aux.DE =  aux.DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;

	if (fractal->foldColor.auxColorEnabledFalse)
	{
		if (rrCol < fractal->transformCommon.maxR2d1)
		{
			colorAdd += fractal->mandelbox.color.factorSp2 * (fractal->transformCommon.maxR2d1 - rrCol);
			if (rrCol < fractal->transformCommon.minR2p25)
				colorAdd += fractal->mandelbox.color.factorSp1 * (fractal->transformCommon.minR2p25 - rrCol)
										+ fractal->mandelbox.color.factorSp2
												* (fractal->transformCommon.maxR2d1 - fractal->transformCommon.minR2p25);
		}
		aux.color += colorAdd;
	}

	//aux.dist
	if (fractal->transformCommon.functionEnabledOFalse)
	{
		CVector4 pd = fabs(z);
		aux.DE0 = max(pd.x, max(pd.y, pd.z));
		aux.dist = min(aux.dist, aux.DE0 / aux.DE);
	}
}

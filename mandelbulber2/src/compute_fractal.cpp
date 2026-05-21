/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2014-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
 *                                        ,=mm=§M ]=4 yJKA"/-Nsaj  "Bw,==,,
 * This file is part of Mandelbulber.    §R.r= jw",M  Km .mM  FW ",§=ß., ,TN
 *                                     ,4R =%["w[N=7]J '"5=],""]]M,w,-; T=]M
 * Mandelbulber is free software:     §R.ß~-Q/M=,=5"v"]=Qf,'§"M= =,M.§ Rz]M"Kw
 * you can redistribute it and/or     §w "xDY.J ' -"m=====WeC=\ ""%""y=%"]"" §
 * modify it under the terms of the    "§M=M =D=4"N #"%==A%p M§ M6  R' #"=~.4M
 * GNU General Public License as        §W =, ][T"]C  §  § '§ e===~ U  !§[Z ]N
 * published by the                    4M",,Jm=,"=e~  §  §  j]]""N  BmM"py=ßM
 * Free Software Foundation,          ]§ T,M=& 'YmMMpM9MMM%=w=,,=MT]M m§;'§,
 * either version 3 of the License,    TWw [.j"5=~N[=§%=%W,T ]R,"=="Y[LFT ]N
 * or (at your option)                   TW=,-#"%=;[  =Q:["V""  ],,M.m == ]N
 * any later version.                      J§"mr"] ,=,," =="""J]= M"M"]==ß"
 *                                          §= "=C=4 §"eM "=B:m|4"]#F,§~
 * Mandelbulber is distributed in            "9w=,,]w em%wJ '"~" ,=,,ß"
 * the hope that it will be useful,                 . "K=  ,=RMMMßM"""
 * but WITHOUT ANY WARRANTY;                            .'''
 * without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with Mandelbulber. If not, see <http://www.gnu.org/licenses/>.
 *
 * ###########################################################################
 *
 * Authors: Krzysztof Marczak (buddhi1980@gmail.com)
 *
 * Compute - function fractal computation
 */

#include "compute_fractal.hpp"

#include <cmath>

#include "common_math.h"
#include "fractal.h"
#include "material.h"
#include "nine_fractals.hpp"
#include "orbit_trap_shape.hpp"

#include "formula/definition/legacy_fractal_transforms.hpp"

using namespace fractal;

template <fractal::enumCalculationMode Mode>
void Compute(const cNineFractals &fractals, const cHybridFractalSequences::sSequence *seq,
	const sFractalIn &in, sFractalOut *out)
{
	cAbstractFractal *fractalFormulaFunction;

	// repeat, move and rotate
	CVector3 pointTransformed = in.point - in.common->fractalPosition;
	pointTransformed = in.common->mRotFractalRotation.RotateVector(pointTransformed);
	pointTransformed = pointTransformed.repeatMod(in.common->repeat);

	CVector4 z = CVector4(pointTransformed, 0.0);

	double colorMin = 1000.0;

	if (in.forcedFormulaIndex >= 0)
	{
		z.w = fractals.GetInitialWAxis(in.forcedFormulaIndex);
	}
	else
	{
		z.w = fractals.GetInitialWAxis(0);
	}

	// double r = z.Length();

	double initialWAxisColor = z.w;

	double orbitTrapTotal = 0.0;
	out->orbitTrapR = 0.0;
	out->orbitTrapMinIter = 0;
	out->orbitTrapCenterIndex = 0;
	double orbitTrapMinDist = 1e30;
	out->orbitSampleCount = 0;
	for (int s = 0; s < sFractalOut::maxOrbitSamples; s++)
	{
		out->orbitSamples[s] = CVector3(0.0, 0.0, 0.0);
		out->orbitSampleIters[s] = 0;
	}

	enumFractalFormula formula = fractal::none;

	out->maxiter = true;

	int fractalIndex = 0;
	if (in.forcedFormulaIndex >= 0) fractalIndex = in.forcedFormulaIndex;

	const sFractal *defaultFractal = fractals.GetFractal(fractalIndex);

	sExtendedAux aux;

	aux.c = z;			 // variable c
	aux.const_c = z; // constant c
	aux.old_z = z;	 // used in hybrid color2
	aux.pos_neg = 1.0;
	aux.r = z.Length();					// r
	aux.DE = 1.0;								// partially calculated distance (derivative)  in fractal formulas
	aux.DE0 = 0.0;							// used in difs formulas
	aux.dist = 1000.0;					// used in difs formulas
	aux.pseudoKleinianDE = 1.0; // used to calculate DE for pseudo kleinian

	aux.actualScale = fractals.GetFractal(fractalIndex)->mandelbox.scale; // used for vary scale
	aux.actualScaleA = 0.0;																								// used for vary scale
	aux.color = 1.0;			 // used to calculate color from most of formulas
	aux.colorHybrid = 0.0; // used for hybrid color
	aux.temp1000 = 1000.0; // used for hybrid color 2 (initial value 1000)

	// main iteration loop
	int i;
	int sequence = 0;

	CVector4 lastGoodZ;
	CVector4 lastZ;
	CVector4 lastLastZ;
	CVector4 autoTrapCenter(0, 0, 0, 0);  // for auto-center mode
	bool autoTrapCenterSet = false;

	int fakeLightsMinIter = in.common->fakeLightsMinIter;
	int fakeLightsMaxIter = in.common->fakeLightsMaxIter;

	if (Mode == calcModeOrbitTrap)
	{
		if (in.orbitTrapIndex == 0)
		{
			if (in.common->fakeLightsColor2Enabled) fakeLightsMaxIter = fakeLightsMinIter;
		}
		else if (in.orbitTrapIndex == 1)
		{
			fakeLightsMinIter = in.common->fakeLightsMinIter + 1;
			fakeLightsMaxIter = max(fakeLightsMinIter, in.common->fakeLightsMaxIter);
			if (in.common->fakeLightsColor3Enabled) fakeLightsMaxIter = fakeLightsMinIter;
		}
		else if (in.orbitTrapIndex == 2)
		{
			fakeLightsMinIter = in.common->fakeLightsMinIter + 2;
			fakeLightsMaxIter = max(fakeLightsMinIter, in.common->fakeLightsMaxIter);
		}
	}

	int maxN;

	if (in.forcedFormulaIndex >= 0)
	{
		maxN = fractals.GetFormulaMaxiter(in.forcedFormulaIndex) * in.maxiterMultiplier;
	}
	else
	{
		maxN = fractals.GetFormulaMaxiter(0) * in.maxiterMultiplier;
	}
	if (in.forcedMaxiter >= 0) maxN = in.forcedMaxiter;

	// main iteration loop
	for (i = 0; i < maxN; i++)
	{
		lastLastZ = lastGoodZ; // FIX: was lastZ, maar moet z_{i-2} zijn
		lastGoodZ = lastZ;

		lastZ = z;

		// hybrid fractal sequence
		if (in.forcedFormulaIndex >= 0)
		{
			sequence = in.forcedFormulaIndex;
		}
		else
		{
			if (seq)
			{
				// FIXME it should return sequence instead instead of objectID
				// it is temporary solution
				sequence = seq->GetSequence(i);
			}
			else
			{
				sequence = fractals.GetSequence(i);
			}
		}

		// foldings
		if (in.common->foldings.boxEnable)
		{
			BoxFolding(z, &in.common->foldings, aux);
			aux.r = z.Length();
		}

		if (in.common->foldings.sphericalEnable)
		{
			SphericalFolding(z, &in.common->foldings, aux);
			aux.r = z.Length();
		}

		const sFractal *fractal = fractals.GetFractal(sequence);
		formula = fractal->formula;

		// temporary values for weight function — save ALL modifiable aux fields
		CVector4 tempZ = z;
		double tempAuxDE = aux.DE;
		double tempAuxDE0 = aux.DE0;
		double tempAuxDist = aux.dist;
		double tempAuxPseudoKleinianDE = aux.pseudoKleinianDE;
		double tempAuxActualScale = aux.actualScale;
		double tempAuxActualScaleA = aux.actualScaleA;
		double tempAuxColor = aux.color;
		double tempAuxColorHybrid = aux.colorHybrid;
		double tempAuxTemp1000 = aux.temp1000;

		aux.i = i;

		fractalFormulaFunction = fractals.GetFractalFormulaFunction(sequence);

		// Calculate effective weight using the advanced weight system
		// Combines standard formula_weight with the advanced weight mode
		double effectiveWeight = 1.0;
		if (fractals.IsHybrid())
		{
			fractal::enumDEFunctionType deFunc = fractals.GetDEFunctionType(sequence);

			// Transforms (withoutDEFunction): auto-passthrough if transform passthrough mode
			const sFormulaWeightParams &wp = fractals.GetWeightParams(sequence);
			if (deFunc == fractal::withoutDEFunction && wp.mode == weightModeTransformPassthrough)
			{
				effectiveWeight = 1.0;
			}
			else
			{
				// Compute actual DE estimate per formula type
				double actualDE = aux.DE;
				if (aux.r > 0.0)
				{
					if (deFunc == fractal::pseudoKleinianDEFunction)
					{
						double rxy = sqrt(z.x * z.x + z.y * z.y);
						actualDE = (aux.DE > 0.0)
							? max(rxy - aux.pseudoKleinianDE, fabs(rxy * z.z) / aux.r) / aux.DE
							: aux.r;
					}
					else if (deFunc == fractal::josKleinianDEFunction)
					{
						actualDE = min(z.y, fractal->analyticDE.tweak005)
							/ max(aux.DE, fractal->analyticDE.offset1);
					}
					else if (deFunc == fractal::logarithmicDEFunction)
					{
						actualDE = (aux.DE > 0.0 && aux.r > 1.0)
							? 0.5 * aux.r * log(aux.r) / aux.DE : aux.r;
					}
					else if (deFunc == fractal::linearDEFunction)
					{
						actualDE = (aux.DE > 0.0) ? aux.r / aux.DE : aux.r;
					}
					else if (deFunc == fractal::customDEFunction)
					{
						// DIFS formulas store distance in aux.dist
						actualDE = (aux.dist > 0.0) ? aux.dist : aux.r;
					}
					else if (deFunc == fractal::maxAxisDEFunction)
					{
						CVector4 absZ = fabs(z);
						double maxZ = dMax(absZ.x, absZ.y, absZ.z);
						actualDE = (aux.DE > 0.0) ? maxZ / aux.DE : maxZ;
					}
					else if (deFunc == fractal::withoutDEFunction)
					{
						// Transforms: use z magnitude change as proxy
						actualDE = aux.r;
					}
				}

				double standardWeight = fractals.GetWeight(sequence);
				double advancedWeight = fractals.CalculateWeight(
					sequence, i, actualDE, aux.r, aux.dist, deFunc);
				effectiveWeight = standardWeight * advancedWeight;
				if (effectiveWeight > 1.0) effectiveWeight = 1.0;
			}
		}

		const sFormulaMutationParams &mut = fractals.GetMutationParams(sequence);
		CVector4 preMutZ = z;

		if (!fractals.IsHybrid() || effectiveWeight > 0.0)
		{
			// -------------- Formula Mutation pre-processing ---------------
			bool mutationActive = mut.enabled
				&& i >= mut.iterationStart && i < mut.iterationStop;
			if (mutationActive)
			{
				// Pre-abs
				if (mut.preAbsX) z.x = fabs(z.x);
				if (mut.preAbsY) z.y = fabs(z.y);
				if (mut.preAbsZ) z.z = fabs(z.z);

				// Pre-offset
				z.x += mut.preOffsetX;
				z.y += mut.preOffsetY;
				z.z += mut.preOffsetZ;

				// Pre-rotation
				if (mut.preRotX != 0.0 || mut.preRotY != 0.0 || mut.preRotZ != 0.0)
				{
					CVector3 z3 = z.GetXYZ();
					z3 = mut.preRotMatrix.RotateVector(z3);
					z = CVector4(z3, z.w);
				}

				// Pre-scale
				if (mut.preScale != 1.0)
				{
					z *= mut.preScale;
					aux.DE *= mut.preScale;
				}

				// Fold injection (pre-formula or both)
				if (mut.foldType != mutFoldNone
					&& (mut.foldPosition == mutFoldPosPre || mut.foldPosition == mutFoldPosBoth))
				{
					switch (mut.foldType)
					{
						case mutFoldBox:
							if (fabs(z.x) > mut.foldLimit) z.x = sign(z.x) * mut.foldValue - z.x;
							if (fabs(z.y) > mut.foldLimit) z.y = sign(z.y) * mut.foldValue - z.y;
							if (fabs(z.z) > mut.foldLimit) z.z = sign(z.z) * mut.foldValue - z.z;
							break;
						case mutFoldSphere:
						{
							double rr = z.x * z.x + z.y * z.y + z.z * z.z;
							double minR2 = mut.foldLimit * mut.foldLimit;
							double fixR2 = mut.foldValue * mut.foldValue;
							if (rr < minR2) { z *= fixR2 / minR2; aux.DE *= fixR2 / minR2; }
							else if (rr < fixR2) { z *= fixR2 / rr; aux.DE *= fixR2 / rr; }
							break;
						}
						case mutFoldMenger:
						{
							z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z);
							if (z.x - z.y < 0) { double t = z.y; z.y = z.x; z.x = t; }
							if (z.x - z.z < 0) { double t = z.z; z.z = z.x; z.x = t; }
							if (z.y - z.z < 0) { double t = z.z; z.z = z.y; z.y = t; }
							double s = mut.foldValue;
							z.x = z.x * s - mut.foldLimit * (s - 1.0);
							z.y = z.y * s - mut.foldLimit * (s - 1.0);
							z.z = z.z * s;
							if (z.z > 0.5 * mut.foldLimit * (s - 1.0))
								z.z -= mut.foldLimit * (s - 1.0);
							aux.DE *= s;
							break;
						}
						case mutFoldSierpinski:
						{
							if (z.x + z.y < 0) { double tx = -z.y; z.y = -z.x; z.x = tx; }
							if (z.x + z.z < 0) { double tx = -z.z; z.z = -z.x; z.x = tx; }
							if (z.y + z.z < 0) { double ty = -z.z; z.z = -z.y; z.y = ty; }
							double s = mut.foldValue;
							z *= s;
							z.x -= mut.foldLimit * (s - 1.0);
							z.y -= mut.foldLimit * (s - 1.0);
							z.z -= mut.foldLimit * (s - 1.0);
							aux.DE *= s;
							break;
						}
						case mutFoldAbs:
						{
							z.x = fabs(z.x + mut.foldLimit) - fabs(z.x - mut.foldLimit) - z.x;
							z.y = fabs(z.y + mut.foldLimit) - fabs(z.y - mut.foldLimit) - z.y;
							z.z = fabs(z.z + mut.foldLimit) - fabs(z.z - mut.foldLimit) - z.z;
							break;
						}
						case mutFoldKaleidoscope:
						{
							int sides = mut.kaleidoscopeSides;
							if (sides >= 3)
							{
								double angle = M_PI / sides;
								double pAngle = atan2(z.y, z.x);
								double r = sqrt(z.x * z.x + z.y * z.y);
								pAngle = fmod(pAngle + angle, 2.0 * angle) - angle;
								z.x = r * cos(pAngle);
								z.y = r * sin(pAngle);
								z.y = fabs(z.y);
							}
							break;
						}
						case mutFoldOctahedral:
						{
							if (z.x + z.y < 0) { double tx = -z.y; z.y = -z.x; z.x = tx; }
							if (z.x + z.z < 0) { double tx = -z.z; z.z = -z.x; z.x = tx; }
							if (z.y + z.z < 0) { double ty = -z.z; z.z = -z.y; z.y = ty; }
							if (z.x - z.y < 0) { double tx = z.y; z.y = z.x; z.x = tx; }
							if (z.x - z.z < 0) { double tx = z.z; z.z = z.x; z.x = tx; }
							break;
						}
						case mutFoldSmooth:
						{
							double k = (mut.foldLimit > 0.0) ? mut.foldLimit : 1.0;
							z.x -= tanh(k * z.x);
							z.y -= tanh(k * z.y);
							z.z -= tanh(k * z.z);
							break;
						}
						case mutFoldPolynomial:
						{
							z.x = z.x * z.x * z.x - 3.0 * z.x;
							z.y = z.y * z.y * z.y - 3.0 * z.y;
							z.z = z.z * z.z * z.z - 3.0 * z.z;
							break;
						}
						case mutFoldCircular:
						{
							double rad = (mut.foldValue > 0.0) ? mut.foldValue : 1.0;
							double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
							if (r > 1e-21) { double s = rad / r; z.x *= s; z.y *= s; z.z *= s; }
							break;
						}
						case mutFoldSpiral:
						{
							double r = sqrt(z.x * z.x + z.y * z.y);
							double angle = r * mut.foldLimit;
							double ca = cos(angle); double sa = sin(angle);
							double nx = z.x * ca - z.y * sa;
							double ny = z.x * sa + z.y * ca;
							z.x = nx; z.y = ny;
							break;
						}
						case mutFoldSinusoidal:
						{
							double a = mut.foldValue;
							double b = (mut.foldLimit > 0.0) ? mut.foldLimit : 1.0;
							z.x += a * sin(b * z.x);
							z.y += a * sin(b * z.y);
							z.z += a * sin(b * z.z);
							break;
						}
						case mutFoldExponential:
						{
							z.x *= exp(-z.x * z.x);
							z.y *= exp(-z.y * z.y);
							z.z *= exp(-z.z * z.z);
							break;
						}
						case mutFoldLogarithmic:
						{
							double rx = fabs(z.x); double ry = fabs(z.y); double rz = fabs(z.z);
							z.x *= log(1.0 + rx);
							z.y *= log(1.0 + ry);
							z.z *= log(1.0 + rz);
							break;
						}
						case mutFoldPower:
						{
							double p = (mut.foldValue > 0.0) ? mut.foldValue : 2.0;
							double ax = fabs(z.x); double ay = fabs(z.y); double az = fabs(z.z);
							z.x = (z.x >= 0 ? 1.0 : -1.0) * pow(max(ax, 1e-21), p);
							z.y = (z.y >= 0 ? 1.0 : -1.0) * pow(max(ay, 1e-21), p);
							z.z = (z.z >= 0 ? 1.0 : -1.0) * pow(max(az, 1e-21), p);
							break;
						}
						case mutFoldSmoothAbs:
						{
							double k = (mut.foldLimit > 0.0) ? mut.foldLimit : 5.0;
							z.x = z.x * tanh(k * z.x);
							z.y = z.y * tanh(k * z.y);
							z.z = z.z * tanh(k * z.z);
							break;
						}
						case mutFoldModuloWrap:
						{
							double period = (mut.foldValue > 0.0) ? mut.foldValue : 2.0;
							z.x = fmod(z.x + period * 0.5, period) - period * 0.5;
							z.y = fmod(z.y + period * 0.5, period) - period * 0.5;
							z.z = fmod(z.z + period * 0.5, period) - period * 0.5;
							break;
						}
						case mutFoldNestedAbs:
						{
							double c = (mut.foldLimit > 0.0) ? mut.foldLimit : 1.0;
							z.x = fabs(fabs(z.x) - c);
							z.y = fabs(fabs(z.y) - c);
							z.z = fabs(fabs(z.z) - c);
							break;
						}
						case mutFoldSawtooth:
						{
							z.x = 2.0 * (z.x * 0.5 - floor(z.x * 0.5 + 0.5));
							z.y = 2.0 * (z.y * 0.5 - floor(z.y * 0.5 + 0.5));
							z.z = 2.0 * (z.z * 0.5 - floor(z.z * 0.5 + 0.5));
							break;
						}
						case mutFoldBipolar:
						{
							double c1 = mut.foldLimit;
							double c2 = -mut.foldLimit;
							z.x = fabs(z.x - c1) - fabs(z.x - c2);
							z.y = fabs(z.y - c1) - fabs(z.y - c2);
							z.z = fabs(z.z - c1) - fabs(z.z - c2);
							break;
						}
						case mutFoldRadialBox:
						{
							double r = sqrt(z.x*z.x + z.y*z.y);
							double theta = atan2(z.y, z.x);
							double foldR = mut.foldLimit;
							if (r > foldR) r = 2.0 * foldR - r;
							if (r < -foldR) r = -2.0 * foldR - r;
							z.x = r * cos(theta);
							z.y = r * sin(theta);
							aux.DE *= r / max(sqrt(z.x*z.x + z.y*z.y), 1e-21);
							break;
						}
						case mutFoldShear:
						{
							double lim = mut.foldLimit;
							if (z.x > lim) z.x = 2.0 * lim - z.x;
							else if (z.x < -lim) z.x = -2.0 * lim - z.x;
							if (z.y > lim) z.y = 2.0 * lim - z.y;
							else if (z.y < -lim) z.y = -2.0 * lim - z.y;
							z.x += mut.foldValue * z.y;
							z.y += mut.foldValue * z.z;
							break;
						}
						case mutFold3DCross:
						{
							double lim = mut.foldLimit;
							int phase = aux.i % 3;
							if (phase == 0)
							{
								if (z.x > lim) z.x = 2.0*lim - z.x;
								if (z.x < -lim) z.x = -2.0*lim - z.x;
								if (z.y > lim) z.y = 2.0*lim - z.y;
								if (z.y < -lim) z.y = -2.0*lim - z.y;
							}
							else if (phase == 1)
							{
								if (z.y > lim) z.y = 2.0*lim - z.y;
								if (z.y < -lim) z.y = -2.0*lim - z.y;
								if (z.z > lim) z.z = 2.0*lim - z.z;
								if (z.z < -lim) z.z = -2.0*lim - z.z;
							}
							else
							{
								if (z.z > lim) z.z = 2.0*lim - z.z;
								if (z.z < -lim) z.z = -2.0*lim - z.z;
								if (z.x > lim) z.x = 2.0*lim - z.x;
								if (z.x < -lim) z.x = -2.0*lim - z.x;
							}
							break;
						}
						case mutFoldConformal:
						{
							double r2 = z.x*z.x + z.y*z.y + z.z*z.z;
							if (r2 > 1e-21)
							{
								z.x += z.x / r2;
								z.y += z.y / r2;
								z.z += z.z / r2;
								aux.DE *= fabs(1.0 - 1.0 / (r2));
							}
							break;
						}
						case mutFoldRotation:
						{
							double lim = mut.foldLimit;
							if (z.x > lim) z.x = 2.0*lim - z.x;
							if (z.x < -lim) z.x = -2.0*lim - z.x;
							if (z.y > lim) z.y = 2.0*lim - z.y;
							if (z.y < -lim) z.y = -2.0*lim - z.y;
							if (z.z > lim) z.z = 2.0*lim - z.z;
							if (z.z < -lim) z.z = -2.0*lim - z.z;
							double t = z.x;
							z.x = -z.y;
							z.y = t;
							break;
						}
						case mutFoldScalePulse:
						{
							double lim = mut.foldLimit;
							if (z.x > lim) z.x = 2.0*lim - z.x;
							if (z.x < -lim) z.x = -2.0*lim - z.x;
							if (z.y > lim) z.y = 2.0*lim - z.y;
							if (z.y < -lim) z.y = -2.0*lim - z.y;
							if (z.z > lim) z.z = 2.0*lim - z.z;
							if (z.z < -lim) z.z = -2.0*lim - z.z;
							double pulse = 1.0 + 0.2 * sin((double)aux.i * mut.foldValue);
							z *= pulse;
							aux.DE *= fabs(pulse);
							break;
						}
						case mutFoldTriangleWave:
						{
							z.x = 2.0 * fabs(z.x * 0.5 - floor(z.x * 0.5 + 0.5));
							z.y = 2.0 * fabs(z.y * 0.5 - floor(z.y * 0.5 + 0.5));
							z.z = 2.0 * fabs(z.z * 0.5 - floor(z.z * 0.5 + 0.5));
							break;
						}
						default: break;
					}
				}

				// Component swizzle
				switch (mut.swizzle)
				{
					case mutSwizzleXYZ: break;
					case mutSwizzleXZY: { double t = z.y; z.y = z.z; z.z = t; } break;
					case mutSwizzleYXZ: { double t = z.x; z.x = z.y; z.y = t; } break;
					case mutSwizzleYZX: { double t = z.x; z.x = z.y; z.y = z.z; z.z = t; } break;
					case mutSwizzleZXY: { double t = z.z; z.z = z.y; z.y = z.x; z.x = t; } break;
					case mutSwizzleZYX: { double t = z.x; z.x = z.z; z.z = t; } break;
				}

				// Warp distortion
				if (mut.warpType == mutWarpSine)
				{
					z.x += mut.warpAmplitude * sin(z.y * mut.warpFrequency);
					z.y += mut.warpAmplitude * sin(z.z * mut.warpFrequency);
					z.z += mut.warpAmplitude * sin(z.x * mut.warpFrequency);
				}
				else if (mut.warpType == mutWarpTwist)
				{
					double angle = z.z * mut.warpFrequency * M_PI / 180.0;
					double ca = cos(angle * mut.warpAmplitude);
					double sa = sin(angle * mut.warpAmplitude);
					double nx = z.x * ca - z.y * sa;
					double ny = z.x * sa + z.y * ca;
					z.x = nx; z.y = ny;
				}
				else if (mut.warpType == mutWarpSpiral)
				{
					double r = sqrt(z.x * z.x + z.y * z.y);
					double angle = r * mut.warpFrequency;
					double ca = cos(angle * mut.warpAmplitude);
					double sa = sin(angle * mut.warpAmplitude);
					double nx = z.x * ca - z.y * sa;
					double ny = z.x * sa + z.y * ca;
					z.x = nx; z.y = ny;
				}
				else if (mut.warpType == mutWarpRadial)
				{
					double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
					if (r > 1e-21)
					{
						double warp = mut.warpAmplitude * sin(r * mut.warpFrequency);
						z.x += z.x / r * warp;
						z.y += z.y / r * warp;
						z.z += z.z / r * warp;
					}
				}
				else if (mut.warpType == mutWarpCylindrical)
				{
					double r = sqrt(z.x * z.x + z.y * z.y);
					if (r > 1e-21)
					{
						double angle = atan2(z.y, z.x);
						angle += mut.warpAmplitude * sin(z.z * mut.warpFrequency);
						z.x = r * cos(angle);
						z.y = r * sin(angle);
					}
				}
				else if (mut.warpType == mutWarpSphericalInversion)
				{
					double rr = z.x * z.x + z.y * z.y + z.z * z.z;
					double radius2 = mut.warpFrequency * mut.warpFrequency;
					if (rr > 1e-21)
					{
						double factor = radius2 / rr;
						factor = 1.0 + (factor - 1.0) * mut.warpAmplitude;
						z *= factor;
						aux.DE *= fabs(factor);
					}
				}
				else if (mut.warpType == mutWarpMobius)
				{
					double r2 = z.x * z.x + z.y * z.y;
					if (r2 > 1e-21)
					{
						double angle = mut.warpAmplitude * mut.warpFrequency / (r2 + 1.0);
						double ca = cos(angle);
						double sa = sin(angle);
						double nx = z.x * ca - z.y * sa;
						double ny = z.x * sa + z.y * ca;
						z.x = nx; z.y = ny;
					}
				}
				else if (mut.warpType == mutWarpIFSContraction)
				{
					double s0 = mut.warpAmplitude;
					double a = mut.warpFrequency;
					double s = s0 * (1.0 + a * sin((double)aux.i));
					z *= s;
					aux.DE = aux.DE * fabs(s) + 1.0;
				}
				else if (mut.warpType == mutWarpIFSRotation)
				{
					double goldenAngle = 2.399963229728653;
					double angle = goldenAngle * aux.i * mut.warpAmplitude;
					double ca = cos(angle); double sa = sin(angle);
					double nx = z.x * ca - z.y * sa;
					double ny = z.x * sa + z.y * ca;
					z.x = nx; z.y = ny;
				}
				else if (mut.warpType == mutWarpPolarIFS)
				{
					double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
					if (r > 1e-21)
					{
						double theta = acos(z.z / r);
						double phi = atan2(z.y, z.x);
						double sr = mut.warpAmplitude;
						r *= sr;
						theta *= mut.warpFrequency;
						z.x = r * sin(theta) * cos(phi);
						z.y = r * sin(theta) * sin(phi);
						z.z = r * cos(theta);
						aux.DE = aux.DE * fabs(sr) + 1.0;
					}
				}
				else if (mut.warpType == mutWarpShearIFS)
				{
					z.x += mut.warpAmplitude * z.y;
					z.y += mut.warpFrequency * z.z;
				}

				// Math injection — new mathematical operations
				if (mut.mathType != mutMathNone)
				{
					CVector4 mathZ = z;
					switch (mut.mathType)
					{
						case mutMathSinPower:
						{
							double p = mut.mathP1;
							mathZ.x = sign(sin(z.x)) * pow(fabs(sin(z.x)), p);
							mathZ.y = sign(sin(z.y)) * pow(fabs(sin(z.y)), p);
							mathZ.z = sign(sin(z.z)) * pow(fabs(sin(z.z)), p);
							break;
						}
						case mutMathCoshField:
						{
							double freq = mut.mathP1;
							double amp = mut.mathP2;
							mathZ.x = z.x + amp * (cosh(z.y * freq) - 1.0);
							mathZ.y = z.y + amp * (cosh(z.z * freq) - 1.0);
							mathZ.z = z.z + amp * (cosh(z.x * freq) - 1.0);
							break;
						}
						case mutMathExpMap:
						{
							double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
							if (r > 1e-21)
							{
								double er = exp(mut.mathP1 * log(r + 1.0));
								double theta = atan2(sqrt(z.x * z.x + z.y * z.y), z.z);
								double phi = atan2(z.y, z.x);
								mathZ.x = er * sin(theta + mut.mathP2) * cos(phi + mut.mathP3);
								mathZ.y = er * sin(theta + mut.mathP2) * sin(phi + mut.mathP3);
								mathZ.z = er * cos(theta + mut.mathP2);
							}
							break;
						}
						case mutMathLogSpiral:
						{
							double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
							if (r > 1e-21)
							{
								double lr = log(r + 1e-21) * mut.mathP1;
								double theta = atan2(sqrt(z.x * z.x + z.y * z.y), z.z);
								double phi = atan2(z.y, z.x);
								double spiralAngle = phi + lr * mut.mathP2;
								double newR = exp(lr);
								mathZ.x = newR * sin(theta) * cos(spiralAngle);
								mathZ.y = newR * sin(theta) * sin(spiralAngle);
								mathZ.z = newR * cos(theta);
							}
							break;
						}
						case mutMathPowerN:
						{
							double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
							if (r > 1e-21)
							{
								double n = mut.mathP1;
								double theta = acos(z.z / r);
								double phi = atan2(z.y, z.x);
								double rn = pow(r, n);
								double nTheta = n * theta + mut.mathP2;
								double nPhi = n * phi + mut.mathP3;
								mathZ.x = rn * sin(nTheta) * cos(nPhi);
								mathZ.y = rn * sin(nTheta) * sin(nPhi);
								mathZ.z = rn * cos(nTheta);
								aux.DE = pow(r, n - 1.0) * n * aux.DE + 1.0;
							}
							break;
						}
						case mutMathComplexMul:
						{
							double cr = mut.mathP1;
							double ci = mut.mathP2;
							double nx = z.x * cr - z.y * ci;
							double ny = z.x * ci + z.y * cr;
							mathZ.x = nx;
							mathZ.y = ny;
							mathZ.z = z.z * sqrt(cr * cr + ci * ci);
							break;
						}
						case mutMathQuaternionMul:
						{
							double qr = mut.mathP1, qi = mut.mathP2;
							double qj = mut.mathP3, qk = mut.mathP4;
							double zr = 0.0, zi = z.x, zj = z.y, zk = z.z;
							mathZ.x = zr*qi + zi*qr + zj*qk - zk*qj;
							mathZ.y = zr*qj - zi*qk + zj*qr + zk*qi;
							mathZ.z = zr*qk + zi*qj - zj*qi + zk*qr;
							break;
						}
						case mutMathBilinear:
						{
							double a = mut.mathP1, b = mut.mathP2;
							double c = mut.mathP3, d = mut.mathP4;
							double rxy = sqrt(z.x * z.x + z.y * z.y);
							double denom = c * rxy + d;
							if (fabs(denom) > 1e-21)
							{
								double scale = (a * rxy + b) / denom;
								mathZ.x = z.x * scale;
								mathZ.y = z.y * scale;
								mathZ.z = z.z * scale;
								aux.DE *= fabs(scale);
							}
							break;
						}
						case mutMathInvCylindr:
						{
							double rxy = sqrt(z.x * z.x + z.y * z.y);
							double radius = mut.mathP1;
							if (rxy > 1e-21)
							{
								double radius2 = radius * radius;
								double scale = radius2 / (rxy * rxy);
								mathZ.x = z.x * scale;
								mathZ.y = z.y * scale;
								mathZ.z = z.z;
								aux.DE *= scale;
							}
							break;
						}
						case mutMathSpiralPower:
						{
							double angle = mut.mathP1 * M_PI / 180.0;
							double scale = mut.mathP2 != 0.0 ? mut.mathP2 : 1.0;
							double ca = cos(angle);
							double sa = sin(angle);
							mathZ.x = (z.x * ca - z.y * sa) * scale;
							mathZ.y = (z.x * sa + z.y * ca) * scale;
							mathZ.z = z.z * scale;
							aux.DE *= fabs(scale);
							break;
						}
						case mutMathHyperbolicRot:
						{
							double angle = mut.mathP1;
							double ch = cosh(angle);
							double sh = sinh(angle);
							mathZ.x = z.x * ch + z.z * sh;
							mathZ.z = z.x * sh + z.z * ch;
							mathZ.y = z.y;
							break;
						}
						case mutMathSphereInversion3D:
						{
							// T(x) = c + r²*(x-c)/|x-c|²
							double cx = mut.mathP1, cy = mut.mathP2, cz = mut.mathP3;
							double r = mut.mathP4 != 0.0 ? mut.mathP4 : 1.0;
							double dx = z.x - cx, dy = z.y - cy, dz = z.z - cz;
							double d2 = dx*dx + dy*dy + dz*dz;
							if (d2 > 1e-21)
							{
								double factor = r * r / d2;
								mathZ.x = cx + dx * factor;
								mathZ.y = cy + dy * factor;
								mathZ.z = cz + dz * factor;
								aux.DE *= factor;
							}
							break;
						}
						case mutMathLoxodromic:
						{
							// s * R_axis(θ) * v — spiral rotation + scale
							double s = mut.mathP1 != 0.0 ? mut.mathP1 : 1.0;
							double theta = mut.mathP2 * M_PI / 180.0;
							// rotation axis from P3,P4 (spherical angles for axis)
							double axPhi = mut.mathP3 * M_PI / 180.0;
							double axPsi = mut.mathP4 * M_PI / 180.0;
							double ax = cos(axPhi) * cos(axPsi);
							double ay = cos(axPhi) * sin(axPsi);
							double az = sin(axPhi);
							// Rodrigues rotation
							double ct = cos(theta), st = sin(theta);
							double dot = z.x*ax + z.y*ay + z.z*az;
							double crx = ay*z.z - az*z.y;
							double cry = az*z.x - ax*z.z;
							double crz = ax*z.y - ay*z.x;
							mathZ.x = (z.x * ct + crx * st + ax * dot * (1.0 - ct)) * s;
							mathZ.y = (z.y * ct + cry * st + ay * dot * (1.0 - ct)) * s;
							mathZ.z = (z.z * ct + crz * st + az * dot * (1.0 - ct)) * s;
							aux.DE *= fabs(s);
							break;
						}
						case mutMathParabolic:
						{
							// horocycle: (x+a, y+b, z) / (1 + c*z)
							double a = mut.mathP1, b = mut.mathP2, c = mut.mathP3;
							double denom = 1.0 + c * z.z;
							if (fabs(denom) > 1e-21)
							{
								mathZ.x = (z.x + a) / denom;
								mathZ.y = (z.y + b) / denom;
								mathZ.z = z.z / denom;
								aux.DE /= fabs(denom);
							}
							break;
						}
						case mutMathSchottkyDual:
						{
							// dual sphere inversions: 2 spheres
							double c1x = mut.mathP1, c1y = mut.mathP2, c1z = mut.mathP3;
							double r1 = mut.mathP4 != 0.0 ? mut.mathP4 : 1.0;
							double c2x = mut.mathP5, c2y = mut.mathP6, c2z = mut.mathP7;
							double r2 = mut.mathP8 != 0.0 ? mut.mathP8 : 1.0;
							// sphere 1
							double dx1 = z.x - c1x, dy1 = z.y - c1y, dz1 = z.z - c1z;
							double d1sq = dx1*dx1 + dy1*dy1 + dz1*dz1;
							if (d1sq < r1 * r1 && d1sq > 1e-21)
							{
								double f = r1 * r1 / d1sq;
								mathZ.x = c1x + dx1 * f;
								mathZ.y = c1y + dy1 * f;
								mathZ.z = c1z + dz1 * f;
								aux.DE *= f;
								break;
							}
							// sphere 2
							double dx2 = z.x - c2x, dy2 = z.y - c2y, dz2 = z.z - c2z;
							double d2sq = dx2*dx2 + dy2*dy2 + dz2*dz2;
							if (d2sq < r2 * r2 && d2sq > 1e-21)
							{
								double f = r2 * r2 / d2sq;
								mathZ.x = c2x + dx2 * f;
								mathZ.y = c2y + dy2 * f;
								mathZ.z = c2z + dz2 * f;
								aux.DE *= f;
							}
							break;
						}
						case mutMathFibonacciWord:
						{
							// aperiodic Fibonacci word: selects between T1(scale+rot) and T2(fold)
							// Fibonacci word: 0,1,0,0,1,0,1,0,0,1,0,0,1,...
							int n = i % 64;
							int a_fib = 1, b_fib = 0, temp_fib;
							for (int fi = 0; fi < n; fi++)
							{
								temp_fib = a_fib; a_fib = a_fib + b_fib; b_fib = temp_fib;
							}
							bool useT1 = (a_fib % 2 == 0);
							if (useT1)
							{
								// T1: scale + rotation by P1 angle around Z
								double angle = mut.mathP1 * M_PI / 180.0;
								double sc = mut.mathP2 != 0.0 ? mut.mathP2 : 1.0;
								double ca = cos(angle), sa = sin(angle);
								mathZ.x = (z.x * ca - z.y * sa) * sc;
								mathZ.y = (z.x * sa + z.y * ca) * sc;
								mathZ.z = z.z * sc;
								aux.DE *= fabs(sc);
							}
							else
							{
								// T2: box fold with limit P3, value P4
								double lim = mut.mathP3 != 0.0 ? mut.mathP3 : 1.0;
								double val = mut.mathP4 != 0.0 ? mut.mathP4 : 2.0;
								if (z.x > lim) mathZ.x = val - z.x;
								else if (z.x < -lim) mathZ.x = -val - z.x;
								if (z.y > lim) mathZ.y = val - z.y;
								else if (z.y < -lim) mathZ.y = -val - z.y;
								if (z.z > lim) mathZ.z = val - z.z;
								else if (z.z < -lim) mathZ.z = -val - z.z;
							}
							break;
						}
						case mutMathMaskitBend:
						{
							// Maskit: μ + 1/z generalized to 3D
							double muRe = mut.mathP1, muIm = mut.mathP2;
							double bendAngle = mut.mathP3 * M_PI / 180.0;
							double r2 = z.x*z.x + z.y*z.y + z.z*z.z;
							if (r2 > 1e-21)
							{
								// inversion: 1/z in 3D = z̄/|z|²
								double invX = z.x / r2, invY = -z.y / r2, invZ = -z.z / r2;
								mathZ.x = muRe + invX;
								mathZ.y = muIm + invY;
								mathZ.z = invZ;
								// bending: rotate around geodesic
								if (fabs(bendAngle) > 1e-12)
								{
									double cb = cos(bendAngle), sb = sin(bendAngle);
									double ty = mathZ.y * cb - mathZ.z * sb;
									double tz = mathZ.y * sb + mathZ.z * cb;
									mathZ.y = ty; mathZ.z = tz;
								}
								aux.DE = aux.DE / r2 + 1.0;
							}
							break;
						}
						case mutMathEllipsoidInversion:
						{
							// T(x) = c + A*(x-c)/|A*(x-c)|²  with A = diag(ax,ay,az)
							double ax = mut.mathP1 != 0.0 ? mut.mathP1 : 1.0;
							double ay = mut.mathP2 != 0.0 ? mut.mathP2 : 1.0;
							double az = mut.mathP3 != 0.0 ? mut.mathP3 : 1.0;
							double r = mut.mathP4 != 0.0 ? mut.mathP4 : 1.0;
							// scale each axis
							double sx = z.x * ax, sy = z.y * ay, sz = z.z * az;
							double d2 = sx*sx + sy*sy + sz*sz;
							if (d2 > 1e-21)
							{
								double factor = r * r / d2;
								mathZ.x = sx * factor / ax;
								mathZ.y = sy * factor / ay;
								mathZ.z = sz * factor / az;
								aux.DE *= factor;
							}
							break;
						}
						case mutMathTorusInversion:
						{
							// inversion in torus: reflect through torus surface
							double R = mut.mathP1 != 0.0 ? mut.mathP1 : 2.0; // major radius
							double r = mut.mathP2 != 0.0 ? mut.mathP2 : 1.0; // minor radius
							double rxy = sqrt(z.x*z.x + z.y*z.y);
							if (rxy > 1e-21)
							{
								// distance from torus center ring
								double dRing = rxy - R;
								double dTorus = sqrt(dRing*dRing + z.z*z.z);
								if (dTorus > 1e-21)
								{
									double factor = r * r / (dTorus * dTorus);
									double scale = (R + dRing * factor) / rxy;
									mathZ.x = z.x * scale;
									mathZ.y = z.y * scale;
									mathZ.z = z.z * factor;
									aux.DE *= factor;
								}
							}
							break;
						}
						case mutMathQuatJuliaKleinian:
						{
							// q² + c in quaternion space: q = (P4, x, y, z)
							double qr = mut.mathP4, qi = z.x, qj = z.y, qk = z.z;
							double nr = qr*qr - qi*qi - qj*qj - qk*qk;
							double ni = 2.0*qr*qi;
							double nj = 2.0*qr*qj;
							double nk = 2.0*qr*qk;
							mathZ.x = ni + mut.mathP1;
							mathZ.y = nj + mut.mathP2;
							mathZ.z = nk + mut.mathP3;
							(void)nr;
							aux.DE = 2.0 * aux.r * aux.DE + 1.0;
							break;
						}
						case mutMathPoincareBall:
						{
							// H³ Poincaré ball: map Euclidean to hyperbolic
							double r2 = z.x*z.x + z.y*z.y + z.z*z.z;
							double curvature = mut.mathP1 != 0.0 ? mut.mathP1 : 1.0;
							if (r2 < 1.0 - 1e-12)
							{
								// Poincaré metric factor: 2/(1-|z|²)
								double metricFactor = 2.0 / (1.0 - r2);
								double hypR = curvature * log((1.0 + sqrt(r2)) / (1.0 - sqrt(r2)));
								double scale = tanh(hypR * mut.mathP2) / (sqrt(r2) + 1e-21);
								mathZ.x = z.x * scale;
								mathZ.y = z.y * scale;
								mathZ.z = z.z * scale;
								aux.DE *= metricFactor * fabs(scale);
							}
							else
							{
								// clamp to ball boundary
								double rr = sqrt(r2);
								double scale = 0.999 / rr;
								mathZ.x = z.x * scale;
								mathZ.y = z.y * scale;
								mathZ.z = z.z * scale;
							}
							break;
						}
						case mutMathLorentzBoost:
						{
							// SO(3,1) Lorentz transform: boost in direction (P1,P2,P3), velocity P4
							double vx = mut.mathP1, vy = mut.mathP2, vz = mut.mathP3;
							double v = mut.mathP4;
							double vLen = sqrt(vx*vx + vy*vy + vz*vz);
							if (vLen > 1e-21 && fabs(v) < 1.0 - 1e-12)
							{
								vx /= vLen; vy /= vLen; vz /= vLen;
								double gamma = 1.0 / sqrt(1.0 - v*v);
								// w = sqrt(1 + |z|²) for hyperboloid model
								double w = sqrt(1.0 + z.x*z.x + z.y*z.y + z.z*z.z);
								// boost: parallel component scales by gamma
								double zDotV = z.x*vx + z.y*vy + z.z*vz;
								double parNew = gamma * (zDotV - v * w);
								double wNew = gamma * (w - v * zDotV);
								// reconstruct z from boosted components
								mathZ.x = z.x + (parNew - zDotV) * vx;
								mathZ.y = z.y + (parNew - zDotV) * vy;
								mathZ.z = z.z + (parNew - zDotV) * vz;
								// project back: normalize so w = sqrt(1+|z|²)
								if (wNew > 1e-21)
								{
									double projScale = sqrt(wNew*wNew - 1.0) / 
										(sqrt(mathZ.x*mathZ.x + mathZ.y*mathZ.y + mathZ.z*mathZ.z) + 1e-21);
									if (projScale > 0.0 && projScale < 100.0)
									{
										mathZ.x *= projScale;
										mathZ.y *= projScale;
										mathZ.z *= projScale;
									}
								}
								aux.DE *= gamma;
							}
							break;
						}
						case mutMathConformeFlow:
						{
							double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
							double harmonic = (r > 1e-21) ? mut.mathP1 / r : 0.0;
							double radial = mut.mathP2 * r;
							double sinusoidal = mut.mathP3 * sin(r * mut.mathP4);
							double u = harmonic + radial + sinusoidal;
							double confFactor = exp(2.0 * u);
							if (confFactor > 100.0) confFactor = 100.0;
							if (confFactor < 0.01) confFactor = 0.01;
							mathZ.x = z.x * confFactor;
							mathZ.y = z.y * confFactor;
							mathZ.z = z.z * confFactor;
							aux.DE *= confFactor;
							break;
						}
						case mutMathFractionalPower:
						{
							// r^p with fractional p — P1=power (default 2.718=e)
							double p = (mut.mathP1 != 0.0) ? mut.mathP1 : 2.718281828;
							double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
							if (r > 1e-21)
							{
								double theta = acos(z.z / r);
								double phi = atan2(z.y, z.x);
								double rp = pow(r, p);
								mathZ.x = rp * sin(theta * p) * cos(phi * p);
								mathZ.y = rp * sin(theta * p) * sin(phi * p);
								mathZ.z = rp * cos(theta * p);
								aux.DE = aux.DE * p * pow(r, p - 1.0) + 1.0;
							}
							break;
						}
						case mutMathAnisotropePower:
						{
							// P1=power_x, P2=power_y, P3=power_z
							double px = (mut.mathP1 != 0.0) ? mut.mathP1 : 2.0;
							double py = (mut.mathP2 != 0.0) ? mut.mathP2 : 2.0;
							double pz = (mut.mathP3 != 0.0) ? mut.mathP3 : 2.0;
							double ax = fabs(z.x); double ay = fabs(z.y); double az = fabs(z.z);
							mathZ.x = (z.x >= 0 ? 1.0 : -1.0) * pow(max(ax, 1e-21), px);
							mathZ.y = (z.y >= 0 ? 1.0 : -1.0) * pow(max(ay, 1e-21), py);
							mathZ.z = (z.z >= 0 ? 1.0 : -1.0) * pow(max(az, 1e-21), pz);
							double maxP = max(px, max(py, pz));
							double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
							aux.DE = aux.DE * maxP * pow(max(r, 1e-21), maxP - 1.0) + 1.0;
							break;
						}
						case mutMathHyperbolicTrigPower:
						{
							// sinh/cosh triplex power instead of sin/cos — P1=power
							double p = (mut.mathP1 != 0.0) ? mut.mathP1 : 2.0;
							double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
							if (r > 1e-21)
							{
								double theta = acos(z.z / r);
								double phi = atan2(z.y, z.x);
								double rp = pow(r, p);
								mathZ.x = rp * sinh(theta * p) * cos(phi * p);
								mathZ.y = rp * sinh(theta * p) * sin(phi * p);
								mathZ.z = rp * cosh(theta * p);
								aux.DE = aux.DE * p * pow(r, p - 1.0) * cosh(theta) + 1.0;
							}
							break;
						}
						case mutMathLogarithmicRadius:
						{
							// log(1 + r^p) — P1=power
							double p = (mut.mathP1 != 0.0) ? mut.mathP1 : 2.0;
							double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
							if (r > 1e-21)
							{
								double rp = pow(r, p);
								double lr = log(1.0 + rp);
								double scale = lr / r;
								mathZ.x = z.x * scale;
								mathZ.y = z.y * scale;
								mathZ.z = z.z * scale;
								aux.DE *= p * pow(r, p - 1.0) / (1.0 + rp);
							}
							break;
						}
						case mutMathPolarSwap:
						{
							// swap θ↔φ in spherical coordinates
							double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
							if (r > 1e-21)
							{
								double theta = acos(z.z / r);
								double phi = atan2(z.y, z.x);
								double tmp = theta; theta = phi; phi = tmp;
								mathZ.x = r * sin(theta) * cos(phi);
								mathZ.y = r * sin(theta) * sin(phi);
								mathZ.z = r * cos(theta);
							}
							break;
						}
						case mutMathRadialModulation:
						{
							double amp = (mut.mathP1 != 0.0) ? mut.mathP1 : 0.1;
							double freq = (mut.mathP2 != 0.0) ? mut.mathP2 : 10.0;
							double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
							if (r > 1e-21)
							{
								double theta = acos(z.z / r);
								double mod = 1.0 + amp * sin(freq * theta);
								mathZ.x = z.x * mod;
								mathZ.y = z.y * mod;
								mathZ.z = z.z * mod;
								aux.DE *= fabs(mod);
							}
							break;
						}
						case mutMathDualQuaternion:
						{
							// q1 * z * q2 — P1,P2,P3,P4 = q1(w,i,j,k), P5,P6,P7,P8 = q2
							double q1w = (mut.mathP1 != 0.0) ? mut.mathP1 : 1.0;
							double q1i = mut.mathP2; double q1j = mut.mathP3; double q1k = mut.mathP4;
							double q2w = (mut.mathP5 != 0.0) ? mut.mathP5 : 1.0;
							double q2i = mut.mathP6; double q2j = mut.mathP7; double q2k = mut.mathP8;
							// q1 * (0,z) — quaternion multiply: q1 * pure(z)
							double tw = -q1i*z.x - q1j*z.y - q1k*z.z;
							double tx = q1w*z.x + q1j*z.z - q1k*z.y;
							double ty = q1w*z.y + q1k*z.x - q1i*z.z;
							double tz = q1w*z.z + q1i*z.y - q1j*z.x;
							// (q1*z) * q2
							mathZ.x = tw*q2i + tx*q2w + ty*q2k - tz*q2j;
							mathZ.y = tw*q2j + ty*q2w + tz*q2i - tx*q2k;
							mathZ.z = tw*q2k + tz*q2w + tx*q2j - ty*q2i;
							break;
						}
						case mutMathOctonionPower:
						{
							// Simplified octonion: use z as first 3 components, P1-P4 as next 4
							double p = (mut.mathP1 != 0.0) ? mut.mathP1 : 2.0;
							double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z
								+ mut.mathP2*mut.mathP2 + mut.mathP3*mut.mathP3);
							if (r > 1e-21)
							{
								double theta = acos(z.z / r);
								double phi = atan2(z.y, z.x);
								double rp = pow(r, p);
								mathZ.x = rp * sin(theta * p) * cos(phi * p);
								mathZ.y = rp * sin(theta * p) * sin(phi * p);
								mathZ.z = rp * cos(theta * p);
								aux.DE = aux.DE * p * pow(r, p - 1.0) + 1.0;
							}
							break;
						}
						case mutMathQuaternionMobius:
						{
							// (az+b)/(cz+d) — P1=a, P2=b, P3=c, P4=d (real coefficients)
							double a = (mut.mathP1 != 0.0) ? mut.mathP1 : 1.0;
							double b = mut.mathP2;
							double c = mut.mathP3;
							double d = (mut.mathP4 != 0.0) ? mut.mathP4 : 1.0;
							// Numerator: a*z + b
							double nx = a * z.x + b;
							double ny = a * z.y;
							double nz = a * z.z;
							// Denominator: c*z + d — treat as scalar |cz+d|²
							double dr = c * z.x + d;
							double di = c * z.y;
							double dk = c * z.z;
							double denom = dr*dr + di*di + dk*dk;
							if (denom > 1e-21)
							{
								mathZ.x = (nx*dr + ny*di + nz*dk) / denom;
								mathZ.y = (ny*dr - nx*di) / denom;
								mathZ.z = (nz*dr - nx*dk) / denom;
								double adbc = fabs(a*d - b*c);
								aux.DE *= adbc / denom;
							}
							break;
						}
						case mutMathSplitQuaternion:
						{
							double p = (mut.mathP1 != 0.0) ? mut.mathP1 : 2.0;
							double r = sqrt(fabs(z.x*z.x + z.y*z.y - z.z*z.z));
							if (r > 1e-21)
							{
								double theta = atanh(z.z / max(sqrt(z.x*z.x + z.y*z.y), 1e-21));
								double phi = atan2(z.y, z.x);
								double rp = pow(max(r, 1e-21), p);
								mathZ.x = rp * cosh(theta * p) * cos(phi * p);
								mathZ.y = rp * cosh(theta * p) * sin(phi * p);
								mathZ.z = rp * sinh(theta * p);
								aux.DE = aux.DE * p * pow(max(r, 1e-21), p - 1.0) + 1.0;
							}
							break;
						}
						case mutMathFordCircles:
						{
							// z += sum(1/(n²·z)) for n=1..N — P1=N (default 3)
							int N = (mut.mathP1 > 0.5) ? (int)mut.mathP1 : 3;
							double r2 = z.x*z.x + z.y*z.y + z.z*z.z;
							if (r2 > 1e-21)
							{
								for (int n = 1; n <= N; n++)
								{
									double nn = (double)(n * n);
									double factor = 1.0 / (nn * r2);
									mathZ.x = z.x + z.x * factor;
									mathZ.y = z.y + z.y * factor;
									mathZ.z = z.z + z.z * factor;
									aux.DE *= (1.0 + factor);
								}
							}
							break;
						}
						case mutMathApollonianNet:
						{
							// Inversie in 4 bollen, kies dichtstbijzijnde
							// P1-P4 = radii, centers op tetraeder vertices
							double rad = (mut.mathP1 > 0.0) ? mut.mathP1 : 1.0;
							CVector4 centers[4];
							centers[0] = CVector4(1, 1, 1, 0);
							centers[1] = CVector4(1, -1, -1, 0);
							centers[2] = CVector4(-1, 1, -1, 0);
							centers[3] = CVector4(-1, -1, 1, 0);
							double minDist = 1e20;
							int closest = 0;
							for (int s = 0; s < 4; s++)
							{
								CVector4 diff = z - centers[s];
								double d = diff.Dot(diff);
								if (d < minDist) { minDist = d; closest = s; }
							}
							if (minDist > 1e-21)
							{
								double r2 = rad * rad;
								CVector4 diff = z - centers[closest];
								double factor = r2 / minDist;
								mathZ = centers[closest] + diff * factor;
								aux.DE *= factor;
							}
							break;
						}
						case mutMathConformalWedge:
						{
							// z^α — P1=α (sector angle mapping)
							double alpha = (mut.mathP1 != 0.0) ? mut.mathP1 : 2.0;
							double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
							if (r > 1e-21)
							{
								double theta = acos(z.z / r);
								double phi = atan2(z.y, z.x);
								double rp = pow(r, alpha);
								mathZ.x = rp * sin(theta * alpha) * cos(phi * alpha);
								mathZ.y = rp * sin(theta * alpha) * sin(phi * alpha);
								mathZ.z = rp * cos(theta * alpha);
								aux.DE = aux.DE * alpha * pow(r, alpha - 1.0) + 1.0;
							}
							break;
						}
						case mutMathCircleInvChain:
						{
							// Sequential circle inversions: 3 circles
							// P1=r1, P2=r2, P3=r3, P4=spacing
							double r1 = (mut.mathP1 > 0.0) ? mut.mathP1 : 1.0;
							double r2c = (mut.mathP2 > 0.0) ? mut.mathP2 : 0.8;
							double r3 = (mut.mathP3 > 0.0) ? mut.mathP3 : 0.6;
							double spacing = (mut.mathP4 != 0.0) ? mut.mathP4 : 2.0;
							double radii[3] = {r1, r2c, r3};
							double offsets[3] = {-spacing, 0.0, spacing};
							for (int c = 0; c < 3; c++)
							{
								double dx = z.x - offsets[c];
								double dist2 = dx*dx + z.y*z.y + z.z*z.z;
								if (dist2 > 1e-21 && dist2 < radii[c] * radii[c])
								{
									double factor = (radii[c] * radii[c]) / dist2;
									mathZ.x = offsets[c] + dx * factor;
									mathZ.y = z.y * factor;
									mathZ.z = z.z * factor;
									aux.DE *= factor;
								}
							}
							break;
						}
						default: break;
					}
					if (mut.mathMix < 1.0)
					{
						double m = mut.mathMix;
						z = mathZ * m + z * (1.0 - m);
					}
					else
					{
						z = mathZ;
					}
				}
			}

			// -------------- call for fractal formulas by function pointers ---------------
			if (fractalFormulaFunction && formula != none)
			{
				fractalFormulaFunction->FormulaCode(z, fractal, aux);
			}
			else
			{
				double high = fractals.GetBailout(sequence) * 10.0;
				z = CVector4(high, high, high, high);
				out->distance = 10.0;
				out->iters = 1;
				out->z = z.GetXYZ();
				return;
			}
			// -----------------------------------------------------------------------------

			// addition of constant (inside weight guard — skipped when weight=0)
			if (fractals.IsAddCConstant(sequence))
			{
				switch (formula)
				{
					case aboxMod1:
					case amazingSurf:
						// case amazingSurfMod1:
						{
							if (fractals.IsJuliaEnabled(sequence))
							{
								CVector3 juliaC =
									fractals.GetJuliaConstant(sequence) * fractals.GetConstantMultiplier(sequence);
								z += CVector4(juliaC.y, juliaC.x, juliaC.z, 0.0);
							}
							else
							{
								z += CVector4(aux.const_c.y, aux.const_c.x, aux.const_c.z, 0.0)
										 * fractals.GetConstantMultiplier(sequence);
							}
							break;
						}

					default:
					{
						if (fractals.IsJuliaEnabled(sequence))
						{
							z += CVector4(
								fractals.GetJuliaConstant(sequence) * fractals.GetConstantMultiplier(sequence), 0.0);
						}
						else
						{
							z += aux.const_c * fractals.GetConstantMultiplier(sequence);
						}
						break;
					}
				}
			}
		}

		// -------------- Formula Mutation post-processing ---------------
		{
			bool mutationActive = mut.enabled
				&& i >= mut.iterationStart && i < mut.iterationStop;
			if (mutationActive)
			{
				// Fold injection (post-formula or both)
				if (mut.foldType != mutFoldNone
					&& (mut.foldPosition == mutFoldPosPost || mut.foldPosition == mutFoldPosBoth))
				{
					switch (mut.foldType)
					{
						case mutFoldBox:
							if (fabs(z.x) > mut.foldLimit) z.x = sign(z.x) * mut.foldValue - z.x;
							if (fabs(z.y) > mut.foldLimit) z.y = sign(z.y) * mut.foldValue - z.y;
							if (fabs(z.z) > mut.foldLimit) z.z = sign(z.z) * mut.foldValue - z.z;
							break;
						case mutFoldSphere:
						{
							double rr = z.x * z.x + z.y * z.y + z.z * z.z;
							double minR2 = mut.foldLimit * mut.foldLimit;
							double fixR2 = mut.foldValue * mut.foldValue;
							if (rr < minR2) { z *= fixR2 / minR2; aux.DE *= fixR2 / minR2; }
							else if (rr < fixR2) { z *= fixR2 / rr; aux.DE *= fixR2 / rr; }
							break;
						}
						case mutFoldMenger:
						{
							z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z);
							if (z.x - z.y < 0) { double t = z.y; z.y = z.x; z.x = t; }
							if (z.x - z.z < 0) { double t = z.z; z.z = z.x; z.x = t; }
							if (z.y - z.z < 0) { double t = z.z; z.z = z.y; z.y = t; }
							double s = mut.foldValue;
							z.x = z.x * s - mut.foldLimit * (s - 1.0);
							z.y = z.y * s - mut.foldLimit * (s - 1.0);
							z.z = z.z * s;
							if (z.z > 0.5 * mut.foldLimit * (s - 1.0))
								z.z -= mut.foldLimit * (s - 1.0);
							aux.DE *= s;
							break;
						}
						case mutFoldSierpinski:
						{
							if (z.x + z.y < 0) { double tx = -z.y; z.y = -z.x; z.x = tx; }
							if (z.x + z.z < 0) { double tx = -z.z; z.z = -z.x; z.x = tx; }
							if (z.y + z.z < 0) { double ty = -z.z; z.z = -z.y; z.y = ty; }
							double s = mut.foldValue;
							z *= s;
							z.x -= mut.foldLimit * (s - 1.0);
							z.y -= mut.foldLimit * (s - 1.0);
							z.z -= mut.foldLimit * (s - 1.0);
							aux.DE *= s;
							break;
						}
						case mutFoldAbs:
						{
							z.x = fabs(z.x + mut.foldLimit) - fabs(z.x - mut.foldLimit) - z.x;
							z.y = fabs(z.y + mut.foldLimit) - fabs(z.y - mut.foldLimit) - z.y;
							z.z = fabs(z.z + mut.foldLimit) - fabs(z.z - mut.foldLimit) - z.z;
							break;
						}
						case mutFoldKaleidoscope:
						{
							int sides = mut.kaleidoscopeSides;
							if (sides >= 3)
							{
								double angle = M_PI / sides;
								double pAngle = atan2(z.y, z.x);
								double r = sqrt(z.x * z.x + z.y * z.y);
								pAngle = fmod(pAngle + angle, 2.0 * angle) - angle;
								z.x = r * cos(pAngle);
								z.y = r * sin(pAngle);
								z.y = fabs(z.y);
							}
							break;
						}
						case mutFoldOctahedral:
						{
							if (z.x + z.y < 0) { double tx = -z.y; z.y = -z.x; z.x = tx; }
							if (z.x + z.z < 0) { double tx = -z.z; z.z = -z.x; z.x = tx; }
							if (z.y + z.z < 0) { double ty = -z.z; z.z = -z.y; z.y = ty; }
							if (z.x - z.y < 0) { double tx = z.y; z.y = z.x; z.x = tx; }
							if (z.x - z.z < 0) { double tx = z.z; z.z = z.x; z.x = tx; }
							break;
						}
						case mutFoldSmooth:
						{
							double k = (mut.foldLimit > 0.0) ? mut.foldLimit : 1.0;
							z.x -= tanh(k * z.x);
							z.y -= tanh(k * z.y);
							z.z -= tanh(k * z.z);
							break;
						}
						case mutFoldPolynomial:
						{
							z.x = z.x * z.x * z.x - 3.0 * z.x;
							z.y = z.y * z.y * z.y - 3.0 * z.y;
							z.z = z.z * z.z * z.z - 3.0 * z.z;
							break;
						}
						case mutFoldCircular:
						{
							double rad = (mut.foldValue > 0.0) ? mut.foldValue : 1.0;
							double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
							if (r > 1e-21) { double s = rad / r; z.x *= s; z.y *= s; z.z *= s; }
							break;
						}
						case mutFoldSpiral:
						{
							double r = sqrt(z.x * z.x + z.y * z.y);
							double angle = r * mut.foldLimit;
							double ca = cos(angle); double sa = sin(angle);
							double nx = z.x * ca - z.y * sa;
							double ny = z.x * sa + z.y * ca;
							z.x = nx; z.y = ny;
							break;
						}
						case mutFoldSinusoidal:
						{
							double a = mut.foldValue;
							double b = (mut.foldLimit > 0.0) ? mut.foldLimit : 1.0;
							z.x += a * sin(b * z.x);
							z.y += a * sin(b * z.y);
							z.z += a * sin(b * z.z);
							break;
						}
						case mutFoldExponential:
						{
							z.x *= exp(-z.x * z.x);
							z.y *= exp(-z.y * z.y);
							z.z *= exp(-z.z * z.z);
							break;
						}
						case mutFoldLogarithmic:
						{
							double rx = fabs(z.x); double ry = fabs(z.y); double rz = fabs(z.z);
							z.x *= log(1.0 + rx);
							z.y *= log(1.0 + ry);
							z.z *= log(1.0 + rz);
							break;
						}
						case mutFoldPower:
						{
							double p = (mut.foldValue > 0.0) ? mut.foldValue : 2.0;
							double ax = fabs(z.x); double ay = fabs(z.y); double az = fabs(z.z);
							z.x = (z.x >= 0 ? 1.0 : -1.0) * pow(max(ax, 1e-21), p);
							z.y = (z.y >= 0 ? 1.0 : -1.0) * pow(max(ay, 1e-21), p);
							z.z = (z.z >= 0 ? 1.0 : -1.0) * pow(max(az, 1e-21), p);
							break;
						}
						case mutFoldSmoothAbs:
						{
							double k = (mut.foldLimit > 0.0) ? mut.foldLimit : 5.0;
							z.x = z.x * tanh(k * z.x);
							z.y = z.y * tanh(k * z.y);
							z.z = z.z * tanh(k * z.z);
							break;
						}
						case mutFoldModuloWrap:
						{
							double period = (mut.foldValue > 0.0) ? mut.foldValue : 2.0;
							z.x = fmod(z.x + period * 0.5, period) - period * 0.5;
							z.y = fmod(z.y + period * 0.5, period) - period * 0.5;
							z.z = fmod(z.z + period * 0.5, period) - period * 0.5;
							break;
						}
						case mutFoldNestedAbs:
						{
							double c = (mut.foldLimit > 0.0) ? mut.foldLimit : 1.0;
							z.x = fabs(fabs(z.x) - c);
							z.y = fabs(fabs(z.y) - c);
							z.z = fabs(fabs(z.z) - c);
							break;
						}
						case mutFoldSawtooth:
						{
							z.x = 2.0 * (z.x * 0.5 - floor(z.x * 0.5 + 0.5));
							z.y = 2.0 * (z.y * 0.5 - floor(z.y * 0.5 + 0.5));
							z.z = 2.0 * (z.z * 0.5 - floor(z.z * 0.5 + 0.5));
							break;
						}
						case mutFoldBipolar:
						{
							double c1 = mut.foldLimit;
							double c2 = -mut.foldLimit;
							z.x = fabs(z.x - c1) - fabs(z.x - c2);
							z.y = fabs(z.y - c1) - fabs(z.y - c2);
							z.z = fabs(z.z - c1) - fabs(z.z - c2);
							break;
						}
						case mutFoldRadialBox:
						{
							double r = sqrt(z.x*z.x + z.y*z.y);
							double theta = atan2(z.y, z.x);
							double foldR = mut.foldLimit;
							if (r > foldR) r = 2.0 * foldR - r;
							if (r < -foldR) r = -2.0 * foldR - r;
							z.x = r * cos(theta);
							z.y = r * sin(theta);
							aux.DE *= r / max(sqrt(z.x*z.x + z.y*z.y), 1e-21);
							break;
						}
						case mutFoldShear:
						{
							double lim = mut.foldLimit;
							if (z.x > lim) z.x = 2.0 * lim - z.x;
							else if (z.x < -lim) z.x = -2.0 * lim - z.x;
							if (z.y > lim) z.y = 2.0 * lim - z.y;
							else if (z.y < -lim) z.y = -2.0 * lim - z.y;
							z.x += mut.foldValue * z.y;
							z.y += mut.foldValue * z.z;
							break;
						}
						case mutFold3DCross:
						{
							double lim = mut.foldLimit;
							int phase = aux.i % 3;
							if (phase == 0)
							{
								if (z.x > lim) z.x = 2.0*lim - z.x;
								if (z.x < -lim) z.x = -2.0*lim - z.x;
								if (z.y > lim) z.y = 2.0*lim - z.y;
								if (z.y < -lim) z.y = -2.0*lim - z.y;
							}
							else if (phase == 1)
							{
								if (z.y > lim) z.y = 2.0*lim - z.y;
								if (z.y < -lim) z.y = -2.0*lim - z.y;
								if (z.z > lim) z.z = 2.0*lim - z.z;
								if (z.z < -lim) z.z = -2.0*lim - z.z;
							}
							else
							{
								if (z.z > lim) z.z = 2.0*lim - z.z;
								if (z.z < -lim) z.z = -2.0*lim - z.z;
								if (z.x > lim) z.x = 2.0*lim - z.x;
								if (z.x < -lim) z.x = -2.0*lim - z.x;
							}
							break;
						}
						case mutFoldConformal:
						{
							double r2 = z.x*z.x + z.y*z.y + z.z*z.z;
							if (r2 > 1e-21)
							{
								z.x += z.x / r2;
								z.y += z.y / r2;
								z.z += z.z / r2;
								aux.DE *= fabs(1.0 - 1.0 / (r2));
							}
							break;
						}
						case mutFoldRotation:
						{
							double lim = mut.foldLimit;
							if (z.x > lim) z.x = 2.0*lim - z.x;
							if (z.x < -lim) z.x = -2.0*lim - z.x;
							if (z.y > lim) z.y = 2.0*lim - z.y;
							if (z.y < -lim) z.y = -2.0*lim - z.y;
							if (z.z > lim) z.z = 2.0*lim - z.z;
							if (z.z < -lim) z.z = -2.0*lim - z.z;
							double t = z.x;
							z.x = -z.y;
							z.y = t;
							break;
						}
						case mutFoldScalePulse:
						{
							double lim = mut.foldLimit;
							if (z.x > lim) z.x = 2.0*lim - z.x;
							if (z.x < -lim) z.x = -2.0*lim - z.x;
							if (z.y > lim) z.y = 2.0*lim - z.y;
							if (z.y < -lim) z.y = -2.0*lim - z.y;
							if (z.z > lim) z.z = 2.0*lim - z.z;
							if (z.z < -lim) z.z = -2.0*lim - z.z;
							double pulse = 1.0 + 0.2 * sin((double)aux.i * mut.foldValue);
							z *= pulse;
							aux.DE *= fabs(pulse);
							break;
						}
						case mutFoldTriangleWave:
						{
							z.x = 2.0 * fabs(z.x * 0.5 - floor(z.x * 0.5 + 0.5));
							z.y = 2.0 * fabs(z.y * 0.5 - floor(z.y * 0.5 + 0.5));
							z.z = 2.0 * fabs(z.z * 0.5 - floor(z.z * 0.5 + 0.5));
							break;
						}
						default: break;
					}
				}

				// Post-rotation
				if (mut.postRotX != 0.0 || mut.postRotY != 0.0 || mut.postRotZ != 0.0)
				{
					CVector3 z3 = z.GetXYZ();
					z3 = mut.postRotMatrix.RotateVector(z3);
					z = CVector4(z3, z.w);
				}

				// Post-scale
				if (mut.postScale != 1.0)
				{
					z *= mut.postScale;
					aux.DE *= mut.postScale;
				}

				// Post-offset
				z.x += mut.postOffsetX;
				z.y += mut.postOffsetY;
				z.z += mut.postOffsetZ;

				// Z-mix: blend between pre-mutation z and post-mutation z
				if (mut.zMix < 1.0)
				{
					double m = mut.zMix;
					double m1 = 1.0 - m;
					z = z * m + preMutZ * m1;
				}

				// DE scale
				if (mut.deScale != 1.0)
				{
					aux.DE *= mut.deScale;
				}

				// DE tweak (Familie 10)
				if (mut.deTweak != mutDENone)
				{
					switch (mut.deTweak)
					{
						case mutDELogarithmic:
							aux.DE = log(1.0 + fabs(aux.DE));
							break;
						case mutDEExponential:
							aux.DE = exp(aux.DE) - 1.0;
							break;
						case mutDENoise:
						{
							double amp = mut.deTweakP1;
							double noise = amp * sin(z.x * 13.7 + z.y * 7.3 + z.z * 11.1);
							aux.DE += noise;
							break;
						}
						case mutDEModulation:
						{
							double amp = mut.deTweakP1;
							double freq = mut.deTweakP2;
							aux.DE *= (1.0 + amp * sin(freq * aux.dist));
							break;
						}
						case mutDESlack:
							aux.DE *= 0.9;
							break;
						case mutDEAggressive:
							aux.DE *= 1.1;
							break;
						default: break;
					}
				}

				// Orbit trap (Familie 10)
				if (mut.orbitTrap != mutTrapNone)
				{
					double trapVal = 1e20;
					switch (mut.orbitTrap)
					{
						case mutTrapSphere:
						{
							double dx = z.x - mut.trapCenterX;
							double dy = z.y - mut.trapCenterY;
							double dz = z.z - mut.trapCenterZ;
							double dist = sqrt(dx*dx + dy*dy + dz*dz);
							trapVal = fabs(dist - mut.trapRadius);
							break;
						}
						case mutTrapCross:
							trapVal = min(min(fabs(z.x), fabs(z.y)), fabs(z.z));
							break;
						case mutTrapLine:
							trapVal = sqrt(z.y * z.y + z.z * z.z);
							break;
						case mutTrapTorus:
						{
							double R = mut.trapRadius;
							double r_minor = mut.deTweakP1;
							double dxy = sqrt(z.x*z.x + z.y*z.y) - R;
							trapVal = sqrt(dxy*dxy + z.z*z.z) - r_minor;
							trapVal = fabs(trapVal);
							break;
						}
						case mutTrapAngle:
							trapVal = fabs(atan2(z.y, z.x));
							break;
						default: break;
					}
					if (trapVal < aux.color)
						aux.color = trapVal;
				}

				// Curvature coloring
				if (mut.curvatureColoring)
				{
					double prevDE = (aux.DE != 0.0) ? aux.DE : 1.0;
					double curvature = aux.DE / prevDE;
					aux.color = min(aux.color, curvature);
				}
			}
		}

		// Apply weight blending in hybrid mode
		if (fractals.IsHybrid() && effectiveWeight < 1.0)
		{
			const sFormulaWeightParams &wp = fractals.GetWeightParams(sequence);
			bool isPKFormula = (fractals.GetDEFunctionType(sequence) == fractal::pseudoKleinianDEFunction);
			double blendCurve = wp.componentBlendCurve;

			if (wp.separateComponents)
			{
				// Separate component weights: z, DE, dist, and color can have different blend factors
				double kz = effectiveWeight * wp.zVectorWeight;
				double kde = effectiveWeight * wp.deComponentWeight;
				double kdist = effectiveWeight * wp.distComponentWeight;
				double kcol = effectiveWeight * wp.colorComponentWeight;

				// Apply blend curve exponent
				if (blendCurve != 1.0)
				{
					if (kz > 0.0 && kz < 1.0) kz = pow(kz, blendCurve);
					if (kde > 0.0 && kde < 1.0) kde = pow(kde, blendCurve);
					if (kdist > 0.0 && kdist < 1.0) kdist = pow(kdist, blendCurve);
					if (kcol > 0.0 && kcol < 1.0) kcol = pow(kcol, blendCurve);
				}

				if (kz < 1.0) z = SmoothCVector(tempZ, z, kz);

				if (kde < 1.0)
				{
					double kden = 1.0 - kde;
					aux.DE = aux.DE * kde + tempAuxDE * kden;
					aux.DE0 = aux.DE0 * kde + tempAuxDE0 * kden;
					if (isPKFormula)
						aux.pseudoKleinianDE = aux.pseudoKleinianDE * kde + tempAuxPseudoKleinianDE * kden;
					aux.actualScale = aux.actualScale * kde + tempAuxActualScale * kden;
					aux.actualScaleA = aux.actualScaleA * kde + tempAuxActualScaleA * kden;
				}

				// DIFS dist has its own component weight
				if (kdist < 1.0)
				{
					double kdistn = 1.0 - kdist;
					aux.dist = aux.dist * kdist + tempAuxDist * kdistn;
				}

				if (kcol < 1.0)
				{
					double kcoln = 1.0 - kcol;
					aux.color = aux.color * kcol + tempAuxColor * kcoln;
					aux.colorHybrid = aux.colorHybrid * kcol + tempAuxColorHybrid * kcoln;
					aux.temp1000 = aux.temp1000 * kcol + tempAuxTemp1000 * kcoln;
				}
			}
			else
			{
				// Unified weight for all components
				double k = effectiveWeight;
				if (blendCurve != 1.0 && k > 0.0 && k < 1.0) k = pow(k, blendCurve);
				z = SmoothCVector(tempZ, z, k);
				double kn = 1.0 - k;
				aux.DE = aux.DE * k + tempAuxDE * kn;
				aux.DE0 = aux.DE0 * k + tempAuxDE0 * kn;
				aux.dist = aux.dist * k + tempAuxDist * kn;
				if (isPKFormula)
					aux.pseudoKleinianDE = aux.pseudoKleinianDE * k + tempAuxPseudoKleinianDE * kn;
				aux.actualScale = aux.actualScale * k + tempAuxActualScale * kn;
				aux.actualScaleA = aux.actualScaleA * k + tempAuxActualScaleA * kn;
				aux.color = aux.color * k + tempAuxColor * kn;
				aux.colorHybrid = aux.colorHybrid * k + tempAuxColorHybrid * kn;
				aux.temp1000 = aux.temp1000 * k + tempAuxTemp1000 * kn;
			}
		}

		// r calculation
		// r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z + w * w);

		aux.r = z.Length();

		if (z.IsNotANumber())
		{
			z = lastZ;
			aux.r = z.Length();
			out->maxiter = true;
			break;
		}

		// escape conditions
		if (fractals.IsCheckForBailout(sequence))
		{
			if (Mode == calcModeNormal || Mode == calcModeDeltaDE1)
			{
				if (aux.r > fractals.GetBailout(sequence))
				{
					out->maxiter = false;
					break;
				}

				if (fractals.UseAdditionalBailoutCond(sequence))
				{
					out->maxiter = false; // maxiter flag has to be always disabled for pseudo klienian
					if ((z - lastZ).Length() / aux.r < 0.1 / fractals.GetBailout(sequence))
					{
						break;
					}
					if ((z - lastLastZ).Length() / aux.r < 0.1 / fractals.GetBailout(sequence))
					{
						break;
					}
				}
			}
			else if (Mode == calcModeDeltaDE2)
			{
				if (i == maxN) break;
			}
			else if (Mode == calcModeColouring)
			{
				CVector4 colorZ = z;
				if (!in.material->fractalColoring.color4dEnabledFalse) colorZ.w = 0.0;
				double len = 0.0;
				switch (in.material->fractalColoring.coloringAlgorithm)
				{
					case fractalColoring_Standard:
					{
						len = colorZ.Length();
						break;
					}
					case fractalColoring_ZDotPoint:
					{
						len = fabs(colorZ.Dot(CVector4(pointTransformed, initialWAxisColor)));
						break;
					}
					case fractalColoring_Sphere:
					{
						len = fabs((colorZ - CVector4(pointTransformed, initialWAxisColor)).Length()
											 - in.material->fractalColoring.sphereRadius);
						break;
					}
					case fractalColoring_Cross:
					{

						len = dMin(fabs(colorZ.x), fabs(colorZ.y), fabs(colorZ.z));
						if (in.material->fractalColoring.color4dEnabledFalse) len = min(len, fabs(colorZ.w));
						break;
					}
					case fractalColoring_Line:
					{

						len = fabs(colorZ.Dot(in.material->fractalColoring.lineDirection));
						break;
					}
					case fractalColoring_Cylinder:
					{
						double distFromAxis = sqrt(colorZ.x * colorZ.x + colorZ.y * colorZ.y);
						len = fabs(distFromAxis - in.material->fractalColoring.sphereRadius);
						break;
					}
					case fractalColoring_Torus:
					{
						double majorR = in.material->fractalColoring.sphereRadius;
						double distXY = sqrt(colorZ.x * colorZ.x + colorZ.y * colorZ.y) - majorR;
						len = sqrt(distXY * distXY + colorZ.z * colorZ.z);
						break;
					}
					case fractalColoring_None:
					{
						len = aux.r;
						break;
					}
				}
				if (!in.material->fractalColoring.colorPreV215False)
				{ // updated code in V2.15
					if (fractal->formula != mandelbox)
					{
						if (len < colorMin) colorMin = len;
						if (aux.r > fractals.GetBailout(sequence)) break;

						if (fractals.UseAdditionalBailoutCond(sequence) && (z - lastZ).Length() / aux.r < 1e-15)
							break;
					}
					else // for Mandelbox. Note in Normal Mode (abox_color) colorMin = 0, else has a value
					{
						if (in.material->fractalColoring.coloringAlgorithm == fractalColoring_Standard)
						{
							if (aux.r > 1e15 || (z - lastZ).Length() / aux.r < 1e-15) break;
						}
						else
						{
							if (len < colorMin) colorMin = len;
							if (aux.r > fractals.GetBailout(sequence) || (z - lastZ).Length() / aux.r < 1e-15)
								break;
						}
					}
				}
				else // pre-v2.15 mode
				{
					if (fractal->formula != mandelbox
							|| in.material->fractalColoring.coloringAlgorithm != fractalColoring_Standard)
					{
						if (len < colorMin) colorMin = len;
						if (aux.r > 1e15 || (z - lastZ).Length() / aux.r < 1e-15)
							break; // old, is updated v2.15
					}
					else // for mandbox and fractalColoring_Standard
					{
						if (aux.r > 1e15 || (z - lastZ).Length() / aux.r < 1e-15) break;
					}
				}
			}

			// Auto-center: capture z at specified iteration
			if (Mode == calcModeOrbitTrap && !autoTrapCenterSet
				&& in.common->fakeLightsCenterIteration > 0
				&& i == in.common->fakeLightsCenterIteration)
			{
				autoTrapCenter = z;
				autoTrapCenterSet = true;
			}


			// Store orbit samples at evenly spaced intervals
			if (Mode == calcModeCubeOrbitTrap && maxN > 0)
			{
				int sampleInterval = max(1, maxN / sFractalOut::maxOrbitSamples);
				if (i % sampleInterval == 0 && out->orbitSampleCount < sFractalOut::maxOrbitSamples)
				{
					out->orbitSamples[out->orbitSampleCount] = z.GetXYZ();
					out->orbitSampleIters[out->orbitSampleCount] = i;
					out->orbitSampleCount++;
				}
			}
			else if (Mode == calcModeOrbitTrap)
			{
				CVector4 trapPoint;
				if (autoTrapCenterSet)
				{
					trapPoint = z - autoTrapCenter; // relatief aan iteratie N
				}
				else if (in.common->fakeLightsRelativeCenter)
				{
					trapPoint = z - aux.const_c;
				}
				else
				{
					trapPoint = z;
				}
				double distance;
				int minCenterIndex = 0;
				if (in.common->fakeLightsMultiCenterEnabled)
				{
					// Multi-center: evaluate distance to all 24 trap positions, take weighted minimum
					distance = 1e30;
					for (int mc = 0; mc < 24; mc++)
					{
						if (in.common->fakeLightsMultiCenterWeight[mc] <= 0.0) continue;

						// Tijdelijk de trap positie overschrijven
						// OrbitTrapShapeDistance berekent: delta = z - par->fakeLightsOrbitTrap
						// We willen: delta = trapPoint - multiCenter[mc]
						// Dus: geef (trapPoint - multiCenter[mc] + par->fakeLightsOrbitTrap) als input
						CVector4 shiftedPoint = trapPoint
							- CVector4(in.common->fakeLightsMultiCenter[mc], 0.0)
							+ CVector4(in.common->fakeLightsOrbitTrap, 0.0);

						double d = OrbitTrapShapeDistance(shiftedPoint, in.common);
						d /= in.common->fakeLightsMultiCenterWeight[mc];
						if (d < distance)
						{
							distance = d;
							minCenterIndex = mc;
						}
					}
				}
				else
				{
					distance = OrbitTrapShapeDistance(trapPoint, in.common);
				}

				if (i >= fakeLightsMinIter && i <= fakeLightsMaxIter)
				{
					double contribution;
					switch (in.common->fakeLightsDecayFunction)
					{
						case params::fakeLightsDecay1R:
							contribution = 1.0 / (distance + 1e-30);
							break;
						case params::fakeLightsDecay1R3:
							contribution = 1.0 / (distance * distance * distance + 1e-30);
							break;
						case params::fakeLightsDecayLinear:
							contribution = max(1.0 - distance * 0.1, 0.0);
							break;
						case params::fakeLightsDecayExp:
							contribution = exp(-distance);
							break;
						default: // fakeLightsDecay1R2
							contribution = 1.0 / (distance * distance + 1e-30);
							break;
					}
					orbitTrapTotal += contribution;

					// Track which iteration had the closest approach
					if (distance < orbitTrapMinDist)
					{
						orbitTrapMinDist = distance;
						out->orbitTrapMinIter = i;
						out->orbitTrapCenterIndex = minCenterIndex;
					}
				}
				if (distance > fractals.GetBailout(sequence))
				{
					out->orbitTrapR = orbitTrapTotal;
					break;
				}
			}
			else if (Mode == calcModeCubeOrbitTrap)
			{
				if (i >= in.material->textureFractalizeStartIteration)
				{
					double size = in.material->textureFractalizeCubeSize * in.material->textureFractalizeSizeMultiplier;
					// Use orbit trap position parameter to offset the trap center
					CVector3 trapCenter = pointTransformed + in.material->textureFractalizeOrbitTrapPosition;
					CVector3 zz = z.GetXYZ() - trapCenter;
					bool trapHit = false;


					switch (in.material->textureFractalizeShape)
					{
						case texture::fractalizeShapeCube:
						{
							if (zz.x > -size && zz.x < size && zz.y > -size && zz.y < size && zz.z > -size
									&& zz.z < size)
							{
								trapHit = true;
							}
							break;
						}
						case texture::fractalizeShapeSphere:
						{
							if (zz.Length() < size)
							{
								trapHit = true;
							}
							break;
						}
						case texture::fractalizeShapeCross:
						{
							double minDist = dMin(fabs(zz.x), fabs(zz.y), fabs(zz.z));
							if (minDist < size)
							{
								trapHit = true;
							}
							break;
						}
						case texture::fractalizeShapeLine:
						{
							// Line along Z axis by default (user can rotate with texture rotation)
							double distFromLine = sqrt(zz.x * zz.x + zz.y * zz.y);
							if (distFromLine < size)
							{
								trapHit = true;
							}
							break;
						}
						case texture::fractalizeShapePlane:
						{
							if (fabs(zz.z) < size)
							{
								trapHit = true;
							}
							break;
						}
						case texture::fractalizeShapeCylinder:
						{
							double distFromAxis = sqrt(zz.x * zz.x + zz.y * zz.y);
							if (distFromAxis < size && fabs(zz.z) < size * 2.0)
							{
								trapHit = true;
							}
							break;
						}
						case texture::fractalizeShapeTorus:
						{
							double majorR = size;
							double minorR = size * 0.4;
							double distXY = sqrt(zz.x * zz.x + zz.y * zz.y) - majorR;
							double distTorus = sqrt(distXY * distXY + zz.z * zz.z);
							if (distTorus < minorR)
							{
								trapHit = true;
							}
							break;
						}
						case texture::fractalizeShapeSpiral:
						{
							double angle = atan2(zz.y, zz.x);
							double r = sqrt(zz.x * zz.x + zz.y * zz.y);
							double spiralR = size * (angle + M_PI) / (2.0 * M_PI);
							double spiralDist = fmod(fabs(r - spiralR), size);
							if (spiralDist > size * 0.5) spiralDist = size - spiralDist;
							if (spiralDist < size * 0.3 && fabs(zz.z) < size)
							{
								trapHit = true;
							}
							break;
						}
					}

					if (trapHit)
					{
						// Continuous SDF: calculate actual distance and weight
						double dx = fabs(zz.x) - size;
						double dy = fabs(zz.y) - size;
						double dz = fabs(zz.z) - size;
						double dist = max(dx, max(dy, dz));
						double softness = size * 0.1;
						if (softness < 1e-10) softness = 1e-10;
						double weight = 1.0 / (1.0 + exp(dist / softness));

						// Continuous color index based on SDF distance (not binary)
						out->colorIndex = (fabs(dist) / size) * 100.0;
						out->iters = i + 1;

						// Blend z toward trap center based on weight for smoother texture coords
						double blend = (weight - 0.5) * 2.0;  // 0..1
						if (blend < 0.0) blend = 0.0;
						if (blend > 1.0) blend = 1.0;
						CVector3 zNormalized = z.GetXYZ();
						double zLen = z.Length();
						if (zLen > 0.0) zNormalized = zNormalized / zLen;
						out->z = z.GetXYZ() * blend + zNormalized * (1.0 - blend);
						// If iteration blending disabled, return immediately (old behavior)
						if (!in.material->textureFractalizeIterationBlend)
						{
							return;
						}
						// else: continue iterating, will use last trap hit
					}
				}
				if (aux.r > in.material->textureFractalizeCubeSize * 100.0)
				{
					out->colorIndex = 0.0;
					out->iters = i + 1;
					out->z = z.GetXYZ(); // Keep actual z position instead of normalizing to unit sphere
					return;
				}
			}
		}

		if (z.IsNotANumber()) // detection of dead computation
		{
			z = lastGoodZ;
			break;
		}
	}

	if (Mode == calcModeOrbitTrap)
	{
		out->orbitTrapR = orbitTrapTotal;
	}

	// final calculations
	if (Mode == calcModeNormal) // analytic
	{
		if (aux.DE > 0.0)
		{
			if (fractals.IsHybrid())
			{
				if (fractals.GetDEFunctionType(0) == fractal::linearDEFunction)
				{
					out->distance = (aux.r - in.common->linearDEOffset) / aux.DE;
				}
				else if (fractals.GetDEFunctionType(0) == fractal::logarithmicDEFunction)
				{
					// out->distance = 0.5 * r * log(r) / aux.DE;
					if (aux.r > 1.0)
						out->distance = 0.5 * aux.r * log(aux.r) / aux.DE;
					else
						out->distance = 0.0;
				}
				else if (fractals.GetDEFunctionType(0) == fractal::pseudoKleinianDEFunction)
				{
					double rxy = sqrt(z.x * z.x + z.y * z.y);

					out->distance = max(rxy - aux.pseudoKleinianDE, fabs(rxy * z.z) / aux.r) / aux.DE;
				}
				else if (fractals.GetDEFunctionType(0) == fractal::josKleinianDEFunction)
				{
					if (fractals.GetFractal(0)->transformCommon.spheresEnabled)
						z.y = min(z.y, fractals.GetFractal(0)->transformCommon.foldingValue - z.y);

					out->distance = min(z.y, fractals.GetFractal(0)->analyticDE.tweak005)
													/ max(aux.DE, fractals.GetFractal(0)->analyticDE.offset1);
				}
				else if (fractals.GetDEFunctionType(0) == fractal::customDEFunction)
				{
					out->distance = aux.dist;
				}
				else if (fractals.GetDEFunctionType(0) == fractal::maxAxisDEFunction)
				{
					CVector4 absZ = fabs(z);
					double rd = max(absZ.x, max(absZ.y, absZ.z));
					out->distance = rd / aux.DE;
				}
			}
			else
			{
				switch (fractals.GetDEAnalyticFunction(sequence))
				{
					case analyticFunctionLogarithmic:
					{
						if (aux.r > 1.0)
							out->distance = 0.5 * aux.r * log(aux.r) / aux.DE;
						else
							out->distance = 0.0;
						break;
					}
					case analyticFunctionLinear:
					{
						out->distance = aux.r / aux.DE;
						break;
					}
					case analyticFunctionIFS:
					{
						out->distance = (aux.r - 2.0) / aux.DE;
						break;
					}
					case analyticFunctionPseudoKleinian:
					{
						double rxy = sqrt(z.x * z.x + z.y * z.y); // * z.w * z.w)
						out->distance = max(rxy - aux.pseudoKleinianDE, fabs(rxy * z.z) / aux.r) / aux.DE;
						break;
					}
					case analyticFunctionJosKleinian:
					{
						if (fractals.GetFractal(sequence)->transformCommon.spheresEnabled)
							z.y = min(z.y, fractals.GetFractal(sequence)->transformCommon.foldingValue - z.y);

						out->distance = min(z.y, fractals.GetFractal(sequence)->analyticDE.tweak005)
														/ max(aux.DE, fractals.GetFractal(sequence)->analyticDE.offset1);
						break;
					}
					case analyticFunctionCustomDE:
					{
						out->distance = aux.dist;
						break;
					}
					case analyticFunctionMaxAxis:
					{
						CVector4 absZ = fabs(z);
						double rd = max(absZ.x, max(absZ.y, absZ.z));
						out->distance = rd / aux.DE;
						break;
					}

					case analyticFunctionNone: out->distance = -1.0; break;
					case analyticFunctionUndefined: out->distance = aux.r; break;
				}
			}
		}
		else
			out->distance = aux.r;
	}

	// color calculation
	else if (Mode == calcModeColouring)
	{
		enumColoringFunction coloringFunction = fractals.GetColoringFunction(sequence);
		out->colorIndex = CalculateColorIndex(fractals.IsHybrid(), aux.r, z, colorMin, aux,
			in.material->fractalColoring, coloringFunction, defaultFractal);
	}
	else
	{
		out->distance = 0.0;

		// needed for JosKleinian fractal to calculate spheres in deltaDE mode
		if (fractals.GetDEFunctionType(0) == fractal::josKleinianDEFunction)
		{
			if (fractals.GetFractal(sequence)->transformCommon.spheresEnabled)
				z.y = min(z.y, fractals.GetFractal(sequence)->transformCommon.foldingValue - z.y);
		}
	}

	out->iters = i + 1;
	out->z = z.GetXYZ();
	out->pseudoKleinianDE = aux.pseudoKleinianDE;
	out->finalDE = aux.DE;
}

template void Compute<calcModeNormal>(const cNineFractals &fractals,
	const cHybridFractalSequences::sSequence *sequence, const sFractalIn &in, sFractalOut *out);
template void Compute<calcModeDeltaDE1>(const cNineFractals &fractals,
	const cHybridFractalSequences::sSequence *sequence, const sFractalIn &in, sFractalOut *out);
template void Compute<calcModeDeltaDE2>(const cNineFractals &fractals,
	const cHybridFractalSequences::sSequence *sequence, const sFractalIn &in, sFractalOut *out);
template void Compute<calcModeColouring>(const cNineFractals &fractals,
	const cHybridFractalSequences::sSequence *sequence, const sFractalIn &in, sFractalOut *out);
template void Compute<calcModeOrbitTrap>(const cNineFractals &fractals,
	const cHybridFractalSequences::sSequence *sequence, const sFractalIn &in, sFractalOut *out);
template void Compute<calcModeCubeOrbitTrap>(const cNineFractals &fractals,
	const cHybridFractalSequences::sSequence *sequence, const sFractalIn &in, sFractalOut *out);

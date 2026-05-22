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

	// v7.5 — Julia start mode (z₀ override)
	{
		const sFormulaMutationParams &mut0 = fractals.GetMutationParams(0);
		if (mut0.enabled && mut0.juliaStart != mutJuliaStartRay)
		{
			CVector4 c = aux.const_c;
			switch (mut0.juliaStart)
			{
				case mutJuliaStartC:
					z = c; break;
				case mutJuliaStartRayPlusC:
					z = z + c; break;
				case mutJuliaStartZero:
					aux.const_c = z; aux.c = z; z = CVector4(0.0, 0.0, 0.0, 0.0); break;
				case mutJuliaStart4D:
					z = CVector4(c.x, c.y, c.z, c.w); break;
				default: break;
			}
		}
	}

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
				// Pre-transform (per-section iteration range)
				if (i >= mut.preIterStart && i < mut.preIterStop)
				{
					if (mut.preAbsX) z.x = fabs(z.x);
					if (mut.preAbsY) z.y = fabs(z.y);
					if (mut.preAbsZ) z.z = fabs(z.z);
					z.x += mut.preOffsetX;
					z.y += mut.preOffsetY;
					z.z += mut.preOffsetZ;
					if (mut.preRotX != 0.0 || mut.preRotY != 0.0 || mut.preRotZ != 0.0)
					{
						CVector3 z3 = z.GetXYZ();
						z3 = mut.preRotMatrix.RotateVector(z3);
						z = CVector4(z3, z.w);
					}
					if (mut.preScale != 1.0)
					{
						z *= mut.preScale;
						aux.DE *= mut.preScale;
					}
				}

				// v7.6 — Inversion (per-section iteration range)
				if (i >= mut.invIterStart && i < mut.invIterStop && mut.inversionType != 0)
				{
					CVector3 zz = z.GetXYZ();
					if (mut.invPreRotX != 0.0 || mut.invPreRotY != 0.0 || mut.invPreRotZ != 0.0)
						zz = mut.invPreRotMatrix.RotateVector(zz);
					zz.x -= mut.invCenterX; zz.y -= mut.invCenterY; zz.z -= mut.invCenterZ;
					double mde = 1.0;
					double ia = mut.invParamA, ib = mut.invParamB, ic = mut.invParamC;
					double iR = mut.invRadius, isc = mut.invScale;
					double rr;
					switch (mut.inversionType)
					{
						case 1: { rr=(zz.x/ia)*(zz.x/ia)+(zz.y/ib)*(zz.y/ib)+(zz.z/ic)*(zz.z/ic); if(rr<1e-21)rr=1e-21; mde=1.0/rr; zz.x*=mde*ia*ia; zz.y*=mde*ib*ib; zz.z*=mde*ic*ic; mde=1.0/rr; break; }
						case 2: { rr=zz.x*zz.x+zz.y*zz.y; if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz.x*=mde; zz.y*=mde; break; }
						case 3: { double rxy=sqrt(zz.x*zz.x+zz.y*zz.y); rr=(rxy-ia)*(rxy-ia)+zz.z*zz.z; if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde; break; }
						case 4: { rr=(zz.x/ia)*(zz.x/ia)+(zz.y/ib)*(zz.y/ib)-(zz.z/ic)*(zz.z/ic); if(fabs(rr)<1e-21)rr=1e-21; mde=1.0/fabs(rr); zz*=mde; break; }
						case 5: { rr=zz.x*zz.x+zz.y*zz.y-ia*zz.z; if(fabs(rr)<1e-21)rr=1e-21; mde=1.0/fabs(rr); zz*=mde; break; }
						case 6: { double tanA=tan(mut.invAngle*M_PI/180.0); rr=zz.x*zz.x+zz.y*zz.y-tanA*tanA*zz.z*zz.z; if(fabs(rr)<1e-21)rr=1e-21; mde=1.0/fabs(rr); zz*=mde; break; }
						case 7: { rr=(zz.x/ia)*(zz.x/ia)-(zz.y/ib)*(zz.y/ib)-zz.z; if(fabs(rr)<1e-21)rr=1e-21; mde=1.0/fabs(rr); zz*=mde; break; }
						case 8: { double r2d=sqrt(zz.x*zz.x+zz.y*zz.y); double theta=atan2(zz.y,zz.x); double k=mut.invFrequency; rr=r2d*exp(-k*theta); if(fabs(rr)<1e-21)rr=1e-21; mde=1.0/rr; zz*=mde; break; }
						case 9: { double x2=zz.x*zz.x,y2=zz.y*zz.y; rr=(x2+y2)*(x2+y2)-ia*ia*(x2-y2); if(fabs(rr)<1e-21)rr=1e-21; mde=1.0/fabs(rr); zz*=mde; break; }
						case 10: { double d1sq=(zz.x-ia)*(zz.x-ia)+zz.y*zz.y; double d2sq=(zz.x+ia)*(zz.x+ia)+zz.y*zz.y; rr=d1sq*d2sq+zz.z*zz.z; if(fabs(rr)<1e-21)rr=1e-21; mde=1.0/rr; zz*=mde; break; }
						case 11: { CVector3 c1(mut.invCenterX,mut.invCenterY,mut.invCenterZ); CVector3 c2(mut.invCenter2X,mut.invCenter2Y,mut.invCenter2Z); CVector3 zr=zz+CVector3(mut.invCenterX,mut.invCenterY,mut.invCenterZ); double d1=(zr-c1).Dot(zr-c1); if(d1<1e-21)d1=1e-21; double d2=(zr-c2).Dot(zr-c2); if(d2<1e-21)d2=1e-21; mde=iR*iR/d1-mut.invRadius2*mut.invRadius2/d2; zz*=mde; mde=fabs(mde); break; }
						case 12: { CVector3 c1(0,0,0); CVector3 c2(mut.invCenter2X,mut.invCenter2Y,mut.invCenter2Z); double w1=mut.invWeight,w2=1.0-w1; double d1=(zz-c1).Dot(zz-c1); if(d1<1e-21)d1=1e-21; double d2=(zz-c2).Dot(zz-c2); if(d2<1e-21)d2=1e-21; mde=w1*iR*iR/d1+w2*mut.invRadius2*mut.invRadius2/d2; zz*=mde; mde=fabs(mde); break; }
						case 13: { CVector3 c1(0,0,0); CVector3 c2(mut.invCenter2X,mut.invCenter2Y,mut.invCenter2Z); double d1=(zz-c1).Dot(zz-c1); if(d1<1e-21)d1=1e-21; double m1=iR*iR/d1; CVector3 z1=c1+(zz-c1)*m1; double d2=(z1-c2).Dot(z1-c2); if(d2<1e-21)d2=1e-21; double m2=mut.invRadius2*mut.invRadius2/d2; zz=c2+(z1-c2)*m2; mde=m1*m2; break; }
						case 14: { mde=1.0; CVector3 cc(0,0,0); double rk=iR; for(int k=0;k<mut.invNSteps&&k<8;k++){CVector3 delta=zz-cc; double dk=delta.Dot(delta); if(dk<1e-21)dk=1e-21; double mk=rk*rk/dk; zz=cc+delta*mk; mde*=mk; cc.x+=mut.invCenter2X/(double)(k+1); cc.y+=mut.invCenter2Y/(double)(k+1); cc.z+=mut.invCenter2Z/(double)(k+1); rk*=0.8;} mde=fabs(mde); break; }
						case 15: { CVector3 centers[4]; centers[0]=CVector3(ia,0,0); centers[1]=CVector3(-ia,0,0); centers[2]=CVector3(0,ia,0); centers[3]=CVector3(0,0,ia); double minD=1e20; int nearest=0; for(int k=0;k<4;k++){double d=(zz-centers[k]).Dot(zz-centers[k]); if(d<minD){minD=d;nearest=k;}} if(minD<1e-21)minD=1e-21; mde=iR*iR/minD; zz=centers[nearest]+(zz-centers[nearest])*mde; break; }
						case 16: { double q=fmax(1.0,ia); double cr2=1.0/(2.0*q*q); CVector3 fc(1.0/q,cr2,0); double d=(zz-fc).Dot(zz-fc); if(d<1e-21)d=1e-21; mde=cr2*cr2/d; zz=fc+(zz-fc)*mde; break; }
						case 17: { CVector3 c1(ia,0,0); CVector3 c2(-ia,0,0); double d1=(zz-c1).Dot(zz-c1); if(d1<1e-21)d1=1e-21; double d2=(zz-c2).Dot(zz-c2); if(d2<1e-21)d2=1e-21; if(d1<d2){mde=iR*iR/d1; zz=c1+(zz-c1)*mde;} else{mde=iR*iR/d2; zz=c2+(zz-c2)*mde;} break; }
						case 18: { double cz_d=ic*zz.x+1.0; double dn=cz_d*cz_d+ic*ic*zz.y*zz.y; if(dn<1e-21)dn=1e-21; mde=1.0/dn; double nx=(ia*zz.x+ib)*cz_d+ia*ic*zz.y*zz.y; double ny=zz.y*(ia-ib*ic); zz.x=nx*mde; zz.y=ny*mde; break; }
						case 19: { rr=zz.x*zz.x+zz.y*zz.y; if(rr<1e-21)rr=1e-21; if(rr<1.0){mde=1.0/rr;zz.x*=mde;zz.y*=-mde;} else{mde=1.0;} if(zz.x>0.5)zz.x-=1.0; if(zz.x<-0.5)zz.x+=1.0; break; }
						case 20: { double lambda=2.0*cos(M_PI/ia); rr=zz.x*zz.x+zz.y*zz.y; if(rr<1e-21)rr=1e-21; if(rr<1.0){mde=1.0/rr;zz.x*=mde;zz.y*=-mde;} else{mde=1.0;} if(zz.x>lambda*0.5)zz.x-=lambda; if(zz.x<-lambda*0.5)zz.x+=lambda; break; }
						case 21: { rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde; break; }
						case 22: { zz.x+=mut.invAmplitude*zz.y; rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde; zz.x-=mut.invAmplitude*zz.y; break; }
						case 23: { double lim=ia; if(zz.x>lim)zz.x=2.0*lim-zz.x; if(zz.x<-lim)zz.x=-2.0*lim-zz.x; if(zz.y>lim)zz.y=2.0*lim-zz.y; if(zz.y<-lim)zz.y=-2.0*lim-zz.y; if(zz.z>lim)zz.z=2.0*lim-zz.z; if(zz.z<-lim)zz.z=-2.0*lim-zz.z; rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde; break; }
						case 24: { zz.x=fabs(zz.x); zz.y=fabs(zz.y); zz.z=fabs(zz.z); rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde; break; }
						case 25: { rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde; double pulse=isc*(1.0+0.1*sin((double)i*mut.invFrequency)); zz*=pulse; mde*=fabs(pulse); break; }
						case 26: { rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde; double freq=mut.invFrequency; zz.x+=mut.invAmplitude*sin(freq*zz.x); zz.y+=mut.invAmplitude*sin(freq*zz.y); zz.z+=mut.invAmplitude*sin(freq*zz.z); break; }
						case 27: { rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde; double ga=(double)i*2.399963; double cosA=cos(ga),sinA=sin(ga); double tx=zz.x*cosA-zz.y*sinA; zz.y=zz.x*sinA+zz.y*cosA; zz.x=tx; break; }
						case 28: { if(aux.DE<mut.invThreshold){rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde;} break; }
						case 29: { rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde; aux.color+=mut.invColorFactor*fabs(mde-1.0); break; }
						case 30: { rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde; double trap=zz.Length(); if(trap<aux.color)aux.color=trap; break; }
						case 31: { CVector4 q(zz.x,zz.y,zz.z,z.w); double qn=q.Dot(q); if(qn<1e-21)qn=1e-21; mde=1.0/qn; q=CVector4(q.x,-q.y,-q.z,-q.w)*mde; zz=CVector3(q.x,q.y,q.z); z.w=q.w; break; }
						case 32: { double n1=zz.x*zz.x+zz.y*zz.y; if(n1<1e-21)n1=1e-21; double n2=zz.z*zz.z+z.w*z.w; if(n2<1e-21)n2=1e-21; zz.x/=n1; zz.y/=-n1; zz.z/=n2; z.w/=-n2; mde=fmax(1.0/n1,1.0/n2); break; }
						case 33: { double dn=zz.x*zz.x-zz.y*zz.y; if(fabs(dn)<1e-21)dn=1e-21; mde=1.0/fabs(dn); zz.x=zz.x/dn; zz.y=-zz.y/dn; break; }
						case 34: { if(fabs(zz.x)<1e-21)zz.x=1e-21; mde=1.0/(zz.x*zz.x); double ox=1.0/zz.x; double oy=-zz.y/(zz.x*zz.x); zz.x=ox; zz.y=oy; break; }
						case 35: { double on=zz.Dot(zz)+z.w*z.w; if(on<1e-21)on=1e-21; mde=1.0/on; zz*=mde; z.w*=-mde; zz.y=-zz.y; zz.z=-zz.z; break; }
						case 36: { double sn=zz.Dot(zz)+z.w*z.w; if(sn<1e-21)sn=1e-21; mde=1.0/sn; zz=CVector3(zz.x,-zz.y,-zz.z)*mde; z.w*=-mde; break; }
						case 37: { rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=1.0/rr; zz*=mde; break; }
						case 38: { double hodge=zz.x*(zz.y*zz.z); if(fabs(hodge)<1e-21)hodge=1e-21; mde=1.0/fabs(hodge); zz.x=(zz.y*zz.z)*mde; zz.y=(zz.x*zz.z)*mde; zz.z=(zz.x*zz.y)*mde; break; }
						case 39: { double detA=zz.x*zz.y-zz.z*zz.z; if(fabs(detA)<1e-21)detA=1e-21; mde=1.0/fabs(detA); double tx=zz.y*mde; zz.y=zz.x*mde; zz.x=tx; zz.z=-zz.z*mde; break; }
						case 40: { double hash=fabs(sin(zz.x*12.9898+zz.y*78.233+zz.z*45.164)*43758.5453); hash=hash-floor(hash); double p=mut.invWeight; rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; if(hash<p){mde=iR*iR/rr;zz*=mde;} else{mde=1.0;} mde=(1.0-p)+p*mde; break; }
						case 41: { rr=zz.Dot(zz); double minR2=mut.invMinR*mut.invMinR; double maxR2=mut.invMaxR*mut.invMaxR; if(rr<minR2)mde=maxR2/minR2; else if(rr<maxR2)mde=maxR2/rr; else mde=1.0; zz*=mde; break; }
						case 42: { double lim=ia; if(zz.x>lim)zz.x=2.0*lim-zz.x; if(zz.x<-lim)zz.x=-2.0*lim-zz.x; if(zz.y>lim)zz.y=2.0*lim-zz.y; if(zz.y<-lim)zz.y=-2.0*lim-zz.y; if(zz.z>lim)zz.z=2.0*lim-zz.z; if(zz.z<-lim)zz.z=-2.0*lim-zz.z; rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde; lim=ib; if(zz.x>lim)zz.x=2.0*lim-zz.x; if(zz.x<-lim)zz.x=-2.0*lim-zz.x; if(zz.y>lim)zz.y=2.0*lim-zz.y; if(zz.y<-lim)zz.y=-2.0*lim-zz.y; if(zz.z>lim)zz.z=2.0*lim-zz.z; if(zz.z<-lim)zz.z=-2.0*lim-zz.z; break; }
						case 43: { double cz_d2=ic*zz.x+1.0; double dn2=cz_d2*cz_d2+ic*ic*zz.y*zz.y; if(dn2<1e-21)dn2=1e-21; double mobMde=(ia*1.0-ib*ic)/dn2; zz.x=(ia*zz.x+ib)/(ic*zz.x+1.0+1e-21); zz.y=zz.y*mobMde; rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde; mde*=fabs(mobMde); break; }
						case 44: { CVector3 dynC=zz*mut.invAmplitude; rr=(zz-dynC).Dot(zz-dynC); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz=dynC+(zz-dynC)*mde; break; }
						case 45: { CVector3 jc(mut.invCenter2X,mut.invCenter2Y,mut.invCenter2Z); rr=(zz-jc).Dot(zz-jc); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz=jc+(zz-jc)*mde; break; }
						case 46: { CVector3 ifs_c(ia,ib,ic); double d=(zz-ifs_c).Dot(zz-ifs_c); if(d<1e-21)d=1e-21; mde=iR*iR/d; zz=ifs_c+(zz-ifs_c)*mde; zz.x=fabs(zz.x); zz.y=fabs(zz.y); break; }
						case 47: { rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde; double theta=mut.invAngle*M_PI/180.0; double cosT=cos(theta),sinT=sin(theta); double tx2=zz.x*cosT-zz.y*sinT; zz.y=zz.x*sinT+zz.y*cosT; zz.x=tx2; zz*=isc; mde*=fabs(isc); break; }
						case 48: { zz.x+=mut.invAmplitude; zz.y+=mut.invAmplitude*zz.x*zz.x; rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde; break; }
						case 49: { double theta=mut.invAngle*M_PI/180.0; double cosT=cos(theta),sinT=sin(theta); double tx3=zz.x*cosT-zz.y*sinT; zz.y=zz.x*sinT+zz.y*cosT; zz.x=tx3; rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=iR*iR/rr; zz*=mde; break; }
						case 50: { CVector3 aa(mut.invCenter2X,mut.invCenter2Y,mut.invCenter2Z); double an=aa.Dot(aa); double za=zz.Dot(aa); double zn=zz.Dot(zz); double dn3=1.0+2.0*za+an*zn; if(fabs(dn3)<1e-21)dn3=1e-21; zz=(zz*(1.0+2.0*za+an)+aa*(1.0+zn))/dn3; mde=(1.0-an)/(dn3*dn3); rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; double invMde=iR*iR/rr; zz*=invMde; mde*=invMde; mde=fabs(mde); break; }
					}
					zz.x += mut.invCenterX; zz.y += mut.invCenterY; zz.z += mut.invCenterZ;
					if (mut.invPreRotX != 0.0 || mut.invPreRotY != 0.0 || mut.invPreRotZ != 0.0)
					{
						CRotationMatrix invRot;
						invRot.SetRotation2(CVector3(-mut.invPreRotX/180.0*M_PI, -mut.invPreRotY/180.0*M_PI, -mut.invPreRotZ/180.0*M_PI));
						zz = invRot.RotateVector(zz);
					}
					z = CVector4(zz, z.w);
					aux.DE *= fabs(mde);
				}

				// Fold injection (pre-formula or both, per-section iteration range)
				if (i >= mut.foldIterStart && i < mut.foldIterStop
					&& mut.foldType != mutFoldNone
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

				// Warp distortion (per-section iteration range)
				if (i >= mut.warpIterStart && i < mut.warpIterStop) {
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

				} // end warp iteration range

				// Math injection (per-section iteration range)
				if (i >= mut.mathIterStart && i < mut.mathIterStop
					&& mut.mathType != mutMathNone)
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
						case mutMathHyperbolicSine:
						{
							// sinh(z) + c — P1=amplitude scale
							double amp = (mut.mathP1 != 0.0) ? mut.mathP1 : 1.0;
							mathZ.x = amp * sinh(z.x);
							mathZ.y = amp * sinh(z.y);
							mathZ.z = amp * sinh(z.z);
							aux.DE = aux.DE * amp * cosh(sqrt(z.x*z.x + z.y*z.y + z.z*z.z)) + 1.0;
							break;
						}
						case mutMathBesselApprox:
						{
							// J₀(r) ≈ cos(r)/sqrt(r) — P1=frequency
							double freq = (mut.mathP1 != 0.0) ? mut.mathP1 : 1.0;
							double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
							if (r > 1e-21)
							{
								double j0 = cos(freq * r) / sqrt(max(r, 1e-21));
								mathZ.x = z.x * j0;
								mathZ.y = z.y * j0;
								mathZ.z = z.z * j0;
								aux.DE = aux.DE * fabs(j0) + 1.0;
							}
							break;
						}
						case mutMathLambertW:
						{
							// z * exp(z) + c — P1=amplitude
							double amp = (mut.mathP1 != 0.0) ? mut.mathP1 : 1.0;
							double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
							double er = exp(min(r, 20.0));
							mathZ.x = amp * z.x * er;
							mathZ.y = amp * z.y * er;
							mathZ.z = amp * z.z * er;
							aux.DE = aux.DE * amp * er * (1.0 + r) + 1.0;
							break;
						}
						case mutMathErrorFunction:
						{
							// erf(z) ≈ tanh(sqrt(π)*z) — fast approximation
							double scale = (mut.mathP1 != 0.0) ? mut.mathP1 : 1.0;
							double sqrtPi = 1.7724538509;
							mathZ.x = scale * tanh(sqrtPi * z.x);
							mathZ.y = scale * tanh(sqrtPi * z.y);
							mathZ.z = scale * tanh(sqrtPi * z.z);
							double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
							double erfDeriv = 2.0 / sqrtPi * exp(-r*r);
							aux.DE = aux.DE * scale * erfDeriv + 1.0;
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

			// v7.5 — Julia pre-fold injection (per-section iteration range)
			if (mut.enabled && mut.juliaInjection != mutJuliaInjectNone
				&& i >= mut.iterationStart && i < mut.iterationStop
				&& i >= mut.juliaIterStart && i < mut.juliaIterStop)
			{
				CVector4 juliaC = aux.const_c * mut.juliaCMul;

				// C-transform
				switch (mut.juliaCTransform)
				{
					case mutJuliaCSpherical:
					{
						double cLen = juliaC.Length();
						if (cLen > 1e-21) juliaC = juliaC * (mut.juliaCRadius / cLen);
						break;
					}
					case mutJuliaCMobius:
					{
						double denom = juliaC.Length() + mut.juliaCMobiusD;
						if (fabs(denom) > 1e-21)
							juliaC = (juliaC * mut.juliaCMobiusA + CVector4(mut.juliaCMobiusB, mut.juliaCMobiusB, mut.juliaCMobiusB, 0.0)) * (1.0 / denom);
						break;
					}
					case mutJuliaCRotate:
						juliaC = mut.juliaCRotMatrix.RotateVector(juliaC);
						break;
					case mutJuliaCPower:
					{
						double r = juliaC.Length();
						if (r > 1e-21) {
							double th = atan2(juliaC.y, juliaC.x);
							double ph = acos(juliaC.z / r);
							double rp = pow(r, mut.juliaCPower);
							juliaC.x = rp * sin(ph * mut.juliaCPower) * cos(th * mut.juliaCPower);
							juliaC.y = rp * sin(ph * mut.juliaCPower) * sin(th * mut.juliaCPower);
							juliaC.z = rp * cos(ph * mut.juliaCPower);
						}
						break;
					}
					case mutJuliaCQuaternion:
					{
						double qw = cos(juliaC.Length() * 0.5);
						double qs = (juliaC.Length() > 1e-21) ? sin(juliaC.Length() * 0.5) / juliaC.Length() : 0.0;
						double qi = juliaC.x * qs, qj = juliaC.y * qs, qk = juliaC.z * qs;
						double zw = 0.0;
						double nw = qw*zw - qi*z.x - qj*z.y - qk*z.z;
						double nx = qw*z.x + qi*zw + qj*z.z - qk*z.y;
						double ny = qw*z.y - qi*z.z + qj*zw + qk*z.x;
						double nz = qw*z.z + qi*z.y - qj*z.x + qk*zw;
						juliaC = CVector4(nx, ny, nz, 0.0);
						break;
					}
					default: break;
				}

				// Dynamic modulation
				switch (mut.juliaDynamic)
				{
					case mutJuliaDynOrbitMod:
						juliaC *= (1.0 + 0.1 * z.Length());
						break;
					case mutJuliaDynPulse:
						juliaC *= sin((double)i * mut.juliaPulseFreq) * mut.juliaPulseAmp;
						break;
					case mutJuliaDynFoldTrigger:
						if (z.Length() > fractals.GetBailout(sequence) * 0.5) juliaC *= 2.0;
						break;
					case mutJuliaDynAbsorb:
						juliaC = juliaC * (1.0 - mut.juliaAbsorb) + z * mut.juliaAbsorb;
						break;
					case mutJuliaDynOrbitMemory:
						juliaC = juliaC + (z - lastZ) * 0.1;
						break;
					default: break;
				}

				// Multi-C modes
				switch (mut.juliaMulti)
				{
					case mutJuliaMultiBipolar:
						if (z.x < 0.0) juliaC = CVector4(mut.juliaBipolarCRx, mut.juliaBipolarCRy, mut.juliaBipolarCRz, 0.0);
						break;
					case mutJuliaMulti4DSwap:
						if (i % 4 == 1) juliaC = CVector4(juliaC.y, juliaC.z, juliaC.w, juliaC.x);
						else if (i % 4 == 2) juliaC = CVector4(juliaC.z, juliaC.w, juliaC.x, juliaC.y);
						else if (i % 4 == 3) juliaC = CVector4(juliaC.w, juliaC.x, juliaC.y, juliaC.z);
						break;
					case mutJuliaMultiFourier:
						juliaC += CVector4(mut.juliaFourierC2x, mut.juliaFourierC2y, mut.juliaFourierC2z, 0.0) * sin((double)i)
								+ CVector4(mut.juliaFourierC3x, mut.juliaFourierC3y, mut.juliaFourierC3z, 0.0) * cos((double)i * 0.5);
						break;
					case mutJuliaMultiNoise:
					{
						double n = sin(z.x * mut.juliaNoiseFreq) * cos(z.y * mut.juliaNoiseFreq * 0.7) * sin(z.z * mut.juliaNoiseFreq * 1.3);
						juliaC += CVector4(n, n, n, 0.0) * mut.juliaNoiseAmp;
						break;
					}
					case mutJuliaMultiRecursive:
						juliaC = juliaC + z * 0.01;
						break;
					default: break;
				}

				// Injection point
				if (mut.juliaInjection == mutJuliaInjectPreFold
					|| mut.juliaInjection == mutJuliaInjectDual)
				{
					z += juliaC;
				}
				else if (mut.juliaInjection == mutJuliaInjectPreScale)
				{
					double r = z.Length();
					double bail = fractals.GetBailout(sequence);
					double factor = (bail > 1e-21) ? r / bail : 1.0;
					z += juliaC * factor;
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

		// v7.5 — Julia mid/post injection (per-section iteration range)
		if (mut.enabled && i >= mut.iterationStart && i < mut.iterationStop
			&& i >= mut.juliaIterStart && i < mut.juliaIterStop
			&& (mut.juliaInjection == mutJuliaInjectMidFold
				|| mut.juliaInjection == mutJuliaInjectPostScale
				|| mut.juliaInjection == mutJuliaInjectDual))
		{
			CVector4 juliaC = aux.const_c * mut.juliaCMul;
			// Apply same C-transform pipeline as pre-fold
			switch (mut.juliaCTransform)
			{
				case mutJuliaCSpherical:
				{
					double cLen = juliaC.Length();
					if (cLen > 1e-21) juliaC = juliaC * (mut.juliaCRadius / cLen);
					break;
				}
				case mutJuliaCRotate:
					juliaC = mut.juliaCRotMatrix.RotateVector(juliaC);
					break;
				default: break;
			}
			switch (mut.juliaDynamic)
			{
				case mutJuliaDynPulse:
					juliaC *= sin((double)i * mut.juliaPulseFreq) * mut.juliaPulseAmp;
					break;
				case mutJuliaDynAbsorb:
					juliaC = juliaC * (1.0 - mut.juliaAbsorb) + z * mut.juliaAbsorb;
					break;
				default: break;
			}
			z += juliaC;
		}

		// -------------- Formula Mutation post-processing ---------------
		{
			bool mutationActive = mut.enabled
				&& i >= mut.iterationStart && i < mut.iterationStop;
			if (mutationActive)
			{
				// Fold injection (post-formula or both, per-section iteration range)
				if (i >= mut.foldIterStart && i < mut.foldIterStop
					&& mut.foldType != mutFoldNone
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

				// Post-transform (per-section iteration range)
				if (i >= mut.postIterStart && i < mut.postIterStop)
				{
					if (mut.postRotX != 0.0 || mut.postRotY != 0.0 || mut.postRotZ != 0.0)
					{
						CVector3 z3 = z.GetXYZ();
						z3 = mut.postRotMatrix.RotateVector(z3);
						z = CVector4(z3, z.w);
					}
					if (mut.postScale != 1.0)
					{
						z *= mut.postScale;
						aux.DE *= mut.postScale;
					}
					z.x += mut.postOffsetX;
					z.y += mut.postOffsetY;
					z.z += mut.postOffsetZ;
				}

				// Z-mix
				if (mut.zMix < 1.0)
				{
					double m = mut.zMix;
					double m1 = 1.0 - m;
					z = z * m + preMutZ * m1;
				}

				// v7.6 — Clip system (per-section iteration range)
				if (i >= mut.clipIterStart && i < mut.clipIterStop && mut.clipType != 0)
				{
					CVector3 cz = z.GetXYZ();
					if (mut.clipPreRotX != 0.0 || mut.clipPreRotY != 0.0 || mut.clipPreRotZ != 0.0)
						cz = mut.clipPreRotMatrix.RotateVector(cz);
					cz.x -= mut.clipCenterX; cz.y -= mut.clipCenterY; cz.z -= mut.clipCenterZ;
					double clipDist = 1e10;
					double sx = mut.clipSizeX, sy = mut.clipSizeY, sz = mut.clipSizeZ;
					double cr = mut.clipRadius, cR = mut.clipMajorRadius;
					double ca = mut.clipParamA, cb = mut.clipParamB, cc = mut.clipParamC;
					switch (mut.clipType)
					{
						case 1: { clipDist=sqrt((cz.x/sx)*(cz.x/sx)+(cz.y/sy)*(cz.y/sy)+(cz.z/sz)*(cz.z/sz))-1.0; break; }
						case 2: { double rxy=sqrt(cz.x*cz.x+cz.y*cz.y)-cR; clipDist=sqrt(rxy*rxy+cz.z*cz.z)-cr; break; }
						case 3: { clipDist=sqrt(cz.x*cz.x+cz.y*cz.y)-cr; break; }
						case 4: { double tanAlpha=tan(mut.clipAngle*M_PI/180.0); clipDist=sqrt(cz.x*cz.x+cz.y*cz.y)-tanAlpha*fabs(cz.z); break; }
						case 5: { clipDist=(cz.x/sx)*(cz.x/sx)+(cz.y/sy)*(cz.y/sy)-(cz.z/sz)*(cz.z/sz)-1.0; break; }
						case 6: { clipDist=cz.x*cz.x+cz.y*cz.y-ca*cz.z; break; }
						case 7: { clipDist=(cz.x/sx)*(cz.x/sx)-(cz.y/sy)*(cz.y/sy)-cz.z; break; }
						case 8: { double r2d=sqrt(cz.x*cz.x+cz.y*cz.y); double theta=atan2(cz.y,cz.x); clipDist=r2d-ca*exp(cb*theta); break; }
						case 9: { double freq=mut.clipFrequency; double amp=mut.clipAmplitude; clipDist=cz.z-amp*sin(freq*cz.x)*sin(freq*cz.y); break; }
						case 10: { double n=sin(cz.x*12.9898+cz.y*78.233)*43758.5453; n=(n-floor(n))*2.0-1.0; double n2=sin(cz.y*19.8672+cz.z*53.471)*28947.3125; n2=(n2-floor(n2))*2.0-1.0; clipDist=cz.z-mut.clipAmplitude*(n+n2)*0.5; break; }
						case 11: { double d1=sqrt((cz.x/sx)*(cz.x/sx)+(cz.y/sy)*(cz.y/sy)+(cz.z/sz)*(cz.z/sz))-1.0; double d2=cz.Length()-cr; clipDist=fmin(d1,d2); break; }
						case 12: { double dA=sqrt((cz.x/sx)*(cz.x/sx)+(cz.y/sy)*(cz.y/sy)+(cz.z/sz)*(cz.z/sz))-1.0; double dB=cz.Length()-cr; clipDist=fmax(dA,-dB); break; }
						case 13: { double dA2=sqrt((cz.x/sx)*(cz.x/sx)+(cz.y/sy)*(cz.y/sy)+(cz.z/sz)*(cz.z/sz))-1.0; double dB2=cz.Length()-cr; clipDist=fmax(fmin(dA2,dB2),-fmax(dA2,dB2)); break; }
						case 14: { double d1s=sqrt((cz.x/sx)*(cz.x/sx)+(cz.y/sy)*(cz.y/sy)+(cz.z/sz)*(cz.z/sz))-1.0; double d2s=cz.Length()-cr; double k=mut.clipSmoothK; double h=fmax(0.0,fmin(1.0,0.5+0.5*(d2s-d1s)/k)); clipDist=d2s+(d1s-d2s)*h-k*h*(1.0-h); break; }
						case 15: { double dAs=sqrt((cz.x/sx)*(cz.x/sx)+(cz.y/sy)*(cz.y/sy)+(cz.z/sz)*(cz.z/sz))-1.0; double dBs=cz.Length()-cr; double k2=mut.clipSmoothK; double h2=fmax(0.0,fmin(1.0,0.5-0.5*(dAs+dBs)/k2)); clipDist=dAs+(-dBs-dAs)*h2+k2*h2*(1.0-h2); break; }
						case 16: { double dc1=cz.Length()-cr; double dc2=fmax(fabs(cz.x)-sx,fmax(fabs(cz.y)-sy,fabs(cz.z)-sz)); double dc3=sqrt(cz.x*cz.x+cz.y*cz.y)-cr*0.5; clipDist=fmax(dc1,fmax(dc2,dc3)); break; }
						case 17: { CVector3 rp=cz; if(sx>0.001)rp.x=fmod(cz.x+sx*0.5,sx)-sx*0.5; if(sy>0.001)rp.y=fmod(cz.y+sy*0.5,sy)-sy*0.5; if(sz>0.001)rp.z=fmod(cz.z+sz*0.5,sz)-sz*0.5; clipDist=rp.Length()-cr; break; }
						case 18: { CVector3 cell; cell.x=(sx>0.001)?floor(cz.x/sx):0; cell.y=(sy>0.001)?floor(cz.y/sy):0; cell.z=(sz>0.001)?floor(cz.z/sz):0; double h=fabs(sin(cell.x*127.1+cell.y*311.7+cell.z*74.7)*43758.5453); h=h-floor(h); CVector3 rp2=cz; if(sx>0.001)rp2.x=fmod(cz.x+sx*0.5,sx)-sx*0.5; if(sy>0.001)rp2.y=fmod(cz.y+sy*0.5,sy)-sy*0.5; if(sz>0.001)rp2.z=fmod(cz.z+sz*0.5,sz)-sz*0.5; clipDist=rp2.Length()-cr*(0.5+h); break; }
						case 19: { double coarse=fmax(fabs(cz.x)-sx*2.0,fmax(fabs(cz.y)-sy*2.0,fabs(cz.z)-sz*2.0)); double fine=cz.Length()-cr; clipDist=(coarse<0.0)?fine:coarse; break; }
						case 20: { CVector3 fz=cz; double fscale=1.0; for(int k=0;k<4;k++){fz.x=fabs(fz.x)*2.0-ca; fz.y=fabs(fz.y)*2.0-ca; fz.z=fabs(fz.z)*2.0-ca; fscale*=2.0;} clipDist=(fz.Length()-cr)/fscale; break; }
						case 21: { clipDist=cz.Length()-cr; break; }
						case 22: { CVector3 scaled(cz.x*sx,cz.y*sy,cz.z*sz); clipDist=scaled.Length()-cr; break; }
						case 23: { CVector3 sheared=cz; sheared.x+=mut.clipAmplitude*cz.y; clipDist=sheared.Length()-cr; break; }
						case 24: { CVector3 folded=cz; double lim=ca; if(folded.x>lim)folded.x=2.0*lim-folded.x; if(folded.x<-lim)folded.x=-2.0*lim-folded.x; if(folded.y>lim)folded.y=2.0*lim-folded.y; if(folded.y<-lim)folded.y=-2.0*lim-folded.y; if(folded.z>lim)folded.z=2.0*lim-folded.z; if(folded.z<-lim)folded.z=-2.0*lim-folded.z; clipDist=folded.Length()-cr; break; }
						case 25: { CVector3 absed(fabs(cz.x),fabs(cz.y),fabs(cz.z)); clipDist=absed.Length()-cr; break; }
						case 26: { clipDist=cz.Length()-cr; double pulse=1.0+0.1*sin((double)i*mut.clipFrequency); clipDist*=pulse; break; }
						case 27: { clipDist=cz.Length()-cr; double sf=ca*(1.0+0.1*(double)i/250.0); clipDist*=sf; break; }
						case 28: { clipDist=cz.Length()-cr; if(clipDist<0.0) aux.color+=fabs(clipDist)*mut.clipAmplitude; break; }
						case 29: { clipDist=cz.Length()-cr; double trap=cz.Length(); if(trap<aux.color)aux.color=trap; break; }
						case 30: { clipDist=cz.Length()-cr; aux.color=log(1.0+fabs(aux.dist))*mut.clipAmplitude; break; }
						case 31: { double r2d=sqrt(cz.x*cz.x+cz.y*cz.y); double theta=atan2(cz.y,cz.x); int n=mut.clipNPoints; double starR=cr*(1.0+mut.clipAmplitude*cos((double)n*theta)); clipDist=r2d-starR; break; }
						case 32: { double x2h=cz.x*cz.x+cz.y*cz.y; clipDist=(x2h-1.0)*(x2h-1.0)*(x2h-1.0)-cz.x*cz.x*cz.y*cz.y*cz.y; break; }
						case 33: { double r2d2=sqrt(cz.x*cz.x+cz.y*cz.y); double theta2=atan2(cz.y,cz.x); double m=(double)mut.clipNPoints; double n1=ca,n2=cb,n3=cc; double t=m*theta2/4.0; double r_sf=pow(pow(fabs(cos(t)/sx),n2)+pow(fabs(sin(t)/sy),n3),-1.0/n1); clipDist=r2d2-r_sf*cr; break; }
						case 34: { double r2d3=sqrt(cz.x*cz.x+cz.y*cz.y); double theta3=atan2(cz.y,cz.x); int ng=mut.clipNPoints; double gearR=cr*(1.0+0.1*tanh(sin((double)ng*theta3))); clipDist=r2d3-gearR; break; }
						case 35: { double r2d4=sqrt(cz.x*cz.x+cz.y*cz.y); double theta4=atan2(cz.y,cz.x); int ns=mut.clipNPoints; double spiralR=ca*exp(-cb*theta4)*(1.0+cc*cos((double)ns*theta4)); clipDist=r2d4-spiralR; break; }
						case 36: { CVector3 seeds[4]; seeds[0]=CVector3(ca,0,0); seeds[1]=CVector3(-ca,cb,0); seeds[2]=CVector3(0,-ca,cc); seeds[3]=CVector3(cb,cc,-ca); double minVD=1e20; for(int k=0;k<4;k++){double vd=(cz-seeds[k]).Length(); if(vd<minVD)minVD=vd;} clipDist=minVD-cr; break; }
						case 37: { CVector3 edges[3]; edges[0]=CVector3(ca,0,0); edges[1]=CVector3(-ca*0.5,ca*0.866,0); edges[2]=CVector3(-ca*0.5,-ca*0.866,0); double minED=1e20; for(int k=0;k<3;k++){CVector3 e=edges[(k+1)%3]-edges[k]; CVector3 p=cz-edges[k]; double t=fmax(0.0,fmin(1.0,p.Dot(e)/e.Dot(e))); double ed=(p-e*t).Length(); if(ed<minED)minED=ed;} clipDist=minED-cr; break; }
						case 38: { CVector3 lz=cz; double lscale=1.0; for(int k=0;k<3;k++){lz.x=fabs(lz.x); lz.y=fabs(lz.y); lz.z=fabs(lz.z); if(lz.x<lz.y){double t=lz.x;lz.x=lz.y;lz.y=t;} if(lz.x<lz.z){double t=lz.x;lz.x=lz.z;lz.z=t;} if(lz.y<lz.z){double t=lz.y;lz.y=lz.z;lz.z=t;} lz=lz*ca-CVector3(cb,cb,cb)*(ca-1.0); lscale*=ca;} clipDist=(lz.Length()-cr)/lscale; break; }
						case 39: { double jx=cz.x,jy=cz.y; for(int k=0;k<8;k++){double tx=jx*jx-jy*jy+ca; jy=2.0*jx*jy+cb; jx=tx; if(jx*jx+jy*jy>4.0)break;} double jDist=(jx*jx+jy*jy>4.0)?-cr:cr; clipDist=fmax(jDist,fabs(cz.z)-sz); break; }
						case 40: { double mx=0,my=0; for(int k=0;k<8;k++){double tx2=mx*mx-my*my+cz.x; my=2.0*mx*my+cz.y; mx=tx2; if(mx*mx+my*my>4.0)break;} double mDist=(mx*mx+my*my>4.0)?-cr:cr; clipDist=fmax(mDist,fabs(cz.z)-sz); break; }
						case 41: { clipDist=fmax(fmax(fabs(cz.x),fabs(cz.y)),fmax(fabs(cz.z),fabs(z.w)))-cr; break; }
						case 42: { clipDist=sqrt(cz.x*cz.x+cz.y*cz.y+cz.z*cz.z+z.w*z.w)-cr; break; }
						case 43: { double time=(double)i*mut.clipFrequency; double tR=cr*(1.0+mut.clipAmplitude*sin(time)); clipDist=cz.Length()-tR; break; }
						case 44: { double orbitR=cr*(1.0+mut.clipAmplitude*sin(aux.color*mut.clipFrequency)); clipDist=cz.Length()-orbitR; break; }
						case 45: { double deR=cr*(1.0+mut.clipAmplitude*log(1.0+fabs(aux.DE))); clipDist=cz.Length()-deR; break; }
						case 46: { double colR=cr*(1.0+mut.clipAmplitude*sin(aux.color*mut.clipFrequency)); clipDist=cz.Length()-colR; break; }
						case 47: { double iterR=cr*(1.0+mut.clipAmplitude*(double)i/250.0); clipDist=cz.Length()-iterR; break; }
						case 48: { double rh=fabs(sin((double)i*12.9898+cz.x*78.233)*43758.5453); rh=rh-floor(rh); double randR=cr*(1.0+mut.clipAmplitude*(rh-0.5)); clipDist=cz.Length()-randR; break; }
						case 49: { double nx=tanh(ca*cz.x+cb*cz.y+cc*cz.z); double ny=tanh(cb*cz.x-ca*cz.y+cc*cz.z); double nz=tanh(cc*cz.x+ca*cz.y-cb*cz.z); clipDist=sqrt(nx*nx+ny*ny+nz*nz)-cr; break; }
						case 50: { CVector3 rz=cz; double rscale=1.0; for(int k=0;k<5;k++){rz.x=fabs(rz.x)*2.0-ca; rz.y=fabs(rz.y)*2.0-ca; rz.z=fabs(rz.z)*2.0-ca; rscale*=2.0; double rd=rz.Length()-cr; rd/=rscale; if(rd<clipDist)clipDist=rd;} break; }
					}
					int bop = mut.clipBooleanOp;
					if (bop == 0) aux.dist = fmax(aux.dist, clipDist);
					else if (bop == 1) aux.dist = fmin(aux.dist, clipDist);
					else if (bop == 2) aux.dist = fmax(aux.dist, -clipDist);
					else if (bop == 3) aux.dist = fmax(fmin(aux.dist, clipDist), -fmax(aux.dist, clipDist));
					else if (bop == 4) { double kk=mut.clipSmoothK; double hh=fmax(0.0,fmin(1.0,0.5+0.5*(clipDist-aux.dist)/kk)); aux.dist=clipDist+(aux.dist-clipDist)*hh-kk*hh*(1.0-hh); }
					else if (bop == 5) { double kk2=mut.clipSmoothK; double hh2=fmax(0.0,fmin(1.0,0.5-0.5*(aux.dist+clipDist)/kk2)); aux.dist=aux.dist+(-clipDist-aux.dist)*hh2+kk2*hh2*(1.0-hh2); }
				}
				// v7.7 — Jos Leys DE system (per-section iteration range)
				if (i >= mut.josIterStart && i < mut.josIterStop && mut.josLeysDeType != 0)
				{
					double jf = mut.josFactor;
					double ja = mut.josParamA, jb = mut.josParamB, jc = mut.josParamC, jd = mut.josParamD;
					double jfreq = mut.josFreq, jamp = mut.josAmp, jsc = mut.josScale, jph = mut.josPhase;
					double zx = z.x, zy = z.y, zz2 = z.z;
					double rr = zx*zx + zy*zy + zz2*zz2; if (rr < 1e-21) rr = 1e-21;
					double r = sqrt(rr);
					switch (mut.josLeysDeType)
					{
						case 1: { double k1=ja,k2=jb,k3=jc,k4=jd; double curv=(k1+k2+k3+k4)/fmax(1.0,r); aux.DE*=(1.0+jf*curv); break; }
						case 2: { double phi=atan2(zy,zx); double sp=ja*exp(2.0*M_PI*(jb*phi+jc*log(fmax(1e-10,r)))); aux.DE*=(1.0+jf*sp); break; }
						case 3: { double prod=1.0; for(int k=0;k<4;k++){double dk=r+ja*(double)(k+1); prod*=fmax(0.01,dk);} aux.DE*=(1.0+jf*jsc/fmax(1e-10,prod)); break; }
						case 4: { double af=ja*log(fmax(1e-10,r))+jb*atan2(zy,zx); aux.DE*=(1.0+jf*tanh(af)); break; }
						case 5: { double hyp=4.0*M_PI*(ja-1.0)/fmax(1e-10,rr); aux.DE*=(1.0+jf*tanh(hyp)); break; }
						case 6: { double bel=ja*zy/fmax(1e-10,rr); aux.DE*=(1.0+jf*tanh(bel)); break; }
						case 7: { double tr=ja*jb/fmax(1e-10,r); aux.DE*=(1.0+jf*tanh(tr)); break; }
						case 8: { double rl=ja/(fmax(1e-10,r*r)+jb*jb); aux.DE*=(1.0+jf*rl); break; }
						case 9: { double bs=ja*jb*jc/fmax(1e-10,rr); aux.DE*=(1.0+jf*tanh(bs)); break; }
						case 10: { double ew=ja*sin(jfreq*zx)*cos(jfreq*zy)/fmax(1e-10,r); aux.DE*=(1.0+jf*ew); break; }
						case 11: { double hc=exp(-fabs(zy))*ja/fmax(1e-10,r); aux.DE*=(1.0+jf*hc); break; }
						case 12: { double q2=fmax(1.0,ja); double fr2=1.0/(2.0*q2*q2); aux.DE*=(1.0+jf*fr2/fmax(1e-10,r)); break; }
						case 13: { double med=(zx+zy)/(fmax(1e-10,2.0*r)); aux.DE*=(1.0+jf*ja*med); break; }
						case 14: { double jt=ja*sin(M_PI*zx/fmax(0.01,jb))*sin(M_PI*zy/fmax(0.01,jc)); aux.DE*=(1.0+jf*jt/fmax(1e-10,rr)); break; }
						case 15: { double eta=exp(M_PI*zy/(12.0*fmax(0.01,ja))); for(int n=1;n<8;n++) eta*=(1.0-exp(-2.0*M_PI*n*fabs(zy)/fmax(0.01,ja))); aux.DE*=(1.0+jf*fabs(eta)); break; }
						case 16: { double wp=1.0/(rr+1e-10); for(int n=1;n<6;n++){double dn2=(zx-n*ja)*(zx-n*ja)+(zy-n*jb)*(zy-n*jb)+zz2*zz2; wp+=1.0/fmax(1e-10,dn2)-1.0/(n*n*ja*ja+n*n*jb*jb+1e-10);} aux.DE*=(1.0+jf*fabs(wp)); break; }
						case 17: { double th=0.0; for(int n=0;n<8;n++){double qn=exp(-M_PI*n*n*fabs(zy)/fmax(0.01,ja)); th+=qn*cos(2.0*M_PI*n*zx/fmax(0.01,ja));} aux.DE*=(1.0+jf*fabs(th)); break; }
						case 18: { double eis=0.0; for(int m=-3;m<=3;m++) for(int n=-3;n<=3;n++){if(m==0&&n==0)continue; double dn=m*ja+n*jb; eis+=1.0/fmax(1e-10,pow(fabs(dn*dn+rr),jc));} aux.DE*=(1.0+jf*fabs(eis)); break; }
						case 19: { double hek=ja*sin(jfreq*r)*cos(jfreq*atan2(zy,zx)+jph); aux.DE*=(1.0+jf*hek/fmax(1e-10,r)); break; }
						case 20: { double maas=ja*sin(jfreq*log(fmax(1e-10,r)))*cos(jfreq*atan2(zy,zx)); aux.DE*=(1.0+jf*maas); break; }
						case 21: { double selb=1.0; for(int k=1;k<=5;k++){selb*=(1.0-exp(-ja*k*r));} aux.DE*=(1.0+jf*(1.0-fabs(selb))); break; }
						case 22: { double ruel=1.0; for(int k=1;k<=5;k++){ruel*=(1.0-exp(-ja*k*log(fmax(1e-10,r))));} aux.DE*=(1.0+jf*fabs(ruel)); break; }
						case 23: { double dz=ja*sin(jfreq*r)*exp(-jb*r); aux.DE*=(1.0+jf*dz); break; }
						case 24: { double gut=0.0; for(int p=1;p<=5;p++){gut+=ja*cos(jfreq*p*r+jph)/fmax(1.0,(double)p);} aux.DE*=(1.0+jf*gut/fmax(1e-10,r)); break; }
						case 25: { double berry=ja*zy*zz2/fmax(1e-10,rr*r); aux.DE*=(1.0+jf*berry); break; }
						case 26: { double hann=ja*zx*zy/fmax(1e-10,rr); aux.DE*=(1.0+jf*hann); break; }
						case 27: { double ab_ph=ja*atan2(zy,zx)/fmax(1e-10,r); aux.DE*=(1.0+jf*ab_ph); break; }
						case 28: { double ac_ph=ja*jb*zz2/fmax(1e-10,rr); aux.DE*=(1.0+jf*ac_ph); break; }
						case 29: { double sab=ja*sin(jfreq*r)*zy/fmax(1e-10,rr); aux.DE*=(1.0+jf*sab); break; }
						case 30: { double hmw=ja*(zx*zy-zy*zz2)/fmax(1e-10,rr*r); aux.DE*=(1.0+jf*hmw); break; }
						case 31: { double ana=ja*sin(jfreq*rr+jph)/fmax(1e-10,r); aux.DE*=(1.0+jf*ana); break; }
						case 32: { double panch=ja*cos(jfreq*zx)*cos(jfreq*zy)*cos(jfreq*zz2); aux.DE*=(1.0+jf*panch/fmax(1e-10,r)); break; }
						case 33: { double mt=ja/(2.0*fmax(1e-10,fabs(zx-zy))); aux.DE*=(1.0+jf*tanh(mt)); break; }
						case 34: { double ml=M_PI*ja/(2.0*fmax(1e-10,r)); aux.DE*=(1.0+jf*tanh(ml)); break; }
						case 35: { double sw=ja*jb/(fmax(1e-10,r)*jc); aux.DE*=(1.0+jf*tanh(sw)); break; }
						case 36: { double pw=ja*exp(-jb*rr); aux.DE*=(1.0+jf*pw); break; }
						case 37: { double gp=ja*sqrt(fmax(0.0,r/jb)); aux.DE*=(1.0+jf*tanh(gp)); break; }
						case 38: { double rov=ja*sin(jfreq*zx+jph)*cos(jfreq*zy); aux.DE*=(1.0+jf*rov/fmax(1e-10,r)); break; }
						case 39: { double barb=ja*sqrt(fmax(0.0,zx*zx+zy*zy))/fmax(1e-10,r); aux.DE*=(1.0+jf*barb); break; }
						case 40: { double con=ja*exp(-jb*fabs(zz2))*sin(jfreq*r); aux.DE*=(1.0+jf*con); break; }
						case 41: { double ach=ja*sin(jfreq*zx)*sin(jfreq*zy)*cos(jfreq*zz2)/fmax(1e-10,r); aux.DE*=(1.0+jf*ach); break; }
						case 42: { double que=ja/(fmax(1e-10,rr)); aux.DE*=(1.0+jf*que); break; }
						case 43: { double rw=0.0; for(int n=1;n<=8;n++){rw+=cos(jfreq*n*zx+jph*n)*exp(-jb*n);} aux.DE*=(1.0+jf*ja*rw/fmax(1e-10,r)); break; }
						case 44: { double nd=ja*floor(sin(jfreq*zx)*sin(jfreq*zy)*4.0+2.0)/4.0; aux.DE*=(1.0+jf*nd); break; }
						case 45: { double nl=ja*fabs(sin(jfreq*zx)*cos(jfreq*zy))*jb; aux.DE*=(1.0+jf*nl/fmax(1e-10,r)); break; }
						case 46: { double pc=ja*(tanh(jb*(r-jc))+1.0)*0.5; aux.DE*=(1.0+jf*pc); break; }
						case 47: { double ip=ja*tanh(jb*(sin(jfreq*zx)+sin(jfreq*zy)+sin(jfreq*zz2))); aux.DE*=(1.0+jf*ip); break; }
						case 48: { double cle=ja*sin(jfreq*atan2(zy,zx))*exp(-jb*r); aux.DE*=(1.0+jf*cle); break; }
						case 49: { double sle=ja*zy/(fmax(1e-10,rr))*exp(-jb*fabs(zx)); aux.DE*=(1.0+jf*sle); break; }
						case 50: { double gff=ja*cos(jfreq*zx)*cos(jfreq*zy)/fmax(1e-10,r); aux.DE*=(1.0+jf*gff); break; }
						case 51: { double lqg=ja*exp(jb*sin(jfreq*r+jph)); aux.DE*=(1.0+jf*lqg/fmax(1e-10,r)); break; }
						case 52: { double bm=ja*sqrt(fmax(0.0,rr-jb*jb))/fmax(1e-10,rr); aux.DE*=(1.0+jf*bm); break; }
						case 53: { double pm2=ja*(2.0-fabs(zx)+fabs(zy)-fabs(zz2))/fmax(1e-10,r); aux.DE*=(1.0+jf*tanh(pm2)); break; }
						case 54: { double tt=ja*(zx*zy+zy*zz2+zz2*zx)/fmax(1e-10,rr*r); aux.DE*=(1.0+jf*tt); break; }
						case 55: { double jon=ja*sin(M_PI*jb*r+jph)/fmax(1e-10,r); aux.DE*=(1.0+jf*jon); break; }
						case 56: { double hom=ja*(sin(jfreq*zx)+sin(jfreq*zy))*jb/fmax(1e-10,rr); aux.DE*=(1.0+jf*hom); break; }
						case 57: { double kau=ja*tanh(jb*sin(jfreq*r)*cos(jfreq*atan2(zy,zx))); aux.DE*=(1.0+jf*kau); break; }
						case 58: { double cs=ja*sin(jfreq*zx)*sin(jfreq*zy)*sin(jfreq*zz2)/(fmax(1e-10,r*r)); aux.DE*=(1.0+jf*cs); break; }
						case 59: { double wrt=ja*jb*cos(jfreq*r+jph)/fmax(1e-10,rr); aux.DE*=(1.0+jf*wrt); break; }
						case 60: { double tv=ja*jb*jc/(fmax(1e-10,rr*r)); aux.DE*=(1.0+jf*tanh(tv)); break; }
						case 61: { double cy=ja*pow(fmax(1e-10,r),jb-3.0); aux.DE*=(1.0+jf*cy); break; }
						case 62: { double dw=ja/(fmax(1e-10,rr))*cos(jfreq*zz2); aux.DE*=(1.0+jf*dw); break; }
						case 63: { double yd=ja*jb*(zx*zy-zy*zx)/(fmax(1e-10,rr)); aux.DE*=(1.0+jf*yd*jc); break; }
						case 64: { double mtc=ja*sin(jfreq*zx+jph)*cos(jfreq*zy)*sin(jfreq*zz2)/fmax(1e-10,r); aux.DE*=(1.0+jf*mtc); break; }
						case 65: { double fus=ja*(sin(jb*zx)*sin(jc*zy)+sin(jd*zz2))/fmax(1e-10,r); aux.DE*=(1.0+jf*fus); break; }
						case 66: { double bra=ja*cos(jfreq*atan2(zy,zx)+jph)*cos(jfreq*atan2(zz2,r)); aux.DE*=(1.0+jf*bra); break; }
						case 67: { double rib=ja*sin(jfreq*r)*cos(jb*atan2(zy,zx)+jph); aux.DE*=(1.0+jf*rib/fmax(1e-10,r)); break; }
						case 68: { double hopf=ja*jb*tanh(jc*(zx*zy+zy*zz2)); aux.DE*=(1.0+jf*hopf/fmax(1e-10,r)); break; }
						case 69: { double qg=ja*pow(fmax(1e-10,r),-jb)*sin(jfreq*r+jph); aux.DE*=(1.0+jf*qg); break; }
						case 70: { double dd=ja*jb*(1.0/(fmax(1e-10,rr))+zx*zy/(fmax(1e-10,rr*r))); aux.DE*=(1.0+jf*tanh(dd)); break; }
						case 71: { double nich=ja*exp(-jb*rr)*sin(jfreq*zx)*cos(jfreq*zy); aux.DE*=(1.0+jf*nich); break; }
						case 72: { double rack=ja*(zx*zx-zy*zy)/(fmax(1e-10,rr))*jb; aux.DE*=(1.0+jf*rack); break; }
						case 73: { double quan=ja*(zx*zx*zx-3.0*zx*zy*zy)/(fmax(1e-10,rr*r))*jb; aux.DE*=(1.0+jf*quan); break; }
						case 74: { double biq=ja*sin(jfreq*(zx+zy))*cos(jfreq*(zx-zy))/fmax(1e-10,r); aux.DE*=(1.0+jf*biq); break; }
						case 75: { double ske=ja*jb*sin(jfreq*r+jph)/(fmax(1e-10,rr)); aux.DE*=(1.0+jf*ske); break; }
						case 76: { double khov=ja*pow(fmax(1e-10,sin(jfreq*r)),2.0)*jb/fmax(1e-10,r); aux.DE*=(1.0+jf*khov); break; }
						case 77: { double hf=ja*exp(-jb*r)*cos(jfreq*zz2+jph); aux.DE*=(1.0+jf*hf); break; }
						case 78: { double kf=ja*atan2(zy,zx)*exp(-jb*fabs(zz2))/M_PI; aux.DE*=(1.0+jf*kf/fmax(1e-10,r)); break; }
						case 79: { double ech2=ja*sin(jfreq*zx)*exp(-jb*zy)*cos(jfreq*zz2)/fmax(1e-10,r); aux.DE*=(1.0+jf*ech2); break; }
						case 80: { double sft=ja*cos(jfreq*r)*sin(jfreq*atan2(zy,zx)+jph)/fmax(1e-10,r); aux.DE*=(1.0+jf*sft); break; }
						case 81: { double lag=ja*(zx*zy+zy*zz2)/(fmax(1e-10,rr))*jb; aux.DE*=(1.0+jf*lag); break; }
						case 82: { double fuk=ja*sin(jb*zx)*cos(jc*zy)*sin(jd*zz2)/fmax(1e-10,r); aux.DE*=(1.0+jf*fuk); break; }
						case 83: { double mir=ja*(sin(jfreq*zx)*sin(jfreq*zy)-cos(jfreq*zz2))/fmax(1e-10,r); aux.DE*=(1.0+jf*mir); break; }
						case 84: { double hmir=ja*cos(jfreq*(zx+zy+zz2)+jph)/fmax(1e-10,r); aux.DE*=(1.0+jf*hmir); break; }
						case 85: { double syz=ja*sin(jfreq*r)*sin(jfreq*atan2(zy,zx))*cos(jfreq*zz2/fmax(0.01,jb)); aux.DE*=(1.0+jf*syz); break; }
						case 86: { double slag=ja*cos(jfreq*zx+jph)*jb; aux.DE*=(1.0+jf*slag/fmax(1e-10,r)); break; }
						case 87: { double g2=ja*sin(jfreq*zx)*sin(jfreq*zy)*sin(jfreq*zz2)*jb; aux.DE*=(1.0+jf*g2/fmax(1e-10,rr)); break; }
						case 88: { double sp7=ja*cos(jfreq*(zx*zy+zy*zz2+zz2*zx)/fmax(1e-10,rr)+jph); aux.DE*=(1.0+jf*sp7); break; }
						case 89: { double cy2=ja*exp(-jb*rr)*jc; aux.DE*=(1.0+jf*cy2); break; }
						case 90: { double hkah=ja*(zx*zx-zy*zy+zz2*zz2)/(fmax(1e-10,rr*r))*jb; aux.DE*=(1.0+jf*hkah); break; }
						case 91: { double qkah=ja*jb*(zx*zy*zz2)/(fmax(1e-10,rr*rr)); aux.DE*=(1.0+jf*tanh(qkah)); break; }
						case 92: { double sas=ja*sqrt(fmax(0.0,r-jb))/fmax(1e-10,r); aux.DE*=(1.0+jf*sas); break; }
						case 93: { double s3s=ja*(sin(jfreq*zx)+sin(jfreq*zy)+sin(jfreq*zz2))/(3.0*fmax(1e-10,r)); aux.DE*=(1.0+jf*s3s); break; }
						case 94: { double exh=ja*pow(fmax(1e-10,r),-jb)*cos(jfreq*r+jph); aux.DE*=(1.0+jf*exh); break; }
						case 95: { double joy=ja*sin(jfreq*zx/fmax(0.01,jb))*sin(jfreq*zy/fmax(0.01,jc))*sin(jfreq*zz2/fmax(0.01,jd)); aux.DE*=(1.0+jf*joy); break; }
						case 96: { double kov=ja*exp(-jb*fabs(zz2))*cos(jfreq*sqrt(fmax(0.0,zx*zx+zy*zy))); aux.DE*=(1.0+jf*kov); break; }
						case 97: { double chnp=ja*jb*tanh(jc*r-jd); aux.DE*=(1.0+jf*chnp/fmax(1e-10,r)); break; }
						case 98: { double bs=ja*exp(-jb*r)*cos(jfreq*r+jph)*jc; aux.DE*=(1.0+jf*bs); break; }
						case 99: { double ah=ja*jb/(fmax(1e-10,rr))*cos(jfreq*atan2(zy,zx)+jph); aux.DE*=(1.0+jf*ah); break; }
						case 100: { double gh=ja*jb*jc/fmax(1e-10,r)*sin(jfreq*zz2+jph); aux.DE*=(1.0+jf*gh); break; }
					}
				}

				// v7.7 — Pseudokleinian DE system (per-section iteration range)
				if (i >= mut.pkIterStart && i < mut.pkIterStop && mut.pseudoKleinianDeType != 0)
				{
					double pf = mut.pkFactor;
					double pa = mut.pkParamA, pb = mut.pkParamB, pc = mut.pkParamC, pd = mut.pkParamD;
					double pfreq = mut.pkFreq, pamp = mut.pkAmp, psc = mut.pkScale, pph = mut.pkPhase;
					double zx = z.x, zy = z.y, zz2 = z.z;
					double rr = zx*zx + zy*zy + zz2*zz2; if (rr < 1e-21) rr = 1e-21;
					double r = sqrt(rr);
					switch (mut.pseudoKleinianDeType)
					{
						case 1: { double mu=pa*zy/fmax(1e-10,rr); aux.DE*=(1.0+pf*tanh(mu)); break; }
						case 2: { double bers=pa*log(fmax(1e-10,r))*pb; aux.DE*=(1.0+pf*tanh(bers)); break; }
						case 3: { double eq=pa*sin(pfreq*zx)*cos(pfreq*zy); aux.DE*=(1.0+pf*eq/fmax(1e-10,r)); break; }
						case 4: { double bc=pa*pb*zy/fmax(1e-10,rr); aux.DE*=(1.0+pf*bc); break; }
						case 5: { double ham=pa*exp(-pb*r)*sin(pfreq*zx); aux.DE*=(1.0+pf*ham); break; }
						case 6: { double wp=pa*pb/(fmax(1e-10,rr)); aux.DE*=(1.0+pf*wp); break; }
						case 7: { double tm=pa*fabs(zx-zy)/fmax(1e-10,r); aux.DE*=(1.0+pf*tanh(tm)); break; }
						case 8: { double kob=pa*tanh(pb*r)/fmax(1e-10,r); aux.DE*=(1.0+pf*kob); break; }
						case 9: { double car=pa*fabs(sin(pfreq*r))/fmax(1e-10,r); aux.DE*=(1.0+pf*car); break; }
						case 10: { double berg=pa*pb*cos(pfreq*zx+pph)*cos(pfreq*zy)/fmax(1e-10,rr); aux.DE*=(1.0+pf*berg); break; }
						case 11: { double ke=pa*pb/fmax(1e-10,r)*tanh(pc*rr); aux.DE*=(1.0+pf*ke); break; }
						case 12: { double csc2=pa*tanh(pb*(r-pc)); aux.DE*=(1.0+pf*csc2); break; }
						case 13: { double duy=pa*pb*exp(-pc*rr); aux.DE*=(1.0+pf*duy); break; }
						case 14: { double hk=pa*sin(pfreq*zx)*cos(pfreq*zy)*exp(-pb*fabs(zz2)); aux.DE*=(1.0+pf*hk); break; }
						case 15: { double nah=pa*pb*(zx*zy+zy*zz2)/(fmax(1e-10,rr*r)); aux.DE*=(1.0+pf*nah); break; }
						case 16: { double hm=pa*exp(-pb*rr)*cos(pfreq*r+pph); aux.DE*=(1.0+pf*hm); break; }
						case 17: { double ms=pa*(1.0-zz2/fmax(1e-10,r)); aux.DE*=(1.0+pf*ms*pb); break; }
						case 18: { double cmc=pa*cos(pfreq*zx)*cos(pfreq*zy)*pb; aux.DE*=(1.0+pf*cmc/fmax(1e-10,r)); break; }
						case 19: { double wil=pa*(zx*zx+zy*zy)/(fmax(1e-10,rr*r))*pb; aux.DE*=(1.0+pf*wil); break; }
						case 20: { double iso=pa*cos(pfreq*zx+pph)*cos(pfreq*zy)*pb; aux.DE*=(1.0+pf*iso); break; }
						case 21: { double lax=pa*sin(pfreq*zx)*cos(pfreq*zy)*sin(pfreq*zz2)/fmax(1e-10,r); aux.DE*=(1.0+pf*lax); break; }
						case 22: { double bac=pa*exp(-pb*r)*sin(pfreq*r+pph); aux.DE*=(1.0+pf*bac); break; }
						case 23: { double dar=pa*pb*cos(pfreq*r+pph)/fmax(1e-10,rr); aux.DE*=(1.0+pf*dar); break; }
						case 24: { double mou=pa*sin(pfreq*zx)*sin(pfreq*zy)/fmax(1e-10,r); aux.DE*=(1.0+pf*mou); break; }
						case 25: { double hir=pa*pb*exp(-pc*rr)*cos(pfreq*r); aux.DE*=(1.0+pf*hir); break; }
						case 26: { double sat=pa*sin(pfreq*zx+pph)*cos(pfreq*zy)*sin(pfreq*zz2)/fmax(1e-10,r); aux.DE*=(1.0+pf*sat); break; }
						case 27: { double kp=pa*(sin(pfreq*zx)*cos(pfreq*zy)+sin(pfreq*zy)*cos(pfreq*zz2))/fmax(1e-10,r); aux.DE*=(1.0+pf*kp); break; }
						case 28: { double kdv=pa*sin(pfreq*zx+pph)*exp(-pb*zy*zy)/fmax(1e-10,r); aux.DE*=(1.0+pf*kdv); break; }
						case 29: { double nls=pa*exp(-pb*(zx*zx+zy*zy))*cos(pfreq*zz2+pph); aux.DE*=(1.0+pf*nls); break; }
						case 30: { double sg=pa*sin(sin(pfreq*zx+pph))*pb; aux.DE*=(1.0+pf*sg/fmax(1e-10,r)); break; }
						case 31: { double toda=pa*exp(pb*(zx-zy))-pa*exp(pb*(zy-zz2)); aux.DE*=(1.0+pf*tanh(toda)/fmax(1e-10,r)); break; }
						case 32: { double cm=0.0; {double d1=zx-zy; double d2=zy-zz2; double d3=zx-zz2; cm=pa*(1.0/fmax(1e-10,d1*d1*d1)+1.0/fmax(1e-10,d2*d2*d2)+1.0/fmax(1e-10,d3*d3*d3));} aux.DE*=(1.0+pf*tanh(cm)); break; }
						case 33: { double rs=pa*tanh(pb*(zx-zy))*tanh(pb*(zy-zz2))/fmax(1e-10,r); aux.DE*=(1.0+pf*rs); break; }
						case 34: { double hs=pa*pb*(zx*zy+zy*zz2+zz2*zx)/(fmax(1e-10,rr*r)); aux.DE*=(1.0+pf*hs); break; }
						case 35: { double bm=pa*sin(pfreq*zx)*sin(pfreq*zy)*pb/fmax(1e-10,r); aux.DE*=(1.0+pf*bm); break; }
						case 36: { double aci=pa*sin(pfreq*r+pph)*cos(pfreq*atan2(zy,zx))/fmax(1e-10,r); aux.DE*=(1.0+pf*aci); break; }
						case 37: { double sep=pa*(sin(pb*zx)+sin(pc*zy)+sin(pd*zz2))/fmax(1e-10,r); aux.DE*=(1.0+pf*sep); break; }
						case 38: { double aa=pa*cos(pfreq*r)*pfreq/fmax(1e-10,r); aux.DE*=(1.0+pf*aa); break; }
						case 39: { double kam=pa*cos(pfreq*r+pph)*(1.0-pb/fmax(1e-10,r)); aux.DE*=(1.0+pf*kam); break; }
						case 40: { double nek=pa*exp(-1.0/fmax(1e-10,pow(fmax(1e-10,pb),pc))); aux.DE*=(1.0+pf*nek); break; }
						case 41: { double ard=pa*sin(pfreq*zx)*cos(pfreq*zy)*sin(pfreq*zz2)/fmax(1e-10,rr); aux.DE*=(1.0+pf*ard); break; }
						case 42: { double abm=pa*fabs(sin(pfreq*zx+pph))/fmax(1e-10,r); aux.DE*=(1.0+pf*abm); break; }
						case 43: { double mse=pa*pb*exp(-pc*rr)*sin(pfreq*zx); aux.DE*=(1.0+pf*mse); break; }
						case 44: { double pei=pa*(1.0-exp(-pb*fabs(zx-zy)))/fmax(1e-10,r); aux.DE*=(1.0+pf*pei); break; }
						case 45: { double fk=pa*sin(pfreq*zx+pph)*cos(pb*zy); aux.DE*=(1.0+pf*fk/fmax(1e-10,r)); break; }
						case 46: { double sm=pa*sin(pfreq*atan2(zy,zx)+pph)*pb; aux.DE*=(1.0+pf*sm/fmax(1e-10,r)); break; }
						case 47: { double chi=pa*tanh(pb*(r-pc)); aux.DE*=(1.0+pf*chi); break; }
						case 48: { double gre=0.5*(1.0-pa*cos(pfreq*r+pph)/fmax(1e-10,r)); aux.DE*=(1.0+pf*gre); break; }
						case 49: { double rg=pa*pow(fmax(1e-10,r),-pb)*cos(pfreq*log(fmax(1e-10,r))+pph); aux.DE*=(1.0+pf*rg); break; }
						case 50: { double fg=pa*4.669201609*sin(pfreq*r+pph)/(fmax(1e-10,r)); aux.DE*=(1.0+pf*fg); break; }
						case 51: { double sh3=pa*floor(sin(pfreq*zx)*3.0+1.5)/3.0; aux.DE*=(1.0+pf*sh3); break; }
						case 52: { double sar=pa*(sin(pfreq*zx)*sin(pfreq*zy)*sin(pfreq*zz2)>0.0?1.0:-1.0)*pb; aux.DE*=(1.0+pf*sar/fmax(1e-10,r)); break; }
						case 53: { double sml=pa*tanh(pb*zx)*tanh(pb*zy); aux.DE*=(1.0+pf*sml); break; }
						case 54: { double ano=pa*fabs(fmod(pb*zx+pc*zy,1.0)-0.5)*4.0; aux.DE*=(1.0+pf*ano/fmax(1e-10,r)); break; }
						case 55: { double axa=pa*exp(-pb*r)*cos(pfreq*r+pph); aux.DE*=(1.0+pf*axa); break; }
						case 56: { double srb=pa*pb*exp(-pc*rr)/fmax(1e-10,r); aux.DE*=(1.0+pf*srb); break; }
						case 57: { double pes=0.0; {double lya=pa*log(fmax(1e-10,r)); pes=lya*pb;} aux.DE*=(1.0+pf*tanh(pes)); break; }
						case 58: { double ly=pa*pb*log(fmax(1e-10,r))/fmax(1e-10,r); aux.DE*=(1.0+pf*tanh(ly)); break; }
						case 59: { double yt=pa*exp(-pb*r)*sin(pfreq*r+pph); aux.DE*=(1.0+pf*yt); break; }
						case 60: { double to=pa*pb*sin(pfreq*zx)*sin(pfreq*zy)/(fmax(1e-10,rr)); aux.DE*=(1.0+pf*to); break; }
						case 61: { double rpf=pa*exp(-pb*r)/fmax(1e-10,r); aux.DE*=(1.0+pf*rpf); break; }
						case 62: { double thf=pa*tanh(pb*(r-pc))*pd; aux.DE*=(1.0+pf*thf); break; }
						case 63: { double gib=pa*exp(-pb*rr)*pc; aux.DE*=(1.0+pf*gib); break; }
						case 64: { double eqs=pa*cos(pfreq*r+pph)/(fmax(1e-10,r)); aux.DE*=(1.0+pf*eqs); break; }
						case 65: { double pht=pa*(1.0/(1.0+exp(-pb*(r-pc)))-0.5)*2.0; aux.DE*=(1.0+pf*pht); break; }
						case 66: { double brf=pa*exp(-pb*r)*cos(pfreq*atan2(zy,zx)+pph); aux.DE*=(1.0+pf*brf); break; }
						case 67: { double spc=pa*sin(pfreq*zx)*cos(pfreq*zy)*sin(pfreq*zz2)*pb; aux.DE*=(1.0+pf*spc/fmax(1e-10,r)); break; }
						case 68: { double sha=pa*exp(-pb*fabs(r-pc)); aux.DE*=(1.0+pf*sha); break; }
						case 69: { double sst=pa*cos(pfreq*r+pph)*exp(-pb*r); aux.DE*=(1.0+pf*sst); break; }
						case 70: { double oms=pa*sin(pfreq*zx)*sin(pfreq*zy)*pb/fmax(1e-10,rr); aux.DE*=(1.0+pf*oms); break; }
						case 71: { double mss=pa*exp(-pb*r)*(1.0-cos(pfreq*r)); aux.DE*=(1.0+pf*mss); break; }
						case 72: { double gfl=-pa*pb*(zx+zy+zz2)/fmax(1e-10,r*r); aux.DE*=(1.0+pf*tanh(gfl)); break; }
						case 73: { double mor=pa*(r-pb)*(r-pb)*exp(-pc*r); aux.DE*=(1.0+pf*mor/fmax(1e-10,r)); break; }
						case 74: { double moh=pa*exp(-pb*rr)*sin(pfreq*r+pph); aux.DE*=(1.0+pf*moh); break; }
						case 75: { double flo=pa*sin(pfreq*zx)*cos(pfreq*zy)*pb; aux.DE*=(1.0+pf*flo/fmax(1e-10,r)); break; }
						case 76: { double sca=pa*pb*r*r/(fmax(1e-10,r*r+pc*pc)); aux.DE*=(1.0+pf*sca); break; }
						case 77: { double hof=pa*pb/fmax(1e-10,r); aux.DE*=(1.0+pf*tanh(hof)); break; }
						case 78: { double hz=pa*M_PI*pb/(2.0*fmax(1e-10,r)); aux.DE*=(1.0+pf*tanh(hz)); break; }
						case 79: { double ekh=pa*sin(pfreq*r+pph)*pb/fmax(1e-10,r); aux.DE*=(1.0+pf*ekh); break; }
						case 80: { double nsq=pa*pb*(1.0-r/fmax(1e-10,pc)); aux.DE*=(1.0+pf*tanh(nsq)); break; }
						case 81: { double emb=pa*pb*sin(pfreq*r+pph)/fmax(1e-10,rr); aux.DE*=(1.0+pf*emb); break; }
						case 82: { double echc=pa*sin(pfreq*zx)*cos(pfreq*zy)*pb/fmax(1e-10,r); aux.DE*=(1.0+pf*echc); break; }
						case 83: { double fib=pa*sin(pfreq*r)*cos(1.618033988749*pfreq*r+pph)/fmax(1e-10,r); aux.DE*=(1.0+pf*fib); break; }
						case 84: { double hut=pa*pb*sin(pfreq*atan2(zy,zx)+pph)/fmax(1e-10,r); aux.DE*=(1.0+pf*hut); break; }
						case 85: { double cmk=pa*cos(pfreq*r)*exp(-pb*r)*pc; aux.DE*=(1.0+pf*cmk); break; }
						case 86: { double vfc=pa*pb*sin(pfreq*r+pph)/(fmax(1e-10,r*r)); aux.DE*=(1.0+pf*vfc); break; }
						case 87: { double pol=pa*exp(-pb*rr)*cos(pfreq*r)*pc; aux.DE*=(1.0+pf*pol); break; }
						case 88: { double scc=pa*tanh(pb*r)*cos(pfreq*r+pph)/fmax(1e-10,r); aux.DE*=(1.0+pf*scc); break; }
						case 89: { double gwi=pa*pb*sin(pfreq*zx)*sin(pfreq*zy)*sin(pfreq*zz2)/(fmax(1e-10,rr)); aux.DE*=(1.0+pf*gwi); break; }
						case 90: { double qco=pa*cos(pfreq*(zx+zy+zz2)+pph)*pb/fmax(1e-10,r); aux.DE*=(1.0+pf*qco); break; }
						case 91: { double msy=pa*(sin(pfreq*zx)*sin(pfreq*zy)-cos(pfreq*zz2))/fmax(1e-10,r); aux.DE*=(1.0+pf*msy); break; }
						case 92: { double hv=pa*exp(-pb*rr)*sin(pfreq*r+pph); aux.DE*=(1.0+pf*hv); break; }
						case 93: { double bat=pa*cos(pfreq*zx+pph)*cos(pfreq*zy)*cos(pfreq*zz2)/fmax(1e-10,r); aux.DE*=(1.0+pf*bat); break; }
						case 94: { double gpo=pa*pb*sin(pfreq*r)/(fmax(1e-10,r*r)); aux.DE*=(1.0+pf*gpo); break; }
						case 95: { double syzf=pa*sin(pfreq*r)*sin(pfreq*atan2(zy,zx)+pph)*pb; aux.DE*=(1.0+pf*syzf/fmax(1e-10,r)); break; }
						case 96: { double gs=pa*exp(-pb*fabs(zz2))*cos(pfreq*sqrt(fmax(0.0,zx*zx+zy*zy))+pph); aux.DE*=(1.0+pf*gs); break; }
						case 97: { double scd=pa*pb*tanh(pc*sin(pfreq*r+pph)); aux.DE*=(1.0+pf*scd/fmax(1e-10,r)); break; }
						case 98: { double thf2=pa*sin(pfreq*zx+pph)*cos(pfreq*zy)*pb; aux.DE*=(1.0+pf*thf2/fmax(1e-10,r)); break; }
						case 99: { double cla=pa*pb*(zx*zy+zy*zz2+zz2*zx)/(fmax(1e-10,rr*r)); aux.DE*=(1.0+pf*cla); break; }
						case 100: { double clv=pa*sin(pfreq*(zx*zy+zy*zz2)/fmax(1e-10,rr)+pph)*pb; aux.DE*=(1.0+pf*clv); break; }
					}
				}

				// v7.8 — Mandelbox Math system (per-section iteration range)
				if (i >= mut.mbIterStart && i < mut.mbIterStop && mut.mbMathType != 0)
				{
					double mf = mut.mbFactor;
					double ma = mut.mbParamA, mb = mut.mbParamB, mc = mut.mbParamC, md = mut.mbParamD;
					double me = mut.mbParamE, mff = mut.mbParamF, mg = mut.mbParamG, mh = mut.mbParamH;
					double zx = z.x, zy = z.y, zz2 = z.z;
					double rr = zx*zx + zy*zy + zz2*zz2; if (rr < 1e-21) rr = 1e-21;
					double r = sqrt(rr);
					switch (mut.mbMathType)
					{
						case 1: { if(zx>ma) z.x=mb*2.0-zx; if(zx<-ma) z.x=-mb*2.0-zx; if(zy>ma) z.y=mb*2.0-zy; if(zy<-ma) z.y=-mb*2.0-zy; if(zz2>ma) z.z=mb*2.0-zz2; if(zz2<-ma) z.z=-mb*2.0-zz2; aux.DE*=fabs(mf); break; }
						case 2: { double lim=ma*(1.0+0.1*sin(i*mc)); if(fabs(zx)>lim) z.x=copysign(mb*2.0,zx)-zx; if(fabs(zy)>lim) z.y=copysign(mb*2.0,zy)-zy; if(fabs(zz2)>lim) z.z=copysign(mb*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
						case 3: { double sx=ma,sy=mb,sz=mc; double fx=1.0/(1.0+exp(-sx*(fabs(zx)-md))); double fy=1.0/(1.0+exp(-sy*(fabs(zy)-md))); double fz=1.0/(1.0+exp(-sz*(fabs(zz2)-md))); z.x=zx*(1.0-fx)+copysign(me*2.0-fabs(zx),zx)*fx; z.y=zy*(1.0-fy)+copysign(me*2.0-fabs(zy),zy)*fy; z.z=zz2*(1.0-fz)+copysign(me*2.0-fabs(zz2),zz2)*fz; aux.DE*=fabs(mf); break; }
						case 4: { double l1=ma,v1=mb,l2=mc,v2=md; if(fabs(zx)>l1) z.x=copysign(v1*2.0,zx)-zx; if(fabs(zx)>l2) z.x=copysign(v2*2.0,zx)-zx; if(fabs(zy)>l1) z.y=copysign(v1*2.0,zy)-zy; if(fabs(zy)>l2) z.y=copysign(v2*2.0,zy)-zy; if(fabs(zz2)>l1) z.z=copysign(v1*2.0,zz2)-zz2; if(fabs(zz2)>l2) z.z=copysign(v2*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
						case 5: { double rxy=sqrt(zx*zx+zy*zy); if(rxy>ma){ double th=atan2(zy,zx); double nr=ma*2.0-rxy; z.x=nr*cos(th); z.y=nr*sin(th); } aux.DE*=fabs(mf); break; }
						case 6: { double rxy=sqrt(zx*zx+zy*zy); double ea=(zx/(ma+1e-21))*(zx/(ma+1e-21))+(zy/(mb+1e-21))*(zy/(mb+1e-21)); if(ea>1.0){ double sc=1.0/sqrt(ea); z.x*=sc; z.y*=sc; } aux.DE*=fabs(mf); break; }
						case 7: { if(fabs(zx)+fabs(zy)>ma){ double sx=(zx>0)?1.0:-1.0,sy=(zy>0)?1.0:-1.0; double nx=ma*0.5*sx,ny=ma*0.5*sy; z.x=2.0*nx-zx; z.y=2.0*ny-zy; } aux.DE*=fabs(mf)*1.41421356; break; }
						case 8: { double ax=fabs(zx),ay=fabs(zy); double hx=fmax(ax,ay*0.8660254+ax*0.5); if(hx>ma){ z.x=copysign(ma*2.0-ax,zx); z.y=copysign(ma*2.0-ay,zy); } aux.DE*=fabs(mf); break; }
						case 9: { double ax=fabs(zx),ay=fabs(zy); double ox=fmax(ax,fmax(ay,(ax+ay)*0.7071068)); if(ox>ma){ z.x=copysign(ma*2.0-ax,zx); z.y=copysign(ma*2.0-ay,zy); } aux.DE*=fabs(mf); break; }
						case 10: { double th=atan2(zy,zx); double rxy=sqrt(zx*zx+zy*zy); double rlim=ma*(1.0+mb*cos(mc*th)); if(rxy>rlim){ double nr=rlim*2.0-rxy; z.x=nr*cos(th); z.y=nr*sin(th); } aux.DE*=fabs(mf); break; }
						case 11: { double th=atan2(zy,zx); double rxy=sqrt(zx*zx+zy*zy); double rlim=ma*exp(-mb*th); if(rxy>rlim){ double nr=rlim*2.0-rxy; z.x=nr*cos(th); z.y=nr*sin(th); } aux.DE*=fabs(mf); break; }
						case 12: { double limy=ma+mb*sin(mc*zy); if(fabs(zx)>limy) z.x=copysign(limy*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; aux.DE*=fabs(mf)*(1.0+fabs(mb*mc)); break; }
						case 13: { double h1=ma+mb*sin(mc*zx)*sin(mc*zy)*sin(mc*zz2); if(fabs(zx)>h1) z.x=copysign(h1*2.0,zx)-zx; if(fabs(zy)>h1) z.y=copysign(h1*2.0,zy)-zy; if(fabs(zz2)>h1) z.z=copysign(h1*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
						case 14: { double h1=ma+mb*sin(mc*zx)*cos(md*zy); if(fabs(zx)>h1) z.x=copysign(h1*2.0,zx)-zx; if(fabs(zy)>h1) z.y=copysign(h1*2.0,zy)-zy; if(fabs(zz2)>h1) z.z=copysign(h1*2.0,zz2)-zz2; aux.DE*=fabs(mf)*(1.0+fabs(mb*mc)); break; }
						case 15: { double jv=ma+0.1*sin(mc*zx)*sin(mc*zy); if(fabs(zx)>jv) z.x=copysign(jv*2.0,zx)-zx; if(fabs(zy)>jv) z.y=copysign(jv*2.0,zy)-zy; aux.DE*=fabs(mf); break; }
						case 16: { double lt=ma+0.1*sin(mb*i); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
						case 17: { double lt=ma*(1.0+0.1*r); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
						case 18: { double cl=fabs(in.point.Length()); double lt=ma+cl*mb; if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
						case 19: { double c1=ma,c2=-ma; if(zx>c1+mb) z.x=2.0*c1+mb*2.0-zx; if(zx<c2-mb) z.x=2.0*c2-mb*2.0-zx; if(zy>c1+mb) z.y=2.0*c1+mb*2.0-zy; if(zy<c2-mb) z.y=2.0*c2-mb*2.0-zy; aux.DE*=fabs(mf); break; }
						case 20: { double lt=ma; for(int n=0;n<3&&n<(int)mb;n++){ lt*=0.5; if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; } aux.DE*=fabs(mf); break; }
						case 21: { if(i>(int)mb){ if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; } aux.DE*=fabs(mf); break; }
						case 22: { double h=((sin(i*12.9898+zx*78.233)*43758.5453) - floor(sin(i*12.9898+zx*78.233)*43758.5453)); if(h<mc){ if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; } aux.DE*=fabs(mf)*(1.0-mc+mc*mb); break; }
						case 23: { double dt=zx*mc+zy*md+zz2*me; double lt=ma*(1.0+0.1*dt/fmax(1e-10,r)); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
						case 24: { double lt=ma+mc*zx*zx; if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; double lty=ma+mc*zy*zy; if(fabs(zy)>lty) z.y=copysign(lty*2.0,zy)-zy; aux.DE*=fabs(mf)*(1.0+2.0*fabs(mc*r)); break; }
						case 25: { double lt=ma+mb*sin(mc*zx); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; double lty=ma+mb*sin(mc*zy); if(fabs(zy)>lty) z.y=copysign(lty*2.0,zy)-zy; double ltz=ma+mb*sin(mc*zz2); if(fabs(zz2)>ltz) z.z=copysign(ltz*2.0,zz2)-zz2; aux.DE*=fabs(mf)*(1.0+fabs(mb*mc)); break; }
						case 26: { double rre=(zx/(ma+1e-10))*(zx/(ma+1e-10))+(zy/(mb+1e-10))*(zy/(mb+1e-10))+(zz2/(mc+1e-10))*(zz2/(mc+1e-10)); if(rre<1e-21) rre=1e-21; double m2=md*md/rre; z*=m2; aux.DE*=m2; break; }
						case 27: { double rrc=zx*zx+zy*zy; if(rrc<1e-21) rrc=1e-21; double m2=ma*ma/rrc; z.x*=m2; z.y*=m2; z.z*=m2; aux.DE*=m2; break; }
						case 28: { double rxy=sqrt(zx*zx+zy*zy); double rrt=(rxy-ma)*(rxy-ma)+zz2*zz2; if(rrt<1e-21) rrt=1e-21; double m2=mb*mb/rrt; z*=m2; aux.DE*=m2; break; }
						case 29: { double rrh=zx*zx+zy*zy-zz2*zz2; double ar=fabs(rrh); if(ar<1e-21) ar=1e-21; double m2=ma*ma/ar; z*=m2; aux.DE*=m2*fmax(1.0,fabs(zz2)); break; }
						case 30: { double rrp=zx*zx+zy*zy-ma*zz2; double ar=fabs(rrp); if(ar<1e-21) ar=1e-21; double m2=mb*mb/ar; z*=m2; aux.DE*=m2*sqrt(1.0+4.0*ma*ma); break; }
						case 31: { double mR2=ma*(1.0+0.1*sin(i*mc)); double fR2=mb; if(rr<mR2) z*=fR2/mR2; else if(rr<fR2) z*=fR2/rr; aux.DE*=fabs(mf)*fR2/fmax(1e-21,fmin(rr,mR2)); break; }
						case 32: { double mx=ma,my=mb,mz=mc; double rrm=fmax(zx*zx/fmax(1e-21,mx),fmax(zy*zy/fmax(1e-21,my),zz2*zz2/fmax(1e-21,mz))); double fR2=md; if(rrm<fR2){ double m2=fR2/fmax(1e-21,rrm); z*=m2; aux.DE*=m2; } break; }
						case 33: { double mR2_1=ma,f1=mb,mR2_2=mc,f2=md; if(rr<mR2_1){ z*=f1; aux.DE*=f1; } double rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mR2_2){ z*=f2; aux.DE*=f2; } break; }
						case 34: { double sm=mc; double mR2=ma,fR2=mb; double t=1.0/(1.0+exp(-sm*(rr-mR2))); double m2=fR2/fmax(1e-21,rr); double sf=(1.0-t)*m2+t*1.0; z*=sf; aux.DE*=sf; break; }
						case 35: { double fR2=mb; double lg=log(fmax(1e-21,fR2))/log(fmax(1e-21,rr)); z*=lg; aux.DE*=lg/(rr*log(fmax(1e-21,rr))); break; }
						case 36: { double fR2=mb; double ex=exp(fR2-rr); z*=ex; aux.DE*=ex; break; }
						case 37: { double fR2=mb; double pw=mc; double m2=pow(fmax(1e-21,fR2/rr),pw); z*=m2; aux.DE*=m2; break; }
						case 38: { double k=mc,fR2=mb; double sg=1.0/(1.0+exp(k*(rr-fR2))); z*=sg; aux.DE*=sg; break; }
						case 39: { double fR2=mb,sg=mc; double gs=exp(-(rr-fR2)*(rr-fR2)/(sg*sg+1e-21)); z*=gs; aux.DE*=gs; break; }
						case 40: { double mR2=ma,fR2=mb,f1=mc; double m2=(rr<mR2)?f1:((rr<fR2)?fR2/rr:1.0); z*=m2; aux.DE*=m2; break; }
						case 41: { double b1=ma,f1=mb,b2=mc,f2=md,b3=me,f3=mff; double m2=(rr<b1)?f1:((rr<b2)?f2:((rr<b3)?f3:1.0)); z*=m2; aux.DE*=m2; break; }
						case 42: { double fR2=mb; if(rr<fR2){ double m2=1.0/fmax(1e-21,rr); z.x=ma+fR2*(zx-ma)*m2; z.y=ma+fR2*(zy-ma)*m2; z.z=ma+fR2*(zz2-ma)*m2; aux.DE*=fR2*m2; } break; }
						case 43: { double fR2=mb; if(rr<fR2){ double den=mc*zx+md+1e-21; z.x=(ma*zx+mb)/(den); z.y=zy/fmax(1e-10,fabs(den)); z.z=zz2/fmax(1e-10,fabs(den)); aux.DE*=fabs(ma*md-mb*mc)/(den*den); } break; }
						case 44: { double fR2=mb; if(rr<fR2){ double qn=rr; if(qn<1e-21) qn=1e-21; double m2=fR2/qn; z*=m2; aux.DE*=m2; } break; }
						case 45: { double dm=fmax(1e-10,acosh(fmax(1.0,r))); double dmax=ma; if(dm<dmax){ double sc=dmax/dm; z*=sc; aux.DE*=sc*dmax/(dm*sinh(dm)+1e-21); } break; }
						case 46: { double ox=ma,oy=mb,oz=mc; double rrc=(zx-ox)*(zx-ox)+(zy-oy)*(zy-oy)+(zz2-oz)*(zz2-oz); if(rrc<1e-21) rrc=1e-21; double fR2=md; if(rrc<fR2){ double m2=fR2/rrc; z*=m2; aux.DE*=m2; } break; }
						case 47: { double th=ma*M_PI/180.0; double cs=cos(th),sn=sin(th); double rx=zx*cs-zy*sn; double ry=zx*sn+zy*cs; double rrc=rx*rx+ry*ry+zz2*zz2; if(rrc<1e-21) rrc=1e-21; double fR2=mb; if(rrc<fR2){ double m2=fR2/rrc; z*=m2; aux.DE*=m2; } break; }
						case 48: { double fR2=ma*(1.0+0.1*sin(i*mb)); double mR2=mc; if(rr<mR2){ z*=fR2/mR2; aux.DE*=fR2/mR2; } else if(rr<fR2){ z*=fR2/rr; aux.DE*=fR2/rr; } break; }
						case 49: { double mR2=ma,fR2=mb; double cf=(rr<mR2)?mc:((rr<fR2)?md:0.0); aux.color+=cf; break; }
						case 50: { aux.color+=log(fmax(1e-21,aux.DE))*ma; break; }
						case 51: { z.x*=ma; z.y*=mb; z.z*=mc; aux.DE*=fmax(fabs(ma),fmax(fabs(mb),fabs(mc))); break; }
						case 52: { double sc=ma+mb*sin(i*mc); z*=sc; aux.DE*=fabs(sc); break; }
						case 53: { double sc=ma*exp(-i*mb); z*=sc; aux.DE*=fabs(sc); break; }
						case 54: { double sc=ma/(1.0+log(1.0+i)); z*=sc; aux.DE*=fabs(sc); break; }
						case 55: { double p=fmax(0.01,mb); double sc=ma/fmax(1e-10,pow(fmax(1.0,(double)i),p)); z*=sc; aux.DE*=fabs(sc); break; }
						case 56: { double f0=1,f1=1; for(int n=0;n<fmin((double)i,20.0);n++){double t=f1;f1=f0+f1;f0=t;} double sc=ma/fmax(1.0,f1); z*=sc; aux.DE*=fabs(sc); break; }
						case 57: { double ns=sin(i*12.9898+zx*78.233)*43758.5453; ns=ns-floor(ns); double sc=ma+ns*mb; z*=sc; aux.DE*=fabs(sc); break; }
						case 58: { double jv=sin(i*mb)*cos(i*mc); double sc=ma+0.1*fabs(jv); z*=sc; aux.DE*=fabs(sc); break; }
						case 59: { double sc=ma*(1.0+0.1*r); z*=sc; aux.DE*=fabs(sc)*(1.0+0.1*r); break; }
						case 60: { double sc=ma+0.1*sin(i*mb); z*=sc; aux.DE*=fabs(sc); break; }
						case 61: { double sc=ma+0.1*mf; z*=sc; aux.DE*=fabs(sc)*1.1; break; }
						case 62: { double sc=(zx>0)?ma:mb; z*=sc; aux.DE*=fmax(fabs(ma),fabs(mb)); break; }
						case 63: { double th=atan2(zy,zx); double sc=ma+mb*cos(mc*th); z*=sc; aux.DE*=fabs(sc); break; }
						case 64: { double th=atan2(sqrt(zx*zx+zy*zy),zz2); double ph=atan2(zy,zx); double sc=ma+mb*cos(mc*th)*sin(md*ph); z*=sc; aux.DE*=fabs(sc); break; }
						case 65: { double off=ma+0.1*sin(i*mb); z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf); break; }
						case 66: { z.x+=ma; z.y+=mb; z.z+=mc; aux.DE*=fabs(mf); break; }
						case 67: { double cl=in.point.Length(); z.x+=cl*ma; z.y+=cl*ma; z.z+=cl*ma; aux.DE*=fabs(mf); break; }
						case 68: { z.x+=zx*0.1*ma; z.y+=zy*0.1*ma; z.z+=zz2*0.1*ma; aux.DE*=fabs(mf); break; }
						case 69: { double ns=sin(zx*ma+zy*mb+zz2*mc)*md; z.x+=ns; z.y+=ns; z.z+=ns; aux.DE*=fabs(mf); break; }
						case 70: { double off=ma+0.1*sin(i*mb); z.x+=off; z.y+=off*0.5; z.z+=off*0.25; aux.DE*=fabs(mf); break; }
						case 71: { double off=ma+0.1*mf; z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf); break; }
						case 72: { double off=(rr<ma)?mb:mc; z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf); break; }
						case 73: { double off=ma*(1.0+0.1*r); z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf); break; }
						case 74: { double th=i*ma; double spr=mb; z.x+=spr*cos(th); z.y+=spr*sin(th); aux.DE*=fabs(mf); break; }
						case 75: { z.x+=ma*sin(mb*i); z.y+=mc*sin(md*i); z.z+=me*sin(mff*i); aux.DE*=fabs(mf); break; }
						case 76: { double ga=2.39996322973; double th=i*ga; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx; z.y=ny; aux.DE*=fabs(mf); break; }
						case 77: { double hth=ma*M_PI/360.0; double ax=mb,ay=mc,az=md; double nm=sqrt(ax*ax+ay*ay+az*az+1e-21); ax/=nm;ay/=nm;az/=nm; double cq=cos(hth),sq=sin(hth); double qw=cq,qx=sq*ax,qy=sq*ay,qz=sq*az; double nx=zx*(1-2*(qy*qy+qz*qz))+zy*2*(qx*qy-qw*qz)+zz2*2*(qx*qz+qw*qy); double ny=zx*2*(qx*qy+qw*qz)+zy*(1-2*(qx*qx+qz*qz))+zz2*2*(qy*qz-qw*qx); double nz=zx*2*(qx*qz-qw*qy)+zy*2*(qy*qz+qw*qx)+zz2*(1-2*(qx*qx+qy*qy)); z.x=nx;z.y=ny;z.z=nz; aux.DE*=fabs(mf); break; }
						case 78: { double th=ma*M_PI/180.0; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx; z.y=ny; double ph=mb*M_PI/180.0; double cp=cos(ph),sp=sin(ph); double nxz=z.x*cp-zz2*sp; double nz=z.x*sp+zz2*cp; z.x=nxz; z.z=nz; aux.DE*=fabs(mf); break; }
						case 79: { double th=ma*M_PI/180.0; double cs=cos(th),sn=sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; double ph=mb*M_PI/180.0; cs=cos(ph); sn=sin(ph); double ty=z.y*cs-zz2*sn; z.z=z.y*sn+zz2*cs; z.y=ty; double ps=mc*M_PI/180.0; cs=cos(ps);sn=sin(ps); double tx=z.x*cs-z.z*sn; z.z=z.x*sn+z.z*cs; z.x=tx; aux.DE*=fabs(mf); break; }
						case 80: { double v=ma; double gm=1.0/sqrt(fmax(1e-10,1.0-v*v)); z.x=gm*(zx-v*zz2); z.z=gm*(zz2-v*zx); aux.DE*=fabs(mf)*gm; break; }
						case 81: { z.x+=ma; z.y+=mb*sin(mc*zz2); aux.DE*=fabs(mf); break; }
						case 82: { double s=ma; double th=mb*M_PI/180.0; double cs=cos(th),sn=sin(th); z.x=s*(zx*cs-zy*sn); z.y=s*(zx*sn+zy*cs); z.z*=s; aux.DE*=fabs(s)*fabs(mf); break; }
						case 83: { double N=fmax(2.0,ma); double th=2.0*M_PI/N; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx; z.y=ny; aux.DE*=fabs(mf); break; }
						case 84: { double ax=sin(i*ma),ay=cos(i*ma); double nm=sqrt(ax*ax+ay*ay+1e-21); ax/=nm; ay/=nm; double th=mb*M_PI/180.0; double cs=cos(th),sn=sin(th); double d=zx*ax+zy*ay; double px=zx-d*ax,py=zy-d*ay; double rx=px*cs-py*sn+d*ax,ry=px*sn+py*cs+d*ay; z.x=rx;z.y=ry; aux.DE*=fabs(mf); break; }
						case 85: { double ns=sin(i*12.9898+78.233)*43758.5453; ns=ns-floor(ns); double th=ns*2.0*M_PI*ma; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
						case 86: { double th=ma+mb*i; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
						case 87: { double th=ma+mf; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
						case 88: { if(zx>0){ double th=ma*M_PI/180.0; double cs=cos(th),sn=sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; } else { double th=mb*M_PI/180.0; double cs=cos(th),sn=sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; } aux.DE*=fabs(mf); break; }
						case 89: { double th=ma*(1.0+0.1*r); double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
						case 90: { double ph=atan2(zy,zx); double th=ma+mb*cos(mc*ph); double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
						case 91: { double N=fmax(2.0,ma); double th=atan2(zy,zx); double sector=2.0*M_PI/N; th=fmod(th+sector*0.5+100.0*sector,sector)-sector*0.5; double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(th); z.y=rxy*sin(th); aux.DE*=fabs(mf); break; }
						case 92: { double nx=fabs(zx); double ny=fabs(zy); double nz2=fabs(zz2); if(ma>0) z.x=nx; if(mb>0) z.y=ny; if(mc>0) z.z=nz2; aux.DE*=fabs(mf); break; }
						case 93: { z.x+=ma*zy; z.y+=mb*zz2; aux.DE*=fabs(mf)*sqrt(1.0+ma*ma+mb*mb); break; }
						case 94: { double rxy=sqrt(zx*zx+zy*zy); double th=atan2(zy,zx)+ma*zz2; z.x=rxy*cos(th); z.y=rxy*sin(th); aux.DE*=fabs(mf)*sqrt(1.0+ma*ma*rxy*rxy); break; }
						case 95: { double cv=ma; double rxy=sqrt(zx*zx+zy*zy); double th=atan2(zy,zx)+cv*rxy; z.x=rxy*cos(th); z.y=rxy*sin(th); aux.DE*=fabs(mf)*(1.0+cv*rxy); break; }
						case 96: { double tf=ma; z.x*=(1.0-tf*zz2); z.y*=(1.0-tf*zz2); aux.DE*=fabs(mf)*(1.0-tf*zz2); break; }
						case 97: { double g=ma; double th=atan2(zy,zx)+g*log(fmax(1e-10,sqrt(zx*zx+zy*zy))); double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(th); z.y=rxy*sin(th); aux.DE*=fabs(mf)*g; break; }
						case 98: { double th=ma*exp(i*mb); double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
						case 99: { double th=ma*log(1.0+i); double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
						case 100: { double p=mb; double th=ma*pow(fmax(1.0,(double)i),p); double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf); break; }
						case 101: { double w=ma; double rr4=rr+w*w; if(rr4<1e-21) rr4=1e-21; double sc=mf; z.x=zx*sc+w*0.1; z.y=zy*sc; z.z=zz2*sc; aux.DE*=fabs(sc); break; }
						case 102: { double w=ma,v=mb; double rr5=rr+w*w+v*v; if(rr5<1e-21) rr5=1e-21; double sc=mf; z*=sc; z.x+=w*0.05; z.y+=v*0.05; aux.DE*=fabs(sc); break; }
						case 103: { double w=ma*sin(mb*i); z.x+=w*0.1; aux.DE*=fabs(mf); break; }
						case 104: { double th4=ma*M_PI/180.0; double cs=cos(th4),sn=sin(th4); double nw=zz2*sn; z.z=zz2*cs; z.x+=nw*0.1; aux.DE*=fabs(mf); break; }
						case 105: { double cx=ma,cy=mb,cz=mc; (void)md; z.x+=cx*mf; z.y+=cy*mf; z.z+=cz*mf; aux.DE*=fabs(mf); break; }
						case 106: { double qw=ma,qx=zx,qy=zy,qz=zz2; double nm=sqrt(qw*qw+qx*qx+qy*qy+qz*qz+1e-21); z.x=qx/nm*mf; z.y=qy/nm*mf; z.z=qz/nm*mf; aux.DE*=fabs(mf)/nm; break; }
						case 107: { double q1w=ma,q2w=mb; double nm1=sqrt(zx*zx+zy*zy+q1w*q1w+1e-21); double nm2=sqrt(zz2*zz2+q2w*q2w+1e-21); z.x*=nm2/(nm1+1e-21); z.y*=nm2/(nm1+1e-21); aux.DE*=fabs(mf)*nm2/(nm1+1e-21); break; }
						case 108: { double d4=sqrt(rr+ma*ma); double td=tanh(d4); z*=td/fmax(1e-10,d4); double ch=cosh(d4); aux.DE*=fabs(mf)/(ch*ch+1e-21); break; }
						case 109: { double rr4=rr+ma*ma; double nm4=sqrt(rr4+1e-21); z*=1.0/nm4; aux.DE*=fabs(mf)/nm4; break; }
						case 110: { double rxy=sqrt(zx*zx+zy*zy+1e-21); z.x=(rxy-ma)*cos(atan2(zy,zx)); z.y=(rxy-ma)*sin(atan2(zy,zx)); aux.DE*=fabs(mf)*rxy; break; }
						case 111: { double R=ma,rr2=mb; double th=atan2(zy,zx); z.x=(R+rr2*cos(th))*cos(mc*i); z.y=(R+rr2*cos(th))*sin(mc*i); z.z=rr2*sin(th); aux.DE*=fabs(mf)*R; break; }
						case 112: { double th=ma*M_PI/180.0; double ph=mb*M_PI/180.0; double cs1=cos(th),sn1=sin(th),cs2=cos(ph); double nx=zx*cs1-zy*sn1; double ny=zx*sn1+zy*cs1; double nz2=zz2*cs2; z.x=nx;z.y=ny;z.z=nz2; aux.DE*=fabs(mf); break; }
						case 113: { double ga=2.39996322973; double th=i*ga; double r4=sqrt(rr+1e-21); z.x=r4*cos(th)*cos(ma*i); z.y=r4*sin(th)*cos(ma*i); z.z=r4*sin(ma*i); aux.DE*=fabs(mf); break; }
						case 114: { double D=ma; double sc=pow(2.0,D); z*=sc/fmax(1e-10,r); aux.DE*=sc/fmax(1e-10,r); break; }
						case 115: { double h=((sin(i*12.9898+78.233)*43758.5453) - floor(sin(i*12.9898+78.233)*43758.5453)); if(h<ma){ z.x=-z.x; z.y=-z.y; } aux.DE*=fabs(mf); break; }
						case 116: { double w=ma+0.1*sin(i*mb); z.x+=w*0.1; aux.DE*=fabs(mf); break; }
						case 117: { z.x+=0.1*zx*ma; z.y+=0.1*zy*ma; z.z+=0.1*zz2*ma; aux.DE*=fabs(mf)*1.1; break; }
						case 118: { double ns=sin(zx*ma+i*mb)*cos(zy*mc); z.x+=ns*0.1*md; z.y+=ns*0.1*md; aux.DE*=fabs(mf); break; }
						case 119: { double jv=sin(i*ma)*cos(i*mb); double sc=mf+0.1*jv; z*=sc; aux.DE*=fabs(sc); break; }
						case 120: { double sc1=ma,sc2=mb; z*=sc1; double rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2>1e-21){ z*=sc2/sqrt(rr2); } aux.DE*=fmax(fabs(sc1),fabs(sc2)); break; }
						case 121: { double h=((sin(i*12.9898+78.233)*43758.5453) - floor(sin(i*12.9898+78.233)*43758.5453)); double w=(h<ma)?mb:mc; z.x+=w*0.1; aux.DE*=fabs(mf); break; }
						case 122: { double h=((sin(i*12.9898+zx*78.233)*43758.5453) - floor(sin(i*12.9898+zx*78.233)*43758.5453)); double sc=ma+h*mb*0.1; z*=sc; aux.DE*=fabs(sc); break; }
						case 123: { double p=ma; z.x=fmod(zx+p*0.5,p)-p*0.5; z.y=fmod(zy+p*0.5,p)-p*0.5; z.z=fmod(zz2+p*0.5,p)-p*0.5; aux.DE*=fabs(mf)/fmax(0.01,p); break; }
						case 124: { double fR2=ma; if(rr<fR2){ double m2=fR2/fmax(1e-21,rr); z*=m2; aux.DE*=m2; } break; }
						case 125: { if(fabs(zx)>ma) z.x=copysign(ma,zx); if(fabs(zy)>ma) z.y=copysign(ma,zy); if(fabs(zz2)>ma) z.z=copysign(ma,zz2); aux.DE*=fabs(mf); break; }
						case 126: { double dx=fabs(z.x-zx),dy=fabs(z.y-zy),dz=fabs(z.z-zz2); aux.color+=ma*dx+mb*dy+mc*dz; break; }
						case 127: { double mR2=ma,fR2=mb; double t=(rr-mR2)/(fR2-mR2+1e-21); t=fmax(0.0,fmin(1.0,t)); aux.color+=t*mc; break; }
						case 128: { aux.color+=log(fabs(mf)+1e-21)*ma; break; }
						case 129: { double th=atan2(zy,zx); aux.color+=fabs(th)*ma; break; }
						case 130: { double td=sqrt((zx-ma)*(zx-ma)+(zy-mb)*(zy-mb)+(zz2-mc)*(zz2-mc))-md; aux.color+=fmax(0.0,1.0-fabs(td))*me; break; }
						case 131: { double ax1=ma,ay1=mb,bx1=mc,by1=md; double dx=bx1-ax1,dy=by1-ay1; double t=((zx-ax1)*dx+(zy-ay1)*dy)/(dx*dx+dy*dy+1e-21); t=fmax(0.0,fmin(1.0,t)); double px=ax1+t*dx,py=ay1+t*dy; double dd=sqrt((zx-px)*(zx-px)+(zy-py)*(zy-py)); aux.color+=fmax(0.0,1.0-dd)*me; break; }
						case 132: { double dd=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.color+=fmax(0.0,1.0-dd*ma)*mb; break; }
						case 133: { double nx=ma,ny=mb,nz2=mc; double nm=sqrt(nx*nx+ny*ny+nz2*nz2+1e-21); double dd=fabs(zx*nx/nm+zy*ny/nm+zz2*nz2/nm-md); aux.color+=fmax(0.0,1.0-dd)*me; break; }
						case 134: { double R=ma,rr2=mb; double rxy=sqrt(zx*zx+zy*zy+1e-21); double td=(rxy-R)*(rxy-R)+zz2*zz2-rr2*rr2; aux.color+=fmax(0.0,1.0-fabs(td))*mc; break; }
						case 135: { double jv=sin(zx*ma)*sin(zy*mb); aux.color+=fabs(jv)*mc; break; }
						case 136: { aux.color+=(double)i/fmax(1.0,ma)*mb; break; }
						case 137: { aux.color+=log(fmax(1e-21,aux.DE))*ma; break; }
						case 138: { double spd=sqrt((z.x-zx)*(z.x-zx)+(z.y-zy)*(z.y-zy)+(z.z-zz2)*(z.z-zz2)); aux.color+=spd*ma; break; }
						case 139: { aux.color+=r*ma*0.01; break; }
						case 140: { double th=atan2(zy,zx); aux.color+=th*ma; break; }
						case 141: { aux.color+=r*ma; break; }
						case 142: { double p=fmax(0.01,ma); double cx2=floor(zx/p),cy2=floor(zy/p),cz2=floor(zz2/p); double h=((sin(cx2*12.9898+cy2*78.233+cz2*37.719)*43758.5453) - floor(sin(cx2*12.9898+cy2*78.233+cz2*37.719)*43758.5453)); aux.color+=h*mb; break; }
						case 143: { aux.color+=sin(i*ma+mb)*mc; break; }
						case 144: { aux.color=0.9*aux.color+0.1*ma*r; break; }
						case 145: { double ns=sin(zx*ma+zy*mb+zz2*mc)*md; aux.color+=ns; break; }
						case 146: { double cl=in.point.Length(); aux.color+=cl*ma; break; }
						case 147: { aux.color+=sqrt(zx*zx+zy*zy)*ma; break; }
						case 148: { double fc=fabs(z.x-zx)*0.3+r*0.3+fabs(atan2(zy,zx))*0.4; aux.color+=fc*ma; break; }
						case 149: { double ns=sin(zx*ma+zy*mb)*cos(zz2*mc+i*md); aux.color+=fabs(ns)*me; break; }
						case 150: { double jv=sin(zx*ma)*sin(zy*mb)*sin(zz2*mc); aux.color+=fabs(jv)*md; break; }
						case 151: { double eps=ma*0.001; double dx=(sqrt((zx+eps)*(zx+eps)+zy*zy+zz2*zz2)-sqrt((zx-eps)*(zx-eps)+zy*zy+zz2*zz2))/(2.0*eps); aux.DE=fmax(1e-21,fabs(dx)*aux.DE); break; }
						case 152: { double de_num=r*0.5; double de_safe=fmin(aux.DE,de_num); aux.DE=de_safe; break; }
						case 153: { aux.DE=0.9*aux.DE+0.1*r*ma; break; }
						case 154: { double prev=aux.DE; aux.DE=prev+0.5*(prev-ma); break; }
						case 155: { double spd=r*0.01; aux.DE=aux.DE*(1.0+0.5*spd); break; }
						case 156: { double tr=ma; aux.DE=fmin(aux.DE,tr); break; }
						case 157: { double j11=1.0+ma*cos(zx),j22=1.0+mb*cos(zy),j33=1.0+mc*cos(zz2); aux.DE*=fmax(fabs(j11),fmax(fabs(j22),fabs(j33))); break; }
						case 158: { double h=ma*sin(zx)*sin(zy)*sin(zz2); aux.DE*=(1.0+h*0.5); break; }
						case 159: { aux.DE=log(fmax(1e-21,aux.DE))*ma+mb; break; }
						case 160: { aux.DE=(exp(fmin(10.0,aux.DE))-1.0)*ma; break; }
						case 161: { double p=ma; aux.DE=pow(fmax(1e-21,aux.DE),p); break; }
						case 162: { double k=ma,de0=mb; aux.DE=1.0/(1.0+exp(-k*(aux.DE-de0))); break; }
						case 163: { double de0=ma,sg=mb; aux.DE=exp(-(aux.DE-de0)*(aux.DE-de0)/(sg*sg+1e-21)); break; }
						case 164: { double th2=ma; aux.DE=(aux.DE>th2)?mb:mc; break; }
						case 165: { double b1=ma,d1=mb,b2=mc,d2=md; aux.DE=(aux.DE<b1)?d1:((aux.DE<b2)?d2:aux.DE); break; }
						case 166: { double ns=sin(zx*ma+zy*mb+zz2*mc)*md; aux.DE+=ns; aux.DE=fmax(1e-21,aux.DE); break; }
						case 167: { double jv=fabs(sin(zx*ma)*sin(zy*mb)); aux.DE*=(1.0+0.1*jv); break; }
						case 168: { aux.DE*=(1.0+0.1*sin(i*ma)); break; }
						case 169: { aux.DE=0.9*aux.DE+0.1*ma; break; }
						case 170: { double ns=sin(zx*ma+zy*mb)*cos(zz2*mc+i*md); aux.DE*=(1.0+me*ns); break; }
						case 171: { double fn=sin(zx*ma*10.0)*sin(zy*mb*10.0)*sin(zz2*mc*10.0); aux.DE*=(1.0+0.1*fn); break; }
						case 172: { double spd=r*0.01; aux.DE/=(1.0+spd); break; }
						case 173: { aux.DE*=fabs(mf); break; }
						case 174: { if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; double rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb*mb) z*=mc*mc/(rr2+1e-21); aux.DE*=fabs(mf); break; }
						case 175: { double sc=ma+mb*sin(i*mc); z*=sc; if(fabs(z.x)>md) z.x=copysign(md*2.0,z.x)-z.x; aux.DE*=fabs(sc); break; }
						case 176: { double th=ma*M_PI/180.0; double cs=cos(th),sn=sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; if(fabs(z.x)>mb) z.x=copysign(mb*2.0,z.x)-z.x; aux.DE*=fabs(mf); break; }
						case 177: { if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; double rr2=z.x*z.x+z.y*z.y+z.z*z.z; double fR2=mb; if(rr2<mc) z*=fR2/mc; else if(rr2<fR2) z*=fR2/rr2; z*=md; z.x+=me; z.y+=mff; z.z+=mg; aux.DE*=fabs(md); break; }
						case 178: { double th=i*2.39996322973; double cs=cos(th),sn=sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; if(fabs(z.x)>ma) z.x=copysign(ma*2.0,z.x)-z.x; z*=mb; aux.DE*=fabs(mb); break; }
						case 179: { double rxy=sqrt(zx*zx+zy*zy); if(rxy>ma){ double th=atan2(zy,zx); z.x=(ma*2.0-rxy)*cos(th); z.y=(ma*2.0-rxy)*sin(th); } double rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb) z*=mc/rr2; aux.DE*=fabs(mf); break; }
						case 180: { z.x+=ma*sin(mb*zy); z.y+=mc*sin(md*zz2); z.z+=me*sin(mff*zx); aux.DE*=fabs(mf)*(1.0+fabs(ma*mb)+fabs(mc*md)+fabs(me*mff)); break; }
						case 181: { if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; aux.color+=mb*fabs(z.x-zx); aux.DE*=fabs(mf); break; }
						case 182: { double rr2=rr; double mR2=ma*ma; double fR2=mb*mb; if(rr2<mR2){ z*=fR2/mR2; aux.DE*=fR2/mR2; } else if(rr2<fR2){ z*=fR2/rr2; aux.DE*=fR2/rr2; } aux.color+=mc*log(fmax(1e-21,rr2/(mR2+1e-21))); break; }
						case 183: { double sc=ma; z*=sc; aux.DE*=fabs(sc); z.x+=mb; z.y+=mc; z.z+=md; double th=me*M_PI/180.0; double cs=cos(th),sn=sin(th); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; break; }
						case 184: { double lt=ma*(1.0+mb*r/fmax(1e-10,sqrt(rr))); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; aux.DE*=fabs(mf); break; }
						case 185: { double mR2=ma*ma; double fR2=mb*mb; double sm=mc; double t=1.0/(1.0+exp(-sm*(rr-mR2))); double m2=fR2/fmax(1e-21,rr); double sf=(1.0-t)*m2+t; z*=sf; aux.DE*=sf; z*=md; z.x+=me; aux.DE*=fabs(md); break; }
						case 186: { double N=fmax(2.0,ma); double th=atan2(zy,zx); double sector=2.0*M_PI/N; th=fmod(th+sector*0.5+100.0*sector,sector)-sector*0.5; double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(th); z.y=rxy*sin(th); if(fabs(z.x)>mb) z.x=copysign(mb*2.0,z.x)-z.x; aux.DE*=fabs(mf); break; }
						case 187: { z.x=fabs(zx); z.y=fabs(zy); z.z=fabs(zz2); if(fabs(z.x)>ma) z.x=ma*2.0-z.x; if(fabs(z.y)>ma) z.y=ma*2.0-z.y; if(fabs(z.z)>ma) z.z=ma*2.0-z.z; aux.DE*=fabs(mf); break; }
						case 188: { if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; double rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb) z*=mc/rr2; else if(rr2<mc) z*=mc/rr2; double th=md*M_PI/180.0; double cs=cos(th),sn=sin(th); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; z*=me; z.x+=mff; aux.DE*=fabs(me); break; }
						case 189: { double rxy=sqrt(zx*zx+zy*zy); double th=atan2(zy,zx)+ma*sin(mb*zz2); z.x=rxy*cos(th); z.y=rxy*sin(th); if(fabs(z.x)>mc) z.x=copysign(mc*2.0,z.x)-z.x; aux.DE*=fabs(mf)*(1.0+fabs(ma*mb)); break; }
						case 190: { double pw=ma; double rp=pow(fmax(1e-10,r),pw-1.0); double th=atan2(zy,zx)*pw; double ph=asin(zz2/fmax(1e-10,r))*pw; z.x=rp*cos(ph)*cos(th); z.y=rp*cos(ph)*sin(th); z.z=rp*sin(ph); aux.DE*=pw*rp; break; }
						case 191: { z.x+=ma*sin(mb*i)*cos(mc*zy); z.y+=md*cos(me*i)*sin(mff*zx); z.z+=mg*sin(mh*i); aux.DE*=fabs(mf); break; }
						case 192: { double sc=mf; z*=sc; double lt=ma; if(fabs(z.x)>lt) z.x=copysign(lt*2.0,z.x)-z.x; if(fabs(z.y)>lt) z.y=copysign(lt*2.0,z.y)-z.y; if(fabs(z.z)>lt) z.z=copysign(lt*2.0,z.z)-z.z; double rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb) z*=mc/rr2; aux.DE*=fabs(sc); break; }
						case 193: { double p=fmax(0.01,ma); z.x=fmod(zx+p*0.5,p)-p*0.5; z.y=fmod(zy+p*0.5,p)-p*0.5; z.z=fmod(zz2+p*0.5,p)-p*0.5; if(fabs(z.x)>mb) z.x=copysign(mb*2.0,z.x)-z.x; aux.DE*=fabs(mf)/fmax(0.01,p); break; }
						case 194: { double ex=exp(-ma*rr); z*=(1.0+mb*ex); aux.DE*=(1.0+mb*ex); break; }
						case 195: { double sg=1.0/(1.0+exp(-ma*(r-mb))); z*=(1.0+mc*sg); aux.DE*=(1.0+mc*sg); break; }
						case 196: { z.x+=ma*sin(mb*zx)*cos(mc*zy); z.y+=md*cos(me*zy)*sin(mff*zz2); z.z+=mg*sin(mh*zz2)*cos(ma*zx); aux.DE*=fabs(mf); break; }
						case 197: { double th1=ma*M_PI/180.0+mb*sin(i*mc); double cs1=cos(th1),sn1=sin(th1); z.x=zx*cs1-zy*sn1; z.y=zx*sn1+zy*cs1; if(fabs(z.x)>md) z.x=copysign(md*2.0,z.x)-z.x; z*=me; aux.DE*=fabs(me); break; }
						case 198: { double rr2=rr; double fR2=ma*ma; if(rr2<fR2){ double m2=fR2/fmax(1e-21,rr2); z*=m2; aux.DE*=m2; } double th=mb*M_PI/180.0; double cs=cos(th),sn=sin(th); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; z*=mc; z.x+=md; aux.DE*=fabs(mc); break; }
						case 199: { double lt=ma+mb*sin(mc*i)*cos(md*r); if(fabs(zx)>lt) z.x=copysign(lt*2.0,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0,zz2)-zz2; double rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<me*me) z*=mff*mff/(rr2+1e-21); z*=mg; aux.DE*=fabs(mg); break; }
						case 200: { if(fabs(zx)>ma) z.x=copysign(ma*2.0,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0,zz2)-zz2; double rr2=z.x*z.x+z.y*z.y+z.z*z.z; double fR2=mb*mb; double mR2=mc*mc; if(rr2<mR2) z*=fR2/mR2; else if(rr2<fR2) z*=fR2/rr2; z*=md; z.x+=me; z.y+=mff; z.z+=mg; double th=mh*M_PI/180.0; double cs=cos(th),sn=sin(th); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; aux.DE*=fabs(md); break; }
					}
				}

				// v7.9 — Warp Distortion system (per-section iteration range)
				if (i >= mut.wdIterStart && i < mut.wdIterStop && mut.warpDistType != 0)
				{
					double wf = mut.wdFactor;
					double wa = mut.wdParamA, wb = mut.wdParamB, wc = mut.wdParamC, wd = mut.wdParamD;
					double wfq = mut.wdFreq, wam = mut.wdAmp;
					double wsc = mut.wdScale, wph = mut.wdPhase * M_PI / 180.0;
					double zx = z.x, zy = z.y, zz2 = z.z;
					double r = sqrt(zx*zx + zy*zy + zz2*zz2 + 1e-21);
					switch(mut.warpDistType)
					{
						case 1: { z.x += wf*wam*sin(wfq*zy + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq*cos(wfq*zy + wph))); break; }
						case 2: { z.y += wf*wam*sin(wfq*zz2 + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq*cos(wfq*zz2 + wph))); break; }
						case 3: { z.z += wf*wam*sin(wfq*zx + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq*cos(wfq*zx + wph))); break; }
						case 4: { z.x += wf*wam*sin(wfq*zy + wph); z.y += wf*wam*sin(wfq*zz2 + wph); z.z += wf*wam*sin(wfq*zx + wph); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq)); break; }
						case 5: { z.x += wf*wam*cos(wfq*zy + wph)*sin(wfq*zz2); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 6: { double ph = atan2(zy, zx); z.x += wf*wam*sin(wfq*ph + wph); z.y += wf*wam*cos(wfq*ph + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 7: { double ph = atan2(zy, zx); double th = acos(zz2/r); z.x += wf*wam*sin(wfq*th + wph)*cos(ph); z.y += wf*wam*sin(wfq*th + wph)*sin(ph); z.z += wf*wam*cos(wfq*th + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 8: { z.x += wf*wam*sin(wfq*zy + wph)*cos(wfq*zz2); z.y += wf*wam*sin(wfq*zz2 + wph)*cos(wfq*zx); z.z += wf*wam*sin(wfq*zx + wph)*cos(wfq*zy); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq)); break; }
						case 9: { z.x += wf*wam*sin(wfq*zx + wph); z.y += wf*wb*sin(wfq*zy + wph); z.z += wf*wc*sin(wfq*zz2 + wph); aux.DE *= (1.0 + fabs(wf*(wam+wb+wc)*wfq/3.0)); break; }
						case 10: { double d = wf*wam*sin(wfq*r + wph); z.x += d*zx/r; z.y += d*zy/r; z.z += d*zz2/r; aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 11: { z.x += wf*wam*sin(wfq*sin(wa*zy) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 12: { z.y += wf*wam*sin(wfq*cos(wa*zz2) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 13: { z.z += wf*wam*cos(wfq*sin(wa*zx) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 14: { double d1 = sin(wfq*zx+wph); double d2 = sin(wa*zy+wb); z.x += wf*wam*sin(wfq*d1+d2); z.y += wf*wam*cos(wa*d1-d2); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq)); break; }
						case 15: { z.x += wf*wam*sin(wfq*(zx*zy) + wph); z.y += wf*wam*cos(wfq*(zy*zz2) + wph); z.z += wf*wam*sin(wfq*(zz2*zx) + wph); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq)); break; }
						case 16: { double n1 = sin(wfq*zx+wa*zy); double n2 = sin(wa*zy+wb*zz2); z.x += wf*wam*sin(wfq*n1+wph); z.y += wf*wam*sin(wfq*n2+wph); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq)); break; }
						case 17: { double n1 = cos(wfq*zx)*sin(wa*zy); double n2 = cos(wa*zy)*sin(wb*zz2); double n3 = cos(wb*zz2)*sin(wfq*zx); z.x += wf*wam*n1; z.y += wf*wam*n2; z.z += wf*wam*n3; aux.DE *= (1.0 + 3.0*fabs(wf*wam)); break; }
						case 18: { z.x += wf*wam*sin(wfq*zy*zz2/(r+1e-21) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 19: { double t = wfq*r+wph; z.x += wf*wam*sin(t)*cos(wa*zy); z.y += wf*wam*cos(t)*sin(wa*zz2); z.z += wf*wam*sin(t)*cos(wa*zx); aux.DE *= (1.0 + 3.0*fabs(wf*wam)); break; }
						case 20: { double q = sin(wfq*zx+wph)+sin(wa*zy+wb)+sin(wc*zz2+wd); z.x += wf*wam*sin(q); z.y += wf*wam*cos(q); z.z += wf*wam*sin(q+M_PI*0.5); aux.DE *= (1.0 + 3.0*fabs(wf*wam)); break; }
						case 21: { { double v=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); v+=sin(f*zx+wph)*cos(f*zy)/pow(2.0,o);} z.x+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
						case 22: { { double v=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); v+=sin(f*zy+wph)*cos(f*zz2)/pow(2.0,o);} z.y+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
						case 23: { { double v=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); v+=sin(f*zz2+wph)*cos(f*zx)/pow(2.0,o);} z.z+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
						case 24: { { double vx=0,vy=0,vz=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); double a=1.0/pow(2.0,o); vx+=sin(f*zy+wph)*a; vy+=sin(f*zz2+wph)*a; vz+=sin(f*zx+wph)*a;} z.x+=wf*wam*vx; z.y+=wf*wam*vy; z.z+=wf*wam*vz; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq*4.0)); } break; }
						case 25: { { double vx=0,vy=0,vz=0; for(int o=0;o<int(wa);o++){double f=wfq*pow(wb,o); double a=1.0/pow(wb,o); vx+=sin(f*zy+o*wph)*a; vy+=sin(f*zz2+o*wph)*a; vz+=sin(f*zx+o*wph)*a;} z.x+=wf*wam*vx; z.y+=wf*wam*vy; z.z+=wf*wam*vz; aux.DE*=(1.0+3.0*fabs(wf*wam)); } break; }
						case 26: { { double v=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); v+=fabs(sin(f*zx+wph))*cos(f*zy)/pow(2.0,o);} z.x+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
						case 27: { { double vx=0,vy=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); vx+=sin(f*zy+wph)*cos(f*zz2)/pow(2.0,o); vy+=cos(f*zx+wph)*sin(f*zz2)/pow(2.0,o);} z.x+=wf*wam*vx; z.y+=wf*wam*vy; aux.DE*=(1.0+2.0*fabs(wf*wam*wfq*4.0)); } break; }
						case 28: { { double v=0; for(int o=0;o<6;o++){double f=wfq*pow(2.0,o); v+=sin(f*r+wph)/pow(2.0,o);} double d=wf*wam*v; z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0+fabs(wf*wam*wfq*6.0)); } break; }
						case 29: { { double vx=0,vy=0,vz=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); double p=wph+o*M_PI*0.25; vx+=sin(f*zy+p)*cos(f*zz2+p)/pow(2.0,o); vy+=sin(f*zz2+p)*cos(f*zx+p)/pow(2.0,o); vz+=sin(f*zx+p)*cos(f*zy+p)/pow(2.0,o);} z.x+=wf*wam*vx; z.y+=wf*wam*vy; z.z+=wf*wam*vz; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq*4.0)); } break; }
						case 30: { { double ph2=atan2(zy,zx); double th=acos(zz2/r); double v=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); v+=sin(f*th+wph)*cos(f*ph2)/pow(2.0,o);} double d=wf*wam*v; z.x+=d*sin(th)*cos(ph2); z.y+=d*sin(th)*sin(ph2); z.z+=d*cos(th); aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); } break; }
						case 31: { z.x += wf*wam*(cos(wfq*zy+wph)-cos(wfq*zz2+wph)); z.y += wf*wam*(cos(wfq*zz2+wph)-cos(wfq*zx+wph)); z.z += wf*wam*(cos(wfq*zx+wph)-cos(wfq*zy+wph)); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq)); break; }
						case 32: { { double cx=-wfq*cos(wfq*zy+wph); double cy=-wfq*cos(wfq*zz2+wph); double cz=-wfq*cos(wfq*zx+wph); z.x+=wf*wam*(cy-cz); z.y+=wf*wam*(cz-cx); z.z+=wf*wam*(cx-cy); aux.DE*=(1.0+3.0*fabs(wf*wam*wfq)); } break; }
						case 33: { z.x += wf*wam*sin(wfq*zy+wph)*sin(wa*zz2); z.y += -wf*wam*sin(wfq*zx+wph)*sin(wa*zz2); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq)); break; }
						case 34: { z.x += wf*wam*sin(wfq*zz2+wph); z.z += -wf*wam*sin(wfq*zx+wph); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq)); break; }
						case 35: { z.y += wf*wam*sin(wfq*zx+wph); z.x += -wf*wam*sin(wfq*zy+wph); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq)); break; }
						case 36: { { double dx=wf*wam*wfq*cos(wfq*zy+wph); double dy=wf*wam*wa*cos(wa*zz2+wph); double dz=wf*wam*wfq*cos(wfq*zx+wph); z.x+=dy-dz; z.y+=dz-dx; z.z+=dx-dy; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq)); } break; }
						case 37: { { double psi=wf*wam*sin(wfq*zx+wph)*cos(wa*zy)*sin(wb*zz2); z.x+=wf*wam*wa*sin(wfq*zx)*cos(wa*zy); z.y+=-wf*wam*wfq*cos(wfq*zx)*sin(wa*zy); aux.DE*=(1.0+2.0*fabs(wf*wam*wfq)); } break; }
						case 38: { { double u=wf*wam*sin(wfq*r+wph); z.x+=u*(-zy/r); z.y+=u*(zx/r); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 39: { { double u=wf*wam*sin(wfq*zz2+wph); z.x+=u*(-zy/(sqrt(zx*zx+zy*zy)+1e-21)); z.y+=u*(zx/(sqrt(zx*zx+zy*zy)+1e-21)); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 40: { { double ph2=atan2(zy,zx); double u=wf*wam*sin(wfq*ph2+wph); z.z+=u; aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 41: { { double th=wf*wfq*zz2+wph; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0+fabs(wf*wfq*wam)); } break; }
						case 42: { { double th=wf*wfq*zx+wph; double cs=cos(th),sn=sin(th); double ny=zy*cs-zz2*sn; z.z=zy*sn+zz2*cs; z.y=ny; aux.DE*=(1.0+fabs(wf*wfq*wam)); } break; }
						case 43: { { double th=wf*wfq*zy+wph; double cs=cos(th),sn=sin(th); double nx=zx*cs-zz2*sn; z.z=zx*sn+zz2*cs; z.x=nx; aux.DE*=(1.0+fabs(wf*wfq*wam)); } break; }
						case 44: { { double th=wf*wfq*r+wph; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0+fabs(wf*wfq*wam)); } break; }
						case 45: { { double a1=wf*wa*sin(wfq*zz2+wph); double cs=cos(a1),sn=sin(a1); double nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; double a2=wf*wb*sin(wfq*zx+wph); cs=cos(a2); sn=sin(a2); double ny=zy*cs-zz2*sn; z.z=zy*sn+zz2*cs; z.y=ny; aux.DE*=(1.0+fabs(wf*(wa+wb)*wfq)); } break; }
						case 46: { { double ph2=atan2(zy,zx)+wf*wam*sin(wfq*zz2+wph); double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(ph2); z.y=rxy*sin(ph2); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 47: { { double th=acos(zz2/r)+wf*wam*sin(wfq*r+wph); double ph2=atan2(zy,zx); z.x=r*sin(th)*cos(ph2); z.y=r*sin(th)*sin(ph2); z.z=r*cos(th); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 48: { { double a=wf*wam*zz2*wfq; double cs=cos(a),sn=sin(a); double nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; z.z+=wf*wb*sin(wfq*r+wph); aux.DE*=(1.0+fabs(wf*(wam+wb)*wfq)); } break; }
						case 49: { { double a=wf*wam*sin(wfq*zz2+wph); z.x=zx*cos(a)-zy*sin(a)+wf*wb*sin(wfq*zy); z.y=zx*sin(a)+zy*cos(a)+wf*wc*cos(wfq*zz2); z.z+=wf*wd*sin(wfq*zx+wph); aux.DE*=(1.0+fabs(wf*(wam+wb+wc+wd)*wfq/4.0)); } break; }
						case 50: { { double t=wf*wfq*log(r+1e-21)+wph; double cs=cos(t),sn=sin(t); double nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0+fabs(wf*wfq/(r+1e-21))); } break; }
						case 51: { { double d=wf*wam*sin(wfq*r+wph); z*=(1.0+d/r); aux.DE*=(1.0+fabs(d/r)); } break; }
						case 52: { { double d=wf*wam/(1.0+exp(-wfq*(r-wa))); z*=(1.0+d); aux.DE*=(1.0+fabs(d)); } break; }
						case 53: { { double d=wf*wam*exp(-wfq*r*r); z*=(1.0+d); aux.DE*=(1.0+fabs(d)); } break; }
						case 54: { { double d=wf*wam*exp(-wfq*fabs(r-wa)); z*=(1.0+d); aux.DE*=(1.0+fabs(d)); } break; }
						case 55: { { double d=wf*wam*(sin(wfq*r+wph)+sin(wa*r+wb))*0.5; z*=(1.0+d/r); aux.DE*=(1.0+fabs(d/r)); } break; }
						case 56: { { double rxy=sqrt(zx*zx+zy*zy+1e-21); double d=wf*wam*sin(wfq*rxy+wph); z.x+=d*zx/rxy; z.y+=d*zy/rxy; aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 57: { { double d=wf*wam*sin(wfq*zz2+wph)*exp(-wa*sqrt(zx*zx+zy*zy)); z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0+fabs(d)); } break; }
						case 58: { { double ph2=atan2(zy,zx); double th=acos(zz2/r); double d=wf*wam*sin(wfq*ph2*wa+wph)*sin(wb*th); z.x+=d*sin(th)*cos(ph2); z.y+=d*sin(th)*sin(ph2); z.z+=d*cos(th); aux.DE*=(1.0+fabs(wf*wam)); } break; }
						case 59: { { double nr=r+wf*wam*sin(wfq*r+wph); z*=(nr/r); aux.DE*=(nr/r); } break; }
						case 60: { { double f2=1.0+wf*wam*sin(wfq*r+wph)/(r+1e-21); z*=f2; aux.DE*=fabs(f2); } break; }
						case 61: { z.x += wf*wam*sin(wfq*floor(zy*wa)/wa + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 62: { z.y += wf*wam*sin(wfq*floor(zz2*wa)/wa + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 63: { z.z += wf*wam*sin(wfq*floor(zx*wa)/wa + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq)); break; }
						case 64: { { double gx=floor(zx*wa+0.5)/wa; double gy=floor(zy*wa+0.5)/wa; z.x+=wf*wam*sin(wfq*gy+wph); z.y+=wf*wam*cos(wfq*gx+wph); aux.DE*=(1.0+2.0*fabs(wf*wam*wfq)); } break; }
						case 65: { { double fx=zx-floor(zx*wa)/wa; double fy=zy-floor(zy*wa)/wa; z.x+=wf*wam*sin(wfq*fx*M_PI*2.0+wph); z.y+=wf*wam*sin(wfq*fy*M_PI*2.0+wph); aux.DE*=(1.0+2.0*fabs(wf*wam*wfq)); } break; }
						case 66: { { double d=zx*wa-floor(zx*wa+0.5); z.x+=wf*wam*d*sin(wfq*zy+wph); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 67: { { double d=sin(wfq*zx+wph)*sin(wa*zy+wb)*sin(wc*zz2+wd); z.x+=wf*wam*d; z.y+=wf*wam*d; z.z+=wf*wam*d; aux.DE*=(1.0+3.0*fabs(wf*wam)); } break; }
						case 68: { { double d=wf*wam*sin(wfq*(zx+zy+zz2)+wph); z.x+=d; z.y+=d; z.z+=d; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq)); } break; }
						case 69: { { double d=wf*wam*sin(wfq*(zx*zy+zy*zz2+zz2*zx)/(r*r+1e-21)+wph); z.x+=d; z.y+=d; z.z+=d; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq)); } break; }
						case 70: { { double v=wf*wam*cos(wfq*zx+wph)*cos(wa*zy+wb)*cos(wc*zz2+wd); z.x+=v*sin(wfq*zy); z.y+=v*sin(wa*zz2); z.z+=v*sin(wc*zx); aux.DE*=(1.0+3.0*fabs(wf*wam)); } break; }
						case 71: { { double d=wf*wam*exp(-wfq*(zx*zx+zy*zy)); z.z+=d; aux.DE*=(1.0+fabs(d)); } break; }
						case 72: { { double d=wf*wam*exp(-wfq*r)*sin(wa*r+wph); z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0+fabs(d)); } break; }
						case 73: { { double d=wf*wam*exp(-wfq*fabs(zz2))*sin(wa*sqrt(zx*zx+zy*zy)+wph); z.z+=d; aux.DE*=(1.0+fabs(d)); } break; }
						case 74: { { double d=wf*wam/(1.0+wfq*(zx*zx+zy*zy+zz2*zz2)); z.x+=d*sin(wa*zy+wph); z.y+=d*cos(wa*zz2+wph); aux.DE*=(1.0+2.0*fabs(d*wa)); } break; }
						case 75: { { z *= (1.0 + wf*wam*pow(fabs(sin(wfq*r+wph)), wa)); aux.DE *= (1.0 + fabs(wf*wam)); } break; }
						case 76: { { double p=wf*wam*pow(r+1e-21, wa-1.0)*sin(wfq*r+wph); z.x+=p*zx; z.y+=p*zy; z.z+=p*zz2; aux.DE*=(1.0+fabs(p*r)); } break; }
						case 77: { { double d=wf*wam*tanh(wfq*(r-wa)); z*=(1.0+d); aux.DE*=(1.0+fabs(d)); } break; }
						case 78: { { double d=wf*wam*log(1.0+wfq*r)*sin(wa*r+wph)/(r+1e-21); z.x+=d*zx; z.y+=d*zy; z.z+=d*zz2; aux.DE*=(1.0+fabs(d*r)); } break; }
						case 79: { { double d=wf*wam*sin(wfq*log(r+1e-21)+wph); z*=(1.0+d/r); aux.DE*=(1.0+fabs(d/r)); } break; }
						case 80: { { double sg=1.0/(1.0+exp(-wfq*(r-wa))); z*=(1.0+wf*wam*(2.0*sg-1.0)); aux.DE*=(1.0+fabs(wf*wam*(2.0*sg-1.0))); } break; }
						case 81: { { double rxy=sqrt(zx*zx+zy*zy+1e-21); double d=wf*wam*sin(wfq*rxy+wph); z.z+=d; aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 82: { { double rxy=sqrt(zx*zx+zy*zy+1e-21); double d=wf*wam*sin(wfq*zz2+wph); z.x+=d*zx/rxy; z.y+=d*zy/rxy; aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 83: { { double rxy=sqrt(zx*zx+zy*zy+1e-21); double rt=rxy-wa; double dt=sqrt(rt*rt+zz2*zz2); double d=wf*wam*sin(wfq*dt+wph); z.x+=d*(rt/dt)*(zx/rxy); z.y+=d*(rt/dt)*(zy/rxy); z.z+=d*(zz2/dt); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 84: { { double ph2=atan2(zy,zx); double d=wf*wam*sin(wfq*ph2*wa+wph); z.z+=d; aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 85: { { double ph2=atan2(zy,zx); double rxy=sqrt(zx*zx+zy*zy+1e-21); z.x+=-wf*wam*sin(ph2)*sin(wfq*zz2+wph); z.y+=wf*wam*cos(ph2)*sin(wfq*zz2+wph); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 86: { { double rxy=sqrt(zx*zx+zy*zy+1e-21); double d=wf*wam*sin(wfq*rxy+wph)*cos(wa*zz2); z.x+=d*zx/rxy; z.y+=d*zy/rxy; z.z+=wf*wam*cos(wfq*rxy+wph)*sin(wa*zz2); aux.DE*=(1.0+2.0*fabs(wf*wam*wfq)); } break; }
						case 87: { { double rxy=sqrt(zx*zx+zy*zy+1e-21); double ph2=atan2(zy,zx)+wf*wam*sin(wfq*zz2+wph)/rxy; z.x=rxy*cos(ph2); z.y=rxy*sin(ph2); aux.DE*=(1.0+fabs(wf*wam*wfq/rxy)); } break; }
						case 88: { { double rxy=sqrt(zx*zx+zy*zy+1e-21); double ph2=atan2(zy,zx); double nr=rxy+wf*wam*sin(wfq*zz2+wph)*sin(wa*ph2); z.x=nr*cos(ph2); z.y=nr*sin(ph2); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 89: { { double rxy=sqrt(zx*zx+zy*zy+1e-21); z.z+=wf*wam*sin(wfq*rxy+wph)*cos(wa*atan2(zy,zx)); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 90: { { double rxy=sqrt(zx*zx+zy*zy+1e-21); double rt=rxy-wa; double ang=atan2(zz2,rt); double d=wf*wam*sin(wfq*ang+wph); z.x+=d*(zx/rxy); z.y+=d*(zy/rxy); aux.DE*=(1.0+fabs(wf*wam*wfq)); } break; }
						case 91: { { double a=wf*wa; double b=wf*wb; z.x=zx+a*sin(wfq*zy); z.y=zy+b*sin(wfq*zx); aux.DE*=(1.0+fabs((a+b)*wfq)); } break; }
						case 92: { { double k=wf*wam; z.x=zx+k*zy; z.y=zy+k*sin(wfq*zx+wph); aux.DE*=(1.0+fabs(k*wfq)); } break; }
						case 93: { { z.x=r*cos(wfq*zy/r+wph); z.y=r*sin(wfq*zy/r+wph); aux.DE*=(1.0+fabs(wf*wam*wfq/r)); } break; }
						case 94: { { double nr=r+wf*wam*sin(wfq*atan2(zy,zx)*wa+wph); z*=(nr/r); aux.DE*=(nr/r); } break; }
						case 95: { { double th=wf*wam/(r*r+1e-10); double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0+fabs(wf*wam*2.0*r/((r*r+1e-10)*(r*r+1e-10)))); } break; }
						case 96: { { double denom=zx*zx+zy*zy+1e-21; z.x=wf*wam*zx/denom+wsc*sin(wfq*zy+wph); z.y=-wf*wam*zy/denom+wsc*cos(wfq*zx+wph); aux.DE*=(1.0+fabs(wf*wam/denom)+fabs(wsc*wfq)); } break; }
						case 97: { { double a1=wfq; double a2=wa; z.x=zx*cos(a1*zy)-zy*sin(a1*zy)+wf*wam*sin(a2*zz2+wph); z.y=zx*sin(a1*zy)+zy*cos(a1*zy)+wf*wam*cos(a2*zz2+wph); aux.DE*=(1.0+fabs(wf*wam*a1)+fabs(wf*wam*a2)); } break; }
						case 98: { { double lx=wf*wam*sin(wfq*zy+wph)*(1.0-exp(-wa*r)); double ly=wf*wb*sin(wfq*zz2+wph)*(1.0-exp(-wa*r)); double lz=wf*wc*sin(wfq*zx+wph)*(1.0-exp(-wa*r)); z.x+=lx; z.y+=ly; z.z+=lz; aux.DE*=(1.0+fabs(wf*(wam+wb+wc)*wfq/3.0)); } break; }
						case 99: { { double t=wfq*r+wph; double d=wf*wam*sin(t)*sin(wa*t); z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0+fabs(d)); } break; }
						case 100: { { double d=wf*wam*(sin(wfq*zx+wph)+sin(wa*zy+wb)+sin(wc*zz2+wd)); z*=(1.0+d/(3.0*r)); aux.DE*=(1.0+fabs(d/(3.0*r))); } break; }
					}
				}

				// v7.9 — Symmetry/Kaleidoscope system (per-section iteration range)
				if (i >= mut.skIterStart && i < mut.skIterStop && mut.symKalType != 0)
				{
					double sf = mut.skFactor;
					double sa = mut.skParamA, sb = mut.skParamB, sc = mut.skParamC, sd = mut.skParamD;
					double sfq = mut.skFreq, sam = mut.skAmp;
					double sang = mut.skAngle * M_PI / 180.0, soff = mut.skOffset;
					double zx = z.x, zy = z.y, zz2 = z.z;
					double r = sqrt(zx*zx + zy*zy + zz2*zz2 + 1e-21);
					switch(mut.symKalType)
					{
						case 1: { z.x = fabs(z.x); break; }
						case 2: { z.y = fabs(z.y); break; }
						case 3: { z.z = fabs(z.z); break; }
						case 4: { z.x = fabs(z.x); z.y = fabs(z.y); break; }
						case 5: { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); break; }
						case 6: { if(z.x < 0) z.x = -z.x - soff; else z.x = z.x + soff; break; }
						case 7: { if(z.y < 0) z.y = -z.y - soff; else z.y = z.y + soff; break; }
						case 8: { if(z.x + z.y < 0) { double t = z.x; z.x = -z.y; z.y = -t; } break; }
						case 9: { if(z.x - z.y < 0) { double t = z.x; z.x = z.y; z.y = t; } break; }
						case 10: { if(z.x + z.z < 0) { double t = z.x; z.x = -z.z; z.z = -t; } break; }
						case 11: { { double ang2 = atan2(zy, zx); double n = fmax(1.0, sa); double sector = 2.0*M_PI/n; ang2 = fmod(ang2 + 10.0*M_PI, sector) - sector*0.5; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); } break; }
						case 12: { { double ang2 = atan2(zy, zx); double n = 3.0; double sector = 2.0*M_PI/n; ang2 = fmod(ang2 + 10.0*M_PI, sector) - sector*0.5; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); } break; }
						case 13: { { double ang2 = atan2(zy, zx); double n = 4.0; double sector = 2.0*M_PI/n; ang2 = fmod(ang2 + 10.0*M_PI, sector) - sector*0.5; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); } break; }
						case 14: { { double ang2 = atan2(zy, zx); double n = 5.0; double sector = 2.0*M_PI/n; ang2 = fmod(ang2 + 10.0*M_PI, sector) - sector*0.5; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); } break; }
						case 15: { { double ang2 = atan2(zy, zx); double n = 6.0; double sector = 2.0*M_PI/n; ang2 = fmod(ang2 + 10.0*M_PI, sector) - sector*0.5; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); } break; }
						case 16: { { double ang2 = atan2(zy, zx); double n = 8.0; double sector = 2.0*M_PI/n; ang2 = fmod(ang2 + 10.0*M_PI, sector) - sector*0.5; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); } break; }
						case 17: { { double ang2 = atan2(zy, zx); double n = 12.0; double sector = 2.0*M_PI/n; ang2 = fmod(ang2 + 10.0*M_PI, sector) - sector*0.5; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); } break; }
						case 18: { { double ang2 = atan2(zz2, zx); double n = fmax(1.0, sa); double sector = 2.0*M_PI/n; ang2 = fmod(ang2 + 10.0*M_PI, sector) - sector*0.5; double rxz = sqrt(zx*zx+zz2*zz2); z.x = rxz*cos(ang2); z.z = rxz*sin(ang2); } break; }
						case 19: { { double ang2 = atan2(zz2, zy); double n = fmax(1.0, sa); double sector = 2.0*M_PI/n; ang2 = fmod(ang2 + 10.0*M_PI, sector) - sector*0.5; double ryz = sqrt(zy*zy+zz2*zz2); z.y = ryz*cos(ang2); z.z = ryz*sin(ang2); } break; }
						case 20: { { double ang2 = atan2(zy, zx); double n = fmax(1.0, sa); double sector = 2.0*M_PI/n; ang2 = fmod(ang2 + 10.0*M_PI, sector); if(fmod(floor(ang2/sector), 2.0) > 0.5) ang2 = sector - fmod(ang2, sector); else ang2 = fmod(ang2, sector); ang2 -= sector*0.5; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); } break; }
						case 21: { { double cs = cos(sang), sn = sin(sang); double nx = zx*cs - zy*sn; z.y = zx*sn + zy*cs; z.x = fabs(nx); } break; }
						case 22: { { double cs = cos(sang), sn = sin(sang); z.x = fabs(zx); double nx = zx*cs - zy*sn; z.y = zx*sn + zy*cs; z.x = nx; z.x = fabs(z.x); } break; }
						case 23: { { if(z.x + z.y < soff) { double t = z.x; z.x = -z.y; z.y = -t; } double cs = cos(sang), sn = sin(sang); double nx = zx*cs - zy*sn; z.y = zx*sn + zy*cs; z.x = nx; } break; }
						case 24: { { z.x = fabs(z.x); z.y = fabs(z.y); double cs = cos(sang), sn = sin(sang); double nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; z.x = fabs(z.x); } break; }
						case 25: { { z.x = fabs(z.x) + soff; z.y = fabs(z.y) + soff; double cs = cos(sang), sn = sin(sang); double nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } break; }
						case 26: { { for(int k=0; k<int(sa); k++) { z.x = fabs(z.x); z.y = fabs(z.y); double cs = cos(sang), sn = sin(sang); double nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } } break; }
						case 27: { { for(int k=0; k<int(sa); k++) { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); double cs = cos(sang+k*sb), sn = sin(sang+k*sb); double nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } } break; }
						case 28: { { double cs1 = cos(sang), sn1 = sin(sang); double nx = zx*cs1 - zy*sn1; z.y = zx*sn1 + zy*cs1; z.x = nx; z.x = fabs(z.x); double cs2 = cos(-sang), sn2 = sin(-sang); nx = z.x*cs2 - z.y*sn2; z.y = z.x*sn2 + z.y*cs2; z.x = nx; } break; }
						case 29: { { z.x = fabs(z.x); if(z.x - z.y < 0) { double t = z.x; z.x = z.y; z.y = t; } z.y = fabs(z.y); double cs = cos(sang), sn = sin(sang); double nx = z.x*cs - z.z*sn; z.z = z.x*sn + z.z*cs; z.x = nx; } break; }
						case 30: { { double n = fmax(2.0, sa); for(int k=0; k<int(n); k++) { double a = k * 2.0*M_PI/n; double cs = cos(a), sn = sin(a); double d = z.x*cs + z.y*sn; if(d < 0) { z.x -= 2.0*d*cs; z.y -= 2.0*d*sn; } } } break; }
						case 31: { { z.x = fabs(z.x); z.y = fabs(z.y); if(z.y > z.x) { double t=z.x; z.x=z.y; z.y=t; } z.x -= sa; z.y -= sb; } break; }
						case 32: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.y > z.x) { double t=z.x; z.x=z.y; z.y=t; } if(z.z > z.x) { double t=z.x; z.x=z.z; z.z=t; } if(z.z > z.y) { double t=z.y; z.y=z.z; z.z=t; } z.x -= sa; z.y -= sb; z.z -= sc; } break; }
						case 33: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.x - z.y < 0) { double t=z.x; z.x=z.y; z.y=t; } if(z.x - z.z < 0) { double t=z.x; z.x=z.z; z.z=t; } if(z.y - z.z < 0) { double t=z.y; z.y=z.z; z.z=t; } z.x -= sa; z.y -= sb; z.z -= sc; double cs = cos(sang), sn = sin(sang); double nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } break; }
						case 34: { { z.x = fabs(z.x); z.y = fabs(z.y); double d = z.x*cos(sang) + z.y*sin(sang); if(d < 0) { z.x -= 2.0*d*cos(sang); z.y -= 2.0*d*sin(sang); } z.x -= sa; z.y -= sb; z.z -= 0; } break; }
						case 35: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); z.x -= sa; z.y -= sb; z.z -= sc; if(z.y > z.x) { double t=z.x; z.x=z.y; z.y=t; } if(z.z > z.x) { double t=z.x; z.x=z.z; z.z=t; } if(z.z > z.y) { double t=z.y; z.y=z.z; z.z=t; } } break; }
						case 36: { { double d = 2.0*fmax(0.0, z.x*cos(sang) + z.y*sin(sang)); z.x -= d*cos(sang); z.y -= d*sin(sang); z.x = fabs(z.x); } break; }
						case 37: { { z.x = fabs(z.x); z.y = fabs(z.y); double a = sang; for(int k=0; k<3; k++) { double d = 2.0*fmin(0.0, z.x*cos(a) + z.y*sin(a)); z.x -= d*cos(a); z.y -= d*sin(a); a += M_PI/3.0; } z.x -= sa; z.y -= sb; z.z -= 0; } break; }
						case 38: { { for(int k=0; k<int(fmax(1,sa)); k++) { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); z.x -= sb; z.y -= sc; z.z -= sd; if(z.y > z.x) { double t=z.x; z.x=z.y; z.y=t; } if(z.z > z.x) { double t=z.x; z.x=z.z; z.z=t; } if(z.z > z.y) { double t=z.y; z.y=z.z; z.z=t; } z *= sf; aux.DE *= fabs(sf); } } break; }
						case 39: { { for(int k=0; k<int(fmax(1,sa)); k++) { double cs = cos(sang+k*sb), sn = sin(sang+k*sb); double d = z.x*cs + z.y*sn; if(d < 0) { z.x -= 2.0*d*cs; z.y -= 2.0*d*sn; } z.x = fabs(z.x) - sc; z.y = fabs(z.y) - sd; } } break; }
						case 40: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); z.x = z.x - sa*round(z.x/fmax(sa,1e-21)); z.y = z.y - sb*round(z.y/fmax(sb,1e-21)); z.z = z.z - sc*round(z.z/fmax(sc,1e-21)); } break; }
						case 41: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.x - z.y < 0) { double t=z.x; z.x=z.y; z.y=t; } if(z.x - z.z < 0) { double t=z.x; z.x=z.z; z.z=t; } if(z.y - z.z < 0) { double t=z.y; z.y=z.z; z.z=t; } z *= sf; { double _cF=(sf-1.0); z.x -= sa*_cF; z.y -= sb*_cF; z.z -= sc*_cF; }; aux.DE = aux.DE * fabs(sf) + 1.0; } break; }
						case 42: { { if(z.x + z.y < 0) { double t=-z.y; z.y=-z.x; z.x=t; } if(z.x + z.z < 0) { double t=-z.z; z.z=-z.x; z.x=t; } if(z.y + z.z < 0) { double t=-z.z; z.z=-z.y; z.y=t; } z *= sf; { double _cF=(sf-1.0); z.x -= sa*_cF; z.y -= sb*_cF; z.z -= sc*_cF; }; aux.DE = aux.DE * fabs(sf) + 1.0; } break; }
						case 43: { { z.x = fabs(z.x); z.y = fabs(z.y); if(z.x - z.y < 0) { double t=z.x; z.x=z.y; z.y=t; } z.x -= sa; z *= sf; z.x += sa; aux.DE = aux.DE * fabs(sf) + 1.0; } break; }
						case 44: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.x - z.y < 0) { double t=z.x; z.x=z.y; z.y=t; } if(z.x - z.z < 0) { double t=z.x; z.x=z.z; z.z=t; } if(z.y - z.z < 0) { double t=z.y; z.y=z.z; z.z=t; } z.z -= 0.5*sc*(sf-1.0)/sf; z.z = fabs(z.z); z.z += 0.5*sc*(sf-1.0)/sf; z *= sf; { double _cF=(sf-1.0); z.x -= sa*_cF; z.y -= sb*_cF; z.z -= sc*_cF; }; aux.DE = aux.DE*fabs(sf)+1.0; } break; }
						case 45: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); double t; if(z.x-z.y<0){t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){t=z.y;z.y=z.z;z.z=t;} z *= sf; double _f45=(sf-1.0)*sa; z.x -= _f45; z.y -= _f45; z.z -= _f45; aux.DE=aux.DE*fabs(sf)+1.0; z.x=fabs(z.x); z.y=fabs(z.y); } break; }
						case 46: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); double d1 = z.x - z.y; double d2 = z.y - z.z; if(d1 < 0){double t=z.x;z.x=z.y;z.y=t;} if(d2 < 0){double t=z.y;z.y=z.z;z.z=t;} if(z.x-z.y < 0){double t=z.x;z.x=z.y;z.y=t;} z.x -= sa; z.y -= sb; z.z -= sc; z *= sf; z.x += sa; z.y += sb; z.z += sc; aux.DE = aux.DE*fabs(sf)+1.0; } break; }
						case 47: { { z.x = sa - fabs(z.x - sa); z.y = sb - fabs(z.y - sb); z.z = sc - fabs(z.z - sc); } break; }
						case 48: { { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.x>sa) z.x=2.0*sa-z.x; if(z.y>sb) z.y=2.0*sb-z.y; if(z.z>sc) z.z=2.0*sc-z.z; } break; }
						case 49: { { double p=sa; z.x = z.x - p*floor(z.x/p+0.5); z.y = z.y - p*floor(z.y/p+0.5); z.z = z.z - p*floor(z.z/p+0.5); } break; }
						case 50: { { double px=sa, py=sb; z.x = z.x - px*floor(z.x/px+0.5); z.y = z.y - py*floor(z.y/py+0.5); } break; }
						case 51: { { double ph2=atan2(zy,zx); double n=fmax(1.0,sa); double s=2.0*M_PI/n; ph2=fmod(ph2+10.0*M_PI,s)-s*0.5; double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(ph2); z.y=rxy*sin(ph2); z.z=fabs(z.z); } break; }
						case 52: { { double ph2=atan2(zy,zx); double th=acos(zz2/r); double n=fmax(1.0,sa); double sp=2.0*M_PI/n; ph2=fmod(ph2+10.0*M_PI,sp)-sp*0.5; double m=fmax(1.0,sb); double st=M_PI/m; th=fmod(th+10.0*M_PI,st); z.x=r*sin(th)*cos(ph2); z.y=r*sin(th)*sin(ph2); z.z=r*cos(th); } break; }
						case 53: { { double ph2=atan2(zy,zx)+sang; double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(ph2); z.y=rxy*sin(ph2); z.z=fabs(zz2); } break; }
						case 54: { { double rxy=sqrt(zx*zx+zy*zy); if(rxy>sa) { double f=sa/rxy; z.x*=f; z.y*=f; } } break; }
						case 55: { { if(r>sa) z*=sa/r; } break; }
						case 56: { { if(r<sa) z*=sa*sa/(r*r); else if(r<sb) z*=sa*sa/(r*r); } break; }
						case 57: { { double rr=r*r; if(rr<sa*sa) z*=sb*sb/(sa*sa); else if(rr<sb*sb) z*=sb*sb/rr; } break; }
						case 58: { { double th=acos(zz2/r); double n=fmax(1.0,sa); double st=M_PI/n; th=fmod(th+10.0*M_PI,st); z.x=r*sin(th)*cos(atan2(zy,zx)); z.y=r*sin(th)*sin(atan2(zy,zx)); z.z=r*cos(th); } break; }
						case 59: { { double p=sa; z.x=z.x-p*round(z.x/p); z.y=z.y-p*round(z.y/p); z.z=z.z-p*round(z.z/p); } break; }
						case 60: { { z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; z.z=fabs(z.z)-sc; if(z.x<0) z.x=-z.x; if(z.y<0) z.y=-z.y; if(z.z<0) z.z=-z.z; } break; }
						case 61: { { double px=fmax(sa,0.01); z.x=z.x-px*floor(z.x/px); z.y=fabs(z.y); } break; }
						case 62: { { double px=fmax(sa,0.01), py=fmax(sb,0.01); z.x=z.x-px*floor(z.x/px); z.y=z.y-py*floor(z.y/py); } break; }
						case 63: { { double px=fmax(sa,0.01), py=fmax(sb,0.01); z.x=z.x-px*floor(z.x/px); z.y=z.y-py*floor(z.y/py); z.x=fabs(z.x-px*0.5); } break; }
						case 64: { { double px=fmax(sa,0.01), py=fmax(sb,0.01); double ix=floor(z.x/px); z.x=z.x-px*ix; z.y=z.y-py*floor(z.y/py); if(fmod(ix,2.0)>0.5) z.x=px-z.x; } break; }
						case 65: { { double p=fmax(sa,0.01); double a60=M_PI/3.0; double ux=p, uy=0; double vx=p*cos(a60), vy=p*sin(a60); double det=ux*vy-uy*vx; double ix=floor((z.x*vy-z.y*vx)/det+0.5); double iy=floor((z.y*ux-z.x*uy)/det+0.5); z.x-=ix*ux+iy*vx; z.y-=ix*uy+iy*vy; } break; }
						case 66: { { double px=fmax(sa,0.01), py=fmax(sb,0.01), pz=fmax(sc,0.01); z.x=z.x-px*floor(z.x/px); z.y=z.y-py*floor(z.y/py); z.z=z.z-pz*floor(z.z/pz); } break; }
						case 67: { { double px=fmax(sa,0.01), py=fmax(sb,0.01), pz=fmax(sc,0.01); z.x=z.x-px*round(z.x/px); z.y=z.y-py*round(z.y/py); z.z=z.z-pz*round(z.z/pz); z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); } break; }
						case 68: { { double p=fmax(sa,0.01); z.x=z.x-p*round(z.x/p); z.y=z.y-p*round(z.y/p); z.z=z.z-p*round(z.z/p); double cs=cos(sang),sn=sin(sang); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } break; }
						case 69: { { double p=fmax(sa,0.01); double ix=round(z.x/p); double iy=round(z.y/p); z.x-=ix*p; z.y-=iy*p; double a=sang*(ix+iy); double cs=cos(a),sn=sin(a); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } break; }
						case 70: { { double p=fmax(sa,0.01); z.x=z.x-p*floor(z.x/p+0.5); z.y=z.y-p*floor(z.y/p+0.5); double cs=cos(sang),sn=sin(sang); if(z.x+z.y>0) { double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } } break; }
						case 71: { if(z.x*z.y > 0) { double t=z.x; z.x=z.y; z.y=t; } break; }
						case 72: { if(z.x*z.y < 0) { z.x = fabs(z.x); z.y = fabs(z.y); } break; }
						case 73: { if(r < sa) { z *= sf; aux.DE *= fabs(sf); } else { z.x = fabs(z.x); z.y = fabs(z.y); } break; }
						case 74: { if(fmod(double(i), sa) < sb) { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); } break; }
						case 75: { { double d = z.x*cos(sang) + z.y*sin(sang); if(d < soff) { z.x -= 2.0*(d-soff)*cos(sang); z.y -= 2.0*(d-soff)*sin(sang); } } break; }
						case 76: { { double d1 = z.x*cos(sang)+z.y*sin(sang); if(d1<0){z.x-=2.0*d1*cos(sang);z.y-=2.0*d1*sin(sang);} double a2=sang+M_PI/fmax(1.0,sa); double d2=z.x*cos(a2)+z.y*sin(a2); if(d2<0){z.x-=2.0*d2*cos(a2);z.y-=2.0*d2*sin(a2);} } break; }
						case 77: { { for(int k=0;k<int(fmax(1,sa));k++){ z.x=fabs(z.x)-sb; z.y=fabs(z.y)-sc; if(z.x<z.y){double t=z.x;z.x=z.y;z.y=t;} } } break; }
						case 78: { { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); double m=fmax(fmax(z.x,z.y),z.z); if(m==z.y){double t=z.x;z.x=z.y;z.y=t;} if(m==z.z){double t=z.x;z.x=z.z;z.z=t;} } break; }
						case 79: { { z.x = sa*floor(z.x/fmax(sa,0.01)+0.5)*2.0-z.x; z.y = sb*floor(z.y/fmax(sb,0.01)+0.5)*2.0-z.y; } break; }
						case 80: { { double a=sang; for(int k=0;k<3;k++){ z.x=fabs(z.x); double d=z.x*cos(a)+z.y*sin(a); if(d<0){z.x-=2.0*d*cos(a);z.y-=2.0*d*sin(a);} a+=M_PI/3.0*sf; } } break; }
						case 81: { { double n=fmax(2.0,sa+sb*sin(sfq*i)); double ang2=atan2(zy,zx); double s=2.0*M_PI/n; ang2=fmod(ang2+10.0*M_PI,s)-s*0.5; double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(ang2); z.y=rxy*sin(ang2); } break; }
						case 82: { { double a=sang+sam*sin(sfq*i); double cs=cos(a),sn=sin(a); z.x=fabs(z.x); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } break; }
						case 83: { { double d=sf*sam*sin(sfq*r+sang); z.x=fabs(z.x)+d; z.y=fabs(z.y)+d; z.z=fabs(z.z)+d; aux.DE*=(1.0+fabs(d)/r); } break; }
						case 84: { { double n=fmax(2.0,sa); double ang2=atan2(zy,zx); double s=2.0*M_PI/n; ang2=fmod(ang2+10.0*M_PI+sam*sin(sfq*i),s)-s*0.5; double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(ang2); z.y=rxy*sin(ang2); } break; }
						case 85: { { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); z *= sf + sam*sin(sfq*i); aux.DE *= fabs(sf + sam*sin(sfq*i)); { double _cF=(sf-1.0); z.x -= sa*_cF; z.y -= sb*_cF; z.z -= sc*_cF; }; } break; }
						case 86: { { if(i%2==0){z.x=fabs(z.x);z.y=fabs(z.y);} else{double cs=cos(sang),sn=sin(sang);double nx=z.x*cs-z.y*sn;z.y=z.x*sn+z.y*cs;z.x=nx;} } break; }
						case 87: { { double rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sa*sa){z*=sb*sb/(sa*sa);aux.DE*=sb*sb/(sa*sa);} else if(rr<sb*sb){z*=sb*sb/rr;aux.DE*=sb*sb/rr;} z.x=fabs(z.x); z.y=fabs(z.y); } break; }
						case 88: { { if(z.x+z.y<0){double t=-z.y;z.y=-z.x;z.x=t;} if(z.x+z.z<0){double t=-z.z;z.z=-z.x;z.x=t;} z *= sf; { double _cF=(sf-1.0); z.x -= sa*_cF; z.y -= sb*_cF; z.z -= sc*_cF; }; aux.DE=aux.DE*fabs(sf)+1.0; if(z.y-z.z<0){double t=z.y;z.y=z.z;z.z=t;} } break; }
						case 89: { { z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; if(z.x<z.y){double t=z.x;z.x=z.y;z.y=t;} double rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sc*sc){double m=sd*sd/(sc*sc);z*=m;aux.DE*=m;} else if(rr<sd*sd){double m=sd*sd/rr;z*=m;aux.DE*=m;} } break; }
						case 90: { { double p=fmax(sa,0.01); z.x=z.x-p*round(z.x/p); z.y=z.y-p*round(z.y/p); z.x=fabs(z.x); z.y=fabs(z.y); if(z.x<z.y){double t=z.x;z.x=z.y;z.y=t;} z *= sf; aux.DE *= fabs(sf); { double _cF=(sf-1.0); z.x -= sb*_cF; z.y -= sc*_cF; z.z -= 0*_cF; }; } break; }
						case 91: { { z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; z.z=fabs(z.z)-sc; if(z.x<z.y){double t=z.x;z.x=z.y;z.y=t;} if(z.x<z.z){double t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){double t=z.y;z.y=z.z;z.z=t;} z*=sf; aux.DE*=fabs(sf); z.x += sa; z.y += sb; z.z += sc; } break; }
						case 92: { { double cs=cos(sang),sn=sin(sang); z.x=fabs(z.x); z.y=fabs(z.y); double d=z.x*sn+z.y*cs; if(d<0){z.x-=2.0*d*sn;z.y-=2.0*d*cs;} z.x-=sa; z.y-=sb; z*=sf; z.x+=sa; z.y+=sb; aux.DE=aux.DE*fabs(sf)+1.0; } break; }
						case 93: { { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); if(z.x-z.y<0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){double t=z.x;z.x=z.z;z.z=t;} z*=sf; z.x-=sa*(sf-1.0); z.y-=sb*(sf-1.0); z.z-=sc*(sf-1.0); double rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sd*sd){z*=sd*sd/rr;aux.DE*=sd*sd/rr;} aux.DE=aux.DE*fabs(sf)+1.0; } break; }
						case 94: { { for(int k=0;k<int(fmax(1,sa));k++){ z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); if(z.x-z.y<0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){double t=z.y;z.y=z.z;z.z=t;} z.x-=sb; z.y-=sc; z.z-=sd; double cs=cos(sang+k*sfq),sn=sin(sang+k*sfq); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; z.x+=sb; z.y+=sc; z.z+=sd; } } break; }
						case 95: { { double n=fmax(2.0,sa); for(int k=0;k<int(n);k++){ double a=k*M_PI/n; double d=z.x*cos(a)+z.y*sin(a); if(d<0){z.x-=2.0*d*cos(a);z.y-=2.0*d*sin(a);} } z.z=fabs(z.z); } break; }
						case 96: { { z=fabs(z); if(z.x<z.y){double t=z.x;z.x=z.y;z.y=t;} if(z.x<z.z){double t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){double t=z.y;z.y=z.z;z.z=t;} z.x -= sa; z.y -= sb; z.z -= sc; double rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sd*sd){double m=sf*sf/fmax(rr,1e-21);z*=m;aux.DE*=m;} z*=sf;aux.DE*=fabs(sf); z.x += sa; z.y += sb; z.z += sc; } break; }
						case 97: { { double a=2.0*M_PI/fmax(1.0,sa); double cs=cos(a),sn=sin(a); z.x=fabs(z.x); z.y=fabs(z.y); double d=z.x*sn+z.y*cs-soff; if(d>0){z.x-=d*sn;z.y-=d*cs;} z.x-=sb; z*=sf; z.x+=sb; aux.DE=aux.DE*fabs(sf)+1.0; } break; }
						case 98: { { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); double d=2.0*fmin(0.0,z.x+z.y+z.z-sa); z.x-=d/3.0; z.y-=d/3.0; z.z-=d/3.0; } break; }
						case 99: { { z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); if(z.x-z.y<0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){double t=z.y;z.y=z.z;z.z=t;} z.z-=0.5*sa; z.z=-fabs(z.z)+0.5*sa; double cs=cos(sang),sn=sin(sang); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } break; }
						case 100: { { z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; z.z=fabs(z.z)-sc; if(z.x<z.y){double t=z.x;z.x=z.y;z.y=t;} if(z.x<z.z){double t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){double t=z.y;z.y=z.z;z.z=t;} double rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sd*sd){double m=sf*sf/fmax(rr,1e-21);z*=m;aux.DE*=m;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0; { double _cF=(1.0-sf); z.x += sa*_cF; z.y += sb*_cF; z.z += sc*_cF; }; } break; }
					}
				}

				// v7.9 — Abox DE system (per-section iteration range)
				if (i >= mut.abIterStart && i < mut.abIterStop && mut.aboxType != 0)
				{
					double af = mut.abFactor;
					double aa = mut.abParamA, ab = mut.abParamB, ac = mut.abParamC, ad = mut.abParamD;
					double ae = mut.abParamE, aff = mut.abParamF, ag = mut.abParamG, ah = mut.abParamH;
					double zx = z.x, zy = z.y, zz2 = z.z;
					double r = sqrt(zx*zx + zy*zy + zz2*zz2 + 1e-21);
					double rr = r*r;
					switch(mut.aboxType)
					{
						case 1: { aux.DE *= (1.0 + af * aa); break; }
						case 2: { aux.DE *= (1.0 + af * aa * sin(ab * r)); break; }
						case 3: { aux.DE *= (1.0 + af * aa * cos(ab * r)); break; }
						case 4: { aux.DE *= (1.0 + af * aa * exp(-ab * r)); break; }
						case 5: { aux.DE *= (1.0 + af * aa * exp(-ab * rr)); break; }
						case 6: { aux.DE *= (1.0 + af * aa * log(1.0 + ab * r)); break; }
						case 7: { aux.DE *= (1.0 + af * aa * tanh(ab * r)); break; }
						case 8: { aux.DE *= (1.0 + af * aa * sin(ab * zx) * cos(ac * zy)); break; }
						case 9: { aux.DE *= (1.0 + af * aa * sin(ab * zy) * cos(ac * zz2)); break; }
						case 10: { aux.DE *= (1.0 + af * aa * sin(ab * zz2) * cos(ac * zx)); break; }
						case 11: { aux.DE *= (1.0 + af * aa * (sin(ab*zx) + sin(ac*zy) + sin(ad*zz2)) / 3.0); break; }
						case 12: { aux.DE *= (1.0 + af * aa / (1.0 + ab * rr)); break; }
						case 13: { aux.DE *= (1.0 + af * aa * pow(r, ab - 1.0)); break; }
						case 14: { aux.DE *= (1.0 + af * aa * fabs(sin(ab * r))); break; }
						case 15: { aux.DE *= (1.0 + af * aa * (1.0 - exp(-ab * r))); break; }
						case 16: { { double sg = 1.0/(1.0+exp(-aa*(r-ab))); aux.DE *= (1.0 + af * sg); } break; }
						case 17: { aux.DE *= (1.0 + af * aa * sin(ab*zx)*sin(ac*zy)*sin(ad*zz2)); break; }
						case 18: { aux.DE *= (1.0 + af * aa * cos(ab*zx)*cos(ac*zy)*cos(ad*zz2)); break; }
						case 19: { aux.DE *= (1.0 + af * aa * sin(ab*r+ac*atan2(zy,zx))); break; }
						case 20: { aux.DE *= (1.0 + af * aa * sin(ab*r)*cos(ac*acos(zz2/r))); break; }
						case 21: { { double v = 0; for(int o=0;o<4;o++) v += sin(ab*pow(2.0,o)*r)/(pow(2.0,o)); aux.DE *= (1.0 + af * aa * v); } break; }
						case 22: { aux.DE *= (1.0 + af * aa * (zx*zy+zy*zz2+zz2*zx)/(rr+1e-21)); break; }
						case 23: { aux.DE *= (1.0 + af * aa * fabs(zx*zy*zz2)/(r*r*r+1e-21)); break; }
						case 24: { aux.DE *= (1.0 + af * aa * sin(ab*(zx*zx-zy*zy)/(rr+1e-21))); break; }
						case 25: { aux.DE *= (1.0 + af * aa * atan2(sqrt(zx*zx+zy*zy), zz2) / M_PI); break; }
						case 26: { { double rr2=rr; if(rr2<aa*aa) { double m=ab*ab/fmax(rr2,1e-21); aux.DE*=m; } aux.DE*=(1.0+af*0.1); } break; }
						case 27: { { double rr2=rr; double mR2=aa*aa; double fR2=ab*ab; if(rr2<mR2) aux.DE*=fR2/mR2; else if(rr2<fR2) aux.DE*=fR2/rr2; } break; }
						case 28: { aux.DE *= (1.0 + af * aa * exp(-ab*(r-ac)*(r-ac))); break; }
						case 29: { aux.DE *= (1.0 + af * aa * (1.0/(1.0+exp(-ab*(r-ac))) - 0.5)); break; }
						case 30: { aux.DE *= (1.0 + af * aa * sin(ab*r)*exp(-ac*r)); break; }
						case 31: { aux.DE *= (1.0 + af * aa * fabs(sin(ab*r+ac))*exp(-ad*r)); break; }
						case 32: { { double s = aa * sin(ab*r+ac*atan2(zy,zx)) * exp(-ad*r); aux.DE *= (1.0 + af*s); } break; }
						case 33: { aux.DE *= (1.0 + af * aa * tanh(ab*(r-ac))); break; }
						case 34: { aux.DE *= (1.0 + af * aa * sin(ab*log(r+1e-21))); break; }
						case 35: { aux.DE *= (1.0 + af * aa * cos(ab*log(r+1e-21)+ac)); break; }
						case 36: { { double ph=atan2(zy,zx); double th=acos(zz2/r); aux.DE*=(1.0+af*aa*sin(ab*ph)*sin(ac*th)); } break; }
						case 37: { { double ph=atan2(zy,zx); aux.DE*=(1.0+af*aa*cos(ab*ph+ac*r)); } break; }
						case 38: { aux.DE *= fmax(0.01, 1.0 + af * aa * sin(ab*r) * cos(ac*r)); break; }
						case 39: { { double d=r-aa; aux.DE*=(1.0+af*ab*exp(-ac*d*d)); } break; }
						case 40: { aux.DE *= (1.0 + af * aa * sin(ab*r) / (r+1e-21)); break; }
						case 41: { { double n=sin(aa*zx)*sin(ab*zy)*sin(ac*zz2); aux.DE*=(1.0+af*ad*n); } break; }
						case 42: { { double rxy=sqrt(zx*zx+zy*zy+1e-21); aux.DE*=(1.0+af*aa*sin(ab*rxy+ac*zz2)); } break; }
						case 43: { aux.DE *= (1.0 + af * aa * cos(ab*zx+ac*zy+ad*zz2)); break; }
						case 44: { { double v=aa*sin(ab*r)+ac*cos(ad*r); aux.DE*=(1.0+af*v*0.5); } break; }
						case 45: { aux.DE *= fmax(0.01, 1.0 + af * aa * pow(fabs(sin(ab*r)), ac)); break; }
						case 46: { aux.DE *= (1.0 + af * aa * sin(ab*r*r/(r+1e-21))); break; }
						case 47: { { double f=aa+ab*sin(ac*i); aux.DE*=(1.0+af*f); } break; }
						case 48: { { double rr2=rr; double minR=aa; double fixR=ab; if(rr2<minR*minR){double m=fixR*fixR/(minR*minR);aux.DE*=m;} else if(rr2<fixR*fixR){double m=fixR*fixR/rr2;aux.DE*=m;} aux.DE*=(1.0+af*ac*sin(ad*r)); } break; }
						case 49: { aux.DE *= (1.0 + af * aa * (sin(ab*r) + cos(ac*r*r/(r+1e-21))) * 0.5); break; }
						case 50: { { double d=fabs(r-aa); double ring=exp(-ab*d*d); aux.DE*=(1.0+af*ac*ring); } break; }
						case 51: { aux.DE *= fabs(aa); break; }
						case 52: { aux.DE *= fabs(aa + ab*sin(ac*i)); break; }
						case 53: { aux.DE *= fabs(aa * pow(ab, ac)); break; }
						case 54: { aux.DE *= fabs(aa + ab * r); break; }
						case 55: { aux.DE *= fmax(0.01, fabs(aa + ab * sin(ac * r))); break; }
						case 56: { aux.DE *= fabs(aa + ab * exp(-ac * i)); break; }
						case 57: { aux.DE *= fabs(aa + ab * log(1.0 + ac * i)); break; }
						case 58: { { double golden=1.6180339887; aux.DE*=fabs(aa+ab*pow(golden,ac*i-ad)); } break; }
						case 59: { aux.DE *= fabs(aa + ab * sin(ac * i) * cos(ad * r)); break; }
						case 60: { { double s=aa+ab*tanh(ac*(i-ad)); aux.DE*=fabs(s); } break; }
						case 61: { aux.DE *= fmax(0.01, fabs(aa + ab * fmod(double(i) * ac, ad))); break; }
						case 62: { aux.DE *= fabs(aa + ab / (1.0 + ac * i)); break; }
						case 63: { { double ph=atan2(zy,zx); aux.DE*=fabs(aa+ab*sin(ac*ph)); } break; }
						case 64: { aux.DE *= fabs(aa + ab * (zx*zx - zy*zy) / (rr + 1e-21)); break; }
						case 65: { aux.DE *= fabs(aa + ab * sin(ac * i * M_PI / ad)); break; }
						case 66: { { double s=aa*(1.0+ab*sin(ac*double(i))); aux.DE*=fabs(s); } break; }
						case 67: { aux.DE *= fabs(aa + ab * fabs(sin(ac * r + ad * i))); break; }
						case 68: { { double s=aa+ab*cos(ac*r)*sin(ad*i*0.1); aux.DE*=fabs(s); } break; }
						case 69: { aux.DE *= fabs(aa + ab * (sin(ac*zx)+sin(ad*zy)+sin(ae*zz2))/3.0); break; }
						case 70: { { double rat=aa/fmax(ab,1e-21); double s=pow(fabs(rat),ac); aux.DE*=s; } break; }
						case 71: { aux.DE *= fmax(0.01, fabs(aa * exp(-ab * fabs(sin(ac * r))))); break; }
						case 72: { { double s=aa+ab*pow(fabs(sin(ac*r)),ad); aux.DE*=fabs(s); } break; }
						case 73: { aux.DE *= fabs(aa + ab * tanh(ac * sin(ad * r))); break; }
						case 74: { { double mix=0.5+0.5*sin(ac*i); double s=aa*(1.0-mix)+ab*mix; aux.DE*=fabs(s); } break; }
						case 75: { aux.DE *= fabs(aa + ab * sin(ac * r) * log(1.0 + ad * r)); break; }
						case 76: { { double a=aa*M_PI/180.0; aux.DE*=(1.0+af*fabs(sin(a))); } break; }
						case 77: { { double a=aa*M_PI/180.0+ab*sin(ac*i); aux.DE*=(1.0+af*fabs(sin(a))); } break; }
						case 78: { aux.DE *= (1.0 + af * aa * sin(ab*atan2(zy,zx))); break; }
						case 79: { aux.DE *= (1.0 + af * aa * cos(ab*atan2(zy,zx)+ac*acos(zz2/r))); break; }
						case 80: { { double ph=atan2(zy,zx); double n=fmax(1.0,aa); double s=2.0*M_PI/n; double sector=fmod(ph+10.0*M_PI,s)/s; aux.DE*=(1.0+af*ab*sin(M_PI*sector)); } break; }
						case 81: { aux.DE *= (1.0 + af * aa * fabs(sin(ab * atan2(zz2, sqrt(zx*zx+zy*zy+1e-21))))); break; }
						case 82: { { double q1=zx*cos(aa)-zy*sin(aa); double q2=zx*sin(aa)+zy*cos(aa); aux.DE*=(1.0+af*ab*sin(ac*q1)*cos(ad*q2)); } break; }
						case 83: { aux.DE *= (1.0 + af * aa * cos(ab * (zx+zy+zz2))); break; }
						case 84: { { double cs=cos(aa*M_PI/180.0),sn=sin(aa*M_PI/180.0); double rxy=sqrt(zx*zx+zy*zy+1e-21); double nph=atan2(zy,zx)+ab*sin(ac*rxy); aux.DE*=(1.0+af*ad*sin(ae*nph)); } break; }
						case 85: { aux.DE *= (1.0 + af * aa * sin(ab*(zx*zy+zy*zz2+zz2*zx)/(rr+1e-21))); break; }
						case 86: { { double gld=aa*0.618033988749895; aux.DE*=(1.0+af*ab*sin(ac*gld*i)); } break; }
						case 87: { aux.DE *= (1.0 + af * aa * sin(ab*r+ac*atan2(zy,zx)+ad*i*0.1)); break; }
						case 88: { { double sw=fabs(zx)>fabs(zy)?zx:zy; aux.DE*=(1.0+af*aa*sin(ab*sw)); } break; }
						case 89: { aux.DE *= (1.0 + af * aa * cos(ab*zx*zy/(r+1e-21))); break; }
						case 90: { { double fld=aa*(fabs(zx)+fabs(zy)+fabs(zz2)); aux.DE*=(1.0+af*ab*sin(fld)); } break; }
						case 91: { aux.DE *= (1.0 + af * aa * sin(ab*i) * cos(ac*r) * sin(ad*atan2(zy,zx))); break; }
						case 92: { { double sym=fabs(zx-zy)+fabs(zy-zz2)+fabs(zz2-zx); aux.DE*=(1.0+af*aa*sin(ab*sym)); } break; }
						case 93: { aux.DE *= (1.0 + af * aa * tanh(ab*sin(ac*atan2(zy,zx)))); break; }
						case 94: { { double det=zx*zy-zy*zz2+zz2*zx; aux.DE*=(1.0+af*aa*sin(ab*det/(rr+1e-21))); } break; }
						case 95: { aux.DE *= (1.0 + af * aa * sin(ab*r) * sin(ac*atan2(zy,zx)+ad*acos(zz2/r))); break; }
						case 96: { { double tw=aa*zz2+ab; double cs=cos(tw),sn=sin(tw); aux.DE*=(1.0+af*ac*fabs(sn)); } break; }
						case 97: { aux.DE *= (1.0 + af * aa * fabs(sin(ab*zx))*fabs(sin(ac*zy))*fabs(sin(ad*zz2))); break; }
						case 98: { { double mir=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.DE*=(1.0+af*aa*sin(ab*mir)); } break; }
						case 99: { { double mx=fmax(fabs(zx),fmax(fabs(zy),fabs(zz2))); aux.DE*=(1.0+af*aa*cos(ab*mx)); } break; }
						case 100: { aux.DE *= (1.0 + af * aa * sin(ab*r+ac*sin(ad*r))); break; }
						case 101: { { double w=aa*sin(ab*r); aux.DE*=(1.0+af*ac*fabs(w)); } break; }
						case 102: { { double r4=sqrt(rr+aa*aa*sin(ab*r)*sin(ab*r)); aux.DE*=(1.0+af*ac*(r4-r)/(r+1e-21)); } break; }
						case 103: { { double w=aa*cos(ab*zx+ac*zy); aux.DE*=(1.0+af*ad*w*w); } break; }
						case 104: { { double w=aa*sin(ab*i*0.1); double r4=sqrt(rr+w*w); aux.DE*=(1.0+af*ac*sin(ad*r4)); } break; }
						case 105: { aux.DE *= (1.0 + af * aa * sin(ab*(zx*zx+zy*zy-zz2*zz2)/(rr+1e-21))); break; }
						case 106: { { double w=aa*sin(ab*r+ac*i*0.1); aux.DE*=(1.0+af*ad*exp(-ae*w*w)); } break; }
						case 107: { { double q=zx*zx-zy*zy; double s=2.0*zx*zy; aux.DE*=(1.0+af*aa*sin(ab*q/(rr+1e-21))*cos(ac*s/(rr+1e-21))); } break; }
						case 108: { aux.DE *= (1.0 + af * aa * sin(ab*(zx*zy+ac*zz2))); break; }
						case 109: { { double hd=sin(aa*zx)*cos(ab*zy)+sin(ac*zy)*cos(ad*zz2)+sin(ae*zz2)*cos(aff*zx); aux.DE*=(1.0+af*ag*hd/3.0); } break; }
						case 110: { { double cr=zx*zx+zy*zy; double ci=2.0*zx*zy; double r4=sqrt(cr*cr+ci*ci+zz2*zz2); aux.DE*=(1.0+af*aa*sin(ab*r4)); } break; }
						case 111: { aux.DE *= (1.0 + af * aa * tanh(ab*(zx*zx+zy*zy-zz2*zz2))); break; }
						case 112: { aux.DE *= (1.0 + af * aa * sin(ab*zx+ac) * sin(ad*zy+ae) * cos(aff*zz2)); break; }
						case 113: { { double p=aa*zx*zy*zz2/(r*r*r+1e-21); aux.DE*=(1.0+af*ab*sin(ac*p)); } break; }
						case 114: { { double s1=sin(aa*r),s2=sin(ab*r); double w=s1*s1-s2*s2; aux.DE*=(1.0+af*ac*w); } break; }
						case 115: { aux.DE *= (1.0 + af * aa * cos(ab*r*r/(r+1e-21)+ac*sin(ad*r))); break; }
						case 116: { { double w=aa*sin(ab*(zx+zy+zz2))+ac*cos(ad*(zx-zy+zz2)); aux.DE*=(1.0+af*w*0.5); } break; }
						case 117: { aux.DE *= (1.0 + af * aa * sin(ab*zx*zx/(rr+1e-21)+ac*zy*zy/(rr+1e-21))); break; }
						case 118: { { double v=aa*sin(ab*r)+ac*sin(ad*r)+ae*sin(aff*r); aux.DE*=(1.0+af*v/3.0); } break; }
						case 119: { aux.DE *= (1.0 + af * aa * exp(-ab*fabs(zx*zy*zz2)/(r*r*r+1e-21))); break; }
						case 120: { { double w=aa+ab*sin(ac*r+ad*sin(ae*r)); aux.DE*=(1.0+af*w); } break; }
						case 121: { aux.DE *= (1.0 + af * aa * sin(ab*(r - floor(r*ac)/ac))); break; }
						case 122: { { double ph4=atan2(zz2,sqrt(zx*zx+zy*zy+1e-21)); aux.DE*=(1.0+af*aa*sin(ab*ph4+ac*r)); } break; }
						case 123: { aux.DE *= (1.0 + af * aa * fabs(sin(ab*r)*cos(ac*r)*sin(ad*r))); break; }
						case 124: { { double v=aa*sin(ab*zx)*cos(ac*zx)+ad*sin(ae*zy)*cos(aff*zy); aux.DE*=(1.0+af*v*0.5); } break; }
						case 125: { aux.DE *= (1.0 + af * aa * (sin(ab*r)+sin(ac*r)+sin(ad*r)+sin(ae*r))/4.0); break; }
						case 126: { aux.DE *= (1.0 + af * aa * fabs(zx)/(r+1e-21)); break; }
						case 127: { aux.DE *= (1.0 + af * aa * fabs(zy)/(r+1e-21)); break; }
						case 128: { aux.DE *= (1.0 + af * aa * fabs(zz2)/(r+1e-21)); break; }
						case 129: { { double orb=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.DE*=(1.0+af*aa*sin(ab*orb)); } break; }
						case 130: { { double orb=fmax(fabs(zx),fmax(fabs(zy),fabs(zz2))); aux.DE*=(1.0+af*aa*cos(ab*orb)); } break; }
						case 131: { { double orb=sqrt(zx*zx+zy*zy); aux.DE*=(1.0+af*aa*sin(ab*orb)); } break; }
						case 132: { { double dt=fabs(sqrt(zx*zx+zy*zy)-aa); aux.DE*=(1.0+af*ab*exp(-ac*dt*dt)); } break; }
						case 133: { { double ds=fmax(fabs(zx)-aa,fabs(zy)-ab); ds=fmax(ds,fabs(zz2)-ac); aux.DE*=(1.0+af*ad*exp(-ae*ds*ds)); } break; }
						case 134: { { double dp=fabs(zx*cos(aa)+zy*sin(aa)-ab); aux.DE*=(1.0+af*ac*exp(-ad*dp*dp)); } break; }
						case 135: { { double dl=fabs(zx-aa*zy-ab); aux.DE*=(1.0+af*ac*exp(-ad*dl*dl)); } break; }
						case 136: { { double c=fabs(sin(aa*zx)+sin(ab*zy)+sin(ac*zz2))/3.0; aux.DE*=(1.0+af*ad*c); } break; }
						case 137: { { double c=fabs(sin(aa*r)*cos(ab*atan2(zy,zx))); aux.DE*=(1.0+af*ac*c); } break; }
						case 138: { { double c=fabs(zx*zy+zy*zz2+zz2*zx)/(rr+1e-21); aux.DE*=(1.0+af*aa*c); } break; }
						case 139: { { double h=atan2(zy,zx)/(2.0*M_PI)+0.5; aux.DE*=(1.0+af*aa*sin(ab*h*M_PI*2.0)); } break; }
						case 140: { { double s=r/(r+aa); aux.DE*=(1.0+af*ab*s); } break; }
						case 141: { { double v=sin(aa*zx)*sin(ab*zy)+sin(ac*zy)*sin(ad*zz2); aux.DE*=(1.0+af*ae*v*0.5); } break; }
						case 142: { { double orb=fabs(zx-floor(zx*aa)/aa)*fabs(zy-floor(zy*ab)/ab); aux.DE*=(1.0+af*ac*sin(ad*orb)); } break; }
						case 143: { aux.DE *= (1.0 + af * aa * sin(ab * (fabs(zx)+fabs(zy)+fabs(zz2)))); break; }
						case 144: { { double d2=fabs(zx*zx/fmax(aa*aa,0.01)+zy*zy/fmax(ab*ab,0.01)-1.0); aux.DE*=(1.0+af*ac*exp(-ad*d2)); } break; }
						case 145: { { double sp=zx*cos(aa*zy)+zy*cos(aa*zz2)+zz2*cos(aa*zx); aux.DE*=(1.0+af*ab*sin(ac*sp)); } break; }
						case 146: { { double cl=sin(aa*in.point.Length()+ab*r); aux.DE*=(1.0+af*ac*cl); } break; }
						case 147: { { double it=double(i)/fmax(double(aa),1.0); aux.DE*=(1.0+af*ab*sin(ac*it*M_PI)); } break; }
						case 148: { { double gr=sin(aa*zx*zy/(r+1e-21))+cos(ab*zy*zz2/(r+1e-21)); aux.DE*=(1.0+af*ac*gr*0.5); } break; }
						case 149: { { double pat=sin(aa*zx)*cos(ab*zy)*sin(ac*zz2)*cos(ad*r); aux.DE*=(1.0+af*ae*pat); } break; }
						case 150: { { double comb=aa*sin(ab*r)+ac*cos(ad*atan2(zy,zx))+ae*sin(aff*acos(zz2/r)); aux.DE*=(1.0+af*comb/3.0); } break; }
						case 151: { { double de=aa*r*log(r+1e-21)/fmax(ab,0.01); aux.DE*=(1.0+af*de/(r+1e-21)); } break; }
						case 152: { aux.DE *= fmax(0.01, 1.0 + af * aa * r * sin(ab*log(r+1e-21)+ac)); break; }
						case 153: { { double lip=aa*fmin(1.0,ab/fmax(r,1e-21)); aux.DE*=(1.0+af*lip); } break; }
						case 154: { aux.DE *= (1.0 + af * aa * exp(-ab*r) * sin(ac*r+ad)); break; }
						case 155: { { double bess=sin(aa*r)/(aa*r+1e-21); aux.DE*=(1.0+af*ab*bess); } break; }
						case 156: { { double cheb=cos(aa*acos(fmin(1.0,fmax(-1.0,zz2/r)))); aux.DE*=(1.0+af*ab*cheb); } break; }
						case 157: { { double leg=(3.0*(zz2/r)*(zz2/r)-1.0)*0.5; aux.DE*=(1.0+af*aa*leg); } break; }
						case 158: { { double herm=(4.0*(zz2/r)*(zz2/r)-2.0)*exp(-(zz2/r)*(zz2/r)*0.5); aux.DE*=(1.0+af*aa*ab*herm); } break; }
						case 159: { { double lag=1.0-aa*r+aa*aa*r*r*0.5; aux.DE*=(1.0+af*ab*lag*exp(-ac*r)); } break; }
						case 160: { aux.DE *= (1.0 + af * aa * sin(ab*r+ac) * sin(ad*r+ae) * sin(aff*r+ag)); break; }
						case 161: { { double gr=aa*r*exp(-ab*r*r)*sin(ac*r); aux.DE*=(1.0+af*gr); } break; }
						case 162: { aux.DE *= (1.0 + af * aa * sin(ab*r) * tanh(ac*r)); break; }
						case 163: { { double sg=1.0/(1.0+exp(-aa*(r-ab))); aux.DE*=(1.0+af*ac*sg*(1.0-sg)); } break; }
						case 164: { { double gau=exp(-aa*(r-ab)*(r-ab)); aux.DE*=(1.0+af*ac*gau); } break; }
						case 165: { { double stp=(r>aa)?ab:ac; aux.DE*=(1.0+af*stp); } break; }
						case 166: { { double bnd=aa*sin(floor(r*ab)*M_PI/ab); aux.DE*=(1.0+af*bnd); } break; }
						case 167: { { double v=0; for(int o=0;o<4;o++){v+=sin(aa*pow(2.0,o)*r+ab*o)/(pow(2.0,o));} aux.DE*=(1.0+af*ac*v); } break; }
						case 168: { { double jc=aa*sin(ab*r)+ac*sin(ad*atan2(zy,zx)); aux.DE*=(1.0+af*jc*0.5); } break; }
						case 169: { { double tmp=aa+ab*sin(ac*r)*cos(ad*i*0.1); aux.DE*=(1.0+af*tmp); } break; }
						case 170: { { double fb=0; double prev=aa; double curr=ab; for(int k=0;k<6;k++){double nxt=prev+curr; fb+=sin(nxt*r)/(nxt+1.0); prev=curr; curr=nxt;} aux.DE*=(1.0+af*ac*fb); } break; }
						case 171: { { double orb=r; double v=aa*sin(ab*orb)+ac*cos(ad*orb*orb/(r+1e-21)); aux.DE*=(1.0+af*v); } break; }
						case 172: { aux.DE *= (1.0 + af * aa * fabs(sin(ab*r)) * fabs(cos(ac*r))); break; }
						case 173: { aux.DE *= fabs(aa); break; }
						case 174: { aux.DE *= (1.0 + fabs(aa*M_PI/180.0) * ab); break; }
						case 175: { aux.DE *= (1.0 + fabs(aa + ab + ac)); break; }
						case 176: { aux.DE *= fmax(0.01, aa * double(i) / fmax(double(ab), 1.0)); break; }
						case 177: { { if(fabs(zx)>aa||fabs(zy)>aa||fabs(zz2)>aa) aux.DE*=ab; } break; }
						case 178: { { double d=sqrt((zx-aa)*(zx-aa)+(zy-ab)*(zy-ab)+(zz2-ac)*(zz2-ac)); if(d<ad) aux.DE*=ae; } break; }
						case 179: { { if(fabs(zx)<aa && fabs(zy)<aa) aux.DE*=ab; } break; }
						case 180: { aux.DE *= (1.0 + 0.1 * aa * fabs(sin(ab*r))); break; }
						case 181: { aux.DE *= (1.0 - aa * ab * exp(-ac*r)); break; }
						case 182: { aux.DE /= fmax(0.01, 1.0 + aa * ab); break; }
						case 183: { aux.DE *= (1.0 + aa * ab * r); break; }
						case 184: { aux.DE /= fmax(0.01, 1.0 + aa * ab * sin(ac*r)); break; }
						case 185: { aux.DE *= (1.0 + aa * ab * r); break; }
						case 186: { aux.DE *= (1.0 + aa * fabs(ab - 550.0) * 0.001); break; }
						case 187: { aux.DE *= (1.0 + aa * fabs(sin(ab*zx)*cos(ac*zy))); break; }
						case 188: { { double fr=pow(fabs(1.0-fabs(zz2)/r),5.0); aux.DE*=(1.0+aa*fr); } break; }
						case 189: { { double tf=sin(aa*r+ab)*cos(ac*r); aux.DE*=(1.0+ad*fabs(tf)); } break; }
						case 190: { { double an=fabs(zx*aa+zy*ab+zz2*ac)/(r+1e-21); aux.DE*=(1.0+ad*an); } break; }
						case 191: { aux.DE /= fmax(0.01, 1.0 + aa * ab); break; }
						case 192: { aux.DE *= (1.0 + aa * exp(-ab * r)); break; }
						case 193: { aux.DE *= (1.0 + aa * ab * r); break; }
						case 194: { aux.DE += aa * ab * sin(ac*zx)*cos(ad*zy); break; }
						case 195: { aux.DE *= (1.0 + aa * ab * sin(ac*zx+ad*zy+ae*zz2)); break; }
						case 196: { aux.DE *= fmax(0.01, aa * ab / fmax(ac, 0.01)); break; }
						case 197: { aux.DE /= fmax(0.01, aa); break; }
						case 198: { aux.DE *= exp(-aa * ab * r); break; }
						case 199: { aux.DE *= (1.0 + aa * ab * (1.0 + ac*cos(ad*atan2(zy,zx)))); break; }
						case 200: { aux.DE /= fmax(0.01, 1.0 + aa * ab); break; }
						case 201: { { double curl=sin(aa*zy+ab*zz2)-sin(aa*zz2+ab*zx); aux.DE*=(1.0+ac*fabs(curl)); } break; }
						case 202: { { double grad=(zx*aa+zy*ab+zz2*ac)/(rr+1e-21); aux.DE/=fmax(0.01,1.0+ad*fabs(grad)); } break; }
						case 203: { aux.DE *= (1.0 + aa * ab / fmax(rr, 1e-21)); break; }
						case 204: { { double v2=aa*aa; double c2=ab*ab; aux.DE*=sqrt(fmax(0.01,1.0-v2/fmax(c2,1e-21))); } break; }
						case 205: { aux.DE *= exp(-aa * fabs(r - ab)); break; }
						case 206: { { double psi=sin(aa*zx)*sin(ab*zy)*sin(ac*zz2); aux.DE*=fmax(0.01,psi*psi); } break; }
						case 207: { aux.DE *= (1.0 + aa / fmax(2.0 * ab * r, 1e-21)); break; }
						case 208: { aux.DE *= (1.0 + aa * (zx*ab + zy*ac + zz2*ad)/(r+1e-21)); break; }
						case 209: { { double corr=sin(aa*zx)*sin(aa*(-zx))+cos(ab*zy)*cos(ab*(-zy)); aux.DE*=(1.0+ac*fabs(corr)); } break; }
						case 210: { aux.DE *= exp(-aa * ab * double(i) * 0.01); break; }
						case 211: { { double ent=sin(aa*zx)*log(fabs(sin(aa*zx))+1e-21)+sin(ab*zy)*log(fabs(sin(ab*zy))+1e-21); aux.DE*=(1.0+ac*fabs(ent)*0.1); } break; }
						case 212: { aux.DE *= (1.0 + aa / fmax(ab * ac, 1e-21)); break; }
						case 213: { { double vg=(sin(aa*(zx+0.01))-sin(aa*zx))/0.01; aux.DE*=(1.0+ab*fabs(vg)); } break; }
						case 214: { { double curv=(sin(aa*zx+0.01)+sin(aa*zx-0.01)-2.0*sin(aa*zx))/0.0001; aux.DE*=(1.0+ab*fabs(curv)); } break; }
						case 215: { aux.DE *= (1.0 + aa * cos(ab) / fmax(ac, 0.01)); break; }
						case 216: { { double cg=(sin(aa*(zx+0.01))-sin(aa*zx))/0.01; aux.DE*=(1.0+ab*fabs(cg)); } break; }
						case 217: { { double lap=sin(aa*(zx+0.01))+sin(aa*(zx-0.01))-2.0*sin(aa*zx); aux.DE+=ab*lap; } break; }
						case 218: { { double adv=(sin(aa*zx)-sin(aa*(zx-0.01)))/0.01; aux.DE*=(1.0+ab*fabs(adv)); } break; }
						case 219: { { double v=0; for(int o=0;o<4;o++){v+=sin(aa*pow(2.0,o)*r)/pow(2.0,o);} aux.DE*=(1.0+ab*fabs(v)); } break; }
						case 220: { { double sh=(r>aa)?ab:0.0; aux.DE*=(1.0+ac*sh); } break; }
						case 221: { { double dw=aa-ab; double bw=ac*0.5; double q=ad/fmax(sqrt(dw*dw+bw*bw),1e-21); aux.DE*=(1.0+af*q); } break; }
						case 222: { aux.DE *= (1.0 + aa * cos(ab * r + ac)); break; }
						case 223: { aux.DE *= (1.0 + aa / fmax(ab, 1e-21) * cos(ac)); break; }
						case 224: { aux.DE *= (1.0 + aa * cos(2.0 * ab * atan2(zy, zx))); break; }
						case 225: { aux.DE *= (1.0 + aa * fabs(sin(2.0 * ab * atan2(zz2, sqrt(zx*zx+zy*zy+1e-21))))); break; }
						case 226: { aux.DE *= (1.0 + aa * ab * ac); break; }
						case 227: { { double lp=fmod(r*aa, ab); aux.DE*=(1.0+ac*sin(M_PI*lp/fmax(ab,0.01))); } break; }
						case 228: { { double skin=exp(-fabs(zz2)*aa/fmax(ab,0.01)); aux.DE*=(1.0+ac*skin); } break; }
						case 229: { aux.DE *= (1.0 + aa * fabs(ab)); break; }
						case 230: { { double wn=floor(atan2(zy,zx)*aa/(2.0*M_PI)+0.5); aux.DE*=(1.0+ab*fabs(wn)); } break; }
						case 231: { { double tc=floor(atan2(zy,zx)*aa/(2.0*M_PI)+0.5); aux.DE*=(1.0+ab*fabs(tc)*sin(ac*r)); } break; }
						case 232: { { double vort=fabs(-aa*zy/(rr+1e-21)-(-ab*zx/(rr+1e-21))); aux.DE*=(1.0+ac*vort); } break; }
						case 233: { { double sw=1.0/cosh(aa*fabs(r-ab)); aux.DE*=(1.0+ac*sw); } break; }
						case 234: { { double inst=exp(-aa*(rr+1e-21)); aux.DE*=(1.0+ab*inst); } break; }
						case 235: { aux.DE *= (1.0 + aa / fmax(r, 1e-21)); break; }
						case 236: { { double sl=fabs(sqrt(zx*zx+zy*zy)); aux.DE*=(1.0+aa*log(sl+1e-21)*ab); } break; }
						case 237: { { double bd=exp(-aa*fabs(zz2-ab)); aux.DE*=(1.0+ac*bd); } break; }
						case 238: { { double wh=exp(-(r-aa)*(r-aa)/(fmax(ab*ab,0.01))); aux.DE*=(1.0+ac*wh); } break; }
						case 239: { aux.DE /= fmax(0.01, 1.0 - aa / fmax(r, aa + 1e-21)); break; }
						case 240: { { double jet=exp(-fabs(sqrt(zx*zx+zy*zy)-aa)/(fmax(ab,0.01))); aux.DE*=(1.0+ac*jet); } break; }
						case 241: { { double halo=1.0/(1.0+pow(r/fmax(aa,0.01),2.0)); aux.DE*=(1.0+ab*halo); } break; }
						case 242: { aux.DE *= exp(aa * ab * r); break; }
						case 243: { { double cs2=log(fmax(fabs(sqrt(zx*zx+zy*zy)),1e-21)/fmax(aa,0.01)); aux.DE*=(1.0+ab*ac*cs2); } break; }
						case 244: { aux.DE *= (1.0 + aa * tanh(fabs(zz2 - ab) / fmax(ac, 0.01))); break; }
						case 245: { { double ylm=sin(aa*acos(zz2/r))*cos(ab*atan2(zy,zx)); aux.DE*=(1.0+ac*fabs(ylm)); } break; }
						case 246: { aux.DE *= exp(aa * ab); break; }
						case 247: { { double rh=aa*ab*exp(-ac*double(i)*0.01); aux.DE*=(1.0+rh); } break; }
						case 248: { { double ns=aa*ab*sin(ac*r)/(1.0+ad*r); aux.DE*=(1.0+ns); } break; }
						case 249: { { double rc=aa*exp(-ab/(fmax(ac*r,0.01))); aux.DE*=(1.0+rc); } break; }
						case 250: { { double sf2=1.0+aa*r; aux.DE*=sf2*sqrt(fmax(0.01,ab*ac/(fmax(r,1e-21)))); } break; }
						case 251: { { double sf2=fmax(0.01,1.0+aa*r); aux.DE/=sf2; } break; }
						case 252: { aux.DE *= (1.0 + aa * (1.0 - exp(-double(i) * 0.01 / fmax(ab, 0.01)))); break; }
						case 253: { { double bn=exp(-aa*rr)*ab; aux.DE*=(1.0+bn); } break; }
						case 254: { { double fv=aa*exp(-ab*rr); aux.DE*=(1.0+fv); } break; }
						case 255: { { double op=sin(aa*r)*sin(aa*r); aux.DE*=(1.0+ab*op); } break; }
						case 256: { { double d=fabs(r-aa); aux.DE*=fmax(0.01,pow(d+1e-21,-ab)); } break; }
						case 257: { aux.DE *= (1.0 + aa * log(fmax(ab, 0.01) / fmax(r, 1e-21))); break; }
						case 258: { { double div=(sin(aa*(zx+0.01))-sin(aa*zx))/0.01; aux.DE*=(1.0+ab*fabs(div)); } break; }
						case 259: { { double vev=aa*r*r; aux.DE*=(1.0+ab*vev); } break; }
						case 260: { { double grd=(sin(aa*(r+0.01))-sin(aa*r))/0.01; aux.DE*=(1.0+ab*fabs(grd)); } break; }
						case 261: { aux.DE *= (1.0 + aa * ab * rr); break; }
						case 262: { { double a2=sin(aa*zx)*sin(aa*zx)+sin(ab*zy)*sin(ab*zy); aux.DE*=(1.0+ac*ad*a2); } break; }
						case 263: { { double psi2=sin(aa*r)*sin(aa*r); aux.DE*=(1.0+ab*psi2); } break; }
						case 264: { { double phi=sin(aa*r); aux.DE*=(1.0+ab*phi*phi+ac*phi*phi*phi*phi); } break; }
						case 265: { { double tmn=(zx*zx+zy*zy+zz2*zz2)/(rr+1e-21); aux.DE*=(1.0+aa*ab*tmn); } break; }
						case 266: { { double sp=sin(aa*zx)*cos(ab*zy); aux.DE*=(1.0+ac*fabs(sp)); } break; }
						case 267: { { double rs=sin(aa*r)*fabs(cos(ab*atan2(zy,zx))); aux.DE*=(1.0+ac*rs*rs); } break; }
						case 268: { { double kr=sin(aa*zx)*sin(ab*zy)-cos(aa*zx)*cos(ab*zy); aux.DE*=(1.0+ac*kr*kr); } break; }
						case 269: { { double gv=sin(aa*r)*sin(ab*r); aux.DE*=(1.0+ac*gv*gv); } break; }
						case 270: { { double xs=fabs(sin(aa*r)-zx); aux.DE*=(1.0+ab*xs*xs); } break; }
						case 271: { { double m5=sin(aa*r)*sin(ab*r)*sin(ac*r); aux.DE*=(1.0+ad*m5*m5); } break; }
						case 272: { { double wf2=exp(-aa*fabs(zz2)); aux.DE*=(1.0+ab*ac*wf2); } break; }
						case 273: { { double kk=sin(aa*r/fmax(ab,0.01))*sin(ac*r/fmax(ab,0.01)); aux.DE*=(1.0+ad*kk); } break; }
						case 274: { aux.DE *= exp(-aa * fabs(zz2 - ab)); break; }
						case 275: { { double av=r>1e-21?(fabs(zx)+fabs(zy)+fabs(zz2))/(r):1.0; aux.DE*=(1.0+aa*ab*av); } break; }
						case 276: { { double cf=1.0/(1.0+aa*rr); aux.DE*=(1.0+ab*cf); } break; }
						case 277: { { double ms=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.DE*=(1.0+aa*ms); } break; }
						case 278: { { double fw=exp(-aa*fabs(r-ab)*fabs(r-ab)*1000.0); aux.DE*=(1.0+ac*fw); } break; }
						case 279: { { double ee=sin(aa*zx)*sin(aa*(-zx+ab)); aux.DE*=(1.0+ac*fabs(ee)); } break; }
						case 280: { { double vol=r*r*r; aux.DE*=(1.0+aa*vol/(vol+ab+1e-21)); } break; }
						case 281: { { double ly=exp(aa*double(i)*0.01); aux.DE*=(1.0+ab*fmin(ly,ac)); } break; }
						case 282: { { double bv=fabs(zx-aa*sin(ab*zy))/(double(i)+1.0); aux.DE*=(1.0+ac*bv); } break; }
						case 283: { { double scr=log(fmax(aa,1.0))*ab*sin(ac*r); aux.DE*=(1.0+fabs(scr)*0.01); } break; }
						case 284: { { double sff=sin(aa*double(i)*0.1)*sin(ab*double(i)*0.1); aux.DE*=(1.0+ac*fabs(sff)); } break; }
						case 285: { { double goe=sin(aa*r)*cos(ab*r)*sin(ac*r); aux.DE*=(1.0+ad*fabs(goe)); } break; }
						case 286: { { double syk=sin(aa*zx)*sin(ab*zy)*sin(ac*zz2)*sin(ad*r); aux.DE*=(1.0+ae*fabs(syk)); } break; }
						case 287: { { double bd2=sin(aa*r)*sin(aa*r); double ent=bd2*log(bd2+1e-21); aux.DE*=(1.0+ab*fabs(ent)); } break; }
						case 288: { { double ml=floor(log(r+1e-21)/log(fmax(aa,1.01))); aux.DE*=(1.0+ab*sin(ac*ml)); } break; }
						case 289: { { double cd=floor(r*aa); double le=exp(-ab*cd); aux.DE*=(1.0+ac*le); } break; }
						case 290: { { double wn2=floor(atan2(zy,zx)*aa/(2.0*M_PI)+0.5); aux.DE*=(1.0+ab*sin(ac*wn2)); } break; }
						case 291: { { double sw2=floor(zx*aa+0.5)*floor(zy*ab+0.5); aux.DE*=(1.0+ac*sin(ad*sw2)); } break; }
						case 292: { { double cc=floor(r*aa)*3.0; aux.DE*=(1.0+ab*sin(ac*cc)); } break; }
						case 293: { { double pc=fmod(floor(r*aa),ab); aux.DE*=(1.0+ac*sin(ad*pc)); } break; }
						case 294: { { double ce=sin(aa*zx)*cos(ab*zy)*sin(ac*zz2); aux.DE*=(1.0+ad*fabs(ce)); } break; }
						case 295: { { double ev=sin(aa*r)*sin(aa*r)+cos(ab*r)*cos(ab*r); aux.DE*=(1.0+ac*ev*0.5); } break; }
						case 296: { { double sgn=sin(aa*r)>0?1.0:-1.0; double mc=exp(-ab*rr)*sgn; aux.DE*=(1.0+ac*fabs(mc)); } break; }
						case 297: { { double pur=sin(aa*r)*sin(aa*r); aux.DE*=(1.0+ab*pur*pur); } break; }
						case 298: { { double wig=sin(aa*zx)*cos(ab*zy); aux.DE*=(1.0+ac*fabs(wig)); } break; }
						case 299: { { double hus=exp(-aa*(zx*zx+zy*zy))*sin(ab*r); aux.DE*=(1.0+ac*fabs(hus)); } break; }
						case 300: { { double mi=sin(aa*r)*sin(ab*r); aux.DE*=(1.0+ac*mi*mi); } break; }
						case 301: { double psi = sin(aa*r + ab*z.x); aux.DE *= (1.0 + af * psi*psi); break; }
						case 302: { double psi_f = cos(aa*r); double psi_i = sin(ab*r); double overlap = psi_f*psi_i + 1e-21; double wv = (psi_f*sin(ac*z.x)) / overlap; aux.DE *= (1.0 + af * fabs(wv)); break; }
						case 303: { double rate = fabs(aa); double variance = z.x*z.x + z.y*z.y; aux.DE *= (1.0 + af * exp(-rate * (double)i * 0.01 * variance)); break; }
						case 304: { double E = aa*r; double t = (double)i * 0.01; aux.DE *= (1.0 + af * fabs(ab) * sin(E*t)*sin(E*t)); break; }
						case 305: { double path1 = sin(aa*z.x + ab*z.y); double path2 = sin(ac*z.x - ab*z.y); aux.DE *= (1.0 + af * fabs(path1 - path2)); break; }
						case 306: { double choice_time = fabs(aa) * 10.0; double theta = (double)i > choice_time ? 1.0 : 0.0; aux.DE *= (1.0 + af * ab * theta); break; }
						case 307: { double visibility = cos(aa*r)*cos(aa*r); double erased = sin(ab*z.x + ac*z.y); aux.DE *= (1.0 + af * visibility * erased*erased); break; }
						case 308: { double source = sin(aa*z.x + ab*z.y + ac*z.z); double target = sin(aa*(z.x+ad) + ab*(z.y+ae) + ac*(z.z+aff)); double fidelity = source*target; aux.DE *= (1.0 + af * fabs(fidelity)); break; }
						case 309: { double psi = sin(aa*r); double clone = sin(aa*r + ab*0.1); double fidelity = 1.0 - (psi-clone)*(psi-clone)*0.5; aux.DE *= (1.0 + af * fmax(fidelity, 0.0)); break; }
						case 310: { double Iz = sin(aa*z.x)*sin(ab*z.y); double classical = sin(aa*z.x)*0.5; double discord = fabs(Iz - classical); aux.DE *= (1.0 + af * discord); break; }
						case 311: { double epr = sin(aa*z.x)*cos(ab*z.y) - cos(aa*z.x)*sin(ab*z.y); aux.DE *= (1.0 + af * fabs(epr)); break; }
						case 312: { double v1 = sin(aa*z.x)*sin(aa*z.y); double v2 = cos(ab*z.y)*cos(ab*z.z); double violation = fabs(v1 + v2) - 1.0; aux.DE *= (1.0 + af * fmax(violation, 0.0)); break; }
						case 313: { double ca = cos(aa*z.x); double cb = cos(ab*z.y); double corr = ca*cb + ca*sin(ab*z.y) + sin(aa*z.x)*cb - sin(aa*z.x)*sin(ab*z.y); aux.DE *= (1.0 + af * fabs(corr) * 0.25); break; }
						case 314: { double S = 2.0*sqrt(2.0)*sin(aa*r)*cos(ab*r); double violation = fmax(fabs(S) - 2.0, 0.0); aux.DE *= (1.0 + af * violation); break; }
						case 315: { double bound = 2.0*sqrt(2.0); double corr = bound * cos(aa*r) * sin(ab*z.x); aux.DE *= (1.0 + af * fabs(corr) / bound); break; }
						case 316: { double t1 = sin(aa*(double)i*0.1); double t2 = sin(aa*((double)i+ab)*0.1); double temporal = t1*t2 + t1*sin(aa*((double)i+ac)*0.1); aux.DE *= (1.0 + af * fabs(temporal)); break; }
						case 317: { double rho = sin(aa*z.x)*sin(aa*z.x) + cos(ab*z.y)*cos(ab*z.y); double witness = rho - ac; aux.DE *= (1.0 + af * fmax(-witness, 0.0)); break; }
						case 318: { double dpsi = aa*cos(aa*r + ab*z.x); double fisher = 4.0*dpsi*dpsi; aux.DE *= (1.0 + af * fisher / (1.0 + fisher)); break; }
						case 319: { double F_Q = 4.0*(aa*cos(aa*r))*(aa*cos(aa*r)); double bound = 1.0/sqrt(fmax(ab*F_Q, 1e-21)); aux.DE *= (1.0 + af * bound); break; }
						case 320: { double N = fmax(fabs(aa)*10.0, 1.0); double dphi = 1.0/(N*sqrt(fmax(fabs(ab), 1e-21))); double sql = 1.0/sqrt(N); double gain = (sql*sql)/(dphi*dphi+1e-21); aux.DE *= (1.0 + af * fmin(gain, 10.0) * sin(ac*r)*sin(ac*r)); break; }
						case 321: { double T2 = fabs(aa) + 0.01; double sensitivity = 1.0/(ab*sqrt(T2)+1e-21); aux.DE *= (1.0 + af * sin(ac*r)*sin(ac*r) * fmin(sensitivity, 10.0)); break; }
						case 322: { double lambda_r = fabs(aa)+0.1; double NA = fabs(ab)+0.1; double N_ph = fmax(fabs(ac)*10, 1.0); double res = lambda_r/(2.0*NA*sqrt(N_ph)); aux.DE *= (1.0 + af * sin(r/fmax(res,0.01))*sin(r/fmax(res,0.01))); break; }
						case 323: { double N = fmax(fabs(aa)*5, 1.0); double pattern = sin(N*ab*z.x)*sin(N*ab*z.y); aux.DE *= (1.0 + af * pattern*pattern); break; }
						case 324: { double snr_q = exp(-aa*r*r); double snr_c = exp(-ab*r*r); double advantage = snr_q/(snr_c+1e-21); aux.DE *= (1.0 + af * fmin(advantage, 10.0)); break; }
						case 325: { double tau = fabs(aa)*r; double N_s = fmax(fabs(ab), 0.1); double N_i = fmax(fabs(ac), 0.1); double range_res = tau/(2.0*sqrt(N_s*N_i)+1e-21); aux.DE *= (1.0 + af * sin(range_res)*sin(range_res)); break; }
						case 326: { double omega_rot = aa*z.x + ab*z.y; double phase = ac*omega_rot; aux.DE *= (1.0 + af * sin(phase)*sin(phase)); break; }
						case 327: { double g_eff = aa; double T = fabs(ab)+0.01; double phase = g_eff*T*T*ac; aux.DE *= (1.0 + af * cos(phase)*cos(phase)); break; }
						case 328: { double omega0 = fabs(aa)*100.0+1.0; double tau_c = fabs(ab)+0.01; double stability = 1.0/(omega0*sqrt(tau_c*(double)(i+1)*0.01)+1e-21); aux.DE *= (1.0 + af * fmin(stability*ac, 5.0)); break; }
						case 329: { double B = aa*z.x + ab*z.y + ac*z.z; double sensitivity = sin(ad*B); aux.DE *= (1.0 + af * sensitivity*sensitivity); break; }
						case 330: { double k_eff = aa; double T = fabs(ab)+0.01; double accel = k_eff*T*T*ac*r; aux.DE *= (1.0 + af * sin(accel)*sin(accel)); break; }
						case 331: { double T_eff = fabs(aa)*r + 0.01; double C = fabs(ab)+0.1; double dE = fabs(ac)+0.01; double res = T_eff*T_eff/(C*dE); aux.DE *= (1.0 + af * fmin(res, 10.0)); break; }
						case 332: { double pressure = aa*r*r + ab*z.x; double sensitivity = sin(ac*pressure); aux.DE *= (1.0 + af * sensitivity*sensitivity); break; }
						case 333: { double dL = aa*(z.x - z.y); double L = fmax(r, 0.01); double strain = dL/L; double gauge = ab*strain; aux.DE *= (1.0 + af * sin(gauge)*sin(gauge)); break; }
						case 334: { double omega0 = fabs(aa)+0.1; double Q = fabs(ab)+1.0; double force = ac/(2.0*Q*omega0+1e-21); aux.DE *= (1.0 + af * sin(force*r)*sin(force*r)); break; }
						case 335: { double torque = aa*z.x*z.y - ab*z.y*z.z; double thermal = fabs(ac)+0.01; aux.DE *= (1.0 + af * fabs(torque)/(thermal+fabs(torque))); break; }
						case 336: { double E_field = aa*z.x + ab*z.y + ac*z.z; double rydberg = sin(ad*E_field*E_field); aux.DE *= (1.0 + af * rydberg*rydberg); break; }
						case 337: { double V_jj = aa*sin(ab*r); double josephson = cos(ac*V_jj); aux.DE *= (1.0 + af * (1.0 - josephson*josephson)); break; }
						case 338: { double tunnel = exp(-aa*fabs(r-ab)); double current = ac*tunnel; aux.DE *= (1.0 + af * fabs(current)); break; }
						case 339: { double n = floor(fabs(aa)*r*5.0+0.5); double R_H = 1.0/(fmax(n,1.0)*ab+1e-21); aux.DE *= (1.0 + af * fmin(R_H, 10.0)); break; }
						case 340: { double C_q = aa*aa/(2.0*(fabs(ab)+0.01)); double charging = exp(-C_q*r*r); aux.DE *= (1.0 + af * charging); break; }
						case 341: { double flux = aa*z.x*z.y; double inductance = cos(ab*flux); aux.DE *= (1.0 + af * inductance*inductance); break; }
						case 342: { double L_q = fabs(aa)+0.01; double C_q = fabs(ab)+0.01; double Z = sqrt(L_q/C_q); double match = 1.0/(1.0 + (Z-ac)*(Z-ac)); aux.DE *= (1.0 + af * match); break; }
						case 343: { double omega = aa*r; double n_th = 1.0/(exp(fabs(ab)*omega+1e-21)-1.0+1e-21); double psd = omega*(n_th+0.5); aux.DE *= (1.0 + af * fmin(fabs(psd), 10.0)); break; }
						case 344: { double dE = fabs(aa)*r; double tau = fmax(fabs(ab),0.01); double uncertainty = dE*tau; aux.DE *= (1.0 + af * exp(-uncertainty)); break; }
						case 345: { double W = aa*r*r; double T_eff = fmax(fabs(ab), 0.01); double jarzynski = exp(-W/T_eff); aux.DE *= (1.0 + af * jarzynski); break; }
						case 346: { double Q_heat = aa*r; double T_eff = fmax(fabs(ab), 0.01); double C = fmax(fabs(ac), 0.01); double fluct = Q_heat/(T_eff*T_eff*C+1e-21); aux.DE *= (1.0 + af * exp(-fabs(fluct))); break; }
						case 347: { double sigma = fabs(aa)*r*r; double relax = fmax(fabs(ab), 0.01); double prod = sigma/relax; aux.DE *= (1.0 + af * (1.0 - exp(-prod))); break; }
						case 348: { double W = aa*(z.x*z.x + z.y*z.y); double T_eff = fmax(fabs(ab), 0.01); double ratio = exp(-W/T_eff); aux.DE *= (1.0 + af * fmin(ratio, 10.0)); break; }
						case 349: { double info = fabs(sin(aa*z.x)*cos(ab*z.y)); double work = ac*info*log(2.0); aux.DE *= (1.0 + af * fabs(work)/(1.0+fabs(work))); break; }
						case 350: { double W = fabs(aa)*log(2.0)*sin(ab*r)*sin(ab*r); aux.DE *= (1.0 + af * W); break; }
						case 351: { double T_hot = fmax(fabs(aa)*r, 0.01); double T_cold = fmax(fabs(ab)*0.5, 0.001); double eff = 1.0 - T_cold/T_hot; double qcorr = sin(ac*r)*sin(ac*r); aux.DE *= (1.0 + af * fabs(eff) * qcorr); break; }
						case 352: { double w_cold = fabs(aa)+0.1; double w_hot = fabs(ab)+0.2; double eff = 1.0 - w_cold/w_hot; double adiabatic = cos(ac*r)*cos(ac*r); aux.DE *= (1.0 + af * fabs(eff) * adiabatic); break; }
						case 353: { double V_ratio = fmax(fabs(aa), 0.1)/fmax(fabs(ab), 0.1); double T_ratio = fmax(fabs(ac), 0.1)/fmax(fabs(ad), 0.1); double eff = log(V_ratio)/(log(T_ratio)+1e-21); aux.DE *= (1.0 + af * fmin(fabs(eff), 5.0) * sin(r)*sin(r)); break; }
						case 354: { double gamma_g = 1.4; double ratio = fmax(fabs(aa), 0.1); double eff = 1.0 - (pow(ratio, gamma_g)-1.0)/(gamma_g*(ratio-1.0)+1e-21); aux.DE *= (1.0 + af * fabs(eff) * sin(ab*r)*sin(ab*r)); break; }
						case 355: { double P_ratio = fmax(fabs(aa), 0.1); double gamma_g = 1.4; double eff = 1.0 - pow(1.0/P_ratio, (gamma_g-1.0)/gamma_g); aux.DE *= (1.0 + af * fabs(eff) * cos(ab*r)*cos(ab*r)); break; }
						case 356: { double T_ratio = fmax(fabs(aa)+0.1, 0.01) / fmax(fabs(ab)+0.1, 0.01); double regen = fmin(fabs(ac), 1.0); double eff = (1.0 - 1.0/T_ratio) * regen; aux.DE *= (1.0 + af * fabs(eff)); break; }
						case 357: { double expansion = fmax(fabs(aa), 0.1); double T_ratio = fmax(fabs(ab)+0.1, 0.01)/fmax(fabs(ac)+0.1, 0.01); double eff = (1.0 - 1.0/T_ratio)*expansion/(expansion+1.0); aux.DE *= (1.0 + af * fabs(eff) * sin(ad*r)*sin(ad*r)); break; }
						case 358: { double T_ratio = fmax(fabs(aa)+0.1,0.01)/fmax(fabs(ab)+0.1,0.01); double loss = 1.0-fmin(fabs(ac),0.99); double eff = (1.0-1.0/T_ratio)*loss; aux.DE *= (1.0 + af * fabs(eff) * cos(ad*r)*cos(ad*r)); break; }
						case 359: { double T_cold = fmax(fabs(aa),0.01); double T_hot = fmax(fabs(ab),0.02); double cop = T_cold/(T_hot-T_cold+1e-21); double qcop = cop*sin(ac*r)*sin(ac*r); aux.DE *= (1.0 + af * fmin(fabs(qcop),10.0)); break; }
						case 360: { double T_hot = fmax(fabs(aa),0.02); double T_cold = fmax(fabs(ab),0.01); double cop = T_hot/(T_hot-T_cold+1e-21); double enhance = cos(ac*r)*cos(ac*r); aux.DE *= (1.0 + af * fmin(cop*enhance,10.0)); break; }
						case 361: { double k = aa; double Gamma = fabs(ab)+0.01; double delta = fabs(ac)+0.01; double cooling = Gamma/(2.0*(1.0 + 4.0*delta*delta/(Gamma*Gamma))); aux.DE *= (1.0 + af * cooling * sin(k*r)*sin(k*r)); break; }
						case 362: { double U0 = aa; double delta = fabs(ab)+0.01; double pol_grad = sin(ac*z.x)*cos(ac*z.y); double eff = U0/(delta+1e-21)*pol_grad*pol_grad; aux.DE *= (1.0 + af * fmin(fabs(eff),10.0)); break; }
						case 363: { double T_ratio = fmax(fabs(aa),0.01)/fmax(fabs(ab),0.01); double eta = fabs(ac)+1.0; double eff = pow(T_ratio, 3.0)*eta; aux.DE *= (1.0 + af * fmin(fabs(eff),10.0) * sin(r)*sin(r)); break; }
						case 364: { double m_ratio = fmax(fabs(aa),0.1)/fmax(fabs(ab),0.1); double collision = fabs(ac); double eff = m_ratio*collision; aux.DE *= (1.0 + af * fmin(eff,10.0) * sin(ad*r)*sin(ad*r)); break; }
						case 365: { double eta = fabs(aa)*0.1; double Omega = fabs(ab)+0.1; double nu_m = fabs(ac)+0.1; double eff = eta*Omega*Omega/((fabs(ad)+0.01)*nu_m); aux.DE *= (1.0 + af * fmin(eff,10.0)); break; }
						case 366: { double Sxy = sin(aa*z.x)*cos(ab*z.y); double Sxx = sin(aa*z.x)*sin(aa*z.x)+0.01; double Syy = cos(ab*z.y)*cos(ab*z.y)+0.01; double gain = Sxy*Sxy/(Sxx*Syy); aux.DE *= (1.0 + af * fabs(gain)); break; }
						case 367: { double g = fabs(aa)+0.01; double kappa = fabs(ab)+0.01; double delta = fabs(ac)+0.01; double cooling = g*g/(kappa*kappa+delta*delta); double n_ph = sin(ad*r)*sin(ad*r)*10.0; aux.DE *= (1.0 + af * cooling*fmin(n_ph,10.0)); break; }
						case 368: { double Cg = fabs(aa)+0.01; double Vg = ab; double C = fabs(ac)+0.01; double coupling = Cg*Vg/C; aux.DE *= (1.0 + af * sin(coupling*r)*sin(coupling*r)); break; }
						case 369: { double S = aa; double sigma = fabs(ab)+0.01; double T_eff = fabs(ac)*r+0.01; double kappa = fabs(ad)+0.01; double ZT = S*S*sigma*T_eff/kappa; aux.DE *= (1.0 + af * fmin(ZT,10.0)); break; }
						case 370: { double Ss = aa; double gradT = ab*z.x+ac*z.y; double spin_pol = sin(ad*r); aux.DE *= (1.0 + af * fabs(Ss*gradT*spin_pol)); break; }
						case 371: { double Bz = aa; double gradT = ab*z.x; double Ey = ac*gradT*Bz; aux.DE *= (1.0 + af * sin(Ey)*sin(Ey)); break; }
						case 372: { double n_level = floor(fabs(aa)*r*5.0+0.5); double conductance = fmax(n_level,1.0)*ab; aux.DE *= (1.0 + af * fmin(fabs(conductance),10.0) * sin(ac*r)*sin(ac*r)); break; }
						case 373: { double edge = exp(-aa*fabs(z.x)); double helical = sin(ab*z.y); aux.DE *= (1.0 + af * edge * helical*helical); break; }
						case 374: { double chern = floor(fabs(aa)*2.0+0.5); double mag_order = sin(ab*z.x)*sin(ab*z.y); aux.DE *= (1.0 + af * fabs(chern) * mag_order*mag_order); break; }
						case 375: { double valley = sin(aa*z.x)*cos(ab*z.y) - cos(aa*z.x)*sin(ab*z.y); double broken_inv = sin(ac*r); aux.DE *= (1.0 + af * fabs(valley*broken_inv)); break; }
						case 376: { double bulk_gap = fabs(aa); double surface = sin(ab*z.x)*sin(ab*z.y)*exp(-ac*fabs(z.z)); double k_F = ad*r; aux.DE *= (1.0 + af * bulk_gap*fabs(surface)*fmin(k_F,5.0)); break; }
						case 377: { double kx = aa*z.x; double ky = ab*z.y; double kz = ac*z.z; double chirality = kx*kx + ky*ky - kz*kz; double fermi_arc = exp(-fabs(chirality)*ad); aux.DE *= (1.0 + af * fermi_arc); break; }
						case 378: { double E_D = aa; double v_F = fabs(ab)+0.01; double k = ac*r; double cone = fabs(E_D)/(v_F*fmax(fabs(k),0.01)); aux.DE *= (1.0 + af * fmin(cone,10.0) * sin(r)*sin(r)); break; }
						case 379: { double xi = fmax(fabs(aa),0.01); double L = fabs(ab)*r; double overlap = exp(-L/xi); double gap = fabs(ac); aux.DE *= (1.0 + af * overlap*gap); break; }
						case 380: { double J = fabs(aa)+0.01; double alpha = fabs(ab)+0.01; double g = fabs(ac)+0.01; double gap = J*exp(-1.0/(alpha*g)); aux.DE *= (1.0 + af * gap * sin(ad*r)*sin(ad*r)); break; }
						case 381: { double J = fabs(aa)+0.01; double h = fabs(ab)+0.01; double gap = fabs(J-h)/J; double crit_exp = fabs(ac)+0.5; aux.DE *= (1.0 + af * pow(fmax(gap,1e-10), crit_exp)); break; }
						case 382: { double J = aa; double Si = sin(ab*z.x); double Sj = sin(ab*z.y); double coupling = J*Si*Sj; aux.DE *= (1.0 + af * fabs(coupling)); break; }
						case 383: { double J = aa; double Sx = sin(ab*z.x)*cos(ac*z.y); double Sy = cos(ab*z.x)*sin(ac*z.y); double coupling = J*(Sx+Sy); aux.DE *= (1.0 + af * fabs(coupling)); break; }
						case 384: { double J = aa; double q = fmax(floor(fabs(ab)*5+2), 2.0); double sigma_i = floor(sin(ac*z.x)*q); double sigma_j = floor(sin(ac*z.y)*q); double delta_s = (sigma_i == sigma_j) ? 1.0 : 0.0; aux.DE *= (1.0 + af * J*delta_s); break; }
						case 385: { double J = aa; double q = fmax(floor(fabs(ab)*5+2), 2.0); double angle = 2.0*M_PI/q; double sigma_diff = sin(ac*z.x) - sin(ac*z.y); aux.DE *= (1.0 + af * J*cos(angle*sigma_diff)); break; }
						case 386: { double J = aa; double lambda = ab; double sigma = sin(ac*z.x)*sin(ac*z.y); double tau = cos(ad*z.x)*cos(ad*z.y); double coupling = J*(sigma + tau + lambda*sigma*tau); aux.DE *= (1.0 + af * fabs(coupling)); break; }
						case 387: { double W = aa; double X = ab; double Y = ac; double sigma = sin(ad*z.x)*sin(ad*z.y); double tau = cos(ad*z.x)*cos(ad*z.y); double v = W*sigma + X*tau + Y*sigma*tau; aux.DE *= (1.0 + af * fabs(v)); break; }
						case 388: { double U = fabs(aa)+0.01; double t = fabs(ab)+0.01; double n_up = sin(ac*z.x)*sin(ac*z.x); double n_down = cos(ac*z.y)*cos(ac*z.y); double mott = U*n_up*n_down/t; aux.DE *= (1.0 + af * fmin(mott,10.0)); break; }
						case 389: { double t = fabs(aa)+0.01; double J = ab; double hop = t*sin(ac*z.x)*cos(ac*z.y); double exchange = J*sin(ad*z.x)*sin(ad*z.y); aux.DE *= (1.0 + af * fabs(hop + exchange)); break; }
						case 390: { double xi_loc = fmax(fabs(aa),0.01); double disorder = fabs(ab); double loc = exp(-r/xi_loc)*disorder; aux.DE *= (1.0 + af * loc); break; }
						case 391: { double U = fabs(aa)+0.01; double U_c = fabs(ab)+0.01; double n = sin(ac*r)*0.5+0.5; double gap = (U/U_c)*(n-0.5)*(n-0.5); aux.DE *= (1.0 + af * fmin(gap*4.0,10.0)); break; }
						case 392: { double alpha = aa; double u = ab; double k_F = ac; double gap = 2.0*fabs(alpha*u)*fabs(cos(2.0*k_F*z.x)); aux.DE *= (1.0 + af * fmin(gap,10.0)); break; }
						case 393: { double J = fabs(aa)+0.01; double g = fabs(ab)+0.01; double gap = J*exp(-M_PI*J/(g*g)); double singlet = cos(ac*z.x)*cos(ac*z.y); aux.DE *= (1.0 + af * gap*singlet*singlet); break; }
						case 394: { double J = fabs(aa)+0.01; double S = fmax(floor(fabs(ab)+1),1.0); double gap = J*exp(-M_PI*S); double string_order = sin(ac*r); aux.DE *= (1.0 + af * gap*string_order*string_order); break; }
						case 395: { double J = fabs(aa)+0.01; double SiSj = sin(ab*z.x)*sin(ab*z.y); double SiSj2 = SiSj*SiSj; double aklt = J*(SiSj + SiSj2/3.0); aux.DE *= (1.0 + af * fabs(aklt)); break; }
						case 396: { double J = fabs(aa)+0.01; double Av = sin(ab*z.x)*sin(ab*z.y); double Bp = cos(ac*z.x)*cos(ac*z.y); double toric = 4.0*J*(Av*Av + Bp*Bp); aux.DE *= (1.0 + af * fmin(toric,10.0)); break; }
						case 397: { double F1 = sin(aa*z.x); double F2 = sin(ab*z.y); double F3 = cos(ac*z.x); double F4 = cos(ad*z.y); double wen = F1*F2*F3*F4; aux.DE *= (1.0 + af * fabs(wen)); break; }
						case 398: { double sn = sin(aa*z.x+ab*z.y); double fusion = sn*sn; double F_sym = cos(ac*r)*cos(ac*r); double lw = fusion*F_sym; aux.DE *= (1.0 + af * lw); break; }
						case 399: { double psi = sin(aa*z.x + ab*(double)i*0.1); double coin = cos(ac*z.y); double walker = psi*psi*coin*coin; aux.DE *= (1.0 + af * walker); break; }
						case 400: { double rule = sin(aa*z.x)*sin(ab*z.y)*cos(ac*z.z); double evolution = cos(ad*(double)i*0.1); double qca = rule*evolution; aux.DE *= (1.0 + af * qca*qca); break; }
					}
				}


				// v7.10 — Noise & Procedural DE system (per-section iteration range)
				if (i >= mut.noiseIterStart && i < mut.noiseIterStop && mut.noiseType != 0)
				{
					double na = mut.noiseParamA, nb = mut.noiseParamB, nc = mut.noiseParamC, nd = mut.noiseParamD;
					double nf = mut.noiseFactor, nfq = mut.noiseFreq, nam = mut.noiseAmp;
					double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
					switch(mut.noiseType) {
						case 1: { double h = sin(na*z.x*12.9898 + nb*z.y*78.233 + nc*z.z*45.164)*43758.5453; h = h - floor(h); aux.DE *= (1.0 + nf*h); break; }
						case 2: { double h1 = sin(na*z.x*12.9898 + z.y*78.233)*43758.5453; h1=h1-floor(h1); double h2 = sin(z.y*12.9898 + na*z.z*78.233)*43758.5453; h2=h2-floor(h2); aux.DE *= (1.0 + nf*(h1+h2)*0.5); break; }
						case 3: { double p = na*z.x + nb*z.y + nc*z.z; double h = sin(p*127.1)*43758.5453; h=h-floor(h); double h2 = sin(p*269.5)*43758.5453; h2=h2-floor(h2); aux.DE *= (1.0 + nf*fabs(h-h2)); break; }
						case 4: { double fx = z.x*nfq; double fy = z.y*nfq; double fz = z.z*nfq; double ix = floor(fx); double iy = floor(fy); double iz = floor(fz); double tx = fx-ix; double ty = fy-iy; double tz = fz-iz; double h000 = sin(ix*127.1+iy*311.7+iz*74.7)*43758.5453; h000=h000-floor(h000); double h100 = sin((ix+1)*127.1+iy*311.7+iz*74.7)*43758.5453; h100=h100-floor(h100); double v = h000*(1.0-tx) + h100*tx; aux.DE *= (1.0 + nf*v); break; }
						case 5: { double fx = z.x*nfq; double fy = z.y*nfq; double h00 = sin(floor(fx)*127.1+floor(fy)*311.7)*43758.5453; h00=h00-floor(h00); double h10 = sin((floor(fx)+1)*127.1+floor(fy)*311.7)*43758.5453; h10=h10-floor(h10); double h01 = sin(floor(fx)*127.1+(floor(fy)+1)*311.7)*43758.5453; h01=h01-floor(h01); double h11 = sin((floor(fx)+1)*127.1+(floor(fy)+1)*311.7)*43758.5453; h11=h11-floor(h11); double tx=fx-floor(fx); double ty=fy-floor(fy); double v = h00*(1-tx)*(1-ty)+h10*tx*(1-ty)+h01*(1-tx)*ty+h11*tx*ty; aux.DE *= (1.0 + nf*v); break; }
						case 6: { double h = sin(z.x*na*12.9898 + z.y*nb*78.233 + z.z*nc*45.164 + nd*i)*43758.5453; h=h-floor(h); h = h*h*(3.0-2.0*h); aux.DE *= (1.0 + nf*h); break; }
						case 7: { double h = sin(z.x*nfq + z.y*nfq*1.3 + z.z*nfq*0.7)*43758.5453; h=h-floor(h); h = 6.0*h*h*h*h*h - 15.0*h*h*h*h + 10.0*h*h*h; aux.DE *= (1.0 + nf*h); break; }
						case 8: { double p = na*z.x*nfq + nb*z.y*nfq + nc*z.z*nfq; double h = sin(p)*0.5+0.5; aux.DE *= (1.0 + nf*h*h); break; }
						case 9: { double h1 = sin(z.x*nfq*12.9898)*43758.5453; h1=h1-floor(h1); double h2 = sin(z.y*nfq*78.233)*43758.5453; h2=h2-floor(h2); double h3 = sin(z.z*nfq*45.164)*43758.5453; h3=h3-floor(h3); aux.DE *= (1.0 + nf*(h1*h2*h3)); break; }
						case 10: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double h = sin(r*nfq)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h); break; }
						case 11: { double gx = sin(z.x*nfq*127.1+z.y*311.7)*2.0-1.0; double gy = sin(z.y*nfq*269.5+z.z*183.3)*2.0-1.0; double gz = sin(z.z*nfq*419.2+z.x*371.9)*2.0-1.0; double v = (gx*z.x+gy*z.y+gz*z.z)*nam; aux.DE *= (1.0 + nf*sin(v)); break; }
						case 12: { double px = z.x*nfq; double py = z.y*nfq; double g1 = sin(floor(px)*127.1+floor(py)*311.7)*2.0-1.0; double g2 = sin((floor(px)+1)*127.1+floor(py)*311.7)*2.0-1.0; double t = px-floor(px); t = t*t*(3.0-2.0*t); double v = g1*(1.0-t)+g2*t; aux.DE *= (1.0 + nf*v); break; }
						case 13: { double px = z.x*nfq; double py = z.y*nfq; double pz = z.z*nfq; double g = sin(px*127.1+py*311.7+pz*74.7)*2.0-1.0; double t = g*g*(3.0-2.0*g); aux.DE *= (1.0 + nf*t*nam); break; }
						case 14: { double v = sin(z.x*nfq)*cos(z.y*nfq*1.3)*sin(z.z*nfq*0.7); aux.DE *= (1.0 + nf*v*nam); break; }
						case 15: { double v1 = sin(z.x*nfq+z.y*nfq*0.5); double v2 = sin(z.y*nfq*1.3+z.z*nfq*0.7); double v3 = sin(z.z*nfq*0.9+z.x*nfq*1.1); aux.DE *= (1.0 + nf*(v1+v2+v3)/3.0); break; }
						case 16: { double px = z.x*nfq; double h = sin(px*12.9898+z.y*nfq*78.233)*43758.5453; h=h-floor(h); double g = (h*2.0-1.0)*(px-floor(px)); aux.DE *= (1.0 + nf*g); break; }
						case 17: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double th = atan2(z.y,z.x); double v = sin(r*nfq+th*na)*nam; aux.DE *= (1.0 + nf*v); break; }
						case 18: { double v = sin(z.x*nfq)*sin(z.y*nfq)*sin(z.z*nfq); v = v*v*(3.0-2.0*v); aux.DE *= (1.0 + nf*v*nam); break; }
						case 19: { double dx = sin(z.x*nfq*12.9898)*2.0-1.0; double dy = sin(z.y*nfq*78.233)*2.0-1.0; double dz = sin(z.z*nfq*45.164)*2.0-1.0; double v = sqrt(dx*dx+dy*dy+dz*dz); aux.DE *= (1.0 + nf*(v-1.0)*nam); break; }
						case 20: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double phi = atan2(z.y,z.x); double theta = acos(z.z/fmax(r,1e-21)); double v = sin(r*nfq)*cos(phi*na)*sin(theta*nb); aux.DE *= (1.0 + nf*v); break; }
						case 21: { double v=0, a=nam, f=nfq; for(int k=0;k<4;k++){ v += a*sin(z.x*f*12.9898+z.y*f*78.233+z.z*f*45.164); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 22: { double v=0, a=nam, f=nfq; for(int k=0;k<6;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 23: { double v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*fabs(h*2.0-1.0); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 24: { double v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*(1.0-fabs(h*2.0-1.0)); f*=na; a*=nb; } aux.DE *= (1.0 + nf*v); break; }
						case 25: { double v=0, a=nam, f=nfq, px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ double h=sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; double d=sin(px*f*269.5+py*f*183.3)*43758.5453; d=d-floor(d); px+=d*na; py+=d*nb; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 26: { double v=0, a=1.0, f=nfq, mx=0; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; mx+=a; f*=2.0; a*=0.5; } v/=fmax(mx,1e-21); aux.DE *= (1.0 + nf*v*nam); break; }
						case 27: { double v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ double h1=sin(z.x*f+z.y*f*1.3)*0.5+0.5; double h2=sin(z.y*f*0.7+z.z*f*1.1)*0.5+0.5; v+=a*fmin(h1,h2); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 28: { double v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ double h1=sin(z.x*f+z.y*f*1.3)*0.5+0.5; double h2=sin(z.y*f*0.7+z.z*f*1.1)*0.5+0.5; v+=a*fmax(h1,h2); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 29: { double v=0, a=nam, f=nfq; double cs=cos(nd*M_PI/180.0), sn=sin(nd*M_PI/180.0); double px=z.x,py=z.y; for(int k=0;k<5;k++){ double h=sin(px*f*127.1+py*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; double nx=px*cs-py*sn; py=px*sn+py*cs; px=nx; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 30: { double v=0, a=nam, f=nfq; for(int k=0;k<6;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*sin(h*M_PI); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 31: { double v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ double r2=z.x*z.x+z.y*z.y+z.z*z.z; double h=sin(r2*f)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 32: { double v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f)*cos(z.y*f)*sin(z.z*f); v+=a*h; f*=na; a*=nb; } aux.DE *= (1.0 + nf*v); break; }
						case 33: { double v=0, w=1.0, f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=w*h; w*=h; f*=2.0; } aux.DE *= (1.0 + nf*v*nam); break; }
						case 34: { double v=1.0, f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v*=(h*0.5+0.75); f*=2.0; } aux.DE *= (1.0 + nf*(v-1.0)*nam); break; }
						case 35: { double v=0, a=nam, f=nfq; double px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ double h=sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; px=fabs(px)*2.0-na; py=fabs(py)*2.0-nb; pz=fabs(pz)*2.0-nc; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 36: { double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx+0.5; double cy=floor(z.y*nfq)+dy+0.5; double cz=floor(z.z*nfq)+dz+0.5; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h*0.5; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md)md=d; } aux.DE *= (1.0 + nf*sqrt(md)*nam); break; }
						case 37: { double md1=1e10,md2=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md1){md2=md1;md1=d;}else if(d<md2)md2=d; } aux.DE *= (1.0 + nf*(sqrt(md2)-sqrt(md1))*nam); break; }
						case 38: { double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ double cx=floor(z.x*nfq)+dx+0.5; double cy=floor(z.y*nfq)+dy+0.5; double h=sin(cx*127.1+cy*311.7)*43758.5453; h=h-floor(h); cx+=h*0.5; double d=fabs(z.x*nfq-cx)+fabs(z.y*nfq-cy); if(d<md)md=d; } aux.DE *= (1.0 + nf*md*nam); break; }
						case 39: { double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; double d=fmax(fabs(z.x*nfq-cx),fmax(fabs(z.y*nfq-cy),fabs(z.z*nfq-cz))); if(d<md)md=d; } aux.DE *= (1.0 + nf*md*nam); break; }
						case 40: { double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h1=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h1=h1-floor(h1); double h2=sin(cx*269.5+cy*183.3+cz*346.9)*43758.5453; h2=h2-floor(h2); double h3=sin(cx*419.2+cy*371.9+cz*529.7)*43758.5453; h3=h3-floor(h3); double d=(z.x*nfq-cx-h1)*(z.x*nfq-cx-h1)+(z.y*nfq-cy-h2)*(z.y*nfq-cy-h2)+(z.z*nfq-cz-h3)*(z.z*nfq-cz-h3); if(d<md)md=d; } aux.DE *= (1.0 + nf*sqrt(md)*nam); break; }
						case 41: { double md1=1e10,md2=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md1){md2=md1;md1=d;}else if(d<md2)md2=d; } aux.DE *= (1.0 + nf*md1*md2*nam); break; }
						case 42: { double md=1e10; double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double th=atan2(z.y,z.x); for(int k=0;k<8;k++){ double a2=k*M_PI*2.0/8.0; double d=fabs(th-a2); if(d>M_PI)d=2.0*M_PI-d; if(d<md)md=d; } aux.DE *= (1.0 + nf*md*r*nam*nfq); break; }
						case 43: { double v=0; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); double d=(z.x*nfq-cx-h)*(z.x*nfq-cx-h)+(z.y*nfq-cy-h)*(z.y*nfq-cy-h)+(z.z*nfq-cz-h)*(z.z*nfq-cz-h); v+=exp(-na*d); } aux.DE *= (1.0 + nf*(1.0-v)*nam); break; }
						case 44: { double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; double d=sqrt((z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz)); if(d<md)md=d; } double v=sin(md*M_PI*na); aux.DE *= (1.0 + nf*v*nam); break; }
						case 45: { double md=1e10,cd=0; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md){md=d;cd=h;} } aux.DE *= (1.0 + nf*cd*nam); break; }
						case 46: { double md1=1e10,md2=1e10,md3=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md1){md3=md2;md2=md1;md1=d;}else if(d<md2){md3=md2;md2=d;}else if(d<md3)md3=d; } aux.DE *= (1.0 + nf*(sqrt(md3)-sqrt(md1))*nam); break; }
						case 47: { double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double h=sin(cx*127.1+cy*311.7)*43758.5453; h=h-floor(h); cx+=h*na; double hy=sin(cx*269.5+cy*183.3)*43758.5453; hy=hy-floor(hy); cy+=hy*nb; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy); if(d<md)md=d; } double v = sin(z.z*nfq)*0.5+0.5; aux.DE *= (1.0 + nf*(sqrt(md)+v*nc)*nam); break; }
						case 48: { double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md)md=d; } md=sqrt(md); double v=md-floor(md*na)/na; aux.DE *= (1.0 + nf*v*nam); break; }
						case 49: { double v=0,a=nam,f=nfq; for(int k=0;k<4;k++){ double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ double cx=floor(z.x*f)+dx; double cy=floor(z.y*f)+dy; double h=sin(cx*127.1+cy*311.7)*43758.5453; h=h-floor(h); cx+=h; double d=(z.x*f-cx)*(z.x*f-cx)+(z.y*f-cy)*(z.y*f-cy); if(d<md)md=d; } v+=a*sqrt(md); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 50: { double md=1e10; int nn = (int)fmax(2.0, fmin(na*8.0, 20.0)); for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; for(int p=0;p<2;p++){ double h1=sin((cx+p*0.5)*127.1+cy*311.7+cz*74.7)*43758.5453; h1=h1-floor(h1); double h2=sin(cx*269.5+(cy+p*0.5)*183.3+cz*346.9)*43758.5453; h2=h2-floor(h2); double d=(z.x*nfq-cx-h1)*(z.x*nfq-cx-h1)+(z.y*nfq-cy-h2)*(z.y*nfq-cy-h2)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md)md=d; } } aux.DE *= (1.0 + nf*sqrt(md)*nam); break; }
						case 51: { double v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); double r2=fabs(h*2.0-1.0); v+=a*(1.0-r2); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v*v); break; }
						case 52: { double v=0,a=nam,f=nfq,w=1.0; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); double r2=1.0-fabs(h*2.0-1.0); r2*=r2; v+=r2*a*w; w=fmin(r2*na, 1.0); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 53: { double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f+z.y*f*1.3+z.z*f*0.7); v+=a*fabs(h); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 54: { double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*fabs(sin(h*M_PI*na)); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 55: { double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f+z.y*f*1.3+z.z*f*0.7); double ridge=1.0-fabs(h); ridge=ridge*ridge; v+=a*ridge; f*=na; a*=nb; } aux.DE *= (1.0 + nf*v); break; }
						case 56: { double v=0,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v=fmax(v,h*nam/(1.0+k*0.5)); f*=2.0; } aux.DE *= (1.0 + nf*v); break; }
						case 57: { double v=0,a=nam,f=nfq,prev=0; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); double cur=fabs(h*2.0-1.0); v+=a*cur*prev; prev=cur; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 58: { double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h1=sin(z.x*f+z.y*f*1.3)*0.5+0.5; double h2=sin(z.y*f*0.7+z.z*f*1.1)*0.5+0.5; double h3=sin(z.z*f*0.9+z.x*f*1.5)*0.5+0.5; v+=a*(h1+h2+h3)/3.0; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*(v*2.0-1.0)); break; }
						case 59: { double v=0,a=nam,f=nfq; for(int k=0;k<6;k++){ double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double h=sin(r*f)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 60: { double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f+z.y*f*1.3+z.z*f*0.7); double billow=fabs(h)*2.0-1.0; v+=a*billow; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 61: { double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f+z.y*f*0.7+z.z*f*1.3)*0.5+0.5; v+=a*pow(h, na); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 62: { double v=0,a=nam,f=nfq; double px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ double h=sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*fabs(h*2.0-1.0); double wx=sin(py*f*269.5)*na; double wy=sin(pz*f*183.3)*nb; double wz=sin(px*f*419.2)*nc; px+=wx; py+=wy; pz+=wz; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 63: { double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); if(k%2==0) v+=a*h; else v+=a*(1.0-h); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 64: { double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f+z.y*f*1.3+z.z*f*0.7); double hs=h*h*sign(h); v+=a*hs; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 65: { double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7+nd*i)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 66: { double wx=z.x+nam*sin(z.y*nfq); double wy=z.y+nam*sin(z.z*nfq); double wz=z.z+nam*sin(z.x*nfq); double h=sin(wx*127.1+wy*311.7+wz*74.7)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h); break; }
						case 67: { double wx=z.x+nam*sin(z.y*nfq+z.z*nfq*0.5); double wy=z.y+nam*sin(z.z*nfq*1.3+z.x*nfq*0.7); double wz=z.z+nam*sin(z.x*nfq*0.9+z.y*nfq*1.1); double wx2=wx+nb*sin(wy*nfq*2.0); double wy2=wy+nb*sin(wz*nfq*2.0); double wz2=wz+nb*sin(wx*nfq*2.0); double h=sin(wx2*127.1+wy2*311.7+wz2*74.7)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h); break; }
						case 68: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double th=atan2(z.y,z.x)+nam*sin(r*nfq); double ph=acos(z.z/fmax(r,1e-21))+nb*cos(r*nfq*0.7); double h=sin(th*na+ph*nc)*0.5+0.5; aux.DE *= (1.0 + nf*h); break; }
						case 69: { double h1=sin(z.x*nfq*127.1+z.y*nfq*311.7)*43758.5453; h1=h1-floor(h1); double h2=sin(z.y*nfq*269.5+z.z*nfq*183.3)*43758.5453; h2=h2-floor(h2); double wx=z.x+(h1*2.0-1.0)*nam; double wy=z.y+(h2*2.0-1.0)*nam; double v=sin(wx*nfq*na+wy*nfq*nb); aux.DE *= (1.0 + nf*v); break; }
						case 70: { double v=0,f=nfq,a=nam; double px=z.x,py=z.y,pz=z.z; for(int k=0;k<4;k++){ double h=sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; px+=sin(py*f*na)*nb; py+=sin(pz*f*na)*nb; pz+=sin(px*f*na)*nb; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 71: { double wx=z.x+nam*sin(z.y*nfq)*cos(z.z*nfq*0.5); double wy=z.y+nam*cos(z.x*nfq*0.7)*sin(z.z*nfq); double v=sin(wx*na)*cos(wy*nb); aux.DE *= (1.0 + nf*v); break; }
						case 72: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double wr=r+nam*sin(r*nfq); double h=sin(wr*na*127.1)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h); break; }
						case 73: { double v=sin(z.x*nfq+nam*sin(z.y*nfq+nam*sin(z.z*nfq))); aux.DE *= (1.0 + nf*v); break; }
						case 74: { double t=nd*i*0.01; double wx=z.x+nam*sin(z.y*nfq+t); double wy=z.y+nam*sin(z.z*nfq+t*1.3); double wz=z.z+nam*sin(z.x*nfq+t*0.7); double h=sin(wx*127.1+wy*311.7+wz*74.7)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h); break; }
						case 75: { double scale=nfq; double wx=z.x*scale; double wy=z.y*scale; double wz=z.z*scale; for(int k=0;k<3;k++){ wx=sin(wx*na+wy); wy=cos(wy*nb+wz); wz=sin(wz*nc+wx); } double h=sin(wx+wy+wz)*0.5+0.5; aux.DE *= (1.0 + nf*h*nam); break; }
						case 76: { double h1=sin(z.x*nfq+z.y*nfq*0.5)*0.5+0.5; double h2=sin(z.y*nfq*1.3+z.z*nfq*0.7)*0.5+0.5; double v=sin((z.x+h1*nam)*na)*cos((z.y+h2*nam)*nb); aux.DE *= (1.0 + nf*v); break; }
						case 77: { double wx=z.x+nam*sin(nfq*z.y); double wy=z.y+nam*cos(nfq*z.x); double v1=sin(wx*na); double v2=cos(wy*nb); double v=v1*v2; z.x+=nf*v*nc*0.01; z.y+=nf*v*nd*0.01; aux.DE *= (1.0 + nf*fabs(v)*0.1); break; }
						case 78: { double r2=z.x*z.x+z.y*z.y+z.z*z.z; double h=sin(r2*nfq)*43758.5453; h=h-floor(h); double wx=z.x*(1.0+h*nam); double wy=z.y*(1.0+h*nam); double v=sin(wx*na+wy*nb)*0.5+0.5; aux.DE *= (1.0 + nf*v); break; }
						case 79: { double v=0,f=nfq; for(int k=0;k<4;k++){ double h=sin(z.x*f+sin(z.y*f*na)*nam); v+=h/(1.0+k); f*=2.0; } aux.DE *= (1.0 + nf*v*0.25); break; }
						case 80: { double wx=z.x+nam*sin(z.y*nfq)*sin(z.z*nfq*0.5); double wy=z.y+nam*sin(z.z*nfq*0.7)*sin(z.x*nfq); double wz=z.z+nam*sin(z.x*nfq*1.3)*sin(z.y*nfq*0.9); double v=sin(wx*na)*sin(wy*nb)*sin(wz*nc); aux.DE *= (1.0 + nf*v); break; }
						case 81: { double s=(z.x+z.y+z.z)/3.0; double ix=floor(z.x+s); double iy=floor(z.y+s); double iz=floor(z.z+s); double t=(ix+iy+iz)/6.0; double x0=z.x-ix+t; double y0=z.y-iy+t; double z0=z.z-iz+t; double h=sin(ix*127.1+iy*311.7+iz*74.7)*43758.5453; h=h-floor(h); double v=fmax(0.0,0.6-x0*x0-y0*y0-z0*z0); v=v*v*v*v*h; aux.DE *= (1.0 + nf*v*nam*32.0); break; }
						case 82: { double s=(z.x+z.y+z.z)*nfq/3.0; double v=sin(s*127.1)*43758.5453; v=v-floor(v); double v2=sin(s*269.5)*43758.5453; v2=v2-floor(v2); aux.DE *= (1.0 + nf*(v*na+v2*nb)*0.5*nam); break; }
						case 83: { double skew=(z.x+z.y)*nfq*(sqrt(3.0)-1.0)/2.0; double ix=floor(z.x*nfq+skew); double iy=floor(z.y*nfq+skew); double unskew=(ix+iy)*(3.0-sqrt(3.0))/6.0; double x0=z.x*nfq-ix+unskew; double y0=z.y*nfq-iy+unskew; double h=sin(ix*127.1+iy*311.7)*43758.5453; h=h-floor(h); double t0=0.5-x0*x0-y0*y0; double v=t0>0?t0*t0*t0*t0*h:0; aux.DE *= (1.0 + nf*v*nam*70.0); break; }
						case 84: { double v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double s=(z.x*f+z.y*f+z.z*f)/3.0; double h=sin(s*127.1+k*519.3)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 85: { double v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double s=(z.x*f+z.y*f+z.z*f)/3.0; double h=sin(s*127.1+k*519.3)*43758.5453; h=h-floor(h); v+=a*fabs(h*2.0-1.0); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 86: { double v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double s=(z.x*f+z.y*f+z.z*f)/3.0; double h=sin(s*127.1+k*519.3)*43758.5453; h=h-floor(h); double ridge=1.0-fabs(h*2.0-1.0); ridge*=ridge; v+=a*ridge; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 87: { double s=(z.x+z.y+z.z)*nfq; double v1=sin(s*na)*0.5+0.5; double v2=sin(s*nb+M_PI*0.5)*0.5+0.5; double v=v1*v2; aux.DE *= (1.0 + nf*v*nam); break; }
						case 88: { double v=0; double px=z.x*nfq,py=z.y*nfq,pz=z.z*nfq; for(int k=0;k<4;k++){ double s=(px+py+pz)/3.0; double h=sin(s*127.1+k*91.7)*43758.5453; h=h-floor(h); v+=h*nam/(1.0+k); px+=sin(py)*na; py+=sin(pz)*nb; pz+=sin(px)*nc; } aux.DE *= (1.0 + nf*v*0.25); break; }
						case 89: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double th=atan2(z.y,z.x); double s=(r*nfq+th*na)/3.0; double h=sin(s*127.1)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h*nam); break; }
						case 90: { double v=0,f=nfq,a=nam; double cs=cos(nd*M_PI/180.0),sn=sin(nd*M_PI/180.0); double px=z.x,py=z.y; for(int k=0;k<5;k++){ double s=(px*f+py*f+z.z*f)/3.0; double h=sin(s*127.1+k*519.3)*43758.5453; h=h-floor(h); v+=a*h; double nx=px*cs-py*sn; py=px*sn+py*cs; px=nx; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 91: { double vn=sin(z.x*nfq*127.1+z.y*nfq*311.7+z.z*nfq*74.7)*43758.5453; vn=vn-floor(vn); double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double h=sin(cx*127.1+cy*311.7)*43758.5453; h=h-floor(h); cx+=h; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy); if(d<md)md=d; } aux.DE *= (1.0 + nf*(vn*na+sqrt(md)*nb)*nam); break; }
						case 92: { double v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*sin(h*M_PI*2.0*na); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 93: { double t=nd*i*0.1; double v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7+t)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 94: { double v1=0,v2=0,f=nfq,a=nam; for(int k=0;k<4;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v1+=a*h; v2+=a*fabs(h*2.0-1.0); f*=2.0; a*=0.5; } double blend=sin(z.x*na+z.y*nb)*0.5+0.5; aux.DE *= (1.0 + nf*(v1*blend+v2*(1.0-blend))); break; }
						case 95: { double v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); double erosion=exp(-na*h); v+=a*erosion; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 96: { double v=0,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); double terrace=floor(h*na+0.5)/fmax(na,1e-21); v+=terrace/(1.0+k); f*=2.0; } aux.DE *= (1.0 + nf*v*nam*0.2); break; }
						case 97: { double v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); double swiss=fabs(h*2.0-1.0); swiss=1.0-swiss*swiss; v+=a*swiss; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 98: { double v=0,f=nfq,a=nam; double px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ double h=sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; double wx=sin(py*f*na)*nb*a; double wy=sin(pz*f*na)*nb*a; double wz=sin(px*f*na)*nb*a; px+=wx; py+=wy; pz+=wz; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 99: { double v=0,f=nfq,a=nam; double offset=0; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7+offset)*43758.5453; h=h-floor(h); double r=fabs(h*2.0-1.0); r=offset+r*r*na; v+=a*r; offset=r; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v); break; }
						case 100: { double v1=0,v2=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v1+=a*h; double ridge=1.0-fabs(h*2.0-1.0); v2+=a*ridge*ridge; f*=2.0; a*=0.5; } double t=sin(z.x*na+z.y*nb+z.z*nc)*0.5+0.5; aux.DE *= (1.0 + nf*(v1*(1.0-t)+v2*t)); break; }
					}
				}

				// v7.10 — Orbit Trap DE system (per-section iteration range)
				if (i >= mut.orbitIterStart && i < mut.orbitIterStop && mut.orbitTrapType != 0)
				{
					double oa = mut.orbitParamA, ob = mut.orbitParamB, oc = mut.orbitParamC, od = mut.orbitParamD;
					double of = mut.orbitFactor;
					switch(mut.orbitTrapType) {
						case 1: { double d = sqrt((z.x-oa)*(z.x-oa)+(z.y-ob)*(z.y-ob)+(z.z-oc)*(z.z-oc)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 2: { double d = fabs(z.x-oa)+fabs(z.y-ob)+fabs(z.z-oc); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 3: { double d = fmax(fabs(z.x-oa),fmax(fabs(z.y-ob),fabs(z.z-oc))); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 4: { double d1=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double d2=sqrt((z.x-oa)*(z.x-oa)+(z.y-ob)*(z.y-ob)+(z.z-oc)*(z.z-oc)); aux.DE *= (1.0 + of*exp(-od*fmin(d1,d2))); break; }
						case 5: { double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double ring=fabs(d-oa); aux.DE *= (1.0 + of*exp(-od*ring)); break; }
						case 6: { double dx=z.x-oa*round(z.x/fmax(oa,1e-21)); double dy=z.y-ob*round(z.y/fmax(ob,1e-21)); double dz=z.z-oc*round(z.z/fmax(oc,1e-21)); double d=sqrt(dx*dx+dy*dy+dz*dz); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 7: { double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double shell=fabs(d-oa); double shell2=fabs(d-ob); aux.DE *= (1.0 + of*exp(-od*fmin(shell,shell2))); break; }
						case 8: { double ph=atan2(z.y,z.x); double r=sqrt(z.x*z.x+z.y*z.y); double spiral_r=oa+ob*ph/(2.0*M_PI); double d=fabs(r-spiral_r); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 9: { double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double v=sin(d*oa*M_PI)*0.5+0.5; aux.DE *= (1.0 + of*v); break; }
						case 10: { int nn=(int)fmax(2,fmin(oa*6,12)); double md=1e10; for(int k=0;k<nn;k++){ double ang=k*2.0*M_PI/nn; double cx=ob*cos(ang); double cy=ob*sin(ang); double d=(z.x-cx)*(z.x-cx)+(z.y-cy)*(z.y-cy)+z.z*z.z; if(d<md)md=d; } aux.DE *= (1.0 + of*exp(-od*sqrt(md))); break; }
						case 11: { double d=z.x*z.x/(oa*oa+1e-21)+z.y*z.y/(ob*ob+1e-21)+z.z*z.z/(oc*oc+1e-21); d=fabs(sqrt(d)-1.0); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 12: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double th=atan2(z.y,z.x); double d=fabs(r-oa*(1.0+ob*cos(oc*th))); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 13: { double r2=z.x*z.x+z.y*z.y+z.z*z.z; double inv_r=oa*oa/fmax(r2,1e-21); double d=fabs(inv_r-1.0)*sqrt(r2); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 14: { double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double s=sin(d*oa); double c=cos(d*ob); aux.DE *= (1.0 + of*(s*s+c*c*0.5)*exp(-od*d)); break; }
						case 15: { double d=fabs(z.x*oa+z.y*ob+z.z*oc)/fmax(sqrt(oa*oa+ob*ob+oc*oc),1e-21); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 16: { double d=sqrt(z.y*z.y+z.z*z.z); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 17: { double d=sqrt(z.x*z.x+z.z*z.z); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 18: { double d=sqrt(z.x*z.x+z.y*z.y); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 19: { double d=fabs(z.x*oa+z.y*ob+z.z*oc-od); aux.DE *= (1.0 + of*exp(-d)); break; }
						case 20: { double d=fmin(fabs(z.x),fmin(fabs(z.y),fabs(z.z))); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 21: { double d1=fabs(z.x); double d2=fabs(z.y); double d3=fabs(z.z); aux.DE *= (1.0 + of*exp(-od*fmin(d1,d2))*exp(-od*d3)); break; }
						case 22: { double d=fmin(sqrt(z.x*z.x+z.y*z.y),sqrt(z.y*z.y+z.z*z.z)); d=fmin(d,sqrt(z.x*z.x+z.z*z.z)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 23: { double d1=fabs(z.x-oa); double d2=fabs(z.y-ob); double d3=fabs(z.z-oc); double d=d1*d2*d3; aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 24: { double cs=cos(oa*M_PI/180.0),sn=sin(oa*M_PI/180.0); double rx=z.x*cs-z.y*sn; double ry=z.x*sn+z.y*cs; double d=fabs(ry); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 25: { double d=fmin(fabs(z.x),fabs(z.y)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 26: { double d1=fabs(z.y-oa*z.x); double d2=fabs(z.y+oa*z.x); aux.DE *= (1.0 + of*exp(-od*fmin(d1,d2))); break; }
						case 27: { double ph=atan2(z.y,z.x); int n=(int)fmax(3,fmin(oa,12)); double seg=2.0*M_PI/n; double sph=fmod(ph+M_PI,seg)-seg*0.5; double r=sqrt(z.x*z.x+z.y*z.y); double d=fabs(r*sin(sph)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 28: { double d1=fabs(z.x*sin(oa*M_PI/180.0)-z.y*cos(oa*M_PI/180.0)); double d2=fabs(z.x*sin(ob*M_PI/180.0)-z.y*cos(ob*M_PI/180.0)); aux.DE *= (1.0 + of*exp(-od*(d1+d2))); break; }
						case 29: { double d=fabs(z.z-oa*sin(ob*z.x)*cos(oc*z.y)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 30: { double r=sqrt(z.x*z.x+z.y*z.y); double d=fabs(z.z-oa*sin(ob*r)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 31: { double r=sqrt(z.x*z.x+z.y*z.y); double d=fabs(r-oa); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 32: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double d=fabs(r-oa); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 33: { double r=sqrt(z.x*z.x+z.y*z.y); double d=sqrt((r-oa)*(r-oa)+z.z*z.z)-ob; aux.DE *= (1.0 + of*exp(-od*fabs(d))); break; }
						case 34: { double r=sqrt(z.x*z.x+z.y*z.y); double th=atan2(z.y,z.x); double sf2=pow(fabs(cos(oa*th/4.0)),ob)+pow(fabs(sin(oa*th/4.0)),ob); double sr=oc*pow(sf2,-1.0/fmax(ob,1e-21)); double d=fabs(r-sr); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 35: { double ph=atan2(z.y,z.x); double r=sqrt(z.x*z.x+z.y*z.y); int n=(int)fmax(3,fmin(oa,12)); double star_r=ob*(1.0+oc*cos(n*ph)); double d=fabs(r-star_r); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 36: { double r=sqrt(z.x*z.x+z.y*z.y); double ph=atan2(z.y,z.x); double lemnR=oa*oa*cos(2.0*ph); double d=fabs(r*r-lemnR); aux.DE *= (1.0 + of*exp(-od*d*0.5)); break; }
						case 37: { double r=sqrt(z.x*z.x+z.y*z.y); double ph=atan2(z.y,z.x); double rose_r=oa*sin(ob*ph); double d=fabs(r-fabs(rose_r)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 38: { double ph=atan2(z.y,z.x); double r=sqrt(z.x*z.x+z.y*z.y); double spiral_r=oa*exp(ob*ph); double d=fabs(r-spiral_r); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 39: { double r=sqrt(z.x*z.x+z.y*z.y); double ph=atan2(z.y,z.x); double heart_r=oa*(1.0-sin(ph)); double d=fabs(r-heart_r); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 40: { double d1=sqrt(z.x*z.x+z.y*z.y)-oa; double d2=sqrt(z.y*z.y+z.z*z.z)-oa; double d3=sqrt(z.x*z.x+z.z*z.z)-oa; double d=fmin(fabs(d1),fmin(fabs(d2),fabs(d3))); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 41: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double d1=fabs(r-oa); double d2=fabs(r-ob); aux.DE *= (1.0 + of*exp(-od*d1)*exp(-od*d2)); break; }
						case 42: { double r=sqrt(z.x*z.x+z.y*z.y); double d=r*r-(oa*z.x+ob*z.y); d=fabs(d)/fmax(r+1e-21, 1e-21); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 43: { double ex=z.x*z.x/(oa*oa+1e-21); double ey=z.y*z.y/(ob*ob+1e-21); double d=fabs(ex+ey-1.0)*sqrt(oa*oa+ob*ob); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 44: { double r=sqrt(z.x*z.x+z.y*z.y); double t2=sqrt((r-oa)*(r-oa)+z.z*z.z); double d=fabs(t2-ob)+fabs(z.z)*oc; aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 45: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double ph=atan2(z.y,z.x); double th=acos(z.z/fmax(r,1e-21)); double d=fabs(r-oa*(1.0+ob*sin(oc*ph)*cos(od*th))); aux.DE *= (1.0 + of*exp(-d)); break; }
						case 46: { double d=fabs(z.x*z.x+z.y*z.y-oa*z.z*z.z); d=sqrt(d); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 47: { double d=fabs(z.x*z.x/fmax(oa*oa,1e-21)+z.y*z.y/fmax(ob*ob,1e-21)-z.z*z.z/fmax(oc*oc,1e-21)-1.0); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 48: { double r=sqrt(z.x*z.x+z.y*z.y); double ph=atan2(z.y,z.x); double cyl_r=oa+ob*sin(oc*z.z)*cos(od*ph); double d=fabs(r-cyl_r); aux.DE *= (1.0 + of*exp(-d)); break; }
						case 49: { double d1=fabs(fmax(fabs(z.x),fabs(z.y))-oa); double d2=fabs(fmax(fabs(z.y),fabs(z.z))-oa); double d3=fabs(fmax(fabs(z.x),fabs(z.z))-oa); double d=fmin(d1,fmin(d2,d3)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 50: { double dx=fabs(fabs(z.x)-oa); double dy=fabs(fabs(z.y)-oa); double dz=fabs(fabs(z.z)-oa); double d=dx+dy+dz; aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 51: { double d1=fabs(z.x); double d2=fabs(z.y); double d=fmin(d1,d2); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 52: { double d1=fmin(fabs(z.x),fabs(z.y)); double d2=fabs(z.z); aux.DE *= (1.0 + of*exp(-od*(d1+d2*oa))); break; }
						case 53: { double gx=fabs(z.x-oa*round(z.x/fmax(oa,1e-21))); double gy=fabs(z.y-ob*round(z.y/fmax(ob,1e-21))); double d=fmin(gx,gy); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 54: { double gx=fabs(z.x-oa*round(z.x/fmax(oa,1e-21))); double gy=fabs(z.y-oa*round(z.y/fmax(oa,1e-21))); double gz=fabs(z.z-oa*round(z.z/fmax(oa,1e-21))); double d=fmin(gx,fmin(gy,gz)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 55: { double cs=cos(oa*M_PI/180.0),sn=sin(oa*M_PI/180.0); double rx=z.x*cs-z.y*sn; double ry=z.x*sn+z.y*cs; double d=fmin(fabs(rx),fabs(ry)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 56: { double ph=atan2(z.y,z.x); int n=(int)fmax(3,fmin(oa,16)); double d=sqrt(z.x*z.x+z.y*z.y)*fabs(sin(n*ph*0.5)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 57: { double d1=fabs(z.x-z.y); double d2=fabs(z.x+z.y); double d=fmin(d1,d2)*0.7071; aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 58: { double gx=oa>0.001?fabs(sin(z.x*M_PI/oa)):fabs(z.x); double gy=ob>0.001?fabs(sin(z.y*M_PI/ob)):fabs(z.y); double d=gx*gy; aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 59: { double d1=fmin(fabs(z.x-oa),fabs(z.x+oa)); double d2=fmin(fabs(z.y-ob),fabs(z.y+ob)); double d3=fmin(fabs(z.z-oc),fabs(z.z+oc)); double d=fmin(d1,fmin(d2,d3)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 60: { double r=sqrt(z.x*z.x+z.y*z.y); double ph=atan2(z.y,z.x); int n=(int)fmax(3,fmin(oa,16)); double seg=2.0*M_PI/n; double sph=fmod(ph+M_PI+seg*0.5,seg)-seg*0.5; double d=r*fabs(sin(sph)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 61: { double d=fabs(z.x*z.x-z.y*z.y-oa*oa); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 62: { double hx=z.x*2.0/3.0+z.y/3.0; double hy=z.y*2.0/sqrt(3.0); double d=fmin(fabs(hx-round(hx)),fabs(hy-round(hy)))*oa; aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 63: { double d=sin(z.x*oa*M_PI)*sin(z.y*ob*M_PI)*sin(z.z*oc*M_PI); aux.DE *= (1.0 + of*fabs(d)); break; }
						case 64: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double ph=atan2(z.y,z.x); double th=acos(z.z/fmax(r,1e-21)); double d=fabs(sin(oa*ph)*sin(ob*th))*r; aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 65: { double gx=fabs(z.x-oa*round(z.x/fmax(oa,1e-21))); double gy=fabs(z.y-ob*round(z.y/fmax(ob,1e-21))); double d=sqrt(gx*gx+gy*gy); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 66: { double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double w=exp(-oa*(double)i); aux.DE *= (1.0 + of*exp(-od*d)*w); break; }
						case 67: { double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double phase=sin(ob*(double)i*M_PI/180.0)*0.5+0.5; aux.DE *= (1.0 + of*exp(-od*d)*phase); break; }
						case 68: { double d=sqrt((z.x-oa*sin(ob*i))*(z.x-oa*sin(ob*i))+(z.y-oa*cos(ob*i))*(z.y-oa*cos(ob*i))+z.z*z.z); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 69: { double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double trap_r=oa+ob*(double)i; double ring=fabs(d-trap_r); aux.DE *= (1.0 + of*exp(-od*ring)); break; }
						case 70: { double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(d < oa) { aux.DE *= (1.0 + of*exp(-od*(oa-d))); } break; }
						case 71: { double d=fabs(z.x)+fabs(z.y)+fabs(z.z); double w = (i%2==0) ? 1.0 : -0.5; aux.DE *= (1.0 + of*w*exp(-od*d)); break; }
						case 72: { double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double v=sin(d*oa+ob*(double)i); aux.DE *= (1.0 + of*v*v); break; }
						case 73: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double prevR=in.point.Length(); double dr=fabs(r-prevR); aux.DE *= (1.0 + of*exp(-od*dr)); break; }
						case 74: { double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double n=fmax(1.0,oa*10.0); double trap=fabs(d-round(d*n)/n)*n; aux.DE *= (1.0 + of*exp(-od*trap)); break; }
						case 75: { double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double v=1.0/(1.0+exp(-oa*(d-ob))); aux.DE *= (1.0 + of*(v-0.5)*2.0); break; }
						case 76: { double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double decay=exp(-oa*d); double osc=sin(ob*d+oc*(double)i); aux.DE *= (1.0 + of*decay*osc); break; }
						case 77: { double d=fabs(z.x*z.y)+fabs(z.y*z.z)+fabs(z.z*z.x); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 78: { double d=z.x*z.x+z.y*z.y+z.z*z.z; double v=exp(-oa*d)*sin(ob*sqrt(d)); aux.DE *= (1.0 + of*v); break; }
						case 79: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double ph=atan2(z.y,z.x); double d=fabs(r-oa)*fabs(sin(ob*ph)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 80: { double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double cs=cos(oa*(double)i*M_PI/180.0); double sn=sin(oa*(double)i*M_PI/180.0); double rd=fabs((z.x*cs-z.y*sn)); aux.DE *= (1.0 + of*exp(-od*rd)); break; }
						case 81: { double d=fabs(z.x*z.x+z.y*z.y-oa*oa*z.z); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 82: { double r=sqrt(z.x*z.x+z.y*z.y); double ph=atan2(z.y,z.x); double d=fabs(r-oa*fabs(cos(ob*ph/2.0))); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 83: { double mx=fabs(z.x); double my=fabs(z.y); double mz=fabs(z.z); if(mx<my){double t=mx;mx=my;my=t;} if(mx<mz){double t=mx;mx=mz;mz=t;} double d=mx-oa; aux.DE *= (1.0 + of*exp(-od*fabs(d))); break; }
						case 84: { double d1=sqrt(z.x*z.x+z.y*z.y)-oa; double d2=fabs(z.z)-ob; double d=sqrt(fmax(d1,0.0)*fmax(d1,0.0)+fmax(d2,0.0)*fmax(d2,0.0))+fmin(fmax(d1,d2),0.0); aux.DE *= (1.0 + of*exp(-od*fabs(d))); break; }
						case 85: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double ph=atan2(z.y,z.x); double th=acos(z.z/fmax(r,1e-21)); int nph=(int)fmax(2,oa*4); int nth=(int)fmax(2,ob*4); double dph=fabs(sin(nph*ph*0.5)); double dth=fabs(sin(nth*th*0.5)); double d=r*dph*dth; aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 86: { double d=fabs(sin(z.x*oa)*sin(z.y*ob)*sin(z.z*oc)); aux.DE *= (1.0 + of*d); break; }
						case 87: { double d1=sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-oa; double d2=fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z)))-ob; double d=fmax(d1,-d2); aux.DE *= (1.0 + of*exp(-od*fabs(d))); break; }
						case 88: { double r=sqrt(z.x*z.x+z.y*z.y); double d=sqrt((r-oa)*(r-oa)+z.z*z.z); double knot=fabs(d-ob*fabs(sin(oc*atan2(z.z,r-oa)))); aux.DE *= (1.0 + of*exp(-od*knot)); break; }
						case 89: { double d=pow(fabs(z.x),oa)+pow(fabs(z.y),oa)+pow(fabs(z.z),oa); d=pow(d,1.0/fmax(oa,1e-21))-ob; aux.DE *= (1.0 + of*exp(-od*fabs(d))); break; }
						case 90: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double th=atan2(z.y,z.x); double d=fabs(r-oa*(sin(ob*th)*sin(ob*th)+oc)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 91: { double d1=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double d2=sqrt((z.x-oa)*(z.x-oa)+(z.y-ob)*(z.y-ob)+(z.z-oc)*(z.z-oc)); double d=fabs(d1-d2); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 92: { double d=fabs(z.x*z.y*z.z); d=pow(d,1.0/3.0); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 93: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double ph=atan2(z.y,z.x); double clover=oa*fabs(sin(ob*ph)); double d=fabs(r-clover); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 94: { double d1=fabs(z.x)-oa; double d2=fabs(z.y)-ob; double d3=fabs(z.z)-oc; double outside=sqrt(fmax(d1,0.0)*fmax(d1,0.0)+fmax(d2,0.0)*fmax(d2,0.0)+fmax(d3,0.0)*fmax(d3,0.0)); double inside=fmin(fmax(d1,fmax(d2,d3)),0.0); double d=outside+inside; aux.DE *= (1.0 + of*exp(-od*fabs(d))); break; }
						case 95: { double md=1e10; for(int k=0;k<(int)fmax(2,fmin(oa*4,8));k++){ double ang=k*2.0*M_PI/fmax(oa*4,2); double cx=ob*cos(ang); double cy=ob*sin(ang); for(int j=0;j<(int)fmax(2,fmin(oc*4,8));j++){ double az=j*2.0*M_PI/fmax(oc*4,2); double cz=od*sin(az); double d=(z.x-cx)*(z.x-cx)+(z.y-cy)*(z.y-cy)+(z.z-cz)*(z.z-cz); if(d<md)md=d; }} aux.DE *= (1.0 + of*exp(-sqrt(md))); break; }
						case 96: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double d=sin(r*oa)*sin(z.x*ob)*sin(z.y*oc); aux.DE *= (1.0 + of*fabs(d)); break; }
						case 97: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double ph=atan2(z.y,z.x); double th=acos(z.z/fmax(r,1e-21)); double Y=sin(th)*cos(oa*ph); double d=fabs(r-ob*(1.0+oc*Y)); aux.DE *= (1.0 + of*exp(-od*d)); break; }
						case 98: { double d=0; for(int k=1;k<=(int)fmax(1,fmin(oa*4,6));k++){ double rk=ob*(double)k; double dk=fabs(sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-rk); d+=exp(-oc*dk); } aux.DE *= (1.0 + of*d/(oa*4+1e-21)); break; }
						case 99: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double d=fabs(r-oa); double v=exp(-ob*d)*cos(oc*d); z.x += of*v*z.x/fmax(r,1e-21)*0.01; z.y += of*v*z.y/fmax(r,1e-21)*0.01; z.z += of*v*z.z/fmax(r,1e-21)*0.01; aux.DE *= (1.0 + of*fabs(v)*0.1); break; }
						case 100: { double d1=sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-oa; double d2=sqrt((z.x-ob)*(z.x-ob)+z.y*z.y+z.z*z.z)-oc; double d=fmin(fabs(d1),fabs(d2)); double blend=sin(z.x*od+z.y*od)*0.5+0.5; aux.DE *= (1.0 + of*(d1*(1.0-blend)+d2*blend)*exp(-d)); break; }
					}
				}

				// v7.12 — MandelTorus DE system (per-section iteration range)
				if (i >= mut.torusIterStart && i < mut.torusIterStop && mut.torusType != 0)
				{
					double tf = mut.torusFactor;
					double ta = mut.torusParamA, tb = mut.torusParamB, tc = mut.torusParamC, td = mut.torusParamD;
					switch(mut.torusType) {
						case 1: { double k = ta; double DE0 = tb; aux.DE = 1.0/(1.0 + exp(-k*(aux.DE - DE0))); break; }
						case 2: { double DE0 = ta; double sigma = fmax(fabs(tb), 0.01); aux.DE *= exp(-(aux.DE-DE0)*(aux.DE-DE0)/(sigma*sigma)); break; }
						case 3: { double threshold = ta; double DE_max = fabs(tb)+1.0; double DE_min = fabs(tc)*0.01; aux.DE = (aux.DE > threshold) ? DE_max : DE_min; break; }
						case 4: { double b1=ta, b2=tb; double d1=fabs(tc),d2=fabs(td); if(aux.DE<b1) aux.DE=d1; else if(aux.DE<b2) aux.DE=d2; break; }
						case 5: { double h = sin(z.x*127.1+z.y*311.7+z.z*74.7)*43758.5453; h=h-floor(h); aux.DE += tf*(h*2.0-1.0)*ta; break; }
						case 6: { double jx=z.x*z.x-z.y*z.y+ta; double jy=2.0*z.x*z.y+tb; double julia_mag=sqrt(jx*jx+jy*jy); aux.DE *= (1.0 + tf*0.1*julia_mag); break; }
						case 7: { aux.DE *= (1.0 + tf*0.1*sin(ta*(double)i*0.1)); break; }
						case 8: { double alpha=fmin(fmax(ta,0.01),0.99); aux.DE = alpha*aux.DE + (1.0-alpha)*tb; break; }
						case 9: { double h1=sin(ta*z.x+tb*z.y+tc*z.z); double h2=sin(td*h1+ta*aux.DE); aux.DE *= (1.0 + tf*h2); break; }
						case 10: { double v=0,f=ta,a=1.0; for(int k=0;k<4;k++){double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453;h=h-floor(h);v+=a*h;f*=2.0;a*=0.5;} aux.DE *= (1.0 + tf*0.1*v); break; }
						case 11: { double speed = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE /= (1.0 + tf*speed*ta); break; }
						case 12: { double sc = fabs(ta) + 0.01; aux.DE *= sc; break; }
						case 13: { double angle = atan2(z.y,z.x); aux.DE *= (1.0 + tf*fabs(angle)*ta/(M_PI)); break; }
						case 14: { double shear = fabs(z.x*z.y*ta) + fabs(z.y*z.z*tb) + fabs(z.z*z.x*tc); aux.DE *= (1.0 + tf*shear); break; }
						case 15: { double progress = (double)i / fmax((double)(i+10), 1.0); aux.DE *= (1.0 + tf*(1.0-progress)*ta); break; }
						case 16: { double box = fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z))); if(box > fabs(ta)) aux.DE *= (1.0 + tf*tb); break; }
						case 17: { double d = sqrt((z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc)); if(d < fabs(td)) aux.DE *= (1.0 + tf); break; }
						case 18: { double w = fabs(ta)+0.01; if(fabs(z.x)<w && fabs(z.y)<w) aux.DE *= (1.0 + tf*tb); break; }
						case 19: { double intensity = sin(z.x*ta)*sin(z.y*tb)*sin(z.z*tc); aux.DE *= (1.0 + tf*0.1*intensity*intensity); break; }
						case 20: { double ao = 1.0/(1.0 + (double)i*ta*0.01); aux.DE *= (1.0 - tf*ao*fabs(tb)); break; }
						case 21: { double gi = sin(z.x*ta+z.y*tb)*0.5+0.5; aux.DE /= (1.0 + tf*gi*fabs(tc)); break; }
						case 22: { double depth = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0 + tf*ta*depth); break; }
						case 23: { double light_accum = sin(z.x*ta)*sin(z.y*ta)*0.5+0.5; aux.DE /= (1.0 + tf*light_accum*tb); break; }
						case 24: { double ss_depth = exp(-fabs(ta)*sqrt(z.x*z.x+z.y*z.y+z.z*z.z)); aux.DE *= (1.0 + tf*ss_depth*tb); break; }
						case 25: { double wl_diff = fabs(z.x*ta - tb); aux.DE *= (1.0 + tf*tc*wl_diff); break; }
						case 26: { double caustic = sin(z.x*ta*10.0)*sin(z.y*tb*10.0); aux.DE *= (1.0 + tf*caustic*caustic*tc); break; }
						case 27: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double view_dot = z.z/fmax(r,1e-21); double fresnel = pow(fmax(1.0-fabs(view_dot),0.0), ta); aux.DE *= (1.0 + tf*fresnel*tb); break; }
						case 28: { double thin_film = sin(ta*sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*M_PI*2.0); aux.DE *= (1.0 + tf*thin_film*thin_film*tb); break; }
						case 29: { double tangent_dot = fabs(z.x*cos(ta)+z.y*sin(ta))/fmax(sqrt(z.x*z.x+z.y*z.y),1e-21); aux.DE *= (1.0 + tf*tangent_dot*tb); break; }
						case 30: { double subdiv = fmax(1.0, floor(ta*(double)i*0.1+1.0)); aux.DE /= subdiv*tf+1.0; break; }
						case 31: { double dist = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double lod = fmin(dist*ta, tb); aux.DE *= (1.0 + tf*lod); break; }
						case 32: { double edge = fabs(z.x-round(z.x*ta)/fmax(ta,1e-21)) + fabs(z.y-round(z.y*ta)/fmax(ta,1e-21)); aux.DE *= (1.0 + tf*edge*tb); break; }
						case 33: { double h = sin(z.x*ta*10.0)*sin(z.y*tb*10.0)*sin(z.z*tc*10.0); aux.DE += tf*h*td; break; }
						case 34: { double perturb = sin(z.x*ta*20.0)*cos(z.y*tb*20.0)*sin(z.z*tc*20.0); aux.DE *= (1.0 + tf*perturb*td); break; }
						case 35: { double depth = sin(z.x*ta+z.y*tb)*0.5+0.5; aux.DE *= (1.0 + tf*depth*tc); break; }
						case 36: { double n = fmax(fabs(ta), 0.1); aux.DE /= n; break; }
						case 37: { double dist = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= exp(-tf*fabs(ta)*dist); break; }
						case 38: { double cos_th = z.z/fmax(sqrt(z.x*z.x+z.y*z.y+z.z*z.z),1e-21); double phase = (1.0-ta*ta)/(1.0+ta*ta-2.0*ta*cos_th+1e-21); aux.DE *= (1.0 + tf*phase*tb); break; }
						case 39: { double emission = sin(z.x*ta)*sin(z.y*ta)*sin(z.z*ta); emission = emission*emission; aux.DE /= (1.0 + tf*emission*tb); break; }
						case 40: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double twist = sin(tb*phi + tc*theta); aux.DE *= (1.0 + tf*twist*twist); break; }
						case 41: { double R = fabs(ta)+0.1; double r_min = fabs(tb)+0.01; double ratio = R/r_min; aux.DE *= (1.0 + tf*ratio*0.1); break; }
						case 42: { double R = fabs(ta)+0.1; double r_min = fabs(tb)+0.01; double ratio = r_min/R; aux.DE *= (1.0 + tf*ratio); break; }
						case 43: { double phi = atan2(z.y,z.x); double revolutions = ta*phi/(2.0*M_PI); aux.DE *= (1.0 + tf*sin(revolutions*2.0*M_PI)*tb); break; }
						case 44: { double r2 = z.x*z.x+z.y*z.y+z.z*z.z+1e-21; double w = sin(ta*r2); double hopf = cos(tb*atan2(z.y,z.x))*sin(tc*acos(z.z/sqrt(r2))); aux.DE *= (1.0 + tf*w*hopf); break; }
						case 45: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double helix_r = ta + tb*sin(tc*phi); double d = fabs(r2d - helix_r); aux.DE *= (1.0 + tf*exp(-td*d)); break; }
						case 46: { double phi = atan2(z.y,z.x); double half_twist = sin(phi*0.5); double r2d = sqrt(z.x*z.x+z.y*z.y); double torus_d = fabs(r2d-ta); aux.DE *= (1.0 + tf*half_twist*half_twist*exp(-tb*torus_d)); break; }
						case 47: { double phi = atan2(z.y,z.x); double R = ta; double r_k = tb*(1.0+0.5*cos(phi)); double r2d = sqrt(z.x*z.x+z.y*z.y); double d = fabs(r2d-R) + fabs(z.z)*r_k; aux.DE *= (1.0 + tf*exp(-tc*d)); break; }
						case 48: { double phi = atan2(z.y,z.x); double genus = fmax(floor(fabs(ta)*3+1),1.0); double fiber = sin(genus*phi)*cos(tb*z.z); aux.DE *= (1.0 + tf*fiber*fiber*tc); break; }
						case 49: { double phi = atan2(z.y,z.x); double wrapping = floor(fabs(ta)*4+2); double companion = sin(wrapping*phi)*tb; double r2d = sqrt(z.x*z.x+z.y*z.y); double d = fabs(r2d-tc-companion); aux.DE *= (1.0 + tf*exp(-td*d)); break; }
						case 50: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double neg_curv = sin(ta*phi)*sin(tb*z.z)*exp(-tc*fabs(r2d-td)); aux.DE *= (1.0 + tf*neg_curv*neg_curv); break; }
						case 51: { double phi = atan2(z.y,z.x); double r2d = sqrt(z.x*z.x+z.y*z.y); double p=fmax(floor(fabs(ta)*3+2),2.0); double q=fmax(floor(fabs(tb)*3+3),3.0); double knot_r = tc + td*cos(q*phi); double knot_z2 = td*sin(q*phi); double d = sqrt((r2d-knot_r)*(r2d-knot_r)+(z.z-knot_z2)*(z.z-knot_z2)); aux.DE *= (1.0 + tf*exp(-d*5.0)); break; }
						case 52: { double phi = atan2(z.y,z.x); double r2d = sqrt(z.x*z.x+z.y*z.y); double trefoil_r = ta*(2.0+cos(3.0*phi)); double trefoil_z = ta*sin(3.0*phi); double d = sqrt((r2d-trefoil_r)*(r2d-trefoil_r)+(z.z-trefoil_z)*(z.z-trefoil_z)); aux.DE *= (1.0 + tf*exp(-tb*d)); break; }
						case 53: { double phi = atan2(z.y,z.x); double r2d = sqrt(z.x*z.x+z.y*z.y); double cinquefoil_r = ta*(2.0+cos(5.0*phi)); double cinquefoil_z = ta*sin(5.0*phi); double d = sqrt((r2d-cinquefoil_r)*(r2d-cinquefoil_r)+(z.z-cinquefoil_z)*(z.z-cinquefoil_z)); aux.DE *= (1.0 + tf*exp(-tb*d)); break; }
						case 54: { double phi = atan2(z.y,z.x); double r2d = sqrt(z.x*z.x+z.y*z.y); double fig8_r = ta*(2.0+cos(2.0*phi)); double fig8_z = ta*sin(4.0*phi)*0.5; double d = sqrt((r2d-fig8_r)*(r2d-fig8_r)+(z.z-fig8_z)*(z.z-fig8_z)); aux.DE *= (1.0 + tf*exp(-tb*d)); break; }
						case 55: { double t2 = atan2(z.y,z.x)*ta; double r2d = sqrt(z.x*z.x+z.y*z.y); double lissajous_r = tb*(2.0+sin(3.0*t2)*cos(2.0*t2)); double d = fabs(r2d-lissajous_r)+fabs(z.z)*tc; aux.DE *= (1.0 + tf*exp(-d*td)); break; }
						case 56: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double bump = sin(tb*phi)*sin(tc*theta); aux.DE *= (1.0 + tf*bump*bump*td); break; }
						case 57: { double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double r = tb; double torus_d = sqrt((r2d-R)*(r2d-R)+z.z*z.z)-r; double corrugation = sin(tc*atan2(z.y,z.x)*10.0)*td; aux.DE *= (1.0 + tf*exp(-(torus_d-corrugation)*(torus_d-corrugation))); break; }
						case 58: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double wave_R = ta + tb*sin(tc*phi)*sin(td*z.z); double d = fabs(r2d-wave_R); aux.DE *= (1.0 + tf*exp(-d*5.0)); break; }
						case 59: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double spiral_R = ta + tb*phi/(2.0*M_PI); double d = fabs(r2d-spiral_R)+fabs(z.z)*tc; aux.DE *= (1.0 + tf*exp(-d*td)); break; }
						case 60: { double r2d = sqrt(z.x*z.x+z.y*z.y); double star_n = fmax(floor(fabs(ta)*5+3),3.0); double phi = atan2(z.y,z.x); double star_R = tb*(1.0+tc*cos(star_n*phi)); double d = fabs(r2d-star_R)+fabs(z.z)*td; aux.DE *= (1.0 + tf*exp(-d*5.0)); break; }
						case 61: { double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double r = tb; double torus_d = sqrt((r2d-R)*(r2d-R)+z.z*z.z)-r; double fracture = sin(z.x*tc*20.0)*sin(z.y*tc*20.0)*td; aux.DE *= (1.0 + tf*exp(-fabs(torus_d)*5.0)*(1.0+fracture)); break; }
						case 62: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double egg_R = ta*(1.0+tb*sin(phi)); double d = sqrt((r2d-egg_R)*(r2d-egg_R)+z.z*z.z)-tc; aux.DE *= (1.0 + tf*exp(-fabs(d)*td)); break; }
						case 63: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double gear_n = fmax(floor(fabs(ta)*8+4),4.0); double gear_R = tb*(1.0+tc*fmax(cos(gear_n*phi)-0.5,0.0)); double d = fabs(r2d-gear_R); aux.DE *= (1.0 + tf*exp(-d*td*10.0)); break; }
						case 64: { double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double r = tb; double torus_d = sqrt((r2d-R)*(r2d-R)+z.z*z.z)-r; double erosion = sin(z.x*tc*5.0)*sin(z.y*tc*5.0)*sin(z.z*tc*5.0); aux.DE *= (1.0 + tf*exp(-fabs(torus_d)*5.0)*fabs(erosion)*td); break; }
						case 65: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double superformula = pow(fabs(cos(tb*theta/4.0)),tc)+pow(fabs(sin(tb*theta/4.0)),tc); double sf_r = td*pow(superformula,-1.0/fmax(tc,0.01)); double d = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-sf_r; aux.DE *= (1.0 + tf*exp(-fabs(d)*5.0)); break; }
						case 66: { double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double gravity = 1.0/fmax((r2d-R)*(r2d-R)+z.z*z.z+0.01, 0.01); aux.DE *= (1.0 + tf*fmin(gravity*tb,10.0)); break; }
						case 67: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double B_field = ta*sin(tb*phi)/(fmax(fabs(r2d-tc),0.01)); aux.DE *= (1.0 + tf*fmin(fabs(B_field),10.0)*td); break; }
						case 68: { double r2d = sqrt(z.x*z.x+z.y*z.y); double vortex = ta*exp(-tb*((r2d-tc)*(r2d-tc)+z.z*z.z)); double circulation = sin(td*atan2(z.y,z.x)); aux.DE *= (1.0 + tf*vortex*circulation); break; }
						case 69: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double plasma = sin(ta*r2d)*cos(tb*phi)*sin(tc*z.z); double temperature = exp(-td*sqrt((r2d-1.0)*(r2d-1.0)+z.z*z.z)); aux.DE *= (1.0 + tf*plasma*temperature); break; }
						case 70: { double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double charge = tb/fmax(sqrt((r2d-R)*(r2d-R)+z.z*z.z),0.01); double screen = exp(-tc*sqrt((r2d-R)*(r2d-R)+z.z*z.z)); aux.DE *= (1.0 + tf*charge*screen*td); break; }
						case 71: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double wave1 = sin(ta*phi + tb*z.z); double wave2 = sin(tc*phi - tb*z.z); double interference = (wave1+wave2)*(wave1+wave2)*0.25; aux.DE *= (1.0 + tf*interference*td); break; }
						case 72: { double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double thermal = exp(-tb*((r2d-R)*(r2d-R)+z.z*z.z)); double fluctuation = sin(tc*z.x)*sin(tc*z.y)*sin(tc*z.z); aux.DE *= (1.0 + tf*thermal*(1.0+td*fluctuation)); break; }
						case 73: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); int modes = (int)fmax(2,fmin(ta*5,10)); double v = 0; for(int m=1;m<=modes;m++) v+=sin(m*phi*tb)*cos(m*z.z*tc)/m; aux.DE *= (1.0 + tf*v*v*td); break; }
						case 74: { double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double diffusion = 1.0/(1.0 + tb*(double)i*0.01); double concentration = exp(-tc*fabs(r2d-R))*diffusion; aux.DE *= (1.0 + tf*concentration*td); break; }
						case 75: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double reaction = sin(ta*phi)*sin(tb*z.z); double diffuse = exp(-tc*((r2d-td)*(r2d-td))); double rd = reaction*diffuse; aux.DE *= (1.0 + tf*rd*rd); break; }
						case 76: { double r2d = sqrt(z.x*z.x+z.y*z.y); double d1 = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double d2 = sqrt((r2d-tc)*(r2d-tc)+z.z*z.z)-td; aux.DE *= (1.0 + tf*exp(-fmin(d1*d1,d2*d2)*5.0)); break; }
						case 77: { double r2d = sqrt(z.x*z.x+z.y*z.y); double ryz = sqrt(z.y*z.y+z.z*z.z); double d1 = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double d2 = sqrt((ryz-ta)*(ryz-ta)+z.x*z.x)-tb; aux.DE *= (1.0 + tf*exp(-fmin(d1*d1,d2*d2)*tc)); break; }
						case 78: { double r2d = sqrt(z.x*z.x+z.y*z.y); double rxz = sqrt(z.x*z.x+z.z*z.z); double ryz = sqrt(z.y*z.y+z.z*z.z); double d1=fabs(sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb); double d2=fabs(sqrt((rxz-ta)*(rxz-ta)+z.y*z.y)-tb); double d3=fabs(sqrt((ryz-ta)*(ryz-ta)+z.x*z.x)-tb); aux.DE *= (1.0 + tf*exp(-fmin(d1,fmin(d2,d3))*tc)); break; }
						case 79: { double phi = atan2(z.y,z.x); double r2d = sqrt(z.x*z.x+z.y*z.y); int n = (int)fmax(2,fmin(ta*4,8)); double md = 1e10; for(int k=0;k<n;k++){ double ang = k*2.0*M_PI/n; double cx = tb*cos(ang); double cy = tb*sin(ang); double d = sqrt((z.x-cx)*(z.x-cx)+(z.y-cy)*(z.y-cy)+z.z*z.z)-tc; if(fabs(d)<md) md=fabs(d); } aux.DE *= (1.0 + tf*exp(-md*td)); break; }
						case 80: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double R_var = ta + tb*sin(tc*phi); double torus_d = sqrt((r2d-R_var)*(r2d-R_var)+z.z*z.z)-td; aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }
						case 81: { double r2d = sqrt(z.x*z.x+z.y*z.y); double d1 = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double d2 = sqrt((r2d-ta)*(r2d-ta)+(z.z-tc)*(z.z-tc))-tb; aux.DE *= (1.0 + tf*exp(-fmin(fabs(d1),fabs(d2))*td)); break; }
						case 82: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double R1 = ta; double r1 = tb; double R2 = tc; double r2 = td; double d1 = sqrt((r2d-R1)*(r2d-R1)+z.z*z.z)-r1; double d2 = sqrt((r2d-R2)*(r2d-R2)+z.z*z.z)-r2; double smooth = -log(exp(-d1*5.0)+exp(-d2*5.0)+1e-21)/5.0; aux.DE *= (1.0 + tf*exp(-smooth*smooth)); break; }
						case 83: { double r2d = sqrt(z.x*z.x+z.y*z.y); double torus_d = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double sphere_d = sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-tc; double d = fmax(torus_d, -sphere_d); aux.DE *= (1.0 + tf*exp(-fabs(d)*td)); break; }
						case 84: { double r2d = sqrt(z.x*z.x+z.y*z.y); double torus_d = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double box_d = fmax(fabs(z.x)-tc,fmax(fabs(z.y)-tc,fabs(z.z)-td))-0.0; double d = fmax(torus_d,box_d); aux.DE *= (1.0 + tf*exp(-fabs(d)*5.0)); break; }
						case 85: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double inner_r = tb*(1.0+tc*sin(td*phi)); double torus_d = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-inner_r; aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }
						case 86: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double flow = sin(ta*phi-(double)i*tb*0.1); double torus_d = sqrt((r2d-tc)*(r2d-tc)+z.z*z.z)-td; aux.DE *= (1.0 + tf*flow*flow*exp(-fabs(torus_d)*5.0)); break; }
						case 87: { double r2d = sqrt(z.x*z.x+z.y*z.y); double omega = ta*(double)i*0.01; double R_t = tb*(1.0+tc*sin(omega)); double torus_d = sqrt((r2d-R_t)*(r2d-R_t)+z.z*z.z)-td; aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }
						case 88: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double stretch = 1.0 + ta*sin(tb*phi); double torus_d = sqrt((r2d-tc*stretch)*(r2d-tc*stretch)+z.z*z.z)-td/stretch; aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }
						case 89: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phase = ta*(double)i*0.1; double wobble_z = tb*sin(phase); double torus_d = sqrt((r2d-tc)*(r2d-tc)+(z.z-wobble_z)*(z.z-wobble_z))-td; aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }
						case 90: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double pulse = exp(-ta*((double)i*0.1-tb)*((double)i*0.1-tb)); double torus_d = sqrt((r2d-tc)*(r2d-tc)+z.z*z.z)-td*(1.0+pulse); aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }
						case 91: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double bifurcation = ta*sin(tb*phi)*sin(tc*phi*2.0); double torus_d = sqrt((r2d-td-bifurcation)*(r2d-td-bifurcation)+z.z*z.z)-0.3; aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }
						case 92: { double r2d = sqrt(z.x*z.x+z.y*z.y); double chaos = sin(ta*z.x)*cos(tb*z.y)*sin(tc*z.z); double torus_d = sqrt((r2d-td)*(r2d-td)+z.z*z.z)-fabs(chaos)*0.5; aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }
						case 93: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double soliton = 1.0/cosh(ta*(r2d-tb)); double torus_phase = sin(tc*phi+td*z.z); aux.DE *= (1.0 + tf*soliton*torus_phase*torus_phase); break; }
						case 94: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double breather = sin(ta*(double)i*0.1)*sin(tb*phi)/cosh(tc*(r2d-td)); aux.DE *= (1.0 + tf*breather*breather); break; }
						case 95: { double r2d = sqrt(z.x*z.x+z.y*z.y); double torus_d = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double damping = exp(-tc*(double)i*0.01); aux.DE *= (1.0 + tf*sin(torus_d*td*10.0)*damping); break; }
						case 96: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double villarceau = sin(phi+theta*tb)*sin(phi-theta*tb); aux.DE *= (1.0 + tf*villarceau*villarceau*tc); break; }
						case 97: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double dupin = ta*(1.0+tb*cos(phi))*(1.0+tc*cos(atan2(z.z,r2d-ta))); double d = fabs(sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-dupin*0.3); aux.DE *= (1.0 + tf*exp(-d*td)); break; }
						case 98: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double clifford_r = ta*(cos(tb*phi)*cos(tc*theta)); double clifford_d = fabs(sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-fabs(clifford_r)); aux.DE *= (1.0 + tf*exp(-clifford_d*td)); break; }
						case 99: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double lawson_r = ta*cos(tb*phi)*cos(tc*z.z); double d = fabs(r2d-fabs(lawson_r)-td); aux.DE *= (1.0 + tf*exp(-d*5.0)); break; }
						case 100: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double p=fmax(ta,0.1); double q=fmax(tb,0.1); double torus_knot_r = tc*(2.0+cos(q/p*phi)); double torus_knot_z = tc*sin(q/p*phi); double d = sqrt((r2d-torus_knot_r)*(r2d-torus_knot_r)+(z.z-torus_knot_z)*(z.z-torus_knot_z))-td; aux.DE *= (1.0 + tf*exp(-fabs(d)*5.0)); break; }
					}
				}

				// DE tweak + DE scale (per-section iteration range)
				if (i >= mut.deIterStart && i < mut.deIterStop)
				{
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
				} // end DE iteration range

				// Orbit trap
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

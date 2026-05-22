/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2017-22 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * container for 9 elements of hybrid fractal
 * file was manually derived from src/nine_fractal.*
 */

#ifndef MANDELBULBER2_OPENCL_FRACTAL_SEQUENCE_CL_H_
#define MANDELBULBER2_OPENCL_FRACTAL_SEQUENCE_CL_H_

#define OPENCL_FRACTAL_SEQUENCE_LENGTH 250

#ifndef OPENCL_KERNEL_CODE
#include "src/fractal_enums.h"
#include "src/include_header_wrapper.hpp"
#include "opencl_algebra.h"
#endif

typedef enum
{
	analyticDEType,
	deltaDEType
} enumDETypeCl;

typedef enum
{
	linearDEFunction = 1,
	logarithmicDEFunction = 2,
	pseudoKleinianDEFunction = 3,
	josKleinianDEFunction = 4,
	customDEFunction = 5,
	maxAxisDEFunction = 6,
} enumDEFunctionTypeCl;

typedef enum
{
	clAnalyticFunctionUndefined = -1,
	clAnalyticFunctionNone = 0,
	clAnalyticFunctionLinear = 1,
	clAnalyticFunctionLogarithmic = 2,
	clAnalyticFunctionIFS = 3,
	clAnalyticFunctionPseudoKleinian = 4,
	clAnalyticFunctionJosKleinian = 5,
	clAnalyticFunctionCustomDE = 6,
	clAnalyticFunctionMaxAxis = 7,
} enumDEAnalyticFunctionCl;

typedef enum
{
	clColoringFunctionUndefined = -1,
	clColoringFunctionDefault = 0,
	clColoringFunctionABox = 1,
	clColoringFunctionIFS = 2,
	clColoringFunctionAmazingSurf = 3,
	clColoringFunctionABox2 = 4,
	clColoringFunctionDonut = 5,
} enumColoringFunctionCl;

// Advanced weight mode enums for OpenCL
typedef enum
{
	clWeightModeStatic = 0,
	clWeightModeIteration = 1,
	clWeightModeDE = 2,
	clWeightModeZLength = 3,
	clWeightModeConditional = 4,
	clWeightModeOrbitTrap = 5,
	clWeightModeCurve = 6,
	clWeightModeTransformPassthrough = 7,
	clWeightModeDERatio = 8,
	clWeightModeAdaptive = 9,
} enumWeightModeCl;

typedef enum
{
	clWeightBlendLinear = 0,
	clWeightBlendSmooth = 1,
	clWeightBlendStep = 2,
	clWeightBlendMultiply = 3,
	clWeightBlendPower = 4,
	clWeightBlendMin = 5,
	clWeightBlendMax = 6,
} enumWeightBlendModeCl;

typedef enum
{
	clWeightModLinear = 0,
	clWeightModSmooth = 1,
	clWeightModExponential = 2,
	clWeightModInverse = 3,
	clWeightModSigmoid = 4,
} enumWeightModTypeCl;

typedef enum
{
	clWeightCondDE = 0,
	clWeightCondZLength = 1,
	clWeightCondDist = 2,
	clWeightCondIteration = 3,
} enumWeightCondTypeCl;

// Per-formula advanced weight parameters for OpenCL
typedef struct
{
	cl_int mode;
	cl_float staticWeight;
	cl_int iterStart;
	cl_int iterEnd;
	cl_float startWeight;
	cl_float endWeight;
	cl_int blendMode;
	cl_float deBase;
	cl_float deSensitivity;
	cl_float deThreshold;
	cl_int deModType;
	cl_float zlengthBase;
	cl_float zlengthSens;
	cl_float zlengthThreshold;
	cl_int zlengthModType;
	cl_int conditionType;
	cl_float conditionThreshold;
	cl_float trueWeight;
	cl_float falseWeight;
	cl_int conditionBlend;
	// OrbitTrap (mode 5)
	cl_float orbitTrapBase;
	cl_float orbitTrapSensitivity;
	cl_float orbitTrapThreshold;
	cl_int orbitTrapModType;
	// Curve (mode 6)
	cl_float curveBase;
	cl_float curveSensitivity;
	cl_float curvePower;
	cl_int curveModType;
	// DE Ratio (mode 8)
	cl_float deRatioScale;
	cl_float deRatioOffset;
	cl_int deRatioModType;
	// Adaptive (mode 9)
	cl_float adaptiveStrength;
	// Separate components
	cl_int separateComponents;
	// Fine-tuning post-processing
	cl_float weightFloor;
	cl_float weightCeiling;
	cl_float weightGamma;
	cl_int weightInvert;
	cl_int fadeInIterations;
	cl_int fadeOutIterations;
	cl_float deSmoothRadius;
	cl_float componentBlendCurve;
	// Separate components
	cl_float zVectorWeight;
	cl_float deComponentWeight;
	cl_float distComponentWeight;
	cl_float colorComponentWeight;
} sClFormulaWeightParams;

typedef struct
{
	cl_int enabled;
	// Pre-transform
	cl_float preRotX, preRotY, preRotZ;
	cl_float preScale;
	cl_float preOffsetX, preOffsetY, preOffsetZ;
	cl_int preAbsX, preAbsY, preAbsZ;
	// Post-transform
	cl_float postRotX, postRotY, postRotZ;
	cl_float postScale;
	cl_float postOffsetX, postOffsetY, postOffsetZ;
	// Component swizzle
	cl_int swizzle;
	// Fold injection
	cl_int foldType;
	cl_int foldPosition;
	cl_float foldLimit;
	cl_float foldValue;
	cl_int kaleidoscopeSides;
	// Warp distortion
	cl_int warpType;
	cl_float warpFrequency;
	cl_float warpAmplitude;
	// Math injection
	cl_int mathType;
	cl_float mathP1;
	cl_float mathP2;
	cl_float mathP3;
	cl_float mathP4;
	cl_float mathP5;
	cl_float mathP6;
	cl_float mathP7;
	cl_float mathP8;
	cl_float mathMix;
	// Output control
	cl_float zMix;
	cl_float deScale;
	// DE tweak (Familie 10)
	cl_int deTweak;
	cl_float deTweakP1;
	cl_float deTweakP2;
	// Orbit trap
	cl_int orbitTrap;
	cl_float trapCenterX, trapCenterY, trapCenterZ;
	cl_float trapRadius;
	// Curvature coloring
	cl_int curvatureColoring;
	// Iteration range (global master)
	cl_int iterationStart;
	cl_int iterationStop;
	// Per-section iteration ranges
	cl_int preIterStart, preIterStop;
	cl_int foldIterStart, foldIterStop;
	cl_int warpIterStart, warpIterStop;
	cl_int mathIterStart, mathIterStop;
	cl_int postIterStart, postIterStop;
	cl_int juliaIterStart, juliaIterStop;
	cl_int deIterStart, deIterStop;
	// v7.5 — Julia injection system
	cl_int juliaInjection;
	cl_int juliaStart;
	cl_int juliaCTransform;
	cl_int juliaDynamic;
	cl_int juliaMulti;
	cl_float juliaCMul;
	cl_float juliaCRotX, juliaCRotY, juliaCRotZ;
	cl_float juliaCPower;
	cl_float juliaCMobiusA, juliaCMobiusB, juliaCMobiusD;
	cl_float juliaCRadius;
	cl_float juliaPulseFreq;
	cl_float juliaPulseAmp;
	cl_float juliaAbsorb;
	cl_float juliaNoiseFreq;
	cl_float juliaNoiseAmp;
	cl_float juliaFourierC2x, juliaFourierC2y, juliaFourierC2z;
	cl_float juliaFourierC3x, juliaFourierC3y, juliaFourierC3z;
	cl_float juliaBipolarCRx, juliaBipolarCRy, juliaBipolarCRz;
	// v7.6 — Inversion system
	cl_int inversionType;
	cl_float invCenterX, invCenterY, invCenterZ;
	cl_float invRadius;
	cl_float invParamA, invParamB, invParamC;
	cl_float invScale;
	cl_float invAngle, invFrequency, invAmplitude;
	cl_float invMinR, invMaxR;
	cl_float invPreRotX, invPreRotY, invPreRotZ;
	cl_float invCenter2X, invCenter2Y, invCenter2Z;
	cl_float invRadius2;
	cl_float invWeight;
	cl_int invNSteps;
	cl_float invThreshold, invColorFactor;
	cl_int invIterStart, invIterStop;
	// v7.6 — Clip system
	cl_int clipType;
	cl_float clipCenterX, clipCenterY, clipCenterZ;
	cl_float clipSizeX, clipSizeY, clipSizeZ;
	cl_float clipRadius, clipMajorRadius;
	cl_float clipAngle, clipAmplitude, clipFrequency;
	cl_float clipSmoothK;
	cl_int clipBooleanOp;
	cl_float clipPreRotX, clipPreRotY, clipPreRotZ;
	cl_int clipNPoints;
	cl_float clipParamA, clipParamB, clipParamC;
	cl_float clipThreshold;
	cl_int clipIterStart, clipIterStop;
	// v7.7 — Jos Leys DE system (100 types)
	cl_int josLeysDeType;
	cl_float josFactor;
	cl_float josParamA, josParamB, josParamC, josParamD;
	cl_float josFreq, josAmp;
	cl_float josScale, josPhase;
	cl_int josIterStart, josIterStop;
	// v7.7 — Pseudokleinian DE system (100 types)
	cl_int pseudoKleinianDeType;
	cl_float pkFactor;
	cl_float pkParamA, pkParamB, pkParamC, pkParamD;
	cl_float pkFreq, pkAmp;
	cl_float pkScale, pkPhase;
	cl_int pkIterStart, pkIterStop;
	// v7.8 — Mandelbox Math system (200 types)
	cl_int mbMathType;
	cl_float mbFactor;
	cl_float mbParamA, mbParamB, mbParamC, mbParamD;
	cl_float mbParamE, mbParamF, mbParamG, mbParamH;
	cl_int mbIterStart, mbIterStop;
	// v7.9 — Warp Distortion system (100 types)
	cl_int warpDistType;
	cl_float wdFactor;
	cl_float wdParamA, wdParamB, wdParamC, wdParamD;
	cl_float wdFreq, wdAmp;
	cl_float wdScale, wdPhase;
	cl_int wdIterStart, wdIterStop;
	// v7.9 — Symmetry/Kaleidoscope system (100 types)
	cl_int symKalType;
	cl_float skFactor;
	cl_float skParamA, skParamB, skParamC, skParamD;
	cl_float skFreq, skAmp;
	cl_float skAngle, skOffset;
	cl_int skIterStart, skIterStop;
	// v7.9 — Abox DE system (300 types)
	cl_int aboxType;
	cl_float abFactor;
	cl_float abParamA, abParamB, abParamC, abParamD;
	cl_float abParamE, abParamF, abParamG, abParamH;
	cl_int abIterStart, abIterStop;
	// v7.10 — Noise & Procedural DE system (100 types)
	cl_int noiseType;
	cl_float noiseFactor;
	cl_float noiseParamA, noiseParamB, noiseParamC, noiseParamD;
	cl_float noiseFreq, noiseAmp;
	cl_int noiseIterStart, noiseIterStop;
	// v7.10 — Orbit Trap DE system (100 types)
	cl_int orbitTrapType;
	cl_float orbitFactor;
	cl_float orbitParamA, orbitParamB, orbitParamC, orbitParamD;
	cl_int orbitIterStart, orbitIterStop;
	// v7.12 — MandelTorus DE system (100 types)
	cl_int torusType;
	cl_float torusFactor;
	cl_float torusParamA, torusParamB, torusParamC, torusParamD;
	cl_int torusIterStart, torusIterStop;
	// Pre-computed rotation matrices
	matrix33 preRotMatrix;
	matrix33 postRotMatrix;
	matrix33 juliaCRotMatrix;
	matrix33 invPreRotMatrix;
	matrix33 clipPreRotMatrix;
} sClFormulaMutationParams;

typedef struct
{
	cl_int isHybrid;
	cl_int hybridSequence[OPENCL_FRACTAL_SEQUENCE_LENGTH];
	cl_float formulaWeight[NUMBER_OF_FRACTALS];
	sClFormulaWeightParams weightParams[NUMBER_OF_FRACTALS];
	sClFormulaMutationParams mutationParams[NUMBER_OF_FRACTALS];
	enumDEFunctionTypeCl DEFunctionType[NUMBER_OF_FRACTALS];
	enumDETypeCl DEType[NUMBER_OF_FRACTALS];
	cl_int counts[NUMBER_OF_FRACTALS];
	cl_int formulaStartIteration[NUMBER_OF_FRACTALS];
	cl_int formulaStopIteration[NUMBER_OF_FRACTALS];
	cl_int addCConstant[NUMBER_OF_FRACTALS];
	cl_int checkForBailout[NUMBER_OF_FRACTALS];
	cl_float bailout[NUMBER_OF_FRACTALS];
	cl_int juliaEnabled[NUMBER_OF_FRACTALS];
	cl_float4 juliaConstant[NUMBER_OF_FRACTALS];
	cl_float4 constantMultiplier[NUMBER_OF_FRACTALS];
	cl_float initialWAxis[NUMBER_OF_FRACTALS];
	cl_int useAdditionalBailoutCond[NUMBER_OF_FRACTALS];
	cl_int formulaMaxiter[NUMBER_OF_FRACTALS];
	enumDEAnalyticFunctionCl DEAnalyticFunction[NUMBER_OF_FRACTALS];
	enumColoringFunctionCl coloringFunction[NUMBER_OF_FRACTALS];
} sClFractalSequence;

#endif /* MANDELBULBER2_OPENCL_FRACTAL_SEQUENCE_CL_H_ */

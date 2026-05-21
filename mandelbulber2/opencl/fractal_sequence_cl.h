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
	cl_int isHybrid;
	cl_int hybridSequence[OPENCL_FRACTAL_SEQUENCE_LENGTH];
	cl_float formulaWeight[NUMBER_OF_FRACTALS];
	sClFormulaWeightParams weightParams[NUMBER_OF_FRACTALS];
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

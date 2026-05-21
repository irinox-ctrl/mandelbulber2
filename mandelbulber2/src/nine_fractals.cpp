/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2015-22 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * cNineFractals - container for 9 elements of hybrid fractal
 * Beware: On change maybe needs porting changes to opencl/fractal_sequence_cl.h
 */

#include "nine_fractals.hpp"

#include <algorithm>

#include "fractal.h"
#include "fractal_container.hpp"
#include "parameters.hpp"

// custom includes
#ifdef USE_OPENCL
#include "opencl/opencl_algebra.h"
#endif

cNineFractals::cNineFractals(std::shared_ptr<const cFractalContainer> par,
	std::shared_ptr<const cParameterContainer> generalPar)
{
	fractals.resize(NUMBER_OF_FRACTALS);
	bool useDefaultBailout = generalPar->Get<bool>("use_default_bailout");
	double commonBailout = generalPar->Get<double>("bailout");
	isHybrid = generalPar->Get<bool>("hybrid_fractal_enable");
	isBoolean = generalPar->Get<bool>("boolean_operators");
	double maxBailout = 0.0;

	// getting data from all formuala slots
	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		// allocating memory for formula data
		fractals[i].reset(new sFractal(par->at(i)));

		// getting selected formula
		fractals[i]->formula = fractal::enumFractalFormula(generalPar->Get<int>("formula", i + 1));

		// setting formula to "none" if disabled
		if (!generalPar->Get<bool>("fractal_enable", i + 1))
		{
			fractals[i]->formula = fractal::none;
		}

		// getting settings form formula
		formulaWeight[i] = generalPar->Get<double>("formula_weight", i + 1);
		formulaStartIteration[i] = generalPar->Get<int>("formula_start_iteration", i + 1);
		formulaStopIteration[i] = generalPar->Get<int>("formula_stop_iteration", i + 1);

		// Advanced weight system parameters
		weightParams[i].mode =
			enumWeightMode(generalPar->Get<int>("weight_mode", i + 1));
		weightParams[i].staticWeight = generalPar->Get<double>("weight_static", i + 1);
		weightParams[i].iterStart = generalPar->Get<int>("weight_iter_start", i + 1);
		weightParams[i].iterEnd = generalPar->Get<int>("weight_iter_end", i + 1);
		weightParams[i].startWeight = generalPar->Get<double>("weight_start", i + 1);
		weightParams[i].endWeight = generalPar->Get<double>("weight_end", i + 1);
		weightParams[i].blendMode =
			enumWeightBlendMode(generalPar->Get<int>("weight_blend_mode", i + 1));
		weightParams[i].deBase = generalPar->Get<double>("weight_de_base", i + 1);
		weightParams[i].deSensitivity =
			generalPar->Get<double>("weight_de_sensitivity", i + 1);
		weightParams[i].deThreshold = generalPar->Get<double>("weight_de_threshold", i + 1);
		weightParams[i].deModType =
			enumWeightModType(generalPar->Get<int>("weight_de_mod_type", i + 1));
		weightParams[i].zlengthBase = generalPar->Get<double>("weight_zlength_base", i + 1);
		weightParams[i].zlengthSens = generalPar->Get<double>("weight_zlength_sens", i + 1);
		weightParams[i].zlengthThreshold =
			generalPar->Get<double>("weight_zlength_threshold", i + 1);
		weightParams[i].zlengthModType =
			enumWeightModType(generalPar->Get<int>("weight_zlength_mod_type", i + 1));
		weightParams[i].conditionType =
			enumWeightConditionType(generalPar->Get<int>("weight_condition_type", i + 1));
		weightParams[i].conditionThreshold =
			generalPar->Get<double>("weight_condition_threshold", i + 1);
		weightParams[i].trueWeight = generalPar->Get<double>("weight_true", i + 1);
		weightParams[i].falseWeight = generalPar->Get<double>("weight_false", i + 1);
		weightParams[i].conditionBlend =
			enumWeightBlendMode(generalPar->Get<int>("weight_condition_blend", i + 1));
		// OrbitTrap-based weight (mode 5)
		weightParams[i].orbitTrapBase =
			generalPar->Get<double>("weight_orbit_trap_base", i + 1);
		weightParams[i].orbitTrapSensitivity =
			generalPar->Get<double>("weight_orbit_trap_sensitivity", i + 1);
		weightParams[i].orbitTrapThreshold =
			generalPar->Get<double>("weight_orbit_trap_threshold", i + 1);
		weightParams[i].orbitTrapModType =
			enumWeightModType(generalPar->Get<int>("weight_orbit_trap_mod_type", i + 1));
		// Curve-based weight (mode 6)
		weightParams[i].curveBase = generalPar->Get<double>("weight_curve_base", i + 1);
		weightParams[i].curveSensitivity =
			generalPar->Get<double>("weight_curve_sensitivity", i + 1);
		weightParams[i].curvePower = generalPar->Get<double>("weight_curve_power", i + 1);
		weightParams[i].curveModType =
			enumWeightModType(generalPar->Get<int>("weight_curve_mod_type", i + 1));
		// DE Ratio weight (mode 8)
		weightParams[i].deRatioScale = generalPar->Get<double>("weight_de_ratio_scale", i + 1);
		weightParams[i].deRatioOffset = generalPar->Get<double>("weight_de_ratio_offset", i + 1);
		weightParams[i].deRatioModType =
			enumWeightModType(generalPar->Get<int>("weight_de_ratio_mod_type", i + 1));
		// Adaptive weight (mode 9)
		weightParams[i].adaptiveStrength =
			generalPar->Get<double>("weight_adaptive_strength", i + 1);
		// Fine-tuning post-processing
		weightParams[i].weightFloor = generalPar->Get<double>("weight_floor", i + 1);
		weightParams[i].weightCeiling = generalPar->Get<double>("weight_ceiling", i + 1);
		weightParams[i].weightGamma = generalPar->Get<double>("weight_gamma", i + 1);
		weightParams[i].weightInvert = generalPar->Get<bool>("weight_invert", i + 1);
		weightParams[i].fadeInIterations = generalPar->Get<int>("weight_fade_in", i + 1);
		weightParams[i].fadeOutIterations = generalPar->Get<int>("weight_fade_out", i + 1);
		weightParams[i].deSmoothRadius = generalPar->Get<double>("weight_de_smooth_radius", i + 1);
		weightParams[i].componentBlendCurve =
			generalPar->Get<double>("weight_component_blend_curve", i + 1);
		// Separate component weights
		weightParams[i].separateComponents =
			generalPar->Get<bool>("weight_separate_components", i + 1);
		weightParams[i].zVectorWeight = generalPar->Get<double>("weight_z_vector", i + 1);
		weightParams[i].deComponentWeight =
			generalPar->Get<double>("weight_de_component", i + 1);
		weightParams[i].distComponentWeight =
			generalPar->Get<double>("weight_dist_component", i + 1);
		weightParams[i].colorComponentWeight =
			generalPar->Get<double>("weight_color_component", i + 1);

		// Formula Mutation parameters
		mutationParams[i].enabled = generalPar->Get<bool>("mutation_enabled", i + 1);
		mutationParams[i].preRotX = generalPar->Get<double>("mutation_pre_rotation_x", i + 1);
		mutationParams[i].preRotY = generalPar->Get<double>("mutation_pre_rotation_y", i + 1);
		mutationParams[i].preRotZ = generalPar->Get<double>("mutation_pre_rotation_z", i + 1);
		mutationParams[i].preScale = generalPar->Get<double>("mutation_pre_scale", i + 1);
		mutationParams[i].preOffsetX = generalPar->Get<double>("mutation_pre_offset_x", i + 1);
		mutationParams[i].preOffsetY = generalPar->Get<double>("mutation_pre_offset_y", i + 1);
		mutationParams[i].preOffsetZ = generalPar->Get<double>("mutation_pre_offset_z", i + 1);
		mutationParams[i].preAbsX = generalPar->Get<bool>("mutation_pre_abs_x", i + 1);
		mutationParams[i].preAbsY = generalPar->Get<bool>("mutation_pre_abs_y", i + 1);
		mutationParams[i].preAbsZ = generalPar->Get<bool>("mutation_pre_abs_z", i + 1);
		mutationParams[i].postRotX = generalPar->Get<double>("mutation_post_rotation_x", i + 1);
		mutationParams[i].postRotY = generalPar->Get<double>("mutation_post_rotation_y", i + 1);
		mutationParams[i].postRotZ = generalPar->Get<double>("mutation_post_rotation_z", i + 1);
		mutationParams[i].postScale = generalPar->Get<double>("mutation_post_scale", i + 1);
		mutationParams[i].postOffsetX = generalPar->Get<double>("mutation_post_offset_x", i + 1);
		mutationParams[i].postOffsetY = generalPar->Get<double>("mutation_post_offset_y", i + 1);
		mutationParams[i].postOffsetZ = generalPar->Get<double>("mutation_post_offset_z", i + 1);
		mutationParams[i].swizzle =
			enumMutationSwizzle(generalPar->Get<int>("mutation_swizzle", i + 1));
		mutationParams[i].foldType =
			enumMutationFoldType(generalPar->Get<int>("mutation_fold_type", i + 1));
		mutationParams[i].foldPosition =
			enumMutationFoldPosition(generalPar->Get<int>("mutation_fold_position", i + 1));
		mutationParams[i].foldLimit = generalPar->Get<double>("mutation_fold_limit", i + 1);
		mutationParams[i].foldValue = generalPar->Get<double>("mutation_fold_value", i + 1);
		mutationParams[i].kaleidoscopeSides =
			generalPar->Get<int>("mutation_kaleidoscope_sides", i + 1);
		mutationParams[i].warpType =
			enumMutationWarpType(generalPar->Get<int>("mutation_warp_type", i + 1));
		mutationParams[i].warpFrequency = generalPar->Get<double>("mutation_warp_frequency", i + 1);
		mutationParams[i].warpAmplitude = generalPar->Get<double>("mutation_warp_amplitude", i + 1);
		mutationParams[i].mathType =
			enumMutationMathType(generalPar->Get<int>("mutation_math_type", i + 1));
		mutationParams[i].mathP1 = generalPar->Get<double>("mutation_math_p1", i + 1);
		mutationParams[i].mathP2 = generalPar->Get<double>("mutation_math_p2", i + 1);
		mutationParams[i].mathP3 = generalPar->Get<double>("mutation_math_p3", i + 1);
		mutationParams[i].mathP4 = generalPar->Get<double>("mutation_math_p4", i + 1);
		mutationParams[i].mathP5 = generalPar->Get<double>("mutation_math_p5", i + 1);
		mutationParams[i].mathP6 = generalPar->Get<double>("mutation_math_p6", i + 1);
		mutationParams[i].mathP7 = generalPar->Get<double>("mutation_math_p7", i + 1);
		mutationParams[i].mathP8 = generalPar->Get<double>("mutation_math_p8", i + 1);
		mutationParams[i].mathMix = generalPar->Get<double>("mutation_math_mix", i + 1);
		mutationParams[i].zMix = generalPar->Get<double>("mutation_z_mix", i + 1);
		mutationParams[i].deScale = generalPar->Get<double>("mutation_de_scale", i + 1);
		mutationParams[i].iterationStart =
			generalPar->Get<int>("mutation_iteration_start", i + 1);
		mutationParams[i].iterationStop =
			generalPar->Get<int>("mutation_iteration_stop", i + 1);

		// Smart defaults: PK/JK formulas get Möbius (Bilinear) math preset
		fractal::enumFractalFormula f = fractals[i]->formula;
		bool isPKJK = (f == fractal::pseudoKleinian || f == fractal::pseudoKleinian4d
			|| f == fractal::pseudoKleinianMod1 || f == fractal::pseudoKleinianMod2
			|| f == fractal::pseudoKleinianMod3 || f == fractal::pseudoKleinianMod4
			|| f == fractal::pseudoKleinianMod5 || f == fractal::pseudoKleinianMod6
			|| f == fractal::pseudoKleinianMod7 || f == fractal::pseudoKleinianStdDE
			|| f == fractal::josKleinian || f == fractal::josKleinianV2
			|| f == fractal::josKleinianV3 || f == fractal::josKleinianV4);
		if (isPKJK && mutationParams[i].mathType == mutMathNone)
		{
			mutationParams[i].mathType = mutMathBilinear;
			mutationParams[i].mathP1 = 1.0;   // a: identity scale
			mutationParams[i].mathP2 = 0.5;   // b: translation offset
			mutationParams[i].mathP3 = 0.1;   // c: inversion strength
			mutationParams[i].mathP4 = 1.0;   // d: denominator base
			mutationParams[i].mathMix = 0.3;   // subtle blend — not overwhelming
		}

		// Pre-compute rotation matrices
		if (mutationParams[i].enabled)
		{
			mutationParams[i].preRotMatrix.SetRotation2(CVector3(
				mutationParams[i].preRotX / 180.0 * M_PI,
				mutationParams[i].preRotY / 180.0 * M_PI,
				mutationParams[i].preRotZ / 180.0 * M_PI));
			mutationParams[i].postRotMatrix.SetRotation2(CVector3(
				mutationParams[i].postRotX / 180.0 * M_PI,
				mutationParams[i].postRotY / 180.0 * M_PI,
				mutationParams[i].postRotZ / 180.0 * M_PI));
		}

		DEType[i] = fractal::deltaDEType;
		DEFunctionType[i] = fractal::logarithmicDEFunction;

		fractalFormulaFunctions[i] = newFractalList[GetIndexOnFractalList(fractals[i]->formula)];
		DEAnalyticFunction[i] =
			newFractalList[GetIndexOnFractalList(fractals[i]->formula)]->getDeAnalyticFunction();
		coloringFunction[i] =
			newFractalList[GetIndexOnFractalList(fractals[i]->formula)]->getColoringFunction();

		// decide if use check for bailout
		if (isBoolean || (!isBoolean && !isHybrid))
			checkForBailout[i] = true;
		else
			checkForBailout[i] = generalPar->Get<bool>("check_for_bailout", i + 1);

		// decide if use addition of C constant
		bool addc;
		if (newFractalList[GetIndexOnFractalList(fractals[i]->formula)]->getCpixelAddition()
				== fractal::cpixelAlreadyHas)
		{
			addc = false;
		}
		else
		{
			addc = !generalPar->Get<bool>("dont_add_c_constant", i + 1);
			if (newFractalList[GetIndexOnFractalList(fractals[i]->formula)]->getCpixelAddition()
					== fractal::cpixelDisabledByDefault)
				addc = !addc;
		}
		addCConstant[i] = addc;

		// default bailout or global one
		if (useDefaultBailout)
		{
			if (isHybrid)
				maxBailout = qMax(maxBailout,
					newFractalList[GetIndexOnFractalList(fractals[i]->formula)]->getDefaultBailout());
			else
				bailout[i] =
					newFractalList[GetIndexOnFractalList(fractals[i]->formula)]->getDefaultBailout();
		}
		else
		{
			bailout[i] = commonBailout;
		}

		// Julia parameters - local or global
		if (isBoolean)
		{
			juliaEnabled[i] = generalPar->Get<bool>("julia_mode", i + 1);
			juliaConstant[i] = generalPar->Get<CVector3>("julia_c", i + 1);
			constantMultiplier[i] = generalPar->Get<CVector3>("fractal_constant_factor", i + 1);
			initialWAxis[i] = generalPar->Get<double>("initial_waxis", i + 1);
			formulaMaxiter[i] = generalPar->Get<double>("formula_maxiter", i + 1);
		}
		else
		{
			juliaEnabled[i] = generalPar->Get<bool>("julia_mode");
			juliaConstant[i] = generalPar->Get<CVector3>("julia_c");
			constantMultiplier[i] = generalPar->Get<CVector3>("fractal_constant_factor");
			initialWAxis[i] = generalPar->Get<double>("initial_waxis");
			formulaMaxiter[i] = generalPar->Get<double>("N");
		}

		useAdditionalBailoutCond[i] = false;
		if (isBoolean)
		{
			if (newFractalList[GetIndexOnFractalList(fractals[i]->formula)]->getDeFunctionType()
						== fractal::pseudoKleinianDEFunction
					|| newFractalList[GetIndexOnFractalList(fractals[i]->formula)]->getDeFunctionType()
							 == fractal::josKleinianDEFunction)
			{
				useAdditionalBailoutCond[i] = true;
			}
		}
	}

	// common bailout for all hybrid components
	if (isHybrid && useDefaultBailout)
	{
		for (double &bailoutIt : bailout)
		{
			bailoutIt = maxBailout;
		}
	}

	forceDeltaDE =
		fractal::enumDEMethod(generalPar->Get<int>("delta_DE_method")) == fractal::forceDeltaDEMethod;

	forceAnalyticDE =
		fractal::enumDEMethod(generalPar->Get<int>("delta_DE_method")) == fractal::forceAnalyticDE;

	optimizedDEType = fractal::withoutDEFunction;
	useOptimizedDE = false;

	maxN = generalPar->Get<int>("N");
	maxFractalIndex = 0;
	CreateSequence(generalPar);

	if (isHybrid)
	{
		DEType[0] = fractal::analyticDEType;
		useOptimizedDE = true;

		if (fractal::enumDEFunctionType(generalPar->Get<int>("delta_DE_function"))
				== fractal::preferredDEFunction)
		{
			// finding preferred delta DE function

			// table to check the which DE type is the most popular
			int DEFunctionCount[fractal::numberOfDEFunctions + 1];
			for (int i = 1; i <= fractal::numberOfDEFunctions; i++)
				DEFunctionCount[i] = 0;

			for (int f = 0; f < NUMBER_OF_FRACTALS; f++)
			{
				fractal::enumFractalFormula formula = fractals[f]->formula;
				int index = GetIndexOnFractalList(formula);

				// looking for the best DE function for DeltaDE mode

				// count usage of DE functions
				fractal::enumDEFunctionType DEFunction = newFractalList[index]->getDeFunctionType();
				if (DEFunction != fractal::withoutDEFunction)
				{
					DEFunctionCount[DEFunction] += counts[f];
				}

				// looking if it's possible to use analyticDEType
				if (!forceDeltaDE && newFractalList[index]->getInternalId() != fractal::none)
				{
					if (optimizedDEType == fractal::withoutDEFunction)
					{
						optimizedDEType = DEFunction;
					}

					if (!forceAnalyticDE && newFractalList[index]->getDeType() == fractal::deltaDEType)
					{
						DEType[0] = fractal::deltaDEType;
						useOptimizedDE = false;
						forceDeltaDE = true;
					}
				}
			}

			// checking if used dIFS formula
			if (DEFunctionCount[fractal::customDEFunction] > 0)
			{
				DEFunctionType[0] = fractal::customDEFunction;
			}
			else // use method which used in the highest iteration count
			{
				int maxCount = -1;
				for (int i = 1; i <= fractal::numberOfDEFunctions; i++)
				{
					if (DEFunctionCount[i] > maxCount)
					{
						maxCount = DEFunctionCount[i];
						DEFunctionType[0] = fractal::enumDEFunctionType(i);
					}
				}
			}
		}
		else
		{
			for (int f = 0; f < NUMBER_OF_FRACTALS; f++)
			{
				fractal::enumFractalFormula formula = fractals[f]->formula;
				int index = GetIndexOnFractalList(formula);
				if (!forceAnalyticDE && newFractalList[index]->getDeType() == fractal::deltaDEType)
				{
					DEType[0] = fractal::deltaDEType;
				}
			}
			DEFunctionType[0] = fractal::enumDEFunctionType(generalPar->Get<int>("delta_DE_function"));
		}

		if (forceDeltaDE) DEType[0] = fractal::deltaDEType;
		if (forceAnalyticDE) DEType[0] = fractal::analyticDEType;
	}
	else // not hybrid or boolean
	{
		for (int f = 0; f < NUMBER_OF_FRACTALS; f++)
		{
			fractal::enumFractalFormula formula = fractals[f]->formula;
			int index = GetIndexOnFractalList(formula);

			DEType[f] = newFractalList[index]->getDeType();
			DEFunctionType[f] = newFractalList[index]->getDeFunctionType();
			DEAnalyticFunction[f] = newFractalList[index]->getDeAnalyticFunction();

			if (forceDeltaDE) DEType[f] = fractal::deltaDEType;
			if (forceAnalyticDE) DEType[f] = fractal::analyticDEType;

			if (fractal::enumDEFunctionType(generalPar->Get<int>("delta_DE_function"))
					!= fractal::preferredDEFunction)
			{
				DEFunctionType[f] = fractal::enumDEFunctionType(generalPar->Get<int>("delta_DE_function"));

				switch (DEFunctionType[f])
				{
					case fractal::linearDEFunction:
						DEAnalyticFunction[f] = fractal::analyticFunctionLinear;
						break;
					case fractal::logarithmicDEFunction:
						DEAnalyticFunction[f] = fractal::analyticFunctionLogarithmic;
						break;
					case fractal::pseudoKleinianDEFunction:
						DEAnalyticFunction[f] = fractal::analyticFunctionPseudoKleinian;
						break;
					case fractal::josKleinianDEFunction:
						DEAnalyticFunction[f] = fractal::analyticFunctionJosKleinian;
						break;
					case fractal::customDEFunction:
						DEAnalyticFunction[f] = fractal::analyticFunctionCustomDE;
						break;
					case fractal::maxAxisDEFunction:
						DEAnalyticFunction[f] = fractal::analyticFunctionMaxAxis;
						break;
					default: DEAnalyticFunction[f] = fractal::analyticFunctionLinear; break;
				}
			}
		}
	}

	if (isHybrid)
		for (int f = 0; f < NUMBER_OF_FRACTALS; f++)
		{
			if (newFractalList[GetIndexOnFractalList(fractals[f]->formula)]->getDeFunctionType()
						== fractal::pseudoKleinianDEFunction
					|| newFractalList[GetIndexOnFractalList(fractals[f]->formula)]->getDeFunctionType()
							 == fractal::josKleinianDEFunction)
			{
				useAdditionalBailoutCond[f] = true;
			}
		}
	else if (!isBoolean)
	{
		if (newFractalList[GetIndexOnFractalList(fractals[0]->formula)]->getDeFunctionType()
					== fractal::pseudoKleinianDEFunction
				|| newFractalList[GetIndexOnFractalList(fractals[0]->formula)]->getDeFunctionType()
						 == fractal::josKleinianDEFunction)
		{
			useAdditionalBailoutCond[0] = true;
		}
	}
}

void cNineFractals::CreateSequence(std::shared_ptr<const cParameterContainer> generalPar)
{
	hybridSequenceLength = maxN * 5;
	hybridSequence.resize(hybridSequenceLength);
	int repeatFrom = generalPar->Get<int>("repeat_from");

	int fractalNo = 0;
	int counter = 0;

	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		counts[i] = generalPar->Get<int>("formula_iterations", i + 1);
	}

	for (int i = 0; i < hybridSequenceLength; i++)
	{
		if (isHybrid)
		{
			counter++;

			int repeatCount = 0;
			while ((fractals[fractalNo]->formula == fractal::none || i < formulaStartIteration[fractalNo]
							 || i > formulaStopIteration[fractalNo])
						 && repeatCount < NUMBER_OF_FRACTALS)
			{
				fractalNo++;
				if (fractalNo >= NUMBER_OF_FRACTALS) fractalNo = repeatFrom - 1;
				repeatCount++;
			}
			hybridSequence[i] = fractalNo;
			if (fractals[fractalNo]->formula != fractal::none && fractalNo > maxFractalIndex)
				maxFractalIndex = fractalNo;

			if (counter >= counts[fractalNo])
			{
				counter = 0;
				fractalNo++;
				if (fractalNo >= NUMBER_OF_FRACTALS) fractalNo = repeatFrom - 1;
			}
		}
		else
		{
			hybridSequence[i] = 0;
		}
	}
}

int cNineFractals::GetSequence(const int i) const
{
	if (i < hybridSequenceLength)
	{
		return hybridSequence[i];
	}
	else
	{
		return 0;
	}
}

fractal::enumDEType cNineFractals::GetDEType(int formulaIndex) const
{
	fractal::enumDEType type;
	if (formulaIndex == -1)
	{
		type = DEType[0];
	}
	else
	{
		type = DEType[formulaIndex];
	}
	return type;
}

fractal::enumDEFunctionType cNineFractals::GetDEFunctionType(int formulaIndex) const
{
	fractal::enumDEFunctionType type;
	if (formulaIndex == -1)
	{
		type = DEFunctionType[0];
	}
	else
	{
		type = DEFunctionType[formulaIndex];
	}
	return type;
}

QString cNineFractals::GetDETypeString() const
{
	QString text;
	if (DEType[0] == fractal::analyticDEType)
	{
		text += "analytic";
	}
	else
	{
		text += "deltaDE";
	}

	if (isBoolean)
	{
		text = "different for each fractal";
	}
	else
	{
		switch (DEFunctionType[0])
		{
			case fractal::logarithmicDEFunction: text += " logarithmic"; break;
			case fractal::linearDEFunction: text += " linear"; break;
			case fractal::pseudoKleinianDEFunction: text += " pseudo kleinian"; break;
			case fractal::josKleinianDEFunction: text += " jos kleinian"; break;
			case fractal::customDEFunction: text += " custom"; break;
			case fractal::maxAxisDEFunction: text += " maxAxis"; break;
			// case fractal::testingDEFunction: text += " testing DE"; break;
			default: text += "unknown"; break;
		}
	}

	return text;
}

int cNineFractals::GetIndexOnFractalList(fractal::enumFractalFormula formula)
{
	for (int i = 0; i < newFractalList.size(); i++)
	{
		if (newFractalList[i]->getInternalId() == formula)
		{
			return i;
		}
	}
	return 0;
}

double cNineFractals::CalculateWeight(
	int formulaIndex, int iteration, double currentDE, double zLength,
	double currentDist, fractal::enumDEFunctionType deFunc) const
{
	const sFormulaWeightParams &wp = weightParams[formulaIndex];

	double weight = 1.0;

	switch (wp.mode)
	{
		case weightModeStatic:
		{
			weight = wp.staticWeight;
			break;
		}
		case weightModeIteration:
		{
			if (iteration <= wp.iterStart)
			{
				weight = wp.startWeight;
			}
			else if (iteration >= wp.iterEnd)
			{
				weight = wp.endWeight;
			}
			else
			{
				double t = double(iteration - wp.iterStart) / double(wp.iterEnd - wp.iterStart);
				switch (wp.blendMode)
				{
					case weightBlendLinear: weight = wp.startWeight + t * (wp.endWeight - wp.startWeight); break;
					case weightBlendSmooth:
					{
						double s = t * t * (3.0 - 2.0 * t);
						weight = wp.startWeight + s * (wp.endWeight - wp.startWeight);
						break;
					}
					case weightBlendStep: weight = (t < 0.5) ? wp.startWeight : wp.endWeight; break;
					case weightBlendMultiply:
					{
						weight = wp.startWeight * pow(wp.endWeight / max(wp.startWeight, 1e-15), t);
						break;
					}
					case weightBlendPower:
					{
						weight = wp.startWeight + pow(t, 2.0) * (wp.endWeight - wp.startWeight);
						break;
					}
					case weightBlendMin:
						weight = min(wp.startWeight, wp.endWeight);
						break;
					case weightBlendMax:
						weight = max(wp.startWeight, wp.endWeight);
						break;
				}
			}
			break;
		}
		case weightModeDE:
		{
			double smoothDE = currentDE;
			if (wp.deSmoothRadius > 0.0)
			{
				double dist = fabs(currentDE - wp.deThreshold);
				if (dist < wp.deSmoothRadius)
				{
					double t = dist / wp.deSmoothRadius;
					smoothDE = wp.deThreshold + (currentDE - wp.deThreshold) * t * t * (3.0 - 2.0 * t);
				}
			}
			double delta = smoothDE - wp.deThreshold;
			double factor = delta * wp.deSensitivity;
			switch (wp.deModType)
			{
				case weightModLinear:
					weight = wp.deBase + factor;
					break;
				case weightModSmooth:
					weight = wp.deBase + factor * factor * (factor > 0 ? 1.0 : -1.0);
					break;
				case weightModExponential:
					weight = wp.deBase * exp(factor);
					break;
				case weightModInverse:
					weight = (fabs(currentDE) > 1e-15)
						? wp.deBase * (wp.deThreshold / currentDE) : 1.0;
					break;
				case weightModSigmoid:
					weight = wp.deBase + (1.0 - wp.deBase) / (1.0 + exp(-factor));
					break;
			}
			weight = qBound(0.0, weight, 1.0);
			break;
		}
		case weightModeZLength:
		{
			double delta = zLength - wp.zlengthThreshold;
			double factor = delta * wp.zlengthSens;
			switch (wp.zlengthModType)
			{
				case weightModLinear:
					weight = wp.zlengthBase + factor;
					break;
				case weightModSmooth:
					weight = wp.zlengthBase + factor * factor * (factor > 0 ? 1.0 : -1.0);
					break;
				case weightModExponential:
					weight = wp.zlengthBase * exp(factor);
					break;
				case weightModInverse:
					weight = (fabs(zLength) > 1e-15)
						? wp.zlengthBase * (wp.zlengthThreshold / zLength) : 1.0;
					break;
				case weightModSigmoid:
					weight = wp.zlengthBase + (1.0 - wp.zlengthBase) / (1.0 + exp(-factor));
					break;
			}
			weight = qBound(0.0, weight, 1.0);
			break;
		}
		case weightModeConditional:
		{
			double testValue = 0.0;
			switch (wp.conditionType)
			{
				case weightCondDE: testValue = currentDE; break;
				case weightCondZLength: testValue = zLength; break;
				case weightCondDist: testValue = currentDist; break;
				case weightCondIteration: testValue = double(iteration); break;
			}
			bool conditionMet = (testValue < wp.conditionThreshold);
			switch (wp.conditionBlend)
			{
				case weightBlendStep:
					weight = conditionMet ? wp.trueWeight : wp.falseWeight;
					break;
				case weightBlendLinear:
				{
					double blend = (wp.conditionThreshold > 1e-15)
						? qBound(0.0, testValue / wp.conditionThreshold, 1.0) : (conditionMet ? 0.0 : 1.0);
					weight = wp.trueWeight * (1.0 - blend) + wp.falseWeight * blend;
					break;
				}
				case weightBlendSmooth:
				{
					double blend = (wp.conditionThreshold > 1e-15)
						? qBound(0.0, testValue / wp.conditionThreshold, 1.0) : (conditionMet ? 0.0 : 1.0);
					double s = blend * blend * (3.0 - 2.0 * blend);
					weight = wp.trueWeight * (1.0 - s) + wp.falseWeight * s;
					break;
				}
				default:
					weight = conditionMet ? wp.trueWeight : wp.falseWeight;
					break;
			}
			break;
		}
		case weightModeOrbitTrap:
		{
			double orbitDist = zLength;
			double delta = orbitDist - wp.orbitTrapThreshold;
			double factor = delta * wp.orbitTrapSensitivity;
			switch (wp.orbitTrapModType)
			{
				case weightModLinear:
					weight = wp.orbitTrapBase + factor;
					break;
				case weightModSmooth:
					weight = wp.orbitTrapBase + factor * factor * (factor > 0 ? 1.0 : -1.0);
					break;
				case weightModExponential:
					weight = wp.orbitTrapBase * exp(factor);
					break;
				case weightModInverse:
					weight = (fabs(orbitDist) > 1e-15)
						? wp.orbitTrapBase * (wp.orbitTrapThreshold / orbitDist) : 1.0;
					break;
				case weightModSigmoid:
					weight = wp.orbitTrapBase + (1.0 - wp.orbitTrapBase) / (1.0 + exp(-factor));
					break;
			}
			weight = qBound(0.0, weight, 1.0);
			break;
		}
		case weightModeCurve:
		{
			double normalized = (wp.curveBase > 1e-15) ? currentDE / wp.curveBase : currentDE;
			double powered = pow(fabs(normalized * wp.curveSensitivity), wp.curvePower);
			switch (wp.curveModType)
			{
				case weightModLinear:
					weight = wp.curveBase + powered * (normalized >= 0 ? 1.0 : -1.0);
					break;
				case weightModSmooth:
				{
					double s = powered * powered * (3.0 - 2.0 * powered);
					weight = wp.curveBase + s;
					break;
				}
				case weightModExponential:
					weight = wp.curveBase * exp(powered - 1.0);
					break;
				case weightModInverse:
					weight = (powered > 1e-15) ? wp.curveBase / powered : 1.0;
					break;
				case weightModSigmoid:
					weight = wp.curveBase + (1.0 - wp.curveBase) / (1.0 + exp(-(powered - 0.5) * 6.0));
					break;
			}
			weight = qBound(0.0, weight, 1.0);
			break;
		}
		case weightModeTransformPassthrough:
		{
			weight = 1.0;
			break;
		}
		case weightModeDERatio:
		{
			// Weight based on ratio of current DE to a reference scale
			double ratio = (wp.deRatioOffset > 1e-15)
				? currentDE / wp.deRatioOffset : currentDE;
			ratio *= wp.deRatioScale;
			switch (wp.deRatioModType)
			{
				case weightModLinear:
					weight = qBound(0.0, ratio, 1.0);
					break;
				case weightModSmooth:
				{
					double clamped = qBound(0.0, ratio, 1.0);
					weight = clamped * clamped * (3.0 - 2.0 * clamped);
					break;
				}
				case weightModExponential:
					weight = 1.0 - exp(-fabs(ratio));
					break;
				case weightModInverse:
					weight = (fabs(ratio) > 1e-15) ? qBound(0.0, 1.0 / ratio, 1.0) : 1.0;
					break;
				case weightModSigmoid:
					weight = 1.0 / (1.0 + exp(-(ratio - 0.5) * 6.0));
					break;
			}
			break;
		}
		case weightModeAdaptive:
		{
			// Auto-select weight function based on formula's DE type
			double str = wp.adaptiveStrength;
			if (deFunc == fractal::logarithmicDEFunction)
			{
				// Logarithmic: sigmoid curve — works well with exponential DE growth
				double normalized = (currentDE > 1e-15) ? log(1.0 + currentDE) : 0.0;
				weight = 1.0 / (1.0 + exp(-(normalized - 0.5) * 4.0 * str));
			}
			else if (deFunc == fractal::linearDEFunction)
			{
				// Linear: smooth interpolation
				double normalized = qBound(0.0, currentDE * str, 1.0);
				weight = normalized * normalized * (3.0 - 2.0 * normalized);
			}
			else if (deFunc == fractal::customDEFunction)
			{
				// DIFS: inverse distance — closer = stronger weight
				double dist = (currentDist > 1e-15) ? currentDist : currentDE;
				weight = (dist > 1e-15) ? qBound(0.0, str / (str + dist), 1.0) : 1.0;
			}
			else if (deFunc == fractal::pseudoKleinianDEFunction
				|| deFunc == fractal::josKleinianDEFunction)
			{
				// PK/JK: sigmoid on bounded DE
				weight = 1.0 / (1.0 + exp(-(currentDE - 0.5) * 6.0 * str));
			}
			else if (deFunc == fractal::withoutDEFunction)
			{
				// Transform: always full weight
				weight = 1.0;
			}
			else
			{
				// Fallback: smooth
				double normalized = qBound(0.0, currentDE * str, 1.0);
				weight = normalized * normalized * (3.0 - 2.0 * normalized);
			}
			weight = qBound(0.0, weight, 1.0);
			break;
		}
	}

	// --- Fine-tuning post-processing ---

	// Gamma (power curve)
	if (wp.weightGamma != 1.0 && weight > 0.0 && weight < 1.0)
	{
		weight = pow(weight, wp.weightGamma);
	}

	// Invert
	if (wp.weightInvert)
	{
		weight = 1.0 - weight;
	}

	// Floor/ceiling clamp
	weight = qBound(wp.weightFloor, weight, wp.weightCeiling);

	// Iteration fade-in: smooth ramp from 0 to weight over fadeInIterations
	if (wp.fadeInIterations > 0)
	{
		if (iteration < wp.fadeInIterations)
		{
			double fadeT = double(iteration) / double(wp.fadeInIterations);
			double fadeFactor = fadeT * fadeT * (3.0 - 2.0 * fadeT); // smoothstep
			weight *= fadeFactor;
		}
	}

	// Iteration fade-out: smooth ramp from weight to 0 over fadeOutIterations before max
	if (wp.fadeOutIterations > 0)
	{
		int maxIter = (wp.mode == weightModeIteration) ? wp.iterEnd : 250;
		int fadeStart = maxIter - wp.fadeOutIterations;
		if (iteration > fadeStart && iteration <= maxIter)
		{
			double fadeT = double(maxIter - iteration) / double(wp.fadeOutIterations);
			double fadeFactor = fadeT * fadeT * (3.0 - 2.0 * fadeT);
			weight *= fadeFactor;
		}
	}

	return weight;
}

#ifdef USE_OPENCL
void cNineFractals::CopyToOpenclData(sClFractalSequence *sequence) const
{
	sequence->isHybrid = isHybrid;

	for (int i = 0; i < OPENCL_FRACTAL_SEQUENCE_LENGTH; i++)
	{
		if (i < hybridSequenceLength)
		{
			sequence->hybridSequence[i] = hybridSequence[i];
		}
		else
		{
			sequence->hybridSequence[i] = 0;
		}
	}

	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		sequence->formulaWeight[i] = formulaWeight[i];

		// Copy advanced weight parameters
		sequence->weightParams[i].mode = static_cast<cl_int>(weightParams[i].mode);
		sequence->weightParams[i].staticWeight = weightParams[i].staticWeight;
		sequence->weightParams[i].iterStart = weightParams[i].iterStart;
		sequence->weightParams[i].iterEnd = weightParams[i].iterEnd;
		sequence->weightParams[i].startWeight = weightParams[i].startWeight;
		sequence->weightParams[i].endWeight = weightParams[i].endWeight;
		sequence->weightParams[i].blendMode = static_cast<cl_int>(weightParams[i].blendMode);
		sequence->weightParams[i].deBase = weightParams[i].deBase;
		sequence->weightParams[i].deSensitivity = weightParams[i].deSensitivity;
		sequence->weightParams[i].deThreshold = weightParams[i].deThreshold;
		sequence->weightParams[i].deModType = static_cast<cl_int>(weightParams[i].deModType);
		sequence->weightParams[i].zlengthBase = weightParams[i].zlengthBase;
		sequence->weightParams[i].zlengthSens = weightParams[i].zlengthSens;
		sequence->weightParams[i].zlengthThreshold = weightParams[i].zlengthThreshold;
		sequence->weightParams[i].zlengthModType = static_cast<cl_int>(weightParams[i].zlengthModType);
		sequence->weightParams[i].conditionType = static_cast<cl_int>(weightParams[i].conditionType);
		sequence->weightParams[i].conditionThreshold = weightParams[i].conditionThreshold;
		sequence->weightParams[i].trueWeight = weightParams[i].trueWeight;
		sequence->weightParams[i].falseWeight = weightParams[i].falseWeight;
		sequence->weightParams[i].conditionBlend = static_cast<cl_int>(weightParams[i].conditionBlend);
		// OrbitTrap (mode 5)
		sequence->weightParams[i].orbitTrapBase = weightParams[i].orbitTrapBase;
		sequence->weightParams[i].orbitTrapSensitivity = weightParams[i].orbitTrapSensitivity;
		sequence->weightParams[i].orbitTrapThreshold = weightParams[i].orbitTrapThreshold;
		sequence->weightParams[i].orbitTrapModType = static_cast<cl_int>(weightParams[i].orbitTrapModType);
		// Curve (mode 6)
		sequence->weightParams[i].curveBase = weightParams[i].curveBase;
		sequence->weightParams[i].curveSensitivity = weightParams[i].curveSensitivity;
		sequence->weightParams[i].curvePower = weightParams[i].curvePower;
		sequence->weightParams[i].curveModType = static_cast<cl_int>(weightParams[i].curveModType);
		// DE Ratio (mode 8)
		sequence->weightParams[i].deRatioScale = weightParams[i].deRatioScale;
		sequence->weightParams[i].deRatioOffset = weightParams[i].deRatioOffset;
		sequence->weightParams[i].deRatioModType = static_cast<cl_int>(weightParams[i].deRatioModType);
		// Adaptive (mode 9)
		sequence->weightParams[i].adaptiveStrength = weightParams[i].adaptiveStrength;
		// Fine-tuning post-processing
		sequence->weightParams[i].weightFloor = weightParams[i].weightFloor;
		sequence->weightParams[i].weightCeiling = weightParams[i].weightCeiling;
		sequence->weightParams[i].weightGamma = weightParams[i].weightGamma;
		sequence->weightParams[i].weightInvert = weightParams[i].weightInvert ? 1 : 0;
		sequence->weightParams[i].fadeInIterations = weightParams[i].fadeInIterations;
		sequence->weightParams[i].fadeOutIterations = weightParams[i].fadeOutIterations;
		sequence->weightParams[i].deSmoothRadius = weightParams[i].deSmoothRadius;
		sequence->weightParams[i].componentBlendCurve = weightParams[i].componentBlendCurve;
		// Components
		sequence->weightParams[i].separateComponents = weightParams[i].separateComponents ? 1 : 0;
		sequence->weightParams[i].zVectorWeight = weightParams[i].zVectorWeight;
		sequence->weightParams[i].deComponentWeight = weightParams[i].deComponentWeight;
		sequence->weightParams[i].distComponentWeight = weightParams[i].distComponentWeight;
		sequence->weightParams[i].colorComponentWeight = weightParams[i].colorComponentWeight;

		// Formula Mutation parameters
		sequence->mutationParams[i].enabled = mutationParams[i].enabled ? 1 : 0;
		sequence->mutationParams[i].preRotX = mutationParams[i].preRotX;
		sequence->mutationParams[i].preRotY = mutationParams[i].preRotY;
		sequence->mutationParams[i].preRotZ = mutationParams[i].preRotZ;
		sequence->mutationParams[i].preScale = mutationParams[i].preScale;
		sequence->mutationParams[i].preOffsetX = mutationParams[i].preOffsetX;
		sequence->mutationParams[i].preOffsetY = mutationParams[i].preOffsetY;
		sequence->mutationParams[i].preOffsetZ = mutationParams[i].preOffsetZ;
		sequence->mutationParams[i].preAbsX = mutationParams[i].preAbsX ? 1 : 0;
		sequence->mutationParams[i].preAbsY = mutationParams[i].preAbsY ? 1 : 0;
		sequence->mutationParams[i].preAbsZ = mutationParams[i].preAbsZ ? 1 : 0;
		sequence->mutationParams[i].postRotX = mutationParams[i].postRotX;
		sequence->mutationParams[i].postRotY = mutationParams[i].postRotY;
		sequence->mutationParams[i].postRotZ = mutationParams[i].postRotZ;
		sequence->mutationParams[i].postScale = mutationParams[i].postScale;
		sequence->mutationParams[i].postOffsetX = mutationParams[i].postOffsetX;
		sequence->mutationParams[i].postOffsetY = mutationParams[i].postOffsetY;
		sequence->mutationParams[i].postOffsetZ = mutationParams[i].postOffsetZ;
		sequence->mutationParams[i].swizzle = static_cast<cl_int>(mutationParams[i].swizzle);
		sequence->mutationParams[i].foldType = static_cast<cl_int>(mutationParams[i].foldType);
		sequence->mutationParams[i].foldPosition = static_cast<cl_int>(mutationParams[i].foldPosition);
		sequence->mutationParams[i].foldLimit = mutationParams[i].foldLimit;
		sequence->mutationParams[i].foldValue = mutationParams[i].foldValue;
		sequence->mutationParams[i].kaleidoscopeSides = mutationParams[i].kaleidoscopeSides;
		sequence->mutationParams[i].warpType = static_cast<cl_int>(mutationParams[i].warpType);
		sequence->mutationParams[i].warpFrequency = mutationParams[i].warpFrequency;
		sequence->mutationParams[i].warpAmplitude = mutationParams[i].warpAmplitude;
		sequence->mutationParams[i].mathType = static_cast<cl_int>(mutationParams[i].mathType);
		sequence->mutationParams[i].mathP1 = mutationParams[i].mathP1;
		sequence->mutationParams[i].mathP2 = mutationParams[i].mathP2;
		sequence->mutationParams[i].mathP3 = mutationParams[i].mathP3;
		sequence->mutationParams[i].mathP4 = mutationParams[i].mathP4;
		sequence->mutationParams[i].mathP5 = mutationParams[i].mathP5;
		sequence->mutationParams[i].mathP6 = mutationParams[i].mathP6;
		sequence->mutationParams[i].mathP7 = mutationParams[i].mathP7;
		sequence->mutationParams[i].mathP8 = mutationParams[i].mathP8;
		sequence->mutationParams[i].mathMix = mutationParams[i].mathMix;
		sequence->mutationParams[i].zMix = mutationParams[i].zMix;
		sequence->mutationParams[i].deScale = mutationParams[i].deScale;
		sequence->mutationParams[i].iterationStart = mutationParams[i].iterationStart;
		sequence->mutationParams[i].iterationStop = mutationParams[i].iterationStop;
		// Copy rotation matrices (3x3 = 9 floats each)
		if (mutationParams[i].enabled)
		{
			CMatrix33 preM = mutationParams[i].preRotMatrix.GetMatrix();
			CMatrix33 postM = mutationParams[i].postRotMatrix.GetMatrix();
			sequence->mutationParams[i].preRotMatrix[0] = preM.m11;
			sequence->mutationParams[i].preRotMatrix[1] = preM.m12;
			sequence->mutationParams[i].preRotMatrix[2] = preM.m13;
			sequence->mutationParams[i].preRotMatrix[3] = preM.m21;
			sequence->mutationParams[i].preRotMatrix[4] = preM.m22;
			sequence->mutationParams[i].preRotMatrix[5] = preM.m23;
			sequence->mutationParams[i].preRotMatrix[6] = preM.m31;
			sequence->mutationParams[i].preRotMatrix[7] = preM.m32;
			sequence->mutationParams[i].preRotMatrix[8] = preM.m33;
			sequence->mutationParams[i].postRotMatrix[0] = postM.m11;
			sequence->mutationParams[i].postRotMatrix[1] = postM.m12;
			sequence->mutationParams[i].postRotMatrix[2] = postM.m13;
			sequence->mutationParams[i].postRotMatrix[3] = postM.m21;
			sequence->mutationParams[i].postRotMatrix[4] = postM.m22;
			sequence->mutationParams[i].postRotMatrix[5] = postM.m23;
			sequence->mutationParams[i].postRotMatrix[6] = postM.m31;
			sequence->mutationParams[i].postRotMatrix[7] = postM.m32;
			sequence->mutationParams[i].postRotMatrix[8] = postM.m33;
		}
		else
		{
			memset(sequence->mutationParams[i].preRotMatrix, 0, sizeof(cl_float) * 9);
			memset(sequence->mutationParams[i].postRotMatrix, 0, sizeof(cl_float) * 9);
		}

		sequence->DEFunctionType[i] = static_cast<enumDEFunctionTypeCl>(DEFunctionType[i]);
		sequence->DEType[i] = static_cast<enumDETypeCl>(DEType[i]);
		sequence->counts[i] = counts[i];
		sequence->formulaStartIteration[i] = formulaStartIteration[i];
		sequence->formulaStopIteration[i] = formulaStopIteration[i];
		sequence->addCConstant[i] = addCConstant[i];
		sequence->checkForBailout[i] = checkForBailout[i];
		sequence->bailout[i] = bailout[i];
		sequence->useAdditionalBailoutCond[i] = useAdditionalBailoutCond[i];
		sequence->juliaEnabled[i] = juliaEnabled[i];
		sequence->juliaConstant[i] = toClFloat4(CVector4(juliaConstant[i], 0.0));
		sequence->constantMultiplier[i] = toClFloat4(CVector4(constantMultiplier[i], 1.0));
		sequence->initialWAxis[i] = initialWAxis[i];
		sequence->formulaMaxiter[i] = formulaMaxiter[i];
		sequence->DEAnalyticFunction[i] = static_cast<enumDEAnalyticFunctionCl>(DEAnalyticFunction[i]);
		sequence->coloringFunction[i] = static_cast<enumColoringFunctionCl>(coloringFunction[i]);
	}
}
#endif

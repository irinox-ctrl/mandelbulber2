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
			enumWeightMode(generalPar->Get<int>("formula_weight_mode", i + 1));
		weightParams[i].staticWeight = generalPar->Get<double>("formula_weight_static", i + 1);
		weightParams[i].iterStart = generalPar->Get<int>("formula_weight_iter_start", i + 1);
		weightParams[i].iterEnd = generalPar->Get<int>("formula_weight_iter_end", i + 1);
		weightParams[i].startWeight = generalPar->Get<double>("formula_weight_start", i + 1);
		weightParams[i].endWeight = generalPar->Get<double>("formula_weight_end", i + 1);
		weightParams[i].blendMode =
			enumWeightBlendMode(generalPar->Get<int>("formula_weight_blend_mode", i + 1));
		weightParams[i].deBase = generalPar->Get<double>("formula_weight_de_base", i + 1);
		weightParams[i].deSensitivity =
			generalPar->Get<double>("formula_weight_de_sensitivity", i + 1);
		weightParams[i].deThreshold = generalPar->Get<double>("formula_weight_de_threshold", i + 1);
		weightParams[i].deModType =
			enumWeightModType(generalPar->Get<int>("formula_weight_de_mod_type", i + 1));
		weightParams[i].zlengthBase = generalPar->Get<double>("formula_weight_zlength_base", i + 1);
		weightParams[i].zlengthSens = generalPar->Get<double>("formula_weight_zlength_sens", i + 1);
		weightParams[i].zlengthThreshold =
			generalPar->Get<double>("formula_weight_zlength_threshold", i + 1);
		weightParams[i].zlengthModType =
			enumWeightModType(generalPar->Get<int>("formula_weight_zlength_mod_type", i + 1));
		weightParams[i].conditionType =
			enumWeightConditionType(generalPar->Get<int>("formula_weight_condition_type", i + 1));
		weightParams[i].conditionThreshold =
			generalPar->Get<double>("formula_weight_condition_threshold", i + 1);
		weightParams[i].trueWeight = generalPar->Get<double>("formula_weight_true", i + 1);
		weightParams[i].falseWeight = generalPar->Get<double>("formula_weight_false", i + 1);
		weightParams[i].conditionBlend =
			enumWeightBlendMode(generalPar->Get<int>("formula_weight_condition_blend", i + 1));
		weightParams[i].separateComponents =
			generalPar->Get<bool>("formula_weight_separate_components", i + 1);
		weightParams[i].zVectorWeight = generalPar->Get<double>("formula_weight_z_vector", i + 1);
		weightParams[i].deComponentWeight =
			generalPar->Get<double>("formula_weight_de_component", i + 1);
		weightParams[i].colorComponentWeight =
			generalPar->Get<double>("formula_weight_color_component", i + 1);

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
	int formulaIndex, int iteration, double currentDE, double zLength) const
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
						double s = t * t * (3.0 - 2.0 * t); // smoothstep
						weight = wp.startWeight + s * (wp.endWeight - wp.startWeight);
						break;
					}
					case weightBlendStep: weight = (t < 0.5) ? wp.startWeight : wp.endWeight; break;
				}
			}
			break;
		}
		case weightModeDE:
		{
			double delta = currentDE - wp.deThreshold;
			double factor = delta * wp.deSensitivity;
			switch (wp.deModType)
			{
				case weightModLinear:
					weight = wp.deBase + factor;
					break;
				case weightModSmooth:
					weight = wp.deBase + factor * factor * (factor > 0 ? 1.0 : -1.0);
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
			}
			bool conditionMet = (testValue < wp.conditionThreshold);
			switch (wp.conditionBlend)
			{
				case weightBlendStep:
					weight = conditionMet ? wp.trueWeight : wp.falseWeight;
					break;
				case weightBlendLinear:
				{
					double blend = qBound(0.0, testValue / wp.conditionThreshold, 1.0);
					weight = wp.trueWeight * (1.0 - blend) + wp.falseWeight * blend;
					break;
				}
				case weightBlendSmooth:
				{
					double blend = qBound(0.0, testValue / wp.conditionThreshold, 1.0);
					double s = blend * blend * (3.0 - 2.0 * blend);
					weight = wp.trueWeight * (1.0 - s) + wp.falseWeight * s;
					break;
				}
			}
			break;
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
		sequence->weightParams[i].separateComponents = weightParams[i].separateComponents ? 1 : 0;
		sequence->weightParams[i].zVectorWeight = weightParams[i].zVectorWeight;
		sequence->weightParams[i].deComponentWeight = weightParams[i].deComponentWeight;
		sequence->weightParams[i].colorComponentWeight = weightParams[i].colorComponentWeight;

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

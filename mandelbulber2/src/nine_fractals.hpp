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

#ifndef MANDELBULBER2_SRC_NINE_FRACTALS_HPP_
#define MANDELBULBER2_SRC_NINE_FRACTALS_HPP_

#include <memory>
#include <vector>

#include "algebra.hpp"
#include "fractal_enums.h"

#include "formula/definition/all_fractal_list.hpp"

// custom includes
#ifdef USE_OPENCL
#include "opencl/fractal_sequence_cl.h"
#endif

// forward declarations
class cParameterContainer;
class cFractalContainer;
struct sFractal;
class cAbstractFractal;

// Advanced weight system enums
enum enumWeightMode
{
	weightModeStatic = 0,
	weightModeIteration = 1,
	weightModeDE = 2,
	weightModeZLength = 3,
	weightModeConditional = 4,
	weightModeOrbitTrap = 5,
	weightModeCurve = 6,
	weightModeTransformPassthrough = 7,
	weightModeDERatio = 8,
	weightModeAdaptive = 9
};

enum enumWeightBlendMode
{
	weightBlendLinear = 0,
	weightBlendSmooth = 1,
	weightBlendStep = 2,
	weightBlendMultiply = 3,
	weightBlendPower = 4,
	weightBlendMin = 5,
	weightBlendMax = 6
};

enum enumWeightModType
{
	weightModLinear = 0,
	weightModSmooth = 1,
	weightModExponential = 2,
	weightModInverse = 3,
	weightModSigmoid = 4
};

enum enumWeightConditionType
{
	weightCondDE = 0,
	weightCondZLength = 1,
	weightCondDist = 2,
	weightCondIteration = 3
};

// Per-formula advanced weight parameters
struct sFormulaWeightParams
{
	enumWeightMode mode;
	double staticWeight;
	// Iteration-based
	int iterStart;
	int iterEnd;
	double startWeight;
	double endWeight;
	enumWeightBlendMode blendMode;
	// DE-based
	double deBase;
	double deSensitivity;
	double deThreshold;
	enumWeightModType deModType;
	// Z-Length-based
	double zlengthBase;
	double zlengthSens;
	double zlengthThreshold;
	enumWeightModType zlengthModType;
	// Conditional
	enumWeightConditionType conditionType;
	double conditionThreshold;
	double trueWeight;
	double falseWeight;
	enumWeightBlendMode conditionBlend;
	// OrbitTrap-based (mode 5)
	double orbitTrapBase;
	double orbitTrapSensitivity;
	double orbitTrapThreshold;
	enumWeightModType orbitTrapModType;
	// Curve-based (mode 6) — custom curve with power exponent
	double curveBase;
	double curveSensitivity;
	double curvePower;
	enumWeightModType curveModType;
	// DE Ratio (mode 8)
	double deRatioScale;
	double deRatioOffset;
	enumWeightModType deRatioModType;
	// Adaptive (mode 9)
	double adaptiveStrength;
	// Fine-tuning post-processing
	double weightFloor;       // minimum output weight (default 0.0)
	double weightCeiling;     // maximum output weight (default 1.0)
	double weightGamma;       // power curve on output weight (default 1.0 = linear)
	bool weightInvert;        // flip weight: 1 - weight
	int fadeInIterations;     // smooth ramp-in over N iterations from formula start
	int fadeOutIterations;    // smooth ramp-out over N iterations before formula stop
	double deSmoothRadius;    // smoothing zone around DE threshold (default 0.0 = sharp)
	double componentBlendCurve; // exponent for component interpolation (default 1.0 = linear)
	// Separate components
	bool separateComponents;
	double zVectorWeight;
	double deComponentWeight;
	double distComponentWeight;
	double colorComponentWeight;
};

// Formula mutation enums
enum enumMutationSwizzle
{
	mutSwizzleXYZ = 0,
	mutSwizzleXZY = 1,
	mutSwizzleYXZ = 2,
	mutSwizzleYZX = 3,
	mutSwizzleZXY = 4,
	mutSwizzleZYX = 5
};

enum enumMutationFoldType
{
	mutFoldNone = 0,
	mutFoldBox = 1,
	mutFoldSphere = 2,
	mutFoldMenger = 3,
	mutFoldSierpinski = 4,
	mutFoldAbs = 5,
	mutFoldKaleidoscope = 6,
	mutFoldOctahedral = 7,
	// v7.1 — Familie 7 advanced folds
	mutFoldSmooth = 8,        // tanh-based smooth fold
	mutFoldPolynomial = 9,    // Chebyshev z³-3z
	mutFoldCircular = 10,     // radial projection to circle
	mutFoldSpiral = 11,       // z * exp(i*|z|)
	mutFoldSinusoidal = 12,   // z + A*sin(B*z)
	mutFoldExponential = 13,  // z * exp(-z²) gaussian
	mutFoldLogarithmic = 14,  // z * log(1+|z|)
	mutFoldPower = 15,        // sign(z) * |z|^p
	// v7.1 — Familie 8 abs/modulo/discontinuous folds
	mutFoldSmoothAbs = 16,    // z * tanh(k*z) — smooth abs replacement
	mutFoldModuloWrap = 17,   // mod(z, period) - period/2 — tiling
	mutFoldNestedAbs = 18,    // abs(abs(z) - c) — double buffered abs
	mutFoldSawtooth = 19      // 2*fract(z/2) - 1 — sawtooth wave fold
};

enum enumMutationWarpType
{
	mutWarpNone = 0,
	mutWarpSine = 1,
	mutWarpTwist = 2,
	mutWarpSpiral = 3,
	mutWarpRadial = 4,
	mutWarpCylindrical = 5,
	mutWarpSphericalInversion = 6,
	mutWarpMobius = 7
};

enum enumMutationFoldPosition
{
	mutFoldPosPre = 0,
	mutFoldPosPost = 1,
	mutFoldPosBoth = 2
};

enum enumMutationMathType
{
	mutMathNone = 0,
	mutMathSinPower = 1,
	mutMathCoshField = 2,
	mutMathExpMap = 3,
	mutMathLogSpiral = 4,
	mutMathPowerN = 5,
	mutMathComplexMul = 6,
	mutMathQuaternionMul = 7,
	mutMathBilinear = 8,
	mutMathInvCylindr = 9,
	mutMathSpiralPower = 10,
	mutMathHyperbolicRot = 11,
	// v6.3 — Advanced Kleinian/Conformal math
	mutMathSphereInversion3D = 12,  // T(x) = c + r²(x-c)/|x-c|² — full 3D sphere inversion
	mutMathLoxodromic = 13,         // s * R_axis(θ) * v — spiral scale + rotation
	mutMathParabolic = 14,          // horocycle: (x+a, y+b, z)/(1+c*z)
	mutMathSchottkyDual = 15,       // dual sphere inversions (2 spheres)
	mutMathFibonacciWord = 16,      // aperiodic automaton: Fibonacci word selects T1/T2
	mutMathMaskitBend = 17,         // bending along geodesic: μ + 1/z generalized
	mutMathEllipsoidInversion = 18, // T(x) = c + A*(x-c)/|A*(x-c)|²
	mutMathTorusInversion = 19,     // inversion in torus coordinates
	mutMathQuatJuliaKleinian = 20,  // q² + c quaternion Julia within Kleinian
	mutMathPoincareBall = 21,       // H³ Poincaré ball model mapping
	mutMathLorentzBoost = 22,       // SO(3,1) Lorentz transform + 4D→3D projection
	mutMathConformeFlow = 23,       // g' = e^(2u(x)) * g conformal deformation
	// v7.1 — Familie 2 power variation math
	mutMathFractionalPower = 24,    // r^p with fractional p (e.g. 2.718)
	mutMathAnisotropePower = 25,    // different power per axis
	mutMathHyperbolicTrigPower = 26,// sinh/cosh triplex instead of sin/cos
	mutMathLogarithmicRadius = 27,  // log(1 + r^p) compression
	mutMathPolarSwap = 28,          // swap θ↔φ
	mutMathRadialModulation = 29    // r * (1 + A*sin(B*θ))
};

// Per-formula mutation parameters — universal pre/post processing on ANY formula
struct sFormulaMutationParams
{
	bool enabled;
	// Pre-transform
	double preRotX, preRotY, preRotZ; // degrees
	double preScale;                  // uniform scale (default 1.0)
	double preOffsetX, preOffsetY, preOffsetZ;
	bool preAbsX, preAbsY, preAbsZ;
	// Post-transform
	double postRotX, postRotY, postRotZ; // degrees
	double postScale;                    // uniform scale (default 1.0)
	double postOffsetX, postOffsetY, postOffsetZ;
	// Component swizzle
	enumMutationSwizzle swizzle;
	// Fold injection
	enumMutationFoldType foldType;
	enumMutationFoldPosition foldPosition;
	double foldLimit;
	double foldValue;
	int kaleidoscopeSides;
	// Warp distortion
	enumMutationWarpType warpType;
	double warpFrequency;
	double warpAmplitude;
	// Math injection — new mathematical operations
	enumMutationMathType mathType;
	double mathP1;     // primary parameter
	double mathP2;     // secondary parameter
	double mathP3;     // tertiary parameter
	double mathP4;     // quaternary parameter
	double mathP5;     // extended: 2nd sphere cx / ellipsoid axis x / torus R
	double mathP6;     // extended: 2nd sphere cy / ellipsoid axis y / torus r
	double mathP7;     // extended: 2nd sphere cz / ellipsoid axis z / boost velocity
	double mathP8;     // extended: 2nd sphere r  / conformal potential scale
	double mathMix;    // 0-1: blend between original z and math-transformed z
	// Output control
	double zMix;
	double deScale;
	// Iteration range
	int iterationStart;
	int iterationStop;

	// Pre-computed rotation matrices (filled in constructor)
	CRotationMatrix preRotMatrix;
	CRotationMatrix postRotMatrix;
};

class cNineFractals
{
public:
	cNineFractals(std::shared_ptr<const cFractalContainer> fractalPar,
		std::shared_ptr<const cParameterContainer> generalPar);
	sFractal *GetFractal(int index) const { return fractals[index].get(); }
	int GetSequence(const int i) const;
	bool IsHybrid() const { return isHybrid; }
	fractal::enumDEType GetDEType(int formulaIndex) const;
	fractal::enumDEFunctionType GetDEFunctionType(int formulaIndex) const;
	inline double GetWeight(int formulaIndex) const { return formulaWeight[formulaIndex]; }
	inline const sFormulaWeightParams &GetWeightParams(int formulaIndex) const
	{
		return weightParams[formulaIndex];
	}
	inline const sFormulaMutationParams &GetMutationParams(int formulaIndex) const
	{
		return mutationParams[formulaIndex];
	}
	// Calculate effective weight based on mode and current iteration state
	double CalculateWeight(int formulaIndex, int iteration, double currentDE, double zLength,
		double currentDist = 0.0, fractal::enumDEFunctionType deFunc = fractal::undefinedDEFunction) const;
	inline int GetMaxFractalIndex() const { return maxFractalIndex; }
	inline bool IsAddCConstant(int formulaIndex) const { return addCConstant[formulaIndex]; }
	inline bool IsCheckForBailout(int formulaIndex) const { return checkForBailout[formulaIndex]; }
	inline bool UseOptimizedDE() const { return useOptimizedDE; }
	QString GetDETypeString() const;
	inline double GetBailout(int formulaIndex) const { return bailout[formulaIndex]; }
	inline bool IsJuliaEnabled(int formulaIndex) const { return juliaEnabled[formulaIndex]; }
	inline CVector3 GetJuliaConstant(int formulaIndex) const { return juliaConstant[formulaIndex]; }
	inline CVector3 GetConstantMultiplier(int formulaIndex) const
	{
		return constantMultiplier[formulaIndex];
	}
	inline double GetInitialWAxis(int formulaIndex) const { return initialWAxis[formulaIndex]; }
	inline bool UseAdditionalBailoutCond(int formulaIndex) const
	{
		return useAdditionalBailoutCond[formulaIndex];
	};
	inline cAbstractFractal *GetFractalFormulaFunction(int formulaIndex) const
	{
		return fractalFormulaFunctions[formulaIndex];
	}
	inline fractal::enumDEAnalyticFunction GetDEAnalyticFunction(int formulaIndex) const
	{
		return DEAnalyticFunction[formulaIndex];
	}
	inline fractal::enumColoringFunction GetColoringFunction(int formulaIndex) const
	{
		return coloringFunction[formulaIndex];
	}
	inline int GetFormulaMaxiter(int formulaIndex) const { return formulaMaxiter[formulaIndex]; }

	static int GetIndexOnFractalList(fractal::enumFractalFormula formula);

#ifdef USE_OPENCL
	void CopyToOpenclData(sClFractalSequence *sequence) const;
#endif

private:
	std::vector<std::unique_ptr<sFractal>> fractals;
	bool forceDeltaDE;
	bool forceAnalyticDE;
	bool isHybrid;
	bool isBoolean;
	fractal::enumDEFunctionType optimizedDEType;
	bool useOptimizedDE;
	int maxFractalIndex;
	int maxN;
	std::vector<int> hybridSequence;
	int hybridSequenceLength;

	double formulaWeight[NUMBER_OF_FRACTALS];
	sFormulaWeightParams weightParams[NUMBER_OF_FRACTALS];
	sFormulaMutationParams mutationParams[NUMBER_OF_FRACTALS];
	fractal::enumDEFunctionType DEFunctionType[NUMBER_OF_FRACTALS];
	fractal::enumDEType DEType[NUMBER_OF_FRACTALS];
	fractal::enumDEAnalyticFunction DEAnalyticFunction[NUMBER_OF_FRACTALS];
	fractal::enumColoringFunction coloringFunction[NUMBER_OF_FRACTALS];
	int counts[NUMBER_OF_FRACTALS];
	int formulaStartIteration[NUMBER_OF_FRACTALS];
	int formulaStopIteration[NUMBER_OF_FRACTALS];
	bool addCConstant[NUMBER_OF_FRACTALS];
	bool checkForBailout[NUMBER_OF_FRACTALS];
	double bailout[NUMBER_OF_FRACTALS];
	bool juliaEnabled[NUMBER_OF_FRACTALS];
	CVector3 juliaConstant[NUMBER_OF_FRACTALS];
	CVector3 constantMultiplier[NUMBER_OF_FRACTALS];
	double initialWAxis[NUMBER_OF_FRACTALS];
	bool useAdditionalBailoutCond[NUMBER_OF_FRACTALS];
	int formulaMaxiter[NUMBER_OF_FRACTALS];
	cAbstractFractal *fractalFormulaFunctions[NUMBER_OF_FRACTALS];

	void CreateSequence(std::shared_ptr<const cParameterContainer> generalPar);
};

#endif /* MANDELBULBER2_SRC_NINE_FRACTALS_HPP_ */

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
	mutFoldSawtooth = 19,     // 2*fract(z/2) - 1 — sawtooth wave fold
	// v7.4 — Familie 7 extra fold types
	mutFoldBipolar = 20,      // two fold centers: |z-c1| - |z-c2|
	mutFoldRadialBox = 21,    // box fold in polar coordinates
	mutFoldShear = 22,        // fold + shear: z.x += shear*z.y
	mutFold3DCross = 23,      // cyclic XY→YZ→ZX fold
	mutFoldConformal = 24,    // z + 1/z conformal fold
	mutFoldRotation = 25,     // rotate 90° after fold
	mutFoldScalePulse = 26,   // scale = 1+A*sin(iter) after fold
	mutFoldTriangleWave = 27  // 2*|fract(z/2)-0.5| — triangle wave
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
	mutWarpMobius = 7,
	// v7.2 — Familie 4 IFS/Menger warps
	mutWarpIFSContraction = 8,    // variable contraction s = s0*(1 + A*sin(iter))
	mutWarpIFSRotation = 9,       // golden angle rotation per iteration
	mutWarpPolarIFS = 10,         // contraction in polar (r,θ,z) coords
	mutWarpShearIFS = 11          // z.x += shear * z.y
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
	mutMathRadialModulation = 29,   // r * (1 + A*sin(B*θ))
	// v7.2 — Familie 5 quaternion/hypercomplex math
	mutMathDualQuaternion = 30,     // q1 * z * q2 (two quaternion multiplication)
	mutMathOctonionPower = 31,      // o^p in octonion (8D→3D projection)
	mutMathQuaternionMobius = 32,   // (az+b)/(cz+d) quaternion Möbius
	mutMathSplitQuaternion = 33,    // split quaternion (i²=+1, hyperbolic)
	// v7.3 — Familie 3 extra Kleinian math
	mutMathFordCircles = 34,        // z += 1/(n²·z) circle packing
	mutMathApollonianNet = 35,      // inversie in 4 bollen, nearest
	mutMathConformalWedge = 36,     // z^α sector mapping
	mutMathCircleInvChain = 37,     // sequential circle inversions
	// v7.4 — Familie 6 special trig/functions
	mutMathHyperbolicSine = 38,     // sinh(z) + c
	mutMathBesselApprox = 39,       // J₀(r) approximation
	mutMathLambertW = 40,           // z*exp(z) + c
	mutMathErrorFunction = 41       // erf(z) + c
};

// v7.3 — Familie 10 DE/rendering tweaks
enum enumMutationDETweak
{
	mutDENone = 0,
	mutDELogarithmic = 1,       // dist = log(1 + DE) — soft misty distance
	mutDEExponential = 2,       // dist = exp(DE) - 1 — hard aggressive distance
	mutDENoise = 3,             // dist = DE + noise — eroded surface
	mutDEModulation = 4,        // dist = DE * (1 + A*sin(B*dist)) — ripple
	mutDESlack = 5,             // dist = DE * 0.9 — safe understep
	mutDEAggressive = 6         // dist = DE * 1.1 — fast overstep
};

enum enumMutationOrbitTrap
{
	mutTrapNone = 0,
	mutTrapSphere = 1,          // trap = abs(|z-c| - r)
	mutTrapCross = 2,           // trap = min(|z.x|, |z.y|, |z.z|)
	mutTrapLine = 3,            // trap = dist_to_line(z, axis)
	mutTrapTorus = 4,           // trap = torus distance
	mutTrapAngle = 5            // trap = abs(atan2(z.y, z.x))
};

// v7.5 — Amazing Surf Julia injection system
enum enumMutationJuliaInjection
{
	mutJuliaInjectNone = 0,
	mutJuliaInjectPreFold = 1,       // z += c before box fold
	mutJuliaInjectMidFold = 2,       // z += c between box and spherical fold
	mutJuliaInjectPostScale = 3,     // z += c after scale, before rotation
	mutJuliaInjectDual = 4,          // c1 pre-fold + c2 post-scale
	mutJuliaInjectPreScale = 5       // c *= |z|/bailout damping
};

enum enumMutationJuliaStart
{
	mutJuliaStartRay = 0,            // default: z₀ = ray position
	mutJuliaStartC = 1,              // z₀ = c (classic Julia)
	mutJuliaStartRayPlusC = 2,       // z₀ = ray + c
	mutJuliaStartZero = 3,           // z₀ = 0, c = ray
	mutJuliaStart4D = 4              // z₀ = (c.x, c.y, c.z, c.w) full 4D
};

enum enumMutationJuliaCTransform
{
	mutJuliaCNone = 0,
	mutJuliaCSpherical = 1,          // c = c/|c| * radius
	mutJuliaCMobius = 2,             // c = (a*c+b)/(c+d) Möbius
	mutJuliaCRotate = 3,             // c = rotMatrix * c
	mutJuliaCPower = 4,              // c = c^p (triplex power)
	mutJuliaCQuaternion = 5          // quaternion c injection
};

enum enumMutationJuliaDynamic
{
	mutJuliaDynNone = 0,
	mutJuliaDynOrbitMod = 1,         // c *= (1 + 0.1*|z|)
	mutJuliaDynPulse = 2,            // c *= sin(iter * freq)
	mutJuliaDynFoldTrigger = 3,      // c *= 2 when |z| > threshold
	mutJuliaDynAbsorb = 4,           // c = lerp(c, z, rate)
	mutJuliaDynOrbitMemory = 5       // c += 0.1*(z - z_prev)
};

enum enumMutationJuliaMulti
{
	mutJuliaMultiNone = 0,
	mutJuliaMultiBipolar = 1,        // c_left vs c_right per halfspace
	mutJuliaMulti4DSwap = 2,         // c component swap every 4 iters
	mutJuliaMultiFourier = 3,        // c1 + c2*sin(iter) + c3*cos(iter/2)
	mutJuliaMultiNoise = 4,          // c += noise(z*freq)*amp
	mutJuliaMultiRecursive = 5       // c += 0.01*z (evolving seed)
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
	// DE tweak (Familie 10)
	enumMutationDETweak deTweak;
	double deTweakP1;   // noise amplitude / modulation amplitude
	double deTweakP2;   // modulation frequency
	// Orbit trap (Familie 10)
	enumMutationOrbitTrap orbitTrap;
	double trapCenterX, trapCenterY, trapCenterZ;
	double trapRadius;
	// Curvature coloring
	bool curvatureColoring;
	// Iteration range (global master)
	int iterationStart;
	int iterationStop;
	// Per-section iteration ranges
	int preIterStart, preIterStop;
	int foldIterStart, foldIterStop;
	int warpIterStart, warpIterStop;
	int mathIterStart, mathIterStop;
	int postIterStart, postIterStop;
	int juliaIterStart, juliaIterStop;
	int deIterStart, deIterStop;

	// v7.5 — Julia injection system
	enumMutationJuliaInjection juliaInjection;
	enumMutationJuliaStart juliaStart;
	enumMutationJuliaCTransform juliaCTransform;
	enumMutationJuliaDynamic juliaDynamic;
	enumMutationJuliaMulti juliaMulti;
	double juliaCMul;          // c multiplier (default 1.0)
	double juliaCRotX, juliaCRotY, juliaCRotZ; // c rotation angles
	double juliaCPower;        // power for c^p transform
	double juliaCMobiusA, juliaCMobiusB, juliaCMobiusD; // Möbius params
	double juliaCRadius;       // sphere radius for spherical projection
	double juliaPulseFreq;     // frequency for pulse mode
	double juliaPulseAmp;      // amplitude for pulse mode
	double juliaAbsorb;        // absorption rate (0-1)
	double juliaNoiseFreq;     // noise frequency
	double juliaNoiseAmp;      // noise amplitude
	double juliaFourierC2x, juliaFourierC2y, juliaFourierC2z; // 2nd harmonic
	double juliaFourierC3x, juliaFourierC3y, juliaFourierC3z; // 3rd harmonic
	double juliaBipolarCRx, juliaBipolarCRy, juliaBipolarCRz; // right-half c

	// v7.6 — Inversion system
	int inversionType;
	double invCenterX, invCenterY, invCenterZ;
	double invRadius;
	double invParamA, invParamB, invParamC;
	double invScale;
	double invAngle, invFrequency, invAmplitude;
	double invMinR, invMaxR;
	double invPreRotX, invPreRotY, invPreRotZ;
	double invCenter2X, invCenter2Y, invCenter2Z;
	double invRadius2;
	double invWeight;
	int invNSteps;
	double invThreshold, invColorFactor;
	int invIterStart, invIterStop;
	// v7.6 — Clip system
	int clipType;
	double clipCenterX, clipCenterY, clipCenterZ;
	double clipSizeX, clipSizeY, clipSizeZ;
	double clipRadius, clipMajorRadius;
	double clipAngle, clipAmplitude, clipFrequency;
	double clipSmoothK;
	int clipBooleanOp;
	double clipPreRotX, clipPreRotY, clipPreRotZ;
	int clipNPoints;
	double clipParamA, clipParamB, clipParamC;
	double clipThreshold;
	int clipIterStart, clipIterStop;

	// v7.7 — Jos Leys DE system (100 types)
	int josLeysDeType;
	double josFactor;
	double josParamA, josParamB, josParamC, josParamD;
	double josFreq, josAmp;
	double josScale, josPhase;
	int josIterStart, josIterStop;

	// v7.7 — Pseudokleinian DE system (100 types)
	int pseudoKleinianDeType;
	double pkFactor;
	double pkParamA, pkParamB, pkParamC, pkParamD;
	double pkFreq, pkAmp;
	double pkScale, pkPhase;
	int pkIterStart, pkIterStop;

	// v7.8 — Mandelbox Math system (200 types)
	int mbMathType;
	double mbFactor;
	double mbParamA, mbParamB, mbParamC, mbParamD;
	double mbParamE, mbParamF, mbParamG, mbParamH;
	int mbIterStart, mbIterStop;

	// v7.9 — Warp Distortion system (100 types)
	int warpDistType;
	double wdFactor;
	double wdParamA, wdParamB, wdParamC, wdParamD;
	double wdFreq, wdAmp;
	double wdScale, wdPhase;
	int wdIterStart, wdIterStop;

	// v7.9 — Symmetry/Kaleidoscope system (100 types)
	int symKalType;
	double skFactor;
	double skParamA, skParamB, skParamC, skParamD;
	double skFreq, skAmp;
	double skAngle, skOffset;
	int skIterStart, skIterStop;

	// v7.9 — Abox DE system (300 types)
	int aboxType;
	double abFactor;
	double abParamA, abParamB, abParamC, abParamD;
	double abParamE, abParamF, abParamG, abParamH;
	int abIterStart, abIterStop;

	// v7.10 — Noise & Procedural DE system (100 types)
	int noiseType;
	double noiseFactor;
	double noiseParamA, noiseParamB, noiseParamC, noiseParamD;
	double noiseFreq, noiseAmp;
	int noiseIterStart, noiseIterStop;

	// v7.10 — Orbit Trap DE system (100 types)
	int orbitTrapType;
	double orbitFactor;
	double orbitParamA, orbitParamB, orbitParamC, orbitParamD;
	int orbitIterStart, orbitIterStop;

	// v7.12 — MandelTorus DE system (100 types)
	int torusType;
	double torusFactor;
	double torusParamA, torusParamB, torusParamC, torusParamD;
	int torusIterStart, torusIterStop;

	// v7.13 — Amazing Surf 1-4 DE system (100 types)
	int asType;
	double asFactor;
	double asParamA, asParamB, asParamC, asParamD;
	int asIterStart, asIterStop;

	// v7.13 — SphereTree/Menger DE system (100 types)
	int smType;
	double smFactor;
	double smParamA, smParamB, smParamC, smParamD;
	int smIterStart, smIterStop;

	int blkType;
	double blkFactor;
	double blkParamA, blkParamB, blkParamC, blkParamD;
	int blkIterStart, blkIterStop;

	int tilType;
	double tilFactor;
	double tilParamA, tilParamB, tilParamC, tilParamD;
	int tilIterStart, tilIterStop;

	// v7.14 — Per-section mutation weights (0=off .. 1=full) + global master
	double masterWeight;
	double inversionWeight, clipWeight, josWeight, pkWeight, mbWeight, wdWeight,
		skWeight, abWeight, noiseWeight, orbitWeight, torusWeight, asWeight,
		smWeight, blkWeight, tilWeight;
	// v7.15 — Per-parameter mutation weights (option 3): blend each param from default(1.0) toward set value
	double wInvParamA, wInvParamB, wInvParamC, wClipParamA, wClipParamB, wClipParamC;
	double wJosFactor, wJosParamA, wJosParamB, wJosParamC, wJosParamD, wPkFactor;
	double wPkParamA, wPkParamB, wPkParamC, wPkParamD, wMbFactor, wMbParamA;
	double wMbParamB, wMbParamC, wMbParamD, wWdFactor, wWdParamA, wWdParamB;
	double wWdParamC, wWdParamD, wSkFactor, wSkParamA, wSkParamB, wSkParamC;
	double wSkParamD, wAbFactor, wAbParamA, wAbParamB, wAbParamC, wAbParamD;
	double wNoiseFactor, wNoiseParamA, wNoiseParamB, wNoiseParamC, wNoiseParamD, wOrbitFactor;
	double wOrbitParamA, wOrbitParamB, wOrbitParamC, wOrbitParamD, wTorusFactor, wTorusParamA;
	double wTorusParamB, wTorusParamC, wTorusParamD, wAsFactor, wAsParamA, wAsParamB;
	double wAsParamC, wAsParamD, wSmFactor, wSmParamA, wSmParamB, wSmParamC;
	double wSmParamD, wBlkFactor, wBlkParamA, wBlkParamB, wBlkParamC, wBlkParamD;
	double wTilFactor, wTilParamA, wTilParamB, wTilParamC, wTilParamD;
	double wMbParamE, wMbParamF, wMbParamG, wMbParamH, wAbParamE, wAbParamF, wAbParamG, wAbParamH;
	// Pre-computed rotation matrices (filled in constructor)
	CRotationMatrix preRotMatrix;
	CRotationMatrix postRotMatrix;
	CRotationMatrix juliaCRotMatrix;
	CRotationMatrix invPreRotMatrix;
	CRotationMatrix clipPreRotMatrix;
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

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
	mutJuliaInjectPreScale = 5,      // c *= |z|/bailout damping
	mutJuliaInjectPostFold = 6,      // z += c after fractal formula
	mutJuliaInjectAlternating = 7,   // pre on even iters, post on odd
	mutJuliaInjectRadial = 8,        // inject proportional to |z|/bailout
	mutJuliaInjectConditional = 9,   // only when |z| > threshold
	mutJuliaInjectGradient = 10,     // linear interpolation over iter range
	mutJuliaInjectLayered = 11       // c₁ first half, c₂ second half
};

enum enumMutationJuliaStart
{
	mutJuliaStartRay = 0,            // default: z₀ = ray position
	mutJuliaStartC = 1,              // z₀ = c (classic Julia)
	mutJuliaStartRayPlusC = 2,       // z₀ = ray + c
	mutJuliaStartZero = 3,           // z₀ = 0, c = ray
	mutJuliaStart4D = 4,             // z₀ = (c.x, c.y, c.z, c.w) full 4D
	mutJuliaStartInversion = 5,      // z₀ = c/|c|² (inversion)
	mutJuliaStartSpherical = 6,      // z₀ on sphere of juliaRadius
	mutJuliaStartBipolar = 7,        // different start for x>0 vs x<0
	mutJuliaStartLattice = 8,        // z₀ snapped to grid of juliaRadius
	mutJuliaStartPerturb = 9         // z₀ = ray + c * small epsilon
};

enum enumMutationJuliaCTransform
{
	mutJuliaCNone = 0,
	mutJuliaCSpherical = 1,          // c = c/|c| * radius
	mutJuliaCMobius = 2,             // c = (a*c+b)/(c+d) Möbius
	mutJuliaCRotate = 3,             // c = rotMatrix * c
	mutJuliaCPower = 4,              // c = c^p (triplex power)
	mutJuliaCQuaternion = 5,         // quaternion c injection
	mutJuliaCLogarithmic = 6,        // c = log(|c|) * normalize(c)
	mutJuliaCExponential = 7,        // c = exp(c) (component-wise)
	mutJuliaCInversion = 8,          // c = c/|c|² (sphere inversion)
	mutJuliaCBoxFold = 9,            // box fold applied to c
	mutJuliaCSpiral = 10,            // c *= e^(i*theta) rotation in xy
	mutJuliaCMandelbrot = 11         // c = c² + c₀ (Mandelbrot iterate)
};

enum enumMutationJuliaDynamic
{
	mutJuliaDynNone = 0,
	mutJuliaDynOrbitMod = 1,         // c *= (1 + 0.1*|z|)
	mutJuliaDynPulse = 2,            // c *= sin(iter * freq)
	mutJuliaDynFoldTrigger = 3,      // c *= 2 when |z| > threshold
	mutJuliaDynAbsorb = 4,           // c = lerp(c, z, rate)
	mutJuliaDynOrbitMemory = 5,      // c += 0.1*(z - z_prev)
	mutJuliaDynExpDecay = 6,         // c *= exp(-decay * iter)
	mutJuliaDynSaw = 7,              // c *= sawtooth(iter * freq)
	mutJuliaDynSmoothStep = 8,       // c *= smoothstep over iter range
	mutJuliaDynChaos = 9,            // c *= logistic map x=rx(1-x)
	mutJuliaDynSpiral = 10,          // c rotates in xy-plane per iter
	mutJuliaDynBounce = 11           // c *= |sin(iter * freq)|
};

enum enumMutationJuliaMulti
{
	mutJuliaMultiNone = 0,
	mutJuliaMultiBipolar = 1,        // c_left vs c_right per halfspace
	mutJuliaMulti4DSwap = 2,         // c component swap every 4 iters
	mutJuliaMultiFourier = 3,        // c1 + c2*sin(iter) + c3*cos(iter/2)
	mutJuliaMultiNoise = 4,          // c += noise(z*freq)*amp
	mutJuliaMultiRecursive = 5,      // c += 0.01*z (evolving seed)
	mutJuliaMultiOctave = 6,         // multi-frequency noise layers
	mutJuliaMultiPhaseShift = 7,     // c₁ phase 0°, c₂ phase 120°, c₃ phase 240°
	mutJuliaMultiOrbitSplit = 8,     // switch c based on orbit quadrant
	mutJuliaMultiIterModulo = 9,     // cycle through c₁,c₂,c₃ per iter%3
	mutJuliaMultiDistBand = 10,      // c₁ near, c₂ mid, c₃ far based on |z|
	mutJuliaMultiRandom = 11         // pseudo-random c selection per iter
};

// v7.7+ integer-dispatched DE sub-systems (numeric cases 1..N in CPU/OpenCL switches)
enum enumJosLeysDeType : int
{
	josDeNone = 0,
	josDeClassic = 1,
	josDeSmooth = 2,
	josDeRipple = 3,
	josDeSpiral = 4,
	josDeMaxType = 100
};

enum enumPseudoKleinianDeType : int
{
	pkDeNone = 0,
	pkDeStandard = 1,
	pkDeTwisted = 2,
	pkDeFolded = 3,
	pkDeMaxType = 100
};

enum enumMandelboxMathType : int
{
	mbMathNone = 0,
	mbMathClassic = 1,
	mbMathSmooth = 2,
	mbMathVariant = 3,
	mbMathMaxType = 200
};

enum enumWarpDistType : int
{
	wdNone = 0,
	wdStandard = 1,
	wdTwisted = 2,
	wdFolded = 3,
	wdMaxType = 100
};

enum enumSymKalType : int
{
	skNone = 0,
	skStandard = 1,
	skKaleidoscope = 2,
	skMirror = 3,
	skMaxType = 100
};

enum enumAboxDeType : int
{
	aboxDeNone = 0,
	aboxDeClassic = 1,
	aboxDeSmooth = 2,
	aboxDeVariant = 3,
	aboxDeMaxType = 300
};

enum enumMutationNoiseDeType : int
{
	mutNoiseDeNone = 0,
	mutNoiseDeClassic = 1,
	mutNoiseDeProcedural = 2,
	mutNoiseDeFractal = 3,
	mutNoiseDeMaxType = 100
};

enum enumMutationOrbitTrapDeType : int
{
	mutOrbitTrapDeNone = 0,
	mutOrbitTrapDeStandard = 1,
	mutOrbitTrapDeSphere = 2,
	mutOrbitTrapDeBox = 3,
	mutOrbitTrapDeMaxType = 100
};

enum enumMandelTorusDeType : int
{
	torusDeNone = 0,
	torusDeStandard = 1,
	torusDeTwisted = 2,
	torusDeFolded = 3,
	torusDeMaxType = 100
};

enum enumAmazingSurfDeType : int
{
	asDeNone = 0,
	asDeSurf1 = 1,
	asDeSurf2 = 2,
	asDeSurf3 = 3,
	asDeSurf4 = 4,
	asDeMaxType = 100
};

enum enumSphereTreeDeType : int
{
	smDeNone = 0,
	smDeMenger = 1,
	smDeTree = 2,
	smDeMaxType = 100
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
	bool adaptiveStrength = false;
	double adaptiveThreshold = 2.0;
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
	// v7.8 — Extended Julia parameters
	double juliaDecayRate;      // exponential decay rate for DynExpDecay
	double juliaSpiralAngle;   // angle increment per iter for DynSpiral and CSpiral
	double juliaChaosR;        // logistic map parameter (3.5-4.0)
	double juliaThreshold;     // threshold for Conditional injection
	double juliaGradientEnd;   // end multiplier for Gradient injection
	double juliaLayerC2x, juliaLayerC2y, juliaLayerC2z; // second c for Layered
	double juliaBoxFoldLimit;  // fold limit for CBoxFold transform
	double juliaStartEpsilon;  // perturbation size for StartPerturb
	double juliaDistBandMid;   // distance band midpoint
	double juliaDistBandFar;   // distance band far threshold
	// v7.9 — Per-subsystem iteration ranges for Julia
	int juliaCTransformIterStart, juliaCTransformIterStop;
	int juliaDynamicIterStart, juliaDynamicIterStop;
	int juliaMultiIterStart, juliaMultiIterStop;
	// v7.9 — Fine-tune strengths
	double juliaCTransformStrength;  // blend factor for C-transform (0=bypass, 1=full)
	double juliaDynamicStrength;     // scale factor for dynamic modulation
	double juliaMultiStrength;       // blend factor for multi-C switching
	double juliaInjectionStrength;   // scale factor for final injection into z
	double juliaDEFactor;            // DE correction (1=none, <1=sharper rendering)

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
	enumJosLeysDeType josLeysDeType;
	double josFactor;
	double josParamA, josParamB, josParamC, josParamD;
	double josFreq, josAmp;
	double josScale, josPhase;
	int josIterStart, josIterStop;

	// v7.7 — Pseudokleinian DE system (100 types)
	enumPseudoKleinianDeType pseudoKleinianDeType;
	double pkFactor;
	double pkParamA, pkParamB, pkParamC, pkParamD;
	double pkFreq, pkAmp;
	double pkScale, pkPhase;
	int pkIterStart, pkIterStop;

	// v7.8 — Mandelbox Math system (200 types)
	enumMandelboxMathType mbMathType;
	double mbFactor;
	double mbParamA, mbParamB, mbParamC, mbParamD;
	double mbParamE, mbParamF, mbParamG, mbParamH;
	int mbIterStart, mbIterStop;

	// v7.9 — Warp Distortion system (100 types)
	enumWarpDistType warpDistType;
	double wdFactor;
	double wdParamA, wdParamB, wdParamC, wdParamD;
	double wdFreq, wdAmp;
	double wdScale, wdPhase;
	int wdIterStart, wdIterStop;

	// v7.9 — Symmetry/Kaleidoscope system (100 types)
	enumSymKalType symKalType;
	double skFactor;
	double skParamA, skParamB, skParamC, skParamD;
	double skFreq, skAmp;
	double skAngle, skOffset;
	int skIterStart, skIterStop;

	// v7.9 — Abox DE system (300 types)
	enumAboxDeType aboxType;
	double abFactor;
	double abParamA, abParamB, abParamC, abParamD;
	double abParamE, abParamF, abParamG, abParamH;
	int abIterStart, abIterStop;

	// v7.10 — Noise & Procedural DE system (100 types)
	enumMutationNoiseDeType noiseType;
	double noiseFactor;
	double noiseParamA, noiseParamB, noiseParamC, noiseParamD;
	double noiseFreq, noiseAmp;
	int noiseIterStart, noiseIterStop;

	// v7.10 — Orbit Trap DE system (100 types)
	enumMutationOrbitTrapDeType orbitTrapType;
	double orbitFactor;
	double orbitParamA, orbitParamB, orbitParamC, orbitParamD;
	int orbitIterStart, orbitIterStop;

	// v7.12 — MandelTorus DE system (100 types)
	enumMandelTorusDeType torusType;
	double torusFactor;
	double torusParamA, torusParamB, torusParamC, torusParamD;
	int torusIterStart, torusIterStop;

	// v7.13 — Amazing Surf 1-4 DE system (100 types)
	enumAmazingSurfDeType asType;
	double asFactor;
	double asParamA, asParamB, asParamC, asParamD;
	int asIterStart, asIterStop;

	// v7.13 — SphereTree/Menger DE system (100 types)
	enumSphereTreeDeType smType;
	double smFactor;
	double smParamA, smParamB, smParamC, smParamD;
	int smIterStart, smIterStop;

	// v7.14 — T Clamp system
	int clampType;
	double clampFactor;
	double clampParamA, clampParamB, clampParamC, clampParamD;
	int clampIterStart, clampIterStop;

	// v7.14 — T Julia Box system
	int jbType;
	double jbFactor;
	double jbParamA, jbParamB, jbParamC, jbParamD;
	int jbIterStart, jbIterStop;

	// v7.14 — T Mandalay system
	int mdType;
	double mdFactor;
	double mdParamA, mdParamB, mdParamC, mdParamD;
	int mdIterStart, mdIterStop;

	// v7.15 — Blockify system
	int blockifyType;
	double blockifyFactor;
	double blockifyParamA, blockifyParamB, blockifyParamC, blockifyParamD;
	int blockifyIterStart, blockifyIterStop;

	// v7.15 — Tile system
	int tileType;
	double tileFactor;
	double tileParamA, tileParamB, tileParamC, tileParamD;
	int tileIterStart, tileIterStop;

	// Per-subsystem enabled flags
	bool inversionEnabled;
	bool clipEnabled;
	bool josLeysEnabled;
	bool pkEnabled;
	bool mbMathEnabled;
	bool warpDistEnabled;
	bool symmetryEnabled;
	bool aboxEnabled;
	bool noiseEnabled;
	bool orbitTrapEnabled;
	bool torusEnabled;
	bool asEnabled;
	bool smEnabled;
	bool clampEnabled;
	bool jbEnabled;
	bool mdEnabled;
	bool blockifyEnabled;
	bool tileEnabled;

	// Section weights (0.0-1.0, multiplied with factor)
	double inversionWeight;
	double clipWeight;
	double josLeysWeight;
	double pkWeight;
	double mbMathWeight;
	double warpDistWeight;
	double symmetryWeight;
	double aboxWeight;
	double noiseWeight;
	double orbitTrapWeight;
	double torusWeight;
	double clampWeight;
	double jbWeight;
	double mdWeight;
	double asWeight;
	double smWeight;
	double blockifyWeight;
	double tileWeight;
	double masterWeight;

	// Pre-computed rotation matrices (filled in constructor)
	CRotationMatrix preRotMatrix;
	CRotationMatrix postRotMatrix;
	CRotationMatrix juliaCRotMatrix;
	CRotationMatrix invPreRotMatrix;
	CRotationMatrix clipPreRotMatrix;
};

void ValidateMutationParams(sFormulaMutationParams &mut);

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
	inline void SetJuliaConstant(int formulaIndex, CVector3 val) { juliaConstant[formulaIndex] = val; }
	inline void SetJuliaEnabled(int formulaIndex, bool val) { juliaEnabled[formulaIndex] = val; }
	inline CVector3 GetConstantMultiplier(int formulaIndex) const
	{
		return constantMultiplier[formulaIndex];
	}
	inline CVector3 GetJuliaCIterStart(int formulaIndex) const { return juliaCIterStart[formulaIndex]; }
	inline CVector3 GetJuliaCIterStop(int formulaIndex) const { return juliaCIterStop[formulaIndex]; }
	inline CVector3 GetJuliaCWeight(int formulaIndex) const { return juliaCWeight[formulaIndex]; }
	inline CVector3 GetConstCIterStart(int formulaIndex) const { return constCIterStart[formulaIndex]; }
	inline CVector3 GetConstCIterStop(int formulaIndex) const { return constCIterStop[formulaIndex]; }
	inline CVector3 GetConstCWeight(int formulaIndex) const { return constCWeight[formulaIndex]; }
	inline CVector3 GetFormulaPosition(int formulaIndex) const { return formulaPosition[formulaIndex]; }
	inline CVector3 GetFormulaRotation(int formulaIndex) const { return formulaRotation[formulaIndex]; }
	inline CVector3 GetFormulaRepeat(int formulaIndex) const { return formulaRepeat[formulaIndex]; }
	inline CVector3 GetPositionIterStart(int formulaIndex) const { return positionIterStart[formulaIndex]; }
	inline CVector3 GetPositionIterStop(int formulaIndex) const { return positionIterStop[formulaIndex]; }
	inline CVector3 GetRotationIterStart(int formulaIndex) const { return rotationIterStart[formulaIndex]; }
	inline CVector3 GetRotationIterStop(int formulaIndex) const { return rotationIterStop[formulaIndex]; }
	inline CVector3 GetRepeatIterStart(int formulaIndex) const { return repeatIterStart[formulaIndex]; }
	inline CVector3 GetRepeatIterStop(int formulaIndex) const { return repeatIterStop[formulaIndex]; }
	inline const CRotationMatrix &GetFormulaRotationMatrix(int formulaIndex) const { return mRotFormulaRotation[formulaIndex]; }
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
	inline int GetMaxN() const { return maxN; }

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
	CVector3 juliaCIterStart[NUMBER_OF_FRACTALS];
	CVector3 juliaCIterStop[NUMBER_OF_FRACTALS];
	CVector3 juliaCWeight[NUMBER_OF_FRACTALS];
	CVector3 constCIterStart[NUMBER_OF_FRACTALS];
	CVector3 constCIterStop[NUMBER_OF_FRACTALS];
	CVector3 constCWeight[NUMBER_OF_FRACTALS];
	CVector3 formulaPosition[NUMBER_OF_FRACTALS];
	CVector3 formulaRotation[NUMBER_OF_FRACTALS];
	CVector3 formulaRepeat[NUMBER_OF_FRACTALS];
	CRotationMatrix mRotFormulaRotation[NUMBER_OF_FRACTALS];
	CVector3 positionIterStart[NUMBER_OF_FRACTALS];
	CVector3 positionIterStop[NUMBER_OF_FRACTALS];
	CVector3 rotationIterStart[NUMBER_OF_FRACTALS];
	CVector3 rotationIterStop[NUMBER_OF_FRACTALS];
	CVector3 repeatIterStart[NUMBER_OF_FRACTALS];
	CVector3 repeatIterStop[NUMBER_OF_FRACTALS];
	double initialWAxis[NUMBER_OF_FRACTALS];
	bool useAdditionalBailoutCond[NUMBER_OF_FRACTALS];
	int formulaMaxiter[NUMBER_OF_FRACTALS];
	cAbstractFractal *fractalFormulaFunctions[NUMBER_OF_FRACTALS];

	void CreateSequence(std::shared_ptr<const cParameterContainer> generalPar);
};

#endif /* MANDELBULBER2_SRC_NINE_FRACTALS_HPP_ */

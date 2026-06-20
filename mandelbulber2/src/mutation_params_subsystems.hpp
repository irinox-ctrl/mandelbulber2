/**
 * Mutation parameter subsystem structs (union/variant refactor — phase 1).
 * Core pipeline: fold, warp, math, clip.
 * DE subsystems: standardized param blocks for v7.7+ systems.
 */

#ifndef MANDELBULBER2_SRC_MUTATION_PARAMS_SUBSYSTEMS_HPP_
#define MANDELBULBER2_SRC_MUTATION_PARAMS_SUBSYSTEMS_HPP_

#include "algebra.hpp"

enum enumMutationFoldType;
enum enumMutationFoldPosition;
enum enumMutationWarpType;
enum enumMutationMathType;
struct sMutationFoldParams
{
	enumMutationFoldType foldType;
	enumMutationFoldPosition foldPosition;
	double foldLimit = 1.0;
	double foldValue = 1.0;
	int kaleidoscopeSides = 6;
	int foldIterStart = 0;
	int foldIterStop = 1000000;
};

/** Warp distortion (pre/post pipeline). */
struct sMutationWarpParams
{
	enumMutationWarpType warpType;
	double warpFrequency = 1.0;
	double warpAmplitude = 0.0;
	bool adaptiveStrength = false;
	double adaptiveThreshold = 2.0;
	int warpIterStart = 0;
	int warpIterStop = 1000000;
};

/** Math injection (pre/post pipeline). */
struct sMutationMathParams
{
	enumMutationMathType mathType;
	double mathP1 = 0.0;
	double mathP2 = 0.0;
	double mathP3 = 0.0;
	double mathP4 = 0.0;
	double mathP5 = 0.0;
	double mathP6 = 0.0;
	double mathP7 = 0.0;
	double mathP8 = 0.0;
	double mathMix = 1.0;
	int mathIterStart = 0;
	int mathIterStop = 1000000;
};

/** Clip / SDF boolean system. */
struct sMutationClipParams
{
	int clipType = 0;
	double clipCenterX = 0.0;
	double clipCenterY = 0.0;
	double clipCenterZ = 0.0;
	double clipSizeX = 1.0;
	double clipSizeY = 1.0;
	double clipSizeZ = 1.0;
	double clipRadius = 1.0;
	double clipMajorRadius = 0.5;
	double clipAngle = 45.0;
	double clipAmplitude = 0.1;
	double clipFrequency = 1.0;
	double clipSmoothK = 0.1;
	int clipBooleanOp = 0;
	double clipPreRotX = 0.0;
	double clipPreRotY = 0.0;
	double clipPreRotZ = 0.0;
	int clipNPoints = 5;
	double clipParamA = 1.0;
	double clipParamB = 1.0;
	double clipParamC = 1.0;
	double clipThreshold = 0.0;
	int clipIterStart = 0;
	int clipIterStop = 1000000;
	CRotationMatrix clipPreRotMatrix;
};

/** Standard 100-type DE subsystem (jos, pk, warpDist, symKal, noise, orbitTrap DE). */
struct sMutationDeSubsystemStd
{
	int type;
	double factor;
	double paramA;
	double paramB;
	double paramC;
	double paramD;
	double freq;
	double amp;
	double scale;
	double phase;
	int iterStart;
	int iterStop;
};

/** Extended 8-param DE subsystem (mandelbox math, abox). */
struct sMutationDeSubsystemExtended
{
	int type;
	double factor;
	double paramA;
	double paramB;
	double paramC;
	double paramD;
	double paramE;
	double paramF;
	double paramG;
	double paramH;
	int iterStart;
	int iterStop;
};

/** Compact 4-param DE subsystem (torus, amazing surf, sphere tree, clamp, jb, md, blockify, tile). */
struct sMutationDeSubsystemCompact
{
	int type;
	double factor;
	double paramA;
	double paramB;
	double paramC;
	double paramD;
	int iterStart;
	int iterStop;
};

/** Symmetry/kaleidoscope variant (angle/offset instead of scale/phase). */
struct sMutationDeSubsystemSymKal
{
	int type;
	double factor;
	double paramA;
	double paramB;
	double paramC;
	double paramD;
	double freq;
	double amp;
	double angle;
	double offset;
	int iterStart;
	int iterStop;
};

/** DE subsystem slot ids (fixed mapping for variant array). */
enum eMutationDeSubsystemId : int
{
	mutDeJosLeys = 0,
	mutDePk,
	mutDeMbMath,
	mutDeWarpDist,
	mutDeSymKal,
	mutDeAbox,
	mutDeNoise,
	mutDeOrbitTrap,
	mutDeTorus,
	mutDeAs,
	mutDeSm,
	mutDeClamp,
	mutDeJb,
	mutDeMd,
	mutDeBlockify,
	mutDeTile,
	mutDeCount
};

/** Layout tag for DE subsystem union storage (C++14 alternative to std::variant). */
enum eMutationDeSubsystemLayout : int
{
	mutDeLayoutStd = 0,
	mutDeLayoutExtended,
	mutDeLayoutCompact,
	mutDeLayoutSymKal
};

struct sMutationDeSubsystemSlot
{
	eMutationDeSubsystemLayout layout = mutDeLayoutStd;
	union
	{
		sMutationDeSubsystemStd stdParams;
		sMutationDeSubsystemExtended extParams;
		sMutationDeSubsystemCompact compactParams;
		sMutationDeSubsystemSymKal symKalParams;
	} data;
};

#endif /* MANDELBULBER2_SRC_MUTATION_PARAMS_SUBSYSTEMS_HPP_ */

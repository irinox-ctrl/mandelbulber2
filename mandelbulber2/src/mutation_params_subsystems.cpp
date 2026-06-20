/**
 * Mutation DE subsystem OpenCL copy helpers (phase 3).
 */

#include "nine_fractals.hpp"

#ifdef USE_OPENCL

static void CopyDeStdToCl(const sMutationDeSubsystemStd &src, sClMutationDeSubsystemStd &dst)
{
	dst.type = src.type;
	dst.factor = static_cast<cl_float>(src.factor);
	dst.paramA = static_cast<cl_float>(src.paramA);
	dst.paramB = static_cast<cl_float>(src.paramB);
	dst.paramC = static_cast<cl_float>(src.paramC);
	dst.paramD = static_cast<cl_float>(src.paramD);
	dst.freq = static_cast<cl_float>(src.freq);
	dst.amp = static_cast<cl_float>(src.amp);
	dst.scale = static_cast<cl_float>(src.scale);
	dst.phase = static_cast<cl_float>(src.phase);
	dst.iterStart = src.iterStart;
	dst.iterStop = src.iterStop;
}

static void CopyDeExtendedToCl(const sMutationDeSubsystemExtended &src,
	sClMutationDeSubsystemExtended &dst)
{
	dst.type = src.type;
	dst.factor = static_cast<cl_float>(src.factor);
	dst.paramA = static_cast<cl_float>(src.paramA);
	dst.paramB = static_cast<cl_float>(src.paramB);
	dst.paramC = static_cast<cl_float>(src.paramC);
	dst.paramD = static_cast<cl_float>(src.paramD);
	dst.paramE = static_cast<cl_float>(src.paramE);
	dst.paramF = static_cast<cl_float>(src.paramF);
	dst.paramG = static_cast<cl_float>(src.paramG);
	dst.paramH = static_cast<cl_float>(src.paramH);
	dst.iterStart = src.iterStart;
	dst.iterStop = src.iterStop;
}

static void CopyDeCompactToCl(const sMutationDeSubsystemCompact &src,
	sClMutationDeSubsystemCompact &dst)
{
	dst.type = src.type;
	dst.factor = static_cast<cl_float>(src.factor);
	dst.paramA = static_cast<cl_float>(src.paramA);
	dst.paramB = static_cast<cl_float>(src.paramB);
	dst.paramC = static_cast<cl_float>(src.paramC);
	dst.paramD = static_cast<cl_float>(src.paramD);
	dst.iterStart = src.iterStart;
	dst.iterStop = src.iterStop;
}

static void CopyDeSymKalToCl(const sMutationDeSubsystemSymKal &src, sClMutationDeSubsystemSymKal &dst)
{
	dst.type = src.type;
	dst.factor = static_cast<cl_float>(src.factor);
	dst.paramA = static_cast<cl_float>(src.paramA);
	dst.paramB = static_cast<cl_float>(src.paramB);
	dst.paramC = static_cast<cl_float>(src.paramC);
	dst.paramD = static_cast<cl_float>(src.paramD);
	dst.freq = static_cast<cl_float>(src.freq);
	dst.amp = static_cast<cl_float>(src.amp);
	dst.angle = static_cast<cl_float>(src.angle);
	dst.offset = static_cast<cl_float>(src.offset);
	dst.iterStart = src.iterStart;
	dst.iterStop = src.iterStop;
}

void CopyMutationDeSubsystemsToOpenCl(const sFormulaMutationParams &src, sClFormulaMutationParams &dst)
{
	CopyDeStdToCl(src.josLeys(), dst.josLeys);
	CopyDeStdToCl(src.pk(), dst.pk);
	CopyDeExtendedToCl(src.mbMath(), dst.mbMath);
	CopyDeStdToCl(src.warpDist(), dst.warpDist);
	CopyDeSymKalToCl(src.symKal(), dst.symKal);
	CopyDeExtendedToCl(src.abox(), dst.abox);
	CopyDeStdToCl(src.noiseDe(), dst.noiseDe);
	CopyDeCompactToCl(src.orbitTrapDe(), dst.orbitTrapDe);
	CopyDeCompactToCl(src.torusDe(), dst.torusDe);
	CopyDeCompactToCl(src.asDe(), dst.asDe);
	CopyDeCompactToCl(src.smDe(), dst.smDe);
	CopyDeCompactToCl(src.clampDe(), dst.clampDe);
	CopyDeCompactToCl(src.jbDe(), dst.jbDe);
	CopyDeCompactToCl(src.mdDe(), dst.mdDe);
	CopyDeCompactToCl(src.blockifyDe(), dst.blockifyDe);
	CopyDeCompactToCl(src.tileDe(), dst.tileDe);
}

#endif /* USE_OPENCL */

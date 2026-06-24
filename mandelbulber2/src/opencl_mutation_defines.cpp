/**
 * Shared OpenCL compile defines for the mutation subsystem.
 */

#include "opencl_mutation_defines.hpp"

#include "nine_fractals.hpp"

void AppendMutationOpenClDefines(const cNineFractals *fractals, QString &definesCollector)
{
	if (!fractals) return;

	bool mutationUsed = false;
	std::set<int> invTypes, foldTypes, swizzles, mathTypes, clipTypes, clampTypes, jbTypes, mdTypes;
	std::set<int> josTypes, pkTypes, mbTypes, wdTypes, skTypes, aboxTypes, noiseTypes, orbitTypes;
	std::set<int> torusTypes, asTypes, smTypes, blockifyTypes, tileTypes;

	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		const sFormulaMutationParams &mp = fractals->GetMutationParams(i);
		if (!mp.enabled) continue;
		mutationUsed = true;
		invTypes.insert(mp.inversionType);
		foldTypes.insert(static_cast<int>(mp.foldType));
		swizzles.insert(static_cast<int>(mp.swizzle));
		mathTypes.insert(static_cast<int>(mp.mathType));
		clipTypes.insert(mp.clipType);
		clampTypes.insert(mp.clampType);
		jbTypes.insert(mp.jbType);
		mdTypes.insert(mp.mdType);
		josTypes.insert(static_cast<int>(mp.josLeysDeType));
		pkTypes.insert(static_cast<int>(mp.pseudoKleinianDeType));
		mbTypes.insert(static_cast<int>(mp.mbMathType));
		wdTypes.insert(static_cast<int>(mp.warpDistType));
		skTypes.insert(static_cast<int>(mp.symKalType));
		aboxTypes.insert(static_cast<int>(mp.aboxType));
		noiseTypes.insert(static_cast<int>(mp.noiseType));
		orbitTypes.insert(static_cast<int>(mp.orbitTrapType));
		torusTypes.insert(static_cast<int>(mp.torusType));
		asTypes.insert(static_cast<int>(mp.asType));
		smTypes.insert(static_cast<int>(mp.smType));
		blockifyTypes.insert(mp.blockifyType);
		tileTypes.insert(mp.tileType);
	}

	if (!mutationUsed) return;

	definesCollector += " -DUSE_MUTATION";
	definesCollector += " -DMUTATION_PRUNE";

	auto emitNeedDefines = [&](const char *prefix, const std::set<int> &values) {
		for (int v : values)
			definesCollector += QString(" -D%1_%2").arg(prefix).arg(v);
	};

	emitNeedDefines("MUT_NEED_INVERSIONTYPE", invTypes);
	emitNeedDefines("MUT_NEED_FOLDTYPE", foldTypes);
	emitNeedDefines("MUT_NEED_SWIZZLE", swizzles);
	emitNeedDefines("MUT_NEED_MATHTYPE", mathTypes);
	emitNeedDefines("MUT_NEED_CLIPTYPE", clipTypes);
	emitNeedDefines("MUT_NEED_CLAMPTYPE", clampTypes);
	emitNeedDefines("MUT_NEED_JBTYPE", jbTypes);
	emitNeedDefines("MUT_NEED_MDTYPE", mdTypes);
	emitNeedDefines("MUT_NEED_JOSLEYSDETYPE", josTypes);
	emitNeedDefines("MUT_NEED_PKDETYPE", pkTypes);
	emitNeedDefines("MUT_NEED_MBMATHTYPE", mbTypes);
	emitNeedDefines("MUT_NEED_WARPDISTTYPE", wdTypes);
	emitNeedDefines("MUT_NEED_SYMKALTYPE", skTypes);
	emitNeedDefines("MUT_NEED_ABOXTYPE", aboxTypes);
	emitNeedDefines("MUT_NEED_NOISETYPE", noiseTypes);
	emitNeedDefines("MUT_NEED_ORBITTRAPTYPE", orbitTypes);
	emitNeedDefines("MUT_NEED_TORUSTYPE", torusTypes);
	emitNeedDefines("MUT_NEED_ASTYPE", asTypes);
	emitNeedDefines("MUT_NEED_SMTYPE", smTypes);
	emitNeedDefines("MUT_NEED_BLOCKIFYTYPE", blockifyTypes);
	emitNeedDefines("MUT_NEED_TILETYPE", tileTypes);
}

/**
 * Mandelbulber v2 — Auto MaxIter + Bailout estimator
 */

#include "auto_iter_bailout.hpp"

#include <algorithm>
#include <cmath>

#include "calculate_distance.hpp"
#include "common_math.h"
#include "fractal_container.hpp"
#include "fractparams.hpp"
#include "nine_fractals.hpp"
#include "parameters.hpp"
#include "render_data.hpp"
#include "formula/definition/all_fractal_list_enums.hpp"

namespace autoIterBailout
{

double GetFormulaComplexityFactor(int formulaIndex)
{
	using namespace fractal;
	switch (formulaIndex)
	{
		case mandelbulb:
		case mandelbulbPower2:
		case mandelbulb2:
		case mandelbulb3:
		case mandelbulb4: return 1.0;
		case mandelbox:
		case mandelboxFast:
		case mandelboxSmooth:
		case mandelboxMenger: return 2.5;
		case amazingSurf:
		case amazingSurfMod1:
		case amazingSurfMod2:
		case amazingSurfMod3:
		case amazingSurfMod4:
		case amazingSurfMulti: return 3.0;
		case mengerSponge:
		case mengerMod1:
		case menger3:
		case menger4d: return 2.0;
		case pseudoKleinian:
		case pseudoKleinianMod1:
		case pseudoKleinianMod2:
		case pseudoKleinianMod3:
		case pseudoKleinianMod4:
		case pseudoKleinianMod5:
		case pseudoKleinianMod6:
		case pseudoKleinianMod7:
		case pseudoKleinian4d:
		case pseudoKleinianStdDE: return 4.0;
		case josKleinian:
		case josKleinianV2:
		case josKleinianV3:
		case josKleinianV4: return 4.5;
		case buffalo: return 1.3;
		case aboxMod1:
		case aboxMod11:
		case aboxMod12:
		case aboxMod13:
		case aboxMod14:
		case aboxMod15: return 2.8;
		default: return 1.5;
	}
}

sProbeStats ProbeScene(const sParamRender &params, cNineFractals &fractals, int probeN,
	int forcedFormulaIndex)
{
	(void)probeN;
	sProbeStats stats;
	const int grid = 8;
	stats.total = grid * grid * grid;

	const double probeRange = params.cameraDistanceToTarget * 0.3;
	const CVector3 target = params.target;

	for (int iz = 0; iz < grid; iz++)
	{
		for (int iy = 0; iy < grid; iy++)
		{
			for (int ix = 0; ix < grid; ix++)
			{
				const double fx = (grid > 1) ? ix / double(grid - 1) : 0.5;
				const double fy = (grid > 1) ? iy / double(grid - 1) : 0.5;
				const double fz = (grid > 1) ? iz / double(grid - 1) : 0.5;

				const CVector3 point = target
					+ CVector3((fx - 0.5) * probeRange, (fy - 0.5) * probeRange, (fz - 0.5) * probeRange);

				sDistanceIn distIn(point, 0.001, false);
				sDistanceOut distOut{};
				CalculateDistanceSimple(params, fractals, distIn, &distOut, forcedFormulaIndex, nullptr);

				if (distOut.maxiter)
					stats.bounded++;
				else if (distOut.distance < 0.01)
					stats.nearSurface++;
				else
					stats.escaped++;

				stats.maxUsefulIter = std::max(stats.maxUsefulIter, double(distOut.iters));
			}
		}
	}

	return stats;
}

sAutoIterBailoutResult EstimateGlobalIterBailout(const sParamRender &params,
	cNineFractals &fractals, std::shared_ptr<cParameterContainer> par)
{
	sAutoIterBailoutResult result;

	sParamRender probeParams = params;
	probeParams.N = 50;

	const int formulaIndex = par->Get<int>("formula", 1);
	const double complexityFactor = GetFormulaComplexityFactor(formulaIndex);

	const sProbeStats stats = ProbeScene(probeParams, fractals, 50, -1);

	if (stats.total > 0)
	{
		result.escapeFraction = double(stats.escaped) / stats.total;
		result.surfaceFraction = double(stats.nearSurface) / stats.total;
		result.boundedFraction = double(stats.bounded) / stats.total;
	}

	int estimatedN;
	if (result.surfaceFraction > 0.3)
		estimatedN = int(stats.maxUsefulIter * complexityFactor * 2.5);
	else if (result.escapeFraction > 0.8)
		estimatedN = int(stats.maxUsefulIter * complexityFactor * 1.2);
	else
		estimatedN = int(stats.maxUsefulIter * complexityFactor * 1.8);

	result.estimatedN = clamp(estimatedN, 5, 5000);
	const int userN = par->Get<int>("N");
	if (userN > 0) result.estimatedN = std::min(result.estimatedN, userN);

	const double cameraDistance = params.cameraDistanceToTarget;
	result.estimatedBailout = std::min(std::max(10.0, cameraDistance * 4.0), 1e6);

	return result;
}

int EstimateSlotMaxIter(const sParamRender &params, cNineFractals &fractals, int slotIndex,
	std::shared_ptr<cParameterContainer> par)
{
	const int formulaIndex = par->Get<int>("formula", slotIndex + 1);
	const double complexity = GetFormulaComplexityFactor(formulaIndex);

	sParamRender probeParams = params;
	probeParams.N = 50;

	const sProbeStats stats = ProbeScene(probeParams, fractals, 50, slotIndex + 1);
	const int globalN = std::max(par->Get<int>("N"), 1);
	const int minIter = std::min(20, globalN);
	return clamp(int(stats.maxUsefulIter * complexity * 1.6), minIter, std::min(2000, globalN));
}

void ApplyGlobalEstimates(std::shared_ptr<cParameterContainer> par,
	const sAutoIterBailoutResult &result)
{
	par->Set("N", result.estimatedN);
	par->Set("formula_maxiter", 1, result.estimatedN);
	par->Set("bailout", result.estimatedBailout);
	par->Set("use_default_bailout", false);
}

void ApplyPerSlotEstimates(std::shared_ptr<cParameterContainer> par,
	std::shared_ptr<cFractalContainer> parFractal)
{
	sRenderData renderData;
	renderData.objectData.resize(NUMBER_OF_FRACTALS);
	cNineFractals fractals(parFractal, par);
	sParamRender paramRender(par, &renderData.objectData);

	for (int slot = 0; slot < NUMBER_OF_FRACTALS; slot++)
	{
		if (!par->Get<bool>("fractal_enable", slot + 1)) continue;
		if (par->Get<int>("formula", slot + 1) == int(fractal::none)) continue;

		const int optimalIter = EstimateSlotMaxIter(paramRender, fractals, slot, par);
		par->Set("formula_maxiter", slot + 1, optimalIter);
	}
}

QString FormatResultLabel(const sAutoIterBailoutResult &result)
{
	return QString("Auto: N=%1  bailout=%2  (surface=%3%  bounded=%4%)")
		.arg(result.estimatedN)
		.arg(result.estimatedBailout, 0, 'g', 3)
		.arg(int(result.surfaceFraction * 100.0))
		.arg(int(result.boundedFraction * 100.0));
}

} // namespace autoIterBailout

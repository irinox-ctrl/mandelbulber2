/**
 * Mandelbulber v2 — Auto MaxIter + Bailout estimator
 *
 * Probes the scene around the camera target with a coarse DE grid and
 * estimates optimal global N/bailout and per-formula-slot maxiter values.
 */

#ifndef MANDELBULBER2_SRC_AUTO_ITER_BAILOUT_HPP_
#define MANDELBULBER2_SRC_AUTO_ITER_BAILOUT_HPP_

#include <QString>
#include <memory>

class cNineFractals;
class cParameterContainer;
class cFractalContainer;
struct sParamRender;

namespace autoIterBailout
{

struct sProbeStats
{
	int escaped = 0;
	int bounded = 0;
	int nearSurface = 0;
	double maxUsefulIter = 0.0;
	int total = 0;
};

struct sAutoIterBailoutResult
{
	int estimatedN = 250;
	double estimatedBailout = 100.0;
	double escapeFraction = 0.0;
	double surfaceFraction = 0.0;
	double boundedFraction = 0.0;
};

double GetFormulaComplexityFactor(int formulaIndex);

sProbeStats ProbeScene(const sParamRender &params, cNineFractals &fractals, int probeN,
	int forcedFormulaIndex = -1);

sAutoIterBailoutResult EstimateGlobalIterBailout(const sParamRender &params,
	cNineFractals &fractals, std::shared_ptr<cParameterContainer> par);

int EstimateSlotMaxIter(const sParamRender &params, cNineFractals &fractals, int slotIndex,
	std::shared_ptr<cParameterContainer> par);

void ApplyGlobalEstimates(std::shared_ptr<cParameterContainer> par,
	const sAutoIterBailoutResult &result);

void ApplyPerSlotEstimates(std::shared_ptr<cParameterContainer> par,
	std::shared_ptr<cFractalContainer> parFractal);

QString FormatResultLabel(const sAutoIterBailoutResult &result);

} // namespace autoIterBailout

#endif /* MANDELBULBER2_SRC_AUTO_ITER_BAILOUT_HPP_ */

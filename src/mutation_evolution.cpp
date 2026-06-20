/**
 * Fitness-guided mutation parameter evolution (genetic algorithm).
 */

#include "mutation_evolution.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>

#include <QtGlobal>

#include "calculate_distance.hpp"
#include "parameters.hpp"

namespace mutation_evolution
{
namespace
{
struct sGeneDef
{
	double minVal;
	double maxVal;
	const char *paramKey;
};

constexpr sGeneDef kGeneDefs[geneCount] = {
	{0.001, 10.0, "mutation_fold_limit"},
	{0.001, 10.0, "mutation_fold_value"},
	{0.01, 10.0, "mutation_warp_frequency"},
	{0.0, 5.0, "mutation_warp_amplitude"},
	{-5.0, 5.0, "mutation_math_p1"},
	{-5.0, 5.0, "mutation_math_p2"},
	{-5.0, 5.0, "mutation_math_p3"},
	{-5.0, 5.0, "mutation_math_p4"},
	{0.0, 1.0, "mutation_math_mix"},
	{0.0, 1.0, "mutation_z_mix"},
	{0.0, 1.0, "mutation_master_weight"},
	{0.1, 2.0, "mutation_de_scale"},
};

double ClampGene(int gene, double v)
{
	return qBound(kGeneDefs[gene].minVal, v, kGeneDefs[gene].maxVal);
}

double GetGeneValue(const sFormulaMutationParams &mut, int gene)
{
	switch (gene)
	{
		case geneFoldLimit: return mut.fold.foldLimit;
		case geneFoldValue: return mut.fold.foldValue;
		case geneWarpFrequency: return mut.warp.warpFrequency;
		case geneWarpAmplitude: return mut.warp.warpAmplitude;
		case geneMathP1: return mut.math.mathP1;
		case geneMathP2: return mut.math.mathP2;
		case geneMathP3: return mut.math.mathP3;
		case geneMathP4: return mut.math.mathP4;
		case geneMathMix: return mut.math.mathMix;
		case geneZMix: return mut.zMix;
		case geneMasterWeight: return mut.masterWeight;
		case geneDeScale: return mut.deScale;
		default: return 0.0;
	}
}

void SetGeneValue(sFormulaMutationParams &mut, int gene, double v)
{
	v = ClampGene(gene, v);
	switch (gene)
	{
		case geneFoldLimit: mut.fold.foldLimit = v; break;
		case geneFoldValue: mut.fold.foldValue = v; break;
		case geneWarpFrequency: mut.warp.warpFrequency = v; break;
		case geneWarpAmplitude: mut.warp.warpAmplitude = v; break;
		case geneMathP1: mut.math.mathP1 = v; break;
		case geneMathP2: mut.math.mathP2 = v; break;
		case geneMathP3: mut.math.mathP3 = v; break;
		case geneMathP4: mut.math.mathP4 = v; break;
		case geneMathMix: mut.math.mathMix = v; break;
		case geneZMix: mut.zMix = v; break;
		case geneMasterWeight: mut.masterWeight = v; break;
		case geneDeScale: mut.deScale = v; break;
		default: break;
	}
}

bool IsBadDistance(double d)
{
	return !std::isfinite(d) || d < 0.0 || d > 1e12;
}

sMutationGenome MutateGenome(const sMutationGenome &parent, std::mt19937 &rng, double rate,
	double sigma)
{
	sMutationGenome child = parent;
	std::uniform_real_distribution<double> unit(0.0, 1.0);
	std::normal_distribution<double> normal(0.0, 1.0);
	for (int i = 0; i < geneCount; ++i)
	{
		if (unit(rng) > rate) continue;
		const sGeneDef &def = kGeneDefs[i];
		const double span = def.maxVal - def.minVal;
		child.values[i] = ClampGene(i, child.values[i] + normal(rng) * sigma * span);
	}
	return child;
}

sMutationGenome Crossover(const sMutationGenome &a, const sMutationGenome &b, std::mt19937 &rng)
{
	sMutationGenome child;
	std::uniform_real_distribution<double> unit(0.0, 1.0);
	for (int i = 0; i < geneCount; ++i)
		child.values[i] = (unit(rng) < 0.5) ? a.values[i] : b.values[i];
	return child;
}

int TournamentSelect(const std::vector<sEvolutionCandidate> &pop, std::mt19937 &rng, int k)
{
	std::uniform_int_distribution<int> pick(0, static_cast<int>(pop.size()) - 1);
	int best = pick(rng);
	for (int i = 1; i < k; ++i)
	{
		const int idx = pick(rng);
		if (pop[static_cast<size_t>(idx)].weightedScore > pop[static_cast<size_t>(best)].weightedScore)
			best = idx;
	}
	return best;
}
} // namespace

double sMutationGenome::DistanceTo(const sMutationGenome &other) const
{
	double sum = 0.0;
	for (int i = 0; i < geneCount; ++i)
	{
		const double span = kGeneDefs[i].maxVal - kGeneDefs[i].minVal;
		if (span < 1e-12) continue;
		const double d = (values[i] - other.values[i]) / span;
		sum += d * d;
	}
	return std::sqrt(sum / geneCount);
}

sMutationGenome GenomeFromMutationParams(const sFormulaMutationParams &mut)
{
	sMutationGenome g;
	for (int i = 0; i < geneCount; ++i)
		g.values[i] = GetGeneValue(mut, i);
	return g;
}

void ApplyGenomeToMutationParams(const sMutationGenome &genome, sFormulaMutationParams &mut)
{
	for (int i = 0; i < geneCount; ++i)
		SetGeneValue(mut, i, genome.values[i]);
	ValidateMutationParams(mut);
}

void ApplyGenomeToParameterContainer(const sMutationGenome &genome, int formulaSlot,
	cParameterContainer &par)
{
	for (int i = 0; i < geneCount; ++i)
		par.Set(QString::fromLatin1(kGeneDefs[i].paramKey), formulaSlot, genome.values[i]);
}

exploration::sMutationFitness ScoreMutationGenome(const sParamRender &pr, cNineFractals &fractals,
	int formulaIndex, const sMutationGenome &genome, const CVector3 &sampleCenter,
	const sMutationGenome *baselineGenome, int gridSize, int maxIterations)
{
	exploration::sMutationFitness fit;

	sFormulaMutationParams mut = fractals.GetMutationParams(formulaIndex);
	ApplyGenomeToMutationParams(genome, mut);
	fractals.SetMutationParams(formulaIndex, mut);

	const int n = std::max(2, gridSize);
	const double zRange = 0.75;
	const double zStep = (n > 1) ? (2.0 * zRange / (n - 1)) : 0.0;
	const int total = n * n * n;
	int inside = 0;
	int surface = 0;
	int nanCount = 0;
	double iterSum = 0.0;
	double iterSqSum = 0.0;

	sParamRender prLocal = pr;
	prLocal.N = std::min(maxIterations, pr.N > 0 ? pr.N : maxIterations);

	const auto t0 = std::chrono::steady_clock::now();

	for (int iz = 0; iz < n; ++iz)
	{
		const double z0z = sampleCenter.z - zRange + iz * zStep;
		for (int iy = 0; iy < n; ++iy)
		{
			const double z0y = sampleCenter.y - zRange + iy * zStep;
			for (int ix = 0; ix < n; ++ix)
			{
				const double z0x = sampleCenter.x - zRange + ix * zStep;
				sDistanceIn distIn(CVector3(z0x, z0y, z0z), 0.001, false);
				sDistanceOut distOut;
				distOut.distance = 0;
				distOut.iters = 0;
				distOut.totalIters = 0;
				distOut.colorIndex = 0;
				distOut.objectId = 0;
				distOut.maxiter = false;

				CalculateDistanceSimple(prLocal, fractals, distIn, &distOut, formulaIndex, nullptr);

				if (IsBadDistance(distOut.distance)) nanCount++;

				const double iters = static_cast<double>(distOut.iters);
				iterSum += iters;
				iterSqSum += iters * iters;

				if (distOut.maxiter)
					inside++;
				else if (distOut.distance < 0.01)
					surface++;
			}
		}
	}

	const auto t1 = std::chrono::steady_clock::now();
	const double elapsedMs =
		std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

	const double insideFrac = static_cast<double>(inside) / total;
	const double surfaceFrac = static_cast<double>(surface) / total;

	double balanceScore = 1.0 - 2.0 * std::abs(insideFrac - 0.4);
	balanceScore = std::max(0.0, balanceScore);

	double surfaceScore = std::min(1.0, surfaceFrac * 3.0);

	double varianceScore = 0.0;
	if (total > 1)
	{
		const double mean = iterSum / total;
		const double var = (iterSqSum / total) - (mean * mean);
		varianceScore = std::min(1.0, std::sqrt(std::max(0.0, var)) / (prLocal.N * 0.15));
	}

	double visual = 0.0;
	if (insideFrac <= 0.9 && (inside + surface) > 0 && !(insideFrac < 0.05 && surfaceFrac < 0.05))
		visual = qBound(0.0, 0.25 * balanceScore + 0.35 * varianceScore + 0.4 * surfaceScore, 1.0);

	fit.visualInterest = visual;
	fit.detailComplexity = varianceScore;
	fit.symmetryBalance = balanceScore;
	fit.boundaryQuality = surfaceScore;
	fit.convergenceSpeed = std::min(1.0, iterSum / (total * prLocal.N));
	fit.numericalStability = 1.0 - static_cast<double>(nanCount) / total;
	fit.renderSpeed = std::min(1.0, 50.0 / std::max(1.0, elapsedMs));
	if (baselineGenome)
	{
		const double dist = genome.DistanceTo(*baselineGenome);
		fit.novelty = std::min(1.0, dist * 2.0);
	}
	else
	{
		fit.novelty = 0.5;
	}

	return fit;
}

sEvolutionResult RunEvolution(const sEvolutionConfig &config, const sParamRender &pr,
	cNineFractals &fractals, int formulaIndex, const CVector3 &sampleCenter,
	const sMutationGenome &seedGenome, const std::shared_ptr<std::atomic<bool>> &cancelled,
	const std::shared_ptr<std::atomic<int>> &progress)
{
	sEvolutionResult result;
	std::mt19937 rng(static_cast<unsigned>(
		std::chrono::steady_clock::now().time_since_epoch().count()));

	std::vector<sEvolutionCandidate> population;
	population.reserve(static_cast<size_t>(config.populationSize));
	population.push_back({seedGenome, {}, 0.0});

	for (int i = 1; i < config.populationSize; ++i)
	{
		sMutationGenome g = MutateGenome(seedGenome, rng, 0.5, config.mutationSigma);
		population.push_back({g, {}, 0.0});
	}

	auto evaluatePop = [&](std::vector<sEvolutionCandidate> &pop, int genIndex, int genTotal) {
		const int popSize = static_cast<int>(pop.size());
		for (int pi = 0; pi < popSize; ++pi)
		{
			auto &c = pop[static_cast<size_t>(pi)];
			if (cancelled && cancelled->load()) return;
			c.fitness = ScoreMutationGenome(pr, fractals, formulaIndex, c.genome, sampleCenter,
				&seedGenome, config.gridSize, config.maxIterations);
			c.weightedScore = c.fitness.WeightedTotal(config.objectiveWeights);
			if (progress && genTotal > 0)
			{
				const int pct = ((genIndex * popSize + pi + 1) * 100) / (genTotal * popSize);
				progress->store(std::min(99, pct));
			}
		}
	};

	evaluatePop(population, 0, config.generations);
	if (cancelled && cancelled->load()) return result;

	for (int gen = 1; gen < config.generations; ++gen)
	{
		std::vector<sEvolutionCandidate> nextGen;
		nextGen.reserve(static_cast<size_t>(config.populationSize));

		std::sort(population.begin(), population.end(),
			[](const sEvolutionCandidate &a, const sEvolutionCandidate &b) {
				return a.weightedScore > b.weightedScore;
			});

		const int elite = std::max(1, config.populationSize / 8);
		for (int i = 0; i < elite && i < static_cast<int>(population.size()); ++i)
			nextGen.push_back(population[static_cast<size_t>(i)]);

		std::uniform_real_distribution<double> unit(0.0, 1.0);
		while (static_cast<int>(nextGen.size()) < config.populationSize)
		{
			const int p1 = TournamentSelect(population, rng, config.tournamentSize);
			const int p2 = TournamentSelect(population, rng, config.tournamentSize);
			sMutationGenome child = (unit(rng) < config.crossoverRate)
				? Crossover(population[static_cast<size_t>(p1)].genome,
						population[static_cast<size_t>(p2)].genome, rng)
				: population[static_cast<size_t>(p1)].genome;
			child = MutateGenome(child, rng, config.mutationRate, config.mutationSigma);
			nextGen.push_back({child, {}, 0.0});
		}

		population = std::move(nextGen);
		evaluatePop(population, gen, config.generations);
		result.generationsCompleted = gen + 1;

		if (cancelled && cancelled->load()) break;
	}

	std::sort(population.begin(), population.end(),
		[](const sEvolutionCandidate &a, const sEvolutionCandidate &b) {
			return a.weightedScore > b.weightedScore;
		});

	result.population = std::move(population);
	if (!result.population.empty()) result.bestByWeight = result.population.front();

	std::vector<exploration::sMultiObjectiveResult> mo;
	mo.resize(result.population.size());
	for (size_t i = 0; i < result.population.size(); ++i)
	{
		mo[i].candidateIndex = static_cast<int>(i);
		result.population[i].fitness.FillObjectives(mo[i].objectives);
	}
	result.paretoFrontierIndices = exploration::sMultiObjectiveResult::ComputeParetoFrontier(mo);

	if (progress) progress->store(100);
	return result;
}

} // namespace mutation_evolution

/**
 * Fitness-guided mutation parameter evolution (genetic algorithm).
 */

#ifndef MANDELBULBER2_SRC_MUTATION_EVOLUTION_HPP_
#define MANDELBULBER2_SRC_MUTATION_EVOLUTION_HPP_

#include <atomic>
#include <memory>
#include <vector>

#include "exploration_engine.h"
#include "fractparams.hpp"
#include "nine_fractals.hpp"

class cParameterContainer;
class cFractalContainer;

namespace mutation_evolution
{

enum eMutationGene : int
{
	geneFoldLimit = 0,
	geneFoldValue,
	geneWarpFrequency,
	geneWarpAmplitude,
	geneMathP1,
	geneMathP2,
	geneMathP3,
	geneMathP4,
	geneMathMix,
	geneZMix,
	geneMasterWeight,
	geneDeScale,
	geneCount
};

struct sMutationGenome
{
	double values[geneCount] = {};

	double DistanceTo(const sMutationGenome &other) const;
};

struct sEvolutionCandidate
{
	sMutationGenome genome;
	exploration::sMutationFitness fitness;
	double weightedScore = 0.0;
};

struct sEvolutionConfig
{
	int populationSize = 16;
	int generations = 5;
	int tournamentSize = 3;
	double crossoverRate = 0.7;
	double mutationRate = 0.25;
	double mutationSigma = 0.15;
	int maxIterations = 48;
	int gridSize = 3;
	exploration::sMutationObjectiveWeights objectiveWeights;
};

struct sEvolutionResult
{
	std::vector<sEvolutionCandidate> population;
	std::vector<int> paretoFrontierIndices;
	sEvolutionCandidate bestByWeight;
	int generationsCompleted = 0;
};

sMutationGenome GenomeFromMutationParams(const sFormulaMutationParams &mut);
void ApplyGenomeToMutationParams(const sMutationGenome &genome, sFormulaMutationParams &mut);
void ApplyGenomeToParameterContainer(const sMutationGenome &genome, int formulaSlot,
	cParameterContainer &par);

exploration::sMutationFitness ScoreMutationGenome(const sParamRender &pr, cNineFractals &fractals,
	int formulaIndex, const sMutationGenome &genome, const CVector3 &sampleCenter,
	const sMutationGenome *baselineGenome = nullptr, int gridSize = 3, int maxIterations = 48);

sEvolutionResult RunEvolution(const sEvolutionConfig &config, const sParamRender &pr,
	cNineFractals &fractals, int formulaIndex, const CVector3 &sampleCenter,
	const sMutationGenome &seedGenome,
	const std::shared_ptr<std::atomic<bool>> &cancelled = nullptr,
	const std::shared_ptr<std::atomic<int>> &progress = nullptr);

} // namespace mutation_evolution

#endif /* MANDELBULBER2_SRC_MUTATION_EVOLUTION_HPP_ */

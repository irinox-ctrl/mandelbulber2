/**
 * 3x3lion Exploration Engine
 * Founded by Iri and Devin
 *
 * Implementation of automated parameter sweep and beauty scoring.
 */

#include "exploration_engine.h"

#include "fractal_container.hpp"
#include "parameters.hpp"
#include "system_directories.hpp"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <cmath>

cExplorationEngine::cExplorationEngine(QObject *parent) : QObject(parent)
{
	bookmarksFilePath =
		systemDirectories.GetDataDirectoryHidden() + "exploration_bookmarks.json";
	ImportBookmarks(bookmarksFilePath);
}

cExplorationEngine::~cExplorationEngine()
{
	ExportBookmarks(bookmarksFilePath);
}

void cExplorationEngine::SetParameters(std::shared_ptr<cParameterContainer> _params,
	std::shared_ptr<cFractalContainer> _fractalParams)
{
	params = _params;
	fractalParams = _fractalParams;
}

// --- Julia Group Management ---

void cExplorationEngine::SetJuliaMode(int formulaSlot, bool enabled)
{
	if (!params) return;
	params->Set("julia_mode", formulaSlot + 1, enabled);
}

void cExplorationEngine::SetJuliaC(int formulaSlot, const CVector3 &juliaC)
{
	if (!params) return;
	params->Set("julia_c", formulaSlot + 1, juliaC);
}

bool cExplorationEngine::GetJuliaMode(int formulaSlot) const
{
	if (!params) return false;
	return params->Get<bool>("julia_mode", formulaSlot + 1);
}

CVector3 cExplorationEngine::GetJuliaC(int formulaSlot) const
{
	if (!params) return CVector3(0.0, 0.0, 0.0);
	return params->Get<CVector3>("julia_c", formulaSlot + 1);
}

// --- Sweep Operations ---

void cExplorationEngine::StartSweep(const exploration::sSweepConfig &config)
{
	if (sweepRunning) return;
	sweepRunning = true;
	sweepProgress = 0;
	results.clear();

	switch (config.strategy)
	{
		case exploration::sweepGrid: RunGridSweep(config); break;
		case exploration::sweepEvolutionary: RunEvolutionarySweep(config); break;
		case exploration::sweepRandom:
		default: RunRandomSweep(config); break;
	}

	sweepRunning = false;
	emit signalSweepComplete(results.size());
}

void cExplorationEngine::StopSweep()
{
	sweepRunning = false;
}

bool cExplorationEngine::IsSweepRunning() const
{
	return sweepRunning;
}

int cExplorationEngine::GetSweepProgress() const
{
	return sweepProgress;
}

QList<exploration::sExplorationBookmark> cExplorationEngine::GetSweepResults() const
{
	return results;
}

void cExplorationEngine::RunGridSweep(const exploration::sSweepConfig &config)
{
	if (config.dimensions.isEmpty()) return;

	// Calculate total grid points
	int totalPoints = 1;
	for (const exploration::sSweepDimension &dim : config.dimensions)
	{
		totalPoints *= dim.steps;
	}
	totalPoints = qMin(totalPoints, config.maxSamples);

	// Set Julia mode
	if (params)
	{
		SetJuliaMode(config.formulaSlot, config.juliaMode);
	}

	int evaluated = 0;

	// For single-dimension sweep (most common for initial exploration)
	if (config.dimensions.size() == 1)
	{
		const exploration::sSweepDimension &dim = config.dimensions[0];
		for (int i = 0; i < dim.steps && sweepRunning; i++)
		{
			double value = dim.minVal + (dim.maxVal - dim.minVal) * i / qMax(1, dim.steps - 1);

			// Apply parameter
			if (dim.isJuliaC)
			{
				CVector3 jc = GetJuliaC(config.formulaSlot);
				if (dim.componentIndex == 0) jc.x = value;
				else if (dim.componentIndex == 1) jc.y = value;
				else jc.z = value;
				SetJuliaC(config.formulaSlot, jc);
			}

			// Note: actual rendering and scoring will be integrated when headless rendering is ready
			// For now, we store the parameter configuration as a bookmark placeholder
			exploration::sExplorationBookmark bookmark;
			bookmark.name = QString("Grid-%1-%2").arg(dim.paramName).arg(i);
			bookmark.formulaId = config.formulaSlot;
			bookmark.juliaMode = config.juliaMode;
			bookmark.juliaC = GetJuliaC(config.formulaSlot);
			bookmark.discoveredBy = config.droneId;
			bookmark.timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);

			results.append(bookmark);
			evaluated++;
			sweepProgress = (evaluated * 100) / totalPoints;
			emit signalSweepProgress(sweepProgress);
		}
	}
	// Multi-dimensional grid: sweep outer product of all dimensions
	else
	{
		QList<int> indices;
		for (int i = 0; i < config.dimensions.size(); i++) indices.append(0);
		bool done = false;

		while (!done && sweepRunning && evaluated < config.maxSamples)
		{
			// Apply all parameter values for current grid point
			for (int d = 0; d < config.dimensions.size(); d++)
			{
				const exploration::sSweepDimension &dim = config.dimensions[d];
				double value =
					dim.minVal
					+ (dim.maxVal - dim.minVal) * indices[d] / qMax(1, dim.steps - 1);

				if (dim.isJuliaC)
				{
					CVector3 jc = GetJuliaC(config.formulaSlot);
					if (dim.componentIndex == 0) jc.x = value;
					else if (dim.componentIndex == 1) jc.y = value;
					else jc.z = value;
					SetJuliaC(config.formulaSlot, jc);
				}
			}

			exploration::sExplorationBookmark bookmark;
			bookmark.name = QString("Grid-%1").arg(evaluated);
			bookmark.formulaId = config.formulaSlot;
			bookmark.juliaMode = config.juliaMode;
			bookmark.juliaC = GetJuliaC(config.formulaSlot);
			bookmark.discoveredBy = config.droneId;
			bookmark.timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);
			results.append(bookmark);

			evaluated++;
			sweepProgress = (evaluated * 100) / totalPoints;
			emit signalSweepProgress(sweepProgress);

			// Increment grid indices (odometer-style)
			int carry = 1;
			for (int d = config.dimensions.size() - 1; d >= 0 && carry; d--)
			{
				indices[d] += carry;
				if (indices[d] >= config.dimensions[d].steps)
				{
					indices[d] = 0;
					carry = 1;
				}
				else
				{
					carry = 0;
				}
			}
			if (carry) done = true;
		}
	}
}

void cExplorationEngine::RunEvolutionarySweep(const exploration::sSweepConfig &config)
{
	if (config.dimensions.isEmpty()) return;

	const int populationSize = 50;
	const int generations = config.maxSamples / populationSize;
	const double mutationRate = 0.1;

	// Initialize random population
	struct Individual
	{
		QList<double> genes;
		double fitness = 0.0;
	};

	QList<Individual> population;
	for (int i = 0; i < populationSize; i++)
	{
		Individual ind;
		for (const exploration::sSweepDimension &dim : config.dimensions)
		{
			double gene = dim.minVal + (dim.maxVal - dim.minVal) * (qrand() / double(RAND_MAX));
			ind.genes.append(gene);
		}
		population.append(ind);
	}

	int evaluated = 0;

	for (int gen = 0; gen < generations && sweepRunning; gen++)
	{
		// Evaluate population
		for (Individual &ind : population)
		{
			// Apply genes as parameters
			for (int d = 0; d < config.dimensions.size(); d++)
			{
				const exploration::sSweepDimension &dim = config.dimensions[d];
				if (dim.isJuliaC)
				{
					CVector3 jc = GetJuliaC(config.formulaSlot);
					if (dim.componentIndex == 0) jc.x = ind.genes[d];
					else if (dim.componentIndex == 1) jc.y = ind.genes[d];
					else jc.z = ind.genes[d];
					SetJuliaC(config.formulaSlot, jc);
				}
			}

			// Fitness placeholder — will be replaced with actual beauty scoring
			ind.fitness = 0.0;
			for (double gene : ind.genes)
			{
				ind.fitness += std::sin(gene * 3.14159) * std::cos(gene * 2.71828);
			}
			ind.fitness = std::abs(ind.fitness);

			evaluated++;
		}

		// Sort by fitness (descending)
		std::sort(population.begin(), population.end(),
			[](const Individual &a, const Individual &b) { return a.fitness > b.fitness; });

		// Save top individual as bookmark
		const Individual &best = population[0];
		exploration::sExplorationBookmark bookmark;
		bookmark.name = QString("Evol-Gen%1-Best").arg(gen);
		bookmark.formulaId = config.formulaSlot;
		bookmark.juliaMode = config.juliaMode;

		CVector3 bestJc(0, 0, 0);
		for (int d = 0; d < config.dimensions.size(); d++)
		{
			if (config.dimensions[d].isJuliaC)
			{
				if (config.dimensions[d].componentIndex == 0) bestJc.x = best.genes[d];
				else if (config.dimensions[d].componentIndex == 1) bestJc.y = best.genes[d];
				else bestJc.z = best.genes[d];
			}
		}
		bookmark.juliaC = bestJc;
		bookmark.score.deVariance = best.fitness;
		bookmark.discoveredBy = config.droneId;
		bookmark.timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);
		results.append(bookmark);

		// Selection: keep top 40%
		int keepCount = populationSize * 4 / 10;
		QList<Individual> parents = population.mid(0, keepCount);

		// Crossover + mutation to fill rest
		population.clear();
		population.append(parents);
		while (population.size() < populationSize)
		{
			int p1 = qrand() % keepCount;
			int p2 = qrand() % keepCount;
			Individual child;
			for (int d = 0; d < config.dimensions.size(); d++)
			{
				// Uniform crossover
				double gene = (qrand() % 2 == 0) ? parents[p1].genes[d] : parents[p2].genes[d];
				// Mutation
				if ((qrand() / double(RAND_MAX)) < mutationRate)
				{
					double range = config.dimensions[d].maxVal - config.dimensions[d].minVal;
					gene += (qrand() / double(RAND_MAX) - 0.5) * range * 0.2;
					gene = qBound(config.dimensions[d].minVal, gene, config.dimensions[d].maxVal);
				}
				child.genes.append(gene);
			}
			population.append(child);
		}

		sweepProgress = (gen * 100) / generations;
		emit signalSweepProgress(sweepProgress);
	}
}

void cExplorationEngine::RunRandomSweep(const exploration::sSweepConfig &config)
{
	if (config.dimensions.isEmpty()) return;

	for (int i = 0; i < config.maxSamples && sweepRunning; i++)
	{
		for (int d = 0; d < config.dimensions.size(); d++)
		{
			const exploration::sSweepDimension &dim = config.dimensions[d];
			double value = dim.minVal + (dim.maxVal - dim.minVal) * (qrand() / double(RAND_MAX));

			if (dim.isJuliaC)
			{
				CVector3 jc = GetJuliaC(config.formulaSlot);
				if (dim.componentIndex == 0) jc.x = value;
				else if (dim.componentIndex == 1) jc.y = value;
				else jc.z = value;
				SetJuliaC(config.formulaSlot, jc);
			}
		}

		exploration::sExplorationBookmark bookmark;
		bookmark.name = QString("Random-%1").arg(i);
		bookmark.formulaId = config.formulaSlot;
		bookmark.juliaMode = config.juliaMode;
		bookmark.juliaC = GetJuliaC(config.formulaSlot);
		bookmark.discoveredBy = config.droneId;
		bookmark.timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);
		results.append(bookmark);

		sweepProgress = ((i + 1) * 100) / config.maxSamples;
		emit signalSweepProgress(sweepProgress);
	}
}

// --- Bookmark Database ---

void cExplorationEngine::SaveBookmark(const exploration::sExplorationBookmark &bookmark)
{
	allBookmarks.append(bookmark);
	ExportBookmarks(bookmarksFilePath);
}

QList<exploration::sExplorationBookmark> cExplorationEngine::LoadBookmarks(int formulaId) const
{
	if (formulaId < 0) return allBookmarks;

	QList<exploration::sExplorationBookmark> filtered;
	for (const exploration::sExplorationBookmark &b : allBookmarks)
	{
		if (b.formulaId == formulaId) filtered.append(b);
	}
	return filtered;
}

void cExplorationEngine::ExportBookmarks(const QString &path) const
{
	QJsonArray arr;
	for (const exploration::sExplorationBookmark &b : allBookmarks)
	{
		arr.append(b.ToJson());
	}

	QDir().mkpath(QFileInfo(path).absolutePath());
	QFile file(path);
	if (file.open(QIODevice::WriteOnly))
	{
		file.write(QJsonDocument(arr).toJson());
		file.close();
	}
}

void cExplorationEngine::ImportBookmarks(const QString &path)
{
	QFile file(path);
	if (!file.exists() || !file.open(QIODevice::ReadOnly)) return;

	QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	file.close();
	if (!doc.isArray()) return;

	QJsonArray arr = doc.array();
	for (const QJsonValue &val : arr)
	{
		allBookmarks.append(exploration::sExplorationBookmark::FromJson(val.toObject()));
	}
}

int cExplorationEngine::BookmarkCount() const
{
	return allBookmarks.size();
}

// --- Beauty Scoring ---

exploration::sBeautyScore cExplorationEngine::ScoreImage(
	const unsigned char *imageData, int width, int height)
{
	exploration::sBeautyScore score;
	int pixels = width * height;
	if (!imageData || pixels == 0) return score;

	score.colorEntropy = ComputeImageEntropy(imageData, pixels);
	score.detailDensity = ComputeEdgeDensity(imageData, width, height);
	score.contrast = ComputeContrast(imageData, pixels);

	return score;
}

double cExplorationEngine::ComputeImageEntropy(const unsigned char *data, int pixels)
{
	// Histogram of luminance values
	int histogram[256] = {};
	for (int i = 0; i < pixels; i++)
	{
		int r = data[i * 3 + 0];
		int g = data[i * 3 + 1];
		int b = data[i * 3 + 2];
		int lum = (r * 299 + g * 587 + b * 114) / 1000;
		histogram[lum]++;
	}

	// Shannon entropy
	double entropy = 0.0;
	for (int i = 0; i < 256; i++)
	{
		if (histogram[i] > 0)
		{
			double p = histogram[i] / static_cast<double>(pixels);
			entropy -= p * std::log2(p);
		}
	}

	return entropy / 8.0; // Normalize to 0-1
}

double cExplorationEngine::ComputeEdgeDensity(
	const unsigned char *data, int width, int height)
{
	// Simplified Sobel edge detection on luminance
	int edgeCount = 0;
	int totalPixels = (width - 2) * (height - 2);
	if (totalPixels <= 0) return 0.0;

	auto lum = [&](int x, int y) -> int {
		int idx = (y * width + x) * 3;
		return (data[idx] * 299 + data[idx + 1] * 587 + data[idx + 2] * 114) / 1000;
	};

	for (int y = 1; y < height - 1; y++)
	{
		for (int x = 1; x < width - 1; x++)
		{
			int gx = -lum(x - 1, y - 1) + lum(x + 1, y - 1) - 2 * lum(x - 1, y)
							 + 2 * lum(x + 1, y) - lum(x - 1, y + 1) + lum(x + 1, y + 1);
			int gy = -lum(x - 1, y - 1) - 2 * lum(x, y - 1) - lum(x + 1, y - 1)
							 + lum(x - 1, y + 1) + 2 * lum(x, y + 1) + lum(x + 1, y + 1);
			int magnitude = std::abs(gx) + std::abs(gy);
			if (magnitude > 30) edgeCount++;
		}
	}

	return static_cast<double>(edgeCount) / totalPixels;
}

double cExplorationEngine::ComputeContrast(const unsigned char *data, int pixels)
{
	if (pixels == 0) return 0.0;

	int minLum = 255;
	int maxLum = 0;
	long long sumLum = 0;

	for (int i = 0; i < pixels; i++)
	{
		int r = data[i * 3 + 0];
		int g = data[i * 3 + 1];
		int b = data[i * 3 + 2];
		int lum = (r * 299 + g * 587 + b * 114) / 1000;
		if (lum < minLum) minLum = lum;
		if (lum > maxLum) maxLum = lum;
		sumLum += lum;
	}

	double range = (maxLum - minLum) / 255.0;
	return range;
}

// --- Slice Distance ---

double cExplorationEngine::SliceDistance(
	const CVector3 &point, const exploration::sSliceConfig &config)
{
	double sliceDist = 0.0;

	switch (config.mode)
	{
		case exploration::sSliceConfig::slicePlanarXY:
			sliceDist = std::abs(point.z - config.planeOffset);
			break;
		case exploration::sSliceConfig::slicePlanarXZ:
			sliceDist = std::abs(point.y - config.planeOffset);
			break;
		case exploration::sSliceConfig::slicePlanarYZ:
			sliceDist = std::abs(point.x - config.planeOffset);
			break;
		case exploration::sSliceConfig::sliceArbitrary:
		{
			CVector3 diff = point - config.origin;
			sliceDist = std::abs(diff.Dot(config.normal));
			break;
		}
		case exploration::sSliceConfig::sliceRadial:
		{
			double r = std::sqrt(point.x * point.x + point.y * point.y);
			sliceDist = std::abs(r - config.radius);
			break;
		}
		case exploration::sSliceConfig::sliceSpherical:
		{
			sliceDist = std::abs(point.Length() - config.radius);
			break;
		}
	}

	return sliceDist - config.thickness;
}

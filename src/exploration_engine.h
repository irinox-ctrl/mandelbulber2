/**
 * 3x3lion Exploration Engine
 * Founded by Iri and Devin
 *
 * Automated parameter sweep and beauty scoring for bot-driven fractal exploration.
 * This is the core infrastructure that drones and bots use to discover the most
 * beautiful views in fractal space.
 */

#ifndef MANDELBULBER2_SRC_EXPLORATION_ENGINE_H_
#define MANDELBULBER2_SRC_EXPLORATION_ENGINE_H_

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QString>

#include "algebra.hpp"

class cParameterContainer;
class cFractalContainer;

namespace exploration
{

// Beauty score components for ranking fractal views
struct sBeautyScore
{
	double deVariance = 0.0;      // geometric complexity (DE field variance)
	double colorEntropy = 0.0;    // color richness (histogram entropy)
	double detailDensity = 0.0;   // fine detail per pixel (edge density)
	double contrast = 0.0;        // dynamic range of the render
	double uniqueness = 0.0;      // distance from known bookmarks in param space
	double symmetryScore = 0.0;   // detected symmetry axes
	double composition = 0.0;     // rule-of-thirds alignment

	double Total() const
	{
		return 0.20 * deVariance + 0.15 * colorEntropy + 0.20 * detailDensity + 0.10 * contrast
					 + 0.15 * uniqueness + 0.10 * symmetryScore + 0.10 * composition;
	}

	QJsonObject ToJson() const
	{
		QJsonObject obj;
		obj["de_variance"] = deVariance;
		obj["color_entropy"] = colorEntropy;
		obj["detail_density"] = detailDensity;
		obj["contrast"] = contrast;
		obj["uniqueness"] = uniqueness;
		obj["symmetry_score"] = symmetryScore;
		obj["composition"] = composition;
		obj["total"] = Total();
		return obj;
	}

	static sBeautyScore FromJson(const QJsonObject &obj)
	{
		sBeautyScore s;
		s.deVariance = obj["de_variance"].toDouble();
		s.colorEntropy = obj["color_entropy"].toDouble();
		s.detailDensity = obj["detail_density"].toDouble();
		s.contrast = obj["contrast"].toDouble();
		s.uniqueness = obj["uniqueness"].toDouble();
		s.symmetryScore = obj["symmetry_score"].toDouble();
		s.composition = obj["composition"].toDouble();
		return s;
	}
};

// A discovered point of interest
struct sExplorationBookmark
{
	QString name;
	int formulaId = 0;
	bool juliaMode = false;
	CVector3 juliaC;
	CVector3 camera;
	CVector3 target;
	CVector3 rotation;
	double distance = 0.0;
	sBeautyScore score;
	QString discoveredBy;  // drone ID
	QString timestamp;
	QJsonObject formulaParams;  // formula-specific parameters at discovery

	QJsonObject ToJson() const
	{
		QJsonObject obj;
		obj["name"] = name;
		obj["formula_id"] = formulaId;
		obj["julia_mode"] = juliaMode;
		obj["julia_cx"] = juliaC.x;
		obj["julia_cy"] = juliaC.y;
		obj["julia_cz"] = juliaC.z;
		obj["cam_x"] = camera.x;
		obj["cam_y"] = camera.y;
		obj["cam_z"] = camera.z;
		obj["tgt_x"] = target.x;
		obj["tgt_y"] = target.y;
		obj["tgt_z"] = target.z;
		obj["rot_x"] = rotation.x;
		obj["rot_y"] = rotation.y;
		obj["rot_z"] = rotation.z;
		obj["distance"] = distance;
		obj["score"] = score.ToJson();
		obj["discovered_by"] = discoveredBy;
		obj["timestamp"] = timestamp;
		obj["formula_params"] = formulaParams;
		return obj;
	}

	static sExplorationBookmark FromJson(const QJsonObject &obj)
	{
		sExplorationBookmark b;
		b.name = obj["name"].toString();
		b.formulaId = obj["formula_id"].toInt();
		b.juliaMode = obj["julia_mode"].toBool();
		b.juliaC = CVector3(
			obj["julia_cx"].toDouble(), obj["julia_cy"].toDouble(), obj["julia_cz"].toDouble());
		b.camera =
			CVector3(obj["cam_x"].toDouble(), obj["cam_y"].toDouble(), obj["cam_z"].toDouble());
		b.target =
			CVector3(obj["tgt_x"].toDouble(), obj["tgt_y"].toDouble(), obj["tgt_z"].toDouble());
		b.rotation =
			CVector3(obj["rot_x"].toDouble(), obj["rot_y"].toDouble(), obj["rot_z"].toDouble());
		b.distance = obj["distance"].toDouble();
		b.score = sBeautyScore::FromJson(obj["score"].toObject());
		b.discoveredBy = obj["discovered_by"].toString();
		b.timestamp = obj["timestamp"].toString();
		b.formulaParams = obj["formula_params"].toObject();
		return b;
	}
};

// Sweep strategy types
enum eSweepStrategy
{
	sweepGrid = 0,          // exhaustive grid scan
	sweepLatinHypercube,    // space-filling sample
	sweepEvolutionary,      // genetic algorithm
	sweepGradientAscent,    // follow beauty gradient
	sweepBayesian,          // Gaussian process optimization
	sweepRandom             // random sampling (baseline)
};

// A single parameter dimension to sweep
struct sSweepDimension
{
	QString paramName;
	double minVal = 0.0;
	double maxVal = 1.0;
	int steps = 10;
	bool isJuliaC = false;  // special flag for julia_c components
	int componentIndex = 0; // 0=x, 1=y, 2=z for vector params
};

// Configuration for a sweep job
struct sSweepConfig
{
	int formulaSlot = 0;              // which formula slot (0-8)
	bool juliaMode = false;           // standard or julia group
	eSweepStrategy strategy = sweepGrid;
	QList<sSweepDimension> dimensions;
	double beautyThreshold = 0.5;     // minimum score to save bookmark
	int maxSamples = 1000;            // maximum evaluations
	int renderWidth = 256;            // preview render resolution
	int renderHeight = 256;
	QString droneId = "local";

	QJsonObject ToJson() const
	{
		QJsonObject obj;
		obj["formula_slot"] = formulaSlot;
		obj["julia_mode"] = juliaMode;
		obj["strategy"] = static_cast<int>(strategy);
		obj["beauty_threshold"] = beautyThreshold;
		obj["max_samples"] = maxSamples;
		obj["render_width"] = renderWidth;
		obj["render_height"] = renderHeight;
		obj["drone_id"] = droneId;

		QJsonArray dims;
		for (const sSweepDimension &d : dimensions)
		{
			QJsonObject dObj;
			dObj["param"] = d.paramName;
			dObj["min"] = d.minVal;
			dObj["max"] = d.maxVal;
			dObj["steps"] = d.steps;
			dObj["is_julia_c"] = d.isJuliaC;
			dObj["component"] = d.componentIndex;
			dims.append(dObj);
		}
		obj["dimensions"] = dims;
		return obj;
	}
};

// Slice configuration
struct sSliceConfig
{
	enum eSliceMode
	{
		slicePlanarXY = 0,
		slicePlanarXZ,
		slicePlanarYZ,
		sliceArbitrary,
		sliceRadial,
		sliceSpherical
	};

	eSliceMode mode = slicePlanarXY;
	double planeOffset = 0.0;       // position of slice plane
	double thickness = 0.01;         // slice thickness
	CVector3 origin;                 // for arbitrary mode
	CVector3 normal;                 // for arbitrary mode
	double radius = 1.0;            // for radial/spherical modes

	// Animation sweep
	double sweepStart = -2.0;
	double sweepEnd = 2.0;
	int sweepSteps = 100;

	QJsonObject ToJson() const
	{
		QJsonObject obj;
		obj["mode"] = static_cast<int>(mode);
		obj["plane_offset"] = planeOffset;
		obj["thickness"] = thickness;
		obj["origin_x"] = origin.x;
		obj["origin_y"] = origin.y;
		obj["origin_z"] = origin.z;
		obj["normal_x"] = normal.x;
		obj["normal_y"] = normal.y;
		obj["normal_z"] = normal.z;
		obj["radius"] = radius;
		obj["sweep_start"] = sweepStart;
		obj["sweep_end"] = sweepEnd;
		obj["sweep_steps"] = sweepSteps;
		return obj;
	}
};

} // namespace exploration

// The main exploration engine — coordinates sweep jobs and scores results
class cExplorationEngine : public QObject
{
	Q_OBJECT

public:
	explicit cExplorationEngine(QObject *parent = nullptr);
	~cExplorationEngine() override;

	// Configure the engine with current fractal parameters
	void SetParameters(std::shared_ptr<cParameterContainer> params,
		std::shared_ptr<cFractalContainer> fractalParams);

	// Julia group management
	void SetJuliaMode(int formulaSlot, bool enabled);
	void SetJuliaC(int formulaSlot, const CVector3 &juliaC);
	bool GetJuliaMode(int formulaSlot) const;
	CVector3 GetJuliaC(int formulaSlot) const;

	// Sweep operations
	void StartSweep(const exploration::sSweepConfig &config);
	void StopSweep();
	bool IsSweepRunning() const;
	int GetSweepProgress() const; // 0-100
	QList<exploration::sExplorationBookmark> GetSweepResults() const;

	// Bookmark database
	void SaveBookmark(const exploration::sExplorationBookmark &bookmark);
	QList<exploration::sExplorationBookmark> LoadBookmarks(int formulaId = -1) const;
	void ExportBookmarks(const QString &path) const;
	void ImportBookmarks(const QString &path);
	int BookmarkCount() const;

	// Beauty scoring
	static exploration::sBeautyScore ScoreImage(const unsigned char *imageData, int width, int height);

	// Slice computation
	static double SliceDistance(const CVector3 &point, const exploration::sSliceConfig &config);

signals:
	void signalSweepProgress(int percent);
	void signalSweepComplete(int bookmarksFound);
	void signalBookmarkDiscovered(const exploration::sExplorationBookmark &bookmark);

private:
	void RunGridSweep(const exploration::sSweepConfig &config);
	void RunEvolutionarySweep(const exploration::sSweepConfig &config);
	void RunRandomSweep(const exploration::sSweepConfig &config);

	static double ComputeImageEntropy(const unsigned char *data, int pixels);
	static double ComputeEdgeDensity(const unsigned char *data, int width, int height);
	static double ComputeContrast(const unsigned char *data, int pixels);

	std::shared_ptr<cParameterContainer> params;
	std::shared_ptr<cFractalContainer> fractalParams;
	QList<exploration::sExplorationBookmark> results;
	QList<exploration::sExplorationBookmark> allBookmarks;
	bool sweepRunning = false;
	int sweepProgress = 0;
	QString bookmarksFilePath;
};

#endif /* MANDELBULBER2_SRC_EXPLORATION_ENGINE_H_ */

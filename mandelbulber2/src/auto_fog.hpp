/**
 * Mandelbulber v2 — Universal Auto Fog System
 *
 * This module analyzes the scene's empirical iteration distribution
 * and automatically tunes fog parameters using scene percentiles plus
 * light fractal-class modifiers (measure first, then adjust).
 *
 * Safe Integration: NO new sParamRender fields, NO OpenCL changes.
 */

#ifndef MANDELBULBER2_SRC_AUTO_FOG_HPP_
#define MANDELBULBER2_SRC_AUTO_FOG_HPP_

#include <vector>
#include <algorithm>
#include <cmath>
#include <memory>

#include <QString>

// Forward declarations
struct sParamRender;
class cNineFractals;
struct sRenderData;
struct sDistanceIn;
struct sDistanceOut;
class cParameterContainer;

namespace autoFog
{

enum class eAutoFogQuality
{
	Preview = 0,
	Balanced = 1,
	Cinematic = 2
};

enum class eAutoFogTuneMode
{
	IterationOnly,
	DistanceOnly,
	BasicOnly,
	All
};

struct sFogProfileModifier
{
	float trimMul = 1.0f;
	float highMul = 1.0f;
	float opacityMul = 1.0f;
	float colorSpreadMul = 1.0f;
	float trimHighExtra = 0.0f;
};

int ProbeGridResForQuality(eAutoFogQuality quality);
sFogProfileModifier DetectFractalModifiers(const cNineFractals *fractal, QString *classNameOut = nullptr);

// ═════════════════════════════════════════════════════════════════════════════
// EMPIRICAL SCENE PROFILE
// ═════════════════════════════════════════════════════════════════════════════

struct sIterationProfile
{
	// Percentiles of iteration count across probed rays
	float p01 = 0.0f;   // 1st percentile (near-minimum)
	float p05 = 0.0f;   // 5th percentile
	float p10 = 0.0f;   // 10th percentile
	float p25 = 0.0f;   // 25th percentile (Q1)
	float p50 = 0.0f;   // 50th percentile (median)
	float p75 = 0.0f;   // 75th percentile (Q3)
	float p90 = 0.0f;   // 90th percentile
	float p95 = 0.0f;   // 95th percentile
	float p99 = 0.0f;   // 99th percentile (near-maximum without extreme outliers)

	// Distribution shape
	float range = 0.0f;   // p95 - p05 (robust spread)
	float iqr = 0.0f;     // p75 - p25 (interquartile range)

	// Scene context
	float meanStep = 0.0f;    // Average raymarching step from probing
	float medianStep = 0.0f;  // Median step
	float meanDepth = 0.0f;   // Average ray depth (distance from camera)
	float hitRate = 0.0f;     // Fraction of rays that hit the surface [0..1]
	float meanStepHits = 0.0f;   // Average step for hit rays only
	float medianStepHits = 0.0f; // Median step for hit rays only
	float meanDepthHits = 0.0f;  // Average depth for hit rays only
	int hitCount = 0;            // Number of hit rays
	int numSamples = 0;       // Total number of probed samples

	// Effective N for IterOpacity (handles boolean mode discrepancy)
	float effectiveN = 250.0f;

	bool valid = false;
};

void WriteAutoFogResults(std::shared_ptr<cParameterContainer> par, const sParamRender &renderParams,
	eAutoFogTuneMode mode, bool enableTunedTypes = true);
QString FormatAutoFogResultLabel(const sIterationProfile &prof, const QString &className);

// Single probed sample point along a ray
struct sProbeSample
{
	float iters = 0.0f;
	float step = 0.0f;
	float distance = 0.0f;
	float distThresh = 0.0f;
	float depth = 0.0f;
	bool hit = false;
};

// ═════════════════════════════════════════════════════════════════════════════
// MAIN CLASS
// ═════════════════════════════════════════════════════════════════════════════

class cAutoFog
{
public:
	cAutoFog();
	~cAutoFog() = default;

	// Main entry: tune fog types. Returns false on failure.
	bool AutoTuneAll(sParamRender *params, const cNineFractals *fractal, sRenderData *data,
		eAutoFogQuality quality = eAutoFogQuality::Balanced,
		eAutoFogTuneMode mode = eAutoFogTuneMode::All);

	// Individual tuners
	bool AutoTuneIterationFog(sParamRender *params, const cNineFractals *fractal, sRenderData *data);
	bool AutoTuneDistanceFog(sParamRender *params, const cNineFractals *fractal, sRenderData *data);
	bool AutoTuneBasicFog(sParamRender *params, const cNineFractals *fractal, sRenderData *data);

	// Auto-detect optimal N, formula_maxiter, and bailout from scene probe data.
	// Returns suggested values via the out-parameters. Does NOT modify anything.
	// Call this AFTER AutoTuneAll (or AutoTuneIterationFog) so probe data is fresh.
	struct sAutoDetectResult
	{
		int suggestedN = 250;
		int suggestedFormulaMaxiter = 250;
		double suggestedBailout = 100.0;
		bool valid = false;
	};
	sAutoDetectResult AutoDetectIterationsAndBailout(const sParamRender *params, const cNineFractals *fractal, sRenderData *data);

	// Getters for diagnostics
	const sIterationProfile &GetIterationProfile() const { return profile; }
	const QString &GetLastFractalClassName() const { return lastFractalClassName; }
	const sFogProfileModifier &GetLastModifier() const { return lastModifier; }

	// Post-process: apply user fine-tune biases to calculated values
	void ApplyFineTuneBiases(sParamRender *params) const;

	// Frame-to-frame smoothing to prevent animation flicker
	// alpha = 0.0 = no smoothing, 1.0 = full hold
	void SmoothParams(sParamRender *params, float alpha);

	// Reset smoothing state
	void ResetSmoothing();

	// Scene probing — simulates actual raymarching to collect empirical data
	sIterationProfile ProbeScene(const sParamRender *params,
		const cNineFractals *fractal, sRenderData *data, int gridRes);

	// Build profile from raw samples
	sIterationProfile BuildProfile(const std::vector<sProbeSample> &samples, float effectiveN);

	// Get raw samples from last probe (for external simulation/validation)
	const std::vector<sProbeSample> &GetLastSamples() const { return lastSamples; }

private:

	// Parameter calculators
	void CalculateIterationFogUniversal(sParamRender *params, const sIterationProfile &prof,
		const sFogProfileModifier &mod);
	void CalculateDistanceFogUniversal(sParamRender *params, const sIterationProfile &prof);
	void CalculateBasicFogUniversal(sParamRender *params, const sIterationProfile &prof);

	// Helpers
	float ComputeEffectiveN(const sParamRender *params, const cNineFractals *fractal) const;

	sIterationProfile profile;
	std::vector<sProbeSample> lastSamples;  // retained for exact opacity calculation
	QString lastFractalClassName;
	sFogProfileModifier lastModifier;

	// Smoothing state
	bool hasPrevValues = false;
	double prevIterOpacity = -1.0;
	float prevIterTrim = -1.0f;
	float prevIterTrimHigh = -1.0f;
	float prevIterC1Max = -1.0f;
	float prevIterC2Max = -1.0f;
	float prevIterBoost = -1.0f;
	double prevDistFactor = -1.0;
	double prevDistDensity = -1.0;
	double prevBasicVisibility = -1.0;
};

} // namespace autoFog

#endif

/**
 * Mandelbulber v2 — Universal Auto Fog Implementation
 *
 * NO presets, NO fractal-type detection, NO heuristics.
 * Purely empirical: probes the scene, computes percentiles,
 * derives parameters mathematically.
 */

#include "auto_fog.hpp"
#include "fractparams.hpp"
#include "nine_fractals.hpp"
#include "render_data.hpp"
#include "calculate_distance.hpp"
#include "algebra.hpp"
#include "projection_3d.hpp"
#include "camera_target.hpp"
#include <QtGlobal>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDir>

namespace autoFog
{

// ═════════════════════════════════════════════════════════════════════════════
// FILE LOGGER — writes every auto-fog step to ~/.mandelbulber/autofog_debug.log
// ═════════════════════════════════════════════════════════════════════════════

static void WriteAutoFogLog(const QString &message)
{
	QString logDir = QDir::homePath() + "/.mandelbulber";
	QDir().mkpath(logDir);
	QString logPath = logDir + "/autofog_debug.log";
	QFile file(logPath);
	if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
	{
		QTextStream stream(&file);
		QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
		stream << "[" << timestamp << "] " << message << "\n";
	}
}

// ═════════════════════════════════════════════════════════════════════════════
// CONSTRUCTOR
// ═════════════════════════════════════════════════════════════════════════════

cAutoFog::cAutoFog()
{
	profile.valid = false;
}

void cAutoFog::ResetSmoothing()
{
	hasPrevValues = false;
	prevIterOpacity = -1.0;
	prevIterTrim = -1.0f;
	prevIterTrimHigh = -1.0f;
	prevIterC1Max = -1.0f;
	prevIterC2Max = -1.0f;
	prevIterBoost = -1.0f;
	prevDistFactor = -1.0;
	prevDistDensity = -1.0;
	prevBasicVisibility = -1.0;
}

// ═════════════════════════════════════════════════════════════════════════════
// SCENE PROBING
// ═════════════════════════════════════════════════════════════════════════════

/**
 * Simulates actual raymarching over a stratified grid of rays.
 * Collects ALL sample points (hits AND misses) with their true step sizes.
 * No random dithering — we want reproducible statistics.
 */
sIterationProfile cAutoFog::ProbeScene(const sParamRender *params,
	const cNineFractals *fractal, sRenderData *data, int gridRes)
{
	sIterationProfile prof{};
	if (!params || !fractal || gridRes <= 0) return prof;

	std::vector<sProbeSample> samples;
	samples.reserve(gridRes * gridRes * 50);

	// Build camera rotation matrix exactly like cRenderWorker::PrepareMainVectors()
	cCameraTarget cameraTarget(params->camera, params->target, params->topVector);
	CVector3 viewAngle = cameraTarget.GetRotation();

	CRotationMatrix mRot;
	mRot.RotateZ(viewAngle.x); // yaw
	mRot.RotateX(viewAngle.y); // pitch
	mRot.RotateY(viewAngle.z); // roll
	mRot.RotateZ(-params->sweetSpotHAngle);
	mRot.RotateX(params->sweetSpotVAngle);

	// Aspect ratio for image-space sampling
	double aspectRatio = 1.0;
	if (params->imageHeight > 0)
		aspectRatio = double(params->imageWidth) / double(params->imageHeight);
	if (params->perspectiveType == params::perspEquirectangular) aspectRatio = 2.0;

	int hitCount = 0;
	int totalRays = 0;

	for (int gy = 0; gy < gridRes; gy++)
	{
		for (int gx = 0; gx < gridRes; gx++)
		{
			totalRays++;

			// Normalized screen coordinates [-1, 1]
			double nx = (double(gx) + 0.5) / double(gridRes) * 2.0 - 1.0;
			double ny = (double(gy) + 0.5) / double(gridRes) * 2.0 - 1.0;
			ny /= aspectRatio;

			// Convert to world direction using same function as real renderer
			CVector2<double> normalizedPoint(nx, ny);
			CVector3 direction = CalculateViewVector(normalizedPoint, params->fov,
				params->perspectiveType, mRot);

			double scan = 0.0;
			double step = 0.0;

			for (int i = 0; i < params->maxRaymarchingSteps && scan < params->viewDistanceMax; i++)
			{
				CVector3 point = params->camera + direction * scan;
				double distThresh = 0.0;

				// Replicate CalcDistThresh logic inline to avoid needing render_worker methods
				// NOTE: params->resolution is often 0 at this point because the renderer sets it
				// later (1.0 / imageHeight). Compute it ourselves if needed.
				double resolution = params->resolution;
				if (resolution <= 0.0 && params->imageHeight > 0)
					resolution = 1.0 / double(params->imageHeight);

				if (params->iterThreshMode)
				{
					distThresh = (params->camera - point).Length()
									 * resolution * params->fov;
				}
				else
				{
					if (params->constantDEThreshold)
						distThresh = params->DEThresh;
					else
						distThresh = (params->camera - point).Length()
										 * resolution * params->fov / params->detailLevel;
				}
				if (params->perspectiveType == params::perspEquirectangular) distThresh *= 0.5;
				if (params->advancedQuality)
				{
					if (distThresh > params->detailSizeMax) distThresh = params->detailSizeMax;
					if (distThresh < params->detailSizeMin) distThresh = params->detailSizeMin;
				}
				if (data)
					distThresh /= data->reduceDetail;

				sDistanceIn distanceIn(point, distThresh, false);
				sDistanceOut distanceOut;
				double dist = CalculateDistance(*params, *fractal, distanceIn, &distanceOut, data);

				// Store EVERY sample, including misses
				samples.push_back({
					float(distanceOut.iters),
					float(step),
					float(dist),
					float(distThresh),
					float(scan),
					dist < distThresh
				});

				if (dist < distThresh)
				{
					hitCount++;
					break;
				}

				// Compute next step EXACTLY like the real raymarching loop
				// (but without random dithering for reproducibility)
				if (params->interiorMode)
					step = (dist - 0.8 * distThresh) * params->DEFactor;
				else
					step = (dist - 0.5 * distThresh) * params->DEFactor;

				if (params->advancedQuality)
				{
					if (step > params->absMaxMarchingStep) step = params->absMaxMarchingStep;
					if (step < params->absMinMarchingStep) step = params->absMinMarchingStep;
					if (distThresh > params->absMinMarchingStep)
					{
						if (step > params->relMaxMarchingStep * distThresh)
							step = params->relMaxMarchingStep * distThresh;
						if (step < params->relMinMarchingStep * distThresh)
							step = params->relMinMarchingStep * distThresh;
					}
				}
				else
				{
					if (step > 3.0) step = 3.0;
				}

				scan += step;
			}
		}
	}

	float effectiveN = ComputeEffectiveN(params, fractal);
	prof = BuildProfile(samples, effectiveN);
	prof.hitRate = (totalRays > 0) ? float(hitCount) / float(totalRays) : 0.0f;

	lastSamples = std::move(samples);
	return prof;
}

// ═════════════════════════════════════════════════════════════════════════════
// PROFILE BUILDING
// ═════════════════════════════════════════════════════════════════════════════

sIterationProfile cAutoFog::BuildProfile(const std::vector<sProbeSample> &samples, float effectiveN)
{
	sIterationProfile prof{};
	prof.numSamples = int(samples.size());
	prof.effectiveN = effectiveN;

	if (samples.empty())
	{
		prof.valid = false;
		return prof;
	}

	// Extract iteration values
	std::vector<float> iters;
	iters.reserve(samples.size());
	for (const auto &s : samples) iters.push_back(s.iters);
	std::sort(iters.begin(), iters.end());

	auto percentile = [&](float p) -> float {
		if (iters.empty()) return 0.0f;
		size_t idx = size_t(p * float(iters.size()));
		if (idx >= iters.size()) idx = iters.size() - 1;
		return iters[idx];
	};

	prof.p01 = percentile(0.01f);
	prof.p05 = percentile(0.05f);
	prof.p10 = percentile(0.10f);
	prof.p25 = percentile(0.25f);
	prof.p50 = percentile(0.50f);
	prof.p75 = percentile(0.75f);
	prof.p90 = percentile(0.90f);
	prof.p95 = percentile(0.95f);
	prof.p99 = percentile(0.99f);
	prof.range = prof.p95 - prof.p05;
	prof.iqr = prof.p75 - prof.p25;

	// Step statistics — compute over HIT samples only for camera-relevant values
	std::vector<float> steps;
	steps.reserve(samples.size());
	float stepSum = 0.0f;
	float depthSum = 0.0f;
	float stepSumHits = 0.0f;
	float depthSumHits = 0.0f;
	int hitCount = 0;
	for (const auto &s : samples)
	{
		steps.push_back(s.step);
		stepSum += s.step;
		depthSum += s.depth;
		if (s.hit)
		{
			stepSumHits += s.step;
			depthSumHits += s.depth;
			hitCount++;
		}
	}
	std::sort(steps.begin(), steps.end());
	prof.meanStep = stepSum / float(samples.size());
	prof.medianStep = steps.empty() ? 0.0f : steps[steps.size() / 2];
	prof.meanDepth = depthSum / float(samples.size());

	// Camera-centric statistics: only hits matter for fog placement
	prof.meanStepHits = (hitCount > 0) ? stepSumHits / float(hitCount) : prof.meanStep;
	prof.meanDepthHits = (hitCount > 0) ? depthSumHits / float(hitCount) : prof.meanDepth;
	prof.hitCount = hitCount;

	// Median step over hits only
	if (hitCount > 0)
	{
		std::vector<float> hitSteps;
		hitSteps.reserve(hitCount);
		for (const auto &s : samples)
			if (s.hit) hitSteps.push_back(s.step);
		std::sort(hitSteps.begin(), hitSteps.end());
		prof.medianStepHits = hitSteps[hitSteps.size() / 2];
	}
	else
	{
		prof.medianStepHits = prof.medianStep;
	}

	prof.valid = true;
	return prof;
}

// ═════════════════════════════════════════════════════════════════════════════
// EFFECTIVE N (handles boolean mode discrepancy)
// ═════════════════════════════════════════════════════════════════════════════

float cAutoFog::ComputeEffectiveN(const sParamRender *params, const cNineFractals *fractal) const
{
	if (!params || !fractal) return 250.0f;

	float effectiveN = float(params->N);

	// In boolean mode, each formula can have its own maxiter.
	// IterOpacity uses params->N as denominator, but the actual
	// iteration loop uses formulaMaxiter. Use the maximum to avoid
	// underestimating the fog density.
	if (params->booleanOperatorsEnabled)
	{
		for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
		{
			if (fractal->GetFractal(i)->formula != fractal::none)
			{
				effectiveN = std::max(effectiveN, float(fractal->GetFormulaMaxiter(i)));
			}
		}
	}

	return std::max(effectiveN, 1.0f);
}

// ═════════════════════════════════════════════════════════════════════════════
// UNIVERSAL PARAMETER CALCULATORS
// ═════════════════════════════════════════════════════════════════════════════

void cAutoFog::CalculateIterationFogUniversal(sParamRender *params, const sIterationProfile &prof)
{
	if (!params || !prof.valid) return;

	float N = prof.effectiveN;
	if (N <= 0.0f) N = 250.0f;

	// ── TRIM: where does fog begin? ──
	// Use p05 as the "typical minimum" — 95% of samples have higher iters.
	// Multiply by 0.5 so fog starts BEFORE the 5th percentile.
	float trim = prof.p05 * 0.5f;
	trim = std::max(trim, 1.0f);
	trim = std::min(trim, N * 0.3f);  // never more than 30% of N

	// For very narrow distributions, pull trim closer to the absolute minimum
	if (prof.range < 3.0f)
	{
		trim = std::max(prof.p01 * 0.8f, 1.0f);
	}

	// ── TRIM HIGH: where does fog peak? ──
	// Use p95 with a small margin. This captures the "tail" of the distribution.
	float trimHigh = prof.p95 * 1.05f;
	trimHigh = std::min(trimHigh, N);
	trimHigh = std::max(trimHigh, trim + 2.0f);

	// For narrow distributions, extend to p99
	if (prof.range < 3.0f)
	{
		trimHigh = std::min(prof.p99 * 1.1f, N);
		trimHigh = std::max(trimHigh, trim + 2.0f);
	}

	// ── COLOR TRANSITIONS: always at 1/3 and 2/3 of the range ──
	float range = trimHigh - trim;
	float c1 = trim + range * 0.33f;
	float c2 = trim + range * 0.66f;
	c1 = std::min(c1, N);
	c2 = std::min(c2, N);
	c1 = std::max(c1, trim + 0.5f);
	c2 = std::max(c2, c1 + 0.5f);

	// ── OPACITY: calibrated formula from simulator ──
	// Derived by fitting to exact IterOpacity() simulation results:
	//   Mandelbulb (N=250, step=0.01)    → ideal opacitySp ≈ 3.2
	//   Mandelbulb deep zoom (step=1e-5) → ideal opacitySp ≈ 94
	//   Menger Sponge (N=15, step=0.005) → ideal opacitySp ≈ 0.5
	//
	// Formula: opacitySp = 0.0047 * N^0.776 * medianStep^(-0.489)
	// This captures the non-linear relationship between N, step size,
	// and the actual accumulated fog visibility.

	float medianStep = prof.medianStepHits > 1e-6f ? prof.medianStepHits : prof.medianStep;
	if (medianStep < 1e-6f) medianStep = 0.01f;
	// Clamp medianStep to avoid extreme values from numerical noise
	if (medianStep > 1.0f) medianStep = 1.0f;

	float opacity = 0.0047f * std::pow(N, 0.776f) * std::pow(medianStep, -0.489f);

	// ── ITERATION SPREAD COMPENSATION ──
	// Narrow iteration distributions (e.g. Menger where iters quickly saturate)
	// produce denser fog per unit opacity. Widen the effective range to
	// prevent under-estimation for these fractals.
	float iterSpread = prof.p95 - prof.p05;
	float spreadRatio = iterSpread / N;
	if (spreadRatio > 0.1f && spreadRatio < 0.3f)
	{
		// Moderate spread: slight boost
		opacity *= 1.0f + (0.3f - spreadRatio);
	}
	else if (spreadRatio <= 0.1f)
	{
		// Very narrow spread (Menger-like): stronger boost needed
		opacity *= 2.0f;
	}

	// DEBUG
	qDebug() << "AUTOFOG: N=" << N << "trim=" << trim << "trimHigh=" << trimHigh
				 << "medianStep=" << medianStep << "spreadRatio=" << spreadRatio
				 << "opacity=" << opacity;

	// Safe clamps — never invisible, never blow out
	opacity = std::max(opacity, 0.1f);
	opacity = std::min(opacity, 5000.0f);
	opacity = std::max(opacity, 0.01f);
	opacity = std::min(opacity, 500.0f);

	// ── BRIGHTNESS BOOST ──
	// When the iteration range is small (uniform fog), boost visibility.
	float rangeRatio = range / N;
	float boost = 1.0f + (1.0f - rangeRatio) * 0.5f;
	boost = std::min(boost, 3.0f);

	// Apply pure calculated values (biases applied as post-process in AutoTuneAll)
	params->iterFogOpacityTrim = trim;
	params->iterFogOpacityTrimHigh = trimHigh;
	params->iterFogColor1Maxiter = c1;
	params->iterFogColor2Maxiter = c2;
	params->iterFogOpacity = double(opacity);
	params->iterFogBrightnessBoost = boost;
}

// ═════════════════════════════════════════════════════════════════════════════
// POST-PROCESS: apply user fine-tune biases to calculated values
// ═════════════════════════════════════════════════════════════════════════════

void cAutoFog::ApplyFineTuneBiases(sParamRender *params) const
{
	if (!params) return;

	float N = std::max(params->N, 1);

	// Trim bias
	float trim = params->iterFogOpacityTrim + params->autoFogTrimBias;
	trim = std::max(trim, 0.0f);
	trim = std::min(trim, N - 1.0f);

	// TrimHigh bias
	float trimHigh = params->iterFogOpacityTrimHigh + params->autoFogTrimHighBias;
	trimHigh = std::max(trimHigh, trim + 2.0f);
	trimHigh = std::min(trimHigh, N);

	// Color spread
	float range = trimHigh - trim;
	float c1 = trim + range * 0.33f * params->autoFogColorSpread;
	float c2 = trim + range * 0.66f * params->autoFogColorSpread;
	c1 = std::min(c1, N);
	c2 = std::min(c2, N);
	c1 = std::max(c1, trim + 0.5f);
	c2 = std::max(c2, c1 + 0.5f);

	// Boost scale
	float boost = params->iterFogBrightnessBoost * params->autoFogBoostScale;
	boost = std::max(boost, 0.0f);
	boost = std::min(boost, 5.0f);

	params->iterFogOpacityTrim = trim;
	params->iterFogOpacityTrimHigh = trimHigh;
	params->iterFogColor1Maxiter = c1;
	params->iterFogColor2Maxiter = c2;
	params->iterFogBrightnessBoost = boost;
}


// ═════════════════════════════════════════════════════════════════════════════
// DISTANCE FOG (simplified universal approach)
// ═════════════════════════════════════════════════════════════════════════════

void cAutoFog::CalculateDistanceFogUniversal(sParamRender *params, const sIterationProfile &prof)
{
	if (!params || !prof.valid) return;

	float sceneScale = std::max(float(params->viewDistanceMax), 1e-6f);

	// Distance factor: based on typical step size for HIT rays (camera-relevant)
	float factor = prof.medianStepHits * 2.5f;
	if (factor < 1e-6f) factor = prof.meanStepHits * 2.5f;
	if (factor < 1e-6f) factor = prof.medianStep * 2.5f;
	if (factor < 1e-6f) factor = prof.meanStep * 2.5f;
	if (factor < 1e-6f) factor = sceneScale * 0.001f;
	params->volFogDistanceFactor = double(factor);
	params->volFogDistanceFactor = std::max(params->volFogDistanceFactor, 1e-9);

	// Offset: small fraction of factor
	float offset = factor * 0.5f;
	params->volFogDistanceFromSurface = double(offset);
	params->volFogDistanceFromSurface = std::max(params->volFogDistanceFromSurface, 1e-15);

	// Density: scale inversely with scene scale so close-ups don't blow out
	float density = 0.5f;
	if (sceneScale > 1e-6f)
	{
		density = 0.25f * std::sqrt(1.0f / sceneScale);
		density = std::min(density, 2.0f);
		density = std::max(density, 0.05f);
	}
	params->volFogDensity = density;

	// Color distances: based on scene scale
	params->volFogColour1Distance = double(sceneScale * 0.1f);
	params->volFogColour2Distance = double(sceneScale * 0.4f);
	params->volFogColour1Distance = std::max(params->volFogColour1Distance, factor * 2.0);
	params->volFogColour2Distance = std::max(params->volFogColour2Distance, params->volFogColour1Distance * 2.0);

}

// ═════════════════════════════════════════════════════════════════════════════
// BASIC FOG (simplified universal approach)
// ═════════════════════════════════════════════════════════════════════════════

void cAutoFog::CalculateBasicFogUniversal(sParamRender *params, const sIterationProfile &prof)
{
	(void)prof;  // unused — basic fog does not depend on iteration profile
	if (!params) return;

	float sceneScale = std::max(float(params->viewDistanceMax), 1e-6f);
	params->fogVisibility = double(sceneScale * 0.3f * 3.0f);
	params->fogVisibility = std::max(params->fogVisibility, 1e-6);
	params->fogColor = sRGBFloat(0.7f, 0.75f, 0.85f);

}

// ═════════════════════════════════════════════════════════════════════════════
// HIGH-LEVEL API
// ═════════════════════════════════════════════════════════════════════════════

bool cAutoFog::AutoTuneIterationFog(sParamRender *params, const cNineFractals *fractal, sRenderData *data)
{
	if (!params || !fractal) return false;
	profile = ProbeScene(params, fractal, data, 32);  // 32x32 = 1024 rays
	if (!profile.valid)
	{
		qWarning() << "AutoFog: Iteration probing failed";
		return false;
	}
	CalculateIterationFogUniversal(params, profile);
	return true;
}

bool cAutoFog::AutoTuneDistanceFog(sParamRender *params, const cNineFractals *fractal, sRenderData *data)
{
	if (!params || !fractal) return false;
	if (!profile.valid)
	{
		profile = ProbeScene(params, fractal, data, 32);
	}
	CalculateDistanceFogUniversal(params, profile);
	return true;
}

bool cAutoFog::AutoTuneBasicFog(sParamRender *params, const cNineFractals *fractal, sRenderData *data)
{
	if (!params || !fractal) return false;
	if (!profile.valid)
	{
		profile = ProbeScene(params, fractal, data, 32);
	}
	CalculateBasicFogUniversal(params, profile);
	return true;
}

bool cAutoFog::AutoTuneAll(sParamRender *params, const cNineFractals *fractal, sRenderData *data)
{
	WriteAutoFogLog("=== AutoTuneAll START ===");
	if (!params || !fractal)
	{
		WriteAutoFogLog("ERROR: null params or fractal");
		return false;
	}

	WriteAutoFogLog(QString("params: image=%1x%2 fov=%3 maxSteps=%4 viewDist=%5")
		.arg(params->imageWidth).arg(params->imageHeight)
		.arg(params->fov).arg(params->maxRaymarchingSteps).arg(params->viewDistanceMax));
	WriteAutoFogLog(QString("params: iterFog=%1 volFog=%2 basicFog=%3")
		.arg(params->iterFogEnabled).arg(params->volFogEnabled).arg(params->fogEnabled));
	WriteAutoFogLog(QString("params: camera=%1 %2 %3 target=%4 %5 %6")
		.arg(params->camera.x).arg(params->camera.y).arg(params->camera.z)
		.arg(params->target.x).arg(params->target.y).arg(params->target.z));

	profile = ProbeScene(params, fractal, data, 32);
	if (!profile.valid)
	{
		WriteAutoFogLog("ERROR: ProbeScene returned invalid profile");
		qWarning() << "AutoFog: Full probing failed, keeping manual fog parameters";
		return false;
	}

	WriteAutoFogLog(QString("ProbeScene OK: hitRate=%1 hitCount=%2/%3 meanDepth=%4 p50=%5 p95=%6")
		.arg(profile.hitRate).arg(profile.hitCount).arg(profile.numSamples)
		.arg(profile.meanDepth).arg(profile.p50).arg(profile.p95));

	if (params->iterFogEnabled)
	{
		CalculateIterationFogUniversal(params, profile);
		WriteAutoFogLog(QString("IterationFog: trim=%1 trimHigh=%2 opacity=%3 c1max=%4 c2max=%5 boost=%6")
			.arg(params->iterFogOpacityTrim).arg(params->iterFogOpacityTrimHigh)
			.arg(params->iterFogOpacity).arg(params->iterFogColor1Maxiter)
			.arg(params->iterFogColor2Maxiter).arg(params->iterFogBrightnessBoost));
	}
	if (params->volFogEnabled)
	{
		CalculateDistanceFogUniversal(params, profile);
		WriteAutoFogLog(QString("DistanceFog: distFactor=%1 distFromSurf=%2 density=%3")
			.arg(params->volFogDistanceFactor).arg(params->volFogDistanceFromSurface)
			.arg(params->volFogDensity));
	}
	if (params->fogEnabled)
	{
		CalculateBasicFogUniversal(params, profile);
		WriteAutoFogLog(QString("BasicFog: visibility=%1").arg(params->fogVisibility));
	}

	WriteAutoFogLog("=== AutoTuneAll SUCCESS ===");
	return true;
}

// ═════════════════════════════════════════════════════════════════════════════
// AUTO-DETECT ITERATIONS & BAILOUT
// ═════════════════════════════════════════════════════════════════════════════

cAutoFog::sAutoDetectResult cAutoFog::AutoDetectIterationsAndBailout(
	const sParamRender *params, const cNineFractals *fractal, sRenderData *data)
{
	sAutoDetectResult result;
	if (!params || !fractal)
	{
		result.valid = false;
		return result;
	}

	// Ensure we have fresh probe data
	if (!profile.valid)
	{
		profile = ProbeScene(params, fractal, data, 32);
	}
	if (!profile.valid)
	{
		result.valid = false;
		return result;
	}

	float N = profile.effectiveN;
	if (N <= 0.0f) N = 250.0f;

	// ── SUGGESTED N (renderer max iterations) ──
	// Use p99 as the "maximum needed" with a safety margin.
	// p99 captures almost all samples without being inflated by extreme outliers.
	float maxObserved = profile.p99;
	if (maxObserved < 1.0f) maxObserved = profile.p95;
	if (maxObserved < 1.0f) maxObserved = profile.p90;
	if (maxObserved < 1.0f) maxObserved = profile.p75;
	if (maxObserved < 1.0f) maxObserved = 5.0f;

	// Safety margin: 25% above p99, plus absolute padding
	float suggestedNf = maxObserved * 1.25f + 10.0f;

	// For deep zoom (small hit depth), we typically need fewer iterations
	float hitDepth = (profile.meanDepthHits > 1e-10f) ? profile.meanDepthHits : profile.meanDepth;
	if (hitDepth < 1e-3f)
	{
		// Deep zoom: cap N more aggressively since surface is reached quickly
		suggestedNf = std::min(suggestedNf, maxObserved * 1.1f + 5.0f);
	}

	result.suggestedN = int(suggestedNf);
	result.suggestedN = std::max(result.suggestedN, 5);
	result.suggestedN = std::min(result.suggestedN, 1000);

	// ── SUGGESTED FORMULA MAXITER ──
	// Formula maxiter should be at least as high as N, often slightly higher
	// because some formulas need extra iterations for internal transforms.
	float suggestedMaxiterF = std::max(suggestedNf * 1.1f, maxObserved * 1.3f + 10.0f);
	result.suggestedFormulaMaxiter = int(suggestedMaxiterF);
	result.suggestedFormulaMaxiter = std::max(result.suggestedFormulaMaxiter, result.suggestedN);
	result.suggestedFormulaMaxiter = std::min(result.suggestedFormulaMaxiter, 2000);

	// ── SUGGESTED BAILOUT ──
	// Bailout should scale with scene distance. Deep zoom needs SMALLER bailout.
	// Standard bailout=100 is often way too large for close-ups, causing
	// unnecessary iterations and 10x render time inflation.
	if (hitDepth > 1e-10f)
	{
		// Scene-scale proportional bailout
		// At 1 unit distance: bailout ~100
		// At 0.001 distance (deep zoom): bailout ~1
		// At 100 distance (far away): bailout ~10000
		result.suggestedBailout = double(hitDepth * 100.0f);
		result.suggestedBailout = std::max(result.suggestedBailout, 1.0);
		result.suggestedBailout = std::min(result.suggestedBailout, 1e6);
	}
	else
	{
		result.suggestedBailout = 100.0;
	}

	// Additional bailout refinement based on observed iteration spread
	// Narrow spread = simple surface = lower bailout sufficient
	// Wide spread = complex structure = higher bailout needed
	if (profile.range < 3.0f)
	{
		result.suggestedBailout *= 0.5;
		result.suggestedBailout = std::max(result.suggestedBailout, 1.0);
	}
	else if (profile.range > 50.0f)
	{
		result.suggestedBailout *= 2.0;
		result.suggestedBailout = std::min(result.suggestedBailout, 1e6);
	}

	result.valid = true;

	qDebug() << "AUTOFOG DETECT: N=" << result.suggestedN
			 << "maxiter=" << result.suggestedFormulaMaxiter
			 << "bailout=" << result.suggestedBailout
			 << "p99=" << profile.p99 << "range=" << profile.range
			 << "hitDepth=" << hitDepth;

	return result;
}

// ═════════════════════════════════════════════════════════════════════════════
// SMOOTHING
// ═════════════════════════════════════════════════════════════════════════════

void cAutoFog::SmoothParams(sParamRender *params, float alpha)
{
	if (!params || alpha <= 0.0f || alpha > 1.0f) return;

	auto lerp = [](double a, double b, double t) { return a * (1.0 - t) + b * t; };
	auto lerpF = [](float a, float b, float t) { return a * (1.0f - t) + b * t; };

	if (hasPrevValues)
	{
		params->iterFogOpacity = lerp(params->iterFogOpacity, prevIterOpacity, alpha);
		params->iterFogOpacityTrim = lerpF(params->iterFogOpacityTrim, prevIterTrim, alpha);
		params->iterFogOpacityTrimHigh = lerpF(params->iterFogOpacityTrimHigh, prevIterTrimHigh, alpha);
		params->iterFogColor1Maxiter = lerpF(params->iterFogColor1Maxiter, prevIterC1Max, alpha);
		params->iterFogColor2Maxiter = lerpF(params->iterFogColor2Maxiter, prevIterC2Max, alpha);
		params->iterFogBrightnessBoost = lerpF(params->iterFogBrightnessBoost, prevIterBoost, alpha);
		params->volFogDistanceFactor = lerp(params->volFogDistanceFactor, prevDistFactor, alpha);
		params->volFogDensity = lerp(params->volFogDensity, prevDistDensity, alpha);
		params->fogVisibility = lerp(params->fogVisibility, prevBasicVisibility, alpha);
	}

	prevIterOpacity = params->iterFogOpacity;
	prevIterTrim = params->iterFogOpacityTrim;
	prevIterTrimHigh = params->iterFogOpacityTrimHigh;
	prevIterC1Max = params->iterFogColor1Maxiter;
	prevIterC2Max = params->iterFogColor2Maxiter;
	prevIterBoost = params->iterFogBrightnessBoost;
	prevDistFactor = params->volFogDistanceFactor;
	prevDistDensity = params->volFogDensity;
	prevBasicVisibility = params->fogVisibility;
	hasPrevValues = true;
}

} // namespace autoFog

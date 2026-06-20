/**
 * Mandelbulber v2 — Universal Auto Fog Implementation
 *
 * Empirical scene probing with percentile-based tuning and fractal-class modifiers.
 */

#include "auto_fog.hpp"
#include "fractparams.hpp"
#include "nine_fractals.hpp"
#include "render_data.hpp"
#include "calculate_distance.hpp"
#include "algebra.hpp"
#include "projection_3d.hpp"
#include "camera_target.hpp"
#include "parameters.hpp"
#include "formula/definition/all_fractal_list_enums.hpp"
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

int ProbeGridResForQuality(const eAutoFogQuality quality)
{
	switch (quality)
	{
		case eAutoFogQuality::Preview: return 16;
		case eAutoFogQuality::Cinematic: return 48;
		case eAutoFogQuality::Balanced:
		default: return 32;
	}
}

static float ClampF(const float v, const float lo, const float hi)
{
	return std::max(lo, std::min(v, hi));
}

static int GetPrimaryFormulaIndex(const cNineFractals *fractal)
{
	if (!fractal) return fractal::mandelbulb;
	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		if (fractal->GetFractal(i)->formula != fractal::none)
			return fractal->GetFractal(i)->formula;
	}
	return fractal::mandelbulb;
}

static bool HasActiveMutations(const cNineFractals *fractal)
{
	if (!fractal) return false;
	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		if (fractal->GetMutationParams(i).enabled) return true;
	}
	return false;
}

sFogProfileModifier DetectFractalModifiers(const cNineFractals *fractal, QString *classNameOut)
{
	sFogProfileModifier mod;
	QString className = QStringLiteral("Mandelbulb-like");

	const int formula = GetPrimaryFormulaIndex(fractal);
	using namespace fractal;

	switch (formula)
	{
		case mandelbox:
		case mandelboxFast:
		case mandelboxSmooth:
		case mandelboxMenger:
		case aboxMod1:
		case aboxMod11:
		case aboxMod12:
		case aboxMod13:
		case aboxMod14:
		case aboxMod15:
		case buffalo:
			mod.highMul = 1.35f;
			mod.opacityMul = 0.75f;
			mod.colorSpreadMul = 1.25f;
			className = QStringLiteral("Mandelbox-like");
			break;

		case amazingSurf:
		case amazingSurfMod1:
		case amazingSurfMod2:
		case amazingSurfMod3:
		case amazingSurfMod4:
		case amazingSurfMulti:
			mod.opacityMul = 0.75f;
			mod.colorSpreadMul = 1.25f;
			className = QStringLiteral("Amazing Surf-like");
			break;

		case pseudoKleinian:
		case pseudoKleinianMod1:
		case pseudoKleinianMod2:
		case pseudoKleinianMod3:
		case pseudoKleinianMod4:
		case pseudoKleinianMod5:
		case pseudoKleinianMod6:
		case pseudoKleinianMod7:
		case pseudoKleinian4d:
		case pseudoKleinianStdDE:
		case josKleinian:
		case josKleinianV2:
		case josKleinianV3:
		case josKleinianV4:
			mod.trimMul = 0.75f;
			mod.highMul = 1.6f;
			mod.opacityMul = 0.65f;
			className = QStringLiteral("Kleinian-like");
			break;

		case mengerSponge:
		case mengerMod1:
		case menger3:
		case menger4d:
		case kaleidoscopicIfs:
			mod.highMul = 1.2f;
			mod.opacityMul = 0.85f;
			mod.trimHighExtra = 2.0f;
			className = QStringLiteral("IFS/Menger-like");
			break;

		default:
			break;
	}

	if (HasActiveMutations(fractal))
	{
		mod.opacityMul *= 0.70f;
		mod.highMul *= 1.15f;
		mod.trimHighExtra += 1.0f;
		className += QStringLiteral(" + mutations");
	}

	if (classNameOut) *classNameOut = className;
	return mod;
}

void WriteAutoFogResults(std::shared_ptr<cParameterContainer> par, const sParamRender &renderParams,
	eAutoFogTuneMode mode, bool enableTunedTypes)
{
	if (!par) return;

	if (mode == eAutoFogTuneMode::All || mode == eAutoFogTuneMode::IterationOnly)
	{
		par->Set("iteration_fog_opacity_trim", double(renderParams.iterFogOpacityTrim));
		par->Set("iteration_fog_opacity_trim_high", double(renderParams.iterFogOpacityTrimHigh));
		par->Set("iteration_fog_color_1_maxiter", double(renderParams.iterFogColor1Maxiter));
		par->Set("iteration_fog_color_2_maxiter", double(renderParams.iterFogColor2Maxiter));
		par->Set("iteration_fog_opacity", renderParams.iterFogOpacity);
		par->Set("iteration_fog_brightness_boost", double(renderParams.iterFogBrightnessBoost));
		if (enableTunedTypes) par->Set("iteration_fog_enable", true);
	}

	if (mode == eAutoFogTuneMode::All || mode == eAutoFogTuneMode::DistanceOnly)
	{
		par->Set("volumetric_fog_distance_factor", renderParams.volFogDistanceFactor);
		par->Set("volumetric_fog_distance_from_surface", renderParams.volFogDistanceFromSurface);
		par->Set("volumetric_fog_density", double(renderParams.volFogDensity));
		par->Set("volumetric_fog_colour_1_distance", renderParams.volFogColour1Distance);
		par->Set("volumetric_fog_colour_2_distance", renderParams.volFogColour2Distance);
		if (enableTunedTypes) par->Set("volumetric_fog_enabled", true);
	}

	if (mode == eAutoFogTuneMode::All || mode == eAutoFogTuneMode::BasicOnly)
	{
		par->Set("basic_fog_visibility", renderParams.fogVisibility);
		if (enableTunedTypes) par->Set("basic_fog_enabled", true);
	}
}

QString FormatAutoFogResultLabel(const sIterationProfile &prof, const QString &className)
{
	if (!prof.valid)
		return QStringLiteral("Auto fog failed: no surface hits from camera");

	return QStringLiteral("%1 — trim %2, high %3, median iter %4, hit rate %5%")
		.arg(className)
		.arg(prof.p05, 0, 'f', 1)
		.arg(prof.p95, 0, 'f', 1)
		.arg(prof.p50, 0, 'f', 1)
		.arg(prof.hitRate * 100.0f, 0, 'f', 0);
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

	// Extract iteration values (hits only — misses along open rays inflate p99)
	std::vector<float> iters;
	iters.reserve(samples.size());
	for (const auto &s : samples)
	{
		if (s.hit) iters.push_back(s.iters);
	}
	if (iters.empty())
	{
		for (const auto &s : samples) iters.push_back(s.iters);
	}
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
	(void)fractal;
	if (!params) return 250.0f;
	return std::max(float(params->N), 1.0f);
}

// ═════════════════════════════════════════════════════════════════════════════
// UNIVERSAL PARAMETER CALCULATORS
// ═════════════════════════════════════════════════════════════════════════════

void cAutoFog::CalculateIterationFogUniversal(sParamRender *params, const sIterationProfile &prof,
	const sFogProfileModifier &mod)
{
	if (!params || !prof.valid) return;

	float N = prof.effectiveN;
	if (N <= 0.0f) N = 250.0f;

	float trim = ClampF(prof.p05 * 0.6f * mod.trimMul, 1.0f, N * 0.25f);
	float c1 = ClampF(prof.p25, trim + 1.0f, N * 0.60f);
	const float colorBlend = 0.5f * (prof.p50 + prof.p75);
	float c2 = ClampF(colorBlend, c1 + 1.0f, N * 0.85f);
	float trimHigh = ClampF(prof.p95 * 1.05f * mod.highMul + mod.trimHighExtra, c2 + 1.0f, N);

	if (std::abs(mod.colorSpreadMul - 1.0f) > 1e-3f)
	{
		const float range = trimHigh - trim;
		c1 = trim + range * 0.33f * mod.colorSpreadMul;
		c2 = trim + range * 0.66f * mod.colorSpreadMul;
		c1 = ClampF(c1, trim + 0.5f, N);
		c2 = ClampF(c2, c1 + 0.5f, N);
	}

	if (prof.range < 3.0f)
	{
		trim = std::max(prof.p01 * 0.8f * mod.trimMul, 1.0f);
		trimHigh = std::min(prof.p99 * 1.1f * mod.highMul + mod.trimHighExtra, N);
		trimHigh = std::max(trimHigh, trim + 2.0f);
	}

	float medianStep = prof.medianStepHits > 1e-6f ? prof.medianStepHits : prof.medianStep;
	if (medianStep < 1e-6f) medianStep = 0.01f;
	if (medianStep > 1.0f) medianStep = 1.0f;

	float opacity = 0.0047f * std::pow(N, 0.776f) * std::pow(medianStep, -0.489f);
	opacity *= mod.opacityMul;

	float iterSpread = prof.p95 - prof.p05;
	float spreadRatio = iterSpread / N;
	if (spreadRatio > 0.1f && spreadRatio < 0.3f)
		opacity *= 1.0f + (0.3f - spreadRatio);
	else if (spreadRatio <= 0.1f)
		opacity *= 2.0f;

	qDebug() << "AUTOFOG: N=" << N << "trim=" << trim << "trimHigh=" << trimHigh
				 << "medianStep=" << medianStep << "spreadRatio=" << spreadRatio
				 << "opacity=" << opacity << "class=" << lastFractalClassName;

	opacity = std::max(opacity, 0.1f);
	opacity = std::min(opacity, 500.0f);

	const float iqr = std::max(prof.iqr, 1.0f);
	float boost = ClampF((prof.p95 - prof.p50) / iqr, 0.6f, 2.5f);

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
	return AutoTuneAll(params, fractal, data, eAutoFogQuality::Balanced, eAutoFogTuneMode::IterationOnly);
}

bool cAutoFog::AutoTuneDistanceFog(sParamRender *params, const cNineFractals *fractal, sRenderData *data)
{
	return AutoTuneAll(params, fractal, data, eAutoFogQuality::Balanced, eAutoFogTuneMode::DistanceOnly);
}

bool cAutoFog::AutoTuneBasicFog(sParamRender *params, const cNineFractals *fractal, sRenderData *data)
{
	return AutoTuneAll(params, fractal, data, eAutoFogQuality::Balanced, eAutoFogTuneMode::BasicOnly);
}

bool cAutoFog::AutoTuneAll(sParamRender *params, const cNineFractals *fractal, sRenderData *data,
	eAutoFogQuality quality, eAutoFogTuneMode mode)
{
	WriteAutoFogLog("=== AutoTuneAll START ===");
	if (!params || !fractal)
	{
		WriteAutoFogLog("ERROR: null params or fractal");
		return false;
	}

	const int gridRes = ProbeGridResForQuality(quality);
	WriteAutoFogLog(QString("quality=%1 grid=%2 mode=%3")
		.arg(int(quality)).arg(gridRes).arg(int(mode)));

	WriteAutoFogLog(QString("params: image=%1x%2 fov=%3 maxSteps=%4 viewDist=%5")
		.arg(params->imageWidth).arg(params->imageHeight)
		.arg(params->fov).arg(params->maxRaymarchingSteps).arg(params->viewDistanceMax));
	WriteAutoFogLog(QString("params: iterFog=%1 volFog=%2 basicFog=%3")
		.arg(params->iterFogEnabled).arg(params->volFogEnabled).arg(params->fogEnabled));
	WriteAutoFogLog(QString("params: camera=%1 %2 %3 target=%4 %5 %6")
		.arg(params->camera.x).arg(params->camera.y).arg(params->camera.z)
		.arg(params->target.x).arg(params->target.y).arg(params->target.z));

	profile = ProbeScene(params, fractal, data, gridRes);
	if (!profile.valid)
	{
		WriteAutoFogLog("ERROR: ProbeScene returned invalid profile");
		qWarning() << "AutoFog: Full probing failed, keeping manual fog parameters";
		return false;
	}

	lastModifier = DetectFractalModifiers(fractal, &lastFractalClassName);
	WriteAutoFogLog(QString("fractalClass=%1 trimMul=%2 highMul=%3 opacityMul=%4")
		.arg(lastFractalClassName).arg(lastModifier.trimMul).arg(lastModifier.highMul)
		.arg(lastModifier.opacityMul));

	WriteAutoFogLog(QString("ProbeScene OK: hitRate=%1 hitCount=%2/%3 meanDepth=%4 p50=%5 p95=%6")
		.arg(profile.hitRate).arg(profile.hitCount).arg(profile.numSamples)
		.arg(profile.meanDepth).arg(profile.p50).arg(profile.p95));

	const bool tuneIter = mode == eAutoFogTuneMode::All || mode == eAutoFogTuneMode::IterationOnly;
	const bool tuneDist = mode == eAutoFogTuneMode::All || mode == eAutoFogTuneMode::DistanceOnly;
	const bool tuneBasic = mode == eAutoFogTuneMode::All || mode == eAutoFogTuneMode::BasicOnly;

	if (quality == eAutoFogQuality::Preview)
		lastModifier.opacityMul *= 0.85f;
	else if (quality == eAutoFogQuality::Cinematic)
		lastModifier.opacityMul *= 1.05f;

	if (tuneIter)
	{
		CalculateIterationFogUniversal(params, profile, lastModifier);
		WriteAutoFogLog(QString("IterationFog: trim=%1 trimHigh=%2 opacity=%3 c1max=%4 c2max=%5 boost=%6")
			.arg(params->iterFogOpacityTrim).arg(params->iterFogOpacityTrimHigh)
			.arg(params->iterFogOpacity).arg(params->iterFogColor1Maxiter)
			.arg(params->iterFogColor2Maxiter).arg(params->iterFogBrightnessBoost));
	}
	if (tuneDist)
	{
		CalculateDistanceFogUniversal(params, profile);
		WriteAutoFogLog(QString("DistanceFog: distFactor=%1 distFromSurf=%2 density=%3")
			.arg(params->volFogDistanceFactor).arg(params->volFogDistanceFromSurface)
			.arg(params->volFogDensity));
	}
	if (tuneBasic)
	{
		CalculateBasicFogUniversal(params, profile);
		WriteAutoFogLog(QString("BasicFog: visibility=%1").arg(params->fogVisibility));
	}

	WriteAutoFogLog("=== AutoTuneAll SUCCESS ===");
	params->UpdateIterFogEffectiveN(fractal);
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
	if (params->N > 0)
		result.suggestedN = std::min(result.suggestedN, params->N);
	else
		result.suggestedN = std::min(result.suggestedN, 1000);

	// ── SUGGESTED FORMULA MAXITER ──
	// Formula maxiter should be at least as high as N, often slightly higher
	// because some formulas need extra iterations for internal transforms.
	float suggestedMaxiterF = std::max(suggestedNf * 1.1f, maxObserved * 1.3f + 10.0f);
	result.suggestedFormulaMaxiter = int(suggestedMaxiterF);
	result.suggestedFormulaMaxiter = std::max(result.suggestedFormulaMaxiter, result.suggestedN);
	if (params->N > 0)
		result.suggestedFormulaMaxiter = std::min(result.suggestedFormulaMaxiter, params->N);
	else
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

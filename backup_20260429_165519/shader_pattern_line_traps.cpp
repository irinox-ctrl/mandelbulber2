/**
 * Pattern line traps — CPU surface shader (world-space lines, no relative_size warp).
 */

#include "fractparams.hpp"
#include "material.h"
#include "render_worker.hpp"

#include <QtGlobal>

#include <algorithm>
#include <cmath>

sRGBAFloat cRenderWorker::PatternLineTraps(
	const sShaderInputData &input, sRGBAFloat surfaceColor, sGradientsCollection *gradients) const
{
	Q_UNUSED(surfaceColor)

	sRGBAFloat result(0.0, 0.0, 0.0, 0.0);
	if (!params->patternLineTraps.enabled) return result;

	const int soloLayer = params->patternLineTraps.soloLayerIndex;
	for (int i = 0; i < PATTERN_LINE_TRAP_COUNT; i++)
	{
		if (soloLayer > 0 && soloLayer != i + 1) continue;
		const sPatternLineTrapLayer &layer = params->patternLineTraps.layers[i];
		if (!layer.enabled) continue;

		sPatternLineTrapLayer effLayer = layer;
		const double camDist = (params->camera - layer.position).Length();
		effLayer.radius = PatternLineTrapEffectiveRadius(layer, camDist);

		CVector3 delta = input.point - layer.position;
		delta = effLayer.mRotRotation.RotateVector(delta);

		if (effLayer.maxDistance > 1e-30 || effLayer.segmentHalfLength > 1e-30)
		{
			double margin =
				PatternLineTrapProfileExtent(effLayer) + fabs(effLayer.edgeSoftness);
			if (effLayer.maxDistance > 1e-30) margin += effLayer.maxDistance;
			if (effLayer.segmentHalfLength > 1e-30) margin += effLayer.segmentHalfLength;
			if (delta.Length() > margin * 2.8) continue;
		}

		double axialFade = 1.0;
		if (effLayer.segmentHalfLength > 1e-30)
		{
			const double ax = fabs(delta.x);
			double t = ax / effLayer.segmentHalfLength;
			if (t >= 1.0) continue;
			t = t * t * (3.0 - 2.0 * t);
			axialFade = 1.0 - t;
		}

		const double rawDist = PatternLineTrapProfileRawDist(effLayer, delta.y, delta.z);
		const double wallDist = PatternLineTrapWallDist(layer, rawDist);

		double fade = 1.0;
		if (layer.maxDistance > 1e-30)
		{
			double t = wallDist / layer.maxDistance;
			if (t >= 1.0) continue;
			t = t * t * (3.0 - 2.0 * t);
			fade = 1.0 - t;
		}

		const double falloff = PatternLineTrapGlowFalloff(layer, wallDist);
		const double intens = layer.intensity * falloff * fade * axialFade;

		double tGrad;
		if (params->patternLineTraps.coloringMode == 1 && gradients)
		{
			double nrCol = fmod(fabs(gradients->colorIndex), 248.0 * 256.0);
			tGrad = fmod(nrCol / 256.0 / 10.0 * input.material->coloring_speed
							 + input.material->paletteOffset,
				1.0);
		}
		else if (params->patternLineTraps.coloringMode == 2 && gradients)
		{
			tGrad = fmod(double(gradients->iters) / params->N * input.material->coloring_speed
						 + input.material->paletteOffset,
				1.0);
		}
		else
		{
			tGrad = PatternLineTrapGradientT(layer, wallDist);
		}

		const sRGBFloat grad = PatternLineTrapGradientRgb(layer, tGrad);

		if (params->patternLineTraps.combineMode == 0)
		{
			result.R += float(intens * double(grad.R));
			result.G += float(intens * double(grad.G));
			result.B += float(intens * double(grad.B));
		}
		else
		{
			result.R = std::max(result.R, float(intens * double(grad.R)));
			result.G = std::max(result.G, float(intens * double(grad.G)));
			result.B = std::max(result.B, float(intens * double(grad.B)));
		}
	}

	return result;
}

/**
 * 3x3lion — Deep Zoom GPU Ray Marcher Integration
 * Founded by Iri and Devin
 *
 * Bridges the perturbation engine with the rendering pipeline.
 * When active, CalculateDeepZoomDistance() is called instead of the
 * standard fractal iteration for distance computation.
 */

#include "deep_zoom_integration.h"

#ifdef USE_MPFR

#include <cstring>

namespace deep_zoom_integration
{

namespace
{
sDeepZoomState gState;
} // namespace

sDeepZoomState &GetState()
{
	return gState;
}

void Enable(deep_zoom::cDeepZoomManager *manager)
{
	gState.enabled = true;
	gState.manager = manager;
	gState.referenceReady = (manager != nullptr && manager->IsReady());
}

void Disable()
{
	gState.enabled = false;
	gState.referenceReady = false;
	// Don't delete manager — it's owned by the dock_navigation widget
}

bool IsActive()
{
	return gState.enabled && gState.referenceReady && gState.manager != nullptr;
}

double CalculateDeepZoomDistance(const CVector3 &point, int *outIters, double *outColorIndex)
{
	if (!IsActive()) return -1.0;

	return gState.manager->CalculateDistance(point, outIters, outColorIndex);
}

void PrepareGPUData()
{
	if (!IsActive()) return;

	const deep_zoom::cReferenceOrbit &orbit = gState.manager->GetReferenceOrbit();
	int len = orbit.GetLength();

	// Pack reference orbit into flat float array for GPU upload
	// Each point: Z.x, Z.y, Z.z, DE, r, theta, phi, escaped (8 floats)
	gState.gpuData.refOrbitFlat.resize(len * 8);
	for (int i = 0; i < len; i++)
	{
		const deep_zoom::sReferenceOrbitPoint &pt = orbit.GetPoint(i);
		int base = i * 8;
		gState.gpuData.refOrbitFlat[base + 0] = static_cast<float>(pt.Z.x);
		gState.gpuData.refOrbitFlat[base + 1] = static_cast<float>(pt.Z.y);
		gState.gpuData.refOrbitFlat[base + 2] = static_cast<float>(pt.Z.z);
		gState.gpuData.refOrbitFlat[base + 3] = static_cast<float>(pt.DE);
		gState.gpuData.refOrbitFlat[base + 4] = static_cast<float>(pt.r);
		gState.gpuData.refOrbitFlat[base + 5] = static_cast<float>(pt.theta);
		gState.gpuData.refOrbitFlat[base + 6] = static_cast<float>(pt.phi);
		gState.gpuData.refOrbitFlat[base + 7] = pt.escaped ? 1.0f : 0.0f;
	}
	gState.gpuData.orbitLength = len;

	// Pack Series Approximation matrix
	const deep_zoom::sSeriesCoeff3x3 &sa = orbit.GetSeriesApprox();
	if (sa.valid)
	{
		for (int row = 0; row < 3; row++)
			for (int col = 0; col < 3; col++)
				gState.gpuData.saMatrix[row * 3 + col] = static_cast<float>(sa.A.m[row][col]);
		gState.gpuData.saSkipIters = sa.skipIters;
		gState.gpuData.saValid = true;
	}
	else
	{
		memset(gState.gpuData.saMatrix, 0, sizeof(gState.gpuData.saMatrix));
		gState.gpuData.saSkipIters = 0;
		gState.gpuData.saValid = false;
	}
}

const sDeepZoomState::sGPUData &GetGPUData()
{
	return gState.gpuData;
}

} // namespace deep_zoom_integration

#endif // USE_MPFR

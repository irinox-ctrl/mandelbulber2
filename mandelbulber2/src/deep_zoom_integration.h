/**
 * 3x3lion — Deep Zoom GPU Ray Marcher Integration
 * Founded by Iri and Devin
 *
 * This module bridges the deep zoom perturbation engine with the existing
 * ray marching pipeline. When deep zoom is enabled and a reference orbit
 * is computed, distance calculations are delegated to the perturbation engine
 * instead of the standard fractal iteration.
 *
 * CPU path: CalculateDistance() → deep zoom manager → perturbation iterator
 * GPU path: OpenCL kernel uses uploaded reference orbit + SA matrix for delta iteration
 */

#ifndef MANDELBULBER2_SRC_DEEP_ZOOM_INTEGRATION_H_
#define MANDELBULBER2_SRC_DEEP_ZOOM_INTEGRATION_H_

#include "algebra.hpp"

#ifdef USE_MPFR
#include "deep_zoom.h"
#endif

namespace deep_zoom_integration
{

#ifdef USE_MPFR

// Global deep zoom state — shared across the rendering pipeline
struct sDeepZoomState
{
	bool enabled = false;
	bool referenceReady = false;
	deep_zoom::cDeepZoomManager *manager = nullptr;

	// GPU data buffers (for OpenCL upload)
	struct sGPUData
	{
		std::vector<float> refOrbitFlat; // flattened reference orbit for GPU
		float saMatrix[9];               // 3x3 SA matrix (row-major)
		int saSkipIters = 0;
		bool saValid = false;
		int orbitLength = 0;
	} gpuData;
};

// Get/set the global deep zoom state
sDeepZoomState &GetState();

// Enable deep zoom for the current render
void Enable(deep_zoom::cDeepZoomManager *manager);

// Disable deep zoom (fall back to standard rendering)
void Disable();

// Check if deep zoom should handle this distance calculation
bool IsActive();

// Calculate distance using deep zoom perturbation theory
// Returns negative value if deep zoom is not applicable (caller should use standard path)
double CalculateDeepZoomDistance(const CVector3 &point, int *outIters = nullptr,
	double *outColorIndex = nullptr);

// Prepare GPU data buffers for OpenCL upload
// Call this after computing reference orbit and before GPU render
void PrepareGPUData();

// Get the reference orbit data formatted for GPU upload
const sDeepZoomState::sGPUData &GetGPUData();

#else // !USE_MPFR

// Stubs for non-MPFR builds
inline bool IsActive() { return false; }
inline double CalculateDeepZoomDistance(const CVector3 &, int * = nullptr,
	double * = nullptr) { return -1.0; }

#endif // USE_MPFR

} // namespace deep_zoom_integration

#endif /* MANDELBULBER2_SRC_DEEP_ZOOM_INTEGRATION_H_ */

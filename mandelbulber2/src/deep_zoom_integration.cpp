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

#include <cmath>
#include <cstring>

namespace deep_zoom_integration
{

namespace
{
sDeepZoomState gState;
deep_zoom::cDeepZoomManager *autoManager = nullptr;
double activeZoomLevel = 0.0;
CVector3 lastAutoCenter;
CVector3 lastAutoJuliaC;
bool lastAutoJuliaMode = false;
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

	// Pack reference orbit into flat double array for GPU upload (fp64)
	// Each point: Z.x, Z.y, Z.z, DE, r, theta, phi, escaped (8 doubles)
	gState.gpuData.refOrbitFlat.resize(len * 8);
	for (int i = 0; i < len; i++)
	{
		const deep_zoom::sReferenceOrbitPoint &pt = orbit.GetPoint(i);
		int base = i * 8;
		gState.gpuData.refOrbitFlat[base + 0] = pt.Z.x;
		gState.gpuData.refOrbitFlat[base + 1] = pt.Z.y;
		gState.gpuData.refOrbitFlat[base + 2] = pt.Z.z;
		gState.gpuData.refOrbitFlat[base + 3] = pt.DE;
		gState.gpuData.refOrbitFlat[base + 4] = pt.r;
		gState.gpuData.refOrbitFlat[base + 5] = pt.theta;
		gState.gpuData.refOrbitFlat[base + 6] = pt.phi;
		gState.gpuData.refOrbitFlat[base + 7] = pt.escaped ? 1.0 : 0.0;
	}
	gState.gpuData.orbitLength = len;

	// Pack Series Approximation matrix
	const deep_zoom::sSeriesCoeff3x3 &sa = orbit.GetSeriesApprox();
	if (sa.valid)
	{
		for (int row = 0; row < 3; row++)
			for (int col = 0; col < 3; col++)
				gState.gpuData.saMatrix[row * 3 + col] = sa.A.m[row][col];
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

const deep_zoom::cDeepZoomManager *GetManager()
{
	return gState.manager;
}

CVector3 GetCenter()
{
	return lastAutoCenter;
}

void AutoActivate(double cameraDistance, const CVector3 &target,
	bool juliaMode, const CVector3 &juliaC, int maxIter,
	double power, double bailout,
	double alphaAngleOffset, double betaAngleOffset)
{
	double zoomLevel = 1.0 / std::max(cameraDistance, 1e-30);

	if (!deep_zoom::cDeepZoomManager::ShouldUseDeepZoom(zoomLevel))
	{
		// Below threshold: disable if auto-manager was active
		if (gState.enabled && gState.manager == autoManager && autoManager != nullptr)
		{
			Disable();
		}
		activeZoomLevel = 0.0;
		return;
	}

	// Check if we need to recompute (center or Julia c changed, or not yet computed)
	bool needRecompute = false;
	if (autoManager == nullptr)
	{
		autoManager = new deep_zoom::cDeepZoomManager();
		needRecompute = true;
	}

	CVector3 delta = target - lastAutoCenter;
	double centerDist = delta.Length();
	bool centerChanged = centerDist > cameraDistance * 0.01;
	bool juliaModeChanged = (juliaMode != lastAutoJuliaMode);
	bool juliaCChanged = juliaMode && (juliaC - lastAutoJuliaC).Length() > 1e-10;

	if (centerChanged || juliaModeChanged || juliaCChanged || !autoManager->IsReady())
	{
		needRecompute = true;
	}

	if (needRecompute)
	{
		deep_zoom::sDeepZoomConfig config;
		config.power = power;
		config.bailout = bailout;
		config.maxIterations = maxIter;
		config.precisionBits = deep_zoom::cDeepZoomManager::PrecisionForZoom(zoomLevel);
		config.juliaMode = juliaMode;
		config.juliaC = juliaC;
		config.alphaAngleOffset = alphaAngleOffset;
		config.betaAngleOffset = betaAngleOffset;

		double pixelSpacing = cameraDistance / 800.0;

		autoManager->Configure(config);
		autoManager->SetPixelSpacing(pixelSpacing);

		if (juliaMode)
		{
			autoManager->SetJuliaMode(true, juliaC);
		}

		autoManager->SetCenter(target);

		lastAutoCenter = target;
		lastAutoJuliaC = juliaC;
		lastAutoJuliaMode = juliaMode;
	}

	// Activate
	Enable(autoManager);
	PrepareGPUData();
	activeZoomLevel = zoomLevel;
}

QString GetStatusString()
{
	if (!IsActive()) return QString();

	const deep_zoom::cReferenceOrbit &orbit = gState.manager->GetReferenceOrbit();
	const deep_zoom::sDeepZoomConfig &config = gState.manager->GetConfig();
	int saSkip = gState.manager->GetSASkipIterations();

	QString mode = config.juliaMode ? "Julia" : "Mandelbulb";
	QString status = QString("DEEP ZOOM [%1]\nOrbit: %2 iters | %3 bits | SA skip: %4")
		.arg(mode)
		.arg(orbit.GetLength())
		.arg(config.precisionBits)
		.arg(saSkip);

	if (activeZoomLevel > 0.0)
	{
		status += QString("\nZoom: %1").arg(QString::number(activeZoomLevel, 'e', 2));
	}

	return status;
}

double GetActiveZoomLevel()
{
	return activeZoomLevel;
}

} // namespace deep_zoom_integration

#endif // USE_MPFR

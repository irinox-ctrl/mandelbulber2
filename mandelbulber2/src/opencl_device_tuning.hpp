#ifndef MANDELBULBER2_SRC_OPENCL_DEVICE_TUNING_HPP_
#define MANDELBULBER2_SRC_OPENCL_DEVICE_TUNING_HPP_

#include <memory>

#include <QString>

#include <QtGlobal>

class cOpenClHardware;
class cFractalContainer;
class cParameterContainer;

#ifdef USE_OPENCL
#include "opencl_device.h"

struct sOpenClDeviceTuning
{
	int jobSizeMultiplier = 2;
	int memoryLimitMb = 512;
	int benchmarkVersion = 0;
	int benchmarkBestMs = 0;
	bool benchmarked = false;
	QString deviceName;
	QString driverVersion;
	QString deviceVersion;
	quint64 globalMemBytes = 0;
	int maxComputeUnits = 0;
};

/** Load cached tuning or compute heuristics; apply to gPar when still at factory defaults. */
void ApplyOpenClDeviceTuning(cOpenClHardware *hardware, std::shared_ptr<cParameterContainer> params);

/** Queue a deferred OpenCL tile benchmark (runs after UI is idle). */
void ScheduleOpenClTileBenchmark(cOpenClHardware *hardware,
	std::shared_ptr<cParameterContainer> params);

/** Run tile benchmark synchronously; returns best job size multiplier or 0 on failure. */
int RunOpenClTileBenchmark(cOpenClHardware *hardware, std::shared_ptr<cParameterContainer> params,
	std::shared_ptr<cFractalContainer> fractalParams);

/** Refine cached job size from observed OpenCL tile scheduler after a full render. */
void PersistRuntimeOpenClDeviceTuning(cOpenClHardware *hardware,
	std::shared_ptr<const cParameterContainer> params, quint64 workGroupSizeMultiplier,
	quint64 workGroupSizeOptimalMultiplier, quint64 renderedPixelCount);

sOpenClDeviceTuning ComputeHeuristicDeviceTuning(
	const cOpenClDevice::sDeviceInformation &deviceInfo);
#endif /* USE_OPENCL */

#endif /* MANDELBULBER2_SRC_OPENCL_DEVICE_TUNING_HPP_ */

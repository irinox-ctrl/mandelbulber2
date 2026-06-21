#include "opencl_device_tuning.hpp"

#ifdef USE_OPENCL

#include <memory>

#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDir>
#include <QElapsedTimer>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>

#include "cimage.hpp"
#include "fractal_container.hpp"
#include "fractal_enums.h"
#include "global_data.hpp"
#include "initparameters.hpp"
#include "interface.hpp"
#include "nine_fractals.hpp"
#include "opencl_device.h"
#include "opencl_engine_render_fractal.h"
#include "opencl_global.h"
#include "opencl_hardware.h"
#include "parameters.hpp"
#include "render_data.hpp"
#include "system_data.hpp"
#include "system_directories.hpp"
#include "wait.hpp"
#include "write_log.hpp"

namespace
{
constexpr int kDefaultJobSizeMultiplier = 2;
constexpr int kDefaultMemoryLimitMb = 512;
constexpr int kBenchmarkVersion = 1;
constexpr int kBenchmarkImageSize = 192;

QString ComputeDeviceTuningKey(const cOpenClDevice::sDeviceInformation &info)
{
	QCryptographicHash hash(QCryptographicHash::Sha256);
	hash.addData(info.deviceName.toUtf8());
	hash.addData(info.driverVersion.toUtf8());
	hash.addData(info.deviceVersion.toUtf8());
	hash.addData(QByteArray::number(qulonglong(info.globalMemSize)));
	return hash.result().toHex().left(16);
}

QString TuningCachePath(const QString &key)
{
	return systemDirectories.GetOpenCLCacheFolder() + QDir::separator() + "device_tuning_" + key
		+ ".json";
}

bool LoadDeviceTuningFromFile(const QString &path, sOpenClDeviceTuning &tuning)
{
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) return false;

	const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	if (!doc.isObject()) return false;

	const QJsonObject obj = doc.object();
	tuning.jobSizeMultiplier = obj.value("jobSizeMultiplier").toInt(kDefaultJobSizeMultiplier);
	tuning.memoryLimitMb = obj.value("memoryLimitMb").toInt(kDefaultMemoryLimitMb);
	tuning.benchmarkVersion = obj.value("benchmarkVersion").toInt(0);
	tuning.benchmarkBestMs = obj.value("benchmarkBestMs").toInt(0);
	tuning.benchmarked = obj.value("benchmarked").toBool(false);
	tuning.deviceName = obj.value("deviceName").toString();
	tuning.driverVersion = obj.value("driverVersion").toString();
	tuning.deviceVersion = obj.value("deviceVersion").toString();
	tuning.globalMemBytes = quint64(obj.value("globalMemBytes").toDouble(0));
	tuning.maxComputeUnits = obj.value("maxComputeUnits").toInt(0);
	return tuning.jobSizeMultiplier > 0 && tuning.memoryLimitMb > 0;
}

void SaveDeviceTuningToFile(const QString &path, const sOpenClDeviceTuning &tuning)
{
	QJsonObject obj;
	obj.insert("jobSizeMultiplier", tuning.jobSizeMultiplier);
	obj.insert("memoryLimitMb", tuning.memoryLimitMb);
	obj.insert("benchmarkVersion", tuning.benchmarkVersion);
	obj.insert("benchmarkBestMs", tuning.benchmarkBestMs);
	obj.insert("benchmarked", tuning.benchmarked);
	obj.insert("deviceName", tuning.deviceName);
	obj.insert("driverVersion", tuning.driverVersion);
	obj.insert("deviceVersion", tuning.deviceVersion);
	obj.insert("globalMemBytes", double(tuning.globalMemBytes));
	obj.insert("maxComputeUnits", tuning.maxComputeUnits);

	QFile file(path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return;
	file.write(QJsonDocument(obj).toJson(QJsonDocument::Indented));
}

bool CacheMatchesDevice(const sOpenClDeviceTuning &tuning,
	const cOpenClDevice::sDeviceInformation &info)
{
	return tuning.driverVersion == info.driverVersion
		&& tuning.deviceVersion == info.deviceVersion
		&& tuning.globalMemBytes == info.globalMemSize;
}

bool NeedsTileBenchmark(const sOpenClDeviceTuning &tuning)
{
	return !tuning.benchmarked || tuning.benchmarkVersion != kBenchmarkVersion;
}

QList<int> CandidateJobMultipliers(const cOpenClDevice::sDeviceInformation &info)
{
	const quint64 memGb = info.globalMemSize / (1024ULL * 1024ULL * 1024ULL);
	if (memGb >= 24) return {4, 6, 8, 10, 12};
	if (memGb >= 16) return {3, 4, 6, 8, 10};
	if (memGb >= 8) return {2, 4, 6, 8};
	if (memGb >= 4) return {2, 3, 4, 6};
	return {2, 3, 4};
}

void ConfigureBenchmarkParams(std::shared_ptr<cParameterContainer> benchPar)
{
	benchPar->Set("image_width", kBenchmarkImageSize);
	benchPar->Set("image_height", kBenchmarkImageSize);
	benchPar->Set("opencl_mode", int(cOpenClEngineRenderFractal::clRenderEngineTypeFast));
	benchPar->Set("N", 24);
	benchPar->Set("detail_level", 1.0);
	benchPar->Set("ambient_occlusion_enabled", false);
	benchPar->Set("DOF_monte_carlo", false);
	benchPar->Set("nebula_mode", false);
	benchPar->Set("raytraced_reflections", false);
	benchPar->Set("volumetric_fog_enabled", false);
	benchPar->Set("antialiasing_enabled", false);
	benchPar->Set("opencl_precision", 0);
}

qint64 RunSingleBenchmarkTile(cOpenClEngineRenderFractal *engine,
	std::shared_ptr<cParameterContainer> benchPar, std::shared_ptr<cFractalContainer> benchFractal,
	const int jobMultiplier)
{
	benchPar->Set("opencl_job_size_multiplier", jobMultiplier);

	bool stopRequest = false;
	auto renderData = std::make_shared<sRenderData>();
	renderData->stopRequest = &stopRequest;
	renderData->configuration.DisableRefresh();
	renderData->configuration.DisableProgressiveRender();

	const int width = benchPar->Get<int>("image_width");
	const int height = benchPar->Get<int>("image_height");
	auto image = std::make_shared<cImage>(width, height);

	renderData->objectData.resize(NUMBER_OF_FRACTALS);
	auto paramRender = std::make_shared<sParamRender>(benchPar, &renderData->objectData);
	auto fractals = std::make_shared<cNineFractals>(benchFractal, benchPar);
	renderData->ValidateObjects();

	engine->Lock();
	qint64 elapsedMs = -1;

	engine->SetParameters(
		benchPar, benchFractal, paramRender, fractals, renderData, false);
	if (engine->LoadSourcesAndCompile(benchPar) && engine->CreateKernel4Program(benchPar)
		&& engine->PreAllocateBuffers(benchPar) && engine->CreateCommandQueue())
	{
		QElapsedTimer timer;
		timer.start();
		if (engine->RenderMulti(image, &stopRequest, renderData.get())) elapsedMs = timer.elapsed();
	}

	engine->Unlock();
	return elapsedMs;
}

bool CanRunBackgroundBenchmark()
{
	if (!gOpenCl || !gOpenCl->openClEngineRenderFractal) return false;
	if (systemData.globalStopRequest) return false;
	if (gMainInterface && gMainInterface->mainImage && gMainInterface->mainImage->IsUsed()) return false;
	return true;
}
} // namespace

sOpenClDeviceTuning ComputeHeuristicDeviceTuning(
	const cOpenClDevice::sDeviceInformation &info)
{
	sOpenClDeviceTuning tuning;
	tuning.deviceName = info.deviceName;
	tuning.driverVersion = info.driverVersion;
	tuning.deviceVersion = info.deviceVersion;
	tuning.globalMemBytes = info.globalMemSize;
	tuning.maxComputeUnits = int(info.maxComputeUnits);

	const quint64 memGb = info.globalMemSize / (1024ULL * 1024ULL * 1024ULL);

	if (memGb >= 24)
		tuning.jobSizeMultiplier = 8;
	else if (memGb >= 16)
		tuning.jobSizeMultiplier = 6;
	else if (memGb >= 8)
		tuning.jobSizeMultiplier = 4;
	else if (memGb >= 4)
		tuning.jobSizeMultiplier = 3;
	else
		tuning.jobSizeMultiplier = 2;

	if (info.deviceName.contains(QStringLiteral("NVIDIA"), Qt::CaseInsensitive)
			&& info.maxComputeUnits >= 80)
	{
		tuning.jobSizeMultiplier = qMin(tuning.jobSizeMultiplier + 2, 12);
	}

	const int memMb = int(info.globalMemSize / (1024ULL * 1024ULL));
	tuning.memoryLimitMb = qBound(kDefaultMemoryLimitMb, int(memMb * 0.65), 28672);

	return tuning;
}

void ApplyOpenClDeviceTuning(cOpenClHardware *hardware, std::shared_ptr<cParameterContainer> params)
{
	if (!hardware || !params) return;
	if (!params->Get<bool>("opencl_enabled")) return;
	if (!params->Get<bool>("opencl_auto_tune")) return;

	const QList<cOpenClDevice> workers = hardware->getClWorkers();
	if (workers.isEmpty()) return;

	const cOpenClDevice::sDeviceInformation info = workers.first().getDeviceInformation();
	const QString cacheKey = ComputeDeviceTuningKey(info);
	const QString cachePath = TuningCachePath(cacheKey);

	sOpenClDeviceTuning tuning;
	const bool cacheValid = LoadDeviceTuningFromFile(cachePath, tuning) && CacheMatchesDevice(tuning, info);

	if (cacheValid)
	{
		WriteLog(QString("[OpenCL tuning] Loaded cache for %1: jobSize=%2 memLimit=%3MB benchmarked=%4")
				.arg(info.deviceName)
				.arg(tuning.jobSizeMultiplier)
				.arg(tuning.memoryLimitMb)
				.arg(tuning.benchmarked ? "yes" : "no"),
			2);
	}
	else
	{
		tuning = ComputeHeuristicDeviceTuning(info);
		SaveDeviceTuningToFile(cachePath, tuning);
		WriteLog(QString("[OpenCL tuning] Computed heuristics for %1 (%2 GB): jobSize=%3 memLimit=%4MB")
				.arg(info.deviceName)
				.arg(double(info.globalMemSize) / (1024.0 * 1024.0 * 1024.0), 0, 'f', 1)
				.arg(tuning.jobSizeMultiplier)
				.arg(tuning.memoryLimitMb),
			2);
	}

	if (params->Get<int>("opencl_job_size_multiplier") == kDefaultJobSizeMultiplier)
	{
		params->Set("opencl_job_size_multiplier", tuning.jobSizeMultiplier);
	}

	if (params->Get<int>("opencl_memory_limit") == kDefaultMemoryLimitMb)
	{
		params->Set("opencl_memory_limit", tuning.memoryLimitMb);
	}

	if (NeedsTileBenchmark(tuning)) ScheduleOpenClTileBenchmark(hardware, params);
}

void ScheduleOpenClTileBenchmark(cOpenClHardware *hardware,
	std::shared_ptr<cParameterContainer> params)
{
	if (!hardware || !params) return;
	if (!params->Get<bool>("opencl_auto_tune")) return;
	if (!params->Get<bool>("opencl_auto_tune_benchmark")) return;
	if (!gOpenCl) return;

	static bool benchmarkScheduled = false;
	if (benchmarkScheduled) return;
	benchmarkScheduled = true;

	QTimer::singleShot(2000, gOpenCl, [hardware, params]() {
		if (!CanRunBackgroundBenchmark()) return;
		if (!gParFractal) return;
		RunOpenClTileBenchmark(hardware, params, gParFractal);
	});
}

int RunOpenClTileBenchmark(cOpenClHardware *hardware, std::shared_ptr<cParameterContainer> params,
	std::shared_ptr<cFractalContainer> fractalParams)
{
	if (!hardware || !params || !fractalParams) return 0;
	if (!params->Get<bool>("opencl_enabled")) return 0;
	if (!params->Get<bool>("opencl_auto_tune")) return 0;
	if (!CanRunBackgroundBenchmark()) return 0;

	cOpenClEngineRenderFractal *const engine = gOpenCl->openClEngineRenderFractal;
	if (!engine) return 0;

	const QList<cOpenClDevice> workers = hardware->getClWorkers();
	if (workers.isEmpty()) return 0;

	const cOpenClDevice::sDeviceInformation info = workers.first().getDeviceInformation();
	const QString cachePath = TuningCachePath(ComputeDeviceTuningKey(info));

	sOpenClDeviceTuning tuning;
	if (!LoadDeviceTuningFromFile(cachePath, tuning) || !CacheMatchesDevice(tuning, info))
	{
		tuning = ComputeHeuristicDeviceTuning(info);
	}

	auto benchPar = std::make_shared<cParameterContainer>();
	auto benchFractal = std::make_shared<cFractalContainer>();
	*benchPar = *params;
	*benchFractal = *fractalParams;
	ConfigureBenchmarkParams(benchPar);

	const QList<int> candidates = CandidateJobMultipliers(info);
	if (candidates.isEmpty()) return 0;

	WriteLog(QString("[OpenCL tuning] Starting tile benchmark on %1 (%2x%2 fast mode)...")
			.arg(info.deviceName)
			.arg(kBenchmarkImageSize),
		2);

	// Warmup compile + driver JIT
	RunSingleBenchmarkTile(engine, benchPar, benchFractal, candidates.first());

	int bestMultiplier = tuning.jobSizeMultiplier;
	qint64 bestMs = -1;

	for (const int multiplier : candidates)
	{
		WaitAllowingEvents(1);
		const qint64 elapsedMs = RunSingleBenchmarkTile(engine, benchPar, benchFractal, multiplier);
		if (elapsedMs < 0) continue;

		WriteLog(QString("[OpenCL tuning] Benchmark jobSize=%1 -> %2 ms").arg(multiplier).arg(elapsedMs), 2);

		if (bestMs < 0 || elapsedMs < bestMs)
		{
			bestMs = elapsedMs;
			bestMultiplier = multiplier;
		}
	}

	if (bestMs < 0) return 0;

	tuning.jobSizeMultiplier = bestMultiplier;
	tuning.benchmarked = true;
	tuning.benchmarkVersion = kBenchmarkVersion;
	tuning.benchmarkBestMs = int(bestMs);
	SaveDeviceTuningToFile(cachePath, tuning);

	if (params->Get<int>("opencl_job_size_multiplier") == kDefaultJobSizeMultiplier)
	{
		params->Set("opencl_job_size_multiplier", bestMultiplier);
	}

	WriteLog(QString("[OpenCL tuning] Benchmark done for %1: best jobSize=%2 (%3 ms)")
			.arg(info.deviceName)
			.arg(bestMultiplier)
			.arg(bestMs),
		2);

	return bestMultiplier;
}

void PersistRuntimeOpenClDeviceTuning(cOpenClHardware *hardware,
	std::shared_ptr<const cParameterContainer> params, const quint64 workGroupSizeMultiplier,
	const quint64 workGroupSizeOptimalMultiplier, const quint64 renderedPixelCount)
{
	if (!hardware || !params) return;
	if (!params->Get<bool>("opencl_enabled")) return;
	if (!params->Get<bool>("opencl_auto_tune")) return;
	if (renderedPixelCount < 640 * 480) return;
	if (workGroupSizeOptimalMultiplier == 0) return;

	const QList<cOpenClDevice> workers = hardware->getClWorkers();
	if (workers.isEmpty()) return;

	const cOpenClDevice::sDeviceInformation info = workers.first().getDeviceInformation();
	const QString cachePath = TuningCachePath(ComputeDeviceTuningKey(info));

	sOpenClDeviceTuning tuning;
	if (!LoadDeviceTuningFromFile(cachePath, tuning) || !CacheMatchesDevice(tuning, info))
	{
		tuning = ComputeHeuristicDeviceTuning(info);
	}

	const int configuredJobSize = params->Get<int>("opencl_job_size_multiplier");
	const double ratio = double(workGroupSizeMultiplier)
		/ double(workGroupSizeOptimalMultiplier);
	const int observedJobSize =
		qBound(1, int(qRound(double(configuredJobSize) * ratio)), 12);

	if (observedJobSize == tuning.jobSizeMultiplier) return;

	tuning.jobSizeMultiplier =
		qBound(1, (tuning.jobSizeMultiplier * 2 + observedJobSize + 1) / 3, 12);
	SaveDeviceTuningToFile(cachePath, tuning);

	WriteLog(QString("[OpenCL tuning] Runtime refine for %1: observed=%2 cached=%3")
			.arg(info.deviceName)
			.arg(observedJobSize)
			.arg(tuning.jobSizeMultiplier),
		2);
}

#endif /* USE_OPENCL */

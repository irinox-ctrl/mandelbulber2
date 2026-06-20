/**
 * Thumbnail widget updates: preview render governor integration.
 */
#include "thumbnail_widget.h"

#include <QEventLoop>
#include <QImage>
#include <QPaintEvent>
#include <QThread>
#include <QTimer>

#include "src/cimage.hpp"
#include "src/common_math.h"
#include "src/files.h"
#include "src/global_data.hpp"
#include "src/interface.hpp"
#include "src/opencl_engine_render_fractal.h"
#include "src/preview_render_governor.hpp"
#include "src/render_job.hpp"
#include "src/rendering_configuration.hpp"
#include "src/settings.hpp"
#include "src/stereo.h"
#include "src/system_data.hpp"
#include "src/system_directories.hpp"

cThumbnailWidget::cThumbnailWidget(QWidget *parent) : QWidget(parent)
{
	Init(parent);
}

cThumbnailWidget::cThumbnailWidget(int _width, int _height, double _oversample, QWidget *parent)
		: QWidget(parent)
{
	Init(parent);
	SetSize(_width, _height, _oversample);
}

void cThumbnailWidget::Init(QWidget *parent)
{
	Q_UNUSED(parent);

	tWidth = 0;
	tHeight = 0;
	oversample = 0;
	progressBar = nullptr;
	stopRequest = false;
	isRendered = false;
	isFullyRendered = false;
	hasParameters = false;
	disableTimer = false;
	disableThumbnailCache = false;
	connect(this, &cThumbnailWidget::renderRequest, this, &cThumbnailWidget::slotRender);
	params.reset(new cParameterContainer);
	fractal.reset(new cFractalContainer);
	useOneCPUCore = false;
	useForrandomizer = false;

	timer = new QTimer(this);
	timer->setSingleShot(true);
	connect(timer, &QTimer::timeout, this, &cThumbnailWidget::slotRandomRender);

	idleRequestTimer = new QTimer(this);
	idleRequestTimer->setSingleShot(true);
	idleRequestTimer->setInterval(100);
	connect(idleRequestTimer, &QTimer::timeout, this, &cThumbnailWidget::slotIdleRenderRequest);

	lastRenderTime = 0.0;

	instanceIndex = instanceCount;
	instanceCount++;
}

void cThumbnailWidget::SetSize(int _width, int _height, double _oversample)
{
	tWidth = _width;
	tHeight = _height;
	oversample = _oversample;
	image.reset(new cImage(tWidth * oversample, tHeight * oversample, true));
	image->CreatePreview(1.0 / oversample, tWidth, tWidth, this);
	setFixedWidth(tWidth);
	setFixedHeight(tHeight);
}

cThumbnailWidget::~cThumbnailWidget()
{
	stopRequest = true;
	if (idleRequestTimer) idleRequestTimer->stop();
	if (timer) timer->stop();
	if (image)
	{
		while (image->IsUsed())
		{
			stopRequest = true;
			QThread::msleep(10);
		}
		image.reset();
	}

	instanceCount--;
}

void cThumbnailWidget::ScheduleIdleRenderRequest()
{
	if (disableRenderOnPaint || !hasParameters || isFullyRendered || !idleRequestTimer) return;
	if (visibleRegion().isEmpty()) return;
	if (!idleRequestTimer->isActive()) idleRequestTimer->start();
}

void cThumbnailWidget::slotIdleRenderRequest()
{
	if (!hasParameters || isFullyRendered) return;
	if (visibleRegion().isEmpty()) return;
	if (!isRendered)
	{
		isRendered = true;
		emit renderRequest();
	}
}

bool cThumbnailWidget::TryStopImageInUse(const int retryDelayMs)
{
	if (!image || !image->IsUsed()) return true;

	stopRequest = true;
	if (timer && retryDelayMs > 0) timer->start(retryDelayMs);
	return false;
}

void cThumbnailWidget::paintEvent(QPaintEvent *event)
{
	if (image)
	{
		event->accept();
		if (hasParameters && !isFullyRendered)
		{
			ScheduleIdleRenderRequest();
		}
		image->RedrawInWidget(this);
	}
}

void cThumbnailWidget::AssignParameters(std::shared_ptr<const cParameterContainer> _params,
	std::shared_ptr<const cFractalContainer> _fractal)
{
	isFullyRendered = false;
	if (image)
	{
		params.reset(new cParameterContainer);
		fractal.reset(new cFractalContainer);
		*params = *_params;
		*fractal = *_fractal;
		params->Set("detail_level", std::min(params->Get<double>("image_width") / tWidth / oversample
																					 * params->Get<double>("detail_level"),
																	4.0));
		params->Set("image_height", tHeight * oversample);
		params->Set("stereo_mode", int(cStereo::stereoRedCyan));
		params->Set("antialiasing_enabled", false);
		if (params->Get<bool>("DOF_monte_carlo"))
		{
			params->Set("MC_denoiser_enable", true);
			params->Set("MC_denoiser_strength", 1);
			params->Set("MC_denoiser_preserve_geometry", true);
			params->Set("DOF_max_noise", params->Get<double>("DOF_max_noise") * 10.0);
			params->Set("DOF_min_samples", 5);
		}

		if (fractal->isUsedCustomFormula())
		{
			params->Set("opencl_mode", int(cOpenClEngineRenderFractal::clRenderEngineTypeFull));
			params->Set("opencl_enabled", true);
		}

		else if (params->Get<bool>("opencl_enabled"))
		{
			if (params->Get<int>("opencl_mode") > 0)
			{
				double distance =
					cInterface::GetDistanceForPoint(params->Get<CVector3>("camera"), params, fractal);
				if (distance < 1e-5 && !useForrandomizer)
				{
					params->Set("opencl_mode", 0);
				}

				if (distance < 1e-5 && useForrandomizer)
				{
					isRendered = true;
					isFullyRendered = true;
					params.reset();
					fractal.reset();
					image->ChangeSize(tWidth * oversample, tHeight * oversample, sImageOptional());
					image->ClearImage();
					emit signalZeroDistance();
					emit signalFinished();
					return;
				}
			}
		}

		cSettings tempSettings(cSettings::formatCondensedText);
		tempSettings.CreateText(params, fractal);
		oldHash = hash;
		hash = tempSettings.GetHashCode();

		if (hash != oldHash)
		{
			if (!TryStopImageInUse(500)) return;

			emit settingsChanged();

			isRendered = false;
			hasParameters = true;

			QString thumbnailFileName = GetThumbnailFileName();
			if (QFileInfo::exists(thumbnailFileName) && !disableThumbnailCache)
			{
				fileTouch(thumbnailFileName);
				stopRequest = true;
				isRendered = true;
				isFullyRendered = true;
				if (!TryStopImageInUse(500)) return;

				double dpiScale = devicePixelRatioF();

				QPixmap pixmap;
				pixmap.load(thumbnailFileName);
				pixmap = pixmap.scaled(
					tWidth * dpiScale, tHeight * dpiScale, Qt::KeepAspectRatio, Qt::SmoothTransformation);
				QImage qImage = pixmap.toImage();
				qImage = qImage.convertToFormat(QImage::Format_RGB888);

				std::vector<sRGB8> &preview = image->GetPreviewPrimary();
				std::vector<sRGB8> &preview2 = image->GetPreview();

				int bWidth = qImage.width();
				int bHeight = qImage.height();

				if (!qImage.isNull())
				{
					for (int y = 0; y < bHeight; y++)
					{
						sRGB8 *line = reinterpret_cast<sRGB8 *>(qImage.scanLine(y));
						for (int x = 0; x < bWidth; x++)
						{
							sRGB8 pixel(quint8(line[x].R), quint8(line[x].G), quint8(line[x].B));
							preview[x + y * bWidth] = pixel;
							preview2[x + y * bWidth] = pixel;
						}
					}
				}

				params.reset();
				fractal.reset();
				emit thumbnailRendered();
				emit signalFinished();
			}
			else
			{
				if (!disableTimer)
				{
					timer->start(Random(360000) + 3000);
				}
				ScheduleIdleRenderRequest();
			}
		}
	}
	else
	{
		qCritical() << "Image not yet allocated!";
	}
}

void cThumbnailWidget::slotRender()
{
	if (!image || !params) return;

	const bool widgetVisible = !visibleRegion().isEmpty();
	const bool usesOpenCL = params->Get<bool>("opencl_enabled");

	if (!cPreviewRenderGovernor::CanStartThumbnailRender(
				usesOpenCL, useOneCPUCore, widgetVisible, forceRender))
	{
		const int delay = cPreviewRenderGovernor::RetryDelayMs(
			widgetVisible, cRenderJob::GetRunningJobCount() > systemData.numberOfThreads);
		timer->start(delay);
		isRendered = false;
		return;
	}

	if (!TryStopImageInUse(cPreviewRenderGovernor::RetryDelayMs(widgetVisible, true)))
	{
		isRendered = false;
		return;
	}

	stopRequest = false;
	cPreviewRenderGovernor::NotifyThumbnailRenderStarted();

	cRenderJob *renderJob =
		new cRenderJob(params, fractal, image, 1, &stopRequest, static_cast<QWidget *>(this));
	connect(renderJob, &cRenderJob::updateProgressAndStatus, this,
		&cThumbnailWidget::updateProgressAndStatus);
	connect(renderJob, &cRenderJob::updateImage, this, QOverload<>::of(&QWidget::update));
	connect(renderJob, &cRenderJob::signalTotalRenderTime, this, &cThumbnailWidget::signalTotalRenderTime);

	renderingTimeTimer.start();
	renderJob->UseSizeFromImage(true);

	cRenderingConfiguration config;
	if (useOneCPUCore) config.DisableMultiThread();
	config.EnableIgnoreErrors();
	config.DisableNetRender();
	if (params->Get<bool>("nebula_mode")) config.SetNebulaMode();

	renderJob->Init(cRenderJob::still, config);

	QThread *thread = new QThread;
	renderJob->moveToThread(thread);
	QObject::connect(thread, &QThread::started, renderJob, &cRenderJob::slotExecute);

	thread->setObjectName("ThumbnailWorker");
	thread->start();

	QObject::connect(renderJob, &cRenderJob::finished, renderJob, &QObject::deleteLater);
	QObject::connect(renderJob, &cRenderJob::finished, thread, &QThread::quit);
	QObject::connect(renderJob, &cRenderJob::fullyRendered, this, &cThumbnailWidget::slotFullyRendered);
	QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);
	connect(thread, &QThread::finished, this, &cThumbnailWidget::signalFinished);
	connect(thread, &QThread::finished, this, []() { cPreviewRenderGovernor::NotifyThumbnailRenderFinished(); });
}

void cThumbnailWidget::slotFullyRendered()
{
	isRendered = true;
	if (!disableThumbnailCache)
	{
		QImage qImage(static_cast<const uchar *>(image->ConvertTo8bitChar()), int(image->GetWidth()),
			int(image->GetHeight()), int(image->GetWidth() * sizeof(sRGB8)), QImage::Format_RGB888);
		QPixmap pixmap;
		pixmap.convertFromImage(qImage);

		QString thumbnailFileName = GetThumbnailFileName();
		pixmap.save(thumbnailFileName, "PNG");
	}
	lastRenderTime = renderingTimeTimer.nsecsElapsed() / 1e9;
	params.reset();
	fractal.reset();
	emit thumbnailRendered();
	isFullyRendered = true;
}

void cThumbnailWidget::slotRandomRender()
{
	if (visibleRegion().isEmpty() && !forceRender) return;

	if (!cPreviewRenderGovernor::CanStartThumbnailRender(
				params && params->Get<bool>("opencl_enabled"), useOneCPUCore, !visibleRegion().isEmpty(),
				forceRender))
	{
		timer->start(cPreviewRenderGovernor::RetryDelayMs(!visibleRegion().isEmpty(), true));
		return;
	}

	if (!disableTimer)
	{
		isRendered = true;
		slotRender();
	}
}

bool cThumbnailWidget::WaitUntilRendered(const int timeoutMs)
{
	if (isFullyRendered) return true;

	QEventLoop loop;
	QTimer timeoutTimer;
	timeoutTimer.setSingleShot(true);
	connect(&timeoutTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
	connect(this, &cThumbnailWidget::signalFinished, &loop, &QEventLoop::quit);

	if (!isRendered && params) slotRender();

	timeoutTimer.start(timeoutMs);
	loop.exec(QEventLoop::ExcludeUserInputEvents);
	return isFullyRendered;
}

void cThumbnailWidget::slotSetMinimumSize(int width, int height)
{
	setMinimumSize(width, height);
}

QString cThumbnailWidget::GetThumbnailFileName() const
{
	return systemDirectories.GetThumbnailsFolder() + QDir::separator() + hash + QString(".png");
}

int cThumbnailWidget::instanceCount = 0;

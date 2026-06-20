#include "preview_render_governor.hpp"

#include "global_data.hpp"
#include "interface.hpp"
#include "render_job.hpp"
#include "system_data.hpp"

int cPreviewRenderGovernor::s_activeThumbnailJobs = 0;

bool cPreviewRenderGovernor::CanStartThumbnailRender(
	const bool usesOpenCL, const bool useOneCPUCore, const bool widgetVisible, const bool forceRender)
{
	if (s_activeThumbnailJobs >= kMaxConcurrentThumbnailJobs) return false;

	if (!forceRender)
	{
		if (!widgetVisible) return false;

		if (gMainInterface)
		{
			if (gMainInterface->IsBatchUpdateInProgress()) return false;
			if (gMainInterface->IsMainRenderBusy()) return false;
			if (gMainInterface->IsNavigationDragging()) return false;
		}
	}

	if (usesOpenCL && cRenderJob::IfOpenCLBusy()) return false;

	const int runningJobs = cRenderJob::GetRunningJobCount();
	if (!usesOpenCL)
	{
		if (useOneCPUCore && runningJobs > systemData.numberOfThreads * 2) return false;
		if (!useOneCPUCore && runningJobs > 2) return false;
	}

	return true;
}

void cPreviewRenderGovernor::NotifyThumbnailRenderStarted()
{
	s_activeThumbnailJobs++;
}

void cPreviewRenderGovernor::NotifyThumbnailRenderFinished()
{
	if (s_activeThumbnailJobs > 0) s_activeThumbnailJobs--;
}

int cPreviewRenderGovernor::RetryDelayMs(const bool widgetVisible, const bool highLoad)
{
	if (!widgetVisible) return 60000;
	if (highLoad) return 10000;
	return 1000;
}

int cPreviewRenderGovernor::ActiveThumbnailJobs()
{
	return s_activeThumbnailJobs;
}

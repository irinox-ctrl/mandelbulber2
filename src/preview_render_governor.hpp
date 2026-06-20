#ifndef MANDELBULBER2_SRC_PREVIEW_RENDER_GOVERNOR_HPP_
#define MANDELBULBER2_SRC_PREVIEW_RENDER_GOVERNOR_HPP_

class cPreviewRenderGovernor
{
public:
	static bool CanStartThumbnailRender(
		bool usesOpenCL, bool useOneCPUCore, bool widgetVisible, bool forceRender = false);
	static void NotifyThumbnailRenderStarted();
	static void NotifyThumbnailRenderFinished();
	static int RetryDelayMs(bool widgetVisible, bool highLoad);
	static int ActiveThumbnailJobs();

private:
	static int s_activeThumbnailJobs;
	static const int kMaxConcurrentThumbnailJobs = 1;
};

#endif /* MANDELBULBER2_SRC_PREVIEW_RENDER_GOVERNOR_HPP_ */

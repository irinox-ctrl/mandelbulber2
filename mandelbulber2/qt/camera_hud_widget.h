/**
 * 3x3lion — Camera HUD Overlay Widget
 * Founded by Iri and Devin
 *
 * Semi-transparent overlay on the render view showing:
 * - Distance to surface (DE)
 * - Camera coordinates and rotation
 * - Current mode, FPS, speed
 * - Collision warning indicator
 * - Mini depth bar
 */

#ifndef MANDELBULBER2_QT_CAMERA_HUD_WIDGET_H_
#define MANDELBULBER2_QT_CAMERA_HUD_WIDGET_H_

#include <QWidget>
#include <QPainter>
#include "smart_camera.h"

class cCameraHUDWidget : public QWidget
{
	Q_OBJECT

public:
	explicit cCameraHUDWidget(QWidget *parent = nullptr);
	void SetVisible(bool v) { hudVisible = v; update(); }
	bool IsVisible() const { return hudVisible; }

public slots:
	void slotUpdateHUD(const cSmartCamera::sHUDData &data);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	void DrawTopBar(QPainter &p, int w);
	void DrawBottomBar(QPainter &p, int w, int h);
	void DrawCollisionWarning(QPainter &p, int w, int h);
	void DrawDepthBar(QPainter &p, int w, int h);
	void DrawModeIndicator(QPainter &p, int w);
	void DrawDeepZoomIndicator(QPainter &p, int w);
	void DrawCopyright(QPainter &p, int w, int h);

	cSmartCamera::sHUDData currentData;
	bool hudVisible = true;

	static constexpr int kBarHeight = 28;
	static constexpr int kMargin = 8;
};

#endif /* MANDELBULBER2_QT_CAMERA_HUD_WIDGET_H_ */

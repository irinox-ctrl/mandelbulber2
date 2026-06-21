/**
 * Mandelbulber v2 — fake lights panel (split from dock_fake_lights.ui)
 */

#ifndef MANDELBULBER2_QT_FAKE_LIGHTS_PANEL_H_
#define MANDELBULBER2_QT_FAKE_LIGHTS_PANEL_H_

#include <QWidget>

#include "ui_fake_lights_panel.h"

class cFakeLightsPanel : public QWidget
{
	Q_OBJECT

public:
	explicit cFakeLightsPanel(QWidget *parent = nullptr);
	~cFakeLightsPanel() override;

	Ui::cFakeLightsPanel *fakeLightsUi() const { return ui; }

private:
	Ui::cFakeLightsPanel *ui;
};

#endif // MANDELBULBER2_QT_FAKE_LIGHTS_PANEL_H_

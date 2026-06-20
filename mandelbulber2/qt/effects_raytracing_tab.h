/**
 * Mandelbulber v2 — effects dock raytracing tab (split from dock_effects.ui)
 */

#ifndef MANDELBULBER2_QT_EFFECTS_RAYTRACING_TAB_H_
#define MANDELBULBER2_QT_EFFECTS_RAYTRACING_TAB_H_

#include <QWidget>

#include "ui_effects_raytracing_tab.h"

class cEffectsRaytracingTab : public QWidget
{
	Q_OBJECT

public:
	explicit cEffectsRaytracingTab(QWidget *parent = nullptr);
	~cEffectsRaytracingTab() override;

	Ui::cEffectsRaytracingTab *raytracingUi() const { return ui; }

private:
	Ui::cEffectsRaytracingTab *ui;
};

#endif // MANDELBULBER2_QT_EFFECTS_RAYTRACING_TAB_H_

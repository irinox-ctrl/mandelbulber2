/**
 * Mandelbulber v2 — effects dock lights tab (split from dock_effects.ui)
 */

#ifndef MANDELBULBER2_QT_CEFFECTSLIGHTSTAB_H_
#define MANDELBULBER2_QT_CEFFECTSLIGHTSTAB_H_

#include <QWidget>

#include "ui_effects_lights_tab.h"

class cEffectsLightsTab : public QWidget
{
	Q_OBJECT

public:
	explicit cEffectsLightsTab(QWidget *parent = nullptr);
	~cEffectsLightsTab() override;

	Ui::cEffectsLightsTab *lightsUi() const { return ui; }

private:
	Ui::cEffectsLightsTab *ui;
};

#endif // MANDELBULBER2_QT_CEFFECTSLIGHTSTAB_H_

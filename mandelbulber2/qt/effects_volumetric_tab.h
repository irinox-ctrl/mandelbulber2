/**
 * Mandelbulber v2 — effects dock volumetric tab (split from dock_effects.ui)
 */

#ifndef MANDELBULBER2_QT_EFFECTS_VOLUMETRIC_TAB_H_
#define MANDELBULBER2_QT_EFFECTS_VOLUMETRIC_TAB_H_

#include <QWidget>

#include "ui_effects_volumetric_tab.h"

class cEffectsVolumetricTab : public QWidget
{
	Q_OBJECT

public:
	explicit cEffectsVolumetricTab(QWidget *parent = nullptr);
	~cEffectsVolumetricTab() override;

	Ui::cEffectsVolumetricTab *volumetricUi() const { return ui; }

private:
	Ui::cEffectsVolumetricTab *ui;
};

#endif // MANDELBULBER2_QT_EFFECTS_VOLUMETRIC_TAB_H_

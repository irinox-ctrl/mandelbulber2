/**
 * Mandelbulber v2 — effects dock background tab (split from dock_effects.ui)
 */

#ifndef MANDELBULBER2_QT_CEFFECTSBACKGROUNDTAB_H_
#define MANDELBULBER2_QT_CEFFECTSBACKGROUNDTAB_H_

#include <QWidget>

#include "ui_effects_background_tab.h"

class cEffectsBackgroundTab : public QWidget
{
	Q_OBJECT

public:
	explicit cEffectsBackgroundTab(QWidget *parent = nullptr);
	~cEffectsBackgroundTab() override;

	Ui::cEffectsBackgroundTab *backgroundUi() const { return ui; }

private:
	Ui::cEffectsBackgroundTab *ui;
};

#endif // MANDELBULBER2_QT_CEFFECTSBACKGROUNDTAB_H_

/**
 * Mandelbulber v2 — effects dock post effects tab (split from dock_effects.ui)
 */

#ifndef MANDELBULBER2_QT_CEFFECTSPOSTTAB_H_
#define MANDELBULBER2_QT_CEFFECTSPOSTTAB_H_

#include <QWidget>

#include "ui_effects_post_tab.h"

class cEffectsPostTab : public QWidget
{
	Q_OBJECT

public:
	explicit cEffectsPostTab(QWidget *parent = nullptr);
	~cEffectsPostTab() override;

	Ui::cEffectsPostTab *postUi() const { return ui; }

private:
	Ui::cEffectsPostTab *ui;
};

#endif // MANDELBULBER2_QT_CEFFECTSPOSTTAB_H_

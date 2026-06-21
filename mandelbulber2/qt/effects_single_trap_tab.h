/**
 * Mandelbulber v2 — effects dock single-trap lights tab (split from dock_effects.ui)
 */

#ifndef MANDELBULBER2_QT_EFFECTS_SINGLE_TRAP_TAB_H_
#define MANDELBULBER2_QT_EFFECTS_SINGLE_TRAP_TAB_H_

#include <QWidget>

#include "ui_effects_single_trap_tab.h"

class cEffectsSingleTrapTab : public QWidget
{
	Q_OBJECT

public:
	explicit cEffectsSingleTrapTab(QWidget *parent = nullptr);
	~cEffectsSingleTrapTab() override;

	Ui::cEffectsSingleTrapTab *trapUi() const { return ui; }

private:
	Ui::cEffectsSingleTrapTab *ui;
};

#endif // MANDELBULBER2_QT_EFFECTS_SINGLE_TRAP_TAB_H_

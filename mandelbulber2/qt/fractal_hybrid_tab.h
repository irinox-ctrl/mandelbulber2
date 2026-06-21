/**
 * Mandelbulber v2 — fractal dock hybrid tab (split from dock_fractal.ui)
 */

#ifndef MANDELBULBER2_QT_CFRACTALHYBRIDTAB_H_
#define MANDELBULBER2_QT_CFRACTALHYBRIDTAB_H_

#include <QWidget>

#include "ui_fractal_hybrid_tab.h"

class cFractalHybridTab : public QWidget
{
	Q_OBJECT

public:
	explicit cFractalHybridTab(QWidget *parent = nullptr);
	~cFractalHybridTab() override;

	Ui::cFractalHybridTab *hybridUi() const { return ui; }

private:
	Ui::cFractalHybridTab *ui;
};

#endif // MANDELBULBER2_QT_CFRACTALHYBRIDTAB_H_

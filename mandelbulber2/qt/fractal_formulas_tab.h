/**
 * Mandelbulber v2 — fractal dock fractals tab (split from dock_fractal.ui)
 */

#ifndef MANDELBULBER2_QT_CFRACTALFORMULASTAB_H_
#define MANDELBULBER2_QT_CFRACTALFORMULASTAB_H_

#include <QWidget>

#include "ui_fractal_formulas_tab.h"

class cFractalFormulasTab : public QWidget
{
	Q_OBJECT

public:
	explicit cFractalFormulasTab(QWidget *parent = nullptr);
	~cFractalFormulasTab() override;

	Ui::cFractalFormulasTab *formulasUi() const { return ui; }

private:
	Ui::cFractalFormulasTab *ui;
};

#endif // MANDELBULBER2_QT_CFRACTALFORMULASTAB_H_

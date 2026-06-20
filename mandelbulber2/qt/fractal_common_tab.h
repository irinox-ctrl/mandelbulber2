/**
 * Mandelbulber v2 — fractal dock global parameters tab (split from dock_fractal.ui)
 */

#ifndef MANDELBULBER2_QT_CFRACTALCOMMONTAB_H_
#define MANDELBULBER2_QT_CFRACTALCOMMONTAB_H_

#include <QWidget>

#include "ui_fractal_common_tab.h"

class cFractalCommonTab : public QWidget
{
	Q_OBJECT

public:
	explicit cFractalCommonTab(QWidget *parent = nullptr);
	~cFractalCommonTab() override;

	Ui::cFractalCommonTab *commonUi() const { return ui; }

private:
	Ui::cFractalCommonTab *ui;
};

#endif // MANDELBULBER2_QT_CFRACTALCOMMONTAB_H_

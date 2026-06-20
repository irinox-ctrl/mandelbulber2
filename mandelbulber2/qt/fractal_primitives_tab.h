/**
 * Mandelbulber v2 — fractal dock primitives tab (split from dock_fractal.ui)
 */

#ifndef MANDELBULBER2_QT_CFRACTALPRIMITIVESTAB_H_
#define MANDELBULBER2_QT_CFRACTALPRIMITIVESTAB_H_

#include <QWidget>

#include "ui_fractal_primitives_tab.h"

class cFractalPrimitivesTab : public QWidget
{
	Q_OBJECT

public:
	explicit cFractalPrimitivesTab(QWidget *parent = nullptr);
	~cFractalPrimitivesTab() override;

	Ui::cFractalPrimitivesTab *primitivesUi() const { return ui; }

private:
	Ui::cFractalPrimitivesTab *ui;
};

#endif // MANDELBULBER2_QT_CFRACTALPRIMITIVESTAB_H_

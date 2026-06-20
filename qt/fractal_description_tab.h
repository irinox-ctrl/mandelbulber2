/**
 * Mandelbulber v2 — fractal dock description tab (split from dock_fractal.ui)
 */

#ifndef MANDELBULBER2_QT_CFRACTALDESCRIPTIONTAB_H_
#define MANDELBULBER2_QT_CFRACTALDESCRIPTIONTAB_H_

#include <QWidget>

#include "ui_fractal_description_tab.h"

class cFractalDescriptionTab : public QWidget
{
	Q_OBJECT

public:
	explicit cFractalDescriptionTab(QWidget *parent = nullptr);
	~cFractalDescriptionTab() override;

	Ui::cFractalDescriptionTab *descriptionUi() const { return ui; }

private:
	Ui::cFractalDescriptionTab *ui;
};

#endif // MANDELBULBER2_QT_CFRACTALDESCRIPTIONTAB_H_

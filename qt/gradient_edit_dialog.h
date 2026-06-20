/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2019-24 Mandelbulber Team
 *
 * cGradientEditDialog - enlarged popup dialog for editing gradient opacity or color
 * Designed for accessibility: larger handles, thicker lines, bigger text.
 */

#ifndef MANDELBULBER2_QT_GRADIENT_EDIT_DIALOG_H_
#define MANDELBULBER2_QT_GRADIENT_EDIT_DIALOG_H_

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>

#include "gradient_edit_widget.h"

class cGradientEditDialog : public QDialog
{
	Q_OBJECT
public:
	cGradientEditDialog(cGradientEditWidget *parentWidget,
		cGradientEditWidget::DisplayMode mode, QWidget *parent = nullptr);
	~cGradientEditDialog() override;

private:
	cGradientEditWidget *parentWidget;
	cGradientEditWidget *editWidget;
	void SyncToParent();
};

#endif /* MANDELBULBER2_QT_GRADIENT_EDIT_DIALOG_H_ */

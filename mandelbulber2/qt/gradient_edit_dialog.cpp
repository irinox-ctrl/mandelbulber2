/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2019-24 Mandelbulber Team
 *
 * cGradientEditDialog - enlarged popup dialog for editing gradient opacity or color
 */

#include "gradient_edit_dialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

cGradientEditDialog::cGradientEditDialog(cGradientEditWidget *parentWidget,
	cGradientEditWidget::DisplayMode mode, QWidget *parent)
		: QDialog(parent), parentWidget(parentWidget)
{
	QString title;
	if (mode == cGradientEditWidget::DisplayMode::OpacityOnly)
		title = tr("Edit Opacity Gradient (enlarged)");
	else if (mode == cGradientEditWidget::DisplayMode::ColorOnly)
		title = tr("Edit Color Gradient (enlarged)");
	else
		title = tr("Edit Gradient (enlarged)");
	setWindowTitle(title);

	// Large dialog for accessibility
	setMinimumSize(900, 300);
	resize(1000, 350);

	QVBoxLayout *mainLayout = new QVBoxLayout(this);

	// Help label
	QLabel *helpLabel = new QLabel(this);
	if (mode == cGradientEditWidget::DisplayMode::OpacityOnly)
	{
		helpLabel->setText(
			tr("Drag handles horizontally to move, vertically to change opacity. "
				"Double-click handles for numeric input. Right-click for menu."));
	}
	else
	{
		helpLabel->setText(tr("Drag color stops to move. Drag diamond midpoints to adjust curve. "
								  "Click a stop to change color. Right-click for menu."));
	}
	QFont helpFont = helpLabel->font();
	helpFont.setPointSize(10);
	helpLabel->setFont(helpFont);
	helpLabel->setWordWrap(true);
	mainLayout->addWidget(helpLabel);

	// The enlarged gradient widget
	editWidget = new cGradientEditWidget(this);
	editWidget->SetDisplayMode(mode);
	editWidget->SetColors(parentWidget->GetColors());
	editWidget->AssignParameterContainer(parentWidget->GetParameterContainer());
	editWidget->AssignParameterName(parentWidget->GetParameterName());
	mainLayout->addWidget(editWidget, 1);

	// Close button
	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	QPushButton *closeButton = new QPushButton(tr("Close"), this);
	QFont btnFont = closeButton->font();
	btnFont.setPointSize(11);
	btnFont.setBold(true);
	closeButton->setFont(btnFont);
	closeButton->setMinimumSize(120, 40);
	buttonLayout->addWidget(closeButton);
	buttonLayout->addStretch();
	mainLayout->addLayout(buttonLayout);

	connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);

	// Live sync: when dialog widget changes, immediately update parent widget and trigger render
	connect(editWidget, &cGradientEditWidget::gradientModified, [this]() {
		SyncToParent();
	});
}

cGradientEditDialog::~cGradientEditDialog()
{
	// Final sync before closing
	SyncToParent();
}

void cGradientEditDialog::SyncToParent()
{
	QString colors = editWidget->GetColors();
	parentWidget->SetColors(colors);
	parentWidget->update();

	// Notify system so fractal sees the change immediately
	parentWidget->NotifyGradientChanged();
}

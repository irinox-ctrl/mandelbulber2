#include "fractal_description_tab.h"
#include "ui_fractal_description_tab.h"

cFractalDescriptionTab::cFractalDescriptionTab(QWidget *parent)
		: QWidget(parent), ui(new Ui::cFractalDescriptionTab)
{
	ui->setupUi(this);
}

cFractalDescriptionTab::~cFractalDescriptionTab()
{
	delete ui;
}

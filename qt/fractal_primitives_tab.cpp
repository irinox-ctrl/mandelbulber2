#include "fractal_primitives_tab.h"
#include "ui_fractal_primitives_tab.h"

cFractalPrimitivesTab::cFractalPrimitivesTab(QWidget *parent)
		: QWidget(parent), ui(new Ui::cFractalPrimitivesTab)
{
	ui->setupUi(this);
}

cFractalPrimitivesTab::~cFractalPrimitivesTab()
{
	delete ui;
}

#include "fractal_common_tab.h"
#include "ui_fractal_common_tab.h"

cFractalCommonTab::cFractalCommonTab(QWidget *parent)
		: QWidget(parent), ui(new Ui::cFractalCommonTab)
{
	ui->setupUi(this);
}

cFractalCommonTab::~cFractalCommonTab()
{
	delete ui;
}

#include "fractal_formulas_tab.h"
#include "ui_fractal_formulas_tab.h"

cFractalFormulasTab::cFractalFormulasTab(QWidget *parent)
		: QWidget(parent), ui(new Ui::cFractalFormulasTab)
{
	ui->setupUi(this);
}

cFractalFormulasTab::~cFractalFormulasTab()
{
	delete ui;
}

#include "fractal_hybrid_tab.h"
#include "ui_fractal_hybrid_tab.h"

cFractalHybridTab::cFractalHybridTab(QWidget *parent)
		: QWidget(parent), ui(new Ui::cFractalHybridTab)
{
	ui->setupUi(this);
}

cFractalHybridTab::~cFractalHybridTab()
{
	delete ui;
}

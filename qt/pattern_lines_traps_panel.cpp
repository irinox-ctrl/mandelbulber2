#include "pattern_lines_traps_panel.h"
#include "ui_pattern_lines_traps_panel.h"

cPatternLinesTrapsPanel::cPatternLinesTrapsPanel(QWidget *parent)
		: QWidget(parent), ui(new Ui::cPatternLinesTrapsPanel)
{
	ui->setupUi(this);
}

cPatternLinesTrapsPanel::~cPatternLinesTrapsPanel()
{
	delete ui;
}

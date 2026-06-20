#include "effects_single_trap_tab.h"
#include "ui_effects_single_trap_tab.h"

cEffectsSingleTrapTab::cEffectsSingleTrapTab(QWidget *parent)
		: QWidget(parent), ui(new Ui::cEffectsSingleTrapTab)
{
	ui->setupUi(this);
}

cEffectsSingleTrapTab::~cEffectsSingleTrapTab()
{
	delete ui;
}

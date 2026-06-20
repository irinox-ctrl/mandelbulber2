#include "effects_background_tab.h"
#include "ui_effects_background_tab.h"

cEffectsBackgroundTab::cEffectsBackgroundTab(QWidget *parent)
		: QWidget(parent), ui(new Ui::cEffectsBackgroundTab)
{
	ui->setupUi(this);
}

cEffectsBackgroundTab::~cEffectsBackgroundTab()
{
	delete ui;
}

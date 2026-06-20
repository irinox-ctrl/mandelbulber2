#include "effects_post_tab.h"
#include "ui_effects_post_tab.h"

cEffectsPostTab::cEffectsPostTab(QWidget *parent)
		: QWidget(parent), ui(new Ui::cEffectsPostTab)
{
	ui->setupUi(this);
}

cEffectsPostTab::~cEffectsPostTab()
{
	delete ui;
}

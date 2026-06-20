#include "effects_lights_tab.h"
#include "ui_effects_lights_tab.h"

cEffectsLightsTab::cEffectsLightsTab(QWidget *parent)
		: QWidget(parent), ui(new Ui::cEffectsLightsTab)
{
	ui->setupUi(this);
}

cEffectsLightsTab::~cEffectsLightsTab()
{
	delete ui;
}

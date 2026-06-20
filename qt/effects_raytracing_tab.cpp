#include "effects_raytracing_tab.h"
#include "ui_effects_raytracing_tab.h"

cEffectsRaytracingTab::cEffectsRaytracingTab(QWidget *parent)
		: QWidget(parent), ui(new Ui::cEffectsRaytracingTab)
{
	ui->setupUi(this);
}

cEffectsRaytracingTab::~cEffectsRaytracingTab()
{
	delete ui;
}

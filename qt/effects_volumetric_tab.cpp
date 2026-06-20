#include "effects_volumetric_tab.h"
#include "ui_effects_volumetric_tab.h"

cEffectsVolumetricTab::cEffectsVolumetricTab(QWidget *parent)
		: QWidget(parent), ui(new Ui::cEffectsVolumetricTab)
{
	ui->setupUi(this);
}

cEffectsVolumetricTab::~cEffectsVolumetricTab()
{
	delete ui;
}

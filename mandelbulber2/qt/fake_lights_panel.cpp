#include "fake_lights_panel.h"
#include "ui_fake_lights_panel.h"

cFakeLightsPanel::cFakeLightsPanel(QWidget *parent)
		: QWidget(parent), ui(new Ui::cFakeLightsPanel)
{
	ui->setupUi(this);
}

cFakeLightsPanel::~cFakeLightsPanel()
{
	delete ui;
}

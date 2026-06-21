#include "rendering_nebula_tab.h"
#include "ui_rendering_nebula_tab.h"
cRenderingNebulaTab::cRenderingNebulaTab(QWidget *parent) : QWidget(parent), ui(new Ui::cRenderingNebulaTab) { ui->setupUi(this); }
cRenderingNebulaTab::~cRenderingNebulaTab() { delete ui; }

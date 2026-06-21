#include "rendering_netrender_tab.h"
#include "ui_rendering_netrender_tab.h"
cRenderingNetrenderTab::cRenderingNetrenderTab(QWidget *parent) : QWidget(parent), ui(new Ui::cRenderingNetrenderTab) { ui->setupUi(this); }
cRenderingNetrenderTab::~cRenderingNetrenderTab() { delete ui; }

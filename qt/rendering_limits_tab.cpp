#include "rendering_limits_tab.h"
#include "ui_rendering_limits_tab.h"
cRenderingLimitsTab::cRenderingLimitsTab(QWidget *parent) : QWidget(parent), ui(new Ui::cRenderingLimitsTab) { ui->setupUi(this); }
cRenderingLimitsTab::~cRenderingLimitsTab() { delete ui; }

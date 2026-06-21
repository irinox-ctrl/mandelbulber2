#include "rendering_fractal_shape_tab.h"
#include "ui_rendering_fractal_shape_tab.h"
cRenderingFractalShapeTab::cRenderingFractalShapeTab(QWidget *parent) : QWidget(parent), ui(new Ui::cRenderingFractalShapeTab) { ui->setupUi(this); }
cRenderingFractalShapeTab::~cRenderingFractalShapeTab() { delete ui; }

#include "material_editor_panel.h"
#include "ui_material_editor_panel.h"

cMaterialEditorPanel::cMaterialEditorPanel(QWidget *parent)
		: QWidget(parent), ui(new Ui::cMaterialEditorPanel)
{
	ui->setupUi(this);
}

cMaterialEditorPanel::~cMaterialEditorPanel()
{
	delete ui;
}

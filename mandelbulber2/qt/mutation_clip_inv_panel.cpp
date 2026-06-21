#include "mutation_clip_inv_panel.h"
#include "ui_mutation_clip_inv_panel.h"

cMutationClipInvPanel::cMutationClipInvPanel(QWidget *parent)
		: QWidget(parent), ui(new Ui::cMutationClipInvPanel)
{
	ui->setupUi(this);
}

cMutationClipInvPanel::~cMutationClipInvPanel()
{
	delete ui;
}

#include "mutation_tail_panel.h"
#include "ui_mutation_tail_panel.h"

cMutationTailPanel::cMutationTailPanel(QWidget *parent)
		: QWidget(parent), ui(new Ui::cMutationTailPanel)
{
	ui->setupUi(this);
}

cMutationTailPanel::~cMutationTailPanel()
{
	delete ui;
}

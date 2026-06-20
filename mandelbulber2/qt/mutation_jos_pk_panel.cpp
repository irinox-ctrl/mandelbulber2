#include "mutation_jos_pk_panel.h"
#include "ui_mutation_jos_pk_panel.h"

cMutationJosPkPanel::cMutationJosPkPanel(QWidget *parent)
		: QWidget(parent), ui(new Ui::cMutationJosPkPanel)
{
	ui->setupUi(this);
}

cMutationJosPkPanel::~cMutationJosPkPanel()
{
	delete ui;
}

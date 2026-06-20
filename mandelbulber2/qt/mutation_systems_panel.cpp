#include "mutation_systems_panel.h"

#include "mutation_systems_group1.h"
#include "mutation_systems_group2.h"
#include "mutation_systems_group3.h"
#include "ui_mutation_systems_panel.h"

cMutationSystemsPanel::cMutationSystemsPanel(QWidget *parent)
		: QWidget(parent), ui(new Ui::cMutationSystemsPanel)
{
	ui->setupUi(this);
}

cMutationSystemsPanel::~cMutationSystemsPanel()
{
	delete ui;
}

Ui::cMutationSystemsGroup1 *cMutationSystemsPanel::group1Ui() const
{
	return static_cast<cMutationSystemsGroup1 *>(ui->widget_mutation_systems_group1)->groupUi();
}

Ui::cMutationSystemsGroup2 *cMutationSystemsPanel::group2Ui() const
{
	return static_cast<cMutationSystemsGroup2 *>(ui->widget_mutation_systems_group2)->groupUi();
}

Ui::cMutationSystemsGroup3 *cMutationSystemsPanel::group3Ui() const
{
	return static_cast<cMutationSystemsGroup3 *>(ui->widget_mutation_systems_group3)->groupUi();
}

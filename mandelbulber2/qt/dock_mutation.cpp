#include "dock_mutation.h"
#include "ui_dock_mutation.h"
#include "dock_mutation_tab.h"
#include "src/automated_widgets.hpp"
#include "src/fractal_enums.h"

cDockMutation::cDockMutation(QWidget *parent)
		: QWidget(parent), cMyWidgetWithParams(), ui(new Ui::cDockMutation)
{
	ui->setupUi(this);
	automatedWidgets = new cAutomatedWidgets(this);
}

cDockMutation::~cDockMutation()
{
	delete ui;
}

void cDockMutation::InitializeMutationUi()
{
	mutationTabs.resize(NUMBER_OF_FRACTALS);
	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		cDockMutationTab *tab = new cDockMutationTab(ui->tabWidget_mutations);
		tab->AssignParameterContainers(params, fractalParams);
		tab->Init(i);
		mutationTabs[i] = tab;
		ui->tabWidget_mutations->addTab(tab, QString("Fractal %1").arg(i + 1));
	}
}

void cDockMutation::SynchronizeInterfaceMutation(std::shared_ptr<cParameterContainer> par,
	qInterface::enumReadWrite mode)
{
	for (cDockMutationTab *tab : mutationTabs)
	{
		if (tab) tab->SynchronizeInterface(par, mode);
	}
}

void cDockMutation::UpdateMutationFieldVisibility(int tabIndex, int formulaIndex)
{
	if (tabIndex >= 0 && tabIndex < mutationTabs.size() && mutationTabs[tabIndex])
	{
		mutationTabs[tabIndex]->UpdateMutationFieldVisibility(formulaIndex);
	}
}

void cDockMutation::UpdateMutationGrayOut(int tabIndex)
{
	if (tabIndex >= 0 && tabIndex < mutationTabs.size() && mutationTabs[tabIndex])
	{
		mutationTabs[tabIndex]->UpdateMutationGrayOut();
	}
}

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

	// Larger fonts and widgets for readability
	setStyleSheet(
		"QWidget { font-size: 14px; }"
		"QLabel { font-size: 13px; font-weight: bold; }"
		"QSpinBox, QDoubleSpinBox, MyDoubleSpinBox { min-width: 90px; padding: 2px; }"
		"QComboBox { min-width: 140px; padding: 2px; }"
		"QCheckBox, QGroupBox { font-size: 14px; }"
		"QSlider::groove:horizontal { height: 10px; }"
		"QSlider::handle:horizontal { width: 18px; height: 18px; }"
		"QTabBar::tab { font-size: 13px; padding: 6px 12px; }"
	);
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

void cDockMutation::UpdateTabTitle(int tabIndex, const QString &title)
{
	if (tabIndex >= 0 && tabIndex < ui->tabWidget_mutations->count())
	{
		ui->tabWidget_mutations->setTabText(tabIndex, title);
	}
}

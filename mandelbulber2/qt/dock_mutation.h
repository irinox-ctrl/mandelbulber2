#ifndef MANDELBULBER2_QT_DOCK_MUTATION_H_
#define MANDELBULBER2_QT_DOCK_MUTATION_H_

#include <QWidget>
#include "my_widget_with_params.h"
#include "src/parameters.hpp"
#include "src/synchronize_interface.hpp"

class cAutomatedWidgets;
class cDockMutationTab;

namespace Ui
{
class cDockMutation;
}

class cDockMutation : public QWidget, public cMyWidgetWithParams
{
	Q_OBJECT
public:
	explicit cDockMutation(QWidget *parent = nullptr);
	~cDockMutation() override;

	void InitializeMutationUi();
	void SynchronizeInterfaceMutation(std::shared_ptr<cParameterContainer> par,
		qInterface::enumReadWrite mode);
	void UpdateMutationFieldVisibility(int tabIndex, int formulaIndex);
	void UpdateMutationGrayOut(int tabIndex);

private:
	Ui::cDockMutation *ui;
	QVector<cDockMutationTab *> mutationTabs;
	cAutomatedWidgets *automatedWidgets;
};

#endif

/**
 * Mandelbulber v2, a 3D fractal generator
 * cDockMutationTab - mutation controls for one fractal
 */

#ifndef MANDELBULBER2_QT_DOCK_MUTATION_TAB_H_
#define MANDELBULBER2_QT_DOCK_MUTATION_TAB_H_

#include <memory>
#include <QSet>
#include <QString>
#include <QWidget>
#include <QPropertyAnimation>
#include "my_widget_with_params.h"
#include "src/synchronize_interface.hpp"

class cAutomatedWidgets;
class cDockMutation;

namespace Ui
{
class cDockMutationTab;
}

class cDockMutationTab : public QWidget, public cMyWidgetWithParams
{
	Q_OBJECT
public:
	explicit cDockMutationTab(QWidget *parent = nullptr);
	~cDockMutationTab() override;

	void Init(int _tabIndex);
	void InitWidgetNames() const;
	void SynchronizeInterface(std::shared_ptr<cParameterContainer> par,
		qInterface::enumReadWrite mode);

	void UpdateMutationFieldVisibility(int formulaIndex) const;
	void UpdateMutationGrayOut() const;

private slots:
	void slotPressedButtonMutationReset();
	void slotPressedButtonRandomizeWeights();
	void slotPressedButtonResetWeights();
	void slotPressedButtonResetSectionWeights();

private:
	void ConnectSignals();
	void SetupTooltips() const;
	void toggleSection(QGroupBox *sec, bool open, int titleHeight) const;
	void MarkFormulaHiddenWidgets(const QStringList &names, bool hidden) const;

	Ui::cDockMutationTab *ui;
	int tabIndex;
	cAutomatedWidgets *automatedWidgets;
	mutable QSet<QString> m_formulaHiddenWidgets;
};

#endif // MANDELBULBER2_QT_DOCK_MUTATION_TAB_H_

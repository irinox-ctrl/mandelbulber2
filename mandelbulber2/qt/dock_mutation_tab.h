/**
 * Mandelbulber v2, a 3D fractal generator
 * cDockMutationTab - mutation controls for one fractal
 */

#ifndef MANDELBULBER2_QT_DOCK_MUTATION_TAB_H_
#define MANDELBULBER2_QT_DOCK_MUTATION_TAB_H_

#include <memory>
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

struct sMutationState
{
	int josType = -1;
	int pkType = -1;
	int mbType = -1;
	int foldType = -1;
	int warpType = -1;
	int mathType = -1;
	int swizzle = -1;
	int orbitTrap = -1;
	int deTweak = -1;
	int juliaInjection = -1;
	int juliaCTransform = -1;
	int juliaDynamic = -1;
	int juliaMulti = -1;
	int juliaStart = -1;
	bool mutEnabled = false;
	bool operator==(const sMutationState &o) const
	{
		return josType == o.josType && pkType == o.pkType && mbType == o.mbType
			&& foldType == o.foldType && warpType == o.warpType && mathType == o.mathType
			&& swizzle == o.swizzle && orbitTrap == o.orbitTrap && deTweak == o.deTweak
			&& juliaInjection == o.juliaInjection && juliaCTransform == o.juliaCTransform
			&& juliaDynamic == o.juliaDynamic && juliaMulti == o.juliaMulti
			&& juliaStart == o.juliaStart && mutEnabled == o.mutEnabled;
	}
};

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
	void SetMutationWidgetsEnabled(const QStringList &names, bool enabled) const;

	Ui::cDockMutationTab *ui;
	int tabIndex;
	cAutomatedWidgets *automatedWidgets;
	mutable sMutationState m_lastGrayState;
};

#endif // MANDELBULBER2_QT_DOCK_MUTATION_TAB_H_

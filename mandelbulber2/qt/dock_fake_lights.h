/**
 * Mandelbulber v2 — dock UI for fake lights (orbit trap lights).
 */

#ifndef MANDELBULBER2_QT_DOCK_FAKE_LIGHTS_H_
#define MANDELBULBER2_QT_DOCK_FAKE_LIGHTS_H_

#include <QWidget>

#include "my_widget_with_params.h"
#include "src/parameters.hpp"

class cAutomatedWidgets;

namespace Ui
{
class cDockFakeLights;
}

class cDockFakeLights : public QWidget, public cMyWidgetWithParams
{
	Q_OBJECT

public:
	explicit cDockFakeLights(QWidget *parent = nullptr);
	~cDockFakeLights() override;

	virtual void AssignParameterContainers(std::shared_ptr<cParameterContainer> _params,
		std::shared_ptr<cFractalContainer> _fractalParams) override;
	virtual void AssignSpecialWidgets(
		RenderedImage *_renderedImage, QComboBox *_mouseFunctionCombo) override;

public slots:
	void slotSynchronizeInterfaceFakeLights(std::shared_ptr<cParameterContainer> par);

private slots:
	void slotPressedButtonNavi();
	void slotNewParametersFromNavi();
	void slotPressedButtonResetWorld();
	void slotPressedButtonResetCamera();
	void slotPressedButtonResetTarget();
	void slotPressedButtonResetFractalCenter();
	void slotPressedButtonResetPathCircle();
	void slotPressedButtonResetPathSpiral();
	void slotPressedButtonResetOrbitTarget();
	void slotPressedButtonResetMultiCenter();

private:
	void ConnectSignals() const;

	Ui::cDockFakeLights *ui;
	cAutomatedWidgets *automatedWidgets;
};

#endif /* MANDELBULBER2_QT_DOCK_FAKE_LIGHTS_H_ */

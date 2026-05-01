/**
 * Mandelbulber v2 — dock UI for fake lights (orbit trap lights).
 */

#include "dock_fake_lights.h"
#include "ui_dock_fake_lights.h"

#include "src/automated_widgets.hpp"
#include "src/fractal_container.hpp"
#include "src/global_data.hpp"
#include "src/interface.hpp"
#include "src/global_data.hpp"
#include "src/initparameters.hpp"
#include "src/interface.hpp"
#include "src/synchronize_interface.hpp"

cDockFakeLights::cDockFakeLights(QWidget *parent)
		: QWidget(parent), cMyWidgetWithParams(), ui(new Ui::cDockFakeLights)
{
	ui->setupUi(this);

	automatedWidgets = new cAutomatedWidgets(this);
	automatedWidgets->ConnectSignalsForSlidersInWindow(this);
	ConnectSignals();
}

cDockFakeLights::~cDockFakeLights()
{
	delete ui;
}

void cDockFakeLights::AssignParameterContainers(
	std::shared_ptr<cParameterContainer> _params, std::shared_ptr<cFractalContainer> _fractalParams)
{
	cMyWidgetWithParams::AssignParameterContainers(_params, _fractalParams);
}

void cDockFakeLights::AssignSpecialWidgets(
	RenderedImage *_renderedImage, QComboBox *_mouseFunctionCombo)
{
	cMyWidgetWithParams::AssignSpecialWidgets(_renderedImage, _mouseFunctionCombo);
}

void cDockFakeLights::ConnectSignals() const
{
	connect(ui->comboBox_fake_lights_position_mode, SIGNAL(currentIndexChanged(int)),
		ui->stackedWidget_fake_lights_mode, SLOT(setCurrentIndex(int)));

	connect(ui->pushButton_reset_world, SIGNAL(clicked()), this, SLOT(slotPressedButtonResetWorld()));
	connect(ui->pushButton_reset_camera, SIGNAL(clicked()), this, SLOT(slotPressedButtonResetCamera()));
	connect(ui->pushButton_reset_target, SIGNAL(clicked()), this, SLOT(slotPressedButtonResetTarget()));
	connect(ui->pushButton_reset_fractal_center, SIGNAL(clicked()), this,
		SLOT(slotPressedButtonResetFractalCenter()));
	connect(ui->pushButton_reset_path_circle, SIGNAL(clicked()), this,
		SLOT(slotPressedButtonResetPathCircle()));
	connect(ui->pushButton_reset_path_spiral, SIGNAL(clicked()), this,
		SLOT(slotPressedButtonResetPathSpiral()));
	connect(ui->pushButton_reset_orbit_target, SIGNAL(clicked()), this,
		SLOT(slotPressedButtonResetOrbitTarget()));
	connect(ui->pushButton_reset_multi_center, SIGNAL(clicked()), this,
		SLOT(slotPressedButtonResetMultiCenter()));
}

void cDockFakeLights::slotSynchronizeInterfaceFakeLights(
	std::shared_ptr<cParameterContainer> par)
{
	SynchronizeInterfaceWindow(this, par, qInterface::write);
}

void cDockFakeLights::slotPressedButtonNavi()
{
	// Not used in this dock; kept for potential future use
}

void cDockFakeLights::slotNewParametersFromNavi()
{
	// Not used in this dock; kept for potential future use
}

void cDockFakeLights::slotPressedButtonResetWorld()
{
	gPar->Set("fake_lights_world_offset", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_world_scale", 1.0);
	gPar->Set("fake_lights_world_rotation", CVector3(0.0, 0.0, 0.0));
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockFakeLights::slotPressedButtonResetCamera()
{
	gPar->Set("fake_lights_camera_offset", CVector3(2.0, 0.0, 0.0));
	gPar->Set("fake_lights_camera_scale", 1.0);
	gPar->Set("fake_lights_camera_rotation", CVector3(0.0, 0.0, 0.0));
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockFakeLights::slotPressedButtonResetTarget()
{
	gPar->Set("fake_lights_target_offset", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_target_scale", 1.0);
	gPar->Set("fake_lights_target_rotation", CVector3(0.0, 0.0, 0.0));
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockFakeLights::slotPressedButtonResetFractalCenter()
{
	gPar->Set("fake_lights_fractal_center_offset", CVector3(0.0, 0.0, 1.0));
	gPar->Set("fake_lights_fractal_center_scale", 1.0);
	gPar->Set("fake_lights_fractal_center_rotation", CVector3(0.0, 0.0, 0.0));
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockFakeLights::slotPressedButtonResetPathCircle()
{
	gPar->Set("fake_lights_path_circle_offset", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_path_circle_scale", 1.0);
	gPar->Set("fake_lights_path_circle_rotation", CVector3(0.0, 45.0, 0.0));
	gPar->Set("fake_lights_path_circle_path_radius", 2.0);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockFakeLights::slotPressedButtonResetPathSpiral()
{
	gPar->Set("fake_lights_path_spiral_offset", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_path_spiral_scale", 1.0);
	gPar->Set("fake_lights_path_spiral_rotation", CVector3(0.0, 90.0, 0.0));
	gPar->Set("fake_lights_path_spiral_path_radius", 2.0);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockFakeLights::slotPressedButtonResetOrbitTarget()
{
	gPar->Set("fake_lights_orbit_target_offset", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_orbit_target_scale", 1.0);
	gPar->Set("fake_lights_orbit_target_rotation", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_orbit_target_path_radius", 2.0);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockFakeLights::slotPressedButtonResetMultiCenter()
{
	gPar->Set("fake_lights_multi_center_enabled", false);
	gPar->Set("fake_lights_multi_center_1", CVector3(1.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_2", CVector3(0.0, 1.0, 0.0));
	gPar->Set("fake_lights_multi_center_3", CVector3(0.0, 0.0, 1.0));
	gPar->Set("fake_lights_multi_center_4", CVector3(-1.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_weight_1", 1.0);
	gPar->Set("fake_lights_multi_center_weight_2", 1.0);
	gPar->Set("fake_lights_multi_center_weight_3", 1.0);
	gPar->Set("fake_lights_multi_center_weight_4", 1.0);
	gPar->Set("fake_lights_multi_center_color_1", sRGB(65535, 0, 0));
	gPar->Set("fake_lights_multi_center_color_2", sRGB(0, 65535, 0));
	gPar->Set("fake_lights_multi_center_color_3", sRGB(0, 0, 65535));
	gPar->Set("fake_lights_multi_center_color_4", sRGB(65535, 65535, 0));
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

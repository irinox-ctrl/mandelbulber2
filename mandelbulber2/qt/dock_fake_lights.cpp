/**
 * Mandelbulber v2 — dock UI for fake lights (orbit trap lights).
 */

#include "dock_fake_lights.h"
#include "ui_dock_fake_lights.h"
#include "fake_lights_panel.h"

#define FAKE_UI (static_cast<cFakeLightsPanel*>(ui->widget_fake_lights_panel)->fakeLightsUi())

#include "src/automated_widgets.hpp"
#include "src/fractal_container.hpp"
#include "src/global_data.hpp"
#include "src/interface.hpp"
#include "qt_utils.h"
#include "src/initparameters.hpp"
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

void cDockFakeLights::ConnectSignals()
{
	connect(FAKE_UI->comboBox_fake_lights_position_mode,
		QOverload<int>::of(&QComboBox::currentIndexChanged),
		FAKE_UI->stackedWidget_fake_lights_mode, &QStackedWidget::setCurrentIndex);

	connect(FAKE_UI->pushButton_reset_world, &QPushButton::clicked, this,
		&cDockFakeLights::slotPressedButtonResetWorld);
	connect(FAKE_UI->pushButton_reset_camera, &QPushButton::clicked, this,
		&cDockFakeLights::slotPressedButtonResetCamera);
	connect(FAKE_UI->pushButton_reset_target, &QPushButton::clicked, this,
		&cDockFakeLights::slotPressedButtonResetTarget);
	connect(FAKE_UI->pushButton_reset_fractal_center, &QPushButton::clicked, this,
		&cDockFakeLights::slotPressedButtonResetFractalCenter);
	connect(FAKE_UI->pushButton_reset_path_circle, &QPushButton::clicked, this,
		&cDockFakeLights::slotPressedButtonResetPathCircle);
	connect(FAKE_UI->pushButton_reset_path_spiral, &QPushButton::clicked, this,
		&cDockFakeLights::slotPressedButtonResetPathSpiral);
	connect(FAKE_UI->pushButton_reset_orbit_target, &QPushButton::clicked, this,
		&cDockFakeLights::slotPressedButtonResetOrbitTarget);
	connect(FAKE_UI->pushButton_reset_multi_center, &QPushButton::clicked, this,
		&cDockFakeLights::slotPressedButtonResetMultiCenter);
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
	CHECK_MAIN_INTERFACE();
	gPar->Set("fake_lights_world_offset", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_world_scale", 1.0);
	gPar->Set("fake_lights_world_rotation", CVector3(0.0, 0.0, 0.0));
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockFakeLights::slotPressedButtonResetCamera()
{
	CHECK_MAIN_INTERFACE();
	gPar->Set("fake_lights_camera_offset", CVector3(2.0, 0.0, 0.0));
	gPar->Set("fake_lights_camera_scale", 1.0);
	gPar->Set("fake_lights_camera_rotation", CVector3(0.0, 0.0, 0.0));
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockFakeLights::slotPressedButtonResetTarget()
{
	CHECK_MAIN_INTERFACE();
	gPar->Set("fake_lights_target_offset", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_target_scale", 1.0);
	gPar->Set("fake_lights_target_rotation", CVector3(0.0, 0.0, 0.0));
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockFakeLights::slotPressedButtonResetFractalCenter()
{
	CHECK_MAIN_INTERFACE();
	gPar->Set("fake_lights_fractal_center_offset", CVector3(0.0, 0.0, 1.0));
	gPar->Set("fake_lights_fractal_center_scale", 1.0);
	gPar->Set("fake_lights_fractal_center_rotation", CVector3(0.0, 0.0, 0.0));
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockFakeLights::slotPressedButtonResetPathCircle()
{
	CHECK_MAIN_INTERFACE();
	gPar->Set("fake_lights_path_circle_offset", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_path_circle_scale", 1.0);
	gPar->Set("fake_lights_path_circle_rotation", CVector3(0.0, 45.0, 0.0));
	gPar->Set("fake_lights_path_circle_path_radius", 2.0);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockFakeLights::slotPressedButtonResetPathSpiral()
{
	CHECK_MAIN_INTERFACE();
	gPar->Set("fake_lights_path_spiral_offset", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_path_spiral_scale", 1.0);
	gPar->Set("fake_lights_path_spiral_rotation", CVector3(0.0, 90.0, 0.0));
	gPar->Set("fake_lights_path_spiral_path_radius", 2.0);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockFakeLights::slotPressedButtonResetOrbitTarget()
{
	CHECK_MAIN_INTERFACE();
	gPar->Set("fake_lights_orbit_target_offset", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_orbit_target_scale", 1.0);
	gPar->Set("fake_lights_orbit_target_rotation", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_orbit_target_path_radius", 2.0);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockFakeLights::slotPressedButtonResetMultiCenter()
{
	CHECK_MAIN_INTERFACE();
	gPar->Set("fake_lights_multi_center_enabled", false);
	gPar->Set("fake_lights_multi_center_1", CVector3(1.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_2", CVector3(0.0, 1.0, 0.0));
	gPar->Set("fake_lights_multi_center_3", CVector3(0.0, 0.0, 1.0));
	gPar->Set("fake_lights_multi_center_4", CVector3(-1.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_5", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_6", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_7", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_8", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_9", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_10", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_11", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_12", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_13", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_14", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_15", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_16", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_17", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_18", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_19", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_20", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_21", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_22", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_23", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_24", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_weight_1", 1.0);
	gPar->Set("fake_lights_multi_center_weight_2", 1.0);
	gPar->Set("fake_lights_multi_center_weight_3", 1.0);
	gPar->Set("fake_lights_multi_center_weight_4", 1.0);
	gPar->Set("fake_lights_multi_center_weight_5", 1.0);
	gPar->Set("fake_lights_multi_center_weight_6", 1.0);
	gPar->Set("fake_lights_multi_center_weight_7", 1.0);
	gPar->Set("fake_lights_multi_center_weight_8", 1.0);
	gPar->Set("fake_lights_multi_center_weight_9", 1.0);
	gPar->Set("fake_lights_multi_center_weight_10", 1.0);
	gPar->Set("fake_lights_multi_center_weight_11", 1.0);
	gPar->Set("fake_lights_multi_center_weight_12", 1.0);
	gPar->Set("fake_lights_multi_center_weight_13", 1.0);
	gPar->Set("fake_lights_multi_center_weight_14", 1.0);
	gPar->Set("fake_lights_multi_center_weight_15", 1.0);
	gPar->Set("fake_lights_multi_center_weight_16", 1.0);
	gPar->Set("fake_lights_multi_center_weight_17", 1.0);
	gPar->Set("fake_lights_multi_center_weight_18", 1.0);
	gPar->Set("fake_lights_multi_center_weight_19", 1.0);
	gPar->Set("fake_lights_multi_center_weight_20", 1.0);
	gPar->Set("fake_lights_multi_center_weight_21", 1.0);
	gPar->Set("fake_lights_multi_center_weight_22", 1.0);
	gPar->Set("fake_lights_multi_center_weight_23", 1.0);
	gPar->Set("fake_lights_multi_center_weight_24", 1.0);
	gPar->Set("fake_lights_multi_center_color_1", sRGB(65535, 0, 0));
	gPar->Set("fake_lights_multi_center_color_2", sRGB(0, 65535, 0));
	gPar->Set("fake_lights_multi_center_color_3", sRGB(0, 0, 65535));
	gPar->Set("fake_lights_multi_center_color_4", sRGB(65535, 65535, 0));
	gPar->Set("fake_lights_multi_center_color_5", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_6", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_7", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_8", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_9", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_10", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_11", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_12", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_13", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_14", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_15", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_16", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_17", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_18", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_19", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_20", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_21", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_22", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_23", sRGB(65535, 65535, 65535));
	gPar->Set("fake_lights_multi_center_color_24", sRGB(65535, 65535, 65535));
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2016-23 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
 *                                        ,=mm=§M ]=4 yJKA"/-Nsaj  "Bw,==,,
 * This file is part of Mandelbulber.    §R.r= jw",M  Km .mM  FW ",§=ß., ,TN
 *                                     ,4R =%["w[N=7]J '"5=],""]]M,w,-; T=]M
 * Mandelbulber is free software:     §R.ß~-Q/M=,=5"v"]=Qf,'§"M= =,M.§ Rz]M"Kw
 * you can redistribute it and/or     §w "xDY.J ' -"m=====WeC=\ ""%""y=%"]"" §
 * modify it under the terms of the    "§M=M =D=4"N #"%==A%p M§ M6  R' #"=~.4M
 * GNU General Public License as        §W =, ][T"]C  §  § '§ e===~ U  !§[Z ]N
 * published by the                    4M",,Jm=,"=e~  §  §  j]]""N  BmM"py=ßM
 * Free Software Foundation,          ]§ T,M=& 'YmMMpM9MMM%=w=,,=MT]M m§;'§,
 * either version 3 of the License,    TWw [.j"5=~N[=§%=%W,T ]R,"=="Y[LFT ]N
 * or (at your option)                   TW=,-#"%=;[  =Q:["V""  ],,M.m == ]N
 * any later version.                      J§"mr"] ,=,," =="""J]= M"M"]==ß"
 *                                          §= "=C=4 §"eM "=B:m|4"]#F,§~
 * Mandelbulber is distributed in            "9w=,,]w em%wJ '"~" ,=,,ß"
 * the hope that it will be useful,                 . "K=  ,=RMMMßM"""
 * but WITHOUT ANY WARRANTY;                            .'''
 * without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with Mandelbulber. If not, see <http://www.gnu.org/licenses/>.
 *
 * ###########################################################################
 *
 * Authors: Krzysztof Marczak (buddhi1980@gmail.com)
 *
 * Widget which contains UI for navigation
 */

#include "dock_navigation.h"

#include "ui_dock_navigation.h"

#include "dock_image_adjustments.h"
#include "navigator_window.h"

#include "src/automated_widgets.hpp"
#include "src/camera_movement_modes.h"
#include "src/fractal_container.hpp"
#include "src/initparameters.hpp"
#include "src/interface.hpp"
#include "src/manipulations.h"
#include "src/render_window.hpp"
#include "src/system.hpp"
#include "src/system_directories.hpp"
#include "src/write_log.hpp"

#include <QApplication>
#include <QClipboard>
#include <QDateTime>
#include <QDir>
#include <QFileDialog>
#include <QGroupBox>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QListWidget>
#include <QCheckBox>
#include <QPropertyAnimation>
#include <QSlider>

cDockNavigation::cDockNavigation(QWidget *parent) : QWidget(parent), ui(new Ui::cDockNavigation)
{
	ui->setupUi(this);
	automatedWidgets = new cAutomatedWidgets(this);
	automatedWidgets->ConnectSignalsForSlidersInWindow(this);
	manipulations = new cManipulations(this);
	ConnectSignals();
	SetIconSizes();
	SetupCollapsibleSections();
	SetupQuickPresets();
	SetupBookmarks();
	SetupSmartCamera();
#ifdef USE_MPFR
	SetupDeepZoom();
#endif
}

cDockNavigation::~cDockNavigation()
{
	delete ui;
}

void cDockNavigation::AssignParameterContainers(
	std::shared_ptr<cParameterContainer> _params, std::shared_ptr<cFractalContainer> _fractalParams)
{
	params = _params;
	fractalParams = _fractalParams;
	manipulations->AssignParameterContainers(_params, _fractalParams);
	if (smartCamera)
		smartCamera->AssignParameters(_params, _fractalParams);
	manipulations->AssignWidgets(nullptr, this, nullptr, nullptr);
}

void cDockNavigation::RenderButtonSetEnabled(bool enabled) const
{
	ui->pushButton_render->setEnabled(enabled);
}

void cDockNavigation::AutoRefreshSetChecked(bool state) const
{
	ui->checkBox_auto_refresh->setChecked(state);
}

bool cDockNavigation::AutoRefreshIsChecked() const
{
	return ui->checkBox_auto_refresh->isChecked();
}

void cDockNavigation::slotUndo()
{
	gMainInterface->Undo();
}

void cDockNavigation::slotRedo()
{
	gMainInterface->Redo();
}

void cDockNavigation::SetIconSizes()
{
	QFontMetrics fm(font());
	int pixelFontSize = fm.height();
	QSize iconSize(int(pixelFontSize * 3.2), int(pixelFontSize * 3.2));
	ui->bu_move_backward->setIconSize(iconSize);
	ui->bu_move_down->setIconSize(iconSize);
	ui->bu_move_forward->setIconSize(iconSize);
	ui->bu_move_left->setIconSize(iconSize);
	ui->bu_move_right->setIconSize(iconSize);
	ui->bu_move_up->setIconSize(iconSize);
	ui->bu_rotate_down->setIconSize(iconSize);
	ui->bu_rotate_left->setIconSize(iconSize);
	ui->bu_rotate_right->setIconSize(iconSize);
	ui->bu_rotate_roll_left->setIconSize(iconSize);
	ui->bu_rotate_roll_right->setIconSize(iconSize);
	ui->bu_rotate_up->setIconSize(iconSize);
}

void cDockNavigation::ConnectSignals() const
{
	// ------------ camera manipulation -----------
	connect(ui->bu_move_up, SIGNAL(clicked()), this, SLOT(slotCameraMove()));
	connect(ui->bu_move_down, SIGNAL(clicked()), this, SLOT(slotCameraMove()));
	connect(ui->bu_move_left, SIGNAL(clicked()), this, SLOT(slotCameraMove()));
	connect(ui->bu_move_right, SIGNAL(clicked()), this, SLOT(slotCameraMove()));
	connect(ui->bu_move_forward, SIGNAL(clicked()), this, SLOT(slotCameraMove()));
	connect(ui->bu_move_backward, SIGNAL(clicked()), this, SLOT(slotCameraMove()));

	connect(ui->bu_rotate_up, SIGNAL(clicked()), this, SLOT(slotCameraRotation()));
	connect(ui->bu_rotate_down, SIGNAL(clicked()), this, SLOT(slotCameraRotation()));
	connect(ui->bu_rotate_left, SIGNAL(clicked()), this, SLOT(slotCameraRotation()));
	connect(ui->bu_rotate_right, SIGNAL(clicked()), this, SLOT(slotCameraRotation()));
	connect(ui->bu_rotate_roll_left, SIGNAL(clicked()), this, SLOT(slotCameraRotation()));
	connect(ui->bu_rotate_roll_right, SIGNAL(clicked()), this, SLOT(slotCameraRotation()));

	connect(ui->vect3_camera_x, SIGNAL(editingFinished()), this, SLOT(slotCameraOrTargetEdited()));
	connect(ui->vect3_camera_y, SIGNAL(editingFinished()), this, SLOT(slotCameraOrTargetEdited()));
	connect(ui->vect3_camera_z, SIGNAL(editingFinished()), this, SLOT(slotCameraOrTargetEdited()));
	connect(ui->vect3_target_x, SIGNAL(editingFinished()), this, SLOT(slotCameraOrTargetEdited()));
	connect(ui->vect3_target_y, SIGNAL(editingFinished()), this, SLOT(slotCameraOrTargetEdited()));
	connect(ui->vect3_target_z, SIGNAL(editingFinished()), this, SLOT(slotCameraOrTargetEdited()));
	connect(ui->vect3_camera_rotation_x, SIGNAL(editingFinished()), this, SLOT(slotRotationEdited()));
	connect(ui->vect3_camera_rotation_y, SIGNAL(editingFinished()), this, SLOT(slotRotationEdited()));
	connect(ui->vect3_camera_rotation_z, SIGNAL(editingFinished()), this, SLOT(slotRotationEdited()));
	connect(ui->logedit_camera_distance_to_target, SIGNAL(editingFinished()), this,
		SLOT(slotCameraDistanceEdited()));
	connect(ui->comboBox_camera_absolute_distance_mode, SIGNAL(currentIndexChanged(int)), this,
		SLOT(slotMovementStepModeChanged(int)));
	connect(ui->comboBox_camera_movement_mode, SIGNAL(currentIndexChanged(int)), this,
		SLOT(slotCameraMovementModeChanged(int)));
	connect(ui->pushButton_undo, SIGNAL(clicked()), this, SLOT(slotUndo()));
	connect(ui->pushButton_redo, SIGNAL(clicked()), this, SLOT(slotRedo()));
	connect(ui->pushButton_render, SIGNAL(clicked()), this, SLOT(slotStartRender()));

	connect(ui->pushButton_stop, SIGNAL(clicked()), this, SLOT(slotStopRender()));
	connect(ui->pushButton_reset_view, SIGNAL(clicked()), this, SLOT(slotPressedButtonResetView()));
	connect(ui->comboBox_opencl_mode, SIGNAL(currentIndexChanged(int)), this,
		SLOT(slotChangedOpenCLMode(int)));
	connect(
		ui->pushButton_openNavigator, &QPushButton::clicked, this, &cDockNavigation::slotOpenNavigator);
}

void cDockNavigation::slotCameraMove()
{
	QString buttonName = sender()->objectName();

	// get data from interface
	QWidget *dock = const_cast<cDockNavigation *>(this);
	SynchronizeInterfaceWindow(dock, params, qInterface::read);

	manipulations->MoveCamera(buttonName);

	SynchronizeInterfaceWindow(dock, params, qInterface::write);
	emit signalRender();
}

void cDockNavigation::slotCameraRotation()
{
	QString buttonName = sender()->objectName();

	// get data from interface
	QWidget *dock = const_cast<cDockNavigation *>(this);
	SynchronizeInterfaceWindow(dock, params, qInterface::read);

	manipulations->RotateCamera(buttonName);

	SynchronizeInterfaceWindow(dock, params, qInterface::write);
	emit signalRender();
}

void cDockNavigation::slotCameraOrTargetEdited()
{
	manipulations->CameraOrTargetEdited();
}

void cDockNavigation::slotRotationEdited()
{
	manipulations->RotationEdited();
}

void cDockNavigation::slotCameraDistanceEdited()
{
	manipulations->CameraDistanceEdited();
}

void cDockNavigation::slotCameraDistanceSlider(int value)
{
	(void)value;
	manipulations->CameraDistanceEdited();
}

void cDockNavigation::slotMovementStepModeChanged(int index)
{
	manipulations->MovementStepModeChanged(index);
}

void cDockNavigation::slotPressedButtonResetView()
{
	QWidget *dock = const_cast<cDockNavigation *>(this);
	cInterface::ResetView(dock, params, fractalParams);
	emit signalRender();
}

void cDockNavigation::slotStartRender()
{
	emit signalRender();
}

void cDockNavigation::slotStopRender()
{
	emit signalStop();
}

void cDockNavigation::LockAllFunctions() const
{
	ui->scrollArea_navi->setEnabled(false);
	ui->pushButton_render->setEnabled(false);
	ui->pushButton_undo->setEnabled(false);
	ui->pushButton_redo->setEnabled(false);
}

void cDockNavigation::UnlockAllFunctions() const
{
	ui->scrollArea_navi->setEnabled(true);
	ui->pushButton_render->setEnabled(true);
	ui->pushButton_undo->setEnabled(true);
	ui->pushButton_redo->setEnabled(true);
}

void cDockNavigation::slotCameraMovementModeChanged(int index)
{
	emit signalCameraMovementModeChanged(index);
}

void cDockNavigation::EnableOpenCLModeComboBox(bool enabled) const
{
	ui->comboBox_opencl_mode->setVisible(enabled);
	ui->label_opencl_mode->setVisible(enabled);
}

void cDockNavigation::HideSomeButtons()
{
	ui->pushButton_undo->hide();
	ui->pushButton_redo->hide();
	ui->pushButton_openNavigator->hide();
	ui->checkBox_auto_refresh->hide();
}

void cDockNavigation::slotChangedOpenCLMode(int index)
{
	// FIXME: to make it working only for main window
	gMainInterface->mainWindow->GetWidgetDockImageAdjustments()->SetAntialiasingOpenCL(
		index > 0 && gPar->Get<bool>("opencl_enabled"));
}

void cDockNavigation::slotOpenNavigator()
{
	gMainInterface->SynchronizeInterface(params, fractalParams, qInterface::read);
	cNavigatorWindow *navigator = new cNavigatorWindow();
	navigator->setAttribute(Qt::WA_DeleteOnClose);
	navigator->SetInitialParameters(gPar, gParFractal);
	navigator->SynchronizeInterface(qInterface::write);
	navigator->SetMouseClickFunction(gMainInterface->GetMouseClickFunction());
	navigator->show();
	navigator->AllPrepared();
}

// --- 3x3lion Navigation Upgrades ---

void cDockNavigation::SetupCollapsibleSections()
{
	QList<QGroupBox *> groups = {
		ui->groupBox_coordinates,
		ui->groupBox_rotation,
		ui->groupBox_11  // sweet spot
	};

	for (QGroupBox *box : groups)
	{
		box->setCheckable(true);
		box->setChecked(true);
		box->setProperty("collapsible", true);
		connect(box, &QGroupBox::toggled, [box](bool checked) {
			for (QObject *child : box->children())
			{
				QWidget *w = qobject_cast<QWidget *>(child);
				if (w) w->setVisible(checked);
			}
		});
	}

	// Sweet spot collapsed by default
	ui->groupBox_11->setChecked(false);
	for (QObject *child : ui->groupBox_11->children())
	{
		QWidget *w = qobject_cast<QWidget *>(child);
		if (w) w->setVisible(false);
	}
}

void cDockNavigation::SetupQuickPresets()
{
	// Quick presets are added via .ui file; connect them here
	if (ui->pushButton_view_home)
		connect(ui->pushButton_view_home, &QPushButton::clicked, this,
			&cDockNavigation::slotQuickViewHome);
	if (ui->pushButton_view_top)
		connect(ui->pushButton_view_top, &QPushButton::clicked, this,
			&cDockNavigation::slotQuickViewTop);
	if (ui->pushButton_view_front)
		connect(ui->pushButton_view_front, &QPushButton::clicked, this,
			&cDockNavigation::slotQuickViewFront);
	if (ui->pushButton_view_right)
		connect(ui->pushButton_view_right, &QPushButton::clicked, this,
			&cDockNavigation::slotQuickViewRight);

	// Copy/paste buttons
	if (ui->pushButton_copy_camera)
		connect(ui->pushButton_copy_camera, &QPushButton::clicked, this,
			&cDockNavigation::slotCopyCameraCoords);
	if (ui->pushButton_paste_camera)
		connect(ui->pushButton_paste_camera, &QPushButton::clicked, this,
			&cDockNavigation::slotPasteCameraCoords);
	if (ui->pushButton_copy_target)
		connect(ui->pushButton_copy_target, &QPushButton::clicked, this,
			&cDockNavigation::slotCopyTargetCoords);
	if (ui->pushButton_paste_target)
		connect(ui->pushButton_paste_target, &QPushButton::clicked, this,
			&cDockNavigation::slotPasteTargetCoords);
}

void cDockNavigation::SetCameraView(double cx, double cy, double cz,
	double tx, double ty, double tz, double yaw, double pitch, double roll, double distance)
{
	QWidget *dock = const_cast<cDockNavigation *>(this);
	SynchronizeInterfaceWindow(dock, params, qInterface::read);

	params->Set("camera", CVector3(cx, cy, cz));
	params->Set("target", CVector3(tx, ty, tz));
	params->Set("camera_rotation", CVector3(yaw, pitch, roll));
	params->Set("camera_distance_to_target", distance);

	SynchronizeInterfaceWindow(dock, params, qInterface::write);
	emit signalRender();
}

void cDockNavigation::slotQuickViewHome()
{
	SetCameraView(3.0, -6.0, 2.0, 0.0, 0.0, 0.0, 26.565, -16.602, 0.0, 7.0);
}

void cDockNavigation::slotQuickViewTop()
{
	SetCameraView(0.0, 0.0, 7.0, 0.0, 0.0, 0.0, 0.0, -90.0, 0.0, 7.0);
}

void cDockNavigation::slotQuickViewFront()
{
	SetCameraView(0.0, -7.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 7.0);
}

void cDockNavigation::slotQuickViewRight()
{
	SetCameraView(7.0, 0.0, 0.0, 0.0, 0.0, 0.0, 90.0, 0.0, 0.0, 7.0);
}

void cDockNavigation::slotCopyCameraCoords()
{
	QWidget *dock = const_cast<cDockNavigation *>(this);
	SynchronizeInterfaceWindow(dock, params, qInterface::read);
	CVector3 cam = params->Get<CVector3>("camera");
	QString text = QString("%1, %2, %3").arg(cam.x, 0, 'g', 15).arg(cam.y, 0, 'g', 15).arg(cam.z, 0, 'g', 15);
	QApplication::clipboard()->setText(text);
}

void cDockNavigation::slotPasteCameraCoords()
{
	QString text = QApplication::clipboard()->text();
	QStringList parts = text.split(',');
	if (parts.size() >= 3)
	{
		bool okX, okY, okZ;
		double x = parts[0].trimmed().toDouble(&okX);
		double y = parts[1].trimmed().toDouble(&okY);
		double z = parts[2].trimmed().toDouble(&okZ);
		if (okX && okY && okZ)
		{
			QWidget *dock = const_cast<cDockNavigation *>(this);
			SynchronizeInterfaceWindow(dock, params, qInterface::read);
			params->Set("camera", CVector3(x, y, z));
			SynchronizeInterfaceWindow(dock, params, qInterface::write);
			emit signalRender();
		}
	}
}

void cDockNavigation::slotCopyTargetCoords()
{
	QWidget *dock = const_cast<cDockNavigation *>(this);
	SynchronizeInterfaceWindow(dock, params, qInterface::read);
	CVector3 tgt = params->Get<CVector3>("target");
	QString text = QString("%1, %2, %3").arg(tgt.x, 0, 'g', 15).arg(tgt.y, 0, 'g', 15).arg(tgt.z, 0, 'g', 15);
	QApplication::clipboard()->setText(text);
}

void cDockNavigation::slotPasteTargetCoords()
{
	QString text = QApplication::clipboard()->text();
	QStringList parts = text.split(',');
	if (parts.size() >= 3)
	{
		bool okX, okY, okZ;
		double x = parts[0].trimmed().toDouble(&okX);
		double y = parts[1].trimmed().toDouble(&okY);
		double z = parts[2].trimmed().toDouble(&okZ);
		if (okX && okY && okZ)
		{
			QWidget *dock = const_cast<cDockNavigation *>(this);
			SynchronizeInterfaceWindow(dock, params, qInterface::read);
			params->Set("target", CVector3(x, y, z));
			SynchronizeInterfaceWindow(dock, params, qInterface::write);
			emit signalRender();
		}
	}
}

void cDockNavigation::slotToggleSection()
{
	QGroupBox *box = qobject_cast<QGroupBox *>(sender());
	if (!box) return;
	bool show = box->isChecked();
	for (QObject *child : box->children())
	{
		QWidget *w = qobject_cast<QWidget *>(child);
		if (w) w->setVisible(show);
	}
}

// --- 3x3lion Camera Bookmark System ---

void cDockNavigation::SetupBookmarks()
{
	bookmarkListWidget = ui->listWidget_bookmarks;

	connect(ui->pushButton_bookmark_save, &QPushButton::clicked, this,
		&cDockNavigation::slotBookmarkSave);
	connect(ui->pushButton_bookmark_recall, &QPushButton::clicked, this,
		&cDockNavigation::slotBookmarkRecall);
	connect(ui->pushButton_bookmark_delete, &QPushButton::clicked, this,
		&cDockNavigation::slotBookmarkDelete);
	connect(ui->pushButton_bookmark_export, &QPushButton::clicked, this,
		&cDockNavigation::slotBookmarkExport);
	connect(ui->pushButton_bookmark_import, &QPushButton::clicked, this,
		&cDockNavigation::slotBookmarkImport);

	// Double-click to recall
	connect(bookmarkListWidget, &QListWidget::itemDoubleClicked, this,
		&cDockNavigation::slotBookmarkRecall);

	LoadBookmarksFromFile();
}

QString cDockNavigation::BookmarksFilePath() const
{
	return systemDirectories.GetDataDirectoryHidden() + "camera_bookmarks.json";
}

void cDockNavigation::SaveBookmarksToFile()
{
	QJsonArray arr;
	for (const sCameraBookmark &b : bookmarks)
	{
		QJsonObject obj;
		obj["name"] = b.name;
		obj["cam_x"] = b.camera.x;
		obj["cam_y"] = b.camera.y;
		obj["cam_z"] = b.camera.z;
		obj["tgt_x"] = b.target.x;
		obj["tgt_y"] = b.target.y;
		obj["tgt_z"] = b.target.z;
		obj["rot_x"] = b.rotation.x;
		obj["rot_y"] = b.rotation.y;
		obj["rot_z"] = b.rotation.z;
		obj["distance"] = b.distance;
		obj["timestamp"] = b.timestamp;
		arr.append(obj);
	}

	QString path = BookmarksFilePath();
	QDir().mkpath(QFileInfo(path).absolutePath());
	QFile file(path);
	if (file.open(QIODevice::WriteOnly))
	{
		file.write(QJsonDocument(arr).toJson());
		file.close();
	}
}

void cDockNavigation::LoadBookmarksFromFile()
{
	bookmarks.clear();
	QString path = BookmarksFilePath();
	QFile file(path);
	if (!file.exists()) return;
	if (!file.open(QIODevice::ReadOnly)) return;

	QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	file.close();
	if (!doc.isArray()) return;

	QJsonArray arr = doc.array();
	for (const QJsonValue &val : arr)
	{
		QJsonObject obj = val.toObject();
		sCameraBookmark b;
		b.name = obj["name"].toString();
		b.camera = CVector3(obj["cam_x"].toDouble(), obj["cam_y"].toDouble(), obj["cam_z"].toDouble());
		b.target = CVector3(obj["tgt_x"].toDouble(), obj["tgt_y"].toDouble(), obj["tgt_z"].toDouble());
		b.rotation =
			CVector3(obj["rot_x"].toDouble(), obj["rot_y"].toDouble(), obj["rot_z"].toDouble());
		b.distance = obj["distance"].toDouble();
		b.timestamp = obj["timestamp"].toString();
		bookmarks.append(b);
	}

	RefreshBookmarkList();
}

void cDockNavigation::RefreshBookmarkList()
{
	if (!bookmarkListWidget) return;
	bookmarkListWidget->clear();
	for (int i = 0; i < bookmarks.size(); i++)
	{
		const sCameraBookmark &b = bookmarks[i];
		QString display =
			QString("%1 — d:%2").arg(b.name).arg(b.distance, 0, 'g', 4);
		bookmarkListWidget->addItem(display);
	}
}

void cDockNavigation::slotBookmarkSave()
{
	QWidget *dock = const_cast<cDockNavigation *>(this);
	SynchronizeInterfaceWindow(dock, params, qInterface::read);

	CVector3 cam = params->Get<CVector3>("camera");
	CVector3 tgt = params->Get<CVector3>("target");
	CVector3 rot = params->Get<CVector3>("camera_rotation");
	double dist = params->Get<double>("camera_distance_to_target");

	QString defaultName = QString("BM-%1").arg(bookmarks.size() + 1);
	QString name = QInputDialog::getText(this, "Save Bookmark", "Bookmark name:", QLineEdit::Normal,
		defaultName);
	if (name.isEmpty()) return;

	sCameraBookmark b;
	b.name = name;
	b.camera = cam;
	b.target = tgt;
	b.rotation = rot;
	b.distance = dist;
	b.timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);

	bookmarks.append(b);
	SaveBookmarksToFile();
	RefreshBookmarkList();
}

void cDockNavigation::slotBookmarkRecall()
{
	int row = bookmarkListWidget ? bookmarkListWidget->currentRow() : -1;
	if (row < 0 || row >= bookmarks.size()) return;

	const sCameraBookmark &b = bookmarks[row];

	QWidget *dock = const_cast<cDockNavigation *>(this);
	SynchronizeInterfaceWindow(dock, params, qInterface::read);

	params->Set("camera", b.camera);
	params->Set("target", b.target);
	params->Set("camera_rotation", b.rotation);
	params->Set("camera_distance_to_target", b.distance);

	SynchronizeInterfaceWindow(dock, params, qInterface::write);
	emit signalRender();
}

void cDockNavigation::slotBookmarkDelete()
{
	int row = bookmarkListWidget ? bookmarkListWidget->currentRow() : -1;
	if (row < 0 || row >= bookmarks.size()) return;

	bookmarks.removeAt(row);
	SaveBookmarksToFile();
	RefreshBookmarkList();
}

void cDockNavigation::slotBookmarkExport()
{
	QString path = QFileDialog::getSaveFileName(
		this, "Export Bookmarks", "3x3lion_bookmarks.json", "JSON Files (*.json)");
	if (path.isEmpty()) return;

	QJsonArray arr;
	for (const sCameraBookmark &b : bookmarks)
	{
		QJsonObject obj;
		obj["name"] = b.name;
		obj["cam_x"] = b.camera.x;
		obj["cam_y"] = b.camera.y;
		obj["cam_z"] = b.camera.z;
		obj["tgt_x"] = b.target.x;
		obj["tgt_y"] = b.target.y;
		obj["tgt_z"] = b.target.z;
		obj["rot_x"] = b.rotation.x;
		obj["rot_y"] = b.rotation.y;
		obj["rot_z"] = b.rotation.z;
		obj["distance"] = b.distance;
		obj["timestamp"] = b.timestamp;
		arr.append(obj);
	}

	QFile file(path);
	if (file.open(QIODevice::WriteOnly))
	{
		file.write(QJsonDocument(arr).toJson());
		file.close();
	}
}

void cDockNavigation::slotBookmarkImport()
{
	QString path = QFileDialog::getOpenFileName(
		this, "Import Bookmarks", QString(), "JSON Files (*.json)");
	if (path.isEmpty()) return;

	QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) return;

	QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	file.close();
	if (!doc.isArray()) return;

	QJsonArray arr = doc.array();
	for (const QJsonValue &val : arr)
	{
		QJsonObject obj = val.toObject();
		sCameraBookmark b;
		b.name = obj["name"].toString();
		b.camera = CVector3(obj["cam_x"].toDouble(), obj["cam_y"].toDouble(), obj["cam_z"].toDouble());
		b.target = CVector3(obj["tgt_x"].toDouble(), obj["tgt_y"].toDouble(), obj["tgt_z"].toDouble());
		b.rotation =
			CVector3(obj["rot_x"].toDouble(), obj["rot_y"].toDouble(), obj["rot_z"].toDouble());
		b.distance = obj["distance"].toDouble();
		b.timestamp = obj["timestamp"].toString();
		bookmarks.append(b);
	}

	SaveBookmarksToFile();
	RefreshBookmarkList();
}

// ============================================================
// Smart Camera System
// ============================================================

void cDockNavigation::SetupSmartCamera()
{
	smartCamera = new cSmartCamera(this);

	connect(smartCamera, &cSmartCamera::signalCameraUpdated, this,
		&cDockNavigation::slotSmartCameraUpdated);
	connect(smartCamera, &cSmartCamera::signalRender, this, &cDockNavigation::signalRender);
	connect(smartCamera, &cSmartCamera::signalHUDDataChanged, this,
		&cDockNavigation::signalHUDDataChanged);

	QGroupBox *smartGroup = new QGroupBox("Smart Camera", this);
	smartGroup->setObjectName("groupBox_smart_camera");

	QVBoxLayout *lay = new QVBoxLayout(smartGroup);
	lay->setContentsMargins(4, 8, 4, 4);
	lay->setSpacing(4);

	// Collision avoidance
	QCheckBox *cbCollision = new QCheckBox("Collision Avoidance", smartGroup);
	cbCollision->setObjectName("cb_collision_avoidance");
	cbCollision->setChecked(true);
	cbCollision->setToolTip("DE-based collision prevention");
	lay->addWidget(cbCollision);
	connect(cbCollision, &QCheckBox::toggled, this, &cDockNavigation::slotToggleCollisionAvoidance);

	// Adaptive step
	QCheckBox *cbAdaptive = new QCheckBox("Adaptive Step Size", smartGroup);
	cbAdaptive->setObjectName("cb_adaptive_step");
	cbAdaptive->setChecked(true);
	cbAdaptive->setToolTip("Auto-adjust movement speed based on distance to surface");
	lay->addWidget(cbAdaptive);
	connect(cbAdaptive, &QCheckBox::toggled, this, &cDockNavigation::slotToggleAdaptiveStep);

	// Smoothness slider
	QHBoxLayout *smoothLay = new QHBoxLayout();
	QLabel *smoothLabel = new QLabel("Smoothness:", smartGroup);
	QSlider *smoothSlider = new QSlider(Qt::Horizontal, smartGroup);
	smoothSlider->setObjectName("slider_smoothness");
	smoothSlider->setRange(1, 50);
	smoothSlider->setValue(15);
	smoothSlider->setToolTip("Camera interpolation smoothness");
	smoothLay->addWidget(smoothLabel);
	smoothLay->addWidget(smoothSlider);
	lay->addLayout(smoothLay);
	connect(smoothSlider, &QSlider::valueChanged, this, &cDockNavigation::slotSmoothnessChanged);

	// Orbit mode
	QHBoxLayout *orbitLay = new QHBoxLayout();
	QPushButton *btnOrbitStart = new QPushButton("Orbit", smartGroup);
	btnOrbitStart->setObjectName("btn_orbit_start");
	btnOrbitStart->setToolTip("Orbit camera around current target");
	QPushButton *btnOrbitStop = new QPushButton("Stop Orbit", smartGroup);
	btnOrbitStop->setObjectName("btn_orbit_stop");
	orbitLay->addWidget(btnOrbitStart);
	orbitLay->addWidget(btnOrbitStop);
	lay->addLayout(orbitLay);
	connect(btnOrbitStart, &QPushButton::clicked, this, &cDockNavigation::slotStartOrbit);
	connect(btnOrbitStop, &QPushButton::clicked, this, &cDockNavigation::slotStopOrbit);

	// Surface following
	QHBoxLayout *surfLay = new QHBoxLayout();
	QPushButton *btnSurfStart = new QPushButton("Surface Follow", smartGroup);
	btnSurfStart->setObjectName("btn_surface_start");
	btnSurfStart->setToolTip("Camera follows fractal surface at constant DE distance");
	QPushButton *btnSurfStop = new QPushButton("Stop Follow", smartGroup);
	btnSurfStop->setObjectName("btn_surface_stop");
	surfLay->addWidget(btnSurfStart);
	surfLay->addWidget(btnSurfStop);
	lay->addLayout(surfLay);
	connect(btnSurfStart, &QPushButton::clicked, this, &cDockNavigation::slotStartSurfaceFollow);
	connect(btnSurfStop, &QPushButton::clicked, this, &cDockNavigation::slotStopSurfaceFollow);

	// Flight path recorder
	QHBoxLayout *flightLay1 = new QHBoxLayout();
	QPushButton *btnRecord = new QPushButton("Record", smartGroup);
	btnRecord->setObjectName("btn_flight_record");
	btnRecord->setToolTip("Record camera movement as a flight path");
	QPushButton *btnStopRecord = new QPushButton("Stop Rec", smartGroup);
	btnStopRecord->setObjectName("btn_flight_stop_record");
	QPushButton *btnPlay = new QPushButton("Play", smartGroup);
	btnPlay->setObjectName("btn_flight_play");
	QPushButton *btnStopPlay = new QPushButton("Stop", smartGroup);
	btnStopPlay->setObjectName("btn_flight_stop_play");
	flightLay1->addWidget(btnRecord);
	flightLay1->addWidget(btnStopRecord);
	flightLay1->addWidget(btnPlay);
	flightLay1->addWidget(btnStopPlay);
	lay->addLayout(flightLay1);
	connect(btnRecord, &QPushButton::clicked, this, &cDockNavigation::slotStartFlightRecord);
	connect(btnStopRecord, &QPushButton::clicked, this, &cDockNavigation::slotStopFlightRecord);
	connect(btnPlay, &QPushButton::clicked, this, &cDockNavigation::slotStartFlightPlayback);
	connect(btnStopPlay, &QPushButton::clicked, this, &cDockNavigation::slotStopFlightPlayback);

	QHBoxLayout *flightLay2 = new QHBoxLayout();
	QPushButton *btnExport = new QPushButton("Export Path", smartGroup);
	btnExport->setObjectName("btn_flight_export");
	QPushButton *btnImport = new QPushButton("Import Path", smartGroup);
	btnImport->setObjectName("btn_flight_import");
	QPushButton *btnClear = new QPushButton("Clear", smartGroup);
	btnClear->setObjectName("btn_flight_clear");
	flightLay2->addWidget(btnExport);
	flightLay2->addWidget(btnImport);
	flightLay2->addWidget(btnClear);
	lay->addLayout(flightLay2);
	connect(btnExport, &QPushButton::clicked, this, &cDockNavigation::slotExportFlightPath);
	connect(btnImport, &QPushButton::clicked, this, &cDockNavigation::slotImportFlightPath);
	connect(btnClear, &QPushButton::clicked, this, &cDockNavigation::slotClearFlightPath);

	// HUD toggle
	QCheckBox *cbHUD = new QCheckBox("Show Camera HUD", smartGroup);
	cbHUD->setObjectName("cb_show_hud");
	cbHUD->setChecked(true);
	cbHUD->setToolTip("Show/hide camera info HUD overlay on the render view");
	lay->addWidget(cbHUD);
	connect(cbHUD, &QCheckBox::toggled, this, &cDockNavigation::slotToggleHUD);

	// Depth overlay toggle
	QCheckBox *cbDepth = new QCheckBox("Depth Visualization", smartGroup);
	cbDepth->setObjectName("cb_depth_overlay");
	cbDepth->setChecked(false);
	cbDepth->setToolTip("Overlay depth coloring on the render (red=near, blue=far)");
	lay->addWidget(cbDepth);
	connect(cbDepth, &QCheckBox::toggled, this, &cDockNavigation::slotToggleDepthOverlay);

	QLayout *dockLayout = layout();
	if (dockLayout)
		dockLayout->addWidget(smartGroup);
}

void cDockNavigation::slotToggleCollisionAvoidance(bool checked)
{
	if (smartCamera) smartCamera->SetCollisionAvoidance(checked);
}

void cDockNavigation::slotToggleAdaptiveStep(bool checked)
{
	if (smartCamera) smartCamera->SetAdaptiveStep(checked);
}

void cDockNavigation::slotSmoothnessChanged(int value)
{
	if (smartCamera) smartCamera->SetSmoothness(value / 100.0);
}

void cDockNavigation::slotStartOrbit()
{
	if (!smartCamera || !params) return;
	CVector3 target = params->Get<CVector3>("target");
	double distance = params->Get<double>("camera_distance_to_target");
	smartCamera->StartOrbit(target, distance, 1.0);
}

void cDockNavigation::slotStopOrbit()
{
	if (smartCamera) smartCamera->StopOrbit();
	emit signalRender();
}

void cDockNavigation::slotStartSurfaceFollow()
{
	if (!smartCamera || !params) return;
	CVector3 cam = params->Get<CVector3>("camera");
	double de = cInterface::GetDistanceForPoint(cam, params, fractalParams);
	smartCamera->StartSurfaceFollow(de * 0.5, 1.0);
}

void cDockNavigation::slotStopSurfaceFollow()
{
	if (smartCamera) smartCamera->StopSurfaceFollow();
	emit signalRender();
}

void cDockNavigation::slotStartFlightRecord()
{
	if (smartCamera) smartCamera->StartRecording();
}

void cDockNavigation::slotStopFlightRecord()
{
	if (smartCamera) smartCamera->StopRecording();
}

void cDockNavigation::slotStartFlightPlayback()
{
	if (smartCamera) smartCamera->StartPlayback(1.0);
}

void cDockNavigation::slotStopFlightPlayback()
{
	if (smartCamera) smartCamera->StopPlayback();
	emit signalRender();
}

void cDockNavigation::slotExportFlightPath()
{
	if (!smartCamera) return;
	QString path = QFileDialog::getSaveFileName(
		this, "Export Flight Path", "3x3lion_flight.json", "JSON Files (*.json)");
	if (path.isEmpty()) return;

	QJsonDocument doc(smartCamera->FlightPathToJson());
	QFile file(path);
	if (file.open(QIODevice::WriteOnly))
	{
		file.write(doc.toJson());
		file.close();
	}
}

void cDockNavigation::slotImportFlightPath()
{
	if (!smartCamera) return;
	QString path = QFileDialog::getOpenFileName(
		this, "Import Flight Path", QString(), "JSON Files (*.json)");
	if (path.isEmpty()) return;

	QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) return;

	QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	file.close();
	if (!doc.isArray()) return;

	smartCamera->FlightPathFromJson(doc.array());
}

void cDockNavigation::slotClearFlightPath()
{
	if (smartCamera) smartCamera->ClearFlightPath();
}

void cDockNavigation::slotToggleHUD(bool checked)
{
	emit signalToggleHUD(checked);
}

void cDockNavigation::slotToggleDepthOverlay(bool checked)
{
	emit signalToggleDepthOverlay(checked);
}

void cDockNavigation::slotSmartCameraUpdated()
{
	SynchronizeInterfaceWindow(this, params, qInterface::write);
}

// ============================================================
// Deep Zoom Engine (Perturbation Theory for 3D Fractals)
// ============================================================

#ifdef USE_MPFR
void cDockNavigation::SetupDeepZoom()
{
	deepZoomManager = new deep_zoom::cDeepZoomManager();

	QGroupBox *dzGroup = new QGroupBox("Deep Zoom (Perturbation Theory)", this);
	dzGroup->setObjectName("groupBox_deep_zoom");

	QVBoxLayout *lay = new QVBoxLayout(dzGroup);
	lay->setContentsMargins(4, 8, 4, 4);
	lay->setSpacing(4);

	// Enable toggle
	deepZoomCheckBox = new QCheckBox("Enable Deep Zoom", dzGroup);
	deepZoomCheckBox->setObjectName("cb_deep_zoom_enable");
	deepZoomCheckBox->setChecked(false);
	deepZoomCheckBox->setToolTip(
		"Perturbation theory for infinite zoom on 3D fractals.\n"
		"Computes reference orbit at arbitrary precision (MPFR)\n"
		"and uses delta iteration at double precision per pixel.");
	lay->addWidget(deepZoomCheckBox);
	connect(deepZoomCheckBox, &QCheckBox::toggled, this, &cDockNavigation::slotDeepZoomToggle);

	// Precision selector
	QHBoxLayout *precLay = new QHBoxLayout();
	QLabel *precLabel = new QLabel("Precision:", dzGroup);
	deepZoomPrecision = new QComboBox(dzGroup);
	deepZoomPrecision->setObjectName("combo_deep_zoom_precision");
	deepZoomPrecision->addItem("Auto (zoom-based)", 0);
	deepZoomPrecision->addItem("256 bits (~77 digits)", 256);
	deepZoomPrecision->addItem("512 bits (~154 digits)", 512);
	deepZoomPrecision->addItem("1024 bits (~308 digits)", 1024);
	deepZoomPrecision->addItem("2048 bits (~617 digits)", 2048);
	deepZoomPrecision->addItem("4096 bits (~1234 digits)", 4096);
	deepZoomPrecision->addItem("8192 bits (~2468 digits)", 8192);
	deepZoomPrecision->setCurrentIndex(0);
	deepZoomPrecision->setToolTip(
		"MPFR precision for reference orbit computation.\n"
		"Auto mode adjusts based on zoom level.\n"
		"Higher precision = deeper zoom but slower computation.");
	precLay->addWidget(precLabel);
	precLay->addWidget(deepZoomPrecision);
	lay->addLayout(precLay);
	connect(deepZoomPrecision, QOverload<int>::of(&QComboBox::currentIndexChanged),
		this, &cDockNavigation::slotDeepZoomPrecisionChanged);

	// Compute reference orbit button
	QPushButton *btnCompute = new QPushButton("Compute Reference Orbit", dzGroup);
	btnCompute->setObjectName("btn_deep_zoom_compute");
	btnCompute->setToolTip(
		"Compute the reference orbit at the current camera target.\n"
		"This must be done once per zoom center.\n"
		"The orbit is computed at arbitrary precision using MPFR.");
	lay->addWidget(btnCompute);
	connect(btnCompute, &QPushButton::clicked, this, &cDockNavigation::slotDeepZoomCompute);

	// Status label
	deepZoomStatusLabel = new QLabel("Status: Inactive", dzGroup);
	deepZoomStatusLabel->setObjectName("label_deep_zoom_status");
	deepZoomStatusLabel->setWordWrap(true);
	lay->addWidget(deepZoomStatusLabel);

	// Info text
	QLabel *infoLabel = new QLabel(
		"<small>The Holy Grail: infinite zoom on 3D fractals.<br>"
		"Reference orbit at arbitrary precision (CPU/MPFR),<br>"
		"delta iteration at double precision (GPU).<br>"
		"<b>Never done before for 3D fractals with DE.</b></small>", dzGroup);
	infoLabel->setWordWrap(true);
	lay->addWidget(infoLabel);

	QLayout *dockLayout = layout();
	if (dockLayout)
		dockLayout->addWidget(dzGroup);
}

void cDockNavigation::slotDeepZoomToggle(bool checked)
{
	if (checked)
	{
		deepZoomStatusLabel->setText("Status: Enabled — compute reference orbit to start");
		if (deepZoomManager && deepZoomManager->IsReady())
		{
			deep_zoom_integration::Enable(deepZoomManager);
			deep_zoom_integration::PrepareGPUData();
			deepZoomStatusLabel->setText("Status: Active — rendering via perturbation engine");
		}
	}
	else
	{
		deep_zoom_integration::Disable();
		deepZoomStatusLabel->setText("Status: Inactive");
	}
}

void cDockNavigation::slotDeepZoomCompute()
{
	if (!params || !deepZoomManager) return;

	deepZoomStatusLabel->setText("Status: Computing reference orbit...");
	QApplication::processEvents();

	// Get zoom level and determine precision
	CVector3 camera = params->Get<CVector3>("camera");
	CVector3 target = params->Get<CVector3>("target");
	double distance = params->Get<double>("camera_distance_to_target");

	double zoomLevel = 1.0 / std::max(distance, 1e-30);

	deep_zoom::sDeepZoomConfig config;
	config.power = 8.0;
	config.bailout = 256.0;
	config.maxIterations = params->Get<int>("N");

	int precData = deepZoomPrecision->currentData().toInt();
	if (precData == 0)
	{
		config.precisionBits = deep_zoom::cDeepZoomManager::PrecisionForZoom(zoomLevel);
	}
	else
	{
		config.precisionBits = precData;
	}

	// Estimate pixel spacing from zoom level (for SA tolerance)
	double pixelSpacing = distance / 800.0; // rough estimate: distance / image_width

	deepZoomManager->Configure(config);
	deepZoomManager->SetPixelSpacing(pixelSpacing);
	deepZoomManager->SetCenter(target);

	const auto &refOrbit = deepZoomManager->GetReferenceOrbit();
	int saSkip = deepZoomManager->GetSASkipIterations();

	QString status = QString("Status: Ready\n"
		"Reference orbit: %1 iterations\n"
		"Precision: %2 bits (%3 digits)\n"
		"Escaped: %4 (iter %5)\n"
		"Zoom level: %6")
		.arg(refOrbit.GetLength())
		.arg(config.precisionBits)
		.arg(static_cast<int>(config.precisionBits * 0.301))
		.arg(refOrbit.Escaped() ? "yes" : "no")
		.arg(refOrbit.GetEscapeIteration())
		.arg(QString::number(zoomLevel, 'e', 2));

	if (saSkip > 0)
	{
		status += QString("\nSeries Approx: skip %1 iterations").arg(saSkip);
	}
	else
	{
		status += "\nSeries Approx: not applicable";
	}

	// Enable deep zoom in the rendering pipeline if checkbox is checked
	if (deepZoomCheckBox && deepZoomCheckBox->isChecked())
	{
		deep_zoom_integration::Enable(deepZoomManager);
		deep_zoom_integration::PrepareGPUData();
		status += "\nGPU Integration: ACTIVE";

		const auto &gpuData = deep_zoom_integration::GetGPUData();
		status += QString("\nGPU orbit: %1 points uploaded").arg(gpuData.orbitLength);
		if (gpuData.saValid)
		{
			status += QString("\nGPU SA: skip %1 iters (matrix ready)").arg(gpuData.saSkipIters);
		}
	}

	deepZoomStatusLabel->setText(status);
}

void cDockNavigation::slotDeepZoomPrecisionChanged(int index)
{
	(void)index;
	// Will take effect on next compute
}
#endif // USE_MPFR

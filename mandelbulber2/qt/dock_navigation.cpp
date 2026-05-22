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
#include <QPropertyAnimation>

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

/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2016-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * RenderWindow class - main program window
 *
 * This file contains implementation of the menu slots in RenderWindow class.
 * See also header render_window.hpp and whole implementation of class
 * spread over render_window_*.cpp
 */

#include "ui_render_window.h"

#include "animation_flight.hpp"
#include "animation_keyframes.hpp"
#include "file_image.hpp"
#include "files.h"
#include "global_data.hpp"
#include "initparameters.hpp"
#include "interface.hpp"
#include "mandelbulb3d_settings.hpp"
#include "material_item_model.h"
#include "old_settings.hpp"
#include "render_window.hpp"
#include "settings.hpp"
#include "system.hpp"
#include "system_data.hpp"
#include "system_directories.hpp"

#include "rendered_image_widget.hpp"

#include "qt/image_save_dialog.h"
#include "qt/preview_file_dialog.h"
#include "qt/settings_browser.h"

#include <QMenu>
#include <QShortcut>

void RenderWindow::slotImportOldSettings()
{
	QFileDialog dialog(this);
	dialog.setOption(QFileDialog::DontUseNativeDialog);
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setNameFilter(tr("Fractals (*.txt *.fract)"));
	dialog.setDirectory(
		QDir::toNativeSeparators(QFileInfo(systemData.lastSettingsFile).absolutePath()));
	dialog.selectFile(QDir::toNativeSeparators(systemData.lastSettingsFile));
	dialog.setAcceptMode(QFileDialog::AcceptOpen);
	dialog.setWindowTitle(tr("Import settings from old Mandelbulber (v1.21)..."));
	QStringList filenames;
	if (dialog.exec())
	{
		filenames = dialog.selectedFiles();
		QString filename = QDir::toNativeSeparators(filenames.first());
		oldSettings::cOldSettings oldSettings;
		oldSettings.LoadSettings(filename);
		oldSettings.ConvertToNewContainer(gPar, gParFractal);
		gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
		gMainInterface->ComboMouseClickUpdate();
		systemData.lastSettingsFile = filename;
		setWindowTitle(QString(APP_NAME) + " (" + filename + ")");
	}
}

void RenderWindow::slotImportMandelbulb3dSettings()
{
	//	QFileDialog dialog(this);
	//	dialog.setOption(QFileDialog::DontUseNativeDialog);
	//	dialog.setFileMode(QFileDialog::ExistingFile);
	//	dialog.setNameFilter(tr("Fractals (*.m3d *.fract)"));
	//	dialog.setDirectory(
	//		QDir::toNativeSeparators(QFileInfo(systemData.lastSettingsFile).absolutePath()));
	//	dialog.selectFile(QDir::toNativeSeparators(systemData.lastSettingsFile));
	//	dialog.setAcceptMode(QFileDialog::AcceptOpen);
	//	dialog.setWindowTitle(tr("Import settings from Mandelbulb3d settings file ..."));
	//	QStringList filenames;
	//	if (dialog.exec())
	//	{
	//		filenames = dialog.selectedFiles();
	//		QString filename = QDir::toNativeSeparators(filenames.first());
	//		cMandelbulb3dSettings m3dSettings;
	//		m3dSettings.LoadSettings(filename);
	//		m3dSettings.ConvertToNewContainer(gPar, gParFractal);
	//		gMainInterface->RebuildPrimitives(gPar);
	//		gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
	//		gMainInterface->ComboMouseClickUpdate();
	//		systemData.lastSettingsFile = filename;
	//		setWindowTitle(QString(APP_NAME) + " (" + filename + ")");
	//	}
}

void RenderWindow::slotMenuAboutMandelbulber()
{
	QString text = "<h2>" + QString(APP_NAME) + "</h2>";
	text += "version: <b>" + QString(MANDELBULBER_VERSION_STRING) + "</b>" + "<br>";
	text += "Founded by: <b>" + QString(APP_FOUNDERS) + "</b><br>";
	text += "<br>";
	text += "Based on Mandelbulber by Krzysztof Marczak<br>";
	text += "<br>";
	text += "Licence: GNU GPL version 3.0<br>";
	text += "Copyright Ⓒ 2025<br>";
	text += "<br>";
	text += "<b>1600+ fractal transformations</b><br>";
	text += "Amazing Surf 1-4 (100 types) | SphereTree/Menger (100 types)<br>";
	text += "MandelTorus (100 types) | Abox (300 types) | Noise/Orbit (200 types)<br>";
	text += "Symmetry/Kaleidoscope (100 types) | Warp/Distortion (100 types)<br>";
	text += "Boolean groups | 7 Cloner modes | Full GPU/CPU parity<br>";
	text += "<br>";
	text += "Original Mandelbulber contributors:<br>";
	text += "Krzysztof Marczak, Sebastian Jennen, Graeme McLaren,<br>";
	text += "Bernardo Martelli, Robert Pancoast, knighty, makemeunsee,<br>";
	text += "Marius Schilder, Ryan Hitchman, Jeff Epler, Martin Reinecke,<br>";
	text += "Quazgaa, Adrian Meyer, and many more<br>";
	text += "<br>";
	text += "Thanks to the Mandelbulber community<br>";
	text +=
		"<a "
		"href=\"https://www.facebook.com/groups/mandelbulber/\">https://www.facebook.com/groups/"
		"mandelbulber/</a>";
	text += "<br>for help<br>";
	text += "<br>";
	text += "<a href=\"http://www.mandelbulber.com\">www.mandelbulber.com</a>";

	QMessageBox::about(this, "About " + QString(APP_NAME), text);
}

void RenderWindow::slotMenuAboutQt()
{
	QMessageBox::aboutQt(this);
}

void RenderWindow::slotMenuAboutManual()
{
	// qDebug() << systemDirectories.docDir;
	QString filename = systemDirectories.docDir + "Mandelbulber_Manual.pdf";
	QDesktopServices::openUrl(QUrl::fromLocalFile(filename));
}

void RenderWindow::slotMenuAboutNews()
{
	QString filename = systemDirectories.docDir + "NEWS";

	QFile f(filename);
	QString text = "";
	if (f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		text = f.readAll();
	}

	QLabel *label = new QLabel;
	label->setText(text);
	label->setWordWrap(true);
	label->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

	QScrollArea *scroll = new QScrollArea();
	scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	scroll->setWidget(label);
	scroll->setWidgetResizable(true);

	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(scroll);
	QDialog *dialog = new QDialog();
	dialog->setLayout(layout);
	dialog->setWindowTitle(QObject::tr("News"));
	dialog->show();
}

void RenderWindow::slotMenuAboutHotKeys()
{
	QString ctrlBadge =
		"<span style='background-color: #222; color: #FFF; padding: 3px;'>" + tr("Ctrl") + "</span>";
	QString altBadge =
		"<span style='background-color: #222; color: #FFF; padding: 3px;'>" + tr("Alt") + "</span>";
	QString shiftBadge =
		"<span style='background-color: #222; color: #FFF; padding: 3px;'>" + tr("Shift") + "</span>";

	// Main program hotkeys
	QString style = "<style>td { padding: 2px; color: black;}</style>";
	QString text = "<table><tr>";
	text += "<td style='padding: 5px; background-color: #DDF'>";
	text += "<h3>" + tr("Main Program Hotkeys") + "</h3>";
	text += "<table border='1'>";

	// File
	text += " <tr><th colspan='2'>" + tr("File") + "</th></tr>";
	text += " <tr><th>" + ctrlBadge + " + O</th><td>" + tr("Load settings...") + "</td></tr>";
	text +=
		" <tr><th>" + altBadge + " + O</th><td>" + tr("Load settings from clipboard...") + "</td></tr>";
	text += " <tr><th>" + ctrlBadge + " + " + altBadge + " + O</th><td>" + tr("Load example...")
					+ "</td></tr>";
	text += " <tr><th>" + ctrlBadge + " + S</th><td>" + tr("Save settings...") + "</td></tr>";
	text +=
		" <tr><th>" + altBadge + " + S</th><td>" + tr("Save settings to clipboard...") + "</td></tr>";
	text +=
		" <tr><th>" + ctrlBadge + " + I</th><td>" + tr("Import legacy settings...") + "</td></tr>";

	text += " <tr><th>" + ctrlBadge + " + M</th><td>" + tr("Export Mesh") + "</td></tr>";
	text += " <tr><th>" + ctrlBadge + " + " + altBadge + " + S</th><td>" + tr("Save as Image...")
					+ "</td></tr>";
	text += " <tr><th>" + ctrlBadge + " + P</th><td>" + tr("Program Preferences") + "</td></tr>";
	text += " <tr><th>" + ctrlBadge + " + Q</th><td>" + tr("Quit") + "</td></tr>";
	text += " <tr><th>F11</th><td>" + tr("Full screen") + "</td></tr>";
	text += "</table>";

	// Other
	text += "<table style='margin-top: 10px;' border='1'>";
	text += " <tr><th colspan='2'>" + tr("Other") + "</th></tr>";
	text += " <tr><th>" + ctrlBadge + " + Z</th><td>" + tr("Undo") + "</td></tr>";
	text += " <tr><th>" + ctrlBadge + " + Y</th><td>" + tr("Redo") + "</td></tr>";
	text += " <tr><th>" + ctrlBadge + " + H</th><td>" + tr("Show User Manual") + "</td></tr>";
	text += " <tr><th>" + altBadge + " + H</th><td>" + tr("Show (these) Hotkeys") + "</td></tr>";
	text +=
		" <tr><th>" + shiftBadge + " + ESC</th><td>" + tr("Terminate all calculations") + "</td></tr>";
	text += "</table>";
	text += "</td>";

	// Render window hotkeys
	text += "<td style='padding: 5px; background-color: #DFD'>";
	text += "<h3>" + tr("Render Window Hotkeys") + "</h3>";

	// Movement
	text += "<table border='1'>";
	text += " <tr><th colspan='2'>" + tr("Movement") + "</th></tr>";
	text +=
		" <tr><th>" + tr("Mouse left button click") + "</th><td>" + tr("jump forward") + "</td></tr>";
	text +=
		" <tr><th>" + tr("Mouse right button click") + "</th><td>" + tr("jump backward") + "</td></tr>";
	text += " <tr><th>" + tr("Mouse Wheel") + "</th><td>" + tr("forward / backward") + "</td></tr>";
	text += " <tr><th>" + tr("Mouse left+right buttons drag") + "</th><td>" + tr("Move camera")
					+ "</td></tr>";

	text += " <tr><th>W</th><td>" + tr("up") + "</td></tr>";
	text += " <tr><th>S</th><td>" + tr("down") + "</td></tr>";
	text += " <tr><th>A</th><td>" + tr("left") + "</td></tr>";
	text +=
		" <tr><th>" + shiftBadge + " + " + tr("Arrow left") + "</th><td>" + tr("left") + "</td></tr>";
	text += " <tr><th>D</th><td>" + tr("right") + "</td></tr>";
	text +=
		" <tr><th>" + shiftBadge + " + " + tr("Arrow right") + "</th><td>" + tr("right") + "</td></tr>";
	text += " <tr><th>Q</th><td>" + tr("forward") + "</td></tr>";
	text +=
		" <tr><th>" + ctrlBadge + " + " + tr("Arrow up") + "</th><td>" + tr("forward") + "</td></tr>";
	text +=
		" <tr><th>" + shiftBadge + " + " + tr("Arrow up") + "</th><td>" + tr("forward") + "</td></tr>";
	text += " <tr><th>Z</th><td>" + tr("backward") + "</td></tr>";
	text += " <tr><th>" + ctrlBadge + " + " + tr("Arrow down") + "</th><td>" + tr("backward")
					+ "</td></tr>";
	text += " <tr><th>" + shiftBadge + " + " + tr("Arrow down") + "</th><td>" + tr("backward")
					+ "</td></tr>";
	text += "</table>";

	// Rotation
	text += "<table style='margin-top: 10px;' border='1'>";
	text += " <tr><th colspan='2'>" + tr("Rotation") + "</th></tr>";
	text +=
		" <tr><th>" + tr("Mouse left button drag") + "</th><td>" + tr("Rotate camera") + "</td></tr>";
	text += " <tr><th>" + tr("Mouse right button drag") + "</th><td>"
					+ tr("Rotate camera around point") + "</td></tr>";
	text +=
		" <tr><th>" + tr("Mouse middle button drag") + "</th><td>" + tr("Roll camera") + "</td></tr>";
	text += " <tr><th>" + tr("Arrow up") + "</th><td>" + tr("up") + "</td></tr>";
	text += " <tr><th>" + tr("Arrow down") + "</th><td>" + tr("down") + "</td></tr>";
	text += " <tr><th>" + tr("Arrow left") + "</th><td>" + tr("left") + "</td></tr>";
	text += " <tr><th>" + tr("Arrow right") + "</th><td>" + tr("right") + "</td></tr>";
	text += " <tr><th>" + ctrlBadge + " + " + tr("Arrow left") + "</th><td>" + tr("Roll left")
					+ "</td></tr>";
	text += " <tr><th>" + ctrlBadge + " + " + tr("Arrow right") + "</th><td>" + tr("Roll right")
					+ "</td></tr>";
	text += "</table>";

	// Render Window, Keyframe, Flight
	text += "<td style='padding: 5px; background-color: #FDD'>";
	text += "<h3>" + tr("Render Window Keyframe / Flight") + "</h3>";

	// Flight
	text += "<table border='1'>";
	text += " <tr><th colspan='2'>" + tr("Flight") + "</th></tr>";
	text += " <tr><th>" + tr("Left mouse click") + "</th><td>" + tr("Increase speed") + "</td></tr>";
	text += " <tr><th>" + tr("Right mouse click") + "</th><td>" + tr("Decrease speed") + "</td></tr>";
	text +=
		" <tr><th>" + tr("Arrow keys") + "</th><td>" + tr("Move forward and sideward") + "</td></tr>";
	text += " <tr><th>" + shiftBadge + "+" + tr("Arrow keys") + "</th><td>" + tr("Move sideward only")
					+ "</td></tr>";
	text += " <tr><th>" + tr("Spacebar") + "</th><td>" + tr("Pause / Unpause") + "</td></tr>";
	text += " <tr><th>Z, X</th><td>" + tr("Roll rotation") + "</td></tr>";
	text += "</table>";

	// Keyframe
	text += "<table style='margin-top: 10px;' border='1'>";
	text += " <tr><th colspan='2'>" + tr("Keyframe") + "</th></tr>";
	text += " <tr><th>I</th><td>" + tr("Add Keyframe") + "</td></tr>";
	text += " <tr><th>M</th><td>" + tr("Modify current Keyframe") + "</td></tr>";
	text += " <tr><th>N</th><td>" + tr("Move to next Keyframe") + "</td></tr>";
	text += " <tr><th>P</th><td>" + tr("Move to previous Keyframe") + "</td></tr>";
	text += "</table>";

	text += "</td>";
	text += "</tr></table>";

	QLabel *label = new QLabel;
	label->setText(style + text);
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(label);
	QDialog *dialog = new QDialog(this);
	dialog->setLayout(layout);
	dialog->setWindowTitle(QObject::tr("HotKeys Cheatsheet"));
	dialog->show();
}

void RenderWindow::slotMenuAboutThirdParty()
{
	QString text = "<h2>Third Party</h2>";
	text += "<ul>";
	text += " <li><b>Dark Skin</b> based on <br>";
	text +=
		"		<a "
		"href=\"https://gist.github.com/QuantumCD/6245215\">gist.github.com/QuantumCD/6245215</"
		"a><br>thanks to QuantumCD</li>";
	text += " <li><b>Code highlighting in ui files</b><br>generated with<br>";
	text +=
		"		<a "
		"href=\"http://www.andre-simon.de/doku/highlight/highlight.php\">highlight</a><br>thanks to "
		"André Simon</li>";
	text += " <li><b>Export Mesh </b><br>generated with<br>";
	text +=
		"		<a "
		"href=\"https://github.com/pmneila/PyMCubes/\">PyMCubes</a><br>thanks to "
		"P. M. Neila</li>";
	text += " <li><b>Export Mesh </b><br>Designed with<br>";
	text +=
		"		<a "
		"href=\"http://algoholic.eu/export-meshes-from-mandelbulber/\">Stanford (PLY) mesh format "
		"Support</a><br>thanks to "
		"Stanislaw Adaszewski</li>";
	text += " <li><b>Fonts</b><br>";
	text +=
		"		<a href=\"http://typodermicfonts.com/\">Nasalization</a><br>"
		"thanks to Typodermic Fonts Inc.<br>";
	text += " For more information about font licenses, see README in fonts folder.</li>";
	text += "</ul>";
	QMessageBox::about(this, "About Third Party", text);
}

void RenderWindow::showDescriptionPopup()
{
	if (gPar->Get<bool>("description_popup_do_not_show_again")) return;
	if (gPar->Get<QString>("description") == "") return;

	QMessageBox *messageBox = new QMessageBox(this);
	messageBox->setText(gPar->Get<QString>("description"));
	messageBox->setWindowTitle(QObject::tr("Description"));
	messageBox->setIcon(QMessageBox::Information);
	messageBox->addButton(QMessageBox::Ok);
	QAbstractButton *btnOkDoNotShowAgain =
		messageBox->addButton(QObject::tr("Ok, don't show again"), QMessageBox::YesRole);
	messageBox->setDefaultButton(QMessageBox::Ok);
	int result = messageBox->exec();
	Q_UNUSED(result);
	if (messageBox->clickedButton() == btnOkDoNotShowAgain)
	{
		gPar->Set("description_popup_do_not_show_again", true);
	}
}

void RenderWindow::SaveSettingsToRecent(QString fileName)
{
	QFile recentFilesFile(systemDirectories.GetRecentFilesListFile());
	QStringList recentFiles;
	if (recentFilesFile.open(QFile::ReadOnly | QFile::Text))
	{
		QTextStream in(&recentFilesFile);
		QString recentFilesFileContent = in.readAll();
		recentFilesFile.close();
#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
		recentFiles = recentFilesFileContent.split(QRegExp("\n|\r\n|\r"), QString::KeepEmptyParts);
#else
		recentFiles =
			recentFilesFileContent.split(QRegularExpression("\n|\r\n|\r"), Qt::KeepEmptyParts);
#endif
		recentFiles.removeOne(fileName);
	}
	recentFiles.prepend(fileName);
	if (recentFiles.size() > 15) recentFiles.removeLast();
	if (!recentFilesFile.open(QFile::WriteOnly | QFile::Text))
	{
		qCritical() << "Cannot open file to save as recent!";
		return;
	}
	QTextStream out(&recentFilesFile);
	out << recentFiles.join("\n");
	recentFilesFile.close();
	slotPopulateRecentSettings();
}

void RenderWindow::slotMenuLoadExample()
{
	//	PreviewFileDialog dialog(this);
	//	dialog.setOption(QFileDialog::DontUseNativeDialog);
	//	dialog.setFileMode(QFileDialog::ExistingFile);
	//	dialog.setNameFilter(tr("Fractals (*.txt *.fract)"));
	//	dialog.setDirectory(QDir::toNativeSeparators(
	//		systemDirectories.sharedDir + QDir::separator() + "examples" + QDir::separator()));
	//	dialog.selectFile(QDir::toNativeSeparators(QFileInfo(systemData.lastSettingsFile).fileName()));
	//	dialog.setAcceptMode(QFileDialog::AcceptOpen);
	//	dialog.setWindowTitle(tr("Load example settings..."));
	//	QStringList filenames;
	//	if (dialog.exec())
	//	{
	//		filenames = dialog.selectedFiles();
	//		QString filename = QDir::toNativeSeparators(filenames.first());
	//		slotMenuLoadSettingsFromFile(filename);
	//	}

	gMainInterface->SynchronizeInterface(
		gPar, gParFractal, qInterface::read); // update appParam before loading new settings

	cSettingsBrowser browser;
	browser.SetInitialFileName(QDir::toNativeSeparators(
		systemDirectories.sharedDir + QDir::separator() + "examples" + QDir::separator()));
	browser.exec();
	QString fileName = browser.getSelectedFileName();
	if (!fileName.isEmpty())
	{
		slotMenuLoadSettingsFromFile(fileName);
	}
}

void RenderWindow::slotMenuLoadSettings()
{
	gMainInterface->SynchronizeInterface(
		gPar, gParFractal, qInterface::read); // update appParam before loading new settings

	PreviewFileDialog dialog(this);
	dialog.setOption(QFileDialog::DontUseNativeDialog);
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setNameFilter(tr("Fractals (*.txt *.fract)"));
	dialog.setDirectory(
		QDir::toNativeSeparators(QFileInfo(systemData.lastSettingsFile).absolutePath()));
	dialog.selectFile(QDir::toNativeSeparators(systemData.lastSettingsFile));
	dialog.setAcceptMode(QFileDialog::AcceptOpen);
	dialog.setWindowTitle(tr("Load settings..."));
	QStringList filenames;
	if (dialog.exec())
	{
		filenames = dialog.selectedFiles();
		QString filename = QDir::toNativeSeparators(filenames.first());
		slotMenuLoadSettingsFromFile(filename);
	}
}

void RenderWindow::slotMenuLoadSettingsFromFile(QString fileName)
{
	cSettings parSettings(cSettings::formatFullText);
	gMainInterface->DisablePeriodicRefresh();
	gInterfaceReadyForSynchronization = false;
	parSettings.LoadFromFile(fileName);
	parSettings.Decode(gPar, gParFractal, gAnimFrames, gKeyframes);
	gMainInterface->materialListModel->Regenerate();
	ui->widgetEffects->RegenerateLights();
	ui->widgetDockFractal->RegeneratePrimitives();

	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
	gInterfaceReadyForSynchronization = true;

	gMainInterface->ComboMouseClickUpdate();
	systemData.lastSettingsFile = fileName;
	SaveSettingsToRecent(fileName);
	setWindowTitle(QString("Mandelbulber (") + fileName + ")");
	gFlightAnimation->RefreshTable();
	gKeyframeAnimation->RefreshTable();
	showDescriptionPopup();
}

void RenderWindow::slotMenuLoadSettingsFromClipboard()
{
	gMainInterface->DisablePeriodicRefresh();

	gMainInterface->SynchronizeInterface(
		gPar, gParFractal, qInterface::read); // update appParam before loading new settings

	cSettings parSettings(cSettings::formatFullText);

	if (parSettings.LoadFromClipboard())
	{
		gMainInterface->DisablePeriodicRefresh();
		gInterfaceReadyForSynchronization = false;
		parSettings.Decode(gPar, gParFractal, gAnimFrames, gKeyframes);
		gMainInterface->materialListModel->Regenerate();
		ui->widgetEffects->RegenerateLights();
		ui->widgetDockFractal->RegeneratePrimitives();

		gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
		gInterfaceReadyForSynchronization = true;

		gMainInterface->ComboMouseClickUpdate();
		systemData.lastSettingsFile = "from clipboard";
		setWindowTitle(QString("Mandelbulber (") + "from clipboard" + ")");
		gFlightAnimation->RefreshTable();
		gKeyframeAnimation->RefreshTable();
		gMainInterface->ReEnablePeriodicRefresh();
		showDescriptionPopup();
	}
	else
	{
		cErrorMessage::showMessage(QObject::tr("Cannot load settings from clipboard!"),
			cErrorMessage::errorMessage, gMainInterface->mainWindow);
	}
}

void RenderWindow::slotMenuSettingsBrowser()
{
	gMainInterface->SynchronizeInterface(
		gPar, gParFractal, qInterface::read); // update appParam before loading new settings

	cSettingsBrowser browser;
	browser.SetInitialFileName(systemData.lastSettingsFile);
	browser.exec();
	QString fileName = browser.getSelectedFileName();
	if (!fileName.isEmpty())
	{
		slotMenuLoadSettingsFromFile(fileName);
	}
}

void RenderWindow::slotMenuRedo()
{
	gMainInterface->Redo();
}

void RenderWindow::ResetDocksPositions()
{
	// restoreGeometry(defaultGeometry);
	restoreState(defaultState);
	setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
	setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
}

void RenderWindow::slotMenuResetDocksPositions()
{
	// restoreState(gMainInterface->settings.value("mainWindowState").toByteArray());
	ResetDocksPositions();
	ui->dockWidget_histogram->hide();
	ui->dockWidget_info->hide();
	ui->dockWidget_queue_dock->hide();
	ui->dockWidget_animation->hide();
	ui->dockWidget_measurement->hide();
	if (ui->dockWidget_gamepad_dock != nullptr) ui->dockWidget_gamepad_dock->hide();

	tabifyDockWidget(ui->dockWidget_materialEditor, ui->dockWidget_pattern_lines);
	tabifyDockWidget(ui->dockWidget_pattern_lines, ui->dockWidget_primitives);
	tabifyDockWidget(ui->dockWidget_primitives, ui->dockWidget_effects);
	tabifyDockWidget(ui->dockWidget_effects, ui->dockWidget_image_adjustments);
	tabifyDockWidget(ui->dockWidget_image_adjustments, ui->dockWidget_rendering_engine);
	tabifyDockWidget(ui->dockWidget_rendering_engine, ui->dockWidget_objects);
	tabifyDockWidget(ui->dockWidget_objects, ui->dockWidget_histogram);

	addDockWidget(Qt::LeftDockWidgetArea, ui->dockWidget_Materials);
}

void RenderWindow::slotMenuAnimationDocksPositions()
{
	ResetDocksPositions();
	ui->dockWidget_histogram->hide();
	ui->dockWidget_info->hide();
	ui->dockWidget_animation->show();
	ui->toolBar->hide();
#ifdef USE_GAMEPAD
	ui->dockWidget_gamepad_dock->hide();
#endif
	ui->dockWidget_queue_dock->hide();

	tabifyDockWidget(ui->dockWidget_materialEditor, ui->dockWidget_pattern_lines);
	tabifyDockWidget(ui->dockWidget_pattern_lines, ui->dockWidget_primitives);
	tabifyDockWidget(ui->dockWidget_primitives, ui->dockWidget_effects);
	tabifyDockWidget(ui->dockWidget_effects, ui->dockWidget_image_adjustments);
	tabifyDockWidget(ui->dockWidget_image_adjustments, ui->dockWidget_rendering_engine);
	tabifyDockWidget(ui->dockWidget_rendering_engine, ui->dockWidget_objects);
	tabifyDockWidget(ui->dockWidget_objects, ui->dockWidget_histogram);

	addDockWidget(Qt::LeftDockWidgetArea, ui->dockWidget_Materials);
}

void RenderWindow::slotMenuSaveDocksPositions()
{
	gMainInterface->settings.setValue("mainWindowGeometry", saveGeometry());
	gMainInterface->settings.setValue("mainWindowState", saveState());
	// qDebug() << "settings saved";
}

void RenderWindow::slotMenuSaveImageAll()
{
	cImageSaveDialog dialog(this);
	dialog.setFileMode(QFileDialog::AnyFile);
	QStringList filters;
	filters << tr("images (*.jpg *.jpeg *.png *.exr *.tiff)");
	dialog.setNameFilters(filters);
	dialog.setDirectory(QDir::toNativeSeparators(QFileInfo(systemData.lastImageFile).absolutePath()));
	dialog.selectFile(QDir::toNativeSeparators(systemData.GetImageFileNameSuggestion()));
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.setWindowTitle(tr("Save image to file..."));
	QStringList filenames;
	if (dialog.exec())
	{
		filenames = dialog.selectedFiles();
		QString filename = QDir::toNativeSeparators(filenames.first());
		ImageFileSave::enumImageFileType imageFileType =
			ImageFileSave::ImageFileType(QFileInfo(filename).suffix());
		gApplication->processEvents();
		SaveImage(filename, imageFileType, gMainInterface->mainImage, gMainInterface->mainWindow);
		gApplication->processEvents();
		systemData.lastImageFile = filename;

		if (gPar->Get<bool>("save_settings_with_image"))
		{
			QString fileWithoutExtension = ImageFileSave::ImageNameWithoutExtension(filename);
			cSettings parSettings(cSettings::formatCondensedText);
			gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
			parSettings.CreateText(gPar, gParFractal, gAnimFrames, gKeyframes);
			parSettings.SaveToFile(fileWithoutExtension + ".fract");
		}
	}
}

void RenderWindow::slotMenuSaveImageJPEG()
{
	slotMenuSaveImage(
		ImageFileSave::IMAGE_FILE_TYPE_JPG, tr("JPEG images (*.jpg *.jpeg)"), "JPEG", "jpeg");
}

void RenderWindow::slotMenuSaveImagePNG()
{
	slotMenuSaveImage(ImageFileSave::IMAGE_FILE_TYPE_PNG, tr("PNG images (*.png)"), "PNG", "png");
}

#ifdef USE_EXR
void RenderWindow::slotMenuSaveImageEXR()
{
	slotMenuSaveImage(ImageFileSave::IMAGE_FILE_TYPE_EXR, tr("EXR images (*.exr)"), "EXR", "exr");
}
#endif // USE_EXR

#ifdef USE_TIFF
void RenderWindow::slotMenuSaveImageTIFF()
{
	slotMenuSaveImage(
		ImageFileSave::IMAGE_FILE_TYPE_TIFF, tr("TIFF images (*.tiff)"), "TIFF", "tiff");
}
#endif // USE_TIFF

void RenderWindow::slotMenuSaveImage(ImageFileSave::enumImageFileType imageFileType,
	QString nameFilter, QString titleType, QString defaultSuffix)
{
	cImageSaveDialog dialog(this);
	dialog.setFileMode(QFileDialog::AnyFile);
	dialog.setNameFilter(nameFilter);
	dialog.setDirectory(QDir::toNativeSeparators(QFileInfo(systemData.lastImageFile).absolutePath()));
	dialog.selectFile(QDir::toNativeSeparators(systemData.GetImageFileNameSuggestion()));
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.setWindowTitle(tr("Save image to %1 file...").arg(titleType));
	dialog.setDefaultSuffix(defaultSuffix);
	QStringList filenames;
	if (dialog.exec())
	{
		filenames = dialog.selectedFiles();
		QString filename = QDir::toNativeSeparators(filenames.first());
		gApplication->processEvents();
		SaveImage(filename, imageFileType, gMainInterface->mainImage, gMainInterface->mainWindow);
		gApplication->processEvents();
		systemData.lastImageFile = filename;

		if (gPar->Get<bool>("save_settings_with_image"))
		{
			QString fileWithoutExtension = ImageFileSave::ImageNameWithoutExtension(filename);
			cSettings parSettings(cSettings::formatCondensedText);
			gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
			parSettings.CreateText(gPar, gParFractal, gAnimFrames, gKeyframes);
			parSettings.SaveToFile(fileWithoutExtension + ".fract");
		}
	}
}

void RenderWindow::slotMenuSaveImagePNG16()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::AnyFile);
	dialog.setNameFilter(tr("PNG images (*.png)"));
	dialog.setDirectory(QDir::toNativeSeparators(QFileInfo(systemData.lastImageFile).absolutePath()));
	dialog.selectFile(QDir::toNativeSeparators(systemData.GetImageFileNameSuggestion()));
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.setWindowTitle(tr("Save image to %1 file...").arg("16-bit PNG"));
	dialog.setDefaultSuffix("png");
	QStringList filenames;
	if (dialog.exec())
	{
		filenames = dialog.selectedFiles();
		QString filename = QDir::toNativeSeparators(filenames.first());
		cProgressText::ProgressStatusText(tr("Saving %1 image").arg("16-bit PNG"),
			tr("Saving image started"), 0.0, cProgressText::progress_IMAGE);
		gApplication->processEvents();
		ImageFileSave::structSaveImageChannel saveImageChannel(
			ImageFileSave::IMAGE_CONTENT_COLOR, ImageFileSave::IMAGE_CHANNEL_QUALITY_16, "");
		ImageFileSave::ImageConfig imageConfig;
		imageConfig.insert(ImageFileSave::IMAGE_CONTENT_COLOR, saveImageChannel);
		ImageFileSavePNG imageSaver(
			ImageFileSave::ImageNameWithoutExtension(filename), gMainInterface->mainImage, imageConfig);
		imageSaver.SetAppendAlphaCustom(false);
		imageSaver.SaveImage();
		cProgressText::ProgressStatusText(tr("Saving %1 image").arg("16-bit PNG"),
			tr("Saving image finished"), 1.0, cProgressText::progress_IMAGE);
		gApplication->processEvents();
		systemData.lastImageFile = filename;
	}
}

void RenderWindow::slotMenuSaveImagePNG16Alpha()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::AnyFile);
	dialog.setNameFilter(tr("PNG images (*.png)"));
	dialog.setDirectory(QDir::toNativeSeparators(QFileInfo(systemData.lastImageFile).absolutePath()));
	dialog.selectFile(QDir::toNativeSeparators(systemData.GetImageFileNameSuggestion()));
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.setWindowTitle(tr("Save image to %1 file...").arg("16-bit PNG + alpha channel"));
	dialog.setDefaultSuffix("png");
	QStringList filenames;
	if (dialog.exec())
	{
		filenames = dialog.selectedFiles();
		QString filename = QDir::toNativeSeparators(filenames.first());
		cProgressText::ProgressStatusText(tr("Saving %1 image").arg("16-bit PNG + alpha channel"),
			tr("Saving image started"), 0.0, cProgressText::progress_IMAGE);
		gApplication->processEvents();
		ImageFileSave::structSaveImageChannel saveImageChannel(
			ImageFileSave::IMAGE_CONTENT_COLOR, ImageFileSave::IMAGE_CHANNEL_QUALITY_16, "");
		ImageFileSave::ImageConfig imageConfig;
		imageConfig.insert(ImageFileSave::IMAGE_CONTENT_COLOR, saveImageChannel);
		ImageFileSavePNG imageSaver(
			ImageFileSave::ImageNameWithoutExtension(filename), gMainInterface->mainImage, imageConfig);
		imageSaver.SetAppendAlphaCustom(true);
		imageSaver.SaveImage();
		cProgressText::ProgressStatusText(tr("Saving %1 image").arg("16-bit PNG + alpha channel"),
			tr("Saving image finished"), 1.0, cProgressText::progress_IMAGE);
		gApplication->processEvents();
		systemData.lastImageFile = filename;
	}
}

void RenderWindow::slotMenuSaveSettings()
{
	cSettings parSettings(cSettings::formatCondensedText);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	parSettings.CreateText(gPar, gParFractal, gAnimFrames, gKeyframes);

	QFileDialog dialog(this);
	dialog.setOption(QFileDialog::DontUseNativeDialog);
	dialog.setFileMode(QFileDialog::AnyFile);
	dialog.setNameFilter(tr("Fractals (*.txt *.fract)"));
	dialog.setDirectory(
		QDir::toNativeSeparators(QFileInfo(systemData.lastSettingsFile).absolutePath()));
	dialog.selectFile(
		QDir::toNativeSeparators(QFileInfo(systemData.lastSettingsFile).completeBaseName()));
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.setWindowTitle(tr("Save settings..."));
	dialog.setDefaultSuffix("fract");
	QStringList filenames;
	if (dialog.exec())
	{
		filenames = dialog.selectedFiles();
		QString filename = QDir::toNativeSeparators(filenames.first());
		parSettings.SaveToFile(filename);
		systemData.lastSettingsFile = filename;
		SaveSettingsToRecent(filename);
		setWindowTitle(QString(APP_NAME) + " (" + filename + ")");

		// QString hash = parSettings.GetHashCode();
		// cThumbnail thumbnail(gPar, gParFractal, 200, 200);
		// thumbnail.Render();
		// thumbnail.Save(systemData.thumbnailDir + hash);
	}
}

void RenderWindow::slotMenuSaveSettingsToClipboard()
{
	cSettings parSettings(cSettings::formatCondensedText);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	parSettings.CreateText(gPar, gParFractal, gAnimFrames, gKeyframes);
	parSettings.SaveToClipboard();
	cErrorMessage::showMessage(
		QObject::tr("Settings saved to clipboard"), cErrorMessage::infoMessage);
}

void RenderWindow::slotMenuUndo()
{
	gMainInterface->Undo();
}

void RenderWindow::slotMenuRenderImage()
{
	gMainInterface->StartRender();
}

void RenderWindow::slotMenuStopRendering()
{
	gMainInterface->StopRender();
}

void RenderWindow::slotUpdateDocksAndToolbarByAction()
{
	// Animation dock
	if (ui->actionShow_animation_dock->isChecked() != ui->dockWidget_animation->isVisible())
	{
		if (ui->actionShow_animation_dock->isChecked())
		{
			addDockWidget(Qt::BottomDockWidgetArea, ui->dockWidget_animation);
		}
		else
		{
			removeDockWidget(ui->dockWidget_animation);
		}
		ui->dockWidget_animation->setVisible(ui->actionShow_animation_dock->isChecked());
	}

	// Information dock
	if (ui->actionShow_info_dock->isChecked() != ui->dockWidget_info->isVisible())
	{
		if (ui->actionShow_info_dock->isChecked())
		{
			addDockWidget(Qt::LeftDockWidgetArea, ui->dockWidget_info);
		}
		else
		{
			removeDockWidget(ui->dockWidget_info);
		}
		ui->dockWidget_info->setVisible(ui->actionShow_info_dock->isChecked());
	}

	// Histogram dock
	if (ui->actionShow_statistics_dock->isChecked() != ui->dockWidget_histogram->isVisible())
	{
		if (ui->actionShow_statistics_dock->isChecked())
		{
			addDockWidget(Qt::LeftDockWidgetArea, ui->dockWidget_histogram);
		}
		else
		{
			removeDockWidget(ui->dockWidget_histogram);
		}
		ui->dockWidget_histogram->setVisible(ui->actionShow_statistics_dock->isChecked());
	}

	// Toolbar
	if (ui->actionShow_toolbar->isChecked() != ui->toolBar->isVisible())
	{
		ui->toolBar->setVisible(ui->actionShow_toolbar->isChecked());
	}

// Gamepad dock
#ifdef USE_GAMEPAD
	if (ui->actionShow_gamepad_dock->isChecked() != ui->dockWidget_gamepad_dock->isVisible())
	{
		if (ui->actionShow_gamepad_dock->isChecked())
		{
			addDockWidget(Qt::RightDockWidgetArea, ui->dockWidget_gamepad_dock);
		}
		else
		{
			removeDockWidget(ui->dockWidget_gamepad_dock);
		}
		ui->dockWidget_gamepad_dock->setVisible(ui->actionShow_gamepad_dock->isChecked());
	}
#endif

	// Queue dock
	if (ui->actionShow_queue_dock->isChecked() != ui->dockWidget_queue_dock->isVisible())
	{
		if (ui->actionShow_queue_dock->isChecked())
		{
			addDockWidget(Qt::RightDockWidgetArea, ui->dockWidget_queue_dock);
		}
		else
		{
			removeDockWidget(ui->dockWidget_queue_dock);
		}
		ui->dockWidget_queue_dock->setVisible(ui->actionShow_queue_dock->isChecked());
	}

	// Queue dock
	if (ui->actionShow_measurement_dock->isChecked() != ui->dockWidget_measurement->isVisible())
	{
		if (ui->actionShow_measurement_dock->isChecked())
		{
			addDockWidget(Qt::RightDockWidgetArea, ui->dockWidget_measurement);
		}
		else
		{
			removeDockWidget(ui->dockWidget_measurement);
		}
		ui->dockWidget_measurement->setVisible(ui->actionShow_measurement_dock->isChecked());
	}
}

void RenderWindow::slotUpdateDocksAndToolbarByView() const
{
	// Animation dock
	if (ui->actionShow_animation_dock->isChecked() != ui->dockWidget_animation->isVisible())
	{
		ui->actionShow_animation_dock->setChecked(ui->dockWidget_animation->isVisible());
	}

	// Log dock
	if (ui->actionShow_info_dock->isChecked() != ui->dockWidget_info->isVisible())
	{
		ui->actionShow_info_dock->setChecked(ui->dockWidget_info->isVisible());
	}

	// Histogram dock
	if (ui->actionShow_statistics_dock->isChecked() != ui->dockWidget_histogram->isVisible())
	{
		ui->actionShow_statistics_dock->setChecked(ui->dockWidget_histogram->isVisible());
	}

	// Toolbar
	if (ui->actionShow_toolbar->isChecked() != ui->toolBar->isVisible())
	{
		ui->actionShow_toolbar->setChecked(ui->toolBar->isVisible());
	}

#ifdef USE_GAMEPAD
	// Gamepad dock
	if (ui->actionShow_gamepad_dock->isChecked() != ui->dockWidget_gamepad_dock->isVisible())
	{
		ui->actionShow_gamepad_dock->setChecked(ui->dockWidget_gamepad_dock->isVisible());
	}
#endif

	// Queue dock
	if (ui->actionShow_queue_dock->isChecked() != ui->dockWidget_queue_dock->isVisible())
	{
		ui->actionShow_queue_dock->setChecked(ui->dockWidget_queue_dock->isVisible());
	}

	// Queue dock
	if (ui->actionShow_measurement_dock->isChecked() != ui->dockWidget_measurement->isVisible())
	{
		ui->actionShow_measurement_dock->setChecked(ui->dockWidget_measurement->isVisible());
	}
}

void RenderWindow::slotStackAllDocks()
{
	tabifyDockWidget(ui->dockWidget_materialEditor, ui->dockWidget_pattern_lines);
	tabifyDockWidget(ui->dockWidget_pattern_lines, ui->dockWidget_effects);
	tabifyDockWidget(ui->dockWidget_effects, ui->dockWidget_image_adjustments);
	tabifyDockWidget(ui->dockWidget_image_adjustments, ui->dockWidget_rendering_engine);
	tabifyDockWidget(ui->dockWidget_rendering_engine, ui->dockWidget_objects);
	tabifyDockWidget(ui->dockWidget_objects, ui->dockWidget_histogram);
	tabifyDockWidget(ui->dockWidget_histogram, ui->dockWidget_info);
}

void RenderWindow::slotDetachMainImage()
{
	if (ui->actionDetach_image_from_main_window->isChecked())
	{
		gMainInterface->DetachMainImageWidget();
	}
	else
	{
		gMainInterface->AttachMainImageWidget();
	}
}

void RenderWindow::slotMenuRandomizeAll()
{
	gMainInterface->RandomizeLocalSettings(this);
}

void RenderWindow::slotCleanSettings()
{
	gMainInterface->CleanSettings();
}

void RenderWindow::slotSaveSettingsAsDefaut()
{
	cSettings parSettings(cSettings::formatCondensedText);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	parSettings.CreateText(gPar, gParFractal, gAnimFrames, gKeyframes);
	QString filename = QDir::toNativeSeparators(systemDirectories.GetDefaultSettingsFile());
	parSettings.SaveToFile(filename);
}

void RenderWindow::slotResetToDefault()
{
	QString filename = QDir::toNativeSeparators(systemDirectories.GetDefaultSettingsFile());
	if (QFile::exists(filename))
	{
		gMainInterface->SynchronizeInterface(
			gPar, gParFractal, qInterface::read); // update appParam before loading new settings
		slotMenuLoadSettingsFromFile(filename);
	}
	else
	{
		gPar->ResetAllToDefault();
		for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
		{
			gParFractal->at(i)->ResetAllToDefault();
			gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
			gMainInterface->StartupDefaultSettings();
		}
	}
}
void RenderWindow::slotDeleteDefaultSettings()
{
	QString filename = QDir::toNativeSeparators(systemDirectories.GetDefaultSettingsFile());
	if (QFile::exists(filename))
	{
		QFile::remove(filename);
	}
}

// ============================================================
// 3x3lion Focus Mode — clean viewer with all panels hidden
// ============================================================

void RenderWindow::slotToggleFocusMode()
{
	focusModeActive = !focusModeActive;

	if (focusModeActive)
	{
		savedStateBeforeFocus = saveState();

		ui->dockWidget_image_adjustments->hide();
		ui->dockWidget_navigation->hide();
		ui->dockWidget_effects->hide();
		ui->dockWidget_fake_lights->hide();
		ui->dockWidget_pattern_lines->hide();
		ui->dockWidget_primitives->hide();
		ui->dockWidget_objects->hide();
		ui->dockWidget_rendering_engine->hide();
		ui->dockWidget_info->hide();
		ui->dockWidget_animation->hide();
		ui->dockWidget_histogram->hide();
		ui->dockWidget_queue_dock->hide();
		ui->dockWidget_measurement->hide();
		ui->dockWidget_materialEditor->hide();
		ui->dockWidget_Materials->hide();
		if (ui->dockWidget_gamepad_dock) ui->dockWidget_gamepad_dock->hide();
		ui->toolBar->hide();
		ui->menubar->hide();
		ui->statusbar->hide();
	}
	else
	{
		ui->menubar->show();
		ui->statusbar->show();
		if (!savedStateBeforeFocus.isEmpty())
			restoreState(savedStateBeforeFocus);
		else
			slotMenuResetDocksPositions();
	}
}

void RenderWindow::slotApplyFocusModeOnStartup()
{
	focusModeActive = true;

	ui->dockWidget_image_adjustments->hide();
	ui->dockWidget_navigation->hide();
	ui->dockWidget_effects->hide();
	ui->dockWidget_fake_lights->hide();
	ui->dockWidget_pattern_lines->hide();
	ui->dockWidget_primitives->hide();
	ui->dockWidget_objects->hide();
	ui->dockWidget_rendering_engine->hide();
	ui->dockWidget_info->hide();
	ui->dockWidget_animation->hide();
	ui->dockWidget_histogram->hide();
	ui->dockWidget_queue_dock->hide();
	ui->dockWidget_measurement->hide();
	ui->dockWidget_materialEditor->hide();
	ui->dockWidget_Materials->hide();
	if (ui->dockWidget_gamepad_dock) ui->dockWidget_gamepad_dock->hide();
	ui->toolBar->hide();
	ui->menubar->hide();
	ui->statusbar->hide();
}

void RenderWindow::slotShowViewerContextMenu(const QPoint &pos)
{
	QMenu menu(this);
	menu.setStyleSheet(
		"QMenu { background: #1e1e2e; color: #cdd6f4; border: 1px solid #313244; }"
		"QMenu::item:selected { background: #313244; }"
		"QMenu::separator { background: #313244; height: 1px; margin: 4px 8px; }");

	QAction *actRender = menu.addAction("Render (Ctrl+R)");
	connect(actRender, &QAction::triggered, this, [this]() {
		gMainInterface->StartRender();
	});

	QAction *actStop = menu.addAction("Stop (Ctrl+T)");
	connect(actStop, &QAction::triggered, this, []() {
		gMainInterface->StopRender();
	});

	menu.addSeparator();

	QAction *actNav = menu.addAction("Navigation (F1)");
	actNav->setCheckable(true);
	actNav->setChecked(ui->dockWidget_navigation->isVisible());
	connect(actNav, &QAction::triggered, this, [this](bool checked) {
		ui->dockWidget_navigation->setVisible(checked);
	});

	QAction *actObj = menu.addAction("Objects / Fractals (F2)");
	actObj->setCheckable(true);
	actObj->setChecked(ui->dockWidget_objects->isVisible());
	connect(actObj, &QAction::triggered, this, [this](bool checked) {
		ui->dockWidget_objects->setVisible(checked);
	});

	QAction *actEffects = menu.addAction("Effects (F3)");
	actEffects->setCheckable(true);
	actEffects->setChecked(ui->dockWidget_effects->isVisible());
	connect(actEffects, &QAction::triggered, this, [this](bool checked) {
		ui->dockWidget_effects->setVisible(checked);
	});

	QAction *actImg = menu.addAction("Image Adjustments (F4)");
	actImg->setCheckable(true);
	actImg->setChecked(ui->dockWidget_image_adjustments->isVisible());
	connect(actImg, &QAction::triggered, this, [this](bool checked) {
		ui->dockWidget_image_adjustments->setVisible(checked);
	});

	QAction *actEngine = menu.addAction("Rendering Engine (F5)");
	actEngine->setCheckable(true);
	actEngine->setChecked(ui->dockWidget_rendering_engine->isVisible());
	connect(actEngine, &QAction::triggered, this, [this](bool checked) {
		ui->dockWidget_rendering_engine->setVisible(checked);
	});

	QAction *actMat = menu.addAction("Materials (F6)");
	actMat->setCheckable(true);
	actMat->setChecked(ui->dockWidget_Materials->isVisible());
	connect(actMat, &QAction::triggered, this, [this](bool checked) {
		ui->dockWidget_Materials->setVisible(checked);
	});

	QAction *actAnim = menu.addAction("Animation (F7)");
	actAnim->setCheckable(true);
	actAnim->setChecked(ui->dockWidget_animation->isVisible());
	connect(actAnim, &QAction::triggered, this, [this](bool checked) {
		ui->dockWidget_animation->setVisible(checked);
	});

	QAction *actLights = menu.addAction("Fake Lights (F8)");
	actLights->setCheckable(true);
	actLights->setChecked(ui->dockWidget_fake_lights->isVisible());
	connect(actLights, &QAction::triggered, this, [this](bool checked) {
		ui->dockWidget_fake_lights->setVisible(checked);
	});

	QAction *actPrim = menu.addAction("Primitives");
	actPrim->setCheckable(true);
	actPrim->setChecked(ui->dockWidget_primitives->isVisible());
	connect(actPrim, &QAction::triggered, this, [this](bool checked) {
		ui->dockWidget_primitives->setVisible(checked);
	});

	QAction *actPattern = menu.addAction("Pattern Lines");
	actPattern->setCheckable(true);
	actPattern->setChecked(ui->dockWidget_pattern_lines->isVisible());
	connect(actPattern, &QAction::triggered, this, [this](bool checked) {
		ui->dockWidget_pattern_lines->setVisible(checked);
	});

	menu.addSeparator();

	QAction *actToolbar = menu.addAction("Preset Toolbar (F9)");
	actToolbar->setCheckable(true);
	actToolbar->setChecked(ui->toolBar->isVisible());
	connect(actToolbar, &QAction::triggered, this, [this](bool checked) {
		ui->toolBar->setVisible(checked);
	});

	QAction *actMenuBar = menu.addAction("Menu Bar (F10)");
	actMenuBar->setCheckable(true);
	actMenuBar->setChecked(ui->menubar->isVisible());
	connect(actMenuBar, &QAction::triggered, this, [this](bool checked) {
		ui->menubar->setVisible(checked);
	});

	menu.addSeparator();

	QAction *actFocus = menu.addAction("Focus Mode (F11)");
	connect(actFocus, &QAction::triggered, this, &RenderWindow::slotToggleFocusMode);

	QAction *actShowAll = menu.addAction("Show All Panels");
	connect(actShowAll, &QAction::triggered, this, [this]() {
		focusModeActive = false;
		ui->menubar->show();
		ui->statusbar->show();
		slotMenuResetDocksPositions();
		ui->toolBar->show();
	});

	menu.addSeparator();

	QAction *actFullscreen = menu.addAction("Fullscreen Viewer (Double-click)");
	connect(actFullscreen, &QAction::triggered, this, &RenderWindow::ToggleFullScreen);

	menu.exec(mapToGlobal(pos));
}

void RenderWindow::SetupFocusModeShortcuts()
{
	auto addToggle = [this](const char *key, QWidget *w) {
		QShortcut *sc = new QShortcut(QKeySequence(key), this);
		connect(sc, &QShortcut::activated, this, [w]() { w->setVisible(!w->isVisible()); });
	};

	addToggle("F1", ui->dockWidget_navigation);
	addToggle("F2", ui->dockWidget_objects);
	addToggle("F3", ui->dockWidget_effects);
	addToggle("F4", ui->dockWidget_image_adjustments);
	addToggle("F5", ui->dockWidget_rendering_engine);
	addToggle("F6", ui->dockWidget_Materials);
	addToggle("F7", ui->dockWidget_animation);
	addToggle("F8", ui->dockWidget_fake_lights);

	auto *scToolbar = new QShortcut(QKeySequence("F9"), this);
	connect(scToolbar, &QShortcut::activated, this, [this]() {
		ui->toolBar->setVisible(!ui->toolBar->isVisible());
	});

	auto *scMenubar = new QShortcut(QKeySequence("F10"), this);
	connect(scMenubar, &QShortcut::activated, this, [this]() {
		ui->menubar->setVisible(!ui->menubar->isVisible());
	});

	auto *scFocus = new QShortcut(QKeySequence("F11"), this);
	connect(scFocus, &QShortcut::activated, this, &RenderWindow::slotToggleFocusMode);

	// Right-click anywhere on central widget shows context menu
	ui->centralwidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->centralwidget, &QWidget::customContextMenuRequested, this,
		&RenderWindow::slotShowViewerContextMenu);

	// Double-click on fractal viewer → fullscreen
	if (gMainInterface && gMainInterface->renderedImage)
	{
		connect(gMainInterface->renderedImage, &RenderedImage::doubleClicked, this,
			&RenderWindow::slotToggleFocusMode);
	}
}

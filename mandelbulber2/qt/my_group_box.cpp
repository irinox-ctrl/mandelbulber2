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
 * MyGroupBox class - promoted MyGroupBox widget with context menu
 */

#include "my_group_box.h"

#include <QTimer>
#include <qaction.h>
#include <qicon.h>
#include <qlist.h>
#include <qmenu.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qstring.h>

#include "src/interface.hpp"
#include "src/parameters.hpp"

MyGroupBox::MyGroupBox(QWidget *parent) : QGroupBox(parent), CommonMyWidgetWrapper(this)
{
	defaultValue = false;
	firstDisplay = true;
	actionResetAllToDefault = nullptr;
	actionLoadToThisGroupbox = nullptr;
	actionSaveFromThisGroupbox = nullptr;
	actionRandomize = nullptr;
	connect(this, &QGroupBox::toggled, this, &MyGroupBox::slotToggled);
	// Delay initial visibility update until all children are created.
	// Use current isChecked() at invocation time (not capture time) to avoid
	// race with SynchronizeInterfaceWindow setting checked=true before this fires.
	QTimer::singleShot(0, this, [this]() { slotToggled(isChecked()); });
}

void MyGroupBox::resetToDefault()
{
	setChecked(defaultValue);
	emit toggled(defaultValue);
}

QString MyGroupBox::getDefaultAsString()
{
	return defaultValue ? "true" : "false";
}

QString MyGroupBox::getFullParameterName()
{
	return parameterName;
}

void MyGroupBox::paintEvent(QPaintEvent *event)
{
	if (firstDisplay)
	{
		originalText = title();
		firstDisplay = false;
	}
	QString displayTitle = originalText;
	if (!isChecked())
	{
		displayTitle += " ... ";
	}

	if (isChecked() != GetDefault())
	{
		displayTitle += " *";
	}
	setTitle(displayTitle);
	QGroupBox::paintEvent(event);
}

bool MyGroupBox::GetDefault()
{
	if (parameterContainer && !gotDefault)
	{
		int val = parameterContainer->GetDefault<int>(parameterName);
		defaultValue = val;
		gotDefault = true;
		setToolTipText();
	}
	return defaultValue;
}

void MyGroupBox::slotToggled(bool on)
{
	QList<QWidget *> list = findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);
	for (auto &widget : list)
	{
		if (on)
		{
			widget->show();
		}
		else
		{
			widget->hide();
		}
	}
	// Laat de layout weten dat onze sizeHint veranderd is
	updateGeometry();
}


QSize MyGroupBox::sizeHint() const
{
	if (!isCheckable() || isChecked())
	{
		return QGroupBox::sizeHint();
	}
	// Ingeklapt: alleen titelbar hoogte
	int titleHeight = fontMetrics().height() + 10;
	return QSize(QGroupBox::sizeHint().width(), titleHeight);
}

QSize MyGroupBox::minimumSizeHint() const
{
	if (!isCheckable() || isChecked())
	{
		return QGroupBox::minimumSizeHint();
	}
	int titleHeight = fontMetrics().height() + 10;
	return QSize(50, titleHeight);
}
void MyGroupBox::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu *menu = new QMenu; // deleted by contextMenuEvent()
	QIcon iconReset = QIcon(":system/icons/edit-undo.png");
	QIcon iconLoad = QIcon(":system/icons/document-open.svg");
	QIcon iconSave = QIcon(":system/icons/document-save.svg");
	QIcon iconRandomize = QIcon(":gradient/icons/dice_colors.svg");

	actionLoadToThisGroupbox = menu->addAction(tr("Load to this groupbox"));
	actionLoadToThisGroupbox->setIcon(iconLoad);

	actionSaveFromThisGroupbox = menu->addAction(tr("Save from this groupbox"));
	actionSaveFromThisGroupbox->setIcon(iconSave);

	actionResetAllToDefault = menu->addAction(tr("Reset all to default"));
	actionResetAllToDefault->setIcon(iconReset);

	actionRandomize = menu->addAction(tr("Randomize"));
	actionRandomize->setIcon(iconRandomize);

	connect(actionLoadToThisGroupbox, &QAction::triggered, this, &MyGroupBox::slotLoadToThisGroupbox);
	connect(actionSaveFromThisGroupbox, &QAction::triggered, this, &MyGroupBox::slotSaveFromThisGroupbox);
	connect(actionResetAllToDefault, &QAction::triggered, this, &MyGroupBox::slotResetAllToDefault);
	connect(actionRandomize, &QAction::triggered, this, &MyGroupBox::slotRandomize);

	CommonMyWidgetWrapper::contextMenuEvent(event, menu);
}

void MyGroupBox::slotResetAllToDefault()
{
	QList<QWidget *> listOfWidgets = findChildren<QWidget *>();

	foreach (QWidget *widget, listOfWidgets)
	{
		CommonMyWidgetWrapper *myWidget = dynamic_cast<CommonMyWidgetWrapper *>(widget);
		if (myWidget)
		{
			myWidget->resetToDefault();
		}
	}
}

void MyGroupBox::slotLoadToThisGroupbox()
{
	gMainInterface->LoadLocalSettings(this);
}
void MyGroupBox::slotSaveFromThisGroupbox()
{
	gMainInterface->SaveLocalSettings(this);
}
void MyGroupBox::slotRandomize()
{
	gMainInterface->RandomizeLocalSettings(this);
}

void MyGroupBox::UpdateScriptAppearance(bool hasScript) {}

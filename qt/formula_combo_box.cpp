/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2017-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * Authors: Sebastian Jennen (jenzebas@gmail.com)
 *
 * cFormulaComboBox - Formula Combobox for the selection of the used formula
 * This is a combobox with icons and autocomplete for fast formula access
 * The item list gets populated with the populateItemsFromFractalList()
 *
 * autocomplete adopted from here:
 * http://stackoverflow.com/questions/4827207/how-do-i-filter-the-pyqt-qcombobox-items-based-on-the-text-input
 */

#include "formula_combo_box.h"

#include <QDebug>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QWidget>

#include "src/common_math.h"
#include "src/parameters.hpp"
#include "src/random.hpp"
#include "src/write_log.hpp"

QMap<QString, QIcon> cFormulaComboBox::iconCache;

cFormulaComboBox::cFormulaComboBox(QWidget *parent) : QComboBox(parent), CommonMyWidgetWrapper(this)
{
	defaultValue = 0;
	QFontMetrics fm(font());
	int pixelFontSize = fm.height();
	int iconSize = pixelFontSize * 3;
	setIconSize(QSize(iconSize, iconSize));
	setFixedHeight(iconSize);

	setFocusPolicy(Qt::StrongFocus);
	setEditable(true);

	// add a filter model to filter matching items
	pFilterModel = new QSortFilterProxyModel(this);
	pFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	pFilterModel->setSourceModel(model());

	// add a completer, which uses the filter model
	completer = new QCompleter(pFilterModel, this);
	// always show all (filtered) completions
	completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);

	setCompleter(completer);

	// connect signals
	connect(lineEdit(), &QLineEdit::textEdited, pFilterModel, &QSortFilterProxyModel::setFilterFixedString);
}

cFormulaComboBox::~cFormulaComboBox()
{
	// iconCache.clear(); !!! it's is static member and shoudl be kept to the end of the universe
}

void cFormulaComboBox::onCompleterActivated(QString text)
{
	WriteLogString("onCompleterActivated: text -> ", text, 3);
	// on selection of an item from the completer, select the corresponding item from combobox
	if (!text.isEmpty())
	{
		int index = findText(text);
		setCurrentIndex(index);
		emit currentIndexChanged(index);
	}
}

void cFormulaComboBox::setModelColumn(int column)
{
	// on model column change, update the model column of the filter and completer as well
	completer->setCompletionColumn(column);
	pFilterModel->setFilterKeyColumn(column);
	QComboBox::setModelColumn(column);
}

void cFormulaComboBox::setModel(QAbstractItemModel *model)
{
	// on model change, update the models of the filter and completer as well
	QComboBox::setModel(model);
	pFilterModel->setSourceModel(model);
	completer->setModel(pFilterModel);
}

void cFormulaComboBox::populateItemsFromFractalList(QList<cAbstractFractal *> fractalList,
	QList<QPair<int, QString> /* */> insertHeader, int randomSeedForColors)
{
	clear();
	for (int f = 0; f < fractalList.size(); f++)
	{
		addItem(
			GetIconFromCache(fractalList[f]->getIconName()), fractalList[f]->getNameInComboBox(), f);
	}

	// set headings and separator of formulas and transforms
	QFont fontHeading;
	fontHeading.setBold(true);

	// 3x3lion: Use Catppuccin Mocha category colors for better organization
	static const QColor kCatppuccinBases[] = {
		QColor(0x1e, 0x1e, 0x2e), // Base
		QColor(0x18, 0x18, 0x25), // Mantle
		QColor(0x11, 0x11, 0x1b), // Crust
	};
	static const QColor kCatppuccinAccents[] = {
		QColor(0x31, 0x32, 0x44), // Surface0
		QColor(0x45, 0x47, 0x5a), // Surface1
		QColor(0x58, 0x5b, 0x70), // Surface2
		QColor(0x2a, 0x2b, 0x3c), // Slightly lighter than Base
		QColor(0x24, 0x24, 0x36), // Between Base and Mantle
	};

	QPalette palette = window()->palette();
	QColor globalColor = palette.window().color();
	int brightness = globalColor.value();

	int rBase = globalColor.red();
	int gBase = globalColor.green();
	int bBase = globalColor.blue();

	cRandom random;
	random.Initialize(randomSeedForColors);

	int previousComboIndex = 0;

	for (int hIndex = 0; hIndex < insertHeader.size(); hIndex++)
	{
		QPair<int, QString> header = insertHeader.at(hIndex);
		int comboIndex = -1;
		for (int fIndex = 0; fIndex < fractalList.size(); fIndex++)
		{
			if (fractalList.at(fIndex)->getInternalId() == header.first)
			{
				comboIndex = fIndex + 2 * hIndex;
			}
		}

		if (comboIndex == -1)
		{
			qCritical() << "Cannot insert combobox Header!";
		}
		else
		{
			QColor itemsColor;
			// Use alternating Catppuccin-based colors for dark themes
			if (brightness <= 60)
			{
				itemsColor = kCatppuccinAccents[hIndex % 5];
			}
			else
			{
				int r = random.Random(40) + rBase - 20;
				r = clamp(r, 0, 255);
				int g = random.Random(40) + gBase - 20;
				g = clamp(g, 0, 255);
				int b = random.Random(40) + bBase - 20;
				b = clamp(b, 0, 255);
				itemsColor = QColor(r, g, b);
			}

			for (int i = previousComboIndex; i < comboIndex; i++)
			{
				setItemData(i, itemsColor, Qt::BackgroundRole);
			}

			previousComboIndex = comboIndex;

			// Category header with accent styling
			QString headerText = QString::fromUtf8("\u25BC ") + header.second;
			insertItem(comboIndex, headerText);
			setItemData(comboIndex, fontHeading, Qt::FontRole);
			setItemData(comboIndex, Qt::AlignCenter, Qt::TextAlignmentRole);
			if (brightness <= 60)
			{
				setItemData(comboIndex, QColor(0x89, 0xb4, 0xfa), Qt::ForegroundRole);
				setItemData(comboIndex, QColor(0x18, 0x18, 0x25), Qt::BackgroundRole);
			}
			qobject_cast<QStandardItemModel *>(model())->item(comboIndex)->setEnabled(false);
			insertSeparator(comboIndex);
		}
	}
}

int cFormulaComboBox::GetDefault()
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

void cFormulaComboBox::paintEvent(QPaintEvent *event)
{
	GetDefault();
	QComboBox::paintEvent(event);
}

void cFormulaComboBox::contextMenuEvent(QContextMenuEvent *event)
{
	CommonMyWidgetWrapper::contextMenuEvent(event);
}

QIcon cFormulaComboBox::GetIconFromCache(const QString &filename)
{
	if (!iconCache.contains(filename))
	{
		iconCache.insert(filename, QIcon(filename));
	}
	return iconCache[filename];
}

void cFormulaComboBox::resetToDefault()
{
	int selection = defaultValue;
	if (parameterName == QString("formula"))
	{
		for (int i = 0; i < newFractalList.size(); i++)
		{
			if (newFractalList[i]->getInternalId() == selection)
			{
				selection = findData(i);
				break;
			}
		}
	}
	setCurrentIndex(selection);
}

QString cFormulaComboBox::getDefaultAsString()
{
	return QString::number(defaultValue);
}

QString cFormulaComboBox::getFullParameterName()
{
	return parameterName;
}

void cFormulaComboBox::UpdateScriptAppearance(bool hasScript) {}

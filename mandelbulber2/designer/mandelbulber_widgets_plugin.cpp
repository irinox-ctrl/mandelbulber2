/**
 * Mandelbulber Qt Designer Plugin — Implementation
 *
 * Uses QDesignerCustomWidgetCollectionInterface to bundle all widgets
 * into a single shared library.
 */

#include "mandelbulber_widgets_plugin.h"

#include <QtPlugin>

#include "my_double_spin_box.h"
#include "my_spin_box.h"
#include "my_check_box.h"
#include "my_combo_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_color_button.h"

// ============================================================
// Base plugin
// ============================================================
MandelbulberWidgetPlugin::MandelbulberWidgetPlugin() : initialized(false) {}

QIcon MandelbulberWidgetPlugin::icon() const
{
	return QIcon();
}

void MandelbulberWidgetPlugin::initialize(QDesignerFormEditorInterface *core)
{
	Q_UNUSED(core)
	if (initialized) return;
	initialized = true;
}

// ============================================================
// MyDoubleSpinBox
// ============================================================
MyDoubleSpinBoxPlugin::MyDoubleSpinBoxPlugin() : MandelbulberWidgetPlugin() {}

QString MyDoubleSpinBoxPlugin::domXml() const
{
	return QStringLiteral(
		"<ui language=\"c++\">"
		"<widget class=\"MyDoubleSpinBox\" name=\"myDoubleSpinBox\">"
		"<property name=\"decimals\">"
		"<number>6</number>"
		"</property>"
		"<property name=\"minimum\">"
		"<double>-99999.0</double>"
		"</property>"
		"<property name=\"maximum\">"
		"<double>99999.0</double>"
		"</property>"
		"</widget>"
		"</ui>");
}

QWidget *MyDoubleSpinBoxPlugin::createWidget(QWidget *parent)
{
	return new MyDoubleSpinBox(parent);
}

// ============================================================
// MySpinBox
// ============================================================
MySpinBoxPlugin::MySpinBoxPlugin() : MandelbulberWidgetPlugin() {}

QString MySpinBoxPlugin::domXml() const
{
	return QStringLiteral(
		"<ui language=\"c++\">"
		"<widget class=\"MySpinBox\" name=\"mySpinBox\">"
		"<property name=\"minimum\">"
		"<number>0</number>"
		"</property>"
		"<property name=\"maximum\">"
		"<number>999999</number>"
		"</property>"
		"</widget>"
		"</ui>");
}

QWidget *MySpinBoxPlugin::createWidget(QWidget *parent)
{
	return new MySpinBox(parent);
}

// ============================================================
// MyCheckBox
// ============================================================
MyCheckBoxPlugin::MyCheckBoxPlugin() : MandelbulberWidgetPlugin() {}

QString MyCheckBoxPlugin::domXml() const
{
	return QStringLiteral(
		"<ui language=\"c++\">"
		"<widget class=\"MyCheckBox\" name=\"myCheckBox\">"
		"<property name=\"text\">"
		"<string>CheckBox</string>"
		"</property>"
		"</widget>"
		"</ui>");
}

QWidget *MyCheckBoxPlugin::createWidget(QWidget *parent)
{
	return new MyCheckBox(parent);
}

// ============================================================
// MyComboBox
// ============================================================
MyComboBoxPlugin::MyComboBoxPlugin() : MandelbulberWidgetPlugin() {}

QString MyComboBoxPlugin::domXml() const
{
	return QStringLiteral(
		"<ui language=\"c++\">"
		"<widget class=\"MyComboBox\" name=\"myComboBox\">"
		"<item>"
		"<property name=\"text\">"
		"<string>Option 1</string>"
		"</property>"
		"</item>"
		"<item>"
		"<property name=\"text\">"
		"<string>Option 2</string>"
		"</property>"
		"</item>"
		"</widget>"
		"</ui>");
}

QWidget *MyComboBoxPlugin::createWidget(QWidget *parent)
{
	return new MyComboBox(parent);
}

// ============================================================
// MyGroupBox
// ============================================================
MyGroupBoxPlugin::MyGroupBoxPlugin() : MandelbulberWidgetPlugin() {}

QString MyGroupBoxPlugin::domXml() const
{
	return QStringLiteral(
		"<ui language=\"c++\">"
		"<widget class=\"MyGroupBox\" name=\"myGroupBox\">"
		"<property name=\"title\">"
		"<string>Group Box</string>"
		"</property>"
		"</widget>"
		"</ui>");
}

QWidget *MyGroupBoxPlugin::createWidget(QWidget *parent)
{
	return new MyGroupBox(parent);
}

// ============================================================
// MyLineEdit
// ============================================================
MyLineEditPlugin::MyLineEditPlugin() : MandelbulberWidgetPlugin() {}

QString MyLineEditPlugin::domXml() const
{
	return QStringLiteral(
		"<ui language=\"c++\">"
		"<widget class=\"MyLineEdit\" name=\"myLineEdit\">"
		"</widget>"
		"</ui>");
}

QWidget *MyLineEditPlugin::createWidget(QWidget *parent)
{
	return new MyLineEdit(parent);
}

// ============================================================
// MyColorButton
// ============================================================
MyColorButtonPlugin::MyColorButtonPlugin() : MandelbulberWidgetPlugin() {}

QString MyColorButtonPlugin::domXml() const
{
	return QStringLiteral(
		"<ui language=\"c++\">"
		"<widget class=\"MyColorButton\" name=\"myColorButton\">"
		"<property name=\"text\">"
		"<string>Color</string>"
		"</property>"
		"</widget>"
		"</ui>");
}

QWidget *MyColorButtonPlugin::createWidget(QWidget *parent)
{
	return new MyColorButton(parent);
}

// ============================================================
// Collection Plugin — registers ALL widgets in one .so file
// ============================================================
MandelbulberWidgetsCollectionPlugin::MandelbulberWidgetsCollectionPlugin(QObject *parent)
		: QObject(parent)
{
	widgets.append(new MyDoubleSpinBoxPlugin());
	widgets.append(new MySpinBoxPlugin());
	widgets.append(new MyCheckBoxPlugin());
	widgets.append(new MyComboBoxPlugin());
	widgets.append(new MyGroupBoxPlugin());
	widgets.append(new MyLineEditPlugin());
	widgets.append(new MyColorButtonPlugin());
}

QList<QDesignerCustomWidgetInterface *> MandelbulberWidgetsCollectionPlugin::customWidgets() const
{
	return widgets;
}

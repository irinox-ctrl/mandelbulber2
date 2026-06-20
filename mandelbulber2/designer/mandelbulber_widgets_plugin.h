/**
 * Mandelbulber Qt Designer Plugin
 * Makes all Mandelbulber custom widgets available in Qt Designer.
 *
 * Build & Install:
 *   cd mandelbulber2/designer
 *   qmake mandelbulber_widgets_plugin.pro
 *   make
 *   sudo make install
 *
 * Or copy manually:
 *   sudo cp libmandelbulber_widgets_plugin.so /usr/lib/qt5/plugins/designer/
 *
 * Then restart Qt Designer.
 * You will find "Mandelbulber Widgets" in the widget box on the left side.
 */

#ifndef MANDELBULBER_WIDGETS_PLUGIN_H
#define MANDELBULBER_WIDGETS_PLUGIN_H

#include <QDesignerCustomWidgetCollectionInterface>
#include <QDesignerCustomWidgetInterface>
#include <QtGlobal>
#include <QIcon>

// ============================================================
// Individual widget plugin descriptors
// ============================================================
class MandelbulberWidgetPlugin : public QDesignerCustomWidgetInterface
{
public:
	MandelbulberWidgetPlugin();

	bool isContainer() const override { return false; }
	bool isInitialized() const override { return initialized; }
	QIcon icon() const override;
	QString whatsThis() const override { return QString(); }
	QString toolTip() const override { return QString(); }
	QString group() const override { return QStringLiteral("Mandelbulber Widgets"); }
	void initialize(QDesignerFormEditorInterface *core) override;

protected:
	bool initialized;
};

class MyDoubleSpinBoxPlugin : public MandelbulberWidgetPlugin
{
public:
	MyDoubleSpinBoxPlugin();
	QString name() const override { return QStringLiteral("MyDoubleSpinBox"); }
	QString includeFile() const override { return QStringLiteral("my_double_spin_box.h"); }
	QString domXml() const override;
	QWidget *createWidget(QWidget *parent) override;
};

class MySpinBoxPlugin : public MandelbulberWidgetPlugin
{
public:
	MySpinBoxPlugin();
	QString name() const override { return QStringLiteral("MySpinBox"); }
	QString includeFile() const override { return QStringLiteral("my_spin_box.h"); }
	QString domXml() const override;
	QWidget *createWidget(QWidget *parent) override;
};

class MyCheckBoxPlugin : public MandelbulberWidgetPlugin
{
public:
	MyCheckBoxPlugin();
	QString name() const override { return QStringLiteral("MyCheckBox"); }
	QString includeFile() const override { return QStringLiteral("my_check_box.h"); }
	QString domXml() const override;
	QWidget *createWidget(QWidget *parent) override;
};

class MyComboBoxPlugin : public MandelbulberWidgetPlugin
{
public:
	MyComboBoxPlugin();
	QString name() const override { return QStringLiteral("MyComboBox"); }
	QString includeFile() const override { return QStringLiteral("my_combo_box.h"); }
	QString domXml() const override;
	QWidget *createWidget(QWidget *parent) override;
};

class MyGroupBoxPlugin : public MandelbulberWidgetPlugin
{
public:
	MyGroupBoxPlugin();
	QString name() const override { return QStringLiteral("MyGroupBox"); }
	QString includeFile() const override { return QStringLiteral("my_group_box.h"); }
	QString domXml() const override;
	QWidget *createWidget(QWidget *parent) override;
	bool isContainer() const override { return true; }
};

class MyLineEditPlugin : public MandelbulberWidgetPlugin
{
public:
	MyLineEditPlugin();
	QString name() const override { return QStringLiteral("MyLineEdit"); }
	QString includeFile() const override { return QStringLiteral("my_line_edit.h"); }
	QString domXml() const override;
	QWidget *createWidget(QWidget *parent) override;
};

class MyColorButtonPlugin : public MandelbulberWidgetPlugin
{
public:
	MyColorButtonPlugin();
	QString name() const override { return QStringLiteral("MyColorButton"); }
	QString includeFile() const override { return QStringLiteral("my_color_button.h"); }
	QString domXml() const override;
	QWidget *createWidget(QWidget *parent) override;
};

// ============================================================
// Collection plugin — bundles all widgets into ONE .so file
// ============================================================
class MandelbulberWidgetsCollectionPlugin
		: public QObject
		, public QDesignerCustomWidgetCollectionInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
	Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
	MandelbulberWidgetsCollectionPlugin(QObject *parent = nullptr);

	QList<QDesignerCustomWidgetInterface *> customWidgets() const override;

private:
	QList<QDesignerCustomWidgetInterface *> widgets;
};

#endif // MANDELBULBER_WIDGETS_PLUGIN_H

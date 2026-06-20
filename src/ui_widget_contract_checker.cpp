/**
 * Mandelbulber v2 — widget ↔ parameter binding contract checker
 */

#include "ui_widget_contract_checker.hpp"

#include <QComboBox>
#include <QHash>
#include <QObject>
#include <QSet>
#include <QWidget>

#include "multi_val.hpp"
#include "parameters.hpp"
#include "synchronize_interface.hpp"
#include "write_log.hpp"

namespace
{
static sWidgetContractReport gLastWidgetContractReport;

bool IsBindableWidgetClass(const QString &className)
{
	static const QSet<QString> bindable = {
		"MyDoubleSpinBox", "QDoubleSpinBox", "MySpinBox", "QSpinBox", "MyLineEdit", "QLineEdit",
		"MyCheckBox", "QCheckBox", "MyGroupBox", "QGroupBox", "FileSelectWidget", "MyColorButton",
		"cGradientEditWidget", "QComboBox", "MyComboBox", "cFormulaComboBox", "cMaterialSelector",
		"QPlainTextEdit", "QTextEdit", "cMyTextEdit", "QKeySequenceEdit", "cLightWidget"};
	return bindable.contains(className);
}

QStringList AllowedClassNamesForWidget(const QString &className)
{
	if (className == "MyDoubleSpinBox" || className == "QDoubleSpinBox")
		return {"MyDoubleSpinBox", "QDoubleSpinBox"};
	if (className == "MySpinBox" || className == "QSpinBox")
		return {"QSpinBox", "MySpinBox"};
	if (className == "MyLineEdit" || className == "QLineEdit")
		return {"MyLineEdit", "QLineEdit"};
	if (className == "MyCheckBox" || className == "QCheckBox")
		return {"QCheckBox", "MyCheckBox"};
	if (className == "MyGroupBox" || className == "QGroupBox")
		return {"QGroupBox", "MyGroupBox"};
	if (className == "QComboBox" || className == "MyComboBox" || className == "cFormulaComboBox")
		return {"QComboBox", "MyComboBox", "cFormulaComboBox"};
	if (className == "QTextEdit" || className == "cMyTextEdit")
		return {"QTextEdit", "cMyTextEdit"};
	if (className == "FileSelectWidget") return {"FileSelectWidget"};
	if (className == "MyColorButton") return {"MyColorButton"};
	if (className == "cGradientEditWidget") return {"cGradientEditWidget"};
	if (className == "cMaterialSelector") return {"cMaterialSelector"};
	if (className == "QPlainTextEdit") return {"QPlainTextEdit"};
	if (className == "QKeySequenceEdit") return {"QKeySequenceEdit"};
	if (className == "cLightWidget") return {"cLightWidget"};
	return {};
}

bool UsesAnyTypePrefix(const QString &className)
{
	return className == "FileSelectWidget" || className == "MyColorButton";
}

bool SkipsParameterLookup(const QString &className)
{
	return className == "cLightWidget";
}

bool IsRecognizedTypePrefix(const QString &className, const QString &typeName)
{
	if (UsesAnyTypePrefix(className)) return true;

	static const QHash<QString, QSet<QString>> prefixes = {
		{"MyDoubleSpinBox", {"spinbox", "spinboxd", "spinbox3", "spinboxd3", "spinbox4", "spinboxd4"}},
		{"QDoubleSpinBox", {"spinbox", "spinboxd", "spinbox3", "spinboxd3", "spinbox4", "spinboxd4"}},
		{"MySpinBox", {"spinboxInt"}},
		{"QSpinBox", {"spinboxInt"}},
		{"MyLineEdit", {"vect3", "logvect3", "vect4", "edit", "logedit", "text"}},
		{"QLineEdit", {"vect3", "logvect3", "vect4", "edit", "logedit", "text"}},
		{"MyCheckBox", {"checkBox"}},
		{"QCheckBox", {"checkBox"}},
		{"MyGroupBox", {"groupCheck"}},
		{"QGroupBox", {"groupCheck"}},
		{"QComboBox", {"comboBox"}},
		{"MyComboBox", {"comboBox"}},
		{"cFormulaComboBox", {"comboBox"}},
		{"cGradientEditWidget", {"colorpalette"}},
		{"cMaterialSelector", {"materialselector"}},
		{"QPlainTextEdit", {"text"}},
		{"QTextEdit", {"textEdit"}},
		{"cMyTextEdit", {"textEdit"}},
		{"QKeySequenceEdit", {"keySequenceEdit"}},
	};
	return prefixes.value(className).contains(typeName);
}

QString ResolveParameterKey(const qInterface::widgetProperties &props)
{
	if (props.typeName == "spinbox3" || props.typeName == "spinboxd3"
		|| props.typeName == "vect3" || props.typeName == "logvect3")
		return props.paramName.left(props.paramName.length() - 2);
	if (props.typeName == "spinbox4" || props.typeName == "spinboxd4" || props.typeName == "vect4")
		return props.paramName.left(props.paramName.length() - 2);
	return props.paramName;
}

void AppendIssue(sWidgetContractReport &report, const sWidgetContractIssue &issue)
{
	for (const sWidgetContractIssue &existing : report.issues)
	{
		if (existing.widgetName == issue.widgetName && existing.kind == issue.kind)
			return;
	}
	report.issues.append(issue);
}
} // namespace

const sWidgetContractReport &GetLastWidgetContractReport()
{
	return gLastWidgetContractReport;
}

QString FormatWidgetContractSummary(const sWidgetContractReport &report, const int maxItems)
{
	if (report.issues.isEmpty())
		return QObject::tr("Widget bindings OK");

	QStringList lines;
	const int count = qMin(maxItems, report.issues.size());
	for (int i = 0; i < count; ++i)
	{
		const sWidgetContractIssue &issue = report.issues.at(i);
		lines.append(QString("%1: %2").arg(issue.widgetName, issue.message));
	}
	if (report.issues.size() > maxItems)
		lines.append(QObject::tr("... and %1 more binding issue(s)").arg(report.issues.size() - maxItems));
	return lines.join(" | ");
}

sWidgetContractReport CheckWidgetParameterContracts(QWidget *root,
	std::shared_ptr<cParameterContainer> par)
{
	sWidgetContractReport report;
	if (!root || !par) return report;

	const QList<QWidget *> widgets = root->findChildren<QWidget *>();
	for (QWidget *widget : widgets)
	{
		if (!widget) continue;
		const QString className = QString(widget->metaObject()->className());
		if (!IsBindableWidgetClass(className)) continue;

		const QString objectName = widget->objectName();
		if (objectName.isEmpty()) continue;

		report.widgetsScanned++;

		const QStringList allowedClasses = AllowedClassNamesForWidget(className);
		if (allowedClasses.isEmpty()) continue;

		qInterface::widgetProperties props = parseWidgetProperties(widget, allowedClasses);

		if (!props.allowed)
		{
			sWidgetContractIssue issue;
			issue.kind = sWidgetContractIssue::Kind::UnknownPrefix;
			issue.widgetName = objectName;
			issue.className = className;
			issue.parameterKey = props.paramName;
			issue.message = QObject::tr("widget name has no recognized type prefix");
			AppendIssue(report, issue);
			continue;
		}

		if (!IsRecognizedTypePrefix(className, props.typeName))
		{
			sWidgetContractIssue issue;
			issue.kind = sWidgetContractIssue::Kind::UnknownPrefix;
			issue.widgetName = objectName;
			issue.className = className;
			issue.parameterKey = props.paramName;
			issue.message =
				QObject::tr("prefix '%1' is not handled by SynchronizeInterface").arg(props.typeName);
			AppendIssue(report, issue);
			continue;
		}

		if (SkipsParameterLookup(className)) continue;

		const QString paramKey = ResolveParameterKey(props);
		report.widgetsBound++;

		if (!par->IfExists(paramKey))
		{
			sWidgetContractIssue issue;
			issue.kind = sWidgetContractIssue::Kind::MissingParameter;
			issue.widgetName = objectName;
			issue.className = className;
			issue.parameterKey = paramKey;
			issue.message = QObject::tr("parameter '%1' is not registered").arg(paramKey);
			AppendIssue(report, issue);
			continue;
		}

		if (props.typeName == "comboBox" && par->GetVarType(paramKey) == typeInt
			&& !paramKey.startsWith("formula"))
		{
			QComboBox *combo = qobject_cast<QComboBox *>(widget);
			if (!combo || combo->count() == 0) continue;

			const cOneParameter onePar = par->GetAsOneParameter(paramKey);
			const int paramMax = onePar.Get<int>(valueMax);
			const int comboMax = combo->count() - 1;
			if (paramMax < comboMax)
			{
				sWidgetContractIssue issue;
				issue.kind = sWidgetContractIssue::Kind::ComboRangeMismatch;
				issue.widgetName = objectName;
				issue.className = className;
				issue.parameterKey = paramKey;
				issue.message = QObject::tr("param max=%1 but combo has %2 items (needs max=%3)")
									.arg(paramMax)
									.arg(combo->count())
									.arg(comboMax);
				AppendIssue(report, issue);
			}
		}
	}

	gLastWidgetContractReport = report;
	return report;
}

void EnsureWidgetParameterContractsChecked(QWidget *root,
	std::shared_ptr<cParameterContainer> par)
{
	static bool checked = false;
	if (checked) return;
	checked = true;

	const sWidgetContractReport report = CheckWidgetParameterContracts(root, par);
	WriteLog(QString("Widget contract check: scanned=%1 bound=%2 issues=%3")
			.arg(report.widgetsScanned)
			.arg(report.widgetsBound)
			.arg(report.issues.size()),
		2);

	const int logLimit = 40;
	for (int i = 0; i < report.issues.size() && i < logLimit; ++i)
	{
		const sWidgetContractIssue &issue = report.issues.at(i);
		WriteLog(QString("WidgetContract [%1] %2 (%3): %4")
				.arg(issue.widgetName, issue.className, issue.parameterKey, issue.message),
			3);
	}
	if (report.issues.size() > logLimit)
	{
		WriteLog(QString("WidgetContract: ... and %1 more issue(s)")
				.arg(report.issues.size() - logLimit),
			3);
	}
}

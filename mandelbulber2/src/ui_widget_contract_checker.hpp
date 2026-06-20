/**
 * Mandelbulber v2 — widget ↔ parameter binding contract checker
 */

#ifndef MANDELBULBER2_SRC_UI_WIDGET_CONTRACT_CHECKER_HPP_
#define MANDELBULBER2_SRC_UI_WIDGET_CONTRACT_CHECKER_HPP_

#include <memory>
#include <QString>
#include <QVector>

class QWidget;
class cParameterContainer;

struct sWidgetContractIssue
{
	enum class Kind
	{
		UnknownPrefix,
		MissingParameter,
		ComboRangeMismatch
	};

	Kind kind = Kind::UnknownPrefix;
	QString widgetName;
	QString className;
	QString parameterKey;
	QString message;
};

struct sWidgetContractReport
{
	QVector<sWidgetContractIssue> issues;
	int widgetsScanned = 0;
	int widgetsBound = 0;
};

sWidgetContractReport CheckWidgetParameterContracts(QWidget *root,
	std::shared_ptr<cParameterContainer> par);

const sWidgetContractReport &GetLastWidgetContractReport();

QString FormatWidgetContractSummary(const sWidgetContractReport &report, int maxItems = 3);

void EnsureWidgetParameterContractsChecked(QWidget *root,
	std::shared_ptr<cParameterContainer> par);

#endif /* MANDELBULBER2_SRC_UI_WIDGET_CONTRACT_CHECKER_HPP_ */

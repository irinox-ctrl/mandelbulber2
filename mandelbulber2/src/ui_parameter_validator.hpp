/**
 * Mandelbulber v2 — pre-render UI parameter validation and repair
 */

#ifndef MANDELBULBER2_SRC_UI_PARAMETER_VALIDATOR_HPP_
#define MANDELBULBER2_SRC_UI_PARAMETER_VALIDATOR_HPP_

#include <memory>
#include <QString>
#include <QVector>

class cParameterContainer;
class cFractalContainer;

struct sValidationIssue
{
	enum Severity
	{
		Info,
		Warning,
		Error
	};

	Severity severity = Warning;
	QString parameter;
	QString message;
	QString autoFix;
};

struct sUiParameterRepairResult
{
	QVector<sValidationIssue> issues;
	int fixesApplied = 0;
};

sUiParameterRepairResult RepairUiParameters(std::shared_ptr<cParameterContainer> par,
	std::shared_ptr<cFractalContainer> /*fractPar*/);

void SyncFormulaMaxiterToN(std::shared_ptr<cParameterContainer> par,
	sUiParameterRepairResult *result = nullptr);

const sUiParameterRepairResult &GetLastUiParameterRepairResult();
QString FormatValidationIssuesSummary(const sUiParameterRepairResult &result, int maxItems = 3);

#endif /* MANDELBULBER2_SRC_UI_PARAMETER_VALIDATOR_HPP_ */

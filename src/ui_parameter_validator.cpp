/**
 * Mandelbulber v2 — pre-render UI parameter validation and repair
 */

#include "ui_parameter_validator.hpp"

#include <cmath>

#include "algebra.hpp"
#include "fractal_enums.h"
#include "initparameters.hpp"
#include "parameters.hpp"
#include "write_log.hpp"

#include <QObject>

namespace
{
bool IsFiniteDouble(const double value)
{
	return !std::isnan(value) && !std::isinf(value);
}

void SwapIterRangeIfNeeded(std::shared_ptr<cParameterContainer> par, const QString &startKey,
	const QString &stopKey, const int index, sUiParameterRepairResult &result)
{
	if (!par->IfExists(startKey) || !par->IfExists(stopKey)) return;

	const int start = par->Get<int>(startKey, index);
	const int stop = par->Get<int>(stopKey, index);
	if (start <= stop) return;

	par->Set(startKey, stop, index);
	par->Set(stopKey, start, index);

	sValidationIssue issue;
	issue.severity = sValidationIssue::Warning;
	issue.parameter = startKey;
	issue.message = QString("iter_start (%1) > iter_stop (%2)").arg(start).arg(stop);
	issue.autoFix = QString("swapped to %1..%2").arg(stop).arg(start);
	result.issues.append(issue);
	result.fixesApplied++;
}

void RepairFiniteDouble(std::shared_ptr<cParameterContainer> par, const QString &key,
	const double fallback, const int index, sUiParameterRepairResult &result)
{
	if (!par->IfExists(key)) return;

	const double value = par->Get<double>(key, index);
	if (IsFiniteDouble(value)) return;

	par->Set(key, fallback, index);

	sValidationIssue issue;
	issue.severity = sValidationIssue::Error;
	issue.parameter = key;
	issue.message = QString("non-finite value repaired to %1").arg(fallback);
	issue.autoFix = QString::number(fallback);
	result.issues.append(issue);
	result.fixesApplied++;
}

const char *kMutationIterPrefixes[] = {
	"mutation_pre_iter",
	"mutation_fold_iter",
	"mutation_warp_iter",
	"mutation_math_iter",
	"mutation_post_iter",
	"mutation_julia_iter",
	"mutation_de_iter",
	"mutation_julia_ctransform_iter",
	"mutation_julia_dynamic_iter",
	"mutation_julia_multi_iter",
	"mutation_inv_iter",
	"mutation_clip_iter",
	"mutation_jos_iter",
	"mutation_pk_iter",
	"mutation_mb_iter",
	"mutation_wd_iter",
	"mutation_sk_iter",
	"mutation_ab_iter",
	"mutation_noise_iter",
	"mutation_orbit_iter",
	"mutation_torus_iter",
	"mutation_as_iter",
	"mutation_sm_iter",
	"mutation_clamp_iter",
	"mutation_jb_iter",
	"mutation_md_iter",
	"mutation_blockify_iter",
	"mutation_tile_iter",
	nullptr};

const char *kMutationJuliaDoubleParams[] = {
	"mutation_julia_c_mul",
	"mutation_julia_pulse_freq",
	"mutation_julia_pulse_amp",
	"mutation_julia_absorb",
	"mutation_julia_c_radius",
	"mutation_julia_c_power",
	"mutation_julia_noise_freq",
	"mutation_julia_noise_amp",
	nullptr};
} // namespace

static sUiParameterRepairResult gLastUiParameterRepairResult;

const sUiParameterRepairResult &GetLastUiParameterRepairResult()
{
	return gLastUiParameterRepairResult;
}

QString FormatValidationIssuesSummary(const sUiParameterRepairResult &result, const int maxItems)
{
	if (result.issues.isEmpty())
		return QObject::tr("Parameters OK");

	QStringList lines;
	const int count = qMin(maxItems, result.issues.size());
	for (int i = 0; i < count; ++i)
	{
		const sValidationIssue &issue = result.issues.at(i);
		lines.append(QString("%1: %2").arg(issue.parameter, issue.message));
	}
	if (result.issues.size() > maxItems)
	{
		lines.append(QObject::tr("... and %1 more").arg(result.issues.size() - maxItems));
	}
	return lines.join(" | ");
}

void SyncFormulaMaxiterToN(std::shared_ptr<cParameterContainer> par,
	sUiParameterRepairResult *result)
{
	if (!par || !par->IfExists("N")) return;

	const int n = std::max(par->Get<int>("N"), 1);

	for (int slot = 1; slot <= NUMBER_OF_FRACTALS; ++slot)
	{
		const int current = par->Get<int>("formula_maxiter", slot);
		if (current <= n) continue;

		par->Set("formula_maxiter", slot, n);

		if (!result) continue;

		sValidationIssue issue;
		issue.severity = sValidationIssue::Info;
		issue.parameter = QString("formula_maxiter_%1").arg(slot);
		issue.message = QString("capped to global N=%1 (was %2)").arg(n).arg(current);
		issue.autoFix = QString::number(n);
		result->issues.append(issue);
		result->fixesApplied++;
	}
}

sUiParameterRepairResult RepairUiParameters(std::shared_ptr<cParameterContainer> par,
	std::shared_ptr<cFractalContainer> /*fractPar*/)
{
	sUiParameterRepairResult result;
	if (!par) return result;

	EnsureDefaultFractalGradientMaterial(par);

	if (par->IfExists("julia_c"))
	{
		CVector3 juliaC = par->Get<CVector3>("julia_c");
		bool repaired = false;
		if (!IsFiniteDouble(juliaC.x))
		{
			juliaC.x = 0.0;
			repaired = true;
		}
		if (!IsFiniteDouble(juliaC.y))
		{
			juliaC.y = 0.0;
			repaired = true;
		}
		if (!IsFiniteDouble(juliaC.z))
		{
			juliaC.z = 0.0;
			repaired = true;
		}
		if (repaired)
		{
			par->Set("julia_c", juliaC);
			sValidationIssue issue;
			issue.severity = sValidationIssue::Error;
			issue.parameter = "julia_c";
			issue.message = "NaN/Inf Julia constant repaired to (0,0,0)";
			issue.autoFix = "0,0,0";
			result.issues.append(issue);
			result.fixesApplied++;
		}
	}

	if (par->IfExists("N"))
	{
		const int n = par->Get<int>("N");
		if (n < 1)
		{
			par->Set("N", 100);
			sValidationIssue issue;
			issue.severity = sValidationIssue::Warning;
			issue.parameter = "N";
			issue.message = "invalid iteration count repaired";
			issue.autoFix = "100";
			result.issues.append(issue);
			result.fixesApplied++;
		}
		else
			SyncFormulaMaxiterToN(par, &result);
	}

	if (par->IfExists("bailout"))
		RepairFiniteDouble(par, "bailout", 4.0, -1, result);

	for (int slot = 1; slot <= NUMBER_OF_FRACTALS; ++slot)
	{
		for (const char **prefix = kMutationIterPrefixes; *prefix != nullptr; ++prefix)
		{
			const QString startKey = QString("%1_start").arg(*prefix);
			const QString stopKey = QString("%1_stop").arg(*prefix);
			SwapIterRangeIfNeeded(par, startKey, stopKey, slot, result);
		}

		for (const char **param = kMutationJuliaDoubleParams; *param != nullptr; ++param)
		{
			const QString key(*param);
			double fallback = 1.0;
			if (key.contains("pulse") || key.contains("noise") || key.contains("absorb"))
				fallback = 0.0;
			RepairFiniteDouble(par, key, fallback, slot, result);
		}
	}

	for (const auto &issue : result.issues)
	{
		WriteLog(QString("RepairUiParameters [%1]: %2 (%3)")
				.arg(issue.parameter, issue.message, issue.autoFix),
			3);
	}

	gLastUiParameterRepairResult = result;
	return result;
}

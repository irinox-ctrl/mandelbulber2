/**
 * Mandelbulber v2 — data-driven mutation UI parameter visibility registry
 */

#include "mutation_ui_registry.hpp"

#include <QComboBox>
#include <QGroupBox>

QVector<sMutationParamRule> cMutationUiRegistry::loadedRules;
QVector<sMutationSystemBinding> cMutationUiRegistry::loadedBindings;
QVector<sMutationJuliaUiRule> cMutationUiRegistry::loadedJuliaRules;
QHash<QString, QSet<int>> cMutationUiRegistry::ruleTypeCache;

void cMutationUiRegistry::EnsureLoaded()
{
	if (!loadedRules.isEmpty()) return;

	const int ruleCount = ParamRulesCount();
	loadedRules.reserve(ruleCount + ExtendedParamRulesCount());
	for (int i = 0; i < ruleCount; ++i)
		loadedRules.append(ParamRulesData()[i]);
	for (int i = 0; i < ExtendedParamRulesCount(); ++i)
		loadedRules.append(ExtendedParamRulesData()[i]);

	const int bindingCount = SystemBindingsCount();
	loadedBindings.reserve(bindingCount + ExtendedSystemBindingsCount());
	for (int i = 0; i < bindingCount; ++i)
		loadedBindings.append(SystemBindingsData()[i]);
	for (int i = 0; i < ExtendedSystemBindingsCount(); ++i)
		loadedBindings.append(ExtendedSystemBindingsData()[i]);

	const int juliaCount = JuliaRulesCount();
	loadedJuliaRules.reserve(juliaCount);
	for (int i = 0; i < juliaCount; ++i)
		loadedJuliaRules.append(JuliaRulesData()[i]);
}

const QVector<sMutationParamRule> &cMutationUiRegistry::ParamRules()
{
	EnsureLoaded();
	return loadedRules;
}

const QVector<sMutationSystemBinding> &cMutationUiRegistry::SystemBindings()
{
	EnsureLoaded();
	return loadedBindings;
}

const QVector<sMutationJuliaUiRule> &cMutationUiRegistry::JuliaRules()
{
	EnsureLoaded();
	return loadedJuliaRules;
}

QSet<int> cMutationUiRegistry::ActiveTypesForRule(const sMutationParamRule &rule)
{
	const QString key = QString("%1|%2|%3")
		.arg(rule.systemId, rule.spinWidgetBase ? rule.spinWidgetBase : "",
			rule.labelWidgetBase ? rule.labelWidgetBase : "");
	if (ruleTypeCache.contains(key)) return ruleTypeCache.value(key);

	QSet<int> types;
	for (int i = 0; i < rule.typeCount; ++i)
		types.insert(rule.typeIds[i]);
	ruleTypeCache.insert(key, types);
	return types;
}

bool cMutationUiRegistry::IsParamActiveForType(const sMutationParamRule &rule, const int typeId)
{
	if (rule.alwaysActive) return true;
	if (rule.typeCount > 0) return ActiveTypesForRule(rule).contains(typeId);
	if (rule.maxTypeInclusive >= rule.minTypeInclusive)
		return typeId >= rule.minTypeInclusive && typeId <= rule.maxTypeInclusive;
	return false;
}

bool cMutationUiRegistry::EvaluateJuliaRule(
	const sMutationJuliaUiContext &ctx, const sMutationJuliaUiRule &rule)
{
	if (rule.alwaysActive) return true;
	if (rule.requiresInjectionNonZero && ctx.injection == 0) return false;
	if (rule.injectionEquals >= 0 && ctx.injection != rule.injectionEquals) return false;
	if (rule.requiresCTransformNonZero && ctx.cTransform == 0) return false;
	if (rule.cTransformEquals >= 0 && ctx.cTransform != rule.cTransformEquals) return false;
	if (rule.requiresDynamicNonZero && ctx.dynamic == 0) return false;
	if (rule.dynamicEquals >= 0 && ctx.dynamic != rule.dynamicEquals) return false;
	if (rule.requiresMultiNonZero && ctx.multi == 0) return false;
	if (rule.multiEquals >= 0 && ctx.multi != rule.multiEquals) return false;
	if (rule.startEquals >= 0 && ctx.start != rule.startEquals) return false;
	return true;
}

static QString MutationJuliaWidgetName(const QString &baseName, const QString &suffix)
{
	const QString lastTwo = baseName.right(2);
	if (lastTwo == "_x" || lastTwo == "_y" || lastTwo == "_z")
		return baseName.left(baseName.size() - 2) + suffix + lastTwo;
	return baseName + suffix;
}

void cMutationUiRegistry::ApplyPerTypeParamGrayOut(const int tabIndex,
	const QHash<QString, QPair<QGroupBox *, QComboBox *>> &systems,
	const std::function<void(QWidget *, bool)> &styleWidget)
{
	const QString suffix = "_" + QString::number(tabIndex + 1);

	for (const sMutationParamRule &rule : ParamRules())
	{
		const auto it = systems.constFind(QString(rule.systemId));
		if (it == systems.cend()) continue;

		QGroupBox *group = it.value().first;
		QComboBox *combo = it.value().second;
		if (!group || !combo) continue;

		const int typeId = combo->currentIndex();
		const bool systemActive = group->isChecked() && typeId != 0;
		const bool paramActive = systemActive && IsParamActiveForType(rule, typeId);

		if (rule.spinWidgetBase && rule.spinWidgetBase[0] != '\0')
		{
			styleWidget(group->findChild<QWidget *>(QString(rule.spinWidgetBase) + suffix),
				paramActive);
		}
		if (rule.labelWidgetBase && rule.labelWidgetBase[0] != '\0')
		{
			styleWidget(group->findChild<QWidget *>(QString(rule.labelWidgetBase) + suffix),
				paramActive);
		}
	}
}

void cMutationUiRegistry::ApplyInlinePerTypeParamGrayOut(const int tabIndex,
	const char *systemId,
	QWidget *searchRoot,
	QComboBox *typeCombo,
	const std::function<void(QWidget *, bool)> &styleWidget)
{
	if (!systemId || !searchRoot || !typeCombo) return;

	const QString suffix = "_" + QString::number(tabIndex + 1);
	const int typeId = typeCombo->currentIndex();

	for (const sMutationParamRule &rule : ParamRules())
	{
		if (!rule.systemId || QString(rule.systemId) != QString(systemId)) continue;

		const bool widgetActive =
			rule.alwaysActive || IsParamActiveForType(rule, typeId);

		if (rule.spinWidgetBase && rule.spinWidgetBase[0] != '\0')
		{
			styleWidget(searchRoot->findChild<QWidget *>(QString(rule.spinWidgetBase) + suffix),
				widgetActive);
		}
		if (rule.labelWidgetBase && rule.labelWidgetBase[0] != '\0')
		{
			styleWidget(searchRoot->findChild<QWidget *>(QString(rule.labelWidgetBase) + suffix),
				widgetActive);
		}
	}
}

void cMutationUiRegistry::ApplyJuliaGrayOut(const int tabIndex, QWidget *searchRoot,
	const sMutationJuliaUiContext &ctx,
	const std::function<void(QWidget *, bool)> &styleWidget)
{
	if (!searchRoot) return;

	const QString suffix = "_" + QString::number(tabIndex + 1);
	QHash<QString, bool> widgetEnabled;

	for (const sMutationJuliaUiRule &rule : JuliaRules())
	{
		if (!rule.widgetBase) continue;
		const QString widgetBase = QString(rule.widgetBase);
		if (EvaluateJuliaRule(ctx, rule))
			widgetEnabled.insert(widgetBase, true);
		else if (!widgetEnabled.contains(widgetBase))
			widgetEnabled.insert(widgetBase, false);
	}

	const QList<QWidget *> children = searchRoot->findChildren<QWidget *>();
	for (auto it = widgetEnabled.constBegin(); it != widgetEnabled.constEnd(); ++it)
	{
		const QString fullName = MutationJuliaWidgetName(it.key(), suffix);
		for (QWidget *w : children)
		{
			if (w->objectName() == fullName)
			{
				styleWidget(w, it.value());
				break;
			}
		}
	}
}

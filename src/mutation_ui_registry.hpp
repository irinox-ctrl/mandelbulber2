/**
 * Mandelbulber v2 — data-driven mutation UI parameter visibility registry
 */

#ifndef MANDELBULBER2_SRC_MUTATION_UI_REGISTRY_HPP_
#define MANDELBULBER2_SRC_MUTATION_UI_REGISTRY_HPP_

#include <QHash>
#include <QSet>
#include <QString>
#include <QVector>
#include <cstdint>
#include <functional>

class QComboBox;
class QGroupBox;
class QWidget;

struct sMutationParamRule
{
	const char *systemId = nullptr;
	const char *spinWidgetBase = nullptr;
	const char *labelWidgetBase = nullptr;
	const int *typeIds = nullptr;
	int typeCount = 0;
	int minTypeInclusive = 0;
	int maxTypeInclusive = 0;
	bool alwaysActive = false;
};

struct sMutationSystemBinding
{
	const char *systemId = nullptr;
	const char *groupWidgetBase = nullptr;
	const char *comboWidgetBase = nullptr;
};

struct sMutationJuliaUiContext
{
	int injection = 0;
	int cTransform = 0;
	int dynamic = 0;
	int multi = 0;
	int start = 0;
};

struct sMutationJuliaUiRule
{
	const char *widgetBase = nullptr;
	bool alwaysActive = false;
	bool requiresInjectionNonZero = false;
	int8_t injectionEquals = -1;
	bool requiresCTransformNonZero = false;
	int8_t cTransformEquals = -1;
	bool requiresDynamicNonZero = false;
	int8_t dynamicEquals = -1;
	bool requiresMultiNonZero = false;
	int8_t multiEquals = -1;
	int8_t startEquals = -1;
};

class cMutationUiRegistry
{
public:
	static const QVector<sMutationParamRule> &ParamRules();
	static const QVector<sMutationSystemBinding> &SystemBindings();
	static const QVector<sMutationJuliaUiRule> &JuliaRules();

	static QSet<int> ActiveTypesForRule(const sMutationParamRule &rule);
	static bool IsParamActiveForType(const sMutationParamRule &rule, int typeId);
	static bool EvaluateJuliaRule(const sMutationJuliaUiContext &ctx, const sMutationJuliaUiRule &rule);

	static void ApplyPerTypeParamGrayOut(int tabIndex,
		const QHash<QString, QPair<QGroupBox *, QComboBox *>> &systems,
		const std::function<void(QWidget *, bool)> &styleWidget);

	static void ApplyInlinePerTypeParamGrayOut(int tabIndex,
		const char *systemId,
		QWidget *searchRoot,
		QComboBox *typeCombo,
		const std::function<void(QWidget *, bool)> &styleWidget);

	static void ApplyJuliaGrayOut(int tabIndex, QWidget *searchRoot,
		const sMutationJuliaUiContext &ctx,
		const std::function<void(QWidget *, bool)> &styleWidget);

	static const sMutationParamRule *ParamRulesData();
	static int ParamRulesCount();
	static const sMutationParamRule *ExtendedParamRulesData();
	static int ExtendedParamRulesCount();
	static const sMutationSystemBinding *SystemBindingsData();
	static int SystemBindingsCount();
	static const sMutationSystemBinding *ExtendedSystemBindingsData();
	static int ExtendedSystemBindingsCount();
	static const sMutationJuliaUiRule *JuliaRulesData();
	static int JuliaRulesCount();

private:
	static void EnsureLoaded();
	static QVector<sMutationParamRule> loadedRules;
	static QVector<sMutationSystemBinding> loadedBindings;
	static QVector<sMutationJuliaUiRule> loadedJuliaRules;
	static QHash<QString, QSet<int>> ruleTypeCache;
};

#endif /* MANDELBULBER2_SRC_MUTATION_UI_REGISTRY_HPP_ */

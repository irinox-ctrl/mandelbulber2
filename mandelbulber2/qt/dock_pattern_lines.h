/**
 * Mandelbulber v2 — dock UI for pattern line traps (dedicated panel).
 */

#ifndef MANDELBULBER2_QT_DOCK_PATTERN_LINES_H_
#define MANDELBULBER2_QT_DOCK_PATTERN_LINES_H_

#include <QWidget>

#include <QTimer>

#include "src/algebra.hpp"
#include "my_widget_with_params.h"

#include "src/parameters.hpp"

class cAutomatedWidgets;

namespace Ui
{
class cDockPatternLines;
}

class cDockPatternLines : public QWidget, public cMyWidgetWithParams
{
	Q_OBJECT

public:
	explicit cDockPatternLines(QWidget *parent = nullptr);
	~cDockPatternLines() override;

	void AssignParameterContainers(std::shared_ptr<cParameterContainer> _params,
		std::shared_ptr<cFractalContainer> _fractalParams) override;
	void AssignSpecialWidgets(RenderedImage *_renderedImage, QComboBox *_mouseFunctionCombo) override;
	/** Zet `m_lastAuxWorldOffset` = huidige `aux_light_manual_placement_offset` in params (bij o.a. file load). */
	void syncAuxLightPlacementOffsetBaseline();

public slots:
	void slotSynchronizeInterfacePatternLineTraps(std::shared_ptr<cParameterContainer> par);

private slots:
	void slotPressedButtonNavi();
	void slotNewParametersFromNavi();
	void slotPressedButtonPlacePatternLineTrapAtTarget();
	void slotPressedButtonPlacePatternLineTrapAtSurface();
	void slotPressedButtonPatternLineTrapsQuickTest();
	void slotPatternLineTrapPresetRefresh();
	void slotPatternLineTrapPresetLoad();
	void slotPatternLineTrapPresetSave();
	void slotPatternLineTrapCopyLayer();
	/** Actief: exacte klik-modus. Uit: muisactie 'no action' + knop ongedrukt. */
	void slotExactPlacementToggled(bool checked);
	void slotMouseFunctionComboChanged(int index);
	void slotExactLayerNumberChanged(int layer);
	void slotPatternLinePrecisionModeChanged(int index);
	/** Direct commit (bij o.a. focus weg) — stopt de debounce. */
	void slotAuxOffsetCommitNow();
	/** Wiel, sleder, toetsen, typen: start/verlengt korte debounce. */
	void slotAuxOffsetTextChanged();
	void slotAuxOffsetDebounceFired();

private:
	void ConnectSignals();
	/**
	 * Delta offset → verplaats gedefinieerde lichten + actieve patroonlijnen.
	 * @param flushStartRender: meteen `StartRender` (Enter/focus weg). Anders alleen gPar+ docks — geen
	 *  tussentijdse render (elke herstart = OpenCL stop + zwart).
	 */
	void applyAuxLightWorldOffsetFromUi(bool flushStartRender);
	/** Zet muisactie, render, hulp-DE-offset; return false = mislukt (knop gaat weer uit). */
	bool applyExactClickPlacementForLayer(int layer);
	void deactivateExactClickPlacement();
	void setExactPlacementButtonCheckedNoSignals(bool on);
	/** Rij in hoofdvenster muisactie-combo, of -1. */
	int findPatternLineModeRowInMouseCombo(int layer) const;
	/** Fills falloff profile combos from param enum (uic+retranslate can leave them empty). */
	void FillPatternLineTrapEnumCombos();
	void RefreshPatternLinePresetCombo();
	void EnsurePatternLineTrapsMasterAndLayer(int layerIndex);
	double PatternLineTrapBumpFromView(int layerNum) const;
	bool RaymarchFirstSurface(const CVector3 &origin, const CVector3 &dirUnit, CVector3 *hitPoint) const;

	Ui::cDockPatternLines *ui;
	cAutomatedWidgets *automatedWidgets;
	QTimer *m_auxOffsetDebounceTimer = nullptr;
	/** Tijdens Synchronize(write) uitschakelen: voorkomt ruis/loops op textChanged. */
	bool m_suppressAuxOffsetTextCallbacks = false;
	CVector3 m_lastAuxWorldOffset{0.0, 0.0, 0.0};
};

#endif /* MANDELBULBER2_QT_DOCK_PATTERN_LINES_H_ */

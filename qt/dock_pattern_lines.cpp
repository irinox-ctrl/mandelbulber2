/**
 * Mandelbulber v2 — pattern line traps dock
 */

#include "dock_pattern_lines.h"

#include "ui_dock_pattern_lines.h"
#include "pattern_lines_traps_panel.h"

#define TRAPS_UI (static_cast<cPatternLinesTrapsPanel*>(ui->widget_pattern_lines_traps_panel)->trapsUi())

#include <algorithm>

#include <QtGlobal>

#include <QApplication>
#include <QComboBox>
#include <QDir>
#include <QFileDialog>
#include <QGroupBox>
#include <QMessageBox>
#include <QPushButton>
#include <QSignalBlocker>
#include <QInputDialog>
#include <QRegularExpression>
#include <QSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include <QWidget>

#include "navigator_window.h"

#include "src/animation_frames.hpp"
#include "src/write_log.hpp"
#include "src/automated_widgets.hpp"
#include "src/fractal_container.hpp"
#include "src/global_data.hpp"
#include "src/initparameters.hpp"
#include "src/interface.hpp"
#include "qt_utils.h"
#include "src/keyframes.hpp"
#include "src/lights.hpp"
#include "src/pattern_line_traps.hpp"
#include "src/fractal_container.hpp"
#include "src/render_window.hpp"
#include "src/rendered_image_widget.hpp"
#include "src/settings.hpp"
#include "src/synchronize_interface.hpp"
#include "src/system_data.hpp"
#include "src/system_directories.hpp"

namespace
{

const QStringList &patternLineTrapLayerSuffixes()
{
	static const QStringList s = {QStringLiteral("_enabled"), QStringLiteral("_position"),
		QStringLiteral("_rotation"), QStringLiteral("_radius"), QStringLiteral("_thickness"),
		QStringLiteral("_scale"), QStringLiteral("_relative_thickness"), QStringLiteral("_edge_softness"),
		QStringLiteral("_intensity"), QStringLiteral("_max_distance"), QStringLiteral("_falloff_sharpness"),
		QStringLiteral("_glow_spread"), QStringLiteral("_falloff_profile"), QStringLiteral("_edge_side"),
		QStringLiteral("_segment_half_length"), QStringLiteral("_shape"), QStringLiteral("_shape_aux"),
		QStringLiteral("_color"), QStringLiteral("_color_2"), QStringLiteral("_color_3")};
	return s;
}

QStringList patternLineTrapPresetMainParameterNames()
{
	QStringList list;
	list << QStringLiteral("main_pattern_line_traps_enabled");
	list << QStringLiteral("main_pattern_line_trap_solo_layer");
	list << QStringLiteral("main_pattern_line_traps_combine_mode");
	list << QStringLiteral("main_pattern_line_traps_coloring_mode");
	list << QStringLiteral("main_pattern_line_traps_coloring_speed");
	list << QStringLiteral("main_pattern_line_traps_palette_offset");
	list << QStringLiteral("main_pattern_line_traps_global_intensity");
	list << QStringLiteral("main_pattern_line_traps_global_max_distance");
	list << QStringLiteral("main_pattern_line_traps_global_scale");
	list << QStringLiteral("main_pattern_line_traps_global_relative_thickness");
	for (int i = 1; i <= PATTERN_LINE_TRAP_COUNT; i++)
	{
		const QString p = QStringLiteral("pattern_line_trap_%1").arg(i);
		for (const QString &s : patternLineTrapLayerSuffixes())
			list << QStringLiteral("main_") + p + s;
	}
	return list;
}

/** Korte tooltips voor alle zichtbare patroon-lijnvelden (Nederlands). */
static void SetupPatternLineLayersTooltips(QWidget *parent)
{
	const QString tipPos = QStringLiteral(
		"Wereldpositie van het lijnsegment. Lokaal: X langs de lijn; Y en Z bepalen het dwarsprofiel (snede in het vlak loodrecht op de lijn).");
	const QString tipRot = QStringLiteral(
		"Rotatie in graden: bepaalt waar de lokale Y- en Z-as staan voor het profiel (o.a. fractale vorm in YZ).");
	const QString tipRadius = QStringLiteral(
		"Schaal van het profiel in de YZ-snede (typische «dikte» van de vorm). Fractalen: vaak eerst verlagen, dan Schaal verhogen.");
	const QString tipThickness = QStringLiteral(
		"Hoe smal de zichtbare gloedband om de profielcurve is (na normalisatie). Lagere waarde = scherpere/dunnere lijn.");
	const QString tipScale = QStringLiteral(
		"Uniforme schaal van YZ vóór de SDF: >1 vergroot het profiel zonder de as te verschuiven.");
	const QString tipRelTh = QStringLiteral(
		"Vermenigvuldigt de effectieve banddikte (1 = zoals Dikte). Handig om één laag zachter te maken.");
	const QString tipEdge = QStringLiteral(
		"Zachte rand van de SDF (voor anti-alias in het profiel). 0 = harde kant.");
	const QString tipMaxDist = QStringLiteral(
		"Maximale afstand waarbij de lijn nog meedoet in de shader (clipping / performance).");
	const QString tipSharp = QStringLiteral(
		"Scherpte van de gloed / falloff (hoger = smalle band). Werkt samen met Gloed-spreiding en Dikte.");
	const QString tipSeg = QStringLiteral(
		"Halve lengte langs lokale X; 0 = oneindige lijn. >0 beperkt het zichtbare segment.");
	const QString tipGlow = QStringLiteral(
		"Spreiding van de gloed: hoger = bredere zachte rand (ten koste van scherpte tenzij je Scherpte verhoogt).");
	const QString tipShape = QStringLiteral(
		"Profiel in het YZ-vlak. Index 0–9: basismodaliteiten; hogere: geometrische en fractale varianten. Zie de hint-tekst hierboven.");
	const QString tipShapeAux = QStringLiteral(
		"Extra parameter per profiel: ovaal, ring, tandwiel, fraktalen (iteraties, hoek, gap, Julia-c, enz.). 1.0 = startwaarde.");
	const QString tipFallP = QStringLiteral("Profiel van de uitdoving: Gauss, smooth step, lineair, exponentieel.");
	const QString tipEdgeSide = QStringLiteral(
		"Welke kant van de SDF oplicht: beide, alleen buiten, of alleen binnen (bij holle/ringvormen).");
	for (int i = 1; i <= PATTERN_LINE_TRAP_COUNT; i++)
	{
		const QString s = QString::number(i);
		if (QLabel *l = parent->findChild<QLabel *>(QStringLiteral("label_pattern_line_%1_pos").arg(s)))
			l->setToolTip(tipPos);
		if (QLabel *l = parent->findChild<QLabel *>(QStringLiteral("label_pattern_line_%1_rot").arg(s)))
			l->setToolTip(tipRot);
		if (QLabel *l = parent->findChild<QLabel *>(QStringLiteral("label_pattern_line_%1_radius").arg(s)))
			l->setToolTip(tipRadius);
		if (QWidget *w = parent->findChild<QWidget *>(QStringLiteral("logedit_pattern_line_trap_%1_radius").arg(s)))
			w->setToolTip(tipRadius);
		if (QWidget *w = parent->findChild<QWidget *>(QStringLiteral("logedit_pattern_line_trap_%1_thickness").arg(s)))
			w->setToolTip(tipThickness);
		if (QLabel *l = parent->findChild<QLabel *>(QStringLiteral("label_pattern_line_%1_scale").arg(s)))
			l->setToolTip(tipScale);
		if (QWidget *w = parent->findChild<QWidget *>(QStringLiteral("logedit_pattern_line_trap_%1_scale").arg(s)))
			w->setToolTip(tipScale);
		if (QWidget *w = parent->findChild<QWidget *>(QStringLiteral("logedit_pattern_line_trap_%1_relative_thickness").arg(s)))
			w->setToolTip(tipRelTh);
		if (QWidget *w = parent->findChild<QWidget *>(QStringLiteral("logedit_pattern_line_trap_%1_edge_softness").arg(s)))
			w->setToolTip(tipEdge);
		if (QWidget *w = parent->findChild<QWidget *>(QStringLiteral("logedit_pattern_line_trap_%1_max_distance").arg(s)))
			w->setToolTip(tipMaxDist);
		if (QLabel *l = parent->findChild<QLabel *>(QStringLiteral("label_pattern_line_%1_int").arg(s)))
			l->setToolTip(QStringLiteral("Intensiteit van deze laag in de uiteindelijke mix (na falloff)."));
		if (QWidget *w = parent->findChild<QWidget *>(QStringLiteral("logedit_pattern_line_trap_%1_intensity").arg(s)))
			w->setToolTip(QStringLiteral("Zelfde als Int.: helderheid van de lijn (emissie-achtig)."));
		if (QLabel *l = parent->findChild<QLabel *>(QStringLiteral("label_pattern_line_%1_shape").arg(s)))
			l->setToolTip(tipShape);
		if (QWidget *w = parent->findChild<QWidget *>(QStringLiteral("comboBox_pattern_line_trap_%1_shape").arg(s)))
			w->setToolTip(tipShape);
		if (QLabel *l = parent->findChild<QLabel *>(QStringLiteral("label_pattern_line_%1_shape_aux").arg(s)))
			l->setToolTip(tipShapeAux);
		if (QWidget *w = parent->findChild<QWidget *>(QStringLiteral("logedit_pattern_line_trap_%1_shape_aux").arg(s)))
			w->setToolTip(tipShapeAux);
		if (QLabel *l = parent->findChild<QLabel *>(QStringLiteral("label_pattern_line_%1_sharp_seg").arg(s)))
			l->setToolTip(
				QStringLiteral("Scherpte (links) = falloff; Segment (rechts) = halve lijnlengte. Zie tooltips per veld."));
		if (QWidget *w = parent->findChild<QWidget *>(QStringLiteral("logedit_pattern_line_trap_%1_falloff_sharpness").arg(s)))
			w->setToolTip(tipSharp);
		if (QWidget *w = parent->findChild<QWidget *>(QStringLiteral("logedit_pattern_line_trap_%1_segment_half_length").arg(s)))
			w->setToolTip(tipSeg);
		if (QLabel *l = parent->findChild<QLabel *>(QStringLiteral("label_pattern_line_%1_glow").arg(s)))
			l->setToolTip(
				QStringLiteral("Gloed: links bedient falloff, rechts de spreiding. Zie tooltips per numeriek veld."));
		if (QWidget *w = parent->findChild<QWidget *>(QStringLiteral("logedit_pattern_line_trap_%1_glow_spread").arg(s)))
			w->setToolTip(tipGlow);
		if (QWidget *w = parent->findChild<QWidget *>(QStringLiteral("comboBox_pattern_line_trap_%1_falloff_profile").arg(s)))
			w->setToolTip(tipFallP);
		if (QWidget *w = parent->findChild<QWidget *>(QStringLiteral("comboBox_pattern_line_trap_%1_edge_side").arg(s)))
			w->setToolTip(tipEdgeSide);
	}
}

} // namespace

cDockPatternLines::cDockPatternLines(QWidget *parent)
		: QWidget(parent), cMyWidgetWithParams(), ui(new Ui::cDockPatternLines)
{
	ui->setupUi(this);

	m_auxOffsetDebounceTimer = new QTimer(this);
	m_auxOffsetDebounceTimer->setSingleShot(true);
	m_auxOffsetDebounceTimer->setInterval(32);
	QObject::connect(
		m_auxOffsetDebounceTimer, &QTimer::timeout, this, &cDockPatternLines::slotAuxOffsetDebounceFired);

	automatedWidgets = new cAutomatedWidgets(this);
	automatedWidgets->ConnectSignalsForSlidersInWindow(this);
	ConnectSignals();
	RefreshPatternLinePresetCombo();
	SetupPatternLineLayersTooltips(this);
}

cDockPatternLines::~cDockPatternLines()
{
	delete ui;
}

void cDockPatternLines::AssignParameterContainers(
	std::shared_ptr<cParameterContainer> _params, std::shared_ptr<cFractalContainer> _fractalParams)
{
	cMyWidgetWithParams::AssignParameterContainers(_params, _fractalParams);
	FillPatternLineTrapEnumCombos();
	syncAuxLightPlacementOffsetBaseline();
}

void cDockPatternLines::slotSynchronizeInterfacePatternLineTraps(
	std::shared_ptr<cParameterContainer> par)
{
	(void)par;
	SynchronizeInterfaceWindow(this, params, qInterface::write);
	syncAuxLightPlacementOffsetBaseline();
	// O.a. signaal vanaf manipulations: anders wijzigt gPar de settings-hash t.o.v. autoRefreshLastHash
	// en start PeriodicRefresh in een extra StartRender.
	if (gMainInterface) gMainInterface->SyncAutoRefreshHashWithGpar();
}

void cDockPatternLines::setExactPlacementButtonCheckedNoSignals(const bool on)
{
	if (!TRAPS_UI->pushButton_pattern_line_exact_activate) return;
	if (TRAPS_UI->pushButton_pattern_line_exact_activate->isChecked() == on) return;
	TRAPS_UI->pushButton_pattern_line_exact_activate->blockSignals(true);
	TRAPS_UI->pushButton_pattern_line_exact_activate->setChecked(on);
	TRAPS_UI->pushButton_pattern_line_exact_activate->blockSignals(false);
}

int cDockPatternLines::findPatternLineModeRowInMouseCombo(const int layer) const
{
	if (!mouseFunctionComboWidget) return -1;
	const int wantMode = int(RenderedImage::clickPlacePatternLineTrap);
	for (int i = 0; i < mouseFunctionComboWidget->count(); ++i)
	{
		const QVariant v = mouseFunctionComboWidget->itemData(i);
		if (!v.isValid()) continue;
		const QList<QVariant> data = v.toList();
		if (data.size() < 2) continue;
		if (data[0].toInt() == wantMode && data[1].toInt() == layer) return i;
	}
	return -1;
}

bool cDockPatternLines::applyExactClickPlacementForLayer(const int layer)
{
	if (!mouseFunctionComboWidget || !renderedImageWidget)
	{
		QMessageBox::warning(this, tr("Patroon-lijnen"),
			tr("De muisactie-koppeling is niet beschikbaar. Herstart Mandelbulber of open het "
			   "standaard render-venster."));
		return false;
	}
	SynchronizeInterfaceWindow(this, params, qInterface::read);

	QList<QVariant> item;
	item.append(int(RenderedImage::clickPlacePatternLineTrap));
	item.append(layer);

	int idx = -1;
	{
		const QSignalBlocker blockCombo(mouseFunctionComboWidget);
		gMainInterface->ComboMouseClickUpdate();
		idx = mouseFunctionComboWidget->findData(item);
		if (idx < 0) idx = findPatternLineModeRowInMouseCombo(layer);
		if (idx < 0)
		{
			QMessageBox::warning(this, tr("Patroon-lijnen"),
				tr("De lijst met muisacties bevat geen patroonlijn-plaatsing. Installeer de juiste build "
				   "en herstart de applicatie."));
			return false;
		}
		mouseFunctionComboWidget->setCurrentIndex(idx);
	}
	renderedImageWidget->setClickMode(item);

	const int precIdx = TRAPS_UI->comboBox_pattern_line_precision_mode
		? TRAPS_UI->comboBox_pattern_line_precision_mode->currentIndex()
		: 0;
	params->Set("pattern_line_precision_mode", precIdx);
	const bool subPrecise = (precIdx == 1);
	if (subPrecise)
	{
		params->Set("aux_light_manual_placement_dist", 0.0);
	}
	else
	{
		const CVector3 camera = params->Get<CVector3>("camera");
		const double dist = cInterface::GetDistanceForPoint(camera, params, fractalParams);
		params->Set("aux_light_manual_placement_dist", dist * 0.1);
	}
	// Moet overeenkomen met combo; anders zet SynchronizeInterface(write) muisactie terug
	// (mouse_click_function) en overschrijft setClickMode weer.
	params->Set("mouse_click_function", idx);

	SynchronizeInterfaceWindow(this, params, qInterface::write);

	if (gMainInterface->mainWindow && gMainInterface->mainWindow->statusBar())
	{
		gMainInterface->mainWindow->statusBar()->showMessage(
			tr("Modus AAN (lijn %1): klik in render, of Enter/Spatie = midden beeld; [ en ] of verticaal slepen = offset; "
			   "Alt+scroll in Effects ook. Uit: knop of andere muisactie.")
				.arg(layer),
			12000);
	}
	if (gMainInterface->mainWindow)
	{
		gMainInterface->mainWindow->raise();
		gMainInterface->mainWindow->activateWindow();
	}
	renderedImageWidget->setFocus(Qt::OtherFocusReason);
	// Zorg dat knop visueel AAN staat (QSignalBlocker kan currentIndexChanged-signal hebben
	// onderdrukt, waardoor slotMouseFunctionComboChanged de knop niet heeft aangezet).
	setExactPlacementButtonCheckedNoSignals(true);
	if (TRAPS_UI->pushButton_pattern_line_exact_activate) TRAPS_UI->pushButton_pattern_line_exact_activate->update();
	return true;
}

void cDockPatternLines::deactivateExactClickPlacement()
{
	if (!mouseFunctionComboWidget || !renderedImageWidget) return;
	QList<QVariant> none;
	none.append(int(RenderedImage::clickDoNothing));
	int i0 = mouseFunctionComboWidget->findData(none);
	if (i0 < 0)
	{
		for (int r = 0; r < mouseFunctionComboWidget->count(); ++r)
		{
			const QList<QVariant> d = mouseFunctionComboWidget->itemData(r).toList();
			if (!d.isEmpty() && d[0].toInt() == int(RenderedImage::clickDoNothing))
			{
				i0 = r;
				break;
			}
		}
	}
	if (i0 < 0) return;
	{
		const QSignalBlocker blockCombo(mouseFunctionComboWidget);
		mouseFunctionComboWidget->setCurrentIndex(i0);
	}
	if (params) params->Set("mouse_click_function", i0);
	renderedImageWidget->setClickMode(none);
	if (gMainInterface->mainWindow && gMainInterface->mainWindow->statusBar())
	{
		gMainInterface->mainWindow->statusBar()->showMessage(
			tr("Exacte patroonlijn-plaatsing uit (muis: geen actie)."), 5000);
	}
}

void cDockPatternLines::slotExactPlacementToggled(const bool checked)
{
	if (checked)
	{
		if (!applyExactClickPlacementForLayer(TRAPS_UI->spinbox_pattern_line_exact_layer->value()))
			setExactPlacementButtonCheckedNoSignals(false);
	}
	else
	{
		deactivateExactClickPlacement();
	}
}

void cDockPatternLines::slotMouseFunctionComboChanged(int index)
{
	(void)index;
	if (!mouseFunctionComboWidget || !TRAPS_UI->pushButton_pattern_line_exact_activate) return;
	const QList<QVariant> data = mouseFunctionComboWidget->currentData().toList();
	const int mode0 = data.isEmpty() ? -1 : data.at(0).toInt();
	const bool isPl = (mode0 == int(RenderedImage::clickPlacePatternLineTrap));
	if (isPl && data.size() >= 2)
	{
		const int L = data.at(1).toInt();
		TRAPS_UI->spinbox_pattern_line_exact_layer->blockSignals(true);
		TRAPS_UI->spinbox_pattern_line_exact_layer->setValue(L);
		TRAPS_UI->spinbox_pattern_line_exact_layer->blockSignals(false);
		setExactPlacementButtonCheckedNoSignals(true);
	}
	else
	{
		setExactPlacementButtonCheckedNoSignals(false);
	}
}

void cDockPatternLines::slotExactLayerNumberChanged(const int layer)
{
	if (!TRAPS_UI->pushButton_pattern_line_exact_activate || !TRAPS_UI->pushButton_pattern_line_exact_activate->isChecked())
		return;
	if (!applyExactClickPlacementForLayer(layer))
		setExactPlacementButtonCheckedNoSignals(false);
}

void cDockPatternLines::slotPatternLinePrecisionModeChanged(const int index)
{
	(void)index;
	if (params && TRAPS_UI->comboBox_pattern_line_precision_mode)
		params->Set("pattern_line_precision_mode", TRAPS_UI->comboBox_pattern_line_precision_mode->currentIndex());
	if (!TRAPS_UI->pushButton_pattern_line_exact_activate || !TRAPS_UI->pushButton_pattern_line_exact_activate->isChecked())
		return;
	if (!applyExactClickPlacementForLayer(TRAPS_UI->spinbox_pattern_line_exact_layer->value()))
		setExactPlacementButtonCheckedNoSignals(false);
}

void cDockPatternLines::FillPatternLineTrapEnumCombos()
{
	if (!params) return;
	for (int i = 1; i <= PATTERN_LINE_TRAP_COUNT; i++)
	{
		const QString pFalloff =
			QStringLiteral("pattern_line_trap_%1_falloff_profile").arg(i);
		QComboBox *cb = findChild<QComboBox *>(
			QStringLiteral("comboBox_pattern_line_trap_%1_falloff_profile").arg(i));
		if (cb)
		{
			const QStringList items = params->GetAsOneParameter(pFalloff).GetEnumLookup();
			if (items.size() >= 2)
			{
				int sel = params->Get<int>(pFalloff);
				cb->blockSignals(true);
				cb->clear();
				cb->addItems(items);
				const int n = cb->count();
				if (n > 0) cb->setCurrentIndex(qBound(0, sel, n - 1));
				cb->blockSignals(false);
			}
		}
		const QString pShape = QStringLiteral("pattern_line_trap_%1_shape").arg(i);
		QComboBox *cbS = findChild<QComboBox *>(
			QStringLiteral("comboBox_pattern_line_trap_%1_shape").arg(i));
		if (cbS)
		{
			const QStringList shapeItems = params->GetAsOneParameter(pShape).GetEnumLookup();
			if (shapeItems.size() >= 2)
			{
				int ssel = params->Get<int>(pShape);
				cbS->blockSignals(true);
				cbS->clear();
				cbS->addItems(shapeItems);
				const int ns = cbS->count();
				if (ns > 0) cbS->setCurrentIndex(qBound(0, ssel, ns - 1));
				cbS->blockSignals(false);
			}
		}
	}
}

void cDockPatternLines::AssignSpecialWidgets(
	RenderedImage *_renderedImage, QComboBox *_mouseFunctionCombo)
{
	cMyWidgetWithParams::AssignSpecialWidgets(_renderedImage, _mouseFunctionCombo);
	if (mouseFunctionComboWidget)
	{
		QObject::disconnect(mouseFunctionComboWidget, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
			&cDockPatternLines::slotMouseFunctionComboChanged);
		connect(mouseFunctionComboWidget, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
			&cDockPatternLines::slotMouseFunctionComboChanged, Qt::UniqueConnection);
	}
	if (TRAPS_UI->spinbox_pattern_line_exact_layer)
	{
		connect(TRAPS_UI->spinbox_pattern_line_exact_layer,
			QOverload<int>::of(&QSpinBox::valueChanged), this,
			&cDockPatternLines::slotExactLayerNumberChanged);
	}
	if (renderedImageWidget && TRAPS_UI->checkBox_pattern_line_traps_overlay_visible)
	{
		renderedImageWidget->SetPatternLineTrapsVisibility(
			TRAPS_UI->checkBox_pattern_line_traps_overlay_visible->isChecked());
	}
	slotMouseFunctionComboChanged(-1);
}

void cDockPatternLines::syncAuxLightPlacementOffsetBaseline()
{
	if (!params) return;
	if (m_auxOffsetDebounceTimer) m_auxOffsetDebounceTimer->stop();
	m_lastAuxWorldOffset = params->Get<CVector3>("aux_light_manual_placement_offset");
}

void cDockPatternLines::slotAuxOffsetTextChanged()
{
	if (m_suppressAuxOffsetTextCallbacks) return;
	if (m_auxOffsetDebounceTimer) m_auxOffsetDebounceTimer->start();
}

void cDockPatternLines::slotAuxOffsetCommitNow()
{
	if (m_suppressAuxOffsetTextCallbacks) return;
	if (m_auxOffsetDebounceTimer) m_auxOffsetDebounceTimer->stop();
	applyAuxLightWorldOffsetFromUi(true);
}

void cDockPatternLines::slotAuxOffsetDebounceFired()
{
	applyAuxLightWorldOffsetFromUi(false);
}

void cDockPatternLines::applyAuxLightWorldOffsetFromUi(const bool flushStartRender)
{
	if (!params) return;
	if (!TRAPS_UI->vect3_aux_light_manual_placement_offset_x || !TRAPS_UI->vect3_aux_light_manual_placement_offset_y
			|| !TRAPS_UI->vect3_aux_light_manual_placement_offset_z)
		return;
	const CVector3 baseline = m_lastAuxWorldOffset;
	const CVector3 now(systemData.locale.toDouble(TRAPS_UI->vect3_aux_light_manual_placement_offset_x->text()),
		systemData.locale.toDouble(TRAPS_UI->vect3_aux_light_manual_placement_offset_y->text()),
		systemData.locale.toDouble(TRAPS_UI->vect3_aux_light_manual_placement_offset_z->text()));
	gPar->Set("aux_light_manual_placement_offset", now);
	const CVector3 d = now - baseline;
	if (d.x == 0.0 && d.y == 0.0 && d.z == 0.0) return;

	const QList<int> lightIds = cLights::GetListOfLights(gPar);
	for (int id : lightIds)
	{
		if (!gPar->Get<bool>(cLight::Name("is_defined", id))) continue;
		const QString pPos = cLight::Name("position", id);
		const CVector3 p = gPar->Get<CVector3>(pPos);
		gPar->Set(pPos, p + d);
	}
	for (int l = 1; l <= PATTERN_LINE_TRAP_COUNT; l++)
	{
		std::shared_ptr<cParameterContainer> pl = params ? params : gPar;
		if (!pl->Get<bool>(QString("pattern_line_trap_%1_enabled").arg(l))) continue;
		const QString pPos = QString("pattern_line_trap_%1_position").arg(l);
		const CVector3 p = pl->Get<CVector3>(pPos);
		pl->Set(pPos, p + d);
	}
	m_lastAuxWorldOffset = now;

	m_suppressAuxOffsetTextCallbacks = true;
	if (flushStartRender)
		gMainInterface->RefreshLightAndPatternLineDocksFromGpar();
	else
	{
		// Tussentijds: geen volledige Synchronize over hele patroon/effects (32ms debounce = haperen).
		gMainInterface->WriteLightAndPatternLineWorldPositionFieldsFromGpar();
		if (gMainInterface) gMainInterface->SyncAutoRefreshHashWithGpar();
	}
	m_suppressAuxOffsetTextCallbacks = false;

	if (flushStartRender) gMainInterface->StartRenderFromCurrentParams(true);
	// Geen tussentijdse StartRender: elke herstart = OpenCL opnieuw (stop + leeg/centraal tegels = zwart).
	// Wiel/sleper: gPar+ docks lopen live mee; beeld = na Enter of veld sluiten (editingFinished).
}

void cDockPatternLines::ConnectSignals()
{
	CHECK_MAIN_INTERFACE();
	if (TRAPS_UI->pushButton_pattern_line_exact_activate)
	{
		QPushButton *ex = TRAPS_UI->pushButton_pattern_line_exact_activate;
		ex->setCheckable(true);
		ex->setAutoDefault(false);
		ex->setDefault(false);
		ex->setAttribute(Qt::WA_StyledBackground, true);
		ex->setStyleSheet(QStringLiteral(
			"QPushButton#pushButton_pattern_line_exact_activate {"
			"  background-color: palette(button); color: palette(button-text);"
			"  border: 2px solid palette(mid); border-radius: 5px; padding: 7px 10px; text-align: left;"
			"}"
			"QPushButton#pushButton_pattern_line_exact_activate:checked {"
			"  background-color: #1b5e20 !important; color: #ffffff !important; border: 2px solid #0d3010 !important;"
			"  font-weight: 600;"
			"}"
			"QPushButton#pushButton_pattern_line_exact_activate:hover:!checked {"
			"  background-color: palette(light);"
			"}"
			"QPushButton#pushButton_pattern_line_exact_activate:hover:checked {"
			"  background-color: #2e7d32 !important; color: #ffffff !important;"
			"}"));
		connect(ex, &QPushButton::toggled, this, &cDockPatternLines::slotExactPlacementToggled);
	}
	if (TRAPS_UI->comboBox_pattern_line_precision_mode)
	{
		connect(TRAPS_UI->comboBox_pattern_line_precision_mode,
			QOverload<int>::of(&QComboBox::currentIndexChanged), this,
			&cDockPatternLines::slotPatternLinePrecisionModeChanged);
	}
	for (int i = 1; i <= PATTERN_LINE_TRAP_COUNT; i++)
	{
		if (QPushButton *b =
					findChild<QPushButton *>(QString("pushButton_pattern_line_trap_%1_place_surface").arg(i)))
			connect(b, &QPushButton::clicked, this,
				&cDockPatternLines::slotPressedButtonPlacePatternLineTrapAtSurface);
		if (QPushButton *b =
					findChild<QPushButton *>(QString("pushButton_pattern_line_trap_%1_place_target").arg(i)))
			connect(b, &QPushButton::clicked, this,
				&cDockPatternLines::slotPressedButtonPlacePatternLineTrapAtTarget);
	}
	if (TRAPS_UI->pushButton_pattern_line_traps_quick_test)
		connect(TRAPS_UI->pushButton_pattern_line_traps_quick_test, &QPushButton::clicked, this,
			&cDockPatternLines::slotPressedButtonPatternLineTrapsQuickTest);
	if (TRAPS_UI->pushButton_pattern_line_traps_enable_all)
		connect(TRAPS_UI->pushButton_pattern_line_traps_enable_all, &QPushButton::clicked, this,
			&cDockPatternLines::slotEnableAllPatternLineTraps);
	if (TRAPS_UI->pushButton_pattern_line_traps_disable_all)
		connect(TRAPS_UI->pushButton_pattern_line_traps_disable_all, &QPushButton::clicked, this,
			&cDockPatternLines::slotDisableAllPatternLineTraps);
	if (TRAPS_UI->pushButton_pattern_line_traps_solo_selected)
		connect(TRAPS_UI->pushButton_pattern_line_traps_solo_selected, &QPushButton::clicked, this,
			&cDockPatternLines::slotSoloSelectedPatternLineTrap);
	if (TRAPS_UI->spinboxInt_pattern_line_trap_solo_layer)
	{
		connect(TRAPS_UI->spinboxInt_pattern_line_trap_solo_layer,
			QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
				if (params) params->Set("pattern_line_trap_solo_layer", value);
				gMainInterface->RequestRender(QStringLiteral("pattern line solo layer"), 120, true);
			});
	}
	if (TRAPS_UI->checkBox_pattern_line_traps_overlay_visible)
	{
		connect(TRAPS_UI->checkBox_pattern_line_traps_overlay_visible, &QCheckBox::stateChanged, this,
			[this](int state) {
				if (renderedImageWidget)
					renderedImageWidget->SetPatternLineTrapsVisibility(state == Qt::Checked);
			});
		// Initieel aan zetten
		if (renderedImageWidget)
			renderedImageWidget->SetPatternLineTrapsVisibility(
				TRAPS_UI->checkBox_pattern_line_traps_overlay_visible->isChecked());
	}

	if (TRAPS_UI->pushButton_pattern_line_trap_preset_refresh)
		connect(TRAPS_UI->pushButton_pattern_line_trap_preset_refresh, &QPushButton::clicked, this,
			&cDockPatternLines::slotPatternLineTrapPresetRefresh);
	if (TRAPS_UI->pushButton_pattern_line_trap_preset_load)
		connect(TRAPS_UI->pushButton_pattern_line_trap_preset_load, &QPushButton::clicked, this,
			&cDockPatternLines::slotPatternLineTrapPresetLoad);
	// Laad ook automatisch bij selectie in de dropdown (intuïtiever)
	if (TRAPS_UI->comboBox_pattern_line_trap_presets)
		connect(TRAPS_UI->comboBox_pattern_line_trap_presets, QOverload<int>::of(&QComboBox::activated), this,
			&cDockPatternLines::slotPatternLineTrapPresetLoad);
	if (TRAPS_UI->pushButton_pattern_line_trap_preset_save)
		connect(TRAPS_UI->pushButton_pattern_line_trap_preset_save, &QPushButton::clicked, this,
			&cDockPatternLines::slotPatternLineTrapPresetSave);
	if (TRAPS_UI->pushButton_pattern_line_trap_copy_layer)
		connect(TRAPS_UI->pushButton_pattern_line_trap_copy_layer, &QPushButton::clicked, this,
			&cDockPatternLines::slotPatternLineTrapCopyLayer);

	connect(ui->pushButton_pattern_dock_navi, &QPushButton::clicked, this,
		&cDockPatternLines::slotPressedButtonNavi);
	if (ui->pushButton_pattern_dock_reset)
	{
		ui->pushButton_pattern_dock_reset->disconnect();
		connect(ui->pushButton_pattern_dock_reset, &QPushButton::clicked, this,
			&cDockPatternLines::slotResetPatternLineTraps);
	}
	// Offset: textChanged → debounce (alleen gPar+ docks). Beeld: Enter / editingFinished (één render).
	if (TRAPS_UI->vect3_aux_light_manual_placement_offset_x)
	{
		QObject::connect(TRAPS_UI->vect3_aux_light_manual_placement_offset_x, &QLineEdit::textChanged, this,
			&cDockPatternLines::slotAuxOffsetTextChanged, Qt::UniqueConnection);
		QObject::connect(
			TRAPS_UI->vect3_aux_light_manual_placement_offset_x, &QLineEdit::editingFinished, this,
			&cDockPatternLines::slotAuxOffsetCommitNow, Qt::UniqueConnection);
		QObject::connect(
			TRAPS_UI->vect3_aux_light_manual_placement_offset_x, &QLineEdit::returnPressed, this,
			&cDockPatternLines::slotAuxOffsetCommitNow, Qt::UniqueConnection);
	}
	if (TRAPS_UI->vect3_aux_light_manual_placement_offset_y)
	{
		QObject::connect(TRAPS_UI->vect3_aux_light_manual_placement_offset_y, &QLineEdit::textChanged, this,
			&cDockPatternLines::slotAuxOffsetTextChanged, Qt::UniqueConnection);
		QObject::connect(
			TRAPS_UI->vect3_aux_light_manual_placement_offset_y, &QLineEdit::editingFinished, this,
			&cDockPatternLines::slotAuxOffsetCommitNow, Qt::UniqueConnection);
		QObject::connect(
			TRAPS_UI->vect3_aux_light_manual_placement_offset_y, &QLineEdit::returnPressed, this,
			&cDockPatternLines::slotAuxOffsetCommitNow, Qt::UniqueConnection);
	}
	if (TRAPS_UI->vect3_aux_light_manual_placement_offset_z)
	{
		QObject::connect(TRAPS_UI->vect3_aux_light_manual_placement_offset_z, &QLineEdit::textChanged, this,
			&cDockPatternLines::slotAuxOffsetTextChanged, Qt::UniqueConnection);
		QObject::connect(
			TRAPS_UI->vect3_aux_light_manual_placement_offset_z, &QLineEdit::editingFinished, this,
			&cDockPatternLines::slotAuxOffsetCommitNow, Qt::UniqueConnection);
		QObject::connect(
			TRAPS_UI->vect3_aux_light_manual_placement_offset_z, &QLineEdit::returnPressed, this,
			&cDockPatternLines::slotAuxOffsetCommitNow, Qt::UniqueConnection);
	}
}

void cDockPatternLines::RefreshPatternLinePresetCombo()
{
	if (!TRAPS_UI->comboBox_pattern_line_trap_presets) return;
	TRAPS_UI->comboBox_pattern_line_trap_presets->clear();
	const QString folder = systemDirectories.GetPatternLinePresetsFolder();
	QDir dir(folder);
	WriteLogString("RefreshPatternLinePresetCombo: folder", folder, 1);
	if (!dir.exists()) { WriteLog("RefreshPatternLinePresetCombo: folder does not exist", 1); return; }
	const QStringList files =
		dir.entryList(QStringList{QStringLiteral("*.m3p"), QStringLiteral("*.fract"), QStringLiteral("*.txt")},
			QDir::Files, QDir::Name);
	WriteLogInt("RefreshPatternLinePresetCombo: found files", files.size(), 1);
	for (const QString &name : files)
		TRAPS_UI->comboBox_pattern_line_trap_presets->addItem(name, QVariant(dir.absoluteFilePath(name)));
}

void cDockPatternLines::slotPatternLineTrapPresetRefresh()
{
	RefreshPatternLinePresetCombo();
}

void cDockPatternLines::slotPatternLineTrapPresetLoad()
{
	CHECK_MAIN_INTERFACE();
	WriteLog("[PatternLines] slotPatternLineTrapPresetLoad() called", 1);
	if (!TRAPS_UI->comboBox_pattern_line_trap_presets)
	{
		WriteLog("[PatternLines] early return: no comboBox", 1);
		return;
	}
	const int idx = TRAPS_UI->comboBox_pattern_line_trap_presets->currentIndex();
	if (idx < 0)
	{
		WriteLog("[PatternLines] early return: idx < 0", 1);
		return;
	}
	const QString path = TRAPS_UI->comboBox_pattern_line_trap_presets->itemData(idx).toString();
	if (path.isEmpty())
	{
		WriteLog("[PatternLines] early return: path empty", 1);
		return;
	}

	std::shared_ptr<cParameterContainer> targetPar = params ? params : gPar;
	std::shared_ptr<cFractalContainer> targetFract = fractalParams ? fractalParams : gParFractal;

	WriteLogString("[PatternLines] Loading preset", path, 1);

	// Eerst ALLE pattern-line parameters resetten naar default zodat de preset
	// als een schone lei laadt (condensed text overschrijft alleen wat erin staat).
	const QStringList paramNames = patternLineTrapPresetMainParameterNames();
	for (const QString &fullName : paramNames)
	{
		const int firstUnderscore = fullName.indexOf('_');
		const QString containerName = fullName.left(firstUnderscore);
		const QString parameterName = fullName.mid(firstUnderscore + 1);
		if (containerName != QStringLiteral("main")) continue;
		if (!targetPar->IfExists(parameterName)) continue;
		cOneParameter oneParam = targetPar->GetAsOneParameter(parameterName);
		oneParam.SetMultiVal(oneParam.GetMultiVal(valueDefault), valueActual);
		targetPar->SetFromOneParameter(parameterName, oneParam);
	}

	SynchronizeInterfaceWindow(this, targetPar, qInterface::write);

	cSettings parSettings(cSettings::formatFullText);
	parSettings.SetListOfParametersToProcess(paramNames);

	gMainInterface->DisablePeriodicRefresh();
	gInterfaceReadyForSynchronization = false;
	bool loadOk = parSettings.LoadFromFile(path);
	WriteLogString("[PatternLines] LoadFromFile result", loadOk ? "true" : "false", 1);
	bool decodeOk = parSettings.Decode(targetPar, targetFract, gAnimFrames, gKeyframes);
	WriteLogString("[PatternLines] Decode result", decodeOk ? "true" : "false", 1);
	WriteLogString("[PatternLines] After decode - enabled",
		(targetPar->Get<bool>("pattern_line_traps_enabled") ? "true" : "false"), 1);
	WriteLogInt("[PatternLines] After decode - solo",
		targetPar->Get<int>("pattern_line_trap_solo_layer"), 1);
	WriteLogDouble("[PatternLines] After decode - l1_int",
		targetPar->Get<double>("pattern_line_trap_1_intensity"), 1);
	WriteLogDouble("[PatternLines] After decode - l1_rad",
		targetPar->Get<double>("pattern_line_trap_1_radius"), 1);
	SynchronizeInterfaceWindow(this, targetPar, qInterface::write);
	gInterfaceReadyForSynchronization = true;
	gMainInterface->ComboMouseClickUpdate();
	gMainInterface->ReEnablePeriodicRefresh();
	gMainInterface->RequestRender(QStringLiteral("pattern lines"), 120, true);
}

void cDockPatternLines::slotPatternLineTrapPresetSave()
{
	std::shared_ptr<cParameterContainer> targetPar = params ? params : gPar;
	std::shared_ptr<cFractalContainer> targetFract = fractalParams ? fractalParams : gParFractal;
	SynchronizeInterfaceWindow(this, targetPar, qInterface::read);
	QDir().mkpath(systemDirectories.GetPatternLinePresetsFolder());

	bool ok = false;
	QString name = QInputDialog::getText(this, tr("Preset opslaan"),
		tr("Naam voor nieuwe preset:"), QLineEdit::Normal, QString(), &ok);
	if (!ok || name.isEmpty()) return;

	name = name.trimmed();
	if (!name.endsWith(QStringLiteral(".m3p"), Qt::CaseInsensitive))
		name += QStringLiteral(".m3p");

	/* Verwijder ongeldige tekens uit bestandsnaam */
	name.replace(QRegularExpression(QStringLiteral("[<>:\"/\\|?*]")), QStringLiteral("_"));

	const QString path =
		systemDirectories.GetPatternLinePresetsFolder() + QDir::separator() + name;

	if (QFile::exists(path))
	{
		const int ret = QMessageBox::question(this, tr("Preset overschrijven?"),
			tr("'%1' bestaat al. Overschrijven?").arg(name),
			QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
		if (ret != QMessageBox::Yes) return;
	}

	cSettings parSettings(cSettings::formatCondensedText);
	parSettings.SetListOfParametersToProcess(patternLineTrapPresetMainParameterNames());
	parSettings.CreateText(targetPar, targetFract, gAnimFrames, gKeyframes);
	if (!parSettings.SaveToFile(path))
	{
		QMessageBox::warning(this, tr("Patroon-preset"),
			tr("Kon preset niet opslaan:\n%1").arg(path));
		return;
	}

	RefreshPatternLinePresetCombo();
	const int idx = TRAPS_UI->comboBox_pattern_line_trap_presets->findData(QVariant(path));
	if (idx >= 0) TRAPS_UI->comboBox_pattern_line_trap_presets->setCurrentIndex(idx);
}

void cDockPatternLines::slotPatternLineTrapCopyLayer()
{
	CHECK_MAIN_INTERFACE();
	const int from = TRAPS_UI->spinbox_pattern_line_trap_copy_from->value();
	const int to = TRAPS_UI->spinbox_pattern_line_trap_copy_to->value();
	if (from == to) return;
	std::shared_ptr<cParameterContainer> targetPar = params ? params : gPar;
	SynchronizeInterfaceWindow(this, targetPar, qInterface::read);
	const QString pf = QStringLiteral("pattern_line_trap_%1").arg(from);
	const QString pt = QStringLiteral("pattern_line_trap_%1").arg(to);
	for (const QString &s : patternLineTrapLayerSuffixes())
		targetPar->SetFromOneParameter(pt + s, targetPar->GetAsOneParameter(pf + s));
	if (QWidget *fw = QApplication::focusWidget()) fw->clearFocus();
	SynchronizeInterfaceWindow(this, targetPar, qInterface::write);
	gMainInterface->RequestRender(QStringLiteral("pattern lines"), 120, true);
}

void cDockPatternLines::EnsurePatternLineTrapsMasterAndLayer(int layerIndex)
{
	if (layerIndex < 1 || layerIndex > PATTERN_LINE_TRAP_COUNT) return;
	if (params)
	{
		params->Set("pattern_line_traps_enabled", true);
		params->Set(QString("pattern_line_trap_%1_enabled").arg(layerIndex), true);
	}
	if (TRAPS_UI->checkBox_pattern_line_traps_enabled)
		TRAPS_UI->checkBox_pattern_line_traps_enabled->setChecked(true);
	if (QGroupBox *layerBox =
					findChild<QGroupBox *>(QString("groupCheck_pattern_line_trap_%1_enabled").arg(layerIndex)))
		layerBox->setChecked(true);
}

double cDockPatternLines::PatternLineTrapBumpFromView(int layerNum) const
{
	const QString p = QString("pattern_line_trap_%1").arg(layerNum);
	sPatternLineTrapLayer tmp;
	tmp.radius = params->Get<double>(p + "_radius");
	tmp.shape = params->Get<int>(p + "_shape");
	tmp.shapeAux = params->Get<double>(p + "_shape_aux");
	const double ext = PatternLineTrapProfileExtent(tmp);
	const double es = fabs(params->Get<double>(p + "_edge_softness"));
	const double md = fabs(params->Get<double>(p + "_max_distance"));
	const double seg = fabs(params->Get<double>(p + "_segment_half_length"));
	return std::max(0.1, ext * 2.5 + es * 0.6 + std::min(md, 3.0) * 0.12 + seg * 0.08);
}

bool cDockPatternLines::RaymarchFirstSurface(
	const CVector3 &origin, const CVector3 &dirUnit, CVector3 *hitPoint) const
{
	CVector3 point = origin;
	double totalDist = 0.0;
	const double maxDist = 100.0;
	for (int i = 0; i < 1000; i++)
	{
		double dist = cInterface::GetDistanceForPoint(point, params, fractalParams);
		if (dist < 1e-6)
		{
			*hitPoint = point;
			return true;
		}
		if (totalDist > maxDist) break;
		point += dirUnit * dist;
		totalDist += dist;
	}
	*hitPoint = point;
	return false;
}

void cDockPatternLines::slotPressedButtonNavi()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->SynchronizeInterface(params, fractalParams, qInterface::read);
	cNavigatorWindow *navigator = new cNavigatorWindow();
	cDockPatternLines *leftWidget = new cDockPatternLines();
	navigator->AddLeftWidget(leftWidget);
	navigator->setAttribute(Qt::WA_DeleteOnClose);
	navigator->SetInitialParameters(params, fractalParams);
	navigator->SynchronizeInterface(qInterface::write);
	navigator->SetMouseClickFunction(gMainInterface->GetMouseClickFunction());

	connect(navigator, &cNavigatorWindow::signalChangesAccepted, this,
		&cDockPatternLines::slotNewParametersFromNavi);

	navigator->show();
	navigator->AllPrepared();
}

void cDockPatternLines::slotNewParametersFromNavi() {}

void cDockPatternLines::slotPressedButtonPlacePatternLineTrapAtTarget()
{
	CHECK_MAIN_INTERFACE();
	QPushButton *button = qobject_cast<QPushButton *>(sender());
	if (!button) return;

	QRegularExpression re("pattern_line_trap_(\\d+)_place_target");
	QRegularExpressionMatch match = re.match(button->objectName());
	if (!match.hasMatch()) return;

	const int layerNum = match.captured(1).toInt();
	SynchronizeInterfaceWindow(this, params, qInterface::read);
	EnsurePatternLineTrapsMasterAndLayer(layerNum);

	const CVector3 camera = params->Get<CVector3>("camera");
	const CVector3 target = params->Get<CVector3>("target");
	CVector3 toCam = camera - target;
	const double len = toCam.Length();
	const double bump = PatternLineTrapBumpFromView(layerNum);

	CVector3 placedWorld = target;
	if (len > 1e-20)
	{
		toCam.Normalize();
		const double move = std::min(bump, len * 0.42);
		placedWorld = target + toCam * move;
	}

	const QString p = QString("pattern_line_trap_%1").arg(layerNum);
	params->Set(p + "_position", placedWorld);

	if (QWidget *fw = QApplication::focusWidget()) fw->clearFocus();
	SynchronizeInterfaceWindow(this, params, qInterface::write);
	gMainInterface->RequestRender(QStringLiteral("pattern lines"), 120, true);
}

void cDockPatternLines::slotPressedButtonPlacePatternLineTrapAtSurface()
{
	CHECK_MAIN_INTERFACE();
	QPushButton *button = qobject_cast<QPushButton *>(sender());
	if (!button) return;

	QRegularExpression re("pattern_line_trap_(\\d+)_place_surface");
	QRegularExpressionMatch match = re.match(button->objectName());
	if (!match.hasMatch()) return;

	const int layerNum = match.captured(1).toInt();
	SynchronizeInterfaceWindow(this, params, qInterface::read);
	EnsurePatternLineTrapsMasterAndLayer(layerNum);

	const CVector3 camera = params->Get<CVector3>("camera");
	const CVector3 target = params->Get<CVector3>("target");
	CVector3 direction = target - camera;
	const double camTargetLen = direction.Length();
	if (camTargetLen < 1e-20)
		direction = CVector3(0.0, 0.0, 1.0);
	else
		direction.Normalize();

	CVector3 point;
	RaymarchFirstSurface(camera, direction, &point);

	const double bump = PatternLineTrapBumpFromView(layerNum);

	const double rayFromCam = (point - camera).Length();
	const double back = std::min(bump, std::max(0.0, rayFromCam - 0.02) * 0.92);
	const CVector3 placedWorld = point - direction * back;

	const QString p = QString("pattern_line_trap_%1").arg(layerNum);
	params->Set(p + "_position", placedWorld);

	if (QWidget *fw = QApplication::focusWidget()) fw->clearFocus();
	SynchronizeInterfaceWindow(this, params, qInterface::write);
	gMainInterface->RequestRender(QStringLiteral("pattern lines"), 120, true);
}

void cDockPatternLines::slotPressedButtonPatternLineTrapsQuickTest()
{
	CHECK_MAIN_INTERFACE();
	std::shared_ptr<cParameterContainer> targetPar = params ? params : gPar;
	SynchronizeInterfaceWindow(this, targetPar, qInterface::read);
	const int layerNum = 1;
	EnsurePatternLineTrapsMasterAndLayer(layerNum);
	const QString p = QString("pattern_line_trap_%1").arg(layerNum);
	targetPar->Set(p + "_radius", 0.035);
	targetPar->Set(p + "_thickness", 1.0);
	targetPar->Set(p + "_scale", 1.0);
	targetPar->Set(p + "_relative_thickness", 1.0);
	targetPar->Set(p + "_edge_softness", 0.0);
	targetPar->Set(p + "_max_distance", 0.12);
	targetPar->Set(p + "_falloff_sharpness", 22.0);
	targetPar->Set(p + "_segment_half_length", 0.0);
	targetPar->Set(p + "_intensity", 4.0);
	targetPar->Set(p + "_rotation", CVector3(0.0, 0.0, 0.0));
	targetPar->Set(p + "_color", sRGB(65535, 8192, 8192));
	targetPar->Set(p + "_color_2", sRGB(8192, 65535, 8192));
	targetPar->Set(p + "_color_3", sRGB(8192, 8192, 65535));

	const CVector3 camera = targetPar->Get<CVector3>("camera");
	const CVector3 target = targetPar->Get<CVector3>("target");
	CVector3 toCam = camera - target;
	const double len = toCam.Length();
	const double bump = PatternLineTrapBumpFromView(layerNum);
	CVector3 placedWorld = target;
	if (len > 1e-20)
	{
		toCam.Normalize();
		const double move = std::min(bump, len * 0.42);
		placedWorld = target + toCam * move;
	}
	targetPar->Set(p + "_position", placedWorld);

	if (QWidget *fw = QApplication::focusWidget()) fw->clearFocus();
	SynchronizeInterfaceWindow(this, targetPar, qInterface::write);
	gMainInterface->RequestRender(QStringLiteral("pattern lines"), 120, true);
}

void cDockPatternLines::slotEnableAllPatternLineTraps()
{
	CHECK_MAIN_INTERFACE();
	if (!params) return;
	SynchronizeInterfaceWindow(this, params, qInterface::read);
	for (int i = 1; i <= PATTERN_LINE_TRAP_COUNT; i++)
		params->Set(QString("pattern_line_trap_%1_enabled").arg(i), true);
	SynchronizeInterfaceWindow(this, params, qInterface::write);
	gMainInterface->RequestRender(QStringLiteral("pattern lines"), 120, true);
}

void cDockPatternLines::slotDisableAllPatternLineTraps()
{
	CHECK_MAIN_INTERFACE();
	if (!params) return;
	SynchronizeInterfaceWindow(this, params, qInterface::read);
	for (int i = 1; i <= PATTERN_LINE_TRAP_COUNT; i++)
		params->Set(QString("pattern_line_trap_%1_enabled").arg(i), false);
	SynchronizeInterfaceWindow(this, params, qInterface::write);
	gMainInterface->RequestRender(QStringLiteral("pattern lines"), 120, true);
}

void cDockPatternLines::slotSoloSelectedPatternLineTrap()
{
	CHECK_MAIN_INTERFACE();
	if (!params) return;
	const int soloLayer = TRAPS_UI->spinboxInt_pattern_line_trap_solo_layer
		? TRAPS_UI->spinboxInt_pattern_line_trap_solo_layer->value()
		: 1;
	SynchronizeInterfaceWindow(this, params, qInterface::read);
	for (int i = 1; i <= PATTERN_LINE_TRAP_COUNT; i++)
		params->Set(QString("pattern_line_trap_%1_enabled").arg(i), (i == soloLayer));
	SynchronizeInterfaceWindow(this, params, qInterface::write);
	gMainInterface->RequestRender(QStringLiteral("pattern lines"), 120, true);
}

void cDockPatternLines::slotResetPatternLineTraps()
{
	CHECK_MAIN_INTERFACE();
	if (!params) return;
	SynchronizeInterfaceWindow(this, params, qInterface::read);
	const QStringList paramNames = patternLineTrapPresetMainParameterNames();
	for (const QString &fullName : paramNames)
	{
		const int firstUnderscore = fullName.indexOf('_');
		const QString containerName = fullName.left(firstUnderscore);
		const QString parameterName = fullName.mid(firstUnderscore + 1);
		if (containerName != QStringLiteral("main")) continue;
		cOneParameter oneParam = params->GetAsOneParameter(parameterName);
		oneParam.SetMultiVal(oneParam.GetMultiVal(valueDefault), valueActual);
		params->SetFromOneParameter(parameterName, oneParam);
	}
	SynchronizeInterfaceWindow(this, params, qInterface::write);
	if (renderedImageWidget)
		renderedImageWidget->SetPatternLineTrapsVisibility(
			TRAPS_UI->checkBox_pattern_line_traps_overlay_visible
				? TRAPS_UI->checkBox_pattern_line_traps_overlay_visible->isChecked()
				: true);
	gMainInterface->RequestRender(QStringLiteral("pattern lines"), 120, true);
}

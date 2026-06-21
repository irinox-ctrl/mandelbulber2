/**
 * Mandelbulber v2 — pattern line traps scroll panel (split from dock_pattern_lines.ui)
 */

#ifndef MANDELBULBER2_QT_PATTERN_LINES_TRAPS_PANEL_H_
#define MANDELBULBER2_QT_PATTERN_LINES_TRAPS_PANEL_H_

#include <QWidget>

#include "ui_pattern_lines_traps_panel.h"

class cPatternLinesTrapsPanel : public QWidget
{
	Q_OBJECT

public:
	explicit cPatternLinesTrapsPanel(QWidget *parent = nullptr);
	~cPatternLinesTrapsPanel() override;

	Ui::cPatternLinesTrapsPanel *trapsUi() const { return ui; }

private:
	Ui::cPatternLinesTrapsPanel *ui;
};

#endif // MANDELBULBER2_QT_PATTERN_LINES_TRAPS_PANEL_H_

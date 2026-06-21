/**
 * Mandelbulber v2 — mutation tail systems sub-panel (md, as, sm, blockify, tile)
 */

#ifndef MANDELBULBER2_QT_MUTATION_TAIL_PANEL_H_
#define MANDELBULBER2_QT_MUTATION_TAIL_PANEL_H_

#include <QWidget>

#include "ui_mutation_tail_panel.h"

class cMutationTailPanel : public QWidget
{
	Q_OBJECT

public:
	explicit cMutationTailPanel(QWidget *parent = nullptr);
	~cMutationTailPanel() override;

	Ui::cMutationTailPanel *tailUi() const { return ui; }

private:
	Ui::cMutationTailPanel *ui;
};

#endif // MANDELBULBER2_QT_MUTATION_TAIL_PANEL_H_

/**
 * Mandelbulber v2 — mutation Jos Leys + PK DE sub-panel (split from dock_mutation_tab.ui)
 */

#ifndef MANDELBULBER2_QT_MUTATION_JOS_PK_PANEL_H_
#define MANDELBULBER2_QT_MUTATION_JOS_PK_PANEL_H_

#include <QWidget>

#include "ui_mutation_jos_pk_panel.h"

class cMutationJosPkPanel : public QWidget
{
	Q_OBJECT

public:
	explicit cMutationJosPkPanel(QWidget *parent = nullptr);
	~cMutationJosPkPanel() override;

	Ui::cMutationJosPkPanel *josPkUi() const { return ui; }

private:
	Ui::cMutationJosPkPanel *ui;
};

#endif // MANDELBULBER2_QT_MUTATION_JOS_PK_PANEL_H_

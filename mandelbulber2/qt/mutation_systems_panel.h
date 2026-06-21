/**
 * Mandelbulber v2 — mutation systems container (3 sub-groups)
 */

#ifndef MANDELBULBER2_QT_MUTATION_SYSTEMS_PANEL_H_
#define MANDELBULBER2_QT_MUTATION_SYSTEMS_PANEL_H_

#include <QWidget>

#include "ui_mutation_systems_panel.h"

class cMutationSystemsGroup1;
class cMutationSystemsGroup2;
class cMutationSystemsGroup3;

class cMutationSystemsPanel : public QWidget
{
	Q_OBJECT

public:
	explicit cMutationSystemsPanel(QWidget *parent = nullptr);
	~cMutationSystemsPanel() override;

	Ui::cMutationSystemsGroup1 *group1Ui() const;
	Ui::cMutationSystemsGroup2 *group2Ui() const;
	Ui::cMutationSystemsGroup3 *group3Ui() const;

private:
	Ui::cMutationSystemsPanel *ui;
};

#endif // MANDELBULBER2_QT_MUTATION_SYSTEMS_PANEL_H_

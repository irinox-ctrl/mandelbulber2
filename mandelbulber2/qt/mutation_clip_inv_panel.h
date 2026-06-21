/**
 * Mandelbulber v2 — mutation clip + inversion sub-panel (split from dock_mutation_tab.ui)
 */

#ifndef MANDELBULBER2_QT_MUTATION_CLIP_INV_PANEL_H_
#define MANDELBULBER2_QT_MUTATION_CLIP_INV_PANEL_H_

#include <QWidget>

#include "ui_mutation_clip_inv_panel.h"

class cMutationClipInvPanel : public QWidget
{
	Q_OBJECT

public:
	explicit cMutationClipInvPanel(QWidget *parent = nullptr);
	~cMutationClipInvPanel() override;

	Ui::cMutationClipInvPanel *clipInvUi() const { return ui; }

private:
	Ui::cMutationClipInvPanel *ui;
};

#endif // MANDELBULBER2_QT_MUTATION_CLIP_INV_PANEL_H_

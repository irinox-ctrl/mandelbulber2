/**
 * Mandelbulber v2 — material editor scroll panel (split from material_editor.ui)
 */

#ifndef MANDELBULBER2_QT_MATERIAL_EDITOR_PANEL_H_
#define MANDELBULBER2_QT_MATERIAL_EDITOR_PANEL_H_

#include <QWidget>

#include "ui_material_editor_panel.h"

class cMaterialEditorPanel : public QWidget
{
	Q_OBJECT

public:
	explicit cMaterialEditorPanel(QWidget *parent = nullptr);
	~cMaterialEditorPanel() override;

	Ui::cMaterialEditorPanel *materialPanelUi() const { return ui; }

private:
	Ui::cMaterialEditorPanel *ui;
};

#endif // MANDELBULBER2_QT_MATERIAL_EDITOR_PANEL_H_

#ifndef MANDELBULBER2_QT_CRENDERINGNEBULATAB_H_
#define MANDELBULBER2_QT_CRENDERINGNEBULATAB_H_
#include <QWidget>
#include "ui_rendering_nebula_tab.h"
class cRenderingNebulaTab : public QWidget {
	Q_OBJECT
public:
	explicit cRenderingNebulaTab(QWidget *parent = nullptr);
	~cRenderingNebulaTab() override;
	Ui::cRenderingNebulaTab *nebulaUi() const { return ui; }
private:
	Ui::cRenderingNebulaTab *ui;
};
#endif

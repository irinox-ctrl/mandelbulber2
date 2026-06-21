#ifndef MANDELBULBER2_QT_CRENDERINGNETRENDERTAB_H_
#define MANDELBULBER2_QT_CRENDERINGNETRENDERTAB_H_
#include <QWidget>
#include "ui_rendering_netrender_tab.h"
class cRenderingNetrenderTab : public QWidget {
	Q_OBJECT
public:
	explicit cRenderingNetrenderTab(QWidget *parent = nullptr);
	~cRenderingNetrenderTab() override;
	Ui::cRenderingNetrenderTab *netrenderUi() const { return ui; }
private:
	Ui::cRenderingNetrenderTab *ui;
};
#endif

#ifndef MANDELBULBER2_QT_CRENDERINGLIMITSTAB_H_
#define MANDELBULBER2_QT_CRENDERINGLIMITSTAB_H_
#include <QWidget>
#include "ui_rendering_limits_tab.h"
class cRenderingLimitsTab : public QWidget {
	Q_OBJECT
public:
	explicit cRenderingLimitsTab(QWidget *parent = nullptr);
	~cRenderingLimitsTab() override;
	Ui::cRenderingLimitsTab *limitsUi() const { return ui; }
private:
	Ui::cRenderingLimitsTab *ui;
};
#endif

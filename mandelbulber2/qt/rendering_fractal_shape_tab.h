#ifndef MANDELBULBER2_QT_CRENDERINGFRACTALSHAPETAB_H_
#define MANDELBULBER2_QT_CRENDERINGFRACTALSHAPETAB_H_
#include <QWidget>
#include "ui_rendering_fractal_shape_tab.h"
class cRenderingFractalShapeTab : public QWidget {
	Q_OBJECT
public:
	explicit cRenderingFractalShapeTab(QWidget *parent = nullptr);
	~cRenderingFractalShapeTab() override;
	Ui::cRenderingFractalShapeTab *fractalShapeUi() const { return ui; }
private:
	Ui::cRenderingFractalShapeTab *ui;
};
#endif

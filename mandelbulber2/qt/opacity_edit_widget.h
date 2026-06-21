/**
 * Mandelbulber v2, a 3D fractal generator
 *
 * opacity_edit_widget.h
 *
 * Standalone opacity gradient editor widget (Photoshop-style)
 */

#ifndef MANDELBULBER2_QT_OPACITY_EDIT_WIDGET_H_
#define MANDELBULBER2_QT_OPACITY_EDIT_WIDGET_H_

#include <QWidget>
#include "src/color_gradient.h"

class cOpacityEditWidget : public QWidget
{
	Q_OBJECT
public:
	cOpacityEditWidget(QWidget *parent = nullptr);
	void AttachGradient(cColorGradient *grad);
	void SetMargins(int m) { margins = m; }

protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void contextMenuEvent(QContextMenuEvent *event) override;

private:
	void PaintOpacityStop(const cColorGradient::sOpacityStop &stop, int index, QPainter &painter);
	void PaintOpacityMidpointHandle(int segmentIndex, QPainter &painter);
	void PaintOpacityCurve(QPainter &painter);
	int CalcButtonPosition(float position);
	int CalcOpacityMidpointPosition(int segmentIndex);
	int FindOpacityStopAtPosition(int x);
	int FindOpacityMidpointAtPosition(int x, int y);

	cColorGradient *gradient;
	int buttonWidth;
	int margins;
	bool isDraggingOpacityStop;
	bool isDraggingOpacityValue;
	bool isDraggingOpacityMidpoint;
	int pressedOpacityIndex;
	int pressedMidpointIndex;
	int dragStartX;
	int dragStartY;

signals:
	void valueChanged();
};

#endif /* MANDELBULBER2_QT_OPACITY_EDIT_WIDGET_H_ */

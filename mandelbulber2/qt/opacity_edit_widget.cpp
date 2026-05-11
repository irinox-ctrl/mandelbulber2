/**
 * Mandelbulber v2, a 3D fractal generator
 *
 * opacity_edit_widget.cpp
 */

#include "opacity_edit_widget.h"
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include <QDebug>

cOpacityEditWidget::cOpacityEditWidget(QWidget *parent) : QWidget(parent)
{
	gradient = nullptr;
	buttonWidth = 10;
	margins = 10;
	isDraggingOpacityStop = false;
	isDraggingOpacityValue = false;
	isDraggingOpacityMidpoint = false;
	pressedOpacityIndex = -1;
	pressedMidpointIndex = -1;
	dragStartX = 0;
	dragStartY = 0;
	setMouseTracking(true);
}

void cOpacityEditWidget::AttachGradient(cColorGradient *grad)
{
	gradient = grad;
	update();
}

int cOpacityEditWidget::CalcButtonPosition(float position)
{
	return int(margins + position * (width() - 2 * margins));
}

int cOpacityEditWidget::CalcOpacityMidpointPosition(int segmentIndex)
{
	if (!gradient) return 0;
	QList<cColorGradient::sOpacityStop> stops = gradient->GetListOfSortedOpacityStops();
	const cColorGradient::sOpacityStop &stop1 = stops[segmentIndex];
	const cColorGradient::sOpacityStop &stop2 = stops[segmentIndex + 1];
	float mid = stop1.midpoint;
	float pos = stop1.position + (stop2.position - stop1.position) * mid;
	return CalcButtonPosition(pos);
}

void cOpacityEditWidget::PaintOpacityCurve(QPainter &painter)
{
	if (!gradient || gradient->GetNumberOfOpacityStops() < 2) return;

	int w = width() - 2 * margins;
	int h = height() - buttonWidth;
	int top = buttonWidth / 2;

	// Checkerboard background
	int checkSize = 4;
	for (int y = top; y < top + h; y += checkSize)
	{
		for (int x = margins; x < margins + w; x += checkSize)
		{
			bool dark = ((x / checkSize) + (y / checkSize)) % 2 == 0;
			painter.fillRect(x, y, checkSize, checkSize, dark ? QColor(180, 180, 180) : QColor(220, 220, 220));
		}
	}

	// Build opacity curve polygon
	QPolygonF poly;
	poly.append(QPointF(margins, top + h));

	for (int x = 0; x <= w; x += 2)
	{
		float pos = float(x) / w;
		float opacity = gradient->GetOpacity(pos, false);
		poly.append(QPointF(margins + x, top + h - opacity * h));
	}

	poly.append(QPointF(margins + w, top + h));

	// Fill curve
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(0, 0, 0));
	painter.drawPolygon(poly);

	// Draw outline
	painter.setPen(QPen(QColor(120, 120, 120), 1));
	painter.setBrush(Qt::NoBrush);
	QPainterPath path;
	path.moveTo(margins, top + h);
	for (int x = 0; x <= w; x += 2)
	{
		float pos = float(x) / w;
		float opacity = gradient->GetOpacity(pos, false);
		path.lineTo(margins + x, top + h - opacity * h);
	}
	path.lineTo(margins + w, top + h);
	painter.drawPath(path);
}

void cOpacityEditWidget::PaintOpacityStop(const cColorGradient::sOpacityStop &stop, int index, QPainter &painter)
{
	int x = CalcButtonPosition(stop.position);
	int top = 0;
	int bw = buttonWidth;

	bool selected = (pressedOpacityIndex == index);

	// Draw stop handle (vertical bar with triangle on top)
	painter.setPen(QPen(selected ? QColor(255, 200, 0) : QColor(0, 0, 0), 1));
	painter.setBrush(QColor(200, 200, 200));

	// Triangle top
	QPolygonF triangle;
	triangle.append(QPointF(x, top));
	triangle.append(QPointF(x - bw / 2, top + bw));
	triangle.append(QPointF(x + bw / 2, top + bw));
	painter.drawPolygon(triangle);

	// Vertical line
	painter.drawLine(x, top + bw, x, height());

	// Opacity value text
	QString text = QString::number(int(stop.opacity * 100));
	painter.setPen(QColor(0, 0, 0));
	painter.drawText(x - 10, top + bw + 2, 20, 12, Qt::AlignCenter, text);
}

void cOpacityEditWidget::PaintOpacityMidpointHandle(int segmentIndex, QPainter &painter)
{
	int x = CalcOpacityMidpointPosition(segmentIndex);
	int y = buttonWidth / 2;
	int s = buttonWidth / 2;

	painter.setPen(QPen(QColor(0, 0, 0), 1));
	painter.setBrush(QColor(200, 200, 200));

	QPolygonF diamond;
	diamond.append(QPointF(x, y - s));
	diamond.append(QPointF(x + s, y));
	diamond.append(QPointF(x, y + s));
	diamond.append(QPointF(x - s, y));
	painter.drawPolygon(diamond);
}

void cOpacityEditWidget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	PaintOpacityCurve(painter);

	if (gradient)
	{
		for (int i = 0; i < gradient->GetNumberOfOpacityStops() - 1; i++)
		{
			PaintOpacityMidpointHandle(i, painter);
		}

		QList<cColorGradient::sOpacityStop> stops = gradient->GetListOfOpacityStops();
		for (int i = 0; i < stops.size(); i++)
		{
			PaintOpacityStop(stops[i], i, painter);
		}
	}
}

int cOpacityEditWidget::FindOpacityStopAtPosition(int x)
{
	if (!gradient) return -1;
	QList<cColorGradient::sOpacityStop> stops = gradient->GetListOfOpacityStops();
	for (int i = 0; i < stops.size(); i++)
	{
		int bx = CalcButtonPosition(stops[i].position);
		if (abs(x - bx) < buttonWidth) return i;
	}
	return -1;
}

int cOpacityEditWidget::FindOpacityMidpointAtPosition(int x, int y)
{
	if (!gradient) return -1;
	for (int i = 0; i < gradient->GetNumberOfOpacityStops() - 1; i++)
	{
		int mx = CalcOpacityMidpointPosition(i);
		int my = buttonWidth / 2;
		if (abs(x - mx) < buttonWidth / 2 && abs(y - my) < buttonWidth / 2) return i;
	}
	return -1;
}

void cOpacityEditWidget::mousePressEvent(QMouseEvent *event)
{
	if (!gradient) return;

	int midpointIndex = FindOpacityMidpointAtPosition(event->x(), event->y());
	if (midpointIndex >= 0)
	{
		pressedMidpointIndex = midpointIndex;
		isDraggingOpacityMidpoint = true;
		dragStartX = event->x();
		update();
		return;
	}

	int stopIndex = FindOpacityStopAtPosition(event->x());
	if (stopIndex >= 0)
	{
		pressedOpacityIndex = stopIndex;
		dragStartX = event->x();
		dragStartY = event->y();
		update();
	}
}

void cOpacityEditWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (!gradient) return;

	if (pressedOpacityIndex >= 0)
	{
		int dx = event->x() - dragStartX;
		int dy = event->y() - dragStartY;

		if (!isDraggingOpacityStop && !isDraggingOpacityValue)
		{
			if (abs(dx) > 3 || abs(dy) > 3)
			{
				if (abs(dy) > abs(dx))
					isDraggingOpacityValue = true;
				else
					isDraggingOpacityStop = true;
			}
		}

		if (isDraggingOpacityStop)
		{
			float newPos = float(event->x() - margins) / (width() - 2 * margins);
			newPos = qBound(0.0f, newPos, 1.0f);
			gradient->ModifyOpacityStopPosition(pressedOpacityIndex, newPos);
			dragStartX = event->x();
			emit valueChanged();
			update();
		}
		else if (isDraggingOpacityValue)
		{
			float deltaY = float(dragStartY - event->y()) / height();
			QList<cColorGradient::sOpacityStop> stops = gradient->GetListOfOpacityStops();
			float newOpacity = stops[pressedOpacityIndex].opacity + deltaY;
			newOpacity = qBound(0.0f, newOpacity, 1.0f);
			gradient->ModifyOpacityStopOpacity(pressedOpacityIndex, newOpacity);
			dragStartY = event->y();
			emit valueChanged();
			update();
		}
	}
	else if (isDraggingOpacityMidpoint && pressedMidpointIndex >= 0)
	{
		QList<cColorGradient::sOpacityStop> stops = gradient->GetListOfSortedOpacityStops();
		const cColorGradient::sOpacityStop &stop1 = stops[pressedMidpointIndex];
		const cColorGradient::sOpacityStop &stop2 = stops[pressedMidpointIndex + 1];
		float segStart = stop1.position;
		float segEnd = stop2.position;
		if (segEnd > segStart)
		{
			float newMid = float(event->x() - margins) / (width() - 2 * margins);
			newMid = (newMid - segStart) / (segEnd - segStart);
			newMid = qBound(0.0f, newMid, 1.0f);
			gradient->SetOpacityMidpoint(pressedMidpointIndex, newMid);
			emit valueChanged();
			update();
		}
	}
}

void cOpacityEditWidget::mouseReleaseEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	isDraggingOpacityStop = false;
	isDraggingOpacityValue = false;
	isDraggingOpacityMidpoint = false;
	pressedOpacityIndex = -1;
	pressedMidpointIndex = -1;
	update();
}

void cOpacityEditWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (!gradient) return;
	float pos = float(event->x() - margins) / (width() - 2 * margins);
	pos = qBound(0.0f, pos, 1.0f);
	float opacity = gradient->GetOpacity(pos, false);
	gradient->AddOpacityStop(pos, opacity);
	emit valueChanged();
	update();
}

void cOpacityEditWidget::contextMenuEvent(QContextMenuEvent *event)
{
	if (!gradient) return;

	QMenu menu(this);
	QAction *addAction = menu.addAction("Add opacity stop");
	QAction *removeAction = nullptr;

	int stopIndex = FindOpacityStopAtPosition(event->x());
	if (stopIndex >= 0 && gradient->GetNumberOfOpacityStops() > 2)
	{
		removeAction = menu.addAction("Remove opacity stop");
	}

	QAction *selected = menu.exec(event->globalPos());
	if (selected == addAction)
	{
		float pos = float(event->x() - margins) / (width() - 2 * margins);
		pos = qBound(0.0f, pos, 1.0f);
		float opacity = gradient->GetOpacity(pos, false);
		gradient->AddOpacityStop(pos, opacity);
		emit valueChanged();
		update();
	}
	else if (removeAction && selected == removeAction)
	{
		gradient->RemoveOpacityStop(stopIndex);
		emit valueChanged();
		update();
	}
}

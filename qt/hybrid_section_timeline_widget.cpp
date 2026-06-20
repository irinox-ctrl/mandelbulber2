#include "hybrid_section_timeline_widget.h"

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QToolTip>

#include "src/fractal_enums.h"

namespace
{
constexpr int kLabelWidth = 96;
constexpr int kRulerHeight = 22;
constexpr int kRowHeight = 18;
constexpr int kSeqRowHeight = 14;
constexpr int kBottomPad = 6;
constexpr int kRightPad = 8;
constexpr int kHandlePixels = 6;
constexpr int kMaxIter = 99999;

QColor SlotColor(int slot)
{
	return QColor::fromHsv((slot * 37) % 360, 180, 220);
}

int ClampIter(int iter)
{
	return qBound(0, iter, kMaxIter);
}
} // namespace

cHybridSectionTimelineWidget::cHybridSectionTimelineWidget(QWidget *parent) : QWidget(parent)
{
	setMinimumHeight(kRulerHeight + NUMBER_OF_FRACTALS * kRowHeight + kSeqRowHeight + kBottomPad + 4);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setMouseTracking(true);
}

void cHybridSectionTimelineWidget::SetSections(
	const QVector<sSectionInfo> &newSections, int newGlobalN, int newViewMaxIter)
{
	sections = newSections;
	globalN = qMax(1, newGlobalN);
	viewMaxIter = qMax(globalN, qMax(1, newViewMaxIter));
	if (hybridSequence.size() != viewMaxIter + 1)
		hybridSequence.resize(viewMaxIter + 1);
	update();
}

void cHybridSectionTimelineWidget::SetHybridSequence(const QVector<int> &sequence)
{
	hybridSequence = sequence;
	update();
}

QString cHybridSectionTimelineWidget::SequenceStatusAt(int iter) const
{
	if (iter < 0 || iter >= hybridSequence.size()) return QString();

	int activeCount = 0;
	int activeSlot = -1;
	for (const sSectionInfo &sec : sections)
	{
		if (!sec.enabled) continue;
		const int lo = qMin(sec.startIter, sec.stopIter);
		const int hi = qMax(sec.startIter, sec.stopIter);
		if (iter >= lo && iter <= hi)
		{
			activeCount++;
			activeSlot = sec.slot;
		}
	}

	const int seqSlot = (iter >= 0 && iter < hybridSequence.size()) ? hybridSequence[iter] : -1;
	QString status;
	if (seqSlot >= 0)
		status = tr("Sequence at i=%1: slot #%2").arg(iter).arg(seqSlot + 1);
	else
		status = tr("Sequence at i=%1: gap (no formula)").arg(iter);

	if (activeCount == 0)
		status += tr(" — no section covers this iteration");
	else if (activeCount > 1)
		status += tr(" — %1 sections overlap here").arg(activeCount);
	else if (activeSlot != seqSlot + 1 && seqSlot >= 0)
		status += tr(" — range covers slot #%1").arg(activeSlot);

	return status;
}

void cHybridSectionTimelineWidget::SetPlayheadIteration(int iter)
{
	playheadIter = ClampIter(iter);
	update();
}

QSize cHybridSectionTimelineWidget::sizeHint() const
{
	return QSize(360, kRulerHeight + NUMBER_OF_FRACTALS * kRowHeight + kSeqRowHeight + kBottomPad + 4);
}

QSize cHybridSectionTimelineWidget::minimumSizeHint() const
{
	return sizeHint();
}

cHybridSectionTimelineWidget::sChartGeom cHybridSectionTimelineWidget::ChartGeom() const
{
	sChartGeom g;
	g.chartLeft = kLabelWidth;
	g.chartWidth = qMax(20, width() - kLabelWidth - kRightPad);
	return g;
}

double cHybridSectionTimelineWidget::IterToX(int iter, const sChartGeom &g) const
{
	return g.chartLeft + (double(ClampIter(iter)) / double(viewMaxIter)) * g.chartWidth;
}

int cHybridSectionTimelineWidget::XToIter(int x, const sChartGeom &g) const
{
	const double t = qBound(0.0, double(x - g.chartLeft) / double(g.chartWidth), 1.0);
	return ClampIter(int(t * viewMaxIter + 0.5));
}

int cHybridSectionTimelineWidget::RowAtY(int y) const
{
	const int rowTop = kRulerHeight;
	if (y < rowTop) return -1;
	const int row = (y - rowTop) / kRowHeight;
	if (row < 0 || row >= sections.size()) return -1;
	return row;
}

QRect cHybridSectionTimelineWidget::BarRect(int row, const sChartGeom &g) const
{
	if (row < 0 || row >= sections.size()) return QRect();

	const sSectionInfo &sec = sections[row];
	const int start = qMin(sec.startIter, sec.stopIter);
	const int stop = qMax(sec.startIter, sec.stopIter);
	int x1 = int(IterToX(start, g));
	int x2 = int(IterToX(stop, g));
	if (x2 < x1) qSwap(x1, x2);
	x2 = qMax(x2, x1 + 2);

	const int y = kRulerHeight + row * kRowHeight;
	return QRect(x1, y + 3, x2 - x1, kRowHeight - 6);
}

cHybridSectionTimelineWidget::sHitResult cHybridSectionTimelineWidget::HitTest(const QPoint &pos) const
{
	sHitResult hit;
	const sChartGeom g = ChartGeom();

	if (pos.x() < g.chartLeft) return hit;

	const int row = RowAtY(pos.y());
	if (row < 0 || row >= sections.size())
	{
		if (pos.y() < kRulerHeight) hit.type = hitRuler;
		return hit;
	}

	if (!sections[row].enabled) return hit;

	const QRect bar = BarRect(row, g);
	if (!bar.contains(pos))
	{
		if (pos.y() < kRulerHeight) hit.type = hitRuler;
		return hit;
	}

	hit.row = row;
	const int distStart = abs(pos.x() - bar.left());
	const int distStop = abs(pos.x() - bar.right());

	if (distStart <= kHandlePixels)
		hit.type = hitBarStart;
	else if (distStop <= kHandlePixels)
		hit.type = hitBarStop;
	else
		hit.type = hitBarMove;

	return hit;
}

int cHybridSectionTimelineWidget::SlotAtIteration(int iter) const
{
	for (const sSectionInfo &sec : sections)
	{
		if (!sec.enabled) continue;
		const int lo = qMin(sec.startIter, sec.stopIter);
		const int hi = qMax(sec.startIter, sec.stopIter);
		if (iter >= lo && iter <= hi) return sec.slot;
	}
	return -1;
}

QString cHybridSectionTimelineWidget::BuildRowTooltip(
	const sSectionInfo &sec, const sHitResult &hit, int iterAtCursor) const
{
	QString tip = tr("Slot #%1: %2\nIterations: %3 – %4\nWeight: %5")
		.arg(sec.slot)
		.arg(sec.name.isEmpty() ? tr("(none)") : sec.name)
		.arg(sec.startIter)
		.arg(sec.stopIter)
		.arg(sec.weight, 0, 'f', 3);
	if (sec.fadeIn > 0 || sec.fadeOut > 0)
		tip += tr("\nFade in: %1, Fade out: %2").arg(sec.fadeIn).arg(sec.fadeOut);
	if (!sec.enabled) tip += tr("\n(disabled)");
	if (sec.startIter > sec.stopIter) tip += tr("\n⚠ start > stop");

	tip += tr("\n—");
	tip += tr("\nDouble-click: open formula tab");
	if (hit.type == hitBarStart || hit.type == hitBarStop)
		tip += tr("\nDrag edge: resize range");
	else if (hit.type == hitBarMove)
		tip += tr("\nDrag: move range");
	else if (hit.type != hitNone)
		tip += tr("\nClick: playhead at iteration %1").arg(iterAtCursor);
	tip += tr("\nShift+drag bar: copy range + weight/fade to another slot");
	if (playheadIter >= 0)
	{
		const QString seqStatus = SequenceStatusAt(playheadIter);
		if (!seqStatus.isEmpty()) tip += "\n" + seqStatus;
	}
	return tip;
}

void cHybridSectionTimelineWidget::UpdateHoverCursor(const QPoint &pos)
{
	const sHitResult hit = HitTest(pos);
	switch (hit.type)
	{
		case hitBarStart:
		case hitBarStop:
			setCursor(Qt::SizeHorCursor);
			break;
		case hitBarMove:
		case hitBarDuplicate:
			setCursor(Qt::OpenHandCursor);
			break;
		case hitRuler:
			setCursor(Qt::CrossCursor);
			break;
		default:
			unsetCursor();
			break;
	}
}

void cHybridSectionTimelineWidget::paintEvent(QPaintEvent * /*event*/)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	const QColor textColor = palette().color(QPalette::WindowText);
	const QColor gridColor = palette().color(QPalette::Mid);
	const QColor bgColor = palette().color(QPalette::Base);
	const sChartGeom g = ChartGeom();

	painter.fillRect(rect(), palette().color(QPalette::Window));

	painter.setPen(textColor);
	QFont smallFont = font();
	smallFont.setPixelSize(10);
	painter.setFont(smallFont);
	painter.drawText(4, 14, tr("Iteration"));

	const int tickCount = 5;
	for (int t = 0; t <= tickCount; t++)
	{
		const int iter = (viewMaxIter * t) / tickCount;
		const int x = int(IterToX(iter, g));
		painter.setPen(gridColor);
		painter.drawLine(x, kRulerHeight - 4, x, height() - kBottomPad);
		painter.setPen(textColor);
		painter.drawText(x - 12, 14, QString::number(iter));
	}

	const int nX = int(IterToX(globalN, g));
	QPen nPen(QColor(255, 180, 60));
	nPen.setStyle(Qt::DashLine);
	painter.setPen(nPen);
	painter.drawLine(nX, kRulerHeight - 6, nX, height() - kBottomPad);
	painter.setPen(textColor);
	painter.drawText(nX + 2, height() - 2, tr("N=%1").arg(globalN));

	const int seqRowY = kRulerHeight + sections.size() * kRowHeight;
	painter.setPen(textColor);
	painter.drawText(4, seqRowY + 11, tr("Seq"));

	if (!hybridSequence.isEmpty())
	{
		const int seqLen = qMin(hybridSequence.size(), viewMaxIter + 1);
		for (int i = 0; i < seqLen;)
		{
			const int slot = hybridSequence[i];
			int j = i + 1;
			while (j < seqLen && hybridSequence[j] == slot) j++;
			const int x1 = int(IterToX(i, g));
			const int x2 = int(IterToX(j, g));
			QRect segRect(x1, seqRowY + 2, qMax(2, x2 - x1), kSeqRowHeight - 4);
			if (slot >= 0 && slot < NUMBER_OF_FRACTALS)
			{
				QColor c = SlotColor(slot);
				c.setAlpha(220);
				painter.fillRect(segRect, c);
			}
			else
				painter.fillRect(segRect, QColor(180, 60, 60, 160));
			painter.setPen(gridColor);
			painter.drawRect(segRect);
			i = j;
		}
	}

	if (playheadIter >= 0)
	{
		const int pX = int(IterToX(playheadIter, g));
		QPen playPen(QColor(100, 200, 255));
		playPen.setWidth(2);
		painter.setPen(playPen);
		painter.drawLine(pX, kRulerHeight - 8, pX, height() - kBottomPad);
		painter.setPen(textColor);
		painter.drawText(pX + 3, kRulerHeight - 2, QString::number(playheadIter));
	}

	for (int row = 0; row < sections.size(); row++)
	{
		const sSectionInfo &sec = sections[row];
		const int y = kRulerHeight + row * kRowHeight;
		const QRect rowRect(0, y, width(), kRowHeight);

		if (row % 2 == 0)
			painter.fillRect(rowRect.adjusted(g.chartLeft, 0, 0, 0), bgColor.darker(108));

		painter.setPen(sec.enabled ? textColor : gridColor);
		QString label = QString("#%1").arg(sec.slot);
		if (!sec.name.isEmpty()) label += " " + sec.name.left(10);
		painter.drawText(4, y + 13, label);

		if (!sec.enabled) continue;

		const int start = qMin(sec.startIter, sec.stopIter);
		const int stop = qMax(sec.startIter, sec.stopIter);
		const bool invalid = sec.startIter > sec.stopIter;
		const QRect barRect = BarRect(row, g);

		QColor fill = invalid ? QColor(220, 80, 80, 200) : SlotColor(sec.slot - 1);
		fill.setAlpha(190);
		painter.fillRect(barRect, fill);

		if (sec.fadeIn > 0 && !invalid)
		{
			const int fadeEnd = qMin(stop, start + sec.fadeIn);
			const int fx2 = int(IterToX(fadeEnd, g));
			QRect fadeRect(barRect.left(), barRect.y(), qMax(2, fx2 - barRect.left()), barRect.height());
			painter.fillRect(fadeRect, QColor(255, 255, 255, 70));
		}
		if (sec.fadeOut > 0 && !invalid)
		{
			const int fadeStart = qMax(start, stop - sec.fadeOut);
			const int fx1 = int(IterToX(fadeStart, g));
			QRect fadeRect(fx1, barRect.y(), qMax(2, barRect.right() - fx1), barRect.height());
			painter.fillRect(fadeRect, QColor(0, 0, 0, 60));
		}

		painter.setPen(sec.enabled ? textColor.darker(130) : gridColor);
		painter.drawRect(barRect);

		// Drag handles
		painter.fillRect(barRect.left() - 1, barRect.top(), 3, barRect.height(), QColor(255, 255, 255, 160));
		painter.fillRect(barRect.right() - 2, barRect.top(), 3, barRect.height(), QColor(255, 255, 255, 160));

		if (hoverRow == row || (dragRow == row && dragType != hitNone)
			|| (dragType == hitBarDuplicate && duplicateTargetRow == row))
			painter.fillRect(rowRect.adjusted(g.chartLeft, 0, 0, 0), QColor(255, 255, 255, 25));
	}

	if (dragType == hitBarDuplicate && dragRow >= 0 && duplicateTargetRow >= 0
			&& duplicateTargetRow < sections.size() && sections[dragRow].enabled)
	{
		const QRect ghost = BarRect(dragRow, g);
		const int targetY = kRulerHeight + duplicateTargetRow * kRowHeight + 3;
		QRect ghostOnTarget(ghost.left(), targetY, ghost.width(), kRowHeight - 6);
		QPen ghostPen(SlotColor(sections[dragRow].slot - 1));
		ghostPen.setStyle(Qt::DashLine);
		ghostPen.setWidth(2);
		painter.setPen(ghostPen);
		painter.setBrush(QColor(255, 255, 255, 30));
		painter.drawRect(ghostOnTarget);
	}
}

void cHybridSectionTimelineWidget::mouseMoveEvent(QMouseEvent *event)
{
	const sChartGeom g = ChartGeom();
	const int row = RowAtY(event->pos().y());

	if (dragType != hitNone && dragRow >= 0 && dragRow < sections.size())
	{
		if (dragType == hitBarDuplicate)
		{
			duplicateTargetRow = RowAtY(event->pos().y());
			if (duplicateTargetRow >= 0 && duplicateTargetRow < sections.size())
			{
				const sSectionInfo &src = sections[dragRow];
				const sSectionInfo &dst = sections[duplicateTargetRow];
				QString tip = tr("Copy slot #%1 → #%2\nIterations: %3 – %4\nWeight: %5")
					.arg(src.slot)
					.arg(dst.slot)
					.arg(src.startIter)
					.arg(src.stopIter)
					.arg(src.weight, 0, 'f', 3);
				if (duplicateTargetRow == dragRow)
					tip += tr("\nRelease on another row to apply");
				else
					tip += tr("\nRelease to paste range + weight/fade + weight mode");
				QToolTip::showText(event->globalPos(), tip, this);
			}
			update();
			event->accept();
			return;
		}

		const int iter = XToIter(event->pos().x(), g);
		sSectionInfo &sec = sections[dragRow];

		if (dragType == hitBarStart)
		{
			sec.startIter = ClampIter(iter);
			if (sec.startIter > sec.stopIter) qSwap(sec.startIter, sec.stopIter);
		}
		else if (dragType == hitBarStop)
		{
			sec.stopIter = ClampIter(iter);
			if (sec.startIter > sec.stopIter) qSwap(sec.startIter, sec.stopIter);
		}
		else if (dragType == hitBarMove)
		{
			const int span = dragStopIter - dragStartIter;
			int newStart = ClampIter(iter - dragAnchorIter);
			int newStop = ClampIter(newStart + span);
			if (newStop > kMaxIter)
			{
				newStop = kMaxIter;
				newStart = qMax(0, newStop - span);
			}
			sec.startIter = newStart;
			sec.stopIter = newStop;
		}
		update();
		event->accept();
		return;
	}

	if (row != hoverRow)
	{
		hoverRow = row;
		update();
	}

	UpdateHoverCursor(event->pos());

	if (row >= 0 && row < sections.size())
	{
		const sSectionInfo &sec = sections[row];
		const sHitResult hit = HitTest(event->pos());
		const int iterAtCursor = XToIter(event->pos().x(), g);
		QToolTip::showText(event->globalPos(), BuildRowTooltip(sec, hit, iterAtCursor), this);
	}
	else if (HitTest(event->pos()).type == hitRuler)
	{
		const int iter = XToIter(event->pos().x(), g);
		QToolTip::showText(event->globalPos(),
			tr("Click: playhead at iteration %1\n(double-click row opens tab without playhead)").arg(iter),
			this);
	}
	else
	{
		QToolTip::hideText();
	}

	QWidget::mouseMoveEvent(event);
}

void cHybridSectionTimelineWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() != Qt::LeftButton)
	{
		QWidget::mousePressEvent(event);
		return;
	}

	const sHitResult hit = HitTest(event->pos());
	const sChartGeom g = ChartGeom();

	if ((event->modifiers() & Qt::ShiftModifier) && hit.row >= 0 && hit.row < sections.size()
			&& sections[hit.row].enabled
			&& (hit.type == hitBarStart || hit.type == hitBarStop || hit.type == hitBarMove))
	{
		dragType = hitBarDuplicate;
		dragRow = hit.row;
		duplicateTargetRow = hit.row;
		setCursor(Qt::ClosedHandCursor);
		emit signalSlotSelected(sections[dragRow].slot);
		event->accept();
		return;
	}

	if (hit.type == hitBarStart || hit.type == hitBarStop || hit.type == hitBarMove)
	{
		dragType = hit.type;
		dragRow = hit.row;
		dragStartIter = sections[dragRow].startIter;
		dragStopIter = sections[dragRow].stopIter;
		dragAnchorIter = XToIter(event->pos().x(), g) - dragStartIter;
		setCursor(hit.type == hitBarMove ? Qt::ClosedHandCursor : Qt::SizeHorCursor);
		emit signalSlotSelected(sections[dragRow].slot);
		event->accept();
		return;
	}

	const int iter = XToIter(event->pos().x(), g);
	SetPlayheadIteration(iter);

	int slot = -1;
	if (hit.row >= 0 && hit.row < sections.size() && sections[hit.row].enabled)
		slot = sections[hit.row].slot;
	else
		slot = SlotAtIteration(iter);

	emit signalIterationClicked(iter, slot);
	if (slot > 0) emit signalSlotSelected(slot);

	event->accept();
}

void cHybridSectionTimelineWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && dragType == hitBarDuplicate && dragRow >= 0
			&& dragRow < sections.size())
	{
		const int targetRow = RowAtY(event->pos().y());
		if (targetRow >= 0 && targetRow < sections.size() && targetRow != dragRow
				&& sections[dragRow].enabled && sections[targetRow].enabled)
		{
			const sSectionInfo &src = sections[dragRow];
			sSectionInfo &dst = sections[targetRow];
			dst.startIter = src.startIter;
			dst.stopIter = src.stopIter;
			dst.weight = src.weight;
			dst.fadeIn = src.fadeIn;
			dst.fadeOut = src.fadeOut;
			emit signalSectionCopied(src.slot, dst.slot, dst.startIter, dst.stopIter, dst.weight,
				dst.fadeIn, dst.fadeOut);
			emit signalSlotSelected(dst.slot);
			update();
		}
	}
	else if (event->button() == Qt::LeftButton && dragType != hitNone && dragType != hitBarDuplicate
			&& dragRow >= 0 && dragRow < sections.size())
	{
		const sSectionInfo &sec = sections[dragRow];
		if (sec.startIter != dragStartIter || sec.stopIter != dragStopIter)
			emit signalRangeChanged(sec.slot, sec.startIter, sec.stopIter);
	}

	dragType = hitNone;
	dragRow = -1;
	duplicateTargetRow = -1;
	UpdateHoverCursor(event->pos());
	unsetCursor();
	event->accept();
}

void cHybridSectionTimelineWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	const int row = RowAtY(event->pos().y());
	if (row >= 0 && row < sections.size() && sections[row].enabled)
	{
		emit signalSlotSelected(sections[row].slot);
		event->accept();
		return;
	}

	const sHitResult hit = HitTest(event->pos());
	if (hit.type == hitRuler)
	{
		const int slot = SlotAtIteration(XToIter(event->pos().x(), ChartGeom()));
		if (slot > 0) emit signalSlotSelected(slot);
		event->accept();
		return;
	}

	QWidget::mouseDoubleClickEvent(event);
}

void cHybridSectionTimelineWidget::leaveEvent(QEvent *event)
{
	if (dragType == hitNone)
	{
		hoverRow = -1;
		duplicateTargetRow = -1;
		update();
	}
	QToolTip::hideText();
	unsetCursor();
	QWidget::leaveEvent(event);
}

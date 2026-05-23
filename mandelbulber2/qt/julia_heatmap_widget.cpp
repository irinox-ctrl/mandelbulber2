/**
 * 3x3lion — Founded by Iri and Devin
 *
 * Julia Heatmap Widget implementation.
 */

#include "julia_heatmap_widget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QtMath>

static const char *kAxisNames[] = {"c.x", "c.y", "c.z"};

cJuliaHeatmapWidget::cJuliaHeatmapWidget(QWidget *parent) : QWidget(parent)
{
	setMouseTracking(true);
	setMinimumSize(200, 200);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	scores.resize(resolution * resolution);
	scores.fill(0.0);

	scanTimer = new QTimer(this);
	scanTimer->setInterval(50);
	connect(scanTimer, &QTimer::timeout, this, &cJuliaHeatmapWidget::slotScanStep);
}

cJuliaHeatmapWidget::~cJuliaHeatmapWidget()
{
	if (scanTimer)
	{
		scanTimer->stop();
		delete scanTimer;
	}
}

void cJuliaHeatmapWidget::SetAxes(int h, int v)
{
	if (h == axisH && v == axisV) return;
	axisH = qBound(0, h, 2);
	axisV = qBound(0, v, 2);
	imageDirty = true;
	update();
}

void cJuliaHeatmapWidget::SetRange(double r)
{
	range = qMax(0.01, r);
	imageDirty = true;
	update();
}

void cJuliaHeatmapWidget::SetFixedAxisValue(double val)
{
	fixedAxisValue = val;
}

void cJuliaHeatmapWidget::SetResolution(int res)
{
	res = qBound(8, res, 128);
	if (res == resolution) return;
	resolution = res;
	scores.resize(resolution * resolution);
	scores.fill(0.0);
	maxScore = 0.0;
	hasData = false;
	imageDirty = true;
	update();
}

void cJuliaHeatmapWidget::SetScore(int gx, int gy, double score)
{
	if (gx < 0 || gx >= resolution || gy < 0 || gy >= resolution) return;
	scores[gy * resolution + gx] = score;
	if (score > maxScore) maxScore = score;
	hasData = true;
	imageDirty = true;
	update();
}

void cJuliaHeatmapWidget::SetScoreGrid(const QVector<double> &grid)
{
	if (grid.size() != resolution * resolution) return;
	scores = grid;
	maxScore = 0.0;
	for (double s : scores)
	{
		if (s > maxScore) maxScore = s;
	}
	hasData = maxScore > 0.0;
	imageDirty = true;
	update();
}

void cJuliaHeatmapWidget::ClearScores()
{
	scores.fill(0.0);
	maxScore = 0.0;
	hasData = false;
	imageDirty = true;
	update();
}

void cJuliaHeatmapWidget::PixelToC(int px, int py, double &cH, double &cV) const
{
	int mapLeft = kLabelSpace;
	int mapTop = kPadding;
	int mapW = width() - kLabelSpace - kColorBarWidth - kPadding * 2;
	int mapH = height() - kLabelSpace - kPadding;

	if (mapW <= 0 || mapH <= 0)
	{
		cH = 0.0;
		cV = 0.0;
		return;
	}

	cH = -range + 2.0 * range * (px - mapLeft) / mapW;
	cV = range - 2.0 * range * (py - mapTop) / mapH;  // Y is inverted
}

void cJuliaHeatmapWidget::SetMarker(double cH, double cV)
{
	markerH = cH;
	markerV = cV;
	showMarker = true;
	update();
}

void cJuliaHeatmapWidget::ClearMarker()
{
	showMarker = false;
	update();
}

void cJuliaHeatmapWidget::StartScan()
{
	if (scanning) return;
	ClearScores();
	scanning = true;
	scanX = 0;
	scanY = 0;
	scanTimer->start();
}

void cJuliaHeatmapWidget::StopScan()
{
	scanning = false;
	scanTimer->stop();
	emit signalScanComplete();
}

int cJuliaHeatmapWidget::GetScanProgress() const
{
	if (!scanning) return 100;
	int total = resolution * resolution;
	int done = scanY * resolution + scanX;
	return total > 0 ? (done * 100) / total : 0;
}

void cJuliaHeatmapWidget::SetColorScheme(eColorScheme scheme)
{
	colorScheme = scheme;
	imageDirty = true;
	update();
}

void cJuliaHeatmapWidget::slotScanStep()
{
	if (!scanning) return;

	double cH, cV;
	double stepSize = 2.0 * range / resolution;
	cH = -range + (scanX + 0.5) * stepSize;
	cV = range - (scanY + 0.5) * stepSize;

	emit signalScanRequested(scanX, scanY, cH, cV);
	emit signalScanProgress(GetScanProgress());

	scanX++;
	if (scanX >= resolution)
	{
		scanX = 0;
		scanY++;
	}
	if (scanY >= resolution)
	{
		StopScan();
	}
}

// --- Painting ---

void cJuliaHeatmapWidget::RebuildImage()
{
	int mapW = width() - kLabelSpace - kColorBarWidth - kPadding * 2;
	int mapH = height() - kLabelSpace - kPadding;
	if (mapW <= 0 || mapH <= 0) return;

	heatmapImage = QImage(mapW, mapH, QImage::Format_ARGB32);
	heatmapImage.fill(QColor(0x1e, 0x1e, 0x2e));  // Catppuccin Mocha base

	if (!hasData)
	{
		imageDirty = false;
		return;
	}

	double normFactor = maxScore > 0.0 ? 1.0 / maxScore : 1.0;
	double cellW = static_cast<double>(mapW) / resolution;
	double cellH = static_cast<double>(mapH) / resolution;

	QPainter imgPainter(&heatmapImage);
	imgPainter.setRenderHint(QPainter::Antialiasing, false);

	for (int gy = 0; gy < resolution; gy++)
	{
		for (int gx = 0; gx < resolution; gx++)
		{
			double score = scores[gy * resolution + gx] * normFactor;
			QColor color = ScoreToColor(score);

			int x = static_cast<int>(gx * cellW);
			int y = static_cast<int>(gy * cellH);
			int w = static_cast<int>((gx + 1) * cellW) - x;
			int h = static_cast<int>((gy + 1) * cellH) - y;
			imgPainter.fillRect(x, y, w, h, color);
		}
	}
	imgPainter.end();
	imageDirty = false;
}

void cJuliaHeatmapWidget::paintEvent(QPaintEvent * /*event*/)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	// Background
	painter.fillRect(rect(), QColor(0x11, 0x11, 0x1b));

	int mapLeft = kLabelSpace;
	int mapTop = kPadding;
	int mapW = width() - kLabelSpace - kColorBarWidth - kPadding * 2;
	int mapH = height() - kLabelSpace - kPadding;
	if (mapW <= 0 || mapH <= 0) return;

	// Rebuild heatmap image if needed
	if (imageDirty || heatmapImage.size() != QSize(mapW, mapH))
	{
		RebuildImage();
	}

	// Draw the heatmap
	painter.drawImage(mapLeft, mapTop, heatmapImage);

	// Border around the heatmap
	painter.setPen(QPen(QColor(0xcb, 0xa6, 0xf7), 1));  // Purple border
	painter.drawRect(mapLeft, mapTop, mapW - 1, mapH - 1);

	// Axis labels
	DrawGrid(painter);
	DrawColorBar(painter);

	// Marker
	if (showMarker) DrawMarker(painter);

	// Hover tooltip
	if (hovering) DrawHoverTooltip(painter);

	// Scan progress overlay
	if (scanning) DrawScanProgress(painter);

	// "No data" text when empty
	if (!hasData && !scanning)
	{
		painter.setPen(QColor(0x6c, 0x70, 0x86));  // Overlay0
		QFont font = painter.font();
		font.setPointSize(9);
		painter.setFont(font);
		painter.drawText(QRect(mapLeft, mapTop, mapW, mapH), Qt::AlignCenter,
			"Click 'Scan' to map\nJulia c-space interest");
	}
}

void cJuliaHeatmapWidget::DrawGrid(QPainter &painter) const
{
	int mapLeft = kLabelSpace;
	int mapTop = kPadding;
	int mapW = width() - kLabelSpace - kColorBarWidth - kPadding * 2;
	int mapH = height() - kLabelSpace - kPadding;

	QPen gridPen(QColor(0x45, 0x47, 0x5a, 80), 1, Qt::DotLine);
	painter.setPen(gridPen);

	// Draw center crosshair (c=0)
	int centerX = mapLeft + mapW / 2;
	int centerY = mapTop + mapH / 2;
	painter.drawLine(centerX, mapTop, centerX, mapTop + mapH);
	painter.drawLine(mapLeft, centerY, mapLeft + mapW, centerY);

	// Axis labels
	QFont font = painter.font();
	font.setPointSize(7);
	painter.setFont(font);
	painter.setPen(QColor(0xcd, 0xd6, 0xf4));  // Text color

	// H axis label at bottom
	QString hLabel = QString("%1 [-%2, +%2]")
						 .arg(kAxisNames[axisH])
						 .arg(QString::number(range, 'f', 1));
	painter.drawText(QRect(mapLeft, mapTop + mapH + 2, mapW, kLabelSpace - 2),
		Qt::AlignCenter, hLabel);

	// V axis label on left (rotated)
	painter.save();
	painter.translate(2, mapTop + mapH / 2);
	painter.rotate(-90);
	QString vLabel = kAxisNames[axisV];
	painter.drawText(QRect(-mapH / 2, 0, mapH, kLabelSpace - 2), Qt::AlignCenter, vLabel);
	painter.restore();

	// Corner values
	font.setPointSize(6);
	painter.setFont(font);
	painter.setPen(QColor(0x6c, 0x70, 0x86));

	QString rangeStr = QString::number(range, 'f', 1);
	painter.drawText(QRect(mapLeft, mapTop + mapH + 1, 30, 12), Qt::AlignLeft, "-" + rangeStr);
	painter.drawText(
		QRect(mapLeft + mapW - 30, mapTop + mapH + 1, 30, 12), Qt::AlignRight, "+" + rangeStr);
}

void cJuliaHeatmapWidget::DrawMarker(QPainter &painter) const
{
	int mapLeft = kLabelSpace;
	int mapTop = kPadding;
	int mapW = width() - kLabelSpace - kColorBarWidth - kPadding * 2;
	int mapH = height() - kLabelSpace - kPadding;
	if (mapW <= 0 || mapH <= 0) return;

	double normH = (markerH + range) / (2.0 * range);
	double normV = (range - markerV) / (2.0 * range);
	int px = mapLeft + static_cast<int>(normH * mapW);
	int py = mapTop + static_cast<int>(normV * mapH);

	// Crosshair
	QPen markerPen(QColor(0xf5, 0xc2, 0xe7), 2);  // Pink
	painter.setPen(markerPen);
	painter.drawLine(px - 6, py, px + 6, py);
	painter.drawLine(px, py - 6, px, py + 6);

	// Circle
	painter.setBrush(Qt::NoBrush);
	painter.drawEllipse(QPoint(px, py), 4, 4);
}

void cJuliaHeatmapWidget::DrawHoverTooltip(QPainter &painter) const
{
	int mapLeft = kLabelSpace;
	int mapTop = kPadding;
	int mapW = width() - kLabelSpace - kColorBarWidth - kPadding * 2;
	int mapH = height() - kLabelSpace - kPadding;

	// Convert hover pixel to grid cell
	double cellW = static_cast<double>(mapW) / resolution;
	double cellH = static_cast<double>(mapH) / resolution;
	int gx = static_cast<int>((hoverX - mapLeft) / cellW);
	int gy = static_cast<int>((hoverY - mapTop) / cellH);

	if (gx < 0 || gx >= resolution || gy < 0 || gy >= resolution) return;

	double score = scores[gy * resolution + gx];
	double cH, cV;
	PixelToC(hoverX, hoverY, cH, cV);

	// Draw tooltip box
	QString text = QString("%1=%2\n%3=%4\nscore: %5")
					   .arg(kAxisNames[axisH])
					   .arg(QString::number(cH, 'f', 3))
					   .arg(kAxisNames[axisV])
					   .arg(QString::number(cV, 'f', 3))
					   .arg(QString::number(score, 'f', 4));

	QFont font = painter.font();
	font.setPointSize(7);
	painter.setFont(font);
	QRect textRect = painter.fontMetrics().boundingRect(QRect(0, 0, 200, 200),
		Qt::TextWordWrap, text);

	int tipX = hoverX + 12;
	int tipY = hoverY - textRect.height() - 8;
	if (tipX + textRect.width() + 8 > width()) tipX = hoverX - textRect.width() - 16;
	if (tipY < 0) tipY = hoverY + 12;

	QRect bgRect(tipX - 4, tipY - 2, textRect.width() + 8, textRect.height() + 4);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(0x1e, 0x1e, 0x2e, 220));
	painter.drawRoundedRect(bgRect, 3, 3);

	painter.setPen(QColor(0xcb, 0xa6, 0xf7));  // Purple border
	painter.drawRoundedRect(bgRect, 3, 3);

	painter.setPen(QColor(0xcd, 0xd6, 0xf4));
	painter.drawText(QRect(tipX, tipY, textRect.width(), textRect.height()),
		Qt::TextWordWrap, text);
}

void cJuliaHeatmapWidget::DrawColorBar(QPainter &painter) const
{
	int barLeft = width() - kColorBarWidth - kPadding;
	int barTop = kPadding;
	int barH = height() - kLabelSpace - kPadding;
	if (barH <= 0) return;

	for (int y = 0; y < barH; y++)
	{
		double t = 1.0 - static_cast<double>(y) / barH;
		QColor c = ScoreToColor(t);
		painter.setPen(c);
		painter.drawLine(barLeft, barTop + y, barLeft + kColorBarWidth - 1, barTop + y);
	}

	// Border
	painter.setPen(QColor(0x45, 0x47, 0x5a));
	painter.drawRect(barLeft, barTop, kColorBarWidth - 1, barH - 1);

	// Labels
	QFont font = painter.font();
	font.setPointSize(6);
	painter.setFont(font);
	painter.setPen(QColor(0x6c, 0x70, 0x86));

	if (maxScore > 0.0)
	{
		painter.drawText(QRect(barLeft - 2, barTop - 10, kColorBarWidth + 4, 10),
			Qt::AlignCenter, QString::number(maxScore, 'f', 2));
	}
	painter.drawText(QRect(barLeft - 2, barTop + barH, kColorBarWidth + 4, 10),
		Qt::AlignCenter, "0");
}

void cJuliaHeatmapWidget::DrawScanProgress(QPainter &painter) const
{
	int mapLeft = kLabelSpace;
	int mapTop = kPadding;
	int mapW = width() - kLabelSpace - kColorBarWidth - kPadding * 2;

	int progress = GetScanProgress();
	int barW = mapW * progress / 100;

	// Semi-transparent progress bar at top
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(0x89, 0xb4, 0xfa, 60));
	painter.drawRect(mapLeft, mapTop, barW, 3);

	// Progress text
	QFont font = painter.font();
	font.setPointSize(8);
	font.setBold(true);
	painter.setFont(font);
	painter.setPen(QColor(0x89, 0xb4, 0xfa));
	painter.drawText(QRect(mapLeft, mapTop + 4, mapW, 16), Qt::AlignCenter,
		QString("Scanning... %1%").arg(progress));
}

// --- Color Mapping ---

QColor cJuliaHeatmapWidget::ScoreToColor(double score) const
{
	score = qBound(0.0, score, 1.0);

	switch (colorScheme)
	{
		case schemeCatppuccin:
		{
			// Catppuccin Mocha gradient: Base → Surface → Lavender → Mauve → Pink → Red
			if (score < 0.01) return QColor(0x1e, 0x1e, 0x2e);       // Base (near zero)
			if (score < 0.2) return InterpolateColor(
				QColor(0x31, 0x32, 0x44), QColor(0x58, 0x5b, 0x70), (score - 0.01) / 0.19);
			if (score < 0.4) return InterpolateColor(
				QColor(0x58, 0x5b, 0x70), QColor(0x89, 0xb4, 0xfa), (score - 0.2) / 0.2);
			if (score < 0.6) return InterpolateColor(
				QColor(0x89, 0xb4, 0xfa), QColor(0xcb, 0xa6, 0xf7), (score - 0.4) / 0.2);
			if (score < 0.8) return InterpolateColor(
				QColor(0xcb, 0xa6, 0xf7), QColor(0xf5, 0xc2, 0xe7), (score - 0.6) / 0.2);
			return InterpolateColor(
				QColor(0xf5, 0xc2, 0xe7), QColor(0xf3, 0x8b, 0xa8), (score - 0.8) / 0.2);
		}
		case schemeInferno:
		{
			if (score < 0.25) return InterpolateColor(
				QColor(0, 0, 4), QColor(87, 16, 110), score / 0.25);
			if (score < 0.5) return InterpolateColor(
				QColor(87, 16, 110), QColor(188, 55, 84), (score - 0.25) / 0.25);
			if (score < 0.75) return InterpolateColor(
				QColor(188, 55, 84), QColor(249, 142, 9), (score - 0.5) / 0.25);
			return InterpolateColor(
				QColor(249, 142, 9), QColor(252, 255, 164), (score - 0.75) / 0.25);
		}
		case schemePlasma:
		{
			if (score < 0.25) return InterpolateColor(
				QColor(13, 8, 135), QColor(126, 3, 168), score / 0.25);
			if (score < 0.5) return InterpolateColor(
				QColor(126, 3, 168), QColor(204, 71, 120), (score - 0.25) / 0.25);
			if (score < 0.75) return InterpolateColor(
				QColor(204, 71, 120), QColor(248, 149, 64), (score - 0.5) / 0.25);
			return InterpolateColor(
				QColor(248, 149, 64), QColor(240, 249, 33), (score - 0.75) / 0.25);
		}
		case schemeViridis:
		{
			if (score < 0.25) return InterpolateColor(
				QColor(68, 1, 84), QColor(59, 82, 139), score / 0.25);
			if (score < 0.5) return InterpolateColor(
				QColor(59, 82, 139), QColor(33, 145, 140), (score - 0.25) / 0.25);
			if (score < 0.75) return InterpolateColor(
				QColor(33, 145, 140), QColor(94, 201, 98), (score - 0.5) / 0.25);
			return InterpolateColor(
				QColor(94, 201, 98), QColor(253, 231, 37), (score - 0.75) / 0.25);
		}
		case schemeMagma:
		{
			if (score < 0.25) return InterpolateColor(
				QColor(0, 0, 4), QColor(81, 18, 124), score / 0.25);
			if (score < 0.5) return InterpolateColor(
				QColor(81, 18, 124), QColor(183, 55, 121), (score - 0.25) / 0.25);
			if (score < 0.75) return InterpolateColor(
				QColor(183, 55, 121), QColor(254, 159, 109), (score - 0.5) / 0.25);
			return InterpolateColor(
				QColor(254, 159, 109), QColor(252, 253, 191), (score - 0.75) / 0.25);
		}
	}
	return QColor(0x1e, 0x1e, 0x2e);
}

QColor cJuliaHeatmapWidget::InterpolateColor(const QColor &a, const QColor &b, double t) const
{
	t = qBound(0.0, t, 1.0);
	return QColor(
		a.red() + static_cast<int>((b.red() - a.red()) * t),
		a.green() + static_cast<int>((b.green() - a.green()) * t),
		a.blue() + static_cast<int>((b.blue() - a.blue()) * t));
}

// --- Mouse Events ---

void cJuliaHeatmapWidget::mousePressEvent(QMouseEvent *event)
{
	int mapLeft = kLabelSpace;
	int mapTop = kPadding;
	int mapW = width() - kLabelSpace - kColorBarWidth - kPadding * 2;
	int mapH = height() - kLabelSpace - kPadding;

	int px = event->pos().x();
	int py = event->pos().y();

	if (px >= mapLeft && px < mapLeft + mapW && py >= mapTop && py < mapTop + mapH)
	{
		double cH, cV;
		PixelToC(px, py, cH, cV);
		emit signalCellClicked(cH, cV);
	}
}

void cJuliaHeatmapWidget::mouseMoveEvent(QMouseEvent *event)
{
	int mapLeft = kLabelSpace;
	int mapTop = kPadding;
	int mapW = width() - kLabelSpace - kColorBarWidth - kPadding * 2;
	int mapH = height() - kLabelSpace - kPadding;

	int px = event->pos().x();
	int py = event->pos().y();

	if (px >= mapLeft && px < mapLeft + mapW && py >= mapTop && py < mapTop + mapH)
	{
		hovering = true;
		hoverX = px;
		hoverY = py;

		double cH, cV;
		PixelToC(px, py, cH, cV);

		// Compute grid cell
		double cellW = static_cast<double>(mapW) / resolution;
		double cellH = static_cast<double>(mapH) / resolution;
		int gx = static_cast<int>((px - mapLeft) / cellW);
		int gy = static_cast<int>((py - mapTop) / cellH);
		double score = 0.0;
		if (gx >= 0 && gx < resolution && gy >= 0 && gy < resolution)
			score = scores[gy * resolution + gx];

		emit signalHoverInfo(cH, cV, score);
	}
	else
	{
		hovering = false;
	}
	update();
}

void cJuliaHeatmapWidget::leaveEvent(QEvent * /*event*/)
{
	hovering = false;
	update();
}

void cJuliaHeatmapWidget::resizeEvent(QResizeEvent * /*event*/)
{
	imageDirty = true;
}

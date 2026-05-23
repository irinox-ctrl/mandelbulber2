/**
 * 3x3lion — Founded by Iri and Devin
 *
 * Drone Explorer Widget implementation — visual prototype for autonomous exploration.
 */

#include "drone_explorer_widget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QtMath>
#include <QRandomGenerator>
#include <QPainterPath>

// Catppuccin Mocha drone colors
const QColor cDroneExplorerWidget::kDroneColors[] = {
	QColor(0x89, 0xb4, 0xfa), // Blue  — Alpha
	QColor(0xcb, 0xa6, 0xf7), // Purple — Bravo
	QColor(0xf5, 0xc2, 0xe7), // Pink — Charlie
	QColor(0xa6, 0xe3, 0xa1), // Green — Delta
	QColor(0xfa, 0xb3, 0x87), // Orange — Echo
};

const char *cDroneExplorerWidget::kDroneNames[] = {
	"Alpha", "Bravo", "Charlie", "Delta", "Echo"};

cDroneExplorerWidget::cDroneExplorerWidget(QWidget *parent) : QWidget(parent)
{
	setMinimumSize(280, 200);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	animTimer = new QTimer(this);
	animTimer->setInterval(40); // 25 fps
	connect(animTimer, &QTimer::timeout, this, &cDroneExplorerWidget::slotAnimationStep);

	InitDrones();
}

cDroneExplorerWidget::~cDroneExplorerWidget()
{
	if (animTimer)
	{
		animTimer->stop();
		delete animTimer;
	}
}

void cDroneExplorerWidget::InitDrones()
{
	drones.clear();
	drones.resize(kDroneCount);
	auto *rng = QRandomGenerator::global();

	for (int i = 0; i < kDroneCount; i++)
	{
		sDroneState &d = drones[i];
		d.color = kDroneColors[i];
		d.name = QString(kDroneNames[i]);
		double angle = 2.0 * M_PI * i / kDroneCount;
		d.pos = QPointF(0.1 * qCos(angle), 0.1 * qSin(angle));
		d.vel = QPointF(0.0, 0.0);
		d.heading = angle;
		d.bestScore = 0.0;
		d.discoveries = 0;
		d.energy = 1.0;
		d.hasTarget = false;
		d.trail.clear();
		d.hotspots.clear();
		d.hotspotScores.clear();
	}
}

void cDroneExplorerWidget::SetRange(double r)
{
	range = qMax(0.1, r);
	update();
}

void cDroneExplorerWidget::SetScoreGrid(const QVector<double> &scores, int resolution)
{
	scoreGrid = scores;
	gridResolution = resolution;
	gridMaxScore = 0.0;
	for (double s : scores)
		if (s > gridMaxScore) gridMaxScore = s;

	visited.resize(resolution * resolution);
	visited.fill(false);
	update();
}

void cDroneExplorerWidget::StartFleet()
{
	if (running) return;
	running = true;
	tickCount = 0;
	animTimer->start();
	update();
}

void cDroneExplorerWidget::StopFleet()
{
	running = false;
	animTimer->stop();
	update();
}

void cDroneExplorerWidget::ResetFleet()
{
	StopFleet();
	InitDrones();
	tickCount = 0;
	visited.fill(false);
	update();
}

void cDroneExplorerWidget::SetSpeed(double s)
{
	speed = qBound(0.1, s, 5.0);
}

void cDroneExplorerWidget::SetStrategy(int idx)
{
	strategy = qBound(0, idx, 2);
}

int cDroneExplorerWidget::GetTotalDiscoveries() const
{
	int total = 0;
	for (const auto &d : drones)
		total += d.discoveries;
	return total;
}

double cDroneExplorerWidget::GetBestScore() const
{
	double best = 0.0;
	for (const auto &d : drones)
		if (d.bestScore > best) best = d.bestScore;
	return best;
}

double cDroneExplorerWidget::GetCoverage() const
{
	if (visited.isEmpty()) return 0.0;
	int count = 0;
	for (bool v : visited)
		if (v) count++;
	return static_cast<double>(count) / visited.size();
}

double cDroneExplorerWidget::SampleScore(double cH, double cV) const
{
	if (gridResolution <= 0 || scoreGrid.isEmpty()) return 0.0;

	int gx = static_cast<int>((cH + range) / (2.0 * range) * gridResolution);
	int gy = static_cast<int>((range - cV) / (2.0 * range) * gridResolution);
	gx = qBound(0, gx, gridResolution - 1);
	gy = qBound(0, gy, gridResolution - 1);
	return scoreGrid[gy * gridResolution + gx];
}

void cDroneExplorerWidget::ChooseTarget(sDroneState &drone)
{
	auto *rng = QRandomGenerator::global();

	if (strategy == 0) // Explore: seek unvisited high-score areas
	{
		double bestScore = -1.0;
		QPointF bestPt;
		for (int attempt = 0; attempt < 30; attempt++)
		{
			double ch = (rng->generateDouble() * 2.0 - 1.0) * range;
			double cv = (rng->generateDouble() * 2.0 - 1.0) * range;
			double score = SampleScore(ch, cv);

			// Penalize already-visited cells
			int gx = static_cast<int>((ch + range) / (2.0 * range) * gridResolution);
			int gy = static_cast<int>((range - cv) / (2.0 * range) * gridResolution);
			gx = qBound(0, gx, gridResolution - 1);
			gy = qBound(0, gy, gridResolution - 1);
			if (!visited.isEmpty() && visited[gy * gridResolution + gx]) score *= 0.3;

			if (score > bestScore)
			{
				bestScore = score;
				bestPt = QPointF(ch, cv);
			}
		}
		drone.target = bestPt;
		drone.hasTarget = true;
	}
	else if (strategy == 1) // Exploit: focus on known hotspots
	{
		if (!drone.hotspots.isEmpty())
		{
			int idx = rng->bounded(drone.hotspots.size());
			QPointF base = drone.hotspots[idx];
			double jitter = range * 0.05;
			drone.target = base + QPointF(
				(rng->generateDouble() - 0.5) * jitter,
				(rng->generateDouble() - 0.5) * jitter);
		}
		else
		{
			ChooseTarget(drone); // fallback to explore
		}
		drone.hasTarget = true;
	}
	else // Swarm: move toward fleet center + random offset
	{
		QPointF center(0, 0);
		for (const auto &d : drones)
			center += d.pos;
		center /= drones.size();

		double offset = range * 0.3;
		drone.target = center + QPointF(
			(rng->generateDouble() - 0.5) * offset,
			(rng->generateDouble() - 0.5) * offset);
		drone.hasTarget = true;
	}
}

void cDroneExplorerWidget::UpdateDrone(sDroneState &drone)
{
	if (!drone.hasTarget || drone.energy <= 0.0) ChooseTarget(drone);

	// Move toward target
	QPointF diff = drone.target - drone.pos;
	double dist = qSqrt(diff.x() * diff.x() + diff.y() * diff.y());

	if (dist < range * 0.02)
	{
		// Arrived at target — check score and choose next
		double score = SampleScore(drone.pos.x(), drone.pos.y());

		if (score > 0.5)
		{
			drone.hotspots.append(drone.pos);
			drone.hotspotScores.append(score);
			drone.discoveries++;
			if (score > drone.bestScore) drone.bestScore = score;

			int droneIdx = 0;
			for (int di = 0; di < drones.size(); di++)
			{
				if (&drones[di] == &drone) { droneIdx = di; break; }
			}
			emit signalDroneDiscovery(droneIdx, drone.pos.x(), drone.pos.y(), score);
		}

		// Mark as visited
		if (gridResolution > 0 && !visited.isEmpty())
		{
			int gx = static_cast<int>((drone.pos.x() + range) / (2.0 * range) * gridResolution);
			int gy = static_cast<int>((range - drone.pos.y()) / (2.0 * range) * gridResolution);
			gx = qBound(0, gx, gridResolution - 1);
			gy = qBound(0, gy, gridResolution - 1);
			visited[gy * gridResolution + gx] = true;
		}

		ChooseTarget(drone);
		return;
	}

	// Smooth steering
	double moveSpeed = speed * range * 0.015;
	QPointF dir = diff / dist;
	drone.vel = drone.vel * 0.85 + dir * moveSpeed * 0.15;
	drone.pos += drone.vel;

	// Clamp to range
	drone.pos.setX(qBound(-range, drone.pos.x(), range));
	drone.pos.setY(qBound(-range, drone.pos.y(), range));

	// Update heading
	if (qAbs(drone.vel.x()) > 1e-9 || qAbs(drone.vel.y()) > 1e-9)
		drone.heading = qAtan2(drone.vel.y(), drone.vel.x());

	// Consume energy
	drone.energy = qMax(0.0, drone.energy - 0.0001 * speed);

	// Add to trail (limit length)
	drone.trail.append(drone.pos);
	if (drone.trail.size() > 200) drone.trail.removeFirst();
}

void cDroneExplorerWidget::slotAnimationStep()
{
	tickCount++;
	for (auto &drone : drones)
		UpdateDrone(drone);

	emit signalFleetStatus(GetTotalDiscoveries(), GetBestScore(), GetCoverage());
	update();
}

// --- Coordinate transforms ---

QPointF cDroneExplorerWidget::CToPixel(double cH, double cV) const
{
	int mapW = width() - kDashboardWidth - kPadding * 2;
	int mapH = height() - kPadding * 2;
	double px = kPadding + (cH + range) / (2.0 * range) * mapW;
	double py = kPadding + (range - cV) / (2.0 * range) * mapH;
	return QPointF(px, py);
}

void cDroneExplorerWidget::PixelToC(int px, int py, double &cH, double &cV) const
{
	int mapW = width() - kDashboardWidth - kPadding * 2;
	int mapH = height() - kPadding * 2;
	cH = (static_cast<double>(px - kPadding) / mapW) * 2.0 * range - range;
	cV = range - (static_cast<double>(py - kPadding) / mapH) * 2.0 * range;
}

// --- Painting ---

void cDroneExplorerWidget::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);

	DrawBackground(p);
	DrawHeatmapOverlay(p);
	DrawGrid(p);
	DrawTrails(p);
	DrawHotspots(p);
	DrawDrones(p);
	DrawDashboard(p);
}

void cDroneExplorerWidget::DrawBackground(QPainter &p) const
{
	// Dark space background
	p.fillRect(rect(), QColor(0x11, 0x11, 0x1b));

	// Map area with subtle gradient
	int mapW = width() - kDashboardWidth - kPadding * 2;
	int mapH = height() - kPadding * 2;
	QRect mapRect(kPadding, kPadding, mapW, mapH);

	QLinearGradient bg(mapRect.topLeft(), mapRect.bottomRight());
	bg.setColorAt(0.0, QColor(0x1e, 0x1e, 0x2e));
	bg.setColorAt(1.0, QColor(0x18, 0x18, 0x28));
	p.fillRect(mapRect, bg);

	// Border
	p.setPen(QPen(QColor(0x45, 0x47, 0x5a), 1));
	p.drawRect(mapRect);
}

void cDroneExplorerWidget::DrawHeatmapOverlay(QPainter &p) const
{
	if (gridResolution <= 0 || scoreGrid.isEmpty() || gridMaxScore <= 0.0) return;

	int mapW = width() - kDashboardWidth - kPadding * 2;
	int mapH = height() - kPadding * 2;
	double cellW = static_cast<double>(mapW) / gridResolution;
	double cellH = static_cast<double>(mapH) / gridResolution;

	for (int gy = 0; gy < gridResolution; gy++)
	{
		for (int gx = 0; gx < gridResolution; gx++)
		{
			double score = scoreGrid[gy * gridResolution + gx];
			if (score <= 0.01) continue;

			double norm = score / gridMaxScore;
			int alpha = static_cast<int>(norm * 60); // subtle overlay
			QColor c;
			if (norm < 0.5)
				c = QColor(0x89, 0xb4, 0xfa, alpha); // blue for low
			else if (norm < 0.8)
				c = QColor(0xcb, 0xa6, 0xf7, alpha); // purple for medium
			else
				c = QColor(0xf5, 0xc2, 0xe7, alpha); // pink for high

			double px = kPadding + gx * cellW;
			double py = kPadding + gy * cellH;
			p.fillRect(QRectF(px, py, cellW + 1, cellH + 1), c);
		}
	}
}

void cDroneExplorerWidget::DrawGrid(QPainter &p) const
{
	int mapW = width() - kDashboardWidth - kPadding * 2;
	int mapH = height() - kPadding * 2;

	// Subtle grid lines
	p.setPen(QPen(QColor(0x31, 0x32, 0x44, 60), 1, Qt::DotLine));
	int gridLines = 8;
	for (int i = 1; i < gridLines; i++)
	{
		double x = kPadding + (static_cast<double>(i) / gridLines) * mapW;
		double y = kPadding + (static_cast<double>(i) / gridLines) * mapH;
		p.drawLine(QPointF(x, kPadding), QPointF(x, kPadding + mapH));
		p.drawLine(QPointF(kPadding, y), QPointF(kPadding + mapW, y));
	}

	// Center crosshair
	QPointF center = CToPixel(0, 0);
	p.setPen(QPen(QColor(0x58, 0x5b, 0x70, 80), 1));
	p.drawLine(QPointF(center.x(), kPadding), QPointF(center.x(), kPadding + mapH));
	p.drawLine(QPointF(kPadding, center.y()), QPointF(kPadding + mapW, center.y()));
}

void cDroneExplorerWidget::DrawTrails(QPainter &p) const
{
	for (const auto &drone : drones)
	{
		if (drone.trail.size() < 2) continue;

		int trailLen = drone.trail.size();
		for (int i = 1; i < trailLen; i++)
		{
			double t = static_cast<double>(i) / trailLen;
			int alpha = static_cast<int>(t * 120);
			QColor trailColor = drone.color;
			trailColor.setAlpha(alpha);
			p.setPen(QPen(trailColor, 1.5));

			QPointF a = CToPixel(drone.trail[i - 1].x(), drone.trail[i - 1].y());
			QPointF b = CToPixel(drone.trail[i].x(), drone.trail[i].y());
			p.drawLine(a, b);
		}
	}
}

void cDroneExplorerWidget::DrawHotspots(QPainter &p) const
{
	for (const auto &drone : drones)
	{
		for (int i = 0; i < drone.hotspots.size(); i++)
		{
			QPointF px = CToPixel(drone.hotspots[i].x(), drone.hotspots[i].y());
			double score = i < drone.hotspotScores.size() ? drone.hotspotScores[i] : 0.5;

			// Pulsing effect based on tick count
			double pulse = 1.0 + 0.2 * qSin(tickCount * 0.08 + i * 0.5);
			double radius = 3.0 + score * 4.0;

			// Glow
			QRadialGradient glow(px, radius * pulse * 2);
			QColor glowColor = drone.color;
			glowColor.setAlpha(40);
			glow.setColorAt(0.0, glowColor);
			glow.setColorAt(1.0, Qt::transparent);
			p.setBrush(glow);
			p.setPen(Qt::NoPen);
			p.drawEllipse(px, radius * pulse * 2, radius * pulse * 2);

			// Diamond marker
			p.setPen(QPen(drone.color, 1.5));
			p.setBrush(Qt::NoBrush);
			double r = radius * pulse;
			QPainterPath diamond;
			diamond.moveTo(px.x(), px.y() - r);
			diamond.lineTo(px.x() + r, px.y());
			diamond.lineTo(px.x(), px.y() + r);
			diamond.lineTo(px.x() - r, px.y());
			diamond.closeSubpath();
			p.drawPath(diamond);
		}
	}
}

void cDroneExplorerWidget::DrawDrones(QPainter &p) const
{
	for (const auto &drone : drones)
	{
		QPointF px = CToPixel(drone.pos.x(), drone.pos.y());
		double droneSize = 6.0;

		// Outer glow
		QRadialGradient glow(px, droneSize * 3);
		QColor glowColor = drone.color;
		glowColor.setAlpha(50);
		glow.setColorAt(0.0, glowColor);
		glow.setColorAt(1.0, Qt::transparent);
		p.setBrush(glow);
		p.setPen(Qt::NoPen);
		p.drawEllipse(px, droneSize * 3, droneSize * 3);

		// Drone body (filled circle)
		p.setBrush(drone.color);
		p.setPen(QPen(QColor(0xff, 0xff, 0xff, 180), 1.5));
		p.drawEllipse(px, droneSize, droneSize);

		// Direction arrow
		double arrowLen = droneSize * 2.0;
		QPointF arrowTip(
			px.x() + arrowLen * qCos(drone.heading),
			px.y() - arrowLen * qSin(drone.heading));
		p.setPen(QPen(drone.color, 2.0));
		p.drawLine(px, arrowTip);

		// Arrow head
		double headAngle = 0.4;
		double headLen = arrowLen * 0.4;
		QPointF h1(arrowTip.x() - headLen * qCos(drone.heading - headAngle),
			arrowTip.y() + headLen * qSin(drone.heading - headAngle));
		QPointF h2(arrowTip.x() - headLen * qCos(drone.heading + headAngle),
			arrowTip.y() + headLen * qSin(drone.heading + headAngle));
		p.drawLine(arrowTip, h1);
		p.drawLine(arrowTip, h2);

		// Target line (dotted)
		if (drone.hasTarget)
		{
			QPointF targetPx = CToPixel(drone.target.x(), drone.target.y());
			QColor targetLineColor = drone.color;
			targetLineColor.setAlpha(40);
			p.setPen(QPen(targetLineColor, 1.0, Qt::DotLine));
			p.drawLine(px, targetPx);

			// Target crosshair
			targetLineColor.setAlpha(80);
			p.setPen(QPen(targetLineColor, 1.0));
			p.drawLine(QPointF(targetPx.x() - 4, targetPx.y()), QPointF(targetPx.x() + 4, targetPx.y()));
			p.drawLine(QPointF(targetPx.x(), targetPx.y() - 4), QPointF(targetPx.x(), targetPx.y() + 4));
		}

		// Drone name label
		p.setPen(QPen(drone.color, 1));
		QFont labelFont = p.font();
		labelFont.setPixelSize(8);
		labelFont.setBold(true);
		p.setFont(labelFont);
		p.drawText(QPointF(px.x() + droneSize + 3, px.y() - droneSize), drone.name);
	}
}

void cDroneExplorerWidget::DrawDashboard(QPainter &p) const
{
	int dashX = width() - kDashboardWidth;
	int dashY = kPadding;
	int dashW = kDashboardWidth - kPadding;
	int dashH = height() - kPadding * 2;

	// Dashboard background
	QLinearGradient dashBg(dashX, dashY, dashX + dashW, dashY);
	dashBg.setColorAt(0.0, QColor(0x1e, 0x1e, 0x2e, 220));
	dashBg.setColorAt(1.0, QColor(0x18, 0x18, 0x28, 240));
	p.fillRect(QRect(dashX, dashY, dashW, dashH), dashBg);

	// Border
	p.setPen(QPen(QColor(0x45, 0x47, 0x5a), 1));
	p.drawRect(QRect(dashX, dashY, dashW, dashH));

	int y = dashY + 8;
	QFont titleFont = p.font();
	titleFont.setPixelSize(11);
	titleFont.setBold(true);

	QFont valueFont = p.font();
	valueFont.setPixelSize(10);
	valueFont.setBold(false);

	QFont labelFont = p.font();
	labelFont.setPixelSize(8);
	labelFont.setBold(false);

	// Title
	p.setFont(titleFont);
	p.setPen(QColor(0x89, 0xb4, 0xfa));
	p.drawText(QRect(dashX + 4, y, dashW - 8, 14), Qt::AlignCenter, "DRONE FLEET");
	y += 18;

	// Status indicator
	if (running)
	{
		p.setPen(QColor(0xa6, 0xe3, 0xa1));
		p.setFont(labelFont);
		p.drawText(QRect(dashX + 4, y, dashW - 8, 10), Qt::AlignCenter, "ACTIVE");
	}
	else
	{
		p.setPen(QColor(0xf3, 0x8b, 0xa8));
		p.setFont(labelFont);
		p.drawText(QRect(dashX + 4, y, dashW - 8, 10), Qt::AlignCenter, "STANDBY");
	}
	y += 14;

	// Separator
	p.setPen(QPen(QColor(0x45, 0x47, 0x5a), 1));
	p.drawLine(dashX + 8, y, dashX + dashW - 8, y);
	y += 6;

	// Stats
	p.setFont(labelFont);
	p.setPen(QColor(0x6c, 0x70, 0x86));
	p.drawText(dashX + 6, y + 8, "Discoveries");
	p.setFont(valueFont);
	p.setPen(QColor(0xf5, 0xc2, 0xe7));
	p.drawText(dashX + dashW - 35, y + 8, QString::number(GetTotalDiscoveries()));
	y += 14;

	p.setFont(labelFont);
	p.setPen(QColor(0x6c, 0x70, 0x86));
	p.drawText(dashX + 6, y + 8, "Best Score");
	p.setFont(valueFont);
	p.setPen(QColor(0xfa, 0xb3, 0x87));
	p.drawText(dashX + dashW - 42, y + 8, QString::number(GetBestScore(), 'f', 3));
	y += 14;

	p.setFont(labelFont);
	p.setPen(QColor(0x6c, 0x70, 0x86));
	p.drawText(dashX + 6, y + 8, "Coverage");
	p.setFont(valueFont);
	p.setPen(QColor(0xa6, 0xe3, 0xa1));
	p.drawText(dashX + dashW - 38, y + 8, QString::number(GetCoverage() * 100.0, 'f', 1) + "%");
	y += 14;

	p.setFont(labelFont);
	p.setPen(QColor(0x6c, 0x70, 0x86));
	p.drawText(dashX + 6, y + 8, "Tick");
	p.setFont(valueFont);
	p.setPen(QColor(0x89, 0xb4, 0xfa));
	p.drawText(dashX + dashW - 45, y + 8, QString::number(tickCount));
	y += 18;

	// Separator
	p.setPen(QPen(QColor(0x45, 0x47, 0x5a), 1));
	p.drawLine(dashX + 8, y, dashX + dashW - 8, y);
	y += 6;

	// Per-drone status
	for (int i = 0; i < drones.size(); i++)
	{
		const auto &d = drones[i];
		if (y + 30 > dashY + dashH) break;

		// Drone color indicator
		p.setBrush(d.color);
		p.setPen(Qt::NoPen);
		p.drawEllipse(QPointF(dashX + 10, y + 6), 3, 3);

		// Name
		p.setFont(labelFont);
		p.setPen(d.color);
		p.drawText(dashX + 18, y + 9, d.name);

		// Discoveries count
		p.setPen(QColor(0x6c, 0x70, 0x86));
		p.drawText(dashX + dashW - 20, y + 9, QString::number(d.discoveries));
		y += 12;

		// Energy bar
		int barX = dashX + 18;
		int barW = dashW - 30;
		int barH = 3;
		p.fillRect(barX, y, barW, barH, QColor(0x31, 0x32, 0x44));
		QColor energyColor = d.energy > 0.3 ? QColor(0xa6, 0xe3, 0xa1)
			: d.energy > 0.1 ? QColor(0xfa, 0xb3, 0x87) : QColor(0xf3, 0x8b, 0xa8);
		p.fillRect(barX, y, static_cast<int>(barW * d.energy), barH, energyColor);
		y += 8;
	}
}

void cDroneExplorerWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		double cH, cV;
		PixelToC(event->pos().x(), event->pos().y(), cH, cV);
		emit signalDroneClicked(cH, cV);
	}
}

void cDroneExplorerWidget::resizeEvent(QResizeEvent *)
{
	update();
}

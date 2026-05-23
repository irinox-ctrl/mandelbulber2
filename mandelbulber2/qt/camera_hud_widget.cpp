/**
 * 3x3lion — Camera HUD Overlay Widget
 * Founded by Iri and Devin
 */

#include "camera_hud_widget.h"

#include <QPainterPath>
#include <cmath>

namespace
{
const QColor kBgColor(0x11, 0x11, 0x1b, 180);
const QColor kTextColor(0xcd, 0xd6, 0xf4);
const QColor kAccentBlue(0x89, 0xb4, 0xfa);
const QColor kAccentPurple(0xcb, 0xa6, 0xf7);
const QColor kAccentGreen(0xa6, 0xe3, 0xa1);
const QColor kAccentOrange(0xfa, 0xb3, 0x87);
const QColor kAccentPink(0xf5, 0xc2, 0xe7);
const QColor kWarningRed(0xf3, 0x8b, 0xa8);
const QColor kSurface(0x31, 0x32, 0x44, 200);

QString FormatScientific(double val, int precision = 3)
{
	if (std::abs(val) < 1e-3 && val != 0.0)
		return QString::number(val, 'e', precision);
	if (std::abs(val) > 1e6)
		return QString::number(val, 'e', precision);
	return QString::number(val, 'f', precision);
}
} // namespace

cCameraHUDWidget::cCameraHUDWidget(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_TransparentForMouseEvents);
	setAttribute(Qt::WA_TranslucentBackground);
	setStyleSheet("background: transparent;");
}

void cCameraHUDWidget::slotUpdateHUD(const cSmartCamera::sHUDData &data)
{
	currentData = data;
	if (hudVisible) update();
}

void cCameraHUDWidget::paintEvent(QPaintEvent *)
{
	if (!hudVisible) return;

	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);
	int w = width();
	int h = height();

	DrawTopBar(p, w);
	DrawBottomBar(p, w, h);
	DrawDepthBar(p, w, h);
	DrawModeIndicator(p, w);

	if (currentData.collisionWarning)
		DrawCollisionWarning(p, w, h);
}

void cCameraHUDWidget::DrawTopBar(QPainter &p, int w)
{
	QRect bar(0, 0, w, kBarHeight);
	p.fillRect(bar, kBgColor);

	p.setPen(kAccentBlue);
	QFont font("Monospace", 9);
	font.setStyleHint(QFont::Monospace);
	p.setFont(font);

	int x = kMargin;
	int y = kBarHeight - 8;

	// DE distance
	QString deText = "DE: " + FormatScientific(currentData.distanceToSurface);
	QColor deColor = kAccentGreen;
	if (currentData.distanceToSurface < 0.01) deColor = kAccentOrange;
	if (currentData.distanceToSurface < 0.001) deColor = kWarningRed;
	p.setPen(deColor);
	p.drawText(x, y, deText);
	x += p.fontMetrics().horizontalAdvance(deText) + 20;

	// Camera position
	p.setPen(kTextColor);
	QString camText = QString("CAM [%1, %2, %3]")
		.arg(FormatScientific(currentData.camera.x, 2))
		.arg(FormatScientific(currentData.camera.y, 2))
		.arg(FormatScientific(currentData.camera.z, 2));
	p.drawText(x, y, camText);
	x += p.fontMetrics().horizontalAdvance(camText) + 20;

	// Rotation
	p.setPen(kAccentPurple);
	QString rotText = QString("ROT [%1, %2, %3]")
		.arg(currentData.rotation.x, 0, 'f', 1)
		.arg(currentData.rotation.y, 0, 'f', 1)
		.arg(currentData.rotation.z, 0, 'f', 1);
	p.drawText(x, y, rotText);

	// FPS on the right
	p.setPen(kAccentGreen);
	QString fpsText = QString("%1 FPS").arg(currentData.fps, 0, 'f', 0);
	int fpsW = p.fontMetrics().horizontalAdvance(fpsText);
	p.drawText(w - fpsW - kMargin, y, fpsText);

	// Separator line
	p.setPen(QPen(kAccentBlue, 1));
	p.drawLine(0, kBarHeight - 1, w, kBarHeight - 1);
}

void cCameraHUDWidget::DrawBottomBar(QPainter &p, int w, int h)
{
	QRect bar(0, h - kBarHeight, w, kBarHeight);
	p.fillRect(bar, kBgColor);

	QFont font("Monospace", 9);
	font.setStyleHint(QFont::Monospace);
	p.setFont(font);

	int y = h - 8;
	int x = kMargin;

	// Camera distance to target
	p.setPen(kTextColor);
	QString distText = "DIST: " + FormatScientific(currentData.cameraDistance);
	p.drawText(x, y, distText);
	x += p.fontMetrics().horizontalAdvance(distText) + 20;

	// Target
	p.setPen(kAccentPink);
	QString tgtText = QString("TGT [%1, %2, %3]")
		.arg(FormatScientific(currentData.target.x, 2))
		.arg(FormatScientific(currentData.target.y, 2))
		.arg(FormatScientific(currentData.target.z, 2));
	p.drawText(x, y, tgtText);

	// Recording indicator
	if (currentData.isRecording)
	{
		p.setPen(kWarningRed);
		p.setBrush(kWarningRed);
		p.drawEllipse(QPoint(w - 40, h - kBarHeight / 2), 5, 5);
		p.setPen(kWarningRed);
		p.drawText(w - 30, y, "REC");
	}

	// Separator
	p.setPen(QPen(kAccentBlue, 1));
	p.drawLine(0, h - kBarHeight, w, h - kBarHeight);
}

void cCameraHUDWidget::DrawCollisionWarning(QPainter &p, int w, int h)
{
	int centerX = w / 2;
	int centerY = h / 2;

	// Pulsing red border
	p.setPen(QPen(kWarningRed, 3));
	p.setBrush(Qt::NoBrush);
	p.drawRect(2, kBarHeight + 2, w - 4, h - 2 * kBarHeight - 4);

	// Warning text
	QFont font("Monospace", 14, QFont::Bold);
	p.setFont(font);
	p.setPen(kWarningRed);

	QString warning = "COLLISION WARNING";
	int tw = p.fontMetrics().horizontalAdvance(warning);
	QRect textBg(centerX - tw / 2 - 10, centerY - 20, tw + 20, 30);
	p.fillRect(textBg, QColor(0x11, 0x11, 0x1b, 220));
	p.drawText(textBg, Qt::AlignCenter, warning);
}

void cCameraHUDWidget::DrawDepthBar(QPainter &p, int w, int h)
{
	int barX = w - 30;
	int barY = kBarHeight + 20;
	int barW = 12;
	int barH = h - 2 * kBarHeight - 40;
	if (barH < 20) return;

	// Background
	p.fillRect(barX, barY, barW, barH, kSurface);

	// DE indicator level (logarithmic scale)
	double de = currentData.distanceToSurface;
	double logDE = 0.0;
	if (de > 1e-15)
	{
		logDE = (log10(de) + 5.0) / 10.0;
		logDE = qBound(0.0, logDE, 1.0);
	}

	int fillH = static_cast<int>(logDE * barH);
	QLinearGradient grad(barX, barY + barH - fillH, barX, barY + barH);
	if (de < 0.001)
		grad.setColorAt(0, kWarningRed);
	else if (de < 0.01)
		grad.setColorAt(0, kAccentOrange);
	else
		grad.setColorAt(0, kAccentGreen);
	grad.setColorAt(1, kBgColor);

	p.fillRect(barX, barY + barH - fillH, barW, fillH, grad);

	// Border
	p.setPen(QPen(kAccentBlue, 1));
	p.drawRect(barX, barY, barW, barH);

	// Label
	QFont font("Monospace", 7);
	p.setFont(font);
	p.setPen(kTextColor);
	p.save();
	p.translate(barX - 2, barY + barH / 2);
	p.rotate(-90);
	p.drawText(0, 0, "DEPTH");
	p.restore();
}

void cCameraHUDWidget::DrawModeIndicator(QPainter &p, int w)
{
	if (currentData.modeName.isEmpty()) return;

	QFont font("Monospace", 10, QFont::Bold);
	p.setFont(font);

	QColor modeColor = kAccentBlue;
	if (currentData.modeName == "ORBIT") modeColor = kAccentPurple;
	else if (currentData.modeName == "SURFACE FOLLOW") modeColor = kAccentGreen;
	else if (currentData.modeName == "PLAYBACK") modeColor = kAccentOrange;
	else if (currentData.modeName == "SMOOTH MOVE") modeColor = kAccentPink;

	int tw = p.fontMetrics().horizontalAdvance(currentData.modeName);
	int x = (w - tw) / 2;
	int y = kBarHeight + 20;

	QRect bg(x - 8, y - 14, tw + 16, 20);
	p.fillRect(bg, kBgColor);
	p.setPen(QPen(modeColor, 1));
	p.drawRect(bg);
	p.setPen(modeColor);
	p.drawText(x, y, currentData.modeName);
}

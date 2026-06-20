/**
 * 3x3lion — Founded by Iri and Devin
 *
 * Julia Heatmap Widget — Interactive 2D heatmap of Julia c-space interest scores.
 * Shows where the most interesting Julia values lie for any fractal formula.
 * Essential infrastructure for drone-based autonomous exploration.
 */

#ifndef MANDELBULBER2_QT_JULIA_HEATMAP_WIDGET_H_
#define MANDELBULBER2_QT_JULIA_HEATMAP_WIDGET_H_

#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QVector>

class cJuliaHeatmapWidget : public QWidget
{
	Q_OBJECT

public:
	explicit cJuliaHeatmapWidget(QWidget *parent = nullptr);
	~cJuliaHeatmapWidget() override;

	// Which two axes are shown (0=cx, 1=cy, 2=cz)
	void SetAxes(int axisH, int axisV);
	int GetAxisH() const { return axisH; }
	int GetAxisV() const { return axisV; }

	// The range of c values displayed
	void SetRange(double range);
	double GetRange() const { return range; }

	// The fixed value for the third axis
	void SetFixedAxisValue(double val);
	double GetFixedAxisValue() const { return fixedAxisValue; }

	// Grid resolution (cells per axis)
	void SetResolution(int res);
	int GetResolution() const { return resolution; }

	// Set a score at a grid position
	void SetScore(int gx, int gy, double score);

	// Set the entire score grid at once
	void SetScoreGrid(const QVector<double> &scores);

	// Clear all scores
	void ClearScores();

	// Get the c-value at a pixel position
	void PixelToC(int px, int py, double &cH, double &cV) const;

	// Mark a point on the heatmap (current Julia c position)
	void SetMarker(double cH, double cV);
	void ClearMarker();

	// Scan control
	void StartScan();
	void StopScan();
	bool IsScanning() const { return scanning; }
	int GetScanProgress() const;
	void SetExternalScanActive(bool active);
	bool HasScoreData() const { return hasData; }
	const QVector<double> &GetScores() const { return scores; }

	// Color scheme
	enum eColorScheme
	{
		schemeInferno = 0,
		schemePlasma,
		schemeViridis,
		schemeMagma,
		schemeCatppuccin
	};
	void SetColorScheme(eColorScheme scheme);

signals:
	void signalCellClicked(double cH, double cV);
	void signalScanRequested(int gx, int gy, double cH, double cV);
	void signalScanProgress(int percent);
	void signalScanComplete();
	void signalHoverInfo(double cH, double cV, double score);

protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void leaveEvent(QEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;

private slots:
	void slotScanStep();

private:
	void RebuildImage();
	QColor ScoreToColor(double score) const;
	QColor InterpolateColor(const QColor &a, const QColor &b, double t) const;
	void DrawGrid(QPainter &painter) const;
	void DrawMarker(QPainter &painter) const;
	void DrawHoverTooltip(QPainter &painter) const;
	void DrawColorBar(QPainter &painter) const;
	void DrawScanProgress(QPainter &painter) const;

	int axisH = 0;  // horizontal axis (0=cx, 1=cy, 2=cz)
	int axisV = 1;  // vertical axis
	double range = 2.0;
	double fixedAxisValue = 0.0;
	int resolution = 32;

	QVector<double> scores;  // resolution * resolution grid
	double maxScore = 0.0;
	bool hasData = false;

	QImage heatmapImage;
	bool imageDirty = true;

	// Marker (current Julia c position)
	bool showMarker = false;
	double markerH = 0.0;
	double markerV = 0.0;

	// Hover state
	bool hovering = false;
	int hoverX = 0;
	int hoverY = 0;

	// Scan state
	QTimer *scanTimer = nullptr;
	bool scanning = false;
	int scanX = 0;
	int scanY = 0;

	eColorScheme colorScheme = schemeCatppuccin;

	// Padding for color bar and labels
	static constexpr int kColorBarWidth = 16;
	static constexpr int kPadding = 4;
	static constexpr int kLabelSpace = 20;
};

#endif /* MANDELBULBER2_QT_JULIA_HEATMAP_WIDGET_H_ */

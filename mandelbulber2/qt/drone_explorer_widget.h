/**
 * 3x3lion — Founded by Iri and Devin
 *
 * Drone Explorer Widget — Visual prototype for autonomous Julia c-space exploration.
 * Displays animated drones navigating interest hotspots with trails and discovery markers.
 */

#ifndef MANDELBULBER2_QT_DRONE_EXPLORER_WIDGET_H_
#define MANDELBULBER2_QT_DRONE_EXPLORER_WIDGET_H_

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QPointF>
#include <QColor>

struct sDroneState
{
	QPointF pos;       // current position in c-space
	QPointF vel;       // velocity vector
	QPointF target;    // current target
	QColor color;      // drone accent color
	QString name;      // drone identifier
	double bestScore;  // best score found by this drone
	int discoveries;   // number of hotspots found
	QVector<QPointF> trail;       // movement trail
	QVector<QPointF> hotspots;    // discovered hotspot positions
	QVector<double> hotspotScores; // scores at discovered positions
	bool hasTarget;
	double heading;    // heading angle in radians
	double energy;     // remaining energy (0-1)
};

class cDroneExplorerWidget : public QWidget
{
	Q_OBJECT

public:
	explicit cDroneExplorerWidget(QWidget *parent = nullptr);
	~cDroneExplorerWidget() override;

	void SetRange(double r);
	void SetScoreGrid(const QVector<double> &scores, int resolution);
	void StartFleet();
	void StopFleet();
	void ResetFleet();
	bool IsRunning() const { return running; }
	int GetDroneCount() const { return drones.size(); }
	void SetSpeed(double s);
	void SetStrategy(int strategyIndex);

	int GetTotalDiscoveries() const;
	double GetBestScore() const;
	double GetCoverage() const;

signals:
	void signalDroneDiscovery(int droneIdx, double cH, double cV, double score);
	void signalFleetStatus(int discoveries, double bestScore, double coverage);
	void signalDroneClicked(double cH, double cV);

protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;

private slots:
	void slotAnimationStep();

private:
	void InitDrones();
	void UpdateDrone(sDroneState &drone);
	void ChooseTarget(sDroneState &drone);
	double SampleScore(double cH, double cV) const;
	QPointF CToPixel(double cH, double cV) const;
	void PixelToC(int px, int py, double &cH, double &cV) const;

	void DrawBackground(QPainter &p) const;
	void DrawHeatmapOverlay(QPainter &p) const;
	void DrawGrid(QPainter &p) const;
	void DrawTrails(QPainter &p) const;
	void DrawHotspots(QPainter &p) const;
	void DrawDrones(QPainter &p) const;
	void DrawDashboard(QPainter &p) const;
	void DrawRadar(QPainter &p, const sDroneState &drone, int x, int y, int size) const;

	QVector<sDroneState> drones;
	QTimer *animTimer = nullptr;
	bool running = false;
	double range = 0.5;
	double speed = 1.0;
	int strategy = 0; // 0=explore, 1=exploit, 2=swarm
	int tickCount = 0;

	// Score grid from heatmap
	QVector<double> scoreGrid;
	int gridResolution = 0;
	double gridMaxScore = 0.0;

	// Visited cells tracking for coverage
	QVector<bool> visited;

	// Drone colors (Catppuccin)
	static constexpr int kDroneCount = 5;
	static const QColor kDroneColors[];
	static const char *kDroneNames[];

	// Layout
	static constexpr int kDashboardWidth = 140;
	static constexpr int kPadding = 4;
};

#endif /* MANDELBULBER2_QT_DRONE_EXPLORER_WIDGET_H_ */

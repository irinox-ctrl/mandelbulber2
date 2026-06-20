/**
 * Hybrid section timeline — visual iteration ranges for all 9 formula slots.
 */

#ifndef MANDELBULBER2_QT_HYBRID_SECTION_TIMELINE_WIDGET_H_
#define MANDELBULBER2_QT_HYBRID_SECTION_TIMELINE_WIDGET_H_

#include <QVector>
#include <QWidget>

class cHybridSectionTimelineWidget : public QWidget
{
	Q_OBJECT

public:
	struct sSectionInfo
	{
		int slot = 0;
		QString name;
		int startIter = 0;
		int stopIter = 0;
		double weight = 1.0;
		int fadeIn = 0;
		int fadeOut = 0;
		bool enabled = true;
	};

	explicit cHybridSectionTimelineWidget(QWidget *parent = nullptr);

	void SetSections(const QVector<sSectionInfo> &sections, int globalN, int viewMaxIter);
	void SetHybridSequence(const QVector<int> &sequence);
	void SetPlayheadIteration(int iter);
	int PlayheadIteration() const { return playheadIter; }
	QString SequenceStatusAt(int iter) const;

	QSize sizeHint() const override;
	QSize minimumSizeHint() const override;

signals:
	void signalIterationClicked(int iteration, int slot);
	void signalSlotSelected(int slot);
	void signalRangeChanged(int slot, int startIter, int stopIter);
	void signalSectionCopied(int fromSlot, int toSlot, int startIter, int stopIter, double weight,
		int fadeIn, int fadeOut);

protected:
	void paintEvent(QPaintEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void leaveEvent(QEvent *event) override;

private:
	enum eHitType
	{
		hitNone = 0,
		hitRuler,
		hitBarStart,
		hitBarStop,
		hitBarMove,
		hitBarDuplicate
	};

	struct sHitResult
	{
		eHitType type = hitNone;
		int row = -1;
	};

	struct sChartGeom
	{
		int chartLeft = 0;
		int chartWidth = 0;
	};

	sChartGeom ChartGeom() const;
	double IterToX(int iter, const sChartGeom &g) const;
	int XToIter(int x, const sChartGeom &g) const;
	int RowAtY(int y) const;
	sHitResult HitTest(const QPoint &pos) const;
	QRect BarRect(int row, const sChartGeom &g) const;
	void UpdateHoverCursor(const QPoint &pos);
	int SlotAtIteration(int iter) const;
	QString BuildRowTooltip(const sSectionInfo &sec, const sHitResult &hit, int iterAtCursor) const;

	QVector<sSectionInfo> sections;
	QVector<int> hybridSequence;
	int globalN = 250;
	int viewMaxIter = 250;
	int playheadIter = -1;
	int hoverRow = -1;

	eHitType dragType = hitNone;
	int dragRow = -1;
	int duplicateTargetRow = -1;
	int dragAnchorIter = 0;
	int dragStartIter = 0;
	int dragStopIter = 0;
};

#endif // MANDELBULBER2_QT_HYBRID_SECTION_TIMELINE_WIDGET_H_

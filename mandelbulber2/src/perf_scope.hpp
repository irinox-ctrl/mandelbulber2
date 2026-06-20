/**
 * Lightweight performance scope logger for diagnosing UI/OpenCL stalls.
 */
#ifndef MANDELBULBER2_SRC_PERF_SCOPE_HPP_
#define MANDELBULBER2_SRC_PERF_SCOPE_HPP_

#include <QElapsedTimer>
#include <QString>

#include "write_log.hpp"

class cPerfScope
{
public:
	explicit cPerfScope(const QString &scopeName, int logThresholdMs = 20)
			: name(scopeName), thresholdMs(logThresholdMs)
	{
		timer.start();
	}

	~cPerfScope()
	{
		const qint64 ms = timer.elapsed();
		if (ms >= thresholdMs)
		{
			WriteLog(QString("[PERF] %1: %2 ms").arg(name).arg(ms), 1);
		}
	}

private:
	QString name;
	int thresholdMs;
	QElapsedTimer timer;
};

#define PERF_SCOPE(name) cPerfScope perfScope_##__LINE__(name)

#endif /* MANDELBULBER2_SRC_PERF_SCOPE_HPP_ */

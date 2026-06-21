/**
 * Mandelbulber v2 — RAII guard for safe UI parameter transactions
 */

#ifndef MANDELBULBER2_SRC_UI_TRANSACTION_HPP_
#define MANDELBULBER2_SRC_UI_TRANSACTION_HPP_

#include <QString>

class cUiTransaction
{
public:
	explicit cUiTransaction(const QString &reason = QString());
	~cUiTransaction();

	void RequestRender(int debounceMs = 80, bool noUndo = false);
	void MarkParamsDirty();
	void MarkUiDirty();

	static bool IsActive();
	static int NestingDepth();

private:
	QString reason;
	int debounceMs = 80;
	bool noUndo = false;
	bool renderRequested = false;
	bool paramsDirty = false;
	bool uiDirty = false;
	bool ownsSyncLock = false;
	bool ownsBatchUpdate = false;

	static int nestingDepth;
};

#endif /* MANDELBULBER2_SRC_UI_TRANSACTION_HPP_ */

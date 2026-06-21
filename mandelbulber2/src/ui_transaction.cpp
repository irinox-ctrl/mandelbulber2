/**
 * Mandelbulber v2 — RAII guard for safe UI parameter transactions
 */

#include "ui_transaction.hpp"

#include <QTimer>

#include "fractal_container.hpp"
#include "global_data.hpp"
#include "initparameters.hpp"
#include "interface.hpp"
#include "render_window.hpp"
#include "ui_parameter_validator.hpp"
#include "qt/dock_statistics.h"

int cUiTransaction::nestingDepth = 0;

cUiTransaction::cUiTransaction(const QString &reason) : reason(reason)
{
	if (nestingDepth == 0)
	{
		if (gMainInterface && !gMainInterface->IsBatchUpdateInProgress())
		{
			gMainInterface->BeginBatchUpdate();
			ownsBatchUpdate = true;
		}
		gInterfaceReadyForSynchronization = false;
		ownsSyncLock = true;
	}
	++nestingDepth;
}

cUiTransaction::~cUiTransaction()
{
	--nestingDepth;
	if (nestingDepth > 0) return;

	const QString capturedReason = reason;
	const int capturedDebounceMs = debounceMs;
	const bool capturedNoUndo = noUndo;
	const bool capturedRenderRequested = renderRequested;
	const bool capturedParamsDirty = paramsDirty;
	const bool capturedUiDirty = uiDirty;
	const bool capturedOwnsBatchUpdate = ownsBatchUpdate;

	QTimer::singleShot(0, qApp, [=]() {
		if (capturedParamsDirty && gMainInterface)
		{
			gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
			RepairUiParameters(gPar, gParFractal);
			if (gMainInterface && gMainInterface->mainWindow)
			{
				if (cDockStatistics *dockStatistics = gMainInterface->mainWindow->GetWidgetDockStatistics())
					dockStatistics->UpdateValidationStatus();
			}
			gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
		}
		else if (capturedUiDirty && gMainInterface)
		{
			gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
		}

		gInterfaceReadyForSynchronization = true;

		if (capturedOwnsBatchUpdate && gMainInterface)
			gMainInterface->EndBatchUpdate();

		if (capturedRenderRequested && gMainInterface)
			gMainInterface->RequestRender(capturedReason, capturedDebounceMs, capturedNoUndo);
	});
}

void cUiTransaction::RequestRender(const int debounceMs, const bool noUndo)
{
	this->debounceMs = debounceMs;
	this->noUndo = noUndo;
	renderRequested = true;
}

void cUiTransaction::MarkParamsDirty()
{
	paramsDirty = true;
}

void cUiTransaction::MarkUiDirty()
{
	uiDirty = true;
}

bool cUiTransaction::IsActive()
{
	return nestingDepth > 0;
}

int cUiTransaction::NestingDepth()
{
	return nestingDepth;
}

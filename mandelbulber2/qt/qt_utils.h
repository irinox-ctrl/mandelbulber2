/**
 * Mandelbulber v2 — shared Qt UI helpers
 */
#ifndef MANDELBULBER2_QT_QT_UTILS_H_
#define MANDELBULBER2_QT_QT_UTILS_H_

#include "src/interface.hpp"

#define CHECK_MAIN_INTERFACE() \
	do { \
		if (!gMainInterface || !gMainInterface->mainWindow) return; \
	} while (0)

#define CHECK_PARAMS() \
	do { \
		if (!params) return; \
	} while (0)

#endif // MANDELBULBER2_QT_QT_UTILS_H_

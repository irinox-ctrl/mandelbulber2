/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2025 Mandelbulber Team        §R-==%w["'~5]m%=L.=~5N
 *                                        ,=mm=§M ]=4 yJKA"/-Nsaj  "Bw,==,,
 * This file is part of Mandelbulber.    §R.r= jw",M  Km .mM  FW ",§=ß., ,TN
 *                                     ,4R =%["w[N=7]J '"5=],""]]M,w,-; T=]M
 * Mandelbulber is free software:     §R.ß~-Q/M=,=5"v"]=Qf,'§"M= =,M.§ Rz]M"Kw
 * you can redistribute it and/or     §w "xDY.J ' -"m=====WeC=\ ""%""y=%"]"" §
 * modify it under the terms of the    "§M=M =D=4"N #"%==A%p M§ M6  R' #"=~.4M
 * GNU General Public License as        §W =, ][T"]C  §  § '§ e===~ U  !§[Z ]N
 * published by the                    4M",,Jm=,"=e~  §  §  j]]""N  BmM"py=ßM
 * Free Software Foundation,          ]§ T,M=& 'YmMMpM9MMM%=w=,,=MT]M m§;'§,
 * either version 3 of the License,    TWw [.j"5=~N[=§%=%W,T ]R,"=="Y[LFT ]N
 * or (at your option)                   TW=,-#"%=;[  =Q:["V""  ],,M.m == ]N
 * any later version.                      J§"mr"] ,=,," =="""J]= M"M"]==ß"
 *                                          §= "=C=4 §"eM "=B:m|4"]#F,§~
 * Mandelbulber is distributed in            "9w=,,]w em%wJ '"~" ,=,,ß"
 * the hope that it will be useful,                 . "K=  ,=RMMMßM"""
 * but WITHOUT ANY WARRANTY;                            .'''
 * without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with Mandelbulber. If not, see <http://www.gnu.org/licenses/>.
 *
 * ###########################################################################
 *
 * Authors: Joeri (DOF auto-focus logging module)
 *
 * Structured logging for DOF auto-focus operations.
 * Provides file, line, function, timestamp, and severity level for every log entry.
 * Zero breaking changes to existing WriteLog() calls.
 */

#ifndef MANDELBULBER2_SRC_DOF_LOG_HPP_
#define MANDELBULBER2_SRC_DOF_LOG_HPP_

#include <QString>

// Undefine Windows API macros that clash with our enum names
#ifdef ERROR
#undef ERROR
#endif
#ifdef DEBUG
#undef DEBUG
#endif

// Log severity levels for DOF auto-focus operations.
// Mapped to existing Mandelbulber verbosity levels (1-3) for compatibility.
enum class DOFLogLevel
{
	LvlError = 1, // Critical failures that prevent auto-focus from working
	LvlWarn = 1,  // Warnings that may affect result quality
	LvlInfo = 2,  // Major decisions (which path taken, key values)
	LvlDebug = 3, // Detailed diagnostics (sample counts, percentiles)
	LvlTrace = 3  // Per-pixel or per-probe values (very verbose)
};

// Core structured logging function.
// Prepends [timestamp][level][file:line function] to the message,
// then delegates to the existing WriteLog() infrastructure.
// Do not call directly — use the LOG_DOF* macros below.
void DOFLog(DOFLogLevel level, const char *file, int line, const char *func, const QString &message);

// Convenience overload for printf-style formatting.
void DOFLogFmt(
	DOFLogLevel level, const char *file, int line, const char *func, const char *fmt, ...);

// ---------------------------------------------------------------------------
// Macros — these are the public API.
// Usage: LOG_INFO("Auto-focus started")
//        LOG_DEBUG("z-buffer samples: " + QString::number(count))
//        LOG_DOF_FMT(DOFLogLevel::LvlDebug, "median = %.4f", median)
// ---------------------------------------------------------------------------

#define LOG_DOF(level, msg) DOFLog(level, __FILE__, __LINE__, Q_FUNC_INFO, msg)

#define LOG_DOF_FMT(level, fmt, ...) \
	DOFLogFmt(level, __FILE__, __LINE__, Q_FUNC_INFO, fmt, __VA_ARGS__)

#define LOG_ERROR(msg) LOG_DOF(DOFLogLevel::LvlError, msg)
#define LOG_WARN(msg) LOG_DOF(DOFLogLevel::LvlWarn, msg)
#define LOG_INFO(msg) LOG_DOF(DOFLogLevel::LvlInfo, msg)
#define LOG_DEBUG(msg) LOG_DOF(DOFLogLevel::LvlDebug, msg)
#define LOG_TRACE(msg) LOG_DOF(DOFLogLevel::LvlTrace, msg)

#endif /* MANDELBULBER2_SRC_DOF_LOG_HPP_ */

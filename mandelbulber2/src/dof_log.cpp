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
 */

#include "dof_log.hpp"

#include <cstdarg>

#include <QDateTime>

#include "system_data.hpp"
#include "write_log.hpp"

using namespace std;

// ---------------------------------------------------------------------------
// Helper: strip directory path from __FILE__ → filename only.
// ---------------------------------------------------------------------------
static QString ExtractFileName(const char *filePath)
{
	QString s(filePath);
	int lastSlash = s.lastIndexOf('/');
	if (lastSlash >= 0) return s.mid(lastSlash + 1);
	int lastBackslash = s.lastIndexOf('\\');
	if (lastBackslash >= 0) return s.mid(lastBackslash + 1);
	return s;
}

// ---------------------------------------------------------------------------
// Helper: strip parameter list from Q_FUNC_INFO → "Class::function" only.
// ---------------------------------------------------------------------------
static QString ExtractFunctionName(const char *funcInfo)
{
	QString s(funcInfo);
	// Q_FUNC_INFO includes return type, parameters, and sometimes qualifiers.
	// We keep everything up to the first '('.
	int paren = s.indexOf('(');
	if (paren >= 0) s = s.left(paren);
	// Also strip "static " or "virtual " prefixes if present.
	if (s.startsWith("static ")) s = s.mid(7);
	if (s.startsWith("virtual ")) s = s.mid(8);
	return s.trimmed();
}

// ---------------------------------------------------------------------------
// Helper: convert DOFLogLevel to 3-character string and Mandelbulber verbosity.
// ---------------------------------------------------------------------------
static const char *LevelToString(DOFLogLevel level)
{
	if (level == DOFLogLevel::LvlError) return "ERR";
	if (level == DOFLogLevel::LvlWarn) return "WRN";
	if (level == DOFLogLevel::LvlInfo) return "INF";
	if (level == DOFLogLevel::LvlDebug) return "DBG";
	if (level == DOFLogLevel::LvlTrace) return "TRC";
	return "UNK";
}

static int LevelToVerbosity(DOFLogLevel level)
{
	return static_cast<int>(level);
}

// ---------------------------------------------------------------------------
// Core structured logging implementation.
// ---------------------------------------------------------------------------
void DOFLog(DOFLogLevel level, const char *file, int line, const char *func, const QString &message)
{
	int verbosity = LevelToVerbosity(level);

	// Respect the global logging verbosity setting (0 = silent, 1 = errors, 2 = main, 3 = detailed).
	if (verbosity > systemData.loggingVerbosity) return;

	QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
	QString fileName = ExtractFileName(file);
	QString funcName = ExtractFunctionName(func);

	QString structured = QString("[%1] [%2] [%3:%4 %5] %6")
										 .arg(timestamp)
										 .arg(LevelToString(level))
										 .arg(fileName)
										 .arg(line)
										 .arg(funcName)
										 .arg(message);

	WriteLog(structured, verbosity);
}

// ---------------------------------------------------------------------------
// Printf-style formatting wrapper.
// ---------------------------------------------------------------------------
void DOFLogFmt(
	DOFLogLevel level, const char *file, int line, const char *func, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	QString message = QString::vasprintf(fmt, args);
	va_end(args);

	DOFLog(level, file, line, func, message);
}

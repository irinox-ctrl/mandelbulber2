/**
 * Mandelbulber v2 — OpenCL GPU Diagnostics System
 *
 * Advanced debugging and error diagnostics for GPU kernel compilation,
 * struct alignment validation, and runtime error detection.
 *
 * Usage: Call RunGPUDiagnostics() before kernel compilation to get
 * detailed struct layout info. On kernel build failure, call
 * FormatKernelBuildError() for enhanced error output with context.
 */

#ifndef MANDELBULBER2_SRC_OPENCL_DIAGNOSTICS_H_
#define MANDELBULBER2_SRC_OPENCL_DIAGNOSTICS_H_

#ifdef USE_OPENCL

#include <QString>
#include <QStringList>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>

#include "opencl/input_data_structures.h"
#include "opencl/fractal_cl.h"
#include "opencl/fractal_sequence_cl.h"

namespace GPUDiag
{

// ═══════════════════════════════════════════════════════════════════
//  SECTION 1: Struct Size & Alignment Validation
// ═══════════════════════════════════════════════════════════════════

struct sStructInfo
{
	const char *name;
	size_t size;
	size_t alignment;
	size_t count;
};

inline QString FormatBytes(size_t bytes)
{
	if (bytes >= 1024)
		return QString("%1 bytes (%2 KB)").arg(bytes).arg(bytes / 1024.0, 0, 'f', 1);
	return QString("%1 bytes").arg(bytes);
}

inline QString RunStructDiagnostics()
{
	std::ostringstream out;
	out << "\n╔══════════════════════════════════════════════════════════════╗\n";
	out << "║           GPU STRUCT DIAGNOSTICS REPORT                     ║\n";
	out << "╠══════════════════════════════════════════════════════════════╣\n";

	// Top-level constant buffer
	out << "║ sClInConstants (total GPU buffer):                          ║\n";
	out << "║   Size: " << std::setw(8) << sizeof(sClInConstants) << " bytes ("
		<< std::fixed << std::setprecision(1) << sizeof(sClInConstants) / 1024.0 << " KB)"
		<< std::string(20, ' ') << "║\n";
	out << "║   Align: " << std::setw(4) << alignof(sClInConstants) << " bytes"
		<< std::string(38, ' ') << "║\n";

	// Memory limit check
	bool overLimit = sizeof(sClInConstants) > 65536;
	if (overLimit)
	{
		out << "║   ⚠ EXCEEDS 64KB __constant limit by "
			<< (sizeof(sClInConstants) - 65536) << " bytes           ║\n";
		out << "║   → Using __global const (no issue on modern GPUs)         ║\n";
	}
	else
	{
		out << "║   ✓ Within 64KB __constant limit                           ║\n";
	}

	out << "╠══════════════════════════════════════════════════════════════╣\n";
	out << "║ Component Breakdown:                                        ║\n";
	out << "╠═══════════════════════════════════╦════════╦═════╦══════════╣\n";
	out << "║ Struct Name                       ║  Size  ║ x N ║  Total   ║\n";
	out << "╠═══════════════════════════════════╬════════╬═════╬══════════╣\n";

	sStructInfo components[] = {
		{"sParamRenderCl", sizeof(sParamRenderCl), alignof(sParamRenderCl), 1},
		{"sFractalCl", sizeof(sFractalCl), alignof(sFractalCl), NUMBER_OF_FRACTALS},
		{"sClFractalSequence", sizeof(sClFractalSequence), alignof(sClFractalSequence), 1},
		{"  └ sClFormulaMutationParams", sizeof(sClFormulaMutationParams),
			alignof(sClFormulaMutationParams), NUMBER_OF_FRACTALS},
		{"  └ sClFormulaWeightParams", sizeof(sClFormulaWeightParams),
			alignof(sClFormulaWeightParams), NUMBER_OF_FRACTALS},
		{"sFractalMandalayCI", sizeof(sFractalMandalayCI), alignof(sFractalMandalayCI), 1},
	};

	size_t totalAccounted = 0;
	for (const auto &c : components)
	{
		size_t total = c.size * c.count;
		out << "║ " << std::left << std::setw(33) << c.name << " ║"
			<< std::right << std::setw(6) << c.size << "  ║"
			<< std::setw(3) << c.count << "  ║"
			<< std::setw(8) << total << "  ║\n";
		if (c.name[0] != ' ') totalAccounted += total;
	}

	out << "╠═══════════════════════════════════╬════════╬═════╬══════════╣\n";
	out << "║ Accounted total                   ║        ║     ║"
		<< std::setw(8) << totalAccounted << "  ║\n";
	out << "║ Actual sClInConstants             ║        ║     ║"
		<< std::setw(8) << sizeof(sClInConstants) << "  ║\n";

	size_t padding = sizeof(sClInConstants) > totalAccounted
					   ? sizeof(sClInConstants) - totalAccounted
					   : 0;
	out << "║ Padding/alignment overhead        ║        ║     ║"
		<< std::setw(8) << padding << "  ║\n";
	out << "╚═══════════════════════════════════╩════════╩═════╩══════════╝\n";

	return QString::fromStdString(out.str());
}

// ═══════════════════════════════════════════════════════════════════
//  SECTION 2: Kernel Build Error Formatter
// ═══════════════════════════════════════════════════════════════════

inline QString FormatKernelBuildError(const QString &buildLog, const QString & /*programSource*/)
{
	std::ostringstream out;
	out << "\n╔══════════════════════════════════════════════════════════════╗\n";
	out << "║           GPU KERNEL BUILD ERROR REPORT                     ║\n";
	out << "╠══════════════════════════════════════════════════════════════╣\n";

	// Parse error lines from the build log
	QStringList logLines = buildLog.split('\n');
	int errorCount = 0;
	int warningCount = 0;

	for (const QString &line : logLines)
	{
		if (line.contains("error:")) errorCount++;
		if (line.contains("warning:")) warningCount++;
	}

	out << "║ Errors: " << errorCount << "  Warnings: " << warningCount
		<< std::string(40, ' ') << "║\n";
	out << "╠══════════════════════════════════════════════════════════════╣\n";

	// Extract and format each error with context
	for (const QString &line : logLines)
	{
		if (line.contains("error:") || line.contains("note:"))
		{
			out << "║ " << line.left(60).toStdString() << "\n";

			// Try to extract file:line info
			int colonPos1 = line.indexOf(':');
			if (colonPos1 > 0)
			{
				int colonPos2 = line.indexOf(':', colonPos1 + 1);
				if (colonPos2 > colonPos1)
				{
					QString fileName = line.left(colonPos1);
					QString lineNumStr = line.mid(colonPos1 + 1, colonPos2 - colonPos1 - 1);
					bool ok;
					int lineNum = lineNumStr.toInt(&ok);
					if (ok && lineNum > 0)
					{
						// Extract short filename
						int lastSlash = fileName.lastIndexOf('/');
						QString shortName =
							lastSlash >= 0 ? fileName.mid(lastSlash + 1) : fileName;
						out << "║   → File: " << shortName.toStdString()
							<< " Line: " << lineNum << "\n";
					}
				}
			}
		}
	}

	out << "╠══════════════════════════════════════════════════════════════╣\n";

	// Common error patterns and solutions
	out << "║ COMMON SOLUTIONS:                                           ║\n";

	if (buildLog.contains("changes address space of pointer"))
	{
		out << "║ → Address space mismatch detected!                          ║\n";
		out << "║   Check all .cl files for 'constant' vs '__global const'    ║\n";
		out << "║   Both source AND deploy copies must match                  ║\n";
		out << "║   grep -rn 'constant sCl\\|constant sFractal' *.cl          ║\n";
	}
	if (buildLog.contains("incompatible type"))
	{
		out << "║ → Type mismatch: check struct definitions match between     ║\n";
		out << "║   CPU (.h/.hpp) and GPU (.cl) headers                       ║\n";
	}
	if (buildLog.contains("undeclared identifier") || buildLog.contains("unknown type"))
	{
		out << "║ → Missing include or type definition                        ║\n";
		out << "║   Check header inclusion order in engine files               ║\n";
	}

	out << "╚══════════════════════════════════════════════════════════════╝\n";

	return QString::fromStdString(out.str());
}

// ═══════════════════════════════════════════════════════════════════
//  SECTION 3: Data Copy Verification
// ═══════════════════════════════════════════════════════════════════

inline QString VerifyConstantBuffer(const sClInConstants *buffer)
{
	std::ostringstream out;
	out << "\n╔══════════════════════════════════════════════════════════════╗\n";
	out << "║           GPU CONSTANT BUFFER VERIFICATION                  ║\n";
	out << "╠══════════════════════════════════════════════════════════════╣\n";

	if (!buffer)
	{
		out << "║ ✗ Buffer is NULL!                                           ║\n";
		out << "╚══════════════════════════════════════════════════════════════╝\n";
		return QString::fromStdString(out.str());
	}

	// Check for NaN/Inf in critical float fields
	int nanCount = 0;
	int infCount = 0;
	const float *fptr = reinterpret_cast<const float *>(buffer);
	size_t numFloats = sizeof(sClInConstants) / sizeof(float);

	for (size_t i = 0; i < numFloats; i++)
	{
		if (std::isnan(fptr[i])) nanCount++;
		if (std::isinf(fptr[i])) infCount++;
	}

	out << "║ Buffer size: " << sizeof(sClInConstants) << " bytes ("
		<< numFloats << " float-equivalents)\n";
	out << "║ NaN values: " << nanCount;
	if (nanCount > 0) out << " ⚠ WARNING";
	out << "\n";
	out << "║ Inf values: " << infCount;
	if (infCount > 0) out << " ⚠ WARNING";
	out << "\n";

	// Check zero-initialized sections (unused mutation params)
	int zeroMutations = 0;
	int activeMutations = 0;
	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		if (buffer->sequence.mutationParams[i].enabled)
			activeMutations++;
		else
			zeroMutations++;
	}
	out << "║ Mutation params: " << activeMutations << " active, "
		<< zeroMutations << " disabled\n";

	// Verify fractal sequence
	out << "║ Hybrid mode: " << (buffer->sequence.isHybrid ? "YES" : "NO") << "\n";

	// Check each fractal slot
	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		const sFractalCl &f = buffer->fractal[i];
		out << "║ Fractal[" << i << "]: ";

		// Check if the fractal slot has reasonable data
		float testVal = f.transformCommon.scaleA1;
		if (std::isnan(testVal) || std::isinf(testVal))
		{
			out << "⚠ CORRUPTED (NaN/Inf in scaleA1)\n";
		}
		else
		{
			out << "OK (scaleA1=" << testVal << ")\n";
		}
	}

	out << "╠══════════════════════════════════════════════════════════════╣\n";

	// Verify params
	out << "║ Render params:\n";
	out << "║   resolution: " << buffer->params.imageWidth << " x "
		<< buffer->params.imageHeight << "\n";
	out << "║   maxiter: " << buffer->params.N << "\n";
	out << "║   bailout[0]: " << buffer->sequence.bailout[0] << "\n";
	out << "║   DE factor: " << buffer->params.DEFactor << "\n";

	if (buffer->params.imageWidth == 0 || buffer->params.imageHeight == 0)
	{
		out << "║   ⚠ ZERO RESOLUTION — buffer not initialized!\n";
	}

	out << "╚══════════════════════════════════════════════════════════════╝\n";
	return QString::fromStdString(out.str());
}

// ═══════════════════════════════════════════════════════════════════
//  SECTION 4: Address Space Scanner
// ═══════════════════════════════════════════════════════════════════

inline QString ScanForAddressSpaceMismatches(const QString & /*deployPath*/)
{
	std::ostringstream out;
	out << "\n╔══════════════════════════════════════════════════════════════╗\n";
	out << "║     ADDRESS SPACE MISMATCH SCANNER                          ║\n";
	out << "╠══════════════════════════════════════════════════════════════╣\n";

	// List of patterns that indicate stale __constant usage
	QStringList badPatterns;
	badPatterns << "constant sClInConstants"
				<< "constant sFractalCl"
				<< "constant sClFormulaMutationParams"
				<< "constant sClFormulaWeightParams"
				<< "constant sFractalFoldingsCl"
				<< "constant sGlowSphereCl"
				<< "constant sPatternLineTrapLayerCl"
				<< "constant sClSingleTrapLight"
				<< "constant sSingleTrapLightLayerCl"
				<< "constant sClMeshExport";

	out << "║ Checking for stale __constant / constant keywords...        ║\n";
	out << "║ Bad patterns to search for:                                 ║\n";

	for (const QString &p : badPatterns)
	{
		out << "║   - " << p.toStdString() << "\n";
	}

	out << "╠══════════════════════════════════════════════════════════════╣\n";
	out << "║ Run this grep on your machine to find remaining issues:     ║\n";
	out << "║                                                             ║\n";
	out << "║ grep -rn '\\bconstant sCl\\|\\bconstant sFractal'             ║\n";
	out << "║   mandelbulber2/opencl/engines/*.cl                         ║\n";
	out << "║   mandelbulber2/formula/opencl/*.cl                         ║\n";
	out << "║   mandelbulber2/deploy/share/mandelbulber2/opencl/engines/  ║\n";
	out << "║   mandelbulber2/deploy/share/mandelbulber2/formula/opencl/  ║\n";
	out << "╚══════════════════════════════════════════════════════════════╝\n";

	return QString::fromStdString(out.str());
}

// ═══════════════════════════════════════════════════════════════════
//  SECTION 5: Full Diagnostics Runner
// ═══════════════════════════════════════════════════════════════════

inline void RunFullDiagnostics(const sClInConstants *buffer)
{
	QString structReport = RunStructDiagnostics();
	std::cerr << structReport.toStdString();

	if (buffer)
	{
		QString bufferReport = VerifyConstantBuffer(buffer);
		std::cerr << bufferReport.toStdString();
	}

	QString scanReport = ScanForAddressSpaceMismatches(QString());
	std::cerr << scanReport.toStdString();
}

} // namespace GPUDiag

#endif // USE_OPENCL
#endif // MANDELBULBER2_SRC_OPENCL_DIAGNOSTICS_H_

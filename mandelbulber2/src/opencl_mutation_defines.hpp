/**
 * Shared OpenCL compile defines for the mutation subsystem.
 * Used by fractal and nebula render engines.
 */

#ifndef MANDELBULBER2_SRC_OPENCL_MUTATION_DEFINES_HPP_
#define MANDELBULBER2_SRC_OPENCL_MUTATION_DEFINES_HPP_

#include <set>

#include <QString>

class cNineFractals;

void AppendMutationOpenClDefines(const cNineFractals *fractals, QString &definesCollector);

#endif /* MANDELBULBER2_SRC_OPENCL_MUTATION_DEFINES_HPP_ */

/**
 * Pattern line traps — OpenCL struct
 */

#ifndef MANDELBULBER2_OPENCL_PATTERN_LINE_TRAPS_CL_HPP_
#define MANDELBULBER2_OPENCL_PATTERN_LINE_TRAPS_CL_HPP_

#ifndef OPENCL_KERNEL_CODE
#include <cstddef>
#include "opencl_algebra.h"
#include "src/pattern_line_traps.hpp"
#else
#define PATTERN_LINE_TRAP_COUNT 20
#endif

typedef struct
{
	cl_int enabled;
	cl_float4 position;
	matrix33 mRotRotation;
	cl_float radius;
	cl_float thickness;
	cl_float scale;
	cl_float relativeThickness;
	cl_float edgeSoftness;
	cl_float intensity;
	cl_float maxDistance;
	cl_float falloffSharpness;
	cl_float glowSpread;
	cl_int falloffProfile;
	cl_int edgeSide;
	cl_float segmentHalfLength;
	cl_int shape;
	cl_float shapeAux;
	cl_float relativeSize;
	/* cl_float4 needs 16-byte alignment; 4 bytes explicit padding (host + OpenCL C must match). */
	cl_int _padAlignBeforeColors[1];
	cl_float4 color;
	cl_float4 color2;
	cl_float4 color3;
} sPatternLineTrapLayerCl;

#ifndef OPENCL_KERNEL_CODE
/* If these fail, update clCopyPatternLineTrapLayer and kernel uses of sPatternLineTrapLayerCl. */
static_assert(sizeof(sPatternLineTrapLayerCl) == 192, "sPatternLineTrapLayerCl size drift");
static_assert(offsetof(sPatternLineTrapLayerCl, falloffSharpness) == 108, "falloff field offset");
static_assert(offsetof(sPatternLineTrapLayerCl, _padAlignBeforeColors) == 140, "padding before colors");
static_assert(offsetof(sPatternLineTrapLayerCl, color) == 144, "color field offset");
#endif

typedef struct
{
	cl_int enabled;
	cl_int soloLayerIndex;
	cl_int combineMode;
	cl_int coloringMode;
	sPatternLineTrapLayerCl layers[PATTERN_LINE_TRAP_COUNT];
} sPatternLineTrapsCl;

#ifndef OPENCL_KERNEL_CODE
inline sPatternLineTrapLayerCl clCopyPatternLineTrapLayer(const sPatternLineTrapLayer &source)
{
	sPatternLineTrapLayerCl target{};
	target.enabled = source.enabled ? 1 : 0;
	target.position = toClFloat3(source.position);
	target.mRotRotation = toClMatrix33(source.mRotRotation);
	target.radius = cl_float(source.radius);
	target.thickness = cl_float(source.thickness);
	target.scale = cl_float(source.scale);
	target.relativeThickness = cl_float(source.relativeThickness);
	target.edgeSoftness = cl_float(source.edgeSoftness);
	target.intensity = cl_float(source.intensity);
	target.maxDistance = cl_float(source.maxDistance);
	target.falloffSharpness = cl_float(source.falloffSharpness);
	target.glowSpread = cl_float(source.glowSpread);
	target.falloffProfile = cl_int(source.falloffProfile);
	target.edgeSide = cl_int(source.edgeSide);
	target.segmentHalfLength = cl_float(source.segmentHalfLength);
	target.shape = cl_int(source.shape);
	target.shapeAux = cl_float(source.shapeAux);
	target.relativeSize = cl_float(source.relativeSize);
	target.color = toClFloat3(source.color);
	target.color2 = toClFloat3(source.color2);
	target.color3 = toClFloat3(source.color3);
	return target;
}

inline sPatternLineTrapsCl clCopyPatternLineTraps(const sPatternLineTraps &source)
{
	sPatternLineTrapsCl target{};
	target.enabled = source.enabled ? 1 : 0;
	target.soloLayerIndex = cl_int(source.soloLayerIndex);
	target.combineMode = cl_int(source.combineMode);
	target.coloringMode = cl_int(source.coloringMode);
	for (int i = 0; i < PATTERN_LINE_TRAP_COUNT; i++)
		target.layers[i] = clCopyPatternLineTrapLayer(source.layers[i]);
	return target;
}
#endif

#endif /* MANDELBULBER2_OPENCL_PATTERN_LINE_TRAPS_CL_HPP_ */

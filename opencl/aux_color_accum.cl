/**
 * aux.color accumulation modes for mutation orbit-trap coloring.
 */

#ifndef MANDELBULBER2_OPENCL_AUX_COLOR_ACCUM_CL_
#define MANDELBULBER2_OPENCL_AUX_COLOR_ACCUM_CL_

// mode 0: min, 1: sum, 2: smooth-min (log-sum-exp)
inline void AccumulateAuxColor(__private float *auxColor, const float tv, const int mode,
	const float weight, const float softness)
{
	if (mode == 1)
		*auxColor += tv * weight;
	else if (mode == 2)
	{
		const float k = fmax(softness, 1e-6f);
		*auxColor = -native_log(native_exp(-k * (*auxColor)) + native_exp(-k * tv)) / k;
	}
	else if (tv < *auxColor)
		*auxColor = tv;
}

#endif /* MANDELBULBER2_OPENCL_AUX_COLOR_ACCUM_CL_ */

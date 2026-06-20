/**
 * Shared mutation clip helpers for OpenCL (CPU parity via compute_fractal.cpp).
 */

#ifndef MANDELBULBER2_OPENCL_MUTATION_CLIP_CL_
#define MANDELBULBER2_OPENCL_MUTATION_CLIP_CL_

inline float3 MutationClipPushToSurface(float3 cz, float clipDist)
{
	if (clipDist >= 0.0f) return cz;
	float r = length(cz);
	if (r < 1e-21f) return cz;
	return cz * ((r - clipDist) / r);
}

inline void ApplyClipBooleanOp(__private float *auxDist, const float clipDist, const int bop,
	const float clipSmoothK)
{
	if (bop == 0)
		*auxDist = max(*auxDist, clipDist); // Intersection (AND)
	else if (bop == 1)
		*auxDist = min(*auxDist, clipDist); // Union (OR)
	else if (bop == 2)
		*auxDist = max(*auxDist, -clipDist); // Difference (A-B)
	else if (bop == 3)
		*auxDist = max(min(*auxDist, clipDist), -max(*auxDist, clipDist)); // XOR
	else if (bop == 4) // Smooth union
	{
		float kk = clipSmoothK;
		float hh = clamp(0.5f + 0.5f * (clipDist - *auxDist) / kk, 0.0f, 1.0f);
		*auxDist = mix(clipDist, *auxDist, hh) - kk * hh * (1.0f - hh);
	}
	else if (bop == 5) // Smooth difference
	{
		float kk2 = clipSmoothK;
		float hh2 = clamp(0.5f - 0.5f * (*auxDist + clipDist) / kk2, 0.0f, 1.0f);
		*auxDist = mix(*auxDist, -clipDist, hh2) + kk2 * hh2 * (1.0f - hh2);
	}
}

#endif /* MANDELBULBER2_OPENCL_MUTATION_CLIP_CL_ */

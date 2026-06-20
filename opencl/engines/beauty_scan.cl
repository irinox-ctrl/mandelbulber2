/**
 * 3x3lion — Founded by Iri and Devin
 *
 * Julia Beauty Scan Kernel — GPU-accelerated search for optimal Julia c-values.
 * Evaluates beauty scores for candidate c-values by computing fractal iterations
 * at multiple spatial sample points.
 *
 * Supports: Mandelbulb (power 2-16), Mandelbox, Quaternion
 */

#define BEAUTY_FORMULA_MANDELBULB 0
#define BEAUTY_FORMULA_MANDELBOX  1
#define BEAUTY_FORMULA_QUATERNION 2

// Mandelbulb iteration: z = z^power + c
inline float3 mandelbulb_iter(float3 z, float3 c, float power)
{
	float r = length(z);
	if (r < 1e-21f) r = 1e-21f;
	float theta = acos(clamp(z.z / r, -1.0f, 1.0f));
	float phi = atan2(z.y, z.x);
	float rn = pow(r, power);
	float newTheta = theta * power;
	float newPhi = phi * power;
	float sinTheta = sin(newTheta);
	return (float3)(
		rn * sinTheta * cos(newPhi) + c.x,
		rn * sinTheta * sin(newPhi) + c.y,
		rn * cos(newTheta) + c.z
	);
}

// Mandelbox iteration
inline float3 mandelbox_iter(float3 z, float3 c, float scale)
{
	// Box fold
	if (z.x > 1.0f) z.x = 2.0f - z.x; else if (z.x < -1.0f) z.x = -2.0f - z.x;
	if (z.y > 1.0f) z.y = 2.0f - z.y; else if (z.y < -1.0f) z.y = -2.0f - z.y;
	if (z.z > 1.0f) z.z = 2.0f - z.z; else if (z.z < -1.0f) z.z = -2.0f - z.z;
	// Sphere fold
	float r2 = dot(z, z);
	if (r2 < 0.25f) z *= 4.0f;
	else if (r2 < 1.0f) z /= r2;
	// Scale and translate
	return z * scale + c;
}

// Quaternion iteration: q = q^2 + c
inline float4 quaternion_iter(float4 q, float4 c)
{
	float4 q2;
	q2.x = q.x * q.x - q.y * q.y - q.z * q.z - q.w * q.w + c.x;
	q2.y = 2.0f * q.x * q.y + c.y;
	q2.z = 2.0f * q.x * q.z + c.z;
	q2.w = 2.0f * q.x * q.w + c.w;
	return q2;
}

// Compute iteration count for a spatial point with given Julia c-value
inline int compute_iterations(float3 point, float3 juliaC, int maxIter,
	int formulaType, float formulaParam)
{
	if (formulaType == BEAUTY_FORMULA_MANDELBULB)
	{
		float3 z = point;
		for (int i = 0; i < maxIter; i++)
		{
			float r = length(z);
			if (r > 4.0f) return i;
			z = mandelbulb_iter(z, juliaC, formulaParam);
		}
		return maxIter;
	}
	else if (formulaType == BEAUTY_FORMULA_MANDELBOX)
	{
		float3 z = point;
		for (int i = 0; i < maxIter; i++)
		{
			float r = length(z);
			if (r > 100.0f) return i;
			z = mandelbox_iter(z, juliaC, formulaParam);
		}
		return maxIter;
	}
	else // QUATERNION
	{
		float4 q = (float4)(point.x, point.y, point.z, 0.0f);
		float4 c4 = (float4)(juliaC.x, juliaC.y, juliaC.z, 0.0f);
		for (int i = 0; i < maxIter; i++)
		{
			if (dot(q, q) > 16.0f) return i;
			q = quaternion_iter(q, c4);
		}
		return maxIter;
	}
}

// Beauty score computation for a single c-value
// Evaluates on a grid of spatial sample points
inline float compute_beauty_score(float3 juliaC, int maxIter,
	int formulaType, float formulaParam, float sampleRange)
{
	// Sample 6x6x6 = 216 spatial points
	const int samplesPerAxis = 6;
	const float step = 2.0f * sampleRange / (float)(samplesPerAxis - 1);

	int totalSamples = 0;
	int boundaryCount = 0;  // Points near boundary (escaped but high iter)
	int insideCount = 0;    // Points that didn't escape
	float iterSum = 0.0f;
	float iterSumSq = 0.0f;

	for (int iz = 0; iz < samplesPerAxis; iz++)
	{
		for (int iy = 0; iy < samplesPerAxis; iy++)
		{
			for (int ix = 0; ix < samplesPerAxis; ix++)
			{
				float3 pt;
				pt.x = -sampleRange + ix * step;
				pt.y = -sampleRange + iy * step;
				pt.z = -sampleRange + iz * step;

				int iters = compute_iterations(pt, juliaC, maxIter, formulaType, formulaParam);
				totalSamples++;

				float normalizedIter = (float)iters / (float)maxIter;
				iterSum += normalizedIter;
				iterSumSq += normalizedIter * normalizedIter;

				if (iters >= maxIter)
				{
					insideCount++;
				}
				else if (normalizedIter > 0.2f)
				{
					boundaryCount++;
				}
			}
		}
	}

	if (totalSamples == 0) return 0.0f;

	// Boundary ratio: fraction of points near the boundary (most interesting)
	float boundaryRatio = (float)boundaryCount / (float)totalSamples;

	// Inside ratio: too many inside = boring (solid blob), too few = disconnected
	float insideRatio = (float)insideCount / (float)totalSamples;

	// Variation: standard deviation of iteration counts
	float mean = iterSum / (float)totalSamples;
	float variance = (iterSumSq / (float)totalSamples) - (mean * mean);
	float stddev = sqrt(max(variance, 0.0f));

	// Ideal: insideRatio between 0.1 and 0.5 (connected but not blob)
	float connectedness = 1.0f - 4.0f * (insideRatio - 0.3f) * (insideRatio - 0.3f);
	connectedness = clamp(connectedness, 0.0f, 1.0f);

	// Score combines: boundary presence, detail variation, connectedness
	float score = (boundaryRatio * 2.0f + stddev * 3.0f + connectedness) / 6.0f;

	// Boost for "sweet spot" — interesting but not chaotic
	if (boundaryRatio > 0.15f && boundaryRatio < 0.6f && insideRatio > 0.05f)
		score *= 1.5f;

	return clamp(score, 0.0f, 1.0f);
}

// Main kernel: each work item evaluates one candidate c-value
kernel void beautyScoreKernel(
	__global float *candidates,   // Input: Nx3 array of candidate c-values (cx,cy,cz)
	__global float *scores,       // Output: N beauty scores
	int numCandidates,
	int maxIter,
	int formulaType,
	float formulaParam,
	float sampleRange)
{
	int gid = get_global_id(0);
	if (gid >= numCandidates) return;

	float3 juliaC;
	juliaC.x = candidates[gid * 3 + 0];
	juliaC.y = candidates[gid * 3 + 1];
	juliaC.z = candidates[gid * 3 + 2];

	scores[gid] = compute_beauty_score(juliaC, maxIter, formulaType, formulaParam, sampleRange);
}

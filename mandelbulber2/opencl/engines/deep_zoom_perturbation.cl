/**
 * 3x3lion — Deep Zoom GPU Delta Iteration Kernel
 * Founded by Iri and Devin
 *
 * The Holy Grail: GPU perturbation theory for 3D Mandelbulb with Distance Estimation.
 * This kernel computes delta iterations (δz) for each pixel, using a reference orbit
 * computed at arbitrary precision on the CPU.
 *
 * Features:
 * - Series Approximation: skips early iterations using linear matrix approximation
 * - Rebasing: when δz grows too large, resets to maintain precision
 * - Perturbed Distance Estimation: full DE computation via perturbation
 *
 * For each pixel:
 *   z_n = Z_n + δz_n   (reference orbit + perturbation)
 *   c   = C   + δc     (reference center + pixel offset)
 *
 * The GPU only needs double precision because δz stays small relative to Z.
 * The reference orbit Z_n is pre-computed at arbitrary precision (MPFR) on the CPU
 * and stored as double-precision snapshots for the GPU.
 */

#ifndef DEEP_ZOOM_PERTURBATION_CL
#define DEEP_ZOOM_PERTURBATION_CL

// Reference orbit point (uploaded from CPU)
typedef struct
{
	float3 Z;       // reference orbit position (double→float for GPU)
	float DE;       // reference running derivative
	float r;        // |Z_n|
	float theta;    // asin(Z.z / r)
	float phi;      // atan2(Z.y, Z.x)
	int escaped;    // 1 if |Z_n| > bailout
} sRefOrbitPoint;

// Series Approximation matrix (3x3, uploaded from CPU)
typedef struct
{
	float m[3][3];  // the linear coefficient matrix A
	int skipIters;  // number of iterations to skip
	int valid;      // 1 if SA is valid
} sSeriesApproxGPU;

// Deep zoom configuration
typedef struct
{
	float power;           // Mandelbulb power (typically 8)
	float bailout;         // escape radius (typically 256)
	int maxIterations;     // max iterations
	float rebaseThreshold; // rebase when |δz|/|Z| > this
	float betaAngleOffset;
	float alphaAngleOffset;
	int refOrbitLength;    // length of reference orbit
} sDeepZoomConfig;

/**
 * Apply 3x3 matrix to vector (for Series Approximation)
 */
float3 MatVecMul(float m[3][3], float3 v)
{
	return (float3)(
		m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
		m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
		m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
}

/**
 * Compute a single perturbed Mandelbulb iteration on GPU.
 *
 * Instead of computing the full Mandelbulb at arbitrary precision,
 * we compute: δz_{n+1} = f(Z_n + δz_n) - f(Z_n) + δc
 *
 * This is exact in double precision when |δz| << |Z|.
 */
float3 PerturbStepGPU(
	float3 deltaZ,
	float3 deltaC,
	__global const sRefOrbitPoint *ref,
	float *deltaDE,
	float power)
{
	float3 Zfull = ref->Z + deltaZ;
	float rFull = length(Zfull);

	if (rFull < 1e-20f) return deltaC;

	// f(Z_n + δz_n) in single precision
	float thetaFull = asin(clamp(Zfull.z / rFull, -1.0f, 1.0f));
	float phiFull = atan2(Zfull.y, Zfull.x);
	float rpFull = native_powr(rFull, power);
	float rp1Full = native_powr(rFull, power - 1.0f);

	float pTh = power * thetaFull;
	float pPh = power * phiFull;
	float cth = native_cos(pTh);
	float sth = native_sin(pTh);
	float cph = native_cos(pPh);
	float sph = native_sin(pPh);

	float3 fFull = (float3)(rpFull * cth * cph, rpFull * cth * sph, rpFull * sth);

	// f(Z_n) from reference
	float thetaRef = ref->theta;
	float phiRef = ref->phi;
	float rpRef = native_powr(ref->r, power);

	float pThRef = power * thetaRef;
	float pPhRef = power * phiRef;

	float3 fRef = (float3)(
		rpRef * native_cos(pThRef) * native_cos(pPhRef),
		rpRef * native_cos(pThRef) * native_sin(pPhRef),
		rpRef * native_sin(pThRef));

	// δz_{n+1} = f(Z_n + δz_n) - f(Z_n) + δc
	float3 newDeltaZ = fFull - fRef + deltaC;

	// Perturbed DE
	float deFull = ref->DE + *deltaDE;
	float newDEFull = power * rp1Full * deFull + 1.0f;
	float newDERef = power * native_powr(ref->r, power - 1.0f) * ref->DE + 1.0f;
	*deltaDE = newDEFull - newDERef;

	return newDeltaZ;
}

/**
 * Rebasing on GPU: find a closer reference orbit point
 * to reduce |δz| and maintain precision.
 */
int RebaseGPU(
	float3 *deltaZ,
	float *deltaDE,
	__global const sRefOrbitPoint *refOrbit,
	int currentIter,
	int orbitLength)
{
	float3 zFull = refOrbit[currentIter].Z + *deltaZ;
	float bestDist = length(*deltaZ);
	int bestIter = currentIter;

	int searchEnd = min(currentIter + 50, orbitLength - 1);
	for (int j = currentIter + 1; j <= searchEnd; j++)
	{
		float3 diff = zFull - refOrbit[j].Z;
		float dist = length(diff);
		if (dist < bestDist)
		{
			bestDist = dist;
			bestIter = j;
		}
	}

	if (bestIter != currentIter)
	{
		float deFull = refOrbit[currentIter].DE + *deltaDE;
		*deltaZ = zFull - refOrbit[bestIter].Z;
		*deltaDE = deFull - refOrbit[bestIter].DE;
	}

	return bestIter;
}

/**
 * Main deep zoom kernel: compute distance for one pixel using perturbation theory.
 *
 * Now with:
 * - Series Approximation: skip early iterations via matrix multiplication
 * - Rebasing: when δz grows too large, find closer reference point
 *
 * Input:
 *   refOrbit[]  — reference orbit (uploaded from CPU)
 *   config      — deep zoom configuration
 *   sa          — series approximation matrix (if valid)
 *   deltaCArray — per-pixel δc values (offset from reference center)
 *
 * Output:
 *   distances[] — estimated distance to fractal surface per pixel
 *   iterations[]— iteration count per pixel
 */
__kernel void DeepZoomPerturbationKernel(
	__global const sRefOrbitPoint *refOrbit,
	__global const sDeepZoomConfig *config,
	__global const sSeriesApproxGPU *sa,
	__global const float3 *deltaCArray,
	__global float *distances,
	__global int *iterations,
	int pixelCount)
{
	int gid = get_global_id(0);
	if (gid >= pixelCount) return;

	float3 deltaC = deltaCArray[gid];
	float3 deltaZ = deltaC; // initial δz = δc
	float deltaDE = 0.0f;
	int startIter = 0;

	float power = config->power;
	float bailout = config->bailout;
	int maxIter = min(config->maxIterations, config->refOrbitLength - 1);
	float rebaseThresh = config->rebaseThreshold;

	// Series Approximation: skip early iterations
	if (sa->valid && sa->skipIters > 0 && sa->skipIters < maxIter)
	{
		// δz_n ≈ A_n · δc
		float saMatrix[3][3];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				saMatrix[i][j] = sa->m[i][j];

		deltaZ = MatVecMul(saMatrix, deltaC);
		startIter = sa->skipIters;
		deltaDE = length(deltaZ); // rough DE seed after SA
	}

	int finalIter = maxIter;
	float finalDist = 1e10f;
	bool escaped = false;

	for (int i = startIter; i < maxIter; i++)
	{
		float3 zFull = refOrbit[i].Z + deltaZ;
		float rFull = length(zFull);

		// Escape check
		if (rFull > bailout)
		{
			escaped = true;
			finalIter = i;

			float deFull = refOrbit[i].DE + deltaDE;
			if (deFull > 0.0f && rFull > 1.0f)
			{
				finalDist = 0.5f * rFull * native_log(rFull) / fabs(deFull);
			}
			else
			{
				finalDist = rFull;
			}
			break;
		}

		// Rebasing check: if δz is too large relative to Z
		float deltaR = length(deltaZ);
		if (refOrbit[i].r > 1e-20f && deltaR > refOrbit[i].r * rebaseThresh)
		{
			int newIter = RebaseGPU(&deltaZ, &deltaDE, refOrbit, i, config->refOrbitLength);
			if (newIter != i)
			{
				i = newIter - 1; // -1 because for loop will increment
				continue;
			}
		}

		// Perturbation step
		deltaZ = PerturbStepGPU(deltaZ, deltaC, &refOrbit[i], &deltaDE, power);
	}

	if (!escaped)
	{
		int lastIdx = maxIter > 0 ? min(maxIter - 1, config->refOrbitLength - 1) : 0;
		float3 zFinal = refOrbit[lastIdx].Z + deltaZ;
		float rFinal = length(zFinal);
		float deFull = refOrbit[lastIdx].DE + deltaDE;
		if (deFull > 0.0f && rFinal > 0.0f)
		{
			finalDist = 0.5f * rFinal * max(native_log(rFinal), 0.0f) / fabs(deFull);
		}
		else
		{
			finalDist = 0.0f;
		}
	}

	distances[gid] = finalDist;
	iterations[gid] = finalIter;
}

#endif /* DEEP_ZOOM_PERTURBATION_CL */

/**
 * Mandelbulber v2 — GPU Mutation Safety Macros (OpenCL)
 *
 * Safe math operations for the formula mutation system.
 * GPU version uses single-precision float with native_* functions.
 */

#ifndef MUTATION_MACROS_GPU_H_
#define MUTATION_MACROS_GPU_H_

// Guard against division by zero: clamp tiny values away from 0 (pointer-safe)
#define GUARD_ZERO(x) do { \
	float _gzval = (x); \
	if (fabs(_gzval) < 1e-21f) { \
		(x) = ((_gzval) >= 0.0f ? 1e-21f : -1e-21f); \
	} \
} while(0)

// Return a guarded value without modifying the original
#define GUARD_ZERO_VAL(x) ((fabs(x) < 1e-21f) ? ((x) >= 0.0f ? 1e-21f : -1e-21f) : (x))

// Safe exponential: clamp to exp(25) ~ 7.2e10 (safe for float)
#define SAFE_EXP(x) native_exp(fmin(fmax((x), -25.0f), 25.0f))

// Safe division: returns 0 if denominator is near-zero
#define SAFE_DIV(num, den) ((fabs(den) < 1e-21f) ? 0.0f : ((num) / (den)))

// Safe square root: clamp negative values to zero
#define SAFE_SQRT(x) native_sqrt(fmax((x), 0.0f))

// Safe log: clamp to positive values
#define SAFE_LOG(x) native_log(fmax((x), 1e-21f))

// Safe power: guards base and exponent
#define SAFE_POW(base, exp) native_powr(fmax(fabs(base), 1e-21f), fmin((exp), 25.0f))

// Length of a 3D vector from components
#define LENGTH3(x, y, z) native_sqrt((x)*(x) + (y)*(y) + (z)*(z))

// Scalar multiply for float4
#define MUL_SCALAR(v, s) ((v) * (s))

// Float type for GPU: single precision
#define FLOAT_T float

#endif // MUTATION_MACROS_GPU_H_

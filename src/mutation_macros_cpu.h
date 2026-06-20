/**
 * Mandelbulber v2 — CPU Mutation Safety Macros
 *
 * Safe math operations for the formula mutation system.
 * CPU version uses double precision.
 */

#ifndef MUTATION_MACROS_CPU_H_
#define MUTATION_MACROS_CPU_H_

#include <cmath>
#include <cfloat>

// Guard against division by zero: clamp tiny values away from 0
#define GUARD_ZERO(x) do { \
	if (fabs(x) < 1e-21) { \
		(x) = ((x) >= 0.0 ? 1e-21 : -1e-21); \
	} \
} while(0)

// Return a guarded value without modifying the original
#define GUARD_ZERO_VAL(x) ((fabs(x) < 1e-21) ? ((x) >= 0.0 ? 1e-21 : -1e-21) : (x))

// Safe exponential: clamp to exp(40) ~ 2.4e17 (safe for double)
#define SAFE_EXP(x) exp(fmin(fmax((x), -40.0), 40.0))

// Safe division: returns 0 if denominator is near-zero
#define SAFE_DIV(num, den) ((fabs(den) < 1e-21) ? 0.0 : ((num) / (den)))

// Safe square root: clamp negative values to zero
#define SAFE_SQRT(x) sqrt(fmax((x), 0.0))

// Safe log: clamp to positive values
#define SAFE_LOG(x) log(fmax((x), 1e-21))

// Safe power: guards base and exponent
#define SAFE_POW(base, exp) pow(fmax(fabs(base), 1e-21), fmin((exp), 40.0))

// Length of a 3D vector from components
#define LENGTH3(x, y, z) sqrt((x)*(x) + (y)*(y) + (z)*(z))

// Scalar multiply macro for CVector4
#define MUL_SCALAR(v, s) ((v) * (s))

// Float type for CPU: double precision
#define FLOAT_T double

#endif // MUTATION_MACROS_CPU_H_

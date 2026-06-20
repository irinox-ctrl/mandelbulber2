/**
 * Double-Single Arithmetic for Extended Precision
 * 
 * Implements double-single emulation: represents a number as (hi + lo) where |lo| << |hi|
 * Provides ~15 decimal digits of precision using two float32 values
 * 
 * Based on Dekker's algorithm for split multiplication and two-sum
 * Used for deep zoom scenarios (>1e7) where standard float32 loses precision
 */

#ifndef OPENCL_DOUBLE_SINGLE_H
#define OPENCL_DOUBLE_SINGLE_H

// Double-single: represents a number as (hi + lo) where |lo| << |hi|
// Value = hi + lo, with hi containing high-order bits and lo containing low-order bits
typedef struct
{
	float hi;
	float lo;
} ds_float;

// Double-single 3D vector
typedef struct
{
	ds_float x;
	ds_float y;
	ds_float z;
} ds_float3;

// Quick two-sum: split a + b into hi + lo
// Assumes |a| >= |b| and result is not zero
inline ds_float ds_quick_two_sum(float a, float b)
{
	ds_float result;
	result.hi = a + b;
	result.lo = b - (result.hi - a);
	return result;
}

// Full two-sum for arbitrary a, b
inline ds_float ds_two_sum(float a, float b)
{
	ds_float result;
	result.hi = a + b;
	float v = result.hi - a;
	result.lo = (a - (result.hi - v)) + (b - v);
	return result;
}

// Two-product using FMA (fused multiply-add)
// Returns a * b split into hi + lo
inline ds_float ds_two_prod(float a, float b)
{
	ds_float result;
	result.hi = a * b;
	result.lo = fma(a, b, -result.hi);
	return result;
}

// Add two ds_floats
inline ds_float ds_add(ds_float a, ds_float b)
{
	ds_float s = ds_two_sum(a.hi, b.hi);
	s.lo += a.lo + b.lo;
	return ds_quick_two_sum(s.hi, s.lo);
}

// Subtract: a - b
inline ds_float ds_sub(ds_float a, ds_float b)
{
	ds_float neg_b = {-b.hi, -b.lo};
	return ds_add(a, neg_b);
}

// Multiply two ds_floats
inline ds_float ds_mul(ds_float a, ds_float b)
{
	ds_float p = ds_two_prod(a.hi, b.hi);
	p.lo += a.hi * b.lo + a.lo * b.hi;
	return ds_quick_two_sum(p.hi, p.lo);
}

// Create ds_float from single float
inline ds_float ds_from_float(float f)
{
	ds_float result = {f, 0.0f};
	return result;
}

// Extract single float (loses precision)
inline float ds_to_float(ds_float a)
{
	return a.hi + a.lo;
}

// Negate a ds_float
inline ds_float ds_neg(ds_float a)
{
	ds_float result = {-a.hi, -a.lo};
	return result;
}

// Absolute value of a ds_float
inline ds_float ds_fabs(ds_float a)
{
	if (a.hi < 0.0f) {
		return ds_neg(a);
	}
	return a;
}

// Vector operations

// Add two ds_float3 vectors
inline ds_float3 ds_float3_add(ds_float3 a, ds_float3 b)
{
	ds_float3 result;
	result.x = ds_add(a.x, b.x);
	result.y = ds_add(a.y, b.y);
	result.z = ds_add(a.z, b.z);
	return result;
}

// Subtract two ds_float3 vectors
inline ds_float3 ds_float3_sub(ds_float3 a, ds_float3 b)
{
	ds_float3 result;
	result.x = ds_sub(a.x, b.x);
	result.y = ds_sub(a.y, b.y);
	result.z = ds_sub(a.z, b.z);
	return result;
}

// Scale ds_float3 by a ds_float scalar
inline ds_float3 ds_float3_scale(ds_float3 a, ds_float s)
{
	ds_float3 result;
	result.x = ds_mul(a.x, s);
	result.y = ds_mul(a.y, s);
	result.z = ds_mul(a.z, s);
	return result;
}

// Scale ds_float3 by a float scalar
inline ds_float3 ds_float3_scale_float(ds_float3 a, float s)
{
	ds_float ds_s = ds_from_float(s);
	return ds_float3_scale(a, ds_s);
}

// Convert ds_float3 to float3 (loses precision)
inline float3 ds_float3_to_float3(ds_float3 a)
{
	return (float3)(ds_to_float(a.x), ds_to_float(a.y), ds_to_float(a.z));
}

// Create ds_float3 from float3
inline ds_float3 ds_float3_from_float3(float3 v)
{
	ds_float3 result;
	result.x = ds_from_float(v.x);
	result.y = ds_from_float(v.y);
	result.z = ds_from_float(v.z);
	return result;
}

// Dot product of two ds_float3 vectors
inline ds_float ds_float3_dot(ds_float3 a, ds_float3 b)
{
	// a.x * b.x + a.y * b.y + a.z * b.z
	ds_float p1 = ds_mul(a.x, b.x);
	ds_float p2 = ds_mul(a.y, b.y);
	ds_float p3 = ds_mul(a.z, b.z);
	
	ds_float s1 = ds_add(p1, p2);
	ds_float result = ds_add(s1, p3);
	return result;
}

// Length of ds_float3 vector
inline ds_float ds_float3_length(ds_float3 v)
{
	ds_float dot = ds_float3_dot(v, v);
	// Square root using Newton-Raphson in double-single
	// For deep zoom, we use an approximation
	float len = native_sqrt(ds_to_float(dot));
	return ds_from_float(len);
}

// Normalize ds_float3 vector
inline ds_float3 ds_float3_normalize(ds_float3 v)
{
	float len = native_sqrt(ds_to_float(ds_float3_dot(v, v)));
	if (len > 1e-20f) {
		float inv_len = 1.0f / len;
		return ds_float3_scale_float(v, inv_len);
	}
	return v;
}

#endif // OPENCL_DOUBLE_SINGLE_H

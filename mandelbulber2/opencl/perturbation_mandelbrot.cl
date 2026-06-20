/**
 * Mandelbulber v2, a 3D fractal generator
 *
 * PROOF OF CONCEPT: GPU Perturbation Kernel for 2D Mandelbrot
 *
 * This kernel calculates delta orbits using a reference orbit.
 * Formula: δ_{n+1} = 2·Z_n·δ_n + δ_n² + δc
 *
 * Theory:
 *   Full orbit: z_n = Z_n + δ_n
 *   where Z_n = reference orbit (high precision, calculated on CPU)
 *         δ_n = delta orbit (float precision, calculated on GPU)
 *
 * Advantage:
 *   δ_n stays small even at extreme zoom, so float precision is sufficient
 *   This allows zoom to 1e-100 and beyond
 *
 * Authors: Claude AI Assistant
 */

/**
 * Complex number multiplication (2D)
 * result = a * b
 */
inline float2 complexMul(float2 a, float2 b)
{
	return (float2)(
		a.x * b.x - a.y * b.y,  // real part
		a.x * b.y + a.y * b.x   // imaginary part
	);
}

/**
 * GPU Perturbation Kernel for 2D Mandelbrot
 *
 * @param width Image width
 * @param height Image height
 * @param center_x Center point X (high precision input as double, converted to float)
 * @param center_y Center point Y
 * @param pixel_size Size of one pixel in fractal space
 * @param max_iterations Maximum iterations
 * @param bailout Escape radius
 * @param ref_orbit_x Reference orbit X coordinates (from CPU, max_iterations elements)
 * @param ref_orbit_y Reference orbit Y coordinates (from CPU, max_iterations elements)
 * @param output Iteration count per pixel (width * height elements)
 */
__kernel void perturbation_mandelbrot_poc(
	int width,
	int height,
	double center_x,
	double center_y,
	double pixel_size,
	int max_iterations,
	float bailout,
	__global const float *ref_orbit_x,
	__global const float *ref_orbit_y,
	__global int *output)
{
	// Get pixel coordinates
	int px = get_global_id(0);
	int py = get_global_id(1);

	if (px >= width || py >= height)
		return;

	// Calculate pixel position in fractal space
	// Position = center + (pixel_offset - image_center) * pixel_size
	float offset_x = (float)(px - width / 2) * (float)pixel_size;
	float offset_y = (float)(py - height / 2) * (float)pixel_size;

	// Delta c = offset from center point
	// c_pixel = c_center + δc
	float2 delta_c = (float2)(offset_x, offset_y);

	// Initial state:
	// z_0 = 0, Z_0 = 0, therefore δ_0 = 0
	float2 delta = (float2)(0.0f, 0.0f);

	// Bailout squared (for faster comparison)
	float bailout_sq = bailout * bailout;

	int iter = 0;
	for (iter = 0; iter < max_iterations; iter++)
	{
		// Get reference orbit point Z_n
		float2 Z_n = (float2)(ref_orbit_x[iter], ref_orbit_y[iter]);

		// Reconstruct full orbit: z_n = Z_n + δ_n
		float2 z_n = Z_n + delta;

		// Check bailout on full orbit
		float r_sq = z_n.x * z_n.x + z_n.y * z_n.y;
		if (r_sq > bailout_sq)
		{
			break;  // Escaped
		}

		// Perturbation iteration formula:
		// z_{n+1} = z_n² + c
		// (Z_n + δ_n)² + (C + δc) = Z_n² + C + 2·Z_n·δ_n + δ_n² + δc
		//                         = Z_{n+1} + 2·Z_n·δ_n + δ_n² + δc
		// Therefore: δ_{n+1} = 2·Z_n·δ_n + δ_n² + δc

		// Calculate terms using complex multiplication
		float2 term1 = complexMul((float2)(2.0f, 0.0f), complexMul(Z_n, delta));  // 2·Z_n·δ_n
		float2 term2 = complexMul(delta, delta);  // δ_n²

		delta = term1 + term2 + delta_c;  // δ_{n+1}
	}

	// Store result
	output[py * width + px] = iter;
}

/**
 * ALTERNATIVE VERSION: More numerically stable
 *
 * Uses split formula to reduce accumulation error:
 * δ_{n+1} = (δ_n + Z_n)² + δc - Z_{n+1}
 *
 * This is mathematically equivalent but sometimes more stable
 */
__kernel void perturbation_mandelbrot_stable(
	int width,
	int height,
	double center_x,
	double center_y,
	double pixel_size,
	int max_iterations,
	float bailout,
	__global const float *ref_orbit_x,
	__global const float *ref_orbit_y,
	__global int *output)
{
	int px = get_global_id(0);
	int py = get_global_id(1);

	if (px >= width || py >= height)
		return;

	float offset_x = (float)(px - width / 2) * (float)pixel_size;
	float offset_y = (float)(py - height / 2) * (float)pixel_size;
	float2 delta_c = (float2)(offset_x, offset_y);

	float2 delta = delta_c;
	float bailout_sq = bailout * bailout;

	int iter = 0;
	for (iter = 0; iter < max_iterations; iter++)
	{
		float2 Z_n = (float2)(ref_orbit_x[iter], ref_orbit_y[iter]);
		float2 z_n = Z_n + delta;

		// Bailout check
		float r_sq = z_n.x * z_n.x + z_n.y * z_n.y;
		if (r_sq > bailout_sq)
			break;

		// Get Z_{n+1} for stable formula
		float2 Z_next;
		if (iter + 1 < max_iterations)
		{
			Z_next = (float2)(ref_orbit_x[iter + 1], ref_orbit_y[iter + 1]);
		}
		else
		{
			// Last iteration, calculate Z_next manually
			Z_next = complexMul(Z_n, Z_n) + (float2)((float)center_x, (float)center_y);
		}

		// Stable formula: δ_{n+1} = (δ_n + Z_n)² + δc - Z_{n+1}
		float2 z_sq = complexMul(z_n, z_n);
		delta = z_sq + delta_c - Z_next;

		// Safety check
		float delta_sq = delta.x * delta.x + delta.y * delta.y;
		if (delta_sq > 1e10f)
			break;
	}

	output[py * width + px] = iter;
}

/**
 * DEBUG VERSION: Visualize delta magnitude
 *
 * Output the maximum |δ_n| encountered during iteration
 * Useful for verifying perturbation theory is working correctly
 */
__kernel void perturbation_debug_delta(
	int width,
	int height,
	double center_x,
	double center_y,
	double pixel_size,
	int max_iterations,
	float bailout,
	__global const float *ref_orbit_x,
	__global const float *ref_orbit_y,
	__global float *output_max_delta)
{
	int px = get_global_id(0);
	int py = get_global_id(1);

	if (px >= width || py >= height)
		return;

	float offset_x = (float)(px - width / 2) * (float)pixel_size;
	float offset_y = (float)(py - height / 2) * (float)pixel_size;
	float2 delta_c = (float2)(offset_x, offset_y);

	float2 delta = delta_c;
	float bailout_sq = bailout * bailout;
	float max_delta_mag = 0.0f;

	for (int iter = 0; iter < max_iterations; iter++)
	{
		float2 Z_n = (float2)(ref_orbit_x[iter], ref_orbit_y[iter]);
		float2 z_n = Z_n + delta;

		// Track maximum delta magnitude
		float delta_mag = sqrt(delta.x * delta.x + delta.y * delta.y);
		max_delta_mag = fmax(max_delta_mag, delta_mag);

		// Bailout check
		float r_sq = z_n.x * z_n.x + z_n.y * z_n.y;
		if (r_sq > bailout_sq)
			break;

		// Perturbation iteration
		float2 term1 = complexMul(2.0f * Z_n, delta);
		float2 term2 = complexMul(delta, delta);
		delta = term1 + term2 + delta_c;
	}

	// Output maximum delta magnitude for this pixel
	output_max_delta[py * width + px] = max_delta_mag;
}

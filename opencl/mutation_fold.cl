/**
 * Shared mutation fold transforms for OpenCL (CPU parity via compute_fractal.cpp).
 */

#ifndef MANDELBULBER2_OPENCL_MUTATION_FOLD_CL_
#define MANDELBULBER2_OPENCL_MUTATION_FOLD_CL_

inline float ApplyFoldTransform(__private float4 *z, const int foldType, const float foldLimit,
	const float foldValue, const int kaleidoscopeSides, const int iteration)
{
	float deScale = 1.0f;

	switch (foldType)
	{
		case 1: // box fold
			if (fabs(z->x) > foldLimit) z->x = sign(z->x) * foldValue - z->x;
			if (fabs(z->y) > foldLimit) z->y = sign(z->y) * foldValue - z->y;
			if (fabs(z->z) > foldLimit) z->z = sign(z->z) * foldValue - z->z;
			break;
		case 2: // sphere fold
		{
			float rr = z->x * z->x + z->y * z->y + z->z * z->z;
			float minR2 = foldLimit * foldLimit;
			float fixR2 = foldValue * foldValue;
			if (rr < minR2) deScale *= fixR2 / minR2;
			else if (rr < fixR2) deScale *= fixR2 / rr;
			if (rr < minR2 || rr < fixR2) *z *= deScale;
			break;
		}
		case 3: // menger fold
		{
			z->x = fabs(z->x); z->y = fabs(z->y); z->z = fabs(z->z);
			if (z->x - z->y < 0) { float t = z->y; z->y = z->x; z->x = t; }
			if (z->x - z->z < 0) { float t = z->z; z->z = z->x; z->x = t; }
			if (z->y - z->z < 0) { float t = z->z; z->z = z->y; z->y = t; }
			float s = foldValue;
			z->x = z->x * s - foldLimit * (s - 1.0f);
			z->y = z->y * s - foldLimit * (s - 1.0f);
			z->z = z->z * s;
			if (z->z > 0.5f * foldLimit * (s - 1.0f)) z->z -= foldLimit * (s - 1.0f);
			deScale *= s;
			break;
		}
		case 4: // sierpinski fold
		{
			if (z->x + z->y < 0) { float tx = -z->y; z->y = -z->x; z->x = tx; }
			if (z->x + z->z < 0) { float tx = -z->z; z->z = -z->x; z->x = tx; }
			if (z->y + z->z < 0) { float ty = -z->z; z->z = -z->y; z->y = ty; }
			float s = foldValue;
			*z *= s;
			z->x -= foldLimit * (s - 1.0f);
			z->y -= foldLimit * (s - 1.0f);
			z->z -= foldLimit * (s - 1.0f);
			deScale *= s;
			break;
		}
		case 5: // abs fold (tglad)
			z->x = fabs(z->x + foldLimit) - fabs(z->x - foldLimit) - z->x;
			z->y = fabs(z->y + foldLimit) - fabs(z->y - foldLimit) - z->y;
			z->z = fabs(z->z + foldLimit) - fabs(z->z - foldLimit) - z->z;
			break;
		case 6: // kaleidoscope
		{
			if (kaleidoscopeSides >= 3)
			{
				float angle = M_PI_F / (float)kaleidoscopeSides;
				float pAngle = atan2(z->y, z->x);
				float r = native_sqrt(z->x * z->x + z->y * z->y);
				pAngle = fmod(pAngle + angle, 2.0f * angle) - angle;
				z->x = r * native_cos(pAngle);
				z->y = r * native_sin(pAngle);
				z->y = fabs(z->y);
			}
			break;
		}
		case 7: // octahedral fold
		{
			if (z->x + z->y < 0) { float tx = -z->y; z->y = -z->x; z->x = tx; }
			if (z->x + z->z < 0) { float tx = -z->z; z->z = -z->x; z->x = tx; }
			if (z->y + z->z < 0) { float ty = -z->z; z->z = -z->y; z->y = ty; }
			if (z->x - z->y < 0) { float tx = z->y; z->y = z->x; z->x = tx; }
			if (z->x - z->z < 0) { float tx = z->z; z->z = z->x; z->x = tx; }
			break;
		}
		case 8: // smooth fold (tanh)
		{
			float k = (foldLimit > 0.0f) ? foldLimit : 1.0f;
			z->x -= tanh(k * z->x);
			z->y -= tanh(k * z->y);
			z->z -= tanh(k * z->z);
			break;
		}
		case 9: // polynomial fold (Chebyshev z³-3z)
			z->x = z->x * z->x * z->x - 3.0f * z->x;
			z->y = z->y * z->y * z->y - 3.0f * z->y;
			z->z = z->z * z->z * z->z - 3.0f * z->z;
			break;
		case 10: // circular fold
		{
			float rad = (foldValue > 0.0f) ? foldValue : 1.0f;
			float r = native_sqrt(z->x * z->x + z->y * z->y + z->z * z->z);
			if (r > 1e-21f) { float s = rad / r; z->x *= s; z->y *= s; z->z *= s; }
			break;
		}
		case 11: // spiral fold
		{
			float r = native_sqrt(z->x * z->x + z->y * z->y);
			float angle = r * foldLimit;
			float ca = native_cos(angle);
			float sa = native_sin(angle);
			float nx = z->x * ca - z->y * sa;
			float ny = z->x * sa + z->y * ca;
			z->x = nx; z->y = ny;
			break;
		}
		case 12: // sinusoidal fold
		{
			float a = foldValue;
			float b = (foldLimit > 0.0f) ? foldLimit : 1.0f;
			z->x += a * native_sin(b * z->x);
			z->y += a * native_sin(b * z->y);
			z->z += a * native_sin(b * z->z);
			break;
		}
		case 13: // exponential fold
			z->x *= native_exp(-z->x * z->x);
			z->y *= native_exp(-z->y * z->y);
			z->z *= native_exp(-z->z * z->z);
			break;
		case 14: // logarithmic fold
		{
			float rx = fabs(z->x);
			float ry = fabs(z->y);
			float rz = fabs(z->z);
			z->x *= native_log(1.0f + rx);
			z->y *= native_log(1.0f + ry);
			z->z *= native_log(1.0f + rz);
			break;
		}
		case 15: // power fold
		{
			float p = (foldValue > 0.0f) ? foldValue : 2.0f;
			float ax = fabs(z->x);
			float ay = fabs(z->y);
			float az = fabs(z->z);
			z->x = sign(z->x) * native_powr(max(ax, 1e-21f), p);
			z->y = sign(z->y) * native_powr(max(ay, 1e-21f), p);
			z->z = sign(z->z) * native_powr(max(az, 1e-21f), p);
			break;
		}
		case 16: // smooth abs
		{
			float k = (foldLimit > 0.0f) ? foldLimit : 5.0f;
			z->x = z->x * tanh(k * z->x);
			z->y = z->y * tanh(k * z->y);
			z->z = z->z * tanh(k * z->z);
			break;
		}
		case 17: // modulo wrap
		{
			float period = (foldValue > 0.0f) ? foldValue : 2.0f;
			z->x = fmod(z->x + period * 0.5f, period) - period * 0.5f;
			z->y = fmod(z->y + period * 0.5f, period) - period * 0.5f;
			z->z = fmod(z->z + period * 0.5f, period) - period * 0.5f;
			break;
		}
		case 18: // nested abs
		{
			float c = (foldLimit > 0.0f) ? foldLimit : 1.0f;
			z->x = fabs(fabs(z->x) - c);
			z->y = fabs(fabs(z->y) - c);
			z->z = fabs(fabs(z->z) - c);
			break;
		}
		case 19: // sawtooth
			z->x = 2.0f * (z->x * 0.5f - floor(z->x * 0.5f + 0.5f));
			z->y = 2.0f * (z->y * 0.5f - floor(z->y * 0.5f + 0.5f));
			z->z = 2.0f * (z->z * 0.5f - floor(z->z * 0.5f + 0.5f));
			break;
		case 20: // bipolar
		{
			float c1 = foldLimit;
			float c2 = -foldLimit;
			z->x = fabs(z->x - c1) - fabs(z->x - c2);
			z->y = fabs(z->y - c1) - fabs(z->y - c2);
			z->z = fabs(z->z - c1) - fabs(z->z - c2);
			break;
		}
		case 21: // radial box
		{
			float rOld = native_sqrt(z->x * z->x + z->y * z->y);
			float theta = atan2(z->y, z->x);
			float foldR = foldLimit;
			float r = rOld;
			if (r > foldR) r = 2.0f * foldR - r;
			if (r < -foldR) r = -2.0f * foldR - r;
			z->x = r * native_cos(theta);
			z->y = r * native_sin(theta);
			deScale *= r / max(rOld, 1e-21f);
			break;
		}
		case 22: // shear
		{
			float lim = foldLimit;
			if (z->x > lim) z->x = 2.0f * lim - z->x;
			else if (z->x < -lim) z->x = -2.0f * lim - z->x;
			if (z->y > lim) z->y = 2.0f * lim - z->y;
			else if (z->y < -lim) z->y = -2.0f * lim - z->y;
			z->x += foldValue * z->y;
			z->y += foldValue * z->z;
			break;
		}
		case 23: // 3D cross
		{
			float lim = foldLimit;
			int phase = iteration % 3;
			if (phase == 0)
			{
				if (z->x > lim) z->x = 2.0f * lim - z->x;
				if (z->x < -lim) z->x = -2.0f * lim - z->x;
				if (z->y > lim) z->y = 2.0f * lim - z->y;
				if (z->y < -lim) z->y = -2.0f * lim - z->y;
			}
			else if (phase == 1)
			{
				if (z->y > lim) z->y = 2.0f * lim - z->y;
				if (z->y < -lim) z->y = -2.0f * lim - z->y;
				if (z->z > lim) z->z = 2.0f * lim - z->z;
				if (z->z < -lim) z->z = -2.0f * lim - z->z;
			}
			else
			{
				if (z->z > lim) z->z = 2.0f * lim - z->z;
				if (z->z < -lim) z->z = -2.0f * lim - z->z;
				if (z->x > lim) z->x = 2.0f * lim - z->x;
				if (z->x < -lim) z->x = -2.0f * lim - z->x;
			}
			break;
		}
		case 24: // conformal
		{
			float r2 = z->x * z->x + z->y * z->y + z->z * z->z;
			if (r2 > 1e-21f)
			{
				z->x += z->x / r2;
				z->y += z->y / r2;
				z->z += z->z / r2;
				deScale *= fabs(1.0f - 1.0f / r2);
			}
			break;
		}
		case 25: // rotation
		{
			float lim = foldLimit;
			if (z->x > lim) z->x = 2.0f * lim - z->x;
			if (z->x < -lim) z->x = -2.0f * lim - z->x;
			if (z->y > lim) z->y = 2.0f * lim - z->y;
			if (z->y < -lim) z->y = -2.0f * lim - z->y;
			if (z->z > lim) z->z = 2.0f * lim - z->z;
			if (z->z < -lim) z->z = -2.0f * lim - z->z;
			float t = z->x;
			z->x = -z->y;
			z->y = t;
			break;
		}
		case 26: // scale pulse
		{
			float lim = foldLimit;
			if (z->x > lim) z->x = 2.0f * lim - z->x;
			if (z->x < -lim) z->x = -2.0f * lim - z->x;
			if (z->y > lim) z->y = 2.0f * lim - z->y;
			if (z->y < -lim) z->y = -2.0f * lim - z->y;
			if (z->z > lim) z->z = 2.0f * lim - z->z;
			if (z->z < -lim) z->z = -2.0f * lim - z->z;
			float pulse = 1.0f + 0.2f * native_sin((float)iteration * foldValue);
			*z *= pulse;
			deScale *= fabs(pulse);
			break;
		}
		case 27: // triangle wave
			z->x = 2.0f * fabs(z->x * 0.5f - floor(z->x * 0.5f + 0.5f));
			z->y = 2.0f * fabs(z->y * 0.5f - floor(z->y * 0.5f + 0.5f));
			z->z = 2.0f * fabs(z->z * 0.5f - floor(z->z * 0.5f + 0.5f));
			break;
		default: break;
	}

	return deScale;
}

#endif /* MANDELBULBER2_OPENCL_MUTATION_FOLD_CL_ */

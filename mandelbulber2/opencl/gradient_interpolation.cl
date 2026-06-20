/**
 * Shared gradient interpolation (8 modes + OKLab/LAB/HSV color spaces).
 * Included by shader_surface_color.cl and nebula.cl kernels.
 */

// ===================================================================
// HSL COLOR SPACE HELPERS FOR OPENCL
// ===================================================================

void RGBtoHSL(float r, float g, float b, float *h, float *s, float *l)
{
	r = clamp(r, 0.0f, 1.0f);
	g = clamp(g, 0.0f, 1.0f);
	b = clamp(b, 0.0f, 1.0f);
	float maxVal = fmax(r, fmax(g, b));
	float minVal = fmin(r, fmin(g, b));
	*l = (maxVal + minVal) / 2.0f;
	if (maxVal == minVal)
	{
		*h = *s = 0.0f;
	}
	else
	{
		float d = maxVal - minVal;
		*s = *l > 0.5f ? d / (2.0f - maxVal - minVal) : d / (maxVal + minVal);
		if (maxVal == r)
			*h = (g - b) / d + (g < b ? 6.0f : 0.0f);
		else if (maxVal == g)
			*h = (b - r) / d + 2.0f;
		else
			*h = (r - g) / d + 4.0f;
		*h /= 6.0f;
	}
}

float3 HSLtoRGB(float h, float s, float l)
{
	h = fmod(h + 1.0f, 1.0f);
	s = clamp(s, 0.0f, 1.0f);
	l = clamp(l, 0.0f, 1.0f);
	float r, g, b;
	if (s == 0.0f)
	{
		r = g = b = l;
	}
	else
	{
		float q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
		float p = 2.0f * l - q;
		float t1 = h + 1.0f / 3.0f;
		float t2 = h;
		float t3 = h - 1.0f / 3.0f;
		if (t1 < 0.0f) t1 += 1.0f;
		if (t1 > 1.0f) t1 -= 1.0f;
		if (t2 < 0.0f) t2 += 1.0f;
		if (t2 > 1.0f) t2 -= 1.0f;
		if (t3 < 0.0f) t3 += 1.0f;
		if (t3 > 1.0f) t3 -= 1.0f;
		float c1 = (t1 < 1.0f / 6.0f) ? p + (q - p) * 6.0f * t1
					: (t1 < 1.0f / 2.0f) ? q
										 : (t1 < 2.0f / 3.0f) ? p + (q - p) * (2.0f / 3.0f - t1) * 6.0f
																								 : p;
		float c2 = (t2 < 1.0f / 6.0f) ? p + (q - p) * 6.0f * t2
					: (t2 < 1.0f / 2.0f) ? q
										 : (t2 < 2.0f / 3.0f) ? p + (q - p) * (2.0f / 3.0f - t2) * 6.0f
																								 : p;
		float c3 = (t3 < 1.0f / 6.0f) ? p + (q - p) * 6.0f * t3
					: (t3 < 1.0f / 2.0f) ? q
										 : (t3 < 2.0f / 3.0f) ? p + (q - p) * (2.0f / 3.0f - t3) * 6.0f
																								 : p;
		r = c1; g = c2; b = c3;
	}
	return (float3)(r, g, b);
}

float InterpolateHue(float h1, float h2, float delta, int shortestPath)
{
	float diff = h2 - h1;
	if (shortestPath)
	{
		if (diff > 0.5f) h2 -= 1.0f;
		else if (diff < -0.5f) h2 += 1.0f;
	}
	else
	{
		if (diff > 0.0f && diff < 0.5f) h2 -= 1.0f;
		else if (diff < 0.0f && diff > -0.5f) h2 += 1.0f;
	}
	float h = h1 + (h2 - h1) * delta;
	return fmod(h + 1.0f, 1.0f);
}

float CubicInterpolate(float y0, float y1, float y2, float y3, float mu)
{
	float a0 = -0.5f * y0 + 1.5f * y1 - 1.5f * y2 + 0.5f * y3;
	float a1 = y0 - 2.5f * y1 + 2.0f * y2 - 0.5f * y3;
	float a2 = -0.5f * y0 + 0.5f * y2;
	float a3 = y1;
	return a0 * mu * mu * mu + a1 * mu * mu + a2 * mu + a3;
}

float3 InterpolateColorSpace(float3 color1, float3 color2, float delta, int colorSpace);

float3 GradientInterpolate(int paletteIndex, float pos, bool smooth, int gradientSize,
	__global float4 *palette, __global float4 *midpoints, int midpointSize, int mode, int colorSpace)
{
	float3 color = 0.0f;
	if (paletteIndex == gradientSize - 1)
	{
		if (gradientSize >= 2 && pos > palette[gradientSize - 1].w)
			paletteIndex = gradientSize - 2;
		else
		{
			color = palette[paletteIndex].xyz;
			return color;
		}
	}

	{
		float3 color1 = palette[paletteIndex].xyz;
		float pos1 = palette[paletteIndex].w;
		float3 color2 = palette[paletteIndex + 1].xyz;
		float pos2 = palette[paletteIndex + 1].w;

		if (pos2 - pos1 > 0.0f)
		{
			float delta = (pos - pos1) / (pos2 - pos1);

			// Apply per-segment mode override BEFORE computing useSmooth
			if (midpoints && paletteIndex < midpointSize)
			{
				// Per-segment interpolation mode override (stored in y component)
				mode = clamp((int)midpoints[paletteIndex].s1, 0, 7);
			}

			bool useSmooth = (mode == 1) || (mode == 0 && smooth);
			if (useSmooth) delta = 0.5f * (1.0f - cos(delta * M_PI_F));

			float rawDelta = delta;

			// Apply midpoint gamma curve only for modes that don't have their own formula
			if (mode != 6 && mode != 7)
			{
				if (midpoints && paletteIndex < midpointSize)
				{
					float m = clamp(midpoints[paletteIndex].s0, 0.01f, 0.99f);
					float reflectedM = 1.0f - m;
					float gamma = log(0.5f) / log(reflectedM);
					float deviation = gamma - 1.0f;
					float intensity = clamp(midpoints[paletteIndex].s2, 0.0f, 5.0f);
					gamma = 1.0f + deviation * intensity;
					gamma = clamp(gamma, 0.01f, 10.0f);
					// Apply asymmetry bias (s3 component)
					float bias = midpoints[paletteIndex].s3;
					if (fabs(bias) > 0.001f)
					{
						float bexp = (bias < 0.0f) ? (1.0f + fabs(bias)) : (1.0f / (1.0f + bias));
						delta = pow(delta, bexp);
					}
					delta = pow(delta, gamma);
				}
			}

			// Quadratic Bezier uses midpoint as control point
			if (mode == 6)
			{
				float mp = (midpoints && paletteIndex < midpointSize) 
					? clamp(midpoints[paletteIndex].s0, 0.01f, 0.99f) : 0.5f;
				delta = 2.0f * (1.0f - rawDelta) * rawDelta * mp + rawDelta * rawDelta;
			}

			// PowerCurve uses midpoint as gamma exponent (reflected to match Photoshop direction)
			if (mode == 7)
			{
				float mp = (midpoints && paletteIndex < midpointSize)
					? clamp(midpoints[paletteIndex].s0, 0.01f, 0.99f) : 0.5f;
				float reflectedMp = 1.0f - mp;
				float gamma = log(0.5f) / log(reflectedMp);
				delta = pow(rawDelta, gamma);
			}

			switch (mode)
			{
				case 5: // Constant
					color = delta < 0.5f ? color1 : color2;
					break;
				case 2: // HSLShort
				case 3: // HSLLong
				{
					float h1, s1, l1, h2, s2, l2;
					RGBtoHSL(color1.x, color1.y, color1.z, &h1, &s1, &l1);
					RGBtoHSL(color2.x, color2.y, color2.z, &h2, &s2, &l2);
					float h = InterpolateHue(h1, h2, delta, mode == 2);
					float s = s1 * (1.0f - delta) + s2 * delta;
					float l = l1 * (1.0f - delta) + l2 * delta;
					color = HSLtoRGB(h, s, l);
					break;
				}
				case 4: // Cubic
				{
					int n = gradientSize;
					int i = paletteIndex;
					float y0[3], y1[3], y2[3], y3[3];
					for (int ch = 0; ch < 3; ch++)
					{
						y0[ch] = palette[clamp(i - 1, 0, n - 1)][ch];
						y1[ch] = palette[clamp(i, 0, n - 1)][ch];
						y2[ch] = palette[clamp(i + 1, 0, n - 1)][ch];
						y3[ch] = palette[clamp(i + 2, 0, n - 1)][ch];
					}
					color.x = clamp(CubicInterpolate(y0[0], y1[0], y2[0], y3[0], delta), 0.0f, 1.0f);
					color.y = clamp(CubicInterpolate(y0[1], y1[1], y2[1], y3[1], delta), 0.0f, 1.0f);
					color.z = clamp(CubicInterpolate(y0[2], y1[2], y2[2], y3[2], delta), 0.0f, 1.0f);
					break;
				}
				case 0: // Linear
				case 1: // Smooth
				case 6: // QuadraticBezier
				case 7: // PowerCurve
				default:
				{
					color = InterpolateColorSpace(color1, color2, delta, colorSpace);
					break;
				}
			}
		}
		else
		{
			color = color1;
		}
	}
	return color;
}

int GradientIterator(
	int paletteIndex, float colorPosition, int gradientSize, __global float4 *palette)
{
	int newIndex = paletteIndex;
	while (newIndex < gradientSize - 1 && colorPosition > palette[newIndex + 1].w)
	{
		newIndex++;
	}
	return newIndex;
}

float3 GetColorFromGradient(float position, bool smooth, int gradientSize,
	__global float4 *palette, __global float4 *midpoints, int midpointSize, int mode, int colorSpace)
{
	int paletteIndex = GradientIterator(0, position, gradientSize, palette);
	return GradientInterpolate(paletteIndex, position, smooth, gradientSize, palette, midpoints, midpointSize, mode, colorSpace);
}

// ===================================================================
// COLOR SPACE CONVERTERS FOR GRADIENT SYSTEM V3
// ===================================================================

void RGBtoHSV(float r, float g, float b, float *h, float *s, float *v)
{
	float maxVal = fmax(r, fmax(g, b));
	float minVal = fmin(r, fmin(g, b));
	float d = maxVal - minVal;
	*v = maxVal;
	*s = maxVal == 0.0f ? 0.0f : d / maxVal;
	if (d == 0.0f)
	{
		*h = 0.0f;
	}
	else if (maxVal == r)
	{
		*h = fmod((g - b) / d + 6.0f, 6.0f);
	}
	else if (maxVal == g)
	{
		*h = (b - r) / d + 2.0f;
	}
	else
	{
		*h = (r - g) / d + 4.0f;
	}
	*h /= 6.0f;
}

float3 HSVtoRGB(float h, float s, float v)
{
	h = fmod(h * 6.0f, 6.0f);
	if (h < 0.0f) h += 6.0f;
	int i = (int)h;
	float f = h - i;
	float p = v * (1.0f - s);
	float q = v * (1.0f - f * s);
	float t = v * (1.0f - (1.0f - f) * s);
	switch (i)
	{
		case 0: return (float3)(v, t, p);
		case 1: return (float3)(q, v, p);
		case 2: return (float3)(p, v, t);
		case 3: return (float3)(p, q, v);
		case 4: return (float3)(t, p, v);
		default: return (float3)(v, p, q);
	}
}

// CIE LAB color space (D65 white point)
void RGBtoLAB(float r, float g, float b, float *L, float *a, float *bOut)
{
	// sRGB to linear RGB
	float lr = r > 0.04045f ? pow((r + 0.055f) / 1.055f, 2.4f) : r / 12.92f;
	float lg = g > 0.04045f ? pow((g + 0.055f) / 1.055f, 2.4f) : g / 12.92f;
	float lb = b > 0.04045f ? pow((b + 0.055f) / 1.055f, 2.4f) : b / 12.92f;
	// XYZ (D65)
	float x = lr * 0.4124564f + lg * 0.3575761f + lb * 0.1804375f;
	float y = lr * 0.2126729f + lg * 0.7151522f + lb * 0.0721750f;
	float z = lr * 0.0193339f + lg * 0.1191920f + lb * 0.9503041f;
	// XYZ to LAB
	x = x > 0.008856f ? pow(x, 1.0f / 3.0f) : 7.787f * x + 16.0f / 116.0f;
	y = y > 0.008856f ? pow(y, 1.0f / 3.0f) : 7.787f * y + 16.0f / 116.0f;
	z = z > 0.008856f ? pow(z, 1.0f / 3.0f) : 7.787f * z + 16.0f / 116.0f;
	*L = 116.0f * y - 16.0f;
	*a = 500.0f * (x - y);
	*bOut = 200.0f * (y - z);
}

float3 LABtoRGB(float L, float a, float bIn)
{
	float y = (L + 16.0f) / 116.0f;
	float x = a / 500.0f + y;
	float z = y - bIn / 200.0f;
	x = x > 0.206897f ? x * x * x : (x - 16.0f / 116.0f) / 7.787f;
	y = y > 0.206897f ? y * y * y : (y - 16.0f / 116.0f) / 7.787f;
	z = z > 0.206897f ? z * z * z : (z - 16.0f / 116.0f) / 7.787f;
	float lr = x *  3.2404542f + y * -1.5371385f + z * -0.4985314f;
	float lg = x * -0.9692660f + y *  1.8760108f + z *  0.0415560f;
	float lb = x *  0.0556434f + y * -0.2040259f + z *  1.0572252f;
	float r = lr > 0.0031308f ? 1.055f * pow(lr, 1.0f / 2.4f) - 0.055f : lr * 12.92f;
	float g = lg > 0.0031308f ? 1.055f * pow(lg, 1.0f / 2.4f) - 0.055f : lg * 12.92f;
	float b = lb > 0.0031308f ? 1.055f * pow(lb, 1.0f / 2.4f) - 0.055f : lb * 12.92f;
	return (float3)(clamp(r, 0.0f, 1.0f), clamp(g, 0.0f, 1.0f), clamp(b, 0.0f, 1.0f));
}

// OKLab color space (perceptually uniform, modern alternative to LAB)
void RGBtoOKLab(float r, float g, float b, float *L, float *a, float *bOut)
{
	// sRGB to linear
	float lr = r > 0.04045f ? pow((r + 0.055f) / 1.055f, 2.4f) : r / 12.92f;
	float lg = g > 0.04045f ? pow((g + 0.055f) / 1.055f, 2.4f) : g / 12.92f;
	float lb = b > 0.04045f ? pow((b + 0.055f) / 1.055f, 2.4f) : b / 12.92f;
	// Linear sRGB to LMS
	float l_ = lr * 0.8189330101f + lg * 0.3618667424f + lb * -0.1288597137f;
	float m_ = lr * 0.0329845436f + lg * 0.9293118715f + lb * 0.0361456387f;
	float s_ = lr * 0.0482003018f + lg * 0.2643662691f + lb * 0.6338517070f;
	// LMS to non-linear LMS
	l_ = pow(fabs(l_), 1.0f / 3.0f) * (l_ >= 0.0f ? 1.0f : -1.0f);
	m_ = pow(fabs(m_), 1.0f / 3.0f) * (m_ >= 0.0f ? 1.0f : -1.0f);
	s_ = pow(fabs(s_), 1.0f / 3.0f) * (s_ >= 0.0f ? 1.0f : -1.0f);
	// LMS to OKLab
	*L = l_ * 0.2104542553f + m_ * 0.7936177850f + s_ * -0.0040720468f;
	*a = l_ * 1.9779984951f + m_ * -2.4285922050f + s_ * 0.4505937099f;
	*bOut = l_ * 0.0259040371f + m_ * 0.7827717662f + s_ * -0.8086757660f;
}

float3 OKLabtoRGB(float L, float a, float bIn)
{
	// OKLab to LMS
	float l_ = L * 1.0f + a *  0.3963377774f + bIn * 0.2158037573f;
	float m_ = L * 1.0f + a * -0.1055613458f + bIn * -0.0638541728f;
	float s_ = L * 1.0f + a * -0.0894841775f + bIn * -1.2914855480f;
	// LMS cube
	l_ = l_ * l_ * l_;
	m_ = m_ * m_ * m_;
	s_ = s_ * s_ * s_;
	// LMS to linear sRGB
	float lr = l_ *  4.0767416621f + m_ * -3.3077115913f + s_ *  0.2309699292f;
	float lg = l_ * -1.2684380046f + m_ *  2.6097574011f + s_ * -0.3413193965f;
	float lb = l_ * -0.0041960863f + m_ * -0.7034186147f + s_ *  1.7076147010f;
	// Linear to sRGB
	float r = lr > 0.0031308f ? 1.055f * pow(lr, 1.0f / 2.4f) - 0.055f : lr * 12.92f;
	float g = lg > 0.0031308f ? 1.055f * pow(lg, 1.0f / 2.4f) - 0.055f : lg * 12.92f;
	float b = lb > 0.0031308f ? 1.055f * pow(lb, 1.0f / 2.4f) - 0.055f : lb * 12.92f;
	return (float3)(clamp(r, 0.0f, 1.0f), clamp(g, 0.0f, 1.0f), clamp(b, 0.0f, 1.0f));
}

// Interpolate two colors in a given color space (0=RGB, 1=Linear sRGB UI, 2=HSV, 3=LAB, 4=OKLab, 5=Linear)
float3 InterpolateColorSpace(float3 color1, float3 color2, float delta, int colorSpace)
{
	if (colorSpace == 0) return color1 * (1.0f - delta) + color2 * delta;
	if (colorSpace == 2) // HSV
	{
		float h1, s1, v1, h2, s2, v2;
		RGBtoHSV(color1.x, color1.y, color1.z, &h1, &s1, &v1);
		RGBtoHSV(color2.x, color2.y, color2.z, &h2, &s2, &v2);
		float h = InterpolateHue(h1, h2, delta, 1);
		float s = s1 * (1.0f - delta) + s2 * delta;
		float v = v1 * (1.0f - delta) + v2 * delta;
		return HSVtoRGB(h, s, v);
	}
	if (colorSpace == 3) // LAB
	{
		float L1, a1, b1, L2, a2, b2;
		RGBtoLAB(color1.x, color1.y, color1.z, &L1, &a1, &b1);
		RGBtoLAB(color2.x, color2.y, color2.z, &L2, &a2, &b2);
		float L = L1 * (1.0f - delta) + L2 * delta;
		float a = a1 * (1.0f - delta) + a2 * delta;
		float b = b1 * (1.0f - delta) + b2 * delta;
		return LABtoRGB(L, a, b);
	}
	if (colorSpace == 4) // OKLab
	{
		float L1, a1, b1, L2, a2, b2;
		RGBtoOKLab(color1.x, color1.y, color1.z, &L1, &a1, &b1);
		RGBtoOKLab(color2.x, color2.y, color2.z, &L2, &a2, &b2);
		float L = L1 * (1.0f - delta) + L2 * delta;
		float a = a1 * (1.0f - delta) + a2 * delta;
		float b = b1 * (1.0f - delta) + b2 * delta;
		return OKLabtoRGB(L, a, b);
	}
	if (colorSpace == 1 || colorSpace == 5) // Linear sRGB
	{
		float3 linear1 = (float3)(pow(color1.x, 2.2f), pow(color1.y, 2.2f), pow(color1.z, 2.2f));
		float3 linear2 = (float3)(pow(color2.x, 2.2f), pow(color2.y, 2.2f), pow(color2.z, 2.2f));
		float3 linear = linear1 * (1.0f - delta) + linear2 * delta;
		return (float3)(pow(linear.x, 1.0f / 2.2f), pow(linear.y, 1.0f / 2.2f), pow(linear.z, 1.0f / 2.2f));
	}
	return color1 * (1.0f - delta) + color2 * delta;
}

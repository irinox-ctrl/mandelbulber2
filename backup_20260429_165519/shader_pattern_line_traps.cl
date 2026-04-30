/**
 * Pattern line traps — surface + volumetric helper (world-space lines).
 */

#ifndef PATTERN_LINE_TRAP_RAW_DIST_CL
#define PATTERN_LINE_TRAP_RAW_DIST_CL

/* --- CPU pattern_line_traps.hpp parity (2D SDFs / fractal proxies) --- */

float PatternLineEquilateralIqCl(float y, float z, float r)
{
	const float k = 1.732050807f; /* sqrt(3) */
	float pY = fabs(y) - r;
	float pZ = z + r / k;
	if (pY + k * pZ > 0.0f)
	{
		float ny = 0.5f * (pY - k * pZ);
		float nz = 0.5f * (-k * pY - pZ);
		pY = ny;
		pZ = nz;
	}
	pY = pY - fmax(-2.0f * r, fmin(0.0f, pY));
	return -native_sqrt(pY * pY + pZ * pZ) * (pZ < 0.0f ? -1.0f : 1.0f);
}

float PatternLineSdf2dSegCl(float y, float z, float y0, float z0, float y1, float z1)
{
	float pY = y - y0, pZ = z - z0;
	float bY = y1 - y0, bZ = z1 - z0;
	float b2 = bY * bY + bZ * bZ;
	if (b2 < 1e-60f) return native_sqrt(pY * pY + pZ * pZ);
	float t = fmax(0.0f, fmin(1.0f, (pY * bY + pZ * bZ) / b2));
	float qY = pY - t * bY, qZ = pZ - t * bZ;
	return native_sqrt(qY * qY + qZ * qZ);
}

float PatternLineMandelbrotDeCl(float y, float z, float r, int maxIter)
{
	float s = 2.5f * fmax(1e-30f, r);
	float cr = y / s, ci = z / s;
	if (native_sqrt(cr * cr + ci * ci) > 2.5f) return 10.0f * s;
	float zr = 0, zi = 0, dr = 0, di = 0;
	for (int i = 0; i < maxIter; i++)
	{
		float m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4f)
		{
			float len = native_sqrt(m2);
			float den = native_sqrt(dr * dr + di * di) + 1e-20f;
			return 0.5f * log(m2) * len / den * s;
		}
		dr = 2.0f * (zr * dr - zi * di) + 1.0f;
		di = 2.0f * (zr * di + zi * dr);
		float t = zr * zr - zi * zi + cr;
		zi = 2.0f * zr * zi + ci;
		zr = t;
	}
	return -0.04f * s;
}

float PatternLineJuliaDeCl(float y, float z, float r, int maxIter, float jcr, float jci)
{
	float s = 2.5f * fmax(1e-30f, r);
	float zr = y / s, zi = z / s;
	if (native_sqrt(zr * zr + zi * zi) > 2.5f) return 10.0f * s;
	float dr = 1.0f, di = 0.0f;
	for (int i = 0; i < maxIter; i++)
	{
		float m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4f)
		{
			float len = native_sqrt(m2);
			float den = native_sqrt(dr * dr + di * di) + 1e-20f;
			return 0.5f * log(m2) * len / den * s;
		}
		dr = 2.0f * (zr * dr - zi * di);
		di = 2.0f * (zr * di + zi * dr);
		float t = zr * zr - zi * zi + jcr;
		zi = 2.0f * zr * zi + jci;
		zr = t;
	}
	return -0.04f * s;
}

float PatternLineBurningShipDeSimpleCl(float y, float z, float r, int maxIter)
{
	float s = 2.5f * fmax(1e-30f, r);
	float cr = y / s, ci = z / s;
	if (native_sqrt(cr * cr + ci * ci) > 2.5f) return 10.0f * s;
	float zr = 0, zi = 0;
	for (int i = 0; i < maxIter; i++)
	{
		float x = fabs(zr);
		float yyv = fabs(zi);
		zr = x * x - yyv * yyv + cr;
		zi = 2.0f * x * yyv + ci;
		float m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4f) return 0.25f * log(m2) * s;
	}
	return -0.04f * s;
}

float PatternLineMultibrot3DeCl(float y, float z, float r, int maxIter)
{
	float s = 2.5f * fmax(1e-30f, r);
	float cr = y / s, ci = z / s;
	if (native_sqrt(cr * cr + ci * ci) > 2.5f) return 10.0f * s;
	float zr = 0, zi = 0, dr = 0, di = 0;
	for (int i = 0; i < maxIter; i++)
	{
		float z2r = zr * zr - zi * zi, z2i = 2.0f * zr * zi;
		float z3r = zr * z2r - zi * z2i, z3i = zr * z2i + zi * z2r;
		float ndr = 3.0f * (z2r * dr - z2i * di) + 1.0f, ndi = 3.0f * (z2r * di + z2i * dr);
		zr = z3r + cr;
		zi = z3i + ci;
		dr = ndr;
		di = ndi;
		float m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4f)
		{
			float len = native_sqrt(m2);
			float den = native_sqrt(dr * dr + di * di) + 1e-20f;
			return 0.5f * log(m2) * len / den * s;
		}
	}
	return -0.04f * s;
}

float PatternLineMultibrot4DeCl(float y, float z, float r, int maxIter)
{
	float s = 2.5f * fmax(1e-30f, r);
	float cr = y / s, ci = z / s;
	if (native_sqrt(cr * cr + ci * ci) > 2.5f) return 10.0f * s;
	float zr = 0, zi = 0, dr = 0, di = 0;
	for (int i = 0; i < maxIter; i++)
	{
		float z2r = zr * zr - zi * zi, z2i = 2.0f * zr * zi;
		float z3r = zr * z2r - zi * z2i, z3i = zr * z2i + zi * z2r;
		float z4r = zr * z3r - zi * z3i, z4i = zr * z3i + zi * z3r;
		float ndr = 4.0f * (z3r * dr - z3i * di) + 1.0f, ndi = 4.0f * (z3r * di + z3i * dr);
		zr = z4r + cr;
		zi = z4i + ci;
		dr = ndr;
		di = ndi;
		float m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4f)
		{
			float len = native_sqrt(m2);
			float den = native_sqrt(dr * dr + di * di) + 1e-20f;
			return 0.5f * log(m2) * len / den * s;
		}
	}
	return -0.04f * s;
}

float PatternLineTricornDeSimpleCl(float y, float z, float r, int maxIter)
{
	float s = 2.5f * fmax(1e-30f, r);
	float cr = y / s, ci = z / s;
	if (native_sqrt(cr * cr + ci * ci) > 2.5f) return 10.0f * s;
	float zr = 0, zi = 0;
	for (int i = 0; i < maxIter; i++)
	{
		float t = zr * zr - zi * zi + cr;
		zi = -2.0f * zr * zi + ci;
		zr = t;
		float m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4f) return 0.25f * log(m2) * s;
	}
	return -0.04f * s;
}

float PatternLineJuliaCubicDeCl(float y, float z, float r, int maxIter, float jcr, float jci)
{
	float s = 2.5f * fmax(1e-30f, r);
	float zr = y / s, zi = z / s;
	if (native_sqrt(zr * zr + zi * zi) > 2.5f) return 10.0f * s;
	float dr = 1.0f, di = 0.0f;
	for (int i = 0; i < maxIter; i++)
	{
		float z2r = zr * zr - zi * zi, z2i = 2.0f * zr * zi;
		float z3r = zr * z2r - zi * z2i, z3i = zr * z2i + zi * z2r;
		float ndr = 3.0f * (z2r * dr - z2i * di), ndi = 3.0f * (z2r * di + z2i * dr);
		zr = z3r + jcr;
		zi = z3i + jci;
		dr = ndr;
		di = ndi;
		float m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4f)
		{
			float len = native_sqrt(m2);
			float den = native_sqrt(dr * dr + di * di) + 1e-20f;
			return 0.5f * log(m2) * len / den * s;
		}
	}
	return -0.04f * s;
}

float PatternLineMultibrot5DeCl(float y, float z, float r, int maxIter)
{
	float s = 2.5f * fmax(1e-30f, r);
	float cr = y / s, ci = z / s;
	if (native_sqrt(cr * cr + ci * ci) > 2.5f) return 10.0f * s;
	float zr = 0, zi = 0, dr = 0, di = 0;
	for (int i = 0; i < maxIter; i++)
	{
		float z2r = zr * zr - zi * zi, z2i = 2.0f * zr * zi;
		float z4r = z2r * z2r - z2i * z2i, z4i = 2.0f * z2r * z2i;
		float z5r = z4r * zr - z4i * zi, z5i = z4r * zi + z4i * zr;
		float ndr = 5.0f * (z4r * dr - z4i * di) + 1.0f, ndi = 5.0f * (z4r * di + z4i * dr);
		zr = z5r + cr;
		zi = z5i + ci;
		dr = ndr;
		di = ndi;
		float m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4f)
		{
			float len = native_sqrt(m2);
			float den = native_sqrt(dr * dr + di * di) + 1e-20f;
			return 0.5f * log(m2) * len / den * s;
		}
	}
	return -0.04f * s;
}

float PatternLineTrapProfileExtentCl(sPatternLineTrapLayerCl *layer)
{
	float r = fabs(layer->radius);
	float aux = fmax(1e-30f, layer->shapeAux);
	float sc = fmax(1e-30f, layer->scale);
	float base;
	switch (layer->shape)
	{
		case 1: base = r * 3.0f; break;
		case 4: base = r * fmax(1.0f, aux); break;
		case 9: base = r + aux; break;
		case 5:
		case 7:
		case 10:
		case 15: base = r * 1.05f; break;
		case 11: base = native_sqrt(r * r + (r * fmax(0.2f, aux)) * (r * fmax(0.2f, aux))); break;
		case 12: base = r + r * fmax(0.05f, aux); break;
		case 13: base = r * 1.2f; break;
		case 14: base = r * (1.0f + 0.25f * fmin(1.0f, fmax(0.01f, aux))); break;
		case 16:
		case 17: base = native_sqrt(r * r + (r * fmax(0.1f, aux)) * (r * fmax(0.1f, aux))) * 1.05f; break;
		case 18: base = r * 1.55f; break;
		case 19: base = r * 1.2f; break;
		case 20:
		case 21: base = r * 1.1f; break;
		case 22: base = r * 1.25f; break;
		case 23:
		case 24:
		case 25: base = r * 2.6f; break;
		case 26: base = r * (1.0f + 0.2f * fmin(1.0f, 0.05f * aux)); break;
		case 27: base = r * 1.3f; break;
		case 28:
		case 29: base = r * 1.15f; break;
		case 30: base = r * 1.1f; break;
		case 31: base = r * (1.0f + 0.05f * fmin(1.0f, 0.1f * fabs(aux - 1.0f))); break;
		case 32:
		case 33:
		case 34: base = r * 2.6f; break;
		case 35: base = r * 1.2f; break;
		case 36: base = r * 1.15f; break;
		case 37: base = r * 1.2f; break;
		case 38: base = r * 0.95f; break;
		case 39: base = r * 1.25f; break;
		case 40: base = r * 0.75f; break;
		case 41: base = r * 0.55f; break;
		case 42:
		case 43: base = r * 2.6f; break;
		case 44: base = r * 1.2f; break;
		case 45: base = r * 1.12f; break;
		case 46: base = r * (1.0f + 0.12f * fmin(1.0f, 0.12f * fabs(aux - 1.0f))); break;
		case 47: base = r * 1.2f; break;
		case 48: base = r * 1.05f; break;
		case 49: base = r * 1.05f; break;
		default: base = r; break;
	}
	return base * sc;
}

float PatternLineTrapCrossSectionSignedCl(float y, float z, sPatternLineTrapLayerCl *layer)
{
	float r = layer->radius;
	float aux = fmax(1e-30f, layer->shapeAux);
	switch (layer->shape)
	{
		case 0:
			return native_sqrt(y * y + z * z) - r;
		case 1:
			return fabs(z) - r;
		case 2:
			return fmax(fabs(y), fabs(z)) - r;
		case 3:
			return fabs(y) + fabs(z) - r;
		case 4:
			return native_sqrt((y * y) / (r * r) + (z * z) / (r * r * aux * aux)) - 1.0f;
		case 5:
		{
			float angle = atan2(z, y);
			float rad = native_sqrt(y * y + z * z);
			float sector = M_PI_F / 3.0f;
			float halfSector = 0.5f * sector;
			float a = angle;
			a -= sector * floor((a + halfSector) / sector);
			a -= halfSector;
			return native_cos(a) * rad - r;
		}
		case 6:
			return fmin(fabs(y), fabs(z)) - r;
		case 7:
		{
			float angle = atan2(z, y);
			float rad = native_sqrt(y * y + z * z);
			float sector = M_PI_F / 4.0f;
			float halfSector = 0.5f * sector;
			float a = angle;
			a -= sector * floor((a + halfSector) / sector);
			a -= halfSector;
			return native_cos(a) * rad - r;
		}
		case 8:
		{
			/* Squircle: pow() — NVIDIA OpenCL has no native_pow (ptxas unresolved). */
			float yr = fabs(y) / r;
			float zr = fabs(z) / r;
			float y4 = yr * yr * yr * yr;
			float z4 = zr * zr * zr * zr;
			return pow(y4 + z4, 0.25f) - 1.0f;
		}
		case 9:
			return fabs(native_sqrt(y * y + z * z) - r) - aux;
		case 10:
		{
			float angle = atan2(z, y);
			float rad = native_sqrt(y * y + z * z);
			float sector = 2.0f * M_PI_F / 5.0f;
			float halfSector = 0.5f * sector;
			float a = angle;
			a -= sector * floor((a + halfSector) / sector);
			a -= halfSector;
			return native_cos(a) * rad - r;
		}
		case 11:
		{
			float bz = r * fmax(0.2f, aux);
			return fmax(fabs(y) - r, fabs(z) - bz);
		}
		case 12:
		{
			float L = r * fmax(0.05f, aux);
			float bx = 2.0f * L;
			float h = (bx > 1e-30f) ? fmax(0.0f, fmin(1.0f, ((y + L) * bx) / (bx * bx))) : 0.0f;
			float qy = y - (-L + h * 2.0f * L);
			return native_sqrt(qy * qy + z * z) - r;
		}
		case 13:
			return PatternLineEquilateralIqCl(y, z, r);
		case 14:
		{
			float ang = atan2(z, y);
			float rad = native_sqrt(y * y + z * z);
			float kdep = 0.25f * fmin(fmax(aux, 0.01f), 1.0f);
			float Rb = r * (1.0f + kdep * native_cos(5.0f * ang));
			return rad - Rb;
		}
		case 15:
		{
			float angle = atan2(z, y);
			float rad = native_sqrt(y * y + z * z);
			float sector = M_PI_F / 5.0f;
			float halfSector = 0.5f * sector;
			float a = angle;
			a -= sector * floor((a + halfSector) / sector);
			a -= halfSector;
			return native_cos(a) * rad - r;
		}
		case 16:
		{
			float bz = r * fmax(0.1f, aux);
			float ay = fabs(y) / r;
			float az = fabs(z) / bz;
			return pow(ay * ay * ay + az * az * az, 0.33333333f) * r - r;
		}
		case 17:
		{
			float bz = r * fmax(0.1f, aux);
			float ay = fabs(y) / r;
			float az = fabs(z) / bz;
			float a6 = ay * ay * ay * ay * ay * ay;
			float b6 = az * az * az * az * az * az;
			return pow(a6 + b6, 0.16666667f) * r - r;
		}
		case 18:
		{
			float dx = r * 0.4f * fmin(fmax(aux, 0.1f), 2.0f);
			float rin = 0.5f * r;
			float d0 = native_sqrt(y * y + z * z) - r;
			float d1 = rin - native_sqrt((y - dx) * (y - dx) + z * z);
			return fmax(d0, d1);
		}
		case 19:
		{
			float ang = atan2(z, y);
			float rad = native_sqrt(y * y + z * z);
			float n = 4.0f + floor(fmin(12.0f, fmax(4.0f, 4.0f + aux * 2.0f)));
			float w = 0.1f * (1.0f - 0.5f * (n - 4.0f) / 8.0f);
			float Rb = r * (1.0f + w * native_cos(n * ang));
			return rad - Rb;
		}
		case 20: /* Sierpinski carpet (1 level) */
		{
			float o = 2.0f * r / 3.0f, h = r / 3.0f;
			float d = 1e20f;
			float cy[8];
			float cz[8];
			cy[0] = o;
			cy[1] = o;
			cy[2] = -o;
			cy[3] = -o;
			cy[4] = 0.0f;
			cy[5] = 0.0f;
			cy[6] = o;
			cy[7] = -o;
			cz[0] = o;
			cz[1] = -o;
			cz[2] = o;
			cz[3] = -o;
			cz[4] = o;
			cz[5] = -o;
			cz[6] = 0.0f;
			cz[7] = 0.0f;
			for (int i = 0; i < 8; i++)
			{
				float qY = fabs(y - cy[i]) - h;
				float qZ = fabs(z - cz[i]) - h;
				float dd = fmin(fmax(qY, qZ), 0.0f) + native_sqrt(fmax(qY, 0.0f) * fmax(qY, 0.0f) + fmax(qZ, 0.0f) * fmax(qZ, 0.0f));
				d = fmin(d, dd);
			}
			return d;
		}
		case 21: /* Sierpinski triangle (1 level) */
		{
			float t = 0.5f * r, rt3 = 0.25f * r * 1.732050807f;
			float d = PatternLineEquilateralIqCl(y, z - 0.5f * r, t);
			d = fmin(d, PatternLineEquilateralIqCl(y + rt3, z + 0.25f * r, t));
			d = fmin(d, PatternLineEquilateralIqCl(y - rt3, z + 0.25f * r, t));
			return d;
		}
		case 22: /* Koch 1-iteration segment chain */
		{
			float s = 1.1f * r, h = s * 1.732050807f / 6.0f;
			float y0 = -s, y1 = y0 + s / 3.0f, y2 = 0.0f, y3 = s / 3.0f, y4 = s;
			float s01 = PatternLineSdf2dSegCl(y, z, y0, 0.0f, y1, 0.0f);
			float s12 = PatternLineSdf2dSegCl(y, z, y1, 0.0f, y2, h);
			float s23 = PatternLineSdf2dSegCl(y, z, y2, h, y3, 0.0f);
			float s34 = PatternLineSdf2dSegCl(y, z, y3, 0.0f, y4, 0.0f);
			float m = fmin(fmin(s01, s12), fmin(s23, s34));
			float aex = fmin(1.0f, 0.1f * fabs(aux - 1.0f) + 1.0f);
			return m - 0.05f * s * (0.5f + 0.5f * aex);
		}
		case 23: /* Mandelbrot */
		{
			int mi = (int)(32.0f + 40.0f * (aux - 1.0f) + 0.5f);
			mi = max(8, min(256, mi));
			return PatternLineMandelbrotDeCl(y, z, r, mi);
		}
		case 24: /* Julia */
		{
			float tt = 0.15f * (aux - 1.0f);
			float jcr = 0.355f + 0.05f * native_cos(tt);
			float jci = 0.355f + 0.05f * native_sin(tt);
			return PatternLineJuliaDeCl(y, z, r, 64, jcr, jci);
		}
		case 25: /* Burning ship */
		{
			int mi = (int)(24.0f + 40.0f * (aux - 1.0f) + 0.5f);
			mi = max(8, min(256, mi));
			return PatternLineBurningShipDeSimpleCl(y, z, r, mi);
		}
		case 26: /* Cantor slats */
		{
			float w = r * 0.15f, g = 0.35f * r * fmin(0.8f, 0.1f + 0.05f * aux);
			float d0 = fmax(fabs(y) - w, fabs(z - g) - w * 0.3f);
			float d1 = fmax(fabs(y) - w, fabs(z + g) - w * 0.3f);
			return fmin(d0, d1);
		}
		case 27: /* Pythagoras tree (three squares) */
		{
			float br = 0.35f + 0.12f * fmin(1.0f, 0.15f * fabs(aux - 1.0f));
			float c = native_cos(br), sn = native_sin(br);
			float s0 = fmax(fabs(y) - 0.45f * r, fabs(z) - 0.3f * r);
			float t2 = 0.22f * r, px = 0.45f * r, pz = 0.3f * r;
			float s1 = fmax(fabs(c * (y + px) + sn * (z - pz)) - t2, fabs(-sn * (y + px) + c * (z - pz)) - t2);
			float s2 = fmax(fabs(c * (y - px) - sn * (z - pz)) - t2, fabs(sn * (y - px) + c * (z - pz)) - t2);
			return fmin(s0, fmin(s1, s2));
		}
		case 28: /* Heighway-style polyline */
		{
			float s = 0.22f * r, ox = 0.0f, oz = 0.25f * r;
			float pY0 = 0.0f, pY1 = s, pY2 = 2.0f * s, pY3 = 2.0f * s, pY4 = 3.0f * s, pY5 = 3.0f * s, pY6 = 2.0f * s;
			float pZ0 = 0.0f, pZ1 = 0.0f, pZ2 = 0.0f, pZ3 = s, pZ4 = s, pZ5 = 2.0f * s, pZ6 = 2.0f * s;
			float m = 1e20f;
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY0 - ox, pZ0 - oz, pY1 - ox, pZ1 - oz));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY1 - ox, pZ1 - oz, pY2 - ox, pZ2 - oz));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY2 - ox, pZ2 - oz, pY3 - ox, pZ3 - oz));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY3 - ox, pZ3 - oz, pY4 - ox, pZ4 - oz));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY4 - ox, pZ4 - oz, pY5 - ox, pZ5 - oz));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY5 - ox, pZ5 - oz, pY6 - ox, pZ6 - oz));
			return m - 0.04f * s;
		}
		case 29: /* Hilbert order-1 U */
		{
			float a = 0.75f * r;
			float pY0 = -a, pY1 = -a, pY2 = a, pY3 = a;
			float pZ0 = -a, pZ1 = a, pZ2 = a, pZ3 = -a;
			float m = 1e20f;
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY0, pZ0, pY1, pZ1));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY1, pZ1, pY2, pZ2));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY2, pZ2, pY3, pZ3));
			return m - 0.03f * r;
		}
		case 30: /* Vicsek */
		{
			float o = 2.0f * r / 3.0f, h = r / 3.0f;
			float d = 1e20f;
			float cy[5];
			float cz[5];
			cy[0] = 0;
			cy[1] = o;
			cy[2] = o;
			cy[3] = -o;
			cy[4] = -o;
			cz[0] = 0;
			cz[1] = o;
			cz[2] = -o;
			cz[3] = o;
			cz[4] = -o;
			for (int i = 0; i < 5; i++)
			{
				float qY = fabs(y - cy[i]) - h;
				float qZ = fabs(z - cz[i]) - h;
				float dd = fmin(fmax(qY, qZ), 0.0f) + native_sqrt(fmax(qY, 0.0f) * fmax(qY, 0.0f) + fmax(qZ, 0.0f) * fmax(qZ, 0.0f));
				d = fmin(d, dd);
			}
			return d;
		}
		case 31: /* Greek cross */
		{
			float w = r * (0.22f + 0.1f * fmin(1.0f, 0.2f * fabs(aux - 1.0f)));
			float dv = fmax(fabs(y) - w, fabs(z) - r);
			float dh = fmax(fabs(y) - r, fabs(z) - w);
			return fmin(dv, dh);
		}
		case 32:
		{
			int mi = (int)(28.0f + 36.0f * (aux - 1.0f) + 0.5f);
			mi = max(8, min(256, mi));
			return PatternLineMultibrot3DeCl(y, z, r, mi);
		}
		case 33:
		{
			int mi = (int)(24.0f + 32.0f * (aux - 1.0f) + 0.5f);
			mi = max(8, min(256, mi));
			return PatternLineMultibrot4DeCl(y, z, r, mi);
		}
		case 34:
		{
			int mi = (int)(24.0f + 40.0f * (aux - 1.0f) + 0.5f);
			mi = max(8, min(256, mi));
			return PatternLineTricornDeSimpleCl(y, z, r, mi);
		}
		case 35: /* ternary Y */
		{
			float L = 0.48f * r, m = 1e20f;
			for (int k = 0; k < 3; k++)
			{
				float ang = -M_PI_F * 0.5f + (2.0f * M_PI_F * (float)k) / 3.0f;
				float y1 = L * native_cos(ang), z1 = L * native_sin(ang);
				m = fmin(m, PatternLineSdf2dSegCl(y, z, 0, 0, y1, z1));
			}
			return m - 0.04f * r;
		}
		case 36: /* Peano-like */
		{
			float a = 0.65f * r;
			float pY0 = -a, pY1 = 0, pY2 = a, pY3 = a, pY4 = 0, pY5 = -a, pY6 = -a, pY7 = 0, pY8 = a;
			float pZ0 = -a, pZ1 = -a, pZ2 = -a, pZ3 = 0, pZ4 = 0, pZ5 = 0, pZ6 = a, pZ7 = a, pZ8 = a;
			float m = 1e20f;
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY0, pZ0, pY1, pZ1));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY1, pZ1, pY2, pZ2));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY2, pZ2, pY3, pZ3));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY3, pZ3, pY4, pZ4));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY4, pZ4, pY5, pZ5));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY5, pZ5, pY6, pZ6));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY6, pZ6, pY7, pZ7));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, pY7, pZ7, pY8, pZ8));
			return m - 0.03f * r;
		}
		case 37: /* Levy C */
		{
			float s = 1.4f * r, h = s * 0.5f;
			float m = fmin(PatternLineSdf2dSegCl(y, z, 0, 0, 0.5f * s, h), PatternLineSdf2dSegCl(y, z, 0.5f * s, h, s, 0));
			return m - 0.04f * r;
		}
		case 38: /* concentric ring gaps */
		{
			float rad = native_sqrt(y * y + z * z);
			float t = 0.045f * r;
			float r0 = 0.32f * r, r1 = 0.5f * r, r2 = 0.7f * r;
			float d0 = fabs(rad - r0) - t, d1 = fabs(rad - r1) - t, d2 = fabs(rad - r2) - t;
			return fmin(fmin(d0, d1), d2);
		}
		case 39: /* golden L */
		{
			const float g = 1.618034f;
			float w = 0.14f * r, l1 = 0.55f * r, l2 = 0.55f * r * g;
			float s1 = fmax(fabs(y) - w, fabs(z - 0.4f * r) - l1 * 0.5f);
			float s2 = fmax(fabs(y - 0.32f * r) - l2 * 0.5f, fabs(z + 0.1f * r) - w);
			return fmin(s1, s2);
		}
		case 40: /* three circles */
		{
			const float R0 = 0.24f * r;
			const float cY0 = 0, cY1 = -0.32f * r, cY2 = 0.32f * r;
			const float cZ0 = 0.38f * r, cZ1 = -0.2f * r, cZ2 = -0.2f * r;
			float m = 1e20f;
			float d0 = fabs(native_sqrt((y - cY0) * (y - cY0) + (z - cZ0) * (z - cZ0)) - R0) - 0.03f * r;
			float d1 = fabs(native_sqrt((y - cY1) * (y - cY1) + (z - cZ1) * (z - cZ1)) - R0) - 0.03f * r;
			float d2 = fabs(native_sqrt((y - cY2) * (y - cY2) + (z - cZ2) * (z - cZ2)) - R0) - 0.03f * r;
			return fmin(fmin(d0, d1), d2);
		}
		case 41: /* Lissajous */
		{
			const int Nm = 40;
			const float A = 0.45f * r, B = 0.45f * r;
			float m = 1e20f;
			for (int k = 0; k < Nm; k++)
			{
				float t0 = 2.0f * M_PI_F * (float)k / 40.0f, t1 = 2.0f * M_PI_F * (float)(k + 1) / 40.0f;
				float y0 = A * native_sin(2.0f * t0), z0 = B * native_sin(3.0f * t0);
				float y1 = A * native_sin(2.0f * t1), z1 = B * native_sin(3.0f * t1);
				m = fmin(m, PatternLineSdf2dSegCl(y, z, y0, z0, y1, z1));
			}
			return m - 0.03f * r;
		}
		case 42: /* Julia cubic */
		{
			float t = 0.12f * (aux - 1.0f);
			float jcr = 0.38f * native_cos(t), jci = 0.2f * native_sin(t);
			return PatternLineJuliaCubicDeCl(y, z, r, 64, jcr, jci);
		}
		case 43: /* Multibrot 5 */
		{
			int mi = (int)(20.0f + 28.0f * (aux - 1.0f) + 0.5f);
			mi = max(8, min(256, mi));
			return PatternLineMultibrot5DeCl(y, z, r, mi);
		}
		case 44: /* H-tree */
		{
			float L = 0.45f * r, hw = 0.34f * r;
			float a = PatternLineSdf2dSegCl(y, z, 0, -L, 0, L);
			a = fmin(a, PatternLineSdf2dSegCl(y, z, -hw, L, hw, L));
			a = fmin(a, PatternLineSdf2dSegCl(y, z, -hw, -L, hw, -L));
			return a - 0.04f * r;
		}
		case 45: /* carpet 2 */
		{
			const float o1 = 2.0f * r / 3.0f, h1 = r / 3.0f, o2 = 2.0f * r / 9.0f, h2 = r / 9.0f;
			const float c1y[8] = {o1, o1, -o1, -o1, 0, 0, o1, -o1};
			const float c1z[8] = {o1, -o1, o1, -o1, o1, -o1, 0, 0};
			const float c2y[8] = {o2, o2, -o2, -o2, 0, 0, o2, -o2};
			const float c2z[8] = {o2, -o2, o2, -o2, o2, -o2, 0, 0};
			float d = 1e20f;
			for (int a = 0; a < 8; a++)
			{
				for (int b = 0; b < 8; b++)
				{
					float qY = fabs(y - c1y[a] - c2y[b]) - h2;
					float qZ = fabs(z - c1z[a] - c2z[b]) - h2;
					float dd = fmin(fmax(qY, qZ), 0.0f) + native_sqrt(fmax(qY, 0.0f) * fmax(qY, 0.0f) + fmax(qZ, 0.0f) * fmax(qZ, 0.0f));
					d = fmin(d, dd);
				}
			}
			return d;
		}
		case 46: /* hex ripples */
		{
			float ang = atan2(z, y);
			float rad = native_sqrt(y * y + z * z);
			float w = 0.1f * r * fmin(1.0f, 0.15f * fabs(aux - 1.0f));
			float Rb = r * (1.0f + w * native_cos(6.0f * ang));
			return rad - Rb;
		}
		case 47: /* binary tree */
		{
			float s = r, m;
			m = PatternLineSdf2dSegCl(y, z, 0, 0, 0, 0.35f * s);
			m = fmin(m, PatternLineSdf2dSegCl(y, z, 0, 0.35f * s, -0.22f * s, 0.55f * s));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, 0, 0.35f * s, 0.22f * s, 0.55f * s));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, -0.22f * s, 0.55f * s, -0.32f * s, 0.68f * s));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, -0.22f * s, 0.55f * s, -0.1f * s, 0.68f * s));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, 0.22f * s, 0.55f * s, 0.1f * s, 0.68f * s));
			m = fmin(m, PatternLineSdf2dSegCl(y, z, 0.22f * s, 0.55f * s, 0.32f * s, 0.68f * s));
			return m - 0.04f * s;
		}
		case 48: /* Fermat spiral */
		{
			float th = fmod(atan2(z, y) + 2.0f * M_PI_F, 2.0f * M_PI_F);
			float rad = native_sqrt(y * y + z * z);
			float a = 0.14f * r * (0.8f + 0.2f * fmin(1.0f, 0.1f * fabs(aux - 1.0f)));
			float angp = fmax(0.0f, th) + 1e-6f;
			float rt = a * native_sqrt(angp);
			return fabs(rad - rt) - 0.04f * r;
		}
		case 49: /* double cross */
		{
			float w1 = 0.2f * r, w2 = 0.12f * r;
			float d1a = fmax(fabs(y) - w1, fabs(z) - r);
			float d1b = fmax(fabs(y) - r, fabs(z) - w1);
			float d2a = fmax(fabs(y) - w2, fabs(z) - 0.75f * r);
			float d2b = fmax(fabs(y) - 0.75f * r, fabs(z) - w2);
			return fmin(fmin(d1a, d1b), fmin(d2a, d2b));
		}
		default:
			return native_sqrt(y * y + z * z) - r;
	}
}

float PatternLineTrapProfileRawDistCl(float y, float z, sPatternLineTrapLayerCl *layer)
{
	float sc = fmax(1e-30f, layer->scale);
	float dist = PatternLineTrapCrossSectionSignedCl(y / sc, z / sc, layer) * sc;
	if (layer->edgeSoftness > 0.0f)
	{
		float es = layer->edgeSoftness * 2.5f;
		dist = native_sqrt(dist * dist + es * es) - es;
	}
	float denom = fmax(1e-30f, layer->thickness * fmax(1e-30f, layer->relativeThickness));
	return dist / denom;
}

float3 PatternLineTrapGradientRgbCl(float t, float3 c0, float3 c1, float3 c2)
{
	t = clamp(t, 0.0f, 1.0f);
	if (t < 0.5f)
	{
		float tt = t * 2.0f;
		return c0 * (1.0f - tt) + c1 * tt;
	}
	float tt = (t - 0.5f) * 2.0f;
	return c1 * (1.0f - tt) + c2 * tt;
}

float3 PatternLineTrapsShader(__constant sClInConstants *consts, float3 point,
	sShaderInputDataCl *input, sClGradientsCollection *gradients)
{
	float3 result = 0.0f;
	if (!consts->params.patternLineTraps.enabled) return result;

	int soloL = consts->params.patternLineTraps.soloLayerIndex;
	for (int i = 0; i < PATTERN_LINE_TRAP_COUNT; i++)
	{
		if (soloL > 0 && soloL != i + 1) continue;
		__constant sPatternLineTrapLayerCl *layer = &consts->params.patternLineTraps.layers[i];
		if (!layer->enabled) continue;

		sPatternLineTrapLayerCl effLayer = *layer;
		if (layer->relativeSize > 0.0f)
		{
			float camDist = length(consts->params.camera - layer->position.xyz);
			effLayer.radius *= camDist * layer->relativeSize;
		}

		float3 delta = Matrix33MulFloat3(effLayer.mRotRotation, point - effLayer.position.xyz);

		if (effLayer.maxDistance > 1e-30f || effLayer.segmentHalfLength > 1e-30f)
		{
			float margin = PatternLineTrapProfileExtentCl(&effLayer) + fabs(effLayer.edgeSoftness);
			if (effLayer.maxDistance > 1e-30f) margin += effLayer.maxDistance;
			if (effLayer.segmentHalfLength > 1e-30f) margin += effLayer.segmentHalfLength;
			if (length(delta) > margin * 2.8f) continue;
		}

		float axialFade = 1.0f;
		if (effLayer.segmentHalfLength > 1e-30f)
		{
			float ax = fabs(delta.x);
			float t = ax / effLayer.segmentHalfLength;
			if (t >= 1.0f) continue;
			t = t * t * (3.0f - 2.0f * t);
			axialFade = 1.0f - t;
		}

		float rawDist = PatternLineTrapProfileRawDistCl(delta.y, delta.z, &effLayer);
		float wallDist;
		if (effLayer.edgeSide == 0)
			wallDist = fabs(rawDist);
		else if (effLayer.edgeSide == 1)
			wallDist = fmax(rawDist, 0.0f);
		else
			wallDist = fmax(-rawDist, 0.0f);

		float fade = 1.0f;
		if (effLayer.maxDistance > 1e-30f)
		{
			float t = wallDist / effLayer.maxDistance;
			if (t >= 1.0f) continue;
			t = t * t * (3.0f - 2.0f * t);
			fade = 1.0f - t;
		}

		float sharp = fmax(0.25f, effLayer.falloffSharpness);
		float spread = fmax(1e-6f, effLayer.glowSpread);
		float u = wallDist * sharp / spread;
		float falloff;
		if (effLayer.falloffProfile == 0)
			falloff = native_exp(-u * u);
		else if (effLayer.falloffProfile == 1)
		{
			float t = fmin(1.0f, u);
			falloff = 1.0f - t * t * (3.0f - 2.0f * t);
		}
		else if (effLayer.falloffProfile == 2)
		{
			float t = fmin(1.0f, u);
			falloff = 1.0f - t;
		}
		else
			falloff = native_exp(-u);
		float intens = effLayer.intensity * falloff * fade * axialFade;
		float tGrad;
		if (gradients != NULL && consts->params.patternLineTraps.coloringMode == 1)
		{
			float nCol = fmod(fabs(gradients->colorIndex), 248.0f * 256.0f);
			tGrad = fmod(nCol / 256.0f / 10.0f * input->material->coloring_speed
							 + input->material->paletteOffset,
				1.0f);
		}
		else if (gradients != NULL && consts->params.patternLineTraps.coloringMode == 2)
		{
			tGrad = fmod(gradients->iters / consts->params.N * input->material->coloring_speed
							 + input->material->paletteOffset,
				1.0f);
		}
		else
		{
			tGrad = u;
		}
		float3 gradCol = PatternLineTrapGradientRgbCl(
			tGrad, effLayer.color.xyz, effLayer.color2.xyz, effLayer.color3.xyz);

		if (consts->params.patternLineTraps.combineMode == 0)
		{
			result += intens * gradCol;
		}
		else
		{
			result = fmax(result, intens * gradCol);
		}
	}
	return result;
}

#endif /* PATTERN_LINE_TRAP_RAW_DIST_CL */

/**
 * Mandelbulber — simple pattern line traps (parallel to single-trap lights).
 * Fixed count, line shape only, world-space position + rotation.
 */

#ifndef MANDELBULBER2_SRC_PATTERN_LINE_TRAPS_HPP_
#define MANDELBULBER2_SRC_PATTERN_LINE_TRAPS_HPP_

#include <algorithm>
#include <cmath>

#include "algebra.hpp"
#include "color_structures.hpp"

const int PATTERN_LINE_TRAP_COUNT = 20;

/** Cross-section profile in the YZ plane (X = pattern axis after rotation). See initparameters combo order. */
struct sPatternLineTrapLayer
{
	bool enabled;
	CVector3 position;
	CVector3 rotation;
	CRotationMatrix mRotRotation;
	double radius;
	double thickness;
	/** Uniform cross-section scale in YZ (1 = default). SDF: sdf_scaled = scale * sdf(y/scale, z/scale). */
	double scale;
	/** Multiplier on effective band thickness (1 = use thickness as-is). */
	double relativeThickness;
	double edgeSoftness;
	double intensity;
	double maxDistance;
	/** Higher = thinner line band (Gaussian); typical 12–40. */
	double falloffSharpness;
	/** Widen/soften the visible rim: divides sharpness in the falloff (1 = default, higher = softer/wider). */
	double glowSpread;
	/** 0 Gauss, 1 smoothstep, 2 linear, 3 exponential. */
	int falloffProfile;
	/** 0 = glow on both sides of profile (|sd|), 1 = outside only, 2 = inside only. */
	int edgeSide;
	/** Half-length along local X; 0 = infinite line. */
	double segmentHalfLength;
	/** Profile index 0…49 (combo in UI). */
	int shape;
	/** Ellipse: Z radius / Y radius. Ring: half tube thickness. */
	double shapeAux;
	/** >0: radius scales with camera distance (like single-trap lights). */
	double relativeSize;
	sRGBFloat color;
	sRGBFloat color2;
	sRGBFloat color3;

	sPatternLineTrapLayer()
			: enabled(false),
				position(0.0, 0.0, 0.0),
				rotation(0.0, 0.0, 0.0),
				radius(0.05),
				thickness(1.0),
				scale(1.0),
				relativeThickness(1.0),
				edgeSoftness(0.0),
				intensity(1.0),
				maxDistance(5.0),
				falloffSharpness(22.0),
				glowSpread(1.0),
				falloffProfile(0),
				edgeSide(0),
				segmentHalfLength(0.0),
				shape(0),
				shapeAux(1.0),
				relativeSize(0.0),
				color(1.0f, 1.0f, 1.0f),
				color2(1.0f, 1.0f, 1.0f),
				color3(1.0f, 1.0f, 1.0f)
	{
	}

	void UpdateRotationMatrix()
	{
		mRotRotation.SetRotation2(rotation * M_PI / 180.0);
	}
};

/** Equilateral triangle 2D SDF, circumradius r (Iñigo Quílez, vertex toward +Z). */
inline double PatternLineEquilateralIq(double y, double z, double r)
{
	const double k = std::sqrt(3.0);
	double pY = std::fabs(y) - r;
	double pZ = z + r / k;
	if (pY + k * pZ > 0.0)
	{
		const double ny = 0.5 * (pY - k * pZ);
		const double nz = 0.5 * (-k * pY - pZ);
		pY = ny;
		pZ = nz;
	}
	pY = pY - std::max(-2.0 * r, std::min(0.0, pY));
	return -std::hypot(pY, pZ) * (pZ < 0.0 ? -1.0 : 1.0);
}

/** 2D distance to segment (y0,z0)–(y1,z1). */
inline double PatternLineSdf2dSeg(double y, double z, double y0, double z0, double y1, double z1)
{
	const double pY = y - y0, pZ = z - z0;
	const double bY = y1 - y0, bZ = z1 - z0;
	const double b2 = bY * bY + bZ * bZ;
	if (b2 < 1e-60) return std::hypot(pY, pZ);
	const double t = std::max(0.0, std::min(1.0, (pY * bY + pZ * bZ) / b2));
	const double qY = pY - t * bY, qZ = pZ - t * bZ;
	return std::sqrt(qY * qY + qZ * qZ);
}

/** Mandelbrot distance estimate; c = (y+iz)/s, s = 2.5r. */
inline double PatternLineMandelbrotDe(double y, double z, double r, int maxIter)
{
	const double s = 2.5 * std::max(1e-30, r);
	const double cr = y / s, ci = z / s;
	if (std::hypot(cr, ci) > 2.5) return 10.0 * s;
	double zr = 0, zi = 0;
	double dr = 0, di = 0;
	for (int i = 0; i < maxIter; i++)
	{
		const double m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4)
		{
			const double len = std::sqrt(m2);
			const double den = std::sqrt(dr * dr + di * di) + 1e-20;
			return 0.5 * std::log(m2) * len / den * s;
		}
		dr = 2.0 * (zr * dr - zi * di) + 1.0;
		di = 2.0 * (zr * di + zi * dr);
		const double t = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci;
		zr = t;
	}
	return -0.04 * s;
}

/** Julia set DE; z0 = (y+iz)/s, fixed julia c. */
inline double PatternLineJuliaDe(double y, double z, double r, int maxIter, double jcr, double jci)
{
	const double s = 2.5 * std::max(1e-30, r);
	const double zr0 = y / s, zi0 = z / s;
	if (std::hypot(zr0, zi0) > 2.5) return 10.0 * s;
	double zr = zr0, zi = zi0;
	double dr = 1.0, di = 0.0;
	for (int i = 0; i < maxIter; i++)
	{
		const double m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4)
		{
			const double len = std::sqrt(m2);
			const double den = std::sqrt(dr * dr + di * di) + 1e-20;
			return 0.5 * std::log(m2) * len / den * s;
		}
		dr = 2.0 * (zr * dr - zi * di);
		di = 2.0 * (zr * di + zi * dr);
		const double t = zr * zr - zi * zi + jcr;
		zi = 2.0 * zr * zi + jci;
		zr = t;
	}
	return -0.04 * s;
}

/** Burning ship (|x|+i|y|)^2 + c, exterior size proxy. */
inline double PatternLineBurningShipDeSimple(double y, double z, double r, int maxIter)
{
	const double s = 2.5 * std::max(1e-30, r);
	const double cr = y / s, ci = z / s;
	if (std::hypot(cr, ci) > 2.5) return 10.0 * s;
	double zr = 0, zi = 0;
	for (int i = 0; i < maxIter; i++)
	{
		const double x = std::fabs(zr);
		const double yyv = std::fabs(zi);
		zr = x * x - yyv * yyv + cr;
		zi = 2.0 * x * yyv + ci;
		const double m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4) return 0.25 * std::log(m2) * s;
	}
	return -0.04 * s;
}

/** z^3 + c, distance estimate (multibrot p=3). */
inline double PatternLineMultibrot3De(double y, double z, double r, int maxIter)
{
	const double s = 2.5 * std::max(1e-30, r);
	const double cr = y / s, ci = z / s;
	if (std::hypot(cr, ci) > 2.5) return 10.0 * s;
	double zr = 0, zi = 0, dr = 0, di = 0;
	for (int i = 0; i < maxIter; i++)
	{
		const double z2r = zr * zr - zi * zi, z2i = 2.0 * zr * zi;
		const double z3r = zr * z2r - zi * z2i, z3i = zr * z2i + zi * z2r;
		const double ndr = 3.0 * (z2r * dr - z2i * di) + 1.0, ndi = 3.0 * (z2r * di + z2i * dr);
		zr = z3r + cr;
		zi = z3i + ci;
		dr = ndr;
		di = ndi;
		const double m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4)
		{
			const double len = std::sqrt(m2);
			const double den = std::sqrt(dr * dr + di * di) + 1e-20;
			return 0.5 * std::log(m2) * len / den * s;
		}
	}
	return -0.04 * s;
}

/** z^4 + c, distance estimate (multibrot p=4). */
inline double PatternLineMultibrot4De(double y, double z, double r, int maxIter)
{
	const double s = 2.5 * std::max(1e-30, r);
	const double cr = y / s, ci = z / s;
	if (std::hypot(cr, ci) > 2.5) return 10.0 * s;
	double zr = 0, zi = 0, dr = 0, di = 0;
	for (int i = 0; i < maxIter; i++)
	{
		const double z2r = zr * zr - zi * zi, z2i = 2.0 * zr * zi;
		const double z3r = zr * z2r - zi * z2i, z3i = zr * z2i + zi * z2r;
		const double z4r = zr * z3r - zi * z3i, z4i = zr * z3i + zi * z3r;
		const double ndr = 4.0 * (z3r * dr - z3i * di) + 1.0, ndi = 4.0 * (z3r * di + z3i * dr);
		zr = z4r + cr;
		zi = z4i + ci;
		dr = ndr;
		di = ndi;
		const double m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4)
		{
			const double len = std::sqrt(m2);
			const double den = std::sqrt(dr * dr + di * di) + 1e-20;
			return 0.5 * std::log(m2) * len / den * s;
		}
	}
	return -0.04 * s;
}

/** Tricorn: conj(z)^2 + c, exterior size proxy. */
inline double PatternLineTricornDeSimple(double y, double z, double r, int maxIter)
{
	const double s = 2.5 * std::max(1e-30, r);
	const double cr = y / s, ci = z / s;
	if (std::hypot(cr, ci) > 2.5) return 10.0 * s;
	double zr = 0, zi = 0;
	for (int i = 0; i < maxIter; i++)
	{
		const double t = zr * zr - zi * zi + cr;
		zi = -2.0 * zr * zi + ci;
		zr = t;
		const double m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4) return 0.25 * std::log(m2) * s;
	}
	return -0.04 * s;
}

/** Julia z^3 + c, distance estimate (d/dz0). */
inline double PatternLineJuliaCubicDe(double y, double z, double r, int maxIter, double jcr, double jci)
{
	const double s = 2.5 * std::max(1e-30, r);
	double zr = y / s, zi = z / s;
	if (std::hypot(zr, zi) > 2.5) return 10.0 * s;
	double dr = 1.0, di = 0.0;
	for (int i = 0; i < maxIter; i++)
	{
		const double z2r = zr * zr - zi * zi, z2i = 2.0 * zr * zi;
		const double z3r = zr * z2r - zi * z2i, z3i = zr * z2i + zi * z2r;
		const double ndr = 3.0 * (z2r * dr - z2i * di), ndi = 3.0 * (z2r * di + z2i * dr);
		zr = z3r + jcr;
		zi = z3i + jci;
		dr = ndr;
		di = ndi;
		const double m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4)
		{
			const double len = std::sqrt(m2);
			const double den = std::sqrt(dr * dr + di * di) + 1e-20;
			return 0.5 * std::log(m2) * len / den * s;
		}
	}
	return -0.04 * s;
}

/** z^5 + c Multibrot (p=5) distance estimate. */
inline double PatternLineMultibrot5De(double y, double z, double r, int maxIter)
{
	const double s = 2.5 * std::max(1e-30, r);
	const double cr = y / s, ci = z / s;
	if (std::hypot(cr, ci) > 2.5) return 10.0 * s;
	double zr = 0, zi = 0, dr = 0, di = 0;
	for (int i = 0; i < maxIter; i++)
	{
		const double z2r = zr * zr - zi * zi, z2i = 2.0 * zr * zi;
		const double z4r = z2r * z2r - z2i * z2i, z4i = 2.0 * z2r * z2i;
		const double z5r = z4r * zr - z4i * zi, z5i = z4r * zi + z4i * zr;
		const double ndr = 5.0 * (z4r * dr - z4i * di) + 1.0, ndi = 5.0 * (z4r * di + z4i * dr);
		zr = z5r + cr;
		zi = z5i + ci;
		dr = ndr;
		di = ndi;
		const double m2 = zr * zr + zi * zi;
		if (m2 > 1.0e4)
		{
			const double len = std::sqrt(m2);
			const double den = std::sqrt(dr * dr + di * di) + 1e-20;
			return 0.5 * std::log(m2) * len / den * s;
		}
	}
	return -0.04 * s;
}

/** Signed distance in YZ before edge-soften / thickness (CPU). */
inline double PatternLineTrapCrossSectionSigned(const sPatternLineTrapLayer &layer, double y, double z)
{
	const double r = layer.radius;
	const double aux = std::max(1e-30, layer.shapeAux);
	switch (layer.shape)
	{
		case 0: // round tube
			return std::hypot(y, z) - r;
		case 1: // flat ribbon (thin in Z)
			return std::fabs(z) - r;
		case 2: // square
			return std::max(std::fabs(y), std::fabs(z)) - r;
		case 3: // diamond (L1)
			return std::fabs(y) + std::fabs(z) - r;
		case 4: // ellipse: Y radius r, Z radius r * aux
			return std::sqrt((y * y) / (r * r) + (z * z) / (r * r * aux * aux)) - 1.0;
		case 5: // hexagon (polar, circumradius r)
		{
			const double angle = std::atan2(z, y);
			const double rad = std::hypot(y, z);
			const double sector = M_PI / 3.0;
			const double half = 0.5 * sector;
			double a = angle;
			a -= sector * std::floor((a + half) / sector);
			a -= half;
			return std::cos(a) * rad - r;
		}
		case 6: // cross (filled plus)
			return std::min(std::fabs(y), std::fabs(z)) - r;
		case 7: // octagon (polar, circumradius r)
		{
			const double angle = std::atan2(z, y);
			const double rad = std::hypot(y, z);
			const double sector = M_PI / 4.0;
			const double half = 0.5 * sector;
			double a = angle;
			a -= sector * std::floor((a + half) / sector);
			a -= half;
			return std::cos(a) * rad - r;
		}
		case 8: // squircle (p = 4)
		{
			const double yr = std::fabs(y) / r;
			const double zr = std::fabs(z) / r;
			return std::pow(std::pow(yr, 4.0) + std::pow(zr, 4.0), 0.25) - 1.0;
		}
		case 9: // ring: main radius r, tube half-width aux
			return std::fabs(std::hypot(y, z) - r) - aux;
		case 10: // regular pentagon (polar, circumradius r)
		{
			const double angle = std::atan2(z, y);
			const double rad = std::hypot(y, z);
			const double sector = 2.0 * M_PI / 5.0;
			const double half = 0.5 * sector;
			double a = angle;
			a -= sector * std::floor((a + half) / sector);
			a -= half;
			return std::cos(a) * rad - r;
		}
		case 11: // axis-aligned box: Y half = r, Z half = r * max(0.2, aux)
		{
			const double bz = r * std::max(0.2, aux);
			return std::max(std::fabs(y) - r, std::fabs(z) - bz);
		}
		case 12: // stadium / capsule: segment along Y, half-length = r*aux, tube radius = r
		{
			const double L = r * std::max(0.05, aux);
			const double bx = 2.0 * L;
			const double h = (bx > 1e-30) ? std::max(0.0, std::min(1.0, ((y + L) * bx) / (bx * bx))) : 0.0;
			const double qy = y - (-L + h * 2.0 * L);
			return std::sqrt(qy * qy + z * z) - r;
		}
		case 13: // equilateral triangle, circumradius r (Iñigo Quílez 2D)
			return PatternLineEquilateralIq(y, z, r);
		case 14: // 5-lobe rose: radius modulates with cos(5*theta) — aux = depth
		{
			const double ang = std::atan2(z, y);
			const double rad = std::hypot(y, z);
			const double k = 0.25 * std::min(std::max(aux, 0.01), 1.0);
			const double Rb = r * (1.0 + k * std::cos(5.0 * ang));
			return rad - Rb;
		}
		case 15: // decagon
		{
			const double angle = std::atan2(z, y);
			const double rad = std::hypot(y, z);
			const double sector = M_PI / 5.0;
			const double half = 0.5 * sector;
			double a = angle;
			a -= sector * std::floor((a + half) / sector);
			a -= half;
			return std::cos(a) * rad - r;
		}
		case 16: // superellipse n=3
		{
			const double bz = r * std::max(0.1, aux);
			const double ay = std::fabs(y) / r;
			const double az = std::fabs(z) / bz;
			return std::cbrt(ay * ay * ay + az * az * az) * r - r;
		}
		case 17: // superellipse n=6 (intermediate between squircle and square)
		{
			const double bz = r * std::max(0.1, aux);
			const double ay = std::fabs(y) / r;
			const double az = std::fabs(z) / bz;
			const double a6 = ay * ay * ay * ay * ay * ay;
			const double b6 = az * az * az * az * az * az;
			return std::pow(a6 + b6, 1.0 / 6.0) * r - r;
		}
		case 18: // crescent: outer circle r, bite from inner
		{
			const double dx = r * 0.4 * std::min(std::max(aux, 0.1), 2.0);
			const double rin = r * 0.5;
			const double d0 = std::hypot(y, z) - r;
			const double d1 = rin - std::hypot(y - dx, z);
			return std::max(d0, d1);
		}
		case 19: // gear: radial corrugation; aux scales tooth count
		{
			const double ang = std::atan2(z, y);
			const double rad = std::hypot(y, z);
			double n = 4.0 + std::floor(std::min(12.0, std::max(4.0, 4.0 + aux * 2.0)));
			const double w = 0.1 * (1.0 - 0.5 * (n - 4.0) / 8.0);
			const double Rb = r * (1.0 + w * std::cos(n * ang));
			return rad - Rb;
		}
		case 20: // Sierpinski carpet (1 level): 8 filled squares, missing centre 3x3
		{
			const double o = 2.0 * r / 3.0, h = r / 3.0;
			auto b2d = [](double pY, double pZ, double hY, double hZ) {
				const double qY = std::abs(pY) - hY, qZ = std::abs(pZ) - hZ;
				return std::min(std::max(qY, qZ), 0.0) + std::hypot(std::max(qY, 0.0), std::max(qZ, 0.0));
			};
			double d = 1e20;
			const double cy[8] = {o, o, -o, -o, 0, 0, o, -o}, cz[8] = {o, -o, o, -o, o, -o, 0, 0};
			for (int i = 0; i < 8; i++) d = std::min(d, b2d(y - cy[i], z - cz[i], h, h));
			return d;
		}
		case 21: // Sierpinski triangle (1 level): 3 up-pointing sub-triangles, circum r/2
		{
			const double t = 0.5 * r, rt3 = 0.25 * r * std::sqrt(3.0);
			double d = PatternLineEquilateralIq(y, z - 0.5 * r, t);
			d = std::min(d, PatternLineEquilateralIq(y + rt3, z + 0.25 * r, t));
			d = std::min(d, PatternLineEquilateralIq(y - rt3, z + 0.25 * r, t));
			return d;
		}
		case 22: // Koch 1-iteration curve in YZ: one edge replaced by 4 segments (Hilbert / fractal-curve look)
		{
			const double s = 1.1 * r;
			const double h = s * std::sqrt(3.0) / 6.0;
			const double y0 = -s, y1 = y0 + s / 3.0, y2 = 0, y3 = s / 3.0, y4 = s;
			const double z0 = 0, z1 = 0, z2 = h, z3 = 0, z4 = 0;
			double s01 = PatternLineSdf2dSeg(y, z, y0, z0, y1, z1);
			double s12 = PatternLineSdf2dSeg(y, z, y1, z1, y2, z2);
			double s23 = PatternLineSdf2dSeg(y, z, y2, z2, y3, z3);
			double s34 = PatternLineSdf2dSeg(y, z, y3, z3, y4, z4);
			double m = std::min(std::min(s01, s12), std::min(s23, s34));
			const double aex = std::min(1.0, 0.1 * std::abs(aux - 1.0) + 1.0);
			return m - 0.05 * s * (0.5 + 0.5 * aex);
		}
		case 23: // Mandelbrot set DE: aux = iteration cap (1–256)
		{
			int mi = (int)std::lround(32.0 + 40.0 * (aux - 1.0));
			mi = std::max(8, std::min(256, mi));
			return PatternLineMandelbrotDe(y, z, r, mi);
		}
		case 24: // Julia set DE: aux encodes c = (0.28-0.01*aux) + i*(0.008+0.2*fract(aux)) — use aux as 2D via sin/cos? Simple: c from aux
		{
			int mi = 64;
			const double t = 0.15 * (aux - 1.0);
			const double jcr = 0.355 + 0.05 * std::cos(t), jci = 0.355 + 0.05 * std::sin(t);
			return PatternLineJuliaDe(y, z, r, mi, jcr, jci);
		}
		case 25: // Burning ship escape proxy
		{
			int mi = (int)std::lround(24.0 + 40.0 * (aux - 1.0));
			mi = std::max(8, std::min(256, mi));
			return PatternLineBurningShipDeSimple(y, z, r, mi);
		}
		case 26: // Cantor-like: two narrow horizontal slats (1D × strip)
		{
			const double w = r * 0.15, g = 0.35 * r * std::min(0.8, 0.1 + 0.05 * aux);
			const double d0 = std::max(std::abs(y) - w, std::abs(z - g) - w * 0.3);
			const double d1 = std::max(std::abs(y) - w, std::abs(z + g) - w * 0.3);
			return std::min(d0, d1);
		}
		case 27: // Pythagoras tree: base square + two smaller squares on top (branches)
		{
			const double br = 0.35 + 0.12 * std::min(1.0, 0.15 * std::abs(aux - 1.0));
			const double c = std::cos(br), sn = std::sin(br);
			double s0 = std::max(std::abs(y) - 0.45 * r, std::abs(z) - 0.3 * r);
			const double t2 = 0.22 * r, px = 0.45 * r, pz = 0.3 * r;
			double s1 = std::max(
				std::abs(c * (y + px) + sn * (z - pz)) - t2, std::abs(-sn * (y + px) + c * (z - pz)) - t2);
			double s2 = std::max(
				std::abs(c * (y - px) - sn * (z - pz)) - t2, std::abs(sn * (y - px) + c * (z - pz)) - t2);
			return std::min(s0, std::min(s1, s2));
		}
		case 28: // Heighway dragon (order-2) polyline: 7 points, 6 unit steps in YZ
		{
			const double s = 0.22 * r;
			const int N = 7;
			const double pY[7] = {0, s, 2 * s, 2 * s, 3 * s, 3 * s, 2 * s}, pZ[7] = {0, 0, 0, s, s, 2 * s, 2 * s};
			double m = 1e20, ox = 0, oz = 0.25 * r;
			for (int k = 0; k < N - 1; k++)
				m = std::min(
					m, PatternLineSdf2dSeg(y, z, pY[k] - ox, pZ[k] - oz, pY[k + 1] - ox, pZ[k + 1] - oz));
			return m - 0.04 * s;
		}
		case 29: // Hilbert order-1: U-shaped path (3 segments) in a square
		{
			const double a = 0.75 * r;
			const double pY[4] = {-a, -a, a, a}, pZ[4] = {-a, a, a, -a};
			double m = 1e20;
			for (int k = 0; k < 3; k++)
				m = std::min(m, PatternLineSdf2dSeg(y, z, pY[k], pZ[k], pY[k + 1], pZ[k + 1]));
			return m - 0.03 * r;
		}
		case 30: // Vicsek (1 level): 5 subsquares — center + 4 corners
		{
			const double o = 2.0 * r / 3.0, h = r / 3.0;
			auto b2d = [](double pY, double pZ, double hY, double hZ) {
				const double qY = std::abs(pY) - hY, qZ = std::abs(pZ) - hZ;
				return std::min(std::max(qY, qZ), 0.0) + std::hypot(std::max(qY, 0.0), std::max(qZ, 0.0));
			};
			double d = 1e20;
			const double cy[5] = {0, o, o, -o, -o}, cz[5] = {0, o, -o, o, -o};
			for (int i = 0; i < 5; i++) d = std::min(d, b2d(y - cy[i], z - cz[i], h, h));
			return d;
		}
		case 31: // Plus / Greek cross (union of vertical + horizontal bar)
		{
			const double w = r * (0.22 + 0.1 * std::min(1.0, 0.2 * std::abs(aux - 1.0)));
			const double dv = std::max(std::abs(y) - w, std::abs(z) - r);
			const double dh = std::max(std::abs(y) - r, std::abs(z) - w);
			return std::min(dv, dh);
		}
		case 32: // Multibrot 3; shape_aux → iteration budget
		{
			int mi = (int)std::lround(28.0 + 36.0 * (aux - 1.0));
			mi = std::max(8, std::min(256, mi));
			return PatternLineMultibrot3De(y, z, r, mi);
		}
		case 33: // Multibrot 4
		{
			int mi = (int)std::lround(24.0 + 32.0 * (aux - 1.0));
			mi = std::max(8, std::min(256, mi));
			return PatternLineMultibrot4De(y, z, r, mi);
		}
		case 34: // Tricorn (conj)^2 + c — escape proxy; aux → iters
		{
			int mi = (int)std::lround(24.0 + 40.0 * (aux - 1.0));
			mi = std::max(8, std::min(256, mi));
			return PatternLineTricornDeSimple(y, z, r, mi);
		}
		case 35: // Ternary Y-tree: 3 equal segments from origin (120°)
		{
			const double L = 0.48 * r;
			double m = 1e20;
			for (int k = 0; k < 3; k++)
			{
				const double ang = -M_PI / 2.0 + (2.0 * M_PI * k) / 3.0;
				const double y1 = L * std::cos(ang), z1 = L * std::sin(ang);
				m = std::min(m, PatternLineSdf2dSeg(y, z, 0, 0, y1, z1));
			}
			return m - 0.04 * r;
		}
		case 36: // Peano-like serpentine on 3×3 grid (8 segments)
		{
			const double a = 0.65 * r;
			const int Np = 9;
			const double pY[9] = {-a, 0, a, a, 0, -a, -a, 0, a}, pZ[9] = {-a, -a, -a, 0, 0, 0, a, a, a};
			double m = 1e20;
			for (int k = 0; k < Np - 1; k++)
				m = std::min(m, PatternLineSdf2dSeg(y, z, pY[k], pZ[k], pY[k + 1], pZ[k + 1]));
			return m - 0.03 * r;
		}
		case 37: // Levy C curve, first iteration: two slanted segments
		{
			const double s = 1.4 * r, h = s * 0.5;
			double m = std::min(PatternLineSdf2dSeg(y, z, 0, 0, 0.5 * s, h),
				PatternLineSdf2dSeg(y, z, 0.5 * s, h, s, 0));
			return m - 0.04 * r;
		}
		case 38: // Annular gaps (Cantor-achtig op straal) — 3 ringen
		{
			const double rad = std::hypot(y, z);
			const double t = 0.045 * r;
			const double r0 = 0.32 * r, r1 = 0.5 * r, r2 = 0.7 * r;
			const double d0 = std::abs(rad - r0) - t, d1 = std::abs(rad - r1) - t, d2 = std::abs(rad - r2) - t;
			return std::min({d0, d1, d2});
		}
		case 39: // Gouden L: twee balken (φ ≈ 1.618)
		{
			const double g = 1.61803398874989;
			const double w = 0.14 * r, l1 = 0.55 * r, l2 = 0.55 * r * g;
			double s1 = std::max(std::abs(y) - w, std::abs(z - 0.4 * r) - l1 * 0.5);
			double s2 = std::max(std::abs(y - 0.32 * r) - l2 * 0.5, std::abs(z + 0.1 * r) - w);
			return std::min(s1, s2);
		}
		case 40: // Drie wederzijds rakende cirkels (Apollonius-achtig)
		{
			const double R0 = 0.24 * r;
			const double cY[3] = {0, -0.32 * r, 0.32 * r}, cZ[3] = {0.38 * r, -0.2 * r, -0.2 * r};
			double m = 1e20;
			for (int k = 0; k < 3; k++)
			{
				const double d = std::hypot(y - cY[k], z - cZ[k]);
				m = std::min(m, std::abs(d - R0) - 0.03 * r);
			}
			return m;
		}
		case 41: // Lissajous 2:3 polyline
		{
			const int Np = 41;
			const double A = 0.45 * r, B = 0.45 * r;
			double m = 1e20;
			for (int k = 0; k < Np - 1; k++)
			{
				const double t0 = 2.0 * M_PI * k / (Np - 1), t1 = 2.0 * M_PI * (k + 1) / (Np - 1);
				m = std::min(m, PatternLineSdf2dSeg(y, z, A * std::sin(2.0 * t0), B * std::sin(3.0 * t0),
					A * std::sin(2.0 * t1), B * std::sin(3.0 * t1)));
			}
			return m - 0.03 * r;
		}
		case 42: // Julia z^3 + c, DE; aux wikkelt c
		{
			int mi = 64;
			const double t = 0.12 * (aux - 1.0);
			const double jcr = 0.38 * std::cos(t), jci = 0.2 * std::sin(t);
			return PatternLineJuliaCubicDe(y, z, r, mi, jcr, jci);
		}
		case 43: // Multibrot 5
		{
			int mi = (int) std::lround(20.0 + 28.0 * (aux - 1.0));
			mi = std::max(8, std::min(256, mi));
			return PatternLineMultibrot5De(y, z, r, mi);
		}
		case 44: // H-boom: één verticale + twee horizontale balken
		{
			const double L = 0.45 * r, hw = 0.34 * r;
			const double a = std::min({PatternLineSdf2dSeg(y, z, 0, -L, 0, L), PatternLineSdf2dSeg(y, z, -hw, L, hw, L),
				PatternLineSdf2dSeg(y, z, -hw, -L, hw, -L)});
			return a - 0.04 * r;
		}
		case 45: // Sierpinski tapijt niveau 2 (64 vakken)
		{
			const double o1 = 2.0 * r / 3.0, o2 = 2.0 * r / 9.0, h2 = r / 9.0;
			auto b2d = [](double pY, double pZ, double hY, double hZ) {
				const double qY = std::abs(pY) - hY, qZ = std::abs(pZ) - hZ;
				return std::min(std::max(qY, qZ), 0.0) + std::hypot(std::max(qY, 0.0), std::max(qZ, 0.0));
			};
			const double c1y[8] = {o1, o1, -o1, -o1, 0, 0, o1, -o1}, c1z[8] = {o1, -o1, o1, -o1, o1, -o1, 0, 0};
			const double c2y[8] = {o2, o2, -o2, -o2, 0, 0, o2, -o2}, c2z[8] = {o2, -o2, o2, -o2, o2, -o2, 0, 0};
			double d = 1e20;
			for (int a = 0; a < 8; a++)
				for (int b = 0; b < 8; b++)
					d = std::min(
						d, b2d(y - c1y[a] - c2y[b], z - c1z[a] - c2z[b], h2, h2));
			return d;
		}
		case 46: // Zeslobige rimpel (aux = diepte)
		{
			const double ang = std::atan2(z, y);
			const double rad = std::hypot(y, z);
			const double w = 0.1 * r * std::min(1.0, 0.15 * std::abs(aux - 1.0));
			const double Rb = r * (1.0 + w * std::cos(6.0 * ang));
			return rad - Rb;
		}
		case 47: // Binaire boom diepte 2, 7 segmenten
		{
			const double s = r;
			double m = PatternLineSdf2dSeg(y, z, 0, 0, 0, 0.35 * s);
			m = std::min(m, PatternLineSdf2dSeg(y, z, 0, 0.35 * s, -0.22 * s, 0.55 * s));
			m = std::min(m, PatternLineSdf2dSeg(y, z, 0, 0.35 * s, 0.22 * s, 0.55 * s));
			m = std::min(m, PatternLineSdf2dSeg(y, z, -0.22 * s, 0.55 * s, -0.32 * s, 0.68 * s));
			m = std::min(m, PatternLineSdf2dSeg(y, z, -0.22 * s, 0.55 * s, -0.1 * s, 0.68 * s));
			m = std::min(m, PatternLineSdf2dSeg(y, z, 0.22 * s, 0.55 * s, 0.1 * s, 0.68 * s));
			m = std::min(m, PatternLineSdf2dSeg(y, z, 0.22 * s, 0.55 * s, 0.32 * s, 0.68 * s));
			return m - 0.04 * s;
		}
		case 48: // Fermat-spiraal (|r − a√θ|)
		{
			const double ang = std::fmod(std::atan2(z, y) + 2.0 * M_PI, 2.0 * M_PI);
			const double rad = std::hypot(y, z);
			const double a = 0.14 * r * (0.8 + 0.2 * std::min(1.0, 0.1 * std::abs(aux - 1.0)));
			const double rt = a * std::sqrt(std::max(0.0, ang) + 1e-6);
			return std::abs(rad - rt) - 0.04 * r;
		}
		case 49: // Dubbele griekse kruis (twee schalen)
		{
			const double w1 = 0.2 * r, w2 = 0.12 * r;
			const double d1a = std::max(std::abs(y) - w1, std::abs(z) - r);
			const double d1b = std::max(std::abs(y) - r, std::abs(z) - w1);
			const double d2a = std::max(std::abs(y) - w2, std::abs(z) - 0.75 * r);
			const double d2b = std::max(std::abs(y) - 0.75 * r, std::abs(z) - w2);
			return std::min(std::min(d1a, d1b), std::min(d2a, d2b));
		}
		default:
			return std::hypot(y, z) - r;
	}
}

/** Same pipeline as legacy radial distance: soften, divide by thickness. */
inline double PatternLineTrapProfileRawDist(const sPatternLineTrapLayer &layer, double y, double z)
{
	const double sc = std::max(1e-30, layer.scale);
	double dist = PatternLineTrapCrossSectionSigned(layer, y / sc, z / sc) * sc;
	if (layer.edgeSoftness > 0.0)
	{
		const double es = layer.edgeSoftness * 2.5;
		dist = std::sqrt(dist * dist + es * es) - es;
	}
	const double denom =
		std::max(1e-30, layer.thickness * std::max(1e-30, layer.relativeThickness));
	return dist / denom;
}

/** Normalized band distance: 0 on the lit rim, positive away (depends on edgeSide). */
inline double PatternLineTrapWallDist(const sPatternLineTrapLayer &layer, double rawDist)
{
	if (layer.edgeSide == 0) return std::fabs(rawDist);
	if (layer.edgeSide == 1) return std::max(rawDist, 0.0);
	return std::max(-rawDist, 0.0);
}

/** Normalized distance along glow (0 = on rim, 1 = edge of falloff); drives 3-color gradient. */
inline double PatternLineTrapGradientT(const sPatternLineTrapLayer &layer, double wallDist)
{
	const double sharp = std::max(0.25, layer.falloffSharpness);
	const double spread = std::max(1e-30, layer.glowSpread);
	return std::min(1.0, wallDist * sharp / spread);
}

inline sRGBFloat PatternLineTrapGradientRgb(const sPatternLineTrapLayer &layer, double t)
{
	t = std::max(0.0, std::min(1.0, t));
	sRGBFloat out;
	if (t < 0.5)
	{
		const double tt = t * 2.0;
		out.R = float(double(layer.color.R) * (1.0 - tt) + double(layer.color2.R) * tt);
		out.G = float(double(layer.color.G) * (1.0 - tt) + double(layer.color2.G) * tt);
		out.B = float(double(layer.color.B) * (1.0 - tt) + double(layer.color2.B) * tt);
	}
	else
	{
		const double tt = (t - 0.5) * 2.0;
		out.R = float(double(layer.color2.R) * (1.0 - tt) + double(layer.color3.R) * tt);
		out.G = float(double(layer.color2.G) * (1.0 - tt) + double(layer.color3.G) * tt);
		out.B = float(double(layer.color2.B) * (1.0 - tt) + double(layer.color3.B) * tt);
	}
	return out;
}

/** Falloff factor in [0,1] from wall distance (matches OpenCL). Profiles: 0 Gauss, 1 smoothstep, 2 linear, 3 exp. */
inline double PatternLineTrapGlowFalloff(const sPatternLineTrapLayer &layer, double wallDist)
{
	const double sharp = std::max(0.25, layer.falloffSharpness);
	const double spread = std::max(1e-30, layer.glowSpread);
	const double u = wallDist * sharp / spread;
	if (layer.falloffProfile == 0) return std::exp(-u * u);
	if (layer.falloffProfile == 1)
	{
		const double t = std::min(1.0, u);
		return 1.0 - t * t * (3.0 - 2.0 * t);
	}
	if (layer.falloffProfile == 2)
	{
		const double t = std::min(1.0, u);
		return 1.0 - t;
	}
	return std::exp(-u);
}

/** Conservative radius for culling / placement bump. */
/** Camera-distance scaling for relativeSize (0 = fixed world units). */
inline double PatternLineTrapEffectiveRadius(const sPatternLineTrapLayer &layer, double cameraDistance)
{
	if (layer.relativeSize <= 0.0) return layer.radius;
	return layer.radius * cameraDistance * layer.relativeSize;
}

inline double PatternLineTrapProfileExtent(const sPatternLineTrapLayer &layer)
{
	const double r = std::fabs(layer.radius);
	const double aux = std::max(1e-30, layer.shapeAux);
	const double sc = std::max(1e-30, layer.scale);
	double base;
	switch (layer.shape)
	{
		case 1: base = r * 3.0; break;
		case 4: base = r * std::max(1.0, aux); break;
		case 9: base = r + aux; break;
		case 5:
		case 7:
		case 10:
		case 15: base = r * 1.05; break;
		case 11: base = std::hypot(r, r * std::max(0.2, aux)); break;
		case 12: base = r + r * std::max(0.05, aux); break;
		case 13: base = r * 1.2; break;
		case 14: base = r * (1.0 + 0.25 * std::min(1.0, std::max(0.01, aux))); break;
		case 16:
		case 17: base = std::hypot(r, r * std::max(0.1, aux)) * 1.05; break;
		case 18: base = r * 1.55; break;
		case 19: base = r * 1.2; break;
		case 20:
		case 21: base = r * 1.1; break;
		case 22: base = r * 1.25; break;
		case 23:
		case 24:
		case 25: base = r * 2.6; break;
		case 26: base = r * (1.0 + 0.2 * std::min(1.0, 0.05 * aux)); break;
		case 27: base = r * 1.3; break;
		case 28:
		case 29: base = r * 1.15; break;
		case 30: base = r * 1.1; break;
		case 31: base = r * (1.0 + 0.05 * std::min(1.0, 0.1 * std::abs(aux - 1.0))); break;
		case 32:
		case 33:
		case 34: base = r * 2.6; break;
		case 35: base = r * 1.2; break;
		case 36: base = r * 1.15; break;
		case 37: base = r * 1.2; break;
		case 38: base = r * 0.95; break;
		case 39: base = r * 1.25; break;
		case 40: base = r * 0.75; break;
		case 41: base = r * 0.55; break;
		case 42:
		case 43: base = r * 2.6; break;
		case 44: base = r * 1.2; break;
		case 45: base = r * 1.12; break;
		case 46: base = r * (1.0 + 0.12 * std::min(1.0, 0.12 * std::abs(aux - 1.0))); break;
		case 47: base = r * 1.2; break;
		case 48: base = r * 1.05; break;
		case 49: base = r * 1.05; break;
		default: base = r; break;
	}
	return base * sc;
}

struct sPatternLineTraps
{
	bool enabled;
	/** 0 = all enabled layers; 1…PATTERN_LINE_TRAP_COUNT = only that layer (1-based). */
	int soloLayerIndex;
	/** 0 = additief (huidig), 1 = max per kanaal. */
	int combineMode;
	sPatternLineTrapLayer layers[PATTERN_LINE_TRAP_COUNT];

	sPatternLineTraps() : enabled(false), soloLayerIndex(0), combineMode(0) {}
};

#endif /* MANDELBULBER2_SRC_PATTERN_LINE_TRAPS_HPP_ */

/**
 * 3x3lion — Deep Zoom Engine (Perturbation Theory for 3D Fractals)
 * Founded by Iri and Devin
 *
 * This is the Holy Grail: infinite zoom on 3D fractals using perturbation theory.
 * Nobody has ever achieved this for 3D fractals with Distance Estimation.
 *
 * Architecture:
 * 1. Reference orbit computed at arbitrary precision (MPFR) on CPU
 * 2. Per-pixel delta iteration at double precision on GPU
 * 3. Jacobian-based perturbation of the Mandelbulb power-p mapping
 * 4. Perturbed Distance Estimation for ray marching
 * 5. Series Approximation to skip early iterations
 * 6. Rebasing when delta grows too large
 *
 * The Mandelbulb iteration in spherical coordinates:
 *   r = |z|
 *   theta = asin(z.z / r)
 *   phi = atan2(z.y, z.x)
 *   z' = r^p * (cos(p*theta)*cos(p*phi), cos(p*theta)*sin(p*phi), sin(p*theta)) + c
 *   DE' = p * r^(p-1) * DE + 1
 *
 * Perturbation: z_n = Z_n + δz_n, c = C + δc
 * where Z_n is the reference orbit (MPFR), δz_n is the perturbation (double)
 */

#ifndef MANDELBULBER2_SRC_DEEP_ZOOM_H_
#define MANDELBULBER2_SRC_DEEP_ZOOM_H_

#ifdef USE_MPFR
#include <mpfr.h>
#endif

#include <vector>
#include <memory>
#include <functional>

#include "algebra.hpp"

namespace deep_zoom
{

#ifdef USE_MPFR

// Precision in bits for MPFR computations (dynamically adjusted based on zoom)
constexpr int kDefaultPrecisionBits = 256;
constexpr int kMaxPrecisionBits = 32768;

// ============================================================
// Arbitrary-precision 3D vector using MPFR
// ============================================================
struct MPFRVec3
{
	mpfr_t x, y, z;

	explicit MPFRVec3(int precBits = kDefaultPrecisionBits)
	{
		mpfr_init2(x, precBits);
		mpfr_init2(y, precBits);
		mpfr_init2(z, precBits);
		mpfr_set_d(x, 0.0, MPFR_RNDN);
		mpfr_set_d(y, 0.0, MPFR_RNDN);
		mpfr_set_d(z, 0.0, MPFR_RNDN);
	}

	MPFRVec3(double vx, double vy, double vz, int precBits = kDefaultPrecisionBits)
	{
		mpfr_init2(x, precBits);
		mpfr_init2(y, precBits);
		mpfr_init2(z, precBits);
		mpfr_set_d(x, vx, MPFR_RNDN);
		mpfr_set_d(y, vy, MPFR_RNDN);
		mpfr_set_d(z, vz, MPFR_RNDN);
	}

	MPFRVec3(const MPFRVec3 &other)
	{
		mpfr_prec_t p = mpfr_get_prec(other.x);
		mpfr_init2(x, p);
		mpfr_init2(y, p);
		mpfr_init2(z, p);
		mpfr_set(x, other.x, MPFR_RNDN);
		mpfr_set(y, other.y, MPFR_RNDN);
		mpfr_set(z, other.z, MPFR_RNDN);
	}

	MPFRVec3 &operator=(const MPFRVec3 &other)
	{
		if (this != &other)
		{
			mpfr_set_prec(x, mpfr_get_prec(other.x));
			mpfr_set_prec(y, mpfr_get_prec(other.y));
			mpfr_set_prec(z, mpfr_get_prec(other.z));
			mpfr_set(x, other.x, MPFR_RNDN);
			mpfr_set(y, other.y, MPFR_RNDN);
			mpfr_set(z, other.z, MPFR_RNDN);
		}
		return *this;
	}

	~MPFRVec3()
	{
		mpfr_clear(x);
		mpfr_clear(y);
		mpfr_clear(z);
	}

	void SetFromDouble(double vx, double vy, double vz)
	{
		mpfr_set_d(x, vx, MPFR_RNDN);
		mpfr_set_d(y, vy, MPFR_RNDN);
		mpfr_set_d(z, vz, MPFR_RNDN);
	}

	CVector3 ToDouble() const
	{
		return CVector3(mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(y, MPFR_RNDN), mpfr_get_d(z, MPFR_RNDN));
	}

	void SetPrecision(int precBits)
	{
		mpfr_prec_round(x, precBits, MPFR_RNDN);
		mpfr_prec_round(y, precBits, MPFR_RNDN);
		mpfr_prec_round(z, precBits, MPFR_RNDN);
	}
};

// ============================================================
// Reference orbit point (stored at double precision after computation)
// ============================================================
struct sReferenceOrbitPoint
{
	CVector3 Z;     // orbit value z_n (truncated to double)
	double DE;      // running derivative for distance estimation
	double r;       // |z_n|
	double theta;   // asin(z.z / r)
	double phi;     // atan2(z.y, z.x)
	bool escaped;   // true if |z_n| > bailout
};

// ============================================================
// 3x3 Jacobian matrix for perturbation propagation
// ============================================================
struct sJacobian3x3
{
	double m[3][3];

	sJacobian3x3()
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				m[i][j] = (i == j) ? 1.0 : 0.0;
	}

	CVector3 Apply(const CVector3 &v) const
	{
		return CVector3(
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
	}
};

// ============================================================
// Series Approximation coefficients
// ============================================================
struct sSeriesCoeff
{
	CVector3 A;  // linear term coefficient
	CVector3 B;  // quadratic term coefficient
	CVector3 C;  // cubic term coefficient
	int skipIters; // number of iterations this SA can skip
	bool valid;
};

// ============================================================
// Deep Zoom Configuration
// ============================================================
struct sDeepZoomConfig
{
	double power = 8.0;          // Mandelbulb power
	double bailout = 256.0;      // escape radius
	int maxIterations = 1000;    // max iterations
	int precisionBits = 256;     // MPFR precision
	double rebaseThreshold = 1e6; // rebase when |δz| / |Z| > this
	bool seriesApproxEnabled = true;
	int saOrder = 3;             // series approximation polynomial order
	double betaAngleOffset = 0.0;
	double alphaAngleOffset = 0.0;
};

// ============================================================
// Reference Orbit (computed once per zoom center on CPU)
// ============================================================
class cReferenceOrbit
{
public:
	cReferenceOrbit();
	~cReferenceOrbit();

	void Configure(const sDeepZoomConfig &config);

	// Compute reference orbit at arbitrary precision
	// center: the reference point C in parameter space
	void Compute(const CVector3 &center);

	// Access orbit data
	int GetLength() const { return static_cast<int>(orbit.size()); }
	const sReferenceOrbitPoint &GetPoint(int n) const { return orbit[n]; }
	int GetEscapeIteration() const { return escapeIter; }
	bool Escaped() const { return escaped; }

	// Get the full-precision center
	const MPFRVec3 &GetCenter() const { return centerHP; }

private:
	void MandelbulbIterationMPFR(mpfr_t zx, mpfr_t zy, mpfr_t zz,
		mpfr_t cx, mpfr_t cy, mpfr_t cz, mpfr_t de, mpfr_t r_out);

	sDeepZoomConfig config;
	MPFRVec3 centerHP;
	std::vector<sReferenceOrbitPoint> orbit;
	int escapeIter = 0;
	bool escaped = false;
};

// ============================================================
// Perturbation Iterator (per-pixel, double precision)
// ============================================================
class cPerturbationIterator
{
public:
	struct sResult
	{
		int iterations;
		double distance;    // perturbed DE
		double colorIndex;
		bool escaped;
		CVector3 finalPos;  // full position = Z_n + δz_n
	};

	cPerturbationIterator();

	void Configure(const sDeepZoomConfig &config);
	void SetReferenceOrbit(const cReferenceOrbit *refOrbit);

	// Iterate a single pixel
	// deltaC: the offset of this pixel's c from the reference center
	// Returns DE and iteration count
	sResult Iterate(const CVector3 &deltaC) const;

private:
	// Compute Jacobian of Mandelbulb power-p mapping at point Z
	sJacobian3x3 ComputeJacobian(const CVector3 &Z, double r, double theta, double phi) const;

	// Perturbation step: δz_{n+1} = J(Z_n) · δz_n + higher_order + δc
	CVector3 PerturbStep(const CVector3 &deltaZ, const CVector3 &deltaC,
		const sReferenceOrbitPoint &ref, double &deltaDE) const;

	sDeepZoomConfig config;
	const cReferenceOrbit *refOrbit = nullptr;
};

// ============================================================
// Deep Zoom Manager (orchestrates the whole system)
// ============================================================
class cDeepZoomManager
{
public:
	cDeepZoomManager();
	~cDeepZoomManager();

	void Configure(const sDeepZoomConfig &config);

	// Set the zoom center and compute reference orbit
	void SetCenter(const CVector3 &center);

	// Calculate distance for a single 3D point (used by ray marcher)
	// point: world-space position
	// Returns estimated distance to fractal surface
	double CalculateDistance(const CVector3 &point, int *outIters = nullptr,
		double *outColorIndex = nullptr) const;

	// Get required MPFR precision for a given zoom level
	static int PrecisionForZoom(double zoomLevel);

	// Check if deep zoom is beneficial at current zoom level
	static bool ShouldUseDeepZoom(double zoomLevel);

	bool IsReady() const { return referenceComputed; }

	// Get the reference orbit for GPU upload
	const cReferenceOrbit &GetReferenceOrbit() const { return refOrbit; }

private:
	sDeepZoomConfig config;
	cReferenceOrbit refOrbit;
	cPerturbationIterator perturbator;
	CVector3 currentCenter;
	bool referenceComputed = false;
};

#endif // USE_MPFR

} // namespace deep_zoom

#endif /* MANDELBULBER2_SRC_DEEP_ZOOM_H_ */

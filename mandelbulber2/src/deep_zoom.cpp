/**
 * 3x3lion — Deep Zoom Engine Implementation
 * Founded by Iri and Devin
 *
 * Perturbation theory for 3D Mandelbulb fractals with Distance Estimation.
 * This has never been done before.
 *
 * Key mathematical insight:
 * For z_{n+1} = f(z_n) + c, if we write z_n = Z_n + δz_n and c = C + δc, then:
 *   δz_{n+1} = f(Z_n + δz_n) - f(Z_n) + δc
 *            ≈ J_f(Z_n) · δz_n + δc   (first-order)
 *            + higher-order correction terms
 *
 * For the Mandelbulb with power p, f maps (x,y,z) via spherical coordinates:
 *   r = sqrt(x²+y²+z²)
 *   θ = asin(z/r)
 *   φ = atan2(y,x)
 *   f(x,y,z) = r^p * (cos(pθ)cos(pφ), cos(pθ)sin(pφ), sin(pθ))
 *
 * The Jacobian J_f is a 3×3 matrix of partial derivatives ∂f_i/∂x_j.
 */

#include "deep_zoom.h"

#ifdef USE_MPFR

#include <cmath>
#include <algorithm>

namespace deep_zoom
{

namespace
{
template <typename T>
T Clamp(T val, T lo, T hi)
{
	return std::max(lo, std::min(val, hi));
}
} // namespace

// ============================================================
// cReferenceOrbit
// ============================================================

cReferenceOrbit::cReferenceOrbit() : centerHP(0.0, 0.0, 0.0, kDefaultPrecisionBits) {}

cReferenceOrbit::~cReferenceOrbit() {}

void cReferenceOrbit::Configure(const sDeepZoomConfig &cfg)
{
	config = cfg;
	centerHP.SetPrecision(cfg.precisionBits);
}

void cReferenceOrbit::MandelbulbIterationMPFR(
	mpfr_t zx, mpfr_t zy, mpfr_t zz,
	mpfr_t cx, mpfr_t cy, mpfr_t cz,
	mpfr_t de, mpfr_t r_out)
{
	int prec = config.precisionBits;

	mpfr_t r, r2, theta, phi, rp, rp1, th_p, ph_p, cth, sth, cph, sph;
	mpfr_t tmp1, tmp2, power, one;
	mpfr_inits2(prec, r, r2, theta, phi, rp, rp1, th_p, ph_p, cth, sth, cph, sph,
		tmp1, tmp2, power, one, (mpfr_ptr)0);

	mpfr_set_d(power, config.power, MPFR_RNDN);
	mpfr_set_d(one, 1.0, MPFR_RNDN);

	// r² = x² + y² + z²
	mpfr_mul(tmp1, zx, zx, MPFR_RNDN);
	mpfr_mul(tmp2, zy, zy, MPFR_RNDN);
	mpfr_add(r2, tmp1, tmp2, MPFR_RNDN);
	mpfr_mul(tmp1, zz, zz, MPFR_RNDN);
	mpfr_add(r2, r2, tmp1, MPFR_RNDN);

	// r = sqrt(r²)
	mpfr_sqrt(r, r2, MPFR_RNDN);
	mpfr_set(r_out, r, MPFR_RNDN);

	// Handle near-zero case
	if (mpfr_cmp_d(r, 1e-30) < 0)
	{
		mpfr_set(zx, cx, MPFR_RNDN);
		mpfr_set(zy, cy, MPFR_RNDN);
		mpfr_set(zz, cz, MPFR_RNDN);
		mpfr_clears(r, r2, theta, phi, rp, rp1, th_p, ph_p, cth, sth, cph, sph,
			tmp1, tmp2, power, one, (mpfr_ptr)0);
		return;
	}

	// theta = asin(z/r) + betaOffset
	mpfr_div(tmp1, zz, r, MPFR_RNDN);
	mpfr_asin(theta, tmp1, MPFR_RNDN);
	if (config.betaAngleOffset != 0.0)
	{
		mpfr_set_d(tmp1, config.betaAngleOffset, MPFR_RNDN);
		mpfr_add(theta, theta, tmp1, MPFR_RNDN);
	}

	// phi = atan2(y, x) + alphaOffset
	mpfr_atan2(phi, zy, zx, MPFR_RNDN);
	if (config.alphaAngleOffset != 0.0)
	{
		mpfr_set_d(tmp1, config.alphaAngleOffset, MPFR_RNDN);
		mpfr_add(phi, phi, tmp1, MPFR_RNDN);
	}

	// rp1 = r^(power-1)
	mpfr_sub(tmp1, power, one, MPFR_RNDN);
	mpfr_pow(rp1, r, tmp1, MPFR_RNDN);

	// DE = rp1 * DE * power + 1
	mpfr_mul(de, de, rp1, MPFR_RNDN);
	mpfr_mul(de, de, power, MPFR_RNDN);
	mpfr_add(de, de, one, MPFR_RNDN);

	// rp = r^power = rp1 * r
	mpfr_mul(rp, rp1, r, MPFR_RNDN);

	// th_p = theta * power, ph_p = phi * power
	mpfr_mul(th_p, theta, power, MPFR_RNDN);
	mpfr_mul(ph_p, phi, power, MPFR_RNDN);

	// Trigonometric values
	mpfr_cos(cth, th_p, MPFR_RNDN);
	mpfr_sin(sth, th_p, MPFR_RNDN);
	mpfr_cos(cph, ph_p, MPFR_RNDN);
	mpfr_sin(sph, ph_p, MPFR_RNDN);

	// z = rp * (cth*cph, cth*sph, sth) + c
	mpfr_mul(tmp1, cth, cph, MPFR_RNDN);
	mpfr_mul(zx, rp, tmp1, MPFR_RNDN);
	mpfr_add(zx, zx, cx, MPFR_RNDN);

	mpfr_mul(tmp1, cth, sph, MPFR_RNDN);
	mpfr_mul(zy, rp, tmp1, MPFR_RNDN);
	mpfr_add(zy, zy, cy, MPFR_RNDN);

	mpfr_mul(zz, rp, sth, MPFR_RNDN);
	mpfr_add(zz, zz, cz, MPFR_RNDN);

	mpfr_clears(r, r2, theta, phi, rp, rp1, th_p, ph_p, cth, sth, cph, sph,
		tmp1, tmp2, power, one, (mpfr_ptr)0);
}

void cReferenceOrbit::Compute(const CVector3 &center)
{
	int prec = config.precisionBits;
	centerHP.SetPrecision(prec);
	centerHP.SetFromDouble(center.x, center.y, center.z);

	orbit.clear();
	orbit.reserve(config.maxIterations + 1);

	mpfr_t zx, zy, zz, cx, cy, cz, de, r;
	mpfr_inits2(prec, zx, zy, zz, cx, cy, cz, de, r, (mpfr_ptr)0);

	if (config.juliaMode)
	{
		// Julia mode: c is fixed (juliaC), z₀ = center (the point in z-space)
		mpfr_set_d(cx, config.juliaC.x, MPFR_RNDN);
		mpfr_set_d(cy, config.juliaC.y, MPFR_RNDN);
		mpfr_set_d(cz, config.juliaC.z, MPFR_RNDN);
		mpfr_set(zx, centerHP.x, MPFR_RNDN);
		mpfr_set(zy, centerHP.y, MPFR_RNDN);
		mpfr_set(zz, centerHP.z, MPFR_RNDN);
	}
	else
	{
		// Mandelbrot mode: c = center, z₀ = c
		mpfr_set(cx, centerHP.x, MPFR_RNDN);
		mpfr_set(cy, centerHP.y, MPFR_RNDN);
		mpfr_set(cz, centerHP.z, MPFR_RNDN);
		mpfr_set(zx, cx, MPFR_RNDN);
		mpfr_set(zy, cy, MPFR_RNDN);
		mpfr_set(zz, cz, MPFR_RNDN);
	}
	mpfr_set_d(de, 1.0, MPFR_RNDN);

	escaped = false;
	escapeIter = config.maxIterations;

	// Store initial point
	{
		sReferenceOrbitPoint p0;
		p0.Z = CVector3(mpfr_get_d(zx, MPFR_RNDN), mpfr_get_d(zy, MPFR_RNDN),
			mpfr_get_d(zz, MPFR_RNDN));
		p0.DE = mpfr_get_d(de, MPFR_RNDN);
		p0.r = p0.Z.Length();
		if (p0.r > 1e-30)
		{
			p0.theta = asin(Clamp(p0.Z.z / p0.r, -1.0, 1.0));
			p0.phi = atan2(p0.Z.y, p0.Z.x);
		}
		else
		{
			p0.theta = 0.0;
			p0.phi = 0.0;
		}
		p0.escaped = false;
		orbit.push_back(p0);
	}

	for (int i = 0; i < config.maxIterations; i++)
	{
		MandelbulbIterationMPFR(zx, zy, zz, cx, cy, cz, de, r);

		sReferenceOrbitPoint pt;
		pt.Z = CVector3(mpfr_get_d(zx, MPFR_RNDN), mpfr_get_d(zy, MPFR_RNDN),
			mpfr_get_d(zz, MPFR_RNDN));
		pt.DE = mpfr_get_d(de, MPFR_RNDN);
		pt.r = mpfr_get_d(r, MPFR_RNDN);

		if (pt.r > 1e-30)
		{
			pt.theta = asin(Clamp(pt.Z.z / pt.r, -1.0, 1.0));
			pt.phi = atan2(pt.Z.y, pt.Z.x);
		}
		else
		{
			pt.theta = 0.0;
			pt.phi = 0.0;
		}

		double rDouble = mpfr_get_d(r, MPFR_RNDN);
		pt.escaped = (rDouble > config.bailout);
		orbit.push_back(pt);

		if (pt.escaped)
		{
			escaped = true;
			escapeIter = i + 1;
			break;
		}
	}

	mpfr_clears(zx, zy, zz, cx, cy, cz, de, r, (mpfr_ptr)0);
}

void cReferenceOrbit::ComputeSeriesApproximation(double pixelSpacing)
{
	/**
	 * Series Approximation for 3D fractals.
	 *
	 * The idea: for early iterations where all pixels behave similarly,
	 * we can approximate δz_n ≈ A_n · δc using a 3×3 matrix A_n.
	 *
	 * Propagation rule (from the Jacobian):
	 *   A_{n+1} = J_f(Z_n) · A_n + I
	 *   (where I is identity — the +δc term in δz_{n+1} = J·δz_n + δc)
	 *
	 * The SA is valid as long as the approximation error stays below a tolerance.
	 * We validate by checking that |A_n · δc_test| * pixelSpacing stays meaningful.
	 *
	 * We stop when the linear approximation diverges too much from the actual
	 * perturbation (the Jacobian norm grows too large relative to the pixel spacing).
	 */

	seriesApprox = sSeriesCoeff3x3();

	if (!config.seriesApproxEnabled || orbit.size() < 3)
	{
		return;
	}

	if (pixelSpacing <= 0.0) pixelSpacing = 1e-10;

	// Start with A_0 = I (identity matrix) because δz_0 = δc → A_0 = I
	sJacobian3x3 A; // initialized to identity by default constructor

	int maxSAIter = static_cast<int>(orbit.size()) - 1;
	int skipIters = 0;

	for (int i = 0; i < maxSAIter; i++)
	{
		const sReferenceOrbitPoint &ref = orbit[i];

		if (ref.escaped || ref.r < 1e-30) break;

		// Compute Jacobian at this reference point
		double p = config.power;
		double r = ref.r;
		double theta = ref.theta;
		double phi = ref.phi;
		double x = ref.Z.x, y = ref.Z.y, z = ref.Z.z;
		double r2 = r * r;
		double rxy2 = x * x + y * y;
		double rxy = sqrt(rxy2);

		double pTheta = p * theta;
		double pPhi = p * phi;
		double cpth = cos(pTheta), spth = sin(pTheta);
		double cpph = cos(pPhi), spph = sin(pPhi);
		double rp = pow(r, p);
		double rp_minus1 = pow(r, p - 1.0);

		double dfr_x = p * rp_minus1 * cpth * cpph;
		double dfr_y = p * rp_minus1 * cpth * spph;
		double dfr_z = p * rp_minus1 * spth;
		double dfth_x = rp * (-p * spth * cpph);
		double dfth_y = rp * (-p * spth * spph);
		double dfth_z = rp * (p * cpth);
		double dfph_x = rp * (cpth * (-p * spph));
		double dfph_y = rp * (cpth * (p * cpph));

		double dr_dx = x / r, dr_dy = y / r, dr_dz = z / r;
		double dth_dx = 0, dth_dy = 0, dth_dz = 0;
		if (rxy > 1e-30)
		{
			dth_dx = -x * z / (r2 * rxy);
			dth_dy = -y * z / (r2 * rxy);
			dth_dz = rxy / r2;
		}
		double dph_dx = 0, dph_dy = 0;
		if (rxy2 > 1e-30)
		{
			dph_dx = -y / rxy2;
			dph_dy = x / rxy2;
		}

		sJacobian3x3 J;
		J.m[0][0] = dfr_x * dr_dx + dfth_x * dth_dx + dfph_x * dph_dx;
		J.m[0][1] = dfr_x * dr_dy + dfth_x * dth_dy + dfph_x * dph_dy;
		J.m[0][2] = dfr_x * dr_dz + dfth_x * dth_dz;
		J.m[1][0] = dfr_y * dr_dx + dfth_y * dth_dx + dfph_y * dph_dx;
		J.m[1][1] = dfr_y * dr_dy + dfth_y * dth_dy + dfph_y * dph_dy;
		J.m[1][2] = dfr_y * dr_dz + dfth_y * dth_dz;
		J.m[2][0] = dfr_z * dr_dx + dfth_z * dth_dx;
		J.m[2][1] = dfr_z * dr_dy + dfth_z * dth_dy;
		J.m[2][2] = dfr_z * dr_dz + dfth_z * dth_dz;

		// Propagate: A_{n+1} = J · A_n + I
		sJacobian3x3 newA;
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				double sum = 0.0;
				for (int k = 0; k < 3; k++)
					sum += J.m[row][k] * A.m[k][col];
				newA.m[row][col] = sum + ((row == col) ? 1.0 : 0.0);
			}
		}

		// Check if SA is still valid: the approximation error should be small
		// relative to the pixel spacing. The error grows with |A| * |δc|².
		// We check the matrix norm (Frobenius) times pixel spacing.
		double normSq = 0.0;
		for (int row = 0; row < 3; row++)
			for (int col = 0; col < 3; col++)
				normSq += newA.m[row][col] * newA.m[row][col];

		double norm = sqrt(normSq);
		double approxError = norm * pixelSpacing * pixelSpacing;

		// SA breaks down when the quadratic error term exceeds half a pixel
		if (approxError > 0.5 * pixelSpacing || !std::isfinite(norm))
		{
			break;
		}

		A = newA;
		skipIters = i + 1;
	}

	if (skipIters > 0)
	{
		seriesApprox.A = A;
		seriesApprox.skipIters = skipIters;
		seriesApprox.tolerance = pixelSpacing;
		seriesApprox.valid = true;
	}
}

// ============================================================
// cPerturbationIterator
// ============================================================

cPerturbationIterator::cPerturbationIterator() {}

void cPerturbationIterator::Configure(const sDeepZoomConfig &cfg)
{
	config = cfg;
}

void cPerturbationIterator::SetReferenceOrbit(const cReferenceOrbit *ref)
{
	refOrbit = ref;
}

sJacobian3x3 cPerturbationIterator::ComputeJacobian(
	const CVector3 &Z, double r, double theta, double phi) const
{
	/**
	 * Jacobian of the Mandelbulb mapping f(x,y,z) = r^p * g(θ,φ)
	 * where g(θ,φ) = (cos(pθ)cos(pφ), cos(pθ)sin(pφ), sin(pθ))
	 *
	 * We need ∂f_i/∂x_j. Using the chain rule through spherical coordinates:
	 *
	 * ∂f/∂x_j = (∂f/∂r)(∂r/∂x_j) + (∂f/∂θ)(∂θ/∂x_j) + (∂f/∂φ)(∂φ/∂x_j)
	 *
	 * Spherical coordinate derivatives:
	 *   ∂r/∂x = x/r,   ∂r/∂y = y/r,   ∂r/∂z = z/r
	 *   ∂θ/∂x = -xz/(r²√(x²+y²)), ∂θ/∂y = -yz/(r²√(x²+y²)), ∂θ/∂z = √(x²+y²)/r²
	 *   ∂φ/∂x = -y/(x²+y²), ∂φ/∂y = x/(x²+y²), ∂φ/∂z = 0
	 *
	 * f components:
	 *   f_x = r^p * cos(pθ)cos(pφ)
	 *   f_y = r^p * cos(pθ)sin(pφ)
	 *   f_z = r^p * sin(pθ)
	 */

	double p = config.power;
	sJacobian3x3 J;

	if (r < 1e-30)
	{
		// Near origin, Jacobian is zero (f ≈ 0)
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				J.m[i][j] = 0.0;
		return J;
	}

	double x = Z.x, y = Z.y, z = Z.z;
	double r2 = r * r;
	double rxy2 = x * x + y * y;
	double rxy = sqrt(rxy2);

	double pTheta = p * theta;
	double pPhi = p * phi;

	double cpth = cos(pTheta);
	double spth = sin(pTheta);
	double cpph = cos(pPhi);
	double spph = sin(pPhi);

	double rp = pow(r, p);
	double rp_minus1 = pow(r, p - 1.0);

	// ∂f/∂r components (scaled by r^(p-1))
	double dfr_x = p * rp_minus1 * cpth * cpph;
	double dfr_y = p * rp_minus1 * cpth * spph;
	double dfr_z = p * rp_minus1 * spth;

	// ∂f/∂θ components
	double dfth_x = rp * (-p * spth * cpph);
	double dfth_y = rp * (-p * spth * spph);
	double dfth_z = rp * (p * cpth);

	// ∂f/∂φ components
	double dfph_x = rp * (cpth * (-p * spph));
	double dfph_y = rp * (cpth * (p * cpph));
	double dfph_z = 0.0;

	// ∂r/∂(x,y,z) = (x,y,z)/r
	double dr_dx = x / r;
	double dr_dy = y / r;
	double dr_dz = z / r;

	// ∂θ/∂(x,y,z) — θ = asin(z/r), so:
	// ∂θ/∂x = -xz/(r²·rxy), ∂θ/∂y = -yz/(r²·rxy), ∂θ/∂z = rxy/r²
	double dth_dx, dth_dy, dth_dz;
	if (rxy > 1e-30)
	{
		dth_dx = -x * z / (r2 * rxy);
		dth_dy = -y * z / (r2 * rxy);
		dth_dz = rxy / r2;
	}
	else
	{
		dth_dx = 0.0;
		dth_dy = 0.0;
		dth_dz = (z >= 0.0) ? 0.0 : 0.0; // at poles, θ gradient is zero in x,y
	}

	// ∂φ/∂(x,y,z) — φ = atan2(y,x), so:
	// ∂φ/∂x = -y/(x²+y²), ∂φ/∂y = x/(x²+y²), ∂φ/∂z = 0
	double dph_dx, dph_dy;
	if (rxy2 > 1e-30)
	{
		dph_dx = -y / rxy2;
		dph_dy = x / rxy2;
	}
	else
	{
		dph_dx = 0.0;
		dph_dy = 0.0;
	}
	double dph_dz = 0.0;

	// Compose: J[i][j] = dfr_i * dr_dxj + dfth_i * dth_dxj + dfph_i * dph_dxj
	J.m[0][0] = dfr_x * dr_dx + dfth_x * dth_dx + dfph_x * dph_dx;
	J.m[0][1] = dfr_x * dr_dy + dfth_x * dth_dy + dfph_x * dph_dy;
	J.m[0][2] = dfr_x * dr_dz + dfth_x * dth_dz + dfph_x * dph_dz;

	J.m[1][0] = dfr_y * dr_dx + dfth_y * dth_dx + dfph_y * dph_dx;
	J.m[1][1] = dfr_y * dr_dy + dfth_y * dth_dy + dfph_y * dph_dy;
	J.m[1][2] = dfr_y * dr_dz + dfth_y * dth_dz + dfph_y * dph_dz;

	J.m[2][0] = dfr_z * dr_dx + dfth_z * dth_dx + dfph_z * dph_dx;
	J.m[2][1] = dfr_z * dr_dy + dfth_z * dth_dy + dfph_z * dph_dy;
	J.m[2][2] = dfr_z * dr_dz + dfth_z * dth_dz + dfph_z * dph_dz;

	return J;
}

CVector3 cPerturbationIterator::PerturbStep(const CVector3 &deltaZ, const CVector3 &deltaC,
	const sReferenceOrbitPoint &ref, double &deltaDE) const
{
	/**
	 * First-order perturbation:
	 *   δz_{n+1} = J_f(Z_n) · δz_n + δc
	 *
	 * Second-order correction (improves accuracy deep in zoom):
	 *   We compute f(Z_n + δz_n) - f(Z_n) exactly in double precision
	 *   when |δz_n| is small enough relative to |Z_n|.
	 *   This captures the full nonlinearity without needing higher-order terms.
	 *
	 * For the DE perturbation:
	 *   DE_{n+1} = p * r^(p-1) * DE_n + 1
	 *   δDE_{n+1} ≈ p * r^(p-1) * δDE_n + p*(p-1)*r^(p-2) * (Z·δz/r) * DE_n
	 *
	 * But for the first implementation, we use the exact perturbation:
	 *   Compute f(Z_n + δz_n) in double precision and subtract f(Z_n).
	 */

	double p = config.power;
	CVector3 Zfull = ref.Z + deltaZ;
	double rFull = Zfull.Length();

	if (rFull < 1e-30)
	{
		deltaDE = 0.0;
		return deltaC;
	}

	// Compute f(Z_n + δz_n) directly in double precision
	double thetaFull = asin(Clamp(Zfull.z / rFull, -1.0, 1.0)) + config.betaAngleOffset;
	double phiFull = atan2(Zfull.y, Zfull.x) + config.alphaAngleOffset;
	double rpFull = pow(rFull, p);
	double rp1Full = pow(rFull, p - 1.0);

	double pTh = p * thetaFull;
	double pPh = p * phiFull;
	double cth = cos(pTh);
	double sth = sin(pTh);
	double cph = cos(pPh);
	double sph = sin(pPh);

	CVector3 fFull(rpFull * cth * cph, rpFull * cth * sph, rpFull * sth);

	// Compute f(Z_n) in double precision (from reference orbit)
	double thetaRef = ref.theta + config.betaAngleOffset;
	double phiRef = ref.phi + config.alphaAngleOffset;
	double rpRef = pow(ref.r, p);
	double pThRef = p * thetaRef;
	double pPhRef = p * phiRef;

	CVector3 fRef(rpRef * cos(pThRef) * cos(pPhRef),
		rpRef * cos(pThRef) * sin(pPhRef),
		rpRef * sin(pThRef));

	// δz_{n+1} = f(Z_n + δz_n) - f(Z_n) + δc
	CVector3 newDeltaZ = fFull - fRef + deltaC;

	// Perturbed DE: DE_{n+1} = p * r_full^(p-1) * DE_full + 1
	// where DE_full = ref.DE + deltaDE
	double deFull = ref.DE + deltaDE;
	double newDEFull = p * rp1Full * deFull + 1.0;
	double newDERef = p * pow(ref.r, p - 1.0) * ref.DE + 1.0;
	deltaDE = newDEFull - newDERef;

	return newDeltaZ;
}

bool cPerturbationIterator::ShouldRebase(
	const CVector3 &deltaZ, const sReferenceOrbitPoint &ref) const
{
	double deltaR = deltaZ.Length();
	// Rebase when δz is too large relative to Z — precision is being lost
	// A good threshold is when |δz| > |Z| (delta exceeds reference)
	return (ref.r > 1e-30 && deltaR > ref.r * config.rebaseThreshold);
}

CVector3 cPerturbationIterator::Rebase(
	CVector3 &deltaZ, double &deltaDE,
	const sReferenceOrbitPoint &ref, int iter) const
{
	/**
	 * Rebasing: when δz grows too large, the subtraction f(Z+δz) - f(Z)
	 * loses significant digits. We "rebase" by:
	 *   1. Computing the full position: z_full = Z_n + δz_n
	 *   2. Finding the closest reference orbit point to z_full
	 *   3. Setting δz_new = z_full - Z_closest
	 *
	 * For simplicity (single reference orbit), we rebase to the same
	 * reference orbit but restart from a later iteration where Z_n is
	 * closer to our current z_full. This is the "glitch detection" approach.
	 *
	 * The key insight: δz is relative to the CURRENT reference point.
	 * After rebase, δz = z_full - Z_n is recomputed fresh (smaller).
	 */

	CVector3 zFull = ref.Z + deltaZ;

	// Search forward in the orbit for a point closer to zFull
	int bestIter = iter;
	double bestDist = deltaZ.Length();
	int searchRange = std::min(50, refOrbit->GetLength() - iter - 1);

	for (int j = 1; j <= searchRange; j++)
	{
		int candidateIter = iter + j;
		if (candidateIter >= refOrbit->GetLength()) break;

		CVector3 diff = zFull - refOrbit->GetPoint(candidateIter).Z;
		double dist = diff.Length();
		if (dist < bestDist)
		{
			bestDist = dist;
			bestIter = candidateIter;
		}
	}

	if (bestIter != iter)
	{
		const sReferenceOrbitPoint &newRef = refOrbit->GetPoint(bestIter);
		deltaZ = zFull - newRef.Z;
		double deFull = ref.DE + deltaDE;
		deltaDE = deFull - newRef.DE;
	}

	return deltaZ;
}

cPerturbationIterator::sResult cPerturbationIterator::Iterate(const CVector3 &deltaC) const
{
	sResult result;
	result.iterations = 0;
	result.distance = 1e20;
	result.colorIndex = 0.0;
	result.escaped = false;
	result.finalPos = CVector3(0, 0, 0);

	if (!refOrbit || refOrbit->GetLength() < 2) return result;

	CVector3 deltaZ = deltaC; // initial δz = δc (since z₀ = c)
	double deltaDE = 0.0;     // initial δDE = 0
	int startIter = 0;

	// Series Approximation: skip early iterations
	const sSeriesCoeff3x3 &sa = refOrbit->GetSeriesApprox();
	if (sa.valid && sa.skipIters > 0)
	{
		// δz_n ≈ A_n · δc (matrix-vector product)
		deltaZ = sa.A.Apply(deltaC);
		startIter = sa.skipIters;

		// Approximate δDE after SA: use magnitude of A·δc as scale
		// This is a rough estimate; the exact DE is refined in the iteration loop
		double deltaZLen = deltaZ.Length();
		if (deltaZLen > 0)
		{
			deltaDE = deltaZLen; // simplified DE seed after SA skip
		}
	}

	int maxIter = std::min(config.maxIterations, refOrbit->GetLength() - 1);

	for (int i = startIter; i < maxIter; i++)
	{
		const sReferenceOrbitPoint &ref = refOrbit->GetPoint(i);

		// Full position
		CVector3 zFull = ref.Z + deltaZ;
		double rFull = zFull.Length();

		// Escape check
		if (rFull > config.bailout)
		{
			result.escaped = true;
			result.iterations = i;
			result.finalPos = zFull;

			// Distance estimation: DE = 0.5 * r * ln(r) / |dr/dc|
			double deFull = ref.DE + deltaDE;
			if (deFull > 0.0 && rFull > 1.0)
			{
				result.distance = 0.5 * rFull * log(rFull) / fabs(deFull);
			}
			else
			{
				result.distance = rFull;
			}
			result.colorIndex = static_cast<double>(i);
			return result;
		}

		// Rebasing: if δz is too large relative to Z, rebase to maintain precision
		if (ShouldRebase(deltaZ, ref))
		{
			deltaZ = Rebase(deltaZ, deltaDE, ref, i);
		}

		// Perturbation step
		deltaZ = PerturbStep(deltaZ, deltaC, ref, deltaDE);
	}

	// Didn't escape — we're inside the fractal
	result.iterations = maxIter;
	result.escaped = false;
	int lastIdx = std::min(maxIter, refOrbit->GetLength() - 1);
	result.finalPos = refOrbit->GetPoint(lastIdx).Z + deltaZ;

	// Interior DE estimate
	double rFinal = result.finalPos.Length();
	double deFull = refOrbit->GetPoint(lastIdx).DE + deltaDE;
	if (deFull > 0.0 && rFinal > 0.0)
	{
		result.distance = 0.5 * rFinal * log(std::max(rFinal, 1.0)) / fabs(deFull);
	}
	else
	{
		result.distance = 0.0;
	}

	return result;
}

// ============================================================
// cDeepZoomManager
// ============================================================

cDeepZoomManager::cDeepZoomManager() {}
cDeepZoomManager::~cDeepZoomManager() {}

void cDeepZoomManager::Configure(const sDeepZoomConfig &cfg)
{
	config = cfg;
	refOrbit.Configure(cfg);
	perturbator.Configure(cfg);
}

void cDeepZoomManager::SetCenter(const CVector3 &center)
{
	currentCenter = center;
	refOrbit.Compute(center);
	perturbator.SetReferenceOrbit(&refOrbit);

	// Compute Series Approximation if enabled
	if (config.seriesApproxEnabled && currentPixelSpacing > 0.0)
	{
		refOrbit.ComputeSeriesApproximation(currentPixelSpacing);
	}

	referenceComputed = true;
}

void cDeepZoomManager::SetJuliaMode(bool enabled, const CVector3 &juliaC)
{
	config.juliaMode = enabled;
	config.juliaC = juliaC;
	refOrbit.Configure(config);
	perturbator.Configure(config);
	referenceComputed = false;
}

void cDeepZoomManager::SetPixelSpacing(double spacing)
{
	currentPixelSpacing = spacing;
}

int cDeepZoomManager::GetSASkipIterations() const
{
	const sSeriesCoeff3x3 &sa = refOrbit.GetSeriesApprox();
	return sa.valid ? sa.skipIters : 0;
}

int cDeepZoomManager::GetRebaseCount() const
{
	return static_cast<int>(refOrbit.GetRebasePoints().size());
}

double cDeepZoomManager::CalculateDistance(
	const CVector3 &point, int *outIters, double *outColorIndex) const
{
	if (!referenceComputed) return 1e20;

	// δc = point - center (the pixel's offset from the reference)
	CVector3 deltaC = point - currentCenter;

	auto result = perturbator.Iterate(deltaC);

	if (outIters) *outIters = result.iterations;
	if (outColorIndex) *outColorIndex = result.colorIndex;

	return result.distance;
}

int cDeepZoomManager::PrecisionForZoom(double zoomLevel)
{
	// Each order of magnitude in zoom requires ~3.32 bits of precision
	// (log2(10) ≈ 3.322)
	// We add a safety margin of 64 bits
	if (zoomLevel <= 1.0) return kDefaultPrecisionBits;

	double bitsNeeded = log2(zoomLevel) + 64.0;
	int precBits = static_cast<int>(bitsNeeded);

	// Round up to nearest 64 for MPFR efficiency
	precBits = ((precBits + 63) / 64) * 64;

	return Clamp(precBits, kDefaultPrecisionBits, kMaxPrecisionBits);
}

bool cDeepZoomManager::ShouldUseDeepZoom(double zoomLevel)
{
	// At zoom levels beyond ~10^13, double precision starts to fail
	// We activate deep zoom a bit before that threshold
	return zoomLevel > 1e12;
}

} // namespace deep_zoom

#endif // USE_MPFR

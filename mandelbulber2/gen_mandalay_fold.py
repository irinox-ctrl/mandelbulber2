#!/usr/bin/env python3
"""Generate 50 Mandalay Fold formulas for 3x3lion.

Each formula is based on Mandalay Box V2 but applies a unique mathematical
fold/flow operation. Uses linearDEFunction like the original Mandalay Box.
"""
import re, os

ENUM_START = 3500
BASE_DIR = "/home/ubuntu/repos/mb-experiment/mandelbulber2"
DEF_DIR = f"{BASE_DIR}/formula/definition"
CL_DIR = f"{BASE_DIR}/formula/opencl"
UI_DIR = f"{BASE_DIR}/formula/ui"

def parse_formulas(path):
    with open(path) as f:
        lines = f.readlines()
    formulas = []
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        m = re.match(r'^Mandalay Fold V(\d+)\s+[—–-]\s+(.+)', line)
        if m:
            num = int(m.group(1))
            name = m.group(2).strip()
            desc = math = visual = ""
            j = i + 1
            while j < len(lines):
                l = lines[j].strip()
                if l.startswith("Toevoeging:"):
                    desc = l[len("Toevoeging:"):].strip()
                elif l.startswith("Wiskunde:"):
                    math = l[len("Wiskunde:"):].strip()
                elif l.startswith("Visueel:"):
                    visual = l[len("Visueel:"):].strip()
                elif re.match(r'^Mandalay Fold V\d+', l):
                    break
                j += 1
            formulas.append({
                'num': num, 'name': name, 'desc': desc,
                'math': math, 'visual': visual,
            })
        i += 1
    return formulas

def to_internal(name, num):
    s = name.lower()
    s = re.sub(r'[^a-z0-9]+', '_', s).strip('_')
    return f"mandalay_fold_{s}"

def to_class(name, num):
    s = name.replace('-', ' ').replace('_', ' ')
    words = s.split()
    camel = ''.join(w.capitalize() for w in words if w)
    camel = re.sub(r'[^A-Za-z0-9]', '', camel)
    return f"cFractalMandalayFold{camel}"

def to_enum(name, num):
    s = name.replace('-', ' ').replace('_', ' ')
    words = s.split()
    camel = words[0].lower() + ''.join(w.capitalize() for w in words[1:] if w)
    camel = re.sub(r'[^A-Za-z0-9]', '', camel)
    return f"mandalayFold{camel[0].upper()}{camel[1:]}"

def to_filename(name, num):
    s = name.lower()
    s = re.sub(r'[^a-z0-9]+', '_', s).strip('_')
    return f"mandalay_fold_{s}"

def to_cl_func(name, num):
    s = name.replace('-', ' ').replace('_', ' ')
    words = s.split()
    camel = ''.join(w.capitalize() for w in words if w)
    camel = re.sub(r'[^A-Za-z0-9]', '', camel)
    return f"MandalayFold{camel}Iteration"

def get_fold_code(f):
    """Generate the unique fold operation for each Mandalay Fold variant."""
    num = f['num']
    
    # Each formula gets a unique mathematical fold based on its theme
    codes = {
        1: """	// Ricci Flow fold: evolve toward constant curvature
	double Kx = (z.y - z.x) + (z.z - z.x);
	double Ky = (z.x - z.y) + (z.z - z.y);
	double Kz = (z.x - z.z) + (z.y - z.z);
	double dt = fractal->transformCommon.scale08;
	z.x -= 2.0 * Kx * dt;
	z.y -= 2.0 * Ky * dt;
	z.z -= 2.0 * Kz * dt;""",
        2: """	// Mean Curvature Flow fold: evolve toward sphere
	double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
	if (r > 1e-21) {
		double H = 2.0 / r;
		double dt = fractal->transformCommon.scale08;
		z.x += H * z.x / r * dt;
		z.y += H * z.y / r * dt;
		z.z += H * z.z / r * dt;
	}""",
        3: """	// Inverse MCF fold: expand outward
	double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
	if (r > 1e-21) {
		double invH = r / 2.0;
		double dt = fractal->transformCommon.scale08;
		z.x -= z.x / r * invH * dt;
		z.y -= z.y / r * invH * dt;
		z.z -= z.z / r * invH * dt;
	}""",
        4: """	// Willmore Flow fold: minimize bending energy
	double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
	if (r > 1e-21) {
		double K = 1.0 / (r * r);
		double H = 1.0 / r;
		double W = H * H - K;
		double dt = fractal->transformCommon.scale08;
		z.x -= W * z.x / r * dt;
		z.y -= W * z.y / r * dt;
		z.z -= W * z.z / r * dt;
	}""",
        5: """	// Gauss Curvature Flow fold: affine-invariant evolution
	double r2 = z.x*z.x + z.y*z.y + z.z*z.z;
	if (r2 > 1e-21) {
		double K = 1.0 / r2;
		double dt = fractal->transformCommon.scale08;
		z.x += K * z.x * dt;
		z.y += K * z.y * dt;
		z.z += K * z.z * dt;
	}""",
        6: """	// Affine Sphere fold: det(D²u) mapping
	double u = z.x*z.x + z.y*z.y + z.z*z.z;
	double det = 4.0 * z.x * z.y * z.z;
	double L = fractal->transformCommon.scale08;
	if (u > 1e-21) {
		z.x += det / (u * u) * z.x * L;
		z.y += det / (u * u) * z.y * L;
		z.z += det / (u * u) * z.z * L;
	}""",
        7: """	// Monge-Ampere fold: nonlinear elliptic PDE
	double hxx = 2.0; double hyy = 2.0; double hzz = 2.0;
	double hxy = z.x * z.y; double hxz = z.x * z.z; double hyz = z.y * z.z;
	double det = hxx*(hyy*hzz - hyz*hyz) - hxy*(hxy*hzz - hyz*hxz) + hxz*(hxy*hyz - hyy*hxz);
	double s = fractal->transformCommon.scale08;
	z.x += det * z.x * s * 0.01;
	z.y += det * z.y * s * 0.01;
	z.z += det * z.z * s * 0.01;""",
        8: """	// Complex Monge-Ampere fold: Kahler-Einstein style
	double u = z.x*z.x + z.y*z.y;
	double v = z.z;
	double F = exp(-u * 0.1) * fractal->transformCommon.scale08;
	z.x *= (1.0 + F);
	z.y *= (1.0 + F);
	z.z += sin(v) * F;""",
        9: """	// Hessian Equation fold: k-Hessian generalization
	double s2 = z.x*z.x + z.y*z.y + z.z*z.z;
	double sk = pow(fabs(s2) + 1e-21, 0.333);
	double s = fractal->transformCommon.scale08;
	z.x *= sk * s + (1.0 - s);
	z.y *= sk * s + (1.0 - s);
	z.z *= sk * s + (1.0 - s);""",
        10: """	// Curvature Measure fold: Steiner formula
	double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
	double mu = 1.0 / (1.0 + r);
	double s = fractal->transformCommon.scale08;
	z.x = z.x * (1.0 - s) + z.x * mu * s;
	z.y = z.y * (1.0 - s) + z.y * mu * s;
	z.z = z.z * (1.0 - s) + z.z * mu * s;""",
        11: """	// Integral Geometry fold: Crofton formula
	double s = fractal->transformCommon.scale08;
	double proj_xy = fabs(z.x * z.y);
	double proj_xz = fabs(z.x * z.z);
	double proj_yz = fabs(z.y * z.z);
	double crofton = (proj_xy + proj_xz + proj_yz) * 0.333;
	z.x += sign(z.x) * crofton * s;
	z.y += sign(z.y) * crofton * s;
	z.z += sign(z.z) * crofton * s;""",
        12: """	// Valuation Theory fold: Hadwiger decomposition
	double V = z.x * z.y * z.z;
	double S = fabs(z.x*z.y) + fabs(z.y*z.z) + fabs(z.x*z.z);
	double M = fabs(z.x) + fabs(z.y) + fabs(z.z);
	double s = fractal->transformCommon.scale08;
	z.x += (V * 0.1 + S * 0.01) * sign(z.x) * s;
	z.y += (V * 0.1 + S * 0.01) * sign(z.y) * s;
	z.z += (V * 0.1 + S * 0.01) * sign(z.z) * s;""",
        13: """	// Convex Integration fold: Nash-Kuiper embedding
	double s = fractal->transformCommon.scale08;
	double freq = 3.14159 * 4.0;
	double amp = s * 0.1;
	z.x += amp * sin(freq * z.y) * cos(freq * z.z);
	z.y += amp * sin(freq * z.z) * cos(freq * z.x);
	z.z += amp * sin(freq * z.x) * cos(freq * z.y);""",
        14: """	// h-Principle fold: holonomic approximation
	double s = fractal->transformCommon.scale08;
	double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
	double theta = atan2(z.y, z.x);
	double phi = acos(z.z / (r + 1e-21));
	z.x += s * 0.1 * sin(phi * 3.0) * cos(theta * 2.0);
	z.y += s * 0.1 * sin(phi * 3.0) * sin(theta * 2.0);
	z.z += s * 0.1 * cos(phi * 3.0);""",
        15: """	// Microflexibility fold: local h-principle
	double s = fractal->transformCommon.scale08;
	double local = exp(-z.x*z.x - z.y*z.y - z.z*z.z);
	z.x += s * local * z.y;
	z.y += s * local * z.z;
	z.z += s * local * z.x;""",
        16: """	// Holonomic Approximation fold: C0-close sections
	double s = fractal->transformCommon.scale08;
	double t = z.x + z.y + z.z;
	z.x += s * 0.1 * sin(t * 2.0);
	z.y += s * 0.1 * cos(t * 2.0);
	z.z += s * 0.1 * sin(t * 3.0);""",
        17: """	// Wrinkle fold: wrinkle singularity
	double s = fractal->transformCommon.scale08;
	double freq = 8.0;
	double warp = sin(z.x * freq) * sin(z.y * freq) * s * 0.05;
	z.z += warp;
	aux.DE *= 1.0 + fabs(warp * freq * 0.1);""",
        18: """	// Fold Singularity fold: Morse critical point
	double s = fractal->transformCommon.scale08;
	double morse = z.x*z.x - z.y*z.y;
	z.z += morse * s * 0.1;
	z.x *= 1.0 + s * 0.05 * z.z;""",
        19: """	// Cusp Singularity fold: A2 swallowtail
	double s = fractal->transformCommon.scale08;
	double cusp = z.x*z.x*z.x + z.x * z.y;
	z.z += cusp * s * 0.01;""",
        20: """	// Swallowtail fold: A3 catastrophe
	double s = fractal->transformCommon.scale08;
	double sw = z.x*z.x*z.x*z.x + z.y*z.x*z.x + z.z*z.x;
	z.x += sw * s * 0.001;""",
        21: """	// Butterfly fold: A4 catastrophe
	double s = fractal->transformCommon.scale08;
	double bfly = z.x*z.x*z.x*z.x*z.x + z.y*z.x*z.x*z.x + z.z*z.x*z.x;
	z.x += bfly * s * 0.0001;""",
        22: """	// Umbilic fold: D4 singularity
	double s = fractal->transformCommon.scale08;
	double K1 = 1.0 / (fabs(z.x) + 1e-21);
	double K2 = 1.0 / (fabs(z.y) + 1e-21);
	double umbilic = K1 - K2;
	z.z += umbilic * s * 0.01;""",
        23: """	// Ridge fold: extremal principal curvature
	double s = fractal->transformCommon.scale08;
	double dKx = -2.0 * z.x / pow(z.x*z.x + z.y*z.y + z.z*z.z + 1e-21, 1.5);
	z.x += dKx * s;
	z.y += dKx * s * 0.5;""",
        24: """	// Symmetry Set fold: medial axis skeleton
	double s = fractal->transformCommon.scale08;
	double mid_xy = (z.x + z.y) * 0.5;
	double mid_xz = (z.x + z.z) * 0.5;
	z.x = z.x * (1.0 - s) + mid_xy * s;
	z.z = z.z * (1.0 - s) + mid_xz * s;""",
        25: """	// Medial Axis fold: Blum skeleton
	double s = fractal->transformCommon.scale08;
	double ax = fabs(z.x); double ay = fabs(z.y); double az = fabs(z.z);
	double minAx = min(ax, min(ay, az));
	z.x = z.x * (1.0 - s) + sign(z.x) * minAx * s;
	z.y = z.y * (1.0 - s) + sign(z.y) * minAx * s;
	z.z = z.z * (1.0 - s) + sign(z.z) * minAx * s;""",
        26: """	// Laguerre Geometry fold: oriented planes
	double s = fractal->transformCommon.scale08;
	double r2 = z.x*z.x + z.y*z.y + z.z*z.z;
	double inv = 1.0 / (r2 + 1.0);
	z.x = z.x * (1.0 - s) + 2.0 * z.x * inv * s;
	z.y = z.y * (1.0 - s) + 2.0 * z.y * inv * s;
	z.z = z.z * (1.0 - s) + (r2 - 1.0) * inv * s;""",
        27: """	// Lie Sphere fold: oriented spheres geometry
	double s = fractal->transformCommon.scale08;
	double r2 = z.x*z.x + z.y*z.y + z.z*z.z;
	double lie = (r2 - 1.0) / (r2 + 1.0);
	z.x *= (1.0 + lie * s * 0.5);
	z.y *= (1.0 + lie * s * 0.5);
	z.z *= (1.0 + lie * s * 0.5);""",
        28: """	// Dupin Cyclide fold: inversion of torus
	double s = fractal->transformCommon.scale08;
	double R = 1.5;
	double rxy = sqrt(z.x*z.x + z.y*z.y);
	double dRing = rxy - R;
	double dTorus = sqrt(dRing*dRing + z.z*z.z);
	if (dTorus > 1e-21) {
		double inv = 1.0 / dTorus;
		z.x += dRing * inv * z.x / (rxy + 1e-21) * s;
		z.y += dRing * inv * z.y / (rxy + 1e-21) * s;
		z.z += z.z * inv * s;
	}""",
        29: """	// Channel Surface fold: envelope of spheres
	double s = fractal->transformCommon.scale08;
	double t = atan2(z.y, z.x);
	double spine_r = 1.0 + 0.3 * sin(t * 3.0);
	double rxy = sqrt(z.x*z.x + z.y*z.y);
	double diff = rxy - spine_r;
	z.x += diff * cos(t) * s * 0.5;
	z.y += diff * sin(t) * s * 0.5;""",
        30: """	// Pipe Surface fold: fixed radius tube
	double s = fractal->transformCommon.scale08;
	double pipe_r = 0.5;
	double rxy = sqrt(z.x*z.x + z.y*z.y);
	if (rxy > 1e-21) {
		double factor = (rxy - pipe_r) / rxy;
		z.x -= z.x * factor * s;
		z.y -= z.y * factor * s;
	}""",
        31: """	// Offset Surface fold: parallel surface
	double s = fractal->transformCommon.scale08;
	double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
	double offset = 0.3;
	if (r > 1e-21) {
		z.x += z.x / r * offset * s;
		z.y += z.y / r * offset * s;
		z.z += z.z / r * offset * s;
	}""",
        32: """	// Minkowski Sum fold: A+B dilation
	double s = fractal->transformCommon.scale08;
	double bx = 0.5 * sign(z.x);
	double by = 0.5 * sign(z.y);
	double bz = 0.5 * sign(z.z);
	z.x += bx * s;
	z.y += by * s;
	z.z += bz * s;""",
        33: """	// Morphological Dilation fold
	double s = fractal->transformCommon.scale08;
	double se = 0.3;
	z.x = max(z.x, se) * s + z.x * (1.0 - s);
	z.y = max(z.y, se) * s + z.y * (1.0 - s);
	z.z = max(z.z, se) * s + z.z * (1.0 - s);""",
        34: """	// Morphological Erosion fold
	double s = fractal->transformCommon.scale08;
	double se = 0.3;
	z.x = min(z.x, -se) * s + z.x * (1.0 - s);
	z.y = min(z.y, -se) * s + z.y * (1.0 - s);
	z.z = min(z.z, -se) * s + z.z * (1.0 - s);""",
        35: """	// Distance Transform fold: EDT nearest feature
	double s = fractal->transformCommon.scale08;
	double ax = fabs(z.x); double ay = fabs(z.y); double az = fabs(z.z);
	double dEdge = min(ax, min(ay, az));
	z.x *= (1.0 + dEdge * s);
	z.y *= (1.0 + dEdge * s);
	z.z *= (1.0 + dEdge * s);""",
        36: """	// Voronoi Diagram fold: nearest site decomposition
	double s = fractal->transformCommon.scale08;
	double cell = 1.0;
	z.x = z.x - cell * floor(z.x / cell + 0.5);
	z.y = z.y - cell * floor(z.y / cell + 0.5);
	z.z = z.z - cell * floor(z.z / cell + 0.5);
	z *= (1.0 + s);""",
        37: """	// Delaunay Triangulation fold: empty circumcircle
	double s = fractal->transformCommon.scale08;
	double circ = z.x*z.x + z.y*z.y + z.z*z.z;
	double flip = (circ < 1.0) ? -1.0 : 1.0;
	z.x *= (1.0 + flip * s * 0.1);
	z.y *= (1.0 + flip * s * 0.1);
	z.z *= (1.0 + flip * s * 0.1);""",
        38: """	// Power Diagram fold: weighted Voronoi
	double s = fractal->transformCommon.scale08;
	double w1 = 1.0; double w2 = 0.7;
	double d1 = z.x*z.x + z.y*z.y + z.z*z.z - w1;
	double d2 = (z.x-1.0)*(z.x-1.0) + z.y*z.y + z.z*z.z - w2;
	double blend = 1.0 / (1.0 + exp(-(d1 - d2) * 5.0));
	z.x = z.x * (1.0 - blend * s) + (z.x - 0.5) * blend * s;""",
        39: """	// Apollonius Diagram fold: sphere bisectors
	double s = fractal->transformCommon.scale08;
	double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
	double r1 = 1.0; double r2 = 0.5;
	double d1 = fabs(r - r1); double d2 = fabs(r - r2);
	double t = d1 / (d1 + d2 + 1e-21);
	z *= (1.0 + (t - 0.5) * s);""",
        40: """	// Alpha Shape fold: filtration
	double s = fractal->transformCommon.scale08;
	double alpha = 1.0;
	double r2 = z.x*z.x + z.y*z.y + z.z*z.z;
	double inside = (r2 < alpha*alpha) ? 1.0 : 0.0;
	z.x = z.x * (1.0 - s) + z.x * inside * s;
	z.y = z.y * (1.0 - s) + z.y * inside * s;
	z.z = z.z * (1.0 - s) + z.z * inside * s;""",
        41: """	// Persistent Homology fold: barcode persistence
	double s = fractal->transformCommon.scale08;
	double birth = min(fabs(z.x), min(fabs(z.y), fabs(z.z)));
	double death = max(fabs(z.x), max(fabs(z.y), fabs(z.z)));
	double persist = death - birth;
	z *= (1.0 + persist * s * 0.1);""",
        42: """	// Betti Number fold: topological holes
	double s = fractal->transformCommon.scale08;
	double b0 = 1.0;
	double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
	double b1 = (r > 0.5 && r < 1.5) ? 1.0 : 0.0;
	z.x *= (1.0 + (b0 + b1) * s * 0.1);
	z.y *= (1.0 + (b0 + b1) * s * 0.1);""",
        43: """	// Euler Characteristic fold: chi = V - E + F
	double s = fractal->transformCommon.scale08;
	double V = fabs(z.x * z.y * z.z);
	double E = fabs(z.x*z.y) + fabs(z.y*z.z) + fabs(z.x*z.z);
	double F = fabs(z.x) + fabs(z.y) + fabs(z.z);
	double chi = V - E + F;
	z *= (1.0 + chi * s * 0.01);""",
        44: """	// Gauss-Bonnet fold: integral(K) = 2*pi*chi
	double s = fractal->transformCommon.scale08;
	double r2 = z.x*z.x + z.y*z.y + z.z*z.z;
	double K = 1.0 / (r2 + 1e-21);
	double integral_K = K * 4.0 * 3.14159;
	z.x += z.x * integral_K * s * 0.001;
	z.y += z.y * integral_K * s * 0.001;
	z.z += z.z * integral_K * s * 0.001;""",
        45: """	// Chern-Gauss-Bonnet fold: Pfaffian integral
	double s = fractal->transformCommon.scale08;
	double r2 = z.x*z.x + z.y*z.y + z.z*z.z;
	double pf = (z.x*z.y - z.y*z.x) + (z.y*z.z - z.z*z.y);
	double cgb = 1.0 / (r2 + 1.0);
	z.x *= (1.0 + cgb * s);
	z.y *= (1.0 + cgb * s);
	z.z *= (1.0 - cgb * s);""",
        46: """	// Atiyah-Singer Index fold: elliptic operator index
	double s = fractal->transformCommon.scale08;
	double ch = exp(-z.x*z.x - z.y*z.y);
	double td = 1.0 / (1.0 - exp(-sqrt(z.z*z.z + 1e-21)));
	double idx = ch * td * 0.01;
	z.x += idx * s;
	z.y += idx * s;""",
        47: """	// Dirac Operator fold: Clifford multiplication
	double s = fractal->transformCommon.scale08;
	double nx = z.y * z.z;
	double ny = z.z * z.x;
	double nz = z.x * z.y;
	z.x += nx * s * 0.1;
	z.y += ny * s * 0.1;
	z.z += nz * s * 0.1;""",
        48: """	// Spin Geometry fold: spinor bundle
	double s = fractal->transformCommon.scale08;
	double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
	double theta = atan2(z.y, z.x);
	z.x += s * 0.1 * cos(theta * 0.5) * r;
	z.y += s * 0.1 * sin(theta * 0.5) * r;
	z.z *= (1.0 + s * 0.05);""",
        49: """	// Twistor Theory fold: CP3 null geodesic
	double s = fractal->transformCommon.scale08;
	double w1 = z.x + z.y;
	double w2 = z.x - z.y;
	z.x = w1 * cos(z.z * s) - w2 * sin(z.z * s);
	z.y = w1 * sin(z.z * s) + w2 * cos(z.z * s);
	z.z *= (1.0 + s * 0.1);""",
        50: """	// Self-Dual Yang-Mills fold: instanton ADHM
	double s = fractal->transformCommon.scale08;
	double F12 = z.x * z.y; double F13 = z.x * z.z; double F23 = z.y * z.z;
	double sd = F12 + F13 + F23;
	double asd = F12 - F13 + F23;
	z.x += (sd - asd) * s * 0.01;
	z.y += (sd + asd) * s * 0.01;
	z.z *= (1.0 + fabs(sd) * s * 0.01);""",
    }
    return codes.get(num, f"""	// Mandalay Fold V{num}: generic fold
	double s = fractal->transformCommon.scale08;
	z.x = z.x * cos(s) - z.y * sin(s);
	z.y = z.x * sin(s) + z.y * cos(s);""")

def sanitize_comment(s):
    return s.replace('*/', '* /')

def gen_cpp(f, enum_id):
    internal = to_internal(f['name'], f['num'])
    classname = to_class(f['name'], f['num'])
    combo = f"Mandalay Fold V{f['num']} {f['name']}"
    enumname = to_enum(f['name'], f['num'])
    fold_code = get_fold_code(f)
    safe_desc = sanitize_comment(f['desc'])
    safe_math = sanitize_comment(f['math'])
    
    return f'''/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: {safe_desc}
 * Math: {safe_math}
 */

#include "all_fractal_definitions.h"

{classname}::{classname}() : cAbstractFractal()
{{
\tnameInComboBox = "{combo}";
\tinternalName = "{internal}";
\tinternalID = fractal::{enumname};
\tDEType = analyticDEType;
\tDEFunctionType = linearDEFunction;
\tcpixelAddition = cpixelEnabledByDefault;
\tdefaultBailout = 100.0;
\tDEAnalyticFunction = analyticFunctionLinear;
\tcoloringFunction = coloringFunctionDefault;
}}

void {classname}::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{{
\t// Mandalay base: abs fold
\tz = fabs(z);

\t// Sort for Mandalay clip
\tif (z.z > z.y) swap(z.y, z.z);
\tif (z.y > z.x) swap(z.x, z.y);
\tif (z.z > z.y) swap(z.y, z.z);

{fold_code}

\t// Spherical fold
\tdouble rr = z.Dot(z);
\tif (rr < fractal->transformCommon.minR2p25)
\t{{
\t\tdouble tglad_factor1 = fractal->transformCommon.maxR2d1 / fractal->transformCommon.minR2p25;
\t\tz *= tglad_factor1;
\t\taux.DE *= tglad_factor1;
\t}}
\telse if (rr < fractal->transformCommon.maxR2d1)
\t{{
\t\tdouble tglad_factor2 = fractal->transformCommon.maxR2d1 / rr;
\t\tz *= tglad_factor2;
\t\taux.DE *= tglad_factor2;
\t}}

\t// Scale
\tdouble useScale = fractal->transformCommon.scale2;
\tz *= useScale;
\taux.DE = aux.DE * fabs(useScale) + 1.0;

\t// Rotation
\tif (fractal->transformCommon.rotationEnabled)
\t{{
\t\tz = fractal->transformCommon.rotationMatrix.RotateVector(z);
\t}}
}}
'''


def gen_cl(f, enum_id):
    internal = to_internal(f['name'], f['num'])
    classname = to_class(f['name'], f['num'])
    funcname = to_cl_func(f['name'], f['num'])
    fold_code = get_fold_code(f)
    safe_desc = sanitize_comment(f['desc'])
    
    # Convert C++ to OpenCL
    cl_fold = fold_code
    cl_fold = cl_fold.replace('double ', 'REAL ')
    cl_fold = cl_fold.replace('fractal->transformCommon.', 'fractal->transformCommon.')
    cl_fold = cl_fold.replace('CVector4', 'REAL4')
    cl_fold = cl_fold.replace('sign(', 'sign(')
    cl_fold = cl_fold.replace('int(', '(int)(')
    cl_fold = cl_fold.replace('aux.DE', 'aux->DE')
    cl_fold = cl_fold.replace('aux.r', 'aux->r')
    
    return f'''/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Mandalay Fold: {safe_desc}
 */

REAL4 {funcname}(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{{
\t// Mandalay base: abs fold
\tz = fabs(z);

\t// Sort for Mandalay clip
\tREAL tmp;
\tif (z.z > z.y) {{ tmp = z.y; z.y = z.z; z.z = tmp; }}
\tif (z.y > z.x) {{ tmp = z.x; z.x = z.y; z.y = tmp; }}
\tif (z.z > z.y) {{ tmp = z.y; z.y = z.z; z.z = tmp; }}

{cl_fold}

\t// Spherical fold
\tREAL rr = dot(z, z);
\tif (rr < fractal->transformCommon.minR2p25)
\t{{
\t\tREAL tglad_factor1 = fractal->transformCommon.maxR2d1 / fractal->transformCommon.minR2p25;
\t\tz *= tglad_factor1;
\t\taux->DE *= tglad_factor1;
\t}}
\telse if (rr < fractal->transformCommon.maxR2d1)
\t{{
\t\tREAL tglad_factor2 = fractal->transformCommon.maxR2d1 / rr;
\t\tz *= tglad_factor2;
\t\taux->DE *= tglad_factor2;
\t}}

\t// Scale
\tREAL useScale = fractal->transformCommon.scale2;
\tz *= useScale;
\taux->DE = aux->DE * fabs(useScale) + 1.0f;

\treturn z;
}}
'''


def gen_ui(f):
    internal = to_internal(f['name'], f['num'])
    combo = f"Mandalay Fold V{f['num']} {f['name']}"
    desc_html = f'&lt;p&gt;Mandalay Fold: {f["desc"]}&lt;/p&gt;&lt;p&gt;Math: {f["math"]}&lt;/p&gt;'
    
    return f'''<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>{internal}</class>
 <widget class="QWidget" name="{internal}">
  <property name="geometry">
   <rect><x>0</x><y>0</y><width>500</width><height>300</height></rect>
  </property>
  <layout class="QVBoxLayout" name="verticalLayout">
   <item>
    <widget class="QGroupBox" name="groupBox_main">
     <property name="title"><string>{combo}</string></property>
     <layout class="QVBoxLayout" name="vLayout_main">
      <item>
       <widget class="QLabel" name="label_info">
        <property name="text"><string>{desc_html}</string></property>
        <property name="wordWrap"><bool>true</bool></property>
        <property name="textFormat"><enum>Qt::RichText</enum></property>
       </widget>
      </item>
      <item>
       <widget class="MyDoubleSpinBox" name="spinbox_{internal}_scale">
        <property name="objectName"><string>fractal_transform_common_scale08</string></property>
        <property name="minimum"><double>-10.0</double></property>
        <property name="maximum"><double>10.0</double></property>
        <property name="singleStep"><double>0.01</double></property>
        <property name="value"><double>0.8</double></property>
       </widget>
      </item>
     </layout>
    </widget>
   </item>
  </layout>
 </widget>
 <resources/>
 <connections/>
</ui>
'''


def main():
    md_path = "/home/ubuntu/attachments/969f652c-d72a-43cf-97ec-7ee55d82d82c/mandalay+fold+for+3x3lion.md"
    formulas = parse_formulas(md_path)
    print(f"Parsed {len(formulas)} Mandalay Fold formulas")
    
    if len(formulas) != 50:
        print(f"WARNING: Expected 50, got {len(formulas)}")
    
    # Check for duplicate filenames
    from collections import Counter
    name_counts = Counter(to_filename(f['name'], f['num']) for f in formulas)
    dups = {n for n, c in name_counts.items() if c > 1}
    if dups:
        print(f"WARNING: Duplicate filenames: {dups}")
    
    enum_entries = []
    class_entries = []
    list_entries = []
    
    for i, f in enumerate(formulas):
        enum_id = ENUM_START + i
        filename = to_filename(f['name'], f['num'])
        classname = to_class(f['name'], f['num'])
        enumname = to_enum(f['name'], f['num'])
        
        cpp_path = f"{DEF_DIR}/fractal_{filename}.cpp"
        with open(cpp_path, 'w') as fh:
            fh.write(gen_cpp(f, enum_id))
        
        cl_path = f"{CL_DIR}/{filename}.cl"
        with open(cl_path, 'w') as fh:
            fh.write(gen_cl(f, enum_id))
        
        ui_path = f"{UI_DIR}/{filename}.ui"
        with open(ui_path, 'w') as fh:
            fh.write(gen_ui(f))
        
        enum_entries.append(f"\t{enumname} = {enum_id},")
        class_entries.append(f"FRACTAL_CLASS({classname})")
        list_entries.append(f"\tfractalList->append(new {classname}());")
        
        if (i + 1) % 10 == 0:
            print(f"  Generated {i+1}/{len(formulas)} formulas...")
    
    with open("/tmp/mandalay_fold_enum.txt", 'w') as fh:
        fh.write("\n\t// Mandalay Fold V1-V50 formulas\n")
        fh.write("\n".join(enum_entries))
        fh.write("\n")
    
    with open("/tmp/mandalay_fold_class.txt", 'w') as fh:
        fh.write("\n// Mandalay Fold V1-V50 formulas\n")
        fh.write("\n".join(class_entries))
        fh.write("\n")
    
    with open("/tmp/mandalay_fold_list.txt", 'w') as fh:
        fh.write("\n\t// ---- Mandalay Fold V1-V50 formulas ----\n")
        fh.write("\n".join(list_entries))
        fh.write("\n")
    
    print(f"\nGenerated {len(formulas)} Mandalay Fold formulas:")
    print(f"  - {len(formulas)} .cpp files")
    print(f"  - {len(formulas)} .cl files")
    print(f"  - {len(formulas)} .ui files")


if __name__ == "__main__":
    main()

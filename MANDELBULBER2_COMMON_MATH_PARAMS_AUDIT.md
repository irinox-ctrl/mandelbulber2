# MANDELBULBER2 COMMON MATH & PARAMS: Developer Guide

**Datum**: 2026-04-22  
**Bestanden**: `common_math.h/cpp`, `common_params.hpp`  
**Scope**: Math utilities, SDF operators, interpolation, PRNG, reflection/refraction, hypercomplex ops, common parameter structs  
**Focus**: Developer guide — math derivations, how to use, how to extend  

---

## 1. Smooth Minimum Operators (`common_math.h`)

### 1.1 `smoothMin` — Polynomial Smooth Minimum

From Inigo Quilez:

$$h = \frac{\max(k - |a - b|, 0)}{k}$$

$$\text{smoothMin}(a, b, k) = \min(a, b) - \frac{h^3 \cdot k}{6}$$

**Properties**:
- When $|a - b| > k$: returns $min(a, b)$ (no blending)
- When $|a - b| < k$: smooth cubic transition
- $C^1$ continuous (first derivative is continuous)
- $C^2$ discontinuous at $|a - b| = k$

**Usage in renderer**: Blending between primitive SDFs (spheres, boxes) for organic shapes.

### 1.2 `opSmoothUnion` — Quadratic Smooth Union

Also from Inigo Quilez:

$$h = \text{clamp}\left(0.5 + 0.5 \cdot \frac{b - a}{k}, 0, 1\right)$$

$$\text{opSmoothUnion}(a, b, k) = \text{dmix}(b, a, h) - k \cdot h \cdot (1 - h)$$

**Properties**:
- Quadratic correction term $-k \cdot h \cdot (1-h)$ creates the "bulge" between shapes
- $C^1$ continuous everywhere
- Unlike `smoothMin`, this always blends — even when shapes are far apart

**When to use which?**
- `smoothMin` → Fast, only blends when shapes are close
- `opSmoothUnion` → Always blends, better for artistic SDF combinations

### 1.3 `dsmin` — Power-Mean Smooth Minimum

```cpp
dsmin(a, b, k) = pow((ta * tb) / (ta + tb), 1.0 / k)
where ta = pow(a, k), tb = pow(b, k)
```

**Properties**:
- When $k = 1$: harmonic mean-like behavior
- When $k \to \infty$: approaches $min(a, b)$
- Produces different visual character than polynomial smooth min

---

## 2. Reflection & Refraction

### 2.1 Reflection Vector

$$R = I - 2(N \cdot I)N$$

```cpp
CVector3 ReflectionVector(const CVector3 &normal, const CVector3 &incident) {
    return incident - normal * incident.Dot(normal) * 2.0;
}
```

**Assumption**: `normal` must be unit length. If not, the reflection direction is scaled.

### 2.2 Refraction Vector (Snell's Law)

$$\eta = \frac{n_1}{n_2}$$

$$\cos I = -N \cdot I$$

$$\sin^2 T = \eta^2 (1 - \cos^2 I)$$

If $\sin^2 T > 1$: **total internal reflection** → return zero vector

$$\cos T = \sqrt{1 - \sin^2 T}$$

$$T = \eta I + N(\eta \cos I - \cos T)$$

```cpp
CVector3 RefractVector(const CVector3 &normal, const CVector3 &incident, double n1, double n2) {
    const double n = n1 / n2;
    const double cosI = -normal.Dot(incident);
    const double sinT2 = n * n * (1.0 - cosI * cosI);
    if (sinT2 > 1.0) return CVector3(0.0, 0.0, 0.0);  // TIR
    const double cosT = sqrt(1.0 - sinT2);
    return incident * n + normal * (n * cosI - cosT);
}
```

### 2.3 Fresnel Reflectance

Schlick's approximation is **not** used here. Instead, the exact Fresnel equations:

$$r_{\perp} = \frac{n_1 \cos I - n_2 \cos T}{n_1 \cos I + n_2 \cos T}$$

$$r_{\parallel} = \frac{n_2 \cos I - n_1 \cos T}{n_2 \cos I + n_1 \cos T}$$

$$R = \frac{r_{\perp}^2 + r_{\parallel}^2}{2}$$

**Note**: This is the **unpolarized** reflectance (average of s and p polarizations).

---

## 3. Interpolation

### 3.1 Cubic Interpolation (Catmull-Rom)

```cpp
float cubicInterpolate(float p[4], float x) {
    return p[1]
        + 0.5f * x
            * (p[2] - p[0]
                + x * (2.0f * p[0] - 5.0f * p[1] + 4.0f * p[2] - p[3]
                    + x * (3.0f * (p[1] - p[2]) + p[3] - p[0])));
}
```

**Input**: 4 control points $p_0, p_1, p_2, p_3$ and interpolation factor $x \in [0, 1]$  
**Output**: Interpolated value between $p_1$ and $p_2$

This is the **Catmull-Rom spline** evaluated in Horner form. The polynomial is:

$$y = 0.5 \cdot \begin{bmatrix} 1 & x & x^2 & x^3 \end{bmatrix} \cdot \begin{bmatrix} 0 & 2 & 0 & 0 \\ -1 & 0 & 1 & 0 \\ 2 & -5 & 4 & -1 \\ -1 & 3 & -3 & 1 \end{bmatrix} \cdot \begin{bmatrix} p_0 \\ p_1 \\ p_2 \\ p_3 \end{bmatrix}$$

### 3.2 Bicubic Interpolation

```cpp
float bicubicInterpolate(float p[4][4], float x, float y) {
    float yy[4];
    yy[0] = cubicInterpolate(p[0], y);
    yy[1] = cubicInterpolate(p[1], y);
    yy[2] = cubicInterpolate(p[2], y);
    yy[3] = cubicInterpolate(p[3], y);
    return cubicInterpolate(yy, x);
}
```

**Input**: 4×4 grid of samples, 2D interpolation factors $(x, y)$  
**Approach**: Separable — first interpolate 4 rows in $y$, then interpolate the 4 results in $x$

**Usage**: Texture sampling with higher quality than bilinear.

---

## 4. Random Number Generator

### 4.1 Park-Miller Generator (Carta 1990)

A **division-free** implementation of the Park-Miller PRNG:

$$X_{n+1} = (16807 \cdot X_n) \mod (2^{31} - 1)$$

The clever bit manipulation avoids the expensive modulo operation:

```cpp
unsigned int lo = 16807 * (gRandomSeed & 0xFFFF);
unsigned int hi = 16807 * (gRandomSeed >> 16);
lo += (hi & 0x7FFF) << 16;
hi >>= 15;
lo += hi;
if (lo > 2147483647) lo -= 2147483647;
return (int)(gRandomSeed = lo);
```

**Period**: $2^{31} - 2 \approx 2.1 \times 10^9$  
**Quality**: Low — Park-Miller fails modern randomness tests. Use only for visual noise, not cryptography.¹

### 4.2 `Random(int max)`

```cpp
int Random(int max) {
    return RandomInt() % (max + 1);
}
```

Returns uniform integer in $[0, \text{max}]$.  
**Note**: The modulo operation introduces **modulo bias** when $2^{31} - 1$ is not divisible by `max + 1`.²

---

## 5. Vector Utilities

### 5.1 `SmoothCVector` — Smooth Vector Transition

```cpp
template <typename T>
T SmoothCVector(const T &v1, const T &v2, double k) {
    if (k <= 0.0) return v1;
    if (k >= 1.0) return v2;
    
    double length1 = v1.Length();
    double length2 = v2.Length();
    double lenInterp = length1 * (1-k) + length2 * k;  // Interpolate magnitude
    
    T vTemp = v1 * (1-k) + v2 * k;  // Linear interpolation
    double lengthTemp = vTemp.Length();
    
    if (lengthTemp > 0.0)
        return (vTemp / lengthTemp) * lenInterp;  // Normalize + rescale
    else
        return v1;
}
```

**What it does**: Interpolates between two vectors while preserving a smooth **magnitude transition**. Unlike simple lerp (which can shrink magnitude in the middle), this:
1. Interpolates direction via linear lerp + normalize
2. Interpolates magnitude separately
3. Recombines

**Instantiated for**: `CVector2<double>`, `CVector3`, `CVector4`

### 5.2 `wrap` — 3D Modulo

```cpp
CVector3 wrap(CVector3 x, const CVector3 &a, const CVector3 &s) {
    x -= s;
    CVector3 out(
        x.x - a.x * floor(x.x / a.x) + s.x,
        x.y - a.y * floor(x.y / a.y) + s.y,
        x.z - a.z * floor(x.z / a.z) + s.z);
    return out;
}
```

**What it does**: Wraps $x$ into the periodic domain $[s, s+a)$.

**Formula per axis**: $out = x - a \cdot \lfloor x/a \rfloor + s$

**Usage**: Domain repetition in fractal formulas.

### 5.3 `MagicRound` — Adaptive Rounding

```cpp
double MagicRound(double val, double maxError) {
    double multiplier = pow(10.0, -int(log10(fabs(val))));
    double rounded = round(val * multiplier);
    
    // Iteratively refine until relative error < maxError
    // Try: rounded, rounded±0.5, rounded±0.25
    // If none work: multiplier *= 10 and retry
}
```

**Purpose**: Rounds a floating-point number to the "nicest" decimal representation within an error tolerance. Useful for displaying parameters or generating clean settings files.

**Example**: `MagicRound(3.14159265, 0.01)` → `3.14`  
`MagicRound(3.14159265, 0.0001)` → `3.1416`

---

## 6. Hypercomplex Operations

### 6.1 `hypercomplex_pow_constant`

Raises a 3D vector to an integer power using **spherical coordinates**:

$$r = \sqrt{x^2 + y^2 + z^2}$$
$$\theta = \text{atan2}(\sqrt{x^2 + y^2}, z)$$
$$\phi = \text{atan2}(y, x)$$

$$new_x = r^n \cdot \sin(n\theta) \cdot \cos(n\phi)$$
$$new_y = r^n \cdot \sin(n\theta) \cdot \sin(n\phi)$$
$$new_z = r^n \cdot \cos(n\theta)$$

**Note**: The $w$ component is passed through unchanged. This is used in 4D fractal formulas where $(x, y, z)$ is the "hypercomplex" part and $w$ is a separate coordinate.

**Relationship to standard 3D power**: This is equivalent to the spherical Mandelbulb power operator. For $n=2$:
- Standard: $(x, y, z)^2 = (x^2 - y^2 - z^2, 2xy, 2xz)$
- Hypercomplex: Uses spherical wrapping

These are **not the same** — the hypercomplex version produces different (often more symmetric) fractals.

---

## 7. Common Parameters (`common_params.hpp`)

### 7.1 `sCommonParams` — The Universal Fractal Parameter Struct

This struct contains **all parameters shared across fractal formulas**. It's passed to every fractal iteration function via `sFractalIn`.

**Key sections**:

| Section | Fields | Purpose |
|---------|--------|---------|
| Iteration control | `iterThreshMode` | Stop iteration based on threshold vs maxiter |
| Fake lights | `fakeLights*`, `fakeLightsOrbitTrapShape` | Orbit trap-based lighting system |
| Positioning | `fractalPosition`, `fractalRotation`, `repeat` | Transform before iteration |
| Foldings | `sFractalFoldings` | TGlad's box fold + spherical fold |
| Rotation matrices | `mRotFractalRotation`, `mRotFakeLightsRotation` | Pre-computed rotation matrices |

### 7.2 Fake Lights System

The fake lights system uses **orbit traps** to create artificial light sources:

```cpp
params::enumFakeLightsShape fakeLightsOrbitTrapShape;  // 106 shapes!
CVector3 fakeLightsOrbitTrap;                           // Trap center
params::enumFakeLightsPositionMode fakeLightsPositionMode; // 7 modes
```

**Position modes**:
| Mode | Meaning |
|------|---------|
| `fakeLightsPositionWorld` | Fixed in world space |
| `fakeLightsPositionCamera` | Follows camera |
| `fakeLightsPositionTarget` | At camera target |
| `fakeLightsPositionFractalCenter` | At fractal origin |
| `fakeLightsPositionPathCircle` | Circular path |
| `fakeLightsPositionPathSpiral` | Spiral path |
| `fakeLightsPositionOrbitTarget` | Orbit trap target |

**Shape list**: 106 shapes ranging from simple (point, line, circle) to complex (Mandelbrot2D, Julia3D, gyroid, Schwarz P/D surfaces, superformula, etc.).³

**Decay functions**:
| Enum | Formula |
|------|---------|
| `fakeLightsDecay1R2` | $1/r^2$ (physically correct) |
| `fakeLightsDecay1R` | $1/r$ |
| `fakeLightsDecay1R3` | $1/r^3$ |
| `fakeLightsDecayLinear` | Linear falloff |
| `fakeLightsDecayExp` | Exponential falloff |

### 7.3 Fractal Foldings

```cpp
struct sFractalFoldings {
    double boxLimit;
    double boxValue;
    double sphericalOuter;
    double sphericalInner;
    bool boxEnable;
    bool sphericalEnable;
};
```

**Box folding** (TGlad's):
```
if (x > boxLimit) x = boxValue - x;
else if (x < -boxLimit) x = -boxValue - x;
```

**Spherical folding**:
```
r = |point|
if (r < sphericalInner) point *= sphericalOuter / (sphericalInner * sphericalInner)
else if (r < sphericalOuter) point *= sphericalOuter / (r * r)
```

These are the **standard folding operations** used in Mandelbox and related fractals.

---

## 8. Footnotes: Known Issues

¹ **Park-Miller PRNG is outdated.** It has known statistical flaws (spectral test failure in high dimensions, short period). For visual noise it's fine, but for Monte Carlo integration or scientific use, consider replacing with `std::mt19937`.

² **`Random(int max)` has modulo bias.** When `max + 1` doesn't divide $2^{31} - 1$ evenly, lower values are slightly more likely. For `max = 1000`, the bias is ~0.05% — negligible for graphics, but measurable.

³ **`enumFakeLightsShape` has 106 values.** This is an enormous enum. Many shapes may not be fully implemented or tested. Adding a new shape requires updates in multiple files (orbit trap distance calculation, UI widget, settings serialization).

⁴ **`MagicRound` can infinite-loop if `val = 0`.** The `qIsNull(val)` check handles exact zero, but subnormal values (e.g., $10^{-320}$) may cause `log10(fabs(val))` to underflow to $-\infty$, making `multiplier = \infty$.

⁵ **`sCommonParams` has mixed initialization styles.** Some fields use C++11 default member initializers (`= 1.0`, `= false`), but others rely on POD zero-initialization. If the struct is default-constructed on the stack, uninitialized fields may contain garbage.

⁶ **`CheckNAN` uses `gsl_finite`**. If the project is compiled without GSL, this function won't compile. Consider using `std::isfinite` from `<cmath>` for C++11 portability.

⁷ **`MAX` and `MIN` are C-style macros.** They evaluate arguments twice and have no type safety. Prefer `std::max` / `std::min` or `qMax` / `qMin`.

⁸ **`dMax` and `dMin` only handle exactly 3 arguments.** There's no variadic version. For 2 arguments, use `std::max`. For 4+, you need nested calls.

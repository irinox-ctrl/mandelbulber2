# MANDELBULBER2 COMPUTE FRACTAL: Developer Guide

**Datum**: 2026-04-22  
**Bestanden**: `compute_fractal.hpp`, `compute_fractal.cpp`  
**Scope**: Core fractal iteration engine — the beating heart of Mandelbulber  
**Focus**: Template-based multi-mode computation pipeline, orbit traps, DE formulas, and known issues  

---

## 1. Architectural Overview

`Compute<Mode>()` is a **single templated function** that handles ALL fractal computation modes. The template parameter `Mode` (from `enumCalculationMode`) determines which code paths are active at compile time:

```cpp
enum enumCalculationMode {
    calcModeNormal = 0,       // Analytic DE for ray marching
    calcModeColouring = 1,    // Color index computation
    calcModeFake_AO = 2,      // Ambient occlusion (unused in CPU path)
    calcModeDeltaDE1 = 3,     // Delta DE — reference point
    calcModeDeltaDE2 = 4,     // Delta DE — offset point
    calcModeOrbitTrap = 5,    // Fake lights / orbit traps
    calcModeCubeOrbitTrap = 6,// Texture fractalization
    calcModeSphereOrbitTrap = 7 // Sphere-based texture fractalization
};
```

**Key insight**: The template is NOT fully specialized — it's one function with `if (Mode == ...)` branches. The compiler can optimize away dead branches, but all code is compiled into each instantiation. This is why there are explicit template instantiations at the bottom of `compute_fractal.cpp` for all 8 modes (well, 6 are instantiated; `calcModeFake_AO` and `calcModeSphereOrbitTrap` are missing).

---

## 2. Data Flow

```
sFractalIn                    sFractalOut
  ├── point  ──►  Transform  ──►  z (CVector4)
  ├── common    │                ├── distance (DE)
  ├── material  │                ├── colorIndex
  ├── minN      │                ├── orbitTrapR
  └── ...       │                ├── iters
                │                ├── maxiter
                │                └── z (final position)
                ▼
         Main Iteration Loop
                │
    ┌───────────┼───────────┐
    ▼           ▼           ▼
  Folding    Formula    Escape Check
    │           │           │
    └───────────┴───────────┘
                │
         Final Calculations
                │
           sFractalOut
```

### 2.1 Input: `sFractalIn`

| Field | Meaning |
|-------|---------|
| `point` | 3D world-space position to evaluate |
| `minN` | Minimum iteration (not used in Compute, but passed through) |
| `forcedMaxiter` | Override max iterations (-1 = use formula default) |
| `maxiterMultiplier` | Scale factor for formula maxiter |
| `orbitTrapIndex` | Which orbit trap color channel (0, 1, 2) |
| `common` | Pointer to `sCommonParams` (shared fractal settings) |
| `forcedFormulaIndex` | Use only this formula (-1 = hybrid sequence) |
| `normalCalculationMode` | Flag for normal computation (unused in Compute!) |
| `material` | Material properties for coloring |

### 2.2 Output: `sFractalOut`

| Field | Meaning |
|-------|---------|
| `z` | Final orbit position (3D) |
| `normal` | Fractal normal (for sphere orbit trap) |
| `distance` | Signed distance estimate |
| `colorIndex` | Color value (0-1000+) |
| `fakeAO` | Ambient occlusion estimate |
| `orbitTrapR` | Accumulated orbit trap intensity |
| `iters` | Number of iterations performed |
| `maxiter` | True if hit iteration limit |
| `orbitTrapMinIter` | Iteration with closest orbit trap approach |
| `orbitTrapCenterIndex` | Which multi-center was closest |
| `orbitSamples[4]` | Snapshots at evenly-spaced iterations |
| `orbitSampleIters[4]` | Iteration numbers for snapshots |
| `orbitSampleCount` | Valid samples (0-4) |

---

## 3. The Main Loop — Step by Step

### 3.1 Point Transformation (Lines 54-56)

```cpp
CVector3 pointTransformed = in.point - in.common->fractalPosition;
pointTransformed = in.common->mRotFractalRotation.RotateVector(pointTransformed);
pointTransformed = pointTransformed.repeatMod(in.common->repeat);
```

**Order matters**: Translate → Rotate → Repeat (modulo). This is standard 3D transformation pipeline.

**Note**: `repeatMod` is NOT in the standard library — it's a custom method on `CVector3` that does component-wise modulo: `x = x - period * floor(x / period)`.

### 3.2 W-Axis Initialization (Lines 62-69)

```cpp
if (in.forcedFormulaIndex >= 0)
    z.w = fractals.GetInitialWAxis(in.forcedFormulaIndex);
else
    z.w = fractals.GetInitialWAxis(0);
```

The 4th dimension (w) is initialized from the formula's preference. Some formulas (like quaternion or 4D variants) need a non-zero w.

### 3.3 Auxiliary State (`sExtendedAux`)

The `aux` struct carries state through iterations:

| Field | Initial Value | Purpose |
|-------|--------------|---------|
| `c` | `z` | Variable c (changes in some formulas) |
| `const_c` | `z` | Constant c (the original point) |
| `old_z` | `z` | Previous z (for hybrid color2) |
| `r` | `z.Length()` | Current radius |
| `DE` | `1.0` | Running derivative estimate |
| `DE0` | `0.0` | DIFS distance accumulator |
| `dist` | `1000.0` | DIFS distance |
| `pseudoKleinianDE` | `1.0` | Pseudo-Kleinian DE helper |
| `actualScale` | Mandelbox scale | For variable-scale Mandelbox |
| `color` | `1.0` | Running color accumulator |
| `colorHybrid` | `0.0` | Hybrid color accumulator |
| `temp1000` | `1000.0` | Hybrid color2 accumulator |

### 3.4 Iteration Sequence (Lines 167-183)

For **hybrid fractals**, the sequence determines which formula to use at each iteration:

```cpp
if (in.forcedFormulaIndex >= 0)
    sequence = in.forcedFormulaIndex;
else if (seq)
    sequence = seq->GetSequence(i);      // Per-ray sequence
else
    sequence = fractals.GetSequence(i);  // Global sequence
```

**The FIXME comment** (line 175-177) notes that `GetSequence(i)` returns `objectID` instead of sequence index — this is a known workaround.

### 3.5 Foldings (Lines 186-196)

Box folding and spherical folding are applied **before** the formula each iteration:

```cpp
if (in.common->foldings.boxEnable)
    BoxFolding(z, &in.common->foldings, aux);
if (in.common->foldings.sphericalEnable)
    SphericalFolding(z, &in.common->foldings, aux);
```

After each folding, `aux.r = z.Length()` is recomputed.

### 3.6 Formula Execution (Lines 208-226)

```cpp
fractalFormulaFunction = fractals.GetFractalFormulaFunction(sequence);

if (!fractals.IsHybrid() || fractals.GetWeight(sequence) > 0.0) {
    if (fractalFormulaFunction && formula != none) {
        fractalFormulaFunction->FormulaCode(z, fractal, aux);
    } else {
        // Fallback: high bailout = "escaped"
        z = CVector4(high, high, high, high);
        out->distance = 10.0;
        out->iters = 1;
        return;
    }
}
```

Formulas are called via **virtual function dispatch** (`FormulaCode`). Each fractal formula is a subclass of `cAbstractFractal`.

### 3.7 Constant Addition (Julia vs Mandelbrot)

```cpp
if (fractals.IsAddCConstant(sequence)) {
    if (fractals.IsJuliaEnabled(sequence))
        z += CVector4(juliaConstant * multiplier, 0.0);
    else
        z += aux.const_c * multiplier;
}
```

**Special case**: `aboxMod1` and `amazingSurf` swap x and y when adding the constant:
```cpp
z += CVector4(juliaC.y, juliaC.x, juliaC.z, 0.0);  // x↔y swap!
```

### 3.8 Hybrid Weight Blending (Lines 268-278)

```cpp
if (fractals.IsHybrid()) {
    double k = fractals.GetWeight(sequence);
    if (k < 1.0) {
        z = SmoothCVector(tempZ, z, k);              // Direction + magnitude blend
        aux.DE = aux.DE * k + tempAuxDE * kn;        // Linear DE blend
        aux.color = aux.color * k + tempAuxColor * kn; // Linear color blend
    }
}
```

**Inconsistency**: `z` uses `SmoothCVector` (which preserves magnitude interpolation), but `DE` and `color` use simple linear interpolation. This is likely intentional — geometric blending needs magnitude preservation, but derivative and color can blend linearly.

---

## 4. Escape Conditions Per Mode

### 4.1 `calcModeNormal` / `calcModeDeltaDE1`

```cpp
if (aux.r > bailout) {
    out->maxiter = false;
    break;
}
if (UseAdditionalBailoutCond) {
    out->maxiter = false;  // Must be false for pseudo kleinian
    if ((z - lastZ).Length() / aux.r < 0.1 / bailout) break;    // Converged?
    if ((z - lastLastZ).Length() / aux.r < 0.1 / bailout) break; // Stuck?
}
```

**The convergence check**: If the orbit stops moving relative to its radius, we assume convergence (interior point).

**BUG ALERT**: See §7.1 — `lastLastZ` is incorrectly initialized, making the second check redundant.

### 4.2 `calcModeDeltaDE2`

```cpp
if (i == maxN) break;
```

Always runs to max iterations. Used as the "offset" point in delta DE computation.

### 4.3 `calcModeColouring`

Uses a `colorMin` accumulator to track the minimum distance to a coloring feature:

```cpp
double len;  // Distance to coloring feature
switch (coloringAlgorithm) {
    case fractalColoring_Standard:   len = colorZ.Length(); break;
    case fractalColoring_ZDotPoint:  len = fabs(colorZ.Dot(point)); break;
    case fractalColoring_Sphere:     len = fabs(|colorZ - point| - sphereRadius); break;
    case fractalColoring_Cross:      len = min(|x|, |y|, |z|); break;
    case fractalColoring_Line:       len = fabs(colorZ.Dot(lineDir)); break;
    case fractalColoring_None:       len = aux.r; break;
}
if (len < colorMin) colorMin = len;
```

**Mandelbox special case**: For the Mandelbox formula with standard coloring, the bailout logic is different — it uses a hardcoded `1e15` threshold instead of the formula's bailout.

### 4.4 `calcModeOrbitTrap` (Fake Lights)

This is the most complex mode. It evaluates orbit trap shapes at each iteration:

```cpp
// Determine trap center
if (autoTrapCenterSet)
    trapPoint = z - autoTrapCenter;      // Auto-center at specific iteration
else if (in.common->fakeLightsRelativeCenter)
    trapPoint = z - aux.const_c;         // Relative to starting point
else
    trapPoint = z;                        // Absolute position

// Evaluate distance to trap shape
distance = OrbitTrapShapeDistance(trapPoint, in.common);

// Accumulate light contribution within [minIter, maxIter]
if (i >= fakeLightsMinIter && i <= fakeLightsMaxIter) {
    orbitTrapTotal += DecayFunction(distance);
}

// Bailout when distance exceeds formula bailout
if (distance > bailout) {
    out->orbitTrapR = orbitTrapTotal;
    break;
}
```

**Multi-center support**: Up to 4 trap centers with individual weights:
```cpp
for (int mc = 0; mc < 4; mc++) {
    CVector4 shiftedPoint = trapPoint
        - CVector4(multiCenter[mc], 0.0)
        + CVector4(fakeLightsOrbitTrap, 0.0);
    double d = OrbitTrapShapeDistance(shiftedPoint, common);
    d /= multiCenterWeight[mc];
    // Take minimum weighted distance
}
```

### 4.5 `calcModeCubeOrbitTrap` (Texture Fractalization)

Uses geometric shapes as "texture traps" for procedurally textured surfaces:

```cpp
if (i >= textureFractalizeStartIteration) {
    CVector3 zz = z.GetXYZ() - trapCenter;
    bool trapHit = false;
    
    switch (textureFractalizeShape) {
        case Cube:    trapHit = |zz.x| < size && |zz.y| < size && |zz.z| < size; break;
        case Sphere:  trapHit = |zz| < size; break;
        case Cross:   trapHit = min(|x|,|y|,|z|) < size; break;
        case Line:    trapHit = sqrt(x²+y²) < size; break;
        case Plane:   trapHit = |z| < size; break;
    }
    
    if (trapHit) {
        // Sigmoid weight based on SDF distance
        double weight = 1.0 / (1.0 + exp(dist / softness));
        out->colorIndex = (|dist| / size) * 100.0;
        
        if (!textureFractalizeIterationBlend) return;  // Immediate return
        // else: continue, last hit wins
    }
}
```

---

## 5. Distance Estimation (DE) Formulas

After the loop, for `calcModeNormal`:

### 5.1 Hybrid Mode DE

```cpp
if (fractals.IsHybrid()) {
    switch (GetDEFunctionType(0)) {
        case linearDEFunction:     distance = (r - offset) / DE; break;
        case logarithmicDEFunction: distance = 0.5 * r * log(r) / DE; break;
        case pseudoKleinianDEFunction:
            distance = max(rxy - pseudoKleinianDE, |rxy * z.z| / r) / DE; break;
        case josKleinianDEFunction:
            distance = min(z.y, tweak005) / max(DE, offset1); break;
        case customDEFunction:     distance = aux.dist; break;
        case maxAxisDEFunction:    distance = max(|x|,|y|,|z|) / DE; break;
    }
}
```

**Note**: In hybrid mode, only `GetDEFunctionType(0)` is used — the DE type of the **first** formula determines the DE for the entire hybrid. This is a significant limitation.

### 5.2 Non-Hybrid Mode DE

```cpp
switch (GetDEAnalyticFunction(sequence)) {
    case analyticFunctionLogarithmic: distance = 0.5 * r * log(r) / DE; break;
    case analyticFunctionLinear:      distance = r / DE; break;
    case analyticFunctionIFS:         distance = (r - 2.0) / DE; break;
    case analyticFunctionPseudoKleinian: ... break;
    case analyticFunctionJosKleinian: ... break;
    case analyticFunctionCustomDE:    distance = aux.dist; break;
    case analyticFunctionMaxAxis:     distance = max(|x|,|y|,|z|) / DE; break;
    case analyticFunctionNone:        distance = -1.0; break;
    case analyticFunctionUndefined:   distance = aux.r; break;
}
```

### 5.3 DE Formula Derivations

**Linear DE**: $d = r / DE$  
Where $DE = |dz/dc|$ — the running derivative magnitude. For the Mandelbrot set: $z_{n+1} = z_n^2 + c$, so $dz/dc = 2z_n \cdot dz/dc + 1$.

**Logarithmic DE**: $d = 0.5 \cdot r \cdot \log(r) / DE$  
Derived from the potential function $\Phi(z) = \log|z| / 2^n$, giving distance estimate $d \approx |z| \cdot \log|z| / |z'|$.

**Pseudo-Kleinian DE**: 
$$d = \frac{\max(r_{xy} - pkDE, |r_{xy} \cdot z_z| / r)}{DE}$$
Where $r_{xy} = \sqrt{x^2 + y^2}$. This handles the cylindrical structure of pseudo-Kleinian fractals.

---

## 6. Color Index Calculation

For `calcModeColouring`:

```cpp
out->colorIndex = CalculateColorIndex(
    IsHybrid(), aux.r, z, colorMin, aux,
    material->fractalColoring, coloringFunction, defaultFractal);
```

The `colorMin` is the minimum distance to the coloring feature throughout the orbit. Different formulas use different coloring strategies:
- Standard: based on orbit length
- Orbit trap: based on minimum distance to trap
- Iteration count: based on escape speed
- Hybrid: weighted combination

---

## 7. Known Bugs and Issues

### BUG-1: `lastLastZ` is incorrectly assigned (CRITICAL)

**Location**: `compute_fractal.cpp`, lines 161-164

```cpp
lastGoodZ = lastZ;     // z_{i-1}
lastLastZ = lastZ;     // ALSO z_{i-1} ← BUG!
lastZ = z;             // z_i
```

**Problem**: Both `lastGoodZ` and `lastLastZ` receive the same value. The "additional bailout" check on line 311:
```cpp
if ((z - lastLastZ).Length() / aux.r < 0.1 / bailout) break;
```
is therefore **identical** to the check on line 307:
```cpp
if ((z - lastZ).Length() / aux.r < 0.1 / bailout) break;  // lastZ was updated to z_{i-1} at line 164
```

Wait — actually `lastZ` was updated at line 164 to `z` of the current iteration (before the formula is applied). So `(z - lastZ)` after formula execution is `(z_i - z_{i-1})`. And `(z - lastLastZ)` is also `(z_i - z_{i-1})` because `lastLastZ = lastZ = z_{i-1}`.

**Fix**: Change to:
```cpp
lastLastZ = lastGoodZ;  // z_{i-2}
lastGoodZ = lastZ;      // z_{i-1}
lastZ = z;              // z_i
```

**Impact**: The second convergence check is currently redundant. Fixing it would add an additional "stuck for 2 iterations" bailout condition, potentially reducing iteration count for convergent orbits.

### BUG-2: NaN handling inconsistency

**Location**: Lines 285-291 and 609-613

```cpp
// First check (after formula + constant + blend)
if (z.IsNotANumber()) {
    z = lastZ;           // Restore to z_{i-1}
    aux.r = z.Length();
    out->maxiter = true;
    break;
}

// Second check (after escape conditions)
if (z.IsNotANumber()) {
    z = lastGoodZ;       // Restore to z_{i-2} (or z_{i-1} due to BUG-1)
    break;
}
```

**Problem**: Two NaN checks with different restore targets. The first restores to `lastZ` (previous iteration), the second to `lastGoodZ` (two iterations ago, or one due to BUG-1). This is inconsistent and confusing. Also, the second check never sets `out->maxiter = true`.

### BUG-3: `out->maxiter` not set in second NaN path

If NaN is detected at line 609, the loop breaks but `out->maxiter` retains its default `true` value. This happens to be correct by accident, but it's not explicit.

### BUG-4: `normalCalculationMode` is unused

`sFractalIn` has a `normalCalculationMode` field that is stored but never read in `Compute()`. It might be used by formula subclasses, but within `Compute()` it's dead weight.

### RISK-1: Missing template instantiations

Only 6 of 8 modes are explicitly instantiated:
```cpp
template void Compute<calcModeNormal>;
template void Compute<calcModeDeltaDE1>;
template void Compute<calcModeDeltaDE2>;
template void Compute<calcModeColouring>;
template void Compute<calcModeOrbitTrap>;
template void Compute<calcModeCubeOrbitTrap>;
// MISSING: calcModeFake_AO, calcModeSphereOrbitTrap
```

These might be instantiated elsewhere, or they might not be used in the CPU path.

### RISK-2: Hardcoded bailout scaling

```cpp
double high = fractals.GetBailout(sequence) * 10.0;
z = CVector4(high, high, high, high);
```

When a formula is missing, the fallback sets z to 10× bailout. This is arbitrary and might not work well for all formulas.

### RISK-3: `colorMin` magic number

```cpp
double colorMin = 1000.0;
```

This arbitrary initial value assumes no coloring feature will be further than 1000 units away. For very large fractals, this could be insufficient.

### RISK-4: Orbit trap bailout behavior

In `calcModeOrbitTrap`, `out->orbitTrapR` is only set when `distance > bailout`:
```cpp
if (distance > bailout) {
    out->orbitTrapR = orbitTrapTotal;
    break;
}
```

If the orbit never exceeds bailout (e.g., interior points), `orbitTrapR` remains at its initial value of `0.0`. This means interior points contribute **no** fake light, which may or may not be desired.

### RISK-5: Hybrid DE always uses formula 0

```cpp
if (fractals.GetDEFunctionType(0) == fractal::linearDEFunction)
```

In hybrid mode, the DE type is always taken from formula index 0, regardless of which formula is active in the sequence. This means combining a logarithmic DE formula with a linear DE formula in a hybrid will produce incorrect distance estimates.

---

## 8. Extension Guide

### Adding a New Calculation Mode

1. Add enum value to `enumCalculationMode` in `calculation_mode.h`
2. Add escape condition branch in `compute_fractal.cpp` (around line 294)
3. Add final calculation branch (around line 617)
4. Add explicit template instantiation at bottom of file
5. Update any dispatchers that select the mode (e.g., `calculate_distance.cpp`)

### Adding a New DE Formula

1. Add enum value to `enumAnalyticDEFunction` (in formula headers)
2. Add case to both hybrid (line 623) and non-hybrid (line 662) switch statements
3. The formula itself must update `aux.DE` during iteration

### Adding a New Orbit Trap Shape

See `orbit_trap_shape.hpp/cpp`. The shape distance function must:
1. Accept a `CVector4` point and `sCommonParams*`
2. Return a non-negative double (distance to shape surface)
3. Handle the `fakeLightsOrbitTrap` offset internally

### Adding Multi-Center Support to New Features

The multi-center pattern is:
```cpp
if (fakeLightsMultiCenterEnabled) {
    double minDist = 1e30;
    for (int mc = 0; mc < 4; mc++) {
        if (weight[mc] <= 0.0) continue;
        CVector4 shifted = point - CVector4(center[mc], 0.0) + CVector4(trap, 0.0);
        double d = ShapeDistance(shifted, params) / weight[mc];
        if (d < minDist) { minDist = d; minIndex = mc; }
    }
} else {
    minDist = ShapeDistance(point, params);
}
```

---

## 9. Performance Notes

### Hot Path Profile (estimated)

The main loop is the hottest code in the entire renderer:

```
for (i = 0; i < maxN; i++) {          // maxN typically 50-500
    // ~10-20 operations per iteration
    BoxFolding();                      // Conditional
    SphericalFolding();                // Conditional
    FormulaCode(z, fractal, aux);      // Virtual dispatch + formula logic
    // Constant addition
    // Hybrid blending
    // Escape checks
}
```

**Virtual dispatch cost**: `fractalFormulaFunction->FormulaCode()` is a virtual call. In a tight loop with 500 iterations and millions of pixels, this adds up. However, the formula logic itself dominates.

**Template optimization**: Because `Compute()` is templated on `Mode`, the compiler can eliminate all branches for other modes. This is crucial for performance — the orbit trap code (which calls `OrbitTrapShapeDistance()`) is completely removed from `calcModeNormal` instantiations.

**Cache considerations**: `sFractal` is a large struct (~5KB). Accessing `fractals.GetFractal(sequence)` per iteration could cause cache misses if the fractal data doesn't fit in L1. In practice, the same fractal is used for many consecutive iterations, so this is usually fine.

---

## 10. Summary

`compute_fractal.cpp` is the **central dispatch hub** of Mandelbulber's fractal engine. It orchestrates:
- Point transformation (translate/rotate/repeat)
- Iteration with folding
- Formula execution via virtual dispatch
- Mode-specific escape conditions
- Final DE or color computation

**Critical bug**: `lastLastZ` initialization is broken, making the secondary convergence check redundant.

**Key design tension**: The hybrid system blends formulas but uses a single DE type (from formula 0), which limits the correctness of distance estimates for mixed-formula hybrids.

# Formula Weight System — Architecture & Fix Documentation

## Document Purpose
This document captures the complete architecture of the formula weight system (hybrid iterative blending), the issues found, and fixes applied. Use this as reference for future implementations.

---

## 1. System Overview

The formula weight system allows per-formula blending in hybrid mode. Each formula slot (1-9) has a `formula_weight` parameter [0.0, 1.0] that controls how much of that formula's result is applied per iteration.

- **weight = 1.0** (default): Formula has full effect (no blending)
- **weight = 0.0**: Formula is completely skipped (no computation)
- **weight = 0.5**: 50% blend between pre-formula state and post-formula state

**Important:** The weight system ONLY activates in hybrid mode (`hybrid_fractal_enable = true`). In non-hybrid mode, weights have no effect.

---

## 2. Data Flow: Parameter → Rendering

```
UI (spinbox_formula_weight_N)
    ↓ SynchronizeInterfaceWindow
Parameter Container ("formula_weight", index N)
    ↓ cNineFractals constructor
formulaWeight[N-1] array (nine_fractals.hpp line 119)
    ↓ CopyToOpenclData()
GPU struct: sequence.formulaWeight[N-1]
    ↓ compute_fractal.cl / compute_fractal.cpp
Per-iteration weight blend
```

### Key Files

| File | Role |
|------|------|
| `src/initparameters.cpp:141` | Parameter definition: `formula_weight`, default 1.0, range [0,1] |
| `src/nine_fractals.cpp:75` | CPU loading: `formulaWeight[i] = generalPar->Get<double>("formula_weight", i+1)` |
| `src/nine_fractals.hpp:68` | Accessor: `GetWeight(int formulaIndex)` |
| `src/nine_fractals.cpp:478` | GPU transfer: `sequence->formulaWeight[i] = formulaWeight[i]` |
| `src/compute_fractal.cpp:217,275-292` | CPU weight logic |
| `opencl/engines/compute_fractal.cl:253,328-347` | GPU weight logic |
| `opencl/engines/nebula.cl:339,407-426` | Nebula engine weight logic |
| `src/opencl_engine_render_fractal.cpp:1037-1048` | `SetParametersForIterationWeight()` — enables `ITERATION_WEIGHT` define |
| `qt/tab_fractal.cpp:335-336` | UI widget visibility (only shown when hybrid enabled) |
| `qt/dock_fractal.cpp:319` | Hybrid checkbox toggles weight widget visibility |

---

## 3. Sequence Generation

In hybrid mode, `CreateSequence()` (nine_fractals.cpp:326) builds a lookup table mapping iteration index → formula index:

```
Iteration:  0  1  2  3  4  5  6  7  8  ...
Formula:    0  1  0  1  0  1  0  1  0  ...  (with formula_iterations=1 for both)
```

With `formula_iterations_1 = 3`:
```
Iteration:  0  1  2  3  4  5  6  7  8  ...
Formula:    0  0  0  1  0  0  0  1  0  ...
```

The sequence respects `formula_start_iteration`, `formula_stop_iteration`, and `repeat_from`.

---

## 4. Weight Application Logic (CPU)

```cpp
// 1. Save pre-formula state (ALL aux fields)
CVector4 tempZ = z;
double tempAuxDE = aux.DE;
double tempAuxDE0 = aux.DE0;
double tempAuxDist = aux.dist;
double tempAuxPseudoKleinianDE = aux.pseudoKleinianDE;
double tempAuxActualScale = aux.actualScale;
double tempAuxActualScaleA = aux.actualScaleA;
double tempAuxColor = aux.color;
double tempAuxColorHybrid = aux.colorHybrid;
double tempAuxTemp1000 = aux.temp1000;

// 2. Skip formula + C-constant if weight = 0
if (!fractals.IsHybrid() || fractals.GetWeight(sequence) > 0.0)
{
    formula->FormulaCode(z, fractal, aux);  // modifies z and aux
    // C-constant addition (now inside guard)
    if (fractals.IsAddCConstant(sequence)) { z += C; }
}

// 3. Blend ALL aux fields based on weight
if (fractals.IsHybrid())
{
    double k = fractals.GetWeight(sequence);
    if (k < 1.0)
    {
        z = SmoothCVector(tempZ, z, k);    // length-preserving spherical blend
        double kn = 1.0 - k;
        aux.DE = aux.DE * k + tempAuxDE * kn;
        aux.DE0 = aux.DE0 * k + tempAuxDE0 * kn;
        aux.dist = aux.dist * k + tempAuxDist * kn;
        aux.pseudoKleinianDE = aux.pseudoKleinianDE * k + tempAuxPseudoKleinianDE * kn;
        aux.actualScale = aux.actualScale * k + tempAuxActualScale * kn;
        aux.actualScaleA = aux.actualScaleA * k + tempAuxActualScaleA * kn;
        aux.color = aux.color * k + tempAuxColor * kn;
        aux.colorHybrid = aux.colorHybrid * k + tempAuxColorHybrid * kn;
        aux.temp1000 = aux.temp1000 * k + tempAuxTemp1000 * kn;
    }
}

// 4. Recalculate r from blended z
aux.r = z.Length();
```

---

## 5. SmoothCVector Function

The blend function preserves vector LENGTH while interpolating:

```cpp
T SmoothCVector(const T &v1, const T &v2, double k)
{
    double length1 = v1.Length();
    double length2 = v2.Length();
    double lenInterp = length1 * (1-k) + length2 * k;   // linear length interpolation
    T vTemp = v1 * (1-k) + v2 * k;                       // linear vector interpolation
    result = normalize(vTemp) * lenInterp;                // apply interpolated length
}
```

This prevents the "shrinking" that pure linear interpolation would cause when vectors point in different directions.

---

## 6. GPU (OpenCL) Implementation

The GPU uses preprocessor guards:

- **`#ifdef ITERATION_WEIGHT`**: Wraps the formula skip (weight=0) and blend logic
- **`ITERATION_WEIGHT`** is defined by `SetParametersForIterationWeight()` when ANY `formulaWeight[i] != 1.0`

When all weights are 1.0, the define is absent → no weight code compiled → maximum performance.

When weights change from 1.0, the kernel is recompiled with `ITERATION_WEIGHT` enabled.

---

## 7. Issues Found & Fixes Applied

### Issue 1: Incomplete aux blending (FIXED)
**Before:** Only `z`, `aux.DE`, and `aux.color` were blended by weight.
**Problem:** Formulas that modify `aux.DE0`, `aux.dist`, `aux.pseudoKleinianDE`, `aux.actualScale`, `aux.actualScaleA`, `aux.colorHybrid`, or `aux.temp1000` would have these values pass through UNBLENDED to subsequent iterations. This made the weight appear to have no effect for certain formula combinations (especially DIFS, pseudo-Kleinian, and mandelbox-type formulas).
**Fix:** All modifiable aux fields are now saved before the formula and blended after.

### Issue 2: C-constant outside weight guard (FIXED)
**Before:** C-constant addition ran unconditionally (even when weight=0), then the blend would undo it.
**Problem:** Wasted computation and potential edge cases with NaN when formula was skipped but C was added.
**Fix:** C-constant addition is now inside the weight>0 guard. When weight=0, neither formula nor C-constant runs.

### Issue 3: CPU/GPU/Nebula synchronization (FIXED)
**Before:** The three rendering paths had slightly different weight logic.
**Fix:** All three paths now have identical weight blending logic.

---

## 8. How to Test

1. Enable hybrid mode (checkbox "Enable hybrid fractals")
2. Set Formula 1: Menger Sponge
3. Set Formula 2: Mandelbulb (or any other)
4. Change `formula_weight_1` from 1.0 to 0.5
5. Expected: Fractal shape changes visibly (blend between Menger and "no formula" state)
6. Change `formula_weight_1` to 0.0
7. Expected: Only Formula 2 contributes (Menger is completely skipped)
8. Test on CPU, GPU FULL, GPU LIMITED — all should show the same behavior

---

## 9. Build Instructions

After pulling the fix:
```bash
cd mandelbulber2/qmake
make clean
qmake mandelbulber-opencl.pro
make -j$(nproc)
```

**IMPORTANT:** `make clean` is required because header changes (aux struct fields) affect all compilation units.

---

## 10. Relevant Commits

- `49cb3b9b7` — Original upstream fix: "Fixed problem with not working fractal weight function in analytic DE mode" (added DE+color blending)
- `7b6b5623a` — "Fixed bug causing noise in the coloring when iteration weight was <1"
- Current fix — Complete aux blending + C-constant guard + sync all engines

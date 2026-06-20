# Nuclear Analysis: Weight System × All Formula Types

## Formula Landscape (461 formulas total)

| Category | DEFunction | DEType | Count | Weight System Status |
|----------|-----------|--------|-------|---------------------|
| Logarithmic (Mandelbulb, etc.) | logarithmicDEFunction | analytic | 113 | ✓ `actualDE = 0.5 * r * log(r) / DE` |
| Linear (Mandelbox, ABox, Menger, IFS, etc.) | linearDEFunction | analytic | 89 | ✓ `actualDE = r / DE` |
| Custom DE (DIFS formulas + JK V3/V4 + Koch) | customDEFunction | analytic | 92 | ✗ **NOT HANDLED** — falls through to raw `aux.DE` |
| PseudoKleinian | pseudoKleinianDEFunction | analytic | 6 | ✓ Uses `aux.pseudoKleinianDE` |
| JosKleinian | josKleinianDEFunction | analytic | 2 | ⚠ Uses hardcoded 0.05/1.0 instead of fractal params |
| Transforms (no DE function) | withoutDEFunction | analytic | 158 | ✗ **NOT HANDLED** — transforms don't produce DE |
| DeltaDE formulas | various | delta | 14 | ✗ **NOT HANDLED** — no deltaDE path in weight calc |
| MaxAxis DE | maxAxisDEFunction | analytic | 0 | ✗ Enum exists but no formulas use it currently |

## Critical Problems Found

### Problem 1: Custom DE / DIFS formulas (92 formulas!) — COMPLETELY BROKEN
**DIFS formulas** (difs_box, difs_cylinder, difs_torus, difs_sphere, etc.) and **DIFS transforms** (transf_difs_box, transf_difs_cylinder, etc.) output their distance estimate via `aux.dist`, NOT via `aux.DE`.

The analytic DE formula for customDEFunction is simply:
```cpp
case analyticFunctionCustomDE: out->distance = aux.dist; break;
```

But the weight system's actualDE computation completely ignores `aux.dist`:
```cpp
// Current code — MISSING customDEFunction case!
if (deFunc == pseudoKleinianDEFunction) { ... }
else if (deFunc == josKleinianDEFunction) { ... }
else if (deFunc == logarithmicDEFunction) { ... }
else if (deFunc == linearDEFunction) { ... }
// customDEFunction: falls through → actualDE = aux.DE (WRONG!)
```

**Impact:** DE-based, Conditional, OrbitTrap, and Curve weight modes are broken for:
- ALL 14 DIFS formulas
- ALL 48 DIFS transforms
- JosKleinian V3, V4, Koch formulas, Octahedron, MengerV2/V3/V6/V7, etc.
- Total: **92 formulas**

### Problem 2: Transforms (158 formulas) — NO WEIGHT STRATEGY
Transforms (`transf_*`) have `DEFunctionType = withoutDEFunction`. They don't produce a distance estimate at all — they modify z and aux.DE for the NEXT formula in the hybrid chain.

Current weight system treats them like any formula, but:
- DE-based weight mode is meaningless for transforms (they don't have a DE)
- OrbitTrap weight mode doesn't account for transforms not being orbit traps
- Only Iteration, Static, and ZLength modes make sense for transforms

**Missing:** A "transform-aware" weight mode that recognizes transforms modify geometry, not distance.

### Problem 3: JosKleinian hardcoded values
```cpp
// Current (WRONG)
actualDE = min(z.y, 0.05) / max(aux.DE, 1.0);

// Should be (using fractal's actual parameters)
actualDE = min(z.y, fractal->analyticDE.tweak005) / max(aux.DE, fractal->analyticDE.offset1);
```

### Problem 4: DeltaDE formulas (14 formulas) — NO actualDE computation
DeltaDE formulas compute distance via numerical differentiation. The weight system's actualDE computation only handles analytic DE functions. For deltaDE formulas, the weight system falls through to raw `aux.DE` which is the derivative accumulator, not the actual distance estimate.

### Problem 5: IFS/linear DE formula diversity not accounted for
Linear DE formulas include very different geometry types:
- **Mandelbox** (scale-based folding)
- **Menger sponge** (subtractive fractal)
- **ABox** variants (additive folding)
- **Sierpinski** (tetrahedron IFS)
- **KaleidoscopicIFS** (rotational symmetry)

All use `actualDE = r / DE` but the blending behavior should be different. A Mandelbox and a Menger sponge respond very differently to weight changes because their DE derivatives behave differently.

### Problem 6: No per-formula-TYPE blend curve presets
Users must manually tune deBase, deSensitivity, deThreshold for every formula. The system should know that:
- Logarithmic formulas: DE grows exponentially → needs exponential/sigmoid weight curve
- Linear formulas: DE grows linearly → linear/smooth weight works
- DIFS formulas: DE is absolute distance → inverse weight is most natural
- PK/JK: DE is bounded → sigmoid weight works best

### Problem 7: Separate component blending missing for DIFS
The separate component weights (zVectorWeight, deComponentWeight, colorComponentWeight) don't have a `distComponentWeight` for DIFS formulas that use `aux.dist` separately from `aux.DE`.

### Problem 8: No "passthrough" mode for transforms
When a transform is in a hybrid chain, it should have an option to pass through weight=1.0 always (since transforms are geometry modifiers, not formula slots). Currently users have to know to set weight=1.0 for transforms manually.

### Problem 9: Boolean mode has no weight awareness
When `isBoolean` is true (max/min of distances), the weight system's linear blending is conceptually wrong — you can't linearly interpolate between two boolean-combined distances.

## Proposed Improvements

### Fix 1: CustomDE/DIFS actualDE computation
```cpp
else if (deFunc == fractal::customDEFunction)
{
    actualDE = aux.dist; // DIFS distance is in aux.dist
}
```

### Fix 2: JosKleinian use real fractal parameters
```cpp
else if (deFunc == fractal::josKleinianDEFunction)
{
    actualDE = min(z.y, fractal->analyticDE.tweak005)
              / max(aux.DE, fractal->analyticDE.offset1);
}
```

### Fix 3: MaxAxis DE support
```cpp
else if (deFunc == fractal::maxAxisDEFunction)
{
    CVector4 absZ = fabs(z);
    double maxZ = dMax(absZ.x, absZ.y, absZ.z);
    actualDE = maxZ / aux.DE;
}
```

### Fix 4: DeltaDE awareness
For deltaDE formulas, aux.DE is the derivative accumulator, not distance. The weight system should use `aux.r / aux.DE` as a rough distance proxy for deltaDE.

### Fix 5: New weight mode — "Transform Passthrough" (mode 7)
Always weight=1.0 for transforms, auto-detected from DEFunctionType==withoutDEFunction.

### Fix 6: New weight mode — "DE Ratio" (mode 8)
Weight = ratio of this formula's DE to the previous formula's DE. Useful for hybrid chains where you want formulas with closer surfaces to dominate.

### Fix 7: New weight mode — "Adaptive" (mode 9)
Auto-selects the best weight function based on the formula's DEFunctionType:
- logarithmic → sigmoid curve
- linear → smooth interpolation
- customDE → inverse distance
- PK/JK → sigmoid
- transform → passthrough

### Fix 8: Add `distComponentWeight` to separate components
For DIFS formulas, aux.dist needs its own blend factor independent of aux.DE.

### Fix 9: New blend modes
- **Multiply** — weight = product of multiple criteria
- **Power** — weight = base^(factor) for more extreme curves
- **Min/Max** — take minimum or maximum of two weight criteria

### Fix 10: Improved boolean mode awareness
When isBoolean, blend via smooth min/max instead of linear interpolation.

### Fix 11: Per-formula-type DE normalization
Normalize actualDE before passing to weight modes so all formula types produce comparable DE values regardless of their mathematical properties.

## Implementation Priority

1. **CRITICAL** — Fix customDE/DIFS (92 formulas broken)
2. **CRITICAL** — Fix JosKleinian hardcoded values
3. **HIGH** — Add MaxAxis and DeltaDE support
4. **HIGH** — Add distComponentWeight for DIFS blending
5. **MEDIUM** — New weight modes (Transform Passthrough, DE Ratio, Adaptive)
6. **MEDIUM** — New blend modes (Multiply, Power, MinMax)
7. **MEDIUM** — Boolean mode awareness
8. **LOW** — Per-formula-type presets/normalization

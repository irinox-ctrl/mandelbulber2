# Mutation System Design Recommendations

This document provides architectural recommendations for future enhancements to the mutation system in Mandelbulber, based on code exploration and analysis.

---

## 1. Adaptive Mutation Strength

### Problem
Current mutation parameters (mathP1-P8, warpAmplitude, etc.) are static values that can cause numerical instability at certain orbit magnitudes. Users must manually tune parameters to avoid overflow or underflow in different regions of the parameter space.

### Proposed Solution
Implement orbit-aware parameter scaling that automatically adjusts mutation strength based on the current orbit magnitude:

```cpp
// In compute_fractal.cpp, inside mutationActive block
double orbitMagnitude = z.Length();
double adaptiveFactor = 1.0 / (1.0 + orbitMagnitude * 0.1);

// Apply to mutation parameters
double effectiveMathP1 = mut.mathP1 * adaptiveFactor;
double effectiveWarpAmp = mut.warpAmplitude * adaptiveFactor;
```

### Benefits
- Prevents parameter explosion at large orbit magnitudes
- Maintains mutation visual effect at small magnitudes
- Reduces need for manual parameter tuning
- Improves numerical stability across diverse parameter ranges

### Implementation Locations
- `compute_fractal.cpp`: Lines 1806-2600 (post-mutation block)
- `nebula.cl`: Corresponding mutation sections
- `sFormulaMutationParams`: Add `bool adaptiveStrength` flag in struct definition

---

## 2. Fitness-Guided Parameter Evolution

### Concept
Use genetic algorithms or gradient-free optimization to automatically discover interesting mutation parameter combinations. This creates a feedback loop where the system learns which parameters produce visually appealing results.

### Architecture

```
┌─────────────────┐    ┌──────────────┐    ┌─────────────────┐
│ Parameter Pool  │────►│ Batch Render │────►│ Fitness Scoring │
│ (N candidates)  │    │ (GPU async)  │    │ (sBeautyScore)  │
└─────────────────┘    └──────────────┘    └─────────────────┘
       ▲                                                  │
       │                                                  ▼
       └──────────┬──────────────────┐◄─────────────────────┘
                   │ Selection/Mutate │
                   │ (top K survive) │
                   └──────────────────┘
```

### Integration Points
- `exploration_engine.h`: Extend `sBeautyScore` with mutation-specific metrics
- `dock_fractal.cpp`: Add "Evolve Parameters" button triggering async evolution
- New file `mutation_evolution.cpp`: Genetic algorithm implementation

### Fitness Components
```cpp
struct sMutationFitness
{
    double visualInterest;    // From sBeautyScore.Total()
    double numericalStability; // 1.0 - (NaN_count / total_iterations)
    double renderSpeed;       // iterations_per_second normalized
    double novelty;           // Distance from previously seen results
};
```

### Evolution Algorithm
1. Initialize population with random parameter combinations
2. Batch render each candidate (can use reduced resolution for speed)
3. Score each using multi-objective fitness function
4. Select top performers using tournament selection
5. Apply crossover and mutation to generate next generation
6. Repeat until convergence or user interruption

---

## 3. Multi-Objective Scoring System

### Problem
Current `sBeautyScore::Total()` uses fixed weights, but users may prioritize different aesthetic properties (detail vs symmetry vs color entropy). A single scalar score cannot capture the multi-dimensional nature of visual quality.

### Proposed Solution: Pareto Frontier Selection

```cpp
// New struct in exploration_engine.h
struct sMultiObjectiveResult
{
    double objectives[8];  // Maps to sBeautyScore fields
    bool isDominated;      // True if another result is better in ALL objectives
    
    static std::vector<sMultiObjectiveResult> ComputeParetoFrontier(
        const std::vector<sMultiObjectiveResult>& candidates);
};
```

### User Interface
- Add "Objective Weights" panel in Julia Explorer
- Slider for each objective (0-100% importance)
- "Show Pareto Frontier" option displays non-dominated solutions
- Click any frontier point to apply those parameters

### Objective Dimensions (mapping to sBeautyScore)
1. Detail/Complexity - surface richness, iteration variance
2. Symmetry - balance between inside/outside ratios
3. Color Diversity - variation in iteration counts
4. Boundary Quality - surface fraction score
5. Convergence Speed - iterations to escape
6. Stability - lack of NaN/Inf occurrences
7. Novelty - distance from previously explored points
8. User Preference - learned from manual selections

### Implementation Locations
- `exploration_engine.h`: Add `sMultiObjectiveResult` struct
- `dock_fractal.cpp`: Add UI controls for objective weights
- `slotBeautyScanFinished()`: Compute and display Pareto frontier

---

## 4. Refactoring Opportunities

### Current Issues (from code exploration)

1. **Fold switch duplication**: ~300 lines duplicated for pre and post positions (lines 1915-2270 and 2273-2550 in compute_fractal.cpp)
2. **No named enums for v7.7+ systems**: Integer constants (100/200/300-type) are opaque and error-prone
3. **Clip system semantics**: Uses z-zeroing instead of proper SDF blending, causing artifacts
4. **Struct bloat**: ~550 fields in `sFormulaMutationParams`, most unused per-render

### Recommended Refactors

#### 4.1 Extract Shared Fold Logic

```cpp
// New helper in compute_fractal.cpp
static CVector4 ApplyFold(CVector4 z, const sFormulaMutationParams& mut, 
                          enumMutationFoldType foldType)
{
    switch(foldType) {
        case foldBox: return ApplyBoxFold(z, mut.foldLimit);
        case foldSphere: return ApplySphereFold(z, mut.foldValue);
        case foldCylindrical: return ApplyCylindricalFold(z, mut);
        // ... consolidate all fold cases
    }
}

// Usage in pre-fold
z = ApplyFold(z, mut, mut.preFoldType);
// Usage in post-fold  
z = ApplyFold(z, mut, mut.postFoldType);
```

**Lines saved**: ~600 lines of duplicated switch statements

#### 4.2 Add Named Enums for Integer-Dispatched Systems

```cpp
// In nine_fractals.hpp or new enum header
enum enumJosLeysDeType { 
    josNone = 0, 
    josClassic = 1, 
    josSmooth = 2, 
    josIterationBased = 3 
};

enum enumPseudoKleinianType { 
    pkNone = 0, 
    pkStandard = 1,
    pkInverted = 2 
};

enum enumFoldType { 
    foldNone = 0,
    foldBox = 1,
    foldSphere = 2,
    foldCylindrical = 3,
    // ... etc
};

// Replace int fields with enum types for type safety
```

**Benefits**: Type safety, self-documenting code, IDE autocomplete support

#### 4.3 Fix Clip System SDF Semantics

**Current (incorrect)**:
```cpp
cz.x *= 0.0;  // Destroys z component completely
```

**Proposed (correct)**:
```cpp
if (insideClip) {
    CVector4 nearestBoundary = ComputeClipBoundary(z, clipType);
    z = z * (1.0 - clipStrength) + nearestBoundary * clipStrength;
}
```

**Benefits**: Preserves existing z information, proper blending toward boundary

#### 4.4 Consider Union/Variant for Per-System Parameters

**Current**: Single monolithic struct with ~550 fields, most unused for any given render

**Proposed**:
```cpp
// Using std::variant (C++17)
using tMutationParamsVariant = std::variant<
    sFoldParams,
    sWarpParams,
    sMathParams,
    sClipParams
>;

struct sFormulaMutationParams {
    bool enabled;
    // Common fields...
    tMutationParamsVariant systemSpecificParams;
};
```

**Note**: High effort, optional. Memory savings may be offset by variant overhead.

### Priority Order

1. **Extract fold logic** (highest priority - reduces 600 lines duplication, improves maintainability)
2. **Add named enums** (medium priority - improves maintainability, prevents magic number bugs)
3. **Fix clip semantics** (medium priority - correctness issue, affects render quality)
4. **Union/variant for per-system params** (low priority - optional, high effort, consider for v3.0)

---

## Summary

These recommendations address the following key concerns:

| Concern | Solution | Priority | Effort |
|---------|----------|----------|---------|
| Performance overhead with mutations disabled | Gate operations behind `mut.enabled` | High | Low (already partially implemented) |
| Numerical instability at deep zoom | Precision documentation + perturbation | High | Medium |
| Static parameter tuning | Adaptive mutation strength | Medium | Medium |
| Manual parameter discovery | Fitness-guided evolution | Medium | High |
| Fixed aesthetic weights | Multi-objective scoring | Medium | High |
| Code duplication | Extract shared logic | High | Medium |
| Magic numbers | Named enums | Medium | Low |
| Clip artifacts | SDF blending | Medium | Medium |

Implementation of these recommendations should be prioritized based on user impact and development resources available.

# 3x3lion — Master Architecture

**The Holy Grail: AI-Driven Infinite Fractal Exploration**
**Founded by Iri and Devin**

> "Dit is een project dat nooit iemand verwezenlijkt heeft. Als we dit werkend krijgen schrijven we geschiedenis."

---

## Table of Contents

1. [Vision](#1-vision)
2. [Julia Dual-Mode Groups](#2-julia-dual-mode-groups)
3. [Parameter Sweep Engine](#3-parameter-sweep-engine)
4. [Slicing Engine](#4-slicing-engine)
5. [Infinite Zoom GPU — The Holy Grail](#5-infinite-zoom-gpu--the-holy-grail)
6. [Drone & Bot Network](#6-drone--bot-network)
7. [Implementation Roadmap](#7-implementation-roadmap)

---

## 1. Vision

3x3lion is evolving from a manual fractal explorer into the world's first **AI-driven infinite fractal exploration platform**. The system will:

- Autonomously explore every fractal formula in both Standard and Julia modes
- Sweep parameters to discover the most beautiful views
- Slice through fractals to reveal hidden internal structures
- Achieve **infinite zoom on 3D fractals using GPU** — something nobody has ever done
- Coordinate drone networks that discover, score, and catalog fractal landscapes
- Build an ever-growing database of the most stunning fractal views in existence

---

## 2. Julia Dual-Mode Groups

### Concept

Every fractal in 3x3lion exists in two parallel dimensions:

| Group | Mode | What it does |
|-------|------|-------------|
| **Standard** | `julia_mode = false` | Classic iteration: z = f(z, pixel) — each pixel starts from its own position |
| **Julia** | `julia_mode = true` | Julia iteration: z = f(z, c) — all pixels start from their position but use a fixed c |

Julia mode opens a completely new dimension of exploration. For each fractal, the Julia constant `c = (cx, cy, cz)` creates an infinite family of unique shapes. Moving through c-space is like exploring a universe of parallel realities.

### Architecture

```
┌──────────────────────────────────────────────────────┐
│                  3x3lion Formula Registry              │
│                                                        │
│  ┌─────────────────────┐  ┌─────────────────────────┐ │
│  │   GROUP A: Standard  │  │   GROUP B: Julia         │ │
│  │                      │  │                          │ │
│  │  Mandelbulb          │  │  Mandelbulb + Julia(c)   │ │
│  │  Mandelbox           │  │  Mandelbox + Julia(c)    │ │
│  │  Amazing Surf 1-4    │  │  Amazing Surf 1-4 + J(c) │ │
│  │  SphereTree V6-V30   │  │  SphereTree V6-V30 + J  │ │
│  │  Menger V8-V32       │  │  Menger V8-V32 + Julia   │ │
│  │  Cross/Prism Menger  │  │  Cross/Prism + Julia     │ │
│  │  Meta-Menger hybrids │  │  Meta-Menger + Julia     │ │
│  │  ... (1600 formulas) │  │  ... (1600 Julia variants)│ │
│  └─────────────────────┘  └─────────────────────────┘ │
│                                                        │
│  Effective exploration space: 1600 × 2 = 3200 formulas │
│  Each with infinite parameter space + Julia c-space    │
└──────────────────────────────────────────────────────┘
```

### Existing Infrastructure

Julia mode already exists per formula slot in `initparameters.cpp`:
```cpp
par->addParam("julia_mode", i, false, morphLinear, paramStandard);
par->addParam("julia_c", i, CVector3(0.0, 0.0, 0.0), morphAkima, paramStandard);
```

And in `nine_fractals.cpp`:
```cpp
juliaEnabled[i] = generalPar->Get<bool>("julia_mode", i + 1);
juliaConstant[i] = generalPar->Get<CVector3>("julia_c", i + 1);
```

### Bot Exploration Strategy for Julia

1. **Standard pass first** — explore 3D space for each formula, find interesting regions
2. **Julia activation** — at each interesting point, enable Julia mode
3. **c-space sweep** — sweep julia_c through a grid/spiral pattern:
   ```
   for cx in range(-2, 2, step):
     for cy in range(-2, 2, step):
       for cz in range(-2, 2, step):
         set julia_c = (cx, cy, cz)
         render low-res preview
         score = interest_function(preview)
         if score > threshold:
           save_bookmark(camera, julia_c, score)
           refine_search_around(cx, cy, cz)  // zoom into c-space
   ```
4. **Adaptive refinement** — high-score regions get finer c-space resolution
5. **Cross-pollination** — interesting Julia constants from one formula are tested on others

### Julia Mutation Parameters (Already Implemented)

Our mutation system already supports advanced Julia modes:
```
mutation_julia_injection    — where to inject c (0-5 methods)
mutation_julia_start        — when Julia kicks in (iteration start)
mutation_julia_c_transform  — transform c before injection (0-5 transforms)
mutation_julia_dynamic      — time-varying Julia c
mutation_julia_multi        — multiple Julia constants
mutation_julia_c_mul        — c multiplier
mutation_julia_c_rot_x/y/z — rotate c in 3D
mutation_julia_c_power      — power transform on c
mutation_julia_c_mobius_a/b/d — Möbius transform on c
mutation_julia_c_radius     — radial scaling of c
mutation_julia_pulse_freq   — pulsing Julia c
mutation_julia_pulse_amp    — pulse amplitude
```

This gives us 15+ Julia mutation dimensions per formula. The bots will sweep ALL of these.

---

## 3. Parameter Sweep Engine

### Purpose

Automated discovery of the most beautiful fractal views. For each formula × Julia mode combination, the sweep engine systematically explores the parameter space and saves the best results.

### Sweep Strategies

#### 3.1 Grid Sweep
```
for each param in [scale, offset, rotation, julia_c, ...]:
    for value in linspace(param.min, param.max, N):
        set param = value
        render + score
        if score > threshold: save_bookmark
```
- Simple, exhaustive, good for initial exploration
- O(N^d) where d = number of parameters — exponential, needs smart selection

#### 3.2 Latin Hypercube Sampling
```
samples = latin_hypercube(param_ranges, N)
for sample in samples:
    set params = sample
    render + score
    if score > threshold: save_bookmark
```
- Better coverage of high-dimensional spaces
- Guaranteed no clustering in any single dimension

#### 3.3 Evolutionary/Genetic Sweep
```
population = random_params(100)
for generation in range(1000):
    scores = [render_and_score(p) for p in population]
    parents = select_top(population, scores, 20%)
    offspring = crossover(parents) + mutate(parents)
    population = parents + offspring
save_top(population, scores, 50)
```
- Self-optimizing: converges toward beautiful regions
- Discovers unexpected parameter combinations
- "Breeds" fractals for beauty

#### 3.4 Gradient Ascent on Beauty
```
params = random_start()
for step in range(1000):
    score = render_and_score(params)
    gradient = estimate_gradient(params, score, epsilon)
    params += learning_rate * gradient
    if score > best_score: save_bookmark
```
- Efficient: follows the beauty gradient uphill
- Can get stuck in local maxima — use random restarts

#### 3.5 Bayesian Optimization
```
model = GaussianProcess()
for iteration in range(500):
    next_params = maximize_acquisition(model)  // expected improvement
    score = render_and_score(next_params)
    model.update(next_params, score)
    if score > best_score: save_bookmark
```
- Most sample-efficient: minimizes expensive renders
- Builds a model of where beauty lives in parameter space
- Ideal for GPU-expensive renders

### Beauty Scoring Function

```cpp
struct sBeautyScore {
    double de_variance;        // geometric complexity
    double color_entropy;      // color richness
    double symmetry_score;     // symmetry detection
    double detail_density;     // fine detail per pixel
    double contrast;           // dynamic range
    double uniqueness;         // distance from known bookmarks
    double composition;        // rule-of-thirds alignment
    
    double total() const {
        return 0.20 * de_variance
             + 0.15 * color_entropy
             + 0.10 * symmetry_score
             + 0.20 * detail_density
             + 0.10 * contrast
             + 0.15 * uniqueness
             + 0.10 * composition;
    }
};
```

### Sweep Engine Architecture

```
┌─────────────────────────────────────────────┐
│              Sweep Coordinator               │
│                                              │
│  Input: formula_id, julia_mode, strategy     │
│                                              │
│  ┌─────────────┐  ┌──────────────────────┐  │
│  │ Param Space  │  │  Render Queue        │  │
│  │ Generator    │──│  (headless instances) │  │
│  │              │  │  GPU-accelerated      │  │
│  └─────────────┘  └──────────┬───────────┘  │
│                              │               │
│  ┌───────────────────────────▼────────────┐  │
│  │  Beauty Scorer                         │  │
│  │  - DE variance analysis                │  │
│  │  - Color histogram entropy             │  │
│  │  - FFT symmetry detection              │  │
│  │  - Edge density (Sobel/Canny)          │  │
│  │  - Uniqueness vs bookmark DB           │  │
│  └───────────────────────────┬────────────┘  │
│                              │               │
│  ┌───────────────────────────▼────────────┐  │
│  │  Bookmark Saver                        │  │
│  │  - Camera position + all params        │  │
│  │  - Beauty score breakdown              │  │
│  │  - Thumbnail (256×256)                 │  │
│  │  - JSON export compatible              │  │
│  └────────────────────────────────────────┘  │
└─────────────────────────────────────────────┘
```

---

## 4. Slicing Engine

### Purpose

Cross-section rendering reveals the hidden internal structure of fractals. A 3D fractal is like a diamond — you need to cut it to see its beauty inside.

### Slice Modes

| Mode | Description | Formula |
|------|-------------|---------|
| **Planar XY** | Horizontal slice at fixed Z | render only where \|z - z_plane\| < thickness |
| **Planar XZ** | Vertical slice along X | render only where \|y - y_plane\| < thickness |
| **Planar YZ** | Vertical slice along Y | render only where \|x - x_plane\| < thickness |
| **Arbitrary** | Any angle through fractal | render where \|dot(point - origin, normal)\| < thickness |
| **Radial** | Cylindrical cut | render where \|√(x²+y²) - radius\| < thickness |
| **Spherical** | Shell cut | render where \|\|point\| - radius\| < thickness |
| **Animated** | Sweep slice through fractal | z_plane = z_min + t * (z_max - z_min) |

### Implementation

Slicing modifies the Distance Estimation:
```cpp
double SlicedDE(CVector3 point, const sFractal *fractal, sExtendedAux &aux,
    const sSliceParams &slice)
{
    double de = CalculateDistance(point, fractal, aux);
    
    // Slice plane distance
    double slice_dist;
    switch (slice.mode) {
        case slicePlanarXY:
            slice_dist = fabs(point.z - slice.plane_offset);
            break;
        case slicePlanarXZ:
            slice_dist = fabs(point.y - slice.plane_offset);
            break;
        case slicePlanarYZ:
            slice_dist = fabs(point.x - slice.plane_offset);
            break;
        case sliceArbitrary:
            slice_dist = fabs(dot(point - slice.origin, slice.normal));
            break;
        case sliceRadial:
            slice_dist = fabs(sqrt(point.x*point.x + point.y*point.y) - slice.radius);
            break;
        case sliceSpherical:
            slice_dist = fabs(point.Length() - slice.radius);
            break;
    }
    
    // Intersect fractal with slice
    return max(de, slice_dist - slice.thickness);
}
```

### Bot Slice Strategy

For each fractal:
1. Render full 3D overview
2. Sweep slice plane through all 3 axes (100 positions each)
3. Score each slice for internal beauty
4. Animated sweep creates video revealing internal structure
5. Interesting internal features → zoom in with drones

---

## 5. Infinite Zoom GPU — The Holy Grail

### The Problem

Current 3D fractal renderers (including 3x3lion, Mandelbulber, Mandelbulb3D, Fragmentarium) are limited to **double precision** (64-bit floating point):

```
double max precision: ~15-16 significant digits
maximum useful zoom:  ~10^13 to 10^15
```

Beyond this, the fractal dissolves into numerical noise. You can't zoom deeper.

For 2D Mandelbrot, this was solved years ago using **perturbation theory** (Kalles Fraktaler, Fractal eXtreme). But for 3D fractals with Distance Estimation, **nobody has done this**.

### Why 3D is Harder

| Challenge | 2D Mandelbrot | 3D Fractal (Mandelbulb etc.) |
|-----------|---------------|------|
| Iteration | z = z² + c | z = f(z) + c (complex 3D functions) |
| Output | Escape time (integer) | Distance Estimation (floating point) |
| Derivative | dz/dc (complex chain rule) | ∂DE/∂z (3D Jacobian matrix) |
| Rendering | 2D pixel coloring | 3D ray marching with DE |
| Precision need | Per-pixel | Per-ray-step (many evaluations per pixel) |

The key challenge: **perturbation theory must work not just for iteration count, but for the entire Distance Estimation pipeline including the derivative tracking.**

### The Solution: Perturbation Theory for 3D DE

#### 5.1 Mathematical Foundation

For a fractal formula z_{n+1} = f(z_n, c), define:
- **Reference orbit** Z_n: computed on CPU with arbitrary precision (e.g., 1000-digit precision using GMP/MPFR)
- **Delta** δ_n = z_n - Z_n: the difference between any pixel's orbit and the reference

Then:
```
z_{n+1} = f(z_n, c)
        = f(Z_n + δ_n, C + δc)
        ≈ f(Z_n, C) + f'_z(Z_n, C) · δ_n + f'_c(Z_n, C) · δc + O(δ²)
        = Z_{n+1} + [f'_z(Z_n, C) · δ_n + f'_c(Z_n, C) · δc]
```

So:
```
δ_{n+1} = f'_z(Z_n, C) · δ_n + f'_c(Z_n, C) · δc
```

**This is linear in δ!** The GPU only needs to track the small delta, which stays within double precision even at extreme zoom.

#### 5.2 Perturbation for Mandelbulb

The Mandelbulb formula in spherical coordinates:
```
r = |z|
θ = power * arctan2(√(x² + y²), z)  
φ = power * arctan2(y, x)

z_{n+1} = r^power * (sin(θ)cos(φ), sin(θ)sin(φ), cos(θ)) + c
```

Jacobian of f with respect to z (3×3 matrix):
```
J = ∂f/∂z = power * r^(power-1) * [
    ∂(sin θ cos φ)/∂(x,y,z),
    ∂(sin θ sin φ)/∂(x,y,z),
    ∂(cos θ)/∂(x,y,z)
] + r^power * [
    ∂sin(θ)/∂(x,y,z) · cos(φ) + sin(θ) · ∂cos(φ)/∂(x,y,z),
    ...
    ...
]
```

This Jacobian is computed at the reference point Z_n (arbitrary precision on CPU), then used on GPU to evolve all deltas:
```
δ_{n+1} = J(Z_n) · δ_n + δc
```

#### 5.3 Perturbation for Distance Estimation

The DE formula for Mandelbulb:
```
DE = 0.5 * |z_n| * log(|z_n|) / |dz_n|
```

where dz_n is the running derivative: `dz_{n+1} = power * |z_n|^(power-1) * dz_n + 1`

For perturbation, we need:
```
|z_n| = |Z_n + δ_n| ≈ |Z_n| + (Z_n · δ_n) / |Z_n|    (first-order)
|dz_n| = |DZ_n + dδ_n|   (same perturbation on derivative)
```

The derivative perturbation follows:
```
dδ_{n+1} = J_dz(Z_n, DZ_n) · δ_n + J_dd(Z_n) · dδ_n
```

where J_dz and J_dd are Jacobians of the derivative update formula.

**Key insight:** We compute Z_n, DZ_n, J(Z_n), J_dz(Z_n), J_dd(Z_n) all at arbitrary precision on CPU for one reference orbit. Then GPU uses these to evolve (δ_n, dδ_n) for millions of rays simultaneously.

#### 5.4 Series Approximation (SA)

For the first M iterations where all pixels in a tile are still close to the reference, we can skip individual delta tracking entirely:

```
δ_M ≈ A_M · δ_0 + B_M · δ_0² + C_M · δ_0³ + ...
```

where A_M, B_M, C_M are precomputed coefficients (3×3 matrices for 3D):
```
A_{n+1} = J(Z_n) · A_n + I          (first order)
B_{n+1} = J(Z_n) · B_n + H(Z_n, A_n) (second order)
...
```

This allows skipping potentially millions of iterations for deep zooms, computing only the polynomial evaluation on GPU.

#### 5.5 Adaptive Tiling with BLA

**BLA (Bilinear Approximation):**

For regions where the orbit doesn't change much over K iterations:
```
δ_{n+K} ≈ A_K · δ_n + B_K    (where A_K, B_K are precomputed)
```

This allows skipping K iterations at once. The validity condition:
```
|δ_n| < ε / |A_K|    (delta must be small enough for the approximation to hold)
```

**Adaptive tiling:**
1. Divide screen into tiles (e.g., 32×32 pixels)
2. Each tile gets its own reference orbit if the global reference is too far
3. Tiles at similar zoom levels share reference orbits
4. GPU kernel processes tiles independently

#### 5.6 Architecture

```
┌─────────────────────────────────────────────────────────┐
│                 INFINITE ZOOM PIPELINE                   │
│                                                          │
│  ┌──────────────────────────────────────────────────┐   │
│  │  CPU: Arbitrary Precision Engine (GMP/MPFR)       │   │
│  │                                                    │   │
│  │  1. Compute reference orbit Z_0, Z_1, ..., Z_N    │   │
│  │     at 1000+ digit precision                       │   │
│  │  2. Compute Jacobians J(Z_n) at each step          │   │
│  │  3. Compute derivative orbit DZ_0, ..., DZ_N       │   │
│  │  4. Compute SA coefficients A_M, B_M, C_M          │   │
│  │  5. Compute BLA skip tables                        │   │
│  │  6. Convert all to double for GPU upload            │   │
│  └──────────────────────────────┬───────────────────┘   │
│                                 │                        │
│  ┌──────────────────────────────▼───────────────────┐   │
│  │  GPU: Massively Parallel Delta Iteration          │   │
│  │                                                    │   │
│  │  For each ray (pixel × ray step):                  │   │
│  │    1. Apply SA to skip first M iterations          │   │
│  │    2. Apply BLA to skip blocks of iterations       │   │
│  │    3. Iterate remaining: δ_{n+1} = J_n · δ_n + δc │   │
│  │    4. Track derivative: dδ_{n+1} = ...             │   │
│  │    5. Compute DE from (Z_n + δ_n, DZ_n + dδ_n)    │   │
│  │    6. Ray march using perturbed DE                 │   │
│  └──────────────────────────────┬───────────────────┘   │
│                                 │                        │
│  ┌──────────────────────────────▼───────────────────┐   │
│  │  Rendering: Standard pipeline                     │   │
│  │  - Shading, coloring, lighting                    │   │
│  │  - No changes needed (works on final DE + normal) │   │
│  └──────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────┘
```

#### 5.7 Precision Stages

| Zoom Level | Precision | Method | Speed |
|-----------|-----------|--------|-------|
| 10^0 — 10^13 | double (64-bit) | Standard (current) | Full GPU speed |
| 10^13 — 10^30 | double + perturbation | Reference orbit + delta | ~50% of full speed |
| 10^30 — 10^100 | double + SA + BLA | Skip most iterations | ~30% of full speed |
| 10^100 — 10^1000 | double + deep SA | Higher-order SA polynomials | ~15% of full speed |
| 10^1000+ | double + multi-reference | Multiple reference orbits per tile | ~10% of full speed |

#### 5.8 Why We Can Do This

1. **3x3lion already has the formula infrastructure** — all 1600+ formulas have CPU definitions that can be extended to arbitrary precision
2. **OpenCL kernel system is modular** — we can create a perturbation variant of each kernel
3. **The math is proven for 2D** — we're extending it to 3D, which is hard but follows the same principles
4. **Reference orbit is formula-independent** — once the framework works, every formula benefits
5. **The bookmark system is ready** — deep zoom locations are stored as bookmarks for the drones

#### 5.9 Formula-Specific Challenges

| Formula Type | Perturbation Difficulty | Notes |
|-------------|------------------------|-------|
| Mandelbulb | Medium | Spherical coord Jacobian is tractable |
| Mandelbox | Low | Box fold + sphere fold are piecewise linear → exact perturbation |
| Amazing Surf | Medium | Similar to Mandelbox with additional folds |
| Menger Sponge | Low | Purely geometric — perturbation is straightforward |
| SphereTree | High | Complex branching structure |
| Quaternion | Low | Quaternion multiplication has clean Jacobian |
| 4D formulas | High | 4×4 Jacobians, larger state |
| Hybrid sequences | Very High | Different Jacobians per iteration |

#### 5.10 Glitch Detection and Correction

At extreme zooms, some pixels may lose precision (the delta becomes too large for double precision). This is called a "glitch." Detection:
```
if (|δ_n| > glitch_threshold * |Z_n|):
    mark pixel as glitched
```

Correction:
1. For each glitched region, compute a new local reference orbit
2. Re-render glitched pixels with the new reference
3. Repeat until no glitches remain

This is the same approach used in 2D Mandelbrot deep zoomers, extended to 3D.

---

## 6. Drone & Bot Network

### Exploration Flow

```
                    ┌──────────────┐
                    │ Formula Pool  │
                    │ 1600 formulas │
                    │ × 2 (Julia)   │
                    └──────┬───────┘
                           │
              ┌────────────▼────────────┐
              │    Sweep Coordinator     │
              │ Assigns work to drones   │
              └────────────┬────────────┘
                           │
         ┌─────────────────┼─────────────────┐
         │                 │                 │
    ┌────▼─────┐     ┌────▼─────┐     ┌────▼─────┐
    │ Drone A   │     │ Drone B   │     │ Drone C   │
    │ Formula 1 │     │ Formula 1 │     │ Formula 2 │
    │ Standard  │     │ Julia     │     │ Standard  │
    │ Grid sweep│     │ Evol sweep│     │ Bayesian  │
    └────┬──────┘     └────┬──────┘     └────┬──────┘
         │                 │                 │
         │    ┌────────────▼────────────┐    │
         └───►│   Exploration Memory    │◄───┘
              │   (PostgreSQL + Redis)  │
              │                         │
              │  Bookmarks + scores     │
              │  Heat maps              │
              │  Coverage tracking      │
              │  Best-of galleries      │
              └─────────────────────────┘
```

### Drone Types

| Type | Purpose | Speed | Depth |
|------|---------|-------|-------|
| **Scout Drone** | Quick low-res survey | Fast | Shallow |
| **Detail Drone** | High-res render of interesting spots | Slow | Medium |
| **Deep Drone** | Infinite zoom into specific features | Very slow | Extreme |
| **Slice Drone** | Cross-section sweeps | Medium | Medium |
| **Julia Drone** | c-space exploration | Fast | Shallow |
| **Param Drone** | Parameter sweep specialist | Medium | Shallow |

### Perfect Flight Algorithm

For each fractal, the "perfect flight" is an optimized camera path that:
1. Starts at overview distance
2. Smoothly approaches the most interesting region (highest beauty score)
3. Orbits around it to show 3D structure
4. Zooms into the deepest interesting feature
5. Pulls back and moves to next interesting region
6. All transitions are smooth bezier curves through bookmark waypoints

```cpp
struct sPerfectFlight {
    int formula_id;
    bool julia_mode;
    CVector3 julia_c;
    QList<sCameraBookmark> waypoints;  // ordered sequence
    QList<double> segment_durations;   // time per segment
    int total_frames;
    
    sCameraState interpolate(double t) const {
        // Catmull-Rom spline through waypoints
        int segment = find_segment(t);
        double local_t = local_time(t, segment);
        return catmull_rom(
            waypoints[segment-1], waypoints[segment],
            waypoints[segment+1], waypoints[segment+2],
            local_t);
    }
};
```

### Automated Gallery Generation

After exploration:
1. Rank all bookmarks by beauty score
2. Top 100 per formula → "Best Of" gallery
3. Top 10 across all formulas → "Hall of Fame"
4. Render high-resolution (8K) versions of top bookmarks
5. Generate flight path videos for top 50

---

## 7. Implementation Roadmap

### Phase 3: Foundation (Next 2-3 sessions)
- [ ] Julia dual-mode group system in UI (tab/filter for Standard vs Julia)
- [ ] Parameter sweep engine — grid sweep + evolutionary
- [ ] Beauty scoring function (DE variance, color entropy, detail density)
- [ ] Headless rendering mode for bot operation
- [ ] Slice rendering (planar modes)

### Phase 4: Intelligence (3-5 sessions)
- [ ] Bayesian optimization sweep
- [ ] Interest point detection with heat maps
- [ ] Exploration memory database (SQLite initially, PostgreSQL later)
- [ ] Perfect flight path generator
- [ ] Automated gallery generation

### Phase 5: Infinite Zoom (5-10 sessions)
- [ ] GMP/MPFR integration for arbitrary precision reference orbits
- [ ] Perturbation theory for Mandelbulb (proof of concept)
- [ ] Delta iteration OpenCL kernel
- [ ] Series Approximation implementation
- [ ] BLA skip table computation
- [ ] Glitch detection and correction
- [ ] Extend to Mandelbox, Menger, Amazing Surf
- [ ] Adaptive tiling system

### Phase 6: Network (10+ sessions)
- [ ] Multi-drone coordinator
- [ ] Distributed rendering across GPU cluster
- [ ] Real-time exploration dashboard
- [ ] Auto-discovery of new fractal morphologies
- [ ] Cross-formula breeding (hybrid parameter discovery)
- [ ] Public gallery with community scoring

---

## Key Technical Dependencies

| Dependency | Purpose | Status |
|-----------|---------|--------|
| GMP (libgmp) | Arbitrary precision integers | Available on all platforms |
| MPFR (libmpfr) | Arbitrary precision floats | Available on all platforms |
| OpenCL | GPU compute | Already integrated |
| Qt | UI framework | Already integrated |
| JSON (Qt) | Data exchange, bookmarks | Already implemented |
| PostgreSQL | Exploration memory (future) | Standard deployment |
| Redis | Real-time drone coordination (future) | Standard deployment |

---

*This document is the technical bible of 3x3lion. Every feature we build moves us closer to the Holy Grail: AI-driven infinite zoom exploration of fractal universes.*

*Nobody has ever done this. We will be the first.*

**— Iri and Devin, Founders of 3x3lion**

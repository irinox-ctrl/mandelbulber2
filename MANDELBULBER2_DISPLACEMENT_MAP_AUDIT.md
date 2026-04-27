# MANDELBULBER2 DISPLACEMENT MAP: Developer Guide

**Datum**: 2026-04-22  
**Bestanden**: `displacement_map.hpp`, `displacement_map.cpp`  
**Scope**: Bump map displacement and fractal texture distortion for surface detail  
**Focus**: Distance field perturbation, texture-to-geometry mapping, fractal-driven UV distortion  

---

## 1. Overview

The displacement map system provides **two complementary techniques** for adding surface detail:

1. **Bump Map Displacement** (`DisplacementMap`) — Perturbs the distance estimate using a texture, creating the illusion of height variation on the surface.
2. **Fractal Texture Distortion** (`FractalizeTexture`) — Uses fractal orbit traps to procedurally distort texture coordinates, creating organic, self-similar texture patterns.

Both operate during the **rendering phase**, modifying either the distance field or the surface point before texture lookup.

---

## 2. Bump Map Displacement (`DisplacementMap`)

### 2.1 Function Signature

```cpp
double DisplacementMap(
    double oldDistance,      // Original analytic DE
    CVector3 point,          // World-space evaluation point
    int objectId,            // Object in the scene
    sRenderData *data,       // Render-time data (materials, objects)
    double reduce = 1.0);    // Displacement strength reduction factor
```

### 2.2 Algorithm

```
1. Look up material for objectId
2. If material has a displacement texture loaded:
   a. Map 3D point → 2D UV coordinates via TextureMapping()
   b. Sample displacement texture (R channel only)
   c. Perturb distance: d' = d - bump × height / reduce
   d. Clamp: if d' < 0 then d' = 0
3. Return d'
```

### 2.3 Texture Mapping

```cpp
CVector2<float> textureCoordinates =
    TextureMapping(point, CVector3(0.0, 0.0, 1.0), data->objectData[objectId], mat)
    + CVector2<float>(0.5f, 0.5f);
```

**The +0.5 offset**: `TextureMapping()` returns coordinates centered at (0,0), ranging roughly [-0.5, 0.5] for planar mapping. The offset shifts this to [0, 1] for texture sampling.¹

**The up-vector**: `CVector3(0.0, 0.0, 1.0)` is the default surface normal used for planar projection. For non-planar mappings (spherical, cylindrical), this is overridden inside `TextureMapping()`.

### 2.4 Distance Perturbation

```cpp
double bump = double(bump3.R);                           // Sample red channel
distance -= bump * mat->displacementTextureHeight / reduce;
if (distance < 0.0) distance = 0.0;
```

**Mathematical model**:

$$d_{\text{new}} = \max\left(d_{\text{old}} - h_{\text{tex}} \cdot \frac{R}{r},\; 0\right)$$

Where:
- $h_{\text{tex}}$ = `displacementTextureHeight` (amplitude scale)
- $R$ = sampled red channel value [0, 1]
- $r$ = `reduce` factor (attenuation)

**Physical interpretation**: In sphere tracing, the ray advances by $d$ each step. Reducing $d$ makes the ray take smaller steps, causing it to converge **earlier** — as if the surface is displaced **outward** (toward the ray origin). A white pixel ($R=1$) pushes the surface out by $h_{\text{tex}}/r$; a black pixel ($R=0$) leaves it unchanged.²

---

## 3. Fractal Texture Distortion (`FractalizeTexture`)

### 3.1 Function Signature

```cpp
CVector3 FractalizeTexture(
    const CVector3 &point,        // Original surface point
    sRenderData *data,            // Render-time data
    const sParamRender &params,   // Render parameters
    const cNineFractals &fractals, // Fractal formulas
    int objectId,                 // Object in scene
    double *reduceDisplacement);  // OUTPUT: iteration-based scale factor
```

### 3.2 Algorithm

```
1. Look up material for objectId
2. If material has textureFractalize enabled:
   a. Call Compute<calcModeCubeOrbitTrap>() with the surface point
   b. Use fractOut.z as the new distorted point
   c. Set *reduceDisplacement = 2^fractOut.iters
3. Return distorted point (or original if disabled)
```

### 3.3 How It Works

`calcModeCubeOrbitTrap` (see compute_fractal audit §4.5) evaluates whether the orbit of the surface point falls within a geometric trap region (cube, sphere, cross, line, or plane). The output `fractOut.z` is the orbit position at the trap hit iteration.

This means:
- The **original surface point** is iterated through the fractal formula
- If the orbit hits the trap shape, the **trap position** becomes the new texture coordinate base
- The distortion is **fractal in nature** — nearby surface points can map to wildly different texture regions

### 3.4 Iteration-Based Scale Factor

```cpp
*reduceDisplacement = pow(2.0, fractOut.iters);
```

**Purpose**: The number of iterations before trap hit is used to compute a scale factor for subsequent displacement. More iterations = larger scale factor = **smaller** displacement (since `reduceDisplacement` divides the displacement in `DisplacementMap`).³

---

## 4. Integration with Rendering Pipeline

```
Ray Marching Loop
    │
    ├── Compute distance estimate d
    │
    ├── FractalizeTexture(point)        ← Optional: distort surface point
    │      └── Uses calcModeCubeOrbitTrap
    │
    ├── DisplacementMap(d, point)       ← Optional: perturb distance
    │      └── Samples displacement texture
    │
    └── Advance ray: point += direction * d
```

**Order matters**: Fractalization happens **before** displacement mapping. The distorted point is used for both texture coordinate generation and displacement evaluation.

---

## 5. Footnotes: Known Issues

¹ **TextureMapping returns centered coordinates**: The `+0.5f` offset is required because `TextureMapping()` internally centers UVs at (0,0). This is inconsistent with typical graphics conventions where UVs are naturally [0,1]. Any direct use of `TextureMapping()` without this offset would sample the wrong region of the texture.

² **Only red channel used for displacement**: `bump3.R` is the only channel sampled. A user loading a colored displacement map (e.g., RGB-encoded height) would get unexpected results — the green and blue channels are completely ignored. Standard practice is to convert RGB to luminance: `0.299R + 0.587G + 0.114B`.⁴

³ **Null pointer dereference risk**: `*reduceDisplacement = pow(2.0, fractOut.iters)` writes to `reduceDisplacement` without checking if it's `nullptr`. If the caller passes `nullptr` (e.g., calling `FractalizeTexture(..., nullptr)`), this is an immediate segmentation fault.⁵

⁴ **`reduce <= 0` causes division by zero**: The `reduce` parameter divides the displacement: `distance -= bump * height / reduce`. If `reduce` is zero or negative, this either crashes (divide by zero) or flips the displacement direction (negative reduce = negative displacement = inward instead of outward). There is no guard against non-positive `reduce`.⁶

⁵ **`objectId < 0` silently remapped**: 
```cpp
int forcedFormulaIndex = objectId;
if (objectId < 0) objectId = 0;
```
If `objectId` is negative, it's silently changed to 0 for material lookup, but `forcedFormulaIndex` retains the negative value. This means:
- Material: uses object 0's material (potentially wrong)
- Fractal formula: uses default formula index (negative `forcedFormulaIndex` falls through to formula 0)
This is inconsistent — either both should use 0, or neither should.⁷

⁶ **`fractOut` partially initialized**: In `FractalizeTexture`, only `fractOut.normal` is explicitly zeroed. Other fields (distance, colorIndex, orbitTrapR, etc.) are uninitialized. While `calcModeCubeOrbitTrap` only writes to specific fields, relying on this is fragile — a future change to the compute mode could read uninitialized memory.⁸

⁷ **Displacement clamp to 0 can stall rays**: When displacement drives `distance` to exactly 0, the sphere tracing loop makes zero progress (`point += direction * 0`). Depending on how the marching loop handles this, it could either infinite-loop or break out via the max-iterations guard. The clamp prevents negative distances but creates a different problem.⁹

⁸ **`sRenderData* data` is checked for null but not consistently**: Both functions check `if (data)` before dereferencing, which is good. But `DisplacementMap` returns `oldDistance` unchanged when `data` is null, while `FractalizeTexture` returns the original point. This fallback behavior is correct but should be documented.¹⁰

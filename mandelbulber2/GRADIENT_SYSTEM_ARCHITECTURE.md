# Gradient System V3 — Architecture & Bug Analysis

## Document Purpose
This document captures all findings from the investigation into the "grey fractal on New" bug in the FULL OpenCL engine. It serves as reference for future implementations and debugging.

---

## 1. Bug Summary

| Scenario | Result |
|----------|--------|
| CPU rendering | ✅ Always works |
| GPU + Load Settings | ✅ Works |
| GPU + Load Example | ✅ Works |
| GPU + Medium engine + New | ✅ Works |
| GPU + Full engine + New | ❌ Grey fractal |
| GPU + Full + Specular enabled | ✅ Color returns |

**Symptom:** After clicking "New" (reset to defaults), the FULL OpenCL engine renders a uniformly grey fractal. Enabling specular highlighting brings color back, suggesting the *surface color* pipeline specifically is outputting a uniform value.

---

## 2. Architecture Overview

### 2.1 Rendering Pipeline (OpenCL)

```
full_engine.cl / limited_engine.cl
  → ray_recursion.cl (FULL only)
    → ObjectShader (shader_object.cl)
      → SurfaceColor (shader_surface_color.cl)
        → Fractal() → colorIndex
        → ApplyGradientTransform() → colorPosition
        → GetColorFromGradient() → gradientColor
        → ApplyGradientPostProcess()
        → ApplyGradientNoise()
        → ApplyBlendMode()
```

### 2.2 Engine Differences

| Aspect | LIMITED (Medium) | FULL |
|--------|-----------------|------|
| Materials | Single `__global sMaterialCl *material` | Array `__global sMaterialCl **materials` |
| Palettes | Single `__global float4 *palette` | Array `__global float4 **palettes` |
| Gradient offsets | Scalar `int paletteSurfaceOffset` | Array `int *paletteSurfaceOffsets` |
| Material lookup | Direct (always material index 1) | Via `objectData->materialId` |
| Ray recursion | No (single bounce) | Yes (reflections, refractions) |
| Object ID | Always 0 | From ray marching result |
| Defined | (none specific) | `FULL_ENGINE` |

### 2.3 Data Flow: CPU → GPU Buffer

```
cMaterial (CPU, material.h)
  → clCopySMaterialCl() (material_cl.h)
    → sMaterialCl (GPU struct)
      → packed into buffer by BuildMaterialsData() (opencl_dynamic_data.cpp)
        → read by full_engine.cl / limited_engine.cl
```

### 2.4 Per-Material Buffer Layout (opencl_dynamic_data.cpp)

Each material's header in the GPU buffer:
```
Offset (bytes)  Field
+0              materialClOffset (int)
+4              paletteItemsOffset (int)
+8              paletteOffsetSurface (int)         [sizeof(int) * 2]
+12             paletteSizeSurface (int)            [sizeof(int) * 3]
+16             paletteOffsetSpecular (int)         [sizeof(int) * 4]
+20             paletteSizeSpecular (int)           [sizeof(int) * 5]
+24             paletteOffsetDiffuse (int)          [sizeof(int) * 6]
+28             paletteSizeDiffuse (int)            [sizeof(int) * 7]
+32             paletteOffsetLuminosity (int)       [sizeof(int) * 8]
+36             paletteSizeLuminosity (int)         [sizeof(int) * 9]
+40             paletteOffsetRoughness (int)        [sizeof(int) * 10]
+44             paletteSizeRoughness (int)          [sizeof(int) * 11]
+48             paletteOffsetReflectance (int)      [sizeof(int) * 12]
+52             paletteSizeReflectance (int)        [sizeof(int) * 13]
+56             paletteOffsetTransparency (int)     [sizeof(int) * 14]
+60             paletteSizeTransparency (int)       [sizeof(int) * 15]
+64             opacityOffsetSurface (int)          [sizeof(int) * 16]
+68             opacitySizeSurface (int)            [sizeof(int) * 17]
... (opacity for specular/diffuse/luminosity/roughness/reflectance/transparency)
+120            midpointOffsetSurface (int)         [sizeof(int) * 30]
+124            midpointSizeSurface (int)           [sizeof(int) * 31]
... (midpoints for specular/diffuse/luminosity/roughness/reflectance/transparency)
+176            [alignment padding to 16 bytes]
+aligned        sMaterialCl struct data
+aligned        palette float4 array (all gradients concatenated)
```

### 2.5 Gradient Palette Concatenation Order

All gradient palettes are concatenated into a single float4 array per material:
1. Surface gradient colors
2. Specular gradient colors
3. Diffuse gradient colors
4. Luminosity gradient colors
5. Roughness gradient colors
6. Reflectance gradient colors
7. Transparency gradient colors
8. Opacity surface gradient
9. Opacity specular gradient
10. ... (opacity for each type)
11. Midpoint surface data
12. Midpoint specular data
13. ... (midpoints for each type)

Offsets and lengths stored in the header are indices into this concatenated array.

---

## 3. Root Cause Analysis

### 3.1 The Gradient Transform Change

**Upstream (original) code** in `shader_surface_color.cl`:
```cl
float colorPosition = fmod(
    nCol / 256.0f / 10.0f * input->material->coloring_speed + input->material->paletteOffset,
    1.0f);
```
This **wraps** the color position into [0, 1) — always produces variation across the fractal.

**Modified (V3) code**:
```cl
float rawColorPosition = nCol / 256.0f / 10.0f * input->material->coloring_speed
    + input->material->paletteOffset;
float colorPosition = ApplyGradientTransform(rawColorPosition,
    input->material->gradientScale, input->material->gradientOffset,
    input->material->gradientRepeatMode);
```

### 3.2 The Problem with Defaults

Default values from `initparameters.cpp`:
- `gradientScale` = 1.0
- `gradientOffset` = 0.0
- `gradientRepeatMode` = 0 (Clamp)

With these defaults, `ApplyGradientTransform(x, 1.0, 0.0, 0)` = `clamp(x, 0.0, 1.0)`.

But `rawColorPosition` range is:
- `nCol` = `fmod(fabs(colorIndex), 248.0 * 256.0)` → range [0, 63488)
- `rawColorPosition` = `nCol / 256.0 / 10.0 * 1.0 + 0.0` = `nCol / 2560.0` → range [0, ~24.8)

**Result:** For ANY non-trivial colorIndex, `rawColorPosition > 1.0`, so Clamp mode returns 1.0 for EVERY pixel → uniform color → appears grey.

### 3.3 Why "Load Settings" Works

Saved settings files likely contain `gradientRepeatMode = 1` (Repeat) which uses:
```cl
case 1: // Repeat
    float f = fmod(p, 1.0f);
    return f < 0.0f ? f + 1.0f : f;
```
This wraps like the original `fmod()`, restoring variation.

### 3.4 Why Medium Works but Full Doesn't (Unresolved)

Both engines:
- Use the same `shader_surface_color.cl`
- Read the same material buffer data
- Have the same compile-time defines (`USE_FRACTAL_COLORING`, `USE_SURFACE_GRADIENT`)
- Call the same `ApplyGradientTransform` function

**Possible explanations (not yet confirmed):**
1. **Struct alignment/padding difference** — The `sMaterialCl` struct may have different padding between C++ (as packed by `clCopySMaterialCl`) and the OpenCL compiler. If `gradientRepeatMode` is at a different offset on the GPU, the FULL engine might read a non-zero value (accidentally reading adjacent data that happens to be nonzero) while LIMITED reads the correct zero.
2. **Array indexing issue** — FULL accesses `materials[objectData->materialId]` (= index 1) while LIMITED always uses `material` directly. If there's an off-by-one in how `materialOffsets` are stored/read, FULL could read from a different memory region.
3. **Kernel compilation difference** — FULL and LIMITED are compiled as separate kernels. If the OpenCL compiler optimizes struct layout differently for each, fields could be at different offsets.
4. **Uninitialized memory in local arrays** — FULL uses `int paletteSurfaceOffsets[MAT_ARRAY_SIZE]` as a local array. If `MAT_ARRAY_SIZE > numberOfMaterials`, unread entries contain garbage.

### 3.5 Why Specular "Brings Back Color"

When specular is enabled:
```cl
color = surfaceColor * (fillLight + auxLights + ...) + totalSpecular + ...
```
`totalSpecular` is ADDED on top. Even if `surfaceColor` is uniform grey, specular highlights create visible variation/contrast. The specular gradient (`gradients->specular`) gets set via `GetColorFromGradient` with the same clamped position, but specular is an additive highlight so even a uniform value creates visible contrast against the surface.

---

## 4. Recommended Fixes

### Fix 1: Change Default gradientRepeatMode (Quick Fix)

In `mandelbulber2/src/initparameters.cpp` line 2464:
```cpp
// Change from:
par->addParam(cMaterial::Name("gradient_repeat_mode", materialId), 0, morphLinear, paramStandard);
// To:
par->addParam(cMaterial::Name("gradient_repeat_mode", materialId), 1, morphLinear, paramStandard);
```

This changes the default from Clamp to Repeat, matching the original `fmod()` behavior.

**Pros:** Simple, backwards-compatible with original rendering behavior.
**Cons:** Doesn't explain why Medium works; may mask a deeper struct alignment bug.

### Fix 2: Normalize rawColorPosition Before Transform

In `shader_surface_color.cl`, wrap `rawColorPosition` into [0, 1) BEFORE applying the transform:
```cl
float rawColorPosition = fmod(
    nCol / 256.0f / 10.0f * input->material->coloring_speed + input->material->paletteOffset,
    1.0f);
if (rawColorPosition < 0.0f) rawColorPosition += 1.0f;
float colorPosition = ApplyGradientTransform(rawColorPosition,
    input->material->gradientScale, input->material->gradientOffset,
    input->material->gradientRepeatMode);
```

**Pros:** Ensures all repeat modes work correctly since input is already in [0, 1).
**Cons:** Clamp mode would then do nothing (since input is already [0,1]), making it effectively the same as Repeat.

### Fix 3: Investigate Struct Alignment (Thorough Fix)

Add `__attribute__((packed))` or explicit padding to `sMaterialCl` to ensure CPU and GPU layouts match exactly. Verify with a diagnostic kernel that prints struct field offsets.

---

## 5. Key Files Reference

| File | Role |
|------|------|
| `src/initparameters.cpp` | Default parameter values (gradientRepeatMode, gradientScale, etc.) |
| `src/material.h` | CPU material struct (cMaterial) |
| `src/material.cpp` | CPU material loading from parameters |
| `opencl/material_cl.h` | GPU material struct (sMaterialCl) + clCopySMaterialCl() |
| `src/opencl_dynamic_data.cpp` | Packs material data into GPU buffer (BuildMaterialsData) |
| `src/opencl_engine_render_fractal.cpp` | Sets compile defines (USE_FRACTAL_COLORING, USE_SURFACE_GRADIENT, etc.) |
| `opencl/engines/shader_surface_color.cl` | Surface color calculation + gradient system V3 |
| `opencl/engines/shader_object.cl` | Combines surface color with lighting |
| `opencl/engines/full_engine.cl` | FULL engine entry point (per-material arrays) |
| `opencl/engines/limited_engine.cl` | LIMITED/Medium engine entry point (single material) |
| `opencl/engines/ray_recursion.cl` | FULL engine ray tracing + material lookup |
| `opencl/engines/compute_fractal.cl` | Fractal calculation + colorIndex output |
| `opencl/render_data_cl.h` | sRenderData struct (different layout for FULL vs LIMITED) |
| `opencl/shader_input_data_cl.h` | sShaderInputDataCl struct (same for both engines) |
| `src/render_window_menu.cpp` | "New" / Reset to Default behavior |
| `src/fractparams.cpp` | Maps formula → objectData → materialId |
| `src/object_data.hpp` | Default materialId = 0 |

---

## 6. Gradient System V3 — Feature Overview

### 6.1 New Features Added
- **Multiple color spaces**: RGB, HSL, HSV, LAB, OKLab, Linear sRGB
- **Interpolation modes**: Linear, Smooth, HSLShort, HSLLong, Cubic, Constant, QuadraticBezier, PowerCurve
- **Midpoint control**: Per-segment gamma, bias, intensity
- **Repeat modes**: Clamp, Repeat, Mirror, MirrorOnce, Extend
- **Post-processing**: Brightness, Contrast, Saturation, Gamma
- **Gradient noise**: Dithering based on world position
- **Opacity masks**: Per-gradient-type with invert, contrast, black/white point
- **Blend modes**: Normal, Multiply, Screen, Overlay, Soft Light, Hard Light
- **7 gradient types**: Surface, Specular, Diffuse, Luminosity, Roughness, Reflectance, Transparency

### 6.2 GPU Struct Fields (sMaterialCl in material_cl.h)

```cl
// Gradient enable flags
cl_int surfaceGradientEnable;       // default: true
cl_int specularGradientEnable;      // default: false
cl_int diffuseGradientEnable;       // default: false
cl_int luminosityGradientEnable;    // default: false
cl_int roughnessGradientEnable;     // default: false
cl_int reflectanceGradientEnable;   // default: false
cl_int transparencyGradientEnable;  // default: false

// Gradient mask enable flags
cl_int surfaceGradientMaskEnable;   // default: false
cl_int specularGradientMaskEnable;
cl_int diffuseGradientMaskEnable;
cl_int luminosityGradientMaskEnable;
cl_int roughnessGradientMaskEnable;
cl_int reflectanceGradientMaskEnable;
cl_int transparencyGradientMaskEnable;

// Gradient System V3 parameters
cl_float gradientScale;             // default: 1.0
cl_float gradientOffset;            // default: 0.0
cl_int gradientRepeatMode;          // default: 0 (Clamp) ← BUG SOURCE
cl_int opacityInvert;               // default: 0
cl_float maskContrast;              // default: 1.0
cl_float maskBlackPoint;            // default: 0.0
cl_float maskWhitePoint;            // default: 1.0
cl_float gradientBrightness;        // default: 1.0
cl_float gradientContrast;          // default: 1.0
cl_float gradientSaturation;        // default: 1.0
cl_float gradientGamma;             // default: 1.0
cl_int gradientColorSpace;          // default: 0 (RGB)
cl_float gradientNoiseAmount;       // default: 0.0
cl_int surfaceGradientInterpolationMode;  // from gradient object
cl_int surfaceGradientBlendMode;    // default: 0 (Normal)
```

---

## 7. Compile-Time Defines (opencl_engine_render_fractal.cpp)

These are set based on material properties across ALL materials:
```
-DUSE_FRACTAL_COLORING        → any material has useColorsFromPalette = true
-DUSE_SURFACE_GRADIENT        → any material has surfaceGradientEnable = true
-DUSE_SPECULAR_GRADIENT       → any material has specularGradientEnable = true
-DUSE_DIFFUSE_GRADIENT        → any material has diffuseGradientEnable = true
-DUSE_LUMINOSITY_GRADIENT     → any material has luminosityGradientEnable = true
-DUSE_ROUGHNESS_GRADIENT      → any material has roughnessGradientEnable = true
-DUSE_REFLECTANCE_GRADIENT    → any material has reflectanceGradientEnable = true
-DUSE_TRANSPARENCY_GRADIENT   → any material has transparencyGradientEnable = true
```

Default material 1 has `useColorsFromPalette = true` and `surfaceGradientEnable = true`, so both `USE_FRACTAL_COLORING` and `USE_SURFACE_GRADIENT` are always defined.

---

## 8. "New" / Reset Flow

```
RenderWindow::slotResetToDefault() (render_window_menu.cpp:1008)
  → gPar->ResetAllToDefault()
  → gParFractal->at(i)->ResetAllToDefault()
  → gMainInterface->SynchronizeInterface(write)
  → gMainInterface->StartupDefaultSettings()
```

This resets ALL parameters to their `initparameters.cpp` defaults, including:
- `formula_material_id` = 1
- `surface_gradient_enable` = true
- `gradient_repeat_mode` = 0 (Clamp) ← causes uniform colorPosition = 1.0
- `gradient_scale` = 1.0
- `gradient_offset` = 0.0
- `coloring_speed` = 1.0
- `paletteOffset` = 0.0

---

## 9. Next Steps

1. **Quick fix:** Change default `gradient_repeat_mode` to 1 (Repeat) — fixes the symptom
2. **Better fix:** Pre-normalize `rawColorPosition` with `fmod()` before applying transform
3. **Investigation needed:** Why does Medium engine render correctly with the same default? This suggests a deeper struct alignment or data propagation issue specific to FULL engine
4. **Testing:** After any fix, verify all 5 scenarios from the bug matrix pass
5. **Consider:** Adding a diagnostic mode that logs struct offsets from within OpenCL kernels to detect alignment mismatches

---

*Document created: 2026-05-20*
*Session: https://app.devin.ai/sessions/0e8b75d1ed5f4d5a959c0272bfa193c1*

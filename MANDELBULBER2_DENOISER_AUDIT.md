# MANDELBULBER2 DENOISER: Developer Guide

**Datum**: 2026-04-22  
**Bestanden**: `denoiser.h`, `denoiser.cpp`  
**Scope**: Post-processing denoiser for Monte Carlo rendered images  
**Focus**: Two-pass filter (weighted blur + median), geometry-aware weighting  

---

## 1. Overview

`cDenoiser` is a **post-render denoiser** designed for Monte Carlo path-traced images. It operates on the rendered image after the main raytracing loop completes, applying a spatial filter that preserves geometric edges using depth and normal information.

**Key characteristics**:
- **Two-pass architecture**: (1) weighted spatial blur, (2) median filter
- **Geometry-aware**: Uses Z-buffer and world-space normals to prevent bleeding across edges
- **Noise-adaptive**: Filter radius scales with per-pixel estimated noise
- **4 strength presets**: light, medium, strong, extreme

---

## 2. Architecture

```
Render Loop
    │
    ▼
UpdatePixel(x, y, color, z, noise)    ← called per pixel during render
    │
    ▼
[Denoise called after render completes]
    │
    ├── Pass 1: Weighted Blur
    │   ├── Anti-aliased circular kernel
    │   ├── Normal-based edge weighting
    │   ├── Depth-based edge weighting
    │   └── Noise-preference sampling
    │
    ├── Copy buffer (blur → image)
    │
    └── Pass 2: Median Filter
        ├── Geometry-filtered neighborhood
        └── Partial-sort median (per channel)
```

---

## 3. Strength Presets

| Parameter | Light | Medium | Strong | Extreme |
|-----------|-------|--------|--------|---------|
| `maxBlurRadius` | 5.0 | 10.0 | 15.0 | 30.0 |
| `minBlurRadius` | 0.4 | 0.6 | 0.7 | 1.0 |
| `maxMedianSize` | 1.1 | 2.0 | 4.0 | 6.0 |
| `noiseMultiplier` | 2500 | 5000 | 15000 | 30000 |
| `zDepthFilterfactor` | 100.0 | 100.0 | 10.0 | 7.0 |
| `normalFilterFactor` | 10.0 | 10.0 | 3.0 | 3.0 |

**Design intent**: Stronger presets blur more aggressively (`maxBlurRadius` ↑, `noiseMultiplier` ↑) but relax geometric constraints (`zDepthFilterfactor` ↓, `normalFilterFactor` ↓) to allow more blending. The extreme preset blurs up to 30px radius with very permissive edge detection.

---

## 4. Pass 1: Weighted Spatial Blur

### 4.1 Filter Radius

Per pixel, the filter radius is computed during `UpdatePixel()`:

$$r = \min\left(\sqrt{n \cdot M} + r_{\min},\; r_{\max}\right)$$

Where $n$ = per-pixel noise estimate, $M$ = `noiseMultiplier`, $r_{\min}$ = `minBlurRadius`, $r_{\max}$ = `maxBlurRadius`.

**Intuition**: High-noise pixels get large blur kernels; low-noise pixels get small (or zero) blur.

### 4.2 Anti-Aliased Circular Kernel

For each neighbor pixel at offset $(dx, dy)$:

$$\text{radius} = \sqrt{dx^2 + dy^2}$$
$$w_{\text{circle}} = \text{clamp}(r_{\text{filter}} - \text{radius},\; 0,\; 1)$$

This creates a **soft circular window**: pixels fully inside the circle get weight 1, pixels near the edge get fractional weight (anti-aliasing), pixels outside get 0.

### 4.3 Noise-Preference Weighting

$$w_{\text{noise}} = \text{clamp}\left(\frac{r_{\text{neighbor}}}{r_{\text{center}}},\; 0,\; 1\right)$$

**Intuition**: When sampling the neighborhood, prefer pixels that themselves have high noise. This prevents over-blurring of already-smooth regions while aggressively blending noisy regions.¹

### 4.4 Geometry-Aware Weighting (when `preserveGeometry = true`)

**Normal-based weighting**:
$$\Delta_{\text{normal}} = |\vec{N}_{\text{center}} - \vec{N}_{\text{neighbor}}|$$
$$w_{\text{normal}} = \text{clamp}(1 - \Delta_{\text{normal}} \cdot f_{\text{normal}},\; 0,\; 1)$$

Where $f_{\text{normal}}$ = `normalFilterFactor`. Large normal differences → weight → 0 (don't blend across surface boundaries).

**Depth-based weighting**:
$$\Delta_z = \frac{|z_{\text{center}} - z_{\text{neighbor}}|}{z_{\text{center}}}$$
$$w_{\text{depth}} = \text{clamp}\left(\frac{1}{\Delta_z \cdot f_{\text{depth}}},\; 0,\; 1\right)$$

Where $f_{\text{depth}}$ = `zDepthFilterfactor`. Large relative depth differences → weight → 0.

**Combined geometry weight**:
$$w_{\text{geom}} = w_{\text{noise}} \cdot w_{\text{normal}} \cdot w_{\text{depth}}$$

### 4.5 Special Handling at Loop Counter 3

```cpp
if (loopCounter == 3) {
    filterRadius += clamp(0.1f / (sum * sum + 0.0000001f), 0.0f, 10.0f);
    inputPixel.R = min(inputPixel.R, 1.5f);
    inputPixel.G = min(inputPixel.G, 1.5f);
    inputPixel.B = min(inputPixel.B, 1.5f);
}
```

**First term**: For dark pixels ($sum \approx 0$), the filter radius is boosted by up to 10px. This is the "black spot prevention" — dark noisy regions get extra blur on the first denoising pass.²

**Second term**: Input pixels are clamped to 1.5 during accumulation. This prevents HDR fireflies from dominating the weighted average.³

### 4.6 Z-Buffer Blending

Unlike color (arithmetic mean), Z is blended using a **weighted harmonic mean**:

$$\bar{Z}^{-1} = \frac{\sum_i \frac{w_i}{Z_i}}{\sum_i w_i}$$

This is mathematically equivalent to:
```cpp
averageZ += (1.0 / inputZ) * fweight;   // accumulate inverse
// ...
averageZ = (1.0 / averageZ) * totalWeight;  // invert back
```

**Why harmonic mean?** Depth values have a non-linear relationship with distance. The harmonic mean is less sensitive to extreme depth values (near-zero = very close to camera) than the arithmetic mean.⁴

---

## 5. Pass 2: Median Filter

Applied only to pixels with `filterRadius <= maxMedianSize`.

### 5.1 Weighted Radius

```cpp
if (filterRadius < 1.0f + minBlurRadius) {
    weight = filterRadius - minBlurRadius;  // 0..1 fade
    filterRadius = 1.0f;                     // clamp to minimum 1px
}
```

Pixels with very small radius get a fade-in weight: at `filterRadius = minBlurRadius`, weight = 0 (no median). At `filterRadius = 1.0 + minBlurRadius`, weight = 1 (full median).

### 5.2 Geometry-Filtered Neighborhood Collection

Unlike the blur pass (which weights samples), the median pass **rejects** samples outright:

```cpp
if (radius <= filterRadius 
    && normalWeight > 0.5f 
    && deltaZ < 1.0f / zDepthFilterfactor)
{
    medianRInput.push_back(inputPixel.R);
    // ...
}
```

Only pixels with:
- Within the circular radius
- Normal similarity > 50%
- Relative depth difference < threshold

...are included in the median computation.

### 5.3 Partial-Sort Median

```cpp
std::vector<float> h(medianRInput.size() / 2 + 1);
std::partial_sort_copy(medianRInput.begin(), medianRInput.end(), h.begin(), h.end());
newPixel.R = h.back();  // the (n/2+1)-th smallest element
```

**Efficiency**: `partial_sort_copy` with $k = n/2 + 1$ runs in $O(n \log k) = O(n)$ time. A full sort would be $O(n \log n)$. For small neighborhoods (max ~49 pixels for radius=3), this is a modest but real saving.⁵

### 5.4 Loop-Adaptive Mixing

```cpp
float mixFactor = 1.0f / (loopCounter / 50.0f + 1.0f) * weight;
newPixelMixed = oldPixel * (1 - mixFactor) + newPixel * mixFactor;
```

**Intuition**: As the render accumulates more samples (higher `loopCounter`), the denoiser blends less aggressively. At `loopCounter = 0`: mixFactor = 1.0 (full median). At `loopCounter = 50`: mixFactor ≈ 0.5. At `loopCounter = 200`: mixFactor ≈ 0.2.

---

## 6. Buffer Layout

| Buffer | Type | Content |
|--------|------|---------|
| `blurBuffer` | `sRGBFloat` | Color (RGB float) |
| `blurZBuffer` | `float` | Depth (Z) |
| `blurRadiusBuffer` | `float` | Computed filter radius |

All buffers are 1D arrays indexed as `x + y * width`. Total size: `width * height * sizeof(type)`.

---

## 7. Footnotes: Known Issues

¹ **Noise weight cancels itself out for uniform noise**: If all pixels in a neighborhood have similar noise levels, $w_{\text{noise}} \approx 1$ for all samples, which is harmless. But if the center pixel is the noisiest, neighbors get downweighted, potentially leaving the center pixel under-blurred.

² **Black spot boost formula**: `0.1f / (sum * sum + 0.0000001f)` — as $sum \to 0$, this approaches $10^6$, clamped to 10. The constant `0.0000001f` prevents division by zero but is 7 orders of magnitude smaller than the clamp, meaning the formula is essentially `clamp(0.1 / sum², 0, 10)` for any reasonable pixel value. For `sum = 0.1`, boost = 10 (max). For `sum = 0.316`, boost = 1. For `sum = 1.0`, boost = 0.1. The threshold is sharp and not well-motivated.

³ **HDR clamp at 1.5**: This arbitrarily clamps HDR values during the first denoising pass. Fireflies (extremely bright specular highlights) are suppressed, but legitimate bright areas are also clipped. A better approach would be a relative clamp based on neighborhood statistics (e.g., median + 3σ).

⁴ **Harmonic mean Z-blending vulnerability**: If any sample has $Z = 0$ (exactly on the camera plane), `1.0 / inputZ` produces `inf`, corrupting the harmonic mean. While `z >= 1e-10f` is checked for geometry weighting, there is no guard against zero Z in the accumulation itself.⁶

⁵ **Partial-sort median is biased for even-sized neighborhoods**: For 4 samples, `partial_sort_copy` with $k=3$ returns the 3rd-smallest element (upper median). The true median would be the average of the 2nd and 3rd. This introduces a slight positive bias in the median estimate for even-sized neighborhoods.

⁶ **`preserveGeometry` Z-check inconsistency**: In the blur pass, geometry weighting is guarded by `if (z >= 1e-10f)` (≥). In the median pass, it's guarded by `if (z > 1e-10f)` (>). For pixels with exactly $z = 10^{-10}$, the blur pass applies geometry weighting but the median pass does not. This inconsistency could cause edge artifacts on pixels at that exact depth.⁷

⁷ **Single-threaded execution**: Both `#pragma omp parallel for` directives are commented out. The comment explains this is because Qt Concurrent is unavailable in the PPA repository. For high-resolution images (4K+), single-threaded denoising can take several seconds.⁸

⁸ **Median vectors allocated per pixel per channel**: The median pass allocates three `std::vector<float>` per pixel (R, G, B), each resized dynamically. For a 4K image with 50 iterations, this is ~600 million vector allocations. Pre-allocating fixed-size arrays on the stack or using thread-local buffers would significantly improve performance.

⁹ **No bounds check on `boxX`, `boxY`**: The denoiser assumes `boxX >= 0` and `boxY >= 0`. If called with negative box offsets, `xx = x + boxX` (where `x` and `boxX` are `int`) could underflow, and the subsequent `size_t` conversion would wrap to a huge positive index, causing an out-of-bounds access.

¹⁰ **`loopCounter == 3` is a magic number**: The special handling at loop counter 3 (black spot boost + HDR clamp) is hardcoded with no explanation of why 3 specifically. If the calling code changes its loop structure, this could break.

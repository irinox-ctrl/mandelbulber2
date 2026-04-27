# MANDELBULBER2 DEPTH OF FIELD: Developer Guide

**Datum**: 2026-04-22  
**Bestanden**: `dof.hpp`, `dof.cpp`  
**Scope**: Post-render depth of field (DOF) effect with bokeh simulation  
**Focus**: Two-pass blur algorithm, Z-driven sample weighting, bokeh disc rendering  

---

## 1. Overview

`cPostRenderingDOF` implements a **post-processing depth of field** effect. Unlike real-time DOF which operates during ray tracing, this is applied after the full image has been rendered. It uses the Z-buffer (depth map) to determine how much each pixel should be blurred based on its distance from the focal plane.

**Key characteristics**:
- **Two-pass algorithm**: Forward blur + reversed bokeh simulation
- **Physically motivated**: Blur radius scales with $|z - z_{focal}| / z$
- **Bokeh shape**: Circular (disc-shaped) blur kernel
- **Multi-pass**: Configurable number of iterations for bokeh accumulation

---

## 2. Architecture

```
Input: Rendered image + Z-buffer
    │
    ├── Phase I: Forward Blur
    │   ├── For each pixel:
    │   │   ├── Compute blur radius from depth
    │   │   ├── Gather neighborhood samples
    │   │   ├── Weight by distance + depth similarity
    │   │   └── Write blurred pixel to temp buffer
    │   └── Copy temp buffer → image
    │
    ├── Phase II: Z-Sort + Randomize
    │   ├── QuickSort pixels by Z (front to back)
    │   └── Shuffle with depth-similarity constraint
    │
    └── Phase III: Reversed Bokeh Blur
        └── For N passes:
            ├── Process pixels in randomized Z-order
            └── Blend each pixel as a bokeh disc onto neighbors
```

---

## 3. Blur Radius Formula

The blur radius for a pixel at depth $z$ is:

$$\text{blur} = \frac{|z - z_{neutral}|}{z} \cdot d_{deep}$$

Where:
- $z_{neutral}$ = focal distance (`neutral` parameter)
- $d_{deep}$ = DOF intensity (`deep` parameter)

**Behavior**:
- At focal plane ($z = z_{neutral}$): blur = 0 (perfectly sharp)
- As $z \to \infty$: blur → $d_{deep}$ (max blur for distant objects)
- As $z \to 0^+$: blur → $\infty$ (clamped by `maxRadius`)

**Physical basis**: This approximates the circle of confusion in a thin lens model:
$$CoC \propto \frac{|z - z_{focus}|}{z \cdot N}$$
where $N$ is the f-stop. The $1/z$ term accounts for perspective projection.¹

---

## 4. Phase I: Forward Blur

### 4.1 Algorithm

For each pixel, gather samples within a square window $[-size, +size]$ where $size = \lfloor blur \rfloor$.

**Distance weight**: For a sample at offset $(dx, dy)$:
$$r = \sqrt{dx^2 + dy^2}$$
$$w_{dist} = \text{clamp}(blur - r,\; 0,\; 1)$$

This creates a **tent-shaped radial weight** — samples closer to the center get higher weight, linearly falling to 0 at radius = blur.

### 4.2 Depth-Sensitive Weighting

The most sophisticated part of Phase I is the depth-based sample rejection:

```cpp
float blur1 = (z1 - neutral) / z1 * deep;   // center pixel blur (signed!)
float blur2 = (z2 - neutral) / z2 * deep;   // sample pixel blur (signed!)

if (blur1 > blur2) {
    if (blur1 * blur2 < 0) {
        weight = 0.0;  // Opposite sides of focal plane → reject
    } else {
        // Same side, but center is more blurred → downweight
        float weight2 = (blur1 > 0) 
            ? 1.1f - blur1 / blur2 
            : 1.1f - blur2 / blur1;
        weight *= weight2 * 10.0f;
    }
}
```

**Signed blur**: Unlike the absolute value used for radius, `blur1` and `blur2` are **signed**. Positive = in front of focal plane, negative = behind focal plane.²

**Three cases**:

| Case | Condition | Action |
|------|-----------|--------|
| Same depth | `blur1 ≈ blur2` | Full weight (no penalty) |
| Opposite sides | `blur1 * blur2 < 0` | **Reject** (weight = 0) |
| Same side, different blur | `blur1 * blur2 > 0` | Scale by blur ratio |

**Same-side scaling formula**:
- If both in front (`blur > 0`): $w_{scale} = 1.1 - \frac{blur_1}{blur_2}$
- If both behind (`blur < 0`): $w_{scale} = 1.1 - \frac{blur_2}{blur_1}$

When $blur_1 = blur_2$: $w_{scale} = 0.1$, multiplied by 10 → weight unchanged.
When $blur_1 \gg blur_2$ (center very blurry, sample sharp): $w_{scale} \to -\infty$, clamped to 0.

**Purpose**: Prevents sharp background pixels from bleeding into blurry foreground pixels, and vice versa.³

### 4.3 Accumulation and Normalization

```cpp
if (totalWeight > 0.0f) {
    newPixel = tempPixel / totalWeight;  // Normalize
} else {
    newPixel = original pixel;           // No valid samples → keep original
}
```

If all samples were rejected (e.g., all on the opposite side of the focal plane), the pixel remains unchanged.

---

## 5. Phase II: Z-Sort & Randomize

### 5.1 QuickSort by Z

```cpp
QuickSortZBuffer(temp_sort.data(), 1, sortBufferSize - 1);
```

Sorts all pixels by ascending Z (front to back). Each entry contains:
- `z`: depth value
- `i`: pixel index in the image (x + y * width)

### 5.2 Probabilistic Shuffle

After sorting, the array is shuffled with a **depth-similarity constraint**:

```cpp
for (i = sortBufferSize - 1; i >= 0; i--) {
    z1 = temp_sort[i].z;
    size1 = (z1 - neutral) / z1 * deep;
    
    randomStep = i;
    do {
        ii = i - Random(int(randomStep));
        z2 = temp_sort[ii].z;
        size2 = (z2 - neutral) / z2 * deep;
        
        if (size1 * size2 > 0) {  // Same side of focal plane
            sizeCompare = (size1 > 0) ? size2 / size1 : size1 / size2;
            intDiff = int((1.0f - sizeCompare) * 500);
            intDiff *= intDiff;
            done = (intDiff < Random(10000));
        }
        randomStep = int(randomStep * 0.7 - 1.0);
    } while (!done && randomStep > 0);
    
    swap(temp_sort[i], temp_sort[ii]);
}
```

**This is a modified Fisher-Yates shuffle** where swaps are only accepted if the two pixels have:
1. Same sign of blur (same side of focal plane), AND
2. Similar blur magnitude (probabilistically)

**Acceptance probability**: 
$$P_{accept} = \frac{intDiff^2}{10000} = \frac{\left[(1 - sizeCompare) \cdot 500\right]^2}{10000}$$

When $sizeCompare = 1$ (identical blur): $intDiff = 0$, $P_{accept} = 1$ (always accept).
When $sizeCompare = 0$ (very different blur): $intDiff = 250000$, $P_{accept} \approx 0$ (rarely accept).

**Decay**: `randomStep` decays by $0.7x - 1$ each iteration, guaranteeing termination.

**Purpose**: The shuffle randomizes the processing order for Phase III while keeping pixels with similar blur grouped together. This prevents sharp edges in the bokeh accumulation.⁴

---

## 6. Phase III: Reversed Bokeh Blur

### 6.1 Algorithm

For each pass, process pixels in the **shuffled Z-order** (back to front):

```cpp
quint64 index = i * screenRegion.height + j;
quint64 ii = temp_sort[sortBufferSize - index - 1].i;  // Reverse order
int x = ii % imageWidth;
int y = ii / imageWidth;
```

**Why reversed?** Processing back-to-front ensures that blurry background pixels are blended **over** sharp foreground pixels, simulating how a real camera lens integrates light.

### 6.2 Bokeh Disc Rendering

For each processed pixel, render a circular disc onto its neighborhood:

```cpp
float blur = fabs(z - neutral) / z * deep + 1.0f;  // +1.0 ensures minimum blur
if (blur > maxRadius) blur = maxRadius;
int size = int(blur);

// Normalization factor
float factor = (M_PI * (blur * blur - blur) + 1.0f) / blurOpacity;
```

**Disc test**: Only pixels within the disc radius contribute:
```cpp
float r2 = dx * dx + dy * dy;
if (blur * blur > r2) {  // Inside disc
    float r = sqrt(r2);
    float op = clamp(blur - r, 0.0f, 1.0f) / factor;
    image->BlendPixelPostImage(xx, yy, op, centerColor);
}
```

**Opacity formula**: 
$$op = \frac{\text{clamp}(blur - r,\; 0,\; 1)}{factor}$$

This creates a **linear falloff from center to edge** of the bokeh disc.

**Normalization factor**: The `factor` term accounts for disc area. As blur increases, the disc area grows as $\pi \cdot blur^2$. The factor divides by this area (with corrections) so that the total accumulated opacity remains consistent regardless of disc size.⁵

### 6.3 Multi-Pass Accumulation

`numberOfPasses` controls how many times the bokeh blur is applied. More passes = smoother, more filled-in bokeh discs. Each pass uses the **same shuffled order**, but because `BlendPixelPostImage` accumulates onto the image, successive passes build up the bokeh shape.

---

## 7. Memory Layout

| Buffer | Type | Size | Purpose |
|--------|------|------|---------|
| `temp_image` | `sRGBFloat` | W × H | Phase I accumulation buffer |
| `temp_alpha` | `unsigned short` | W × H | Alpha channel backup |
| `temp_sort` | `sSortZ<float>` | regionW × regionH | Z-sorted pixel indices |

Total memory: `W × H × (12 + 2 + 8)` bytes ≈ 22 bytes/pixel. For 4K (8.3M pixels): ~180 MB.

---

## 8. Footnotes: Known Issues

¹ **Blur formula approximation**: The formula $\frac{|z - z_{focus}|}{z} \cdot d_{deep}$ is a simplified model. A more accurate thin-lens model would be $CoC = \frac{|z - z_{focus}|}{z \cdot z_{focus}} \cdot \frac{f^2}{N}$, where $f$ is focal length and $N$ is f-stop. The current model conflates focal length and aperture into a single `deep` parameter.⁶

² **Signed blur for focal plane detection**: The signed blur $(z - neutral) / z \cdot deep$ is a clever trick. Positive = in front of focal plane, negative = behind. The product `blur1 * blur2` instantly detects when two pixels are on opposite sides. However, this breaks down when $z$ crosses 0 (impossible for positive depths) or when `neutral` is negative (nonsensical).

³ **Depth weighting can over-attenuate**: The scaling `weight2 * 10.0f` amplifies small differences. When $blur_1 / blur_2 = 0.9$, $weight2 = 0.2$, multiplied by 10 → weight doubled. When $blur_1 / blur_2 = 1.1$, $weight2 = 0$, weight zeroed. This is a very sharp cutoff for pixels with slightly different blur radii.⁷

⁴ **Shuffle randomness quality**: The shuffle uses the project's `Random(int)` function (Park-Miller PRNG with modulo bias). For large arrays, this introduces slight non-uniformity. More importantly, the acceptance probability formula `intDiff * intDiff < Random(10000)` means that when `intDiff > 100`, acceptance probability drops below 1%. With `intDiff = 500 * (1 - sizeCompare)`, this happens when $sizeCompare < 0.8$ — i.e., pixels with >20% blur difference are rarely swapped.⁸

⁵ **Bokeh factor derivation**: The normalization factor $(\pi \cdot (blur^2 - blur) + 1) / blurOpacity$ approximates disc area. For large blur: factor ≈ $\pi \cdot blur^2 / blurOpacity$. For blur = 1: factor = 1 / blurOpacity. The `-blur` term is a correction for small radii. This is heuristic rather than derived from physical optics.⁹

⁶ **QuickSort starts at index 1, not 0**: 
```cpp
QuickSortZBuffer(temp_sort.data(), 1, sortBufferSize - 1);
```
Element 0 is **never sorted**. It remains in its original position (top-left pixel of screenRegion). While Phase II's shuffle processes all elements, starting the sort at index 1 means the array is not fully sorted before shuffling. If `sortBufferSize` = 1, the sort is a no-op. If `sortBufferSize` = 2, only element 1 is "sorted" (trivially).¹⁰

⁷ **QuickSort can stack overflow on sorted input**: The recursive QuickSort has no depth limit or tail-call optimization. On already-sorted (or reverse-sorted) Z data — common for images with clear foreground/background separation — the recursion depth can reach $O(n)$ where $n = W \times H$. For a 4K image region (8M pixels), this would overflow the call stack. The subsequent shuffle randomizes the array, but the **initial** sort on nearly-sorted data is the dangerous case.¹¹

⁸ **Phase III loop order**: The outer loop iterates over `i` (width), inner over `j` (height). The index calculation is `index = i * height + j`, and pixels are accessed in **reverse Z-order** via `temp_sort[sortBufferSize - index - 1]`. Because the outer loop is sequential and the inner loop is OpenMP-parallelized, different columns are processed concurrently. This is safe because `BlendPixelPostImage` blends atomically (or at least, race conditions produce acceptable noise in bokeh).¹²

⁹ **Preview refresh rate scaling**: 
```cpp
lastRefreshTime = timerRefresh.elapsed() * 20.0;
if (lastRefreshTime < 100) lastRefreshTime = 100;
```
The refresh interval grows by 20× the elapsed time of the previous refresh, with a 100ms floor. This means preview updates get progressively slower — after a 50ms render, next refresh is in 1 second. After a 100ms render, next refresh is in 2 seconds. This is an aggressive throttling mechanism that may make the UI feel unresponsive during long renders.¹³

¹⁰ **Z = 0 pixels are silently skipped**: Both Phase I and Phase III skip pixels with `z < 1e-14f`. These are typically background/sky pixels with infinite depth. They receive **no DOF blur at all**, remaining perfectly sharp regardless of focal settings. This is physically incorrect — background pixels at infinity should be maximally blurred when focused on a near object.¹⁴

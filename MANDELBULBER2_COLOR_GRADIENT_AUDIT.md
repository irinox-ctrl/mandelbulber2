# MANDELBULBER2 COLOR GRADIENT SYSTEM: Developer Guide

**Datum**: 2026-04-22  
**Bestanden**: `color_structures.hpp`, `color_gradient.h/cpp`  
**Scope**: Color data types, gradient interpolation, serialization, palette system  
**Focus**: Developer guide — how it works, how to extend it, how to use it  

---

## 1. Color Data Types (`color_structures.hpp`)

### 1.1 The `tsRGB<T>` Template

```cpp
template <typename T>
struct tsRGB {
    T R, G, B;
    tsRGB(T r, T g, T b) : R(r), G(g), B(b) {}
    tsRGB() { R = 0; G = 0; B = 0; }
};
```

| Alias | Type | Range | Typical Use |
|-------|------|-------|-------------|
| `sRGB8` | `tsRGB<quint8>` | 0–255 | Display buffers, file I/O |
| `sRGB16` | `tsRGB<quint16>` | 0–65535 | 16-bit intermediate, gamma table |
| `sRGBFloat` | `tsRGB<float>` | 0.0–1.0+ | HDR rendering, calculations |
| `sRGB` | `tsRGB<qint32>` | 0–65535 | Internal gradient storage |

**Why `qint32` for `sRGB`?** The gradient system stores colors as 32-bit signed integers internally, but only uses the 0–65535 range. This is historical — it allows negative intermediate values during interpolation without overflow.¹

### 1.2 The `tsRGBA<T>` Template

Same as `tsRGB` but with an alpha channel. **Important**: default alpha values differ by type:

| Type | Default Alpha |
|------|--------------|
| `sRGBA8` | 255 (fully opaque) |
| `sRGBA16` | 65535 (fully opaque) |
| `sRGBAFloat` | 1.0 (fully opaque) |

### 1.3 Conversion Functions

```cpp
sRGBFloat toRGBFloat(const sRGB16 &c);   // c.R / 65536.0
sRGBFloat toRGBFloat(const sRGB8 &c);    // c.R / 256.0
sRGB8 toRGB8(const sRGBFloat &c);        // int(c.R * 255.0)
```

**Usage pattern in renderer**:
```cpp
sRGBFloat hdrPixel = imageFloat[pixelIndex];
sRGB8 displayPixel = toRGB8(hdrPixel);  // For screen output
```

---

## 2. The Gradient Class (`cColorGradient`)

### 2.1 Core Concept

A gradient is a **sorted list of color stops** on a `[0.0, 1.0]` axis. Each stop has:
- A color (`sRGB` — 32-bit integer, 0–65535 per channel)
- A position (`float` in [0.0, 1.0])

The first stop is always at `0.0`, the last at `1.0`.²

```cpp
cColorGradient gradient;
gradient.AddColor(sRGB(255, 0, 0), 0.0f);    // Red at start
gradient.AddColor(sRGB(0, 255, 0), 0.5f);    // Green at middle
gradient.AddColor(sRGB(0, 0, 255), 1.0f);    // Blue at end
```

### 2.2 Internal Data Layout

```cpp
class cColorGradient {
    QList<sColor> colors;        // Insertion order (unsorted)
    QList<sColor> sortedColors;  // Sorted by position (cached)
    bool sorted;                 // Dirty flag for lazy sorting
    bool grayscale;              // Force all colors to grayscale
};
```

**Lazy sorting**: `sortedColors` is only rebuilt when `SortGradient()` is called and `sorted == false`. This amortizes the `O(n log n)` sort cost across multiple color queries.

### 2.3 Query API

| Method | Returns | Use Case |
|--------|---------|----------|
| `GetColor(pos, smooth)` | `sRGB` | Integer color for UI |
| `GetColorFloat(pos, smooth)` | `sRGBFloat` | Float color for renderer |
| `GetGradient(length, smooth)` | `QVector<sRGB>` | Pre-computed palette lookup table |

**The `smooth` parameter**:
- `false` → Linear interpolation
- `true` → Cosine ease-in-out (smoothstep)

```cpp
// smooth interpolation formula:
float delta = (pos - pos1) / (pos2 - pos1);
delta = 0.5f * (1.0f - cosf(delta * M_PI));  // smoothstep
```

### 2.4 Palette Iterator

```cpp
int PaletteIterator(int paletteIndex, float colorPosition) const {
    int newIndex = paletteIndex;
    while (newIndex < sortedColors.size() - 1 
           && colorPosition > sortedColors[newIndex + 1].position) {
        newIndex++;
    }
    return newIndex;
}
```

This is an **incremental search** starting from a known index. When iterating through a gradient sequentially (e.g., building a lookup table), pass the previous index as `paletteIndex` for `O(1)` amortized cost per sample instead of `O(n)` binary search.

**Usage pattern**:
```cpp
int paletteIndex = 0;
for (int i = 0; i < length; i++) {
    float pos = i * step;
    paletteIndex = PaletteIterator(paletteIndex, pos);
    sRGB color = Interpolate(paletteIndex, pos, smooth);
}
```

---

## 3. Serialization Format

### 3.1 String Encoding

Gradients are serialized as space-separated tokens:

```
"pos0 RRGGBB pos1 RRGGBB pos2 RRGGBB ..."
```

- Position: integer `0–10000` (represents `0.0–1.0`)
- Color: 6-digit hex `RRGGBB`

**Example**:
```
"0 ff0000 5000 00ff00 10000 0000ff"
```
→ Red at 0.0, Green at 0.5, Blue at 1.0

### 3.2 Why the last color is implicit

The last stop is **always at position 1.0** and matches the first stop's color. This creates a **looping/cyclic gradient** by default. When deserializing, the code appends the first color at position 1.0:

```cpp
if (i == 1) {
    sColor lastColor = colors.first();
    lastColor.position = 1.0;
    colors.append(lastColor);
}
```

**For developers**: If you want a non-looping gradient, you must explicitly add a different color at 1.0.

---

## 4. Grayscale Mode

```cpp
gradient.SetGrayscale(true);
gradient.AddColor(sRGB(255, 128, 64), 0.5f);
// Internally stored as: sRGB(149, 149, 149)
```

When grayscale mode is enabled, every added/modified color is converted via:
```cpp
int avg = (R + G + B) / 3;
R = G = B = avg;
```

This is applied at **storage time**, not at query time. The original color information is lost.

---

## 5. How the Renderer Uses Gradients

### 5.1 Typical Flow

1. **UI** → User edits gradient in `cGradientEditWidget`
2. **Parameters** → Gradient serialized to string, stored in `cParameterContainer`
3. **Render setup** → `cColorGradient::SetColorsFromString()` rebuilds the gradient
4. **Per pixel** → `fractOut.colorIndex` (0.0–1.0) is looked up via `GetColorFloat(colorIndex, smooth)`
5. **Coloring** → The returned `sRGBFloat` is multiplied into the rendered pixel

### 5.2 Performance Consideration

For the renderer (which calls `GetColorFloat()` millions of times), it's better to pre-compute a lookup table:

```cpp
// During render setup:
QVector<sRGB> palette = gradient.GetGradient(65536, true);  // 16-bit LUT

// Per pixel (fast path):
int index = int(colorIndex * 65535.0f);
sRGB color = palette[qBound(0, index, 65535)];
```

Mandelbulber2 uses this pattern internally — the gradient is typically pre-sampled into a texture or LUT before rendering starts.

---

## 6. Extension Recipes

### 6.1 Adding a new interpolation mode

Currently only linear and cosine smoothstep are supported. To add cubic interpolation:

```cpp
// In color_gradient.h, add to enum or parameter:
sRGB InterpolateCubic(int paletteIndex, float pos) const;

// In color_gradient.cpp:
sRGB cColorGradient::InterpolateCubic(int paletteIndex, float pos) const {
    // Need 4 points for cubic: prev, curr, next, nextnext
    sRGB c0 = sortedColors[qMax(0, paletteIndex - 1)].color;
    sRGB c1 = sortedColors[paletteIndex].color;
    sRGB c2 = sortedColors[paletteIndex + 1].color;
    sRGB c3 = sortedColors[qMin(sortedColors.size()-1, paletteIndex + 2)].color;
    
    float t = (pos - pos1) / (pos2 - pos1);
    // Catmull-Rom or cubic Hermite interpolation...
}
```

Then modify `Interpolate()` and `InterpolateFloat()` to dispatch based on a new mode parameter.

### 6.2 Adding HSL/HSV color space support

The current system interpolates in **RGB space**, which can produce muddy browns when transitioning between saturated colors. To interpolate in HSL:

```cpp
sRGB InterpolateHSL(int paletteIndex, float pos, bool smooth) const {
    // 1. Convert c1 and c2 to HSL
    // 2. Interpolate H (with shortest-path wrap), S, L
    // 3. Convert back to RGB
    // 4. Return
}
```

**Note**: Hue interpolation requires special handling because hue is cyclic (0° = 360°).

### 6.3 Adding alpha gradient support

The current `sColor` uses `sRGB` (no alpha). To support alpha gradients:

```cpp
struct sColor {
    sRGBA color;      // Change from sRGB to sRGBA
    float position;
};
```

All serialization, interpolation, and UI code would need updates.

---

## 7. Footnotes: Known Issues

¹ **`sRGB` uses `qint32` internally.** The negative range is never used in practice but allows intermediate calculations without overflow. Converting from `sRGBFloat` to `sRGB` requires clamping to [0, 65535].

² **Constructor enforces two stops at 0.0 and 1.0.** You cannot create an empty gradient or a single-stop gradient. `RemoveColor()` refuses to delete if fewer than 3 colors would remain.

³ **`SortGradient()` creates a local `QMutex`.** The mutex is constructed on the stack inside the function, so it provides no actual thread safety between concurrent calls. The `sorted` flag itself is also not atomic.

⁴ **`Interpolate()` for the last element uses `paletteIndex - 1`.** If the gradient has only 2 stops and `paletteIndex == 1` (the last), this accesses index 0 correctly. But if somehow `sortedColors.size() == 1`, `paletteIndex - 1 == 0` would still be valid — however, a 1-stop gradient should never occur due to constructor enforcement.

⁵ **`GetColorByIndex` and `GetPositionByIndex` fallback to index 1 (not `size()-1`).** If you request an index beyond bounds, you get the second color, not the last. This is inconsistent with typical "clamp to last" behavior.

⁶ **`CorrectPosition()` can theoretically loop infinitely** if all positions from 0.0 to 1.0 are occupied with 0.0001 spacing. With 10,000 colors at exactly 0.0001 intervals, the `do-while` has no room to nudge and would spin forever.

⁷ **`SetColorsFromString()` silently drops the last position if `split.size()` is even.** The format expects pairs of `(position, color)`, so an odd number of tokens means the last position has no matching color and is ignored.

⁸ **`toRGB8(sRGBFloat)` does `int(c.R * 255.0)` without clamping.** If `c.R > 1.0`, the result exceeds 255 and wraps modulo 256 when cast to `quint8`. Use `qBound(0, int(c.R * 255.0), 255)` for safety.

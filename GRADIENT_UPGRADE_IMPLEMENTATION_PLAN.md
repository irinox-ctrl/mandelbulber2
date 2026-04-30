# GRADIENT UPGRADE - VOORZICHTIG IMPLEMENTATION PLAN

**Datum**: 2026-04-29
**Status**: PLANNING FASE - GEEN CODE CHANGES NOG
**Backup**: mandelbulber2_v2_experiment_backup_gradient_upgrade_20260429_172853.tar.gz (602MB)

---

## VEILIGHEIDS PROTOCOL

### VOOR ELKE CODE CHANGE:
1. ✅ Lees EERST bestaande code volledig
2. ✅ Begrijp ALLE dependencies
3. ✅ Test backward compatibility strategie
4. ✅ Maak lokale backup van file
5. ✅ Schrijf nieuwe code
6. ✅ Compile test
7. ✅ Runtime test met bestaande .fract files

### ROLLBACK PLAN:
```bash
# Als iets misgaat:
cd /home/joeri
tar -xzf mandelbulber2_v2_experiment_backup_gradient_upgrade_20260429_172853.tar.gz
# Restore complete
```

---

## PHASE 1: ENHANCED COLOR STOP SYSTEM (WEEK 1-2)

### STAP 1: Extend ColorStop Structure (DAY 1)

**Files to modify**:
- `src/color_gradient.h` - Add new struct members
- `src/color_gradient.cpp` - Update methods

**Strategy**: ADDITIVE ONLY - geen breaking changes

**Current Structure**:
```cpp
struct sColor {
    sRGB color;        // RGB 0-255
    float position;    // 0.0 - 1.0
};
```

**New Structure** (backward compatible):
```cpp
struct sColor {
    // EXISTING (unchanged):
    sRGB color;        // RGB 0-255
    float position;    // 0.0 - 1.0

    // NEW (with defaults for backward compat):
    float midpoint = 0.5f;     // Blend bias (default = 50%)
    int blendMode = 0;         // 0=LINEAR (current behavior)
    int colorSpace = 0;        // 0=RGB (current behavior)

    // Constructor for old code compatibility:
    sColor(sRGB c, float pos)
        : color(c), position(pos), midpoint(0.5f),
          blendMode(0), colorSpace(0) {}

    // New constructor with all params:
    sColor(sRGB c, float pos, float mid, int blend, int space)
        : color(c), position(pos), midpoint(mid),
          blendMode(blend), colorSpace(space) {}
};
```

**SAFETY CHECK**:
- Bestaande code gebruikt `sColor(color, position)` → blijft werken
- Default values geven EXACT current behavior
- sizeof(sColor) verandert → test alignment!

---

### STAP 2: Add Blend Mode Enums (DAY 1)

**Add to color_gradient.h**:
```cpp
namespace GradientBlend {
    enum Mode {
        LINEAR = 0,      // Current behavior (lerp)
        SMOOTH = 1,      // Current smooth mode (cosine)
        EASE_IN = 2,     // Cubic ease-in
        EASE_OUT = 3,    // Cubic ease-out
        EASE_IN_OUT = 4, // S-curve
        HSV_CW = 5,      // HSV clockwise
        HSV_CCW = 6      // HSV counter-clockwise
    };

    enum ColorSpace {
        RGB = 0,         // Current behavior
        HSV = 1,
        // LAB = 2,      // Future
    };
}
```

**VEILIG**: Pure additions, geen bestaande code geraakt

---

### STAP 3: Update Interpolation Function (DAY 2)

**CRITICAL**: Dit is de kernfunctie - MOET backward compatible blijven!

**Current code** (`src/color_gradient.cpp:186`):
```cpp
sRGBFloat cColorGradient::InterpolateFloat(int paletteIndex, float pos, bool smooth) const
{
    // ... existing code ...
    float delta = (pos - pos1) / (pos2 - pos1);
    if (smooth) delta = 0.5f * (1.0f - cosf(delta * float(M_PI)));
    // ... rest ...
}
```

**New code** (BACKWARD COMPATIBLE):
```cpp
sRGBFloat cColorGradient::InterpolateFloat(int paletteIndex, float pos, bool smooth) const
{
    // Get stops
    const sColor &stop1 = sortedColors[paletteIndex];
    const sColor &stop2 = sortedColors[paletteIndex + 1];

    // Calculate base delta
    float delta = (pos - stop1.position) / (stop2.position - stop1.position);

    // Apply midpoint bias (NEW)
    if (stop1.midpoint != 0.5f) {
        // Adjust delta based on midpoint
        if (delta < stop1.midpoint) {
            delta = 0.5f * (delta / stop1.midpoint);
        } else {
            delta = 0.5f + 0.5f * ((delta - stop1.midpoint) / (1.0f - stop1.midpoint));
        }
    }

    // Apply blend mode (NEW - but backward compatible!)
    int blendMode = stop1.blendMode;
    if (smooth && blendMode == GradientBlend::LINEAR) {
        blendMode = GradientBlend::SMOOTH;  // Legacy smooth flag
    }

    delta = ApplyBlendMode(delta, blendMode);

    // Color interpolation (with color space support)
    return InterpolateColors(stop1.color, stop2.color, delta, stop1.colorSpace);
}
```

**BACKWARD COMPAT CHECK**:
- Old code: `midpoint=0.5, blendMode=0` → EXACT current behavior
- Legacy `smooth` flag still works → triggers SMOOTH mode
- New features only active if explicitly set

---

### STAP 4: Helper Functions (DAY 2-3)

**Add nieuwe functies** (geen bestaande code wijzigen):

```cpp
// In color_gradient.cpp

float cColorGradient::ApplyBlendMode(float t, int mode) const
{
    switch (mode) {
        case GradientBlend::LINEAR:
            return t;  // No change

        case GradientBlend::SMOOTH:
            return 0.5f * (1.0f - cosf(t * M_PI));  // Current smooth

        case GradientBlend::EASE_IN:
            return t * t * t;

        case GradientBlend::EASE_OUT:
            return 1.0f - pow(1.0f - t, 3.0f);

        case GradientBlend::EASE_IN_OUT:
            return t < 0.5f
                ? 4.0f * t * t * t
                : 1.0f - pow(-2.0f * t + 2.0f, 3.0f) / 2.0f;

        default:
            return t;
    }
}

sRGBFloat cColorGradient::InterpolateColors(
    sRGB c1, sRGB c2, float t, int colorSpace) const
{
    if (colorSpace == GradientBlend::HSV) {
        // Convert to HSV, lerp, convert back
        sHSV hsv1 = RGBtoHSV(c1);
        sHSV hsv2 = RGBtoHSV(c2);
        sHSV result = LerpHSV(hsv1, hsv2, t);
        return HSVtoRGB(result);
    }
    else {
        // RGB lerp (current behavior)
        float nDelta = 1.0f - t;
        sRGBFloat result;
        result.R = (c1.R * nDelta + c2.R * t) / 256.0f;
        result.G = (c1.G * nDelta + c2.G * t) / 256.0f;
        result.B = (c1.B * nDelta + c2.B * t) / 256.0f;
        return result;
    }
}
```

**VEILIG**: Pure additions, bestaande code ongewijzigd

---

### STAP 5: String Serialization Update (DAY 3-4)

**CRITICAL**: File format backward compatibility!

**Current format**:
```
"0 FF0000 5000 00FF00 10000 0000FF"
pos RGB  pos  RGB    pos   RGB
```

**New format** (EXTENDED):
```
Version 2:
"2 0 FF0000 50.0 0 0 5000 00FF00 50.0 1 0 10000 0000FF 50.0 0 0"
v pos RGB  mid  bld cs pos RGB   mid  bld cs pos  RGB   mid  bld cs
```

**Implementation**:
```cpp
QString cColorGradient::GetColorsAsString()
{
    // Detect if we need V2 format
    bool needsV2 = false;
    for (auto &stop : sortedColors) {
        if (stop.midpoint != 0.5f || stop.blendMode != 0 || stop.colorSpace != 0) {
            needsV2 = true;
            break;
        }
    }

    if (needsV2) {
        return GetColorsAsStringV2();
    } else {
        return GetColorsAsStringV1();  // Exact current format!
    }
}

void cColorGradient::SetColorsFromString(const QString &string)
{
    QStringList parts = string.split(" ");

    // Check version
    if (parts.size() > 0 && parts[0] == "2") {
        SetColorsFromStringV2(string);
    } else {
        SetColorsFromStringV1(string);  // Current parser - unchanged!
    }
}
```

**BACKWARD COMPAT GUARANTEE**:
- Old .fract files → parsed by V1 parser → exact current behavior
- New features → trigger V2 format → new .fract files
- Can always export V1 for compatibility

---

## PHASE 2: GPU/OPENCL INTEGRATION (WEEK 3)

**WAARSCHUWING**: Dit is COMPLEX - OpenCL struct alignment!

### STAP 1: Analyze Current GPU Data Transfer

**Files to examine** (READ ONLY first):
- `src/opencl_dynamic_data.cpp` - Where palette is built
- `opencl/shader_input_data_cl.h` - GPU struct definition
- `opencl/engines/shader_surface_color.cl` - GPU interpolation

**Action**: JUST READ and UNDERSTAND - NO CHANGES yet

---

### STAP 2: Design GPU-Compatible Structure

**Challenge**:
- GPU needs `float4` arrays (current)
- Need to add: midpoint, blendMode, colorSpace
- Alignment must be correct (16-byte boundaries!)

**Proposed**:
```opencl
// Option A: Extend float4 to float8 (wastes memory but simple)
typedef struct {
    float4 color_pos;     // {R, G, B, position}
    float4 metadata;      // {midpoint, blendMode, colorSpace, reserved}
} GradientStopCl;

// Option B: Separate arrays (more complex but efficient)
__global float4 *colorData;   // Current system
__global float4 *metadata;    // New: {midpoint, blendMode, colorSpace, reserved}
```

**Decision**: Start with Option A for safety
**Rollback**: Option B if memory becomes issue

---

### STAP 3: Update GPU Interpolation Kernel

**File**: `opencl/engines/shader_surface_color.cl`

**Current**:
```opencl
float3 GradientInterpolate(int paletteIndex, float pos, bool smooth,
                          int gradientSize, __global float4 *palette)
```

**New** (backward compatible):
```opencl
float3 GradientInterpolate(int paletteIndex, float pos, bool smooth,
                          int gradientSize,
                          __global float4 *colorData,
                          __global float4 *metadata)  // NEW - optional!
{
    // If metadata == NULL → legacy mode (backward compat)
    if (metadata == NULL) {
        // Use current algorithm exactly
        return GradientInterpolateLegacy(paletteIndex, pos, smooth,
                                        gradientSize, colorData);
    }

    // New algorithm with midpoint/blend support
    float4 meta1 = metadata[paletteIndex];
    float midpoint = meta1.x;
    int blendMode = (int)meta1.y;

    // ... new interpolation ...
}
```

**SAFETY**: Dual code path - old path unchanged!

---

## TESTING STRATEGY

### Unit Tests (CREATE NEW FILES):
```cpp
// test/test_gradient_v2.cpp (NEW FILE - no existing code modified)

void TestBackwardCompatibility() {
    // Load old gradient string
    cColorGradient grad;
    grad.SetColorsFromString("0 FF0000 5000 00FF00 10000 0000FF");

    // Sample colors
    sRGBFloat c1 = grad.GetColorFloat(0.25, false);

    // Compare with expected (current behavior)
    assert(abs(c1.R - expected.R) < 0.01);
}

void TestMidpoint() {
    // Create gradient with midpoint shift
    cColorGradient grad;
    grad.AddColor(sRGB(255,0,0), 0.0);

    sColor stop;
    stop.color = sRGB(0,255,0);
    stop.position = 1.0;
    stop.midpoint = 0.3;  // Shift towards red
    grad.AddColorExtended(stop);

    // Test sampling
    sRGBFloat c1 = grad.GetColorFloat(0.5, false);
    // Should be more red than 50/50 mix
}
```

### Integration Tests:
```bash
# Test with existing .fract files
./mandelbulber2 --test test_suite/gradient_tests/*.fract

# Render comparison
./mandelbulber2 --nogui --render old_file.fract -o old_output.png
# (with new code)
./mandelbulber2 --nogui --render old_file.fract -o new_output.png
# Compare: should be IDENTICAL

diff old_output.png new_output.png
# Expected: no difference for legacy files
```

---

## ROLLBACK CHECKPOINTS

### Checkpoint 1: After struct extension
```bash
cp src/color_gradient.h src/color_gradient.h.checkpoint1
cp src/color_gradient.cpp src/color_gradient.cpp.checkpoint1
```

### Checkpoint 2: After interpolation update
```bash
tar -czf checkpoint2_interpolation.tar.gz src/color_gradient.*
```

### Checkpoint 3: After GPU integration
```bash
tar -czf checkpoint3_gpu.tar.gz src/color_gradient.* opencl/engines/shader_surface_color.cl
```

---

## IMPLEMENTATION ORDER (SAFE)

**WEEK 1**: CPU Only - NO GPU CHANGES
1. Day 1: Extend struct, add enums (compile test only)
2. Day 2: Blend mode functions (unit tests)
3. Day 3: Color space conversion (unit tests)
4. Day 4: String serialization (file I/O tests)
5. Day 5: Integration testing, bugfixes

**WEEK 2**: CPU Finalization
1. Day 1-2: Update UI widget (preview only, no saving yet)
2. Day 3-4: Backward compat testing with 100+ .fract files
3. Day 5: Documentation, code review

**WEEK 3**: GPU Integration (IF CPU stable)
1. Day 1-2: Analyze current GPU code (READ ONLY)
2. Day 3: Design GPU struct (PLAN ONLY)
3. Day 4-5: Implement GPU (with dual code path)

**STOP POINTS**:
- After Week 1: Can ship CPU-only version
- After Week 2: Can ship with UI
- Week 3: Optional GPU acceleration

---

## APPROVAL GATES

**Gate 1** (After struct extension):
- [ ] Code compiles without warnings
- [ ] Existing .fract files load correctly
- [ ] Colors render identically to before
- [ ] Unit tests pass (100+ tests)

**Gate 2** (After CPU implementation):
- [ ] All blend modes tested
- [ ] Performance < 2x slowdown
- [ ] Memory < 2x increase
- [ ] NO crashes with legacy files

**Gate 3** (After GPU):
- [ ] GPU rendering matches CPU pixel-perfect
- [ ] OpenCL alignment correct (test on AMD/NVIDIA)
- [ ] Performance within 10% of baseline

---

## STOP IF:
- ❌ Any existing .fract file fails to load
- ❌ Any visual regression in renders
- ❌ Crashes or memory leaks
- ❌ >3x performance degradation
- ❌ GPU alignment issues

→ ROLLBACK and RETHINK

---

## NEXT STEP: WACHT OP APPROVAL

**Ik ga NIET beginnen** tot je zegt:
- "Ja, ga verder met Week 1 Day 1"
- OF je geeft specifieke wijzigingen aan dit plan

**Vragen voor jou**:
1. Is dit plan voorzichtig genoeg?
2. Wil je eerst alleen READ-ONLY code analysis?
3. Moet ik eerst prototype in SEPARATE files (geen bestaande code touch)?

**Status**: WACHTEND OP GOEDKEURING

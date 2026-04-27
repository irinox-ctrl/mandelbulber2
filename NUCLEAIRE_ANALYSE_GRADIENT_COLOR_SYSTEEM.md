# ☢️ NUCLEAIRE ANALYSE: Gradient & Color Systeem — Mandelbulber2 v2

> **Scope:** Elk detail van shader tot renderlijn, alle structs, data flow, GPU/CPU synchronisatie, en alle valkuilen.
> **Datum:** 2026-04-27
> **Doel:** Voorkomen dat upgrades fout lopen door volledige kennis van het systeem.

---

## 📋 INHOUDSOPGAVE

1. [Architectuur Overzicht](#1-architectuur-overzicht)
2. [Kleur Structs & Type System](#2-kleur-structs--type-system)
3. [Het Gradient Systeem (cColorGradient)](#3-het-gradient-systeem-ccolorgradient)
4. [Kleur Conversie (HSV↔RGB)](#4-kleur-conversie-hsvrgb)
5. [Fractal Coloring Pipeline](#5-fractal-coloring-pipeline)
6. [Material Systeem & Gradients](#6-material-systeem--gradients)
7. [Render Worker Pipeline (CPU)](#7-render-worker-pipeline-cpu)
8. [OpenCL GPU Pipeline](#8-opencl-gpu-pipeline)
9. [Data Transfer: CPU → GPU](#9-data-transfer-cpu--gpu)
10. [UI: Gradient Editor](#10-ui-gradient-editor)
11. [Histogram Systeem](#11-histogram-systeem)
12. [Image Buffer System (cImage)](#12-image-buffer-system-cimage)
13. [Kritieke Valkuilen & Gotchas](#13-kritieke-valkuilen--gotchas)
14. [Upgrade Checklist](#14-upgrade-checklist)

---

## 1. ARCHITECTUUR OVERZICHT

Het color/gradient systeem in Mandelbulber2 is **dual-path**: identieke logica bestaat zowel op CPU als GPU (OpenCL). Wijzigingen moeten **ALTIJD** in beide paden worden doorgevoerd.

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                              CPU RENDER PAD                                 │
│  render_worker.cpp → shader_surface_color.cpp → shader_object.cpp          │
│       ↓                    ↓                        ↓                       │
│  fractal_coloring.cpp  cColorGradient           cMaterial                   │
│       ↓                    ↓                        ↓                       │
│  compute_fractal.cpp   color_structures.hpp     color_gradient.cpp/h        │
└─────────────────────────────────────────────────────────────────────────────┘
                                      │
                                      ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                         DATA TRANSFER (OpenCL)                              │
│  opencl_dynamic_data.cpp → BuildMaterialsData()                            │
│       ↓                                                                     │
│  material_cl.h (sMaterialCl) + palette float4 array                         │
└─────────────────────────────────────────────────────────────────────────────┘
                                      │
                                      ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                              GPU RENDER PAD                                 │
│  shader_surface_color.cl → shader_object.cl → shader_light_shading.cl      │
│       ↓                    ↓                        ↓                       │
│  fractal_coloring.cl    GradientInterpolate()   sClGradientsCollection      │
│       ↓                    ↓                        ↓                       │
│  compute_fractal.cl     shader_input_data_cl.h  render_data_cl.h            │
└─────────────────────────────────────────────────────────────────────────────┘
```

### 1.1 Kernregels
- **Rule #1:** Wijzigingen in CPU-logica = wijzigingen in GPU-logica (`.cl` bestanden)
- **Rule #2:** Struct layouts op CPU en GPU moeten **byte-identiek** zijn
- **Rule #3:** Gradient strings zijn het serialisatieformaat tussen UI, settings en runtime
- **Rule #4:** `color_structures.hpp` wordt gedeeld door CPU en GPU (via `opencl_algebra.h`)

---

## 2. KLEUR STRUCTS & TYPE SYSTEM

### 2.1 Basis Kleur Types (`src/color_structures.hpp`)

```cpp
template <typename T>
struct tsRGB { T R, G, B; };

template <typename T>
struct tsRGBA { T R, G, B, A; };

// Type aliases:
using sRGB8   = tsRGB<quint8>;    // 0-255  (UI, preview, 8-bit output)
using sRGB16  = tsRGB<quint16>;   // 0-65535 (16-bit buffers)
using sRGB    = tsRGB<qint32>;    // 0-65535 interne representatie (signed!)
using sRGBFloat = tsRGB<float>;   // 0.0-1.0+ (HDR, shaders)

using sRGBA8   = tsRGBA<quint8>;
using sRGBA16  = tsRGBA<quint16>;
using sRGBAFloat = tsRGBA<float>;
```

### 2.2 Kritieke Details

| Aspect | Waarde | Impact |
|--------|--------|--------|
| `sRGB` is `qint32`, niet `quint32` | Signed 32-bit | Kan negatieve waarden bevatten na berekeningen; clampen vereist |
| `sRGBFloat` conversie | `/ 65536.0` | Niet `/ 255.0` of `/ 256.0`! Interne schaal is 16-bit |
| `toRGB8(sRGBFloat)` | `int(c.R * 255.0)` | Conversie naar 8-bit voor display |
| Alpha defaults | `quint8=255`, `quint16=65535`, `float=1.0` | Verschilt per type! |

### 2.3 Conversiefuncties
```cpp
inline sRGBFloat toRGBFloat(const sRGB &c) {
    return sRGBFloat(c.R / 65536.0, c.G / 65536.0, c.B / 65536.0);
}
inline sRGB8 toRGB8(const sRGB &c) {
    return sRGB8(c.R / 256, c.G / 256, c.B / 256);
}
inline sRGB8 toRGB8(const sRGBFloat &c) {
    return sRGB8(int(c.R * 255.0), int(c.G * 255.0), int(c.B * 255.0));
}
```

**⚠️ VALKUIL:** `sRGB` gebruikt `qint32` (signed). Bij berekeningen kan overflow optreden die niet gedetecteerd wordt. De gradient interpolation in `color_gradient.cpp` doet `int(color1.R * nDelta + color2.R * delta)` — dit werkt omdat de waarden in 0-255 range blijven, maar bij grotere waarden is dit riskant.

---

## 3. HET GRADIENT SYSTEEM (cColorGradient)

### 3.1 Kernstructuur (`src/color_gradient.h`)

```cpp
class cColorGradient {
public:
    struct sColor {
        sRGB color;        // R,G,B in 0-255 range (qint32 per channel)
        float position;    // 0.0 tot 1.0
        static bool lessCompare(sColor a, sColor b) { return a.position < b.position; }
    };

    sRGB GetColor(float position, bool smooth) const;       // Returns 0-255 sRGB
    sRGBFloat GetColorFloat(float position, bool smooth) const; // Returns 0.0-1.0 float
    QVector<sRGB> GetGradient(int length, bool smooth);     // Voor UI preview
    QString GetColorsAsString();                             // Serialisatie
    void SetColorsFromString(const QString &string);         // Deserialisatie

private:
    QList<sColor> colors;        // Ongeordend (bij edits)
    QList<sColor> sortedColors;  // Geordend (voor lookup)
    bool grayscale;
    bool sorted;
};
```

### 3.2 Serialisatie Formaat

Het gradient formaat is een **spatie-gescheiden string**:
```
"<positie1*10000> <RRGGBB_hex> <positie2*10000> <RRGGBB_hex> ..."
```

**Voorbeeld (default surface gradient):**
```
"0 fd6029 1000 698403 2000 fff59b 3000 f5bd22 4000 0b5e87 5000 c68876 6000 a51c64 7000 3b9fee 8000 d4ffd4 9000 aba53c"
```

**Decodeer regels:**
1. Positie = integer / 10000.0f (dus `1000` = 0.1, `5000` = 0.5)
2. Kleur = hex RRGGBB, geparsed als `colorHex / 65536`, `(colorHex / 256) % 256`, `colorHex % 256`
3. **LAATSTE kleur wordt NIET opgeslagen** — de laatste kleur is altijd een kopie van de eerste met positie 1.0
4. Minimaal 2 kleuren vereist (positie 0.0 en 1.0)

### 3.3 Interpolatie Algoritme

```cpp
sRGB cColorGradient::Interpolate(int paletteIndex, float pos, bool smooth) const {
    sRGB color1 = sortedColors[paletteIndex].color;
    sRGB color2 = sortedColors[paletteIndex + 1].color;
    float pos1 = sortedColors[paletteIndex].position;
    float pos2 = sortedColors[paletteIndex + 1].position;
    
    float delta = (pos - pos1) / (pos2 - pos1);
    if (smooth) delta = 0.5f * (1.0f - cosf(delta * float(M_PI)));
    
    float nDelta = 1.0f - delta;
    color.R = int(color1.R * nDelta + color2.R * delta);  // LINEAIR in RGB!
    color.G = int(color1.G * nDelta + color2.G * delta);
    color.B = int(color1.B * nDelta + color2.B * delta);
}
```

**⚠️ VALKUILEN:**
- Interpolatie is **RGB lineair**, niet in perceptuele ruimte (Lab/LCh)
- `smooth` gebruikt cosine ease-in-out, niet spline
- `GetColorFloat()` deelt door `256.0f` (niet `255.0f`), dus max output is `255/256 = 0.996`, nooit exact 1.0
- Bij `paletteIndex == gradientSize - 1` wordt `paletteIndex - 1` gebruikt (laatste kleur overslaan)

### 3.4 Position Correctie

```cpp
float cColorGradient::CorrectPosition(float position, int ignoreIndex) {
    position = qBound(0.0f, position, 1.0f);
    do {
        for (int i = 0; i < colors.size(); i++) {
            if (i == ignoreIndex) continue;
            if (fabsf(position - colors[i].position) < 0.0001f) {
                position += (position < 0.5f) ? 0.0001f : -0.0001f;
            }
        }
    } while (positionIncorrect);
}
```

**Wat dit doet:** Voorkomt dat twee kleuren exact dezelfde positie hebben (minimale afstand 0.0001).

---

## 4. KLEUR CONVERSIE (HSV↔RGB)

### 4.1 CPU (`src/hsv2rgb.cpp`)

```cpp
sRGBFloat Hsv2rgb(float hue, float sat, float val) {
    float h = hue / 60.0f;
    int i = int(floorf(hue / 60.0f));
    float f = h - i;
    float p = val * (1 - sat);
    float q = val * (1 - (sat * f));
    float t = val * (1 - (sat * (1 - f)));
    switch (i) {
        case 0: return sRGBFloat(val, t, p);
        case 1: return sRGBFloat(q, val, p);
        case 2: return sRGBFloat(p, val, t);
        case 3: return sRGBFloat(p, q, val);
        case 4: return sRGBFloat(t, p, val);
        case 5: return sRGBFloat(val, p, q);
    }
}
```

### 4.2 GPU (`opencl/engines/shader_hsv2rgb.cl`)

```opencl
float3 Hsv2rgb(float hue, float sat, float val) {
    float h = hue / 60.0f;
    int i = (int)h;  // Let op: geen floorf() in OpenCL!
    // ... identieke logica
}
```

**⚠️ VALKUIL:** OpenCL versie cast naar `int` zonder `floorf()`. Bij negatieve hue waarden gedraagt dit zich anders dan C++ `floorf()`.

### 4.3 Gebruik van HSV
- **Chromatic aberration** in DOF monte carlo mode (`render_worker.cpp`)
- **Iridescence** shader (`shader_iridescence.cpp` / `.cl`)
- **Glow** effecten
- Niet gebruikt voor gradient interpolatie!

---

## 5. FRACTAL COLORING PIPELINE

### 5.1 Color Index Berekening

De `colorIndex` is een `double` (CPU) of `cl_float` (GPU) die de positie in het gradient bepaalt.

**Stroom:**
```
fractal iteratie → colorIndex (double) → fmod(fabs(colorIndex), 248*256)
                                              ↓
                 colorPosition = fmod(nrCol / 256.0 / 10.0 * coloring_speed + paletteOffset, 1.0)
                                              ↓
                 gradient.GetColorFloat(colorPosition, false)
```

### 5.2 Drie Modi (`src/fractal_coloring.cpp`)

| Modus | Wanneer | Formule |
|-------|---------|---------|
| **Extra Color** | `fractalColoring.extraColorEnabledFalse == true` | Volledig configureerbaar met orbit traps, aux color, XYZ bias, iter scale, etc. |
| **Hybrid** | `isHybrid == true` | `colorMin * 1000 + mboxColor * 100 + r2 * 5000` |
| **Standard** | Anders | Formula-specifiek (ABox, IFS, AmazingSurf, etc.) |

### 5.3 Extra Color Mode Details

Dit is de meest complexe mode met **29 boolean flags** en **25 double parameters**.

Belangrijkste componenten:
1. **Initial color value** — basis offset
2. **Init cond** — afhankelijk van C-vector (icRad, icXYZ)
3. **Orbit trap** — `colorMin * orbitTrapWeight`
4. **Aux color** — `extendedAux.color * auxColorWeight + extendedAux.colorHybrid * auxColorHybridWeight`
5. **Radius** — `r * radWeight` (optioneel / 1e13, optioneel ^2)
6. **Radius/DE** — `(r / DE) * radDivDeWeight`
7. **XYZ bias** — `(x,y,z) * xyz000` met optionele fabs, square
8. **Iter controls** — add en scale gebaseerd op iteratie nummer
9. **Global palette controls** — add curve, parabola, cos, round
10. **Min/max clamp** — `minColorValue` tot `maxColorValue`

**Eindformule:** `colorIndex = colorValue * 256.0`

### 5.4 OpenCL Versie (`opencl/engines/fractal_coloring.cl`)

Exact dezelfde logica als CPU, maar:
- Gebruikt `sExtendedAuxCl` struct
- `colorMin` wordt in hybrid mode geclamped: `min(100.0f, colorMin)`
- `r2` wordt geclamped: `min(r / fabs(DE), 20.0f)`

---

## 6. MATERIAL SYSTEEM & GRADIENTS

### 6.1 cMaterial (`src/material.h`)

Elk materiaal heeft **7 gradients**:

```cpp
class cMaterial {
    cColorGradient gradientSurface;      // Oppervlak kleur
    cColorGradient gradientSpecular;     // Specular highlight kleur
    cColorGradient gradientDiffuse;      // Diffuse (ruwheid van oppervlak)
    cColorGradient gradientLuminosity;   // Zelflichtend
    cColorGradient gradientRoughness;    // Oppervlakte ruwheid
    cColorGradient gradientReflectance;  // Reflectie sterkte
    cColorGradient gradientTransparency; // Transparantie
    
    // Enable flags (ELKE gradient heeft een eigen boolean!)
    bool surfaceGradientEnable;      // DEFAULT: true
    bool specularGradientEnable;     // DEFAULT: false
    bool diffuseGradientEnable;      // DEFAULT: false
    bool luminosityGradientEnable;   // DEFAULT: false
    bool roughnessGradientEnable;    // DEFAULT: false
    bool reflectanceGradientEnable;  // DEFAULT: false
    bool transparencyGradientEnable; // DEFAULT: false
    
    // Zorgvuldig: gradient_opacity parameters bestaan ook (niet altijd gebruikt!)
    float paletteOffset;      // Offset in gradient (0-256)
    float coloring_speed;     // Snelheid van kleurverloop
    bool useColorsFromPalette; // Moet gradient gebruikt worden?
};
```

### 6.2 Parameter Naming Conventie

Alle materiaal parameters volgen het patroon:
```
mat{materialId}_{parameter_name}
```

Voorbeelden:
- `mat1_surface_color_gradient`
- `mat1_surface_gradient_enable`
- `mat1_coloring_palette_offset`
- `mat1_use_colors_from_palette`

### 6.3 Gradient Defaults (`src/initparameters.cpp`)

```cpp
// Surface (default = ingeschakeld, 10 kleuren)
par->addParam("mat1_surface_color_gradient",
    QString("0 fd6029 1000 698403 2000 fff59b 3000 f5bd22 4000 0b5e87 "
            "5000 c68876 6000 a51c64 7000 3b9fee 8000 d4ffd4 9000 aba53c"));
par->addParam("mat1_surface_gradient_enable", true);

// Alle andere (default = 1 kleur wit/zwart, UITgeschakeld)
par->addParam("mat1_specular_gradient", QString("0 ffffff"));
par->addParam("mat1_specular_gradient_enable", false);

par->addParam("mat1_luminosity_gradient", QString("0 000000"));
par->addParam("mat1_luminosity_gradient_enable", false);
// ... etc
```

**⚠️ VALKUIL:** Er zijn ook `*_gradient_opacity` parameters gedefinieerd (regels 2250-2262) maar ze worden **NIET gebruikt** in de huidige shader code! Ze zitten wel in de parameter database.

### 6.4 sGradientsCollection (CPU Shader Input)

```cpp
struct sGradientsCollection {
    sRGBFloat surface;      // Wordt gevuld in SurfaceColour()
    sRGBFloat specular;     // Wordt gevuld in SurfaceColour()
    sRGBFloat diffuse;      // Wordt gevuld in SurfaceColour()
    sRGBFloat luminosity;   // Wordt gevuld in SurfaceColour()
    sRGBFloat roughness;    // Wordt gevuld in SurfaceColour()
    sRGBFloat reflectance;  // Wordt gevuld in SurfaceColour()
    sRGBFloat trasparency;  // Let op: typo in naam! "trasparency" niet "transparency"
};
```

**⚠️ KRITIEKE VALKUIL:** `trasparency` heeft een **typo** — mist een 'n'. Dit zit in `render_worker.hpp` regel 211. Wijzigingen hier breken backwards compatibility.

---

## 7. RENDER WORKER PIPELINE (CPU)

### 7.1 Shader Flow

```
doWork() → per pixel:
    RayMarching() → vindt intersection point
        ↓
    ObjectShader() → hoofd shader
        ↓
    SurfaceColour() → bepaalt kleur + gradients
        ↓
    LightShading() / AuxLightsShader() → licht + specular
        ↓
    SpecularHighlightCombined() → specular met diffuse gradient
        ↓
    VolumetricShader() → transparantie/volume
        ↓
    PutPixelImage() → schrijf naar cImage buffer
```

### 7.2 SurfaceColour Details (`src/shader_surface_color.cpp`)

```cpp
sRGBAFloat cRenderWorker::SurfaceColour(CVector3 point, const sShaderInputData &input, 
                                        sGradientsCollection *gradients) const {
    if (input.material->useColorsFromPalette) {
        // 1. Bereken fractal color index
        Compute<calcModeColouring>(...) → fractOut.colorIndex
        
        // 2. Normaliseer naar 0-1
        double nrCol = fmod(fabs(fractOut.colorIndex), 248.0 * 256.0);
        double colorPosition = fmod(nrCol / 256.0 / 10.0 * coloring_speed + paletteOffset, 1.0);
        
        // 3. Haal gradient kleuren op
        if (input.material->surfaceGradientEnable) {
            colour = input.material->gradientSurface.GetColorFloat(colorPosition, false);
            gradients->surface = colour;
        }
        if (input.material->specularGradientEnable) {
            gradients->specular = input.material->gradientSpecular.GetColorFloat(colorPosition, false);
        }
        // ... etc voor alle 7 gradients
    }
}
```

**Let op:** `smooth = false` — gradient interpolatie is altijd lineair in de renderer, nooit cosine smooth.

### 7.3 ObjectShader Gradient Toepassing (`src/shader_object.cpp`)

```cpp
// Surface color
if (mat->perlinNoiseEnable && mat->perlinNoiseColorEnable) {
    // Perlin noise vervangt fractal coloring — gradient nog steeds gebruikt
    float colorPosition = fmod(perlin * coloring_speed + paletteOffset, 1.0f);
    sRGBFloat gradientColor = gradientSurface.GetColorFloat(colorPosition, false);
} else {
    colour = SurfaceColour(input.point, input, gradients);
    // Textuur blending
    colour.R *= input.texColor.R * texColInt + texColIntN;
}

// Luminosity
if (mat->useColorsFromPalette && mat->luminosityGradientEnable) {
    luminosity.R = texLum.R * lumTexInt + mat->luminosity * gradients->luminosity.R;
}

// Specular (in LightShading)
if (input.material->useColorsFromPalette && input.material->specularGradientEnable) {
    specular.R *= gradients->specular.R;
    specular.G *= gradients->specular.G;
    specular.B *= gradients->specular.B;
}

// Diffuse (in SpecularHighlight)
if (input.material->useColorsFromPalette && input.material->diffuseGradientEnable) {
    diffuse *= 10.0f * (1.1f - (diffuseGradient.R + diffuseGradient.G + diffuseGradient.B) / 3.0f);
}
```

---

## 8. OPENCL GPU PIPELINE

### 8.1 OpenCL Shader Input (`opencl/shader_input_data_cl.h`)

```opencl
typedef struct {
    float3 point;
    float3 viewVector;
    float3 normal;
    // ... textures, etc ...
    __global sMaterialCl *material;
    __global float4 *palette;  // ← ALLE gradients zitten in ÉÉN flat array!
    
    #ifdef USE_SURFACE_GRADIENT
    int paletteSurfaceOffset;
    int paletteSurfaceLength;
    #endif
    #ifdef USE_SPECULAR_GRADIENT
    int paletteSpecularOffset;
    int paletteSpecularLength;
    #endif
    // ... etc voor alle 7 gradients
} sShaderInputDataCl;

typedef struct {
    #ifdef USE_SURFACE_GRADIENT
    float3 surface;
    #endif
    #ifdef USE_SPECULAR_GRADIENT
    float3 specular;
    #endif
    // ... etc
} sClGradientsCollection;
```

### 8.2 Gradient Lookup op GPU (`opencl/engines/shader_surface_color.cl`)

```opencl
float3 GetColorFromGradient(float position, bool smooth, int gradientSize, __global float4 *palette) {
    int paletteIndex = GradientIterator(0, position, gradientSize, palette);
    return GradientInterpolate(paletteIndex, position, smooth, gradientSize, palette);
}

float3 GradientInterpolate(int paletteIndex, float pos, bool smooth, int gradientSize, __global float4 *palette) {
    float3 color1 = palette[paletteIndex].xyz;
    float pos1 = palette[paletteIndex].w;      // positie in .w component
    float3 color2 = palette[paletteIndex + 1].xyz;
    float pos2 = palette[paletteIndex + 1].w;
    
    float delta = (pos - pos1) / (pos2 - pos1);
    if (smooth) delta = 0.5f * (1.0f - cos(delta * M_PI_F));
    
    float nDelta = 1.0f - delta;
    color.s0 = color1.s0 * nDelta + color2.s0 * delta;
    color.s1 = color1.s1 * nDelta + color2.s1 * delta;
    color.s2 = color1.s2 * nDelta + color2.s2 * delta;
    return color;
}
```

### 8.3 Preprocessor Defines voor Gradients

De OpenCL kernel wordt dynamisch gecompileerd met defines op basis van welke features nodig zijn:

```cpp
// In opencl_engine_render_fractal.cpp
#ifdef USE_SURFACE_GRADIENT
    definesCollector += " -DUSE_SURFACE_GRADIENT";
#endif
// ... etc
```

**⚠️ KRITIEKE VALKUIL:** Als je een nieuwe gradient toevoegt, moet je:
1. `USE_XXX_GRADIENT` define toevoegen in de kernel builder
2. `sShaderInputDataCl` uitbreiden met offset/length fields
3. `sClGradientsCollection` uitbreiden
4. `sRenderData` uitbreiden (voor multi-material mode)
5. `BuildMaterialsData()` aanpassen voor offset berekening

---

## 9. DATA TRANSFER: CPU → GPU

### 9.1 BuildMaterialsData (`src/opencl_dynamic_data.cpp`)

Dit is de **belangrijkste** functie voor gradient data transfer.

```cpp
int cOpenClDynamicData::BuildMaterialsData(
    const std::map<int, cMaterial> &materials, const QMap<QString, int> &textureIndexes) {
    
    // Layout per materiaal in GPU buffer:
    // +0  cl_int materialClOffset
    // +4  cl_int paletteItemsOffset
    // +8  cl_int palette_offset_surface
    // +12 cl_int paletteLengthSurface
    // +16 cl_int palette_offset_specular
    // +20 cl_int paletteLengthSpecular
    // +24 sMaterialCl material
    //     ... palettes als cl_float4 array ...
}
```

### 9.2 Palette Flattening

Alle gradienten van één materiaal worden in één flat `cl_float4` array geplaatst:

```cpp
// CPU kant:
QList<cColorGradient::sColor> gradientSurface = material.gradientSurface.GetListOfSortedColors();
QList<cColorGradient::sColor> gradientSpecular = material.gradientSpecular.GetListOfSortedColors();
// ... etc

// Bereken offsets (sequentieel)
paletteOffsetSurface = 0;
paletteSizeSurface = gradientSurface.size();
paletteOffsetSpecular = paletteOffsetSurface + paletteSizeSurface;
paletteSizeSpecular = gradientSpecular.size();
// ... etc

// Converteer naar cl_float4
for (int i = 0; i < paletteSizeSurface; i++) {
    paletteCl[i + paletteOffsetSurface] = toClFloat4(CVector4(
        gradientSurface[i].color.R / 256.0,   // ← Let op: /256.0, niet /255.0!
        gradientSurface[i].color.G / 256.0,
        gradientSurface[i].color.B / 256.0,
        gradientSurface[i].position));
}
```

### 9.3 Dummy Material Fallback

Als een materiaal index niet bestaat, wordt een **dummy** gemaakt:

```cpp
memset(&materialCl, 0, sizeof(materialCl));
paletteOffsetSurface = 0;   paletteSizeSurface = 2;
paletteOffsetSpecular = 2;  paletteSizeSpecular = 2;
paletteOffsetDiffuse = 4;   paletteSizeDiffuse = 2;
// ... etc
// Dummy palette entries: allemaal zwart of wit (afhankelijk van default constructor)
```

**⚠️ KRITIEKE VALKUIL:** Bij toevoegen van een nieuwe gradient moet je:
1. De offset berekening aanpassen in `BuildMaterialsData()`
2. De dummy fallback aanpassen
3. Zorgen dat `totalSizeOfGradients` correct is
4. Anders worden GPU palette lookups **out of bounds**

---

## 10. UI: GRADIENT EDITOR

### 10.1 cGradientEditWidget (`qt/gradient_edit_widget.h`)

```cpp
class cGradientEditWidget : public QWidget {
    cColorGradient gradient;     // Interne gradient
    bool grayscale;              // Alleen grijswaarden?
    bool viewMode;               // Alleen bekijken?
    QString defaultValue;        // Voor reset-to-default
    
    // Toolbar knoppen:
    // - Randomize colors
    // - Randomize colors + positions
    // - Brightness inc/dec
    // - Saturation inc/dec
    // - Invert palette
};
```

### 10.2 Paint Event

```cpp
void cGradientEditWidget::paintEvent(QPaintEvent *event) {
    QVector<sRGB> grad = gradient.GetGradient(gradientWidth, false);
    for (int x = 0; x < grad.size(); x++) {
        QColor color(QColor(grad[x].R, grad[x].G, grad[x].B));
        painter.setPen(color);
        painter.drawLine(x + margins, toolbarHeight, x + margins, toolbarHeight + gradientHeight);
    }
}
```

### 10.3 Context Menu

Rechts-klik op een kleur knop:
- Add color
- Remove color
- Clear (alle kleuren verwijderen)
- Grab colors (uit huidige render?)
- Load/Save (naar/uit bestand)
- Clipboard operaties

---

## 11. HISTOGRAM SYSTEEM

### 11.1 cHistogram (`src/histogram.hpp`)

```cpp
class cHistogram {
    void Add(int index);  // Increment count for bucket 'index'
    long GetHist(int index) const;
    long long GetCount() const;
    long long GetSum() const;
    
private:
    std::vector<long> data;
    long long count;
    long long sum;
    int histSize;
};
```

### 11.2 Gebruik

Het histogram wordt gebruikt voor:
- **Auto-brightness** / exposure aanpassing
- **Tone mapping** (histogram equalization)
- **Statistische analyse** van de render

**Let op:** `Add()` clamped indices >= histSize naar `data[histSize]` (overflow bucket).

---

## 12. IMAGE BUFFER SYSTEM (cImage)

### 12.1 Multi-Layer Buffer Structuur

```cpp
class cImage {
    // Hoofd buffers
    std::vector<sRGBFloat> imageFloat;       // HDR float (0.0 - ∞)
    std::vector<sRGBFloat> postImageFloat;   // Na post-processing
    std::vector<sRGB16>    image16;          // 16-bit half-float
    std::vector<sRGB8>     image8;           // 8-bit display
    
    // Optionele kanalen
    std::vector<sRGBFloat> normalFloat;
    std::vector<sRGBFloat> specularFloat;
    std::vector<sRGBFloat> diffuseFloat;
    std::vector<sRGBFloat> worldFloat;
    std::vector<sRGBFloat> shadows;
    std::vector<sRGBFloat> globalIllumination;
    
    // Overige
    std::vector<quint16> alphaBuffer16;
    std::vector<quint8>  alphaBuffer8;
    std::vector<quint16> opacityBuffer;
    std::vector<sRGB8>   colourBuffer;       // ← 8-bit kleur kanaal (apart van image!)
    std::vector<float>   zBuffer;
};
```

### 12.2 Compile Image

```cpp
void cImage::CompileImage(QList<int> *list = nullptr) {
    // Converteert imageFloat → image16 (met gamma, exposure, etc)
    // Dan image16 → image8 voor display
}
```

### 12.3 Image Adjustments (`src/image_adjustments.h`)

```cpp
struct sImageAdjustments {
    float brightness{1.0};
    float contrast{1.0};
    float imageGamma{1.0};
    float saturation{1.0};
    bool hdrEnabled{false};
    int toneMappingMode{0};
    float toneExposure{1.0f};
    float colorTemperature{6500.0f};
    float blackPoint{0.0f};
    float whitePoint{1.0f};
    float vignetteIntensity{0.0f};
    float sharpenIntensity{0.0f};
};
```

---

## 13. KRITIEKE VALKUILEN & GOTCHAS

### 13.1 Structuur & Naming

| # | Probleem | Locatie | Impact |
|---|----------|---------|--------|
| 1 | **Typo: `trasparency`** | `render_worker.hpp:211` | Naamwijziging breekt parameter compatibiliteit |
| 2 | **`sRGB` = `qint32`** | `color_structures.hpp:100` | Signed type — negatieve waarden mogelijk na berekeningen |
| 3 | **Gradient conversie `/256.0`** | `color_gradient.cpp:219`, `opencl_dynamic_data.cpp` | Max waarde is 0.996, nooit 1.0 exact |
| 4 | **`smooth = false` in renderer** | `shader_surface_color.cpp`, `shader_surface_color.cl` | Cosine smoothing wordt niet gebruikt bij renderen |
| 5 | **Opacity parameters ongebruikt** | `initparameters.cpp:2250-2262` | `*_gradient_opacity` bestaan maar doen niets |
| 6 | **OpenCL `floorf` vs cast** | `shader_hsv2rgb.cl:40` | `(int)h` ≠ `floorf(h)` voor negatieve waarden |
| 7 | **Palette last element skipped** | `color_gradient.cpp:148-150` | Bij `paletteIndex == size-1` wordt index-1 gebruikt |
| 8 | **Gradient string: last color omitted** | `color_gradient.cpp:289-300` | Laatste kleur in string wordt niet opgeslagen |
| 9 | **Dual-path vereiste** | CPU + GPU | Wijziging in één pad = ongedefinieerd gedrag in ander |
| 10 | **Grayscale averaging** | `color_gradient.cpp:425` | `(R+G+B)/3` — niet perceptueel (luminance zou beter zijn) |

### 13.2 Data Flow Risico's

```
UI (gradient_edit_widget)
    ↓  GetColorsAsString()
Parameters (cParameterContainer)
    ↓  SetColorsFromString()
cMaterial (setParameters)
    ↓  GetListOfSortedColors()
OpenCL Data (BuildMaterialsData)
    ↓  toClFloat4()
GPU Shader (GetColorFromGradient)
```

**Risico:** Als het string formaat verandert, breekt:
- Settings laden/saven
- Animation keyframes
- Net render overdracht
- Presets
- Clipboard operaties

### 13.3 OpenCL Compile-Time Defines

De GPU kernel wordt **dynamisch gecompileerd** met defines die afhangen van:
- Welke materialen actief zijn
- Welke gradients ingeschakeld zijn
- Welke textures gebruikt worden
- Engine mode (fast/full/limited)

**Als je een nieuwe gradient toevoegt:**
1. Voeg `USE_XXX_GRADIENT` define toe in kernel builder
2. Update `CreateListOfHeaderFiles()` als er nieuwe headers nodig zijn
3. Update alle engine modes (fast/full/limited/nebula/mesh)

---

## 14. UPGRADE CHECKLIST

### 14.1 Voor Elke Gradient/Gerelateerde Wijziging

- [ ] **CPU kant:** `cColorGradient` logica gewijzigd?
- [ ] **GPU kant:** `.cl` gradient functies gewijzigd?
- [ ] **Structs:** `sGradientsCollection` (CPU) en `sClGradientsCollection` (GPU) gesynced?
- [ ] **Material:** `cMaterial` en `sMaterialCl` gesynced?
- [ ] **Data transfer:** `BuildMaterialsData()` offsets correct?
- [ ] **Shader input:** `sShaderInputData` en `sShaderInputDataCl` gesynced?
- [ ] **Render data:** `sRenderData` (GPU) palette pointers correct?
- [ ] **Parameters:** `initparameters.cpp` defaults toegevoegd/aangepast?
- [ ] **UI:** `gradient_edit_widget` hoeft meestal NIET gewijzigd (generic)
- [ ] **Serialization:** String formaat ongewijzigd? (anders backwards compat!)
- [ ] **OpenCL defines:** Nieuwe defines geregistreerd in kernel builder?
- [ ] **Dummy fallback:** Onbestaande materialen worden correct afgehandeld?
- [ ] **Shader gebruik:** Alle shaders die gradients gebruiken zijn geüpdatet?
  - `shader_surface_color.cl`
  - `shader_light_shading.cl`
  - `shader_object.cl`
  - `shader_volumetric.cl`

### 14.2 Build & Test Checklist

- [ ] Compileert zowel CPU als OpenCL code?
- [ ] Render met CPU engine correct?
- [ ] Render met OpenCL engine correct?
- [ ] Materialen met nieuwe feature laden correct uit bestand?
- [ ] Animation met nieuwe feature correct?
- [ ] Net render synchronisatie correct?
- [ ] Oude settings (backwards compat) laden correct?

---

## 15. BESTANDEN REFERENTIE

### 15.1 Kern Bestanden (moet je kennen)

| Bestand | Rol |
|---------|-----|
| `src/color_structures.hpp` | Alle kleur types |
| `src/color_gradient.h/cpp` | Gradient klasse |
| `src/hsv2rgb.h/cpp` | HSV conversie |
| `src/fractal_coloring.hpp/cpp` | Fractal color index berekening |
| `src/material.h/cpp` | Materiaal + gradient binding |
| `src/render_worker.hpp` | Shader structs (sGradientsCollection) |
| `src/shader_surface_color.cpp` | CPU kleur bepaling |
| `src/shader_object.cpp` | CPU shader object |
| `src/shader_light_shading.cpp` | CPU licht + specular |
| `src/opencl_dynamic_data.cpp` | GPU data transfer |
| `src/initparameters.cpp` | Defaults |

### 15.2 OpenCL Bestanden (moet je kennen)

| Bestand | Rol |
|---------|-----|
| `opencl/engines/shader_surface_color.cl` | GPU kleur bepaling |
| `opencl/engines/fractal_coloring.cl` | GPU fractal coloring |
| `opencl/engines/shader_object.cl` | GPU object shader |
| `opencl/engines/shader_light_shading.cl` | GPU licht |
| `opencl/engines/shader_hsv2rgb.cl` | GPU HSV |
| `opencl/material_cl.h` | GPU materiaal struct |
| `opencl/shader_input_data_cl.h` | GPU shader input |
| `opencl/render_data_cl.h` | GPU render data |
| `opencl/opencl_algebra.h` | Conversie functies (toClFloat4, etc) |

### 15.3 UI Bestanden

| Bestand | Rol |
|---------|-----|
| `qt/gradient_edit_widget.h/cpp` | Gradient editor UI |
| `qt/my_color_button.h/cpp` | Kleur knop widget |

---

## 16. SAMENVATTING VOOR UPGRADES

**De 5 gouden regels:**

1. **Symmetrie:** CPU en GPU code moeten identieke logica hebben
2. **Struct matching:** Elke CPU struct heeft een GPU equivalent met exacte layout
3. **String stabiliteit:** Het gradient serialisatie formaat mag NOIT wijzigen zonder migratie
4. **Default completeness:** Elke nieuwe parameter MOET een default hebben in `initparameters.cpp`
5. **Enable flags:** Elke gradient MOET een `_enable` flag hebben, default `false` (behalve surface)

**De 3 meest voorkomende fouten bij upgrades:**

1. **Vergeten GPU pad bij te werken** → OpenCL render geeft verkeerde kleuren of crashed
2. **Struct layout mismatch** → GPU leest verkeerde geheugen offsets → artifacts/crash
3. **Gradient offset berekening fout** in `BuildMaterialsData()` → GPU palette lookups out of bounds

---

*Einde nucleaire analyse. Gebruik dit als referentie bij elke gradient/color systeem wijziging.*

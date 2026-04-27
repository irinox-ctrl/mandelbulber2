# MANDELBULBER2 CIMAGE: Nucleaire Diepte-Audit

**Datum**: 2026-04-22  
**Bestanden**: `cimage.hpp/cpp`, `color_structures.hpp`, `image_adjustments.h`  
**Scope**: Multi-layer image container, pixel pipeline, gamma/HDRI processing, preview system, memory management

---

## INHOUDSOPGAVE

1. [Architectuur-Overzicht](#1-architectuur-overzicht)
2. [Buffer Layout & Memory Footprint](#2-buffer-layout--memory-footprint)
3. [Pixel Processing Pipeline](#3-pixel-processing-pipeline)
4. [Gamma & HDR Processing](#4-gamma--hdr-processing)
5. [Preview Systeem](#5-preview-systeem)
6. [Drawing Primitives](#6-drawing-primitives)
7. [Visual Compare (MSE)](#7-visual-compare-mse)
8. [Bugs & Riskante Code](#8-bugs--riskante-code)

---

## 1. Architectuur-Overzicht

```
┌─────────────────────────────────────────────────────────────────────┐
│                          cImage                                     │
│                                                                     │
│  ┌─────────────┐   ┌──────────────┐   ┌─────────────┐              │
│  │ imageFloat  │ → │postImageFloat│ → │   image16   │              │
│  │  (HDR raw)  │   │(post-process)│   │ (16-bit)    │              │
│  └─────────────┘   └──────────────┘   └──────┬──────┘              │
│                                              ↓                      │
│                                        ┌─────────────┐             │
│                                        │   image8    │             │
│                                        │  (8-bit)    │             │
│                                        └──────┬──────┘             │
│                                               ↓                     │
│                                        ┌─────────────┐             │
│                                        │   preview   │             │
│                                        │ (scaled)    │             │
│                                        └─────────────┘             │
│                                                                     │
│  Optionele buffers: normal, specular, diffuse, worldPos,           │
│                     shadows, globalIllumination, notDenoised       │
│                                                                     │
│  Z-buffer: 1e20 default (oneindig ver weg)                         │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 2. Buffer Layout & Memory Footprint

### 2.1 Basis Buffers (altijd gealloceerd)

| Buffer | Type | Bytes/pixel | 4K (3840×2160) |
|--------|------|-------------|----------------|
| `imageFloat` | `sRGBFloat` (3×float) | 12 | ~99 MB |
| `postImageFloat` | `sRGBFloat` | 12 | ~99 MB |
| `image16` | `sRGB16` (3×quint16) | 6 | ~50 MB |
| `image8` | `sRGB8` (3×quint8) | 3 | ~25 MB |
| `zBuffer` | `float` | 4 | ~33 MB |
| `alphaBuffer16` | `quint16` | 2 | ~16 MB |
| `alphaBuffer8` | `quint8` | 1 | ~8 MB |
| `opacityBuffer` | `quint16` | 2 | ~16 MB |
| `colourBuffer` | `sRGB8` | 3 | ~25 MB |
| **Totaal basis** | | **45** | **~371 MB** |

### 2.2 Optionele Buffers (per channel ~12 bytes/pixel)

| Buffer | Gebruik |
|--------|---------|
| `normalFloat` | Normaal vectoren (voor belichting) |
| `normalFloatWorld` | Wereld-ruimte normaal vectoren |
| `specularFloat` | Specular reflectie component |
| `diffuseFloat` | Diffuse reflectie component |
| `worldFloat` | Wereld positie per pixel |
| `shadows` | Schaduw buffer |
| `globalIllumination` | GI pass |
| `notDenoised` | Ruwe render voor denoising vergelijking |

**Met alle optionele buffers**: +8 × 12 × 3840 × 2160 ≈ **+794 MB**

**Totaal 4K met alles aan**: ~1.1 GB

### 2.3 Memory Allocatie

```cpp
bool cImage::AllocMem() {
    try {
        imageFloat.resize(width * height);
        postImageFloat.resize(width * height);
        image16.resize(width * height);
        // ... etc
        if (opt.optionalNormal) normalFloat.resize(width * height);
        // ... etc
    }
    catch (std::bad_alloc &ba) {
        width = 0; height = 0;
        FreeImage();
        qCritical() << "bad_alloc caught in cImage";
        return false;
    }
}
```

Alle buffers worden **atomisch** geallocateerd in één functie call. Als één buffer faalt, wordt alles op 0 gezet.

---

## 3. Pixel Processing Pipeline

### 3.1 Rendering Fase
Render workers schrijven HDR float waarden naar `imageFloat`:
```cpp
PutPixelImage(x, y, sRGBFloat(R, G, B));
```

### 3.2 Post-Processing Fase
Post-processing (glow, fog, DOF, etc.) leest `imageFloat` en schrijft naar `postImageFloat`.

### 3.3 Compile Fase (float → 16-bit)

```cpp
void cImage::CompileImage() {
    for (elke pixel) {
        sRGBFloat pixel = postImageFloat[address];
        sRGB16 newPixel16 = CalculatePixel(pixel);
        image16[address] = newPixel16;
    }
}
```

### 3.4 8-bit Conversie (16-bit → 8-bit)

```cpp
quint8 *cImage::ConvertTo8bitChar() {
    for (elke pixel) {
        image8[i].R = image16[i].R / 256;  // Rechtse shift
    }
}
```

### 3.5 Pixel Indexering

```cpp
inline quint64 getImageIndex(const quint64 x, const quint64 y) const {
#ifdef QT_DEBUG
    if (x < width && y < height) {
        return x + y * width;
    } else {
        qCritical() << "getImageIndex out of range";
        return 0;  // ← Corrupteert pixel (0,0)!
    }
#else
    return x + y * width;
#endif
}
```

---

## 4. Gamma & HDR Processing

### 4.1 CalculatePixel() — De Post-Processing Formule

```cpp
sRGB16 cImage::CalculatePixel(sRGBFloat pixel) {
    // 1. Brightness
    R = pixel.R * adj.brightness;
    G = pixel.G * adj.brightness;
    B = pixel.B * adj.brightness;

    // 2. Contrast (rond 0.5)
    R = (R - 0.5f) * adj.contrast + 0.5f;
    G = (G - 0.5f) * adj.contrast + 0.5f;
    B = (B - 0.5f) * adj.contrast + 0.5f;

    // 3. Clip negatief
    if (R < 0) R = 0;  if (G < 0) G = 0;  if (B < 0) B = 0;

    // 4. HDR compressie
    if (adj.hdrEnabled) {
        R = tanhf(R);
        G = tanhf(G);
        B = tanhf(B);
    }

    // 5. Saturation
    float V = sqrtf(R*R*0.299f + G*G*0.587f + B*B*0.114f);
    R = V + (R - V) * adj.saturation;
    G = V + (G - V) * adj.saturation;
    B = V + (B - V) * adj.saturation;

    // 6. Clamp
    R = clamp(R, 0.0f, 1.0f);
    G = clamp(G, 0.0f, 1.0f);
    B = clamp(B, 0.0f, 1.0f);

    // 7. Gamma correctie (via lookup tabel)
    newPixel16.R = gammaTable[quint16(R * 65535.0f)];
    // ... etc
}
```

### 4.2 HDR tanh Compressie

```cpp
if (adj.hdrEnabled) {
    R = tanhf(R);
    G = tanhf(G);
    B = tanhf(B);
}
```

| Input | tanh(Input) | Opmerking |
|-------|-------------|-----------|
| 0.0 | 0.0 | Zwart blijft zwart |
| 0.5 | 0.462 | Licht compressie |
| 1.0 | 0.762 | Zelfs "normale" waarden worden gecomprimeerd |
| 2.0 | 0.964 | HDR highlights |
| 5.0 | 0.9999 | Bijna 1.0 |

**Opmerking**: Zelfs met `R=1.0` (geen overbelichting) wordt de output `0.762`. Dit betekent dat **HDR mode altijd het beeld donkerder maakt**, zelfs voor LDR input. De brightness slider moet dan worden verhoogd om te compenseren.

### 4.3 Gamma Tabel

```cpp
void cImage::CalculateGammaTable() {
    gammaTable.resize(65536);
    for (quint64 i = 0; i < 65536; i++) {
        gammaTable[i] = int(powf(i / 65536.0f, 1.0f / adj.imageGamma) * 65535.0f);
    }
}
```

De tabel wordt **1x berekend** bij gamma wijziging, daarna is de pixel-conversie O(1) via lookup.

---

## 5. Preview Systeem

### 5.1 Preview Generatie

```cpp
quint8 *cImage::CreatePreview(double scale, int visibleWidth, int visibleHeight, QWidget *widget) {
    dpiScale = widget->devicePixelRatioF();
    quint64 w = width * scale * dpiScale;
    quint64 h = height * scale * dpiScale;
    preview.resize(w * h);
    preview2.resize(w * h);
}
```

De preview wordt geschaald met **box filtering** (gemiddelde van meerdere bron pixels):

```cpp
for (int j = 0; j < countY; j++) {
    for (int i = 0; i < countX; i++) {
        float xx = x * scaleX + i * deltaX - 0.5f;
        float yy = y * scaleY + j * deltaY - 0.5f;
        if (xx > 0 && xx < width - 1 && yy > 0 && yy < height - 1) {
            sRGB8 oldPixel = Interpolation(xx, yy);
            R += oldPixel.R; G += oldPixel.G; B += oldPixel.B;
        }
    }
}
newPixel.R = quint8(R / factor);
```

**Fast preview mode**: Nearest-neighbor (1 bronpixel per preview pixel):
```cpp
if (fastPreview) {
    preview[x + y * w] = image8[quint64(y * scaleY) * width + quint64(x * scaleX)];
}
```

### 5.2 Thread Safety

```cpp
QMutex previewMutex;
```

Preview operaties worden beschermd door een mutex. Maar de **main image buffers** (`imageFloat`, `image16`, etc.) hebben **geen mutex**. De renderer vertrouwt erop dat threads niet-overlappende regio's schrijven.

---

## 6. Drawing Primitives

### 6.1 AntiAliasedPoint (Bilineaire splat)

Een punt wordt verspreid over 4 naburige pixels met bilineaire gewichten:
```
(1-dx)(1-dy)   dx(1-dy)
(1-dx)dy       dx*dy
```

### 6.2 AntiAliasedLine (SDF-based)

Gebruikt een **Signed Distance Field** benadering voor dikke lijnen:

```cpp
float dot = pax * deltaX + pay * deltaY;
float h = clamp(dot / l2, 0.0f, 1.0f);
float dx = pax - deltaX * h;
float dy = pay - deltaY * h;
float dist = sqrtf(dx*dx + dy*dy);
float opacity2 = clamp(halfThickness - dist, 0.0f, 1.0f);
```

Dit is de afstand van pixel `(ix, iy)` tot het lijnsegment `(x1,y1)-(x2,y2)`. De opacity is 1.0 binnen de lijn, 0.0 erbuiten, met een lineaire overgang over `halfThickness` pixels.

### 6.3 CircleBorder

Tekent een ring (buitenste radius `r2`, binnenste radius `r1`) met soft edges. De opacity is:
```cpp
float opacity2 = wspJ * (borderWidth - deltaR);
```
waar `deltaR = |rr - r|` en `wspJ = 1.0 / borderWidth`.

---

## 7. Visual Compare (MSE)

### 7.1 Mean Squared Error

```cpp
double cImage::VisualCompare(std::shared_ptr<cImage> refImage, bool checkIfBlank) {
    double totalDiff = 0.0;
    for (y = 2; y < h - 2; y++) {
        for (x = 2; x < w - 2; x++) {
            sRGB8 p1 = GetPixelImage8(x, y);
            sRGB8 p2 = refImage->GetPixelImage8(x, y);
            double diff = (p1.R-p2.R)² + (p1.G-p2.G)² + (p1.B-p2.B)²;
            totalDiff += diff;
        }
    }
    return totalDiff / (w * h);  // MSE per pixel
}
```

**Border skip**: De buitenste 2 pixels worden overgeslagen — waarschijnlijk omdat randpixels vaak artifacts hebben.

### 7.2 Blank Image Detectie

```cpp
if (checkIfBlank) {
    if (min > 245*3 || max < 5*10 || max - min < 5) {
        diffPerPixel = 0;  // Blank image = geen verschil
    }
}
```

Een image wordt als "blank" beschouwd als:
- Bijna alle pixels wit (`R+G+B > 245*3`)
- Bijna alle pixels donker (`R+G+B < 50`)
- Geen contrast (`max - min < 5`)

---

## 8. Bugs & Riskante Code

### 🐛 BUG #1 — `getImageIndex` corrupteert pixel (0,0) bij out-of-bounds

```cpp
#ifdef QT_DEBUG
    if (x < width && y < height) {
        return x + y * width;
    } else {
        qCritical() << "getImageIndex out of range";
        return 0;  // ← SCHRIJFT NAAR PIXEL (0,0)!
    }
#endif
```

In debug mode, als een pixel buiten bounds wordt geschreven, wordt **pixel (0,0) overschreven** in plaats van een crash. Dit maakt debuggen extreem moeilijk — je ziet een vreemd artifact in de hoek maar weet niet waar het vandaan komt.

**Fix**: `assert(false)` of een aparte "dummy pixel" buffer voor out-of-bounds writes.

---

### 🐛 BUG #2 — `ConvertTo8bitChar` doet rechtse shift in plaats van rounding

```cpp
image8[i].R = image16[i].R / 256;
```

Dit is equivalent met `image16 >> 8`, wat een **rechtse shift** is. Voor `image16.R = 65535` is het resultaat `255` (correct). Maar voor waarden net onder een grens (bv. `511 / 256 = 1` vs `512 / 256 = 2`) is er geen rounding. Een betere conversie is:
```cpp
image8[i].R = quint8((image16[i].R + 128) / 256);  // rounding
```

---

### 🐛 BUG #3 — `ChangeSize` met `useResizeOnChangeSize` heeft race condition

```cpp
bool cImage::ChangeSize(quint64 w, quint64 h, sImageOptional optional) {
    previewMutex.lock();
    // ... kopieer oude image
    FreeImage();
    AllocMem();
    // ... resize logic
    previewMutex.unlock();
}
```

De `previewMutex` lockt de preview, maar `FreeImage()` deallocateert **alle buffers** inclusief `imageFloat`. Als een render worker op dat moment aan het schrijven is naar `imageFloat`, is er een race condition. De renderer heeft geen eigen mutex op de main buffers.

---

### 🐛 BUG #4 — `GetPreviewConstPtr()` doet `abort()`

```cpp
const quint8 *cImage::GetPreviewConstPtr() const {
    if (previewAllocated) {
        ptr = reinterpret_cast<const quint8 *>(preview2.data());
    } else {
        abort();  // ← KILLED BY SIGNAL
    }
}
```

Als de preview niet is gealloceerd, wordt het hele programma **afgebroken**. Dit is extreem hard voor een getter functie.

**Fix**: Returnt `nullptr` en laat de caller beslissen:
```cpp
if (!previewAllocated) return nullptr;
```

---

### ⚠️ RISICO #5 — `CalculatePixel` HDR tanh maakt LDR beelden donkerder

```cpp
if (adj.hdrEnabled) {
    R = tanhf(R);  // tanh(1.0) = 0.762
}
```

Zelfs een perfect belichte scene (waarden rond 1.0) wordt met HDR enabled naar ~76% gecomprimeerd. De gebruiker moet dan brightness verhogen om te compenseren. Dit is verwarrend — HDR mode zou alleen extreem hoge waarden moeten comprimeren.

**Alternatief**: Gebruik `tonemap(x) = x / (1 + x)` (Reinhard) of een adaptieve curve.

---

### ⚠️ RISICO #6 — `VisualCompare` MSE deling door totaal aantal pixels

```cpp
double diffPerPixel = totalDiff / numberOfPixels;
```

Maar `numberOfPixels = w * h` (het volledige image), terwijl de loop alleen over `(w-4) * (h-4)` pixels itereert (border skip van 2). Dit betekent dat de MSE wordt **onderschat** — de border pixels (die vaak het meeste verschil hebben) worden niet meegenomen in de som maar wel in de deling.

---

### ⚠️ RISICO #7 — `FastResize` en `ChangeSize` gebruiken nearest-neighbor

```cpp
quint64 yy = y * scaleY;
quint64 xx = x * scaleX;
PutPixelImage(x, y, imageCopy[yy * oldWidth + xx]);
```

Geen interpolatie — gewoon de dichtstbijzijnde bronpixel nemen. Dit levert **blocky resultaten** bij downscaling en aliasing bij upscaling.

---

### ⚠️ RISICO #8 — `GetUsedMB()` kan integer overflow hebben

```cpp
quint64 mb = (zBufferSize + alphaSize16 + ... + optionalSize) / 1024 / 1024;
return int(mb);
```

De som kan groter zijn dan `2^31` bij extreem grote images met veel optionele buffers. De `int` cast truncateert dan.

---

### ⚠️ RISICO #9 — `CompileImage` met `QList<int>*` heeft potentiele infinite loop

```cpp
for (quint64 y = 0; y < height; y++) {
    if (list) {
        if (listIndex >= list->size()) break;
        y = quint64(list->at(listIndex));
        listIndex++;
    }
    // ...
}
```

Als de `list` een waarde bevat die groter is dan `height - 1`, dan wordt `y` gezet naar die waarde en de `y++` incrementeert. Maar de for-loop condition `y < height` faalt, dus de loop stopt. Dit is correct. Echter, als de list **ongesorteerde of dubbele waarden** bevat, worden regio's dubbel gecompileerd.

---

*De cImage class is een robuuste multi-layer image container met een goed doordachte pixel pipeline. De belangrijkste kwetsbaarheden zitten in de error handling (abort(), corruptie van pixel 0,0) en de thread safety rondom buffer resizen.*

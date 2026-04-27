# MANDELBULBER2 ANIMATIE-SYSTEEM: Nucleaire Diepte-Audit

**Datum**: 2026-04-22  
**Scope**: `animation_flight`, `animation_frames`, `animation_keyframes`, `animation_path_data`, `keyframes`, `morph`, `render_job`, `one_parameter`, `multi_val`, `parameters`  
**Doel**: Volledige architecturale en wiskundige dekking van het animatie-systeem

---

## INHOUDSOPGAVE

1. [Hoog Niveau Overzicht](#1-hoog-niveau-overzicht)
2. [Gedetailleerde File-Analyse](#2-gedetailleerde-file-analyse)
3. [Interpolatie-Mathematiek](#3-interpolatie-mathematiek)
4. [RenderJob Consumptie](#4-renderjob-consumptie)
5. [Morph-Type Extensie](#5-morph-type-extensie)
6. [Concrete Implementaties](#6-concrete-implementaties)
7. [Volledige Synthese](#7-volledige-synthese)

---

## 1. Hoog Niveau Overzicht

Het animatiesysteem bestaat uit **twee parallelle subsystemen** die beide steunen op een gemeenschappelijke data-container:

| Subsysteem | Klasse | Data-container | Modus |
|------------|--------|----------------|-------|
| **Flight Animation** | `cFlightAnimation` | `cAnimationFrames` (via `gAnimFrames`) | Real-time opname, frame-voor-frame |
| **Keyframe Animation** | `cKeyframeAnimation` | `cKeyframes` (via `gKeyframes`) | Keyframe + interpolatie |

De bestanden vormen een **drie-lagen architectuur**:
- **Data-laag**: `animation_frames.hpp/cpp` + `animation_path_data.hpp`
- **Flight controle-laag**: `animation_flight.hpp/cpp`
- **Keyframe controle-laag**: `animation_keyframes.hpp/cpp`

---

## 2. Gedetailleerde File-Analyse

### 2.1 `animation_path_data.hpp` — De Visualisatie-Struct

**Doel**: Puur data-transport voor het tekenen van animatiepaden in de `RenderedImage` widget.

```cpp
struct sAnimationPathPoint {
    CVector3 camera;
    CVector3 target;
    CVector3 lights[4];
    sRGB8 lightColor[4];
};

struct sAnimationPathData {
    QList<sAnimationPathPoint> animationPath;
    int numberOfKeyframes;
    int numberOfFrames;
    QList<int> framesPeyKey;
    int actualSelectedFrameNo;
    bool cameraPathEnable;
    bool targetPathEnable;
    bool lightPathEnable[4];
};
```

**Belangrijk**: Deze struct wordt **gevuld** in `cKeyframeAnimation::UpdateAnimationPathCameraAndLights()` en **geconsumeerd** door `RenderedImage::SetAnimationPath()`.

**Light handling**: Lights kunnen relatief of absoluut gepositioneerd zijn. Bij relatieve positie wordt de delta geroteerd naar de camera-ruimte:
```cpp
CVector3 deltaPositionRotated = 
    cameraTarget.GetForwardVector() * deltaPosition.z +
    cameraTarget.GetTopVector() * deltaPosition.y +
    cameraTarget.GetRightVector() * deltaPosition.x;
```

### 2.2 `animation_frames.hpp/cpp` — De Data-Matrix

**Rol**: De centrale "database" voor alle animatieparameters. Beheert een **2D matrix**: parameters (rijen) x frames (kolommen).

#### Kernstructuren:

```cpp
struct sAnimationFrame {
    cParameterContainer parameters;  // Alle geanimeerde params voor dit frame
    QImage thumbnail;
    int numberOfSubFrames = 0;       // Voor keyframes: interpolatie-stappen
};

struct sParameterDescription {
    QString parameterName;
    QString containerName;           // "main" of "fractal0", "fractal1", etc.
    enumVarType varType;             // typeVector3, typeDouble, etc.
    enumMorphType morphType;         // morphLinear, morphCatMullRom, etc.
};
```

#### Container Selectie:

Een kritisch mechanisme is `ContainerSelector()`. Parameters kunnen leven in:
- `main` -> `cParameterContainer` (globale params)
- `fractal0`..`fractalN` -> `cFractalContainer` (fractal-specifiek)

```cpp
if (containerName == "main" || containerName == "material") 
    container = params;
else if (containerName.indexOf("fractal") >= 0)
    container = fractal->at(index);
```

**Let op**: De non-const versie accepteert ook `"material"` als alias voor `main`, maar de const versie doet dat **niet**. Dit is een subtiel asymmetrisch ontwerp.

#### Frame Manipulatie:

| Methode | Werking |
|---------|---------|
| `AddFrame()` | Kopieert alle `listOfParameters` uit de huidige `params/fractal` naar een nieuw frame. Bewaart `morphType` van bestaande frames. |
| `GetFrameAndConsolidate()` | Schrijft frame-data **terug** naar de globale `params/fractal` containers. |
| `ModifyFrame()` | Overschrijft een bestaand frame. |

#### Audio-Integratie:

Elke geanimeerde parameter kan een audiobron hebben. De formule voor audio-modulatie:
```cpp
if (negative)
    newVal = oldVal / (1.0 + multFactor * animSound) - additionFactor * animSound;
else
    newVal = oldVal * (1.0 + multFactor * animSound) + additionFactor * animSound;
```

**Timing**: `soundFrame = frame - soundDelay` (negatieve delay = audio loopt vooruit).

### 2.3 `animation_flight.hpp/cpp` — Real-time Flight Opname

**Filosofie**: De gebruiker "vliegt" door de fractal met muis/toetsenbord, en elke `x` seconden wordt een frame opgeslagen.

#### State Machine:

De klasse houdt **real-time vlieg-state** bij:
```cpp
CVector2<double> strafe;           // Zijwaartse beweging (muis X/Y)
CVector2<double> yawAndPitch;      // Rotatie (muis)
double rotationDirection;          // Roll (toetsen)
bool orthogonalStrafe;             // Of strafe orthogonaal is
bool negativeFlightSpeed;          // Of we achteruit vliegen
double linearSpeedSp;              // Basis snelheid
```

#### Physics Loop:

De flight recorder gebruikt een **eenvoudige inertia-gebaseerde integrator**:

1. Bereken afstand tot fractal oppervlak -> `distanceToSurface`
2. Bepaal lineaire snelheid:
   - `speedRelative`: speed = distanceToSurface * speedSetting
   - `speedConstant`: speed = speedSetting
3. Bereken acceleratie: `(targetSpeed - currentSpeed) / (inertia + 1)`
4. Update positie: position += speed
5. Update rotatie met Euler-achtige stappen (`RotateAroundVectorByAngle`)
6. Render frame met `cRenderJob::flightAnimRecord`
7. Sla op met `SaveImage()`

**Pause mechanisme**: `recordPause` bevriest de opname maar niet de render loop.

#### Tabel/GUI:

De flight table is een `QTableWidget` waar:
- **Rij 0**: Preview thumbnails
- **Rijen 1..N**: Geanimeerde parameters (x,y,z gescheiden)

`AddVariableToTable()` explodeert vectoren naar aparte rijen:
- `typeVector3` -> 3 rijen (`_x`, `_y`, `_z`)
- `typeVector4` -> 4 rijen (`_x`, `_y`, `_z`, `_w`)
- `typeRgb` -> 3 rijen (`_R`, `_G`, `_B`)

#### Interpolatie:

`InterpolateForward()` doet **lineaire interpolatie** tussen een cel en een toekomstig frame. Dit werkt op tabel-niveau, niet op keyframe-interpolatie-niveau.

### 2.4 `animation_keyframes.hpp/cpp` — Keyframe Animatie

**Filosofie**: Gebruiker plaatst **keyframes** (discrete posities), en het systeem genereert tussenliggende frames via **mathematische interpolatie** (morphing).

#### Tabel Layout:

De keyframe tabel is complexer dan de flight tabel:

```
Rij 0: Keyframe previews (thumbnails)
Rij 1: Frames/keyframe (subFrames)
Rij 2: Camera speed [units/frame]
Rij 3+: Geanimeerde parameters
```

Kolommen:
- **Kolom 0**: Audio selectors (`cPushButtonAnimSound`)
- **Kolom 1+**: Keyframes zelf

#### Morph Types (kleurcodering):

| Type | Kleur |
|------|-------|
| `morphNone` | Wit |
| `morphLinear` | Grijs |
| `morphLinearAngle` | Grijs/Blauw |
| `morphCatMullRom` | Groen |
| `morphAkima` | Rood |
| `morphCubic` | Geel |
| `morphSteffen` | Blauw |

Deze kleuren worden in de tabelcellen getoond als achtergrond (`MorphType2Color()`).

#### Interpolatie Engine:

De eigenlijke interpolatie gebeurt **niet** in deze files -- die delegeert naar `cKeyframes` (uit `keyframes.hpp`). Deze klasse **consumeert** de geïnterpoleerde resultaten:

```cpp
keyframes->GetInterpolatedFrameAndConsolidate(frameIndex, params, fractalParams);
```

**Sub-frames**: Elke keyframe heeft `numberOfSubFrames`. De mapping van `frameIndex` -> `(keyframeIndex, subIndex)` gebeurt via:
```cpp
int index = keyframes->GetKeyframeIndex(frameIndex);
int subIndex = keyframes->GetSubIndex(frameIndex);
```

#### Collision Detection (`CheckForCollisions`):

Een unieke feature van keyframe animatie: het systeem kan **botsingen** detecteren tussen camera en fractal:

```cpp
for (int frameIndex = 0; frameIndex < totalFrames; frameIndex++) {
    keyframes->GetInterpolatedFrameAndConsolidate(frameIndex, tempPar, tempFractPar);
    double dist = mainInterface->GetDistanceForPoint(camera, tempPar, tempFractPar);
    if (dist < minDist) listOfCollisions.append(frameIndex);
}
```

#### Animatie Pad Visualisatie:

`UpdateAnimationPathCameraAndLights()` is de **zwaarste GUI-update functie**. Voor **elk frame** van de volledige animatie:
1. Interpoleert alle parameters
2. Haalt camera, target op
3. Berekent light posities (absoluut of relatief)
4. Slaat op in `sAnimationPathData`
5. Stuurt naar `imageWidget->SetAnimationPath()`

**Performance impact**: Dit is O(N) met N = totaal aantal frames.

#### Value Chart Widget:

De `cAnimationValueChartWidget` toont een grafiek van één parameter-component over tijd. Bij klikken op een parameter-rij wordt `UpdateAnimationPathSingleParameter()` aangeroepen.

#### Bijzondere Features:

| Feature | Implementatie |
|---------|---------------|
| **Export Flight->Keyframes** | Elke N-de flight frame wordt een keyframe met `frames_per_keyframe` stappen |
| **Export Keyframes->Flight** | Elke geïnterpoleerde frame wordt een flight frame (volledige expansie) |
| **Set Constant Target Distance** | Herberekent alle `target` vectoren zodat `distance(camera, target) = constant` |
| **Insert In Between** | Voegt een keyframe toe op de helft van de interpolatie tussen twee bestaande keyframes |

---

## 3. Interpolatie-Mathematiek

### 3.1 De Interpolatie-Pijplijn

```
Globale Frame Index (N)
        |
        v
[cKeyframes] Frame->Keyframe Mapping (keyframesIndexesTable)
        |
        v
[cKeyframes] Morph Cache Opbouw (per parameter, lazy)
        |
        v
[cMorph::Interpolate()] Factor berekening (0.0 ... 1.0 tussen keyframes)
        |
        v
[Algoritme] Linear / CatmullRom / GSL-Spline
        |
        v
[cOneParameter] Geïnterpoleerde waarde per component (x,y,z,w,R,G,B)
        |
        v
[cAnimationFrames::ApplyAudioAnimation()] Audio-modulatie
        |
        v
[cParameterContainer] Terugschrijven naar render parameters
```

### 3.2 Frame Index Mapping

In `keyframes.cpp` worden twee tabellen opgebouwd:

```cpp
// Voorbeeld: 3 keyframes met [30, 60, 30] subframes
keyframesIndexesTable = [0,0,0,...,0, 1,1,1,...,1, 2,2,2,...,2]
                        |--30x--|  |--60x--|  |--30x--|
framesIndexesTable    = [0, 30, 90]   // startframe per keyframe
```

| Tabel | Functie |
|-------|---------|
| `keyframesIndexesTable` | Geeft voor **elke globale frame index** aan bij welk keyframe deze hoort |
| `framesIndexesTable` | Geeft voor **elk keyframe** aan wat de eerste globale frame index is |

### 3.3 De Morph Cache

Voor **elke parameter** (en dus elk `cMorph` object) wordt bij eerste gebruik een cache opgebouwd. De cache bevat **alle keyframes die een niet-lege waarde hebben** voor deze parameter.

In `cMorph::AddData()`:
```cpp
for (int i = 0; i < noOfSubFrames; i++) {
    frameIndices.append(QPair<int, double>(keyFrame, double(i) / noOfSubFrames));
}
```

De totale `frameIndices` lijst heeft een lengte gelijk aan het **totaal aantal frames**.

### 3.4 De Interpolatie-Algoritmes

#### 3.4.1 morphNone -- Stapsgewijs

$$f(t) = v_{key}$$

#### 3.4.2 morphLinear -- Lineaire Interpolatie

$$f(t) = v_1 + t(v_2 - v_1), \quad t \in [0,1]$$

**Angle variant**: `NearestNeighbourAngle()` + `LimitAngle()`

#### 3.4.3 morphCatMullRom -- Catmull-Rom Spline

De Catmull-Rom basisfuncties:

$$P(t) = \frac{1}{2}\begin{bmatrix}1 & t & t^2 & t^3\end{bmatrix} \begin{bmatrix}0 & 2 & 0 & 0\\-1 & 0 & 1 & 0\\2 & -5 & 4 & -1\\-1 & 3 & -3 & 1\end{bmatrix} \begin{bmatrix}v_1\\v_2\\v_3\\v_4\end{bmatrix}$$

**Eigenschappen**:
- Gaat **exact** door $v_2$ (bij $t=0$) en $v_3$ (bij $t=1$)
- Tangent bij $v_2$ is parallel aan $(v_3 - v_1) / 2$
- Tangent bij $v_3$ is parallel aan $(v_4 - v_2) / 2$

**Logaritmische adaptieve interpolatie**:

Als waarden over meerdere ordes van grootte variëren:
```cpp
if (deviation / average > 0.1) {
    v1 = log(fabs(v1)); ...;
    // Interpoleer in log-ruimte
    // result = exp(interpolated_value)
}
```

Dit is **constante-relatieve-groei interpolatie**.

#### 3.4.4 GSL Splines: Akima, Cubic, Steffen

Deze drie algoritmes delegeren naar de **GNU Scientific Library (GSL)**.

**Data-voorbereiding** (niet-uniform domein):
```cpp
x[2] = 0.0;
x[3] = 1.0;
x[4] = x[3] + dataSets[k[3]].numberOfSubFrames / baseFramesPerKeyframe;
```

| Type | GSL Constant | Karakteristiek |
|------|-------------|----------------|
| **Akima** | `gsl_interp_akima` | Lokaal, robuust tegen oscilaties |
| **Cubic** | `gsl_interp_cspline` | Globaal, natuurlijke randvoorwaarden |
| **Steffen** | `gsl_interp_steffen` | Monotonie-bewarend |

### 3.5 Hoek-Handling

#### NearestNeighbourAngle (Unwrapping)

```cpp
void cMorph::NearestNeighbourAngle(QList<double *> vals) {
    int deltaCircle = 0;
    for (int i = 1; i < vals.size(); i++) {
        double newVal = *vals[i] + deltaCircle;
        if (fabs(newVal - *vals[i-1]) > 180.0) {
            deltaCircle += newVal < *vals[i-1] ? 360 : -360;
        }
        *vals[i] += deltaCircle;
    }
}
```

**Voorbeeld**:
- Input: `[10°, 350°, 20°]`
- Resultaat: `[10°, -10°, 20°]`

### 3.6 Audio-Integratie

De audio-pipeline draait **parallel** aan de geometrische interpolatie:

```
[cKeyframes] --> [cMorph::Interpolate()] --> [cOneParameter]
                                                   |
                                           [ApplyAudioAnimation()]
                                                   |
                    [cAudioTrackCollection] ---------
                            |
                    [cAudioTrack] per parameter
```

**De formule**:

$$v_{final} = v_{spline} \cdot (1 + m \cdot a(t)) + c \cdot a(t)$$  [positieve modus]

$$v_{final} = \frac{v_{spline}}{1 + m \cdot a(t)} - c \cdot a(t)$$  [negatieve modus]

Waarbij:
- $v_{spline}$ = de geïnterpoleerde waarde uit de spline
- $a(t)$ = de geamp sample waarde op (vertraagde) tijd $t$, met $a(t) \in [0, 1]$
- $m$ = `multFactor`
- $c$ = `additionFactor`

---

## 4. RenderJob Consumptie

### 4.1 De Parameter-Stroom

```
[gKeyframes::GetInterpolatedFrameAndConsolidate()]
                    |
                    v
    [cParameterContainer::SetFromOneParameter()] <-- per parameter
                    |
                    v
    [cRenderJob::UpdateParameters()] --> *paramsContainer = *_params
                    |
                    v
    [cRenderJob::Execute()] --> PrepareData()
                    |
                    v
    [sParamRender constructor] --> leest uit paramsContainer
                    |
                    v
    [cRenderer::RenderImage()] --> gebruikt sParamRender direct
```

### 4.2 De Kopie-Architectuur

In de constructor van `cRenderJob`:

```cpp
cRenderJob::cRenderJob(...) {
    paramsContainer.reset(new cParameterContainer());
    *paramsContainer = *_params;           // DIEPE KOPIE!
    fractalContainer.reset(new cFractalContainer());
    *fractalContainer = *_fractal;         // DIEPE KOPIE!
}
```

De render job werkt op een **privé kopie** van de parameters. Dit betekent:
- De animatie-controller kan ongestoord het volgende frame voorbereiden
- Er is **geen race condition** tussen interpolatie en rendering

### 4.3 Van Container naar Render-Structuur

In `cRenderJob::Execute()`:

```cpp
std::shared_ptr<sParamRender> params(new sParamRender(
    paramsContainer, &renderData->objectData, &renderData->nodesDataForRendering));
std::shared_ptr<cNineFractals> fractals(
    new cNineFractals(fractalContainer, paramsContainer));

std::unique_ptr<cRenderer> renderer(new cRenderer(params, fractals, renderData, image));
result = renderer->RenderImage();
```

**sParamRender** is een **platte C++ struct**. De constructor doet de **vertaling** van `cParameterContainer` (string-based map) naar directe float/double/vector members.

---

## 5. Morph-Type Extensie

### 5.1 Stappenplan Nieuw Morph-Type

| Stap | Bestand | Wat |
|------|---------|-----|
| 1 | `one_parameter.hpp` | Voeg toe aan `enumMorphType` |
| 2 | `morph.hpp` | Declareer nieuwe `InterpolateXXX()` methode |
| 3 | `morph.cpp` | Implementeer + voeg toe aan `Interpolate()` switch |
| 4 | `animation_keyframes.cpp` | Voeg kleur toe aan `MorphType2Color()` |
| 5 | `settings.cpp` | Voeg string mapping toe (encoder/decoder) |

### 5.2 De "Verborgen Contracten"

1. **De `angular` Flag**: Elk nieuw algoritme **moet** `NearestNeighbourAngle` + `LimitAngle` respecteren
2. **De `IsEmpty()` Check**: De cache-opbouw slaat lege keyframes over -- je interpolatie moet correct omgaan met ongelijke keyframe-afstanden
3. **Type-Distributiviteit**: Je algoritme moet **per component** werken (x,y,z onafhankelijk)
4. **De `valueActual` Selectie**: Alle interpolaties schrijven naar `valueActual`

---

## 6. Concrete Implementaties

### 6.1 morphElastic -- Ease-Out Elastic Bounce

**Wiskundelijke kern** (Robert Penner easing):

$$f(t) = \begin{cases} 0 & t = 0 \\ 1 & t = 1 \\ 2^{-10t} \cdot \sin\left((10t - \frac{3}{4}) \cdot \frac{2\pi}{3}\right) + 1 & \text{anders} \end{cases}$$

**Toepassing**: De elastic factor transformeert de interpolatiefactor **voordat** lineaire interpolatie plaatsvindt:

```cpp
double elasticFactor = ElasticEaseOut(factor);
double result = v1 + (v2 - v1) * elasticFactor;
```

**Uniek kenmerk**: Dit is een **tween** tussen twee punten, geen spline door 4+ punten. Het produceert een "spring" effect met gegarandeerde overshoot.

### 6.2 morphNoise -- Deterministische Pseudo-Ruis

**Wiskundelijke kern**:

$$f(t, n) = \text{lerp}(v_1, v_2, t) + A \cdot |v_2 - v_1| \cdot \sin\left(2\pi \cdot f_{noise} \cdot n + \phi\right)$$

Waarbij:
- $n$ = globale frame index (integer)
- $A$ = 0.15 (relatieve amplitude)
- $f_{noise}$ = 0.3 cycli per frame
- $\phi$ = fase-offset afgeleid van parameter-waarde (deterministisch)

**Uniek kenmerk**: Dit is het **eerste frame-afhankelijke** morph-type. Zelfs tussen twee identieke keyframes ($v_1 = v_2$) toont `morphNoise` nog steeds trilling.

---

## 7. Volledige Synthese

### 7.1 Globale Architectuurkaart

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                         GEBRUIKERSINTERFACE (Qt)                            │
│  ┌─────────────────────┐  ┌─────────────────────┐  ┌─────────────────────┐ │
│  │   Flight Animation  │  │  Keyframe Animation │  │   Audio/Settings    │ │
│  │   cDockAnimation    │  │   cDockAnimation    │  │   cDockAnimation    │ │
│  └──────────┬──────────┘  └──────────┬──────────┘  └──────────┬──────────┘ │
└─────────────┼────────────────────────┼────────────────────────┼────────────┘
              │                        │                        │
              ▼                        ▼                        ▼
┌──────────────────────────────┐ ┌──────────────────────────────┐ ┌─────────┐
│   cFlightAnimation           │ │   cKeyframeAnimation         │ │cAudio...│
│   (animation_flight.hpp/cpp) │ │   (animation_keyframes.hpp/  │ │TrackCol │
│                              │ │    cpp)                      │ │lection  │
│   • Real-time opname         │ │   • Keyframe management      │ │         │
│   • Physics integrator       │ │   • Tabel-editors            │ │         │
│   • Directe frame-opslag     │ │   • Path visualisatie        │ │         │
└──────────┬───────────────────┘ └──────────┬───────────────────┘ └────┬────┘
           │         ┌──────────────────────┘                          │
           │         │                                                 │
           ▼         ▼                                                 ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                      DATA CONTAINERS (animation_frames.hpp/cpp)             │
│  ┌──────────────────────────────────────────────────────────────────────┐   │
│  │                    cAnimationFrames (basis-klasse)                   │   │
│  │  • QList<sAnimationFrame> frames                                     │   │
│  │  • QList<sParameterDescription> listOfParameters                     │   │
│  │  • cAudioTrackCollection audioTracks                                 │   │
│  │  • AddFrame() / GetFrame() / ModifyFrame()                           │   │
│  └──────────────────────────────────────────────────────────────────────┘   │
│                              ▲                                              │
│                              │ erft van                                      │
│                              ▼                                              │
│  ┌──────────────────────────────────────────────────────────────────────┐   │
│  │                    cKeyframes (keyframes.hpp/cpp)                    │   │
│  │  • GetInterpolatedFrame()                                            │   │
│  │  • InterpolateSingleParameter() -> cMorph                            │   │
│  │  • UpdateFramesIndexesTable()                                        │   │
│  │  • keyframesIndexesTable[] / framesIndexesTable[]                    │   │
│  └──────────────────────────────────────────────────────────────────────┘   │
└────────────────────────────────────┬────────────────────────────────────────┘
                                     │
                                     ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                    INTERPOLATIE-ENGINE (morph.hpp/cpp)                      │
│                                                                             │
│   ┌─────────────┐  ┌─────────────┐  ┌─────────────┐  ┌─────────────────┐  │
│   │   Linear    │  │ CatmullRom  │  │ GSL Splines │  │  Custom (jouw   │  │
│   │  (2 punten) │  │ (4 punten)  │  │ (6 punten)  │  │   uitbreiding)  │  │
│   └─────────────┘  └─────────────┘  └─────────────┘  └─────────────────┘  │
│                                                                             │
│   • NearestNeighbourAngle()  ──►  unwrapping voor hoek-interpolatie       │
│   • LimitAngle()             ──►  wrapping naar [0, 360)                  │
│   • Logaritmische adaptie    ──►  voor exponentiële parameters            │
│                                                                             │
└────────────────────────────────────┬────────────────────────────────────────┘
                                     │
                                     ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│              AUDIO-MODULATIE (animation_frames.hpp/cpp)                     │
│                                                                             │
│   v_final = v_spline * (1 + m * a(t)) + c * a(t)       [positieve modus]   │
│   v_final = v_spline / (1 + m * a(t)) - c * a(t)       [negatieve modus]   │
│                                                                             │
│   waarbij:  a(t) = geamp sample op frame (t - delay)                        │
│             m    = multFactor                                               │
│             c    = additionFactor                                           │
│                                                                             │
└────────────────────────────────────┬────────────────────────────────────────┘
                                     │
                                     ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                     RENDER JOB (render_job.hpp/cpp)                         │
│                                                                             │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │  cRenderJob constructor: DIEPE KOPIE van params + fractal           │   │
│   │  paramsContainer.reset(new cParameterContainer());                  │   │
│   │  *paramsContainer = *_params;                                       │   │
│   └─────────────────────────────────────────────────────────────────────┘   │
│                                  │                                          │
│                                  ▼                                          │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │  UpdateParameters(_params, _fractal)                                │   │
│   │  -> overschrijft interne kopie met nieuwe (geinterpoleerde) waarden │   │
│   └─────────────────────────────────────────────────────────────────────┘   │
│                                  │                                          │
│                                  ▼                                          │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │  Execute() -> PrepareData()                                         │   │
│   │  • LoadTextures(frameNo)                                            │   │
│   │  • renderData->lights.Set(...)                                      │   │
│   │  • renderData->perlinNoise.reset(...)                               │   │
│   └─────────────────────────────────────────────────────────────────────┘   │
│                                  │                                          │
│                                  ▼                                          │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │  sParamRender params(paramsContainer, objectData, nodesData);       │   │
│   │  cNineFractals fractals(fractalContainer, paramsContainer);         │   │
│   │                                                                     │   │
│   │  -> FLATTENING: van string-based map naar directe C++ structs       │   │
│   └─────────────────────────────────────────────────────────────────────┘   │
│                                  │                                          │
│                                  ▼                                          │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │  cRenderer renderer(params, fractals, renderData, image);           │   │
│   │  renderer->RenderImage();  <<<< RENDERING GEBEURT HIER              │   │
│   └─────────────────────────────────────────────────────────────────────┘   │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘
                                     │
                                     ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                         NETRENDER (netrender.hpp/cpp)                       │
│                                                                             │
│   Server                         │                         Client           │
│   -------------------------------┼-------------------------------------      │
│   InitJobsForClients()           │  <-- SendNetRenderSetup()                │
│   Verdeelt frames over clients   │         SetNetRenderStartingFrames()      │
│                                  │                                         │
│   slotNetRenderFinishedFrame()   │  <-- client rendered frame               │
│   -> reservedFrames[] bijwerken  │         ConfirmAndSendRenderedFrames()    │
│   -> nieuwe frames toewijzen     │  ---> SendFramesToDoList()               │
│                                  │                                         │
└─────────────────────────────────────────────────────────────────────────────┘
```

### 7.2 Dataflow per Frame (Keyframe Animatie)

**Stap 1**: Animatie-Controller Initieert
```cpp
for (int frameIndex = 0; frameIndex < totalFrames; frameIndex++) {
```

**Stap 2**: Frame -> Keyframe Mapping
```cpp
int keyframe = GetKeyframeIndex(150);      // bv. 3
int subIndex = GetSubIndex(150);            // bv. 25
```

**Stap 3**: Interpolatie per Parameter
```cpp
cOneParameter onePar = InterpolateSingleParameter(i, keyframe, ..., subIndex, frameIndex, params);
// -> cMorph::Interpolate(150)
// -> ApplyAudioAnimation(150, onePar, ...)
```

**Stap 4**: Consolidatie naar Globale Containers
```cpp
container->SetFromOneParameter(parameterName, oneParameter);
```

**Stap 5**: RenderJob Voorbereiding
```cpp
renderJob->UpdateParameters(params, fractalParams);
```

**Stap 6**: RenderJob Execute
```cpp
renderJob->Execute();
    PrepareData();
    sParamRender sPar(paramsContainer, ...);
    cNineFractals fractals(fractalContainer, paramsContainer);
    cRenderer renderer(&sPar, &fractals, renderData, image);
    renderer->RenderImage();
```

**Stap 7**: Frame Opslag
```cpp
QStringList files = SaveImage(filename, fileType, image, ...);
```

**Stap 8**: NetRender Sync (indien client)
```cpp
ConfirmAndSendRenderedFrames(frameIndex, files);
```

### 7.3 NetRender Distributed Rendering

**Server-Kant**:
```cpp
void InitJobsForClients(const sFrameRanges &frameRanges) {
    int framesPerClient = unrenderedTotal / clientCount / 2 + 1;
    // min/max clipping
    for (int client = 0; client < clientCount; client++) {
        QList<int> startingFrames;
        for (...) {
            if (!alreadyRenderedFrames[f] && !reservedFrames[f]) {
                startingFrames.append(f);
                reservedFrames[f] = true;
            }
        }
        emit SendNetRenderSetup(client, startingFrames);
    }
}
```

**Dynamisch Load Balancing**:
```cpp
void slotNetRenderFinishedFrame(clientIndex, frameIndex, toDoListSize) {
    int countLeft = reservedFrames.count(false);
    int target = countLeft / clientCount / 2;
    int toAssign = target - toDoListSize;
    if (toAssign > 0) {
        // Zoek nieuwe ongereserveerde frames
        emit NetRenderSendFramesToDoList(clientIndex, newFrames);
    }
}
```

### 7.4 Bestandsindex

| Bestand | Regels | Rol |
|---------|--------|-----|
| `animation_path_data.hpp` | 64 | Struct voor pad-visualisatie (camera, lights) |
| `animation_frames.hpp/cpp` | 157 / 642 | Basis data-container + audio-modulatie |
| `animation_flight.hpp/cpp` | 220 / 1726 | Real-time flight opname & rendering |
| `animation_keyframes.hpp/cpp` | 271 / 2578 | Keyframe management, tabel UI, path viz |
| `keyframes.hpp/cpp` | 96 / 340 | Interpolatie-dispatcher + index tabellen |
| `morph.hpp/cpp` | 102 / 688 | Wiskundige interpolatie-algoritmes |
| `one_parameter.hpp/cpp` | 156 / ? | Enkele parameter opslag (type + waarde) |
| `multi_val.hpp/cpp` | 124 / ? | Union-like waarde-opslag (dVal[4], iVal[4], sVal) |
| `parameters.hpp/cpp` | 245 / ? | String-keyed parameter container (QMap) |
| `render_job.hpp/cpp` | 164 / 1328 | Render coordinatie, parameter-flattening |
| `fractparams.hpp/cpp` | ? / ? | `sParamRender` struct definitie |
| `netrender.hpp/cpp` | ? / ? | Distributed rendering netwerk-laag |

### 7.5 Sleutel-Inzichten

1. **Waarom Diepe Kopie in cRenderJob?**
   - De render job maakt een **privé kopie** omdat de animatie-controller het volgende frame al voorbereidt terwijl de vorige rendert
   - De renderer parameters **muteren** (stereo eye offset, detail level)
   - Thread-safety zonder locks

2. **Waarom Component-Gewijze Interpolatie?**
   - Het `cMorph` systeem is type-agnostisch
   - Het voorkomt afhankelijkheid van geometrische vector-interpolatie bibliotheken
   - Hoek-parameters (Euler rotatie) kunnen per as verschillend unwrapten

3. **Waarom Lazy Morph Cache?**
   - Een animatie kan honderden parameters hebben, maar slechts enkele worden per frame gebruikt
   - De cache-opbouw is O(keyframes) per parameter
   - Bij settings-wijziging wordt `morph.clear()` aangeroepen (invalidatie)

4. **Waarom Audio Post-Processing?**
   - De spline cache herbruikbaar blijft onafhankelijk van audio-instellingen
   - Audio kan per frame variëren zonder de geometrische curve te verstoren
   - Het maakt real-time audio preview mogelijk zonder cache-rebuild

### 7.6 Data-Transformaties (Snelle Referentie)

```
[KeyFrame Waarden]
       |
       v  cKeyframes::GetInterpolatedFrame()
[Geinterpoleerde Frame (cParameterContainer)]
       |
       v  cAnimationFrames::ApplyAudioAnimation()
[Geinterpoleerde + Audio Frame (cParameterContainer)]
       |
       v  cRenderJob::UpdateParameters()
[Interne RenderJob Kopie (cParameterContainer)]
       |
       v  sParamRender constructor
[Platte Render Struct (sParamRender)]
       |
       v  cRenderer constructor
[Gerasterde Pixel Data (cImage)]
       |
       v  SaveImage()
[Bestand op Schijf (PNG/EXR)]
```

---

*Dit document vormt de volledige grondwaarheid van de Mandelbulber2 animatie-architectuur. Bij elke toekomstige wijziging -- of het nu een bugfix, nieuw morph-type, of audio-feature is -- is dit de kaart waarmee je de impact kunt traceren van keyframe definitie tot gerenderde pixel.*

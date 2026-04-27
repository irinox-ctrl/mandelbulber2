# MANDELBULBER2 CAMERA TARGET: Nucleaire Diepte-Audit

**Datum**: 2026-04-22  
**Bestanden**: `camera_movement_modes.h`, `camera_target.hpp/cpp`, `algebra.hpp`  
**Scope**: Camera controller, look-at matrix, Euler hoeken, vector normalisatie, edge cases

---

## INHOUDSOPGAVE

1. [Architectuur-Overzicht](#1-architectuur-overzicht)
2. [Camera Movement Modus Enum](#2-camera-movement-modus-enum)
3. [cCameraTarget — De Camera Controller](#3-ccameratarget--de-camera-controller)
4. [SetCameraTargetRotation — Roll-gedreven](#4-setcameratargetrotation--roll-gedreven)
5. [SetCameraTargetTop — Top-gedreven](#5-setcameratargettop--top-gedreven)
6. [De Hoekberekeningen](#6-de-hoekberekeningen)
7. [CorrectAngle — Angle Wrapping](#7-correctangle--angle-wrapping)
8. [Uitlerg & Edge Case Analyse](#8-uitlerg--edge-case-analyse)
9. [Bugs & Riskante Code](#9-bugs--riskante-code)

---

## 1. Architectuur-Overzicht

```
┌─────────────────────────────────────────────────────────────┐
│                    cCameraTarget                              │
│                                                               │
│  Input: camera, target, top (of roll)                        │
│                                                               │
│  ┌─────────────┐    ┌─────────────┐    ┌─────────────┐      │
│  │   yaw       │    │   pitch     │    │   roll      │      │
│  │ (azimuth)   │    │ (elevation) │    │ (bank)      │      │
│  └──────┬──────┘    └──────┬──────┘    └──────┬──────┘      │
│         │                  │                  │              │
│         └──────────────────┼──────────────────┘              │
│                            v                                  │
│              ┌─────────────────────────┐                     │
│              │   Euler rotaties (ZXY)  │                     │
│              │   top = R_z(yaw) *      │                     │
│              │         R_x(pitch) *    │                     │
│              │         R_y(roll) *     │                     │
│              │         (0,0,1)         │                     │
│              └─────────────────────────┘                     │
│                            │                                  │
│                            v                                  │
│              ┌─────────────────────────┐                     │
│              │  forward = target-camera │                     │
│              │  right = forward × top   │                     │
│              └─────────────────────────┘                     │
└─────────────────────────────────────────────────────────────┘
```

De klasse ondersteunt **twee modi**:
- **`constantRoll`**: roll is vast, top vector wordt herberekend
- **`constantTop`**: top vector is vast, roll wordt afgeleid

---

## 2. Camera Movement Modus Enum

```cpp
namespace cameraMovementEnums {
enum enumCameraMovementStepMode {
    relative,   // Stapgrootte is relatief aan huidige positie
    absolute    // Stapgrootte is absolute wereldcoördinaten
};
enum enumCameraMovementMode {
    fixedDistance,  // Camera-target afstand blijft constant
    moveCamera,     // Alleen camera beweegt
    moveTarget      // Alleen target beweegt
};
enum enumCameraRotationMode {
    rotateCamera,       // Camera roteert rond eigen as
    rotateAroundTarget  // Camera roteert rond target
};
}
```

Deze enums worden gebruikt door de **flight recorder** en **UI navigatie** om te bepalen hoe muisbewegingen worden vertaald naar camera transformaties.

---

## 3. cCameraTarget — De Camera Controller

### 3.1 Interne State

```cpp
class cCameraTarget {
    CVector3 camera;        // Camera positie
    CVector3 target;        // Kijkpunt
    double yaw;             // Azimutale hoek (rond Z-as)
    double pitch;           // Elevatie hoek (rond X-as)
    double roll;            // Bank hoek (rond Y-as)
    double distance;        // |target - camera|
    CVector3 forwardVector; // (target - camera) / |target - camera|
    CVector3 topVector;     // "Up" richting
    CVector3 rightVector;   // forward × top
};
```

### 3.2 Constructor

```cpp
cCameraTarget::cCameraTarget() {
    SetCameraTargetTop({-1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0});
}
```

Standaard camera staat op `(-1, 0, 0)`, kijkt naar `(0, 0, 0)`, met top `+Z`.

---

## 4. SetCameraTargetRotation — Roll-gedreven

```cpp
void cCameraTarget::SetCameraTargetRotation(CVector3 _camera, CVector3 _target, double _roll) {
    camera = _camera;
    target = _target;

    if (camera == target) {
        forwardVector = CVector3(0.0, 1.0, 0.0);  // Fallback
    } else {
        forwardVector = (target - camera);
    }
    forwardVector.Normalize();
    distance = (target - camera).Length();

    yaw = forwardVector.GetAlpha() - 0.5 * M_PI;
    pitch = forwardVector.GetBeta();
    roll = _roll;

    yaw = CorrectAngle(yaw);
    pitch = CorrectAngle(pitch);
    roll = CorrectAngle(roll);

    // Top vector = R_z(yaw) * R_x(pitch) * R_y(roll) * (0,0,1)
    topVector = CVector3(0.0, 0.0, 1.0);
    topVector = topVector.RotateAroundVectorByAngle(CVector3(0.0, 1.0, 0.0), roll);
    topVector = topVector.RotateAroundVectorByAngle(CVector3(1.0, 0.0, 0.0), pitch);
    topVector = topVector.RotateAroundVectorByAngle(CVector3(0.0, 0.0, 1.0), yaw);

    rightVector = forwardVector.Cross(topVector);
}
```

### 4.1 Euler Rotatie Volgorde

De top vector wordt berekend via drie opeenvolgende rotaties:
1. **Roll** rond Y-as: `(0,0,1) → R_y(roll)`
2. **Pitch** rond X-as: `→ R_x(pitch)`
3. **Yaw** rond Z-as: `→ R_z(yaw)`

Dit is een **ZXY Euler sequentie** (intrinsiek: yaw → pitch → roll).

De resulterende rotatiematrix is:
$$R = R_z(yaw) \cdot R_x(pitch) \cdot R_y(roll)$$

---

## 5. SetCameraTargetTop — Top-gedreven

```cpp
void cCameraTarget::SetCameraTargetTop(CVector3 _camera, CVector3 _target, CVector3 _top) {
    camera = _camera;
    target = _target;

    if (camera == target) {
        forwardVector = CVector3(0.0, 1.0, 0.0);
    } else {
        forwardVector = (target - camera);
    }
    forwardVector.Normalize();
    distance = (target - camera).Length();

    yaw = forwardVector.GetAlpha() - 0.5 * M_PI;
    pitch = forwardVector.GetBeta();

    CVector3 topVectorTemp = _top;
    topVectorTemp.Normalize();  // ← CRITICAL: kan delen door nul!
    topVectorTemp = topVectorTemp.RotateAroundVectorByAngle(CVector3(0.0, 0.0, 1.0), -yaw);
    topVectorTemp = topVectorTemp.RotateAroundVectorByAngle(CVector3(1.0, 0.0, 0.0), -pitch);
    roll = -atan2(topVectorTemp.z, topVectorTemp.x) + 0.5 * M_PI;

    yaw = CorrectAngle(yaw);
    pitch = CorrectAngle(pitch);
    roll = CorrectAngle(roll);

    // Herbouw top vector (idem als SetCameraTargetRotation)
    topVector = CVector3(0.0, 0.0, 1.0);
    topVector = topVector.RotateAroundVectorByAngle(CVector3(0.0, 1.0, 0.0), roll);
    topVector = topVector.RotateAroundVectorByAngle(CVector3(1.0, 0.0, 0.0), pitch);
    topVector = topVector.RotateAroundVectorByAngle(CVector3(0.0, 0.0, 1.0), yaw);

    rightVector = forwardVector.Cross(topVector);
}
```

### 5.1 Roll Extractie

```cpp
topVectorTemp.Normalize();
topVectorTemp = topVectorTemp.RotateAroundVectorByAngle(CVector3(0.0, 0.0, 1.0), -yaw);
topVectorTemp = topVectorTemp.RotateAroundVectorByAngle(CVector3(1.0, 0.0, 0.0), -pitch);
roll = -atan2(topVectorTemp.z, topVectorTemp.x) + 0.5 * M_PI;
```

**Wiskunde**:
1. Normaliseer de input top vector
2. Roteer terug met **-yaw** (omgekeerde Z-rotatie)
3. Roteer terug met **-pitch** (omgekeerde X-rotatie)
4. De overgebleven vector ligt in het XZ-vlak; de hoek is de roll

Na deze un-rotaties:
$$topVectorTemp = R_x(-pitch) \cdot R_z(-yaw) \cdot \hat{t}$$

De roll wordt dan:
$$roll = -\arctan2(top_z, top_x) + \frac{\pi}{2}$$

De `+ π/2` verschuift zodat roll=0 overeenkomt met top=(0,0,1).

---

## 6. De Hoekberekeningen

### 6.1 GetAlpha / GetBeta (uit algebra.hpp)

```cpp
inline double GetAlpha() const { return atan2(y, x); }
inline double GetBeta() const { return atan2(z, sqrt(x * x + y * y)); }
```

| Functie | Bereik | Betekenis |
|---------|--------|-----------|
| `GetAlpha()` | [-π, π] | Azimutale hoek in XY-vlak |
| `GetBeta()` | [-π/2, π/2] | Elevatie hoek vanaf XY-vlak |

### 6.2 Yaw / Pitch Mapping

```cpp
yaw = forwardVector.GetAlpha() - 0.5 * M_PI;
pitch = forwardVector.GetBeta();
```

**Waarom `- 0.5*M_PI`?**

`GetAlpha()` returnt de hoek van de vector in het XY-vlak, gemeten vanaf de **X-as**. Maar yaw is traditioneel gemeten vanaf de **Y-as** (forward = +Y in het scherm). De `-π/2` correctie draait het coördinaatsysteem.

**Voorbeeld**:
- Forward = (1, 0, 0) → GetAlpha = 0 → yaw = -π/2 (kijkt naar +X)
- Forward = (0, 1, 0) → GetAlpha = π/2 → yaw = 0 (kijkt naar +Y)
- Forward = (-1, 0, 0) → GetAlpha = π → yaw = π/2 (kijkt naar -X)

---

## 7. CorrectAngle — Angle Wrapping

```cpp
static double CorrectAngle(double angle) {
    return fmod(angle + 3 * M_PI, 2 * M_PI) - M_PI;
}
```

**Doel**: Map een willekeurige hoek naar het interval `[-π, π]`.

**Werking**:
1. `angle + 3π` — verschuift zodat de input altijd positief is (als angle > -3π)
2. `fmod(..., 2π)` — neemt de rest na deling door 2π
3. `- π` — verschuift terug naar [-π, π]

**Voorbeelden**:
| Input | +3π | fmod(…, 2π) | -π | Output |
|-------|-----|-------------|-----|--------|
| 0 | 3π | π | 0 | 0 |
| π | 4π | 0 | -π | -π |
| 3π | 6π | 0 | -π | -π |
| -2π | π | π | 0 | 0 |
| -5π | -2π | ??? | ??? | UB |

---

## 8. Uitlerg & Edge Case Analyse

### 8.1 Camera == Target (nul afstand)

```cpp
if (camera == target) {
    forwardVector = CVector3(0.0, 1.0, 0.0);
} else {
    forwardVector = (target - camera);
}
forwardVector.Normalize();
```

**Exact gelijk**: forward wordt (0,1,0). distance = 0. yaw = 0 - π/2 = -π/2. pitch = 0. → Camera kijkt naar +Y, top is +Z. **Correct**.

**Bijna gelijk** (bv. |target-camera| = 1e-16): De `==` check faalt (exact float equality). `forwardVector` is een heel kleine vector. `Normalize()` deelt door `Length() = 1e-16`. Dit produceert een enorm gescaleerde vector. De `Normalize()` functie uit algebra.hpp doet `norm = 1.0 / Length()` — bij Length=1e-16 is norm=1e16. Het resultaat is numeriek correct maar **verliest significante cijfers**. yaw en pitch kunnen onverwachte waarden krijgen door afrondingsfouten.

### 8.2 Top Vector == Nulvector

```cpp
CVector3 topVectorTemp = _top;
topVectorTemp.Normalize();  // ← DIVIDE BY ZERO
```

Als `_top = (0, 0, 0)`, dan `Length() = 0`, `norm = 1.0 / 0 = inf`, en de hele applicatie krijgt `inf` waarden in de rotatiematrix. Dit is **undefined behavior** (delen door nul in floating point produceert inf, maar de resulterende topVector is NaN).

### 8.3 Forward || Top (parallelle vectoren)

```cpp
rightVector = forwardVector.Cross(topVector);
```

Als forward en top parallel zijn (of anti-parallel):
- `rightVector = (0, 0, 0)`
- Dit breekt het orthonormale coördinaatsysteem
- De renderer gebruikt rightVector voor het opbouwen van de view matrix
- Dit kan leiden tot **gedegenereerde beelden** of delingen door nul

**Wanneer gebeurt dit?**
- Camera kijkt recht omhoog (pitch = +π/2): forward = (0,0,1), top wordt ook (0,0,1) na rotaties
- Camera kijkt recht omlaag (pitch = -π/2): forward = (0,0,-1), top wordt (0,0,-1)

Dit is **gimbal lock**! Bij pitch = ±π/2 is de yaw rotatie rond dezelfde as als de roll rotatie.

### 8.4 Forward Vector langs Z-as

```cpp
yaw = forwardVector.GetAlpha() - 0.5 * M_PI;
```

Als forward = (0, 0, ±1): `GetAlpha() = atan2(0, 0) = 0` (implementation-defined!). yaw = -π/2. Maar de forward vector heeft geen azimutale component — **yaw is arbitrair** wanneer je recht omhoog/omlaag kijkt.

### 8.5 Roll bij top parallel aan Y-as

```cpp
roll = -atan2(topVectorTemp.z, topVectorTemp.x) + 0.5 * M_PI;
```

Na un-rotatie: als de originele top vector parallel is aan de forward vector (dus parallel aan Y-as na un-rotatie van yaw), dan `topVectorTemp = (0, ±1, 0)`.

`atan2(0, 0) = 0` → roll = π/2. Dit is een **willekeurige keuze**. Er is geen unieke roll wanneer top parallel is aan forward.

### 8.6 CorrectAngle met extreme input

```cpp
static double CorrectAngle(double angle) {
    return fmod(angle + 3 * M_PI, 2 * M_PI) - M_PI;
}
```

**Probleem 1**: `angle + 3*M_PI` kan overflowen als angle ≈ 1e308 (max double).

**Probleem 2**: Als angle = NaN of inf, dan is `fmod(NaN, 2π) = NaN`, en het resultaat is NaN. Dit verspreidt zich door het hele systeem.

**Probleem 3**: Als angle < -3π (bijv. -10π), dan `angle + 3π = -7π` (negatief). `fmod(-7π, 2π)` is **implementation-defined** in C++. GCC returnt -π, MSVC kan π retourneren. Dit betekent dat de output platform-afhankelijk kan zijn.

---

## 9. Bugs & Riskante Code

### 🐛 CRITICAL BUG #1 — `topVectorTemp.Normalize()` kan delen door nul

```cpp
CVector3 topVectorTemp = _top;
topVectorTemp.Normalize();  // ← CRASH als _top = (0,0,0)
```

**Impact**: Als een UI widget of animatie keyframe per ongeluk een nul top vector produceert, crasht de hele renderer met NaN/Inf waarden.

**Fix**:
```cpp
CVector3 topVectorTemp = _top;
if (topVectorTemp.Length() > 0.0) {
    topVectorTemp.Normalize();
} else {
    topVectorTemp = CVector3(0.0, 0.0, 1.0);  // Fallback
}
```

---

### 🐛 CRITICAL BUG #2 — Numerieke instabiliteit bij camera ≈ target

```cpp
if (camera == target) {
    forwardVector = CVector3(0.0, 1.0, 0.0);
} else {
    forwardVector = (target - camera);
}
forwardVector.Normalize();
```

De `==` check gebruikt **exacte float equality**. Als camera en target op 1e-16 afstand zijn (bijna gelijk maar niet exact), faalt de check en wordt een heel kleine vector genormaliseerd. Dit verliest **alle significante cijfers**.

**Fix**:
```cpp
const double epsilon = 1e-12;
if ((camera - target).Length() < epsilon) {
    forwardVector = CVector3(0.0, 1.0, 0.0);
} else {
    forwardVector = (target - camera);
    forwardVector.Normalize();
}
```

---

### 🐛 HIGH BUG #3 — `fmod` in CorrectAngle is implementation-defined voor negatieve input

```cpp
static double CorrectAngle(double angle) {
    return fmod(angle + 3 * M_PI, 2 * M_PI) - M_PI;
}
```

Als `angle < -3π`, is `angle + 3π` negatief en `fmod(negatief, positief)` is **implementation-defined**.

**Fix** (robuste angle wrapping):
```cpp
static double CorrectAngle(double angle) {
    angle = fmod(angle + M_PI, 2 * M_PI);
    if (angle < 0) angle += 2 * M_PI;
    return angle - M_PI;
}
```

Of nog beter (geen fmod afhankelijkheid):
```cpp
static double CorrectAngle(double angle) {
    const double twoPi = 2.0 * M_PI;
    angle = fmod(angle + M_PI, twoPi);
    if (angle < 0) angle += twoPi;
    return angle - M_PI;
}
```

---

### 🐛 MEDIUM BUG #4 — Gimbal lock bij pitch = ±π/2

```cpp
topVector = CVector3(0.0, 0.0, 1.0);
topVector = topVector.RotateAroundVectorByAngle(CVector3(0.0, 1.0, 0.0), roll);
topVector = topVector.RotateAroundVectorByAngle(CVector3(1.0, 0.0, 0.0), pitch);
topVector = topVector.RotateAroundVectorByAngle(CVector3(0.0, 0.0, 1.0), yaw);
rightVector = forwardVector.Cross(topVector);
```

Bij pitch = π/2:
- forward = (0, 0, 1)
- Na rotaties: top = (0, 0, 1) (of -1, afhankelijk van yaw/roll)
- right = forward × top = (0, 0, 0)

Dit is **gimbal lock** — de right vector verdwijnt. De view matrix is dan:
```
[ right=0   ?   forward ]
[   ?       ?     ?    ]
[   0       0     1    ]
```

Dit is een singuliere matrix. De renderer kan hier delen door nul.

**Fix**: Gebruik quaternion rotaties in plaats van Euler hoeken. Dit is een architecturale wijziging.

---

### ⚠️ RISICO #5 — `distance` kan nul zijn

```cpp
distance = (target - camera).Length();
```

Als camera == target, is distance = 0. Dit wordt niet gebruikt voor deling, maar sommige UI elementen of animatie interpolatie kunnen hier niet goed mee omgaan.

---

### ⚠️ RISICO #6 — `atan2(0, 0)` is implementation-defined

```cpp
roll = -atan2(topVectorTemp.z, topVectorTemp.x) + 0.5 * M_PI;
```

Als `topVectorTemp = (0, ±1, 0)` (parallel aan Y-as), dan `atan2(0, 0)` returnt 0 op de meeste platforms. Maar de C++ standaard garandeert dit niet.

---

### ⚠️ RISICO #7 — `SetCamera`/`SetTarget` roepen de volledige reconstructie aan

```cpp
void cCameraTarget::SetCamera(CVector3 _camera, enumRotationMode mode) {
    camera = _camera;
    if (mode == constantRoll) {
        SetCameraTargetRotation(camera, target, roll);
    } else {
        SetCameraTargetTop(camera, target, topVector);
    }
}
```

Elke kleine camera update triggert **alle** berekeningen opnieuw (forward, top, right, yaw, pitch, roll). Dit is O(1) dus niet erg, maar het is een potentiele bron van drift als er afrondingsfouten accumuleren.

---

*De camera controller is elegant in zijn eenvoud, maar heeft meerdere edge cases rond nul vectoren, gimbal lock, en platform-afhankelijk gedrag bij extreme hoekwaarden. De twee CRITICAL bugs (#1 en #2) zijn eenvoudig te fixen en zouden de stabiliteit aanzienlijk verbeteren.*

---

## 10. Toekomstige Verbetering: Quaternion Architectuur

**Status**: Gepland voor latere implementatie  
**Scope**: Interne refactor van Euler (yaw/pitch/roll) naar quaternion representatie

### Waarom quaternions?

| Huidig probleem (Euler ZXY) | Quaternion oplossing |
|---------------------------|---------------------|
| Gimbal lock bij pitch = ±π/2 | **Geen singulariteiten** — volledige boldekking |
| Camera springt bij over-the-top rotatie | **Vloeiende rotatie** over alle assen |
| Keyframe animatie hakkeltjes (Euler lerp) | **Slerp** — natuurlijke boog over de eenheidsbol |
| 3× matrix multiplicaties per frame | **1× quaternion → matrix** conversie |
| Numerieke drift bij cumulatieve rotaties | **Quaternion normalisatie** is robuuster dan Euler angle wrapping |

### Architectuur

```
┌─────────────────────────────────────────────────────────────┐
│                    cCameraTarget (quaternion)                 │
│                                                               │
│  Intern: CVector3 position;  // camera positie               │
│          CQuaternion rotation; // oriëntatie                 │
│                                                               │
│  Externe API (behouden):                                      │
│    GetRotation() → CVector3(yaw, pitch, roll)               │
│    GetForwardVector() → CVector3                            │
│    GetTopVector() → CVector3                                │
│    GetRightVector() → CVector3                              │
│                                                               │
│  Conversie:                                                   │
│    quaternion → rotation matrix (render_worker)              │
│    quaternion → yaw/pitch/roll (parameter opslag)            │
└─────────────────────────────────────────────────────────────┘
```

### Impact op gebruikerservaring

**Wel merkbaar**:
- Vloeiende over-the-top rotatie zonder gimbal lock
- Natuurlijkere flight animatie bochten
- Betere camera interpolatie in keyframes (>180° rotaties)

**Niet merkbaar**:
- Renderkwaliteit blijft identiek
- UI ziet er hetzelfde uit
- Rendertijd verschil is verwaarloosbaar

### Implementatieplan

1. **algebra.hpp** — `CQuaternion` class toevoegen
   - `FromAxisAngle(axis, angle)`
   - `ToRotationMatrix()`
   - `Slerp(q1, q2, t)`
   - `Normalize()`
   - `RotateVector(v)`

2. **camera_target.hpp/cpp** — Interne representatie wijzigen
   - `CVector3 position` + `CQuaternion rotation` in plaats van `camera/target/yaw/pitch/roll`
   - Constructors en setters bouwen quaternion uit input
   - Getters berekenen vectoren en Euler hoeken on-the-fly

3. **render_worker.cpp** — View matrix opbouw
   - Vervang `mRot.RotateZ(yaw); mRot.RotateX(pitch); mRot.RotateY(roll)`
   - Door `mRot = rotation.ToRotationMatrix()`

4. **Risico** — Quaternion → Euler conversie heeft zelf een "pole problem" bij pitch = ±90°. De parameter container slaat nog steeds yaw/pitch/roll op, dus deze edge case blijft bestaan in de opslaglaag.

### Aanbeveling

Quaternions zijn **technisch superieur** voor rotaties, maar voor Mandelbulber2 is het voordeel subtiel tenzij je veel met extreme camera hoeken of animatie werkt. De **pragmatische hardening** (bugs #1-#4 fixen in de huidige Euler code) heeft meer directe impact op stabiliteit. Quaternions zijn een waardevolle **latere refactor** wanneer er tijd is voor grondig testen van alle 20+ callers.

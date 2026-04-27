# MANDELBULBER2 ALGEBRA: Nucleaire Diepte-Audit

**Datum**: 2026-04-22  
**Bestanden**: `algebra.hpp` (829 regels), `algebra.cpp` (735 regels)  
**Scope**: CVector2/3/4, CMatrix33/44, CRotationMatrix/44, StructuredCVector3

---

## INHOUDSOPGAVE

1. [Architectuur-Overzicht](#1-architectuur-overzicht)
2. [CVector3 Deep-Dive](#2-cvector3-deep-dive)
3. [De Experimentele repeatMod Familie](#3-de-experimentele-repeatmod-familie)
4. [CVector4 Analyse](#4-cvector4-analyse)
5. [Matrix & Rotatie Systemen](#5-matrix--rotatie-systemen)
6. [Gevonden Bugs & Riskante Code](#6-gevonden-bugs--riskante-code)
7. [Performance-Analyse](#7-performance-analyse)
8. [Extensie-Patronen](#8-extensie-patronen)

---

## 1. Architectuur-Overzicht

De algebra-laag is de **fundering** van alle 3D/4D berekeningen in Mandelbulber. Het volgt een **klassieke game-engine structuur**:

```
CVector2<T>     (templated 2D) ──► UI, muis-coordinaten, texture mapping
      |
      v
CVector3        (3D vector) ─────► Camera, posities, fractal DE, lichten
      |
      v
CVector4        (4D vector) ─────► Kleuren (RGB+alpha), quaternion-achtig
      |
      v
CMatrix33/44    (platte matrices) ──► Rotaties, transformaties
      |
      v
CRotationMatrix/44 (hoog-niveau) ──► Euler-rotaties, look-at matrices
```

### Design-Filosofie

| Principe | Implementatie |
|----------|---------------|
| **Header-heavy** | 90% van de code zit in `.hpp` (inline) voor compiler optimalisatie |
| **Geen templates voor 3D/4D** | Alleen `CVector2<T>` is getemplated; 3D/4D zijn hardcoded `double` |
| **Directe member access** | `x`, `y`, `z`, `w` zijn public members — geen getters/setters |
| **Minimalistisch** | Geen operator overloading voor dot/cross als vriend-functies; alles is member of global inline |

---

## 2. CVector3 Deep-Dive

### 2.1 Constructors

| Constructor | Parameters | Gebruik |
|-------------|------------|---------|
| Default | `()` | `(0, 0, 0)` |
| Cartesian | `(x, y, z)` | Standaard |
| Spherical | `(alpha, beta)` | $x = \cos\beta \cos\alpha$, $y = \cos\beta \sin\alpha$, $z = \sin\beta$ |
| Copy | `(const CVector3&)` | Standaard |
| Array | `(const double[3])` | **Fataal bij nullptr!** — roept `qFatal()` aan |

**Kritieke opmerking**: De array-constructor doet een **null-check**:
```cpp
inline explicit CVector3(const double vector[3]) {
    if (vector) { x = vector[0]; y = vector[1]; z = vector[2]; }
    else { qFatal("Assigned nullptr to CVector3 as initialization!"); }
}
```
Dit is de **enige** constructor die runtime-validatie doet. Alle andere constructors vertrouwen op correcte input.

### 2.2 Operator Semantiek

#### Arithmetic
```cpp
CVector3 operator+(const CVector3&)   // Component-gewijze optelling
CVector3 operator-(const CVector3&)   // Component-gewijze aftrekking
CVector3 operator*(double)            // Scalaire vermenigvuldiging
CVector3 operator*(const CVector3&)   // Hadamard product (component-gewijs!)
CVector3 operator/(double)            // Scalaire deling
CVector3 operator/(const CVector3&)   // Hadamard deling (component-gewijs!)
```

**Waarschuwing**: `v1 * v2` is **geen** dot-product of cross-product! Het is het **Hadamard product** (element-wise vermenigvuldiging):
$$(v_1 * v_2)_i = v_{1i} \cdot v_{2i}$$

Dit is een **niet-standaard** conventie in wiskunde. In de meeste C++ math libraries (GLM, Eigen) betekent `operator*` het dot-product of matrix-vermenigvuldiging. Hier is het expliciet component-gewijs.

#### De `%` Operator (Modulo)
```cpp
inline CVector3 operator%(const CVector3 &vector) const {
    return CVector3(
        (vector.x > 0.0 ? fmod(x, vector.x) : x),
        (vector.y > 0.0 ? fmod(y, vector.y) : y),
        (vector.z > 0.0 ? fmod(z, vector.z) : z)
    );
}
```

Dit is **component-gewijs modulo** met een guard tegen negatieve delers. De `fmod` functie behoudt het teken van de teller, dus `(-5) % 3 = -2`.

#### De `repeatMod` Familie (ZIE HOOFDSTUK 3)

### 2.3 Wiskundige Operaties

| Methode | Formule | Complexiteit |
|---------|---------|--------------|
| `Length()` | $\sqrt{x^2 + y^2 + z^2}$ | O(1), 3 mul + 2 add + 1 sqrt |
| `LengthPow(p)` | $(\|x\|^p + \|y\|^p + \|z\|^p)^{1/p}$ | O(1), Minkowski afstand van orde p |
| `Dot(v)` | $x_1 x_2 + y_1 y_2 + z_1 z_2$ | O(1) |
| `Cross(v)` | Standaard 3D kruisproduct | O(1) |
| `Normalize()` | Deelt door Length(), geeft factor terug | O(1) |
| `Abs()` | $(\|x\|, \|y\|, \|z\|)$ | O(1) |
| `GetAlpha()` | $\text{atan2}(y, x)$ — azimut | O(1) |
| `GetBeta()` | $\text{atan2}(z, \sqrt{x^2+y^2})$ — elevatie | O(1) |
| `IsNotANumber()` | `!(gsl_finite(x) & gsl_finite(y) & gsl_finite(z))` | O(1) |

### 2.4 Rotatie: Rodrigues' Formule

```cpp
CVector3 CVector3::RotateAroundVectorByAngle(const CVector3 &axis, double angle) const {
    CVector3 vector = *this * cos(angle);
    vector += (axis.Cross(*this)) * sin(angle);
    vector += axis * axis.Dot(*this) * (1 - cos(angle));
    return vector;
}
```

Dit is de **Rodrigues' rotatie formule**:
$$\mathbf{v}_{rot} = \mathbf{v}\cos\theta + (\mathbf{a} \times \mathbf{v})\sin\theta + \mathbf{a}(\mathbf{a} \cdot \mathbf{v})(1 - \cos\theta)$$

Waarbij:
- $\mathbf{v}$ = de te roteren vector
- $\mathbf{a}$ = de rotatie-as (genormaliseerd)
- $\theta$ = de rotatie-hoek

**Let op**: Deze implementatie veronderstelt **niet** dat `axis` al genormaliseerd is! Als `axis` niet eenheidslengte heeft, wordt de projectie-term $(1 - \cos\theta)$ verkeerd geschaald. In de praktijk wordt dit vaak correct aangeroepen, maar het is een **stil contract**.

### 2.5 Global Helpers

```cpp
inline CVector3 operator*(double scalar, const CVector3 &vector);  // Commutatieve scalaar
inline CVector3 operator/(double scalar, const CVector3 &vector);  // Scalaar / vector (component-gewijs!)
inline CVector3 fabs(CVector3 v);                                   // Component-gewijs abs
inline CVector3 max(const CVector3&, const CVector3&);              // Component-gewijs max
inline CVector3 min(const CVector3&, const CVector3&);              // Component-gewijs min
```

De `operator/(double, CVector3)` is opnieuw **niet-standaard**:
$$(s / \mathbf{v})_i = s / v_i$$

Dit is nuttig voor **inverse scaling** maar kan verwarring veroorzaken.

---

## 3. De Experimentele repeatMod Familie

**Kritische ontdekking**: De `v2_experiment` branch bevat **zeven** `repeatMod` varianten die **niet** in standaard Mandelbulber2 voorkomen. Dit zijn domain-repetitie (tiling) algoritmes voor fractal rendering.

### 3.1 repeatMod (Basis)

```cpp
inline CVector3 repeatMod(const CVector3 &vector) const {
    if (vector.Length() == 0.0) return *this;
    return (((*this - vector * 0.5) % vector) + vector) % vector - vector * 0.5;
}
```

**Wiskunde**: Symmetrische tiling rond de oorsprong met periode `vector`.

Stap-voor-stap:
1. `*this - vector * 0.5` — verschuif naar symmetrisch bereik
2. `% vector` — component-gewijs modulo
3. `+ vector` — corrigeer negatieve waarden
4. `% vector` — nogmaals modulo
5. `- vector * 0.5` — verschuif terug naar symmetrisch bereik $[-p/2, p/2]$

**Resultaat**: De ruimte wordt oneindig herhaald met periode `vector`, gecentreerd op de oorsprong.

### 3.2 repeatModMirror

```cpp
inline CVector3 repeatModMirror(const CVector3 &vector) const {
    CVector3 modded = repeatMod(vector);
    return CVector3(
        (modded.x < 0.0 ? -modded.x : modded.x),
        (modded.y < 0.0 ? -modded.y : modded.y),
        (modded.z < 0.0 ? -modded.z : modded.z));
}
```

**Effect**: Mirrored tiling (kaleidoscope). Negatieve helften worden gespiegeld naar positief. Resultaat bereik: $[0, p/2]$.

### 3.3 repeatModRotation

```cpp
inline CVector3 repeatModRotation(const CVector3 &vector, double stepDegrees) const {
    CVector3 modded = repeatMod(vector);
    double angle = stepDegrees * M_PI / 180.0;
    // Rotatie rond Z-as
    CVector3 rotated;
    rotated.x = modded.x * cos(angle) - modded.y * sin(angle);
    rotated.y = modded.x * sin(angle) + modded.y * cos(angle);
    rotated.z = modded.z;
    return rotated;
}
```

**Effect**: Na elke cel wordt de inhoud geroteerd rond de Z-as. Dit creëert **spirale-achtige** tiling patronen.

### 3.4 repeatModFibonacci

```cpp
inline CVector3 repeatModFibonacci(int count, double spread) const {
    const double goldenAngle = M_PI * (3.0 - sqrt(5.0));  // ~137.5°
    double r = Length();
    double theta = atan2(y, x);
    double ringSpacing = spread * 0.5;
    int ring = int(r / ringSpacing);
    if (ring < 1) ring = 1;
    double targetR = ring * ringSpacing;
    double targetTheta = fmod(ring * goldenAngle + theta, 2.0 * M_PI);
    return CVector3(targetR * cos(targetTheta), targetR * sin(targetTheta), z);
}
```

**Wiskunde**: De **gulden hoek** ($\approx 137.5°$) wordt gebruikt voor phyllotaxis-patronen (zonnebloem-spiralen).

**Opmerking**: De `count` parameter wordt **niet gebruikt** (`(void)count`). Dit is **dode code**.

### 3.5 repeatModBrick

```cpp
inline CVector3 repeatModBrick(const CVector3 &vector) const {
    CVector3 modded = repeatMod(vector);
    int cellY = int(floor(y / vector.y));
    int cellZ = int(floor(z / vector.z));
    if (cellY % 2 != 0) modded.x += vector.x * 0.5;
    if (cellZ % 4 != 0) modded.x += vector.x * 0.25;
    return modded;
}
```

**Effect**: Baksteen-patroon (running bond). Elke oneven rij in Y wordt half een cel verschoven.

### 3.6 repeatModHoneycomb

```cpp
inline CVector3 repeatModHoneycomb(const CVector3 &vector) const {
    double hexW = vector.x;
    double hexH = vector.y * sqrt(3.0) / 2.0;
    int row = int(floor(y / hexH));
    double offsetX = (row % 2) * hexW * 0.5;
    double localX = x - offsetX;
    int col = int(floor(localX / hexW));
    CVector3 modded(localX - col * hexW, y - row * hexH, z);
    modded.x += offsetX;
    return modded;
}
```

**Wiskunde**: Hexagonale tiling in het XY-vlak. De hoogte van een hexagon is $\frac{\sqrt{3}}{2} \times \text{width}$.

### 3.7 repeatModSpiral

```cpp
inline CVector3 repeatModSpiral(
    const CVector3 &vector, const CVector3 &step, 
    const CVector3 &angle, const CVector3 &radius) const {
    (void)angle;   // <<< DODE PARAMETERS
    (void)radius;  // <<< DODE PARAMETERS
    CVector3 modded = repeatMod(vector);
    int cellX = int(floor(x / vector.x));
    int cellY = int(floor(y / vector.y));
    int cellZ = int(floor(z / vector.z));
    int cellIdx = cellX + cellY * 10 + cellZ * 100;
    double t = cellIdx * 0.1;
    modded.x += step.x * t * cos(t);
    modded.y += step.y * t * sin(t);
    modded.z += step.z * t;
    return modded;
}
```

**Effect**: Archimedische spiraal offset per cel.

**Problemen**:
- `angle` en `radius` worden **niet gebruikt** — dode parameters
- De cel-index berekening (`cellX + cellY * 10 + cellZ * 100`) werkt alleen correct voor kleine positieve cellen
- Er is geen wrap-around logica voor negatieve cellen

### 3.8 repeatModWave

```cpp
inline CVector3 repeatModWave(
    const CVector3 &vector, const CVector3 &amplitude, 
    const CVector3 &frequency, const CVector3 &phase, int axis) const {
    CVector3 modded = repeatMod(vector);
    if (axis == 0) { // wave along X, displacement in YZ
        modded.y += amplitude.y * sin(modded.x * frequency.y + phase.y);
        modded.z += amplitude.z * sin(modded.x * frequency.z + phase.z);
    }
    else if (axis == 1) { // wave along Y, displacement in XZ
        modded.x += amplitude.x * sin(modded.y * frequency.x + phase.x);
        modded.z += amplitude.z * sin(modded.y * frequency.z + phase.z);
    }
    else { // wave along Z, displacement in XY
        modded.x += amplitude.x * sin(modded.z * frequency.x + phase.x);
        modded.y += amplitude.y * sin(modded.z * frequency.y + phase.y);
    }
    return modded;
}
```

**Effect**: Sinusoïdale vervorming binnen elke cel. De golf loopt langs één as en verplaatst punten in de orthogonale vlakken.

---

## 4. CVector4 Analyse

### 4.1 Constructie

```cpp
CVector4()                                   // (0, 0, 0, 0)
CVector4(double _x, double _y, double _z, double _w)  // Direct
CVector4(const CVector3 &vectXYZ, double _w)          // Van 3D + w
CVector4(const double v[4])                           // Van array
```

**Interessant**: Er is **geen** `qFatal()` check voor de array-versie (in tegenstelling tot `CVector3`).

### 4.2 Unieke Operaties

```cpp
inline CVector4 operator*(const CVector3 &v) const {
    return CVector4(x * v.x, y * v.y, z * v.z, w);  // w blijft onveranderd!
}
```

De `CVector3` multiplicatie laat `w` onveranderd. Dit is handig voor kleur-vermenigvuldiging waarbij alpha behouden blijft.

```cpp
inline void GetXYZWInto(CVector3 &v, double &wOutput) const;
inline CVector3 GetXYZ() const;
inline std::array<double, 4> GetArray() const;
```

### 4.3 Modulo

```cpp
inline CVector4 operator%(const CVector4 &vector) const {
    return CVector4(
        (vector.x > 0.0 ? fmod(x, vector.x) : x),
        (vector.y > 0.0 ? fmod(y, vector.y) : y),
        (vector.z > 0.0 ? fmod(z, vector.z) : z),
        (vector.w > 0.0 ? fmod(w, vector.w) : w)
    );
}
```

Identiek aan CVector3 maar met 4 componenten.

### 4.4 Rotatie

```cpp
CVector4 CVector4::RotateAroundVectorByAngle(const CVector3 &axis, double angle) const {
    const CVector3 oldVector = GetXYZ();
    CVector3 vector = oldVector * cos(angle);
    vector += (axis.Cross(oldVector)) * sin(angle);
    vector += axis * axis.Dot(oldVector) * (1 - cos(angle));
    return CVector4(vector, w);  // w blijft behouden!
}
```

**Belangrijk**: De 4D rotatie roteert **alleen de XYZ component** rond de 3D as. `w` wordt onveranderd teruggegeven. Dit is correct voor rotaties in 3D-ruimte van 4D homogene coördinaten.

---

## 5. Matrix & Rotatie Systemen

### 5.1 CMatrix33

Een **platte** 3x3 matrix met directe member-access:

```cpp
class CMatrix33 {
public:
    double m11, m12, m13;
    double m21, m22, m23;
    double m31, m32, m33;
};
```

**Kolom-major vs rij-major**: De constructor van kolom-vectoren:
```cpp
CMatrix33(const CVector3 &v1, const CVector3 &v2, const CVector3 &v3) {
    m11 = v1.x; m12 = v2.x; m13 = v3.x;  // eerste rij = x-componenten van kolom-vectoren
    m21 = v1.y; m22 = v2.y; m23 = v3.y;  // tweede rij = y-componenten
    m31 = v1.z; m32 = v2.z; m33 = v3.z;  // derde rij = z-componenten
}
```

Dit is **kolom-major** opslag: de input vectoren $v_1, v_2, v_3$ worden de **kolommen** van de matrix.

De matrix-vector vermenigvuldiging:
```cpp
CVector3 CMatrix33::operator*(const CVector3 &vector) const {
    result.x = m11 * vector.x + m12 * vector.y + m13 * vector.z;
    result.y = m21 * vector.x + m22 * vector.y + m23 * vector.z;
    result.z = m31 * vector.x + m32 * vector.y + m33 * vector.z;
    return result;
}
```

Dit is **correct** voor kolom-major: $\mathbf{M} \cdot \mathbf{v}$ waarbij $\mathbf{v}$ een kolom-vector is.

### 5.2 CRotationMatrix

**De "zero" optimalisatie**:
```cpp
class CRotationMatrix {
    CMatrix33 matrix;
    bool zero;  // <-- optimalisatie flag
};
```

Wanneer `zero == true`, worden rotaties **overgeslagen**:
```cpp
CVector3 CRotationMatrix::RotateVector(const CVector3 &vector) const {
    if (!zero) { return matrix * vector; }
    else { return vector; }  // Identiteit, geen berekening nodig
}
```

Dit bespaart significante CPU-cycli wanneer een object niet geroteerd is.

#### Rotatie-Ordes

De klasse biedt **5 verschillende Euler-rotatie ordes**:

| Methode | Orde | Conventie |
|---------|------|-----------|
| `SetRotation(alpha, beta, gamma)` | Z -> X -> Y | Extrinsieke rotaties |
| `SetRotation2(rotation)` | Z -> Y -> X | |
| `SetRotation3(rotation)` | Z -> Y -> X (met xyz mapping) | |
| `SetRotation4(rotation)` | X -> Y -> Z | |
| `SetRotation(direction, up)` | Look-at matrix | Basis orthonormale basis |

**De look-at matrix**:
```cpp
void CRotationMatrix::SetRotation(const CVector3 &direction, const CVector3 &up) {
    CVector3 xaxis = up.Cross(direction); xaxis.Normalize();
    CVector3 yaxis = direction.Cross(xaxis); yaxis.Normalize();
    
    matrix.m11 = xaxis.x; matrix.m12 = xaxis.y; matrix.m13 = xaxis.z;
    matrix.m21 = yaxis.x; matrix.m22 = yaxis.y; matrix.m23 = yaxis.z;
    matrix.m31 = direction.x; matrix.m32 = direction.y; matrix.m33 = direction.z;
}
```

Dit bouwt een **rotatiematrix** (geen volledige 4x4 view-matrix) waar:
- Rij 1 = X-as (right vector)
- Rij 2 = Y-as (up vector)
- Rij 3 = Z-as (forward/direction vector)

#### Euler-Extractie

```cpp
double CRotationMatrix::GetAlfa() const { return atan2(matrix.m12, matrix.m22); }
double CRotationMatrix::GetBeta() const { return asin(-matrix.m32); }
double CRotationMatrix::GetGamma() const { return atan2(matrix.m31, matrix.m33); }
```

Dit extracteert **Z-X-Y** intrinsieke Euler-hoeken. De `asin` voor beta betekent dat er een **gimbal lock** optreedt bij $\beta = \pm 90°$.

### 5.3 CMatrix44 & CRotationMatrix44

Identiek ontwerp als de 3D varianten, maar dan voor 4D rotaties. De 4D rotatie-matrix ondersteunt rotaties in 6 vlakken:

| Methode | Rotatie vlak | Term |
|---------|-------------|------|
| `RotateXY(angle)` | X-Y | $R_{xy}$ |
| `RotateYZ(angle)` | Y-Z | $R_{yz}$ |
| `RotateXZ(angle)` | X-Z | $R_{xz}$ |
| `RotateXW(angle)` | X-W | $R_{xw}$ |
| `RotateYW(angle)` | Y-W | $R_{yw}$ |
| `RotateZW(angle)` | Z-W | $R_{zw}$ |

Deze worden gebruikt voor **4D Julia fractals** en andere 4D objecten.

---

## 6. Gevonden Bugs & Riskante Code

### BUG #1: RotateYZ overschrijft zichzelf (CRITICAL)

**Bestand**: `algebra.cpp`, regels 496-512

```cpp
void CRotationMatrix44::RotateYZ(double angle) {
    CMatrix44 rot;
    rot.m22 = c;    rot.m23 = s;
    rot.m11 = -s;   // <<< FOUT! m11 wordt hier -s gezet
    rot.m31 = c;
    rot.m11 = 1.0;  // <<< ... maar hier direct overschreven met 1.0!
    rot.m44 = 1.0;
    matrix = matrix * rot;
}
```

**Analyse**: De regel `rot.m11 = -s` wordt **onmiddellijk** overschreven door `rot.m11 = 1.0`. Dit betekent dat de YZ-rotatie in de 4D matrix **nooit correct** wordt uitgevoerd. De correcte implementatie zou moeten zijn:

```cpp
// Correcte versie:
rot.m22 = c;   rot.m23 = s;
rot.m32 = -s;  rot.m33 = c;  // <<< m32 en m33, niet m11!
rot.m11 = 1.0;
rot.m44 = 1.0;
```

**Impact**: Elke 4D fractal die `RotateYZ` gebruikt produceert **foute resultaten**. Dit is een **silent failure** — de code compileert en draait, maar de wiskunde is fout.

### BUG #2: Dode parameters in repeatModSpiral

**Bestand**: `algebra.hpp`, regels 185-202

```cpp
inline CVector3 repeatModSpiral(
    const CVector3 &vector, const CVector3 &step, 
    const CVector3 &angle, const CVector3 &radius) const {
    (void)angle;    // Nooit gebruikt
    (void)radius;   // Nooit gebruikt
    ...
}
```

De parameters `angle` en `radius` zijn **functioneel dood**. De UI/parameters zouden waarden doorgeven die geen effect hebben.

### BUG #3: Dode parameter in repeatModFibonacci

**Bestand**: `algebra.hpp`, regels 138-158

```cpp
inline CVector3 repeatModFibonacci(int count, double spread) const {
    (void)count;    // Nooit gebruikt
    ...
}
```

De `count` parameter bepaalt **niets**.

### BUG #4: GetDelta/GetEpsilon/GetZeta zijn kopieen van GetAlfa/GetBeta/GetGamma

**Bestand**: `algebra.cpp`, regels 683-711

```cpp
double CRotationMatrix44::GetDelta() const {
    return atan2(matrix.m12, matrix.m22); // fix
}
double CRotationMatrix44::GetEpsilon() const {
    return asin(-matrix.m32); // fix
}
double CRotationMatrix44::GetZeta() const {
    return atan2(matrix.m31, matrix.m33); // fix
}
```

De comments `// fix` suggereren dat de implementateur wist dat dit niet klopt, maar het nooit heeft gecorrigeerd. Voor een 4D matrix zouden deze functies de **4D Euler-hoeken** moeten teruggeven, wat een veel complexere berekening vereist.

### Riskante Code #1: Normalize() deelt door Length() zonder check

```cpp
inline double Normalize() {
    const double norm = 1.0 / Length();  // DELING DOOR NUL MOGELIJK!
    x = x * norm; y = y * norm; z = z * norm;
    return norm;
}
```

Als `Length() == 0`, produceert dit **+inf** of een floating-point exception. Er is **geen guard**.

### Riskante Code #2: Operator== gebruikt exacte vergelijking

```cpp
inline bool operator==(const CVector3 &vector) const {
    return x == vector.x && y == vector.y && z == vector.z;
}
```

Dit gebruikt **exacte** float-vergelijking (`==`), wat gevoelig is voor afrondingsfouten. Er is geen epsilon-based vergelijking.

---

## 7. Performance-Analyse

### 7.1 Cache-Efficiëntie

De CVector3 klasse heeft een **memory footprint van precies 24 bytes** (3 x 8-byte doubles). Dit past in **een halve cache-lijn** (64 bytes) op moderne CPU's. Twee CVector3 objecten passen in één cache-lijn.

```
CVector3:  [x:8][y:8][z:8] = 24 bytes
Cache line: [CVector3 A (24B)][CVector3 B (24B)][padding (16B)]
```

Het ontwerp heeft **geen virtual functions**, **geen padding-problemen** (dubbels zijn 8-byte aligned), en **alle operaties zijn inline** in de header.

### 7.2 SIMD-Kansen

Huidige implementatie is **niet SIMD-geoptimaliseerd**. Elke component wordt individueel behandeld:

```cpp
// Huidig (scalar):
result.x = x + vector.x;
result.y = y + vector.y;
result.z = z + vector.z;

// Mogelijke SIMD (AVX):
// _mm256_add_pd(ymm1, ymm2) -- maar 3 doubles passen niet mooi in 256-bit (4 doubles)
```

Met **AVX-512** (8 doubles) of door `CVector4` te gebruiken als intern formaat, zou SIMD-optimalisatie mogelijk zijn.

### 7.3 StructuredCVector3 — De SIMD-Hint

```cpp
class StructuredCVector3 {
public:
    double x[8];
    double y[8];
    double z[8];
};
```

Dit is een **Structure of Arrays (SoA)** indeling in plaats van Array of Structures (AoS). Dit is **expliciet ontworpen voor SIMD-verwerking**:

```
SoA: [x0,x1,x2,x3,x4,x5,x6,x7][y0,y1,y2,y3,y4,y5,y6,y7][z0,z1,z2,z3,z4,z5,z6,z7]
     ^^^^^^^^^^^^^^^ 8 contiguous doubles ^^^^^^^^^^^^^^
     → perfect voor _mm512_loadu_pd() (AVX-512)
```

Maar zoekend in de codebase lijkt deze struct **niet actief gebruikt** te worden in de renderer. Het is mogelijk **voorbereid voor toekomstige optimalisatie**.

---

## 8. Extensie-Patronen

### 8.1 Nieuwe Vector-Type Toevoegen

Als je een `CVector3i` (integer variant) zou willen:

```cpp
class CVector3i {
public:
    int x, y, z;
    // Kopieer het patroon van CVector3 maar vervang double door int
    // Let op: Geen Normalize(), geen Length() met sqrt
    // Wel: Manhattan distance, grid operaties
};
```

### 8.2 Nieuwe repeatMod Variant

Patroon voor toevoegen:
```cpp
inline CVector3 repeatModMyPattern(const CVector3 &vector, ...) const {
    if (vector.Length() == 0.0) return *this;  // ALWAYS guard
    CVector3 modded = repeatMod(vector);        // ALWAYS start vanaf basis
    // ... jouw transformatie ...
    return modded;
}
```

### 8.3 Rotatie-Matrix Uitbreiden

De `CRotationMatrix` klasse gebruikt **composition** (opeenvolgende matrix-vermenigvuldigingen). Om een nieuwe rotatie toe te voegen:

```cpp
void RotateAroundArbitraryAxis(const CVector3 &axis, double angle) {
    // 1. Bouw de rotatiematrix voor deze as (Rodrigues formule als matrix)
    // 2. matrix = matrix * rot;
    zero = false;
}
```

---

## 9. Snelle Referentie-Tabel

| Class | Dim | Grootte | Key Members |
|-------|-----|---------|-------------|
| `CVector2<T>` | 2D | 2x T | `x, y` |
| `CVector3` | 3D | 24B | `x, y, z` + 7 repeatMod varianten |
| `CVector4` | 4D | 32B | `x, y, z, w` |
| `StructuredCVector3` | 8x3D | 192B | `x[8], y[8], z[8]` (SoA) |
| `CMatrix33` | 3x3 | 72B | `m11..m33` |
| `CMatrix44` | 4x4 | 128B | `m11..m44` |
| `CRotationMatrix` | 3D rot | 80B | `CMatrix33 matrix + bool zero` |
| `CRotationMatrix44` | 4D rot | 136B | `CMatrix44 matrix + bool zero` |

---

*Dit document beschrijft de algebra-laag van de experimentele Mandelbulber2 branch. Let speciaal op de gedocumenteerde bugs in `RotateYZ` en de dode parameters in de `repeatMod` familie bij verdere ontwikkeling.*

# MANDELBULBER2 DISTANCE CALCULATION: Nucleaire Diepte-Audit

**Datum**: 2026-04-22  
**Bestanden**: `calculation_mode.h`, `calculate_distance.hpp/cpp`, `common_math.h`, `object_node_type.h`  
**Scope**: Distance Estimation (DE), boolean operators, object tree walker, surface finding, deltaDE vs analyticDE

---

## INHOUDSOPGAVE

1. [Architectuur-Overzicht](#1-architectuur-overzicht)
2. [Berekeningsmodi (calculation_mode.h)](#2-berekeningsmodi-calculation_modeh)
3. [Data Structuren](#3-data-structuren)
4. [CalculateDistance — De Hoofdfunctie](#4-calculatedistance--de-hoofdfunctie)
5. [CalculateDistanceSimple — DE Kern](#5-calculatedistancesimple--de-kern)
6. [Delta DE — Numerieke Differentiatie](#6-delta-de--numerieke-differentiatie)
7. [Boolean Operatoren](#7-boolean-operatoren)
8. [Object Tree Walker](#8-object-tree-walker)
9. [CalculateDistanceMinPlane — Surface Finding](#9-calculatedistanceminplane--surface-finding)
10. [Bugs & Riskante Code](#10-bugs--riskante-code)

---

## 1. Architectuur-Overzicht

```
[Renderer ray marcher]
        |
        v
CalculateDistance(params, fractals, point, detailSize)
        |
        +---> [Objects Tree enabled?]
        |           +-- YES → CalculateDistanceFromObjectsTree()
        |           +-- NO  → CalculateDistanceSimple() + boolean operators
        |
        +---> Limit box clipping
        +---> Primitives (sphere, box, etc.)
        +---> Displacement mapping
        +---> Perlin noise displacement
        +---> View distance clipping
        |
        v
[out: distance, colorIndex, iters, objectId, maxiter]
```

---

## 2. Berekeningsmodi (calculation_mode.h)

```cpp
namespace fractal {
enum enumCalculationMode {
    calcModeNormal = 0,       // Standaard DE berekening
    calcModeColouring = 1,    // Kleur index extractie
    calcModeFake_AO = 2,      // Fake ambient occlusion
    calcModeDeltaDE1 = 3,     // Delta DE stap 1 (centraal punt)
    calcModeDeltaDE2 = 4,     // Delta DE stap 2 (naburige punten)
    calcModeOrbitTrap = 5,    // Orbit trap voor kleuring
    calcModeCubeOrbitTrap = 6,// Kubieke orbit trap
    calcModeSphereOrbitTrap = 7 // Sferische orbit trap (textuur fractalisatie)
};
}
```

Deze modi worden als **template argument** doorgegeven aan `Compute<>` in `compute_fractal.cpp`:
```cpp
Compute<fractal::calcModeNormal>(fractals, sequence, fractIn, &fractOut);
```

Dit is een **zero-overhead abstraction** — de compiler genereert aparte instanties per modus.

---

## 3. Data Structuren

### sDistanceIn (input)
```cpp
struct sDistanceIn {
    CVector3 point;           // Wereldpositie
    double detailSize;        // Gewenste ray marching stapgrootte
    bool normalCalculationMode; // true = normaal vector berekening
};
```

### sDistanceOut (output)
```cpp
struct sDistanceOut {
    double distance;    // Gevonden afstand (niet-geclipped)
    double colorIndex;  // Kleur index voor texturering
    int iters;          // Iteraties voor dit punt
    int totalIters;     // Cumulatieve iteraties (voor stats)
    int objectId;       // ID van het dichtstbijzijnde object
    bool maxiter;       // Max iteraties bereikt?
};
```

---

## 4. CalculateDistance — De Hoofdfunctie

### 4.1 Limit Box Check (vroege exit)

```cpp
if (params.limitsEnabled) {
    const double distance_a = max(in.point.x - params.limitMax.x, -(in.point.x - params.limitMin.x));
    const double distance_b = max(in.point.y - params.limitMax.y, -(in.point.y - params.limitMin.y));
    const double distance_c = max(in.point.z - params.limitMax.z, -(in.point.z - params.limitMin.z));
    limitBoxDist = max(max(distance_a, distance_b), distance_c);

    if (limitBoxDist > in.detailSize) {
        // EARLY EXIT: punt is buiten de limit box
        out->distance = limitBoxDist;
        return limitBoxDist;
    }
}
```

**Wiskunde**: De signed distance tot een axis-aligned box is:
$$d_{box}(p) = \max(d_x, d_y, d_z)$$
$$d_x = \max(p_x - \max_x, -(p_x - \min_x))$$

Dit is de **Chebyshev distance** tot de box. Als $d_{box} > \text{detailSize}$, is het punt ver genoeg buiten de box dat we direct kunnen terugkeren.

### 4.2 Boolean Operators (legacy mode)

```cpp
if (params.booleanOperatorsEnabled) {
    // Transformeer punt naar lokale fractal ruimte
    point = in.point - params.formulaPosition[0];
    point = params.mRotFormulaRotation[0].RotateVector(point);
    point = point.repeatMod(params.formulaRepeat[0]);
    point *= params.formulaScale[0];

    distance = CalculateDistanceSimple(...) / params.formulaScale[0];
    distance = DisplacementMap(distance, pointFractalized, 0, data, reduceDisplacement);

    for (int i = 0; i < NUMBER_OF_FRACTALS - 1; i++) {
        // ... combineer met boolean operators
    }
}
```

**Transformatie pipeline** per fractal:
1. Translatie: `point -= formulaPosition`
2. Rotatie: `point = rotationMatrix.RotateVector(point)`
3. Domain repetition: `point = point.repeatMod(formulaRepeat)`
4. Schaling: `point *= formulaScale`
5. DE berekening
6. Inverse schaling: `distance /= formulaScale`

### 4.3 Primitives

```cpp
distance = params.primitives.TotalDistance(
    in.point, distance, in.detailSize, in.normalCalculationMode, &out->objectId, data, -1);
```

Primitive objecten (bollen, boxen, cylinders, etc.) worden **na** de fractal berekening gecombineerd via de standaard SDF operatoren.

### 4.4 Post-processing Clips

```cpp
// NaN check
if (CheckNAN(distance)) distance = 0.0;

// Near plane clipping
const double distFromCamera = (in.point - params.camera).Length();
const double distanceLimitMin = params.viewDistanceMin - distFromCamera;
if (distanceLimitMin > in.detailSize) {
    out->maxiter = false;
    out->objectId = 0;
    out->iters = 0;
}
distance = max(distance, distanceLimitMin);
```

---

## 5. CalculateDistanceSimple — DE Kern

### 5.1 Analytic DE Pad

```cpp
if (fractals.GetDEType(forcedFormulaIndex) == fractal::analyticDEType) {
    Compute<fractal::calcModeNormal>(fractals, sequence, fractIn, &fractOut);
    distance = fractOut.distance;
    // ... maxiter handling
}
```

**Analytic DE**: De fractal formule berekent de afstand analytisch (via de afgeleide `dr`). Dit is het snelste pad.

**Maxiter handling**:
```cpp
if (!params.common.iterThreshMode) out->maxiter = false;
if (in.normalCalculationMode) out->maxiter = false;
if (out->maxiter) distance = 0.0;
if (fractOut.iters < params.minN && distance < in.detailSize) distance = in.detailSize;
```

**Interior mode**:
```cpp
if (params.interiorMode && !in.normalCalculationMode) {
    if (distance < 0.5 * in.detailSize || fractOut.maxiter) {
        distance = in.detailSize;  // Binnen fractal = oppervlak
        out->maxiter = false;
    }
}
```

**Distance clamping**:
```cpp
if (distance < 0.0) distance = 0.0;
if (distance > 10.0) distance = 10.0;  // HARD CAP
```

De **harde cap van 10.0** is een veiligheidsmaatregel om de ray marcher niet oneindig ver te laten stappen. Maar dit is **arbitrair** en kan artifacten veroorzaken bij grote scenes.

---

## 6. Delta DE — Numerieke Differentiatie

### 6.1 Wanneer?

Delta DE wordt gebruikt wanneer de fractal **geen analytische DE** heeft:
```cpp
if (fractals.GetDEType(forcedFormulaIndex) != fractal::analyticDEType) {
    // Delta DE pad
}
```

### 6.2 Adaptieve Delta

```cpp
double deltaDE;
if (params.advancedQuality) {
    deltaDE = max(fractIn.point.Length() * 1e-14, params.deltaDERelativeDelta * in.detailSize);
} else {
    deltaDE = max(fractIn.point.Length() * 1e-14, 1e-5 * in.detailSize);
}
```

| Factor | Advanced Quality | Standaard |
|--------|-----------------|-----------|
| Relatief tot detailSize | `deltaDERelativeDelta` | `1e-5` |
| Absoluut minimum | `\|point\| * 1e-14` | `\|point\| * 1e-14` |

De **absoluut minimum** voorkomt dat `deltaDE` nul wordt bij de oorsprong.

### 6.3 4-Punts Sampling

```cpp
// Stap 1: Centraal punt
Compute<fractal::calcModeDeltaDE1>(fractals, sequence, fractIn, &fractOut);
const double r = fractOut.z.Length();

// Stap 2: +X offset
fractIn.point = in.point + CVector3(deltaDE, 0.0, 0.0);
Compute<fractal::calcModeDeltaDE1>(fractals, sequence, fractIn, &fractOut);
const double dr1 = fabs(fractOut.z.Length() - r) / deltaDE;

// Stap 3: +Y offset
fractIn.point = in.point + CVector3(0.0, deltaDE, 0.0);
Compute<fractal::calcModeDeltaDE1>(fractals, sequence, fractIn, &fractOut);
const double dr2 = fabs(fractOut.z.Length() - r) / deltaDE;

// Stap 4: +Z offset
fractIn.point = in.point + CVector3(0.0, 0.0, deltaDE);
Compute<fractal::calcModeDeltaDE1>(fractals, sequence, fractIn, &fractOut);
const double dr3 = fabs(fractOut.z.Length() - r) / deltaDE;

const double dr = sqrt(dr1*dr1 + dr2*dr2 + dr3*dr3);
```

### 6.4 DE Formules

```cpp
if (dr > 0) {
    if (linearDEFunction)       distance = 0.5 * r / dr;
    else if (logarithmicDEFunction) distance = 0.5 * r * log(r) / dr;
    else if (pseudoKleinianDEFunction) {
        const double rxy = sqrt(z.x*z.x + z.y*z.y);
        distance = max(rxy - 0.92784, fabs(rxy * z.z) / r) / dr;
    }
    else if (josKleinianDEFunction) {
        const double rxy = sqrt(z.x*z.x + z.z*z.z);
        distance = (fabs(rxy * z.y) / r) / dr;
        maxiter = false;
    }
    else if (customDEFunction)  distance = r;  // FIXME: dIFS in deltaDE?
    else if (maxAxisDEFunction) {
        double maxZ = dMax(fabs(z.x), fabs(z.y), fabs(z.z));
        double maxDr = dMax(fabs(dr1), fabs(dr2), fabs(dr3));
        distance = 0.5 * maxZ / maxDr;
    }
}
```

**Wiskundige basis**:
- **Lineair**: $DE = \frac{r}{2|dr|}$ — standaard Mandelbrot/Mandelbulb DE
- **Logaritmisch**: $DE = \frac{r \ln(r)}{2|dr|}$ — voor exponential mappings
- **Pseudo-Kleinian**: $DE = \frac{\max(r_{xy} - 0.92784, |r_{xy} \cdot z_z|/r)}{|dr|}$ — specifiek voor Kleinian groepen
- **Jos Kleinian**: $DE = \frac{|r_{xy} \cdot z_y|/r}{|dr|}$
- **Max axis**: $DE = \frac{\max(|z_x|, |z_y|, |z_z|)}{2\max(|dr_1|, |dr_2|, |dr_3|)}$ — voor box-achtige fractals

---

## 7. Boolean Operatoren

### 7.1 OR (Union)

```cpp
case params::booleanOperatorOR:
    if (distTemp < distance) {
        outTemp.objectId = 1 + i;
        *out = outTemp;
    }
    if (params.smoothDeCombineEnable[i + 1]) {
        distance = opSmoothUnion(distTemp, distance, params.smoothDeCombineDistance[i + 1]);
    } else {
        distance = min(distTemp, distance);
    }
```

**Smooth Union** (Inigo Quilez):
```cpp
inline double opSmoothUnion(double d1, double d2, double k) {
    double h = clamp(0.5 + 0.5 * (d2 - d1) / k, 0.0, 1.0);
    return dmix(d2, d1, h) - k * h * (1.0 - h);
}
```

Dit is de **polynomiale smooth minimum** van Quilez. De parameter $k$ bepaalt de overgangsbreedte.

### 7.2 AND (Intersection)

```cpp
case params::booleanOperatorAND:
    if (distTemp > distance) {
        outTemp.objectId = 1 + i;
        *out = outTemp;
    }
    distance = max(distTemp, distance);
```

### 7.3 SUB (Difference)

```cpp
case params::booleanOperatorSUB:
    const double limit = 1.5;
    if (distance < in.detailSize) {  // Binnen eerste vorm
        if (distTemp < in.detailSize * limit * 1.5) {
            outTemp.objectId = 1 + i;
            *out = outTemp;
        }
        if (distTemp < in.detailSize * limit) {  // Binnen tweede vorm
            if (in.normalCalculationMode) {
                distance = max(in.detailSize * limit - distTemp, distance);
            } else {
                distance = in.detailSize * limit;
            }
        } else {  // Buiten tweede vorm
            distance = max(in.detailSize * limit - distTemp, distance);
            if (distance < 0) distance = 0;
        }
    } else {
        // Buiten eerste vorm: NIETS GEBEURT ER
    }
```

**Opmerking**: De `else` tak (buiten eerste vorm) is **leeg**. Dit is correct want als je buiten de eerste vorm bent, heeft de subtractie geen effect — de eerste vorm definieert de buitenkant.

---

## 8. Object Tree Walker

### 8.1 Stack-gebaseerde Tree Traversal

```cpp
struct StackFrame {
    int nodeIdx;
    int level;
    int closestObjectId;
    double cumulativeDistance;
    enumNodeType nodeType;
};

StackFrame stack[10];  // MAX 10 NIVEAUS DIEP
```

**Algoritme**:
1. Itereer over alle nodes in de tree (lineaire array)
2. Bij een `booleanAdd` node: push naar stack
3. Bij een leaf node (fractal/primitive/hybrid): bereken afstand
4. Update cumulative distance van het huidige stack niveau
5. Bij level decrease: pop stack en combineer afstanden

### 8.2 Node Types

| Type | Waarde | Betekenis |
|------|--------|-----------|
| fractal | 1 | Enkele fractal formule |
| primitive | 2 | Primitief object (bol, box, etc.) |
| light | 3 | Lichtbron |
| effect | 4 | Visueel effect |
| material | 5 | Materiaal definitie |
| hybrid | 10 | Hybrid fractal sequence |
| booleanAdd | 11 | Boolean union groep |
| booleanMul | 12 | Boolean intersection groep |
| booleanSub | 13 | Boolean subtractie groep |

### 8.3 Hybrid Sequence Handling

```cpp
case enumNodeType::hybrid:
    distance = CalculateDistanceSimple(params, fractals, in, &nodeOut, -1, 
                                       data->hybridFractalSequences.GetSequence(seqIndex));
    numberOfFractalsToSkip = 
        data->hybridFractalSequences.GetSequence(seqIndex)->numberOfFractalsInTheSequence;
    break;
```

Hybrid sequences combineren meerdere fractal formulas in één iteratie. De volgende fractal nodes in de tree moeten worden **geskipped** omdat ze al in de hybrid sequence zijn verwerkt.

---

## 9. CalculateDistanceMinPlane — Surface Finding

### 9.1 Doel

Vindt het **dichtstbijzijnde punt op de fractal oppervlak** vanaf een vlak gedefinieerd door `planePoint` en `direction`. Wordt gebruikt voor:
- Voxel export
- Mesh export
- Surface detection

### 9.2 Algoritme

```cpp
double distStep = 0.0;
CVector3 point = planePoint;
const double detail = 0.5;
const int transVectorAngles = 5;

CVector3 rotationAxis = planePoint;
rotationAxis.Normalize();

while (distStep == 0 || distStep > 0.00001) {
    CVector3 pointNextBest(0, 0, 0);
    double newDistStepMin = 0;

    for (int i = 0; i <= transVectorAngles; i++) {
        const double angle = (double(i) / transVectorAngles) * 2.0 * M_PI;
        CVector3 transversalVect = orthDirection;
        transversalVect = transversalVect.RotateAroundVectorByAngle(rotationAxis, angle);
        transversalVect.Normalize();
        CVector3 pointNext = point + direction * distStep;
        if (i > 0) pointNext += transversalVect * distStep / 2.0;

        const double dist = CalculateDistance(...);
        const double newDistStep = dist * detail * 0.5;
        if (newDistStep < newDistStepMin || newDistStepMin == 0) {
            pointNextBest = pointNext;
            newDistStepMin = newDistStep;
        }
    }

    if (newDistStepMin > 1000) newDistStepMin = 1000;
    if (distStep != 0 && newDistStepMin > distStep) break;
    distStep = newDistStepMin;
    point = pointNextBest;
}

return CVector3(point - planePoint).Dot(direction);
```

### 9.3 Wiskundige Analyse

Dit is een **gradient descent met transversale zoekrichtingen**:
1. Begin bij `planePoint`
2. Probeer `transVectorAngles+1 = 6` richtingen in een cirkel om de huidige richting
3. Kies de richting met de kleinste `newDistStep = dist * detail * 0.5`
4. Stap naar het beste punt
5. Herhaal tot convergentie (`distStep < 0.00001`) of divergentie (`newDistStep > distStep`)

**Convergentie criterium**: `distStep < 0.00001` (vaste threshold).

**Divergentie guard**: Als `newDistStep > distStep` (we bewegen verder van het oppervlak), stop.

**Oneindigheid guard**: Als `point.Length() > 1000000`, geef op.

---

## 10. Bugs & Riskante Code

### ⚠️ RISICO #1 — `rotationAxis.Normalize()` zonder zero-check

```cpp
CVector3 rotationAxis = planePoint;
rotationAxis.Normalize();
```

Als `planePoint = (0, 0, 0)`, dan is `rotationAxis` de nulvector en `Normalize()` deelt door nul. Dit kan NaN produceren. Dit is hetzelfde patroon als gevonden in de algebra audit.

**Fix**:
```cpp
CVector3 rotationAxis = planePoint;
if (rotationAxis.Length() > 0.0) {
    rotationAxis.Normalize();
}
```

---

### ⚠️ RISICO #2 — Harde distance cap van 10.0

```cpp
if (distance > 10.0) distance = 10.0;
```

Dit wordt op **twee plaatsen** toegepast (regels 466 en 598). De cap is **arbitrair** en kan artifacten veroorzaken bij grote scenes of wijd open ruimtes. De renderer stapt nooit verder dan 10 eenheden per ray marching stap, wat de prestaties kan beïnvloeden bij lage detail levels.

---

### ⚠️ RISICO #3 — Hardcoded stack diepte van 10

```cpp
StackFrame stack[10];
```

Als een gebruiker een object tree maakt die dieper dan 10 niveaus is, is er **stack overflow**. Er is geen runtime check. Dit is een veiligheidsrisico.

**Fix**: Dynamische allocatie of assert bij tree constructie:
```cpp
const int maxStackDepth = data->nodesDataForRendering.maxDepth();
QVector<StackFrame> stack(maxStackDepth + 1);
```

---

### ⚠️ RISICO #4 — `gApplication->processEvents()` in CalculateDistanceMinPlane

```cpp
gApplication->processEvents();
```

Dit wordt aangeroepen in elke iteratie van de while-loop. Dit kan leiden tot:
- Re-entrantie problemen
- UI freeze als het algoritme lang duurt
- Hogere CPU-belasting

---

### ⚠️ RISICO #5 — Inconsistente maxiter handling

```cpp
// Analytic DE pad
if (!params.common.iterThreshMode) out->maxiter = false;
if (in.normalCalculationMode) out->maxiter = false;
if (out->maxiter) distance = 0.0;

// Delta DE pad
if (!params.common.iterThreshMode) out->maxiter = false;
if (in.normalCalculationMode) out->maxiter = false;
if (out->maxiter) distance = 0.0;
```

Deze logica wordt **dubbel gecodeerd** (regels 430-434 en 563-568). Bij wijzigingen moet dit op twee plekken worden aangepast.

---

### ⚠️ RISICO #6 — `CheckNAN` returnt `true` voor NaN (dubbele negatie)

```cpp
inline bool CheckNAN(double a) {
    return !gsl_finite(a);
}
```

De functienaam suggereert dat het `true` returnt als de waarde **een NaN is**, wat correct is. Maar `gsl_finite` returnt `false` voor NaN/inf, dus `!gsl_finite` is `true` voor NaN. Dit is correct maar verwarrend.

---

### ⚠️ RISICO #7 — `distanceLimitMin` reset inconsistent

```cpp
const double distanceLimitMin = params.viewDistanceMin - distFromCamera;
if (distanceLimitMin > in.detailSize) {
    out->maxiter = false;
    out->objectId = 0;
    out->iters = 0;
}
distance = max(distance, distanceLimitMin);
```

Als `distanceLimitMin > detailSize`, worden `maxiter`, `objectId`, en `iters` gereset. Maar `distance` wordt pas **daarna** geclipped. Er is een toestand waarin:
- `distance < distanceLimitMin`
- `out->maxiter = false` (gereset)
- Maar `out->distance` wordt later pas geüpdatet

Dit kan leiden tot inconsistente output tijdens normaalberekening.

---

### ⚠️ RISICO #8 — `numberOfFractalsToSkip` geen bounds check

```cpp
numberOfFractalsToSkip = 
    data->hybridFractalSequences.GetSequence(seqIndex)->numberOfFractalsInTheSequence;
```

Er is geen check dat `numberOfFractalsToSkip` niet groter is dan het aantal resterende fractal nodes. Als een hybrid sequence meer fractals bevat dan er in de tree zijn, worden er nodes "overslaan" die eigenlijk andere objecten zijn.

---

### ⚠️ RISICO #9 — Delta DE forceert `maxiter = false` bij JosKleinian

```cpp
else if (fractals.GetDEFunctionType(forcedFormulaIndex) == fractal::josKleinianDEFunction) {
    // ...
    distance = (fabs(rxy * z.y) / r) / (dr);
    maxiter = false;  // ALTIJD false!
}
```

Bij JosKleinian wordt `maxiter` expliciet op `false` gezet. Dit betekent dat de iteratie threshold mode nooit werkt voor deze fractal type.

---

### ⚠️ RISICO #10 — `customDEFunction` TODO

```cpp
else if (fractals.GetDEFunctionType(forcedFormulaIndex) == fractal::customDEFunction) {
    distance = r; // FIXME: Can we calculate dIFS in deltaDE mode ???
}
```

Dit is een **bewuste placeholder**. dIFS (discrete Iterated Function Systems) heeft geen correcte Delta DE implementatie. De fallback is `distance = r`, wat een grove overschatting is.

---

*De distance calculation is het hart van de Mandelbulber2 renderer. Elke pixel, elke normaal, elke lichtstraal hangt af van deze functies. De dualiteit tussen analytic DE (snel, accuraat) en Delta DE (langzaam, generiek) is een elegant ontwerp dat vrijwel alle fractal types ondersteunt.*

# Mandelbulber2 Fake Lights / Orbit Trap Analyse

## Datum: 10 April 2026
## Analyse tijd: 30+ minuten

---

## 1. ARCHITECTUUR OVERZICHT

### CPU Side (C++)
- **src/compute_fractal.cpp**: Core fractal berekening
- **src/shader_fake_lights.cpp**: Fake lights shader (CPU)
- **src/orbit_trap_shape.cpp**: 106 SDF shapes
- **src/common_params.hpp**: sCommonParams struct + enums

### OpenCL Side
- **opencl/engines/compute_fractal.cl**: OpenCL kernel fractal berekening
- **opencl/engines/shader_fake_lights.cl**: Fake lights shader (OpenCL)
- **opencl/common_params_cl.hpp**: sCommonParamsCl struct (AUTO-GENERATED!)
- **opencl/opencl_algebra.h**: Hulpfuncties

### UI
- **qt/dock_effects.ui**: Qt UI definitie

---

## 2. BELANGRIJKE STRUCTUREN

### CPU: src/common_params.hpp
```cpp
struct sCommonParams {
    bool fakeLightsRelativeCenter;
    bool fakeLightsColor2Enabled;
    bool fakeLightsColor3Enabled;
    bool fakeLightsUseColorTemperature;
    
    int fakeLightsMaxIter;
    int fakeLightsMinIter;
    
    params::enumFakeLightsShape fakeLightsOrbitTrapShape;  // 106 shapes (0-105)
    params::enumFakeLightsFalloff fakeLightsFalloffType;   // 6 falloff modes (0-5)
    params::enumFakeLightsFalloff fakeLightsGlowFalloffType;
    
    double fakeLightsOrbitTrapSize;
    double fakeLightsFalloffExponent;
    double fakeLightsGlowFalloffExponent;
    double fakeLightsThickness;
    double fakeLightsColorTemperature;
    
    CVector3 fakeLightsOrbitTrap;
    CVector3 fakeLightsRotation;
    
    CRotationMatrix mRotFakeLightsRotation;
};
```

### OpenCL: opencl/common_params_cl.hpp
**WAARSCHUWING: AUTO-GENERATED DOOR tools/populateOpenCL.php**

```cpp
typedef struct {
    cl_int fakeLightsRelativeCenter;
    cl_int fakeLightsColor2Enabled;
    // ... etc
} sCommonParamsCl;
```

Deze file wordt automatisch gegenereerd vanuit src/common_params.hpp via het PHP script.

---

## 3. COMPUTE FRACTAL LOGICA (CRITISCH)

### CPU: src/compute_fractal.cpp (regels 392-405)
```cpp
else if (Mode == calcModeOrbitTrap)
{
    double distance = (in.common->fakeLightsRelativeCenter)
        ? OrbitTrapShapeDistance(z - aux.const_c, in.common)
        : OrbitTrapShapeDistance(z, in.common);

    if (i >= fakeLightsMinIter && i <= fakeLightsMaxIter)
        orbitTrapTotal += (1.0 / (distance * distance));
    if (distance > fractals.GetBailout(sequence))
    {
        out->orbitTrapR = orbitTrapTotal;
        break;
    }
}
```

### OpenCL: opencl/engines/compute_fractal.cl (regels 436-450)
```c
#ifdef FAKE_LIGHTS
else if (mode == calcModeOrbitTrap)
{
    float distance = (consts->params.common.fakeLightsRelativeCenter)
        ? OrbitTrapShapeDistance(z - aux.const_c, consts)
        : OrbitTrapShapeDistance(z, consts);

    if (i >= fakeLightsMinIter && i <= fakeLightsMaxIter)
        orbitTrapTotal += (1.0f / (distance * distance));
    if (distance > consts->sequence.bailout[sequence])
    {
        out.orbitTrapR = orbitTrapTotal;
        break;
    }
}
#endif
```

---

## 4. SHADER FAKE LIGHTS LOGICA

### CPU: src/shader_fake_lights.cpp (regels 103-229)
Berekeningsflow:
1. Loop over fakeLightMaxLoop (1-3 based on enabled colors)
2. Compute orbit trap via `Compute<calcModeOrbitTrap>`
3. Apply falloff based on `fakeLightsFalloffType`:
   - 0: None = 1.0
   - 1: Linear = 1/(1+r)
   - 2: Quadratic = 1/(1+r²)
   - 3: Cubic = 1/(1+r³)
   - 4: Gaussian = exp(-r²/2)
   - 5: Custom = 1/(1+r^exponent)
4. Sample 3-point gradient for normal
5. Dot product for diffuse shading
6. Apply color (temperature or RGB)

### OpenCL: opencl/engines/shader_fake_lights.cl (regels 100-204)
Identieke logica met float types.

---

## 5. CLIP MODE IMPLEMENTATIE PLAN

### Concept
Clip mode bepaalt of orbit trap accumulatie alleen gebeurt:
- **None (0)**: Altijd accumuleren (huidig gedrag)
- **Inside (1)**: Alleen accumuleren als aux.r <= bailout (binnen fractal)
- **Outside (2)**: Alleen accumuleren als aux.r > bailout (buiten fractal)

### Waar moet dit geïmplementeerd worden?

1. **src/common_params.hpp**: Nieuwe enum + veld toevoegen
2. **tools/populateOpenCL.php**: Updaten om nieuwe velden te kopiëren (of handmatig sync)
3. **opencl/common_params_cl.hpp**: Nieuwe enum + veld (handmatig of via PHP)
4. **src/compute_fractal.cpp**: Clip mode check in calcModeOrbitTrap sectie
5. **opencl/engines/compute_fractal.cl**: Idem voor OpenCL

### Huidige accumulatie logica (CPU):
```cpp
if (i >= fakeLightsMinIter && i <= fakeLightsMaxIter)
    orbitTrapTotal += (1.0 / (distance * distance));
```

### Nieuwe logica met Clip Mode:
```cpp
bool shouldAccumulate = false;
if (i >= fakeLightsMinIter && i <= fakeLightsMaxIter) {
    switch (in.common->fakeLightsClipMode) {
        case params::fakeLightsClipNone:
            shouldAccumulate = true;
            break;
        case params::fakeLightsClipInside:
            shouldAccumulate = (aux.r <= fractals.GetBailout(sequence));
            break;
        case params::fakeLightsClipOutside:
            shouldAccumulate = (aux.r > fractals.GetBailout(sequence));
            break;
    }
}
if (shouldAccumulate)
    orbitTrapTotal += (1.0 / (distance * distance));
```

---

## 6. UI IMPLEMENTATIE

### dock_effects.ui analyse
Grid layout met rows 0-16 bezet. Row 17+ beschikbaar.

Nieuwe ComboBox nodig:
- Naam: comboBox_fakeLightsClipMode
- Items: "None", "Inside", "Outside"
- Row: 17 (vrij)

---

## 7. BUILD SYSTEM

### populateOpenCL.php
Belangrijk! Dit script genereert de OpenCL structs vanuit CPU structs.

Locatie: tools/populateOpenCL.php

Na wijzigingen in src/common_params.hpp:
1. PHP script runnen: `php tools/populateOpenCL.php`
2. Of handmatig sync naar opencl/common_params_cl.hpp

---

## 8. OPENCL CACHE

Na elke struct wijziging:
```bash
rm -rf ~/.mandelbulber/openclCache/*
```

---

## 9. VOLGORDE VAN IMPLEMENTATIE

1. ✅ **ANALYSE** (30+ minuten - GEDAAN)
2. **STRUCT TOEVOEGINGEN**: common_params.hpp + common_params_cl.hpp
3. **COMPUTE_FRACTAL.CPP**: Clip mode logica
4. **COMPUTE_FRACTAL.CL**: Clip mode logica
5. **UI**: dock_effects.ui update
6. **BUILD**: Compileer en test
7. **CACHE CLEAR**: Verwijder OpenCL cache

---

## 10. BELANGRIJKE ONTDEKKINGEN

### orbit_trap_shape.cpp (regel 1574)
```cpp
return dist / par->fakeLightsThickness;
```

De distance wordt genormaliseerd door thickness. Dit is belangrijk voor de clip mode logica omdat de afstand hier al geschaald is.

### bailout vs aux.r
- `aux.r`: lengte van z vector (afstand van oorsprong)
- `bailout`: drempel waarde (typisch 4.0 of 1024.0)
- Als `aux.r > bailout`: punt is "escaped" uit fractal

### Clip Mode Logica
- **Inside**: `aux.r <= bailout` (punt is binnen fractal)
- **Outside**: `aux.r > bailout` (punt is buiten fractal)

Dit is consistent met de escape condition in calcModeNormal.

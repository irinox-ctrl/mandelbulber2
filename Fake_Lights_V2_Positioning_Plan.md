# Fake Lights V2 - Verbeterde Positionering & Implementatie Plan

## Deel 1: Huidige Situatie Analyse

### 1.1 Huidige Positionering Systeem (V1)

#### Huidige Parameters:
```cpp
// In common_params.hpp (sCommonParams)
CVector3 fakeLightsOrbitTrap;        // Statische 3D positie (default: 2.0, 0.0, 0.0)
bool fakeLightsRelativeCenter;       // false = world space, true = relatief aan Julia const_c
CVector3 fakeLightsRotation;         // Rotatie van de vorm (NIET de positie!)
double fakeLightsOrbitTrapSize;      // Grootte van de vorm
double fakeLightsThickness;          // Dikte/falloff

// In fractparams.hpp (sParamRender)
CVector3 camera;                     // Camera positie (BESTAAT AL)
CVector3 target;                     // Camera target (BESTAAT AL)
```

#### Huidige Berekening (compute_fractal.cpp):
```cpp
// Keuze tussen world space of Julia-relative
if (in.common->fakeLightsRelativeCenter) {
    distance = OrbitTrapShapeDistance(z - aux.const_c, in.common);
} else {
    distance = OrbitTrapShapeDistance(z, in.common);
}

// In OrbitTrapShapeDistance:
CVector3 delta = z - par->fakeLightsOrbitTrap;  // Statische offset!
```

### 1.2 Problemen met Huidige Systeem

| Probleem | Impact | Oorzaak |
|----------|--------|---------|
| **Statische Positie** | Lights blijven achter bij camera beweging | `fakeLightsOrbitTrap` is fixed in world space |
| **Geen Camera Tracking** | Lights volgen niet waar je naar kijkt | Geen relatie met `camera` of `target` parameters |
| **Handmatige Positionering** | Gebruiker moet trial-and-error doen | Complexe 3D fractal structuren zijn moeilijk te visualiseren |
| **Geen Surface Following** | Lights snijden door fractal heen | Geen intersectie met oppervlak |
| **Beperkte Rotatie** | Alleen vorm roteert, niet positie | `fakeLightsRotation` is alleen voor shape orientatie |
| **Julia Relative Is Beperkt** | Alleen relatief aan Julia constant, niet camera | Alleen `const_c` als referentie, niet flexibel |

### 1.3 Wat Werkt Wel in V1

- Orbit trap accumulatie: `orbitTrapTotal += 1/(distance²)` ✅
- Multi-color support via iteration ranges ✅
- 6 verschillende vormen (Point, Line, Circle, Square, Sphere, Cube) ✅
- Rotatie van vormen werkt correct ✅
- Volumetrische gloed (visibility) ✅

---

## Deel 2: V2 Positionering Ontwerp

### 2.1 Nieuwe Positionering Modes

```cpp
enum enumFakeLightsPositionMode {
    fakeLightsPositionWorld = 0,           // Huidig: Statische world space positie
    fakeLightsPositionCamera = 1,          // NIEUW: Relatief aan camera
    fakeLightsPositionTarget = 2,          // NIEUW: Op camera target punt
    fakeLightsPositionFractalCenter = 3,   // Huidig "relative_center": Relatief aan fractal centrum
    fakeLightsPositionSurfaceFollow = 4,   // NIEUW: Projecteer op dichtstbijzijnde oppervlak
    fakeLightsPositionPath = 5             // NIEUW: Langs een pad (voor animaties)
};
```

### 2.2 Gedetailleerde Mode Beschrijvingen

#### Mode 0: World Space (Huidig)
- **Beschrijving**: Statische positie in wereld coördinaten
- **Gebruik**: Wanneer je lights op een vaste plek wilt
- **Implementatie**: `trapPos = fakeLightsOrbitTrap`

#### Mode 1: Camera Relative (NIEUW)
- **Beschrijving**: Trap positie is relatief aan camera positie
- **Gebruik**: Lights blijven meebewegen met camera
- **Implementatie**: `trapPos = camera + fakeLightsOrbitTrap`
- **Opties**: 
  - Fixed offset (huidige `fakeLightsOrbitTrap`)
  - Distance scaling (wordt kleiner/groter met camera afstand)

#### Mode 2: Target Point (NIEUW)
- **Beschrijving**: Trap is gecentreerd op camera target
- **Gebruik**: Lights focussen op het onderwerp dat je filmt
- **Implementatie**: `trapPos = target + fakeLightsOrbitTrap`
- **Voordeel**: Altijd gericht op het interessante deel van de fractal

#### Mode 3: Fractal Center (Huidig "relative_center")
- **Beschrijving**: Relatief aan fractal centrum (Julia const_c)
- **Gebruik**: Voor Julia fractals, volgt de structuur
- **Implementatie**: `trapPos = fractalPosition + fakeLightsOrbitTrap` (of `const_c`)

#### Mode 4: Surface Following (NIEUW - ADVANCED)
- **Beschrijving**: Projecteer de orbit trap op het dichtstbijzijnde fractal oppervlak
- **Gebruik**: Lights volgen de contouren van de fractal
- **Implementatie**: 
  1. Bereken base positie (via andere mode)
  2. Ray-march vanaf base positie in richting van camera
  3. Plaats trap op intersectie punt
- **Kosten**: Extra ray-marching per frame (precompute mogelijk)

#### Mode 5: Path Based (NIEUW - ANIMATIE)
- **Beschrijving**: Meerdere trap posities langs een pad
- **Gebruik**: Voor animaties, lights bewegen door de scene
- **Implementatie**: 
  - Array van posities
  - Tijds/Frame gebaseerde interpolatie
  - Of afstand-gebaseerd voor constante snelheid

### 2.3 Extra Positionering Opties

#### Offset Type
```cpp
enum enumFakeLightsOffsetType {
    fakeLightsOffsetCartesian = 0,     // XYZ offset (huidig)
    fakeLightsOffsetSpherical = 1,     // Distance, Azimuth, Elevation
    fakeLightsOffsetView = 2           // Forward, Right, Up (view space)
};
```

#### Tracking Smoothness
- **Instant**: Directe positie update
- **Smooth**: Gefilterde beweging (lag) voor vloeiendere resultaten
- **Spring**: Veer-physics gebaseerde volg systeem

---

## Deel 3: Data Structuren

### 3.1 Aangepaste sCommonParams (src/common_params.hpp)

```cpp
// NIEUW: Positionering modes
enum enumFakeLightsPositionMode {
    fakeLightsPositionWorld = 0,
    fakeLightsPositionCamera = 1,
    fakeLightsPositionTarget = 2,
    fakeLightsPositionFractalCenter = 3,
    fakeLightsPositionSurfaceFollow = 4,
    // fakeLightsPositionPath = 5  // Future expansion
};

enum enumFakeLightsOffsetType {
    fakeLightsOffsetCartesian = 0,
    fakeLightsOffsetSpherical = 1,
    fakeLightsOffsetView = 2
};

struct sCommonParams {
    // ... bestaande velden ...
    
    // NIEUW: Positionering
    params::enumFakeLightsPositionMode fakeLightsPositionMode;
    params::enumFakeLightsOffsetType fakeLightsOffsetType;
    
    // AANGEPAST: Wordt gebruikt als offset volgens gekozen mode/type
    CVector3 fakeLightsOrbitTrap;  // Was absolute positie, nu offset
    
    // NIEUW: Camera tracking opties
    bool fakeLightsTrackCamera;        // Auto-update bij camera beweging
    double fakeLightsTrackingSmoothness; // 0.0 = instant, 1.0 = zeer smooth
    
    // NIEUW: Voor surface following mode
    double fakeLightsSurfaceOffset;    // Afstand van oppervlak
    
    // ... rest van bestaande velden ...
};
```

### 3.2 Runtime Berekende Positie

```cpp
// In shader_fake_lights.cpp - CalculateOrbitTrapPosition()

CVector3 CalculateOrbitTrapPosition(
    const CVector3& basePosition,      // Huidige trap positie (voor smoothness)
    const CVector3& camera,            // Camera positie
    const CVector3& target,            // Camera target
    const sCommonParams* common,       // Parameters
    const sFractalOut* fractOut        // Voor surface following
) {
    CVector3 newPosition;
    
    switch (common->fakeLightsPositionMode) {
        case fakeLightsPositionWorld:
            newPosition = common->fakeLightsOrbitTrap;
            break;
            
        case fakeLightsPositionCamera:
            newPosition = camera + common->fakeLightsOrbitTrap;
            break;
            
        case fakeLightsPositionTarget:
            newPosition = target + common->fakeLightsOrbitTrap;
            break;
            
        case fakeLightsPositionFractalCenter:
            // Gebruik fractOut->z of const_c als referentie
            newPosition = fractOut->z + common->fakeLightsOrbitTrap;
            break;
            
        case fakeLightsPositionSurfaceFollow:
            // Advanced: projecteer op oppervlak
            newPosition = ProjectToSurface(
                basePosition, camera, common);
            break;
    }
    
    // Apply smoothing if enabled
    if (common->fakeLightsTrackCamera && common->fakeLightsTrackingSmoothness > 0.0) {
        double t = 1.0 - common->fakeLightsTrackingSmoothness;
        newPosition = basePosition * (1.0 - t) + newPosition * t;
    }
    
    return newPosition;
}
```

---

## Deel 4: Stap-voor-Stap Implementatie Plan

### Fase 1: Data Structuren (Week 1)

#### Stap 1.1: Wijzig src/common_params.hpp
- [ ] Voeg nieuwe enums toe: `enumFakeLightsPositionMode`, `enumFakeLightsOffsetType`
- [ ] Wijzig `fakeLightsRelativeCenter` bool naar `fakeLightsPositionMode` enum
- [ ] Voeg nieuwe velden toe aan `sCommonParams`
- [ ] Update constructor/defaults indien nodig

#### Stap 1.2: Wijzig src/fractparams.hpp
- [ ] Voeg eventuele high-level parameters toe aan `sParamRender`
- [ ] Zorg dat `camera` en `target` goed doorgestuurd worden

#### Stap 1.3: Run Auto-Generatie
```bash
cd /home/joeri/mandelbulber2_v2_experiment/mandelbulber2
php tools/populateOpenCL.php nondry
```
- [ ] Controleer gegenereerde `opencl/common_params_cl.hpp`
- [ ] Controleer conversie functies

#### Stap 1.4: Update src/initparameters.cpp
- [ ] Registreer nieuwe parameters:
  - `fake_lights_position_mode` (0-4)
  - `fake_lights_offset_type` (0-2)
  - `fake_lights_tracking_smoothness` (0.0-1.0)
  - `fake_lights_surface_offset` (0.0-10.0)
- [ ] Update oude `fake_lights_relative_center` naar nieuw systeem

#### Stap 1.5: Update src/fractparams.cpp
- [ ] Laad nieuwe parameters naar structs
- [ ] Zorg voor backwards compatibility met oude settings

### Fase 2: CPU Implementatie (Week 2)

#### Stap 2.1: Update src/compute_fractal.hpp
- [ ] Voeg `camera` en `target` toe aan `sFractalIn` struct
- [ ] Of: maak nieuwe helper functie voor positie berekening

#### Stap 2.2: Update src/orbit_trap_shape.hpp/cpp
- [ ] Voeg `CalculateOrbitTrapPosition()` functie toe
- [ ] Wijzig `OrbitTrapShapeDistance()` om berekende positie te gebruiken
- [ ] Ondersteun alle nieuwe modes

#### Stap 2.3: Update src/shader_fake_lights.cpp
- [ ] Pas `FakeLights()` aan om nieuwe positionering te gebruiken
- [ ] Test met verschillende modes
- [ ] Zorg dat smoothing correct werkt

#### Stap 2.4: Update src/shader_volumetric.cpp
- [ ] Pas volumetrische fake lights aan voor nieuwe modes

### Fase 3: GPU/OpenCL Implementatie (Week 3)

#### Stap 3.1: Update opencl/engines/compute_fractal.cl
- [ ] Pas aan voor nieuwe `sCommonParamsCl` struct
- [ ] Zorg dat camera/target doorgestuurd worden naar kernel

#### Stap 3.2: Update opencl/engines/orbit_trap_shape.cl
- [ ] Implementeer `CalculateOrbitTrapPosition()` in OpenCL
- [ ] Test compile-time defines nog werken

#### Stap 3.3: Update opencl/engines/shader_fake_lights.cl
- [ ] Pas `FakeLightsShader()` aan voor nieuwe modes
- [ ] Zorg voor identieke resultaten als CPU

#### Stap 3.4: Update opencl/engines/shader_volumetric.cl
- [ ] Pas volumetrische lights aan

#### Stap 3.5: Update src/opencl_engine_render_fractal.cpp
- [ ] Zorg dat camera/target meegestuurd worden naar GPU
- [ ] Update defines indien nodig

### Fase 4: UI Implementatie (Week 4)

#### Stap 4.1: Update qt/dock_effects.ui
- [ ] Voeg ComboBox toe voor `fake_lights_position_mode`
  - "World Space (Fixed)"
  - "Camera Relative"
  - "Target Point"
  - "Fractal Center"
  - "Surface Follow"
- [ ] Voeg ComboBox toe voor `fake_lights_offset_type`
  - "Cartesian (X, Y, Z)"
  - "Spherical (Dist, Azimuth, Elevation)"
  - "View Space (Fwd, Right, Up)"
- [ ] Voeg slider toe voor `fake_lights_tracking_smoothness`
- [ ] Voeg input toe voor `fake_lights_surface_offset`
- [ ] Hernoem `fakeLightsOrbitTrap` labels naar "Offset" indien van toepassing

#### Stap 4.2: Update UI Logica
- [ ] Schakel velden uit op basis van gekozen mode
- [ ] Update tooltips voor nieuwe functionaliteit

### Fase 5: Testen & Validatie (Week 5)

#### Stap 5.1: Unit Tests
- [ ] Test elke positionering mode
- [ ] Test smoothness filtering
- [ ] Test backwards compatibility

#### Stap 5.2: Performance Tests
- [ ] Benchmark CPU vs GPU
- [ ] Test impact van surface following

#### Stap 5.3: User Testing
- [ ] Test met verschillende fractal types
- [ ] Test met animaties

---

## Deel 5: Implementatie Details

### 5.1 Key Implementation Decisions

#### Camera/Target Doorgeven
Optie A: Toevoegen aan `sFractalIn`
- Voordelen: Direct toegang in compute_fractal
- Nadelen: Struct wijziging, meer data doorgeven

Optie B: Berekenen in `FakeLights()` voor call
- Voordelen: Minimale struct wijzigingen
- Nadelen: Moet elke frame opnieuw

**Aanbeveling**: Optie B voor nu, A voor volledige V2.

#### Surface Following Implementatie
```cpp
CVector3 ProjectToSurface(
    const CVector3& basePos,
    const CVector3& camera,
    const sCommonParams* common
) {
    // Richting van base naar camera
    CVector3 dir = (camera - basePos).Normalize();
    
    // Ray-march naar oppervlak
    double dist = 0.0;
    CVector3 p = basePos;
    for (int i = 0; i < 100; i++) {
        double d = CalculateDistance(p); // Fractal DE
        if (d < 0.001) break; // Hit surface
        dist += d;
        if (dist > 100.0) break; // Max range
        p = basePos + dir * dist;
    }
    
    // Offset van oppervlak af
    return p - dir * common->fakeLightsSurfaceOffset;
}
```

### 5.2 OpenCL Consideraties

- Camera/target moeten doorgestuurd worden via `sClInConstants`
- Surface following is expensive op GPU - overweeg simpele versie
- Compile-time defines voor shapes blijven ongewijzigd

### 5.3 Backwards Compatibility

```cpp
// In fractparams.cpp - conversie van oude settings
if (container->Exists("fake_lights_relative_center")) {
    bool oldRelative = container->Get<bool>("fake_lights_relative_center");
    if (oldRelative) {
        common.fakeLightsPositionMode = fakeLightsPositionFractalCenter;
    } else {
        common.fakeLightsPositionMode = fakeLightsPositionWorld;
    }
}
```

---

## Deel 6: Toekomstige Uitbreidingen

### 6.1 Multi-Trap Support
- Meerdere orbit traps tegelijk
- Elk met eigen positie mode

### 6.2 Animation Paths
- Spline-gebaseerde beweging
- Tijdsgebonden keyframes

### 6.3 Auto-Discovery
- Automatisch detecteren van interessante fractal features
- Plaats lights op optimale locaties

### 6.4 Physics-Based Placement
- Simuleer licht bronnen die op het oppervlak "liggen"
- Gravitatie gebaseerde plaatsing

---

## Samenvatting

Deze V2 implementatie transformeert Fake Lights van een statisch, moeilijk te positioneren effect naar een dynamisch, camera-volgend belichtingssysteem. De key verbeteringen zijn:

1. **Camera Relative Mode**: Lights blijven meebewegen met de camera
2. **Target Mode**: Lights focussen automatisch op het onderwerp
3. **Surface Following**: Lights volgen de contouren van de fractal
4. **Smooth Tracking**: Vloeiende beweging zonder schokken
5. **Flexible Offsets**: Cartesian, spherical, of view-space offsets

**Inschatting**: 4-5 weken voor volledige implementatie (inclusief testen)

**Prioriteit**: Camera Relative en Target modes eerst (2 weken), daarna Surface Following.

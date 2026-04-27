# Position Mode Analyse - Orbit Trap

## HET PROBLEEM

De huidige orbit trap positie (`fakeLightsOrbitTrap`) is een **absolute wereldcoördinaat**. 
Als de fractal wordt verplaatst of geroteerd, blijft de orbit trap op dezelfde absolute positie staan.

## HUIDIGE CODE FLOW

### 1. Fractal Transformatie (compute_fractal.cpp regels 54-56)
```cpp
CVector3 pointTransformed = in.point - in.common->fractalPosition;
pointTransformed = in.common->mRotFractalRotation.RotateVector(pointTransformed);
CVector4 z = CVector4(pointTransformed, 0.0);
```
Het fractal punt wordt getransformeerd naar het "fractale coördinatensysteem".

### 2. Orbit Trap Berekening (orbit_trap_shape.cpp regel 45)
```cpp
CVector3 delta = z - par->fakeLightsOrbitTrap;
```
De orbit trap positie wordt **NIET** getransformeerd!

### 3. fakeLightsRelativeCenter (compute_fractal.cpp regel 394-396)
```cpp
double distance = (in.common->fakeLightsRelativeCenter)
    ? OrbitTrapShapeDistance(z - aux.const_c, in.common)
    : OrbitTrapShapeDistance(z, in.common);
```
Dit bepaalt alleen of we `z - const_c` gebruiken vs `z`. Het heeft niets met de positie te maken.

## GEWENSTE POSITION MODES

### Mode 0: World Absolute (huidig)
```cpp
delta = z - fakeLightsOrbitTrap
```
De orbit trap staat op een vaste positie in de wereld.

### Mode 1: Fractal Relative
```cpp
// Transformeer fakeLightsOrbitTrap door de fractal transformatie
CVector3 transformedTrap = fakeLightsOrbitTrap - fractalPosition;
transformedTrap = mRotFractalRotation.RotateVector(transformedTrap);
delta = z - transformedTrap;
```
De orbit trap beweegt mee met de fractal transformatie.

### Mode 2: Julia Constant Relative
```cpp
// fakeLightsOrbitTrap is relatief aan const_c
delta = z - (aux.const_c.GetXYZ() + fakeLightsOrbitTrap);
```
De orbit trap volgt de Julia constante.

## IMPLEMENTATIE PLAN

### Stap 1: Enum toevoegen
```cpp
enum enumFakeLightsPositionMode
{
    fakeLightsPositionWorld = 0,      // Absolute world position (current)
    fakeLightsPositionFractal = 1,    // Relative to fractal transform
    fakeLightsPositionJulia = 2       // Relative to Julia constant (const_c)
};
```

### Stap 2: Veld toevoegen aan sCommonParams
```cpp
params::enumFakeLightsPositionMode fakeLightsPositionMode;
```

### Stap 3: Transformatie logica in compute_fractal.cpp
Voor de orbit trap call, transformeer de positie afhankelijk van de mode.

### Stap 4: UI toevoegen
ComboBox met: "World Absolute", "Fractal Relative", "Julia Constant"

## VOORBEELD VAN HET PROBLEEM

Stel:
- Fractal staat op positie (10, 0, 0)
- Orbit trap staat op (0, 0, 0) 
- Mode: World Absolute

Resultaat: De orbit trap is op wereld (0,0,0), de fractal is op (10,0,0).
De lichtbron staat 10 units VAN de fractal af, niet IN de fractal.

Met Fractal Relative mode:
- Orbit trap (0,0,0) wordt getransformeerd naar fractal positie (10,0,0)
- De lichtbron staat IN de fractal.

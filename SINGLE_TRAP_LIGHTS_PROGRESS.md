# Single Trap Lights — Fake Lights Parameters Integratie

## Status: UI & Core Klaar, Softness Shader Logica Nog Open

---

## ✅ VOLTOOID

### `relativeSize` — Volledig Functioneel
- **CPU shader** (`src/shader_single_trap_lights.cpp`): vermenigvuldigt raw SDF distance
- **OpenCL surface shader** (`opencl/engines/shader_single_trap_lights.cl`): idem
- **OpenCL volumetric shader** (`opencl/engines/shader_volumetric.cl`): idem
- **UI**: veld zichtbaar voor alle 20 lagen in `dock_effects.ui`
- **Parameter registratie**: `initparameters.cpp`
- **Struct loading**: `fractparams.cpp`

### `softness` — UI & Struct Klaar, Shader Logica Nog Niet
- **CPU struct** (`src/single_trap_lights.hpp`): `double softness;` toegevoegd
- **OpenCL struct** (`opencl/single_trap_lights_cl.hpp`): `cl_float softness;` toegevoegd
- **Parameter registratie**: `initparameters.cpp` — `addParam(prefix + "_softness", 0.1, ...)`
- **Struct loading**: `fractparams.cpp` — laad in `singleTrapLights.layers[i].softness`
- **UI**: veld "Zachtheid:" zichtbaar voor alle 20 lagen in `dock_effects.ui`
- **Shader logica**: veld wordt geladen maar heeft **nog geen effect** op rendering

### Struct Alignment Fix (GPU)
- `cl_float3` → `cl_float4` voor `position`, `rotation`, `color` in OpenCL struct
- Access via `.xyz` in shaders
- OpenCL header gesynct naar `share/mandelbulber2/opencl/`

### Position Bug Fix
- Hersteld: `adjustedPoint = input.point - effectivePosition + layer.position`
- Was: dubbele subtractie van `layer.position`

### `size2` Dynamische UI Visibility
- `slotChangedSingleTrapLightShape()` in `dock_effects.cpp`
- Verbergt `size2` voor Point/Line/Circle/Square/Sphere/Cube
- Toont `size2` voor Torus/Capsule/Ring/Ellipse/Cross

### Build Fix
- `fractal_transf_wizard_demo.h` had handgeschreven class definitie die conflicteerde met `FRACTAL_CLASS` macro
- Opgelost door class definitie te verwijderen (patroon van andere fractal headers gevolgd)

---

## 🔄 NOG TE DOEN (vanavond)

### 1. Softness Shader Logica Implementeren

**Doel:** Vloeiende edge-fade aan de grens van het licht, gebaseerd op `softness` waarde (0 = hard, >0 = zachtere overgang).

**Te wijzigen bestanden:**
- `src/shader_single_trap_lights.cpp` (CPU surface)
- `opencl/engines/shader_single_trap_lights.cl` (OpenCL surface)
- `opencl/engines/shader_volumetric.cl` (OpenCL volumetric)

**Conceptuele aanpak (te verfijnen):**
```cpp
// Huidige logica (werkt):
double rawDistance = SingleTrapLightDistance(adjustedPoint, layer);
double relativeSizeFactor = max(0.0, layer.relativeSize);
double distance = rawDistance * relativeSizeFactor;

// Softness toevoegen:
// softness = 0  → harde cutoff (huidig gedrag)
// softness > 0  → vloeiende fade vanaf distance = 0 naar distance = softness
double softnessMask = 1.0;
if (layer.softness > 0.0 && distance > 0.0) {
    softnessMask = 1.0 - smoothstep(0.0, layer.softness, distance);
}
// softnessMask vermenigvuldigen met intensity
```

**Belangrijk:** Softness moet waarschijnlijk worden toegepast *voor* of *na* de blur/sharpening falloff — dit moeten we testen.

### 2. Testen
- Kill oude processen: `pkill -9 mandelbulber2`
- Wis OpenCL cache: `rm -rf ~/.mandelbulber/openclCache/*`
- Sync header: `cp opencl/single_trap_lights_cl.hpp share/mandelbulber2/opencl/`
- Herbuild: `cd build && make -j$(nproc)`
- Test CPU vs GPU pixel match

---

## 📁 Bestanden Gewijzigd (voor referentie)

| Bestand | Wijziging |
|---------|-----------|
| `src/single_trap_lights.hpp` | `softness`, `relativeSize` velden |
| `opencl/single_trap_lights_cl.hpp` | `softness`, `relativeSize` velden + alignment fix |
| `src/initparameters.cpp` | Param registratie voor `_softness`, `_relative_size` (alle 20 lagen) |
| `src/fractparams.cpp` | Laad `softness`, `relativeSize` in runtime struct |
| `qt/dock_effects.ui` | UI widgets voor `softness` & `relative_size` (alle 20 lagen) |
| `qt/dock_effects.cpp` | `slotChangedSingleTrapLightShape()` + size2 visibility |
| `src/shader_single_trap_lights.cpp` | `relativeSize` multiplier in CPU shader |
| `opencl/engines/shader_single_trap_lights.cl` | `relativeSize` multiplier in OpenCL shader |
| `opencl/engines/shader_volumetric.cl` | `relativeSize` multiplier in volumetric shader |
| `formula/definition/fractal_transf_wizard_demo.h` | Build fix (class redefinition) |

---

## ⚠️ Belangrijke Workflow Herinneringen

1. **OpenCL header sync** altijd na struct wijziging:
   ```bash
   cp opencl/single_trap_lights_cl.hpp share/mandelbulber2/opencl/
   ```
2. **Cache invalidatie** altijd na GPU wijzigingen:
   ```bash
   rm -rf ~/.mandelbulber/openclCache/*
   pkill -9 mandelbulber2
   ```
3. **Debug kernel dump** beschikbaar op `/tmp/opencl_program_debug.cl`
4. **CPU vs GPU outlier pixels** (~max 152 diff) zijn inherent float-vs-double raymarching, geen bug in STL code

---

## 🎯 Vanavond: Softness Shader Implementatie

Focus: De `softness` parameter functioneel maken in alle drie de shaders (CPU surface, OpenCL surface, OpenCL volumetric).

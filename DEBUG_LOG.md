# Mandelbulber Experiment — Debug & Issue Tracking Log

> Dit document houdt alle gevonden problemen, fixes en lessen bij.
> Referentie voor het hele traject. Altijd up-to-date houden!

---

## Voortgang Overzicht

| Fase | Status | Opmerkingen |
|------|--------|-------------|
| Basis mutation systeem (pre/post/fold/warp/math) | ✅ Klaar | CPU + GPU |
| Per-sectie iteratie controls (7 secties) | ✅ Klaar | UI + CPU + GPU |
| Julia injection systeem (10 modes) | ✅ Klaar | CPU + GPU |
| Smart field greying per formule | ✅ Klaar | DE/Julia/Orbit grijs bij irrelevante formules |
| Reset button | ✅ Klaar | Reset alleen params, niet enabled checkbox |
| 50 Inversies | ✅ Code klaar | CPU + GPU, nog niet getest op RTX 5090 |
| 50 Clips | ✅ Code klaar | CPU + GPU, nog niet getest op RTX 5090 |
| GPU rendering fix (cache) | ✅ Fix gepusht | Wacht op user test |
| Visuele verificatie inversies/clips | ⏳ Wachtend | Na GPU fix bevestiging |
| 100 Jos Leys DE (V1-V100) | ✅ Klaar | CPU + GPU + UI + Iteratie |
| 100 Pseudokleinian DE (V1-V100) | ✅ Klaar | CPU + GPU + UI + Iteratie |
| 200 Mandelbox Math (V1-V200) | ✅ Klaar | CPU + GPU + UI + Iteratie |
| 100 Warp Distortion (V1-V100) | ✅ Klaar | CPU + GPU + UI + Iteratie |
| 100 Symmetry/Kaleidoscope (V1-V100) | ✅ Klaar | CPU + GPU + UI + Iteratie |
| 400 Abox DE (V1-V400) | ✅ Klaar | CPU + GPU + UI + Iteratie |

| 100 Noise & Procedural DE (V1-V100) | ✅ Klaar | CPU + GPU + UI + Iteratie |
| 100 Orbit Trap DE (V1-V100) | ✅ Klaar | CPU + GPU + UI + Iteratie |
| 100 MandelTorus DE (V1-V100) | ✅ Klaar | CPU + GPU + UI + Iteratie |

**Totaal transformaties: 1400** (50 inv + 50 clip + 100 JL + 100 PK + 200 MB + 100 WD + 100 SK + 400 AB + 100 Noise + 100 Orbit + 100 Torus)

---

## Issue Register

### ISSUE-001: `extendedAux.color` referenties op CPU side
- **Datum:** Sessie 1
- **Symptoom:** Compilatiefouten in `compute_fractal.cpp`
- **Locaties:** `compute_fractal.cpp` regels 379, 380, 2151-2153, 2167, 2169
- **Oorzaak:** CPU code gebruikt `aux` struct, niet `extendedAux`
- **Fix:** `sed -i 's/extendedAux\.color/aux.color/g' compute_fractal.cpp`
- **Status:** ✅ Opgelost
- **Les:** CPU en GPU hebben verschillende aux struct namen. Altijd verifiëren welke context (CPU vs GPU) je bewerkt.

---

### ISSUE-002: Widget namen collision (`_x/_y/_z`)
- **Datum:** Sessie 2
- **Symptoom:** Pre-rotation spinboxes werkten niet; waarden kwamen niet door
- **Oorzaak:** Mandelbulber's `InitWidgetNames()` detecteert `_x`, `_y`, `_z` als vector-componenten en voegt de formule-index op de verkeerde plek in. Voorbeeld: `spinbox_mutation_pre_rotation_x` → geïndexeerd als `_rotation_[1]_x` i.p.v. `_rotation_x_[1]`
- **Fix:** Alle 24 parameters hernoemd van `_x/_y/_z` naar `_ax/_ay/_az`
- **Getroffen parameters:**
  - `pre_rotation_{x,y,z}` → `pre_rotation_{ax,ay,az}`
  - `post_rotation_{x,y,z}` → `post_rotation_{ax,ay,az}`
  - `pre_offset_{x,y,z}` → `pre_offset_{ax,ay,az}`
  - `post_offset_{x,y,z}` → `post_offset_{ax,ay,az}`
  - `julia_c_rotation_{x,y,z}` → `julia_c_rotation_{ax,ay,az}`
  - `inv_center_{x,y,z}` → `inv_center_{ax,ay,az}`
  - `clip_center_{x,y,z}` → `clip_center_{ax,ay,az}`
  - `clip_size_{x,y,z}` → `clip_size_{ax,ay,az}`
- **Status:** ✅ Opgelost
- **Les:** **NOOIT** parameter namen laten eindigen op `_x`, `_y`, of `_z` in Mandelbulber. Gebruik altijd `_ax`, `_ay`, `_az` of een ander suffix.

---

### ISSUE-003: `.ui` wijzigingen niet zichtbaar na `make`
- **Datum:** Sessie 2-3
- **Symptoom:** Nieuwe UI secties (inversie/clip dropdowns, per-sectie iteratie spinboxes) verschenen niet in de applicatie na `make`
- **Oorzaak:** Qt's `uic` compiler genereert `ui_tab_fractal.h` uit het `.ui` bestand. Dit gebeurt alleen als `qmake` wordt gedraaid — `make` alleen hercompileert bestaande code maar regenereert niet de UI header.
- **Fix:** Altijd `qmake mandelbulber-opencl.pro` draaien vóór `make` wanneer `.ui` bestanden gewijzigd zijn
- **Status:** ✅ Opgelost
- **Les:** **Build commando moet altijd `qmake` bevatten bij UI wijzigingen:**
  ```bash
  cd mandelbulber2/qmake && qmake mandelbulber-opencl.pro && make -j$(nproc)
  ```

---

### ISSUE-004: Git merge conflict op Makefile
- **Datum:** Sessie 3
- **Symptoom:** `git pull` faalt met "Your local changes to Makefile would be overwritten by merge"
- **Oorzaak:** `qmake` genereert een lokale Makefile die verschilt van de repo versie
- **Fix:** `git stash` vóór `git pull`
- **Status:** ✅ Opgelost
- **Les:** De Makefile is gegenereerd en niet gecommit. Altijd `git stash` gebruiken als `git pull` faalt door lokale Makefile wijzigingen.

---

### ISSUE-005: Reset button sluit mutation groep
- **Datum:** Sessie 3
- **Symptoom:** Reset knop zette `mutation_enabled` op false → hele mutation groep sluit
- **Oorzaak:** Reset code resette ALLE parameters inclusief de enabled checkbox
- **Fix:** Reset slaat `mutation_enabled` over — reset alleen waarden, niet de aan/uit status
- **Status:** ✅ Opgelost
- **Les:** Reset functies moeten altijd de "master enable" checkbox bewaren.

---

### ISSUE-006: GPU geen beeld (struct cache probleem)
- **Datum:** Sessie 4 (huidig)
- **Symptoom:** GPU mode toont geen fractal beeld; CPU mode werkt correct
- **Oorzaak:** Mandelbulber's OpenCL kernel cache hash werd berekend op basis van `#include` directives in de program string — NIET de daadwerkelijke file-inhoud. Toen struct velden werden toegevoegd aan `fractal_sequence_cl.h`, veranderde de hash niet → stale cached kernel binary werd geladen → GPU las data op verkeerde byte offsets.
- **Root cause detail:**
  - `opencl_engine.cpp` `Build()` functie: hash = Md4(programString + deviceHash)
  - `programString` bevat `#include "/pad/naar/fractal_sequence_cl.h"` (directive, niet inhoud)
  - Header file wijzigingen veranderen de hash NIET
  - Cache bestand in `~/.mandelbulber/openclCache/` bevat oude compiled binary
  - NVIDIA driver cache in `~/.nv/ComputeCache/` bevat ook oude binary
- **Fix (permanent):** Hash berekening uitgebreid om alle `#include`'d header file inhoud mee te nemen. Nu invalideren header-wijzigingen automatisch de cache.
  - Bestand: `mandelbulber2/src/opencl_engine.cpp` regels 103-119
  - Commit: `a1a94ba9e`
- **Fix (eenmalig voor user):**
  ```bash
  rm -rf ~/.mandelbulber/openclCache/ ~/.nv/ComputeCache/
  ```
- **Status:** ✅ Fix gepusht, ⏳ wacht op user bevestiging
- **Les:** **OpenCL cache invalidatie moet ALLE bronbestanden meenemen**, niet alleen de top-level program string. Bij elke struct wijziging: verifieer dat de cache wordt geïnvalideerd.

---

### ISSUE-007: Windows MSVC build — DOFLogLevel enum clashes
- **Datum:** Sessie 5
- **Symptoom:** MSVC `error C2059: syntax error: 'constant'` op `dof_log.hpp` lijn 46; `error C2065: 'INFO': undeclared identifier` op `interface.cpp`
- **Oorzaak:** Windows API headers (`wingdi.h`) definiëren `#define ERROR 0`. Onze `DOFLogLevel` enum gebruikte `ERROR`, `WARN`, `INFO`, `DEBUG`, `TRACE` als enum waarden. Na preprocessor macro expansie werd `ERROR = 1` → `0 = 1` → syntax error.
- **Fix:** Enum waarden hernoemd naar `LvlError`, `LvlWarn`, `LvlInfo`, `LvlDebug`, `LvlTrace`. Toegevoegd `#undef ERROR` en `#undef DEBUG` guards.
- **Getroffen bestanden:** `dof_log.hpp`, `dof_log.cpp`
- **Status:** ✅ Opgelost
- **Les:** **NOOIT** Windows API reserved woorden gebruiken als enum/variabele namen: `ERROR`, `DEBUG`, `NEAR`, `FAR`, `IN`, `OUT`, `OPTIONAL`, `CONST`, `TRUE`, `FALSE`, etc.

---

### ISSUE-008: Windows MSVC build — raw string literal parsing
- **Datum:** Sessie 5
- **Symptoom:** MSVC `error C2001: newline in constant` op `opencl_engine.cpp` lijn 107
- **Oorzaak:** MSVC had moeite met de raw string literal `R"(#include\s+"([^"]+)")"` — de embedded aanhalingstekens en escape characters verwarren de parser in sommige MSVC versies.
- **Fix:** Vervangen door standaard escaped `QString("#include\\s+\"([^\"]+)\"")`.
- **Getroffen bestanden:** `opencl_engine.cpp`
- **Status:** ✅ Opgelost
- **Les:** **Vermijd raw string literals (`R"()"`) in cross-platform code** wanneer de inhoud aanhalingstekens bevat. Gebruik gewone escaped strings voor maximale compatibiliteit.

---

## Bekende Beperkingen & Aandachtspunten

### Struct Alignment Regels (GPU/CPU)
- Alle `cl_float` en `cl_int` velden: 4-byte aligned
- `cl_float3` op host = `cl_float4` = 16 bytes, 16-byte aligned
- `cl_float3` op GPU = `float3` = 16 bytes (padded to float4), 16-byte aligned
- `matrix33` = 3 × `cl_float3` = 48 bytes, 16-byte aligned
- **sClFormulaMutationParams** = 816 bytes per slot × 9 slots = 7,344 bytes
- **sClFractalSequence** = ~10,832 bytes (inclusief weight + mutation params)
- **sClInConstants** totaal = ~54 KB (binnen 64KB constant buffer limiet)

### Widget Naming Convention
```
GOED:  spinbox_mutation_inv_center_ax    (eindigt op _ax)
FOUT:  spinbox_mutation_inv_center_x     (eindigt op _x → collision)
```

### Build Commando (user machine)
```bash
cd /home/joeri/mandelbulber2_v2_experiment && git stash && git pull && cd mandelbulber2/qmake && qmake mandelbulber-opencl.pro && make -j$(nproc) && ./mandelbulber2
```

### Cache Locaties
| Platform | Mandelbulber Cache | NVIDIA Driver Cache |
|----------|-------------------|-------------------|
| Linux | `~/.mandelbulber/openclCache/` | `~/.nv/ComputeCache/` |
| Windows | `~/mandelbulber/openclCache/` | `%APPDATA%/NVIDIA/ComputeCache/` |

---

## Architectuur Notities

### Mutation Systeem Pipeline
```
UI Spinbox/Dropdown
  → Parameter (initparameters.cpp)
    → CPU struct (nine_fractals.hpp :: sFormulaMutationParams)
      → GPU copy (nine_fractals.cpp :: CopyToOpenclData)
        → GPU struct (fractal_sequence_cl.h :: sClFormulaMutationParams)
          → GPU kernel (compute_fractal.cl / nebula.cl)
```

### Per-Sectie Iteratie Controls
Elke mutation sectie heeft een eigen Start/Stop range:
| Sectie | Parameters | Default Range |
|--------|-----------|---------------|
| Pre-Transform | preIterStart, preIterStop | 0 - 10000 |
| Fold | foldIterStart, foldIterStop | 0 - 10000 |
| Warp | warpIterStart, warpIterStop | 0 - 10000 |
| Math | mathIterStart, mathIterStop | 0 - 10000 |
| Post-Transform | postIterStart, postIterStop | 0 - 10000 |
| Julia | juliaIterStart, juliaIterStop | 0 - 10000 |
| DE/Output | deIterStart, deIterStop | 0 - 10000 |
| Inversion | invIterStart, invIterStop | 0 - 10000 |
| Clip | clipIterStart, clipIterStop | 0 - 10000 |
| Jos Leys DE | josIterStart, josIterStop | 0 - 10000 |
| Pseudokleinian DE | pkIterStart, pkIterStop | 0 - 10000 |
| Mandelbox Math | mbIterStart, mbIterStop | 0 - 10000 |

Globale "Iter Range" (iterationStart/iterationStop) is de master gate — per-sectie ranges werken alleen BINNEN de globale range.

---

### ISSUE-009: `frac()` niet beschikbaar in C++
- **Datum:** Sessie 7
- **Symptoom:** Compilatiefout `frac was not declared in this scope`
- **Root Cause:** `frac()` is een GLSL/HLSL functie, niet beschikbaar in standaard C++
- **Fix:** Alle `frac(x)` vervangen door `(x - floor(x))` in CPU code
- **Les:** Altijd `floor()`-gebaseerde fractional part gebruiken in C++ code

---

### ISSUE-010: `extendedAux` niet beschikbaar in mutation scope
- **Datum:** Sessie 7
- **Symptoom:** Compilatiefout `extendedAux was not declared in this scope`
- **Root Cause:** `extendedAux` is lokaal in formule code, niet beschikbaar in mutation sectie
- **Fix:** `extendedAux.c_formula.Length()` vervangen door `in.point.Length()`
- **Les:** In mutation code alleen `z`, `aux`, `in`, en `mut` gebruiken

---

### ISSUE-011: CVector4/CVector3 type mismatch in Symmetry system
- **Datum:** Sessie 8
- **Symptoom:** `no match for operator-= (operand types CVector4 and CVector3)`
- **Root Cause:** `z` is CVector4, maar gegenereerde code gebruikte `z -= CVector3(a,b,c)` patronen (Sierpinski/IFS-achtige operaties)
- **Fix:** Alle `z -= CVector3(a,b,c)*expr` vervangen door component-wise `z.x -= a*expr; z.y -= b*expr; z.z -= c*expr;`
- **Les:** In Mandelbulber is `z` altijd CVector4 (4D). Gebruik nooit CVector3 assignment met z. Altijd component-wise bewerkingen.

---

### ISSUE-012: `afp` niet gedeclareerd in Abox V308 scope
- **Datum:** Sessie 9
- **Symptoom:** `afp was not declared in this scope; did you mean aff?`
- **Root Cause:** Generator script gebruikte `afp` als variabelenaam voor parameter F, maar in Abox scope heet die `aff` (niet `af` want dat is al factor)
- **Fix:** `afp` vervangen door `aff` in V308 (CPU + GPU)
- **Les:** In Abox scope: factor=`af`, params=`aa`-`ae`, `aff` (F), `ag`, `ah`. Nooit andere namen gebruiken.

---

### ISSUE-013: 284 GPU conversiefouten + runtime safety issues
- **Datum:** Sessie 10 (v7.12.1)
- **Symptoom:** Geen compilatiefouten, maar potentiële runtime crashes/NaN op GPU
- **Root Cause:** Generator scripts produceerden GPU code met:
  - 44× `double` keyword (moet `float` zijn in OpenCL)
  - 212× bare math functies (`exp`, `sqrt`, `sin`, `cos`, `log`) zonder `native_` prefix
  - 4× `exp()` met onbegrensde positieve argumenten (overflow → Inf)
  - 4× `log()` met potentieel nul/negatief argument (→ NaN)
- **Fix:** 
  - `mutation_scanner.py --fix` voor automatische GPU conversies
  - Handmatige exp() clamping: `exp(fmin(arg, 20.0))`
  - Handmatige log() bescherming: `log(fmax(arg, 1e-21))`
- **Detectie:** Nieuwe `mutation_scanner.py` tool (6-punt automatische audit)
- **Status:** ✅ Alle CRITICAL en HIGH issues opgelost
- **Resterend (MEDIUM):** 149× div-by-zero (veilig met defaults), 110× sqrt domain, 5× cosh, 2× DE unbounded
- **Les:** ALTIJD `mutation_scanner.py` draaien na elke nieuwe batch transformaties. Scanner detecteert fouten die de compiler niet vangt.

---

*Laatst bijgewerkt: 2026-05-22 — Sessie 10 (v7.12.1)*

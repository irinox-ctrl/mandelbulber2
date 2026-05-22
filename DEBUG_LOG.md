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
| Uitbreiding / verfijning | 🔲 Nog niet | ~80% resterend werk |

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

Globale "Iter Range" (iterationStart/iterationStop) is de master gate — per-sectie ranges werken alleen BINNEN de globale range.

---

*Laatst bijgewerkt: 2026-05-20 — Sessie 4*

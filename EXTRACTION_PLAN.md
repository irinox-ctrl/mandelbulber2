# EXTRACTION PLAN: Transform Systems uit Backups

**Datum:** 2026-04-19
**Doel:** Cloner, Deformers, Repeats, Pivot Point systemen installeren

---

## MAPPING RESULTATEN

### ✅ Reeds Aanwezig
- **Fake Lights V2** (pathSpiral, pathCircle positioning modes)
- Alle 16 primitive .ui files
- Core primitive implementation

###❌ ONTBREKEND (Te Extracten)
1. **Epic Repeat System** - Repeat modes (grid, brick, honeycomb, radial, spiral, etc.)
2. **Cloner System** - Clone count, offset, patterns
3. **Deformation System** - Bend, twist, taper transforms
4. **Pivot/World Space** - World coordinate system, rotation centers
5. **Emission System** - Primitive emission modes

---

## BESTE BACKUPS PER SYSTEEM

### 1. Epic Repeat System
**Beste backup:** `mb_20260307_194901_epic_repeat_klaar.tar.gz`
- **Datum:** 2026-03-07 19:49
- **Naam betekenis:** "epic repeat klaar" = epic repeat DONE
- **Size:** 274.2 MB
- **Waarom:** Expliciet gemarkeerd als "klaar" (complete)

**Alternatieve backups:**
- `mb_20260311_080641_voor_repeat_modes_11_15.tar.gz` (modes 11-15)
- `mb_20260311_084428_voor_repeat_modes_16_20.tar.gz` (modes 16-20)
- `mb_20260312_053524_voor_repeat_modes_16_20.tar.gz` (modes 16-20 v2)

### 2. Pivot/World Space System
**Beste backup:** `mandelbulber2_backup_20260307_091551_world_pivot_complete.tar.gz`
- **Datum:** 2026-03-07 09:15
- **Naam betekenis:** "world pivot complete"
- **Size:** 241.8 MB
- **Waarom:** Expliciet "complete" in naam

**Alternatieve backups:**
- `mb_20260307_190415_pivot_world_space_werkend.tar.gz` ("werkend" = working)
- `mb_20260311_073620_voor_world_coord_6_10.tar.gz` (coord fixes 6-10)

### 3. Deformation System
**Beste backup:** `Backup Mandelbulber met alle groepeen, deformers, cloner, OT , fractal textures.tar.gz`
- **Datum:** Unknown (maar recent)
- **Naam betekenis:** "alle groepeen, deformers, cloner"
- **Size:** 1738.9 MB (GROOT - volledige backup)
- **Waarom:** Expliciet "deformers" EN "cloner" in naam

### 4. Emission System
**Beste backup:** `mb_20260309_105130_voor_emission_complete_fix.tar.gz`
- **Datum:** 2026-03-09 10:51
- **Naam betekenis:** "voor emission complete fix"
- **Size:** 9.0 MB
- **Waarom:** "complete fix" voor emission

**Alternatieve backups:**
- `mb_20260309_101030_voor_primitive_emission.tar.gz` (primitive emission start)
- `mandelbulber2_backup_voor_emission_move_20260314_054142.tar.gz` (emission move)

---

## EXTRACTION STRATEGIE

### Aanpak: Per Systeem Extracten

We extracten systeem per systeem om controle te houden:

#### Stap 1: Epic Repeat System
```bash
# Extract uit: mb_20260307_194901_epic_repeat_klaar.tar.gz
# Benodigde files:
- src/compute_fractal.cpp (repeat logic)
- src/initparameters.cpp (repeat parameters)
- src/common_params.hpp (repeat struct members)
- opencl/engines/compute_fractal.cl (GPU repeat)
```

#### Stap 2: Pivot/World Space
```bash
# Extract uit: mandelbulber2_backup_20260307_091551_world_pivot_complete.tar.gz
# Benodigde files:
- src/compute_fractal.cpp (world coord transform)
- src/initparameters.cpp (pivot parameters)
- src/common_params.hpp (pivot/world members)
- opencl/engines/compute_fractal.cl (GPU world coord)
```

#### Stap 3: Deformation System
```bash
# Extract uit: Backup Mandelbulber met alle groepeen, deformers, cloner...
# Benodigde files:
- src/compute_fractal.cpp (deformation logic)
- src/initparameters.cpp (deform parameters)
- src/common_params.hpp (deform struct members)
- opencl/engines/compute_fractal.cl (GPU deformations)
```

#### Stap 4: Emission System
```bash
# Extract uit: mb_20260309_105130_voor_emission_complete_fix.tar.gz
# Benodigde files:
- src/primitive.cpp (emission logic)
- src/initparameters.cpp (emission parameters)
- opencl/engines/compute_fractal.cl (GPU emission)
```

---

## RISICO'S & VOORZORGSMAATREGELEN

### ⚠️ Risico's:
1. **Struct Size Mismatch** - GPU crash als CPU/GPU struct niet matchen
2. **Merge Conflicts** - Backups kunnen overlapping hebben met current work
3. **Parameter ID Conflicts** - Nieuwe parameters kunnen conflicteren met bestaande
4. **Build Failures** - Incomplete extraction kan build breken

### ✅ Voorzorgsmaatregelen:
1. **GPU Struct Check** - Run `gpu_struct_checker.py` NA elke extractie
2. **Backup Current State** - Maak backup VOOR extractie begint
3. **Test Builds** - Build EN test na elke systeem extractie
4. **Diff Review** - Review elke file diff voordat we mergen
5. **Incremental Approach** - 1 systeem per keer, volledig testen

---

## EXTRACTION VOLGORDE (Aanbevolen)

### Fase 1: Pivot/World Space (EERSTE)
**Waarom eerst:** Fundamenteel systeem, andere systemen kunnen ervan afhangen

**Backup:** `mandelbulber2_backup_20260307_091551_world_pivot_complete.tar.gz`

**Checklist:**
- [ ] Backup current state
- [ ] Extract pivot/world files
- [ ] Review diffs
- [ ] Merge changes
- [ ] Run gpu_struct_checker.py
- [ ] Build test
- [ ] Functional test
- [ ] Commit

### Fase 2: Epic Repeat System (TWEEDE)
**Waarom hierna:** Kan pivot systeem gebruiken

**Backup:** `mb_20260307_194901_epic_repeat_klaar.tar.gz`

**Checklist:**
- [ ] Backup current state
- [ ] Extract repeat files
- [ ] Review diffs (check overlap met Fase 1)
- [ ] Merge changes
- [ ] Run gpu_struct_checker.py
- [ ] Build test
- [ ] Functional test (test repeat modes)
- [ ] Commit

### Fase 3: Deformation System (DERDE)
**Waarom hierna:** Independent van repeat, maar kan repeat gebruiken

**Backup:** `Backup Mandelbulber met alle groepeen, deformers, cloner, OT , fractal textures.tar.gz`

**Checklist:**
- [ ] Backup current state
- [ ] Extract deformation files
- [ ] Review diffs
- [ ] Merge changes
- [ ] Run gpu_struct_checker.py
- [ ] Build test
- [ ] Functional test (test bend/twist/taper)
- [ ] Commit

### Fase 4: Emission System (LAATSTE)
**Waarom laatst:** Primitive-specifiek, minder afhankelijkheden

**Backup:** `mb_20260309_105130_voor_emission_complete_fix.tar.gz`

**Checklist:**
- [ ] Backup current state
- [ ] Extract emission files
- [ ] Review diffs
- [ ] Merge changes
- [ ] Run gpu_struct_checker.py
- [ ] Build test
- [ ] Functional test (test primitive emission)
- [ ] Commit

---

## TOOLS BESCHIKBAAR

### 1. backup_quick_extract.py
**Gebruik:** Extract specifieke files uit backups
```bash
python3 backup_quick_extract.py
# Kies custom pattern voor specifieke files
```

### 2. gpu_struct_checker.py
**Gebruik:** Check CPU/GPU struct sync
```bash
python3 gpu_struct_checker.py
# Run NA elke struct wijziging!
```

### 3. detailed_backup_compare.py
**Gebruik:** Vergelijk backup vs repo
```bash
python3 detailed_backup_compare.py
# Zie wat er ontbreekt
```

### 4. feature_presence_checker.py
**Gebruik:** Check of feature aanwezig is
```bash
python3 feature_presence_checker.py
# Verify na extractie
```

---

## VOLGENDE STAP

**KEUZE:**

**Optie A: Volledige Automatische Extractie**
- Maak een extraction tool die alles automatisch doet
- Risico: Minder controle
- Voordeel: Snel

**Optie B: Handmatige Stap-voor-Stap**
- Extract 1 systeem per keer
- Review elke change
- Risico: Langzamer
- Voordeel: Volledige controle, veiliger

**Optie C: Semi-Automatisch**
- Tool extracteert files
- Jij reviewt diffs voordat merge
- Risico: Medium
- Voordeel: Balans tussen snelheid en controle

---

**AANBEVELING:** Optie C - Semi-Automatisch

Ik maak een tool die:
1. Extract uit juiste backup
2. Toont diffs
3. Vraagt bevestiging
4. Merged changes
5. Run safety checks
6. Build test

**AKKOORD?**

# SAFE SYSTEM EXTRACTOR - Gebruikshandleiding

**Tool:** `safe_system_extractor.py`
**Versie:** 1.0
**Datum:** 2026-04-19

---

## WAT DOET DE TOOL?

De Safe System Extractor extracteert automatisch complete transform systems uit backups naar je repo, met volledige safety checks en rollback mogelijkheden.

### ✅ Safety Features:
1. **Automatische backup** van current state VOOR extractie
2. **Diff review** - Zie alle changes voordat je ze accepteert
3. **GPU struct check** - Voorkomt GPU crashes
4. **Feature verification** - Checkt of extractie gelukt is
5. **Test build** (optioneel) - Verify compilatie
6. **Rollback** - Herstel vorige state als er iets misgaat

---

## BESCHIKBARE SYSTEMEN

De tool kan deze 4 systemen extracten:

### 1. `pivot` - Pivot/World Space System
**Backup:** mandelbulber2_backup_20260307_091551_world_pivot_complete.tar.gz
**Features:** World coordinates, rotation pivot points
**Files:** 6 bestanden (compute_fractal, initparameters, common_params + OpenCL)

### 2. `repeat` - Epic Repeat System
**Backup:** mb_20260307_194901_epic_repeat_klaar.tar.gz
**Features:** Epic repeat modes (grid, brick, honeycomb, spiral, radial, etc.)
**Files:** 6 bestanden (compute_fractal, initparameters, common_params + OpenCL)

### 3. `deform` - Deformation System
**Backup:** Backup Mandelbulber met alle groepeen, deformers, cloner, OT , fractal textures.tar.gz
**Features:** Bend, twist, taper deformations
**Files:** 6 bestanden (compute_fractal, initparameters, common_params + OpenCL)

### 4. `emission` - Emission System
**Backup:** mb_20260309_105130_voor_emission_complete_fix.tar.gz
**Features:** Primitive emission modes
**Files:** 6 bestanden (primitive, initparameters, common_params + OpenCL)

---

## GEBRUIK

### Basic Gebruik

```bash
cd /home/joeri/mandelbulber2_v2_experiment
python3 dev_tools/safe_system_extractor.py
```

De tool zal vragen welk systeem je wilt extracten.

### Direct Systeem Opgeven

```bash
python3 dev_tools/safe_system_extractor.py pivot
python3 dev_tools/safe_system_extractor.py repeat
python3 dev_tools/safe_system_extractor.py deform
python3 dev_tools/safe_system_extractor.py emission
```

---

## EXTRACTIE PROCES (8 Stappen)

Wanneer je de tool runt, doorloopt het deze stappen:

### STEP 1: Creating safety backup
- Maakt volledige backup van huidige mandelbulber2/ directory
- Opgeslagen in: `SAFETY_BACKUPS/safety_backup_<system>_<timestamp>.tar.gz`
- Je kunt hiermee rollbacken als er iets misgaat

**Output:**
```
📦 STEP 1: Creating safety backup...
   Saved to: SAFETY_BACKUPS/safety_backup_pivot_20260419_143022.tar.gz
   Size: 156.3 MB
✅ Safety backup created
```

### STEP 2: Extracting files from backup
- Haalt de benodigde files uit de backup
- Zet ze tijdelijk in `/tmp/mandelbulber_extraction/`

**Output:**
```
📂 STEP 2: Extracting files from backup...
   ✓ src/compute_fractal.cpp
   ✓ src/compute_fractal.hpp
   ✓ src/initparameters.cpp
   ✓ src/common_params.hpp
   ✓ opencl/common_params_cl.hpp
   ✓ opencl/engines/compute_fractal.cl
✅ Extracted 6 files
```

### STEP 3: Reviewing changes
- Genereert diffs tussen current en extracted files
- Toont hoeveel lines toegevoegd/verwijderd worden

**Output:**
```
🔍 STEP 3: Reviewing changes...
   📝 src/compute_fractal.cpp: +342 -12 lines
   📝 src/initparameters.cpp: +89 -3 lines
   📝 src/common_params.hpp: +45 -0 lines
   ✅ opencl/common_params_cl.hpp: No changes
   📝 opencl/engines/compute_fractal.cl: +201 -8 lines
```

### STEP 4: Confirmation required
- Vraagt of je de changes wilt toepassen
- Opties: `yes`, `no`, `diff`

**Je kunt kiezen:**
- `yes` / `y` - Ga door met extractie
- `no` / `n` - Annuleer extractie
- `diff` - Bekijk volledige diffs eerst

**Output:**
```
⚠️  STEP 4: Confirmation required

Apply these changes? (yes/no/diff):
```

**Als je `diff` kiest:**
- Toont complete unified diffs voor alle files
- Eerste 100 lines per file
- Daarna vraagt het opnieuw om bevestiging

### STEP 5: Applying changes
- Kopieert extracted files naar je repo
- Overschrijft huidige versies

**Output:**
```
📝 STEP 5: Applying changes...
   ✓ src/compute_fractal.cpp
   ✓ src/compute_fractal.hpp
   ✓ src/initparameters.cpp
   ✓ src/common_params.hpp
   ✓ opencl/common_params_cl.hpp
   ✓ opencl/engines/compute_fractal.cl
✅ Files copied
```

### STEP 6: GPU struct safety check
- Runt `gpu_struct_checker.py`
- Checkt of CPU/GPU structs nog synced zijn
- **KRITIEK** - voorkomt GPU crashes!

**Output bij SUCCESS:**
```
🛡️  STEP 6: GPU struct safety check...
✅ GPU struct check passed
```

**Output bij FAILURE:**
```
🛡️  STEP 6: GPU struct safety check...
⚠️  WARNING: GPU struct check failed!
   This may cause GPU crashes!
Continue anyway? (yes/no):
```

**Als check faalt:**
- Krijg je optie om door te gaan of te rollbacken
- **AANBEVELING:** Type `no` en laat het rollbacken
- Review de struct changes manueel

### STEP 7: Verifying feature presence
- Checkt of feature keywords aanwezig zijn in de files
- Verifieert dat extractie gelukt is

**Output:**
```
🔍 STEP 7: Verifying feature presence...
   ✓ Found 'pivot' in src/compute_fractal.cpp
   ✓ Found 'worldCoord' in src/compute_fractal.cpp
   ✓ Found 'world_space' in src/initparameters.cpp
✅ Feature verified present
```

### STEP 8: Test build (optional)
- Vraagt of je een test build wilt runnen
- Runt `qmake` + `make` in qmake/ directory
- Stopt na eerste 10 files of bij errors

**Output:**
```
🔨 STEP 8: Test build (optional)...
Run test build? (yes/no): yes
   Running qmake...
   Running make (first 10 files)...
   ✅ No immediate compile errors
```

**Als build faalt:**
```
   ❌ Compile errors detected
Rollback? (yes/no):
```

---

## ROLLBACK

Als er iets misgaat, kun je rollbacken naar de safety backup.

### Automatische Rollback
De tool biedt automatisch rollback aan bij:
- GPU struct check failure
- Build errors
- Feature verification failure

### Handmatige Rollback

Als je later wilt rollbacken:

```bash
cd /home/joeri/mandelbulber2_v2_experiment

# Vind je backup
ls -lh SAFETY_BACKUPS/

# Rollback handmatig
rm -rf mandelbulber2/
tar -xzf SAFETY_BACKUPS/safety_backup_pivot_20260419_143022.tar.gz
```

---

## AANBEVOLEN VOLGORDE

Volg deze volgorde voor beste resultaten:

### 1. EERSTE: Pivot/World Space
```bash
python3 dev_tools/safe_system_extractor.py pivot
```
**Waarom eerst:** Fundamenteel systeem, andere kunnen hiervan afhangen

### 2. TWEEDE: Epic Repeat
```bash
python3 dev_tools/safe_system_extractor.py repeat
```
**Waarom hierna:** Kan pivot systeem gebruiken

### 3. DERDE: Deformation
```bash
python3 dev_tools/safe_system_extractor.py deform
```
**Waarom hierna:** Independent, maar kan repeat gebruiken

### 4. LAATSTE: Emission
```bash
python3 dev_tools/safe_system_extractor.py emission
```
**Waarom laatst:** Primitive-specific, minste dependencies

---

## TROUBLESHOOTING

### "Backup not found"
**Probleem:** Backup file bestaat niet in ~/mandelbulber2_backups/

**Oplossing:**
```bash
ls -lh ~/mandelbulber2_backups/ | grep -i <backup_name>
```

### GPU Struct Check Faalt
**Probleem:** CPU en GPU structs matchen niet

**Oorzaak:** common_params.hpp is veranderd maar common_params_cl.hpp niet geupdate

**Oplossing:**
1. Type `no` bij "Continue anyway?"
2. Laat het rollbacken
3. Run `populateOpenCL.php` om GPU struct te regenereren
4. Probeer extractie opnieuw

### Build Errors
**Probleem:** Compile errors na extractie

**Mogelijke oorzaken:**
- Incomplete extractie
- Missing dependencies
- Conflicting changes

**Oplossing:**
1. Rollback
2. Check git status voor conflicting changes
3. Review diffs zorgvuldiger
4. Mogelijk handmatige merge nodig

### Feature Not Found
**Probleem:** Feature keywords niet gevonden na extractie

**Oorzaak:** Verkeerde backup of incomplete extractie

**Oplossing:**
1. Rollback
2. Probeer andere backup voor dat systeem
3. Check of backup file de features echt bevat

---

## NA EXTRACTIE

### Git Status Checken
```bash
git status
git diff mandelbulber2/src/compute_fractal.cpp
```

### Testen
Test de nieuwe features in Mandelbulber UI

### Committen
```bash
git add mandelbulber2/
git commit -m "Add <system_name> from backup

Extracted using safe_system_extractor.py
Source: <backup_file>
Features: <feature_list>
"
```

---

## VEILIGHEIDS TIPS

1. **Commit je huidige work** VOOR extractie
2. **Run git status** om te zien wat er verandert
3. **Test build** altijd runnen bij belangrijke changes
4. **Backup de backups** - Safety backups blijven staan in SAFETY_BACKUPS/
5. **Een systeem per keer** - Niet meerdere tegelijk extracten

---

## VOORBEELD SESSIE

Volledige voorbeeld van pivot extractie:

```bash
$ python3 dev_tools/safe_system_extractor.py pivot

╔════════════════════════════════════════════════════════════════════╗
║                  SAFE SYSTEM EXTRACTOR v1.0                        ║
╚════════════════════════════════════════════════════════════════════╝

======================================================================
🔧 EXTRACTING: Pivot/World Space System
======================================================================
Backup: mandelbulber2_backup_20260307_091551_world_pivot_complete.tar.gz
Description: World coordinate system en rotation pivot points
Files: 6

📦 STEP 1: Creating safety backup...
   Saved to: SAFETY_BACKUPS/safety_backup_pivot_20260419_143022.tar.gz
   Size: 156.3 MB
✅ Safety backup created

📂 STEP 2: Extracting files from backup...
   ✓ src/compute_fractal.cpp
   ✓ src/compute_fractal.hpp
   ✓ src/initparameters.cpp
   ✓ src/common_params.hpp
   ✓ opencl/common_params_cl.hpp
   ✓ opencl/engines/compute_fractal.cl
✅ Extracted 6 files

🔍 STEP 3: Reviewing changes...
   📝 src/compute_fractal.cpp: +342 -12 lines
   📝 src/initparameters.cpp: +89 -3 lines
   📝 src/common_params.hpp: +45 -0 lines
   ✅ opencl/common_params_cl.hpp: No changes
   📝 opencl/engines/compute_fractal.cl: +201 -8 lines

⚠️  STEP 4: Confirmation required

Apply these changes? (yes/no/diff): yes
✅ Proceeding with extraction

📝 STEP 5: Applying changes...
   ✓ src/compute_fractal.cpp
   ✓ src/compute_fractal.hpp
   ✓ src/initparameters.cpp
   ✓ src/common_params.hpp
   ✓ opencl/common_params_cl.hpp
   ✓ opencl/engines/compute_fractal.cl
✅ Files copied

🛡️  STEP 6: GPU struct safety check...
✅ GPU struct check passed

🔍 STEP 7: Verifying feature presence...
   ✓ Found 'pivot' in src/compute_fractal.cpp
   ✓ Found 'worldCoord' in src/initparameters.cpp
✅ Feature verified present

🔨 STEP 8: Test build (optional)...
Run test build? (yes/no): no
⏭️  Skipping build test

======================================================================
✅ EXTRACTION COMPLETE!
======================================================================
System 'Pivot/World Space System' successfully extracted!
Safety backup: SAFETY_BACKUPS/safety_backup_pivot_20260419_143022.tar.gz

🎉 SUCCESS!
System 'Pivot/World Space System' extracted successfully!
```

---

## HULP NODIG?

De tool is volledig interactief en vraagt bevestiging bij belangrijke stappen.

**Bij problemen:**
1. Type `no` bij confirmation
2. Review de diffs
3. Check de safety backup
4. Probeer handmatige extractie

**Tools voor debugging:**
- `feature_presence_checker.py` - Check wat er aanwezig is
- `detailed_backup_compare.py` - Vergelijk backup vs repo
- `gpu_struct_checker.py` - Check struct safety

---

*Veel success met de extracties!* 🚀

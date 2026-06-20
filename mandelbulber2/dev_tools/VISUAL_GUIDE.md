# 📖 Visuele Handleiding: Mandelbulber Formula Wizard

> **Doel:** Een nieuwe formule maken zonder handmatig XML of C++ te schrijven.

---

## 🚀 Snelstart

```bash
cd mandelbulber2/dev_tools
python3 formula_wizard.py
```

---

## 🖼️ Stap 1: Wizard Openen

Wanneer je het commando uitvoert, opent dit venster:

```
┌─────────────────────────────────────────────────────────────┐
│  Mandelbulber Formula Wizard                                │
│                                                             │
│  [Welkom]  [Basis Info]  [Parameters]  [Code]  [Preview]   │
│                                                             │
│  Welkom bij de Formula Wizard                               │
│  ─────────────────────────────────────                      │
│                                                             │
│  Deze wizard helpt je stap voor stap een nieuwe             │
│  Mandelbulber formule te maken.                             │
│                                                             │
│  Wat gaan we doen?                                          │
│  ┌─────────────────────────────────────┐                    │
│  │ 1. Basis informatie — naam, type    │                    │
│  │ 2. Parameters — sliders, knoppen    │                    │
│  │ 3. Formule code — de berekening     │                    │
│  │ 4. Genereren — bestanden maken!     │                    │
│  └─────────────────────────────────────┘                    │
│                                                             │
│  Tips:                                                      │
│  • Transform formules beginnen met "transf_"                │
│  • Gebruik duidelijke namen                                 │
│  • Je kunt altijd terug                                     │
│                                                             │
│              [Volgende >]                                   │
└─────────────────────────────────────────────────────────────┘
```

**Klik op "Volgende"** om te beginnen.

---

## 🖼️ Stap 2: Basis Informatie Invullen

```
┌─────────────────────────────────────────────────────────────┐
│  Stap 1: Basis Informatie                                   │
│  ─────────────────────────                                  │
│                                                             │
│  Interne naam*:    [transf_mijn_effect        ]  ◄──┐      │
│                      ▲                              │      │
│                      │                              │      │
│  Gebruik kleine      │       Geen spaties!        │      │
│  letters en _________┘                              │      │
│  underscores                                       │      │
│                                                     │      │
│  Display naam*:     [T>Mijn Effect            ]  ◄──┐      │
│                      ▲                              │      │
│                      │       Dit ziet de gebruiker  │      │
│  Dit is wat je in    │       in de lijst           │      │
│  de UI ziet _________┘                              │      │
│                                                     │      │
│  Formule type:      [Transform (transf_) ▼]              │
│  DE Type:           [analyticDEType      ▼]              │
│  Default bailout:   [100.0               ▲▼]             │
│  Cpixel mode:       [cpixelEnabledByDefau▼]              │
│                                                             │
│  [< Vorige]  [Volgende >]                                   │
└─────────────────────────────────────────────────────────────┘
```

### 📝 Veld-uitleg:

| Veld | Voorbeeld | Uitleg |
|------|-----------|--------|
| **Interne naam** | `transf_rotatie_v2` | Unieke ID, kleine letters, underscores |
| **Display naam** | `T>Rotatie V2` | Wat gebruikers zien in de lijst |
| **Formule type** | Transform / Fractal / Primitive | Categorie |
| **DE Type** | analyticDEType | Distance Estimation methode |
| **Bailout** | 100.0 | Wanneer de iteratie stopt |

**✅ Tip:** Gebruik het `T>` prefix voor transforms zodat ze gegroepeerd staan in de lijst.

**Klik op "Volgende"** als alles is ingevuld.

---

## 🖼️ Stap 3: Parameters Toevoegen

```
┌─────────────────────────────────────────────────────────────┐
│  Stap 2: Parameters                                         │
│  ─────────────────                                          │
│                                                             │
│  ┌─────────────────────────────────────────────────────┐    │
│  │ Naam      │ Type      │ Label       │Default│Min│Max│    │
│  ├─────────────────────────────────────────────────────┤    │
│  │ scale     │ double  ▼ │ Scale       │ 2.0   │0.0│100│ ◄──┼── Slider
│  │ offset    │ cvector3▼ │ Offset      │0;0;0  │-100│100│ ◄──┼── 3D vector
│  │ iterations│ int     ▼ │ Iterations  │ 10    │ 1 │250│ ◄──┼── Getal
│  │ enabled   │ bool    ▼ │ Enable      │ true  │   │   │ ◄──┼── Vinkje
│  └─────────────────────────────────────────────────────┘    │
│                                                             │
│  [+ Parameter toevoegen]  [- Verwijder geselecteerde]       │
│                                                             │
│  ┌─────────────────────────────────────────────────────┐    │
│  │ 💡 Type uitleg:                                      │    │
│  │   double   → decimaal getal (slider)                │    │
│  │   cvector3 → 3D vector (x, y, z velden)             │    │
│  │   cvector4 → 4D vector (x, y, z, w velden)          │    │
│  │   int      → geheel getal                           │    │
│  │   bool     → aan/uit vinkje                         │    │
│  │   color    → kleurselector                          │    │
│  └─────────────────────────────────────────────────────┘    │
│                                                             │
│  [< Vorige]  [Volgende >]                                   │
└─────────────────────────────────────────────────────────────┘
```

### ➕ Parameter Toevoegen:

1. Klik op **"+ Parameter toevoegen"**
2. Vul de rij in:
   - **Naam:** unieke naam zonder spaties (`scale`, `offset_x`)
   - **Type:** kies uit de dropdown
   - **Label:** gebruikersvriendelijke naam
   - **Default:** startwaarde
   - **Min / Max:** bereik

### 🎯 Voorbeeld Parameters:

Voor een **scale transform** heb je nodig:
- `scale` (double) — hoeveel vergroten/verkleinen
- `offset` (cvector3) — verschuiving in x,y,z

Voor een **rotation transform** heb je nodig:
- `rotation` (cvector3) — hoeken in graden
- `center` (cvector3) — draaipunt

**Klik op "Volgende"** als je klaar bent.

---

## 🖼️ Stap 4: Formule Code Schrijven

```
┌─────────────────────────────────────────────────────────────┐
│  Stap 3: Formule Code                                       │
│  ─────────────────                                          │
│                                                             │
│  Schrijf hier de code die in void FormulaCode(...) komt.   │
│                                                             │
│  Beschikbare variabelen:                                   │
│  • z     — CVector4 (het punt dat je transformeert)        │
│  • aux   — sExtendedAux (distance estimation info)          │
│  • fractal — const sFractal* (toegang tot parameters)      │
│  • c     — CVector4 (constante c waarde)                   │
│                                                             │
│  ┌─────────────────────────────────────────────────────┐    │
│  │ // Voorbeeld: scale transform                       │    │
│  │ z *= fractal->transformCommon.scale;                │    │
│  │ aux.DE = aux.DE * fabs(fractal->transformCommon.scal│    │
│  │       e) + 1.0;                                     │    │
│  │                                                     │    │
│  │                                                     │    │
│  │                                                     │    │
│  │                                                     │    │
│  └─────────────────────────────────────────────────────┘    │
│                                                             │
│  [Scale]  [Rotation]  [Offset]      ◄── snel-voorbeelden    │
│                                                             │
│  [< Vorige]  [Volgende >]                                   │
└─────────────────────────────────────────────────────────────┘
```

### 📝 Code Tips:

- Gebruik **tabs** (`\t`) voor inspringing
- Je hoeft **geen** accolades of functie-header te schrijven
- Parameters zijn bereikbaar via `fractal->transformCommon.<naam>`

### 🔥 Veelgebruikte patronen:

**Scale:**
```cpp
z *= fractal->transformCommon.scale;
aux.DE = aux.DE * fabs(fractal->transformCommon.scale) + 1.0;
```

**Offset/Translation:**
```cpp
z += fractal->transformCommon.offset;
```

**Rotation:**
```cpp
z = fractal->transformCommon.rotationMatrix.RotateVector(z);
```

**Box Fold:**
```cpp
if (z.x > fractal->transformCommon.foldingLimit)
    z.x = fractal->transformCommon.foldValue - z.x;
else if (z.x < -fractal->transformCommon.foldingLimit)
    z.x = -fractal->transformCommon.foldValue - z.x;
```

**Klik op "Volgende"** om verder te gaan.

---

## 🖼️ Stap 5: Preview & Genereren

```
┌─────────────────────────────────────────────────────────────┐
│  Stap 4: Preview & Genereren                                │
│  ───────────────────────────                                │
│                                                             │
│  ┌─────────────────────────────────────────────────────┐    │
│  │ {                                                   │    │
│  │   "formula": {                                      │    │
│  │     "internal_name": "transf_mijn_effect",          │    │
│  │     "display_name": "T>Mijn Effect",                │    │
│  │     "de_type": "analyticDEType",                    │    │
│  │     ...                                             │    │
│  │   },                                                │    │
│  │   "parameters": [                                   │    │
│  │     { "name": "scale", "type": "double", ... },     │    │
│  │     ...                                             │    │
│  │   ],                                                │    │
│  │   "formula_code": "z *= ..."                        │    │
│  │ }                                                   │    │
│  └─────────────────────────────────────────────────────┘    │
│                                                             │
│  [🚀 Genereer Alle Bestanden]                               │
│                                                             │
│  Na generatie verschijnt hier het resultaat:               │
│                                                             │
│  ┌─────────────────────────────────────────────────────┐    │
│  │  ✅ Succes!                                          │    │
│  │  • Enum entry toegevoegd                             │    │
│  │  • C++ class gegenereerd                             │    │
│  │  • UI file gegenereerd                               │    │
│  │  • OpenCL stub gegenereerd                           │    │
│  │  • Parameter registratie toegevoegd                  │    │
│  │                                                     │    │
│  │  Volgende stap: Implementeer de formule logica      │    │
│  │  in FormulaCode() in de .cpp file.                  │    │
│  └─────────────────────────────────────────────────────┘    │
│                                                             │
│  [< Vorige]                                                 │
└─────────────────────────────────────────────────────────────┘
```

### 📂 Wat wordt er aangemaakt?

| Bestand | Locatie |
|---------|---------|
| C++ Source | `formula/definition/fractal_*.cpp` |
| C++ Header | `formula/definition/fractal_*.h` |
| UI XML | `deploy/share/mandelbulber2/formula/ui/*.ui` |
| OpenCL | `deploy/share/mandelbulber2/formula/opencl/*.cl` |
| Enum patch | `formula/definition/all_fractal_list_enums.hpp` |
| Factory patch | `formula/definition/all_fractal_list.cpp` |
| Parameter patch | `src/initparameters.cpp` |

---

## 🖼️ Stap 6: Code Implementeren (Handmatig)

De wizard genereert een **stub** met een lege `FormulaCode()` functie. Je moet nog de wiskundige logica toevoegen:

```cpp
// Open de gegenereerde .cpp file
// Zoek naar de FormulaCode() functie

void cFractalTransfMijnEffect::FormulaCode(
    CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
    // ═══════════════════════════════════════
    // JOUW CODE HIER!
    // ═══════════════════════════════════════
    
    // Voorbeeld: simpele scale
    z *= fractal->transformCommon.scale;
    aux.DE = aux.DE * fabs(fractal->transformCommon.scale) + 1.0;
    
    // ═══════════════════════════════════════
}
```

### 🔧 Compilen:

```bash
cd ~/mandelbulber2_v2_experiment/mandelbulber2
qmake mandelbulber.pro
make -j$(nproc)
```

### ▶️ Testen:

1. Start Mandelbulber
2. Ga naar het **Formula** tabblad
3. Zoek je formule in de lijst (bijv. **T>Mijn Effect**)
4. Selecteer hem en bekijk de sliders!

---

## 🎯 Volledig Voorbeeld: "Mijn Eerste Transform"

Hier is een compleet voorbeeld dat je kunt volgen:

### Wizard Invulling:

| Stap | Waarde |
|------|--------|
| **Interne naam** | `transf_dubbele_scale` |
| **Display naam** | `T>Dubbele Scale` |
| **Type** | Transform |
| **DE Type** | analyticDEType |

### Parameters:

| Naam | Type | Label | Default | Min | Max |
|------|------|-------|---------|-----|-----|
| `scale1` | double | Eerste Scale | 2.0 | 0.001 | 100 |
| `scale2` | double | Tweede Scale | 0.5 | 0.001 | 100 |
| `offset` | cvector3 | Offset | 0;0;0 | -100 | 100 |

### Code:

```cpp
z *= fractal->transformCommon.scale1;
z += fractal->transformCommon.offset;
aux.DE = aux.DE * fabs(fractal->transformCommon.scale1) + 1.0;
```

### Resultaat:

Je krijgt een formule die:
1. Het punt schaalt met `scale1`
2. Een offset toevoegt
3. De distance estimation bijwerkt

---

## ❗ Problemen Oplossen

| Probleem | Oplossing |
|----------|-----------|
| "Naam mag geen spaties bevatten" | Gebruik underscores: `transf_mijn_formule` |
| "Kan bestand niet vinden" | Zorg dat je in `mandelbulber2/dev_tools` staat |
| Parameters verschijnen niet | Controleer of `initparameters.cpp` is gepatched |
| UI laadt niet | Run `validate_formula_ui.py` op je .ui file |
| Compile error | Controleer of alle haakjes sluiten in je C++ code |

---

## 📚 Gerelateerde Tools

| Tool | Gebruik |
|------|---------|
| `formula_wizard.py` | ⭐ Deze GUI wizard |
| `generate_complete_formula.py` | Command-line versie |
| `validate_formula_ui.py` | Controleer UI files op fouten |
| `generate_formula_ui.py` | Genereer alleen UI XML |

---

**Veel succes met je formules! 🎨🔢**

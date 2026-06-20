# Mandelbulber Qt Designer Toolkit

## 🎯 Doel

Maakt het werken met Qt Designer voor Mandelbulber **dramatisch** gebruiksvriendelijker. Dit lost het probleem op dat **80% van de fouten UI/Qt-gerelateerd** zijn.

---

## 📦 Wat Je Krijgt

| Tool | Bestand | Wat Het Doet |
|------|---------|-------------|
| **Designer Plugin** | `mandelbulber_widgets_plugin.pro` | Laat Qt Designer Mandelbulber custom widgets weergeven |
| **Designer Project** | `mandelbulber_designer_project.pro` | Open alle UI's als één project in Designer |
| **Widget Wrappers** | `designer/*.h` | Lichtgewicht versies van custom widgets voor Designer |
| **UI Validator** | `validate_formula_ui.py` | Vangt widget-naam fouten **vóór** runtime |
| **UI Generator** | `generate_formula_ui.py` | Genereert formula XML automatisch vanuit JSON |

---

## 🔧 Snelstart

### Stap 1: Installeer de Qt Designer Plugin

```bash
cd ~/mandelbulber2_v2_experiment/mandelbulber2/designer
qmake mandelbulber_widgets_plugin.pro
make
sudo make install
```

Dit kopieert `libmandelbulber_widgets_plugin.so` naar `/usr/lib/qt5/plugins/designer/`.

**Herstart Qt Designer** na installatie.

> 💡 Je vindt de widgets nu in de "Widget Box" onder **"Mandelbulber Widgets"**.

---

### Stap 2: Open het Designer Project

```bash
designer mandelbulber_designer_project.pro
```

Nu kun je **alle** UI files bewerken:
- Statische UI's: `dock_*.ui`, `render_window.ui`, `tab_fractal.ui`, etc.
- Formula UI's: `mandelbox_fast.ui`, `abox_mod13.ui`, etc.
- Primitive UI's: `primitive_sphere.ui`, etc.

---

### Stap 3: Valideer Je Formula UI

Controleer één file:
```bash
python3 validate_formula_ui.py ../deploy/share/mandelbulber2/formula/ui/mijn_formule.ui
```

Controleer ALLE formula UI's:
```bash
python3 validate_formula_ui.py --all
```

---

### Stap 4: Genereer Een Nieuwe Formula UI

Maak een JSON bestand `mijn_params.json`:

```json
{
  "formula": {
    "internal_name": "mijn_nieuwe_formule",
    "display_name": "Mijn Nieuwe Formule"
  },
  "parameters": [
    {
      "name": "scale",
      "type": "double",
      "label": "Scale",
      "default": 2.0,
      "min": 0.001,
      "max": 100.0,
      "step": 0.1,
      "decimals": 6
    },
    {
      "name": "rotation",
      "type": "cvector3",
      "label": "Rotation",
      "default": [0.0, 0.0, 0.0],
      "min": -36000.0,
      "max": 36000.0
    },
    {
      "name": "iterations",
      "type": "int",
      "label": "Iterations",
      "default": 10,
      "min": 1,
      "max": 250
    },
    {
      "name": "enabled",
      "type": "bool",
      "label": "Enable feature",
      "default": true
    }
  ]
}
```

Genereer de UI:
```bash
python3 generate_formula_ui.py \
  --input mijn_params.json \
  --output ../deploy/share/mandelbulber2/formula/ui/mijn_nieuwe_formule.ui
```

✅ Klaar! De UI is gegenereerd én gevalideerd.

---

## 🏗️ Hoe Het Werkt

### Het Oorspronkelijke Probleem

Qt Designer kon **niets** met Mandelbulber's custom widgets:

```
MyDoubleSpinBox  →  ❌ Niet herkend → placeholder
MyCheckBox       →  ❌ Niet herkend → verkeerde widget
MySpinBox        →  ❌ Niet herkend → verkeerde widget
```

Dit forceerde ontwikkelaars om **300+ regels XML met de hand te schrijven**.

### De Oplossing

```
┌────────────────────────────────────────────────────────────┐
│  Qt Designer                                               │
│     │                                                      │
│     ▼                                                      │
│  ┌──────────────────────────────┐                         │
│  │ mandelbulber_widgets_plugin  │ ← Geladen als plugin    │
│  │                              │                         │
│  │  MyDoubleSpinBoxPlugin       │ ← Registreert class     │
│  │  MySpinBoxPlugin             │                         │
│  │  MyCheckBoxPlugin            │                         │
│  │  ...                         │                         │
│  └──────────────────────────────┘                         │
│     │                                                      │
│     ▼                                                      │
│  ┌──────────────────────────────┐                         │
│  │ Designer-safe wrappers       │                         │
│  │ (geen Mandelbulber deps!)    │                         │
│  │                              │                         │
│  │  MyDoubleSpinBox  → QDoubleSpinBox  (lightweight)     │
│  │  MyCheckBox       → QCheckBox       (lightweight)     │
│  │  MySpinBox        → QSpinBox        (lightweight)     │
│  │  ...                        │                         │
│  └──────────────────────────────┘                         │
└────────────────────────────────────────────────────────────┘
```

De wrappers hebben **exact dezelfde class namen** als de echte widgets, maar zonder afhankelijkheden op Mandelbulber internals (`CommonMyWidgetWrapper`, animatie systeem, etc.).

---

## 📋 Ondersteunde Parameter Types (Generator)

| Type | UI Widget | Voorbeeld JSON |
|------|-----------|----------------|
| `double` | `MyDoubleSpinBox` | `{"type": "double", "default": 2.0, "min": 0, "max": 100}` |
| `cvector3` | 3× `MyDoubleSpinBox` (x,y,z) | `{"type": "cvector3", "default": [0,0,0]}` |
| `cvector4` | 4× `MyDoubleSpinBox` (x,y,z,w) | `{"type": "cvector4", "default": [0,0,0,1]}` |
| `int` | `MySpinBox` | `{"type": "int", "default": 10, "min": 1, "max": 250}` |
| `bool` | `MyCheckBox` | `{"type": "bool", "default": true}` |
| `enum` | `MyComboBox` | `{"type": "enum", "options": ["A", "B", "C"]}` |
| `color` | `MyColorButton` | `{"type": "color"}` |

---

## 🔍 Validator Regels

De validator controleert:

| Regel | Ernst | Beschrijving |
|-------|-------|-------------|
| Geldig XML | 🔴 ERROR | Bestand moet parseerbare XML zijn |
| Widget prefix | 🔴 ERROR | `spinboxd_`, `checkBox_`, etc. moet bekend zijn |
| Correcte class | 🟡 WARNING | `spinboxd_` moet `MyDoubleSpinBox` zijn |
| CVector3 compleet | 🔴 ERROR | `_x`, `_y`, `_z` moeten alle drie bestaan |
| CVector4 compleet | 🔴 ERROR | `_x`, `_y`, `_z`, `_w` moeten alle vier bestaan |
| Partner widget | 🔴 ERROR | `slider_` moet een bijbehorende `spinbox_` hebben |
| Custom widgets declared | 🟡 WARNING | Gebruikte custom widgets moeten in `<customwidgets>` staan |
| Vereiste properties | 🟡 WARNING | `MyDoubleSpinBox` moet `decimals` hebben |
| Duplicate namen | 🔴 ERROR | Geen twee widgets met dezelfde naam |

---

## 🚀 Workflow Vergelijking

### OUD (foutgevoelig)
```
1. Handmatig 300+ regels XML schrijven
2. Rebuild Mandelbulber
3. Start app
4. Ontdek dat parameter niet werkt
5. Zoek typo in widget naam
6. Herhaal...
```

### NIEUW (gebruiksvriendelijk)
```
1. Schrijf simpel JSON bestand
2. python3 generate_formula_ui.py --input params.json --output formula.ui
3. (Optioneel) Bewerk visueel in Qt Designer
4. python3 validate_formula_ui.py formula.ui
5. Test in Mandelbulber (geen rebuild nodig voor formula UI's!)
```

---

## 🛠️ Bestanden Overzicht

```
mandelbulber2/designer/
├── README.md                              ← Dit bestand
├── mandelbulber_widgets_plugin.pro        ← Plugin build file
├── mandelbulber_widgets_plugin.h          ← Plugin declaraties
├── mandelbulber_widgets_plugin.cpp        ← Plugin implementatie
├── mandelbulber_designer_project.pro      ← Designer project file
├── dummy_main.cpp                         ← Dummy main voor qmake
├── validate_formula_ui.py                 ← UI validator tool
├── generate_formula_ui.py                 ← UI generator tool
├── my_double_spin_box.h                   ← Designer-safe wrapper
├── my_spin_box.h                          ← Designer-safe wrapper
├── my_check_box.h                         ← Designer-safe wrapper
├── my_combo_box.h                         ← Designer-safe wrapper
├── my_group_box.h                         ← Designer-safe wrapper
├── my_line_edit.h                         ← Designer-safe wrapper
└── my_color_button.h                      ← Designer-safe wrapper
```

---

*Gemaakt om het leven van Mandelbulber ontwikkelaars makkelijker te maken.*

# Qt Designer Analyse: Mandelbulber2

## Samenvatting

Mandelbulber2 gebruikt Qt Designer op een **hybride manier** met twee duidelijk gescheiden strategieën:

1. **Statische UI's** — Compile-time gegenereerd via `uic` (Qt UI Compiler) voor de hoofdapplicatie
2. **Dynamische UI's** — Runtime geladen via een custom `QUiLoader` voor formules en primitives

---

## 1. Projectstructuur UI-Bestanden

### 1.1 Statische UI's (`mandelbulber2/qt/*.ui`)

| Bestand | Regels | Functie |
|---------|--------|---------|
| `dock_effects.ui` | 10.812 | Effects dock (grootste UI) |
| `material_editor.ui` | 6.044 | Materiaal editor |
| `dock_fractal.ui` | 2.799 | Fractal dock |
| `dock_rendering_engine.ui` | 2.467 | Rendering engine settings |
| `preferences_dialog.ui` | 2.197 | Voorkeuren dialoog |
| `render_window.ui` | 1.881 | Hoofdrender venster |
| `dock_animation.ui` | 1.665 | Animatie dock |
| `dock_navigation.ui` | 1.493 | Navigatie dock |
| `tab_fractal.ui` | 1.254 | Fractal tab container |
| `dock_image_adjustments.ui` | 1.165 | Afbeelding aanpassingen |
| **Overige 23 bestanden** | **~8.000** | Diverse dialogs en docks |
| **TOTAAL** | **~39.663** | 33 statische UI bestanden |

### 1.2 Dynamische Formula UI's (`deploy/share/mandelbulber2/formula/ui/*.ui`)

- **472 formula UI bestanden** — één per fractal formule
- **16 primitive UI bestanden** (`primitive_*.ui`) — voor 3D primitives
- Deze worden **niet** door `uic` gecompileerd, maar **runtime** geladen

---

## 2. Build Systeem Integratie

### 2.1 QMake (`mandelbulber2/qmake/common.pri`)

```qmake
QT += core gui uitools widgets network testlib multimedia qml concurrent

# Statische UI bestanden voor uic compilatie
FORMS += $$ROOT/qt/*.ui

# Output directory voor gegenereerde headers
UI_DIR = $$ROOT/qt
```

**Wat gebeurt hier:**
- `uic` (Qt UI Compiler) verwerkt alle `qt/*.ui` bestanden
- Genereert C++ headers (`ui_*.h`) in `mandelbulber2/qt/`
- Deze headers bevatten een `setupUi()` methode die de widgets opbouwt

### 2.2 CMake (`mandelbulber2/cmake/CMakeLists.txt`)

```cmake
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ../qt/)

find_package(Qt5UiTools REQUIRED)
```

**Opmerking:** CMake gebruikt `AUTOUIC` maar alleen voor de `qt/*.ui` bestanden. De formula UI's in `deploy/share/` worden **niet** meegenomen in de build.

---

## 3. Gegenereerde Headers (`ui_*.h`)

Voorbeeld: `ui_dock_fractal.h` (uit `dock_fractal.ui`)

```cpp
#ifndef UI_DOCK_FRACTAL_H
#define UI_DOCK_FRACTAL_H

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTabWidget>
// ... meer includes

#include "my_double_spin_box.h"
#include "my_check_box.h"
#include "my_combo_box.h"
// ... custom widgets

class Ui_cDockFractal
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget_fractal;
    // ... alle widget pointers
    
    void setupUi(QWidget *cDockFractal)
    {
        // Bouwt de volledige widget hierarchy op
        // Maakt layouts, plaatst widgets, zet properties
    }
};
```

**Gebruik in C++ code:**
```cpp
// render_window.cpp
mainWindow = new RenderWindow();
// ...
ui->setupUi(this);  // Roept de gegenereerde setupUi() aan
```

---

## 4. Dynamisch UI Laden met MyUiLoader

### 4.1 Architectuur

```
QUiLoader (Qt base class)
    └── MyUiLoader (custom override)
        └── createWidget() — instantiate custom widgets
```

### 4.2 MyUiLoader Implementatie

**Header:** `mandelbulber2/src/my_ui_loader.h`
**Source:** `mandelbulber2/src/my_ui_loader.cpp`

```cpp
class MyUiLoader : public QUiLoader
{
    Q_OBJECT
public:
    MyUiLoader(QObject *parent = nullptr) : QUiLoader(parent) {}
    ~MyUiLoader() override;

    QWidget *createWidget(
        const QString &className, QWidget *parent = nullptr, 
        const QString &name = QString()) override;
};
```

De `createWidget()` override herkent custom widget class namen en instantieert de juiste klassen:

| Class Name | C++ Class | Bestand |
|------------|-----------|---------|
| `MyLineEdit` | `MyLineEdit` | `qt/my_line_edit.h` |
| `MySpinBox` | `MySpinBox` | `qt/my_spin_box.h` |
| `MyDoubleSpinBox` | `MyDoubleSpinBox` | `qt/my_double_spin_box.h` |
| `MyCheckBox` | `MyCheckBox` | `qt/my_check_box.h` |
| `MyGroupBox` | `MyGroupBox` | `qt/my_group_box.h` |
| `MyColorButton` | `MyColorButton` | `qt/my_color_button.h` |
| `FileSelectWidget` | `FileSelectWidget` | `qt/file_select_widget.h` |
| `cMaterialSelector` | `cMaterialSelector` | `qt/material_selector.h` |
| `MyComboBox` | `MyComboBox` | `qt/my_combo_box.h` |
| *Standaard Qt* | *Via `QUiLoader::createWidget()`* | — |

### 4.3 Gebruik: Formula UI Laden

**Locatie:** `mandelbulber2/qt/tab_fractal.cpp` (regel 179)

```cpp
void cTabFractal::slotChangedComboFractal(int indexInComboBox)
{
    // ...
    QString formulaName = newFractalList[index]->getInternalName();
    QString uiFilename = newFractalList[index]->getUiFilename();
    // uiFilename = "<sharedDir>/formula/ui/<internalName>.ui"
    
    MyUiLoader loader;
    QFile uiFile(uiFilename);
    
    if (uiFile.exists())
    {
        uiFile.open(QFile::ReadOnly);
        fractalWidget.reset(loader.load(&uiFile));  // DYNAMISCH LADEN
        uiFile.close();
        // ...
        layout->addWidget(fractalWidget.get());
        fractalWidget->show();
    }
}
```

### 4.4 Gebruik: Primitive UI Laden

**Locatie:** `mandelbulber2/qt/primitives_manager.cpp` (regel 141)

```cpp
void cPrimitivesManager::AddPrimitive(bool init, const sPrimitiveItem &primitive)
{
    QString uiFileName = systemDirectories.sharedDir + "formula/ui/primitive_" 
                         + primitiveType + ".ui";
    
    MyUiLoader loader;
    QFile uiFile(uiFileName);
    if (uiFile.exists())
    {
        uiFile.open(QFile::ReadOnly);
        QWidget *newEditor = loader.load(&uiFile);  // DYNAMISCH LADEN
        uiFile.close();
        ui->tabWidget_primitives->addTab(newEditor, name);
    }
}
```

---

## 5. Custom Widgets

### 5.1 Overzicht

Mandelbulber definieert eigen widgets die uitbreiden op standaard Qt widgets. Deze worden gedeclareerd in `.ui` bestanden via de `<customwidgets>` sectie.

### 5.2 Voorbeeld: MyDoubleSpinBox

**Header:** `mandelbulber2/qt/my_double_spin_box.h`

```cpp
class MyDoubleSpinBox : public QDoubleSpinBox, public CommonMyWidgetWrapper
{
    Q_OBJECT
public:
    MyDoubleSpinBox(QWidget *parent = nullptr);
    // ... extra functionaliteit
    
private:
    cFrameSliderPopup *slider;  // Popup slider bij rechtermuisklik
    double defaultValue;
    enumSliderPrecision precision;
    
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    
private slots:
    void slotResetToDefault();
    void slotZeroValue();
    void slotDoubleValue();
    void slotSliderMoved(int sliderPosition);
    // ...
};
```

**Features:**
- Rechtermuisklik context menu (reset, *2, /2, etc.)
- Popup slider voor snelle waarde aanpassing
- Script indicator (geeft aan als een parameter geanimeerd is)
- Precision modes

### 5.3 UI Bestand Declaratie

```xml
<customwidgets>
 <customwidget>
  <class>MyDoubleSpinBox</class>
  <extends>QDoubleSpinBox</extends>
  <header>my_double_spin_box.h</header>
 </customwidget>
 <!-- ... meer custom widgets -->
</customwidgets>
```

---

## 6. Widget Naming Conventions

### 6.1 AutomatedWidgets Systeem

**Locatie:** `mandelbulber2/src/automated_widgets.cpp`

`cAutomatedWidgets` verbindt automatisch sliders met hun bijbehorende spinboxes/edit velden op basis van **naamconventies**:

| Widget Type | Naam Patroon | Voorbeeld |
|-------------|-------------|-----------|
| Double spinbox | `spinboxd_<param>` | `spinboxd_mandelbox_scale` |
| CVector3 (x,y,z) | `spinboxd3_<param>_<axis>` | `spinboxd3_transf_rotation_x` |
| CVector4 (x,y,z,w) | `spinboxd4_<param>_<axis>` | `spinboxd4_transf_color_xyzw_x` |
| Int spinbox | `spinbox_<param>` | `spinbox_iterations` |
| Checkbox | `checkBox_<param>` | `checkBox_mandelbox_main_rotation_enabled` |
| Combobox | `comboBox_<param>` | `comboBox_mode` |
| Slider (gekoppeld) | `slider_<spinbox_naam>` | `slider_spinboxd_scale` |
| Log slider | `logslider_<param>` | — |
| Dial | `dial_<param>` | — |

### 6.2 Voorbeeld uit Formula UI

```xml
<widget class="MyDoubleSpinBox" name="spinbox_mandelbox_folding_min_radius">
 <property name="decimals"><number>6</number></property>
 <property name="minimum"><double>0.0</double></property>
 <property name="maximum"><double>99.999</double></property>
 <property name="singleStep"><double>0.01</double></property>
</widget>
```

---

## 7. Formula UI Bestand Structuur

### 7.1 Locatie & Naamgeving

```
deploy/share/mandelbulber2/formula/ui/
├── <internal_name>.ui          # Fractal formule UI (472 bestanden)
├── primitive_<type>.ui         # Primitive UI (16 bestanden)
└── transf_<name>.ui            # Transform UI
```

**Naam resolutie:**
```cpp
// abstract_fractal.h
QString getUiFilename() const
{
    return systemDirectories.sharedDir + "formula" + QDir::separator() 
         + "ui" + QDir::separator() + internalName + ".ui";
}
```

### 7.2 Typisch Formula UI Layout

```xml
<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>mandelbox_fast</class>
 <widget class="QWidget" name="Form">
  <layout class="QVBoxLayout" name="verticalLayout">
   <property name="spacing"><number>2</number></property>
   
   <!-- Titel -->
   <item>
    <widget class="QLabel" name="label_title">
     <property name="text">
      <string notr="true">Mandelbox Fast</string>
     </property>
    </widget>
   </item>
   
   <!-- Parameter grid -->
   <item>
    <layout class="QGridLayout" name="gridLayout_params">
     <!-- Labels + MyDoubleSpinBox per parameter -->
    </layout>
   </item>
   
   <!-- Spacer -->
   <item>
    <spacer name="verticalSpacer">
     <property name="orientation"><enum>Qt::Vertical</enum></property>
    </spacer>
   </item>
  </layout>
 </widget>
 
 <!-- Custom widgets declaratie -->
 <customwidgets>
  <customwidget>
   <class>MyDoubleSpinBox</class>
   <extends>QDoubleSpinBox</extends>
   <header>my_double_spin_box.h</header>
  </customwidget>
  <!-- ... -->
 </customwidgets>
</ui>
```

---

## 8. UI Generator Tool

### 8.1 `dev_tools/ui_generator.py`

Een Python tool om formula UI's automatisch te genereren van parameter definities.

**Probleem dat het oplost:**
- Elke nieuwe formule = 260+ regels XML handmatig schrijven
- Copy-paste errors
- 1-2 uur werk per formule

**Ondersteunde parameter types:**

| ParamType | UI Widget | Naam Patroon |
|-----------|-----------|--------------|
| `CVector3` | 3× `MyDoubleSpinBox` (x,y,z) | `spinboxd3_<formula>_<param>_<axis>` |
| `CVector4` | 4× `MyDoubleSpinBox` (x,y,z,w) | `spinboxd4_<formula>_<param>_<axis>` |
| `double` | 1× `MyDoubleSpinBox` | `spinboxd_<formula>_<param>` |
| `int` | 1× `MySpinBox` | `spinbox_<formula>_<param>` |
| `bool` | 1× `MyCheckBox` | `checkBox_<formula>_<param>` |
| `enum` | 1× `MyComboBox` | `comboBox_<formula>_<param>` |
| `color` | 1× `MyColorButton` | `colorButton_<formula>_<param>` |

### 8.2 Voorbeeld Output

```bash
$ python3 dev_tools/ui_generator.py --demo

🎨 Generating UI for: T>Rotation V2
Parameters: 3
Output: dev_tools/generated_ui/transf_rotation_v2.ui

✅ Generated: dev_tools/generated_ui/transf_rotation_v2.ui
   Lines: 156
```

---

## 9. Workflow Vergelijking

### 9.1 Statische UI Workflow

```
Qt Designer
    ↓
dock_fractal.ui (XML)
    ↓
uic (Qt UI Compiler) ← compile-time
    ↓
ui_dock_fractal.h (C++ header)
    ↓
#include in C++ code
    ↓
setupUi(this) ← roept gegenereerde code aan
```

### 9.2 Dynamische UI Workflow

```
Formula definitie (C++)
    ↓
getUiFilename() → ".../formula/ui/mandelbox_fast.ui"
    ↓
MyUiLoader::load(&uiFile) ← runtime
    ↓
XML parsing + createWidget() calls
    ↓
QWidget* tree returned
    ↓
layout->addWidget(formulaWidget)
```

---

## 10. Voordelen & Nadelen

### 10.1 Hybride Aanpak (wat Mandelbulber doet)

| Aspect | Statisch | Dynamisch |
|--------|----------|-----------|
| **Snelheid** | ✅ Snel (gecompileerde code) | ❌ Trager (XML parsing) |
| **Type safety** | ✅ Compile-time checks | ❌ Runtime fouten |
| **Flexibiliteit** | ❌ Vast na compilatie | ✅ Formules toevoegen zonder rebuild |
| **Distributie** | ❌ In binary | ✅ Losse .ui bestanden |
| **Debugbaar** | ✅ Ja | ⚠️ Moeilijker |
| **IDE support** | ✅ Goed | ⚠️ Beperkt |

### 10.2 Waarom Mandelbulber Dynamisch Gebruikt voor Formules

1. **472 formules** — Te veel om allemaal in de binary te compileren
2. **Community formules** — Gebruikers kunnen eigen `.ui` bestanden toevoegen
3. **Snelle iteratie** — Formula UI aanpassen zonder hele applicatie te rebuilden
4. **Consistentie** — Alle formules gebruiken hetzelfde UI patroon

---

## 11. Aandachtspunten voor Ontwikkeling

### 11.1 Widget Naam Conventie

**CRITICAL:** Widget namen MOETEN exact overeenkomen met parameter namen in de C++ code. Een typefout in de `.ui` filename of widget name = parameter werkt niet.

```cpp
// Deze naam in .ui:
name="spinboxd_mandelbox_scale"

// Moet overeenkomen met parameter naam in fractal params:
fractal->mandelbox.scale
```

### 11.2 Custom Widget Header Paden

In `.ui` bestanden worden custom widgets gedeclareerd met relatieve headers:
```xml
<header>my_double_spin_box.h</header>
```

Dit vereist dat de include path correct is ingesteld in het build systeem.

### 11.3 UI Bestand Deployment

Formula UI's moeten meegeleverd worden bij installatie:

```cmake
# CMakeLists.txt
install(DIRECTORY ../deploy/share/mandelbulber2/ DESTINATION "${SHARED_DIR}")
install(DIRECTORY ../formula DESTINATION "${SHARED_DIR}")
```

---

## 12. Statistieken

| Metric | Waarde |
|--------|--------|
| Statische UI bestanden | 33 |
| Formula UI bestanden | 472 |
| Primitive UI bestanden | 16 |
| **Totaal UI bestanden** | **521** |
| Statische UI regels (XML) | ~39.600 |
| Custom widget klassen | 15+ |
| Gemiddelde formula UI grootte | ~350 regels |
| Grootste statische UI | `dock_effects.ui` (10.812 regels) |

---

## 13. Conclusie

Mandelbulber2's Qt Designer architectuur is **elegant en schaalbaar**:

- **Statische UI's** voor de vaste applicatie shell (hoog performance, type-safe)
- **Dynamische UI's** voor formules/primitives (flexibel, uitbreidbaar)
- **MyUiLoader** als brug om custom widgets in runtime geladen XML te ondersteunen
- **AutomatedWidgets** elimineert handmatige signal/slot verbindingen
- **UI Generator** tool versnelt formula ontwikkeling dramatisch

Deze aanpak maakt het mogelijk om 472+ formules te ondersteunen zonder de binary te laten exploderen, terwijl de kern-UI snel en betrouwbaar blijft.

---

*Analyse gegenereerd op: 2026-04-21*
*Project: mandelbulber2_v2_experiment*

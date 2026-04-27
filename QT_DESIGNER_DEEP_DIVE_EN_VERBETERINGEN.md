# Qt Designer Deep Dive + Verbeteringsvoorstellen

Dit document behandelt diepgaand:
1. Hoe je een nieuwe formula UI maakt (stap-voor-stap)
2. Hoe `MyUiLoader` precies werkt
3. Hoe `AutomatedWidgets` signal/slot verbindingen maakt
4. **Verbeteringsvoorstellen** om alles gebruiksvriendelijker te maken

---

# DEEL 1: Hoe Je Een Nieuwe Formula UI Maakt

## 1.1 Huidige Workflow (Stap-voor-stap)

Om een nieuwe fractal formule toe te voegen met UI in Mandelbulber, moet je **7 verschillende bestanden** aanmaken/wijzigen:

### Stap 1: Formule C++ Code schrijven

**Bestand:** `mandelbulber2/formula/definition/fractal_<naam>.cpp`

```cpp
#include "all_fractal_definitions.h"

cFractalMijnNieuweFormule::cFractalMijnNieuweFormule() : cAbstractFractal()
{
    nameInComboBox = "Mijn Nieuwe Formule";   // Zichtbare naam in UI
    internalName = "mijn_nieuwe_formule";      // MOET overeenkomen met .ui filename!
    internalID = fractal::mijnNieuweFormule;   // Enum waarde
    DEType = analyticDEType;
    DEFunctionType = linearDEFunction;
    cpixelAddition = cpixelEnabledByDefault;
    defaultBailout = 100.0;
    DEAnalyticFunction = analyticFunctionLinear;
    coloringFunction = coloringFunctionDefault;
}

void cFractalMijnNieuweFormule::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
    // Jouw formule code hier
    z = z * fractal->mijnNieuweFormule.scale;
    aux.DE = aux.DE * fabs(fractal->mijnNieuweFormule.scale) + 1.0;
}
```

### Stap 2: Parameter struct definiëren

**Bestand:** `mandelbulber2/src/fractparams.hpp` (of gelijkwaardig)

Je moet een C-struct definiëren voor de parameters die de formule gebruikt. Dit is **handmatig C++ struct werk**:

```cpp
struct sMijnNieuweFormule
{
    double scale;
    CVector3 rotation;
    int iterations;
    bool enabled;
    // ... etc
};
```

### Stap 3: Parameters registreren bij het systeem

**Bestand:** `mandelbulber2/src/initparameters.cpp` (typisch)

```cpp
// Registreer defaults voor elke parameter
par->addParam("mijn_nieuwe_formule_scale", 2.0, 0.001, 100.0, morphAkima, paramStandard);
par->addParam("mijn_nieuwe_formule_rotation", CVector3(0.0, 0.0, 0.0), morphAkima, paramStandard);
par->addParam("mijn_nieuwe_formule_iterations", 10, 1, 250, morphLinear, paramStandard);
par->addParam("mijn_nieuwe_formule_enabled", true, morphLinear, paramStandard);
```

### Stap 4: Formula UI XML schrijven

**Bestand:** `mandelbulber2/deploy/share/mandelbulber2/formula/ui/mijn_nieuwe_formule.ui`

Dit is een **handgeschreven XML bestand** van ~300-500 regels:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>mijn_nieuwe_formule</class>
 <widget class="QWidget" name="Form">
  <property name="geometry">
   <rect><x>0</x><y>0</y><width>799</width><height>600</height></rect>
  </property>
  <layout class="QVBoxLayout" name="verticalLayout">
   <property name="spacing"><number>2</number></property>

   <!-- Titel -->
   <item>
    <widget class="QLabel" name="label_title">
     <property name="text">
      <string notr="true">Mijn Nieuwe Formule</string>
     </property>
    </widget>
   </item>

   <!-- Parameter Grid -->
   <item>
    <layout class="QGridLayout" name="gridLayout_params">
     <property name="spacing"><number>2</number></property>

     <!-- Scale parameter -->
     <item row="0" column="0">
      <widget class="QLabel" name="label_scale">
       <property name="text"><string>Scale:</string></property>
      </widget>
     </item>
     <item row="0" column="1">
      <widget class="MyDoubleSpinBox" name="spinboxd_mijn_nieuwe_formule_scale">
       <property name="decimals"><number>6</number></property>
       <property name="minimum"><double>0.001</double></property>
       <property name="maximum"><double>100.0</double></property>
       <property name="singleStep"><double>0.1</double></property>
       <property name="value"><double>2.0</double></property>
      </widget>
     </item>

     <!-- Rotation CVector3 (x,y,z) -->
     <item row="1" column="0">
      <widget class="QLabel" name="label_rotation">
       <property name="text"><string>Rotation:</string></property>
      </widget>
     </item>
     <item row="1" column="1">
      <layout class="QHBoxLayout" name="hLayout_rotation">
       <item>
        <widget class="MyDoubleSpinBox" name="spinboxd3_mijn_nieuwe_formule_rotation_x">
         <property name="decimals"><number>6</number></property>
         <property name="minimum"><double>-36000.0</double></property>
         <property name="maximum"><double>36000.0</double></property>
        </widget>
       </item>
       <item>
        <widget class="MyDoubleSpinBox" name="spinboxd3_mijn_nieuwe_formule_rotation_y">
         <property name="decimals"><number>6</number></property>
         <property name="minimum"><double>-36000.0</double></property>
         <property name="maximum"><double>36000.0</double></property>
        </widget>
       </item>
       <item>
        <widget class="MyDoubleSpinBox" name="spinboxd3_mijn_nieuwe_formule_rotation_z">
         <property name="decimals"><number>6</number></property>
         <property name="minimum"><double>-36000.0</double></property>
         <property name="maximum"><double>36000.0</double></property>
        </widget>
       </item>
      </layout>
     </item>

     <!-- Iterations (int) -->
     <item row="2" column="0">
      <widget class="QLabel" name="label_iterations">
       <property name="text"><string>Iterations:</string></property>
      </widget>
     </item>
     <item row="2" column="1">
      <widget class="MySpinBox" name="spinbox_mijn_nieuwe_formule_iterations">
       <property name="minimum"><number>1</number></property>
       <property name="maximum"><number>250</number></property>
       <property name="value"><number>10</number></property>
      </widget>
     </item>

     <!-- Enabled (bool/checkbox) -->
     <item row="3" column="0" colspan="2">
      <widget class="MyCheckBox" name="checkBox_mijn_nieuwe_formule_enabled">
       <property name="text"><string>Enable feature</string></property>
       <property name="checked"><bool>true</bool></property>
      </widget>
     </item>

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
  <customwidget>
   <class>MySpinBox</class>
   <extends>QSpinBox</extends>
   <header>my_spin_box.h</header>
  </customwidget>
  <customwidget>
   <class>MyCheckBox</class>
   <extends>QCheckBox</extends>
   <header>my_check_box.h</header>
  </customwidget>
 </customwidgets>
 <resources/>
 <connections/>
</ui>
```

**⚠️ CRITICAL:** De widget naam `spinboxd_mijn_nieuwe_formule_scale` MOET exact overeenkomen met de parameter naam `mijn_nieuwe_formule_scale` die je in `initparameters.cpp` hebt geregistreerd.

### Stap 5: Formule toevoegen aan de enum lijst

**Bestand:** `mandelbulber2/formula/definition/all_fractal_list.hpp`

Voeg je formule toe aan de enum en de factory lijst.

### Stap 6: Formule toevoegen aan het build systeem

**Bestand:** `mandelbulber2/formula/definition/all_fractal_definitions.h`

Include je nieuwe header.

### Stap 7: Rebuild

```bash
cd build
make -j$(nproc)
```

---

## 1.2 Problemen met de Huidige Workflow

| Probleem | Impact |
|----------|--------|
| **7+ bestanden** handmatig aanpassen | Foutgevoelig, tijdrovend |
| **XML handmatig schrijven** | 300-500 regels copy-paste, geen validatie |
| **Naam conventie is brittle** | Één typo in widget naam = parameter werkt niet |
| **Geen IDE support** | Qt Designer kan formula UI's niet openen zonder include pad hacks |
| **C++ struct + XML duplicatie** | Parameters worden 2x gedefinieerd (C++ en XML) |
| **Geen preview** | Je ziet de UI pas na rebuild |
| **Geen type checking** | Runtime fouten als widget namen niet matchen |

---

# DEEL 2: Hoe MyUiLoader Precies Werkt

## 2.1 Qt's QUiLoader Basis

Qt biedt `QUiLoader` uit de `QtUiTools` module. Dit is een runtime UI parser:

```cpp
#include <QtUiTools/QtUiTools>

QUiLoader loader;
QFile uiFile("myform.ui");
uiFile.open(QFile::ReadOnly);
QWidget *widget = loader.load(&uiFile);  // Parseert XML, maakt widgets aan
uiFile.close();
```

`QUiLoader` doet dit:
1. Leest het `.ui` XML bestand
2. Vindt `<widget class="QPushButton" ...>` tags
3. Roept `QUiLoader::createWidget("QPushButton", parent, name)` aan
4. Voor standaard Qt widgets: maakt het object aan via meta-object systeem
5. Voor custom widgets: **weet het niet wat te doen** → geeft `nullptr` of error

## 2.2 Het Probleem: Custom Widgets

Mandelbulber gebruikt **geen** standaard Qt spinboxes. Het gebruikt eigen widgets zoals `MyDoubleSpinBox` die extra features hebben:
- Rechtermuisklik context menu
- Popup slider
- Script animatie indicators
- Specifieke precision modes

In een `.ui` bestand worden deze gedeclareerd als:

```xml
<widget class="MyDoubleSpinBox" name="spinboxd_formula_scale">
```

De standaard `QUiLoader` herkent `MyDoubleSpinBox` niet. Het is geen standaard Qt class.

## 2.3 MyUiLoader: De Oplossing

**Bestanden:**
- `mandelbulber2/src/my_ui_loader.h`
- `mandelbulber2/src/my_ui_loader.cpp`

### Architectuur

```
QUiLoader (Qt base — weet alleen standaard Qt widgets)
    └── MyUiLoader (custom override — weet Mandelbulber widgets)
            └── createWidget(const QString &className, ...)
                    ├── "MyDoubleSpinBox" → new MyDoubleSpinBox(parent)
                    ├── "MySpinBox"       → new MySpinBox(parent)
                    ├── "MyCheckBox"      → new MyCheckBox(parent)
                    ├── ... etc
                    └── default: QUiLoader::createWidget(className, parent, name)
```

### De Code (uitgebreid)

```cpp
// my_ui_loader.h
#ifndef MANDELBULBER2_SRC_MY_UI_LOADER_H_
#define MANDELBULBER2_SRC_MY_UI_LOADER_H_

#include <QtUiTools/QtUiTools>

class MyUiLoader : public QUiLoader
{
    Q_OBJECT
public:
    MyUiLoader(QObject *parent = nullptr) : QUiLoader(parent) {}
    ~MyUiLoader() override;

    // DEZE methode wordt door Qt aangeroepen voor ELKE widget in het .ui bestand
    QWidget *createWidget(
        const QString &className, QWidget *parent = nullptr, 
        const QString &name = QString()) override;
};

#endif
```

```cpp
// my_ui_loader.cpp
#include "my_ui_loader.h"

// Include ALLE custom widgets die we moeten kunnen instantiëren
#include "qt/file_select_widget.h"
#include "qt/material_selector.h"
#include "qt/my_check_box.h"
#include "qt/my_color_button.h"
#include "qt/my_combo_box.h"
#include "qt/my_double_spin_box.h"
#include "qt/my_group_box.h"
#include "qt/my_line_edit.h"
#include "qt/my_spin_box.h"

MyUiLoader::~MyUiLoader() = default;

QWidget *MyUiLoader::createWidget(const QString &className, QWidget *parent, const QString &name)
{
    QWidget *widget;

    // ==== Mandelbulber Custom Widgets ====
    
    if (className == QString("MyLineEdit"))
    {
        widget = new MyLineEdit(parent);
        widget->setObjectName(name);
    }
    else if (className == QString("MySpinBox"))
    {
        widget = new MySpinBox(parent);
        widget->setObjectName(name);
    }
    else if (className == QString("MyDoubleSpinBox"))
    {
        widget = new MyDoubleSpinBox(parent);
        widget->setObjectName(name);
    }
    else if (className == QString("MyCheckBox"))
    {
        widget = new MyCheckBox(parent);
        widget->setObjectName(name);
    }
    else if (className == QString("MyGroupBox"))
    {
        widget = new MyGroupBox(parent);
        widget->setObjectName(name);
    }
    else if (className == QString("MyColorButton"))
    {
        widget = new MyColorButton(parent);
        widget->setObjectName(name);
    }
    else if (className == QString("FileSelectWidget"))
    {
        widget = new FileSelectWidget(parent);
        widget->setObjectName(name);
    }
    else if (className == QString("cMaterialSelector"))
    {
        widget = new cMaterialSelector(parent);
        widget->setObjectName(name);
    }
    else if (className == QString("MyComboBox"))
    {
        widget = new MyComboBox(parent);
        widget->setObjectName(name);
    }
    else
    {
        // ==== Fallback naar standaard Qt widgets ====
        // QPushButton, QLabel, QSlider, QDial, QGroupBox, etc.
        widget = QUiLoader::createWidget(className, parent, name);
    }
    return widget;
}
```

## 2.4 Runtime Loading Flow (Step-by-Step)

Wat er gebeurt als de gebruiker een formule selecteert in de combo box:

```cpp
// tab_fractal.cpp — slotChangedComboFractal()

// 1. Bepaal welke formule geselecteerd is
QString formulaName = newFractalList[index]->getInternalName();
//    → "mandelbox_fast"

// 2. Bepaal het .ui bestand pad
QString uiFilename = newFractalList[index]->getUiFilename();
//    → "/usr/share/mandelbulber2/formula/ui/mandelbox_fast.ui"

// 3. Maak de custom loader aan
MyUiLoader loader;

// 4. Open het .ui bestand
QFile uiFile(uiFilename);
uiFile.open(QFile::ReadOnly);

// 5. LAAD DE UI RUNTIME
//    Dit parseert het XML, roept createWidget() aan voor elke widget,
//    zet properties, maakt layouts aan, etc.
fractalWidget.reset(loader.load(&uiFile));

// 6. Sluit het bestand
uiFile.close();

// 7. Voeg de geladen widget toe aan het layout
QVBoxLayout *layout = ui->verticalLayout_fractal;
layout->addWidget(fractalWidget.get());

// 8. Verbind sliders met spinboxes (AutomatedWidgets)
automatedWidgets->ConnectSignalsForSlidersInWindow(fractalWidget.get());

// 9. Synchroniseer waarden uit parameter container naar widgets
SynchronizeInterfaceWindow(fractalWidget.get(), fractalParams->at(tabIndex), qInterface::write);
```

### Wat `loader.load()` intern doet:

```
1. XML parser leest het .ui bestand
2. Vindt <widget class="QWidget" name="Form"> (root widget)
3. Roept createWidget("QWidget", nullptr, "Form") aan
4. Vindt <layout class="QVBoxLayout" name="verticalLayout">
5. Vindt <widget class="QLabel" name="label_title">
   → createWidget("QLabel", Form, "label_title")
   → QUiLoader::createWidget("QLabel", ...) → new QLabel(Form)
6. Vindt <widget class="MyDoubleSpinBox" name="spinboxd_mandelbox_scale">
   → createWidget("MyDoubleSpinBox", Form, "spinboxd_mandelbox_scale")
   → MyUiLoader herkent dit! → new MyDoubleSpinBox(Form)
   → setObjectName("spinboxd_mandelbox_scale")
7. Zet properties: decimals=6, minimum=0.0, maximum=99.999, etc.
8. Herhaalt voor ALLE widgets in het bestand
9. Bouwt layout hierarchy op
10. Returnt de root QWidget pointer
```

## 2.5 Belangrijk: UI Bestanden zijn Runtime Data

De formula UI's worden **NIET** door `uic` gecompileerd. Ze zijn gewone XML bestanden die meegeleverd worden als data:

```cmake
# CMakeLists.txt
install(DIRECTORY ../formula DESTINATION "${SHARED_DIR}")
```

Dit betekent:
- ✅ Je kunt formula UI's aanpassen zonder te rebuilden
- ✅ Gebruikers kunnen custom formula UI's maken
- ❌ Geen compile-time type checking
- ❌ Trager dan gecompileerde UI (XML parsing)
- ❌ Fouten in XML worden pas runtime ontdekt

---

# DEEL 3: Hoe AutomatedWidgets Werkt

## 3.1 Het Probleem: Handmatige Signal/Slot Verbindingen

In een normale Qt applicatie moet je handmatig sliders en spinboxes verbinden:

```cpp
// Normale Qt code — veel werk!
connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), 
        slider, &QSlider::setValue);
```

Voor 472 formules met gemiddeld 10 parameters elk = **~5000 handmatige connects**. Onmogelijk.

## 3.2 De Oplossing: Conventie-gebaseerde Automatisering

Mandelbulber lost dit op met **naam conventies**. Als twee widgets dezelfde "parameter naam" hebben (alles na het eerste `_`), worden ze automatisch verbonden.

### Naam Conventie Parser

```cpp
// synchronize_interface.cpp — regel 739
void GetNameAndType(QString name, QString *parameterName, QString *type)
{
    int firstDashPosition = name.indexOf("_");
    *type = name.left(firstDashPosition);        // "spinboxd3" of "slider" of "dial"
    *parameterName = name.mid(firstDashPosition + 1);  // "mandelbox_scale"
}
```

Voorbeeld:
```
Widget naam: "spinboxd3_mandelbox_rotation_x"
                    ↑ eerste _ split hier
    type = "spinboxd3"
    parameterName = "mandelbox_rotation_x"

Widget naam: "slider_mandelbox_rotation"
    type = "slider"
    parameterName = "mandelbox_rotation"
```

### 3.3 Widget Type Mapping

| Widget Type Prefix | C++ Widget | Koppelt met | Data Flow |
|--------------------|-----------|-------------|-----------|
| `spinboxd_` | `MyDoubleSpinBox` | `dial_` | Dial → SpinBox (×100) |
| `spinboxd3_` | `MyDoubleSpinBox` (x3) | `dial3_` | Dial → SpinBox (×100) |
| `spinboxd4_` | `MyDoubleSpinBox` (x4) | `dial4_` | Dial → SpinBox (×100) |
| `spinbox3_` | `MyDoubleSpinBox` | `slider3_` | Slider → SpinBox (÷10^decimals) |
| `spinbox4_` | `MyDoubleSpinBox` | `slider4_` | Slider → SpinBox (÷10^decimals) |
| `spinbox_` | `QDoubleSpinBox` | `slider_` | Slider → SpinBox (÷10^decimals) |
| `spinboxInt_` | `QSpinBox` | `sliderInt_` | Slider → SpinBox (1:1) |
| `logedit_` | `QLineEdit` | `logslider_` | Logaritmische schaal |
| `logvect3_` | `QLineEdit` (x3) | `logslidervect3_` | Logaritmische vector |
| `edit_` | `QLineEdit` | — | Direct |
| `vect3_` | `QLineEdit` (x3) | — | CVector3 |
| `vect4_` | `QLineEdit` (x4) | — | CVector4 |

### 3.4 De ConnectSignalsForSlidersInWindow() Methode

Dit is de kern van het AutomatedWidgets systeem. Het scant ALLE widgets in een window en maakt verbindingen op basis van namen.

```cpp
// automated_widgets.cpp — regel 454
void cAutomatedWidgets::ConnectSignalsForSlidersInWindow(QWidget *window) const
{
    // ==== STAP 1: Vind alle QSliders in het window ====
    QList<QSlider *> widgetList = window->findChildren<QSlider *>();
    
    for (auto &it : widgetList)
    {
        QString name = it->objectName();
        
        // Alleen verwerken als het een "echte" QSlider is (niet subclass)
        if (name.length() > 1 && it->metaObject()->className() == QString("QSlider"))
        {
            const QSlider *slider = it;
            
            QString type;
            QString parameterName;
            GetNameAndType(name, &parameterName, &type);
            
            // ==== TYPE: "slider" (normale double slider) ====
            if (type == QString("slider"))
            {
                // Verbind slider moved → spinbox update
                connect(slider, SIGNAL(sliderMoved(int)), 
                        this, SLOT(slotSliderMoved(int)));
                
                // Vind de bijbehorende spinbox
                const QString spinBoxName = QString("spinbox_") + parameterName;
                QDoubleSpinBox *spinBox = 
                    slider->parent()->findChild<QDoubleSpinBox *>(spinBoxName);
                
                if (spinBox)
                {
                    // Verbind spinbox changed → slider update
                    connect(spinBox, SIGNAL(valueChanged(double)), 
                            this, SLOT(slotDoubleSpinBoxChanged(double)));
                }
                else
                {
                    qWarning() << "ConnectSignalsForSlidersInWindow() error: spinbox " 
                               << spinBoxName << " doesn't exists";
                }
            }
            
            // ==== TYPE: "sliderInt" (integer slider) ====
            else if (type == QString("sliderInt"))
            {
                connect(slider, SIGNAL(sliderMoved(int)), 
                        this, SLOT(slotIntSliderMoved(int)));
                
                const QString spinboxName = QString("spinboxInt_") + parameterName;
                QSpinBox *spinbox = slider->parent()->findChild<QSpinBox *>(spinboxName);
                
                if (spinbox)
                {
                    connect(spinbox, SIGNAL(valueChanged(int)), 
                            this, SLOT(slotIntSpinBoxChanged(int)));
                }
            }
            
            // ==== TYPE: "slider3" (CVector3 slider) ====
            else if (type == QString("slider3"))
            {
                connect(slider, SIGNAL(sliderMoved(int)), 
                        this, SLOT(slotSlider3Moved(int)));
                
                const QString spinboxName = QString("spinbox3_") + parameterName;
                QDoubleSpinBox *spinbox = 
                    slider->parent()->findChild<QDoubleSpinBox *>(spinboxName);
                
                if (spinbox)
                {
                    connect(spinbox, SIGNAL(valueChanged(double)), 
                            this, SLOT(slotSpinBox3Changed(double)));
                }
            }
            
            // ... soortgelijk voor slider4, logslider, logslidervect3
        }
    }
    
    // ==== STAP 2: Vind alle QDials in het window ====
    QList<QDial *> widgetList2 = window->findChildren<QDial *>(QString());
    
    for (auto &it2 : widgetList2)
    {
        QString name = it2->objectName();
        
        if (name.length() > 1 && it2->metaObject()->className() == QString("QDial"))
        {
            const QDial *dial = it2;
            QString type;
            QString parameterName;
            GetNameAndType(name, &parameterName, &type);
            
            // ==== TYPE: "dial3" (CVector3 dial) ====
            if (type == QString("dial3"))
            {
                connect(dial, SIGNAL(valueChanged(int)), 
                        this, SLOT(slotDial3Moved(int)));
                
                const QString spinBoxName = QString("spinboxd3_") + parameterName;
                QDoubleSpinBox *spinBox = 
                    dial->parent()->findChild<QDoubleSpinBox *>(spinBoxName);
                
                if (spinBox)
                {
                    connect(spinBox, SIGNAL(valueChanged(double)), 
                            this, SLOT(slotSpinBoxD3Changed(double)));
                }
            }
            
            // ... soortgelijk voor dial4, dial
        }
    }
}
```

## 3.5 Hoe De Slots Werken (Data Conversie)

### Voorbeeld: `slotSliderMoved` → Slider → SpinBox

```cpp
void cAutomatedWidgets::slotSliderMoved(int value) const
{
    // 1. Wie heeft dit signaal gestuurd?
    const QString sliderName = sender()->objectName();
    //    → "slider_mandelbox_scale"
    
    // 2. Parse de naam
    QString type;
    QString parameterName;
    GetNameAndType(sliderName, &parameterName, &type);
    //    type = "slider"
    //    parameterName = "mandelbox_scale"
    
    // 3. Bouw de spinbox naam
    const QString spinBoxName = QString("spinbox_") + parameterName;
    //    → "spinbox_mandelbox_scale"
    
    // 4. Zoek de spinbox in dezelfde parent widget
    QDoubleSpinBox *spinBox = 
        sender()->parent()->findChild<QDoubleSpinBox *>(spinBoxName);
    
    if (spinBox)
    {
        // 5. Converteer slider int → spinbox double
        //    Slider value = double_value × 10^decimals
        //    Bijv: slider=123456, decimals=3 → spinbox=123.456
        const double decimals = spinBox->decimals();  // bijv. 3
        const double divider = pow(10.0, decimals);   // 1000.0
        spinBox->setValue(value / divider);           // 123.456
    }
}
```

### Voorbeeld: `slotDoubleSpinBoxChanged` → SpinBox → Slider

```cpp
void cAutomatedWidgets::slotDoubleSpinBoxChanged(double value) const
{
    const QString spinBoxName = sender()->objectName();
    //    → "spinbox_mandelbox_scale"
    
    QString type;
    QString parameterName;
    GetNameAndType(spinBoxName, &parameterName, &type);
    
    const QString sliderName = QString("slider_") + parameterName;
    //    → "slider_mandelbox_scale"
    
    QSlider *slider = sender()->parent()->findChild<QSlider *>(sliderName);
    
    if (slider)
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox *>(sender());
        const double decimals = spinBox->decimals();    // 3
        const double multiplier = pow(10.0, decimals);  // 1000.0
        slider->setValue(int(value * multiplier));      // 123456
    }
}
```

### Voorbeeld: `slotDial3Moved` → Dial → CVector3 SpinBox

```cpp
void cAutomatedWidgets::slotDial3Moved(int value) const
{
    const QString sliderName = sender()->objectName();
    //    → "dial3_mandelbox_rotation"
    
    QString type;
    QString parameterName;
    GetNameAndType(sliderName, &parameterName, &type);
    //    parameterName = "mandelbox_rotation"
    
    const QString spinBoxName = QString("spinboxd3_") + parameterName;
    //    → "spinboxd3_mandelbox_rotation"
    
    QDoubleSpinBox *spinBox = 
        sender()->parent()->findChild<QDoubleSpinBox *>(spinBoxName);
    
    if (spinBox)
    {
        // Dial waarde 0-10000 → spinbox waarde 0.0-100.0
        spinBox->setValue(value / 100.0);
    }
}
```

## 3.6 Samenvatting AutomatedWidgets

```
┌─────────────────────────────────────────────────────────────┐
│           ConnectSignalsForSlidersInWindow()                │
│                     (eenmalig bij laden)                    │
└─────────────────────────────────────────────────────────────┘
                              │
              ┌───────────────┼───────────────┐
              ▼               ▼               ▼
        findChildren     findChildren    findChildren
        <QSlider*>       <QDial*>        <QDial*>
              │               │               │
              ▼               ▼               ▼
        Parse naam:      Parse naam:     Parse naam:
        type + param     type + param    type + param
              │               │               │
              ▼               ▼               ▼
        Connect signal   Connect signal  Connect signal
        naar eigen slot  naar eigen slot naar eigen slot
              │               │               │
              ▼               ▼               ▼
        Zoek partner     Zoek partner    Zoek partner
        widget (spinbox) widget          widget
              │               │               │
              ▼               ▼               ▼
        Connect partner  Connect partner Connect partner
        signal terug     signal terug    signal terug
```

---

# DEEL 4: Verbeteringsvoorstellen

## 4.1 Overzicht van Problemen en Oplossingen

| # | Probleem | Huidige Status | Verbetering | Moeilijkheid |
|---|----------|---------------|-------------|-------------|
| 1 | Handmatig XML schrijven | 300-500 regels per formule | **JSON/YAML parameter definitie** → auto-generate UI | Laag |
| 2 | Naam conventie fouten | Runtime warnings, stille failures | **UI Validator tool** | Laag |
| 3 | Geen preview zonder rebuild | Moet app herstarten | **Live UI herlader** (watch file) | Laag |
| 4 | Parameters 2x definiëren | C++ struct + XML | **Single source of truth** (JSON → beide) | Medium |
| 5 | Geen IDE support | XML met custom widgets | **Qt Designer plugin** voor custom widgets | Medium |
| 6 | Geen type checking | Runtime fouten | **Compile-time UI validator** | Medium |
| 7 | 7+ bestanden per formule | Verspreid over codebase | **Formule template generator** | Laag |

---

## 4.2 Verbetering 1: JSON/YAML Parameter Definitie (Single Source of Truth)

### Het Idee

In plaats van handmatig XML te schrijven, definieer je parameters in een simpel formaat. Een tool genereert dan:
- De `.ui` XML
- De C++ parameter registratie code
- De C++ struct definitie

### Voorbeeld: `formula_params.json`

```json
{
  "formula": {
    "internal_name": "mijn_nieuwe_formule",
    "display_name": "Mijn Nieuwe Formule",
    "category": "transform",
    "de_type": "analytic",
    "cpixel_addition": "enabled_by_default",
    "default_bailout": 100.0
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
      "max": 36000.0,
      "step": 1.0,
      "decimals": 6
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

### Wat de Tool Genereert

**A. `.ui` bestand** (automatisch)
```bash
python3 generate_formula_ui.py --input mijn_nieuwe_formule.json
# → mandelbulber2/deploy/share/mandelbulber2/formula/ui/mijn_nieuwe_formule.ui
```

**B. C++ parameter registratie** (automatisch)
```cpp
// auto_generated_params.cpp
par->addParam("mijn_nieuwe_formule_scale", 2.0, 0.001, 100.0, morphAkima, paramStandard);
par->addParam("mijn_nieuwe_formule_rotation", CVector3(0.0, 0.0, 0.0), morphAkima, paramStandard);
par->addParam("mijn_nieuwe_formule_iterations", 10, 1, 250, morphLinear, paramStandard);
par->addParam("mijn_nieuwe_formule_enabled", true, morphLinear, paramStandard);
```

**C. C++ struct** (automatisch)
```cpp
// auto_generated_structs.hpp
struct sMijnNieuweFormule
{
    double scale;
    CVector3 rotation;
    int iterations;
    bool enabled;
};
```

### Bestaande Tool Uitbreiden

De huidige `dev_tools/ui_generator.py` doet dit al gedeeltelijk. Verbeteringen:

1. **JSON/YAML input** in plaats van interactief
2. **Meer types**: `CVector4`, `enum`, `color`, `file`
3. **Validatie**: check of parameter namen uniek zijn
4. **Batch mode**: alle formules in één keer
5. **Diff detectie**: alleen regenereren als JSON gewijzigd

---

## 4.3 Verbetering 2: UI Validator Tool

### Het Probleem

Een typo in de widget naam = stille failure:
```xml
<!-- FOUT: "spinboxd_mijn_nieuw_formule_scale" (mist 'e') -->
<widget class="MyDoubleSpinBox" name="spinboxd_mijn_nieuw_formule_scale">
```

De parameter `mijn_nieuwe_formule_scale` wordt nooit gesynchroniseerd. Geen error, geen warning (behalve misschien een qWarning in de log).

### De Oplossing

Een validator tool die checkt:

```bash
python3 validate_formula_ui.py mandelbox_fast.ui

Checking: mandelbox_fast.ui
✓ File exists
✓ Valid XML structure
✓ Root widget is QWidget
✓ Custom widgets declared: MyDoubleSpinBox, MySpinBox, MyCheckBox
✓ Widget naming convention:
  ✓ spinboxd_mandelbox_folding_min_radius → valid
  ✓ spinboxd3_mandelbox_rotation_x → valid
  ✓ checkBox_mandelbox_main_rotation_enabled → valid
⚠ Warning: widget "label_11" has no corresponding parameter
✓ All referenced parameters exist in parameter container
✓ All MyDoubleSpinBox widgets have decimals/min/max set
✓ All CVector3 widgets have x/y/z variants

Result: PASSED (1 warning)
```

### Validatie Regels

| Regel | Ernst | Beschrijving |
|-------|-------|-------------|
| Valid XML | ERROR | Bestand moet geldig XML zijn |
| Widget type prefix | ERROR | `spinboxd_`, `checkBox_`, etc. moet geldig zijn |
| Parameter bestaat | ERROR | Parameter naam moet in `cParameterContainer` geregistreerd zijn |
| CVector3 compleet | ERROR | Als `_x` bestaat, moeten `_y` en `_z` ook bestaan |
| CVector4 compleet | ERROR | Als `_x` bestaat, moeten `_y`, `_z`, `_w` ook bestaan |
| MyDoubleSpinBox props | WARNING | `decimals`, `minimum`, `maximum` moeten gezet zijn |
| Lege labels | WARNING | `QLabel` widgets moeten text hebben |
| Ongebruikte widgets | INFO | Widgets die geen parameter updaten |

---

## 4.4 Verbetering 3: Live UI Herlader (File Watcher)

### Het Probleem

Je bewerkt een `.ui` bestand, maar moet Mandelbulber herstarten om het resultaat te zien.

### De Oplossing

Een **file watcher** in `tab_fractal.cpp` die `.ui` bestanden in de gaten houdt:

```cpp
// In cTabFractal constructor
QFileSystemWatcher *uiWatcher = new QFileSystemWatcher(this);
connect(uiWatcher, &QFileSystemWatcher::fileChanged,
        this, &cTabFractal::slotReloadFormulaUi);
```

Wanneer het bestand wijzigt:
```cpp
void cTabFractal::slotReloadFormulaUi()
{
    // 1. Verwijder oude widget
    if (fractalWidget)
    {
        ui->verticalLayout_fractal->removeWidget(fractalWidget.get());
        fractalWidget.reset();
    }
    
    // 2. Herlaad UI
    MyUiLoader loader;
    QFile uiFile(currentUiFilename);
    uiFile.open(QFile::ReadOnly);
    fractalWidget.reset(loader.load(&uiFile));
    uiFile.close();
    
    // 3. Voeg toe en synchroniseer
    ui->verticalLayout_fractal->addWidget(fractalWidget.get());
    automatedWidgets->ConnectSignalsForSlidersInWindow(fractalWidget.get());
    SynchronizeInterfaceWindow(fractalWidget.get(), ...);
    
    // 4. Toon melding
    qDebug() << "Formula UI reloaded: " << currentUiFilename;
}
```

### Gebruik

```bash
# Terminal 1: Start Mandelbulber
./mandelbulber2

# Terminal 2: Bewerk UI
nano mandelbulber2/deploy/share/mandelbulber2/formula/ui/mandelbox_fast.ui

# Mandelbulber herlaadt automatisch de UI bij het wisselen van tab!
```

---

## 4.5 Verbetering 4: Enhanced ui_generator.py (Volledige Formule Generator)

### Nieuwe Functionaliteit

```bash
# 1. Genereer een complete formule vanuit template
python3 dev_tools/formula_generator.py new \
  --name "mijn_nieuwe_formule" \
  --display "Mijn Nieuwe Formule" \
  --type transform \
  --params params.json

# Output:
# ✓ Created: formula/definition/fractal_mijn_nieuwe_formule.cpp
# ✓ Created: deploy/share/mandelbulber2/formula/ui/mijn_nieuwe_formule.ui
# ✓ Updated: formula/definition/all_fractal_list.hpp (enum + factory)
# ✓ Updated: src/initparameters.cpp (parameter registration)
# ✓ Updated: src/fractparams.hpp (struct)
# ✓ Created: formula/opencl/mijn_nieuwe_formule.cl (OpenCL stub)
# 
# Next steps:
# 1. Implement FormulaCode() in fractal_mijn_nieuwe_formule.cpp
# 2. Build: make -j$(nproc)
```

### Wat de Tool Genereert

**A. Formule C++ Template:**
```cpp
cFractalMijnNieuweFormule::cFractalMijnNieuweFormule() : cAbstractFractal()
{
    nameInComboBox = "Mijn Nieuwe Formule";
    internalName = "mijn_nieuwe_formule";
    internalID = fractal::mijnNieuweFormule;
    DEType = analyticDEType;
    // ...
}

void cFractalMijnNieuweFormule::FormulaCode(CVector4 &z, 
    const sFractal *fractal, sExtendedAux &aux)
{
    // TODO: Implement your formula here
    // Available parameters:
    //   fractal->mijnNieuweFormule.scale (double)
    //   fractal->mijnNieuweFormule.rotation (CVector3)
    //   fractal->mijnNieuweFormule.iterations (int)
    //   fractal->mijnNieuweFormule.enabled (bool)
}
```

**B. UI XML (automatisch):**
```xml
<!-- Auto-generated from params.json -->
<!-- DO NOT EDIT - Regenerate with: python3 formula_generator.py -->
```

**C. OpenCL Stub (GPU versie):**
```opencl
// formula/opencl/mijn_nieuwe_formule.cl
// TODO: Implement OpenCL version
```

---

## 4.6 Verbetering 5: Qt Designer Plugin voor Custom Widgets

### Het Probleem

Je kunt `dock_fractal.ui` openen in Qt Designer, maar niet formula UI's omdat Qt Designer `MyDoubleSpinBox` niet kent.

### De Oplossing

Een **Qt Designer Custom Widget Plugin**:

```cpp
// designer_plugins/mandelbulber_widgets_plugin.cpp
#include <QtDesigner/QtDesigner>

class MyDoubleSpinBoxPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
    QString name() const override { return "MyDoubleSpinBox"; }
    QString group() const override { return "Mandelbulber Widgets"; }
    QWidget *createWidget(QWidget *parent) override { return new MyDoubleSpinBox(parent); }
    // ...
};
```

### Installatie

```bash
# Build plugin
qmake designer_plugins/mandelbulber_widgets.pro
make

# Install to Qt Designer plugins directory
sudo cp libmandelbulber_widgets.so /usr/lib/qt5/plugins/designer/

# Nu kun je formula UI's direct in Qt Designer bewerken!
```

---

## 4.7 Verbetering 6: UI Preview Tool (Standalone)

Een kleine standalone app om formula UI's te previewen zonder Mandelbulber te starten:

```cpp
// tools/ui_preview/main.cpp
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    MyUiLoader loader;
    QFile uiFile(argv[1]);
    uiFile.open(QFile::ReadOnly);
    QWidget *widget = loader.load(&uiFile);
    uiFile.close();
    
    widget->show();
    return app.exec();
}
```

### Gebruik

```bash
./ui_preview mandelbulber2/deploy/share/mandelbulber2/formula/ui/mandelbox_fast.ui
# Toont de UI in een standalone venster
```

---

## 4.8 Prioriteit Matrix

| Verbetering | Impact | Moeilijkheid | Prioriteit |
|-------------|--------|-------------|------------|
| **UI Validator** | Hoog | Laag | ⭐⭐⭐ Eerste |
| **JSON Parameter Def** | Hoog | Laag | ⭐⭐⭐ Tweede |
| **Live UI Herlader** | Medium | Laag | ⭐⭐ Derde |
| **Formule Generator** | Hoog | Medium | ⭐⭐ Vierde |
| **UI Preview Tool** | Medium | Laag | ⭐⭐ Vijfde |
| **Designer Plugin** | Medium | Medium | ⭐ Zesde |

---

## 4.9 Direct Uitvoerbare Verbeteringen (vandaag)

### A. Verbeter `ui_generator.py`

```python
# dev_tools/ui_generator_v2.py
import json
import sys
from pathlib import Path

def generate_from_json(json_file):
    with open(json_file) as f:
        spec = json.load(f)
    
    # Generate .ui
    generate_ui(spec)
    
    # Generate C++ registration code
    generate_cpp_registration(spec)
    
    # Generate C++ struct
    generate_cpp_struct(spec)
    
    # Validate
    validate_ui(spec)

if __name__ == "__main__":
    generate_from_json(sys.argv[1])
```

### B. Maak `validate_ui.py`

```python
#!/usr/bin/env python3
"""Validates a Mandelbulber formula .ui file"""

import xml.etree.ElementTree as ET
import sys

def validate_ui_file(filepath):
    errors = []
    warnings = []
    
    # Parse XML
    try:
        tree = ET.parse(filepath)
    except ET.ParseError as e:
        errors.append(f"Invalid XML: {e}")
        return errors, warnings
    
    root = tree.getroot()
    
    # Find all widgets
    widgets = root.findall('.//widget')
    names = [w.get('name') for w in widgets]
    
    # Check naming conventions
    valid_prefixes = ['spinbox', 'spinboxd', 'spinboxd3', 'spinboxd4',
                      'spinbox3', 'spinbox4', 'spinboxInt',
                      'checkBox', 'comboBox', 'colorButton',
                      'label', 'groupBox', 'slider', 'dial',
                      'logslider', 'logedit', 'logvect3']
    
    for name in names:
        if not name or name == 'Form':
            continue
        prefix = name.split('_')[0] if '_' in name else name
        if prefix not in valid_prefixes:
            warnings.append(f"Unknown prefix: '{prefix}' in '{name}'")
    
    # Check CVector3 completeness
    d3_widgets = [n for n in names if 'spinboxd3_' in n or 'spinbox3_' in n]
    d3_bases = set('_'.join(n.split('_')[:-1]) for n in d3_widgets)
    for base in d3_bases:
        for axis in ['x', 'y', 'z']:
            if f"{base}_{axis}" not in names:
                errors.append(f"Missing CVector3 axis: {base}_{axis}")
    
    # Check MyDoubleSpinBox has properties
    for widget in widgets:
        if widget.get('class') == 'MyDoubleSpinBox':
            props = widget.findall('.//property')
            prop_names = [p.get('name') for p in props]
            if 'decimals' not in prop_names:
                warnings.append(f"MyDoubleSpinBox {widget.get('name')} missing 'decimals'")
    
    return errors, warnings

if __name__ == "__main__":
    errors, warnings = validate_ui_file(sys.argv[1])
    
    for e in errors:
        print(f"❌ ERROR: {e}")
    for w in warnings:
        print(f"⚠️  WARNING: {w}")
    
    if not errors and not warnings:
        print("✅ All checks passed!")
    
    sys.exit(1 if errors else 0)
```

---

*Document gegenereerd op: 2026-04-21*
*Gebaseerd op analyse van mandelbulber2_v2_experiment codebase*

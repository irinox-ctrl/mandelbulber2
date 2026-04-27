# MANDELBULBER2 AUTOMATED WIDGETS: Nucleaire Diepte-Audit

**Datum**: 2026-04-22  
**Bestanden**: `automated_widgets.hpp/cpp`, `synchronize_interface.hpp/cpp`, `render_window.cpp`  
**Scope**: UI↔Parameter binding, widget naming conventies, bidirectionele synchronisatie, vector component handling, logarithmische schalen

---

## INHOUDSOPGAVE

1. [Architectuur-Overzicht](#1-architectuur-overzicht)
2. [Widget Naming Conventie](#2-widget-naming-conventie)
3. [cAutomatedWidgets — Bidirectionele Slider↔SpinBox Sync](#3-cautomatedwidgets--bidirectionele-sliderspinbox-sync)
4. [synchronize_interface.cpp — UI↔Parameter Sync](#4-synchronize_interfacecpp--uiparameter-sync)
5. [Vector Component Handling](#5-vector-component-handling)
6. [Logaritmische Schalen](#6-logaritmische-schalen)
7. [Dial Widgets](#7-dial-widgets)
8. [Bugs & Riskante Code](#8-bugs--riskante-code)
9. [Uitbreiding Recipe: Nieuw Widget Type Toevoegen](#9-uitbreiding-recipe-nieuw-widget-type-toevoegen)

---

## 1. Architectuur-Overzicht

Het UI-systeem heeft een **tweelaags synchronisatie**:

```
┌─────────────────────────────────────────────────────────────┐
│                    GEBRUIKER INTERACTIE                      │
│  (klikt/sleept/typt in widgets)                             │
└──────────────────┬──────────────────────────────────────────┘
                   │
         ┌─────────▼──────────┐
         │ cAutomatedWidgets  │  ← Slider↔SpinBox/Dial binding
         │ (automated_widgets)│    (directe UI↔UI sync)
         └─────────┬──────────┘
                   │
         ┌─────────▼──────────────────────────┐
         │ synchronize_interface.cpp          │  ← UI↔Parameter binding
         │ (SynchronizeInterfaceWindow)       │    (batch read/write)
         └─────────┬──────────────────────────┘
                   │
         ┌─────────▼──────────┐
         │ cParameterContainer│  ← Centrale parameter opslag
         │ (parameters.hpp)   │
         └────────────────────┘
```

**Laag 1** (`cAutomatedWidgets`): Real-time bidirectionele synchronisatie tussen **gerelateerde UI widgets** (slider ↔ spinbox, dial ↔ spinbox, logslider ↔ lineEdit).

**Laag 2** (`synchronize_interface`): Batch-synchronisatie tussen **alle UI widgets** en de `cParameterContainer`. Wordt aangeroepen bij:
- Knop indrukken (render, save)
- Undo/restore
- Script evaluatie
- Animatie frame wissel

---

## 2. Widget Naming Conventie

De **hele binding** is gebaseerd op **string parsing van objectName**. Dit is de kern van het architectuurontwerp.

```
objectName = "<type>_<parameterName>"
```

| Type | Widget Class | Gekoppeld aan | Gebruik |
|------|-------------|---------------|---------|
| `slider` | QSlider | `spinbox_*` | Double waarde met decimal scaling |
| `sliderInt` | QSlider | `spinboxInt_*` | Integer waarde (1:1) |
| `slider3` | QSlider | `spinbox3_*` | Vector3 component (x/y/z suffix) |
| `slider4` | QSlider | `spinbox4_*` | Vector4 component (x/y/z/w suffix) |
| `logslider` | QSlider | `logedit_*` | Logaritmische schaal |
| `logslidervect3` | QSlider | `logvect3_*` | Logaritmische vector3 |
| `dial` | QDial | `spinboxd_*` | Knop met /100 scaling |
| `dial3` | QDial | `spinboxd3_*` | Knop vector3 |
| `dial4` | QDial | `spinboxd4_*` | Knop vector4 |
| `spinbox` | QDoubleSpinBox | `slider_*` | Double spinbox |
| `spinboxInt` | QSpinBox | `sliderInt_*` | Integer spinbox |
| `spinbox3` | QDoubleSpinBox | `slider3_*` | Vector3 spinbox |
| `spinbox4` | QDoubleSpinBox | `slider4_*` | Vector4 spinbox |
| `spinboxd` | QDoubleSpinBox | `dial_*` | Dial spinbox |
| `spinboxd3` | QDoubleSpinBox | `dial3_*` | Dial vector3 |
| `spinboxd4` | QDoubleSpinBox | `dial4_*` | Dial vector4 |
| `edit` | QLineEdit | — | Directe double/string input |
| `logedit` | QLineEdit | `logslider_*` | Logaritmische input |
| `logvect3` | QLineEdit | `logslidervect3_*` | Logaritmische vector3 |
| `vect3` | QLineEdit (×3) | — | 3D vector componenten |
| `vect4` | QLineEdit (×4) | — | 4D vector componenten |
| `checkBox` | QCheckBox | — | Boolean |
| `groupCheck` | QGroupBox | — | Boolean (checkable group) |
| `comboBox` | QComboBox | — | Enum/index selectie |
| `text` | QLineEdit | — | String |
| `textEdit` | QTextEdit | — | Multi-line string |
| `colorpalette` | cGradientEditWidget | — | Kleurverloop |
| `keySequenceEdit` | QKeySequenceEdit | — | Toetsencombinatie |
| `materialselector` | cMaterialSelector | — | Materiaal index |

### Voorbeeld: Camera X-positie

```
slider_camera_x        → QSlider (integer, geschaald)
spinbox_camera_x       → QDoubleSpinBox (double waarde)
```

De parameter naam is `camera_x`, en `synchronize_interface.cpp` ziet de `x` suffix en weet dat dit een `CVector3 camera` component is.

### GetNameAndType (synchronize_interface.cpp:739)

```cpp
void GetNameAndType(QString name, QString *parameterName, QString *type) {
    int firstDashPosition = name.indexOf("_");
    *type = name.left(firstDashPosition);           // Alles voor eerste '_'
    *parameterName = name.mid(firstDashPosition + 1); // Alles na eerste '_'
}
```

**Kritiek**: Dit is een eenvoudige string split op de **eerste** underscore. De parameter naam mag zelf geen underscores bevatten in de prefix, maar mag ze wel in de rest van de naam hebben.

---

## 3. cAutomatedWidgets — Bidirectionele Slider↔SpinBox Sync

### 3.1 Double Slider (lineair)

**Slider → SpinBox** (`slotSliderMoved`):
```cpp
const double decimals = spinBox->decimals();
const double divider = pow(10.0, decimals);
spinBox->setValue(value / divider);
```

**SpinBox → Slider** (`slotDoubleSpinBoxChanged`):
```cpp
const double decimals = spinBox->decimals();
const double multiplier = pow(10.0, decimals);
slider->setValue(int(value * multiplier));
```

| Decimals | Slider range | SpinBox range | Resolutie |
|----------|-------------|---------------|-----------|
| 0 | 0-100 | 0.0-100.0 | 1.0 |
| 1 | 0-1000 | 0.0-100.0 | 0.1 |
| 2 | 0-10000 | 0.0-100.0 | 0.01 |
| 6 | 0-10^8 | 0.0-100.0 | 0.000001 |

**Signaalkeuze**: Er wordt expres `sliderMoved` (alleen bij gebruikers-interactie) gebruikt in plaats van `valueChanged` (ook bij programmatische updates), om **feedback loops** te voorkomen tijdens batch-synchronisatie.

### 3.2 Integer Slider

```cpp
// slotIntSliderMoved
spinbox->setValue(value);  // 1:1 mapping, geen scaling

// slotIntSpinBoxChanged
slider->setValue(value);   // 1:1 mapping
```

### 3.3 Vector3/Vector4 Sliders

```cpp
// slotSlider3Moved → spinbox3_camera_x
const double decimals = spinBox->decimals();
const double divider = pow(10.0, decimals);
spinBox->setValue(value / divider);
```

Dit is identiek aan de standaard double slider. Het verschil zit in `synchronize_interface.cpp` die de `x`/`y`/`z` suffix detecteert en de component in een `CVector3` object plaatst.

---

## 4. synchronize_interface.cpp — UI↔Parameter Sync

### 4.1 Batch Synchronisatie

```cpp
void SynchronizeInterfaceWindow(QWidget *window, 
    std::shared_ptr<cParameterContainer> par, qInterface::enumReadWrite mode) {
    
    if (!gInterfaceReadyForSynchronization && mode == qInterface::read) return;
    
    SynchronizeInterfaceQLineEdit(window->findChildren<QLineEdit *>(), par, mode);
    SynchronizeInterfaceQDoubleSpinBox(window->findChildren<QDoubleSpinBox *>(), par, mode);
    SynchronizeInterfaceQSpinBox(window->findChildren<QSpinBox *>(), par, mode);
    SynchronizeInterfaceQCheckBox(window->findChildren<QCheckBox *>(), par, mode);
    SynchronizeInterfaceQGroupBox(window->findChildren<QGroupBox *>(), par, mode);
    SynchronizeInterfaceFileSelectWidget(...);
    SynchronizeInterfaceMyColorButton(...);
    SynchronizeInterfaceColorGradientWidget(...);
    SynchronizeInterfaceQComboBox(...);
    SynchronizeInterfaceMaterialSelector(...);
    SynchronizeInterfaceQPlainTextEdit(...);
    SynchronizeInterfaceQTextEdit(...);
    SynchronizeInterfaceLightWidget(...);
    SynchronizeInterfaceQKeySequenceEdit(...);
}
```

### 4.2 Read Mode (UI → ParameterContainer)

Leest de huidige waarde uit elk widget en schrijft naar `cParameterContainer`:

```cpp
// Voor QDoubleSpinBox
if (mode == qInterface::read) {
    double value = spinbox->value();
    par->Set(props.paramName, value);
}
```

### 4.3 Write Mode (ParameterContainer → UI)

Leest de waarde uit `cParameterContainer` en schrijft naar widgets:

```cpp
// Voor QDoubleSpinBox
else if (mode == qInterface::write) {
    double value = par->Get<double>(props.paramName);
    spinbox->setValue(value);
}
```

### 4.4 Focus Guard

```cpp
if (spinbox->hasFocus() && mode == qInterface::write) continue;
```

Als een widget focus heeft, wordt het **niet overschreven** bij write-mode. Dit voorkomt dat de gebruiker zijn ingetypte waarde verliest tijdens een automatische refresh.

---

## 5. Vector Component Handling

### 5.1 Vector3 Synchronisatie

**Read** (UI → Parameter):
```cpp
void SynchronizeInterfaceReadVect3d(QString &nameVect, char lastChar, 
                                     double value, std::shared_ptr<cParameterContainer> par) {
    CVector3 vect = par->Get<CVector3>(nameVect);
    switch (lastChar) {
        case 'x': vect.x = value; break;
        case 'y': vect.y = value; break;
        case 'z': vect.z = value; break;
        default: qWarning() << "wrong axis name"; break;
    }
    par->Set(nameVect, vect);
}
```

**Write** (Parameter → UI):
```cpp
void SynchronizeInterfaceWriteVect3d(QString &nameVect, char lastChar, 
                                      double &out, std::shared_ptr<cParameterContainer> par) {
    CVector3 vect = par->Get<CVector3>(nameVect);
    switch (lastChar) {
        case 'x': out = vect.x; break;
        case 'y': out = vect.y; break;
        case 'z': out = vect.z; break;
        default: qWarning() << "wrong axis name"; break;
    }
}
```

**Probleem**: De hele vector wordt gelezen en teruggeschreven voor **elke component**. Bij een Vector3 met `camera_x`, `camera_y`, `camera_z` worden er 3 reads en 3 writes gedaan. De read-modify-write is niet atomisch.

### 5.2 Vector4 Synchronisatie

Identiek aan Vector3, maar met extra `case 'w':`.

---

## 6. Logaritmische Schalen

### 6.1 Slider → LineEdit

```cpp
void cAutomatedWidgets::slotLogSliderMoved(int value) const {
    const double dValue = pow(10.0, value / 100.0);
    const QString text = QString("%L1").arg(dValue);
    lineEdit->setText(text);
}
```

| Slider Value | Output |
|-------------|--------|
| -200 | 10⁻² = 0.01 |
| -100 | 10⁻¹ = 0.1 |
| 0 | 10⁰ = 1.0 |
| 100 | 10¹ = 10.0 |
| 200 | 10² = 100.0 |
| 400 | 10⁴ = 10000.0 |

**Resolutie**: 0.01 log-eenheden per slider stap = **~2.3% multiplicatieve resolutie**.

### 6.2 LineEdit → Slider

```cpp
void cAutomatedWidgets::slotLogLineEditChanged(const QString &text) const {
    const double value = systemData.locale.toDouble(text);
    if (value > 0.0) {
        const int sliderPosition = int(log10(value) * 100.0);
        slider->setValue(sliderPosition);
    }
    else {
        qWarning() << "value is not greater zero";
    }
}
```

**Beperking**: Negatieve of nul waarden worden **geweigerd**. De slider wordt niet geüpdatet en een warning wordt gelogd.

---

## 7. Dial Widgets

### 7.1 Dial → SpinBox

```cpp
void cAutomatedWidgets::slotDialMoved(int value) const {
    spinBox->setValue(value / 100.0);
}
```

| Dial Value | SpinBox Value |
|-----------|---------------|
| 0 | 0.00 |
| 50 | 0.50 |
| 100 | 1.00 |
| 314 | 3.14 |
| 360 | 3.60 |

**Resolutie**: 0.01 per dial stap = **2 decimalen**.

### 7.2 SpinBox → Dial

```cpp
void cAutomatedWidgets::slotSpinBoxDChanged(double value) const {
    dial->setValue(int(value * 100.0));
}
```

---

## 8. Bugs & Riskante Code

### 🐛 BUG #1 — parseWidgetProperties crasht bij namen zonder underscore

```cpp
widgetProperties parseWidgetProperties(QWidget *widget, QStringList allowedClassNames) {
    props.allowed = (props.name.length() > 1 && (allowedClassNames.contains(props.className)));
    int firstDashPosition = props.name.indexOf("_");
    props.typeName = props.name.left(firstDashPosition);   // → volledige naam als firstDashPosition = -1
    props.paramName = props.name.mid(firstDashPosition + 1); // → leeg string als firstDashPosition = -1
    return props;
}
```

Als een widget een toegestane class heeft maar een naam **zonder underscore** (bv. een tijdelijk widget), dan:
- `typeName` = volledige object name
- `paramName` = lege string
- `allowed` = true

Dit kan leiden tot crashes of corrupte parameter data in `synchronize_interface.cpp`.

**Fix**:
```cpp
props.allowed = (props.name.length() > 1 
                 && firstDashPosition > 0  // underscore moet bestaan en niet op positie 0
                 && allowedClassNames.contains(props.className));
```

---

### 🐛 BUG #2 — Inconsistente signaalkeuze voor slider4

```cpp
// slider (standaard)
connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(slotSliderMoved(int)));

// slider3
connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(slotSlider3Moved(int)));

// slider4 ← ANDERS!
connect(slider, SIGNAL(valueChanged(int)), this, SLOT(slotSlider4Moved(int)));
```

`slider4` gebruikt `valueChanged` in plaats van `sliderMoved`. Dit betekent dat **programmatische updates** van `slider4` ook de spinbox triggeren. Als `synchronize_interface.cpp` in write-mode de slider update, krijgt de spinbox een `valueChanged` signaal en probeert de slider weer te updaten → potentiele feedback loop of extra signals.

**Fix**: Wijzig `valueChanged` naar `sliderMoved` voor consistentie:
```cpp
connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(slotSlider4Moved(int)));
```

---

### 🐛 BUG #3 — Inconsistente signaalkeuze voor dial4

```cpp
// dial3
connect(dial, SIGNAL(valueChanged(int)), this, SLOT(slotDial3Moved(int)));

// dial4 ← ANDERS!
connect(dial, SIGNAL(sliderMoved(int)), this, SLOT(slotDial4Moved(int)));
```

`dial3` gebruikt `valueChanged`, maar `dial4` gebruikt `sliderMoved`. Dit is inconsistent en kan leiden tot verschillend gedrag bij programmatische updates.

---

### ⚠️ RISICO #4 — Integer overflow bij hoge decimalen

```cpp
const double multiplier = pow(10.0, decimals);
slider->setValue(int(value * multiplier));
```

Als `decimals = 16` (de maximale voor QDoubleSpinBox) en `value = 100.0`:
- `multiplier = 10^16`
- `value * multiplier = 10^18`
- `int(10^18)` → **undefined behavior** (overflow op 32-bit int)

QSlider gebruikt `int` intern. Qt bewaart het als `int`, maar de conversie van `double` naar `int` bij waarden > 2^31-1 is UB in C++.

---

### ⚠️ RISICO #5 — Locale inconsistentie bij logaritmische widgets

```cpp
// slotLogSliderMoved: schrijft getal zonder locale-aware formatting
const QString text = QString("%L1").arg(dValue);

// slotLogLineEditChanged: leest MET locale awareness
const double value = systemData.locale.toDouble(text);
```

`QString("%L1").arg(dValue)` gebruikt de **systeem-locale** voor formatting (komma vs punt). Maar als de gebruiker handmatig typt in een andere locale, kan `toDouble()` falen of verkeerd interpreteren.

---

### ⚠️ RISICO #6 — Log LineEdit accepteert geen negatieve waarden

```cpp
if (value > 0.0) {
    slider->setValue(int(log10(value) * 100.0));
} else {
    qWarning() << "value is not greater zero";
}
```

Als de gebruiker een negatief getal of nul typt:
- De slider wordt **niet geüpdatet**
- Er is **geen visuele feedback** in de UI (alleen een console warning)
- De lineEdit blijft de negatieve waarde tonen
- Maar de parameter container heeft mogelijk al de negatieve waarde ontvangen via `synchronize_interface`

---

### ⚠️ RISICO #7 — Vector3 Read-Modify-Write Race Condition

```cpp
void SynchronizeInterfaceReadVect3d(QString &nameVect, char lastChar, 
                                     double value, std::shared_ptr<cParameterContainer> par) {
    CVector3 vect = par->Get<CVector3>(nameVect);  // Read
    vect.x = value;                                  // Modify
    par->Set(nameVect, vect);                        // Write
}
```

Bij een Vector3 worden er 3 aparte read-modify-write operaties uitgevoerd. Als er **tussen twee componenten** een andere thread (of een slot) dezelfde vector update, gaat data verloren. Mandelbulber is over het algemeen single-threaded voor UI, maar dit is een architecturaal zwak punt.

**Fix**: Batch alle componenten samen in één update.

---

### ⚠️ RISICO #8 — QObject::sender() casting zonder check

```cpp
QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox *>(sender());
```

In `slotDoubleSpinBoxChanged` wordt `sender()` direct gecast naar `QDoubleSpinBox*` zonder `qobject_cast` of `dynamic_cast`. Als het signaal ooit van een ander widget type komt, is dit UB.

---

### ⚠️ RISICO #9 — Hardcoded /100 factor voor dials

```cpp
spinBox->setValue(value / 100.0);    // slotDialMoved
dial->setValue(int(value * 100.0));   // slotSpinBoxDChanged
```

Dials hebben een **vaste precisie van 2 decimalen**. Dit kan niet worden geconfigureerd per parameter. Sommige parameters hebben misschien 3 of 4 decimalen nodig.

---

## 9. Uitbreiding Recipe: Nieuw Widget Type Toevoegen

Stel je wilt een **exponential slider** toevoegen (bv. voor decay factoren):

### Stap 1: Slots toevoegen in cAutomatedWidgets

```cpp
// automated_widgets.hpp
private slots:
    void slotExpSliderMoved(int value) const;
    void slotExpSpinBoxChanged(double value) const;
```

### Stap 2: Implementeren in automated_widgets.cpp

```cpp
void cAutomatedWidgets::slotExpSliderMoved(int value) const {
    const QString sliderName = sender()->objectName();
    QString type, parameterName;
    GetNameAndType(sliderName, &parameterName, &type);
    const QString spinBoxName = QString("expspinbox_") + parameterName;
    
    QDoubleSpinBox *spinBox = sender()->parent()->findChild<QDoubleSpinBox *>(spinBoxName);
    if (spinBox) {
        // Exponential mapping: slider [-200, 200] → value [e^-2, e^2]
        const double dValue = exp(value / 100.0);
        spinBox->setValue(dValue);
    }
}

void cAutomatedWidgets::slotExpSpinBoxChanged(double value) const {
    const QString spinBoxName = sender()->objectName();
    QString type, parameterName;
    GetNameAndType(spinBoxName, &parameterName, &type);
    const QString sliderName = QString("expslider_") + parameterName;
    
    QSlider *slider = sender()->parent()->findChild<QSlider *>(sliderName);
    if (slider) {
        if (value > 0.0) {
            slider->setValue(int(log(value) * 100.0));
        }
    }
}
```

### Stap 3: Connecteren in ConnectSignalsForSlidersInWindow

```cpp
if (type == QString("expslider")) {
    QApplication::connect(slider, SIGNAL(sliderMoved(int)), 
                         this, SLOT(slotExpSliderMoved(int)));
    
    const QString spinBoxName = QString("expspinbox_") + parameterName;
    QDoubleSpinBox *spinBox = slider->parent()->findChild<QDoubleSpinBox *>(spinBoxName);
    if (spinBox) {
        QApplication::connect(spinBox, SIGNAL(valueChanged(double)), 
                             this, SLOT(slotExpSpinBoxChanged(double)));
    }
}
```

### Stap 4: Qt Designer naming

In de `.ui` file:
- Slider: `objectName="expslider_myParameter"`
- SpinBox: `objectName="expspinbox_myParameter"`

### Stap 5: SynchronizeInterface toevoegen (indien nodig)

Als de spinbox al van type `spinbox` is, wordt deze automatisch gesynchroniseerd door `SynchronizeInterfaceQDoubleSpinBox`. Geen extra code nodig.

---

*De `automated_widgets` en `synchronize_interface` vormen het **hart van de UI-binding** in Mandelbulber2. De elegantie zit in de naamgeving-conventie die volledig declaratief is — geen handmatige connecties, geen mapping tabellen. De prijs is een strakke naming discipline en enkele kwetsbaarheden in de string parsing.*

# Clip Mode Implementatie Checklist

## DOEL
Voeg een "Clip Mode" toe aan de Fake Lights/Orbit Trap feature die bepaalt of accumulatie alleen gebeurt binnen of buiten de fractal.

---

## FILES DIE GEWIJZIGD MOETEN WORDEN

### 1. src/common_params.hpp
**Actie**: Voeg nieuwe enum en veld toe aan sCommonParams

```cpp
// Nieuwe enum in namespace params
enum enumFakeLightsClipMode
{
    fakeLightsClipNone = 0,
    fakeLightsClipInside = 1,
    fakeLightsClipOutside = 2
};

// Nieuw veld in sCommonParams struct
params::enumFakeLightsClipMode fakeLightsClipMode;
```

**Regels**: Na regel 160 (na enumFakeLightsFalloff), en in struct na regel 186 (fakeLightsGlowFalloffType)

---

### 2. tools/populateOpenCL.php (OPTIONEEL)
**Actie**: Script automatisch uitvoeren na wijzigingen

```bash
cd /home/joeri/mandelbulber2/mandelbulber2
php tools/populateOpenCL.php nondry
```

**OF** handmatig sync naar opencl/common_params_cl.hpp

---

### 3. opencl/common_params_cl.hpp
**Actie**: Handmatig toevoegen als PHP script niet werkt

```cpp
// Nieuwe enum
enum enumFakeLightsClipModeCl
{
    fakeLightsClipNoneCl = 0,
    fakeLightsClipInsideCl = 1,
    fakeLightsClipOutsideCl = 2
};

// Nieuw veld in sCommonParamsCl
cl_int fakeLightsClipMode;
```

**Regels**: Na regel 178 (enumFakeLightsFalloffCl), en in struct na fakeLightsGlowFalloffType

Ook toevoegen aan clCopySCommonParamsCl() functie:
```cpp
target.fakeLightsClipMode = source.fakeLightsClipMode;
```

---

### 4. src/compute_fractal.cpp
**Actie**: Wijzig calcModeOrbitTrap sectie (regels 392-405)

**Huidige code**:
```cpp
else if (Mode == calcModeOrbitTrap)
{
    double distance = (in.common->fakeLightsRelativeCenter)
        ? OrbitTrapShapeDistance(z - aux.const_c, in.common)
        : OrbitTrapShapeDistance(z, in.common);

    if (i >= fakeLightsMinIter && i <= fakeLightsMaxIter)
        orbitTrapTotal += (1.0 / (distance * distance));
    if (distance > fractals.GetBailout(sequence))
    {
        out->orbitTrapR = orbitTrapTotal;
        break;
    }
}
```

**Nieuwe code**:
```cpp
else if (Mode == calcModeOrbitTrap)
{
    double distance = (in.common->fakeLightsRelativeCenter)
        ? OrbitTrapShapeDistance(z - aux.const_c, in.common)
        : OrbitTrapShapeDistance(z, in.common);

    bool shouldAccumulate = false;
    if (i >= fakeLightsMinIter && i <= fakeLightsMaxIter)
    {
        switch (in.common->fakeLightsClipMode)
        {
            case params::fakeLightsClipNone:
                shouldAccumulate = true;
                break;
            case params::fakeLightsClipInside:
                shouldAccumulate = (aux.r <= fractals.GetBailout(sequence));
                break;
            case params::fakeLightsClipOutside:
                shouldAccumulate = (aux.r > fractals.GetBailout(sequence));
                break;
        }
    }
    
    if (shouldAccumulate)
        orbitTrapTotal += (1.0 / (distance * distance));
    if (distance > fractals.GetBailout(sequence))
    {
        out->orbitTrapR = orbitTrapTotal;
        break;
    }
}
```

---

### 5. opencl/engines/compute_fractal.cl
**Actie**: Wijzig calcModeOrbitTrap sectie (regels 436-450)

**Huidige code**:
```c
#ifdef FAKE_LIGHTS
else if (mode == calcModeOrbitTrap)
{
    float distance = (consts->params.common.fakeLightsRelativeCenter)
        ? OrbitTrapShapeDistance(z - aux.const_c, consts)
        : OrbitTrapShapeDistance(z, consts);

    if (i >= fakeLightsMinIter && i <= fakeLightsMaxIter)
        orbitTrapTotal += (1.0f / (distance * distance));
    if (distance > consts->sequence.bailout[sequence])
    {
        out.orbitTrapR = orbitTrapTotal;
        break;
    }
}
#endif
```

**Nieuwe code**:
```c
#ifdef FAKE_LIGHTS
else if (mode == calcModeOrbitTrap)
{
    float distance = (consts->params.common.fakeLightsRelativeCenter)
        ? OrbitTrapShapeDistance(z - aux.const_c, consts)
        : OrbitTrapShapeDistance(z, consts);

    bool shouldAccumulate = false;
    if (i >= fakeLightsMinIter && i <= fakeLightsMaxIter)
    {
        switch (consts->params.common.fakeLightsClipMode)
        {
            case fakeLightsClipNoneCl:
                shouldAccumulate = true;
                break;
            case fakeLightsClipInsideCl:
                shouldAccumulate = (aux.r <= consts->sequence.bailout[sequence]);
                break;
            case fakeLightsClipOutsideCl:
                shouldAccumulate = (aux.r > consts->sequence.bailout[sequence]);
                break;
        }
    }
    
    if (shouldAccumulate)
        orbitTrapTotal += (1.0f / (distance * distance));
    if (distance > consts->sequence.bailout[sequence])
    {
        out.orbitTrapR = orbitTrapTotal;
        break;
    }
}
#endif
```

---

### 6. qt/dock_effects.ui
**Actie**: Voeg nieuwe ComboBox toe

**Locatie**: Grid layout, row 17 (vrij)

**UI Element**:
```xml
<widget class="QLabel" name="label_fakeLightsClipMode">
  <property name="text">
    <string>Clip Mode:</string>
  </property>
</widget>

<widget class="QComboBox" name="comboBox_fakeLightsClipMode">
  <item><property name="text"><string>None</string></property></item>
  <item><property name="text"><string>Inside</string></property></item>
  <item><property name="text"><string>Outside</string></property></item>
</widget>
```

**Grid positions**:
- Label: row 17, column 0
- ComboBox: row 17, column 1

---

### 7. src/interface/dock_effects.cpp (CONNECTIE)
**Actie**: Koppel UI aan params

Zoek naar bestaande fake lights connecties en voeg toe:
```cpp
// In constructor of init-functie
connect(ui->comboBox_fakeLightsClipMode, QOverload<int>::of(&QComboBox::currentIndexChanged),
    this, &cDockEffects::slotFakeLightsClipModeChanged);

// Slot functie
void cDockEffects::slotFakeLightsClipModeChanged(int index)
{
    SynchronizeInterfaceBasic();
}
```

---

### 8. src/initparameters.cpp
**Actie**: Voeg default waarde toe

Zoek naar andere fakeLights defaults en voeg toe:
```cpp
// In InitFractalParams() of vergelijkbare functie
par->Set(fakeLightsClipMode, (int)params::fakeLightsClipNone);
```

---

## BUILD & TEST STEPS

1. **Compile**:
   ```bash
   cd /home/joeri/mandelbulber2/mandelbulber2
   make clean
   qmake mandelbulber-opencl.pro
   make -j16
   ```

2. **Clear OpenCL Cache**:
   ```bash
   rm -rf ~/.mandelbulber/openclCache/*
   ```

3. **Test**:
   - Start Mandelbulber
   - Open Effects panel
   - Enable Fake Lights
   - Test alle 3 clip modes
   - Verify CPU en GPU resultaten zijn consistent

---

## VOLGORDE VAN UITVOERING

1. ✅ Analyse (30+ minuten) - GEDAAN
2. **src/common_params.hpp** - Enum + veld toevoegen
3. **opencl/common_params_cl.hpp** - Sync met CPU struct
4. **src/compute_fractal.cpp** - Clip mode logica
5. **opencl/engines/compute_fractal.cl** - Clip mode logica
6. **qt/dock_effects.ui** - UI toevoegen
7. **src/interface/dock_effects.cpp** - Connectie toevoegen
8. **src/initparameters.cpp** - Default waarde
9. **Build & Test**
10. **Clear cache & her-test**

---

## CRITISCHE PUNTEN

1. **OpenCL struct sync**: Zorg dat common_params_cl.hpp exact matched met common_params.hpp
2. **Bailout vergelijking**: `aux.r <= bailout` voor Inside, `aux.r > bailout` voor Outside
3. **Default waarde**: Moet 0 (None) zijn voor backward compatibility
4. **Cache clearing**: VERPLICHT na struct wijzigingen

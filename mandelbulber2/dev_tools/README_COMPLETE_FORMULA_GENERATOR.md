# Complete Formula Generator

## Wat Het Doet

Genereert **ALLE** bestanden die nodig zijn voor een nieuwe Mandelbulber formule — van één JSON specificatie.

## Hoe Het Werkt

```bash
cd mandelbulber2/dev_tools
python3 generate_complete_formula.py --input mijn_formule.json
```

## Wat Het Genereert

| # | Bestand | Locatie |
|---|---------|---------|
| 1 | **Enum entry** | `formula/definition/all_fractal_list_enums.hpp` |
| 2 | **Class declaratie** | `formula/definition/all_fractal_definitions.h` |
| 3 | **Factory registratie** | `formula/definition/all_fractal_list.cpp` |
| 4 | **Parameter registratie** | `src/initparameters.cpp` |
| 5 | **C++ source** | `formula/definition/fractal_<naam>.cpp` |
| 6 | **C++ header** | `formula/definition/fractal_<naam>.h` |
| 7 | **UI XML** | `deploy/share/mandelbulber2/formula/ui/<naam>.ui` |
| 8 | **OpenCL stub** | `deploy/share/mandelbulber2/formula/opencl/<naam>.cl` |

## JSON Voorbeeld

```json
{
  "formula": {
    "internal_name": "transf_mijn_transform",
    "display_name": "T>Mijn Transform",
    "de_type": "analyticDEType",
    "de_function": "linearDEFunction",
    "cpixel_addition": "cpixelEnabledByDefault",
    "default_bailout": 100.0,
    "de_analytic_function": "analyticFunctionLinear",
    "coloring_function": "coloringFunctionDefault"
  },
  "parameters": [
    {
      "name": "scale",
      "type": "double",
      "label": "Scale",
      "default": 2.0,
      "min": 0.001,
      "max": 100.0
    },
    {
      "name": "offset",
      "type": "cvector3",
      "label": "Offset",
      "default": [0.0, 0.0, 0.0]
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
      "label": "Enable",
      "default": true
    }
  ],
  "formula_code": "z *= fractal->transformCommon.scale;\n\taux.DE = aux.DE * fabs(fractal->transformCommon.scale) + 1.0;"
}
```

## Test Resultaat

```
Generating formula: T>Demo Scale V2
Next enum ID: 2106 (transfDemoScaleV2)
  Added enum entry
  Added FRACTAL_CLASS declaration
  Added factory registration
  Added parameter registration
  Generated C++ files
  Generated UI file
  Generated OpenCL stub

Validator: ALL PASSED ✅ (0 errors, 0 warnings)
```

## Workflow

```
1. Schrijf JSON specificatie
2. python3 generate_complete_formula.py --input spec.json
3. Implementeer FormulaCode() in .cpp
4. make -j$(nproc)
5. Test in Mandelbulber
```

**Tijdsbesparing: ~2-3 uur handmatig werk → 1 minuut met tool!**

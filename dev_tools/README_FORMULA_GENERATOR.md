# MANDELBULBER FORMULA GENERATOR TOOL

**Version:** 1.1
**Date:** 2026-04-19
**Author:** Claude + Joeri

---

## 📖 OVERVIEW

The Formula Generator Tool allows you to create **NEW** Mandelbulber fractal formulas by combining existing formulas. This tool automates the complex process of:

- Parsing existing formula C++ files
- Combining multiple FormulaCode sections
- Generating proper C++ class structure
- Handling variable name conflicts
- Creating different merge strategies

---

## 🚀 QUICK START

### Basic Usage

```bash
cd /home/joeri/mandelbulber2_v2_experiment/dev_tools
python3 formula_generator_interactive.py
```

This launches the interactive menu where you can:
1. Browse 457 available formulas
2. Search for specific formulas
3. Combine multiple formulas into one
4. Generate production-ready C++ code

---

## 📁 FILES

| File | Description |
|------|-------------|
| `formula_generator.py` | Automated tool (runs test automatically) |
| `formula_generator_interactive.py` | Interactive menu-driven tool |
| `generated_formulas/` | Output directory for generated formulas |
| `test.fract` | Test settings file (formula_1 = 217) |

---

## 🎯 FEATURES

### 1. Formula Parsing
- Scans all 457 formula files in `mandelbulber2/formula/definition/`
- Extracts complete formula information:
  - Class name
  - Internal ID and name
  - DE (Distance Estimation) settings
  - Complete FormulaCode implementation

### 2. Merge Strategies

#### **Sequential** (Default)
Executes formulas one after another:
```cpp
// Stage 1: Formula A
// ... code from formula A ...

// Stage 2: Formula B
// ... code from formula B ...
```

**Use case:** Create complex multi-stage fractals

#### **Parallel**
Alternates formulas based on iteration count:
```cpp
if (aux.i % 2 == 0) {
    // Formula A
} else {
    // Formula B
}
```

**Use case:** Create hybrid iteration patterns

#### **Weighted**
Blends formula results with weights:
```cpp
z_result = z_formula_a * 0.5 + z_formula_b * 0.5;
```

**Use case:** Smooth morphing between formulas

### 3. Automatic Code Generation
- Proper C++ class structure
- Correct header includes
- Constructor with all parameters
- Variable conflict resolution

---

## 📋 STEP-BY-STEP GUIDE

### Example: Combining Two Formulas

1. **Launch tool:**
   ```bash
   python3 formula_generator_interactive.py
   ```

2. **Search for formulas:**
   ```
   Menu: 2 (Search)
   Search term: "kleinian"
   ```

   Results:
   ```
   217. Pseudo Kleinian - Mod 4    [fractal::pseudoKleinianMod4]
   218. Pseudo Kleinian - StdDE    [fractal::pseudoKleinianStdDE]
   ```

3. **Combine formulas:**
   ```
   Menu: 3 (Combine)
   Formula numbers: 217,218
   Display Name: My Kleinian Hybrid
   Internal Name: my_kleinian_hybrid
   Internal ID: myKleinianHybrid
   Strategy: 1 (Sequential)
   ```

4. **Output:**
   ```
   ✅ Generated: generated_formulas/fractal_my_kleinian_hybrid.cpp
   ```

---

## 🔧 INTEGRATION WITH MANDELBULBER

### Step 1: Copy Generated File

```bash
cp generated_formulas/fractal_my_kleinian_hybrid.cpp \
   ../mandelbulber2/formula/definition/
```

### Step 2: Add to Registry

Edit `mandelbulber2/formula/all_fractal_definitions.h`:

```cpp
// Add near the end with other includes
#include "definition/fractal_my_kleinian_hybrid.cpp"
```

### Step 3: Add Enum ID

Find the fractal namespace enum and add your ID. Check the last number and increment:

```cpp
// In fractal_enums.h or similar
namespace fractal {
    enum enumFractalFormula {
        // ... existing formulas ...
        pseudoKleinianMod4 = 217,
        pseudoKleinianStdDE = 218,
        // Add your new formula
        myKleinianHybrid = 458,  // Use next available number
    };
}
```

### Step 4: Register Formula Class

In the formula registry initialization (usually in `fractal_list.cpp`):

```cpp
formulaList.append(new cFractalMyKleinianHybrid());
```

### Step 5: Rebuild Mandelbulber

```bash
cd ../mandelbulber2/qmake
qmake ../mandelbulber.pro
make -j$(nproc)
```

### Step 6: Test Your Formula

```bash
./mandelbulber2
```

Your new formula should appear in the formula dropdown!

---

## 🧪 TESTING WITH test.fract

The included `test.fract` file uses formula 217 (Pseudo Kleinian Mod 4):

```ini
[main_parameters]
formula_1 217;
camera_rotation 26.565 -16.602 0;
detail_level 2;
ambient_occlusion_enabled true;
```

**Test workflow:**
1. Generate a new formula combining #217 with others
2. Note the new formula's ID
3. Edit test.fract: `formula_1 458;` (use your new ID)
4. Load in Mandelbulber to test

---

## 📊 FORMULA DATABASE

The tool parses **457 formulas** including:

- **Power fractals:** Mandelbulb, Mandelbox, etc.
- **IFS fractals:** Menger, Koch, Sierpinski
- **Transform fractals:** Rotations, folds, spherical inversions
- **Kleinian groups:** Pseudo-Kleinian variants
- **4D fractals:** Quaternion and 4D extensions

---

## 🎨 ADVANCED USAGE

### Custom Merge Strategy

Edit `formula_generator_interactive.py` and add to `_generate_formula_code`:

```python
elif strategy == "custom":
    # Your custom merge logic
    code += '\t// Custom merge strategy\n'
    code += '\tdouble blend = sin(aux.i * 0.1);\n'
    code += '\t// Blend based on sine wave\n'
```

### Variable Conflict Resolution

The tool automatically renames local variables:

```cpp
// Original formula A:
double k = 0.0;

// Stage 1:
double k_s0 = 0.0;

// Stage 2:
double k_s1 = 0.0;
```

---

## 🐛 TROUBLESHOOTING

### Issue: "Formula not found"
**Solution:** Run option 1 to list all formulas and verify the number

### Issue: Compilation errors
**Solution:** Check for:
- Duplicate variable names (tool should fix, but manual check needed)
- Missing includes
- Incompatible DE types

### Issue: Formula produces black/blank image
**Solution:**
- Check DE type compatibility
- Verify bailout values
- Test with known-working parameters first

---

## 📚 REFERENCE

### Formula Structure

Every formula has:

```cpp
class cFractalMyFormula : cAbstractFractal {
    // Constructor - sets metadata
    cFractalMyFormula();

    // Main iteration code
    void FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux);
};
```

### Key Variables

| Variable | Description |
|----------|-------------|
| `z` | Current iteration point (CVector4: x,y,z,w) |
| `aux.i` | Current iteration number |
| `aux.DE` | Distance Estimation accumulator |
| `aux.r` | Radius/magnitude of z |
| `aux.color` | Color accumulator |
| `fractal->*` | All formula parameters |

### DE Types

| Type | Description | Use Case |
|------|-------------|----------|
| `analyticDEType` | Analytic DE (fast) | Most fractals |
| `deltaDEType` | Numerical DE (slow) | Complex transforms |

---

## 💡 TIPS

1. **Start Simple:** Combine 2 formulas first, test, then add more
2. **Use Similar DE Types:** Mix formulas with same DE type for best results
3. **Test Incrementally:** Build → test → iterate
4. **Save Presets:** Once working, save .fract files of good combinations
5. **Document:** Add comments explaining what each stage does

---

## 📖 EXAMPLES

### Example 1: Double Kleinian

Combine Pseudo Kleinian Mod 4 with itself for recursive effect:

```
Formulas: 217, 217
Name: Double Kleinian
Strategy: Sequential
```

### Example 2: Menger + Mandelbulb

```
Formulas: 52 (Menger), 7 (Mandelbulb Power 2)
Name: Menger Bulb Hybrid
Strategy: Parallel
```

### Example 3: Triple IFS

```
Formulas: 52, 53, 54 (various IFS)
Name: IFS Trinity
Strategy: Weighted
```

---

## 🔗 RELATED TOOLS

- **populateOpenCL.php:** Auto-generates OpenCL from C++ formulas
- **analyze_all_primitives.py:** Analyzes primitive code
- **add_deformations_to_primitives.py:** Adds deformation support

---

## 📞 SUPPORT

For issues or questions:
1. Check the Mandelbulber documentation
2. Review generated C++ code manually
3. Test with simpler formula combinations
4. Check compiler output for specific errors

---

## 🎓 LEARNING RESOURCES

### Understanding Formula Code

Read existing formulas in `mandelbulber2/formula/definition/`:
- Start with simple ones: `fractal_none.cpp`
- Study transforms: `fractal_transf_rotation.cpp`
- Complex examples: `fractal_pseudo_kleinian_mod4.cpp`

### Distance Estimation

See `MANDELBULBER_MATHEMATICS_AND_ALGORITHMS_COMPLETE.md`:
- Part 1: DE Theory
- Part 3: Fractal Iteration
- Part 4: Transformation System

---

## ✅ CHECKLIST: Adding New Formula

- [ ] Generate formula code
- [ ] Copy to formula/definition/
- [ ] Add include to all_fractal_definitions.h
- [ ] Add enum ID
- [ ] Register in formula list
- [ ] Rebuild Mandelbulber
- [ ] Test basic render
- [ ] Test with different parameters
- [ ] Save working preset
- [ ] Document interesting discoveries

---

## 🎉 HAPPY FRACTAL CREATING!

This tool opens up **thousands** of possible formula combinations. Experiment, explore, and create amazing new fractals!

**Remember:** The best discoveries often come from unexpected combinations. Don't be afraid to mix formulas that seem unrelated!

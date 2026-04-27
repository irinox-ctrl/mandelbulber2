# DEV TOOLS INDEX
**Mandelbulber v2 Development Tools**
**Location:** `/home/joeri/mandelbulber2_v2_experiment/dev_tools/`

---

## 🛠️ AVAILABLE TOOLS

### 1. Formula Generator (MAIN TOOL)

#### **formula_generator_interactive.py** ⭐
**Interactive formula combination tool**

```bash
python3 formula_generator_interactive.py
```

**Features:**
- Browse 457 available formulas
- Search by name
- Combine multiple formulas
- 3 merge strategies (sequential, parallel, weighted)
- Auto-generate C++ code

**Output:** `generated_formulas/fractal_*.cpp`

**Documentation:** `README_FORMULA_GENERATOR.md`

---

#### **formula_generator.py**
**Automated test version**

```bash
python3 formula_generator.py
```

**What it does:**
- Runs automatic test combining pseudoKleinianMod4 with itself
- Generates `fractal_test_combined_pk.cpp`
- Useful for testing tool functionality

---

### 2. Formula ID Finder

#### **find_next_formula_id.py**
**Find next available formula enum ID**

```bash
python3 find_next_formula_id.py
```

**Output:**
```
NEXT AVAILABLE NUMBER: 458
Current formula count: 457
```

**Use case:** When adding new formulas, need to know next ID number

---

### 3. Test Files

#### **test.fract**
**Test settings file for formula 217**

```ini
formula_1 217;  # Pseudo Kleinian Mod 4
camera_rotation 26.565 -16.602 0;
detail_level 2;
```

**Use case:** Testing generated formulas in Mandelbulber

---

## 📁 DIRECTORY STRUCTURE

```
dev_tools/
├── formula_generator_interactive.py    ⭐ Main tool
├── formula_generator.py                  Test version
├── find_next_formula_id.py               ID finder utility
├── test.fract                            Test settings
├── README_FORMULA_GENERATOR.md           Full documentation
├── TOOLS_INDEX.md                        This file
└── generated_formulas/                   Output directory
    └── fractal_*.cpp                     Generated formulas
```

---

## 🚀 QUICK START WORKFLOW

### Create a New Formula

1. **Find formulas to combine:**
   ```bash
   python3 formula_generator_interactive.py
   # Select option 2 (Search)
   ```

2. **Combine formulas:**
   ```bash
   # In interactive tool, select option 3
   # Enter formula numbers: 217,52
   # Enter names and settings
   ```

3. **Find next ID:**
   ```bash
   python3 find_next_formula_id.py
   # Note the number (e.g., 458)
   ```

4. **Integrate into Mandelbulber:**
   - Copy generated .cpp to `mandelbulber2/formula/definition/`
   - Add include to `all_fractal_definitions.h`
   - Add enum with ID 458
   - Rebuild

5. **Test:**
   - Load Mandelbulber
   - Select your formula
   - Render!

---

## 📊 TOOL CAPABILITIES

### Formula Database
- **Total formulas:** 457
- **Categories:**
  - Power fractals (Mandelbulb, etc.)
  - IFS (Menger, Koch, Sierpinski)
  - Transforms (rotations, folds, inversions)
  - Kleinian groups
  - 4D fractals

### Merge Strategies

| Strategy | Description | Use Case |
|----------|-------------|----------|
| Sequential | Execute in order | Multi-stage effects |
| Parallel | Alternate by iteration | Hybrid patterns |
| Weighted | Blend results | Smooth morphing |

### Generated Code Quality
- ✅ Proper C++ structure
- ✅ Correct headers
- ✅ Variable conflict resolution
- ✅ Formatted and commented
- ✅ Production-ready

---

## 🎯 COMMON USE CASES

### Case 1: Create Hybrid Fractal
```
Combine: Mandelbulb + Mandelbox
Strategy: Parallel
Result: Alternates between bulb and box iterations
```

### Case 2: Multi-Stage Transform
```
Combine: Transform A → Transform B → Base Formula
Strategy: Sequential
Result: Complex transformation pipeline
```

### Case 3: Morphing Effect
```
Combine: Formula A + Formula B
Strategy: Weighted
Result: Smooth blend between two fractals
```

---

## 🔧 ADVANCED USAGE

### Custom Modifications

After generation, you can manually edit:

1. **Adjust blend weights:**
   ```cpp
   z = z_formula_a * 0.7 + z_formula_b * 0.3;
   ```

2. **Add conditional logic:**
   ```cpp
   if (aux.i < 50) {
       // Use formula A
   } else {
       // Use formula B
   }
   ```

3. **Add custom parameters:**
   ```cpp
   double blend = fractal->transformCommon.scale1;
   z = z_a * blend + z_b * (1.0 - blend);
   ```

---

## 📚 DOCUMENTATION

### Primary Docs
- **README_FORMULA_GENERATOR.md** - Complete guide
- **TOOLS_INDEX.md** - This file

### Reference Docs (in /Mandelbulber Core/)
- **MANDELBULBER_MASTER_REFERENCE.md** - Architecture overview
- **MANDELBULBER_COMPLETE_TECHNICAL_REFERENCE.md** - All systems
- **MANDELBULBER_MATHEMATICS_AND_ALGORITHMS_COMPLETE.md** - Math formulas
- **MANDELBULBER_ADVANCED_DEVELOPER_REFERENCE.md** - Developer patterns

---

## 🐛 TROUBLESHOOTING

### Tool doesn't start
```bash
# Check Python version
python3 --version  # Should be 3.6+

# Check file permissions
chmod +x *.py
```

### Formula not found
```bash
# Verify formula directory
ls ../mandelbulber2/formula/definition/ | wc -l
# Should show 457 files
```

### Compilation errors after integration
- Check variable name conflicts
- Verify DE type compatibility
- Check all includes are present
- Run `make clean && make`

---

## 🎓 LEARNING PATH

1. **Start:** Read README_FORMULA_GENERATOR.md
2. **Practice:** Run interactive tool, browse formulas
3. **Experiment:** Combine 2 simple formulas
4. **Study:** Read generated code
5. **Advanced:** Manually modify generated code
6. **Master:** Create custom merge strategies

---

## 💡 PRO TIPS

1. **Test Incrementally:** Combine 2 formulas first
2. **Use Similar Types:** Mix formulas with same DE type
3. **Save Presets:** Document working combinations
4. **Version Control:** Use git for generated formulas
5. **Read Source:** Study existing formulas for inspiration

---

## 🔗 RELATED TOOLS

### In mandelbulber2/ directory:

| Tool | Location | Purpose |
|------|----------|---------|
| populateOpenCL.php | tools/ | Generate OpenCL from C++ |
| analyze_all_primitives.py | / | Analyze primitives |
| add_deformations_to_primitives.py | / | Add deformations |

---

## 📞 NEXT STEPS

1. ✅ Tool created and tested
2. ✅ Documentation complete
3. 🎯 **Your turn:** Create your first formula!

**Ready to start?**
```bash
cd /home/joeri/mandelbulber2_v2_experiment/dev_tools
python3 formula_generator_interactive.py
```

---

## 🎉 HAPPY FRACTAL GENERATING!

These tools enable you to create **thousands** of new formula combinations. The only limit is your imagination!

**Remember:** Every great fractal discovery starts with a simple experiment. Start combining!

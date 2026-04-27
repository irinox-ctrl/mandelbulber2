# FORMULA VALIDATOR & TESTER

**Version:** 1.0
**Purpose:** Automatic validation of generated formulas
**Integration:** Works standalone or with generator

---

## 🎯 FEATURES

### Validation Checks (8 Categories)

1. **Basic Syntax**
   - Brace balance `{ }`
   - Parenthesis balance `( )`
   - Semicolons
   - Namespace usage

2. **Include Checks**
   - Required headers present
   - No missing dependencies

3. **Class Structure**
   - Valid class declaration
   - Correct inheritance
   - Proper base class

4. **Constructor Validation**
   - All required parameters
   - DE type validity
   - Function type validity

5. **FormulaCode Function**
   - Correct signature
   - DE updates
   - z modifications
   - Color handling

6. **Variable Conflicts**
   - Duplicate declarations
   - Scope issues
   - Name collisions

7. **DE Type Consistency**
   - Type/function compatibility
   - Analytic vs numerical
   - Configuration validation

8. **Common Pitfalls**
   - Division by zero risks
   - Uninitialized variables
   - Missing DE updates
   - Logic errors

---

## 🚀 USAGE

### Standalone Mode

```bash
python3 formula_validator.py
```

**Output:**
```
🔍 VALIDATING: fractal_test_v2_pk.cpp

✅ Info messages: 13
⚠️  Warnings: 0
❌ Errors: 1
📊 Score: 50.0%

✅ PASS fractal_test_v2_pk.cpp    Score:  50.0%
```

### Integrated with Generator

V2 generator automatically runs validation:

```python
from formula_validator import FormulaValidator

validator = FormulaValidator(base_dir)
result = validator.validate_formula(cpp_file)

if result.passed:
    print("✅ VALIDATION PASSED!")
```

---

## 📊 SCORING SYSTEM

**Score Range:** 0.0 - 1.0 (0% - 100%)

Each check contributes to overall score:

| Score | Status | Meaning |
|-------|--------|---------|
| 100% | ✅ Perfect | No issues |
| 90-99% | ✅ Excellent | Minor warnings |
| 70-89% | ⚠️ Good | Some warnings |
| 50-69% | ⚠️ Fair | Multiple warnings |
| < 50% | ❌ Poor | Critical errors |

**Pass Threshold:** Score >= 70% AND 0 errors

---

## 🔍 VALIDATION RESULTS

### Example Output

```
======================================================================
📊 VALIDATION SUMMARY
======================================================================

✅ Info messages: 13
  ℹ️  Brace balance OK: 10 pairs
  ℹ️  Class name: cFractalTestv2pk
  ℹ️  FormulaCode function signature OK
  ℹ️  Uses DE (Distance Estimation)
  ℹ️  No obvious variable conflicts detected

⚠️  Warnings: 2
  ⚠️  Multiple 'colorAdd' declarations (potential conflict)
  ⚠️  Potential division by zero (check DE/rr guards)

❌ Errors: 0

📊 Score: 95.0%

======================================================================
✅ VALIDATION PASSED
======================================================================
```

---

## 🛠️ VALIDATION DETAILS

### 1. Basic Syntax Checks

**Detects:**
- Unmatched `{` `}` braces
- Unmatched `(` `)` parentheses
- Missing semicolons
- Namespace issues

**Example Issues:**
```cpp
// ❌ Unmatched brace
void FormulaCode(...) {
    if (condition) {
        doSomething();
    // Missing }
}

// ✅ Correct
void FormulaCode(...) {
    if (condition) {
        doSomething();
    }
}
```

### 2. Include Checks

**Required:**
```cpp
#include "all_fractal_definitions.h"
```

**Detects:**
- Missing includes
- Wrong include paths

### 3. Class Structure

**Expected:**
```cpp
class cFractalMyFormula : public cAbstractFractal
{
public:
    cFractalMyFormula();
    void FormulaCode(...) override;
};
```

**Detects:**
- Missing class declaration
- Wrong base class
- Missing override keyword

### 4. Constructor Validation

**Required Parameters:**
```cpp
nameInComboBox = "...";
internalName = "...";
internalID = fractal::...;
DEType = ...;
DEFunctionType = ...;
```

**Validates:**
- All parameters present
- Valid DE type values
- Valid function type values

### 5. FormulaCode Checks

**Expected Signature:**
```cpp
void cFractalMyFormula::FormulaCode(
    CVector4 &z,
    const sFractal *fractal,
    sExtendedAux &aux)
```

**Checks:**
- Correct parameters
- aux.DE usage
- z modifications
- Color handling

### 6. Variable Conflict Detection

**Detects:**
```cpp
// ⚠️ WARNING: Multiple declarations
double colorAdd = 0.0;  // Stage 1
// ... later ...
double colorAdd = 0.0;  // Stage 2 - CONFLICT!
```

**V2 Generator Fixes:**
```cpp
// ✅ Auto-fixed with suffixes
double colorAdd_s0 = 0.0;  // Stage 1
double colorAdd_s1 = 0.0;  // Stage 2
```

### 7. DE Type Validation

**Checks Compatibility:**
```cpp
// ✅ Valid combination
DEType = analyticDEType;
DEFunctionType = logarithmicDEFunction;

// ⚠️ Questionable
DEType = analyticDEType;
DEFunctionType = unknownFunction;
```

### 8. Common Pitfalls

**Division by Zero:**
```cpp
// ⚠️ Potential issue
z *= scale / aux.DE;  // What if DE = 0?

// ✅ Better with guard
if (aux.DE > 0.0001)
    z *= scale / aux.DE;
```

**Uninitialized Variables:**
```cpp
// ⚠️ Potential issue
double temp;
temp = z.x * temp;  // Using uninitialized!

// ✅ Correct
double temp = 0.0;
temp = z.x * temp;
```

---

## 📈 IMPROVING SCORES

### Tips to Fix Issues

1. **Syntax Errors (Critical)**
   - Use validator output to locate
   - Check brace matching
   - Verify all semicolons

2. **Variable Conflicts (Warning)**
   - Use V2 generator (auto-fixes)
   - Add scope isolation `{ }`
   - Rename conflicting variables

3. **Missing Parameters (Error)**
   - Check constructor completeness
   - Verify all required fields

4. **DE Issues (Warning)**
   - Match DE type with function
   - Use known DE types

---

## 🎓 INTERPRETING RESULTS

### Good Formula Example

```
✅ Info messages: 15
⚠️  Warnings: 0
❌ Errors: 0
📊 Score: 100.0%

✅ VALIDATION PASSED
```

**Action:** Ready for integration!

### Needs Fixes Example

```
✅ Info messages: 10
⚠️  Warnings: 5
❌ Errors: 2
📊 Score: 45.0%

❌ VALIDATION FAILED
```

**Action:**
1. Fix all errors first
2. Address critical warnings
3. Re-validate
4. Repeat until pass

---

## 🔧 INTEGRATION WORKFLOW

### Complete Process

```bash
# 1. Generate formula
python3 formula_generator_v2.py

# 2. Validation runs automatically
#    (built into V2 generator)

# 3. If validation passes:
✅ Ready to integrate into Mandelbulber

# 4. If validation fails:
❌ Check errors, fix issues, regenerate
```

---

## 📁 OUTPUT FILES

Validator doesn't create files, only validates:

**Input:** `generated_formulas/fractal_*.cpp`
**Output:** Console report + return code

**Return Codes:**
- `0` = All formulas passed
- `1` = Some formulas failed

---

## 🐛 FALSE POSITIVES

### ASCII Art in Headers

The header comment art may contain unmatched parentheses:

```cpp
/**
 *                        \><||i|=>>%)     <- Extra )
 */
```

**Solution:** Validator knows to ignore this (comment-aware)

### Commented Code

```cpp
// double temp = calc();  <- Detected but in comment
```

**Solution:** Currently basic regex, improvement planned

---

## ⚡ PERFORMANCE

**Speed:**
- 457 formula scan: ~2 seconds
- Single validation: <0.1 seconds
- Compilation test: 1-2 seconds (if g++ available)

**Memory:**
- Minimal (<50MB)
- No heavy parsing libraries

---

## 🎯 FUTURE ENHANCEMENTS

### Planned Features

1. **AST Parsing**
   - More accurate syntax checking
   - Better variable tracking
   - Scope-aware analysis

2. **Compilation Testing**
   - Full g++ integration
   - Syntax-only check
   - Warning detection

3. **Runtime Testing**
   - Generate test renders
   - Verify no crashes
   - Compare with originals

4. **Auto-Fix Mode**
   - Automatically fix common issues
   - Suggest improvements
   - Code formatting

5. **Integration Testing**
   - Test with Mandelbulber build
   - Check registration
   - Verify UI integration

---

## 📚 EXAMPLES

### Example 1: Perfect Formula

```bash
python3 formula_validator.py

# Output:
✅ VALIDATION PASSED
📊 Score: 100.0%
```

### Example 2: Minor Issues

```bash
# Output:
⚠️  Warnings: 3
  ⚠️  Variable 'k' declared 2 times
  ⚠️  Potential division by zero
  ⚠️  Missing z update guard

✅ VALIDATION PASSED (with warnings)
📊 Score: 85.0%
```

### Example 3: Critical Errors

```bash
# Output:
❌ Errors: 3
  ❌ Missing class declaration
  ❌ Unmatched braces
  ❌ No FormulaCode function

❌ VALIDATION FAILED
📊 Score: 20.0%
```

---

## 🎓 BEST PRACTICES

1. **Always Validate**
   - Before integration
   - After manual edits
   - Before commits

2. **Fix Errors First**
   - Errors block integration
   - Warnings can wait
   - Score matters

3. **Use V2 Generator**
   - Built-in validation
   - Auto-fixes conflicts
   - Higher success rate

4. **Read Warnings**
   - May indicate bugs
   - Could affect rendering
   - Worth investigating

5. **Test After Integration**
   - Validation ≠ guarantee
   - Still test renders
   - Check parameters

---

## ✅ VALIDATION CHECKLIST

Before declaring formula "production ready":

- [ ] Validator score >= 70%
- [ ] Zero errors
- [ ] Critical warnings addressed
- [ ] Manual code review done
- [ ] Compilation successful
- [ ] Test render works
- [ ] Parameters accessible
- [ ] No crashes
- [ ] Matches expected behavior

---

**Remember:** The validator is a tool, not a replacement for testing! Always verify formulas render correctly in Mandelbulber.

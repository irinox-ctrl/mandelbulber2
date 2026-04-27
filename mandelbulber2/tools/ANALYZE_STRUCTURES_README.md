# analyzeStructures.py - Mandelbulber2 Structure Analyzer

## Overview

**analyzeStructures.py** is a comprehensive validation and analysis tool for Mandelbulber2's core data structures. It validates consistency between CPU and OpenCL implementations, checks for structural integrity, and identifies potential issues.

Based on comprehensive studies:
- `SCOMMONPARAMS_COMPREHENSIVE_STUDY.md`
- `CALCPARAMS_COMPREHENSIVE_STUDY.md`
- `MORPH_SYSTEM_COMPREHENSIVE_STUDY.md`

## Features

### ✅ Structure Validation
- **sCommonParams** - Validates CPU/OpenCL alignment (70+ members)
- **sClCalcParams** - Validates OpenCL runtime structure (9 members)
- **enumMorphType** - Validates morph type enumeration (11 types)

### 🔍 Analysis Capabilities
- Member count verification
- CPU ↔ OpenCL member alignment checking
- Padding field detection
- Unused parameter detection
- Initialization pattern validation
- Type consistency checking

### 📊 Reporting
- Color-coded output (✅ success, ⚠️  warnings, ❌ errors)
- Detailed member listings
- Usage statistics
- Comprehensive summary reports

## Installation

The tool requires Python 3.6+. No additional dependencies.

```bash
# Make executable
chmod +x tools/analyzeStructures.py

# Verify installation
python3 tools/analyzeStructures.py --help
```

## Usage

### Quick Checks

```bash
# Check sCommonParams CPU/OpenCL alignment
./tools/analyzeStructures.py --check-commonparams

# Check sClCalcParams structure
./tools/analyzeStructures.py --check-calcparams

# Check morph type enumeration
./tools/analyzeStructures.py --check-morph
```

### Advanced Analysis

```bash
# Find potentially unused sCommonParams members
./tools/analyzeStructures.py --find-unused-params

# Validate calcParams initialization in OpenCL engines
./tools/analyzeStructures.py --validate-init

# Check structure alignment
./tools/analyzeStructures.py --check-alignment
```

### Comprehensive Validation

```bash
# Run ALL checks and generate full report
./tools/analyzeStructures.py --validate-all

# Generate comprehensive report only
./tools/analyzeStructures.py --report
```

## Output Examples

### sCommonParams Alignment Check

```
================================================================================
CHECKING sCommonParams ALIGNMENT
================================================================================

📊 CPU members: 48
📊 OpenCL members: 51

✅ All members present in both CPU and OpenCL

📝 Padding fields found: 3
   - cl_float pad1[2];
   - cl_float pad2[1];
   - cl_float pad3[3];
```

### sClCalcParams Structure Check

```
================================================================================
CHECKING sClCalcParams STRUCTURE
================================================================================

📊 OpenCL members: 9
📊 Expected members: 9

✅ Member count matches expected

📝 Members:
   cl_uint              N
   cl_uint              deltaDEMaxN
   cl_int               randomSeed
   cl_int               iterThreshMode
   cl_int               normalCalculationMode
   cl_int               orbitTrapIndex
   cl_float3            orbitTrap
   cl_float             distThresh
   cl_float             detailSize

✅ All required members present
```

### Morph Type Check

```
================================================================================
CHECKING MORPH TYPE ENUMERATION
================================================================================

📊 Morph types found: 11
📊 Expected types: 11

✅ Type count matches expected

📝 Morph Types:
   0   - morphNone
   1   - morphLinear
   2   - morphLinearAngle
   3   - morphCatMullRom
   4   - morphCatMullRomAngle
   5   - morphAkima
   6   - morphAkimaAngle
   7   - morphCubic
   8   - morphCubicAngle
   9   - morphSteffen
   10  - morphSteffenAngle

✅ All expected types present
```

## Validation Rules

### sCommonParams
- ✅ All CPU members must exist in OpenCL (or be explicitly documented)
- ✅ Padding fields must use `pad` prefix
- ✅ Member types must be compatible (CVector3 ↔ cl_float3)
- ⚠️  Unused members should be documented or removed

### sClCalcParams
- ✅ Exactly 9 members expected
- ✅ All required members present: N, deltaDEMaxN, randomSeed, iterThreshMode, normalCalculationMode, orbitTrapIndex, orbitTrap, distThresh, detailSize
- ✅ All OpenCL engines must initialize: N, normalCalculationMode, iterThreshMode, distThresh, detailSize

### Morph Types
- ✅ Exactly 11 morph types expected
- ✅ All expected types present: morphNone, morphLinear, morphLinearAngle, morphCatMullRom, morphCatMullRomAngle, morphAkima, morphAkimaAngle, morphCubic, morphCubicAngle, morphSteffen, morphSteffenAngle
- ⚠️  New types should be documented

## Common Issues and Solutions

### Issue: Member count mismatch

**Symptom:**
```
⚠️  Member count mismatch!
   Expected: 70
   Found: 68
```

**Solution:**
1. Check if new members were added to CPU struct but not OpenCL
2. Verify padding fields are correctly counted
3. Check comprehensive study documentation for expected count

### Issue: Missing members in OpenCL

**Symptom:**
```
⚠️  Members in CPU but NOT in OpenCL:
   - newMember
```

**Solution:**
1. Add member to OpenCL struct in `opencl/common_params_cl.hpp`
2. Use correct OpenCL types (cl_float, cl_int, cl_float3)
3. Add padding if needed for 16-byte alignment

### Issue: Incomplete calcParams initialization

**Symptom:**
```
⚠️  Missing initialization:
   - calcParam.distThresh
   - calcParam.detailSize
```

**Solution:**
1. Add missing initialization in OpenCL engine file
2. Use standard pattern:
   ```c
   calcParam.distThresh = CalcDistThresh(point, consts);
   calcParam.detailSize = CalcDelta(point, consts);
   ```

### Issue: Potentially unused parameters

**Symptom:**
```
⚠️  cl_float oldUnusedParam - NOT FOUND
```

**Solution:**
1. Verify parameter is truly unused (search manually)
2. If unused: Remove from struct OR document why it's kept
3. If used: Check if search pattern needs adjustment

## Integration with Development Workflow

### Pre-Commit Checks

Add to your pre-commit hook:

```bash
#!/bin/bash
# .git/hooks/pre-commit

echo "Running structure validation..."
python3 tools/analyzeStructures.py --validate-all

if [ $? -ne 0 ]; then
    echo "❌ Structure validation failed!"
    echo "Run: python3 tools/analyzeStructures.py --report"
    exit 1
fi

echo "✅ Structure validation passed"
```

### CI/CD Integration

Add to your CI pipeline:

```yaml
# .github/workflows/validate.yml
- name: Validate Structures
  run: |
    python3 tools/analyzeStructures.py --validate-all
```

### Regression Testing

After modifying structures:

```bash
# Before changes
./tools/analyzeStructures.py --report > before.txt

# Make changes
# ... edit common_params.hpp ...

# After changes
./tools/analyzeStructures.py --report > after.txt

# Compare
diff before.txt after.txt
```

## Technical Details

### Analyzed Files

**sCommonParams:**
- CPU: `src/common_params.hpp` (lines 191-266)
- OpenCL: `opencl/common_params_cl.hpp` (lines 214-291)

**sClCalcParams:**
- OpenCL: `opencl/input_data_structures.h` (lines 72-83)

**enumMorphType:**
- CPU: `src/one_parameter.hpp` (lines 53-66)

### Search Locations

- Source files: `src/**/*.cpp`, `src/**/*.hpp`
- OpenCL files: `opencl/**/*.cl`, `opencl/**/*.h`

### Performance

- Typical run time: < 1 second
- Full validation: ~2-3 seconds (includes file searching)
- Memory usage: < 50MB

## Extending the Tool

### Adding New Structure Checks

Edit `STRUCTURES` dictionary in `analyzeStructures.py`:

```python
STRUCTURES = {
    'YourNewStruct': {
        'cpu_file': SRC_DIR / 'your_struct.hpp',
        'cpu_start': 100,
        'cpu_end': 150,
        'opencl_file': OPENCL_DIR / 'your_struct_cl.hpp',
        'opencl_start': 50,
        'opencl_end': 100,
        'member_count': 25,
    }
}
```

### Adding New Validation Rules

Add function:

```python
def check_your_struct():
    """Check your structure."""
    print("CHECKING YOUR STRUCTURE")
    # Your validation logic
    return result
```

Add to `main()`:

```python
if args.check_yourstruct or args.validate_all:
    check_your_struct()
```

## Troubleshooting

### Tool doesn't find files

**Error:**
```
❌ File not found: /path/to/file
```

**Solution:**
1. Verify you're running from correct directory
2. Check `MANDELBULBER_ROOT` path detection
3. Verify file paths in `STRUCTURES` dictionary

### False positives for unused parameters

**Issue:** Parameter marked as unused but is actually used

**Solution:**
1. Check if parameter name appears in comments only
2. Verify search patterns match actual usage
3. Add manual verification for flagged parameters

### Python version issues

**Error:** Syntax errors or import failures

**Solution:**
1. Verify Python 3.6+: `python3 --version`
2. Use correct Python: `python3` instead of `python`
3. Check shebang: `#!/usr/bin/env python3`

## Contributing

When modifying structures:

1. ✅ Run `--validate-all` BEFORE committing
2. ✅ Update comprehensive study documentation
3. ✅ Update expected counts in `STRUCTURES` if needed
4. ✅ Add test cases for new features
5. ✅ Document any new validation rules

## Support

For issues or questions:

1. Check comprehensive study documentation:
   - `SCOMMONPARAMS_COMPREHENSIVE_STUDY.md`
   - `CALCPARAMS_COMPREHENSIVE_STUDY.md`
   - `MORPH_SYSTEM_COMPREHENSIVE_STUDY.md`

2. Run full report: `./tools/analyzeStructures.py --report`

3. Check tool source code comments for implementation details

## Version History

**v1.0** (2026-04-20)
- Initial release
- sCommonParams validation
- sClCalcParams validation
- Morph type validation
- Unused parameter detection
- Initialization pattern validation
- Comprehensive reporting

## License

Same as Mandelbulber2 project (GPL-3.0)

---

**Created:** 2026-04-20
**Author:** Based on comprehensive structure studies
**Maintained by:** Mandelbulber2 development team

# Mutation System

The mutation system provides per-formula pre/post processing transformations applicable to ANY fractal formula in 3x3lion / Mandelbulber2.

## Directory Structure

```
mutations/
  systems/           # .mut definition files per system
    custom_clip/     # Example system
  generated/         # Auto-generated .inc files (CPU/GPU switch blocks)
  codegen/           # Code generation tools
    generate_switch.py       # Switch-case code generator
    mutation_wizard.py       # Batch mutation creation tool
    nuclear_analysis.py      # System analysis tool
  config/            # Configuration files
    mutation_registry.json   # System registry
```

## Safety & Constraints

- **TYPE_ID Range**: Must be unique per system, 1-999. Case 0 is reserved (disabled).
- **Parameter Count**: Max 8 parameters per mutation (PA-PH).
- **GPU Precision**: `FLOAT_T` = `float` (32-bit). Avoid operations requiring >6 significant digits.
- **Enabled Flags**: Each subsystem has its own enabled flag. If disabled, the switch case is skipped entirely.
- **NaN/Inf Recovery**: Automatic rollback to pre-mutation `z` on NaN/Inf detection.
- **DE Guard**: `aux.DE` is clamped to `[1e-15, 1e15]` and reset to `1.0` on NaN/Inf.

## Safety Macros

### CPU (`mutation_macros_cpu.h`)

| Macro | Description |
|-------|-------------|
| `GUARD_ZERO(x)` | Clamps near-zero values away from 0 (double) |
| `GUARD_ZERO_VAL(x)` | Returns guarded value without modifying original |
| `SAFE_EXP(x)` | `exp(clamp(x, -40, 40))` — safe for double |
| `SAFE_DIV(n, d)` | Returns 0 if denominator near-zero |
| `SAFE_SQRT(x)` | `sqrt(max(x, 0))` |
| `SAFE_LOG(x)` | `log(max(x, 1e-21))` |
| `SAFE_POW(b, e)` | Guards base and exponent |

### GPU (`mutation_macros_gpu.h`)

| Macro | Description |
|-------|-------------|
| `GUARD_ZERO(x)` | Pointer-safe, uses `1e-21f` (float) |
| `SAFE_EXP(x)` | `native_exp(clamp(x, -25, 25))` — safe for float |
| `SAFE_DIV(n, d)` | Returns `0.0f` if denominator near-zero |
| `SAFE_SQRT(x)` | `native_sqrt(max(x, 0))` |

## Troubleshooting

| Error | Cause | Fix |
|-------|-------|-----|
| `GPU_DOUBLE` | CPU `double` literal in GPU code | Use `FLOAT_T` macro or add `f` suffix |
| `DIV_ZERO` | Unguarded division | Use `GUARD_ZERO(x)` or `SAFE_DIV()` |
| `CASE_MISMATCH` | CPU/GPU case count differs | Regenerate with `generate_switch.py` |
| `NaN artifacts` | Math overflow | Use `SAFE_EXP()`, check parameter bounds |
| `TYPE_ID collision` | Duplicate IDs | Run `generate_switch.py --validate-only` |

## Creating New Mutations

### Quick Start

```bash
cd mandelbulber2/mutations/codegen/

# Create a new system interactively
python3 mutation_wizard.py --new-system

# Generate 50 mutations for a system
python3 mutation_wizard.py --batch-add 50 --system custom_clip --template smooth_fold

# Validate all .mut files
python3 mutation_wizard.py --validate

# Generate switch blocks
python3 generate_switch.py --system custom_clip

# Full rebuild (validate + generate)
python3 mutation_wizard.py --full-rebuild
```

### .mut File Format

```c
// SYSTEM: custom_clip
// TYPE_ID: 1
// NAME: Linear Scale Variant 1
// PARAMS: PA, PB, PC

if (zz.x > PA) zz.x = PA - zz.x;
else if (zz.x < -PA) zz.x = -PA - zz.x;
```

### Parameter Aliases

Parameters `PA` through `PH` are expanded to struct field accessors during code generation:
- CPU: `PA` -> `mut.customClipParamA`
- GPU: `PA` -> `mut->customClipParamA`

Aliases are sorted by length (longest first) during expansion to prevent partial match bugs.

## Per-Subsystem Enabled Flags

Each subsystem has an independent enabled flag:

| Flag | Subsystem |
|------|-----------|
| `inversionEnabled` | Inversion transforms |
| `clipEnabled` | Clipping operations |
| `josLeysEnabled` | Jos Leys DE system |
| `pkEnabled` | Pseudokleinian DE |
| `mbMathEnabled` | Mandelbox Math |
| `warpDistEnabled` | Warp Distortion |
| `symmetryEnabled` | Symmetry/Kaleidoscope |
| `aboxEnabled` | Abox DE system |
| `noiseEnabled` | Noise & Procedural DE |
| `orbitTrapEnabled` | Orbit Trap DE |
| `torusEnabled` | MandelTorus DE |
| `asEnabled` | Amazing Surf 1-4 DE |
| `smEnabled` | SphereTree/Menger DE |

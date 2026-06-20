# Phase 3 — CPU/GPU DE case parity (2026-06-19)

## Doel

Alle DE-subsystem switch cases op GPU synchroniseren met CPU (`compute_fractal.cpp`).

## Aanpak

1. **`migrate_gpu_flat_to_nested.py`** — flat `mut->josFactor` etc. → nested `mut->josLeys.factor` (499 replacements)
2. **`port_cpu_de_cases.py`** — ontbrekende cases CPU→GPU geconverteerd (1165 cases)

## Resultaat scanner

| Metric | Vóór | Na |
|--------|------|-----|
| CRITICAL | 11 | **0** |
| CASE_MISSING_GPU | 11 | **0** |
| HIGH | 4–9 | 4 (LOG_DOMAIN heuristiek) |

## Gedeeltelijk gedeployed

- `opencl/engines/compute_fractal.cl` — volledig bijgewerkt
- `initparameters.cpp` — type max ranges aligned met enum max (100/200/300)
- UI combo's tonen nog ~30 items — types 31+ werken via .fract/load; UI-update later

## Tools

```bash
python3 mutations/codegen/migrate_gpu_flat_to_nested.py --apply
python3 mutations/codegen/port_cpu_de_cases.py --all --apply
python3 mutations/codegen/mutation_scanner.py
```

## Incident

Tijdens port is `compute_fractal.cl` per ongeluk via `git checkout` teruggezet naar oude flat-field versie. Hersteld via migrate + port scripts.

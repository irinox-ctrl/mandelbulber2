# Mutation Extension Contract

*Foundation gate — geen nieuw subsysteem zonder deze checklist.*

## Doel

Elke nieuwe mutation-subsystem wijziging moet de volledige keten synchron houden:

```
UI widget ↔ param name ↔ initparameters ↔ nine_fractals load ↔ struct field
  ↔ CPU compute_fractal ↔ OpenCL compute_fractal ↔ nebula (indien van toepassing)
  ↔ gray-out / enabled state
```

## Checklist per subsysteem

| # | Laag | Vereist | Audit |
|---|------|---------|-------|
| 1 | Param | `addParam("mutation_*")` in `initparameters.cpp` | `mutation_audit.py --ci` |
| 2 | Enabled | Eén canonical `mutation_<system>_enabled`; legacy alias alleen via `LoadMutationEnabled()` | `mutation_enabled_aliases.json` |
| 3 | Load | `nine_fractals.cpp` leest alle params → `sFormulaMutationParams` | `mutation_audit.py` |
| 4 | Validate | `ValidateMutationParams()` clamped ranges + iter start≤stop | runtime |
| 5 | OpenCL copy | veld in `CopyToOpenclData` / `mutation_params_subsystems.cpp` | handmatig / later schema |
| 6 | CPU math | switch/case in `compute_fractal.cpp` | `tri_engine_parity.py --ci` |
| 7 | GPU math | switch/case in `compute_fractal.cl` | `tri_engine_parity.py --ci` |
| 8 | Nebula | expliciet `partial` of `absent` in `subsystem_engine_map.json` | `tri_engine_parity.py` |
| 9 | UI combo | items ≥ param max + 1 | `combo_audit.py --ci` |
| 10 | UI gray-out | groupCheck + `grayOutGroupSystem` + registry binding | `ui_audit.py --ci` |
| 11 | Safety | geen bare div/log zonder guard (heuristic) | `mutation_scanner.py --ci` |

## Nebula-regel

Nebula ondersteunt **alleen** clip, inversion, clamp, jb, md vandaag.

- Nieuwe DE-subsystemen → **niet** automatisch naar nebula porten
- Documenteer `nebula: absent` in `config/subsystem_engine_map.json`
- Gebruiker moet weten dat nebula-rendering andere mutation-stack heeft

## CI-minimum (lokaal)

```bash
cd mandelbulber2
python3 mutations/codegen/run_all_audits.py --ci
```

## Wanneer mag je uitbreiden?

Pas nieuwe mutation-math toevoegen als:

1. Param registered + loaded + UI/gray-out OK
2. CPU/GPU parity bewezen (`tri_engine_parity --ci`)
3. Nebula-expectation expliciet
4. `run_all_audits.py --ci` groen

## Codegen (later)

Schema-first generatie is **experimenteel** (`mutations/STATUS.md`). Runtime handmatig blijft waarheid tot één subsysteem-pilot bewezen is.

# Mutation System — Status & Source of Truth

*Laatst bijgewerkt: 2026-06-22*

## Executive summary

| Laag | Status | Bron van waarheid |
|------|--------|-------------------|
| **Runtime (actief)** | Productie | Handmatig in C++/OpenCL |
| **Codegen (.mut → .inc)** | Actief (pilot) | `mutations/systems/` + `generate_switch.py` |
| **Param codegen** | Actief | `mutations/codegen/param_codegen.py` |
| **Safety budget** | Actief | `mutations/codegen/safety_budget.py` |
| **Scanner (audit)** | Actief v2 | `mutations/codegen/mutation_scanner.py` |

De renderer gebruikt **handmatige** switch/case-logica in:

- `src/compute_fractal.cpp`
- `opencl/engines/compute_fractal.cl`
- `opencl/engines/nebula.cl`
- `src/nine_fractals.{hpp,cpp}`
- `src/initparameters.cpp`
- `qt/dock_mutation_tab.cpp`

De gegenereerde `.inc` snippets in `mutations/generated/` zijn **referentie/diff-materiaal** voor
handmatige integratie of toekomstige geautomatiseerde injectie — ze worden *niet* automatisch
`#include`'d door de runtime.

## Beslissing

**Korte termijn:** handmatige runtime blijft source of truth.

**Middellange termijn:** schema-first codegen is actief voor `inversion` en `clip` als piloten.
Nieuwe subsystemen kunnen via `mutation_wizard.py` + `generate_switch.py` worden opgezet.

**Niet doen:** beide parallel als "waarheid" presenteren zonder duidelijke STATUS.

## Fase-voortgang

| Fase | Doel | Status |
|------|------|--------|
| 0 | UI XML validatie PR-risico | ✅ zie `audit/PHASE0_UI.md` |
| 1 | Scanner betrouwbaar + smoke test | ✅ v2 + `--ci-smoke` |
| 2 | Source-of-truth documentatie + schema stub | ✅ dit bestand + `config/mutation_schema.example.yaml` |
| 3 | CPU/GPU DE case parity (compute_fractal.cl) | ✅ incl. inversion 31–50 |
| 4 | Nebula scoped parity assessment | ✅ zie `audit/PHASE4_NEBULA_PARITY.md` |
| 5 | UI gray-out / widget audit | ✅ zie `audit/UI_AUDIT.md` |
| 6 | Tri-engine parity report | ✅ zie `audit/TRI_ENGINE_PARITY.md` |
| 7 | Subsystem `.inc` split (codegen pilot) | ✅ `systems/inversion/*.mut` + `generate_switch.py --all` |
| 8 | Param reg/read/copy generatie | ✅ `param_codegen.py` — registry → C++/OpenCL snippets |
| 9 | Safety budget | ✅ `safety_budget.py` — per-categorie budget tracker |
| 10 | UI binding audit in CI | ✅ `ui_audit.py --ci` |
| 11 | Volledige CI pipeline | ✅ `run_all_audits.py --ci` (nu met phases 7–9) |
| 12 | Formula registry audit (C++/OpenCL/UI/enum) | ✅ `formula_audit.py --ci` |

## Codegen pipeline — hoe het werkt

### Phase 7: .mut → .inc (generate_switch.py)

```
mutations/systems/<system>/*.mut
  → generate_switch.py --system <system>
    → mutations/generated/<system>_cpu.inc
    → mutations/generated/<system>_gpu.inc
```

Pilot systemen: `inversion` (8 types), `clip` (te starten via mutation_wizard.py)

Validatie (in CI):
```bash
python3 mutations/codegen/generate_switch.py --all --validate-only
```

Genereren:
```bash
python3 mutations/codegen/generate_switch.py --system inversion
python3 mutations/codegen/mutation_wizard.py --batch-add 5 --system clip --template distance_field
python3 mutations/codegen/mutation_wizard.py --full-rebuild
```

### Phase 8: Registry → C++ snippets (param_codegen.py)

```
mutations/config/mutation_registry.json
  → param_codegen.py --system inversion --target all
    → mutations/generated/inversion_initparams.cpp.inc
    → mutations/generated/inversion_reads.cpp.inc
    → mutations/generated/inversion_struct.hpp.inc
    → mutations/generated/inversion_gpu_struct.h.inc
    → mutations/generated/inversion_copy.cpp.inc
```

CI validatie (alleen schema-check, geen code generatie):
```bash
python3 mutations/codegen/param_codegen.py --ci
```

Snippets genereren (voor review/integratie):
```bash
python3 mutations/codegen/param_codegen.py --all --out mutations/generated/
```

Schema uitbreiden: voeg een nieuw systeem toe aan `config/mutation_registry.json` met
de juiste `initparam_blocks` array.

### Phase 9: Safety budget (safety_budget.py)

```
compute_fractal.cpp + compute_fractal.cl + nebula.cl
  → safety_budget.py
    → rapport per categorie (DOUBLE_IN_GPU, DIV_ZERO, LOG_DOMAIN, ...)
    → vergelijking met config/safety_budget.json
```

Budget initialiseren (eenmalig):
```bash
python3 mutations/codegen/safety_budget.py --update-budget
```

CI check:
```bash
python3 mutations/codegen/safety_budget.py --ci
```

Budget aanpassen (veiliger maken):
- Edit `config/safety_budget.json` en verlaag de limieten
- Voer `--ci` opnieuw uit om te verifiëren

## Parity status (2026-06-22)

- **Enabled flags:** UI canonical names via `LoadMutationEnabled()` — zie `config/mutation_enabled_aliases.json`
- **compute_fractal.cl:** 18/18 secties volledig vs CPU (inversion 31–50 geporteerd uit nebula)
- **nebula.cl:** 5/18 secties by design — assessment in `audit/PHASE4_NEBULA_PARITY.md`
- **UI wiring:** 0 issues — `audit/UI_AUDIT.md`
- **Tri-engine matrix:** `audit/TRI_ENGINE_PARITY.md`

## Oude baseline (opgelost)

~~GPU mist extra cases 31+ (DE subsystems)~~ — opgelost via `port_cpu_de_cases.py`

**Nog open:** nebula mist 13 DE-subsystems by design (gedocumenteerd).

## CI-aanbeveling

```bash
cd mandelbulber2
python3 mutations/codegen/run_all_audits.py --ci
```

Individual checks:

```bash
cd mandelbulber2
# Phases 0–6, 10–12
python3 mutations/codegen/test_scanner_smoke.py
python3 mutations/codegen/mutation_scanner.py --ci-smoke
python3 mutations/codegen/mutation_scanner.py --validate-ui
python3 mutations/codegen/mutation_audit.py --ci
python3 mutations/codegen/ui_audit.py --ci
python3 mutations/codegen/combo_audit.py --ci
python3 mutations/codegen/julia_audit.py --ci
python3 mutations/codegen/tri_engine_parity.py --ci
python3 mutations/codegen/formula_audit.py --ci
# Phase 7
python3 mutations/codegen/generate_switch.py --all --validate-only
# Phase 8
python3 mutations/codegen/param_codegen.py --ci
# Phase 9
python3 mutations/codegen/safety_budget.py --ci
```

Strengere gate (math heuristics only):

```bash
python3 mutations/codegen/mutation_scanner.py --ci   # 0 CRITICAL/HIGH
```

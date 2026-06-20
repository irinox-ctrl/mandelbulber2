# Mutation System — Status & Source of Truth

*Laatst bijgewerkt: 2026-06-19*

## Executive summary

| Laag | Status | Bron van waarheid |
|------|--------|-------------------|
| **Runtime (actief)** | Productie | Handmatig in C++/OpenCL |
| **Codegen (.mut → .inc)** | Experimenteel | Niet geactiveerd |
| **Scanner (audit)** | Actief v2 | `mutations/codegen/mutation_scanner.py` |

De renderer gebruikt **handmatige** switch/case-logica in:

- `src/compute_fractal.cpp`
- `opencl/engines/compute_fractal.cl`
- `opencl/engines/nebula.cl`
- `src/nine_fractals.{hpp,cpp}`
- `src/initparameters.cpp`
- `qt/dock_mutation_tab.cpp`

De map `mutations/systems/`, `mutations/generated/` en `config/mutation_registry.json` **bestaan nog niet**. Codegen-tools zijn voorbereid maar niet wired-in.

## Beslissing (Phase 2)

**Korte termijn:** handmatige runtime blijft source of truth.

**Middellange termijn:** schema-first codegen (Phase 2–4 plan) — één subsystem als pilot vóór volledige migratie.

**Niet doen:** beide parallel als “waarheid” presenteren zonder duidelijke STATUS.

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
| 7 | Subsystem `.inc` split (codegen pilot) | ⏸ on hold |
| 8 | Param reg/read/copy generatie | ⏸ on hold |
| 9 | Fuzz / safety budget | ⏸ on hold |
| 10 | UI binding audit in CI | ✅ `ui_audit.py --ci` |
| 11 | Volledige CI pipeline | ✅ `run_all_audits.py --ci` |
| 12 | Formula registry audit (C++/OpenCL/UI/enum) | ✅ `formula_audit.py --ci` |

## Parity status (2026-06-19)

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
python3 mutations/codegen/test_scanner_smoke.py
python3 mutations/codegen/mutation_scanner.py --ci-smoke
python3 mutations/codegen/mutation_scanner.py --validate-ui
python3 mutations/codegen/mutation_audit.py --ci
python3 mutations/codegen/ui_audit.py --ci
python3 mutations/codegen/combo_audit.py --ci
python3 mutations/codegen/julia_audit.py --ci
python3 mutations/codegen/tri_engine_parity.py --ci
python3 mutations/codegen/formula_audit.py --ci
```

Strengere gate (math heuristics only):

```bash
python3 mutations/codegen/mutation_scanner.py --ci   # 0 CRITICAL/HIGH
```

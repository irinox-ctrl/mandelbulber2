# Phase 0 — UI validatie (2026-06-19)

## Scope

Validatie van het PR-risico rond `dock_effects.ui` en `spinboxd_glow_sphere_1_weight`.

## Resultaat op huidige branch

| Check | Status |
|-------|--------|
| `mandelbulber2/qt/dock_effects.ui` XML parse (Python ElementTree) | OK (303 regels) |
| `spinboxd_glow_sphere_1_weight` in repo | **Niet aanwezig** op deze branch |
| `glow_sphere_1_weight` parameter in `initparameters.cpp` | **Niet geregistreerd** |

Glow-sphere parameters op deze branch: `glow_sphere_1_enabled`, `position`, `rotation`, `radius`, `color`, `intensity`, `falloff_radius`, `outer_color`, `pulse_speed`, `pulse_amount` — geen `weight`.

## Conclusie

Het beschreven PR-probleem (regel ~4994, ontbrekende `</widget>`, `spinboxd_glow_sphere_1_weight`) geldt **niet** voor de huidige werkbranch. Waarschijnlijk een andere PR/branch.

**Actie bij merge van die PR:** XML valideren + parameter wiring controleren vóór merge.

## Gevalideerde mutation UI

| Bestand | XML |
|---------|-----|
| `qt/dock_mutation_tab.ui` | OK |

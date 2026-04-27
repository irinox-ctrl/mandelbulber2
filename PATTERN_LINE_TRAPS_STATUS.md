# Patroonlijnen — profielvormen (huidige status)

**Statusdatum:** 2026-04-24  

- **Aantal vormen:** **50** (indices `0` … `49` op parameter `pattern_line_trap_*_shape`).
- **CPU:** `mandelbulber2/src/pattern_line_traps.hpp` — `PatternLineTrapCrossSectionSigned`, `PatternLineTrapProfileExtent`, en 2D-SDF-hulpfuncties.
- **OpenCL:** `mandelbulber2/opencl/engines/shader_pattern_line_traps.cl` — dezelfde `case`s en extent-regels.
- **Parameters / clamp:** `initparameters.cpp` (QStringList in UI), `fractparams.cpp` clamp `shape` t/m **49**.
- **UI:** `mandelbulber2/qt/dock_pattern_lines.ui` — uitgebreide hint onderaan; **tooltips** op het groepskader, workflow, solo, preset-label, en per veld op **alle 20 lagen** via `dock_pattern_lines.cpp` (`SetupPatternLineLayersTooltips`).

Dit is het referentie-ankerpunt om bij een backup / restore te verifiëren dat patroonlijn-profielen met deze 50 vormen en de UI-tips aanwezig zijn.

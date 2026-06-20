# Formula Freeze Policy

*Strategische regel voor mutation-as-core.*

## Principe

**Nieuwe creatieve variatie → mutation presets, niet nieuwe formule-clones.**

Bestaande formules zijn stabiele **base kernels**. Het mutatiesysteem is de creatieve laag.

## Wat is toegestaan

- Bugfixes in bestaande formules (CPU/GPU parity, NaN guards)
- Base primitives die echt nieuw zijn (zeldzaam, review verplicht)
- Mutation subsystem uitbreiding (via extension contract)

## Wat is **niet** toegestaan zonder expliciete review

- Nieuwe `fractal_*` varianten die alleen een fold/warp/inversion combo dupliceren
- Handmatige formula-explosie (1000+ bestanden onderhouden)
- UI/OpenCL/C++ triple-copy van hetzelfde gedrag

## Aanbevolen workflow

```
base formula + mutation profile = nieuw gedrag
```

Gebruik mutation presets (`.fract` met mutation params) i.p.v. nieuwe formula enums.

## Audit

`mutations/codegen/formula_audit.py` — matrix: C++ def / OpenCL / UI / enum / share-sync.

```bash
cd mandelbulber2
python3 mutations/codegen/formula_audit.py --ci
```

Allowlist bekende gaps: `mutations/config/formula_audit_allowlist.json`  
Rapport: `mutations/audit/FORMULA_AUDIT.md`

**Freeze:** baseline registry count in allowlist; nieuwe formules vereisen expliciete review + baseline update.

## Base families (referentie)

Mandelbulb, Mandelbox, Menger, kaleidoscopic IFS, pseudo-kleinian, amazing surf/box, torus/DIFS, Julia-capable bases, sandbox.

Creative variants → mutation, niet formula file #1009+.

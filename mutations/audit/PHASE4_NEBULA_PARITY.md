# Nebula Mutation Parity Assessment

*Read-only scan — geen code gewijzigd.*

## Samenvatting

| Engine | Mutation sections | Opmerking |
|--------|-------------------|-----------|
| CPU | 18 | Bron |
| compute_fractal.cl | 18 | Volledige DE-stack |
| nebula.cl | 5 | Bewust beperkte stack |

Nebula implementeert **niet** de volledige mutatie-DE-stack. Dat is verwacht voor nebula-rendering: alleen transform-gerelateerde subsystems + v7.14 tail.

## Secties aanwezig in nebula.cl

| Sectie | Nebula cases | CPU cases | Gap vs CPU |
|--------|-------------|-----------|------------|
| v7.6 Clip | 100 | 100 | 0 |
| v7.6 Inversion | 50 | 50 | 0 |
| v7.14 T Clamp | 50 | 50 | 0 |
| v7.14 T Julia Box | 50 | 50 | 0 |
| v7.14 T Mandalay | 50 | 50 | 0 |

## Secties afwezig in nebula (13 subsystems)

Jos Leys, Pseudokleinian, Mandelbox Math, Warp Distortion, Symmetry, Abox DE, Noise, Orbit Trap, MandelTorus, Amazing Surf, SphereTree/Menger, Blockify, Tile.

**Impact:** als gebruiker deze subsystems inschakelt en nebula-rendering gebruikt, worden ze **niet** toegepast in de nebula-kernel. Fractal GPU (`compute_fractal.cl`) wel (behalve bekende inv-gap hieronder).

## Opvallend: inversion parity

- **CPU:** 50 inversion types (cases 1–50)
- **nebula.cl:** 50 — volledig
- **compute_fractal.cl:** 30 — **cases 31–50 ontbreken**

Dit is een echte fractal-GPU gap (niet nebula). Zie `TRI_ENGINE_PARITY.md`.

## Aanbevolen vervolg (voorzichtig)

1. **Geen bulk-port** van alle CPU-secties naar nebula.
2. **Wel fixen:** ~~inversion cases 31–50 in `compute_fractal.cl`~~ ✅ gedaan (2026-06-19)
3. **UI/UX:** overweeg waarschuwing wanneer nebula actief is en niet-ondersteunde mutation-subsystems aan staan.
4. Her-run: `python3 mutations/codegen/tri_engine_parity.py`

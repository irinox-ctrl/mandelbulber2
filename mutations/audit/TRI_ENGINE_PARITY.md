# Tri-Engine Mutation Parity

- CPU sections: `18`
- compute_fractal.cl sections: `18`
- nebula.cl sections: `5`

## Subsystem matrix

| ID | CPU cases | CF | Nebula | Expectation | Status |
|----|-----------|----|--------|-------------|--------|
| `clip` | 100 | 100 | 100 | partial | OK_ALL_ENGINES |
| `inv` | 50 | 50 | 50 | partial | OK_ALL_ENGINES |
| `jos` | 100 | 100 | 0 | absent | OK_FRACTAL_ONLY |
| `pk` | 100 | 100 | 0 | absent | OK_FRACTAL_ONLY |
| `mb` | 200 | 200 | 0 | absent | OK_FRACTAL_ONLY |
| `wd` | 100 | 100 | 0 | absent | OK_FRACTAL_ONLY |
| `sk` | 100 | 100 | 0 | absent | OK_FRACTAL_ONLY |
| `ab` | 400 | 400 | 0 | absent | OK_FRACTAL_ONLY |
| `noise` | 100 | 100 | 0 | absent | OK_FRACTAL_ONLY |
| `orbit` | 100 | 100 | 0 | absent | OK_FRACTAL_ONLY |
| `torus` | 100 | 100 | 0 | absent | OK_FRACTAL_ONLY |
| `as` | 100 | 100 | 0 | absent | OK_FRACTAL_ONLY |
| `sm` | 100 | 100 | 0 | absent | OK_FRACTAL_ONLY |
| `clamp` | 50 | 50 | 50 | partial | OK_ALL_ENGINES |
| `jb` | 50 | 50 | 50 | partial | OK_ALL_ENGINES |
| `md` | 50 | 50 | 50 | partial | OK_ALL_ENGINES |
| `blockify` | 8 | 8 | 0 | absent | OK_FRACTAL_ONLY |
| `tile` | 8 | 8 | 0 | absent | OK_FRACTAL_ONLY |

## Actionable compute_fractal gaps

_None — compute_fractal matches CPU for all checked subsystems._

## Nebula notes

Nebula intentionally omits DE-heavy subsystems (jos, pk, mb, wd, sk, ab, noise, orbit, torus, as, sm, blockify, tile). Only clip, inversion, clamp, jb, md are expected in nebula today.

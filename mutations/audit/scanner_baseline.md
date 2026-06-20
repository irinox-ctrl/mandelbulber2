# Mutation Scanner Report

- GPU struct: 5.3 KB
- Issues: 723

## Counts by severity

- **CRITICAL**: 0
- **HIGH**: 4
- **MEDIUM**: 719
- **LOW**: 0

## Counts by category

- `DE_UNBOUNDED`: 312
- `DIV_ZERO`: 393
- `LOG_DOMAIN`: 4
- `NO_ITER_GUARD`: 14

## CRITICAL + HIGH

- `LOG_DOMAIN` compute_fractal.cl:5627 — log(n) — argument may be zero or negative
- `LOG_DOMAIN` compute_fractal.cl:5627 — log(n) — argument may be zero or negative
- `LOG_DOMAIN` compute_fractal.cpp:4157 — log(n) — argument may be zero or negative
- `LOG_DOMAIN` compute_fractal.cpp:4157 — log(n) — argument may be zero or negative

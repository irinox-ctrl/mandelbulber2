# Formula Registry Audit

*Generated: 2026-06-19*

## Summary

| Metric | Value |
|--------|-------|
| Registered formulas | 1009 |
| Baseline (freeze) | 1009 |
| With C++ definition | 1009/1009 |
| With OpenCL | 1005/1009 |
| With UI | 1005/1009 |
| Critical issues | 0 |
| Warnings | 0 |

## CI policy

- **CRITICAL (fail `--ci`):** registered formula missing cpp/opencl/ui, enum drift, share sync
- **WARN:** orphan assets, registry count drift, unallowlisted unused enums
- **Allowlist:** `mutations/config/formula_audit_allowlist.json`

## Known gaps (allowlisted)

- Missing OpenCL: `none, custom, transf_demo_scale_v2, transf_wizard_demo`
- Missing UI: `none, custom, transf_demo_scale_v2, transf_wizard_demo`

## Issues

*No critical or warning issues.*

## Tooling

```bash
cd mandelbulber2
python3 mutations/codegen/formula_audit.py --ci
python3 mutations/codegen/formula_audit.py --markdown mutations/audit/FORMULA_AUDIT.md
```

# Combo Sync Status

*Audit: `combo_audit.py`*

## Runtime fix (2026-06-19)

`dock_mutation_tab.cpp` pads type combos at Init/Sync:

- Existing named items (None, Ellipsoid, …) stay unchanged
- Missing indices get generic label `Type N` up to param max

Static `combo_audit.py` still counts `.ui` XML items only (expected WARN debt in file audit).

## CI policy

- **FAIL:** type param registered but no `comboBox_mutation_*` widget
- **WARN (known debt):** combo has fewer labeled items than param max allows

Saved `.fract` files can still use types above the combo label count; runtime accepts them via `initparameters` max.

## Known UI label gaps (2026-06-19)

Many DE subsystems register max 100–300 types but UI combos show ~31 named entries (+ None).

| Param | Param max | Typical combo items |
|-------|-----------|---------------------|
| `mutation_abox_type` | 300 | 31 |
| `mutation_mb_math_type` | 200 | 31 |
| `mutation_*_type` (100-max) | 100 | 31 or 51 |

**Not a runtime parity bug** — CPU/GPU cases exist (`tri_engine_parity --ci` green).

**Is a UX gap** — users cannot pick high type indices from combo without editing `.fract`.

## Planned fix (not blocking foundation)

Runtime combo padding in `dock_mutation_tab.cpp`:

```cpp
// Ensure combo count >= param max + 1; add generic "Type N" labels
```

Or schema-generated combo item lists.

## Until then

Run `python3 mutations/codegen/combo_audit.py` to see current gap list.

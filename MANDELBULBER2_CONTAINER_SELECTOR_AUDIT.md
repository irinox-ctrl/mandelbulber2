# MANDELBULBER2 CONTAINER SELECTOR: Developer Guide

**Datum**: 2026-04-22  
**Bestanden**: `container_selector.hpp`, `container_selector.cpp`  
**Scope**: Parameter container routing — resolves "main_foo" or "fractal2_bar" to the correct `cParameterContainer`  
**Focus**: Naming convention parsing, fractal index extraction, and edge cases  

---

## 1. Purpose

`container_selector` is a **tiny but critical routing layer**. It translates string-based parameter names into the correct `cParameterContainer` pointer. This enables the rest of the system to use fully-qualified names like:

```
main_camera_x                    → main params container
fractal0_mandelbulb_power        → fractal container #0
fractal2_transformCommon_scale   → fractal container #2
```

Without this layer, every parameter read/write would need manual container selection.

---

## 2. API

### 2.1 `ContainerSelector(fullParameterName, params, fractal)`

```cpp
std::shared_ptr<cParameterContainer> ContainerSelector(
    QString fullParameterName,
    std::shared_ptr<cParameterContainer> params,
    std::shared_ptr<cFractalContainer> fractal);
```

**Parsing rule**: Split `fullParameterName` at the **first underscore**:
```cpp
int firstDashIndex = fullParameterName.indexOf("_");
QString containerName = fullParameterName.left(firstDashIndex);
```

| Input | `containerName` | Result |
|-------|----------------|--------|
| `main_camera_x` | `main` | `params` |
| `fractal0_power` | `fractal0` | `fractal->at(0)` |
| `fractal3_color` | `fractal3` | `fractal->at(3)` |
| `nounderscore` | `nounderscore` (entire string) | `nullptr` + warning |

### 2.2 `ContainerSelectorByContainerName(containerName, params, fractal)`

Same logic, but takes the already-extracted `containerName` directly. Useful when the caller has already parsed the name.

---

## 3. Fractal Index Extraction

```cpp
else if (containerName.indexOf("fractal") >= 0) {
    const int index = containerName.right(1).toInt();
    if (index < NUMBER_OF_FRACTALS) {
        container = fractal->at(index);
    }
}
```

**How it works**:
1. Checks if `"fractal"` appears **anywhere** in the container name
2. Takes the **last character** with `right(1)`
3. Converts to integer with `toInt()`

**Examples**:
| `containerName` | `indexOf("fractal")` | `right(1)` | `toInt()` |
|----------------|---------------------|-----------|-----------|
| `fractal0` | 0 | `"0"` | 0 |
| `fractal3` | 0 | `"3"` | 3 |
| `fractal10` | 0 | `"0"` | 0 ← **only last digit!** |
| `myfractal5` | 2 | `"5"` | 5 ← **substring match!** |
| `fractal` | 0 | `"l"` | 0 ← **no digit = 0!** |

---

## 4. Edge Cases & Behavior

### 4.1 No Underscore in Name

```cpp
int firstDashIndex = fullParameterName.indexOf("_");  // returns -1
QString containerName = fullParameterName.left(-1);   // returns entire string
```

Per Qt documentation, `QString::left(-1)` returns the **entire string**. So `containerName` becomes the full parameter name, which won't match "main" or contain "fractal", resulting in a warning and `nullptr`.

**Behavior**: Safe — falls through to warning + nullptr.

### 4.2 `toInt()` on Non-Digit

```cpp
"fractal".right(1)   → "l"
"l".toInt()          → 0 (Qt returns 0 on failure, with *ok = false)
```

`toInt()` without the `ok` parameter returns 0 on failure. So `"fractal"` (no digit) maps to index 0. This is **silent** — no warning is issued if the conversion fails.

**Behavior**: `"fractal"` → index 0 → `fractal->at(0)`. Could be surprising.

### 4.3 Multiple Underscores

Only the **first** underscore matters:
```cpp
"main_foo_bar_baz"
  └─ containerName = "main"
     └── routed to main params
```

The remaining `_foo_bar_baz` is ignored by the selector — it's the parameter name within the container.

---

## 5. Known Issues

### ISSUE-1: Single-digit index limitation

`containerName.right(1).toInt()` can only extract indices 0-9. If `NUMBER_OF_FRACTALS` ever exceeds 10, containers `fractal10`+ would incorrectly map to index `0` (the last digit).

**Mitigation**: `NUMBER_OF_FRACTALS` is currently 5 (from `HYBRID_COUNT`), so this is not a practical problem.

**Fix if needed**:
```cpp
// Extract all trailing digits
int digitStart = containerName.length();
while (digitStart > 0 && containerName[digitStart - 1].isDigit()) digitStart--;
int index = containerName.mid(digitStart).toInt();
```

### ISSUE-2: Substring matching

`containerName.indexOf("fractal") >= 0` matches any name containing "fractal" as a substring:
- `myfractal2` → matched
- `fractalized` → matched

In practice, container names are well-controlled, but this is looser than an exact prefix check.

**Fix**:
```cpp
else if (containerName.startsWith("fractal"))  // stricter
```

### ISSUE-3: Silent `toInt()` failure

When the last character is not a digit, `toInt()` returns 0 without error. `"fractal"` silently maps to index 0.

**Fix**:
```cpp
bool ok;
int index = containerName.right(1).toInt(&ok);
if (!ok) { qWarning() << "..."; return nullptr; }
```

### ISSUE-4: Code duplication

The two functions share ~90% identical logic. The only difference is:
- `ContainerSelector`: extracts `containerName` from `fullParameterName`
- `ContainerSelectorByContainerName`: uses `containerName` directly

**Refactoring opportunity**: Extract the common routing logic:
```cpp
static std::shared_ptr<cParameterContainer> RouteContainer(
    const QString &containerName,
    std::shared_ptr<cParameterContainer> params,
    std::shared_ptr<cFractalContainer> fractal)
{
    // shared logic here
}
```

---

## 6. Security & Robustness

| Concern | Status | Note |
|---------|--------|------|
| Nullptr return | ✅ Handled | Returns `nullptr` + warning for unknown names |
| Out-of-bounds index | ✅ Handled | Checked against `NUMBER_OF_FRACTALS` |
| Empty string | ⚠️ Silent | `""` doesn't match anything → nullptr + warning |
| Integer overflow | ✅ Not possible | Only single digit extracted |
| Memory safety | ✅ Safe | Uses `shared_ptr`, no raw pointers |

---

## 7. Usage Context

This module is called from:
- **Parameter serialization** (save/load settings files)
- **UI synchronization** (automated_widgets, synchronize_interface)
- **Animation/keyframe systems** (when interpolating fractal-specific parameters)
- **Command-line interface** (when overriding parameters)

Any change to the naming convention or parsing logic would ripple through the entire parameter system.

---

## 8. Extension Guide

### Adding a New Container Type

If you need to route parameters to a new container (e.g., `materials`):

```cpp
else if (containerName.startsWith("material"))
{
    const int index = containerName.right(1).toInt();
    if (index < NUMBER_OF_MATERIALS) {
        container = materials->at(index);
    }
}
```

### Supporting Multi-Digit Indices

Replace the single-digit extraction:
```cpp
// Before
const int index = containerName.right(1).toInt();

// After
int digitPos = containerName.length() - 1;
while (digitPos >= 0 && containerName[digitPos].isDigit()) digitPos--;
const int index = containerName.mid(digitPos + 1).toInt();
```

---

## 9. Summary

`container_selector` is a **small, focused name-to-pointer resolver**. It does one thing and does it adequately for the current scope (≤10 fractals, controlled naming). The main weaknesses are:

1. **Single-digit index extraction** — would break if fractal count exceeds 10
2. **Loose substring matching** — `indexOf("fractal")` is too permissive
3. **Silent `toInt()` failures** — non-digit suffixes map to index 0
4. **Code duplication** — two nearly identical functions

None of these are critical for the current system, but they represent technical debt if the fractal container architecture ever expands.

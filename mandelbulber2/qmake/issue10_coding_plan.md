# CodeRabbit Coding Plan — Issue #10
Julia Beauty Finder: async scan + mutation performance fixes

---

<!-- This is an auto-generated reply by CodeRabbit -->
## Coding Plan

### Summary

- Phases 0-3 address the original ticket: async beauty scanning via `QtConcurrent::run` with `QFutureWatcher`, CPU mutation optimization by gating `preMutZ` and NaN checks behind `mut.enabled`, and OpenCL hardening with ±25.0f clamps on ExpMap/LogSpiral `native_exp` calls
- Phases 4-7 implement optional foundational enhancements: double-single emulation for deep zoom (with strict performance isolation), palette buffer sync for gradient bugs, batch UI updates for loading, and adaptive mutation with consolidated fold logic

<details>
<summary><b>Design Choices</b></summary>

<details>
<summary><b>Design Choice 1: Beauty Finder symbols do not exist yet</b></summary>



**Options Considered:**
1. Create all new symbols from scratch as part of this ticket
2. Assume a base PR branch contains these symbols and this ticket modifies them

**Chosen Option:** 1

**Rationale:** Create the async infrastructure and new symbols, as the ticket describes adding them and the current codebase has no equivalent functionality.

</details>

<details>
<summary><b>Design Choice 2: OpenCL line numbers differ from ticket</b></summary>



**Options Considered:**
1. Target only the three specific calls mentioned regardless of actual line numbers
2. Target all unguarded `native_exp` calls found in exploration

**Chosen Option:** 1

**Rationale:** Target ExpMap (1531, 3040) and LogSpiral (1549, 3058) as these match the described "mathP1 log-exp" and "newR spiral" contexts; the "juliaC exponential" reference appears to be a documentation error in the ticket.

</details>

<details>
<summary><b>Design Choice 3: Iteration cap implementation</b></summary>



**Options Considered:**
1. Rename existing function and add parameter-based iteration cap
2. Create new `ComputeQuickScoreReal` alongside existing function
3. Modify existing `ComputeQuickScore` to use `std::min(60, pr.N)` pattern

**Chosen Option:** 3

**Rationale:** Modify existing `ComputeQuickScore` to use a configurable cap based on fractal parameters, as the function already exists and serves this purpose.

</details>

</details>

<b>💡 User Tips</b>

Regenerate the plan with different choices with `@coderabbitai <feedback>`.


## Implementation Steps


### Phase 1: Environment Setup and Prerequisites

Establish the development environment with all required dependencies for building and testing the Mandelbulber application.


<details>
<summary><b>Task 1: Install System Dependencies</b></summary>

Install required system packages for Qt5, OpenCL, and build tools.

- For Ubuntu/Debian: install `build-essential cmake git qtbase5-dev qttools5-dev qttools5-dev-tools libqt5svg5-dev ocl-icd-opencl-dev opencl-headers libpng-dev libjpeg-dev libtiff-dev libgsl-dev`
- For Fedora/RHEL: install `cmake gcc-c++ git qt5-qtbase-devel qt5-qttools-devel qt5-qtsvg-devel ocl-icd-devel opencl-headers libpng-devel libjpeg-devel libtiff-devel gsl-devel`

</details>


<details>
<summary><b>Task 2: Clone and Configure Build Environment</b></summary>

Set up the project directory structure and configure CMake.

- Clone repository and create out-of-source build directory
- Run `cmake .. -DCMAKE_BUILD_TYPE=Debug` to configure
- Verify configuration shows Qt5 and OpenCL found

</details>


<details>
<summary><b>Task 3: Build and Verify Installation</b></summary>

Compile the application and verify it launches correctly.

- Run `make -j$(nproc)` from build directory
- Launch `./mandelbulber2` and verify GUI opens
- Confirm Julia Explorer panel accessible and fractal renders

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
This phase sets up the development environment and does not require code
generation. Follow the shell commands in each task to install dependencies (Qt5,
OpenCL, build tools), configure the CMake build in Debug mode, and verify the
application launches correctly with the Julia Explorer panel accessible before
proceeding to implementation phases.
```

</details>




### Phase 2: Async Beauty Scan Infrastructure

Create the asynchronous beauty scanning system in `cDockFractal` to enable non-blocking UI during parameter space exploration.


<details>
<summary><b>Task 1: Define Beauty Result Data Structure</b></summary>

Add the `sBeautyResult` struct to hold scan results for sorting and display.

- Add struct to `mandelbulber2/qt/dock_fractal.h` after line ~85 (near `sJuliaHistoryEntry`)
- Include fields: `double cx, cy, cz, score`
- Add `operator<` for descending sort by score

</details>


<details>
<summary><b>Task 2: Add Async Infrastructure Members and Slots</b></summary>

Extend `cDockFractal` with QtConcurrent support for background scanning.

- Add `#include <QtConcurrent/QtConcurrent>` to `dock_fractal.cpp` after existing includes
- Add `QFutureWatcher<QVector<sBeautyResult>> *beautyScanWatcher = nullptr` to private members in `dock_fractal.h`
- Add `void slotBeautyScanFinished()` to private slots section
- Initialize watcher in constructor and connect to `slotBeautyScanFinished`
- Add cleanup in destructor: cancel, wait, delete

</details>


<details>
<summary><b>Task 3: Implement Async Scan Function</b></summary>

Create a thread-safe free function that performs the beauty parameter scan without UI access.

- Add `static QVector<sBeautyResult> RunBeautyScanAsync(...)` before `cDockFractal` class implementation
- Parameters: cxMin/Max, cyMin/Max, czMin/Max, resolution, scoreFunc
- Iterate 3D grid of Julia C parameters, compute scores, return results vector

</details>


<details>
<summary><b>Task 4: Implement slotBeautyFindBest Entry Point</b></summary>

Create the slot that initiates async beauty scanning.

- Add `void slotBeautyFindBest()` to public slots in header
- Check if scan already running, return early if so
- Get range from `JuliaSliderRange()`, set resolution to 10 (1000 samples)
- Capture scoring function, launch via `QtConcurrent::run`, set future on watcher

</details>


<details>
<summary><b>Task 5: Implement Scan Completion Handler</b></summary>

Process async scan results and update UI when complete.

- Get results from watcher, return early if empty
- Sort by score descending using `std::sort`
- Select best result and update Julia C parameter text fields

</details>


<details>
<summary><b>Task 6: Add Auto-Trigger on Slider Release</b></summary>

Enable automatic beauty scanning when Julia sliders are released.

- Add `slotJuliaSliderReleased()` and `TriggerAutoBeauty()` declarations to private slots
- Connect `sliderReleased()` signals from all three Julia sliders to `slotJuliaSliderReleased`
- Implement `TriggerAutoBeauty()` to call `slotBeautyFindBest()`

</details>


<details>
<summary><b>Task 7: Cap Screening Iterations</b></summary>

Limit iteration count in quick scoring for performance during rapid scanning.

- In `ComputeQuickScore` standard path (~line 1050): replace `int maxIter = 64` with `int maxIter = std::min(60, gPar->Get<int>("N"))`
- In deep zoom path (~line 1010): replace `int maxIter = 1000` with `int maxIter = std::min(1000, gPar->Get<int>("N"))`

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
Implement the async beauty scanning infrastructure in `cDockFractal` across
`mandelbulber2/qt/dock_fractal.h` and `mandelbulber2/qt/dock_fractal.cpp`. The
goal is to introduce non-blocking UI behavior during Julia parameter space
exploration.

**Data Structure (`dock_fractal.h`)**
- Add `sBeautyResult` struct after line ~85, near `sJuliaHistoryEntry`,
containing: `cx`, `cy`, `cz` (double), `score` (double), and a comparison
`operator<` that sorts descending by score

**Class Members & Slots (`dock_fractal.h`)**
- Add private member: `QFutureWatcher<QVector<sBeautyResult>> *beautyScanWatcher
= nullptr`
- Add private slots: `void slotBeautyScanFinished()`, `void
slotJuliaSliderReleased()`
- Add private helper method: `void TriggerAutoBeauty()`
- Add public slot: `void slotBeautyFindBest()`

**Includes (`dock_fractal.cpp`)**
- Add `#include <QtConcurrent/QtConcurrent>` after existing includes at top of
file (~line 30)

**Constructor / Destructor (`dock_fractal.cpp`)**
- In the constructor (~line 80), after existing initialization, create
`beautyScanWatcher` and connect its `finished` signal to
`slotBeautyScanFinished`
- In the destructor, cancel, wait for, and delete `beautyScanWatcher`

**Free Function `RunBeautyScanAsync` (`dock_fractal.cpp`)**
- Implement as a static free function before the `cDockFractal` class
implementation (~line 60)
- Takes: `cxMin`, `cxMax`, `cyMin`, `cyMax`, `czMin`, `czMax` (doubles),
`resolution` (int), and a `std::function<double(double, double, double)>` score
function
- Returns `QVector<sBeautyResult>`
- Must not access any Qt widgets or UI elements (thread-safety requirement)
- Use a triple nested grid-sampling loop over the parameter space; call
`scoreFunc` for each grid point and accumulate `sBeautyResult` entries

**`slotBeautyFindBest` (`dock_fractal.cpp`)**
- Return early if `beautyScanWatcher->isRunning()`
- Disable relevant UI controls during scan
- Gather scan range via `JuliaSliderRange()`; use `resolution = 10`
- Capture a `scoreFunc` lambda calling `ComputeQuickScore` (must not capture UI
widgets)
- Launch `RunBeautyScanAsync` via `QtConcurrent::run` and set the returned
future on `beautyScanWatcher`

**`slotBeautyScanFinished` (`dock_fractal.cpp`)**
- Retrieve results from `beautyScanWatcher->result()`
- Return early (re-enable UI) if results are empty
- Sort results using `std::sort` (uses `operator<` for descending order)
- Update Julia C parameters (`vect3_julia_c_x/y/z`) with the first (best)
result's coordinates
- Re-enable UI controls

**Slider Release Auto-Trigger (`dock_fractal.cpp`)**
- Connect each Julia slider's `sliderReleased` signal to
`slotJuliaSliderReleased` (~line 558, alongside existing `valueChanged`
connections)
- `slotJuliaSliderReleased()` calls `TriggerAutoBeauty()`
- `TriggerAutoBeauty()` checks conditions and calls `slotBeautyFindBest()`

**Iteration Cap in `ComputeQuickScore` (`dock_fractal.cpp`)**
- In the standard path (~line 1050): replace hardcoded `maxIter = 64` with `int
configuredN = gPar->Get<int>("N"); int maxIter = std::min(60, configuredN);`
- In the deep zoom path (~line 1010): replace `maxIter = 1000` with `int
configuredN = gPar->Get<int>("N"); int maxIter = std::min(1000, configuredN);`
```

</details>




### Phase 3: Mutation Performance Optimization

Reduce per-iteration overhead in the CPU fractal computation by gating mutation-related operations behind the `mut.enabled` flag.


<details>
<summary><b>Task 1: Gate preMutZ Copy</b></summary>

Move the `preMutZ` snapshot inside the mutation-enabled check.

- In `mandelbulber2/src/compute_fractal.cpp` lines 313-321
- Change `CVector4 preMutZ = z;` to `CVector4 preMutZ;` (declare without initialization)
- Move `preMutZ = z;` inside the `if (mutationActive)` block

</details>


<details>
<summary><b>Task 2: Gate Post-Mutation NaN Check</b></summary>

Ensure NaN/Inf recovery logic only runs when mutations could have caused instability.

- In `mandelbulber2/src/compute_fractal.cpp` lines 3989-3997
- Change `if (z.IsNotANumber())` to `if (mut.enabled && z.IsNotANumber())`
- Second NaN check at line 4339 remains unconditional as safety net

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
Optimize the mutation path in `mandelbulber2/src/compute_fractal.cpp` by gating
two operations behind the `mut.enabled` flag to eliminate unnecessary overhead
when mutations are disabled.

**Gate `preMutZ` copy (~lines 313-321)**
- Locate the unconditional declaration `CVector4 preMutZ = z;` that currently
appears before the `mutationActive` check
- Change the declaration to `CVector4 preMutZ;` (no initialization) outside the
block
- Move the actual assignment `preMutZ = z;` to the first line inside the `if
(mutationActive)` block

**Gate post-mutation NaN check (~lines 3989-3997)**
- Locate the `if (z.IsNotANumber())` check that fires after mutation
post-processing
- Change the condition to `if (mut.enabled && z.IsNotANumber())` so it is
skipped entirely when mutations are inactive
- Do NOT modify the second NaN check at ~line 4339 — leave it unconditional as a
safety net
```

</details>




### Phase 4: OpenCL Exponential Safety Clamps

Add argument clamping to unguarded `native_exp` calls in the OpenCL engine to prevent overflow and NaN propagation. The clamp range of ±25.0f allows `e^25 ≈ 7.2×10^10` (within float range) while preventing overflow at larger arguments.


<details>
<summary><b>Task 1: Clamp ExpMap native_exp Arguments</b></summary>

Add bounds to the exponential map math mutation at lines 1531 and 3040.

- In `mandelbulber2/opencl/engines/nebula.cl` case 3 (ExpMap)
- Extract argument: `float expArg = mut->mathP1 * native_log(r + 1.0f);`
- Apply clamp: `float er = native_exp(clamp(expArg, -25.0f, 25.0f));`
- Apply identical change at line 3040 (duplicate instance)

</details>


<details>
<summary><b>Task 2: Clamp LogSpiral native_exp Arguments</b></summary>

Add bounds to the logarithmic spiral math mutation at lines 1549 and 3058.

- In `mandelbulber2/opencl/engines/nebula.cl` case 4 (LogSpiral)
- Add clamped value: `float lrClamped = clamp(lr, -25.0f, 25.0f);`
- Use `lrClamped` for both `spiralAngle` calculation and `native_exp(lrClamped)`
- Apply identical change at line 3058 (duplicate instance)

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
Harden `mandelbulber2/opencl/engines/nebula.cl` by clamping `native_exp`
arguments to ±25.0f at all unguarded call sites in the ExpMap and LogSpiral
mutations.

**ExpMap clamp (lines 1531 and 3040 — two duplicate instances)**
- Locate `native_exp(mut->mathP1 * native_log(r + 1.0f))` in the `case 3: //
ExpMap` block
- Extract the argument into a local variable: `float expArg = mut->mathP1 *
native_log(r + 1.0f);`
- Replace the `native_exp` call with: `native_exp(clamp(expArg, -25.0f, 25.0f))`
- Apply to both instances at lines 1531 and 3040

**LogSpiral clamp (lines 1549 and 3058 — two duplicate instances)**
- Locate the `case 4: // LogSpiral` block where `float lr = native_log(r +
1e-21f) * mut->mathP1;` is computed
- After computing `lr`, add: `float lrClamped = clamp(lr, -25.0f, 25.0f);`
- Replace uses of `lr` in `spiralAngle` and `newR` with `lrClamped`: `float
spiralAngle = phi + lrClamped * mut->mathP2;` and `float newR =
native_exp(lrClamped);`
- Apply to both instances at lines 1549 and 3058
```

</details>




### Phase 5: Deep Zoom Precision Implementation

Implement functional deep zoom support at 1e-10 scale using double-single emulation for critical ray-marching calculations. This approach uses two floats to represent extended precision (~15 decimal digits) and activates conditionally only when zoom exceeds the float32 precision threshold, ensuring no performance regression at normal zoom levels.

**HARD CONSTRAINT: All changes must have zero performance impact on normal zoom levels (< 1e7). Deep zoom code paths must only activate when zoom exceeds threshold.**


<details>
<summary><b>Task 1: Add Double-Single Arithmetic Header</b></summary>

Create `mandelbulber2/opencl/opencl_double_single.h` with double-single emulation primitives.

- Define `ds_float` struct with `hi` and `lo` float fields
- Define `ds_float3` struct for 3D vectors
- Implement `ds_quick_two_sum`, `ds_two_sum`, `ds_two_prod` for error-free arithmetic
- Implement `ds_add`, `ds_sub`, `ds_mul` for ds_float operations
- Implement `ds_from_float`, `ds_to_float` conversions
- Implement `ds_float3_add`, `ds_float3_sub`, `ds_float3_scale`, `ds_float3_to_float3` vector operations

</details>


<details>
<summary><b>Task 2: Extend Parameter Structs for Deep Zoom</b></summary>

Add double-precision camera parameters to CPU struct and split hi/lo pairs for OpenCL.

- In `mandelbulber2/src/fractparams_cl.hpp`, add to `sParamRenderCl`: `cl_int useDeepZoom`, `cl_float cameraDistanceHi/Lo`, `cl_float3 cameraHi/Lo`, `cl_float3 targetHi/Lo`, `cl_float resolutionHi/Lo`
- In `clCopySParamRenderCl()`, add Dekker splitting logic for zoom > 1e7 threshold
- Split doubles into hi+lo float pairs for camera, target, resolution
- Set `useDeepZoom = 0` when zoom < threshold to bypass extended precision paths

</details>


<details>
<summary><b>Task 3: Implement Deep Zoom Ray Setup in OpenCL</b></summary>

Modify nebula.cl kernel to use double-single arithmetic for ray setup when deep zoom active.

- Add `#include "opencl_double_single.h"` to nebula.cl
- Add conditional branch on `consts->useDeepZoom` at ray origin calculation
- Use ds_float3 for camera and target positions in extended precision path only
- Compute pixel offset with extended precision, downcast result for iteration loop
- Ensure standard path remains unchanged when `useDeepZoom == 0`

</details>


<details>
<summary><b>Task 4: Add Periodic Rebasing for Deep Iteration</b></summary>

Implement rebasing during ray marching to prevent accumulated error.

- Inside main ray marching loop, add rebasing check every 64 steps when `useDeepZoom` active
- Recompute current position using extended precision from camera + totalDistance * rayDir
- Downcast rebased position back to float3 for continued iteration
- Skip rebasing entirely when `useDeepZoom == 0`

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
Implement functional deep zoom precision support across
`mandelbulber2/opencl/opencl_double_single.h` (new file),
`mandelbulber2/src/fractparams_cl.hpp`, and
`mandelbulber2/opencl/engines/nebula.cl`. The goal is double-single emulation
providing ~15 decimal digits of precision, activated conditionally only when
zoom exceeds 1e7. All standard (non-deep-zoom) code paths must remain entirely
unchanged.

**New header file `mandelbulber2/opencl/opencl_double_single.h`**
- Define `ds_float` struct (`float hi`, `float lo`) and `ds_float3` struct
(three `ds_float` components)
- Implement primitives: `ds_quick_two_sum`, `ds_two_sum`, `ds_two_prod` (using
FMA), `ds_add`, `ds_sub`, `ds_mul`, `ds_from_float`, `ds_to_float`
- Implement vector operations: `ds_float3_add`, `ds_float3_sub`,
`ds_float3_scale`, `ds_float3_to_float3`
- All functions as `inline`

**Parameter struct extension (`mandelbulber2/src/fractparams_cl.hpp`)**
- Inside `sParamRenderCl`, add: `cl_int useDeepZoom`, `cl_float
cameraDistanceHi/Lo`, `cl_float3 cameraHi/Lo`, `cl_float3 targetHi/Lo`,
`cl_float resolutionHi/Lo`
- In `clCopySParamRenderCl()`, after existing assignments, add a branch: if
`source.cameraDistanceToTarget > 1e7` (DEEP_ZOOM_THRESHOLD), set
`target.useDeepZoom = 1` and populate all hi/lo fields using Dekker splitting
(`hi = (float)d; lo = (float)(d - (double)hi)`); otherwise set
`target.useDeepZoom = 0` and zero the hi/lo fields

**OpenCL kernel ray setup (`mandelbulber2/opencl/engines/nebula.cl`)**
- Add `#include "opencl_double_single.h"` near the top of the file after
existing includes
- At the ray setup location (where `rayOrigin` and `rayDir` are computed), add a
branch on `consts->useDeepZoom`:
- In the deep zoom branch: construct `cameraDS` and `targetDS` from hi/lo pairs,
compute pixel offsets using `ds_mul` and `ds_from_float`, add offsets to
`rayOriginDS`, downcast to `float3` via `ds_float3_to_float3`, compute `rayDir`
by subtracting `cameraDS` from `targetDS` and normalizing
- In the standard branch: use the existing single-precision camera and direction
calculation unchanged

**Periodic rebasing in the ray marching loop
(`mandelbulber2/opencl/engines/nebula.cl`)**
- Inside the main ray marching loop, after the distance step, insert a rebasing
block gated on `consts->useDeepZoom && (step % 64 == 0)`
- Recompute the current marching position by: constructing `totalDistDS` from
`totalDistance`, constructing `cameraDS` from hi/lo pairs, computing `offsetDS =
totalDistDS * rayDir` component-wise using `ds_mul`, adding to get `posDS`, then
downcasting `point = ds_float3_to_float3(posDS)`
- When `useDeepZoom == 0`, skip this block entirely
```

</details>




### Phase 6: Orange Fractal / Gradient Bug Fix

Diagnose and fix the bug where newly loaded fractals display with incorrect orange coloring or missing gradient. This phase investigates the palette/gradient synchronization between parameter loading and GPU buffer updates.


<details>
<summary><b>Task 1: Investigate Palette Buffer Synchronization</b></summary>

Identify where palette data fails to propagate to the GPU after fractal parameter changes.

- Root cause: palette buffer not marked dirty when palette parameters change during fractal load
- Investigate `mandelbulber2/src/opencl_engine_render_fractal.cpp` for palette buffer management
- Search for `palette` and `dirty` or `update` patterns in OpenCL engine

</details>


<details>
<summary><b>Task 2: Add Palette Dirty Flag on Parameter Load</b></summary>

Ensure palette buffer is marked dirty when palette-related parameters are loaded.

- In `opencl_engine_render_fractal.cpp` `PrepareBuffers()`: set `paletteDirty = true` when `paramsChanged`
- In `settings.cpp` after loading parameters: call `gMainInterface->openClEngine->SetPaletteDirty()`

</details>


<details>
<summary><b>Task 3: Add Explicit Palette Sync on Fractal Change</b></summary>

Implement dedicated synchronization point when fractal formula changes.

- Add `InvalidateColorBuffers()` method to `cOpenClEngineRenderFractal` class
- Set `paletteDirty`, `gradientDirty`, `paletteBufferValid = false`
- Call from `SynchronizeInterfaceOnFormulaChange()` in interface.cpp

</details>


<details>
<summary><b>Task 4: Add Diagnostic Logging for Palette Issues</b></summary>

Add conditional debug logging for palette buffer updates.

- In `UpdatePaletteBuffer()`, add `#ifdef QT_DEBUG` logging for palette size and first color
- Log when palette buffer upload triggers and completes

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
Diagnose and fix the orange fractal/gradient bug by ensuring palette buffer
synchronization across `mandelbulber2/src/opencl_engine_render_fractal.cpp`,
`mandelbulber2/src/opencl_engine_render_fractal.h`,
`mandelbulber2/src/settings.cpp`, and `mandelbulber2/src/interface.cpp`. The
root cause is the palette buffer not being marked dirty or re-uploaded when
fractal parameters change.

**Investigate palette buffer synchronization**
- Inspect `mandelbulber2/src/opencl_engine_render_fractal.cpp` for palette
buffer management, specifically looking for `clmem_palette`,
`SetPaletteDirty()`, and dirty flag patterns
- Inspect `mandelbulber2/src/settings.cpp` for where parameters are loaded from
file without triggering GPU palette re-upload
- Inspect `mandelbulber2/src/cimage.cpp` and
`mandelbulber2/src/color_palette.cpp` for palette data structures

**Palette dirty flag on parameter load
(`mandelbulber2/src/opencl_engine_render_fractal.cpp`)**
- In `PrepareBuffers()` or equivalent, add: if `paramsChanged`, set
`paletteDirty = true`; then if `paletteDirty`, call `UpdatePaletteBuffer()` and
reset the flag
- In `mandelbulber2/src/settings.cpp`, after loading parameters into the
container, call `gMainInterface->openClEngine->SetPaletteDirty()` if the engine
exists

**Explicit palette sync on fractal change (`mandelbulber2/src/interface.cpp`)**
- In the function handling fractal formula changes (search for `fractal_type`),
after existing sync code, call `openClEngine->InvalidateColorBuffers()` and
`mainWindow->RefreshPalettePreview()`
- Declare `void InvalidateColorBuffers()` in
`mandelbulber2/src/opencl_engine_render_fractal.h`
- Implement `InvalidateColorBuffers()` in
`mandelbulber2/src/opencl_engine_render_fractal.cpp` to set `paletteDirty =
true`, `gradientDirty = true`, and `paletteBufferValid = false`

**Diagnostic logging (`mandelbulber2/src/opencl_engine_render_fractal.cpp`)**
- In `UpdatePaletteBuffer()`, add `#ifdef QT_DEBUG` blocks before and after the
upload that log: trigger message, palette size, and first color RGB values
```

</details>




### Phase 7: Fractal Loading Performance Optimization

Optimize fractal parameter loading to reduce UI freeze time when opening complex fractal files. This phase identifies and addresses specific bottlenecks in the loading pipeline.


<details>
<summary><b>Task 1: Profile and Identify Loading Bottlenecks</b></summary>

Add timing instrumentation to the parameter loading path.

- Add `QElapsedTimer` instrumentation in `cSettings::LoadSettings()`
- Log timing for: File I/O, Parsing, Parameter sync, UI update, Total

</details>


<details>
<summary><b>Task 2: Implement Batch UI Updates</b></summary>

Reduce UI update overhead by batching widget updates and deferring repaints.

- Add `BeginBatchUpdate()` and `EndBatchUpdate()` methods to `cInterface`
- Use `setUpdatesEnabled(false/true)` to block/unblock widget repaints
- Wrap parameter sync in batch update calls in `LoadSettings()`

</details>


<details>
<summary><b>Task 3: Defer Non-Critical Parameter Processing</b></summary>

Move non-essential parameter validation to background processing after UI responsive.

- Add `LoadSettingsAsync()` that loads critical parameters synchronously
- Use `QTimer::singleShot(0, ...)` to defer: formula validation, derived values, preview thumbnails
- Critical parameters: camera position/target, fractal type, image dimensions, basic iteration

</details>


<details>
<summary><b>Task 4: Cache Parsed Parameter Templates</b></summary>

Avoid re-parsing parameter definitions on each load by caching the schema.

- Add static `QHash<QString, sParameterDefinition> parameterDefinitionCache` in parameters.cpp
- Add `InitializeParameterCache()` to pre-populate cache at startup
- Add `GetParameterDefinition()` that reads from cache instead of re-parsing

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
Optimize fractal loading performance across `mandelbulber2/src/settings.cpp`,
`mandelbulber2/src/interface.cpp`, and `mandelbulber2/src/parameters.cpp`. The
goal is to reduce UI freeze time by profiling bottlenecks, batching updates,
deferring non-critical work, and caching parameter definitions.

**Profiling instrumentation (`mandelbulber2/src/settings.cpp`)**
- Add `#include <QElapsedTimer>` at the top
- In `LoadSettings()`, wrap each phase (file I/O, parsing, parameter sync, UI
update) with `QElapsedTimer` measurements and `qDebug()` output reporting
elapsed milliseconds; report total at the end

**Batch UI updates (`mandelbulber2/src/interface.cpp`)**
- Add `BeginBatchUpdate()`: set `batchUpdateInProgress = true`, call
`mainWindow->setUpdatesEnabled(false)`
- Add `EndBatchUpdate()`: set `batchUpdateInProgress = false`, call
`mainWindow->setUpdatesEnabled(true)` and `mainWindow->update()`
- In `SynchronizeAllParameters()`, wrap the existing sync code between
`BeginBatchUpdate()` and `EndBatchUpdate()`
- In `mandelbulber2/src/settings.cpp`, replace `UpdateUI()` with
`gMainInterface->BeginBatchUpdate(); UpdateUI();
gMainInterface->EndBatchUpdate();`

**Deferred non-critical processing (`mandelbulber2/src/settings.cpp`)**
- Add `LoadSettingsAsync()`: call `LoadCriticalParameters()` synchronously, then
use `QTimer::singleShot(0, ...)` to defer `ValidateFormulaParameters()`,
`ComputeDerivedParameters()`, and `UpdatePreviews()`
- Add `LoadCriticalParameters()`: load only camera position/target, fractal
type, image dimensions, and basic iteration parameters; skip mutation
parameters, advanced coloring, and animation keyframes

**Parameter definition caching (`mandelbulber2/src/parameters.cpp`)**
- Add static `QHash<QString, sParameterDefinition> parameterDefinitionCache` and
`bool cacheInitialized = false`
- In `GetParameterDefinition()`, on first call trigger
`InitializeParameterCache()` and return from cache; provide a `static
sParameterDefinition defaultDef` as fallback for unknown parameters
- Add `InitializeParameterCache()`: iterate all known parameter definitions via
`GetAllParameterDefinitions()` and insert them into the cache; this runs only
once at startup
```

</details>




### Phase 8: Mutation System Concrete Improvements

Implement tangible enhancements to the mutation system including adaptive parameter scaling, fold logic consolidation, and parameter validation. These are functional code changes, not documentation.


<details>
<summary><b>Task 1: Implement Adaptive Mutation Strength</b></summary>

Add automatic parameter scaling based on orbit magnitude to prevent numerical instability.

- Add `bool adaptiveStrength` and `double adaptiveThreshold` to `sFormulaMutationParams`
- Register parameters in initparameters.cpp with threshold default 2.0
- In compute_fractal.cpp mutationActive block: compute `adaptiveFactor = threshold / orbitMag` when orbit exceeds threshold
- Apply factor to `mathP1`, `mathP2`, `warpAmplitude` before use

</details>


<details>
<summary><b>Task 2: Extract Shared Fold Logic Helper</b></summary>

Consolidate duplicated fold switch blocks into single reusable function.

- Add static `ApplyFoldTransform()` function in compute_fractal.cpp before main Compute function
- Parameters: z, foldType, foldLimit, foldValue, kaleidoscopeSides
- Implement switch cases for: foldNone, foldBox, foldSphere, foldAbs, foldKaleidoscope, etc.
- Replace pre-fold (~line 1806) and post-fold (~line 2088) switch blocks with single function calls

</details>


<details>
<summary><b>Task 3: Add Parameter Range Validation</b></summary>

Implement bounds checking for mutation parameters to prevent numerical instability.

- Add `ValidateMutationParams()` function in nine_fractals.cpp
- Clamp `mathP1`, `mathP2` to ±10.0 with warning log
- Clamp `warpAmplitude` to 0-10.0 with warning
- Validate `iterationStop >= iterationStart`, swap if invalid
- Clamp `zMix` to [0.0, 1.0]
- Call validation after loading params from container

</details>


<details>
<summary><b>Task 4: Add OpenCL Mutation Parameter Validation</b></summary>

Mirror CPU-side parameter validation in OpenCL kernel.

- Define `MATH_PARAM_SAFE_MAX` and `WARP_AMP_SAFE_MAX` constants (10.0f)
- At start of mutation processing block in nebula.cl: clamp `mathP1`, `mathP2`, `warpAmplitude` to safe ranges
- Use clamped values in subsequent calculations

</details>


<details>
<summary><b>Task 5: Implement Named Enums for Integer-Dispatched Systems</b></summary>

Add proper enum types for v7.7+ mutation sub-systems that use raw integers.

- Add enums in nine_fractals.hpp: `enumJosLeysDeType`, `enumPseudoKleinianDeType`, `enumMandelboxMathType`
- Add similar enums for: warpDistType, symKalType, aboxType, noiseType, orbitTrapType, torusType, asType, smType
- Replace `int` fields in `sFormulaMutationParams` with corresponding enum types

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
Implement concrete mutation system improvements across
`mandelbulber2/src/nine_fractals.hpp`, `mandelbulber2/src/nine_fractals.cpp`,
`mandelbulber2/src/initparameters.cpp`, `mandelbulber2/src/compute_fractal.cpp`,
and `mandelbulber2/opencl/engines/nebula.cl`. These are functional code changes
providing adaptive strength scaling, fold logic consolidation, parameter
validation, and named enums.

**Adaptive mutation strength**
- In `sFormulaMutationParams` (`nine_fractals.hpp`), add `bool adaptiveStrength`
and `double adaptiveThreshold` fields
- In `initparameters.cpp`, register `mutation_adaptive_strength` (default false)
and `mutation_adaptive_threshold` (default 2.0, range 0.1–100.0) parameters
- In `compute_fractal.cpp` inside the `mutationActive` block (~line 1530),
before applying mutation parameters: compute `adaptiveFactor = 1.0`; if
`mut.adaptiveStrength` and `z.Length() > mut.adaptiveThreshold`, set
`adaptiveFactor = mut.adaptiveThreshold / orbitMag` clamped to [0.01, 1.0] via
`qBound`; compute `effectiveMathP1 = mut.mathP1 * adaptiveFactor`,
`effectiveMathP2`, and `effectiveWarpAmp` and use these instead of `mut.*` in
subsequent calculations

**Extract shared fold logic (`mandelbulber2/src/compute_fractal.cpp`)**
- Add a static helper `ApplyFoldTransform(CVector4 z, enumMutationFoldType
foldType, double foldLimit, double foldValue, int kaleidoscopeSides)` returning
`CVector4`, placed before the main Compute function
- Implement cases for: `foldNone` (no-op), `foldBox` (component-wise mirroring),
`foldSphere` (spherical folding using r2/minR2/fixedR2), `foldAbs` (abs of each
component), `foldKaleidoscope` (angle-based wrapping), and all remaining fold
types from the existing duplicated switch blocks
- Replace the pre-fold switch at ~line 1806 with `z = ApplyFoldTransform(z,
mut.preFoldType, mut.foldLimit, mut.foldValue, mut.kaleidoscopeSides)`
- Replace the post-fold switch at ~line 2088 with `z = ApplyFoldTransform(z,
mut.postFoldType, mut.foldLimit, mut.foldValue, mut.kaleidoscopeSides)`

**CPU parameter range validation (`mandelbulber2/src/nine_fractals.cpp`)**
- Add `ValidateMutationParams(sFormulaMutationParams &mut)` method: define
`MATH_PARAM_SAFE_MAX = 10.0`; use a `clampWithWarning` lambda to clamp `mathP1`,
`mathP2` to ±10.0 and `warpAmplitude` to [0.0, 10.0] with `qWarning()` on
out-of-range; swap `iterationStart`/`iterationStop` if inverted; clamp `zMix` to
[0.0, 1.0] via `qBound`
- Call `ValidateMutationParams(params)` after loading parameters in
`GetMutationParams` or equivalent

**OpenCL parameter validation (`mandelbulber2/opencl/engines/nebula.cl`)**
- At the top of the mutation processing block, define `#define
MATH_PARAM_SAFE_MAX 10.0f` and `#define WARP_AMP_SAFE_MAX 10.0f`
- Inside `if (mutationActive)`, compute `safeMathP1 = clamp(mut->mathP1,
-MATH_PARAM_SAFE_MAX, MATH_PARAM_SAFE_MAX)`, `safeMathP2`, and `safeWarpAmp =
clamp(mut->warpAmplitude, 0.0f, WARP_AMP_SAFE_MAX)`, then use these safe values
throughout

**Named enums for integer-dispatched systems
(`mandelbulber2/src/nine_fractals.hpp`)**
- After existing enum definitions (~line 450), add `enumJosLeysDeType`
(josNone=0, josClassic=1, josSmooth=2, josRipple=3, josSpiral=4, and remaining
cases up to 100), `enumPseudoKleinianDeType` (pkNone=0, pkStandard=1,
pkTwisted=2, pkFolded=3, and remaining cases), `enumMandelboxMathType`
(mbNone=0, mbClassic=1, mbSmooth=2, mbVariant=3, and remaining cases up to 200),
plus similar enums for warpDistType, symKalType, aboxType, noiseType,
orbitTrapType, torusType, asType, smType
- In `sFormulaMutationParams`, replace the `int josLeysDeType`, `int
pseudoKleinianDeType`, and `int mbMathType` fields with the new enum types
```

</details>

<details>
<summary><b>Research</b></summary>

The codebase is a fractal rendering application with Qt-based UI (`mandelbulber2/qt/`) and both CPU (`compute_fractal.cpp`) and OpenCL (`nebula.cl`) computation backends. The `cDockFractal` class in `dock_fractal.h/.cpp` manages Julia Explorer UI with existing `ComputeQuickScore` function and Julia slider slots. The mutation system in `compute_fractal.cpp` uses `sFormulaMutationParams` with an `enabled` flag, and `preMutZ` is currently captured unconditionally before mutation blocks. The OpenCL engine has multiple `native_exp` calls, some guarded (LambertW with `min(r, 20.0f)`) and some unguarded (ExpMap, LogSpiral).

</details>


---



### 🚀 Next Steps


<details>
<summary><b>🤖 All AI agent prompts combined</b></summary>

```
Task: 1

This phase sets up the development environment and does not require code
generation. Follow the shell commands in each task to install dependencies (Qt5,
OpenCL, build tools), configure the CMake build in Debug mode, and verify the
application launches correctly with the Julia Explorer panel accessible before
proceeding to implementation phases.
===============================================================================

Task: 2

Implement the async beauty scanning infrastructure in `cDockFractal` across
`mandelbulber2/qt/dock_fractal.h` and `mandelbulber2/qt/dock_fractal.cpp`. The
goal is to introduce non-blocking UI behavior during Julia parameter space
exploration.

**Data Structure (`dock_fractal.h`)**
- Add `sBeautyResult` struct after line ~85, near `sJuliaHistoryEntry`,
containing: `cx`, `cy`, `cz` (double), `score` (double), and a comparison
`operator<` that sorts descending by score

**Class Members & Slots (`dock_fractal.h`)**
- Add private member: `QFutureWatcher<QVector<sBeautyResult>> *beautyScanWatcher
= nullptr`
- Add private slots: `void slotBeautyScanFinished()`, `void
slotJuliaSliderReleased()`
- Add private helper method: `void TriggerAutoBeauty()`
- Add public slot: `void slotBeautyFindBest()`

**Includes (`dock_fractal.cpp`)**
- Add `#include <QtConcurrent/QtConcurrent>` after existing includes at top of
file (~line 30)

**Constructor / Destructor (`dock_fractal.cpp`)**
- In the constructor (~line 80), after existing initialization, create
`beautyScanWatcher` and connect its `finished` signal to
`slotBeautyScanFinished`
- In the destructor, cancel, wait for, and delete `beautyScanWatcher`

**Free Function `RunBeautyScanAsync` (`dock_fractal.cpp`)**
- Implement as a static free function before the `cDockFractal` class
implementation (~line 60)
- Takes: `cxMin`, `cxMax`, `cyMin`, `cyMax`, `czMin`, `czMax` (doubles),
`resolution` (int), and a `std::function<double(double, double, double)>` score
function
- Returns `QVector<sBeautyResult>`
- Must not access any Qt widgets or UI elements (thread-safety requirement)
- Use a triple nested grid-sampling loop over the parameter space; call
`scoreFunc` for each grid point and accumulate `sBeautyResult` entries

**`slotBeautyFindBest` (`dock_fractal.cpp`)**
- Return early if `beautyScanWatcher->isRunning()`
- Disable relevant UI controls during scan
- Gather scan range via `JuliaSliderRange()`; use `resolution = 10`
- Capture a `scoreFunc` lambda calling `ComputeQuickScore` (must not capture UI
widgets)
- Launch `RunBeautyScanAsync` via `QtConcurrent::run` and set the returned
future on `beautyScanWatcher`

**`slotBeautyScanFinished` (`dock_fractal.cpp`)**
- Retrieve results from `beautyScanWatcher->result()`
- Return early (re-enable UI) if results are empty
- Sort results using `std::sort` (uses `operator<` for descending order)
- Update Julia C parameters (`vect3_julia_c_x/y/z`) with the first (best)
result's coordinates
- Re-enable UI controls

**Slider Release Auto-Trigger (`dock_fractal.cpp`)**
- Connect each Julia slider's `sliderReleased` signal to
`slotJuliaSliderReleased` (~line 558, alongside existing `valueChanged`
connections)
- `slotJuliaSliderReleased()` calls `TriggerAutoBeauty()`
- `TriggerAutoBeauty()` checks conditions and calls `slotBeautyFindBest()`

**Iteration Cap in `ComputeQuickScore` (`dock_fractal.cpp`)**
- In the standard path (~line 1050): replace hardcoded `maxIter = 64` with `int
configuredN = gPar->Get<int>("N"); int maxIter = std::min(60, configuredN);`
- In the deep zoom path (~line 1010): replace `maxIter = 1000` with `int
configuredN = gPar->Get<int>("N"); int maxIter = std::min(1000, configuredN);`
===============================================================================

Task: 3

Optimize the mutation path in `mandelbulber2/src/compute_fractal.cpp` by gating
two operations behind the `mut.enabled` flag to eliminate unnecessary overhead
when mutations are disabled.

**Gate `preMutZ` copy (~lines 313-321)**
- Locate the unconditional declaration `CVector4 preMutZ = z;` that currently
appears before the `mutationActive` check
- Change the declaration to `CVector4 preMutZ;` (no initialization) outside the
block
- Move the actual assignment `preMutZ = z;` to the first line inside the `if
(mutationActive)` block

**Gate post-mutation NaN check (~lines 3989-3997)**
- Locate the `if (z.IsNotANumber())` check that fires after mutation
post-processing
- Change the condition to `if (mut.enabled && z.IsNotANumber())` so it is
skipped entirely when mutations are inactive
- Do NOT modify the second NaN check at ~line 4339 — leave it unconditional as a
safety net
===============================================================================

Task: 4

Harden `mandelbulber2/opencl/engines/nebula.cl` by clamping `native_exp`
arguments to ±25.0f at all unguarded call sites in the ExpMap and LogSpiral
mutations.

**ExpMap clamp (lines 1531 and 3040 — two duplicate instances)**
- Locate `native_exp(mut->mathP1 * native_log(r + 1.0f))` in the `case 3: //
ExpMap` block
- Extract the argument into a local variable: `float expArg = mut->mathP1 *
native_log(r + 1.0f);`
- Replace the `native_exp` call with: `native_exp(clamp(expArg, -25.0f, 25.0f))`
- Apply to both instances at lines 1531 and 3040

**LogSpiral clamp (lines 1549 and 3058 — two duplicate instances)**
- Locate the `case 4: // LogSpiral` block where `float lr = native_log(r +
1e-21f) * mut->mathP1;` is computed
- After computing `lr`, add: `float lrClamped = clamp(lr, -25.0f, 25.0f);`
- Replace uses of `lr` in `spiralAngle` and `newR` with `lrClamped`: `float
spiralAngle = phi + lrClamped * mut->mathP2;` and `float newR =
native_exp(lrClamped);`
- Apply to both instances at lines 1549 and 3058
===============================================================================

Task: 5

Implement functional deep zoom precision support across
`mandelbulber2/opencl/opencl_double_single.h` (new file),
`mandelbulber2/src/fractparams_cl.hpp`, and
`mandelbulber2/opencl/engines/nebula.cl`. The goal is double-single emulation
providing ~15 decimal digits of precision, activated conditionally only when
zoom exceeds 1e7. All standard (non-deep-zoom) code paths must remain entirely
unchanged.

**New header file `mandelbulber2/opencl/opencl_double_single.h`**
- Define `ds_float` struct (`float hi`, `float lo`) and `ds_float3` struct
(three `ds_float` components)
- Implement primitives: `ds_quick_two_sum`, `ds_two_sum`, `ds_two_prod` (using
FMA), `ds_add`, `ds_sub`, `ds_mul`, `ds_from_float`, `ds_to_float`
- Implement vector operations: `ds_float3_add`, `ds_float3_sub`,
`ds_float3_scale`, `ds_float3_to_float3`
- All functions as `inline`

**Parameter struct extension (`mandelbulber2/src/fractparams_cl.hpp`)**
- Inside `sParamRenderCl`, add: `cl_int useDeepZoom`, `cl_float
cameraDistanceHi/Lo`, `cl_float3 cameraHi/Lo`, `cl_float3 targetHi/Lo`,
`cl_float resolutionHi/Lo`
- In `clCopySParamRenderCl()`, after existing assignments, add a branch: if
`source.cameraDistanceToTarget > 1e7` (DEEP_ZOOM_THRESHOLD), set
`target.useDeepZoom = 1` and populate all hi/lo fields using Dekker splitting
(`hi = (float)d; lo = (float)(d - (double)hi)`); otherwise set
`target.useDeepZoom = 0` and zero the hi/lo fields

**OpenCL kernel ray setup (`mandelbulber2/opencl/engines/nebula.cl`)**
- Add `#include "opencl_double_single.h"` near the top of the file after
existing includes
- At the ray setup location (where `rayOrigin` and `rayDir` are computed), add a
branch on `consts->useDeepZoom`:
- In the deep zoom branch: construct `cameraDS` and `targetDS` from hi/lo pairs,
compute pixel offsets using `ds_mul` and `ds_from_float`, add offsets to
`rayOriginDS`, downcast to `float3` via `ds_float3_to_float3`, compute `rayDir`
by subtracting `cameraDS` from `targetDS` and normalizing
- In the standard branch: use the existing single-precision camera and direction
calculation unchanged

**Periodic rebasing in the ray marching loop
(`mandelbulber2/opencl/engines/nebula.cl`)**
- Inside the main ray marching loop, after the distance step, insert a rebasing
block gated on `consts->useDeepZoom && (step % 64 == 0)`
- Recompute the current marching position by: constructing `totalDistDS` from
`totalDistance`, constructing `cameraDS` from hi/lo pairs, computing `offsetDS =
totalDistDS * rayDir` component-wise using `ds_mul`, adding to get `posDS`, then
downcasting `point = ds_float3_to_float3(posDS)`
- When `useDeepZoom == 0`, skip this block entirely
===============================================================================

Task: 6

Diagnose and fix the orange fractal/gradient bug by ensuring palette buffer
synchronization across `mandelbulber2/src/opencl_engine_render_fractal.cpp`,
`mandelbulber2/src/opencl_engine_render_fractal.h`,
`mandelbulber2/src/settings.cpp`, and `mandelbulber2/src/interface.cpp`. The
root cause is the palette buffer not being marked dirty or re-uploaded when
fractal parameters change.

**Investigate palette buffer synchronization**
- Inspect `mandelbulber2/src/opencl_engine_render_fractal.cpp` for palette
buffer management, specifically looking for `clmem_palette`,
`SetPaletteDirty()`, and dirty flag patterns
- Inspect `mandelbulber2/src/settings.cpp` for where parameters are loaded from
file without triggering GPU palette re-upload
- Inspect `mandelbulber2/src/cimage.cpp` and
`mandelbulber2/src/color_palette.cpp` for palette data structures

**Palette dirty flag on parameter load
(`mandelbulber2/src/opencl_engine_render_fractal.cpp`)**
- In `PrepareBuffers()` or equivalent, add: if `paramsChanged`, set
`paletteDirty = true`; then if `paletteDirty`, call `UpdatePaletteBuffer()` and
reset the flag
- In `mandelbulber2/src/settings.cpp`, after loading parameters into the
container, call `gMainInterface->openClEngine->SetPaletteDirty()` if the engine
exists

**Explicit palette sync on fractal change (`mandelbulber2/src/interface.cpp`)**
- In the function handling fractal formula changes (search for `fractal_type`),
after existing sync code, call `openClEngine->InvalidateColorBuffers()` and
`mainWindow->RefreshPalettePreview()`
- Declare `void InvalidateColorBuffers()` in
`mandelbulber2/src/opencl_engine_render_fractal.h`
- Implement `InvalidateColorBuffers()` in
`mandelbulber2/src/opencl_engine_render_fractal.cpp` to set `paletteDirty =
true`, `gradientDirty = true`, and `paletteBufferValid = false`

**Diagnostic logging (`mandelbulber2/src/opencl_engine_render_fractal.cpp`)**
- In `UpdatePaletteBuffer()`, add `#ifdef QT_DEBUG` blocks before and after the
upload that log: trigger message, palette size, and first color RGB values
===============================================================================

Task: 7

Optimize fractal loading performance across `mandelbulber2/src/settings.cpp`,
`mandelbulber2/src/interface.cpp`, and `mandelbulber2/src/parameters.cpp`. The
goal is to reduce UI freeze time by profiling bottlenecks, batching updates,
deferring non-critical work, and caching parameter definitions.

**Profiling instrumentation (`mandelbulber2/src/settings.cpp`)**
- Add `#include <QElapsedTimer>` at the top
- In `LoadSettings()`, wrap each phase (file I/O, parsing, parameter sync, UI
update) with `QElapsedTimer` measurements and `qDebug()` output reporting
elapsed milliseconds; report total at the end

**Batch UI updates (`mandelbulber2/src/interface.cpp`)**
- Add `BeginBatchUpdate()`: set `batchUpdateInProgress = true`, call
`mainWindow->setUpdatesEnabled(false)`
- Add `EndBatchUpdate()`: set `batchUpdateInProgress = false`, call
`mainWindow->setUpdatesEnabled(true)` and `mainWindow->update()`
- In `SynchronizeAllParameters()`, wrap the existing sync code between
`BeginBatchUpdate()` and `EndBatchUpdate()`
- In `mandelbulber2/src/settings.cpp`, replace `UpdateUI()` with
`gMainInterface->BeginBatchUpdate(); UpdateUI();
gMainInterface->EndBatchUpdate();`

**Deferred non-critical processing (`mandelbulber2/src/settings.cpp`)**
- Add `LoadSettingsAsync()`: call `LoadCriticalParameters()` synchronously, then
use `QTimer::singleShot(0, ...)` to defer `ValidateFormulaParameters()`,
`ComputeDerivedParameters()`, and `UpdatePreviews()`
- Add `LoadCriticalParameters()`: load only camera position/target, fractal
type, image dimensions, and basic iteration parameters; skip mutation
parameters, advanced coloring, and animation keyframes

**Parameter definition caching (`mandelbulber2/src/parameters.cpp`)**
- Add static `QHash<QString, sParameterDefinition> parameterDefinitionCache` and
`bool cacheInitialized = false`
- In `GetParameterDefinition()`, on first call trigger
`InitializeParameterCache()` and return from cache; provide a `static
sParameterDefinition defaultDef` as fallback for unknown parameters
- Add `InitializeParameterCache()`: iterate all known parameter definitions via
`GetAllParameterDefinitions()` and insert them into the cache; this runs only
once at startup
===============================================================================

Task: 8

Implement concrete mutation system improvements across
`mandelbulber2/src/nine_fractals.hpp`, `mandelbulber2/src/nine_fractals.cpp`,
`mandelbulber2/src/initparameters.cpp`, `mandelbulber2/src/compute_fractal.cpp`,
and `mandelbulber2/opencl/engines/nebula.cl`. These are functional code changes
providing adaptive strength scaling, fold logic consolidation, parameter
validation, and named enums.

**Adaptive mutation strength**
- In `sFormulaMutationParams` (`nine_fractals.hpp`), add `bool adaptiveStrength`
and `double adaptiveThreshold` fields
- In `initparameters.cpp`, register `mutation_adaptive_strength` (default false)
and `mutation_adaptive_threshold` (default 2.0, range 0.1–100.0) parameters
- In `compute_fractal.cpp` inside the `mutationActive` block (~line 1530),
before applying mutation parameters: compute `adaptiveFactor = 1.0`; if
`mut.adaptiveStrength` and `z.Length() > mut.adaptiveThreshold`, set
`adaptiveFactor = mut.adaptiveThreshold / orbitMag` clamped to [0.01, 1.0] via
`qBound`; compute `effectiveMathP1 = mut.mathP1 * adaptiveFactor`,
`effectiveMathP2`, and `effectiveWarpAmp` and use these instead of `mut.*` in
subsequent calculations

**Extract shared fold logic (`mandelbulber2/src/compute_fractal.cpp`)**
- Add a static helper `ApplyFoldTransform(CVector4 z, enumMutationFoldType
foldType, double foldLimit, double foldValue, int kaleidoscopeSides)` returning
`CVector4`, placed before the main Compute function
- Implement cases for: `foldNone` (no-op), `foldBox` (component-wise mirroring),
`foldSphere` (spherical folding using r2/minR2/fixedR2), `foldAbs` (abs of each
component), `foldKaleidoscope` (angle-based wrapping), and all remaining fold
types from the existing duplicated switch blocks
- Replace the pre-fold switch at ~line 1806 with `z = ApplyFoldTransform(z,
mut.preFoldType, mut.foldLimit, mut.foldValue, mut.kaleidoscopeSides)`
- Replace the post-fold switch at ~line 2088 with `z = ApplyFoldTransform(z,
mut.postFoldType, mut.foldLimit, mut.foldValue, mut.kaleidoscopeSides)`

**CPU parameter range validation (`mandelbulber2/src/nine_fractals.cpp`)**
- Add `ValidateMutationParams(sFormulaMutationParams &mut)` method: define
`MATH_PARAM_SAFE_MAX = 10.0`; use a `clampWithWarning` lambda to clamp `mathP1`,
`mathP2` to ±10.0 and `warpAmplitude` to [0.0, 10.0] with `qWarning()` on
out-of-range; swap `iterationStart`/`iterationStop` if inverted; clamp `zMix` to
[0.0, 1.0] via `qBound`
- Call `ValidateMutationParams(params)` after loading parameters in
`GetMutationParams` or equivalent

**OpenCL parameter validation (`mandelbulber2/opencl/engines/nebula.cl`)**
- At the top of the mutation processing block, define `#define
MATH_PARAM_SAFE_MAX 10.0f` and `#define WARP_AMP_SAFE_MAX 10.0f`
- Inside `if (mutationActive)`, compute `safeMathP1 = clamp(mut->mathP1,
-MATH_PARAM_SAFE_MAX, MATH_PARAM_SAFE_MAX)`, `safeMathP2`, and `safeWarpAmp =
clamp(mut->warpAmplitude, 0.0f, WARP_AMP_SAFE_MAX)`, then use these safe values
throughout

**Named enums for integer-dispatched systems
(`mandelbulber2/src/nine_fractals.hpp`)**
- After existing enum definitions (~line 450), add `enumJosLeysDeType`
(josNone=0, josClassic=1, josSmooth=2, josRipple=3, josSpiral=4, and remaining
cases up to 100), `enumPseudoKleinianDeType` (pkNone=0, pkStandard=1,
pkTwisted=2, pkFolded=3, and remaining cases), `enumMandelboxMathType`
(mbNone=0, mbClassic=1, mbSmooth=2, mbVariant=3, and remaining cases up to 200),
plus similar enums for warpDistType, symKalType, aboxType, noiseType,
orbitTrapType, torusType, asType, smType
- In `sFormulaMutationParams`, replace the `int josLeysDeType`, `int
pseudoKleinianDeType`, and `int mbMathType` fields with the new enum types
```

</details>


<details>
<summary><b>💡 Iterate on the plan with:
<code>@coderabbitai &lt;feedback&gt;</code>
</b></summary>

```
Example Feedback
- @coderabbitai You can skip phase 3. Add a simple unit test case for phase 2.
- @coderabbitai For design choice 1 go ahead with option 3 and replan.
```

</details>


---



💬 Have feedback or questions? Drop into our [discord](https://discord.gg/coderabbit)!



<!-- <agentComponentType>plan-edits</agentComponentType> -->

<!-- <rawResChunk><planningResult>## Coding Plan

### Summary

- Phases 0-3 address the original ticket: async beauty scanning via `QtConcurrent::run` with `QFutureWatcher`, CPU mutation optimization by gating `preMutZ` and NaN checks behind `mut.enabled`, and OpenCL hardening with ±25.0f clamps on ExpMap/LogSpiral `native_exp` calls
- Phases 4-7 implement optional foundational enhancements: double-single emulation for deep zoom (with strict performance isolation), palette buffer sync for gradient bugs, batch UI updates for loading, and adaptive mutation with consolidated fold logic

<details>
<summary><b>Design Choices</b></summary>

<details>
<summary><b>Design Choice 1: Beauty Finder symbols do not exist yet</b></summary>



**Options Considered:**
1. Create all new symbols from scratch as part of this ticket
2. Assume a base PR branch contains these symbols and this ticket modifies them

**Chosen Option:** 1

**Rationale:** Create the async infrastructure and new symbols, as the ticket describes adding them and the current codebase has no equivalent functionality.

</details>

<details>
<summary><b>Design Choice 2: OpenCL line numbers differ from ticket</b></summary>



**Options Considered:**
1. Target only the three specific calls mentioned regardless of actual line numbers
2. Target all unguarded `native_exp` calls found in exploration

**Chosen Option:** 1

**Rationale:** Target ExpMap (1531, 3040) and LogSpiral (1549, 3058) as these match the described "mathP1 log-exp" and "newR spiral" contexts; the "juliaC exponential" reference appears to be a documentation error in the ticket.

</details>

<details>
<summary><b>Design Choice 3: Iteration cap implementation</b></summary>



**Options Considered:**
1. Rename existing function and add parameter-based iteration cap
2. Create new `ComputeQuickScoreReal` alongside existing function
3. Modify existing `ComputeQuickScore` to use `std::min(60, pr.N)` pattern

**Chosen Option:** 3

**Rationale:** Modify existing `ComputeQuickScore` to use a configurable cap based on fractal parameters, as the function already exists and serves this purpose.

</details>

</details>

<b>💡 User Tips</b>

Regenerate the plan with different choices with `@coderabbitai <feedback>`.


## Implementation Steps


### Phase 1: Environment Setup and Prerequisites

Establish the development environment with all required dependencies for building and testing the Mandelbulber application.


<details>
<summary><b>Task 1: Install System Dependencies</b></summary>

Install required system packages for Qt5, OpenCL, and build tools.

- For Ubuntu/Debian: install `build-essential cmake git qtbase5-dev qttools5-dev qttools5-dev-tools libqt5svg5-dev ocl-icd-opencl-dev opencl-headers libpng-dev libjpeg-dev libtiff-dev libgsl-dev`
- For Fedora/RHEL: install `cmake gcc-c++ git qt5-qtbase-devel qt5-qttools-devel qt5-qtsvg-devel ocl-icd-devel opencl-headers libpng-devel libjpeg-devel libtiff-devel gsl-devel`

</details>


<details>
<summary><b>Task 2: Clone and Configure Build Environment</b></summary>

Set up the project directory structure and configure CMake.

- Clone repository and create out-of-source build directory
- Run `cmake .. -DCMAKE_BUILD_TYPE=Debug` to configure
- Verify configuration shows Qt5 and OpenCL found

</details>


<details>
<summary><b>Task 3: Build and Verify Installation</b></summary>

Compile the application and verify it launches correctly.

- Run `make -j$(nproc)` from build directory
- Launch `./mandelbulber2` and verify GUI opens
- Confirm Julia Explorer panel accessible and fractal renders

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
This phase sets up the development environment and does not require code
generation. Follow the shell commands in each task to install dependencies (Qt5,
OpenCL, build tools), configure the CMake build in Debug mode, and verify the
application launches correctly with the Julia Explorer panel accessible before
proceeding to implementation phases.
```

</details>




### Phase 2: Async Beauty Scan Infrastructure

Create the asynchronous beauty scanning system in `cDockFractal` to enable non-blocking UI during parameter space exploration.


<details>
<summary><b>Task 1: Define Beauty Result Data Structure</b></summary>

Add the `sBeautyResult` struct to hold scan results for sorting and display.

- Add struct to `mandelbulber2/qt/dock_fractal.h` after line ~85 (near `sJuliaHistoryEntry`)
- Include fields: `double cx, cy, cz, score`
- Add `operator<` for descending sort by score

</details>


<details>
<summary><b>Task 2: Add Async Infrastructure Members and Slots</b></summary>

Extend `cDockFractal` with QtConcurrent support for background scanning.

- Add `#include <QtConcurrent/QtConcurrent>` to `dock_fractal.cpp` after existing includes
- Add `QFutureWatcher<QVector<sBeautyResult>> *beautyScanWatcher = nullptr` to private members in `dock_fractal.h`
- Add `void slotBeautyScanFinished()` to private slots section
- Initialize watcher in constructor and connect to `slotBeautyScanFinished`
- Add cleanup in destructor: cancel, wait, delete

</details>


<details>
<summary><b>Task 3: Implement Async Scan Function</b></summary>

Create a thread-safe free function that performs the beauty parameter scan without UI access.

- Add `static QVector<sBeautyResult> RunBeautyScanAsync(...)` before `cDockFractal` class implementation
- Parameters: cxMin/Max, cyMin/Max, czMin/Max, resolution, scoreFunc
- Iterate 3D grid of Julia C parameters, compute scores, return results vector

</details>


<details>
<summary><b>Task 4: Implement slotBeautyFindBest Entry Point</b></summary>

Create the slot that initiates async beauty scanning.

- Add `void slotBeautyFindBest()` to public slots in header
- Check if scan already running, return early if so
- Get range from `JuliaSliderRange()`, set resolution to 10 (1000 samples)
- Capture scoring function, launch via `QtConcurrent::run`, set future on watcher

</details>


<details>
<summary><b>Task 5: Implement Scan Completion Handler</b></summary>

Process async scan results and update UI when complete.

- Get results from watcher, return early if empty
- Sort by score descending using `std::sort`
- Select best result and update Julia C parameter text fields

</details>


<details>
<summary><b>Task 6: Add Auto-Trigger on Slider Release</b></summary>

Enable automatic beauty scanning when Julia sliders are released.

- Add `slotJuliaSliderReleased()` and `TriggerAutoBeauty()` declarations to private slots
- Connect `sliderReleased()` signals from all three Julia sliders to `slotJuliaSliderReleased`
- Implement `TriggerAutoBeauty()` to call `slotBeautyFindBest()`

</details>


<details>
<summary><b>Task 7: Cap Screening Iterations</b></summary>

Limit iteration count in quick scoring for performance during rapid scanning.

- In `ComputeQuickScore` standard path (~line 1050): replace `int maxIter = 64` with `int maxIter = std::min(60, gPar->Get<int>("N"))`
- In deep zoom path (~line 1010): replace `int maxIter = 1000` with `int maxIter = std::min(1000, gPar->Get<int>("N"))`

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
Implement the async beauty scanning infrastructure in `cDockFractal` across
`mandelbulber2/qt/dock_fractal.h` and `mandelbulber2/qt/dock_fractal.cpp`. The
goal is to introduce non-blocking UI behavior during Julia parameter space
exploration.

**Data Structure (`dock_fractal.h`)**
- Add `sBeautyResult` struct after line ~85, near `sJuliaHistoryEntry`,
containing: `cx`, `cy`, `cz` (double), `score` (double), and a comparison
`operator<` that sorts descending by score

**Class Members & Slots (`dock_fractal.h`)**
- Add private member: `QFutureWatcher<QVector<sBeautyResult>> *beautyScanWatcher
= nullptr`
- Add private slots: `void slotBeautyScanFinished()`, `void
slotJuliaSliderReleased()`
- Add private helper method: `void TriggerAutoBeauty()`
- Add public slot: `void slotBeautyFindBest()`

**Includes (`dock_fractal.cpp`)**
- Add `#include <QtConcurrent/QtConcurrent>` after existing includes at top of
file (~line 30)

**Constructor / Destructor (`dock_fractal.cpp`)**
- In the constructor (~line 80), after existing initialization, create
`beautyScanWatcher` and connect its `finished` signal to
`slotBeautyScanFinished`
- In the destructor, cancel, wait for, and delete `beautyScanWatcher`

**Free Function `RunBeautyScanAsync` (`dock_fractal.cpp`)**
- Implement as a static free function before the `cDockFractal` class
implementation (~line 60)
- Takes: `cxMin`, `cxMax`, `cyMin`, `cyMax`, `czMin`, `czMax` (doubles),
`resolution` (int), and a `std::function<double(double, double, double)>` score
function
- Returns `QVector<sBeautyResult>`
- Must not access any Qt widgets or UI elements (thread-safety requirement)
- Use a triple nested grid-sampling loop over the parameter space; call
`scoreFunc` for each grid point and accumulate `sBeautyResult` entries

**`slotBeautyFindBest` (`dock_fractal.cpp`)**
- Return early if `beautyScanWatcher->isRunning()`
- Disable relevant UI controls during scan
- Gather scan range via `JuliaSliderRange()`; use `resolution = 10`
- Capture a `scoreFunc` lambda calling `ComputeQuickScore` (must not capture UI
widgets)
- Launch `RunBeautyScanAsync` via `QtConcurrent::run` and set the returned
future on `beautyScanWatcher`

**`slotBeautyScanFinished` (`dock_fractal.cpp`)**
- Retrieve results from `beautyScanWatcher->result()`
- Return early (re-enable UI) if results are empty
- Sort results using `std::sort` (uses `operator<` for descending order)
- Update Julia C parameters (`vect3_julia_c_x/y/z`) with the first (best)
result's coordinates
- Re-enable UI controls

**Slider Release Auto-Trigger (`dock_fractal.cpp`)**
- Connect each Julia slider's `sliderReleased` signal to
`slotJuliaSliderReleased` (~line 558, alongside existing `valueChanged`
connections)
- `slotJuliaSliderReleased()` calls `TriggerAutoBeauty()`
- `TriggerAutoBeauty()` checks conditions and calls `slotBeautyFindBest()`

**Iteration Cap in `ComputeQuickScore` (`dock_fractal.cpp`)**
- In the standard path (~line 1050): replace hardcoded `maxIter = 64` with `int
configuredN = gPar->Get<int>("N"); int maxIter = std::min(60, configuredN);`
- In the deep zoom path (~line 1010): replace `maxIter = 1000` with `int
configuredN = gPar->Get<int>("N"); int maxIter = std::min(1000, configuredN);`
```

</details>




### Phase 3: Mutation Performance Optimization

Reduce per-iteration overhead in the CPU fractal computation by gating mutation-related operations behind the `mut.enabled` flag.


<details>
<summary><b>Task 1: Gate preMutZ Copy</b></summary>

Move the `preMutZ` snapshot inside the mutation-enabled check.

- In `mandelbulber2/src/compute_fractal.cpp` lines 313-321
- Change `CVector4 preMutZ = z;` to `CVector4 preMutZ;` (declare without initialization)
- Move `preMutZ = z;` inside the `if (mutationActive)` block

</details>


<details>
<summary><b>Task 2: Gate Post-Mutation NaN Check</b></summary>

Ensure NaN/Inf recovery logic only runs when mutations could have caused instability.

- In `mandelbulber2/src/compute_fractal.cpp` lines 3989-3997
- Change `if (z.IsNotANumber())` to `if (mut.enabled && z.IsNotANumber())`
- Second NaN check at line 4339 remains unconditional as safety net

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
Optimize the mutation path in `mandelbulber2/src/compute_fractal.cpp` by gating
two operations behind the `mut.enabled` flag to eliminate unnecessary overhead
when mutations are disabled.

**Gate `preMutZ` copy (~lines 313-321)**
- Locate the unconditional declaration `CVector4 preMutZ = z;` that currently
appears before the `mutationActive` check
- Change the declaration to `CVector4 preMutZ;` (no initialization) outside the
block
- Move the actual assignment `preMutZ = z;` to the first line inside the `if
(mutationActive)` block

**Gate post-mutation NaN check (~lines 3989-3997)**
- Locate the `if (z.IsNotANumber())` check that fires after mutation
post-processing
- Change the condition to `if (mut.enabled && z.IsNotANumber())` so it is
skipped entirely when mutations are inactive
- Do NOT modify the second NaN check at ~line 4339 — leave it unconditional as a
safety net
```

</details>




### Phase 4: OpenCL Exponential Safety Clamps

Add argument clamping to unguarded `native_exp` calls in the OpenCL engine to prevent overflow and NaN propagation. The clamp range of ±25.0f allows `e^25 ≈ 7.2×10^10` (within float range) while preventing overflow at larger arguments.


<details>
<summary><b>Task 1: Clamp ExpMap native_exp Arguments</b></summary>

Add bounds to the exponential map math mutation at lines 1531 and 3040.

- In `mandelbulber2/opencl/engines/nebula.cl` case 3 (ExpMap)
- Extract argument: `float expArg = mut->mathP1 * native_log(r + 1.0f);`
- Apply clamp: `float er = native_exp(clamp(expArg, -25.0f, 25.0f));`
- Apply identical change at line 3040 (duplicate instance)

</details>


<details>
<summary><b>Task 2: Clamp LogSpiral native_exp Arguments</b></summary>

Add bounds to the logarithmic spiral math mutation at lines 1549 and 3058.

- In `mandelbulber2/opencl/engines/nebula.cl` case 4 (LogSpiral)
- Add clamped value: `float lrClamped = clamp(lr, -25.0f, 25.0f);`
- Use `lrClamped` for both `spiralAngle` calculation and `native_exp(lrClamped)`
- Apply identical change at line 3058 (duplicate instance)

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
Harden `mandelbulber2/opencl/engines/nebula.cl` by clamping `native_exp`
arguments to ±25.0f at all unguarded call sites in the ExpMap and LogSpiral
mutations.

**ExpMap clamp (lines 1531 and 3040 — two duplicate instances)**
- Locate `native_exp(mut->mathP1 * native_log(r + 1.0f))` in the `case 3: //
ExpMap` block
- Extract the argument into a local variable: `float expArg = mut->mathP1 *
native_log(r + 1.0f);`
- Replace the `native_exp` call with: `native_exp(clamp(expArg, -25.0f, 25.0f))`
- Apply to both instances at lines 1531 and 3040

**LogSpiral clamp (lines 1549 and 3058 — two duplicate instances)**
- Locate the `case 4: // LogSpiral` block where `float lr = native_log(r +
1e-21f) * mut->mathP1;` is computed
- After computing `lr`, add: `float lrClamped = clamp(lr, -25.0f, 25.0f);`
- Replace uses of `lr` in `spiralAngle` and `newR` with `lrClamped`: `float
spiralAngle = phi + lrClamped * mut->mathP2;` and `float newR =
native_exp(lrClamped);`
- Apply to both instances at lines 1549 and 3058
```

</details>




### Phase 5: Deep Zoom Precision Implementation

Implement functional deep zoom support at 1e-10 scale using double-single emulation for critical ray-marching calculations. This approach uses two floats to represent extended precision (~15 decimal digits) and activates conditionally only when zoom exceeds the float32 precision threshold, ensuring no performance regression at normal zoom levels.

**HARD CONSTRAINT: All changes must have zero performance impact on normal zoom levels (< 1e7). Deep zoom code paths must only activate when zoom exceeds threshold.**


<details>
<summary><b>Task 1: Add Double-Single Arithmetic Header</b></summary>

Create `mandelbulber2/opencl/opencl_double_single.h` with double-single emulation primitives.

- Define `ds_float` struct with `hi` and `lo` float fields
- Define `ds_float3` struct for 3D vectors
- Implement `ds_quick_two_sum`, `ds_two_sum`, `ds_two_prod` for error-free arithmetic
- Implement `ds_add`, `ds_sub`, `ds_mul` for ds_float operations
- Implement `ds_from_float`, `ds_to_float` conversions
- Implement `ds_float3_add`, `ds_float3_sub`, `ds_float3_scale`, `ds_float3_to_float3` vector operations

</details>


<details>
<summary><b>Task 2: Extend Parameter Structs for Deep Zoom</b></summary>

Add double-precision camera parameters to CPU struct and split hi/lo pairs for OpenCL.

- In `mandelbulber2/src/fractparams_cl.hpp`, add to `sParamRenderCl`: `cl_int useDeepZoom`, `cl_float cameraDistanceHi/Lo`, `cl_float3 cameraHi/Lo`, `cl_float3 targetHi/Lo`, `cl_float resolutionHi/Lo`
- In `clCopySParamRenderCl()`, add Dekker splitting logic for zoom > 1e7 threshold
- Split doubles into hi+lo float pairs for camera, target, resolution
- Set `useDeepZoom = 0` when zoom < threshold to bypass extended precision paths

</details>


<details>
<summary><b>Task 3: Implement Deep Zoom Ray Setup in OpenCL</b></summary>

Modify nebula.cl kernel to use double-single arithmetic for ray setup when deep zoom active.

- Add `#include "opencl_double_single.h"` to nebula.cl
- Add conditional branch on `consts->useDeepZoom` at ray origin calculation
- Use ds_float3 for camera and target positions in extended precision path only
- Compute pixel offset with extended precision, downcast result for iteration loop
- Ensure standard path remains unchanged when `useDeepZoom == 0`

</details>


<details>
<summary><b>Task 4: Add Periodic Rebasing for Deep Iteration</b></summary>

Implement rebasing during ray marching to prevent accumulated error.

- Inside main ray marching loop, add rebasing check every 64 steps when `useDeepZoom` active
- Recompute current position using extended precision from camera + totalDistance * rayDir
- Downcast rebased position back to float3 for continued iteration
- Skip rebasing entirely when `useDeepZoom == 0`

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
Implement functional deep zoom precision support across
`mandelbulber2/opencl/opencl_double_single.h` (new file),
`mandelbulber2/src/fractparams_cl.hpp`, and
`mandelbulber2/opencl/engines/nebula.cl`. The goal is double-single emulation
providing ~15 decimal digits of precision, activated conditionally only when
zoom exceeds 1e7. All standard (non-deep-zoom) code paths must remain entirely
unchanged.

**New header file `mandelbulber2/opencl/opencl_double_single.h`**
- Define `ds_float` struct (`float hi`, `float lo`) and `ds_float3` struct
(three `ds_float` components)
- Implement primitives: `ds_quick_two_sum`, `ds_two_sum`, `ds_two_prod` (using
FMA), `ds_add`, `ds_sub`, `ds_mul`, `ds_from_float`, `ds_to_float`
- Implement vector operations: `ds_float3_add`, `ds_float3_sub`,
`ds_float3_scale`, `ds_float3_to_float3`
- All functions as `inline`

**Parameter struct extension (`mandelbulber2/src/fractparams_cl.hpp`)**
- Inside `sParamRenderCl`, add: `cl_int useDeepZoom`, `cl_float
cameraDistanceHi/Lo`, `cl_float3 cameraHi/Lo`, `cl_float3 targetHi/Lo`,
`cl_float resolutionHi/Lo`
- In `clCopySParamRenderCl()`, after existing assignments, add a branch: if
`source.cameraDistanceToTarget > 1e7` (DEEP_ZOOM_THRESHOLD), set
`target.useDeepZoom = 1` and populate all hi/lo fields using Dekker splitting
(`hi = (float)d; lo = (float)(d - (double)hi)`); otherwise set
`target.useDeepZoom = 0` and zero the hi/lo fields

**OpenCL kernel ray setup (`mandelbulber2/opencl/engines/nebula.cl`)**
- Add `#include "opencl_double_single.h"` near the top of the file after
existing includes
- At the ray setup location (where `rayOrigin` and `rayDir` are computed), add a
branch on `consts->useDeepZoom`:
- In the deep zoom branch: construct `cameraDS` and `targetDS` from hi/lo pairs,
compute pixel offsets using `ds_mul` and `ds_from_float`, add offsets to
`rayOriginDS`, downcast to `float3` via `ds_float3_to_float3`, compute `rayDir`
by subtracting `cameraDS` from `targetDS` and normalizing
- In the standard branch: use the existing single-precision camera and direction
calculation unchanged

**Periodic rebasing in the ray marching loop
(`mandelbulber2/opencl/engines/nebula.cl`)**
- Inside the main ray marching loop, after the distance step, insert a rebasing
block gated on `consts->useDeepZoom && (step % 64 == 0)`
- Recompute the current marching position by: constructing `totalDistDS` from
`totalDistance`, constructing `cameraDS` from hi/lo pairs, computing `offsetDS =
totalDistDS * rayDir` component-wise using `ds_mul`, adding to get `posDS`, then
downcasting `point = ds_float3_to_float3(posDS)`
- When `useDeepZoom == 0`, skip this block entirely
```

</details>




### Phase 6: Orange Fractal / Gradient Bug Fix

Diagnose and fix the bug where newly loaded fractals display with incorrect orange coloring or missing gradient. This phase investigates the palette/gradient synchronization between parameter loading and GPU buffer updates.


<details>
<summary><b>Task 1: Investigate Palette Buffer Synchronization</b></summary>

Identify where palette data fails to propagate to the GPU after fractal parameter changes.

- Root cause: palette buffer not marked dirty when palette parameters change during fractal load
- Investigate `mandelbulber2/src/opencl_engine_render_fractal.cpp` for palette buffer management
- Search for `palette` and `dirty` or `update` patterns in OpenCL engine

</details>


<details>
<summary><b>Task 2: Add Palette Dirty Flag on Parameter Load</b></summary>

Ensure palette buffer is marked dirty when palette-related parameters are loaded.

- In `opencl_engine_render_fractal.cpp` `PrepareBuffers()`: set `paletteDirty = true` when `paramsChanged`
- In `settings.cpp` after loading parameters: call `gMainInterface->openClEngine->SetPaletteDirty()`

</details>


<details>
<summary><b>Task 3: Add Explicit Palette Sync on Fractal Change</b></summary>

Implement dedicated synchronization point when fractal formula changes.

- Add `InvalidateColorBuffers()` method to `cOpenClEngineRenderFractal` class
- Set `paletteDirty`, `gradientDirty`, `paletteBufferValid = false`
- Call from `SynchronizeInterfaceOnFormulaChange()` in interface.cpp

</details>


<details>
<summary><b>Task 4: Add Diagnostic Logging for Palette Issues</b></summary>

Add conditional debug logging for palette buffer updates.

- In `UpdatePaletteBuffer()`, add `#ifdef QT_DEBUG` logging for palette size and first color
- Log when palette buffer upload triggers and completes

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
Diagnose and fix the orange fractal/gradient bug by ensuring palette buffer
synchronization across `mandelbulber2/src/opencl_engine_render_fractal.cpp`,
`mandelbulber2/src/opencl_engine_render_fractal.h`,
`mandelbulber2/src/settings.cpp`, and `mandelbulber2/src/interface.cpp`. The
root cause is the palette buffer not being marked dirty or re-uploaded when
fractal parameters change.

**Investigate palette buffer synchronization**
- Inspect `mandelbulber2/src/opencl_engine_render_fractal.cpp` for palette
buffer management, specifically looking for `clmem_palette`,
`SetPaletteDirty()`, and dirty flag patterns
- Inspect `mandelbulber2/src/settings.cpp` for where parameters are loaded from
file without triggering GPU palette re-upload
- Inspect `mandelbulber2/src/cimage.cpp` and
`mandelbulber2/src/color_palette.cpp` for palette data structures

**Palette dirty flag on parameter load
(`mandelbulber2/src/opencl_engine_render_fractal.cpp`)**
- In `PrepareBuffers()` or equivalent, add: if `paramsChanged`, set
`paletteDirty = true`; then if `paletteDirty`, call `UpdatePaletteBuffer()` and
reset the flag
- In `mandelbulber2/src/settings.cpp`, after loading parameters into the
container, call `gMainInterface->openClEngine->SetPaletteDirty()` if the engine
exists

**Explicit palette sync on fractal change (`mandelbulber2/src/interface.cpp`)**
- In the function handling fractal formula changes (search for `fractal_type`),
after existing sync code, call `openClEngine->InvalidateColorBuffers()` and
`mainWindow->RefreshPalettePreview()`
- Declare `void InvalidateColorBuffers()` in
`mandelbulber2/src/opencl_engine_render_fractal.h`
- Implement `InvalidateColorBuffers()` in
`mandelbulber2/src/opencl_engine_render_fractal.cpp` to set `paletteDirty =
true`, `gradientDirty = true`, and `paletteBufferValid = false`

**Diagnostic logging (`mandelbulber2/src/opencl_engine_render_fractal.cpp`)**
- In `UpdatePaletteBuffer()`, add `#ifdef QT_DEBUG` blocks before and after the
upload that log: trigger message, palette size, and first color RGB values
```

</details>




### Phase 7: Fractal Loading Performance Optimization

Optimize fractal parameter loading to reduce UI freeze time when opening complex fractal files. This phase identifies and addresses specific bottlenecks in the loading pipeline.


<details>
<summary><b>Task 1: Profile and Identify Loading Bottlenecks</b></summary>

Add timing instrumentation to the parameter loading path.

- Add `QElapsedTimer` instrumentation in `cSettings::LoadSettings()`
- Log timing for: File I/O, Parsing, Parameter sync, UI update, Total

</details>


<details>
<summary><b>Task 2: Implement Batch UI Updates</b></summary>

Reduce UI update overhead by batching widget updates and deferring repaints.

- Add `BeginBatchUpdate()` and `EndBatchUpdate()` methods to `cInterface`
- Use `setUpdatesEnabled(false/true)` to block/unblock widget repaints
- Wrap parameter sync in batch update calls in `LoadSettings()`

</details>


<details>
<summary><b>Task 3: Defer Non-Critical Parameter Processing</b></summary>

Move non-essential parameter validation to background processing after UI responsive.

- Add `LoadSettingsAsync()` that loads critical parameters synchronously
- Use `QTimer::singleShot(0, ...)` to defer: formula validation, derived values, preview thumbnails
- Critical parameters: camera position/target, fractal type, image dimensions, basic iteration

</details>


<details>
<summary><b>Task 4: Cache Parsed Parameter Templates</b></summary>

Avoid re-parsing parameter definitions on each load by caching the schema.

- Add static `QHash<QString, sParameterDefinition> parameterDefinitionCache` in parameters.cpp
- Add `InitializeParameterCache()` to pre-populate cache at startup
- Add `GetParameterDefinition()` that reads from cache instead of re-parsing

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
Optimize fractal loading performance across `mandelbulber2/src/settings.cpp`,
`mandelbulber2/src/interface.cpp`, and `mandelbulber2/src/parameters.cpp`. The
goal is to reduce UI freeze time by profiling bottlenecks, batching updates,
deferring non-critical work, and caching parameter definitions.

**Profiling instrumentation (`mandelbulber2/src/settings.cpp`)**
- Add `#include <QElapsedTimer>` at the top
- In `LoadSettings()`, wrap each phase (file I/O, parsing, parameter sync, UI
update) with `QElapsedTimer` measurements and `qDebug()` output reporting
elapsed milliseconds; report total at the end

**Batch UI updates (`mandelbulber2/src/interface.cpp`)**
- Add `BeginBatchUpdate()`: set `batchUpdateInProgress = true`, call
`mainWindow->setUpdatesEnabled(false)`
- Add `EndBatchUpdate()`: set `batchUpdateInProgress = false`, call
`mainWindow->setUpdatesEnabled(true)` and `mainWindow->update()`
- In `SynchronizeAllParameters()`, wrap the existing sync code between
`BeginBatchUpdate()` and `EndBatchUpdate()`
- In `mandelbulber2/src/settings.cpp`, replace `UpdateUI()` with
`gMainInterface->BeginBatchUpdate(); UpdateUI();
gMainInterface->EndBatchUpdate();`

**Deferred non-critical processing (`mandelbulber2/src/settings.cpp`)**
- Add `LoadSettingsAsync()`: call `LoadCriticalParameters()` synchronously, then
use `QTimer::singleShot(0, ...)` to defer `ValidateFormulaParameters()`,
`ComputeDerivedParameters()`, and `UpdatePreviews()`
- Add `LoadCriticalParameters()`: load only camera position/target, fractal
type, image dimensions, and basic iteration parameters; skip mutation
parameters, advanced coloring, and animation keyframes

**Parameter definition caching (`mandelbulber2/src/parameters.cpp`)**
- Add static `QHash<QString, sParameterDefinition> parameterDefinitionCache` and
`bool cacheInitialized = false`
- In `GetParameterDefinition()`, on first call trigger
`InitializeParameterCache()` and return from cache; provide a `static
sParameterDefinition defaultDef` as fallback for unknown parameters
- Add `InitializeParameterCache()`: iterate all known parameter definitions via
`GetAllParameterDefinitions()` and insert them into the cache; this runs only
once at startup
```

</details>




### Phase 8: Mutation System Concrete Improvements

Implement tangible enhancements to the mutation system including adaptive parameter scaling, fold logic consolidation, and parameter validation. These are functional code changes, not documentation.


<details>
<summary><b>Task 1: Implement Adaptive Mutation Strength</b></summary>

Add automatic parameter scaling based on orbit magnitude to prevent numerical instability.

- Add `bool adaptiveStrength` and `double adaptiveThreshold` to `sFormulaMutationParams`
- Register parameters in initparameters.cpp with threshold default 2.0
- In compute_fractal.cpp mutationActive block: compute `adaptiveFactor = threshold / orbitMag` when orbit exceeds threshold
- Apply factor to `mathP1`, `mathP2`, `warpAmplitude` before use

</details>


<details>
<summary><b>Task 2: Extract Shared Fold Logic Helper</b></summary>

Consolidate duplicated fold switch blocks into single reusable function.

- Add static `ApplyFoldTransform()` function in compute_fractal.cpp before main Compute function
- Parameters: z, foldType, foldLimit, foldValue, kaleidoscopeSides
- Implement switch cases for: foldNone, foldBox, foldSphere, foldAbs, foldKaleidoscope, etc.
- Replace pre-fold (~line 1806) and post-fold (~line 2088) switch blocks with single function calls

</details>


<details>
<summary><b>Task 3: Add Parameter Range Validation</b></summary>

Implement bounds checking for mutation parameters to prevent numerical instability.

- Add `ValidateMutationParams()` function in nine_fractals.cpp
- Clamp `mathP1`, `mathP2` to ±10.0 with warning log
- Clamp `warpAmplitude` to 0-10.0 with warning
- Validate `iterationStop >= iterationStart`, swap if invalid
- Clamp `zMix` to [0.0, 1.0]
- Call validation after loading params from container

</details>


<details>
<summary><b>Task 4: Add OpenCL Mutation Parameter Validation</b></summary>

Mirror CPU-side parameter validation in OpenCL kernel.

- Define `MATH_PARAM_SAFE_MAX` and `WARP_AMP_SAFE_MAX` constants (10.0f)
- At start of mutation processing block in nebula.cl: clamp `mathP1`, `mathP2`, `warpAmplitude` to safe ranges
- Use clamped values in subsequent calculations

</details>


<details>
<summary><b>Task 5: Implement Named Enums for Integer-Dispatched Systems</b></summary>

Add proper enum types for v7.7+ mutation sub-systems that use raw integers.

- Add enums in nine_fractals.hpp: `enumJosLeysDeType`, `enumPseudoKleinianDeType`, `enumMandelboxMathType`
- Add similar enums for: warpDistType, symKalType, aboxType, noiseType, orbitTrapType, torusType, asType, smType
- Replace `int` fields in `sFormulaMutationParams` with corresponding enum types

</details>


<details>
<summary><b>🤖 Prompt for AI agents</b></summary>

```
Implement concrete mutation system improvements across
`mandelbulber2/src/nine_fractals.hpp`, `mandelbulber2/src/nine_fractals.cpp`,
`mandelbulber2/src/initparameters.cpp`, `mandelbulber2/src/compute_fractal.cpp`,
and `mandelbulber2/opencl/engines/nebula.cl`. These are functional code changes
providing adaptive strength scaling, fold logic consolidation, parameter
validation, and named enums.

**Adaptive mutation strength**
- In `sFormulaMutationParams` (`nine_fractals.hpp`), add `bool adaptiveStrength`
and `double adaptiveThreshold` fields
- In `initparameters.cpp`, register `mutation_adaptive_strength` (default false)
and `mutation_adaptive_threshold` (default 2.0, range 0.1–100.0) parameters
- In `compute_fractal.cpp` inside the `mutationActive` block (~line 1530),
before applying mutation parameters: compute `adaptiveFactor = 1.0`; if
`mut.adaptiveStrength` and `z.Length() > mut.adaptiveThreshold`, set
`adaptiveFactor = mut.adaptiveThreshold / orbitMag` clamped to [0.01, 1.0] via
`qBound`; compute `effectiveMathP1 = mut.mathP1 * adaptiveFactor`,
`effectiveMathP2`, and `effectiveWarpAmp` and use these instead of `mut.*` in
subsequent calculations

**Extract shared fold logic (`mandelbulber2/src/compute_fractal.cpp`)**
- Add a static helper `ApplyFoldTransform(CVector4 z, enumMutationFoldType
foldType, double foldLimit, double foldValue, int kaleidoscopeSides)` returning
`CVector4`, placed before the main Compute function
- Implement cases for: `foldNone` (no-op), `foldBox` (component-wise mirroring),
`foldSphere` (spherical folding using r2/minR2/fixedR2), `foldAbs` (abs of each
component), `foldKaleidoscope` (angle-based wrapping), and all remaining fold
types from the existing duplicated switch blocks
- Replace the pre-fold switch at ~line 1806 with `z = ApplyFoldTransform(z,
mut.preFoldType, mut.foldLimit, mut.foldValue, mut.kaleidoscopeSides)`
- Replace the post-fold switch at ~line 2088 with `z = ApplyFoldTransform(z,
mut.postFoldType, mut.foldLimit, mut.foldValue, mut.kaleidoscopeSides)`

**CPU parameter range validation (`mandelbulber2/src/nine_fractals.cpp`)**
- Add `ValidateMutationParams(sFormulaMutationParams &mut)` method: define
`MATH_PARAM_SAFE_MAX = 10.0`; use a `clampWithWarning` lambda to clamp `mathP1`,
`mathP2` to ±10.0 and `warpAmplitude` to [0.0, 10.0] with `qWarning()` on
out-of-range; swap `iterationStart`/`iterationStop` if inverted; clamp `zMix` to
[0.0, 1.0] via `qBound`
- Call `ValidateMutationParams(params)` after loading parameters in
`GetMutationParams` or equivalent

**OpenCL parameter validation (`mandelbulber2/opencl/engines/nebula.cl`)**
- At the top of the mutation processing block, define `#define
MATH_PARAM_SAFE_MAX 10.0f` and `#define WARP_AMP_SAFE_MAX 10.0f`
- Inside `if (mutationActive)`, compute `safeMathP1 = clamp(mut->mathP1,
-MATH_PARAM_SAFE_MAX, MATH_PARAM_SAFE_MAX)`, `safeMathP2`, and `safeWarpAmp =
clamp(mut->warpAmplitude, 0.0f, WARP_AMP_SAFE_MAX)`, then use these safe values
throughout

**Named enums for integer-dispatched systems
(`mandelbulber2/src/nine_fractals.hpp`)**
- After existing enum definitions (~line 450), add `enumJosLeysDeType`
(josNone=0, josClassic=1, josSmooth=2, josRipple=3, josSpiral=4, and remaining
cases up to 100), `enumPseudoKleinianDeType` (pkNone=0, pkStandard=1,
pkTwisted=2, pkFolded=3, and remaining cases), `enumMandelboxMathType`
(mbNone=0, mbClassic=1, mbSmooth=2, mbVariant=3, and remaining cases up to 200),
plus similar enums for warpDistType, symKalType, aboxType, noiseType,
orbitTrapType, torusType, asType, smType
- In `sFormulaMutationParams`, replace the `int josLeysDeType`, `int
pseudoKleinianDeType`, and `int mbMathType` fields with the new enum types
```

</details>

<details>
<summary><b>Research</b></summary>

The codebase is a fractal rendering application with Qt-based UI (`mandelbulber2/qt/`) and both CPU (`compute_fractal.cpp`) and OpenCL (`nebula.cl`) computation backends. The `cDockFractal` class in `dock_fractal.h/.cpp` manages Julia Explorer UI with existing `ComputeQuickScore` function and Julia slider slots. The mutation system in `compute_fractal.cpp` uses `sFormulaMutationParams` with an `enabled` flag, and `preMutZ` is currently captured unconditionally before mutation blocks. The OpenCL engine has multiple `native_exp` calls, some guarded (LambertW with `min(r, 20.0f)`) and some unguarded (ExpMap, LogSpiral).

</details>


---



### 🚀 Next Steps


<details>
<summary><b>🤖 All AI agent prompts combined</b></summary>

```
Task: 1

This phase sets up the development environment and does not require code
generation. Follow the shell commands in each task to install dependencies (Qt5,
OpenCL, build tools), configure the CMake build in Debug mode, and verify the
application launches correctly with the Julia Explorer panel accessible before
proceeding to implementation phases.
===============================================================================

Task: 2

Implement the async beauty scanning infrastructure in `cDockFractal` across
`mandelbulber2/qt/dock_fractal.h` and `mandelbulber2/qt/dock_fractal.cpp`. The
goal is to introduce non-blocking UI behavior during Julia parameter space
exploration.

**Data Structure (`dock_fractal.h`)**
- Add `sBeautyResult` struct after line ~85, near `sJuliaHistoryEntry`,
containing: `cx`, `cy`, `cz` (double), `score` (double), and a comparison
`operator<` that sorts descending by score

**Class Members & Slots (`dock_fractal.h`)**
- Add private member: `QFutureWatcher<QVector<sBeautyResult>> *beautyScanWatcher
= nullptr`
- Add private slots: `void slotBeautyScanFinished()`, `void
slotJuliaSliderReleased()`
- Add private helper method: `void TriggerAutoBeauty()`
- Add public slot: `void slotBeautyFindBest()`

**Includes (`dock_fractal.cpp`)**
- Add `#include <QtConcurrent/QtConcurrent>` after existing includes at top of
file (~line 30)

**Constructor / Destructor (`dock_fractal.cpp`)**
- In the constructor (~line 80), after existing initialization, create
`beautyScanWatcher` and connect its `finished` signal to
`slotBeautyScanFinished`
- In the destructor, cancel, wait for, and delete `beautyScanWatcher`

**Free Function `RunBeautyScanAsync` (`dock_fractal.cpp`)**
- Implement as a static free function before the `cDockFractal` class
implementation (~line 60)
- Takes: `cxMin`, `cxMax`, `cyMin`, `cyMax`, `czMin`, `czMax` (doubles),
`resolution` (int), and a `std::function<double(double, double, double)>` score
function
- Returns `QVector<sBeautyResult>`
- Must not access any Qt widgets or UI elements (thread-safety requirement)
- Use a triple nested grid-sampling loop over the parameter space; call
`scoreFunc` for each grid point and accumulate `sBeautyResult` entries

**`slotBeautyFindBest` (`dock_fractal.cpp`)**
- Return early if `beautyScanWatcher->isRunning()`
- Disable relevant UI controls during scan
- Gather scan range via `JuliaSliderRange()`; use `resolution = 10`
- Capture a `scoreFunc` lambda calling `ComputeQuickScore` (must not capture UI
widgets)
- Launch `RunBeautyScanAsync` via `QtConcurrent::run` and set the returned
future on `beautyScanWatcher`

**`slotBeautyScanFinished` (`dock_fractal.cpp`)**
- Retrieve results from `beautyScanWatcher->result()`
- Return early (re-enable UI) if results are empty
- Sort results using `std::sort` (uses `operator<` for descending order)
- Update Julia C parameters (`vect3_julia_c_x/y/z`) with the first (best)
result's coordinates
- Re-enable UI controls

**Slider Release Auto-Trigger (`dock_fractal.cpp`)**
- Connect each Julia slider's `sliderReleased` signal to
`slotJuliaSliderReleased` (~line 558, alongside existing `valueChanged`
connections)
- `slotJuliaSliderReleased()` calls `TriggerAutoBeauty()`
- `TriggerAutoBeauty()` checks conditions and calls `slotBeautyFindBest()`

**Iteration Cap in `ComputeQuickScore` (`dock_fractal.cpp`)**
- In the standard path (~line 1050): replace hardcoded `maxIter = 64` with `int
configuredN = gPar->Get<int>("N"); int maxIter = std::min(60, configuredN);`
- In the deep zoom path (~line 1010): replace `maxIter = 1000` with `int
configuredN = gPar->Get<int>("N"); int maxIter = std::min(1000, configuredN);`
===============================================================================

Task: 3

Optimize the mutation path in `mandelbulber2/src/compute_fractal.cpp` by gating
two operations behind the `mut.enabled` flag to eliminate unnecessary overhead
when mutations are disabled.

**Gate `preMutZ` copy (~lines 313-321)**
- Locate the unconditional declaration `CVector4 preMutZ = z;` that currently
appears before the `mutationActive` check
- Change the declaration to `CVector4 preMutZ;` (no initialization) outside the
block
- Move the actual assignment `preMutZ = z;` to the first line inside the `if
(mutationActive)` block

**Gate post-mutation NaN check (~lines 3989-3997)**
- Locate the `if (z.IsNotANumber())` check that fires after mutation
post-processing
- Change the condition to `if (mut.enabled && z.IsNotANumber())` so it is
skipped entirely when mutations are inactive
- Do NOT modify the second NaN check at ~line 4339 — leave it unconditional as a
safety net
===============================================================================

Task: 4

Harden `mandelbulber2/opencl/engines/nebula.cl` by clamping `native_exp`
arguments to ±25.0f at all unguarded call sites in the ExpMap and LogSpiral
mutations.

**ExpMap clamp (lines 1531 and 3040 — two duplicate instances)**
- Locate `native_exp(mut->mathP1 * native_log(r + 1.0f))` in the `case 3: //
ExpMap` block
- Extract the argument into a local variable: `float expArg = mut->mathP1 *
native_log(r + 1.0f);`
- Replace the `native_exp` call with: `native_exp(clamp(expArg, -25.0f, 25.0f))`
- Apply to both instances at lines 1531 and 3040

**LogSpiral clamp (lines 1549 and 3058 — two duplicate instances)**
- Locate the `case 4: // LogSpiral` block where `float lr = native_log(r +
1e-21f) * mut->mathP1;` is computed
- After computing `lr`, add: `float lrClamped = clamp(lr, -25.0f, 25.0f);`
- Replace uses of `lr` in `spiralAngle` and `newR` with `lrClamped`: `float
spiralAngle = phi + lrClamped * mut->mathP2;` and `float newR =
native_exp(lrClamped);`
- Apply to both instances at lines 1549 and 3058
===============================================================================

Task: 5

Implement functional deep zoom precision support across
`mandelbulber2/opencl/opencl_double_single.h` (new file),
`mandelbulber2/src/fractparams_cl.hpp`, and
`mandelbulber2/opencl/engines/nebula.cl`. The goal is double-single emulation
providing ~15 decimal digits of precision, activated conditionally only when
zoom exceeds 1e7. All standard (non-deep-zoom) code paths must remain entirely
unchanged.

**New header file `mandelbulber2/opencl/opencl_double_single.h`**
- Define `ds_float` struct (`float hi`, `float lo`) and `ds_float3` struct
(three `ds_float` components)
- Implement primitives: `ds_quick_two_sum`, `ds_two_sum`, `ds_two_prod` (using
FMA), `ds_add`, `ds_sub`, `ds_mul`, `ds_from_float`, `ds_to_float`
- Implement vector operations: `ds_float3_add`, `ds_float3_sub`,
`ds_float3_scale`, `ds_float3_to_float3`
- All functions as `inline`

**Parameter struct extension (`mandelbulber2/src/fractparams_cl.hpp`)**
- Inside `sParamRenderCl`, add: `cl_int useDeepZoom`, `cl_float
cameraDistanceHi/Lo`, `cl_float3 cameraHi/Lo`, `cl_float3 targetHi/Lo`,
`cl_float resolutionHi/Lo`
- In `clCopySParamRenderCl()`, after existing assignments, add a branch: if
`source.cameraDistanceToTarget > 1e7` (DEEP_ZOOM_THRESHOLD), set
`target.useDeepZoom = 1` and populate all hi/lo fields using Dekker splitting
(`hi = (float)d; lo = (float)(d - (double)hi)`); otherwise set
`target.useDeepZoom = 0` and zero the hi/lo fields

**OpenCL kernel ray setup (`mandelbulber2/opencl/engines/nebula.cl`)**
- Add `#include "opencl_double_single.h"` near the top of the file after
existing includes
- At the ray setup location (where `rayOrigin` and `rayDir` are computed), add a
branch on `consts->useDeepZoom`:
- In the deep zoom branch: construct `cameraDS` and `targetDS` from hi/lo pairs,
compute pixel offsets using `ds_mul` and `ds_from_float`, add offsets to
`rayOriginDS`, downcast to `float3` via `ds_float3_to_float3`, compute `rayDir`
by subtracting `cameraDS` from `targetDS` and normalizing
- In the standard branch: use the existing single-precision camera and direction
calculation unchanged

**Periodic rebasing in the ray marching loop
(`mandelbulber2/opencl/engines/nebula.cl`)**
- Inside the main ray marching loop, after the distance step, insert a rebasing
block gated on `consts->useDeepZoom && (step % 64 == 0)`
- Recompute the current marching position by: constructing `totalDistDS` from
`totalDistance`, constructing `cameraDS` from hi/lo pairs, computing `offsetDS =
totalDistDS * rayDir` component-wise using `ds_mul`, adding to get `posDS`, then
downcasting `point = ds_float3_to_float3(posDS)`
- When `useDeepZoom == 0`, skip this block entirely
===============================================================================

Task: 6

Diagnose and fix the orange fractal/gradient bug by ensuring palette buffer
synchronization across `mandelbulber2/src/opencl_engine_render_fractal.cpp`,
`mandelbulber2/src/opencl_engine_render_fractal.h`,
`mandelbulber2/src/settings.cpp`, and `mandelbulber2/src/interface.cpp`. The
root cause is the palette buffer not being marked dirty or re-uploaded when
fractal parameters change.

**Investigate palette buffer synchronization**
- Inspect `mandelbulber2/src/opencl_engine_render_fractal.cpp` for palette
buffer management, specifically looking for `clmem_palette`,
`SetPaletteDirty()`, and dirty flag patterns
- Inspect `mandelbulber2/src/settings.cpp` for where parameters are loaded from
file without triggering GPU palette re-upload
- Inspect `mandelbulber2/src/cimage.cpp` and
`mandelbulber2/src/color_palette.cpp` for palette data structures

**Palette dirty flag on parameter load
(`mandelbulber2/src/opencl_engine_render_fractal.cpp`)**
- In `PrepareBuffers()` or equivalent, add: if `paramsChanged`, set
`paletteDirty = true`; then if `paletteDirty`, call `UpdatePaletteBuffer()` and
reset the flag
- In `mandelbulber2/src/settings.cpp`, after loading parameters into the
container, call `gMainInterface->openClEngine->SetPaletteDirty()` if the engine
exists

**Explicit palette sync on fractal change (`mandelbulber2/src/interface.cpp`)**
- In the function handling fractal formula changes (search for `fractal_type`),
after existing sync code, call `openClEngine->InvalidateColorBuffers()` and
`mainWindow->RefreshPalettePreview()`
- Declare `void InvalidateColorBuffers()` in
`mandelbulber2/src/opencl_engine_render_fractal.h`
- Implement `InvalidateColorBuffers()` in
`mandelbulber2/src/opencl_engine_render_fractal.cpp` to set `paletteDirty =
true`, `gradientDirty = true`, and `paletteBufferValid = false`

**Diagnostic logging (`mandelbulber2/src/opencl_engine_render_fractal.cpp`)**
- In `UpdatePaletteBuffer()`, add `#ifdef QT_DEBUG` blocks before and after the
upload that log: trigger message, palette size, and first color RGB values
===============================================================================

Task: 7

Optimize fractal loading performance across `mandelbulber2/src/settings.cpp`,
`mandelbulber2/src/interface.cpp`, and `mandelbulber2/src/parameters.cpp`. The
goal is to reduce UI freeze time by profiling bottlenecks, batching updates,
deferring non-critical work, and caching parameter definitions.

**Profiling instrumentation (`mandelbulber2/src/settings.cpp`)**
- Add `#include <QElapsedTimer>` at the top
- In `LoadSettings()`, wrap each phase (file I/O, parsing, parameter sync, UI
update) with `QElapsedTimer` measurements and `qDebug()` output reporting
elapsed milliseconds; report total at the end

**Batch UI updates (`mandelbulber2/src/interface.cpp`)**
- Add `BeginBatchUpdate()`: set `batchUpdateInProgress = true`, call
`mainWindow->setUpdatesEnabled(false)`
- Add `EndBatchUpdate()`: set `batchUpdateInProgress = false`, call
`mainWindow->setUpdatesEnabled(true)` and `mainWindow->update()`
- In `SynchronizeAllParameters()`, wrap the existing sync code between
`BeginBatchUpdate()` and `EndBatchUpdate()`
- In `mandelbulber2/src/settings.cpp`, replace `UpdateUI()` with
`gMainInterface->BeginBatchUpdate(); UpdateUI();
gMainInterface->EndBatchUpdate();`

**Deferred non-critical processing (`mandelbulber2/src/settings.cpp`)**
- Add `LoadSettingsAsync()`: call `LoadCriticalParameters()` synchronously, then
use `QTimer::singleShot(0, ...)` to defer `ValidateFormulaParameters()`,
`ComputeDerivedParameters()`, and `UpdatePreviews()`
- Add `LoadCriticalParameters()`: load only camera position/target, fractal
type, image dimensions, and basic iteration parameters; skip mutation
parameters, advanced coloring, and animation keyframes

**Parameter definition caching (`mandelbulber2/src/parameters.cpp`)**
- Add static `QHash<QString, sParameterDefinition> parameterDefinitionCache` and
`bool cacheInitialized = false`
- In `GetParameterDefinition()`, on first call trigger
`InitializeParameterCache()` and return from cache; provide a `static
sParameterDefinition defaultDef` as fallback for unknown parameters
- Add `InitializeParameterCache()`: iterate all known parameter definitions via
`GetAllParameterDefinitions()` and insert them into the cache; this runs only
once at startup
===============================================================================

Task: 8

Implement concrete mutation system improvements across
`mandelbulber2/src/nine_fractals.hpp`, `mandelbulber2/src/nine_fractals.cpp`,
`mandelbulber2/src/initparameters.cpp`, `mandelbulber2/src/compute_fractal.cpp`,
and `mandelbulber2/opencl/engines/nebula.cl`. These are functional code changes
providing adaptive strength scaling, fold logic consolidation, parameter
validation, and named enums.

**Adaptive mutation strength**
- In `sFormulaMutationParams` (`nine_fractals.hpp`), add `bool adaptiveStrength`
and `double adaptiveThreshold` fields
- In `initparameters.cpp`, register `mutation_adaptive_strength` (default false)
and `mutation_adaptive_threshold` (default 2.0, range 0.1–100.0) parameters
- In `compute_fractal.cpp` inside the `mutationActive` block (~line 1530),
before applying mutation parameters: compute `adaptiveFactor = 1.0`; if
`mut.adaptiveStrength` and `z.Length() > mut.adaptiveThreshold`, set
`adaptiveFactor = mut.adaptiveThreshold / orbitMag` clamped to [0.01, 1.0] via
`qBound`; compute `effectiveMathP1 = mut.mathP1 * adaptiveFactor`,
`effectiveMathP2`, and `effectiveWarpAmp` and use these instead of `mut.*` in
subsequent calculations

**Extract shared fold logic (`mandelbulber2/src/compute_fractal.cpp`)**
- Add a static helper `ApplyFoldTransform(CVector4 z, enumMutationFoldType
foldType, double foldLimit, double foldValue, int kaleidoscopeSides)` returning
`CVector4`, placed before the main Compute function
- Implement cases for: `foldNone` (no-op), `foldBox` (component-wise mirroring),
`foldSphere` (spherical folding using r2/minR2/fixedR2), `foldAbs` (abs of each
component), `foldKaleidoscope` (angle-based wrapping), and all remaining fold
types from the existing duplicated switch blocks
- Replace the pre-fold switch at ~line 1806 with `z = ApplyFoldTransform(z,
mut.preFoldType, mut.foldLimit, mut.foldValue, mut.kaleidoscopeSides)`
- Replace the post-fold switch at ~line 2088 with `z = ApplyFoldTransform(z,
mut.postFoldType, mut.foldLimit, mut.foldValue, mut.kaleidoscopeSides)`

**CPU parameter range validation (`mandelbulber2/src/nine_fractals.cpp`)**
- Add `ValidateMutationParams(sFormulaMutationParams &mut)` method: define
`MATH_PARAM_SAFE_MAX = 10.0`; use a `clampWithWarning` lambda to clamp `mathP1`,
`mathP2` to ±10.0 and `warpAmplitude` to [0.0, 10.0] with `qWarning()` on
out-of-range; swap `iterationStart`/`iterationStop` if inverted; clamp `zMix` to
[0.0, 1.0] via `qBound`
- Call `ValidateMutationParams(params)` after loading parameters in
`GetMutationParams` or equivalent

**OpenCL parameter validation (`mandelbulber2/opencl/engines/nebula.cl`)**
- At the top of the mutation processing block, define `#define
MATH_PARAM_SAFE_MAX 10.0f` and `#define WARP_AMP_SAFE_MAX 10.0f`
- Inside `if (mutationActive)`, compute `safeMathP1 = clamp(mut->mathP1,
-MATH_PARAM_SAFE_MAX, MATH_PARAM_SAFE_MAX)`, `safeMathP2`, and `safeWarpAmp =
clamp(mut->warpAmplitude, 0.0f, WARP_AMP_SAFE_MAX)`, then use these safe values
throughout

**Named enums for integer-dispatched systems
(`mandelbulber2/src/nine_fractals.hpp`)**
- After existing enum definitions (~line 450), add `enumJosLeysDeType`
(josNone=0, josClassic=1, josSmooth=2, josRipple=3, josSpiral=4, and remaining
cases up to 100), `enumPseudoKleinianDeType` (pkNone=0, pkStandard=1,
pkTwisted=2, pkFolded=3, and remaining cases), `enumMandelboxMathType`
(mbNone=0, mbClassic=1, mbSmooth=2, mbVariant=3, and remaining cases up to 200),
plus similar enums for warpDistType, symKalType, aboxType, noiseType,
orbitTrapType, torusType, asType, smType
- In `sFormulaMutationParams`, replace the `int josLeysDeType`, `int
pseudoKleinianDeType`, and `int mbMathType` fields with the new enum types
```

</details>


<details>
<summary><b>💡 Iterate on the plan with:
<code>@coderabbitai &lt;feedback&gt;</code>
</b></summary>

```
Example Feedback
- @coderabbitai You can skip phase 3. Add a simple unit test case for phase 2.
- @coderabbitai For design choice 1 go ahead with option 3 and replan.
```

</details>


---



💬 Have feedback or questions? Drop into our [discord](https://discord.gg/coderabbit)!</planningResult></rawResChunk> -->

<!-- <agentComponentType>plan-edits</agentComponentType> -->
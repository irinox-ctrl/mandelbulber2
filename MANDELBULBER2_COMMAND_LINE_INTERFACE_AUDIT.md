# MANDELBULBER2 COMMAND LINE INTERFACE: Developer Guide

**Datum**: 2026-04-22  
**Bestanden**: `command_line_interface.hpp/cpp`  
**Scope**: CLI argument parsing, operational mode dispatch, headless rendering, NetRender, queue processing  
**Focus**: Developer guide — how the CLI works, how to add new flags, architecture overview  

---

## 1. Architecture Overview

```
[main.cpp]
    |
    v
[cCommandLineInterface constructor]  ← QCommandLineParser setup
    |
    v
[ReadCLI()]    ← Parse & validate arguments, set operational mode
    |
    v
[ProcessCLI()] ← Dispatch to headless renderers
    |
    +---> modeNetrender  → gNetRender->SetClient() + exec()
    +---> modeFlight     → cHeadless::RenderFlightAnimation()
    +---> modeKeyframe   → cHeadless::RenderKeyframeAnimation()
    +---> modeStill      → cHeadless::RenderStillImage()
    +---> modeQueue      → cHeadless::RenderQueue()
    +---> modeVoxel      → cHeadless::RenderVoxel()
    +---> modeBootOnly   → (GUI mode or no-op)
```

---

## 2. Operational Modes

| Enum | Trigger Flags | What It Does |
|------|--------------|--------------|
| `modeBootOnly` | No special flags, or just GUI launch | Starts normally (Qt GUI) |
| `modeNetrender` | `--server` or `--host <ip>` | Distributed rendering server/client |
| `modeKeyframe` | `-K` or `--keyframe` | Renders keyframe animation |
| `modeFlight` | `-F` or `--flight` | Renders flight animation |
| `modeStill` | `-n <file.fract>` without animation flags | Renders single image |
| `modeQueue` | `-q` or `--queue`, or multiple input files | Batch renders queue items |
| `modeVoxel` | `-V <format>` | Exports voxel volume |

**Mode resolution priority** (in `ReadCLI()`):
1. `--server` / `--host` → `modeNetrender` (highest priority)
2. `-q` → `modeQueue`
3. `-F` → `modeFlight`
4. `-K` → `modeKeyframe`
5. `-V` → `modeVoxel`
6. Multiple files or folders → `modeQueue`
7. Single `.fract` file → `modeStill`
8. Nothing → `modeBootOnly`

---

## 3. Argument Parsing

### 3.1 Using Qt's QCommandLineParser

```cpp
QCommandLineParser parser;
parser.addHelpOption();
parser.addVersionOption();

const QCommandLineOption noguiOption(
    QStringList({"n", "nogui"}),
    QCoreApplication::translate("main", "Starts without GUI"));

parser.addOption(noguiOption);
parser.process(*qApplication);

bool nogui = parser.isSet(noguiOption);
QString value = parser.value(someOption);
```

**Key feature**: `QCommandLineParser` handles `--help`, `--version`, and error formatting automatically.

### 3.2 Stdin Input Support

A special positional argument `"-"` tells the CLI to read settings from stdin instead of a file:

```cpp
if (!args.empty() && args[0] == "-") {
    QTextStream qin(stdin);
    args[0] = qin.readAll();  // Replace "-" with file contents
}
```

**Usage**:
```bash
cat mysettings.fract | mandelbulber2 -
```

The entire settings text is passed as a string argument, then `handleArgs()` tries to load it via `cSettings::LoadFromString()`.

### 3.3 Positional Arguments

The first positional argument is always treated as the settings file:
```cpp
parser.addPositionalArgument("settings_file",
    "file with fractal settings (also searches ./mandelbulber/settings)");
```

If multiple positional arguments are given, the CLI switches to **queue mode** and processes all of them.

---

## 4. Parameter Override System

### 4.1 Syntax

```bash
mandelbulber2 -n myscene.fract -O "camera_x=1.5#fov=60#image_width=1920"
```

Multiple overrides are separated by `#`. Each override is `KEY=VALUE`.

### 4.2 Fractal Parameter Overrides

To override a specific fractal formula's parameter:
```bash
mandelbulber2 -n myscene.fract -O "fractal1_power=8"
```

The `fractal<N>_` prefix is stripped and the parameter is routed to `gParFractal->at(N-1)`:

```cpp
QRegularExpression reType("^fractal([0-9]+)_(.*)$");
QRegularExpressionMatch matchType = reType.match(overrideParameters[i]);
if (matchType.hasMatch()) {
    fractalIndex = matchType.captured(1).toInt() - 1;  // 1-based to 0-based
    overrideParameters[i] = matchType.captured(2);
    gParFractal->at(fractalIndex)->Set(key, value);
}
```

### 4.3 How Overrides Are Applied

Overrides are processed **after** the settings file is loaded, so they take precedence:

```cpp
// In ReadCLI():
handleArgs();              // 1. Load settings file
handleOverrideParameters(); // 2. Apply CLI overrides
handleResolution();         // 3. Apply resolution override
// ... etc
```

**For developers**: If you add a new CLI option that modifies parameters, place its handler between `handleArgs()` and the animation handlers to ensure it overrides file settings.

---

## 5. NetRender Handling

### 5.1 Server Mode

```cpp
void cCommandLineInterface::handleServer() {
    // Parse optional port
    if (cliData.portText != "") {
        int port = cliData.portText.toInt(&checkParse);
        gPar->Set("netrender_server_local_port", port);
    }
    
    gNetRender->SetServer(gPar->Get<int>("netrender_server_local_port"));
    
    // Wait 5 seconds for clients to connect
    QElapsedTimer timer;
    timer.start();
    while (timer.elapsed() < 5000) {
        gApplication->processEvents();
    }
}
```

The server waits **5 seconds** for clients before starting the render.¹

### 5.2 Client Mode

```cpp
void cCommandLineInterface::handleClient() {
    gPar->Set("netrender_client_remote_address", cliData.host);
    if (cliData.portText != "") {
        gPar->Set("netrender_client_remote_port", port);
    }
    cliOperationalMode = modeNetrender;
}
```

In `ProcessCLI()`, the client connects and enters Qt's event loop:
```cpp
case modeNetrender:
    gNetRender->SetClient(gPar->Get<QString>("netrender_client_remote_address"),
                          gPar->Get<int>("netrender_client_remote_port"));
    gApplication->exec();
    break;
```

---

## 6. Queue Processing

### 6.1 Input Types

When multiple positional arguments are given, the CLI enters queue mode and processes each argument:

| Input Type | Extension / Check | Action |
|-----------|-------------------|--------|
| Folder | `QDir.exists()` | `gQueue->AppendFolder()` — adds all `.fract` files |
| Queue list | `.fractlist` | `gQueue->AppendList()` — appends all entries from list file |
| Single file | anything else | `gQueue->Append()` — adds one file to queue |

### 6.2 Queue Mode Invocation

```bash
# Single queue file
mandelbulber2 -q myqueue.fractlist

# Folder of fract files
mandelbulber2 -q ./my_fractals/

# Multiple files (auto queue mode)
mandelbulber2 -n file1.fract file2.fract file3.fract
```

---

## 7. Benchmark & Test Modes

### 7.1 Test Mode

```cpp
void cCommandLineInterface::runTestCasesAndExit() {
    systemData.noGui = true;
    QStringList arguments = gApplication->arguments();
    arguments.removeOne("--test");
    arguments.removeOne("-t");
    
    // Also strip output arguments so tests don't write files
    arguments.removeAt(index_of("-o")); arguments.removeAt(index_of("-o") + 1);
    
    Test test(Test::simpleTestMode);
    int status = QTest::qExec(&test, arguments);
    exit(status);
}
```

Uses Qt's `QTest` framework. The `--test` flag is stripped from arguments before passing to `qExec()`.

### 7.2 Benchmark Mode

```cpp
void cCommandLineInterface::runBenchmarksAndExit() {
    qputenv("QTEST_FUNCTION_TIMEOUT", QByteArray("86400000"));  // 24h timeout
    
    int difficulty = 10;  // Default
    if (args.size() > 0) {
        difficulty = args[0].toInt(&checkParse);
    }
    
    Test test(Test::benchmarkTestMode, difficulty, exampleOutputPath);
    QTest::qExec(&test, arguments);
}
```

Difficulty range: 1 (very easy) to >20 (very hard). Benchmark images can be saved to a folder via `-o`.

---

## 8. Adding a New CLI Flag

### Step-by-step recipe:

**1. Declare the option in the constructor:**
```cpp
const QCommandLineOption myNewOption(
    QStringList({"m", "my-flag"}),
    QCoreApplication::translate("main", "Description of what it does"),
    QCoreApplication::translate("main", "VALUE"));  // Optional: requires a value

parser.addOption(myNewOption);
```

**2. Store the parsed value in `cliData`:**
```cpp
// In constructor, after parser.process():
cliData.myFlag = parser.isSet(myNewOption);
cliData.myFlagText = parser.value(myNewOption);
```

**3. Add field to `sCliData` struct:**
```cpp
struct sCliData {
    // ... existing fields ...
    bool myFlag;
    QString myFlagText;
};
```

**4. Add handler method declaration:**
```cpp
// In header private section:
void handleMyFlag();
```

**5. Implement the handler:**
```cpp
void cCommandLineInterface::handleMyFlag() {
    if (cliData.myFlag) {
        // Do something
        gPar->Set("some_parameter", cliData.myFlagText);
    }
}
```

**6. Call the handler in `ReadCLI()`:**
```cpp
void cCommandLineInterface::ReadCLI() {
    // ... existing handlers ...
    if (cliData.myFlag) handleMyFlag();
    // ...
}
```

**7. Handle the new mode in `ProcessCLI()` (if needed):**
```cpp
// Add to enum:
enum cliOperationalMode {
    // ... existing modes ...
    modeMyNewMode
};

// Add to switch:
case modeMyNewMode:
    gMainInterface->headless = new cHeadless(gMainInterface);
    gMainInterface->headless->DoMyNewThing();
    break;
```

---

## 9. Error Codes

| Code | Name | When Triggered |
|------|------|----------------|
| -10 | `cliErrorServerInvalidPort` | `--server` with invalid port |
| -11 | `cliErrorClientInvalidPort` | `--host` with invalid port |
| -12 | `cliErrorQueueInit` | Queue initialization failure |
| -13 | `cliErrorLoadSettingsFile` | Settings file not found |
| -14 | `cliErrorResolutionInvalid` | `-r` format invalid or dimensions ≤ 0 |
| -15 | `cliErrorFPKInvalid` | `--fpk` value ≤ 0 |
| -16 | `cliErrorImageFileFormatInvalid` | `-f` not in allowed list |
| -17 | `cliErrorSettingsFileNotSpecified` | NoGUI mode without settings file |
| -30 | `cliErrorFlightNoFrames` | Flight animation has 0 frames |
| -31 | `cliErrorFlightStartFrameOutOfRange` | Start frame > total flight frames |
| -32 | `cliErrorFlightEndFrameSmallerStartFrame` | End ≤ start for flight |
| -33 | `cliErrorFlightEndFrameOutOfRange` | End frame > total flight frames |
| -40 | `cliErrorKeyframeNoFrames` | Keyframe animation has 0 frames |
| -41 | `cliErrorKeyframeStartFrameOutOfRange` | Start frame > total keyframe frames |
| -42 | `cliErrorKeyframeEndFrameSmallerStartFrame` | End ≤ start for keyframes |
| -43 | `cliErrorKeyframeEndFrameOutOfRange` | End frame > total keyframe frames |
| -50 | `cliErrorVoxelOutputFolderDoesNotExists` | Voxel output folder missing |
| -51 | `cliErrorVoxelOutputFormatInvalid` | Voxel format not `ply` or `slice` |
| -60 | `cliErrorBenchmarkOutputFolderInvalid` | Benchmark output path invalid |
| -70 | `cliErrorOpenClNotCompiled` | `--gpu` without OpenCL build |
| -71 | `cliErrorOpenClNoPlatform` | No OpenCL platforms found |
| -72 | `cliErrorOpenClNoDevice` | No OpenCL devices found |

---

## 10. Footnotes: Known Issues

¹ **`handleServer()` busy-waits with `processEvents()` for 5 seconds.** The server enters a `while (timer.elapsed() < 5000)` loop calling `QApplication::processEvents()`. This blocks the constructor thread but keeps the Qt event loop alive. There's no way to extend the wait time or early-exit if all clients connect.

² **`handleOverrideParameters()` splits on `=` with regex, but values containing `=` are truncated.** For example, `-O "my_param=a=b"` splits into `["my_param", "a", "b"]` and the value becomes `"a"` (size==2 check passes, rest is ignored).³

³ **`runTestCasesAndExit()` and `runBenchmarksAndExit()` use `arguments.removeOne()`** which only removes the first occurrence. If `--test` appears twice in the command line, the second instance is passed to `QTest::qExec()`.

⁴ **`handleStartFrame()` and `handleEndFrame()` don't check `checkParse` after `toInt()`.** If the user passes `-s abc`, `toInt()` fails but the resulting `startFrame` is `0`, which is treated as a valid frame.⁴

⁵ **`printOpenCLHelpAndExit()` allocates `gOpenCl` with `new` but never `delete`s it.** This is a minor memory leak only triggered by `--help-opencl`.

⁶ **`handleServer()` sets `cliData.nogui = true` but doesn't set `cliOperationalMode`.** After `handleServer()` returns, `ReadCLI()` continues and may fall through to `modeStill` if no animation flags are set. The server mode should probably set `cliOperationalMode` explicitly.

⁷ **`handleArgs()` catches `QString&` by value instead of reference.** While `QString` is implicitly shared (copy-on-write), catching exceptions by value is generally discouraged in C++.⁵

⁸ **The `--touch` flag exits with `exit(0)` inside `handleArgs()`** rather than using a `[[noreturn]]` method like other help flags. This is inconsistent with the codebase style.

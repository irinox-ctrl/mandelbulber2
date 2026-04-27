# MANDELBULBER2 ERROR MESSAGE: Developer Guide

**Datum**: 2026-04-22  
**Bestanden**: `error_message.hpp`, `error_message.cpp`  
**Scope**: Cross-thread error/warning/info display with deduplication  
**Focus**: GUI vs headless dual mode, thread-safety via queued signals, message throttling  

---

## 1. Overview

`cErrorMessage` is a **dual-mode message handler** that displays errors, warnings, and info messages either as GUI popup dialogs (when running with a QApplication) or as colored console output (when running headless/CLI).

It also provides **cross-thread message posting** via Qt signals, allowing worker threads to safely display messages without directly touching GUI widgets.

---

## 2. Architecture

```
Calling Code
    │
    ├── showMessage()          ← Direct call (any thread, but prefer main thread)
    │
    └── showMessageFromOtherThread()  ← Emit signal → queued to main thread
                │
                ▼
        signalShowMessage ──Qt::QueuedConnection──► slotShowMessage
                │                                         │
                │                                         ▼
                │                              showMessage(text, type, parent)
                │                                         │
                ▼                                         ▼
         [Non-GUI thread]                       [Main thread event loop]
```

---

## 3. API

### 3.1 Direct Display: `showMessage()` (static)

```cpp
static void showMessage(QString text, enumMessageType messageType, QWidget *parent = nullptr);
```

Can be called from any thread, but if called from a worker thread while in GUI mode, it will **directly construct and show a QMessageBox on that thread**. This is generally unsafe — Qt GUI operations must happen on the main thread.

**Safe usage**: Only call from the main thread, or when in headless mode.

### 3.2 Thread-Safe Display: `showMessageFromOtherThread()`

```cpp
void showMessageFromOtherThread(QString text, enumMessageType messageType, QWidget *parent = nullptr);
```

Emits `signalShowMessage`, which is connected to `slotShowMessage` via **`Qt::QueuedConnection`**:

```cpp
connect(this, &cErrorMessage::signalShowMessage, this, &cErrorMessage::slotShowMessage,
    Qt::QueuedConnection);
```

**How it works**: When emitted from a non-GUI thread, the signal event is placed in the **main thread's event queue**. The main thread's event loop later picks it up and calls `slotShowMessage`, which delegates to `showMessage()` on the correct thread.¹

### 3.3 Message Types

| Type | GUI Icon | Console Color | Stream |
|------|----------|---------------|--------|
| `warningMessage` | ⚠️ Warning | Magenta | stderr |
| `errorMessage` | ❌ Critical | Red on White | stderr |
| `infoMessage` | ℹ️ Information | Green | stdout |

---

## 4. GUI Mode (`QApplication` detected)

### 4.1 Message Deduplication

```cpp
if ((lastMessage != text && lastMessageTime.elapsed() > 1000) || lastMessage.isEmpty())
{
    QMessageBox *messageBox = new QMessageBox(parent);
    messageBox->exec();
    delete messageBox;
    lastMessageTime.restart();
}
```

A popup is shown only if:
- **Text differs** from last message, **OR**
- **More than 1 second** has elapsed since the last popup, **OR**
- **No previous message** exists

**Logic analysis**:

| Scenario | lastMessage | elapsed | Popup? | Why |
|----------|-------------|---------|--------|-----|
| First message | empty | N/A | ✅ | `lastMessage.isEmpty()` |
| Same message, < 1s | same | <1000 | ❌ | Both conditions fail |
| Same message, > 1s | same | >1000 | ✅ | elapsed > 1000 |
| Different message, < 1s | different | <1000 | ✅ | `lastMessage != text` |
| Different message, > 1s | different | >1000 | ✅ | Both conditions pass |

**Key insight**: The 1-second throttle only applies to **identical** messages. A rapid sequence of **different** error messages will each trigger a popup, potentially creating a cascade of modal dialogs.²

### 4.2 Modal Dialog Behavior

`QMessageBox::exec()` starts a **local event loop**. While the dialog is open:
- The main thread continues processing events (via the modal loop)
- Other signals/slots may be processed
- The calling code blocks until the user dismisses the dialog

This is standard Qt behavior but can lead to **reentrancy** if other code triggers messages while a dialog is already open.³

---

## 5. Headless Mode (no `QApplication`)

When `gApplication` is not a `QApplication` (e.g., CLI rendering mode), messages are printed to the console with ANSI color codes via `cHeadless::colorize()`:

| Type | ANSI Foreground | ANSI Background | Bold |
|------|-----------------|-----------------|------|
| Warning | Magenta | Default | Yes |
| Error | Red | White | Yes |
| Info | Green | Default | Yes |

**No deduplication** is applied in headless mode — all messages are printed immediately.

---

## 6. Footnotes: Known Issues

¹ **Thread-safety depends on `gErrorMessage` living in main thread**: `showMessageFromOtherThread()` emits a signal on the `cErrorMessage` instance. For `Qt::QueuedConnection` to deliver to the main thread, the `cErrorMessage` object must have been created in (or moved to) the main thread. If `gErrorMessage` is created in a worker thread, the queued connection delivers to that worker thread's event loop instead, defeating the purpose.⁴

² **Deduplication throttle is per-message, not global**: The condition `(lastMessage != text && elapsed > 1000)` uses AND logic for the two checks. For a *different* message, `lastMessage != text` is true regardless of elapsed time, so the popup always shows. In a render with multiple rapid errors (e.g., "Out of memory", "OpenCL kernel failed", "File not found"), the user gets 3 modal dialogs in quick succession. A global cooldown (e.g., max 1 popup per second regardless of content) would be less intrusive.⁵

³ **Potential reentrancy via modal event loop**: When `QMessageBox::exec()` runs its local event loop, pending signals in the queue may be processed. If one of those signals triggers another `showMessage()`, a second QMessageBox can appear while the first is still open. Qt handles nested dialogs, but this can lead to confusing UX and potential state corruption if the reentrant call modifies shared data.⁶

⁴ **`showMessage()` is static but not thread-safe in GUI mode**: The static method directly accesses GUI widgets (`new QMessageBox`, `exec()`). If called from a worker thread in GUI mode, this violates Qt's threading rule ("GUI objects must live in the main thread"). The method exists for convenience but is only safe when the caller is already on the main thread. The naming doesn't reflect this constraint.⁷

⁵ **Memory allocation per message**: Each displayed message allocates a new `QMessageBox` on the heap, shows it modally, and immediately deletes it. For an application that rarely shows errors this is fine, but for high-frequency warning scenarios (e.g., per-frame OpenCL warnings), the repeated allocation/deallocation is unnecessary overhead. A single reusable dialog or a non-blocking notification system would be more efficient.⁸

⁶ **`lastMessage` and `lastMessageTime` are static but not thread-safe**: Both are `static` members, meaning they're shared across all `cErrorMessage` instances. In a multi-threaded scenario where multiple threads call `showMessage()` directly (not via `showMessageFromOtherThread()`), concurrent reads/writes to `lastMessage` and `lastMessageTime` are data races. The code has no mutex protection.⁹

⁷ **Inconsistent `lastMessage` update timing**: `lastMessage = text` is set at the **end** of `showMessage()` (line 146), outside the `if (qobject_cast<QApplication *>...)` block. This means it's updated even in headless mode, even though headless mode doesn't use it for deduplication. More importantly, if `showMessage()` is called from multiple threads concurrently, the final assignment can overwrite a different thread's message, causing the deduplication check in yet another thread to compare against the wrong text.¹⁰

⁸ **Qt version branching for flush**: 
```cpp
#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
    outErr << messageText << "\n" << flush;
#else
    outErr << messageText << "\n" << Qt::flush;
#endif
```
This handles a Qt API change where `flush` manipulator was replaced by `Qt::flush` enum. The code supports Qt 5.14+ and older versions. The `infoMessage` branch doesn't flush at all — it relies on line-buffered stdout.¹¹

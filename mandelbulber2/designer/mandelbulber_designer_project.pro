# ============================================================
# Mandelbulber Designer Project
# ============================================================
# Open this file in Qt Designer to edit Mandelbulber UI files
# with full support for custom widgets.
#
# Usage:
#   1. Install the Designer Plugin first:
#      cd mandelbulber2/designer && qmake && make && sudo make install
#
#   2. Open this project in Qt Designer:
#      designer mandelbulber_designer_project.pro
#
#   3. Edit any .ui file under qt/ or formula/ui/
#
# ============================================================

QT += widgets uitools

TEMPLATE = app
TARGET = mandelbulber_designer_dummy

# ============================================================
# IMPORTANT: Include paths
# ============================================================
# The designer/ directory MUST come FIRST so Qt Designer uses
# the lightweight widget wrappers instead of the real ones.
# ============================================================
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/../qt
INCLUDEPATH += $$PWD/../src
INCLUDEPATH += $$PWD/../formula/definition
INCLUDEPATH += $$PWD/../third-party/stb

# ============================================================
# UI Files — All editable in Designer
# ============================================================

# Static UI files (main application)
FORMS += \
    $$PWD/../qt/dock_animation.ui \
    $$PWD/../qt/dock_effects.ui \
    $$PWD/../qt/dock_fractal.ui \
    $$PWD/../qt/dock_gamepad.ui \
    $$PWD/../qt/dock_image_adjustments.ui \
    $$PWD/../qt/dock_measurements.ui \
    $$PWD/../qt/dock_navigation.ui \
    $$PWD/../qt/dock_queue.ui \
    $$PWD/../qt/dock_rendering_engine.ui \
    $$PWD/../qt/dock_statistics.ui \
    $$PWD/../qt/render_window.ui \
    $$PWD/../qt/tab_fractal.ui \
    $$PWD/../qt/preferences_dialog.ui \
    $$PWD/../qt/material_editor.ui \
    $$PWD/../qt/light_editor.ui \
    $$PWD/../qt/primitives_manager.ui \
    $$PWD/../qt/custom_formula_editor.ui \
    $$PWD/../qt/audio_selector.ui \
    $$PWD/../qt/image_save_dialog.ui \
    $$PWD/../qt/mesh_export_dialog.ui \
    $$PWD/../qt/voxel_export_dialog.ui \
    $$PWD/../qt/navigator_window.ui \
    $$PWD/../qt/randomizer_dialog.ui \
    $$PWD/../qt/settings_browser.ui \
    $$PWD/../qt/settings_cleaner.ui \
    $$PWD/../qt/script_dialog.ui \
    $$PWD/../qt/detached_window.ui \
    $$PWD/../qt/light_sources_manager.ui \
    $$PWD/../qt/material_manager_view.ui \
    $$PWD/../qt/slider_popup.ui \
    $$PWD/../qt/objects_tree_widget.ui

# ============================================================
# Formula UI files (dynamic, loaded at runtime)
# ============================================================
# These are loaded from deploy/share/mandelbulber2/formula/ui/
# You can edit them directly in Designer after installing the plugin.
# ============================================================

FORMULA_UI_DIR = $$PWD/../deploy/share/mandelbulber2/formula/ui

# Include a representative sample (edit this list or use wildcard)
FORMS += \
    $$FORMULA_UI_DIR/mandelbox_fast.ui \
    $$FORMULA_UI_DIR/abox_mod13.ui \
    $$FORMULA_UI_DIR/pseudo_kleinian.ui

# Alternative: include ALL formula UI files (may be slow to load in Designer)
# FORMS += $$files($$FORMULA_UI_DIR/*.ui)

# ============================================================
# UI output directory
# ============================================================
UI_DIR = $$PWD/../qt

# ============================================================
# Dummy main — Designer only needs the project context
# ============================================================
SOURCES += $$PWD/dummy_main.cpp

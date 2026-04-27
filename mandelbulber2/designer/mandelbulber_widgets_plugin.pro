# ============================================================
# Mandelbulber Qt Designer Plugin Build File
# ============================================================
# Build & Install:
#   cd mandelbulber2/designer
#   qmake mandelbulber_widgets_plugin.pro
#   make
#   sudo make install
#
# Or copy manually:
#   sudo cp libmandelbulber_widgets_plugin.so /usr/lib/qt5/plugins/designer/
#
# Then restart Qt Designer.
# ============================================================

QT += widgets designer
CONFIG += plugin warn_on release

TARGET = mandelbulber_widgets_plugin
TEMPLATE = lib

# Plugin output directory
DESTDIR = $$PWD/../qmake/

# Source files for the plugin
HEADERS += \
    mandelbulber_widgets_plugin.h \
    my_double_spin_box.h \
    my_spin_box.h \
    my_check_box.h \
    my_combo_box.h \
    my_group_box.h \
    my_line_edit.h \
    my_color_button.h

SOURCES += \
    mandelbulber_widgets_plugin.cpp

# Installation path for Qt Designer plugins
unix {
    target.path = /usr/lib/qt5/plugins/designer
    INSTALLS += target
}

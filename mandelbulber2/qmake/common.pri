# qt dependencies
QT += core gui uitools widgets network testlib multimedia qml concurrent
macx:QT += svg

CONFIG += link_pkgconfig

unix:!macx:CONFIG += c++14
macx:!m1:CONFIG += c++14
macx:m1:CONFIG += c++17

m1: {
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 12.0
}

# specify paths to misc ressources
ROOT = $$PWD/..
SHARED = $$ROOT/deploy/share/mandelbulber2

# Linux dev builds: use this checkout’s deploy/share (OpenCL, formula, etc.).
# Without this, the binary looks for ../share/mandelbulber2 above the exe or /usr/share/mandelbulber2 — often stale.
# Packaging: pass SHARED_PATH to qmake so installer.pri sets CUSTOM_PREFIX instead (this block is skipped).
unix:!macx:isEmpty(SHARED_PATH) {
	SHARE_DATA_ABS = $$clean_path($$absolute_path($$ROOT/deploy/share/mandelbulber2))
	SHARE_DOC_ABS = $$clean_path($$absolute_path($$ROOT/deploy/doc))
	DEFINES += SHARED_DIR=\\\"$$SHARE_DATA_ABS\\\"
	DEFINES += SHARED_DOC_DIR=\\\"$$SHARE_DOC_ABS\\\"
}

# Auto-sync formula files to deploy directory (symlink for dev builds)
# Created at BOTH qmake time (immediate) and link time (rebuild safety)
FORMULA_SRC = $$clean_path($$absolute_path($$ROOT/formula))
FORMULA_DST = $$clean_path($$absolute_path($$ROOT/deploy/share/mandelbulber2/formula))
unix:system(rm -rf $$FORMULA_DST && mkdir -p $$clean_path($$absolute_path($$ROOT/deploy/share/mandelbulber2)) && ln -sf $$FORMULA_SRC $$FORMULA_DST)
unix:QMAKE_POST_LINK += rm -rf $$FORMULA_DST && \
	mkdir -p $$clean_path($$absolute_path($$ROOT/deploy/share/mandelbulber2)) && \
	ln -sf $$FORMULA_SRC $$FORMULA_DST

QMAKE_FULL_VERSION = 2.35
QMAKE_TARGET_BUNDLE_PREFIX = com.mandelbulber
VERSION = 2.35

#m1:DEFINES += NO_AUDIO_OUTPUT
#m1:DEFINES += NO_QT_MULTIMEDIA_AUDIO

# optional dependecies
qtHaveModule(gamepad){
	QT += gamepad
	DEFINES += USE_GAMEPAD
	message("Use QtGamepad module")
}

packagesExist(OpenEXR){
	PKGCONFIG += OpenEXR
	DEFINES += USE_EXR
	message("Use OpenEXR libraries for EXR files")
}

packagesExist(libtiff-4){
	PKGCONFIG += libtiff-4
}
macx|win32|packagesExist(libtiff-4) {
	LIBS += -ltiff
	DEFINES += USE_TIFF
	message("Use tiff library for TIFF files")
}

packagesExist(sndfile){
	PKGCONFIG += sndfile
}
macx|win32|packagesExist(sndfile) {
	LIBS += -lsndfile
	DEFINES += USE_SNDFILE
	message("Use sndfile library for WAV files")
}

opencl {
	DEFINES += USE_OPENCL
	!win32:LIBS += -lOpenCL
        macx:LIBS -= -lOpenCL
        macx:LIBS += -framework OpenCL
	message("Use OpenCL library")
}

# required for proper logging output
DEFINES += QT_MESSAGELOGCONTEXT

TARGET = mandelbulber2 
TEMPLATE = app

CONFIG += qt thread

SOURCES +=  $$ROOT/src/*.cpp
SOURCES +=  $$ROOT/qt/*.cpp
SOURCES +=  $$ROOT/formula/definition/*.cpp

HEADERS += $$ROOT/src/*.hpp
HEADERS += $$ROOT/src/*.h
HEADERS += $$ROOT/qt/*.hpp
HEADERS += $$ROOT/qt/*.h
HEADERS += $$ROOT/formula/definition/*.h
HEADERS += $$ROOT/formula/definition/*.hpp
HEADERS += $$ROOT/third-party/stb/*.h

FORMS += $$ROOT/qt/*.ui

RESOURCES = $$ROOT/qt/icons.qrc

UI_DIR = $$ROOT/qt

INCLUDEPATH += $$ROOT/

TRANSLATIONS = $$ROOT/language/en.ts\
               $$ROOT/language/de.ts\
               $$ROOT/language/pl.ts\
               $$ROOT/language/it.ts\
               $$ROOT/language/nl.ts\
               $$ROOT/language/es.ts

# copy all system flags
QMAKE_CXXFLAGS += $$(CXXFLAGS)
QMAKE_CFLAGS += $$(CFLAGS)
QMAKE_CXXFLAGS += $$(CPPFLAGS)
QMAKE_CFLAGS += $$(CPPFLAGS)
QMAKE_LFLAGS += $$(LDFLAGS)

# TODO: is this still required?
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_LFLAGS_RELEASE -= -O1

# compiler build flags
unix:!macx:QMAKE_CXXFLAGS += -ffast-math -fopenmp
macx:!m1:QMAKE_CXXFLAGS += -ffast-math -fopenmp
#macx:m1:QMAKE_CXXFLAGS += -ffast-math -Xpreprocessor -fopenmp
macx:m1:QMAKE_CXXFLAGS += -ffast-math -Xpreprocessor

macx:DEFINES += "SHARED_DIR_IS_APP_DIR" 

m1:QMAKE_CXXFLAGS += -I/opt/homebrew/include

# library linking
unix:!macx:LIBS += -lpng -lgsl -lgslcblas -llzo2 -lmpfr -lgmp -fopenmp
unix:!macx:DEFINES += USE_MPFR
macx:!m1:LIBS += -lpng -lgsl -lgslcblas -llzo2 -fopenmp
#macx:m1:LIBS += -lpng -lgsl -lgslcblas -llzo2 -lomp
macx:m1:LIBS += -lpng -lgsl -lgslcblas -llzo2

macx:!m1:LIBS += -framework CoreFoundation
win32:LIBS += -lz

# mac specific options
macx:!m1:QMAKE_CC=/usr/local/opt/llvm/bin/clang
macx:!m1:QMAKE_CXX=/usr/local/opt/llvm/bin/clang++
macx:!m1:QMAKE_LINK=/usr/local/opt/llvm/bin/clang++
macx:!m1:INCLUDEPATH += /usr/local/opt/llvm/include/
macx:!m1:LIBS += -L/usr/local/opt/llvm/lib/
macx:LIBS += -L/opt/homebrew/lib/
macx:ICON = $$ROOT/mac/mandelbulber2.icns

# gsl png osx absolute path
macx:!m1:INCLUDEPATH += /usr/local/include/
macx:!m1:LIBS += -L/usr/local/lib/





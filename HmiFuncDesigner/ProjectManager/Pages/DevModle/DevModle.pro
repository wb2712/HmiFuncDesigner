QT += core gui widgets

TARGET = DevModle
TEMPLATE = lib

CONFIG  += plugin

BUILD_DIR = $$clean_path($$OUT_PWD)
LIB_DIR = $$clean_path($$BUILD_DIR/../../../../lib)
TOP_SRC_DIR = $$clean_path($$BUILD_DIR/../../../..)

DESTDIR = $$clean_path($$LIB_DIR/pages)
win32 {
    DLLDESTDIR = $$BUILD_DIR/../../../../HmiFuncDesignerBin/bin/pages
}
unix {
    DESTDIR = $$BUILD_DIR/../../../../HmiFuncDesignerBin/bin/pages
    LIB_DIR = $$clean_path($$BUILD_DIR/../../../../HmiFuncDesignerBin/bin)
}

LIBS += -L$$clean_path($$LIB_DIR) -lshared
LIBS += -L$$clean_path($$LIB_DIR) -lcore

INCLUDEPATH += \
    $$TOP_SRC_DIR/HmiFuncDesigner/libs/core \
    $$TOP_SRC_DIR/HmiFuncDesigner/libs/shared

HEADERS += \
    ../../Public/userevent.h \
    DevModle.h \
    DevModleManagerWin.h \
    DevModlePlugin.h

SOURCES += \
    ../../Public/userevent.cpp \
    DevModle.cpp \
    DevModleManagerWin.cpp \
    DevModlePlugin.cpp


RESOURCES += \
    images.qrc

FORMS += \
    DevModleManagerWin.ui


DISTFILES += \
    DevModlePlugin.json


message("LIBS DevModle  $$LIBS")

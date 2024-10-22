include(../../HmiFuncDesigner.pri)

QT += core gui xml
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += sql

TARGET = ProjectManager
TEMPLATE = app

DESTDIR = $$IDE_BIN_PATH

INCLUDEPATH += .
INCLUDEPATH += $$PWD/widget
INCLUDEPATH += $$PWD/ProjData
INCLUDEPATH += $$PWD/../../common/qtsingleapplication
#INCLUDEPATH += $$PWD/../../common/register
INCLUDEPATH += $$PWD/../QtPropertyBrowserEx
INCLUDEPATH += $$PWD/../../libs/core
INCLUDEPATH += $$PWD/../../libs/shared
INCLUDEPATH += $$PWD/../../libs/shared/projdata
INCLUDEPATH += $$PWD/../../libs/gradienteditor
INCLUDEPATH += $$PWD/../../libs/utils

include($$PWD/../../common/qtsingleapplication/qtsingleapplication.pri)
#include($$PWD/../../common/register/register.pri)

#DEFINES += QT_NO_DEBUG_OUTPUT

LIB_SUFFIX=""
CONFIG(debug, debug|release) { #debug
    win32 {
        LIB_SUFFIX=d
    }
}

BUILD_DIR = $$clean_path($$OUT_PWD)
LIB_DIR = $$clean_path($$BUILD_DIR/../../../lib)
#LIBS += -L$$clean_path($$LIB_DIR) -lshared
#message("LIBS----  $$LIBS")

LIBS += -L$$clean_path($$LIB_DIR) -lcsv$${LIB_SUFFIX}
LIBS += -L$$clean_path($$LIB_DIR) -lqscintilla2_qt$${QT_MAJOR_VERSION}$${LIB_SUFFIX}
LIBS += -L$$clean_path($$LIB_DIR) -lutils$${LIB_SUFFIX}
LIBS += -L$$clean_path($$LIB_DIR) -lcore
LIBS += -L$$clean_path($$LIB_DIR) -lshared
LIBS += -L$$clean_path($$LIB_DIR) -lgradienteditor
LIBS += -L$$clean_path($$LIB_DIR)/pages -lCmdManager




unix {
    # suppress the default RPATH if you wish
    # QMAKE_LFLAGS_RPATH=
    QMAKE_LFLAGS += "-Wl,-rpath,\'"$$LINK_LIBRARY_PATH"\'"
}

SOURCES += main.cpp\
    ../Public/userevent.cpp \
    EmsConfigExport.cpp \
    MainWindow.cpp \
    ProjectTreeView.cpp \
    TableviewDelegate.cpp \
    ProjectDownloadDialog.cpp \
    ProjectUploadDialog.cpp \
    AboutDialog.cpp \
#    TagFuncEditDialog.cpp \
    VerifyPasswordDialog.cpp \
    widget/QFramelessDockWidget.cpp \
    widget/QIPAddressEdit.cpp \
    widget/QQuickInputLineEdit.cpp \
#    ../Public/PubTool.cpp \
    ../Public/Element.cpp \
    ../Public/ElementGroup.cpp

HEADERS  += MainWindow.h \
    ../Public/userevent.h \
    ../Public/Public.h \
    EmsConfigExport.h \
    ProjectTreeView.h \
    TableviewDelegate.h \
    ProjectDownloadDialog.h \
    ProjectUploadDialog.h \
    AboutDialog.h \
#    TagFuncEditDialog.h \
    FileTansfer.h \
    VerifyPasswordDialog.h \
    widget/QFramelessDockWidget.h \
    widget/QIPAddressEdit.h \
    widget/QQuickInputLineEdit.h \
    ../Public/PublicDefine.h \
#    ../Public/PubTool.h \
    ../IDrawApplicationPlugin/IDrawApplicationPlugin.h \
    ../Public/Element.h \
    ../Public/ElementGroup.h


FORMS    += \
    ProjectDownloadDialog.ui \
    ProjectUploadDialog.ui \
    AboutDialog.ui \
    widget/QIPAddressEdit.ui

RESOURCES += \
    images.qrc \
    images1.qrc \
    DrawAppImages.qrc

# windows application icon
RC_FILE = ProjectManager.rc

#or
#RC_ICONS = project.ico


######################################################

DISTFILES += \
    $$IDE_BIN_PATH/Config/DrawAppJScriptFun.xml \
    $$IDE_BIN_PATH/Config/ElementSupportEvents.xml

CODECFORTR = UTF-8
TRANSLATIONS += chinese.ts


message("LIBS ProjectManager $$LIBS")

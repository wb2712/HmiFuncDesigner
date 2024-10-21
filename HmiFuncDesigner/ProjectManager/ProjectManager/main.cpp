﻿#include "MainWindow.h"
#include "VersionInfo.h"
#include "qtsingleapplication.h"
#include "configutils.h"
#include "../../libs/shared/pluginloader.h"
#include "../../libs/shared/qbaseinit.h"
#include "../../libs/core/qbaseinit.h"
#include "../../libs/core/qsoftcore.h"
#include <QApplication>
#include <QTextCodec>
#include <QFont>
#include <QTranslator>
#include <QLibrary>
#include <QDebug>
#include <windows.h>
#include "../shared/projdata/Tag.h"


int main(int argc, char *argv[])
{

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QtSingleApplication app(argc, argv);

    if (app.isRunning())
        return !app.sendMessage("project manager start " + app.applicationDirPath());

    app.setOrganizationName("JasonWangCtd");
    app.setApplicationName("ProjectManager");
    app.setApplicationDisplayName("ProjectManager");
    app.setApplicationVersion(QString("V%1").arg(VER_FILE));
    app.setWindowIcon(QIcon(":/images/appicon.png"));

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QTranslator translator;
    if(translator.load("chinese.qm", QApplication::applicationDirPath()))
        qApp->installTranslator(&translator);

    QFont font;
    font.setFamily("宋体");
    font.setPointSize(10);
    app.setFont(font);

    qRegisterBaseProperty();
    qRegisterBasePropertyEditor();
    qRegisterBaseHost();

    PluginLoader::loadPlugin(app.applicationDirPath() + "/plugins.xml");

    MainWindow win;
    app.setActivationWindow(&win);
    win.show();

    return app.exec();
}

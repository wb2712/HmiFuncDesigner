#include "DevModlePlugin.h"
#include "DevModle.h"
#include <qplugin.h>
#include <QIcon>
#include <QVariant>
#include "DevModleManagerWin.h"
void DevModlePlugin::createWidget()
{
//    m_widget = new DevModle;
    m_widget = new DevModleManagerWin;
    m_widget->setProperty("panelwidget", true);
}

QString DevModlePlugin::getPageName()
{
    return "DevModle";
}

QString DevModlePlugin::getPluginName()
{
    return PLUGIN_NAME;
}

QIcon DevModlePlugin::getPageIcon()
{
    return QIcon();
}

int DevModlePlugin::getIndex()
{
    return 3;
}

bool DevModlePlugin::getEnabled()
{
    return false;
}


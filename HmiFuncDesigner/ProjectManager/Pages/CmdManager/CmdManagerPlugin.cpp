#include "CmdManagerPlugin.h"
#include "CmdManagerWin.h"
#include <qplugin.h>
#include <QIcon>
#include <QVariant>

void CmdManagerPlugin::createWidget()
{
    m_widget = new CmdManagerWin;
    m_widget->setProperty("panelwidget", true);
}

QString CmdManagerPlugin::getPageName()
{
    return "CmdMgr";
}

QString CmdManagerPlugin::getPluginName()
{
    return PLUGIN_NAME;
}

QIcon CmdManagerPlugin::getPageIcon()
{
    return QIcon();
}

int CmdManagerPlugin::getIndex()
{
    return 4;
}

bool CmdManagerPlugin::getEnabled()
{
    return false;
}


#include "devmanagerplugin.h"
#include "devmanagerwin.h"
#include <qplugin.h>
#include <QIcon>
#include <QVariant>

void DevManagerPlugin::createWidget()
{
    m_widget = new DevManagerWin;
    m_widget->setProperty("panelwidget", true);
    TagManager::GetInstance().registryTagClass("DeviceTag", QSharedPointer<Tag>(new DeviceTag()));

}

QString DevManagerPlugin::getPageName()
{
    return "DevMgr";
}

QString DevManagerPlugin::getPluginName()
{
    return PLUGIN_NAME;
}

QIcon DevManagerPlugin::getPageIcon()
{
    return QIcon();
}

int DevManagerPlugin::getIndex()
{
    return 4;
}

bool DevManagerPlugin::getEnabled()
{
    return false;
}


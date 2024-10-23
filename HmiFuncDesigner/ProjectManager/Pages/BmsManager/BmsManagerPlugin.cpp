#include "BmsManagerPlugin.h"
#include "BmsManagerWin.h"
#include <qplugin.h>
#include <QIcon>
#include <QVariant>
#include "BmsEditDialog/BmsTag.h"


void BmsManagerPlugin::createWidget()
{
    m_widget = new BmsManagerWin;
    m_widget->setProperty("panelwidget", true);

    TagManager::GetInstance().registryTagClass("BmsTag", QSharedPointer<Tag>(new BmsTag()));
}

QString BmsManagerPlugin::getPageName()
{
    return "BmsMgr";
}

QString BmsManagerPlugin::getPluginName()
{
    return PLUGIN_NAME;
}

QIcon BmsManagerPlugin::getPageIcon()
{
    return QIcon();
}

int BmsManagerPlugin::getIndex()
{
    return 4;
}

bool BmsManagerPlugin::getEnabled()
{
    return false;
}


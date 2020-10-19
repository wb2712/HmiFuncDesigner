#ifndef SCRIPT_H
#define SCRIPT_H

#include <QString>
#include <QStringList>
#include <QList>
#include "XMLObject.h"

class ScriptObject
{
public:
    QString m_szName;
    bool m_bInUse;
    QString m_szDescription;
    QString m_szRunMode;
    QString m_szRunModeArgs;
    QString m_szScriptText;
};


class Script
{
public:
    Script();
    ~Script();

    void AddScriptObject(ScriptObject * obj);
    void ModifyScriptObject(ScriptObject * oldobj, ScriptObject * newobj);
    void DeleteScriptObject(ScriptObject * obj);
    ScriptObject *GetScriptObject(const QString &szName);

    bool openFromXml(XMLObject *pXmlObj);
    bool saveToXml(XMLObject *pXmlObj);

public:
    QList<ScriptObject *> m_listScriptObjects;
};


#endif // SCRIPT_H

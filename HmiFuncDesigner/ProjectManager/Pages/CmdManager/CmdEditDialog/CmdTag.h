#ifndef CMDTAG_H
#define CMDTAG_H
#include "../shared/projdata/Tag.h"

class CmdTag : public Tag
{
public:
    CmdTag();
    CmdTag(const CmdTag &obj);
    CmdTag &operator=(const CmdTag &obj);
    virtual ~CmdTag();

    void copyObject(const CmdTag &obj);

    Tag *clone() const override
    {
        return new CmdTag();
    }

    bool openFromXml(XMLObject *pXmlObj) override;
    bool saveToXml(XMLObject *pXmlObj) override;

    QString toXmlNodeString() override;
    bool fromXmlNodeString(const QString &szNode) override;

    QJsonObject toJsonObject() override;
    void fromJsonObject(QJsonObject jsonObj) override;

public:
    ////////////////////<基本信息>//////////////////////////

    QString m_cmdType   = ""; // 命令类型
    QVector<QVector<QString>> m_args; // 命令参数

    QString m_remark   = ""; // 变量描述
    QString m_ownGroup = ""; // 变量所属组
    QString m_devType  = ""; // 变量设备类型-设备协议名称, 内存变量-MEMORY, 系统变量-SYSTEM

private:
    bool saveToXmlInner(XMLObject *pXmlObj) override;
};

#endif // CMDTAG_H

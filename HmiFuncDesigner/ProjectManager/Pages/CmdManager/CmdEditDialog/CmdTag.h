#ifndef CMDTAG_H
#define CMDTAG_H
#include "../shared/projdata/Tag.h"


class  CmdTag: public Tag
{
public:
    CmdTag();
    CmdTag(const CmdTag &obj);
    CmdTag &operator=(const CmdTag &obj);
    virtual ~CmdTag();

    void copyObject(const CmdTag &obj) ;

    Tag* clone() const override {
         return new CmdTag();
    }

    virtual bool openFromXml(XMLObject *pXmlObj);
    virtual bool saveToXml(XMLObject *pXmlObj);

    virtual QString toXmlNodeString();
    virtual bool fromXmlNodeString(const QString &szNode);

    virtual QJsonObject toJsonObject();
    virtual void fromJsonObject(QJsonObject jsonObj);

public:
    ////////////////////<基本信息>//////////////////////////

        QString m_addrOffset = "0"; // 地址偏移
        QString m_dataType = ""; // 数据类型
        int m_addrOffsetBit = 0; // bit 取位
        QString formula = ""; // 计算公式
        QString m_remark = ""; // 变量描述
        QString m_ownGroup = ""; // 变量所属组
        QString m_devType = ""; // 变量设备类型-设备协议名称, 内存变量-MEMORY, 系统变量-SYSTEM

private:
    virtual bool saveToXmlInner(XMLObject *pXmlObj);
};


#endif // CMDTAG_H

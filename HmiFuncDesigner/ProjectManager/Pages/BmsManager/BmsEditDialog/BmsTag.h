#ifndef BMSTAG_H
#define BMSTAG_H
#include "../shared/projdata/Tag.h"

class BmsTag : public Tag
{

public:
    BmsTag();
    BmsTag(const BmsTag &obj);
    BmsTag &operator=(const BmsTag &obj);
    virtual ~BmsTag();

    void copyObject(const BmsTag &obj);

    Tag *clone() const override
    {
        return new BmsTag();
    }

    bool openFromXml(XMLObject *pXmlObj) override;
    bool saveToXml(XMLObject *pXmlObj) override;

    QString toXmlNodeString() override;
    bool fromXmlNodeString(const QString &szNode) override;

    QJsonObject toJsonObject() override;
    void fromJsonObject(QJsonObject jsonObj) override;

public:
    ////////////////////<基本信息>//////////////////////////

    int m_dataSource;  // 数据来源

    bool m_isCollect;
    QString m_unit = ""; // 变量单位
    QString m_addrOffset = "0"; // 地址偏移
    QString m_functionCodes = ""; // 功能
    QString m_rate = "0";    // 缩放计算
    QString m_dataType = ""; // 数据类

    bool m_isUpload;
    QString m_formula; // Redis 计算

    QString m_remark   = ""; // 变量描述
    QString m_ownGroup = ""; // 变量所属组

private:
    bool saveToXmlInner(XMLObject *pXmlObj) override;
};

#endif // BMSTAG_H

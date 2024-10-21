#ifndef TAG_H
#define TAG_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QMetaType>
#include <QJsonObject>
#include <QJsonValue>
#include "../xmlobject.h"
#include "../sharedlibglobal.h"
#include <QSharedPointer>
#include <mutex>


class SHAREDLIB_EXPORT Tag
{
public:
    Tag();
    Tag(const Tag &obj);
    Tag &operator=(const Tag &obj);

    void copyObject(const Tag &obj);
//    void copyFromTag(Tag obj);
    virtual ~Tag();
    virtual Tag* clone() const {
        return new Tag();
   };

    virtual bool openFromXml(XMLObject *pXmlObj);
    virtual bool saveToXml(XMLObject *pXmlObj);

    virtual QString toXmlNodeString();
    virtual bool fromXmlNodeString(const QString &szNode);

    virtual QJsonObject toJsonObject();
    virtual void fromJsonObject(QJsonObject jsonObj);

public:
    ////////////////////<基本信息>//////////////////////////
    int m_id = 0; // 变量ID
    int m_blockReadId = -1; // 块读变量ID
    QString m_name = ""; // 变量名称
    QString m_devType = ""; // 变量设备类型-设备协议名称, 内存变量-MEMORY, 系统变量-SYSTEM
    QString m_tagType = "";
private:
    virtual bool saveToXmlInner(XMLObject *pXmlObj);

};
Q_DECLARE_METATYPE(Tag)


class SHAREDLIB_EXPORT DeviceTag: public Tag
{
public:
    DeviceTag();
    DeviceTag(const DeviceTag &obj);
    DeviceTag &operator=(const DeviceTag &obj);
    virtual ~DeviceTag();

    void copyObject(const DeviceTag &obj) ;
//    void copyFromTag(DeviceTag obj);

    Tag* clone() const override {
         return new DeviceTag();
    }

    bool openFromXml(XMLObject *pXmlObj) override;
    bool saveToXml(XMLObject *pXmlObj) override;

    QString toXmlNodeString() override;
    bool fromXmlNodeString(const QString &szNode) override;

    QJsonObject toJsonObject() override;
    void fromJsonObject(QJsonObject jsonObj) override;

public:
    ////////////////////<基本信息>//////////////////////////

    QString m_unit = ""; // 变量单位
    QString m_addrType = ""; // 地址类型
    QString m_addrOffset = "0"; // 地址偏移
    QString m_functionCodes = ""; // 功能
    QString m_rate = "0";
    QString m_dataType = ""; // 数据类型
    int m_writeable = 1; // 读写类型  0-只读, 1-可写
    QString m_remark = ""; // 变量描述
    QString m_ownGroup = ""; // 变量所属组 

private:
    bool saveToXmlInner(XMLObject *pXmlObj) override;
};


class SHAREDLIB_EXPORT RedisTag: public Tag
{
public:
    RedisTag();
    RedisTag(const RedisTag &obj);
    RedisTag &operator=(const RedisTag &obj);
    virtual ~RedisTag();

    void copyObject(const RedisTag &obj) ;

    Tag* clone() const override {
         return new RedisTag();
    }

    bool openFromXml(XMLObject *pXmlObj) override;
    bool saveToXml(XMLObject *pXmlObj) override;

    QString toXmlNodeString() override;
    bool fromXmlNodeString(const QString &szNode) override;

    QJsonObject toJsonObject() override;
    void fromJsonObject(QJsonObject jsonObj) override;

public:
    ////////////////////<基本信息>//////////////////////////

//    QString m_unit = ""; // 变量单位
//    QString m_addrType = ""; // 地址类型
    QString m_addrOffset = "0"; // 地址偏移
//    QString m_addrType2 = ""; // 地址类型2
//    QString m_addrOffset2 = "0"; // 地址偏移2
    QString m_dataType = ""; // 数据类型
//    int m_writeable = 1; // 读写类型  0-只读, 1-可写
    int m_addrOffsetBit = 0; // bit 取位
    QString formula = ""; // 计算公式
    QString m_remark = ""; // 变量描述
    QString m_ownGroup = ""; // 变量所属组
    QString m_devType = ""; // 变量设备类型-设备协议名称, 内存变量-MEMORY, 系统变量-SYSTEM

private:
    bool saveToXmlInner(XMLObject *pXmlObj) override;
};


class SHAREDLIB_EXPORT TagManager
{
public:
    static TagManager& GetInstance();
    ~TagManager();

protected:
    TagManager();
    TagManager(const TagManager&) = delete;
    TagManager& operator=(const TagManager&) = delete;

public:

    bool openFromXml(XMLObject *pXmlObj);
    bool saveToXml(XMLObject *pXmlObj);
    bool saveBlockReadTagToXml(XMLObject *pXmlObj);
    //分配一个 ID
    int allocID();
    QSharedPointer<Tag> getTag(int id);
    QSharedPointer<Tag> getBlockReadTag(int id);
    void getAllTagName(QStringList &szList);
    void debugInfo();
    bool registryTagClass(QString className, QSharedPointer<Tag> classObj);

public:
    QVector<QSharedPointer<Tag>> m_vecTags;
    // key-device name, value-tags
    QMap<QString, QVector<QSharedPointer<Tag>> > m_mapDevBlockReadTags;
    QMap<QString, QSharedPointer<Tag> > m_classMap;
};
//Q_DECLARE_METATYPE(TagManager)

#endif // TAG_H

#include "BmsTag.h"
#include <QJsonArray>

BmsTag::BmsTag() : Tag()
{
    m_tagType = "BmsTag";
}

BmsTag::~BmsTag()
{
}

BmsTag::BmsTag(const BmsTag &obj)
{
    copyObject(obj);
}

BmsTag &BmsTag::operator=(const BmsTag &obj)
{
    copyObject(obj);
    return *this;
}

void BmsTag::copyObject(const BmsTag &obj)
{

    m_name          = obj.m_name;
    m_dataSource    = obj.m_dataSource;
    m_isCollect     = obj.m_isCollect;
    m_unit          = obj.m_unit;
    m_addrOffset    = obj.m_addrOffset;
    m_functionCodes = obj.m_functionCodes;
    m_rate          = obj.m_rate;
    m_dataType      = obj.m_dataType;
    m_isUpload      = obj.m_isUpload;
    m_formula       = obj.m_formula;

    m_remark   = obj.m_remark;
    m_ownGroup = obj.m_ownGroup;
    m_devType  = obj.m_devType;
}

bool BmsTag::openFromXml(XMLObject *pXmlObj)
{
    XMLObject *pTagObj = pXmlObj;
    if (pXmlObj == NULL) {
        return false;
    }
    m_id          = pTagObj->getProperty("id").toInt();
    m_blockReadId = pTagObj->getProperty("blockReadId").toInt();
    m_name        = pTagObj->getProperty("name");

    m_remark   = pTagObj->getProperty("remark");
    m_ownGroup = pTagObj->getProperty("group");
    m_devType  = pTagObj->getProperty("dev");


    m_dataSource = pTagObj->getProperty("dataSource").toInt();
    m_isCollect = pTagObj->getProperty("isCollect").toInt() == 0 ? true : false;
    m_unit = pTagObj->getProperty("unit");
    m_addrOffset = pTagObj->getProperty("addrOffset");
    m_functionCodes = pTagObj->getProperty("functionCodes");
    m_rate = pTagObj->getProperty("rate");
    m_dataType = pTagObj->getProperty("dataType");
    m_isUpload = pTagObj->getProperty("isUpload").toInt() == 0 ? true : false;
    m_formula = pTagObj->getProperty("formula");



    return true;
}

bool BmsTag::saveToXml(XMLObject *pXmlObj)
{
    XMLObject *pTagObj = new XMLObject(pXmlObj);
    return saveToXmlInner(pTagObj);
}

bool BmsTag::saveToXmlInner(XMLObject *pXmlObj)
{
    pXmlObj->setTagName("tag");
    pXmlObj->setProperty("tagType", m_tagType);
    pXmlObj->setProperty("id", QString::number(m_id));
    pXmlObj->setProperty("blockReadId", QString::number(m_blockReadId));
    pXmlObj->setProperty("name", m_name);

    pXmlObj->setProperty("remark", m_remark);
    pXmlObj->setProperty("group", m_ownGroup);
    pXmlObj->setProperty("dev", m_devType);

    pXmlObj->setProperty("dataSource", QString::number( m_dataSource));
    pXmlObj->setProperty("isCollect", QString::number(m_isCollect ? 0 : 1));
    pXmlObj->setProperty("unit", m_unit);
    pXmlObj->setProperty("addrOffset", m_addrOffset);
    pXmlObj->setProperty("functionCodes", m_functionCodes);
    pXmlObj->setProperty("rate", m_rate);
    pXmlObj->setProperty("dataType", m_dataType);
    pXmlObj->setProperty("isUpload", QString::number(m_isUpload ? 0 : 1));
    pXmlObj->setProperty("formula", m_formula);




    return true;
}

QString BmsTag::toXmlNodeString()
{
    XMLObject tagXml;
    saveToXmlInner(&tagXml);
    return tagXml.write();
}

bool BmsTag::fromXmlNodeString(const QString &szNode)
{
    XMLObject tagXml;
    if (!tagXml.load(szNode, NULL)) {
        return false;
    }
    return openFromXml(&tagXml);
}

QJsonObject BmsTag::toJsonObject()
{
    QJsonObject jsonTagObj;
    jsonTagObj.insert("id", QJsonValue(m_id));
    jsonTagObj.insert("blockReadId", QJsonValue(m_blockReadId));
    jsonTagObj.insert("name", QJsonValue(m_name));

    jsonTagObj.insert("remark", QJsonValue(m_remark));
    jsonTagObj.insert("group", QJsonValue(m_ownGroup));
    jsonTagObj.insert("dev", QJsonValue(m_devType));

    jsonTagObj.insert("dataSource", QJsonValue(QString::number( m_dataSource)));
    jsonTagObj.insert("isCollect", QJsonValue(QString::number(m_isCollect ? 0 : 1)));
    jsonTagObj.insert("unit", QJsonValue(m_unit));
    jsonTagObj.insert("addrOffset", QJsonValue(m_addrOffset));
    jsonTagObj.insert("functionCodes", QJsonValue(m_functionCodes));
    jsonTagObj.insert("rate", QJsonValue(m_rate));
    jsonTagObj.insert("dataType", QJsonValue(m_dataType));
    jsonTagObj.insert("isUpload", QJsonValue( QString::number(m_isUpload ? 0 : 1)));
    jsonTagObj.insert("formula", QJsonValue(m_formula));


    return jsonTagObj;
}

void BmsTag::fromJsonObject(QJsonObject jsonObj)
{
    if (!jsonObj.isEmpty()) {
        m_id          = jsonObj["id"].toInt();
        m_blockReadId = jsonObj["blockReadId"].toInt();
        m_name        = jsonObj["name"].toString();
        m_remark      = jsonObj["remark"].toString();
        m_ownGroup    = jsonObj["group"].toString();
        m_devType     = jsonObj["dev"].toString();

        m_dataSource     = jsonObj["dataSource"].toString().toInt();
        m_isCollect     = (jsonObj["isCollect"].toString().toUInt() == 0) ? true : false;
        m_unit     = jsonObj["unit"].toString();
        m_addrOffset     = jsonObj["addrOffset"].toString();
        m_functionCodes     = jsonObj["functionCodes"].toString();
        m_rate     = jsonObj["rate"].toString();
        m_dataType     = jsonObj["dataType"].toString();

        m_isUpload     = (jsonObj["isUpload"].toString().toUInt() == 0) ? true : false;
        m_formula     = jsonObj["formula"].toString();

    }
}

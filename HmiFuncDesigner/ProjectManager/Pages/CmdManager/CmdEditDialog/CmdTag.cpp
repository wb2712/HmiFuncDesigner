#include "CmdTag.h"



CmdTag::CmdTag()
{
    m_tagType = "CmdTag";
}

CmdTag::~CmdTag()
{

}


CmdTag::CmdTag(const CmdTag &obj)
{
    copyObject(obj);
}


CmdTag &CmdTag::operator=(const CmdTag &obj)
{
    copyObject(obj);
    return *this;
}

void CmdTag::copyObject(const CmdTag &obj)
{
    m_name = obj.m_name;
    m_dataType = obj.m_dataType;
    m_addrOffset = obj.m_addrOffset;

    formula = obj.formula;
    m_remark = obj.m_remark;
    m_ownGroup = obj.m_ownGroup;
    m_devType = obj.m_devType;
    m_addrOffsetBit = obj.m_addrOffsetBit;
}



bool CmdTag::openFromXml(XMLObject *pXmlObj)
{
    XMLObject *pTagObj = pXmlObj;
    if(pXmlObj == NULL) {
        return false;
    }
    m_id = pTagObj->getProperty("id").toInt();
    m_blockReadId = pTagObj->getProperty("blockReadId").toInt();
    m_name = pTagObj->getProperty("name");
    m_dataType = pTagObj->getProperty("type");
    m_addrOffset = pTagObj->getProperty("offset");
    formula = pTagObj->getProperty("formula");
    m_addrOffsetBit = pTagObj->getProperty("offsetBit").toInt();
    m_remark = pTagObj->getProperty("remark");
    m_ownGroup = pTagObj->getProperty("group");
    m_devType = pTagObj->getProperty("dev");
    return true;
}


bool CmdTag::saveToXml(XMLObject *pXmlObj)
{
    XMLObject *pTagObj = new XMLObject(pXmlObj);
    return saveToXmlInner(pTagObj);
}

bool CmdTag::saveToXmlInner(XMLObject *pXmlObj)
{
    pXmlObj->setTagName("tag");
    pXmlObj->setProperty("tagType", m_tagType);
    pXmlObj->setProperty("id", QString::number(m_id));
    pXmlObj->setProperty("blockReadId", QString::number(m_blockReadId));
    pXmlObj->setProperty("name", m_name);
    pXmlObj->setProperty("type", m_dataType);
    pXmlObj->setProperty("offset", m_addrOffset);
    pXmlObj->setProperty("offsetBit", QString::number(m_addrOffsetBit));
    pXmlObj->setProperty("formula", formula);
    pXmlObj->setProperty("remark", m_remark);
    pXmlObj->setProperty("group", m_ownGroup);
    pXmlObj->setProperty("dev", m_devType);
    return true;
}

QString CmdTag::toXmlNodeString()
{
    XMLObject tagXml;
    saveToXmlInner(&tagXml);
    return tagXml.write();
}

bool CmdTag::fromXmlNodeString(const QString &szNode)
{
    XMLObject tagXml;
    if(!tagXml.load(szNode, NULL)) {
        return false;
    }
    return openFromXml(&tagXml);
}

QJsonObject CmdTag::toJsonObject()
{
    QJsonObject jsonTagObj;
    jsonTagObj.insert("id", QJsonValue(m_id));
    jsonTagObj.insert("blockReadId", QJsonValue(m_blockReadId));
    jsonTagObj.insert("name", QJsonValue(m_name));
    jsonTagObj.insert("type", QJsonValue(m_dataType));
    jsonTagObj.insert("offset", QJsonValue(m_addrOffset));
    jsonTagObj.insert("offsetBit", QJsonValue(m_addrOffsetBit));
    jsonTagObj.insert("formula", QJsonValue(formula));
    jsonTagObj.insert("remark", QJsonValue(m_remark));
    jsonTagObj.insert("group", QJsonValue(m_ownGroup));
    jsonTagObj.insert("dev", QJsonValue(m_devType));
    return jsonTagObj;
}

void CmdTag::fromJsonObject(QJsonObject jsonObj)
{
    if(!jsonObj.isEmpty()) {
        m_id = jsonObj["id"].toInt();
        m_blockReadId = jsonObj["blockReadId"].toInt();
        m_name = jsonObj["name"].toString();
        m_dataType = jsonObj["type"].toString();
        m_addrOffset = jsonObj["offset"].toString();
        m_addrOffsetBit = jsonObj["offsetBit"].toInt();
        formula = jsonObj["formula"].toString();
        m_remark = jsonObj["remark"].toString();
        m_ownGroup = jsonObj["group"].toString();
        m_devType = jsonObj["dev"].toString();
    }
}

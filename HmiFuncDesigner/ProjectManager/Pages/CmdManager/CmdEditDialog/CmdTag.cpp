#include "CmdTag.h"
#include <QJsonArray>

CmdTag::CmdTag():Tag()
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
    m_name       = obj.m_name;
    m_args       = obj.m_args;

    m_remark   = obj.m_remark;
    m_ownGroup = obj.m_ownGroup;
    m_devType  = obj.m_devType;
}

bool CmdTag::openFromXml(XMLObject *pXmlObj)
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

    m_cmdType = pTagObj->getProperty("cmdType");

    // 清空 m_args 以准备新的数据
    m_args.clear();

    // 获取所有 "cmdArg" 子节点
    QVector<XMLObject *> cmdArgNodes = pXmlObj->getCurrentChildren("cmdArg");

    // 解析每个 "cmdArg" 子节点的属性，并将其存储到 m_args
    for (XMLObject *argNode : cmdArgNodes) {
        QVector<QString> argGroup;

        // 获取并存储该子节点的各个属性值
        QString argAddr  = argNode->getProperty("argAddr");
        QString argType  = argNode->getProperty("argType");
        QString argValue = argNode->getProperty("argValue");

        // 将每个参数添加到 argGroup
        argGroup.append(argAddr);
        argGroup.append(argType);
        argGroup.append(argValue);

        // 将该组参数添加到 m_args
        m_args.append(argGroup);
    }

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

    pXmlObj->setProperty("remark", m_remark);
    pXmlObj->setProperty("group", m_ownGroup);
    pXmlObj->setProperty("dev", m_devType);
    pXmlObj->setProperty("cmdType", m_cmdType);


    for (const QVector<QString> &argGroup : m_args) {
        if (argGroup.size() >= 3) {
            // 创建一个新的 XML 子节点
            XMLObject *argXmlObj = new XMLObject(pXmlObj);

            // 设置子节点的标签名称和属性
            argXmlObj->setTagName("cmdArg");
            argXmlObj->setProperty("argAddr", argGroup[0]);
            argXmlObj->setProperty("argType", argGroup[1]);
            argXmlObj->setProperty("argValue", argGroup[2]);

            // 将该子节点插入到父 XML 节点
            pXmlObj->inser_child(-1, argXmlObj);
        }
    }

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
    if (!tagXml.load(szNode, NULL)) {
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

    jsonTagObj.insert("remark", QJsonValue(m_remark));
    jsonTagObj.insert("group", QJsonValue(m_ownGroup));
    jsonTagObj.insert("dev", QJsonValue(m_devType));

    jsonTagObj.insert("cmdType", QJsonValue(m_cmdType));


    // 创建一个 QJsonArray 用于保存 m_args
    QJsonArray cmdArgArray;

    // 遍历 m_args，将每个 QVector<QString> 转换为 QJsonObject 并加入 cmdArgArray
    for (const QVector<QString> &argGroup : m_args) {
        QJsonObject argObj;

        // 假设 argGroup 中有三个元素：argAddr, argType, argValue
        if (argGroup.size() >= 3) {
            argObj["argAddr"]  = argGroup[0];
            argObj["argType"]  = argGroup[1];
            argObj["argValue"] = argGroup[2];
        }

        // 将该组加入 cmdArgArray
        cmdArgArray.append(argObj);
    }

    // 将 cmdArgArray 插入到 jsonTagObj 中
    jsonTagObj.insert("cmdArg", cmdArgArray);

    return jsonTagObj;
}

void CmdTag::fromJsonObject(QJsonObject jsonObj)
{
    if (!jsonObj.isEmpty()) {
        m_id          = jsonObj["id"].toInt();
        m_blockReadId = jsonObj["blockReadId"].toInt();
        m_name        = jsonObj["name"].toString();
        m_remark      = jsonObj["remark"].toString();
        m_ownGroup    = jsonObj["group"].toString();
        m_devType     = jsonObj["dev"].toString();

        m_cmdType     = jsonObj["cmdType"].toString();

        // 获取 cmdArg 数组
        QJsonArray cmdArgArray = jsonObj["cmdArg"].toArray();

        // 解析每个 QJsonObject 到 QVector<QString>
        for (int i = 0; i < cmdArgArray.size(); ++i) {
            QJsonObject obj = cmdArgArray[i].toObject();
            QVector<QString> argGroup;

            // 将每个字段转换为 QString 并加入 QVector
            argGroup.append(obj["argAddr"].toString());
            argGroup.append(obj["argType"].toString());
            argGroup.append(obj["argValue"].toString());

            // 将该组加入到 m_args 中
            m_args.append(argGroup);
        }
    }
}

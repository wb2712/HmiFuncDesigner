#include "DevModleInfo.h"
#include "ulog.h"

int DevModleInfo::m_startNewDeviceID = 0;

DevModleInfo::DevModleInfo()
{
    m_listDevModleInfoObject.clear();
}

DevModleInfo::~DevModleInfo()
{
    qDeleteAll(m_listDevModleInfoObject);
    m_listDevModleInfoObject.clear();
}

bool DevModleInfo::openFromXml(XMLObject *pXmlObj)
{
    qDeleteAll(m_listDevModleInfoObject);
    m_listDevModleInfoObject.clear();
    XMLObject *pDevicesObj = pXmlObj->getCurrentChild("DevModles");
    if (pDevicesObj == NULL) {
        return false;
    }
    QVector<XMLObject *> listUsersObj = pDevicesObj->getCurrentChildren("DevModle");
    foreach (XMLObject *pDevObj, listUsersObj) {
        DevModleInfoObject *pObj = new DevModleInfoObject();
        pObj->m_id               = pDevObj->getProperty("id").toInt();
        if (m_startNewDeviceID < pObj->m_id) {
            m_startNewDeviceID = pObj->m_id;
        }
        pObj->m_deviceType          = pDevObj->getProperty("type");
        pObj->m_name                = pDevObj->getProperty("name");
        pObj->m_deviceName          = pDevObj->getProperty("dev_name");
        pObj->m_frameLen            = pDevObj->getProperty("frame_len").toInt();
        pObj->m_protocol            = pDevObj->getProperty("protocol");
        pObj->m_link                = pDevObj->getProperty("link");
        pObj->m_stateVar            = pDevObj->getProperty("state").toInt();
        pObj->m_frameTimePeriod     = pDevObj->getProperty("frame_period").toInt();
        pObj->m_ctrlVar             = pDevObj->getProperty("ctrl").toInt();
        pObj->m_dynamicOptimization = pDevObj->getProperty("dyn") == "1";
        pObj->m_remotePort          = pDevObj->getProperty("remote").toInt();
        pObj->m_portParameters      = pDevObj->getProperty("param");
        pObj->m_properties          = pDevObj->getProperty("prop");

        pObj->dev_Name        = pDevObj->getProperty("dev_Name");
        pObj->Category        = pDevObj->getProperty("Category").toInt();
        pObj->ArchType        = pDevObj->getProperty("ArchType").toInt();
        pObj->BusType         = pDevObj->getProperty("BusType").toInt();
        pObj->ProtoType       = pDevObj->getProperty("ProtoType").toInt();
        pObj->isCollect       = pDevObj->getProperty("isCollect").toInt() != 0;
        pObj->ClassID         = pDevObj->getProperty("ClassID");
        pObj->dev_manufactory = pDevObj->getProperty("dev_manufactory");
        pObj->dev_Type        = pDevObj->getProperty("dev_Type");

        pObj->isUpload   = pDevObj->getProperty("isUpload").toInt() != 0;
        pObj->ArchType_2 = pDevObj->getProperty("ArchType_2").toInt();
        pObj->BusType_2  = pDevObj->getProperty("BusType_2").toInt();
        pObj->ClassID_2  = pDevObj->getProperty("ClassID_2");

        pObj->commDev  = pDevObj->getProperty("commDev");
        pObj->devModel = pDevObj->getProperty("devModel");

        pObj->commDev_2  = pDevObj->getProperty("commDev_2");
        pObj->devModel_2 = pDevObj->getProperty("devModel_2");

        QVector<XMLObject *> argNodes = pDevObj->getCurrentChildren("customParameters");

        // 解析每个 "cmdArg" 子节点的属性，并将其存储到 m_args
        for (XMLObject *argNode : argNodes) {
            QVector<QString> argGroup;

            // 获取并存储该子节点的各个属性值
            QString argAddr  = argNode->getProperty("argName");
            QString argType  = argNode->getProperty("argType");
            QString argValue = argNode->getProperty("argValue");

            // 将每个参数添加到 argGroup
            argGroup.append(argAddr);
            argGroup.append(argValue);
            argGroup.append(argType);

            pObj->customParameters.append(argGroup);
        }

        pObj->num         = pDevObj->getProperty("num").toInt();
        pObj->devices     = pDevObj->getProperty("devices");
        pObj->PowerCtrl   = pDevObj->getProperty("PowerCtrl");
        pObj->MonitorCtrl = pDevObj->getProperty("MonitorCtrl");
        pObj->PCS         = pDevObj->getProperty("PCS");
        pObj->BAMS        = pDevObj->getProperty("BAMS");
        pObj->Pump        = pDevObj->getProperty("Pump");
        pObj->PumpCtrl    = pDevObj->getProperty("PumpCtrl");

        m_listDevModleInfoObject.append(pObj);
    }
    return true;
}

bool DevModleInfo::saveToXml(XMLObject *pXmlObj)
{
    XMLObject *pDevicesObj = new XMLObject(pXmlObj);
    pDevicesObj->setTagName("DevModles");

    for (int i = 0; i < m_listDevModleInfoObject.count(); i++) {
        DevModleInfoObject *pObj = m_listDevModleInfoObject.at(i);
        XMLObject *pDevObj       = new XMLObject(pDevicesObj);
        pDevObj->setTagName("DevModle");
        pDevObj->setProperty("id", QString::number(pObj->m_id));
        pDevObj->setProperty("type", pObj->m_deviceType);
        pDevObj->setProperty("name", pObj->m_name);
        pDevObj->setProperty("dev_name", pObj->m_deviceName);
        pDevObj->setProperty("frame_len", QString::number(pObj->m_frameLen));
        pDevObj->setProperty("protocol", pObj->m_protocol);
        pDevObj->setProperty("link", pObj->m_link);
        pDevObj->setProperty("state", QString::number(pObj->m_stateVar));
        pDevObj->setProperty("frame_period", QString::number(pObj->m_frameTimePeriod));
        pDevObj->setProperty("ctrl", QString::number(pObj->m_ctrlVar));
        pDevObj->setProperty("dyn", pObj->m_dynamicOptimization ? "1" : "0");
        pDevObj->setProperty("remote", QString::number(pObj->m_remotePort));
        pDevObj->setProperty("param", pObj->m_portParameters);
        pDevObj->setProperty("prop", pObj->m_properties);

        pDevObj->setProperty("dev_Name", pObj->dev_Name);
        pDevObj->setProperty("Category", QString::number(pObj->Category));
        pDevObj->setProperty("ArchType", QString::number(pObj->ArchType));
        pDevObj->setProperty("BusType", QString::number(pObj->BusType));
        pDevObj->setProperty("ProtoType", QString::number(pObj->ProtoType));
        pDevObj->setProperty("isCollect", QString::number(pObj->isCollect ? 1 : 0));
        pDevObj->setProperty("ClassID", pObj->ClassID);
        pDevObj->setProperty("dev_manufactory", pObj->dev_manufactory);
        pDevObj->setProperty("dev_Type", pObj->dev_Type);

        pDevObj->setProperty("isUpload", QString::number(pObj->isUpload ? 1 : 0));
        pDevObj->setProperty("ArchType_2", QString::number(pObj->ArchType_2));
        pDevObj->setProperty("BusType_2", QString::number(pObj->BusType_2));
        pDevObj->setProperty("ClassID_2", pObj->ClassID_2);

        pDevObj->setProperty("commDev", pObj->commDev);
        pDevObj->setProperty("devModel", pObj->devModel);

        pDevObj->setProperty("commDev_2", pObj->commDev_2);
        pDevObj->setProperty("devModel_2", pObj->devModel_2);

        for (const QVector<QString> &argGroup : pObj->customParameters) {
            if (argGroup.size() >= 3) {

                // 创建一个新的 XML 子节点
                XMLObject *argXmlObj = new XMLObject(pDevObj);

                // 设置子节点的标签名称和属性
                argXmlObj->setTagName("customParameters");
                argXmlObj->setProperty("argName", argGroup[0]);
                argXmlObj->setProperty("argValue", argGroup[1]);
                argXmlObj->setProperty("argType", argGroup[2]);

                // 将该子节点插入到父 XML 节点
                pDevObj->inser_child(-1, argXmlObj);
            }
        }

        pDevObj->setProperty("num", QString::number(pObj->num));
        pDevObj->setProperty("devices", pObj->devices);
        pDevObj->setProperty("PowerCtrl", pObj->PowerCtrl);
        pDevObj->setProperty("MonitorCtrl", pObj->MonitorCtrl);
        pDevObj->setProperty("PCS", pObj->PCS);
        pDevObj->setProperty("BAMS", pObj->BAMS);
        pDevObj->setProperty("Pump", pObj->Pump);
        pDevObj->setProperty("PumpCtrl", pObj->PumpCtrl);
    }

    return true;
}

DevModleInfoObject *DevModleInfo::newObject()
{
    DevModleInfoObject *pObj = new DevModleInfoObject();
    if (pObj != NULL) {
        pObj->m_id = allocNewDeviceID();
        m_listDevModleInfoObject.append(pObj);
    }
    return pObj;
}

DevModleInfoObject *DevModleInfo::getObjectByID(int id)
{
    for (int i = 0; i < m_listDevModleInfoObject.count(); i++) {
        DevModleInfoObject *pObj = m_listDevModleInfoObject.at(i);
        if (pObj->m_id == id) {
            return pObj;
        }
    }
    return NULL;
}

DevModleInfoObject *DevModleInfo::getObjectByName(const QString &name)
{
    for (int i = 0; i < m_listDevModleInfoObject.count(); i++) {
        DevModleInfoObject *pObj = m_listDevModleInfoObject.at(i);
        if (pObj->m_name == name) {
            return pObj;
        }
    }
    return NULL;
}

/**
 * @brief DevModleInfo::allocNewDeviceID
 * @details 分配一个设备ID
 * @return 设备ID
 */
int DevModleInfo::allocNewDeviceID()
{
    ++m_startNewDeviceID;
    return m_startNewDeviceID;
}

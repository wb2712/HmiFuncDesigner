#ifndef DEVMODLEINFO_H
#define DEVMODLEINFO_H

#include <QString>
#include <QStringList>
#include <QList>
#include "../xmlobject.h"
#include "../sharedlibglobal.h"

class SHAREDLIB_EXPORT DevModleInfoObject
{
public:
    explicit DevModleInfoObject()
    {

    }

    DevModleInfoObject(const DevModleInfoObject &obj)
    {
        copyObject(obj);
    }

    ~DevModleInfoObject()
    {
    }

    DevModleInfoObject &operator=(const DevModleInfoObject &obj)
    {
        copyObject(obj);
        return *this;
    }

    void copyObject(const DevModleInfoObject &obj)
    {
        m_id = obj.m_id;
        m_deviceType = obj.m_deviceType;
        m_name = obj.m_name;
        m_deviceName = obj.m_deviceName;
        m_frameLen = obj.m_frameLen;
        m_protocol = obj.m_protocol;
        m_link = obj.m_link;
        m_stateVar = obj.m_stateVar;
        m_frameTimePeriod = obj.m_frameTimePeriod;
        m_ctrlVar = obj.m_ctrlVar;
        m_dynamicOptimization = obj.m_dynamicOptimization;
        m_remotePort = obj.m_remotePort;
        m_portParameters = obj.m_portParameters;
        m_properties = obj.m_properties;

        
        dev_Name = obj.dev_Name;
        Category = obj.Category;
        ArchType = obj.ArchType;
        BusType = obj.BusType;
        ProtoType = obj.ProtoType;
        ClassID = obj.ClassID;
        dev_manufactory = obj.dev_manufactory;
        dev_Type = obj.dev_Type;

        ArchType_2 = obj.ArchType_2;
        BusType_2 = obj.BusType_2;
        ClassID_2 = obj.ClassID_2;


        num = obj.num;
        devices = obj.devices;
        PowerCtrl = obj.PowerCtrl;
        MonitorCtrl = obj.MonitorCtrl;
        PCS = obj.PCS;
        BAMS = obj.BAMS;
        Pump = obj.Pump;
        PumpCtrl = obj.PumpCtrl;
    }

public:
    int m_id;
    QString m_deviceType; //COM, NET, BUS, OPC
    QString m_name; // 显示名称
    QString m_deviceName; // 设备插件名称
    int m_frameLen;
    QString m_protocol;
    QString m_link;
    int m_stateVar;
    int m_frameTimePeriod;
    int m_ctrlVar;
    bool m_dynamicOptimization;
    int m_remotePort;
    QString m_portParameters;
    QString m_properties; // 设备私有属性

    QString dev_Name;
    int Category;
    int ArchType;
    int BusType;
    int ProtoType;
    QString ClassID;
    QString dev_manufactory;
    QString dev_Type;
    int ArchType_2;
    int BusType_2;
    QString ClassID_2;

    int num;
    QString devices;
    QString PowerCtrl;
    QString MonitorCtrl;
    QString PCS;
    QString BAMS;
    QString Pump;
    QString PumpCtrl;

};

/*
class SHAREDLIB_EXPORT ComDevice : public DevModleInfoObject
{
public:
    explicit ComDevice() : DevModleInfoObject()
    {

    }

    ComDevice(const ComDevice &obj) : DevModleInfoObject(obj)
    {
        copyObject(obj);
    }

    ~ComDevice()
    {

    }

    ComDevice &operator=(const ComDevice &obj)
    {
        copyObject(obj);
        return *this;
    }

    void copyObject(const ComDevice &obj)
    {
        DevModleInfoObject::copyObject(obj);
        m_portNumber = obj.m_portNumber;
        m_baudrate = obj.m_baudrate;
        m_databit = obj.m_databit;
        m_stopbit = obj.m_stopbit;
        m_verifybit = obj.m_verifybit;
        m_timeout = obj.m_timeout;
    }

    void fromString(const QString &param)
    {
        QStringList listParam = param.split('|');
        if(listParam.count() == 6) {
            m_portNumber = listParam.at(0);
            m_baudrate = listParam.at(1).toInt();
            m_databit = listParam.at(2).toInt();
            m_stopbit = listParam.at(3).toFloat();
            m_verifybit = listParam.at(4);
            m_timeout = listParam.at(5).toInt();
        }
    }

    QString toString()
    {
        QStringList param;
        param.append(m_portNumber);
        param.append(QString::number(m_baudrate));
        param.append(QString::number(m_databit));
        param.append(QString::number(m_stopbit));
        param.append(m_verifybit);
        param.append(QString::number(m_timeout));
        return param.join("|");
    }

public:
    QString m_portNumber;
    int m_baudrate;
    int m_databit;
    float m_stopbit;
    QString m_verifybit;
    int m_timeout;
};


class SHAREDLIB_EXPORT NetDevice : public DevModleInfoObject
{
public:
    explicit NetDevice() : DevModleInfoObject()
    {

    }

    NetDevice(const NetDevice &obj) : DevModleInfoObject(obj)
    {
        copyObject(obj);
    }

    ~NetDevice()
    {

    }

    NetDevice &operator=(const NetDevice &obj)
    {
        copyObject(obj);
        return *this;
    }

    void copyObject(const NetDevice &obj)
    {
        DevModleInfoObject::copyObject(obj);
        m_ipAddress = obj.m_ipAddress;
        m_port = obj.m_port;
        m_ipAddress1 = obj.m_ipAddress1;
        m_port1 = obj.m_port1;
    }

    void fromString(const QString &param)
    {
        QStringList listParam = param.split('|');
        if(listParam.count() == 4) {
            m_ipAddress = listParam.at(0);
            m_port = listParam.at(1).toInt();
            m_ipAddress1 = listParam.at(2);
            m_port1 = listParam.at(3).toInt();
        }
    }

    QString toString()
    {
        QStringList param;
        param.append(m_ipAddress);
        param.append(QString::number(m_port));
        param.append(m_ipAddress1);
        param.append(QString::number(m_port1));
        return param.join("|");
    }

public:
    QString m_ipAddress;
    int m_port;
    QString m_ipAddress1;
    int m_port1;
};

*/
class SHAREDLIB_EXPORT DevModleInfo
{
public:
    explicit DevModleInfo();
    ~DevModleInfo();

    bool openFromXml(XMLObject *pXmlObj);
    bool saveToXml(XMLObject *pXmlObj);

    DevModleInfoObject *newObject();
    DevModleInfoObject *getObjectByID(int id);
    DevModleInfoObject *getObjectByName(const QString &name);

    // 分配一个设备ID
    static int allocNewDeviceID();

public:
    QList<DevModleInfoObject *> m_listDevModleInfoObject;

private:
    static int m_startNewDeviceID;
};

#endif // DEVMODLEINFO_H

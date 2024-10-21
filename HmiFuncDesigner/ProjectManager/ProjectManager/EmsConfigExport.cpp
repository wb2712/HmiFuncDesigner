#include "EmsConfigExport.h"
#include "qsoftcore.h"
#include "./projdata/Tag.h"
#include "./projdata/DevModleInfo.h"
#include "qprojectcore.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

EmsConfigExport::EmsConfigExport()
{
}

void EmsConfigExport::Export()
{
    // 弹出提示框，告诉用户正在进行导出操作
    QMessageBox::information(nullptr, "Export", "Configuration export in progress...", QMessageBox::Ok);

    // 获取设备信息
    DevModleInfo &devModleInfo              = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    QList<DevModleInfoObject *> &dev_temp = devModleInfo.m_listDevModleInfoObject;

    DeviceInfo &deviceInfo              = QSoftCore::getCore()->getProjectCore()->m_deviceInfo;
    QList<DeviceInfoObject *> &comm_dev_temp = deviceInfo.m_listDeviceInfoObject;


    // 输出字符串
    QString output;

    // 1. 处理 Station 对象
    int stationCount = 0;
    output += "[STATIONS]\n";

    // Station 数量统计
    for (auto pObj : dev_temp) {
        if (pObj->m_deviceType == "Station") {
            stationCount++;
        }
    }

    output += QString("num=%1\n\n").arg(stationCount);

    // 导出 Station 信息
    for (auto pObj : dev_temp) {
        if (pObj->m_deviceType == "Station") {
            output += QString("[STATION%1]\n").arg(pObj->num);
            output += QString("devices=%1\n").arg(pObj->devices);
            output += QString("PowerCtrl=%1\n").arg(pObj->PowerCtrl);
            output += QString("MonitorCtrl=%1\n").arg(pObj->MonitorCtrl);
            output += QString("PCS=%1\n").arg(pObj->PCS);
            output += QString("BAMS=%1\n").arg(pObj->BAMS);
            output += QString("Pump=%1\n").arg(pObj->Pump);
            output += QString("PumpCtrl=%1\n").arg(pObj->PumpCtrl);
            output += "\n";
        }
    }

    // 2. 处理 DevModle 对象
    int deviceCount = 0;
    output += "[DEV]\n";

    // DevModle 数量统计
    for (auto pObj : dev_temp) {
        if (pObj->m_deviceType == "DevModle") {
            deviceCount++;
        }
    }

    output += QString("num=%1\n\n").arg(deviceCount);

    // 导出 DevModle 信息
    int deviceIndex = 1;
    for (auto pObj : dev_temp) {
        if (pObj->m_deviceType == "DevModle") {
            // 第一个设备
            if(pObj->isCollect){
                output += QString("[DEVICE%1]\n").arg(deviceIndex++);
                output += QString("ClassID=%1\n").arg(pObj->ClassID);
                output += QString("Category=%1\n").arg(pObj->Category);
                output += QString("ArchType=%1\n").arg(pObj->ArchType);
                output += QString("BusType=%1\n").arg(pObj->BusType);
                output += QString("ProtoType=%1\n").arg(pObj->ProtoType);
                output += QString("dev_Name=%1\n").arg(pObj->dev_Name);
                output += QString("dev_manufactory=%1\n").arg(pObj->dev_manufactory);
                output += QString("dev_Type=%1\n").arg(pObj->dev_Type);

                if(!pObj->commDev.isEmpty())
                {
                    NetDevice netDev;
                    bool finded = false;
                    for(auto it : comm_dev_temp)
                    {
                        if(it->m_name == pObj->commDev)
                        {
                            netDev.fromString(it->m_portParameters);
                            finded = true;
                            break;
                        }
                    }

                    if(finded)
                    {
                        output += QString("dev_procAddr=%1\n").arg(netDev.m_ipAddress);
                        output += QString("dev_procPort=%1\n").arg(netDev.m_port);
                    }
                }else if(!pObj->devModel.isEmpty())
                {
                    output += QString("dev_procAddr=%1\n").arg(pObj->devModel);
                }


                for(auto it: pObj->customParameters)
                {
                    if(it.at(2).toInt() == 0)
                    {
                        output += QString("%1=%2\n").arg(it.at(0)).arg(it.at(1));
                    }
                }


                output += "\n";
            }

            // 第二个设备
            if(pObj->isUpload){
                output += QString("[DEVICE%1]\n").arg(deviceIndex++);
                output += QString("ClassID=%1\n").arg(pObj->ClassID_2);   // 第二个设备的 ClassID
                output += QString("Category=%1\n").arg(pObj->Category);   // Category 等其他属性与第一个设备相同
                output += QString("ArchType=%1\n").arg(pObj->ArchType_2); // 第二个设备的 ArchType
                output += QString("BusType=%1\n").arg(pObj->BusType_2);   // 第二个设备的 BusType
                output += QString("ProtoType=%1\n").arg(pObj->ProtoType);
                output += QString("dev_Name=%1\n").arg(pObj->dev_Name); // 名称等属性相同
                output += QString("dev_manufactory=%1\n").arg(pObj->dev_manufactory);
                output += QString("dev_Type=%1\n").arg(pObj->dev_Type);

                if(!pObj->commDev_2.isEmpty())
                {
                    NetDevice netDev;
                    bool finded = false;
                    for(auto it : comm_dev_temp)
                    {
                        if(it->m_name == pObj->commDev_2)
                        {
                            netDev.fromString(it->m_portParameters);
                            finded = true;
                            break;
                        }
                    }

                    if(finded)
                    {
                        output += QString("dev_procAddr=%1\n").arg(netDev.m_ipAddress);
                        output += QString("dev_procPort=%1\n").arg(netDev.m_port);
                    }
                }else if(!pObj->devModel_2.isEmpty())
                {
                    output += QString("dev_procAddr=%1\n").arg(pObj->devModel_2);
                }


                for(auto it: pObj->customParameters)
                {
                    if(it.at(2).toInt() == 0)
                    {
                        output += QString("%1=%2\n").arg(it.at(0)).arg(it.at(1));
                    }
                }

                output += "\n";
            }
        }
    }

    // 3. 保存到文件
    QString fileName = "KgDevices.ini"; // 默认文件名

    // 这里你可以选择文件保存路径
    fileName = QFileDialog::getSaveFileName(nullptr, "Save Config File", fileName, "Text Files (*.ini)");
    if (fileName.isEmpty()) {
        QMessageBox::warning(nullptr, "Export", "Export operation cancelled or failed.", QMessageBox::Ok);
        return;
    }

    // 写入文件
    bool success = false;
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << output;
        file.close();
        success = true;
    }

    // 4. 弹出导出结果提示框
    if (success) {
        QString message = QString("Export successful!\nFile saved at: %1").arg(fileName);
        QMessageBox::information(nullptr, "Export Success", message, QMessageBox::Ok);
    } else {
        QMessageBox::critical(nullptr, "Export Failed", "Failed to export configuration file.", QMessageBox::Ok);
    }

    // 输出到控制台用于调试
    qDebug().noquote() << output;
}

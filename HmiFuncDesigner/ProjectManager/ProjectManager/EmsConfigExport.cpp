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
#include "../Pages/CmdManager/CmdEditDialog/CmdTag.h"

EmsConfigExport &EmsConfigExport::GetInstance()
{
    static EmsConfigExport instance; // 局部静态变量，线程安全
    return instance;
}

EmsConfigExport::EmsConfigExport()
{
}

EmsConfigExport::~EmsConfigExport()
{
}

void EmsConfigExport::Export()
{
    // 弹出提示框，告诉用户正在进行导出操作
    QMessageBox::information(nullptr, "Export", "Configuration export in progress...", QMessageBox::Ok);

    m_dirPath = QFileDialog::getExistingDirectory(nullptr, "Select Save Directory");
    if (m_dirPath.isEmpty()) {
        QMessageBox::warning(nullptr, "Export", "Export operation cancelled or failed.", QMessageBox::Ok);
        return;
    }

    ExportStationCfg();
    ExportDevModleCfg();
    ExportRedisCfg();

    QString message = QString("Export successful!\nFile saved at: %1").arg(m_dirPath);
    QMessageBox::information(nullptr, "Export Success", message, QMessageBox::Ok);
}

void EmsConfigExport::ExportStationCfg()
{
    // 获取设备信息
    DevModleInfo &devModleInfo            = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    QList<DevModleInfoObject *> &dev_temp = devModleInfo.m_listDevModleInfoObject;

    DeviceInfo &deviceInfo                   = QSoftCore::getCore()->getProjectCore()->m_deviceInfo;
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
            if (pObj->isCollect) {
                output += QString("[DEVICE%1]\n").arg(deviceIndex++);
                output += QString("ClassID=%1\n").arg(pObj->ClassID);
                output += QString("Category=%1\n").arg(pObj->Category);
                output += QString("ArchType=%1\n").arg(pObj->ArchType);
                output += QString("BusType=%1\n").arg(pObj->BusType);
                output += QString("ProtoType=%1\n").arg(pObj->ProtoType);
                output += QString("dev_Name=%1\n").arg(pObj->dev_Name);
                output += QString("dev_manufactory=%1\n").arg(pObj->dev_manufactory);
                output += QString("dev_Type=%1\n").arg(pObj->dev_Type);

                if (!pObj->commDev.isEmpty()) {
                    NetDevice netDev;
                    bool finded = false;
                    for (auto it : comm_dev_temp) {
                        if (it->m_name == pObj->commDev) {
                            netDev.fromString(it->m_portParameters);
                            finded = true;
                            break;
                        }
                    }

                    if (finded) {
                        output += QString("dev_procAddr=%1\n").arg(netDev.m_ipAddress);
                        output += QString("dev_procPort=%1\n").arg(netDev.m_port);
                    }
                } else if (!pObj->devModel.isEmpty()) {
                    output += QString("dev_procAddr=%1\n").arg(pObj->devModel);
                }

                for (auto it : pObj->customParameters) {
                    if (it.at(2).toInt() == 0) {
                        output += QString("%1=%2\n").arg(it.at(0)).arg(it.at(1));
                    }
                }

                output += "\n";
            }

            // 第二个设备
            if (pObj->isUpload) {
                output += QString("[DEVICE%1]\n").arg(deviceIndex++);
                output += QString("ClassID=%1\n").arg(pObj->ClassID_2);   // 第二个设备的 ClassID
                output += QString("Category=%1\n").arg(pObj->Category);   // Category 等其他属性与第一个设备相同
                output += QString("ArchType=%1\n").arg(pObj->ArchType_2); // 第二个设备的 ArchType
                output += QString("BusType=%1\n").arg(pObj->BusType_2);   // 第二个设备的 BusType
                output += QString("ProtoType=%1\n").arg(pObj->ProtoType);
                output += QString("dev_Name=%1\n").arg(pObj->dev_Name); // 名称等属性相同
                output += QString("dev_manufactory=%1\n").arg(pObj->dev_manufactory);
                output += QString("dev_Type=%1\n").arg(pObj->dev_Type);

                if (!pObj->commDev_2.isEmpty()) {
                    NetDevice netDev;
                    bool finded = false;
                    for (auto it : comm_dev_temp) {
                        if (it->m_name == pObj->commDev_2) {
                            netDev.fromString(it->m_portParameters);
                            finded = true;
                            break;
                        }
                    }

                    if (finded) {
                        output += QString("dev_procAddr=%1\n").arg(netDev.m_ipAddress);
                        output += QString("dev_procPort=%1\n").arg(netDev.m_port);
                    }
                } else if (!pObj->devModel_2.isEmpty()) {
                    output += QString("dev_procAddr=%1\n").arg(pObj->devModel_2);
                }

                for (auto it : pObj->customParameters) {
                    if (it.at(2).toInt() == 0) {
                        output += QString("%1=%2\n").arg(it.at(0)).arg(it.at(1));
                    }
                }

                output += "\n";
            }
        }
    }

    // 3. 保存到文件
    QString fileName = "KgDevices.ini"; // 默认文件名

    SaveFile(fileName, output);
}

void EmsConfigExport::ExportDevModleCfg()
{
    // 获取设备信息
    DevModleInfo &devModleInfo            = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    QList<DevModleInfoObject *> &dev_temp = devModleInfo.m_listDevModleInfoObject;

    TagManager *tag_mgr = QSoftCore::getCore()->getProjectCore()->m_tagMgr;

    QMap<QString, QVector<QSharedPointer<Tag>>> tag_map;

    // 将标签按设备名称分组
    for (const auto &it : tag_mgr->m_vecTags) {
        tag_map[it->m_devType].append(it);
    }

    // 遍历设备模型对象
    for (auto pObj : dev_temp) {
        if (pObj->m_deviceType == "DevModle" && pObj->isCollect) {

            // 输出字符串
            QString output;
            QString dev_out_put;
            QString cmd_out_put;

            // 配置文件的起始部分
            dev_out_put += "{\n  \"start\",\n";
            cmd_out_put += "{\n  \"start\",\n";

            // 根据设备名称获取关联的标签
            const QVector<QSharedPointer<Tag>> &tags = tag_map[pObj->dev_Name];

            for (auto it : tags) {
                if (it->m_tagType == "DeviceTag") {
                    // 将标签转换为 DeviceTag 类型
                    DeviceTag *dev_tag = dynamic_cast<DeviceTag *>(it.data());

                    // 如果转换成功，拼接输出字符串
                    if (dev_tag != nullptr) {
                        dev_out_put += QString("  \"%1_fcode:%2_type:%3_rate:%4_unit:%5_rOrw:%6\",\n")
                                           .arg(dev_tag->m_addrOffset)                                // 地址偏移
                                           .arg(dev_tag->m_functionCodes)                             // 功能码（直接作为字符串）
                                           .arg(dev_tag->m_dataType)                                  // 数据类型
                                           .arg(dev_tag->m_rate)                                      // 比率
                                           .arg(dev_tag->m_unit.isEmpty() ? "none" : dev_tag->m_unit) // 单位
                                           .arg(dev_tag->m_writeable == 0 ? "R" : "RW");              // 读/写权限
                    }
                } else if (it->m_tagType == "CmdTag") {

                    CmdTag *cmd_tag = dynamic_cast<CmdTag *>(it.data());

                    // 如果转换成功，拼接输出字符串
                    if (cmd_tag != nullptr) {
                        cmd_out_put += QString("  \"%1_%2.%3")
                                           .arg(cmd_tag->m_name)
                                           .arg(cmd_tag->m_cmdType)
                                           .arg(QString("%1_%2=%3").arg(cmd_tag->m_args[0][0]).arg(cmd_tag->m_args[0][1]).arg(cmd_tag->m_args[0][2]));

                        for (int i = 1; i < cmd_tag->m_args.count(); ++i) {
                            const auto &it = cmd_tag->m_args[i];
                            cmd_out_put += QString("#%1_%2=%3").arg(it[0]).arg(it[1]).arg(it[2]);
                        }

                        cmd_out_put += QString("\",\n");
                    }
                }
            }

            // 配置文件的结束部分
            dev_out_put += "  \"end\"\n}\n";
            cmd_out_put += "  \"end\"\n}\n";

            output += dev_out_put;
            output += cmd_out_put;

            // 打印输出字符串到控制台，用于调试
            qDebug() << output;

            // 自动生成文件名
            QString fileName = QString("%1_%2@T%3P%4A%5.mapcfg")
                                   .arg(pObj->dev_manufactory)
                                   .arg(pObj->dev_Type)
                                   .arg(pObj->Category)
                                   .arg(pObj->ProtoType)
                                   .arg(pObj->ArchType);

            // 将文件名和路径组合
            QString fullPath = m_dirPath + "/" + fileName;

            SaveFile(fileName, output);
        }
    }
}

void EmsConfigExport::ExportRedisCfg()
{
    // 获取设备信息
    DevModleInfo &devModleInfo            = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    QList<DevModleInfoObject *> &dev_temp = devModleInfo.m_listDevModleInfoObject;

    TagManager *tag_mgr = QSoftCore::getCore()->getProjectCore()->m_tagMgr;

    QMap<QString, QVector<QSharedPointer<Tag>>> tag_map;

    // 将标签按设备名称分组
    for (const auto &it : tag_mgr->m_vecTags) {
        tag_map[it->m_devType].append(it);
    }

    // 遍历设备模型对象
    for (auto pObj : dev_temp) {
        if (pObj->m_deviceType == "DevModle" && pObj->isUpload) {

            // 输出字符串
            QString output;
            QString dev_out_put;

            // 配置文件的起始部分
            dev_out_put += "{\n  \"start\",\n";

            // 根据设备名称获取关联的标签
            const QVector<QSharedPointer<Tag>> &tags = tag_map[pObj->dev_Name];

            for (auto it : tags) {
                if (it->m_tagType == "RedisTag") {

                    RedisTag *redis_tag = dynamic_cast<RedisTag *>(it.data());

                    // 如果转换成功，拼接输出字符串
                    if (redis_tag != nullptr) {

                        if (redis_tag->m_dataType != "SQ_Keys_or") {
                            dev_out_put += QString("  \"%1_%2_%3_%4\",\n")
                                               .arg(redis_tag->m_name)
                                               .arg(redis_tag->m_dataType)
                                               .arg(redis_tag->m_addrOffset)
                                               .arg(((redis_tag->m_dataType == "D") ? "null" : QString("bit%1").arg(redis_tag->m_addrOffsetBit)));
                        } else {
                            dev_out_put += QString("  \"%1_%2_%3\",\n").arg(redis_tag->m_name).arg(redis_tag->m_dataType).arg(redis_tag->formula);
                        }
                    }
                }
            }

            // 配置文件的结束部分
            dev_out_put += "  \"end\"\n}\n";

            output += dev_out_put;

            // 打印输出字符串到控制台，用于调试
            qDebug() << output;

            // 自动生成文件名
            QString fileName = QString("%1_%2@T%3P%4A%5.mapcfg")
                                   .arg(pObj->dev_manufactory)
                                   .arg(pObj->dev_Type)
                                   .arg(pObj->Category)
                                   .arg(pObj->ProtoType)
                                   .arg(pObj->ArchType_2);

            SaveFile(fileName, output);
        }
    }
}

void EmsConfigExport::SaveFile(QString fileName, QString output)
{
    // 将文件名和路径组合
    QString fullPath = m_dirPath + "/" + fileName;

    // 写入文件
    QFile file(fullPath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << output;
        file.close();
    } else {
        QString errorMessage = QString("Failed to save file at: %1").arg(fullPath);

        // 打印错误日志
        qWarning() << errorMessage;

        // 弹出错误提示框
        QMessageBox::critical(nullptr, "Export Failed", errorMessage, QMessageBox::Ok);
    }
}

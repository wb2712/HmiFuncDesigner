#include "StationDialog.h"
#include "ui_StationDialog.h"
#include "devicelistdialog.h"
#include "selectprotocoldialog.h"
#include "../../Devices/IDevicePlugin/IDevicePlugin.h"
#include "../shared/confighelper.h"
#include "qsoftcore.h"
#include "../shared/qprojectcore.h"
#include "../shared/qpropertyfactory.h"
#include "../shared/property/qabstractproperty.h"
#include "./qpropertylist/qpropertylistview.h"
#include <QDir>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QSettings>
#include <QFile>
#include <QPluginLoader>
#include "devicepluginloader.h"
#include <QDebug>
#include "CEmsGlobalDefines.h"


template<typename T>
int stringToEnum(const QString &str) {
    QMetaEnum metaEnum = QMetaEnum::fromType<T>();
    int enumValue = metaEnum.keyToValue(str.toUtf8().constData());
    return enumValue; // 返回对应的整型值
}

template<typename T>
QString intToEnumStr(int enumValue) {
    QMetaEnum metaEnum = QMetaEnum::fromType<T>();
    const char *key = metaEnum.valueToKey(enumValue);
    if (key != nullptr) {
        return QString(key); // 返回枚举对应的字符串
    } else {
        return QString(); // 如果没有找到对应的值，返回空字符串
    }
}


StationDialog::StationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StationDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & (~Qt::WindowContextHelpButtonHint));

    m_propertyView = new QPropertyListView(this);
    connect(m_propertyView, SIGNAL(notifyPropertyEdit(QAbstractProperty*, QVariant)),
            this, SLOT(onPropertyEdit(QAbstractProperty*, QVariant)));

    ui->vLayoutPropertyEditor->addWidget(m_propertyView);

    ui->num->setText("");
    ui->devices->setText("");
    ui->PowerCtrl->setText("");
    ui->MonitorCtrl->setText("");
    ui->PCS->setText("");
    ui->BAMS->setText("");
    ui->Pump->setText("");
    ui->PumpCtrl->setText("");
    ui->editTagDesc->setPlainText("");
}

StationDialog::~StationDialog()
{
    delete ui;
}

void StationDialog::on_btnHelp_clicked()
{

}

/*
* 设备选择
*/
void StationDialog::on_btnDeviceSelect_clicked()
{
    DeviceListDialog *pDlg = new DeviceListDialog("Station", this);
    if(pDlg->exec() == QDialog::Accepted) {
        QString devName = pDlg->GetDeviceName();
        m_szPluginName = devName;
        // 查找相同的设备名称
        int findCnt = 0;
        DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
continueFind:
        for(int i = 0; i < deviceInfo.m_listDevModleInfoObject.count(); i++) {
            DevModleInfoObject *pObj = deviceInfo.m_listDevModleInfoObject.at(i);
            if(pObj->m_name == devName) {
                findCnt++;
                devName = pDlg->GetDeviceName() + QString("_%1").arg(findCnt);
                goto continueFind;
            }
        }

        ui->devices->setText(devName);
        IDevicePlugin *pDevPluginObj = DevicePluginLoader::getInstance()->getPluginObject(m_szPluginName);
        if (pDevPluginObj) {
            pDevPluginObj->getDefaultDeviceProperty(m_properties);
            pDevPluginObj->getDefaultDevicePropertyDataType(m_propType);
        }
        this->updatePropertyEditor();
    }
}

/*
* 协议选择
*/
void StationDialog::on_btnProtocolSelect_clicked()
{
    IDevicePlugin *pDevPluginObj = DevicePluginLoader::getInstance()->getPluginObject(m_szPluginName);
    if (pDevPluginObj) {
        SelectProtocolDialog *pDlg = new SelectProtocolDialog(this);
        QString szDeviceDescInfo = pDevPluginObj->getDeviceDescInfo();
        XMLObject xmlObj;
        if(xmlObj.load(szDeviceDescInfo, NULL)) {
            pDlg->SetProtocolList(xmlObj.getProperty("SupportProtocol").split("|"));
            if(pDlg->exec() == QDialog::Accepted) {
//                ui->editProtocol->setText(pDlg->GetProtocolName());
            }
        }
    }
}


void StationDialog::on_btnCheck_clicked()
{
    if(check_data()) {
        QMessageBox::information(this, tr("系统提示"), tr("设置正确！"));
    }
}

void StationDialog::on_btnOk_clicked()
{
    if(check_data()) {
        QDialog::accept();
    }
}

void StationDialog::on_btnExit_clicked()
{
    QDialog::reject();
}



bool StationDialog::check_data()
{
    bool ret = true;
#if 0
    if(ui->editProjectName->text().isEmpty()) {
        QMessageBox::information(this, tr("系统提示"), tr(""));
        ret = false;
    }
#endif
    return ret;
}


QString StationDialog::GetDeviceName() const
{
    return ui->devices->text();
}

QString StationDialog::pluginName() const
{
    return m_szPluginName;
}

void StationDialog::load(const QString &szName)
{
    if(szName == "") {
        return;
    }
    DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    DevModleInfoObject *pObj = deviceInfo.getObjectByName(szName);
    if(pObj == NULL) {
        return;
    }
    m_szPluginName = pObj->m_deviceName;

    ui->num->setText(QString::number(pObj->num));
    ui->devices->setText(pObj->devices);

    ui->PowerCtrl->setText(pObj->PowerCtrl);
    ui->MonitorCtrl->setText(pObj->MonitorCtrl);
    ui->PCS->setText(pObj->PCS);
    ui->BAMS->setText(pObj->BAMS);
    ui->Pump->setText(pObj->Pump);
    ui->PumpCtrl->setText(pObj->PumpCtrl);

    ui->editTagDesc->setPlainText("");

    NetDevice netDev;
    netDev.fromString(pObj->m_portParameters);

    QString pluginName = pObj->m_deviceName;
    IDevicePlugin *pDevPluginObj = DevicePluginLoader::getInstance()->getPluginObject(pluginName);
    if (pDevPluginObj) {
        if(pObj->m_properties == "") {
            pDevPluginObj->getDefaultDeviceProperty(m_properties);
        } else {
            pDevPluginObj->readProperties(pObj->m_properties, m_properties);
        }
        pDevPluginObj->getDefaultDevicePropertyDataType(m_propType);
    }
    this->updatePropertyEditor();
}

void StationDialog::save(const QString &szName)
{
    DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    DevModleInfoObject *pObj = deviceInfo.getObjectByName(szName);

    if(pObj == NULL) {
        pObj = deviceInfo.newObject();
        if(pObj == NULL) {
            return;
        }
    }

    pObj->m_deviceType = "Station";

    pObj->m_deviceName = m_szPluginName;

    pObj->num = ui->num->text().toInt();
    pObj->devices = ui->devices->text();
    pObj->m_name  = pObj->devices;
    pObj->PowerCtrl = ui->PowerCtrl->text();
    pObj->MonitorCtrl = ui->MonitorCtrl->text();
    pObj->PCS = ui->PCS->text();
    pObj->BAMS = ui->BAMS->text();
    pObj->Pump = ui->Pump->text();
    pObj->PumpCtrl = ui->PumpCtrl->text();


    NetDevice netDev;

    pObj->m_portParameters = netDev.toString();

    QString pluginName = pObj->m_deviceName;
    IDevicePlugin *pDevPluginObj = DevicePluginLoader::getInstance()->getPluginObject(pluginName);
    if (pDevPluginObj) {
        pDevPluginObj->writeProperties(pObj->m_properties, m_properties);
    }
}

QString StationDialog::getValue2ByValue1(const QString &szVal1,
        QVector<QPair<QString, QString>>& properties)
{
    for (int i = 0; i < properties.size(); ++i) {
        if (properties[i].first == szVal1) {
            return properties[i].second;
        }
    }
    return "";
}


void StationDialog::setValue2ByValue1(const QString &szVal1,
        const QString &szVal2,
        QVector<QPair<QString, QString>>& properties)
{
    for (int i = 0; i < properties.size(); ++i) {
        if (properties[i].first == szVal1) {
            properties[i].second = szVal2;
        }
    }
}


///
/// \brief StationDialog::updatePropertyEditor
/// \details 更新PropertyEditor数据
///
void StationDialog::updatePropertyEditor()
{
    if(m_properties.count() != m_propType.count()) {
        return;
    }

    QList<QAbstractProperty *> listProperties;
    QAbstractProperty* pProObj = NULL;

    for (int i = 0; i < m_properties.size(); ++i) {
        QString szKey = m_properties[i].first;
        QString szValue = m_properties[i].second;
        QString szType = m_propType[i].second;

        if(szType == QString("int")) {
            pProObj = QPropertyFactory::create_property("Number");
            if(pProObj != NULL) {
                pProObj->setObjectProperty("name", szKey);
                pProObj->setAttribute("show_name", szKey);
                pProObj->setAttribute("group", "Attributes");
                pProObj->setAttribute(ATTR_CAN_SAME, true);
                QVariant val;
                val.setValue(szValue);
                pProObj->setValue(val);
                listProperties.append(pProObj);
            }
        } else if(szType == QString("bool")) {
            pProObj = QPropertyFactory::create_property("Bool");
            if(pProObj != NULL) {
                pProObj->setObjectProperty("name", szKey);
                pProObj->setAttribute("show_name", szKey);
                pProObj->setAttribute("group", "Attributes");
                pProObj->setAttribute(ATTR_CAN_SAME, true);
                QVariant val;
                val.setValue(szValue);
                pProObj->setValue(val);
                listProperties.append(pProObj);
            }
        }
    }

    m_propertyView->setPropertys(listProperties);
}





void StationDialog::onPropertyEdit(QAbstractProperty *pro, const QVariant &value)
{
    if(m_properties.count() != m_propType.count()) {
        return;
    }

    QString id = pro->getObjectProperty("name").toString();
    QString szType = getValue2ByValue1(id, m_propType);

    if(szType == QString("int")) {
        setValue2ByValue1(id, value.toString(), m_properties);
    } else if(szType == QString("bool")) {
        bool val = value.toBool();
        QString szVal = val ? "true" : "false";
        setValue2ByValue1(id, szVal, m_properties);
    }

    pro->setValue(value);
}




#include "DevModleDialog.h"
#include "ui_DevModleDialog.h"
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

template <typename T>
int stringToEnum(const QString &str)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<T>();
    int enumValue      = metaEnum.keyToValue(str.toUtf8().constData());
    return enumValue; // 返回对应的整型值
}

template <typename T>
QString intToEnumStr(int enumValue)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<T>();
    const char *key    = metaEnum.valueToKey(enumValue);
    if (key != nullptr) {
        return QString(key); // 返回枚举对应的字符串
    } else {
        return QString(); // 如果没有找到对应的值，返回空字符串
    }
}

DevModleDialog::DevModleDialog(QWidget *parent) : QDialog(parent), ui(new Ui::DevModleDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & (~Qt::WindowContextHelpButtonHint));

    m_propertyView = new QPropertyListView(this);
    connect(m_propertyView, SIGNAL(notifyPropertyEdit(QAbstractProperty *, QVariant)), this, SLOT(onPropertyEdit(QAbstractProperty *, QVariant)));

    ui->vLayoutPropertyEditor->addWidget(m_propertyView);

    ui->dev_Name->setText("");

    QStringList szListCategory;
    QMetaEnum metaEnum = QMetaEnum::fromType<CEmsGlobalDefines::EmsDevType>();
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        szListCategory << metaEnum.key(i);
    }
    ui->Category->addItems(szListCategory);
    ui->Category->setCurrentIndex(0);

    QStringList szListArchType;
    metaEnum = QMetaEnum::fromType<CEmsGlobalDefines::ArchType>();
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        szListArchType << metaEnum.key(i);
    }
    ui->ArchType->addItems(szListArchType);
    ui->ArchType->setCurrentIndex(0);

    ui->ArchType_2->addItems(szListArchType);
    ui->ArchType_2->setCurrentIndex(0);

    QStringList szListBusType;
    metaEnum = QMetaEnum::fromType<CEmsPropertySheet::EmsBus>();
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        szListBusType << metaEnum.key(i);
    }
    ui->BusType->addItems(szListBusType);
    ui->BusType->setCurrentIndex(0);

    ui->BusType_2->addItems(szListBusType);
    ui->BusType_2->setCurrentIndex(0);

    QStringList szListProtoType;
    metaEnum = QMetaEnum::fromType<CEmsPropertySheet::EmsProto>();
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        szListProtoType << metaEnum.key(i);
    }
    ui->ProtoType->addItems(szListProtoType);
    ui->ProtoType->setCurrentIndex(0);

    ui->ClassID->setText("");
    ui->ClassID_2->setText("");
    ui->editTagDesc->setPlainText("");

    ui->isCollect->setChecked(false);
    ui->isUpload->setChecked(false);

    QStringList szListDevComm;
    DeviceInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_deviceInfo;
    for (int i = 0; i < deviceInfo.m_listDeviceInfoObject.count(); i++) {
        DeviceInfoObject *pObj = deviceInfo.m_listDeviceInfoObject.at(i);
        szListDevComm << pObj->m_name;
    }

    ui->commDev->addItems(szListDevComm);
    ui->commDev->setCurrentIndex(-1);

    ui->commDev_2->addItems(szListDevComm);
    ui->commDev_2->setCurrentIndex(-1);

    QStringList szListDevModle;
    DevModleInfo &devModleInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    for (int i = 0; i < devModleInfo.m_listDevModleInfoObject.count(); i++) {
        DevModleInfoObject *pObj = devModleInfo.m_listDevModleInfoObject.at(i);
        if (pObj->m_deviceType == "DevModle") {
            szListDevModle << pObj->m_name;
        }
    }

    ui->devModel->addItems(szListDevModle);
    ui->devModel->setCurrentIndex(-1);

    ui->devModel_2->addItems(szListDevModle);
    ui->devModel_2->setCurrentIndex(-1);

    connect(ui->add, &QToolButton::clicked, this, &DevModleDialog::insertRows);
    connect(ui->remove, &QToolButton::clicked, this, &DevModleDialog::removeRows);

    connect(ui->commCheckBox, &QCheckBox::stateChanged, ui->commDev, &QComboBox::setEnabled);
    connect(ui->devCheckBox, &QCheckBox::stateChanged, ui->devModel, &QComboBox::setEnabled);

    connect(ui->commCheckBox_2, &QCheckBox::stateChanged, ui->commDev_2, &QComboBox::setEnabled);
    connect(ui->devCheckBox_2, &QCheckBox::stateChanged, ui->devModel_2, &QComboBox::setEnabled);


}

DevModleDialog::~DevModleDialog()
{
    delete ui;
}

void DevModleDialog::on_btnHelp_clicked()
{
}

/*
 * 设备选择
 */
void DevModleDialog::on_btnDeviceSelect_clicked()
{
    DeviceListDialog *pDlg = new DeviceListDialog("DevModle", this);
    if (pDlg->exec() == QDialog::Accepted) {
        QString devName = pDlg->GetDeviceName();
        m_szPluginName  = devName;
        // 查找相同的设备名称
        int findCnt              = 0;
        DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
continueFind:
        for (int i = 0; i < deviceInfo.m_listDevModleInfoObject.count(); i++) {
            DevModleInfoObject *pObj = deviceInfo.m_listDevModleInfoObject.at(i);
            if (pObj->m_name == devName) {
                findCnt++;
                devName = pDlg->GetDeviceName() + QString("_%1").arg(findCnt);
                goto continueFind;
            }
        }

        ui->dev_Name->setText(devName);
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
void DevModleDialog::on_btnProtocolSelect_clicked()
{
    IDevicePlugin *pDevPluginObj = DevicePluginLoader::getInstance()->getPluginObject(m_szPluginName);
    if (pDevPluginObj) {
        SelectProtocolDialog *pDlg = new SelectProtocolDialog(this);
        QString szDeviceDescInfo   = pDevPluginObj->getDeviceDescInfo();
        XMLObject xmlObj;
        if (xmlObj.load(szDeviceDescInfo, NULL)) {
            pDlg->SetProtocolList(xmlObj.getProperty("SupportProtocol").split("|"));
            if (pDlg->exec() == QDialog::Accepted) {
                //                ui->editProtocol->setText(pDlg->GetProtocolName());
            }
        }
    }
}

void DevModleDialog::on_btnCheck_clicked()
{
    if (check_data()) {
        QMessageBox::information(this, tr("系统提示"), tr("设置正确！"));
    }
}

void DevModleDialog::on_btnOk_clicked()
{
    if (check_data()) {
        QDialog::accept();
    }
}

void DevModleDialog::on_btnExit_clicked()
{
    QDialog::reject();
}

bool DevModleDialog::check_data()
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

QString DevModleDialog::GetDeviceName() const
{
    return ui->dev_Name->text();
}

QString DevModleDialog::pluginName() const
{
    return m_szPluginName;
}

void DevModleDialog::load(const QString &szName)
{
    if (szName == "") {
        return;
    }
    DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    DevModleInfoObject *pObj = deviceInfo.getObjectByName(szName);
    if (pObj == NULL) {
        return;
    }
    ui->dev_Name->setText(pObj->m_name);
    m_szPluginName = pObj->m_deviceName;

    ui->dev_Name->setText(pObj->dev_Name);
    ui->Category->setCurrentText(intToEnumStr<CEmsGlobalDefines::EmsDevType>(pObj->Category));
    ui->ArchType->setCurrentText(intToEnumStr<CEmsGlobalDefines::ArchType>(pObj->ArchType));
    ui->BusType->setCurrentText(intToEnumStr<CEmsPropertySheet::EmsBus>(pObj->BusType));
    ui->ProtoType->setCurrentText(intToEnumStr<CEmsPropertySheet::EmsProto>(pObj->ProtoType));

    ui->isCollect->setChecked(pObj->isCollect);
    ui->ClassID->setText(pObj->ClassID);
    ui->dev_manufactory->setText(pObj->dev_manufactory);
    ui->dev_Type->setText(pObj->dev_Type);

    ui->isUpload->setChecked(pObj->isUpload);
    ui->ArchType_2->setCurrentText(intToEnumStr<CEmsGlobalDefines::ArchType>(pObj->ArchType_2));
    ui->BusType_2->setCurrentText(intToEnumStr<CEmsPropertySheet::EmsBus>(pObj->BusType_2));
    ui->ClassID_2->setText(pObj->ClassID_2);

    ui->commDev->setCurrentText(pObj->commDev);
    ui->devModel->setCurrentText(pObj->devModel);

    ui->commDev_2->setCurrentText(pObj->commDev_2);
    ui->devModel_2->setCurrentText(pObj->devModel_2);

    ui->commCheckBox->setChecked(!pObj->commDev.isEmpty());
    ui->devCheckBox->setChecked(!pObj->devModel.isEmpty());
    ui->commCheckBox_2->setChecked(!pObj->commDev_2.isEmpty());
    ui->devCheckBox_2->setChecked(!pObj->devModel_2.isEmpty());

    for (int i = 0; i < pObj->customParameters.size(); ++i) {
        auto &cmdArgObj = pObj->customParameters[i];

        // 新增一行
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        QTableWidgetItem *argAddrItem = new QTableWidgetItem(cmdArgObj[0]);
        ui->tableWidget->setItem(row, 0, argAddrItem);

        QTableWidgetItem *argValueItem = new QTableWidgetItem(cmdArgObj[1]);
        ui->tableWidget->setItem(row, 1, argValueItem);

        QTableWidgetItem *argTypeItem = new QTableWidgetItem(cmdArgObj[2]);
        ui->tableWidget->setItem(row, 2, argTypeItem);
    }

    ui->editTagDesc->setPlainText("");

    NetDevice netDev;
    netDev.fromString(pObj->m_portParameters);

    QString pluginName           = pObj->m_deviceName;
    IDevicePlugin *pDevPluginObj = DevicePluginLoader::getInstance()->getPluginObject(pluginName);
    if (pDevPluginObj) {
        if (pObj->m_properties == "") {
            pDevPluginObj->getDefaultDeviceProperty(m_properties);
        } else {
            pDevPluginObj->readProperties(pObj->m_properties, m_properties);
        }
        pDevPluginObj->getDefaultDevicePropertyDataType(m_propType);
    }
    this->updatePropertyEditor();
}

void DevModleDialog::save(const QString &szName)
{
    DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    DevModleInfoObject *pObj = deviceInfo.getObjectByName(szName);

    if (pObj == NULL) {
        pObj = deviceInfo.newObject();
        if (pObj == NULL) {
            return;
        }
    }

    pObj->m_deviceType = "DevModle";
    pObj->m_name       = ui->dev_Name->text();
    pObj->m_deviceName = m_szPluginName;

    pObj->dev_Name  = ui->dev_Name->text();
    pObj->Category  = stringToEnum<CEmsGlobalDefines::EmsDevType>(ui->Category->currentText());
    pObj->ArchType  = stringToEnum<CEmsGlobalDefines::ArchType>(ui->ArchType->currentText());
    pObj->BusType   = stringToEnum<CEmsPropertySheet::EmsBus>(ui->BusType->currentText());
    pObj->ProtoType = stringToEnum<CEmsPropertySheet::EmsProto>(ui->ProtoType->currentText());

    pObj->isCollect       = ui->isCollect->isChecked();
    pObj->ClassID         = ui->ClassID->text();
    pObj->dev_manufactory = ui->dev_manufactory->text();
    pObj->dev_Type        = ui->dev_Type->text();

    pObj->isUpload   = ui->isUpload->isChecked();
    pObj->ArchType_2 = stringToEnum<CEmsGlobalDefines::ArchType>(ui->ArchType_2->currentText());
    pObj->BusType_2  = stringToEnum<CEmsPropertySheet::EmsBus>(ui->BusType_2->currentText());
    pObj->ClassID_2  = ui->ClassID_2->text();


    if(ui->commCheckBox->isChecked())
    {
        pObj->commDev  = ui->commDev->currentText();}
    else{
        pObj->commDev  = "";
    }

    if(ui->devCheckBox->isChecked())
    {
        pObj->devModel  = ui->devModel->currentText();}
    else{
        pObj->devModel  = "";
    }

    if(ui->commCheckBox_2->isChecked())
    {
        pObj->commDev_2  = ui->commDev_2->currentText();}
    else{
        pObj->commDev_2  = "";
    }

    if(ui->devCheckBox_2->isChecked())
    {
        pObj->devModel_2  = ui->devModel_2->currentText();}
    else{
        pObj->devModel_2  = "";
    }

    int newRow = ui->tableWidget->rowCount();
    pObj->customParameters.clear();
    for (int i = 0; i < newRow; ++i) {
        QString argName;
        QString argValue;
        QString argType;
        QVector<QString> argGroup;
        if (ui->tableWidget->item(i, 0)) {
            argName = ui->tableWidget->item(i, 0)->text();
            argGroup.append(argName);
        }
        if (ui->tableWidget->item(i, 1)) {
            argValue = ui->tableWidget->item(i, 1)->text();
            argGroup.append(argValue);
        }

        if (ui->tableWidget->item(i, 2)) {
            argType = ui->tableWidget->item(i, 2)->text();
            argGroup.append(argType);
        }
        pObj->customParameters.append(argGroup);
    }

    NetDevice netDev;

    pObj->m_portParameters = netDev.toString();

    QString pluginName           = pObj->m_deviceName;
    IDevicePlugin *pDevPluginObj = DevicePluginLoader::getInstance()->getPluginObject(pluginName);
    if (pDevPluginObj) {
        pDevPluginObj->writeProperties(pObj->m_properties, m_properties);
    }
}

QString DevModleDialog::getValue2ByValue1(const QString &szVal1, QVector<QPair<QString, QString>> &properties)
{
    for (int i = 0; i < properties.size(); ++i) {
        if (properties[i].first == szVal1) {
            return properties[i].second;
        }
    }
    return "";
}

void DevModleDialog::setValue2ByValue1(const QString &szVal1, const QString &szVal2, QVector<QPair<QString, QString>> &properties)
{
    for (int i = 0; i < properties.size(); ++i) {
        if (properties[i].first == szVal1) {
            properties[i].second = szVal2;
        }
    }
}

///
/// \brief DevModleDialog::updatePropertyEditor
/// \details 更新PropertyEditor数据
///
void DevModleDialog::updatePropertyEditor()
{
    if (m_properties.count() != m_propType.count()) {
        return;
    }

    QList<QAbstractProperty *> listProperties;
    QAbstractProperty *pProObj = NULL;

    for (int i = 0; i < m_properties.size(); ++i) {
        QString szKey   = m_properties[i].first;
        QString szValue = m_properties[i].second;
        QString szType  = m_propType[i].second;

        if (szType == QString("int")) {
            pProObj = QPropertyFactory::create_property("Number");
            if (pProObj != NULL) {
                pProObj->setObjectProperty("name", szKey);
                pProObj->setAttribute("show_name", szKey);
                pProObj->setAttribute("group", "Attributes");
                pProObj->setAttribute(ATTR_CAN_SAME, true);
                QVariant val;
                val.setValue(szValue);
                pProObj->setValue(val);
                listProperties.append(pProObj);
            }
        } else if (szType == QString("bool")) {
            pProObj = QPropertyFactory::create_property("Bool");
            if (pProObj != NULL) {
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

void DevModleDialog::onPropertyEdit(QAbstractProperty *pro, const QVariant &value)
{
    if (m_properties.count() != m_propType.count()) {
        return;
    }

    QString id     = pro->getObjectProperty("name").toString();
    QString szType = getValue2ByValue1(id, m_propType);

    if (szType == QString("int")) {
        setValue2ByValue1(id, value.toString(), m_properties);
    } else if (szType == QString("bool")) {
        bool val      = value.toBool();
        QString szVal = val ? "true" : "false";
        setValue2ByValue1(id, szVal, m_properties);
    }

    pro->setValue(value);
}

void DevModleDialog::insertRows()
{
    int newRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(newRow); // 增加一行

    // 在第一列添加普通文本项
    ui->tableWidget->setItem(newRow, 0, new QTableWidgetItem(""));
    ui->tableWidget->setItem(newRow, 1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(newRow, 2, new QTableWidgetItem(""));
}

void DevModleDialog::removeRows()
{
    int newRow = ui->tableWidget->rowCount();
    ui->tableWidget->removeRow(newRow - 1);
}

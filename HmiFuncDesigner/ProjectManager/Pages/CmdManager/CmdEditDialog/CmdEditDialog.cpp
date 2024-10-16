#include "CmdEditDialog.h"
#include "ui_CmdEditDialog.h"
#include <QMessageBox>
//#include "CEmsGlobalDefines.h"
#include "qsoftcore.h"
#include "../shared/projdata/Tag.h"
#include "CmdTag.h"


//template<typename T>
//int stringToEnum(const QString &str) {
//    QMetaEnum metaEnum = QMetaEnum::fromType<T>();
//    int enumValue = metaEnum.keyToValue(str.toUtf8().constData());
//    return enumValue; // 返回对应的整型值
//}

CmdEditDialog::CmdEditDialog(QWidget *parent, Tag *objTag)
    : QDialog(parent),
      ui(new Ui::CmdEditDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & (~Qt::WindowContextHelpButtonHint));

    if(objTag)
    {
        m_objTag = static_cast<CmdTag*>(objTag);
        m_jsonTagObj = m_objTag->toJsonObject();
    }
    m_mapDevToAddrType.clear();
    m_mapAddrTypeToAddrTypeAlias.clear();
    m_mapAddrTypeToSubAddrType.clear();
    m_mapAddrTypeToDataType.clear();
    ui->tabWidget->setCurrentIndex(0);

    ui->cboDataType->setCurrentIndex(-1);
    ui->editTagDesc->setPlainText("");

    QStringList szListDataType;
    szListDataType << tr("0x01") // 读取线圈状态
                   << tr("0x02") // 读取离散输入状态
                   << tr("0x03") // 读取保持寄存器
                   << tr("0x04") // 读取输入寄存器
                   << tr("0x05") // 写单个线圈
                   << tr("0x06") // 写单个保持寄存器
                   << tr("0x0F") // 写多个线圈
                   << tr("0x10"); // 写多个保持寄存器

    ui->FunctionCodes->addItems(szListDataType);
    ui->FunctionCodes->setCurrentIndex(-1);

    ui->cboDataType->setCurrentIndex(-1);
    ui->cboReadWriteType->setCurrentIndex(-1);

    QStringList szListDev;

    DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    for(int i = 0; i < deviceInfo.m_listDevModleInfoObject.count(); i++) {
        DevModleInfoObject *pObj = deviceInfo.m_listDevModleInfoObject.at(i);
        if(pObj->m_deviceType == "DevModle") {
            szListDev << pObj->m_name;
        }
    }

    ui->cboDev->addItems(szListDev);
    ui->cboDev->setCurrentIndex(-1);
    ui->btnSave->setEnabled(false);

}

CmdEditDialog::~CmdEditDialog()
{
    delete ui;
}

///
/// \brief CmdEditDialog::setInfosAndTagObj
/// @details 设置变量信息
/// \param jsonTag 变量
///
void CmdEditDialog::setTagObj(QJsonObject &jsonTag)
{
    m_jsonTagObj = jsonTag;
}


///
/// \brief CmdEditDialog::getTagObj
/// @details 返回变量信息
/// \return 变量信息
///
QJsonObject CmdEditDialog::getTagObj()
{
    return m_jsonTagObj;
}


///
/// \brief CmdEditDialog::setAddrTypeLimit
/// \details 设置地址类型的限制范围
/// \param mapLimit
///
void CmdEditDialog::setAddrTypeLimit(QMap<QString, QMap<QString, quint32>> mapLimit)
{
    m_mapAddrTypeToLimit = mapLimit;
}


///
/// \brief CmdEditDialog::on_btnOk_clicked
/// \details 单击确定按钮
///
void CmdEditDialog::on_btnOk_clicked()
{
    bool bOk = false;

    on_btnSave_clicked();

    this->accept();
}

///
/// \brief CmdEditDialog::on_btnCancel_clicked
/// \details 单击取消按钮
///
void CmdEditDialog::on_btnCancel_clicked()
{
    this->reject();
}

///
/// \brief CmdEditDialog::on_cboAddrType_currentTextChanged
/// \details 地址类型改变
/// \param szAddrType
///
void CmdEditDialog::on_cboAddrType_currentTextChanged(const QString &szAddrType)
{
    if(szAddrType == "") {
        return;
    }
//    QStringList szListSubAddrType;
//    szListSubAddrType = m_mapAddrTypeToSubAddrType[szAddrType];
//    ui->cboAddrType2->clear();
//    ui->cboAddrType2->addItems(szListSubAddrType);
//    ui->cboAddrType2->setCurrentIndex(-1);

//    ui->cboAddrType2->setEnabled((szListSubAddrType.size() > 0));
//    ui->editAddrOffset2->setEnabled((szListSubAddrType.size() > 0));

    ui->cboDataType->clear();
    ui->cboDataType->addItems(m_mapAddrTypeToDataType[szAddrType]);
}

void CmdEditDialog::on_cboAddrType2_currentTextChanged(const QString &szAddrType)
{
    if(szAddrType == "") {
        return;
    }
    ui->cboDataType->clear();
    ui->cboDataType->addItems(m_mapAddrTypeToDataType[szAddrType]);
}

///
/// \brief CmdEditDialog::updateUI
/// \details 更新UI
///
void CmdEditDialog::updateUI()
{
    ui->tabWidget->setCurrentIndex(0);

//    QStringList listDevs = m_mapDevToAddrType.keys();
//    ui->cboDev->clear();
//    ui->cboDev->addItems(listDevs);

    if(!m_jsonTagObj.isEmpty()) {
        ui->cboDev->setCurrentText(m_jsonTagObj["dev"].toString());

        ui->editTagName->setText(m_jsonTagObj["name"].toString());

        ui->cboAddrType->setCurrentText(m_jsonTagObj["addr"].toString());
        ui->editAddrOffset->setText(m_jsonTagObj["offset"].toString());
        ui->FunctionCodes->setCurrentText(m_jsonTagObj["functionCodes"].toString());
        ui->rate->setText(m_jsonTagObj["rate"].toString());
        ui->cboDataType->setCurrentText(m_jsonTagObj["type"].toString());
        ui->editTagUnit->setText(m_jsonTagObj["unit"].toString());
        ui->cboReadWriteType->setCurrentText(m_jsonTagObj["writeable"].toString());
        ui->cboDev->setCurrentText(m_jsonTagObj["dev"].toString());

        QString szDataType = m_jsonTagObj["type"].toString();
        if(szDataType != "") {
            ui->cboDataType->setCurrentText(szDataType);
        }
        ui->cboReadWriteType->setCurrentIndex(m_jsonTagObj["writeable"].toInt());
        ui->editTagDesc->setPlainText(m_jsonTagObj["remark"].toString());
    }
}

///
/// \brief CmdEditDialog::on_cboDev_currentIndexChanged
/// \details 设备改变
/// \param szDev 设备名称
///
void CmdEditDialog::on_cboDev_currentIndexChanged(const QString &szDev)
{
//    QStringList szListAddrType;
//    szListAddrType = m_mapDevToAddrType[szDev];
//    ui->cboAddrType->clear();
//    ui->cboAddrType->addItems(szListAddrType);
//    ui->cboAddrType->setCurrentIndex(0);
}

void CmdEditDialog::on_btnSave_clicked()
{
    m_jsonTagObj["name"] = ui->editTagName->text();
    m_jsonTagObj["addr"] = ui->cboAddrType->currentText();
    m_jsonTagObj["offset"] = ui->editAddrOffset->text();
    m_jsonTagObj["functionCodes"] = ui->FunctionCodes->currentText();
    m_jsonTagObj["rate"] = ui->rate->text();
    m_jsonTagObj["type"] = ui->cboDataType->currentText();
    m_jsonTagObj["unit"] = ui->editTagUnit->text();
    m_jsonTagObj["writeable"] = ui->cboReadWriteType->currentIndex();
    m_jsonTagObj["remark"] = ui->editTagDesc->toPlainText();
    m_jsonTagObj["dev"] = ui->cboDev->currentText();

    if(!m_objTag)
    {
        QSharedPointer<Tag> pTagObj = QSharedPointer<Tag>(new CmdTag());
        pTagObj->fromJsonObject(getTagObj());
        pTagObj->m_id = QSoftCore::getCore()->getProjectCore()->m_tagMgr->allocID();

        if(pTagObj->m_devType == "MEMORY") { // 内存变量
        }

        QSoftCore::getCore()->getProjectCore()->m_tagMgr->m_vecTags.append(pTagObj);
    }else{
        m_objTag->fromJsonObject(getTagObj());
    }
}

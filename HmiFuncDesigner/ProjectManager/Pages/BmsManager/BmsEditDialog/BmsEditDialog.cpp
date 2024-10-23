#include "BmsEditDialog.h"
#include "ui_BmsEditDialog.h"
#include <QMessageBox>
// #include "CEmsGlobalDefines.h"
#include "qsoftcore.h"
#include "../shared/projdata/Tag.h"
#include "BmsTag.h"
#include <QJsonArray>

// template<typename T>
// int stringToEnum(const QString &str) {
//     QMetaEnum metaEnum = QMetaEnum::fromType<T>();
//     int enumValue = metaEnum.keyToValue(str.toUtf8().constData());
//     return enumValue; // 返回对应的整型值
// }

BmsEditDialog::BmsEditDialog(QWidget *parent, Tag *objTag) : QDialog(parent), ui(new Ui::BmsEditDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & (~Qt::WindowContextHelpButtonHint));

    if (objTag) {
        m_objTag     = static_cast<BmsTag *>(objTag);
        m_jsonTagObj = m_objTag->toJsonObject();
    }

    ui->tabWidget->setCurrentIndex(0);

    ui->editTagDesc->setPlainText("");

    QStringList szListDev;

    DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    for (int i = 0; i < deviceInfo.m_listDevModleInfoObject.count(); i++) {
        DevModleInfoObject *pObj = deviceInfo.m_listDevModleInfoObject.at(i);
        if (pObj->m_deviceType == "DevModle") {
            szListDev << pObj->m_name;
        }
    }

    ui->cboDev->addItems(szListDev);
    ui->cboDev->setCurrentIndex(-1);
    ui->btnSave->setEnabled(false);

}

BmsEditDialog::~BmsEditDialog()
{
    delete ui;
}

///
/// \brief BmsEditDialog::setInfosAndTagObj
/// @details 设置变量信息
/// \param jsonTag 变量
///
void BmsEditDialog::setTagObj(QJsonObject &jsonTag)
{
    m_jsonTagObj = jsonTag;
}

///
/// \brief BmsEditDialog::getTagObj
/// @details 返回变量信息
/// \return 变量信息
///
QJsonObject BmsEditDialog::getTagObj()
{
    return m_jsonTagObj;
}

///
/// \brief BmsEditDialog::setAddrTypeLimit
/// \details 设置地址类型的限制范围
/// \param mapLimit
///
void BmsEditDialog::setAddrTypeLimit(QMap<QString, QMap<QString, quint32>> mapLimit)
{
}

///
/// \brief BmsEditDialog::on_btnOk_clicked
/// \details 单击确定按钮
///
void BmsEditDialog::on_btnOk_clicked()
{
    bool bOk = false;

    on_btnSave_clicked();

    this->accept();
}

///
/// \brief BmsEditDialog::on_btnCancel_clicked
/// \details 单击取消按钮
///
void BmsEditDialog::on_btnCancel_clicked()
{
    this->reject();
}

///
/// \brief BmsEditDialog::updateUI
/// \details 更新UI
///
void BmsEditDialog::updateUI()
{
    // 切换到第一个 Tab 页
    ui->tabWidget->setCurrentIndex(0);

    // 确保 JSON 对象不为空
    if (!m_jsonTagObj.isEmpty()) {
        ui->editTagName->setText(m_jsonTagObj["name"].toString());
        // 设置设备类型
        ui->cboDev->setCurrentText(m_jsonTagObj["dev"].toString());

        // 设置标签描述
        ui->editTagDesc->setPlainText(m_jsonTagObj["remark"].toString());

        ui->dataSource->setCurrentIndex(m_jsonTagObj["dataSource"].toString().toInt());
        ui->isCollect->setChecked(m_jsonTagObj["isCollect"].toString().toInt() == 0 ? true : false);
        ui->editTagUnit->setText(m_jsonTagObj["unit"].toString());
        ui->editAddrOffset->setText(m_jsonTagObj["addrOffset"].toString());
        ui->FunctionCodes->setCurrentText(m_jsonTagObj["functionCodes"].toString());
        ui->rate->setText(m_jsonTagObj["rate"].toString());
        ui->cboDataType->setCurrentText(m_jsonTagObj["dataType"].toString());
        ui->isUpload->setChecked(m_jsonTagObj["isUpload"].toString().toInt() == 0 ? true : false);
        ui->formula->setText(m_jsonTagObj["formula"].toString());

    }
}

///
/// \brief BmsEditDialog::on_cboDev_currentIndexChanged
/// \details 设备改变
/// \param szDev 设备名称
///
void BmsEditDialog::on_cboDev_currentIndexChanged(const QString &szDev)
{
    //    QStringList szListAddrType;
    //    szListAddrType = m_mapDevToAddrType[szDev];
    //    ui->cboAddrType->clear();
    //    ui->cboAddrType->addItems(szListAddrType);
    //    ui->cboAddrType->setCurrentIndex(0);
}

void BmsEditDialog::on_btnSave_clicked()
{
    m_jsonTagObj["name"] = ui->editTagName->text();
    m_jsonTagObj["remark"] = ui->editTagDesc->toPlainText();
    m_jsonTagObj["dev"]    = ui->cboDev->currentText();


    m_jsonTagObj["dataSource"] = QString::number(ui->dataSource->currentIndex());
    m_jsonTagObj["isCollect"] = QString::number(ui->isCollect->isChecked() ? 0 : 1);

    m_jsonTagObj["unit"] = ui->editTagUnit->text();

    m_jsonTagObj["addrOffset"] = ui->editAddrOffset->text();

    m_jsonTagObj["functionCodes"] = ui->FunctionCodes->currentText();
    m_jsonTagObj["rate"] = ui->rate->text();
    m_jsonTagObj["dataType"] = ui->cboDataType->currentText();

    m_jsonTagObj["isUpload"] = QString::number(ui->isUpload->isChecked() ? 0 : 1);
    m_jsonTagObj["formula"] = ui->formula->text();

    if (!m_objTag) {
        QSharedPointer<Tag> pTagObj = QSharedPointer<Tag>(new BmsTag());
        pTagObj->fromJsonObject(getTagObj());
        pTagObj->m_id = QSoftCore::getCore()->getProjectCore()->m_tagMgr->allocID();

        if (pTagObj->m_devType == "MEMORY") { // 内存变量
        }

        QSoftCore::getCore()->getProjectCore()->m_tagMgr->m_vecTags.append(pTagObj);
    } else {
        m_objTag->fromJsonObject(getTagObj());
    }
}

#include "TagEditDialog.h"
#include "ui_TagEditDialog.h"
#include <QMessageBox>
#include "qsoftcore.h"
#include "../shared/projdata/Tag.h"


TagEditDialog::TagEditDialog(QWidget *parent, Tag* objTag)
    : QDialog(parent),
      ui(new Ui::TagEditDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & (~Qt::WindowContextHelpButtonHint));

    if(objTag)
    {
        m_objTag = static_cast<RedisTag*>(objTag);
        m_jsonTagObj = m_objTag->toJsonObject();
    }

    m_mapDevToAddrType.clear();
    m_mapAddrTypeToAddrTypeAlias.clear();
    m_mapAddrTypeToSubAddrType.clear();
    m_mapAddrTypeToDataType.clear();
    ui->tabWidget->setCurrentIndex(0);
    ui->editAddrOffset->setText("");
    ui->editTagName->setText("");
    ui->cboDataType->setCurrentIndex(-1);
    ui->editTagDesc->setPlainText("");
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

    ui->cboDataType->setCurrentIndex(-1);
}

TagEditDialog::~TagEditDialog()
{
    delete ui;
}

///
/// \brief TagEditDialog::setInfosAndTagObj
/// @details 设置变量信息
/// \param jsonTag 变量
///
void TagEditDialog::setTagObj(QJsonObject &jsonTag)
{
    m_jsonTagObj = jsonTag;
}


///
/// \brief TagEditDialog::getTagObj
/// @details 返回变量信息
/// \return 变量信息
///
QJsonObject TagEditDialog::getTagObj()
{
    return m_jsonTagObj;
}

///
/// \brief TagEditDialog::setAddrTypeAndDataType
/// @details 设置地址类型和数据类型
/// \param mapAddrType 地址类型1=地址类型2x,地址类型2y,地址类型2z
/// \param mapDataType 数据类型=数据类型,数据类型,数据类型
///
void TagEditDialog::setAddrTypeAndDataType(QMap<QString, QStringList> mapDevToAddrType,
        QMap<QString, QString> mapAddrTypeToAddrTypeAlias,
        QMap<QString, QStringList> mapAddrTypeToSubAddrType,
        QMap<QString, QStringList> mapAddrTypeToDataType)
{
    m_mapDevToAddrType = mapDevToAddrType;
    m_mapAddrTypeToAddrTypeAlias = mapAddrTypeToAddrTypeAlias;
    m_mapAddrTypeToSubAddrType = mapAddrTypeToSubAddrType;
    m_mapAddrTypeToDataType = mapAddrTypeToDataType;
}


///
/// \brief TagEditDialog::setAddrTypeLimit
/// \details 设置地址类型的限制范围
/// \param mapLimit
///
void TagEditDialog::setAddrTypeLimit(QMap<QString, QMap<QString, quint32>> mapLimit)
{
    m_mapAddrTypeToLimit = mapLimit;
}


///
/// \brief TagEditDialog::on_btnOk_clicked
/// \details 单击确定按钮
///
void TagEditDialog::on_btnOk_clicked()
{
    bool bOk = false;

    on_btnSave_clicked();

    this->accept();
}

///
/// \brief TagEditDialog::on_btnCancel_clicked
/// \details 单击取消按钮
///
void TagEditDialog::on_btnCancel_clicked()
{
    this->reject();
}

///
/// \brief TagEditDialog::on_cboAddrType_currentTextChanged
/// \details 地址类型改变
/// \param szAddrType
///
void TagEditDialog::on_cboAddrType_currentTextChanged(const QString &szAddrType)
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

void TagEditDialog::on_cboAddrType2_currentTextChanged(const QString &szAddrType)
{
    if(szAddrType == "") {
        return;
    }
    ui->cboDataType->clear();
    ui->cboDataType->addItems(m_mapAddrTypeToDataType[szAddrType]);
}

///
/// \brief TagEditDialog::updateUI
/// \details 更新UI
///
void TagEditDialog::updateUI()
{
    ui->tabWidget->setCurrentIndex(0);

    QStringList listDevs = m_mapDevToAddrType.keys();

    if(!m_jsonTagObj.isEmpty()) {
        ui->cboDev->setCurrentText(m_jsonTagObj["dev"].toString());
        ui->editTagName->setText(m_jsonTagObj["name"].toString());

        QStringList szListAddrTypes = m_mapDevToAddrType[m_jsonTagObj["dev"].toString()];

        QString szAddrTypeAlias = m_jsonTagObj["addr"].toString();
        if(szAddrTypeAlias != "") {
            QString szAddrType = m_mapAddrTypeToAddrTypeAlias.key(szAddrTypeAlias);
            if(szAddrType != "") {
                szAddrTypeAlias = szAddrType;
            }
            on_cboAddrType_currentTextChanged(szAddrTypeAlias);
        }

        ui->editAddrOffset->setText(m_jsonTagObj["offset"].toString());

        QString szDataType = m_jsonTagObj["type"].toString();
        if(szDataType != "") {
            ui->cboDataType->setCurrentText(szDataType);
        }
        ui->editTagDesc->setPlainText(m_jsonTagObj["remark"].toString());

    }
}

///
/// \brief TagEditDialog::on_cboDev_currentIndexChanged
/// \details 设备改变
/// \param szDev 设备名称
///
void TagEditDialog::on_cboDev_currentIndexChanged(const QString &szDev)
{
    QStringList szListAddrType;
    szListAddrType = m_mapDevToAddrType[szDev];
}
void TagEditDialog::on_btnSave_clicked()
{
    m_jsonTagObj["name"] = ui->editTagName->text();
    m_jsonTagObj["type"] = ui->cboDataType->currentText();
    QString addr = ui->editAddrOffset->text();
    if(!ui->editAddrOffset_1->text().isEmpty())
    {
        addr += QString("#%1").arg(ui->editAddrOffset_1->text());
    }
    if(!ui->editAddrOffset_2->text().isEmpty())
    {
        addr += QString("#%1").arg(ui->editAddrOffset_2->text());
    }

    m_jsonTagObj["offset"] = addr;
    m_jsonTagObj["offsetBit"] = ui->editAddrOffsetBit->text();
    m_jsonTagObj["formula"] = ui->formula->text();
    m_jsonTagObj["remark"] = ui->editTagDesc->toPlainText();
    m_jsonTagObj["dev"] = ui->cboDev->currentText();

    if(m_objTag){
        QSharedPointer<Tag> pTagObj = QSharedPointer<Tag>(new RedisTag());
        pTagObj->fromJsonObject(getTagObj());
        pTagObj->m_id = QSoftCore::getCore()->getProjectCore()->m_tagMgr->allocID();

        if(pTagObj->m_devType == "MEMORY") { // 内存变量
    //        if(pTagObj->m_addrType == tr("自动分配")) {
    //            pTagObj->m_addrType = "AutoAlloc";
    //        }
        }

        QSoftCore::getCore()->getProjectCore()->m_tagMgr->m_vecTags.append(pTagObj);
    }else{
        m_objTag->fromJsonObject(getTagObj());
    }
}

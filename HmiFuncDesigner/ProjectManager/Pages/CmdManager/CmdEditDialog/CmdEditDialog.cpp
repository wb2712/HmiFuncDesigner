#include "CmdEditDialog.h"
#include "ui_CmdEditDialog.h"
#include <QMessageBox>
// #include "CEmsGlobalDefines.h"
#include "qsoftcore.h"
#include "../shared/projdata/Tag.h"
#include "CmdTag.h"
#include <QJsonArray>

// template<typename T>
// int stringToEnum(const QString &str) {
//     QMetaEnum metaEnum = QMetaEnum::fromType<T>();
//     int enumValue = metaEnum.keyToValue(str.toUtf8().constData());
//     return enumValue; // 返回对应的整型值
// }

CmdEditDialog::CmdEditDialog(QWidget *parent, Tag *objTag) : QDialog(parent), ui(new Ui::CmdEditDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & (~Qt::WindowContextHelpButtonHint));

    if (objTag) {
        m_objTag     = static_cast<CmdTag *>(objTag);
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

    connect(ui->add, &QToolButton::clicked, this, &CmdEditDialog::insertRows);
    connect(ui->remove, &QToolButton::clicked, this, &CmdEditDialog::removeRows);

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
/// \brief CmdEditDialog::updateUI
/// \details 更新UI
///
void CmdEditDialog::updateUI()
{
    // 切换到第一个 Tab 页
    ui->tabWidget->setCurrentIndex(0);

    // 确保 JSON 对象不为空
    if (!m_jsonTagObj.isEmpty()) {
        // 设置设备类型
        ui->cboDev->setCurrentText(m_jsonTagObj["dev"].toString());

        // 设置标签描述
        ui->editTagDesc->setPlainText(m_jsonTagObj["remark"].toString());

        // 设置命令类型（根据 on_btnSave_clicked 的逻辑）
        ui->cmdType->setText(m_jsonTagObj["cmdType"].toString());

        // 清空表格并重新填充
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0); // 清除现有的行

        // 获取 cmdArg 数组
        QJsonArray cmdArgsArray = m_jsonTagObj["cmdArg"].toArray();

        // 遍历 cmdArg 数组中的每个对象并插入到 tableWidget 中
        for (int i = 0; i < cmdArgsArray.size(); ++i) {
            QJsonObject cmdArgObj = cmdArgsArray[i].toObject();

            // 新增一行
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);

            // 设置 argAddr 列
            QTableWidgetItem *argAddrItem = new QTableWidgetItem(cmdArgObj["argAddr"].toString());
            ui->tableWidget->setItem(row, 0, argAddrItem);

            // 设置 argType 列
            QTableWidgetItem *argTypeItem = new QTableWidgetItem(cmdArgObj["argType"].toString());
            ui->tableWidget->setItem(row, 1, argTypeItem);

            // 设置 argValue 列
            QTableWidgetItem *argValueItem = new QTableWidgetItem(cmdArgObj["argValue"].toString());
            ui->tableWidget->setItem(row, 2, argValueItem);
        }
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
    m_jsonTagObj["name"] = ui->cmdName->text();
    m_jsonTagObj["remark"] = ui->editTagDesc->toPlainText();
    m_jsonTagObj["dev"]    = ui->cboDev->currentText();

    m_jsonTagObj["cmdType"] = ui->cmdType->text();

    // 创建一个 QJsonArray 用于存储多组数据
    QJsonArray groupArray;

    int newRow = ui->tableWidget->rowCount();

    for (int i = 0; i < newRow; ++i) {
        QJsonObject group1;
        if (ui->tableWidget->item(i, 0)) {
            group1["argAddr"] = ui->tableWidget->item(i, 0)->text();
        }
        if (ui->tableWidget->item(i, 1)) {
            group1["argType"] = ui->tableWidget->item(i, 1)->text();
        }
        if (ui->tableWidget->item(i, 2)) {
            group1["argValue"] = ui->tableWidget->item(i, 2)->text();
        }
        groupArray.append(group1);
    }

    m_jsonTagObj["cmdArg"] = groupArray;

    if (!m_objTag) {
        QSharedPointer<Tag> pTagObj = QSharedPointer<Tag>(new CmdTag());
        pTagObj->fromJsonObject(getTagObj());
        pTagObj->m_id = QSoftCore::getCore()->getProjectCore()->m_tagMgr->allocID();

        if (pTagObj->m_devType == "MEMORY") { // 内存变量
        }

        QSoftCore::getCore()->getProjectCore()->m_tagMgr->m_vecTags.append(pTagObj);
    } else {
        m_objTag->fromJsonObject(getTagObj());
    }
}

void CmdEditDialog::insertRows()
{
    int newRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(newRow); // 增加一行

    // 在第一列添加普通文本项
    ui->tableWidget->setItem(newRow, 0, new QTableWidgetItem(""));
    ui->tableWidget->setItem(newRow, 1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(newRow, 2, new QTableWidgetItem(""));
}

void CmdEditDialog::removeRows()
{
    int newRow = ui->tableWidget->rowCount();
    ui->tableWidget->removeRow(newRow-1);
}

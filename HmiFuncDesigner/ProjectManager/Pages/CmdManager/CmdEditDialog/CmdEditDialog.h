#ifndef CMDEDITDIALOG_H
#define CMDEDITDIALOG_H

#include <QDialog>
#include <QMap>
#include <QStringList>
#include <QJsonObject>
#include "corelibglobal.h"
#include "../shared/property/qabstractproperty.h"
#include "../shared/qprojectcore.h"


namespace Ui {
class CmdEditDialog;
}

class CmdTag;
class CmdEditDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CmdEditDialog(QWidget *parent = nullptr, Tag* objTag = nullptr);
    ~CmdEditDialog();
    // 更新UI
    void updateUI();

    // 设置地址类型的限制范围
    void setAddrTypeLimit(QMap<QString, QMap<QString, quint32>> mapLimit);
    // 设置变量信息
    void setTagObj(QJsonObject &jsonTag);
    // 返回变量信息
    QJsonObject getTagObj();

private slots:
    // 单击确定按钮
    void on_btnOk_clicked();
    // 单击取消按钮
    void on_btnCancel_clicked();
    // 地址类型改变
    void on_cboAddrType_currentTextChanged(const QString &szAddrType);
    // 地址类型改变
    void on_cboAddrType2_currentTextChanged(const QString &szAddrType);
    // 设备改变
    void on_cboDev_currentIndexChanged(const QString &szDev);

    void on_btnSave_clicked();

private:
    Ui::CmdEditDialog *ui;
    QJsonObject m_jsonTagObj; // 变量
    QMap<QString, QStringList> m_mapDevToAddrType;
    QMap<QString, QString> m_mapAddrTypeToAddrTypeAlias; // 寄存器类型名称和别名寄存器类型映射
    QMap<QString, QStringList> m_mapAddrTypeToSubAddrType;
    QMap<QString, QStringList> m_mapAddrTypeToDataType;
    QMap<QString, QMap<QString, quint32>> m_mapAddrTypeToLimit;

    CmdTag* m_objTag = nullptr;
};

#endif // DEVEDITDIALOG_H

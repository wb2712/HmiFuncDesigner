#ifndef BMSEDITDIALOG_H
#define BMSEDITDIALOG_H

#include <QDialog>
#include <QMap>
#include <QStringList>
#include <QJsonObject>
#include "corelibglobal.h"
#include "../shared/property/qabstractproperty.h"
#include "../shared/qprojectcore.h"

namespace Ui {
class BmsEditDialog;
}

class BmsTag;

class BmsEditDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BmsEditDialog(QWidget *parent = nullptr, Tag *objTag = nullptr);
    ~BmsEditDialog();
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
    // 设备改变
    void on_cboDev_currentIndexChanged(const QString &szDev);

    void on_btnSave_clicked();

private:
    Ui::BmsEditDialog *ui;
    QJsonObject m_jsonTagObj; // 变量
    BmsTag *m_objTag = nullptr;
};

#endif // DEVEDITDIALOG_H

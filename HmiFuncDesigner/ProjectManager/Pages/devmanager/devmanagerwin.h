#ifndef DEVMANAGERWIN_H
#define DEVMANAGERWIN_H

#include "../../../libs/shared/projdata/Tag.h"
#include "listviewex.h"
#include "../../Public/Public.h"
#include <QString>
#include <QWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QVBoxLayout>
#include <QMap>
#include <QTableWidget>
#include <QToolBar>
#include <QStringList>
#include <QAbstractTableModel>
#include <QVector>



class DevTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Column {
        TagID = 0,
        Name = 1,
        Addr = 2,
        DataType = 3,
        ReadWrite = 4,
        Unit = 5,
        Rate = 6,
        FunctionCodes = 7,
        Remark = 8,

        MaxColumns = 9
    };

public:
    explicit DevTableModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {}

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool setHeaderData(int, Qt::Orientation, const QVariant&, int = Qt::EditRole)
    {
        return false;
    }

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

public:
    void AppendRow(QStringList rowDat);
    void AppendRows(QVector<QStringList> rowsDat);
    void InsertRow(int i, QStringList rowDat);
    QStringList GetRow(int i);
    void UpdateRow(int i, QStringList rowDat);
    void UpdateRows(QVector<QStringList> rowsDat);

public:
    QVector<QStringList> m_tagRows;
};

//-----------------------------------------------------------------------------

class Tag;

typedef enum {
    TagAct_Add = 0,
    TagAct_Copy,
    TagAct_Cut,
    TagAct_Paste,
    TagAct_Delete,
    TagAct_Edit,

    TagAct_None = 255
} TagTableActonType;

class QTableWidgetEx : public QTableView
{
    Q_OBJECT
public:
    QTableWidgetEx(QWidget *parent = NULL);
    ~QTableWidgetEx();

    // 清空变量表
    void clearTable();
    // 刷新变量表
    void updateTable();
    // 启用或禁用功能菜单
    void setActionEnable(TagTableActonType id, bool enable);

public slots:
    // 单元格被双击
    void onDoubleClicked(const QModelIndex &index);

    // 添加变量
    void onAddTag();
    // 复制
    void onCopyTag();
    // 粘贴
    void onPasteTag();
    // 删除
    void onDeleteTag();
    // 属性
    void onEditTag();
    // 导出
    void onExportToCsv();
    // 导入
    void onImportFromCsv();

signals:
    // 单击空白区域
    void clickedBlankArea();
    // 已经拷贝或剪切变量值剪切板
    void copyOrCutTagToClipboard();
    // 剪切的变量值已经被粘贴
    void cutTagIsPasted();
    // 更新保存按钮状态
    void notifyUpdateSaveButtonStatus(bool bEnable);

private:
    // 初始化变量表控件
    void initTagsTable();
    // 设置行数据
    void setRowData(QStringList &rowDat, Tag *pObj);

protected:
    void contextMenuEvent(QContextMenuEvent * event);
    void mousePressEvent(QMouseEvent *event);

public:
    DevTableModel *m_pDevTableModel = NULL;

private:
    bool m_bCopyOrCutDone = false; // true-执行过复制或剪切, false-未执行过复制或剪切
    QMap<TagTableActonType, QAction*> m_mapIdToAction;

};



//------------------------------------------------------------------------------


class DevManagerWin : public QWidget
{
    Q_OBJECT
public:
    explicit DevManagerWin(QWidget *parent = NULL);
    ~DevManagerWin();

protected:
    bool event(QEvent *ev);

private:
    QVBoxLayout *m_pTopVLayoutObj;
    QTableWidgetEx *m_pTagMgrTableViewObj;
    QMenu *m_pMenuTagEditObj = NULL; // 变量编辑菜单
    QToolBar *m_pToolBarTagEditObj = NULL; // 变量编辑工具条
    QAction *m_pActAddTagObj = NULL; // 添加变量
    QAction *m_pActCopyTagObj = NULL; // 拷贝变量
    QAction *m_pActPasteTagObj = NULL; // 粘贴变量
    QAction *m_pActModifyTagObj = NULL; // 修改变量
    QAction *m_pActDeleteTagObj = NULL; // 删除变量
    QAction *m_pActExportTagObj = NULL; // 导出变量
    QAction *m_pActImportTagObj = NULL; // 导入变量
};

#endif // DEVMANAGERWIN_H

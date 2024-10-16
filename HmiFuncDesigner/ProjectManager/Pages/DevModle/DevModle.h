#ifndef DEVMODLE_H
#define DEVMODLE_H

#include "listviewex.h"
#include <QWidget>
#include <QStandardItemModel>
#include <QVBoxLayout>

class DevModle : public QWidget
{
    Q_OBJECT
public:
    explicit DevModle(QWidget *parent = NULL);
    ~DevModle();
    void listViewUpdate();
    QStandardItemModel *m_pCommDevModelObj = NULL;
private:
    void listViewUISetting();
//    void listViewUpdate();
    void listViewDevModleUpdate();
    void listViewCOMDeviceUpdate();
    void listViewNetDeviceUpdate();

protected:
    void contextMenuEvent(QContextMenuEvent * event);
    bool event(QEvent *ev);

public slots:
    void contextMenuEventSlot(QContextMenuEvent * event);
    void onSlotListViewProjectDoubleClicked(const QModelIndex &index);
    void onSlotNewDevice();
    void onSlotModifyDevice();
    void onSlotDeleteDevice();

private:
//    QStandardItemModel *m_pCommDevModelObj = NULL;
    ListViewEx *m_pListViewCommDevObj = NULL;
    QString m_szItemName = "";
};

#endif

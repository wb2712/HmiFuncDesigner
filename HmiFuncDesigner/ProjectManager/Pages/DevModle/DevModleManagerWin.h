#ifndef DEVMODLEMANAGERWIN_H
#define DEVMODLEMANAGERWIN_H

#include <QWidget>
#include "listviewex.h"
#include <QWidget>
#include <QStandardItemModel>
#include <QVBoxLayout>

namespace Ui {
class DevModleManagerWin;
}

class DevModleManagerWin : public QWidget
{
    Q_OBJECT

public:
    explicit DevModleManagerWin(QWidget *parent = nullptr);
    ~DevModleManagerWin();

private:
    void listViewUISetting();
    void listViewUpdate();
    void listViewDevModleUpdate();
    void listViewCOMDeviceUpdate();
    void listViewNetDeviceUpdate();

protected:
    void contextMenuEvent(QContextMenuEvent * event);
    bool event(QEvent *ev);

public slots:
    void contextMenuEventSlot(const QPoint &pos);
    void onSlotListViewProjectDoubleClicked(const QModelIndex &index);
    void onSlotNewDevice();
    void onSlotModifyDevice();
    void onSlotDeleteDevice();
    void onSlotNewStation();

    void contextMenuEventSlotStation(const QPoint &pos);
    void onSlotModifyStation();
    void onSlotDeleteStation();
    void onSlotListViewStationDoubleClicked(const QModelIndex &index);
    void listViewStationUpdate();

private:
    QStandardItemModel *m_pCommDevModelObj = NULL;
    QStandardItemModel *m_pStationObj = NULL;
    ListViewEx *m_pListViewCommDevObj = NULL;
    QString m_szItemName = "";
private:
    Ui::DevModleManagerWin *ui;
};

#endif // DEVMODLEMANAGERWIN_H

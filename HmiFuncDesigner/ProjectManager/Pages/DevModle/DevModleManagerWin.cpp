#include "DevModleManagerWin.h"
#include "ui_DevModleManagerWin.h"
#include "newcomdevicedialog.h"
#include "DevModleDialog/DevModleDialog.h"
#include "qsoftcore.h"
#include "qprojectcore.h"
#include "../../Public/userevent.h"
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QKeySequence>
#include <QContextMenuEvent>
#include <QFile>
#include "DevModleDialog/StationDialog.h"

DevModleManagerWin::DevModleManagerWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DevModleManagerWin)
{
    ui->setupUi(this);

    m_pCommDevModelObj = new QStandardItemModel(this);
    ui->treeView->setModel(m_pCommDevModelObj);

    m_pStationObj = new QStandardItemModel(this);
    ui->treeView_2->setModel(m_pStationObj);

    // 设置自定义右键菜单策略
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    // 连接右键菜单信号到槽函数
    connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &DevModleManagerWin::contextMenuEventSlot);
    // 连接双击信号到槽函数
    QObject::connect(ui->treeView, &QTreeView::doubleClicked, this,&DevModleManagerWin::onSlotListViewProjectDoubleClicked);

    connect(ui->newStation, &QToolButton::clicked, this, &DevModleManagerWin::onSlotNewStation);

    ui->treeView_2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView_2, &QTreeView::customContextMenuRequested, this, &DevModleManagerWin::contextMenuEventSlotStation);
    QObject::connect(ui->treeView_2, &QTreeView::doubleClicked, this,&DevModleManagerWin::onSlotListViewStationDoubleClicked);

    listViewUpdate();
}

DevModleManagerWin::~DevModleManagerWin()
{
    m_pCommDevModelObj->deleteLater();
    delete ui;
}

void DevModleManagerWin::listViewUISetting()
{
}


void DevModleManagerWin::listViewUpdate()
{
    listViewDevModleUpdate();
    listViewNetDeviceUpdate();
    listViewStationUpdate();
}

/**
 * @brief DevModleManagerWin::listViewDevModleUpdate
 * @details 所有通讯设备列表视图
 */
void DevModleManagerWin::listViewDevModleUpdate()
{
    m_pCommDevModelObj->clear();

    QStandardItem *pNewNetDevice = new QStandardItem(QIcon(":/images/pj_net.png"), tr("新建网络设备"));
    pNewNetDevice->setEditable(false);
    pNewNetDevice->setData(QString("NewNetDevice").toUpper(), Qt::UserRole + 1);
    m_pCommDevModelObj->appendRow(pNewNetDevice);

    //m_pCommDevModelObj->appendRow(pNewOPCDevice);

    ////////////////////////////////////////////////////////////////////////////

    DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    for(int i = 0; i < deviceInfo.m_listDevModleInfoObject.count(); i++) {
        DevModleInfoObject *pObj = deviceInfo.m_listDevModleInfoObject.at(i);
        if(pObj->m_deviceType == "DevModle") {
            QStandardItem *pNewNetDevice = new QStandardItem(QIcon(":/images/pj_net.png"), pObj->m_name);
            pNewNetDevice->setEditable(false);
            pNewNetDevice->setData(pObj->m_name, Qt::UserRole + 1);
            m_pCommDevModelObj->appendRow(pNewNetDevice);
        }
    }
}

/**
 * @brief DevModleManagerWin::listViewCOMDeviceUpdate
 * @details 串口通讯设备列表视图
 */
void DevModleManagerWin::listViewCOMDeviceUpdate()
{
    m_pCommDevModelObj->clear();

    QStandardItem *pNewComDevice = new QStandardItem(QIcon(":/images/pj_com.png"), tr("新建串口设备"));
    pNewComDevice->setEditable(false);
    pNewComDevice->setData(QString("NewComDevice").toUpper(), Qt::UserRole + 1);
    m_pCommDevModelObj->appendRow(pNewComDevice);

    DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    for(int i = 0; i < deviceInfo.m_listDevModleInfoObject.count(); i++) {
        DevModleInfoObject *pObj = deviceInfo.m_listDevModleInfoObject.at(i);
        if(pObj->m_deviceType == "COM") {
            QStandardItem *pComDevice = new QStandardItem(QIcon(":/images/pj_com.png"), pObj->m_name);
            pComDevice->setEditable(false);
            pComDevice->setData(pObj->m_name, Qt::UserRole + 1);
            m_pCommDevModelObj->appendRow(pComDevice);
        }
    }
}

/**
 * @brief DevModleManagerWin::listViewNetDeviceUpdate
 * @details 网络通讯设备列表视图
 */
void DevModleManagerWin::listViewNetDeviceUpdate()
{
    m_pCommDevModelObj->clear();

    QStandardItem *pNewNetDevice = new QStandardItem(QIcon(":/images/pj_net.png"), tr("新建设备模型"));
    pNewNetDevice->setEditable(false);
    pNewNetDevice->setData(QString("NewNetDevice").toUpper(), Qt::UserRole + 1);
    m_pCommDevModelObj->appendRow(pNewNetDevice);

    DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    for(int i = 0; i < deviceInfo.m_listDevModleInfoObject.count(); i++) {
        DevModleInfoObject *pObj = deviceInfo.m_listDevModleInfoObject.at(i);
        if(pObj->m_deviceType == "DevModle") {
            QStandardItem *pNetDevice = new QStandardItem(QIcon(":/images/pj_net.png"), pObj->m_name);
            pNetDevice->setEditable(false);
            pNetDevice->setData(pObj->m_name, Qt::UserRole + 1);
            m_pCommDevModelObj->appendRow(pNetDevice);
        }
    }
}


void DevModleManagerWin::listViewStationUpdate()
{
    m_pStationObj->clear();

    DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    for(int i = 0; i < deviceInfo.m_listDevModleInfoObject.count(); i++) {
        DevModleInfoObject *pObj = deviceInfo.m_listDevModleInfoObject.at(i);
        if(pObj->m_deviceType == "Station") {
            QStandardItem *pNetDevice = new QStandardItem(QIcon(":/images/pj_net.png"), pObj->m_name);
            pNetDevice->setEditable(false);
            pNetDevice->setData(pObj->m_name, Qt::UserRole + 1);
            m_pStationObj->appendRow(pNetDevice);
        }
    }
}


void DevModleManagerWin::contextMenuEventSlot(const QPoint &pos)
{
    // 获取右键点击位置的索引
    QModelIndex index = ui->treeView->indexAt(pos);
    if (!index.isValid()) {
        return;  // 如果点击的是空白区域，直接返回
    }

    // 创建上下文菜单
    QMenu contextMenu(this);

    // 修改设备参数动作
    QAction *pModifyAct = new QAction(QIcon(":/images/icon_modify.png"), tr("修改"), this);
    pModifyAct->setStatusTip(tr("修改设备参数"));
    connect(pModifyAct, &QAction::triggered, this, &DevModleManagerWin::onSlotModifyDevice);

    // 删除通讯设备动作
    QAction *pDeleteAct = new QAction(QIcon(":/images/icon_delete.png"), tr("删除"), this);
    pDeleteAct->setStatusTip(tr("删除通讯设备"));
    connect(pDeleteAct, &QAction::triggered, this, &DevModleManagerWin::onSlotDeleteDevice);

    // 添加动作到菜单
    contextMenu.addAction(pModifyAct);
    contextMenu.addAction(pDeleteAct);

    // 在鼠标位置显示菜单
    contextMenu.exec(ui->treeView->viewport()->mapToGlobal(pos));
}

void DevModleManagerWin::contextMenuEventSlotStation(const QPoint &pos)
{
    // 获取右键点击位置的索引
    QModelIndex index = ui->treeView_2->indexAt(pos);
    if (!index.isValid()) {
        return;  // 如果点击的是空白区域，直接返回
    }

    // 创建上下文菜单
    QMenu contextMenu(this);

    // 修改设备参数动作
    QAction *pModifyAct = new QAction(QIcon(":/images/icon_modify.png"), tr("修改"), this);
    pModifyAct->setStatusTip(tr("修改设备参数"));
    connect(pModifyAct, &QAction::triggered, this, &DevModleManagerWin::onSlotModifyStation);

    // 删除通讯设备动作
    QAction *pDeleteAct = new QAction(QIcon(":/images/icon_delete.png"), tr("删除"), this);
    pDeleteAct->setStatusTip(tr("删除通讯设备"));
    connect(pDeleteAct, &QAction::triggered, this, &DevModleManagerWin::onSlotDeleteStation);

    // 添加动作到菜单
    contextMenu.addAction(pModifyAct);
    contextMenu.addAction(pDeleteAct);

    // 在鼠标位置显示菜单
    contextMenu.exec(ui->treeView_2->viewport()->mapToGlobal(pos));
}

/*
* 右键菜单
*/
void DevModleManagerWin::contextMenuEvent(QContextMenuEvent * event)
{

}

/*
* 插槽：新建通讯设备
*/
void DevModleManagerWin::onSlotNewDevice()
{
    if(QSoftCore::getCore()->getProjectCore()->m_szProjName == "") {
        return;
    }

    QList<QStandardItem *> itemList;
    if(m_szItemName == QString("NewNetDevice").toUpper()) { // 网络设备
        itemList = m_pCommDevModelObj->findItems(tr("新建设备模型"));
        if(itemList.size() == 0) {
            return;
        }
        DevModleDialog *pNewNetDeviceDlg = new DevModleDialog(this);
        pNewNetDeviceDlg->load("");
        if(pNewNetDeviceDlg->exec() == QDialog::Accepted) {
            pNewNetDeviceDlg->save("");
        }
    }

    listViewUpdate();
}


/*
* 插槽：修改通讯设备参数
*/
void DevModleManagerWin::onSlotModifyDevice()
{
    QModelIndex idx = ui->treeView->currentIndex();
    if (!idx.isValid()) {
       return;
    }

    QStandardItem *pItemObj = m_pCommDevModelObj->itemFromIndex(idx);
    if(QSoftCore::getCore()->getProjectCore()->m_szProjName == "") {
        return;
    }

    DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    DevModleInfoObject *pObj = deviceInfo.getObjectByName(pItemObj->text());
    if(pObj != NULL) {
        if(pObj->m_deviceType == "DevModle") {
            DevModleDialog *pNewDeviceDlg = new DevModleDialog(this);
            pNewDeviceDlg->load(pObj->m_name);
            pNewDeviceDlg->exec();
            pObj->m_name = pNewDeviceDlg->GetDeviceName();
            pObj->m_deviceName = pNewDeviceDlg->pluginName();
            pNewDeviceDlg->save(pObj->m_name);
        }
    }

    listViewUpdate();
}

void DevModleManagerWin::onSlotModifyStation()
{
    QModelIndex idx = ui->treeView_2->currentIndex();
    if (!idx.isValid()) {
       return;
    }

    QStandardItem *pItemObj = m_pCommDevModelObj->itemFromIndex(idx);
    if(QSoftCore::getCore()->getProjectCore()->m_szProjName == "") {
        return;
    }

    DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    DevModleInfoObject *pObj = deviceInfo.getObjectByName(pItemObj->text());
    if(pObj != NULL) {
        if(pObj->m_deviceType == "Station") {
            StationDialog *pNewStationDlg = new StationDialog(this);
            pNewStationDlg->load(pObj->m_name);
            pNewStationDlg->exec();
            pObj->m_name = pNewStationDlg->GetDeviceName();
            pObj->m_deviceName = pNewStationDlg->pluginName();
            pNewStationDlg->save(pObj->m_name);
        }
    }

    listViewUpdate();
}
/*
* 插槽：删除通讯设备
*/
void DevModleManagerWin::onSlotDeleteDevice()
{
    QModelIndex idx = ui->treeView->currentIndex();
    if (!idx.isValid()) {
       return;
    }
    QStandardItem *pItemObj = m_pCommDevModelObj->itemFromIndex(idx);

    DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    for(int i = 0; i < deviceInfo.m_listDevModleInfoObject.count(); i++) {
        DevModleInfoObject *pObj = deviceInfo.m_listDevModleInfoObject.at(i);
        if(pItemObj->text() == pObj->m_name) {
            deviceInfo.m_listDevModleInfoObject.removeOne(pObj);
            break;
        }
    }

    listViewUpdate();
}

void DevModleManagerWin::onSlotDeleteStation()
{
    QModelIndex idx = ui->treeView_2->currentIndex();
    if (!idx.isValid()) {
       return;
    }
    QStandardItem *pItemObj = m_pCommDevModelObj->itemFromIndex(idx);

    DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    for(int i = 0; i < deviceInfo.m_listDevModleInfoObject.count(); i++) {
        DevModleInfoObject *pObj = deviceInfo.m_listDevModleInfoObject.at(i);
        if(pItemObj->text() == pObj->m_name) {
            deviceInfo.m_listDevModleInfoObject.removeOne(pObj);
            break;
        }
    }

    listViewUpdate();
}

void DevModleManagerWin::onSlotListViewProjectDoubleClicked(const QModelIndex &index)
{
    QStandardItem *pItemObj = m_pCommDevModelObj->itemFromIndex(index);
    if(QSoftCore::getCore()->getProjectCore()->m_szProjName == "") {
        return;
    }
    QString szItemText = pItemObj->data(Qt::UserRole + 1).toString();

    if(szItemText == QString("NewNetDevice").toUpper()) { // 网络设备
        DevModleDialog *pNewNetDeviceDlg = new DevModleDialog(this);
        pNewNetDeviceDlg->load("");
        if(pNewNetDeviceDlg->exec() == QDialog::Accepted) {
            pNewNetDeviceDlg->save("");
        }
    } else {
        DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
        DevModleInfoObject *pObj = deviceInfo.getObjectByName(pItemObj->text());
        if(pObj != NULL) {
           if(pObj->m_deviceType == "DevModle") {
                DevModleDialog *pNewDeviceDlg = new DevModleDialog(this);
                pNewDeviceDlg->load(pObj->m_name);
                pNewDeviceDlg->exec();
                pObj->m_name = pNewDeviceDlg->GetDeviceName();
                pObj->m_deviceName = pNewDeviceDlg->pluginName();
                pNewDeviceDlg->save(pObj->m_name);
            }
        }
    }
    listViewUpdate();
}

void DevModleManagerWin::onSlotListViewStationDoubleClicked(const QModelIndex &index)
{
    QStandardItem *pItemObj = m_pStationObj->itemFromIndex(index);
    if(QSoftCore::getCore()->getProjectCore()->m_szProjName == "") {
        return;
    }

    DevModleInfo &deviceInfo = QSoftCore::getCore()->getProjectCore()->m_devModleInfo;
    DevModleInfoObject *pObj = deviceInfo.getObjectByName(pItemObj->text());
    if(pObj != NULL) {
       if(pObj->m_deviceType == "Station") {
            StationDialog *pNewStaionDlg = new StationDialog(this);
            pNewStaionDlg->load(pObj->m_name);
            pNewStaionDlg->exec();
            pObj->m_name = pNewStaionDlg->GetDeviceName();
            pObj->m_deviceName = pNewStaionDlg->pluginName();
            pNewStaionDlg->save(pObj->m_name);
        }
    }

    listViewUpdate();
}
/*
* 插槽：新建通讯设备
*/
void DevModleManagerWin::onSlotNewStation() 
{

  if (QSoftCore::getCore()->getProjectCore()->m_szProjName == "") {
    return;
  }

  QList<QStandardItem *> itemList;

  StationDialog *pNewStationDlg = new StationDialog(this);
  pNewStationDlg->load("");
  if (pNewStationDlg->exec() == QDialog::Accepted) {
    pNewStationDlg->save("");
  }

  listViewUpdate();
}

bool DevModleManagerWin::event(QEvent *ev)
{
    if(ev->type() == UserEvent::EVT_USER_SHOW_UPDATE) {
        UserEvent *pEvObj = dynamic_cast<UserEvent *>(ev);
        if(pEvObj) {
            m_szItemName = pEvObj->data().toString();
        }
        listViewUpdate();
        return true;
    } else if(ev->type() == UserEvent::EVT_USER_HIDE_UPDATE) {
        return true;
    }
    return QWidget::event(ev);
}


#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QPoint>
#include <QWidget>
#include "SqlInfo.h"
#include <QTcpSocket>
#include <QTcpServer>
#include "FileInfo.h"
#include "UserInfo.h"
#include "GroupInfo.h"
#include <QMouseEvent>
#include <QThreadPool>
#include "srcFile/threadFile/TcpThread.h"
#include "srcFile/threadFile/SqlThread.h"

namespace Ui {
class mainWidget;
}

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

public:
    //初始化界面
    void init_Boundary();
    //初始化Tcp模块
    void init_TcpModule();
    //初始化数据库模块
    void init_SqlModule();
    //获取本机IPV4地址
    QString getLocalIPv4();

protected:
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    //关闭窗口函数
    void on_clos_Btn_clicked();
    //缩小窗口函数
    void on_reduce_Btn_clicked();
    //用户信息按钮
    void on_userinfo_But_clicked();
    //群聊信息窗口
    void on_groupinfo_But_clicked();
    //文件转发信息窗口
    void on_fileinfo_But_clicked();
    //数据库信息窗口
    void on_sqlinfo_But_clicked();
    //初始化链接
    void do_newConnection();

signals:
    //更新数据库对象
    void new_SqlData();

private:
    Ui::mainWidget *ui;
    bool move_Ok;         //是否移动
    QString localIPv4;    //IPv4地址
    QPoint move_point;    //移动的距离
    SqlInfo *SqlInfo_GUI;       //数据库信息窗口
    QTcpServer *tcpServer;      //TCP服务器
    TcpThread *tcp_Thread;      //Tcp线程，获取客户端信息
    SqlThread *sql_Thread;      //Sql线程，获取数据库信息
    FileInfo *FileInfo_GUI;     //文件信息窗口
    UserInfo *UserInfo_GUI;     //用户信息窗口
    GroupInfo *GroupInfo_GUI;   //群聊信息窗口
    int TcpConnect_Number = 0;            //客户端连接数量
    QTcpSocket *tcpSocket = nullptr;      //TCP通讯的Socket
};

#endif // MAINWIDGET_H

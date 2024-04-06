#ifndef LOGON_H
#define LOGON_H

#include <QMovie>
#include <QWidget>
#include <QPainter>
#include <QHostInfo>
#include <QSettings>
#include <QTcpSocket>
#include "UserInfo.h"
#include "Register.h"
#include <QMouseEvent>
#include "SetUp/SetUp.h"
#include "srcFile/SQL.h"
#include "srcFile/USER.h"
#include <QPropertyAnimation>
#include "srcFile/JsonThread.h"
#include <QRegularExpressionValidator>

class QPropertyAnimation;

namespace Ui {
class Logon;
}

//登录界面类
class Logon : public QWidget
{
    Q_OBJECT

public:
    explicit Logon(QWidget *parent = nullptr);
    ~Logon();

public:
    //初始化Tcp模块
    void init_TcpModule();
    //初始化Json模块
    void init_JsonModule(const QString &type = nullptr, const QByteArray &jsondata = nullptr);
    void init_JsonModule(const QString &type = nullptr, const QString &number = nullptr,const QString &data = nullptr);
    //发送消息至服务端
    void sending_toServer(QByteArray jsondata);
    //读取服务端发送的信息
    void read_ServerMessage();
    //处理线程返回的验证信息
    void process_ThreadTest(bool ok);

protected:
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    //连接服务器成功
    void do_connected();
    //读取设置文件
    bool get_Settings();
    //修改设置文件
    bool set_Settings();
    //设置用户信息
    void set_UserInfo();
    //绘制动画
    void set_animation();
    //初始化默认配置
    void init_Settings();
    //验证账号密码输入是否正确
    bool testing_Input();
    //初始化界面
    bool initLogon_Boundary();
    //界面关闭
    void on_clos_Btn_clicked();
    //设置窗口
    void on_setup_Btn_clicked();
    //登录验证
    void on_logon_Btn_clicked();
    //界面缩小
    void on_reduce_Btn_clicked();
    //注册账号
    void on_register_Btn_clicked();
    //加密算法
    void get_encrypt(const QString &str);
    //记住账号
    void on_saved_number_clicked(bool checked);
    //记住密码
    void on_saved_Password_clicked(bool checked);

signals:
    //提示TcpThread线程处理服务端返回的数据
    void process_ServerTest(QByteArray read_Array);

private:
    Ui::Logon *ui;
    bool tcp_Ok;            //是否连接上服务端
    bool move_Ok;           //是否移动
    QString localIPv4;      //IPv4地址
    QPoint move_point;      //移动的距离
    QSettings *settings;    //配置文件
    bool saved_Password;    //是否记住密码
    bool saved_Usernumbe;   //是否记住账号
    QTcpSocket  *tcpClient;         //链接服务器Socket
    QString input_Password;         //输入的密码
    QString input_Usernumber;       //输入的账号
    QString encrypt_Password;       //加密的密码
    JsonThread *json_Thread;        //Json数据处理线程
    QPropertyAnimation *animation;  //登录动画
    QRegularExpressionValidator *usernumber_Validator;    //号码输入验证器
    QRegularExpressionValidator *password_Validator;      //密码输入验证器
};

#endif // LOGON_H

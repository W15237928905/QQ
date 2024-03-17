#ifndef LOGON_H
#define LOGON_H

#include <QMovie>
#include "Setup.h"
#include <QWidget>
#include <QPainter>
#include <QSettings>
#include "UserInfo.h"
#include "Register.h"
#include <QMouseEvent>
#include "srcFile/SQL.h"
#include <QPropertyAnimation>
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

protected:
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    //读取设置文件
    bool get_Settings();
    //修改设置文件
    bool set_Settings();
    //绘制动画
    void set_animation();
    //初始化默认配置
    void init_Settings();
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
    void on_saved_number_clicked(bool &checked);
    //记住密码
    void on_saved_Password_clicked(bool &checked);
    //验证输入
    bool testing_Input(const QString &number,const QString &password);

private:
    Ui::Logon *ui;
    bool move_Ok;           //是否移动
    QPoint move_point;      //移动的距离
    QSettings *settings;    //配置文件
    bool saved_Password;    //是否记住密码
    bool saved_Usernumbe;   //是否记住账号
    QString input_Password;         //输入的密码
    QString input_Usernumber;       //输入的账号
    QString encrypt_Password;       //加密的密码
    QPropertyAnimation *animation;  //登录动画
    QRegularExpressionValidator *usernumber_Validator;    //号码输入验证器
    QRegularExpressionValidator *password_Validator;      //密码输入验证器
};

#endif // LOGON_H

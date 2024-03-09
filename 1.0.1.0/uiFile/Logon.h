#ifndef LOGON_H
#define LOGON_H

#include "Setup.h"
#include "UserInfo.h"
#include "Register.h"
#include "srcFile/SQL.h"

#include <QMovie>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
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

private:
    Ui::Logon *ui;
    QPoint move_point;  //移动的距离
    bool move_Ok;       //是否移动
    QPropertyAnimation *animation;  //登录动画
    QString input_Usernumber;     //输入的账号
    QString input_Password;     //输入的密码
    QRegularExpressionValidator *usernumber_Validator;    //号码输入验证器
    QRegularExpressionValidator *password_Validator;  //密码输入验证器

private slots:
    void on_clos_Btn_clicked();     //界面关闭
    void on_reduce_Btn_clicked();   //界面缩小
    void on_logon_Btn_clicked();    //登录验证
    void on_register_Btn_clicked(); //注册账号
    void set_animation();           //绘制动画
    void on_setup_Btn_clicked();    //设置窗口
    bool testing_Input();           //验证输入
    bool initLogon_Boundary();    //初始化界面

protected:

    virtual void mousePressEvent(QMouseEvent *event) override;   //鼠标点击事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;    //鼠标移动事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override; //鼠标释放事件
};

#endif // LOGON_H

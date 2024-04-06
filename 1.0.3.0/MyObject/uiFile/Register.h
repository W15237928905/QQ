#ifndef REGISTER_H
#define REGISTER_H

#include <QMovie>
#include <QWidget>
#include "Logon.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QIntValidator>
#include "srcFile/SQL.h"
#include <QRegularExpressionValidator>

class QRegularExpressionValidator;
class Logon;

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent);
    explicit Register(QWidget *parent = nullptr,Logon *logon = nullptr);
    ~Register();

protected:
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    //最小化界面函数
    void on_reduce_Btn_clicked();
    //关闭界面函数
    void on_clos_Btn_clicked();
    //立即注册函数
    void on_register_Btn_clicked();
    //选择头像函数
    void on_headimg_Btn_clicked();
    //检测用户输入是否合理
    bool getEdit_InputSecure();
    //初始化界面
    bool initRegister_Boundary();

private:
    Ui::Register *ui;
    bool move_Ok;        //是否移动
    Logon *logon_Copy;   //登录窗口复制对象
    QPoint move_point;   //移动的距离
    QString input_Sex;          //输入的性别
    QString input_Name;         //输入的名字
    QString input_Number;           //输入的号码
    QString input_Password;         //输入的密码
    QRegularExpressionValidator *number_Validator;    //号码输入验证器
    QRegularExpressionValidator *password_Validator;  //密码输入验证器

};

#endif // REGISTER_H

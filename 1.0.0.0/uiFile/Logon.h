#ifndef LOGON_H
#define LOGON_H

#include <QWidget>

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

private slots:
    void on_clos_Btn_clicked();     //界面关闭
    void on_reduce_Btn_clicked();   //界面缩小
    void on_logon_Btn_clicked();    //登录验证
    void on_register_Btn_clicked(); //注册账号

    void on_setup_Btn_clicked();

private:
    Ui::Logon *ui;
    QPoint move_point;  //移动的距离
    bool move_Ok;       //是否移动
    QPropertyAnimation *animation;  //登录动画

protected:

    virtual void mousePressEvent(QMouseEvent *event) override;   //鼠标点击事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;    //鼠标移动事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override; //鼠标释放事件
};

#endif // LOGON_H

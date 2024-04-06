#ifndef USERINFO_H
#define USERINFO_H

#include <QPoint>
#include <QWidget>
#include <QMouseEvent>
#include "SetUp/SetUp.h"
#include <QStackedLayout>
#include "srcFile/USER.h"
#include "modelFile/AiList_Model.h"
#include "modelFile/GroupList_Model.h"
#include "modelFile/FriendList_Model.h"

namespace Ui {
class UserInfo;
}

//用户界面类
class UserInfo : public QWidget
{
    Q_OBJECT

public:
    explicit UserInfo(QWidget *parent = nullptr);
    ~UserInfo();
public slots:
    //更新控件消息
    void new_WindowInfo();

protected:
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    //事件过滤器
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    //初始化界面
    void init_Window();
    //关闭界面函数
    void on_clos_Btn_clicked();
    //最小化界面函数
    void on_reduce_Btn_clicked();
    //设置
    void on_setup_Btn_clicked();

private:
    Ui::UserInfo *ui;
    bool move_Ok;           //是否移动
    SetUp *Setup_GUI;       //设置窗口
    QPoint move_point;      //移动的距离
    QSharedPointer<AiList_Model> AiList;                //消息列表
    QSharedPointer<GroupList_Model> GroupList;          //群聊列表
    QSharedPointer<FriendList_Model> FriendList;        //好友列表
    QSharedPointer<QStackedLayout> Stacked_Layout;      //列表布局

};

#endif // USERINFO_H

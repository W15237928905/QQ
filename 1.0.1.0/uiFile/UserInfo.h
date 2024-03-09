#ifndef USERINFO_H
#define USERINFO_H

#include <QWidget>

class FriendList_Model;
class QStackedLayout;
class GroupList_Model;
class MessageList_Model;

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

private:
    Ui::UserInfo *ui;
    QSharedPointer<FriendList_Model> FriendList;        //好友列表
    QSharedPointer<GroupList_Model> GroupList;          //群聊列表
    QSharedPointer<MessageList_Model> MessageList;      //消息列表
    QSharedPointer<QStackedLayout> Stacked_Layout;      //列表布局
    bool move_Ok;   //是否移动
    QPoint move_point;  //移动的距离

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;      //鼠标点击事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;    //鼠标释放事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;       //鼠标移动事件
    virtual bool eventFilter(QObject *watched, QEvent *event) override;//事件过滤器

private slots:
    void on_clos_Btn_clicked();
    void on_reduce_Btn_clicked();

};

#endif // USERINFO_H

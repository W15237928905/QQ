#ifndef FRIENDCHAT_H
#define FRIENDCHAT_H

#include <QFile>
#include <QWidget>
#include <QScrollBar>
#include <QMouseEvent>
#include <QLayout>
#include "Chatbubble/sendbox.h"

namespace Ui {
class FriendChat;
}

class FriendChat : public QWidget
{
    Q_OBJECT

public:
    explicit FriendChat(QWidget *parent = nullptr);
    ~FriendChat();

public:
    //事件过滤器
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
    //修改好友信息
    void set_FriendInfo(const QString &headPath,const QString &name,const QString &sign);

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
    //Top关闭界面函数
    void on_close_Btntop_clicked();
    //Bottom关闭界面函数
    void on_close_Btnbottom_clicked();
    //消息发送按钮
    void on_sending_Btn_clicked();

private:
    Ui::FriendChat *ui;
    bool move_Ok;       //是否移动
    QPoint move_point;  //移动的距离

};

#endif // FRIENDCHAT_H

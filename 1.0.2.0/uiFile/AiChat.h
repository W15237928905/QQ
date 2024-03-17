#ifndef AICHAT_H
#define AICHAT_H

#include <QFile>
#include <QLayout>
#include <QWidget>
#include <QDateTime>
#include <QScrollBar>
#include <QMouseEvent>
#include <QNetworkInterface>
#include "srcFile/AiThread.h"
#include "Chatbubble/sendbox.h"
#include "Chatbubble/recvbox.h"

namespace Ui {
class AiChat;
}

class AiChat : public QWidget
{
    Q_OBJECT

public:
    explicit AiChat(QWidget *parent = nullptr);
    ~AiChat();

public:
    //事件过滤器
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
    //修改好友信息
    void set_FriendInfo(const QString &headPath,const QString &name,const QString &sign);

private slots:
    //最小化界面函数
    void on_reduce_Btn_clicked();
    //Top关闭界面函数
    void on_close_Btntop_clicked();
    //Bottom关闭界面函数
    void on_close_Btnbottom_clicked();
    //消息发送按钮
    void on_sending_Btn_clicked();
    //处理消息回复
    void get_Aianswer(const QString &response);
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::AiChat *ui;
    bool move_Ok;         //是否移动
    QPoint move_point;    //移动的距离
    AiThread *ai_Thread;  //Ai对话线程
};

#endif // FRIENDCHAT_H

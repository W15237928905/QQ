#ifndef FRIENDCHAT_H
#define FRIENDCHAT_H

#include <QFile>
#include <QWidget>
#include <QLayout>
#include <QScrollBar>
#include <QMouseEvent>
#include "srcFile/USER.h"
#include "uiFile/Emotion/Emotion.h"
#include "uiFile/Chatbubble/Sendbox.h"
#include "uiFile/Chatbubble/Recvbox.h"
#include "srcFile/FileSrc/FileThread.h"
#include "uiFile/Chatbubble/sendFilebox.h"

namespace Ui {
class FriendChat;
}

class FriendChat : public QWidget
{
    Q_OBJECT

public:
    ~FriendChat();
    explicit FriendChat(QWidget *parent = nullptr);
    explicit FriendChat(const QString &name, const QString &sign,
                        const QString &number, const QString headimg,
                        const QString &state, QWidget *parent = nullptr);

////------------------------------------事件模块函数-------------------------------------------------------------
protected:
    //事件过滤器
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;
////------------------------------------界面模块函数-------------------------------------------------------------
public:
    //初始化好友聊天界面
    int init_FriendChatWidget();
    //修改好友信息
    int set_FriendInfo(const QString &headPath,const QString &name,const QString &sign);
private slots:
    //选择传输文件函数
    void on_file_Btn_clicked();
    //最小化界面函数
    void on_reduce_Btn_clicked();
    //消息发送按钮
    void on_sending_Btn_clicked();
    //Top关闭界面函数
    void on_close_Btntop_clicked();
    //Bottom关闭界面函数
    void on_close_Btnbottom_clicked();
    //表情发送
    void sending_Emotion(const QString &imgurl);

private:
    Ui::FriendChat *ui;
    bool move_Ok;       //是否移动
    QPoint move_point;  //移动的距离
    Emotion emotion;    //表情包对象
    sendFilebox *send_File;         //文件发送气泡
    FileThread *file_Conveying;     //文件发送对象

private:
    QString friend_name;    //好友昵称
    QString friend_sign;    //好友个签
    QString friend_state;   //好友状态
    QString friend_number;  //好友账号
    QString friend_headimg; //好友头像
};

#endif // FRIENDCHAT_H

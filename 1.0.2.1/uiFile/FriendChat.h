#ifndef FRIENDCHAT_H
#define FRIENDCHAT_H

#include <QFile>
#include <QWidget>
#include <QLayout>
#include "Emotion.h"
#include <QScrollBar>
#include <QMouseEvent>
#include "Chatbubble/sendbox.h"
#include "srcFile/FileSrc/FileThread.h"
#include "Chatbubble/sendFilebox.h"

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
    //初始化界面
    void initChat_Window();
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
    //消息发送按钮
    void on_sending_Btn_clicked();
    //Top关闭界面函数
    void on_close_Btntop_clicked();
    //Bottom关闭界面函数
    void on_close_Btnbottom_clicked();
    //表情发送
    void sending_Emotion(const QString &imgurl);
    //选择传输文件函数
    void on_file_Btn_clicked();

private:
    Ui::FriendChat *ui;
    bool move_Ok;       //是否移动
    QPoint move_point;  //移动的距离
    Emotion emotion;    //表情包对象
    sendFilebox *send_File;         //文件发送气泡
    FileThread *file_Conveying;     //文件发送对象
};

#endif // FRIENDCHAT_H

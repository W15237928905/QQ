#ifndef GROUPCHAT_H
#define GROUPCHAT_H

#include <QFile>
#include <QWidget>
#include <QScrollBar>
#include <QMouseEvent>

namespace Ui {
class GroupChat;
}

class GroupChat : public QWidget
{
    Q_OBJECT

public:
    ~GroupChat();
    explicit GroupChat(QWidget *parent = nullptr);
    explicit GroupChat(const QString &name, const QString &id,
                       const QString &head_Path, QWidget *parent = nullptr);

////------------------------------------事件模块函数-------------------------------------------------------------
protected:
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;
////------------------------------------界面模块函数-------------------------------------------------------------
public:
    //初始化群聊界面
    int init_GroupChatWidget(const QString &name, const QString &id, const QString &head_Path);
private slots:
    //最小化界面函数
    void on_reduce_Btn_clicked();
    //Top关闭界面函数
    void on_close_Btn_clicked();
    //Bottom关闭界面函数
    void on_close_Btnbottom_clicked();

private:
    Ui::GroupChat *ui;
    bool move_Ok;   //是否移动
    QPoint move_point;  //移动的距离
    QString group_id;      //群聊ID
    QString group_name;    //群聊昵称
    QString group_headimg; //群聊头像
};

#endif // GROUPCHAT_H

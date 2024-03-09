#ifndef FRIENDCHAT_H
#define FRIENDCHAT_H

#include <QWidget>

namespace Ui {
class FriendChat;
}

class FriendChat : public QWidget
{
    Q_OBJECT

public:
    explicit FriendChat(QWidget *parent = nullptr);
    ~FriendChat();

private slots:
    //最小化界面函数
    void on_reduce_Btn_clicked();
    //Top关闭界面函数
    void on_close_Btntop_clicked();
    //Bottom关闭界面函数
    void on_close_Btnbottom_clicked();

private:
    Ui::FriendChat *ui;
    bool move_Ok;   //是否移动
    QPoint move_point;  //移动的距离

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;      //鼠标点击事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;    //鼠标释放事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;       //鼠标移动事件
};

#endif // FRIENDCHAT_H

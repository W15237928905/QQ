#ifndef GROUPCHAT_H
#define GROUPCHAT_H

#include <QWidget>

namespace Ui {
class GroupChat;
}

class GroupChat : public QWidget
{
    Q_OBJECT

public:
    explicit GroupChat(QWidget *parent = nullptr);
    ~GroupChat();

private:
    Ui::GroupChat *ui;
    bool move_Ok;   //是否移动
    QPoint move_point;  //移动的距离

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;      //鼠标点击事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;    //鼠标释放事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;       //鼠标移动事件

private slots:
    void on_reduce_Btn_clicked();       //最小化界面函数
    void on_close_Btn_clicked();        //Top关闭界面函数
    void on_close_Btnbottom_clicked();  //Bottom关闭界面函数
};

#endif // GROUPCHAT_H

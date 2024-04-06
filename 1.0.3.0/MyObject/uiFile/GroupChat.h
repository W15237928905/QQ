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
    explicit GroupChat(QWidget *parent = nullptr);
    ~GroupChat();

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
    void on_close_Btn_clicked();
    //Bottom关闭界面函数
    void on_close_Btnbottom_clicked();

private:
    Ui::GroupChat *ui;
    bool move_Ok;   //是否移动
    QPoint move_point;  //移动的距离
};

#endif // GROUPCHAT_H

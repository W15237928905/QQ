#ifndef RECVBOX_H
#define RECVBOX_H

#include <QWidget>

namespace Ui {
class Recvbox;
}

class Recvbox : public QWidget
{
    Q_OBJECT

public:
    explicit Recvbox(QWidget *parent = nullptr);
    ~Recvbox();

public:
    //设置气泡大小
    int set_RecvSize();
    //返回气泡高度
    int return_RecvHeight();
    //设置发送的文字
    int set_RecvText(QString text);

protected:
    //处理大小变化事件
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::Recvbox *ui;
    int height;
};

#endif // RECVBOX_H

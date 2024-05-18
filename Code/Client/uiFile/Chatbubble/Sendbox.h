#ifndef SENDBOX_H
#define SENDBOX_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class Sendbox;
}

class Sendbox : public QWidget
{
    Q_OBJECT

public:
    explicit Sendbox(QWidget *parent = nullptr);
    ~Sendbox();

public:
    //设置气泡大小
    int set_SendSize();
    //返回气泡高度
    int return_SendHeight();
    //设置发送的文字
    int set_Sendtext(QString text);
    //设置头像
    int set_SendAvatar(const QString &avtarPath);

protected:
    //处理大小变化事件
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::Sendbox *ui;
    int height;         //气泡高度
};



#endif // SENDBOX_H

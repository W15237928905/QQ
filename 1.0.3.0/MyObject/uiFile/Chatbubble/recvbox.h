#ifndef RECVBOX_H
#define RECVBOX_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QString>
#include <QColor>
#include <QPalette>
#include <QPainterPath>
#include <QRegion>
#include <QPaintEngine>

namespace Ui {
class RecvBox;
}

class RecvBox : public QWidget
{
    Q_OBJECT

public:
    explicit RecvBox(QWidget *parent = nullptr);
    ~RecvBox();

public slots:
    //设置气泡消息
    void setText(const QString& text);
    //设置头像
    void setAvatar(const QString &avtarPath);

private:
    Ui::RecvBox *ui;
};

#endif // RECVBOX_H

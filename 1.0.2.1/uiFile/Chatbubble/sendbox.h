#ifndef SENDBOX_H
#define SENDBOX_H

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
class SendBox;
}

class SendBox : public QWidget
{
    Q_OBJECT

public:
    explicit SendBox(QWidget *parent = nullptr);
    ~SendBox();

public:
    //设置气泡文字
    void setText(const QString& text);
    //设置表情
    void setEmotion(const QString& imgurl);
    //设置头像
    void setAvatar(const QString &avtarPath);

private:
    Ui::SendBox *ui;
};

#endif // SENDBOX_H

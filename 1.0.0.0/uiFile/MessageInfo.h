#ifndef MESSAGEINFO_H
#define MESSAGEINFO_H

#include <QWidget>

namespace Ui {
class MessageInfo;
}

class MessageInfo : public QWidget
{
    Q_OBJECT

public:
    explicit MessageInfo(QWidget *parent = nullptr);
    explicit MessageInfo(QString name, QString message, QString head_Path,QString timer,QWidget *parent = nullptr);
    ~MessageInfo();

private:
    Ui::MessageInfo *ui;
};

#endif // MESSAGEINFO_H

#ifndef GROUPINFO_H
#define GROUPINFO_H

#include <QWidget>
#include <QMouseEvent>
#include "uiFile/GroupChat.h"

class GroupChat;

namespace Ui {
class GroupInfo;
}

class GroupInfo : public QWidget
{
    Q_OBJECT

public:
    explicit GroupInfo(QWidget *parent = nullptr);
    explicit GroupInfo(QString name, QString head_Path, QWidget *parent = nullptr);
    ~GroupInfo();

protected:
    //鼠标双击事件
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    Ui::GroupInfo *ui;
    QSharedPointer<GroupChat> Chat;
};

#endif // GROUPINFO_H

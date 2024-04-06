#ifndef FRIENDINFO_H
#define FRIENDINFO_H

#include <QPixmap>
#include <QToolBox>
#include <QMouseEvent>
#include <QStackedLayout>
#include "uiFile/FriendChat.h"

class FriendChat;

namespace Ui {
class FriendInfo;
}

class FriendInfo : public QWidget
{
    Q_OBJECT
public:
    explicit FriendInfo(QWidget *parent = nullptr);
    explicit FriendInfo(QString name, QString sign, QString head_Path,QWidget *parent = nullptr);
    ~FriendInfo();

protected:
    //双击好友显示对话框
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    Ui::FriendInfo *ui;
    QSharedPointer<FriendChat> Chat;

};

#endif // FRIENDINFO_H

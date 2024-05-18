#ifndef FRIENDINFO_H
#define FRIENDINFO_H

#include <QPixmap>
#include <QToolBox>
#include <QMouseEvent>
#include <QStackedLayout>
#include "uiFile/FriendModel/FriendChat.h"

class FriendChat;

namespace Ui {
class FriendInfo;
}

class FriendInfo : public QWidget
{
    Q_OBJECT
public:
    explicit FriendInfo(QWidget *parent = nullptr);
    explicit FriendInfo(const QString &name, const QString &sign,
                        const QString &number, const QString headimg,
                        const QString &state,QWidget *parent = nullptr);
    ~FriendInfo();

public:
    //初始化界面
    void FriendInfoFun_init_Widget(const QString &name, const QString &sign,
                                   const QString &number, const QString headimg,const QString &state);

protected:
    //双击好友显示对话框
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    Ui::FriendInfo *ui;
    QSharedPointer<FriendChat> Chat;

};

#endif // FRIENDINFO_H

#ifndef FRIENDLIST_MODEL_H
#define FRIENDLIST_MODEL_H

#include <QWidget>
#include <QToolBox>
#include <QListWidget>
#include "uiFile/FriendModel/FriendInfo.h"

class FriendList_Model : public QToolBox
{
    Q_OBJECT

public:
    ~FriendList_Model();
    explicit FriendList_Model(QWidget *parent = nullptr);

public:
    //新增分组
    int handle_AddFriendList(const QString &groupname);
    //新增好友
    int handle_AddFriend(const QString &name, const QString &sign,
                         const QString &number, const QString headimg,const QString &state);
    //将好友插入分组
    int handle_FriendInsertlist(QSharedPointer<QListWidget> &List,
                                                    QSharedPointer<FriendInfo> &Friend);

private:
    int len;    //好友个数
    QVector<QSharedPointer<FriendInfo>> FriendInfo_Vector;          //好友信息框容器
    QVector<QSharedPointer<QListWidget>> ListWidget_Vector;         //分组信息框容器

};

#endif // FRIENDLIST_MODEL_H

#ifndef FRIENDLIST_MODEL_H
#define FRIENDLIST_MODEL_H

#include <QToolBox>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QSharedPointer>
#include <QListWidgetItem>
#include "uiFile/FriendInfo.h"

class FriendList_Model : public QToolBox
{
    Q_OBJECT
public:
    explicit FriendList_Model(QWidget *parent = nullptr);
    ~FriendList_Model();

public:
    //新增好友
    bool addFriend(const QString &name,const QString &sign,const QString &head_Path);
    //新增分组
    bool addList(const QString &name);
    //好友插入分组
    bool friend_Insertlist(QSharedPointer<QListWidget> &List,
                           QSharedPointer<FriendInfo> &Friend);
    //多次添加好友或分组
    template <typename Type>
    bool loop_Addvalue(Type &Demo,int &value);

private:
    QVector<QSharedPointer<FriendInfo>> FriendInfo_Vector;          //好友信息框容器
    QVector<QSharedPointer<QListWidget>> ListWidget_Vector;         //分组信息框容器

};

#endif // FRIENDLIST_MODEL_H

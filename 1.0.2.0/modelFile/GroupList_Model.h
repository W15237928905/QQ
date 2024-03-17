#ifndef GROUPLIST_MODEL_H
#define GROUPLIST_MODEL_H

#include <QToolBox>
#include <QObject>
#include <QWidget>
#include <QListWidget>
#include "uiFile/GroupInfo.h"

class GroupList_Model : public QToolBox
{
    Q_OBJECT
public:
    explicit GroupList_Model(QWidget *parent = nullptr);
    ~GroupList_Model();

public:
    //新增群组
    bool addGroup(const QString &name,const QString &head_Path);
    //新增分组
    bool addList(const QString &name);
    //群组插入分组
    bool group_Insertlist(QSharedPointer<QListWidget> &List,
                           QSharedPointer<GroupInfo> &Group);
    //多次添加好友或分组
    template <typename Type>
    bool loop_Addvalue(Type &Demo,int &value);

private:
    QVector<QSharedPointer<GroupInfo>> GroupInfo_Vector;            //群组信息框容器
    QVector<QSharedPointer<QListWidget>> ListWidget_Vector;         //分组信息框容器
};

#endif // GROUPLIST_MODEL_H

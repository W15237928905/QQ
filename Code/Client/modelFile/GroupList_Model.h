#ifndef GROUPLIST_MODEL_H
#define GROUPLIST_MODEL_H

#include <QWidget>
#include <QToolBox>
#include <QListWidget>
#include "uiFile/GroupModel/GroupInfo.h"

class GroupList_Model : public QToolBox
{
    Q_OBJECT

public:
    ~GroupList_Model();
    explicit GroupList_Model(QWidget *parent = nullptr);

public:
    //新增分组
    int handle_AddGroupList(const QString &name);
    //群组插入分组
    int handle_GroupInsertList(QSharedPointer<QListWidget> &List,
                                                  QSharedPointer<GroupInfo> &Group);
    //新增群组
    int handle_AddGroup(const QString &name,const QString &id,
                                           const QString &head_Path);

private:
    int len;    //群聊个数
    QVector<QSharedPointer<GroupInfo>> GroupInfo_Vector;            //群组信息框容器
    QVector<QSharedPointer<QListWidget>> ListWidget_Vector;         //分组信息框容器
};

#endif // GROUPLIST_MODEL_H

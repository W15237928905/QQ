#ifndef AILIST_MODEL_H
#define AILIST_MODEL_H

#include <QWidget>
#include <QToolBox>
#include <QListWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include "uiFile/AiInfo.h"

class AiList_Model : public QToolBox
{
    Q_OBJECT
public:
    explicit AiList_Model(QWidget *parent = nullptr);
    //新增消息
    bool addMessage(const QString &name,const QString &message, const QString &head_Path,const QString &timer);
    //新增分组
    bool addList(const QString &name);
    //消息插入分组
    bool Message_Insertlist(QSharedPointer<QListWidget> &List,
                          QSharedPointer<AiInfo> &Message);
private:
    QVector<QSharedPointer<AiInfo>> MessageInfo_Vector;            //消息信息框容器
    QVector<QSharedPointer<QListWidget>> ListWidget_Vector;         //分组信息框容器
};

#endif // AILIST_MODEL_H

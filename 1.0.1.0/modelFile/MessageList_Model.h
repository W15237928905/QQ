#ifndef MESSAGELIST_MODEL_H
#define MESSAGELIST_MODEL_H

#include <QToolBox>
#include <QWidget>
#include <QListWidget>
#include "uiFile/MessageInfo.h"

class MessageList_Model : public QToolBox
{
    Q_OBJECT
public:
    explicit MessageList_Model(QWidget *parent = nullptr);
    //新增消息
    bool addMessage(QString name, QString message, QString head_Path,QString timer);
    //新增分组
    bool addList(QString name);
    //消息插入分组
    bool Message_Insertlist(QSharedPointer<QListWidget> List,
                          QSharedPointer<MessageInfo> Message);
private:
    QVector<QSharedPointer<MessageInfo>> MessageInfo_Vector;            //消息信息框容器
    QVector<QSharedPointer<QListWidget>> ListWidget_Vector;         //分组信息框容器
};

#endif // MESSAGELIST_MODEL_H

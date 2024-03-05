#include "MessageList_Model.h"
#include "uiFile/MessageInfo.h"

#include <QListWidget>
#include <QListWidgetItem>

MessageList_Model::MessageList_Model(QWidget *parent)
    :QToolBox(parent)
{
    addMessage("小野","你好，新用户",":/new/user/user/touxiang01.jpg","2021/2/26");
    addMessage("小Q","你好，新用户",":/new/user/user/touxiang02.jpg","2021/2/26");
    addList("已读");
    Message_Insertlist(ListWidget_Vector[0],MessageInfo_Vector[0]);
    Message_Insertlist(ListWidget_Vector[0],MessageInfo_Vector[1]);
    addMessage("Wild_Pointer","你好，世界",":/new/user/user/My.jpg","2021/2/26");
    addList("未读");
    Message_Insertlist(ListWidget_Vector[1],MessageInfo_Vector[2]);
}

/*  新增消息
 *  name：名字    head_Path：头像路径
*/
bool MessageList_Model::addMessage(QString name, QString message, QString head_Path,QString timer)
{
    QSharedPointer<MessageInfo> Demo(new MessageInfo(name,message,head_Path,timer)); //使用智能指针托管
    MessageInfo_Vector.append(Demo);
    return true;
}

/*  新增分组
 *  name：分组名称
*/
bool MessageList_Model::addList(QString name)
{
    QSharedPointer<QListWidget> Demo(new QListWidget);   //使用智能指针托管
    ListWidget_Vector.append(Demo);
    this->addItem(Demo.data(),name);
    return true;
}

/*  消息插入分组
 *  List：指定分组容器   Message：指定消息容器
*/
bool MessageList_Model::Message_Insertlist(QSharedPointer<QListWidget> List, QSharedPointer<MessageInfo> Message)
{
    QListWidgetItem *Item = new QListWidgetItem();  //新建替换的Item
    Item->setSizeHint(QSize(270, 65));
    List->addItem(Item);                       //分组中添加Item
    List->setItemWidget(Item, Message.data());         //修改Item为自定义样式(Message)
}

#include "AiList_Model.h"

AiList_Model::AiList_Model(QWidget *parent)
    :QToolBox(parent)
{
    addMessage("智能机器人","你好!用户,请跟我聊聊吧！",":/new/user/user/Ai_Logn.png","2021/2/26");
    addList("当前");
    Message_Insertlist(ListWidget_Vector[0],MessageInfo_Vector[0]);
}

/*  新增消息
 *  name：名字    message：消息   head_Path：头像路径    timer：时间
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool AiList_Model::addMessage(const QString &name,const QString &message, const QString &head_Path,const QString &timer)
{
    QSharedPointer<AiInfo> Demo(new AiInfo(name,message,head_Path,timer)); //使用智能指针托管
    MessageInfo_Vector.append(Demo);
    return true;
}

/*  新增分组
 *  name：分组名称
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool AiList_Model::addList(const QString &name)
{
    QSharedPointer<QListWidget> Demo(new QListWidget);   //使用智能指针托管
    ListWidget_Vector.append(Demo);
    this->addItem(Demo.data(),name);
    return true;
}

/*  消息插入分组
 *  List：指定分组容器   Message：指定消息容器
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool AiList_Model::Message_Insertlist(QSharedPointer<QListWidget> &List, QSharedPointer<AiInfo> &Message)
{
    QListWidgetItem *Item = new QListWidgetItem();  //新建替换的Item
    Item->setSizeHint(QSize(270, 65));
    List->addItem(Item);                       //分组中添加Item
    List->setItemWidget(Item, Message.data());         //修改Item为自定义样式(Message)
}

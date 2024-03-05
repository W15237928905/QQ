#include "FriendList_Model.h"
#include "uiFile/FriendInfo.h"
#include <QSharedPointer>
#include <QListWidgetItem>
#include <QListWidget>
#include <QVBoxLayout>

FriendList_Model::FriendList_Model(QWidget *parent)
    :QToolBox(parent)
{
    addFriend("Wild_Pointer","人生唯一确定的就是不确定的人生",":/new/user/user/My.jpg");
    addList("好友");
    friend_Insertlist(ListWidget_Vector[0],FriendInfo_Vector[0]);
    addFriend("Wild_Pointer2","人生唯一确定的就是不确定的人生",":/new/user/user/My.jpg");
    addList("陌生人");
    friend_Insertlist(ListWidget_Vector[1],FriendInfo_Vector[1]);

}

/*  新增好友
 *  name：名字    sign：个性签名   head_Path：头像路径
*/
bool FriendList_Model::addFriend(QString name, QString sign, QString head_Path)
{
    QSharedPointer<FriendInfo> Demo(new FriendInfo(name,sign,head_Path)); //使用智能指针托管
    FriendInfo_Vector.append(Demo);
    return true;
}

/*  新增分组
 *  name：分组名称
*/
bool FriendList_Model::addList(QString name)
{
    QSharedPointer<QListWidget> Demo(new QListWidget);   //使用智能指针托管
    ListWidget_Vector.append(Demo);
    this->addItem(Demo.data(),name);
    return true;
}

/*  好友插入分组
 *  List：指定分组容器   Friend：指定好友容器
*/
bool FriendList_Model::friend_Insertlist(QSharedPointer<QListWidget> List,
                                         QSharedPointer<FriendInfo> Friend)
{
    QListWidgetItem *Item = new QListWidgetItem();  //新建替换的Item
    Item->setSizeHint(QSize(270, 65));
    List->addItem(Item);                       //分组中添加Item
    List->setItemWidget(Item, Friend.data());         //修改Item为自定义样式(FriendInfo)
}

/*  多次添加好友或分组
*   Demp：添加元素     value：个数
*/
template<typename Type>
bool FriendList_Model::loop_Addvalue(Type Demo,int value)
{

}

#include "FriendList_Model.h"

FriendList_Model::FriendList_Model(QWidget *parent)
    :QToolBox(parent)
{
    //初始化对象
    len = 0;
    handle_AddFriendList("好友");
}

FriendList_Model::~FriendList_Model()
{

}

/*  新增好友
 *  name：好友昵称    sign：好友个签   number：好友账号   headimg：好友头像
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int FriendList_Model::handle_AddFriend(const QString &name, const QString &sign,
                                 const QString &number, const QString headimg,const QString &state)
{
    QSharedPointer<FriendInfo> Demo(new FriendInfo(name,sign,number,headimg,state)); //使用智能指针托管
    FriendInfo_Vector.append(Demo);
    handle_FriendInsertlist(ListWidget_Vector[0],FriendInfo_Vector[len]);
    ++len;
    return 1;
}

/*  新增分组
 *  groupname：分组名称
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int FriendList_Model::handle_AddFriendList(const QString &groupname)
{
    QSharedPointer<QListWidget> Demo(new QListWidget);   //使用智能指针托管
    ListWidget_Vector.append(Demo);
    this->addItem(Demo.data(),groupname);
    return 1;
}

/*  将好友插入分组
 *  fist：指定分组容器    friendinfo：好友信息
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int FriendList_Model::handle_FriendInsertlist(QSharedPointer<QListWidget> &list,
                                                             QSharedPointer<FriendInfo> &friendinfo)
{
    QListWidgetItem *item = new QListWidgetItem();//新建替换的Item
    item->setSizeHint(QSize(270, 85));
    list->addItem(item);
    list->setItemWidget(item, friendinfo.data()); //修改Item为自定义样式(FriendInfo)
    this->update();
    return 1;
}


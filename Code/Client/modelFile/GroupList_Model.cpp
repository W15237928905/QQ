#include "GroupList_Model.h"

GroupList_Model::GroupList_Model(QWidget *parent)
    :QToolBox(parent)
{
    //初始化对象
    len = 0;
    handle_AddGroupList("加入的群聊");
}

GroupList_Model::~GroupList_Model()
{

}

/*  新增群组
 *  name：名字    id：群聊ID    head_Path：头像路径
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int GroupList_Model::handle_AddGroup(const QString &name,const QString &id,
                                                        const QString &head_Path)
{
    QSharedPointer<GroupInfo> Demo(new GroupInfo(name,id,head_Path));  //使用智能指针托管
    GroupInfo_Vector.append(Demo);
    handle_GroupInsertList(ListWidget_Vector[0],GroupInfo_Vector[len]);
    ++len;
    return 1;
}

/*  新增分组
 *  name：分组名称
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int GroupList_Model::handle_AddGroupList(const QString &name)
{
    QSharedPointer<QListWidget> Demo(new QListWidget);   //使用智能指针托管
    ListWidget_Vector.append(Demo);
    this->addItem(Demo.data(),name);
    return 1;
}

/*  群组插入分组
 *  List：指定分组容器   Group：指定好友容器
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int GroupList_Model::handle_GroupInsertList(QSharedPointer<QListWidget> &List,
                                       QSharedPointer<GroupInfo> &Group)
{
    QListWidgetItem *Item = new QListWidgetItem();//新建替换的Item
    Item->setSizeHint(QSize(270, 30));
    List->addItem(Item);                          //分组中添加Item
    List->setItemWidget(Item, Group.data());      //修改Item为自定义样式(GroupInfo)
    return 1;
}


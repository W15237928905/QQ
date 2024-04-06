#include "GroupList_Model.h"

GroupList_Model::GroupList_Model(QWidget *parent)
    :QToolBox(parent)
{
    addGroup("群聊1",":/new/user/user/touxiang01.jpg");
    addList("创建的群聊");
    group_Insertlist(ListWidget_Vector[0],GroupInfo_Vector[0]);
    addGroup("群聊2",":/new/user/user/touxiang01.jpg");
    addList("加入的群聊");
    group_Insertlist(ListWidget_Vector[1],GroupInfo_Vector[1]);
}

GroupList_Model::~GroupList_Model()
{

}

/*  新增群组
 *  name：名字    head_Path：头像路径
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool GroupList_Model::addGroup(const QString &name,const QString &head_Path)
{
    QSharedPointer<GroupInfo> Demo(new GroupInfo(name,head_Path)); //使用智能指针托管
    GroupInfo_Vector.append(Demo);
    return true;
}

/*  新增分组
 *  name：分组名称
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool GroupList_Model::addList(const QString &name)
{
    QSharedPointer<QListWidget> Demo(new QListWidget);   //使用智能指针托管
    ListWidget_Vector.append(Demo);
    this->addItem(Demo.data(),name);
    return true;
}

/*  群组插入分组
 *  List：指定分组容器   Group：指定好友容器
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool GroupList_Model::group_Insertlist(QSharedPointer<QListWidget> &List,
                                       QSharedPointer<GroupInfo> &Group)
{
    QListWidgetItem *Item = new QListWidgetItem();  //新建替换的Item
    Item->setSizeHint(QSize(270, 30));
    List->addItem(Item);                       //分组中添加Item
    List->setItemWidget(Item, Group.data());         //修改Item为自定义样式(GroupInfo)
}

/*  多次添加好友或分组
 *  Demp：添加元素     value：个数
 *  时间：2024/03/14   作者：Wild_Pointer
*/
template<typename Type>
bool GroupList_Model::loop_Addvalue(Type &Demo, int &value)
{

}

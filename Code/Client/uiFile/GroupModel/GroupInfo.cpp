#include "GroupInfo.h"
#include "ui_GroupInfo.h"

GroupInfo::GroupInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupInfo)
{
    ui->setupUi(this);
}

GroupInfo::GroupInfo(const QString &name, const QString &id,
                     const QString &head_Path, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupInfo)
{
    ui->setupUi(this);

    //初始化界面
    init_GroupInfoWidget(name,id,head_Path);
}


GroupInfo::~GroupInfo()
{
    delete ui;
}

////---------------------------------------事件操作函数-------------------------------------------------------
/*  鼠标双击事件
 *  event：事件
 *  返回值：void
*/
void GroupInfo::mouseDoubleClickEvent(QMouseEvent *event)
{
    Chat.data()->show();
    event->accept();
}

////---------------------------------------界面操作函数--------------------------------------------------------
/*  初始化群聊信息界面
 *  name：群聊昵称    id：群聊ID    head_Path：群聊头像
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int GroupInfo::init_GroupInfoWidget(const QString &name, const QString &id, const QString &head_Path)
{
    //初始化参数
    Chat = QSharedPointer<GroupChat>(new GroupChat(name,id,head_Path));

    //设置头像大小自适应
    ui->Image->setScaledContents(true);

    //初始化姓名，个性签名，头像
    ui->groupName_Lab->setText(name);
    QPixmap originalPixmap(head_Path);
    originalPixmap = originalPixmap.scaled(ui->Image->width(),
                                           ui->Image->height(), Qt::KeepAspectRatio);
    ui->Image->setPixmap(originalPixmap);
    return 1;
}

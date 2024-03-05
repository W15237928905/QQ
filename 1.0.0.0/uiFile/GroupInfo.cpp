#include "GroupInfo.h"
#include "ui_GroupInfo.h"
#include "uiFile/GroupChat.h"

#include <QMouseEvent>

GroupInfo::GroupInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupInfo)
{
    ui->setupUi(this);
}

GroupInfo::GroupInfo(QString name, QString head_Path,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupInfo)
{
    ui->setupUi(this);

    //初始化参数
    Chat = QSharedPointer<GroupChat>(new GroupChat());

    //设置头像大小自适应
    ui->Image->setScaledContents(true);

    //初始化姓名，个性签名，头像
    ui->groupName_Lab->setText(name);
    QPixmap originalPixmap(head_Path);
    originalPixmap = originalPixmap.scaled(ui->Image->width(),
                                           ui->Image->height(), Qt::KeepAspectRatio);
    ui->Image->setPixmap(originalPixmap);

}

GroupInfo::~GroupInfo()
{
    delete ui;
}

//鼠标双击事件
void GroupInfo::mouseDoubleClickEvent(QMouseEvent *event)
{
    Chat.data()->show();
    event->accept();
}

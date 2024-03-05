#include "FriendInfo.h"
#include "ui_FriendInfo.h"
#include "modelFile/FriendList_Model.h"
#include "uiFile/FriendChat.h"
#include <QPixmap>
#include <QStackedLayout>
#include <QMouseEvent>

FriendInfo::FriendInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendInfo)
{
    ui->setupUi(this);
    //初始化参数
    Chat = QSharedPointer<FriendChat>(new FriendChat());
    //设置头像大小自适应
    ui->userHead_Lab->setScaledContents(true);
}

FriendInfo::FriendInfo(QString name, QString sign, QString head_Path,QWidget *parent):
    QWidget(parent),
    ui(new Ui::FriendInfo)
{
    ui->setupUi(this);
    //初始化参数
    Chat = QSharedPointer<FriendChat>(new FriendChat());

    //设置头像大小自适应
    ui->userHead_Lab->setScaledContents(true);

    //初始化姓名，个性签名，头像
    ui->userName_Lab->setText(name);
    ui->userSign_Lab->setText(sign);
    QPixmap originalPixmap(head_Path);
    originalPixmap = originalPixmap.scaled(ui->userHead_Lab->width(),
                                           ui->userHead_Lab->height(), Qt::KeepAspectRatio);
    ui->userHead_Lab->setPixmap(originalPixmap);

}

FriendInfo::~FriendInfo()
{
    delete ui;
}

/*  双击好友显示对话框
 *  event：事件
*/
void FriendInfo::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug("FriendInfo::mouseDoubleClickEvent");
    Chat.data()->show();
    event->accept();

}

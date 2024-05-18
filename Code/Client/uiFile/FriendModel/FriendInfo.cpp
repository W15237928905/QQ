#include "FriendInfo.h"
#include "ui_FriendInfo.h"

FriendInfo::FriendInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendInfo)
{
    ui->setupUi(this);
}

FriendInfo::FriendInfo(const QString &name, const QString &sign,
                       const QString &number, const QString headimg,
                       const QString &state,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendInfo)
{
    ui->setupUi(this);

    //初始化界面
    FriendInfoFun_init_Widget(name,sign,number,headimg,state);
}

FriendInfo::~FriendInfo()
{
    delete ui;
}

////---------------------------------------事件操作函数-------------------------------------------------------
/*  双击好友显示对话框
 *  event：事件
 *  返回值：void
*/
void FriendInfo::mouseDoubleClickEvent(QMouseEvent *event)
{
    Chat.data()->show();
    event->accept();
}

////---------------------------------------界面操作函数--------------------------------------------------------
/*  初始化界面
 *  name：优化昵称    sign：用户个签    number：用户账号    headimg：用户头像    state：用户状态
 *  返回值：void
*/
void FriendInfo::FriendInfoFun_init_Widget(const QString &name, const QString &sign,
                                           const QString &number, const QString headimg,const QString &state)
{
    //初始化参数
    Chat = QSharedPointer<FriendChat>(new FriendChat(name,sign,number,headimg,state));

    //设置头像大小自适应
    ui->userHead_Lab->setScaledContents(true);

    //初始化姓名，个签，账号，头像
    ui->userName_Lab->setText(name);
    ui->userSign_Lab->setText(sign);
    ui->userNumber_Lab->setText(number);
    QPixmap originalPixmap(headimg);
    originalPixmap = originalPixmap.scaled(ui->userHead_Lab->width(),
                                           ui->userHead_Lab->height(), Qt::KeepAspectRatio);
    ui->userHead_Lab->setPixmap(originalPixmap);

    if(state == "1"){   //设置头像状态样式
        ui->userHead_Lab->setStyleSheet("border: 2px solid green;");
    }
    else{
        ui->userHead_Lab->setStyleSheet("border: 2px solid black;");
    }
}

#include "AiInfo.h"
#include "ui_AiInfo.h"

AiInfo::AiInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AiInfo)
{
    ui->setupUi(this);
}

AiInfo::AiInfo(QString name, QString message, QString head_Path, QString timer, QWidget *parent):
    QWidget(parent),
    ui(new Ui::AiInfo)
{

    ui->setupUi(this);

    //初始化参数
    Chat = QSharedPointer<AiChat>(new AiChat());

    //设置头像大小自适应
    ui->Image_Lab->setScaledContents(true);

    //初始化姓名，个性签名，头像
    ui->userName_Lab->setText(name);
    ui->userMessage_Lab->setText(message);
    ui->timer_Lab->setText(timer);
    QPixmap originalPixmap(head_Path);
    originalPixmap = originalPixmap.scaled(ui->Image_Lab->width(),
                                           ui->Image_Lab->height(), Qt::KeepAspectRatio);
    ui->Image_Lab->setPixmap(originalPixmap);
}

AiInfo::~AiInfo()
{
    delete ui;
}

/*  双击机器人显示对话框
 *  event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void AiInfo::mouseDoubleClickEvent(QMouseEvent *event)
{
    Chat.data()->set_FriendInfo(":/new/user/user/Ai_Logn.png","智能机器人","你好！我是你专属聊天机器人");
    Chat.data()->show();
    event->accept();
}

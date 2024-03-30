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
    ui->aiName_Lab->setText(my_AI.get_AiInfo("Name"));
    ui->aiSign_Lab->setText(my_AI.get_AiInfo("Sign"));
    QPixmap originalPixmap(head_Path);
    originalPixmap = originalPixmap.scaled(ui->Image_Lab->width(),
                                           ui->Image_Lab->height(), Qt::KeepAspectRatio);
    ui->Image_Lab->setPixmap(originalPixmap);

    connect(&my_AI, AI::new_AI,this,AiInfo::new_WindowInfo);
}

AiInfo::~AiInfo()
{
    delete ui;
}

/*  设置窗口消息 
 *  时间：2024/03/24   作者：Wild_Pointer
*/
void AiInfo::new_WindowInfo()
{
    //设置参数
    ui->aiName_Lab->setText(my_AI.get_AiInfo("Name"));
    ui->aiSign_Lab->setText(my_AI.get_AiInfo("Sign"));
}

/*  双击机器人显示对话框
 *  event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void AiInfo::mouseDoubleClickEvent(QMouseEvent *event)
{
    Chat.data()->set_FriendInfo(":/new/user/user/Ai_Logn.png",
                                my_AI.get_AiInfo("Name"),
                                my_AI.get_AiInfo("Sign"));
    Chat.data()->show();
    event->accept();
}

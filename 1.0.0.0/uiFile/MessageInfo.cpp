#include "MessageInfo.h"
#include "ui_MessageInfo.h"

MessageInfo::MessageInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageInfo)
{
    ui->setupUi(this);
}

MessageInfo::MessageInfo(QString name, QString message, QString head_Path, QString timer, QWidget *parent):
    QWidget(parent),
    ui(new Ui::MessageInfo)
{
    ui->setupUi(this);

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

MessageInfo::~MessageInfo()
{
    delete ui;
}

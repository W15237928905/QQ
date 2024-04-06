#include "sendbox.h"
#include "ui_sendbox.h"

SendBox::SendBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendBox)
{
    ui->setupUi(this);

    //初始化控件属性
    ui->recvmsg_lab->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->recvmsg_lab->setWordWrap(true);
    ui->Img_lab->setScaledContents(true);
    ui->recvmsg_lab->setScaledContents(true);
}

SendBox::~SendBox()
{
    delete ui;
}

/*  设置头像
 *  avtarPath：头像路径
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void SendBox::setAvatar(const QString &avtarPath)
{
    QPixmap pixmap(avtarPath);
    pixmap = pixmap.scaled(ui->Img_lab->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap roundPixmap(ui->Img_lab->size());
    roundPixmap.fill(Qt::transparent);
    QPainter painter(&roundPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(roundPixmap.rect());
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(0, 0, pixmap);
    ui->Img_lab->setPixmap(roundPixmap);
}

/*  设置气泡消息
 *  text：消息
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void SendBox::setText(const QString& text)
{
    ui->recvmsg_lab->setText(text);
}

/*  设置表情
 *  imgurl：表情地址
 *  时间：2024/03/20   作者：Wild_Pointer
*/
void SendBox::setEmotion(const QString &imgurl)
{
    QPixmap Emotion(imgurl);
    Emotion = Emotion.scaled(ui->recvmsg_lab->width(),
                             ui->recvmsg_lab->height(), Qt::KeepAspectRatio);
    ui->recvmsg_lab->setPixmap(Emotion);
}

#include "recvbox.h"
#include "ui_recvbox.h"

RecvBox::RecvBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecvBox)
{
    ui->setupUi(this);

    //初始化控件属性
    ui->friend_Recvmsg->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->friend_Recvmsg->setWordWrap(true);
    ui->friend_Img->setScaledContents(true);
}

RecvBox::~RecvBox()
{
    delete ui;
}

/*  设置头像
 *  avtarPath：头像路径
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void RecvBox::setAvatar(const QString &avtarPath)
{
    ui->friend_Img->setWordWrap(true);
    QPixmap pixmap(avtarPath);
    pixmap = pixmap.scaled(ui->friend_Img->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap roundPixmap(ui->friend_Img->size());
    roundPixmap.fill(Qt::transparent);
    QPainter painter(&roundPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(roundPixmap.rect());
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(0, 0, pixmap);
    ui->friend_Img->setPixmap(roundPixmap);
}

/*  设置气泡消息
 *  text：消息
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void RecvBox::setText(const QString &text)
{
    ui->friend_Recvmsg->setText(text);
}

#include "Sendbox.h"
#include "ui_Sendbox.h"

Sendbox::Sendbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sendbox)
{
    ui->setupUi(this);

    connect(ui->user_Recvmsg,&QTextEdit::textChanged,this,&Sendbox::set_SendSize);
}

Sendbox::~Sendbox()
{
    delete ui;
}

/*  设置发送的文字
 *  text：文字
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int Sendbox::set_Sendtext(QString text)
{
    ui->user_Recvmsg->setText(text);
    height = ui->user_Recvmsg->height();
    resize(50, return_SendHeight()); // 调整 QWidget 的大小
    ui->widget->resize(50,return_SendHeight());
    return 1;
}


/*  设置气泡大小
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int Sendbox::set_SendSize()
{
    QTextDocument* doc = ui->user_Recvmsg->document();
    QTextEdit* textEdit = ui->user_Recvmsg;

    //textEdit内的document和边框的距离
    QMargins margins = textEdit->contentsMargins();
    doc->adjustSize();
    textEdit->setFixedWidth(doc->size().width()+margins.left()+margins.right());
    textEdit->setFixedHeight(doc->size().height()+margins.top()+margins.bottom());
    return 1;
}

/*  返回气泡高度
 *  返回值int：气泡高度
*/
int Sendbox::return_SendHeight()
{
    return height;
}

/*  设置头像
 *  avtarPath：头像路径
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int Sendbox::set_SendAvatar(const QString &avtarPath)
{
    QPixmap pixmap(avtarPath);
    pixmap = pixmap.scaled(ui->img_lab->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap roundPixmap(ui->img_lab->size());
    roundPixmap.fill(Qt::transparent);
    QPainter painter(&roundPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(roundPixmap.rect());
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(0, 0, pixmap);
    ui->img_lab->setPixmap(roundPixmap);
    return 1;
}

/*  处理大小变化事件
 *  event：事件
 *  返回值：void
*/
void Sendbox::resizeEvent(QResizeEvent *event)
{
    set_SendSize();
}




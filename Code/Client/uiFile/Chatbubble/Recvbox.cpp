#include "Recvbox.h"
#include "ui_Recvbox.h"

Recvbox::Recvbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Recvbox)
{
    ui->setupUi(this);

    connect(ui->friend_Recvmsg,&QTextEdit::textChanged,this,&Recvbox::set_RecvSize);
}

Recvbox::~Recvbox()
{
    delete ui;
}

/*  设置发送的文字
 *  text：文字
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int Recvbox::set_RecvText(QString text)
{
    ui->friend_Recvmsg->setText(text);
    height = ui->friend_Recvmsg->height();
    resize(50, return_RecvHeight()); // 调整 QWidget 的大小
    ui->widget->resize(50,return_RecvHeight());
    return 1;
}

/*  设置气泡大小
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int Recvbox::set_RecvSize()
{
    QTextDocument* doc = ui->friend_Recvmsg->document();
    QTextEdit* textEdit = ui->friend_Recvmsg;

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
int Recvbox::return_RecvHeight()
{
    return height;
}

/*  处理大小变化事件
 *  event：事件
 *  返回值：void
*/
void Recvbox::resizeEvent(QResizeEvent *event)
{
    set_RecvSize();
}

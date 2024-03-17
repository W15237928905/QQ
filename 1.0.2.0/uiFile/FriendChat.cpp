#include "FriendChat.h"
#include "ui_FriendChat.h"

FriendChat::FriendChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendChat)
{
    ui->setupUi(this);

    ui->text_scrollArea->setLayout(new QVBoxLayout());
    ui->text_Widget->setLayout(new QVBoxLayout());

    //设置头像大小自适应
    ui->FriendHead->setScaledContents(true);

    //控件间距离
    ui->text_scrollArea->layout()->setSpacing(10);
    ui->text_Edit->setWordWrapMode(QTextOption::WrapAnywhere);


    //设置界面透明与去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);

    QFile file(":/new/qss/qssFile/scrollbar.qss");
    file.open(QFile::ReadOnly);
    ui->text_scrollArea->verticalScrollBar()->setStyleSheet(file.readAll());

    //注册事件过滤器
    ui->text_scrollArea->installEventFilter(this);//滚动区域
    ui->text_Widget->installEventFilter(this);//窗口容器

}

FriendChat::~FriendChat()
{
    delete ui;
}


/*  事件过滤器
 *  watched：对象    event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool FriendChat::eventFilter(QObject *watched, QEvent *event)
{
    //设置滚动条永远保持底部
    static int nHeight = 0;
    if (dynamic_cast<QScrollArea*>(watched) == ui->text_scrollArea)
    {
        if (event->type() == QEvent::Resize)
        {
            nHeight = ui->text_scrollArea->height();//记录滚动窗口高度
            return false;
        }
    }
    else if (dynamic_cast<QWidget*>(watched) == ui->text_Widget)
    {
        if (event->type() == QEvent::Resize)
        {
            int nDif = ui->text_Widget->height() - nHeight;
            if (nDif>0)
            {//容器高度大于滚动区域，此时就需要滚动条
                QScrollBar* pVScrollBar = ui->text_scrollArea->verticalScrollBar();
                pVScrollBar->setMaximum(nDif);//设置最大值
                pVScrollBar->setValue(nDif);//将当前值设置成最大值
                return false;
            }
        }
    }
}

/*  最小化界面函数
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void FriendChat::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

/*  Top关闭界面函数
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void FriendChat::on_close_Btntop_clicked()
{
    this->close();
}

/*  Bottom关闭界面函数
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void FriendChat::on_close_Btnbottom_clicked()
{
    this->close();
}

/*  鼠标点击事件
 *  event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void FriendChat::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        move_Ok = true;
        this->setMouseTracking(true);   //开启鼠标追踪
        move_point = event->pos();      //获取鼠标位置
    }
}

/*  鼠标释放事件
 *  event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void FriendChat::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

/*  鼠标移动事件
 *  event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void FriendChat::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

/*  消息发送按钮
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void FriendChat::on_sending_Btn_clicked()
{
    QString text = ui->text_Edit->toPlainText();
    qDebug() << text;
    SendBox *sendbox = new SendBox(ui->text_scrollArea);

    ui->text_Widget->layout()->addWidget(sendbox);

    sendbox->setAvatar(":/new/user/user/My.jpg");

    if(!text.isEmpty())
        sendbox->setText(text);

    ui->text_Edit->clear();
}

/*  修改好友信息
 *  headPath：头像路径   name：好友昵称   sign：好友个性签名
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void FriendChat::set_FriendInfo(const QString &headPath,const QString &name,const QString &sign)
{
    //设置头像
    QPixmap Img(headPath);
    Img = Img.scaled(ui->FriendHead->width(),
                     ui->FriendHead->height(), Qt::KeepAspectRatio);
    ui->FriendHead->setPixmap(Img);

    //设置昵称
    ui->FriendName->setText(name);

    //设置好友个性签名
    ui->FriendSign->setText(sign);
}


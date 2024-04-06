#include "AiChat.h"
#include "ui_AiChat.h"

AiChat::AiChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AiChat)
{
    ui->setupUi(this);

    //设置控件布局
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

    connect(&my_AI, AI::new_AI,this,AiChat::new_WindowInfo);
}

AiChat::~AiChat()
{
    delete ui;
}

/*  事件过滤器
 *  watched：对象    event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool AiChat::eventFilter(QObject *watched, QEvent *event)
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
void AiChat::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

/*  Top关闭界面函数
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void AiChat::on_close_Btntop_clicked()
{
    this->close();
}

/*  Bottom关闭界面函数
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void AiChat::on_close_Btnbottom_clicked()
{
    this->close();
}

/*  鼠标点击事件
 *  event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void AiChat::mousePressEvent(QMouseEvent *event)
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
void AiChat::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}


/*  鼠标移动事件
 *  event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void AiChat::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

/*  消息发送按钮
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void AiChat::on_sending_Btn_clicked()
{
    //获取输入的文本
    QString text = ui->text_Edit->toPlainText();

    //初始化气泡并输出
    SendBox *sendbox = new SendBox(ui->text_scrollArea);
    ui->text_Widget->layout()->addWidget(sendbox);
    sendbox->setAvatar(":/new/user/user/My.jpg");
    sendbox->setText(text);

    //清空文本输入框
    ui->text_Edit->clear();

    //设置文本并启动线程
    if(my_NETWORK.inspect_KeyandSecret()){
        ai_Thread = new AiThread(my_NETWORK.set_EnquireText(text));
        connect(ai_Thread,SIGNAL(getAnswer(const QString)),this,SLOT(get_Aianswer(const QString)));
        QThreadPool::globalInstance()->start(ai_Thread);
    }
}

/*  处理消息回复
 *  response：回复的消息文本
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void AiChat::get_Aianswer(const QString &response)
{
    //初始化气泡并输出
    RecvBox *recvbox = new RecvBox(ui->text_scrollArea);
    ui->text_Widget->layout()->addWidget(recvbox);
    recvbox->setAvatar(":/new/user/user/Ai_Logn.png");
    recvbox->setText(response);
}


/*  修改机器人信息
 *  headPath：头像路径   name：好友昵称   sign：好友个性签名
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void AiChat::set_FriendInfo(const QString &headPath,const QString &name,const QString &sign)
{
    //设置头像
    QPixmap Img(headPath);
    Img = Img.scaled(ui->FriendHead->width(),
                     ui->FriendHead->height(), Qt::KeepAspectRatio);
    ui->FriendHead->setPixmap(Img);

    //设置昵称
    ui->FriendName->setText(my_AI.get_AiInfo("Name"));

    //设置好友个性签名
    ui->FriendSign->setText(my_AI.get_AiInfo("Sign"));
}

/*  设置窗口消息
 *  时间：2024/03/24   作者：Wild_Pointer
*/
void AiChat::new_WindowInfo()
{
    //设置参数
    ui->FriendName->setText(my_AI.get_AiInfo("Name"));
    ui->FriendSign->setText(my_AI.get_AiInfo("Sign"));
}




#include "FriendChat.h"
#include "ui_FriendChat.h"

FriendChat::FriendChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendChat)
{
    ui->setupUi(this);

    //初始化界面
    initChat_Window();

    connect(&emotion,SIGNAL(imgurl(QString)),this,SLOT(sending_Emotion(QString)));
}

FriendChat::~FriendChat()
{
    delete send_File;
    delete file_Conveying;
    delete ui;
}


/*  事件过滤器
 *  watched：对象    event：事件
 *  时间：2024/03/20   作者：Wild_Pointer
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
            return true;
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
                return true;
            }
        }
    }
    else if(event->type() == QEvent::MouseButtonPress && watched==ui->Emotion_lab){
        //转换为鼠标事件
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        int x = mouseEvent->globalPos().x() - 13;
        int y = mouseEvent->globalPos().y() - 125;
        emotion.move(x,y);
        emotion.show();
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

/*  表情发送
 *  imgurl：图片路径
 *  时间：2024/03/20   作者：Wild_Pointer
*/
void FriendChat::sending_Emotion(const QString &imgurl)
{
    SendBox *sendbox = new SendBox(ui->text_scrollArea);
    sendbox->setAvatar(":/new/user/user/My.jpg");
    ui->text_Widget->layout()->addWidget(sendbox);
    sendbox->setEmotion(imgurl);
}

/*  鼠标点击事件
 *  event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void FriendChat::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "鼠标点击事件";
    if(event->button() == Qt::LeftButton){
        emotion.hide();
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

/*  初始化界面
 *  时间：2024/03/24   作者：Wild_Pointer
*/
void FriendChat::initChat_Window()
{
    //初始化对象
    file_Conveying = new FileThread(this);

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
    ui->text_scrollArea->installEventFilter(this);  //滚动区域
    ui->text_Widget->installEventFilter(this);      //窗口容器
    ui->Emotion_lab->installEventFilter(this);      //表情
}

/*  选择传输文件函数
 *  时间：2024/03/24   作者：Wild_Pointer
*/
void FriendChat::on_file_Btn_clicked()
{

    if(file_Conveying->get_FilePath()){
        send_File = new sendFilebox(ui->text_scrollArea);
        qint64 Size = file_Conveying->get_UserSizeinfo("Size");
        send_File->set_FileInfo(file_Conveying->get_UserStrinfo("Name"),Size);
        ui->text_Widget->layout()->addWidget(send_File);

    }
}


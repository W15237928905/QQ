#include "FriendChat.h"
#include "ui_FriendChat.h"

FriendChat::FriendChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendChat)
{
    ui->setupUi(this);
}

FriendChat::FriendChat(const QString &name, const QString &sign,
                       const QString &number, const QString headimg,
                       const QString &state, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendChat)
{
    ui->setupUi(this);

    //初始化对象
    friend_name = name;    //好友昵称
    friend_sign = sign;    //好友个签
    friend_state = state;  //好友状态
    friend_number = number;   //好友账号
    friend_headimg = headimg; //好友头像

    init_FriendChatWidget();    //初始化界面
}

FriendChat::~FriendChat()
{
    delete send_File;
    delete file_Conveying;
    delete ui;
}

////---------------------------------------事件模块函数-------------------------------------------------------
/*  事件过滤器
 *  watched：对象    event：事件
 *  返回值：bool
*/
bool FriendChat::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress && watched==ui->Emotion_lab){
        //转换为鼠标事件
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        int x = mouseEvent->globalPos().x() - 13;
        int y = mouseEvent->globalPos().y() - 125;
        emotion.move(x,y);
        emotion.show();
    }
}

/*  鼠标点击事件
 *  event：事件
 *  返回值：void
*/
void FriendChat::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        emotion.hide();
        move_Ok = true;
        this->setMouseTracking(true);   //开启鼠标追踪
        move_point = event->pos();      //获取鼠标位置
    }
}

/*  鼠标释放事件
 *  event：事件
 *  返回值：void
*/
void FriendChat::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

/*  鼠标移动事件
 *  event：事件
 *  返回值：void
*/
void FriendChat::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

////---------------------------------------界面模块函数------------------------------------------------------
/*  初始化好友聊天界面
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int FriendChat::init_FriendChatWidget()
{
    //初始化对象
    file_Conveying = new FileThread(this);

    //初始化属性
    ui->FriendHead->setScaledContents(true);    //设置头像大小自适应
    setWindowFlags(Qt::WindowType::FramelessWindowHint);    //设置界面透明与去掉边框
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);   //设置listWidget关闭选中
    ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); //设置listWidget为以像素大小进行移动

    //初始化控件对象
    ui->FriendName->setText(friend_name);
    ui->FriendSign->setText(friend_sign);
    ui->FriendNumber->setText(friend_number);
    QPixmap originalPixmap(friend_headimg);
    originalPixmap = originalPixmap.scaled(ui->FriendHead->width(),
                                           ui->FriendHead->height(), Qt::KeepAspectRatio);
    ui->FriendHead->setPixmap(originalPixmap);

    //初始化样式表
    QFile file(":/new/qss/qssFile/scrollbar.qss");
    file.open(QFile::ReadOnly);
    ui->listWidget->verticalScrollBar()->setStyleSheet(file.readAll()); //设置listWidet对象样式
    if(friend_state == "1"){        //设置头像状态样式
        ui->FriendHead->setStyleSheet("border: 2px solid green;");
    }
    else{
        ui->FriendHead->setStyleSheet("border: 2px solid black;");
    }

    ui->Emotion_lab->installEventFilter(this);  //初始化事件过滤器
    connect(&emotion,SIGNAL(imgurl(QString)),this,SLOT(sending_Emotion(QString)));    //发送表情
    return 1;
}

/*  修改好友信息
 *  headPath：头像路径   name：好友昵称   sign：好友个性签名
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int FriendChat::set_FriendInfo(const QString &headPath,const QString &name,const QString &sign)
{
    QPixmap Img(headPath);
    Img = Img.scaled(ui->FriendHead->width(),
                     ui->FriendHead->height(), Qt::KeepAspectRatio);
    ui->FriendHead->setPixmap(Img); //设置头像
    ui->FriendName->setText(name);  //设置昵称
    ui->FriendSign->setText(sign);  //设置好友个性签名
    return 1;
}

/*  表情发送
 *  imgurl：图片路径
 *  返回值：void
*/
void FriendChat::sending_Emotion(const QString &imgurl)
{
    /*Sendbox *sendbox = new SendBox(ui->text_scrollArea);
    sendbox->setAvatar(":/new/user/user/My.jpg");
    ui->text_Widget->layout()->addWidget(sendbox);
    sendbox->setEmotion(imgurl);*/
}

/*  消息发送按钮
 *  返回值：void
*/
void FriendChat::on_sending_Btn_clicked()
{
    //初始化气泡并输出
    QListWidgetItem *item=new QListWidgetItem(ui->listWidget);
    Sendbox *send_item=new Sendbox(this);
    send_item->set_Sendtext(ui->text_Edit->toPlainText());
    item->setSizeHint(QSize(200,send_item->return_SendHeight()+50));
    ui->listWidget->setItemWidget(item,send_item);

    send_item->set_SendAvatar(my_USER.get_UserInfo(USER::Headimg));

    //清空文本输入框
    ui->text_Edit->clear();

    //每次更新消息都显示最新的项
    ui->listWidget->setCurrentRow(ui->listWidget->model()->rowCount() - 1);
}

/*  选择传输文件函数
 *  返回值：void
*/
void FriendChat::on_file_Btn_clicked()
{

    /*if(file_Conveying->get_FilePath()){
        send_File = new sendFilebox(ui->text_scrollArea);
        qint64 Size = file_Conveying->get_UserSizeinfo("Size");
        send_File->set_FileInfo(file_Conveying->get_UserStrinfo("Name"),Size);
        ui->text_Widget->layout()->addWidget(send_File);
    }*/
}

/*  最小化界面函数
 *  返回值：void
*/
void FriendChat::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

/*  Top关闭界面函数
 *  返回值：void
*/
void FriendChat::on_close_Btntop_clicked()
{
    this->close();
}

/*  Bottom关闭界面函数
 *  返回值：void
*/
void FriendChat::on_close_Btnbottom_clicked()
{
    this->close();
}

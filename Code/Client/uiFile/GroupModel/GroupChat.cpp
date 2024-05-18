#include "GroupChat.h"
#include "ui_GroupChat.h"

GroupChat::GroupChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupChat)
{
    ui->setupUi(this);
}

GroupChat::GroupChat(const QString &name, const QString &id,
                     const QString &head_Path, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupChat)
{
    ui->setupUi(this);

    //初始化对象
    group_id = id;           //群聊ID
    group_name = name;       //群聊昵称
    group_headimg = head_Path; //群聊头像

    //初始化界面
    init_GroupChatWidget(name,id,head_Path);
}

GroupChat::~GroupChat()
{
    delete ui;
}

////---------------------------------------事件模块函数------------------------------------------------------
/*  鼠标点击事件
 *  event：事件
 *  返回值：void
*/
void GroupChat::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        move_Ok = true;
        this->setMouseTracking(true);   //开启鼠标追踪
        move_point = event->pos();      //获取鼠标位置
    }
}

/*  鼠标释放事件
 *  event：事件
 *  返回值：void
*/
void GroupChat::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

/*  鼠标移动事件
 *  event：事件
 *  返回值：void
*/
void GroupChat::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

////---------------------------------------界面模块函数------------------------------------------------------
/*  初始化聊天界面
 *  name：群聊昵称    id：群聊Id    head_Path：群聊头像
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int GroupChat::init_GroupChatWidget(const QString &name, const QString &id, const QString &head_Path)
{
    setWindowFlags(Qt::WindowType::FramelessWindowHint);    //设置界面透明与去掉边框

    ui->groupID->setText(id);         //初始化群聊Id
    ui->groupName_Lab->setText(name); //初始化群聊昵称
    QPixmap originalPixmap(head_Path);
    originalPixmap = originalPixmap.scaled(ui->headImage_Lab->width(),
                                           ui->headImage_Lab->height(), Qt::KeepAspectRatio);
    ui->headImage_Lab->setPixmap(originalPixmap);//初始化群聊头像

    //初始化样式表
    QFile qssFile(":/new/qss/qssFile/scrollbar.qss");
    qssFile.open(QFile::ReadOnly);
    ui->text_Browser->verticalScrollBar()->setStyleSheet(qssFile.readAll());
}

/*  最小化界面函数
 *  返回值：void
*/
void GroupChat::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

/*  Top关闭界面函数
 *  返回值：void
*/
void GroupChat::on_close_Btn_clicked()
{
    this->close();
}

/*  Bottom关闭界面函数
 *  返回值：void
*/
void GroupChat::on_close_Btnbottom_clicked()
{
    this->close();
}


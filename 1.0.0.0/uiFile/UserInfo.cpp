#include "UserInfo.h"
#include "ui_UserInfo.h"
#include "modelFile/FriendList_Model.h"
#include "modelFile/GroupList_Model.h"
#include "modelFile/MessageList_Model.h"

#include <QStackedLayout>
#include <QMouseEvent>
#include <QPoint>

UserInfo::UserInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInfo)
{
    ui->setupUi(this);
    //初始化参数
    move_Ok = false;
    FriendList =  QSharedPointer<FriendList_Model>(new FriendList_Model(this));
    GroupList =  QSharedPointer<GroupList_Model>(new GroupList_Model(this));
    MessageList =  QSharedPointer<MessageList_Model>(new MessageList_Model(this));
    Stacked_Layout = QSharedPointer<QStackedLayout>(new QStackedLayout());

    //注册事件过滤器
    ui->friend_Lab->installEventFilter(this);
    ui->group_Lab->installEventFilter(this);
    ui->message_Lab->installEventFilter(this);

    //设置界面透明与去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    //设置组件与布局
    Stacked_Layout.data()->addWidget(FriendList.data());
    Stacked_Layout.data()->addWidget(GroupList.data());
    Stacked_Layout.data()->addWidget(MessageList.data());
    ui->Middle->setLayout(Stacked_Layout.data());

}

UserInfo::~UserInfo()
{
    delete ui;
}

//鼠标点击事件
void UserInfo::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        move_Ok = true;
        this->setMouseTracking(true);   //开启鼠标追踪
        move_point = event->pos();      //获取鼠标位置
    }
}

//鼠标释放事件
void UserInfo::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

//鼠标移动事件
void UserInfo::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

//事件过滤器
bool UserInfo::eventFilter(QObject *watched, QEvent *event)
{
    //底部换页函数
    if((event->type()==QEvent::MouseButtonPress) && (watched==ui->friend_Lab)){
        //点击好友标签
        Stacked_Layout->setCurrentIndex(0);
        return true;
    }
    else if((event->type()==QEvent::MouseButtonPress) && (watched==ui->group_Lab)){
        //点击群聊标签
        Stacked_Layout->setCurrentIndex(1);
        return true;
    }
    else if((event->type()==QEvent::MouseButtonPress) && (watched==ui->message_Lab)){
        //点击消息标签
        Stacked_Layout->setCurrentIndex(2);
        return true;
    }
    else{
        return false;
    }
}

//关闭界面函数
void UserInfo::on_clos_Btn_clicked()
{
    this->close();
}

//最小化界面函数
void UserInfo::on_reduce_Btn_clicked()
{
    this->showMinimized();
}


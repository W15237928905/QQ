#include "UserInfo.h"
#include "ui_UserInfo.h"

UserInfo::UserInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInfo)
{
    ui->setupUi(this);

    //初始化参数
    move_Ok = false;
    FriendList =  QSharedPointer<FriendList_Model>(new FriendList_Model(this));
    GroupList =  QSharedPointer<GroupList_Model>(new GroupList_Model(this));
    AiList =  QSharedPointer<AiList_Model>(new AiList_Model(this));
    Stacked_Layout = QSharedPointer<QStackedLayout>(new QStackedLayout());

    //初始化界面
    init_Window();

    connect(&my_USER,&USER::new_USER,this,&UserInfo::new_WindowInfo);
}

UserInfo::~UserInfo()
{
    delete Setup_GUI;
    delete ui;
}

/*  更新控件消息
 *  时间：2024/03/24   作者：Wild_Pointer
*/
#include <QDebug>
void UserInfo::new_WindowInfo()
{
    qDebug() << "new_WindowInfo()";
    QPixmap headimg(my_USER.get_UserInfo("HeadimgPath"));
    ui->userHead_Lab->setPixmap(headimg);
    ui->userName_Lab->setText(my_USER.get_UserInfo("Name"));
    ui->userSign_Lab->setText(my_USER.get_UserInfo("Sign"));
    ui->userNumber_Lab->setText(my_USER.get_UserInfo("Number"));
}

/*  鼠标点击事件
 *  event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void UserInfo::mousePressEvent(QMouseEvent *event)
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
void UserInfo::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

/*  鼠标移动事件
 *  event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void UserInfo::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

/*  事件过滤器
 *  watched：对象    event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
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
    else if((event->type()==QEvent::MouseButtonPress) && (watched==ui->Ai_Lab)){
        //点击消息标签
        Stacked_Layout->setCurrentIndex(2);
        return true;
    }
    else{
        return false;
    }
}

/*  初始化界面
 *  时间：2024/03/23   作者：Wild_Pointer
*/
void UserInfo::init_Window()
{
    //初始化对象
    Setup_GUI = new SetUp();

    //初始化控件
    QPixmap headimg(my_USER.get_UserInfo("HeadimgPath"));
    ui->userHead_Lab->setPixmap(headimg);
    ui->userName_Lab->setText(my_USER.get_UserInfo("Name"));
    ui->userSign_Lab->setText(my_USER.get_UserInfo("Sign"));
    ui->userNumber_Lab->setText(my_USER.get_UserInfo("Number"));

    //注册事件过滤器
    ui->friend_Lab->installEventFilter(this);
    ui->group_Lab->installEventFilter(this);
    ui->Ai_Lab->installEventFilter(this);

    //设置界面透明与去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    //设置组件与布局
    Stacked_Layout.data()->addWidget(FriendList.data());
    Stacked_Layout.data()->addWidget(GroupList.data());
    Stacked_Layout.data()->addWidget(AiList.data());
    ui->Middle->setLayout(Stacked_Layout.data());
}

/*  关闭界面函数
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void UserInfo::on_clos_Btn_clicked()
{
    this->close();
}

/*  最小化界面函数
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void UserInfo::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

/*  设置
 *  时间：2024/03/29   作者：Wild_Pointer
*/
void UserInfo::on_setup_Btn_clicked()
{
    Setup_GUI->show();
}


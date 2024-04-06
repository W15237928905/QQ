#include "mainWidget.h"
#include "ui_mainWidget.h"

mainWidget::mainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);

    //设置界面透明与去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);

    //初始化数据库模块
    init_SqlModule();

    //初始化Tcp模块
    init_TcpModule();


    //初始化界面
    init_Boundary();
}

mainWidget::~mainWidget()
{
    delete ui;
}

//------------------------------------Tcp模块函数------------------------------
//初始化连接
void mainWidget::do_newConnection()
{
    //获取第一个链接的客户端
    tcpSocket = tcpServer->nextPendingConnection();
    TcpConnect_Number +=1;
    tcp_Thread = new TcpThread(tcpSocket,TcpConnect_Number,this);
    connect(tcp_Thread,&TcpThread::ask_ForSqlinEncrypt,sql_Thread,&SqlThread::add_SqkQuery);
    connect(tcp_Thread,&TcpThread::ask_ForSqlinTesting,sql_Thread,&SqlThread::testing_SqlQuery);
    connect(sql_Thread,&SqlThread::return_TestingResult,tcp_Thread,&TcpThread::set_PackageJSoninOperate);

    //启动线程
    QThreadPool::globalInstance()->start(tcp_Thread);
}

//获取本机IPV4地址
QString mainWidget::getLocalIPv4()
{
    QString hostName = QHostInfo::localHostName();
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QString localIP = "";
    QList<QHostAddress> addList = hostInfo.addresses();
    if(addList.isEmpty()){
        return localIP;
    }
    else{
        foreach(const QHostAddress& item,addList){
            if(item.protocol() == QAbstractSocket::IPv4Protocol){
                localIP = item.toString();
                break;
            }
        }
    }
    return localIP;
}

//初始化Tcp模块
void mainWidget::init_TcpModule()
{
    //初始化对象
    tcpSocket = new QTcpSocket;
    tcpServer = new QTcpServer(this);
    connect(tcpServer,&QTcpServer::newConnection,this,&mainWidget::do_newConnection);

    //获取IPv4地址
    localIPv4 = getLocalIPv4();
    ui->IPv4_lab->setText(localIPv4);

    //开始监听
    quint16 prot= 13020;        //监听端口
    tcpServer->listen(QHostAddress::Any,prot);
}

//------------------------------------数据库模块函数------------------------------
//初始化数据库
void mainWidget::init_SqlModule()
{
    sql_Thread = new SqlThread(this);

}

//鼠标点击事件
void mainWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        move_Ok = true;
        this->setMouseTracking(true);   //开启鼠标追踪
        move_point = event->pos();      //获取鼠标位置
    }
}

//------------------------------------界面模块函数------------------------------
//初始化界面
void mainWidget::init_Boundary()
{
    //初始化对象
    UserInfo_GUI = new UserInfo(ui->bottom_Widget);
    SqlInfo_GUI = new SqlInfo(ui->bottom_Widget);
    FileInfo_GUI = new FileInfo(ui->bottom_Widget);
    GroupInfo_GUI = new GroupInfo(ui->bottom_Widget);

    //优先显示用户信息窗口
    UserInfo_GUI->show();
    SqlInfo_GUI->hide();
    FileInfo_GUI->hide();
    GroupInfo_GUI->hide();

}

//鼠标释放事件
void mainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

//鼠标移动事件
void mainWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

//关闭窗口函数
void mainWidget::on_clos_Btn_clicked()
{
    this->close();
}

//缩小窗口函数
void mainWidget::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

//用户信息按钮
void mainWidget::on_userinfo_But_clicked()
{
    //显示用户信息窗口
    UserInfo_GUI->show();

    //关闭其他窗口
    SqlInfo_GUI->hide();
    FileInfo_GUI->hide();
    GroupInfo_GUI->hide();
}

//群聊信息窗口
void mainWidget::on_groupinfo_But_clicked()
{
    //显示群聊信息窗口
    GroupInfo_GUI->show();

    //关闭其他窗口
    SqlInfo_GUI->hide();
    FileInfo_GUI->hide();
    UserInfo_GUI->hide();
}

//文件转发信息窗口
void mainWidget::on_fileinfo_But_clicked()
{
    //显示文件转发信息窗口
    FileInfo_GUI->show();

    //关闭其他窗口
    SqlInfo_GUI->hide();
    UserInfo_GUI->hide();
    GroupInfo_GUI->hide();
}

//数据库信息窗口
void mainWidget::on_sqlinfo_But_clicked()
{
    //显示数据库信息窗口
    SqlInfo_GUI->show();
    emit new_SqlData();

    //关闭其他窗口
    FileInfo_GUI->hide();
    UserInfo_GUI->hide();
    GroupInfo_GUI->hide();
}


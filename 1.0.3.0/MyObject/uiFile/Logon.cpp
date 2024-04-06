#include "Logon.h"
#include "ui_Logon.h"

Logon::Logon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Logon)
{
    ui->setupUi(this);

    //初始化Tcp模块
    init_TcpModule();

    //初始化界面
    initLogon_Boundary();

    //初始化默认配置
    init_Settings();

}

Logon::~Logon()
{
    delete settings;
    delete animation;
    delete usernumber_Validator;
    delete password_Validator;
    delete ui;
}

//------------------------------------Json处理模块函数-------------------------
/*  初始化Json模块
 *  type：操作类型
 *  时间：2024/04/02   作者：Wild_Pointer
*/
void Logon::init_JsonModule(const QString &type,const QString &number, const QString &data)
{
    //服务器通信线程
    json_Thread = new JsonThread(type,number,data);
    connect(json_Thread,&JsonThread::sending_inServer,this,&Logon::sending_toServer);
    connect(json_Thread,&JsonThread::return_TestingMessage,this,&Logon::process_ThreadTest);

    //启动线程
    QThreadPool::globalInstance()->start(json_Thread);
}

//初始化Json模块函数重载
void Logon::init_JsonModule(const QString &type,const QByteArray &jsondata)
{
    //服务器通信线程
    json_Thread = new JsonThread(type,jsondata);
    connect(json_Thread,&JsonThread::sending_inServer,this,&Logon::sending_toServer);
    connect(json_Thread,&JsonThread::return_TestingMessage,this,&Logon::process_ThreadTest);

    //启动线程
    QThreadPool::globalInstance()->start(json_Thread);
}


//------------------------------------Tcp模块函数------------------------------
/*  初始化Tcp模块
 *  时间：2024/04/02   作者：Wild_Pointer
*/
void Logon::init_TcpModule()
{
    //创建socket变量
    tcpClient = new QTcpSocket(this);
    connect(tcpClient,&QTcpSocket::connected,this,&Logon::do_connected);
    connect(tcpClient,&QAbstractSocket::readyRead,this,&Logon::read_ServerMessage);

    //链接服务器
    //tcpClient->connectToHost("127.0.0.1",13020);
}

/*  发送消息至客户端
 *  时间：2024/04/04   作者：Wild_Pointer
*/
void Logon::sending_toServer(QByteArray jsondata)
{
    tcpClient->write(jsondata);
    tcpClient->flush();      //确保消息被发送
}

/*  读取服务端发送的信息
 *  时间：2024/04/04   作者：Wild_Pointer
*/
void Logon::read_ServerMessage(){
    QByteArray read_Array;

    while(tcpClient->canReadLine()){
        read_Array += tcpClient->readLine();
    }

    //定义Json解析线程
    init_JsonModule("read",read_Array);
}

/*  处理线程返回的验证信息
 *  时间：2024/04/04   作者：Wild_Pointer
*/
void Logon::process_ThreadTest(bool ok)
{
    if(ok){
        //记住密码操作
        if(saved_Password){
            //记住密码：把加密的密码上传到服务器
            get_encrypt(input_Password);
            init_JsonModule("set_encrypt",input_Usernumber,encrypt_Password);
        }

        set_UserInfo();     //设置用户信息
        set_Settings();     //更新配置文件
        set_animation();    //登录动画
    }
    else{
        QMessageBox::information(nullptr,"提示","账号或密码错误！",QMessageBox::Ok);
    }
}

/*  连接服务器成功
 *  时间：2024/04/02   作者：Wild_Pointer
*/
void Logon::do_connected()
{
    tcp_Ok = true;
}

//------------------------------------控件函数---------------------------------
/*  关闭界面函数
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Logon::on_clos_Btn_clicked()
{
    this->close();
}

/*  最小化界面函数
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Logon::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

/*  鼠标点击事件
 *  event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Logon::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        move_Ok = true;
        this->setMouseTracking(true);   //开启鼠标追踪
        move_point = event->pos();      //获取鼠标位置
    }
}

/*  鼠标移动事件
 *  event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Logon::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

/*  鼠标释放事件
 *  event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Logon::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

/*  注册账号
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Logon::on_register_Btn_clicked()
{
    Register* Register_GUI = new Register(nullptr,this);
    Register_GUI->show();
}

/*  记住账号
 *  checked：状态位
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Logon::on_saved_number_clicked(bool checked)
{
    saved_Usernumbe = checked;
}


/*  记住密码
 *  checked：状态位
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Logon::on_saved_Password_clicked(bool checked)
{
    saved_Password = checked;
}

/*  验证窗口
 *  number：账号   password：密码
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool Logon::testing_Input()
{
    int pos = 0;
    if(QValidator::Acceptable != usernumber_Validator->validate(input_Usernumber,pos) ||
            input_Usernumber == nullptr){
        //验证号码是否存在且正确
        QMessageBox::information(nullptr,"提示","账号错误!",QMessageBox::Ok);
        return false;
    }
    else if(QValidator::Acceptable != password_Validator->validate(input_Password,pos) ||
            input_Password == nullptr){
        //验证密码是否正确
        QMessageBox::information(nullptr,"提示","密码错误！",QMessageBox::Ok);
        return false;
    }
    else{
        return true;
    }
}

/*  设置
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Logon::on_setup_Btn_clicked()
{
    SetUp *Setup_GUI = new SetUp();
    Setup_GUI->show();
}

/*  初始化登录操作
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Logon::on_logon_Btn_clicked()
{
    if(!tcp_Ok){
        tcpClient->connectToHost("127.0.0.1",13020);
        QMessageBox::information(nullptr,"提示","网络连接失败！",QMessageBox::Ok);
        return;
    }
    //获取输入框内容
    input_Usernumber = ui->usernumber_Box->currentText();
    input_Password = ui->password_Edit->text();

    //验证输入信息
    if(!testing_Input()){
        return;
    }

    //定义Json解析线程
    init_JsonModule("logo",input_Usernumber);

}

/*  设置用户信息
 *  时间：2024/03/23   作者：Wild_Pointer
*/
void Logon::set_UserInfo()
{
    //获取用户信息
    //init_JsonModule("set_encrypt",input_Usernumber,encrypt_Password);
    QString query = QStringLiteral("SELECT * FROM user WHERE number = '%1';").arg(input_Usernumber);
    const QStringList &info = my_SQL.get_SqkQuery(query);
    my_USER.set_UserName(info.at(1));       //设置用户昵称
    my_USER.set_UserNumber(info.at(2));     //设置用户账号
    my_USER.set_UserSex(info.at(4));        //设置用户性别
    my_USER.set_UserSign(info.at(5));       //设置用户个性签名
    my_USER.set_UserHeadimgPath(info.at(6));   //设置用户头像
}

//------------------------------------软件配置设置---------------------------------

/*  读取设置文件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool Logon::get_Settings()
{
    input_Password = settings->value("Password","").toString();              //读取密码
    input_Usernumber = settings->value("Username","").toString();            //读取账号
    encrypt_Password = settings->value("encrypt_Pswd","").toString();        //读取加密的密码
    saved_Password = settings->value("saved_Password",false).toBool();
    saved_Usernumbe = settings->value("saved_Usernumbe",false).toBool();
}

/*  修改设置文件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool Logon::set_Settings()
{
    get_encrypt(input_Password);                            //密码加密
    settings->setValue("Password",input_Password);          //密码
    settings->setValue("Username",input_Usernumber);        //用户名
    settings->setValue("encrypt_Pswd",encrypt_Password);    //加密的密码
    settings->setValue("saved_Password",saved_Password);    //是否保存密码
    settings->setValue("saved_Usernumbe",saved_Usernumbe);  //是否保存账号
    settings->sync();
}

/*  初始化默认配置
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Logon::init_Settings()
{
    //读取配置文件
    get_Settings();

    if(saved_Password){
        //保存密码
        ui->saved_Password->setChecked(saved_Password);
        ui->password_Edit->setText(input_Password);
    }

    if(saved_Usernumbe){
        //保存账号
        ui->saved_number->setChecked(saved_Usernumbe);
        ui->usernumber_Box->addItem(input_Usernumber);
    }
}

/*  加密算法
 *  str：原密码
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Logon::get_encrypt(const QString &str)
{
    QByteArray btArray= str.toLocal8Bit();  //字符串转换为字节数组数据
    QCryptographicHash hash(QCryptographicHash::Md5);  //Md5加密算法
    hash.addData(btArray);  //添加数据到加密哈希值
    QByteArray resultArray = hash.result();  //返回最终的哈希值
    encrypt_Password = resultArray.toHex();       //转换为16进制字符串
}

//------------------------------------界面函数---------------------------------

/*  绘制动画
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Logon::set_animation()
{
    //设置控件不可见
    ui->usernumber_Box->hide();
    ui->password_Edit->hide();
    ui->saved_number->hide();
    ui->saved_Password->hide();
    ui->register_Btn_2->hide();
    ui->logon_Btn->hide();
    ui->register_Btn->hide();
    animation->start();//执行GUI动画

    this->close();
    UserInfo *UserInfo_Widget = new UserInfo();
    UserInfo_Widget->show();
}

/*  初始化界面
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool Logon::initLogon_Boundary()
{
    //初始化参数
    tcp_Ok = false;
    move_Ok = false;
    input_Password = "";
    input_Usernumber = "";
    saved_Password = false;
    saved_Usernumbe = false;

    //设置应用名称
    settings = new QSettings("QQ-Qt", "Wild_Pointer");

    //去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);


    //设置Top中的gif动画
    QMovie *top_Gif = new QMovie(this);
    top_Gif->setFileName(":/new/logo/icons/logo/Top.gif");
    top_Gif->start();
    ui->Top->setMovie(top_Gif);

    //设置username_Box提示
    ui->usernumber_Box->lineEdit()->setPlaceholderText("QQ号码/手机/邮箱");

    //设置user_image为圆形
    QPixmap pixmap(":/new/user/user/My.jpg");
    pixmap = pixmap.scaled(ui->user_image->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap roundPixmap(ui->user_image->size());
    roundPixmap.fill(Qt::transparent);
    QPainter painter(&roundPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(roundPixmap.rect());
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(0, 0, pixmap);
    ui->user_image->setPixmap(roundPixmap);

    //设置登录动画
    animation=new QPropertyAnimation(ui->user_image, "geometry");     //设置user_image的位置大小
    animation->setDuration(400);                        //设置动画完成双击为400毫秒
    animation->setStartValue(QRect(160, 90, 85, 85));  //设置动画初始位置值
    animation->setEndValue(QRect(160, 175, 85, 85));   //设置动画结束位置值

    //初始化输入验证器，限制输入为数值
    usernumber_Validator = new QRegularExpressionValidator(QRegularExpression("\\d{10}"), this);
    password_Validator = new QRegularExpressionValidator(QRegularExpression("[A-Za-z0-9].{10,14}"), this);
    ui->usernumber_Box->setValidator(usernumber_Validator);
    ui->password_Edit->setValidator(password_Validator);
}



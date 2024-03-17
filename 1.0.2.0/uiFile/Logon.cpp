#include "Logon.h"
#include "ui_Logon.h"

Logon::Logon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Logon)
{
    ui->setupUi(this);

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
void Logon::on_saved_number_clicked(bool &checked)
{
    saved_Usernumbe = checked;
}

/*  记住密码
 *  checked：状态位
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Logon::on_saved_Password_clicked(bool &checked)
{
    saved_Password = checked;
}

/*  验证窗口
 *  number：账号   password：密码
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool Logon::testing_Input(const QString &number,const QString &password)
{
    int pos = 0;
    if(QValidator::Acceptable != usernumber_Validator->validate(input_Usernumber,pos) ||
            input_Usernumber == nullptr || !mySql.get_SqlQuery("user", "number",number)){
        //验证号码是否存在且正确
        QMessageBox::information(nullptr,"提示","账号错误或未注册!",QMessageBox::Ok);
        return false;
    }
    else if(QValidator::Acceptable != password_Validator->validate(input_Password,pos) ||
            input_Password == nullptr || !mySql.get_SqlQuery("user", "password",password)){
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
    Setup* Setup_GUI = new Setup();
    Setup_GUI->show();
}

/*  登录验证
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Logon::on_logon_Btn_clicked()
{
    //获取输入框内容
    input_Usernumber = ui->usernumber_Box->currentText();
    input_Password = ui->password_Edit->text();

    if (!testing_Input(input_Usernumber,input_Password)){
        return;
    }
    else if(saved_Password){
        //记住密码：把加密的密码上传到服务器
        get_encrypt(input_Password);
        QString query = QStringLiteral("UPDATE user SET encrypt_Pswd = '%1' WHERE number = '%2';")
                            .arg(encrypt_Password).arg(input_Usernumber);
        qDebug() << query;
        mySql.add_SqkQuery(query);

    }

    set_Settings();     //更新配置文件
    set_animation();    //登录动画
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
    move_Ok = false;
    input_Password = "";
    input_Usernumber = "";
    saved_Password = false;
    saved_Usernumbe = false;

    //设置应用名称
    settings = new QSettings("QQ-Qt", "Wild_Pointer");
    /*settings->setValue("saved_Password",false);    //是否保存密码
    settings->setValue("saved_Usernumbe",false);  //是否保存账号
    settings->sync();*/

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


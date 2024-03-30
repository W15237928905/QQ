#include "Register.h"
#include "ui_Register.h"

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    //初始化界面
    initRegister_Boundary();
}

Register::Register(QWidget *parent, Logon *logon):
    QWidget(parent),
    ui(new Ui::Register),
    logon_Copy(logon)
{
    ui->setupUi(this);

    //关闭登录窗口，初始化注册界面
    logon_Copy->close();
    initRegister_Boundary();
}

Register::~Register()
{
    delete number_Validator;
    delete password_Validator;
    delete ui;
}


/*  鼠标点击事件
 *  event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Register::mousePressEvent(QMouseEvent *event)
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
void Register::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

/*  鼠标移动事件
 *  event：事件
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Register::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

/*  最小化界面函数
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Register::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

/*  关闭界面函数
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Register::on_clos_Btn_clicked()
{
    logon_Copy->show();
    this->close();
}

/*  立即注册函数
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Register::on_register_Btn_clicked()
{
    my_SQL.get_Path();
    if(!getEdit_InputSecure()){
        //检测输入是否合格
        return;
    }
    else if(my_SQL.testing_SqlQuery("user", "number",input_Number)){
        //检测账号是否存在
        QMessageBox::critical(nullptr,"提示！","账号已存在，请重新输入",QMessageBox::Ok);
    }
    else{
        //添加用户
        QString query = QStringLiteral("INSERT INTO user (id, name, number, password, sex, headimg)"
                                       "VALUES ('%1', '%2', '%3', '%4', '%5', '%6')")
                            .arg(my_SQL.get_RowCount("user")+1).arg(input_Name).arg(input_Number)
                            .arg(input_Password).arg(input_Sex).arg("");
        if(my_SQL.add_SqkQuery(query)){
            QMessageBox::information(nullptr,"恭喜！","欢迎您加入QQ大家庭",QMessageBox::Ok);
            logon_Copy->show();
            this->close();
        }
        else{
            QMessageBox::critical(nullptr,"提示！","用户注册失败，请联系管理员",QMessageBox::Ok);
        }
    }
}

/*  检测用户输入是否合理
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool Register::getEdit_InputSecure()
{
    //获取输入框内容
    input_Number = ui->number_Edit->text();
    input_Password = ui->password_Edit->text();
    input_Name = ui->name_Edit->text();
    input_Sex = ui->sex_Box->currentText();

    int pos = 0;
    if(input_Name.isEmpty()){
        //检测昵称
        QMessageBox::information(nullptr,"提示","昵称为空",QMessageBox::Ok);
        return false;
    }
    else if(QValidator::Acceptable != number_Validator->validate(input_Number,pos)){
        //检测账号
        QMessageBox::information(nullptr,"提示","账号不合理!\n号码个数应为：10",QMessageBox::Ok);
        return false;
    }
    else if(QValidator::Acceptable != password_Validator->validate(input_Password,pos)){
        //检测密码
        QMessageBox::information(nullptr,"提示","密码不合理!\n号码个数应为：10-15",QMessageBox::Ok);
        return false;
    }
    else{
        return true;
    }
}

/*  初始化界面
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool Register::initRegister_Boundary()
{
    //初始化对象
    input_Number = "";
    input_Password = "";
    input_Name = "";
    input_Sex = "";

    //设置界面透明与去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);

    //设置backimg_Lab中的gif动画
    QMovie *backimg_Gif = new QMovie(this);
    backimg_Gif->setFileName(":/new/logo/icons/logo/Register_Img.gif");
    backimg_Gif->start();
    ui->backimg_Lab->setScaledContents(true);
    ui->backimg_Lab->setMovie(backimg_Gif);

    //初始化输入验证器，限制输入为数值
    number_Validator = new QRegularExpressionValidator(QRegularExpression("\\d{10}"), this);
    password_Validator = new QRegularExpressionValidator(QRegularExpression("[A-Za-z0-9].{10,14}"), this);
    ui->number_Edit->setValidator(number_Validator);
    ui->password_Edit->setValidator(password_Validator);
}

/*  选择头像函数
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void Register::on_headimg_Btn_clicked()
{
    ui->headimg_Btn->setText("");
    ui->headimg_Btn->setStyleSheet("QPushButton#headimg_Btn{"
                              "border-image: url(:/new/user/user/My.jpg);};");
}


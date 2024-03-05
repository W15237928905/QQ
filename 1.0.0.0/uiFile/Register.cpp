#include "Register.h"
#include "ui_Register.h"

#include <QMovie>
#include<QMouseEvent>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    //设置界面透明与去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);


    //设置backimg_Lab中的gif动画
    QMovie *backimg_Gif = new QMovie(this);
    backimg_Gif->setFileName(":/new/logo/icons/logo/Register_Img.gif");
    backimg_Gif->start();
    ui->backimg_Lab->setScaledContents(true);
    ui->backimg_Lab->setMovie(backimg_Gif);
}

Register::~Register()
{
    delete ui;
}

//鼠标点击事件
void Register::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        move_Ok = true;
        this->setMouseTracking(true);   //开启鼠标追踪
        move_point = event->pos();      //获取鼠标位置
    }
}

//鼠标释放事件
void Register::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

//鼠标移动事件
void Register::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

//最小化界面函数
void Register::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

//关闭界面函数
void Register::on_clos_Btn_clicked()
{
    this->close();
}


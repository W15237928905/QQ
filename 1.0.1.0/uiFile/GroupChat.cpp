#include "GroupChat.h"
#include "ui_GroupChat.h"
#include <QMouseEvent>

GroupChat::GroupChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupChat)
{
    ui->setupUi(this);

    //设置界面透明与去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);

}

GroupChat::~GroupChat()
{
    delete ui;
}

//鼠标点击事件
void GroupChat::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        move_Ok = true;
        this->setMouseTracking(true);   //开启鼠标追踪
        move_point = event->pos();      //获取鼠标位置
    }
}

//鼠标释放事件
void GroupChat::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

//鼠标移动事件
void GroupChat::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

//最小化界面函数
void GroupChat::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

//Top关闭界面函数
void GroupChat::on_close_Btn_clicked()
{
    this->close();
}

//Bottom关闭界面函数
void GroupChat::on_close_Btnbottom_clicked()
{
    this->close();
}


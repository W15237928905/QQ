#ifndef SETUP_H
#define SETUP_H

#include <QMovie>
#include <QWidget>
#include "AiSetup.h"
#include <QMouseEvent>
#include "UserSetup.h"
#include "FileSetup.h"

namespace Ui {
class SetUp;
}

class SetUp : public QWidget
{
    Q_OBJECT

public:
    explicit SetUp(QWidget *parent = nullptr);

    ~SetUp();

protected:
    //初始化界面
    bool initSetUp_Boundary();
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    //关闭界面函数
    void on_clos_Btn_clicked();
    //最小化界面函数
    void on_reduce_Btn_clicked();
    //用户设置界面函数
    void on_userSetup_Btn_clicked();
    //Ai设置界面函数
    void on_AiSetup_Btn_clicked();
    //文件设置界面函数
    void on_fileSetup_Btn_clicked();

private:
    Ui::SetUp *ui;
    bool move_Ok;         //是否移动
    QPoint move_point;    //移动的距离
    AiSetup *AiSetup_GUI;         //Ai设置界面
    UserSetup *UserSetup_GUI;     //用户设置界面
    FileSetup *FileSetup_GUI;     //文件设置界面
};

#endif // SETUP_H

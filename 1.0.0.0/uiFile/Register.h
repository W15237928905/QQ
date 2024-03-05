#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private:
    Ui::Register *ui;
    QPoint move_point;  //移动的距离
    bool move_Ok;       //是否移动

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;      //鼠标点击事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;    //鼠标释放事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;       //鼠标移动事件
private slots:
    void on_reduce_Btn_clicked();
    void on_clos_Btn_clicked();
};

#endif // REGISTER_H

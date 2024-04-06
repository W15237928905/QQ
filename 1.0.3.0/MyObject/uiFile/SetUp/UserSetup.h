#ifndef USERSETUP_H
#define USERSETUP_H

#include <QWidget>
#include <QMessageBox>
#include "srcFile/USER.h"

namespace Ui {
class UserSetup;
}

class UserSetup : public QWidget
{
    Q_OBJECT

public:
    explicit UserSetup(QWidget *parent = nullptr);
    ~UserSetup();

    //设置控件信息
    void set_AssemblyInfo();

public slots:
    //更新控件消息
    void new_WindowInfo();

private slots:
    //确定修改信息
    void on_determine_Btn_clicked();

private:
    Ui::UserSetup *ui;
};

#endif // USERSETUP_H

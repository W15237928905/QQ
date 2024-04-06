#ifndef AISETUP_H
#define AISETUP_H

#include <QWidget>
#include <QMessageBox>
#include "srcFile/AiSrc/AI.h"
#include <QRegularExpressionValidator>

namespace Ui {
class AiSetup;
}

class AiSetup : public QWidget
{
    Q_OBJECT

public:
    explicit AiSetup(QWidget *parent = nullptr);
    ~AiSetup();

    //设置控件信息
    void set_AssemblyInfo();

public slots:
    //更新控件消息
    void new_WindowInfo();

private slots:
    //确定修改信息
    void on_determine_Btn_clicked();

private:
    Ui::AiSetup *ui;
    QRegularExpressionValidator *aiName_Validator;      //Ai名称输入验证器
    QRegularExpressionValidator *aiSign_Validator;      //Ai介绍输入验证器

};

#endif // AISETUP_H

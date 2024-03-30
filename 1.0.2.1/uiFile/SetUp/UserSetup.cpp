#include "UserSetup.h"
#include "ui_UserSetup.h"

UserSetup::UserSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserSetup)
{
    ui->setupUi(this);

    //置控件信息
    set_AssemblyInfo();

    connect(&my_USER,&USER::new_USER,this,&UserSetup::new_WindowInfo);
}

UserSetup::~UserSetup()
{
    delete ui;
}

/*  设置控件信息
 *  时间：2024/03/23   作者：Wild_Pointer
*/
void UserSetup::set_AssemblyInfo()
{
    //设置头像
    QString headimg_Css = QStringLiteral("QPushButton#headimg_Btn{"
                                         "border-image: url(%1);};").arg(my_USER.get_UserInfo("HeadimgPath"));
    ui->headimg_Btn->setStyleSheet(headimg_Css);

    //设置性别
    if(my_USER.get_UserInfo("Sex") == "女"){
        ui->sex_Box->setItemText(0,"女");
        ui->sex_Box->setItemText(1,"男");
    }
    else{
        ui->sex_Box->setItemText(0,"男");
        ui->sex_Box->setItemText(1,"女");
    }
    ui->sex_Box->setCurrentIndex(0);

    //设置账号
    ui->Number_Lab->setText(my_USER.get_UserInfo("Number"));

    //设置昵称
    ui->userName_Edit->setText(my_USER.get_UserInfo("Name"));

    //设置个性签名
    ui->userSign_Edit->setText(my_USER.get_UserInfo("Sign"));
}

/*  更新控件消息
 *  时间：2024/03/24   作者：Wild_Pointer
*/
void UserSetup::new_WindowInfo()
{
    set_AssemblyInfo();
}

/*  确定修改信息
 *  时间：2024/03/23   作者：Wild_Pointer
*/
void UserSetup::on_determine_Btn_clicked()
{
    my_USER.set_AllObject(ui->sex_Box->currentText(),ui->userName_Edit->text(),ui->userSign_Edit->text(),
                          ui->Number_Lab->text(),my_USER.get_UserInfo("HeadimgPath"));

    QMessageBox::information(nullptr,"提示","用户信息设置成功",QMessageBox::Ok);
}


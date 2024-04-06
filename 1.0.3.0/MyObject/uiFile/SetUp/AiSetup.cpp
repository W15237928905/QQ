#include "AiSetup.h"
#include "ui_AiSetup.h"

AiSetup::AiSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AiSetup)
{
    ui->setupUi(this);

    //设置控件信息
    set_AssemblyInfo();

    //初始化验证器
    aiName_Validator = new QRegularExpressionValidator(QRegularExpression("^.{8}$"));
    aiSign_Validator = new QRegularExpressionValidator(QRegularExpression("^.{15}$"));

    //设置验证器
    ui->Ainame_Edit->setValidator(aiName_Validator);
    ui->Aisign_Edit->setValidator(aiSign_Validator);
}

AiSetup::~AiSetup()
{
    delete aiName_Validator;
    delete aiSign_Validator;
    delete ui;
}

/*  设置控件信息
 *  时间：2024/03/23   作者：Wild_Pointer
*/
void AiSetup::set_AssemblyInfo()
{
    //设置控件消息
    ui->Ainame_Edit->setText(my_AI.get_AiInfo("Name"));
    ui->Aisign_Edit->setText(my_AI.get_AiInfo("Sign"));
    ui->APIKey_Edit->setText(my_AI.get_AiInfo("ApiKey"));
    ui->APISecret_Edit->setText(my_AI.get_AiInfo("ApiSecret"));
}

/*  更新控件消息
 *  时间：2024/03/24   作者：Wild_Pointer
*/
void AiSetup::new_WindowInfo()
{
    set_AssemblyInfo();
}

/*  确定修改信息
 *  时间：2024/03/23   作者：Wild_Pointer
*/
void AiSetup::on_determine_Btn_clicked()
{
    my_AI.set_AllObject(ui->Ainame_Edit->text(),ui->Aisign_Edit->text(),
                        ui->APIKey_Edit->text(),ui->APISecret_Edit->text());

    QMessageBox::information(nullptr,"提示","Ai信息设置成功",QMessageBox::Ok);
    new_WindowInfo();
}



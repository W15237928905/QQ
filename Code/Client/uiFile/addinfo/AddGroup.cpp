#include "AddGroup.h"
#include "ui_AddGroup.h"

AddGroup::AddGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddGroup)
{
    ui->setupUi(this);
}

AddGroup::~AddGroup()
{
    delete ui;
}

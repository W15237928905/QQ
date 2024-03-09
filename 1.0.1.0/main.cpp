#include "mainwindow.h"
#include "srcFile/SQL.h"
#include "uiFile/Logon.h"
#include <QApplication>

//全局变量的声明
SQL mySql;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Logon logon_Ui;
    logon_Ui.show();
    /*MainWindow w;
    w.show();*/
    return a.exec();
}

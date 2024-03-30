#include "mainwindow.h"
#include "srcFile/SQL.h"
#include "srcFile/USER.h"
#include "srcFile/HOST.h"
#include "uiFile/Logon.h"
#include <QApplication>
#include "srcFile/AiSrc/AI.h"

//全局变量的声明
AI my_AI;
SQL my_SQL;
USER my_USER;
HOST my_HOST;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Logon logon_Ui;
    logon_Ui.show();
    /*MainWindow w;
    w.show();*/
    return a.exec();
}

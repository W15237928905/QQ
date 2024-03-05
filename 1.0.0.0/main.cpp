#include "mainwindow.h"
#include "uiFile/Logon.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Logon logon_Ui;
    logon_Ui.show();
    /*MainWindow w;
    w.show();*/
    return a.exec();
}

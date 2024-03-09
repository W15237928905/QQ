#include "CustomTimer.h"

CustomTimer::CustomTimer(QObject *parent)
    : QTimer{parent}
{
    logon_Timer = new QTimer();
}

//设置登录界面定时器
void CustomTimer::set_LogonTimer(int msec)
{
    qDebug() << "启动定时器";
    logon_Timer->start(msec);
}

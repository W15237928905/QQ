#ifndef CUSTOMTIMER_H
#define CUSTOMTIMER_H

#include <QTimer>
#include <QObject>
#include <QDebug>

class CustomTimer : public QTimer
{
    Q_OBJECT
public:
    explicit CustomTimer(QObject *parent = nullptr);
    void set_LogonTimer(int msec);      //设置登录界面定时器

private:
    QTimer *logon_Timer;    //登录界面定时器

};

extern CustomTimer Timer;   //声明全局变量

#endif // CUSTOMTIMER_H

#ifndef HOST_H
#define HOST_H

#include <QObject>
#include <QHostInfo>
#include <QHostAddress>

class HOST : public QObject
{
    Q_OBJECT
public:
    explicit HOST();
    ~HOST();

    //获取本机IPv4地址
    void get_HoatIPv4();


private:
    QString Local_HostName;      //本机名
    quint16 Local_HostPort;      //本机端口
    QString Local_HoatIPv4;      //本机IPv4地址
    QHostInfo Local_HostInfo;    //本机信息
};

extern HOST my_HOST;   //声明全局变量

#endif // HOST_H

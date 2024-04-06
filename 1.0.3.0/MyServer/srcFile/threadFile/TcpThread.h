#ifndef TCPTHREAD_H
#define TCPTHREAD_H

#include <QObject>
#include <QHostInfo>
#include <QRunnable>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>

class TcpThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ~TcpThread();
    //线程执行函数
    virtual void run() override;
    explicit TcpThread(QObject *parent = nullptr);
    explicit TcpThread(QTcpSocket *socket,int value,QObject *parent = nullptr);

public:
    //读取缓存区信息
    void onSocketReadyRead();
    //客户端成功连接
    void onClientconnected();
    //执行Json中的操作
    void execute_JsonOperate();
    //客户端断开连接
    void onClientdisconnected();
    //设置传输的Json数据
    void set_PackageJSoninOperate(const QString &data);

signals:
    //申请数据库保存加密信息操作
    void ask_ForSqlinEncrypt(const QString &query);
    //更新连接用户数据
    void new_onClientconnected(int value);
    //更新断开用户数据
    void new_onClientdisconnected(int value);
    //申请数据库验证信息操作
    void ask_ForSqlinTesting(const QString &outside,const QString &list=nullptr,const QString &data=nullptr);

private:
    QString read_type;       //读取到的操作类型字段
    QString read_data;       //读取到的数据字段
    QString read_number;     //读取到的账号字段
    bool isdiscon=false;            //判断客户端是否断开连接
    QJsonObject jsonObject;         //传输的json数据
    int Tcpthread_number = 0;       //客户端编号
    QTcpSocket *Tcpthread_Socket;   //通信对象
};

#endif // TCPTHREAD_H

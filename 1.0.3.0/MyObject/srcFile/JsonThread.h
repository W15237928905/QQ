#ifndef JSONTHREAD_H
#define JSONTHREAD_H

#include <QObject>
#include <QRunnable>
#include <QJsonObject>
#include <QJsonDocument>

class JsonThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ~JsonThread();
    virtual void run() override;
    explicit JsonThread(QObject *parent = nullptr);
    explicit JsonThread(const QString &type = nullptr, const QString &number = nullptr, const QString &data = nullptr, QObject *parent = nullptr);
    explicit JsonThread(const QString &type = nullptr, const QByteArray &jsondata = nullptr, QObject *parent = nullptr);

public:
    //处理服务端返回的Json
    void execute_JsonOperate(QByteArray jsondata);
    //设置传输的Json数据
    QJsonObject set_PackageJSoninOperate(const QString &type, const QString &data, const QString &number);

signals:
    //返回服务器验证信息给主线程处理
    void return_TestingMessage(bool Ok);
    //提示主线程把信息发送给服务端
    void sending_inServer(QByteArray jsondata);

private:
    QString Type;            //Json线程执行的操作类型
    QString read_type;       //读取到的操作类型字段
    QString read_data;       //读取到的数据字段
    QString read_number;     //读取到的账号字段
    QString write_Data;      //写入Json的数据
    QJsonObject jsonObject;      //传输的json数据
    QString user_Number = "";    //登录的账号
    QByteArray json_ByteAray;    //接收到的json数据
};

#endif // JSONTHREAD_H

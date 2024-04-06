#include "TcpThread.h"
#include <QDebug>

TcpThread::TcpThread(QObject *parent)
    : QObject{parent}
    , QRunnable{}
{
    setAutoDelete(true);//线程自动析构

    //初始化对象
    read_type = "";
    read_data = "";
    read_number = "";
}

TcpThread::TcpThread(QTcpSocket *socket, int value, QObject *parent)
    : QObject{parent}
    , QRunnable{}
{
    setAutoDelete(true);//线程自动析构

    //初始化对象
    read_type = "";
    read_data = "";
    read_number = "";
    Tcpthread_number = value;
    Tcpthread_Socket = socket;
}

TcpThread::~TcpThread()
{

}

void TcpThread::run()
{
    connect(Tcpthread_Socket,&QTcpSocket::connected,this,&TcpThread::onClientconnected);
    onClientconnected();
    connect(Tcpthread_Socket,&QAbstractSocket::disconnected,this,&TcpThread::onClientdisconnected);
    connect(Tcpthread_Socket,&QAbstractSocket::readyRead,this,&TcpThread::onSocketReadyRead);
    while(!isdiscon);

}

//客户端成功连接
void TcpThread::onClientconnected()
{
   qDebug()<<"********客户端已连接********";
   qDebug()<<"客户端的id：" +QString::number(Tcpthread_number);
   qDebug()<<"客户端的ip：" + Tcpthread_Socket->peerAddress().toString();
   qDebug()<<"客户端端口号：" + QString::number(Tcpthread_Socket->peerPort());

   emit new_onClientconnected(Tcpthread_number);
}

//客户端断开连接
void TcpThread::onClientdisconnected()
{
    qDebug()<<"客户端断开连接..................";
    Tcpthread_Socket->deleteLater();
    isdiscon=true;

    emit new_onClientdisconnected(Tcpthread_number);
}

//执行Json中的操作
void TcpThread::execute_JsonOperate()
{
    qDebug() << "执行Json中的操作";
    qDebug() << read_type;
    if(read_type == "logo"){
        //发出信号，申请数据库验证操作
        qDebug() << "发出信号，申请数据库验证操作\n";
        emit ask_ForSqlinTesting("user", "number",read_number);
    }
    else if(read_type == "set_encrypt"){
        QString query = QStringLiteral("UPDATE user SET encrypt_Pswd = '%1' WHERE number = '%2';")
                           .arg(read_data).arg(read_number);
        qDebug() << "发出信号，申请数据库添加加密数据\n";
        //发出信号，申请数据库保存加密信息
        emit ask_ForSqlinEncrypt(query);
    }
}

//设置传输的Json数据
void TcpThread::set_PackageJSoninOperate(const QString &data)
{
    //初始化Json对象
    QJsonObject Object;
    Object["type"] = read_type;
    Object["data"] = data;
    Object["number"] = read_number;

    //返回数据
    QJsonDocument jsonDocument(Object);
    QByteArray jsonData = jsonDocument.toJson();
    Tcpthread_Socket->write(jsonData);
    Tcpthread_Socket->flush();
}

//读取客户短消息
void TcpThread::onSocketReadyRead()
{
    QByteArray data_Array;

    while(Tcpthread_Socket->canReadLine()){
        data_Array += Tcpthread_Socket->readLine();
    }

    qDebug() << "接收到的Json" << data_Array;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data_Array);
    QJsonObject jsonObject = jsonDocument.object();

    //从 JSON 对象中提取数据
    read_type = jsonObject["type"].toString();
    read_data = jsonObject["data"].toString();
    read_number = jsonObject["number"].toString();
    qDebug() << read_type;
    execute_JsonOperate();
}


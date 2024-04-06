#include "JsonThread.h"

JsonThread::JsonThread(QObject *parent)
    : QObject{parent}
    , QRunnable{}
{
    //初始化对象
    read_type = "";
    read_data = "";
    read_number = "";

    //线程自动析构
    setAutoDelete(true);
}

JsonThread::JsonThread(const QString &type, const QString &number, const QString &data, QObject *parent)
    : QObject{parent}
    , Type{type}
    , write_Data{data}
    , user_Number{number}
    , QRunnable{}
{
    //初始化对象
    read_type = "";
    read_data = "";
    read_number = "";

    //线程自动析构
    setAutoDelete(true);
}

JsonThread::JsonThread(const QString &type, const QByteArray &jsondata, QObject *parent)
    : QObject{parent}
    , Type{type}
    , json_ByteAray{jsondata}
    , QRunnable{}
{
    //初始化对象
    read_type = "";
    read_data = "";
    read_number = "";

    //线程自动析构
    setAutoDelete(true);
}

JsonThread::~JsonThread()
{

}

/*  设置传输的Json数据
 *  type：操作类型      data：数据      number：账号
 *  时间：2024/04/03   作者：Wild_Pointer
*/
QJsonObject JsonThread::set_PackageJSoninOperate(const QString &type, const QString &data, const QString &number)
{
    //初始化Json对象
    QJsonObject Object;
    Object["type"] = type;
    Object["data"] = data;
    Object["number"] = number;

    jsonObject = Object;
    return jsonObject;
}

/*  处理服务端返回的Json
 *  时间：2024/04/03   作者：Wild_Pointer
*/
void JsonThread::execute_JsonOperate(QByteArray jsondata)
{
    //解析数据
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsondata);
    QJsonObject jsonObject = jsonDocument.object();

    //从 JSON 对象中提取数据
    read_type = jsonObject["type"].toString();
    read_data = jsonObject["data"].toString();
    read_number = jsonObject["number"].toString();

    if(read_data == "True"){
        emit return_TestingMessage(true);
    }
    else{
        emit return_TestingMessage(false);
    }
}

void JsonThread::run()
{
    QJsonDocument jsonDocument;
    if(Type == "logo"){
        //发送登录操作消息
        jsonDocument.setObject(set_PackageJSoninOperate("logo"," ",user_Number));
    }
    else if(Type == "set_encrypt"){
        //发送加密操作信息
        jsonDocument.setObject(set_PackageJSoninOperate("set_encrypt",write_Data,user_Number));
    }
    else if(Type == "read"){
        //解析消息
        execute_JsonOperate(json_ByteAray);
    }

    QByteArray jsonData = jsonDocument.toJson();
    qDebug() << jsonData;
    emit sending_inServer(jsonData);
}

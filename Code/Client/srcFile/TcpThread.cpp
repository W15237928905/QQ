#include "TcpThread.h"
#include <QDebug>

TcpThread::TcpThread(QObject *parent)
    : QObject{parent}
    , QRunnable{}
{
    //线程自动析构
    setAutoDelete(true);
}

TcpThread::TcpThread(QTcpSocket *socket, QObject *parent) :
    QRunnable{},
    QObject{parent},
    server_DataService{socket}
{
    ok = true;   //初始化线程状态
    setAutoDelete(true);  //设置线程自动析构
    isdisconnect = false; //初始化连接服务器状态

    init_TcpConnect();     //初始化TCP链接信号槽
    server_DataService->connectToHost("127.0.0.1",13020);    //链接服务器
}

TcpThread::~TcpThread()
{

}

void TcpThread::run()
{
    while(ok);
}


////-----------------------------------Json模块函数---------------------------------------------------------
/*  处理服务端返回的Json
 *  jsondata：服务端返回的数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_ReturnJsonData(QByteArray jsondata)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsondata);
    QJsonObject jsonObject = jsonDocument.object();
    read_Type = jsonObject["type"].toString();      //获取Json中所含的操作类型

    if(read_Type == "login"){
        //处理登录返回的用户信息
        handle_LoginReturnUserInfo(jsonObject);
    }
    else if(read_Type == "register"){
        //处理用户注册操作返回的信息
        handle_UserRegisterResult(jsonObject);
    }
    else if(read_Type == "encrypt"){
        //处理加密操作返回的信息
        handle_EncryptResult(jsonObject);
    }
    else if(read_Type == "selectFriend"){
        //处理查询好友信息操作返回的信息
        handle_SeleteFriendInfo(jsonObject);
    }
    else if(read_Type == "setAi" || read_Type == "getAi"){
        //处理AI操作返回的信息
        handle_AiResult(jsonObject);
    }
    else if(read_Type == "friendVerify"){
        //处理好友添加请求返回的信息
        handle_FriendVerify(jsonObject);
    }
    else if(read_Type == "return_AddFriendLinkResult"){
        //处理新增好友链接返回的信息
        emit relat_AddFriendLinkResult(jsonObject);
    }
    return 1;
}

////-----------------------------------TCP模块函数---------------------------------------------------------
/*  初始化Tcp链接
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::init_TcpConnect()
{
    //链接服务器成功
    connect(server_DataService,&QTcpSocket::connected,this,&TcpThread::handle_ConnectedSuccess);
    //链接服务器失败
    connect(server_DataService,&QTcpSocket::disconnected,this,&TcpThread::handle_DisConnected);
    //处理接收到的数据
    connect(server_DataService,&QAbstractSocket::readyRead,this,&TcpThread::receive_ServerMessage);
    return 1;
}

/*  关闭线程
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_CloseThread(const QString& number)
{
    //请求更改用户状态为离线
    QJsonObject Json;
    Json.insert("type","exitClient");
    Json.insert("data",number);
    QJsonDocument jsonDoc(Json);
    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Compact);
    sending_ToServer(byteArray);

    ok = false;
    return 1;
}

/*  连接服务器成功
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_ConnectedSuccess()
{
    isdisconnect = true;
    return 1;
}

/*  服务器链接断开
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_DisConnected()
{
    while(!isdisconnect){
        server_DataService->connectToHost("127.0.0.1",13020);    //链接服务器
    }
    return 1;
}

/*  接收服务器发送的信息
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
void TcpThread::receive_ServerMessage()
{
    handle_ReturnJsonData(server_DataService->readAll());   //解析数据
}

/*  发送消息至服务器
 *  jsondata：发送的Json数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/

int TcpThread::sending_ToServer(const QByteArray &jsondata)
{
    if(!isdisconnect){
        server_DataService->connectToHost("127.0.0.1",13020);    //链接服务器
    }
    server_DataService->write(jsondata);
    server_DataService->flush();     //确保消息被发送
    return 1;
}

////-----------------------------------添加好友模块函数------------------------------------------------------
/*  处理查询好友信息操作返回的信息
 *  jsonObject：服务端返回的用户数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_SeleteFriendInfo(const QJsonObject &jsonObject)
{
    QJsonObject dataObject = jsonObject["data"].toObject();
    if(jsonObject["return"].toString() == "True"){
        emit return_AddFriendInfo(jsonObject["code"].toString(), dataObject["friendstate"].toString(),
                                  dataObject["friendname"].toString(), dataObject["friendsex"].toString(),
                                  dataObject["friendsign"].toString(), dataObject["friendnumber"].toString(),
                                  dataObject["friendheadimg"].toString());
        return 1;
    }
    else{
        emit return_AddFriendInfo(jsonObject["code"].toString()," "," "," "," "," "," ");
        return 0;
    }
}

/*  处理好友验证的请求的信息
 *  jsonObject：服务端返回的用户数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_FriendVerify(const QJsonObject &jsonObject)
{
    QJsonObject dataObject = jsonObject["data"].toObject();
    emit return_FriendVerify(dataObject["friendname"].toString(), dataObject["friendsex"].toString(),
                             dataObject["friendsign"].toString(),
                             dataObject["friendnumber"].toString(),
                             dataObject["friendheadimg"].toString());
    return 1;
}

////-----------------------------------AI模块函数-----------------------------------------------------------
/*  处理获取Ai（设置Ai）请求返回的信息
 *  jsonObject：服务端返回的用户数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_AiResult(const QJsonObject &jsonObject)
{
    //获取返回的结果
    QJsonObject dataObject = jsonObject["data"].toObject();
    QString read_APIkey = dataObject["APIkey"].toString();            //读取的APIkey
    QString read_Aisign = dataObject["Aisign"].toString();            //读取的Ai介绍
    QString read_Ainame  = dataObject["Ainame"].toString();           //读取的Ai昵称
    QString read_APIsecret = dataObject["APIsecret"].toString();      //读取的APIsecret

    if(jsonObject["return"].toString()== "True" && read_Type == "setAi"){
        emit return_SetAiResult(true,read_Ainame,read_Aisign,read_APIkey,read_APIsecret);
        return 1;
    }
    else if(jsonObject["return"].toString() == "False"  && read_Type == "setAi"){
        emit return_SetAiResult(false,read_Ainame,read_Aisign,read_APIkey,read_APIsecret);
        return 0;
    }
    else if(jsonObject["return"].toString() == "True"  && read_Type == "getAi"){
        emit return_GetAiResult(true,read_Ainame,read_Aisign,read_APIkey,read_APIsecret);
        return 1;
    }
    else if(jsonObject["return"].toString() == "False"  && read_Type == "getAi"){
        emit return_GetAiResult(false,read_Ainame,read_Aisign,read_APIkey,read_APIsecret);
        return 0;
    }
}

////-----------------------------------加密模块函数-----------------------------------------------------------
/*  处理保存加密请求返回的信息
 *  jsonObject：服务端返回的用户数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_EncryptResult(const QJsonObject &jsonObject)
{
    QString returnData = jsonObject["return"].toString();

    //返回服务器处理加密信息结果给主线程处理
    if(returnData == "True"){
        emit return_SaveEncryptResult(true,"");
        return 1;
    }
    else if(returnData == "False"){
        emit return_SaveEncryptResult(false,"");
        return 0;
    }
}

////-----------------------------------注册模块函数-----------------------------------------------------------
/*  处理注册请求返回的信息
 *  jsonObject：服务端返回的用户数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_UserRegisterResult(const QJsonObject &jsonObject)
{
    QString returnData = jsonObject["return"].toString();

    //注册用户请求结果返回给UserInfo界面处理
    if(returnData == "True"){
        emit return_RegisterResult(true);
        return 1;
    }
    else if(returnData == "False"){
        emit return_RegisterResult(false);
        return 0;
    }
}

////-----------------------------------登录模块函数-----------------------------------------------------------
/*  处理登录返回的信息
 *  jsonObject：服务端返回的用户数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_LoginReturnUserInfo(const QJsonObject &jsonObject)
{
    QString read_Return = jsonObject["return"].toString();   //读取的操作结果
    if(read_Return == "True"){      //登录成功
        QJsonObject userObject = jsonObject["data"].toObject();           //用户信息

        emit return_UserInfo(true,jsonObject["code"].toString(),userObject["userSex"].toString(),
                             userObject["userName"].toString(),userObject["userSign"].toString(),
                             userObject["userNumber"].toString(),userObject["userHeadimg"].toString());
        if(jsonObject["code"].toString() == "1"){
            handle_LoginReturnGroupInfo(jsonObject["groupinfo"].toObject());      //处理群聊信息
            handle_LoginReturnFriendInfo(jsonObject["friendinfo"].toObject());     //处理好友信息
        }
        return 1;
    }
    else if(read_Return == "False"){
        emit return_UserInfo(false,jsonObject["code"].toString()," "," "," "," "," ");
        return 0;
    }
}

/*  处理登录返回的好友信息
 *  friendinfo：服务端返回的好友数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_LoginReturnFriendInfo(const QJsonObject &friendinfo)
{
    int len = friendinfo["friendLen"].toInt();  //获取好友个数

    for(int i=1; i<=len; ++i){
        QString number = QStringLiteral("friend%1").arg(i);
        QJsonObject numberInfo = friendinfo[number].toObject();   //获取编号为number的好友信息
        emit return_FriendInfo(numberInfo["name"].toString(),numberInfo["sign"].toString(),
                               numberInfo["number"].toString(),numberInfo["headimg"].toString(),
                               numberInfo["state"].toString());
    }
    return 1;
}

/*  处理登录返回的群聊信息
 *  groupinfo：服务端返回的群聊数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_LoginReturnGroupInfo(const QJsonObject &groupinfo)
{
    int len = groupinfo["groupLen"].toInt();  //获取好友个数

    for(int i=1; i<=len; ++i){
        QString number = QStringLiteral("group%1").arg(i);
        QJsonObject numberInfo = groupinfo[number].toObject();   //获取编号为number的群聊信息
        emit return_GroupInfo(numberInfo["name"].toString(),numberInfo["id"].toString(),
                              numberInfo["headimg"].toString());
    }
    return 1;
}


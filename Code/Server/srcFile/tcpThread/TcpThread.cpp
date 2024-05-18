#include "TcpThread.h"
#include <QDebug>

TcpThread::TcpThread(QObject *parent)
    : QObject{parent}
    , QRunnable{}
{
    setAutoDelete(true);//设置线程自动析构
}

TcpThread::TcpThread(QTcpSocket *socket, int value, QObject *parent)
    : QObject{parent}
    , QRunnable{}
{
    //初始化对象
    thread_UserID = "";
    thread_UserPort = "";
    Tcpthread_number = value;
    Tcpthread_Socket = socket;

    init_TcpConnect();  //初始化Tcp链接
    setAutoDelete(true);//设置线程自动析构
}

TcpThread::~TcpThread()
{

}

void TcpThread::run()
{
    handle_ClientConnected();//客户端成功连接
    while(!TCPdiscon);
}

/*  设置用户项Id
 *  port：线程端口    ItemId：用户项Id
 *  返回值：void
*/
void TcpThread::handle_SetUserItemId(const QString &port, const int &ItemId)
{
    if(thread_UserPort == port){
        userItem_Id = ItemId;
    }
}

////---------------------------------------用户退出模块函数----------------------------------------------------------
/*  处理退出客户端操作
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_ExitClient()
{
    QString Sql_Code = QStringLiteral("UPDATE user SET state = '0' WHERE number = '%1'")
                         .arg(thread_UserID);
    emit request_SqlNewUserStateinExit(Sql_Code);    //请求数据库更新用户状态为离线
    return 1;
}

////---------------------------------------Tcp模块函数----------------------------------------------------------
/*  初始化Tcp链接
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::init_TcpConnect()
{
    //客户端断开连接
    connect(Tcpthread_Socket,&QAbstractSocket::disconnected,this,&TcpThread::handle_ClientDisconnected);
    //读取客户端发送的信息
    connect(Tcpthread_Socket,&QAbstractSocket::readyRead,this,&TcpThread::get_ClientSendingData);
    return 1;
}

/*  读取客户短消息
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::get_ClientSendingData()
{
    execute_JsonOperate(Tcpthread_Socket->readAll());
    return 1;
}

/*  返回信息至客户端
 *  id：线程ID    rootObj：返回客户端的Json
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::return_ClientData(const QString &id, QJsonObject rootObj)
{
    qDebug() << "当前Id" << id << "线程ID" << thread_UserID;
    if(thread_UserID == id){
        QJsonDocument jsonDocument(rootObj);
        QByteArray jsonData = jsonDocument.toJson();
        qDebug() << "返回消息至客户端" << rootObj;
        Tcpthread_Socket->write(jsonData);
        Tcpthread_Socket->flush();
        return 1;
    }
    return 0;
}

/*  客户端成功连接
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_ClientConnected()
{
    thread_UserPort = QString::number(Tcpthread_Socket->peerPort());
    if (Tcpthread_Socket->peerAddress().toString().startsWith("::ffff:")){
        emit request_NewUserConnect(Tcpthread_Socket->peerAddress().toString().mid(7),
                                    QString::number(Tcpthread_Socket->peerPort()));
    }
    else{
        emit request_NewUserConnect(Tcpthread_Socket->peerAddress().toString(),
                                    QString::number(Tcpthread_Socket->peerPort()));
    }
    return 1;
}

/*  客户端断开连接
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_ClientDisconnected()
{
    qDebug()<<"客户端断开连接..................";
    Tcpthread_Socket->deleteLater();
    TCPdiscon = true;
    return 1;
}

//执行Json中的操作
void TcpThread::execute_JsonOperate(QByteArray data_Array)
{
    //解析Json
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data_Array);
    QJsonObject jsonObject = jsonDocument.object();
    QJsonObject dataObject = jsonObject["data"].toObject();
    read_type = jsonObject["type"].toString();
    qDebug() << "读取到的数据" << jsonObject;

    if(!ismark){    //认领线程
        thread_UserID = dataObject["userNumber"].toString();  //标记线程ID
        emit request_NewUserNumber(userItem_Id,thread_UserID);//更新用户账号信息
        ismark = true;
    }

    if(read_type == "encrypt"){
        //处理加密操作
        handle_EncryptRequest(dataObject);
    }
    else if(read_type == "login"){
        //处理登录操作
        handle_UserLoginRequest(dataObject);
    }
    else if(read_type == "getAI"){
        //处理获取Ai信息操作
        handle_GetAiInfoRequest(dataObject);
    }
    else if(read_type == "setAI"){
        //处理设置Ai信息操作
        handle_SetAiInfoRequest(dataObject);
    }
    else if(read_type == "register"){
        //处理注册操作
        handle_UserRegisterRequest(dataObject);
    }
    else if(read_type == "exitClient"){
        //处理退出客户端操作
        handle_ExitClient();
    }
    else if(read_type == "selectFriend"){
        //处理查找好友信息操作
        handle_SelectFriendInfo(dataObject);
    }
    else if(read_type == "applyForfriendVerify"){
        //处理请求好友验证操作
        handle_AddFriendVerify(dataObject);
    }
    else if(read_type == "addfriendResult"){
        //处理好友验证结果操作
        handle_AddFriendResult(dataObject);
    }
    emit request_NewUserOperator(userItem_Id,read_type);    //更新用户当前操作
}

/*  处理关闭客户端线程操作
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_TCPDisconnect()
{
    TCPdiscon = true;
    return 1;
}

////---------------------------------------添加好友模块函数----------------------------------------------------------
/*  处理请求好友验证操作
 *  dataObject：接收到的数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_AddFriendVerify(QJsonObject dataObject)
{
    QString Sql_Code = QStringLiteral("SELECT * FROM user WHERE number = '%1';").arg(thread_UserID);
    emit relay_AddFriendVerify(dataObject["friendNumber"].toString(),Sql_Code);
}

/*  处理好友验证结果操作
 *  dataObject：接收到的数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_AddFriendResult(QJsonObject dataObject)
{
    emit request_AddFriendLinkData(thread_UserID,dataObject["friendNumber"].toString());
}

/*  处理获取好友信息请求
 *  dataObject：接收到的数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_SelectFriendInfo(QJsonObject dataObject)
{
    //查询是否存在该账号
    QString friend_Number = dataObject["friendNumber"].toString();
    QString Sql_Code = QStringLiteral("SELECT * FROM user WHERE number = '%1'").arg(friend_Number);
    emit request_SqlSeleteFriendInfo(thread_UserID,Sql_Code);
    return 1;
}

////---------------------------------------Ai模块函数----------------------------------------------------------
/*  处理获取Ai信息请求
 *  dataObject：接收到的数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_GetAiInfoRequest(QJsonObject dataObject)
{
    Q_UNUSED(dataObject);
    QString query = QStringLiteral("SELECT * FROM aiinfo WHERE number = '%1';").arg(thread_UserID);
    emit request_SqlSeleteAiInfo(thread_UserID,query);
}

/*  处理获取Ai信息请求
 *  dataObject：接收到的数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_SetAiInfoRequest(QJsonObject dataObject)
{
    QString query =QStringLiteral("UPDATE aiinfo SET number = '%1', sign = '%2', name = '%3', APIKey = '%4', APISecret = '%5'"
                                   " WHERE number = '%6'")
                                    .arg(thread_UserID)
                                    .arg(dataObject["Aisign"].toString())
                                    .arg(dataObject["Ainame"].toString())
                                    .arg(dataObject["APIkey"].toString())
                                    .arg(dataObject["APIsecret"].toString())
                                    .arg(thread_UserID);
    emit request_SqlSetAiInfo(thread_UserID,query);    //请求数据库设置Ai信息
    return 1;
}

////---------------------------------------加密模块函数----------------------------------------------------------
/*  处理客户端用户数据加密请求
 *  dataObject：接收到的数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_EncryptRequest(QJsonObject dataObject)
{
    QString query = QStringLiteral("UPDATE user SET encrypt_Pswd = '%1' WHERE number = '%2';")
                    .arg(dataObject["userEncrypt"].toString()).arg(thread_UserID);    //定义执行的Sql语句
    emit request_SaveEncryptData(thread_UserID,query);  //请求数据库保存加密数据
    return 1;
}

////---------------------------------------注册模块函数----------------------------------------------------------
/*  处理用户注册请求
 *  dataObject：接收到的数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_UserRegisterRequest(QJsonObject dataObject)
{

    QString query = QStringLiteral("INSERT INTO user (name, number, password, sex, sign, headimg_Path, encrypt_Pswd, state)"
                                   "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7','0')")
                        .arg(dataObject["userName"].toString())
                        .arg(dataObject["userNumber"].toString())
                        .arg(dataObject["userPassword"].toString())
                        .arg(dataObject["userSex"].toString())
                        .arg(dataObject["userSign"].toString())
                        .arg(dataObject["userHeadimg"].toString())
                        .arg(" ");
    emit request_SqlAddUserInfo(thread_UserID,query);    //请求数据库添加用户信息
    return 1;
}

////---------------------------------------登录模块函数----------------------------------------------------------
/*  处理客户端用户登录请求
 *  dataObject：接收到的数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_UserLoginRequest(QJsonObject dataObject)
{
    QString query = QStringLiteral("SELECT * FROM user "
                               "WHERE number = '%1' AND password = '%2';")
                            .arg(dataObject["userNumber"].toString())
                            .arg(dataObject["userPassword"].toString());
    emit request_VerifyUserInfo(thread_UserID,query);      //发送信号验证登录信息
    return 1;
}

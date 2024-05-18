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
    void handle_SetUserItemId(const QString &port, const int &ItemId);    //设置用户项Id
    explicit TcpThread(QTcpSocket *socket,int value,QObject *parent = nullptr);

////-----------------------------------------用户退出模块函数--------------------------------------------------------
public:
    //处理退出客户端操作
    int handle_ExitClient();
signals:
    //请求数据库更新用户状态为离线
    void request_SqlNewUserStateinExit(const QString &sqlcode);
////-----------------------------------------注册模块函数--------------------------------------------------------
public:
    //处理用户注册请求
    int handle_UserRegisterRequest(QJsonObject dataObject);
signals:
    //请求数据库添加用户信息
    void request_SqlAddUserInfo(const QString &id, const QString &query);
////-----------------------------------------登录模块函数--------------------------------------------------------
public:
    //处理用户登录请求
    int handle_UserLoginRequest(QJsonObject dataObject);
signals:
    //请求数据库验证登录信息操作
    void request_VerifyUserInfo(const QString &id, const QString &query);
////-----------------------------------------加密模块函数--------------------------------------------------------
public:
    //处理客户端用户数据加密请求
    int handle_EncryptRequest(QJsonObject dataObject);
signals:
    //申请数据库保存加密信息操作
    void request_SaveEncryptData(const QString &id, const QString &query);
////-----------------------------------------添加好友模块函数--------------------------------------------------------
public:
    int handle_AddFriendResult(QJsonObject dataObject);
    //处理请求好友验证操作
    int handle_AddFriendVerify(QJsonObject dataObject);
    //处理获取好友信息请求
    int handle_SelectFriendInfo(QJsonObject dataObject);
    //发送Json请求好友验证
    void request_FriendVerify(const QString &id, const QString &type, const QString &friendnumbe,
                              const QString &name, const QString &sex, const QString &sign,
                              const QString &number, const QString &headimg_Path);
signals:
    //转发至主线程处理请求好友验证操作
    void relay_AddFriendVerify(const QString &id, const QString &sqlcode);
    //申请数据库查询好友信息
    void request_SqlSeleteFriendInfo(const QString &id, const QString& sqlcode);
    //申请数据库添加好友链接数据
    void request_AddFriendLinkData(const QString &id,const QString &friendnumber);
////-----------------------------------------Tcp模块函数--------------------------------------------------------
public:
    //初始化Tcp链接
    int init_TcpConnect();
    //客户端成功连接
    int handle_ClientConnected();
    //读取客户端发送的信息
    int get_ClientSendingData();
    //客户端断开连接
    int handle_ClientDisconnected();
    //返回信息至客户端
    int return_ClientData(const QString &id, QJsonObject rootObj);
    //执行Json中的操作
    void execute_JsonOperate(QByteArray data_Array);
public slots:
    //处理关闭客户端线程操作
    int handle_TCPDisconnect();
signals:
    //请求UserInfo更新用户链接信息
    void request_NewUserConnect(const QString& ip,const QString& port);
    //请求UserInfo更新用户账号信息
    void request_NewUserNumber(const int& itemid,const QString& number);
    //请求UserInfo更新用户操作信息
    void request_NewUserOperator(const int& id, const QString& type);
////-----------------------------------------Ai模块函数--------------------------------------------------------
public:
    //处理获取Ai信息操作请求
    int handle_GetAiInfoRequest(QJsonObject dataObject);
    //设置Ai信息
    int handle_SetAiInfoRequest(QJsonObject dataObject);
signals:
    //申请数据库设置Ai信息
    void request_SqlSetAiInfo(const QString &id, const QString &query);
    //申请数据库查询Ai信息操作
    void request_SqlSeleteAiInfo(const QString &id, const QString &query);

private:
    QString read_type;           //当前线程操作类型
    int userItem_Id = 0;         //用户项Id
    bool ismark = false;         //标记线程是否被用户认领
    QJsonObject VerifyObj;       //传输的验证Json数据
    QString thread_UserID;       //用户线程标记
    bool TCPdiscon = false;      //判断客户端是否断开连接
    QJsonObject jsonObject;      //传输的json数据
    QString thread_UserPort;     //用户线程端口
    int Tcpthread_number = 0;    //客户端编号
    QTcpSocket *Tcpthread_Socket;//通信对象


private:
    QString read_friendsex;        //读取到好友的性别字段
    QString read_friendtype;       //读取到好友的类型字段
    QString read_friendsign;       //读取到好友的个签字段
    QString read_frienddata;       //读取到好友的数据字段
    QString read_friendname;       //读取到好友的昵称字段
    QString read_friendnumber;     //读取到好友的账号字段
    QString read_friendheadimg;    //读取到好友的头像字段
};

#endif // TCPTHREAD_H

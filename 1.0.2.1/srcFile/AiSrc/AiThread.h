#ifndef AITHREAD_H
#define AITHREAD_H

#include <QThread>
#include <QObject>
#include <QUrlQuery>
#include <QDateTime>
#include <QEventLoop>
#include <QJsonArray>
#include <QMessageBox>
#include <QJsonObject>
#include <QHostAddress>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkInterface>
#include <QRegularExpression>
#include <QNetworkAccessManager>
#include <QMessageAuthenticationCode>

class AiThread : public QThread
{
    Q_OBJECT
public:
    explicit AiThread(QObject *parent = nullptr);
    ~AiThread();

public:
    //获取Accesstoken
    bool get_Accesstoken();
    //初始化鉴权元素
    void init_Authentication();
    //解析回复语句
    QString get_AnswerText(const QString &text);
    //修改询问语句
    bool set_EnquireText(const QString &Enquiretext);

protected:
    //线程执行内容
    virtual void run() override;

signals:
    //答复信号
    void getAnswer(const QString &response);

private:
    QString APIKey;                  //鉴权元素APIKey
    QString APISecret;               //鉴权元素APISecret
    QByteArray payload;              //请求内容
    QString accessToken;             //返回的AccessToken
    QNetworkReply *reply;            //发送POST请求
    QByteArray responseData;         //解析的回复语句
    QNetworkRequest request;         //创建POST请求
    QRegularExpression Regex;        //正则表达式对象
    QNetworkAccessManager *manager;  //网络访问管理器

};

#endif // AITHREAD_H

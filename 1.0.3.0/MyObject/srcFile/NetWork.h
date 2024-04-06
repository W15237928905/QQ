#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QUrlQuery>
#include "AiSrc/AI.h"
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QRegularExpression>
#include <QNetworkAccessManager>


class NetWork : public QObject
{
    Q_OBJECT
public:
    explicit NetWork();
    ~NetWork();

public:
    //获取Accesstoken
    bool get_Accesstoken();
    //更新鉴权元素
    void new_KeyandSecret();
    //判断是否存在鉴权元素
    bool inspect_KeyandSecret();
    //设置鉴权元素
    void set_Authentication(const QString &key, const QString &secret);
    //修改询问语句
    QString set_EnquireText(const QString &enquiretext);

private:
    QString APIKey;                  //鉴权元素APIKey
    QString APISecret;               //鉴权元素APISecret
    QByteArray payload;              //请求内容
    QString accessToken;             //返回的AccessToken
    QNetworkReply *reply;            //发送POST请求
    QNetworkRequest request;         //创建POST请求
    QRegularExpression Regex;        //正则表达式对象
    QNetworkAccessManager *manager;  //网络访问管理器
};

extern NetWork my_NETWORK;   //声明全局变量

#endif // NETWORK_H

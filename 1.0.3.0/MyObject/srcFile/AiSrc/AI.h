#ifndef AI_H
#define AI_H

#include <QObject>
#include <QThread>

class AI : public QObject
{
    Q_OBJECT
public:
    explicit AI();
    ~AI();

    //设置机器人名称
    void set_AiName(const QString &name);
    //设置机器人介绍
    void set_AiSign(const QString &sign);
    //设置鉴权元素APIKey
    void set_ApiKey(const QString &ApiKey);
    //设置鉴权元素APISecret
    void set_ApiSecret(const QString &ApiSecret);
    //获取机器人信息
    const QString& get_AiInfo(const QString &Type);
    //设置全部对象
    void set_AllObject(const QString &ai_Name,const QString &ai_Sign,
                       const QString &ai_ApiKey,const QString &ai_ApiSecret);

signals:
    //更新信号
    void new_AI();

private:
    QString ai_Name;           //机器人名称
    QString ai_Sign;           //机器人介绍
    QString ai_ApiKey;         //鉴权元素APIKey
    QString ai_ApiSecret;      //鉴权元素APISecret
};

extern AI my_AI;   //声明全局变量

#endif // AI_H

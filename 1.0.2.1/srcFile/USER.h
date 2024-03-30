#ifndef USER_H
#define USER_H

#include <QObject>

class USER : public QObject
{
    Q_OBJECT
public:
    explicit USER();
    ~USER();

    //设置用户性别
    void set_UserSex(const QString &Sex);
    //设置用户昵称
    void set_UserName(const QString &Name);
    //设置用户签名
    void set_UserSign(const QString &Sign);
    //设置用户账号
    void set_UserNumber(const QString &Number);
    //设置用户头像
    void set_UserHeadimgPath(const QString &HeadimgPath);
    //获取用户信息
    const QString& get_UserInfo(const QString &Type);
    //设置全部对象
    void set_AllObject(const QString &user_Sex,const QString &user_Name,const QString &user_Sign,
                       const QString &user_Number,const QString &user_HeadimgPath);

signals:
    //更新信号
    void new_USER();

private:
    QString user_Sex;           //用户性别
    QString user_Name;          //用户昵称
    QString user_Sign;          //用户签名
    QString user_Number;        //用户账号
    QString user_HeadimgPath;   //用户头像
};

extern USER my_USER;   //声明全局变量

#endif // USER_H

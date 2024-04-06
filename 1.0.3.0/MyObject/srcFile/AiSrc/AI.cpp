#include "AI.h"
#include <QDebug>

AI::AI()
{
    //初始化对象
    ai_Name = "智能机器人";
    ai_Sign = "你好！我是小源，你的专属聊天机器人";
    ai_ApiKey = "";
    ai_ApiSecret = "";
}

AI::~AI()
{

}

/*  设置机器人名称
 *  时间：2024/03/23   作者：Wild_Pointer
*/
void AI::set_AiName(const QString &name)
{
    ai_Name = name;
}

/*  设置机器人介绍
 *  时间：2024/03/23   作者：Wild_Pointer
*/
void AI::set_AiSign(const QString &sign)
{
    ai_Sign = sign;
}

/*  鉴权元素APIKey
 *  时间：2024/03/23   作者：Wild_Pointer
*/
void AI::set_ApiKey(const QString &ApiKey)
{
    ai_ApiKey = ApiKey;
}

/*  设置鉴权元素APISecret
 *  时间：2024/03/23   作者：Wild_Pointer
*/
void AI::set_ApiSecret(const QString &ApiSecret)
{
    ai_ApiSecret = ApiSecret;
}

/*  获取机器人信息
 *  Type：信息类型
 *  时间：2024/03/23   作者：Wild_Pointer
*/
const QString &AI::get_AiInfo(const QString &Type)
{
    if(Type == "Name"){
        return ai_Name;
    }
    else if(Type == "Sign"){
        return ai_Sign;
    }
    else if(Type == "ApiKey"){
        return ai_ApiKey;
    }
    else if(Type == "ApiSecret"){
        return ai_ApiSecret;
    }
    else{
        return QString("");
    }
}

/*  设置全部对象
 *  ai_Name：机器人名称   ai_Sign：机器人介绍   ai_ApiKey：鉴权元素APIKey    ai_ApiSecret：鉴权元素APISecret
 *  时间：2024/03/24   作者：Wild_Pointer
*/
void AI::set_AllObject(const QString &ai_Name, const QString &ai_Sign, const QString &ai_ApiKey, const QString &ai_ApiSecret)
{
    set_AiName(ai_Name);
    set_AiSign(ai_Sign);
    set_ApiKey(ai_ApiKey);
    set_ApiSecret(ai_ApiSecret);

    emit new_AI();
}

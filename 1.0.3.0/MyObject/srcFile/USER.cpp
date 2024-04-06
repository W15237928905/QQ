#include "USER.h"

USER::USER()
{
    //初始化对象
    user_Name = "";
    user_Number= "";
    user_Sex = "男";
    user_Sign = "当前还没有个性签名喔！";
    user_HeadimgPath = ":/new/Chat/icons/Chat/logo_Show.png";
}

USER::~USER()
{

}

/*  设置用户性别
 *  Sex：性别
 *  时间：2024/03/23   作者：Wild_Pointer
*/
void USER::set_UserSex(const QString &Sex)
{
    user_Sex = Sex;
}

/*  设置用户昵称
 *  Name：昵称
 *  时间：2024/03/23   作者：Wild_Pointer
*/
void USER::set_UserName(const QString &Name)
{
    user_Name = Name;
}

/*  设置用户签名
 *  Sign：签名
 *  时间：2024/03/23   作者：Wild_Pointer
*/
void USER::set_UserSign(const QString &Sign)
{
    user_Sign = Sign;
}

/*  设置用户账号
 *  Number：账号
 *  时间：2024/03/23   作者：Wild_Pointer
*/
void USER::set_UserNumber(const QString &Number)
{
    user_Number = Number;
}

/*  设置用户头像
 *  HeadimgPath：头像路径
 *  时间：2024/03/23   作者：Wild_Pointer
*/
void USER::set_UserHeadimgPath(const QString &HeadimgPath)
{
    user_HeadimgPath = HeadimgPath;
}

/*  获取用户信息
 *  Type：信息类型
 *  时间：2024/03/23   作者：Wild_Pointer
*/
const QString& USER::get_UserInfo(const QString &Type)
{
    if(Type == "Sex"){
        return user_Sex;
    }
    else if(Type == "Name"){
        return user_Name;
    }
    else if(Type == "Sign"){
        return user_Sign;
    }
    else if(Type == "Number"){
        return user_Number;
    }
    else if(Type == "HeadimgPath"){
        return user_HeadimgPath;
    }
    else{
        return "";
    }
}

/*  设置全部对象
 *  user_Sex：用户性别   user_Name：用户昵称   user_Sign：用户签名    user_Number：用户账号    user_HeadimgPath：用户头像
 *  时间：2024/03/24   作者：Wild_Pointer
*/
void USER::set_AllObject(const QString &user_Sex,const QString &user_Name,const QString &user_Sign,
                         const QString &user_Number,const QString &user_HeadimgPath)
{
    set_UserSex(user_Sex);
    set_UserName(user_Name);
    set_UserSign(user_Sign);
    set_UserNumber(user_Number);
    set_UserHeadimgPath(user_HeadimgPath);


    emit new_USER();
}



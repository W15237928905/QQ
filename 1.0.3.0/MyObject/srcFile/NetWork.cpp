#include "NetWork.h"

NetWork::NetWork()
{
    //初始化对象
    APIKey = "";
    APISecret = "";
    accessToken = "";
    manager = new QNetworkAccessManager(this);

    connect(&my_AI, AI::new_AI,this,NetWork::new_KeyandSecret);
}

NetWork::~NetWork()
{
    reply->deleteLater();
    delete reply;
    delete manager;
}

/*  获取Accesstoken
 *  时间：2024/03/30   作者：Wild_Pointer
*/
bool NetWork::get_Accesstoken()
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        //修改正则表达式
        Regex.setPattern("\"access_token\":\"(.*?)\"");

        //在JSON字符串中进行匹配
        QRegularExpressionMatch match = Regex.match(responseData);

        // 如果找到匹配项，则提取access_token数据
        if (match.hasMatch()) {
            accessToken = match.captured(1);
            return true;
        } else {
            QMessageBox::information(nullptr,"提示","未获取到Access_token!",QMessageBox::Ok);
            return false;
        }
    }
    else {
        QMessageBox::warning(nullptr,"错误",reply->errorString(),QMessageBox::Ok);
        return false;
    }
}


/*  更新鉴权元素
 *  时间：2024/03/30   作者：Wild_Pointer
*/
void NetWork::new_KeyandSecret()
{
    set_Authentication(my_AI.get_AiInfo("ApiKey"),my_AI.get_AiInfo("ApiSecret"));
}

/*  判断是否存在鉴权元素
 *  时间：2024/03/30   作者：Wild_Pointer
*/
bool NetWork::inspect_KeyandSecret()
{
    if(APIKey.isEmpty() || APISecret.isEmpty()){
        QMessageBox::warning(nullptr,"错误","未设置APIKey或APISecret",QMessageBox::Ok);
        return false;
    }
    else if(accessToken.isEmpty()){
        QMessageBox::warning(nullptr,"错误","token为空",QMessageBox::Ok);
        return false;
    }
    return true;
}

/*  设置鉴权元素
 *  时间：2024/03/30   作者：Wild_Pointer
*/
void NetWork::set_Authentication(const QString &key, const QString &secret)
{
    //更新APIKey和APISecret
    APIKey = key;
    APISecret = secret;

    //初始化POST请求的参数
    QUrlQuery params;
    params.addQueryItem("grant_type", "client_credentials");
    params.addQueryItem("client_id", APIKey);
    params.addQueryItem("client_secret", APISecret);
    QByteArray postData = params.toString(QUrl::FullyEncoded).toUtf8();

    // 设置URL和请求头部
    request.setUrl(QUrl("https://aip.baidubce.com/oauth/2.0/token"));
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    request.setRawHeader("Accept", "application/json");

    //将请求数据作为第二个参数传递给post函数
    reply = manager->post(request, postData);
    connect(reply, &QNetworkReply::finished,this,&NetWork::get_Accesstoken);
}

/*  修改询问语句
 *  enquiretext：询问语句
 *  时间：2024/03/30   作者：Wild_Pointer
*/
QString NetWork::set_EnquireText(const QString &enquiretext)
{
    //清空请求内容和回复语句
    payload = "";

    // 准备请求数据
    QJsonObject messageObject;
    messageObject["role"] = "user";
    messageObject["content"] = enquiretext;

    QJsonArray messagesArray;
    messagesArray.append(messageObject);
    QJsonObject requestBody;
    requestBody["messages"] = messagesArray;

    // 将JSON对象转换为字符串
    QJsonDocument doc(requestBody);
    payload = doc.toJson();

    // 设置请求头
    QString url = "https://aip.baidubce.com/rpc/2.0/ai_custom/v1/wenxinworkshop/chat/completions_pro?access_token=" + accessToken;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //发送POST请求
    reply = manager->post(request, payload);

    // 等待响应完成
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // 读取响应数据
    if (reply->error() == QNetworkReply::NoError) {
        return reply->readAll();
    } else {
        QMessageBox::warning(nullptr,"错误",reply->errorString(),QMessageBox::Ok);
        return "";
    }
}

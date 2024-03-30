#include "AiThread.h"

AiThread::AiThread(QObject *parent)
    : QThread{parent}
{
    //初始化私有对象
    manager = new QNetworkAccessManager(this);

    //初始化鉴权元素
    init_Authentication();

    connect(reply, &QNetworkReply::finished,this,&AiThread::get_Accesstoken);
}


/*  初始化鉴权元素
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void AiThread::init_Authentication()
{
    //初始化鉴权元素
    APIKey = "";
    APISecret = "";

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
    qDebug() << "AiThread::init_Authentication()" << params.toString();
    reply = manager->post(request, postData);
}

/*  解析回复语句
 *  text：回复语句
 *  时间：2024/03/14   作者：Wild_Pointer
*/
QString AiThread::get_AnswerText(const QString &text)
{
    QString hex;
    //定义正则表达式，用于获取指定result值后的数据
    QRegularExpression regular("\"result\":\"(.*?)\"");
    QRegularExpressionMatch match = regular.match(text);
    QString matchedString = match.captured();   //捕获匹配正则表达式的数据

    //设置正则表达式，用于匹配\x后面的数据
    regular.setPattern("\\\\x([0-9A-Fa-f]{2})");

    //迭代正则表达式匹配的结果
    QRegularExpressionMatchIterator iteration = regular.globalMatch(matchedString);

    while (iteration.hasNext()) {       //循环遍历寻找匹配数据
        QRegularExpressionMatch match = iteration.next();
        hex = match.captured(1);
        bool ok;
        int decimal = hex.toInt(&ok, 16);
        if (ok) {
            matchedString.replace(match.capturedStart(), match.capturedLength(), QString(QChar(decimal)));
        }
    }

    //文本处理
    matchedString.replace("result\":\"", "");
    matchedString.replace("\\n", "\n");
    qDebug() << "AiThread::get_AnswerText(const QString &text)" << matchedString;
    return matchedString;
}

/*  修改询问语句
 *  Enquiretext：询问语句
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool AiThread::set_EnquireText(const QString &Enquiretext)
{
    //清空请求内容和回复语句
    payload = "";
    responseData = "";

    // 准备请求数据
    QJsonObject messageObject;
    messageObject["role"] = "user";
    messageObject["content"] = Enquiretext;

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
        responseData = reply->readAll();
    } else {
        QMessageBox::warning(nullptr,"错误",reply->errorString(),QMessageBox::Ok);
    }
}

/*  获取Accesstoken
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool AiThread::get_Accesstoken()
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
            qDebug() << "AiThread::get_Accesstoken()" << accessToken;
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

AiThread::~AiThread()
{
    reply->deleteLater();
    delete reply;
    delete manager;
}

/*  线程执行内容
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void AiThread::run()
{
    //解析回复语句
    emit getAnswer(get_AnswerText(responseData));
    qDebug() << "线程启动";
}

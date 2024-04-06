#ifndef AITHREAD_H
#define AITHREAD_H

#include <QThread>
#include <QRunnable>
#include <QObject>
#include <QRegularExpressionMatch>

class AiThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit AiThread(QObject *parent = nullptr);
    explicit AiThread(const QString &response,QObject *parent = nullptr);
    ~AiThread();   

public:
    //线程执行内容
    virtual void run() override;
    //解析回复语句
    QString get_AnswerText(const QString &text);


signals:
    //答复信号
    void getAnswer(const QString &response);

private:
    QString responseData;    //答复数据
};

#endif // AITHREAD_H

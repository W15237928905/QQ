#ifndef SQLTHREAD_H
#define SQLTHREAD_H

#include <QtSql>
#include <QObject>
#include <QSqlError>
#include <QRunnable>
#include <QSqlDatabase>

class SqlThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ~SqlThread();
    //线程执行函数
    virtual void run() override;
    explicit SqlThread(QObject *parent = nullptr);
    explicit SqlThread(const QString &type,const QString &query,QObject *parent = nullptr);


public:
    //初始化数据库线程
    void init_SqlThread();
    //修改数据
    bool set_SqlQuery(QString query);
    //获取表格列数
    int get_RowCount(const QString &list);
    //修改Sql语句
    void set_Query(const QString &Sqlquery);
    //添加数据
    bool add_SqkQuery(const QString &query);
    //查询数据
    const QStringList& get_SqkQuery(const QString &query);
    //验证数据
    bool testing_SqlQuery(const QString &outside,const QString &list=nullptr,const QString &data=nullptr);

signals:
    //返回数据库验证操作结果
    void return_TestingResult(const QString &result);

private:
    bool state_Ok;               //互斥量，用于防止多个线程同时操作数据库
    QString query;               //记录查询语句
    QString *Sql_Data;           //记录查询结果
    QSqlError *Sql_Error;        //数据库错误信息
    QSqlQuery *Sql_Query;        //数据库查询语句
    QSqlDatabase *Data_Base;     //数据库对象

};

#endif // SQLTHREAD_H

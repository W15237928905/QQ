#ifndef SQLOBJECT_H
#define SQLOBJECT_H

#include <QtSql>
#include <QObject>
#include <QSqlError>
#include <QRunnable>
#include <QSqlDatabase>

class SqlObject : public QObject
{
    Q_OBJECT
public:
    ~SqlObject();
    explicit SqlObject();

public:
    //初始化数据库线程
    void init_SqlObeject();
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

private:
    QString query;               //记录查询语句
    QString *Sql_Data;           //记录查询结果
    QSqlError *Sql_Error;        //数据库错误信息
    QSqlQuery *Sql_Query;        //数据库查询语句
    QSqlDatabase *Data_Base;     //数据库对象
};

#endif // SQLOBJECT_H

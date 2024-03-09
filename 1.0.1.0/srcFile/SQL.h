#ifndef SQL_H
#define SQL_H

#include <QtSql>
#include <QObject>
#include <QSqlError>
#include <QSqlDatabase>

class SQL : public QObject
{
    Q_OBJECT
public:
    explicit SQL();
    ~SQL();

private:
    QSqlDatabase *Data_Base;     //数据库对象
    QString *Sql_Data;           //记录查询结果
    QString query;               //记录查询语句
    QSqlError *Sql_Error;        //数据库错误信息
    QSqlQuery *Sql_Query;        //数据库查询语句

public:
    bool get_SqlQuery(QString outside,QString list=nullptr,QString data=nullptr);    //查询数据函数
    bool add_SqkQuery(QString query);       //添加数据函数
    int get_RowCount(QString list);        //获取表格列数
    void get_Path();
};

extern SQL mySql;   //声明全局变量

#endif // SQL_H

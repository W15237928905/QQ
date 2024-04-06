#include "SqlThread.h"
#include <QDebug>

SqlThread::SqlThread(QObject *parent)
    : QObject{parent}
    , QRunnable{}
{
    //初始化数据库线程
    init_SqlThread();
}

/*  创建指定操作的线程
 *  type：操作类型   query：Sql语句
*/
SqlThread::SqlThread(const QString &type,const QString &query,QObject *parent)
    : QObject{parent}
    , QRunnable{}
{
    //初始化数据库线程
    init_SqlThread();
}

//修改Sql语句
void SqlThread::set_Query(const QString &Sqlquery)
{
    query = Sqlquery;
}

//初始化数据库线程
void SqlThread::init_SqlThread()
{
    //初始化对象
    Sql_Error = new QSqlError();

    //设置自动析构
    setAutoDelete(true);

    //配置数据库信息
    Data_Base = new QSqlDatabase();
    *Data_Base = QSqlDatabase::addDatabase("QMYSQL");
    Data_Base->setHostName("127.0.0.1");
    Data_Base->setPort(3306);
    Data_Base->setUserName("root");
    Data_Base->setPassword("");
    Data_Base->setDatabaseName("");

    if (Data_Base->open()) {
        qDebug() << "成功连接到数据库";
    } else {
        qDebug() << "连接数据库失败:" << Data_Base->lastError().text();
    }
    Sql_Query = new QSqlQuery(*Data_Base);
}

SqlThread::~SqlThread()
{
    delete Sql_Error;
    delete Data_Base;
    delete Sql_Query;
}

//线程执行函数
void SqlThread::run()
{

}

//验证数据
bool SqlThread::testing_SqlQuery(const QString &outside, const QString &list, const QString &data)
{
    if (list == nullptr && data == nullptr){
        query = QStringLiteral("SELECT * FROM %1;")    //初始化查询语句
                    .arg(outside);
        Sql_Query->exec(query);         //设置查询语句并查询
        while (Sql_Query->next()) {     //开始查询
            QSqlRecord record = Sql_Query->record();    //获取当前遍历的数据
            int columnCount = record.count();
            for (int i = 0; i < columnCount; ++i) {
                QString columnName = record.fieldName(i);
                QVariant value = record.value(i);
                qDebug() << columnName << ": " << value.toString();
            }
        }
        qDebug() << "验证数据\n";
        emit return_TestingResult("True");
        return true;
    }
    else{
        query = QStringLiteral("SELECT * FROM %1 WHERE %2 = '%3';")    //初始化查询语句
                    .arg(outside).arg(list).arg(data);
        qDebug() << query;
        Sql_Query->exec(query);         //设置查询语句并查询
        while (Sql_Query->next()) {     //开始查询
            emit return_TestingResult("True");
            return true;
        }
    }
    emit return_TestingResult("False");
    return false;
}

//查询数据
const QStringList &SqlThread::get_SqkQuery(const QString &query)
{
    QStringList *info = new QStringList();
    Sql_Query->exec(query);
    while (Sql_Query->next()) {     //开始查询
        QSqlRecord record = Sql_Query->record();    //获取当前遍历的数据
        int columnCount = record.count();
        for (int i = 0; i < columnCount; ++i) {
            QVariant value = record.value(i);
            info->append(value.toString());
        }
    }
    return *info;
}

//添加数据
bool SqlThread::add_SqkQuery(const QString &query)
{
    qDebug() << "添加数据" << query;
    return Sql_Query->exec(query);
}

//修改数据
bool SqlThread::set_SqlQuery(QString query)
{

}

//获取表格列数
int SqlThread::get_RowCount(const QString &list)
{
    //获取当前用户个数
    Sql_Query->exec(QStringLiteral("SELECT COUNT(*) FROM %1")
                        .arg(list));
    Sql_Query->next();
    return Sql_Query->value(0).toInt();
}

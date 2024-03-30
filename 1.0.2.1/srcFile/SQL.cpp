#include "SQL.h"

SQL::SQL()
{
    //初始化对象
    Sql_Error = new QSqlError();

    //配置数据库信息
    Data_Base = new QSqlDatabase();
    *Data_Base = QSqlDatabase::addDatabase("QMYSQL");
    Data_Base->setHostName("127.0.0.1");
    Data_Base->setPort(3306);
    Data_Base->setUserName("");
    Data_Base->setPassword("");
    Data_Base->setDatabaseName("");

    if (Data_Base->open()) {
        qDebug() << "成功连接到数据库";
        // 在这里执行数据库操作
    } else {
        qDebug() << "连接数据库失败:" << Data_Base->lastError().text();
    }
    Sql_Query = new QSqlQuery(*Data_Base);

}

SQL::~SQL()
{

}

/*  验证数据
 *  outside：查询的表格   list：查询的列   data：验证的数据
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool SQL::testing_SqlQuery(const QString &outside,const QString &list,const QString &data)
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
        return true;
    }
    else{
        query = QStringLiteral("SELECT * FROM %1 WHERE %2 = '%3';")    //初始化查询语句
                            .arg(outside).arg(list).arg(data);
        qDebug() << query;
        Sql_Query->exec(query);         //设置查询语句并查询
        while (Sql_Query->next()) {     //开始查询
            return true;
        }
    }
    return false;
}

/*  查询数据
 *  query：执行的语句
 *  时间：2024/03/23   作者：Wild_Pointer
*/
const QStringList& SQL::get_SqkQuery(const QString &query)
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

/*  增加数据
 *  query：执行的语句
 *  时间：2024/03/14   作者：Wild_Pointer
*/
bool SQL::add_SqkQuery(const QString &query)
{
    return Sql_Query->exec(query);
}


/*  获取表格列数
 *  list：表格名称
 *  时间：2024/03/14   作者：Wild_Pointer
*/
int SQL::get_RowCount(const QString &list)
{
    //获取当前用户个数
    Sql_Query->exec(QStringLiteral("SELECT COUNT(*) FROM %1")
                        .arg(list));
    Sql_Query->next();
    return Sql_Query->value(0).toInt();
}

/*  获取数据库对象地址
 *  时间：2024/03/14   作者：Wild_Pointer
*/
void SQL::get_Path()
{
    qDebug() << QString("Data_Base地址：%1").arg(reinterpret_cast<quintptr>(&Data_Base), 0, 16);
}



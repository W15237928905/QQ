#include "sendFilebox.h"
#include "ui_sendFilebox.h"

sendFilebox::sendFilebox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sendFilebox)
{
    ui->setupUi(this);

    connect(&file_Thread, &FileThread::newRecvsize, this, &sendFilebox::setRecvsize);
}

sendFilebox::~sendFilebox()
{
    delete ui;
}

/*  更新进度条下载信息
 *  recvsize：下载进度
 *  时间：2024/03/25   作者：Wild_Pointer
*/
void sendFilebox::setRecvsize(int recvsize)
{
    ui->progressBar->setValue(recvsize);
}

/*  设置文件信息
 *  name：文件名称   size：文件大小
 *  时间：2024/03/25   作者：Wild_Pointer
*/
void sendFilebox::set_FileInfo(const QString &name, const qint64 &size)
{
    ui->filename_lab->setText(name);

    //设置显示的文件大小
    double number = static_cast<double>(size)/1024/1024;
    QString str = QStringLiteral("%1MB").arg(QString::number(number,'f',2));
    ui->filesize_lab->setText(str);
    ui->progressBar->setMinimum(number);

}

/*  鼠标双击事件
 *  event：事件
 *  时间：2024/03/26   作者：Wild_Pointer
*/
void sendFilebox::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "sendFilebox::mouseDoubleClickEvent(QMouseEvent *event)";
}

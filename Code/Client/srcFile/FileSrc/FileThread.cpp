#include "FileThread.h"

FileThread::FileThread(QObject *parent)
    : QObject{parent}
    , QRunnable()
{
    //初始化对象
    file = new QFile();
    Widget = new QWidget();
    file_progressByte = 0;
}

FileThread::~FileThread()
{
    delete Widget;
}

/*  获取传输的文件
 *  时间：2024/03/24   作者：Wild_Pointer
*/
bool FileThread::get_FilePath()
{
    //选择文件，打开路径为桌面
    file_Path = QFileDialog::getOpenFileName(Widget, "选择传输的文件",
                                             QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)
                                             ,"All Files (*)");

    if(!file_Path.isEmpty()){
        file_FileInfo = QSharedPointer<QFileInfo>(new QFileInfo(file_Path));
        file_Name = file_FileInfo->fileName();
        file_Size = file_FileInfo->size();
        file->setFileName(file_Path);

        //打开文件
        bool is_Open = file->open(QIODevice::ReadOnly);
        if(!is_Open){
            QMessageBox::information(Widget,"提示","文件打开失败",QMessageBox::Ok);
            return false;
        }else{
            emit newFile();
        }
        file->close();
        return true;
    }
}

void FileThread::run()
{

}

/*  获取文件信息(文字)
 *  时间：2024/03/25   作者：Wild_Pointer
*/
const QString &FileThread::get_UserStrinfo(const QString &Type)
{
    if(Type == "Name"){
        return file_Name;
    }
    else if(Type == "Path"){
        return file_Path;
    }
    else{
        return "";
    }

}

/*  获取文件信息(大小)
 *  时间：2024/03/25   作者：Wild_Pointer
*/
const qint64 &FileThread::get_UserSizeinfo(const QString &Type)
{
   if(Type == "Size"){
        return file_Size;
    }
    else if(Type == "RecvSize"){
        return file_RecvSize;
    }
    else if(Type == "SendSize"){
        return file_SendSize;
    }
    return 0;
}

/*  链接服务器
 *  时间：2024/03/27   作者：Wild_Pointer
*/
void FileThread::connectToServer()
{
    //初始化file_TcpSocket对象，链接至对应服务器
    /*file_TcpSocket = new QTcpSocket(this);
    file_TcpSocket->connectToconnect("127.0.0.1",28080);
    if(!file_TcpSocket->waitForConnected(2*1000)) {
        QString Str = QStringLiteral("连接服务器失败，错误信息：%1").arg(file_TcpSocket->errorString());
        QMessageBox::warning(Widget, "警告", Str, QMessageBox::Ok);
    }else{
        QMessageBox::information(Widget, "提示", "服务器连接成功！", QMessageBox::Ok);
    }

    //对读取服务器数据和断开连接进行处理
    connect(file_TcpSocket, &QTcpSocket::readyRead, this, &FileThread::readServerMsg);
    connect(file_TcpSocket, &QTcpSocket::disconnected, this, [=]() {
        QString error = QStringLiteral("与服务器断开连接：原因：%1").arg(file_TcpSocket->errorString());
        QMessageBox::information(Widget,"提示",error,QMessageBox::Ok);
    });*/

}

void FileThread::readServerMsg()
{
    /*//如果正在下载，则收到的全是文件数据，读取即可
    if(file_isDownloading) {
        fileDataRead();
        return;
    }
    qDebug()<< ".............readServerMsg................";

    QDataStream in(file_TcpSocket);
    in.setVersion(QDataStream::Qt_5_12);
    int type;
    in >> type; //判断消息类型

    if(type == FileType::FileInfo) {
        //fileInfoRead();
        file_isDownloading = true;
    }
    else {
        qDebug() << "收到其他消息类型！！！type：" <<type;
    }*/
}

void FileThread::fileDataRead()
{
   /* qint64 readBytes = file_TcpSocket->bytesAvailable();
    if(readBytes <0) return;

    int progress = 0;
    //如果接收的数据大小小于要接收的文件大小，那么继续写入文件

    if(file_RecvSize < file_Size) {
        // 返回等待读取的传入字节数
        QByteArray data = file_TcpSocket->read(readBytes);
        file_RecvSize += readBytes;
        progress =static_cast<int>(file_RecvSize*100/file_Size);
        file_progressByte = file_RecvSize;
        file->write(data);
        emit newRecvsize(progress);
    }

    // 接收数据完成时
    if (file_RecvSize == file_Size){
        progress = 100;
        file->close();
        file_progressByte = file_RecvSize;
        emit newRecvsize(progress);
        file_isDownloading = false;
    }

    if (file_RecvSize > file_Size){
        qDebug()<<"myFile->bytesReceived > m_fileSize";
    }*/
}

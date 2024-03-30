#ifndef SENDFILEBOX_H
#define SENDFILEBOX_H

#include <QWidget>
#include <QMouseEvent>
#include "srcFile/FileSrc/FileThread.h"


namespace Ui {
class sendFilebox;
}

class sendFilebox : public QWidget
{
    Q_OBJECT

public:
    explicit sendFilebox(QWidget *parent = nullptr);
    ~sendFilebox();

public:
    //更新进度条下载信息
    void setRecvsize(int recvsize);
    //设置文件信息
    void set_FileInfo(const QString& name,const qint64& size);

protected:
    //鼠标双击事件
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    Ui::sendFilebox *ui;
    FileThread file_Thread;
};

#endif // SENDBOX_H

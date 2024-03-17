#ifndef AIINFO_H
#define AIINFO_H

#include <QWidget>
#include "uiFile/AiChat.h"

namespace Ui {
class AiInfo;
}

class AiInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AiInfo(QWidget *parent = nullptr);
    explicit AiInfo(QString name, QString message, QString head_Path, QString timer, QWidget *parent = nullptr);
    ~AiInfo();

protected:
    //双击机器人显示对话框
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    Ui::AiInfo *ui;
    QSharedPointer<AiChat> Chat;        //AI聊天界面


};

#endif // AIINFO_H

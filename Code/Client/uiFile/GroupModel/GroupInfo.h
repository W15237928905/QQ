#ifndef GROUPINFO_H
#define GROUPINFO_H

#include <QWidget>
#include <QMouseEvent>
#include "uiFile/GroupModel/GroupChat.h"

class GroupChat;

namespace Ui {
class GroupInfo;
}

class GroupInfo : public QWidget
{
    Q_OBJECT

public:
    ~GroupInfo();
    explicit GroupInfo(QWidget *parent = nullptr);
    explicit GroupInfo(const QString &name, const QString &id,
                       const QString &head_Path, QWidget *parent = nullptr);

public:
    //初始化群聊信息界面
    int init_GroupInfoWidget(const QString &name, const QString &id, const QString &head_Path);

protected:
    //鼠标双击事件
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    Ui::GroupInfo *ui;
    QSharedPointer<GroupChat> Chat;
};

#endif // GROUPINFO_H

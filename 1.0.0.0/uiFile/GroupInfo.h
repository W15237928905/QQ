#ifndef GROUPINFO_H
#define GROUPINFO_H

#include <QWidget>

class GroupChat;

namespace Ui {
class GroupInfo;
}

class GroupInfo : public QWidget
{
    Q_OBJECT

public:
    explicit GroupInfo(QWidget *parent = nullptr);
    explicit GroupInfo(QString name, QString head_Path, QWidget *parent = nullptr);
    ~GroupInfo();

private:
    Ui::GroupInfo *ui;
    QSharedPointer<GroupChat> Chat;

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;    //鼠标双击事件
};

#endif // GROUPINFO_H

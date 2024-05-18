#ifndef ADDGROUP_H
#define ADDGROUP_H

#include <QWidget>

namespace Ui {
class AddGroup;
}

class AddGroup : public QWidget
{
    Q_OBJECT

public:
    ~AddGroup();
    explicit AddGroup(QWidget *parent = nullptr);

private:
    Ui::AddGroup *ui;
};

#endif // ADDGROUP_H

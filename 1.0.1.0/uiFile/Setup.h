#ifndef SETUP_H
#define SETUP_H

#include <QWidget>

namespace Ui {
class Setup;
}

class Setup : public QWidget
{
    Q_OBJECT

public:
    explicit Setup(QWidget *parent = nullptr);
    ~Setup();

private:
    Ui::Setup *ui;
};

#endif // SETUP_H

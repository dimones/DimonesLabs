#ifndef LAB3_H
#define LAB3_H

#include <QMainWindow>

namespace Ui {
class Lab3;
}

class Lab3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lab3(QWidget *parent = 0);
    ~Lab3();

private:
    Ui::Lab3 *ui;
};

#endif // LAB3_H

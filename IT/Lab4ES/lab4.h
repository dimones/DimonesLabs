#ifndef LAB4_H
#define LAB4_H

#include <QMainWindow>
#include <stdio.h>
#include <math.h>
namespace Ui {
class Lab4;
}

class Lab4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lab4(QWidget *parent = 0);
    ~Lab4();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_addItem_clicked();

    void on_deleteItem_clicked();

private:
    Ui::Lab4 *ui;
};

#endif // LAB4_H

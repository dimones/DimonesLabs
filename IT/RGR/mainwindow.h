#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTableWidgetItem>
#include <QMainWindow>
#include <math.h>
#include <QDebug>
#include "functions.h"
#include "func.h"
#include <stdio.h>
#include <stdlib.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_pushButton_clicked();

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_tableWidget_itemPressed(QTableWidgetItem *item);

    void on_tableWidget_itemEntered(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTableWidgetItem>
#include <QMainWindow>
#include <math.h>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>

namespace Ui {
class MainWindow;
}


char colNames[25] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','V','X','Y','Z'};
struct elem{
  int type;
  int X,Y;
  char func[256];
  char value[256];
};

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

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    //Functions defenition:
    char getCharFromPos(int pos);
    int getPosFromChar(char c);
    char* getValueFromItem(int row,char col);
    char* getVariable(char *text);
    double isValue(char *t);
    int containsChar(char s[],char c);
    void deleteChar(char s[],char c);
    void checkItemsInList(QStringList &list);
    double SUM(char *text);
    double isFunc(char *t);
    char* calc(char *t);
    bool haveBrackets(char *t);
    void superParser(QTableWidgetItem *item);
    void Parser(QTableWidgetItem *item);



};

#endif // MAINWINDOW_H

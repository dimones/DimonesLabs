#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QDebug>
#include <math.h>
#include <QRegExp>

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

private:
    Ui::MainWindow *ui;
    char getCharFromPos(int pos);
    char* getValueFromItem(int row,char col);
    char* getVariable(char *text);
    char* getVariableBR(char *text);
    double isValue(char* t);
    int containsChar(char s[],char c);
    void deleteChar(char s[],char c);
    void checkListItems(QStringList &list);
    char* calc(char* text);
    double SUM(char* text);
    double isFunc(char* t);
    bool haveBrackets(char* t);
    void Parse(QTableWidgetItem *item);
    int  getPosFromChar(char c);
};

#endif // MAINWINDOW_H

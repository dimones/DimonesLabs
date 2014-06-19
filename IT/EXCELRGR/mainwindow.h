#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QtGui>
#include <QMainWindow>
#include <QTableWidgetItem>
#include <QDebug>
#include <math.h>
#include <QRegExp>
#include <QFileDialog>
#include <QKeyEvent>
#include "about.h"
#include <iostream>
#include <stdio.h>
#include <funchelp.h>
#include <QScrollBar>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    struct Cell{
        int type;
        char* func  = new char[256];
        char* value = new char[256];
        int y = 0;
        Cell(int type0,char *func0,char *value0,int y0)
        {
            type = type0;
            strcpy(func, func0);
            strcpy(value, value0);
            y = y0;
            //qDebug() << y << "  " << value << "  " << func << endl;
        }
        Cell *next;
    };
    struct element{
        Cell *head;
        Cell *tail;
        element()
        {
            head = NULL;
            tail = NULL;
        }
        void saveToFile(int x,FILE *fd)
        {
            for(Cell *t = this->head;t;t=t->next)
            {
                std::fwrite(&x,sizeof(int),1,fd);
                std::fwrite(&t->y,sizeof(int),1,fd);
                std::fwrite(&t->func,sizeof(char*),1,fd);
                std::fwrite(&t->value,sizeof(char*),1,fd);
            }
        }
        void printAll()
        {
            for(Cell *t = this->head;t;t=t->next)
            {
                qDebug() << t->y << "  " << t->value << "  " << t->func << endl;
            }
        }

        void pushTo(int y,char *value,char *func){
            if(isConsists(y))
            {
                for(Cell *t = this->head;t;t=t->next)
                    if(t->y==y)
                    {
                        strcpy(t->func, func);
                        strcpy(t->value, value);
                    }
            }
            else
                pushBack(y,func,value);
        }
        bool isConsists(int y)
        {
            for(Cell *t = this->head;t;t=t->next)
                if(t->y==y) return true;
            return false;
        }
        int getCountCell()
        {
            int r = 0;
            for(Cell *c = this->head;c;c=c->next)
                r++;
            return r;
        }
        void pushBack(int y,char *func, char *value)
        {
            Cell *c = new Cell(1,func,value,y);
            c->next = 0;
            //qDebug() << "init in push element" << y << "  " << func << "  " << value << endl;
            if(this->head==0)
            {
                this->head = c;
                this->tail = c;
                return;
            }
            this->tail->next = c;
            this->tail = c;
        }
        char *getFunc(int y)
        {
            if(isConsists(y))
                for(Cell *t = this->head;t;t=t->next)
                    if(t->y == y)
                        return t->func;
            return NULL;
        }
        char *getValue(int y)
        {
            if(isConsists(y))
                for(Cell *t = this->head;t;t=t->next)
                    if(t->y == y)
                        return t->value;
            return NULL;
        }
    };
    struct Node
    {
        int x = 0;
        struct element* elem = new element();
        struct Node* next;
        Node(int x0)
        {
            x = x0;
        }
    };
    struct List
    {
        int count_x,count_y;
        Node *head;
        Node *tail;
        List()
        {
            head = NULL;
            tail = NULL;
        }
        int getCountNode()
        {
            int r = 0;
            for(Node *c = this->head;c;c=c->next)
                r++;
            return r;
        }
        void saveToFile(char *nm)
        {
            FILE *fd = fopen(nm,"wb+");
            for(Node *t = this->head;t;t=t->next)
                t->elem->saveToFile(t->x,fd);
            fclose(fd);
        }
        void printAll()
        {
            for(Node *t = this->head;t;t=t->next)
            {
                t->elem->printAll();
            }
        }

        void pushBack(int x)
        {
            Node *t = new Node(x);
            t->elem = new element();
            t->next = 0;
            if(this->head==0)
            {
                this->head = t;
                this->tail = t;
                return;
            }
            this->tail->next = t;
            this->tail = t;
        }
        void pushTo(int x,int y,char *value,char *func)
        {
            qDebug() << "INPUT FUNC: " << func << "  VALUE: " << value << endl;
            if(isConsists(x))
            {
                for(Node *t = this->head;t;t=t->next)
                    if(t->x==x)
                        t->elem->pushTo(y, value, func);
            }
            else{
                pushBack(x);
                pushTo(x, y, value, func);
            }
        }
        bool isConsists(int x)
        {
            for(Node *t = this->head;t;t=t->next)
                if(t->x==x) return true;
            return false;
        }
        char *getFunc(int x,int y)
        {
            if(isConsists(x))
                for(Node *t = this->head;t;t=t->next)
                    if(t->x == x)
                        return t->elem->getFunc(y);
            return NULL;
        }
        char *getValue(int x,int y)
        {
            if(isConsists(x))
                for(Node *t = this->head;t;t=t->next)
                    if(t->x == x)
                        return t->elem->getValue(y);
            return NULL;
        }
        int *getIndexes()
        {
            int *ret= new int[getCountNode()];
            for(Node *t = this->head;t;t=t->next)
            {
                *ret = t->x;
                ret++;
            }
            return ret;
        }
    };
    List *T = new List();
private slots:
    void handlerVertical(int y);
    void handlerHorizontal(int x);
    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_tableWidget_itemEntered(QTableWidgetItem *item);

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_itemActivated(QTableWidgetItem *item);

    void on_tableWidget_itemPressed(QTableWidgetItem *item);

    void on_tableWidget_itemSelectionChanged();

    void on_pushButton_clicked();

    void on_btn_home_clicked();

    void on_btn_load_clicked();

    void on_btn_save_clicked();

    void on_action_triggered();

    void on_open_triggered();

    void on_save_triggered();

    void on_exit_triggered();

    void on_func_help_triggered();

    void on_all_help_triggered();

    void on_about_triggered();

    void on_tableWidget_viewportEntered();
    void on_runAll_clicked();

    void on_runAll_2_clicked();

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
private:
    Ui::MainWindow *ui;
    void newTable(int count_x, int count_y);
    char* getCharFromPos(int pos);
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
    void firstParse(QTableWidgetItem *item);
    bool isNumber(char t);
    bool isChar(char t);
    double min(char *t);
    double max(char *t);
    double pow(char *t);
    void resizeTable(int mode);
    char *mirror(char *in);
    char *getVariableBROutside(char *text);
};

#endif // MAINWINDOW_H

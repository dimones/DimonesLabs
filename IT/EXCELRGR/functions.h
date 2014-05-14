#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <QRegExp>
#include <QDebug>
#include <math.h>
#include <cstdlib>
#include <QTableWidgetItem>



struct item{
    int type;
    int X,Y;
    char func[256];
    char value[256];
};

class Functions
{
public:
    static const char colNames[];
    Functions();
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
};

#endif // FUNCTIONS_H

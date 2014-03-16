//
//  main.cpp
//  testmaccpp
//
//  Created by Дмитрий Богомолов on 15.03.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#include <iostream>
#include <stdio.h>

using namespace std;

struct date{
    int dd,mm,yy;
    void setDate(int dd0, int mm0, int yy0){    // встроенная функция установки даты
        dd=dd0; mm=mm0; yy=yy0;
        cout << dd << " " << mm <<" " << yy << endl;
    }
    void getDate(){                                       // встроенная функция чтения даты
        printf("\nday:"); scanf("%d",&dd);
        printf("month:"); scanf("%d",&mm);
        printf("year:"); scanf("%d",&yy);   // непосредственный доступ по имени поля
    }
    int cmpDate(date &T){                            // встроенная функция сравнения дат
        if (yy!=T.yy) return yy-T.yy;
        if (mm!=T.mm) return mm-T.mm;
        return dd-T.dd;
    }                                               // встроенные функции работы с файлом
    void loadDate(FILE *fd){ fscanf(fd,"%d%d%d",&dd,&mm,&yy); cout << "Date: " << dd << "." << mm << "." << yy << endl;  }
    void saveDate(FILE *fd){ fprintf(fd,"%d %d %d ",dd,mm,yy); }
    void showDate(){ printf("%02d.%02d.%04d ",dd,mm,yy); }
};
const int NP = 100;
const int N = 100;
struct exam
{
    char name[32],profName[32];
    date _date;
    int marks[NP];
    void loadMarks(FILE *fd,int i)
    {
        int temp;
        fscanf(fd,"%d",&temp);
        marks[i] = temp;
        cout << marks[i] << ",";
    }
    void addExam(char name0[],char profName0[])
    {
        strcpy(name0,name);
        strcpy(profName0, profName);// profName = profName0;
        cout << "You type name exam:" << name0 << " Имя преподавателя:" << profName0 << endl;
    }
    void loadExam(FILE *fd)
    {
        int np;
        fscanf(fd,"%s %s",profName,name);
        cout << "Имя экзамена:" << name << "  Имя преподавалеля " << profName << "  ";
        _date.loadDate(fd);        // вызов встроенной функции для поля birth
        fscanf(fd,"%d",&np);
        cout << "Кол-во оценок: " << np << " Оценки: ";
        for (int i=0;i<np;i++)
        {
            loadMarks(fd,i);
        }
        cout << endl;
    }
};
struct table
{
    exam _exams[N];
    int nn;
    void loadTable(char nm[]){           // встроенная функция загрузки из файла
        FILE *fd=fopen(nm,"rw+");
        if (fd==NULL) return;
        fscanf(fd,"%d",&nn);
        cout << "in file " << nn << " exams" << endl;
        if (nn>=N) return;            // вызов встроенной функции для поля TBL[i]
        for (int i=0;i<nn;i++) _exams[i].loadExam(fd);
        fclose(fd);
    }
};

table TT;

int main(int argc, const char * argv[])
{
    while(true)
    {
        cout << "\na(dd),v(iew),l(oad),s(ave)\nwhat to do" << endl;
        char t;
        cin >> t;
        switch (t) {
            case 'a':
            {
                cout << "a(dd) mode" << endl;
            }
                break;
            case 'v':
            {
                cout << "v(iew) mode" << endl;
                TT.loadTable("file.txt");
            }
                break;
            case 'l':
            {
                cout << "l(oad) mode" << endl;
               
            }
                break;
            case 's':
            {
                cout << "s(ave) mode" << endl;
            }
                break;
                
                
            default:
                cout << "non implemented mode" << endl;
                break;
        }
    }
    getchar();
    return 0;
}
/*
Определить структурированный тип и набор  функций для работы с таблицей записей, реализованной в массиве структур. В перечень функций входят:
·        ввод записи таблицы с клавиатуры;
·        загрузка и сохранение  таблицы в текстовом файле;
·        просмотр таблицы;
·        сортировка таблицы в порядке возрастания заданного поля;
·        поиск в таблице элемента с заданным значением поля или с наиболее близким к нему по значению;
·        удаление записи;
·        изменение (редактирование) записи;
·        вычисление с проверкой и использованием всех pfgbctq по заданному условию и формуле (например, общая сумма на всех счетах).
Перечень полей структурированной переменной:

    3. Название экзамена, дата экзамена, фамилия преподавателя,  количество оценок, оценки.*/
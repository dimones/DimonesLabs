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
        printf("\nДень:"); scanf("%d",&dd);
        printf("Месяц:"); scanf("%d",&mm);
        printf("Год:"); scanf("%d",&yy);   // непосредственный доступ по имени поля
    }
    int cmpDate(date &T){                            // встроенная функция сравнения дат
        if (yy!=T.yy) return yy-T.yy;
        if (mm!=T.mm) return mm-T.mm;
        return dd-T.dd;
    }
    // встроенные функции работы с файлом
    void loadDate(FILE *fd){ fscanf(fd,"%d%d%d",&dd,&mm,&yy); }
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
    int np;
    void loadMark(FILE *fd,int i)
    {
        int temp;
        fscanf(fd,"%d",&temp);
        marks[i] = temp;
    }
    void sortMarks()
    {
        //для упрощения взята сама тупая сортировка, пузырьком
        for(int i=0;i<np;i++)
            for(int j=i;j<np;j++)
                if(marks[i]>marks[j])
                {
                    int temp = marks[i];
                    marks[i] = marks[j];
                    marks[j] = temp; // LOL
                }
    }
    void saveMarks(FILE *fd)
    {
        fprintf(fd, "%d ",np);
        for(int i=0;i<np;i++)
            fprintf(fd, "%d ",marks[i]);
        fprintf(fd, "\n");
    }
    void showMarks()
    {
        for(int i = 0;i<np;i++)
            cout << marks[i]<< " ";
    }
    void getMarks(int n)
    {
        np = n;
        for(int i = 0;i < np;i++)
            cin >> marks[i];
    }
    void showExam()
    {
        cout << "Имя преподавателя: " << profName << ", имя экзамена: " << name << ", дата экзамена: ";
        _date.showDate();
        cout << ", кол-во оценок: " << np << ", оценки: ";
        showMarks();
        cout << endl;
    }
    void addExam(char name0[],char profName0[])
    {
        strcpy(name,name0);
        strcpy(profName, profName0);// profName = profName0;
        //cout << "You type name exam:" << name0 << " Имя преподавателя:" << profName0 << endl;
        _date.getDate();
        cout << "Введи кол-во оценок у преподавателя: ";
        int temp;
        cin >> temp;
        getMarks(temp);
    }
    void loadExam(FILE *fd)
    {
        fscanf(fd,"%s %s",profName,name);
        _date.loadDate(fd);        // вызов встроенной функции для поля birth
        fscanf(fd,"%d",&np);
        for (int i=0;i<np;i++)
        {
            loadMark(fd,i);
        }
    }
    void saveExam(FILE *fd)
    {
        for(int i=0;i<np;i++)
        {
            fprintf(fd, "%s %s ",name,profName);
            _date.saveDate(fd);
            saveMarks(fd);
        }
    }
};
struct table
{
    exam _exams[N];
    int nn = 0;
    void loadTable(char nm[]){
        FILE *fd=fopen(nm,"rw+");
        if (fd==NULL) return;
        fscanf(fd,"%d",&nn);
        cout << "in file " << nn << " exams" << endl;
        if (nn>=N) return;
        for (int i=0;i<nn;i++) _exams[i].loadExam(fd);
        fclose(fd);
    }
    void addExam(char name[],char profName[])
    {
        
        _exams[nn].addExam(name, profName);
        nn++;
        
    }
    void deleteExam(char name[])
    {
        for(int i=0;i<nn;i++)
        {
            if(strcmp(_exams[i].name, name)==0)
            {
                for(int j=i;j<nn-1;j++)
                    _exams[j]= _exams[j+1];
                nn--;
                break;
            }
        }
        
    }
    void editExam(char name[])
    {
        for(int i=0;i<nn;i++)
        {
            if(strcmp(_exams[i].name, name)==0)
            {
                cout << "Я нашел вашу запись =3, что хотите отредактировать?\n 1 - имя преподавателя\n2 - имя экзамена,\n3 - изменить дату экзамена\n4-изменить оценки" << endl;
                int mode; cin >> mode;
                switch(mode)
                {
                    case 1:
                    {
                        cout << "Введите имя преподавателя" << endl;
                        cin >> _exams[i].profName;
                    }
                        break;
                    case 2:
                    {
                        cout << "Введите имя экзамена" << endl;
                        cin >> _exams[i].name;
                    }
                        break;
                    case 3:
                    {
                        cout << "Введите дату" << endl;
                        _exams[i]._date.getDate();
                    }
                        break;
                    case 4:
                    {
                        cout << "Введите кол-во оценок" << endl;
                        int count; cin >> count;
                        cout << "Вы молодец, теперь введите ваши оценки через пробел или каждую через enter" << endl;
                        _exams[i].getMarks(count);
                    }
                        break;
                }
                break;
            }
        }
    }
    void sortMarks(char name[])
    {
        for(int i=0;i<nn;i++)
        {
            if(strcmp(_exams[i].name, name)==0)
            {
                _exams[i].sortMarks();
                break;
            }
        }
    }
    void sortTable(int mode)
    {
        switch(mode)
        {
            case 1:
            {
                //для упрощения взята сама тупая сортировка, пузырьком
                for(int i=0;i<nn;i++)
                    for(int j=i;j<nn;j++)
                        if(_exams[i].np>_exams[j].np)
                        {
                            exam temp = _exams[i];
                            _exams[i] = _exams[j];
                            _exams[j] = temp; // LOL
                        }
            }
                break;
        }
    }
    
    void viewExams()
    {
        for(int i = 0;i < nn;i++)
            _exams[i].showExam();
    }
    void saveTable(char nm[])
    {
        FILE *fd=fopen(nm,"w+");
        if (fd==NULL) return;
        cout << " Write " << nn << " exams into file. Begin" << endl;
        fprintf(fd, "%d\n",nn);
        for (int j=0;j<nn;j++) _exams[j].saveExam(fd);
        fclose(fd);
    }
};

table TT;

int main(int argc, const char * argv[])
{
    while(true)
    {
        cout << "\na(dd),v(iew),l(oad),E(dit),s(ave),d(elete),S(ort),c(ompare),e(xit)\nwhat to do" << endl;
        char t;
        cin >> t;
        switch (t) {
            case 'a':
            {
                cout << "a(dd) mode" << endl;
                cout << "Введите имя преподавателя и название экзамена" << endl;
                char name[32],name2[32];
                cin >> name >> name2;
                TT.addExam(name, name2);
            }
                break;
            case 'v':
            {
                cout << "v(iew) mode" << endl;
                TT.viewExams();
            }
                break;
            case 'l':
            {
                cout << "l(oad) mode" << endl;
                TT.loadTable("file.txt");
            }
                case 'E':
            {
                cout << "E(dit) mode " << endl;
                cout << "Вы можете изменить поле экзамена по имени,введите его" << endl;
                char name[32]; cin >> name;
                TT.editExam(name);
                
            }
                break;
            case 'S':
            {
                cout << "S(ort) mode " << endl;
                cout << "Сортировка по:\n 1 - кол-ву оценок\n 2 - внутри экзамена будут сортиоваться оценки" << endl;
                int mode; cin >> mode;
                switch (mode) {
                    case 1:
                    {
                        TT.sortTable(1);
                    }
                        break;
                    case 2:
                    {
                        cout << "Введите имя экзамена" << endl;
                        char name[32]; cin >> name;
                        TT.sortMarks(name);
                    }
                        break;
                    default:
                        break;
                }
            }
                break;
                case 'd':
            {
                cout << "d(elete) mode" << endl;
                cout << "Введите название экзамена для удаления" << endl;
                char name[32];
                cin >>name;
                TT.deleteExam(name);
                
            }
                break;
            case 's':
            {
                cout << "s(ave) mode" << endl;
                cout << "r(ewrite) or a(ppend)?" << endl;
                char c; cin >> c;
                switch (c) {
                    case 'r':
                    {
                        TT.saveTable("file.txt");
                    }
                        break;
                        
                    default:
                        break;
                }
                //TT.saveTable("file.txt");
            }
                case 'e':
            {
                cout << "Press enter to exit:" << endl;
                getchar();
                getchar();
                return 0;
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
·        ввод записи таблицы с клавиатуры; // done
·        загрузка и сохранение  таблицы в текстовом файле; //done
·        просмотр таблицы; // done
·        сортировка таблицы в порядке возрастания заданного поля;// all done
·        поиск в таблице элемента с заданным значением поля или с наиболее близким к нему по значению;
·        удаление записи;//done
·        изменение (редактирование) записи; // DONE!
·        вычисление с проверкой и использованием всех pfgbctq по заданному условию и формуле (например, общая сумма на всех счетах).// непонятно...
Перечень полей структурированной переменной:

    3. Название экзамена, дата экзамена, фамилия преподавателя,  количество оценок, оценки.*/
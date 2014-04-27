//
//  main.cpp
//  Lab1Chaban
//
//  Created by Дмитрий Богомолов on 27.04.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//
#include <iostream>
#include <string.h>
using namespace std;

string dayS[] = {"Понедельник","Вторник","Среда","Четверг","Пятница","Суббота","Воскресенье"};
int stat[7];
struct date{
    int mM,hH;//For time
    int dd,mm,yy;//For date
    void setDate(int dd0, int mm0, int yy0){    // встроенная функция установки даты
        dd=dd0; mm=mm0; yy=yy0;
        cout << dd << " " << mm <<" " << yy << endl;
    }
    void getDate(){// встроенная функция чтения даты
        cout << "Введите дату \n" << endl;
        printf("\nДень:"); scanf("%d",&dd);
        printf("Месяц:"); scanf("%d",&mm);
        printf("Год:"); scanf("%d",&yy);   // непосредственный доступ по имени поля
        printf("Часы:"); scanf("%d",&hH);
        printf("Минуты:"); scanf("%d",&mM);
    }
    int cmpDate(date &T){                            // встроенная функция сравнения дат
        if (yy!=T.yy) return yy-T.yy;
        if (mm!=T.mm) return mm-T.mm;
        return dd-T.dd;
    }
    // встроенные функции работы с файлом
    void loadDate(FILE *fd){ fscanf(fd,"%d%d%d%d%d",&hH,&mM,&dd,&mm,&yy); }
    void saveDate(FILE *fd){ fprintf(fd,"%d %d %d %d %d ",hH,mM,dd,mm,yy); }
    void showDate(){ printf("%02d:%02d  %02d.%02d.%04d ",hH,mM,dd,mm,yy); }
};

struct train{
    int number;//number train
    char dest[32];//destination
    bool days[7];//7 days in week,and 7 boolean for identify
    date date;
    short await;//In minutes
    void getWeek()
    {
        cout << "Подсказка - Для того чтобы заполнить ходимость поезда по дням,нужно записать нули и еденички, аналогично тому едет поезд или нет." << endl;
        for(int i = 0;i<7;i++)
        {
            cout << "Едет в  " << dayS[i] << ":";
            int temp; cin >> temp;
            switch(temp)
            {
                case 1: days[i] = true; break;
                case 2: days[i] = false; break;
                default: days[i] = false; break;
            }
        }
    }
    void addTrain(int number0,char dest0[],short await0)
    {
        number = number0; await = await0;
        strcpy(dest, dest0);
        date.getDate();
        getWeek();
    }
    void loadTrain(FILE *fd)
    {
        fscanf(fd, "%d%s%hd",&number,dest,&await);
        date.loadDate(fd);
        loadWeek(fd);
    }
    void loadWeek(FILE *fd)
    {
        for(int i = 0;i<7;i++)
        {
            fscanf(fd, "%d",&days[i]);
        }
    }
    void viewWeek()
    {
        for(int i=0;i<7;i++)
            if(days[i]!=0)
                cout << dayS[i]<<"  ";
    }
    void saveWeek(FILE *fd)
    {
        for(int i = 0;i<7;i++)
        {
            fprintf(fd, "%d ",days[i]);
        }
    }
    void getStat()
    {
        for(int i=0;i<7;i++)
        {
            if(days[i]!=0)
                stat[i]++;
        }
    }
    void saveTrain(FILE *fd)
    {
        fprintf(fd,"%d %s %d ",number,dest,await);
        date.saveDate(fd);
        saveWeek(fd);
    }
    int cmpBook(train &T,int mode){ // встроенная функция сравнения записей
        switch (mode){
            case 2 : return strcmp(dest,T.dest);
            //case 3 : return strcmp(nameBook, T.nameBook);
            case 4 : return date.cmpDate(T.date);
        }
        cout << "problem" << endl;
        return 0;
    }
    void viewTrain()
    {
        cout << "Номер поезда: " << number << "\r\nПункт назначения: " <<dest << "\r\nДни следования: " ;
        viewWeek();
        cout << "\r\nВремя прибытия: " ;
        date.showDate();
        cout << "\r\nВремя стоянки: "<< await << endl;
        cout << "________________________________________"<<endl;
    }
};
const int N = 100;
struct table
{
    train train[N];
    int curInFile,nn;
    void addTrain(int number0,char* dest0,short await0)
    {
        train[nn].addTrain(number0, dest0, await0); nn++;
    }
    void viewTrains()
    {
        for(int i = 0 ; i < nn ; i++)
        {
            cout << i << ": "; train[i].viewTrain();
        }
    }
    void loadTable(char nm[])
    {
        FILE *fd=fopen(nm,"rw+");
        if (fd==NULL) return;
        fscanf(fd,"%d ",&curInFile);
        cout << "in file " << nn+curInFile << " books" << endl;
        if (nn>=N) return;
        for (int i=nn;i<nn+curInFile;i++) train[i].loadTrain(fd);
        nn+=curInFile;
        fclose(fd);
    }
    void saveTable(char nm[])
    {
        FILE *fd=fopen(nm,"wb+");
        if (fd==NULL) return;
        cout << " Write " << nn << " books into file. Begin" << endl;
        fprintf(fd, "%d\n",nn);
        for (int j=0;j<nn;j++) train[j].saveTrain(fd);
        fclose(fd);
    }
    void deleteTrain(int mode)
    {
        switch(mode)
        {
            case 1:
            {
                cout << "Введите номер поезда для удаления" << endl;
                int temp; cin >> temp;
                for(int i=0;i<nn-1;i++)
                    if(train[i].number==temp)
                    {
                        for(int j=i;j<nn-1;j++)
                            train[j]= train[j+1];
                        break;
                    }
                nn--;
            } break;
            case 2:
            {
                cout << "Введите путь назначения для удаления" << endl;
                char temp[32]; cin >> temp;
                for(int i=0;i<nn-1;i++)
                    if(strcmp(train[i].dest,temp)==0){
                        for(int j=i;j<nn-1;j++)
                            train[j]= train[j+1];
                        break;
                    }
                nn--;
            } break;
            case 3:
            {
                cout << "Введите ID записи" << endl;
                int temp; cin >> temp;
                for(int j=temp;j<nn-1;j++)
                    train[j]= train[j+1];
                nn--;
            } break;
        }
    }
    void edit(int i)
    {
        cout << "Я нашел вашу запись =3, что хотите отредактировать?\n1: Номер поезда\n2: Пусть назначения\n3: Дни следования\n4: Дату прибытия\n5: Время стоянки" << endl;
        int mode; cin >> mode;
        switch(mode)
        {
            case 1:
            {
                cout << "Введите номер поезда" << endl;
                cin >> train[i].number;
            }
                break;
            case 2:
            {
                cout << "Введите путь назначения" << endl;
                cin >> train[i].dest;
            }
                break;
            case 3:
            {
                cout << "Введите дни следования" << endl;
                train[i].getWeek();
            }
                break;
            case 4:
            {
                cout << "Введите повторно дату" << endl;
                train[i].date.getDate();
            }
                break;
            case 5:
            {
                cout << "Введите время стоянки" << endl;
                cin >> train[i].await;
            }
                break;
        }
    }
    void editTrain()
    {
        cout << "По какому критерию вы хотите найти чтобы отредакировать?\n1: Номеру поезда\n2: Дате \n3: ID " << endl;
        int mode; cin >> mode;
        switch(mode)
        {
            case 1:
            {
                cout << "Введите номер поезда" << endl;
                int temp; cin >> temp;
                for(int i = 0;i<nn;i++)
                {
                    if(train[i].number == temp)
                    {
                        edit(i);
                        break;
                    }
                }
            }
                break;
            case 2:
            {
                cout << "Введите дату" << endl;
                for(int i = 0;i<nn;i++)
                {
                    date temp;
                    temp.getDate();
                    if(train[i].date.cmpDate(temp)==0)
                    {
                        edit(i);
                        break;
                    }
                }
            }
                break;
            case 3:
            {
                cout << "Введите ID записи из общего списка" << endl;
                int temp; cin >> temp;
                edit(temp);
            }
                break;
        }
    }
    void findTrain()
    {
        cout << "По какому критерию вы хотите найти?\n1: Номеру поезда\n2: Дате \n3: ID " << endl;
        int mode; cin >> mode;
        switch(mode)
        {
            case 1:
            {
                cout << "Введите номер поезда" << endl;
                int temp; cin >> temp;
                for(int i = 0;i<nn;i++)
                {
                    if(train[i].number == temp)
                    {
                        train[i].viewTrain();
                    }
                }
            }
                break;
            case 2:
            {
                //cout << "Введите дату" << endl;
                for(int i = 0;i<nn;i++)
                {
                    date temp;
                    temp.getDate();
                    if(train[i].date.cmpDate(temp)==0)
                    {
                        train[i].viewTrain();
                    }
                }
            }
                break;
            case 3:
            {
                cout << "Введите ID записи из общего списка" << endl;
                int temp; cin >> temp;
                train[temp].viewTrain();
            }
                break;
        }
    }
    void specFunc(int mode)
    {
        switch(mode)
        {
            case 1:
            {
                for(int i=0;i<nn;i++)
                    train[i].getStat();
                cout << "Статистика по дням:"<< endl;
                for(int i = 0;i<7;i++)
                    cout << dayS[i] << ": " << stat[i] << endl;
            }
                break;
            case 2:
            {
                double temp;
                for(int i = 0;i<nn;i++)
                    temp+=train[i].await;
                cout << "Среднее время стоянки: " << temp/nn << endl;
            }
                break;
            //default: cout << "not implemented mode" << endl;
        }
    }
    void sortTable(int mode)
    {
        switch(mode)
        {
            case 2:
            {
                int i,j,k;
                for (i=0;i<nn;i++){
                    for(j=k=i; j<nn;j++)
                        if (train[j].cmpBook(train[k], 2)<0) k=j;
                    struct train cc=train[i]; train[i]=train[k]; train[k]=cc;
                }
            }
                break;
            case 1:
            {
                for(int i=0;i<nn;i++)
                    for(int j=i;j<nn;j++)
                        if(train[i].number>train[j].number)
                        {
                            struct train temp = train[i];
                            train[i] = train[j];
                            train[j] = temp; // LOL
                        }
            }
                break;
            case 3:
            {
                int i,j,k;
                for (i=0;i<nn;i++){           // вызов встроенной функции сравнения записей
                    for(j=k=i; j<nn;j++)
                        if (train[j].cmpBook(train[k], 4)<0) k=j;
                    struct train cc=train[i]; train[i]=train[k]; train[k]=cc;
                }
            }
                break;
                
        }
    }
};

table TT;

int main(int argc, const char * argv[])
{
    while(true)
    {
        cout << "\na(dd),v(iew),l(oad),E(dit),s(ave),F(ind),d(elete),S(ort),f(unctions),e(xit)\nwhat to do" << endl;
        char t;
        cin >> t;
        switch (t) {
            case 'a':
            {
                cout << "a(dd) mode" << endl;
                cout << "Введите номер поезда,пункт назначения и время стоянки " << endl;
                char dest[32]; int number; short await;
                cin >> number >> dest >> await;
                TT.addTrain(number, dest, await);
            }
                break;
            case 'v':
            {
                cout << "v(iew) mode" << endl;
                if(TT.nn!=0)
                    TT.viewTrains();
                else cout << "Нет ни одной записи но вы можете загрузить нажав 'l' или добавить нажав 'a'" << endl;
                break;
            }
                break;
            case 'l':
            {
                cout << "l(oad) mode" << endl;
                TT.loadTable("file.txt");
            }
                break;
            case 'E':
            {
                cout << "E(dit) mode " << endl;
                TT.editTrain();
                break;
            }
                break;
            case 'f':
            {
                cout << "special final f(unctions)\n1: Статистика отправлений поездов по дням\n2: Среднее время стоянки" << endl;
                int mode; cin >> mode;
                switch (mode) {
                    case 1:
                    {
                        TT.specFunc(1);
                    }
                        break;
                    case 2:
                    {
                        TT.specFunc(2);
                    }
                        break;
                    default:
                        break;
                }
            }
                break;
            case 'F':
            {
                TT.findTrain();
            }
                break;
            case 'S':
            {
                cout << "S(ort) mode " << endl;
                cout << "Сортировка по:\n1: Номеру поезда\n2: Пункту назначения\n3: По дате" << endl;
                int mode; cin >> mode;
                TT.sortTable(mode);
            }
                break;
            case 'd':
            {
                cout << "d(elete) mode" << endl;
                cout << "Удаление произвоидтся по:\n1:Номеру поезда \n2:Времени прибытия\n3:По номеру в общем списке(предварительно необходимо узнать)." << endl;
                int id;
                cin >>id;
                //TT.deleteBook(id);
            }
                break;
            case 's':
            {
                cout << "s(ave) mode" << endl;
                cout << "r(ewrite) or w(rite) file with another name?" << endl;
                char c; cin >> c;
                switch (c) {
                    case 'r':
                    {
                        TT.saveTable("file.txt");
                    }
                        break;
                    case 'w':
                    {
                        cout << "Введите имя файла,на английском" <<  endl;
                        char name[32]; cin >> name;
                        TT.saveTable(name);
                    }
                        break;
                    default:
                        break;
                }
            }
                break;
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
//13. Номер поезда, пункт назначения, дни следования, время прибытия, время стоянки.
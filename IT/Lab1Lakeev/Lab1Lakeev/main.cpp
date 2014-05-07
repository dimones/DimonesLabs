//
//  main.cpp
//  Lab1Lakeev
//
//  Created by Дмитрий Богомолов on 07.05.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#include <iostream>
using namespace std;

struct cinema{
    char name[256];
    int number,count,price;
    void add(char name0[],int number0,int count0,int price0)
    {
        number = number0; count = count0; price = price0;
        strcpy(name,name0);
    }
    void show()
    {
        cout << "Название кинофильма: " << name<< " сеанс: " << number << "  кол-во зрителей: " << count << "  цена:" << price <<endl;
    }
    void load(FILE *fd)
    {
        fscanf(fd, "%s %d %d %d ",name,&number,&count,&price);
    }
    void save(FILE *fd)
    {
        fprintf(fd, "%s %d %d %d ",name,number,count,price);
    }
    int cmp(cinema &T,int mode){ // встроенная функция сравнения записей
        switch (mode){
            case 1 : return strcmp(name,T.name);
        }
        cout << "problem" << endl;
        return 0;
    }
};

struct table
{
    cinema _cinema[100];
    int nn = 0,curInFile = 0;
    void loadTable(char nm[])
    {
        FILE *fd = fopen(nm,"r");
        if(fd==NULL) return;
        fscanf(fd, "%d",&curInFile);
        if(nn>=100) return;
        for(int i = nn;i<nn+curInFile;i++) _cinema[i].load(fd);
        nn+=curInFile;
        fclose(fd);
    }
    void saveTable(char nm[])
    {
        FILE *fd=fopen(nm,"wb+");
        if (fd==NULL) return;
        cout << " Write " << nn << " books into file. Begin" << endl;
        fprintf(fd, "%d\n",nn);
        for (int j=0;j<nn;j++) _cinema[j].save(fd);
        fclose(fd);
    }
    void addCinema(char name0[],int number0,int count0,int price0)
    {
        _cinema[nn].add(name0,number0,count0,price0);
        nn++;
    }
    void viewAll()
    {
        for(int i = 0;i<nn;i++)
        {
            printf("%d %s",i,": ");
            _cinema[i].show();
        }
    }
    void edit(int i)
    {
        cout << "Я нашел вашу запись =3, что хотите отредактировать?\n1: Название кинофильма\n2: номер сеанса\n3: кол-во зрителей\n4: цену" << endl;
        int mode; cin >> mode;
        switch(mode)
        {
            case 1:
            {
                cout << "Название кинофильма" << endl;
                cin >> _cinema[i].name;
            }
                break;
            case 2:
            {
                cout << "Введите номер сеанса" << endl;
                cin >> _cinema[i].number;
            }
                break;
            case 3:
            {
                cout << "Введите кол-во зрителей" << endl;
                cin >> _cinema[i].count;
            }
                break;
                
            case 4:
            {
                cout << "Введите цену" << endl;
                cin >> _cinema[i].price;
            }
                break;
        }
    }
    void editExam()
    {
        cout << "По какому критерию вы хотите найти чтобы отредакировать?\n1: Название кинофильма\n2: номер сеанса \n3: ID " << endl;
        int mode; cin >> mode;
        switch(mode)
        {
            case 1:
            {
                cout << "Введите необходимую название сеанса" << endl;
                char temp[256]; cin >> temp;
                for(int i = 0;i<nn;i++)
                {
                    if(strcmp(_cinema[i].name, temp)==0)
                    {
                        edit(i);
                        break;
                    }
                }
            }
                break;
            case 2:
            {
                cout << "Введите номер сеанса" << endl;
                int temp; cin >> temp;
                for(int i = 0;i<nn;i++)
                {
                    if(_cinema[i].number == temp)
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
    void specFunc(int func)
    {
        switch(func)
        {
            case 1:
            {
                cout << "Введите название фильма " << endl;
                char name[256]; cin>> name;
                int temp;
                for(int i = 0;i<nn;i++)
                    if(strcmp(_cinema[i].name, name)==0)
                        temp++;
                cout << temp << " фильмов с этим названий" << endl;
            }
                break;
            case 2:
            {
                cout << "Среднее кол-во зрителей по:\n1: Всем сеансам\n2: по опр-му сеансу" << endl;
                int temp; cin >> temp;
                switch(temp)
                {
                    case 1:
                    {
                        double tempout,count;
                        for(int i = 0;i<nn;i++)
                        {
                                tempout+= _cinema[i].count;
                                count++;
                            
                        }
                        cout << "Статистика. Среднее кол-во зрителей: " << tempout/count << endl;
                    }
                        break;
                    case 2:
                    {
                        cout << "Введите имя сеанса:" << endl;
                        char temp[256]; cin >> temp;
                        double tempout,count;
                        for(int i = 0;i<nn;i++)
                        {
                            if(strcmp(_cinema[i].name, temp)==0){
                                tempout+= _cinema[i].count;
                                count++;
                            }
                        }
                        cout << "Статистика. Среднее кол-во зрителей: " << tempout/count << endl;
                    }
                        break;
                }
            }
                break;
            case 3:
            {
                cout << "Среднее цена по:\n1: Всем сеансам\n2: по опр-му сеансу" << endl;
                int temp; cin >> temp;
                switch(temp)
                {
                    case 1:
                    {
                        double tempout,count;
                        for(int i = 0;i<nn;i++)
                        {
                            tempout+= _cinema[i].price;
                            count++;
                            
                        }
                        cout << "Статистика. Среднее цена: " << tempout/count << endl;
                    }
                        break;
                    case 2:
                    {
                        cout << "Введите имя сеанса:" << endl;
                        char temp[256]; cin >> temp;
                        double tempout,count;
                        for(int i = 0;i<nn;i++)
                        {
                            if(strcmp(_cinema[i].name, temp)==0){
                                tempout+= _cinema[i].price;
                                count++;
                            }
                        }
                        cout << "Статистика. Среднее цена: " << tempout/count << endl;
                    }
                        break;
                }
            }
                break;
        }
    }
    void findBook(int mode)
    {
        switch(mode)
        {
            case 1:
            {
                cout << "Введите имя сеанса:" << endl;
                char name[256]; cin >> name;
                for(int i=0;i<nn;i++)
                {
                    if(strcmp(_cinema[i].name,name)==0)
                    {
                        cout << i << ": ";
                        _cinema[i].show();
                    }
                }
            }
                break;
            case 2:
            {
                cout << "Введие номеру сеанса" << endl;
                int temp; cin >> temp;
                for(int i=0;i<nn;i++)
                {
                    if(_cinema[i].number == temp)
                    {
                        cout << i << ": ";
                        _cinema[i].show();
                    }
                }
            }
                break;
            case 3:
            {
                cout << "Введите ID записи" << endl;
                int temp; cin >> temp;
                for(int i = 0 ;i<nn;i++)
                {
                    if(temp==i)
                    {
                        cout << i << ": ";
                        _cinema[i].show();
                    }
                }
            }
                break;
        }
    }
    void sortTable(int mode)
    {
        switch(mode)
        {
            case 1:
            {
                int i,j,k;
                for (i=0;i<nn;i++){
                    for(j=k=i; j<nn;j++)
                        if (_cinema[j].cmp(_cinema[k], 1)<0) k=j;
                    cinema cc=_cinema[i]; _cinema[i]=_cinema[k]; _cinema[k]=cc;
                }
            }
                break;
            case 2:
            {
                for(int i=0;i<nn;i++)
                    for(int j=i;j<nn;j++)
                        if(_cinema[i].number>_cinema[j].number)
                        {
                            cinema temp = _cinema[i];
                            _cinema[i] = _cinema[j];
                            _cinema[j] = temp; // LOL
                        }
            }
                break;
            case 3:
            {
                for(int i=0;i<nn;i++)
                    for(int j=i;j<nn;j++)
                        if(_cinema[i].count>_cinema[j].count)
                        {
                            cinema temp = _cinema[i];
                            _cinema[i] = _cinema[j];
                            _cinema[j] = temp; // LOL
                        }
            }
                break;
            case 4:
            {
                for(int i=0;i<nn;i++)
                    for(int j=i;j<nn;j++)
                        if(_cinema[i].price>_cinema[j].price)
                        {
                            cinema temp = _cinema[i];
                            _cinema[i] = _cinema[j];
                            _cinema[j] = temp; // LOL
                        }
            }
                break;
                
        }
    }
    void deleteBook(int mode)
    {
        switch(mode)
        {
            case 1:
            {
                cout << "Введите название сеанса для удаления" << endl;
                char temp[32]; cin >> temp;
                for(int i=0;i<nn-1;i++)
                    if(strcmp(_cinema[i].name,temp)==0)
                    {
                        for(int j=i;j<nn-1;j++)
                            _cinema[j]= _cinema[j+1];
                        break;
                    }
                nn--;
            } break;
            case 2:
            {
                cout << "Введите номер сеанса для удаления" << endl;
                int temp; cin >> temp;
                for(int i=0;i<nn-1;i++)
                    if(_cinema[i].number==temp){
                        for(int j=i;j<nn-1;j++)
                            _cinema[j]= _cinema[j+1];
                        break;
                    }
                nn--;
            } break;
            case 3:
            {
                cout << "Введите ID записи" << endl;
                int temp; cin >> temp;
                for(int j=temp;j<nn-1;j++)
                    _cinema[j]= _cinema[j+1];
                nn--;
            } break;
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
                cout << "Введите название кинофильма,номер сеанса,кол-во зрителей, цена " << endl;
                char temp[256]; int number,count,price;
                cin >> temp >> number >> count >> price;
                TT.addCinema(temp, number, count, price);
            }
                break;
            case 'v':
            {
                cout << "v(iew) mode" << endl;
                if(TT.nn!=0)
                    TT.viewAll();
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
                TT.editExam();
            }
                break;
            case 'f':
            {
                cout << "special final f(unctions)\n1: Кол-во сеансов кинофильма\n2: Средняя посещаемость\n3: Средняя цена" << endl;
                int mode; cin >> mode;
                TT.specFunc(mode);
                
            }
                break;
            case 'F':
            {
                cout << "Поиск по:\n1: Имя сеанса \n2: номер сеанса \n3: ID" << endl;
                int temp; cin >> temp;
                switch (temp) {
                    case 1:
                    {
                        TT.findBook(1);
                    }
                        break;
                    case 2:
                    {
                        TT.findBook(2);
                    }
                    case 3:
                    {
                        TT.findBook(3);
                    }
                        break;
                        
                    default:
                        break;
                }
            }
                break;
            case 'S':
            {
                cout << "S(ort) mode " << endl;
                cout << "Сортировка по:\n1: Имени сеанса\n2:номеру сеанса \n3: посещаемости\n4: цене" << endl;
                int mode; cin >> mode;
                switch (mode) {
                    case 1:
                    {
                        TT.sortTable(1);
                    }
                        break;
                    case 2:
                    {
                        TT.sortTable(2);
                    }
                        break;
                    case 3:
                    {
                        TT.sortTable(3);
                    }
                        break;
                    case 4:
                    {
                        TT.sortTable(4);
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
                cout << "Удаление произвоидтся по:\n1:Названию сеанса \n2:номеру сеансу\n3:ID." << endl;
                int id;
                cin >>id;
                TT.deleteBook(id);
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


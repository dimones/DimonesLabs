//
//  main.cpp
//  Lab1Yakovleva
//
//  Created by Дмитрий Богомолов on 08.04.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#include <iostream>

using namespace std;

struct date{
    int dd,mm,yy;
    void setDate(int dd0, int mm0, int yy0){    // встроенная функция установки даты
        dd=dd0; mm=mm0; yy=yy0;
        cout << dd << " " << mm <<" " << yy << endl;
    }
    void getDate(){// встроенная функция чтения даты
        cout << "Введите дату возврата \n" << endl;
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

struct book{
    char surName[32],nameBook[32]; //Фамилия и имя книги
    int number=0;//номер читательского билета
    date _return; //Дата возвращения книги
    void showBook()
    {
        cout << "Фамилия: " << surName << "\t Номер билета: " << number << "\t Имя книги: " <<nameBook << "\t Дата: ";
        _return.showDate();
        cout << endl;
    }
    void addBook(char surName0[],char nameBook0[],int number0)
    {
        strcpy(surName, surName0);
        strcpy(nameBook, nameBook0);
        number = number0;
        _return.getDate();
    }
    
    void loadBook(FILE *fd)
    {
        fscanf(fd,"%s %d %s",surName,&number,nameBook);
        _return.loadDate(fd);        // вызов встроенной функции для поля date
    }
    void saveBook(FILE *fd)
    {
        fprintf(fd,"%s %d %s ",surName,number,nameBook);
        _return.saveDate(fd);
    }
    int cmpBook(book &T,int mode){ // встроенная функция сравнения записей
        switch (mode){
            case 1 : return strcmp(surName,T.surName);      // сравнение по фамилии
            case 3 : return strcmp(nameBook, T.nameBook);   //сравнение по имени книги
            case 4 : return _return.cmpDate(T._return);       // сравнение по дате регистрации
        }
        cout << "problem" << endl;
        return 0;
    }
};

struct table
{
    book _books[N];
    int nn = 0,curInFile = 0;
    void loadTable(char nm[])
    {
        FILE *fd=fopen(nm,"rw+");
        if (fd==NULL) return;
        fscanf(fd,"%d ",&curInFile);
        cout << "in file " << nn+curInFile << " books" << endl;
        if (nn>=N) return;
        for (int i=nn;i<nn+curInFile;i++) _books[i].loadBook(fd);
        nn+=curInFile;
        fclose(fd);
    }
    void addBook(char surName[],char nameBook[],int number)
    {
        _books[nn].addBook(surName, nameBook, number);
        nn++;
    }
    void deleteBook(int mode)
    {
        switch(mode)
        {
            case 1:
            {
                cout << "Введите Фамилию для удаления" << endl;
                char temp[32]; cin >> temp;
                for(int i=0;i<nn-1;i++)
                    if(strcmp(_books[i].surName,temp)==0)
                    {
                        for(int j=i;j<nn-1;j++)
                            _books[j]= _books[j+1];
                        break;
                    }
                nn--;
            } break;
            case 2:
            {
                cout << "Введите ID для удаления" << endl;
                int temp; cin >> temp;
                for(int i=0;i<nn-1;i++)
                    if(_books[i].number==temp){
                        for(int j=i;j<nn-1;j++)
                            _books[j]= _books[j+1];
                        break;
                    }
                nn--;
            } break;
            case 3:
            {
                cout << "Введите ID записи" << endl;
                int temp; cin >> temp;
                for(int j=temp;j<nn-1;j++)
                    _books[j]= _books[j+1];
                nn--;
            } break;
        }
    }
    void findBook(int mode)
    {
        switch(mode)
        {
            case 1:
            {
                cout << "Введите фамилию" << endl;
                char name[32]; cin >> name;
                for(int i=0;i<nn;i++)
                {
                    if(strstr(_books[i].surName,name))
                    {
                        cout << i << ": ";
                        _books[i].showBook();
                    }
                }
            }
                break;
            case 2:
            {
                cout << "Введие номер билета" << endl;
                int temp; cin >> temp;
                for(int i=0;i<nn;i++)
                {
                    if(_books[i].number == temp)
                    {
                        cout << i << ": ";
                        _books[i].showBook();
                    }
                }
            }
                break;
            case 3:
            {
                cout << "Введие название книги" << endl;
                char name[32]; cin >> name;
                for(int i=0;i<nn;i++)
                {
                    if(strstr(_books[i].nameBook,name))
                    {
                        cout << i << ": ";
                        _books[i].showBook();
                    }
                }
            }
                break;
            case 4:
            {
                cout << "Введите ID записи" << endl;
                int temp; cin >> temp;
                for(int i = 0 ;i<nn;i++)
                {
                    if(temp==i)
                    {
                        cout << i << ": ";
                        _books[i].showBook();
                    }
                }
            }
                break;
        }
    }
    void viewBooks()
    {
        for(int i = 0;i < nn;i++)
        {
            printf("%d %s",i,": ");
            _books[i].showBook();
        }
    }
    void saveTable(char nm[])
    {
        FILE *fd=fopen(nm,"wb+");
        if (fd==NULL) return;
        cout << " Write " << nn << " books into file. Begin" << endl;
        fprintf(fd, "%d\n",nn);
        for (int j=0;j<nn;j++) _books[j].saveBook(fd);
        fclose(fd);
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
                        if (_books[j].cmpBook(_books[k], 1)<0) k=j;
                    book cc=_books[i]; _books[i]=_books[k]; _books[k]=cc;
                }
            }
                break;
            case 2:
            {
                for(int i=0;i<nn;i++)
                    for(int j=i;j<nn;j++)
                        if(_books[i].number>_books[j].number)
                        {
                            book temp = _books[i];
                            _books[i] = _books[j];
                            _books[j] = temp; // LOL
                        }
            }
                break;
            case 3:
            {
                int i,j,k;
                for (i=0;i<nn;i++){           // вызов встроенной функции сравнения записей
                    for(j=k=i; j<nn;j++)
                        if (_books[j].cmpBook(_books[k], 3)<0) k=j;
                    book cc=_books[i]; _books[i]=_books[k]; _books[k]=cc;
                }
            }
                break;
            case 4:
            {
                int i,j,k;
                for (i=0;i<nn;i++){           // вызов встроенной функции сравнения записей
                    for(j=k=i; j<nn;j++)
                        if (_books[j].cmpBook(_books[k], 4)<0) k=j;
                    book cc=_books[i]; _books[i]=_books[k]; _books[k]=cc;
                }
            }
                break;
                
        }
    }
    void edit(int i)
    {
        cout << "Я нашел вашу запись =3, что хотите отредактировать?\n1: Фамилию\n2: Номер билета,\n3: Название книги\n4: Дату возрата" << endl;
        int mode; cin >> mode;
        switch(mode)
        {
            case 1:
            {
                cout << "Введите фамилию" << endl;
                cin >> _books[i].surName;
            }
                break;
            case 2:
            {
                cout << "Введите номер билета" << endl;
                cin >> _books[i].number;
            }
                break;
            case 3:
            {
                cout << "Введите название книги" << endl;
                cin >> _books[i].nameBook;
            }
                break;
            case 4:
            {
                cout << "Введите повторно дату" << endl;
                _books[i]._return.getDate();
            }
                break;
        }
    }
    void editExam()
    {
        cout << "По какому критерию вы хотите найти чтобы отредакировать?\n1: Фамилия\n2: Номер билета \n3: Название книги \n4: ID " << endl;
        int mode; cin >> mode;
        switch(mode)
        {
            case 1:
            {
                cout << "Введите необходимую фамилию" << endl;
                char temp[32]; cin >> temp;
                for(int i = 0;i<nn;i++)
                {
                    if(strcmp(_books[i].surName, temp)==0)
                    {
                        edit(i);
                        break;
                    }
                }
            }
                break;
            case 2:
            {
                cout << "Введите номер билета" << endl;
                int temp; cin >> temp;
                for(int i = 0;i<nn;i++)
                {
                    if(_books[i].number == temp)
                    {
                        edit(i);
                        break;
                    }
                }
            }
                break;
            case 3:
            {
                cout << "Введите название книги(отредактируется первая найденная)" << endl;
                char temp[32]; cin >> temp;
                for(int i = 0;i<nn;i++)
                {
                    if(strcmp(_books[i].nameBook, temp)==0)
                    {
                        edit(i);
                        break;
                    }
                }
            }
                break;
            case 4:
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
                cout << "Введите название книги для подсчета" << endl;
                char nameBook[32]; cin >> nameBook;
                int temp = 0;
                for(int i = 0;i<nn;i++)
                {
                    if(strcmp(_books[i].nameBook,nameBook)==0) //для частичного поиска следует использовать if(strstr(_books[i].nameBook,nameBook))
                    {
                        temp++;
                    }
                }
                cout << temp <<" книг(и) выдано на руки" << endl;
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
                cout << "Введите Вашу фамилию, номер читательского билета, название книги " << endl;
                char name[32],name2[32]; int number;
                cin >> name >> number >> name2;
                TT.addBook(name, name2,number);
            }
                break;
            case 'v':
            {
                cout << "v(iew) mode" << endl;
                if(TT.nn!=0)
                TT.viewBooks();
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
                cout << "special final f(unctions)\n1: Кол-во книг выданных" << endl;
                int mode; cin >> mode;
                switch (mode) {
                    case 1:
                    {
                        TT.specFunc(1);
                    }
                        break;
                    default:
                        break;
                }
            }
                break;
            case 'F':
            {
                cout << "Поиск по:\n1: Фамилии \n2: По номеру билета \n3: Названии книги \n4: ID" << endl;
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
                    case 4:
                    {
                        TT.findBook(4);
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
                cout << "Сортировка по:\n1: Фамилии\n2: Номеру билета\n3: Названию книги\n4: По дате" << endl;
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
                cout << "Удаление произвоидтся по:\n1:Фамилии \n2:Номеру билета\n3:По номеру в общем списке." << endl;
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
#include <QCoreApplication>
#include <iostream>

using namespace std;

const int N = 5;
struct Node
{
    int elem;
    struct Node* next;
};

struct List
{
    Node *head;
    Node *tail;
};

void init(List *lst)
{
    lst->head = NULL;
    lst->tail = NULL;
}

void pushBack(List* lst,int elem)
{
    Node *t = new Node;
    t->elem = elem;
    t->next = 0;
    if(lst->head == 0)
    {
        lst->head = t;
        lst->tail = t;
        return;
    }
    lst->tail->next = t;
    lst->tail = t;
}

void print_list(List* lst)
{
    for(Node* tmp = lst->head; tmp; tmp = tmp->next)
        cout <<"Element : " << tmp->elem<< endl;
    cout << "_______________________________" <<endl;
}

List Function(List* lst1,List* lst2)
{
    List T; init(&T);
    for(Node* tmp = lst1->head;tmp;tmp = tmp->next)
    {
        for(Node* tmp2 = lst2->head;tmp2;tmp2 = tmp2->next)
        {
            if(tmp->elem == tmp2->elem)
            {
                pushBack(&T,tmp->elem);
            }
        }
    }
    return T;
}

int main(int argc, char *argv[])
{
    List A,B,OUT;
    init(&A); init(&B); init(&OUT);
    QCoreApplication a(argc, argv);
    while(true)
    {
        cout<<"1 to add List A\n2 to add List B\n3 to view List A\n4 to view List B\n5 to release quest" << endl;
        int t; cin>>t;
        switch (t) {
        case 1:
        {
            for(int i = 0;i<N;i++)
            {
                cout << "Введите содержимое списка элемента : " <<i+1 << endl;
                int temp; cin >> temp;
                pushBack(&A,temp);
            }

        }
            break;
        case 2:
        {
            for(int i = 0;i<N;i++)
            {
                cout << "Введите содержимое списка элемента : " <<i+1 << endl;
                int temp; cin >> temp;
                pushBack(&B,temp);
            }
        }
            break;
        case 3:
        {
            cout << "Вывод списка A:" <<endl;
            print_list(&A);
        }
            break;
        case 4:
        {
            cout << "Вывод списка B:" <<endl;
            print_list(&B);
        }
            break;
        case 5:
        {
            cout << "Result:" <<endl;
            OUT = Function(&A,&B);
            print_list(&OUT);
        }
            break;
        default:
            break;
        }
        cout << "_________________________________" <<endl;
    }
    return a.exec();
}

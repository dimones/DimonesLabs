#include "lab4.h"
#include "ui_lab4.h"
#include <iostream>
using namespace std;
Lab4::Lab4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lab4)
{
    ui->setupUi(this);
}

Lab4::~Lab4()
{
    delete ui;
}


//Реализовать рекурсивный алгоритм построения цепочки из имеющегося набора костей домино.

const int n=6;
int A[100000],B[100000];

//A - входной массив, B - массив решения, i - количество найденных костяшек, n - размерность входного массива
void path(int* A,int *B,int i, int n){
    int j,v;
    if(i==n) return; //условие завершения рекурсии - все костяшки проверены
    for(j=0;j<n;j++){
        if(A[j]==-1) continue;
        v=A[j];A[j]=-1; //отметить как выбранный
        if(i==0 || B[i-1]%10==v/10){B[i]=v; path(A,B,i+1,n);} //если первый раз или если половинки костяшек совпадают,
        v=v/10+(v%10)*10; //переворот костяшки
        if(i==0 || B[i-1]%10==v/10){B[i]=v; path(A,B,i+1,n);} //то запомнить костяшку в массив и запустить поиск для следующей костяшки
        A[j]=v; //восстановить элемент в массив
    }
}


void Lab4::on_pushButton_clicked()
{
    path(A,B,0,n);
    for(int i = 0;i<atoi(ui->lineEdit_3->text().toUtf8().data());i++)
    {
        QListWidgetItem *item = new QListWidgetItem(QString::number(B[i]));
        ui->listWidget_2->addItem(item);
    }
}

void Lab4::on_pushButton_2_clicked()
{
    ui->listWidget->clear();
    for(int i = 0;i<atoi(ui->lineEdit_3->text().toUtf8().data());i++)
    {
        int temp = rand()%66;
        QListWidgetItem *item = new QListWidgetItem(QString::number(temp));
        A[i] = temp;
        ui->listWidget->addItem(item);
    }
}

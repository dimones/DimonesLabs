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
int iteratorI = 0;
//const int n=6;
int A[100000],B[100000];

//A - входной массив, B - массив решения, i - количество найденных костяшек, n - размерность входного массива
void path(int A[],int B[],int i, int n){
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
     ui->listWidget_2->clear();
    path(A,B,0,iteratorI);
    for(int i = 0;i<iteratorI;i++)
    {
        QListWidgetItem *item = new QListWidgetItem(B[i]/10>=1?QString("%1 | %2").arg(QString::number(B[i]/10)).arg(B[i]%10):QString("0 | %1").arg(QString::number(B[i])));
        ui->listWidget_2->addItem(item);
    }
}


void Lab4::on_addItem_clicked()
{
    iteratorI++;
    //ui->listWidget->addItem(new QListWidgetItem(ui->lineEdit_2->text()));
    int temp = atoi(ui->lineEdit_2->text().toUtf8().constData());
    QListWidgetItem *item = new QListWidgetItem(temp/10>=1?QString("%1 | %2").arg(QString::number(temp/10)).arg(temp%10):QString("0 | %1").arg(QString::number(temp)));
    ui->listWidget->addItem(item);
    A[iteratorI] = temp;
    ui->lineEdit_2->clear();
}

void Lab4::on_deleteItem_clicked()
{
    //hui->listWidget->takeItem(ui->listWidget->selectedItems().removeFirst());
    //delete item;
}

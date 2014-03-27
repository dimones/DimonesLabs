
#include <stdio.h>
#include <iostream>
using namespace std;
//сумма m элементов массива, стоящих после *p
double F4(int *p)
{//p - указатель на нулевой элемент, q - указатель на следующий элемент. m - кол-во чисел, сумму которых нужно посчитать
    double *q, s; int m;
    for (q = (double*)(p + 1), m = *p, s = 0.; m >= 0; m--) s += *q++;
    return s;
}

int main()
{
    int* p;
    double s;
    double A[11] = { 5, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    p = (int*)A;
    s = F4(p);
    cout << s << endl;
    getchar();
}
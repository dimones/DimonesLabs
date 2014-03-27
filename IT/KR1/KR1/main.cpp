//
//  main.cpp
//  KR1
//
//  Created by Дмитрий Богомолов on 27.03.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#include <iostream>
using namespace std;

int F7(char *c){ //возвращает сумму цифр с строке
    int nc;
    for (nc=0; *c!=0;c++)
        if (*c>='0' && *c<='9')
            nc=nc+*c-'0';
    return nc;
}

char *F12(char *c, int &m){
    char *b=NULL;
    int k=0;
    for (;*c!=0;c++)
        if (*c!=' ') k++; //считает длину слова
        else{
            if (k!=0 && k>m) m=k,b=c-k; //запоминает максимум и начало слова максимальной длины
            k=0;
        }
    return b; //возвращает указатель начала слова
}
void F22(double x, char *c)
{
    x-=(int)x; //отбрасывает целую часть числа
    int i;
    for (*c++='.', i=1; i< 6; i++)
    {
        x *= 10.; //перенес первую цифру после точки в целую часть
        *c++=(int)x + '0'; //записал целую часть в строку
        x -= (int)x; //отбросил целую часть
    }
    *c='\0';
}
int main(int argc, const char * argv[])
{
    //_____________________________7
	char *s=new char[10];
	F7("howtoget100500chickens"); //returned 6
	delete[] s;
    //_____________________________12
    int max=0;
    F12("hello worlds", max); //returned 6
    //_____________________________22
    double in=8.3456756789;
    char v[10];
    F22(in, v); //returned 34567
    return 0;
}


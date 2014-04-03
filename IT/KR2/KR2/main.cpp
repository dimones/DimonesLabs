//
//  main.cpp
//  KR2
//
//  Created by Дмитрий Богомолов on 30.03.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#include <iostream>
using namespace std;


double F4(int *p)
{
    double *q,s;
    int m;
    for (q=(double*)(p+1), m=*p, s=0.; m>=0; m--)
        s+= *q++;
    return s;}


int main(int argc, const char * argv[])
{
    printf("%f.2",F4((int*)5));
    getchar();
    return 0;
}


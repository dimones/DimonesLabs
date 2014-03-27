//
//  main.cpp
//  Lab2
//
//  Created by Дмитрий Богомолов on 26.03.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#include <iostream>
using namespace std;
const int N = 100;

char** getWords(char * stroke)
{
    char * temp;
    for(int i =0;*stroke!=0;i++)
    {
        cout << *stroke;
    }
    getchar();
    return NULL;
}


int main(int argc, const char * argv[])
{
    cout << "Введите строку" << endl;
    char * temp =  new char[1000]; cin >> temp;
    char *forFuncTemp = new char[1000];
    strcpy(forFuncTemp, temp);
    getWords(temp);
    getchar();
    return 0;
}
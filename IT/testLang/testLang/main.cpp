//
//  main.cpp
//  testLang
//
//  Created by Дмитрий Богомолов on 17.03.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#include <iostream>
#include "compiler.h"

using namespace std;

int main(int argc, const char * argv[])
{
    bool _compile = false;
    if(argv != NULL)
    {
        int i = 0;
        while(argv[i]!=NULL)
        {
            if(argv[i]!=' '){
            if(strcmp(argv[i],"-")==0)
            {
                i++;
                if(strcmp(argv[i], "compile")==0)
                {
                    i+=2;
                    _compile = true;
                    if(argv[i]!=NULL)
                    {
                        string nameFile = argv[i];
                        cout << "name of source file " << nameFile << endl;
                    }
                }
                else if(strcmp(argv[i], "out")==0)
                {
                    if(_compile == true)
                    {
                        _compile = true;
                        i+=2;
                        if(argv[i]!=NULL)
                        {
                            string nameFile = argv[i];
                            cout << "name of out file " << nameFile << endl;
                        }
                    }
                    else cout << "You dont type '- compile' compiler will be exit" << endl;
                }
            }
            else
               {
                   cout << "wrong arguments, compiler will be exit" << endl;
               }
            } else continue;
        }
    }
    else cout << "no arguments, compiler will be exit" << endl;
    return 0;
}


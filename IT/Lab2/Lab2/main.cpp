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

char** getWords(char *stroke, int &count)
{
	int i = 0, n = 0, sz = 100;
	count = 0;
    stroke =  (char*)realloc(stroke, (sizeof(char*)+1));
    stroke = strcat(stroke, " ");
	char **output = new char*[N];
	output = (char**)malloc(N);
	while (*stroke != '\0')
	{
		if (*stroke != ' '){
			n++;
		}
		else if (n>0)
		{
			stroke -= n;
			char *temp = new char[n];
			temp = (char*)malloc(n);
			for (int j = 0; j<n; j++, stroke++)
			{
				temp[j] = *stroke;
			}
			n = 0;
			
			output[count] = temp;
			count++;
		}
		stroke++;
	}
	output[count] = NULL;
	return output;
}


int main(int argc, const char * argv[])
{
	cout << "Введите строку" << endl;
	char * temp = new char[1000]; cin.getline(temp, 999);
	char **mass = new char*[100];
	int count = 0;
	mass = (char**)malloc(N);
	mass = getWords(temp, count);
	cout << count << endl;
	while (**mass!=NULL)
	{
		cout << *mass << endl;
		mass++;
	}
	getchar();
    
	return 0;
}
//Quest
//2.      Функция получает строку текста и возвращает динамический массив указателей на слова.
//Каждое слово копируется в отдельный массив в динамической памяти.

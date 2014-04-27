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
	int n = 0;
	count = 0;
    stroke = strcat(stroke, " ");//Добавление в конец строки пробела для успешной работы алгоритма
	char **output = new char*[N];//Инициализация МУ
	while (*stroke!= '\0')//Считывание строки посимвольно пока не достигнет конца
	{
		if (*stroke != ' '){ //Пока не найден пробел увеличивааем переменную-счетчик длины слова
			n++;
		}
		else if (n>0)//После того как нашли пробел
		{
			stroke -= n; // Сдвинули указатель на длину слова
			char *temp = new char[n]; //Инициализировали новый массив для содержания в нем слова
			for (int j = 0; j<n; j++, stroke++) // Переносим его туда
			{
				temp[j] = *stroke;
			}
			n = 0; //Обнуление счетчика длины слова
			output[count] = temp; // Переносим указатель
			count++; //Увеличиваем кол-во слов
		}
		stroke++; //сдвигаем указатель на символ вперед
	}
	output[count] = NULL;//Затычка
	return output;
}


int main(int argc, const char * argv[])
{
	cout << "Введите строку" << endl;
	char * temp = new char[1000];//Иницализация строки для работы
    cin.getline(temp, 999);//получения текста из CLI
	char **mass = new char*[100]; //Выделяем МУ
	int count = 0; //Кол-во слов
	mass = getWords(temp, count); //Получаем массив
	cout << "Кол-во слов: " << count << endl;
	while (**mass!='\0') //Выводим полученный массив
	{
		cout << *mass << endl;
		mass++;
	}
	getchar();
	return 0;
}
//Quest
//2.Функция получает строку текста и возвращает динамический массив указателей на слова.
//Каждое слово копируется в отдельный массив в динамической памяти.

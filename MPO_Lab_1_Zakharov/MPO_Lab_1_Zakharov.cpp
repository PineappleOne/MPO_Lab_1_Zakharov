// Захаров Д.Б.
// Вариант №56 (База данных научных конференций)
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <filesystem>
#include "ScientificConfModel .h"
#include "Helper.h"
#include <fstream>
#include <direct.h>
#include <windows.h>
#include <ctime>
#include<string>
#include <cctype>   // для функции isspace
#include <iomanip>
using namespace std;

const char* PathLog = "C:\\MPP_Log\\";

/// <summary>
/// Логирование запуска приложения
/// </summary>
void LogingStart()
{
	int result = mkdir(PathLog);

	if (result == 0)
	{
		//ToDo: каталог создан
	}

	ofstream FileLog;
	FileLog.open("C:\\MPP_Log\\Log.txt", ios::app);

	if (FileLog)
	{
		char buffer[80];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		const char* format = "%A, %B %d, %Y %I:%M:%S";
		strftime(buffer, 80, format, timeinfo);
		FileLog << "Запуск приложения 'База данных научных конференций' ("<<buffer<<") " << endl;
	
	

	}
	else
	{
		//ToDo:Не удалось открыть файл
	}

}

/// <summary>
/// Функция для пункта меню "Запись в базу данных"
/// Спрашивает у пользователя основную информацию, собирает и генерирует строку для отправки в бд (файл в нашем случае))
/// </summary>
void AddDataToBD(ScientificConfModel h)
{
	string name;
	string theme;
	string contructData;
	struct tm tm;

	cout << "Запись в базу научных конференций \nВведите название конференции: " << endl;
	std::cin.ignore(32767, '\n'); // игнорируем символы перевода строки "\n" во входящем потоке длиной 32767 символов
	cin.sync();

	getline(std::cin, name);
	cin.sync();

	cout << "Введите тему конференции: ";
	getline(std::cin, theme);
	cin.sync();

	cout << "Введите Дату конференции в формате DD.MM.YYYY HH:MM: ";

	string date;
	getline(std::cin, date);
	cin.sync();

	const char* bufferDate = date.c_str();
	int day=-1, month=-1, year=-1, hours=-1, minutes=-1;

	sscanf(bufferDate, "%2d.%2d.%4d %2d:%2d",
		&day,
		&month,
		&year,
		&hours,
		&minutes);

	if ((day > 0 && day < 31)			&& 
		(month > 0 && month <= 12)		&& 
		(year >= 1900 && year <= 2200)	&& 
		(hours >= 0 && hours <= 24)		&& 
		(minutes >= 0 && minutes <= 60))
	{
		string constructor = "\t" + name + "\t" + theme + "\t" + bufferDate;
		h.SaveData(constructor);
	}
	else
	{
		cout << "Не правильный формат даты! \n";
		return;
	}


}

void showAllConf()
{
	const char* pathData = "C:\\MPP_Log\\Data.txt";
	const int N = 256; //Константный размер строки 
	char S[N] = { "" }; //В S будут считываться строки 
	ifstream in1(pathData); //Открыли файл для чтения
	while (!in1.eof()) //Будем читать информацию пока не дойдем до конца файла
	{
		in1.getline(S, N); //Построчное считывание информации в S 
		cout << setw(2) << S << endl; //Вывод очередной строки на экран 
	}
	in1.close();  //Закрыли открытый файл
}


int main()
{
	setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали
	LogingStart();

    cout << "База данных научных конференций !\n";
    system("color F0");  // Установка белого фона и черного текста
    bool flagMenu = true;
    Helper helper;
    ScientificConfModel scientificConfModel;

	do
	{

		cout << endl << "Выберите действие" << endl;
		cout << "1. Записать в базу новую научную конференцию" << endl;
		cout << "2. Вывести все  конференции" << endl;
		cout << "3. Вывести ближайшие научные конференции" << endl;
		cout << "--------------------" << endl;
		cout << "0. Выход" << endl;

		int variant = helper.get_variant(4);

		switch (variant)
		{
		case 1:
			system("cls");
			AddDataToBD(scientificConfModel);
			break;
		case 2:
			showAllConf();
			break;
		case 3:
			

			break;
		case 0:
			exit(0);
			break;
		}

	} while (flagMenu);
}


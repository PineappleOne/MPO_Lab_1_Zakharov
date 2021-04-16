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

string  PathLog = "C:\\MPP_Log\\";
string PathData = "C:\\MPP_Log\\Data.txt";


/// <summary>
/// Логирование запуска приложения
/// </summary>
void LogingStart(ScientificConfModel h)
{
	int result = mkdir(PathLog.c_str());

	if (result == 0)
	{
		//ToDo: каталог создан
	}

	ofstream FileLog;
	FileLog.open("C:\\MPP_Log\\Log.txt", ios::app);

	if (FileLog)
	{
		FileLog << "Запуск приложения 'База данных научных конференций' ("<<h.GetCurrentDate()<<") " << endl;
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
		system("cls");
		if (h.SaveData(constructor,PathData))
		{
			cout << "Конференция "<< name << " успешно добавлена" << endl;
			return;
		}
		else
		{
			cout << "Ошибка сохранения! \n";
			return;
		}
	}
	else
	{
		cout << "Не правильный формат даты! \n";
		return;
	}


}



int main()
{
	setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали
	
    system("color F0");  // Установка белого фона и черного текста
    bool flagMenu = true;
    Helper helper;
    ScientificConfModel scientificConfModel;
	int id = -1;

	LogingStart(scientificConfModel);
	cout << "База данных научных конференций !\n";
	do
	{

		cout << endl << "Выберите действие" << endl;
		cout << "1. Записать в базу новую научную конференцию" << endl;
		cout << "2. Вывести все  конференции" << endl;
		cout << "3. Вывести ближайшие даты научных конференции" << endl;
		cout << "4. Удалить конференцию по ID" << endl;
		cout << "5. Удалить все записи" << endl;
		cout << "--------------------" << endl;
		cout << "6. Выход" << endl;

		int variant = helper.get_variant(6);

		switch (variant)
		{
		case 1:
			system("cls");
			AddDataToBD(scientificConfModel);

			break;
		case 2:
			system("cls");
			scientificConfModel.showAllConf(PathData);
			break;
		case 3:
			system("cls");
			scientificConfModel.showAllConfWeek(PathData);
			break;
		case 4:
			system("cls");
			scientificConfModel.showAllConf(PathData);
			
			cout << endl << "Введите ID конференции для удаления" << endl;
			cin >> id;
			if (id != -1)
			{
				if (scientificConfModel.remove_line(PathData, id))
					cout << endl << "Запись успешно удалена";
			}
			break;
		case 5:
			system("cls");
			scientificConfModel.clear(PathData);
			cout << "Файл очищен";
			break;
		case 6:
			exit(0);
			break;
		}

	} while (flagMenu);
}


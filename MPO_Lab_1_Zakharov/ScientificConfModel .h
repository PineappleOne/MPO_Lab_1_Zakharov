#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <cmath>

class ScientificConfModel
{

public:
	ScientificConfModel();
	bool SaveData(string message);
	void showAllConf(string path);
	void showAllConfWeek(string path);
	string GetCurrentDate();
private:

};


ScientificConfModel::ScientificConfModel()
{
	
}




/// <summary>
/// Вывести все конференции в консоль
/// </summary>
/// <param name="path">Путь до файла с базой конференций</param>
inline void ScientificConfModel::showAllConf(string path)
{
	ifstream file(path);
	string line;
	string partial;
	vector<std::string> tokens;

	while (std::getline(file, line)) {

	
		istringstream iss(line);
		string token;
		while (getline(iss, token, '\t'))
			tokens.push_back(token);

		for (string token : tokens)
			if (token != "")
				cout << token << endl;

	
	}
}

/// <summary>
/// Вывести все даты конференции на ближайшую неделю
/// </summary>
/// <param name="path">Путь до файла с базой конференций</param>
inline void ScientificConfModel::showAllConfWeek(string path)
{
	ifstream file(path);
	string line;
	string partial;
	vector<std::string> tokens;

	string CurrentDate = GetCurrentDate();
	
	int dayCurrent = -1, monthCurrent = -1, yearCurrent = -1;
	
	sscanf(CurrentDate.c_str(), "%2d.%2d.%4d",
		&dayCurrent,
		&monthCurrent,
		&yearCurrent);

	cout << "ближайшие даты собраний" << endl;

	while (std::getline(file, line)) {

		tokens.clear();
		istringstream iss(line);
		string token;
		while (getline(iss, token, '\t'))
			tokens.push_back(token);

		for (string token : tokens)
		{
			if (token != "")
			{
				int day = -1, month = -1, year = -1, hours = -1, minute = -1;


				sscanf(token.c_str(), "%2d.%2d.%4d %2d:%2d",
					&day,
					&month,
					&year,
					&hours,
					&minute);


				if (dayCurrent + 7 > 31)
				{
					//Костыльный алгоритм перехода на следующий месяц
					//если текущий день + 7 больше 31, то вычитаем разницу, прибавляем к текущему месяцу +1
					//и создаем новую дату где день это результат разности
					int raznica = abs(31 - dayCurrent + 7);


					if (raznica <= day && monthCurrent + 1 == month && yearCurrent == year)
					{
						cout << endl << token << endl;
					}

				}
				else
				{
					if (day >= dayCurrent && day <= dayCurrent + 7 && monthCurrent == month && yearCurrent == year)
					{
						cout << endl << token << endl;
					}
				}


			}
			}
		}

	}


inline string ScientificConfModel::GetCurrentDate()
{
	char buffer[80];
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	const char* format = "%d.%m.%Y %H:%M";
	strftime(buffer, 80, format, timeinfo);
	string result(buffer);
	return result;
}


/// <summary>
/// Сохранить запись конференции
/// </summary>
/// <param name="message">Сообщение для записи</param>
inline bool ScientificConfModel::SaveData(string message)
{
	ofstream FileLog;
	FileLog.open("C:\\MPP_Log\\Data.txt", ios::app);

	if (FileLog)
	{
		char buffer[80];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		const char* format = "%d.%m.%Y %H:%M";
		strftime(buffer, 80, format, timeinfo);
		FileLog << "Запись добавленна:" << buffer << "\t"<< message << endl;
		return true;
	}
	else
	{
		//ToDo:Не удалось открыть файл
		return false;
	}
}




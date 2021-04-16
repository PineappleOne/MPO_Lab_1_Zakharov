#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iterator>


class ScientificConfModel
{

public:
	ScientificConfModel();
	bool SaveData(string message, string path);
	bool remove_line(string path, int id);
	void showAllConf(string path);
	void showAllConfWeek(string path);
	string GetCurrentDate();
	void clear(string path);

private:
	bool remove_line_from_index(string filename, size_t index);
	string last_line(string filename);
};


ScientificConfModel::ScientificConfModel()
{
	
}




/// <summary>
/// ������� ��� ����������� � �������
/// </summary>
/// <param name="path">���� �� ����� � ����� �����������</param>
inline void ScientificConfModel::showAllConf(string path)
{
	ifstream file(path);
	string line;
	string partial;
	vector<std::string> tokens;

	while (std::getline(file, line)) {

		tokens.clear();

		istringstream iss(line);
		string token;
		while (getline(iss, token, '\t'))
			tokens.push_back(token);

		for (string token : tokens)
			if (token != "")
				cout << token << endl;

		cout <<endl<< "******************" << endl;
	}

	if (tokens.empty())
	{
		cout << "��� ������� ������� �����������" << endl;
	}
}

/// <summary>
/// ������� ��� ���� ����������� �� ��������� ������
/// </summary>
/// <param name="path">���� �� ����� � ����� �����������</param>
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

	cout << "��������� ���� ��������" << endl;

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
					//���������� �������� �������� �� ��������� �����
					//���� ������� ���� + 7 ������ 31, �� �������� �������, ���������� � �������� ������ +1
					//� ������� ����� ���� ��� ���� ��� ��������� ��������
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
/// �������� ����
/// </summary>
inline void ScientificConfModel::clear(string path)
{
	//���������� ������ �������� ����- ������� ��� � ������ ����������
	//�� �� ���� �++
	fstream in(path, ios::out);
	in.close();
}


/// <summary>
/// ��������� ������ �����������
/// </summary>
/// <param name="message">��������� ��� ������</param>
inline bool ScientificConfModel::SaveData(string message,string path)
{
	ofstream FileData;
	string lastLine = last_line(path);
	vector<string> tokens;
	

	//�������� ��������� ID ������
		int lastId = -1;
		istringstream iss(lastLine);
		string token;
		tokens.clear();
		while (getline(iss, token, '\t'))
			tokens.push_back(token);

		
		if (!tokens.empty())
		{
			lastId = stoi(tokens[0]);
		}
			
	

	FileData.open(path, ios::app);

	if (FileData)
	{
		char buffer[80];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		const char* format = "%d.%m.%Y %H:%M";
		strftime(buffer, 80, format, timeinfo);


		FileData << ++lastId << "\t" << "������ ����������:" << buffer << message << endl;
		FileData.close();
		return true;
	}
	else
	{
		//ToDo:�� ������� ������� ����
		return false;
	}



}

//�������� ������ �� ��
inline bool ScientificConfModel::remove_line(string path, int id)
{
	ifstream file(path);
	string line;
	string partial;
	vector<string> lines;
	vector<string> tokens;

	lines.clear();
	
	//��������� �� ������
	for (string a;getline(file, a);)
	{
		lines.push_back(a);
	}

	//��������� ������ �� �����������
	for (string l : lines)
	{
		istringstream iss(l);
		string token;
		tokens.clear();
		while (getline(iss, token, '\t'))
			tokens.push_back(token);

		if (tokens[0] != "" && stoi(tokens[0]) == id)
		{
			auto it = std::find(lines.begin(), lines.end(), l);

			if (it == lines.end())
			{
				cout << endl << "�� ������� ������ ��� ��������" << endl;
				return false;
			}
			else
			{
				int index = it - lines.begin();
				return remove_line_from_index(path, index);
			
			}
		}
	}

	return false;

}

bool ScientificConfModel::remove_line_from_index(string filename, size_t index)
{
	 vector< string> vec;
	 ifstream file(filename);
	if (file.is_open())
	{
		 string str;
		while ( getline(file, str))
			vec.push_back(str);
		file.close();
		if (vec.size() < index)
			return false;
		vec.erase(vec.begin() + index);
		 ofstream outfile(filename);
		if (outfile.is_open())
		{
			 copy(vec.begin(), vec.end(),
				 ostream_iterator< string>(outfile, "\n"));
			outfile.close();
			return true;
		}
		return false;
	}
	return false;
}
/// <summary>
/// ���������� ������ �������� ��������� ������ �����
/// </summary>
string ScientificConfModel::last_line(string path)
{
	ifstream inClientFile(path, ios::in);

	if (!inClientFile)
	{
		
	}

	string buf;
	string result;
		while (getline(inClientFile, buf))
		{
			if (buf != "")
				result = buf;
		}
		return result;
}




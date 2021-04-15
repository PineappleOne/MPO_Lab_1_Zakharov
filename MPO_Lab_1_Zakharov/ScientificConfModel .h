#pragma once
#include <iostream>
using namespace std;
#include <fstream>

class ScientificConfModel
{

public:
	ScientificConfModel();
	void SaveData(string message);

private:

};

ScientificConfModel::ScientificConfModel()
{
	
}

/// <summary>
/// ��������� ������ �����������
/// </summary>
/// <param name="message">��������� ��� ������</param>
inline void ScientificConfModel::SaveData(string message)
{
	ofstream FileLog;
	FileLog.open("C:\\MPP_Log\\Data.txt", ios::app);

	if (FileLog)
	{
		char buffer[80];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		const char* format = "%A, %B %d, %Y %I:%M:%S";
		strftime(buffer, 80, format, timeinfo);
		FileLog << "������ ����������:" << buffer << "\t"<< message << endl;
	}
	else
	{
		//ToDo:�� ������� ������� ����
	}
}


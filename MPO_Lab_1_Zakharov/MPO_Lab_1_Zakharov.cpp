// Захаров Д.Б.
// Вариант №56 (База данных научных конференций)

#include <iostream>
#include "ScientificConfModel .h"
#include "Helper.h"
using namespace std;


int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "База данных научных конференций !\n";
    system("color F0");  // Установка белого фона и черного текста
    bool flagMenu = true;
    Helper helper;
    ScientificConfModel scientificConfModel;

	do
	{

		cout << endl << "Выберите действие" << endl;
		cout << "1. Вывести вектор на экран" << endl;
		cout << "2. Найти максимальный элемент" << endl;
		cout << "3. Заменить все элементы, значения которых меньше 0 на 0" << endl;
		cout << "4. Удалить из массива все повторяющиеся значения" << endl;
		cout << "--------------------" << endl;
		cout << "0. Выход" << endl;

		int variant = helper.get_variant(5);

		switch (variant)
		{
		case 1:
			
			break;
		case 2:
			
			break;
		case 3:
			
			break;
		case 4:

			break;
		case 0:
			exit(0);
			break;
		}

	} while (flagMenu);
}


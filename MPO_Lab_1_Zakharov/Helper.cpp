#define _CRT_SECURE_NO_WARNINGS
#include "Helper.h"
#include <xlocinfo>

int Helper::get_variant(int count)
{
	int variant;
	char s[100]; // строка для считывания введённых данных
	scanf("%s", s); // считываем строку

	// пока ввод некорректен, сообщаем об этом и просим повторить его
	while (sscanf(s, "%d", &variant) != 1 || variant < 1 || variant > count) {
		printf("Неккоректный ввод варианта,повторите снова: ");
		scanf("%s", s); // считываем строку повторно
	}

	return variant;
}


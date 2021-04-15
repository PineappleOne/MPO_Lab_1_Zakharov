#define _CRT_SECURE_NO_WARNINGS
#include "Helper.h"
#include <xlocinfo>

int Helper::get_variant(int count)
{
	int variant;
	char s[100]; // ������ ��� ���������� �������� ������
	scanf("%s", s); // ��������� ������

	// ���� ���� �����������, �������� �� ���� � ������ ��������� ���
	while (sscanf(s, "%d", &variant) != 1 || variant < 1 || variant > count) {
		printf("������������ ���� ��������,��������� �����: ");
		scanf("%s", s); // ��������� ������ ��������
	}

	return variant;
}


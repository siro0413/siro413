#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define count 6
#define num 50
//
//int main()
//{
//
//	int a = 0;
//
//	for (int i = 0; i < 5; i++)
//	{
//		for (int j = 0; j < i + 1; j++)
//		{
//			printf("*");
//		}
//		printf("\n");
//	}
//	printf("\n");
//
//	for (int i = 1; i <= 5; i++)
//	{
//		for (int j = 1; j <i+1; j++)
//		{
//			printf(" ");
//		}
//		for (int k = 5; k > i-1; k--)
//		{
//			printf("*");
//		}
//		printf("\n");
//	}
//
//	printf("\n");
//	for (int i = 1; i < 6; i++)
//	{
//		for (int j = 5; j+1 > i; j--)
//		{
//			printf("*");
//		}
//		printf("\n");
//	}
//	printf("\n");
//
//	for (int i = 1; i < 6; i++)
//	{
//		for (int j = 5; j+1 > i; j--)
//		{
//			printf(" ");
//		}
//		for (int k = 1; k < i+1; k++)
//		{
//			printf("*");
//		}
//		printf("\n");
//	}
//
//	for (int i = 0; i < 5; i++)
//		{
//		for (int k = 5; k > i; k--)
//			printf(" ");
//		for (int j = 1; j < (i * 2); j++)
//			printf("*");
//		printf("\n");
//	}
//	for (int i = 0; i < 5; i++)
//	{
//		for (int k = 0; k < i + 2; k++)
//			printf(" ");
//		for (int j = 5; j > (i * 2); j--)
//			printf("*");
//		printf("\n");
//	}
//	return 0;
//
//}

#define MAX_COUNT    6    // ������ �׸��� ����

int main()
{
	// ���� ���� ������ �迭
	int data[MAX_COUNT];
	// ���� ������ ���� ����� ����
	int i, j, temp = 0, loop;

	// ���� �߻��� ���� ���� ���� ���� �ð����� �����Ѵ�.
	srand((unsigned int)time(NULL));
	printf("������ �� : ");
	// 6���� ������ �����Ѵ�.
	for (i = 0; i < MAX_COUNT; i++) {
		// ������ ������ 0 ~ 100�� ������ �������� 100���� ���� �������� ����Ѵ�.
		data[i] = rand() % 100;
		// ������ ���� ����Ѵ�.
		Sleep(1000);

		printf("%d ", data[i]);
	}

	// �� ���� �����Ѵ�.
	printf("\n\n");

	// ���� ������ ����Ͽ� data �迭�� ���� ������������ �����Ѵ�.
	for (i = 0; i < MAX_COUNT - 1; i++) {
		for (j = 0; j < MAX_COUNT - i - 1; j++) {
			// �� ���� ���ڸ� ���Ͽ� �� ū ���ڸ� �ڷ� �ű��.
			if (data[j] > data[j + 1]) {
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
		}

	}

	// ������������ �� �����Ǿ����� Ȯ���Ѵ�.
	printf("\n���İ�� : ");
	Sleep(3000);

	for (i = 0; i < MAX_COUNT; i++) printf("%d ", data[i]);
	printf("\n");
	return 0;
}
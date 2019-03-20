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

#define MAX_COUNT    6    // 정렬할 항목의 개수

int main()
{
	// 난수 값을 저장할 배열
	int data[MAX_COUNT];
	// 버블 정렬을 위해 사용할 변수
	int i, j, temp = 0, loop;

	// 난수 발생을 위한 기준 값을 현재 시간으로 설정한다.
	srand((unsigned int)time(NULL));
	printf("생성된 값 : ");
	// 6개의 난수를 생성한다.
	for (i = 0; i < MAX_COUNT; i++) {
		// 생성된 난수가 0 ~ 100의 범위를 가지도록 100으로 나눈 나머지를 사용한다.
		data[i] = rand() % 100;
		// 생성된 값을 출력한다.
		Sleep(1000);

		printf("%d ", data[i]);
	}

	// 두 줄을 개행한다.
	printf("\n\n");

	// 버블 정렬을 사용하여 data 배열의 값을 오름차순으로 정렬한다.
	for (i = 0; i < MAX_COUNT - 1; i++) {
		for (j = 0; j < MAX_COUNT - i - 1; j++) {
			// 앞 뒤의 숫자를 비교하여 더 큰 숫자를 뒤로 옮긴다.
			if (data[j] > data[j + 1]) {
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
		}

	}

	// 오름차순으로 잘 정리되었는지 확인한다.
	printf("\n정렬결과 : ");
	Sleep(3000);

	for (i = 0; i < MAX_COUNT; i++) printf("%d ", data[i]);
	printf("\n");
	return 0;
}
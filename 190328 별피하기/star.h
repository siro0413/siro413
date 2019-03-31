#pragma once
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void removeCursor(void) //깜박임 없애기
{
	CONSOLE_CURSOR_INFO cur;

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);

	cur.bVisible = 0;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}
class stars {
public:
	int x;
	int y;
	int i;//별의 여부
};
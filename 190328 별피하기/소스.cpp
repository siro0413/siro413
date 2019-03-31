#include"star.h"
#define MAXY 22
#define MAXX 11
#define MINY 0
#define MINX 0




int main()
{
	int levelcnt;
	int level = 1, lms = 15 ;
	int lmcnt = 0;
	int score;
	int bs = 50;


	removeCursor();
	stars k[20];
	int cnt = 0;
	int die = 0;
	stars player;
	player.x = 5;
	player.y = 20;
	int t = 0;
	int a;
	for (int i = 0; i < 20; i++)
	{
		k[i].x = i;
		k[i].y = 1;
	}
	gotoxy(10, 10);
	std::cout << "º°¶Ëº°";
	Sleep(2000);
	system("cls");
	while (true)
	{
		levelcnt = level * lms;
		score = lmcnt * 10;
		if (score > 50)
			bs = score;
		system("cls");
		gotoxy(25, 5);
		gotoxy(25, 6);
		cout << "3¹ø ´êÀ¸¸é game over";
		gotoxy(25, 7);
		cout << "Level : " << level;
		gotoxy(25, 8);
		cout << "next Level : " << levelcnt - lmcnt;
		gotoxy(25, 9);
		cout << "score : " << score;
		gotoxy(25, 10);
		cout << "Best score : " << bs;
		for (int i = 0; i < 22; i++)
		{
			gotoxy(22, i);
			cout << "¡à";
		}
		for (int i = 0; i < 22; i++)
		{
			gotoxy(i, 21);
			cout << "¡à";
			i++;
		}
		for (int i = 0; i < 22; i++)
		{
			gotoxy(i, 0);
			cout << "¡à";
			i++;

		}
		for (int i = 0; i < 22; i++)
		{
			gotoxy(0, i);
			cout << "¡à";

		}
		gotoxy(player.x, player.y);
		cout << "¡á";

		if (kbhit())
		{
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
				player.x--;
			else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
				player.x++;
		}
		srand((char)time(NULL));
		a = rand() % 5 + rand() % 5 + rand() % 5 + rand() % 5;

		k[a].i = 1;
		cnt = 0;
		cnt++;


		for (int p = 0; p < 20; p++)
		{
			if (k[p].i == 1)
			{
				k[p].y++;
				if (k[p].x == player.x&&k[p].y == player.y || k[p].x + 1 == player.x&&k[p].y == player.y || k[p].x - 1 == player.x&&k[p].y == player.y)
				{
					if (die == 3)
					{
						die = 3;
					}
					system("cls");
					gotoxy(5, 10);
					cout << "Game Over" << endl;
					system("pause");
					die++;
				}
				gotoxy(k[p].x, k[p].y);
				cout << "¡Ù";
				if (k[p].y == 20)
				{
					k[p].y = 0;
					k[p].i = 0;
					lmcnt++;
					if (lmcnt == levelcnt)
						level++;
					break;
				}
			}
		}
		Sleep(50 - (level * 2));
		if (die == 3)
			break;
	}
	return 0;
	system("cls");
}

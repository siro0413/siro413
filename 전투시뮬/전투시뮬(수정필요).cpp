#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>


typedef struct characher
{
	char* symbol;
	short x;
	short y;
	char alive;


}Ch;

typedef struct ability
{
	int hp;
	int att;
	int def;
	int luck;
}St;



void drawmap(Ch map);
void drawmaping();
void drawmaping2();
void drawmaping3();
void drawmapingend();
void MoveCursor(short x, short y, const char* str);
void Battel();
void Battel2();
void Battel3();


Ch player = { (char*)"○",5,3 };
Ch monster1 = { (char*)"♠",3,2 };
Ch monster2 = { (char*)"♣",7,1};
Ch monster3 = { (char*)"◑",10,5 };

St playerst = { 200,32,21,20.0f };
St monster1st = { 100,12,16,5.0f };
St monster2st = { 50,20,20,30.0f };
St monster3st = { 70,32,15,15.0f };

int main()
{




	drawmaping();
	drawmap(player);
	drawmap(monster1);
	drawmap(monster2);
	drawmap(monster3);

	while (true)
	{
		char key = getch();
		_getch();

		if (key == 'q')
			break;

		switch (key)
		{
		case 'w': player.y--; break;
		case 's': player.y++; break;
		case 'a': player.x--; break;
		case 'd': player.x++; break;

		}

		
		drawmaping();

		
		//drawmapingend();

		

	}

	system("cls");


	return 0;
}

//x,y 좌표설정
void drawmap(Ch map)
{
	MoveCursor(map.x, map.y, map.symbol);
	MoveCursor(0, 10, "");

}


//1번몬스터와의 전투후 맵
void drawmaping()
{
	MoveCursor(0, 0, "┌─────────────┐");
	MoveCursor(0, 1, "│             │");
	MoveCursor(0, 2, "│             │");
	MoveCursor(0, 3, "│             │");
	MoveCursor(0, 4, "│             │");
	MoveCursor(0, 5, "│             │");
	MoveCursor(0, 6, "│             │");
	MoveCursor(0, 7, "│             │");
	MoveCursor(0, 8, "│             │");
	MoveCursor(0, 9, "└─────────────┘");

	drawmap(player);
	drawmap(monster1);
	drawmap(monster2);
	drawmap(monster3);
	// 몬스터의 4방향으로 이동시 전투
	if (player.x == monster1.x - 2 && player.y == monster1.y)
	{
		Battel();
	}
	else if (player.x == monster1.x + 2 && player.y == monster1.y)
	{
		Battel();
	}
	else if (player.y == monster1.y + 1 && player.x == monster1.x)
	{
		Battel();
	}
	else if (player.y == monster1.y - 1 && player.x == monster1.x)
	{
		Battel();
	}

	if (monster1st.hp <= 0)
	{

		drawmaping2();
		
	}
	if (playerst.hp <= 0)
	{

		drawmaping();
		
	}
	
}
//2번몬스터와의 전투후 맵
void drawmaping2()
{
	MoveCursor(0, 0, "┌─────────────┐");
	MoveCursor(0, 1, "│             │");
	MoveCursor(0, 2, "│             │");
	MoveCursor(0, 3, "│             │");
	MoveCursor(0, 4, "│             │");
	MoveCursor(0, 5, "│             │");
	MoveCursor(0, 6, "│             │");
	MoveCursor(0, 7, "│             │");
	MoveCursor(0, 8, "│             │");
	MoveCursor(0, 9, "└─────────────┘");

	drawmap(player);
	drawmap(monster2);
	drawmap(monster3);
	// 몬스터의 4방향으로 이동시 전투
	if (player.x == monster2.x - 2 && player.y == monster2.y)
	{
		Battel2();
	}
	else if (player.x == monster2.x + 2 && player.y == monster2.y)
	{
		Battel2();
	}
	else if (player.y == monster2.y + 1 && player.x == monster2.x)
	{
		Battel2();
	}
	else if (player.y == monster2.y - 1 && player.x == monster2.x)
	{
		Battel2();
	}

	if (monster2st.hp <= 0)
	{

		drawmaping3();

	}
	if (playerst.hp <= 0)
	{

		drawmaping2();

	}
}
//3번 몬스터와 전투후 맵
void drawmaping3()
{
	MoveCursor(0, 0, "┌─────────────┐");
	MoveCursor(0, 1, "│             │");
	MoveCursor(0, 2, "│             │");
	MoveCursor(0, 3, "│             │");
	MoveCursor(0, 4, "│             │");
	MoveCursor(0, 5, "│             │");
	MoveCursor(0, 6, "│             │");
	MoveCursor(0, 7, "│             │");
	MoveCursor(0, 8, "│             │");
	MoveCursor(0, 9, "└─────────────┘");

	drawmap(player);
	drawmap(monster3);
	// 몬스터의 4방향으로 이동시 전투
	if (player.x == monster3.x - 2 && player.y == monster3.y)
	{
		Battel3();
	}
	else if (player.x == monster3.x + 2 && player.y == monster3.y)
	{
		Battel3();
	}
	else if (player.y == monster3.y + 1 && player.x == monster3.x)
	{
		Battel3();
	}
	else if (player.y == monster3.y - 1 && player.x == monster3.x)
	{
		Battel3();
	}
	if (monster3st.hp <= 0)
	{

		drawmapingend();

	}
	if (playerst.hp <= 0)
	{

		drawmaping3();

	}

}
//모든 몬스터와 전투후 맵
void drawmapingend()
{
	MoveCursor(0, 0, "┌─────────────┐");
	MoveCursor(0, 1, "│             │");
	MoveCursor(0, 2, "│             │");
	MoveCursor(0, 3, "│             │");
	MoveCursor(0, 4, "│             │");
	MoveCursor(0, 5, "│             │");
	MoveCursor(0, 6, "│             │");
	MoveCursor(0, 7, "│             │");
	MoveCursor(0, 8, "│             │");
	MoveCursor(0, 9, "└─────────────┘");

	drawmap(player);
	//Sleep(2000);
	system("cls");
	Sleep(1000);
	printf("승리하였습니다.");
}


//1번 배틀 시뮬
void Battel()
{
	printf("적과 만났습니다.");
	Sleep(1000);
	system("cls");
	printf("잠시후 전투가 시작됩니다.");
	Sleep(2000);
	system("cls");
	printf("전투 시작\n");
	srand(time(0));
	for (;;)
	{
		int luckm = rand() % 10 + 1;
		int luckp = rand() % 20 + 1;

		if (luckm <= 3)
		{
			printf("공격회피\n\n");
			monster1st.hp = monster1st.hp - 0;
			Sleep(2000);
		}
		else
		{
			printf("공격성공\n\n");
			monster1st.hp = monster1st.hp - (playerst.att - monster1st.def);
			printf("몬스터의 체력은 현재 %d입니다.\n", monster1st.hp);
			Sleep(2000);
		}

		if (monster1st.hp <= 0)
		{
			printf("플레이어가 승리하였습니다.\n");
			Sleep(2000);
			system("cls");
			drawmaping2();
			break;
		}


		if (luckm == 1)
		{
			printf("공격회피\n\n");
			playerst.hp = playerst.hp - 0;
			Sleep(2000);
		}
		else
		{
			printf("공격성공\n\n");
			playerst.hp = playerst.hp - (playerst.def- monster1st.att);
			printf("플레이어의 체력은 현재 %d입니다.\n", playerst.hp);
			Sleep(2000);

		}

		if (playerst.hp <= 0)
		{
			printf("몬스터가 승리하였습니다.\n");
			Sleep(2000);
			system("cls");
			drawmaping();
			break;
		}

	}


	/*if (monster1st.hp == 100)
		drawmaping2();
	else if (monster1st.hp > 100)
		drawmaping();
	*/

}
//2번 배틀 시뮬
void Battel2()
{
	printf("적과 만났습니다.");
	Sleep(1000);
	system("cls");
	printf("잠시후 전투가 시작됩니다.");
	Sleep(2000);
	system("cls");
	printf("전투 시작\n");
	srand(time(0));
	for (;;)
	{
		int luckm = rand() % 30 + 1;
		int luckp = rand() % 20 + 1;

		if (luckm <= 3)
		{
			printf("공격회피\n\n");
			monster2st.hp = monster2st.hp - 0;
			Sleep(2000);
		}
		else
		{
			printf("공격성공\n\n");
			monster2st.hp = monster2st.hp - (playerst.att - monster2st.def);
			printf("몬스터의 체력은 현재 %d입니다.\n", monster2st.hp);
			Sleep(2000);
		}

		if (monster2st.hp <= 0)
		{
			printf("플레이어가 승리하였습니다.\n");
			Sleep(2000);
			system("cls");
			drawmaping3();
			break;
		}


		if (luckm == 1)
		{
			printf("공격회피\n\n");
			playerst.hp = playerst.hp - 0;
			Sleep(2000);
		}
		else
		{
			printf("공격성공\n\n");
			playerst.hp = playerst.hp - (playerst.def - monster2st.att);
			printf("플레이어의 체력은 현재 %d입니다.\n", playerst.hp);
			Sleep(2000);

		}

		if (playerst.hp <= 0)
		{
			printf("몬스터가 승리하였습니다.\n");
			Sleep(2000);
			system("cls");
			drawmaping2();
			break;
		}
	}
}
//3번 배틀 시뮬
void Battel3()
{
	printf("적과 만났습니다.");
	Sleep(1000);
	system("cls");
	printf("잠시후 전투가 시작됩니다.");
	Sleep(2000);
	system("cls");
	printf("전투 시작\n");
	srand(time(0));
	for (;;)
	{
		int luckm = rand() % 20 + 1;
		int luckp = rand() % 20 + 1;

		if (luckm <= 2)
		{
			printf("공격회피\n\n");
			monster3st.hp = monster3st.hp - 0;
			Sleep(2000);
		}
		else
		{
			printf("공격성공\n\n");
			monster3st.hp = monster3st.hp - (playerst.att - monster3st.def);
			printf("몬스터의 체력은 현재 %d입니다.\n", monster3st.hp);
			Sleep(2000);
		}

		if (monster3st.hp <= 0)
		{
			printf("플레이어가 승리하였습니다.\n");
			Sleep(2000);
			system("cls");
			drawmapingend();
			break;
		}


		if (luckm == 1)
		{
			printf("공격회피\n\n");
			playerst.hp = playerst.hp - 0;
			Sleep(2000);
		}
		else
		{
			printf("공격성공\n\n");
			playerst.hp = playerst.hp - (monster3st.att- playerst.def);
			printf("플레이어의 체력은 현재 %d입니다.\n", playerst.hp);
			Sleep(2000);

		}

		if (playerst.hp <= 0)
		{
			printf("몬스터가 승리하였습니다.\n");
			Sleep(2000);
			system("cls");
			drawmaping3();
			break;
		}
	}
}

void MoveCursor(short x, short y, const char* str)
{
	COORD coord = { x,y };
	SetConsoleCursorPosition
	(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
	printf("%s", str);
}
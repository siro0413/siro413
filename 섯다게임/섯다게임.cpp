#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <iostream>

struct Player
{
	char* name;
	int money;
	int call;

};
Player play = { (char*)"しろ",100'000,0 };
Player com = { (char*)"computer",1'000'000,0 };
void loadFile();
void saveFile();
void mainpage();
void gamepage();
void win();
void lose();
void draw();
//void gamestart();






int main()
{
	loadFile();
	mainpage();
	while (true)
	{
		gamepage();

	}


	return 0;
}
//파일 저장
void saveFile()
{
	//파일 쓰기
	FILE* fp = fopen("player.dat", "wb");
	fwrite(&play, sizeof(Player), 1, fp);
	fwrite(&com, sizeof(Player), 1, fp);

	fclose(fp);
}
//파일 로드
void loadFile()
{
	//파일 열기
	FILE* fp = fopen("player.dat", "rb");
	if (fp == NULL) {
		FILE* fp2 = fopen("player.dat", "wb");
		fwrite(&play, sizeof(Player), 1, fp2);
		fwrite(&com, sizeof(Player), 1, fp);

		fclose(fp2);
	}
	else {
		fread(&play, sizeof(Player), 1, fp);
		fread(&com, sizeof(Player), 1, fp);
	}
	fclose(fp);


}
//파일 저장
//void saveFile2()
//{
//	//파일 쓰기
//	FILE* fp = fopen("com.dat", "wb");
//	fwrite(&com, sizeof(Player), 1, fp);
//	fclose(fp);
//}
////파일 로드2
//void loadFile2()
//{
//	//파일 열기
//	FILE* fp = fopen("com.dat", "rb");
//	if (fp == NULL) {
//		FILE* fp2 = fopen("com.dat", "wb");
//		fwrite(&com, sizeof(Player), 1, fp2);
//		fclose(fp2);
//	}
//	else {
//		fread(&play, sizeof(Player), 1, fp);
//	}
//	fclose(fp);
//
//
//}

//섯다 메인페이지
void mainpage()
{
	printf("\n\n\n");
	
                                                  
	printf("\t\t\t	                  0000                             \n");
	printf("\t\t\t	                  000 000                          \n");
	printf("\t\t\t	       00000       00   0                          \n");
	printf("\t\t\t	       0   000      0   0                          \n");
	printf("\t\t\t	        0    0      0   0                          \n");
	printf("\t\t\t	       00   0       0   0                          \n");
	printf("\t\t\t	       0  00    00000 0 0               000        \n");
	printf("\t\t\t	      0   0     000000  0              000 000     \n");
	printf("\t\t\t	     0 000000        0  0                0  00     \n");
	printf("\t\t\t	    00000 000000     0000            00  00  0     \n");
	printf("\t\t\t	   0000    00000     0000 0000000000000   0 00     \n");
	printf("\t\t\t	 0000                000  000   0000      0 0      \n");
	printf("\t\t\t	              000000  0    00  0          0 00     \n");
	printf("\t\t\t	               000000       0000          000      \n");
	printf("\t\t\t	               000000       0000          000 00   \n");
	printf("\t\t\t	              00000         0000          00000000 \n");
	printf("\t\t\t	            0000000000      0000      000 000  0   \n");
	printf("\t\t\t	           0000  0000000    00000 000000  000      \n");
	printf("\t\t\t	        00000      00000    000000000     000      \n");
	printf("\t\t\t	                             00000        000      \n");
	printf("\t\t\t	                                          000      \n");
	printf("\t\t\t	                                          000      \n");
	printf("\t\t\t	                                           0       \n");

	printf("\n\n");
	printf("\t\t\t\t         아무키 입력시 시작\n");
	printf("\t\t\t\t         q를 입력시 종료\n");




	char key = getch();
	_getch();

	switch (key)
	{
	case 'q': break;
	case 'Q': break;
	default: gamepage();

		break;
	}

}
void gamepage()
{
	srand((unsigned int)time(0));

	int playcard[2] = { 0,0 }; //카드를 입력받기 위한 어레이
	int comcard[2] = { 0,0 }; //카드를 입력받기 위한 어레이
	int hide[2] = { 0,0 };

	int i = 0, k = 0;
	for (int i = 0; i < 11; i++)
	{
		playcard[0] = rand() % 10 + 1;
	}

	for (int k = 0; k < 11; k++)
	{
		playcard[1] = rand() % 10 + 1;
	}

	for (int i = 0; i < 11; i++)
	{
		hide[0] = rand() % 10 + 1;
		comcard[0] = hide[0];
		hide[0] = '*';
	}

	for (int k = 0; k < 11; k++)
	{
		hide[1] = rand() % 10 + 1;
		comcard[1] = hide[1];
		hide[1] = '*';

	}
	system("cls");
	printf("현재 보유금액 : %d								상대 보유금액 : %d\n\n", play.money, com.money);

	printf("					현재 배팅액 : \n");


	printf("나의패 :	%d,%d							상대 패 :  %c,%c \n\n", playcard[0], playcard[1], hide[0], hide[1]);

	printf("배팅금액 입력해주세요 : ");


	play.call = 0;
	com.call = 0;

	Sleep(1000);
	int temp = 0;
Recall:
	scanf(" %d", &play.call);

	if (play.money < play.call) {
		printf("배팅금액이 현재돈보다 큽니다.\n");
		goto Recall;
	}
	else if (play.money == play.call) {
		printf("올인했습니다.\n");
		play.money = play.call;
	}
	else {
		printf("%d 배팅했습니다.\n", play.call);
		play.money = play.money - play.call;
	}
	Sleep(1000);
	printf("컴퓨터가 배팅중 입니다\n");
	Sleep(1000);
	for (int i = 0; i < 10; i++)
	{
	Reroll:
		temp = rand() % 100000 + 1;
		if (temp < 20 || temp > 1001) {
			goto Reroll;
		}
		com.call = temp;
	}
	printf("컴퓨터가 %d 배팅했습니다.\n", com.call);
	com.money = com.money - com.call;
	Sleep(1000);
	system("cls");
	printf("현재 보유금액 : %d								상대 보유금액 : %d\n\n", play.money - play.call, com.money - com.call);

	printf("					현재 배팅액 : %d\n", play.call + com.call);


	printf("나의패 :	%d,%d							상대 패 :  %d,%d \n\n", playcard[0], playcard[1], comcard[0], comcard[1]);


	//38,18광땡
	if (playcard[0] == 3 && playcard[1] == 8 != playcard[0] == 8 && playcard[1] == 3)
	{
		printf("38광땡!");
		win();
		Sleep(1000);
	}
	else if (comcard[0] == 3 && comcard[1] == 8 != comcard[0] == 8 && comcard[1] == 3)
	{
		printf("38광땡!");
		lose();
		Sleep(1000);
	}
	else if (playcard[0] == 1 && playcard[1] == 8 != playcard[0] == 8 && playcard[1] == 1)
	{
		printf("18광땡!");
		win();
		Sleep(1000);
	}
	else if (comcard[0] == 1 && comcard[1] == 8 != comcard[0] == 8 && comcard[1] == 1)
	{
		printf("18광땡!");
		lose();
		Sleep(1000);
	}
	//그외 끗
	else if ((playcard[0] + playcard[1])%10 > (comcard[0] + comcard[1]) % 10)
		win();

	else if ((playcard[0] + playcard[1])% 10 < (comcard[0] + comcard[1]) % 10)
		lose();

	else if (playcard[0] == playcard[0] && comcard[1] == comcard[1])
	{
		if (playcard[0] > comcard[0])
			win();
		else if (playcard[0] < comcard[0])
			lose();
		else if (playcard[0] = comcard[0])
			draw();
	}

	else if (playcard[0] == playcard[1] || comcard[0] != comcard[1])
		win();
	else if (comcard[0] == comcard[1] || playcard[0] != playcard[1])
		lose();
	saveFile();
}


	void win()
	{
		printf("승리했습니다.\n");
		play.money = play.money + play.call + com.call;
		com.money = com.money - com.call;
		Sleep(3000);

	}
	void lose()
	{
		printf("패배했습니다.\n");
		com.money = com.money + play.call + com.call;
		play.money = play.money - play.call;
		Sleep(3000);

	}
	void draw()
	{
		printf("무승부입니다.\n");
		play.money = play.money + play.call;
		com.money = com.money + com.call;
		Sleep(3000);

	}

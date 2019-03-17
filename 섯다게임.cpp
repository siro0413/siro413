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
Player play = { (char*)"����",100'000,0 };
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
//���� ����
void saveFile()
{
	//���� ����
	FILE* fp = fopen("player.dat", "wb");
	fwrite(&play, sizeof(Player), 1, fp);
	fwrite(&com, sizeof(Player), 1, fp);

	fclose(fp);
}
//���� �ε�
void loadFile()
{
	//���� ����
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
//���� ����
//void saveFile2()
//{
//	//���� ����
//	FILE* fp = fopen("com.dat", "wb");
//	fwrite(&com, sizeof(Player), 1, fp);
//	fclose(fp);
//}
////���� �ε�2
//void loadFile2()
//{
//	//���� ����
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

//���� ����������
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
	printf("\t\t\t\t         �ƹ�Ű �Է½� ����\n");
	printf("\t\t\t\t         q�� �Է½� ����\n");




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

	int playcard[2] = { 0,0 }; //ī�带 �Է¹ޱ� ���� ���
	int comcard[2] = { 0,0 }; //ī�带 �Է¹ޱ� ���� ���
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
	printf("���� �����ݾ� : %d								��� �����ݾ� : %d\n\n", play.money, com.money);

	printf("					���� ���þ� : \n");


	printf("������ :	%d,%d							��� �� :  %c,%c \n\n", playcard[0], playcard[1], hide[0], hide[1]);

	printf("���ñݾ� �Է����ּ��� : ");


	play.call = 0;
	com.call = 0;

	Sleep(1000);
	int temp = 0;
Recall:
	scanf(" %d", &play.call);

	if (play.money < play.call) {
		printf("���ñݾ��� ���絷���� Ů�ϴ�.\n");
		goto Recall;
	}
	else if (play.money == play.call) {
		printf("�����߽��ϴ�.\n");
		play.money = play.call;
	}
	else {
		printf("%d �����߽��ϴ�.\n", play.call);
		play.money = play.money - play.call;
	}
	Sleep(1000);
	printf("��ǻ�Ͱ� ������ �Դϴ�\n");
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
	printf("��ǻ�Ͱ� %d �����߽��ϴ�.\n", com.call);
	com.money = com.money - com.call;
	Sleep(1000);
	system("cls");
	printf("���� �����ݾ� : %d								��� �����ݾ� : %d\n\n", play.money - play.call, com.money - com.call);

	printf("					���� ���þ� : %d\n", play.call + com.call);


	printf("������ :	%d,%d							��� �� :  %d,%d \n\n", playcard[0], playcard[1], comcard[0], comcard[1]);


	//38,18����
	if (playcard[0] == 3 && playcard[1] == 8 != playcard[0] == 8 && playcard[1] == 3)
	{
		printf("38����!");
		win();
		Sleep(1000);
	}
	else if (comcard[0] == 3 && comcard[1] == 8 != comcard[0] == 8 && comcard[1] == 3)
	{
		printf("38����!");
		lose();
		Sleep(1000);
	}
	else if (playcard[0] == 1 && playcard[1] == 8 != playcard[0] == 8 && playcard[1] == 1)
	{
		printf("18����!");
		win();
		Sleep(1000);
	}
	else if (comcard[0] == 1 && comcard[1] == 8 != comcard[0] == 8 && comcard[1] == 1)
	{
		printf("18����!");
		lose();
		Sleep(1000);
	}
	//�׿� ��
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
		printf("�¸��߽��ϴ�.\n");
		play.money = play.money + play.call + com.call;
		com.money = com.money - com.call;
		Sleep(3000);

	}
	void lose()
	{
		printf("�й��߽��ϴ�.\n");
		com.money = com.money + play.call + com.call;
		play.money = play.money - play.call;
		Sleep(3000);

	}
	void draw()
	{
		printf("���º��Դϴ�.\n");
		play.money = play.money + play.call;
		com.money = com.money + com.call;
		Sleep(3000);

	}

#include "stdafx.h"
#include "./Gameobj/Player.h"
#include "./Gameobj/Monster.h"

//template <typename T> //typename = class
//T Add(T a, T b)
//{
//
//	return a + b;
//}

int main()
{
	//int a = 10, b = 20;
	//int c = Add(a, b);// ��ȯ���� ���ٸ� ������ �����ϴ� ex int c = Add<int>(a,b)

    Player* player = new Player(const_cast<char*>("#"), 10, 100, { 3, 3 });
    Monster* monster = new Monster(const_cast<char*>("&"), 10, 100, { 5, 5 });

    while (true)
    {

		Sleep(50);
        player->Update();
        monster->Update();
		bulletmanger::Get().Update();
		system("cls");

		bulletmanger::Get().Render();
        player->Render();
        monster->Render();

	}
	
	delete monster;
	delete player;
    return 0;
}
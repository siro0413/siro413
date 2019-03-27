#include "stdafx.h"
#include "./Gameobj/Player.h"
#include "./Gameobj/Monster.h"



int main()
{


	Player* player = new Player(const_cast<char*>("#"), 10, 100, { 3, 3 });
	Monster* monster = new Monster(const_cast<char*>("&"), 10, 100, { 5, 5 });

	while (true)
	{
		Sleep(100);
		player->Update();
		monster->Update();

		system("cls");

		player->Render();
		monster->Render();
	}

	delete monster;
	delete player;
	return 0;
}
#include "stdafx.h"
#include "stage1.h"
#include "map/map.h"
#include "Gameobj/Player.h"
#include "Gameobj/Monster.h"

stage1::stage1()
{
	map = new Map();
	player = new Player(const_cast<char*>("@"), 20, 100, { 3,3 });
	//monster = new Monster(const_cast<char*>("#"), 5, 100, { 5,5 });
	monster[0] = new Monster(/*const_cast<char*>("%"), 10, 50, { 5,5}*/ );
	monster[1] = new Monster(/*const_cast<char*>("$"), 10, 50, { 6,6 }*/);
	monster[2] = new Monster(/*const_cast<char*>("&"), 10, 50, { 7,7 }*/);

	monster[0]->Initialize(const_cast<char*>("%"), 10, 50, { 5,5 });
	monster[1]->Initialize(const_cast<char*>("%"), 10, 50, { 6,6 });
	monster[2]->Initialize(const_cast<char*>("%"), 10, 50, { 7,7 });

	monster2 = new Monster[3];
	monster2[0].Initialize(const_cast<char*>("%"), 10, 50, { 5,5 });
	monster2[1].Initialize(const_cast<char*>("%"), 10, 50, { 6,6 });
	monster2[2].Initialize(const_cast<char*>("%"), 10, 50, { 7,7 });
}

stage1::~stage1()
{
	for(auto mon : monster)
		SAFE_DELETE(mon);

	//delete[] monster2;//[]배열자체를 지워야한다

	SAFE_DELETE_ARRAY(monster2);

	SAFE_DELETE(player);
	SAFE_DELETE(map);

}

void stage1::Update()
{
	player->Update();
	//monster->Update();
}

void stage1::Render()
{
	map->Render();
	player->Render();
	//monster->Render();
}

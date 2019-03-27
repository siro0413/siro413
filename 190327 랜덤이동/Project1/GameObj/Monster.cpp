#include "stdafx.h"
#include "../Gameobj/Monster.h"


std::random_device rd;
std::mt19937 randEngine(rd());



Monster::Monster(char * symbol, int damage, int hp, Pos pos)
	: GameObject(symbol, damage, hp, pos)
	, direction(MonDirect::Right)
	, time(0)
{
}

Monster::~Monster()
{
}

void Monster::Update()
{
	//int arr[2];
	//arr[static_cast<unsigned int>(MonDirect::UP)];
	//std::uniform_int_distribution<int> dist(0, 3);
	//int random = dist(randEngine); //이게 정석
	//chromon //시간관리함수일종
	//uniform initaialization(중괄호 초기화)
	if (timeGetTime() - time > 1000)
	{
		direction = static_cast<MonDirect>(std::uniform_int_distribution<int>{0, 3}(randEngine));
		time = timeGetTime();
	}

jump:
	switch (direction)
	{
	case MonDirect::Up: pos.y--;
		break;
	case MonDirect::Right: pos.x++;
		break;
	case MonDirect::Down: pos.y++;
		break;
	case MonDirect::Left: pos.x--;
		break;
	case MonDirect::UpRi: pos.x++; pos.y--;
		break;
	case MonDirect::UpLe: pos.x--; pos.y--;
		break;
	case MonDirect::DownRi: pos.x++; pos.y++;
		break;
	case MonDirect::DownLe: pos.x--; pos.y++;
		break;

	default:
		break;
	}
	bool bChek = false;
	bChek |= pos.x <= 1;
	bChek |= pos.x >= 40;
	bChek |= pos.y <= 1;
	bChek |= pos.y >= 40;

	if (bChek)
	{
		unsigned int tempDir = static_cast<unsigned int>(direction);
		tempDir = (tempDir < 4) ? tempDir + 4 : tempDir - 4;

		direction = static_cast<MonDirect>(tempDir);
		goto jump;
	}

}

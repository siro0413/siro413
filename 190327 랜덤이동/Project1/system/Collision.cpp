#include "stdafx.h"
#include "Collision.h"
#include "../Gameobj/Player.h"
#include "../Gameobj/Monster.h"

const bool Collision::IsInside(Player * player, Monster * monster)
{
	//if (player->pos.x == monster->pos.x && player->pos.x == monster->pos.x)
	//    return true;

	//bool bCheck = false;
	//bCheck |= player->pos.x == monster->pos.x;
	//bCheck |= player->pos.y == monster->pos.y;

	if (player->pos == monster->pos)
		return true;

	return false;
}

//+ - * /
//+= -= *= /=
//== !=


const bool Collision::IsIntersect(Player * player, Monster * monster)
{
	//Up
	bool bCheck = true;
	bCheck &= player->pos.x == monster->pos.x;
	bCheck &= player->pos.y - 1 == monster->pos.y;

	if (bCheck)
		return true;

	//Down
	bCheck = true;
	bCheck &= player->pos.x == monster->pos.x;
	bCheck &= player->pos.y + 1 == monster->pos.y;

	if (bCheck)
		return true;

	//Left
	bCheck = true;
	bCheck &= player->pos.x - 1 == monster->pos.x;
	bCheck &= player->pos.y == monster->pos.y;

	if (bCheck)
		return true;

	//Right
	bCheck = true;
	bCheck &= player->pos.x + 1 == monster->pos.x;
	bCheck &= player->pos.y == monster->pos.y;

	if (bCheck)
		return true;

	return false;
}

#include "stdafx.h"
#include "Player.h"
#define UP 224 72
#define Down 224 80
#define Left 224 75
#define Right 224 77


Player::Player(char * symbol, int damage, int hp, Pos pos)
	: GameObject(symbol, damage, hp, pos)
{
}

Player::~Player()
{

}

void Player::Update()
{
	if (GetAsyncKeyState('W') & 0x8000)
		pos.y--;
	else if (GetAsyncKeyState('S') & 0x8000)
		pos.y++;
	if (GetAsyncKeyState('A') & 0x8000)
		pos.x--;
	else if (GetAsyncKeyState('D') & 0x8000)
		pos.x++;


}
//GetAsyncKeyState vs getkeysate
//0x8000
//virtual keycode
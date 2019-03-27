#pragma once
#include "GameObject.h"



class Player final : public GameObject
{
public:

	Player(char* symbol, int damage, int hp, Pos pos/* = {3, 3}*/);//default parameter
	~Player();

	void Update() override;

	void Test() {}

private:
	friend class Collision;
};
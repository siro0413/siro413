#include "stdafx.h"
#pragma once

class bullet
{
public:
	bullet() = default;
	~bullet() = default;
	bullet(Pos pos, bool bFire)
		:pos(pos), bFire(bFire)
		//,symbol("*"),speed(1)
	{}

	void Updete();
	void Render();


private:
	//std::string symbol = "*";
	Pos pos = { 0,0 };
	int speed = 1;
	bool bFire = false;

};


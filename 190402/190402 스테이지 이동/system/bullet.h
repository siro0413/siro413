#pragma once

class bullet final
{
public:
	bullet() = default;
	bullet(Pos pos,bool bFire)
		:pos(pos),bFire(bFire)
		//,symbol("*"),speed(1)
	{}
	~bullet() = default;

	void Updete();
	void Render();


private:
	friend class bulletmanger;

	//std::string symbol = "*";
	Pos pos = { 0,0 };
	int speed = 1;
	bool bFire = false;
};


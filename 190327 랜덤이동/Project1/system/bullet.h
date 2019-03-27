#pragma once

class bullet final
{
public:
	bullet() = default;
	~bullet() = default;

private:
	std::string symbol;
	Pos pos;
	int speed;
	bool bFire;
};


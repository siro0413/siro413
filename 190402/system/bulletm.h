#pragma once
#include "bullet.h"
class bulletmanger final
{
public:

	static bulletmanger& Get()
	{
		static bulletmanger instance;
		return instance;
	}

	void AddBullet(const Pos& pos, const int& speed = 1);

	void Update();
	void Render();

private:
	bulletmanger() = default;
	~bulletmanger() = default;

private:
	std::vector<bullet> bullsts;

};


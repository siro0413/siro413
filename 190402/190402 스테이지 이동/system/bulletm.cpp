#include "stdafx.h"
#include "system/bulletm.h"

void bulletmanger::AddBullet(const Pos & pos, const int & speed)
{
	int selectBulletindex = -1;
	int count = 0;
	for (auto& bullet : bullsts)
	{
		if ( ! bullet.bFire)
		{
			selectBulletindex = count;
			break;
		}
		count++;
	}

	if (selectBulletindex > -1)
	{
		bullsts[selectBulletindex].bFire = true;
		bullsts[selectBulletindex].pos = pos;
		bullsts[selectBulletindex].speed = speed;

	}
	else
	{
		bullet bullet;
		bullet.bFire = true;
		bullet.pos = pos;
		bullet.speed = speed;
		bullsts.push_back(bullet);

		//bullsts.emplace_back(pos, true);
	}
	//사용후 다시 원래대로 메모리를 돌려줌 
	//bullsts.clear(); //요소는 남기고 메모리를 지움 <- 정적할당일때만 clear를 넣어야함 
	//bullsts.shrink_to_fit(); //요소까지 날려버리는 함수
}

void bulletmanger::Update()
{
	for (auto& bullet : bullsts)
		bullet.Updete();
}

void bulletmanger::Render()
{
	std::string str = "Bullet Count :" + std::to_string(bullsts.size());

	Renderer::Get().Render({ 15,0 }, str.c_str());
	
	for (auto& bullet : bullsts)
		bullet.Render();
}

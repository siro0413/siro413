#include "bullet.h"



void bullet::Updete() //총알의 최대길이
{

	if (bFire)
	{
		pos.x++;


		bool bCheck = false;

		bCheck |= pos.x <= 1;
		bCheck |= pos.x >= 40;
		bCheck |= pos.y <= 1;
		bCheck |= pos.y >= 20;

		if (bCheck)
			bFire = false;
	}
}

void bullet::Render() //총알그리기
{
	if (bFire)
		Renderer::Get().Render(pos, "*" /*symbol.c_str()*/); //const charÇü
}
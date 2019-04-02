#include "stdafx.h"
#include "bullet.h"
#include "Gameobj/Player.h"

void bullet::Updete()
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

void bullet::Render()
{
	if (bFire)
		Renderer::Get().Render(pos,"*" /*symbol.c_str()*/); //const charÇü
}

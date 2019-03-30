#pragma once

struct Pos
{

	//¿¬»êÀÚ ÀçÁ¤ÀÇ
	const bool operator==(const Pos& rhs) const
	{
		bool bCheck = true;
		bCheck &= x == rhs.x;
		bCheck &= y == rhs.y;
		return bCheck;
	}

	short x;
	short y;
};
#pragma once

//#ifndef _POS
//#define _POS


struct Pos
{

	//연산자 재정의
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

//#endif // _POS
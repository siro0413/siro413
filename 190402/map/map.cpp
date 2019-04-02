#include "stdafx.h"
#include "map.h"

Map::Map()
{
	//1:─
	//2:│
	//3:┌
	//4:┐
	//5:┘
	//6:└



	int temp[MAP_SIZE_Y][MAP_SIZE_X] =
	{
		3, 1, 1, 1, 1, 1, 1, 1, 1, 4,
		2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
		2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
		2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
		2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
		2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
		2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
		2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
		2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
		5, 1, 1, 1, 1, 1, 1, 1, 1, 6,


	};
	//for (int y = 0; y < MAP_SIZE_Y; y++)
	//	for (int x = 0; x < MAP_SIZE_X; x++)
	//		map[y][x] = temp[y][x];
	memcpy(map, temp, sizeof(int)*MAP_SIZE_Y*MAP_SIZE_X);
}
//Dst 복사본 목적지
//Src 원본
Map ::~Map()
{
}

void Map::Render()
{
	for (int y = 0; y < MAP_SIZE_Y; y++)
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			std::string symbol = "";

			switch (map[y][x])
			{
			case 0 : symbol = " "; break;
			case 1 : symbol = "─"; break;
			case 2 : symbol = "│"; break;
			case 3 : symbol = "┌"; break;
			case 4 : symbol = "┐"; break;
			case 5 : symbol = "└"; break;
			case 6 : symbol = "┘"; break;
			}

			Renderer::Get().Render
			(
				{static_cast<short>(x),static_cast<short>(y) },
			symbol.c_str()
			);

		}
}

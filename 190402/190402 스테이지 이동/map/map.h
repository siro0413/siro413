#pragma once
#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10



class Map final
{
public:
	Map ();
	~Map ();


	void Render();

private:
	int map[MAP_SIZE_Y][MAP_SIZE_X];
};


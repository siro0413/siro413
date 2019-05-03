#pragma once
#pragma once

class Game
{
public:
	Game(class Graphics* graphics);
	~Game();

	void Update();
	void Render();

	void Collision();

	bool bCheck = false;

private:
	class Graphics* graphics;
	class Rect* rect;

	std::vector<Rect*> rects;

};